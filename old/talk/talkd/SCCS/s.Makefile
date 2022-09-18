h23048
s 00009/00000/00000
d D 5.1 90/05/31 16:39:47 bostic 1 0
c date and time created 90/05/31 16:39:47 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	talkd
CFLAGS+=-I${.CURDIR}/../common_source
NOMAN=	noman
SRCS=	announce.c print.c process.c table.c talkd.c

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
