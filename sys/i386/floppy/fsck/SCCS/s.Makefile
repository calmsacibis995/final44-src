h36952
s 00000/00000/00011
d D 8.1 93/06/11 15:28:54 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00000/00000
d D 5.1 91/05/03 18:30:34 bostic 1 0
c date and time created 91/05/03 18:30:34 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	fsck
SRCS=	dir.c inode.c main.c pass1.c pass1b.c pass2.c pass3.c pass4.c \
	pass5.c preen.c setup.c utilities.c ufs_subr.c ufs_tables.c
CFLAGS+=-DLETS_GET_SMALL
NOMAN=	noman
LDFLAGS=-N
.PATH:	${.CURDIR}/../../../../sbin/fsck ${.CURDIR}/../../../ufs

.include <bsd.prog.mk>
E 1
