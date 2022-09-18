h34896
s 00002/00000/00004
d D 6.10 90/05/11 17:12:40 bostic 10 9
c add sccs headers
e
s 00003/00053/00001
d D 6.9 90/05/11 17:12:13 bostic 9 8
c first pass for new make
e
s 00002/00001/00052
d D 6.8 89/05/19 18:47:23 bostic 8 7
c add vplotf to installation list
e
s 00003/00003/00050
d D 6.7 89/05/11 14:10:09 bostic 7 6
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00052
d D 6.6 89/01/20 10:03:50 bostic 6 5
c remove vplotf on clean
e
s 00017/00080/00036
d D 6.5 88/09/29 09:24:59 bostic 5 4
c general cleanup
e
s 00010/00005/00106
d D 6.4 88/06/30 17:53:10 bostic 4 3
c install approved copyright notice
e
s 00009/00003/00102
d D 6.3 88/03/08 08:29:57 bostic 3 2
c add Berkeley specific header
e
s 00001/00001/00104
d D 6.2 87/11/05 09:22:11 bostic 2 1
c add chrtab.o to clean
e
s 00105/00000/00000
d D 6.1 87/11/04 20:45:01 bostic 1 0
c date and time created 87/11/04 20:45:01 by bostic
e
u
U
t
T
I 10
#	%W% (Berkeley) %G%

E 10
I 1
D 9
#
# Copyright (c) 1987 Regents of the University of California.
D 3
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 3
I 3
# All rights reserved.
E 3
#
D 3
#	%W%	(Berkeley)	%G%
E 3
I 3
# Redistribution and use in source and binary forms are permitted
D 4
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 4
I 4
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
#	%W% (Berkeley) %G%
E 3
#
CFLAGS=	-O
LIBC=	/lib/libc.a
D 5
SRCS=	necf.c railmag.c rvcat.c rvsort.c sidebyside.c vcat.c \
E 5
I 5
SRCS=	chrtab.c necf.c railmag.c rvcat.c rvsort.c sidebyside.c vcat.c \
E 5
	vdmp.c vpf.c vplotf.c vpltdmp.c vpsf.c vsort.c
D 5
OBJS=	necf.o railmag.o rvcat.o rvsort.o sidebyside.o vcat.o \
E 5
I 5
OBJS=	chrtab.o necf.o railmag.o rvcat.o rvsort.o sidebyside.o vcat.o \
E 5
	vdmp.o vpf.o vplotf.o vpltdmp.o vpsf.o vsort.o
D 5
ALL=	necf railmag rvcat rvsort sidebyside vcat \
	vdmp vpf vplotf vpltdmp vpsf vsort
E 5
I 5
ALL=	necf railmag rvcat rvsort sidebyside vcat vdmp vpf vpltdmp vpsf vsort
E 9
I 9
SUBDIR=	necf railmag rvcat rvsort sidebyside vcat vdmp vpf vplotf vpltdmp \
	vpsf vsort
E 9
E 5

D 5
all: ${ALL}
E 5
I 5
D 9
all: ${ALL} vplotf
E 5

D 5
necf: ${LIBC}
	${CC} -O -o $@ necf.c
railmag: ${LIBC}
	${CC} -O -o $@ railmag.c
rvcat: ${LIBC}
	${CC} -O -o $@ rvcat.c
rvsort: ${LIBC}
	${CC} -O -o $@ rvsort.c
sidebyside: ${LIBC}
	${CC} -O -o $@ sidebyside.c
vcat: ${LIBC}
	${CC} -O -o $@ vcat.c
vdmp: ${LIBC}
	${CC} -O -o $@ vdmp.c
vpf: ${LIBC}
	${CC} -O -o $@ vpf.c
E 5
I 5
${ALL}: ${LIBC}
	${CC} -O -o $@ $@.c

E 5
vplotf: ${LIBC} chrtab.c
	${CC} -O -o $@ vplotf.c chrtab.c
D 5
vpltdmp: ${LIBC}
	${CC} -O -o $@ vpltdmp.c
vpsf: ${LIBC}
	${CC} -O -o $@ vpsf.c
vsort: ${LIBC}
	${CC} -O -o $@ vsort.c
E 5

D 5
clean: FRC
D 2
	rm -f ${OBJS} core ${ALL}
E 2
I 2
	rm -f ${OBJS} core ${ALL} chrtab.o
E 5
I 5
clean:
D 6
	rm -f ${OBJS} core ${ALL}
E 6
I 6
	rm -f ${OBJS} core ${ALL} vplotf
E 6
E 5
E 2

D 5
depend: FRC
E 5
I 5
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 5
	mkdep -p ${CFLAGS} ${SRCS}

D 5
install: FRC
	install -s -o bin -g bin -m 755 necf ${DESTDIR}/usr/lib/necf
	install -s -o bin -g bin -m 755 railmag ${DESTDIR}/usr/lib/railmag
	install -s -o bin -g bin -m 755 rvcat ${DESTDIR}/usr/lib/rvcat
	install -s -o bin -g bin -m 755 rvsort ${DESTDIR}/usr/lib/rvsort
	install -s -o bin -g bin -m 755 sidebyside ${DESTDIR}/usr/lib/sidebyside
	install -s -o bin -g bin -m 755 vcat ${DESTDIR}/usr/lib/vcat
	install -s -o bin -g bin -m 755 vdmp ${DESTDIR}/usr/lib/vdmp
	install -s -o bin -g bin -m 755 vpf ${DESTDIR}/usr/lib/vpf
E 5
I 5
install: ${MAN}
D 7
	install -s -o bin -g bin -m 755 ${ALL} ${DESTDIR}/usr/lib
E 5
	rm -f ${DESTDIR}/usr/lib/vpfW
	ln ${DESTDIR}/usr/lib/vpf ${DESTDIR}/usr/lib/vpfW
E 7
I 7
D 8
	install -s -o bin -g bin -m 755 ${ALL} ${DESTDIR}/usr/libexec/lpr
E 8
I 8
	install -s -o bin -g bin -m 755 ${ALL} vplotf \
	    ${DESTDIR}/usr/libexec/lpr
E 8
	rm -f ${DESTDIR}/usr/libexec/lpr/vpfW
	ln ${DESTDIR}/usr/libexec/lpr/vpf ${DESTDIR}/usr/libexec/lpr/vpfW
E 7
D 5
	install -s -o bin -g bin -m 755 vplotf ${DESTDIR}/usr/lib/vplotf
	install -s -o bin -g bin -m 755 vpltdmp ${DESTDIR}/usr/lib/vpltdmp
	install -s -o bin -g bin -m 755 vpsf ${DESTDIR}/usr/lib/vpsf
	install -s -o bin -g bin -m 755 vsort ${DESTDIR}/usr/lib/vsort
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
	ctags ${SRCS}
E 9
I 9
.include <bsd.subdir.mk>
E 9
D 5

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

necf: necf.c /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
necf: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
railmag: railmag.c
rvcat: rvcat.c /usr/include/stdio.h /usr/include/sys/vcmd.h
rvcat: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
rvcat: /usr/include/sys/ttydev.h /usr/include/vfont.h
rvsort: rvsort.c /usr/include/stdio.h
sidebyside: sidebyside.c /usr/include/stdio.h
vcat: vcat.c /usr/include/stdio.h /usr/include/sys/vcmd.h
vcat: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
vcat: /usr/include/sys/ttydev.h /usr/include/vfont.h
vdmp: vdmp.c /usr/include/stdio.h /usr/include/sys/vcmd.h
vdmp: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
vdmp: /usr/include/sys/ttydev.h
vpf: vpf.c /usr/include/signal.h /usr/include/machine/trap.h
vpf: /usr/include/stdio.h /usr/include/sys/vcmd.h /usr/include/sys/ioctl.h
vpf: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
vplotf: vplotf.c /usr/include/stdio.h /usr/include/vfont.h
vplotf: /usr/include/sys/vcmd.h /usr/include/sys/ioctl.h
vplotf: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
vpltdmp: vpltdmp.c /usr/include/stdio.h /usr/include/sys/vcmd.h
vpltdmp: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
vpltdmp: /usr/include/sys/ttydev.h
vpsf: vpsf.c /usr/include/stdio.h /usr/include/sys/vcmd.h
vpsf: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
vpsf: /usr/include/sys/ttydev.h
vsort: vsort.c /usr/include/stdio.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 5
E 1
