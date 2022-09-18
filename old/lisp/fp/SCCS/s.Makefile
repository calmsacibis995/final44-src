h02080
s 00001/00017/00015
d D 5.6 91/05/13 18:04:30 bostic 6 5
c makefiles don't need copyrights
e
s 00001/00001/00031
d D 5.5 89/03/06 11:52:39 bostic 5 4
c add cleandir
e
s 00005/00001/00027
d D 5.4 88/10/25 16:12:24 bostic 4 3
c add cleandir
e
s 00007/00001/00021
d D 5.3 88/10/25 16:11:08 bostic 3 2
c cleanup, install man page
e
s 00013/00018/00009
d D 5.2 88/10/21 15:50:12 bostic 2 1
c cleanup
e
s 00027/00000/00000
d D 5.1 87/12/23 13:59:14 bostic 1 0
c date and time created 87/12/23 13:59:14 by bostic
e
u
U
t
T
I 1
D 6
#
D 2
# Copyright (c) 1987 Regents of the University of California.
E 2
I 2
# Copyright (c) 1987 The Regents of the University of California.
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
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
#
E 6
#	%W% (Berkeley) %G%
D 6
#
E 6
I 6

E 6
D 2
all: FRC
	cd fp.${MACHINE}; make ${MFLAGS}
E 2
I 2
D 3
all fp clean cleandir install lint tags: FRC
E 3
I 3
MAN=	fp.0

D 4
all fp clean cleandir lint tags: FRC
E 4
I 4
D 5
all fp clean lint tags: FRC
E 5
I 5
all clean depend lint tags: FRC
E 5
E 4
E 3
	cd fp.${MACHINE}; make ${MFLAGS} DESTDIR=${DESTDIR} $@
I 4

cleandir: clean
	cd fp.${MACHINE}; make ${MFLAGS} DESTDIR=${DESTDIR} $@
	rm -f ${MAN} tags .depend
E 4
I 3

install: ${MAN}
	cd fp.${MACHINE}; make ${MFLAGS} DESTDIR=${DESTDIR} $@
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 3
E 2

D 2
install: FRC
	cd fp.${MACHINE}; make DESTDIR=${DESTDIR} install

clean: FRC
	cd fp.${MACHINE}; make ${MFLAGS} clean

depend: FRC
	cd fp.${MACHINE}; make ${MFLAGS} depend

E 2
FRC:
D 2

E 2
E 1
