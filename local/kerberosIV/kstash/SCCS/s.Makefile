h34831
s 00000/00000/00009
d D 8.1 93/06/01 23:12:35 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00009
d D 5.2 91/03/05 11:30:50 bostic 2 1
c kstash belongs in /usr/sbin
e
s 00010/00000/00000
d D 5.1 90/06/25 18:20:09 bostic 1 0
c date and time created 90/06/25 18:20:09 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	kstash
CFLAGS+=-DKERBEROS -DDEBUG -I${.CURDIR}/../include
DPADD=	${LIBKDB} ${LIBKRB} ${LIBDES}
LDADD=	-lkdb -lkrb -ldes 
D 2
BINDIR=	/usr/bin
E 2
NOMAN=	noman

.include <bsd.prog.mk>
E 1
