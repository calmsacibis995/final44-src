h07140
s 00000/00000/00010
d D 8.1 93/06/08 14:05:42 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 5.6 93/06/05 16:42:15 bostic 6 5
c new doc.mk; document numbering changes for 4.4BSD
e
s 00002/00002/00008
d D 5.5 93/06/05 13:14:05 bostic 5 4
c make it work for 4.4BSD
e
s 00004/00033/00006
d D 5.4 90/06/30 15:05:51 bostic 4 3
c new doc makefiles
e
s 00014/00003/00025
d D 5.3 89/03/07 10:56:59 bostic 3 2
c add Berkeley specific copyright notice
e
s 00016/00010/00012
d D 5.2 86/05/20 16:36:40 kjd 2 1
c fixes for typesetting
e
s 00022/00000/00000
d D 5.1 86/05/14 16:52:39 kjd 1 0
c date and time created 86/05/14 16:52:39 by kjd
e
u
U
t
T
I 1
D 4
#
D 2
# Copyright (c) 1980 Regents of the University of California.
E 2
I 2
D 3
# Copyright (c) 1986 Regents of the University of California.
E 2
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 3
I 3
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
E 3
#
E 4
#	%W% (Berkeley) %G%
D 4
#
E 4
I 4

D 6
DIR=	smm/14.fastfs
E 6
I 6
DIR=	smm/05.fastfs
E 6
E 4
D 2
SRCS=	input.me
MACROS=	-me
E 2
I 2
SRCS=	0.t 1.t 2.t 3.t 4.t 5.t 6.t
MACROS=	-ms
E 2
D 4
PRINTER=Pdp
I 2
EQN=	deqn -${PRINTER}
TBL=	dtbl -${PRINTER}
TROFF=	ditroff -${PRINTER}
E 4
E 2

I 2
D 4
paper:	paper.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}
E 2

E 4
I 2
D 5
paper.${PRINTER}: ${SRCS}
D 4
	${TBL} ${SRCS} | ${EQN} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 4
I 4
	${TBL} ${SRCS} | ${EQN} | ${TROFF} > ${.TARGET}
E 5
I 5
paper.ps: ${SRCS}
	${TBL} ${SRCS} | ${EQN} | ${ROFF} > ${.TARGET}
E 5
E 4
E 2

I 2
D 4
clean:
	rm -f paper.[PT]* *.spell errs Errs make.out
E 2

D 2
SRCS=	0.t 1.t 2.t 3.t 4.t 5.t 6.t
TROFF=	itroff
E 2
I 2
spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 2

E 4
I 4
.include <bsd.doc.mk>
E 4
D 2
fs:	${SRCS}
	eqn ${SRCS} | tbl | ${TROFF} -ms -t > fs

paper:	fs
	lpr -Pimagen -t fs
E 2
E 1
