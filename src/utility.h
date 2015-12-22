#ifndef _UTILITY_H
#define _UTILITY_H

#include <syslog.h>

void log_lev_msgf(int level, const char *fmt, ...);
void log_msgf(const char *fmt, ...);
void log_msg(const char *str);
void log_wiz(char *str, int sev);

#endif /* #ifdef _UTILITY_H */
