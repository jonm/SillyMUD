##
CC=gcc
##
LD=$(CC)
##
##  these are compile time constructs, that affect the running of the game.
CPPFLAGS = -DIMPL_SECURITY -DNEW_RENT -DLEVEL_LOSS -DNEWEXP \
 -DGROUP_NAMES
##  these are architecture dependent flags
TITANFLAGS = -g -43 -vector_c -safe=ptrs -DTITAN
SUNFLAGS = -g
##
CFLAGS = $(SUNFLAGS) $(CPPFLAGS) # -Werror
##
##
##  For lower exp loss at lower levels -DNEWEXP
##
##  For level loss for really low exp -DLEVEL_LOSS
##
##  To make some optimizations, you need to add things to the line above.
##  to use hash tables for rooms  (More cpu, less storage), add
##  -DHASH    
##
##  To get rid of tracking (lower cpu)
##  -DNOTRACK
##
##  To limit items above a specific rent cost
##  -DLIMITED_ITEMS
##
##  To force new players to be authorized
##  -DPLAYER_AUTH
##
##  To add some new debugging stuff (mostly limited to malloc_debug)
##  -DDEBUG
##  To add some commands for locking out specific hosts
##  -DSITELOCK
##
## To lock out oak.grove.iup.edu from boot time.
## -DLOCKGROVE
##
##  To save the world (objects and mobs) -DSAVE_WORLD
##
##  To modify some commands to make item duplication near impossible:
##  -DNODUPLICATES
##
##  To have each 58+ god restricted to one site, or set of sites
##  -DIMPL_SECURITY
##
##  To use BSD memory allocation/deallocation routines instead of the
##  native memory routines:
##  -DKLUDGE_MEM
##
##  If your system doesn't have built in functions of strdup() and
##  strstr(), then:
##  -DKLUDGE_STRING
##

HEADERFILES = structs.h utils.h comm.h interpreter.h db.h
##
OBJS = comm.o act.comm.o act.info.o act.move.o act.obj1.o act.obj2.o \
	act.off.o act.other.o act.social.o act.wizard.o handler.o \
	db.o interpreter.o utility.o spec_assign.o shop.o limits.o mobact.o \
	fight.o modify.o weather.o spells1.o spells2.o spell_parser.o \
	reception.o constants.o spec_procs.o signals.o board.o magic.o \
	magic2.o skills.o Opinion.o Trap.o magicutils.o multiclass.o hash.o \
	Sound.o Heap.o spec_procs2.o magic3.o security.o spec_procs3.o \
        create.o bsd.o parser.o intrinsics.o

SRCS = comm.c act.comm.c act.info.c act.move.c act.obj1.c act.obj2.c \
	act.off.c act.other.c act.social.c act.wizard.c handler.c \
	db.c interpreter.c utility.c spec_assign.c shop.c limits.c mobact.c \
	fight.c modify.c weather.c spells1.c spells2.c spell_parser.c \
	reception.c constants.c spec_procs.c signals.c board.c magic.c \
	magic2.c skills.c Opinion.c Trap.c magicutils.c multiclass.c hash.c \
	Sound.c Heap.c spec_procs2.c magic3.c security.c spec_procs3.c \
        create.c bsd.c parser.c intrinsics.c

TEST_SRCS = test.act.wizard.c

TEST_OBJS = test.act.wizard.o

all : dmserver

tests : ${OBJS} ${TEST_OBJS}
	$(LD) -o $@ ${OBJS} ${TEST_OBJS} -lcriterion

test : tests
	./tests

dmserver : ${OBJS} main.o
## if you want to add debugging stuff, uncomment the following, and comment
##  out the line after that
##	$(LD) -o $@ -g ${OBJS} /local/lib/gnu/gcc-gnulib /usr/lib/debug/malloc.o
	$(LD) -o $@ -g ${OBJS} main.o
##	$(LD) -o $@  ${OBJS}
##
depend :
	makedepend -I/usr/local/include ${SRCS} ${TEST_SRCS} main.c

clean :
	rm -f ${OBJS} dmserver main.o test



# DO NOT DELETE THIS LINE -- make depend depends on it.

comm.o: /usr/include/errno.h /usr/include/sys/errno.h
comm.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
comm.o: /usr/include/sys/_posix_availability.h
comm.o: /usr/include/sys/_types/_errno_t.h /usr/include/stdio.h
comm.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
comm.o: /usr/include/_types.h /usr/include/sys/_types.h
comm.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
comm.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/_types/_size_t.h
comm.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_off_t.h
comm.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
comm.o: /usr/include/secure/_common.h /usr/include/stdlib.h
comm.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
comm.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
comm.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
comm.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
comm.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
comm.o: /usr/include/sys/_types/_sigaltstack.h
comm.o: /usr/include/sys/_types/_ucontext.h
comm.o: /usr/include/sys/_types/_pthread_attr_t.h
comm.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h
comm.o: /usr/include/sys/resource.h /usr/include/stdint.h
comm.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
comm.o: /usr/include/sys/_types/_int32_t.h /usr/include/sys/_types/_int64_t.h
comm.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
comm.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
comm.o: /usr/include/sys/_types/_intptr_t.h
comm.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
comm.o: /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h
comm.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
comm.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
comm.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
comm.o: /usr/include/sys/_types/_ct_rune_t.h
comm.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
comm.o: /usr/include/machine/types.h /usr/include/i386/types.h
comm.o: /usr/include/sys/_types/___offsetof.h
comm.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
comm.o: /usr/include/ctype.h /usr/include/runetype.h
comm.o: /usr/include/sys/_types/_wint_t.h /usr/include/sys/types.h
comm.o: /usr/include/sys/_types/_blkcnt_t.h
comm.o: /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h
comm.o: /usr/include/sys/_types/_in_addr_t.h
comm.o: /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h
comm.o: /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h
comm.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_clock_t.h
comm.o: /usr/include/sys/_types/_time_t.h
comm.o: /usr/include/sys/_types/_useconds_t.h
comm.o: /usr/include/sys/_types/_suseconds_t.h
comm.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_fd_def.h
comm.o: /usr/include/sys/_types/_fd_setsize.h
comm.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
comm.o: /usr/include/sys/_types/_fd_zero.h
comm.o: /usr/include/sys/_types/_fd_isset.h
comm.o: /usr/include/sys/_types/_fd_copy.h
comm.o: /usr/include/sys/_types/_pthread_cond_t.h
comm.o: /usr/include/sys/_types/_pthread_condattr_t.h
comm.o: /usr/include/sys/_types/_pthread_mutex_t.h
comm.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
comm.o: /usr/include/sys/_types/_pthread_once_t.h
comm.o: /usr/include/sys/_types/_pthread_rwlock_t.h
comm.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
comm.o: /usr/include/sys/_types/_pthread_t.h
comm.o: /usr/include/sys/_types/_pthread_key_t.h
comm.o: /usr/include/sys/_types/_fsblkcnt_t.h
comm.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/sys/socket.h
comm.o: /usr/include/machine/_param.h /usr/include/i386/_param.h
comm.o: /usr/include/sys/_types/_sa_family_t.h
comm.o: /usr/include/sys/_types/_socklen_t.h
comm.o: /usr/include/sys/_types/_iovec_t.h /usr/include/netinet/in.h
comm.o: /usr/include/netinet6/in6.h /usr/include/arpa/inet.h
comm.o: /usr/include/netdb.h /usr/include/string.h /usr/include/strings.h
comm.o: /usr/include/secure/_string.h /usr/include/sys/time.h
comm.o: /usr/include/sys/_types/_timespec.h /usr/include/time.h
comm.o: /usr/include/_structs.h /usr/include/sys/_structs.h
comm.o: /usr/include/sys/_select.h /usr/include/fcntl.h
comm.o: /usr/include/sys/fcntl.h /usr/include/sys/_types/_o_sync.h
comm.o: /usr/include/sys/_types/_o_dsync.h
comm.o: /usr/include/sys/_types/_seek_set.h /usr/include/sys/_types/_s_ifmt.h
comm.o: /usr/include/sys/_types/_filesec_t.h /usr/include/signal.h
comm.o: /usr/include/unistd.h /usr/include/sys/unistd.h
comm.o: /usr/include/sys/_types/_posix_vdisable.h /usr/include/sys/select.h
comm.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h protos.h
comm.o: structs.h /usr/include/assert.h area.h comm.h db.h handler.h hash.h
comm.o: heap.h interpreter.h limits.h poly.h race.h script.h spells.h trap.h
comm.o: utils.h vt100c.h wizlist.h parser.h
act.comm.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
act.comm.o: /usr/include/sys/_symbol_aliasing.h
act.comm.o: /usr/include/sys/_posix_availability.h
act.comm.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
act.comm.o: /usr/include/_types.h /usr/include/sys/_types.h
act.comm.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
act.comm.o: /usr/include/sys/_types/_va_list.h
act.comm.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
act.comm.o: /usr/include/sys/_types/_off_t.h
act.comm.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
act.comm.o: /usr/include/secure/_common.h /usr/include/string.h
act.comm.o: /usr/include/sys/_types/_rsize_t.h
act.comm.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
act.comm.o: /usr/include/secure/_string.h protos.h structs.h
act.comm.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
act.comm.o: /usr/include/machine/types.h /usr/include/i386/types.h
act.comm.o: /usr/include/sys/_types/_int8_t.h
act.comm.o: /usr/include/sys/_types/_int16_t.h
act.comm.o: /usr/include/sys/_types/_int32_t.h
act.comm.o: /usr/include/sys/_types/_int64_t.h
act.comm.o: /usr/include/sys/_types/_intptr_t.h
act.comm.o: /usr/include/sys/_types/_uintptr_t.h
act.comm.o: /usr/include/sys/_types/___offsetof.h
act.comm.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
act.comm.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
act.comm.o: /usr/include/libkern/i386/_OSByteOrder.h
act.comm.o: /usr/include/sys/_types/_dev_t.h
act.comm.o: /usr/include/sys/_types/_blkcnt_t.h
act.comm.o: /usr/include/sys/_types/_blksize_t.h
act.comm.o: /usr/include/sys/_types/_gid_t.h
act.comm.o: /usr/include/sys/_types/_in_addr_t.h
act.comm.o: /usr/include/sys/_types/_in_port_t.h
act.comm.o: /usr/include/sys/_types/_ino_t.h
act.comm.o: /usr/include/sys/_types/_ino64_t.h
act.comm.o: /usr/include/sys/_types/_key_t.h
act.comm.o: /usr/include/sys/_types/_mode_t.h
act.comm.o: /usr/include/sys/_types/_nlink_t.h
act.comm.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/_types/_pid_t.h
act.comm.o: /usr/include/sys/_types/_uid_t.h
act.comm.o: /usr/include/sys/_types/_clock_t.h
act.comm.o: /usr/include/sys/_types/_time_t.h
act.comm.o: /usr/include/sys/_types/_useconds_t.h
act.comm.o: /usr/include/sys/_types/_suseconds_t.h
act.comm.o: /usr/include/sys/_types/_fd_def.h
act.comm.o: /usr/include/sys/_types/_fd_setsize.h
act.comm.o: /usr/include/sys/_types/_fd_set.h
act.comm.o: /usr/include/sys/_types/_fd_clr.h
act.comm.o: /usr/include/sys/_types/_fd_zero.h
act.comm.o: /usr/include/sys/_types/_fd_isset.h
act.comm.o: /usr/include/sys/_types/_fd_copy.h
act.comm.o: /usr/include/sys/_types/_pthread_attr_t.h
act.comm.o: /usr/include/sys/_types/_pthread_cond_t.h
act.comm.o: /usr/include/sys/_types/_pthread_condattr_t.h
act.comm.o: /usr/include/sys/_types/_pthread_mutex_t.h
act.comm.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
act.comm.o: /usr/include/sys/_types/_pthread_once_t.h
act.comm.o: /usr/include/sys/_types/_pthread_rwlock_t.h
act.comm.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
act.comm.o: /usr/include/sys/_types/_pthread_t.h
act.comm.o: /usr/include/sys/_types/_pthread_key_t.h
act.comm.o: /usr/include/sys/_types/_fsblkcnt_t.h
act.comm.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
act.comm.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h limits.h
act.comm.o: poly.h race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h
act.comm.o: parser.h
act.info.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
act.info.o: /usr/include/sys/_symbol_aliasing.h
act.info.o: /usr/include/sys/_posix_availability.h
act.info.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
act.info.o: /usr/include/_types.h /usr/include/sys/_types.h
act.info.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
act.info.o: /usr/include/sys/_types/_va_list.h
act.info.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
act.info.o: /usr/include/sys/_types/_off_t.h
act.info.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
act.info.o: /usr/include/secure/_common.h /usr/include/stdlib.h
act.info.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
act.info.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
act.info.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
act.info.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
act.info.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
act.info.o: /usr/include/sys/_types/_sigaltstack.h
act.info.o: /usr/include/sys/_types/_ucontext.h
act.info.o: /usr/include/sys/_types/_pthread_attr_t.h
act.info.o: /usr/include/sys/_types/_sigset_t.h
act.info.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
act.info.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
act.info.o: /usr/include/sys/_types/_int16_t.h
act.info.o: /usr/include/sys/_types/_int32_t.h
act.info.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
act.info.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
act.info.o: /usr/include/_types/_uint64_t.h
act.info.o: /usr/include/sys/_types/_intptr_t.h
act.info.o: /usr/include/sys/_types/_uintptr_t.h
act.info.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
act.info.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
act.info.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
act.info.o: /usr/include/libkern/_OSByteOrder.h
act.info.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
act.info.o: /usr/include/sys/_types/_ct_rune_t.h
act.info.o: /usr/include/sys/_types/_rune_t.h
act.info.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
act.info.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
act.info.o: /usr/include/sys/_types/_dev_t.h
act.info.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
act.info.o: /usr/include/sys/_types/_rsize_t.h
act.info.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
act.info.o: /usr/include/secure/_string.h /usr/include/ctype.h
act.info.o: /usr/include/runetype.h /usr/include/sys/_types/_wint_t.h
act.info.o: /usr/include/time.h /usr/include/_structs.h
act.info.o: /usr/include/sys/_structs.h /usr/include/sys/_types/_timespec.h
act.info.o: /usr/include/sys/_types/_clock_t.h
act.info.o: /usr/include/sys/_types/_time_t.h protos.h structs.h
act.info.o: /usr/include/sys/types.h /usr/include/sys/_types/_blkcnt_t.h
act.info.o: /usr/include/sys/_types/_blksize_t.h
act.info.o: /usr/include/sys/_types/_gid_t.h
act.info.o: /usr/include/sys/_types/_in_addr_t.h
act.info.o: /usr/include/sys/_types/_in_port_t.h
act.info.o: /usr/include/sys/_types/_ino_t.h
act.info.o: /usr/include/sys/_types/_ino64_t.h
act.info.o: /usr/include/sys/_types/_key_t.h
act.info.o: /usr/include/sys/_types/_nlink_t.h
act.info.o: /usr/include/sys/_types/_useconds_t.h
act.info.o: /usr/include/sys/_types/_suseconds_t.h
act.info.o: /usr/include/sys/_types/_fd_def.h
act.info.o: /usr/include/sys/_types/_fd_setsize.h
act.info.o: /usr/include/sys/_types/_fd_set.h
act.info.o: /usr/include/sys/_types/_fd_clr.h
act.info.o: /usr/include/sys/_types/_fd_zero.h
act.info.o: /usr/include/sys/_types/_fd_isset.h
act.info.o: /usr/include/sys/_types/_fd_copy.h
act.info.o: /usr/include/sys/_types/_pthread_cond_t.h
act.info.o: /usr/include/sys/_types/_pthread_condattr_t.h
act.info.o: /usr/include/sys/_types/_pthread_mutex_t.h
act.info.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
act.info.o: /usr/include/sys/_types/_pthread_once_t.h
act.info.o: /usr/include/sys/_types/_pthread_rwlock_t.h
act.info.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
act.info.o: /usr/include/sys/_types/_pthread_t.h
act.info.o: /usr/include/sys/_types/_pthread_key_t.h
act.info.o: /usr/include/sys/_types/_fsblkcnt_t.h
act.info.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
act.info.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h limits.h
act.info.o: poly.h race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h
act.info.o: parser.h
act.move.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
act.move.o: /usr/include/sys/_symbol_aliasing.h
act.move.o: /usr/include/sys/_posix_availability.h
act.move.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
act.move.o: /usr/include/_types.h /usr/include/sys/_types.h
act.move.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
act.move.o: /usr/include/sys/_types/_va_list.h
act.move.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
act.move.o: /usr/include/sys/_types/_off_t.h
act.move.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
act.move.o: /usr/include/secure/_common.h /usr/include/string.h
act.move.o: /usr/include/sys/_types/_rsize_t.h
act.move.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
act.move.o: /usr/include/secure/_string.h protos.h structs.h
act.move.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
act.move.o: /usr/include/machine/types.h /usr/include/i386/types.h
act.move.o: /usr/include/sys/_types/_int8_t.h
act.move.o: /usr/include/sys/_types/_int16_t.h
act.move.o: /usr/include/sys/_types/_int32_t.h
act.move.o: /usr/include/sys/_types/_int64_t.h
act.move.o: /usr/include/sys/_types/_intptr_t.h
act.move.o: /usr/include/sys/_types/_uintptr_t.h
act.move.o: /usr/include/sys/_types/___offsetof.h
act.move.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
act.move.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
act.move.o: /usr/include/libkern/i386/_OSByteOrder.h
act.move.o: /usr/include/sys/_types/_dev_t.h
act.move.o: /usr/include/sys/_types/_blkcnt_t.h
act.move.o: /usr/include/sys/_types/_blksize_t.h
act.move.o: /usr/include/sys/_types/_gid_t.h
act.move.o: /usr/include/sys/_types/_in_addr_t.h
act.move.o: /usr/include/sys/_types/_in_port_t.h
act.move.o: /usr/include/sys/_types/_ino_t.h
act.move.o: /usr/include/sys/_types/_ino64_t.h
act.move.o: /usr/include/sys/_types/_key_t.h
act.move.o: /usr/include/sys/_types/_mode_t.h
act.move.o: /usr/include/sys/_types/_nlink_t.h
act.move.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/_types/_pid_t.h
act.move.o: /usr/include/sys/_types/_uid_t.h
act.move.o: /usr/include/sys/_types/_clock_t.h
act.move.o: /usr/include/sys/_types/_time_t.h
act.move.o: /usr/include/sys/_types/_useconds_t.h
act.move.o: /usr/include/sys/_types/_suseconds_t.h
act.move.o: /usr/include/sys/_types/_fd_def.h
act.move.o: /usr/include/sys/_types/_fd_setsize.h
act.move.o: /usr/include/sys/_types/_fd_set.h
act.move.o: /usr/include/sys/_types/_fd_clr.h
act.move.o: /usr/include/sys/_types/_fd_zero.h
act.move.o: /usr/include/sys/_types/_fd_isset.h
act.move.o: /usr/include/sys/_types/_fd_copy.h
act.move.o: /usr/include/sys/_types/_pthread_attr_t.h
act.move.o: /usr/include/sys/_types/_pthread_cond_t.h
act.move.o: /usr/include/sys/_types/_pthread_condattr_t.h
act.move.o: /usr/include/sys/_types/_pthread_mutex_t.h
act.move.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
act.move.o: /usr/include/sys/_types/_pthread_once_t.h
act.move.o: /usr/include/sys/_types/_pthread_rwlock_t.h
act.move.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
act.move.o: /usr/include/sys/_types/_pthread_t.h
act.move.o: /usr/include/sys/_types/_pthread_key_t.h
act.move.o: /usr/include/sys/_types/_fsblkcnt_t.h
act.move.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
act.move.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h limits.h
act.move.o: poly.h race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h
act.move.o: parser.h
act.obj1.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
act.obj1.o: /usr/include/sys/_symbol_aliasing.h
act.obj1.o: /usr/include/sys/_posix_availability.h
act.obj1.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
act.obj1.o: /usr/include/_types.h /usr/include/sys/_types.h
act.obj1.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
act.obj1.o: /usr/include/sys/_types/_va_list.h
act.obj1.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
act.obj1.o: /usr/include/sys/_types/_off_t.h
act.obj1.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
act.obj1.o: /usr/include/secure/_common.h /usr/include/stdlib.h
act.obj1.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
act.obj1.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
act.obj1.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
act.obj1.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
act.obj1.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
act.obj1.o: /usr/include/sys/_types/_sigaltstack.h
act.obj1.o: /usr/include/sys/_types/_ucontext.h
act.obj1.o: /usr/include/sys/_types/_pthread_attr_t.h
act.obj1.o: /usr/include/sys/_types/_sigset_t.h
act.obj1.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
act.obj1.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
act.obj1.o: /usr/include/sys/_types/_int16_t.h
act.obj1.o: /usr/include/sys/_types/_int32_t.h
act.obj1.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
act.obj1.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
act.obj1.o: /usr/include/_types/_uint64_t.h
act.obj1.o: /usr/include/sys/_types/_intptr_t.h
act.obj1.o: /usr/include/sys/_types/_uintptr_t.h
act.obj1.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
act.obj1.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
act.obj1.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
act.obj1.o: /usr/include/libkern/_OSByteOrder.h
act.obj1.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
act.obj1.o: /usr/include/sys/_types/_ct_rune_t.h
act.obj1.o: /usr/include/sys/_types/_rune_t.h
act.obj1.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
act.obj1.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
act.obj1.o: /usr/include/sys/_types/_dev_t.h
act.obj1.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
act.obj1.o: /usr/include/sys/_types/_rsize_t.h
act.obj1.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
act.obj1.o: /usr/include/secure/_string.h protos.h structs.h
act.obj1.o: /usr/include/sys/types.h /usr/include/sys/_types/_blkcnt_t.h
act.obj1.o: /usr/include/sys/_types/_blksize_t.h
act.obj1.o: /usr/include/sys/_types/_gid_t.h
act.obj1.o: /usr/include/sys/_types/_in_addr_t.h
act.obj1.o: /usr/include/sys/_types/_in_port_t.h
act.obj1.o: /usr/include/sys/_types/_ino_t.h
act.obj1.o: /usr/include/sys/_types/_ino64_t.h
act.obj1.o: /usr/include/sys/_types/_key_t.h
act.obj1.o: /usr/include/sys/_types/_nlink_t.h
act.obj1.o: /usr/include/sys/_types/_clock_t.h
act.obj1.o: /usr/include/sys/_types/_time_t.h
act.obj1.o: /usr/include/sys/_types/_useconds_t.h
act.obj1.o: /usr/include/sys/_types/_suseconds_t.h
act.obj1.o: /usr/include/sys/_types/_fd_def.h
act.obj1.o: /usr/include/sys/_types/_fd_setsize.h
act.obj1.o: /usr/include/sys/_types/_fd_set.h
act.obj1.o: /usr/include/sys/_types/_fd_clr.h
act.obj1.o: /usr/include/sys/_types/_fd_zero.h
act.obj1.o: /usr/include/sys/_types/_fd_isset.h
act.obj1.o: /usr/include/sys/_types/_fd_copy.h
act.obj1.o: /usr/include/sys/_types/_pthread_cond_t.h
act.obj1.o: /usr/include/sys/_types/_pthread_condattr_t.h
act.obj1.o: /usr/include/sys/_types/_pthread_mutex_t.h
act.obj1.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
act.obj1.o: /usr/include/sys/_types/_pthread_once_t.h
act.obj1.o: /usr/include/sys/_types/_pthread_rwlock_t.h
act.obj1.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
act.obj1.o: /usr/include/sys/_types/_pthread_t.h
act.obj1.o: /usr/include/sys/_types/_pthread_key_t.h
act.obj1.o: /usr/include/sys/_types/_fsblkcnt_t.h
act.obj1.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
act.obj1.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h limits.h
act.obj1.o: poly.h race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h
act.obj1.o: parser.h
act.obj2.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
act.obj2.o: /usr/include/sys/_symbol_aliasing.h
act.obj2.o: /usr/include/sys/_posix_availability.h
act.obj2.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
act.obj2.o: /usr/include/_types.h /usr/include/sys/_types.h
act.obj2.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
act.obj2.o: /usr/include/sys/_types/_va_list.h
act.obj2.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
act.obj2.o: /usr/include/sys/_types/_off_t.h
act.obj2.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
act.obj2.o: /usr/include/secure/_common.h /usr/include/stdlib.h
act.obj2.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
act.obj2.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
act.obj2.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
act.obj2.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
act.obj2.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
act.obj2.o: /usr/include/sys/_types/_sigaltstack.h
act.obj2.o: /usr/include/sys/_types/_ucontext.h
act.obj2.o: /usr/include/sys/_types/_pthread_attr_t.h
act.obj2.o: /usr/include/sys/_types/_sigset_t.h
act.obj2.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
act.obj2.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
act.obj2.o: /usr/include/sys/_types/_int16_t.h
act.obj2.o: /usr/include/sys/_types/_int32_t.h
act.obj2.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
act.obj2.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
act.obj2.o: /usr/include/_types/_uint64_t.h
act.obj2.o: /usr/include/sys/_types/_intptr_t.h
act.obj2.o: /usr/include/sys/_types/_uintptr_t.h
act.obj2.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
act.obj2.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
act.obj2.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
act.obj2.o: /usr/include/libkern/_OSByteOrder.h
act.obj2.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
act.obj2.o: /usr/include/sys/_types/_ct_rune_t.h
act.obj2.o: /usr/include/sys/_types/_rune_t.h
act.obj2.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
act.obj2.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
act.obj2.o: /usr/include/sys/_types/_dev_t.h
act.obj2.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
act.obj2.o: /usr/include/sys/_types/_rsize_t.h
act.obj2.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
act.obj2.o: /usr/include/secure/_string.h /usr/include/assert.h
act.obj2.o: /usr/include/ctype.h /usr/include/runetype.h
act.obj2.o: /usr/include/sys/_types/_wint_t.h protos.h structs.h
act.obj2.o: /usr/include/sys/types.h /usr/include/sys/_types/_blkcnt_t.h
act.obj2.o: /usr/include/sys/_types/_blksize_t.h
act.obj2.o: /usr/include/sys/_types/_gid_t.h
act.obj2.o: /usr/include/sys/_types/_in_addr_t.h
act.obj2.o: /usr/include/sys/_types/_in_port_t.h
act.obj2.o: /usr/include/sys/_types/_ino_t.h
act.obj2.o: /usr/include/sys/_types/_ino64_t.h
act.obj2.o: /usr/include/sys/_types/_key_t.h
act.obj2.o: /usr/include/sys/_types/_nlink_t.h
act.obj2.o: /usr/include/sys/_types/_clock_t.h
act.obj2.o: /usr/include/sys/_types/_time_t.h
act.obj2.o: /usr/include/sys/_types/_useconds_t.h
act.obj2.o: /usr/include/sys/_types/_suseconds_t.h
act.obj2.o: /usr/include/sys/_types/_fd_def.h
act.obj2.o: /usr/include/sys/_types/_fd_setsize.h
act.obj2.o: /usr/include/sys/_types/_fd_set.h
act.obj2.o: /usr/include/sys/_types/_fd_clr.h
act.obj2.o: /usr/include/sys/_types/_fd_zero.h
act.obj2.o: /usr/include/sys/_types/_fd_isset.h
act.obj2.o: /usr/include/sys/_types/_fd_copy.h
act.obj2.o: /usr/include/sys/_types/_pthread_cond_t.h
act.obj2.o: /usr/include/sys/_types/_pthread_condattr_t.h
act.obj2.o: /usr/include/sys/_types/_pthread_mutex_t.h
act.obj2.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
act.obj2.o: /usr/include/sys/_types/_pthread_once_t.h
act.obj2.o: /usr/include/sys/_types/_pthread_rwlock_t.h
act.obj2.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
act.obj2.o: /usr/include/sys/_types/_pthread_t.h
act.obj2.o: /usr/include/sys/_types/_pthread_key_t.h
act.obj2.o: /usr/include/sys/_types/_fsblkcnt_t.h
act.obj2.o: /usr/include/sys/_types/_fsfilcnt_t.h area.h comm.h db.h
act.obj2.o: handler.h hash.h heap.h interpreter.h limits.h poly.h race.h
act.obj2.o: script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
act.off.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
act.off.o: /usr/include/sys/_symbol_aliasing.h
act.off.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
act.off.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
act.off.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
act.off.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
act.off.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
act.off.o: /usr/include/sys/_types/_off_t.h
act.off.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
act.off.o: /usr/include/secure/_common.h /usr/include/stdlib.h
act.off.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
act.off.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
act.off.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
act.off.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
act.off.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
act.off.o: /usr/include/sys/_types/_sigaltstack.h
act.off.o: /usr/include/sys/_types/_ucontext.h
act.off.o: /usr/include/sys/_types/_pthread_attr_t.h
act.off.o: /usr/include/sys/_types/_sigset_t.h
act.off.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
act.off.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
act.off.o: /usr/include/sys/_types/_int16_t.h
act.off.o: /usr/include/sys/_types/_int32_t.h
act.off.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
act.off.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
act.off.o: /usr/include/_types/_uint64_t.h
act.off.o: /usr/include/sys/_types/_intptr_t.h
act.off.o: /usr/include/sys/_types/_uintptr_t.h
act.off.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
act.off.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
act.off.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
act.off.o: /usr/include/libkern/_OSByteOrder.h
act.off.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
act.off.o: /usr/include/sys/_types/_ct_rune_t.h
act.off.o: /usr/include/sys/_types/_rune_t.h
act.off.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
act.off.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
act.off.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
act.off.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
act.off.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
act.off.o: /usr/include/secure/_string.h protos.h structs.h
act.off.o: /usr/include/sys/types.h /usr/include/sys/_types/_blkcnt_t.h
act.off.o: /usr/include/sys/_types/_blksize_t.h
act.off.o: /usr/include/sys/_types/_gid_t.h
act.off.o: /usr/include/sys/_types/_in_addr_t.h
act.off.o: /usr/include/sys/_types/_in_port_t.h
act.off.o: /usr/include/sys/_types/_ino_t.h
act.off.o: /usr/include/sys/_types/_ino64_t.h
act.off.o: /usr/include/sys/_types/_key_t.h
act.off.o: /usr/include/sys/_types/_nlink_t.h
act.off.o: /usr/include/sys/_types/_clock_t.h
act.off.o: /usr/include/sys/_types/_time_t.h
act.off.o: /usr/include/sys/_types/_useconds_t.h
act.off.o: /usr/include/sys/_types/_suseconds_t.h
act.off.o: /usr/include/sys/_types/_fd_def.h
act.off.o: /usr/include/sys/_types/_fd_setsize.h
act.off.o: /usr/include/sys/_types/_fd_set.h
act.off.o: /usr/include/sys/_types/_fd_clr.h
act.off.o: /usr/include/sys/_types/_fd_zero.h
act.off.o: /usr/include/sys/_types/_fd_isset.h
act.off.o: /usr/include/sys/_types/_fd_copy.h
act.off.o: /usr/include/sys/_types/_pthread_cond_t.h
act.off.o: /usr/include/sys/_types/_pthread_condattr_t.h
act.off.o: /usr/include/sys/_types/_pthread_mutex_t.h
act.off.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
act.off.o: /usr/include/sys/_types/_pthread_once_t.h
act.off.o: /usr/include/sys/_types/_pthread_rwlock_t.h
act.off.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
act.off.o: /usr/include/sys/_types/_pthread_t.h
act.off.o: /usr/include/sys/_types/_pthread_key_t.h
act.off.o: /usr/include/sys/_types/_fsblkcnt_t.h
act.off.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
act.off.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
act.off.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h
act.off.o: parser.h
act.other.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
act.other.o: /usr/include/sys/_symbol_aliasing.h
act.other.o: /usr/include/sys/_posix_availability.h
act.other.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
act.other.o: /usr/include/_types.h /usr/include/sys/_types.h
act.other.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
act.other.o: /usr/include/sys/_types/_va_list.h
act.other.o: /usr/include/sys/_types/_size_t.h
act.other.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_off_t.h
act.other.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
act.other.o: /usr/include/secure/_common.h /usr/include/stdlib.h
act.other.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
act.other.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
act.other.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
act.other.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
act.other.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
act.other.o: /usr/include/sys/_types/_sigaltstack.h
act.other.o: /usr/include/sys/_types/_ucontext.h
act.other.o: /usr/include/sys/_types/_pthread_attr_t.h
act.other.o: /usr/include/sys/_types/_sigset_t.h
act.other.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
act.other.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
act.other.o: /usr/include/sys/_types/_int16_t.h
act.other.o: /usr/include/sys/_types/_int32_t.h
act.other.o: /usr/include/sys/_types/_int64_t.h
act.other.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
act.other.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
act.other.o: /usr/include/sys/_types/_intptr_t.h
act.other.o: /usr/include/sys/_types/_uintptr_t.h
act.other.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
act.other.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
act.other.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
act.other.o: /usr/include/libkern/_OSByteOrder.h
act.other.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
act.other.o: /usr/include/sys/_types/_ct_rune_t.h
act.other.o: /usr/include/sys/_types/_rune_t.h
act.other.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
act.other.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
act.other.o: /usr/include/sys/_types/_dev_t.h
act.other.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
act.other.o: /usr/include/sys/_types/_rsize_t.h
act.other.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
act.other.o: /usr/include/secure/_string.h /usr/include/ctype.h
act.other.o: /usr/include/runetype.h /usr/include/sys/_types/_wint_t.h
act.other.o: protos.h structs.h /usr/include/sys/types.h
act.other.o: /usr/include/sys/_types/_blkcnt_t.h
act.other.o: /usr/include/sys/_types/_blksize_t.h
act.other.o: /usr/include/sys/_types/_gid_t.h
act.other.o: /usr/include/sys/_types/_in_addr_t.h
act.other.o: /usr/include/sys/_types/_in_port_t.h
act.other.o: /usr/include/sys/_types/_ino_t.h
act.other.o: /usr/include/sys/_types/_ino64_t.h
act.other.o: /usr/include/sys/_types/_key_t.h
act.other.o: /usr/include/sys/_types/_nlink_t.h
act.other.o: /usr/include/sys/_types/_clock_t.h
act.other.o: /usr/include/sys/_types/_time_t.h
act.other.o: /usr/include/sys/_types/_useconds_t.h
act.other.o: /usr/include/sys/_types/_suseconds_t.h
act.other.o: /usr/include/sys/_types/_fd_def.h
act.other.o: /usr/include/sys/_types/_fd_setsize.h
act.other.o: /usr/include/sys/_types/_fd_set.h
act.other.o: /usr/include/sys/_types/_fd_clr.h
act.other.o: /usr/include/sys/_types/_fd_zero.h
act.other.o: /usr/include/sys/_types/_fd_isset.h
act.other.o: /usr/include/sys/_types/_fd_copy.h
act.other.o: /usr/include/sys/_types/_pthread_cond_t.h
act.other.o: /usr/include/sys/_types/_pthread_condattr_t.h
act.other.o: /usr/include/sys/_types/_pthread_mutex_t.h
act.other.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
act.other.o: /usr/include/sys/_types/_pthread_once_t.h
act.other.o: /usr/include/sys/_types/_pthread_rwlock_t.h
act.other.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
act.other.o: /usr/include/sys/_types/_pthread_t.h
act.other.o: /usr/include/sys/_types/_pthread_key_t.h
act.other.o: /usr/include/sys/_types/_fsblkcnt_t.h
act.other.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
act.other.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h
act.other.o: limits.h poly.h race.h script.h spells.h trap.h utils.h vt100c.h
act.other.o: wizlist.h parser.h
act.social.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
act.social.o: /usr/include/sys/_symbol_aliasing.h
act.social.o: /usr/include/sys/_posix_availability.h
act.social.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
act.social.o: /usr/include/_types.h /usr/include/sys/_types.h
act.social.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
act.social.o: /usr/include/sys/_types/_va_list.h
act.social.o: /usr/include/sys/_types/_size_t.h
act.social.o: /usr/include/sys/_types/_null.h
act.social.o: /usr/include/sys/_types/_off_t.h
act.social.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
act.social.o: /usr/include/secure/_common.h /usr/include/stdlib.h
act.social.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
act.social.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
act.social.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
act.social.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
act.social.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
act.social.o: /usr/include/sys/_types/_sigaltstack.h
act.social.o: /usr/include/sys/_types/_ucontext.h
act.social.o: /usr/include/sys/_types/_pthread_attr_t.h
act.social.o: /usr/include/sys/_types/_sigset_t.h
act.social.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
act.social.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
act.social.o: /usr/include/sys/_types/_int16_t.h
act.social.o: /usr/include/sys/_types/_int32_t.h
act.social.o: /usr/include/sys/_types/_int64_t.h
act.social.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
act.social.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
act.social.o: /usr/include/sys/_types/_intptr_t.h
act.social.o: /usr/include/sys/_types/_uintptr_t.h
act.social.o: /usr/include/_types/_intmax_t.h
act.social.o: /usr/include/_types/_uintmax_t.h
act.social.o: /usr/include/sys/_types/_timeval.h
act.social.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
act.social.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
act.social.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
act.social.o: /usr/include/sys/_types/_ct_rune_t.h
act.social.o: /usr/include/sys/_types/_rune_t.h
act.social.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
act.social.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
act.social.o: /usr/include/sys/_types/_dev_t.h
act.social.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
act.social.o: /usr/include/sys/_types/_rsize_t.h
act.social.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
act.social.o: /usr/include/secure/_string.h protos.h structs.h
act.social.o: /usr/include/sys/types.h /usr/include/sys/_types/_blkcnt_t.h
act.social.o: /usr/include/sys/_types/_blksize_t.h
act.social.o: /usr/include/sys/_types/_gid_t.h
act.social.o: /usr/include/sys/_types/_in_addr_t.h
act.social.o: /usr/include/sys/_types/_in_port_t.h
act.social.o: /usr/include/sys/_types/_ino_t.h
act.social.o: /usr/include/sys/_types/_ino64_t.h
act.social.o: /usr/include/sys/_types/_key_t.h
act.social.o: /usr/include/sys/_types/_nlink_t.h
act.social.o: /usr/include/sys/_types/_clock_t.h
act.social.o: /usr/include/sys/_types/_time_t.h
act.social.o: /usr/include/sys/_types/_useconds_t.h
act.social.o: /usr/include/sys/_types/_suseconds_t.h
act.social.o: /usr/include/sys/_types/_fd_def.h
act.social.o: /usr/include/sys/_types/_fd_setsize.h
act.social.o: /usr/include/sys/_types/_fd_set.h
act.social.o: /usr/include/sys/_types/_fd_clr.h
act.social.o: /usr/include/sys/_types/_fd_zero.h
act.social.o: /usr/include/sys/_types/_fd_isset.h
act.social.o: /usr/include/sys/_types/_fd_copy.h
act.social.o: /usr/include/sys/_types/_pthread_cond_t.h
act.social.o: /usr/include/sys/_types/_pthread_condattr_t.h
act.social.o: /usr/include/sys/_types/_pthread_mutex_t.h
act.social.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
act.social.o: /usr/include/sys/_types/_pthread_once_t.h
act.social.o: /usr/include/sys/_types/_pthread_rwlock_t.h
act.social.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
act.social.o: /usr/include/sys/_types/_pthread_t.h
act.social.o: /usr/include/sys/_types/_pthread_key_t.h
act.social.o: /usr/include/sys/_types/_fsblkcnt_t.h
act.social.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
act.social.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h
act.social.o: limits.h poly.h race.h script.h spells.h trap.h utils.h
act.social.o: vt100c.h wizlist.h parser.h
act.wizard.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
act.wizard.o: /usr/include/sys/_symbol_aliasing.h
act.wizard.o: /usr/include/sys/_posix_availability.h
act.wizard.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
act.wizard.o: /usr/include/_types.h /usr/include/sys/_types.h
act.wizard.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
act.wizard.o: /usr/include/sys/_types/_va_list.h
act.wizard.o: /usr/include/sys/_types/_size_t.h
act.wizard.o: /usr/include/sys/_types/_null.h
act.wizard.o: /usr/include/sys/_types/_off_t.h
act.wizard.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
act.wizard.o: /usr/include/secure/_common.h /usr/include/stdlib.h
act.wizard.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
act.wizard.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
act.wizard.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
act.wizard.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
act.wizard.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
act.wizard.o: /usr/include/sys/_types/_sigaltstack.h
act.wizard.o: /usr/include/sys/_types/_ucontext.h
act.wizard.o: /usr/include/sys/_types/_pthread_attr_t.h
act.wizard.o: /usr/include/sys/_types/_sigset_t.h
act.wizard.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
act.wizard.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
act.wizard.o: /usr/include/sys/_types/_int16_t.h
act.wizard.o: /usr/include/sys/_types/_int32_t.h
act.wizard.o: /usr/include/sys/_types/_int64_t.h
act.wizard.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
act.wizard.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
act.wizard.o: /usr/include/sys/_types/_intptr_t.h
act.wizard.o: /usr/include/sys/_types/_uintptr_t.h
act.wizard.o: /usr/include/_types/_intmax_t.h
act.wizard.o: /usr/include/_types/_uintmax_t.h
act.wizard.o: /usr/include/sys/_types/_timeval.h
act.wizard.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
act.wizard.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
act.wizard.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
act.wizard.o: /usr/include/sys/_types/_ct_rune_t.h
act.wizard.o: /usr/include/sys/_types/_rune_t.h
act.wizard.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
act.wizard.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
act.wizard.o: /usr/include/sys/_types/_dev_t.h
act.wizard.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
act.wizard.o: /usr/include/sys/_types/_rsize_t.h
act.wizard.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
act.wizard.o: /usr/include/secure/_string.h /usr/include/ctype.h
act.wizard.o: /usr/include/runetype.h /usr/include/sys/_types/_wint_t.h
act.wizard.o: /usr/include/unistd.h /usr/include/sys/unistd.h
act.wizard.o: /usr/include/sys/_types/_posix_vdisable.h
act.wizard.o: /usr/include/sys/_types/_seek_set.h
act.wizard.o: /usr/include/sys/_types/_gid_t.h
act.wizard.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
act.wizard.o: /usr/include/sys/_types/_fd_def.h
act.wizard.o: /usr/include/sys/_types/_timespec.h
act.wizard.o: /usr/include/sys/_types/_time_t.h
act.wizard.o: /usr/include/sys/_types/_suseconds_t.h
act.wizard.o: /usr/include/sys/_types/_fd_setsize.h
act.wizard.o: /usr/include/sys/_types/_fd_set.h
act.wizard.o: /usr/include/sys/_types/_fd_clr.h
act.wizard.o: /usr/include/sys/_types/_fd_isset.h
act.wizard.o: /usr/include/sys/_types/_fd_zero.h
act.wizard.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
act.wizard.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
act.wizard.o: /usr/include/time.h /usr/include/_structs.h
act.wizard.o: /usr/include/sys/_structs.h /usr/include/sys/_types/_clock_t.h
act.wizard.o: protos.h structs.h /usr/include/sys/types.h
act.wizard.o: /usr/include/sys/_types/_blkcnt_t.h
act.wizard.o: /usr/include/sys/_types/_blksize_t.h
act.wizard.o: /usr/include/sys/_types/_in_addr_t.h
act.wizard.o: /usr/include/sys/_types/_in_port_t.h
act.wizard.o: /usr/include/sys/_types/_ino_t.h
act.wizard.o: /usr/include/sys/_types/_ino64_t.h
act.wizard.o: /usr/include/sys/_types/_key_t.h
act.wizard.o: /usr/include/sys/_types/_nlink_t.h
act.wizard.o: /usr/include/sys/_types/_pthread_cond_t.h
act.wizard.o: /usr/include/sys/_types/_pthread_condattr_t.h
act.wizard.o: /usr/include/sys/_types/_pthread_mutex_t.h
act.wizard.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
act.wizard.o: /usr/include/sys/_types/_pthread_once_t.h
act.wizard.o: /usr/include/sys/_types/_pthread_rwlock_t.h
act.wizard.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
act.wizard.o: /usr/include/sys/_types/_pthread_t.h
act.wizard.o: /usr/include/sys/_types/_pthread_key_t.h
act.wizard.o: /usr/include/sys/_types/_fsblkcnt_t.h
act.wizard.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
act.wizard.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h
act.wizard.o: limits.h poly.h race.h script.h spells.h trap.h utils.h
act.wizard.o: vt100c.h wizlist.h parser.h
handler.o: /usr/include/string.h /usr/include/_types.h
handler.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
handler.o: /usr/include/sys/_symbol_aliasing.h
handler.o: /usr/include/sys/_posix_availability.h
handler.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
handler.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
handler.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
handler.o: /usr/include/sys/_types/_rsize_t.h
handler.o: /usr/include/sys/_types/_errno_t.h
handler.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
handler.o: /usr/include/secure/_string.h /usr/include/secure/_common.h
handler.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
handler.o: /usr/include/sys/_types/_off_t.h /usr/include/secure/_stdio.h
handler.o: /usr/include/ctype.h /usr/include/runetype.h
handler.o: /usr/include/sys/_types/_ct_rune_t.h
handler.o: /usr/include/sys/_types/_rune_t.h
handler.o: /usr/include/sys/_types/_wchar_t.h
handler.o: /usr/include/sys/_types/_wint_t.h /usr/include/assert.h protos.h
handler.o: structs.h /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
handler.o: /usr/include/machine/types.h /usr/include/i386/types.h
handler.o: /usr/include/sys/_types/_int8_t.h
handler.o: /usr/include/sys/_types/_int16_t.h
handler.o: /usr/include/sys/_types/_int32_t.h
handler.o: /usr/include/sys/_types/_int64_t.h
handler.o: /usr/include/sys/_types/_intptr_t.h
handler.o: /usr/include/sys/_types/_uintptr_t.h
handler.o: /usr/include/sys/_types/___offsetof.h
handler.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
handler.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
handler.o: /usr/include/libkern/i386/_OSByteOrder.h
handler.o: /usr/include/sys/_types/_dev_t.h
handler.o: /usr/include/sys/_types/_blkcnt_t.h
handler.o: /usr/include/sys/_types/_blksize_t.h
handler.o: /usr/include/sys/_types/_gid_t.h
handler.o: /usr/include/sys/_types/_in_addr_t.h
handler.o: /usr/include/sys/_types/_in_port_t.h
handler.o: /usr/include/sys/_types/_ino_t.h
handler.o: /usr/include/sys/_types/_ino64_t.h
handler.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
handler.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
handler.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
handler.o: /usr/include/sys/_types/_clock_t.h
handler.o: /usr/include/sys/_types/_time_t.h
handler.o: /usr/include/sys/_types/_useconds_t.h
handler.o: /usr/include/sys/_types/_suseconds_t.h
handler.o: /usr/include/sys/_types/_fd_def.h
handler.o: /usr/include/sys/_types/_fd_setsize.h
handler.o: /usr/include/sys/_types/_fd_set.h
handler.o: /usr/include/sys/_types/_fd_clr.h
handler.o: /usr/include/sys/_types/_fd_zero.h
handler.o: /usr/include/sys/_types/_fd_isset.h
handler.o: /usr/include/sys/_types/_fd_copy.h
handler.o: /usr/include/sys/_types/_pthread_attr_t.h
handler.o: /usr/include/sys/_types/_pthread_cond_t.h
handler.o: /usr/include/sys/_types/_pthread_condattr_t.h
handler.o: /usr/include/sys/_types/_pthread_mutex_t.h
handler.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
handler.o: /usr/include/sys/_types/_pthread_once_t.h
handler.o: /usr/include/sys/_types/_pthread_rwlock_t.h
handler.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
handler.o: /usr/include/sys/_types/_pthread_t.h
handler.o: /usr/include/sys/_types/_pthread_key_t.h
handler.o: /usr/include/sys/_types/_fsblkcnt_t.h
handler.o: /usr/include/sys/_types/_fsfilcnt_t.h area.h comm.h db.h handler.h
handler.o: hash.h heap.h interpreter.h limits.h poly.h race.h script.h
handler.o: spells.h trap.h utils.h vt100c.h wizlist.h parser.h
db.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
db.o: /usr/include/sys/_symbol_aliasing.h
db.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
db.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
db.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
db.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
db.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
db.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
db.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
db.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
db.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
db.o: /usr/include/secure/_string.h /usr/include/ctype.h
db.o: /usr/include/runetype.h /usr/include/sys/_types/_ct_rune_t.h
db.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
db.o: /usr/include/sys/_types/_wint_t.h /usr/include/time.h
db.o: /usr/include/_structs.h /usr/include/sys/_structs.h
db.o: /usr/include/sys/_types/_timespec.h /usr/include/sys/_types/_clock_t.h
db.o: /usr/include/sys/_types/_time_t.h protos.h structs.h
db.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
db.o: /usr/include/machine/types.h /usr/include/i386/types.h
db.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
db.o: /usr/include/sys/_types/_int32_t.h /usr/include/sys/_types/_int64_t.h
db.o: /usr/include/sys/_types/_intptr_t.h
db.o: /usr/include/sys/_types/_uintptr_t.h
db.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
db.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
db.o: /usr/include/libkern/_OSByteOrder.h
db.o: /usr/include/libkern/i386/_OSByteOrder.h
db.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_blkcnt_t.h
db.o: /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h
db.o: /usr/include/sys/_types/_in_addr_t.h
db.o: /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h
db.o: /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h
db.o: /usr/include/sys/_types/_mode_t.h /usr/include/sys/_types/_nlink_t.h
db.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/_types/_pid_t.h
db.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_useconds_t.h
db.o: /usr/include/sys/_types/_suseconds_t.h
db.o: /usr/include/sys/_types/_fd_def.h /usr/include/sys/_types/_fd_setsize.h
db.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
db.o: /usr/include/sys/_types/_fd_zero.h /usr/include/sys/_types/_fd_isset.h
db.o: /usr/include/sys/_types/_fd_copy.h
db.o: /usr/include/sys/_types/_pthread_attr_t.h
db.o: /usr/include/sys/_types/_pthread_cond_t.h
db.o: /usr/include/sys/_types/_pthread_condattr_t.h
db.o: /usr/include/sys/_types/_pthread_mutex_t.h
db.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
db.o: /usr/include/sys/_types/_pthread_once_t.h
db.o: /usr/include/sys/_types/_pthread_rwlock_t.h
db.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
db.o: /usr/include/sys/_types/_pthread_t.h
db.o: /usr/include/sys/_types/_pthread_key_t.h
db.o: /usr/include/sys/_types/_fsblkcnt_t.h
db.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
db.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
db.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
interpreter.o: /usr/include/string.h /usr/include/_types.h
interpreter.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
interpreter.o: /usr/include/sys/_symbol_aliasing.h
interpreter.o: /usr/include/sys/_posix_availability.h
interpreter.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
interpreter.o: /usr/include/Availability.h
interpreter.o: /usr/include/AvailabilityInternal.h
interpreter.o: /usr/include/sys/_types/_size_t.h
interpreter.o: /usr/include/sys/_types/_null.h
interpreter.o: /usr/include/sys/_types/_rsize_t.h
interpreter.o: /usr/include/sys/_types/_errno_t.h
interpreter.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
interpreter.o: /usr/include/secure/_string.h /usr/include/secure/_common.h
interpreter.o: /usr/include/ctype.h /usr/include/runetype.h
interpreter.o: /usr/include/sys/_types/_ct_rune_t.h
interpreter.o: /usr/include/sys/_types/_rune_t.h
interpreter.o: /usr/include/sys/_types/_wchar_t.h
interpreter.o: /usr/include/sys/_types/_wint_t.h /usr/include/stdio.h
interpreter.o: /usr/include/sys/_types/_va_list.h
interpreter.o: /usr/include/sys/_types/_off_t.h /usr/include/secure/_stdio.h
interpreter.o: /usr/include/arpa/telnet.h protos.h structs.h
interpreter.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
interpreter.o: /usr/include/machine/types.h /usr/include/i386/types.h
interpreter.o: /usr/include/sys/_types/_int8_t.h
interpreter.o: /usr/include/sys/_types/_int16_t.h
interpreter.o: /usr/include/sys/_types/_int32_t.h
interpreter.o: /usr/include/sys/_types/_int64_t.h
interpreter.o: /usr/include/sys/_types/_intptr_t.h
interpreter.o: /usr/include/sys/_types/_uintptr_t.h
interpreter.o: /usr/include/sys/_types/___offsetof.h
interpreter.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
interpreter.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
interpreter.o: /usr/include/libkern/i386/_OSByteOrder.h
interpreter.o: /usr/include/sys/_types/_dev_t.h
interpreter.o: /usr/include/sys/_types/_blkcnt_t.h
interpreter.o: /usr/include/sys/_types/_blksize_t.h
interpreter.o: /usr/include/sys/_types/_gid_t.h
interpreter.o: /usr/include/sys/_types/_in_addr_t.h
interpreter.o: /usr/include/sys/_types/_in_port_t.h
interpreter.o: /usr/include/sys/_types/_ino_t.h
interpreter.o: /usr/include/sys/_types/_ino64_t.h
interpreter.o: /usr/include/sys/_types/_key_t.h
interpreter.o: /usr/include/sys/_types/_mode_t.h
interpreter.o: /usr/include/sys/_types/_nlink_t.h
interpreter.o: /usr/include/sys/_types/_id_t.h
interpreter.o: /usr/include/sys/_types/_pid_t.h
interpreter.o: /usr/include/sys/_types/_uid_t.h
interpreter.o: /usr/include/sys/_types/_clock_t.h
interpreter.o: /usr/include/sys/_types/_time_t.h
interpreter.o: /usr/include/sys/_types/_useconds_t.h
interpreter.o: /usr/include/sys/_types/_suseconds_t.h
interpreter.o: /usr/include/sys/_types/_fd_def.h
interpreter.o: /usr/include/sys/_types/_fd_setsize.h
interpreter.o: /usr/include/sys/_types/_fd_set.h
interpreter.o: /usr/include/sys/_types/_fd_clr.h
interpreter.o: /usr/include/sys/_types/_fd_zero.h
interpreter.o: /usr/include/sys/_types/_fd_isset.h
interpreter.o: /usr/include/sys/_types/_fd_copy.h
interpreter.o: /usr/include/sys/_types/_pthread_attr_t.h
interpreter.o: /usr/include/sys/_types/_pthread_cond_t.h
interpreter.o: /usr/include/sys/_types/_pthread_condattr_t.h
interpreter.o: /usr/include/sys/_types/_pthread_mutex_t.h
interpreter.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
interpreter.o: /usr/include/sys/_types/_pthread_once_t.h
interpreter.o: /usr/include/sys/_types/_pthread_rwlock_t.h
interpreter.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
interpreter.o: /usr/include/sys/_types/_pthread_t.h
interpreter.o: /usr/include/sys/_types/_pthread_key_t.h
interpreter.o: /usr/include/sys/_types/_fsblkcnt_t.h
interpreter.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
interpreter.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h
interpreter.o: limits.h poly.h race.h script.h spells.h trap.h utils.h
interpreter.o: vt100c.h wizlist.h parser.h
utility.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
utility.o: /usr/include/sys/_symbol_aliasing.h
utility.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
utility.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
utility.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
utility.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
utility.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
utility.o: /usr/include/sys/_types/_off_t.h
utility.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
utility.o: /usr/include/secure/_common.h /usr/include/stdlib.h
utility.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
utility.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
utility.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
utility.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
utility.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
utility.o: /usr/include/sys/_types/_sigaltstack.h
utility.o: /usr/include/sys/_types/_ucontext.h
utility.o: /usr/include/sys/_types/_pthread_attr_t.h
utility.o: /usr/include/sys/_types/_sigset_t.h
utility.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
utility.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
utility.o: /usr/include/sys/_types/_int16_t.h
utility.o: /usr/include/sys/_types/_int32_t.h
utility.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
utility.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
utility.o: /usr/include/_types/_uint64_t.h
utility.o: /usr/include/sys/_types/_intptr_t.h
utility.o: /usr/include/sys/_types/_uintptr_t.h
utility.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
utility.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
utility.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
utility.o: /usr/include/libkern/_OSByteOrder.h
utility.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
utility.o: /usr/include/sys/_types/_ct_rune_t.h
utility.o: /usr/include/sys/_types/_rune_t.h
utility.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
utility.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
utility.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
utility.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
utility.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
utility.o: /usr/include/secure/_string.h /usr/include/ctype.h
utility.o: /usr/include/runetype.h /usr/include/sys/_types/_wint_t.h
utility.o: /usr/include/time.h /usr/include/_structs.h
utility.o: /usr/include/sys/_structs.h /usr/include/sys/_types/_timespec.h
utility.o: /usr/include/sys/_types/_clock_t.h
utility.o: /usr/include/sys/_types/_time_t.h protos.h structs.h
utility.o: /usr/include/sys/types.h /usr/include/sys/_types/_blkcnt_t.h
utility.o: /usr/include/sys/_types/_blksize_t.h
utility.o: /usr/include/sys/_types/_gid_t.h
utility.o: /usr/include/sys/_types/_in_addr_t.h
utility.o: /usr/include/sys/_types/_in_port_t.h
utility.o: /usr/include/sys/_types/_ino_t.h
utility.o: /usr/include/sys/_types/_ino64_t.h
utility.o: /usr/include/sys/_types/_key_t.h
utility.o: /usr/include/sys/_types/_nlink_t.h
utility.o: /usr/include/sys/_types/_useconds_t.h
utility.o: /usr/include/sys/_types/_suseconds_t.h
utility.o: /usr/include/sys/_types/_fd_def.h
utility.o: /usr/include/sys/_types/_fd_setsize.h
utility.o: /usr/include/sys/_types/_fd_set.h
utility.o: /usr/include/sys/_types/_fd_clr.h
utility.o: /usr/include/sys/_types/_fd_zero.h
utility.o: /usr/include/sys/_types/_fd_isset.h
utility.o: /usr/include/sys/_types/_fd_copy.h
utility.o: /usr/include/sys/_types/_pthread_cond_t.h
utility.o: /usr/include/sys/_types/_pthread_condattr_t.h
utility.o: /usr/include/sys/_types/_pthread_mutex_t.h
utility.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
utility.o: /usr/include/sys/_types/_pthread_once_t.h
utility.o: /usr/include/sys/_types/_pthread_rwlock_t.h
utility.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
utility.o: /usr/include/sys/_types/_pthread_t.h
utility.o: /usr/include/sys/_types/_pthread_key_t.h
utility.o: /usr/include/sys/_types/_fsblkcnt_t.h
utility.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
utility.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
utility.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h
utility.o: parser.h
spec_assign.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
spec_assign.o: /usr/include/sys/_symbol_aliasing.h
spec_assign.o: /usr/include/sys/_posix_availability.h
spec_assign.o: /usr/include/Availability.h
spec_assign.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
spec_assign.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
spec_assign.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
spec_assign.o: /usr/include/sys/_types/_size_t.h
spec_assign.o: /usr/include/sys/_types/_null.h
spec_assign.o: /usr/include/sys/_types/_off_t.h
spec_assign.o: /usr/include/sys/_types/_ssize_t.h
spec_assign.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
spec_assign.o: protos.h structs.h /usr/include/sys/types.h
spec_assign.o: /usr/include/sys/appleapiopts.h /usr/include/machine/types.h
spec_assign.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
spec_assign.o: /usr/include/sys/_types/_int16_t.h
spec_assign.o: /usr/include/sys/_types/_int32_t.h
spec_assign.o: /usr/include/sys/_types/_int64_t.h
spec_assign.o: /usr/include/sys/_types/_intptr_t.h
spec_assign.o: /usr/include/sys/_types/_uintptr_t.h
spec_assign.o: /usr/include/sys/_types/___offsetof.h
spec_assign.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
spec_assign.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
spec_assign.o: /usr/include/libkern/i386/_OSByteOrder.h
spec_assign.o: /usr/include/sys/_types/_dev_t.h
spec_assign.o: /usr/include/sys/_types/_blkcnt_t.h
spec_assign.o: /usr/include/sys/_types/_blksize_t.h
spec_assign.o: /usr/include/sys/_types/_gid_t.h
spec_assign.o: /usr/include/sys/_types/_in_addr_t.h
spec_assign.o: /usr/include/sys/_types/_in_port_t.h
spec_assign.o: /usr/include/sys/_types/_ino_t.h
spec_assign.o: /usr/include/sys/_types/_ino64_t.h
spec_assign.o: /usr/include/sys/_types/_key_t.h
spec_assign.o: /usr/include/sys/_types/_mode_t.h
spec_assign.o: /usr/include/sys/_types/_nlink_t.h
spec_assign.o: /usr/include/sys/_types/_id_t.h
spec_assign.o: /usr/include/sys/_types/_pid_t.h
spec_assign.o: /usr/include/sys/_types/_uid_t.h
spec_assign.o: /usr/include/sys/_types/_clock_t.h
spec_assign.o: /usr/include/sys/_types/_time_t.h
spec_assign.o: /usr/include/sys/_types/_useconds_t.h
spec_assign.o: /usr/include/sys/_types/_suseconds_t.h
spec_assign.o: /usr/include/sys/_types/_rsize_t.h
spec_assign.o: /usr/include/sys/_types/_errno_t.h
spec_assign.o: /usr/include/sys/_types/_fd_def.h
spec_assign.o: /usr/include/sys/_types/_fd_setsize.h
spec_assign.o: /usr/include/sys/_types/_fd_set.h
spec_assign.o: /usr/include/sys/_types/_fd_clr.h
spec_assign.o: /usr/include/sys/_types/_fd_zero.h
spec_assign.o: /usr/include/sys/_types/_fd_isset.h
spec_assign.o: /usr/include/sys/_types/_fd_copy.h
spec_assign.o: /usr/include/sys/_types/_pthread_attr_t.h
spec_assign.o: /usr/include/sys/_types/_pthread_cond_t.h
spec_assign.o: /usr/include/sys/_types/_pthread_condattr_t.h
spec_assign.o: /usr/include/sys/_types/_pthread_mutex_t.h
spec_assign.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
spec_assign.o: /usr/include/sys/_types/_pthread_once_t.h
spec_assign.o: /usr/include/sys/_types/_pthread_rwlock_t.h
spec_assign.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
spec_assign.o: /usr/include/sys/_types/_pthread_t.h
spec_assign.o: /usr/include/sys/_types/_pthread_key_t.h
spec_assign.o: /usr/include/sys/_types/_fsblkcnt_t.h
spec_assign.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
spec_assign.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h
spec_assign.o: limits.h poly.h race.h script.h spells.h trap.h utils.h
spec_assign.o: vt100c.h wizlist.h parser.h
shop.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
shop.o: /usr/include/sys/_symbol_aliasing.h
shop.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
shop.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
shop.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
shop.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
shop.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
shop.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
shop.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
shop.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
shop.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
shop.o: /usr/include/secure/_string.h protos.h structs.h
shop.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
shop.o: /usr/include/machine/types.h /usr/include/i386/types.h
shop.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
shop.o: /usr/include/sys/_types/_int32_t.h /usr/include/sys/_types/_int64_t.h
shop.o: /usr/include/sys/_types/_intptr_t.h
shop.o: /usr/include/sys/_types/_uintptr_t.h
shop.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
shop.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
shop.o: /usr/include/libkern/_OSByteOrder.h
shop.o: /usr/include/libkern/i386/_OSByteOrder.h
shop.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_blkcnt_t.h
shop.o: /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h
shop.o: /usr/include/sys/_types/_in_addr_t.h
shop.o: /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h
shop.o: /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h
shop.o: /usr/include/sys/_types/_mode_t.h /usr/include/sys/_types/_nlink_t.h
shop.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/_types/_pid_t.h
shop.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_clock_t.h
shop.o: /usr/include/sys/_types/_time_t.h
shop.o: /usr/include/sys/_types/_useconds_t.h
shop.o: /usr/include/sys/_types/_suseconds_t.h
shop.o: /usr/include/sys/_types/_fd_def.h
shop.o: /usr/include/sys/_types/_fd_setsize.h
shop.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
shop.o: /usr/include/sys/_types/_fd_zero.h
shop.o: /usr/include/sys/_types/_fd_isset.h
shop.o: /usr/include/sys/_types/_fd_copy.h
shop.o: /usr/include/sys/_types/_pthread_attr_t.h
shop.o: /usr/include/sys/_types/_pthread_cond_t.h
shop.o: /usr/include/sys/_types/_pthread_condattr_t.h
shop.o: /usr/include/sys/_types/_pthread_mutex_t.h
shop.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
shop.o: /usr/include/sys/_types/_pthread_once_t.h
shop.o: /usr/include/sys/_types/_pthread_rwlock_t.h
shop.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
shop.o: /usr/include/sys/_types/_pthread_t.h
shop.o: /usr/include/sys/_types/_pthread_key_t.h
shop.o: /usr/include/sys/_types/_fsblkcnt_t.h
shop.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
shop.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
shop.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
limits.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
limits.o: /usr/include/sys/_symbol_aliasing.h
limits.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
limits.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
limits.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
limits.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
limits.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
limits.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
limits.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
limits.o: /usr/include/assert.h protos.h structs.h /usr/include/sys/types.h
limits.o: /usr/include/sys/appleapiopts.h /usr/include/machine/types.h
limits.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
limits.o: /usr/include/sys/_types/_int16_t.h
limits.o: /usr/include/sys/_types/_int32_t.h
limits.o: /usr/include/sys/_types/_int64_t.h
limits.o: /usr/include/sys/_types/_intptr_t.h
limits.o: /usr/include/sys/_types/_uintptr_t.h
limits.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
limits.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
limits.o: /usr/include/libkern/_OSByteOrder.h
limits.o: /usr/include/libkern/i386/_OSByteOrder.h
limits.o: /usr/include/sys/_types/_dev_t.h
limits.o: /usr/include/sys/_types/_blkcnt_t.h
limits.o: /usr/include/sys/_types/_blksize_t.h
limits.o: /usr/include/sys/_types/_gid_t.h
limits.o: /usr/include/sys/_types/_in_addr_t.h
limits.o: /usr/include/sys/_types/_in_port_t.h
limits.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
limits.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
limits.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
limits.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
limits.o: /usr/include/sys/_types/_clock_t.h
limits.o: /usr/include/sys/_types/_time_t.h
limits.o: /usr/include/sys/_types/_useconds_t.h
limits.o: /usr/include/sys/_types/_suseconds_t.h
limits.o: /usr/include/sys/_types/_rsize_t.h
limits.o: /usr/include/sys/_types/_errno_t.h
limits.o: /usr/include/sys/_types/_fd_def.h
limits.o: /usr/include/sys/_types/_fd_setsize.h
limits.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
limits.o: /usr/include/sys/_types/_fd_zero.h
limits.o: /usr/include/sys/_types/_fd_isset.h
limits.o: /usr/include/sys/_types/_fd_copy.h
limits.o: /usr/include/sys/_types/_pthread_attr_t.h
limits.o: /usr/include/sys/_types/_pthread_cond_t.h
limits.o: /usr/include/sys/_types/_pthread_condattr_t.h
limits.o: /usr/include/sys/_types/_pthread_mutex_t.h
limits.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
limits.o: /usr/include/sys/_types/_pthread_once_t.h
limits.o: /usr/include/sys/_types/_pthread_rwlock_t.h
limits.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
limits.o: /usr/include/sys/_types/_pthread_t.h
limits.o: /usr/include/sys/_types/_pthread_key_t.h
limits.o: /usr/include/sys/_types/_fsblkcnt_t.h
limits.o: /usr/include/sys/_types/_fsfilcnt_t.h area.h comm.h db.h handler.h
limits.o: hash.h heap.h interpreter.h limits.h poly.h race.h script.h
limits.o: spells.h trap.h utils.h vt100c.h wizlist.h parser.h
mobact.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
mobact.o: /usr/include/sys/_symbol_aliasing.h
mobact.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
mobact.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
mobact.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
mobact.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
mobact.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
mobact.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
mobact.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
mobact.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
mobact.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
mobact.o: /usr/include/secure/_string.h protos.h structs.h
mobact.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
mobact.o: /usr/include/machine/types.h /usr/include/i386/types.h
mobact.o: /usr/include/sys/_types/_int8_t.h
mobact.o: /usr/include/sys/_types/_int16_t.h
mobact.o: /usr/include/sys/_types/_int32_t.h
mobact.o: /usr/include/sys/_types/_int64_t.h
mobact.o: /usr/include/sys/_types/_intptr_t.h
mobact.o: /usr/include/sys/_types/_uintptr_t.h
mobact.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
mobact.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
mobact.o: /usr/include/libkern/_OSByteOrder.h
mobact.o: /usr/include/libkern/i386/_OSByteOrder.h
mobact.o: /usr/include/sys/_types/_dev_t.h
mobact.o: /usr/include/sys/_types/_blkcnt_t.h
mobact.o: /usr/include/sys/_types/_blksize_t.h
mobact.o: /usr/include/sys/_types/_gid_t.h
mobact.o: /usr/include/sys/_types/_in_addr_t.h
mobact.o: /usr/include/sys/_types/_in_port_t.h
mobact.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
mobact.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
mobact.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
mobact.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
mobact.o: /usr/include/sys/_types/_clock_t.h
mobact.o: /usr/include/sys/_types/_time_t.h
mobact.o: /usr/include/sys/_types/_useconds_t.h
mobact.o: /usr/include/sys/_types/_suseconds_t.h
mobact.o: /usr/include/sys/_types/_fd_def.h
mobact.o: /usr/include/sys/_types/_fd_setsize.h
mobact.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
mobact.o: /usr/include/sys/_types/_fd_zero.h
mobact.o: /usr/include/sys/_types/_fd_isset.h
mobact.o: /usr/include/sys/_types/_fd_copy.h
mobact.o: /usr/include/sys/_types/_pthread_attr_t.h
mobact.o: /usr/include/sys/_types/_pthread_cond_t.h
mobact.o: /usr/include/sys/_types/_pthread_condattr_t.h
mobact.o: /usr/include/sys/_types/_pthread_mutex_t.h
mobact.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
mobact.o: /usr/include/sys/_types/_pthread_once_t.h
mobact.o: /usr/include/sys/_types/_pthread_rwlock_t.h
mobact.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
mobact.o: /usr/include/sys/_types/_pthread_t.h
mobact.o: /usr/include/sys/_types/_pthread_key_t.h
mobact.o: /usr/include/sys/_types/_fsblkcnt_t.h
mobact.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
mobact.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
mobact.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
fight.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
fight.o: /usr/include/sys/_symbol_aliasing.h
fight.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
fight.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
fight.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
fight.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
fight.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
fight.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
fight.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
fight.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
fight.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
fight.o: /usr/include/secure/_string.h /usr/include/assert.h protos.h
fight.o: structs.h /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
fight.o: /usr/include/machine/types.h /usr/include/i386/types.h
fight.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
fight.o: /usr/include/sys/_types/_int32_t.h
fight.o: /usr/include/sys/_types/_int64_t.h
fight.o: /usr/include/sys/_types/_intptr_t.h
fight.o: /usr/include/sys/_types/_uintptr_t.h
fight.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
fight.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
fight.o: /usr/include/libkern/_OSByteOrder.h
fight.o: /usr/include/libkern/i386/_OSByteOrder.h
fight.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_blkcnt_t.h
fight.o: /usr/include/sys/_types/_blksize_t.h
fight.o: /usr/include/sys/_types/_gid_t.h
fight.o: /usr/include/sys/_types/_in_addr_t.h
fight.o: /usr/include/sys/_types/_in_port_t.h
fight.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
fight.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
fight.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
fight.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
fight.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h
fight.o: /usr/include/sys/_types/_useconds_t.h
fight.o: /usr/include/sys/_types/_suseconds_t.h
fight.o: /usr/include/sys/_types/_fd_def.h
fight.o: /usr/include/sys/_types/_fd_setsize.h
fight.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
fight.o: /usr/include/sys/_types/_fd_zero.h
fight.o: /usr/include/sys/_types/_fd_isset.h
fight.o: /usr/include/sys/_types/_fd_copy.h
fight.o: /usr/include/sys/_types/_pthread_attr_t.h
fight.o: /usr/include/sys/_types/_pthread_cond_t.h
fight.o: /usr/include/sys/_types/_pthread_condattr_t.h
fight.o: /usr/include/sys/_types/_pthread_mutex_t.h
fight.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
fight.o: /usr/include/sys/_types/_pthread_once_t.h
fight.o: /usr/include/sys/_types/_pthread_rwlock_t.h
fight.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
fight.o: /usr/include/sys/_types/_pthread_t.h
fight.o: /usr/include/sys/_types/_pthread_key_t.h
fight.o: /usr/include/sys/_types/_fsblkcnt_t.h
fight.o: /usr/include/sys/_types/_fsfilcnt_t.h area.h comm.h db.h handler.h
fight.o: hash.h heap.h interpreter.h limits.h poly.h race.h script.h spells.h
fight.o: trap.h utils.h vt100c.h wizlist.h parser.h
modify.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
modify.o: /usr/include/sys/_symbol_aliasing.h
modify.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
modify.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
modify.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
modify.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
modify.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
modify.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
modify.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
modify.o: /usr/include/ctype.h /usr/include/runetype.h
modify.o: /usr/include/sys/_types/_ct_rune_t.h
modify.o: /usr/include/sys/_types/_rune_t.h
modify.o: /usr/include/sys/_types/_wchar_t.h
modify.o: /usr/include/sys/_types/_wint_t.h /usr/include/string.h
modify.o: /usr/include/sys/_types/_rsize_t.h
modify.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
modify.o: /usr/include/secure/_string.h /usr/include/time.h
modify.o: /usr/include/_structs.h /usr/include/sys/_structs.h
modify.o: /usr/include/sys/_types/_timespec.h
modify.o: /usr/include/sys/_types/_clock_t.h
modify.o: /usr/include/sys/_types/_time_t.h protos.h structs.h
modify.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
modify.o: /usr/include/machine/types.h /usr/include/i386/types.h
modify.o: /usr/include/sys/_types/_int8_t.h
modify.o: /usr/include/sys/_types/_int16_t.h
modify.o: /usr/include/sys/_types/_int32_t.h
modify.o: /usr/include/sys/_types/_int64_t.h
modify.o: /usr/include/sys/_types/_intptr_t.h
modify.o: /usr/include/sys/_types/_uintptr_t.h
modify.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
modify.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
modify.o: /usr/include/libkern/_OSByteOrder.h
modify.o: /usr/include/libkern/i386/_OSByteOrder.h
modify.o: /usr/include/sys/_types/_dev_t.h
modify.o: /usr/include/sys/_types/_blkcnt_t.h
modify.o: /usr/include/sys/_types/_blksize_t.h
modify.o: /usr/include/sys/_types/_gid_t.h
modify.o: /usr/include/sys/_types/_in_addr_t.h
modify.o: /usr/include/sys/_types/_in_port_t.h
modify.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
modify.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
modify.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
modify.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
modify.o: /usr/include/sys/_types/_useconds_t.h
modify.o: /usr/include/sys/_types/_suseconds_t.h
modify.o: /usr/include/sys/_types/_fd_def.h
modify.o: /usr/include/sys/_types/_fd_setsize.h
modify.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
modify.o: /usr/include/sys/_types/_fd_zero.h
modify.o: /usr/include/sys/_types/_fd_isset.h
modify.o: /usr/include/sys/_types/_fd_copy.h
modify.o: /usr/include/sys/_types/_pthread_attr_t.h
modify.o: /usr/include/sys/_types/_pthread_cond_t.h
modify.o: /usr/include/sys/_types/_pthread_condattr_t.h
modify.o: /usr/include/sys/_types/_pthread_mutex_t.h
modify.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
modify.o: /usr/include/sys/_types/_pthread_once_t.h
modify.o: /usr/include/sys/_types/_pthread_rwlock_t.h
modify.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
modify.o: /usr/include/sys/_types/_pthread_t.h
modify.o: /usr/include/sys/_types/_pthread_key_t.h
modify.o: /usr/include/sys/_types/_fsblkcnt_t.h
modify.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
modify.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
modify.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
weather.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
weather.o: /usr/include/sys/_symbol_aliasing.h
weather.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
weather.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
weather.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
weather.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
weather.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
weather.o: /usr/include/sys/_types/_off_t.h
weather.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
weather.o: /usr/include/secure/_common.h /usr/include/string.h
weather.o: /usr/include/sys/_types/_rsize_t.h
weather.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
weather.o: /usr/include/secure/_string.h protos.h structs.h
weather.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
weather.o: /usr/include/machine/types.h /usr/include/i386/types.h
weather.o: /usr/include/sys/_types/_int8_t.h
weather.o: /usr/include/sys/_types/_int16_t.h
weather.o: /usr/include/sys/_types/_int32_t.h
weather.o: /usr/include/sys/_types/_int64_t.h
weather.o: /usr/include/sys/_types/_intptr_t.h
weather.o: /usr/include/sys/_types/_uintptr_t.h
weather.o: /usr/include/sys/_types/___offsetof.h
weather.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
weather.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
weather.o: /usr/include/libkern/i386/_OSByteOrder.h
weather.o: /usr/include/sys/_types/_dev_t.h
weather.o: /usr/include/sys/_types/_blkcnt_t.h
weather.o: /usr/include/sys/_types/_blksize_t.h
weather.o: /usr/include/sys/_types/_gid_t.h
weather.o: /usr/include/sys/_types/_in_addr_t.h
weather.o: /usr/include/sys/_types/_in_port_t.h
weather.o: /usr/include/sys/_types/_ino_t.h
weather.o: /usr/include/sys/_types/_ino64_t.h
weather.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
weather.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
weather.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
weather.o: /usr/include/sys/_types/_clock_t.h
weather.o: /usr/include/sys/_types/_time_t.h
weather.o: /usr/include/sys/_types/_useconds_t.h
weather.o: /usr/include/sys/_types/_suseconds_t.h
weather.o: /usr/include/sys/_types/_fd_def.h
weather.o: /usr/include/sys/_types/_fd_setsize.h
weather.o: /usr/include/sys/_types/_fd_set.h
weather.o: /usr/include/sys/_types/_fd_clr.h
weather.o: /usr/include/sys/_types/_fd_zero.h
weather.o: /usr/include/sys/_types/_fd_isset.h
weather.o: /usr/include/sys/_types/_fd_copy.h
weather.o: /usr/include/sys/_types/_pthread_attr_t.h
weather.o: /usr/include/sys/_types/_pthread_cond_t.h
weather.o: /usr/include/sys/_types/_pthread_condattr_t.h
weather.o: /usr/include/sys/_types/_pthread_mutex_t.h
weather.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
weather.o: /usr/include/sys/_types/_pthread_once_t.h
weather.o: /usr/include/sys/_types/_pthread_rwlock_t.h
weather.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
weather.o: /usr/include/sys/_types/_pthread_t.h
weather.o: /usr/include/sys/_types/_pthread_key_t.h
weather.o: /usr/include/sys/_types/_fsblkcnt_t.h
weather.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
weather.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
weather.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h
weather.o: parser.h
spells1.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
spells1.o: /usr/include/sys/_symbol_aliasing.h
spells1.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
spells1.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
spells1.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
spells1.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
spells1.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
spells1.o: /usr/include/sys/_types/_off_t.h
spells1.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
spells1.o: /usr/include/secure/_common.h protos.h structs.h
spells1.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
spells1.o: /usr/include/machine/types.h /usr/include/i386/types.h
spells1.o: /usr/include/sys/_types/_int8_t.h
spells1.o: /usr/include/sys/_types/_int16_t.h
spells1.o: /usr/include/sys/_types/_int32_t.h
spells1.o: /usr/include/sys/_types/_int64_t.h
spells1.o: /usr/include/sys/_types/_intptr_t.h
spells1.o: /usr/include/sys/_types/_uintptr_t.h
spells1.o: /usr/include/sys/_types/___offsetof.h
spells1.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
spells1.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
spells1.o: /usr/include/libkern/i386/_OSByteOrder.h
spells1.o: /usr/include/sys/_types/_dev_t.h
spells1.o: /usr/include/sys/_types/_blkcnt_t.h
spells1.o: /usr/include/sys/_types/_blksize_t.h
spells1.o: /usr/include/sys/_types/_gid_t.h
spells1.o: /usr/include/sys/_types/_in_addr_t.h
spells1.o: /usr/include/sys/_types/_in_port_t.h
spells1.o: /usr/include/sys/_types/_ino_t.h
spells1.o: /usr/include/sys/_types/_ino64_t.h
spells1.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
spells1.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
spells1.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
spells1.o: /usr/include/sys/_types/_clock_t.h
spells1.o: /usr/include/sys/_types/_time_t.h
spells1.o: /usr/include/sys/_types/_useconds_t.h
spells1.o: /usr/include/sys/_types/_suseconds_t.h
spells1.o: /usr/include/sys/_types/_rsize_t.h
spells1.o: /usr/include/sys/_types/_errno_t.h
spells1.o: /usr/include/sys/_types/_fd_def.h
spells1.o: /usr/include/sys/_types/_fd_setsize.h
spells1.o: /usr/include/sys/_types/_fd_set.h
spells1.o: /usr/include/sys/_types/_fd_clr.h
spells1.o: /usr/include/sys/_types/_fd_zero.h
spells1.o: /usr/include/sys/_types/_fd_isset.h
spells1.o: /usr/include/sys/_types/_fd_copy.h
spells1.o: /usr/include/sys/_types/_pthread_attr_t.h
spells1.o: /usr/include/sys/_types/_pthread_cond_t.h
spells1.o: /usr/include/sys/_types/_pthread_condattr_t.h
spells1.o: /usr/include/sys/_types/_pthread_mutex_t.h
spells1.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
spells1.o: /usr/include/sys/_types/_pthread_once_t.h
spells1.o: /usr/include/sys/_types/_pthread_rwlock_t.h
spells1.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
spells1.o: /usr/include/sys/_types/_pthread_t.h
spells1.o: /usr/include/sys/_types/_pthread_key_t.h
spells1.o: /usr/include/sys/_types/_fsblkcnt_t.h
spells1.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
spells1.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
spells1.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h
spells1.o: parser.h
spells2.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
spells2.o: /usr/include/sys/_symbol_aliasing.h
spells2.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
spells2.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
spells2.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
spells2.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
spells2.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
spells2.o: /usr/include/sys/_types/_off_t.h
spells2.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
spells2.o: /usr/include/secure/_common.h /usr/include/strings.h
spells2.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
spells2.o: /usr/include/sys/_types/_errno_t.h /usr/include/secure/_string.h
spells2.o: protos.h structs.h /usr/include/sys/types.h
spells2.o: /usr/include/sys/appleapiopts.h /usr/include/machine/types.h
spells2.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
spells2.o: /usr/include/sys/_types/_int16_t.h
spells2.o: /usr/include/sys/_types/_int32_t.h
spells2.o: /usr/include/sys/_types/_int64_t.h
spells2.o: /usr/include/sys/_types/_intptr_t.h
spells2.o: /usr/include/sys/_types/_uintptr_t.h
spells2.o: /usr/include/sys/_types/___offsetof.h
spells2.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
spells2.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
spells2.o: /usr/include/libkern/i386/_OSByteOrder.h
spells2.o: /usr/include/sys/_types/_dev_t.h
spells2.o: /usr/include/sys/_types/_blkcnt_t.h
spells2.o: /usr/include/sys/_types/_blksize_t.h
spells2.o: /usr/include/sys/_types/_gid_t.h
spells2.o: /usr/include/sys/_types/_in_addr_t.h
spells2.o: /usr/include/sys/_types/_in_port_t.h
spells2.o: /usr/include/sys/_types/_ino_t.h
spells2.o: /usr/include/sys/_types/_ino64_t.h
spells2.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
spells2.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
spells2.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
spells2.o: /usr/include/sys/_types/_clock_t.h
spells2.o: /usr/include/sys/_types/_time_t.h
spells2.o: /usr/include/sys/_types/_useconds_t.h
spells2.o: /usr/include/sys/_types/_suseconds_t.h
spells2.o: /usr/include/sys/_types/_fd_def.h
spells2.o: /usr/include/sys/_types/_fd_setsize.h
spells2.o: /usr/include/sys/_types/_fd_set.h
spells2.o: /usr/include/sys/_types/_fd_clr.h
spells2.o: /usr/include/sys/_types/_fd_zero.h
spells2.o: /usr/include/sys/_types/_fd_isset.h
spells2.o: /usr/include/sys/_types/_fd_copy.h
spells2.o: /usr/include/sys/_types/_pthread_attr_t.h
spells2.o: /usr/include/sys/_types/_pthread_cond_t.h
spells2.o: /usr/include/sys/_types/_pthread_condattr_t.h
spells2.o: /usr/include/sys/_types/_pthread_mutex_t.h
spells2.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
spells2.o: /usr/include/sys/_types/_pthread_once_t.h
spells2.o: /usr/include/sys/_types/_pthread_rwlock_t.h
spells2.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
spells2.o: /usr/include/sys/_types/_pthread_t.h
spells2.o: /usr/include/sys/_types/_pthread_key_t.h
spells2.o: /usr/include/sys/_types/_fsblkcnt_t.h
spells2.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
spells2.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
spells2.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h
spells2.o: parser.h
spell_parser.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
spell_parser.o: /usr/include/sys/_symbol_aliasing.h
spell_parser.o: /usr/include/sys/_posix_availability.h
spell_parser.o: /usr/include/Availability.h
spell_parser.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
spell_parser.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
spell_parser.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
spell_parser.o: /usr/include/sys/_types/_size_t.h
spell_parser.o: /usr/include/sys/_types/_null.h
spell_parser.o: /usr/include/sys/_types/_off_t.h
spell_parser.o: /usr/include/sys/_types/_ssize_t.h
spell_parser.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
spell_parser.o: /usr/include/assert.h protos.h structs.h
spell_parser.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
spell_parser.o: /usr/include/machine/types.h /usr/include/i386/types.h
spell_parser.o: /usr/include/sys/_types/_int8_t.h
spell_parser.o: /usr/include/sys/_types/_int16_t.h
spell_parser.o: /usr/include/sys/_types/_int32_t.h
spell_parser.o: /usr/include/sys/_types/_int64_t.h
spell_parser.o: /usr/include/sys/_types/_intptr_t.h
spell_parser.o: /usr/include/sys/_types/_uintptr_t.h
spell_parser.o: /usr/include/sys/_types/___offsetof.h
spell_parser.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
spell_parser.o: /usr/include/sys/_endian.h
spell_parser.o: /usr/include/libkern/_OSByteOrder.h
spell_parser.o: /usr/include/libkern/i386/_OSByteOrder.h
spell_parser.o: /usr/include/sys/_types/_dev_t.h
spell_parser.o: /usr/include/sys/_types/_blkcnt_t.h
spell_parser.o: /usr/include/sys/_types/_blksize_t.h
spell_parser.o: /usr/include/sys/_types/_gid_t.h
spell_parser.o: /usr/include/sys/_types/_in_addr_t.h
spell_parser.o: /usr/include/sys/_types/_in_port_t.h
spell_parser.o: /usr/include/sys/_types/_ino_t.h
spell_parser.o: /usr/include/sys/_types/_ino64_t.h
spell_parser.o: /usr/include/sys/_types/_key_t.h
spell_parser.o: /usr/include/sys/_types/_mode_t.h
spell_parser.o: /usr/include/sys/_types/_nlink_t.h
spell_parser.o: /usr/include/sys/_types/_id_t.h
spell_parser.o: /usr/include/sys/_types/_pid_t.h
spell_parser.o: /usr/include/sys/_types/_uid_t.h
spell_parser.o: /usr/include/sys/_types/_clock_t.h
spell_parser.o: /usr/include/sys/_types/_time_t.h
spell_parser.o: /usr/include/sys/_types/_useconds_t.h
spell_parser.o: /usr/include/sys/_types/_suseconds_t.h
spell_parser.o: /usr/include/sys/_types/_rsize_t.h
spell_parser.o: /usr/include/sys/_types/_errno_t.h
spell_parser.o: /usr/include/sys/_types/_fd_def.h
spell_parser.o: /usr/include/sys/_types/_fd_setsize.h
spell_parser.o: /usr/include/sys/_types/_fd_set.h
spell_parser.o: /usr/include/sys/_types/_fd_clr.h
spell_parser.o: /usr/include/sys/_types/_fd_zero.h
spell_parser.o: /usr/include/sys/_types/_fd_isset.h
spell_parser.o: /usr/include/sys/_types/_fd_copy.h
spell_parser.o: /usr/include/sys/_types/_pthread_attr_t.h
spell_parser.o: /usr/include/sys/_types/_pthread_cond_t.h
spell_parser.o: /usr/include/sys/_types/_pthread_condattr_t.h
spell_parser.o: /usr/include/sys/_types/_pthread_mutex_t.h
spell_parser.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
spell_parser.o: /usr/include/sys/_types/_pthread_once_t.h
spell_parser.o: /usr/include/sys/_types/_pthread_rwlock_t.h
spell_parser.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
spell_parser.o: /usr/include/sys/_types/_pthread_t.h
spell_parser.o: /usr/include/sys/_types/_pthread_key_t.h
spell_parser.o: /usr/include/sys/_types/_fsblkcnt_t.h
spell_parser.o: /usr/include/sys/_types/_fsfilcnt_t.h area.h comm.h db.h
spell_parser.o: handler.h hash.h heap.h interpreter.h limits.h poly.h race.h
spell_parser.o: script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
reception.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
reception.o: /usr/include/sys/_symbol_aliasing.h
reception.o: /usr/include/sys/_posix_availability.h
reception.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
reception.o: /usr/include/_types.h /usr/include/sys/_types.h
reception.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
reception.o: /usr/include/sys/_types/_va_list.h
reception.o: /usr/include/sys/_types/_size_t.h
reception.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_off_t.h
reception.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
reception.o: /usr/include/secure/_common.h /usr/include/sys/time.h
reception.o: /usr/include/sys/_types/_fd_def.h
reception.o: /usr/include/sys/_types/_timespec.h
reception.o: /usr/include/sys/_types/_timeval.h
reception.o: /usr/include/sys/_types/_time_t.h
reception.o: /usr/include/sys/_types/_suseconds_t.h
reception.o: /usr/include/sys/_types/_fd_setsize.h
reception.o: /usr/include/sys/_types/_fd_set.h
reception.o: /usr/include/sys/_types/_fd_clr.h
reception.o: /usr/include/sys/_types/_fd_isset.h
reception.o: /usr/include/sys/_types/_fd_zero.h
reception.o: /usr/include/sys/_types/_fd_copy.h /usr/include/time.h
reception.o: /usr/include/_structs.h /usr/include/sys/_structs.h
reception.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_select.h
reception.o: protos.h structs.h /usr/include/sys/types.h
reception.o: /usr/include/sys/appleapiopts.h /usr/include/machine/types.h
reception.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
reception.o: /usr/include/sys/_types/_int16_t.h
reception.o: /usr/include/sys/_types/_int32_t.h
reception.o: /usr/include/sys/_types/_int64_t.h
reception.o: /usr/include/sys/_types/_intptr_t.h
reception.o: /usr/include/sys/_types/_uintptr_t.h
reception.o: /usr/include/sys/_types/___offsetof.h
reception.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
reception.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
reception.o: /usr/include/libkern/i386/_OSByteOrder.h
reception.o: /usr/include/sys/_types/_dev_t.h
reception.o: /usr/include/sys/_types/_blkcnt_t.h
reception.o: /usr/include/sys/_types/_blksize_t.h
reception.o: /usr/include/sys/_types/_gid_t.h
reception.o: /usr/include/sys/_types/_in_addr_t.h
reception.o: /usr/include/sys/_types/_in_port_t.h
reception.o: /usr/include/sys/_types/_ino_t.h
reception.o: /usr/include/sys/_types/_ino64_t.h
reception.o: /usr/include/sys/_types/_key_t.h
reception.o: /usr/include/sys/_types/_mode_t.h
reception.o: /usr/include/sys/_types/_nlink_t.h
reception.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/_types/_pid_t.h
reception.o: /usr/include/sys/_types/_uid_t.h
reception.o: /usr/include/sys/_types/_useconds_t.h
reception.o: /usr/include/sys/_types/_rsize_t.h
reception.o: /usr/include/sys/_types/_errno_t.h
reception.o: /usr/include/sys/_types/_pthread_attr_t.h
reception.o: /usr/include/sys/_types/_pthread_cond_t.h
reception.o: /usr/include/sys/_types/_pthread_condattr_t.h
reception.o: /usr/include/sys/_types/_pthread_mutex_t.h
reception.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
reception.o: /usr/include/sys/_types/_pthread_once_t.h
reception.o: /usr/include/sys/_types/_pthread_rwlock_t.h
reception.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
reception.o: /usr/include/sys/_types/_pthread_t.h
reception.o: /usr/include/sys/_types/_pthread_key_t.h
reception.o: /usr/include/sys/_types/_fsblkcnt_t.h
reception.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
reception.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h
reception.o: limits.h poly.h race.h script.h spells.h trap.h utils.h vt100c.h
reception.o: wizlist.h parser.h
constants.o: structs.h /usr/include/sys/types.h
constants.o: /usr/include/sys/appleapiopts.h /usr/include/sys/cdefs.h
constants.o: /usr/include/sys/_symbol_aliasing.h
constants.o: /usr/include/sys/_posix_availability.h
constants.o: /usr/include/machine/types.h /usr/include/i386/types.h
constants.o: /usr/include/i386/_types.h /usr/include/sys/_types/_int8_t.h
constants.o: /usr/include/sys/_types/_int16_t.h
constants.o: /usr/include/sys/_types/_int32_t.h
constants.o: /usr/include/sys/_types/_int64_t.h
constants.o: /usr/include/sys/_types/_intptr_t.h
constants.o: /usr/include/sys/_types/_uintptr_t.h
constants.o: /usr/include/sys/_types/___offsetof.h /usr/include/sys/_types.h
constants.o: /usr/include/machine/_types.h /usr/include/machine/endian.h
constants.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
constants.o: /usr/include/libkern/_OSByteOrder.h
constants.o: /usr/include/libkern/i386/_OSByteOrder.h
constants.o: /usr/include/sys/_types/_dev_t.h
constants.o: /usr/include/sys/_types/_blkcnt_t.h
constants.o: /usr/include/sys/_types/_blksize_t.h
constants.o: /usr/include/sys/_types/_gid_t.h
constants.o: /usr/include/sys/_types/_in_addr_t.h
constants.o: /usr/include/sys/_types/_in_port_t.h
constants.o: /usr/include/sys/_types/_ino_t.h
constants.o: /usr/include/sys/_types/_ino64_t.h
constants.o: /usr/include/sys/_types/_key_t.h
constants.o: /usr/include/sys/_types/_mode_t.h
constants.o: /usr/include/sys/_types/_nlink_t.h
constants.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/_types/_pid_t.h
constants.o: /usr/include/sys/_types/_off_t.h
constants.o: /usr/include/sys/_types/_uid_t.h
constants.o: /usr/include/sys/_types/_clock_t.h
constants.o: /usr/include/sys/_types/_size_t.h
constants.o: /usr/include/sys/_types/_ssize_t.h
constants.o: /usr/include/sys/_types/_time_t.h
constants.o: /usr/include/sys/_types/_useconds_t.h
constants.o: /usr/include/sys/_types/_suseconds_t.h
constants.o: /usr/include/sys/_types/_rsize_t.h
constants.o: /usr/include/sys/_types/_errno_t.h
constants.o: /usr/include/sys/_types/_fd_def.h
constants.o: /usr/include/sys/_types/_fd_setsize.h
constants.o: /usr/include/sys/_types/_fd_set.h
constants.o: /usr/include/sys/_types/_fd_clr.h
constants.o: /usr/include/sys/_types/_fd_zero.h
constants.o: /usr/include/sys/_types/_fd_isset.h
constants.o: /usr/include/sys/_types/_fd_copy.h
constants.o: /usr/include/sys/_types/_pthread_attr_t.h
constants.o: /usr/include/sys/_types/_pthread_cond_t.h
constants.o: /usr/include/sys/_types/_pthread_condattr_t.h
constants.o: /usr/include/sys/_types/_pthread_mutex_t.h
constants.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
constants.o: /usr/include/sys/_types/_pthread_once_t.h
constants.o: /usr/include/sys/_types/_pthread_rwlock_t.h
constants.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
constants.o: /usr/include/sys/_types/_pthread_t.h
constants.o: /usr/include/sys/_types/_pthread_key_t.h
constants.o: /usr/include/sys/_types/_fsblkcnt_t.h
constants.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
constants.o: limits.h trap.h race.h
spec_procs.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
spec_procs.o: /usr/include/sys/_symbol_aliasing.h
spec_procs.o: /usr/include/sys/_posix_availability.h
spec_procs.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
spec_procs.o: /usr/include/_types.h /usr/include/sys/_types.h
spec_procs.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
spec_procs.o: /usr/include/sys/_types/_va_list.h
spec_procs.o: /usr/include/sys/_types/_size_t.h
spec_procs.o: /usr/include/sys/_types/_null.h
spec_procs.o: /usr/include/sys/_types/_off_t.h
spec_procs.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
spec_procs.o: /usr/include/secure/_common.h /usr/include/string.h
spec_procs.o: /usr/include/sys/_types/_rsize_t.h
spec_procs.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
spec_procs.o: /usr/include/secure/_string.h /usr/include/ctype.h
spec_procs.o: /usr/include/runetype.h /usr/include/sys/_types/_ct_rune_t.h
spec_procs.o: /usr/include/sys/_types/_rune_t.h
spec_procs.o: /usr/include/sys/_types/_wchar_t.h
spec_procs.o: /usr/include/sys/_types/_wint_t.h protos.h structs.h
spec_procs.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
spec_procs.o: /usr/include/machine/types.h /usr/include/i386/types.h
spec_procs.o: /usr/include/sys/_types/_int8_t.h
spec_procs.o: /usr/include/sys/_types/_int16_t.h
spec_procs.o: /usr/include/sys/_types/_int32_t.h
spec_procs.o: /usr/include/sys/_types/_int64_t.h
spec_procs.o: /usr/include/sys/_types/_intptr_t.h
spec_procs.o: /usr/include/sys/_types/_uintptr_t.h
spec_procs.o: /usr/include/sys/_types/___offsetof.h
spec_procs.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
spec_procs.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
spec_procs.o: /usr/include/libkern/i386/_OSByteOrder.h
spec_procs.o: /usr/include/sys/_types/_dev_t.h
spec_procs.o: /usr/include/sys/_types/_blkcnt_t.h
spec_procs.o: /usr/include/sys/_types/_blksize_t.h
spec_procs.o: /usr/include/sys/_types/_gid_t.h
spec_procs.o: /usr/include/sys/_types/_in_addr_t.h
spec_procs.o: /usr/include/sys/_types/_in_port_t.h
spec_procs.o: /usr/include/sys/_types/_ino_t.h
spec_procs.o: /usr/include/sys/_types/_ino64_t.h
spec_procs.o: /usr/include/sys/_types/_key_t.h
spec_procs.o: /usr/include/sys/_types/_mode_t.h
spec_procs.o: /usr/include/sys/_types/_nlink_t.h
spec_procs.o: /usr/include/sys/_types/_id_t.h
spec_procs.o: /usr/include/sys/_types/_pid_t.h
spec_procs.o: /usr/include/sys/_types/_uid_t.h
spec_procs.o: /usr/include/sys/_types/_clock_t.h
spec_procs.o: /usr/include/sys/_types/_time_t.h
spec_procs.o: /usr/include/sys/_types/_useconds_t.h
spec_procs.o: /usr/include/sys/_types/_suseconds_t.h
spec_procs.o: /usr/include/sys/_types/_fd_def.h
spec_procs.o: /usr/include/sys/_types/_fd_setsize.h
spec_procs.o: /usr/include/sys/_types/_fd_set.h
spec_procs.o: /usr/include/sys/_types/_fd_clr.h
spec_procs.o: /usr/include/sys/_types/_fd_zero.h
spec_procs.o: /usr/include/sys/_types/_fd_isset.h
spec_procs.o: /usr/include/sys/_types/_fd_copy.h
spec_procs.o: /usr/include/sys/_types/_pthread_attr_t.h
spec_procs.o: /usr/include/sys/_types/_pthread_cond_t.h
spec_procs.o: /usr/include/sys/_types/_pthread_condattr_t.h
spec_procs.o: /usr/include/sys/_types/_pthread_mutex_t.h
spec_procs.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
spec_procs.o: /usr/include/sys/_types/_pthread_once_t.h
spec_procs.o: /usr/include/sys/_types/_pthread_rwlock_t.h
spec_procs.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
spec_procs.o: /usr/include/sys/_types/_pthread_t.h
spec_procs.o: /usr/include/sys/_types/_pthread_key_t.h
spec_procs.o: /usr/include/sys/_types/_fsblkcnt_t.h
spec_procs.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
spec_procs.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h
spec_procs.o: limits.h poly.h race.h script.h spells.h trap.h utils.h
spec_procs.o: vt100c.h wizlist.h parser.h
signals.o: /usr/include/signal.h /usr/include/sys/cdefs.h
signals.o: /usr/include/sys/_symbol_aliasing.h
signals.o: /usr/include/sys/_posix_availability.h /usr/include/_types.h
signals.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
signals.o: /usr/include/i386/_types.h /usr/include/sys/signal.h
signals.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
signals.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
signals.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
signals.o: /usr/include/sys/_types/_sigaltstack.h
signals.o: /usr/include/sys/_types/_ucontext.h
signals.o: /usr/include/sys/_types/_pid_t.h
signals.o: /usr/include/sys/_types/_pthread_attr_t.h
signals.o: /usr/include/sys/_types/_sigset_t.h
signals.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_uid_t.h
signals.o: /usr/include/sys/_types/_pthread_t.h /usr/include/stdio.h
signals.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
signals.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/_types/_null.h
signals.o: /usr/include/sys/_types/_off_t.h
signals.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
signals.o: /usr/include/secure/_common.h /usr/include/sys/time.h
signals.o: /usr/include/sys/_types/_fd_def.h
signals.o: /usr/include/sys/_types/_timespec.h
signals.o: /usr/include/sys/_types/_timeval.h
signals.o: /usr/include/sys/_types/_time_t.h
signals.o: /usr/include/sys/_types/_suseconds_t.h
signals.o: /usr/include/sys/_types/_fd_setsize.h
signals.o: /usr/include/sys/_types/_fd_set.h
signals.o: /usr/include/sys/_types/_fd_clr.h
signals.o: /usr/include/sys/_types/_fd_isset.h
signals.o: /usr/include/sys/_types/_fd_zero.h
signals.o: /usr/include/sys/_types/_fd_copy.h /usr/include/time.h
signals.o: /usr/include/_structs.h /usr/include/sys/_structs.h
signals.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_select.h
signals.o: protos.h structs.h /usr/include/sys/types.h
signals.o: /usr/include/machine/types.h /usr/include/i386/types.h
signals.o: /usr/include/sys/_types/_int8_t.h
signals.o: /usr/include/sys/_types/_int16_t.h
signals.o: /usr/include/sys/_types/_int32_t.h
signals.o: /usr/include/sys/_types/_int64_t.h
signals.o: /usr/include/sys/_types/_intptr_t.h
signals.o: /usr/include/sys/_types/_uintptr_t.h
signals.o: /usr/include/sys/_types/___offsetof.h
signals.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
signals.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
signals.o: /usr/include/libkern/i386/_OSByteOrder.h
signals.o: /usr/include/sys/_types/_dev_t.h
signals.o: /usr/include/sys/_types/_blkcnt_t.h
signals.o: /usr/include/sys/_types/_blksize_t.h
signals.o: /usr/include/sys/_types/_gid_t.h
signals.o: /usr/include/sys/_types/_in_addr_t.h
signals.o: /usr/include/sys/_types/_in_port_t.h
signals.o: /usr/include/sys/_types/_ino_t.h
signals.o: /usr/include/sys/_types/_ino64_t.h
signals.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
signals.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
signals.o: /usr/include/sys/_types/_useconds_t.h
signals.o: /usr/include/sys/_types/_rsize_t.h
signals.o: /usr/include/sys/_types/_errno_t.h
signals.o: /usr/include/sys/_types/_pthread_cond_t.h
signals.o: /usr/include/sys/_types/_pthread_condattr_t.h
signals.o: /usr/include/sys/_types/_pthread_mutex_t.h
signals.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
signals.o: /usr/include/sys/_types/_pthread_once_t.h
signals.o: /usr/include/sys/_types/_pthread_rwlock_t.h
signals.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
signals.o: /usr/include/sys/_types/_pthread_key_t.h
signals.o: /usr/include/sys/_types/_fsblkcnt_t.h
signals.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
signals.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
signals.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h
signals.o: parser.h
board.o: /usr/include/string.h /usr/include/_types.h
board.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
board.o: /usr/include/sys/_symbol_aliasing.h
board.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
board.o: /usr/include/i386/_types.h /usr/include/Availability.h
board.o: /usr/include/AvailabilityInternal.h
board.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
board.o: /usr/include/sys/_types/_rsize_t.h
board.o: /usr/include/sys/_types/_errno_t.h
board.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
board.o: /usr/include/secure/_string.h /usr/include/secure/_common.h
board.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
board.o: /usr/include/sys/_types/_off_t.h /usr/include/secure/_stdio.h
board.o: /usr/include/ctype.h /usr/include/runetype.h
board.o: /usr/include/sys/_types/_ct_rune_t.h
board.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
board.o: /usr/include/sys/_types/_wint_t.h protos.h structs.h
board.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
board.o: /usr/include/machine/types.h /usr/include/i386/types.h
board.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
board.o: /usr/include/sys/_types/_int32_t.h
board.o: /usr/include/sys/_types/_int64_t.h
board.o: /usr/include/sys/_types/_intptr_t.h
board.o: /usr/include/sys/_types/_uintptr_t.h
board.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
board.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
board.o: /usr/include/libkern/_OSByteOrder.h
board.o: /usr/include/libkern/i386/_OSByteOrder.h
board.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_blkcnt_t.h
board.o: /usr/include/sys/_types/_blksize_t.h
board.o: /usr/include/sys/_types/_gid_t.h
board.o: /usr/include/sys/_types/_in_addr_t.h
board.o: /usr/include/sys/_types/_in_port_t.h
board.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
board.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
board.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
board.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
board.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h
board.o: /usr/include/sys/_types/_useconds_t.h
board.o: /usr/include/sys/_types/_suseconds_t.h
board.o: /usr/include/sys/_types/_fd_def.h
board.o: /usr/include/sys/_types/_fd_setsize.h
board.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
board.o: /usr/include/sys/_types/_fd_zero.h
board.o: /usr/include/sys/_types/_fd_isset.h
board.o: /usr/include/sys/_types/_fd_copy.h
board.o: /usr/include/sys/_types/_pthread_attr_t.h
board.o: /usr/include/sys/_types/_pthread_cond_t.h
board.o: /usr/include/sys/_types/_pthread_condattr_t.h
board.o: /usr/include/sys/_types/_pthread_mutex_t.h
board.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
board.o: /usr/include/sys/_types/_pthread_once_t.h
board.o: /usr/include/sys/_types/_pthread_rwlock_t.h
board.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
board.o: /usr/include/sys/_types/_pthread_t.h
board.o: /usr/include/sys/_types/_pthread_key_t.h
board.o: /usr/include/sys/_types/_fsblkcnt_t.h
board.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
board.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
board.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
magic.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
magic.o: /usr/include/sys/_symbol_aliasing.h
magic.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
magic.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
magic.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
magic.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
magic.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
magic.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
magic.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
magic.o: /usr/include/assert.h protos.h structs.h /usr/include/sys/types.h
magic.o: /usr/include/sys/appleapiopts.h /usr/include/machine/types.h
magic.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
magic.o: /usr/include/sys/_types/_int16_t.h
magic.o: /usr/include/sys/_types/_int32_t.h
magic.o: /usr/include/sys/_types/_int64_t.h
magic.o: /usr/include/sys/_types/_intptr_t.h
magic.o: /usr/include/sys/_types/_uintptr_t.h
magic.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
magic.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
magic.o: /usr/include/libkern/_OSByteOrder.h
magic.o: /usr/include/libkern/i386/_OSByteOrder.h
magic.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_blkcnt_t.h
magic.o: /usr/include/sys/_types/_blksize_t.h
magic.o: /usr/include/sys/_types/_gid_t.h
magic.o: /usr/include/sys/_types/_in_addr_t.h
magic.o: /usr/include/sys/_types/_in_port_t.h
magic.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
magic.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
magic.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
magic.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
magic.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h
magic.o: /usr/include/sys/_types/_useconds_t.h
magic.o: /usr/include/sys/_types/_suseconds_t.h
magic.o: /usr/include/sys/_types/_rsize_t.h
magic.o: /usr/include/sys/_types/_errno_t.h /usr/include/sys/_types/_fd_def.h
magic.o: /usr/include/sys/_types/_fd_setsize.h
magic.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
magic.o: /usr/include/sys/_types/_fd_zero.h
magic.o: /usr/include/sys/_types/_fd_isset.h
magic.o: /usr/include/sys/_types/_fd_copy.h
magic.o: /usr/include/sys/_types/_pthread_attr_t.h
magic.o: /usr/include/sys/_types/_pthread_cond_t.h
magic.o: /usr/include/sys/_types/_pthread_condattr_t.h
magic.o: /usr/include/sys/_types/_pthread_mutex_t.h
magic.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
magic.o: /usr/include/sys/_types/_pthread_once_t.h
magic.o: /usr/include/sys/_types/_pthread_rwlock_t.h
magic.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
magic.o: /usr/include/sys/_types/_pthread_t.h
magic.o: /usr/include/sys/_types/_pthread_key_t.h
magic.o: /usr/include/sys/_types/_fsblkcnt_t.h
magic.o: /usr/include/sys/_types/_fsfilcnt_t.h area.h comm.h db.h handler.h
magic.o: hash.h heap.h interpreter.h limits.h poly.h race.h script.h spells.h
magic.o: trap.h utils.h vt100c.h wizlist.h parser.h
magic2.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
magic2.o: /usr/include/sys/_symbol_aliasing.h
magic2.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
magic2.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
magic2.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
magic2.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
magic2.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
magic2.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
magic2.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
magic2.o: /usr/include/assert.h protos.h structs.h /usr/include/sys/types.h
magic2.o: /usr/include/sys/appleapiopts.h /usr/include/machine/types.h
magic2.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
magic2.o: /usr/include/sys/_types/_int16_t.h
magic2.o: /usr/include/sys/_types/_int32_t.h
magic2.o: /usr/include/sys/_types/_int64_t.h
magic2.o: /usr/include/sys/_types/_intptr_t.h
magic2.o: /usr/include/sys/_types/_uintptr_t.h
magic2.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
magic2.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
magic2.o: /usr/include/libkern/_OSByteOrder.h
magic2.o: /usr/include/libkern/i386/_OSByteOrder.h
magic2.o: /usr/include/sys/_types/_dev_t.h
magic2.o: /usr/include/sys/_types/_blkcnt_t.h
magic2.o: /usr/include/sys/_types/_blksize_t.h
magic2.o: /usr/include/sys/_types/_gid_t.h
magic2.o: /usr/include/sys/_types/_in_addr_t.h
magic2.o: /usr/include/sys/_types/_in_port_t.h
magic2.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
magic2.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
magic2.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
magic2.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
magic2.o: /usr/include/sys/_types/_clock_t.h
magic2.o: /usr/include/sys/_types/_time_t.h
magic2.o: /usr/include/sys/_types/_useconds_t.h
magic2.o: /usr/include/sys/_types/_suseconds_t.h
magic2.o: /usr/include/sys/_types/_rsize_t.h
magic2.o: /usr/include/sys/_types/_errno_t.h
magic2.o: /usr/include/sys/_types/_fd_def.h
magic2.o: /usr/include/sys/_types/_fd_setsize.h
magic2.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
magic2.o: /usr/include/sys/_types/_fd_zero.h
magic2.o: /usr/include/sys/_types/_fd_isset.h
magic2.o: /usr/include/sys/_types/_fd_copy.h
magic2.o: /usr/include/sys/_types/_pthread_attr_t.h
magic2.o: /usr/include/sys/_types/_pthread_cond_t.h
magic2.o: /usr/include/sys/_types/_pthread_condattr_t.h
magic2.o: /usr/include/sys/_types/_pthread_mutex_t.h
magic2.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
magic2.o: /usr/include/sys/_types/_pthread_once_t.h
magic2.o: /usr/include/sys/_types/_pthread_rwlock_t.h
magic2.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
magic2.o: /usr/include/sys/_types/_pthread_t.h
magic2.o: /usr/include/sys/_types/_pthread_key_t.h
magic2.o: /usr/include/sys/_types/_fsblkcnt_t.h
magic2.o: /usr/include/sys/_types/_fsfilcnt_t.h area.h comm.h db.h handler.h
magic2.o: hash.h heap.h interpreter.h limits.h poly.h race.h script.h
magic2.o: spells.h trap.h utils.h vt100c.h wizlist.h parser.h
skills.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
skills.o: /usr/include/sys/_symbol_aliasing.h
skills.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
skills.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
skills.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
skills.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
skills.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
skills.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
skills.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h protos.h
skills.o: structs.h /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
skills.o: /usr/include/machine/types.h /usr/include/i386/types.h
skills.o: /usr/include/sys/_types/_int8_t.h
skills.o: /usr/include/sys/_types/_int16_t.h
skills.o: /usr/include/sys/_types/_int32_t.h
skills.o: /usr/include/sys/_types/_int64_t.h
skills.o: /usr/include/sys/_types/_intptr_t.h
skills.o: /usr/include/sys/_types/_uintptr_t.h
skills.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
skills.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
skills.o: /usr/include/libkern/_OSByteOrder.h
skills.o: /usr/include/libkern/i386/_OSByteOrder.h
skills.o: /usr/include/sys/_types/_dev_t.h
skills.o: /usr/include/sys/_types/_blkcnt_t.h
skills.o: /usr/include/sys/_types/_blksize_t.h
skills.o: /usr/include/sys/_types/_gid_t.h
skills.o: /usr/include/sys/_types/_in_addr_t.h
skills.o: /usr/include/sys/_types/_in_port_t.h
skills.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
skills.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
skills.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
skills.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
skills.o: /usr/include/sys/_types/_clock_t.h
skills.o: /usr/include/sys/_types/_time_t.h
skills.o: /usr/include/sys/_types/_useconds_t.h
skills.o: /usr/include/sys/_types/_suseconds_t.h
skills.o: /usr/include/sys/_types/_rsize_t.h
skills.o: /usr/include/sys/_types/_errno_t.h
skills.o: /usr/include/sys/_types/_fd_def.h
skills.o: /usr/include/sys/_types/_fd_setsize.h
skills.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
skills.o: /usr/include/sys/_types/_fd_zero.h
skills.o: /usr/include/sys/_types/_fd_isset.h
skills.o: /usr/include/sys/_types/_fd_copy.h
skills.o: /usr/include/sys/_types/_pthread_attr_t.h
skills.o: /usr/include/sys/_types/_pthread_cond_t.h
skills.o: /usr/include/sys/_types/_pthread_condattr_t.h
skills.o: /usr/include/sys/_types/_pthread_mutex_t.h
skills.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
skills.o: /usr/include/sys/_types/_pthread_once_t.h
skills.o: /usr/include/sys/_types/_pthread_rwlock_t.h
skills.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
skills.o: /usr/include/sys/_types/_pthread_t.h
skills.o: /usr/include/sys/_types/_pthread_key_t.h
skills.o: /usr/include/sys/_types/_fsblkcnt_t.h
skills.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
skills.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
skills.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
Opinion.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
Opinion.o: /usr/include/sys/_symbol_aliasing.h
Opinion.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
Opinion.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
Opinion.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
Opinion.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
Opinion.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
Opinion.o: /usr/include/sys/_types/_off_t.h
Opinion.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
Opinion.o: /usr/include/secure/_common.h /usr/include/string.h
Opinion.o: /usr/include/sys/_types/_rsize_t.h
Opinion.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
Opinion.o: /usr/include/secure/_string.h /usr/include/ctype.h
Opinion.o: /usr/include/runetype.h /usr/include/sys/_types/_ct_rune_t.h
Opinion.o: /usr/include/sys/_types/_rune_t.h
Opinion.o: /usr/include/sys/_types/_wchar_t.h
Opinion.o: /usr/include/sys/_types/_wint_t.h /usr/include/time.h
Opinion.o: /usr/include/_structs.h /usr/include/sys/_structs.h
Opinion.o: /usr/include/sys/_types/_timespec.h
Opinion.o: /usr/include/sys/_types/_clock_t.h
Opinion.o: /usr/include/sys/_types/_time_t.h protos.h structs.h
Opinion.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
Opinion.o: /usr/include/machine/types.h /usr/include/i386/types.h
Opinion.o: /usr/include/sys/_types/_int8_t.h
Opinion.o: /usr/include/sys/_types/_int16_t.h
Opinion.o: /usr/include/sys/_types/_int32_t.h
Opinion.o: /usr/include/sys/_types/_int64_t.h
Opinion.o: /usr/include/sys/_types/_intptr_t.h
Opinion.o: /usr/include/sys/_types/_uintptr_t.h
Opinion.o: /usr/include/sys/_types/___offsetof.h
Opinion.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
Opinion.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
Opinion.o: /usr/include/libkern/i386/_OSByteOrder.h
Opinion.o: /usr/include/sys/_types/_dev_t.h
Opinion.o: /usr/include/sys/_types/_blkcnt_t.h
Opinion.o: /usr/include/sys/_types/_blksize_t.h
Opinion.o: /usr/include/sys/_types/_gid_t.h
Opinion.o: /usr/include/sys/_types/_in_addr_t.h
Opinion.o: /usr/include/sys/_types/_in_port_t.h
Opinion.o: /usr/include/sys/_types/_ino_t.h
Opinion.o: /usr/include/sys/_types/_ino64_t.h
Opinion.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
Opinion.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
Opinion.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
Opinion.o: /usr/include/sys/_types/_useconds_t.h
Opinion.o: /usr/include/sys/_types/_suseconds_t.h
Opinion.o: /usr/include/sys/_types/_fd_def.h
Opinion.o: /usr/include/sys/_types/_fd_setsize.h
Opinion.o: /usr/include/sys/_types/_fd_set.h
Opinion.o: /usr/include/sys/_types/_fd_clr.h
Opinion.o: /usr/include/sys/_types/_fd_zero.h
Opinion.o: /usr/include/sys/_types/_fd_isset.h
Opinion.o: /usr/include/sys/_types/_fd_copy.h
Opinion.o: /usr/include/sys/_types/_pthread_attr_t.h
Opinion.o: /usr/include/sys/_types/_pthread_cond_t.h
Opinion.o: /usr/include/sys/_types/_pthread_condattr_t.h
Opinion.o: /usr/include/sys/_types/_pthread_mutex_t.h
Opinion.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
Opinion.o: /usr/include/sys/_types/_pthread_once_t.h
Opinion.o: /usr/include/sys/_types/_pthread_rwlock_t.h
Opinion.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
Opinion.o: /usr/include/sys/_types/_pthread_t.h
Opinion.o: /usr/include/sys/_types/_pthread_key_t.h
Opinion.o: /usr/include/sys/_types/_fsblkcnt_t.h
Opinion.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
Opinion.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
Opinion.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h
Opinion.o: parser.h
Trap.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
Trap.o: /usr/include/sys/_symbol_aliasing.h
Trap.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
Trap.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
Trap.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
Trap.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
Trap.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
Trap.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
Trap.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h protos.h
Trap.o: structs.h /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
Trap.o: /usr/include/machine/types.h /usr/include/i386/types.h
Trap.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
Trap.o: /usr/include/sys/_types/_int32_t.h /usr/include/sys/_types/_int64_t.h
Trap.o: /usr/include/sys/_types/_intptr_t.h
Trap.o: /usr/include/sys/_types/_uintptr_t.h
Trap.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
Trap.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
Trap.o: /usr/include/libkern/_OSByteOrder.h
Trap.o: /usr/include/libkern/i386/_OSByteOrder.h
Trap.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_blkcnt_t.h
Trap.o: /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h
Trap.o: /usr/include/sys/_types/_in_addr_t.h
Trap.o: /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h
Trap.o: /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h
Trap.o: /usr/include/sys/_types/_mode_t.h /usr/include/sys/_types/_nlink_t.h
Trap.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/_types/_pid_t.h
Trap.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_clock_t.h
Trap.o: /usr/include/sys/_types/_time_t.h
Trap.o: /usr/include/sys/_types/_useconds_t.h
Trap.o: /usr/include/sys/_types/_suseconds_t.h
Trap.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
Trap.o: /usr/include/sys/_types/_fd_def.h
Trap.o: /usr/include/sys/_types/_fd_setsize.h
Trap.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
Trap.o: /usr/include/sys/_types/_fd_zero.h
Trap.o: /usr/include/sys/_types/_fd_isset.h
Trap.o: /usr/include/sys/_types/_fd_copy.h
Trap.o: /usr/include/sys/_types/_pthread_attr_t.h
Trap.o: /usr/include/sys/_types/_pthread_cond_t.h
Trap.o: /usr/include/sys/_types/_pthread_condattr_t.h
Trap.o: /usr/include/sys/_types/_pthread_mutex_t.h
Trap.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
Trap.o: /usr/include/sys/_types/_pthread_once_t.h
Trap.o: /usr/include/sys/_types/_pthread_rwlock_t.h
Trap.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
Trap.o: /usr/include/sys/_types/_pthread_t.h
Trap.o: /usr/include/sys/_types/_pthread_key_t.h
Trap.o: /usr/include/sys/_types/_fsblkcnt_t.h
Trap.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
Trap.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
Trap.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
magicutils.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
magicutils.o: /usr/include/sys/_symbol_aliasing.h
magicutils.o: /usr/include/sys/_posix_availability.h
magicutils.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
magicutils.o: /usr/include/_types.h /usr/include/sys/_types.h
magicutils.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
magicutils.o: /usr/include/sys/_types/_va_list.h
magicutils.o: /usr/include/sys/_types/_size_t.h
magicutils.o: /usr/include/sys/_types/_null.h
magicutils.o: /usr/include/sys/_types/_off_t.h
magicutils.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
magicutils.o: /usr/include/secure/_common.h /usr/include/assert.h protos.h
magicutils.o: structs.h /usr/include/sys/types.h
magicutils.o: /usr/include/sys/appleapiopts.h /usr/include/machine/types.h
magicutils.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
magicutils.o: /usr/include/sys/_types/_int16_t.h
magicutils.o: /usr/include/sys/_types/_int32_t.h
magicutils.o: /usr/include/sys/_types/_int64_t.h
magicutils.o: /usr/include/sys/_types/_intptr_t.h
magicutils.o: /usr/include/sys/_types/_uintptr_t.h
magicutils.o: /usr/include/sys/_types/___offsetof.h
magicutils.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
magicutils.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
magicutils.o: /usr/include/libkern/i386/_OSByteOrder.h
magicutils.o: /usr/include/sys/_types/_dev_t.h
magicutils.o: /usr/include/sys/_types/_blkcnt_t.h
magicutils.o: /usr/include/sys/_types/_blksize_t.h
magicutils.o: /usr/include/sys/_types/_gid_t.h
magicutils.o: /usr/include/sys/_types/_in_addr_t.h
magicutils.o: /usr/include/sys/_types/_in_port_t.h
magicutils.o: /usr/include/sys/_types/_ino_t.h
magicutils.o: /usr/include/sys/_types/_ino64_t.h
magicutils.o: /usr/include/sys/_types/_key_t.h
magicutils.o: /usr/include/sys/_types/_mode_t.h
magicutils.o: /usr/include/sys/_types/_nlink_t.h
magicutils.o: /usr/include/sys/_types/_id_t.h
magicutils.o: /usr/include/sys/_types/_pid_t.h
magicutils.o: /usr/include/sys/_types/_uid_t.h
magicutils.o: /usr/include/sys/_types/_clock_t.h
magicutils.o: /usr/include/sys/_types/_time_t.h
magicutils.o: /usr/include/sys/_types/_useconds_t.h
magicutils.o: /usr/include/sys/_types/_suseconds_t.h
magicutils.o: /usr/include/sys/_types/_rsize_t.h
magicutils.o: /usr/include/sys/_types/_errno_t.h
magicutils.o: /usr/include/sys/_types/_fd_def.h
magicutils.o: /usr/include/sys/_types/_fd_setsize.h
magicutils.o: /usr/include/sys/_types/_fd_set.h
magicutils.o: /usr/include/sys/_types/_fd_clr.h
magicutils.o: /usr/include/sys/_types/_fd_zero.h
magicutils.o: /usr/include/sys/_types/_fd_isset.h
magicutils.o: /usr/include/sys/_types/_fd_copy.h
magicutils.o: /usr/include/sys/_types/_pthread_attr_t.h
magicutils.o: /usr/include/sys/_types/_pthread_cond_t.h
magicutils.o: /usr/include/sys/_types/_pthread_condattr_t.h
magicutils.o: /usr/include/sys/_types/_pthread_mutex_t.h
magicutils.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
magicutils.o: /usr/include/sys/_types/_pthread_once_t.h
magicutils.o: /usr/include/sys/_types/_pthread_rwlock_t.h
magicutils.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
magicutils.o: /usr/include/sys/_types/_pthread_t.h
magicutils.o: /usr/include/sys/_types/_pthread_key_t.h
magicutils.o: /usr/include/sys/_types/_fsblkcnt_t.h
magicutils.o: /usr/include/sys/_types/_fsfilcnt_t.h area.h comm.h db.h
magicutils.o: handler.h hash.h heap.h interpreter.h limits.h poly.h race.h
magicutils.o: script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
multiclass.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
multiclass.o: /usr/include/sys/_symbol_aliasing.h
multiclass.o: /usr/include/sys/_posix_availability.h
multiclass.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
multiclass.o: /usr/include/_types.h /usr/include/sys/_types.h
multiclass.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
multiclass.o: /usr/include/sys/_types/_va_list.h
multiclass.o: /usr/include/sys/_types/_size_t.h
multiclass.o: /usr/include/sys/_types/_null.h
multiclass.o: /usr/include/sys/_types/_off_t.h
multiclass.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
multiclass.o: /usr/include/secure/_common.h /usr/include/string.h
multiclass.o: /usr/include/sys/_types/_rsize_t.h
multiclass.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
multiclass.o: /usr/include/secure/_string.h protos.h structs.h
multiclass.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
multiclass.o: /usr/include/machine/types.h /usr/include/i386/types.h
multiclass.o: /usr/include/sys/_types/_int8_t.h
multiclass.o: /usr/include/sys/_types/_int16_t.h
multiclass.o: /usr/include/sys/_types/_int32_t.h
multiclass.o: /usr/include/sys/_types/_int64_t.h
multiclass.o: /usr/include/sys/_types/_intptr_t.h
multiclass.o: /usr/include/sys/_types/_uintptr_t.h
multiclass.o: /usr/include/sys/_types/___offsetof.h
multiclass.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
multiclass.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
multiclass.o: /usr/include/libkern/i386/_OSByteOrder.h
multiclass.o: /usr/include/sys/_types/_dev_t.h
multiclass.o: /usr/include/sys/_types/_blkcnt_t.h
multiclass.o: /usr/include/sys/_types/_blksize_t.h
multiclass.o: /usr/include/sys/_types/_gid_t.h
multiclass.o: /usr/include/sys/_types/_in_addr_t.h
multiclass.o: /usr/include/sys/_types/_in_port_t.h
multiclass.o: /usr/include/sys/_types/_ino_t.h
multiclass.o: /usr/include/sys/_types/_ino64_t.h
multiclass.o: /usr/include/sys/_types/_key_t.h
multiclass.o: /usr/include/sys/_types/_mode_t.h
multiclass.o: /usr/include/sys/_types/_nlink_t.h
multiclass.o: /usr/include/sys/_types/_id_t.h
multiclass.o: /usr/include/sys/_types/_pid_t.h
multiclass.o: /usr/include/sys/_types/_uid_t.h
multiclass.o: /usr/include/sys/_types/_clock_t.h
multiclass.o: /usr/include/sys/_types/_time_t.h
multiclass.o: /usr/include/sys/_types/_useconds_t.h
multiclass.o: /usr/include/sys/_types/_suseconds_t.h
multiclass.o: /usr/include/sys/_types/_fd_def.h
multiclass.o: /usr/include/sys/_types/_fd_setsize.h
multiclass.o: /usr/include/sys/_types/_fd_set.h
multiclass.o: /usr/include/sys/_types/_fd_clr.h
multiclass.o: /usr/include/sys/_types/_fd_zero.h
multiclass.o: /usr/include/sys/_types/_fd_isset.h
multiclass.o: /usr/include/sys/_types/_fd_copy.h
multiclass.o: /usr/include/sys/_types/_pthread_attr_t.h
multiclass.o: /usr/include/sys/_types/_pthread_cond_t.h
multiclass.o: /usr/include/sys/_types/_pthread_condattr_t.h
multiclass.o: /usr/include/sys/_types/_pthread_mutex_t.h
multiclass.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
multiclass.o: /usr/include/sys/_types/_pthread_once_t.h
multiclass.o: /usr/include/sys/_types/_pthread_rwlock_t.h
multiclass.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
multiclass.o: /usr/include/sys/_types/_pthread_t.h
multiclass.o: /usr/include/sys/_types/_pthread_key_t.h
multiclass.o: /usr/include/sys/_types/_fsblkcnt_t.h
multiclass.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
multiclass.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h
multiclass.o: limits.h poly.h race.h script.h spells.h trap.h utils.h
multiclass.o: vt100c.h wizlist.h parser.h
hash.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
hash.o: /usr/include/sys/_symbol_aliasing.h
hash.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
hash.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
hash.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
hash.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
hash.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
hash.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
hash.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h protos.h
hash.o: structs.h /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
hash.o: /usr/include/machine/types.h /usr/include/i386/types.h
hash.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
hash.o: /usr/include/sys/_types/_int32_t.h /usr/include/sys/_types/_int64_t.h
hash.o: /usr/include/sys/_types/_intptr_t.h
hash.o: /usr/include/sys/_types/_uintptr_t.h
hash.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
hash.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
hash.o: /usr/include/libkern/_OSByteOrder.h
hash.o: /usr/include/libkern/i386/_OSByteOrder.h
hash.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_blkcnt_t.h
hash.o: /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h
hash.o: /usr/include/sys/_types/_in_addr_t.h
hash.o: /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h
hash.o: /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h
hash.o: /usr/include/sys/_types/_mode_t.h /usr/include/sys/_types/_nlink_t.h
hash.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/_types/_pid_t.h
hash.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_clock_t.h
hash.o: /usr/include/sys/_types/_time_t.h
hash.o: /usr/include/sys/_types/_useconds_t.h
hash.o: /usr/include/sys/_types/_suseconds_t.h
hash.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
hash.o: /usr/include/sys/_types/_fd_def.h
hash.o: /usr/include/sys/_types/_fd_setsize.h
hash.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
hash.o: /usr/include/sys/_types/_fd_zero.h
hash.o: /usr/include/sys/_types/_fd_isset.h
hash.o: /usr/include/sys/_types/_fd_copy.h
hash.o: /usr/include/sys/_types/_pthread_attr_t.h
hash.o: /usr/include/sys/_types/_pthread_cond_t.h
hash.o: /usr/include/sys/_types/_pthread_condattr_t.h
hash.o: /usr/include/sys/_types/_pthread_mutex_t.h
hash.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
hash.o: /usr/include/sys/_types/_pthread_once_t.h
hash.o: /usr/include/sys/_types/_pthread_rwlock_t.h
hash.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
hash.o: /usr/include/sys/_types/_pthread_t.h
hash.o: /usr/include/sys/_types/_pthread_key_t.h
hash.o: /usr/include/sys/_types/_fsblkcnt_t.h
hash.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
hash.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
hash.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
Sound.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
Sound.o: /usr/include/sys/_symbol_aliasing.h
Sound.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
Sound.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
Sound.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
Sound.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
Sound.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
Sound.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
Sound.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
Sound.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
Sound.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
Sound.o: /usr/include/secure/_string.h protos.h structs.h
Sound.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
Sound.o: /usr/include/machine/types.h /usr/include/i386/types.h
Sound.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
Sound.o: /usr/include/sys/_types/_int32_t.h
Sound.o: /usr/include/sys/_types/_int64_t.h
Sound.o: /usr/include/sys/_types/_intptr_t.h
Sound.o: /usr/include/sys/_types/_uintptr_t.h
Sound.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
Sound.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
Sound.o: /usr/include/libkern/_OSByteOrder.h
Sound.o: /usr/include/libkern/i386/_OSByteOrder.h
Sound.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_blkcnt_t.h
Sound.o: /usr/include/sys/_types/_blksize_t.h
Sound.o: /usr/include/sys/_types/_gid_t.h
Sound.o: /usr/include/sys/_types/_in_addr_t.h
Sound.o: /usr/include/sys/_types/_in_port_t.h
Sound.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
Sound.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
Sound.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
Sound.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
Sound.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h
Sound.o: /usr/include/sys/_types/_useconds_t.h
Sound.o: /usr/include/sys/_types/_suseconds_t.h
Sound.o: /usr/include/sys/_types/_fd_def.h
Sound.o: /usr/include/sys/_types/_fd_setsize.h
Sound.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
Sound.o: /usr/include/sys/_types/_fd_zero.h
Sound.o: /usr/include/sys/_types/_fd_isset.h
Sound.o: /usr/include/sys/_types/_fd_copy.h
Sound.o: /usr/include/sys/_types/_pthread_attr_t.h
Sound.o: /usr/include/sys/_types/_pthread_cond_t.h
Sound.o: /usr/include/sys/_types/_pthread_condattr_t.h
Sound.o: /usr/include/sys/_types/_pthread_mutex_t.h
Sound.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
Sound.o: /usr/include/sys/_types/_pthread_once_t.h
Sound.o: /usr/include/sys/_types/_pthread_rwlock_t.h
Sound.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
Sound.o: /usr/include/sys/_types/_pthread_t.h
Sound.o: /usr/include/sys/_types/_pthread_key_t.h
Sound.o: /usr/include/sys/_types/_fsblkcnt_t.h
Sound.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
Sound.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
Sound.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
Heap.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
Heap.o: /usr/include/sys/_symbol_aliasing.h
Heap.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
Heap.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
Heap.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
Heap.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
Heap.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
Heap.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
Heap.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h protos.h
Heap.o: structs.h /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
Heap.o: /usr/include/machine/types.h /usr/include/i386/types.h
Heap.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
Heap.o: /usr/include/sys/_types/_int32_t.h /usr/include/sys/_types/_int64_t.h
Heap.o: /usr/include/sys/_types/_intptr_t.h
Heap.o: /usr/include/sys/_types/_uintptr_t.h
Heap.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
Heap.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
Heap.o: /usr/include/libkern/_OSByteOrder.h
Heap.o: /usr/include/libkern/i386/_OSByteOrder.h
Heap.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_blkcnt_t.h
Heap.o: /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h
Heap.o: /usr/include/sys/_types/_in_addr_t.h
Heap.o: /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h
Heap.o: /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h
Heap.o: /usr/include/sys/_types/_mode_t.h /usr/include/sys/_types/_nlink_t.h
Heap.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/_types/_pid_t.h
Heap.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_clock_t.h
Heap.o: /usr/include/sys/_types/_time_t.h
Heap.o: /usr/include/sys/_types/_useconds_t.h
Heap.o: /usr/include/sys/_types/_suseconds_t.h
Heap.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
Heap.o: /usr/include/sys/_types/_fd_def.h
Heap.o: /usr/include/sys/_types/_fd_setsize.h
Heap.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
Heap.o: /usr/include/sys/_types/_fd_zero.h
Heap.o: /usr/include/sys/_types/_fd_isset.h
Heap.o: /usr/include/sys/_types/_fd_copy.h
Heap.o: /usr/include/sys/_types/_pthread_attr_t.h
Heap.o: /usr/include/sys/_types/_pthread_cond_t.h
Heap.o: /usr/include/sys/_types/_pthread_condattr_t.h
Heap.o: /usr/include/sys/_types/_pthread_mutex_t.h
Heap.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
Heap.o: /usr/include/sys/_types/_pthread_once_t.h
Heap.o: /usr/include/sys/_types/_pthread_rwlock_t.h
Heap.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
Heap.o: /usr/include/sys/_types/_pthread_t.h
Heap.o: /usr/include/sys/_types/_pthread_key_t.h
Heap.o: /usr/include/sys/_types/_fsblkcnt_t.h
Heap.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
Heap.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
Heap.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
spec_procs2.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
spec_procs2.o: /usr/include/sys/_symbol_aliasing.h
spec_procs2.o: /usr/include/sys/_posix_availability.h
spec_procs2.o: /usr/include/Availability.h
spec_procs2.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
spec_procs2.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
spec_procs2.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
spec_procs2.o: /usr/include/sys/_types/_size_t.h
spec_procs2.o: /usr/include/sys/_types/_null.h
spec_procs2.o: /usr/include/sys/_types/_off_t.h
spec_procs2.o: /usr/include/sys/_types/_ssize_t.h
spec_procs2.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
spec_procs2.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
spec_procs2.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
spec_procs2.o: /usr/include/secure/_string.h /usr/include/ctype.h
spec_procs2.o: /usr/include/runetype.h /usr/include/sys/_types/_ct_rune_t.h
spec_procs2.o: /usr/include/sys/_types/_rune_t.h
spec_procs2.o: /usr/include/sys/_types/_wchar_t.h
spec_procs2.o: /usr/include/sys/_types/_wint_t.h protos.h structs.h
spec_procs2.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
spec_procs2.o: /usr/include/machine/types.h /usr/include/i386/types.h
spec_procs2.o: /usr/include/sys/_types/_int8_t.h
spec_procs2.o: /usr/include/sys/_types/_int16_t.h
spec_procs2.o: /usr/include/sys/_types/_int32_t.h
spec_procs2.o: /usr/include/sys/_types/_int64_t.h
spec_procs2.o: /usr/include/sys/_types/_intptr_t.h
spec_procs2.o: /usr/include/sys/_types/_uintptr_t.h
spec_procs2.o: /usr/include/sys/_types/___offsetof.h
spec_procs2.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
spec_procs2.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
spec_procs2.o: /usr/include/libkern/i386/_OSByteOrder.h
spec_procs2.o: /usr/include/sys/_types/_dev_t.h
spec_procs2.o: /usr/include/sys/_types/_blkcnt_t.h
spec_procs2.o: /usr/include/sys/_types/_blksize_t.h
spec_procs2.o: /usr/include/sys/_types/_gid_t.h
spec_procs2.o: /usr/include/sys/_types/_in_addr_t.h
spec_procs2.o: /usr/include/sys/_types/_in_port_t.h
spec_procs2.o: /usr/include/sys/_types/_ino_t.h
spec_procs2.o: /usr/include/sys/_types/_ino64_t.h
spec_procs2.o: /usr/include/sys/_types/_key_t.h
spec_procs2.o: /usr/include/sys/_types/_mode_t.h
spec_procs2.o: /usr/include/sys/_types/_nlink_t.h
spec_procs2.o: /usr/include/sys/_types/_id_t.h
spec_procs2.o: /usr/include/sys/_types/_pid_t.h
spec_procs2.o: /usr/include/sys/_types/_uid_t.h
spec_procs2.o: /usr/include/sys/_types/_clock_t.h
spec_procs2.o: /usr/include/sys/_types/_time_t.h
spec_procs2.o: /usr/include/sys/_types/_useconds_t.h
spec_procs2.o: /usr/include/sys/_types/_suseconds_t.h
spec_procs2.o: /usr/include/sys/_types/_fd_def.h
spec_procs2.o: /usr/include/sys/_types/_fd_setsize.h
spec_procs2.o: /usr/include/sys/_types/_fd_set.h
spec_procs2.o: /usr/include/sys/_types/_fd_clr.h
spec_procs2.o: /usr/include/sys/_types/_fd_zero.h
spec_procs2.o: /usr/include/sys/_types/_fd_isset.h
spec_procs2.o: /usr/include/sys/_types/_fd_copy.h
spec_procs2.o: /usr/include/sys/_types/_pthread_attr_t.h
spec_procs2.o: /usr/include/sys/_types/_pthread_cond_t.h
spec_procs2.o: /usr/include/sys/_types/_pthread_condattr_t.h
spec_procs2.o: /usr/include/sys/_types/_pthread_mutex_t.h
spec_procs2.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
spec_procs2.o: /usr/include/sys/_types/_pthread_once_t.h
spec_procs2.o: /usr/include/sys/_types/_pthread_rwlock_t.h
spec_procs2.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
spec_procs2.o: /usr/include/sys/_types/_pthread_t.h
spec_procs2.o: /usr/include/sys/_types/_pthread_key_t.h
spec_procs2.o: /usr/include/sys/_types/_fsblkcnt_t.h
spec_procs2.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
spec_procs2.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h
spec_procs2.o: limits.h poly.h race.h script.h spells.h trap.h utils.h
spec_procs2.o: vt100c.h wizlist.h parser.h
magic3.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
magic3.o: /usr/include/sys/_symbol_aliasing.h
magic3.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
magic3.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
magic3.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
magic3.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
magic3.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
magic3.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
magic3.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
magic3.o: /usr/include/assert.h protos.h structs.h /usr/include/sys/types.h
magic3.o: /usr/include/sys/appleapiopts.h /usr/include/machine/types.h
magic3.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
magic3.o: /usr/include/sys/_types/_int16_t.h
magic3.o: /usr/include/sys/_types/_int32_t.h
magic3.o: /usr/include/sys/_types/_int64_t.h
magic3.o: /usr/include/sys/_types/_intptr_t.h
magic3.o: /usr/include/sys/_types/_uintptr_t.h
magic3.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
magic3.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
magic3.o: /usr/include/libkern/_OSByteOrder.h
magic3.o: /usr/include/libkern/i386/_OSByteOrder.h
magic3.o: /usr/include/sys/_types/_dev_t.h
magic3.o: /usr/include/sys/_types/_blkcnt_t.h
magic3.o: /usr/include/sys/_types/_blksize_t.h
magic3.o: /usr/include/sys/_types/_gid_t.h
magic3.o: /usr/include/sys/_types/_in_addr_t.h
magic3.o: /usr/include/sys/_types/_in_port_t.h
magic3.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
magic3.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
magic3.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
magic3.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
magic3.o: /usr/include/sys/_types/_clock_t.h
magic3.o: /usr/include/sys/_types/_time_t.h
magic3.o: /usr/include/sys/_types/_useconds_t.h
magic3.o: /usr/include/sys/_types/_suseconds_t.h
magic3.o: /usr/include/sys/_types/_rsize_t.h
magic3.o: /usr/include/sys/_types/_errno_t.h
magic3.o: /usr/include/sys/_types/_fd_def.h
magic3.o: /usr/include/sys/_types/_fd_setsize.h
magic3.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
magic3.o: /usr/include/sys/_types/_fd_zero.h
magic3.o: /usr/include/sys/_types/_fd_isset.h
magic3.o: /usr/include/sys/_types/_fd_copy.h
magic3.o: /usr/include/sys/_types/_pthread_attr_t.h
magic3.o: /usr/include/sys/_types/_pthread_cond_t.h
magic3.o: /usr/include/sys/_types/_pthread_condattr_t.h
magic3.o: /usr/include/sys/_types/_pthread_mutex_t.h
magic3.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
magic3.o: /usr/include/sys/_types/_pthread_once_t.h
magic3.o: /usr/include/sys/_types/_pthread_rwlock_t.h
magic3.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
magic3.o: /usr/include/sys/_types/_pthread_t.h
magic3.o: /usr/include/sys/_types/_pthread_key_t.h
magic3.o: /usr/include/sys/_types/_fsblkcnt_t.h
magic3.o: /usr/include/sys/_types/_fsfilcnt_t.h area.h comm.h db.h handler.h
magic3.o: hash.h heap.h interpreter.h limits.h poly.h race.h script.h
magic3.o: spells.h trap.h utils.h vt100c.h wizlist.h parser.h
security.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
security.o: /usr/include/sys/_symbol_aliasing.h
security.o: /usr/include/sys/_posix_availability.h
security.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
security.o: /usr/include/_types.h /usr/include/sys/_types.h
security.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
security.o: /usr/include/sys/_types/_va_list.h
security.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
security.o: /usr/include/sys/_types/_off_t.h
security.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
security.o: /usr/include/secure/_common.h /usr/include/string.h
security.o: /usr/include/sys/_types/_rsize_t.h
security.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
security.o: /usr/include/secure/_string.h
spec_procs3.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
spec_procs3.o: /usr/include/sys/_symbol_aliasing.h
spec_procs3.o: /usr/include/sys/_posix_availability.h
spec_procs3.o: /usr/include/Availability.h
spec_procs3.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
spec_procs3.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
spec_procs3.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
spec_procs3.o: /usr/include/sys/_types/_size_t.h
spec_procs3.o: /usr/include/sys/_types/_null.h
spec_procs3.o: /usr/include/sys/_types/_off_t.h
spec_procs3.o: /usr/include/sys/_types/_ssize_t.h
spec_procs3.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
spec_procs3.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
spec_procs3.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
spec_procs3.o: /usr/include/secure/_string.h /usr/include/ctype.h
spec_procs3.o: /usr/include/runetype.h /usr/include/sys/_types/_ct_rune_t.h
spec_procs3.o: /usr/include/sys/_types/_rune_t.h
spec_procs3.o: /usr/include/sys/_types/_wchar_t.h
spec_procs3.o: /usr/include/sys/_types/_wint_t.h protos.h structs.h
spec_procs3.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
spec_procs3.o: /usr/include/machine/types.h /usr/include/i386/types.h
spec_procs3.o: /usr/include/sys/_types/_int8_t.h
spec_procs3.o: /usr/include/sys/_types/_int16_t.h
spec_procs3.o: /usr/include/sys/_types/_int32_t.h
spec_procs3.o: /usr/include/sys/_types/_int64_t.h
spec_procs3.o: /usr/include/sys/_types/_intptr_t.h
spec_procs3.o: /usr/include/sys/_types/_uintptr_t.h
spec_procs3.o: /usr/include/sys/_types/___offsetof.h
spec_procs3.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
spec_procs3.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
spec_procs3.o: /usr/include/libkern/i386/_OSByteOrder.h
spec_procs3.o: /usr/include/sys/_types/_dev_t.h
spec_procs3.o: /usr/include/sys/_types/_blkcnt_t.h
spec_procs3.o: /usr/include/sys/_types/_blksize_t.h
spec_procs3.o: /usr/include/sys/_types/_gid_t.h
spec_procs3.o: /usr/include/sys/_types/_in_addr_t.h
spec_procs3.o: /usr/include/sys/_types/_in_port_t.h
spec_procs3.o: /usr/include/sys/_types/_ino_t.h
spec_procs3.o: /usr/include/sys/_types/_ino64_t.h
spec_procs3.o: /usr/include/sys/_types/_key_t.h
spec_procs3.o: /usr/include/sys/_types/_mode_t.h
spec_procs3.o: /usr/include/sys/_types/_nlink_t.h
spec_procs3.o: /usr/include/sys/_types/_id_t.h
spec_procs3.o: /usr/include/sys/_types/_pid_t.h
spec_procs3.o: /usr/include/sys/_types/_uid_t.h
spec_procs3.o: /usr/include/sys/_types/_clock_t.h
spec_procs3.o: /usr/include/sys/_types/_time_t.h
spec_procs3.o: /usr/include/sys/_types/_useconds_t.h
spec_procs3.o: /usr/include/sys/_types/_suseconds_t.h
spec_procs3.o: /usr/include/sys/_types/_fd_def.h
spec_procs3.o: /usr/include/sys/_types/_fd_setsize.h
spec_procs3.o: /usr/include/sys/_types/_fd_set.h
spec_procs3.o: /usr/include/sys/_types/_fd_clr.h
spec_procs3.o: /usr/include/sys/_types/_fd_zero.h
spec_procs3.o: /usr/include/sys/_types/_fd_isset.h
spec_procs3.o: /usr/include/sys/_types/_fd_copy.h
spec_procs3.o: /usr/include/sys/_types/_pthread_attr_t.h
spec_procs3.o: /usr/include/sys/_types/_pthread_cond_t.h
spec_procs3.o: /usr/include/sys/_types/_pthread_condattr_t.h
spec_procs3.o: /usr/include/sys/_types/_pthread_mutex_t.h
spec_procs3.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
spec_procs3.o: /usr/include/sys/_types/_pthread_once_t.h
spec_procs3.o: /usr/include/sys/_types/_pthread_rwlock_t.h
spec_procs3.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
spec_procs3.o: /usr/include/sys/_types/_pthread_t.h
spec_procs3.o: /usr/include/sys/_types/_pthread_key_t.h
spec_procs3.o: /usr/include/sys/_types/_fsblkcnt_t.h
spec_procs3.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
spec_procs3.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h
spec_procs3.o: limits.h poly.h race.h script.h spells.h trap.h utils.h
spec_procs3.o: vt100c.h wizlist.h parser.h
create.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
create.o: /usr/include/sys/_symbol_aliasing.h
create.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
create.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
create.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
create.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
create.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
create.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
create.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h protos.h
create.o: structs.h /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
create.o: /usr/include/machine/types.h /usr/include/i386/types.h
create.o: /usr/include/sys/_types/_int8_t.h
create.o: /usr/include/sys/_types/_int16_t.h
create.o: /usr/include/sys/_types/_int32_t.h
create.o: /usr/include/sys/_types/_int64_t.h
create.o: /usr/include/sys/_types/_intptr_t.h
create.o: /usr/include/sys/_types/_uintptr_t.h
create.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
create.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
create.o: /usr/include/libkern/_OSByteOrder.h
create.o: /usr/include/libkern/i386/_OSByteOrder.h
create.o: /usr/include/sys/_types/_dev_t.h
create.o: /usr/include/sys/_types/_blkcnt_t.h
create.o: /usr/include/sys/_types/_blksize_t.h
create.o: /usr/include/sys/_types/_gid_t.h
create.o: /usr/include/sys/_types/_in_addr_t.h
create.o: /usr/include/sys/_types/_in_port_t.h
create.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
create.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
create.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
create.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
create.o: /usr/include/sys/_types/_clock_t.h
create.o: /usr/include/sys/_types/_time_t.h
create.o: /usr/include/sys/_types/_useconds_t.h
create.o: /usr/include/sys/_types/_suseconds_t.h
create.o: /usr/include/sys/_types/_rsize_t.h
create.o: /usr/include/sys/_types/_errno_t.h
create.o: /usr/include/sys/_types/_fd_def.h
create.o: /usr/include/sys/_types/_fd_setsize.h
create.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
create.o: /usr/include/sys/_types/_fd_zero.h
create.o: /usr/include/sys/_types/_fd_isset.h
create.o: /usr/include/sys/_types/_fd_copy.h
create.o: /usr/include/sys/_types/_pthread_attr_t.h
create.o: /usr/include/sys/_types/_pthread_cond_t.h
create.o: /usr/include/sys/_types/_pthread_condattr_t.h
create.o: /usr/include/sys/_types/_pthread_mutex_t.h
create.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
create.o: /usr/include/sys/_types/_pthread_once_t.h
create.o: /usr/include/sys/_types/_pthread_rwlock_t.h
create.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
create.o: /usr/include/sys/_types/_pthread_t.h
create.o: /usr/include/sys/_types/_pthread_key_t.h
create.o: /usr/include/sys/_types/_fsblkcnt_t.h
create.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
create.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
create.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
bsd.o: /usr/include/string.h /usr/include/_types.h /usr/include/sys/_types.h
bsd.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
bsd.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
bsd.o: /usr/include/i386/_types.h /usr/include/Availability.h
bsd.o: /usr/include/AvailabilityInternal.h /usr/include/sys/_types/_size_t.h
bsd.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_rsize_t.h
bsd.o: /usr/include/sys/_types/_errno_t.h /usr/include/sys/_types/_ssize_t.h
bsd.o: /usr/include/strings.h /usr/include/secure/_string.h
bsd.o: /usr/include/secure/_common.h /usr/include/sys/types.h
bsd.o: /usr/include/sys/appleapiopts.h /usr/include/machine/types.h
bsd.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
bsd.o: /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h
bsd.o: /usr/include/sys/_types/_int64_t.h /usr/include/sys/_types/_intptr_t.h
bsd.o: /usr/include/sys/_types/_uintptr_t.h
bsd.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
bsd.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
bsd.o: /usr/include/libkern/_OSByteOrder.h
bsd.o: /usr/include/libkern/i386/_OSByteOrder.h
bsd.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_blkcnt_t.h
bsd.o: /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h
bsd.o: /usr/include/sys/_types/_in_addr_t.h
bsd.o: /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h
bsd.o: /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h
bsd.o: /usr/include/sys/_types/_mode_t.h /usr/include/sys/_types/_nlink_t.h
bsd.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/_types/_pid_t.h
bsd.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_uid_t.h
bsd.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h
bsd.o: /usr/include/sys/_types/_useconds_t.h
bsd.o: /usr/include/sys/_types/_suseconds_t.h
bsd.o: /usr/include/sys/_types/_fd_def.h
bsd.o: /usr/include/sys/_types/_fd_setsize.h
bsd.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
bsd.o: /usr/include/sys/_types/_fd_zero.h /usr/include/sys/_types/_fd_isset.h
bsd.o: /usr/include/sys/_types/_fd_copy.h
bsd.o: /usr/include/sys/_types/_pthread_attr_t.h
bsd.o: /usr/include/sys/_types/_pthread_cond_t.h
bsd.o: /usr/include/sys/_types/_pthread_condattr_t.h
bsd.o: /usr/include/sys/_types/_pthread_mutex_t.h
bsd.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
bsd.o: /usr/include/sys/_types/_pthread_once_t.h
bsd.o: /usr/include/sys/_types/_pthread_rwlock_t.h
bsd.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
bsd.o: /usr/include/sys/_types/_pthread_t.h
bsd.o: /usr/include/sys/_types/_pthread_key_t.h
bsd.o: /usr/include/sys/_types/_fsblkcnt_t.h
bsd.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/unistd.h
bsd.o: /usr/include/sys/unistd.h /usr/include/sys/_types/_posix_vdisable.h
bsd.o: /usr/include/sys/_types/_seek_set.h /usr/include/sys/select.h
bsd.o: /usr/include/sys/_types/_timespec.h /usr/include/sys/_types/_timeval.h
bsd.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_select.h
bsd.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
parser.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
parser.o: /usr/include/sys/_symbol_aliasing.h
parser.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
parser.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
parser.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
parser.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
parser.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
parser.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
parser.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
parser.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
parser.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
parser.o: /usr/include/secure/_string.h protos.h structs.h
parser.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
parser.o: /usr/include/machine/types.h /usr/include/i386/types.h
parser.o: /usr/include/sys/_types/_int8_t.h
parser.o: /usr/include/sys/_types/_int16_t.h
parser.o: /usr/include/sys/_types/_int32_t.h
parser.o: /usr/include/sys/_types/_int64_t.h
parser.o: /usr/include/sys/_types/_intptr_t.h
parser.o: /usr/include/sys/_types/_uintptr_t.h
parser.o: /usr/include/sys/_types/___offsetof.h /usr/include/machine/endian.h
parser.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
parser.o: /usr/include/libkern/_OSByteOrder.h
parser.o: /usr/include/libkern/i386/_OSByteOrder.h
parser.o: /usr/include/sys/_types/_dev_t.h
parser.o: /usr/include/sys/_types/_blkcnt_t.h
parser.o: /usr/include/sys/_types/_blksize_t.h
parser.o: /usr/include/sys/_types/_gid_t.h
parser.o: /usr/include/sys/_types/_in_addr_t.h
parser.o: /usr/include/sys/_types/_in_port_t.h
parser.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
parser.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
parser.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
parser.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
parser.o: /usr/include/sys/_types/_clock_t.h
parser.o: /usr/include/sys/_types/_time_t.h
parser.o: /usr/include/sys/_types/_useconds_t.h
parser.o: /usr/include/sys/_types/_suseconds_t.h
parser.o: /usr/include/sys/_types/_fd_def.h
parser.o: /usr/include/sys/_types/_fd_setsize.h
parser.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
parser.o: /usr/include/sys/_types/_fd_zero.h
parser.o: /usr/include/sys/_types/_fd_isset.h
parser.o: /usr/include/sys/_types/_fd_copy.h
parser.o: /usr/include/sys/_types/_pthread_attr_t.h
parser.o: /usr/include/sys/_types/_pthread_cond_t.h
parser.o: /usr/include/sys/_types/_pthread_condattr_t.h
parser.o: /usr/include/sys/_types/_pthread_mutex_t.h
parser.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
parser.o: /usr/include/sys/_types/_pthread_once_t.h
parser.o: /usr/include/sys/_types/_pthread_rwlock_t.h
parser.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
parser.o: /usr/include/sys/_types/_pthread_t.h
parser.o: /usr/include/sys/_types/_pthread_key_t.h
parser.o: /usr/include/sys/_types/_fsblkcnt_t.h
parser.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
parser.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
parser.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
intrinsics.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
intrinsics.o: /usr/include/sys/_symbol_aliasing.h
intrinsics.o: /usr/include/sys/_posix_availability.h
intrinsics.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
intrinsics.o: /usr/include/_types.h /usr/include/sys/_types.h
intrinsics.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
intrinsics.o: /usr/include/sys/_types/_va_list.h
intrinsics.o: /usr/include/sys/_types/_size_t.h
intrinsics.o: /usr/include/sys/_types/_null.h
intrinsics.o: /usr/include/sys/_types/_off_t.h
intrinsics.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
intrinsics.o: /usr/include/secure/_common.h /usr/include/string.h
intrinsics.o: /usr/include/sys/_types/_rsize_t.h
intrinsics.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
intrinsics.o: /usr/include/secure/_string.h /usr/include/ctype.h
intrinsics.o: /usr/include/runetype.h /usr/include/sys/_types/_ct_rune_t.h
intrinsics.o: /usr/include/sys/_types/_rune_t.h
intrinsics.o: /usr/include/sys/_types/_wchar_t.h
intrinsics.o: /usr/include/sys/_types/_wint_t.h protos.h structs.h
intrinsics.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
intrinsics.o: /usr/include/machine/types.h /usr/include/i386/types.h
intrinsics.o: /usr/include/sys/_types/_int8_t.h
intrinsics.o: /usr/include/sys/_types/_int16_t.h
intrinsics.o: /usr/include/sys/_types/_int32_t.h
intrinsics.o: /usr/include/sys/_types/_int64_t.h
intrinsics.o: /usr/include/sys/_types/_intptr_t.h
intrinsics.o: /usr/include/sys/_types/_uintptr_t.h
intrinsics.o: /usr/include/sys/_types/___offsetof.h
intrinsics.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
intrinsics.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
intrinsics.o: /usr/include/libkern/i386/_OSByteOrder.h
intrinsics.o: /usr/include/sys/_types/_dev_t.h
intrinsics.o: /usr/include/sys/_types/_blkcnt_t.h
intrinsics.o: /usr/include/sys/_types/_blksize_t.h
intrinsics.o: /usr/include/sys/_types/_gid_t.h
intrinsics.o: /usr/include/sys/_types/_in_addr_t.h
intrinsics.o: /usr/include/sys/_types/_in_port_t.h
intrinsics.o: /usr/include/sys/_types/_ino_t.h
intrinsics.o: /usr/include/sys/_types/_ino64_t.h
intrinsics.o: /usr/include/sys/_types/_key_t.h
intrinsics.o: /usr/include/sys/_types/_mode_t.h
intrinsics.o: /usr/include/sys/_types/_nlink_t.h
intrinsics.o: /usr/include/sys/_types/_id_t.h
intrinsics.o: /usr/include/sys/_types/_pid_t.h
intrinsics.o: /usr/include/sys/_types/_uid_t.h
intrinsics.o: /usr/include/sys/_types/_clock_t.h
intrinsics.o: /usr/include/sys/_types/_time_t.h
intrinsics.o: /usr/include/sys/_types/_useconds_t.h
intrinsics.o: /usr/include/sys/_types/_suseconds_t.h
intrinsics.o: /usr/include/sys/_types/_fd_def.h
intrinsics.o: /usr/include/sys/_types/_fd_setsize.h
intrinsics.o: /usr/include/sys/_types/_fd_set.h
intrinsics.o: /usr/include/sys/_types/_fd_clr.h
intrinsics.o: /usr/include/sys/_types/_fd_zero.h
intrinsics.o: /usr/include/sys/_types/_fd_isset.h
intrinsics.o: /usr/include/sys/_types/_fd_copy.h
intrinsics.o: /usr/include/sys/_types/_pthread_attr_t.h
intrinsics.o: /usr/include/sys/_types/_pthread_cond_t.h
intrinsics.o: /usr/include/sys/_types/_pthread_condattr_t.h
intrinsics.o: /usr/include/sys/_types/_pthread_mutex_t.h
intrinsics.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
intrinsics.o: /usr/include/sys/_types/_pthread_once_t.h
intrinsics.o: /usr/include/sys/_types/_pthread_rwlock_t.h
intrinsics.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
intrinsics.o: /usr/include/sys/_types/_pthread_t.h
intrinsics.o: /usr/include/sys/_types/_pthread_key_t.h
intrinsics.o: /usr/include/sys/_types/_fsblkcnt_t.h
intrinsics.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h
intrinsics.o: area.h comm.h db.h handler.h hash.h heap.h interpreter.h
intrinsics.o: limits.h poly.h race.h script.h spells.h trap.h utils.h
intrinsics.o: vt100c.h wizlist.h parser.h
test.act.wizard.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
test.act.wizard.o: /usr/include/sys/_symbol_aliasing.h
test.act.wizard.o: /usr/include/sys/_posix_availability.h
test.act.wizard.o: /usr/include/Availability.h
test.act.wizard.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
test.act.wizard.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
test.act.wizard.o: /usr/include/i386/_types.h
test.act.wizard.o: /usr/include/sys/_types/_va_list.h
test.act.wizard.o: /usr/include/sys/_types/_size_t.h
test.act.wizard.o: /usr/include/sys/_types/_null.h
test.act.wizard.o: /usr/include/sys/_types/_off_t.h
test.act.wizard.o: /usr/include/sys/_types/_ssize_t.h
test.act.wizard.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
test.act.wizard.o: /usr/include/stdlib.h /usr/include/sys/wait.h
test.act.wizard.o: /usr/include/sys/_types/_pid_t.h
test.act.wizard.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
test.act.wizard.o: /usr/include/sys/appleapiopts.h
test.act.wizard.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
test.act.wizard.o: /usr/include/machine/_mcontext.h
test.act.wizard.o: /usr/include/i386/_mcontext.h
test.act.wizard.o: /usr/include/mach/i386/_structs.h
test.act.wizard.o: /usr/include/sys/_types/_sigaltstack.h
test.act.wizard.o: /usr/include/sys/_types/_ucontext.h
test.act.wizard.o: /usr/include/sys/_types/_pthread_attr_t.h
test.act.wizard.o: /usr/include/sys/_types/_sigset_t.h
test.act.wizard.o: /usr/include/sys/_types/_uid_t.h
test.act.wizard.o: /usr/include/sys/resource.h /usr/include/stdint.h
test.act.wizard.o: /usr/include/sys/_types/_int8_t.h
test.act.wizard.o: /usr/include/sys/_types/_int16_t.h
test.act.wizard.o: /usr/include/sys/_types/_int32_t.h
test.act.wizard.o: /usr/include/sys/_types/_int64_t.h
test.act.wizard.o: /usr/include/_types/_uint8_t.h
test.act.wizard.o: /usr/include/_types/_uint16_t.h
test.act.wizard.o: /usr/include/_types/_uint32_t.h
test.act.wizard.o: /usr/include/_types/_uint64_t.h
test.act.wizard.o: /usr/include/sys/_types/_intptr_t.h
test.act.wizard.o: /usr/include/sys/_types/_uintptr_t.h
test.act.wizard.o: /usr/include/_types/_intmax_t.h
test.act.wizard.o: /usr/include/_types/_uintmax_t.h
test.act.wizard.o: /usr/include/sys/_types/_timeval.h
test.act.wizard.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
test.act.wizard.o: /usr/include/sys/_endian.h
test.act.wizard.o: /usr/include/libkern/_OSByteOrder.h
test.act.wizard.o: /usr/include/libkern/i386/_OSByteOrder.h
test.act.wizard.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
test.act.wizard.o: /usr/include/sys/_types/_rune_t.h
test.act.wizard.o: /usr/include/sys/_types/_wchar_t.h
test.act.wizard.o: /usr/include/machine/types.h /usr/include/i386/types.h
test.act.wizard.o: /usr/include/sys/_types/___offsetof.h
test.act.wizard.o: /usr/include/sys/_types/_dev_t.h
test.act.wizard.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
test.act.wizard.o: /usr/include/sys/_types/_rsize_t.h
test.act.wizard.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
test.act.wizard.o: /usr/include/secure/_string.h /usr/include/ctype.h
test.act.wizard.o: /usr/include/runetype.h /usr/include/sys/_types/_wint_t.h
test.act.wizard.o: /usr/local/include/criterion/criterion.h
test.act.wizard.o: /usr/local/include/criterion/designated-initializer-compat.h
test.act.wizard.o: /usr/local/include/criterion/common.h
test.act.wizard.o: /usr/local/include/criterion/types.h
test.act.wizard.o: /usr/local/include/criterion/alloc.h /usr/include/stddef.h
test.act.wizard.o: /usr/include/sys/_types/_ptrdiff_t.h
test.act.wizard.o: /usr/include/stdbool.h /usr/include/assert.h protos.h
test.act.wizard.o: structs.h /usr/include/sys/types.h
test.act.wizard.o: /usr/include/sys/_types/_blkcnt_t.h
test.act.wizard.o: /usr/include/sys/_types/_blksize_t.h
test.act.wizard.o: /usr/include/sys/_types/_gid_t.h
test.act.wizard.o: /usr/include/sys/_types/_in_addr_t.h
test.act.wizard.o: /usr/include/sys/_types/_in_port_t.h
test.act.wizard.o: /usr/include/sys/_types/_ino_t.h
test.act.wizard.o: /usr/include/sys/_types/_ino64_t.h
test.act.wizard.o: /usr/include/sys/_types/_key_t.h
test.act.wizard.o: /usr/include/sys/_types/_nlink_t.h
test.act.wizard.o: /usr/include/sys/_types/_clock_t.h
test.act.wizard.o: /usr/include/sys/_types/_time_t.h
test.act.wizard.o: /usr/include/sys/_types/_useconds_t.h
test.act.wizard.o: /usr/include/sys/_types/_suseconds_t.h
test.act.wizard.o: /usr/include/sys/_types/_fd_def.h
test.act.wizard.o: /usr/include/sys/_types/_fd_setsize.h
test.act.wizard.o: /usr/include/sys/_types/_fd_set.h
test.act.wizard.o: /usr/include/sys/_types/_fd_clr.h
test.act.wizard.o: /usr/include/sys/_types/_fd_zero.h
test.act.wizard.o: /usr/include/sys/_types/_fd_isset.h
test.act.wizard.o: /usr/include/sys/_types/_fd_copy.h
test.act.wizard.o: /usr/include/sys/_types/_pthread_cond_t.h
test.act.wizard.o: /usr/include/sys/_types/_pthread_condattr_t.h
test.act.wizard.o: /usr/include/sys/_types/_pthread_mutex_t.h
test.act.wizard.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
test.act.wizard.o: /usr/include/sys/_types/_pthread_once_t.h
test.act.wizard.o: /usr/include/sys/_types/_pthread_rwlock_t.h
test.act.wizard.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
test.act.wizard.o: /usr/include/sys/_types/_pthread_t.h
test.act.wizard.o: /usr/include/sys/_types/_pthread_key_t.h
test.act.wizard.o: /usr/include/sys/_types/_fsblkcnt_t.h
test.act.wizard.o: /usr/include/sys/_types/_fsfilcnt_t.h area.h comm.h db.h
test.act.wizard.o: handler.h hash.h heap.h interpreter.h limits.h poly.h
test.act.wizard.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h
test.act.wizard.o: parser.h
main.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
main.o: /usr/include/sys/_symbol_aliasing.h
main.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
main.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
main.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
main.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
main.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
main.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
main.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
main.o: /usr/include/stdlib.h /usr/include/sys/wait.h
main.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
main.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
main.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
main.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
main.o: /usr/include/mach/i386/_structs.h
main.o: /usr/include/sys/_types/_sigaltstack.h
main.o: /usr/include/sys/_types/_ucontext.h
main.o: /usr/include/sys/_types/_pthread_attr_t.h
main.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h
main.o: /usr/include/sys/resource.h /usr/include/stdint.h
main.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
main.o: /usr/include/sys/_types/_int32_t.h /usr/include/sys/_types/_int64_t.h
main.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
main.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
main.o: /usr/include/sys/_types/_intptr_t.h
main.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
main.o: /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h
main.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
main.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
main.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
main.o: /usr/include/sys/_types/_ct_rune_t.h
main.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
main.o: /usr/include/machine/types.h /usr/include/i386/types.h
main.o: /usr/include/sys/_types/___offsetof.h
main.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
main.o: protos.h structs.h /usr/include/sys/types.h
main.o: /usr/include/sys/_types/_blkcnt_t.h
main.o: /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h
main.o: /usr/include/sys/_types/_in_addr_t.h
main.o: /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h
main.o: /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h
main.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_clock_t.h
main.o: /usr/include/sys/_types/_time_t.h
main.o: /usr/include/sys/_types/_useconds_t.h
main.o: /usr/include/sys/_types/_suseconds_t.h
main.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
main.o: /usr/include/sys/_types/_fd_def.h
main.o: /usr/include/sys/_types/_fd_setsize.h
main.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
main.o: /usr/include/sys/_types/_fd_zero.h
main.o: /usr/include/sys/_types/_fd_isset.h
main.o: /usr/include/sys/_types/_fd_copy.h
main.o: /usr/include/sys/_types/_pthread_cond_t.h
main.o: /usr/include/sys/_types/_pthread_condattr_t.h
main.o: /usr/include/sys/_types/_pthread_mutex_t.h
main.o: /usr/include/sys/_types/_pthread_mutexattr_t.h
main.o: /usr/include/sys/_types/_pthread_once_t.h
main.o: /usr/include/sys/_types/_pthread_rwlock_t.h
main.o: /usr/include/sys/_types/_pthread_rwlockattr_t.h
main.o: /usr/include/sys/_types/_pthread_t.h
main.o: /usr/include/sys/_types/_pthread_key_t.h
main.o: /usr/include/sys/_types/_fsblkcnt_t.h
main.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/assert.h area.h
main.o: comm.h db.h handler.h hash.h heap.h interpreter.h limits.h poly.h
main.o: race.h script.h spells.h trap.h utils.h vt100c.h wizlist.h parser.h
