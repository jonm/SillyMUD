/*
  SillyMUD Distribution V1.1b             (c) 1993 SillyMUD Developement
 
  See license.doc for distribution terms.   SillyMUD is based on DIKUMUD
*/

#ifndef _HASH_H
#define _HASH_H

#include "config.h"

struct hash_link {
  int key;
  struct hash_link *next;
  void *data;
};

struct hash_header {
  int rec_size;
  int table_size;
  int *keylist, klistsize, klistlen;    /* this is really lame,
                                           AMAZINGLY lame */
  struct hash_link **buckets;
};

typedef struct hash_header hash_table_t;

void init_hash_table(hash_table_t *ht, int rec_size, int table_size);
void destroy_hash_table(hash_table_t *ht);
void _hash_enter(hash_table_t *ht, int key, void *data);
void *hash_find(hash_table_t *ht, int key);
int hash_enter(hash_table_t *ht, int key, void *data);
void *hash_find_or_create(hash_table_t *ht, int key);
void *hash_remove(hash_table_t *ht, int key);
void hash_iterate(hash_table_t *ht, void (*func) (), void *cdata);

#endif
