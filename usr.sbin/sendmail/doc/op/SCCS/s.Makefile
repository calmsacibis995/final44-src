h45998
s 00001/00000/00012
d D 8.2 94/02/28 10:17:04 eric 8 7
c remove target before building in case it isn't owned by us
e
s 00001/00001/00011
d D 8.1 93/06/08 17:24:16 bostic 7 5
c document numbering changes for 4.4BSD
e
s 00000/00000/00012
d R 8.1 93/06/08 14:11:09 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00011
d D 5.5 93/06/05 17:05:57 eric 5 4
c make op.ps, not op.${PRINTER}
e
s 00001/00001/00011
d D 5.4 93/06/05 16:45:22 bostic 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00003/00001/00009
d D 5.3 93/06/01 21:05:13 eric 3 2
c new doc scheme
e
s 00006/00037/00004
d D 5.2 90/06/30 15:05:18 bostic 2 1
c new doc makefiles
e
s 00041/00000/00000
d D 5.1 89/01/23 09:48:17 bostic 1 0
c date and time created 89/01/23 09:48:17 by bostic
e
u
U
t
T
I 1
D 2
#
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
#
E 2
#	%W% (Berkeley) %G%
D 2
#
#
PRINTER=-Pdp
TROFF=	ditroff ${PRINTER}
EQN=	deqn ${PRINTER}
TBL=	dtbl ${PRINTER}
PIC=	pic ${PRINTER}
LPR=	lpr -n ${PRINTER}
E 2

D 2
SRC=	op.me
E 2
I 2
D 7
DIR=	smm/07.sendmailop
E 7
I 7
DIR=	smm/08.sendmailop
E 7
SRCS=	op.me
MACROS=	-me
E 2

D 2
op: op.out
	${LPR} op.out
E 2
I 2
D 3
paper.${PRINTER}: ${SRCS}
E 3
I 3
D 5
all: op.${PRINTER}
E 5
I 5
all: op.ps
E 5

D 4
op.${PRINTER}: ${SRCS}
E 4
I 4
op.ps: ${SRCS}
I 8
	rm -f ${.TARGET}
E 8
E 4
E 3
	${PIC} ${SRCS} | ${EQN} | ${ROFF} > ${.TARGET}
E 2

D 2
op.out: ${SRC}
	${PIC} ${SRC} | ${EQN} | ${TROFF} -t -me > op.out

clean:
	rm -f op.out op.me.spell errs Errs

spell:	${SRC}
	@for i in ${SRC}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 2
I 2
.include <bsd.doc.mk>
E 2
E 1
