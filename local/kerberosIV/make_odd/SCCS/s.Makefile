h29182
s 00000/00000/00010
d D 8.1 93/06/01 23:13:43 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00010/00000/00000
d D 5.1 90/06/25 11:38:41 bostic 1 0
c date and time created 90/06/25 11:38:41 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	make_odd
SRCS=	make_odd.c misc.c
.PATH:	${.CURDIR}/../make_key_perm
CFLAGS+=-DKERBEROS -DDEBUG -I${.CURDIR}/../include \
	-I${.CURDIR}/../des
NOMAN=	noman

.include <bsd.prog.mk>
E 1
