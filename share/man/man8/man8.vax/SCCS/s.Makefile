h23271
s 00000/00000/00015
d D 8.1 93/06/05 13:57:30 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00014
d D 5.5 91/03/22 14:06:40 bostic 5 4
c add MAKEDEV
e
s 00010/00023/00005
d D 5.4 90/05/11 13:56:13 bostic 4 3
c first pass for new make
e
s 00007/00020/00021
d D 5.3 89/03/06 11:14:54 bostic 3 2
c move man pages into source tree
e
s 00010/00005/00031
d D 5.2 88/07/09 11:32:41 bostic 2 1
c install approved copyright notice
e
s 00036/00000/00000
d D 5.1 87/12/12 18:24:27 bostic 1 0
c date and time created 87/12/12 18:24:27 by bostic
e
u
U
t
T
I 1
D 4
#
# Copyright (c) 1987 Regents of the University of California.
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
D 3
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
E 2
#
E 4
#	%W% (Berkeley) %G%
D 4
#
D 3
MDIR=	/usr/man/cat8/vax
SRCS=	arff.8 bad144.8 crash.8 drtest.8 format.8 installboot.8 rxformat.8 \
	reboot.8
OBJS=	arff.0 bad144.0 crash.0 drtest.0 format.0 installboot.0 rxformat.0 \
	reboot.0
LINKS=	flcopy.0
E 3
I 3
MDIR=	${DESTDIR}/usr/man/cat8/vax
OBJS=	crash.0 drtest.0 format.0 installboot.0
E 4
E 3

D 3
.SUFFIXES: .8 .0
E 3
I 3
D 4
all clean depend lint tags:
E 4
I 4
D 5
MAN8=	crash.0 drtest.0 format.0 installboot.0
E 5
I 5
MAN8=	MAKEDEV.0 crash.0 drtest.0 format.0 installboot.0
E 5
MANSUBDIR=/vax
E 4
E 3

I 4
all: ${MAN8}

clean depend lint tags:

E 4
D 3
.8.0:
	${DESTDIR}/usr/man/manroff $*.8 > $*.0

all: ${OBJS}

clean: FRC
E 3
I 3
cleandir:
E 3
D 4
	rm -f ${OBJS}
E 4
I 4
	rm -f ${MAN8}
E 4

D 3
install: FRC
	cd ${DESTDIR}${MDIR}; rm -f *.0
	install -c -o bin -g bin -m 444 ${OBJS} ${DESTDIR}${MDIR}
	ln ${DESTDIR}${MDIR}/arff.0 ${DESTDIR}${MDIR}/flcopy.0

FRC:
E 3
I 3
D 4
install: ${OBJS}
	install -c -o bin -g bin -m 444 ${OBJS} ${MDIR}
E 4
I 4
install: maninstall

.include <bsd.prog.mk>
E 4
E 3
E 1
