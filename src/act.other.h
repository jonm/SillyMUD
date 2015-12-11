#ifndef ACT_OTHER_H
#define ACT_OTHER_H

void do_gain(struct char_data *ch, char *argument, const char * cmd);
void do_guard(struct char_data *ch, char *argument, const char * cmd);
void do_qui(struct char_data *ch, char *argument, const char * cmd);
void do_title(struct char_data *ch, char *argument, const char * cmd);
void do_quit(struct char_data *ch, char *argument, const char * cmd);
void do_save(struct char_data *ch, char *argument, const char * cmd);
void do_not_here(struct char_data *ch, char *argument, const char * cmd);
void do_sneak(struct char_data *ch, char *argument, const char * cmd);
void do_hide(struct char_data *ch, char *argument, const char * cmd);
void do_steal(struct char_data *ch, char *argument, const char * cmd);
void do_junk(struct char_data *ch, char *argument, const char * cmd);
void do_practice(struct char_data *ch, char *arg, const char *cmd);
void do_idea(struct char_data *ch, char *argument, const char * cmd);
void do_typo(struct char_data *ch, char *argument, const char * cmd);
void do_bug(struct char_data *ch, char *argument, const char * cmd);
void do_brief(struct char_data *ch, char *argument, const char * cmd);
void do_compact(struct char_data *ch, char *argument, const char * cmd);
void do_group(struct char_data *ch, char *argument, const char * cmd);
void do_quaff(struct char_data *ch, char *argument, const char * cmd);
void do_recite(struct char_data *ch, char *argument, const char * cmd);
void do_use(struct char_data *ch, char *argument, const char * cmd);
void do_plr_noshout(struct char_data *ch, char *argument, const char * cmd);
void do_show_exits(struct char_data *ch, char *argument, const char * cmd);
void do_alias(struct char_data *ch, char *arg, const char *cmd);
void do_mount(struct char_data *ch, char *arg, const char *cmd);
void do_split(struct char_data *ch, char *arg, const char * cmd);
void do_gname(struct char_data *ch, char *arg, const char * cmd);
void do_donate(struct char_data *ch, char *argument, const char * cmd);
void do_auto(struct char_data *ch, char *argument, const char * cmd);
void do_prompt(struct char_data *ch, char *argument, const char * cmd);

void dismount(struct char_data *ch, struct char_data *h, int pos);

#endif
