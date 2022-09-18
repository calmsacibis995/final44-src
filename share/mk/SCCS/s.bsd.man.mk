h36731
s 00000/00000/00058
d D 8.1 93/06/08 11:35:47 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00028/00057
d D 5.2 90/05/11 12:08:55 bostic 2 1
c make man specific, move LINKS to bsd.prog.mk, LIB to bsd.lib.mk
e
s 00085/00000/00000
d D 5.1 90/05/10 17:22:48 bostic 1 0
c date and time created 90/05/10 17:22:48 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

.if exists(${.CURDIR}/../Makefile.inc)
.include "${.CURDIR}/../Makefile.inc"
.endif

D 2
MANDIR?=	/usr/share/man/cat
E 2
MANGRP?=	bin
MANOWN?=	bin
MANMODE?=	444

D 2
BINGRP?=	bin
BINOWN?=	bin
BINMODE?=	555
E 2
I 2
MANDIR?=	/usr/share/man/cat
E 2

D 2
LIBDIR?=	/usr/lib
LINTLIBDIR?=	/usr/libdata/lint
LIBGRP?=	bin
LIBOWN?=	bin
LIBMODE?=	444

INCOWN?=	bin
INCGRP?=	bin
INCMODE?=	444

STRIP?=		-s

E 2
MINSTALL=	install -c -o ${MANOWN} -g ${MANGRP} -m ${MANMODE}

maninstall:
.if defined(MAN1) && !empty(MAN1)
	${MINSTALL} ${MAN1} ${DESTDIR}${MANDIR}1${MANSUBDIR}
.endif
.if defined(MAN2) && !empty(MAN2)
	${MINSTALL} ${MAN2} ${DESTDIR}${MANDIR}2${MANSUBDIR}
.endif
.if defined(MAN3) && !empty(MAN3)
	${MINSTALL} ${MAN3} ${DESTDIR}${MANDIR}3${MANSUBDIR}
.endif
.if defined(MAN3F) && !empty(MAN3F)
	${MINSTALL} ${MAN3F} ${DESTDIR}${MANDIR}3f${MANSUBDIR}
.endif
.if defined(MAN4) && !empty(MAN4)
	${MINSTALL} ${MAN4} ${DESTDIR}${MANDIR}4${MANSUBDIR}
.endif
.if defined(MAN5) && !empty(MAN5)
	${MINSTALL} ${MAN5} ${DESTDIR}${MANDIR}5${MANSUBDIR}
.endif
.if defined(MAN6) && !empty(MAN6)
	${MINSTALL} ${MAN6} ${DESTDIR}${MANDIR}6${MANSUBDIR}
.endif
.if defined(MAN7) && !empty(MAN7)
	${MINSTALL} ${MAN7} ${DESTDIR}${MANDIR}7${MANSUBDIR}
.endif
.if defined(MAN8) && !empty(MAN8)
	${MINSTALL} ${MAN8} ${DESTDIR}${MANDIR}8${MANSUBDIR}
D 2
.endif
.if defined(LINKS) && !empty(LINKS)
	@set ${LINKS}; \
	while test $$# -ge 2; do \
		l=${DESTDIR}$$1; \
		shift; \
		t=${DESTDIR}$$1; \
		shift; \
		echo $$t -\> $$l; \
		rm -f $$t; \
		ln $$l $$t; \
	done; true
E 2
.endif
.if defined(MLINKS) && !empty(MLINKS)
	@set ${MLINKS}; \
	while test $$# -ge 2; do \
		name=$$1; \
		shift; \
		dir=${DESTDIR}${MANDIR}`expr $$name : '[^\.]*\.\(.*\)'`; \
		l=$${dir}${MANSUBDIR}/`expr $$name : '\([^\.]*\)'`.0; \
		name=$$1; \
		shift; \
		dir=${DESTDIR}${MANDIR}`expr $$name : '[^\.]*\.\(.*\)'`; \
		t=$${dir}${MANSUBDIR}/`expr $$name : '\([^\.]*\)'`.0; \
		echo $$t -\> $$l; \
		rm -f $$t; \
		ln $$l $$t; \
	done; true
.endif
E 1
