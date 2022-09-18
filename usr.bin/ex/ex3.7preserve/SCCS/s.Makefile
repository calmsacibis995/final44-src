h41344
s 00000/00000/00010
d D 8.1 93/06/09 21:47:48 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 5.3 90/07/25 14:11:35 bostic 3 2
c needs VMUNIX
e
s 00001/00001/00009
d D 5.2 90/06/19 16:13:11 bostic 2 1
c name it ex3.7preserve, heaven knows why...
e
s 00010/00000/00000
d D 5.1 90/06/05 10:57:58 bostic 1 0
c date and time created 90/06/05 10:57:58 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
PROG=	expreserve
E 2
I 2
PROG=	ex3.7preserve
E 2
D 3
CFLAGS+=-I${.CURDIR}/..
E 3
I 3
CFLAGS+=-I${.CURDIR}/.. -DVMUNIX
E 3
BINOWN=	root
BINDIR=	/usr/libexec
BINMODE=4555
NOMAN=	noman

.include <bsd.prog.mk>
E 1
