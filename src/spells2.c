/*
  SillyMUD Distribution V1.1b             (c) 1993 SillyMUD Developement
 
  See license.doc for distribution terms.   SillyMUD is based on DIKUMUD
*/
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "protos.h"
#include "utility.h"
#include "db.h"

/* Global data */


extern struct room_data *world;
extern struct char_data *character_list;
extern struct obj_data *object_list;
extern int rev_dir[];
extern char *dirs[];
extern int movement_loss[];
extern struct weather_data weather_info;
extern struct time_info_data time_info;
extern struct PolyType DruidList[17];
/* Extern procedures */

void die(struct char_data *ch);
void update_pos(struct char_data *victim);
void clone_char(struct char_data *ch);
bool saves_spell(struct char_data *ch, sh_int spell);
void add_follower(struct char_data *ch, struct char_data *victim);
char in_group(struct char_data *ch1, struct char_data *ch2);
void change_weather(int change);
void raw_unlock_door(struct char_data *ch, struct room_direction_data *exitp,
                     int door);
int no_summon(struct char_data *ch);

struct PolyType PolyList[45] = {
  {"goblin", 4, 201},           /* 1 */
  {"parrot", 4, 9001},
  {"frog", 4, 215},
  {"orc", 5, 4005},
  {"trog", 5, 219},
  {"gnoll", 6, 211},
  {"parrot", 6, 9010},
  {"lizard", 6, 224},
  {"ogre", 8, 4113},
  {"parrot", 8, 9011},
  {"wolf", 8, 3094},            /* 10 */
  {"spider", 9, 227},
  {"beast", 9, 242},
  {"minotaur", 9, 247},
  {"snake", 10, 249},
  {"bull", 10, 1008},
  {"warg", 10, 6100},
  {"rat", 11, 7002},
  {"sapling", 12, 1421},
  {"ogre-maji", 12, 257},
  {"black", 12, 230},           /* 20 */
  {"troll", 14, 4101},
  {"crocodile", 14, 5310},
  {"mindflayer", 14, 7202},
  {"giant", 16, 261},
  {"bear", 16, 9024},
  {"blue", 16, 233},
  {"enfan", 18, 21001},
  {"lamia", 18, 5201},
  {"drider", 18, 5011},
  {"wererat", 19, 7203},        /* 30 */
  {"wyvern", 20, 3415},
  {"mindflayer", 20, 7201},
  {"spider", 20, 20010},
  {"snog", 22, 27008},
  {"roc", 22, 3724},
  {"mud", 23, 7000},
  {"enfan", 23, 21004},
  {"white", 26, 243},
  {"master", 28, 7200},
  {"red", 30, 7040},            /* 40 */
  {"roo", 35, 27411},
  {"brontosaurus", 35, 21802},
  {"mulichort", 40, 15830},     /* 43 */
  {"beholder", 45, 5200}        /* 44 */
};

#define LAST_POLY_MOB 44

void cast_resurrection(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *UNUSED(tar_ch),
                       struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (!tar_obj)
      return;
    spell_resurrection(level, ch, 0, tar_obj);
    break;
  case SPELL_TYPE_STAFF:
    if (!tar_obj)
      return;
    spell_resurrection(level, ch, 0, tar_obj);
    break;
  default:
    log_msg("Serious problem in 'resurrection'");
    break;
  }

}


void cast_major_track(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (!tar_ch)
      tar_ch = ch;
    spell_track(level, ch, tar_ch, NULL);
    break;
  case SPELL_TYPE_POTION:
    spell_track(level, ch, ch, NULL);
    break;
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_track(level, ch, tar_ch, NULL);
    break;
  case SPELL_TYPE_SCROLL:
    if (!tar_ch)
      tar_ch = ch;
    spell_track(level, ch, tar_ch, NULL);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room) {
      if (tar_ch != ch)
        spell_track(level, ch, tar_ch, NULL);
    }
    break;
  default:
    log_msg("Serious problem in 'track'");
    break;
  }

}

void cast_minor_track(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (!tar_ch)
      tar_ch = ch;
    spell_track(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_track(level, ch, ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_track(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (!tar_ch)
      tar_ch = ch;
    spell_track(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room) {
      if (tar_ch != ch)
        spell_track(level, ch, tar_ch, 0);
    }
    break;
  default:
    log_msg("Serious problem in 'track'");
    break;
  }

}

void cast_mana(byte level, struct char_data *ch, char *UNUSED(arg), int type,
               struct char_data *tar_ch, struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_POTION:
    spell_mana(level, ch, ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_mana(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_mana(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious problem in 'mana'");
    break;
  }

}

void cast_armor(byte level, struct char_data *ch, char *UNUSED(arg),
                int type, struct char_data *tar_ch, struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (affected_by_spell(tar_ch, SPELL_ARMOR)) {
      send_to_char("Nothing seems to happen.\n\r", ch);
      return;
    }
    spell_armor(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    if (affected_by_spell(ch, SPELL_ARMOR))
      return;
    spell_armor(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    if (affected_by_spell(tar_ch, SPELL_ARMOR))
      return;
    spell_armor(level, ch, ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    if (affected_by_spell(tar_ch, SPELL_ARMOR))
      return;
    spell_armor(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in armor!");
    break;
  }
}

void cast_stone_skin(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *UNUSED(tar_ch),
                     struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (affected_by_spell(ch, SPELL_STONE_SKIN)) {
      send_to_char("Nothing seems to happen.\n\r", ch);
      return;
    }
    spell_stone_skin(level, ch, ch, 0);
    break;
  case SPELL_TYPE_POTION:
    if (affected_by_spell(ch, SPELL_STONE_SKIN))
      return;
    spell_stone_skin(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (affected_by_spell(ch, SPELL_STONE_SKIN))
      return;
    spell_stone_skin(level, ch, ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    if (affected_by_spell(ch, SPELL_STONE_SKIN))
      return;
    spell_stone_skin(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in stone_skin!");
    break;
  }
}

void cast_astral_walk(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_POTION:
  case SPELL_TYPE_SPELL:

    if (!tar_ch)
      send_to_char("Yes, but who do you wish to walk to?\n", ch);
    else
      spell_astral_walk(level, ch, tar_ch, 0);
    break;

  default:
    log_msg("Serious screw-up in astral walk!");
    break;
  }
}

void cast_teleport(byte level, struct char_data *ch, char *UNUSED(arg),
                   int type, struct char_data *tar_ch,
                   struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_POTION:
  case SPELL_TYPE_SPELL:
    if (!tar_ch)
      tar_ch = ch;
    spell_teleport(level, ch, tar_ch, 0);
    break;

  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_teleport(level, ch, tar_ch, 0);
    break;

  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_teleport(level, ch, tar_ch, 0);
    break;

  default:
    log_msg("Serious screw-up in teleport!");
    break;
  }
}

void cast_bless(byte level, struct char_data *ch, char *UNUSED(arg), int type,
                struct char_data *tar_ch, struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (tar_obj) {              /* It's an object */
      if (IS_SET(tar_obj->obj_flags.extra_flags, ITEM_BLESS)) {
        send_to_char("Nothing seems to happen.\n\r", ch);
        return;
      }
      spell_bless(level, ch, 0, tar_obj);

    }
    else {                      /* Then it is a PC | NPC */

      if (affected_by_spell(tar_ch, SPELL_BLESS) ||
          (GET_POS(tar_ch) == POSITION_FIGHTING)) {
        send_to_char("Nothing seems to happen.\n\r", ch);
        return;
      }
      spell_bless(level, ch, tar_ch, 0);
    }
    break;
  case SPELL_TYPE_POTION:
    if (affected_by_spell(ch, SPELL_BLESS) ||
        (GET_POS(ch) == POSITION_FIGHTING))
      return;
    spell_bless(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj) {              /* It's an object */
      if (IS_SET(tar_obj->obj_flags.extra_flags, ITEM_BLESS))
        return;
      spell_bless(level, ch, 0, tar_obj);

    }
    else {                      /* Then it is a PC | NPC */

      if (!tar_ch)
        tar_ch = ch;

      if (affected_by_spell(tar_ch, SPELL_BLESS) ||
          (GET_POS(tar_ch) == POSITION_FIGHTING))
        return;
      spell_bless(level, ch, tar_ch, 0);
    }
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj) {              /* It's an object */
      if (IS_SET(tar_obj->obj_flags.extra_flags, ITEM_BLESS))
        return;
      spell_bless(level, ch, 0, tar_obj);

    }
    else {                      /* Then it is a PC | NPC */

      if (affected_by_spell(tar_ch, SPELL_BLESS) ||
          (GET_POS(tar_ch) == POSITION_FIGHTING))
        return;
      spell_bless(level, ch, tar_ch, 0);
    }
    break;
  default:
    log_msg("Serious screw-up in bless!");
    break;
  }
}

void cast_infravision(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (IS_AFFECTED(tar_ch, AFF_INFRAVISION)) {
      send_to_char("Nothing seems to happen.\n\r", ch);
      return;
    }
    spell_infravision(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    if (IS_AFFECTED(ch, AFF_INFRAVISION))
      return;
    spell_infravision(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    if (IS_AFFECTED(tar_ch, AFF_INFRAVISION))
      return;
    spell_infravision(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    if (IS_AFFECTED(tar_ch, AFF_INFRAVISION))
      return;
    spell_infravision(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        if (!(IS_AFFECTED(tar_ch, AFF_INFRAVISION)))
          spell_infravision(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in infravision!");
    break;
  }

}

void cast_true_seeing(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (IS_AFFECTED(tar_ch, AFF_TRUE_SIGHT)) {
      send_to_char("Nothing seems to happen.\n\r", ch);
      return;
    }
    spell_true_seeing(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    if (IS_AFFECTED(ch, AFF_TRUE_SIGHT))
      return;
    spell_true_seeing(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    if (IS_AFFECTED(tar_ch, AFF_TRUE_SIGHT))
      return;
    spell_true_seeing(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    if (IS_AFFECTED(tar_ch, AFF_TRUE_SIGHT))
      return;
    spell_true_seeing(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        if (!(IS_AFFECTED(tar_ch, AFF_TRUE_SIGHT)))
          spell_true_seeing(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in true_seeing!");
    break;
  }

}

void cast_blindness(byte level, struct char_data *ch, char *UNUSED(arg),
                    int type, struct char_data *tar_ch,
                    struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (IS_AFFECTED(tar_ch, AFF_BLIND)) {
      send_to_char("Nothing seems to happen.\n\r", ch);
      return;
    }
    spell_blindness(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    if (IS_AFFECTED(ch, AFF_BLIND))
      return;
    spell_blindness(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    if (IS_AFFECTED(tar_ch, AFF_BLIND))
      return;
    spell_blindness(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    if (IS_AFFECTED(tar_ch, AFF_BLIND))
      return;
    spell_blindness(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(ch, tar_ch))
        if (!(IS_AFFECTED(tar_ch, AFF_BLIND)))
          spell_blindness(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in blindness!");
    break;
  }
}

void cast_light(byte level, struct char_data *ch, char *UNUSED(arg),
                int type, struct char_data *UNUSED(tar_ch),
                struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_light(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    spell_light(level, ch, ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    spell_light(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in light!");
    break;
  }
}

void cast_cont_light(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *UNUSED(tar_ch),
                     struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_cont_light(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    spell_cont_light(level, ch, ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    spell_cont_light(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in continual light!");
    break;
  }
}

void cast_calm(byte level, struct char_data *ch, char *UNUSED(arg), int type,
               struct char_data *tar_ch, struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_calm(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_calm(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_calm(level, ch, ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      spell_calm(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in continual light!");
    break;
  }
}

void cast_web(byte level, struct char_data *ch, char *UNUSED(arg), int type,
              struct char_data *tar_ch, struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_web(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_web(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_web(level, ch, ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(ch, tar_ch))
        spell_web(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in web!");
    break;
  }
}

void cast_clone(byte UNUSED(level), struct char_data *ch, char *UNUSED(arg),
                int UNUSED(type), struct char_data *UNUSED(tar_ch),
                struct obj_data *UNUSED(tar_obj)) {
  send_to_char("Not *YET* implemented.", ch);
  return;
}

void cast_control_weather(byte UNUSED(level), struct char_data *ch, char *arg,
                          int type, struct char_data *UNUSED(tar_ch),
                          struct obj_data *UNUSED(tar_obj)) {
  char buffer[MAX_STRING_LENGTH];
  extern struct weather_data weather_info;

  switch (type) {
  case SPELL_TYPE_SPELL:

    one_argument(arg, buffer);

    if (str_cmp("better", buffer) && str_cmp("worse", buffer)) {
      send_to_char("Do you want it to get better or worse?\n\r", ch);
      return;
    }
    if (!OUTSIDE(ch)) {
      send_to_char("You need to be outside.\n\r", ch);
    }

    if (!str_cmp("better", buffer)) {
      if (weather_info.sky == SKY_CLOUDLESS)
        return;
      if (weather_info.sky == SKY_CLOUDY) {
        send_to_outdoor("The clouds disappear.\n\r");
        weather_info.sky = SKY_CLOUDLESS;
      }
      if (weather_info.sky == SKY_RAINING) {
        if ((time_info.month > 3) && (time_info.month < 14))
          send_to_outdoor("The rain has stopped.\n\r");
        else
          send_to_outdoor("The snow has stopped. \n\r");
        weather_info.sky = SKY_CLOUDY;
      }
      if (weather_info.sky == SKY_LIGHTNING) {
        if ((time_info.month > 3) && (time_info.month < 14))
          send_to_outdoor
            ("The lightning has gone, but it is still raining.\n\r");
        else
          send_to_outdoor
            ("The blizzard is over, but it is still snowing.\n\r");
        weather_info.sky = SKY_RAINING;
      }
      return;
    }
    else {
      if (weather_info.sky == SKY_CLOUDLESS) {
        send_to_outdoor("The sky is getting cloudy.\n\r");
        weather_info.sky = SKY_CLOUDY;
        return;
      }
      if (weather_info.sky == SKY_CLOUDY) {
        if ((time_info.month > 3) && (time_info.month < 14))
          send_to_outdoor("It starts to rain.\n\r");
        else
          send_to_outdoor("It starts to snow. \n\r");
        weather_info.sky = SKY_RAINING;
      }
      if (weather_info.sky == SKY_RAINING) {
        if ((time_info.month > 3) && (time_info.month < 14))
          send_to_outdoor("You are caught in lightning storm.\n\r");
        else
          send_to_outdoor("You are caught in a blizzard. \n\r");
        weather_info.sky = SKY_LIGHTNING;
      }
      if (weather_info.sky == SKY_LIGHTNING) {
        return;
      }

      return;
    }
    break;

  default:
    log_msg("Serious screw-up in control weather!");
    break;
  }
}

void cast_create_food(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    act("$n magically creates a mushroom.", FALSE, ch, 0, 0, TO_ROOM);
    spell_create_food(level, ch, 0, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (tar_ch)
      return;
    spell_create_food(level, ch, 0, 0);
    break;
  default:
    log_msg("Serious screw-up in create food!");
    break;
  }
}

void cast_create_water(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *UNUSED(tar_ch),
                       struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (tar_obj->obj_flags.type_flag != ITEM_DRINKCON) {
      send_to_char("It is unable to hold water.\n\r", ch);
      return;
    }
    spell_create_water(level, ch, 0, tar_obj);
    break;
  default:
    log_msg("Serious screw-up in create water!");
    break;
  }
}

void cast_water_breath(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *tar_ch,
                       struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_water_breath(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_water_breath(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    spell_water_breath(level, ch, tar_ch, 0);
    break;

  default:
    log_msg("Serious screw-up in water breath");
    break;
  }
}

void cast_flying(byte level, struct char_data *ch, char *UNUSED(arg),
                 int type, struct char_data *tar_ch,
                 struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_fly(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_fly(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    spell_fly(level, ch, tar_ch, 0);
    break;

  default:
    log_msg("Serious screw-up in fly");
    break;
  }
}

void cast_fly_group(byte level, struct char_data *ch, char *UNUSED(arg),
                    int type, struct char_data *tar_ch,
                    struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_fly_group(level, ch, 0, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_fly(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in fly");
    break;
  }
}

void cast_heroes_feast(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *UNUSED(tar_ch),
                       struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_heroes_feast(level, ch, 0, 0);
    break;
  default:
    log_msg("Serious screw-up in heroes feast");
    break;
  }
}

void cast_cure_blind(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *tar_ch,
                     struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_cure_blind(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_cure_blind(level, ch, ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_cure_blind(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in cure blind!");
    break;
  }
}

void cast_cure_critic(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_cure_critic(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    spell_cure_critic(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_cure_critic(level, ch, ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_cure_critic(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_cure_critic(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in cure critic!");
    break;

  }
}

void cast_cure_light(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *tar_ch,
                     struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_cure_light(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_cure_light(level, ch, ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_cure_light(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_cure_light(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in cure light!");
    break;
  }
}

void cast_cure_serious(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *tar_ch,
                       struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_cure_serious(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_cure_serious(level, ch, ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_cure_serious(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_cure_serious(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in cure serious!");
    break;
  }
}

void cast_refresh(byte level, struct char_data *ch, char *UNUSED(arg),
                  int type, struct char_data *tar_ch,
                  struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_refresh(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_refresh(level, ch, ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_refresh(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_refresh(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in refresh!");
    break;
  }
}

void cast_second_wind(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_second_wind(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_second_wind(level, ch, ch, 0);
    break;
  case SPELL_TYPE_WAND:

  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_second_wind(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in second_wind!");
    break;
  }
}

void cast_shield(byte level, struct char_data *ch, char *UNUSED(arg),
                 int type, struct char_data *tar_ch,
                 struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_shield(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_shield(level, ch, ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_shield(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_shield(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in shield!");
    break;
  }

}

void cast_curse(byte level, struct char_data *ch, char *UNUSED(arg), int type,
                struct char_data *tar_ch, struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (tar_obj)                /* It is an object */
      spell_curse(level, ch, 0, tar_obj);
    else {                      /* Then it is a PC | NPC */
      spell_curse(level, ch, tar_ch, 0);
    }
    break;
  case SPELL_TYPE_POTION:
    spell_curse(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)                /* It is an object */
      spell_curse(level, ch, 0, tar_obj);
    else {                      /* Then it is a PC | NPC */
      if (!tar_ch)
        tar_ch = ch;
      spell_curse(level, ch, tar_ch, 0);
    }
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)                /* It is an object */
      spell_curse(level, ch, 0, tar_obj);
    else {                      /* Then it is a PC | NPC */
      if (!tar_ch)
        tar_ch = ch;
      spell_curse(level, ch, tar_ch, 0);
    }
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_curse(level, ch, tar_ch, 0);
    break;
  default:
    log_msgf("Serious screw up in curse! Char = %s.", ch->player.name);
    break;
  }
}

void cast_detect_evil(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (affected_by_spell(tar_ch, SPELL_DETECT_EVIL)) {
      send_to_char("Nothing seems to happen.\n\r", tar_ch);
      return;
    }
    spell_detect_evil(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    if (affected_by_spell(ch, SPELL_DETECT_EVIL))
      return;
    spell_detect_evil(level, ch, ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        if (!(IS_AFFECTED(tar_ch, AFF_DETECT_EVIL)))
          spell_detect_evil(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in detect evil!");
    break;
  }
}

void cast_detect_invisibility(byte level, struct char_data *ch,
                              char *UNUSED(arg), int type,
                              struct char_data *tar_ch,
                              struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (IS_AFFECTED(tar_ch, AFF_DETECT_INVISIBLE)) {
      send_to_char("Nothing seems to happen.\n\r", tar_ch);
      return;
    }
    spell_detect_invisibility(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    if (IS_AFFECTED(ch, AFF_DETECT_INVISIBLE))
      return;
    spell_detect_invisibility(level, ch, ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (in_group(ch, tar_ch))
        if (!(IS_AFFECTED(tar_ch, AFF_DETECT_INVISIBLE)))
          spell_detect_invisibility(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in detect invisibility!");
    break;
  }
}

void cast_detect_magic(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *tar_ch,
                       struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (affected_by_spell(tar_ch, SPELL_DETECT_MAGIC)) {
      send_to_char("Nothing seems to happen.\n\r", tar_ch);
      return;
    }
    spell_detect_magic(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    if (affected_by_spell(ch, SPELL_DETECT_MAGIC))
      return;
    spell_detect_magic(level, ch, ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        if (!(IS_AFFECTED(tar_ch, SPELL_DETECT_MAGIC)))
          spell_detect_magic(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in detect magic!");
    break;
  }
}

void cast_detect_poison(byte level, struct char_data *ch, char *UNUSED(arg),
                        int type, struct char_data *tar_ch,
                        struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_detect_poison(level, ch, tar_ch, tar_obj);
    break;
  case SPELL_TYPE_POTION:
    spell_detect_poison(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj) {
      spell_detect_poison(level, ch, 0, tar_obj);
      return;
    }
    if (!tar_ch)
      tar_ch = ch;
    spell_detect_poison(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in detect poison!");
    break;
  }
}

void cast_dispel_evil(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_dispel_evil(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_dispel_evil(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_dispel_evil(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    spell_dispel_evil(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch))
        spell_dispel_evil(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in dispel evil!");
    break;
  }
}

void cast_dispel_good(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_dispel_good(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_dispel_good(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_dispel_good(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    spell_dispel_good(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch))
        spell_dispel_good(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in dispel good!");
    break;
  }
}

void cast_faerie_fire(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_faerie_fire(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_faerie_fire(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_faerie_fire(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    spell_faerie_fire(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch))
        spell_faerie_fire(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in dispel good!");
    break;
  }
}

void cast_enchant_weapon(byte level, struct char_data *ch, char *UNUSED(arg),
                         int type, struct char_data *UNUSED(tar_ch),
                         struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_enchant_weapon(level, ch, 0, tar_obj);
    break;

  case SPELL_TYPE_SCROLL:
    if (!tar_obj)
      return;
    spell_enchant_weapon(level, ch, 0, tar_obj);
    break;
  default:
    log_msg("Serious screw-up in enchant weapon!");
    break;
  }
}

void cast_enchant_armor(byte level, struct char_data *ch, char *UNUSED(arg),
                        int type, struct char_data *UNUSED(tar_ch),
                        struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_enchant_armor(level, ch, 0, tar_obj);
    break;
  case SPELL_TYPE_SCROLL:
    if (!tar_obj)
      return;
    spell_enchant_armor(level, ch, 0, tar_obj);
    break;
  default:
    log_msg("Serious screw-up in enchant armor!");
    break;
  }
}

void cast_heal(byte level, struct char_data *ch, char *UNUSED(arg), int type,
               struct char_data *tar_ch, struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    act("$n heals $N.", FALSE, ch, 0, tar_ch, TO_NOTVICT);
    act("You heal $N.", FALSE, ch, 0, tar_ch, TO_CHAR);
    spell_heal(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_heal(level, ch, ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_heal(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in heal!");
    break;
  }
}

void cast_invisibility(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *tar_ch,
                       struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (tar_obj) {
      if (IS_SET(tar_obj->obj_flags.extra_flags, ITEM_INVISIBLE))
        send_to_char("Nothing new seems to happen.\n\r", ch);
      else
        spell_invisibility(level, ch, 0, tar_obj);
    }
    else {                      /* tar_ch */
      if (IS_AFFECTED(tar_ch, AFF_INVISIBLE))
        send_to_char("Nothing new seems to happen.\n\r", ch);
      else
        spell_invisibility(level, ch, tar_ch, 0);
    }
    break;
  case SPELL_TYPE_POTION:
    if (!IS_AFFECTED(ch, AFF_INVISIBLE))
      spell_invisibility(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj) {
      if (!(IS_SET(tar_obj->obj_flags.extra_flags, ITEM_INVISIBLE)))
        spell_invisibility(level, ch, 0, tar_obj);
    }
    else {                      /* tar_ch */
      if (!tar_ch)
        tar_ch = ch;

      if (!(IS_AFFECTED(tar_ch, AFF_INVISIBLE)))
        spell_invisibility(level, ch, tar_ch, 0);
    }
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj) {
      if (!(IS_SET(tar_obj->obj_flags.extra_flags, ITEM_INVISIBLE)))
        spell_invisibility(level, ch, 0, tar_obj);
    }
    else {                      /* tar_ch */
      if (!(IS_AFFECTED(tar_ch, AFF_INVISIBLE)))
        spell_invisibility(level, ch, tar_ch, 0);
    }
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        if (!(IS_AFFECTED(tar_ch, AFF_INVISIBLE)))
          spell_invisibility(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in invisibility!");
    break;
  }
}

void cast_locate_object(byte level, struct char_data *ch, char *UNUSED(arg),
                        int type, struct char_data *UNUSED(tar_ch),
                        struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_locate_object(level, ch, NULL, tar_obj);
    break;
  default:
    log_msg("Serious screw-up in locate object!");
    break;
  }
}

void cast_poison(byte level, struct char_data *ch, char *UNUSED(arg),
                 int type, struct char_data *tar_ch,
                 struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_WAND:
    spell_poison(level, ch, tar_ch, tar_obj);
    break;
  case SPELL_TYPE_POTION:
    spell_poison(level, ch, ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_poison(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in poison!");
    break;
  }
}

void cast_protection_from_evil(byte level, struct char_data *ch,
                               char *UNUSED(arg), int type,
                               struct char_data *tar_ch,
                               struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_protection_from_evil(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_protection_from_evil(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_protection_from_evil(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_protection_from_evil(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in protection from evil!");
    break;
  }
}

void cast_remove_curse(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *tar_ch,
                       struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_remove_curse(level, ch, tar_ch, tar_obj);
    break;
  case SPELL_TYPE_POTION:
    spell_remove_curse(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj) {
      spell_remove_curse(level, ch, 0, tar_obj);
      return;
    }
    if (!tar_ch)
      tar_ch = ch;
    spell_remove_curse(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_remove_curse(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in remove curse!");
    break;
  }
}

void cast_remove_poison(byte level, struct char_data *ch, char *UNUSED(arg),
                        int type, struct char_data *tar_ch,
                        struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_remove_poison(level, ch, tar_ch, tar_obj);
    break;
  case SPELL_TYPE_POTION:
    spell_remove_poison(level, ch, ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_remove_poison(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in remove poison!");
    break;
  }
}

void cast_remove_paralysis(byte level, struct char_data *ch,
                           char *UNUSED(arg), int type,
                           struct char_data *tar_ch,
                           struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_remove_paralysis(level, ch, tar_ch, tar_obj);
    break;
  case SPELL_TYPE_POTION:
    spell_remove_paralysis(level, ch, ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_remove_paralysis(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_remove_paralysis(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in remove paralysis!");
    break;
  }
}

void cast_sanctuary(byte level, struct char_data *ch, char *UNUSED(arg),
                    int type, struct char_data *tar_ch,
                    struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_sanctuary(level, ch, tar_ch, 0);
    break;

  case SPELL_TYPE_WAND:
  case SPELL_TYPE_POTION:
    spell_sanctuary(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_sanctuary(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_sanctuary(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in sanctuary!");
    break;
  }
}

void cast_fireshield(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *tar_ch,
                     struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_fireshield(level, ch, tar_ch, 0);
    break;

  case SPELL_TYPE_WAND:
  case SPELL_TYPE_POTION:
    spell_fireshield(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_fireshield(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_fireshield(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in fireshield!");
    break;
  }
}

void cast_sleep(byte level, struct char_data *ch, char *UNUSED(arg), int type,
                struct char_data *tar_ch, struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_sleep(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_sleep(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_sleep(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    spell_sleep(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_sleep(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in sleep!");
    break;
  }
}

void cast_strength(byte level, struct char_data *ch, char *UNUSED(arg),
                   int type, struct char_data *tar_ch,
                   struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_SPELL:
    spell_strength(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_strength(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_strength(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_strength(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in strength!");
    break;
  }
}

void cast_ventriloquate(byte UNUSED(level), struct char_data *ch, char *arg,
                        int type, struct char_data *tar_ch,
                        struct obj_data *tar_obj) {
  struct char_data *tmp_ch;
  char buf1[MAX_STRING_LENGTH];
  char buf2[MAX_STRING_LENGTH];
  char buf3[MAX_STRING_LENGTH];

  if (type != SPELL_TYPE_SPELL) {
    log_msg("Attempt to ventriloquate by non-cast-spell.");
    return;
  }
  for (; *arg && (*arg == ' '); arg++);
  if (tar_obj) {
    SPRINTF(buf1, "The %s says '%s'\n\r", fname(tar_obj->name), arg);
    SPRINTF(buf2, "Someone makes it sound like the %s says '%s'.\n\r",
            fname(tar_obj->name), arg);
  }
  else {
    SPRINTF(buf1, "%s says '%s'\n\r", GET_NAME(tar_ch), arg);
    SPRINTF(buf2, "Someone makes it sound like %s says '%s'\n\r",
            GET_NAME(tar_ch), arg);
  }

  SPRINTF(buf3, "Someone says, '%s'\n\r", arg);

  for (tmp_ch = real_roomp(ch->in_room)->people; tmp_ch;
       tmp_ch = tmp_ch->next_in_room) {

    if ((tmp_ch != ch) && (tmp_ch != tar_ch)) {
      if (saves_spell(tmp_ch, SAVING_SPELL))
        send_to_char(buf2, tmp_ch);
      else
        send_to_char(buf1, tmp_ch);
    }
    else {
      if (tmp_ch == tar_ch)
        send_to_char(buf3, tar_ch);
    }
  }
}

void cast_word_of_recall(byte level, struct char_data *ch, char *UNUSED(arg),
                         int type, struct char_data *tar_ch,
                         struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_word_of_recall(level, ch, ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_word_of_recall(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    tar_ch = ch;
    spell_word_of_recall(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    spell_word_of_recall(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_word_of_recall(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in word of recall!");
    break;
  }
}

void cast_summon(byte level, struct char_data *ch, char *UNUSED(arg),
                 int type, struct char_data *tar_ch,
                 struct obj_data *UNUSED(tar_obj)) {
  switch (type) {

  case SPELL_TYPE_SPELL:
    spell_summon(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in summon!");
    break;
  }
}

void cast_charm_person(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *tar_ch,
                       struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_charm_person(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (!tar_ch)
      return;
    spell_charm_person(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch))
        spell_charm_person(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in charm person!");
    break;
  }
}

void cast_charm_monster(byte level, struct char_data *ch, char *UNUSED(arg),
                        int type, struct char_data *tar_ch,
                        struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_charm_monster(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (!tar_ch)
      return;
    spell_charm_monster(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch))
        spell_charm_monster(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in charm monster!");
    break;
  }
}

void cast_sense_life(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *tar_ch,
                     struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_sense_life(level, ch, ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_sense_life(level, ch, ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_sense_life(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in sense life!");
    break;
  }
}

void cast_identify(byte level, struct char_data *ch, char *UNUSED(arg),
                   int type, struct char_data *tar_ch,
                   struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_SCROLL:
    spell_identify(level, ch, tar_ch, tar_obj);
    break;
  default:
    log_msg("Serious screw-up in identify!");
    break;
  }
}

#define MAX_BREATHS 3
struct pbreath {
  int vnum, spell[MAX_BREATHS];
} breath_potions[] = {
  {
    3970, {
  201, 0}}, {
    3971, {
  202, 0}}, {
    3972, {
  203, 0}}, {
    3973, {
  204, 0}}, {
    3974, {
  205, 0}}, {
    0, {
0, 0}},};

void cast_dragon_breath(byte level, struct char_data *ch, char *UNUSED(arg),
                        int UNUSED(type), struct char_data *UNUSED(tar_ch),
                        struct obj_data *potion) {
  struct pbreath *scan;
  int i;
  struct affected_type af;

  if (!potion)
    return;

  for (scan = breath_potions;
       scan->vnum && scan->vnum != obj_index[potion->item_number].virtual;
       scan++);
  if (scan->vnum == 0) {
    send_to_char("Hey, this potion isn't in my list!\n\r", ch);
    log_msgf("unlisted breath potion %s %d", potion->short_description,
             obj_index[potion->item_number].virtual);
    return;
  }

  for (i = 0; i < MAX_BREATHS && scan->spell[i]; i++) {
    if (!affected_by_spell(ch, scan->spell[i])) {
      af.type = scan->spell[i];
      af.duration = 1 + dice(1, 2);
      if (GET_CON(ch) < 4) {
        send_to_char
          ("You are too weak to stomach the potion and spew it all over the floor.\n\r",
           ch);
        act("$n gags and pukes glowing goop all over the floor.", FALSE, ch, 0,
            ch, TO_NOTVICT);
        break;
      }
      if (level > MIN(GET_CON(ch) - 1, get_max_level(ch))) {
        send_to_char
          ("!GACK! You are too weak to handle the full power of the potion.\n\r",
           ch);
        act("$n gags and flops around on the floor a bit.", FALSE, ch, 0, ch,
            TO_NOTVICT);
        level = MIN(GET_CON(ch) - 1, get_max_level(ch));
      }
      af.modifier = -level;
      af.location = APPLY_CON;
      af.bitvector = 0;
      affect_to_char(ch, &af);
      send_to_char("You feel powerful forces build within your stomach...\n\r",
                   ch);
    }
  }
}

void cast_fire_breath(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_fire_breath(level, ch, tar_ch, 0);
    break;                      /* It's a spell.. But people can'c cast it! */
  default:
    log_msg("Serious screw-up in firebreath!");
    break;
  }
}

void cast_frost_breath(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *tar_ch,
                       struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_frost_breath(level, ch, tar_ch, 0);
    break;                      /* It's a spell.. But people can'c cast it! */
  default:
    log_msg("Serious screw-up in frostbreath!");
    break;
  }
}

void cast_acid_breath(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_acid_breath(level, ch, tar_ch, 0);
    break;                      /* It's a spell.. But people can'c cast it! */
  default:
    log_msg("Serious screw-up in acidbreath!");
    break;
  }
}

void cast_gas_breath(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *tar_ch,
                     struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_gas_breath(level, ch, tar_ch, 0);
    break;
    /* THIS ONE HURTS!! */
  default:
    log_msg("Serious screw-up in gasbreath!");
    break;
  }
}

void cast_lightning_breath(byte level, struct char_data *ch,
                           char *UNUSED(arg), int type,
                           struct char_data *tar_ch,
                           struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_lightning_breath(level, ch, tar_ch, 0);
    break;                      /* It's a spell.. But people can'c cast it! */
  default:
    log_msg("Serious screw-up in lightningbreath!");
    break;
  }
}

void cast_knock(byte UNUSED(level), struct char_data *ch, char *arg,
                int type, struct char_data *UNUSED(tar_ch),
                struct obj_data *UNUSED(tar_obj)) {
  int door;
  char dir[MAX_INPUT_LENGTH];
  char otype[MAX_INPUT_LENGTH];
  struct obj_data *obj;
  struct char_data *victim;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:{

      argument_interpreter(arg, otype, dir);

      if (otype[0] == '\0') {
        send_to_char("Knock on what?\n\r", ch);
        return;
      }

      if (generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &victim, &obj)) {
        send_to_char("sorry.. this spell can only be cast on doors\n", ch);
        return;
      }
      else if ((door = find_door(ch, otype, dir)) >= 0) {
        if (!IS_SET(EXIT(ch, door)->exit_info, EX_ISDOOR))
          send_to_char("That's absurd.\n\r", ch);
        else if (!IS_SET(EXIT(ch, door)->exit_info, EX_CLOSED))
          send_to_char("You realize that the door is already open.\n\r", ch);
        else if (EXIT(ch, door)->key < 0)
          send_to_char("You can't seem to spot any lock to pick.\n\r", ch);
        else if (!IS_SET(EXIT(ch, door)->exit_info, EX_LOCKED))
          send_to_char("Oh.. it wasn't locked at all.\n\r", ch);
        else if (IS_SET(EXIT(ch, door)->exit_info, EX_PICKPROOF))
          send_to_char("You seem to be unable to knock this...\n\r", ch);
        else {
          if ((EXIT(ch, door)->keyword) &&
              strcmp("secret", fname(EXIT(ch, door)->keyword)))
            act("$n magically opens the lock of the $F.", 0, ch, 0,
                EXIT(ch, door)->keyword, TO_ROOM);
          else
            act("$n magically opens the lock.", TRUE, ch, 0, 0, TO_ROOM);
          send_to_char("The lock quickly yields to your skills.\n\r", ch);
          raw_unlock_door(ch, EXIT(ch, door), door);

        }
      }
    }
    break;
  default:
    log_msg("serious error in Knock.");
    break;
  }
}

void cast_know_alignment(byte level, struct char_data *ch, char *UNUSED(arg),
                         int type, struct char_data *tar_ch,
                         struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_know_alignment(level, ch, tar_ch, tar_obj);
    break;
  case SPELL_TYPE_POTION:
    spell_know_alignment(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (!tar_ch)
      tar_ch = ch;
    spell_know_alignment(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in know alignment!");
    break;
  }
}

void cast_weakness(byte level, struct char_data *ch, char *UNUSED(arg),
                   int type, struct char_data *tar_ch,
                   struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_SPELL:
    spell_weakness(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_weakness(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_weakness(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch))
        spell_weakness(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in weakness!");
    break;
  }
}

void cast_dispel_magic(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *tar_ch,
                       struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_SPELL:
    spell_dispel_magic(level, ch, tar_ch, tar_obj);
    break;
  case SPELL_TYPE_POTION:
    spell_dispel_magic(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj) {
      spell_dispel_magic(level, ch, 0, tar_obj);
      return;
    }
    if (!tar_ch)
      tar_ch = ch;
    spell_dispel_magic(level, ch, tar_ch, 0);
    break;

  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_dispel_magic(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in dispel magic");
    break;
  }
}

void cast_animate_dead(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *UNUSED(tar_ch),
                       struct obj_data *tar_obj) {
  struct obj_data *i;

  if (no_summon(ch))
    return;

  switch (type) {

  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    if (tar_obj) {
      if (IS_CORPSE(tar_obj)) {
        spell_animate_dead(level, ch, 0, tar_obj);
      }
      else {
        send_to_char("That's not a corpse!\n\r", ch);
        return;
      }
    }
    else {
      send_to_char("That isn't a corpse!\n\r", ch);
      return;
    }
    break;
  case SPELL_TYPE_POTION:
    send_to_char("Your body revolts against the magic liquid.\n\r", ch);
    ch->points.hit = 0;
    break;
  case SPELL_TYPE_STAFF:
    for (i = real_roomp(ch->in_room)->contents; i; i = i->next_content) {
      if (GET_ITEM_TYPE(i) == ITEM_CONTAINER && i->obj_flags.value[3]) {
        spell_animate_dead(level, ch, 0, i);
      }
    }
    break;
  default:
    log_msg("Serious screw-up in animate_dead!");
    break;
  }
}

void cast_succor(byte level, struct char_data *ch, char *UNUSED(arg),
                 int type, struct char_data *UNUSED(tar_ch),
                 struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_succor(level, ch, 0, 0);
  }
}

void cast_paralyze(byte level, struct char_data *ch, char *UNUSED(arg),
                   int type, struct char_data *tar_ch,
                   struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_paralyze(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_paralyze(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_paralyze(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    spell_paralyze(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (tar_ch != ch)
        spell_paralyze(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in paralyze");
    break;
  }
}

void cast_fear(byte level, struct char_data *ch, char *UNUSED(arg), int type,
               struct char_data *tar_ch, struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_fear(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
    spell_fear(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_fear(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_fear(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch))
        spell_fear(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in fear");
    break;
  }
}

void cast_turn(byte level, struct char_data *ch, char *UNUSED(arg),
               int type, struct char_data *tar_ch, struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_turn(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_turn(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_turn(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch))
        spell_turn(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in turn");
    break;
  }
}

void cast_faerie_fog(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *UNUSED(victim),
                     struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_STAFF:
  case SPELL_TYPE_SCROLL:
    spell_faerie_fog(level, ch, 0, 0);
    break;
  default:
    log_msg("Serious screw-up in faerie fog!");
    break;
  }
}

void cast_poly_self(byte level, struct char_data *ch, char *arg, int type,
                    struct char_data *UNUSED(tar_ch),
                    struct obj_data *UNUSED(tar_obj)) {
  char buffer[40];
  int mobn, X = LAST_POLY_MOB, found = FALSE;
  struct char_data *mob;

  one_argument(arg, buffer);

  if (IS_NPC(ch)) {
    send_to_char("You don't really want to do that.\n\r", ch);
    return;
  }

  switch (type) {
  case SPELL_TYPE_SPELL:{

      while (!found) {
        if (PolyList[X].level > level) {
          X--;
        }
        else {
          if (!str_cmp(PolyList[X].name, buffer)) {
            mobn = PolyList[X].number;
            found = TRUE;
          }
          else {
            X--;
          }
          if (X < 0)
            break;
        }
      }

      if (!found) {
        send_to_char("Couldn't find any of those\n\r", ch);
        return;
      }
      else {
        mob = read_mobile(mobn, VIRTUAL);
        if (mob) {
          spell_poly_self(level, ch, mob, 0);
        }
        else {
          send_to_char("You couldn't summon an image of that creature\n\r",
                       ch);
        }
        return;
      }

    }
    break;

  default:{
      log_msg("Problem in poly_self");
    }
    break;
  }

}


#define LONG_SWORD   3022
#define SHIELD       3042
#define CANOE         3061
#define BAG          3032
#define WATER_BARREL 6013
#define BREAD        3010

void cast_minor_creation(byte level, struct char_data *ch, char *arg,
                         int type, struct char_data *UNUSED(tar_ch),
                         struct obj_data *UNUSED(tar_obj)) {
  char buffer[40];
  int obj;
  struct obj_data *o;

  one_argument(arg, buffer);

  if (!str_cmp(buffer, "sword")) {
    obj = LONG_SWORD;
  }
  else if (!str_cmp(buffer, "shield")) {
    obj = SHIELD;
  }
  else if (!str_cmp(buffer, "canoe")) {
    obj = CANOE;
  }
  else if (!str_cmp(buffer, "bag")) {
    obj = BAG;
  }
  else if (!str_cmp(buffer, "barrel")) {
    obj = WATER_BARREL;
  }
  else if (!str_cmp(buffer, "bread")) {
    obj = BREAD;
  }
  else {
    send_to_char("There is nothing of that available\n\r", ch);
    return;
  }

  o = read_object(obj, VIRTUAL);
  if (!o) {
    send_to_char("There is nothing of that available\n\r", ch);
    return;
  }

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
    spell_minor_create(level, ch, 0, o);
    break;
  default:
    log_msg("serious screw-up in minor_create.");
    break;
  }

}

#define FIRE_ELEMENTAL  10
#define WATER_ELEMENTAL 11
#define AIR_ELEMENTAL   12
#define EARTH_ELEMENTAL 13

#define RED_STONE       5233
#define PALE_BLUE_STONE 5230
#define GREY_STONE      5239
#define CLEAR_STONE     5243

void cast_conjure_elemental(byte level, struct char_data *ch, char *arg,
                            int type, struct char_data *UNUSED(tar_ch),
                            struct obj_data *UNUSED(tar_obj)) {
  char buffer[40];
  int mob, obj;
  struct obj_data *sac;
  struct char_data *el;


  one_argument(arg, buffer);

  if (no_summon(ch))
    return;

  if (!str_cmp(buffer, "fire")) {
    mob = FIRE_ELEMENTAL;
    obj = RED_STONE;
  }
  else if (!str_cmp(buffer, "water")) {
    mob = WATER_ELEMENTAL;
    obj = PALE_BLUE_STONE;
  }
  else if (!str_cmp(buffer, "air")) {
    mob = AIR_ELEMENTAL;
    obj = CLEAR_STONE;
  }
  else if (!str_cmp(buffer, "earth")) {
    mob = EARTH_ELEMENTAL;
    obj = GREY_STONE;
  }
  else {
    send_to_char("There are no elementals of that type available\n\r", ch);
    return;
  }
  if (!ch->equipment[HOLD]) {
    send_to_char(" You must be holding the correct stone\n\r", ch);
    return;
  }

  sac = unequip_char(ch, HOLD);
  if (sac) {
    obj_to_char(sac, ch);
    if (obj_vnum(sac) != obj) {
      send_to_char("You must have the correct item to sacrifice.\n\r", ch);
      return;
    }
    el = read_mobile(mob, VIRTUAL);
    if (!el) {
      send_to_char("There are no elementals of that type available\n\r", ch);
      return;
    }
  }
  else {
    send_to_char("You must be holding the correct item to sacrifice.\n\r", ch);
    return;
  }

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
    spell_conjure_elemental(level, ch, el, sac);
    break;
  default:
    log_msg("serious screw-up in conjure_elemental.");
    break;
  }

}

#define DEMON_TYPE_I     20
#define DEMON_TYPE_II    21
#define DEMON_TYPE_III   22
#define DEMON_TYPE_IV    23
#define DEMON_TYPE_V     24
#define DEMON_TYPE_VI    25

#define TYPE_VI_ITEM     27002
#define TYPE_V_ITEM      5107
#define TYPE_IV_ITEM     5113
#define TYPE_III_ITEM    1101
#define TYPE_II_ITEM     21014
#define TYPE_I_ITEM      5105

void cast_cacaodemon(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *UNUSED(tar_ch),
                     struct obj_data *UNUSED(tar_obj)) {
  char buffer[40];
  int mob, obj;
  struct obj_data *sac;
  struct char_data *el;


  one_argument(arg, buffer);

  if (no_summon(ch))
    return;

  if (!str_cmp(buffer, "one")) {
    mob = DEMON_TYPE_I;
    obj = TYPE_I_ITEM;
  }
  else if (!str_cmp(buffer, "two")) {
    mob = DEMON_TYPE_II;
    obj = TYPE_II_ITEM;
  }
  else if (!str_cmp(buffer, "three")) {
    mob = DEMON_TYPE_III;
    obj = TYPE_III_ITEM;
  }
  else if (!str_cmp(buffer, "four")) {
    mob = DEMON_TYPE_IV;
    obj = TYPE_IV_ITEM;
  }
  else if (!str_cmp(buffer, "five")) {
    mob = DEMON_TYPE_V;
    obj = TYPE_V_ITEM;
  }
  else if (!str_cmp(buffer, "six")) {
    mob = DEMON_TYPE_VI;
    obj = TYPE_VI_ITEM;
  }
  else {
    send_to_char("There are no demons of that type available\n\r", ch);
    return;
  }
  if (!ch->equipment[WIELD]) {
    send_to_char(" You must be wielding the correct item\n\r", ch);
    return;
  }

  if (obj_index[ch->equipment[WIELD]->item_number].virtual != obj) {
    send_to_char(" You must be wielding the correct item\n\r", ch);
    return;
  }

  sac = unequip_char(ch, WIELD);
  if (sac) {
    obj_to_char(sac, ch);
    if (obj_vnum(sac) != obj) {
      send_to_char("You must have the correct item to sacrifice.\n\r", ch);
      return;
    }
    el = read_mobile(mob, VIRTUAL);
    if (!el) {
      send_to_char("There are no demons of that type available\n\r", ch);
      return;
    }
  }
  else {
    send_to_char("You must be holding the correct item to sacrifice.\n\r", ch);
    return;
  }

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
    spell_cacaodemon(level, ch, el, sac);
    break;
  default:
    log_msg("serious screw-up in cacaodemon.");
    break;
  }

}

void cast_mon_sum1(byte UNUSED(level), struct char_data *ch,
                   char *UNUSED(arg), int type,
                   struct char_data *UNUSED(tar_ch),
                   struct obj_data *UNUSED(tar_obj)) {
  if (no_summon(ch))
    return;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_create_monster(5, ch, 0, 0);
    break;
  default:
    log_msg("Serious screw-up in monster_summoning_1");
    break;
  }
}

void cast_mon_sum2(byte UNUSED(level), struct char_data *ch,
                   char *UNUSED(arg), int type,
                   struct char_data *UNUSED(tar_ch),
                   struct obj_data *UNUSED(tar_obj)) {
  if (no_summon(ch))
    return;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_create_monster(7, ch, 0, 0);
    break;
  default:
    log_msg("Serious screw-up in monster_summoning_1");
    break;
  }
}

void cast_mon_sum3(byte UNUSED(level), struct char_data *ch,
                   char *UNUSED(arg), int type,
                   struct char_data *UNUSED(tar_ch),
                   struct obj_data *UNUSED(tar_obj)) {
  if (no_summon(ch))
    return;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_create_monster(9, ch, 0, 0);
    break;
  default:
    log_msg("Serious screw-up in monster_summoning_1");
    break;
  }
}

void cast_mon_sum4(byte UNUSED(level), struct char_data *ch,
                   char *UNUSED(arg), int type,
                   struct char_data *UNUSED(tar_ch),
                   struct obj_data *UNUSED(tar_obj)) {
  if (no_summon(ch))
    return;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_create_monster(11, ch, 0, 0);
    break;
  default:
    log_msg("Serious screw-up in monster_summoning_1");
    break;
  }
}

void cast_mon_sum5(byte UNUSED(level), struct char_data *ch,
                   char *UNUSED(arg), int type,
                   struct char_data *UNUSED(tar_ch),
                   struct obj_data *UNUSED(tar_obj)) {
  if (no_summon(ch))
    return;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_create_monster(13, ch, 0, 0);
    break;
  default:
    log_msg("Serious screw-up in monster_summoning_1");
    break;
  }
}

void cast_mon_sum6(byte UNUSED(level), struct char_data *ch,
                   char *UNUSED(arg), int type,
                   struct char_data *UNUSED(tar_ch),
                   struct obj_data *UNUSED(tar_obj)) {
  if (no_summon(ch))
    return;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_create_monster(15, ch, 0, 0);
    break;
  default:
    log_msg("Serious screw-up in monster_summoning_1");
    break;
  }
}

void cast_mon_sum7(byte UNUSED(level), struct char_data *ch,
                   char *UNUSED(arg), int type,
                   struct char_data *UNUSED(tar_ch),
                   struct obj_data *UNUSED(tar_obj)) {
  if (no_summon(ch))
    return;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_create_monster(17, ch, 0, 0);
    break;
  default:
    log_msg("Serious screw-up in monster_summoning_1");
    break;
  }
}


void cast_tree_travel(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *UNUSED(tar_ch),
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_tree_travel(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in tree travel");
    break;
  }
}

void cast_speak_with_plants(byte level, struct char_data *ch,
                            char *UNUSED(arg), int type,
                            struct char_data *UNUSED(tar_ch),
                            struct obj_data *tar_obj) {
  if (!tar_obj)
    return;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    spell_speak_with_plants(level, ch, 0, tar_obj);
    break;
  default:
    log_msg("Serious screw-up in speak_with_plants");
    break;
  }
}

void cast_transport_via_plant(byte level, struct char_data *ch,
                              char *UNUSED(arg), int type,
                              struct char_data *UNUSED(tar_ch),
                              struct obj_data *tar_obj) {
  if (!tar_obj)
    return;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
    spell_transport_via_plant(level, ch, 0, tar_obj);
    break;
  default:
    log_msg("Serious screw-up in transport_via_plant");
    break;
  }
}

void cast_haste(byte level, struct char_data *ch, char *UNUSED(arg),
                int type, struct char_data *tar_ch, struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_haste(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_haste(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_haste(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch))
        spell_haste(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in haste");
    break;
  }
}

void cast_slow(byte level, struct char_data *ch, char *UNUSED(arg),
               int type, struct char_data *tar_ch, struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_slow(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_slow(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_WAND:
    if (tar_obj)
      return;
    if (!tar_ch)
      tar_ch = ch;
    spell_slow(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch))
        spell_slow(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in slow");
    break;
  }
}

void cast_reincarnate(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *UNUSED(tar_ch),
                      struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    if (!tar_obj)
      return;
    spell_reincarnate(level, ch, 0, tar_obj);
    break;
  case SPELL_TYPE_STAFF:
    if (!tar_obj)
      return;
    spell_reincarnate(level, ch, 0, tar_obj);
    break;
  default:
    log_msg("Serious problem in 'reincarnate'");
    break;
  }

}

void cast_changestaff(byte level, struct char_data *ch, char *arg,
                      int type, struct char_data *UNUSED(tar_ch),
                      struct obj_data *UNUSED(tar_obj)) {
  char buffer[40];

  one_argument(arg, buffer);

  if (no_summon(ch))
    return;

  if (!ch->equipment[HOLD]) {
    send_to_char(" You must be holding a staff!\n\r", ch);
    return;
  }

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_STAFF:
    spell_changestaff(level, ch, 0, 0);
    break;
  default:
    log_msg("serious screw-up in changestaff.");
    break;
  }

}

void cast_pword_kill(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *tar_ch,
                     struct obj_data *UNUSED(tar_obj)) {

  if (!tar_ch)
    tar_ch = ch;
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
    spell_pword_kill(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in pword_kill.");
    break;
  }

}

void cast_pword_blind(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *UNUSED(tar_obj)) {
  if (!tar_ch)
    tar_ch = ch;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
    spell_pword_blind(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in pword_blind.");
    break;
  }
}

void cast_chain_lightn(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *tar_ch,
                       struct obj_data *UNUSED(tar_obj)) {

  if (!tar_ch)
    tar_ch = ch;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_chain_lightn(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in chain lightn.");
    break;
  }
}

void cast_scare(byte level, struct char_data *ch, char *UNUSED(arg),
                int type, struct char_data *tar_ch,
                struct obj_data *UNUSED(tar_obj)) {
  if (!tar_ch)
    tar_ch = ch;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_scare(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in scare.");
    break;
  }
}

void cast_familiar(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch,
                   struct obj_data *UNUSED(tar_obj)) {
  char buf[128];

  if (no_summon(ch))
    return;

  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_familiar(level, ch, &tar_ch, 0);

    if (tar_ch) {
      SPRINTF(buf, "%s %s", GET_NAME(tar_ch), fname(arg));
      free(GET_NAME(tar_ch));
      GET_NAME(tar_ch) = (char *)malloc(strlen(buf) + 1);
      strcpy(GET_NAME(tar_ch), buf);
    }
    break;
  default:
    log_msg("serious screw-up in familiar.");
    break;
  }
}

void cast_aid(byte level, struct char_data *ch, char *UNUSED(arg),
              int type, struct char_data *tar_ch,
              struct obj_data *UNUSED(tar_obj)) {
  if (!tar_ch)
    tar_ch = ch;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_aid(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in scare.");
    break;
  }
}

void cast_holyword(byte level, struct char_data *ch, char *UNUSED(arg),
                   int type, struct char_data *UNUSED(tar_ch),
                   struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
    spell_holy_word(level, ch, 0, 0);
    break;
  default:
    log_msg("serious screw-up in holy word.");
    break;
  }
}

void cast_golem(byte level, struct char_data *ch, char *UNUSED(arg),
                int type, struct char_data *UNUSED(tar_ch),
                struct obj_data *UNUSED(tar_obj)) {
  if (no_summon(ch))
    return;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
    spell_golem(level, ch, 0, 0);
    break;
  default:
    log_msg("serious screw-up in golem.");
    break;
  }
}

void cast_command(byte UNUSED(level), struct char_data *ch, char *arg,
                  int type, struct char_data *tar_ch,
                  struct obj_data *UNUSED(tar_obj)) {
  char *p;
  char buf[128];
  /* have to parse the argument to get the command */


  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
    break;
  default:
    log_msg("serious screw-up in command.");
    return;
    break;
  }

  for (; *arg == ' '; arg++);

  if (arg && *arg) {
    p = fname(arg);

    if (((get_max_level(tar_ch) < 6) && (GET_INT(tar_ch) < 13)) ||
        !saves_spell(tar_ch, SAVING_PARA)) {

      if (strcmp(p, "quit")) {
        SPRINTF(buf, "$n has commanded you to '%s'.", p);
        act(buf, FALSE, ch, 0, tar_ch, TO_VICT);
        send_to_char("Ok.\n\r", ch);
        command_interpreter(tar_ch, p);
        return;
      }
    }

    SPRINTF(buf, "$n just tried to command you to '%s'.", p);
    act(buf, FALSE, ch, 0, tar_ch, TO_VICT);

    if (!IS_PC(tar_ch))
      hit(tar_ch, ch, TYPE_UNDEFINED);

  }
  else
    return;

}

void cast_shillelagh(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *UNUSED(tar_ch),
                     struct obj_data *tar_obj) {

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
    spell_shillelagh(level, ch, ch, tar_obj);
    break;
  default:
    log_msg("serious screw-up in shillelagh.");
    break;
  }
}

void cast_goodberry(byte level, struct char_data *ch, char *UNUSED(arg),
                    int type, struct char_data *UNUSED(tar_ch),
                    struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
    spell_goodberry(level, ch, ch, 0);
    break;
  default:
    log_msg("serious screw-up in goodberry.");
    break;
  }
}

void cast_flame_blade(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *UNUSED(tar_ch),
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
    spell_flame_blade(level, ch, ch, 0);
    break;
  default:
    log_msg("serious screw-up in flame blade.");
    break;
  }
}

void cast_animal_growth(byte level, struct char_data *ch, char *UNUSED(arg),
                        int type, struct char_data *tar_ch,
                        struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    spell_animal_growth(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in animal_growth.");
    break;
  }
}

void cast_insect_growth(byte level, struct char_data *ch, char *UNUSED(arg),
                        int type, struct char_data *tar_ch,
                        struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    spell_insect_growth(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in insect_growth.");
    break;
  }
}

void cast_creeping_death(byte level, struct char_data *ch, char *arg,
                         int type, struct char_data *UNUSED(tar_ch),
                         struct obj_data *UNUSED(tar_obj)) {
  char *p;
  int i;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:

    /* get the argument, parse it into a direction */
    for (; *arg == ' '; arg++);
    if (!*arg) {
      send_to_char("you must supply a direction!\n\r", ch);
      return;
    }
    p = fname(arg);
    for (i = 0; i < 6; i++) {
      if (strncmp(p, dirs[i], strlen(p)) == 0) {
        break;
      }
      if (i == 6) {
        send_to_char("you must supply a direction!\n\r", ch);
        return;
      }
    }

    spell_creeping_death(level, ch, 0, i);
    break;
  default:
    log_msg("serious screw-up in creeping_death.");
    break;
  }
}

void cast_commune(byte level, struct char_data *ch, char *UNUSED(arg),
                  int type, struct char_data *UNUSED(tar_ch),
                  struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
    spell_commune(level, ch, 0, 0);
    break;
  default:
    log_msg("serious screw-up in commune.");
    break;
  }
}

void cast_feeblemind(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *tar_ch,
                     struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_POTION:
    spell_feeblemind(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_feeblemind(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in commune.");
    break;
  }
}

void cast_animal_summon_1(byte UNUSED(level), struct char_data *ch,
                          char *UNUSED(arg), int type,
                          struct char_data *UNUSED(tar_ch),
                          struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_POTION:
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_animal_summon(1, ch, 0, 0);
    break;
  default:
    log_msg("serious screw-up in animal summon.");
    break;
  }
}

void cast_animal_summon_2(byte UNUSED(level), struct char_data *ch,
                          char *UNUSED(arg), int type,
                          struct char_data *UNUSED(tar_ch),
                          struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_POTION:
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_animal_summon(2, ch, 0, 0);
    break;
  default:
    log_msg("serious screw-up in animal summon.");
    break;
  }
}

void cast_animal_summon_3(byte UNUSED(level), struct char_data *ch,
                          char *UNUSED(arg), int type,
                          struct char_data *UNUSED(tar_ch),
                          struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_POTION:
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_animal_summon(3, ch, 0, 0);
    break;
  default:
    log_msg("serious screw-up in animal summon.");
    break;
  }
}

void cast_fire_servant(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *UNUSED(tar_ch),
                       struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_STAFF:
    spell_elemental_summoning(level, ch, 0, SPELL_FIRE_SERVANT);
    break;
  default:
    log_msg("serious screw-up in fire servant.");
    break;
  }
}

void cast_earth_servant(byte level, struct char_data *ch, char *UNUSED(arg),
                        int type, struct char_data *UNUSED(tar_ch),
                        struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_STAFF:
    spell_elemental_summoning(level, ch, 0, SPELL_EARTH_SERVANT);
    break;
  default:
    log_msg("serious screw-up in earth servant.");
    break;
  }
}

void cast_water_servant(byte level, struct char_data *ch, char *UNUSED(arg),
                        int type, struct char_data *UNUSED(tar_ch),
                        struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_STAFF:
    spell_elemental_summoning(level, ch, 0, SPELL_WATER_SERVANT);
    break;
  default:
    log_msg("serious screw-up in water servant.");
    break;
  }
}

void cast_wind_servant(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *UNUSED(tar_ch),
                       struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_STAFF:
    spell_elemental_summoning(level, ch, 0, SPELL_WIND_SERVANT);
    break;
  default:
    log_msg("serious screw-up in wind servant.");
    break;
  }
}

void cast_veggie_growth(byte level, struct char_data *ch, char *UNUSED(arg),
                        int type, struct char_data *tar_ch,
                        struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    spell_veggie_growth(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in veggie_growth.");
    break;
  }
}


void cast_charm_veggie(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *tar_ch,
                       struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_charm_veggie(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_SCROLL:
    if (!tar_ch)
      return;
    spell_charm_veggie(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch))
        spell_charm_veggie(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("Serious screw-up in charm veggie!");
    break;
  }
}

void cast_tree(byte level, struct char_data *ch, char *UNUSED(arg), int type,
               struct char_data *UNUSED(tar_ch),
               struct obj_data *UNUSED(tar_obj)) {
  if (no_summon(ch))
    return;

  if (IS_NPC(ch))
    return;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_POTION:
  case SPELL_TYPE_STAFF:
    spell_tree(level, ch, 0, 0);
    break;
  default:
    log_msg("Serious screw-up in tree");
    break;
  }
}

void cast_animate_rock(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *UNUSED(tar_ch),
                       struct obj_data *tar_obj) {
  if (no_summon(ch))
    return;

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    spell_animate_rock(level, ch, 0, tar_obj);
    break;
  default:
    log_msg("serious screw-up in animate_rock.");
    break;
  }
}

void cast_travelling(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *UNUSED(tar_ch),
                     struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_POTION:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_travelling(level, ch, ch, 0);
    break;
  default:
    log_msg("serious screw-up in travelling.");
    break;
  }
}

void cast_animal_friendship(byte level, struct char_data *ch,
                            char *UNUSED(arg), int type,
                            struct char_data *tar_ch,
                            struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    spell_animal_friendship(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in animal friendship.");
    break;
  }
}

void cast_invis_to_animals(byte level, struct char_data *ch,
                           char *UNUSED(arg), int type,
                           struct char_data *UNUSED(tar_ch),
                           struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_POTION:
    spell_invis_to_animals(level, ch, ch, 0);
    break;
  default:
    log_msg("serious screw-up in invis to animals.");
    break;
  }
}

void cast_slow_poison(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_POTION:
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_slow_poison(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in slow_poison.");
    break;
  }
}

void cast_entangle(byte level, struct char_data *ch, char *UNUSED(arg),
                   int type, struct char_data *tar_ch,
                   struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_entangle(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch) && !IS_IMMORTAL(tar_ch))
        spell_entangle(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in entangle.");
    break;
  }
}

void cast_snare(byte level, struct char_data *ch, char *UNUSED(arg),
                int type, struct char_data *tar_ch,
                struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_snare(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch) && !IS_IMMORTAL(tar_ch))
        spell_snare(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in snare.");
    break;
  }
}

void cast_gust_of_wind(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *UNUSED(tar_ch),
                       struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_gust_of_wind(level, ch, 0, 0);
    break;
  default:
    log_msg("serious screw-up in snare.");
    break;
  }
}


void cast_barkskin(byte level, struct char_data *ch, char *UNUSED(arg),
                   int type, struct char_data *tar_ch,
                   struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_barkskin(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch))
        spell_barkskin(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in barkskin.");
    break;
  }
}

void cast_warp_weapon(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *tar_ch,
                      struct obj_data *tar_obj) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_warp_weapon(level, ch, tar_ch, tar_obj);
    break;
  default:
    log_msg("serious screw-up in warp_weapon.");
    break;
  }
}

void cast_heat_stuff(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *tar_ch,
                     struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_heat_stuff(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in heat_stuff.");
    break;
  }
}

void cast_sunray(byte level, struct char_data *ch, char *UNUSED(arg),
                 int type, struct char_data *tar_ch,
                 struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_sunray(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in sunray.");
    break;
  }
}

void cast_find_traps(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *tar_ch,
                     struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    spell_find_traps(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_POTION:
  case SPELL_TYPE_STAFF:
    spell_find_traps(level, ch, ch, 0);
    break;
  default:
    log_msg("serious screw-up in find_traps.");
    break;
  }
}

void cast_firestorm(byte level, struct char_data *ch, char *UNUSED(arg),
                    int type, struct char_data *UNUSED(tar_ch),
                    struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_STAFF:
    spell_firestorm(level, ch, 0, 0);
    break;
  default:
    log_msg("serious screw-up in firestorm.");
    break;
  }
}

void cast_dust_devil(byte level, struct char_data *ch, char *UNUSED(arg),
                     int type, struct char_data *UNUSED(tar_ch),
                     struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_STAFF:
    spell_dust_devil(level, ch, 0, 0);
    break;
  default:
    log_msg("serious screw-up in dust_devil.");
    break;
  }
}

void cast_know_monster(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *tar_ch,
                       struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      return;
    spell_know_monster(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in know_monster.");
    break;
  }
}

void cast_silence(byte level, struct char_data *ch, char *UNUSED(arg),
                  int type, struct char_data *tar_ch,
                  struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_POTION:
    spell_silence(level, ch, ch, 0);
    break;
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
    if (!tar_ch)
      tar_ch = ch;
    spell_silence(level, ch, tar_ch, 0);
    break;
  case SPELL_TYPE_STAFF:
    for (tar_ch = real_roomp(ch->in_room)->people;
         tar_ch; tar_ch = tar_ch->next_in_room)
      if (!in_group(tar_ch, ch) && !IS_IMMORTAL(tar_ch))
        spell_silence(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in silence.");
    break;
  }
}

void cast_dragon_ride(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *UNUSED(tar_ch),
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_POTION:
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_STAFF:
    spell_dragon_ride(level, ch, ch, 0);
    break;
  default:
    log_msg("serious screw-up in dragon_ride.");
    break;
  }
}

void cast_mount(byte level, struct char_data *ch, char *UNUSED(arg),
                int type, struct char_data *UNUSED(tar_ch),
                struct obj_data *UNUSED(tar_obj)) {

  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_STAFF:
    spell_mount(level, ch, ch, 0);
    break;
  default:
    log_msg("serious screw-up in mount.");
    break;
  }
}

void cast_sending(byte UNUSED(level), struct char_data *ch, char *arg,
                  int type, struct char_data *tar_ch,
                  struct obj_data *UNUSED(tar_obj)) {
  char buf[512];

  switch (type) {
  case SPELL_TYPE_SPELL:
    for (; *arg == ' '; arg++);
    SPRINTF(buf, "$n sends you a mystic message: %s", arg);
    act(buf, TRUE, ch, 0, tar_ch, TO_VICT);
    SPRINTF(buf, "You send $N the message: %s", arg);
    act(buf, TRUE, ch, 0, tar_ch, TO_CHAR);
    break;
  default:
    log_msg("serious screw-up in sending");
    break;

  }
}

void cast_portal(byte level, struct char_data *ch, char *UNUSED(arg),
                 int type, struct char_data *tar_ch,
                 struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_STAFF:
    if (!tar_ch)
      tar_ch = ch;
    spell_portal(level, ch, tar_ch, 0);
    break;
  default:
    log_msg("serious screw-up in portal");
    break;

  }
}

void cast_teleport_wo_error(byte level, struct char_data *ch,
                            char *UNUSED(arg), int type,
                            struct char_data *tar_ch,
                            struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_WAND:
  case SPELL_TYPE_SCROLL:
  case SPELL_TYPE_POTION:
  case SPELL_TYPE_SPELL:

    if (!tar_ch)
      send_to_char("Yes, but who do you wish to teleport to?\n", ch);
    else
      spell_astral_walk(level, ch, tar_ch, 0);
    break;

  default:
    log_msg("Serious screw-up in teleport without error!");
    break;
  }
}


#define THORN 1111

void cast_thorn_spray(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *victim,
                      struct obj_data *UNUSED(tar_obj)) {
  struct obj_data *component;

  switch (type) {
  case SPELL_TYPE_SPELL:

    if (!ch->equipment[HOLD]) {
      send_to_char("You must be holding a thorn.\n\r", ch);
      return;
    }

    component = unequip_char(ch, HOLD);

    if (component) {
      obj_to_char(component, ch);
      if (obj_vnum(component) != THORN) {
        send_to_char("You aint holdin no thorn!\n\r", ch);
        return;
      }
      else {                    /* they must have a thorn */
        spell_thorn_spray(level, ch, victim, component);
      }
    }
    else {
      send_to_char("You must hold the correct item to cast the spell.\n\r",
                   ch);
    }
    break;
  default:
    log_msg("Serious screw-up in thorn spray!");
    break;
  }
}

void cast_resist_hold(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *UNUSED(tar_ch),
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_resist_hold(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in resist_hold!");
    break;
  }
}

void cast_resist_electricity(byte level, struct char_data *ch,
                             char *UNUSED(arg), int type,
                             struct char_data *UNUSED(tar_ch),
                             struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_resist_electricity(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in resist_electricity!");
    break;
  }
}

void cast_resist_cold(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *UNUSED(tar_ch),
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_resist_cold(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in resist_cold!");
    break;
  }
}

void cast_resist_drain(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *UNUSED(tar_ch),
                       struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_resist_drain(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in resist_drain!");
    break;
  }
}

void cast_resist_poison(byte level, struct char_data *ch, char *UNUSED(arg),
                        int type, struct char_data *UNUSED(tar_ch),
                        struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_resist_poison(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in resist_poison!");
    break;
  }
}

void cast_resist_acid(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *UNUSED(tar_ch),
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_resist_acid(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in resist_acid!");
    break;
  }
}

void cast_resist_fire(byte level, struct char_data *ch, char *UNUSED(arg),
                      int type, struct char_data *UNUSED(tar_ch),
                      struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_resist_fire(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in resist_fire!");
    break;
  }
}

void cast_resist_energy(byte level, struct char_data *ch, char *UNUSED(arg),
                        int type, struct char_data *UNUSED(tar_ch),
                        struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_resist_energy(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in resist_energy!");
    break;
  }
}

void cast_resist_pierce(byte level, struct char_data *ch, char *UNUSED(arg),
                        int type, struct char_data *UNUSED(tar_ch),
                        struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_resist_pierce(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in resist_pierce!");
    break;
  }
}

void cast_resist_slash(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *UNUSED(tar_ch),
                       struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_resist_slash(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in resist_slash!");
    break;
  }
}

void cast_resist_blunt(byte level, struct char_data *ch, char *UNUSED(arg),
                       int type, struct char_data *UNUSED(tar_ch),
                       struct obj_data *UNUSED(tar_obj)) {
  switch (type) {
  case SPELL_TYPE_SPELL:
    spell_resist_blunt(level, ch, ch, 0);
    break;
  default:
    log_msg("Serious screw-up in resist_blunt!");
    break;
  }
}
