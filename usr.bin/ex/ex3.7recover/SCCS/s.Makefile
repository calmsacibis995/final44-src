h59158
s 00000/00000/00012
d D 8.1 93/06/09 21:48:13 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00011
d D 5.4 90/07/25 11:09:02 bostic 4 3
c ex_temp.h needs DVMUNIX
e
s 00001/00001/00011
d D 5.3 90/06/25 16:52:34 bostic 3 2
c ex_vars.h got moved
e
s 00002/00002/00010
d D 5.2 90/06/19 16:15:37 bostic 2 1
c name it ex3.7recover, heaven knows why...
e
s 00012/00000/00000
d D 5.1 90/06/05 10:57:54 bostic 1 0
c date and time created 90/06/05 10:57:54 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
PROG=	exrecover
SRCS=	exrecover.c ex_extern.c
E 2
I 2
PROG=	ex3.7recover
SRCS=	ex3.7recover.c ex_extern.c
E 2
D 3
CFLAGS+=-I${.CURDIR}/..
E 3
I 3
D 4
CFLAGS+=-I${.CURDIR}/.. -I${.CURDIR}/../obj
E 4
I 4
CFLAGS+=-I${.CURDIR}/.. -I${.CURDIR}/../obj -DVMUNIX
E 4
E 3
.PATH:	${.CURDIR}/..
BINOWN=	root
BINDIR=	/usr/libexec
BINMODE=4555
NOMAN=	noman

.include <bsd.prog.mk>
E 1
