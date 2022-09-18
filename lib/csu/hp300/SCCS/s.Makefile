h39230
s 00000/00000/00025
d D 8.1 93/06/01 23:56:24 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00010/00023
d D 5.8 92/07/10 17:34:26 mckusick 8 7
c update for new profiling style
e
s 00004/00004/00029
d D 5.7 92/03/03 00:05:29 mckusick 7 6
c gmon.c moves out; mcount.c replaces it
e
s 00003/00003/00030
d D 5.6 91/07/03 12:28:28 bostic 6 5
c use CFLAGS in CC lines
e
s 00001/00009/00032
d D 5.5 91/05/21 18:43:51 mckusick 5 4
c delete support for prof style profiling
e
s 00001/00001/00040
d D 5.4 91/05/03 11:48:32 donn 4 3
c Botched sccs id
e
s 00015/00023/00026
d D 5.3 91/04/28 15:02:25 donn 3 2
c Clean-up for GCC.
e
s 00028/00076/00021
d D 5.2 90/06/29 17:31:33 bostic 2 1
c HP300 version (seems to work...)
e
s 00097/00000/00000
d D 5.1 90/06/25 23:09:50 bostic 1 0
c date and time created 90/06/25 23:09:50 by bostic
e
u
U
t
T
I 1
D 2
#
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	@(#)Makefile	5.4 (Berkeley) 9/5/85
#
#	crt0	Normal C run time startoff
#	mcrt0	C run time start off for profiling, ``prof'' conventions
#	gcrt0	C run time start off for profiling, ``gprof'' conventions
#
SRCS=	crt0.c mon.c gmon.c
OBJS=	crt0.o mcrt0.o gcrt0.o mon.o gmon.o
TAGSFILE=tags
E 2
I 2
D 3
#	%W% (Berkeley) %G%
E 3
I 3
D 4
#	#W# (Berkeley) %G%
E 4
I 4
#	%W% (Berkeley) %G%
E 4
E 3
E 2

D 2
CPP=	/lib/cpp
E 2
I 2
CFLAGS=	-O -DLIBC_SCCS
D 5
OBJS=	crt0.o mcrt0.o gcrt0.o
E 5
I 5
OBJS=	crt0.o gcrt0.o
E 5
D 7
CLEANFILES+=	gmon.o mon.o moncrt0.o core a.out
E 7
I 7
D 8
CLEANFILES+=	mcount.o mon.o moncrt0.o core a.out
E 8
I 8
CLEANFILES+=	core a.out
E 8
E 7
E 2

all: ${OBJS}

D 2
install: ${OBJS}
	install -m 755 crt0.o ${DESTDIR}/usr/lib/crt0.o
	install -m 755 mcrt0.o ${DESTDIR}/usr/lib/mcrt0.o
	install -m 755 gcrt0.o ${DESTDIR}/usr/lib/gcrt0.o

crt0.o:	crt0.c
	cc -S ${DFLAGS} -DCRT0 crt0.c
E 2
I 2
crt0.o: crt0.c
D 3
	${CC} -S -DCRT0 ${.ALLSRC}
E 2
	${CPP} crt0.s > x.s
D 2
	as -o x.o x.s
	ld -x -r -o crt0.o x.o
E 2
I 2
	${AS} -o x.o x.s
	${LD} -x -r -o ${.TARGET} x.o
E 2
	rm -f x.s x.o crt0.s
E 3
I 3
D 6
	${CC} -c -DCRT0 ${.ALLSRC}
E 6
I 6
	${CC} ${CFLAGS} -c -DCRT0 ${.ALLSRC}
E 6
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}
E 3

D 8
moncrt0.o: crt0.c
E 8
I 8
gcrt0.o: crt0.c
E 8
D 2
	cc -S ${DFLAGS} -DMCRT0 crt0.c
E 2
I 2
D 3
	${CC} -S -DMCRT0 ${.ALLSRC}
E 2
	${CPP} crt0.s > x.s
D 2
	as -o x.o x.s
	ld -x -r -o moncrt0.o x.o
E 2
I 2
	${AS} -o x.o x.s
	${LD} -x -r -o ${.TARGET} x.o
E 2
	rm -f x.s x.o crt0.s
E 3
I 3
D 6
	${CC} -c -DMCRT0 ${.ALLSRC} -o ${.TARGET}
E 6
I 6
	${CC} ${CFLAGS} -c -DMCRT0 ${.ALLSRC} -o ${.TARGET}
E 6
D 8
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}
E 3

D 2
gcrt0.o: moncrt0.o gmon.o
	ld -x -r -o gcrt0.o moncrt0.o gmon.o

E 2
D 5
mcrt0.o: moncrt0.o mon.o
D 2
	ld -x -r -o mcrt0.o moncrt0.o mon.o
E 2
I 2
	${LD} -x -r -o ${.TARGET} moncrt0.o mon.o
E 2

E 5
I 2
D 7
gcrt0.o: moncrt0.o gmon.o
	${LD} -x -r -o ${.TARGET} moncrt0.o gmon.o
E 7
I 7
gcrt0.o: moncrt0.o mcount.o
	${LD} -x -r -o ${.TARGET} moncrt0.o mcount.o
E 7
D 5

E 2
D 3
mon.o: mon.c mon.ex
D 2
	cc -S ${DEFS} ${DFLAGS} mon.c
	ex - mon.s < mon.ex
	as -o x.o mon.s
	ld -x -r -o mon.o x.o
E 2
I 2
	${CC} -S ${DEFS} ${.IMPSRC}
	ex - mon.s < ${.CURDIR}/mon.ex
	${AS} -o x.o mon.s
	${LD} -x -r -o ${.TARGET} x.o
E 2
	rm -f x.o mon.s
E 3
I 3
mon.o: mon.c
	${CC} -c ${DEFS} ${.IMPSRC}
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}
E 5
E 3

D 3
gmon.o: gmon.c gmon.h gmon.ex
D 2
	cc -S ${DEFS} ${DFLAGS} gmon.c
	ex - gmon.s < gmon.ex
	as -o x.o gmon.s
	ld -x -r -o gmon.o x.o
E 2
I 2
	${CC} -S ${DEFS} ${.IMPSRC}
	ex - gmon.s < ${.CURDIR}/gmon.ex
	${AS} -o x.o gmon.s
	${LD} -x -r -o ${.TARGET} x.o
E 2
	rm -f x.o gmon.s
E 3
I 3
D 7
gmon.o: gmon.c gmon.h
E 7
I 7
mcount.o: ../csu.gmon/gmon.c ../csu.gmon/gmon.h
E 7
D 6
	${CC} -c ${DEFS} ${.IMPSRC}
E 6
I 6
	${CC} ${CFLAGS} -c ${DEFS} ${.IMPSRC}
E 8
E 6
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}
E 3

D 2
tags:	
	cwd=`pwd`; \
	for i in ${SRCS}; do \
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done
E 2
I 2
install:
	install -o ${BINOWN} -g ${BINGRP} -m 444 ${OBJS} \
	    ${DESTDIR}/usr/lib
E 2

D 2
clean:
	rm -f ${OBJS} *.o *.s core errs tags Makefile.bak
E 2
I 2
depend lint tags:
E 2

D 2
lint:	crt0.c
	lint crt0.c -DMCRT0
	lint crt0.c -DGCRT0
	lint crt0.c -DCRT0

depend:
	for i in ${SRCS}; do \
	    cc -M ${DEFS} ${DFLAGS} $$i | awk ' { if ($$1 != prev) \
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

crt0.o : crt0.c 
mon.o : mon.c 
gmon.o : gmon.c gmon.h 
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
