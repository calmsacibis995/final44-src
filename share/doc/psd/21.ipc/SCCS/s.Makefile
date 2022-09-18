h07239
s 00000/00000/00010
d D 8.1 93/06/08 18:42:23 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 1.6 93/06/08 18:42:15 bostic 7 5
c document numbering changes for 4.4BSD
e
s 00000/00000/00010
d R 8.1 93/06/08 18:38:03 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 1.5 93/06/05 16:09:40 bostic 5 4
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00032/00006
d D 1.4 90/06/30 15:02:48 bostic 4 3
c new doc makefiles
e
s 00014/00003/00024
d D 1.3 89/03/07 10:59:46 bostic 3 2
c add Berkeley specific copyright, for networking release
e
s 00016/00010/00011
d D 1.2 86/05/02 17:41:06 karels 2 1
c corrections
e
s 00021/00000/00000
d D 1.1 86/04/30 12:29:50 karels 1 0
c date and time created 86/04/30 12:29:50 by karels
e
u
U
t
T
I 2
D 4
#
E 2
I 1
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

D 5
DIR=	ps1/08.ipc
E 5
I 5
D 7
DIR=	psd/20.ipc
E 7
I 7
DIR=	psd/21.ipc
E 7
E 5
E 4
D 2
# Makefile to run off revised 4.3 ipc primer
#
E 2
I 2
SRCS=	0.t 1.t 2.t 3.t 4.t 5.t
MACROS=	-ms
D 4
PRINTER=-Pdp
EQN=	deqn ${PRINTER}
TBL=	dtbl ${PRINTER}
TROFF=	ditroff ${PRINTER}
E 4
E 2

D 2
TROFF= ditroff
PKG= -ms
TBL= dtbl
TBLARGS =
PRINTER = -Pdp
E 2
I 2
D 4
ipc:	ipc.${PRINTER}
	lpr ${PRINTER} -n ipc.${PRINTER}
E 2

E 4
D 2
ipc: 0.t 1.t 2.t 3.t 4.t 5.t
	$(TBL) $(TBLARGS) *.t | $(TROFF) $(PKG) $(PRINTER)
E 2
I 2
D 5
ipc.${PRINTER}: ${SRCS}
E 5
I 5
paper.ps: ${SRCS}
E 5
D 4
	${TBL} ${SRCS} | ${TROFF} ${MACROS} -t > ipc.${PRINTER}
E 4
I 4
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
E 4
E 2

D 4
clean:
D 2
	rm *.imP *.bak *.CKP
E 2
I 2
	rm -f ipc.-* *.spell errs Errs make.out
E 2

I 2
spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 4
I 4
.include <bsd.doc.mk>
E 4
E 2
E 1
