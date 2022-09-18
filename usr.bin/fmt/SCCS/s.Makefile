h19477
s 00000/00000/00007
d D 8.1 93/06/06 14:39:50 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00000/00000
d D 5.1 90/05/11 15:22:30 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	fmt
SRCS=	fmt.c head.c
.PATH: ${.CURDIR}/../mail

.include <bsd.prog.mk>
E 1
