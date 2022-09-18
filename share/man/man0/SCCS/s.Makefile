h61840
s 00002/00001/00068
d D 8.3 94/05/04 16:04:54 mckusick 9 8
c need to add eqn for title.urm
e
s 00006/00024/00063
d D 8.2 94/01/29 15:00:56 mckusick 8 7
c title.urm, intro.ms, preface.ms, toc.in, and ptx.in merged into title.urm
e
s 00000/00000/00087
d D 8.1 93/07/05 11:51:07 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00041/00003/00046
d D 6.5 93/07/05 11:50:53 mckusick 6 4
c put in rules for printing man pages
e
s 00000/00000/00049
d R 8.1 93/06/29 06:24:14 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00048
d D 6.4 93/06/28 17:12:18 mckusick 4 3
c have to specify scripts in current directory
e
s 00025/00023/00024
d D 6.3 93/06/18 14:54:53 mckusick 3 2
c update for 4.4BSD
e
s 00011/00007/00036
d D 6.2 86/05/15 09:11:30 mckusick 2 1
c add title page (with toc) for PRM
e
s 00043/00000/00000
d D 6.1 86/05/10 23:56:55 mckusick 1 0
c date and time created 86/05/10 23:56:55 by mckusick
e
u
U
t
T
I 1
#
D 3
# Copyright (c) 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 3
I 3
# Copyright (c) 1986, 1993 Regents of the University of California.
# All rights reserved.
E 3
#
#	%W% (Berkeley) %G%
#
D 3
TOCS=	toc1 toc2 toc3 toc3f toc4 toc5 toc6 toc7 toc8 \
	tocx1 tocx2 tocx3 tocx3f tocx4 tocx5 tocx6 tocx7 tocx8
MACROS=	-msU
PRINTER=Pdp
TROFF=	ditroff -${PRINTER}
E 3
I 3
SRCS=	man1 man2 man3 man4 man5 man6 man7 man8
E 3

I 3
MACROS=	-ms
PRINTER=Pps
I 9
EQN=	eqn
E 9
TBL=	tbl
TROFF=	groff

E 3
D 2
all: title.${PRINTER} preface.${PRINTER} intro.${PRINTER} \
     toc.${PRINTER} ptx.${PRINTER}
	lpr -${PRINTER} -n title.${PRINTER}
E 2
I 2
D 8
all: title.urm.${PRINTER} preface.${PRINTER} intro.${PRINTER} \
     toc.${PRINTER} ptx.${PRINTER} title.prm.${PRINTER}
E 8
I 8
all: title.urm.${PRINTER} title.prm.${PRINTER}
E 8
D 3
	lpr -${PRINTER} -n title.urm.${PRINTER}
E 2
	lpr -${PRINTER} -n preface.${PRINTER}
	lpr -${PRINTER} -n intro.${PRINTER}
	lpr -${PRINTER} -n toc.${PRINTER}
	lpr -${PRINTER} -n ptx.${PRINTER}
I 2
	lpr -${PRINTER} -n title.prm.${PRINTER}
E 3
E 2

I 3
D 8
print: title.urm.${PRINTER} preface.${PRINTER} intro.${PRINTER} \
     toc.${PRINTER} ptx.${PRINTER} title.prm.${PRINTER}
E 8
I 8
print: title.urm.${PRINTER} title.prm.${PRINTER}
E 8
	lpr -${PRINTER} title.urm.${PRINTER}
D 8
	lpr -${PRINTER} preface.${PRINTER}
	lpr -${PRINTER} intro.${PRINTER}
	lpr -${PRINTER} toc.${PRINTER}
	lpr -${PRINTER} ptx.${PRINTER}
E 8
	lpr -${PRINTER} title.prm.${PRINTER}

E 3
D 2
title.${PRINTER}: title.urm
	${TROFF} -t title.urm >title.${PRINTER}
E 2
I 2
D 8
title.urm.${PRINTER}: title.urm
D 3
	${TROFF} -t title.urm >title.urm.${PRINTER}
E 3
I 3
	${TROFF} title.urm >title.urm.${PRINTER}
E 8
I 8
title.urm.${PRINTER}: title.urm ptxx
D 9
	${TBL} title.urm | ${TROFF} ${MACROS} >title.urm.${PRINTER}
E 9
I 9
	${EQN} title.urm | ${TBL} | ${TROFF} ${MACROS} >title.urm.${PRINTER}
E 9
E 8
E 3
E 2

D 8
preface.${PRINTER}: preface.ms
D 3
	${TROFF} ${MACROS} -t preface.ms >preface.${PRINTER}
E 3
I 3
	${TBL} preface.ms | ${TROFF} ${MACROS} >preface.${PRINTER}
E 3

intro.${PRINTER}: intro.ms
D 3
	${TROFF} ${MACROS} -t intro.ms >intro.${PRINTER}
E 3
I 3
	${TROFF} ${MACROS} intro.ms >intro.${PRINTER}
E 3

D 6
toc.${PRINTER}: toc.in ptxx
E 6
I 6
toc.${PRINTER}: ${SRCS} toc.in ptxx
E 6
D 3
	${TROFF} -t toc.in >toc.${PRINTER}
E 3
I 3
	${TROFF} toc.in >toc.${PRINTER}
E 3

D 6
ptx.${PRINTER}: ptx.in ptxx
E 6
I 6
ptx.${PRINTER}: ${SRCS} ptx.in ptxx
E 6
D 3
	${TROFF} -t ptx.in >ptx.${PRINTER}
E 3
I 3
	${TROFF} ptx.in >ptx.${PRINTER}
E 3

E 8
I 2
D 6
title.prm.${PRINTER}: title.prm ptxx
E 6
I 6
title.prm.${PRINTER}: ${SRCS} title.prm ptxx
E 6
D 3
	${TROFF} -t title.prm >title.prm.${PRINTER}
E 3
I 3
	${TROFF} title.prm >title.prm.${PRINTER}
E 3

E 2
ptxx:
D 3
	tocrc all
	tocrc t
E 3
I 3
D 4
	tocrc
E 4
I 4
	./tocrc
I 6

man1pages: man1
	rm -f man1.out
	for i in `cat man1`; do \
		sed -f groff.sed $$i | groff -man >>man1pages; \
	done;

man2pages: man2
	rm -f man2.out
	for i in `cat man2`; do groff -man $$i >>man2pages; done;

man3pages: man3
	rm -f man3.out
	for i in `cat man3`; do groff -man $$i >>man3pages; done;

man4pages: man4
	rm -f man4.out
	for i in `cat man4`; do groff -man $$i >>man4pages; done;

man5pages: man5
	rm -f man5.out
	for i in `cat man5`; do \
		sed -f groff.sed $$i | groff -man >>man5pages; \
	done;

man6pages: man6
	rm -f man6.out
	for i in `cat man6`; do groff -man $$i >>man6pages; done;

man7pages: man7
	rm -f man7.out
	for i in `cat man7`; do \
		sed -f groff.sed $$i | groff -man >>man7pages; \
	done;

man8pages: man8
	rm -f man8.out
	for i in `cat man8`; do groff -man $$i >>man8pages; done;
E 6
E 4
E 3

clean:
D 2
	rm -f title.[PT]* preface.[PT]* intro.[PT]* toc.[PT]* ptx.[PT]* \
	${TOCS} ptxx *.spell errs Errs make.out
E 2
I 2
D 8
	rm -f title.urm.[PT]* preface.[PT]* intro.[PT]* toc.[PT]* ptx.[PT]* \
D 3
	title.prm.[PT]* ${TOCS} ptxx *.spell errs Errs make.out
E 3
I 3
	title.prm.[PT]* toc? tocx? ptxx *.spell errs Errs make.out
E 8
I 8
	rm -f title.urm.[PT]* title.prm.[PT]* toc? tocx? ptxx \
		*.spell errs Errs make.out
E 8
E 3
E 2
E 1
