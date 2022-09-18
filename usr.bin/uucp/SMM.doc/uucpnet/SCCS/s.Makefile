h32479
s 00000/00000/00011
d D 8.1 93/06/08 16:54:35 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00009
d D 6.3 93/06/05 16:48:47 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00020/00007
d D 6.2 90/06/30 15:06:22 bostic 2 1
c new doc makefiles
e
s 00027/00000/00000
d D 6.1 86/05/14 12:09:01 kjd 1 0
c date and time created 86/05/14 12:09:01 by kjd
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
DIR=	smm/21.uucpnet
E 3
I 3
DIR=	smm/15.uucpnet
E 3
E 2
SRCS=	network.ms
MACROS=	-ms
D 2
PRINTER=Pdp
E 2
D 3
REFER=	refer -p /usr/doc/run/Ind
E 3
I 3
REFER=	refer -p /usr/old/dict/papers/Ind
E 3
D 2
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
	${REFER} -e ${SRCS} | ${TBL} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 2
I 2
	${REFER} -e ${SRCS} | ${TBL} | ${ROFF} > ${.TARGET}
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
