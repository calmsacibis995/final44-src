h12173
s 00006/00003/00008
d D 8.2 94/03/27 13:47:33 bostic 19 18
c Jan-Simon Pendry's and my new mount code
e
s 00000/00000/00011
d D 8.1 93/06/18 15:02:42 bostic 18 17
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00010
d D 7.14 93/06/18 15:02:37 bostic 17 15
c rename mfs man page to mount_mfs, leave mfs though
e
s 00000/00000/00011
d R 8.1 93/06/05 11:06:28 bostic 16 15
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00009
d D 7.13 91/02/26 15:40:37 bostic 15 13
c dkcksum moved from C library to disklable
e
s 00001/00001/00009
d R 7.13 91/01/15 14:10:06 bostic 14 13
c kernel reorg
e
s 00001/00001/00009
d D 7.12 90/05/24 16:43:32 bostic 13 12
c wrong link order
e
s 00007/00048/00003
d D 7.11 90/05/11 13:05:07 bostic 12 11
c first pass for new make
e
s 00002/00002/00049
d D 7.10 89/11/25 14:45:58 mckusick 11 10
c install as mount_mfs
e
s 00002/00000/00049
d D 7.9 89/10/18 17:03:10 mckusick 10 9
c add link for mfs manual page
e
s 00002/00002/00047
d D 7.8 89/10/18 11:10:07 mckusick 9 8
c memfs => mfs
e
s 00002/00000/00047
d D 7.7 89/09/06 11:21:21 mckusick 8 7
c install memfs
e
s 00001/00001/00046
d D 7.6 89/09/05 23:13:50 mckusick 7 6
c define memory filesystem
e
s 00001/00001/00046
d D 7.5 89/05/11 13:54:47 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00025/00029/00022
d D 7.4 88/10/25 19:07:19 bostic 5 4
c add man page, cleanup
e
s 00030/00040/00021
d D 7.3 87/06/02 21:53:11 bostic 4 2
c new template
e
s 00029/00039/00022
d R 7.3 87/06/02 20:45:49 bostic 3 2
c new template
e
s 00002/00002/00059
d D 7.2 87/01/08 22:55:05 karels 2 1
c typo
e
s 00061/00000/00000
d D 7.1 87/01/08 22:42:15 karels 1 0
c date and time created 87/01/08 22:42:15 by karels
e
u
U
t
T
I 1
D 12
#
D 5
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 5
I 5
# Copyright (c) 1987 The Regents of the University of California.
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
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
E 4
#
E 12
I 5
#	%W% (Berkeley) %G%
D 12
#
E 5
D 4
DESTDIR=
E 4
D 7
CFLAGS=	-O
E 7
I 7
CFLAGS=	-O -DMFS
E 7
D 4
LDFLAGS=	

E 4
I 4
LIBC=	/lib/libc.a
E 12
I 12

PROG=	newfs
D 19
CFLAGS+=-DMFS
E 12
E 4
D 15
SRCS=	newfs.c mkfs.c
E 15
I 15
SRCS=	dkcksum.c newfs.c mkfs.c
E 19
I 19
SRCS=	dkcksum.c getmntopts.c newfs.c mkfs.c
E 19
E 15
D 12
OBJS=	newfs.o mkfs.o
I 5
MAN=	newfs.0
E 12
I 12
MAN8=	newfs.0
I 19

MOUNT=	${.CURDIR}/../mount
CFLAGS+=-DMFS -I${MOUNT}
.PATH:	${MOUNT} ${.CURDIR}/../disklabel

E 19
LINKS=	${BINDIR}/newfs ${BINDIR}/mount_mfs
D 13
MLINKS=	mfs.8 newfs.8
E 13
I 13
D 17
MLINKS=	newfs.8 mfs.8
E 17
I 17
MLINKS=	newfs.8 mount_mfs.8 newfs.8 mfs.8
E 17
I 15
D 19
.PATH:	${.CURDIR}/../disklabel
E 19
E 15
E 13
E 12
E 5

D 12
all: newfs

D 2
newfs: ${OBJS}}
	cc ${LDFLAGS} ${CFLAGS} -o newfs ${OBJS}}
E 2
I 2
D 4
newfs: ${OBJS}
	cc ${LDFLAGS} ${CFLAGS} -o newfs ${OBJS}
E 4
I 4
newfs: ${OBJS} ${LIBC}
	${CC} ${CFLAGS} -o $@ ${OBJS}
E 4
E 2

D 4
install: all
	install -s newfs ${DESTDIR}/etc/newfs
E 4
I 4
D 5
clean: FRC
E 5
I 5
clean:
E 5
	rm -f ${OBJS} core newfs
E 4

D 4
clean:
	rm -f newfs *.o errs a.out core
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
E 4

D 4
lint:
	lint ${SRCS}
E 4
I 4
D 5
install: FRC
E 5
I 5
install: ${MAN}
E 5
D 6
	install -s -o bin -g bin -m 755 newfs ${DESTDIR}/etc/newfs
E 6
I 6
	install -s -o bin -g bin -m 755 newfs ${DESTDIR}/sbin/newfs
I 8
D 9
	rm -f ${DESTDIR}/sbin/memfs
	ln ${DESTDIR}/sbin/newfs ${DESTDIR}/sbin/memfs
E 9
I 9
D 11
	rm -f ${DESTDIR}/sbin/mfs
	ln ${DESTDIR}/sbin/newfs ${DESTDIR}/sbin/mfs
E 11
I 11
	rm -f ${DESTDIR}/sbin/mount_mfs
	ln ${DESTDIR}/sbin/newfs ${DESTDIR}/sbin/mount_mfs
E 11
E 9
E 8
E 6
I 5
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8
I 10
	rm -f ${DESTDIR}/usr/man/cat8/mfs.0
	ln ${DESTDIR}/usr/man/cat8/${MAN} ${DESTDIR}/usr/man/cat8/mfs.0
E 10
E 5
E 4

D 4
depend:
	cc -M ${INCPATH} ${SRCS} | \
	awk ' { if ($$1 != prev) { print rec; rec = $$0; prev = $$1; } \
		else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
		       else rec = rec " " $$2 } } \
	      END { print rec } ' > makedep
	echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	cp Makefile Makefile.bak
	ed - Makefile < eddep
	rm eddep makedep
	echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	echo '# see make depend above' >> Makefile
E 4
I 4
D 5
lint: FRC
E 5
I 5
lint: ${SRCS}
E 5
	lint ${CFLAGS} ${SRCS}
E 4

D 4
# DO NOT DELETE THIS LINE -- make depend uses it
E 4
I 4
D 5
tags: FRC
E 5
I 5
tags: ${SRCS}
E 5
	ctags ${SRCS}
E 12
I 12
.include <bsd.prog.mk>
E 12
E 4
D 5

I 4
FRC:
E 4

D 4
newfs.o: newfs.c /usr/include/sys/param.h /usr/include/machine/machparam.h
newfs.o: /usr/include/signal.h /usr/include/sys/types.h /usr/include/sys/stat.h
newfs.o: /usr/include/sys/fs.h /usr/include/sys/dir.h /usr/include/sys/ioctl.h
newfs.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
newfs.o: /usr/include/sys/disklabel.h /usr/include/sys/file.h
newfs.o: /usr/include/stdio.h /usr/include/ctype.h
E 4
I 4
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

newfs.o: newfs.c /usr/include/sys/param.h /usr/include/sys/types.h
newfs.o: /usr/include/signal.h /usr/include/machine/machparam.h
newfs.o: /usr/include/sys/stat.h /usr/include/sys/fs.h /usr/include/sys/dir.h
newfs.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
newfs.o: /usr/include/sys/ttydev.h /usr/include/sys/disklabel.h
newfs.o: /usr/include/sys/file.h /usr/include/stdio.h /usr/include/ctype.h
E 4
mkfs.o: mkfs.c /usr/include/stdio.h /usr/include/a.out.h
mkfs.o: /usr/include/sys/exec.h /usr/include/sys/param.h
D 4
mkfs.o: /usr/include/machine/machparam.h /usr/include/signal.h
mkfs.o: /usr/include/sys/types.h /usr/include/sys/inode.h /usr/include/sys/fs.h
mkfs.o: /usr/include/sys/dir.h /usr/include/sys/disklabel.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
E 4
I 4
mkfs.o: /usr/include/sys/types.h /usr/include/signal.h
mkfs.o: /usr/include/machine/machparam.h /usr/include/sys/inode.h
mkfs.o: /usr/include/sys/fs.h /usr/include/sys/dir.h
mkfs.o: /usr/include/sys/disklabel.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 5
E 4
E 1
