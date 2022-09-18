h42524
s 00001/00002/00021
d D 1.8 93/06/08 17:48:47 bostic 8 7
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00004/00019
d D 1.7 91/12/10 16:52:20 mckusick 7 6
c cleanups for new refer
e
s 00002/00001/00021
d D 1.6 90/12/16 17:23:14 mckusick 6 5
c make it work
e
s 00008/00034/00014
d D 1.5 90/06/30 15:01:04 bostic 5 4
c new doc makefiles
e
s 00005/00003/00043
d D 1.4 90/05/12 11:17:55 mckusick 4 3
c add rule to make troff input
e
s 00002/00002/00044
d D 1.3 90/04/16 22:29:24 mckusick 3 2
c get it right!
e
s 00006/00003/00040
d D 1.2 90/04/13 17:07:17 mckusick 2 1
c add ref.bib dependencies
e
s 00043/00000/00000
d D 1.1 90/04/13 16:55:34 mckusick 1 0
c date and time created 90/04/13 16:55:34 by mckusick
e
u
U
t
T
I 1
D 5
#
# Copyright (c) 1989 The Regents of the University of California.
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
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
E 5
#	%W% (Berkeley) %G%
D 5
#
E 5

I 5
DIR=	papers/memfs
E 5
D 2
SRCS=	0.t 1.t A.gt
E 2
I 2
D 3
SRCS=	0.t 1.t A.t
E 3
I 3
SRCS=	0.t 1.t
E 3
E 2
MACROS=	-ms
D 5
PRINTER=Plz
TROFF=	ditroff -${PRINTER}
E 5
D 7
REFER=	/a/staff/mckusick/book/ref/refer -m -n -e -l -s -p ref.bib
E 7
I 7
REFER=	refer -n -e -l -s -p ref.bib
E 7
D 5
GRIND=	vgrind -f
E 5
I 5
EXTRA=	ref.bib A.t tmac.srefs
D 7
CLEANFILES=ref.bib.i? A.gt paper.t
E 7
I 7
CLEANFILES=ref.bib.i A.gt paper.t
E 7
I 6
D 8
PRINTER=ps
E 8
E 6
E 5

D 2
paper.${PRINTER}: ${SRCS}
E 2
I 2
D 4
paper.${PRINTER}: ${SRCS} ref.bib.ia A.gt
E 2
D 3
	${REFER} ${SRCS} | ${TROFF} ${MACROS} -t tmac.srefs - | \
E 3
I 3
	${REFER} ${SRCS} A.gt | ${TROFF} ${MACROS} -t tmac.srefs - | \
E 3
		psdit >paper.${PRINTER}
E 4
I 4
D 8
paper.${PRINTER}: paper.t
E 8
I 8
paper.ps: paper.t
E 8
D 5
	${TROFF} ${MACROS} -t tmac.srefs paper.t | psdit >paper.${PRINTER}
E 5
I 5
D 6
	${ROFF} ${SRCS} tmac.srefs paper.t > ${.TARGET}
E 6
I 6
	${ROFF} tmac.srefs paper.t > ${.TARGET}
E 6
E 5

D 7
paper.t: ${SRCS} ref.bib.ia A.gt
E 7
I 7
paper.t: ${SRCS} ref.bib.i A.gt
E 7
D 5
	${REFER} ${SRCS} A.gt > paper.t
E 5
I 5
	${REFER} ${SRCS} A.gt > ${.TARGET}
E 5
E 4

I 2
D 7
ref.bib.ia: ref.bib
E 7
I 7
ref.bib.i: ref.bib
E 7
D 5
	indxbib ref.bib
E 5
I 5
	${INDXBIB} ref.bib
E 5

E 2
A.gt: A.t
D 5
	${GRIND} <A.t >A.gt
E 5
I 5
	${GRIND} < A.t > A.gt
E 5

D 5
print: paper.${PRINTER}
	lpr -${PRINTER} paper.${PRINTER}

clean:
D 2
	rm -f *.spell errs Errs make.out paper.${PRINTER}
E 2
I 2
	rm -f A.gt *.spell errs Errs make.out paper.${PRINTER} ref.bib.i?
E 2

spell: ${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 5
I 5
.include <bsd.doc.mk>
E 5
E 1
