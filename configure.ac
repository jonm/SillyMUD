## Process this file with automake to produce Makefile.in

AC_INIT([sillymud], [0.1.10], [], [], [https://github.com/jonm/SillyMUD])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

AC_CHECK_HEADERS([arpa/inet.h crypt.h errno.h fcntl.h malloc.h netdb.h netinet/in.h stdlib.h signal.h string.h sys/socket.h sys/stat.h sys/time.h time.h unistd.h])

AC_TYPE_SIZE_T
AC_CHECK_SIZEOF([void *])

AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([arc4random arc4random_buf bzero gethostbyaddr gethostbyname gethostname getpagesize gettimeofday hstrerror htonl inet_addr inet_ntoa isascii memcmp memset srand rand select sigaddset sigemptyset sigprocmask socket strchr strdup strrchr strerror strstr time])

AC_CHECK_HEADERS([criterion/criterion.h],[],[
  AC_MSG_WARN(unit tests will not be runnable without Criterion library)
  AC_MSG_WARN(See https://github.com/Snaipe/Criterion/)
])
AC_CHECK_LIB(criterion,extmatch,[
  true
],[
  AC_MSG_WARN(unit tests will not be runnable without Criterion library)
  AC_MSG_WARN(See https://github.com/Snaipe/Criterion/)
])

AC_SEARCH_LIBS([crypt],[crypt])

AH_TEMPLATE([IMPL_SECURITY],
        [Define as 1 to restrict each level 58+ god to one site or set of
         sites])
AC_ARG_ENABLE([impl-security],
  [AS_HELP_STRING([--disable-impl-security],
    [turn off site-locking for gods])],
  [],
  [AC_DEFINE([IMPL_SECURITY])])

AH_TEMPLATE([NEW_RENT],
        [Define as 1 to use newer (more expensive) rent])
AC_ARG_ENABLE([new-rent],
  [AS_HELP_STRING([--disable-new-rent],
     [turn off newer (more expensive) rent])],
  [],
  [AC_DEFINE([NEW_RENT])])

AH_TEMPLATE([LEVEL_LOSS],
  [Define as 1 to enable loss of level at low experience levels])
AC_ARG_ENABLE([level-loss],
  [AS_HELP_STRING([--disable-level-loss],
    [turn off loss of level for low experience])],
  [],
  [AC_DEFINE([LEVEL_LOSS])])

AH_TEMPLATE([NEWEXP],
  [Define as 1 to allow lower exp loss for lower levels])
AC_ARG_ENABLE([new-exp],
  [AS_HELP_STRING([--disable-new-exp],
    [turn off lower exp loss for low level chars])],
  [],
  [AC_DEFINE([NEWEXP])])

AH_TEMPLATE([GROUP_NAMES],
  [Define as 1 to allow for named groups])
AC_ARG_ENABLE([group-names],
  [AS_HELP_STRING([--disable-group-names],
    [turn off group names])],
  [],
  [AC_DEFINE([GROUP_NAMES])])

AH_TEMPLATE([HASH],
  [Define as 1 to use hash tables for rooms (more cpu, less storage)])
AC_ARG_ENABLE([room-hashtables],
  [AS_HELP_STRING([--enable-room-hashtables],
    [use hash tables for rooms])],
  [AC_DEFINE([HASH])],
  [])

AH_TEMPLATE([NOTRACK],
  [Define as 1 to disable tracking (lower cpu)])
AC_ARG_ENABLE([tracking],
  [AS_HELP_STRING([--disable-tracking],
    [disable the track skill])],
  [AC_DEFINE([NOTRACK])],
  [])

AH_TEMPLATE([LIMITED_ITEMS],
  [Define as 1 to limit items above a specific rent cost])
AC_ARG_ENABLE([limited-items],
  [AS_HELP_STRING([--enable-limited-items],
    [limit items above a specific rent cost])],
  [AC_DEFINE([LIMITED_ITEMS])],
  [])

AH_TEMPLATE([PLAYER_AUTH],
  [Define as 1 to require new players to be authorized])
AC_ARG_ENABLE([player-auth],
  [AS_HELP_STRING([--enable-player-auth],
    [require new players to be authorized])],
  [AC_DEFINE([PLAYER_AUTH])],
  [])

AH_TEMPLATE([SITELOCK],
  [Define as 1 to add commands for locking out specific hosts])
AC_ARG_ENABLE([site-lock],
  [AS_HELP_STRING([--enable-site-lock],
    [add commands for locking out specific hosts])],
  [AC_DEFINE([SITELOCK])],
  [])

AH_TEMPLATE([SAVE_WORLD],
  [Define as 1 to save objects and mobs too])
AC_ARG_ENABLE([save-world],
  [AS_HELP_STRING([--enable-save-world],
    [save the world (objects and mobs)])],
  [AC_DEFINE([SAVE_WORLD])],
  [])

AH_TEMPLATE([NODUPLICATES],
  [Define as 1 to modify some commands to make item duplication
   nearly impossible])
AC_ARG_ENABLE([duplicates],
  [AS_HELP_STRING([--disable-duplicates],
    [make item duplication nearly impossible])],
  [AC_DEFINE([NODUPLICATES])],
  [])

AC_DEFINE([DEFAULT_LIBDIR],[LOCAL_STATE_DIR "/sillymud"],
  [Default location to look for game data files])

AH_BOTTOM([
#if (SIZEOF_VOID_P == 8)
#define PTR_SZ_INT long
#elif (SIZEOF_VOID_P == 4)
#define PTR_SZ_INT int
#else
#error "Not sure what integer type is equivalently sized to a (void *)"
#endif

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif
])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  lib/Makefile
  lib/security/Makefile
])
AC_OUTPUT
