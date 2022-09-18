h38132
s 00001/00001/00011
d D 5.2 93/05/20 16:20:10 bostic 2 1
c add nfs
e
s 00012/00000/00000
d D 5.1 90/06/30 15:00:03 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

BINDIR=	/usr/share/doc/papers
FILES=	Makefile
SUBDIR=	beyond4.3 diskperf fsinterface future gprof kernmalloc kerntune \
D 2
	memfs newvm px relengr sysperf
E 2
I 2
	memfs newvm nfs px relengr sysperf
E 2

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${FILES} \
	    ${DESTDIR}${BINDIR}

.include <bsd.subdir.mk>
E 1
