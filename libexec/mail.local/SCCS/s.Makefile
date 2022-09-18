h54475
s 00000/00000/00009
d D 8.1 93/07/19 09:48:57 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00008
d D 5.4 93/07/19 09:48:56 bostic 5 3
c set the immutable bit on installation
e
s 00000/00000/00008
d R 8.1 93/06/04 18:56:26 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00006
d D 5.3 91/01/17 14:39:25 bostic 3 2
c from scratch -- /bin/mail was a security problem, and not worth fixing
e
s 00001/00000/00007
d D 5.2 90/06/29 17:05:08 bostic 2 1
c move man page to section 8
e
s 00007/00000/00000
d D 5.1 90/05/11 12:54:12 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 3
PROG=	delivermail
I 2
MAN8=	delivermail.0
E 3
I 3
PROG=	mail.local
MAN8=	mail.local.0
E 3
E 2
BINOWN=	root
BINMODE=4555
I 5
INSTALLFLAGS=-fschg
E 5

.include <bsd.prog.mk>
E 1
