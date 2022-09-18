h24469
s 00000/00000/00006
d D 8.1 93/06/06 22:22:05 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00005
d D 5.2 90/06/29 00:40:37 marc 2 1
c broke out some code into foldit.c
e
s 00005/00000/00000
d D 5.1 90/05/11 15:57:52 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	vis
I 2
SRCS=	vis.c foldit.c
E 2

.include <bsd.prog.mk>
E 1
