#ifndef _RECEPTION_H
#define _RECEPTION_H

#include "config.h"

#define RENT_DIRECTORY DEFAULT_LIBDIR "/rent"

void ensure_rent_directory();
int receptionist(struct char_data *ch, const char *cmd, char *arg,
                 struct char_data *mob, int type);

#endif
