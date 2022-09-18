h12806
s 00000/00017/00017
d D 5.7 91/05/13 18:07:47 bostic 7 6
c makefiles don't need copyrights
e
s 00010/00005/00024
d D 5.6 88/07/09 10:54:17 bostic 6 5
c install approved copyright notice
e
s 00000/00001/00029
d D 5.5 88/06/08 15:54:22 karels 5 4
c !@#$%! don't need to make in doc at all, just fix Makefile
e
s 00001/00001/00029
d D 5.4 88/06/08 11:49:58 karels 4 3
c don't need "make rall" (make install does it twice)
e
s 00001/00000/00029
d D 5.3 88/06/05 16:26:38 karels 3 2
c sigh, copy doc before attempting make
e
s 00007/00007/00022
d D 5.2 88/06/04 13:59:56 karels 2 1
c compress directory hierarchy
e
s 00029/00000/00000
d D 5.1 87/12/17 12:48:02 bostic 1 0
c date and time created 87/12/17 12:48:02 by bostic
e
u
U
t
T
I 1
D 7
#
D 2
# Copyright (c) 1987 Regents of the University of California.
E 2
I 2
# Copyright (c) 1987, 1988 Regents of the University of California.
E 2
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 6
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 6
#
E 7
#	%W% (Berkeley) %G%
D 7
#
E 7

all: FRC
I 3
D 4
	(cd doc; make ${MFLAGS} rall install)
E 4
I 4
D 5
	(cd doc; make ${MFLAGS} install)
E 5
E 4
E 3
D 2
	cd lisp; ./lispconf ${MACHINE}_4_3
	cd lisp; make DESTDIR=${DESTDIR} copylibrary
	cd lisp; make ${MFLAGS}
E 2
I 2
	./lispconf ${MACHINE}_4_3
	make -f Makefile ${MFLAGS} DESTDIR=${DESTDIR} copylibrary
	make -f Makefile ${MFLAGS}
E 2

install: FRC
D 2
	cd lisp; make DESTDIR=${DESTDIR} install
E 2
I 2
	make -f Makefile ${MFLAGS} DESTDIR=${DESTDIR} install
E 2

clean: FRC
D 2
	cd lisp; make ${MFLAGS} clean
E 2
I 2
	make -f Makefile ${MFLAGS} clean
E 2

depend: FRC
D 2
	cd lisp; make ${MFLAGS} depend
E 2
I 2
	make -f Makefile ${MFLAGS} depend
E 2

FRC:
E 1
