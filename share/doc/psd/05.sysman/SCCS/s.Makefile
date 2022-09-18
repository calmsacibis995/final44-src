h33997
s 00001/00000/00011
d D 8.2 94/06/01 18:52:59 ah 5 4
c cleanup toc
e
s 00000/00000/00011
d D 8.1 93/06/08 18:07:01 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00009
d D 6.3 93/06/05 15:49:07 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00020/00007
d D 6.2 90/06/30 15:02:41 bostic 2 1
c new doc makefiles
e
s 00027/00000/00000
d D 6.1 86/05/08 00:06:17 mckusick 1 0
c date and time created 86/05/08 00:06:17 by mckusick
e
u
U
t
T
I 1
D 2
#
# Copyright (c) 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 2
#	%W% (Berkeley) %G%
D 2
#
E 2
I 2

D 3
DIR=	ps1/06.sysman
E 3
I 3
DIR=	psd/05.sysman
E 3
E 2
SRCS=	0.t 1.0.t 1.1.t 1.2.t 1.3.t 1.4.t 1.5.t 1.6.t 1.7.t \
	2.0.t 2.1.t 2.2.t 2.3.t 2.4.t 2.5.t a.t
MACROS=	-ms
I 5
CLEANFILES+=toc
E 5
D 2
PRINTER=Pdp
TBL=	dtbl -${PRINTER}
TROFF=	ditroff -${PRINTER}
E 2

D 2
paper:	paper.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}

E 2
D 3
paper.${PRINTER}: ${SRCS}
E 3
I 3
paper.ps: ${SRCS}
E 3
D 2
	${TBL} ${SRCS} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 2
I 2
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
E 2

D 2
clean:
	rm -f paper.[PT]* *.spell errs Errs make.out

spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 2
I 2
.include <bsd.doc.mk>
E 2
E 1
