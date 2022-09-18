h45025
s 00000/00000/00012
d D 8.1 93/06/11 15:31:02 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00004/00010
d D 5.2 91/05/10 14:28:41 bostic 2 1
c delete KERBEROS stuff
e
s 00014/00000/00000
d D 5.1 91/05/03 18:58:17 bostic 1 0
c date and time created 91/05/03 18:58:17 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	rsh
D 2
SRCS=   rsh.c krcmd.c kcmd.c des_rw.c
CFLAGS+=-DLETS_GET_SMALL -DKERBEROS -DCRYPT
DPADD=	${LIBKRB} ${LIBDES}
LDADD=	-lkrb -ldes
E 2
I 2
SRCS=   rsh.c
CFLAGS+=-DLETS_GET_SMALL
E 2
BINOWN=	root
BINMODE=4555
NOMAN=	noman
LDFLAGS=-N
.PATH:	${.CURDIR}/../../../../usr.bin/rsh ${.CURDIR}/../../../../usr.bin/rlogin

.include <bsd.prog.mk>
E 1
