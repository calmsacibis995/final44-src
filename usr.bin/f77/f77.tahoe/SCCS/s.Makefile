h44196
s 00005/00038/00003
d D 5.3 90/06/17 18:49:04 bostic 3 2
c pmake style make, reorg the directories
e
s 00009/00021/00032
d D 5.2 89/05/10 22:21:56 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00053/00000/00000
d D 5.1 87/12/12 17:39:41 bostic 1 0
c date and time created 87/12/12 17:39:41 by bostic
e
u
U
t
T
I 1
D 3
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
#
E 3
#	%W% (Berkeley) %G%
D 3
#
CFLAGS=	-DHERE=TAHOE -DTARGET=TAHOE -DFAMILY=PCC -DUCBVAXASM \
	-DUCBPASS2 -O -I$(INCLDIR)/usr/include -I../include
LIBC=	/lib/libc.a
SRCS=	f77.c
OBJS=	f77.o
E 3

D 3
all: f77
E 3
I 3
PROG=	f77
CFLAGS+=-DHERE=TAHOE -DTARGET=TAHOE -DFAMILY=PCC -DUCBVAXASM -DUCBPASS2 \
	-I${.CURDIR}/../include.tahoe
BINDIR=	/usr/bin
E 3

D 3
f77: ${SRCS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${SRCS}

D 2
clean: FRC
E 2
I 2
clean:
E 2
	rm -f ${OBJS} core f77

D 2
depend: FRC
E 2
I 2
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 2
	mkdep -p ${CFLAGS} ${SRCS}

D 2
install: FRC
	install -s -o bin -g bin -m 755 f77 ${DESTDIR}/usr/bin/f77
E 2
I 2
install: ${MAN}
	install -s -o bin -g bin -m 755 f77 ${DESTDIR}/usr/bin
E 2

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
E 3
I 3
.include <bsd.prog.mk>
E 3
D 2

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

f77: f77.c /usr/include/stdio.h /usr/include/sys/types.h
f77: /usr/include/sys/stat.h /usr/include/ctype.h /usr/include/signal.h
f77: /usr/include/machine/trap.h /usr/include/sys/time.h /usr/include/time.h
f77: /usr/include/sys/resource.h /usr/include/sys/wait.h
f77: /usr/include/machine/machparam.h ../include/defines.h
f77: ../include/machdefs.h drivedefs.h ../include/version.h
f77: /usr/include/errno.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 2
E 1
