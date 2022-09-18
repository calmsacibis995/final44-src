h33216
s 00012/00000/00000
d D 5.1 90/05/31 16:39:41 bostic 1 0
c date and time created 90/05/31 16:39:41 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	talk
CFLAGS+=-I${.CURDIR}/../common_source
SRCS=	ctl.c ctl_transact.c display.c get_addrs.c get_names.c init_disp.c \
	invite.c io.c look_up.c msgs.c talk.c
DPADD=	${LIBCURSES} ${LIBTERMCAP}
LDADD=	-lcurses -ltermcap
NOMAN=	noman

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
