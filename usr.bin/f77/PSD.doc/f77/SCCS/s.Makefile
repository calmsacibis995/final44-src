h25808
s 00000/00000/00010
d D 8.1 93/06/08 18:10:59 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 5.3 93/06/05 15:52:29 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00021/00006
d D 5.2 90/06/30 15:02:24 bostic 2 1
c new doc makefiles
e
s 00027/00000/00000
d D 5.1 86/04/21 18:29:55 mckusick 1 0
c date and time created 86/04/21 18:29:55 by mckusick
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
DIR=	ps1/02.f77
E 3
I 3
DIR=	psd/08.f77
E 3
E 2
SRCS=	f77.ms
MACROS=	-msU
D 2
PRINTER=Pdp
EQN=	deqn -${PRINTER}
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
	${TBL} ${SRCS} | ${EQN} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 2
I 2
	${TBL} ${SRCS} | ${EQN} | ${ROFF} > ${.TARGET}
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
