h37822
s 00023/00000/00000
d D 1.1 87/03/31 23:52:51 jaap 1 0
c date and time created 87/03/31 23:52:51 by jaap
e
u
U
t
T
I 1
#
#	%M%	(CWI)	%I%	%E%
#
CFLAGS=-O
DESTDIR=
BINDIR=/usr/local
HFILES= ../dev.h
ALL= makedev dumpdev

all:	${ALL}

makedev:	makedev.c ${HFILES}
	${CC} -o makedev ${CFLAGS} makedev.c

dumpdev:	dumpdev.c ${HFILES}
	${CC} -o dumpdev ${CFLAGS} dumpdev.c

install:	all
	install -s makedev ${DESTDIR}${BINDIR}/makedev
	install -s dumpdev ${DESTDIR}${BINDIR}/dumpdev

clean:
	rm -f make.out ${ALL}
E 1
