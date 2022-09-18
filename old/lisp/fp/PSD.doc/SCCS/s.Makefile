h28890
s 00006/00024/00005
d D 6.2 90/06/30 15:04:16 bostic 2 1
c new doc makefiles
e
s 00029/00000/00000
d D 6.1 86/04/29 12:18:40 cuccia 1 0
c date and time created 86/04/29 12:18:40 by cuccia
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
SRCS = 	manDefs.rno manCh0.rno manCh1.rno\
	manCh2.rno manCh3.rno manCh4.rno manCh5.rno\
	manCh6.rno manCh7.rno refs.rno manApp.rno
PRINTER=Pdp
TBL=dtbl -${PRINTER}
EQN=deqn -${PRINTER}
TROFF=	ditroff -${PRINTER}
E 2
I 2

DIR=	ps2/07.fp
SRCS = 	manDefs.rno manCh0.rno manCh1.rno manCh2.rno manCh3.rno manCh4.rno \
	manCh5.rno manCh6.rno manCh7.rno refs.rno manApp.rno
E 2
MACROS= -me

D 2
paper:	paper.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}

E 2
paper.${PRINTER}: ${SRCS}
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
