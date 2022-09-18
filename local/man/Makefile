#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W%	(Berkeley)	%G%
#

DIRS=	man1 man2 man3 man4 man5 man6 man7 man8

all:
	for i in ${DIRS}; do \
		(cd $$i; make ${MFLAGS}); \
	done

install: FRC
	for i in ${DIRS}; do \
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); \
	done
	for file in `find /usr/local/man -type f -name '*.0' -print`; do \
		sed -n -f /usr/man/makewhatis.sed $$file; \
	done | sort -u > whatis.db
	install -o bin -g bin -m 444 whatis.db ${DESTDIR}/usr/local/man/whatis

manclean: FRC
	for i in ${DIRS}; do \
		(cd $$i; make ${MFLAGS} clean); \
	done

clean:
depend:
lint:
tags:
FRC:
