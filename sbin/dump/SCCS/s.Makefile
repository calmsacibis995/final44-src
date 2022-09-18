h03041
s 00000/00000/00025
d D 8.1 93/06/05 10:53:06 bostic 38 37
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00002/00025
d D 5.16 92/07/15 09:52:27 bostic 37 36
c don't specify "all" target or it won't build the man page
e
s 00006/00007/00021
d D 5.15 92/06/20 15:28:28 mckusick 36 35
c get rid of leading `dump' on all the names
e
s 00001/00001/00027
d D 5.14 91/09/23 15:19:15 bostic 35 34
c MLINKS needs a section number
e
s 00010/00020/00018
d D 5.13 91/07/23 22:18:30 mckusick 34 33
c merge dump and rdump
e
s 00002/00002/00036
d D 5.12 91/03/07 17:55:41 mckusick 33 31
c need dependencies for dumprmain.o and dumprtape.o
e
s 00001/00000/00038
d R 5.12 91/01/15 14:07:29 bostic 32 31
c kernel reorg
e
s 00001/00000/00037
d D 5.11 90/07/01 10:46:55 bostic 31 30
c clean rdump files
e
s 00016/00054/00021
d D 5.10 90/05/11 13:05:43 bostic 30 29
c first pass for new make
e
s 00002/00002/00073
d D 5.9 89/05/11 13:52:26 bostic 29 28
c file reorg, pathnames.h, paths.h
e
s 00004/00001/00071
d D 5.8 89/03/06 08:27:22 bostic 28 27
c add cleandir lable
e
s 00024/00073/00048
d D 5.7 88/10/25 18:57:28 bostic 27 26
c cleanup, add man page
e
s 00090/00041/00031
d D 5.6 87/06/03 10:02:02 bostic 26 20
c new template
e
s 00090/00041/00031
d R 5.6 87/06/02 21:47:39 bostic 25 20
c new template
e
s 00090/00041/00031
d R 5.6 87/06/02 20:55:56 bostic 24 20
c new template
e
s 00089/00040/00032
d R 5.6 87/06/02 20:13:08 bostic 23 20
c new template
e
s 00089/00040/00032
d R 5.6 87/06/02 20:02:15 bostic 22 20
c new template
e
s 00088/00039/00033
d R 5.6 87/06/02 19:53:49 bostic 21 20
c new template
e
s 00002/00000/00070
d D 5.5 87/05/31 20:38:18 bostic 20 19
c added depend label
e
s 00002/00002/00068
d D 5.4 86/05/28 11:08:03 mckusick 19 18
c finally no longer need setuid root
e
s 00001/00001/00069
d D 5.3 85/10/15 21:01:13 mckusick 18 17
c fix comment (from sjk@sri-spam)
e
s 00002/00002/00068
d D 5.2 85/06/18 22:06:57 mckusick 17 15
c dumprestor.h moved to /usr/include/protocols/dumprestore.h
e
s 00002/00002/00068
d R 5.2 85/06/18 21:54:33 mckusick 16 15
c restore.h moves to /usr/include/protocols/dumprestore.h
e
s 00006/00001/00064
d D 5.1 85/05/06 11:36:10 dist 15 14
c Add copyright
e
s 00009/00004/00056
d D 1.14 85/02/19 16:26:22 mckusick 14 13
c dumptape.c and dumprtape.c have been merged
e
s 00002/00002/00058
d D 1.13 84/10/05 16:04:39 mckusick 13 12
c update install mode
e
s 00002/00002/00058
d D 1.12 83/07/03 20:22:03 sam 12 11
c include fix
e
s 00001/00001/00059
d D 1.11 83/06/12 02:43:56 sam 11 10
c new signals == no libjobs
e
s 00005/00003/00055
d D 1.10 83/02/11 12:58:17 sam 10 9
c merge from sun
e
s 00001/00003/00057
d D 1.9 82/10/11 18:05:00 mckusick 9 8
c rcmd.o moves to libc.a
e
s 00018/00008/00042
d D 1.8 82/10/05 15:03:40 sam 8 7
c merge rdump with dump
e
s 00003/00001/00047
d D 1.7 82/06/05 17:14:13 mckusick 7 6
c include /usr/src/ucb/netser/rcmd.o
e
s 00007/00007/00041
d D 1.6 82/05/20 15:10:58 sam 6 5
c convert to calder
e
s 00004/00003/00044
d D 1.5 82/05/07 15:27:35 sam 5 4
c old stuff
e
s 00010/00004/00037
d D 1.4 82/02/23 12:56:29 mckusic 4 3
c convert to new directory format
e
s 00001/00001/00040
d D 1.3 81/02/20 15:58:58 wnj 3 2
c Remove -DERNIE from the makefile (by Robert Henry)
e
s 00001/00003/00040
d D 1.2 80/10/18 17:56:02 bill 2 1
c install in /etc
e
s 00043/00000/00000
d D 1.1 80/10/13 17:30:22 root 1 0
c date and time created 80/10/13 17:30:22 by root
e
u
U
t
T
I 1
D 12
# sccsid = "%W% (Berkeley) %G%"
E 12
I 12
D 15
#	%M%	%I%	%E%
E 15
I 15
D 30
#
D 26
# Copyright (c) 1980 Regents of the University of California.
E 26
I 26
D 27
# Copyright (c) 1987 Regents of the University of California.
E 26
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 27
I 27
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 27
#
D 26
#	%W% (Berkeley) %G%
E 26
I 26
D 27
#	%W%	(Berkeley)	%G%
E 27
I 27
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
E 27
E 26
E 15
E 12
#
E 30
I 27
#	%W% (Berkeley) %G%
D 30
#
E 30
I 30

E 30
E 27
#	dump.h			header file
D 18
#	dumpitime.c		reads /etc/ddate
E 18
I 18
D 36
#	dumpitime.c		reads /etc/dumpdates
E 18
#	dumpmain.c		driver
#	dumpoptr.c		operator interface
E 36
I 36
#	itime.c			reads /etc/dumpdates
#	main.c			driver
#	optr.c			operator interface
E 36
I 34
#	dumprmt.c		handles remote tape via rmt(8)
E 34
D 36
#	dumptape.c		handles the mag tape and opening/closing
#	dumptraverse.c		traverses the file system
E 36
I 36
#	tape.c			handles the mag tape and opening/closing
#	traverse.c		traverses the file system
E 36
#	unctime.c		undo ctime
#
#	DEBUG			use local directory to find ddate and dumpdates
#	TDEBUG			trace out the process forking
D 26
#
I 7
D 9
NETSER=	/usr/src/ucb/netser

E 9
E 7
PSRCS = \
D 4
	dump.h dumpmain.c dumptraverse.c dumptape.c dumpoptr.c dumpitime.c
E 4
I 4
D 5
	../../h/dumprestor.h dump.h \
E 5
I 5
D 17
	/usr/include/dumprestor.h dump.h \
E 17
I 17
	/usr/include/protocols/dumprestore.h dump.h \
E 17
E 5
	dumpmain.c dumptraverse.c dumptape.c dumpoptr.c dumpitime.c unctime.c
E 26
E 4

D 26
SRCS =  \
	dump.h dumpitime.c \
D 6
	dumpmain.c dumpoptr.c dumptape.c \
E 6
I 6
	dumpmain.c dumpoptr.c dumprmt.c dumprtape.c \
E 26
I 26
D 30
DFLAGS=
CFLAGS=	-O ${DFLAGS}
LIBC=	/lib/libc.a
PSRCS=	/usr/include/protocols/dumprestore.h dump.h dumpmain.c \
	dumptraverse.c dumptape.c dumpoptr.c dumpitime.c unctime.c
SRCS=	dump.h dumpitime.c dumpmain.c dumpoptr.c dumprmt.c dumptape.c \
E 26
E 6
	dumptraverse.c unctime.c
I 26
OBJS=	dumpitime.o dumpmain.o dumpoptr.o dumptape.o dumptraverse.o \
	unctime.o
E 30
I 30
PROG=	dump
D 34
SRCS=	dumpitime.c dumpmain.c dumpoptr.c dumptape.c dumptraverse.c \
	unctime.c
E 30
ROBJS=	dumpitime.o dumprmain.o dumpoptr.o dumprmt.o dumprtape.o \
	dumptraverse.o unctime.o
E 34
I 34
LINKS=	${BINDIR}/dump ${BINDIR}/rdump
CFLAGS+=-DRDUMP
D 36
SRCS=	dumpitime.c dumpmain.c dumpoptr.c dumprmt.c dumptape.c \
	dumptraverse.c unctime.c
E 36
I 36
SRCS=	itime.c main.c optr.c dumprmt.c tape.c traverse.c unctime.c
E 36
BINOWN=	root
E 34
I 27
D 30
MAN=	dump.0 rdump.0
E 30
I 30
BINGRP=	tty
D 34
MAN8=	dump.0 rdump.0
I 31
CLEANFILES=dumprmain.o dumprtape.o dumprmt.o rdump
E 34
I 34
BINMODE=6555
MAN8=	dump.0
D 35
MLINKS+=dump.0 rdump.0
E 35
I 35
MLINKS+=dump.8 rdump.8
E 35
E 34
E 31
E 30
E 27
E 26

D 8
OBJS = \
	dumpitime.o \
	dumpmain.o dumpoptr.o \
E 8
I 8
D 26
OBJS = dumpitime.o dumpmain.o dumpoptr.o \
	dumptape.o dumptraverse.o unctime.o
E 26
I 26
D 30
all: dump rdump
E 30
I 30
D 34
all: rdump
E 30
E 26

D 26
ROBJS = dumpitime.o dumprmain.o dumpoptr.o \
E 8
D 6
	dumptape.o dumptraverse.o unctime.o
E 6
I 6
D 7
	dumprmt.o dumprtape.o dumptraverse.o unctime.o
E 7
I 7
D 9
	dumprmt.o dumprtape.o dumptraverse.o unctime.o $(NETSER)/rcmd.o
E 9
I 9
	dumprmt.o dumprtape.o dumptraverse.o unctime.o
E 26
I 26
D 27
dump:	${OBJS} ${LIBC}
E 27
I 27
D 30
dump: ${OBJS} ${LIBC}
E 27
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 26
E 9
E 7
E 6

E 30
D 3
DFLAGS = -DERNIE
E 3
I 3
D 26
DFLAGS =
E 3
D 4
CFLAGS = -O $(DFLAGS)
E 4
I 4
D 6
CFLAGS = -O -DKERNEL $(DFLAGS)
E 6
I 6
D 8
CFLAGS = -O $(DFLAGS) -DRDUMP
E 8
I 8
CFLAGS = -O $(DFLAGS)
E 26
I 26
D 27
rdump:	${ROBJS} ${LIBC}
E 27
I 27
rdump: ${ROBJS} ${LIBC}
E 27
D 30
	${CC} -o $@ ${CFLAGS} ${ROBJS}
E 30
I 30
	${CC} -o ${.TARGET} ${CFLAGS} ${ROBJS}
E 30
E 26
E 8
E 6
E 4

D 6
dump:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o dump
E 6
I 6
D 8
rdump:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o rdump -ljobs
E 8
I 8
D 26
all: dump rdump
E 26
I 26
D 30
dumprmain.o: dumpmain.c
	${CC} -c -DRDUMP ${CFLAGS} dumpmain.c -o dumprmain.o
E 30
I 30
D 33
dumprmain.o:
E 33
I 33
dumprmain.o: dumpmain.o
E 33
	${CC} -c -DRDUMP ${CFLAGS} ${.CURDIR}/dumpmain.c -o ${.TARGET}
E 30
E 26
E 8
E 6
I 4

E 4
D 8
install:
E 8
I 8
D 26
rdump:	$(ROBJS)
D 11
	$(CC) $(CFLAGS) $(ROBJS) -o rdump -ljobs
E 11
I 11
	$(CC) $(CFLAGS) $(ROBJS) -o rdump
E 26
I 26
D 30
dumprtape.o: dumptape.c
	${CC} -c -DRDUMP ${CFLAGS} dumptape.c -o dumprtape.o
E 30
I 30
D 33
dumprtape.o:
E 33
I 33
dumprtape.o: dumptape.o
E 33
	${CC} -c -DRDUMP ${CFLAGS} ${.CURDIR}/dumptape.c -o ${.TARGET}
E 30
E 26
E 11

D 26
dump:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o dump
E 26
I 26
D 27
clean: FRC
E 27
I 27
D 28
clean: ${SRCS}
E 28
I 28
D 30
clean:
E 28
E 27
	rm -f ${ROBJS} ${OBJS} rdump dump core
E 30
I 30
afterinstall:
	install ${STRIP} -o root -g ${BINGRP} -m 6555 rdump \
	    ${DESTDIR}${BINDIR}
E 34
I 34
D 37
all: dump
E 34
E 30
I 28

E 37
D 30
cleandir: clean
	rm -f ${MAN} tags .depend
E 28
E 26

D 26
install: rdump dump
E 8
D 2
	install -s dump $(DESTDIR)/bin
/etc/dump:
	cp dump.csh $(DESTDIR)/etc/dump
E 2
I 2
D 6
	install -s dump $(DESTDIR)/etc
E 6
I 6
D 13
	install -s rdump $(DESTDIR)/etc
I 8
	install -s dump $(DESTDIR)/etc
E 13
I 13
D 19
	install -s -m 4750 -g operator rdump $(DESTDIR)/etc
	install -s -m 4750 -g operator dump $(DESTDIR)/etc
E 19
I 19
	install -s -m 6755 -g tty rdump $(DESTDIR)/etc
	install -s -m 2755 -g tty dump $(DESTDIR)/etc
E 26
I 26
D 27
depend: FRC
E 27
I 27
depend: ${SRCS}
E 27
	mkdep ${CFLAGS} ${SRCS}
E 26
E 19
E 13
E 8
E 6
I 4

I 8
D 10
dumprmain.o: dumprmain.c
	cc -c -DRDUMP dumprmain.c
E 10
I 10
D 14
dumprmain.o: dumpmain.c
	cp dumpmain.c dumprmain.c
E 14
I 14
D 26
dumprmain.c:
	ln -s dumpmain.c dumprmain.c
dumprmain.o: dumprmain.c
E 14
	${CC} -c -DRDUMP ${CFLAGS} dumprmain.c
E 26
I 26
D 27
install: FRC
E 27
I 27
install: ${MAN}
E 27
D 29
	install -s -o root -g tty -m 6755 rdump ${DESTDIR}/etc/rdump
	install -s -o bin -g tty -m 2755 dump ${DESTDIR}/etc/dump
E 29
I 29
	install -s -o root -g tty -m 6755 rdump ${DESTDIR}/sbin/rdump
	install -s -o bin -g tty -m 2755 dump ${DESTDIR}/sbin/dump
E 29
I 27
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8
E 27
E 26
D 14
	rm -f dumprmain.c
E 14
E 10

I 14
D 26
dumprtape.c:
	ln -s dumptape.c dumprtape.c
dumprtape.o: dumprtape.c
	${CC} -c -DRDUMP ${CFLAGS} dumprtape.c
E 26
I 26
D 27
lint: FRC
E 27
I 27
lint: ${SRCS}
E 27
	lint ${CFLAGS} ${SRCS}
E 26

E 14
E 8
E 4
E 2
D 26
clean:
D 6
	rm -f *.o dump
E 6
I 6
D 8
	rm -f *.o rdump
E 8
I 8
D 10
	rm -f *.o rdump dump errs
E 10
I 10
D 14
	rm -f *.o rdump dump errs dumprmain.c
E 14
I 14
	rm -f *.o rdump dump errs dumprmain.c dumprtape.c
E 26
I 26
D 27
tags: FRC
E 27
I 27
tags: ${SRCS}
E 27
	ctags ${SRCS}
E 30
I 30
.include <bsd.prog.mk>
E 30
E 26
E 14
E 10
E 8
E 6
D 27

I 20
D 26
depend:
E 26
I 26
FRC:
E 26

E 20
D 26
lint:
	lint $(DFLAGS) $(SRCS)
E 26
I 26
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 26

D 4
psrcs:
	echo $(PSRCS)
E 4
I 4
D 26
print:
	pr $(PSRCS) | lpr
E 26
I 26
dump.o: dump.h /usr/include/stdio.h /usr/include/ctype.h
dump.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
dump.o: /usr/include/machine/machparam.h /usr/include/sys/stat.h
dump.o: /usr/include/sys/fs.h /usr/include/sys/inode.h
dump.o: /usr/include/protocols/dumprestore.h /usr/include/sys/dir.h
dump.o: /usr/include/utmp.h /usr/include/sys/time.h /usr/include/time.h
dump.o: /usr/include/signal.h /usr/include/fstab.h
dumpitime.o: dumpitime.c dump.h /usr/include/stdio.h /usr/include/ctype.h
dumpitime.o: /usr/include/sys/param.h /usr/include/sys/types.h
dumpitime.o: /usr/include/signal.h /usr/include/machine/machparam.h
dumpitime.o: /usr/include/sys/stat.h /usr/include/sys/fs.h
dumpitime.o: /usr/include/sys/inode.h /usr/include/protocols/dumprestore.h
dumpitime.o: /usr/include/sys/dir.h /usr/include/utmp.h /usr/include/sys/time.h
dumpitime.o: /usr/include/time.h /usr/include/signal.h /usr/include/fstab.h
dumpitime.o: /usr/include/sys/file.h
dumpmain.o: dumpmain.c dump.h /usr/include/stdio.h /usr/include/ctype.h
dumpmain.o: /usr/include/sys/param.h /usr/include/sys/types.h
dumpmain.o: /usr/include/signal.h /usr/include/machine/machparam.h
dumpmain.o: /usr/include/sys/stat.h /usr/include/sys/fs.h
dumpmain.o: /usr/include/sys/inode.h /usr/include/protocols/dumprestore.h
dumpmain.o: /usr/include/sys/dir.h /usr/include/utmp.h /usr/include/sys/time.h
dumpmain.o: /usr/include/time.h /usr/include/signal.h /usr/include/fstab.h
dumpoptr.o: dumpoptr.c dump.h /usr/include/stdio.h /usr/include/ctype.h
dumpoptr.o: /usr/include/sys/param.h /usr/include/sys/types.h
dumpoptr.o: /usr/include/signal.h /usr/include/machine/machparam.h
dumpoptr.o: /usr/include/sys/stat.h /usr/include/sys/fs.h
dumpoptr.o: /usr/include/sys/inode.h /usr/include/protocols/dumprestore.h
dumpoptr.o: /usr/include/sys/dir.h /usr/include/utmp.h /usr/include/sys/time.h
dumpoptr.o: /usr/include/time.h /usr/include/signal.h /usr/include/fstab.h
dumprmt.o: dumprmt.c /usr/include/sys/param.h /usr/include/sys/types.h
dumprmt.o: /usr/include/signal.h /usr/include/machine/machparam.h
dumprmt.o: /usr/include/sys/mtio.h /usr/include/sys/ioctl.h
dumprmt.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
dumprmt.o: /usr/include/sys/socket.h /usr/include/sys/inode.h
dumprmt.o: /usr/include/netinet/in.h /usr/include/stdio.h /usr/include/pwd.h
dumprmt.o: /usr/include/netdb.h /usr/include/protocols/dumprestore.h
dumptape.o: dumptape.c /usr/include/sys/file.h dump.h /usr/include/stdio.h
dumptape.o: /usr/include/ctype.h /usr/include/sys/param.h
dumptape.o: /usr/include/sys/types.h /usr/include/signal.h
dumptape.o: /usr/include/machine/machparam.h /usr/include/sys/stat.h
dumptape.o: /usr/include/sys/fs.h /usr/include/sys/inode.h
dumptape.o: /usr/include/protocols/dumprestore.h /usr/include/sys/dir.h
dumptape.o: /usr/include/utmp.h /usr/include/sys/time.h /usr/include/time.h
dumptape.o: /usr/include/signal.h /usr/include/fstab.h
dumptraverse.o: dumptraverse.c dump.h /usr/include/stdio.h /usr/include/ctype.h
dumptraverse.o: /usr/include/sys/param.h /usr/include/sys/types.h
dumptraverse.o: /usr/include/signal.h /usr/include/machine/machparam.h
dumptraverse.o: /usr/include/sys/stat.h /usr/include/sys/fs.h
dumptraverse.o: /usr/include/sys/inode.h /usr/include/protocols/dumprestore.h
dumptraverse.o: /usr/include/sys/dir.h /usr/include/utmp.h
dumptraverse.o: /usr/include/sys/time.h /usr/include/time.h
dumptraverse.o: /usr/include/signal.h /usr/include/fstab.h
unctime.o: unctime.c /usr/include/sys/types.h /usr/include/sys/time.h
unctime.o: /usr/include/time.h /usr/include/stdio.h
E 26

D 5
$(OBJS): dump.h ../../h/param.h ../../h/stat.h ../../h/fs.h
$(OBJS): ../../h/inode.h ../../h/dumprestor.h
E 5
I 5
D 26
$(OBJS): dump.h /usr/include/sys/param.h
$(OBJS): /usr/include/sys/fs.h /usr/include/sys/inode.h
D 12
$(OBJS): /usr/include/dumprestor.h /usr/include/stat.h
E 12
I 12
D 17
$(OBJS): /usr/include/dumprestor.h /usr/include/sys/stat.h
E 17
I 17
$(OBJS): /usr/include/protocols/dumprestore.h /usr/include/sys/stat.h
E 26
I 26
# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 27
E 26
E 17
E 12
E 5
E 4
E 1
