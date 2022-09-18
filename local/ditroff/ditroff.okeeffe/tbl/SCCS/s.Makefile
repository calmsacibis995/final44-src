h40276
s 00005/00000/00036
d D 1.2 85/10/02 16:49:26 jaap 2 1
c Added entry for install
e
s 00036/00000/00000
d D 1.1 85/10/01 17:49:59 jaap 1 0
c date and time created 85/10/01 17:49:59 by jaap
e
u
U
t
T
I 1
#	%W% (CWI) %E%
#
I 2
DESTDIR=
BINDIR=/usr/local
E 2
CFLAGS = -O
HFILES = ext.h defs.h
SOURCES = checkuse.c delimfields.c getstop.c globals.c horlines.c \
	intersect.c io.c main.c maktab.c misc.c numfields.c options.c \
	over200.c rdata.c savrstor.c specs.c subr.c textblocks.c \
	vertlines.c write1line.c writecntl.c
OBJECTS = checkuse.o delimfields.o getstop.o globals.o horlines.o \
	intersect.o io.o main.o maktab.o misc.o numfields.o options.o \
	over200.o rdata.o savrstor.o specs.o subr.o textblocks.o \
	vertlines.o write1line.o writecntl.o
#
#
#
all: tbl
I 2

install: all
	install -s tbl ${DESTDIR}${BINDIR}/tbl
E 2

tbl: ${OBJECTS}
	cc ${CFLAGS} -o tbl ${OBJECTS}

checkuse.o delimfields.o getstop.o globals.o horlines.o:	ext.h defs.h
intersect.o io.o main.o maktab.o misc.o numfields.o options.o:	ext.h defs.h
over200.o rdata.o savrstor.o specs.o subr.o textblocks.o:	ext.h defs.h
vertlines.o write1line.o writecntl.o:				ext.h defs.h

lint:
	lint -ahbcp ${SOURCES}

print:	${HFILES} ${SOURCES}
	print ${HFILES} ${SOURCES}

clean:
	rm -f *.o tbl

tblfiles:
	echo ${SOURCES} ${HFILES} > tblfiles
E 1
