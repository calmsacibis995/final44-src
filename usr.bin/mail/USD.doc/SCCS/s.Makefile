h40654
s 00000/00000/00011
d D 8.1 93/06/08 13:41:19 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00010
d D 6.4 93/06/08 13:41:15 bostic 5 3
c Mail -> mail
e
s 00000/00000/00011
d R 8.1 93/06/08 12:41:51 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00010
d D 6.3 93/06/05 17:17:53 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00021/00007
d D 6.2 90/06/30 15:07:59 bostic 2 1
c new doc makefiles
e
s 00028/00000/00000
d D 6.1 86/05/23 12:06:30 kjd 1 0
c date and time created 86/05/23 12:06:30 by kjd
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

D 5
DIR=	usd/07.Mail
E 5
I 5
DIR=	usd/07.mail
E 5
E 2
SRCS=	mail0.nr mail1.nr mail2.nr mail3.nr mail4.nr mail5.nr mail6.nr \
	mail7.nr mail8.nr mail9.nr maila.nr
D 2

E 2
MACROS=	-me
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
