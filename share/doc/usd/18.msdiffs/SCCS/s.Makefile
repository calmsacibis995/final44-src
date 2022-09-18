h19334
s 00000/00000/00007
d D 8.1 93/06/08 13:04:05 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00004/00006
d D 6.3 93/06/05 17:23:16 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00019/00006
d D 6.2 90/06/30 15:09:59 bostic 2 1
c new doc makefiles
e
s 00025/00000/00000
d D 6.1 86/06/02 15:52:05 mckusick 1 0
c date and time created 86/06/02 15:52:05 by mckusick
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
DIR=	usd/21.msdiffs
E 3
I 3
DIR=	usd/18.msdiffs
E 3
E 2
SRCS=	ms.diffs
MACROS=	-msU
D 2
PRINTER=Pdp
TROFF=	ditroff -${PRINTER}
E 2
D 3

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
E 3
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
