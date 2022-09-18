h38280
s 00000/00000/00010
d D 8.1 93/06/08 13:42:35 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 6.4 93/06/08 13:42:32 bostic 5 3
c document numbering changes for 4.4BSD
e
s 00000/00000/00010
d R 8.1 93/06/08 13:28:30 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00031/00006
d D 6.3 90/06/30 15:11:08 bostic 3 2
c new doc makefiles
e
s 00014/00003/00023
d D 6.2 89/02/10 13:36:18 bostic 2 1
c freely redistributable according to Ken Arnold
e
s 00026/00000/00000
d D 6.1 86/04/27 23:01:02 mckusick 1 0
c date and time created 86/04/27 23:01:02 by mckusick
e
u
U
t
T
I 1
D 3
#
D 2
# Copyright (c) 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 2
I 2
# Copyright (c) 1986 The Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
#
E 3
#	%W% (Berkeley) %G%
D 3
#
E 3
I 3

D 5
DIR=	usd/33.rogue
E 5
I 5
DIR=	usd/30.rogue
E 5
E 3
SRCS=	rogue.me
MACROS=	-me
D 3
PRINTER=Pdp
TBL=	dtbl -${PRINTER}
TROFF=	ditroff -${PRINTER}
E 3

D 3
paper:	paper.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}

E 3
paper.${PRINTER}: ${SRCS}
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
