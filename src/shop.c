/*
  SillyMUD Distribution V1.1b             (c) 1993 SillyMUD Developement
 
  See license.doc for distribution terms.   SillyMUD is based on DIKUMUD
*/
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "protos.h"
#include "db.h"
#include "act.comm.h"
#include "act.wizard.h"
#include "act.social.h"
#include "act.comm.h"
#include "utility.h"
#include "db.h"
#include "shop.h"
#include "spec_procs.h"

#define SHOP_FILE "tinyworld.shp"
#define MAX_TRADE 5
#define MAX_PROD 5


extern struct str_app_type str_app[];
extern struct chr_app_type chr_apply[];

float shop_multiplier = 0;
int gevent = 0;                 /* Global Event happening currently */

#define SHOP_MAX_MSG_SIZE 128

struct shop_data {
  int producing[MAX_PROD];      /* Which item to produce (virtual)      */
  float profit_buy;             /* Factor to multiply cost with.        */
  float profit_sell;            /* Factor to multiply cost with.        */
  byte type[MAX_TRADE];         /* Which item to trade.                 */
  char no_such_item1[SHOP_MAX_MSG_SIZE];  /* Message if keeper hasn't got an item */
  char no_such_item2[SHOP_MAX_MSG_SIZE];  /* Message if player hasn't got an item */
  char missing_cash1[SHOP_MAX_MSG_SIZE];  /* Message if keeper hasn't got cash    */
  char missing_cash2[SHOP_MAX_MSG_SIZE];  /* Message if player hasn't got cash    */
  char do_not_buy[SHOP_MAX_MSG_SIZE];  /* If keeper dosn't buy such things.    */
  char message_buy[SHOP_MAX_MSG_SIZE];  /* Message when player buys item        */
  char message_sell[SHOP_MAX_MSG_SIZE];  /* Message when player sells item       */
  int temper1;                  /* How does keeper react if no money    */
  int temper2;                  /* How does keeper react when attacked  */
  int keeper;                   /* The mobil who owns the shop (virtual) */
  int with_who;                 /* Who does the shop trade with?        */
  int in_room;                  /* Where is the shop?                   */
  int open1, open2;             /* When does the shop open?             */
  int close1, close2;           /* When does the shop close?            */
};

#if HASH
extern struct hash_header room_db;
#else
extern struct room_data *room_db;
#endif
extern struct time_info_data time_info;

struct shop_data *shop_index;
int number_of_shops;

int is_ok(struct char_data *keeper, struct char_data *ch, int shop_nr) {
  if (shop_index[shop_nr].open1 > time_info.hours) {
    say(keeper, "Come back later!");
    return (FALSE);
  }
  else if (shop_index[shop_nr].close1 < time_info.hours) {
    if (shop_index[shop_nr].open2 > time_info.hours) {
      say(keeper, "Sorry, we have closed, but come back later.");
      return (FALSE);
    }
    else if (shop_index[shop_nr].close2 < time_info.hours) {
      say(keeper, "Sorry, come back tomorrow.");
      return (FALSE);
    };
  }

  if (!(CAN_SEE(keeper, ch))) {
    say(keeper, "I don't trade with someone I can't see!");
    return (FALSE);
  };

  switch (shop_index[shop_nr].with_who) {
  case 0:
    return (TRUE);
  case 1:
    return (TRUE);
  default:
    return (TRUE);
  };
}

int trade_with(struct obj_data *item, int shop_nr) {
  int counter;

  if (item->obj_flags.cost < 1)
    return (FALSE);

  for (counter = 0; counter < MAX_TRADE; counter++)
    if (shop_index[shop_nr].type[counter] == item->obj_flags.type_flag)
      return (TRUE);
  return (FALSE);
}

int shop_producing(struct obj_data *item, int shop_nr) {
  int counter;

  if (item->item_number < 0)
    return (FALSE);

  for (counter = 0; counter < MAX_PROD; counter++)
    if (shop_index[shop_nr].producing[counter] == item->item_number)
      return (TRUE);
  return (FALSE);
}

void shopping_buy(char *arg, struct char_data *ch,
                  struct char_data *keeper, int shop_nr) {
  char argm[100], buf[MAX_STRING_LENGTH], newarg[100];
  int num = 1;
  struct obj_data *temp1;
  int i;
  float mult = 1.0, perc;
  int cost;

  if (!(is_ok(keeper, ch, shop_nr)))
    return;

  if (keeper->generic != 0)
    for (i = 0; i <= MAX_TRADE; i++) {
      if (keeper->generic == FAMINE)
        if (shop_index[shop_nr].type[i] == ITEM_FOOD) {
          mult = shop_multiplier;       /* we're in a famine, we sell food, so we */
          break;                /* our prices to hell ;-) -DM */
        }
      if (keeper->generic == DWARVES_STRIKE)
        if ((shop_index[shop_nr].type[i] == ITEM_ARMOR)
            || (shop_index[shop_nr].type[i] == ITEM_WEAPON)) {
          mult = shop_multiplier;
          break;
        }
    }

  only_argument(arg, argm);
  if (!(*argm)) {
    SPRINTF(buf, "%s what do you want to buy??", GET_NAME(ch));
    do_tell(keeper, buf, "tell");
    return;
  }

  if ((num = getabunch(argm, newarg)) != 0) {
    strcpy(argm, newarg);
  }
  if (num == 0)
    num = 1;

  if (!(temp1 = get_obj_in_list_vis(ch, argm, keeper->carrying))) {
    SPRINTF(buf, shop_index[shop_nr].no_such_item1, GET_NAME(ch));
    do_tell(keeper, buf, "tell");
    return;
  }

  if (temp1->obj_flags.cost <= 0) {
    SPRINTF(buf, shop_index[shop_nr].no_such_item1, GET_NAME(ch));
    do_tell(keeper, buf, "tell");
    extract_obj(temp1);
    return;
  }

  perc = 100.0 + chr_apply[(int)GET_CHR(ch)].reaction;
  perc /= 100.0;

  if (shop_index[shop_nr].profit_buy < 1.0)
    shop_index[shop_nr].profit_buy = 1.33;

  cost =
    (temp1->obj_flags.cost * mult) * (shop_index[shop_nr].profit_buy / perc);

  cost /= 6;

  if (cost < 1)
    cost = 1;

  if (do_i_hate_you(ch))        /* we are prejudice against certain races */
    cost *= 2;

  if (GET_GOLD(ch) < (int)(num * cost)) {
    SPRINTF(buf, shop_index[shop_nr].missing_cash2, GET_NAME(ch));
    do_tell(keeper, buf, "tell");

    switch (shop_index[shop_nr].temper1) {
    case 0:
      do_action(keeper, GET_NAME(ch), "puke");
      return;
    case 1:
      emote(keeper, "grins happily");
      return;
    default:
      return;
    }
  }

  if ((IS_CARRYING_N(ch) + num) > (CAN_CARRY_N(ch))) {
    send_to_charf(ch, "%s : You can't carry that many items.\n\r",
                  fname(temp1->name));
    return;
  }

  if ((IS_CARRYING_W(ch) + (num * temp1->obj_flags.weight)) > CAN_CARRY_W(ch)) {
    send_to_charf(ch, "%s : You can't carry that much weight.\n\r",
                  fname(temp1->name));
    return;
  }

  act("$n buys $p.", FALSE, ch, temp1, 0, TO_ROOM);

  SPRINTF(buf, shop_index[shop_nr].message_buy,
          GET_NAME(ch), (int)(num * cost));

  do_tell(keeper, buf, "tell");

  send_to_charf(ch, "You now have %s (*%d).\n\r", temp1->short_description, num);


  if (cost < 1)
    cost = 1;

  while (num-- > 0) {

    if (get_max_level(ch) < DEMIGOD)
      GET_GOLD(ch) -= (int)cost;

    GET_GOLD(keeper) += (int)cost;

    /* Test if producing shop ! */
    if (shop_producing(temp1, shop_nr)) {
      temp1 = read_object(temp1->item_number, REAL);
      if (!temp1) {
        send_to_char("Game error loading object. File a bug.\n\r", ch);
        return;
      }
    }
    else {
      obj_from_char(temp1);
      if (temp1 == NULL) {
        send_to_char("Sorry, I just ran out of those.\n\r", ch);
        GET_GOLD(ch) += cost;
        return;
      }
    }

    obj_to_char(temp1, ch);

  }
  return;
}

void shopping_sell(char *arg, struct char_data *ch,
                   struct char_data *keeper, int shop_nr) {
  char argm[100], buf[MAX_STRING_LENGTH];
  int cost, temp_cost, i;
  struct obj_data *temp1;
  float mult = 1.0, perc;

  if (!(is_ok(keeper, ch, shop_nr)))
    return;

  if (keeper->generic != 0)
    for (i = 0; i <= MAX_TRADE; i++) {
      if (keeper->generic == FAMINE)
        if (shop_index[shop_nr].type[i] == ITEM_FOOD) {
          mult = shop_multiplier;       /*we're in a famine, we sell food, so we */
          break;                /* raise our prices to hell ;-) -DM */
        }
      if (keeper->generic == DWARVES_STRIKE)
        if ((shop_index[shop_nr].type[i] == ITEM_ARMOR)
            || (shop_index[shop_nr].type[i] == ITEM_WEAPON)) {
          mult = shop_multiplier;
          break;
        }
    }

  only_argument(arg, argm);

  if (!(*argm)) {
    SPRINTF(buf, "%s What do you want to sell??", GET_NAME(ch));
    do_tell(keeper, buf, "tell");
    return;
  }

  if (!(temp1 = get_obj_in_list_vis(ch, argm, ch->carrying))) {
    SPRINTF(buf, shop_index[shop_nr].no_such_item2, GET_NAME(ch));
    do_tell(keeper, buf, "tell");
    return;
  }

  if (IS_OBJ_STAT(temp1, ITEM_NODROP)) {
    send_to_char("You can't let go of it, it must be CURSED!\n\r", ch);
    return;
  }

  if (!(trade_with(temp1, shop_nr)) || (temp1->obj_flags.cost < 1)) {
    SPRINTF(buf, shop_index[shop_nr].do_not_buy, GET_NAME(ch));
    do_tell(keeper, buf, "tell");
    return;
  }

  perc = 100.0 + chr_apply[(int)GET_CHR(ch)].reaction;
  perc /= 100.0;

  cost =
    (temp1->obj_flags.cost * mult) * (shop_index[shop_nr].profit_sell * perc);

  if (do_i_hate_you(ch) && cost)
    cost /= 2;

  if (cost < 1)
    cost = 1;

  if (GET_GOLD(keeper) < (int)cost) {
    SPRINTF(buf, shop_index[shop_nr].missing_cash1, GET_NAME(ch));
    do_tell(keeper, buf, "tell");
    return;
  }

  if ((ITEM_TYPE(temp1) == ITEM_WAND) || (ITEM_TYPE(temp1) == ITEM_STAFF)) {
    if (temp1->obj_flags.value[1]) {
      cost = (int)cost *(float)(temp1->obj_flags.value[2] /
                                (float)temp1->obj_flags.value[1]);
    }
    else {
      cost = 0;
    }
  }
  else if (ITEM_TYPE(temp1) == ITEM_ARMOR) {
    if (temp1->obj_flags.value[1]) {
      cost = (int)cost *(float)(temp1->obj_flags.value[0] /
                                (float)(temp1->obj_flags.value[1]));
    }
    else {
      cost = 0;
    }
  }

  act("$n sells $p.", FALSE, ch, temp1, 0, TO_ROOM);
  temp_cost = (int)cost;
  if (temp_cost < 0)
    temp_cost = 1;

  SPRINTF(buf, shop_index[shop_nr].message_sell, GET_NAME(ch), temp_cost);

/* (int) (temp1->obj_flags.cost*	
		shop_index[shop_nr].profit_sell +
		((chr_apply[GET_CHR(ch)].reaction*temp1->obj_flags.cost)/100)))
; */

  do_tell(keeper, buf, "tell");

  send_to_charf(ch, "The shopkeeper now has %s.\n\r", temp1->short_description);

  if (GET_GOLD(keeper) < temp_cost) {
    /* (int) (temp1->obj_flags.cost*
       shop_index[shop_nr].profit_sell +
       ((chr_apply[GET_CHR(ch)].reaction*temp1->obj_flags.cost)/100))) {
     */
    SPRINTF(buf, shop_index[shop_nr].missing_cash1, GET_NAME(ch));
    do_tell(keeper, buf, "tell");
    return;
  }

  GET_GOLD(ch) += temp_cost;
  /* (int) (temp1->obj_flags.cost*
     shop_index[shop_nr].profit_sell +
     ((chr_apply[GET_CHR(ch)].reaction*temp1->obj_flags.cost)/100));
   */
  GET_GOLD(keeper) -= temp_cost;
  /* (int) (temp1->obj_flags.cost*
     shop_index[shop_nr].profit_sell +
     ((chr_apply[GET_CHR(ch)].reaction*temp1->obj_flags.cost)/100));
   */
  obj_from_char(temp1);
  if (temp1 == NULL) {
    send_to_char("As far as I am concerned, you are out..\n\r", ch);
    return;
  }
  if ((get_obj_in_list(argm, keeper->carrying)) ||
      (GET_ITEM_TYPE(temp1) == ITEM_TRASH)) {
    extract_obj(temp1);
  }
  else {
    obj_to_char(temp1, keeper);
  }
  return;
}

void shopping_value(char *arg, struct char_data *ch,
                    struct char_data *keeper, int shop_nr) {
  char argm[100], buf[MAX_STRING_LENGTH];
  struct obj_data *temp1;
  int i, cost;
  float mult = 1.0, perc;

  if (!(is_ok(keeper, ch, shop_nr)))
    return;

  if (keeper->generic != 0)
    for (i = 0; i <= MAX_TRADE; i++) {
      if (keeper->generic == FAMINE)
        if (shop_index[shop_nr].type[i] == ITEM_FOOD) {
          mult = shop_multiplier;
          break;                /* our prices to hell ;-) -DM */
        }
      if (keeper->generic == DWARVES_STRIKE)
        if ((shop_index[shop_nr].type[i] == ITEM_ARMOR)
            || (shop_index[shop_nr].type[i] == ITEM_WEAPON)) {
          mult = shop_multiplier;
          break;
        }
    }

  only_argument(arg, argm);

  if (!(*argm)) {
    SPRINTF(buf, "%s What do you want me to evaluate??", GET_NAME(ch));
    do_tell(keeper, buf, "tell");
    return;
  }

  if (!(temp1 = get_obj_in_list_vis(ch, argm, ch->carrying))) {
    SPRINTF(buf, shop_index[shop_nr].no_such_item2, GET_NAME(ch));
    do_tell(keeper, buf, "tell");
    return;
  }

  if (!(trade_with(temp1, shop_nr))) {
    SPRINTF(buf, shop_index[shop_nr].do_not_buy, GET_NAME(ch));
    do_tell(keeper, buf, "tell");
    return;
  }

  perc = 100.0 + chr_apply[(int)GET_CHR(ch)].reaction;
  perc /= 100.0;

  cost = (temp1->obj_flags.cost * mult) *
    (shop_index[shop_nr].profit_sell * perc);

  if (do_i_hate_you(ch))
    cost /= 2;

  SPRINTF(buf, "%s I'll give you %d gold coins for that!",
          GET_NAME(ch), (int)cost);

  do_tell(keeper, buf, "tell");

  return;
}

void shopping_list(char *UNUSED(arg), struct char_data *ch,
                   struct char_data *keeper, int shop_nr) {
  char buf[MAX_STRING_LENGTH], buf2[MAX_BUF_LENGTH], buf3[100];
  struct obj_data *temp1;
  extern char *drinks[];
  int found_obj;
  int i, cost;
  float mult = 1.0, perc;

  if (!(is_ok(keeper, ch, shop_nr)))
    return;


  if (keeper->generic != 0)
    for (i = 0; i <= MAX_TRADE; i++) {
      if (keeper->generic == FAMINE)
        if (shop_index[shop_nr].type[i] == ITEM_FOOD) {
          mult = shop_multiplier;
          break;                /* Send our prices to hell ;-) -DM */
        }
      if (keeper->generic == DWARVES_STRIKE)
        if ((shop_index[shop_nr].type[i] == ITEM_ARMOR)
            || (shop_index[shop_nr].type[i] == ITEM_WEAPON)) {
          mult = shop_multiplier;
          break;
        }
    }

  strcpy(buf, "You can buy:\n\r");
  found_obj = FALSE;
  if (keeper->carrying)
    for (temp1 = keeper->carrying; temp1; temp1 = temp1->next_content)
      if ((CAN_SEE_OBJ(ch, temp1)) && (temp1->obj_flags.cost > 0)) {
        found_obj = TRUE;

        perc = 100.0 + chr_apply[(int)GET_CHR(ch)].reaction;
        perc /= 100.0;

        if (shop_index[shop_nr].profit_buy < 1.0)
          shop_index[shop_nr].profit_buy = 1.33;

        cost = (temp1->obj_flags.cost * mult) *
          (shop_index[shop_nr].profit_buy / perc);

        cost /= 6;

        if (cost < 1)
          cost = 1;

        if (do_i_hate_you(ch))  /* we are prejudice against certain races */
          cost *= 2;

        if (temp1->obj_flags.type_flag != ITEM_DRINKCON) {

          SPRINTF(buf2, "%s for %d gold coins.\n\r",
                  (temp1->short_description), cost);
        }
        else {
          if (temp1->obj_flags.value[1])
            SPRINTF(buf3, "%s of %s", (temp1->short_description)
                    , drinks[temp1->obj_flags.value[2]]);
          else
            SPRINTF(buf3, "%s", (temp1->short_description));
          SPRINTF(buf2, "%s for %d gold coins.\n\r", buf3, cost);
        }
        strcat(buf, CAP(buf2));
      };

  if (!found_obj)
    strcat(buf, "Nothing!\n\r");

  send_to_char(buf, ch);
  return;
}

void shopping_kill(char *UNUSED(arg), struct char_data *ch,
                   struct char_data *keeper, int shop_nr) {
  char buf[100];

  switch (shop_index[shop_nr].temper2) {
  case 0:
    SPRINTF(buf, "%s Don't ever try that again!", GET_NAME(ch));
    do_tell(keeper, buf, "tell");
    return;

  case 1:
    SPRINTF(buf, "%s Scram - midget!", GET_NAME(ch));
    do_tell(keeper, buf, "tell");
    return;

  default:
    return;
  }
}

int shop_keeper(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *UNUSED(mob), int type) {
  char argm[100];
  struct char_data *temp_char;
  struct char_data *keeper;
  int shop_nr;

  if (type == EVENT_DWARVES_STRIKE) {
    ch->generic = DWARVES_STRIKE;
    return (FALSE);
  }

  if (type == EVENT_FAMINE) {
    ch->generic = FAMINE;
    return (FALSE);
  }

  keeper = 0;

  if (!real_roomp(ch->in_room))
    return (FALSE);

  for (temp_char = real_roomp(ch->in_room)->people; (!keeper) && (temp_char);
       temp_char = temp_char->next_in_room)
    if (IS_MOB(temp_char))
      if (mob_index[temp_char->nr].func == shop_keeper)
        keeper = temp_char;



  for (shop_nr = 0; shop_index[shop_nr].keeper != keeper->nr; shop_nr++);


  if (!cmd) {
    if (keeper->specials.fighting) {
      return (citizen(keeper, 0, "", keeper, 0));
    }
  }

  if (do_i_hate_you(ch) && number(0, 3) == 2) {
    act("$n sneers at you.", TRUE, keeper, 0, ch, TO_VICT);
    act("$n sneers at $N.", TRUE, keeper, 0, ch, TO_NOTVICT);
  }

  if (STREQ(cmd, "buy") &&
      (ch->in_room == shop_index[shop_nr].in_room))
  {
    shopping_buy(arg, ch, keeper, shop_nr);
    return (TRUE);
  }

  if (STREQ(cmd, "sell") &&
      (ch->in_room == shop_index[shop_nr].in_room))
  {
    shopping_sell(arg, ch, keeper, shop_nr);
    return (TRUE);
  }

  if ((STREQ(cmd, "value") &&
       (ch->in_room == shop_index[shop_nr].in_room)))
  {
    shopping_value(arg, ch, keeper, shop_nr);
    return (TRUE);
  }

  if (STREQ(cmd, "list") &&
      (ch->in_room == shop_index[shop_nr].in_room))
  {
    shopping_list(arg, ch, keeper, shop_nr);
    return (TRUE);
  }

  if (STREQ(cmd, "hit") || STREQ(cmd, "kill")) {
    only_argument(arg, argm);

    if (keeper == get_char_room(argm, ch->in_room)) {
      shopping_kill(arg, ch, keeper, shop_nr);
      return (TRUE);
    }
  }
  else if (STREQ(cmd, "cast") ||
           STREQ(cmd, "recite") ||
           STREQ(cmd, "use")) {
    act("$N tells you 'No magic here - kid!'.", FALSE, ch, 0, keeper, TO_CHAR);
    return TRUE;
  }

  return (FALSE);
}

void boot_the_shops() {
  int temp;
  int count;
  FILE *shop_f;
  int keeper;

  if (!(shop_f = fopen(SHOP_FILE, "r"))) {
    perror("Error in boot shop\n");
    exit(0);
  }

  number_of_shops = 0;

  for (;;) {
    char buf[128];
    FREAD_STRING_NA(buf, shop_f);
    if (*buf == '#') {          /* a new shop */
      if (!number_of_shops)     /* first shop */
        CREATE(shop_index, struct shop_data, 1);
      else
        if (!(shop_index =
              (struct shop_data *)realloc(shop_index, (number_of_shops + 1) *
                                          sizeof(struct shop_data)))) {
        perror("Error in boot shop\n");
        exit(0);
      }

      for (count = 0; count < MAX_PROD; count++) {
        fscanf(shop_f, "%d \n", &temp);
        if (temp >= 0)
          shop_index[number_of_shops].producing[count] = real_object(temp);
        else
          shop_index[number_of_shops].producing[count] = temp;
      }
      fscanf(shop_f, "%f \n", &shop_index[number_of_shops].profit_buy);
      fscanf(shop_f, "%f \n", &shop_index[number_of_shops].profit_sell);
      for (count = 0; count < MAX_TRADE; count++) {
        fscanf(shop_f, "%d \n", &temp);
        shop_index[number_of_shops].type[count] = (byte) temp;
      }
      FREAD_STRING_NA(shop_index[number_of_shops].no_such_item1, shop_f);
      FREAD_STRING_NA(shop_index[number_of_shops].no_such_item2, shop_f);
      FREAD_STRING_NA(shop_index[number_of_shops].do_not_buy, shop_f);
      FREAD_STRING_NA(shop_index[number_of_shops].missing_cash1, shop_f);
      FREAD_STRING_NA(shop_index[number_of_shops].missing_cash2, shop_f);
      FREAD_STRING_NA(shop_index[number_of_shops].message_buy, shop_f);
      FREAD_STRING_NA(shop_index[number_of_shops].message_sell, shop_f);
      fscanf(shop_f, "%d \n", &shop_index[number_of_shops].temper1);
      fscanf(shop_f, "%d \n", &shop_index[number_of_shops].temper2);
      fscanf(shop_f, "%d \n", &keeper);

      shop_index[number_of_shops].keeper = real_mobile(keeper);

      if (shop_index[number_of_shops].keeper < 0 ||
          shop_index[number_of_shops].keeper > top_of_mobt) {
        char *fmt = "***WARNING***: Shop %d has invalid keeper mobile %d";
        char *buf;
        buf = (char *)malloc(strlen(fmt) + 40);
        log_msgf(fmt, number_of_shops, keeper);
        free(buf);
      }

      fscanf(shop_f, "%d \n", &shop_index[number_of_shops].with_who);
      fscanf(shop_f, "%d \n", &shop_index[number_of_shops].in_room);
      fscanf(shop_f, "%d \n", &shop_index[number_of_shops].open1);
      fscanf(shop_f, "%d \n", &shop_index[number_of_shops].close1);
      fscanf(shop_f, "%d \n", &shop_index[number_of_shops].open2);
      fscanf(shop_f, "%d \n", &shop_index[number_of_shops].close2);

      number_of_shops++;
    }
    else if (*buf == '$')       /* EOF */
      break;
  }

  fclose(shop_f);
}

void assign_the_shopkeepers() {
  int i;

  for (i = 0; i < number_of_shops; i++) {
    int keeper = shop_index[i].keeper;
    if (keeper >= 0 && keeper <= top_of_mobt) {
      mob_index[keeper].func = shop_keeper;
    }
  }
}


int do_i_hate_you(struct char_data *v) {
  switch (GET_RACE(v)) {
  case RACE_ORC:
  case RACE_UNDEAD:
  case RACE_DEMON:
  case RACE_DEVIL:
  case RACE_GHOST:
  case RACE_GOBLIN:
  case RACE_TROLL:
  case RACE_MFLAYER:
  case RACE_ENFAN:
  case RACE_DROW:
  case RACE_TROGMAN:
  case RACE_SMURF:             /* hee hee */
  case RACE_HALFORC:
  case RACE_GOD:               /* I kill me */
    return (TRUE);
    break;
  default:
    return (FALSE);
    break;
  }
}
