#	@(#)Makefile	5.4 (Berkeley) 10/26/90

PROG=	lpd
CFLAGS+=-I/usr/src/usr.sbin/lpr/common_source
LDADD=	-lutil
MAN8=	lpd.0
SRCS=	lpd.c printjob.c recvjob.c displayq.c rmjob.c startdaemon.c \
	lpdchar.c common.c printcap.c tcp_conn.c
.PATH:	/usr/src/usr.sbin/lpr/common_source

.include "/usr/src/usr.sbin/Makefile.inc"
.include <bsd.prog.mk>
