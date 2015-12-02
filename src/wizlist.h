/*
  SillyMUD Distribution V1.1b             (c) 1993 SillyMUD Developement
 
  See license.doc for distribution terms.   SillyMUD is based on DIKUMUD
*/

#ifndef _WIZLIST_H
#define _WIZLIST_H

#include "config.h"

struct wiznest {
  char *name;
  char *title;
};

struct wiznode {
  struct wiznest stuff[150];
};

struct wizlistgen {
  int number[11];
  struct wiznode lookup[11];
};

#endif
