#
#	%M%	(CWI)	%I%	%E%
#
CFLAGS=-O
DESTDIR=
BINDIR=/usr/local
OBJFILES=dhar.o draw.o llio.o

all:	dhar FONTS

FONTS:
	cd fonts; make ${MFLAGS} all

dhar:	${OBJFILES}
	${CC} -o dhar ${CFLAGS} ${OBJFILES}  -lm

dhar.o:	../dev.h hcodes.h
llio.o:	llio.h

install:	all
	install -s dhar ${DESTDIR}${BINDIR}/dhar
	install -c -m 644 dhar.1 ${DESTDIR}/usr/man/manl/dhar.1
	cd fonts; make ${MFLAGS} DESTDIR=${DESTDIR} install

clean:
	rm -f make.out *.o dhar
