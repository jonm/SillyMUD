#ifndef FIGHT_H
#define FIGHT_H

typedef int (damage_func)(struct char_data*, struct char_data *, int, int);

damage_func missile_damage;
damage_func damage;
void miss_victim(struct char_data *, struct char_data *, int, int,
                 damage_func *);
void hit_victim(struct char_data *, struct char_data *, int, int, int,
                damage_func *);
void root_hit(struct char_data *, struct char_data *, int, damage_func *);



#endif
