# All these are not really CAP related
CFLAGS=-O
LFLAGS=
MAC_EFSSRC=/usr/src/local/mac/efs/src/mac
CAPLIB=-lcap
O=
PROGS=iwif
DESTDIR=/usr/local/lib

all:	${PROGS}

iwif:	iwif.o $(O)
	cc ${LFLAGS} -o iwif iwif.o

install: ${PROGS}
	cp ${PROGS} ${DESTDIR}
	(cd ${DESTDIR}; strip ${PROGS})
	rm ${PROGS}

clean:
	-rm ${PROGS} *.o core make.log err *~

cleanexe:
	-rm ${PROGS}

dist:
	@cat todist
