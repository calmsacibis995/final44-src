#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W%	(Berkeley)	%G%
#
MDIR1=	/usr/local/man/cat1
SRC1=	admin.1 chghist.1 comb.1 delta.1 get.1 prt.1 rmdel.1 sccs.1 \
	sccsdiff.1 what.1
OBJ1=	admin.0 chghist.0 comb.0 delta.0 get.0 prt.0 rmdel.0 sccs.0 \
	sccsdiff.0 what.0
MDIR5=	/usr/local/man/cat5
SRC5=	sccsfile.5
OBJ5=	sccsfile.0

.SUFFIXES: .5 .1 .0

.5.0:
	../../../man/manroff $*.5 > $*.0
.1.0:
	../../../man/manroff $*.1 > $*.0

all:

install: ${OBJ5} ${OBJ1} FRC
	cp -p ${OBJ5} ${DESTDIR}${MDIR5}
	chown bin.bin ${DESTDIR}${MDIR5}/*.0
	chmod 444 ${DESTDIR}${MDIR5}/*.0
	cp -p ${OBJ1} ${DESTDIR}${MDIR1}
	chown bin.bin ${DESTDIR}${MDIR1}/*.0
	chmod 444 ${DESTDIR}${MDIR1}/*.0

clean:
depend:
FRC:
