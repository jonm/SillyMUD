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
AC_CHECK_LIB(criterion,extmatch,[],[
  AC_MSG_WARN(unit tests will not be runnable without Criterion library)
  AC_MSG_WARN(See https://github.com/Snaipe/Criterion/)
])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_OUTPUT
