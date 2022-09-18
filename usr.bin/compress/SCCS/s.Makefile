h05604
s 00001/00000/00011
d D 8.2 94/04/17 09:06:44 bostic 18 17
c move zopen(3) out of the C library, to here
c the interface is wrong for the C library, and I don't have time to fix it
e
s 00000/00000/00011
d D 8.1 93/06/06 14:29:04 bostic 17 16
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00011
d D 5.16 92/12/02 19:15:50 bostic 16 15
c remove -g flag
e
s 00006/00009/00006
d D 5.15 92/12/02 18:17:42 bostic 15 14
c new versions, based on Diomidis Spinellis' work on zopen(3).
e
s 00005/00010/00010
d D 5.14 90/06/25 16:48:00 bostic 14 13
c just wire in USERMEM value
e
s 00002/00001/00018
d D 5.13 90/05/17 16:12:57 bostic 13 12
c get USERMEM right
e
s 00011/00055/00008
d D 5.12 90/05/11 14:23:06 bostic 12 11
c first pass for new make
e
s 00001/00001/00062
d D 5.11 89/07/20 11:55:29 bostic 11 10
c needs compat library
e
s 00008/00006/00055
d D 5.10 89/05/11 10:48:23 bostic 10 9
c file reorg, pathnames.h, paths.h
e
s 00033/00026/00028
d D 5.9 88/10/15 08:59:19 bostic 9 8
c cleanup, add man page, cleandir
e
s 00002/00002/00052
d D 5.8 87/06/18 15:29:14 mckusick 8 7
c must put back USERMEM
e
s 00041/00015/00013
d D 5.7 87/06/16 17:27:42 bostic 7 6
c new template
e
s 00002/00000/00026
d D 5.6 87/05/31 21:07:27 bostic 6 5
c added depend labels
e
s 00004/00001/00022
d D 5.5 85/09/18 05:07:59 lepreau 5 4
c temp hack since usermem fails when chroot'ed to nbsd: don't clean USERMEM
e
s 00002/00003/00021
d D 5.4 85/09/17 16:15:50 lepreau 4 3
c compress 4.0 deleted warning about -O
e
s 00001/00001/00023
d D 5.3 85/06/17 17:57:12 edward 3 2
c use install -s
e
s 00001/00001/00023
d D 5.2 85/06/06 18:51:14 mckusick 2 1
c moves from local to ucb
e
s 00024/00000/00000
d D 5.1 85/06/06 18:46:10 mckusick 1 0
c 4.3 beta version
e
u
U
t
T
I 1
D 12
#
D 7
#	%W% (Berkeley) %G%
E 7
I 7
D 9
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 9
I 9
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 9
E 7
#
D 4
# if you have bugs in your C compiler dont use -O
E 4
D 7
COMFLAGS=-DBSD4_2 -O -DSACREDMEM=256000
D 2
BIN=${DESTDIR}/usr/local
E 2
I 2
BIN=${DESTDIR}/usr/ucb
E 7
I 7
D 9
#	%W%	(Berkeley)	%G%
E 9
I 9
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
E 9
#
E 12
I 9
#	%W% (Berkeley) %G%
D 12
#
E 9
D 8
CFLAGS=	-O -DBSD4_2 -DSACREDMEM=256000
E 8
I 8
CFLAGS=	-O -DBSD4_2 -DSACREDMEM=256000 -DUSERMEM=`cat USERMEM` 
E 8
LIBC=	/lib/libc.a
SRCS=	compress.c
D 9
OBJS=	compress.o
E 9
I 9
OBJS=
MAN=	compress.0
E 12
E 9
E 7
E 2

I 14
D 15
# USERMEM should be the amount of available user memory in bytes.
# Set it to zero, for physical memory less than 1 Meg.
USERMEM=4194304

E 15
E 14
D 4
compress : compress.c USERMEM
E 4
I 4
D 7
compress: compress.c USERMEM
E 4
	cc $(COMFLAGS) -DUSERMEM=`cat USERMEM` -o compress compress.c
E 7
I 7
D 12
all: compress
E 12
I 12
PROG=	compress
I 18
SRCS=	compress.c zopen.c
E 18
D 13
CFLAGS+=-DBSD4_2 -DSACREDMEM=256000 -DUSERMEM=`cat USERMEM`
E 13
I 13
D 14
MEM!=cat ${.CURDIR}/USERMEM
CFLAGS+=-DBSD4_2 -DSACREDMEM=256000 -DUSERMEM=${MEM}
E 14
I 14
D 15
CFLAGS+=-DBSD4_2 -DSACREDMEM=256000 -DUSERMEM=${USERMEM}
E 14
E 13
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
LINKS=	${BINDIR}/compress ${BINDIR}/uncompress \
	${BINDIR}/compress ${BINDIR}/zcat
E 15
I 15
D 16
CFLAGS=	-g
E 16
LINKS=	${BINDIR}/compress ${BINDIR}/uncompress
E 15
MLINKS=	compress.1 uncompress.1 compress.1 zcat.1
I 15

afterinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/zcat.sh ${DESTDIR}/usr/bin/zcat
E 15
E 12
E 7
D 14

I 7
D 9
compress: USERMEM ${OBJS} ${LIBC}
D 8
	${CC} ${CFLAGS} -DUSERMEM=`cat USERMEM` -o $@ ${OBJS}
E 8
I 8
	${CC} ${CFLAGS} -o $@ ${OBJS}
E 9
I 9
D 12
compress: USERMEM ${LIBC}
D 11
	${CC} ${CFLAGS} -o $@ $@.c
E 11
I 11
	${CC} ${CFLAGS} -o $@ $@.c -lcompat
E 12
I 12
all: USERMEM
E 12
E 11
E 9
E 8

E 7
# USERMEM may have to be set by hand.  It should contain the amount of
# available user memory in bytes.  Set it to zero, for physical memory
# less than 1 Meg.
D 9
USERMEM:
E 9
I 9
D 12
USERMEM: FRC
E 9
	sh usermem.sh > USERMEM
E 12
I 12
USERMEM: ${.CURDIR}/usermem.sh
	sh ${.CURDIR}/usermem.sh > USERMEM
E 14
E 12

D 7
install: compress
D 3
	cp compress $(BIN)
E 3
I 3
	install -s compress $(BIN)
E 3
	rm -f $(BIN)/uncompress $(BIN)/zcat
	ln $(BIN)/compress $(BIN)/uncompress
	ln $(BIN)/compress $(BIN)/zcat

E 7
I 5
D 9
# Temporarily don't delete USERMEM.  When chroot'ed to /nbsd, usermem.sh
# fails totally.
E 5
D 7
clean:
D 4
	rm -f compress USERMEM
E 4
I 4
D 5
	rm -f compress USERMEM core errs
E 5
I 5
	rm -f compress core errs
#	rm -f compress USERMEM core errs
E 7
I 7
clean: FRC
E 9
I 9
D 12
clean:
E 9
	rm -f ${OBJS} core compress
D 9
#	rm -f ${OBJS} core compress USERMEM
E 9
E 7
I 6

D 7
depend:
E 7
I 7
D 9
depend: FRC
	mkdep ${CFLAGS} ${SRCS}
E 9
I 9
cleandir: clean
	rm -f ${MAN} tags .depend
E 9

D 9
install: FRC
E 9
I 9
depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
E 9
D 10
	install -s -o bin -g bin -m 755 compress ${DESTDIR}/usr/ucb/compress
	rm -f ${DESTDIR}/usr/ucb/uncompress ${DESTDIR}/usr/ucb/zcat
	ln ${DESTDIR}/usr/ucb/compress ${DESTDIR}/usr/ucb/uncompress
	ln ${DESTDIR}/usr/ucb/compress ${DESTDIR}/usr/ucb/zcat
I 9
	rm -f ${DESTDIR}/usr/man/cat1/uncompress.0 ${DESTDIR}/usr/man/cat1/zcat.0
E 10
I 10
	install -s -o bin -g bin -m 755 compress ${DESTDIR}/usr/bin
	rm -f ${DESTDIR}/usr/bin/uncompress ${DESTDIR}/usr/bin/zcat
	ln ${DESTDIR}/usr/bin/compress ${DESTDIR}/usr/bin/uncompress
	ln ${DESTDIR}/usr/bin/compress ${DESTDIR}/usr/bin/zcat
	rm -f ${DESTDIR}/usr/man/cat1/uncompress.0 \
	    ${DESTDIR}/usr/man/cat1/zcat.0
E 10
	install -c -o bin -g bin -m 444 compress.0 ${DESTDIR}/usr/man/cat1
D 10
	ln ${DESTDIR}/usr/man/cat1/compress.0 ${DESTDIR}/usr/man/cat1/uncompress.0
E 10
I 10
	ln ${DESTDIR}/usr/man/cat1/compress.0 \
	    ${DESTDIR}/usr/man/cat1/uncompress.0
E 10
	ln ${DESTDIR}/usr/man/cat1/compress.0 ${DESTDIR}/usr/man/cat1/zcat.0
E 9

D 9
lint: FRC
E 9
I 9
lint: ${SRCS}
E 9
	lint ${CFLAGS} ${SRCS}

D 9
tags: FRC
E 9
I 9
tags: ${SRCS}
E 9
	ctags ${SRCS}

FRC:
E 12
I 12
.include <bsd.prog.mk>
E 12
D 9

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

compress.o: compress.c /usr/include/stdio.h /usr/include/ctype.h
compress.o: /usr/include/signal.h /usr/include/sys/types.h
compress.o: /usr/include/sys/stat.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 9
E 7
E 6
E 5
E 4
E 1
