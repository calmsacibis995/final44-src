h36664
s 00004/00002/00057
d D 5.4 89/05/10 22:36:57 bostic 6 5
c minor cleanups
e
s 00025/00064/00034
d D 5.3 89/04/10 11:12:00 bostic 5 4
c add man page
e
s 00072/00018/00026
d D 5.2 87/06/19 09:21:08 bostic 4 3
c new template
e
s 00005/00001/00039
d D 5.1 85/04/26 12:51:34 dist 3 2
c Add copyright
e
s 00001/00001/00039
d D 4.2 83/05/23 00:18:33 sam 2 1
c bogus
e
s 00040/00000/00000
d D 4.1 83/03/09 16:22:07 ralph 1 0
c date and time created 83/03/09 16:22:07 by ralph
e
u
U
t
T
I 1
#
D 3
#	%M%	%I%	%E%
E 3
I 3
D 4
# Copyright (c) 1980 Regents of the University of California.
E 4
I 4
D 5
# Copyright (c) 1987 Regents of the University of California.
E 4
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 5
I 5
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
E 5
#
D 4
#	%W% (Berkeley) %G%
E 4
I 4
D 5
#	%W%	(Berkeley)	%G%
E 5
I 5
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
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
E 4
E 3
#
I 5
#	%W% (Berkeley) %G%
#
E 5
D 4
LIBDIR=	/usr/lib
DESTDIR=
E 4
CFLAGS=	-DTRACE -O
D 4
VGRIND=	csh /usr/ucb/vgrind
SRCS=	2648.h bit.h \
	agoto.c aminmax.c aon.c areaclear.c beep.c bitcopy.c cleara.c \
E 4
I 4
SRCS=	agoto.c aminmax.c aon.c areaclear.c beep.c bitcopy.c cleara.c \
E 4
	clearg.c curon.c dispmsg.c draw.c drawbox.c dumpmat.c \
	emptyrow.c error.c escseq.c gdefault.c gon.c kon.c line.c mat.c \
	message.c minmax.c motion.c move.c movecurs.c newmat.c outchar.c \
	outstr.c printg.c rawchar.c rbon.c rdchar.c readline.c set.c \
	setmat.c sync.c texton.c ttyinit.c update.c video.c zermat.c \
	zoomn.c zoomon.c zoomout.c
OBJS=	agoto.o aminmax.o aon.o areaclear.o beep.o bitcopy.o cleara.o \
	clearg.o curon.o dispmsg.o draw.o drawbox.o dumpmat.o \
	emptyrow.o error.o escseq.o gdefault.o gon.o kon.o line.o mat.o \
	message.o minmax.o motion.o move.o movecurs.o newmat.o outchar.o \
	outstr.o printg.o rawchar.o rbon.o rdchar.o readline.o set.o \
	setmat.o sync.o texton.o ttyinit.o update.o video.o zermat.o \
	zoomn.o zoomon.o zoomout.o
I 5
MAN=	lib2648.0
E 5

D 4
lib2648.a:	${OBJS}
E 4
I 4
all: lib2648.a

lib2648.a: ${OBJS}
E 4
D 6
	ar cr lib2648.a `lorder ${OBJS} | tsort`
E 6
I 6
	@echo building normal lib2648
	@ar cr lib2648.a `lorder ${OBJS} | tsort`
	ranlib lib2648.a
E 6

D 4
install:	lib2648.a
	install lib2648.a ${DESTDIR}${LIBDIR}/lib2648.a
	ranlib ${DESTDIR}${LIBDIR}/lib2648.a
E 4
I 4
D 5
clean: FRC
E 5
I 5
clean:
E 5
	rm -f ${OBJS} core lib2648.a
E 4

D 4
tags:	/tmp
E 4
I 4
D 5
depend: FRC
E 5
I 5
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 5
	mkdep ${CFLAGS} ${SRCS}

D 5
install: FRC
E 5
I 5
install: ${MAN}
E 5
	install -o bin -g bin -m 644 lib2648.a ${DESTDIR}/usr/lib/lib2648.a
D 6
	ranlib ${DESTDIR}/usr/lib/lib2648.a
E 6
I 6
	ranlib -t ${DESTDIR}/usr/lib/lib2648.a
E 6
I 5
	install -c -o bin -g bin -m 444 lib2648.0 ${DESTDIR}/usr/man/cat3
E 5

D 5
lint: FRC
E 5
I 5
lint: ${SRCS}
E 5
	lint ${CFLAGS} ${SRCS}

D 5
tags: FRC
E 5
I 5
tags: ${SRCS}
E 5
E 4
	ctags ${SRCS}
D 5

D 4
clean:
D 2
	rm lib2648.a ${OBJS}
E 2
I 2
	rm -f lib2648.a ${OBJS}
E 4
I 4
FRC:
E 4
E 2

D 4
vgrind:
	tee index </dev/null
	${VGRIND} -h lib2648 ${SRCS}
	${VGRIND} -x index
E 4
I 4
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

agoto.o: agoto.c 2648.h /usr/include/stdio.h
aminmax.o: aminmax.c bit.h /usr/include/stdio.h
aon.o: aon.c 2648.h /usr/include/stdio.h
areaclear.o: areaclear.c 2648.h /usr/include/stdio.h
beep.o: beep.c 2648.h /usr/include/stdio.h
bitcopy.o: bitcopy.c bit.h /usr/include/stdio.h
cleara.o: cleara.c 2648.h /usr/include/stdio.h
clearg.o: clearg.c 2648.h /usr/include/stdio.h
curon.o: curon.c 2648.h /usr/include/stdio.h
dispmsg.o: dispmsg.c 2648.h /usr/include/stdio.h
draw.o: draw.c 2648.h /usr/include/stdio.h
drawbox.o: drawbox.c 2648.h /usr/include/stdio.h
dumpmat.o: dumpmat.c bit.h /usr/include/stdio.h
emptyrow.o: emptyrow.c bit.h /usr/include/stdio.h
error.o: error.c
escseq.o: escseq.c 2648.h /usr/include/stdio.h
gdefault.o: gdefault.c 2648.h /usr/include/stdio.h
gon.o: gon.c 2648.h /usr/include/stdio.h
kon.o: kon.c 2648.h /usr/include/stdio.h
line.o: line.c 2648.h /usr/include/stdio.h
mat.o: mat.c bit.h /usr/include/stdio.h
message.o: message.c 2648.h /usr/include/stdio.h
minmax.o: minmax.c bit.h /usr/include/stdio.h
motion.o: motion.c 2648.h /usr/include/stdio.h
move.o: move.c 2648.h /usr/include/stdio.h
movecurs.o: movecurs.c 2648.h /usr/include/stdio.h
newmat.o: newmat.c bit.h /usr/include/stdio.h
outchar.o: outchar.c 2648.h /usr/include/stdio.h
outstr.o: outstr.c 2648.h /usr/include/stdio.h
printg.o: printg.c 2648.h /usr/include/stdio.h
rawchar.o: rawchar.c 2648.h /usr/include/stdio.h
rbon.o: rbon.c 2648.h /usr/include/stdio.h
rdchar.o: rdchar.c /usr/include/ctype.h
readline.o: readline.c 2648.h /usr/include/stdio.h
set.o: set.c 2648.h /usr/include/stdio.h
setmat.o: setmat.c bit.h /usr/include/stdio.h
sync.o: sync.c 2648.h /usr/include/stdio.h
texton.o: texton.c 2648.h /usr/include/stdio.h
ttyinit.o: ttyinit.c /usr/include/sgtty.h /usr/include/sys/ioctl.h
ttyinit.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h 2648.h
ttyinit.o: /usr/include/stdio.h
update.o: update.c bit.h /usr/include/stdio.h
video.o: video.c 2648.h /usr/include/stdio.h
zermat.o: zermat.c bit.h /usr/include/stdio.h
zoomn.o: zoomn.c 2648.h /usr/include/stdio.h
zoomon.o: zoomon.c 2648.h /usr/include/stdio.h
zoomout.o: zoomout.c

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 5
E 4
E 1
