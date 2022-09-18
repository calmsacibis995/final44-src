h18759
s 00000/00000/00013
d D 8.1 93/08/14 10:32:32 mckusick 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00003/00010
d D 6.7 93/08/02 12:08:24 elan 8 6
c Deleted gremlin pictures and added pic versions.
e
s 00000/00000/00013
d R 8.1 93/06/08 18:36:53 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00005/00011
d D 6.6 93/06/05 15:38:33 bostic 6 5
c update for new doc.mk; document numbering changes for 4.4BSD
e
s 00003/00008/00013
d D 6.5 91/01/02 22:29:23 karels 5 4
c mv gremlin in-line (only works with older ditroff, but don't need
c separate printers now)
e
s 00012/00034/00009
d D 6.4 90/06/30 15:02:45 bostic 4 3
c new doc makefiles
e
s 00014/00003/00029
d D 6.3 89/03/07 11:04:00 bostic 3 2
c add Berkeley specific copyright, networking release
e
s 00001/00003/00031
d D 6.2 86/05/06 17:09:46 mckusick 2 1
c cannot vgrind with -me
e
s 00034/00000/00000
d D 6.1 86/05/04 16:35:06 mckusick 1 0
c date and time created 86/05/04 16:35:06 by mckusick
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
E 3
#
E 4
#	%W% (Berkeley) %G%
D 4
#
E 4
I 4

D 6
DIR=	ps1/07.ipctut
E 6
I 6
DIR=	psd/20.ipctut
E 6
E 4
SRCS=	tutor.me
D 5
GSRCS=	gremlins
E 5
MACROS=	-me
D 4
PRINTER=Pdp
SOELIM=	soelim
D 2
GRIND=	vgrind -f
E 2
TBL=	dtbl -${PRINTER}
TROFF=	ditroff -${PRINTER}
E 4
I 4
D 8
EXTRA=	accept.grn dgramread.c dgramsend.c gremlins pipe.c pipe.grn \
	socketpair.c socketpair.grn strchkread.c streamread.c streamwrite.c \
E 8
I 8
EXTRA=	dgramread.c dgramsend.c fig2.pic fig3.pic fig8.pic pipe.c \
	socketpair.c strchkread.c streamread.c streamwrite.c \
E 8
	udgramread.c udgramsend.c ustreamread.c ustreamwrite.c
E 4

D 4
paper:	paper.${PRINTER} pics.Pip
	lpr -${PRINTER} -n paper.${PRINTER}
	lpr -Pip -n pics.Pip
E 4
I 4
D 5
print: paper.${PRINTER} pics.${PRINTER}
E 5
I 5
D 6
print: paper.${PRINTER}
E 5
	lpr -P${PRINTER} -n paper.${PRINTER}
D 5
	lpr -P${PRINTER} -n pics.P${PRINTER
E 5
E 4

D 5
paper.${PRINTER}: ${SRCS}
D 2
	${SOELIM} ${SRCS} | ${GRIND} | ${TBL} | \
	${TROFF} ${MACROS} -t > paper.${PRINTER}
E 2
I 2
D 4
	${TBL} ${SRCS} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 4
I 4
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
E 4
E 2

D 4
pics.Pip: ${GSRCS}
	grn -Pip ${GSRCS} | ditroff -Pip -t >pics.Pip
E 4
I 4
pics.${PRINTER}: ${GSRCS}
	${GREMLIN} ${GSRCS} | ${ROFF} > ${.TARGET}
E 5
I 5
paper.${PRINTER}: ${SRCS} ${EXTRA}
E 6
I 6
paper.ps: ${SRCS} ${EXTRA}
E 6
D 8
	${TBL} ${SRCS} | ${GREMLIN} | ${ROFF} > ${.TARGET}
E 8
I 8
	${SOELIM} ${SRCS} | ${PIC} | ${TBL} | ${ROFF} > ${.TARGET}
E 8
E 5
E 4

D 4
clean:
	rm -f paper.[PT]* *.spell errs Errs make.out

spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 4
I 4
.include <bsd.doc.mk>
E 4
E 1
