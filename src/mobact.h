#ifndef MOBACT_H
#define MOBACT_H

typedef void (mobact_func)(char *, struct char_data *);

mobact_func noop;
mobact_func end2;
mobact_func sgoto;
mobact_func do_act;
mobact_func do_jmp;
mobact_func do_jsr;
mobact_func do_rts;

void command_assign(char *arg, mobact_func *p);

#endif
