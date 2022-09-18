h60968
s 00001/00001/00017
d D 5.5 91/04/30 14:42:58 bostic 5 4
c move fonts  to /usr/odl
e
s 00000/00001/00018
d D 5.4 90/06/08 14:39:25 bostic 4 3
c don't need bsd.own.mk
e
s 00007/00030/00012
d D 5.3 90/05/11 14:24:10 bostic 3 2
c first pass for new make
e
s 00027/00015/00015
d D 5.2 89/05/11 10:06:29 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00030/00000/00000
d D 5.1 87/12/12 17:37:39 bostic 1 0
c date and time created 87/12/12 17:37:39 by bostic
e
u
U
t
T
I 1
D 3
#
D 2
# Copyright (c) 1987 Regents of the University of California.
E 2
I 2
# Copyright (c) 1989 The Regents of the University of California.
E 2
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 2
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 2
I 2
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
#
E 3
#	%W% (Berkeley) %G%
D 3
#
SUBDIR=	nroff troff nroff_term troff_font
E 3
I 3

SUBDIR=	nroff troff nroff_term
E 3
I 2
FONTS=	fontlist ftB ftBC ftC ftCE ftCI ftCK ftCW ftFD ftG ftGI ftGM \
	ftGR ftH ftHI ftHM ftI ftI.bak ftL ftLI ftPA ftPB ftPI ftR \
	ftS ftSB ftSI ftSM ftTB ftTI ftTR ftTS ftUD ftap ftbb ftbi ftbk \
	ftbr ftcb ftch ftch.old ftci ftcl ftco ftcr ftct ftcy ftdb ftdi \
	ftdr ftfx ftgb ftgf ftgi ftgk ftgr fthb fthn ftm ftmb ftmi ftmn \
	ftmr ftnb ftni ftnr ftob ftoe ftoi ftor ftpb ftpp ftsb ftsc ftsg \
	ftsh ftsi ftsl ftsr fttB fttI fttR fttS fttb ftti fttr ftts ftwp \
	ftxx
E 2

D 3
all: FRC
D 2
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS}); done
E 2
I 2
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} all); done
E 2

D 2
install: FRC
E 2
I 2
clean cleandir depend lint tags: FRC
E 2
	for i in ${SUBDIR}; do \
D 2
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); \
	done
E 2
I 2
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done
E 2

D 2
clean: FRC
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} clean); done

depend: FRC
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} depend); done
E 2
I 2
install: FRC
	for i in ${SUBDIR}; do \
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done
	cd fonts; install -c -o bin -g bin -m 444 ${FONTS} \
E 3
I 3
beforeinstall:
	cd ${.CURDIR}/fonts; \
	    install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${FONTS} \
E 3
D 5
	    ${DESTDIR}/usr/libdata/troff_font
E 5
I 5
	    ${DESTDIR}/usr/old/libdata/troff_font
E 5
E 2

D 3
FRC:
E 3
I 3
.include <bsd.subdir.mk>
D 4
.include <bsd.own.mk>
E 4
E 3
E 1
