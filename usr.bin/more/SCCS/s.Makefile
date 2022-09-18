h17750
s 00000/00000/00015
d D 8.1 93/06/06 15:37:45 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00013
d D 5.6 91/03/12 08:53:04 bostic 6 5
c re_comp, re_exec moved to -lcompat
e
s 00011/00049/00004
d D 5.5 90/05/11 14:14:35 bostic 5 4
c first pass for new make
e
s 00005/00005/00048
d D 5.4 89/05/11 13:36:44 bostic 4 3
c file reorg, pathnames.h, paths.h
e
s 00012/00017/00041
d D 5.3 88/11/22 17:10:09 bostic 3 2
c less -> more
e
s 00013/00065/00045
d D 5.2 88/09/23 14:51:49 bostic 2 1
c remove version.c, lesskey, cleanup, add cleandir, blah, balh
e
s 00110/00000/00000
d D 5.1 88/07/22 12:55:26 bostic 1 0
c date and time created 88/07/22 12:55:26 by bostic
e
u
U
t
T
I 1
D 5
#
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation, advertising
# materials, and other materials related to such redistribution and
# use acknowledge that the software was developed by the University
# of California, Berkeley.  The name of the University may not be
# used to endorse or promote products derived from this software
# without specific prior written permission.  THIS SOFTWARE IS PROVIDED
# ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
# WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND
# FITNESS FOR A PARTICULAR PURPOSE.
#
# %W% (Berkeley) %G%
#
E 5
I 5
#	%W% (Berkeley) %G%
E 5

D 3
DEFS=	-DHELPFILE=\"/usr/lib/less.help\" -DEDIT_PGM=\"/usr/ucb/vi\" -DRECOMP
CFLAGS=	-O ${DEFS}
E 3
I 3
D 4
CFLAGS=	-O -I/nbsd/usr/include -I.
E 4
I 4
D 5
CFLAGS=	-g -I.
E 4
E 3
LIBC=	/lib/libc.a
E 5
I 5
PROG=	more
CFLAGS+=-I${.CURDIR}
E 5
SRCS=	ch.c command.c decode.c help.c input.c line.c linenum.c main.c \
D 3
	option.c os.c output.c position.c prim.c prompt.c screen.c \
E 3
I 3
D 5
	option.c os.c output.c position.c prim.c screen.c \
E 3
D 2
	signal.c tags.c ttyin.c version.c
E 2
I 2
	signal.c tags.c ttyin.c
E 2
OBJS=	ch.o command.o decode.o help.o input.o line.o linenum.o main.o \
D 3
	option.o os.o output.o position.o prim.o prompt.o screen.o \
E 3
I 3
	option.o os.o output.o position.o prim.o screen.o \
E 3
D 2
	signal.o tags.o ttyin.o version.o
E 2
I 2
	signal.o tags.o ttyin.o
D 3
MAN=	less.0
E 3
I 3
MAN=	more.0
E 5
I 5
	option.c os.c output.c position.c prim.c screen.c signal.c tags.c \
	ttyin.c
D 6
DPADD=	${LIBTERM}
LDADD=	-ltermcap
E 6
I 6
DPADD=	${LIBTERM} ${LIBCOMPAT}
LDADD=	-ltermcap -lcompat
E 6
E 5
E 3
E 2

D 2
.SUFFIXES: .1 .0
E 2
I 2
D 3
all: less
E 3
I 3
D 5
all: more
E 5
I 5
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/more.help \
	    ${DESTDIR}/usr/share/misc
E 5
E 3
E 2

D 2
.1.0:
	${DESTDIR}/usr/man/manroff $*.1 > $*.0

all: less lesskey

E 2
D 3
less: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS} -ltermcap
E 3
I 3
D 5
more: ${OBJS} ${LIBC}
D 4
	${CC} -o $@ ${CFLAGS} ${OBJS} -ltermcap /nbsd/lib/libc.a
E 4
I 4
	${CC} -o $@ ${CFLAGS} ${OBJS} -ltermcap
E 4
E 3

D 2
lesskey: lesskey.o ${LIBC}
	${CC} -o $@ ${CFLAGS} lesskey.o 

E 2
D 3
#funcs.h: ${SRCS}
funcs.h:
	awk -f mkfuncs.awk ${SRCS} > funcs.h

E 3
D 2
clean: FRC
	rm -f ${OBJS} core less lesskey less.0 lesskey.0
E 2
I 2
clean:
D 3
	rm -f ${OBJS} core less lesskey
E 3
I 3
	rm -f ${OBJS} core more
E 3
E 2

D 2
depend: ${SRCS} funcs.h FRC
E 2
I 2
cleandir: clean
	rm -f ${MAN} tags .depend

D 3
depend: ${SRCS} funcs.h
E 3
I 3
depend: ${SRCS}
E 3
E 2
	mkdep ${CFLAGS} ${SRCS}

D 2
install: less.0 lesskey.0 FRC
E 2
I 2
install: ${MAN}
E 2
D 3
	install -s -o bin -g bin -m 755 less ${DESTDIR}/usr/ucb/less
D 2
	install -s -o bin -g bin -m 755 lesskey ${DESTDIR}/usr/ucb/lesskey
E 2
	install -o bin -g bin -m 444 less.0 ${DESTDIR}/usr/man/cat1/less.0
D 2
	install -o bin -g bin -m 444 lesskey.0 ${DESTDIR}/usr/man/cat1/lesskey.0
E 2
	install -c -o bin -g bin -m 444 less.help ${DESTDIR}/usr/lib/less.help
E 3
I 3
D 4
	install -s -o bin -g bin -m 755 more ${DESTDIR}/usr/ucb/more
	install -o bin -g bin -m 444 more.0 ${DESTDIR}/usr/man/cat1
	install -c -o bin -g bin -m 444 more.help ${DESTDIR}/usr/lib
E 4
I 4
	install -s -o bin -g bin -m 755 more ${DESTDIR}/usr/bin
	install -c -o bin -g bin -m 444 more.0 ${DESTDIR}/usr/man/cat1
	install -c -o bin -g bin -m 444 more.help ${DESTDIR}/usr/share/misc
E 4
E 3

D 2
lint: FRC
E 2
I 2
lint: ${SRCS}
E 2
	lint ${CFLAGS} ${SRCS}

D 2
tags: FRC
E 2
I 2
tags: ${SRCS}
E 2
	ctags ${SRCS}
E 5
I 5
.include <bsd.prog.mk>
E 5
D 2

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

ch.o: ch.c less.h /usr/include/sys/types.h /usr/include/sys/file.h funcs.h
command.o: command.c less.h /usr/include/sys/types.h /usr/include/sys/file.h
command.o: funcs.h position.h cmd.h
decode.o: decode.c less.h /usr/include/sys/types.h /usr/include/sys/file.h
decode.o: funcs.h cmd.h
help.o: help.c less.h /usr/include/sys/types.h /usr/include/sys/file.h funcs.h
input.o: input.c less.h /usr/include/sys/types.h /usr/include/sys/file.h
input.o: funcs.h
line.o: line.c less.h /usr/include/sys/types.h /usr/include/sys/file.h funcs.h
linenum.o: linenum.c less.h /usr/include/sys/types.h /usr/include/sys/file.h
linenum.o: funcs.h position.h
main.o: main.c less.h /usr/include/sys/types.h /usr/include/sys/file.h funcs.h
main.o: position.h
option.o: option.c less.h /usr/include/sys/types.h /usr/include/sys/file.h
option.o: funcs.h
os.o: os.c /usr/include/stdio.h /usr/include/signal.h
os.o: /usr/include/machine/trap.h /usr/include/setjmp.h less.h
os.o: /usr/include/sys/types.h /usr/include/sys/file.h funcs.h
os.o: /usr/include/sys/types.h /usr/include/sys/stat.h
output.o: output.c less.h /usr/include/sys/types.h /usr/include/sys/file.h
output.o: funcs.h
position.o: position.c less.h /usr/include/sys/types.h /usr/include/sys/file.h
position.o: funcs.h position.h
prim.o: prim.c less.h /usr/include/sys/types.h /usr/include/sys/file.h funcs.h
prim.o: position.h
prompt.o: prompt.c less.h /usr/include/sys/types.h /usr/include/sys/file.h
prompt.o: funcs.h position.h
screen.o: screen.c less.h /usr/include/sys/types.h /usr/include/sys/file.h
screen.o: funcs.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
screen.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
screen.o: /usr/include/sys/ioctl.h
signal.o: signal.c less.h /usr/include/sys/types.h /usr/include/sys/file.h
signal.o: funcs.h /usr/include/signal.h /usr/include/machine/trap.h
tags.o: tags.c /usr/include/stdio.h less.h /usr/include/sys/types.h
tags.o: /usr/include/sys/file.h funcs.h
ttyin.o: ttyin.c less.h /usr/include/sys/types.h /usr/include/sys/file.h
ttyin.o: funcs.h
version.o: version.c

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 2
E 1
