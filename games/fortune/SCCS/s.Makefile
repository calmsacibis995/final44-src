h16717
s 00000/00000/00015
d D 8.1 93/05/31 17:16:46 bostic 16 15
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00014
d D 5.6 91/04/27 16:12:04 bostic 15 14
c typo
e
s 00004/00000/00011
d D 5.5 91/04/27 16:07:11 bostic 14 13
c add datfiles to clean list
e
s 00007/00047/00004
d D 5.4 91/04/27 16:03:33 bostic 13 12
c break up into separate directories
e
s 00001/00001/00050
d D 5.3 91/03/12 08:46:23 bostic 12 11
c re_comp, re_exec moved to libcompat
e
s 00005/00002/00046
d D 5.2 90/06/26 14:32:51 bostic 11 10
c need -x file for obscene fortunes
e
s 00031/00055/00017
d D 5.1 90/05/11 12:48:13 bostic 10 9
c first pass for new make
e
s 00008/00008/00064
d D 1.8 89/09/07 16:56:03 bostic 9 8
c new version that installs obscene fortunes
e
s 00046/00044/00026
d D 1.7 89/09/07 16:41:58 bostic 8 7
c update Makefile for new version of fortune
e
s 00002/00002/00068
d D 1.6 89/03/05 20:31:24 bostic 7 6
c remove FRC label
e
s 00009/00017/00061
d D 1.5 88/10/19 20:32:47 bostic 6 5
c cleanup, add manual page
e
s 00002/00002/00076
d D 1.4 87/09/20 12:06:42 bostic 5 4
c owned by games, mode 755
e
s 00001/00004/00077
d D 1.3 87/08/30 09:12:20 bostic 4 3
c better fix for chmod problem; bug report 4.3BSD/games/8
e
s 00050/00042/00031
d D 1.2 87/06/06 14:54:59 bostic 3 1
c new template
e
s 00050/00042/00031
d R 1.2 87/06/03 13:51:09 bostic 2 1
c new template
e
s 00073/00000/00000
d D 1.1 87/06/03 12:22:12 bostic 1 0
c date and time created 87/06/03 12:22:12 by bostic
e
u
U
t
T
I 1
D 3
FORTUNES=	scene obscene
SOURCE=		fortune.c strfile.h strfile.c rnd.c unstr.c $(FORTUNES)
TFILES=		Troff.mac Troff.sed Do_troff
LIBDIR=		/usr/games/lib
BINDIR=		/usr/games
OWN=		arnold
GRP=		arpa
DEFS=
CFLAGS=		-O $(DEFS)
SFLAGS=		-r
TDEV=		-Pver
TROFF=		ditroff $(TDEV)
DESTDIR=
E 3
I 3
D 10
#
D 8
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 8
I 8
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
E 8
#
D 8
#	%W%	(Berkeley)	%G%
E 8
I 8
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
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 8
#
E 10
I 8
#	%W% (Berkeley) %G%
D 10
#
E 8
CFLAGS=	-O
LIBC=	/lib/libc.a
E 10
I 10

D 13
PROGS=	fortune strfile unstr
E 10
D 8
SFLAGS=	-r
TDEV=	-Pver
TROFF=	ditroff ${TDEV}
SRCS=	fortune.c rnd.c strfile.c unstr.c
E 8
I 8
SRCS=	fortune.c strfile.c unstr.c
D 10
OBJS=
E 8
I 6
MAN=	fortune.0
E 10
I 10
MAN6=	fortune.0
BINOWN=	games
D 11
DATFILES=fortunes.dat fortunes-o.dat startrek.dat zippy.dat
E 11
I 11
DATFILES=fortunes.dat startrek.dat zippy.dat fortunes-o.dat
E 11
.PATH:	${.CURDIR} ${.CURDIR}/datfiles
I 11
CLEANFILES+=strfile unstr
E 13
I 13
SUBDIR=	fortune
E 13
E 11
E 10
E 6
E 3

I 14
D 15
.ifmake (clean) || ifmake (cleandir)
E 15
I 15
.ifmake (clean) || (cleandir)
E 15
SUBDIR+=datfiles
.endif

E 14
D 8
all: fortune strfile unstr fortunes.dat
E 8
I 8
D 10
all: fortune strfile # unstr
E 10
I 10
D 13
all: ${PROGS} ${MAN6} ${DATFILES}
E 13
I 13
.ifmake !(install)
SUBDIR+=strfile
.else
SUBDIR+=datfiles
.endif
E 13
E 10
E 8

D 3
fortune: fortune.o rnd.o
	$(CC) $(CFLAGS) -o fortune fortune.o rnd.o
E 3
I 3
D 8
fortune: fortune.o rnd.o ${LIBC}
	${CC} ${CFLAGS} -o $@ fortune.o rnd.o
E 8
I 8
D 10
fortune: ${LIBC}
	${CC} ${CFLAGS} -o $@ $@.c
E 10
I 10
D 13
${PROGS}: ${LIBC} ${.PREFIX}.c
D 12
	${CC} ${CFLAGS} -o ${.TARGET} ${.CURDIR}/${.PREFIX}.c
E 12
I 12
	${CC} ${CFLAGS} -o ${.TARGET} ${.CURDIR}/${.PREFIX}.c -lcompat
E 12
E 10
E 8
E 3

D 3
strfile: strfile.o rnd.o
	$(CC) $(CFLAGS) -o strfile strfile.o rnd.o
E 3
I 3
D 8
strfile: strfile.o rnd.o ${LIBC}
	${CC} ${CFLAGS} -o $@ strfile.o rnd.o
E 8
I 8
D 10
strfile: ${LIBC}
	${CC} ${CFLAGS} -o $@ $@.c
E 10
I 10
D 11
${DATFILES}: ${.TARGET:R}
E 11
I 11
fortunes-o.dat: ${.TARGET:R}
	./strfile -rsx ${.CURDIR}/datfiles/${.TARGET:R} ${.TARGET}
fortunes.dat startrek.dat zippy.dat: ${.TARGET:R}
E 11
	./strfile -rs ${.CURDIR}/datfiles/${.TARGET:R} ${.TARGET}
E 10
E 8
E 3

D 3
unstr: unstr.o
	$(CC) $(CFLAGS) -o unstr unstr.o
E 3
I 3
D 8
unstr: unstr.o ${LIBC}
	${CC} ${CFLAGS} -o $@ unstr.o
E 8
I 8
D 10
unstr: ${LIBC}
	${CC} ${CFLAGS} -o $@ $@.c
E 8
E 3

E 10
D 3
fortune.o strfile.o unstr.o: strfile.h

E 3
D 8
fortunes.dat: fortunes strfile
D 3
	./strfile $(SFLAGS) fortunes
E 3
I 3
	./strfile ${SFLAGS} fortunes
E 3

D 3
fortunes: $(FORTUNES)
E 3
I 3
fortunes: scene obscene
E 3
D 4
	cp scene fortunes
I 3
	chmod 666 fortunes
E 3
	echo "%-" >> fortunes
	cat obscene >> fortunes
E 4
I 4
	(cat scene; echo "%-"; cat obscene) > fortunes
E 4

E 8
D 3
lint:
	lint -hxb $(DEFS) fortune.c rnd.c 2>&1 > fortune.lint
	lint -hxb $(DEFS) strfile.c rnd.c 2>&1 > strfile.lint
	lint -hxb $(DEFS) unstr.c 2>&1 > unstr.lint
E 3
I 3
D 7
clean: FRC
E 7
I 7
clean:
E 7
D 8
	rm -f fortune fortunes fortunes.dat strfile unstr core *.o
	rm -f Oscene Oobscene
E 8
I 8
D 10
	rm -f fortune strfile unstr core *.dat
E 10
I 10
	rm -f ${PROGS} core *.dat
E 10
E 8
E 3

D 3
install: all install.data
	install -s -m 4711 -o daemon fortune $(DESTDIR)$(BINDIR)
E 3
I 3
D 6
depend: FRC
E 6
I 6
cleandir: clean
D 10
	rm -f ${MAN} tags .depend
E 10
I 10
	rm -f ${MAN6} tags .depend
E 10

depend: ${SRCS}
E 6
D 8
	mkdep ${CFLAGS} ${SRCS}
E 8
I 8
D 10
	mkdep -p ${CFLAGS} ${SRCS}
E 10
I 10
	mkdep -p ${CFLAGS} ${.ALLSRC}
E 10
E 8
E 3

D 3
install.data: fortunes.dat
	install -m 600 -o daemon fortunes.dat $(DESTDIR)$(LIBDIR)
E 3
I 3
D 6
install: FRC
E 6
I 6
D 10
install: ${MAN}
E 6
D 5
	install -s -o bin -g bin -m 4711 fortune ${DESTDIR}/usr/games
	install -o bin -g bin -m 600 fortunes.dat ${DESTDIR}/usr/games/lib
E 5
I 5
	install -s -o games -g bin -m 4755 fortune ${DESTDIR}/usr/games
D 8
	install -o games -g bin -m 600 fortunes.dat ${DESTDIR}/usr/games/lib
I 6
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
E 8
I 8
	install -c -o bin -g bin -m 444 fortune.0 ${DESTDIR}/usr/man/cat6
	./strfile -rs fortunes
	./strfile -rs startrek
	./strfile -rs zippy
	install -c -o bin -g bin -m 444 fortunes startrek zippy \
E 10
I 10
install:
	install ${STRIP} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} fortune \
	    ${DESTDIR}/usr/games
	install -c -o ${MANOWN} -g ${MANGRP} -m ${MANMODE} fortune.0 \
	    ${DESTDIR}/usr/share/man/cat6
	(cd ${.CURDIR}/datfiles; install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
	    ${DATFILES:R} ${DESTDIR}/usr/share/games/fortune)
	install -o ${BINOWN} -g ${BINGRP} -m 444 ${DATFILES} \
E 10
	    ${DESTDIR}/usr/share/games/fortune
D 10
	install -o bin -g bin -m 444 fortunes.dat startrek.dat zippy.dat \
	    ${DESTDIR}/usr/share/games/fortune
D 9
	./strfile -rsx noobscene
	install -c -o bin -g bin -m 444 noobscene \
	    ${DESTDIR}/usr/share/games/fortune/fortunes-o
	install -o bin -g bin -m 444 noobscene.dat \
	    ${DESTDIR}/usr/share/games/fortune/fortunes-o.dat
#	./strfile -rsx fortunes-o.rot
#	install -c -o bin -g bin -m 444 fortunes-o.rot \
E 9
I 9
#	./strfile -rsx noobscene
#	install -c -o bin -g bin -m 444 noobscene \
E 9
#	    ${DESTDIR}/usr/share/games/fortune/fortunes-o
D 9
#	install -o bin -g bin -m 444 fortunes-o.rot.dat \
E 9
I 9
#	install -o bin -g bin -m 444 noobscene.dat \
E 9
#	    ${DESTDIR}/usr/share/games/fortune/fortunes-o.dat
I 9
	./strfile -rsx fortunes-o.rot
	install -c -o bin -g bin -m 444 fortunes-o.rot \
	    ${DESTDIR}/usr/share/games/fortune/fortunes-o
	install -o bin -g bin -m 444 fortunes-o.rot.dat \
	    ${DESTDIR}/usr/share/games/fortune/fortunes-o.dat
E 10
E 9
E 8
E 6
E 5
E 3

D 3
troff: troff.scene troff.obscene
E 3
I 3
D 6
lint: FRC
E 6
I 6
lint: ${SRCS}
E 6
D 8
	lint ${CFLAGS} fortune.c rnd.c
	lint ${CFLAGS} strfile.c rnd.c
E 8
I 8
D 10
	lint ${CFLAGS} fortune.c
	lint ${CFLAGS} strfile.c
E 8
	lint ${CFLAGS} unstr.c
E 10
I 10
	cd ${.CURDIR}; lint ${CFLAGS} ${LINTFLAGS} fortune.c
	cd ${.CURDIR}; lint ${CFLAGS} ${LINTFLAGS} strfile.c
	cd ${.CURDIR}; lint ${CFLAGS} ${LINTFLAGS} unstr.c
E 10
E 3

D 3
troff.scene:
	./Do_troff scene $(TROFF)
E 3
I 3
D 6
tags: FRC
E 6
I 6
tags: ${SRCS}
E 6
D 10
	ctags ${SRCS}
E 10
I 10
	cd ${.CURDIR}; ctags fortune.c
	cd ${.CURDIR}; ctags strfile.c
	cd ${.CURDIR}; ctags unstr.c
	cd ${.CURDIR}; sort -o tags tags

.include <bsd.prog.mk>
E 13
I 13
.include <bsd.subdir.mk>
E 13
E 10
E 3
D 8

D 3
troff.obscene:
	./Do_troff obscene $(TROFF)
E 3
I 3
D 7
troff: FRC
E 7
I 7
troff:
E 7
	./Do_troff scene ${TROFF}
	./Do_troff obscene ${TROFF}
E 3

D 3
clean: sort.clean
	rm -f fortune fortunes fortunes.dat strfile unstr ? core *.o

E 3
sort: sort.scene sort.obscene

sort.scene: strfile unstr
	strfile -oi scene
	mv scene Oscene
	unstr -o scene

sort.obscene: strfile unstr
	strfile -oi obscene
	mv obscene Oobscene
	unstr -o obscene
E 8
D 6

D 3
sort.clean:
	rm -f Oscene Oobscene
E 3
I 3
FRC:
E 3

D 3
depend:
E 3
I 3
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

fortune.o: fortune.c /usr/include/sys/types.h /usr/include/stdio.h
fortune.o: /usr/include/sys/file.h strfile.h
rnd.o: rnd.c
strfile.o: strfile.c /usr/include/stdio.h /usr/include/ctype.h strfile.h
unstr.o: unstr.c /usr/include/stdio.h strfile.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 6
E 3
E 1
