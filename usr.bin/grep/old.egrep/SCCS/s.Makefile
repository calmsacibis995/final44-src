h32088
s 00000/00000/00009
d D 8.1 93/06/06 14:48:51 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00008
d D 5.2 90/07/01 10:31:32 bostic 2 1
c clean y.tab.h
e
s 00009/00000/00000
d D 5.1 90/06/19 12:51:11 bostic 1 0
c date and time created 90/06/19 12:51:11 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	old.egrep
SRCS=	old.egrep.c
BINDIR=	/usr/libexec
NOMAN=	noman
D 2
CLEANFILES+=old.egrep.c
E 2
I 2
CLEANFILES+=old.egrep.c y.tab.h
E 2

.include <bsd.prog.mk>
E 1
