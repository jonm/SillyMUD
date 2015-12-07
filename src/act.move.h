#ifndef _ACT_MOVE_H
#define _ACT_MOVE_H

#define MOVE_DIR_NORTH 0
#define MOVE_DIR_EAST 1
#define MOVE_DIR_SOUTH 2
#define MOVE_DIR_WEST 3
#define MOVE_DIR_UP 4
#define MOVE_DIR_DOWN 5

#define MOVE_DIR_FIRST 0
#define MOVE_DIR_LAST 5

#define MOVE_DIR_INVALID -1

void move_dir(struct char_data *ch, int dir);

#endif /* _ACT_MOVE_H */
