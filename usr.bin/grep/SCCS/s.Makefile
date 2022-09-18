h14088
s 00000/00000/00005
d D 8.1 93/06/06 14:50:34 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00048/00003
d D 5.8 90/06/19 12:51:42 bostic 8 7
c break up into subdirectories
e
s 00001/00001/00050
d D 5.7 90/06/19 11:14:10 bostic 7 6
c CTAGS not defined
e
s 00034/00049/00017
d D 5.6 90/05/11 14:18:04 bostic 6 5
c first pass for new make
e
s 00007/00014/00059
d D 5.5 89/05/11 13:34:55 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00012/00041/00057
d D 5.4 88/10/25 18:24:07 bostic 4 3
c cleanup, add man page
e
s 00011/00005/00087
d D 5.3 88/07/09 10:41:10 bostic 3 2
c install approved copyright notice
e
s 00001/00001/00091
d D 5.2 88/01/21 12:41:01 bostic 2 1
c optimize compiler
e
s 00092/00000/00000
d D 5.1 87/12/12 18:07:39 bostic 1 0
c date and time created 87/12/12 18:07:39 by bostic
e
u
U
t
T
I 1
D 6
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 3
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 3
#
E 6
#	%W% (Berkeley) %G%
I 3
D 6
#
E 3
#
D 5
# -DEGREPSTD=path	location of std egrep (normally /usr/bin/egrep).
# -DGREPSTD=path	location of std grep (normally /bin/grep).
# -DFGREPSTD=path	location of std fgrep (normally /usr/bin/fgrep).
E 5
# -Dstrrchr=rindex, -Dstrchr=index	for troglodytes.
# -DSLOWSYS		invoke xread() for system time quirk on PDP, others? 
# -DNOKANJI		default is for Japanese Unix.  undef only for raw
#			 parity-marked search capability, not standard w/grep.
# -DCHINESE		for systems using EUC Chinese2 codes
E 6

D 2
CFLAGS=	-g -Dstrrchr=rindex -Dstrchr=index -DNOKANJI \
E 2
I 2
D 5
CFLAGS=	-O -Dstrrchr=rindex -Dstrchr=index -DNOKANJI \
E 2
	-DEGREPSTD=\"/usr/lib/old.egrep\" -DGREPSTD=\"/usr/lib/old.bin.grep\" \
	-DFGREPSTD=\"/usr/lib/old.fgrep\"
E 5
I 5
D 6
CFLAGS=	-O -Dstrrchr=rindex -Dstrchr=index -DNOKANJI
E 5
LIBC=	/lib/libc.a
ALL=	egrep old.ucb.grep old.bin.grep old.fgrep old.egrep
E 6
I 6
D 8
# -DSLOWSYS	invoke xread() for system time quirk on PDP, others?
# -DNOKANJI	default is for Japanese Unix.  undef only for raw
#		parity-marked search capability, not standard w/grep.
# -DCHINESE	for systems using EUC Chinese2 codes
# -Dstrrchr=rindex, -Dstrchr=index	as necessary
E 8
I 8
SUBDIR=	egrep old.bin.grep old.egrep old.fgrep old.ucb.grep
E 8

D 8
PROGS=	egrep old.ucb.grep old.bin.grep old.fgrep old.egrep
CFLAGS+=-Dstrrchr=rindex -Dstrchr=index -DNOKANJI
E 6
SRCS=	egrep.c old.ucb.grep.c old.bin.grep.c old.fgrep.c old.egrep.c
D 6
OBJS=
I 4
MAN=	grep.0
E 6
I 6
LIBC=	/usr/lib/libc.a
MAN1=	grep.0
LINKS=	${BINDIR}/egrep ${BINDIR}/grep ${BINDIR}/egrep ${BINDIR}/fgrep
MLINKS=	grep.1 egrep.1 grep.1 fgrep.1
E 6
E 4

D 6
all: ${ALL}
E 6
I 6
all: ${PROGS} ${MAN1}
E 6

D 4
egrep: egrep.c ${LIBC}
	${CC} -o $@ ${CFLAGS} egrep.c
E 4
I 4
D 6
egrep oegrep old.ucb.grep old.bin.grep old.fgrep old.egrep: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 6
I 6
egrep oegrep old.ucb.grep old.bin.grep old.fgrep: ${.PREFIX}.c ${LIBC}
	${CC} -o ${.TARGET} ${CFLAGS} ${.CURDIR}/${.PREFIX}.c
E 6
E 4

I 6
old.egrep: old.egrep.c ${LIBC}
	${CC} -o ${.TARGET} ${CFLAGS} ${.PREFIX}.c

E 6
D 4
oegrep: oegrep.c ${LIBC}
	${CC} -o $@ ${CFLAGS} oegrep.c

old.ucb.grep: ${LIBC}
	${CC} -o $@ ${CFLAGS} old.ucb.grep.c

old.bin.grep: ${LIBC}
	${CC} -o $@ ${CFLAGS} old.bin.grep.c

old.fgrep: ${LIBC}
	${CC} -o $@ ${CFLAGS} old.fgrep.c

old.egrep: ${LIBC}
	${CC} -o $@ ${CFLAGS} old.egrep.c

clean: FRC
E 4
I 4
clean:
E 4
D 6
	rm -f ${OBJS} core ${ALL} old.egrep.c
E 6
I 6
	rm -f a.out Errs errs mklog core ${PROGS} old.egrep.c
E 6

D 4
depend: FRC ${SRCS}
E 4
I 4
cleandir: clean
D 6
	rm -f ${MAN} tags .depend
E 6
I 6
	rm -f ${MAN1} ${.CURDIR}/tags .depend
E 6

depend: ${SRCS}
E 4
D 6
	mkdep -p ${CFLAGS} ${SRCS}
E 6
I 6
	mkdep ${CFLAGS:M-[ID]*} ${.ALLSRC}
E 6

D 4
install: FRC
E 4
I 4
D 6
install: ${MAN}
E 4
D 5
	install -s -o bin -g bin -m 755 egrep ${DESTDIR}/usr/ucb/egrep
	rm -f ${DESTDIR}/usr/ucb/fgrep ${DESTDIR}/usr/ucb/grep
	ln ${DESTDIR}/usr/ucb/egrep ${DESTDIR}/usr/ucb/grep
	ln ${DESTDIR}/usr/ucb/egrep ${DESTDIR}/usr/ucb/fgrep
	install -s -o bin -g bin -m 755 old.bin.grep ${DESTDIR}/usr/lib/old.bin.grep
	install -s -o bin -g bin -m 755 old.ucb.grep ${DESTDIR}/usr/lib/old.ucb.grep
	install -s -o bin -g bin -m 755 old.fgrep ${DESTDIR}/usr/lib/old.fgrep
	install -s -o bin -g bin -m 755 old.egrep ${DESTDIR}/usr/lib/old.egrep
E 5
I 5
	install -s -o bin -g bin -m 755 egrep ${DESTDIR}/usr/bin/egrep
	rm -f ${DESTDIR}/usr/bin/fgrep ${DESTDIR}/usr/bin/grep
	ln ${DESTDIR}/usr/bin/egrep ${DESTDIR}/usr/bin/grep
	ln ${DESTDIR}/usr/bin/egrep ${DESTDIR}/usr/bin/fgrep
	install -s -o bin -g bin -m 755 old.ucb.grep old.bin.grep old.fgrep \
		old.egrep ${DESTDIR}/usr/libexec
E 5
I 4
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
	rm -f ${DESTDIR}/usr/man/cat1/egrep.0
	rm -f ${DESTDIR}/usr/man/cat1/fgrep.0
	ln ${DESTDIR}/usr/man/cat1/grep.0 ${DESTDIR}/usr/man/cat1/egrep.0
	ln ${DESTDIR}/usr/man/cat1/grep.0 ${DESTDIR}/usr/man/cat1/fgrep.0
E 6
I 6
install: maninstall
E 6
E 4

I 6
maninstall: beforeinstall

beforeinstall:
	install ${STRIP} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} egrep \
	    ${DESTDIR}${BINDIR}/egrep
	install ${STRIP} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    old.ucb.grep old.bin.grep old.fgrep old.egrep \
	    ${DESTDIR}/usr/libexec

E 6
D 4
lint: FRC ${SRCS}
E 4
I 4
lint: ${SRCS}
E 4
D 6
	lint ${CFLAGS} ${SRCS}
E 6
I 6
	${LINT} ${LINTFLAGS} ${CFLAGS} ${.ALLSRC}
E 6

D 4
tags: FRC ${SRCS}
E 4
I 4
tags: ${SRCS}
E 4
D 6
	ctags ${SRCS}
E 6
I 6
D 7
	${CTAGS} ${.ALLSRC} -f ${.CURDIR}/tags
E 7
I 7
	-ctags ${.ALLSRC} -f ${.CURDIR}/tags
E 7
E 6

D 6
FRC:
E 6
I 6
.include <bsd.prog.mk>
E 8
I 8
.include <bsd.subdir.mk>
E 8
E 6
D 4

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

egrep: egrep.c /usr/include/stdio.h /usr/include/ctype.h
egrep: /usr/include/sys/types.h /usr/include/sys/stat.h /usr/include/sys/file.h
egrep: /usr/include/regexp.h
old.ucb.grep: old.ucb.grep.c /usr/include/stdio.h /usr/include/sys/types.h
old.ucb.grep: /usr/include/sys/stat.h
old.bin.grep: old.bin.grep.c /usr/include/sys/types.h /usr/include/sys/file.h
old.bin.grep: /usr/include/sys/stat.h /usr/include/stdio.h /usr/include/ctype.h
old.fgrep: old.fgrep.c /usr/include/stdio.h /usr/include/ctype.h
old.fgrep: /usr/include/sys/param.h /usr/include/sys/types.h
old.fgrep: /usr/include/signal.h /usr/include/machine/trap.h
old.fgrep: /usr/include/machine/machparam.h /usr/include/sys/stat.h
old.egrep: old.egrep.c /usr/include/stdio.h /usr/include/sys/types.h
old.egrep: /usr/include/sys/stat.h /usr/include/ctype.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 1
