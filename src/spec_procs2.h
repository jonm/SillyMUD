#ifndef SPEC_PROCS2_H
#define SPEC_PROCS2_H

int druid_challenge_prep_room(struct char_data *ch, const char *cmd, char *arg,
                              struct room_data *rp, int type);
int druid_challenge_room(struct char_data *ch, const char *cmd, char *arg,
                         struct room_data *rp, int type);
int monk_challenge_room(struct char_data *ch, const char *cmd, char *arg,
                        struct room_data *rp, int type);
int monk_challenge_prep_room(struct char_data *ch, const char *cmd, char *arg,
                             struct room_data *rp, int type);

int ghost(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
          int type);
int druid_protector(struct char_data *ch, const char *cmd, char *arg,
                    struct char_data *mob, int type);
int druid_attack_spells(struct char_data *ch, struct char_data *vict,
                        int level);
int summoner(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
             int type);
int monk(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
         int type);
int jive_box(struct char_data *ch, const char *cmd, char *arg, struct obj_data *obj,
             int type);
int magic_user(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
               int type);
int cleric(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
           int type);
int ninja_master(struct char_data *ch, const char *cmd, char *arg,
                 struct char_data *mob, int type);
int ettin(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
          int type);
int repair_guy(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
               int type);
int samah(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
          int type);
int bitter_blade(struct char_data *ch, const char *cmd, char *arg,
                 struct obj_data *tobj, int type);
int make_quest(struct char_data *ch, struct char_data *gm, int Class,
               char *arg, const char *cmd);
int abyss_gate_keeper(struct char_data *ch, const char *cmd, char *arg,
                      struct char_data *mob, int type);
int creeping_death(struct char_data *ch, const char *cmd, char *arg,
                   struct char_data *mob, int type);
void submit(struct char_data *ch, struct char_data *t);
void say_hello(struct char_data *ch, struct char_data *t);
void greet_people(struct char_data *ch);
int generic_cityguardHateUndead(struct char_data *ch, const char *cmd, char *arg,
                                struct char_data *mob, int type);
int generic_cityguard(struct char_data *ch, const char *cmd, char *arg,
                      struct char_data *mob, int type);
int prydain_guard(struct char_data *ch, const char *cmd, char *arg,
                  struct char_data *mob, int type);
struct breath_victim *choose_victims(struct char_data *ch,
                                     struct char_data *first_victim);
void free_victims(struct breath_victim *head);
void breath_weapon(struct char_data *ch, struct char_data *target,
                   int mana_cost, breath_weapon_func *func);
void use_breath_weapon(struct char_data *ch, struct char_data *target,
                       int cost, breath_weapon_func *func);
int breath_weapon_mob(struct char_data *ch, const char *cmd, char *arg,
                      struct char_data *mob, int type);
int sailor(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
           int type);
int loremaster(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
               int type);
int hunter(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
           int type);
int monk_master(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);
int druid_guild_master(struct char_data *ch, const char *cmd, char *arg,
                       struct char_data *mob, int type);
int teacher(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
            int type, int teacher, char *say_str);
int devil(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
          int type);
int demon(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
          int type);
void druid_heal(struct char_data *ch, int level);
void druid_tree(struct char_data *ch);
void druid_mob(struct char_data *ch);
int druid_challenger(struct char_data *ch, const char *cmd, char *arg,
                     struct char_data *mob, int type);
int monk_challenger(struct char_data *ch, const char *cmd, char *arg,
                    struct char_data *mob, int type);
int portal(struct char_data *ch, const char *cmd, char *arg, struct obj_data *obj,
           int type);
int scraps(struct char_data *ch, const char *cmd, char *arg, struct obj_data *obj,
           int type);
int attack_rats(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);
int dragon_hunter_leader(struct char_data *ch, const char *cmd, char *arg,
                         struct char_data *mob, int type);
int hunting_mercenary(struct char_data *ch, const char *cmd, char *arg,
                      struct char_data *mob, int type);
int slot_machine(struct char_data *ch, const char *cmd, char *arg,
                 struct obj_data *obj, int type);
int astral_portal(struct char_data *ch, const char *cmd, char *arg,
                  struct char_data *mob, int type);
int dwarven_miners(struct char_data *ch, const char *cmd, char *arg,
                   struct char_data *mob, int type);
int real_rabbit(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);
int real_fox(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
             int type);
int antioch_grenade(struct char_data *ch, const char *cmd, char *arg,
                    struct obj_data *obj, int type);

#endif
