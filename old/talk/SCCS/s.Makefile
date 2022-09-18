h18590
s 00003/00055/00003
d D 5.5 90/05/31 16:39:32 bostic 5 4
c pmake
e
s 00015/00004/00043
d D 5.4 89/07/30 12:08:15 bostic 4 3
c get SCCS id's back
e
s 00001/00001/00046
d D 5.3 89/07/30 12:07:19 bostic 3 2
c needs libcompat for gtty
e
s 00008/00002/00039
d D 5.2 89/05/11 13:49:48 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00041/00000/00000
d D 5.1 89/04/12 12:44:35 bostic 1 0
c date and time created 89/04/12 12:44:35 by bostic
e
u
U
t
T
I 1
D 5
#
D 4
# Copyright (c) 1983 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# Copyright (c) 1983, 1988 The Regents of the University of California.
# All rights reserved.
E 4
#
D 4
#	@(#)Makefile	5.1 (Berkeley) 6/6/85
E 4
I 4
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
#
E 5
#	%W% (Berkeley) %G%
E 4
D 5
#
DESTDIR=
DOBJECT=talkd.o announce.o process.o table.o print.o
TOBJECT=talk.o get_names.o display.o io.o ctl.o init_disp.o \
	msgs.o get_addrs.o ctl_transact.o invite.o look_up.o
DSOURCE=talkd.c announce.c process.c table.c print.c
TSOURCE=talk.c get_names.c display.c io.c ctl.c init_disp.c \
	msgs.c get_addrs.c ctl_transact.c invite.c look_up.c
INCLUDE=talk.h ctl.h talk_ctl.h
SOURCE= ${DSOURCE} ${TSOURCE}
CFLAGS= -O 
E 5

D 2
all:	talk talkd
E 2
I 2
D 5
all: talk talkd
E 5
I 5
SUBDIR=	talk talkd
E 5
E 2

D 5
talkd: ${DOBJECT}
	cc ${CFLAGS} -o talkd ${DOBJECT}

talk:	${TOBJECT}
D 3
	cc -o talk ${TOBJECT} -lcurses -ltermlib
E 3
I 3
	cc -o talk ${TOBJECT} -lcurses -ltermlib -lcompat
E 3

${DOBJECT}: ctl.h
${TOBJECT}: talk.h ctl.h talk_ctl.h

install: talk talkd
	install -g tty -m 2755 -s talk ${DESTDIR}/usr/old/talk
D 2
	install -s talkd ${DESTDIR}/etc/talkd
E 2
I 2
	install -s talkd ${DESTDIR}/usr/libexec/talkd
E 2

lint:
	lint ${DSOURCE}

clean:
	rm -f *.o talk talkd
I 2

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SOURCE}
	mkdep ${SOURCE}
E 2

tags:	${SOURCE} ${INCLUDE}
	ctags ${SOURCE} ${INCLUDE}
E 5
I 5
.include "../Makefile.inc"
.include <bsd.subdir.mk>
E 5
E 1
