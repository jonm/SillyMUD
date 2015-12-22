/*
  SillyMUD Distribution V1.1b             (c) 1993 SillyMUD Developement
 
  See license.doc for distribution terms.   SillyMUD is based on DIKUMUD
*/

#ifndef _UTILS_H
#define _UTILS_H

#include "config.h"

#if DEBUG

#define free(obj) log_msgf("freeing %d\n", sizeof(*obj));\
		      free(obj)

#endif

#define TRUE  1

#define FALSE 0

#define LOWER(c) (((c)>='A'  && (c) <= 'Z') ? ((c)+('a'-'A')) : (c))

#define UPPER(c) (((c)>='a'  && (c) <= 'z') ? ((c)+('A'-'a')) : (c) )

#define ISNEWL(ch) ((ch) == '\n' || (ch) == '\r')

#define IS_WEAPON(o) (o->obj_flags.type_flag == ITEM_WEAPON)

#define IF_STR(st) ((st) ? (st) : "\0")

#define CAP(st)  (*(st) = UPPER(*(st)), st)

#define CAPITALIZE(st) (*(st) = UPPER(*(st)))

#define CREATE(result, type, number)  do {\
	if (!((result) = (type *) calloc ((number), sizeof(type))))\
		{ perror("malloc failure"); abort(); }\
		} while(0)

#define RECREATE(result,type,number) do {\
  if (!((result) = (type *) realloc ((result), sizeof(type) * (number))))\
		{ perror("realloc failure"); abort(); } \
		} while(0)


#define IS_SET(flag,bit)  ((flag) & (bit))


#define SWITCH(a,b) { (a) ^= (b); \
                      (b) ^= (a); \
                      (a) ^= (b); }

#define IS_AFFECTED(ch,skill)  (IS_SET((ch)->specials.affected_by, (skill)))
#define IS_AFFECTED2(ch,skill) (IS_SET((ch)->specials.affected_by2,(skill)))
#define IS_INTRINSIC(ch,skill) (IS_SET((ch)->specials.intrinsics,(skill)))

#define IS_DARK(room) (real_roomp(room)->light <= 0 && \
	((IS_SET(real_roomp(room)->room_flags, DARK)) ||  \
	 is_dark_outside(real_roomp(room))))

#define IS_LIGHT(room) (real_roomp(room)->light>0 || \
	 (!IS_SET(real_roomp(room)->room_flags, DARK) || \
	  !is_dark_outside(real_roomp(room))))

#define SET_BIT(var,bit)  ((var) = (var) | (bit))

#define REMOVE_BIT(var,bit)  ((var) = (var) & ~(bit) )

#define RM_FLAGS(i)  ((real_roomp(i))?real_roomp(i)->room_flags:0)

#define GET_LEVEL(ch, i)   ((ch)->player.level[(i)])

#define GET_CLASS_TITLE(ch, class, lev)   ((ch)->player.sex ?  \
    (((ch)->player.sex == 1) ? titles[(class)][(int)(lev)].title_m : \
    titles[(class)][(int)(lev)].title_f) : titles[(class)][(int)(lev)].title_m)

#define GET_REQ(i) (i<2  ? "Awful" :(i<4  ? "Bad"     :(i<7  ? "Poor"      :\
(i<10 ? "Average" :(i<14 ? "Fair"    :(i<20 ? "Good"    :(i<24 ? "Very good" :\
        "Superb" )))))))

#define HSHR(ch) ((ch)->player.sex ?					\
	(((ch)->player.sex == 1) ? "his" : "her") : "its")

#define HSSH(ch) ((ch)->player.sex ?					\
	(((ch)->player.sex == 1) ? "he" : "she") : "it")

#define HMHR(ch) ((ch)->player.sex ? 					\
	(((ch)->player.sex == 1) ? "him" : "her") : "it")

#define ANA(obj) (index("aeiouyAEIOUY", *(obj)->name) ? "An" : "A")

#define SANA(obj) (index("aeiouyAEIOUY", *(obj)->name) ? "an" : "a")

#define IS_NPC(ch)  (IS_SET((ch)->specials.act, ACT_ISNPC))

#define IS_MOB(ch)  (IS_SET((ch)->specials.act, ACT_ISNPC) && ((ch)->nr >-1))

#define GET_POS(ch)     ((ch)->specials.position)

#define GET_COND(ch, i) ((ch)->specials.conditions[(i)])

#define GET_NAME(ch)    ((ch)->player.name)

#define GET_TITLE(ch)   ((ch)->player.title)

#define GET_CLASS(ch)   ((ch)->player.class)

#define GET_HOME(ch)	((ch)->player.hometown)

#define GET_AGE(ch)     (age(ch).year)

#define GET_STR(ch)     ((ch)->tmpabilities.str)

#define GET_ADD(ch)     ((ch)->tmpabilities.str_add)

#define GET_DEX(ch)     ((ch)->tmpabilities.dex)

#define GET_INT(ch)     ((ch)->tmpabilities.intel)

#define GET_WIS(ch)     ((ch)->tmpabilities.wis)

#define GET_CON(ch)     ((ch)->tmpabilities.con)

#define GET_CHR(ch)     ((ch)->tmpabilities.chr)


#define GET_RSTR(ch)     ((ch)->abilities.str)

#define GET_RADD(ch)     ((ch)->abilities.str_add)

#define GET_RDEX(ch)     ((ch)->abilities.dex)

#define GET_RINT(ch)     ((ch)->abilities.intel)

#define GET_RWIS(ch)     ((ch)->abilities.wis)

#define GET_RCON(ch)     ((ch)->abilities.con)

#define GET_RCHR(ch)     ((ch)->abilities.chr)

#define STRENGTH_APPLY_INDEX(ch) \
        ( ((GET_ADD(ch)==0) || (GET_STR(ch) != 18)) ? GET_STR(ch) :\
          (GET_ADD(ch) <= 50) ? 26 :( \
          (GET_ADD(ch) <= 75) ? 27 :( \
          (GET_ADD(ch) <= 90) ? 28 :( \
          (GET_ADD(ch) <= 99) ? 29 :  30 ) ) )                   \
        )

#define GET_AC(ch)      ((ch)->points.armor)

#define GET_HIT(ch)     ((ch)->points.hit)

#define GET_MAX_HIT(ch) (hit_limit(ch))

#define GET_MOVE(ch)    ((ch)->points.move)

#define GET_MAX_MOVE(ch) (move_limit(ch))

#define GET_MANA(ch)    ((ch)->points.mana)

#define GET_MAX_MANA(ch) (mana_limit(ch))

#define GET_GOLD(ch)    ((ch)->points.gold)

#define GET_BANK(ch)    ((ch)->points.bankgold)

#define GET_ZONE(ch)    ((ch)->specials.permissions)

#define GET_EXP(ch)     ((ch)->points.exp)

#define GET_HEIGHT(ch)  ((ch)->player.height)

#define GET_WEIGHT(ch)  ((ch)->player.weight)

#define GET_SEX(ch)     ((ch)->player.sex)

#define GET_RACE(ch)     ((ch)->race)

#define GET_HITROLL(ch) ((ch)->points.hitroll)

#define GET_DAMROLL(ch) ((ch)->points.damroll)

#define AWAKE(ch) (GET_POS(ch) > POSITION_SLEEPING && \
		   !IS_AFFECTED(ch, AFF_PARALYSIS) )

#define WAIT_STATE(ch, cycle)  (((ch)->desc) ? (ch)->desc->wait = ((get_max_level(ch) >= DEMIGOD) ? (0) : (cycle)) : 0)

/* Object And Carry related macros */

#define GET_ITEM_TYPE(obj) ((obj)->obj_flags.type_flag)

#define CAN_WEAR(obj, part) (IS_SET((obj)->obj_flags.wear_flags,part))

#define GET_OBJ_WEIGHT(obj) ((obj)->obj_flags.weight)

#define CAN_CARRY_W(ch) (str_app[STRENGTH_APPLY_INDEX(ch)].carry_w)

#define CAN_CARRY_N(ch) (5+GET_DEX(ch)/2+get_max_level(ch)/2)

#define IS_CARRYING_W(ch) ((ch)->specials.carry_weight)

#define IS_CARRYING_N(ch) ((ch)->specials.carry_items)

#define CAN_CARRY_OBJ(ch,obj)  \
   (((IS_CARRYING_W(ch) + GET_OBJ_WEIGHT(obj)) <= CAN_CARRY_W(ch)) &&   \
    ((IS_CARRYING_N(ch) + 1) <= CAN_CARRY_N(ch)))

#define CAN_GET_OBJ(ch, obj)   \
   (CAN_WEAR((obj), ITEM_TAKE) && CAN_CARRY_OBJ((ch),(obj)) &&          \
    CAN_SEE_OBJ((ch),(obj)))

#define IS_OBJ_STAT(obj,stat) (IS_SET((obj)->obj_flags.extra_flags,stat))



/* char name/short_desc(for mobs) or someone?  */

#define PERS(ch, vict)   (                                          \
	CAN_SEE(vict, ch) ?						                                    \
	  (!IS_NPC(ch) ? (ch)->player.name : (ch)->player.short_descr) :	\
	  "someone")

#define OBJS(obj, vict) (CAN_SEE_OBJ((vict), (obj)) ? \
	(obj)->short_description  : "something")

#define OBJN(obj, vict) (CAN_SEE_OBJ((vict), (obj)) ? \
	fname((obj)->name) : "something")

#define OUTSIDE(ch) (!IS_SET(real_roomp((ch)->in_room)->room_flags,INDOORS) &&\
                     (real_roomp(ch->in_room)->sector_type != SECT_INSIDE) && \
                     (real_roomp(ch->in_room)->sector_type != SECT_UNDERWATER))

#define IS_IMMORTAL(ch) (!IS_NPC(ch)&&(get_max_level(ch)>=LOW_IMMORTAL))

#define IS_POLICE(ch) ((mob_index[ch->nr].virtual == 3060) || \
                       (mob_index[ch->nr].virtual == 3069) || \
                       (mob_index[ch->nr].virtual == 3067))

#define IS_CORPSE(obj) (GET_ITEM_TYPE((obj))==ITEM_CONTAINER && \
			(obj)->obj_flags.value[3] && \
			isname("corpse", (obj)->name))

#define EXIT(ch, door)  (real_roomp((ch)->in_room)->dir_option[door])

#define CAN_GO(ch, door) (EXIT(ch,door)&&real_roomp(EXIT(ch,door)->to_room) \
                          && !IS_SET(EXIT(ch, door)->exit_info, EX_CLOSED))

#define CAN_GO_HUMAN(ch, door) (EXIT(ch,door) && \
			  real_roomp(EXIT(ch,door)->to_room) \
                          && !IS_SET(EXIT(ch, door)->exit_info, EX_LOCKED))

#define GET_ALIGNMENT(ch) ((ch)->specials.alignment)

#define IS_GOOD(ch)    (GET_ALIGNMENT(ch) >= 350)
#define IS_EVIL(ch)    (GET_ALIGNMENT(ch) <= -350)
#define IS_NEUTRAL(ch) (!IS_GOOD(ch) && !IS_EVIL(ch))

#define ITEM_TYPE(obj)  ((int)(obj)->obj_flags.type_flag)

#define IS_PC(ch) (!IS_NPC((ch)) || IS_SET((ch)->specials.act, ACT_POLYSELF))


#define GET_AVE_LEVEL(ch) (get_max_level(ch)+(get_sec_max_lev(ch)/2)+\
	  (get_third_max_lev(ch)/3))

#define GET_ALIAS(ch, num) ((ch)->specials.A_list->com[(num)])

#define MOUNTED(ch) ((ch)->specials.mounted_on)
#define RIDDEN(ch) ((ch)->specials.ridden_by)

#define GET_VALUE(obj) ((obj)->obj_flags.cost)
#define GET_RENT(obj) ((obj)->obj_flags.cost_per_day)

#define SUNPROBLEM(ch) (GET_RACE(ch) == RACE_DROW || GET_RACE(ch) == \
			RACE_MFLAYER)

#endif

#define SPRINTF(str, ...)                       \
  (sizeof(str) > SIZEOF_VOID_P ?                \
   snprintf(str, sizeof(str), __VA_ARGS__) :    \
   sprintf(str, __VA_ARGS__))

#define SAPPENDF(str, ...)                                          \
  snprintf(str+strlen(str), sizeof(str)-strlen(str) - 1, __VA_ARGS__)

#define STREQ(a, b) (a && b && !strcmp(a, b))

