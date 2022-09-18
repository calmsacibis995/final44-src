SRCS=	deqn.1 ditroff.1 tbl.1 dterm.1 grn.1 ideal.1 pic.1 font.7 trchange.1
OBJS=	deqn.0 ditroff.0 tbl.0 dterm.0 grn.0 ideal.0 pic.0 font.0 trchange.0

.SUFFIXES: .1 .7 .0

.7.0:
	../../../man/manroff $*.7 > $*.0
.1.0:
	../../../man/manroff $*.1 > $*.0

all: ${OBJS}

tbl.1:	tbl.1.tbl
	tbl tbl.1.tbl > tbl.1

font.7:	font.7.tbl
	tbl font.7.tbl > font.7

install:
	install -c -o bin -g bin -m 444 deqn.0 ${DESTDIR}/usr/local/man/cat1/deqn.0
	install -c -o bin -g bin -m 444 ditroff.0 ${DESTDIR}/usr/local/man/cat1/ditroff.0
	install -c -o bin -g bin -m 444 tbl.0 ${DESTDIR}/usr/local/man/cat1/tbl.0
	install -c -o bin -g bin -m 444 dterm.0 ${DESTDIR}/usr/local/man/cat1/dterm.0
	install -c -o bin -g bin -m 444 grn.0 ${DESTDIR}/usr/local/man/cat1/grn.0
	install -c -o bin -g bin -m 444 ideal.0 ${DESTDIR}/usr/local/man/cat1/ideal.0
	install -c -o bin -g bin -m 444 pic.0 ${DESTDIR}/usr/local/man/cat1/pic.0
	install -c -o bin -g bin -m 444 font.0 ${DESTDIR}/usr/local/man/cat1/font.0
	install -c -o bin -g bin -m 444 trchange.0 ${DESTDIR}/usr/local/man/cat1/trchange.0

clean:
	rm -f tbl.1 font.7 ${OBJS}
