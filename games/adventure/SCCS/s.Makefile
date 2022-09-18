h35938
s 00000/00000/00016
d D 8.1 93/06/12 16:30:57 bostic 20 19
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00015
d D 5.2 93/06/12 16:30:46 bostic 19 17
c remove data.c on clean
e
s 00000/00000/00016
d R 8.1 93/05/31 15:54:35 bostic 18 17
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00011/00009
d D 5.1 93/05/12 14:04:00 bostic 17 16
c new version of adventure from Jim Gillogly (jim@rand.org)
e
s 00014/00048/00006
d D 4.12 90/05/11 12:47:27 bostic 16 15
c first pass for new make
e
s 00001/00001/00053
d D 4.11 89/07/30 12:20:23 bostic 15 14
c needs libcompat
e
s 00002/00000/00052
d D 4.10 89/03/05 20:42:41 bostic 14 13
c add all label
e
s 00007/00006/00045
d D 4.9 89/03/05 20:21:39 bostic 13 12
c cleanup, some machinations no longer needed
e
s 00025/00025/00026
d D 4.8 88/10/19 16:15:07 bostic 12 11
c add manual page, Berkeley specific copyright
e
s 00012/00039/00039
d D 4.7 87/09/21 12:00:30 bostic 11 7
c integrate with dm
e
s 00014/00039/00039
d R 4.7 87/09/19 17:37:21 bostic 10 7
c integrate with dm; some general cleanup
e
s 00004/00001/00077
d R 4.7 87/09/19 17:01:30 bostic 9 7
c integrate with dm
e
s 00003/00001/00077
d R 4.7 87/09/19 13:10:29 bostic 8 7
c integrate with dm
e
s 00002/00006/00076
d D 4.6 87/07/27 16:06:13 bostic 7 6
c fix new template
e
s 00056/00028/00026
d D 4.5 87/06/05 13:41:21 bostic 6 5
c new template
e
s 00002/00000/00052
d D 4.4 87/05/31 20:57:31 bostic 5 4
c added depend label
e
s 00001/00001/00051
d D 4.3 85/09/07 21:02:27 mckusick 4 3
c strip on install
e
s 00009/00001/00043
d D 4.2 82/10/24 19:33:32 mckusick 3 2
c add DESTDIR
e
s 00000/00000/00044
d D 4.1 82/05/11 14:41:06 rrh 2 1
c release version 4.1
e
s 00044/00000/00000
d D 1.1 82/05/11 14:35:36 rrh 1 0
c date and time created 82/05/11 14:35:36 by rrh
e
u
U
t
T
I 1
D 6
#	%M%	%I%	%E%

I 3
DESTDIR=
E 3
CFILES=	done.c init.c io.c main.c save.c subr.c vocab.c wizard.c
OBJS=	done.o init.o io.o main.o save.o subr.o vocab.o wizard.o
I 3
HFILES = hdr.h
SRCS = $(CFILES) $(HFILES) glorkz
E 6
I 6
D 16
#
D 12
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 12
I 12
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 12
#
D 12
#	%W%	(Berkeley)	%G%
E 12
I 12
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
E 12
#
E 16
I 12
#	%W% (Berkeley) %G%
D 16
#
E 12
E 6
E 3
CFLAGS=	-O
D 6
LDFLAGS=-n	# should be -i on small machines, -n on a vax
E 6
I 6
LIBC=	/lib/libc.a
E 16
I 16

PROG=	adventure
I 17
SRCS=	main.c init.c done.c save.c subr.c vocab.c wizard.c io.c data.c crc.c
E 17
MAN6=	adventure.0
E 16
D 7
LFLGS=	-n		# should be -i on small machines, -n on a vax
E 7
D 17
SRCS=	done.c init.c io.c main.c save.c subr.c vocab.c wizard.c
D 16
OBJS=	done.o init.o io.o main.o save.o subr.o vocab.o wizard.o
I 12
MAN=	adventure.0
E 16
I 16
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
.PATH:	${.CURDIR}
E 17
I 17
CFLAGS+=-traditional-cpp
E 17
HIDEGAME=hidegame
I 17
D 19
CLEANFILES+=setup
E 19
I 19
CLEANFILES+=setup data.c
E 19
E 17
E 16
E 12
E 6

I 14
D 16
all: adventure

E 14
D 6
advent:	a.out
E 6
I 6
D 11
all: advent

advent: a.out
E 6
	rm -f advent
E 11
I 11
D 13
advent: ${OBJS} ${LIBC}
E 13
I 13
adventure: ${OBJS} ${LIBC}
E 13
D 15
	${CC} -n ${CFLAGS} ${OBJS}
E 15
I 15
	${CC} -n ${CFLAGS} ${OBJS} -lcompat
E 15
D 13
	rm -f $@
E 11
	echo y | ./a.out
E 13
I 13
	./a.out
E 13

E 16
D 6
a.out: ${OBJS}
E 6
I 6
D 11
a.out: ${OBJS} ${LIBC}
E 6
D 7
	${CC} ${LDFLAGS} ${CFLAGS} ${OBJS}
E 7
I 7
	${CC} -n ${CFLAGS} ${OBJS}
E 7

E 11
D 6
save.o:	save.c	# vax C optimizer bug - infinite loop
	cc -c save.c
E 6
I 6
D 7
PROG:	${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 6

E 7
I 6
D 17
save.o: save.c			# vax C optimizer bug - infinite loop
D 16
	${CC} -c save.c
E 16
I 16
	${CC} -c ${.CURDIR}/save.c
E 17
I 17
data.c: glorkz setup
	./setup ${.CURDIR}/glorkz > data.c
E 17
E 16

E 6
D 7
# always recomple okplay
E 7
I 7
D 11
# always recompile okplay
E 7
D 6
okplay.o: /tmp
E 6
I 6
okplay.o: FRC
E 6

D 6
install: advent
D 3
	cp advent /usr/games/adventure
E 3
I 3
D 4
	install advent ${DESTDIR}/usr/games/adventure
E 4
I 4
	install -s advent ${DESTDIR}/usr/games/adventure
E 6
I 6
advsaver: advsaver.s
	${AS} -o $@ advsaver.s

E 11
D 12
clean: FRC
E 12
I 12
D 16
clean:
E 12
D 13
	rm -f ${OBJS} core advent a.out
E 13
I 13
	rm -f ${OBJS} core adventure a.out
E 16
I 16
D 17
beforeinstall:
	cp ${.CURDIR}/glorkz .
	mv adventure adventure.out
	./adventure.out
	rm -f adventure.out
E 17
I 17
setup: setup.c hdr.h
	${CC} -o setup ${.CURDIR}/setup.c
E 17
E 16
E 13

D 12
depend: FRC
E 12
I 12
D 16
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 12
	mkdep ${CFLAGS} ${SRCS}

D 12
install: FRC
E 12
I 12
install: ${MAN}
E 12
D 11
	install -o bin -g bin -m 755 -s advent ${DESTDIR}/usr/games/adventure
E 6
E 4
E 3
#	cp okplay /usr/games/adventure
#	cp advsaver /usr/games/lib
#	dd if=/usr/games/lib/adventure of=/usr/games/lib/advheader bs=1 count=16
#	chmod 711 /usr/games/lib
#	chmod 700 /usr/games/lib/adventure
#	chmod 755 /usr/games/lib/advheader
#	chmod 755 /usr/games/lib/advsaver
#	chmod 4711 /usr/games/adventure
#	chown games /usr/games/adventure /usr/games/lib/adventure /usr/games/lib/advheader /usr/games/lib/advsaver
#	rm advent a.out okplay 
E 11
I 11
D 13
	install -s -o games -g bin -m 700 advent ${DESTDIR}/usr/games/hide/adventure
	(cd ${DESTDIR}/usr/games; rm -f adventure; ln -s dm adventure; chown games.bin adventure)
E 13
I 13
	install -s -o games -g bin -m 4700 adventure \
		${DESTDIR}/usr/games/hide/adventure
	(cd ${DESTDIR}/usr/games; rm -f adventure; ln -s dm adventure; \
		chown games.bin adventure)
E 13
I 12
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
E 12
E 11

D 6
okplay: okplay.c
	${CC} ${CFLAGS} -o okplay okplay.c
E 6
I 6
D 12
lint: FRC
E 12
I 12
lint: ${SRCS}
E 12
	lint ${CFLAGS} ${SRCS}
E 6

D 6
advsaver: advsaver.s
	${AS} -o advsaver advsaver.s
E 6
I 6
D 12
tags: FRC
E 12
I 12
tags: ${SRCS}
E 12
	ctags ${SRCS}
E 16
I 16
.include <bsd.prog.mk>
E 16
E 6
D 12

D 6
lint:
	lint $(CFILES) >& lint.out
E 6
I 6
FRC:
E 6

I 5
D 6
depend:
E 6
I 6
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 6

E 5
D 6
clean:
	rm -f ${OBJS} a.out advent core errs
E 6
I 6
D 11
done.o: done.c
done.o:hdr.h
init.o: init.c
init.o:hdr.h
io.o: io.c
io.o:hdr.h
io.o: /usr/include/stdio.h
main.o: main.c
main.o:hdr.h
E 11
I 11
done.o: done.c hdr.h
init.o: init.c hdr.h
io.o: io.c hdr.h /usr/include/stdio.h
main.o: main.c hdr.h
E 11
save.o: save.c /usr/include/a.out.h /usr/include/sys/exec.h
D 11
subr.o: subr.c
subr.o:hdr.h
vocab.o: vocab.c
vocab.o:hdr.h
wizard.o: wizard.c
wizard.o:hdr.h
E 11
I 11
subr.o: subr.c hdr.h
vocab.o: vocab.c hdr.h
wizard.o: wizard.c hdr.h
E 11
E 6
I 3

D 6
sources: $(SRCS)

$(SRCS):
	sccs get $@
E 6
I 6
# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 12
E 6
E 3
E 1
