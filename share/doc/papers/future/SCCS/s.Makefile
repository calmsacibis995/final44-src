h07879
s 00002/00001/00008
d D 1.3 93/06/08 17:46:44 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00005/00018/00004
d D 1.2 90/06/30 15:00:31 bostic 2 1
c new doc makefiles
e
s 00022/00000/00000
d D 1.1 86/11/25 23:22:39 mckusick 1 0
c date and time created 86/11/25 23:22:39 by mckusick
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

DIR=	papers/future
E 2
SRCS=	0.t 1.t 2.t r.t
MACROS=	-ms
D 2
PRINTER=Plz
TROFF=	ptroff -${PRINTER}
E 2

D 2
paper: ${SRCS}
	${TROFF} ${MACROS} ${SRCS}

clean:
	rm -f paper.[PT]* *.spell errs Errs make.out

spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 2
I 2
D 3
paper.${PRINTER}: ${SRCS}
E 3
I 3
paper.ps: ${SRCS}
E 3
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
I 3

E 3
.include <bsd.doc.mk>
E 2
E 1
