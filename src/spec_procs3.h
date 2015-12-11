#ifndef SPEC_PROCS3_H
#define SPEC_PROCS3_H

int entering_turbo_lift(struct char_data *ch, const char *cmd, char *arg,
                        struct room_data *rp, int type);
int turbo_lift(struct char_data *ch, const char *cmd, char *arg,
               struct room_data *rp, int type);
int chess_game(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
               int type);
int acid_blob(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
              int type);
int baby_bear(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
              int type);
int timnus(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
           int type);
int winger(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
           int type);
int death_room(int dt_room);
int youth_potion(struct char_data *ch, const char *cmd, char *arg,
                 struct obj_data *mob, int type);
int warpstone(struct char_data *ch, const char *cmd, char *arg, struct obj_data *mob,
              int type);
int old_hag(struct char_data *ch, const char *cmd, char *arg, struct char_data *mob,
            int type);
int death_knight(struct char_data *ch, const char *cmd, char *arg,
                 struct char_data *mob, int type);

#endif
