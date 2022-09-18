h46446
s 00000/00000/00011
d D 8.1 93/08/14 10:22:00 mckusick 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00010
d D 6.4 93/08/02 12:18:13 elan 5 3
c Fixed refer(1) pathname problem.
e
s 00000/00000/00011
d R 8.1 93/06/08 18:23:56 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00009
d D 6.3 93/06/05 15:55:01 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00019/00007
d D 6.2 90/06/30 15:03:14 bostic 2 1
c new doc makefiles
e
s 00026/00000/00000
d D 6.1 86/05/08 00:26:49 mckusick 1 0
c date and time created 86/05/08 00:26:49 by mckusick
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
DIR=	ps1/15.yacc
E 3
I 3
DIR=	psd/15.yacc
E 3
E 2
SRCS=	ss.. ss0 ss1 ss2 ss3 ss4 ss5 ss6 ss7 ss8 ss9 ssA ssB ssa ssb ssc ssd
MACROS=	-msU
D 2
PRINTER=Pdp
E 2
D 5
REFER=	refer -e -p /usr/doc/run/Ind
E 5
I 5
REFER=	refer -e -p /usr/old/dict/papers/Ind
E 5
D 2
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
	${REFER} ${SRCS} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 2
I 2
	${REFER} ${SRCS} | ${ROFF} > ${.TARGET}
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
