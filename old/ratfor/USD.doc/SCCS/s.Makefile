h03254
s 00004/00019/00006
d D 6.2 93/06/05 09:45:13 bostic 2 1
c checkpoint
e
s 00025/00000/00000
d D 6.1 86/04/29 21:35:15 cuccia 1 0
c date and time created 86/04/29 21:35:15 by cuccia
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

DIR=	ps2/08.ratfor
E 2
SRCS=	m.mac m0 m1 m2 m3 m4 m5 m9 m99
MACROS=	-msU
D 2
PRINTER=Pdp
TROFF=	ditroff -${PRINTER}
E 2

D 2
paper:	paper.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}

E 2
paper.${PRINTER}: ${SRCS}
D 2
	${TROFF} ${MACROS} -t ${SRCS} > paper.${PRINTER}
E 2
I 2
	${ROFF} ${SRCS} > ${.TARGET}
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
