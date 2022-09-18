h38984
s 00000/00000/00011
d D 8.1 93/06/04 19:03:15 bostic 3 1
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00000/00011
d R 8.1 93/06/04 18:58:58 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00000/00000
d D 5.1 92/07/23 16:43:14 bostic 1 0
c date and time created 92/07/23 16:43:14 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	rbootd
SRCS=	bpf.c conf.c parseconf.c rbootd.c rmpproto.c utils.c
MAN8=	rbootd.0

afterinstall:
	(cd ${.CURDIR}/bootdir && install -c -o ${BINOWN} -g ${BINGRP} \
	    -m 444 * ${DESTDIR}/usr/mdec/)

.include <bsd.prog.mk>
E 1
