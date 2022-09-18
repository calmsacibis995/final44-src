h34472
s 00000/00000/00018
d D 8.1 93/06/05 11:11:10 bostic 12 11
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00016
d D 5.11 92/07/09 18:27:45 torek 11 10
c add boot_sparc.8
e
s 00001/00001/00016
d D 5.10 92/07/06 14:04:34 bostic 10 9
c fix the man page links
e
s 00001/00003/00016
d D 5.9 91/11/15 17:20:40 bostic 9 8
c minor cleanup
e
s 00002/00000/00017
d D 5.8 91/10/30 14:42:54 bostic 8 7
c fold halt into reboot; clean up the options, add -l back in
e
s 00009/00003/00008
d D 5.7 91/10/28 17:44:54 bostic 7 6
c break reboot man page up into machine specific and independent
e
s 00001/00005/00010
d D 5.6 90/06/29 20:19:16 bostic 6 5
c add hp300 support
e
s 00005/00000/00010
d D 5.5 90/06/19 15:11:04 bostic 5 4
c no reboot man page for hp300
e
s 00003/00010/00007
d D 5.4 90/06/08 14:32:02 bostic 4 3
c cleanup
e
s 00013/00045/00004
d D 5.3 90/05/11 13:04:59 bostic 3 2
c first pass for new make
e
s 00001/00001/00048
d D 5.2 89/05/11 13:55:06 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00049/00000/00000
d D 5.1 88/09/20 13:46:18 bostic 1 0
c date and time created 88/09/20 13:46:18 by bostic
e
u
U
t
T
I 1
D 3
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
E 3
I 3
#	%W% (Berkeley) %G%
E 3

D 3
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	reboot.c
OBJS=
MAN=	vax.reboot.0 tahoe.reboot.0
E 3
I 3
PROG=	reboot
D 4
NOMAN=	noman
E 4
DPADD=	${LIBUTIL}
LDADD=	-lutil
I 7
D 9
MAN8=	reboot.0
E 9
I 9
D 11
MAN8=	reboot.0 boot_hp300.0 boot_i386.0 boot_tahoe.0 boot_vax.0
E 11
I 11
MAN8=	reboot.0 boot_hp300.0 boot_i386.0 boot_sparc.0 boot_tahoe.0 boot_vax.0
E 11
E 9
I 8
D 10
MLINKS=	halt.8 reboot.8
E 10
I 10
MLINKS=	reboot.8 halt.8
E 10
LINKS=	${BINDIR}/reboot ${BINDIR}/halt
E 8
E 7
I 5
D 9

D 6
.if ${MACHINE} == "hp300"
NOMAN=	noman
.else
E 6
E 5
I 4
D 7
MAN8=	reboot_${MACHINE}.0
D 6
MANSUBDIR=/${MACHINE}
E 6
MLINKS=	reboot_${MACHINE}.8 reboot.8
I 5
D 6
.endif
E 6
I 6
MANSUBDIR=/${MACHINE}
E 7
I 7
reboot.0: boot_hp300.0 boot_i386.0 boot_tahoe.0 boot_vax.0
E 9
E 7
E 6
E 5
E 4
E 3

I 7
afterinstall:
	${MINSTALL} boot_hp300.0 ${DESTDIR}${MANDIR}8/hp300/boot.0
	${MINSTALL} boot_i386.0 ${DESTDIR}${MANDIR}8/i386/boot.0
I 11
	${MINSTALL} boot_sparc.0 ${DESTDIR}${MANDIR}8/sparc/boot.0
E 11
	${MINSTALL} boot_tahoe.0 ${DESTDIR}${MANDIR}8/tahoe/boot.0
	${MINSTALL} boot_vax.0 ${DESTDIR}${MANDIR}8/vax/boot.0

.include <bsd.man.mk>
E 7
D 3
all: reboot
E 3
I 3
D 4
all: vax.reboot.0 tahoe.reboot.0
E 3

D 3
reboot: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c -lutil
E 3
I 3
beforeinstall:
	install -c -o ${MANOWN} -g ${MANGRP} -m ${MANMODE} vax.reboot.0 \
	    ${DESTDIR}${MANDIR}8/vax
	install -c -o ${MANOWN} -g ${MANGRP} -m ${MANMODE} tahoe.reboot.0 \
	    ${DESTDIR}${MANDIR}8/tahoe
E 3

D 3
clean:
	rm -f ${OBJS} core reboot

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 reboot ${DESTDIR}/etc/reboot
E 2
I 2
	install -s -o bin -g bin -m 755 reboot ${DESTDIR}/sbin
E 2
	install -c -o bin -g bin -m 444 vax.reboot.0 ${DESTDIR}/usr/man/cat8/vax
	install -c -o bin -g bin -m 444 tahoe.reboot.0 ${DESTDIR}/usr/man/cat8/tahoe

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.own.mk>
E 4
.include <bsd.prog.mk>
E 3
E 1
