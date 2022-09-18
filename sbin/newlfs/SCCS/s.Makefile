h57081
s 00000/00000/00009
d D 8.1 93/06/18 15:14:37 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00008
d D 5.4 93/06/18 15:14:31 bostic 5 3
c add a man page
e
s 00000/00000/00009
d R 8.1 93/06/05 11:07:24 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00008
d D 5.3 92/01/19 10:27:21 bostic 3 2
c extra -O
e
s 00001/00001/00008
d D 5.2 91/12/31 17:06:19 bostic 2 1
c get dkcksum from disklabel subdirectory
e
s 00009/00000/00000
d D 5.1 91/12/31 17:04:28 bostic 1 0
c date and time created 91/12/31 17:04:28 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	newlfs
D 3
CFLAGS+=-O -I/sys/ufs/lfs
E 3
I 3
CFLAGS+=-I/sys/ufs/lfs
E 3
SRCS=	dkcksum.c lfs.c lfs_cksum.c misc.c newfs.c
D 5
NOMAN=	noman
E 5
I 5
MAN8=	newlfs.0
E 5
D 2
.PATH:	/sys/ufs/lfs
E 2
I 2
.PATH:	/sys/ufs/lfs ${.CURDIR}/../disklabel
E 2

.include <bsd.prog.mk>
E 1
