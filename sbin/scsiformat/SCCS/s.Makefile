h33075
s 00001/00001/00006
d D 5.3 93/06/05 12:38:48 bostic 3 2
c man page from Chris T.
e
s 00001/00001/00006
d D 5.2 92/07/20 15:50:12 bostic 2 1
c minor cleanup, update, fix argument processing (which I broke)
e
s 00007/00000/00000
d D 5.1 92/07/20 12:09:06 bostic 1 0
c date and time created 92/07/20 12:09:06 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	scsiformat
I 3
MAN8=	scsiformat.0
E 3
D 2
CFLAGS=-I/sys
E 2
I 2
CFLAGS+=-I/sys
E 2
D 3
NOMAN=	noman
E 3

.include <bsd.prog.mk>
E 1
