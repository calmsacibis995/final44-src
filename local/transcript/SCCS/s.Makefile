h43165
s 00001/00001/00048
d D 1.2 88/03/22 09:51:02 karels 2 1
c update for current config
e
s 00049/00000/00000
d D 1.1 88/03/22 09:46:35 karels 1 0
c date and time created 88/03/22 09:46:35 by karels
e
u
U
t
T
I 2
#	%W% (Berkeley) %G%
E 2
I 1
# transcript/Makefile.bsd
#
# Copyright 1985 (C) Adobe Systems Incorporated
#
# RCSID: $Header: Makefile.bsd,v 2.1 85/11/24 12:34:05 shore Rel $
#
# to install transcript:
#
#	(Once for your system)
#		bsd
#		edit config & printer
#		make programs
#
#		(become super-user)
#		make install		( install files in system dirs )
#
#	(For each PostScript/TranScript printer)
#		cd etc
#		(become super-user)
#		mkprinter PRINTER TTY
#

explain:
	@cat doc/make.notes

programs:
	. ./config; cd lib; make ${MFLAGS} programs
	. ./config; cd man; make ${MFLAGS} programs
	. ./config; cd sh;  make ${MFLAGS} programs
	. ./config; cd src; make ${MFLAGS} programs

install:
D 2
	-. ./config; mv $$PSLIBDIR $$PSLIBDIR.old
E 2
	-. ./config; mkdir $$PSLIBDIR; chown $$OWNER $$PSLIBDIR; \
		chgrp $$GROUP $$PSLIBDIR; chmod 755 $$PSLIBDIR
	. ./config; cd src; make ${MFLAGS} install
	. ./config; cd sh;  make ${MFLAGS} install
	. ./config; cd lib; make ${MFLAGS} install
	. ./config; cd man; make ${MFLAGS} install

clean:
	rm -f *BAK *CKP .emacs_[0-9]*

cleanall: clean
	cd etc; make ${MFLAGS} clean
	cd lib; make ${MFLAGS} clean
	cd man; make ${MFLAGS} clean
	cd  sh; make ${MFLAGS} clean
	cd src; make ${MFLAGS} clean
E 1
