h02923
s 00000/00000/00025
d D 8.1 93/06/01 23:58:12 bostic 18 17
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00010/00023
d D 5.16 92/07/16 23:38:14 mckusick 17 16
c update for new profiling method
e
s 00004/00004/00029
d D 5.15 92/03/03 00:23:50 mckusick 16 15
c break out machine independent part to ../csu.gmon/gmon.c
e
s 00003/00003/00030
d D 5.14 91/07/03 12:29:21 bostic 15 14
c use CFLAGS in CC lines
e
s 00002/00010/00031
d D 5.13 91/05/22 11:21:45 mckusick 14 13
c delete support for prof style profiling
e
s 00020/00020/00021
d D 5.12 91/05/03 12:28:36 donn 13 12
c Convert for GCC.  Works like the other architectures now.
e
s 00001/00000/00040
d D 5.11 90/07/02 16:10:14 bostic 12 11
c clean gmon.o mon.o moncrt0.o
e
s 00001/00004/00039
d D 5.10 90/06/08 14:02:43 bostic 11 10
c use prog, not own
e
s 00021/00053/00022
d D 5.9 90/05/11 12:49:07 bostic 10 9
c first pass for new make
e
s 00004/00002/00071
d D 5.8 90/03/15 21:54:20 mckusick 9 8
c update for separate machine compilation
e
s 00007/00004/00066
d D 5.7 90/03/11 17:10:38 bostic 8 7
c reorg; add cleandir
e
s 00010/00005/00060
d D 5.6 88/07/09 11:11:57 bostic 7 6
c install approved copyright notice
e
s 00012/00001/00053
d D 5.5 88/05/24 08:57:08 bostic 6 5
c add tags
e
s 00003/00001/00051
d D 5.4 88/05/20 15:04:05 bostic 5 4
c set DEFS to compile in SCCS ids.
e
s 00024/00018/00028
d D 5.3 88/05/20 13:48:25 bostic 4 3
c restructuring libc
e
s 00011/00004/00035
d D 5.2 87/07/27 16:16:04 bostic 3 1
c explicitly assign ownership
e
s 00008/00001/00038
d R 5.2 87/06/06 15:06:55 bostic 2 1
c added depend label
e
s 00039/00000/00000
d D 5.1 86/08/01 08:56:10 sam 1 0
c date and time created 86/08/01 08:56:10 by sam
e
u
U
t
T
I 1
D 3
#	%M%	%I%	%E%
E 3
D 10
#
I 3
D 4
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
E 4
#
D 4
#	%W%	(Berkeley)	%G%
E 4
I 4
# Redistribution and use in source and binary forms are permitted
D 7
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 7
E 4
#
E 10
E 3
D 4
DESTDIR=
E 4
I 4
#	%W% (Berkeley) %G%
D 10
#
E 4
D 5
CFLAGS=	-O
E 5
I 5
DEFS=	-DLIBC_SCCS
CFLAGS=	-O ${DEFS}
D 6
SRCS=	gmon.c mon.c
E 6
I 6
CSRCS=	gmon.c mon.c
ASRCS=	crt0.s  mcrt0.s
E 10
I 10

CFLAGS=	-O -DLIBC_SCCS
E 10
E 6
E 5
D 14
OBJS=	crt0.o mcrt0.o gcrt0.o
I 12
D 13
CLEANFILES=gmon.o mon.o moncrt0.o
E 13
I 13
CLEANFILES+=	gmon.o mon.o moncrt0.o core a.out
E 14
I 14
OBJS=	crt0.o gcrt0.o
D 16
CLEANFILES+=	gmon.o moncrt0.o core a.out
E 16
I 16
D 17
CLEANFILES+=	mcount.o moncrt0.o core a.out
E 17
I 17
CLEANFILES+=	core a.out
E 17
E 16
E 14
E 13
E 12
I 4
D 10
TAGSFILE=tags
E 10
E 4

D 13
.s.o:
D 10
	${AS} -o $*.o $*.s
	ld -x -r $*.o
D 9
	mv a.out $*.o
E 9
I 9
	mv ${OBJDIR}a.out ${OBJDIR}$*.o
E 10
I 10
	${AS} -o ${.TARGET} ${.IMPSRC}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}
E 10
E 9

E 13
D 4
all:	${OBJS}
E 4
I 4
D 8
all link: ${OBJS}
E 8
I 8
all: ${OBJS}
E 8
E 4

I 13
crt0.o: crt0.c
D 15
	${CC} -c -DCRT0 ${.ALLSRC}
E 15
I 15
	${CC} ${CFLAGS} -c -DCRT0 ${.ALLSRC}
E 15
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}

D 17
moncrt0.o: crt0.c
E 17
I 17
gcrt0.o: crt0.c
E 17
D 15
	${CC} -c -DMCRT0 ${.ALLSRC} -o ${.TARGET}
E 15
I 15
	${CC} ${CFLAGS} -c -DMCRT0 ${.ALLSRC} -o ${.TARGET}
E 15
D 17
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}

E 13
D 4
mcrt0.o:	moncrt0.o mon.o
	ld -x -r -o mcrt0.o moncrt0.o mon.o
E 4
I 4
D 14
mcrt0.o: moncrt0.o mon.o
D 10
	ld -x -r -o $@ moncrt0.o mon.o
E 10
I 10
	${LD} -x -r -o ${.TARGET} moncrt0.o mon.o
E 10
E 4

E 14
D 4
gcrt0.o:	moncrt0.o gmon.o
	ld -x -r -o gcrt0.o moncrt0.o gmon.o
E 4
I 4
D 16
gcrt0.o: moncrt0.o gmon.o
D 10
	ld -x -r -o $@ moncrt0.o gmon.o
E 10
I 10
D 13
	${LD} -x -r -o ${.TARGET} ${.ALLSRC}
E 13
I 13
	${LD} -x -r -o ${.TARGET} moncrt0.o gmon.o
E 16
I 16
gcrt0.o: moncrt0.o mcount.o
	${LD} -x -r -o ${.TARGET} moncrt0.o mcount.o
E 16
E 13
E 10
E 4
D 14

D 4
moncrt0.o:	mcrt0.s
	$(AS) -o moncrt0.o mcrt0.s
E 4
I 4
D 13
moncrt0.o: mcrt0.s
D 10
	${AS} -o $@ mcrt0.s
E 10
I 10
	${AS} -o ${.TARGET} ${.ALLSRC}
E 13
I 13
mon.o: mon.c
	${CC} -c ${DEFS} ${.IMPSRC}
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}
E 14
E 13
E 10
E 4

D 4
mon.o:	mon.c
E 4
I 4
D 10
mon.o: mon.c
E 4
	${CC} -S ${CFLAGS} mon.c
	ex - mon.s < mon.ex
D 4
	$(AS) -o mon.o mon.s
E 4
I 4
	${AS} -o $@ mon.s
E 10
I 10
D 13
mon.o: mon.c mon.ex
	${CC} -S ${CFLAGS} ${.IMPSRC}
	ex - mon.s < ${.CURDIR}/mon.ex
	${AS} -o ${.TARGET} mon.s
E 10
I 9
	rm -f mon.s
E 9
E 4

D 4
gmon.o:	gmon.c
E 4
I 4
D 10
gmon.o: gmon.c
E 4
	${CC} -S ${CFLAGS} gmon.c
	ex - gmon.s < mon.ex
E 10
I 10
gmon.o: gmon.c mon.ex
	${CC} -S ${CFLAGS} ${.IMPSRC}
	ex - gmon.s < ${.CURDIR}/mon.ex
E 10
D 4
	${AS} -o gmon.o gmon.s
E 4
I 4
	${AS} -o $@ gmon.s
I 9
	rm -f gmon.s
E 13
I 13
D 16
gmon.o: gmon.c gmon.h
E 16
I 16
mcount.o: ../csu.gmon/gmon.c ../csu.gmon/gmon.h
E 16
D 15
	${CC} -c ${DEFS} ${.IMPSRC}
E 15
I 15
	${CC} ${CFLAGS} -c ${DEFS} ${.IMPSRC}
E 17
E 15
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}
E 13
E 9
E 4

D 4
install: all
E 4
I 4
install:
E 4
D 3
	install -m 444 crt0.o ${DESTDIR}/lib/crt0.o
	install -m 444 mcrt0.o ${DESTDIR}/lib/mcrt0.o
	install -m 444 gcrt0.o ${DESTDIR}/usr/lib/gcrt0.o
E 3
I 3
D 8
	install -o bin -g bin -m 444 crt0.o ${DESTDIR}/lib/crt0.o
	install -o bin -g bin -m 444 mcrt0.o ${DESTDIR}/lib/mcrt0.o
E 8
I 8
D 10
	install -o bin -g bin -m 444 crt0.o ${DESTDIR}/usr/lib/crt0.o
	install -o bin -g bin -m 444 mcrt0.o ${DESTDIR}/usr/lib/mcrt0.o
E 8
	install -o bin -g bin -m 444 gcrt0.o ${DESTDIR}/usr/lib/gcrt0.o
E 10
I 10
	install -o ${BINOWN} -g ${BINGRP} -m 444 ${OBJS} \
	    ${DESTDIR}/usr/lib
E 10
E 3

D 10
clean:
D 4
	rm -f ${OBJS} *mon.s moncrt0.o mon.o gmon.o a.out errs core
E 4
I 4
D 8
	rm -f *.o *mon.s a.out core ${TAGSFILE}
E 8
I 8
D 9
	rm -f *.o *mon.s a.out core
E 9
I 9
	rm -f ${OBJDIR}*.o ${OBJDIR}a.out core
E 10
I 10
D 11
cleandir clean:
	rm -f ${OBJS} core a.out
E 10
E 9

E 11
D 10
cleandir: clean
	rm -f ${MAN} tags .depend
E 10
I 10
depend lint tags:
E 10
E 8
I 6

D 10
tags:
	cwd=`pwd`; \
	for i in ${CSRCS}; do \
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done
	(P=`pwd`; \
	egrep "^ENTRY(.*)|^SYSCALL(.*)" ${ASRCS} | sed \
"s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 $$P/\1 /^\2(\3\4$$/;" \
		>> ${TAGSFILE})
E 6
E 4
I 3

depend:
E 10
I 10
D 11
.include <bsd.own.mk>
E 11
I 11
.include <bsd.prog.mk>
E 11
E 10
E 3
E 1
