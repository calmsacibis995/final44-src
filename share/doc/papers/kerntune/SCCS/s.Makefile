h44552
s 00001/00008/00009
d D 1.5 93/06/08 17:48:04 bostic 5 4
c new doc.mk; document numbering changes for 4.4BSD
e
s 00007/00000/00010
d D 1.4 90/11/08 20:38:50 mckusick 4 3
c update copyright notice
e
s 00006/00016/00004
d D 1.3 90/06/30 15:00:54 bostic 3 2
c new doc makefiles
e
s 00008/00006/00012
d D 1.2 87/08/05 17:05:14 mckusick 2 1
c use pic for figure 2
e
s 00018/00000/00000
d D 1.1 84/05/21 18:02:44 mckusick 1 0
c date and time created 84/05/21 18:02:44 by mckusick
e
u
U
t
T
I 4
D 5
#
# Copyright (c) 1984 The Regents of the University of California.
# All rights reserved.
#
# %sccs.include.redist.sh
#
E 5
E 4
I 1
D 3
#
# Copyright (c) 1984 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 3
#	%W% (Berkeley) %G%
I 4
D 5
#
E 5
E 4
D 3
#
E 3
I 3

DIR=	papers/kerntune
E 3
SRCS=	0.t 1.t 2.t 3.t 4.t
D 2
TBL=	tbl
EQN=	eqn
TROFF=	itroff
TYPE=	-t
E 2
I 2
D 3
PIC=	pic ${PRINTER}
TBL=	dtbl ${PRINTER}
EQN=	deqn ${PRINTER}
TROFF=	ditroff ${PRINTER}
PRINTER=-Plz
TYPE=	-n
E 3
I 3
MACROS=	-ms
E 3
E 2

D 3
paper:	perf
D 2
	lpr -Pimagen ${TYPE} perf
E 2
I 2
	lpr ${PRINTER} ${TYPE} perf
E 3
I 3
D 5
paper.${PRINTER}: ${SRCS}
E 5
I 5
paper.ps: ${SRCS}
E 5
	${SOELIM} ${SRCS} | ${PIC} | ${TBL} | ${EQN} | ${ROFF} > ${.TARGET}
E 3
E 2

D 3
perf:	${SRCS} Makefile
D 2
	${TBL} ${SRCS} | ${EQN} | ${TROFF} -ms -t > perf
E 2
I 2
	soelim ${SRCS} | ${PIC} | ${TBL} | ${EQN} | ${TROFF} -ms -t > perf
E 3
I 3
.include <bsd.doc.mk>
E 3
E 2
E 1
