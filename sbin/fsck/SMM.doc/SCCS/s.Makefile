h28020
s 00000/00000/00007
d D 8.1 93/06/08 14:04:19 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00006
d D 4.5 93/06/05 16:41:15 bostic 5 4
c new doc.mk; document numbering changes for 4.4BSD
e
s 00001/00004/00006
d D 4.4 93/06/05 12:56:06 bostic 4 3
c make it work for 4.4BSD
e
s 00005/00015/00005
d D 4.3 90/06/30 15:05:09 bostic 3 2
c new doc makefiles
e
s 00005/00004/00015
d D 4.2 85/07/18 22:43:35 mckusick 2 1
c update to reflect 4.3BSD version of fsck
e
s 00019/00000/00000
d D 4.1 85/06/03 17:31:54 mckusick 1 0
c date and time created 85/06/03 17:31:54 by mckusick
e
u
U
t
T
I 1
D 3
#
# Copyright (c) 1982 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 3
#	%W% (Berkeley) %G%
D 3
#
E 3
I 3

D 5
DIR=	smm/05.fsck
E 5
I 5
DIR=	smm/03.fsck
E 5
E 3
SRCS=	0.t 1.t 2.t 3.t 4.t
D 2
TROFF=	itroff
TYPE=	-t
E 2
I 2
D 4
TROFF=	ditroff
D 3
PRINTER=-Pdp
TYPE=	-n
E 3
E 2

D 3
paper:	fsck.t
D 2
	lpr -Pimagen ${TYPE} fsck.t
E 2
I 2
	lpr ${PRINTER} ${TYPE} fsck.t
E 3
I 3
paper.${PRINTER}: ${SRCS}
	${ROFF} ${SRCS} > ${.TARGET}
E 4
I 4
MACROS=	-ms
E 4
E 3
E 2

D 3
fsck.t:	${SRCS}
D 2
	${TROFF} -ms -t ${SRCS} > fsck.t
E 2
I 2
	${TROFF} ${PRINTER} -ms -t ${SRCS} > fsck.t
E 2

clean:
	rm -f fsck.t
E 3
I 3
.include <bsd.doc.mk>
E 3
E 1
