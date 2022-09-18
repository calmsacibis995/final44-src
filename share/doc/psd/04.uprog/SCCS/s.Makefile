h45463
s 00000/00003/00007
d D 8.2 94/05/23 14:36:01 mckusick 6 5
c syntax error
e
s 00000/00000/00010
d D 8.1 93/06/08 18:04:13 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 6.4 93/06/05 15:47:39 bostic 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00005/00021/00005
d D 6.3 90/06/30 15:03:56 bostic 3 2
c new doc makefiles
e
s 00001/00003/00025
d D 6.2 86/05/10 14:14:19 bloom 2 1
c final working copy
e
s 00028/00000/00000
d D 6.1 86/04/25 02:24:06 cuccia 1 0
c date and time created 86/04/25 02:24:06 by cuccia
e
u
U
t
T
I 1
D 3
#
# Copyright (c) 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 3
#	%W% (Berkeley) %G%
D 3
#
SRCS=	p0 p1 p2 p3 p4 p5 p6 p8 p9
MAC = p.mac
E 3
I 3

D 4
DIR=	ps2/03.uprog
E 4
I 4
DIR=	psd/04.uprog
E 4
SRCS=	p.mac p0 p1 p2 p3 p4 p5 p6 p8 p9
E 3
D 2
SEDFILES=cwscript
E 2
MACROS=	-ms
D 3
PRINTER=Pdp
D 2
SED = sed -f
E 2
TROFF=	ditroff -${PRINTER}
E 3

D 3
paper:	paper.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}

E 3
D 4
paper.${PRINTER}: ${SRCS}
E 4
I 4
D 6
paper.ps: ${SRCS}
E 4
D 2
	${SED} ${SEDFILES} ${SRCS} | ${TROFF} ${MACROS} ${MAC} -t > paper.${PRINTER}
E 2
I 2
D 3
	${TROFF} -t ${MACROS} ${MAC} ${SRCS} > paper.${PRINTER}
E 3
I 3
	${ROFF} ${MAC} ${SRCS} > ${.TARGET}
E 3
E 2

E 6
D 3
clean:
	rm -f paper.[PT]* *.spell errs Errs make.out

spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 3
I 3
.include <bsd.doc.mk>
E 3
E 1
