h38966
s 00000/00000/00010
d D 8.1 93/06/08 14:07:39 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 6.4 93/06/05 16:44:29 bostic 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00032/00006
d D 6.3 90/06/30 15:05:14 bostic 3 2
c new doc makefiles
e
s 00014/00003/00024
d D 6.2 89/03/07 14:33:17 bostic 2 1
c add Berkeley specific copyright, networking release
e
s 00027/00000/00000
d D 6.1 86/04/17 16:36:06 mckusick 1 0
c date and time created 86/04/17 16:36:06 by mckusick
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
DIR=	smm/06.lpd
E 4
I 4
DIR=	smm/07.lpd
E 4
E 3
SRCS=	0.t 1.t 2.t 3.t 4.t 5.t 6.t 7.t
MACROS=	-ms
D 3
PRINTER=Pdp
EQN=	deqn -${PRINTER}
TBL=	dtbl -${PRINTER}
TROFF=	ditroff -${PRINTER}
E 3

D 3
paper:	paper.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}

E 3
D 4
paper.${PRINTER}: ${SRCS}
E 4
I 4
paper.ps: ${SRCS}
E 4
D 3
	${TBL} ${SRCS} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 3
I 3
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
E 3

D 3
clean:
	rm -f paper.${PRINTER} *.spell errs Errs make.out

spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 3
I 3
.include <bsd.doc.mk>
E 3
E 1
