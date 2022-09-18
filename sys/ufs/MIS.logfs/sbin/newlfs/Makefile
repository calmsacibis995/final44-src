#	@(#)Makefile	8.1 (Berkeley) 6/18/93

PROG=	newlfs
CFLAGS+=-I/usr2/src/sys/ufs/lfs
SRCS=	dkcksum.c lfs.c lfs_cksum.c misc.c newfs.c
MAN8=	newlfs.0
.PATH:	/sys/ufs/lfs ${.CURDIR}/../common

.include <../../lite.prog.mk>
