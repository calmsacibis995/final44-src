h18769
s 00001/00003/00009
d D 1.4 93/06/08 17:49:09 bostic 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00005/00027/00007
d D 1.3 90/06/30 15:01:09 bostic 3 2
c new doc makefiles
e
s 00014/00003/00020
d D 1.2 89/03/10 09:44:12 bostic 2 1
c add Berkeley specific copyright notice
e
s 00023/00000/00000
d D 1.1 86/08/11 11:51:32 mckusick 1 0
c first draft
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

DIR=	papers/newvm
E 3
SRCS=	0.t 1.t a.t
MACROS=	-ms
D 3
PRINTER=Plz
E 3
D 4
TBL=	dtbl -${PRINTER}
TROFF=	ptroff -${PRINTER}
E 4

D 3
paper: ${SRCS}
	${TBL} ${SRCS} | ${TROFF} ${MACROS}
E 3
I 3
D 4
paper.${PRINTER}: ${SRCS}
E 4
I 4
paper.ps: ${SRCS}
E 4
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
