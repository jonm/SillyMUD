#ifndef SPEC_PROCS3_H
#define SPEC_PROCS3_H

int entering_turbo_lift(struct char_data *ch, const char *cmd, char *arg,
                        struct room_data *rp, int type);
int turbo_lift(struct char_data *ch, const char *cmd, char *arg,
               struct room_data *rp, int type);

#endif
