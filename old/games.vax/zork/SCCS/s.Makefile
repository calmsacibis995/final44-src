h37904
s 00029/00021/00023
d D 4.4 88/10/20 11:51:04 bostic 4 3
c cleanup, add manual page
e
s 00035/00034/00009
d D 4.3 87/06/03 17:41:40 bostic 3 2
c new template
e
s 00001/00001/00042
d D 4.2 85/09/07 21:11:02 mckusick 2 1
c strip on install
e
s 00043/00000/00000
d D 4.1 82/11/28 18:47:13 mckusick 1 0
c date and time created 82/11/28 18:47:13 by mckusick
e
u
U
t
T
I 3
#
D 4
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 4
#
E 3
I 1
D 4
#	%W%	(Berkeley)	%G%
E 4
I 4
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
E 4
#
I 4
#	%W% (Berkeley) %G%
#
E 4
D 3
DESTDIR=
E 3
CFLAGS=	-O
I 3
LIBC=	/lib/libc.a
SRCS=	zork.c
D 4
OBJS=	zork.o
E 4
I 4
OBJS=
MAN=	zork.0
E 4
E 3

D 3
zork: zork.c
	cc ${CFLAGS} -o zork zork.c
E 3
I 3
all: zork
E 3

D 3
install:
D 2
	install zork ${DESTDIR}/usr/games/zork
E 2
I 2
	install -s zork ${DESTDIR}/usr/games/zork
E 2
	cp zorklib/dtext.dat ${DESTDIR}/usr/games/lib
	cp zorklib/dindex.dat ${DESTDIR}/usr/games/lib
	cp zorklib/doverlay ${DESTDIR}/usr/games/lib
	cp zorklib/dungeon ${DESTDIR}/usr/games/lib
E 3
I 3
D 4
zork: zork.c ${LIBC}
	${CC} ${CFLAGS} -o $@ zork.c
E 4
I 4
zork: ${LIBC}
	${CC} ${CFLAGS} -o $@ $@.c
E 4
E 3

D 3
clean:
	rm -f a.out core *.s *.o zork
E 3
I 3
D 4
clean: FRC
E 4
I 4
clean:
E 4
	rm -f ${OBJS} core zork
E 3

D 3
depend:
	cat </dev/null >x.c
	for i in zork; do \
		(echo $$i: $$i.c >>makedep; \
		/bin/grep '^#[ 	]*include' x.c $$i.c | sed \
			-e 's,<\(.*\)>,"/usr/include/\1",' \
			-e 's/:[^"]*"\([^"]*\)".*/: \1/' \
			-e 's/\.c//' >>makedep); done
	echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	cp Makefile Makefile.bak
	ed - Makefile < eddep
	rm eddep makedep x.c
	echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	echo '# see make depend above' >> Makefile
E 3
I 3
D 4
depend: FRC
E 4
I 4
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 4
	mkdep ${CFLAGS} ${SRCS}
E 3

D 3
# DO NOT DELETE THIS LINE -- make depend uses it
E 3
I 3
D 4
install: FRC
E 4
I 4
install: ${MAN}
	-[ -d ${DESTDIR}/usr/games/lib/zorklib ] || mkdir ${DESTDIR}/usr/games/lib/zorklib
E 4
	install -s -o bin -g bin -m 755 zork ${DESTDIR}/usr/games/zork
	install -c -o bin -g bin -m 755 zorklib/dtext.dat ${DESTDIR}/usr/games/lib
	install -c -o bin -g bin -m 755 zorklib/dindex.dat ${DESTDIR}/usr/games/lib
	install -c -o bin -g bin -m 755 zorklib/doverlay ${DESTDIR}/usr/games/lib
	install -c -o bin -g bin -m 755 zorklib/dungeon ${DESTDIR}/usr/games/lib
I 4
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
E 4
E 3

D 3
zork: zork.c
zork: /usr/include/stdio.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
E 3
I 3
D 4
lint: FRC
E 4
I 4
lint: ${SRCS}
E 4
	lint ${CFLAGS} ${SRCS}

D 4
tags: FRC
E 4
I 4
tags: ${SRCS}
E 4
	ctags ${SRCS}
D 4

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

zork.o: zork.c /usr/include/stdio.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 3
E 1
