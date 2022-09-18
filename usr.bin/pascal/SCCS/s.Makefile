h06687
s 00000/00000/00006
d D 8.1 93/06/06 16:20:58 bostic 16 15
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00005
d D 5.9 91/01/11 16:24:20 bostic 15 14
c move libpc from /usr/src/lib
e
s 00003/00033/00003
d D 5.8 90/06/29 11:37:33 bostic 14 13
c redo pascal makefiles
e
s 00004/00002/00032
d D 5.7 90/06/25 00:57:50 bostic 13 12
c syntactic sugar
e
s 00001/00001/00033
d D 5.6 89/03/29 12:29:07 bostic 12 11
c add man directory
e
s 00017/00028/00017
d D 5.5 89/03/06 11:49:08 bostic 11 10
c cleanup
e
s 00021/00010/00024
d D 5.4 87/10/27 07:47:45 bostic 10 7
c new template, pass depend on down
e
s 00015/00006/00028
d R 5.4 87/10/26 07:43:42 bostic 9 7
c new template
e
s 00011/00006/00028
d R 5.4 87/10/26 07:42:42 bostic 8 7
c new template
e
s 00002/00000/00032
d D 5.3 87/05/31 21:12:55 bostic 7 6
c added depend label
e
s 00004/00001/00028
d D 5.2 87/05/10 16:20:59 mckusick 6 5
c update from Jim McKie
e
s 00006/00001/00023
d D 5.1 85/06/04 14:06:57 mckusick 5 4
c Add copyright
e
s 00001/00001/00023
d D 1.4 85/06/04 13:37:50 mckusick 4 3
c eyacc moves into Pascal
e
s 00005/00002/00019
d D 1.3 83/04/17 14:11:09 peter 3 2
c record subdirectory names in the output as you get to them.
e
s 00001/00001/00020
d D 1.2 83/02/03 18:07:02 mckusick 2 1
c pascal is renamed to utilities
e
s 00021/00000/00000
d D 1.1 83/01/31 18:05:04 mckusick 1 0
c date and time created 83/01/31 18:05:04 by mckusick
e
u
U
t
T
I 1
D 5
#	%W%	(Berkeley)	%G%
E 5
I 5
D 14
#
D 11
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 11
I 11
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
E 11
#
I 11
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
E 14
E 11
#	%W% (Berkeley) %G%
E 5
D 14
#
D 10
DESTDIR=
E 10
CFLAGS=	-O
E 14

D 11
# Programs that live in subdirectories, and have makefiles of their own.
#
E 11
D 2
SUBDIR=	pi pc0 px pxp pdx pascal
E 2
I 2
D 4
SUBDIR=	pi pc0 px pxp pdx utilities
E 4
I 4
D 10
SUBDIR=	eyacc pi pc0 px pxp pdx utilities
E 10
I 10
D 12
SUBDIR=	pi pc0 px pxp pdx utilities
E 12
I 12
D 14
SUBDIR=	pi pc0 px pxp pdx man utilities
E 14
I 14
D 15
SUBDIR=	eyacc how pc pc0 pc2 pc3 pcexterns pdx pi pix pmerge px \
E 15
I 15
SUBDIR=	eyacc how libpc pc pc0 pc2 pc3 pcexterns pdx pi pix pmerge px \
E 15
	px_header pxp pxref
E 14
E 12
E 10
E 4
E 2

D 6
all:	${SUBDIR}
E 6
I 6
D 11
all:
E 11
I 11
D 14
all clean cleandir install lint tags:
E 11
D 10
	for i in ${SUBDIR}; do \
E 10
I 10
	for i in eyacc ${SUBDIR}; do \
E 10
D 11
		(cd $$i; make ${MFLAGS}); \
	done
E 11
I 11
D 13
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done
E 13
I 13
		(echo "==> $$i"; \
		    cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done
E 13
E 11
E 6

D 10
${SUBDIR}: /tmp
E 10
I 10
${SUBDIR}: FRC
E 10
	cd $@; make ${MFLAGS}

D 10
install:
	for i in ${SUBDIR}; do \
D 3
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); done
E 3
I 3
		(echo $$i; cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); \
E 10
I 10
D 11
tags: FRC
	for i in eyacc ${SUBDIR}; do \
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} tags); \
E 10
	done
E 3

D 10
clean:
E 10
I 10
install: FRC
	for i in eyacc ${SUBDIR}; do \
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); \
	done

clean: FRC
E 10
	rm -f a.out core *.s *.o
D 3
	for i in ${SUBDIR}; do (echo $$i; cd $$i; make ${MFLAGS} clean); done
E 3
I 3
D 10
	for i in ${SUBDIR}; do \
		(echo $$i; cd $$i; make ${MFLAGS} clean); \
E 10
I 10
	for i in eyacc ${SUBDIR}; do \
		(cd $$i; make ${MFLAGS} clean); \
E 10
	done
I 7

E 11
depend:
I 10
	(cd eyacc; make ${MFLAGS} depend)
	(cd eyacc; make ${MFLAGS} all)
	for i in ${SUBDIR}; do \
D 11
		(cd $$i; make ${MFLAGS} depend); \
	done

FRC:
E 11
I 11
D 13
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} depend); done
E 13
I 13
		(echo "==> $$i"; \
		    cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} depend); done
E 14
I 14
.include <bsd.subdir.mk>
E 14
E 13
E 11
E 10
E 7
E 3
E 1
