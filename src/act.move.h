#ifndef _ACT_MOVE_H
#define _ACT_MOVE_H

#define MOVE_DIR_NORTH 0
#define MOVE_DIR_EAST 1
#define MOVE_DIR_SOUTH 2
#define MOVE_DIR_WEST 3
#define MOVE_DIR_UP 4
#define MOVE_DIR_DOWN 5

#define MOVE_DIR_FIRST 0
#define MOVE_DIR_LAST 5

#define MOVE_DIR_INVALID -1

extern const char *move_dir_string[];

void move_to_dir(struct char_data *ch, int dir);
int move_string_to_dir(const char *str);

void do_move(struct char_data *ch, char *argument, const char *cmd);
void do_enter(struct char_data *ch, char *argument, const char *cmd);
void do_open(struct char_data *ch, char *argument, const char * cmd);
void do_close(struct char_data *ch, char *argument, const char * cmd);
void do_lock(struct char_data *ch, char *argument, const char * cmd);
void do_unlock(struct char_data *ch, char *argument, const char * cmd);
void do_pick(struct char_data *ch, char *argument, const char * cmd);
void do_leave(struct char_data *ch, char *argument, const char * cmd);
void do_stand(struct char_data *ch, char *argument, const char * cmd);
void do_sit(struct char_data *ch, char *argument, const char * cmd);
void do_rest(struct char_data *ch, char *argument, const char * cmd);
void do_sleep(struct char_data *ch, char *argument, const char * cmd);
void do_wake(struct char_data *ch, char *argument, const char * cmd);
void do_follow(struct char_data *ch, char *argument, const char * cmd);
void do_walk(struct char_data *ch, char *argument, const char * cmd);
void do_fly(struct char_data *ch, char *argument, const char * cmd);

#define stand(ch) do_stand((ch), "", "stand")
#define wake_other(ch, wakee) do_wake((ch), (wakee), "wake")
#define wake_self(ch) do_wake((ch), "", "wake")

#endif /* _ACT_MOVE_H */
