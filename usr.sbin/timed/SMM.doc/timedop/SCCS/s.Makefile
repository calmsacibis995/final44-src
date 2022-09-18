h31408
s 00000/00000/00007
d D 8.1 93/06/08 14:17:23 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00004/00006
d D 6.4 93/06/05 16:47:26 bostic 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00030/00006
d D 6.3 90/06/30 15:05:26 bostic 3 2
c new doc makefiles
e
s 00014/00003/00022
d D 6.2 89/03/07 10:54:52 bostic 2 1
c add Berkeley specific copyright notice, networking release
e
s 00025/00000/00000
d D 6.1 86/05/23 18:31:31 mckusick 1 0
c first draft of document for 4.3BSD
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
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
#
E 3
#	%W% (Berkeley) %G%
D 3
#
E 3
I 3

D 4
DIR=	smm/08.timedop
E 4
I 4
DIR=	smm/11.timedop
E 4
E 3
SRCS=	timed.ms
MACROS=	-ms
D 3
PRINTER=Pdp
TROFF=	ditroff -${PRINTER}
E 3
D 4

D 3
paper:	paper.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}

E 3
paper.${PRINTER}: ${SRCS}
D 3
	${TROFF} ${MACROS} -t ${SRCS} > paper.${PRINTER}
E 3
I 3
	${ROFF} ${SRCS} > ${.TARGET}
E 4
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
