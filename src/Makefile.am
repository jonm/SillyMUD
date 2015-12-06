## Process this file with automake to produce Makefile.in

AM_CFLAGS = -DLOCAL_STATE_DIR=\"$(localstatedir)\"

# main program
bin_PROGRAMS = sillymud
common_sources = comm.c act.comm.c act.info.c act.move.c act.obj1.c \
	act.obj2.c act.off.c act.other.c act.social.c act.wizard.c handler.c \
	db.c interpreter.c utility.c spec_assign.c shop.c limits.c mobact.c \
	fight.c modify.c weather.c spells1.c spells2.c spell_parser.c \
	reception.c constants.c spec_procs.c signals.c board.c magic.c \
	magic2.c skills.c Opinion.c Trap.c magicutils.c multiclass.c hash.c \
	Sound.c Heap.c spec_procs2.c magic3.c security.c spec_procs3.c \
        create.c parser.c intrinsics.c
sillymud_SOURCES = $(common_sources) main.c

# unit tests
check_PROGRAMS = tests
tests_SOURCES = $(common_sources) test.act.wizard.c test.spell_parser.c \
	test.handler.c test.modify.c test.db.c
tests_LDADD = -lcriterion
TESTS = tests

