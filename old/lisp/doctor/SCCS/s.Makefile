h44385
s 00001/00017/00022
d D 4.10 91/05/13 18:03:04 bostic 11 10
c new copyright; att/bsd/shared
e
s 00001/00001/00038
d D 4.9 89/05/11 13:48:38 bostic 10 9
c file reorg, pathnames.h, paths.h
e
s 00026/00010/00013
d D 4.8 88/10/19 20:32:33 bostic 9 8
c cleanup, add manual pages
e
s 00004/00001/00019
d D 4.7 87/09/19 17:05:21 bostic 8 7
c integrate with dm
e
s 00015/00007/00005
d D 4.6 87/06/03 18:32:26 bostic 7 5
c new template
e
s 00015/00007/00005
d R 4.6 87/06/03 18:31:52 bostic 6 5
c new template
e
s 00001/00001/00011
d D 4.5 85/10/25 17:20:20 mckusick 5 4
c cannot strip lisp
e
s 00001/00001/00011
d D 4.4 85/09/07 21:04:06 mckusick 4 3
c strip on install
e
s 00001/00001/00011
d D 4.3 85/06/25 21:01:18 bloom 3 2
c install should make sure doctor is up to date
e
s 00001/00003/00011
d D 4.2 83/07/26 12:02:39 layer 2 1
c simplified 'doctor' entry
e
s 00014/00000/00000
d D 4.1 82/11/22 17:16:47 mckusick 1 0
c date and time created 82/11/22 17:16:47 by mckusick
e
u
U
t
T
I 1
D 7
#	%W%	(Berkeley)	%E%
E 7
D 11
#
D 7
DESTDIR=
E 7
I 7
D 9
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 9
I 9
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 9
#
D 9
#	%W%	(Berkeley)	%G%
E 9
I 9
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
E 9
#
E 11
I 9
#	%W% (Berkeley) %G%
D 11
#
E 11
I 11

E 11
MAN=	doctor.0

E 9
all: doctor
E 7

D 7
doctor: /usr/ucb/lisp /usr/ucb/liszt
E 7
I 7
D 9
doctor: FRC
E 9
I 9
doctor:
E 9
E 7
D 2
	liszt -mrq doctor.l
	mv doctor.o doctor
	chmod 755 doctor
E 2
I 2
	liszt -mrq -o doctor doctor.l
E 2

D 3
install:
E 3
I 3
D 7
install: doctor
E 3
D 4
	install doctor $(DESTDIR)/usr/games
E 4
I 4
D 5
	install -s doctor $(DESTDIR)/usr/games
E 5
I 5
	install doctor $(DESTDIR)/usr/games
E 7
I 7
D 9
install: FRC
E 9
I 9
install: ${MAN}
E 9
D 8
	install -o bin -g bin -m 755 doctor ${DESTDIR}/usr/games/doctor
E 8
I 8
	install -o games -g bin -m 700 doctor ${DESTDIR}/usr/games/hide
	rm -f ${DESTDIR}/usr/games/doctor
	ln -s ${DESTDIR}/usr/games/dm ${DESTDIR}/usr/games/doctor
	chown games.bin ${DESTDIR}/usr/games/doctor
I 9
D 10
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/games/cat6
E 10
I 10
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
E 10
E 9
E 8
E 7
E 5
E 4

D 7
clean:
	rm -f doctor
E 7
I 7
D 9
clean: FRC
	rm -f doctor core
E 9
I 9
clean:
	rm -f doctor
E 9

D 9
depend: FRC
FRC:
E 9
I 9
cleandir: clean
	rm -f ${MAN}

depend lint tags:
E 9
E 7
E 1
