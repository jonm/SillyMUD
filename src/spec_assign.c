/*
  SillyMUD Distribution V1.1b             (c) 1993 SillyMUD Developement
 
  See license.doc for distribution terms.   SillyMUD is based on DIKUMUD
*/
#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "protos.h"
#include "board.h"

#if HASH
extern struct hash_header room_db;
#else
extern struct room_data *room_db;
#endif
extern struct index_data *mob_index;
extern struct index_data *obj_index;
void boot_the_shops();
void assign_the_shopkeepers();

struct special_proc_entry {
  int vnum;
  int (*proc) ();
};

/* ********************************************************************
*  Assignments                                                        *
******************************************************************** */

/* put here so we don't have to recompile EVERYTHING */
int death_knight(struct char_data *ch, int cmd, char *arg,
                 struct char_data *mob, int type);


/* assign special procedures to mobiles */
void assign_mobiles() {

  static struct special_proc_entry specials[] = {

    {1, puff},
    {2, ringwraith},
    {3, tormentor},
    {4, inquisitor},
    {6, acid_blob},
    {25, magic_user},

    {30, mage_guild_master},
    {31, cleric_guild_master},
    {32, thief_guild_master},
    {33, warrior_guild_master},
    {34, mage_guild_master},
    {35, cleric_guild_master},
    {36, thief_guild_master},
    {37, warrior_guild_master},
    {38, fighter},              /* armor golem */
    {39, creeping_death},

    {199, AGGRESSIVE},
    {200, AGGRESSIVE},
/*
**  D&D standard
*/

    {210, snake},               /* spider */
    {211, fighter},             /* gnoll  */
    {220, fighter},             /* fighter */
    {221, fighter},             /* bugbear */
    {223, ghoul},               /* ghoul */
    {226, fighter},             /* ogre */
    {236, ghoul},               /* ghast */
    {227, snake},               /* spider */
    {230, breath_weapon_mob},   /* baby black */
    {232, blink},               /* blink dog */
    {233, breath_weapon_mob},   /* baby blue */
    {234, cleric},              /* cleric */
    {239, shadow},              /* shadow    */
    {240, snake},               /* toad      */
    {243, breath_weapon_mob},   /* teenage white */
    {247, fighter},             /* minotaur */
    {251, carrion_crawler},
    {261, fighter},
    {262, regenerator},
    {264, fighter},
    {265, magic_user},
    {266, magic_user},
    {267, devil},
    {269, demon},
    {271, regenerator},
    {248, snake},               /* snake       */
    {249, snake},               /* snake       */
    {250, snake},               /* snake       */
    {257, magic_user},          /* magic_user  */

    {600, druid_challenger},
    {601, druid_challenger},
    {602, druid_challenger},
    {603, druid_challenger},
    {604, druid_challenger},
    {605, druid_challenger},
    {606, druid_challenger},
    {607, druid_challenger},
    {608, druid_challenger},
    {609, druid_challenger},
    {610, druid_challenger},
    {611, druid_challenger},
    {612, druid_challenger},
    {613, druid_challenger},
    {614, druid_challenger},
    {615, druid_challenger},
    {616, druid_challenger},
    {617, druid_challenger},
    {618, druid_challenger},
    {619, druid_challenger},
    {620, druid_challenger},
    {621, druid_challenger},
    {622, druid_challenger},
    {623, druid_challenger},
    {624, druid_challenger},
    {625, druid_challenger},
    {626, druid_challenger},
    {627, druid_challenger},
    {628, druid_challenger},
    {629, druid_challenger},
    {630, druid_challenger},
    {631, druid_challenger},
    {632, druid_challenger},
    {633, druid_challenger},
    {634, druid_challenger},
    {635, druid_challenger},
    {636, druid_challenger},
    {637, druid_challenger},
    {638, druid_challenger},
    {639, druid_challenger},
    {640, druid_challenger},
    {641, druid_guild_master},
    {642, druid_guild_master},

    {651, monk_challenger},
    {652, monk_challenger},
    {653, monk_challenger},
    {654, monk_challenger},
    {655, monk_challenger},
    {656, monk_challenger},
    {657, monk_challenger},
    {658, monk_challenger},
    {659, monk_challenger},
    {660, monk_challenger},
    {661, monk_challenger},
    {662, monk_challenger},
    {663, monk_challenger},
    {664, monk_challenger},
    {665, monk_challenger},
    {666, monk_challenger},
    {667, monk_challenger},
    {668, monk_challenger},
    {669, monk_challenger},
    {670, monk_challenger},
    {671, monk_challenger},
    {672, monk_challenger},
    {673, monk_challenger},
    {674, monk_challenger},
    {675, monk_challenger},
    {676, monk_challenger},
    {677, monk_challenger},
    {678, monk_challenger},
    {679, monk_challenger},
    {680, monk_challenger},
    {681, monk_challenger},
    {682, monk_challenger},
    {683, monk_challenger},
    {684, monk_challenger},
    {685, monk_challenger},
    {686, monk_challenger},
    {687, monk_challenger},
    {688, monk_challenger},
    {689, monk_challenger},
    {690, monk_challenger},
    {691, monk_master},

/*
  frost giant area 
*/

    {9401, fighter},
    {9403, magic_user},
    {9404, fighter},
    {9405, thief},
    {9406, fighter},
    {9407, fighter},
    {9408, fighter},
    {9409, fighter},
    {9410, fighter},
    {9411, fighter},
    {9412, fighter},
    {9413, fighter},
    {9414, fighter},
    {9415, fighter},
    {9416, fido},
    {9418, breath_weapon_mob},
    {9419, breath_weapon_mob},
    {9420, fighter},
    {9421, fighter},
    {9424, storm_giant},
    {9426, monk_challenger},
    {9427, cleric},
    {9428, magic_user},
    {9429, fighter},
    {9430, regenerator},
    {9431, snake},
    {9432, magic_user},
    {9433, fighter},
    {9434, fighter},
    {9435, snake},
    {9436, fido},

/*
**   shire
*/
    {1000, magic_user},
    {1035, fighter},
    {1012, fighter},
    {1026, fighter},
    {1010, fighter},
    {1011, fighter},
    {1012, fighter},
    {1014, fighter},
    {1015, fighter},
    {1016, fighter},
    {1017, fighter},
    {1001, fighter},
    {1023, fighter},
    {1031, receptionist},
    {1032, fighter},

    {1701, monk},
    {1702, monk},
    {1703, monk},
    {1704, monk},
    {1705, monk},
    {1706, monk},
    {1707, monk},
    {1708, monk},
    {1709, monk},
    {1710, monk},
    {1711, monk},
    {1712, monk},
    {1713, monk},
    {1714, monk},
    {1715, monk},
    {1716, monk},
    {1717, monk},
    {1718, monk},

    /* Thand's thief area */
    {1105, thief},
    {1108, thief},
    {1115, fido},
    /* end of Thand's thief area */

    {6001, real_rabbit},
    {6005, real_fox},
/*
  prydain
*/
    {6601, prydain_guard},
    {6602, prydain_guard},
    {6604, fighter},
    {6605, prydain_guard},
    {6606, prydain_guard},
    {6608, fighter},
    {6613, fighter},
    {6619, prydain_guard},
    {6620, prydain_guard},
    {6621, fighter},
    {6622, fighter},
    {6614, prydain_guard},
    {6609, breath_weapon_mob},
    {6642, breath_weapon_mob},
    {6640, jugglernaut},
    {6612, magic_user},
    {6615, magic_user},
    {6616, magic_user},
    {6624, magic_user},
    {6637, magic_user},
    {6634, fighter},
    {6635, breath_weapon_mob},
    {6625, demon},
    {6638, stat_teller},

/*
  deadhame
*/
    {24782, fighter},

/*
**  G1
*/
    {9200, fighter},
    {9201, fighter},
    {9202, fighter},
    {9203, fighter},
    {9204, fighter},
    {9206, fighter},
    {9207, fighter},
    {9211, fighter},
    {9212, fighter},
    {9216, fighter},
    {9213, carrion_crawler},
    {9208, cleric},
    {9217, breath_weapon_mob},
    {9218, fighter},

/*
**  chessboard
*/
    {1400, chess_game},         /* black pieces */
    {1401, chess_game},
    {1402, chess_game},
    {1403, chess_game},
    {1404, chess_game},
    {1405, chess_game},
    {1406, chess_game},
    {1407, chess_game},
    {1408, chess_game},
    {1409, chess_game},
    {1410, chess_game},
    {1411, chess_game},
    {1412, chess_game},
    {1413, chess_game},
    {1414, chess_game},
    {1415, chess_game},

    {1448, chess_game},         /* white pieces */
    {1449, chess_game},
    {1450, chess_game},
    {1451, chess_game},
    {1452, chess_game},
    {1453, chess_game},
    {1454, chess_game},
    {1455, chess_game},
    {1456, chess_game},
    {1457, chess_game},
    {1458, chess_game},
    {1459, chess_game},
    {1460, chess_game},
    {1461, chess_game},
    {1462, chess_game},
    {1463, chess_game},

    {1499, sisyphus},
    {1471, paramedics},
    {1470, jabberwocky},
    {1472, flame},
    {1437, banana},
    {1428, jugglernaut},
    {1495, delivery_elf},
    {1493, delivery_beast},

/*
**  Bandits Temple
*/
    {2113, ghoul},
    {2115, ghost},
    {2116, ghost},
    {2111, cleric},
    {2112, cleric},
    {2117, druid_protector},


    /* Astral plane */
    {2715, astral_portal},
    {2716, astral_portal},
    {2717, astral_portal},
    {2718, astral_portal},
    {2719, astral_portal},
    {2720, astral_portal},
    {2721, astral_portal},
    {2722, astral_portal},
    {2723, astral_portal},
    {2724, astral_portal},
    {2725, astral_portal},
    {2726, astral_portal},
    {2727, astral_portal},
    {2728, astral_portal},
    {2729, astral_portal},
    {2730, astral_portal},
    {2731, astral_portal},
    {2732, astral_portal},
    {2733, astral_portal},
    {2734, astral_portal},
    {2735, astral_portal},
    {2736, astral_portal},


/*
**  Valley of the Mage
*/
    {21106, snake},
    {21107, rust_monster},
    {21108, wraith},
    {21111, web_slinger},
    {21112, trapper},
    {21114, troguard},
    {21121, trogcook},
    {21122, shaman},
    {21123, troguard},
    {21124, golgar},
    {21118, troguard},
    {21119, troguard},
/*
    { 21130, valik},
*/
    {21135, regenerator},
    {21138, ghostsoldier},
    {21139, ghostsoldier},
/*
    { 21140, keystone},
    { 21141, lattimore},
    { 21142, guardian},
*/
    {21144, troguard},
    {21145, troguard},
    {21146, coldcaster},
    {21147, rust_monster},

/*
**  New Thalos
*/
    {3600, mage_guild_master},
    {3601, cleric_guild_master},
    {3602, warrior_guild_master},
    {3603, thief_guild_master},
    {3604, receptionist},
    {3619, fighter},
    {3620, fighter},
    {3632, fighter},
    {3634, fighter},
    {3636, fighter},
    {3638, fighter},
    {3639, fighter},            /* caramon */
    {3641, cleric},             /* curley g. */
    {3640, magic_user},         /* raist */
    {3656, new_thalos_guild_guard},
    {3657, new_thalos_guild_guard},
    {3658, new_thalos_guild_guard},
    {3659, new_thalos_guild_guard},
    {3661, sultan_guard},       /* wandering */
    {3662, sultan_guard},       /* not */
    {3682, sultan_guard},       /* royal */
    {3670, breath_weapon_mob},  /* Cryohydra */
    {3674, breath_weapon_mob},  /* Behir */
    {3675, breath_weapon_mob},  /* Chimera */
    {3676, breath_weapon_mob},  /* Couatl */
    {3681, cleric},             /* High priest */
    {3689, new_thalos_mayor},   /* Guess */
    {3644, fido},
    {3635, thief},
/*
**  Skexie
*/
    {15813, magic_user},
    {15815, magic_user},
    {15820, magic_user},
    {15821, vampire},
    {15844, cleric},
    {15847, fighter},
    {15831, fighter},
    {15832, fighter},
    {15822, fighter},
    {15819, fighter},
    {15805, fighter},
/*
**  Challenge
*/
    {15858, breath_weapon_mob},
    {15861, magic_user},
    {15862, magic_user},
    {15863, fighter},
    {15864, sisyphus},
    {15877, magic_user},
    {15868, snake},
    {15866, magic_user},
    {15810, magic_user},
    {15880, fighter},
    {15879, breath_weapon_mob},
    {15873, magic_user},
    {15871, magic_user},
    {15852, fighter},
    {15875, cleric},
    {15869, magic_user},

/*
**  abyss
*/
    {25000, magic_user},        /* Demi-lich  */
    {25001, keftab},
    {25009, breath_weapon_mob}, /* hydra */
    {25002, vampire},           /* Crimson */
    {25003, storm_giant},       /* MistDaemon */
    {25006, storm_giant},       /* Storm giant */
    {25014, storm_giant},       /* DeathKnight */
    {25009, breath_weapon_mob}, /* hydra */
    {25017, abyss_gate_keeper}, /* Abyss Gate Keeper */
    {25013, fighter},           /* kalas */
    {25008, magic_user},        /* efreeti */
    {25034, fighter},           /* marilith */
    {25035, magic_user},        /* balor  */
/*
**  Paladin's guild
*/
    {25100, paladin_guild_guard},
    {25101, paladin_guild_guard},
/*
** Shark's Junk
*/
    {196, grey_paramedic},
    {197, amber_paramedic},
    {198, game_guard},
/*
**  Abyss Fire Giants
*/
    {25500, fighter},
    {25501, fighter},
    {25502, fighter},
    {25505, fighter},
    {25504, breath_weapon_mob},
    {25503, cleric},

/*
**  Temple Labrynth
*/

    {10900, temple_labrynth_liar},
    {10901, temple_labrynth_liar},
    {10902, temple_labrynth_sentry},

/*
**  Gypsy Village
*/

    {16106, fido},
    {16107, caravan_guild_guard},
    {16108, caravan_guild_guard},
    {16109, caravan_guild_guard},
    {16110, caravan_guild_guard},
    {16111, warrior_guild_master},
    {16112, mage_guild_master},
    {16113, thief_guild_master},
    {16114, cleric_guild_master},
    {16122, receptionist},
    {16105, stat_teller},

/*
**  Draagdim
*/

    {2500, nudge_nudge},        /* jailer */
/*
**  mordilnia
*/
    {18200, magic_user},
    {18205, receptionist},
    {18206, mage_guild_master},
    {18207, cleric_guild_master},
    {18208, thief_guild_master},
    {18209, warrior_guild_master},
    {18210, mord_guild_guard},  /*18266 3 */
    {18211, mord_guild_guard},  /*18276 1 */
    {18212, mord_guild_guard},  /*18272 0 */
    {18213, mord_guild_guard},  /*18256 2 */
    {18215, mord_guard},
    {18216, janitor},
    {18217, fido},
    {18218, fighter},
    {18221, fighter},
    {18222, mord_guard},
    {18223, mord_guard},

/*
**  Graecia:
*/
    {13706, fighter},
    {13709, fighter},
    {13711, fighter},
    {13714, fighter},
    {13721, fighter},
    {13722, fighter},
    {13732, snake},
    {13762, fighter},
    {13764, fighter},
    {13766, fighter},
    {13769, fighter},
    {13771, fighter},
    {13775, fighter},

    {13779, magic_user},
    {13784, magic_user},
    {13785, magic_user},
    {13787, magic_user},
    {13789, magic_user},
    {13791, magic_user},
    {13793, magic_user},
    {13795, magic_user},
    {13797, magic_user},
    {13843, fighter},



/*
**  Eastern Path
*/

    {16001, fighter},
    {16006, fighter},
    {16007, fighter},
    {16008, fighter},
    {16009, fighter},
    {16016, fighter},
    {16017, fighter},
    {16020, snake},
    {16021, cleric},
    {16022, fighter},
    {16023, thief},
    {16027, fighter},
    {16033, fighter},
    {16034, fighter},
    {16035, fighter},
    {16036, magic_user},
    {16043, fighter},
    {16050, fighter},
    {16052, fighter},
    {16048, fighter},
    {16056, cleric},
    {16057, magic_user},
    {16037, dwarven_miners},
    {16014, magic_user},
    {16039, tyrannosaurus_swallower},

/*
**  undercaves.. level 1
*/
    {16201, magic_user},
    {16204, magic_user},
    {16205, magic_user},
    {16206, magic_user},
    {16210, fighter},
    {16211, magic_user},
    {16214, fighter},
    {16215, fighter},
    {16216, cleric},
    {16217, magic_user},
    {16219, death_knight},
/*
** Sauria
*/
    {21803, tyrannosaurus_swallower},
    {21810, tyrannosaurus_swallower},

/*
**  Bay Isle
*/
    {16610, demon},
    {16620, breath_weapon_mob},
    {16640, cleric},
    {16650, cleric},

/*
**  Sewer Rats
*/
    {7002, attack_rats},
    {2531, dragon_hunter_leader},
    {3063, hunting_mercenary},

/*
**  Mages Tower
*/
    {1500, shadow},
    {1504, magic_user},
    {1506, magic_user},
    {1507, magic_user},
    {1508, magic_user},
    {1510, magic_user},
    {1514, magic_user},
    {1515, magic_user},
    {1516, magic_user},
    {1517, magic_user},
    {1518, magic_user},
    {1520, magic_user},
    {1521, magic_user},
    {1522, magic_user},
    {1523, magic_user},
    {1524, magic_user},
    {1525, magic_user},
    {1526, magic_user},
    {1527, magic_user},
    {1528, magic_user},
    {1529, magic_user},
    {1530, magic_user},
    {1531, magic_user},
    {1532, magic_user},
    {1533, magic_user},
    {1534, magic_user},
    {1537, magic_user},
    {1538, magic_user},
    {1540, magic_user},
    {1541, magic_user},
    {1548, magic_user},
    {1549, magic_user},
    {1552, magic_user},
    {1553, magic_user},
    {1554, magic_user},
    {1556, magic_user},
    {1557, magic_user},
    {1559, magic_user},
    {1560, magic_user},
    {1562, magic_user},
    {1564, magic_user},
    {1565, magic_user},
/*
**  Forest of Rhowyn
*/

    {13901, thrower_mob},

/*
**  Quikland
*/
    {6202, fighter},
    {6204, magic_user},
    {6206, fighter},
    {6207, fighter},
    {6208, fighter},
/*
** Dwarf Village
*/
    {6500, fighter},
    {6501, fighter},
    {6502, wraith},
    {6506, fighter},
    {6507, fighter},
    {6508, fighter},
    {6514, fighter},
    {6516, fighter},
    {6516, snake},

/*
**  Lycanthropia
*/
    {16901, fighter},
    {16902, fighter},
    {16903, fighter},
    {16904, fighter},
    {16905, fighter},
    {16906, fighter},
    {16907, magic_user},
    {16908, fighter},
    {16910, fighter},
    {16911, fighter},

/*
**  Main City
*/

    {3000, magic_user},
    {3060, midgaard_cityguard},
    {3080, fighter},
    {3067, midgaard_cityguard},
    {3061, janitor},
    {3062, fido},
    {3066, fido},
    {3005, receptionist},
    {3020, mage_guild_master},
    {3021, cleric_guild_master},
    {3022, thief_guild_master},
    {3023, warrior_guild_master},

    {3007, sailor},             /* Sailor */
    {3024, guild_guard},
    {3025, guild_guard},
    {3026, guild_guard},
    {3027, guild_guard},
    {3070, repair_guy},
    {3071, repair_guy},
    {3069, midgaard_cityguard}, /* post guard */
    {3068, ninja_master},
    {3073, loremaster},
    {3074, hunter},

/*
**  Lower city
*/
    {3143, mayor},
    {7009, midgaard_cityguard},

/*
**   Hammor's Stuff
*/
    {3900, eric_johnson}, {3901, andy_wilcox}, {3950, zombie_master},
    {3952, breath_weapon_mob},

/* 
**  MORIA 
*/
    {4000, snake},
    {4001, snake},
    {4053, snake},

    {4103, thief},
    {4100, magic_user},
    {4101, regenerator},
    {4102, snake},

/*
**  Pyramid
*/

    {5308, rust_monster},
    {5303, vampire},

/*
**  Arctica
*/
    {6800, fighter},
    {6803, fighter},
    {6801, breath_weapon_mob},
    {6802, breath_weapon_mob},
    {6815, magic_user},
    {6821, snake},
    {6824, breath_weapon_mob},
    {6825, thief},

/* 
** SEWERS 
*/
    {7009, fighter},
    {7006, snake},
    {7008, snake},
    {7042, magic_user},         /* naga       */
    {7040, breath_weapon_mob},  /* Red    */
    {7041, magic_user},         /* sea hag    */
    {7045, ettin},              /* berserk teacher */
    {7200, magic_user},         /* mindflayer */
    {7201, magic_user},         /* senior     */
    {7202, magic_user},         /* junior     */


/* 
** FOREST 
*/

    {6111, magic_user},         /* tree */
    {6113, snake},
    {6114, snake},
    {6112, breath_weapon_mob},  /* green */
    {6910, magic_user},

/*
**  Great Eastern Desert
*/
    {5000, thief},              /* rag. dervish */
    {5002, snake},              /* coral snake */
    {5003, snake},              /* scorpion    */
    {5004, snake},              /* purple worm  */
    {5014, cleric},             /* myconoid */
    {5005, breath_weapon_mob},  /* brass */

/*
**  Drow (edition 1)
*/
    {5010, magic_user},         /* dracolich */
    {5104, cleric},
    {5103, magic_user},         /* drow mage */
    {5107, cleric},             /* drow mat. mot */
    {5108, magic_user},         /* drow mat. mot */
    {5109, cleric},             /* yochlol */

/*
**   Thalos
*/
    {5200, magic_user},         /* beholder    */

/*
**  Zoo
*/
    {9021, snake},              /* Gila Monster */

/*
**  Castle Python
*/
    {11001, fighter},           /* lord python */
    {11002, fighter},
    {11004, fighter},
    {11005, fighter},
    {11006, fighter},
    {11007, fighter},
    {11016, receptionist},
    {11017, nudge_nudge},

/*
**  miscellaneous
*/
    {9061, vampire},            /* vampiress  */

/*
**  White Plume Mountain
*/

    {17004, magic_user},        /* gnyosphinx   */
    {17017, magic_user},        /* ogre magi   */
    {17014, ghoul},             /* ghoul  */
    {17009, geyser},            /* geyser  */
    {17011, vampire},           /* vampire Amelia  */
    {17002, wraith},            /* wight */
    {17005, shadow},            /* shadow */
    {17010, green_slime},       /* green slime */

/*
**  Arachnos
*/

    {20003, snake},             /* wolf (giant) spider  */

    {20005, snake},             /* queen wasp      */

    {20010, snake},             /* bird spider     */
    {20009, magic_user},        /* quasit         */
    {20014, magic_user},        /* Arachnos        */
    {20015, magic_user},        /* Ki Rin          */
    {20011, old_hag},           /* hermit (hey, DM wrote it!) */
    {20002, breath_weapon_mob}, /* Yevaud */
    {20017, breath_weapon_mob}, /* Elder  */
    {20016, breath_weapon_mob}, /* Baby   */
    {20012, fighter},           /* donjonkeeper */

/*
**  SSMinnow
*/

    {21700, fighter},           /* Captain Saltmere */
    {21701, fighter},           /* First Mate */
    {21702, thief},             /* Stowaway */
    {21705, magic_user},        /* Elven Priestss */
    {21706, fighter},           /* Jedadia */
    {21712, fighter},           /* Crew Memeber */
    {21714, snake},             /* Zatagaster */
    {21716, magic_user},

/*
**  Sunsor's elf area
*/

    {22605, timnus},            /* timnus */
    {22604, baby_bear},         /* mother bear */
    {22624, baby_bear},         /* baby bears. */

/*
**   Abbarach
*/
    {27001, magic_user},
    {27002, magic_user},
    {27003, magic_user},
    {27004, magic_user},
    {27005, magic_user},
    {27006, tytan},
    {27007, replicant},
    {27016, abbarach_dragon},
    {27014, magic_user},
    {27017, magic_user},
    {27018, magic_user},
    {27019, magic_user},
    {27025, samah},             /* in skills.c ... shoot me */

    {27401, fighter},
    {27403, fighter},
    {27407, fighter},
    {27408, fighter},
    {27409, fighter},
    {27411, fighter},
    {27415, fighter},
    {27416, fighter},
    {27417, fighter},
    {27418, fighter},
    {27419, fighter},
    {27420, fighter},

    {27404, magic_user},
    {27405, magic_user},
    {27422, magic_user},

    {27413, cleric},
    {27414, cleric},

    {27429, AGGRESSIVE},
    {27430, AGGRESSIVE},

    {7526, winger},
    {7522, magic_user},
    {7531, magic_user},
    {7510, fighter},
    {7514, fighter},
    {7515, fighter},
    {7516, fighter},
    {7527, fighter},
    {7528, fighter},
    {7530, fighter},

    {-1, NULL},
  };

  int i, rnum;
  char buf[MAX_STRING_LENGTH];

  for (i = 0; specials[i].vnum >= 0; i++) {
    rnum = real_mobile(specials[i].vnum);
    if (rnum < 0) {
      SPRINTF(buf, "mobile_assign: Mobile %d not found in database.",
              specials[i].vnum);
      log_msg(buf);
    }
    else {
      mob_index[rnum].func = specials[i].proc;
    }
  }

  boot_the_shops();
  assign_the_shopkeepers();
}

struct object_proc {
  int virtual_obj_num;
  int (*func) ();
};
static struct object_proc obj_procs[] = {
  {15, slot_machine},
  {29, warpstone},
  {30, scraps},
  {23, jive_box},
  {31, portal},
  {3092, board},
  {3097, board},
  {3098, board},
  {3099, board},
  {25102, board},
  {21122, nodrop},
  {21130, youth_potion},
#if EGO
  {40000, bitter_blade},
#endif
  {-1, NULL}
};

/* assign special procedures to objects */
void assign_objects() {
  int i = 0;
  while (obj_procs[i].virtual_obj_num > 0) {
    int real_obj_num = real_object(obj_procs[i].virtual_obj_num);
    if (real_obj_num >= 0 && real_obj_num <= top_of_objt) {
      obj_index[real_obj_num].func = obj_procs[i].func;
    }
    else {
      const char *fmt =
        "***WARNING***: assigning special proc to non-existent object %d";
      char *buf;
      buf = (char *)malloc(strlen(fmt) + 20);
      SPRINTF(buf, fmt, obj_procs[i].virtual_obj_num);
      log_msg(buf);
      free(buf);
    }
    i++;
  }
}


/* assign special procedures to rooms */
void assign_rooms() {
  static struct special_proc_entry specials[] = {

    {99, donation},
    {500, druid_challenge_prep_room},
    {501, druid_challenge_room},
    {550, monk_challenge_prep_room},
    {551, monk_challenge_room},
    {3030, dump},
    {13547, dump},
    {3054, pray_for_items},

    {2188, magic__fountain},
    {2189, magic__fountain},

    {13518, fountain},
    {11014, fountain},
    {5234, fountain},
    {3141, fountain},
    {13406, fountain},
    {22642, fountain},
    {22644, fountain},
    {22646, fountain},
    {22648, fountain},
    {13530, pet_shops},

    {2500, entering_turbo_lift},
    {2639, turbo_lift},

    {2000, bank},
    {13521, bank},
    {-1, NULL},
  };
  int i;
  struct room_data *rp;
  char buf[80];

  for (i = 0; specials[i].vnum >= 0; i++) {
    rp = real_roomp(specials[i].vnum);
    if (rp == NULL) {
      SPRINTF(buf, "assign_rooms: room %d unknown", specials[i].vnum);
      log_msg(buf);
    }
    else
      rp->funct = specials[i].proc;
  }
}
