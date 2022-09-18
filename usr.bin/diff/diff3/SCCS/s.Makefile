h28774
s 00000/00000/00011
d D 8.1 93/06/06 14:37:38 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00044/00004
d D 4.7 90/05/11 14:31:11 bostic 7 6
c first pass for new make
e
s 00001/00001/00047
d D 4.6 89/05/11 09:47:24 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00018/00051/00030
d D 4.5 89/03/06 12:27:52 bostic 5 4
c typo?
e
s 00064/00024/00017
d D 4.4 88/10/25 16:26:35 bostic 4 3
c add manual page, cleanup
e
s 00036/00010/00005
d D 4.3 87/06/18 15:44:41 bostic 3 2
c new template
e
s 00003/00001/00012
d D 4.2 87/05/31 21:28:23 bostic 2 1
c added depend label
e
s 00013/00000/00000
d D 4.1 83/02/10 21:00:45 shannon 1 0
c date and time created 83/02/10 21:00:45 by shannon
e
u
U
t
T
I 1
D 3
#	%M%	%I%	%E%
E 3
I 3
D 4
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W%	(Berkeley)	%G%
#
E 4
I 4
D 5
autoconfig
backingstore
badsectforw
bdp
bottomhalf
busadapter
byte
capability
cbreak
character
cookedmode
demandpage
egid
erasechar
euid
fodkluster
gid
hardlimit
hardlock
interruptvectab
iopage
ipl
killchar
kluster
ldpctx
mmapioarch
msl
nbio
page
pagedaemon
panic
psn
rawmode
recvwindow
rgid
ruid
secondstorage
sharedtextseg
sigdrivenio
slidingwindowscheme
sndwindow
stickytext
svpctx
swapper
syspagetab
text
tophalf
uid
unbuffered
usrrequest
worderasechar
E 5
I 5
D 7
#
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
#
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
#
E 7
#	%W% (Berkeley) %G%
D 7
#
E 5
E 4
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	diff3.c
D 4
OBJS=	diff3.o
E 4
I 4
OBJS=
MAN=	diff3.0
E 7
E 4
E 3

D 3
CFLAGS=-O
E 3
I 3
D 7
all: diff3
E 7
I 7
PROG=	diff3
BINDIR=	/usr/libexec
E 7
E 3

D 3
diff3: diff3.o
	cc -o diff3 diff3.o
E 3
I 3
D 4
diff3: diff3.c ${LIBC}
	${CC} ${CFLAGS} -o $@ diff3.c
E 4
I 4
D 7
diff3: ${LIBC}
	${CC} ${CFLAGS} -o $@ $@.c
E 7
I 7
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/diff3.sh ${DESTDIR}/usr/bin/${PROG}
E 7
E 4
E 3

D 3
install: diff3
	install -s diff3 $(DESTDIR)/usr/lib
	install -c diff3.sh $(DESTDIR)/usr/bin/diff3
E 3
I 3
D 4
clean: FRC
E 4
I 4
D 7
clean:
E 4
	rm -f ${OBJS} core diff3
E 3

D 3
clean:
D 2
	rm -f diff3.o diff3	
E 2
I 2
	rm -f diff3.o diff3
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
	mkdep -p ${CFLAGS} ${SRCS}
E 3

D 3
depend:
E 3
I 3
D 4
install: FRC
E 4
I 4
install: ${MAN}
E 4
D 6
	install -s -o bin -g bin -m 755 diff3 $(DESTDIR)/usr/lib/diff3
E 6
I 6
	install -s -o bin -g bin -m 755 diff3 $(DESTDIR)/usr/libexec/diff3
E 6
	install -c -o bin -g bin -m 755 diff3.sh $(DESTDIR)/usr/bin/diff3
I 4
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 4

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
E 7
I 7
.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 7
D 4

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

diff3: diff3.c /usr/include/stdio.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 3
E 2
E 1
