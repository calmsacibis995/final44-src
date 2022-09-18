h09459
s 00002/00003/00007
d D 8.2 94/04/04 12:35:57 pendry 20 19
c eliminate local version of glob (cf ftp)
c clean up yacc grammar.  prettiness police.
e
s 00000/00000/00010
d D 8.1 93/06/04 18:48:49 bostic 19 18
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00009
d D 5.15 90/07/01 12:34:44 bostic 18 17
c install man page in the right place
e
s 00003/00006/00006
d D 5.14 90/06/25 14:53:40 bostic 17 16
c don't use symlink for glob.c, forget fancy versioning
e
s 00002/00002/00010
d D 5.13 90/06/24 18:24:59 bostic 16 15
c don't need to get includes from ftp, clean vers.c, version, y.tab.h
e
s 00006/00045/00006
d D 5.12 90/05/11 12:55:49 bostic 15 14
c first pass for new make
e
s 00001/00001/00050
d D 5.11 89/11/19 18:03:27 bostic 14 13
c source reorganization
e
s 00002/00002/00049
d D 5.10 89/04/20 13:59:32 bostic 13 12
c file system reorganization; pathnames.h
e
s 00001/00001/00050
d D 5.9 89/01/25 15:46:39 bostic 12 11
c add SETPROCTITLE define to CFLAGS
e
s 00002/00002/00049
d D 5.8 88/09/22 15:19:05 bostic 11 10
c add logwtmp and popen modules
e
s 00010/00037/00041
d D 5.7 88/09/19 21:24:39 bostic 10 9
c cleanup, add man page
e
s 00010/00005/00068
d D 5.6 88/06/18 13:46:45 bostic 9 8
c install approved copyright notice
e
s 00020/00011/00053
d D 5.5 88/03/14 17:27:45 bostic 8 7
c add Berkeley specific header
e
s 00052/00013/00012
d D 5.4 87/06/02 21:48:55 bostic 7 5
c new template
e
s 00052/00013/00012
d R 5.4 87/06/02 20:20:04 bostic 6 5
c new template
e
s 00002/00000/00023
d D 5.3 87/05/31 20:38:40 bostic 5 4
c added depend label
e
s 00000/00000/00023
d D 5.2 86/02/03 14:32:49 minshall 4 3
c Steve Jacobson's changes (from <csvsj@ucbopal>).
e
s 00006/00001/00017
d D 5.1 85/06/06 11:08:25 dist 3 2
c Add copyright
e
s 00004/00006/00014
d D 4.2 83/06/12 02:45:42 sam 2 1
c new signals == no libjobs
e
s 00020/00000/00000
d D 4.1 83/05/03 16:37:57 sam 1 0
c date and time created 83/05/03 16:37:57 by sam
e
u
U
t
T
I 1
D 3
#	%W%	%G%
E 3
I 3
D 15
#
D 7
# Copyright (c) 1983 Regents of the University of California.
E 7
I 7
D 8
# Copyright (c) 1987 Regents of the University of California.
E 7
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 8
I 8
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
E 8
#
D 7
#	%W% (Berkeley) %G%
E 7
I 7
D 8
#	%W%	(Berkeley)	%G%
E 8
I 8
# Redistribution and use in source and binary forms are permitted
D 9
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 8
E 7
E 3
#
E 15
I 8
#	%W% (Berkeley) %G%
D 15
#
E 8
D 2
ALL=	ftpd
E 2
I 2
D 7
ALL=	ftpd.o ftpcmd.o glob.o vers.o
E 2
DESTDIR=
E 7
D 12
CFLAGS=	-O
E 12
I 12
D 13
CFLAGS=	-O -DSETPROCTITLE
E 13
I 13
D 14
CFLAGS=	-O -I../../usr.ucb/ftp -DSETPROCTITLE
E 14
I 14
CFLAGS=	-O -I../../../usr.bin/ftp -DSETPROCTITLE
E 14
E 13
E 12
I 7
LIBC=	/lib/libc.a
E 15
I 15

PROG=	ftpd
D 16
CFLAGS+=-I${.CURDIR}/../../../usr.bin/ftp -DSETPROCTITLE
E 16
I 16
D 17
CFLAGS+=-DSETPROCTITLE
E 17
I 17
D 20
CFLAGS+=-I${.CURDIR}/../../usr.bin/ftp -DSETPROCTITLE
E 17
E 16
E 15
D 11
SRCS=	ftpd.c ftpcmd.c glob.c vers.c
OBJS=	ftpd.o ftpcmd.o glob.o vers.o
E 11
I 11
SRCS=	ftpd.c ftpcmd.c glob.c logwtmp.c popen.c vers.c
E 20
I 20
CFLAGS+=-DSETPROCTITLE
SRCS=	ftpd.c ftpcmd.c logwtmp.c popen.c
E 20
I 18
MAN8=	ftpd.0
E 18
D 15
OBJS=	ftpd.o ftpcmd.o glob.o logwtmp.o popen.o vers.o
E 11
I 10
MAN=	ftpd.0
E 15
I 15
D 16
CLEANFILES+=ftpcmd.c
E 16
I 16
D 17
CLEANFILES+=ftpcmd.c vers.c version y.tab.h
E 16
E 15
E 10
E 7

D 2
all:	${ALL}
E 2
I 2
D 7
ftpd:	${ALL}
	${CC} -o ftpd ${ALL}
E 7
I 7
D 15
all: ftpd
E 7
E 2

D 2
ftpd:	ftpd.o ftpcmd.o vers.o glob.o
	${CC} ftpd.o ftpcmd.o glob.o -o ftpd vers.o -ljobs

E 2
D 7
vers.o:	ftpd.c ftpcmd.y
E 7
I 7
ftpd: ${OBJS} ${LIBC}
	${CC} -o $@ ${OBJS}

E 15
vers.o: ftpd.c ftpcmd.y
E 7
D 15
	sh newvers.sh
E 15
I 15
	sh ${.CURDIR}/newvers.sh
E 15
D 7
	${CC} -c vers.c
E 7
I 7
	${CC} ${CFLAGS} -c vers.c
E 17
I 17
CLEANFILES+=ftpcmd.c y.tab.h
D 20
.PATH:	${.CURDIR}/../../usr.bin/ftp
E 20
E 17
E 7

D 7
install:
	install -s ftpd ${DESTDIR}/etc/ftpd
E 7
I 7
D 10
clean: FRC
E 10
I 10
D 15
clean:
E 10
	rm -f ${OBJS} ftpd core ftpcmd.c
E 7

D 7
clean:
D 2
	rm -f ${ALL} *.o *.s errs core a.out t.? yacc.* y.tab.c
E 2
I 2
	rm -f ftpd *.o *.s errs core a.out t.? yacc.* y.tab.c
E 7
I 7
D 8
depend: ftpcmd.c FRC
E 8
I 8
D 10
depend: ${SRCS} FRC
E 10
I 10
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 10
E 8
	mkdep ${CFLAGS} ${SRCS}
E 7
I 5

D 7
depend:
E 7
I 7
D 10
install: FRC
E 10
I 10
install: ${MAN}
E 10
D 13
	install -s -o bin -g bin -m 755 ftpd ${DESTDIR}/etc/ftpd
E 13
I 13
	install -s -o bin -g bin -m 755 ftpd ${DESTDIR}/usr/libexec
E 13
I 10
	install -c -o bin -g bin -m 755 ftpd.0 ${DESTDIR}/usr/man/cat8
E 10

D 8
lint: ftpcmd.c FRC
E 8
I 8
D 10
lint: ${SRCS} FRC
E 10
I 10
lint: ${SRCS}
E 10
E 8
	lint ${CFLAGS} ${SRCS}

D 8
tags: ftpcmd.c FRC
E 8
I 8
D 10
tags: ${SRCS} FRC
E 10
I 10
tags: ${SRCS}
E 10
E 8
	ctags ${SRCS}
E 15
I 15
.include <bsd.prog.mk>
E 15
D 10

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

ftpd.o: ftpd.c /usr/include/sys/param.h /usr/include/sys/types.h
D 8
ftpd.o: /usr/include/signal.h /usr/include/machine/machparam.h
E 8
I 8
ftpd.o: /usr/include/signal.h /usr/include/machine/trap.h
ftpd.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
E 8
ftpd.o: /usr/include/sys/stat.h /usr/include/sys/ioctl.h
ftpd.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
ftpd.o: /usr/include/sys/socket.h /usr/include/sys/file.h
ftpd.o: /usr/include/sys/wait.h /usr/include/netinet/in.h
ftpd.o: /usr/include/arpa/ftp.h /usr/include/arpa/inet.h
ftpd.o: /usr/include/arpa/telnet.h /usr/include/stdio.h /usr/include/signal.h
ftpd.o: /usr/include/pwd.h /usr/include/setjmp.h /usr/include/netdb.h
ftpd.o: /usr/include/errno.h /usr/include/strings.h /usr/include/syslog.h
ftpd.o: /usr/include/utmp.h
ftpcmd.o: ftpcmd.c /usr/include/sys/types.h /usr/include/sys/socket.h
ftpcmd.o: /usr/include/netinet/in.h /usr/include/arpa/ftp.h
D 8
ftpcmd.o: /usr/include/stdio.h /usr/include/signal.h /usr/include/ctype.h
ftpcmd.o: /usr/include/pwd.h /usr/include/setjmp.h /usr/include/syslog.h
E 8
I 8
ftpcmd.o: /usr/include/stdio.h /usr/include/signal.h
ftpcmd.o: /usr/include/machine/trap.h /usr/include/ctype.h /usr/include/pwd.h
ftpcmd.o: /usr/include/setjmp.h /usr/include/syslog.h
E 8
ftpcmd.o: /usr/include/arpa/telnet.h
glob.o: glob.c /usr/include/sys/param.h /usr/include/sys/types.h
D 8
glob.o: /usr/include/signal.h /usr/include/machine/machparam.h
E 8
I 8
glob.o: /usr/include/signal.h /usr/include/machine/trap.h
glob.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
E 8
glob.o: /usr/include/sys/stat.h /usr/include/sys/dir.h /usr/include/stdio.h
glob.o: /usr/include/errno.h /usr/include/pwd.h
vers.o: vers.c

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 10
E 7
E 5
E 2
E 1
