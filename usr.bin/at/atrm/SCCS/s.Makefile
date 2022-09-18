h26296
s 00000/00000/00008
d D 8.1 93/06/06 14:21:51 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00000/00006
d D 5.2 90/05/29 21:42:58 bostic 2 1
c needs to be setuid root
e
s 00006/00000/00000
d D 5.1 90/05/11 14:28:05 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	atrm
I 2
BINOWN=	root
BINMODE=4555
E 2

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
