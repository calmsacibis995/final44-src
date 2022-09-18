h58966
s 00002/00001/00039
d D 1.4 93/07/27 09:17:52 bostic 4 3
c checkpoint; Mike Karels left this checked out.
e
s 00003/00005/00037
d D 1.3 88/04/15 11:41:18 edward 3 2
c UC seal from Greg Couch
e
s 00007/00011/00035
d D 1.2 88/03/26 19:58:04 karels 2 1
c get serious, we don't need *3* copies of the font crap!
e
s 00046/00000/00000
d D 1.1 88/03/22 09:53:06 karels 1 0
c date and time created 88/03/22 09:53:06 by karels
e
u
U
t
T
I 2
# %W% (Berkeley) %G%
E 2
I 1
# transcript/lib/Makefile.bsd
#
# Copyright (c) 1985 Adobe Systems Incorporated. All Rights Reserved. 
#
# RCSID: $Header: Makefile.bsd,v 2.1 85/11/24 12:19:06 shore Rel $

PSLIBDIR = /usr/local/lib/ps

FILES = banner.pro enscript.pro pstext.pro \
	ps4014.pro ps630.pro ps4014.pro pscat.pro psplot.pro psdit.pro \
D 3
	ehandler.ps uartpatch.ps bogusmsg.ps \
E 3
I 3
	ehandler.ps uartpatch.ps bogusmsg.ps ucseal.ps \
E 3
	font.map

D 3
PRG = psint.sh psbad.sh
E 3
I 3
PRG = psint.sh psbad.sh loadseal.sh
E 3

D 2
OWNER = daemon
GROUP = tex
E 2
I 2
OWNER = bin
GROUP = bin
E 2

programs all:
	sed -e s,XPSLIBDIRX,$(PSLIBDIR),g psint.proto > psint.sh

install: 
D 4
	cd $(PSLIBDIR); rm -rf - ${FILES} ${PRG} *.afm 
E 4
I 4
	cd $(PSLIBDIR); rm -rf - ${FILES} ${PRG} *.afm \
		psif psof psnf pstf psgf psvf psdf pscf psrf psbad loadseal
E 4
D 2
	cp ${FILES} ${PRG} *.afm $(PSLIBDIR)
	cd $(PSLIBDIR); chown $(OWNER) ${FILES} ${PRG} *.afm; \
		chgrp $(GROUP) ${FILES} ${PRG} *.afm; \
E 2
I 2
	cp -p ${FILES} ${PRG} *.afm $(PSLIBDIR)
	cd $(PSLIBDIR); chown $(OWNER).$(GROUP) ${FILES} ${PRG} *.afm; \
E 2
		chmod 664 ${FILES} *.afm; \
		chmod 775 ${PRG}
	cd $(PSLIBDIR); \
		ln psint.sh psif; ln psint.sh psof; ln psint.sh psnf; \
		ln psint.sh pstf; ln psint.sh psgf; ln psint.sh psvf; \
		ln psint.sh psdf; ln psint.sh pscf; ln psint.sh psrf; \
D 3
		ln psbad.sh psbad
	-rm -rf $(PSLIBDIR)/troff.font $(PSLIBDIR)/ditroff.font
	-mkdir $(PSLIBDIR)/troff.font $(PSLIBDIR)/ditroff.font
E 3
I 3
		ln psbad.sh psbad; ln loadseal.sh loadseal
E 3
D 2
	cp troff.font/* $(PSLIBDIR)/troff.font
	cd $(PSLIBDIR)/troff.font; make ${MFLAGS} install
	cd $(PSLIBDIR)/troff.font; chown $(OWNER) . * ; chgrp $(GROUP) . *
	cp ditroff.font/* $(PSLIBDIR)/ditroff.font
	-cd $(PSLIBDIR)/ditroff.font; make ${MFLAGS} install
	-cd $(PSLIBDIR)/ditroff.font; chown $(OWNER) . * ; chgrp $(GROUP) . *
E 2
I 2
	cd troff.font; make ${MFLAGS} install
	cd ditroff.font; make ${MFLAGS} install
E 2

clean:
	rm -f - *.BAK *.CKP .emacs_[0-9]*
	cd troff.font; make ${MFLAGS} clean
	cd ditroff.font; make ${MFLAGS} clean
E 1
