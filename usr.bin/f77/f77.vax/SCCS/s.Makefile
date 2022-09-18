h43916
s 00005/00040/00003
d D 5.5 90/06/17 18:30:07 bostic 5 4
c redo makefiles, reorg directories
e
s 00003/00000/00040
d D 5.4 89/07/30 13:53:48 bostic 4 3
c add cleandir label
e
s 00000/00013/00040
d D 5.3 89/07/30 13:37:00 bostic 3 2
c rip out dependency list
e
s 00001/00001/00052
d D 5.2 89/05/10 22:23:17 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00053/00000/00000
d D 5.1 87/12/12 17:38:54 bostic 1 0
c date and time created 87/12/12 17:38:54 by bostic
e
u
U
t
T
I 1
D 5
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
E 5
#	%W% (Berkeley) %G%
D 5
#
CFLAGS=	-DHERE=VAX -DTARGET=VAX -DFAMILY=PCC -DUCBVAXASM -DUCBPASS2 \
	-O -I../include
LIBC=	/lib/libc.a
SRCS=	f77.c
OBJS=	f77.o
E 5

D 5
all: f77
E 5
I 5
PROG=	f77
CFLAGS+=-DHERE=VAX -DTARGET=VAX -DFAMILY=PCC -DUCBVAXASM -DUCBPASS2 \
	-I${.CURDIR}/../include.vax
BINDIR=	/usr/bin
E 5

D 5
f77: ${SRCS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${SRCS}

clean: FRC
	rm -f ${OBJS} core f77

I 4
cleandir: clean
	rm -f tags .depend ${MAN}

E 4
depend: FRC
	mkdep -p ${CFLAGS} ${SRCS}

install: FRC
D 2
	install -s -o bin -g bin -m 755 f77 ${DESTDIR}/usr/bin/f77
E 2
I 2
	install -s -o bin -g bin -m 755 f77 ${DESTDIR}/usr/bin
E 2

lint: FRC
	lint ${CFLAGS} ${SRCS}

tags: FRC
	ctags ${SRCS}

FRC:
E 5
I 5
.include <bsd.prog.mk>
E 5
D 3

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
E 3
E 1
