h23674
s 00021/00011/00016
d D 5.6 88/10/19 16:11:09 bostic 7 6
c add manual page, cleanup
e
s 00001/00001/00026
d D 5.5 87/12/20 13:14:08 bostic 6 5
c don't fail on ddlcomp return
e
s 00005/00002/00022
d D 5.4 87/12/12 17:19:38 bostic 5 4
c integrate with dm
e
s 00015/00009/00009
d D 5.3 87/06/03 17:30:32 bostic 4 3
c new template
e
s 00001/00001/00017
d D 5.2 86/02/01 16:21:14 mckusick 3 2
c clean up spurious aard's
e
s 00006/00001/00012
d D 5.1 85/05/29 11:28:04 dist 2 1
c Add copyright
e
s 00013/00000/00000
d D 4.1 83/08/13 16:28:17 sam 1 0
c date and time created 83/08/13 16:28:17 by sam
e
u
U
t
T
I 1
D 2
#	%M%	%I%	%E%
E 2
I 2
#
D 4
# Copyright (c) 1980 Regents of the University of California.
E 4
I 4
D 7
# Copyright (c) 1987 Regents of the University of California.
E 4
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 7
I 7
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 7
#
D 4
#	%W% (Berkeley) %G%
E 4
I 4
D 7
#	%W%	(Berkeley)	%G%
E 7
I 7
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
E 7
E 4
E 2
#
I 7
#	%W% (Berkeley) %G%
#
MAN=	aardvark.0
E 7
D 4
DESTDIR=
E 4

D 4
aard:
E 4
I 4
all: aard

D 7
aard: FRC
E 7
I 7
aard:
E 7
E 4
D 6
	../ddl/ddlcomp aard < aard.ddl > ddlcomp.out
E 6
I 6
	-../ddl/ddlcomp aard < aard.ddl > ddlcomp.out
E 6

D 4
install:
	install aard ${DESTDIR}/usr/games/lib/aard
	install -c -m 755 frontend ${DESTDIR}/usr/games/aardvark

clean:
E 4
I 4
D 7
clean: FRC
E 7
I 7
cleandir clean:
E 7
E 4
D 3
	rm -f ddlcomp.out
E 3
I 3
	rm -f ddlcomp.out aard
I 4

D 7
install: FRC
E 7
I 7
install: ${MAN}
E 7
D 5
	install -o bin -g bin -m 755 aard ${DESTDIR}/usr/games/lib/aard
	install -c -o bin -g bin -m 755 frontend ${DESTDIR}/usr/games/aardvark
E 5
I 5
	install -o games -g bin -m 755 aard ${DESTDIR}/usr/games/lib/aard
	install -c -o games -g bin -m 755 frontend ${DESTDIR}/usr/games/hide/aardvark
	rm -f ${DESTDIR}/usr/games/aardvark
	ln -s ${DESTDIR}/usr/games/dm ${DESTDIR}/usr/games/aardvark
	chown games.bin ${DESTDIR}/usr/games/aardvark
I 7
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6/vax
E 7
E 5

D 7
depend:
lint:
tags:
FRC:
E 7
I 7
depend lint tags:
E 7
E 4
E 3
E 1
