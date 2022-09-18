h47467
s 00006/00003/00013
d D 8.2 94/04/16 04:21:46 pendry 16 15
c better makedb rule
e
s 00000/00000/00016
d D 8.1 93/06/05 13:16:04 bostic 15 14
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00015
d D 5.13 92/07/21 14:59:22 bostic 14 13
c strip backsapces
e
s 00001/00001/00015
d D 5.12 92/07/18 15:52:20 bostic 13 12
c oops
e
s 00001/00001/00015
d D 5.11 92/07/18 15:48:30 bostic 12 11
c build the whatis file in /tmp
e
s 00000/00002/00016
d D 5.10 92/07/18 10:57:06 bostic 11 10
c move the copyright to etc
e
s 00002/00000/00016
d D 5.9 91/07/01 11:20:20 bostic 10 8
c install COPYRIGHT stuff
e
s 00003/00001/00015
d D 5.8.1.1 91/05/07 21:58:15 bostic 9 8
c branch for the 2nd network distribution
e
s 00001/00001/00015
d D 5.8 91/05/07 21:47:22 bostic 8 7
c add man1 to the list, get intro.1
e
s 00000/00001/00016
d D 5.7 90/06/08 14:36:48 bostic 7 6
c don't need bsd.own.m
e
s 00010/00036/00007
d D 5.6 90/05/11 13:55:59 bostic 6 5
c first pass for new make
e
s 00016/00015/00027
d D 5.5 90/05/10 16:13:35 bostic 5 4
c checkpoint for pmake
e
s 00007/00018/00035
d D 5.4 89/03/06 11:55:38 bostic 4 3
c move man pages into source tree, cleanup, no more manroff
e
s 00010/00005/00043
d D 5.3 88/07/09 11:25:13 bostic 3 2
c install approved copyright notice
e
s 00002/00002/00046
d D 5.2 88/02/22 08:52:07 bostic 2 1
c add man8/tahoe
e
s 00048/00000/00000
d D 5.1 87/12/12 18:29:20 bostic 1 0
c date and time created 87/12/12 18:29:20 by bostic
e
u
U
f b 
t
T
I 1
D 6
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 3
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 3
I 3
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
#
E 6
#	%W% (Berkeley) %G%
D 6
#
D 4
DIRS=	man1 man2 man3 man3f man4 man4/vax man4/tahoe man5 man6 \
D 2
	man7 man8 man8/vax
E 2
I 2
	man7 man8 man8/vax man8/tahoe
E 2
CDIRS=	cat1 cat2 cat3 cat3f cat4 cat4/vax cat4/tahoe cat5 cat6 \
D 2
	cat7 cat8 cat8/vax
E 2
I 2
	cat7 cat8 cat8/vax man8/tahoe
E 2
LCDIRS=	cat1 cat2 cat3 cat4 cat5 cat6 cat7 cat8
E 4
I 4
D 5
DIRS=	man1 man2 man3 man3f man4 man4/vax man4/tahoe man5 man7 man8 man8/vax
E 5
I 5
DIRS=	man3 man3f man4 man4/vax man4/tahoe man5 man7 man8 man8/vax
E 6
E 5
E 4

D 5
all: scriptinstall FRC
I 4
	install -c -o bin -g bin -m 444 makewhatis.sed \
		${DESTDIR}/usr/man/makewhatis.sed
E 4
	for i in ${DIRS}; do \
D 4
		(cd $$i; make ${MFLAGS}); \
E 4
I 4
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); \
E 5
I 5
D 6
all: FRC
	@-for i in ${DIRS}; do \
		(echo "==> $$i"; \
		    cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); \
E 5
E 4
	done
E 6
I 6
D 8
SUBDIR=	man3 man3f man4 man5 man7 man8
E 8
I 8
D 9
SUBDIR=	man1 man3 man3f man4 man5 man7 man8
I 16
SEDF= /usr/share/man/makewhatis.sed
E 16
E 9
I 9
# Missing: man3f

SUBDIR=	man1 man3 man4 man5 man7 man8
E 9
E 8
E 6

D 4
scriptinstall: FRC
	install -c -o bin -g bin -m 444 makewhatis.sed ${DESTDIR}/usr/man/makewhatis.sed
	install -c -o bin -g bin -m 755 manroff ${DESTDIR}/usr/man/manroff
E 4
D 5

E 5
D 6
install: FRC
D 5
	for i in ${DIRS}; do \
D 4
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); \
	done
E 4
I 4
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); done
E 4
	for file in `find /usr/man -type f -name '*.0' -print`; do \
		sed -n -f /usr/man/makewhatis.sed $$file; \
E 5
I 5
	install -c -o bin -g bin -m 444 makewhatis.sed \
		${DESTDIR}/usr/share/man/makewhatis.sed
	@-for i in ${DIRS}; do \
		(echo "==> $$i"; \
		    cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); done
E 6
I 6
afterinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 makewhatis.sed \
D 16
	    ${DESTDIR}/usr/share/man/makewhatis.sed
E 16
I 16
	    ${DESTDIR}${SEDF}
E 16
I 10
D 11
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 man0/COPYRIGHT \
	    ${DESTDIR}/usr/share/man/COPYRIGHT
E 11
E 10

makedb:
E 6
D 16
	for file in `find /usr/share/man -type f -name '*.0' -print`; do \
		sed -n -f /usr/share/man/makewhatis.sed $$file; \
E 16
I 16
	find /usr/share/man -type f -name '*.0' -print | \
	while read file; \
	do \
		sed -n -f ${SEDF} $$file; \
E 16
E 5
D 12
	done | sort -u > whatis.db
E 12
I 12
D 14
	done | sort -u > /tmp/whatis.db
E 14
I 14
	done | col -b | sort -u > /tmp/whatis.db
E 14
E 12
D 5
	install -o bin -g bin -m 444 whatis.db ${DESTDIR}/usr/man/whatis
	install -c -o bin -g bin -m 444 man.template ${DESTDIR}/usr/man/man.template
E 5
I 5
D 6
	install -o bin -g bin -m 444 whatis.db ${DESTDIR}/usr/share/man
E 6
I 6
D 13
	install -o ${BINOWN} -g ${BINGRP} -m 444 whatis.db \
E 13
I 13
	install -o ${BINOWN} -g ${BINGRP} -m 444 /tmp/whatis.db \
E 13
	    ${DESTDIR}/usr/share/man
E 6
E 5

D 4
manclean: FRC
E 4
I 4
D 6
clean cleandir depend lint tags:
E 4
D 5
	for i in ${DIRS}; do \
D 4
		(cd $$i; make ${MFLAGS} clean); \
	done
E 4
I 4
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done
E 5
I 5
	@-for i in ${DIRS}; do \
		(echo "==> $$i"; \
		    cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done
E 5
E 4

D 4
clean:
depend:
lint:
tags:
E 4
FRC:
E 6
I 6
D 7
.include <bsd.own.mk>
E 7
.include <bsd.subdir.mk>
E 6
E 1
