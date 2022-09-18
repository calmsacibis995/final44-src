h14597
s 00000/00000/00010
d D 8.1 93/06/05 13:50:49 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 5.5 93/06/05 13:50:40 bostic 6 4
c add a man page from Chris Demetrios
e
s 00000/00000/00010
d R 8.1 93/06/04 18:55:53 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00003/00010
d D 5.4 93/04/27 16:07:07 bostic 4 3
c getloadavg(3) moves to libc, lfs_cleanerd no longer needs libutil or libkvm
e
s 00001/00001/00012
d D 5.3 92/10/24 09:59:04 margo 3 2
c Compile with DIAGNOSTICS for awhile.
e
s 00001/00001/00012
d D 5.2 92/08/28 18:13:08 bostic 2 1
c Turn off verbose
e
s 00013/00000/00000
d D 5.1 92/08/06 12:38:29 bostic 1 0
c date and time created 92/08/06 12:38:29 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	lfs_cleanerd
D 2
CFLAGS+=-I/sys/ufs/lfs -I${.CURDIR} -DVERBOSE
E 2
I 2
D 3
CFLAGS+=-I/sys/ufs/lfs -I${.CURDIR}
E 3
I 3
CFLAGS+=-I/sys/ufs/lfs -I${.CURDIR} -DDIAGNOSTIC
I 6
MAN8=	lfs_cleanerd.0
E 6
E 3
E 2
SRCS=	cleanerd.c lfs_cksum.c library.c misc.c print.c
D 4

E 4
D 6
.PATH:	/sys/ufs/lfs
E 6

D 4
LDADD=	-lutil -lkvm
DPADD=	${LIBUTIL} ${LIBKVM}
E 4
D 6
NOMAN=	noman
E 6
I 6
.PATH:	/sys/ufs/lfs
E 6

.include <bsd.prog.mk>
E 1
