h39792
s 00000/00000/00011
d D 8.1 93/06/01 23:10:26 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00010
d D 5.2 91/02/14 14:50:33 bostic 2 1
c fix SRCS list
e
s 00011/00000/00000
d D 5.1 90/06/25 11:37:45 bostic 1 0
c date and time created 90/06/25 11:37:45 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	kdb_edit
CFLAGS+=-DKERBEROS -DDEBUG -I. -I${.CURDIR}/../include
D 2
SRCS=	kdb_edit.o maketime.o
E 2
I 2
SRCS=	kdb_edit.c maketime.c
E 2
.PATH:	${.CURDIR}/../kdb_edit
DPADD=	${LIBKDB} ${LIBKRB} ${LIBDES}
LDADD=	-lkdb -lkrb -ldes
NOMAN=	noman

.include <bsd.prog.mk>
E 1
