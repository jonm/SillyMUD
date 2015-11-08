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
CFLAGS = $(SUNFLAGS) $(CPPFLAGS) -Werror
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

comm.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
comm.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h utils.h
comm.o: vt100c.h wizlist.h parser.h
act.comm.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
act.comm.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
act.comm.o: utils.h vt100c.h wizlist.h parser.h
act.info.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
act.info.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
act.info.o: utils.h vt100c.h wizlist.h parser.h
act.move.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
act.move.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
act.move.o: utils.h vt100c.h wizlist.h parser.h
act.obj1.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
act.obj1.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
act.obj1.o: utils.h vt100c.h wizlist.h parser.h
act.obj2.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
act.obj2.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
act.obj2.o: utils.h vt100c.h wizlist.h parser.h
act.off.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
act.off.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
act.off.o: utils.h vt100c.h wizlist.h parser.h
act.other.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
act.other.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
act.other.o: utils.h vt100c.h wizlist.h parser.h
act.social.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
act.social.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
act.social.o: utils.h vt100c.h wizlist.h parser.h
act.wizard.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
act.wizard.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
act.wizard.o: utils.h vt100c.h wizlist.h parser.h
handler.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
handler.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
handler.o: utils.h vt100c.h wizlist.h parser.h
db.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
db.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h utils.h
db.o: vt100c.h wizlist.h parser.h
interpreter.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
interpreter.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
interpreter.o: utils.h vt100c.h wizlist.h parser.h
utility.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
utility.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
utility.o: utils.h vt100c.h wizlist.h parser.h
spec_assign.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
spec_assign.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
spec_assign.o: utils.h vt100c.h wizlist.h parser.h
shop.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
shop.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h utils.h
shop.o: vt100c.h wizlist.h parser.h
limits.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
limits.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
limits.o: utils.h vt100c.h wizlist.h parser.h
mobact.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
mobact.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
mobact.o: utils.h vt100c.h wizlist.h parser.h
fight.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
fight.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
fight.o: utils.h vt100c.h wizlist.h parser.h
modify.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
modify.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
modify.o: utils.h vt100c.h wizlist.h parser.h
weather.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
weather.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
weather.o: utils.h vt100c.h wizlist.h parser.h
spells1.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
spells1.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
spells1.o: utils.h vt100c.h wizlist.h parser.h
spells2.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
spells2.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
spells2.o: utils.h vt100c.h wizlist.h parser.h
spell_parser.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
spell_parser.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
spell_parser.o: utils.h vt100c.h wizlist.h parser.h
reception.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
reception.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
reception.o: utils.h vt100c.h wizlist.h parser.h
constants.o: structs.h limits.h trap.h race.h
spec_procs.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
spec_procs.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
spec_procs.o: utils.h vt100c.h wizlist.h parser.h
signals.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
signals.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
signals.o: utils.h vt100c.h wizlist.h parser.h
board.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
board.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
board.o: utils.h vt100c.h wizlist.h parser.h
magic.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
magic.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
magic.o: utils.h vt100c.h wizlist.h parser.h
magic2.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
magic2.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
magic2.o: utils.h vt100c.h wizlist.h parser.h
skills.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
skills.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
skills.o: utils.h vt100c.h wizlist.h parser.h
Opinion.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
Opinion.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
Opinion.o: utils.h vt100c.h wizlist.h parser.h
Trap.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
Trap.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h utils.h
Trap.o: vt100c.h wizlist.h parser.h
magicutils.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
magicutils.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
magicutils.o: utils.h vt100c.h wizlist.h parser.h
multiclass.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
multiclass.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
multiclass.o: utils.h vt100c.h wizlist.h parser.h
hash.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
hash.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h utils.h
hash.o: vt100c.h wizlist.h parser.h
Sound.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
Sound.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
Sound.o: utils.h vt100c.h wizlist.h parser.h
Heap.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
Heap.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h utils.h
Heap.o: vt100c.h wizlist.h parser.h
spec_procs2.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
spec_procs2.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
spec_procs2.o: utils.h vt100c.h wizlist.h parser.h
magic3.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
magic3.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
magic3.o: utils.h vt100c.h wizlist.h parser.h
spec_procs3.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
spec_procs3.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
spec_procs3.o: utils.h vt100c.h wizlist.h parser.h
create.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
create.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
create.o: utils.h vt100c.h wizlist.h parser.h
parser.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
parser.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
parser.o: utils.h vt100c.h wizlist.h parser.h
intrinsics.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
intrinsics.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h
intrinsics.o: utils.h vt100c.h wizlist.h parser.h
test.act.wizard.o: /usr/local/include/criterion/criterion.h
test.act.wizard.o: /usr/local/include/criterion/designated-initializer-compat.h
test.act.wizard.o: /usr/local/include/criterion/common.h
test.act.wizard.o: /usr/local/include/criterion/types.h
test.act.wizard.o: /usr/local/include/criterion/alloc.h
test.act.wizard.o: /usr/local/include/criterion/assert.h
test.act.wizard.o: /usr/local/include/criterion/preprocess.h
test.act.wizard.o: /usr/local/include/criterion/asprintf-compat.h
test.act.wizard.o: /usr/local/include/criterion/stats.h
test.act.wizard.o: /usr/local/include/criterion/hooks.h
test.act.wizard.o: /usr/local/include/criterion/event.h
test.act.wizard.o: /usr/local/include/criterion/abort.h
main.o: protos.h structs.h area.h comm.h db.h handler.h hash.h heap.h
main.o: interpreter.h limits.h poly.h race.h script.h spells.h trap.h utils.h
main.o: vt100c.h wizlist.h parser.h
