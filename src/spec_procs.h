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


#endif
