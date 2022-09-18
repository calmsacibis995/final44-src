h49052
s 00001/00001/00045
d D 4.15 94/04/02 14:35:31 bostic 15 14
c typo
e
s 00001/00001/00045
d D 4.14 91/04/30 14:36:12 bostic 14 13
c move libdata/term into /usr/old
e
s 00014/00012/00032
d D 4.13 90/06/24 12:57:26 bostic 13 12
c make the dependencies right -- have to have a .o for each tabfoo.c file.
c The obvious approach, using mkdep -p, means that mktab would have the
c wrong dependency info.  From Chris Torek.
e
s 00004/00004/00040
d D 4.12 90/06/22 19:02:58 bostic 12 11
c reversed arguments, CTAGS not defined
e
s 00001/00005/00043
d D 4.11 90/06/08 14:40:46 bostic 11 10
c cleanup
e
s 00036/00078/00012
d D 4.10 90/05/11 14:24:39 bostic 10 9
c first pass for new make
e
s 00005/00036/00085
d D 4.9 89/05/11 10:06:08 bostic 9 8
c file reorg, pathnames.h, paths.h
e
s 00038/00032/00083
d D 4.8 89/02/28 04:04:42 donn 8 7
c This version will build terminal tables using any compiler, not just PCC.
e
s 00095/00041/00020
d D 4.7 87/06/18 22:17:45 bostic 7 6
c new template
e
s 00001/00004/00060
d D 4.6 86/05/15 06:48:30 lepreau 6 5
c "make links" must be done every time or else the links get broken & never remade
e
s 00002/00001/00062
d D 4.5 86/04/03 18:59:37 mckusick 5 4
c addition of nec25-t (from muller@nprdc.arpa (Keith Muller))
e
s 00001/00001/00062
d D 4.4 85/12/13 11:27:41 donn 4 3
c pass DESTDIR value to 'make links' during 'make install'
e
s 00002/00001/00061
d D 4.3 85/05/21 12:19:08 miriam 3 2
c include epson
e
s 00001/00001/00061
d D 4.2 83/08/15 12:17:32 root 2 1
c ignore error return from test ! -f .../tabtn300
c 	(karels)
e
s 00062/00000/00000
d D 4.1 83/08/05 13:34:29 sam 1 0
c date and time created 83/08/05 13:34:29 by sam
e
u
U
t
T
I 1
D 7
#	%M%	%I%	%E%
E 7
D 10
#
I 7
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W%	(Berkeley)	%G%
#
E 7
# Possible options:
D 7
#	make		compile source for terminal tables below
E 7
I 7
#	make		compile source for all terminal tables below
E 7
#	make <term>	compile table for a specific <term>
#	make install	move tables to ${DEST}
D 7
#	make links	make links for ease of documentation
E 7
#	make clean	remove tab*.o files lying around
D 7
ALL=	37 lpr 300 300-12 302 302-12 382 382-12 450 450-12 833 833-12 \
D 3
	itoh itoh12 nec nec12 nec-t qume qume12 xerox xerox12 \
E 3
I 3
D 5
	epson itoh itoh12 nec nec12 nec-t qume qume12 xerox xerox12 \
E 5
I 5
	epson itoh itoh12 nec nec12 nec-t nec25-t qume qume12 xerox xerox12 \
E 5
E 3
	x-ecs x-ecs12
DESTDIR=
E 7
I 7
D 8
CFLAGS=	-O
E 8
I 8
CFLAGS=	-I../common_source
E 8
LIBC=	/lib/libc.a
E 7
D 9
DEST=	${DESTDIR}/usr/lib/term
E 9
I 9
DEST=	${DESTDIR}/usr/libdata/term
E 9
I 7
SRCS=	tab300-12.c tab300.c tab302-12.c tab302.c tab37.c tab382-12.c \
	tab382.c tab450-12.c tab450.c tab833-12.c tab833.c tabepson.c \
	tabitoh.c tabitoh12.c tablpr.c tabnec-t.c tabnec.c tabnec12.c \
	tabnec25-t.c tabqume.c tabqume12.c tabx-ecs.c tabx-ecs12.c \
	tabxerox.c tabxerox12.c
OBJS=	tab300-12.o tab300.o tab302-12.o tab302.o tab37.o tab382-12.o \
	tab382.o tab450-12.o tab450.o tab833-12.o tab833.o tabepson.o \
	tabitoh.o tabitoh12.o tablpr.o tabnec-t.o tabnec.o tabnec12.o \
	tabnec25-t.o tabqume.o tabqume12.o tabx-ecs.o tabx-ecs12.o \
	tabxerox.o tabxerox12.o
D 8
ALL=	37 lpr 300 300-12 302 302-12 382 382-12 450 450-12 833 833-12 \
	epson itoh itoh12 nec nec12 nec-t nec25-t qume qume12 xerox \
	xerox12 x-ecs x-ecs12
E 8
I 8
ALL=	tab37 tablpr tab300 tab300-12 tab302 tab302-12 tab382 tab382-12 \
	tab450 tab450-12 tab833 tab833-12 tabepson tabitoh tabitoh12 \
	tabnec tabnec12 tabnec-t tabnec25-t tabqume tabqume12 tabxerox \
	tabxerox12 tabx-ecs tabx-ecs12
E 10
I 10
#	%W% (Berkeley) %G%
E 10
E 8
E 7

D 7
all:	${ALL}
E 7
I 7
D 10
all: ${ALL}
E 10
I 10
D 13
CFLAGS=	-I${.CURDIR}/../common_source
LIBC=	/usr/lib/libc.a
E 13
I 13
CFLAGS+=-I${.CURDIR}/../common_source
E 13
D 14
DEST=	/usr/libdata/term
E 14
I 14
DEST=	/usr/old/libdata/term
E 14
PROGS=	tab300 tab300-12 tab302 tab302-12 tab37 tab382 tab382-12 tab450 \
	tab450-12 tab833 tab833-12 tabepson tabitoh tabitoh12 tablpr \
	tabnec tabnec-t tabnec12 tabnec25-t tabqume tabqume12 tabx-ecs \
	tabx-ecs12 tabxerox tabxerox12
D 13
OBJS=	${PROGS:=.o}
SRCS=	${PROGS:=.c}
E 13
I 13
OBJS=	${PROGS:=.o} mktab.o
SRCS=	${PROGS:=.c} mktab.c
E 13
LINKS=	${DEST}/tablpr ${DEST}/tabtn300 ${DEST}/tablpr ${DEST}/tabcrt \
D 12
	${DEST}/tab302 ${DEST}/tab300s ${DEST}/tab300s-12 ${DEST}/tab302-12 \
	${DEST}/tabdtc ${DEST}/tab302 ${DEST}/tabdtc12 ${DEST}/tab302-12 \
	${DEST}/tabipsi ${DEST}/tab450 ${DEST}/tabipsi12 ${DEST}/tab450-12
E 12
I 12
	${DEST}/tab302 ${DEST}/tab300s ${DEST}/tab302-12 ${DEST}/tab300s-12 \
	${DEST}/tab302 ${DEST}/tabdtc ${DEST}/tab302-12 ${DEST}/tabdtc12 \
	${DEST}/tab450 ${DEST}/tabipsi ${DEST}/tab450-12 ${DEST}/tabipsi12
I 13
BINMODE=444
NOMAN=	noman
E 13
E 12
E 10
E 7

D 7
37:	tab37.o
lpr:	tablpr.o
300:	tab300.o code.300
300-12:	tab300-12.o code.300
302:	tab302.o code.300
302-12:	tab302-12.o code.300
382:	tab382.o code.300
382-12: tab382-12.o code.300
450:	tab450.o code.300
450-12:	tab450-12.o code.300
833:	tab833.o code.aj833
833-12: tab833-12.o code.aj833
I 3
epson:	tabepson.o
E 3
itoh:	tabitoh.o code.itoh
itoh12: tabitoh12.o code.itoh
nec:	tabnec.o code.nec
nec12:	tabnec12.o code.nec
nec-t:	tabnec-t.o
I 5
nec25-t:tabnec25-t.o
E 5
qume:	tabqume.o
qume12:	tabqume12.o
xerox:	tabxerox.o code.xerox
xerox12:tabxerox12.o code.xerox
x-ecs:	tabx-ecs.o code.x-ecs
x-ecs12:tabx-ecs12.o code.x-ecs
E 7
I 7
D 8
37:		tab37.o
lpr:		tablpr.o
300:		tab300.o 
300-12:		tab300-12.o 
302:		tab302.o 
302-12:		tab302-12.o 
382:		tab382.o 
382-12:		tab382-12.o 
450:		tab450.o 
450-12:		tab450-12.o 
833:		tab833.o 
833-12:		tab833-12.o 
epson:		tabepson.o
itoh:		tabitoh.o 
itoh12:		tabitoh12.o 
nec:		tabnec.o 
nec12:		tabnec12.o 
nec-t:		tabnec-t.o
nec25-t:	tabnec25-t.o
qume:		tabqume.o
qume12:		tabqume12.o
xerox:		tabxerox.o 
xerox12:	tabxerox12.o 
x-ecs:		tabx-ecs.o 
x-ecs12:	tabx-ecs12.o 
E 8
I 8
D 10
tab37:		mktab.o tab37.o
tablpr:		mktab.o tablpr.o
tab300:		mktab.o tab300.o 
tab300-12:	mktab.o tab300-12.o 
tab302:		mktab.o tab302.o 
tab302-12:	mktab.o tab302-12.o 
tab382:		mktab.o tab382.o 
tab382-12:	mktab.o tab382-12.o 
tab450:		mktab.o tab450.o 
tab450-12:	mktab.o tab450-12.o 
tab833:		mktab.o tab833.o 
tab833-12:	mktab.o tab833-12.o 
tabepson:	mktab.o tabepson.o
tabitoh:	mktab.o tabitoh.o 
tabitoh12:	mktab.o tabitoh12.o 
tabnec:		mktab.o tabnec.o 
tabnec12:	mktab.o tabnec12.o 
tabnec-t:	mktab.o tabnec-t.o
tabnec25-t:	mktab.o tabnec25-t.o
tabqume:	mktab.o tabqume.o
tabqume12:	mktab.o tabqume12.o
tabxerox:	mktab.o tabxerox.o 
tabxerox12:	mktab.o tabxerox12.o 
tabx-ecs:	mktab.o tabx-ecs.o 
tabx-ecs12:	mktab.o tabx-ecs12.o 
E 10
I 10
all: ${PROGS}
E 10
E 8
E 7

I 8
D 10
${ALL}:
	${CC} mktab.o $@.o -o mktab
E 10
I 10
D 13
${PROGS}: mktab.o ${.CURDIR}/${.PREFIX.c}
	${CC} mktab.o ${.CURDIR}/${.PREFIX}.c -o mktab
E 10
	./mktab > $@
E 13
I 13
${PROGS}: mktab.o ${.PREFIX}.o
	${CC} mktab.o ${.PREFIX}.o -o mktab
	./mktab > ${.TARGET}
E 13

E 8
D 7
install:
E 7
I 7
D 10
clean: FRC
D 8
	rm -f ${OBJS} core
E 8
I 8
	rm -f ${OBJS} ${ALL} mktab.o mktab core
E 10
I 10
D 13
clean:
	rm -f ${OBJS} ${PROGS} mktab.o mktab a.out Errs errs mklog core
E 13
I 13
clean::
	rm -f ${OBJS} ${PROGS} mktab a.out Errs errs mklog core
E 13
E 10
E 8

I 9
D 13
cleandir: clean
E 13
I 13
cleandir:: clean
E 13
D 10
	rm -f ${MAN} tags .depend
E 10
I 10
	rm -f ${.CURDIR}/tags .depend
E 10

E 9
D 10
depend: FRC
	mkdep ${CFLAGS} ${SRCS}
E 10
I 10
D 13
depend: ${SRCS}
E 13
I 13
depend: .depend
.depend: ${SRCS} mktab.c
E 13
	mkdep ${CFLAGS:M-[ID]*} ${.ALLSRC}
E 10

D 10
install: FRC
E 7
D 8
	for file in tab*.o; do \
D 7
		install -s -m 755 $$file ${DEST}/`basename $$file .o`;\
E 7
I 7
		install -s -o bin -g bin -m 755 $$file ${DEST}/`basename $$file .o`; \
E 8
I 8
D 9
	-mkdir ${DEST}
	for file in ${ALL}; do \
		install -c -o bin -g bin -m 755 $$file ${DEST}/$$file; \
E 8
E 7
	done
E 9
I 9
	install -c -o bin -g bin -m 755 ${ALL} ${DEST}
E 9
D 2
	if test ! -f ${DEST}/tabtn300; \
E 2
I 2
D 6
	-if test ! -f ${DEST}/tabtn300; \
E 2
	then \
D 4
		make links; \
E 4
I 4
		make DESTDIR=${DESTDIR} links; \
E 4
	fi
E 6
I 6
D 7
	make DESTDIR=${DESTDIR} links
E 6
	install -c -m 644 README ${DEST}/README

links:
E 7
	rm -f ${DEST}/tabtn300; ln ${DEST}/tablpr ${DEST}/tabtn300
	rm -f ${DEST}/tabcrt; ln ${DEST}/tablpr ${DEST}/tabcrt
	rm -f ${DEST}/tab300s; ln ${DEST}/tab302 ${DEST}/tab300s
	rm -f ${DEST}/tab300s-12; ln ${DEST}/tab302-12 ${DEST}/tab300s-12
	rm -f ${DEST}/tabdtc; ln ${DEST}/tab302 ${DEST}/tabdtc
	rm -f ${DEST}/tabdtc12; ln ${DEST}/tab302-12 ${DEST}/tabdtc12
	rm -f ${DEST}/tabipsi; ln ${DEST}/tab450 ${DEST}/tabipsi
	rm -f ${DEST}/tabipsi12; ln ${DEST}/tab450-12 ${DEST}/tabipsi12
I 7
	install -c -o bin -g bin -m 644 README ${DEST}/README
E 10
I 10
D 11
install: maninstall
E 10
E 7

D 7
clean:
	rm -f tab*.o errs
E 7
I 7
D 10
lint: FRC
	lint ${CFLAGS} ${SRCS}
E 10
I 10
maninstall: beforeinstall
E 10

E 11
D 10
tags: FRC
	ctags ${SRCS}
E 10
I 10
beforeinstall:
	install -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} ${PROGS} \
	    ${DESTDIR}${DEST}
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/README \
	    ${DESTDIR}${DEST}
E 10

D 10
FRC:
E 10
I 10
lint: ${SRCS}
	${LINT} ${LINTFLAGS} ${CFLAGS} ${.ALLSRC}

tags: ${SRCS}
D 12
	${CTAGS} -f ${.CURDIR}/tags ${.ALLSRC}
E 12
I 12
D 13
	ctags -f ${.CURDIR}/tags ${.ALLSRC}
E 13
I 13
D 15
	${CTAGS} -f ${.CURDIR}/tags ${.ALLSRC}
E 15
I 15
	ctags -f ${.CURDIR}/tags ${.ALLSRC}
E 15
E 13
E 12

D 11
.include <bsd.own.mk>
E 11
I 11
.include <bsd.prog.mk>
E 11
E 10
D 9

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

tab300-12.o: tab300-12.c code.300
tab300.o: tab300.c code.300
tab302-12.o: tab302-12.c code.300
tab302.o: tab302.c code.300
tab37.o: tab37.c
tab382-12.o: tab382-12.c code.300
tab382.o: tab382.c code.300
tab450-12.o: tab450-12.c code.300
tab450.o: tab450.c code.300
tab833-12.o: tab833-12.c code.aj833
tab833.o: tab833.c code.aj833
tabepson.o: tabepson.c
tabitoh.o: tabitoh.c code.itoh
tabitoh12.o: tabitoh12.c code.itoh
tablpr.o: tablpr.c
tabnec-t.o: tabnec-t.c
tabnec.o: tabnec.c code.nec
tabnec12.o: tabnec12.c code.nec
tabnec25-t.o: tabnec25-t.c
tabqume.o: tabqume.c
tabqume12.o: tabqume12.c
tabx-ecs.o: tabx-ecs.c code.x-ecs
tabx-ecs12.o: tabx-ecs12.c code.x-ecs
tabxerox.o: tabxerox.c code.xerox
tabxerox12.o: tabxerox12.c code.xerox

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 9
E 7
E 1
