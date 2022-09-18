h57372
s 00001/00001/00068
d D 5.12 93/05/30 19:37:39 bostic 13 12
c make it run for 4.4BSD
e
s 00001/00001/00068
d D 5.11 91/09/06 13:42:24 sellgren 12 11
c lfortune doesn't exist anymore
e
s 00001/00001/00068
d D 5.10 91/09/06 13:38:30 sellgren 11 10
c we need writable strings since we're writing to char consts...
e
s 00001/00000/00068
d D 5.9 90/07/25 22:13:07 bostic 10 9
c move man page to section 6
e
s 00010/00071/00058
d D 5.8 90/05/11 12:46:29 bostic 9 8
c first pass for new make
e
s 00001/00001/00128
d D 5.7 89/07/30 12:58:10 bostic 8 7
c needs libcompat
e
s 00002/00006/00127
d D 5.6 89/03/05 19:08:41 bostic 7 6
c don't hide files
e
s 00099/00115/00034
d D 5.5 89/03/05 19:01:06 bostic 6 5
c cleanup, make it Berkeley's own
e
s 00001/00001/00148
d D 5.4 87/09/22 10:45:47 bostic 5 4
c fix mkdir
e
s 00009/00007/00140
d D 5.3 87/09/21 11:51:32 bostic 4 2
c integrate with dm
e
s 00011/00007/00140
d R 5.3 87/09/20 10:18:26 bostic 3 2
c integrate with dm
e
s 00062/00015/00085
d D 5.2 87/06/03 19:30:52 bostic 2 1
c BSD template
e
s 00100/00000/00000
d D 5.1 87/06/03 19:13:02 bostic 1 0
c date and time created 87/06/03 19:13:02 by bostic
e
u
U
t
T
I 6
D 9
#
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
E 9
#	%W% (Berkeley) %G%
D 9
#
E 6
I 1
# Configuration options
#  
D 6
#  Updated by jgd for csd1 and bruno for csd4.
#  Check this against Omakefile for changes.
#
E 6
#  LARNHOME is the directory where the larn data files will be installed.
#  BINDIR is the directory where the larn binary will be installed.
E 9

D 6
# LARNHOME = /c/noah/public/.lfiles
LARNHOME = /usr/games/lib/larnfiles
# BINDIR = /c/noah/public
BINDIR = /usr/games
CC= cc
E 6
I 6
D 9
LARNHOME=	/usr/games/lib/larnfiles
BINDIR=		/usr/games
E 6

D 6
# -ltermlib may need to be changed to -ltermcap on some systems
# TERMLIB= -ltermlib
TERMLIB= -ltermcap

E 6
# Available compile time options:
D 6
#   WIZID=xxx  - this is the userid (or playerid) of the wizard.  Default is
#			zero (superuser), which disables all wizard functions.
#			Players must have this userid (or playerid) in order
#			to become the non-scoring wizard player.  Definition
#			of WIZID to non-zero will enable the special wizard
#			debugging commands.  For root to become wizard, use
#			WIZID= -1.
#   EXTRA      - incorporates code to gather additional performance statistics
#   TIMECHECK  - incorporates code to disable play during working hours (8-5)
#   SYSV       - use system III/V (instead of V7) type ioctl calls
#   BSD        - use BSD specific features (mostly timer and signal stuff)
#   BSD4.1     - use BSD4.1 to avoid some 4.2 dependencies (must be used with
#					BSD above; do not mix with SYSV)
#   HIDEBYLINK - if defined, the program attempts to hide from ps
#   DOCHECKPOINTS - if not defined, checkpoint files are periodically written
#                   by the larn process (no forking) if enabled in the .larnopts
#		    description file.  Checkpointing is handy on an unreliable
#	    	    system, but takes CPU. Inclusion of DOCHECKPOINTS will cause
#		    fork()ing to perform the checkpoints (again if enabled in
#		    the .larnopts file).  This usually avoids pauses in larn
#		    while the checkpointing is being done (on large machines).
#   SAVEINHOME - put save files in users HOME instead of LARNHOME the as default
#	VER        - This is the version of the software, example:  12
#	SUBVER     - This is the revision of the software, example:  1
#	FLUSHNO=#  - Set the input queue excess flushing threshold (default 5)
#	NOVARARGS  - Define for systems that don't have varargs (a default
#		     varargs will be used).
#	MACRORND   - Define to use macro version of rnd() and rund() (fast
#		     and big)
#	UIDSCORE   - Define to use user id's to manage scoreboard.  Leaving
#		     this out will cause player id's from the file ".playerids"
#		     to be used instead.  (.playerids is created upon demand).
#		     Only one entry per id # is allowed in each scoreboard
#		     (winning & non-winning).
#	VT100	  - Compile for using vt100 family of terminals.  Omission of
#		    this define will cause larn to use termcap, but it will be
#		    MUCH slower due to an extra layer of output interpretation.
#		    Also, only VT100 mode allows 2 different standout modes,
#		    inverse video, and bold video.  And only in VT100 mode is
#		    the scrolling region of the terminal used (much nicer than
#		    insert/delete line sequences to simulate it, if VT100 is
#		    omitted).
#	NONAP	  - This causes napms() to return immediately instead of
#		    delaying n milliseconds.  This define may be needed on
#		    some systems if the nap stuff does not work correctly
#		    (possible hang).  nap() is primarilly used to delay for
#		    effect when casting missile type spells.
#	NOLOG	  - Turn off logging.
E 6
I 6
# WIZID=xxx
#	This is the userid (or playerid) of the wizard.  Default is zero
#	(superuser), which disables all wizard functions.  Players must
#	have this userid (or playerid) in order to become the non-scoring
#	wizard player.  Definition of WIZID to non-zero will enable the
#	special wizard debugging commands.  For root to become wizard, use
#	WIZID= -1.
E 9
# EXTRA
#	Incorporates code to gather additional performance statistics
D 9
# TIMECHECK
#	Incorporates code to disable play during working hours (8-5)
E 9
# SYSV
#	Use system III/V (instead of V7) type ioctl calls
# BSD
#	Use BSD specific features (mostly timer and signal stuff)
# BSD4.1
#	Use BSD4.1 to avoid some 4.2 dependencies (must be used with
#	BSD above; do not mix with SYSV)
# HIDEBYLINK
#	If defined, the program attempts to hide from ps
# DOCHECKPOINTS
#	If not defined, checkpoint files are periodically written by the
#	larn process (no forking) if enabled in the .larnopts description
#	file.  Checkpointing is handy on an unreliable system, but takes
#	CPU. Inclusion of DOCHECKPOINTS will cause fork()ing to perform the
#	checkpoints (again if enabled in the .larnopts file).  This usually
#	avoids pauses in larn while the checkpointing is being done (on
#	large machines).
D 9
# SAVEINHOME
#	Put save files in users HOME instead of LARNHOME the as default
E 9
# VER
#	This is the version of the software, example:  12
# SUBVER
#	This is the revision of the software, example:  1
# FLUSHNO=#
#	Set the input queue excess flushing threshold (default 5)
# NOVARARGS
#	Define for systems that don't have varargs (a default varargs will
#	be used).
# MACRORND
#	Define to use macro version of rnd() and rund() (fast and big)
# UIDSCORE
#	Define to use user id's to manage scoreboard.  Leaving this out will
#	cause player id's from the file ".playerids" to be used instead.
#	(.playerids is created upon demand).  Only one entry per id # is
#	allowed in each scoreboard (winning & non-winning).
#  VT100
#	Compile for using vt100 family of terminals.  Omission of this
#	define will cause larn to use termcap, but it will be MUCH slower
#	due to an extra layer of output interpretation.  Also, only VT100
#	mode allows 2 different standout modes, inverse video, and bold video.
#	And only in VT100 mode is the scrolling region of the terminal used
#	(much nicer than insert/delete line sequences to simulate it, if
#	VT100 is omitted).
# NONAP
#	This causes napms() to return immediately instead of delaying n
#	milliseconds.  This define may be needed on some systems if the nap
#	stuff does not work correctly (possible hang).  nap() is primarilly
#	used to delay for effect when casting missile type spells.
# NOLOG
#	Turn off logging.
E 6
D 9
#
E 9

D 6
OPTIONS = -DBSD -DVER=12 -DSUBVER=0 -DWIZID=57 -DSAVEINHOME -DNONAP -DNOLOG
E 6
I 6
D 9
OPTIONS = -DBSD -DVER=12 -DSUBVER=0 -DWIZID=-7 -DSAVEINHOME -DNONAP -DNOLOG
E 6

E 9
I 9
PROG=	larn
I 10
MAN6=	larn.0
E 10
D 11
CFLAGS+=-DBSD -DVER=12 -DSUBVER=0 -DNONAP
E 11
I 11
D 13
CFLAGS+=-DBSD -DVER=12 -DSUBVER=0 -DNONAP -fwritable-strings
E 13
I 13
CFLAGS+=-DBSD -DVER=12 -DSUBVER=0 -DNONAP -DUIDSCORE -fwritable-strings
E 13
E 11
E 9
D 6
# End of configurable make options
########################################################################
#
OBJS= main.o object.o create.o tok.o display.o global.o data.o io.o monster.o\
	store.o diag.o help.o config.o nap.o bill.o scores.o signal.o moreobj.o\
	movem.o regen.o fortune.o savelev.o
I 2
SRCS= main.c object.c create.c tok.c display.c global.c data.c io.c monster.c\
	store.c diag.c help.c config.c nap.c bill.c scores.c signal.c moreobj.c\
	movem.c regen.c fortune.c savelev.c
E 6
I 6
SRCS=	main.c object.c create.c tok.c display.c global.c data.c io.c \
	monster.c store.c diag.c help.c config.c nap.c bill.c scores.c \
	signal.c moreobj.c movem.c regen.c fortune.c savelev.c
D 9
OBJS=	main.o object.o create.o tok.o display.o global.o data.o io.o \
	monster.o store.o diag.o help.o config.o nap.o bill.o scores.o \
	signal.o moreobj.o movem.o regen.o fortune.o savelev.o
E 9
I 9
DPADD=	${LIBTERM} ${LIBCOMPAT}
LDADD=	-ltermcap -lcompat
HIDEGAME=hidegame
E 9
E 6
E 2

D 7
DOTFILES= .larn.help .larnmaze .larnopts .lfortune

E 7
D 2
FLAGS= -O $(OPTIONS) -DLARNHOME=\"$(LARNHOME)/\"
E 2
I 2
D 6
CFLAGS= -O $(OPTIONS) -DLARNHOME=\"$(LARNHOME)/\"
E 6
I 6
D 9
CFLAGS= -O ${OPTIONS} -DLARNHOME=\"${LARNHOME}/\"
E 9
I 9
beforeinstall:
	(cd ${.CURDIR}/datfiles; install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
D 12
	    larnmaze larnopts lfortune larn.help \
E 12
I 12
	    larnmaze larnopts larn.help \
E 12
	    ${DESTDIR}/usr/share/games/larn)
E 9
E 6
E 2

D 2
larn: larn12.0
larn12.0: $(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -o larn12.0 $(TERMLIB)
	size larn12.0
E 2
I 2
D 9
all: larn
E 2

D 2
all: larn install
E 2
I 2
D 6
larn: $(OBJS) ${LIBC}
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(TERMLIB)
E 6
I 6
larn: ${OBJS} ${LIBC}
D 8
	${CC} ${CFLAGS} ${OBJS} -o $@ -ltermcap
E 8
I 8
	${CC} ${CFLAGS} ${OBJS} -o $@ -ltermcap -lcompat
E 8
E 6
E 2

D 2
.c.o:	$<
	$(CC) -c $(FLAGS) $*.c
	chmod 0600 $*.o
E 2
I 2
D 6
install:
E 6
I 6
install: ${MAN}
E 6
D 4
	-mkdir ${DESTDIR}/usr/games/lib/larnfiles
	chmod 777 ${DESTDIR}/usr/games/lib/larnfiles
	install -s -o bin -g bin -m 755 larn ${DESTDIR}/usr/games/larn
	install -c -o bin -g bin -m 444 .larn.help ${DESTDIR}/usr/games/lib/larnfiles
	install -c -o bin -g bin -m 444 .larnmaze ${DESTDIR}/usr/games/lib/larnfiles
	install -c -o bin -g bin -m 444 .larnopts ${DESTDIR}/usr/games/lib/larnfiles
	install -c -o bin -g bin -m 444 .lfortune ${DESTDIR}/usr/games/lib/larnfiles
E 4
I 4
D 5
	-mkdir ${DESTDIR}/usr/games/lib/larnfiles > /dev/null 2>&1
E 5
I 5
	-[ -d ${DESTDIR}/usr/games/lib/larnfiles ] || mkdir ${DESTDIR}/usr/games/lib/larnfiles
E 5
	chmod 700 ${DESTDIR}/usr/games/lib/larnfiles
	chown games.src ${DESTDIR}/usr/games/lib/larnfiles
	install -s -o games -g bin -m 4700 larn ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f larn; ln -s dm larn; chown games.bin larn)
D 7
	install -c -o games -g bin -m 444 .larn.help ${DESTDIR}/usr/games/lib/larnfiles
	install -c -o games -g bin -m 444 .larnmaze ${DESTDIR}/usr/games/lib/larnfiles
	install -c -o games -g bin -m 444 .larnopts ${DESTDIR}/usr/games/lib/larnfiles
	install -c -o games -g bin -m 444 .lfortune ${DESTDIR}/usr/games/lib/larnfiles
E 7
I 7
	install -c -o games -g bin -m 444 larnmaze larnopts lfortune \
		larn.help ${DESTDIR}/usr/games/lib/larnfiles
E 7
E 4
E 2

D 2
$(OBJS): header.h
E 2
I 2
D 6
clean: FRC
E 6
I 6
clean:
E 6
	rm -f ${OBJS} core larn
E 2

D 2
install:
	if test ! -d $(LARNHOME) ; then mkdir $(LARNHOME); fi
	-chmod a+w $(LARNHOME)
	cp larn12.0 $(BINDIR)/larn
	cp $(DOTFILES) $(LARNHOME)
E 2
I 2
D 6
depend: FRC
E 6
I 6
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 6
	mkdep ${CFLAGS} ${SRCS}

D 6
lint: FRC
E 6
I 6
lint: ${SRCS}
E 6
	lint ${CFLAGS} ${SRCS}

D 6
tags: FRC
E 6
I 6
tags: ${SRCS}
E 6
	ctags ${SRCS}
E 9
I 9
.include <bsd.prog.mk>
E 9
D 6

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

main.o: main.c header.h /usr/include/pwd.h
object.o: object.c header.h
create.o: create.c header.h
tok.o: tok.c /usr/include/sys/types.h /usr/include/sys/ioctl.h
tok.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h header.h
display.o: display.c header.h
global.o: global.c header.h
data.o: data.c header.h
io.o: io.c header.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
io.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
io.o: /usr/include/varargs.h
monster.o: monster.c header.h
store.o: store.c header.h
diag.o: diag.c /usr/include/sys/types.h /usr/include/sys/times.h
diag.o: /usr/include/sys/stat.h header.h
help.o: help.c header.h
config.o: config.c header.h
nap.o: nap.c /usr/include/signal.h /usr/include/sys/types.h
nap.o: /usr/include/sys/timeb.h
bill.o: bill.c header.h
scores.o: scores.c /usr/include/sys/types.h /usr/include/sys/times.h
scores.o: /usr/include/sys/stat.h header.h
signal.o: signal.c /usr/include/signal.h header.h
moreobj.o: moreobj.c header.h
movem.o: movem.c header.h
regen.o: regen.c header.h
fortune.o: fortune.c /usr/include/sys/types.h /usr/include/sys/stat.h
fortune.o: /usr/include/fcntl.h header.h
savelev.o: savelev.c header.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 6
E 2
E 1
