# transcript/sh/Makefile
#
# Copyright 1985 Adobe Systems Incorporated
#
# RCSID: $Header: Makefile,v 2.1 85/11/24 12:31:56 shore Rel $
# RCSLOG:
# $Log:	Makefile,v $
# Revision 2.1  85/11/24  12:31:56  shore
# Product Release 2.0
# 
#

programs all: ptroff psroff

ptroff: ptroff.sh
	sed	-e s,TROFFFONTDIR,$$TROFFFONTDIR,g \
		ptroff.sh >ptroff

psroff: psroff.sh
	cp psroff.sh psroff

install: psroff ptroff
	cp ptroff psroff $$BINDIR
	chown $$OWNER $$BINDIR/ptroff $$BINDIR/psroff
	chgrp $$GROUP $$BINDIR/ptroff $$BINDIR/psroff
	chmod 755 $$BINDIR/ptroff $$BINDIR/psroff

clean:
	-rm -f - ptroff psroff *.BAK *.CKP .emacs_[0-9]*
