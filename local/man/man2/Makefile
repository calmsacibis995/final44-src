#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W%	(Berkeley)	%G%
#
MDIR=	/usr/local/man/cat2
SRCS=	
OBJS=	
LINKS=	

.SUFFIXES: .2 .0

.2.0:
	${DESTDIR}/usr/man/manroff $*.2 > $*.0

all: ${OBJS}

clean: FRC
	rm -f ${OBJS}

install:

xinstall: FRC
	cd ${DESTDIR}${MDIR}; rm -f *.0
	install -c -o bin -g bin -m 444 ${OBJS} ${DESTDIR}${MDIR}

FRC:
