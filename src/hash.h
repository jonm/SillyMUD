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


#define WORLD_SIZE 30000

/* From hash.c */

void init_hash_table(struct hash_header *ht, int rec_size, int table_size);
void init_world(struct room_data *room_db[]);
void destroy_hash_table(struct hash_header *ht, void (*gman) ());
void _hash_enter(struct hash_header *ht, int key, void *data);
struct room_data *room_find(struct room_data *room_db[], int key);
void *hash_find(struct hash_header *ht, int key);
int room_enter(struct room_data *rb[], int key, struct room_data *rm);
int hash_enter(struct hash_header *ht, int key, void *data);
struct room_data *room_find_or_create(struct room_data *rb[], int key);
void *hash_find_or_create(struct hash_header *ht, int key);
int room_remove(struct room_data *rb[], int key);
void *hash_remove(struct hash_header *ht, int key);
void room_iterate(struct room_data *rb[], void (*func) (), void *cdata);
void hash_iterate(struct hash_header *ht, void (*func) (), void *cdata);

#endif
