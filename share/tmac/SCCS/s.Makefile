h46955
s 00000/00000/00024
d D 8.1 93/06/08 11:23:13 bostic 19 18
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00002/00021
d D 6.15 92/07/14 14:47:56 cael 18 17
c minor fixes (still have blank line booboo somewheres)
e
s 00001/00001/00022
d D 6.14 91/08/18 00:01:24 cael 17 15
c remove tmac.mdoc.old
e
s 00003/00001/00022
d D 6.13.1.1 91/05/07 22:02:10 bostic 16 15
c branch for the 2nd network distribution
e
s 00000/00001/00023
d D 6.13 91/03/20 11:40:47 bostic 15 14
c don't do an sccs get on a file
e
s 00008/00005/00016
d D 6.12 91/03/14 13:50:49 cael 14 12
c check out files before trying to use them...
e
s 00006/00005/00016
d R 6.12 91/03/07 18:14:41 cael 13 12
c fix stupid mistake
e
s 00004/00000/00017
d D 6.11 91/03/07 16:46:34 cael 12 11
c added sed.strip for doc files
e
s 00002/00001/00015
d D 6.10 91/03/07 15:20:27 cael 11 10
c new version of -mdoc
e
s 00001/00002/00015
d D 6.9 90/06/29 22:01:36 bostic 10 9
c make links work right
e
s 00003/00001/00014
d D 6.8 90/06/29 21:23:15 karels 9 8
c rename tmac.an to .old, link tmac.andoc to tmac.an
e
s 00003/00002/00012
d D 6.7 90/06/11 04:08:10 cael 8 7
c added tmac.andoc
e
s 00004/00001/00010
d D 6.6 90/06/02 19:02:05 karels 7 6
c remove old stuff, rename tmac.an.new to tmac.an, add tmac.r
e
s 00006/00006/00005
d D 6.5 90/05/11 13:51:24 bostic 6 5
c first pass for new make
e
s 00004/00014/00007
d D 6.4 89/05/10 22:44:06 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00011/00009/00010
d D 6.3 87/06/21 14:51:23 bostic 4 2
c new template
e
s 00011/00010/00009
d R 6.3 87/06/21 14:48:59 bostic 3 2
c new template
e
s 00001/00001/00018
d D 6.2 85/05/28 18:37:30 mckusick 2 1
c syntax
e
s 00019/00000/00000
d D 6.1 85/05/28 15:08:53 mckusick 1 0
c man macros distributed with 4.3BSD beta
e
u
U
f b 
t
T
I 1
D 5
#
D 4
# Copyright (c) 1985 Regents of the University of California.
E 4
I 4
# Copyright (c) 1987 Regents of the University of California.
E 4
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
D 4
#	%W% (Berkeley) %G%
E 4
I 4
#	%W%	(Berkeley)	%G%
E 4
#
E 5
D 4
#
#  Makefile for -man macros
#

E 4
I 4
D 6
CFLAGS=	-O
LIBC=	/lib/libc.a
E 4
SRCS=	tmac.an tmac.an.new tmac.an6n tmac.an6t
E 6
I 6
#	%W% (Berkeley) %G%
E 6

I 6
D 7
FILES=	tmac.an tmac.an.new tmac.an6n tmac.an6t
E 7
I 7
D 8
FILES=	tmac.an tmac.r
E 8
I 8
D 9
FILES=	tmac.an tmac.r tmac.doc tmac.andoc
E 9
I 9
D 11
FILES=	tmac.an.old tmac.r tmac.doc tmac.andoc
E 11
I 11
D 14
FILES=	tmac.an.old tmac.r tmac.doc tmac.andoc tmac.doc.old tmac.doc-ditroff \
	tmac.doc-nroff tmac.doc-common tmac.doc-syms
I 12
MSRCS=  doc-parse doc-ditroff doc-common doc-nroff doc-syms
E 14
I 14
D 16
D 17
FILES=	tmac.an.old tmac.r tmac.andoc tmac.doc.old
E 17
I 17
D 18
FILES=	tmac.an.old tmac.r tmac.andoc
E 18
I 18
FILES=	tmac.r tmac.andoc tmac.s tmac.e
E 18
E 17
E 16
I 16
# Missing: tmac.a tmac.an.old tmac.cp tmac.r

FILES=	tmac.andoc tmac.doc.old
E 16
MSRCS=  doc doc-ditroff doc-common doc-nroff doc-syms
I 18

E 18
E 14
E 12
E 11
LINKS=	${BINDIR}/tmac/tmac.andoc ${BINDIR}/tmac/tmac.an
E 9
NOOBJ=	noobj
E 8

# old macros not currently installed...
D 18
OFILES=	tmac.an.v6compat tmac.an6n tmac.an6t tmac.a tmac.cp
E 18
I 18
# OFILES=	tmac.a tmac.cp
E 18
E 7

E 6
D 4
all:	${SRCS}
E 4
I 4
D 5
all:
E 5
I 5
all clean cleandir depend lint tags:
E 5
E 4

D 4
install:${SRCS}
D 2
	for i in ${SRCS} do (install -c $$i ${DESTDIR}/usr/lib/tmac/$$i); done
E 2
I 2
	for i in ${SRCS}; do (install -c $$i ${DESTDIR}/usr/lib/tmac/$$i); done
E 4
I 4
D 5
install: FRC
E 5
I 5
D 10
install:
E 10
I 10
beforeinstall:
I 12
	for i in ${MSRCS}; do \
D 14
		sed -f strip.sed < $$i > tmac.$$i; \
E 14
I 14
D 15
		sccs get $$i; \
E 15
		sed -f strip.sed < $$i > ${DESTDIR}${BINDIR}/tmac/tmac.$$i; \
		chown ${BINOWN}.${BINGRP} ${DESTDIR}${BINDIR}/tmac/tmac.$$i; \
		chmod 444 ${DESTDIR}${BINDIR}/tmac/tmac.$$i; \
E 14
	done
E 12
E 10
E 5
D 6
	for i in ${SRCS}; do \
D 5
		(install -c -o bin -g bin -m 644 $$i ${DESTDIR}/usr/lib/tmac/$$i); \
	done
E 5
I 5
		(install -c -o bin -g bin -m 644 $$i \
		    ${DESTDIR}/usr/share/tmac/$$i); done
E 6
I 6
	install -c -o ${BINOWN} -g ${BINOWN} -m 444 ${FILES} \
D 14
	    ${DESTDIR}${BINDIR}/tmac
E 14
I 14
		${DESTDIR}${BINDIR}/tmac

E 14
I 9
D 10
	ln ${LINKS}
E 10
E 9
E 6
E 5
E 4
E 2

I 6
D 8
.include <bsd.own.mk>
E 8
I 8
.include <bsd.prog.mk>
E 8
E 6
D 5
clean:
I 4
depend:
FRC:
E 5
E 4
E 1
