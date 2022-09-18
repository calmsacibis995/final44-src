h62137
s 00001/00001/00011
d D 1.6 93/06/08 17:49:50 bostic 6 5
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00031/00008
d D 1.5 90/06/30 15:01:19 bostic 5 4
c new doc makefiles
e
s 00016/00004/00023
d D 1.4 89/02/23 23:07:37 bostic 4 3
c Berkeley copyright
e
s 00001/00001/00026
d D 1.3 89/02/20 17:00:16 mckusick 3 2
c revise location of refer
e
s 00003/00002/00024
d D 1.2 89/02/19 15:58:24 mckusick 2 1
c use refer from book
e
s 00026/00000/00000
d D 1.1 89/02/18 18:54:36 mckusick 1 0
c date and time created 89/02/18 18:54:36 by mckusick
e
u
U
t
T
I 1
D 5
#
D 4
# Copyright (c) 1989 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
E 4
#
I 4
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
E 5
E 4
#	%W% (Berkeley) %G%
D 5
#
E 5
I 4

I 5
DIR=	papers/relengr
E 5
E 4
SRCS=	0.t 1.t 2.t 3.t
MACROS=	-ms
D 5
PRINTER=Plz
TROFF=	ditroff -${PRINTER}
E 5
I 5
EXTRA=	ref.bib tmac.srefs
E 5
D 2
REFER=	refer -m -n -e -l -s -p ref.bib
E 2
I 2
D 3
REFER=	../../book/ref/refer -m -n -e -l -s -p ref.bib
E 3
I 3
REFER=	/a/staff/mckusick/book/ref/refer -m -n -e -l -s -p ref.bib
E 3
E 2

D 6
paper.${PRINTER}: ${SRCS}
E 6
I 6
paper.ps: ${SRCS}
E 6
D 2
	${REFER} ${SRCS} | ${TROFF} ${MACROS} -t | psdit >paper.${PRINTER}
E 2
I 2
D 5
	${REFER} ${SRCS} | ${TROFF} ${MACROS} -t tmac.srefs - | \
		psdit >paper.${PRINTER}
E 5
I 5
	${REFER} ${SRCS} | ${ROFF} > ${.TARGET}
E 5
E 2

D 5
print: paper.${PRINTER}
	lpr -${PRINTER} paper.${PRINTER}

clean:
	rm -f *.spell errs Errs make.out paper.${PRINTER}

D 4
spell:	${SRCS}
E 4
I 4
spell: ${SRCS}
E 4
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 5
I 5
.include <bsd.doc.mk>
E 5
E 1
