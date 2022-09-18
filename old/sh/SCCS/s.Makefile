h51162
s 00001/00001/00012
d D 4.14 91/06/17 12:41:45 bostic 14 13
c move cd.1 and wait.1 into share/man/man1
e
s 00001/00001/00012
d D 4.13 91/04/30 17:48:50 bostic 13 12
c intro shouldn't have been moved into sh
e
s 00008/00055/00005
d D 4.12 90/05/11 12:42:24 bostic 12 11
c first pass for new make
e
s 00001/00001/00059
d D 4.11 89/07/30 12:19:51 bostic 11 10
c needs libcompat
e
s 00001/00001/00059
d D 4.10 89/04/03 20:45:31 bostic 10 9
c add other man pages
e
s 00008/00000/00052
d D 4.9 88/10/25 18:37:17 bostic 9 8
c add links to manual page
e
s 00027/00062/00025
d D 4.8 88/10/22 14:07:31 bostic 8 7
c cleanup, add manual page
e
s 00079/00027/00008
d D 4.7 87/06/02 23:57:41 bostic 7 6
c new template
e
s 00002/00000/00033
d D 4.6 87/05/31 20:33:52 bostic 6 5
c added depend label
e
s 00001/00001/00032
d D 4.5 83/07/01 03:48:52 sam 5 4
c purge -n
e
s 00007/00009/00026
d D 4.4 83/02/09 14:29:08 sam 4 3
c stuff from sun
e
s 00001/00001/00034
d D 4.3 82/10/23 20:35:37 mckusick 3 2
c no -n to CFLAGS
e
s 00001/00001/00034
d D 4.2 82/06/03 23:41:34 mckusick 2 1
c get rid of -g flag
e
s 00035/00000/00000
d D 4.1 82/05/07 19:36:11 mckusick 1 0
c date and time created 82/05/07 19:36:11 by mckusick
e
u
U
t
T
I 1
D 7
#	%M%	%I%	%E%
E 7
D 12
#
D 2
CFLAGS = -n -O -g
E 2
I 2
D 3
CFLAGS = -n -O
E 3
I 3
D 4
CFLAGS = -O
E 4
I 4
D 7
CFLAGS = -O -w
E 7
I 7
D 8
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 8
I 8
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 8
#
D 8
#	%W%	(Berkeley)	%G%
E 8
I 8
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
E 8
#
E 12
I 8
#	%W% (Berkeley) %G%
D 12
#
#
E 8
CFLAGS=	-O -w
LIBC=	/lib/libc.a
E 12
I 12

PROG=	sh
CFLAGS+=-w
E 12
SRCS=	setbrk.c builtin.c blok.c stak.c cmd.c fault.c main.c word.c \
	string.c name.c args.c xec.c service.c error.c io.c print.c \
	macro.c expand.c ctype.c msg.c
D 12
OBJS=	setbrk.o builtin.o blok.o stak.o cmd.o fault.o main.o word.o \
	string.o name.o args.o xec.o service.o error.o io.o print.o \
	macro.o expand.o ctype.o msg.o
I 8
D 10
MAN=	sh.0
E 10
I 10
MAN=	cd.0 intro.0 sh.0 wait.0
E 12
I 12
D 13
MAN1=	cd.0 intro.0 sh.0 wait.0
E 13
I 13
D 14
MAN1=	cd.0 sh.0 wait.0
E 14
I 14
MAN1=	sh.0
E 14
E 13
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
MLINKS=	sh.1 case.1 sh.1 for.1 sh.1 if.1 sh.1 while.1
E 12
E 10
E 8
E 7
E 4
E 3
E 2

D 7
all:	sh
E 7
I 7
D 12
all: sh
E 7

D 7
cp:	sh
	cp sh /bin/sh
	rm sh *.o
E 7
I 7
D 8
sh:	${OBJS} ${LIBC}
E 8
I 8
sh: ${OBJS} ${LIBC}
E 8
D 11
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 11
I 11
	${CC} -o $@ ${CFLAGS} ${OBJS} -lcompat
E 11
E 7

D 7
cmp:	sh
	cmp sh /bin/sh
	rm sh *.o
E 7
I 7
D 8
clean: FRC
E 8
I 8
clean:
E 8
	rm -f ${OBJS} core sh
E 7

D 7
sh:	setbrk.o
sh:	builtin.o blok.o stak.o
sh:	cmd.o fault.o main.o
sh:	word.o string.o name.o args.o
sh:	xec.o service.o error.o io.o
sh:	print.o macro.o expand.o
sh:	ctype.o msg.o
blok.o:		brkincr.h
fault.o:	brkincr.h
main.o:		brkincr.h
stak.o:		brkincr.h
E 7
I 7
D 8
depend: FRC
E 8
I 8
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 8
	mkdep ${CFLAGS} ${SRCS}
E 7

D 4
sh:;		cc -o sh -n *.o
E 4
I 4
D 7
sh:
D 5
	cc -o sh -n *.o
E 5
I 5
	cc -o sh *.o
E 7
I 7
D 8
install: FRC
E 8
I 8
install: ${MAN}
E 8
	install -s -o bin -g bin -m 755 sh ${DESTDIR}/bin/sh
I 8
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
I 9
	rm -f ${DESTDIR}/usr/man/cat1/case.0
	rm -f ${DESTDIR}/usr/man/cat1/for.0
	rm -f ${DESTDIR}/usr/man/cat1/if.0
	rm -f ${DESTDIR}/usr/man/cat1/while.0
	ln ${DESTDIR}/usr/man/cat1/sh.0 ${DESTDIR}/usr/man/cat1/case.0
	ln ${DESTDIR}/usr/man/cat1/sh.0 ${DESTDIR}/usr/man/cat1/for.0
	ln ${DESTDIR}/usr/man/cat1/sh.0 ${DESTDIR}/usr/man/cat1/if.0
	ln ${DESTDIR}/usr/man/cat1/sh.0 ${DESTDIR}/usr/man/cat1/while.0
E 9
E 8
E 7
E 5
E 4

I 6
D 7
depend:
E 7
I 7
D 8
lint: FRC
E 8
I 8
lint: ${SRCS}
E 8
	lint ${CFLAGS} ${SRCS}
E 7

E 6
D 4
newsys:;	:newsys file=msg; make sh
install:;	install -s sh $(DESTDIR)/bin
clean:; rm -f sh *.o
diff:;		:diff
list:;		list Makefile *.h *.s *.c

.c.o:;	cc -O  -c $<
E 4
I 4
D 7
install:
	install -s sh $(DESTDIR)/bin
clean:
	rm -f sh *.o
E 7
I 7
D 8
tags: FRC
E 8
I 8
tags: ${SRCS}
E 8
	ctags ${SRCS}
E 12
I 12
.include <bsd.prog.mk>
E 12
D 8

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

setbrk.o: setbrk.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
setbrk.o: brkincr.h ctype.h
builtin.o: builtin.c
blok.o: blok.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
blok.o: brkincr.h ctype.h
stak.o: stak.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
stak.o: brkincr.h ctype.h
cmd.o: cmd.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h brkincr.h
cmd.o: ctype.h sym.h
fault.o: fault.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
fault.o: brkincr.h ctype.h
main.o: main.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
main.o: brkincr.h ctype.h sym.h timeout.h /usr/include/sys/types.h
main.o: /usr/include/sys/stat.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
main.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
main.o: /usr/include/signal.h
word.o: word.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
word.o: brkincr.h ctype.h sym.h
string.o: string.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
string.o: brkincr.h ctype.h
name.o: name.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
name.o: brkincr.h ctype.h
args.o: args.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
args.o: brkincr.h ctype.h
xec.o: xec.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h brkincr.h
xec.o: ctype.h sym.h
service.o: service.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
service.o: brkincr.h ctype.h
error.o: error.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
error.o: brkincr.h ctype.h
io.o: io.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h brkincr.h
io.o: ctype.h
print.o: print.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
print.o: brkincr.h ctype.h
macro.o: macro.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
macro.o: brkincr.h ctype.h sym.h
expand.o: expand.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
expand.o: brkincr.h ctype.h /usr/include/sys/param.h /usr/include/sys/types.h
expand.o: /usr/include/signal.h /usr/include/machine/machparam.h
expand.o: /usr/include/sys/stat.h /usr/include/sys/dir.h
ctype.o: ctype.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h
ctype.o: brkincr.h ctype.h
msg.o: msg.c defs.h mac.h mode.h name.h stak.h /usr/include/setjmp.h brkincr.h
msg.o: ctype.h sym.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 8
E 7
E 4
E 1
