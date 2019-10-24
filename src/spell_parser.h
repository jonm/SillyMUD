#ifndef SPELL_PARSER_H
#define SPELL_PARSER_H

void do_cast(struct char_data *ch, char *argument, const char *cmd);

void spello(int nr, ubyte beat, byte pos, byte mlev, byte clev, byte dlev,
            ubyte mana, sh_int tar, spell_func *func, sh_int sf);

#endif
