/*
  SillyMUD Distribution V1.1b             (c) 1993 SillyMUD Developement
 
  See license.doc for distribution terms.   SillyMUD is based on DIKUMUD
*/
#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "protos.h"
#include "db.h"
#include "utility.h"

#define NEW_ZONE_SYSTEM

/**************************************************************************
*  declarations of most of the 'global' variables                         *
************************************************************************ */
int top_of_scripts = 0;
int top_of_world = 0;           /* ref to the top element of world */
#if HASH
struct hash_header room_db;
#else
struct room_data *room_db[WORLD_SIZE];
#endif

struct obj_data *object_list = 0;       /* the global linked list of obj's */
struct char_data *character_list = 0;   /* global l-list of chars          */

struct zone_data *zone_table;   /* table of reset data             */
int top_of_zone_table = 0;
struct message_list fight_messages[MAX_MESSAGES];       /* fighting messages   */
struct player_index_element *player_table = 0;  /* index to player file   */
int top_of_p_table = 0;         /* ref to top of table             */
int top_of_p_file = 0;
long total_bc = 0;
long room_count = 0;
long mob_count = 0;
long obj_count = 0;
long total_mbc = 0;
long total_obc = 0;
struct figurine_data figurine[255];
int fig_count = 0;

/*
**  distributed monster stuff
*/
int mob_tick_count = 0;
char wmotd[MAX_STRING_LENGTH];
char credits[MAX_STRING_LENGTH];        /* the Credits List                */
char news[MAX_STRING_LENGTH];   /* the news                        */
char motd[MAX_STRING_LENGTH];   /* the messages of today           */
char help[MAX_STRING_LENGTH];   /* the main help page              */
char info[MAX_STRING_LENGTH];   /* the info text                   */
char wizlist[MAX_STRING_LENGTH * 2];    /* the wizlist                     */
char login[MAX_STRING_LENGTH];


FILE *mob_f,                    /* file containing mob prototypes  */
 *obj_f,                        /* obj prototypes                  */
 *help_fl;                      /* file for help texts (HELP <kwd>) */

struct mob_index_data *mob_index;   /* index table for mobile file     */
struct obj_index_data *obj_index;   /* index table for object file     */
struct help_index_element *help_index = 0;

int top_of_mobt = 0;            /* top of mobile index table       */
int top_of_objt = 0;            /* top of object index table       */
int top_of_helpt;               /* top of help index table         */

struct time_info_data time_info;        /* the infomation about the time   */
struct weather_data weather_info;       /* the infomation about the weather */

int saved_rooms[29000];
int number_of_saved_rooms = 0;
extern struct descriptor_data *descriptor_list;

/* internal function */
int verify_mob(struct char_data *ch);


/*************************************************************************
*  routines for booting the system                                       *
*********************************************************************** */


/* body of the booting system */
void boot_db() {
  int i;
  extern int no_specials;
  struct _index_data *base_mob_idx, *base_obj_idx;

  log_msg("Boot db -- BEGIN.");

  log_msg("Resetting the game time:");
  reset_time();

  ensure_file_exists(PLAYER_FILE);
  ensure_file_exists(WIZLIST_FILE);
  ensure_file_exists(BUG_FILE);
  ensure_file_exists(IDEA_FILE);
  ensure_file_exists(KILL_FILE);
  ensure_file_exists(TYPO_FILE);
  ensure_file_exists(RHYODIN_FILE);

  log_msg("Reading newsfile, credits, help-page, info and motd.");
  file_to_string(NEWS_FILE, news);
  file_to_string(CREDITS_FILE, credits);
  file_to_string(MOTD_FILE, motd);
  file_to_string("wizmotd", wmotd);
  file_to_string(HELP_PAGE_FILE, help);
  file_to_string(INFO_FILE, info);
  file_to_string(WIZLIST_FILE, wizlist);
  file_to_string("login", login);

  log_msg("Initializing Script Files.");

  /* some machines are pre-allocation specific when dealing with realloc */
  script_data = (struct scripts *)malloc(sizeof(struct scripts));
  command_setup();
  init_scripts();
  log_msg("Opening mobile, object and help files.");
  if (!(mob_f = fopen(MOB_FILE, "r"))) {
    perror("boot");
    assert(0);
  }

  if (!(obj_f = fopen(OBJ_FILE, "r"))) {
    perror("boot");
    assert(0);
  }
  if (!(help_fl = fopen(HELP_KWRD_FILE, "r")))
    log_msg("   Could not open help file.");
  else
    help_index = build_help_index(help_fl, &top_of_helpt);

  log_msg("Booting Figurine Table.");
  boot_figurines();

  log_msg("Loading zone table.");
  boot_zones();

  log_msg("Loading rooms.");
  boot_world();


  log_msg("Generating index tables for mobile and object files.");
  base_mob_idx = generate_indices(mob_f, &top_of_mobt);
  mob_index = make_mob_indices(base_mob_idx, top_of_mobt);
  base_obj_idx = generate_indices(obj_f, &top_of_objt);
  obj_index = make_obj_indices(base_obj_idx, top_of_objt);

  log_msg("Renumbering zone table.");
  renum_zone_table();
  log_msg("Generating player index.");
  build_player_index();

  log_msg("Loading fight messages.");
  load_messages();

  log_msg("Loading social messages.");
  boot_social_messages();

  log_msg("Loading pose messages.");
  boot_pose_messages();

  log_msg("Assigning function pointers:");
  if (!no_specials) {
    log_msg("   Mobiles.");
    assign_mobiles();
    log_msg("   Objects.");
    assign_objects();
    log_msg("   Room.");
    assign_rooms();
  }

  log_msg("   Commands.");
  assign_command_pointers();
  log_msg("   Spells.");
  assign_spell_pointers();
  log_msg("   Skills.");
  assign_skills();

  log_msg("Updating characters with saved items:");
  update_obj_file();
  log_msg("Loading saved rooms.");
  reload_rooms();

#if LIMITED_ITEMS
  print_limited_items();
#endif
  for (i = 0; i <= top_of_zone_table; i++) {
    char *s;
    int d, e;
    s = zone_table[i].name;
    d = (i ? (zone_table[i - 1].top + 1) : 0);
    e = zone_table[i].top;
    log_msgf("Performing boot-time init of %s (rooms %d-%d)",
             s, d, e);
    zone_table[i].start = 0;


    if (i == 0) {
      log_msgf("Performing boot-time reload of static mobs");
      reset_zone(0);

    }

    if (i == 1) {
      log_msgf("Automatic initialization of  %s\n", s);
      reset_zone(1);
    }
  }

  reset_q.head = reset_q.tail = 0;

  log_msg("Boot db -- DONE.");
}


/* reset the time in the game from file */
/* reset the time in the game from file */
void reset_time() {
  extern unsigned char moontype;
  long beginning_of_time = 650336715;



  struct time_info_data mud_time_passed(time_t t2, time_t t1);

  time_info = mud_time_passed(time(0), beginning_of_time);

  moontype = time_info.day;

  switch (time_info.hours) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
    {
      weather_info.sunlight = SUN_DARK;
      switch_light(MOON_SET);
      break;
    }
  case 5:
  case 6:
    {
      weather_info.sunlight = SUN_RISE;
      switch_light(SUN_RISE);
      break;
    }
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
  case 15:
  case 16:
  case 17:
  case 18:
    {
      weather_info.sunlight = SUN_LIGHT;
      break;
    }
  case 19:
  case 20:
    {
      weather_info.sunlight = SUN_SET;
      break;
    }
  case 21:
  case 22:
  case 23:
  default:
    {
      switch_light(SUN_DARK);
      weather_info.sunlight = SUN_DARK;
      break;
    }
  }

  log_msgf("   Current Gametime: %dH %dD %dM %dY.",
           time_info.hours, time_info.day, time_info.month, time_info.year);

  weather_info.pressure = 960;
  if ((time_info.month >= 7) && (time_info.month <= 12))
    weather_info.pressure += dice(1, 50);
  else
    weather_info.pressure += dice(1, 80);

  weather_info.change = 0;

  if (weather_info.pressure <= 980) {
    if ((time_info.month >= 3) && (time_info.month <= 14))
      weather_info.sky = SKY_LIGHTNING;
    else
      weather_info.sky = SKY_LIGHTNING;
  }
  else if (weather_info.pressure <= 1000) {
    if ((time_info.month >= 3) && (time_info.month <= 14))
      weather_info.sky = SKY_RAINING;
    else
      weather_info.sky = SKY_RAINING;
  }
  else if (weather_info.pressure <= 1020) {
    weather_info.sky = SKY_CLOUDY;
  }
  else {
    weather_info.sky = SKY_CLOUDLESS;
  }
}



/* update the time file */
void update_time() {
  return;
}



struct wizs {
  char name[20];
  int level;
};

int intcomp(struct wizs *j, struct wizs *k) {
  return (k->level - j->level);
}

         /* generate index table for the player file */
void build_player_index() {
  int nr = -1, i;
  struct char_file_u dummy;
  FILE *fl;

  char buf[MAX_STRING_LENGTH * 2];

  register int max = 0, j;
  int center;

  struct wizlistgen list_wiz;

  for (j = 0; j <= 11; j++)
    list_wiz.number[j] = 0;

  if (!(fl = fopen(PLAYER_FILE, "rb+"))) {
    perror("build player index");
    exit(0);
  }

  for (; !feof(fl);) {
    fread(&dummy, sizeof(struct char_file_u), 1, fl);
    if (!feof(fl)) {            /* new record */
      /* Create new entry in the list */
      if (nr == -1) {
        CREATE(player_table, struct player_index_element, 1);
        nr = 0;
      }
      else {
        if (!(player_table = (struct player_index_element *)
              realloc(player_table, (++nr + 1) *
                      sizeof(struct player_index_element)))) {
          perror("generate index");
          exit(0);
        }
      }

      player_table[nr].nr = nr;

      CREATE(player_table[nr].name, char, strlen(dummy.name) + 1);
      for (i = 0; (*(player_table[nr].name + i) =
                   LOWER(*(dummy.name + i))) != '\0'; i++);

      for (i = 0; i <= 5; i++)
        if (dummy.level[i] >= 51) {
          log_msgf("GOD: %s, Levels [%d][%d][%d][%d][%d][%d]", dummy.name,
                   dummy.level[0], dummy.level[1], dummy.level[2],
                   dummy.level[3], dummy.level[4], dummy.level[5]);

          max = 0;
          for (j = 0; j < MAX_CLASS; j++)
            if (dummy.level[j] > max) {
              max = dummy.level[j];
            }
          list_wiz.lookup[max - 51].stuff[list_wiz.number[max - 51]].name =
            (char *)strdup(dummy.name);
          list_wiz.lookup[max - 51].stuff[list_wiz.number[max - 51]].title =
            (char *)strdup(dummy.title);
          list_wiz.number[max - 51]++;
          break;
        }

    }
  }


  fclose(fl);

  top_of_p_table = nr;

  top_of_p_file = top_of_p_table;

  log_msg("Began Wizlist Generation.");

  SPRINTF(wizlist, "\033[2J\033[0;0H\n\r\n\r");
  SPRINTF(buf, "-* Creator and Supreme Being [%d/1] *-\n\r",
          list_wiz.number[10]);


  center = (38 - (int)(str_len(buf) / 2));
  log_msg("center computed.");
  for (i = 0; i <= center; i++)
    strcat(wizlist, " ");

  strcat(wizlist, buf);


  for (i = 0; i < list_wiz.number[10]; i++) {
    SPRINTF(buf, "%s %s\n\r", list_wiz.lookup[10].stuff[i].name,
            list_wiz.lookup[10].stuff[i].title);

    center = 38 - (int)(str_len(buf) / 2);
    for (j = 0; j <= center; j++)
      strcat(wizlist, " ");
    strcat(wizlist, buf);
  }

  strcat(wizlist, "\n\r\n\r");
  log_msg("Creator Generated.");

  SPRINTF(buf, "-* Designers/Administrators [%d/2] *-\n\r",
          list_wiz.number[9]);
  center = 38 - (int)(str_len(buf) / 2);

  for (i = 0; i <= center; i++)
    strcat(wizlist, " ");
  strcat(wizlist, buf);

  for (i = 0; i < list_wiz.number[9]; i++) {
    SPRINTF(buf, "%s %s\n\r", list_wiz.lookup[9].stuff[i].name,
            list_wiz.lookup[9].stuff[i].title);
    center = 38 - (int)(str_len(buf) / 2);
    for (j = 0; j <= center; j++)
      strcat(wizlist, " ");
    strcat(wizlist, buf);
  }

  strcat(wizlist, "\n\r\n\r");

  SPRINTF(buf, "-* Implementors [%d/5] *-\n\r", list_wiz.number[8]);
  center = 38 - (int)(str_len(buf) / 2);

  for (i = 0; i <= center; i++)
    strcat(wizlist, " ");
  strcat(wizlist, buf);

  for (i = 0; i < list_wiz.number[8]; i++) {
    SPRINTF(buf, "%s %s\n\r", list_wiz.lookup[8].stuff[i].name,
            list_wiz.lookup[8].stuff[i].title);
    center = 38 - (int)(str_len(buf) / 2);
    for (j = 0; j <= center; j++)
      strcat(wizlist, " ");
    strcat(wizlist, buf);
  }

  strcat(wizlist, "\n\r\n\r");
  log_msg("Implementors Generated.");

  SPRINTF(buf, "-* Gods of Final Judgement [%d/6] *-\n\r", list_wiz.number[7]);
  center = 38 - (int)(str_len(buf) / 2);

  for (i = 0; i <= center; i++)
    strcat(wizlist, " ");
  strcat(wizlist, buf);

  for (i = 0; i < list_wiz.number[7]; i++) {
    SPRINTF(buf, "%s %s\n\r", list_wiz.lookup[7].stuff[i].name,
            list_wiz.lookup[7].stuff[i].title);
    center = 38 - (int)(str_len(buf) / 2);
    for (j = 0; j <= center; j++)
      strcat(wizlist, " ");
    strcat(wizlist, buf);
  }

  strcat(wizlist, "\n\r\n\r");
  log_msg("Gods of Final Judgement Generated.");

  SPRINTF(buf, "-* Gods of Judgement [%d/8] *-\n\r", list_wiz.number[6]);
  center = 38 - (int)(str_len(buf) / 2);

  for (i = 0; i <= center; i++)
    strcat(wizlist, " ");
  strcat(wizlist, buf);

  for (i = 0; i < list_wiz.number[6]; i++) {
    SPRINTF(buf, "%s %s\n\r", list_wiz.lookup[6].stuff[i].name,
            list_wiz.lookup[6].stuff[i].title);
    center = 38 - (int)(str_len(buf) / 2);
    for (j = 0; j <= center; j++)
      strcat(wizlist, " ");
    strcat(wizlist, buf);
  }

  strcat(wizlist, "\n\r\n\r");


  SPRINTF(buf, "-* Greater Gods [%d/10] *-\n\r", list_wiz.number[5]);
  center = 38 - (int)(str_len(buf) / 2);

  for (i = 0; i <= center; i++)
    strcat(wizlist, " ");
  strcat(wizlist, buf);

  for (i = 0; i < list_wiz.number[5]; i++) {
    SPRINTF(buf, "%s %s\n\r", list_wiz.lookup[5].stuff[i].name,
            list_wiz.lookup[5].stuff[i].title);
    center = 38 - (int)(str_len(buf) / 2);
    for (j = 0; j <= center; j++)
      strcat(wizlist, " ");
    strcat(wizlist, buf);
  }

  strcat(wizlist, "\n\r\n\r");


  SPRINTF(buf, "-* Gods [%d/12] *-\n\r", list_wiz.number[4]);
  center = 38 - (int)(str_len(buf) / 2);

  for (i = 0; i <= center; i++)
    strcat(wizlist, " ");
  strcat(wizlist, buf);

  for (i = 0; i < list_wiz.number[4]; i++) {
    SPRINTF(buf, "%s %s\n\r", list_wiz.lookup[4].stuff[i].name,
            list_wiz.lookup[4].stuff[i].title);
    center = 38 - (int)(str_len(buf) / 2);
    for (j = 0; j <= center; j++)
      strcat(wizlist, " ");
    strcat(wizlist, buf);
  }

  strcat(wizlist, "\n\r\n\r");


  SPRINTF(buf, "-* Demi-Gods [%d/14] *-\n\r", list_wiz.number[3]);
  center = 38 - (int)(str_len(buf) / 2);

  for (i = 0; i <= center; i++)
    strcat(wizlist, " ");
  strcat(wizlist, buf);

  for (i = 0; i < list_wiz.number[3]; i++) {
    SPRINTF(buf, "%s %s\n\r", list_wiz.lookup[3].stuff[i].name,
            list_wiz.lookup[3].stuff[i].title);
    center = 38 - (int)(str_len(buf) / 2);
    for (j = 0; j <= center; j++)
      strcat(wizlist, " ");
    strcat(wizlist, buf);
  }

  strcat(wizlist, "\n\r\n\r");


  SPRINTF(buf, "-* Saints [%d/30] *-\n\r", list_wiz.number[2]);
  center = 38 - (int)(str_len(buf) / 2);

  for (i = 0; i <= center; i++)
    strcat(wizlist, " ");
  strcat(wizlist, buf);

  for (i = 0; i < list_wiz.number[2]; i++) {
    SPRINTF(buf, "%s %s\n\r", list_wiz.lookup[2].stuff[i].name,
            list_wiz.lookup[2].stuff[i].title);
    center = 38 - (int)(str_len(buf) / 2);
    for (j = 0; j <= center; j++)
      strcat(wizlist, " ");
    strcat(wizlist, buf);
  }

  strcat(wizlist, "\n\r\n\r");


  SPRINTF(buf, "-* Immortals of Creation [%d/50] *-\n\r", list_wiz.number[1]);
  center = 38 - (int)(str_len(buf) / 2);

  for (i = 0; i <= center; i++)
    strcat(wizlist, " ");
  strcat(wizlist, buf);

  for (i = 0; i < list_wiz.number[1]; i++) {
    SPRINTF(buf, "%s %s\n\r", list_wiz.lookup[1].stuff[i].name,
            list_wiz.lookup[1].stuff[i].title);
    center = 38 - (int)(str_len(buf) / 2);
    for (j = 0; j <= center; j++)
      strcat(wizlist, " ");
    strcat(wizlist, buf);
  }

  strcat(wizlist, "\n\r\n\r");


  SPRINTF(buf, "-* Immortals [%d/~] *-\n\r", list_wiz.number[0]);
  center = 38 - (int)(str_len(buf) / 2);

  for (i = 0; i <= center; i++)
    strcat(wizlist, " ");
  strcat(wizlist, buf);

  for (i = 0; i < list_wiz.number[0]; i++) {
    SPRINTF(buf, "%s %s\n\r", list_wiz.lookup[0].stuff[i].name,
            list_wiz.lookup[0].stuff[i].title);
    center = 38 - (int)(str_len(buf) / 2);
    for (j = 0; j <= center; j++)
      strcat(wizlist, " ");
    strcat(wizlist, buf);
  }

  strcat(wizlist, "\n\r\n\r");
  max = 0;
  for (i = 0; i <= 9; i++)
    max += list_wiz.number[i];
  SPRINTF(buf, "Total Gods: %d\n\r\n\r", max);
  strcat(wizlist, buf);

  return;
}


struct mob_index_data *make_mob_indices(struct _index_data *base_idx,
                                        int top) {
  struct mob_index_data *mob_idx = NULL;

  if (base_idx) {
    CREATE(mob_idx, struct mob_index_data, top + 1);

    for (int i = 0; i < top + 1; i++) {
      mob_idx[i].virtual = base_idx[i].virtual;
      mob_idx[i].pos = base_idx[i].pos;
      mob_idx[i].number = base_idx[i].number;
      mob_idx[i].name = base_idx[i].name;
      mob_idx[i].short_desc = base_idx[i].short_desc;
      mob_idx[i].long_desc = base_idx[i].long_desc;
      mob_idx[i].func = NULL;
    }
    free(base_idx);
  }
  return mob_idx;
}

struct obj_index_data *make_obj_indices(struct _index_data *base_idx,
                                        int top) {
  struct obj_index_data *obj_idx = NULL;

  if (base_idx) {
    CREATE(obj_idx, struct obj_index_data, top + 1);

    for (int i = 0; i < top + 1; i++) {
      obj_idx[i].virtual = base_idx[i].virtual;
      obj_idx[i].pos = base_idx[i].pos;
      obj_idx[i].number = base_idx[i].number;
      obj_idx[i].name = base_idx[i].name;
      obj_idx[i].short_desc = base_idx[i].short_desc;
      obj_idx[i].long_desc = base_idx[i].long_desc;
      obj_idx[i].func = NULL;
    }
    free(base_idx);
  }
  return obj_idx;
}

/* generate index table for object or monster file */
struct _index_data *generate_indices(FILE * fl, int *top) {
  int i = 0;
  long bc = 1500;
  struct _index_data *index;
  char buf[82];

  rewind(fl);

  for (;;) {
    if (fgets(buf, sizeof(buf), fl)) {
      if (*buf == ';') {
        continue;
      }

      if (*buf == '#') {
        if (!i) {               /* first cell */
          CREATE(index, struct _index_data, bc);
        }
        else {
          if (i >= bc) {
            if (!(index = (struct _index_data *)
                  realloc(index, (i + 50) * sizeof(struct _index_data)))) {
              perror("load indices");
              assert(0);
            }
            bc += 50;
          }
        }
        sscanf(buf, "#%d", &index[i].virtual);
        index[i].pos = ftell(fl);
        index[i].number = 0;
        index[i].name = (index[i].virtual < 99999) ? fread_string(fl) :
          strdup("omega");
        i++;
      }
      else {
        if (*buf == '$')        /* EOF */
          break;
      }
    }
    else {
      log_msgf("generate indices");
      assert(0);
    }
  }
  *top = i - 1;
  return (index);
}

void cleanout_room(struct room_data *rp) {
  int i;
  struct extra_descr_data *exptr, *nptr;

  free(rp->name);
  free(rp->description);
  for (i = 0; i < 6; i++)
    if (rp->dir_option[i]) {
      free(rp->dir_option[i]->general_description);
      free(rp->dir_option[i]->keyword);
      free(rp->dir_option[i]);
      rp->dir_option[i] = NULL;
    }

  for (exptr = rp->ex_description; exptr; exptr = nptr) {
    nptr = exptr->next;
    free(exptr->keyword);
    free(exptr->description);
    free(exptr);
  }
}

void completely_cleanout_room(struct room_data *rp) {
  struct char_data *ch;
  struct obj_data *obj;

  while (rp->people) {
    ch = rp->people;
    act
      ("The hand of god sweeps across the land and you are swept into the Void.",
       FALSE, NULL, NULL, NULL, TO_VICT);
    char_from_room(ch);
    char_to_room(ch, 0);        /* send character to the void */
  }

  while (rp->contents) {
    obj = rp->contents;
    obj_from_room(obj);
    obj_to_room(obj, 0);        /* send item to the void */
  }

  cleanout_room(rp);
}

void load_one_room(FILE * fl, struct room_data *rp) {
  char chk[50];
  int bc = 0;
  long int tmp = 0;

  struct extra_descr_data *new_descr;

  bc = sizeof(struct room_data);

  rp->name = fread_string(fl);
  if (rp->name && *rp->name)
    bc += strlen(rp->name);
  rp->description = fread_string(fl);
  if (rp->description && *rp->description)
    bc += strlen(rp->description);

  if (top_of_zone_table >= 0) {
    int zone;
    fscanf(fl, " %*d ");

    /* OBS: Assumes ordering of input rooms */

    for (zone = 0;
         rp->number > zone_table[zone].top && zone <= top_of_zone_table;
         zone++);
    if (zone > top_of_zone_table) {
      log_msgf("Room %d is outside of any zone.\n", rp->number);
      assert(0);
    }
    rp->zone = zone;
  }
  fscanf(fl, " %ld ", &tmp);
  rp->room_flags = tmp;
  fscanf(fl, " %ld ", &tmp);
  rp->sector_type = tmp;

  if (tmp == -1) {
    fscanf(fl, " %ld", &tmp);
    rp->tele_time = tmp;
    fscanf(fl, " %ld", &tmp);
    rp->tele_targ = tmp;
    fscanf(fl, " %ld", &tmp);
    rp->tele_mask = tmp;
    if (IS_SET(TELE_COUNT, rp->tele_mask)) {
      fscanf(fl, "%ld ", &tmp);
      rp->tele_cnt = tmp;
    }
    else {
      rp->tele_cnt = 0;
    }
    fscanf(fl, " %ld", &tmp);
    rp->sector_type = tmp;
  }
  else {
    rp->tele_time = 0;
    rp->tele_targ = 0;
    rp->tele_mask = 0;
    rp->tele_cnt = 0;
  }

  if (tmp == SECT_WATER_NOSWIM || tmp == SECT_UNDERWATER) {     /* river */
    /* read direction and rate of flow */
    fscanf(fl, " %ld ", &tmp);
    rp->river_speed = tmp;
    fscanf(fl, " %ld ", &tmp);
    rp->river_dir = tmp;
  }

  if (rp->room_flags & TUNNEL) {        /* read in mobile limit on tunnel */
    fscanf(fl, " %ld ", &tmp);
    rp->moblim = tmp;
  }

  rp->funct = 0;
  rp->light = 0;                /* Zero light sources */

  for (tmp = 0; tmp <= 5; tmp++)
    rp->dir_option[tmp] = 0;

  rp->ex_description = 0;

  while (1 == fscanf(fl, " %s \n", chk)) {
    switch (*chk) {
    case 'D':
      setup_dir(fl, rp->number, atoi(chk + 1));
      bc += sizeof(struct room_direction_data);
/*      bc += strlen(rp->dir_option[atoi(chk + 1)]->general_description);
      bc += strlen(rp->dir_option[atoi(chk + 1)]->keyword);
*/
      break;
    case 'E':                  /* extra description field */

      CREATE(new_descr, struct extra_descr_data, 1);
      bc += sizeof(struct extra_descr_data);

      new_descr->keyword = fread_string(fl);
      if (new_descr->keyword && *new_descr->keyword)
        bc += strlen(new_descr->keyword);
      else
        log_msgf("No keyword in room %d\n", rp->number);

      new_descr->description = fread_string(fl);
      if (new_descr->description && *new_descr->description)
        bc += strlen(new_descr->description);
      else
        log_msgf("No desc in room %d\n", rp->number);

      new_descr->next = rp->ex_description;
      rp->ex_description = new_descr;
      break;
    case 'S':                  /* end of current room */

#if BYTE_COUNT
      if (bc >= 1000)
        log_msgf("Byte count for this room[%d]: %d\n", rp->number, bc);
#endif
      total_bc += bc;
      room_count++;
      return;
    default:
      log_msgf("unknown auxiliary code `%s' in room load of #%d",
               chk, rp->number);
      break;
    }
  }
}



/* load the rooms */
void boot_world() {
  FILE *fl;
  int virtual_nr, last;
  struct room_data *rp;


#if HASH
  init_hash_table(&room_db, sizeof(struct room_data), 2048);
#else
  init_world(room_db);
#endif
  character_list = 0;
  object_list = 0;

  if (!(fl = fopen(WORLD_FILE, "r"))) {
    perror("fopen");
    log_msg("boot_world: could not open world file.");
    assert(0);
  }

  last = 0;
  while (1 == fscanf(fl, " #%d\n", &virtual_nr)) {
    allocate_room(virtual_nr);
    rp = real_roomp(virtual_nr);
    if (rp)
      bzero(rp, sizeof(*rp));
    else {
      log_msgf("Error, room %d not in database!(%d)\n",
              virtual_nr, last);
      assert(0);
    }

    rp->number = virtual_nr;
    load_one_room(fl, rp);
    last = virtual_nr;
  }

  fclose(fl);
}





void allocate_room(int room_number) {
  if (room_number > top_of_world)
    top_of_world = room_number;
#if HASH
  hash_find_or_create(&room_db, room_number);
#else
  room_find_or_create(room_db, room_number);
#endif
}






/* read direction data */
void setup_dir(FILE * fl, int room, int dir) {
  int tmp;
  struct room_data *rp, dummy;

  rp = real_roomp(room);

  if (!rp) {
    rp = &dummy;                /* this is a quick fix to make the game */
    dummy.number = room;        /* stop crashing   */
  }

  CREATE(rp->dir_option[dir], struct room_direction_data, 1);

  rp->dir_option[dir]->general_description = fread_string(fl);
  rp->dir_option[dir]->keyword = fread_string(fl);

  fscanf(fl, "%d ", &tmp);
  switch (tmp) {
  case 1:
    rp->dir_option[dir]->exit_info = EX_ISDOOR;
    break;
  case 2:
    rp->dir_option[dir]->exit_info = EX_ISDOOR | EX_PICKPROOF;
    break;
  case 3:
    rp->dir_option[dir]->exit_info = EX_ISDOOR | EX_SECRET;
    break;
  case 4:
    rp->dir_option[dir]->exit_info = EX_ISDOOR | EX_SECRET | EX_PICKPROOF;
    break;
  case 5:
    rp->dir_option[dir]->exit_info = EX_CLIMB;
    break;
  case 6:
    rp->dir_option[dir]->exit_info = EX_CLIMB | EX_ISDOOR;
    break;
  case 7:
    rp->dir_option[dir]->exit_info = EX_CLIMB | EX_ISDOOR | EX_PICKPROOF;
    break;
  default:
    rp->dir_option[dir]->exit_info = 0;
  }

  fscanf(fl, " %d ", &tmp);
  rp->dir_option[dir]->key = tmp;

  fscanf(fl, " %d ", &tmp);
  rp->dir_option[dir]->to_room = tmp;
}


#define LOG_ZONE_ERROR(ch, type, zone, cmd) {                       \
	log_msgf("error in zone %s cmd %d (%c) resolving %s number",    \
             zone_table[zone].name, cmd, ch, type);                 \
		  }
void renum_zone_table() {
  int zone, comm;
  struct reset_com *cmd;

  for (zone = 0; zone <= top_of_zone_table; zone++)
    for (comm = 0; zone_table[zone].cmd[comm].command != 'S'; comm++)
      switch ((cmd = zone_table[zone].cmd + comm)->command) {
      case 'M':
        cmd->arg1 = real_mobile(cmd->arg1);
        if (cmd->arg1 < 0)
          LOG_ZONE_ERROR('M', "mobile", zone, comm);
        if (cmd->arg3 < 0)
          LOG_ZONE_ERROR('M', "room", zone, comm);
        break;
      case 'C':
        cmd->arg1 = real_mobile(cmd->arg1);
        if (cmd->arg1 < 0)
          LOG_ZONE_ERROR('C', "mobile", zone, comm);
        /*cmd->arg3 = real_room(cmd->arg3); */
        if (cmd->arg3 < 0)
          LOG_ZONE_ERROR('C', "room", zone, comm);
        break;
      case 'O':
        cmd->arg1 = real_object(cmd->arg1);
        if (cmd->arg1 < 0)
          LOG_ZONE_ERROR('O', "object", zone, comm);
        if (cmd->arg3 != NOWHERE) {
          /*cmd->arg3 = real_room(cmd->arg3); */
          if (cmd->arg3 < 0)
            LOG_ZONE_ERROR('O', "room", zone, comm);
        }
        break;
      case 'G':
        cmd->arg1 = real_object(cmd->arg1);
        if (cmd->arg1 < 0)
          LOG_ZONE_ERROR('G', "object", zone, comm);
        break;
      case 'E':
        cmd->arg1 = real_object(cmd->arg1);
        if (cmd->arg1 < 0)
          LOG_ZONE_ERROR('E', "object", zone, comm);
        break;
      case 'P':
        cmd->arg1 = real_object(cmd->arg1);
        if (cmd->arg1 < 0)
          LOG_ZONE_ERROR('P', "object", zone, comm);
        cmd->arg3 = real_object(cmd->arg3);
        if (cmd->arg3 < 0)
          LOG_ZONE_ERROR('P', "object", zone, comm);
        break;
      case 'D':
        /*cmd->arg1 = real_room(cmd->arg1); */
        if (cmd->arg1 < 0)
          LOG_ZONE_ERROR('D', "room", zone, comm);
        break;
      }
}


/* load the zone table and command tables */
void boot_zones() {

  FILE *fl;
  int zon = 0, cmd_no = 0, expand, tmp, bc = 100, cc = 22;
  char *check, buf[81];

  if (!(fl = fopen(ZONE_FILE, "r"))) {
    perror("boot_zones");
    assert(0);
  }

  for (;;) {
    fscanf(fl, " #%*d\n");
    check = fread_string(fl);

    if (*check == '$')
      break;                    /* end of file */

    /* alloc a new zone */

    if (!zon)
      CREATE(zone_table, struct zone_data, bc);
    else if (zon >= bc) {
      if (!(zone_table = (struct zone_data *)realloc(zone_table,
                                                     (zon +
                                                      10) *
                                                     sizeof(struct
                                                            zone_data)))) {
        perror("boot_zones realloc");
        assert(0);
      }
      bc += 10;
    }
    zone_table[zon].name = check;
    fscanf(fl, " %d ", &zone_table[zon].top);
    fscanf(fl, " %d ", &zone_table[zon].lifespan);
    fscanf(fl, " %d ", &zone_table[zon].reset_mode);

    /* read the command table */

/*
  new code to allow the game to be 'static' i.e. all the mobs are saved
in one big zone file, and restored later.
*/

    cmd_no = 0;

    if (zon == 0)
      cc = 20;

    for (expand = 1;;) {
      if (expand) {
        if (!cmd_no) {
          CREATE(zone_table[zon].cmd, struct reset_com, cc);
        }
        else {
          if (cmd_no >= cc) {
            cc += 5;
            if (!(zone_table[zon].cmd =
                  (struct reset_com *)realloc(zone_table[zon].cmd,
                                              (cc *
                                               sizeof(struct reset_com))))) {
              perror("reset command load");
              assert(0);
            }
          }
        }
      }

      expand = 1;

      fscanf(fl, " ");          /* skip blanks */
      fscanf(fl, "%c", &zone_table[zon].cmd[cmd_no].command);

      if (zone_table[zon].cmd[cmd_no].command == 'S')
        break;

      if (zone_table[zon].cmd[cmd_no].command == '*') {
        expand = 0;
        fgets(buf, 80, fl);     /* skip command */
        continue;
      }

      fscanf(fl, " %d %d %d",
             &tmp,
             &zone_table[zon].cmd[cmd_no].arg1,
             &zone_table[zon].cmd[cmd_no].arg2);

      zone_table[zon].cmd[cmd_no].if_flag = tmp;

      if (zone_table[zon].cmd[cmd_no].command == 'M' ||
          zone_table[zon].cmd[cmd_no].command == 'O' ||
          zone_table[zon].cmd[cmd_no].command == 'C' ||
          zone_table[zon].cmd[cmd_no].command == 'E' ||
          zone_table[zon].cmd[cmd_no].command == 'P' ||
          zone_table[zon].cmd[cmd_no].command == 'D')
        fscanf(fl, " %d", &zone_table[zon].cmd[cmd_no].arg3);

      fgets(buf, 80, fl);       /* read comment */
      cmd_no++;
    }
    zon++;
    if (zon == 1) {
      /* fix the cheat */
/*      if (fl != tmp_fl && fl != 0)
	fclose(fl);
      fl = tmp_fl;*/
    }

  }
  top_of_zone_table = --zon;
  free(check);
  fclose(fl);
}


/*************************************************************************
*  procedures for resetting, both play-time and boot-time	 	 *
*********************************************************************** */


/* read a mobile from MOB_FILE */
struct char_data *read_mobile(int nr, int type) {
  int i;
  long tmp, tmp2, tmp3, bc = 0;
  struct char_data *mob;
  char letter;

  extern int mob_tick_count;
  extern long mob_count;

  i = nr;
  if (type == VIRTUAL)
    if ((nr = real_mobile(nr)) < 0) {
      log_msgf("Mobile (V) %d does not exist in database.", i);
      return NULL;
    }

  if (fseek(mob_f, mob_index[nr].pos, 0) < 0) {
    log_msgf("Error seeking to mob #%d: (%d) %s", nr, errno,
             strerror(errno));
    return NULL;
}

  CREATE(mob, struct char_data, 1);
  bc = sizeof(struct char_data);
  clear_char(mob);

  mob->specials.last_direction = -1;    /* this is a fix for wander */

  /***** String data *** */

  mob->player.name = fread_string(mob_f);
  if (*mob->player.name)
    bc += strlen(mob->player.name);
  mob->player.short_descr = fread_string(mob_f);
  if (*mob->player.short_descr)
    bc += strlen(mob->player.short_descr);
  mob->player.long_descr = fread_string(mob_f);
  if (*mob->player.long_descr)
    bc += strlen(mob->player.long_descr);
  mob->player.description = fread_string(mob_f);
  if (mob->player.description && *mob->player.description)
    bc += strlen(mob->player.description);
  mob->player.title = 0;

  /* *** Numeric data *** */
#ifdef VERIFY_COUNT
  #undef VERIFY_COUNT
#endif
#define VERIFY_COUNT(got, expect)                       \
  do {                                                  \
    if ((got) < (expect)) {                             \
      log_msgf("Bad stats for mob %s near pos %lld",    \
               mob->player.name, ftell(mob_f));         \
      return NULL;                                      \
    }                                                   \
  } while(0)

  mob->mult_att = 1.0;
  mob->specials.spellfail = 101;

  VERIFY_COUNT(fscanf(mob_f, "%ld ", &tmp), 1);
  mob->specials.act = tmp;
  SET_BIT(mob->specials.act, ACT_ISNPC);

  VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
  mob->specials.affected_by = tmp;

  VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
  mob->specials.alignment = tmp;

  mob->player.class = CLASS_WARRIOR;

  VERIFY_COUNT(fscanf(mob_f, " %c ", &letter), 1);

  if (letter == 'S') {

    fscanf(mob_f, "\n");

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    GET_LEVEL(mob, WARRIOR_LEVEL_IND) = tmp;


    mob->abilities.str = 9 + number(1, (MAX(1, tmp / 5 - 1)));
    mob->abilities.intel = 9 + number(1, (MAX(1, tmp / 5 - 1)));
    mob->abilities.wis = 9 + number(1, (MAX(1, tmp / 5 - 1)));
    mob->abilities.dex = 9 + number(1, (MAX(1, tmp / 5 - 1)));
    mob->abilities.con = 9 + number(1, (MAX(1, tmp / 5 - 1)));
    mob->abilities.chr = 9 + number(1, (MAX(1, tmp / 5 - 1)));


    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->points.hitroll = 20 - tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);

    if (tmp > 10 || tmp < -10)
      tmp /= 10;

    mob->points.armor = 10 * tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ldd%ld+%ld ", &tmp, &tmp2, &tmp3),
                 3);
    mob->points.max_hit = dice(tmp, tmp2) + tmp3;
    mob->points.hit = mob->points.max_hit;

    VERIFY_COUNT(fscanf(mob_f, " %ldd%ld+%ld \n", &tmp, &tmp2, &tmp3),
                 3);
    mob->points.damroll = tmp3;
    mob->specials.damnodice = tmp;
    mob->specials.damsizedice = tmp2;

    mob->points.mana = 10;
    mob->points.max_mana = 10;


    mob->points.move = 50;
    mob->points.max_move = 50;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    if (tmp == -1) {
      VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
      mob->points.gold = tmp;
      VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
      GET_EXP(mob) = tmp;
      VERIFY_COUNT(fscanf(mob_f, " %ld \n", &tmp), 1);
      GET_RACE(mob) = tmp;
      if (is_giant(mob))
        mob->abilities.str += number(1, 4);
      if (is_small(mob))
        mob->abilities.str -= 1;
    }
    else {
      mob->points.gold = tmp;
      VERIFY_COUNT(fscanf(mob_f, " %ld \n", &tmp), 1);
      GET_EXP(mob) = tmp;
    }
    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->specials.position = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->specials.default_pos = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    if (tmp < 3) {
      mob->player.sex = tmp;
      mob->immune = 0;
      mob->M_immune = 0;
      mob->susc = 0;
    }
    else if (tmp < 6) {
      mob->player.sex = (tmp - 3);
      VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
      mob->immune = tmp;
      VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
      mob->M_immune = tmp;
      VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
      mob->susc = tmp;
    }
    else {
      mob->player.sex = 0;
      mob->immune = 0;
      mob->M_immune = 0;
      mob->susc = 0;
    }

    fscanf(mob_f, "\n");

    mob->player.class = 0;

    mob->player.time.birth = time(0);
    mob->player.time.played = 0;
    mob->player.time.logon = time(0);
    mob->player.weight = 200;
    mob->player.height = 198;

    for (i = 0; i < 3; i++)
      GET_COND(mob, i) = -1;

    for (i = 0; i < 5; i++)
      mob->specials.apply_saving_throw[i] =
        MAX(20 - GET_LEVEL(mob, WARRIOR_LEVEL_IND), 2);

  }
  else if ((letter == 'A') || (letter == 'N') || (letter == 'B') ||
           (letter == 'L')) {

    if ((letter == 'A') || (letter == 'B') || (letter == 'L')) {
      VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
      mob->mult_att = (float)tmp;
      /*
       **  read in types:
       */
    }

    fscanf(mob_f, "\n");

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    GET_LEVEL(mob, WARRIOR_LEVEL_IND) = tmp;


    mob->abilities.str = 9 + number(1, (MAX(1, tmp / 5 - 1)));
    mob->abilities.intel = 9 + number(1, (MAX(1, tmp / 5 - 1)));
    mob->abilities.wis = 9 + number(1, (MAX(1, tmp / 5 - 1)));
    mob->abilities.dex = 9 + number(1, (MAX(1, tmp / 5 - 1)));
    mob->abilities.con = 9 + number(1, (MAX(1, tmp / 5 - 1)));
    mob->abilities.chr = 9 + number(1, (MAX(1, tmp / 5 - 1)));



    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->points.hitroll = 20 - tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->points.armor = 10 * tmp;
    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->points.max_hit = dice(GET_LEVEL(mob, WARRIOR_LEVEL_IND), 8) + tmp;
    mob->points.hit = mob->points.max_hit;

    VERIFY_COUNT(fscanf(mob_f, " %ldd%ld+%ld \n", &tmp, &tmp2, &tmp3),
                 3);
    mob->points.damroll = tmp3;
    mob->specials.damnodice = tmp;
    mob->specials.damsizedice = tmp2;

    mob->points.mana = 10;
    mob->points.max_mana = 10;


    mob->points.move = 50;
    mob->points.max_move = 50;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);

    if (tmp == -1) {
      VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
      mob->points.gold = tmp;
      VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
      if (tmp >= 0)
        GET_EXP(mob) = (determine_exp(mob, tmp) + mob->points.gold);
      else
        GET_EXP(mob) = -tmp;
      VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
      GET_RACE(mob) = tmp;
      if (is_giant(mob))
        mob->abilities.str += number(1, 4);
      if (is_small(mob))
        mob->abilities.str -= 1;
    }
    else {
      mob->points.gold = tmp;

      /*
         this is where the new exp will come into play
       */
      VERIFY_COUNT(fscanf(mob_f, " %ld \n", &tmp), 1);
      GET_EXP(mob) = (determine_exp(mob, tmp) + mob->points.gold);
    }

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->specials.position = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->specials.default_pos = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld \n", &tmp), 1);
    if (tmp < 3) {
      mob->player.sex = tmp;
      mob->immune = 0;
      mob->M_immune = 0;
      mob->susc = 0;
    }
    else if (tmp < 6) {
      mob->player.sex = (tmp - 3);
      VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
      mob->immune = tmp;
      VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
      mob->M_immune = tmp;
      VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
      mob->susc = tmp;
    }
    else {
      mob->player.sex = 0;
      mob->immune = 0;
      mob->M_immune = 0;
      mob->susc = 0;
    }

    /*
     *   read in the sound string for a mobile
     */
    if (letter == 'L') {
      mob->player.sounds = fread_string(mob_f);
      if (mob->player.sounds && *mob->player.sounds)
        bc += strlen(mob->player.sounds);

      mob->player.distant_snds = fread_string(mob_f);
      if (mob->player.distant_snds && *mob->player.distant_snds)
        bc += strlen(mob->player.distant_snds);
    }
    else {
      mob->player.sounds = 0;
      mob->player.distant_snds = 0;
    }

    if (letter == 'B') {
      SET_BIT(mob->specials.act, ACT_HUGE);
    }

    mob->player.class = 0;

    mob->player.time.birth = time(0);
    mob->player.time.played = 0;
    mob->player.time.logon = time(0);
    mob->player.weight = 200;
    mob->player.height = 198;

    for (i = 0; i < 3; i++)
      GET_COND(mob, i) = -1;

    for (i = 0; i < 5; i++)
      mob->specials.apply_saving_throw[i] =
        MAX(20 - GET_LEVEL(mob, WARRIOR_LEVEL_IND), 2);

  }
  else {                        /* The old monsters are down below here */

    fscanf(mob_f, "\n");

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->abilities.str = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->abilities.intel = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->abilities.wis = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->abilities.dex = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld \n", &tmp), 1);
    mob->abilities.con = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp2), 1);

    mob->points.max_hit = number(tmp, tmp2);
    mob->points.hit = mob->points.max_hit;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->points.armor = 10 * tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->points.mana = tmp;
    mob->points.max_mana = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->points.move = tmp;
    mob->points.max_move = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->points.gold = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld \n", &tmp), 1);
    GET_EXP(mob) = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->specials.position = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->specials.default_pos = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->player.sex = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->player.class = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    GET_LEVEL(mob, WARRIOR_LEVEL_IND) = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->player.time.birth = time(0);
    mob->player.time.played = 0;
    mob->player.time.logon = time(0);

    VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
    mob->player.weight = tmp;

    VERIFY_COUNT(fscanf(mob_f, " %ld \n", &tmp), 1);
    mob->player.height = tmp;

    for (i = 0; i < 3; i++) {
      VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
      GET_COND(mob, i) = tmp;
    }
    fscanf(mob_f, " \n ");

    for (i = 0; i < 5; i++) {
      VERIFY_COUNT(fscanf(mob_f, " %ld ", &tmp), 1);
      mob->specials.apply_saving_throw[i] = tmp;
    }

    fscanf(mob_f, " \n ");

    /* Set the damage as some standard 1d4 */
    mob->points.damroll = 0;
    mob->specials.damnodice = 1;
    mob->specials.damsizedice = 6;

    /* Calculate THAC0 as a formula of Level */
    mob->points.hitroll = MAX(1, GET_LEVEL(mob, WARRIOR_LEVEL_IND) - 3);
  }

  mob->tmpabilities = mob->abilities;

  for (i = 0; i < MAX_WEAR; i++)        /* Initialisering Ok */
    mob->equipment[i] = 0;

  mob->nr = nr;

  mob->desc = 0;

  if (!IS_SET(mob->specials.act, ACT_ISNPC))
    SET_BIT(mob->specials.act, ACT_ISNPC);

  mob->generic = 0;
  mob->commandp = 0;
  mob->commandp2 = 0;
  mob->waitp = 0;

  /* Check to see if associated with a script, if so, set it up */
  if (IS_SET(mob->specials.act, ACT_SCRIPT))
    REMOVE_BIT(mob->specials.act, ACT_SCRIPT);

  for (i = 0; i < top_of_scripts; i++) {
    if (script_data[i].virtual == mob_index[nr].virtual) {
      SET_BIT(mob->specials.act, ACT_SCRIPT);
      /* SPRINTF(buffer, "Setting SCRIPT bit for mobile %s, file %s.", GET_NAME(mob), script_data[i].filename);
         log_msg(buffer); */
      mob->script = i;
      break;
    }
  }

  verify_mob(mob);              /* check it for acceptability */

  /* tell the spec_proc (if there is one) that we've been born */
  /*  if(mob_index[nr].func)
     (*mob_index[nr].func)(mob, 0, "", mob, EVENT_BIRTH);
   */
  /* insert in list */

  mob->next = character_list;
  character_list = mob;

#if NEW_RENT
  if (mob->points.gold >= 10)
    mob->points.gold /= 10;
  else if (mob->points.gold > 0)
    mob->points.gold = 1;
#endif

  if (mob->points.gold > GET_LEVEL(mob, WARRIOR_LEVEL_IND) * 1500) {
    log_msgf("%s has gold > level * 1500 (%d)", mob->player.short_descr,
             mob->points.gold);
  }

  /* set up things that all members of the race have */
  mob->specials.intrinsics = 0;
  set_racial_stuff(mob);        /* this sets intrinsics */
  mob->specials.affected_by |= mob->specials.intrinsics;

  /* change exp for wimpy mobs (lower) */
  if (IS_SET(mob->specials.act, ACT_WIMPY))
    GET_EXP(mob) -= GET_EXP(mob) / 10;

  /* change exp for agressive mobs (higher) */
  if (IS_SET(mob->specials.act, ACT_AGGRESSIVE)) {
    GET_EXP(mob) += GET_EXP(mob) / 10;
/* big bonus for fully aggressive mobs for now */
    if (!IS_SET(mob->specials.act, ACT_WIMPY) ||
        IS_SET(mob->specials.act, ACT_META_AGG))
      GET_EXP(mob) += (GET_EXP(mob) / 2);
  }

  /* set up distributed movement system */

  mob->specials.tick = mob_tick_count++;

  if (mob_tick_count == TICK_WRAP_COUNT)
    mob_tick_count = 0;

  mob_index[nr].number++;

#if BYTE_COUNT
  log_msgf("Mobile [%d]: byte count: %d\n", mob_index[nr].virtual, bc);
#endif

  total_mbc += bc;
  mob_count++;
  return (mob);
}


/* read an object from OBJ_FILE */
struct obj_data *read_object(int nr, int type) {
  struct obj_data *obj;
  int tmp, i;
  long bc;
  char chk[50];
  struct extra_descr_data *new_descr;

  extern long obj_count;
  extern long total_obc;

  i = nr;
  if (type == VIRTUAL) {
    nr = real_object(nr);
  }
  if (nr < 0 || nr > top_of_objt) {
    log_msgf("Object (V) %d does not exist in database.", i);
    return NULL;
  }

  if (fseek(obj_f, obj_index[nr].pos, 0) < 0) {
    log_msgf("Error seeking to object #%d: (%d) %s", nr, errno,
             strerror(errno));
    return NULL;
  }

  CREATE(obj, struct obj_data, 1);
  bc = sizeof(struct obj_data);

  clear_object(obj);

  /* *** string data *** */

  obj->name = fread_string(obj_f);
  if (obj->name && *obj->name) {
    bc += strlen(obj->name);
  }
  obj->short_description = fread_string(obj_f);
  if (obj->short_description && *obj->short_description) {
    bc += strlen(obj->short_description);
  }
  obj->description = fread_string(obj_f);
  if (obj->description && *obj->description) {
    bc += strlen(obj->description);
  }
  obj->action_description = fread_string(obj_f);
  if (obj->action_description && *obj->action_description) {
    bc += strlen(obj->action_description);
  }

  /* *** numeric data *** */
#ifdef VERIFY_COUNT
  #undef VERIFY_COUNT
#endif
#define VERIFY_COUNT(got, expect)                       \
  do {                                                  \
    if ((got) < (expect)) {                             \
      log_msgf("Bad stats for obj %s near pos %lld",    \
               obj->name, ftell(obj_f));                \
      return NULL;                                      \
    }                                                   \
  } while(0)

  VERIFY_COUNT(fscanf(obj_f, " %d ", &tmp), 1);
  obj->obj_flags.type_flag = tmp;
  VERIFY_COUNT(fscanf(obj_f, " %d ", &tmp), 1);
  obj->obj_flags.extra_flags = tmp;
  VERIFY_COUNT(fscanf(obj_f, " %d ", &tmp), 1);
  obj->obj_flags.wear_flags = tmp;
  VERIFY_COUNT(fscanf(obj_f, " %d ", &tmp), 1);
  obj->obj_flags.value[0] = tmp;
  VERIFY_COUNT(fscanf(obj_f, " %d ", &tmp), 1);
  obj->obj_flags.value[1] = tmp;
  VERIFY_COUNT(fscanf(obj_f, " %d ", &tmp), 1);
  obj->obj_flags.value[2] = tmp;
  VERIFY_COUNT(fscanf(obj_f, " %d ", &tmp), 1);
  obj->obj_flags.value[3] = tmp;
  VERIFY_COUNT(fscanf(obj_f, " %d ", &tmp), 1);
  obj->obj_flags.weight = tmp;
  VERIFY_COUNT(fscanf(obj_f, " %d \n", &tmp), 1);
  obj->obj_flags.cost = tmp;
  VERIFY_COUNT(fscanf(obj_f, " %d \n", &tmp), 1);
  obj->obj_flags.cost_per_day = tmp;

  /* *** extra descriptions *** */

  obj->ex_description = 0;

  while (fscanf(obj_f, " %s \n", chk), *chk == 'E') {
    CREATE(new_descr, struct extra_descr_data, 1);
    bc += sizeof(struct extra_descr_data);
    new_descr->keyword = fread_string(obj_f);
    if (new_descr->keyword && *new_descr->keyword)
      bc += strlen(new_descr->keyword);
    new_descr->description = fread_string(obj_f);
    if (new_descr->description && *new_descr->description)
      bc += strlen(new_descr->description);

    new_descr->next = obj->ex_description;
    obj->ex_description = new_descr;
  }

  for (i = 0; (i < MAX_OBJ_AFFECT) && (*chk == 'A'); i++) {
    VERIFY_COUNT(fscanf(obj_f, " %d ", &tmp), 1);
    obj->affected[i].location = tmp;
    VERIFY_COUNT(fscanf(obj_f, " %d \n", &tmp), 1);
    obj->affected[i].modifier = tmp;
    VERIFY_COUNT(fscanf(obj_f, " %s \n", chk), 1);
  }

  for (; (i < MAX_OBJ_AFFECT); i++) {
    obj->affected[i].location = APPLY_NONE;
    obj->affected[i].modifier = 0;
  }

  obj->in_room = NOWHERE;
  obj->next_content = 0;
  obj->carried_by = 0;
  obj->equipped_by = 0;
  obj->eq_pos = -1;
  obj->in_obj = 0;
  obj->contains = 0;
  obj->item_number = nr;
  obj->in_obj = 0;

  obj->next = object_list;
  object_list = obj;

  obj_index[nr].number++;

  if (IS_SET(obj->obj_flags.extra_flags, ITEM_FIGURINE)) {
    int i, found = 0;

    for (i = 0; i < fig_count; i++)
      if (figurine[i].obj == obj_index[nr].virtual) {
        found = 1;
        break;
      }

    if (found &&
        (obj->link =
         read_mobile(real_mobile(figurine[i].mob), REAL))) {
      SET_BIT(obj->link->specials.act, ACT_FIGURINE);
      obj->link->link = obj;
      char_to_room(obj->link, 3);
    }
    else {
      REMOVE_BIT(obj->obj_flags.extra_flags, ITEM_FIGURINE);
      obj->link = NULL;
    }
  }

  else
    obj->link = NULL;

  obj_count++;
#if BYTE_COUNT
  log_msgf("Object [%d] uses %d bytes\n", obj_index[nr].virtual, bc);
#endif
  total_obc += bc;
  return (obj);
}




#define ZO_DEAD  999

/* update zone ages, queue for reset if necessary, and dequeue when possible */
void zone_update() {
  int i;
  struct reset_q_element *update_u, *temp, *tmp2;
  extern struct reset_q_type reset_q;


  /* enqueue zones */

  for (i = 0; i <= top_of_zone_table; i++) {
    if (zone_table[i].start) {
      if (zone_table[i].age < zone_table[i].lifespan &&
          zone_table[i].reset_mode)
        (zone_table[i].age)++;
      else if (zone_table[i].age < ZO_DEAD && zone_table[i].reset_mode) {
        /* enqueue zone */

        CREATE(update_u, struct reset_q_element, 1);

        update_u->zone_to_reset = i;
        update_u->next = 0;

        if (!reset_q.head)
          reset_q.head = reset_q.tail = update_u;
        else {
          reset_q.tail->next = update_u;
          reset_q.tail = update_u;
        }

        zone_table[i].age = ZO_DEAD;
      }
    }
  }

  /* dequeue zones (if possible) and reset */

  for (update_u = reset_q.head; update_u; update_u = tmp2) {
    if (update_u->zone_to_reset > top_of_zone_table) {

      /*  this may or may not work */
      /*  may result in some lost memory, but the loss is not signifigant
         over the short run
       */
      update_u->zone_to_reset = 0;
      update_u->next = 0;
    }
    tmp2 = update_u->next;

    if (IS_SET(zone_table[update_u->zone_to_reset].reset_mode, ZONE_ALWAYS) ||
        (IS_SET(zone_table[update_u->zone_to_reset].reset_mode, ZONE_EMPTY) &&
         is_empty(update_u->zone_to_reset))) {
      reset_zone(update_u->zone_to_reset);
      /* dequeue */

      if (update_u == reset_q.head)
        reset_q.head = reset_q.head->next;
      else {
        for (temp = reset_q.head; temp->next != update_u; temp = temp->next);

        if (!update_u->next)
          reset_q.tail = temp;

        temp->next = update_u->next;
      }
      free(update_u);
    }
  }
}




#define ZCMD zone_table[zone].cmd[cmd_no]

/* execute the reset command table of a given zone */
void reset_zone(int zone) {
  int cmd_no, last_cmd = 1;
  struct char_data *mob;
  struct char_data *master;
  struct obj_data *obj, *obj_to;
  struct room_data *rp;
  /*   FILE *fl; */
  static int done = 0;

  mob = 0;

  if (zone == 0 && !done) {
    done = 1;
#if SAVE_WORLD
    for (i = 0; i < 30000; i += 1000) {
      SPRINTF(buf, "world/mobs.%d", i);
      fl = fopen(buf, "r");
      if (!fl) {
        log_msg("Unable to load scratch zone file for update.");
        return;
      }
      read_text_zone(fl);
      fclose(fl);
    }
#endif
    return;
  }



  if (zone_table[zone].start == 0) {
    char *s;
    int d, e;
    s = zone_table[zone].name;
    d = (zone ? (zone_table[zone - 1].top + 1) : 0);
    e = zone_table[zone].top;
    log_msgf("Run time initialization of zone %s, rooms (%d-%d)", s, d, e);

  }

  if (!zone_table[zone].cmd) {
    return;
  }

  for (cmd_no = 0;; cmd_no++) {
    if (ZCMD.command == 'S')
      break;

    if (last_cmd || ZCMD.if_flag <= 0)
      switch (ZCMD.command) {
      case 'M':                /* read a mobile */
        if ((mob_index[ZCMD.arg1].number < ZCMD.arg2)
            && !check_kill_file(mob_index[ZCMD.arg1].virtual)) {
          mob = read_mobile(ZCMD.arg1, REAL);
          if (!mob) {
            continue;
          }
          mob->specials.zone = zone;
          char_to_room(mob, ZCMD.arg3);

          if (GET_RACE(mob) > RACE_GNOME)
            if (!strchr(zone_table[zone].races, GET_RACE(mob))) {
              zone_table[zone].races[strlen(zone_table[zone].races)] =
                GET_RACE(mob);
            }

          last_cmd = 1;
          master = mob;
        }
        else
          last_cmd = 0;
        break;

      case 'C':                /* read a mobile.  Charm them to follow prev. */
        if ((mob_index[ZCMD.arg1].number < ZCMD.arg2)
            && !check_kill_file(mob_index[ZCMD.arg1].virtual)) {
          mob = read_mobile(ZCMD.arg1, REAL);
          if (!mob) {
            continue;
          }
          mob->specials.zone = zone;

          if (GET_RACE(mob) > RACE_GNOME)
            if (!strchr(zone_table[zone].races, GET_RACE(mob))) {
              zone_table[zone].races[strlen(zone_table[zone].races)] =
                GET_RACE(mob);
            }

          if (master) {
            char_to_room(mob, master->in_room);
            /*
               add the charm bit to the dude.
             */
            add_follower(mob, master);
            SET_BIT(mob->specials.affected_by, AFF_CHARM);
            SET_BIT(mob->specials.act, ZCMD.arg3);
          }
          else {
            extract_char(mob);
            last_cmd = 0;
          }
          last_cmd = 1;
        }
        else
          last_cmd = 0;
        break;

      case 'Z':                /* set the last mobile to this zone */
        if (mob) {
          mob->specials.zone = ZCMD.arg1;

          if (GET_RACE(mob) > RACE_GNOME)
            if (!strchr(zone_table[ZCMD.arg1].races, GET_RACE(mob))) {
              zone_table[ZCMD.
                         arg1].races[strlen(zone_table[ZCMD.arg1].races)] =
                GET_RACE(mob);
            }
        }
        break;

      case 'O':                /* read an object */
        if (obj_index[ZCMD.arg1].number < ZCMD.arg2) {
          if (ZCMD.arg3 >= 0 && ((rp = real_roomp(ZCMD.arg3)) != NULL)) {
            if ((ZCMD.if_flag > 0
                 && obj_room_count(ZCMD.arg1, rp) < ZCMD.if_flag)
                || (ZCMD.if_flag <= 0
                    && obj_room_count(ZCMD.arg1, rp) < (-ZCMD.if_flag) + 1)) {
              if ((obj = read_object(ZCMD.arg1, REAL)) != NULL) {
                obj_to_room(obj, ZCMD.arg3);
                last_cmd = 1;
              }
              else {
                last_cmd = 0;
              }
            }
            else {
              last_cmd = 0;
            }
          }
          else if ((obj = read_object(ZCMD.arg1, REAL)) != NULL) {
            log_msgf("Error finding room #%d", ZCMD.arg3);
            last_cmd = 1;
          }
          else {
            last_cmd = 0;
          }
        }
        break;

      case 'P':                /* object to object */
        if (obj_index[ZCMD.arg1].number < ZCMD.arg2) {
          obj = read_object(ZCMD.arg1, REAL);
          if (!obj) {
            return;
          }
          obj_to = get_obj_num(ZCMD.arg3);
          if (obj_to && obj) {
            obj_to_obj(obj, obj_to);
            last_cmd = 1;
          }
          else {
            last_cmd = 0;
          }
        }
        else
          last_cmd = 0;
        break;

      case 'G':                /* obj_to_char */
        if (obj_index[ZCMD.arg1].number < ZCMD.arg2 &&
            (obj = read_object(ZCMD.arg1, REAL)) && mob)  {
          obj_to_char(obj, mob);
          last_cmd = 1;
        }
        else
          last_cmd = 0;
        break;

      case 'H':                /* hatred to char */
        
        if (mob && add_hatred(mob, ZCMD.arg1, ZCMD.arg2))
          last_cmd = 1;
        else
          last_cmd = 0;
        break;

      case 'F':                /* fear to char */

        if (mob && add_fears(mob, ZCMD.arg1, ZCMD.arg2))
          last_cmd = 1;
        else
          last_cmd = 0;
        break;

      case 'E':                /* object to equipment list */
        if (obj_index[ZCMD.arg1].number < ZCMD.arg2 &&
            (obj = read_object(ZCMD.arg1, REAL))) {
          if (mob && !mob->equipment[ZCMD.arg3]) {
            equip_char(mob, obj, ZCMD.arg3);
          }
          else {
            log_lev_msgf(LOG_ALERT,
                         "eq error - zone %d, cmd %d, item %d, mob %d, loc %d\n",
                         zone, cmd_no, obj_index[ZCMD.arg1].virtual,
                         mob_index[mob->nr].virtual, ZCMD.arg3);
          }
          last_cmd = 1;
        }
        else
          last_cmd = 0;
        break;

      case 'D':                /* set state of door */
        rp = real_roomp(ZCMD.arg1);
        if (rp && rp->dir_option[ZCMD.arg2]) {
          switch (ZCMD.arg3) {
          case 0:
            SET_BIT(rp->dir_option[ZCMD.arg2]->exit_info, EX_ISDOOR);
            REMOVE_BIT(rp->dir_option[ZCMD.arg2]->exit_info, EX_LOCKED);
            REMOVE_BIT(rp->dir_option[ZCMD.arg2]->exit_info, EX_CLOSED);
            break;
          case 1:
            SET_BIT(rp->dir_option[ZCMD.arg2]->exit_info, EX_ISDOOR);
            SET_BIT(rp->dir_option[ZCMD.arg2]->exit_info, EX_CLOSED);
            REMOVE_BIT(rp->dir_option[ZCMD.arg2]->exit_info, EX_LOCKED);
            break;
          case 2:
            SET_BIT(rp->dir_option[ZCMD.arg2]->exit_info, EX_ISDOOR);
            SET_BIT(rp->dir_option[ZCMD.arg2]->exit_info, EX_LOCKED);
            SET_BIT(rp->dir_option[ZCMD.arg2]->exit_info, EX_CLOSED);
            break;
          }
          last_cmd = 1;
        }
        else {
          /* that exit doesn't exist anymore */
        }
        break;

      default:
        log_msgf("Undefd cmd [%c] in reset table; zone %d cmd %d.",
                 ZCMD.command, zone, cmd_no);
        break;
      }
    else
      last_cmd = 0;

  }

  zone_table[zone].age = 0;
  zone_table[zone].start = 1;

}

#undef ZCMD

/* for use in reset_zone; return TRUE if zone 'nr' is free of PC's  */
int is_empty(int zone_nr) {
  struct descriptor_data *i;

  for (i = descriptor_list; i; i = i->next)
    if (!i->connected)
      if (real_roomp(i->character->in_room)->zone == zone_nr)
        return (0);

  return (1);
}





/*************************************************************************
*  stuff related to the save/load player system								  *
*********************************************************************** */

/* Load a char, TRUE if loaded, FALSE if not */
int load_char(char *name, struct char_file_u *char_element) {
  FILE *fl;
  int player_i;

  if ((player_i = find_name(name)) >= 0) {

    if (!(fl = fopen(PLAYER_FILE, "r"))) {
      perror("Opening player file for reading. (db.c, load_char)");
      assert(0);
    }

    fseek(fl, (long)(player_table[player_i].nr *
                     sizeof(struct char_file_u)), 0);

    fread(char_element, sizeof(struct char_file_u), 1, fl);
    fclose(fl);
    /*
     **  Kludge for ressurection
     */
    char_element->talks[2] = FALSE;     /* they are not dead */
    return (player_i);

  }
  else

    return (-1);
}




/* copy data from the file structure to a char struct */
void store_to_char(struct char_file_u *st, struct char_data *ch) {
  int i;
  int max;

  GET_SEX(ch) = st->sex;
  ch->player.class = st->class;

  for (i = MAGE_LEVEL_IND; i < MAX_CLASS; i++)
    ch->player.level[i] = st->level[i];

  GET_RACE(ch) = st->race;

  ch->player.short_descr = 0;
  ch->player.long_descr = 0;

  if (*st->title) {
    CREATE(ch->player.title, char, strlen(st->title) + 1);
    strcpy(ch->player.title, st->title);
  }
  else
    GET_TITLE(ch) = 0;

  if (*st->description) {
    CREATE(ch->player.description, char, strlen(st->description) + 1);
    strcpy(ch->player.description, st->description);
  }
  else
    ch->player.description = 0;

  ch->player.hometown = st->hometown;

  ch->player.time.birth = st->birth;
  ch->player.time.played = st->played;
  ch->player.time.logon = time(0);

  for (i = 0; i <= MAX_TOUNGE - 1; i++)
    ch->player.talks[i] = st->talks[i];

  ch->player.weight = st->weight;
  ch->player.height = st->height;

  ch->abilities = st->abilities;

  ch->tmpabilities = st->abilities;

  ch->points = st->points;

  space_for_skills(ch);

  if (get_max_level(ch) >= LOW_IMMORTAL) {
    max = 100;
  }
  else {
    if (how_many_classes(ch) >= 3) {
      max = 80;
    }
    else if (how_many_classes(ch) == 2) {
      max = 87;
    }
    else {
      max = 95;
    }
  }

  for (i = 0; i <= MAX_SKILLS - 1; i++) {
    ch->skills[i].flags = st->skills[i].flags;
    ch->skills[i].learned = MIN(st->skills[i].learned, max);
  }

  ch->specials.spells_to_learn = st->spells_to_learn;
  ch->specials.alignment = st->alignment;

  ch->specials.act = st->act;
  ch->specials.carry_weight = 0;
  ch->specials.carry_items = 0;
  ch->specials.pmask = 0;
  ch->specials.poofin = 0;
  ch->specials.poofout = 0;
  ch->points.armor = 100;
  ch->points.hitroll = 0;
  ch->points.damroll = 0;
  ch->specials.affected_by = st->affected_by;
  ch->specials.affected_by2 = st->affected_by2;
  ch->specials.start_room = st->startroom;
  ch->player.extra_flags = st->extra_flags;

  CREATE(GET_NAME(ch), char, strlen(st->name) + 1);
  strcpy(GET_NAME(ch), st->name);

  for (i = 0; i <= 4; i++) {
    ch->specials.apply_saving_throw[i] = 0;
  }

  for (i = 0; i <= 2; i++)
    GET_COND(ch, i) = st->conditions[i];

  /* Add all spell effects */
  for (i = 0; i < MAX_AFFECT; i++) {
    if (st->affected[i].type)
      affect_to_char(ch, &st->affected[i]);
  }
  ch->in_room = st->load_room;
  ch->term = 0;
  /* set default screen size */
  ch->size = 25;
  affect_total(ch);
}                               /* store_to_char */




/* copy vital data from a players char-structure to the file structure */
void char_to_store(struct char_data *ch, struct char_file_u *st) {
  int i;
  struct affected_type *af;
  struct obj_data *char_eq[MAX_WEAR];

  /* Unaffect everything a character can be affected by */

  for (i = 0; i < MAX_WEAR; i++) {
    if (ch->equipment[i])
      char_eq[i] = unequip_char(ch, i);
    else
      char_eq[i] = 0;
  }

  for (af = ch->affected, i = 0; i < MAX_AFFECT; i++) {
    if (af) {
      st->affected[i] = *af;
      st->affected[i].next = 0;
      /* subtract effect of the spell or the effect will be doubled */
      affect_modify(ch, st->affected[i].location,
                    (int)st->affected[i].modifier,
                    st->affected[i].bitvector, FALSE);
      af = af->next;
    }
    else {
      st->affected[i].type = 0; /* Zero signifies not used */
      st->affected[i].duration = 0;
      st->affected[i].modifier = 0;
      st->affected[i].location = 0;
      st->affected[i].bitvector = 0;
      st->affected[i].next = 0;
    }
  }

  if ((i >= MAX_AFFECT) && af && af->next)
    log_msg("WARNING: OUT OF STORE ROOM FOR AFFECTED TYPES!!!");



  ch->tmpabilities = ch->abilities;

  st->birth = ch->player.time.birth;
  st->played = ch->player.time.played;
  st->played += (long)(time(0) - ch->player.time.logon);
  st->last_logon = time(0);

  ch->player.time.played = st->played;
  ch->player.time.logon = time(0);

  st->hometown = ch->player.hometown;
  st->weight = GET_WEIGHT(ch);
  st->height = GET_HEIGHT(ch);
  st->sex = GET_SEX(ch);
  st->class = ch->player.class;
  for (i = MAGE_LEVEL_IND; i < MAX_CLASS; i++)
    st->level[i] = ch->player.level[i];
  st->race = GET_RACE(ch);

  st->abilities = ch->abilities;

  st->points = ch->points;

  st->alignment = ch->specials.alignment;
  st->spells_to_learn = ch->specials.spells_to_learn;
  st->act = ch->specials.act;
  st->affected_by = ch->specials.affected_by;
  st->affected_by2 = ch->specials.affected_by2;
  st->startroom = ch->specials.start_room;
  st->extra_flags = ch->player.extra_flags;

  st->points.armor = 100;
  st->points.hitroll = 0;
  st->points.damroll = 0;

  memset(st->title, 0, sizeof(st->title));
  if (GET_TITLE(ch))
    strcpy(st->title, GET_TITLE(ch));
  else
    *st->title = '\0';

  memset(st->description, 0, sizeof(st->description));
  if (ch->player.description)
    strcpy(st->description, ch->player.description);
  else
    *st->description = '\0';

  for (i = 0; i <= MAX_TOUNGE - 1; i++)
    st->talks[i] = ch->player.talks[i];

  for (i = 0; i <= MAX_SKILLS - 1; i++)
    st->skills[i] = ch->skills[i];

  memset(st->name, 0, sizeof(st->name));
  strcpy(st->name, GET_NAME(ch));

  for (i = 0; i <= 4; i++)
    st->apply_saving_throw[i] = ch->specials.apply_saving_throw[i];

  for (i = 0; i <= 2; i++)
    st->conditions[i] = GET_COND(ch, i);

  for (af = ch->affected, i = 0; i < MAX_AFFECT; i++) {
    if (af) {
      /* Add effect of the spell or it will be lost */
      /* When saving without quitting               */
      affect_modify(ch, st->affected[i].location,
                    (int)st->affected[i].modifier,
                    st->affected[i].bitvector, TRUE);
      af = af->next;
    }
  }

  for (i = 0; i < MAX_WEAR; i++) {
    if (char_eq[i])
      equip_char(ch, char_eq[i], i);
  }

  affect_total(ch);
}                               /* Char to store */




/* create a new entry in the in-memory index table for the player file */
int create_entry(char *name) {
  int i;

  if (top_of_p_table == -1) {
    CREATE(player_table, struct player_index_element, 1);
    top_of_p_table = 0;
  }
  else if (!(player_table = (struct player_index_element *)
             realloc(player_table, sizeof(struct player_index_element) *
                     (++top_of_p_table + 1)))) {
    perror("create entry");
    assert(0);
  }

  CREATE(player_table[top_of_p_table].name, char, strlen(name) + 1);

  /* copy lowercase equivalent of name to table field */
  for (i = 0; (*(player_table[top_of_p_table].name + i) =
               LOWER(*(name + i))) != '\0'; i++);

  player_table[top_of_p_table].nr = top_of_p_table;

  return (top_of_p_table);
}



/* write the vital data of a player to the player file */
void save_char(struct char_data *ch, sh_int load_room) {
  struct char_file_u st;
  FILE *fl;
  char mode[4];
  int expand;
  struct char_data *tmp;

  if (IS_NPC(ch) && !(IS_SET(ch->specials.act, ACT_POLYSELF))) {
    return;
  }

  if (IS_NPC(ch)) {
    if (!ch->desc)
      return;
    tmp = ch->desc->original;
    if (!tmp)
      return;

  }
  else {
    if (!ch->desc)
      return;
    tmp = 0;
  }

  if ((expand = (ch->desc->pos > top_of_p_file))) {
    strcpy(mode, "a");
    top_of_p_file++;
  }
  else
    strcpy(mode, "r+");

  memset(&st, 0, sizeof(st));
  if (!tmp)
    char_to_store(ch, &st);
  else
    char_to_store(tmp, &st);

  st.load_room = load_room;

  memset(st.pwd, 0, sizeof(st.pwd));
  strcpy(st.pwd, ch->desc->pwd);

  if (!(fl = fopen(PLAYER_FILE, mode))) {
    perror("save char");
    assert(0);
  }

  if (!expand)
    fseek(fl, ch->desc->pos * sizeof(struct char_file_u), SEEK_SET);

  fwrite(&st, sizeof(struct char_file_u), 1, fl);

  fclose(fl);
}




/* for possible later use with qsort */
int compare(struct player_index_element *arg1, struct player_index_element
            *arg2) {
  return (str_cmp(arg1->name, arg2->name));
}




/************************************************************************
*  procs of a (more or less) general utility nature			*
********************************************************************** */

/* Original fread_string was a memory leaking piece of garbage... -DM */
/* Newer fread_string was no bouquet of roses either */
int fread_string_na(char *dst, size_t max_len, FILE * f1) {
  if (!dst) {
    perror("Fread_string");
    assert(0);
  }

  size_t i = 0, tmp;

  dst[0] = '\0';

  while (i < max_len - 2) {
    tmp = fgetc(f1);
    if (!tmp) {
      perror("Fread_string");
      assert(0);
    }

    if (tmp == '~') {
      break;
    }

    dst[i++] = (char)tmp;
    if (dst[i - 1] == '\n')
      dst[i++] = '\r';
  }

  if (i == MAX_STRING_LENGTH - 3) {     /* We filled the buffer */
    dst[i] = '\0';
    log_msg("File too long (fread_string).");
    while ((tmp = fgetc(f1)) != 0)
      if (tmp == '~')
        break;
  }

  else
    dst[i] = '\0';

  fgetc(f1);

  return 0;
}

char *fread_string(FILE * f1) {
  char buf[MAX_STRING_LENGTH];
  int i = 0, tmp;

  buf[0] = '\0';

  while (i < MAX_STRING_LENGTH - 2) {
    tmp = fgetc(f1);
    if (!tmp) {
      perror("Fread_string");
      assert(0);
    }

    if (tmp == '~') {
      break;
    }

    buf[i++] = (char)tmp;
    if (buf[i - 1] == '\n')
      buf[i++] = '\r';
  }

  if (i == MAX_STRING_LENGTH - 3) {     /* We filled the buffer */
    buf[i] = '\0';
    log_msg("File too long (fread_string).");
    while ((tmp = fgetc(f1)) != 0)
      if (tmp == '~')
        break;
  }

  else
    buf[i] = '\0';

  fgetc(f1);

  return ((char *)strdup(buf));
}



/* release memory allocated for a char struct */
void free_char(struct char_data *ch) {
  int i;

  free(GET_NAME(ch));

  if (ch->player.title)
    free(ch->player.title);
  if (ch->player.short_descr)
    free(ch->player.short_descr);
  if (ch->player.long_descr)
    free(ch->player.long_descr);
  if (ch->player.description)
    free(ch->player.description);
  if (ch->player.sounds)
    free(ch->player.sounds);
  if (ch->player.distant_snds)
    free(ch->player.distant_snds);
  if (ch->specials.A_list) {
    for (i = 0; i < 10; i++) {
      if (GET_ALIAS(ch, i))
        free(GET_ALIAS(ch, i));
    }
    free(ch->specials.A_list);
  }

  while (ch->affected) {
    affect_remove(ch, ch->affected);
  }

  if (ch->skills)
    free(ch->skills);

  free(ch);
}







/* release memory allocated for an obj struct */
void free_obj(struct obj_data *obj) {
  struct extra_descr_data *this, *next_one;

  free(obj->name);
  if (obj->description && *obj->description)
    free(obj->description);
  if (obj->short_description && *obj->short_description)
    free(obj->short_description);
  if (obj->action_description && *obj->action_description)
    free(obj->action_description);

  for (this = obj->ex_description; (this != 0); this = next_one) {
    next_one = this->next;
    if (this->keyword)
      free(this->keyword);
    if (this->description)
      free(this->description);
    free(this);
  }

  free(obj);
}






/* read contents of a text file, and place in buf */
int file_to_string(char *name, char *buf) {
  FILE *fl;
  char tmp[100];

  *buf = '\0';

  if (!(fl = fopen(name, "r"))) {
    perror("file-to-string");
    *buf = '\0';
    return (-1);
  }

  do {
    fgets(tmp, 99, fl);

    if (!feof(fl)) {
      if (strlen(buf) + strlen(tmp) + 2 > MAX_STRING_LENGTH) {
        log_msg("fl->strng: string too big (db.c, file_to_string)");
        *buf = '\0';
        fclose(fl);
        return (-1);
      }

      strcat(buf, tmp);
      if (buf[strlen(buf)-1] == '\n') {
	*(buf + strlen(buf) + 1) = '\0';
	*(buf + strlen(buf)) = '\r';
      }
    }
  }
  while (!feof(fl));

  fclose(fl);

  return (0);
}


void clear_dead_bit(struct char_data *ch) {

  FILE *fl;
  struct char_file_u st;

  fl = fopen(PLAYER_FILE, "r+");
  if (!fl) {
    perror("player file");
    exit(0);
  }

  fseek(fl, ch->desc->pos * sizeof(struct char_file_u), 0);
  fread(&st, sizeof(struct char_file_u), 1, fl);
  /*
   **   this is a serious kludge, and must be changed before multiple
   **   languages can be implemented
   */
  if (st.talks[2]) {
    st.talks[2] = 0;            /* fix the 'resurrectable' bit */
    fseek(fl, ch->desc->pos * sizeof(struct char_file_u), 0);
    fwrite(&st, sizeof(struct char_file_u), 1, fl);
    ch->player.talks[2] = 0;    /* fix them both */
  }
  fclose(fl);


}

/* clear some of the the working variables of a char */
void reset_char(struct char_data *ch) {
  struct affected_type *af;
  extern struct dex_app_type dex_app[];

  int i;

  for (i = 0; i < MAX_WEAR; i++)        /* Initializing */
    ch->equipment[i] = 0;

  ch->followers = 0;
  ch->master = 0;
  ch->carrying = 0;
  ch->specials.affected_by = 0;
  ch->specials.affected_by2 = 0;
  ch->next = 0;

  ch->immune = 0;
  ch->M_immune = 0;
  ch->susc = 0;
  ch->mult_att = 1.0;

  if (!GET_RACE(ch))
    GET_RACE(ch) = RACE_HUMAN;

  if ((ch->player.class == 3) && (GET_LEVEL(ch, THIEF_LEVEL_IND))) {
    ch->player.class = 8;
    send_to_char("Setting your class to THIEF only.\n\r", ch);
  }

  for (i = 0; i < MAX_CLASS; i++) {
    if (GET_LEVEL(ch, i) > LOKI) {
      GET_LEVEL(ch, i) = 51;
    }
  }

  SET_BIT(ch->specials.act, PLR_ECHO);

  ch->hunt_dist = 0;
  ch->hatefield = 0;
  ch->fearfield = 0;
  ch->hates.clist = 0;
  ch->fears.clist = 0;

  /* AC adjustment */
  GET_AC(ch) = 100;

  GET_HITROLL(ch) = 0;

  if (GET_RACE(ch) == RACE_OGRE)
    GET_DAMROLL(ch) = 1;
  else
    GET_DAMROLL(ch) = 0;

  ch->next_fighting = 0;
  ch->next_in_room = 0;
  ch->specials.fighting = 0;
  ch->specials.position = POSITION_STANDING;
  ch->specials.default_pos = POSITION_STANDING;
  ch->specials.carry_weight = 0;
  ch->specials.carry_items = 0;
  ch->specials.spellfail = 101;

  if (GET_HIT(ch) <= 0)
    GET_HIT(ch) = 1;
  if (GET_MOVE(ch) <= 0)
    GET_MOVE(ch) = 1;
  if (GET_MANA(ch) <= 0)
    GET_MANA(ch) = 1;

  ch->points.max_mana = 0;
  ch->points.max_move = 0;

  if (IS_IMMORTAL(ch)) {
    GET_BANK(ch) = 0;
    GET_GOLD(ch) = 100000;
  }

  if (GET_BANK(ch) > get_max_level(ch) * 100000) {
    log_msgf("%s has %d coins in bank.", GET_NAME(ch), GET_BANK(ch));
  }
  if (GET_GOLD(ch) > get_max_level(ch) * 100000) {
    log_msgf("%s has %d coins.", GET_NAME(ch), GET_GOLD(ch));
  }

  /*
     Class specific Stuff
   */

  class_specific_stuff(ch);

  if (has_class(ch, CLASS_MONK)) {
    GET_AC(ch) -= MIN(150, (GET_LEVEL(ch, MONK_LEVEL_IND) * 5));
    ch->points.max_move += GET_LEVEL(ch, MONK_LEVEL_IND);
  }
  else if (GET_RACE(ch) == RACE_OGRE)
    GET_AC(ch) -= 15;

  if (has_class(ch, CLASS_MAGIC_USER) ||
      has_class(ch, CLASS_CLERIC) || has_class(ch, CLASS_DRUID)) {
    ch->specials.prompt = 7;    /* these are bit types */
  }
  else if (has_class(ch, CLASS_THIEF) ||
           has_class(ch, CLASS_WARRIOR) || has_class(ch, CLASS_MONK)) {
    ch->specials.prompt = 3;
  }
  else {
    ch->specials.prompt = 1;
  }

  /*
     racial stuff
   */
  ch->specials.intrinsics = 0;
  set_racial_stuff(ch);         /* this sets intrinsics */
  ch->specials.affected_by |= ch->specials.intrinsics;

/*
  update the affects on the character.
*/

  ch->specials.sev = 5;
  ch->specials.pct = 20;        /* Make default wimpy percent be 20% (original) */
  ch->specials.flee = 1;        /* Make default flee rooms = 1 (original) */
  ch->specials.loot = FALSE;    /* Make default autoloot OFF */
  ch->specials.split = FALSE;   /* Make default autosplit OFF */
  ch->specials.bitten = FALSE;  /* Nope, sorry, no one is bitten, at first */

  for (af = ch->affected; af; af = af->next)
    affect_modify(ch, af->location, (int)af->modifier, af->bitvector, TRUE);

  if (!has_class(ch, CLASS_MONK))
    GET_AC(ch) += dex_app[(int)GET_DEX(ch)].defensive;
  if (GET_AC(ch) > 100)
    GET_AC(ch) = 100;


/*
  clear out the 'dead' bit on characters
*/
  if (ch->desc)
    clear_dead_bit(ch);

}



/* clear ALL the working variables of a char and do NOT free any space alloc'ed*/
void clear_char(struct char_data *ch) {
  memset(ch, 0, sizeof(struct char_data));

  ch->in_room = NOWHERE;
  ch->specials.was_in_room = NOWHERE;
  ch->specials.position = POSITION_STANDING;
  ch->specials.default_pos = POSITION_STANDING;
  GET_AC(ch) = 100;             /* Basic Armor */
}


void clear_object(struct obj_data *obj) {
  memset(obj, '\0', sizeof(struct obj_data));

  obj->item_number = -1;
  obj->in_room = NOWHERE;
  obj->eq_pos = -1;
}




/* initialize a new character only if class is set */
void init_char(struct char_data *ch) {
  int i;

  /* *** if this is our first player --- he be God *** */

  if (top_of_p_table < 0) {
    GET_EXP(ch) = 69;
    GET_LEVEL(ch, 0) = IMPLEMENTOR;
    ch->points.max_hit = 1000;
  }

  set_title(ch);

  ch->player.short_descr = 0;
  ch->player.long_descr = 0;
  ch->player.description = 0;

  ch->player.hometown = number(1, 4);

  ch->player.time.birth = time(0);
  ch->player.time.played = 0;
  ch->player.time.logon = time(0);

  for (i = 0; i < MAX_TOUNGE; i++)
    ch->player.talks[i] = 0;

  GET_STR(ch) = 9;
  GET_INT(ch) = 9;
  GET_WIS(ch) = 9;
  GET_DEX(ch) = 9;
  GET_CON(ch) = 9;
  GET_CHR(ch) = 9;

  /* make favors for sex */
  if (GET_RACE(ch) == RACE_HUMAN) {
    if (ch->player.sex == SEX_MALE) {
      ch->player.weight = number(120, 180);
      ch->player.height = number(160, 200);
    }
    else {
      ch->player.weight = number(100, 160);
      ch->player.height = number(150, 180);
    }
  }
  else if (GET_RACE(ch) == RACE_DWARF || (GET_RACE(ch) == RACE_GNOME)) {
    if (ch->player.sex == SEX_MALE) {
      ch->player.weight = number(120, 180);
      ch->player.height = number(100, 150);
    }
    else {
      ch->player.weight = number(100, 160);
      ch->player.height = number(100, 150);
    }
  }
  else if (GET_RACE(ch) == RACE_HALFLING) {
    if (ch->player.sex == SEX_MALE) {
      ch->player.weight = number(70, 120);
      ch->player.height = number(80, 120);
    }
    else {
      ch->player.weight = number(60, 110);
      ch->player.height = number(70, 115);
    }

  }
  else if (GET_RACE(ch) == RACE_ELVEN) {
    if (ch->player.sex == SEX_MALE) {
      ch->player.weight = number(100, 150);
      ch->player.height = number(160, 200);
    }
    else {
      ch->player.weight = number(80, 230);
      ch->player.height = number(150, 180);
    }
  }
  else {
    if (ch->player.sex == SEX_MALE) {
      ch->player.weight = number(120, 180);
      ch->player.height = number(160, 200);
    }
    else {
      ch->player.weight = number(100, 160);
      ch->player.height = number(150, 180);
    }
  }

  ch->points.mana = GET_MAX_MANA(ch);
  ch->points.hit = GET_MAX_HIT(ch);
  ch->points.move = GET_MAX_MOVE(ch);

  ch->points.move_gain = 0;
  ch->points.hit_gain = 0;
  ch->points.mana_gain = 0;

  ch->points.armor = 100;

  if (!ch->skills)
    space_for_skills(ch);

  for (i = 0; i <= MAX_SKILLS - 1; i++) {
    if (get_max_level(ch) < IMPLEMENTOR) {
      ch->skills[i].learned = 0;
      ch->skills[i].flags = 0;
    }
    else {
      ch->skills[i].learned = 100;
      ch->skills[i].flags = 0;
    }
  }

  ch->specials.affected_by = 0;
  ch->specials.affected_by2 = 0;
  ch->specials.spells_to_learn = 0;

  for (i = 0; i < 5; i++)
    ch->specials.apply_saving_throw[i] = 0;

  for (i = 0; i < 3; i++)
    GET_COND(ch, i) = (get_max_level(ch) > GOD ? -1 : 24);
}

/*
**  this duplicates the code in room_find, because it is much quicker this way.
*/
struct room_data *real_roomp(int virtual) {
#if HASH
  return hash_find(&room_db, virtual);
#else
  return ((virtual < WORLD_SIZE && virtual > -1) ? room_db[virtual] : 0);
#endif
}

/* returns the real number of the monster with given virtual number */
int real_mobile(int virtual) {
  int bot, top, mid;

  bot = 0;
  top = top_of_mobt;

  /* perform binary search on mob-table */
  for (;;) {
    mid = (bot + top) / 2;

    if ((mob_index + mid)->virtual == virtual)
      return (mid);
    if (bot >= top)
      return (-1);
    if ((mob_index + mid)->virtual > virtual)
      top = mid - 1;
    else
      bot = mid + 1;
  }
}






/* returns the real number of the object with given virtual number */
int real_object(int virtual) {
  int bot, top, mid;

  bot = 0;
  top = top_of_objt;

  /* perform binary search on obj-table */
  for (;;) {
    mid = (bot + top) / 2;

    if ((obj_index + mid)->virtual == virtual)
      return (mid);
    if (bot >= top)
      return (-1);
    if ((obj_index + mid)->virtual > virtual)
      top = mid - 1;
    else
      bot = mid + 1;
  }
}

int obj_room_count(int nr, struct room_data *rp) {
  struct obj_data *o;
  int count = 0;

  for (o = rp->contents; o; o = o->next_content) {
    if (o->item_number == nr) {
      count++;
    }
  }
  return (count);
}

int str_len(char *buf) {
  int i;
  for (i = 0; buf[i] != '\0'; i++);
  return (i);
}


int load() {
  return (0);
}

void gr() {
  return;
}

int workhours() {
  return (0);
}

void reboot_text(struct char_data *ch, char *UNUSED(arg),
                 const char * UNUSED(cmd)) {
  if (IS_NPC(ch))
    return;

  log_msg("Rebooting Essential Text Files.");

  file_to_string(NEWS_FILE, news);
  file_to_string(CREDITS_FILE, credits);
  file_to_string(MOTD_FILE, motd);
  file_to_string("wizmotd", wmotd);

  fclose(mob_f);
  fclose(obj_f);
  top_of_mobt = 0;
  top_of_objt = 0;
  free(mob_index);
  free(obj_index);

  log_msg("Opening mobile, object and help files.");
  if (!(mob_f = fopen(MOB_FILE, "r"))) {
    perror("boot");
    assert(0);
  }

  if (!(obj_f = fopen(OBJ_FILE, "r"))) {
    perror("boot");
    assert(0);
  }


  log_msg("Generating index tables for mobile and object files.");
  mob_index = make_mob_indices(generate_indices(mob_f, &top_of_mobt),
                               top_of_mobt);
  obj_index = make_obj_indices(generate_indices(obj_f, &top_of_objt),
                               top_of_objt);

/* log_msg("Initializing Scripts.");
 init_scripts();
*/
/* jdb -- you don't appear to re-install the scripts after you
   reset the script db
   */
/*
  for (p = character_list;p;p=p->next) {
    for(i = 0; i < top_of_scripts; i++) {
      if(script_data[i].virtual == mob_index[p->nr].virtual) {
	SET_BIT(p->specials.act, ACT_SCRIPT);
	SPRINTF(buffer, "Setting SCRIPT bit for mobile %s, file %s.", GET_NAME(p), script_data[i].filename);
	log_msg(buffer);
	p->script = i;
	break;
      }
    }
  }
*/
  return;
}


void init_scripts() {
  char buf[MAX_BUF_LENGTH * 2], buf2[255];
  FILE *f1, *f2;
  int i, count;
  struct char_data *mob;

  if (!script_data)
    top_of_scripts = 0;

  /* what is ths for?  turn off all the scripts ??? */
  /* -yes, just in case the script file was removed, saves pointer probs */

  for (mob = character_list; mob; mob = mob->next)
    if (IS_MOB(mob) && IS_SET(mob->specials.act, ACT_SCRIPT)) {
      mob->commandp = 0;
      REMOVE_BIT(mob->specials.act, ACT_SCRIPT);
    }

  if (!(f1 = fopen("scripts.dat", "r"))) {
    log_msg("Unable to open file \"scripts.dat\".");
    return;
  }

  if (script_data) {
    int i = 0;
    for (; i < top_of_scripts; i++) {
      free(script_data[i].script);
      free(script_data[i].filename);
    }
    free(script_data);
    top_of_scripts = 0;
  }


  script_data = NULL;
  script_data = (struct scripts *)malloc(sizeof(struct scripts));

  while (1) {
    if (fgets(buf, 254, f1) == NULL)
      break;

    if (buf[strlen(buf) - 1] == '\n')
      buf[strlen(buf) - 1] = '\0';

    if (strlen(buf) < 4) {      /* no way we can get a valid thing in less */
      char garbage[4];
      strncpy(garbage, buf, 3);
      garbage[3] = '\0';
      log_msgf("%s read in, garbage.", garbage);
    }

    sscanf(buf, "%s %d", buf2, &i);

    SPRINTF(buf, "scripts/%s", buf2);
    if (!(f2 = fopen(buf, "r"))) {
      log_msgf("Unable to open script \"%s\" for reading.", buf2);
    }

    else {

      script_data =
        (struct scripts *)realloc(script_data,
                                  (top_of_scripts +
                                   1) * sizeof(struct scripts));

      count = 0;
      while (!feof(f2)) {
        fgets(buf, 254, f2);
        if (buf[strlen(buf) - 1] == '\n')
          buf[strlen(buf) - 1] = '\0';
/* you really don't want to do a lot of reallocs all at once
*/
        if (count == 0) {
          script_data[top_of_scripts].script =
            (struct foo_data *)malloc(sizeof(struct foo_data));
        }
        else {
          script_data[top_of_scripts].script =
            (struct foo_data *)realloc(script_data[top_of_scripts].script,
                                       sizeof(struct foo_data) * (count + 1));
        }
        log_msgf("top_of_scripts %d\n", top_of_scripts);
        log_msgf("count %d\n", count);
        log_msgf("buf2: %s\n", buf2);
        script_data[top_of_scripts].script[count].line =
          (char *)malloc(sizeof(char) * (strlen(buf) + 1));

        strcpy(script_data[top_of_scripts].script[count].line, buf);

        count++;
      }

      script_data[top_of_scripts].virtual = i;
      script_data[top_of_scripts].filename =
        (char *)malloc((strlen(buf2) + 1) * sizeof(char));
      strcpy(script_data[top_of_scripts].filename, buf2);
      log_msgf("Script %s assigned to mobile %d.", buf2, i);
      top_of_scripts++;
      fclose(f2);
    }
  }

  if (top_of_scripts)
    log_msgf("%d scripts assigned.", top_of_scripts);
  else
    log_msgf("No scripts found to assign.");

  fclose(f1);
}

int check_kill_file(int virtual) {
  FILE *f1;
  char buf[255];
  int i;

  if (!(f1 = fopen(KILL_FILE, "r"))) {
    log_msg("Unable to find killfile.");
    exit(0);
  }

  while (fgets(buf, 254, f1) != NULL) {
    sscanf(buf, "%d", &i);
    if (i == virtual) {
      fclose(f1);
      return (1);
    }
  }

  fclose(f1);
  return (0);
}

void reload_rooms() {
  int i;

  for (i = 0; i < number_of_saved_rooms; i++)
    load_room_objs(saved_rooms[i]);
}


void save_the_world() {
#if SAVE_WORLD
  static int ctl = 0;
  char cmd, buf[80];
  int i, j, arg1, arg2, arg3;
  struct char_data *p;
  struct obj_data *o;
  struct room_data *room;
  FILE *fp;

  if (ctl == 30000)
    ctl = 0;

  SPRINTF(buf, "world/mobs.%d", ctl);
  fp = (FILE *) fopen(buf, "w");        /* append */

  if (!fp) {
    log_msg("Unable to open zone writing file.");
    return;
  }

  i = ctl;
  ctl += 1000;

  for (; i < ctl; i++) {
    room = real_roomp(i);
    if (room && !IS_SET(room->room_flags, DEATH)) {
      /*
       *  first write out monsters
       */
      for (p = room->people; p; p = p->next_in_room) {
        if (!IS_PC(p)) {
          cmd = 'M';
          arg1 = mob_vnum(p);
          arg2 = mob_index[p->nr].number;
          arg3 = i;
          zwrite(fp, cmd, 0, arg1, arg2, arg3, p->player.short_descr);
          fprintf(fp, "Z 1 %d 1\n", p->specials.zone);

          /* save hatreds && fears */
          if (IS_SET(p->hatefield, HATE_SEX))
            fprintf(fp, "H 1 %d %d -1\n", OP_SEX, p->hates.sex);
          if (IS_SET(p->hatefield, HATE_RACE))
            fprintf(fp, "H 1 %d %d -1\n", OP_RACE, p->hates.race);
          if (IS_SET(p->hatefield, HATE_GOOD))
            fprintf(fp, "H 1 %d %d -1\n", OP_GOOD, p->hates.good);
          if (IS_SET(p->hatefield, HATE_EVIL))
            fprintf(fp, "H 1 %d %d -1\n", OP_EVIL, p->hates.evil);
          if (IS_SET(p->hatefield, HATE_CLASS))
            fprintf(fp, "H 1 %d %d -1\n", OP_CLASS, p->hates.class);
          if (IS_SET(p->hatefield, HATE_VNUM))
            fprintf(fp, "H 1 %d %d -1\n", OP_VNUM, p->hates.vnum);

          if (IS_SET(p->fearfield, FEAR_SEX))
            fprintf(fp, "H 1 %d %d -1\n", OP_SEX, p->fears.sex);
          if (IS_SET(p->fearfield, FEAR_RACE))
            fprintf(fp, "H 1 %d %d -1\n", OP_RACE, p->fears.race);
          if (IS_SET(p->fearfield, FEAR_GOOD))
            fprintf(fp, "H 1 %d %d -1\n", OP_GOOD, p->fears.good);
          if (IS_SET(p->fearfield, FEAR_EVIL))
            fprintf(fp, "H 1 %d %d -1\n", OP_EVIL, p->fears.evil);
          if (IS_SET(p->fearfield, FEAR_CLASS))
            fprintf(fp, "H 1 %d %d -1\n", OP_CLASS, p->fears.class);
          if (IS_SET(p->fearfield, FEAR_VNUM))
            fprintf(fp, "H 1 %d %d -1\n", OP_VNUM, p->fears.vnum);

          for (j = 0; j < MAX_WEAR; j++) {
            if (p->equipment[j]) {
              if (p->equipment[j]->item_number >= 0) {
                cmd = 'E';
                arg1 = obj_vnum(p->equipment[j]);
                arg2 = obj_index[p->equipment[j]->item_number].number;
                arg3 = j;
                strcpy(buf, p->equipment[j]->short_description);
                zwrite(fp, cmd, 1, arg1, arg2, arg3, buf);
                rec_zwrite_obj(fp, p->equipment[j]);
              }
            }
          }
          for (o = p->carrying; o; o = o->next_content) {
            if (o->item_number >= 0) {
              cmd = 'G';
              arg1 = obj_vnum(o);
              arg2 = obj_index[o->item_number].number;
              arg3 = 0;
              strcpy(buf, o->short_description);
              zwrite(fp, cmd, 1, arg1, arg2, arg3, buf);
              rec_zwrite_obj(fp, o);
            }
          }
        }
      }
    }
  }
  fprintf(fp, "S\n");
  fclose(fp);
#endif
}

void read_text_zone(FILE * fl) {
  while (1) {
    char c, buf[255], count = 0, last_cmd = 1;
    int i, j, k, tmp, zone = 0;
    struct char_data *mob = NULL, *master = NULL;
    struct room_data *rp;
    struct obj_data *obj, *obj_to;

    count++;
    fscanf(fl, " ");            /* skip blanks */
    fscanf(fl, "%c", &c);


    if (c == 'S' || c == EOF)
      break;

    if (c == '*') {
      fgets(buf, 80, fl);       /* skip command */
      continue;
    }

    fscanf(fl, " %d %d %d", &tmp, &i, &j);
    if (c == 'M' || c == 'O' || c == 'C' || c == 'E' || c == 'P' || c == 'D')
      fscanf(fl, " %d", &k);

    fgets(buf, 80, fl);         /* read comment */
    if (last_cmd || tmp <= 0)
      switch (c) {
      case 'M':                /* read a mobile */
        i = real_mobile(i);
        if ((mob_index[i].number < j)
            && !check_kill_file(mob_index[i].virtual)) {
          mob = read_mobile(i, REAL);
          if (!mob) {
            continue;
          }
          char_to_room(mob, k);

          last_cmd = 1;
          master = mob;
        }
        else
          last_cmd = 0;
        break;

      case 'C':                /* read a mobile.  Charm them to follow prev. */
        i = real_mobile(i);
        if ((mob_index[i].number < j)
            && !check_kill_file(mob_index[i].virtual)) {
          mob = read_mobile(i, REAL);
          if (!mob) {
            continue;
          }
          if (master) {
            char_to_room(mob, master->in_room);
            /*
               add the charm bit to the dude.
             */
            add_follower(mob, master);
            SET_BIT(mob->specials.affected_by, AFF_CHARM);
            SET_BIT(mob->specials.act, k);
          }
          else {
            extract_char(mob);
            last_cmd = 0;
          }
          last_cmd = 1;
        }
        else
          last_cmd = 0;
        break;

      case 'Z':                /* set the last mobile to this zone */
        if (mob) {
          mob->specials.zone = i;

          if (GET_RACE(mob) > RACE_GNOME)
            if (!strchr(zone_table[i].races, GET_RACE(mob))) {
              zone_table[i].races[strlen(zone_table[i].races)] = GET_RACE(mob);
            }
          last_cmd = 1;
        }
        else {
          last_cmd = 0;
        }
        break;

      case 'O':                /* read an object */
        i = real_object(i);
        if (obj_index[i].number < j) {
          if (j >= 0 && ((rp = real_roomp(j)) != NULL)) {
            if ((tmp > 0 && obj_room_count(i, rp) < tmp) ||
                (tmp <= 0 && obj_room_count(i, rp) < (-tmp) + 1)) {
              if ((obj = read_object(i, REAL)) != NULL) {
                obj_to_room(obj, k);
                last_cmd = 1;
              }
              else {
                last_cmd = 0;
              }
            }
            else {
              last_cmd = 0;
            }
          }
          else if ((obj = read_object(i, VIRTUAL)) != NULL) {
            log_msgf("Error finding room #%d", k);
            last_cmd = 1;
          }
          else {
            last_cmd = 0;
          }
        }
        break;

      case 'P':                /* object to object */
        i = real_object(i);
        if (obj_index[i].number < j) {
          obj = read_object(i, VIRTUAL);
          if (!obj) {
            return;
          }
          obj_to = get_obj_num(k);
          if (obj_to && obj) {
            obj_to_obj(obj, obj_to);
            last_cmd = 1;
          }
          else {
            last_cmd = 0;
          }
        }
        else
          last_cmd = 0;
        break;

      case 'G':                /* obj_to_char */
        i = real_object(i);
        if (obj_index[i].number < j && (obj = read_object(i, REAL))) {
          obj_to_char(obj, mob);
          last_cmd = 1;
#ifndef NEW_RENT
        }
        else {
          last_cmd = 0;
#endif
        }
        break;

      case 'H':                /* hatred to char */

        if (add_hatred(mob, i, j))
          last_cmd = 1;
        else
          last_cmd = 0;
        break;

      case 'F':                /* fear to char */

        if (add_fears(mob, i, j))
          last_cmd = 1;
        else
          last_cmd = 0;
        break;

      case 'E':                /* object to equipment list */
        i = real_object(i);
        if (obj_index[i].number < j && (obj = read_object(i, REAL))) {
          if (!mob->equipment[k]) {
            equip_char(mob, obj, k);
          }
          else {
            log_lev_msgf(LOG_ALERT,
                         "eq error - zone %d, cmd %d, item %d, mob %d, loc %d",
                         zone, 1, obj_index[i].virtual,
                         mob_index[mob->nr].virtual, k);
          }
          last_cmd = 1;
        }
        else
          last_cmd = 0;
        break;

      case 'D':                /* set state of door */
        rp = real_roomp(i);
        if (rp && rp->dir_option[j]) {
          switch (k) {
          case 0:
            SET_BIT(rp->dir_option[j]->exit_info, EX_ISDOOR);
            REMOVE_BIT(rp->dir_option[j]->exit_info, EX_LOCKED);
            REMOVE_BIT(rp->dir_option[j]->exit_info, EX_CLOSED);
            break;
          case 1:
            SET_BIT(rp->dir_option[j]->exit_info, EX_ISDOOR);
            SET_BIT(rp->dir_option[j]->exit_info, EX_CLOSED);
            REMOVE_BIT(rp->dir_option[j]->exit_info, EX_LOCKED);
            break;
          case 2:
            SET_BIT(rp->dir_option[j]->exit_info, EX_ISDOOR);
            SET_BIT(rp->dir_option[j]->exit_info, EX_LOCKED);
            SET_BIT(rp->dir_option[j]->exit_info, EX_CLOSED);
            break;
          }
          last_cmd = 1;
        }
        else {
          /* that exit doesn't exist anymore */
        }
        break;

      default:
        break;
      }
  }

}

void boot_figurines() {
  FILE *f1;
  char buf[255];

  if (!(f1 = fopen("figurines", "r"))) {
    log_msg("Unable to open file \"figurines\".");
    return;
  }

  while (fgets(buf, 254, f1)) {
    sscanf(buf, "%d %d\n", &figurine[fig_count].obj, &figurine[fig_count].mob);
    fig_count++;
    if (fig_count >= 255)
      fig_count = 254;
  }
  fclose(f1);
}

int verify_mob(struct char_data *ch) {
  /* check to see that the mob falls within certain parameters */

  if (ch->specials.damnodice < 0) {
    log_lev_msgf(LOG_ALERT,
                 "%s's number of damage dice is negative\n",
                 ch->player.name);
  }

  if (ch->specials.damsizedice < 0) {
    log_lev_msgf(LOG_ALERT, "%s's size of damage dice is negative\n",
                 ch->player.name);
  }
  return (1);
}

void clean_playerfile() {
  struct junk {
    struct char_file_u dummy;
    bool AXE;
  };

  struct junk grunt;

  time_t timeH;
  char buf[80];
  FILE *f, *f2;
  int j, max, num_processed, num_deleted, num_demoted, ones;

  num_processed = num_deleted = num_demoted = ones = 0;
  timeH = time(0);

  if (!(f = fopen(PLAYER_FILE, "rb+"))) {
    perror("clean player file");
    exit(0);
  }

  if (!(f2 = fopen("temp", "w+"))) {
    perror("clean player file");
    exit(0);
  }


  for (; !feof(f);) {
    fread(&(grunt.dummy), sizeof(struct char_file_u), 1, f);
    if (!feof(f)) {             /* we have someone */
      num_processed++;
      grunt.AXE = FALSE;
      if (!str_cmp(grunt.dummy.name, "111111")) {
        log_msgf("%s was deleted (111111 name hopefully).",
                 grunt.dummy.name);
        ones++;
        num_deleted++;
        grunt.AXE = TRUE;
      }
      else {
        for (j = 0, max = 0; j < 6; j++)
          if (grunt.dummy.level[j] > max)
            max = grunt.dummy.level[j];
        if (max < LOW_IMMORTAL) {
          j = 1;
          if (max > 15)
            j++;
          if (max > 30)
            j++;
          if (max > 45)
            j++;

          if (timeH - grunt.dummy.last_logon >
              (long)j * (SECS_PER_REAL_DAY * 30)) {
            num_deleted++;
            grunt.AXE = TRUE;
            log_msgf("%s deleted after %d months of inactivity.",
                     grunt.dummy.name, j);
          }
        }
        else if (max > LOW_IMMORTAL) {
          if (timeH - grunt.dummy.last_logon > (long)SECS_PER_REAL_DAY * 30) {
            num_demoted++;
            log_msgf("%s demoted from %d to %d due to inactivity.",
                     grunt.dummy.name, max, max - 1);
            grunt.dummy.last_logon = timeH;     /* so it doesn't happen twice */
            max--;
            max = MAX(51, max); /* should not be necessary */

            for (j = 0; j < 6; j++)
              grunt.dummy.level[j] = max;

          }
        }
      }
      if (!grunt.AXE)
        fwrite(&(grunt.dummy), sizeof(struct char_file_u), 1, f2);
    }
  }

  log_msgf("-- %d characters were processed.", num_processed);
  log_msgf("-- %d characters were deleted.  ", num_deleted);
  log_msgf("-- %d of these were allread deleted. (11111s)", ones);
  log_msgf("-- %d gods were demoted due to inactivity.", num_demoted);
  SPRINTF(buf, "mv %s %s.bak", PLAYER_FILE, PLAYER_FILE);
  system(buf);
  SPRINTF(buf, "mv temp %s", PLAYER_FILE);
  system(buf);
  log_msg("Cleaning done.");

}

void ensure_file_exists(const char *path) {
  struct stat stats;
  int result;

  result = stat(path, &stats);
  if (result == 0)
    return;
  if (errno == ENOENT) {
    int fd;
    log_msgf("Creating empty file \"%s\"", path);
    if ((fd = open(path, O_CREAT | O_WRONLY, 0644)) == -1) {
      char *buf;
      const char *fmt = "ensure_file_exists(%s)(open)";
      int len = strlen(path) + strlen(fmt) - 1;
      buf = (char *)malloc(len);
      snprintf(buf, len, fmt, path);
      perror(buf);
      free(buf);
      exit(-1);
    }
    close(fd);
  }
  else {
    char *buf;
    const char *fmt = "ensure_file_exists(%s)(stat)";
    int len = strlen(path) + strlen(fmt) - 1;
    buf = (char *)malloc(len);
    snprintf(buf, len, fmt, path);
    perror(buf);
    free(buf);
    exit(-1);
  }
}
