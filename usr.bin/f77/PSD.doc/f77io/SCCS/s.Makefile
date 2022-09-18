h27087
s 00001/00004/00006
d D 8.2 94/05/23 15:24:07 mckusick 5 4
c fix syntax errors
e
s 00000/00000/00010
d D 8.1 93/06/08 18:11:33 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 5.3 93/06/05 15:52:45 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00019/00006
d D 5.2 90/06/30 15:02:28 bostic 2 1
c new doc makefiles
e
s 00025/00000/00000
d D 5.1 86/04/21 18:34:13 mckusick 1 0
c date and time created 86/04/21 18:34:13 by mckusick
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
DIR=	ps1/03.f77io
E 3
I 3
DIR=	psd/09.f77io
E 3
E 2
SRCS=	f77IO.ms
D 5
MACROS=	-msU
D 2
PRINTER=Pdp
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
	${TROFF} ${MACROS} -t ${SRCS} > paper.${PRINTER}
E 2
I 2
	${ROFF} ${SRCS} > ${.TARGET}
E 5
I 5
MACROS=	-ms
E 5
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
