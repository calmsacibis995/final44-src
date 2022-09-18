h30871
s 00000/00000/00010
d D 8.1 93/06/06 14:35:23 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00009
d D 5.2 90/06/29 17:10:41 bostic 2 1
c clean part.c
e
s 00009/00000/00000
d D 5.1 90/05/11 15:14:58 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	style3
CFLAGS+=-I${.CURDIR} -I${.CURDIR}/../style1
SRCS=	part.c pscan.c outp.c
I 2
CLEANFILES=part.c
E 2
NOMAN=	noman
BINDIR=	/usr/libexec

.include <bsd.prog.mk>
E 1
