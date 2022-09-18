h41721
s 00000/00000/00012
d D 8.1 93/06/01 23:10:50 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00011
d D 5.2 91/02/14 14:51:00 bostic 2 1
c fix SRCS list
e
s 00012/00000/00000
d D 5.1 90/06/25 11:37:55 bostic 1 0
c date and time created 90/06/25 11:37:55 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	kdb_util
CFLAGS+=-DKERBEROS -DDEBUG -I${.CURDIR}/../kdb_edit \
	-I${.CURDIR}/../include
D 2
SRCS=	kdb_util.o maketime.o
E 2
I 2
SRCS=	kdb_util.c maketime.c
E 2
.PATH:	${.CURDIR}/../kdb_edit
DPADD=	${LIBKDB} ${LIBKRB} ${LIBDES}
LDADD=	-lkdb -lkrb -ldes
NOMAN=	noman

.include <bsd.prog.mk>
E 1
