CFLAGS=cflags() nbpflags()
I=includedir()
DESTDIR=etcdest()
ETCDIR=etcdest()
CAPLIB=libcap()
# for other libraries (like BSD on hpux)
SLIB=libspecial()
PROGS=atis 
# aufs.c definitions: USEVPRINTF - use vprintf in logging
ifdef([usevprintf],[],[#])ATISDEFS=-DUSEVPRINTF

# Make sure to define needgetopt if your system doesnt have it or
# just set GETOPT=att_getopt.o (or to a getopt of your own liking)
GETOPT=ifdef([needgetopt],[att_getopt.o])

all:	${PROGS}

atis:	atis.o nisaux.o ${GETOPT}
	${CC} ${LFLAGS} -o atis atis.o nisaux.o ${GETOPT} ${CAPLIB} ${SLIB}

atis.o:	$I/netat/abnbp.h
	${CC} ${CFLAGS} ${ATISDEFS} -DETCDIR=\"${ETCDIR}\" -c atis.c

nisaux.o: $I/netat/abnbp.h

att_getopt.c:
	ln -s ../extras/att_getopt.c

install: ${PROGS}
	cp ${PROGS} ${DESTDIR}
	(cd ${DESTDIR}; strip ${PROGS})
	rm ${PROGS}
	cp start-cap-servers ${ETCDIR}

clean:
	-rm atis *.o core att_getopt.c *~

dist:
	@cat todist


