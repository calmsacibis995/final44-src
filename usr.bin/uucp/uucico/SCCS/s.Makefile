h35668
s 00000/00000/00013
d D 8.1 93/06/06 22:12:43 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00013/00000/00000
d D 5.1 91/03/02 13:15:16 bostic 1 0
c date and time created 91/03/02 13:15:16 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	uucico
SRCS=	chksum.c cico.c cntrl.c condevs.c conn.c fio.c gio.c gnsys.c \
	imsg.c pk0.c pk1.c tio.c
CFLAGS+=-I${.CURDIR}/../includes
BINDIR=	${LIBDIR}
BINMODE=6555
DPADD=	${LIBCOMPAT}
LDADD=	${LIBUU} ${LIBACU} -lcompat
MAN8=	uucico.0

.include <bsd.prog.mk>
E 1
