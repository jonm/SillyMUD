#ifndef _ACT_OFF_H
#define _ACT_OFF_H

extern breath_weapon_func *bweapons[];

void bash_action(struct char_data *ch, char *argument, int npc_ok);
void kick_action(struct char_data *ch, char *argument, int npc_ok);
void rescue_action(struct char_data *ch, char *argument, int npc_ok);
void kick_messages(struct char_data *ch, struct char_data *victim, int damage);

void do_hit(struct char_data *ch, char *argument, const char * cmd);
void do_kill(struct char_data *ch, char *argument, const char * cmd);
void do_backstab(struct char_data *ch, char *argument, const char * cmd);
void do_order(struct char_data *ch, char *argument, const char * cmd);
void do_flee(struct char_data *ch, char *argument, const char * cmd);
void do_bash(struct char_data *ch, char *argument, const char * cmd);
void do_rescue(struct char_data *ch, char *argument, const char * cmd);
void do_assist(struct char_data *ch, char *argument, const char * cmd);
void do_kick(struct char_data *ch, char *argument, const char * cmd);
void do_wimp(struct char_data *ch, char *argument, const char * cmd);
void do_breath(struct char_data *ch, char *argument, const char * cmd);
void do_shoot(struct char_data *ch, char *argument, const char * cmd);
void do_springleap(struct char_data *ch, char *argument, const char * cmd);
void do_quivering_palm(struct char_data *ch, char *arg, const char * cmd);

#endif /* ifdef _ACT_OFF_H */
