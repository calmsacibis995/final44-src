h09359
s 00000/00000/00018
d D 8.1 93/06/01 23:16:03 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00017
d D 5.4 90/11/01 10:36:08 bostic 4 3
c add CRYPT define for rlogin code (local CRYPT -> RCRYPT)
c minor cleanups, add Berkeley copyright
e
s 00001/00000/00017
d D 5.3 90/08/06 15:48:48 kfall 3 2
c set BINDIR to install registerd in /usr/libexec
e
s 00001/00000/00016
d D 5.2 90/06/26 09:40:35 bostic 2 1
c needs rlogin for des_rw.c
e
s 00016/00000/00000
d D 5.1 90/06/25 18:28:17 bostic 1 0
c date and time created 90/06/25 18:28:17 by bostic
e
u
U
t
T
I 1
#
# Copyright (c) 1990 The Regents of the University of California.
# All rights reserved.
#
# %sccs.include.redist.sh
#
#	%W% (Berkeley) %G%
#
PROG=	registerd
SRCS=	registerd.c des_rw.c
D 4
CFLAGS+=-DKERBEROS -I${.CURDIR}/../register
E 4
I 4
CFLAGS+=-DCRYPT -DKERBEROS -I${.CURDIR}/../register
E 4
I 2
.PATH:	${.CURDIR}/../../usr.bin/rlogin
E 2
DPADD=	${LIBKDB} ${LIBKRB} ${LIBDES}
LDADD=	-lkdb -lkrb -ldes
MAN8=	registerd.0
I 3
BINDIR=	/usr/libexec
E 3

.include <bsd.prog.mk>
E 1
