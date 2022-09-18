CFLAGS=cflags()
I=includedir()

O=

# Make sure to define needgetopt if your system doesnt have it
GETOPT=ifdef([needgetopt],[att_getopt.o])

PROGS=snitch cvt2apple cvt2cap

DESTDIR=capdestdir()
CAPLIB=libcap()
# for other libraries (like BSD on hpux)
SLIB=libspecial()

all:	${PROGS}

snitch: snitch.o ${O} ${GETOPT}
	${CC} ${LFLAGS} -o snitch snitch.o ${GETOPT} ${O} ${CAPLIB} ${SLIB}

cvt2apple: cvt2apple.o ${O}
	${CC} ${LFLAGS} -o cvt2apple cvt2apple.o ${O}

cvt2cap: cvt2cap.o ${O}
	${CC} ${LFLAGS} -o cvt2cap cvt2cap.o ${O}

install: ${PROGS}
	cp ${PROGS} ${DESTDIR}
	(cd ${DESTDIR}; strip ${PROGS})
	rm ${PROGS}

att_getopt.c:
	ln -s ../extras/att_getopt.c

clean:
	-rm ${PROGS} *.o core make.log err att_getopt.c *~

cleanexe:
	-rm ${PROGS}

dist:
	@cat todist
