#	@(#)Makefile	8.1 (Berkeley) 6/18/93

PROG=	dumpwafs
CFLAGS+= -DDIAGNOSTIC -g -I../../sys/ufs/wafs
SRCS=	dumpwafs.c dkcksum.c misc.c
.PATH:	../../sys/ufs/lfs ../common
MAN8=	

.include <../../lite.prog.mk>
