h34777
s 00000/00000/00009
d D 8.1 93/07/19 09:47:58 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00008
d D 5.2 93/07/19 09:47:57 bostic 3 1
c set the immutable bit on installation
e
s 00000/00000/00008
d R 8.1 93/06/06 14:05:57 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00008/00000/00000
d D 5.1 90/05/11 16:12:59 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	sliplogin
MAN8=	sliplogin.0
BINOWN=	root
BINMODE=4555
I 3
INSTALLFLAGS=-fschg
E 3

.include <bsd.prog.mk>
E 1
