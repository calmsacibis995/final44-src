h02735
s 00011/00004/00050
d D 1.2 87/04/01 16:36:59 jaap 2 1
c cleanup
e
s 00054/00000/00000
d D 1.1 85/03/01 17:03:15 jaap 1 0
c date and time created 85/03/01 17:03:15 by jaap
e
u
U
t
T
I 1
#
#	%M%	(CWI)	%I%	%E%
#
# BINDIR is the place where ideal will be installed
BINDIR = /usr/local
# DESTDIR is the destination where we want to move the thing (temporarily)
DESTDIR =
# LIBDIR is the place where we expect the the things we need and is
# is therefore hardwired in. Since it is all local, we use BINDIR as well
LIBDIR = ${BINDIR}/lib/ideal/lib
# pfilt is ideal filter for plot(1)
# tfilt is filter for ditroff
# idsort is general sort for ideal
D 2
OBJECTS = tfilt pfilt idsort
E 2
I 2
OBJECTS = tfilt pfilt idsort vfilt 4filt
E 2

all:	${OBJECTS}

idfilt.o	:idfilt.c idfilt.h

4014.o	:4014.c idfilt.h

4filt	:idfilt.o 4014.o
	cc -o 4filt 4014.o idfilt.o -l4014 -lm

pout.o	:pout.c

pfilt	:idfilt.o pout.o
	cc -o pfilt pout.o idfilt.o -lplot -lm

202.o	:202.c idfilt.h

202filt	:idfilt.o 202.o
	cc -o tfilt 202.o idfilt.o

har.o	:har.c idfilt.h

I 2
ver.o	:ver.c idfilt.h

vfilt	:idfilt.o ver.o
	cc -o vfilt ver.o idfilt.o

E 2
tfilt	:idfilt.o har.o
	cc -o tfilt har.o idfilt.o

aps.o	:aps.c

apsfilt	:aps.o idfilt.o
	cc -o apsfilt aps.o idfilt.o

idsort	:idsort.c
	cc -o idsort idsort.c

install: all
D 2
	install -s tfilt ${DESTDIR}/${LIBDIR}/tfilt
	install -s pfilt ${DESTDIR}/${LIBDIR}/pfilt
	install -s idsort ${DESTDIR}/${LIBDIR}/idsort
E 2
I 2
	install -s tfilt ${DESTDIR}${LIBDIR}/tfilt
	install -s 4filt ${DESTDIR}${LIBDIR}/4filt
	install -s pfilt ${DESTDIR}${LIBDIR}/pfilt
	install -s vfilt ${DESTDIR}${LIBDIR}/vfilt
	install -s idsort ${DESTDIR}${LIBDIR}/idsort
E 2

clean:
	rm -f *.o ${OBJECTS}
E 1
