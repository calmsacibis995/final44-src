h59182
s 00001/00001/00024
d D 8.2 94/03/27 12:11:37 bostic 19 18
c move me macros somewhere else besides this file
e
s 00000/00000/00025
d D 8.1 93/06/05 14:05:50 bostic 18 17
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00024
d D 6.15 92/07/23 14:09:59 bostic 17 16
c needed TMLIB
e
s 00009/00012/00015
d D 6.14 92/07/21 18:15:43 bostic 16 15
c update for 4.4Alpha
e
s 00010/00010/00017
d D 6.13 92/07/14 21:51:48 cael 15 14
c minor adjustments for groff -me
e
s 00002/00000/00025
d D 6.12 91/10/07 20:58:26 cael 14 13
c merge in to /usr/old/lib tree
e
s 00000/00004/00025
d D 6.11 90/07/01 10:32:59 bostic 13 12
c don't need these targets
e
s 00005/00006/00024
d D 6.10 90/06/08 14:38:56 bostic 12 11
c don't need obj, use bsd.prog.mk
e
s 00014/00029/00016
d D 6.9 90/05/11 13:57:04 bostic 11 10
c first pass for new make
e
s 00005/00009/00040
d D 6.8 89/05/10 22:43:37 bostic 10 9
c file reorg, pathnames.h, paths.h
e
s 00011/00006/00038
d D 6.7 88/09/30 10:21:44 bostic 9 8
c update copyright notice
e
s 00003/00000/00041
d D 6.6 88/09/30 10:02:45 bostic 8 7
c add extra labels
e
s 00001/00001/00040
d D 6.5 88/05/19 16:48:22 karels 7 6
c add letterhead.me
e
s 00027/00022/00014
d D 6.4 88/04/22 12:16:19 bostic 6 5
c minor cleanups
e
s 00004/00005/00032
d D 6.3 87/10/03 14:46:08 bostic 5 4
c clean up directory creation
e
s 00013/00021/00024
d D 6.2 87/06/21 14:51:35 bostic 4 3
c new template
e
s 00029/00007/00016
d D 6.1 86/05/21 21:46:19 mckusick 3 2
c update from Jim McKie
e
s 00001/00001/00022
d D 1.2 86/05/15 04:19:44 lepreau 2 1
c DESTDIR; ensure mode 644
e
s 00023/00000/00000
d D 1.1 85/04/29 19:02:09 eric 1 0
c date and time created 85/04/29 19:02:09 by eric
e
u
U
f i 
t
T
I 1
D 11
#
I 3
D 4
# Copyright (c) 1980 Regents of the University of California.
E 4
I 4
D 9
# Copyright (c) 1987 Regents of the University of California.
E 9
I 9
# Copyright (c) 1987 The Regents of the University of California.
E 9
E 4
D 6
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 6
I 6
# All rights reserved.
E 6
#
D 4
#	%W% (Berkeley) %G%
E 4
I 4
D 6
#	%W%	(Berkeley)	%G%
E 6
I 6
# Redistribution and use in source and binary forms are permitted
D 9
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 9
E 6
E 4
#
E 11
E 3
D 4
#  Makefile for -me macros
#
#	This makefile strips comments from the source files and
#	installs them in the expected directories.
#
D 3
#	%W%	%Y%	%E%
#
E 3
I 3
DESTDIR=
LIB =	/usr/lib/me
E 4
I 4
D 6
CFLAGS=	-O
LIBC=	/lib/libc.a
LIB=	/usr/lib/me
SRCS=	tmac.e acm.me chars.me deltext.me eqn.me float.me footnote.me \
E 6
I 6
#	%W% (Berkeley) %G%
D 11
#
D 10
MELIB=	/usr/lib/me
TMLIB=	/usr/lib/tmac
E 10
I 10
MELIB=	/usr/share/me
TMLIB=	/usr/share/tmac
E 11
I 11

MELIB=	${BINDIR}/me
I 17
TMLIB=	${BINDIR}/tmac
E 17
D 15
TMLIB=	${BINDIR}/tmac
E 15
I 15
D 16
# TMLIB=	${BINDIR}/tmac
E 16
E 15
E 11
E 10
MESRCS=	acm.me chars.me deltext.me eqn.me float.me footnote.me \
E 6
D 7
	index.me local.me null.me refer.me sh.me tbl.me thesis.me
E 7
I 7
D 10
	index.me letterhead.me local.me null.me refer.me sh.me tbl.me thesis.me
E 10
I 10
	index.me letterhead.me local.me null.me refer.me sh.me \
	tbl.me thesis.me
E 10
E 7
I 6
D 15
TMSRCS=	tmac.e
I 11
MAN7=	me.0
E 15
I 15
D 16
# TMSRCS=	tmac.e
# MAN7=	me.0
E 16
I 16
D 19
TMSRCS=	tmac.e
E 19
I 19
TMSRCS=	tmac.orig_me
E 19
MAN7=	me.0
E 16
E 15
E 11
E 6
E 4
E 3

D 3
SRCS=	tmac.e acm.me chars.me deltext.me eqn.me \
E 3
I 3
D 4
SRCS =	tmac.e acm.me chars.me deltext.me eqn.me \
E 3
	float.me footnote.me index.me local.me null.me \
	refer.me sh.me tbl.me thesis.me
D 3
GET=	sccs get
E 3
I 3
GET =	sccs get
E 4
I 4
D 11
all:
E 11
I 11
D 13
all: ${MAN7}
E 11
E 4
E 3

D 4
all: revisions $(SRCS)

D 3
install: revisions $(SRCS) install.csh
D 2
	csh install.csh $(SRCS)
E 2
I 2
	DEST=$(DESTDIR) csh install.csh $(SRCS)
E 3
I 3
install: revisions $(SRCS)
E 4
I 4
D 11
install: FRC
E 4
D 5
	-if [ ! -d ${DESTDIR}${LIB} ]; then \
		rm -f ${DESTDIR}${LIB}; \
		mkdir ${DESTDIR}${LIB}; \
	fi
E 5
I 5
D 6
	-[ -d ${DESTDIR}${LIB} ] || mkdir ${DESTDIR}${LIB}
	chown bin.bin ${DESTDIR}${LIB}
	chmod 755 ${DESTDIR}${LIB}
E 5
	-for i in ${SRCS}; do \
		sed -e '/%beginstrip%/{' \
		    -e 'h' \
		    -e 's/.*/.\\" This version has had comments stripped; an unstripped version is available./p' \
		    -e 'g' \
		    -e '}' \
		    -e '/%beginstrip%/,$$s/[. 	][ 	]*\\".*//' \
		    -e '/^$$/d' \
		    -e '/\\n@/d' $$i > _mac_tmp_; \
D 4
		install -m 0444 _mac_tmp_ ${DESTDIR}${LIB}/$$i; \
E 4
I 4
D 5
		install -o bin -g bin -m 644 _mac_tmp_ ${DESTDIR}${LIB}/$$i; \
E 5
I 5
		install -o bin -g bin -m 444 _mac_tmp_ ${DESTDIR}${LIB}/$$i; \
E 6
I 6
	-[ -d ${DESTDIR}${MELIB} ] || mkdir ${DESTDIR}${MELIB}
	-[ -d ${DESTDIR}${TMLIB} ] || mkdir ${DESTDIR}${TMLIB}
	chown bin.bin ${DESTDIR}${MELIB} ${DESTDIR}${TMLIB}
	chmod 755 ${DESTDIR}${MELIB} ${DESTDIR}${TMLIB}
E 11
I 11
clean cleandir depend lint tags:

E 13
D 12
install: maninstall
E 11
	for i in ${MESRCS}; do \
E 12
I 12
beforeinstall:
	cd ${.CURDIR}; for i in ${MESRCS}; do \
E 12
		sed -f strip.sed < $$i > ${DESTDIR}${MELIB}/$$i; \
D 11
		chown bin.bin ${DESTDIR}${MELIB}/$$i; \
E 11
I 11
		chown ${BINOWN}.${BINGRP} ${DESTDIR}${MELIB}/$$i; \
E 11
		chmod 444 ${DESTDIR}${MELIB}/$$i; \
E 6
E 5
E 4
	done
D 6
	mv ${DESTDIR}${LIB}/tmac.e ${DESTDIR}/usr/lib/tmac/tmac.e
D 4
	install -c -m 0444 revisions ${DESTDIR}${LIB}/revisions
E 4
I 4
	install -c -o bin -g bin -m 444 revisions ${DESTDIR}${LIB}/revisions
E 6
I 6
D 12
	for i in ${TMSRCS}; do \
E 12
I 12
D 15
	cd ${.CURDIR}; for i in ${TMSRCS}; do \
E 12
		sed -f strip.sed < $$i > ${DESTDIR}${TMLIB}/$$i; \
D 11
		chown bin.bin ${DESTDIR}${TMLIB}/$$i; \
E 11
I 11
		chown ${BINOWN}.${BINGRP} ${DESTDIR}${TMLIB}/$$i; \
E 11
		chmod 444 ${DESTDIR}${TMLIB}/$$i; \
	done
D 11
	install -c -o bin -g bin -m 444 revisions ${DESTDIR}${MELIB}/revisions
E 11
I 11
D 12
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 revisions \
E 12
I 12
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m 444 revisions \
E 12
	    ${DESTDIR}${MELIB}/revisions
E 15
I 15
D 16
# 	cd ${.CURDIR}; for i in ${TMSRCS}; do \
#  		sed -f strip.sed < $$i > ${DESTDIR}${TMLIB}/$$i; \
# 		chown ${BINOWN}.${BINGRP} ${DESTDIR}${TMLIB}/$$i; \
# 		chmod 444 ${DESTDIR}${TMLIB}/$$i; \
# 	done
# 	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m 444 revisions \
# 	    ${DESTDIR}${MELIB}/revisions
E 15
E 11
E 6
E 4
E 3
E 2

I 14
BINDIR= /usr/old/lib
E 16
I 16
	cd ${.CURDIR}; for i in ${TMSRCS}; do \
		sed -f strip.sed < $$i > ${DESTDIR}${TMLIB}/$$i; \
		chown ${BINOWN}.${BINGRP} ${DESTDIR}${TMLIB}/$$i; \
		chmod 444 ${DESTDIR}${TMLIB}/$$i; \
	done
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m 444 revisions \
	    ${DESTDIR}${MELIB}/revisions
E 16

E 14
D 10
clean:
I 8
cleandir:
E 8
D 4

D 3
revisions install.csh $(SRCS):
E 3
I 3
revisions $(SRCS):
E 3
	$(GET) SCCS/s.$@
E 4
I 4
depend:
I 8
lint:
tags:
E 8
FRC:
E 10
I 10
D 11
clean cleandir depend lint tags FRC:
E 11
I 11
D 12
.include <bsd.own.mk>
.include <bsd.man.mk>
E 12
I 12
.include <bsd.prog.mk>
E 12
E 11
E 10
E 4
E 1
