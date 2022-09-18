h14329
s 00001/00001/00016
d D 8.4 94/05/23 14:24:45 mckusick 11 10
c fix up source list
e
s 00002/00002/00015
d D 8.3 94/05/17 16:28:44 mckusick 10 9
c update for 4.4BSD manuals
e
s 00002/00002/00015
d D 8.2 94/04/22 08:51:41 bostic 9 8
c move vi tutorial to 11.vitut; install all the sources
e
s 00000/00000/00017
d D 8.1 93/08/14 10:54:03 mckusick 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00016
d D 6.6 93/08/10 11:49:53 elan 7 5
c typo in file name.
e
s 00000/00000/00017
d R 8.1 93/06/08 12:49:18 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00016
d D 6.5 93/06/05 17:25:16 bostic 5 4
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00004/00013
d D 6.4 93/06/05 17:20:57 bostic 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00008/00036/00009
d D 6.3 90/06/30 15:09:28 bostic 3 2
c new doc makefiles
e
s 00014/00003/00031
d D 6.2 89/11/30 12:28:16 bostic 2 1
c add Berkeley specific copyright notice
e
s 00034/00000/00000
d D 6.1 86/05/30 11:19:12 mckusick 1 0
c date and time created 86/05/30 11:19:12 by mckusick
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
DIR=	usd/15.vi
E 4
I 4
D 9
DIR=	usd/12.vi
E 4
E 3
SRCS=	vi.in vi.chars
E 9
I 9
DIR=	usd/11.vitut
D 11
SRCS=	vi.in vi.chars vi.summary vi.apwh.ms
E 11
I 11
SRCS=	vi.in vi.chars
E 11
E 9
D 10
MACROS=	-msU
E 10
I 10
MACROS=	-ms
E 10
D 3
PRINTER=Pdp
TBL=	dtbl -${PRINTER}
TROFF=	ditroff -${PRINTER}
E 3
I 3
CLEANFILES+=summary.* viapwh.*
E 3

D 3
paper:	paper.${PRINTER} summary.${PRINTER} viapwh.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}
	lpr -${PRINTER} -n summary.${PRINTER}
	lpr -${PRINTER} -n viapwh.${PRINTER}
E 3
I 3
D 4
paper.${PRINTER}: ${SRCS} summary.${PRINTER} viapwh.${PRINTER}
E 4
I 4
D 5
paper.ps: ${SRCS} summary.${PRINTER} viapwh.${PRINTER}
E 5
I 5
paper.ps: ${SRCS} summary.ps viapwh.ps
E 5
E 4
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
E 3

D 3
paper.${PRINTER}: ${SRCS}
	${TBL} ${SRCS} | ${TROFF} ${MACROS} -t > paper.${PRINTER}

E 3
D 4
summary.${PRINTER}: vi.summary
E 4
I 4
summary.ps: vi.summary
E 4
D 3
	${TBL} vi.summary | ${TROFF} ${MACROS} -t > summary.${PRINTER}
E 3
I 3
	${TBL} vi.summary | ${ROFF}  > ${.TARGET}
E 3

D 4
viapwh.${PRINTER}: vi.apwh.ms
E 4
I 4
viapwh.ps: vi.apwh.ms
E 4
D 3
	${TROFF} ${MACROS} -t vi.viapwh > viapwh.${PRINTER}
E 3
I 3
D 7
	${ROFF} vi.viapwh > ${.TARGET}
E 7
I 7
D 10
	${ROFF} vi.apwh.ms > ${.TARGET}
E 10
I 10
	${TBL} vi.apwh.ms | ${ROFF} > ${.TARGET}
E 10
E 7
E 3

D 3
clean:
	rm -f paper.[PT]* summary.[PT]* viapwh.[PT]* *.spell errs Errs make.out

spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 3
I 3
.include <bsd.doc.mk>
E 3
E 1
