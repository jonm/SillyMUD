#ifndef _MEMORY_H
#define _MEMORY_H

#include "config.h"

struct string_entry {
  char *string;                 /* Pointer to the actual data      */
  int count;                    /* How many strings are using it   */
  struct string_entry *next;
};

#endif
