h37944
s 00000/00000/00009
d D 8.1 93/06/18 15:11:50 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00008
d D 5.2 93/06/18 15:11:31 bostic 3 1
c add a man page
e
s 00000/00000/00009
d R 8.1 93/06/05 10:54:49 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00000/00000
d D 5.1 91/12/31 17:00:36 bostic 1 0
c date and time created 91/12/31 17:00:36 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	dumplfs
CFLAGS+=-I/sys/ufs/lfs
SRCS=	dumplfs.c lfs_cksum.c misc.c
.PATH:	/sys/ufs/lfs
D 3
NOMAN=	noman
E 3
I 3
MAN8=	dumplfs.0
E 3

.include <bsd.prog.mk>
E 1
