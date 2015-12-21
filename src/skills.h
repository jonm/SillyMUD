#ifndef _SKILLS_H
#define _SKILLS_H

void disarm_action(struct char_data *ch, char *argument, int npc_ok);

void do_palm(struct char_data *ch, char *arg, const char *cmd);
void do_peek(struct char_data *ch, char *arg, const char *cmd);
void do_train(struct char_data *ch, char *argument, const char * cmd);
void do_inset(struct char_data *ch, char *argument, const char * cmd);
void do_disarm(struct char_data *ch, char *argument, const char * cmd);
void do_track(struct char_data *ch, char *argument, const char * cmd);
void do_doorbash(struct char_data *ch, char *arg, const char * cmd);
void do_swim(struct char_data *ch, char *arg, const char * cmd);
void do_spy(struct char_data *ch, char *arg, const char * cmd);
void do_feign_death(struct char_data *ch, char *arg, const char * cmd);
void do_first_aid(struct char_data *ch, char *arg, const char * cmd);
void do_disguise(struct char_data *ch, char *arg, const char * cmd);
void do_climb(struct char_data *ch, char *arg, const char * cmd);
void do_berserk(struct char_data *ch, char *arg, const char * cmd);
void do_makepotion(struct char_data *ch, char *argument, const char * cmd);

#endif /* _SKILLS_H */
