#ifndef ACT_OBJ2_H
#define ACT_OBJ2_H

void do_drink(struct char_data *ch, char *argument, const char *cmd);
void do_eat(struct char_data *ch, char *argument, const char * cmd);
void do_wear(struct char_data *ch, char *argument, const char* cmd);
void do_wield(struct char_data *ch, char *argument, const char *cmd);
void do_grab(struct char_data *ch, char *argument, const char *cmd);
void do_remove(struct char_data *ch, char *argument, const char *cmd);
void do_pour(struct char_data *ch, char *argument, const char * UNUSED(cmd));
void do_sip(struct char_data *ch, char *argument, const char * UNUSED(cmd));
void do_taste(struct char_data *ch, char *argument, const char * UNUSED(cmd));

#endif
