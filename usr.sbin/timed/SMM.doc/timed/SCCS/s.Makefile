h42221
s 00001/00002/00009
d D 8.2 94/05/11 10:19:06 mckusick 6 5
c wrong target
e
s 00000/00000/00010
d D 8.1 93/06/08 16:03:23 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 6.4 93/06/05 16:47:43 bostic 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00032/00006
d D 6.3 90/06/30 15:06:26 bostic 3 2
c new doc makefiles
e
s 00014/00003/00024
d D 6.2 89/03/07 14:26:34 bostic 2 1
c Berkeley specific copyright notcie
e
s 00027/00000/00000
d D 6.1 86/05/23 18:29:58 mckusick 1 0
c first draft for distribution in 4.3BSD
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
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
#
E 3
#	%W% (Berkeley) %G%
D 3
#
E 3
I 3

D 4
DIR=	smm/22.timed
E 4
I 4
DIR=	smm/12.timed
E 4
E 3
SRCS=	timed.ms
MACROS=	-ms
D 6
PRINTER=Pdp
E 6
D 3
SOELIM=	soelim
TBL=	dtbl -${PRINTER}
TROFF=	ditroff -${PRINTER}
E 3

D 3
paper:	paper.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}

E 3
D 6
paper.${PRINTER}: ${SRCS}
E 6
I 6
paper.ps: ${SRCS}
E 6
D 3
	${SOELIM} ${SRCS} | ${TBL} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 3
I 3
	${SOELIM} ${SRCS} | ${TBL} | ${ROFF} > ${.TARGET}
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
