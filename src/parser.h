/*
  SillyMUD Distribution V1.1b             (c) 1993 SillyMUD Developement
 
  See license.doc for distribution terms.   SillyMUD is based on DIKUMUD
*/

#ifndef _PARSER_H
#define _PARSER_H

#include "config.h"

#define MAGIC    96             /* Magic number for the hash table */


typedef struct command_node NODE;
typedef void (*cmd_handler) (struct char_data * ch, char *arg, const char *cmd);

struct command_node {
  char name[64];
  cmd_handler func;
  byte min_pos;
  byte min_level;
  byte log;
  struct command_node *next;
  struct command_node *previous;
};

struct radix_list {
  struct command_node *next;
  unsigned short int number;
  byte max_len;
};

void add_command(char *name, cmd_handler func, int min_pos, int min_lev);

#endif
