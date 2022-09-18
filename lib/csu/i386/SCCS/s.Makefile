h54228
s 00000/00000/00025
d D 8.1 93/06/01 23:56:41 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00010/00023
d D 5.9 92/07/16 23:26:36 mckusick 9 8
c update for new structure
e
s 00004/00004/00029
d D 5.8 92/03/03 00:17:23 mckusick 8 7
c break out machine independent part to ../csu.gmon/gmon.c
e
s 00003/00003/00030
d D 5.7 91/07/03 12:29:48 bostic 7 6
c use CFLAGS in CC lines
e
s 00002/00010/00031
d D 5.6 91/05/22 11:08:40 mckusick 6 5
c delete support for prof style profiling
e
s 00026/00012/00015
d D 5.5 91/04/28 12:23:50 donn 5 4
c Support profiling on the 386; because of gcc asm(), we can get rid of :fix.
e
s 00002/00000/00025
d D 5.4 91/03/21 16:10:50 bostic 4 3
c needed bsd.prog.mk
e
s 00016/00111/00009
d D 5.3 90/05/14 19:38:30 bostic 3 2
c makefile for pmake
e
s 00004/00004/00116
d D 5.2 90/05/14 15:31:38 william 2 1
c Release 0.1 changes
e
s 00120/00000/00000
d D 5.1 90/04/23 18:08:31 william 1 0
c date and time created 90/04/23 18:08:31 by william
e
u
U
t
T
I 1
D 3
#-
# Copyright (c) 1990 The Regents of the University of California.
# All rights reserved.
#
# This code is derived from software contributed to Berkeley by
# William Jolitz.
#
#
# Copying or redistribution in any form is explicitly forbidden
# unless prior written permission is obtained from William Jolitz or an
# authorized representative of the University of California, Berkeley.
#
# Freely redistributable copies of this code will be available in
# the near future; for more information contact William Jolitz or
# the Computer Systems Research Group at the University of California,
# Berkeley.
#
# The name of the University may not be used to endorse or promote
# products derived from this software without specific prior written
# permission.  THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE.
E 3
#	%W% (Berkeley) %G%
D 2
CC=gcc
AS=a386
E 2
I 2
D 3
AS=as
E 2
#
#	crt0	Normal C run time startoff
#	mcrt0	C run time start off for profiling, ``prof'' conventions
#	gcrt0	C run time start off for profiling, ``gprof'' conventions
#
DESTDIR=
SRCS=	crt0.c # mon.c gmon.c
OBJS=	crt0.o # mcrt0.o gcrt0.o mon.o gmon.o
TAGSFILE=tags
E 3

I 3
CFLAGS=	-O -DLIBC_SCCS
D 5
OBJS=	crt0.o
E 5
I 5
D 6
OBJS=	crt0.o mcrt0.o gcrt0.o
CLEANFILES+=	gmon.o mon.o moncrt0.o core a.out
E 6
I 6
OBJS=	crt0.o gcrt0.o
D 8
CLEANFILES+=	gmon.o moncrt0.o core a.out
E 8
I 8
D 9
CLEANFILES+=	mcount.o moncrt0.o core a.out
E 9
I 9
CLEANFILES+=	core a.out
E 9
E 8
E 6
E 5

E 3
all: ${OBJS}

D 3
install: ${OBJS}
	mv crt0.o ${DESTDIR}/lib/crt0.o
	# mv mcrt0.o ${DESTDIR}/lib/mcrt0.o
	# mv gcrt0.o ${DESTDIR}/usr/lib/gcrt0.o

crt0.o:	crt0.c
	${CC} -S ${DFLAGS} -DCRT0 crt0.c
	grep -v "^#[ _]" <crt0.s >x.s 
I 2
	ed x.s <:fix
E 2
	mv x.s crt0.s
D 2
	/lib/cpp crt0.s > x.s
E 2
I 2
	/lib/cpp -traditional crt0.s > x.s
E 3
I 3
crt0.o: crt0.c
D 5
	${CC} -S -DCRT0 ${.ALLSRC}
	grep -v "^#[ _]" < ${.PREFIX}.s > x.s
	ed x.s < :fix
	mv x.s ${.PREFIX}.s
	${CPP} -traditional crt0.s > x.s
E 3
E 2
	${AS} -o x.o x.s
D 3
	ld -x -r -o crt0.o x.o
E 3
I 3
	${LD} -x -r -o crt0.o x.o
E 3
	rm -f x.s x.o crt0.s
E 5
I 5
D 7
	${CC} -c -DCRT0 ${.ALLSRC}
E 7
I 7
	${CC} ${CFLAGS} -c -DCRT0 ${.ALLSRC}
E 7
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}
E 5

I 5
D 9
moncrt0.o: crt0.c
E 9
I 9
gcrt0.o: crt0.c
E 9
D 7
	${CC} -c -DMCRT0 ${.ALLSRC} -o ${.TARGET}
E 7
I 7
	${CC} ${CFLAGS} -c -DMCRT0 ${.ALLSRC} -o ${.TARGET}
E 7
D 9
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}

D 6
mcrt0.o: moncrt0.o mon.o
	${LD} -x -r -o ${.TARGET} moncrt0.o mon.o

E 6
D 8
gcrt0.o: moncrt0.o gmon.o
	${LD} -x -r -o ${.TARGET} moncrt0.o gmon.o
E 8
I 8
gcrt0.o: moncrt0.o mcount.o
	${LD} -x -r -o ${.TARGET} moncrt0.o mcount.o
E 8
D 6

mon.o: mon.c
	${CC} -c ${DEFS} ${.IMPSRC}
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}
E 6

D 8
gmon.o: gmon.c gmon.h
E 8
I 8
mcount.o: ../csu.gmon/gmon.c ../csu.gmon/gmon.h
E 8
D 7
	${CC} -c ${DEFS} ${.IMPSRC}
E 7
I 7
	${CC} ${CFLAGS} -c ${DEFS} ${.IMPSRC}
E 9
E 7
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}

E 5
D 3
moncrt0.o: crt0.c
	${CC} -S ${DFLAGS} -DMCRT0 crt0.c
	grep -v "^#[ _]" <crt0.s >x.s 
	mv x.s crt0.s
D 2
	/lib/cpp crt0.s > x.s
E 2
I 2
	/lib/cpp -traditional crt0.s > x.s
E 2
	${AS} -o x.o x.s
	ld -x -r -o moncrt0.o x.o
	rm -f x.s x.o crt0.s
E 3
I 3
install:
	install -o ${BINOWN} -g ${BINGRP} -m 444 ${OBJS} \
	    ${DESTDIR}/usr/lib
E 3
D 5

D 3
gcrt0.o: moncrt0.o gmon.o
	ld -x -r -o gcrt0.o moncrt0.o gmon.o
E 3
I 3
cleandir clean:
	rm -f ${OBJS} gmon.o mon.o moncrt0.o core a.out x.s x.o crt0.s
E 5
E 3

D 3
mcrt0.o: moncrt0.o mon.o
	ld -x -r -o mcrt0.o moncrt0.o mon.o

mon.o: mon.c mon.ex
	${CC} -S ${DEFS} ${DFLAGS} mon.c
	ex - mon.s < mon.ex
	${AS} -o x.o mon.s
	ld -x -r -o mon.o x.o
	rm -f x.o mon.s

gmon.o: gmon.c gmon.h gmon.ex
	${CC} -S ${DEFS} ${DFLAGS} gmon.c
	ex - gmon.s < gmon.ex
	${AS} -o x.o gmon.s
	ld -x -r -o gmon.o x.o
	rm -f x.o gmon.s

tags:	
	cwd=`pwd`; \
	for i in ${SRCS}; do \
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done

clean:
	rm -f ${OBJS} *.o *.s core errs tags Makefile.bak

lint:	crt0.c
	lint crt0.c -DMCRT0
	lint crt0.c -DGCRT0
	lint crt0.c -DCRT0

depend:
	for i in ${SRCS}; do \
	    ${CC} -M ${DEFS} ${DFLAGS} $$i | awk ' { if ($$1 != prev) \
		{ if (rec != "") print rec; rec = $$0; prev = $$1; } \
		else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
		else rec = rec " " $$2 } } \
		END { print rec } ' >> makedep; done
	echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	cp Makefile Makefile.bak
	ed - Makefile < eddep
	rm eddep makedep
	echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	echo '# see make depend above' >> Makefile

# DO NOT DELETE THIS LINE -- make depend uses it

crt0.o: crt0.c
mon.o: mon.c
gmon.o: gmon.c ./gmon.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
E 3
I 3
depend lint tags:
I 4

.include <bsd.prog.mk>
E 4
E 3
E 1
