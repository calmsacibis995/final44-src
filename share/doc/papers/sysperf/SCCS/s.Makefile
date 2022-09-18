h10304
s 00001/00001/00021
d D 1.6 93/06/08 17:50:12 bostic 6 5
c new doc.mk; document numbering changes for 4.4BSD
e
s 00001/00000/00021
d D 1.5 92/10/04 23:29:12 mckusick 5 4
c need macros
e
s 00013/00025/00008
d D 1.4 90/06/30 15:01:29 bostic 4 3
c new doc makefiles
e
s 00002/00002/00031
d D 1.3 89/05/01 17:13:57 mckusick 3 2
c update for new command locations
e
s 00001/00001/00032
d D 1.2 85/11/30 12:08:06 mckusick 2 1
c use dp instead of ip by default
e
s 00033/00000/00000
d D 1.1 85/07/27 19:43:14 mckusick 1 0
c date and time created 85/07/27 19:43:14 by mckusick
e
u
U
t
T
I 1
D 4
#
# Copyright (c) 1985 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 4
#	%W% (Berkeley) %G%
D 4
#
D 2
PRINTER=-Pip
E 2
I 2
D 3
PRINTER=-Pdp
E 3
I 3
PRINTER=-Plz
E 3
E 2
TYPE=	-n
E 4
I 4

DIR=	papers/sysperf
I 5
MACROS= -ms
E 5
E 4
SRCS=	0.t 1.t 2.t 3.t 4.t 5.t 6.t 7.t
D 4
OBJS=	perf.t appendix.t
TBL=	dtbl
EQN=	deqn
TROFF=	ditroff
D 3
GRIND=	igrind
E 3
I 3
GRIND=	vgrind
E 4
I 4
EXTRA=	a1.t a2.t
OBJS=	paper.tmp appendix.tmp
CLEANFILES+=${OBJS}
E 4
E 3

D 4
paper:	perf
	lpr ${PRINTER} ${TYPE} perf
E 4
I 4
D 6
paper.${PRINTER}: ${OBJS}
E 6
I 6
paper.ps: ${OBJS}
E 6
	${ROFF} ${OBJS} > ${.TARGET}
E 4

D 4
perf:	${OBJS}
	${TROFF} -ms -t ${PRINTER} ${OBJS} > perf
E 4
I 4
paper.tmp: ${SRCS}
	${TBL} ${SRCS} | ${EQN} > paper.tmp
E 4

D 4
perf.t:	${SRCS}
	${TBL} ${PRINTER} ${SRCS} | ${EQN} ${PRINTER} > perf.t

appendix.t: a1.t a2.t
E 4
I 4
appendix.tmp: a1.t a2.t
E 4
	${GRIND} -f a1.t |  awk '/\.\(\)/{ cnt = 2 } \
D 4
	   { if (cnt) cnt -= 1; else print $$0; } ' > appendix.t
E 4
I 4
	   { if (cnt) cnt -= 1; else print $$0; } ' > appendix.tmp
E 4
	${GRIND} -f -lcsh a2.t |  awk '/\.\(\)/{ cnt = 2 } \
D 4
	   { if (cnt) cnt -= 1; else print $$0; } ' >> appendix.t
E 4
I 4
	   { if (cnt) cnt -= 1; else print $$0; } ' >> appendix.tmp
E 4

D 4
clean:
	rm -f perf ${OBJS}
E 4
I 4
.include <bsd.doc.mk>
E 4
E 1
