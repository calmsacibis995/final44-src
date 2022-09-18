h06471
s 00000/00000/00020
d D 8.1 93/06/06 15:03:11 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00019
d D 5.3 90/06/08 14:41:44 bostic 3 2
c use bsd.prog.mk
e
s 00005/00003/00015
d D 5.2 90/05/24 15:54:10 bostic 2 1
c do DESTDIR right
e
s 00018/00000/00000
d D 5.1 90/05/11 16:01:52 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

OBJS=	getline.o getnum.o

all objects: ${OBJS}

clean cleandir:
	rm -f ${OBJS}

depend lint tags:

install:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/getline.c \
D 2
	    ${.CURDIR}/getnum.c ${LLIB}/learn/C
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${OBJS} ${LLIB}/learn/bin
	install -o ${BINOWN} -g ${BINGRP} -m 444 ${OBJS} ${LLIB}/learn/C
E 2
I 2
	    ${.CURDIR}/getnum.c ${DESTDIR}${LLIB}/learn/C
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${OBJS} \
	    ${DESTDIR}${LLIB}/learn/bin
	install -o ${BINOWN} -g ${BINGRP} -m 444 ${OBJS} \
	    ${DESTDIR}${LLIB}/learn/C
E 2

D 3
.include <bsd.own.mk>
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
