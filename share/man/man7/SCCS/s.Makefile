h10449
s 00000/00000/00016
d D 8.1 93/06/05 13:54:30 bostic 10 8
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00015
d R 5.8 92/07/25 10:57:21 bostic 9 8
c me got dropped somehow
e
s 00001/00001/00015
d D 5.7 91/08/05 07:27:15 cael 8 6
c add mdoc.7
e
s 00002/00002/00014
d D 5.6.1.1 91/05/07 21:56:40 bostic 7 6
c branch for the 2nd network distribution
e
s 00001/00001/00015
d D 5.6 90/06/22 16:32:37 cael 6 5
c added mdoc.samples.7
e
s 00010/00025/00006
d D 5.5 90/05/11 13:56:19 bostic 5 4
c first pass for new make
e
s 00002/00002/00029
d D 5.4 90/05/10 16:31:55 bostic 4 3
c checkpoint for pmake
e
s 00008/00018/00023
d D 5.3 89/03/06 11:07:54 bostic 3 2
c move man pages into source tree
e
s 00010/00005/00031
d D 5.2 88/07/09 11:33:37 bostic 2 1
c install approved copyright notice
e
s 00036/00000/00000
d D 5.1 87/12/12 18:22:56 bostic 1 0
c date and time created 87/12/12 18:22:56 by bostic
e
u
U
f b 
t
T
I 1
D 5
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
E 5
#	%W% (Berkeley) %G%
D 5
#
D 3
MDIR=	/usr/man/cat7
SRCS=	ascii.7 environ.7 eqnchar.7 hier.7 hostname.7 intro.7 mailaddr.7 \
	man.7 me.7 ms.7 term.7
E 3
I 3
D 4
MDIR=	${DESTDIR}/usr/man/cat7
E 4
I 4
MDIR=	${DESTDIR}/usr/share/man/cat7
E 4
E 3
OBJS=	ascii.0 environ.0 eqnchar.0 hier.0 hostname.0 intro.0 mailaddr.0 \
E 5
I 5

D 7
MAN7=	ascii.0 environ.0 eqnchar.0 hier.0 hostname.0 intro.0 mailaddr.0 \
E 5
D 4
	man.0 me.0 ms.0 term.0
E 4
I 4
D 6
	man.0 ms.0 operator.0 term.0
E 6
I 6
D 8
	man.0 mdoc.samples.0 ms.0 operator.0 term.0
E 8
I 8
	man.0 mdoc.0 mdoc.samples.0 ms.0 operator.0 term.0
E 8
E 7
I 7
MAN7=	ascii.0 environ.0 hier.0 hostname.0 intro.0 mailaddr.0 \
	mdoc.samples.0 operator.0 term.0
E 7
E 6
I 5
MLINKS=	intro.7 miscellaneous.7
E 5
E 4
D 3
LINKS=	miscellaneous.0
E 3

D 3
.SUFFIXES: .7 .0
E 3
I 3
D 5
all clean depend lint tags:
E 5
I 5
all: ${MAN7}
E 5
E 3

I 5
clean depend lint tags:

E 5
D 3
.7.0:
	${DESTDIR}/usr/man/manroff $*.7 > $*.0

all: ${OBJS}

clean: FRC
E 3
I 3
cleandir:
E 3
D 5
	rm -f ${OBJS}
E 5
I 5
	rm -f ${MAN7}
E 5

D 3
install: FRC
	cd ${DESTDIR}${MDIR}; rm -f *.0
	install -c -o bin -g bin -m 444 ${OBJS} ${DESTDIR}${MDIR}
	ln ${DESTDIR}${MDIR}/intro.0 ${DESTDIR}${MDIR}/miscellaneous.0

FRC:
E 3
I 3
D 5
install: ${OBJS}
	install -c -o bin -g bin -m 444 ${OBJS} ${MDIR}
	rm -f ${MDIR}/miscellaneous.0; \
		ln ${MDIR}/intro.0 ${MDIR}/miscellaneous.0
E 5
I 5
install: maninstall

.include <bsd.prog.mk>
E 5
E 3
E 1
