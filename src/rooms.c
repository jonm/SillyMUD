#include <stdlib.h>
#include <strings.h>

#include "config.h"
#include "structs.h"
#include "rooms.h"

void init_world(struct room_data *room_db[]) {

  bzero(room_db, sizeof(struct room_data *) * WORLD_SIZE);      /* zero out the world */

}

struct room_data *room_find(struct room_data *room_db[], int key) {
  return ((key < WORLD_SIZE && key > -1) ? room_db[key] : 0);
}

int room_enter(struct room_data *rb[], int key, struct room_data *rm) {
  struct room_data *temp;

  temp = room_find(rb, key);
  if (temp)
    return (0);

  rb[key] = rm;
  return (1);

}

struct room_data *room_find_or_create(struct room_data *rb[], int key) {
  struct room_data *rv;

  rv = room_find(rb, key);
  if (rv)
    return rv;

  rv = (struct room_data *)malloc(sizeof(struct room_data));

  rb[key] = rv;

  return rv;
}

int room_remove(struct room_data *rb[], int key) {

  struct room_data *tmp;

  tmp = room_find(rb, key);

  if (tmp) {
    rb[key] = 0;
    free(tmp);
  }
  return (0);
}

void room_iterate(struct room_data *rb[], void (*func) (), void *cdata) {
  register int i;
  for (i = 0; i < WORLD_SIZE; i++) {
    struct room_data *temp;

    temp = room_find(rb, i);
    if (temp) {
      (*func) (i, temp, cdata);
    }
  }
}
