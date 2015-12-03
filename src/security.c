/*
  SillyMUD Distribution V1.1b             (c) 1993 SillyMUD Developement
 
  See license.doc for distribution terms.   SillyMUD is based on DIKUMUD
*/
#include "config.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

void log_msg(char *);

int sec_check(char *arg, char *site) {
  char buf[255], buf2[255];
  FILE *f1;

  SPRINTF(buf, "security/%s", arg);

  if (!(f1 = fopen(buf, "rt"))) {
    SPRINTF(buf, "Unable to open security file for %s.", arg);
    log_msg(buf);
    return (-1);
  }

  fgets(buf2, 250, f1);
  fclose(f1);

  if (!*buf2) {
    SPRINTF(buf, "Security file for %s empty.", arg);
    log_msg(buf);
    return (-1);
  }

  if (buf2[strlen(buf2) - 1] == '\n')
    buf2[strlen(buf2) - 1] = '\0';

  if (!(strncmp(site, buf2, strlen(buf2)))) {
    return (1);
  }
  SPRINTF(buf, "Site %s and %s don't match for %s. Booting.", site, buf2, arg);
  log_msg(buf);

  return (0);
}
