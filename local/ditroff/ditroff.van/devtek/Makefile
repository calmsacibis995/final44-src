#
#	%M%	(CWI)	%I%	%E%
#
CFLAGS=-O
DESTDIR=
BINDIR=/usr/local
OBJFILES=tc.o ../devhar/draw.o

all:	tc

tc:	${OBJFILES}
	${CC} -o tc ${CFLAGS} ${OBJFILES}  -lm

tc.o:	../dev.h

../devhar/draw.o:
	cd ../devhar; make draw.o

install:	all
	install -s tc ${DESTDIR}${BINDIR}/tc
	install -c -m 644 tc.1 ${DESTDIR}/usr/man/manl/tc.1

clean:
	rm -f make.out *.o tc
