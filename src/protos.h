#ifndef _PROTOS_H
#define _PROTOS_H

#include "config.h"

/* Prototypes */
#include "structs.h"
#include "area.h"
#include "comm.h"
#include "db.h"
#include "handler.h"
#include "hash.h"
#include "heap.h"
#include "interpreter.h"
#include "limits.h"
#include "poly.h"
#include "race.h"
#include "script.h"
#include "spells.h"
#include "trap.h"
#include "utils.h"
#include "vt100c.h"
#include "wizlist.h"
#include "parser.h"

/* From Heap.c */

void smart_str_cpy(char *s1, const char *s2);
void string_heap(char *string, struct StrHeap *Heap);
struct StrHeap *init_heap();
void display_string_heap(struct StrHeap *Heap, struct char_data *ch, int type,
                         int d);


/* From Opinion.c */

void free_hates(struct char_data *ch);
void free_fears(struct char_data *ch);
int rem_hated(struct char_data *ch, struct char_data *pud);
int add_hated(struct char_data *ch, struct char_data *pud);
int add_hatred(struct char_data *ch, int parm_type, int parm);
void delete_hatreds(struct char_data *ch);
int hates(struct char_data *ch, struct char_data *v);
int fears(struct char_data *ch, struct char_data *v);
int rem_feared(struct char_data *ch, struct char_data *pud);
int add_feared(struct char_data *ch, struct char_data *pud);
int add_fears(struct char_data *ch, int parm_type, int parm);
struct char_data *find_a_hatee(struct char_data *ch);
struct char_data *find_a_fearee(struct char_data *ch);
void zero_hatred(struct char_data *ch, struct char_data *v);
void zero_feared(struct char_data *ch, struct char_data *v);
void delete_fears(struct char_data *ch);
void kill_the_orcs(struct char_data *ch);

/* From Sound.c */

int rec_get_obj_room(struct obj_data *obj);
void make_noise(int room, char *local_snd, char *distant_snd);
void make_sound(int pulse);


/* From Trap.c */

void do_settrap(struct char_data *ch, char *arg, int cmd);
int check_for_move_trap(struct char_data *ch, int dir);
int check_for_inside_trap(struct char_data *ch, struct obj_data *i);
int check_for_any_trap(struct char_data *ch, struct obj_data *i);
int check_for_get_trap(struct char_data *ch, struct obj_data *i);
int trigger_trap(struct char_data *ch, struct obj_data *i);
void find_trap_damage(struct char_data *v, struct obj_data *i);
void trap_damage(struct char_data *v, int damtype, int amnt,
                 struct obj_data *t);
void trap_dam(struct char_data *v, int damtype, int amnt, struct obj_data *t);
void trap_teleport(struct char_data *v);
void trap_sleep(struct char_data *v);
void inform_mess(struct char_data *v);


/* From act.comm.c and act.move.c*/

void update_screen(struct char_data *ch, int update);
void init_screen(struct char_data *ch);
char *random_word();
void bird_garble(char *buf, char *buf2, struct char_data *ch);
void rat_garble(char *buf, char *buf2, struct char_data *ch);
void half_orc_garble(char *buf, char *buf2, struct char_data *ch);
void ogre_garble(char *buf, char *buf2, struct char_data *ch);
int move_one(struct char_data *ch, int dir);
void display_one_move(struct char_data *ch, int dir, int was_in);
void display_group_move(struct char_data *ch, int dir, int was_in, int total);
void display_move(struct char_data *ch, int dir, int was_in, int total);
int valid_move(struct char_data *ch, int cmd);
int add_to_char_heap(struct char_data **heap, int *top, int *total,
                     struct char_data *k);
int find_door(struct char_data *ch, char *type, char *dir);
void raw_open_door(struct char_data *ch, int dir);
void open_door(struct char_data *ch, int dir);
void raw_unlock_door(struct char_data *ch, struct room_direction_data *exitp,
                     int door);

/* From act.info.c */

void screen_off(struct char_data *ch);
int singular(struct obj_data *o);
void argument_split_2(char *argument, char *first_arg, char *second_arg);
struct obj_data *get_object_in_equip_vis(struct char_data *ch,
                                         char *arg,
                                         struct obj_data *equipment[], int *j);
char *find_ex_description(char *word, struct extra_descr_data *list);
void show_obj_to_char(struct obj_data *object, struct char_data *ch, int mode);
void show_mult_obj_to_char(struct obj_data *o, struct char_data *ch, int m,
                           int n);
void list_obj_in_room(struct obj_data *list, struct char_data *ch);
void list_obj_in_heap(struct obj_data *list, struct char_data *ch);
void list_obj_to_char(struct obj_data *l, struct char_data *ch, int m,
                      bool show);
void show_char_to_char(struct char_data *i, struct char_data *ch, int mode);
void show_mult_char_to_char(struct char_data *i, struct char_data *ch, int m,
                            int n);
void list_char_in_room(struct char_data *list, struct char_data *ch);
int which_number_mobile(struct char_data *mob);
char *numbered_person(struct char_data *ch, struct char_data *person);
void do_where_person(struct char_data *ch, struct char_data *p,
                     struct string_block *sb);
void do_where_object(struct char_data *ch, struct obj_data *obj,
                     int recurse, struct string_block *sb);
char *align_desc(int a);
char *armor_desc(int a);
char *hit_roll_desc(int a);
char *dam_roll_desc(int a);
char *desc_ratio(float f);
char *desc_damage(float dam);
char *desc_attacks(float a);
char *ego_desc(int a);
int mob_lev_bonus(struct char_data *ch);
void show_exits(struct char_data *ch);


/* From act.obj1.c */

void get(struct char_data *ch, struct obj_data *obj_object,
         struct obj_data *sub_object);
int newstrlen(char *p);


/* From act.obj2.c */

void weight_change_object(struct obj_data *obj, int weight);
void name_from_drinkcon(struct obj_data *obj);
void name_to_drinkcon(struct obj_data *obj, int type);
void perform_wear(struct char_data *ch, struct obj_data *obj_object,
                  int keyword);
int is_restricted(int Mask, int Class);
void wear(struct char_data *ch, struct obj_data *obj_object, int keyword);

/* From act.social.c */

char *fread_action(FILE * fl);
void boot_social_messages();
void boot_pose_messages();


/* From act.wizard.c */

void dsearch(char *string, char *tmp);
void purge_one_room(int rnum, struct room_data *rp, int *range);
void roll_abilities(struct char_data *ch);
void print_room(int rnum, struct room_data *rp, struct string_block *sb);
void print_death_room(int rnum, struct room_data *rp, struct string_block *sb);
void print_private_room(int r, struct room_data *rp, struct string_block *sb);
void create_one_room(int loc_nr);

/* From board.c */

void board_write_msg(struct char_data *ch, char *arg, int bnum);
int board_display_msg(struct char_data *ch, char *arg, int bnum);
int board_remove_msg(struct char_data *ch, char *arg, int bnum);
void board_save_board();
void board_load_board();
int board_show_board(struct char_data *ch, char *arg, int bnum);
int fwrite_string(char *buf, FILE * fl);
char *fix_returns(char *text_string);
int board_check_locks(int bnum, struct char_data *ch);


/* From comm.c */

int __main();
void close_socket_fd(int desc);
int real_main(int argc, char **argv);
void run_the_game(int port);
void game_loop(int s);
int get_from_q(struct txt_q *queue, char *dest);
void write_to_q(char *txt, struct txt_q *queue);
struct timeval timediff(struct timeval *a, struct timeval *b);
void flush_queues(struct descriptor_data *d);
int init_socket(int port);
int new_connection(int s);

int new_descriptor(int s);
int process_output(struct descriptor_data *t);
int write_to_descriptor(int desc, char *txt);
int process_input(struct descriptor_data *t);
void close_sockets(int s);
void close_socket(struct descriptor_data *d);
void nonblock(int s);
void coma(int s);
void send_to_char(char *messg, struct char_data *ch);
void save_all();
void send_to_all(char *messg);
void send_to_outdoor(char *messg);
void send_to_desert(char *messg);
void send_to_out_other(char *messg);
void send_to_arctic(char *messg);
void send_to_except(char *messg, struct char_data *ch);
void send_to_zone(char *messg, struct char_data *ch);
void send_to_room(char *messg, int room);
void send_to_room_except(char *messg, int room, struct char_data *ch);
void send_to_room_except_two
  (char *messg, int room, struct char_data *ch1, struct char_data *ch2);
void act(char *str, int hide_invisible, struct char_data *ch,
         struct obj_data *obj, void *vict_obj, int type);
void raw_force_all(char *to_force);


/* From constants.c */


/* From db.c */

void save_the_world();
void boot_db();
void reset_time();
void update_time();
void build_player_index();
void cleanout_room(struct room_data *rp);
void completely_cleanout_room(struct room_data *rp);
void load_one_room(FILE * fl, struct room_data *rp);
void boot_world();
void allocate_room(int room_number);
void setup_dir(FILE * fl, int room, int dir);
void renum_zone_table();
void boot_zones();
struct char_data *read_mobile(int nr, int type);
struct obj_data *read_object(int nr, int type);
void zone_update();
void reset_zone(int zone);
int is_empty(int zone_nr);
int load_char(char *name, struct char_file_u *char_element);
void store_to_char(struct char_file_u *st, struct char_data *ch);
void char_to_store(struct char_data *ch, struct char_file_u *st);
int create_entry(char *name);
void save_char(struct char_data *ch, sh_int load_room);
int compare(struct player_index_element *arg1, struct player_index_element
            *arg2);
void free_char(struct char_data *ch);
void free_obj(struct obj_data *obj);
int file_to_string(char *name, char *buf);
void clear_dead_bit(struct char_data *ch);
void clean_playerfile();
void reset_char(struct char_data *ch);
void clear_char(struct char_data *ch);
void clear_object(struct obj_data *obj);
void init_char(struct char_data *ch);
struct room_data *real_roomp(int virtual);
int real_mobile(int virtual);
int real_object(int virtual);
int obj_room_count(int nr, struct room_data *rp);
int str_len(char *buf);
int load();
void gr();
int workhours();
void init_scripts();
void reload_rooms();
void free_zone(int zone_nr);
void boot_figurines();
int check_kill_file(int virtual);
/* char *strmake(char *string); KEEP THIS OUT UNTIL FIXED */
/* void strfree(char *string);  KEEP THIS OUT UNTIL FIXED */

/* From fight.c */

void appear(struct char_data *ch);
int level_mod(struct char_data *ch, struct char_data *v, int exp);
int ratio_exp(struct char_data *ch, struct char_data *victim, int total);
void load_messages();
void update_pos(struct char_data *victim);
int check_peaceful(struct char_data *ch, char *msg);
void set_fighting(struct char_data *ch, struct char_data *vict);
void stop_fighting(struct char_data *ch);
void make_corpse(struct char_data *ch);
void change_alignment(struct char_data *ch, struct char_data *victim);
void death_cry(struct char_data *ch);
void raw_kill(struct char_data *ch);
void die(struct char_data *ch);
void group_gain(struct char_data *ch, struct char_data *victim);
char *replace_string(char *str, char *weapon, char *weapon_s);
void dam_message(int dam, struct char_data *ch, struct char_data *victim,
                 int w_type);
int dam_check_deny(struct char_data *ch, struct char_data *victim, int type);
int dam_details_ok(struct char_data *ch, struct char_data *v, int dam,
                   int type);
int set_char_fighting(struct char_data *ch, struct char_data *v);
int set_vict_fighting(struct char_data *ch, struct char_data *v);
int damage_trivia(struct char_data *ch, struct char_data *v, int dam,
                  int type);
int do_damage(struct char_data *ch, struct char_data *v, int dam, int type);
void damage_messages(struct char_data *ch, struct char_data *v, int dam,
                     int attacktype);
int damage_epilog(struct char_data *ch, struct char_data *victim);
int get_weapon_type(struct char_data *ch, struct obj_data **wielded);
int Getw_type(struct obj_data *wielded);
int hit_check_deny(struct char_data *ch, struct char_data *victim);
int calc_thaco(struct char_data *ch);
int hit_or_miss(struct char_data *ch, struct char_data *victim,
                int calc_thaco);
int get_weapon_dam(struct char_data *ch, struct char_data *v,
                   struct obj_data *wielded);
int get_backstab_mult(struct char_data *ch, struct char_data *v);
void missile_hit(struct char_data *ch, struct char_data *victim, int type);
void hit(struct char_data *ch, struct char_data *victim, int type);
void perform_violence(void);
struct char_data *find_victim(struct char_data *ch);
struct char_data *find_any_victim(struct char_data *ch);
void break_life_saver_obj(struct char_data *ch);
int brittle_check(struct char_data *ch, int dam);
int pre_proc_dam(struct char_data *ch, int type, int dam);
int damage_one_item(struct char_data *ch, int dam_type, struct obj_data *obj);
void make_scrap(struct char_data *ch, struct obj_data *obj);
void damage_all_stuff(struct char_data *ch, int dam_type);
int damage_item(struct obj_data *o, int num);
int item_save(struct obj_data *i, int dam_type);
int damaged_by_attack(struct obj_data *i, int dam_type);
int weapon_check(struct char_data *ch, struct char_data *v, int type, int dam);
void damage_stuff(struct char_data *v, int type, int dam);
int get_item_damage_type(int type);
int skip_immortals(struct char_data *v, int amnt);
void weapon_spell(struct char_data *c, struct char_data *v, int type);
struct char_data *find_an_attacker(struct char_data *ch);
void shoot(struct char_data *ch, struct char_data *victim);
struct char_data *find_meta_victim(struct char_data *ch);
void nail_this_sucker(struct char_data *ch);
int get_form_type(struct char_data *ch);
int monk_dodge(struct char_data *ch, struct char_data *v, int *dam);
int get_monkw_type(struct char_data *ch);
void area_damage(struct char_data *ch, int dam, int attacktype,
                 char *same_room_hitmsg, char *same_room_missmsg,
                 char *global_msg, bool save_negates, bool heat_blind);

/* From handler.c */

char *fname(char *namelist);
int split_string(char *str, char *sep, char **argv);
int isname(const char *str, const char *namelist);
void init_string_block(struct string_block *sb);
void append_to_string_block(struct string_block *sb, char *str);
void page_string_block(struct string_block *sb, struct char_data *ch);
void destroy_string_block(struct string_block *sb);
void affect_modify(struct char_data *ch, byte loc, long mod, long bitv,
                   bool add);
void affect_total(struct char_data *ch);
void affect_to_char(struct char_data *ch, struct affected_type *af);
void affect_remove(struct char_data *ch, struct affected_type *af);
void affect_from_char(struct char_data *ch, short skill);
bool affected_by_spell(struct char_data *ch, short skill);
void affect_join(struct char_data *ch, struct affected_type *af,
                 bool avg_dur, bool avg_mod);
void char_from_room(struct char_data *ch);
void char_to_room(struct char_data *ch, int room);
void obj_to_char(struct obj_data *object, struct char_data *ch);
void obj_from_char(struct obj_data *object);
int apply_ac(struct char_data *ch, int eq_pos);
void equip_char(struct char_data *ch, struct obj_data *obj, int pos);
int give_min_str_to_wield(struct obj_data *obj, struct char_data *ch);
struct obj_data *unequip_char(struct char_data *ch, int pos);
struct obj_data *get_obj_in_list(char *name, struct obj_data *list);
struct obj_data *get_obj_in_list_num(int num, struct obj_data *list);
struct obj_data *get_obj(char *name);
struct obj_data *get_obj_num(int nr);
struct char_data *get_char_room(char *name, int room);
struct char_data *get_char(char *name);
struct char_data *get_char_num(int nr);
void obj_to_room(struct obj_data *object, int room);
void obj_to_room2(struct obj_data *object, int room);
void obj_from_room(struct obj_data *object);
void obj_to_obj(struct obj_data *obj, struct obj_data *obj_to);
void obj_from_obj(struct obj_data *obj);
void object_list_new_owner(struct obj_data *list, struct char_data *ch);
void extract_obj(struct obj_data *obj);
void update_object(struct obj_data *obj, int use);
void update_char_objects(struct char_data *ch);
void extract_char(struct char_data *ch);
void extract_char_smarter(struct char_data *ch, int save_room);
struct char_data *get_char_room_vis(struct char_data *ch, char *name);
struct char_data *get_char_vis_world(struct char_data *ch, char *name,
                                     int *count);
struct char_data *get_char_vis(struct char_data *ch, char *name);
struct obj_data *get_obj_in_list_vis(struct char_data *ch, char *name,
                                     struct obj_data *list);
struct obj_data *get_obj_vis_world(struct char_data *ch, char *name,
                                   int *count);
struct obj_data *get_obj_vis(struct char_data *ch, char *name);
struct obj_data *get_obj_vis_accessible(struct char_data *ch, char *name);
struct obj_data *create_money(int amount);
int generic_find(char *arg, int bitvector, struct char_data *ch,
                 struct char_data **tar_ch, struct obj_data **tar_obj);
void add_affects(struct char_data *ch, struct obj_data *o);

/* From interpreter.c */

void commando(int number, int min_pos, void (*pointer) (), int min_level);
int search_block(char *arg, char **list, bool exact);
int old_search_block(char *argument, int begin, int length, char **list,
                     int mode);
void command_interpreter(struct char_data *ch, char *argument);
void argument_interpreter(char *argument, char *first_arg, char *second_arg);
int is_number(char *str);
char *one_argument(char *argument, char *first_arg);
void only_argument(char *argument, char *dest);
int fill_word(char *argument);
int is_abbrev(char *arg1, char *arg2);
void half_chop(char *string, char *arg1, char *arg2);
void assign_command_pointers();
int find_name(char *name);
int _parse_name(char *arg, char *name);
void nanny(struct descriptor_data *d, char *arg);
void display_races(struct descriptor_data *d);
int get_racial_alignment(struct descriptor_data *d);
int check_valid_class(struct descriptor_data *d, int class);
void display_race_classes(struct descriptor_data *d);

/* From limits.c */

char *class_titles(struct char_data *ch);
int graf(int age, int p0, int p1, int p2, int p3, int p4, int p5, int p6);
int mana_limit(struct char_data *ch);
int hit_limit(struct char_data *ch);
int move_limit(struct char_data *ch);
int mana_gain(struct char_data *ch);
int hit_gain(struct char_data *ch);
int move_gain(struct char_data *ch);
void advance_level(struct char_data *ch, int class);
void drop_level(struct char_data *ch, int class);
void set_title(struct char_data *ch);
void gain_exp(struct char_data *ch, int gain);
void gain_exp_regardless(struct char_data *ch, int gain, int class);
void gain_condition(struct char_data *ch, int condition, int value);
void check_idling(struct char_data *ch);
void obj_from_corpse(struct obj_data *c);
void class_specific_stuff(struct char_data *ch);


/* From magic.c */

void heat_blind(struct char_data *ch);
void spell_magic_missile(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_chill_touch(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_burning_hands(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_shocking_grasp(byte level, struct char_data *ch,
                          struct char_data *victim, struct obj_data *obj);
void spell_lightning_bolt(byte level, struct char_data *ch,
                          struct char_data *victim, struct obj_data *obj);
void spell_colour_spray(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_energy_drain(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_fireball(byte level, struct char_data *ch,
                    struct char_data *victim, struct obj_data *obj);
void spell_earthquake(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_dispel_evil(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_call_lightning(byte level, struct char_data *ch,
                          struct char_data *victim, struct obj_data *obj);
void spell_harm(byte level, struct char_data *ch,
                struct char_data *victim, struct obj_data *obj);
void spell_armor(byte level, struct char_data *ch,
                 struct char_data *victim, struct obj_data *obj);
void spell_astral_walk(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_teleport(byte level, struct char_data *ch,
                    struct char_data *victim, struct obj_data *obj);
void spell_bless(byte level, struct char_data *ch,
                 struct char_data *victim, struct obj_data *obj);
void spell_blindness(byte level, struct char_data *ch,
                     struct char_data *victim, struct obj_data *obj);
void spell_clone(byte level, struct char_data *ch,
                 struct char_data *victim, struct obj_data *obj);
void spell_control_weather(byte level, struct char_data *ch,
                           struct char_data *victim, struct obj_data *obj);
void spell_create_food(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_create_water(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_cure_blind(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_cure_critic(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_cure_light(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_curse(byte level, struct char_data *ch,
                 struct char_data *victim, struct obj_data *obj);
void spell_detect_evil(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_detect_invisibility(byte level, struct char_data *ch,
                               struct char_data *victim, struct obj_data *obj);
void spell_detect_magic(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_detect_poison(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_enchant_weapon(byte level, struct char_data *ch,
                          struct char_data *victim, struct obj_data *obj);
void spell_enchant_armor(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_heal(byte level, struct char_data *ch,
                struct char_data *victim, struct obj_data *obj);
void spell_invisibility(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_locate_object(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_poison(byte level, struct char_data *ch,
                  struct char_data *victim, struct obj_data *obj);
void spell_protection_from_evil(byte level, struct char_data *ch,
                                struct char_data *victim,
                                struct obj_data *obj);
void spell_remove_curse(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_remove_poison(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_fireshield(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_sanctuary(byte level, struct char_data *ch,
                     struct char_data *victim, struct obj_data *obj);
void spell_sleep(byte level, struct char_data *ch, struct char_data *victim,
                 struct obj_data *obj);
void spell_strength(byte level, struct char_data *ch, struct char_data *victim,
                    struct obj_data *obj);
void spell_ventriloquate(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_word_of_recall(byte level, struct char_data *ch,
                          struct char_data *victim, struct obj_data *obj);
void spell_summon(byte level, struct char_data *ch, struct char_data *victim,
                  struct obj_data *obj);
void raw_summon(struct char_data *v, struct char_data *c);
void spell_charm_person(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_charm_monster(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_sense_life(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_identify(byte level, struct char_data *ch,
                    struct char_data *victim, struct obj_data *obj);
void spell_fire_breath(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_frost_breath(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_acid_breath(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_gas_breath(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_lightning_breath(byte level, struct char_data *ch,
                            struct char_data *victim, struct obj_data *obj);


/* Fom magic2.c */

void spell_resurrection(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_cause_light(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_cause_critical(byte level, struct char_data *ch,
                          struct char_data *victim, struct obj_data *obj);
void spell_cause_serious(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_cure_serious(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_mana(byte level, struct char_data *ch,
                struct char_data *victim, struct obj_data *obj);
void spell_second_wind(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_flamestrike(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_dispel_good(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_turn(byte level, struct char_data *ch,
                struct char_data *victim, struct obj_data *obj);
void spell_remove_paralysis(byte level, struct char_data *ch,
                            struct char_data *victim, struct obj_data *obj);
void spell_holy_word(byte level, struct char_data *ch,
                     struct char_data *victim, struct obj_data *obj);
void holy_banish(byte level, struct char_data *ch,
                 struct char_data *victim, struct obj_data *obj);
void holy_destroy(byte level, struct char_data *ch,
                  struct char_data *victim, struct obj_data *obj);
void holy_bigdif(byte level, struct char_data *ch,
                 struct char_data *victim, struct obj_data *obj);
void holy_meddif(byte level, struct char_data *ch,
                 struct char_data *victim, struct obj_data *obj);
void holy_smldif(byte level, struct char_data *ch,
                 struct char_data *victim, struct obj_data *obj);
void spell_succor(byte level, struct char_data *ch,
                  struct char_data *victim, struct obj_data *obj);
void spell_detect_charm(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_true_seeing(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_track(byte level, struct char_data *ch,
                 struct char_data *targ, struct obj_data *obj);
void spell_poly_self(byte level, struct char_data *ch,
                     struct char_data *mob, struct obj_data *obj);
void spell_minor_create(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_stone_skin(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_infravision(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_shield(byte level, struct char_data *ch,
                  struct char_data *victim, struct obj_data *obj);
void spell_weakness(byte level, struct char_data *ch,
                    struct char_data *victim, struct obj_data *obj);
void spell_invis_group(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_acid_blast(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_cone_of_cold(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_ice_storm(byte level, struct char_data *ch,
                     struct char_data *victim, struct obj_data *obj);
void spell_poison_cloud(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_major_create(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_sending(byte level, struct char_data *ch,
                   struct char_data *victim, struct obj_data *obj);
void spell_meteor_swarm(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_create_monster(byte level, struct char_data *ch,
                          struct char_data *victim, struct obj_data *obj);
void spell_light(byte level, struct char_data *ch,
                 struct char_data *victim, struct obj_data *obj);
void spell_fly(byte level, struct char_data *ch,
               struct char_data *victim, struct obj_data *obj);
void spell_fly_group(byte level, struct char_data *ch,
                     struct char_data *victim, struct obj_data *obj);
void spell_refresh(byte level, struct char_data *ch,
                   struct char_data *victim, struct obj_data *obj);
void spell_water_breath(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_cont_light(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_animate_dead(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *corpse);
void spell_know_alignment(byte level, struct char_data *ch,
                          struct char_data *victim, struct obj_data *obj);
void spell_dispel_magic(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_paralyze(byte level, struct char_data *ch,
                    struct char_data *victim, struct obj_data *obj);
void spell_fear(byte level, struct char_data *ch,
                struct char_data *victim, struct obj_data *obj);
void spell_calm(byte level, struct char_data *ch,
                struct char_data *victim, struct obj_data *obj);
void spell_web(byte level, struct char_data *ch,
               struct char_data *victim, struct obj_data *obj);
void spell_heroes_feast(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_conjure_elemental(byte level, struct char_data *ch,
                             struct char_data *victim, struct obj_data *obj);
void spell_faerie_fire(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_faerie_fog(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_cacaodemon(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_improved_identify(byte level, struct char_data *ch,
                             struct char_data *victim, struct obj_data *obj);
void spell_geyser(byte level, struct char_data *ch,
                  struct char_data *victim, struct obj_data *obj);
void spell_green_slime(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);


/* From magic3.c */

void spell_tree_travel(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_transport_via_plant(byte level, struct char_data *ch,
                               struct char_data *victim, struct obj_data *obj);
void spell_speak_with_plants(byte level, struct char_data *ch,
                             struct char_data *victim, struct obj_data *obj);
void spell_changestaff(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_pword_kill(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_pword_blind(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_chain_lightn(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_scare(byte level, struct char_data *ch,
                 struct char_data *victim, struct obj_data *obj);
void spell_haste(byte level, struct char_data *ch,
                 struct char_data *victim, struct obj_data *obj);
void spell_slow(byte level, struct char_data *ch,
                struct char_data *victim, struct obj_data *obj);
void spell_familiar(byte level, struct char_data *ch,
                    struct char_data **victim, struct obj_data *obj);
void spell_aid(byte level, struct char_data *ch,
               struct char_data *victim, struct obj_data *obj);
void spell_golem(byte level, struct char_data *ch,
                 struct char_data *victim, struct obj_data *obj);
void spell_feeblemind(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_shillelagh(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_goodberry(byte level, struct char_data *ch,
                     struct char_data *victim, struct obj_data *obj);
void spell_flame_blade(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_animal_growth(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_insect_growth(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_creeping_death(byte level, struct char_data *ch,
                          struct char_data *victim, int dir);
void spell_commune(byte level, struct char_data *ch,
                   struct char_data *victim, struct obj_data *obj);
void spell_animal_summon(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_elemental_summoning(byte level, struct char_data *ch,
                               struct char_data *victim, int spell);
void spell_reincarnate(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_charm_veggie(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_veggie_growth(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_tree(byte level, struct char_data *ch,
                struct char_data *victim, struct obj_data *obj);
void spell_animate_rock(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_travelling(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_animal_friendship(byte level, struct char_data *ch,
                             struct char_data *victim, struct obj_data *obj);
void spell_invis_to_animals(byte level, struct char_data *ch,
                            struct char_data *victim, struct obj_data *obj);
void spell_slow_poison(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_snare(byte level, struct char_data *ch,
                 struct char_data *victim, struct obj_data *obj);
void spell_entangle(byte level, struct char_data *ch,
                    struct char_data *victim, struct obj_data *obj);
void spell_barkskin(byte level, struct char_data *ch,
                    struct char_data *victim, struct obj_data *obj);
void spell_gust_of_wind(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_silence(byte level, struct char_data *ch,
                   struct char_data *victim, struct obj_data *obj);
void spell_warp_weapon(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_heat_stuff(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_dust_devil(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_sunray(byte level, struct char_data *ch,
                  struct char_data *victim, struct obj_data *obj);
void spell_know_monster(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_find_traps(byte level, struct char_data *ch,
                      struct char_data *victim, struct obj_data *obj);
void spell_firestorm(byte level, struct char_data *ch,
                     struct char_data *victim, struct obj_data *obj);
void spell_teleport_wo_error(byte level, struct char_data *ch,
                             struct char_data *victim, struct obj_data *obj);
void spell_portal(byte level, struct char_data *ch,
                  struct char_data *tmp_ch, struct obj_data *obj);
void spell_mount(byte level, struct char_data *ch,
                 struct char_data *victim, struct obj_data *obj);
void spell_dragon_ride(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_thorn_spray(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_resist_hold(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_resist_electricity(byte level, struct char_data *ch,
                              struct char_data *victim, struct obj_data *obj);
void spell_resist_cold(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_resist_drain(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_resist_poison(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_resist_acid(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_resist_fire(byte level, struct char_data *ch,
                       struct char_data *victim, struct obj_data *obj);
void spell_resist_energy(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_resist_pierce(byte level, struct char_data *ch,
                         struct char_data *victim, struct obj_data *obj);
void spell_resist_slash(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);
void spell_resist_blunt(byte level, struct char_data *ch,
                        struct char_data *victim, struct obj_data *obj);

/* From magicutils.c */

void switch_stuff(struct char_data *giver, struct char_data *taker);
void fail_charm(struct char_data *victim, struct char_data *ch);
void fail_snare(struct char_data *victim, struct char_data *ch);
void fail_sleep(struct char_data *victim, struct char_data *ch);
void fail_para(struct char_data *victim, struct char_data *ch);
void fail_calm(struct char_data *victim, struct char_data *ch);
int item_magic_failure(struct char_data *ch, int skill_number);

/* From mobact.c */

void mobile_guardian(struct char_data *ch);
void mobile_wander(struct char_data *ch);
void mob_hunt(struct char_data *ch);
void mob_scavenge(struct char_data *ch);
void check_mobile_activity(int pulse);
void mobile_activity(struct char_data *ch);
int same_race(struct char_data *ch1, struct char_data *ch2);
int assist_friend(struct char_data *ch);
void find_a_better_weapon(struct char_data *mob);
int get_damage(struct obj_data *w, struct char_data *ch);
int get_dam_bonus(struct obj_data *w);
int get_hand_damage(struct char_data *ch);
int mob_friend(struct char_data *ch, struct char_data *f);
void pulse_mobiles(int type);
void do_script(struct char_data *ch);
int command_search(char *arg);
void command_setup();
void mob_hit(struct char_data *, struct char_data *, int);


/* From modify.c */

void string_add(struct descriptor_data *d, char *str);
void string_add_static(struct descriptor_data *d, char *str);
void quad_arg(char *arg, int *type, char *name, int *field, char *string);
void bisect_arg(char *arg, int *field, char *string);
char *one_word(char *argument, char *first_arg);
struct help_index_element *build_help_index(FILE * fl, int *num);
void page_string(struct descriptor_data *d, char *str, int keep_internal);
void show_string(struct descriptor_data *d, char *input);
void night_watchman();
void check_reboot();


/* From multiclass.c */

int get_class_level(struct char_data *ch, int class);
int count_bits(int class);
int only_class(struct char_data *ch, int class);
int has_class(struct char_data *ch, int class);
int how_many_classes(struct char_data *ch);
int best_fighting_class(struct char_data *ch);
int best_thief_class(struct char_data *ch);
int best_magic_class(struct char_data *ch);
int get_sec_max_lev(struct char_data *ch);
int get_a_level(struct char_data *ch, int which);
int get_third_max_lev(struct char_data *ch);
int get_max_level(struct char_data *ch);
int get_tot_level(struct char_data *ch);
void start_levels(struct char_data *ch);
int best_class(struct char_data *ch);


/* From reception.c */

int add_obj_cost(struct char_data *ch, struct char_data *re,
                 struct obj_data *obj, struct obj_cost *cost, int hoarder);
bool recep_offer(struct char_data *ch, struct char_data *receptionist,
                 struct obj_cost *cost);
void update_file(struct char_data *ch, struct obj_file_u *st);
void obj_store_to_char(struct char_data *ch, struct obj_file_u *st);
void load_char_objs(struct char_data *ch);
void put_obj_in_store(struct obj_data *obj, struct obj_file_u *st);
int contained_weight(struct obj_data *container);
void obj_to_store(struct obj_data *obj, struct obj_file_u *st,
                  struct char_data *ch, int delete);
void save_obj(struct char_data *ch, struct obj_cost *cost, int delete);
void update_obj_file();
void count_limited_items(struct obj_file_u *st);
void print_limited_items();
void zero_rent(struct char_data *ch);
void zero_rent_by_name(char *n);
int read_objs(FILE * fl, struct obj_file_u *st);
void write_objs(FILE * fl, struct obj_file_u *st);
void load_char_extra(struct char_data *ch);
void write_char_extra(struct char_data *ch);
void obj_store_to_room(int room, struct obj_file_u *st);
void load_room_objs(int room);
void save_room(int room);

/* From shop.c */

int is_ok(struct char_data *keeper, struct char_data *ch, int shop_nr);
int trade_with(struct obj_data *item, int shop_nr);
int shop_producing(struct obj_data *item, int shop_nr);
void shopping_buy(char *arg, struct char_data *ch,
                  struct char_data *keeper, int shop_nr);
void shopping_sell(char *arg, struct char_data *ch,
                   struct char_data *keeper, int shop_nr);
void shopping_value(char *arg, struct char_data *ch,
                    struct char_data *keeper, int shop_nr);
void shopping_list(char *arg, struct char_data *ch,
                   struct char_data *keeper, int shop_nr);
void shopping_kill(char *arg, struct char_data *ch,
                   struct char_data *keeper, int shop_nr);
void boot_the_shops();
void assign_the_shopkeepers();
int do_i_hate_you(struct char_data *v);

/* From signals.c */

void signal_setup();


/* From skills.c */

int track(struct char_data *ch, struct char_data *vict);
int dir_track(struct char_data *ch, struct char_data *vict);
void donothing();
int find_path(int in_room, int (*predicate) (), void *c_data,
              int depth, int in_zone);
int choose_exit_global(int in_room, int tgt_room, int depth);
int choose_exit_in_zone(int in_room, int tgt_room, int depth);
int go_direction(struct char_data *ch, int dir);
void slam_into_wall(struct char_data *ch, struct room_direction_data *exitp);
int spy_check(struct char_data *ch);
int remove_trap(struct char_data *ch, struct obj_data *trap);
void slip_in_climb(struct char_data *ch, int dir, int room);
void add_skill(int nr, int taught_by, int class_use, int percent);
void assign_skills();

/* From spec_assign.c */

void assign_mobiles();
void assign_objects();
void assign_rooms();


/* From spec_procs.c */
int is_target_room_p(int room, void *tgt_room);
int named_object_on_ground(int room, void *c_data);
char *how_good(int percent);
int gain_level(struct char_data *ch, int class);


/* From spec_procs2.c */

void invert(char *arg1, char *arg2);


/* From spec_procs3.c */

struct room_data *forward_square(struct room_data *room);
struct room_data *back_square(struct room_data *room);
struct room_data *left_square(struct room_data *room);
struct room_data *right_square(struct room_data *room);
struct room_data *forward_left_square(struct room_data *room);
struct room_data *forward_right_square(struct room_data *room);
struct room_data *back_right_square(struct room_data *room);
struct room_data *back_left_square(struct room_data *room);
struct char_data *square_contains_enemy(struct room_data *square);
int square_contains_friend(struct room_data *square);
int square_empty(struct room_data *square);
/* From spell_parser.c */

int SPELL_LEVEL(struct char_data *ch, int sn);
void affect_update(int pulse);
void clone_char(struct char_data *ch);
bool circle_follow(struct char_data *ch, struct char_data *victim);
void stop_follower(struct char_data *ch);
void die_follower(struct char_data *ch);
void add_follower(struct char_data *ch, struct char_data *leader);
void say_spell(struct char_data *ch, int si);
bool saves_spell(struct char_data *ch, sh_int save_type);
bool imp_save_spell(struct char_data *ch, sh_int save_type, int mod);
char *skip_spaces(char *string);
void assign_spell_pointers();
void spell_wear_off_soon(int s, struct char_data *ch);
void spell_wear_off(int s, struct char_data *ch);
void check_decharm(struct char_data *ch);
int check_falling(struct char_data *ch);
void check_drowning(struct char_data *ch);
void check_falling_obj(struct obj_data *obj, int room);
void check_nature(struct char_data *i);
int is_intrinsic(struct char_data *ch, int spl);
int cast_intrinsic(struct char_data *ch, int spl);

/* From spells1.c */

void cast_burning_hands(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *victim, struct obj_data *tar_obj);
void cast_call_lightning(byte level, struct char_data *ch, char *arg, int type,
                         struct char_data *victim, struct obj_data *tar_obj);
void cast_chill_touch(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *victim, struct obj_data *tar_obj);
void cast_shocking_grasp(byte level, struct char_data *ch, char *arg, int type,
                         struct char_data *victim, struct obj_data *tar_obj);
void cast_colour_spray(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *victim, struct obj_data *tar_obj);
void cast_earthquake(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *victim, struct obj_data *tar_obj);
void cast_energy_drain(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *victim, struct obj_data *tar_obj);
void cast_fireball(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *victim, struct obj_data *tar_obj);
void cast_harm(byte level, struct char_data *ch, char *arg, int type,
               struct char_data *victim, struct obj_data *tar_obj);
void cast_lightning_bolt(byte level, struct char_data *ch, char *arg, int type,
                         struct char_data *victim, struct obj_data *tar_obj);
void cast_acid_blast(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *victim, struct obj_data *tar_obj);
void cast_cone_of_cold(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *victim, struct obj_data *tar_obj);
void cast_ice_storm(byte level, struct char_data *ch, char *arg, int type,
                    struct char_data *victim, struct obj_data *tar_obj);
void cast_meteor_swarm(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *victim, struct obj_data *tar_obj);
void cast_flamestrike(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *victim, struct obj_data *tar_obj);
void cast_magic_missile(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *victim, struct obj_data *tar_obj);
void cast_cause_light(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *victim, struct obj_data *tar_obj);
void cast_cause_serious(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *victim, struct obj_data *tar_obj);
void cast_cause_critic(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *victim, struct obj_data *tar_obj);
void cast_green_slime(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *victim, struct obj_data *tar_obj);


/* From spells2.c */

void cast_resurrection(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_major_track(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_minor_track(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_mana(byte level, struct char_data *ch, char *arg, int type,
               struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_armor(byte level, struct char_data *ch, char *arg, int type,
                struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_stone_skin(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_astral_walk(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_teleport(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_bless(byte level, struct char_data *ch, char *arg, int type,
                struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_infravision(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_true_seeing(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_blindness(byte level, struct char_data *ch, char *arg, int type,
                    struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_light(byte level, struct char_data *ch, char *arg, int type,
                struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_cont_light(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_web(byte level, struct char_data *ch, char *arg, int type,
              struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_clone(byte level, struct char_data *ch, char *arg, int type,
                struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_control_weather(byte level, struct char_data *ch, char *arg,
                          int type, struct char_data *tar_ch,
                          struct obj_data *tar_obj);
void cast_create_food(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_create_water(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_water_breath(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_flying(byte level, struct char_data *ch, char *arg, int type,
                 struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_fly_group(byte level, struct char_data *ch, char *arg, int type,
                    struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_heroes_feast(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_cure_blind(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_cure_critic(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_cure_light(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_cure_serious(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_refresh(byte level, struct char_data *ch, char *arg, int type,
                  struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_second_wind(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_shield(byte level, struct char_data *ch, char *arg, int type,
                 struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_curse(byte level, struct char_data *ch, char *arg, int type,
                struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_detect_evil(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_detect_invisibility(byte level, struct char_data *ch, char *arg,
                              int type, struct char_data *tar_ch,
                              struct obj_data *tar_obj);
void cast_detect_magic(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_detect_poison(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_dispel_evil(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_dispel_good(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_faerie_fire(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_enchant_weapon(byte level, struct char_data *ch, char *arg, int type,
                         struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_enchant_armor(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_heal(byte level, struct char_data *ch, char *arg, int type,
               struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_invisibility(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_locate_object(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_poison(byte level, struct char_data *ch, char *arg, int type,
                 struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_protection_from_evil(byte level, struct char_data *ch, char *arg,
                               int type, struct char_data *tar_ch,
                               struct obj_data *tar_obj);
void cast_remove_curse(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_remove_poison(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_remove_paralysis(byte level, struct char_data *ch, char *arg,
                           int type, struct char_data *tar_ch,
                           struct obj_data *tar_obj);
void cast_sanctuary(byte level, struct char_data *ch, char *arg, int type,
                    struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_fireshield(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_sleep(byte level, struct char_data *ch, char *arg, int type,
                struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_strength(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_ventriloquate(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_word_of_recall(byte level, struct char_data *ch, char *arg, int type,
                         struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_summon(byte level, struct char_data *ch, char *arg, int type,
                 struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_charm_person(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_charm_monster(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_sense_life(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_identify(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_dragon_breath(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *tar_ch, struct obj_data *potion);
void cast_knock(byte level, struct char_data *ch, char *arg, int type,
                struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_know_alignment(byte level, struct char_data *ch, char *arg, int type,
                         struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_weakness(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_dispel_magic(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_animate_dead(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_succor(byte level, struct char_data *ch, char *arg, int type,
                 struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_paralyze(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_fear(byte level, struct char_data *ch, char *arg, int type,
               struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_turn(byte level, struct char_data *ch, char *arg, int type,
               struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_faerie_fog(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *victim, struct obj_data *tar_obj);
void cast_poly_self(byte level, struct char_data *ch, char *arg, int type,
                    struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_minor_creation(byte level, struct char_data *ch, char *arg, int type,
                         struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_conjure_elemental(byte level, struct char_data *ch, char *arg,
                            int type, struct char_data *tar_ch,
                            struct obj_data *tar_obj);
void cast_cacaodemon(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_mon_sum1(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_mon_sum2(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_mon_sum3(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_mon_sum4(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_mon_sum5(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_mon_sum6(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_mon_sum7(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_tree_travel(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_speak_with_plants(byte level, struct char_data *ch, char *arg,
                            int type, struct char_data *tar_ch,
                            struct obj_data *tar_obj);
void cast_transport_via_plant(byte level, struct char_data *ch, char *arg,
                              int type, struct char_data *tar_ch,
                              struct obj_data *tar_obj);
void cast_haste(byte level, struct char_data *ch, char *arg, int type,
                struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_slow(byte level, struct char_data *ch, char *arg, int type,
               struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_reincarnate(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_changestaff(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_pword_kill(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_pword_blind(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_chain_lightn(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_scare(byte level, struct char_data *ch, char *arg, int type,
                struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_familiar(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_aid(byte level, struct char_data *ch, char *arg, int type,
              struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_holyword(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_unholyword(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_golem(byte level, struct char_data *ch, char *arg, int type,
                struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_command(byte level, struct char_data *ch, char *arg, int type,
                  struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_change_form(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_shillelagh(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_goodberry(byte level, struct char_data *ch, char *arg, int type,
                    struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_flame_blade(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_animal_growth(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_insect_growth(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_creeping_death(byte level, struct char_data *ch, char *arg, int type,
                         struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_commune(byte level, struct char_data *ch, char *arg, int type,
                  struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_feeblemind(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_animal_summon_1(byte level, struct char_data *ch, char *arg,
                          int type, struct char_data *tar_ch,
                          struct obj_data *tar_obj);
void cast_animal_summon_2(byte level, struct char_data *ch, char *arg,
                          int type, struct char_data *tar_ch,
                          struct obj_data *tar_obj);
void cast_animal_summon_3(byte level, struct char_data *ch, char *arg,
                          int type, struct char_data *tar_ch,
                          struct obj_data *tar_obj);
void cast_fire_servant(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_earth_servant(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_water_servant(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_wind_servant(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_veggie_growth(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_charm_veggie(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_tree(byte level, struct char_data *ch, char *arg, int type,
               struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_animate_rock(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_travelling(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_animal_friendship(byte level, struct char_data *ch, char *arg,
                            int type, struct char_data *tar_ch,
                            struct obj_data *tar_obj);
void cast_invis_to_animals(byte level, struct char_data *ch, char *arg,
                           int type, struct char_data *tar_ch,
                           struct obj_data *tar_obj);
void cast_slow_poison(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_entangle(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_snare(byte level, struct char_data *ch, char *arg, int type,
                struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_gust_of_wind(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_barkskin(byte level, struct char_data *ch, char *arg, int type,
                   struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_warp_weapon(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_calm(byte level, struct char_data *ch, char *arg, int type,
               struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_heat_stuff(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_sunray(byte level, struct char_data *ch, char *arg, int type,
                 struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_find_traps(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_firestorm(byte level, struct char_data *ch, char *arg, int type,
                    struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_dust_devil(byte level, struct char_data *ch, char *arg, int type,
                     struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_know_monster(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_silence(byte level, struct char_data *ch, char *arg, int type,
                  struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_dragon_ride(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_mount(byte level, struct char_data *ch, char *arg, int type,
                struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_sending(byte level, struct char_data *ch, char *arg, int type,
                  struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_portal(byte level, struct char_data *ch, char *arg, int type,
                 struct char_data *tar_ch, struct obj_data *tar_obj);
void cast_teleport_wo_error(byte level, struct char_data *ch, char *arg,
                            int type, struct char_data *tar_ch,
                            struct obj_data *tar_obj);
void cast_thorn_spray(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *victim, struct obj_data *tar_obj);
void cast_resist_hold(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *victim, struct obj_data *tar_obj);
void cast_resist_electricity(byte level, struct char_data *ch, char *arg,
                             int type, struct char_data *victim,
                             struct obj_data *tar_obj);
void cast_resist_cold(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *victim, struct obj_data *tar_obj);
void cast_resist_drain(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *victim, struct obj_data *tar_obj);
void cast_resist_poison(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *victim, struct obj_data *tar_obj);
void cast_resist_acid(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *victim, struct obj_data *tar_obj);
void cast_resist_fire(byte level, struct char_data *ch, char *arg, int type,
                      struct char_data *victim, struct obj_data *tar_obj);
void cast_resist_energy(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *victim, struct obj_data *tar_obj);
void cast_resist_pierce(byte level, struct char_data *ch, char *arg, int type,
                        struct char_data *victim, struct obj_data *tar_obj);
void cast_resist_slash(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *victim, struct obj_data *tar_obj);
void cast_resist_blunt(byte level, struct char_data *ch, char *arg, int type,
                       struct char_data *victim, struct obj_data *tar_obj);


/* From utility.c */
int char_array_size(char *thingie[]);
int ego_blade_save(struct char_data *ch);
int MIN(int a, int b);
int MAX(int a, int b);
int get_item_class_restrictions(struct obj_data *obj);
int CAN_SEE(struct char_data *s, struct char_data *o);
int CAN_SEE_OBJ(struct char_data *ch, struct obj_data *obj);
int exit_ok(struct room_direction_data *exit, struct room_data **rpp);
int mob_vnum(struct char_data *c);
int obj_vnum(struct obj_data *o);
void zwrite(FILE * fp, char cmd, int tf, int arg1, int arg2, int arg3,
            char *desc);
void rec_zwrite_obj(FILE * fp, struct obj_data *o);
FILE *make_zone_file(struct char_data *c);
int weapon_immune(struct char_data *ch);
unsigned is_immune(struct char_data *ch, int bit);
unsigned is_resist(struct char_data *ch, int bit);
unsigned is_susc(struct char_data *ch, int bit);
int number(int from, int to);
int dice(int number, int size);
int scan_number(char *text, int *rval);
int str_cmp(char *arg1, char *arg2);
int strn_cmp(char *arg1, char *arg2, int n);
void slog(char *str);
void sprintbit(unsigned long vektor, char *names[], char *result);
void sprinttype(int type, char *names[], char *result);
struct time_info_data real_time_passed(time_t t2, time_t t1);
struct time_info_data mud_time_passed(time_t t2, time_t t1);
void mud_time_passed2(time_t t2, time_t t1, struct time_info_data *t);
void age2(struct char_data *ch, struct time_info_data *g);
struct time_info_data age(struct char_data *ch);
char getall(char *name, char *newname);
int getabunch(char *name, char *newname);
int determine_exp(struct char_data *mob, int exp_flags);
void down_river(int pulse);
void room_save(struct char_data *ch, int start, int end);
void room_load(struct char_data *ch, int start, int end);
int is_humanoid(struct char_data *ch);
int is_rideable(struct char_data *ch);
int is_animal(struct char_data *ch);
int is_veggie(struct char_data *ch);
int is_undead(struct char_data *ch);
int is_lycanthrope(struct char_data *ch);
int is_diabolic(struct char_data *ch);
int is_reptile(struct char_data *ch);
int has_hands(struct char_data *ch);
int is_person(struct char_data *ch);
int is_giantish(struct char_data *ch);
int is_small(struct char_data *ch);
int is_giant(struct char_data *ch);
int is_extra_planar(struct char_data *ch);
int is_other(struct char_data *ch);
int is_godly(struct char_data *ch);
void set_hunting(struct char_data *ch, struct char_data *tch);
void call_for_guard
  (struct char_data *ch, struct char_data *vict, int lev, int area);
void stand_up(struct char_data *ch);
void make_nifty_attack(struct char_data *ch);
void fighter_move(struct char_data *ch);
void monk_move(struct char_data *ch);
void develop_hatred(struct char_data *ch, struct char_data *v);
int has_object(struct char_data *ch, int ob_num);
int room_of_object(struct obj_data *obj);
struct char_data *char_holding(struct obj_data *obj);
int rec_comp_obj_num(struct obj_data *o, int obj_num);
void restore_char(struct char_data *ch);
void rem_all_affects(struct char_data *ch);
int check_for_blocked_move
  (struct char_data *ch, int cmd, char *arg, int room, int dir, int class);
void teleport_pulse_stuff(int pulse);
void river_pulse_stuff(int pulse);
int apply_soundproof(struct char_data *ch);
int check_soundproof(struct char_data *ch);
int mob_count_in_room(struct char_data *list);
void *mymalloc(long size);
void space_for_skills(struct char_data *ch);
int count_lims(struct obj_data *obj);
char *lower(char *s);
int getfree_aff_slot(struct obj_data *obj);
void set_racial_stuff(struct char_data *mob);
int check_nomagic(struct char_data *ch, char *msg_ch, char *msg_rm);
int num_charmed_followers_in_room(struct char_data *ch);
struct char_data *find_mob_diff_zone_same_race(struct char_data *ch);
int no_summon(struct char_data *ch);
int get_new_race(void);
int get_approx(int num, int perc);
int mount_ego_check(struct char_data *ch, struct char_data *horse);
int ride_check(struct char_data *ch, int mod);
void fall_off_mount(struct char_data *ch, struct char_data *h);
int eq_w_bits(struct char_data *ch, int bits);
int inv_w_bits(struct char_data *ch, int bits);
int has_w_bits(struct char_data *ch, int bits);
void learn_from_mistake(struct char_data *ch, int sknum, int silent, int max);
int get_sum_race_max_lev_in_room(struct char_data *ch);
int too_many_followers(struct char_data *ch);
int follow_time(struct char_data *ch);
int item_align_clash(struct char_data *ch, struct obj_data *obj);
int item_ego_clash(struct char_data *ch, struct obj_data *obj, int bon);
void increment_zone_nr(int nr);
int is_dark_outside(struct room_data *rp);
int GET_OBJ_EGO(struct obj_data *obj);
int GET_EGO(struct char_data *ch);
int is_in_same_zone(struct char_data *ch, struct char_data *v);
int get_plane(struct char_data *ch);
int is_on_same_plane(struct char_data *ch, struct char_data *v);
int is_on_pmp(int room_nr);
void improve_prefered_stat(struct char_data *ch, int num, byte onelifer);
int is_goblinoid(struct char_data *ch);
int is_article(char *c);
void change_strength(struct char_data *ch, int delta);
char *movement_type(struct char_data *ch, bool enter);
char in_group(struct char_data *ch1, struct char_data *ch2);

/* From weather.c */

void weather_and_time(int mode);
void another_hour(int mode);
void change_season(int month);
void weather_change();
void change_weather(int change);
void get_month(int month);
void switch_light(byte why);
void remove_sun_blind(struct char_data *ch);
void sun_blind(struct char_data *ch);
void sun_problem_check(struct char_data *ch);
void global_sun_problem_check(bool light);

/* From create.c */

void change_room_flags(struct room_data *rp, struct char_data *ch, char *arg,
                       int type);
void change_room_desc(struct room_data *rp, struct char_data *ch, char *arg,
                      int type);
void update_room_menu(struct char_data *ch);
void room_edit(struct char_data *ch, char *arg);
void change_room_name(struct room_data *rp, struct char_data *ch, char *arg,
                      int type);
void change_room_type(struct room_data *rp, struct char_data *ch, char *arg,
                      int type);
void change_exit_dir(struct room_data *rp, struct char_data *ch, char *arg,
                     int type);
void change_exit_number(struct room_data *rp, struct char_data *ch, char *arg,
                        int type);
void change_key_number(struct room_data *rp, struct char_data *ch, char *arg,
                       int type);
void add_exit_to_room(struct room_data *rp, struct char_data *ch, char *arg,
                      int type);
void delete_exit(struct room_data *rp, struct char_data *ch, char *arg,
                 int type);


/* From parser.c */

void generate_hash();
void add_node_tail(NODE * n, int length, int radix);
NODE *search_for_node_by_name(NODE * head, char *name, int length);
void init_radix();
NODE *find_valid_command(char *name);

/* from intrinsics.c */
void mindflayer_attack(struct char_data *ch, struct char_data *v);
void vampire_bite(struct char_data *ch, struct char_data *v);
int veggie_gain_mods(struct char_data *ch, int gain, bool msgs);
int vamp_gain_mods(struct char_data *ch, int gain, bool msgs);

/* From hoard.c */
int no__hoard(struct char_data *ch, struct char_data *re,
              struct obj_data *obj, struct obj_cost *cost);

/*  */
/* All Done! (yay!) */

#endif
