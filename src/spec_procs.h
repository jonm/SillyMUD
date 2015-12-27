#ifndef SPEC_PROCS_H
#define SPEC_PROCS_H

int dump(struct char_data *ch, const char *cmd, char *arg,
         struct room_data *rp, int type);
int pet_shops(struct char_data *ch, const char *cmd, char *arg,
              struct room_data *rp, int type);
int fountain(struct char_data *ch, const char *cmd, char *arg,
             struct room_data *rp, int type);
int bank(struct char_data *ch, const char *cmd, char *arg,
         struct room_data *rp, int type);
int pray_for_items(struct char_data *ch, const char *cmd, char *arg,
                   struct room_data *rp, int type);
int donation(struct char_data *ch, const char *cmd, char *arg,
             struct room_data *rp, int type);
int magic__fountain(struct char_data *ch, const char *cmd, char *arg,
                    struct room_data *rp, int type);

int puff(struct char_data *ch, const char *cmd, char *arg,
         struct char_data *mob, int type);
int ringwraith(struct char_data *ch, const char *cmd, char *arg,
               struct char_data *mob, int type);
int tormentor(struct char_data *ch, const char *cmd, char *arg,
              struct char_data *mob, int type);
int mage_guild_master(struct char_data *ch, const char *cmd, char *arg,
                      struct char_data *mob, int type);
int cleric_guild_master(struct char_data *ch, const char *cmd, char *arg,
                        struct char_data *mob, int type);
int thief_guild_master(struct char_data *ch, const char *cmd, char *arg,
                       struct char_data *mob, int type);
int warrior_guild_master(struct char_data *ch, const char *cmd, char *arg,
                         struct char_data *mob, int type);
int guildmaster(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type, int class);
int mayor(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
          int type);
int andy_wilcox(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);
struct char_data *find_mobile_here_with_spec_proc(int (*fcn) (), int rnumber);
int eric_johnson(struct char_data *ch, const char *cmd, char *arg,
                 struct char_data *mob, int type);
void exec_social(struct char_data *npc, char *cmd, int next_line,
                 int *cur_line, void **thing);
void npc_steal(struct char_data *ch, struct char_data *victim);
int snake(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
          int type);
int midgaard_cityguard(struct char_data *ch, const char *cmd, char *arg,
                       struct char_data *mob, int type);
int paladin_guild_guard(struct char_data *ch, const char *cmd, char *arg,
                        struct char_data *mob, int type);
int game_guard(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
               int type);
int grey_paramedic(struct char_data *ch, const char *cmd, char *arg,
                   struct char_data *mob, int types);
int amber_paramedic(struct char_data *ch, const char *cmd, char *arg,
                    struct char_data *mob, int type);
int blink(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
          int type);
int midgaard_citizen(struct char_data *ch, const char *cmd, char *arg,
                     struct char_data *mob, int type);
int ghoul(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
          int type);
int carrion_crawler(struct char_data *ch, const char *cmd, char *arg,
                    struct char_data *mob, int type);
int wizard_guard(struct char_data *ch, const char *cmd, char *arg,
                 struct char_data *mob, int type);
int vampire(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
            int type);
int wraith(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
           int type);
int shadow(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
           int type);
int geyser(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
           int type);
int green_slime(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);
int drow(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
         int type);
int thief(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
          int type);
int guild_guard(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);
int inquisitor(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
               int type);
int regenerator(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);
int replicant(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob1,
              int type);
int tytan(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
          int type);
int abbarach_dragon(struct char_data *ch, const char *cmd, char *arg,
                    struct char_data *mob, int type);
int fido(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
         int type);
int janitor(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
            int type);
int rust_monster(struct char_data *ch, const char *cmd, char *arg,
                 struct char_data *mob, int type);
int temple_labrynth_liar(struct char_data *ch, const char *cmd, char *arg,
                         struct char_data *mob, int type);
int temple_labrynth_sentry(struct char_data *ch, const char *cmd, char *arg,
                           struct char_data *mob, int type);
int whirlwind(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
              int type);
int nudge_nudge(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);
int AGGRESSIVE(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
               int type);
int citizen(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
            int type);
int warren_guard(struct char_data *ch, const char *cmd, char *arg,
                 struct char_data *mob, int type);
int zm_tired(struct char_data *zmaster);
int zm_stunned_followers(struct char_data *zmaster);
void zm_init_combat(struct char_data *zmaster, struct char_data *target);
int zm_kill_fidos(struct char_data *zmaster);
int zm_kill_aggressor(struct char_data *zmaster);
int zombie_master(struct char_data *ch, const char *cmd, char *arg,
                  struct char_data *mob, int type);
int chalice(struct char_data *ch, const char *cmd, char *arg);
int kings_hall(struct char_data *ch, const char *cmd, char *arg);
int house(struct char_data *ch, const char *cmd, char *arg, struct room_data *rp,
          int type);
int sisyphus(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
             int type);
int jabberwocky(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);
int flame(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
          int type);
int banana(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
           int type);
int paramedics(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
               int type);
int jugglernaut(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);
int delivery_elf(struct char_data *ch, const char *cmd, char *arg,
                 struct char_data *mob, int type);
int delivery_beast(struct char_data *ch, const char *cmd, char *arg,
                   struct char_data *mob, int type);
int keftab(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
           int type);
int storm_giant(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);
int fighter(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
            int type);
int new_thalos_mayor(struct char_data *ch, const char *cmd, char *arg,
                     struct char_data *mob, int type);
int sultan_guard(struct char_data *ch, const char *cmd, char *arg,
                 struct char_data *mob, int type);
int new_thalos_citizen(struct char_data *ch, const char *cmd, char *arg,
                       struct char_data *mob, int type);
int new_thalos_guild_guard(struct char_data *ch, const char *cmd, char *arg,
                           struct char_data *mob, int type);
int magic_user2(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);
int mord_guard(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
               int type);
int mord_guild_guard(struct char_data *ch, const char *cmd, char *arg,
                     struct char_data *mob, int type);
int caravan_guild_guard(struct char_data *ch, const char *cmd, char *arg,
                        struct char_data *mob, int type);
int stat_teller(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);
void throw_char(struct char_data *ch, struct char_data *v, int dir);
int thrower_mob(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);
int tyrannosaurus_swallower(struct char_data *ch, const char *cmd, char *arg,
                            struct char_data *mob, int type);
int soap(struct char_data *ch, const char *cmd, char *arg, struct obj_data *tobj,
         int type);
int nodrop(struct char_data *ch, const char *cmd, char *arg, struct obj_data *tobj,
           int type);
int lattimore(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
              int type);
int coldcaster(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
               int type);
int trapper(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
            int type);
int trogcook(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
             int type);
int shaman(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
           int type);
int golgar(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
           int type);
int troguard(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
             int type);
int ghostsoldier(struct char_data *ch, const char *cmd, char *arg,
                 struct char_data *mob, int type);
int valik(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
          int type);
int guardian(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
             int type);
int keystone(struct char_data *ch, const char *cmd, char *arg,
             struct char_data *mob, int type);
int web_slinger(struct char_data *ch, const char *cmd, char *arg,
                struct char_data *mob, int type);

int citizen(struct char_data *, const char *, char *, struct char_data *, int);

struct char_data *find_mob_in_room_with_function(int room, mob_func *func);
#endif
