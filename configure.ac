## Process this file with automake to produce Makefile.in

AC_INIT([dmserver], [0.1.0], [], [], [https://github.com/jonm/SillyMUD])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

AC_CHECK_HEADERS([arpa/inet.h fcntl.h malloc.h netdb.h netinet/in.h stdlib.h string.h strings.h sys/socket.h sys/time.h unistd.h])

AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([bzero gethostbyaddr gethostbyname gethostname getpagesize gettimeofday inet_ntoa isascii memset select socket strchr strdup strrchr strstr])

AC_CHECK_HEADERS([criterion/criterion.h],[],[
  AC_MSG_WARN(unit tests will not be runnable without Criterion library)
  AC_MSG_WARN(See https://github.com/Snaipe/Criterion/)
])
AC_CHECK_LIB(criterion,extmatch,[
  AC_MSG_RESULT(yes)
],[
  AC_MSG_WARN(unit tests will not be runnable without Criterion library)
  AC_MSG_WARN(See https://github.com/Snaipe/Criterion/)
])

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

AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_OUTPUT
