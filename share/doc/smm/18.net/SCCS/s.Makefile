h53399
s 00000/00000/00010
d D 8.1 93/06/10 17:52:48 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 6.5 93/06/10 17:52:41 bostic 6 4
c move 13.net to 18.net
e
s 00000/00000/00010
d R 8.1 93/06/08 16:53:02 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 6.4 93/06/05 16:48:07 bostic 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00032/00006
d D 6.3 90/06/30 15:05:58 bostic 3 2
c new doc makefiles
e
s 00015/00003/00023
d D 6.2 89/03/07 10:53:20 bostic 2 1
c install Berkeley specific copyright, for networking release
e
s 00026/00000/00000
d D 6.1 86/05/26 13:30:12 mckusick 1 0
c date and time created 86/05/26 13:30:12 by mckusick
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
E 2
#
I 2
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
E 3
E 2
#	%W% (Berkeley) %G%
I 2
D 3
#
E 2
#
E 3
I 3

D 4
DIR=	smm/15.net
E 4
I 4
D 6
DIR=	smm/13.net
E 6
I 6
DIR=	smm/18.net
E 6
E 4
E 3
SRCS=	0.t 1.t 2.t 3.t 4.t 5.t 6.t 7.t 8.t 9.t a.t b.t c.t d.t e.t f.t
MACROS=	-ms
D 3
PRINTER=Pdp
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
