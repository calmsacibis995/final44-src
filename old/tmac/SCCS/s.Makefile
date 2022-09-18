h19114
s 00003/00014/00013
d D 1.2 91/10/07 21:12:08 cael 2 1
c merge into /usr/old
e
s 00027/00000/00000
d D 1.1 91/09/26 16:28:46 cael 1 0
c date and time created 91/09/26 16:28:46 by cael
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
# eliminating tmac.an.old to test tmac.an from /usr/src/.../groff/mancros/grot
# FILES=	tmac.an.old tmac.r tmac.andoc
E 2
I 2
FILES=	tmac.an.v6compat tmac.an6n tmac.an6t tmac.an
E 2

D 2
FILES=	tmac.r tmac.andoc tmac.s
MSRCS=  doc doc-ditroff doc-common doc-nroff doc-syms

LINKS=	${BINDIR}/tmac/tmac.andoc ${BINDIR}/tmac/tmac.an
E 2
NOOBJ=	noobj
I 2
BINDIR= /usr/old/lib
E 2

D 2
# old macros not currently installed...
# OFILES=	tmac.an.v6compat tmac.an6n tmac.an6t tmac.a tmac.cp

E 2
all clean cleandir depend lint tags:

beforeinstall:
D 2
	for i in ${MSRCS}; do \
		sed -f strip.sed < $$i > ${DESTDIR}${BINDIR}/tmac/tmac.$$i; \
		chown ${BINOWN}.${BINGRP} ${DESTDIR}${BINDIR}/tmac/tmac.$$i; \
		chmod 444 ${DESTDIR}${BINDIR}/tmac/tmac.$$i; \
	done
E 2
	install -c -o ${BINOWN} -g ${BINOWN} -m 444 ${FILES} \
		${DESTDIR}${BINDIR}/tmac

I 2
BINDIR= /usr/old/lib
E 2

.include <bsd.prog.mk>
E 1
