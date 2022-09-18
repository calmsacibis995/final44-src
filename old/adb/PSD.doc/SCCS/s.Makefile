h19738
s 00000/00000/00010
d D 8.1 93/06/08 18:12:27 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 6.3 93/06/05 15:53:18 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00005/00023/00005
d D 6.2 90/06/30 15:02:55 bostic 2 1
c new doc makefiles
e
s 00028/00000/00000
d D 6.1 86/05/07 23:54:48 mckusick 1 0
c document released with 4.3BSD
e
u
U
t
T
I 1
D 2
#
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 2
#	%W% (Berkeley) %G%
D 2
#
PRINTER=-Pdp
TROFF=	ditroff ${PRINTER}
EQN=	deqn ${PRINTER}
TBL=	dtbl ${PRINTER}
LPR=	lpr -n ${PRINTER}
E 2

I 2
D 3
DIR=	ps1/10.adb
E 3
I 3
DIR=	psd/11.adb
E 3
E 2
SRCS=	adb.ms
I 2
MACROS=	-ms
E 2

D 2
paper:	adb.n
	${LPR} adb.n
E 2
I 2
D 3
paper.${PRINTER}: ${SRCS}
E 3
I 3
paper.ps: ${SRCS}
E 3
	${EQN} ${SRCS} | ${TBL} | ${ROFF} > ${.TARGET}
E 2

D 2
adb.n:	${SRCS}
	${EQN} ${SRCS} | ${TBL} | ${TROFF} -t -ms >adb.n

clean:
	rm -f adb.n

spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 2
I 2
.include <bsd.doc.mk>
E 2
E 1
