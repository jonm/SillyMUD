#ifndef _ROOMS_H
#define _ROOMS_H

#define WORLD_SIZE 30000

void init_world(struct room_data *room_db[]);
struct room_data *room_find(struct room_data *room_db[], int key);
int room_enter(struct room_data *rb[], int key, struct room_data *rm);
struct room_data *room_find_or_create(struct room_data *rb[], int key);
int room_remove(struct room_data *rb[], int key);
void room_iterate(struct room_data *rb[], void (*func) (), void *cdata);

#endif
