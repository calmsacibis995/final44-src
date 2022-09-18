h19576
s 00001/00001/00034
d D 8.2 94/05/23 15:30:19 mckusick 16 15
c syntax fixes
e
s 00000/00000/00035
d D 8.1 93/08/14 10:29:51 mckusick 15 14
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00034
d D 6.8 93/07/29 15:39:40 elan 14 12
c Added ex1.gr.
e
s 00000/00000/00035
d R 8.1 93/06/08 18:32:43 bostic 13 12
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00034
d D 6.7 93/06/07 00:17:12 bostic 12 8
c new doc.mk; document numbering changes for 4.4BSD
e
s 00001/00001/00034
d R 8.3 93/06/05 16:11:10 bostic 11 10
c new doc.mk; document numbering changes for 4.4BSD
e
s 00002/00002/00033
d R 8.2 93/06/05 15:59:22 bostic 10 9
c new doc.mk; document numbering changes for 4.4BSD
e
s 00000/00000/00035
d R 8.1 93/06/04 16:40:38 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00033
d D 6.6 93/05/12 11:03:17 elan 8 7
c Added macros and c_macros.
e
s 00010/00012/00025
d D 6.5 93/01/14 17:10:41 elan 7 6
c fixed up the makefile.
e
s 00011/00060/00026
d D 6.4 90/06/30 15:03:24 bostic 6 5
c new doc makefiles
e
s 00014/00005/00072
d D 6.3 89/03/17 11:31:48 bostic 5 4
c add Berkeley specific copyright notices
e
s 00008/00006/00069
d D 6.2 86/04/28 17:36:40 mckusick 4 3
c generalize and make -Pdp the default
e
s 00015/00015/00060
d D 6.1 86/04/23 23:56:54 mckusick 3 2
c document distributed with 4.3BSD
e
s 00006/00005/00069
d D 5.1 86/04/23 23:54:57 mckusick 2 1
c document distributed with 4.2BSD
e
s 00074/00000/00000
d D 4.1 86/04/23 23:53:38 mckusick 1 0
c document distributed with 4.1BSD
e
u
U
t
T
I 1
D 6
#
D 5
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 5
I 5
# Copyright (c) 1980 The Regents of the University of California.
# All rights reserved.
E 5
#
D 5
#	%W% (Berkeley) %G%
E 5
I 5
# Redistribution and use in source and binary forms are permitted
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
E 5
#
E 6
D 5
#	makefile for screen package documentation
E 5
I 5
#	%W% (Berkeley) %G%
E 5
D 6
#
NROFF=	nroff
D 3
TROFF=	vtroff
E 3
I 3
TROFF=	ditroff
I 4
TBL=	dtbl -Pdp
E 4
E 3
D 2
#	VFONT=	vfontedpr
E 2
I 2
VFONT=	/usr/lib/vfontedpr
E 2
NFLAGS=	-Tcrt
D 3
TFLAGS=
E 3
I 3
TFLAGS= -Pdp
E 3
CFLAGS=	-O -n -s
D 3
BINDIR=	/usr/doc/curses
TARFILE=cf curdoc.tar
E 3
I 3
BINDIR=	/usr/doc/ps1/18.curses
E 6
E 3

D 6
DOCS=	doc.I doc.II doc.III doc.IV
D 3
RAW=	macros c_macros appen.B appen.A appen.C disclaim intro.0 intro.1 \
	intro.2 intro.3 intro.4 intro.5 ${DOCS} curses.3
E 3
I 3
RAW=	macros c_macros appen.B appen.A appen.C intro.0 intro.1 \
	intro.2 intro.3 intro.4 intro.5 ${DOCS} curses.3x
E 6
I 6
D 12
DIR=	ps1/18.curses
E 12
I 12
DIR=	psd/19.curses
E 12
D 7
SRCS=	Master macros appen.A appen.B appen.C intro.0 intro.1 \
	intro.2 intro.3 intro.4 intro.5
E 7
I 7
SRCS=	Master
E 7
MACROS=	-me
E 6
E 3

D 6
CRAW=	win_st.c twinkle1.c twinkle2.c life.c
CSOURCE=win_st.gr twinkle1.gr twinkle2.gr life.gr
D 3
SOURCE=	macros appen.A.tbl appen.B appen.C disclaim intro.0 intro.1 \
E 3
I 3
SOURCE=	macros appen.A.tbl appen.B appen.C intro.0 intro.1 \
E 3
	intro.2.tbl intro.3 intro.4 intro.5
E 6
I 6
D 7
CLEANFILES+=win_st.gr twinkle1.gr twinkle2.gr life.gr intro.2.tbl appen.A.tbl
E 7
I 7
CLEANFILES+=win_st.gr twinkle1.gr twinkle2.gr life.gr intro.2.tbl appen.A.tbl \
	ex1.gr ex2.gr
E 7
E 6

I 6
D 7
paper.${PRINTER}: ${SRCS}
	${ROFF} ${SRCS} > ${.TARGET}

E 7
E 6
D 2
.SUFFIXES:
.SUFFIXES: .c .gr
E 2
I 2
D 3
#.SUFFIXES:
#.SUFFIXES: .c .gr
E 3
I 3
.SUFFIXES:
.SUFFIXES: .c .gr
E 3
E 2

#
# this section formats C input source into nice troffable (or nroffable)
# versions.  It uses the capabilites of "vgrind", which sets keywords in
# bold font, and comments in italics.
#

D 4
Curses.doc: ${VFONT} Master macros ${SOURCE}
	${NROFF} -me ${NFLAGS} Master > Curses.doc

E 4
D 2
.c.gr:
	${VFONT} $*.c > $*.gr
E 2
I 2
# Don't re-run vgrind unless you want to patch the output files.
I 6
VFONT=	/usr/libexec/vfontedpr
E 6
D 3
#.c.gr:
#	${VFONT} $*.c > $*.gr
E 3
I 3
.c.gr:
	${VFONT} $*.c | grep -v "^'wh" > $*.gr
E 3
E 2

D 3
${CSOURCE}: ${VFONT}
E 3
D 6
troff: Master macros ${SOURCE}
	${TROFF} -me ${TFLAGS} Master ;

I 4
Curses.doc: ${VFONT} Master macros ${SOURCE}
	${NROFF} -me ${NFLAGS} Master > Curses.doc

E 4
I 3
${CSOURCE}: ${VFONT}

E 3
intro.5: ${DOCS}
E 6
I 6
D 7
intro.5: doc.I doc.II doc.III doc.IV
E 6
appen.B: win_st.gr
appen.C: twinkle1.gr life.gr twinkle2.gr
E 7
I 7
paper.ps: ${SRCS}
D 16
	${ROFF} ${SRCS} > ${.TARGET}
E 16
I 16
	soelim ${SRCS} | ${ROFF} > ${.TARGET}
E 16
E 7

I 7
D 8
Master: twinkle1.gr twinkle2.gr life.gr ex1.gr ex2.gr
Master: fns.doc intro.5 intro.2.tbl intro.0 intro.1 intro.3 intro.4 intro.6
E 8
I 8
D 14
Master: twinkle1.gr ex2.gr fns.doc intro.5 intro.2.tbl intro.0 intro.1 \
E 14
I 14
Master: twinkle1.gr ex1.gr ex2.gr fns.doc intro.5 intro.2.tbl intro.0 intro.1 \
E 14
	intro.3 intro.4 intro.6 macros c_macros
E 8

E 7
intro.2.tbl: intro.2
D 4
	tbl intro.2 > intro.2.tbl
E 4
I 4
	${TBL} intro.2 > intro.2.tbl
E 4

D 7
appen.A.tbl: appen.A
D 4
	tbl appen.A > appen.A.tbl
E 4
I 4
	${TBL} appen.A > appen.A.tbl
E 4

E 7
D 6
vfontedpr: vfontedpr.c
	${CC} ${CFLAGS} -o vfontedpr vfontedpr.c

spell: ${SOURCE}
	/bin/csh ./Spellit ${SOURCE} ${DOCS}

install:
	cp Makefile ${RAW} ${BINDIR}

D 3
tar:
	tar rv${TARFILE} Master ${RAW} ${CRAW} Makefile vfontedpr.c
E 3
I 3
ar:
	ar crv curdoc.ar Master ${RAW} ${CRAW} Makefile
E 3

lpr: Curses
	-lpr Curses ; lpq
	-lpq

clean:
D 3
	rm -f ${CSOURCE} appen.A.tbl intro.2.tbl curses.tar vfontedpr
E 3
I 3
D 4
	rm -f ${CSOURCE} appen.A.tbl intro.2.tbl curses.tar vfontedpr Curses.doc
E 4
I 4
	rm -f ${CSOURCE} appen.A.tbl intro.2.tbl curses.tar vfontedpr \
		Curses.doc errs Errs
E 6
I 6
.include <bsd.doc.mk>
I 7


E 7
E 6
E 4
E 3
E 1
