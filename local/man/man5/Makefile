#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W%	(Berkeley)	%G%
#
MDIR=	/usr/local/man/cat5
SRCS=	sccsfile.5
OBJS=	sccsfile.0
LINKS=	

.SUFFIXES: .5 .0

.5.0:
	${DESTDIR}/usr/man/manroff $*.5 > $*.0

all: ${OBJS}

clean: FRC
	rm -f ${OBJS}

install: FRC
	cd ${DESTDIR}${MDIR}; rm -f *.0
	install -c -o bin -g bin -m 444 ${OBJS} ${DESTDIR}${MDIR}

FRC:
