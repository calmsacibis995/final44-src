h38458
s 00000/00000/00007
d D 8.1 93/06/08 13:04:48 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00004/00006
d D 6.5 93/06/05 17:23:28 bostic 5 4
c new doc.mk; document numbering changes for 4.4BSD
e
s 00006/00031/00004
d D 6.4 90/06/30 15:10:04 bostic 4 3
c new doc makefiles
e
s 00015/00004/00020
d D 6.3 89/07/17 17:50:58 bostic 3 2
c AT&T free
e
s 00002/00002/00022
d D 6.2 86/04/16 16:46:50 eric 2 1
c oops....
e
s 00024/00000/00000
d D 6.1 86/04/16 16:29:13 eric 1 0
c date and time created 86/04/16 16:29:13 by eric
e
u
U
t
T
I 1
D 4
#
D 3
# Copyright (c) 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 3
I 3
# Copyright (c) 1986 The Regents of the University of California.
# All rights reserved.
E 3
#
I 3
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
#
E 4
E 3
#	%W% (Berkeley) %G%
D 4
#
E 4
I 4

D 5
DIR=	usd/22.memacros
E 5
I 5
DIR=	usd/19.memacros
E 5
E 4
SRCS=	intro.me
D 4
DEVICE=	dp
TROFF=	ditroff -P${DEVICE}
E 4
I 4
MACROS=	-me
E 4
D 5

D 2
paper:	intro.me
E 2
I 2
D 4
paper:	intro.${DEVICE}
E 2
	lpr -P${DEVICE} -n intro.${DEVICE}
E 4
I 4
paper.${PRINTER}: ${SRCS}
	${ROFF} ${SRCS} > ${.TARGET}
E 5
E 4

D 2
uchanges: ${SRCS}
E 2
I 2
D 4
intro.${DEVICE}: ${SRCS}
E 2
	${TROFF} -me -t ${SRCS} > intro.${DEVICE}

clean:
	rm -f intro.${DEVICE} *.spell errs Errs make.out

D 3
spell:	${SRCS}
E 3
I 3
spell: ${SRCS}
E 3
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 4
I 4
.include <bsd.doc.mk>
E 4
E 1
