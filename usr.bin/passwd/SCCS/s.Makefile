h29984
s 00002/00001/00013
d D 8.3 94/04/02 09:35:28 pendry 18 17
c prettyness police
e
s 00001/00001/00013
d D 8.2 94/04/02 05:34:24 bostic 17 16
c Jan-Simon broke out pw_util includes into pw_util.h
e
s 00000/00000/00014
d D 8.1 93/07/19 09:46:22 bostic 16 15
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00013
d D 5.12 93/07/19 09:46:21 bostic 15 12
c set the immutable bit on installation
e
s 00000/00000/00013
d R 8.1 93/06/06 15:49:33 bostic 14 12
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00004/00009
d D 5.11.1.1 91/08/20 15:59:22 mckusick 13 12
c delete data-stream encryption for the foreign sites (Network, Release 2)
e
s 00001/00001/00012
d D 5.11 91/02/19 14:29:44 bostic 12 11
c vipw moved to usr.sbin
e
s 00003/00002/00010
d D 5.10 91/02/12 22:16:24 bostic 11 10
c rework the password subsystem
e
s 00001/00001/00011
d D 5.9 91/02/03 13:36:25 bostic 10 8
c add krb_passwd.c
e
s 00006/00004/00008
d D 5.8.1.1 90/10/21 20:46:25 mckusick 9 8
c delete data-stream encryption for the foreign sites (4.3-Reno)
e
s 00001/00001/00011
d D 5.8 90/09/28 20:08:50 mckusick 8 7
c now need CRYPT too
e
s 00005/00001/00007
d D 5.7 90/06/19 17:06:25 kfall 7 6
c changes for Kerberos
e
s 00005/00044/00003
d D 5.6 90/05/11 14:14:28 bostic 6 5
c first pass for new make
e
s 00001/00001/00046
d D 5.5 89/05/11 13:37:24 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00004/00010/00043
d D 5.4 89/02/22 17:22:27 bostic 4 3
c shadow passwords
e
s 00028/00024/00021
d D 5.3 88/10/21 15:54:39 bostic 3 2
c cleanup, add manual page
e
s 00009/00011/00036
d D 5.2 88/01/21 10:27:34 bostic 2 1
c only compile the one file
e
s 00047/00000/00000
d D 5.1 87/12/12 17:14:19 bostic 1 0
c date and time created 87/12/12 17:14:19 by bostic
e
u
U
f b 
t
T
I 1
D 6
#
D 3
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 3
I 3
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 3
#
D 3
#	%W%	(Berkeley)	%G%
E 3
I 3
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
E 3
#
E 6
I 3
#	%W% (Berkeley) %G%
D 6
#
E 3
D 4
CFLAGS=	-O
E 4
I 4
CFLAGS=	-I. -O
E 4
LIBC=	/lib/libc.a
SRCS=	passwd.c
I 3
D 4
OBJS=
E 4
I 4
OBJS=	passwd.o
E 4
MAN=	passwd.0
E 6
E 3
D 2
OBJS=	passwd.o
E 2

D 6
all: passwd
E 6
I 6
PROG=	passwd
D 7
CFLAGS+=-I${.CURDIR}
E 7
I 7
D 9
D 10
SRCS=	passwd.c des_rw.c
E 10
I 10
D 11
SRCS=	passwd.c des_rw.c krb_passwd.c
E 11
I 11
D 13
SRCS=	des_rw.c krb_passwd.c local_passwd.c passwd.c pw_copy.c pw_util.c
E 11
E 10
DPADD=	${LIBKRB} ${LIBDES}
E 13
I 13
SRCS=	krb_passwd.c local_passwd.c passwd.c pw_copy.c pw_util.c
CFLAGS+=-I${.CURDIR}
#SRCS=	des_rw.c krb_passwd.c local_passwd.c passwd.c pw_copy.c pw_util.c
#CFLAGS+=-I${.CURDIR} -DKERBEROS -DCRYPT
#DPADD=	${LIBKRB} ${LIBDES}
#LDADD=	-lkrb -ldes
E 13
I 11
D 12
.PATH:  ${.CURDIR}/../../usr.bin/chpass ${.CURDIR}/../../sbin/vipw \
E 12
I 12
.PATH:  ${.CURDIR}/../../usr.bin/chpass ${.CURDIR}/../../usr.sbin/vipw \
E 12
	${.CURDIR}/../rlogin
E 11
D 8
CFLAGS+=-I${.CURDIR} -DKERBEROS
E 8
I 8
D 13
D 17
CFLAGS+=-I${.CURDIR} -DKERBEROS -DCRYPT
E 17
I 17
D 18
CFLAGS+=-DKERBEROS -DCRYPT -I${.CURDIR} -I${.CURDIR}/../../usr.sbin/vipw
E 18
I 18
CFLAGS+=-DKERBEROS -DCRYPT -I${.CURDIR} -I${.CURDIR}/../../usr.sbin/vipw \
	-I${.CURDIR}/../../usr.bin/chpass
E 18
E 17
E 8
LDADD=	-lkrb -ldes
E 13
E 9
I 9
SRCS=	passwd.c
CFLAGS+=-I${.CURDIR}
#SRCS=	passwd.c des_rw.c
#CFLAGS+=-I${.CURDIR} -DKERBEROS -DCRYPT
#DPADD=	${LIBKRB} ${LIBDES}
#LDADD=	-lkrb -ldes
E 9
E 7
BINOWN=	root
BINMODE=4555
I 15
INSTALLFLAGS=-fschg
E 15
I 7
D 11
.PATH:	${.CURDIR}/../rlogin
E 11
E 7
E 6

D 2
passwd:	${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 2
I 2
D 4
passwd: ${LIBC}
D 3
	${CC} -o $@ ${CFLAGS} ${SRCS}
E 3
I 3
	${CC} ${CFLAGS} -o $@ $@.c
E 4
I 4
D 6
passwd: ${LIBC} ${OBJS}
	${CC} ${CFLAGS} -o $@ ${OBJS}
E 4
E 3
E 2

D 3
clean: FRC
D 2
	rm -f ${OBJS} core passwd
E 2
I 2
	rm -f core passwd
E 3
I 3
clean:
	rm -f ${OBJS} core passwd
E 3
E 2

D 3
depend: FRC
E 3
I 3
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 3
D 2
	mkdep ${CFLAGS} ${SRCS}
E 2
I 2
	mkdep -p ${CFLAGS} ${SRCS}
E 2

D 3
install: FRC
E 3
I 3
install: ${MAN}
E 3
D 5
	install -s -o root -g bin -m 4755 passwd ${DESTDIR}/bin/passwd
E 5
I 5
	install -s -o root -g bin -m 4755 passwd ${DESTDIR}/usr/bin
E 5
D 4
	rm -f ${DESTDIR}/bin/chfn; ln ${DESTDIR}/bin/passwd ${DESTDIR}/bin/chfn
	rm -f ${DESTDIR}/bin/chsh; ln ${DESTDIR}/bin/passwd ${DESTDIR}/bin/chsh
E 4
I 3
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
D 4
	rm -f ${DESTDIR}/usr/man/cat1/chfn.0
	rm -f ${DESTDIR}/usr/man/cat1/chsh.0
	ln ${DESTDIR}/usr/man/cat1/passwd.0 ${DESTDIR}/usr/man/cat1/chfn.0
	ln ${DESTDIR}/usr/man/cat1/passwd.0 ${DESTDIR}/usr/man/cat1/chsh.0
E 4
E 3

D 3
lint: FRC
E 3
I 3
lint: ${SRCS}
E 3
	lint ${CFLAGS} ${SRCS}

D 3
tags: FRC
E 3
I 3
tags: ${SRCS}
E 3
	ctags ${SRCS}
E 6
I 6
.include <bsd.prog.mk>
E 6
D 3

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

D 2
passwd.o: passwd.c /usr/include/sys/types.h /usr/include/sys/file.h
passwd.o: /usr/include/sys/stat.h /usr/include/sys/time.h /usr/include/time.h
passwd.o: /usr/include/sys/resource.h /usr/include/stdio.h
passwd.o: /usr/include/signal.h /usr/include/machine/trap.h /usr/include/pwd.h
passwd.o: /usr/include/ndbm.h /usr/include/errno.h /usr/include/strings.h
passwd.o: /usr/include/ctype.h
E 2
I 2
passwd: passwd.c /usr/include/sys/types.h /usr/include/sys/file.h
passwd: /usr/include/sys/stat.h /usr/include/sys/time.h /usr/include/time.h
passwd: /usr/include/sys/resource.h /usr/include/stdio.h /usr/include/signal.h
passwd: /usr/include/machine/trap.h /usr/include/pwd.h /usr/include/ndbm.h
passwd: /usr/include/errno.h /usr/include/strings.h /usr/include/ctype.h
E 2

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 3
E 1
