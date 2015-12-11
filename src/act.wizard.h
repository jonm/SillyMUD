#ifndef _ACT_WIZARD_H
#define _ACT_WIZARD_H

void force_action(struct char_data *ch, char *argument, int npc_ok);
void return_action(struct char_data *ch, int call_as_self);
void do_start(struct char_data *ch);

void do_imptest(struct char_data *ch, char *arg, const char * cmd);
void do_passwd(struct char_data *ch, char *argument, const char * cmdnum);
void do_setsev(struct char_data *ch, char *arg, const char * cmd);
void do_bamfin(struct char_data *ch, char *arg, const char * cmd);
void do_bamfout(struct char_data *ch, char *arg, const char * cmd);
void do_instazone(struct char_data *ch, char *argument, const char * cmdnum);
void do_highfive(struct char_data *ch, char *argument, const char * cmd);
void do_addhost(struct char_data *ch, char *argument, const char * command);
void do_removehost(struct char_data *ch, char *argument, const char * command);
void do_listhosts(struct char_data *ch, char *argument, const char * command);
void do_silence(struct char_data *ch, char *argument, const char * cmd);
void do_wizlock(struct char_data *ch, char *argument, const char * cmd);
void do_rload(struct char_data *ch, char *argument, const char * cmd);
void do_rsave(struct char_data *ch, char *argument, const char * cmd);
void do_emote(struct char_data *ch, char *argument, const char * cmd);
void do_echo(struct char_data *ch, char *argument, const char * cmd);
void do_system(struct char_data *ch, char *argument, const char * cmd);
void do_trans(struct char_data *ch, char *argument, const char * cmd);
void do_at(struct char_data *ch, char *argument, const char * cmd);
void do_goto(struct char_data *ch, char *argument, const char * cmd);
void do_stat(struct char_data *ch, char *argument, const char * cmd);
void do_set(struct char_data *ch, char *argument, const char * cmd);
void do_shutdow(struct char_data *ch, char *argument, const char * cmd);
void do_shutdown(struct char_data *ch, char *argument, const char * cmd);
void do_snoop(struct char_data *ch, char *argument, const char * cmd);
void do_switch(struct char_data *ch, char *argument, const char * cmd);
void do_return(struct char_data *ch, char *argument, const char * cmd);
void do_force(struct char_data *ch, char *argument, const char * cmd);
void do_load(struct char_data *ch, char *argument, const char * cmd);
void do_purge(struct char_data *ch, char *argument, const char * cmd);
void do_advance(struct char_data *ch, char *argument, const char * cmd);
void do_reroll(struct char_data *ch, char *argument, const char * cmd);
void do_restore(struct char_data *ch, char *argument, const char * cmd);
void do_noshout(struct char_data *ch, char *argument, const char * cmd);
void do_nohassle(struct char_data *ch, char *argument, const char * cmd);
void do_stealth(struct char_data *ch, char *argument, const char * cmd);
void do_show(struct char_data *ch, char *argument, const char * cmd);
void do_debug(struct char_data *ch, char *argument, const char * cmd);
void do_invis(struct char_data *ch, char *argument, const char * cmd);
void do_create(struct char_data *ch, char *argument, const char * cmd);
void do_set_log(struct char_data *ch, char *arg, const char * cmd);
void do_event(struct char_data *ch, char *arg, const char * cmd);
void do_beep(struct char_data *ch, char *argument, const char * cmd);
void do_cset(struct char_data *ch, char *arg, const char * cmd);

#define emote(ch, emo) do_emote((ch), (emo), NULL)

#endif /* _ACT_WIZARD_H */
