h07631
s 00001/00001/00004
d D 5.9 91/01/13 10:13:25 bostic 9 8
c does the right thing in the mk script
e
s 00001/00001/00004
d D 5.8 91/01/13 10:11:15 bostic 8 7
c move Fortran libraries out of /usr/src/lib
e
s 00002/00033/00003
d D 5.7 90/06/17 18:22:32 bostic 7 6
c pmake style, reorg the directories
e
s 00002/00002/00034
d D 5.6 90/06/17 17:23:21 bostic 6 5
c move fpr and fsplit elsewhere
e
s 00027/00015/00009
d D 5.5 88/10/25 18:18:21 bostic 5 4
c add man page, cleanup
e
s 00002/00002/00022
d D 5.4 87/06/18 17:37:28 bostic 4 3
c remove extra level of Makefiles
e
s 00012/00015/00012
d D 5.3 87/06/18 17:16:19 bostic 3 2
c new template
e
s 00000/00002/00027
d D 5.2 87/05/24 14:42:59 bostic 2 1
c MACHINE defined in make, now
e
s 00029/00000/00000
d D 5.1 87/05/11 09:32:39 mckusick 1 0
c date and time created 87/05/11 09:32:39 by mckusick
e
u
U
t
T
I 1
D 7
#
D 5
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 5
I 5
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 5
#
D 4
#	%W% (Berkeley) %G%
E 4
I 4
D 5
#	@(#)Makefile	5.3 (Berkeley) 6/18/87
E 5
I 5
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
E 5
E 4
#
E 7
I 5
#	%W% (Berkeley) %G%
D 7
#
I 6
SUBDIR=	f77.${MACHINE}/f77 f77.${MACHINE}/f77pass1
E 6
MAN=	f77.0
E 7
E 5
D 3
DESTDIR	      =
E 3
I 3
D 4
SUBDIR=	f77.${MACHINE} fpr fsplit
E 4
I 4
D 6
SUBDIR=	f77.${MACHINE}/f77 f77.${MACHINE}/f77pass1 fpr fsplit
E 6
E 4
E 3

D 2
MACHINE	      = unknown

E 2
D 3
SUBDIR	      = f77.${MACHINE} fpr fsplit
E 3
I 3
D 5
all: FRC
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS}); done
E 5
I 5
D 6
all f77 clean lint tags: FRC
E 6
I 6
D 7
all depend clean lint tags: FRC
E 6
	for i in ${SUBDIR}; \
		do (cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done
E 7
I 7
D 8
SUBDIR=	f77.${MACHINE} pass1.${MACHINE}
E 8
I 8
D 9
SUBDIR=	f77.${MACHINE} pass1.${MACHINE} libF77 libI77 libU77
E 9
I 9
SUBDIR=	f77 libF77 libI77 libU77 pass1
E 9
E 8
E 7
E 5
E 3

D 3
all:		${SUBDIR}
E 3
I 3
D 5
install: FRC
	for i in ${SUBDIR}; do \
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); \
	done
E 5
I 5
D 7
cleandir: clean
	for i in ${SUBDIR}; \
		do (cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done
	rm -f ${MAN} tags .depend
E 5
E 3

D 3
${SUBDIR}:	FRC
		cd $@; make ${MFLAGS}
E 3
I 3
D 5
clean: FRC
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} clean); done
E 3

D 3
FRC:
E 3
I 3
depend: FRC
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} depend); done
E 5
I 5
install: ${MAN}
	for i in ${SUBDIR}; do \
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 5
E 3

D 3
install:
		for i in ${SUBDIR}; do \
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); done

clean:
		for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} clean); done

depend:
		for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} depend); done
E 3
I 3
FRC:
E 7
I 7
.include <bsd.subdir.mk>
E 7
E 3
E 1
