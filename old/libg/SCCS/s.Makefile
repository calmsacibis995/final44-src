h19543
s 00014/00015/00011
d D 5.2 89/05/10 22:40:29 bostic 2 1
c new template
e
s 00026/00000/00000
d D 5.1 87/12/12 17:33:06 bostic 1 0
c date and time created 87/12/12 17:33:06 by bostic
e
u
U
t
T
I 1
#
D 2
# Copyright (c) 1987 Regents of the University of California.
E 2
I 2
# Copyright (c) 1989 The Regents of the University of California.
E 2
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 2
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 2
#
#	%W% (Berkeley) %G%
#
all: FRC
D 2
	cd libg.${MACHINE}; make ${MFLAGS}
E 2
I 2
	cd libg.${MACHINE}; make ${MFLAGS} all
E 2

D 2
install: FRC
	cd libg.${MACHINE}; make DESTDIR=${DESTDIR} install

clean: FRC
	cd libg.${MACHINE}; make ${MFLAGS} clean

depend: FRC
	cd libg.${MACHINE}; make ${MFLAGS} depend
E 2
I 2
clean cleandir depend lint install tags: FRC
	cd libg.${MACHINE}; make DESTDIR=${DESTDIR} $@
E 2

FRC:
E 1
