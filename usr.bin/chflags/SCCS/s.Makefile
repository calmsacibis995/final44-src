h36891
s 00000/00000/00007
d D 8.1 93/06/06 14:26:47 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00000/00005
d D 5.2 93/03/03 20:35:33 bostic 2 1
c use err routines from C library
c add sappend, schange, uappend, uchange flags, use routine from ls(1) source
e
s 00005/00000/00000
d D 5.1 91/12/12 16:56:56 mckusick 1 0
c date and time created 91/12/12 16:56:56 by mckusick
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	chflags
I 2
SRCS=	chflags.c stat_flags.c
.PATH:	${.CURDIR}/../../bin/ls
E 2

.include <bsd.prog.mk>
E 1
