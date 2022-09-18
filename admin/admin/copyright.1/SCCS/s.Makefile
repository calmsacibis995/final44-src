h55297
s 00003/00000/00032
d D 5.5 90/07/19 15:55:34 mckusick 5 4
c add redist.tex
e
s 00002/00001/00030
d D 5.4 90/06/29 16:49:23 bostic 4 3
c add att.man 
e
s 00000/00001/00031
d D 5.3 90/06/22 19:04:07 bostic 3 2
c need an obj directory
e
s 00002/00010/00030
d D 5.2 90/06/08 14:33:04 bostic 2 1
c don't need obj, use bsd.prog.mk
e
s 00040/00000/00000
d D 5.1 90/06/01 18:19:33 bostic 1 0
c date and time created 90/06/01 18:19:33 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

BUILD=	redist.c redist.sh redist.man redist.gas
D 4
STD=	386.c contrib hdrs kern libc libs libs.cci main make man sh src
E 4
I 4
STD=	386.c att.man contrib hdrs kern libc libs libs.cci main make \
	man sh src
E 4
I 2
D 3
NOOBJ=	noobj
E 3
E 2

all: ${BUILD}

clean cleandir:
	rm -f redist.c redist.sh redist.man redist.gas

install:
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${STD} \
	    ${DESTDIR}${BINDIR}/copyright
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${BUILD} \
	    ${DESTDIR}${BINDIR}/copyright

D 2
all: ${BUILD}

clean cleandir:
	rm -f redist.c redist.sh redist.man redist.gas

install:
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${STD} \
	    ${STD} ${DESTDIR}${BINDIR}/copyright

E 2
depend lint tags:

redist.c: redist
	sed 's/^/ */' < ${.CURDIR}/redist > redist.c

redist.sh: redist
	sed 's/^/#/' < ${.CURDIR}/redist > redist.sh

redist.man: redist
	sed 's/^/.\\"/' < ${.CURDIR}/redist > redist.man

redist.gas: redist
	sed 's/^/|/' < ${.CURDIR}/redist > redist.gas

I 5
redist.tex: redist
	sed 's/^/%/' < ${.CURDIR}/redist > redist.tex

E 5
D 2
.include <bsd.own.mk>
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
