#ifndef ACT_COMM_H
#define ACT_COMM_H

void do_say(struct char_data *ch, char *argument, const char * cmd);
void do_shout(struct char_data *ch, char *argument, const char * cmd);
void do_commune(struct char_data *ch, char *argument, const char * cmd);
void do_tell(struct char_data *ch, char *argument, const char * cmd);
void do_whisper(struct char_data *ch, char *argument, const char * cmd);
void do_ask(struct char_data *ch, char *argument, const char * cmd);
void do_write(struct char_data *ch, char *argument, const char * cmd);
void do_sign(struct char_data *ch, char *argument, const char * cmd);

#define say(ch, words) do_say((ch), (words), "say")
#define shout(ch, words) do_shout((ch), (words), "shout")

#endif
