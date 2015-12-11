#ifndef _ACT_LOOK_H
#define _ACT_LOOK_H

void do_exits(struct char_data *ch, char *argument, const char *cmd);
void do_look(struct char_data *ch, char *argument, const char * cmd);
void do_read(struct char_data *ch, char *argument, const char *cmd);
void do_examine(struct char_data *ch, char *argument, const char * cmd);
void do_score(struct char_data *ch, char *argument, const char * cmd);
void do_time(struct char_data *ch, char *argument, const char * cmd);
void do_weather(struct char_data *ch, char *argument, const char * cmd);
void do_help(struct char_data *ch, char *argument, const char * cmd);
void do_wizhelp(struct char_data *ch, char *arg, const char * cmd);
void do_who(struct char_data *ch, char *argument, const char * cmd);
void do_users(struct char_data *ch, char *argument, const char * cmd);
void do_inventory(struct char_data *ch, char *argument, const char * cmd);
void do_equipment(struct char_data *ch, char *argument, const char * cmd);
void do_news(struct char_data *ch, char *argument, const char * cmd);
void do_info(struct char_data *ch, char *argument, const char * cmd);
void do_wizlist(struct char_data *ch, char *argument, const char * cmd);
void do_where(struct char_data *ch, char *argument, const char * cmd);
void do_levels(struct char_data *ch, char *argument, const char * cmd);
void do_consider(struct char_data *ch, char *argument, const char * cmd);
void do_spells(struct char_data *ch, char *argument, const char * cmd);
void do_world(struct char_data *ch, char *argument, const char * cmd);
void do_attribute(struct char_data *ch, char *argument, const char * cmd);
void do_value(struct char_data *ch, char *argument, const char * cmd);
void do_display(struct char_data *ch, char *arg, const char * cmd);
void do_resize(struct char_data *ch, char *arg, const char * cmd);
void do_report(struct char_data *ch, char *argument, const char * cmd);
void do_credits(struct char_data *ch, char *argument, const char * cmd);


#define look_room(ch) do_look((ch), "", "look")
#define look_at(ch, at) do_look((ch), (at), "look")

#endif /* ifdef _ACT_LOOK_H */
