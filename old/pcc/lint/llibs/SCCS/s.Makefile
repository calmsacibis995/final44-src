h08384
s 00001/00001/00058
d D 5.3 93/05/24 17:10:10 bostic 3 2
c move to /usr/old/libdata
e
s 00016/00010/00043
d D 5.2 91/02/25 10:55:14 bostic 2 1
c lint displays the entire lint path instead of just the name
c probably not worth fixing, but what the heck.
e
s 00053/00000/00000
d D 5.1 90/06/05 14:33:31 bostic 1 0
c date and time created 90/06/05 14:33:31 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

SRCS=	llib-lc llib-lcurses llib-ldbm llib-lm llib-lmp llib-lplot \
	llib-ltermcap llib-port
LN=	llib-port.ln llib-lc.ln llib-lcurses.ln llib-ldbm.ln llib-lm.ln \
	llib-lmp.ln llib-lplot.ln llib-ltermcap.ln

D 3
BINDIR=	/usr/libdata/lint
E 3
I 3
BINDIR=	/usr/old/libdata/lint
E 3
LINKS=	${BINDIR}/llib-ltermcap ${BINDIR}/llib-ltermlib \
	${BINDIR}/llib-ltermcap.ln ${BINDIR}/llib-ltermlib.ln

all llibs: ${LN}

clean cleandir:
	rm -f ${LN}

depend lint tags:

beforeinstall:
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${SRCS} \
	    ${DESTDIR}${BINDIR}
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${LN} \
	    ${DESTDIR}${BINDIR}

.include <bsd.prog.mk>

LP1=	/usr/libexec/lintpass1

llib-port.ln: llib-port
D 2
	-(${CPP} -C -Dlint ${.CURDIR}/llib-port | ${LP1} -puv > llib-port.ln )
E 2
I 2
	-(cd ${.CURDIR}; ${CPP} -C -Dlint llib-port) | \
	    ${LP1} -puv > llib-port.ln
E 2

llib-ldbm.ln: llib-ldbm
D 2
	-(${CPP} -C -Dlint ${.CURDIR}/llib-ldbm | ${LP1} -uv > llib-ldbm.ln )
E 2
I 2
	-(cd ${.CURDIR}; ${CPP} -C -Dlint llib-ldbm) | \
	    ${LP1} -uv > llib-ldbm.ln
E 2

llib-lm.ln: llib-lm
D 2
	-(${CPP} -C -Dlint ${.CURDIR}/llib-lm | ${LP1} -uv > llib-lm.ln )
E 2
I 2
	-(cd ${.CURDIR}; ${CPP} -C -Dlint llib-lm) | \
	    ${LP1} -uv > llib-lm.ln
E 2

llib-lmp.ln: llib-lmp
D 2
	-(${CPP} -C -Dlint ${.CURDIR}/llib-lmp | ${LP1} -uv > llib-lmp.ln )
E 2
I 2
	-(cd ${.CURDIR}; ${CPP} -C -Dlint llib-lmp) | \
	    ${LP1} -uv > llib-lmp.ln
E 2

llib-lplot.ln: llib-lplot
D 2
	-(${CPP} -C -Dlint ${.CURDIR}/llib-lplot | ${LP1} -uv > llib-lplot.ln )
E 2
I 2
	-(cd ${.CURDIR}; ${CPP} -C -Dlint llib-lplot) | \
	    ${LP1} -uv > llib-lplot.ln
E 2

llib-ltermcap.ln: llib-ltermcap
D 2
	-(${CPP} -C -Dlint ${.CURDIR}/llib-ltermcap | \
	    ${LP1} -uv > llib-ltermcap.ln )
E 2
I 2
	-(${CPP} -C -Dlint ${.CURDIR}/llib-ltermcap) | \
	    ${LP1} -uv > llib-ltermcap.ln
E 2

llib-lc.ln: llib-lc
D 2
	-(${CPP} -C -Dlint ${.CURDIR}/llib-lc | ${LP1} -v > llib-lc.ln )
E 2
I 2
	-(cd ${.CURDIR}; ${CPP} -C -Dlint llib-lc) | \
	    ${LP1} -v > llib-lc.ln
E 2

llib-lcurses.ln: llib-lcurses
D 2
	-(${CPP} -C -Dlint -D__void__=__curses__ ${.CURDIR}/llib-lcurses | \
	    ${LP1} -v > llib-lcurses.ln )
E 2
I 2
	-(cd ${.CURDIR}; ${CPP} -C -Dlint -D__void__=__curses__ \
	    llib-lcurses) | ${LP1} -v > llib-lcurses.ln
E 2
E 1
