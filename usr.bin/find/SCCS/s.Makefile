h18592
s 00000/00000/00006
d D 8.1 93/06/06 14:39:33 bostic 15 14
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00002/00006
d D 5.4 93/04/27 18:16:45 bostic 14 13
c pwcache(3) now in the C library
e
s 00000/00000/00008
d D 5.3 91/08/19 11:19:46 elan 13 12
c 
e
s 00001/00002/00007
d D 5.2 91/05/24 15:17:05 bostic 12 11
c return to the original find syntax (newsyntax.c -> main.c, delete
c oldsyntax.c; create extern.h for ANSI prototypes; create true error routine;
c make NEW macro a real routine
e
s 00006/00044/00003
d D 5.1 90/05/11 14:22:29 bostic 11 10
c first pass for new make
e
s 00005/00014/00042
d D 4.9 90/03/06 11:06:48 bostic 10 9
c pull out fast database code, rename as list
e
s 00004/00003/00052
d D 4.8 89/08/28 09:24:14 karels 9 8
c prepend "find." to names in /usr/libexec
e
s 00004/00005/00051
d D 4.7 89/05/11 13:33:08 bostic 8 7
c file reorg, pathnames.h, paths.h
e
s 00027/00032/00029
d D 4.6 88/10/22 16:39:38 bostic 7 6
c cleanup, add manual page
e
s 00001/00001/00060
d D 4.5 87/10/07 09:31:02 bostic 6 5
c fix mkdir line
e
s 00046/00054/00015
d D 4.4 87/06/19 07:13:48 bostic 5 3
c new template
e
s 00047/00054/00015
d R 4.4 87/06/18 17:49:47 bostic 4 3
c new template
e
s 00003/00003/00066
d D 4.3 85/06/01 14:00:02 edward 3 2
c install with -s
e
s 00003/00001/00066
d D 4.2 83/07/21 00:33:16 mckusick 2 1
c minor name changes
e
s 00067/00000/00000
d D 4.1 83/07/21 00:14:42 mckusick 1 0
c date and time created 83/07/21 00:14:42 by mckusick
e
u
U
t
T
I 1
D 5
#	%W%	(Berkeley)	%E%
E 5
D 11
#
D 5
DESTDIR=
CFLAGS=	-O
LFLAGS=	

# The programs themselves
E 5
I 5
D 7
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 7
I 7
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 7
E 5
#
D 5
PROG=	find
LIBS=	bigram code

# Sources
E 5
I 5
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
E 5
#
E 11
I 7
#	%W% (Berkeley) %G%
D 11
#
E 7
I 5
CFLAGS=	-O
D 9
LIBC=	/lib/libc.a
E 9
I 9
LIBC=	/usr/lib/libc.a
E 9
E 5
D 10
SRCS=	find.c bigram.c code.c
I 5
OBJS=	find.o bigram.o code.o
E 10
I 10
SRCS=	find.c
OBJS=
E 10
I 7
MAN=	find.0
E 11
E 7
E 5

I 2
D 5
all: ${PROG} ${LIBS}
E 5
I 5
D 10
all: find bigram code
E 10
I 10
D 11
all: find
E 11
I 11
PROG=	find
D 12
SRCS=	find.c function.c ls.c misc.c newsyntax.c oldsyntax.c operator.c \
	option.c
E 12
I 12
SRCS=	find.c function.c ls.c main.c misc.c operator.c option.c
E 12
D 14
DPADD=	${LIBUTIL}
LDADD=	-lutil
E 14
E 11
E 10
E 5

E 2
D 5
find: find.c
	cc ${CFLAGS} -o find find.c
E 5
I 5
D 7
find: find.c ${LIBC}
	${CC} ${CFLAGS} -o $@ find.c
E 7
I 7
D 10
bigram code find: ${LIBC}
E 10
I 10
D 11
find: ${LIBC}
E 10
	${CC} ${CFLAGS} -o $@ $@.c
E 7
E 5

D 7
bigram: bigram.c
D 5
	cc ${CFLAGS} -o bigram bigram.c
E 5
I 5
	${CC} ${CFLAGS} -o $@ bigram.c
E 5

code: code.c
D 5
	cc ${CFLAGS} -o code code.c
E 5
I 5
	${CC} ${CFLAGS} -o $@ code.c
E 5

D 5
install: ${PROG} ${LIBS}
D 3
	install ${PROG} ${DESTDIR}/usr/bin/${PROG}
E 3
I 3
	install -s ${PROG} ${DESTDIR}/usr/bin/${PROG}
E 3
	-mkdir ${DESTDIR}/usr/lib/find
D 3
	install bigram ${DESTDIR}/usr/lib/find/bigram
	install code ${DESTDIR}/usr/lib/find/code
E 3
I 3
	install -s bigram ${DESTDIR}/usr/lib/find/bigram
	install -s code ${DESTDIR}/usr/lib/find/code
E 3
D 2
	install -c -m 755 squeeze.csh ${DESTDIR}/usr/lib/find/squeeze.csh
E 2
I 2
	install -c -m 755 updatedb.csh ${DESTDIR}/usr/lib/find/updatedb
E 5
I 5
clean: FRC
E 7
I 7
clean:
E 7
D 10
	rm -f ${OBJS} core find bigram code
E 10
I 10
	rm -f ${OBJS} core find
E 10
E 5
E 2

D 5
clean:
	rm -f a.out core ${LIBS} ${PROG}
E 5
I 5
D 7
depend: FRC
E 7
I 7
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 7
	mkdep -p ${CFLAGS} ${SRCS}
E 5

D 5
depend:
	cat </dev/null >x.c
	for i in ${SRCS}; do \
		(echo `basename $$i .c`.o: $$i >>makedep; \
		/bin/grep '^#[ 	]*include' x.c $$i | sed \
			-e 's,<\(.*\)>,"/usr/include/\1",' \
			-e 's/:[^"]*"\([^"]*\)".*/: \1/' \
			-e 's/\.c/.o/' >>makedep); done
	echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	cp Makefile Makefile.bak
	ed - Makefile < eddep
	rm eddep makedep x.c
	echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	echo '# see make depend above' >> Makefile
E 5
I 5
D 7
install: FRC
E 7
I 7
install: ${MAN}
E 7
D 8
	install -s -o bin -g bin -m 755 find ${DESTDIR}/usr/bin/find
D 6
	-mkdir ${DESTDIR}/usr/lib/find > /dev/null 2>&1
E 6
I 6
	-[ -d ${DESTDIR}/usr/lib/find ] || mkdir ${DESTDIR}/usr/lib/find
E 6
	install -s -o bin -g bin -m 755 bigram ${DESTDIR}/usr/lib/find/bigram
	install -s -o bin -g bin -m 755 code ${DESTDIR}/usr/lib/find/code
	install -c -o bin -g bin -m 755 updatedb.csh ${DESTDIR}/usr/lib/find/updatedb
E 8
I 8
	install -s -o bin -g bin -m 755 find ${DESTDIR}/usr/bin
D 9
	install -s -o bin -g bin -m 755 code bigram ${DESTDIR}/usr/libexec
E 9
I 9
D 10
	install -s -o bin -g bin -m 755 code ${DESTDIR}/usr/libexec/find.code
	install -s -o bin -g bin -m 755 bigram ${DESTDIR}/usr/libexec/find.bigram
E 9
	install -c -o bin -g bin -m 755 updatedb.csh \
D 9
	    ${DESTDIR}/usr/libexec/updatedb
E 9
I 9
	    ${DESTDIR}/usr/libexec/find.updatedb
E 10
E 9
E 8
I 7
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 7
E 5

D 5
# DO NOT DELETE THIS LINE -- make depend uses it
E 5
I 5
D 7
lint: FRC
E 7
I 7
lint: ${SRCS}
E 7
	lint ${CFLAGS} find.c
D 10
	lint ${CFLAGS} bigram.c
	lint ${CFLAGS} code.c
E 10
E 5

D 5
find.o: find.c
find.o: /usr/include/stdio.h
find.o: /usr/include/sys/param.h
find.o: /usr/include/sys/dir.h
find.o: /usr/include/sys/stat.h
find.o: /usr/include/signal.h
bigram.o: bigram.c
bigram.o: /usr/include/stdio.h
code.o: code.c
code.o: /usr/include/stdio.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
E 5
I 5
D 7
tags: FRC
E 7
I 7
tags: ${SRCS}
E 7
	ctags find.c
E 11
I 11
.include <bsd.prog.mk>
E 11
D 10
	ctags -a bigram.c
	ctags -a code.c
	sort -o tags tags
E 10
D 7

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

find: find.c /usr/include/stdio.h /usr/include/sys/param.h
find: /usr/include/sys/types.h /usr/include/signal.h
find: /usr/include/machine/machparam.h /usr/include/sys/dir.h
find: /usr/include/sys/stat.h /usr/include/pwd.h /usr/include/grp.h
find: /usr/include/utmp.h
bigram: bigram.c /usr/include/stdio.h
code: code.c /usr/include/stdio.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 7
E 5
E 1
