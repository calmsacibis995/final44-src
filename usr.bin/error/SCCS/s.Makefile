h10940
s 00000/00000/00006
d D 8.1 93/06/06 14:38:14 bostic 14 13
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00002/00005
d D 5.9 91/02/26 13:44:23 bostic 13 12
c rename the files to something approaching reasonable
e
s 00003/00045/00004
d D 5.8 90/05/11 13:50:44 bostic 12 11
c first pass for new make
e
s 00001/00001/00048
d D 5.7 89/05/10 22:21:16 bostic 11 10
c file reorg, pathnames.h, paths.h
e
s 00013/00032/00036
d D 5.6 88/10/19 09:04:54 bostic 10 9
c cleanup, add man page, move out dependencies
e
s 00010/00005/00058
d D 5.5 88/06/29 18:50:47 bostic 9 8
c install approved copyright notice
e
s 00009/00003/00054
d D 5.4 88/06/06 21:51:28 bostic 8 7
c written by Robert Henry; add Berkeley specific header
e
s 00041/00033/00016
d D 5.3 87/06/16 18:20:13 bostic 7 6
c new template
e
s 00002/00000/00047
d D 5.2 87/05/31 21:08:40 bostic 6 5
c added depend label
e
s 00005/00000/00042
d D 5.1 85/05/31 11:43:50 dist 5 4
c Add copyright
e
s 00001/00001/00041
d D 1.4 82/05/04 12:33:53 rrh 4 3
c Preserves links by writing to /tmp and copying.  Removed #ifdef ERNIE
e
s 00000/00000/00042
d D 1.3 82/01/22 17:55:32 rrh 3 2
c Re proceduralization in errortouch for clarity.
c Added -T (terse option)
c Added typedefs, and changed textual form of structures
c changed argument to vi to begin searching from line 1, instead of line $
e
s 00000/00003/00042
d D 1.2 80/10/19 00:15:38 bill 2 1
c rid duplicate clean entries
e
s 00045/00000/00000
d D 1.1 80/10/18 23:58:59 bill 1 0
c date and time created 80/10/18 23:58:59 by bill
e
u
U
t
T
I 1
D 12
#
I 5
D 7
# Copyright (c) 1980 Regents of the University of California.
E 7
I 7
# Copyright (c) 1987 Regents of the University of California.
E 7
D 8
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 8
I 8
# All rights reserved.
E 8
#
E 5
D 7
#	%W% (Berkeley) %G%
E 7
I 7
D 8
#	%W%	(Berkeley)	%G%
E 8
I 8
# Redistribution and use in source and binary forms are permitted
D 9
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 9
#
E 12
#	%W% (Berkeley) %G%
E 8
E 7
I 5
D 12
#
E 5
D 7
#
#	error.h			error header file
#	errorinput.c		does all of the input, and canonicalizes errors
#	errorpi.c		canonicalizes pi errors
#	errormain.c		main
#	errorsubr.c		does grotty subroutine work
#	errorfilter.c		"greps" out unwanted messages
#	errortouch.c		touches all mentioned files
#
E 7
I 7
D 10
CFLAGS=	-O -DDEBUG
E 10
I 10
CFLAGS=	-O
E 10
LIBC=	/lib/libc.a
E 12
I 12

PROG=	error
E 12
D 13
SRCS=	errormain.c errorinput.c errorpi.c errorsubr.c errorfilter.c \
	errortouch.c
E 13
I 13
SRCS=	main.c input.c pi.c subr.c filter.c touch.c
E 13
D 12
OBJS=	errormain.o errorinput.o errorpi.o errorsubr.o errorfilter.o \
	errortouch.o
I 10
MAN=	error.0
E 12
E 10
E 7

D 7
HDRS = error.h
PHDRS = $(HDRS)
SRCS = errormain.c errorinput.c errorpi.c errorsubr.c errorfilter.c errortouch.c
PSRCS = $(SRCS)
OBJS = errormain.o errorinput.o errorpi.o errorsubr.o errorfilter.o errortouch.o
E 7
I 7
D 12
all: error
E 7

D 4
DFLAGS = -DDEBUG -DERNIE
E 4
I 4
D 7
DFLAGS = -DDEBUG
E 4
CFLAGS =  -O $(DFLAGS)
E 7
I 7
D 10
error:	${OBJS} ${LIBC}
E 10
I 10
error: ${OBJS} ${LIBC}
E 10
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 7

D 7
LINTFLAGS = $(DFLAGS)
E 7
I 7
D 10
clean: FRC
E 10
I 10
clean:
E 10
	rm -f ${OBJS} core error
E 7

D 7
error:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o error
E 7
I 7
D 10
depend: FRC
E 10
I 10
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 10
	mkdep ${CFLAGS} ${SRCS}
E 7

D 7
$(OBJS): $(HDRS)
E 7
I 7
D 10
install: FRC
	install -s -o bin -g bin -m 755 error ${DESTDIR}/usr/ucb/error
E 10
I 10
install: ${MAN}
D 11
	install -s -o bin -g bin -m 755 error ${DESTDIR}/usr/ucb
E 11
I 11
	install -s -o bin -g bin -m 755 error ${DESTDIR}/usr/bin
E 11
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 10
E 7

D 7
install:
	install -s error $(DESTDIR)/usr/ucb
E 7
I 7
D 10
lint: FRC
E 10
I 10
lint: ${SRCS}
E 10
	lint ${CFLAGS} ${SRCS}
E 7

D 7
clean:
	rm -f error $(OBJS)
E 7
I 7
D 10
tags: FRC
E 10
I 10
tags: ${SRCS}
E 10
	ctags ${SRCS}
E 12
I 12
.include <bsd.prog.mk>
E 12
E 7
D 10

D 7
lint:	
	lint $(LINTFLAGS) $(SRCS)
E 7
I 7
FRC:
E 7

D 7
psrcs:
	echo $(PHDRS) $(PSRCS)
E 7
I 7
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 7

D 7
print:
	print $(PHDRS) $(PSRCS)
E 7
I 7
errormain.o: errormain.c /usr/include/stdio.h /usr/include/ctype.h
errormain.o: /usr/include/signal.h
errormain.o:error.h
errorinput.o: errorinput.c /usr/include/stdio.h /usr/include/ctype.h
errorinput.o:error.h
errorpi.o: errorpi.c /usr/include/stdio.h /usr/include/ctype.h
errorpi.o:error.h
errorsubr.o: errorsubr.c /usr/include/stdio.h /usr/include/ctype.h
errorsubr.o:error.h
errorfilter.o: errorfilter.c /usr/include/stdio.h /usr/include/ctype.h
errorfilter.o: /usr/include/pwd.h
errorfilter.o:error.h
errortouch.o: errortouch.c /usr/include/stdio.h /usr/include/ctype.h
errortouch.o: /usr/include/sys/types.h /usr/include/sys/stat.h
errortouch.o: /usr/include/signal.h
errortouch.o:error.h
E 7
I 6

D 7
depend:
E 7
I 7
# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 10
E 7
E 6
D 2

clean:
	rm $(OBJS) error
E 2
E 1
