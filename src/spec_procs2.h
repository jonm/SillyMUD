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


#endif
