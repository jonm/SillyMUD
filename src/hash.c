/*
  SillyMUD Distribution V1.1b             (c) 1993 SillyMUD Developement
 
  See license.doc for distribution terms.   SillyMUD is based on DIKUMUD
*/
#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "protos.h"

#define	HASH_KEY(ht,key)	( (((unsigned int)(key)) * 17) % (ht)->table_size )

void init_hash_table(hash_table_t *ht, int rec_size, int table_size) {
  ht->rec_size = rec_size;
  ht->table_size = table_size;
  ht->buckets = (void *)calloc(sizeof(struct hash_link **), table_size);
  ht->keylist = (void *)malloc(sizeof(ht->keylist) * (ht->klistsize = 128));
  ht->klistlen = 0;
}

void destroy_hash_table(hash_table_t *ht) {
  int i;
  struct hash_link *scan, *temp;

  for (i = 0; i < ht->table_size; i++)
    for (scan = ht->buckets[i]; scan;) {
      temp = scan->next;
      free(scan);
      scan = temp;
    }
  free(ht->buckets);
  free(ht->keylist);
}

void _hash_enter(hash_table_t *ht, int key, void *data) { /* precondition: there is no entry for <key> yet */
  struct hash_link *temp;
  int i;

  temp = (struct hash_link *)malloc(sizeof(struct hash_link));
  temp->key = key;
  temp->next = ht->buckets[HASH_KEY(ht, key)];
  temp->data = data;
  ht->buckets[HASH_KEY(ht, key)] = temp;
  if (ht->klistlen >= ht->klistsize) {
    ht->keylist = (void *)realloc(ht->keylist, sizeof(*ht->keylist) *
                                  (ht->klistsize *= 2));
  }
  for (i = ht->klistlen; i >= 0; i--) {
    if (i == 0 || ht->keylist[i - 1] < key) {
      ht->keylist[i] = key;
      break;
    }
    ht->keylist[i] = ht->keylist[i - 1];
  }
  ht->klistlen++;
}

void *hash_find(hash_table_t *ht, int key) {
  struct hash_link *scan;

  scan = ht->buckets[HASH_KEY(ht, key)];

  while (scan && scan->key != key)
    scan = scan->next;

  return scan ? scan->data : NULL;
}

int hash_enter(hash_table_t *ht, int key, void *data) {
  void *temp;
  temp = hash_find(ht, key);
  if (temp)
    return 0;

  _hash_enter(ht, key, data);
  return 1;
}

void *hash_find_or_create(hash_table_t *ht, int key) {
  void *rval;

  rval = hash_find(ht, key);
  if (rval)
    return rval;

  rval = (void *)malloc(ht->rec_size);
  _hash_enter(ht, key, rval);
  return rval;
}

void *hash_remove(hash_table_t *ht, int key) {
  struct hash_link **scan;

  scan = ht->buckets + HASH_KEY(ht, key);

  while (*scan && (*scan)->key != key)
    scan = &(*scan)->next;

  if (*scan) {
    int i;

    struct hash_link *temp, *aux;
    temp = (*scan)->data;
    aux = *scan;
    *scan = aux->next;
    free(aux);

    for (i = 0; i < ht->klistlen; i++)
      if (ht->keylist[i] == key)
        break;

    if (i < ht->klistlen) {
      bcopy(ht->keylist + i + 1, ht->keylist + i,
            (ht->klistlen - i) * sizeof(*ht->keylist));
      ht->klistlen--;
    }

    return temp;
  }

  return NULL;
}

void hash_iterate(hash_table_t *ht, void (*func) (), void *cdata) {
  int i;
  for (i = 0; i < ht->klistlen; i++) {
    void *temp;
    register int key;

    key = ht->keylist[i];
    temp = hash_find(ht, key);
    (*func) (key, temp, cdata);
    if (ht->keylist[i] != key)  /* They must have deleted this room */
      i--;                      /* Hit this slot again. */
  }
}
