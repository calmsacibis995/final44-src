h56149
s 00000/00000/00016
d D 8.1 93/06/06 15:31:28 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00014
d D 5.6 93/04/05 21:51:02 ralph 6 5
c add mips to list of gcc machines.
e
s 00001/00001/00014
d D 5.5 92/10/13 19:08:45 torek 5 4
c sparc uses gcc too
e
s 00006/00000/00009
d D 5.4 91/02/19 14:25:50 bostic 4 3
c hacks for gcc pre-processor
e
s 00002/00011/00007
d D 5.3 90/06/23 12:57:30 bostic 3 2
c don't need special tags anymore
e
s 00011/00021/00007
d D 5.2 90/05/11 13:48:09 bostic 2 1
c first pass for new make
e
s 00025/00000/00000
d D 5.1 88/10/24 11:04:40 bostic 1 0
c date and time created 88/10/24 11:04:40 by bostic
e
u
U
t
T
I 1
D 2
#
# Copyright (c) 1988 The Regents of the University of California.
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
E 2
#	%W% (Berkeley) %G%
D 2
#
E 2
I 2

E 2
D 3
MAN=	mkdep.0
E 3
I 3
MAN1=	mkdep.0
E 3

I 4
D 5
.if (${MACHINE} == "hp300" || ${MACHINE} == "i386")
E 5
I 5
D 6
.if (${MACHINE} == "hp300" || ${MACHINE} == "i386" || ${MACHINE} == "sparc")
E 6
I 6
.if (${MACHINE} == "hp300" || ${MACHINE} == "i386" || \
	${MACHINE} == "mips" || ${MACHINE} == "sparc")
E 6
E 5
E 4
D 2
all mkdep clean depend lint tags:
E 2
I 2
D 3
all mkdep: ${MAN}
E 2

I 2
clean depend lint tags:

E 2
cleandir:
	rm -f ${MAN}

D 2
install: ${MAN}
	install -c -o bin -g bin -m 755 mkdep.sh ${DESTDIR}/usr/bin/mkdep
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 2
I 2
install:
E 3
I 3
beforeinstall:
E 3
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
I 4
	    ${.CURDIR}/mkdep.gcc.sh ${DESTDIR}/usr/bin/mkdep
.else
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
E 4
	    ${.CURDIR}/mkdep.sh ${DESTDIR}/usr/bin/mkdep
I 4
.endif
E 4
D 3
	install -c -o ${MANOWN} -g ${MANGRP} -m ${MANMODE} ${MAN} \
	    ${DESTDIR}${MANDIR}1
E 3

.include <bsd.prog.mk>
E 2
E 1
