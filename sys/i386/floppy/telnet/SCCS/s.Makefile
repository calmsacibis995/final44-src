h01616
s 00000/00000/00014
d D 8.1 93/06/11 15:32:35 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00006/00009
d D 5.2 91/05/10 14:45:27 william 2 1
c make a smaller telnet
e
s 00015/00000/00000
d D 5.1 91/05/03 19:15:56 bostic 1 0
c date and time created 91/05/03 19:15:56 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	telnet
SRCS=	authenc.c commands.c main.c network.c ring.c sys_bsd.c telnet.c \
D 2
	terminal.c tn3270.c utilities.c
CFLAGS+=-DLETS_GET_SMALL -DTERMCAP -DKLUDGELINEMODE -DUSE_TERMIO \
	-DAUTHENTICATE -DENCRYPT -DKRB4 -I${.CURDIR}/../../../../lib
LDADD=  -ltermcap -ltelnet -lkrb -ldes
DPADD=  ${LIBTERMCAP} ${LIBTELNET} ${LIBKRB} ${LIBDES}
E 2
I 2
	terminal.c utilities.c
CFLAGS+=-s -N -DLETS_GET_SMALL -DTERMCAP -DUSE_TERMIO \
	-I${.CURDIR}/../../../../lib
LDADD=  -ltelnet -ltermcap
DPADD=  ${LIBTELNET} ${LIBTERMCAP}
E 2

NOMAN=	noman
D 2
LDFLAGS=-N
E 2
.PATH:	${.CURDIR}/../../../../usr.bin/telnet

.include <bsd.prog.mk>
E 1
