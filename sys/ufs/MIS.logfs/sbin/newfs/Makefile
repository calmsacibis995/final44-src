#	@(#)Makefile	8.2 (Berkeley) 3/27/94

PROG=	newfs
SRCS=	dkcksum.c getmntopts.c newfs.c mkfs.c newfs_aix.c mkwafs.c misc.c disklabel.c label.c
MAN8=	newfs.0

MOUNT=	${.CURDIR}/../mount
CFLAGS+=-DMFS -I${MOUNT}
.PATH:	${MOUNT} ${.CURDIR}/../common

LINKS=	${BINDIR}/newfs ${BINDIR}/mount_mfs
MLINKS=	newfs.8 mount_mfs.8 newfs.8 mfs.8

.include "../../lite.prog.mk"
