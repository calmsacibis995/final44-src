h32353
s 00000/00000/00010
d D 8.1 93/06/08 14:00:36 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 6.4 93/06/05 16:40:27 bostic 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00020/00006
d D 6.3 90/06/30 15:04:51 bostic 3 2
c new doc makefiles
e
s 00001/00001/00025
d D 6.2 86/06/03 18:05:40 karels 2 1
c 4.3 version
e
s 00026/00000/00000
d D 6.1 86/05/25 17:37:32 mckusick 1 0
c date and time created 86/05/25 17:37:32 by mckusick
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
E 3
I 3

DIR=	smm/02.config
E 3
D 2
SRCS=	0.t 1.t 2.t 3.t 4.t 5.t 6.t a.t b.t c.t d.t
E 2
I 2
SRCS=	0.t 1.t 2.t 3.t 4.t 5.t 6.t a.t b.t c.t d.t e.t
E 2
MACROS=	-ms
D 3
PRINTER=Pdp
TBL=	dtbl -${PRINTER}
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
paper.ps: ${SRCS}
E 4
D 3
	${TBL} ${SRCS} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 3
I 3
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
E 3

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
