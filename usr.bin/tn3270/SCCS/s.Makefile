h22007
s 00000/00000/00009
d D 8.1 93/06/06 16:35:15 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00000/00000
d D 5.1 93/05/11 10:02:21 bostic 1 0
c date and time created 93/05/11 10:02:21 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

SUBDIR=	tn3270 mset

.if !make(install)
SUBDIR+=tools
.endif

.include <bsd.subdir.mk>
E 1
