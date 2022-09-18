h13001
s 00001/00001/00039
d D 1.2 88/04/15 11:46:37 edward 2 1
c loadseal.1p added (for UC seal), from Greg Couch
e
s 00040/00000/00000
d D 1.1 88/03/31 23:05:20 edward 1 0
c date and time created 88/03/31 23:05:20 by edward
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%
# transcript/man/Makefile
#
# Copyright 1985 Adobe Systems Incorporated
#
# RCSID: $Header: Makefile,v 2.1 85/11/24 12:38:23 shore Rel $
# RCSLOG:
# $Log:	Makefile,v $
# Revision 2.1  85/11/24  12:38:23  shore
# Product Release 2.0
# 
# 
#

.SUFFIXES: .1 .1p .7 .7p .8 .8p

PAGES1 = enscript.1 ps4014.1 ps630.1 pscat.1 psdit.1 psplot.1 psrev.1 \
D 2
	psroff.1 ptroff.1
E 2
I 2
	psroff.1 ptroff.1 loadseal.1
E 2
PAGES7 = afm.7 postscript.7
PAGES8 = pscatmap.8 transcript.8

PAGES = ${PAGES1} ${PAGES7} ${PAGES8}

programs all: ${PAGES}

.1p.1 .7p.7 .8p.8:
	sed	-e s,XPSLIBDIRX,$$PSLIBDIR,g \
		-e s,XTROFFFONTDIRX,$$TROFFFONTDIR,g \
		-e s,XPSTEMPDIR,$$PSTEMPDIR,g \
		-e s,XDITDIRX,$$DITDIR,g \
		$? > $@

install: ${PAGES}
	cd ${MANDIR}; rm -f ${PAGES}
	./installman 1 $$MAN1
	./installman 7 $$MAN7
	./installman 8 $$MAN8

clean:
	rm -f - ${PAGES} *.BAK *.CKP .emacs_[0-9]*
E 1
