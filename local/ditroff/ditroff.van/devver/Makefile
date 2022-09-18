#
#	%W%	(CWI)	%E%
#
# This grud needs to been cleaned one of these days
#
CFLAGS=
DESTDIR=
BINDIR=/usr/local
LIBDIR=/usr/lib
SUBDIR= vfont.desc
PROGS = dver80 vsort80
FILES = hartovermap Vtroff.sh

all:	${PROGS} ${SUBDIR}

${SUBDIR}: /tmp
	cd $@; make ${MFLAGS}

dver80.o:	dver.c
	cc -c ${CFLAGS} -DVER80 dver.c
	mv dver.o dver80.o

dver80:	graph.o dver80.o
	cc ${CFLAGS} -o dver80 graph.o dver80.o -lm

vsort80:
	cc ${CFLAGS} -DVER80  -o vsort80 vsort.c -lm

install:	all
	install -s vsort80 ${DESTDIR}${LIBDIR}/vsort80
	install -s dver80 ${DESTDIR}${LIBDIR}/dver80
	install -c -m 644 hartovermap /usr/local/lib/ditroff/font/devver/hartovermap
	install -c -m 755 Vtroff.sh ${DESTDIR}${BINDIR}/Vtroff
	for i in ${SUBDIR}; do \
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); done

clean:
	rm -f *.o ${PROGS}
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} clean); done
