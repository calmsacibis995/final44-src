#	@(#)Makefile	8.1 (Berkeley) 6/5/93

PROG=	lfs_cleanerd
# CFLAGS+=-g -I${.CURDIR} -DDIAGNOSTIC -DVERBOSE
CFLAGS+=-g -I${.CURDIR} -DDIAGNOSTIC
LDFLAGS += -g
MAN8=	lfs_cleanerd.0
SRCS=	cleanerd.c lfs_cksum.c library.c misc.c print.c

.PATH:	/usr2/src//sys/ufs/lfs

.include <../../lite.prog.mk>
