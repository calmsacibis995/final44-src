h07601
s 00004/00019/00007
d D 6.2 90/06/30 15:02:52 bostic 2 1
c new doc makefiles
e
s 00026/00000/00000
d D 6.1 86/05/07 23:43:05 mckusick 1 0
c date and time created 86/05/07 23:43:05 by mckusick
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

DIR=	ps1/09.lint
E 2
SRCS=	lint.ms
MACROS=	-msU
D 2
PRINTER=Pdp
E 2
REFER=	refer -e -p /usr/doc/run/Ind
D 2
TROFF=	ditroff -${PRINTER}
E 2

D 2
paper:	paper.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}

E 2
paper.${PRINTER}: ${SRCS}
D 2
	${REFER} ${SRCS} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 2
I 2
	${REFER} ${SRCS} | ${ROFF} > ${.TARGET}
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
