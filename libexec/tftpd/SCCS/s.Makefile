h26430
s 00000/00000/00009
d D 8.1 93/06/04 19:07:53 bostic 13 12
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00008
d D 5.11 93/05/16 14:53:02 torek 12 11
c add prototypes, need -I now
e
s 00005/00045/00003
d D 5.10 90/05/11 12:55:51 bostic 11 10
c first pass for new make
e
s 00002/00002/00046
d D 5.9 89/05/11 14:32:40 bostic 10 9
c file reorg, pathnames.h, paths.h
e
s 00011/00023/00037
d D 5.8 88/09/20 09:51:58 bostic 9 8
c cleanup, add man page
e
s 00011/00006/00049
d D 5.7 88/06/18 14:01:49 bostic 8 7
c install approved copyright notice
e
s 00006/00008/00049
d D 5.6 88/05/21 15:32:55 bostic 7 6
c use VPATH, not links
e
s 00010/00004/00047
d D 5.5 88/03/28 13:54:45 bostic 6 5
c add Berkeley specific header
e
s 00041/00013/00010
d D 5.4 87/06/02 21:55:46 bostic 5 3
c new template
e
s 00041/00013/00010
d R 5.4 87/06/02 21:29:12 bostic 4 3
c new template
e
s 00002/00000/00021
d D 5.3 87/05/31 20:42:26 bostic 3 2
c added depend label
e
s 00001/00001/00020
d D 5.2 86/02/07 11:47:42 minshall 2 1
c Move to new version of tftpd (changes from <guyton@rand-unix>).
e
s 00021/00000/00000
d D 5.1 86/02/07 11:44:15 minshall 1 0
c date and time created 86/02/07 11:44:15 by minshall
e
u
U
t
T
I 1
D 11
#
D 5
# Copyright (c) 1983 Regents of the University of California.
E 5
I 5
D 6
# Copyright (c) 1987 Regents of the University of California.
E 5
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 6
I 6
D 8
# Copyright (c) 1988 Regents of the University of California.
E 8
I 8
# Copyright (c) 1987 Regents of the University of California.
E 8
# All rights reserved.
E 6
#
D 5
#	%W% (Berkeley) %G%
E 5
I 5
D 6
#	%W%	(Berkeley)	%G%
E 6
I 6
# Redistribution and use in source and binary forms are permitted
D 8
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 8
#
E 11
#	%W% (Berkeley) %G%
E 6
E 5
D 11
#
I 7
D 10
VPATH=	../../ucb/tftp
E 10
I 10
VPATH=	../../usr.bin/tftp
E 10
E 7
D 5

D 2
ALL=	tftpd.o
E 2
I 2
ALL=	tftpd.o tftpsubs.o
E 2
DESTDIR=
E 5
CFLAGS=	-O
D 5
LDFLAGS=
E 5
I 5
LIBC=	/lib/libc.a
E 11
I 11

PROG=	tftpd
E 11
SRCS=	tftpd.c tftpsubs.c
D 11
OBJS=	tftpd.o tftpsubs.o
I 9
MAN=	tftpd.0
E 11
I 11
MAN8=	tftpd.0
I 12
CFLAGS+=-I${.CURDIR}/../../usr.bin/tftp
E 12
.PATH:	${.CURDIR}/../../usr.bin/tftp
E 11
E 9
E 5

D 5
tftpd:	${ALL}
	${CC} ${LDFLAGS} -o tftpd ${ALL}
E 5
I 5
D 11
all: tftpd
E 5

D 5
install:
	install -s tftpd ${DESTDIR}/etc/tftpd
E 5
I 5
D 9
tftpd:	${OBJS} ${LIBC}
E 9
I 9
tftpd: ${OBJS} ${LIBC}
E 9
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 5

D 5
clean:
	rm -f tftpd *.o *.s errs core a.out t.?
E 5
I 5
D 9
clean: FRC
E 9
I 9
clean:
E 9
	rm -f ${OBJS} core tftpd
E 5
I 3

D 5
depend:
E 5
I 5
D 9
depend: FRC
E 9
I 9
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 9
	mkdep ${CFLAGS} ${SRCS}

D 9
install: FRC
E 9
I 9
install: ${MAN}
E 9
D 10
	install -s -o bin -g bin -m 755 tftpd ${DESTDIR}/etc/tftpd
E 10
I 10
	install -s -o bin -g bin -m 755 tftpd ${DESTDIR}/usr/libexec
E 10
I 9
	install -c -o bin -g bin -m 444 tftpd.0 ${DESTDIR}/usr/man/cat8
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
E 11
I 11
.include <bsd.prog.mk>
E 11
D 9

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

tftpd.o: tftpd.c /usr/include/sys/types.h /usr/include/sys/socket.h
tftpd.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 7
tftpd.o: /usr/include/sys/ttydev.h /usr/include/sys/wait.h
tftpd.o: /usr/include/machine/machparam.h /usr/include/sys/stat.h
tftpd.o: /usr/include/netinet/in.h /usr/include/arpa/tftp.h
tftpd.o: /usr/include/signal.h /usr/include/stdio.h /usr/include/errno.h
E 7
I 7
tftpd.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
tftpd.o: /usr/include/sys/wait.h /usr/include/machine/endian.h
tftpd.o: /usr/include/sys/stat.h /usr/include/netinet/in.h
tftpd.o: /usr/include/arpa/tftp.h /usr/include/signal.h
tftpd.o: /usr/include/machine/trap.h /usr/include/stdio.h /usr/include/errno.h
E 7
tftpd.o: /usr/include/ctype.h /usr/include/netdb.h /usr/include/setjmp.h
tftpd.o: /usr/include/syslog.h
D 7
tftpsubs.o: tftpsubs.c /usr/include/sys/types.h /usr/include/sys/socket.h
tftpsubs.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
tftpsubs.o: /usr/include/sys/ttydev.h /usr/include/netinet/in.h
tftpsubs.o: /usr/include/arpa/tftp.h /usr/include/stdio.h
E 7

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 9
E 5
E 3
E 1
