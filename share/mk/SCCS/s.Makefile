h63645
s 00000/00000/00012
d D 8.1 93/06/08 11:35:39 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00010
d D 5.3 90/06/22 19:05:01 bostic 3 2
c don't use an obj directory, add bsd.doc.mk
e
s 00002/00001/00010
d D 5.2 90/06/08 14:35:24 bostic 2 1
c don't need obj, use bsd.prog.mk
e
s 00011/00000/00000
d D 5.1 90/06/01 10:32:23 bostic 1 0
c date and time created 90/06/01 10:32:23 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 3
FILES=	bsd.lib.mk bsd.man.mk bsd.own.mk bsd.prog.mk bsd.subdir.mk sys.mk
E 3
I 3
FILES=	bsd.doc.mk bsd.lib.mk bsd.man.mk bsd.prog.mk bsd.subdir.mk sys.mk
E 3
I 2
NOOBJ=	noobj
E 2

all clean cleandir depend lint tags:

install:
D 3
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINOWN} -m 444 ${FILES} \
E 3
I 3
	install -c -o ${BINOWN} -g ${BINOWN} -m 444 ${FILES} \
E 3
	    ${DESTDIR}${BINDIR}/mk

D 2
.include <bsd.own.mk>
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
