h50244
s 00000/00000/00018
d D 8.1 93/06/08 12:48:55 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00016
d D 6.3 93/06/05 17:20:05 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00005/00021/00013
d D 6.2 90/06/30 15:09:20 bostic 2 1
c new doc makefiles
e
s 00034/00000/00000
d D 6.1 86/05/27 20:21:38 mckusick 1 0
c date and time created 86/05/27 20:21:38 by mckusick
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
DIR=	usd/14.edit
E 3
I 3
DIR=	usd/11.edit
E 3
E 2
SRCS=	edittut.ms
MACROS=	-msU
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
# index for versatec is different from the one in edit.tut
# because the fonts are different and entries reference page
# rather than section numbers.  if you have a typesetter
# you should just use the index in edit.tut, and ignore editvindex.

editvindex:
	${TROFF} ${MACROS} -n22 edit.vindex
I 2

.include <bsd.doc.mk>
E 2
E 1
