h29591
s 00001/00001/00018
d D 4.14 91/11/13 08:47:05 bostic 14 13
c as moved into src/old
e
s 00002/00000/00017
d D 4.13 90/06/24 15:11:33 bostic 13 12
c depend needs instrs.c2
e
s 00001/00001/00016
d D 4.12 90/06/17 14:37:42 bostic 12 11
c moved to libexec/pcc
e
s 00003/00002/00014
d D 4.11 90/05/29 20:21:34 bostic 11 10
c needs -I., mkdep will do the instrs.c2 dependency
e
s 00011/00036/00005
d D 4.10 90/05/11 12:54:38 bostic 10 9
c first pass for new make
e
s 00001/00001/00040
d D 4.9 89/07/30 09:37:18 bostic 9 8
c reorg
e
s 00002/00002/00039
d D 4.8 89/05/11 14:34:43 bostic 8 7
c file reorg, pathnames.h, paths.h
e
s 00008/00016/00033
d D 4.7 89/03/06 08:40:41 bostic 7 6
c add cleandir label, cleanup
e
s 00038/00021/00011
d D 4.6 87/06/06 15:42:57 bostic 6 5
c new template
e
s 00001/00001/00031
d D 4.5 87/05/28 20:24:15 bostic 5 4
c wrong as directory
e
s 00001/00001/00031
d D 4.4 85/07/06 12:06:37 bloom 4 3
c allow easier repositioning of assembler src
e
s 00003/00003/00029
d D 4.3 85/03/19 10:50:39 ralph 3 2
c Turn on optimization for gosh sakes.
e
s 00001/00001/00031
d D 4.2 82/10/27 13:47:54 sam 2 1
c d2 causes "word displacement overflow" from ld
e
s 00032/00000/00000
d D 4.1 82/10/27 13:46:25 sam 1 0
c date and time created 82/10/27 13:46:25 by sam
e
u
U
t
T
I 1
D 6
#	%W%	(Berkeley)	%E%
E 6
D 10
#
D 2
CFLAGS=-c -d2 -w -DCOPYCODE -DC2
E 2
I 2
D 3
CFLAGS=-c -w -DCOPYCODE -DC2
E 3
I 3
D 6
CFLAGS=-DCOPYCODE -DC2 -O
E 3
E 2
LDFLAGS=
D 5
ASDIR = /usr/src/bin/as
E 5
I 5
ASDIR = /usr/src/bin/as/as.${MACHINE}
E 6
I 6
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W%	(Berkeley)	%G%
#
CFLAGS=	-DCOPYCODE -DC2 -O
D 8
ASDIR=	../../../bin/as/as.${MACHINE}
E 8
I 8
D 9
ASDIR=	../../../usr.bin/as/as.${MACHINE}
E 9
I 9
ASDIR=	../../../pgrm/as/as.${MACHINE}
E 10
I 10
#	%W% (Berkeley) %G%

PROG=	c2
E 10
E 9
E 8
SRCS=	c20.c c21.c c22.c
D 10
OBJS=	c20.o c21.o c22.o
E 10
I 10
D 11
CFLAGS+=-DCOPYCODE -DC2
E 11
I 11
CFLAGS+=-DCOPYCODE -DC2 -I.
E 11
D 12
ASDIR=	${.CURDIR}/../../pgrm/as.${MACHINE}
E 12
I 12
D 14
ASDIR=	${.CURDIR}/../../../pgrm/as.${MACHINE}
E 14
I 14
ASDIR=	${.CURDIR}/../../as.${MACHINE}
E 14
E 12
NOMAN=	noman
I 11
CLEANFILES=instrs.c2
E 11
E 10
E 6
E 5

D 6
SRCS = makefile c2.h c20.c c21.c c22.c
E 6
I 6
D 10
all: c2
E 10
I 10
D 11
c22.o: instrs.c2
E 11
I 11
c22.o:
E 11
	${CC} ${CFLAGS} -R -c ${.IMPSRC}
E 10
E 6

D 6
c2:	c20.o c21.o c22.o
D 3
	$(CC) $(LDFLAGS) -z -o c2 c2?.o
E 3
I 3
	$(CC) $(LDFLAGS) -o c2 c2?.o
E 6
I 6
D 10
c2: ${OBJS} ${LIBC}
	${CC} -o $@ ${OBJS}
E 6
E 3

D 6
c20.o:	c20.c c2.h
c21.o:	c21.c c2.h
c22.o:  c22.c c2.h instrs.c2
D 3
	$(CC) $(CFLAGS) -R c22.c
E 3
I 3
	$(CC) $(CFLAGS) -R -c c22.c
E 6
I 6
c22.o: c22.c c2.h instrs.c2
	${CC} ${CFLAGS} -R -c c22.c
E 6
E 3

E 10
D 6
instrs.c2: $(ASDIR)/instrs
D 4
	(echo FLAVOR C2 ; cat $(ASDIR)/instrs) | awk -f /usr/src/bin/as/instrs > instrs.c2
E 4
I 4
	(echo FLAVOR C2 ; cat $(ASDIR)/instrs) | awk -f $(ASDIR)/instrs > instrs.c2
E 6
I 6
instrs.c2: ${ASDIR}/instrs
D 10
	(echo FLAVOR C2 ; cat ${ASDIR}/instrs) | awk -f ${ASDIR}/instrs > instrs.c2
E 10
I 10
	(echo FLAVOR C2 ; cat ${ASDIR}/instrs) | \
	    awk -f ${ASDIR}/instrs > instrs.c2
E 10
E 6
E 4

D 10
clean:
D 6
	rm -f *.o *.s 
E 6
I 6
	rm -f *.o *.s c2
E 6

D 6
install: c2
	install -s c2 $(DESTDIR)/lib
E 6
I 6
D 7
install:
E 7
I 7
cleandir: clean
	rm -f ${MAN} tags .depend

install: ${MAN}
E 7
D 8
	install -o bin -g bin -m 755 -s c2 ${DESTDIR}/lib/c2
E 8
I 8
	install -o bin -g bin -m 755 -s c2 ${DESTDIR}/usr/libexec/c2
E 8
E 6

D 6
sources: $(SRCS)
E 6
I 6
D 7
tags:
E 7
I 7
tags: ${SRCS}
E 7
	ctags ${SRCS}
E 6

D 6
$(ASDIR)/instrs:
	(cd $(ASDIR); sccs get instrs)
E 6
I 6
D 7
depend:
E 7
I 7
depend: ${SRCS}
E 7
	mkdep ${CFLAGS} ${SRCS}
E 6

D 6
$(SRCS):
	sccs get $@
E 6
I 6
D 7
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 7
I 7
lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}
E 7

E 10
I 10
.include <bsd.prog.mk>
I 13

.depend: instrs.c2
E 13
E 10
D 7
c20.o: c20.c
c20.o:c2.h
c20.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/sys/types.h
c21.o: c21.c
c21.o:c2.h
c21.o: /usr/include/stdio.h /usr/include/ctype.h
c22.o: c22.c
c22.o:c2.h
c22.o:./instrs.c2

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 7
E 6
E 1
