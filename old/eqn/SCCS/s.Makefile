h24365
s 00002/00025/00003
d D 5.3 90/05/11 15:11:08 bostic 3 2
c first pass for new make
e
s 00020/00016/00008
d D 5.2 88/10/22 15:54:07 bostic 2 1
c cleanup, add new labels, checkeq
e
s 00024/00000/00000
d D 5.1 87/12/12 17:36:15 bostic 1 0
c date and time created 87/12/12 17:36:15 by bostic
e
u
U
t
T
I 1
D 3
#
D 2
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 2
I 2
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 2
#
D 2
#	%W%	(Berkeley)	%G%
E 2
I 2
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
D 2
SUBDIR=	eqn neqn
E 2
I 2
#	%W% (Berkeley) %G%
D 3
#
E 3
I 3

E 3
SUBDIR=	checkeq eqn neqn
E 2

D 2
all: FRC
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS}); done

install: FRC
E 2
I 2
D 3
all depend clean cleandir install lint tags: FRC
E 2
	for i in ${SUBDIR}; do \
D 2
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); \
	done
E 2
I 2
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done
E 2

D 2
clean: FRC
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} clean); done

depend: FRC
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} depend); done
E 2
I 2
${SUBDIR}: FRC
	cd $@; make ${MFLAGS} DESTDIR=${DESTDIR}
E 2

FRC:
E 3
I 3
.include <bsd.subdir.mk>
E 3
E 1
