/*
  SillyMUD Distribution V1.1b             (c) 1993 SillyMUD Developement
 
  See license.doc for distribution terms.   SillyMUD is based on DIKUMUD
*/


/*
**  0 = Mage, 1 = cleric, 3 = thief, 2 = fighter
*/

/*
**  
*/
#include "config.h"

#include <stdio.h>
#include <string.h>

#include "protos.h"
#include "utility.h"


/* extern variables */

extern struct room_data *world;
extern struct descriptor_data *descriptor_list;
extern struct room_data *world;
extern struct dex_app_type dex_app[];



int get_class_level(struct char_data *ch, int class) {

  if (IS_SET(ch->player.class, class)) {
    return (GET_LEVEL(ch, count_bits(class) - 1));
  }
  return (0);
}

int count_bits(int class) {

  if (class == 1)
    return (1);
  if (class == 2)
    return (2);
  if (class == 4)
    return (3);
  if (class == 8)
    return (4);
  if (class == 16)
    return (5);
  if (class == 32)
    return (6);
  return (0);
}

int only_class(struct char_data *ch, int class) {
  int i;

  for (i = 1; i <= 32; i *= 2) {
    if (get_class_level(ch, i) != 0)
      if (i != class)
        return (FALSE);
  }
  return (TRUE);

}


int has_class(struct char_data *ch, int class) {

  if (!IS_PC(ch)) {
    if (!IS_SET(class, CLASS_MONK)) {
      return (TRUE);
    }
  }

  if (IS_SET(ch->player.class, class))
    return (TRUE);

  return FALSE;
}

int how_many_classes(struct char_data *ch) {
  short i, tot = 0;

  for (i = 0; i < MAX_CLASS; i++) {
    if (GET_LEVEL(ch, i)) {
      tot++;
    }
  }
  if (tot)
    return (tot);
  else {
    if (IS_SET(ch->player.class, CLASS_MAGIC_USER))
      tot++;

    if (IS_SET(ch->player.class, CLASS_WARRIOR))
      tot++;

    if (IS_SET(ch->player.class, CLASS_THIEF))
      tot++;

    if (IS_SET(ch->player.class, CLASS_CLERIC))
      tot++;

    if (IS_SET(ch->player.class, CLASS_DRUID))
      tot++;

    if (IS_SET(ch->player.class, CLASS_MONK))
      tot++;

  }
  return (tot);
}


int best_fighting_class(struct char_data *ch) {

  if (GET_LEVEL(ch, WARRIOR_LEVEL_IND))
    return (WARRIOR_LEVEL_IND);
  if (GET_LEVEL(ch, CLERIC_LEVEL_IND))
    return (CLERIC_LEVEL_IND);
  if (GET_LEVEL(ch, DRUID_LEVEL_IND))
    return (DRUID_LEVEL_IND);
  if (GET_LEVEL(ch, MONK_LEVEL_IND))
    return (MONK_LEVEL_IND);
  if (GET_LEVEL(ch, THIEF_LEVEL_IND))
    return (THIEF_LEVEL_IND);
  if (GET_LEVEL(ch, MAGE_LEVEL_IND))
    return (MAGE_LEVEL_IND);

  log_msgf("Massive error.. character has no recognized class.: %s",
           GET_NAME(ch));
  assert(0);

  return (1);
}

int best_thief_class(struct char_data *ch) {

  if (GET_LEVEL(ch, THIEF_LEVEL_IND))
    return (THIEF_LEVEL_IND);
  if (GET_LEVEL(ch, MONK_LEVEL_IND))
    return (MONK_LEVEL_IND);
  if (GET_LEVEL(ch, MAGE_LEVEL_IND))
    return (MAGE_LEVEL_IND);
  if (GET_LEVEL(ch, WARRIOR_LEVEL_IND))
    return (WARRIOR_LEVEL_IND);
  if (GET_LEVEL(ch, DRUID_LEVEL_IND))
    return (DRUID_LEVEL_IND);
  if (GET_LEVEL(ch, CLERIC_LEVEL_IND))
    return (CLERIC_LEVEL_IND);

  log_msgf("Massive error.. character has no recognized class.: %s",
           GET_NAME(ch));
  assert(0);

  return (1);
}

int best_magic_class(struct char_data *ch) {

  if (GET_LEVEL(ch, MAGE_LEVEL_IND))
    return (MAGE_LEVEL_IND);
  if (GET_LEVEL(ch, DRUID_LEVEL_IND))
    return (DRUID_LEVEL_IND);
  if (GET_LEVEL(ch, CLERIC_LEVEL_IND))
    return (CLERIC_LEVEL_IND);
  if (GET_LEVEL(ch, THIEF_LEVEL_IND))
    return (THIEF_LEVEL_IND);
  if (GET_LEVEL(ch, WARRIOR_LEVEL_IND))
    return (WARRIOR_LEVEL_IND);
  if (GET_LEVEL(ch, MONK_LEVEL_IND))
    return (MONK_LEVEL_IND);

  log_msgf("Massive error.. character has no recognized class.: %s", 
           GET_NAME(ch));
  ch->player.class = 4;

  return (1);
}

int get_sec_max_lev(struct char_data *ch) {
  return (get_a_level(ch, 2));
}

int get_a_level(struct char_data *ch, int which) {
  byte ind[MAX_CLASS], k;
  int i, j;

  for (i = 0; i < MAX_CLASS; i++) {
    ind[i] = GET_LEVEL(ch, i);
  }

/*
 *  chintzy sort. (just to prove that I did learn something in college)
 */

  for (i = 0; i < MAX_CLASS - 1; i++) {
    for (j = i + 1; j < MAX_CLASS; j++) {
      if (ind[j] > ind[i]) {
        k = ind[i];
        ind[i] = ind[j];
        ind[j] = k;
      }
    }
  }

  if (which > -1 && which < 4) {
    return (ind[which]);
  }
  return (1);
}

int get_third_max_lev(struct char_data *ch) {
  return (get_a_level(ch, 3));
}

int get_max_level(struct char_data *ch) {
  register int max = 0, i;

  for (i = 0; i <= MAX_CLASS; i++) {
    if (GET_LEVEL(ch, i) > max)
      max = GET_LEVEL(ch, i);
  }

  return (max);
}

int get_tot_level(struct char_data *ch) {
  int max = 0, i;

  for (i = 0; i < MAX_CLASS; i++)
    max += GET_LEVEL(ch, i);

  return (max);

}

void start_levels(struct char_data *ch) {

  if (IS_SET(ch->player.class, CLASS_MAGIC_USER)) {
    advance_level(ch, MAGE_LEVEL_IND);
  }
  if (IS_SET(ch->player.class, CLASS_CLERIC)) {
    advance_level(ch, CLERIC_LEVEL_IND);
  }
  if (IS_SET(ch->player.class, CLASS_WARRIOR)) {
    advance_level(ch, WARRIOR_LEVEL_IND);
  }
  if (IS_SET(ch->player.class, CLASS_THIEF)) {
    advance_level(ch, THIEF_LEVEL_IND);
  }
  if (IS_SET(ch->player.class, CLASS_DRUID)) {
    advance_level(ch, DRUID_LEVEL_IND);
  }
  if (IS_SET(ch->player.class, CLASS_MONK)) {
    advance_level(ch, MONK_LEVEL_IND);
  }

  if (GET_RACE(ch) == RACE_OGRE)
    ch->specials.spells_to_learn = 2;
  else
    ch->specials.spells_to_learn = 4;   /* we are generous. */

}


int best_class(struct char_data *ch) {
  int max = 0, class = 0, i;

  for (i = 0; i < MAX_CLASS; i++)
    if (max < GET_LEVEL(ch, i)) {
      max = GET_LEVEL(ch, i);
      class = i;
    }

  class = 1 << class;           /* perhaps this will work properly */

  assert(max > 0);
  return (class);

}
