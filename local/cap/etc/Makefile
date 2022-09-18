# Makefile autoconfigured for a: \
	SunOS system on Wed Sep 14 03:40:07 PDT 1988



MFLAGS=
LFLAGS=
CC=cc
LD=ld
CFLAGS=-O -DSYSLOG -I/usr/include/4.3syslog 
I=/usr/include
DESTDIR=/etc
ETCDIR=/etc
CAPLIB=-lcap
# for other libraries (like BSD on hpux)
SLIB= -lsyslog
PROGS=atis 
# aufs.c definitions: USEVPRINTF - use vprintf in logging
ATISDEFS=-DUSEVPRINTF

# Make sure to define needgetopt if your system doesnt have it or
# just set GETOPT=att_getopt.o (or to a getopt of your own liking)
GETOPT=

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


