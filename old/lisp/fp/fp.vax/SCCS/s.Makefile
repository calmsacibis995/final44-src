h57164
s 00004/00001/00047
d D 4.5 89/07/30 14:07:43 bostic 5 4
c add cleandir label
e
s 00001/00001/00047
d D 4.4 89/07/30 09:39:17 bostic 4 3
c add all label
e
s 00002/00002/00046
d D 4.3 89/05/10 22:24:29 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00002/00000/00046
d D 4.2 87/05/31 21:09:57 bostic 2 1
c added depend label
e
s 00046/00000/00000
d D 4.1 85/09/07 15:57:07 mckusick 1 0
c date and time created 85/09/07 15:57:07 by mckusick
e
u
U
t
T
I 1
#  FP interpreter/compiler
#  Copyright (c) 1982  Scott B. Baden
#  Berkeley, California
#
#  Copyright (c) 1982 Regents of the University of California.
#  All rights reserved.  The Berkeley software License Agreement
#  specifies the terms and conditions for redistribution.
#
#	%W% (Berkeley) %G%
#
DESTDIR =

FP_SYS = 	runFp.l fpMain.l\
		scanner.l parser.l codeGen.l\
		primFp.l utils.l fpPP.l handlers.l fpMeasures.l

FP_SYSO = 	runFp.o fpMain.o\
		scanner.o parser.o codeGen.o\
		primFp.o utils.o  fpPP.o handlers.o fpMeasures.o

.SUFFIXES:
.SUFFIXES:	.l .o
.l.o:
		liszt -axq $<


D 4
fp:		${FP_SYSO}
E 4
I 4
all fp:		${FP_SYSO}
E 4
		/bin/rm -f fp
		echo "(progn (load 'runFp)\
			     (dumplisp fp))" | lisp > junk.fp
		chmod 755 fp

${FP_SYSO}:	specials.l fpMacs.o


D 3
install:	fp
		install -s fp ${DESTDIR}/usr/ucb/fp
E 3
I 3
install:
	install -s -o bin -g bin -m 755 fp ${DESTDIR}/usr/bin
E 3

D 5
clean:		
E 5
I 5
clean:
E 5
		rm -f core *.[ox] junk.fp
I 5

cleandir: clean
	rm -f ${MAN} tags .depend
E 5


listings:	${FP_SYS}
		print runFp.l fpMain.l scanner.l parser.l codeGen.l \
		primFp.l utils.l fpPP.l handlers.l fpMeasures.l \
		specials.l fpMacs.l  &
I 2

depend:
E 2
E 1
