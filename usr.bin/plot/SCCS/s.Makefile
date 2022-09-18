h35782
s 00000/00000/00107
d D 8.1 93/06/06 15:55:05 bostic 22 21
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00105
d D 4.17 90/06/24 22:44:06 bostic 21 20
c don't make depend more than once
e
s 00003/00002/00103
d D 4.16 90/06/24 14:59:18 bostic 20 19
c programs depend on libc, make clean better
e
s 00002/00002/00103
d D 4.15 90/06/22 19:03:13 bostic 19 18
c LINT, CTAGS not defined
e
s 00075/00067/00031
d D 4.14 90/05/11 14:26:27 bostic 18 17
c first pass for new make
e
s 00016/00016/00082
d D 4.13 89/07/24 16:57:05 bostic 17 16
c move to subdirectory of /usr/libexec
e
s 00001/00003/00097
d D 4.12 89/05/11 10:02:52 bostic 16 15
c file reorg, pathnames.h, paths.h
e
s 00025/00027/00075
d D 4.11 88/10/25 15:11:22 bostic 15 14
c add manual page, cleanup
e
s 00065/00031/00037
d D 4.10 87/12/01 20:45:05 bostic 14 11
c new template
e
s 00065/00031/00037
d R 4.10 87/06/19 07:14:46 bostic 13 11
c new template
e
s 00066/00032/00036
d R 4.10 87/06/18 22:36:53 bostic 12 11
c new template
e
s 00002/00000/00066
d D 4.9 87/05/31 21:31:36 bostic 11 10
c added depend label
e
s 00004/00001/00062
d D 4.8 86/08/29 15:30:04 sklower 10 9
c add entry for grn output "driver"
e
s 00004/00013/00059
d D 4.7 85/11/11 16:27:07 mckusick 9 8
c update install script
e
s 00004/00001/00068
d D 4.6 85/09/21 15:19:18 sam 8 7
c add imagen
e
s 00005/00001/00064
d D 4.5 85/01/04 14:08:40 jak 7 5
c add t4013 module for tek 4013.
e
s 00000/00000/00065
d R 4.5 85/01/04 14:00:47 jak 6 5
c add t4013 for tektronix 4013.
e
s 00038/00004/00027
d D 4.4 83/11/11 15:02:34 ralph 5 4
c added new devices.
e
s 00011/00005/00020
d D 4.3 83/07/04 11:06:31 sam 4 3
c forgot to update after libary changes
e
s 00001/00001/00024
d D 4.2 83/03/24 09:35:15 ralph 3 2
c fixed install dependency
e
s 00012/00009/00013
d D 4.1 83/03/10 15:36:17 ralph 2 1
c updated vplot entry
e
s 00022/00000/00000
d D 1.1 83/03/10 15:31:21 ralph 1 0
c date and time created 83/03/10 15:31:21 by ralph
e
u
U
t
T
I 2
D 4
#
E 4
D 14
#	%M%	%I%	%E%
E 14
D 18
#
I 14
D 15
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 15
I 15
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 15
#
D 15
#	%W%	(Berkeley)	%G%
E 15
I 15
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
E 15
#
E 18
I 15
#	%W% (Berkeley) %G%
D 18
#
E 15
E 14
E 2
I 1
D 4
all: tek t300 t300s t450 vplot
E 4
I 4
CFLAGS=	-O
I 14
LIBC=	/lib/libc.a
SRCS=	atoplot.c chrtab.c crtdriver.c crtplot.c debug.c driver.c plottoa.c
OBJS=	atoplot.o chrtab.o crtdriver.o crtplot.o debug.o driver.o plottoa.o
E 14
D 5
ALL=	tek t300 t300s t450 vplot
E 5
I 5
D 7
ALL=	tek t300 t300s t450 aedplot bgplot crtplot dumbplot gigiplot \
E 7
I 7
ALL=	tek t4013 t300 t300s t450 aedplot bgplot crtplot dumbplot gigiplot \
E 18
I 18

PROGS=	tek t4013 t300 t300s t450 aedplot bgplot crtplot dumbplot gigiplot \
E 18
E 7
D 8
	hpplot hp7221plot debug atoplot plottoa
E 8
I 8
D 9
	hpplot hp7221plot implot debug atoplot plottoa
E 9
I 9
D 10
	hpplot hp7221plot implot atoplot plottoa
E 10
I 10
	hpplot hp7221plot implot atoplot plottoa grnplot
I 15
D 18
MAN=	plot.0
E 18
I 18
SRCS=	atoplot.c chrtab.c crtdriver.c crtplot.c debug.c driver.c plottoa.c
BINDIR=	/usr/bin
MAN1=	plot.0
E 18
E 15
E 10
E 9
E 8
E 5
E 4

I 4
D 9
all:	${ALL}
E 9
I 9
D 14
all:	${ALL} debug
E 14
I 14
D 18
all: ${ALL} debug
E 18
I 18
LIB300=		/usr/lib/lib300.a
LIB300s=	/usr/lib/lib300s.a
LIB4013=	/usr/lib/lib4013.a
LIB4014=	/usr/lib/lib4014.a
LIB450=		/usr/lib/lib450.a
LIBCOMPAT=	/usr/lib/libcompat.a
LIBCURSES=	/usr/lib/libcurses.a
LIBM=		/usr/lib/libm.a
LIBPLOT2648=	/usr/lib/libplot2648.a
LIBPLOT7221=	/usr/lib/libplot7221.a
LIBPLOT=	/usr/lib/libplot.a
LIBPLOTAED=	/usr/lib/libplotaed.a
LIBPLOTBG=	/usr/lib/libplotbg.a
LIBPLOTDUMB=	/usr/lib/libplotdumb.a
LIBPLOTGIGI=	/usr/lib/libplotgigi.a
LIBPLOTGRN=	/usr/lib/libplotgrn.a
LIBPLOTIMAGEN=	/usr/lib/libplotimagen.a
LIBTERMCAP=	/usr/lib/libtermcap.a
E 18
E 14
E 9

E 4
D 14
tek:	driver.o
	cc -o tek  driver.o -l4014 -lm
E 14
I 14
D 18
tek: driver.o
D 17
	${CC} ${CFLAGS} -o $@ driver.o -l4014 -lm
E 17
I 17
	${CC} ${CFLAGS} -o $@ driver.o -l4014 -lm -lcompat
E 18
I 18
all: ${PROGS} ${MAN1}
E 18
E 17
E 14
I 4

I 7
D 14
t4013:	driver.o
	cc -o t4013  driver.o -l4013 -lm
E 14
I 14
D 18
t4013: driver.o
D 17
	${CC} ${CFLAGS} -o $@ driver.o -l4013 -lm
E 17
I 17
	${CC} ${CFLAGS} -o $@ driver.o -l4013 -lm -lcompat
E 18
I 18
aedplot: driver.o ${LIBPLOTAED} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} driver.o -lplotaed -lcompat
E 18
E 17
E 14

E 7
E 4
D 14
t300:	driver.o 
	cc -o t300 driver.o -l300 -lm
E 14
I 14
D 18
t300: driver.o
D 17
	${CC} ${CFLAGS} -o $@ driver.o -l300 -lm
E 17
I 17
	${CC} ${CFLAGS} -o $@ driver.o -l300 -lm -lcompat
E 18
I 18
atoplot: atoplot.c ${LIBPLOT} ${LIBM} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} ${.CURDIR}/atoplot.c -lplot -lm -lcompat
E 18
E 17
E 14
I 4

E 4
D 14
t300s:	driver.o 
	cc -o t300s driver.o -l300s -lm
E 14
I 14
D 18
t300s: driver.o
D 17
	${CC} ${CFLAGS} -o $@ driver.o -l300s -lm
E 17
I 17
	${CC} ${CFLAGS} -o $@ driver.o -l300s -lm -lcompat
E 18
I 18
bgplot: driver.o ${LIBPLOTBG} ${LIBM} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} driver.o -lplotbg -lm -lcompat
E 18
E 17
E 14
I 4

E 4
D 14
t450:	driver.o 
	cc -o t450 driver.o -l450 -lm
E 14
I 14
D 18
t450: driver.o
D 17
	${CC} ${CFLAGS} -o $@ driver.o -l450 -lm
E 17
I 17
	${CC} ${CFLAGS} -o $@ driver.o -l450 -lm -lcompat
E 18
I 18
crtplot: crtdriver.o crtplot.o ${LIBCURSES} ${LIBTERMCAP} ${LIBM} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} crtdriver.o crtplot.o -lcurses \
	    -ltermcap -lm -lcompat
E 18
E 17
E 14
D 2
vplot:	chrtab.o vplot.o
	cc -o vplot vplot.o chrtab.o
E 2
I 2
D 4
vplot:	vplot.c
	cc -o vplot vplot.c
E 4
E 2

I 4
D 5
vplot:	vplot.o chrtab.o
	cc -o vplot vplot.o chrtab.o
E 5
I 5
D 18
aedplot: driver.o
D 14
	cc -o aedplot driver.o -lplotaed
E 14
I 14
D 17
	${CC} ${CFLAGS} -o $@ driver.o -lplotaed
E 17
I 17
	${CC} ${CFLAGS} -o $@ driver.o -lplotaed -lcompat
E 18
I 18
debug:
	${CC} ${CFLAGS} -o ${.TARGET} ${.CURDIR}/debug.c
E 18
E 17
E 14
E 5

I 5
D 18
bgplot: driver.o
D 14
	cc -o bgplot driver.o -lplotbg -lm
E 14
I 14
D 17
	${CC} ${CFLAGS} -o $@ driver.o -lplotbg -lm
E 17
I 17
	${CC} ${CFLAGS} -o $@ driver.o -lplotbg -lm -lcompat
E 18
I 18
dumbplot: driver.o ${LIBPLOTDUMB} ${LIBTERMCAP} ${LIBM} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} driver.o -lplotdumb -ltermcap \
	    -lm -lcompat
E 18
E 17
E 14

D 18
crtplot: crtdriver.o crtplot.o
D 14
	cc -o crtplot crtdriver.o crtplot.o -lcurses -ltermcap -lm
E 14
I 14
D 17
	${CC} ${CFLAGS} -o $@ crtdriver.o crtplot.o -lcurses -ltermcap -lm
E 17
I 17
	${CC} ${CFLAGS} -o $@ crtdriver.o crtplot.o -lcurses -ltermcap -lm -lcompat
E 18
I 18
gigiplot: driver.o ${LIBPLOTGIGI} ${LIBM} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} driver.o -lplotgigi -lm -lcompat
E 18
E 17
E 14

D 18
dumbplot: driver.o
D 14
	cc -o dumbplot driver.o -lplotdumb -ltermcap -lm
E 14
I 14
D 17
	${CC} ${CFLAGS} -o $@ driver.o -lplotdumb -ltermcap -lm
E 17
I 17
	${CC} ${CFLAGS} -o $@ driver.o -lplotdumb -ltermcap -lm -lcompat
E 18
I 18
grnplot: driver.o ${LIBPLOTGRN} ${LIBM} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} driver.o -lplotgrn -lm -lcompat
E 18
E 17
E 14

D 18
gigiplot: driver.o
D 14
	cc -o gigiplot driver.o -lplotgigi -lm
E 14
I 14
D 17
	${CC} ${CFLAGS} -o $@ driver.o -lplotgigi -lm
E 17
I 17
	${CC} ${CFLAGS} -o $@ driver.o -lplotgigi -lm -lcompat
E 18
I 18
hp7221plot: driver.o ${LIBPLOT7221} ${LIBM} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} driver.o -lplot7221 -lm -lcompat
E 18
E 17
E 14

D 18
hpplot: driver.o
D 14
	cc -o hpplot driver.o -lplot2648 -lm
E 14
I 14
D 17
	${CC} ${CFLAGS} -o $@ driver.o -lplot2648 -lm
E 17
I 17
	${CC} ${CFLAGS} -o $@ driver.o -lplot2648 -lm -lcompat
E 18
I 18
hpplot: driver.o ${LIBPLOT2648} ${LIBM} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} driver.o -lplot2648 -lm -lcompat
E 18
E 17
E 14

D 18
hp7221plot: driver.o
D 14
	cc -o hp7221plot driver.o -lplot7221 -lm
E 14
I 14
D 17
	${CC} ${CFLAGS} -o $@ driver.o -lplot7221 -lm
E 17
I 17
	${CC} ${CFLAGS} -o $@ driver.o -lplot7221 -lm -lcompat
E 18
I 18
implot: driver.o ${LIBPLOTIMAGEN} ${LIBM} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} driver.o -lplotimagen -lm -lcompat
E 18
E 17
E 14
I 8

D 18
implot: driver.o
D 14
	cc -o implot driver.o -lplotimagen -lm
E 14
I 14
D 17
	${CC} ${CFLAGS} -o $@ driver.o -lplotimagen -lm
E 17
I 17
	${CC} ${CFLAGS} -o $@ driver.o -lplotimagen -lm -lcompat
E 18
I 18
plottoa: plottoa.c
	${CC} ${CFLAGS} -o ${.TARGET} ${.CURDIR}/plottoa.c
E 18
E 17
E 14
E 8

D 18
atoplot: atoplot.o
D 14
	cc -o atoplot atoplot.o -lplot -lm
E 14
I 14
D 17
	${CC} ${CFLAGS} -o $@ atoplot.o -lplot -lm
E 17
I 17
	${CC} ${CFLAGS} -o $@ atoplot.o -lplot -lm -lcompat
E 18
I 18
t300: driver.o  ${LIB300} ${LIBM} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} driver.o -l300 -lm -lcompat
E 18
E 17
E 14

D 18
plottoa: plottoa.o
D 14
	cc -o plottoa plottoa.o
E 14
I 14
	${CC} ${CFLAGS} -o $@ plottoa.o
E 18
I 18
t300s: driver.o ${LIB300S} ${LIBM} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} driver.o -l300s -lm -lcompat
E 18
E 14
I 10

D 18
grnplot: driver.o
D 14
	cc -o grnplot driver.o -lplotgrn -lm
E 14
I 14
D 17
	${CC} ${CFLAGS} -o $@ driver.o -lplotgrn -lm
E 17
I 17
	${CC} ${CFLAGS} -o $@ driver.o -lplotgrn -lm -lcompat
E 18
I 18
t4013: driver.o ${LIB4013} ${LIBM} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} driver.o -l4013 -lm -lcompat
E 18
E 17
E 14
E 10

D 18
debug: debug.o
D 14
	cc -o debug debug.o
E 14
I 14
	${CC} ${CFLAGS} -o $@ debug.o
E 18
I 18
t450: driver.o  ${LIB450} ${LIBM} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} driver.o -l450 -lm -lcompat
E 18
E 14

I 18
tek: driver.o ${LIB4014} ${LIBM} ${LIBCOMPAT}
	${CC} ${CFLAGS} -o ${.TARGET} driver.o -l4014 -lm -lcompat

E 18
E 5
E 4
D 3
install:
E 3
I 3
D 14
install: all
E 3
D 2
	install -s tek $(DESTDIR)/usr/bin
	install -s t300 $(DESTDIR)/usr/bin
	install -s t300s $(DESTDIR)/usr/bin
	install -s t450 $(DESTDIR)/usr/bin
	install -s vplot $(DESTDIR)/usr/bin
	install -c plot.sh $(DESTDIR)/usr/bin/plot
E 2
I 2
D 9
	install -s tek ${DESTDIR}/usr/bin
I 7
	install -s t4013 ${DESTDIR}/usr/bin
E 7
	install -s t300 ${DESTDIR}/usr/bin
	install -s t300s ${DESTDIR}/usr/bin
	install -s t450 ${DESTDIR}/usr/bin
D 5
	install -s vplot ${DESTDIR}/usr/bin
E 5
I 5
	install -s aedplot $(DESTDIR)/usr/bin
	install -s bgplot ${DESTDIR}/usr/bin
	install -s crtplot ${DESTDIR}/usr/bin
	install -s dumbplot ${DESTDIR}/usr/bin
	install -s gigiplot ${DESTDIR}/usr/bin
	install -s hpplot ${DESTDIR}/usr/bin
E 9
I 9
	-for i in ${ALL}; do \
		(install -s $$i ${DESTDIR}/usr/bin/$$i); done
E 9
E 5
	install -c plot.sh ${DESTDIR}/usr/bin/plot
E 14
I 14
D 15
clean: FRC
E 15
I 15
clean:
E 15
D 18
	rm -f ${OBJS} ${ALL} debug core
E 18
I 18
D 20
	rm -f a.out Errs errs mklog core ${PROGS} driver.o crtdriver.o \
	    crtplot.o debug
E 20
I 20
	rm -f a.out Errs errs mklog core ${PROGS} ${SRCS:.c=.o} debug
E 20
E 18
E 14
I 5

E 5
E 2
D 14
clean:
D 2
	rm -f *.o tek t300 t300s t450
E 2
I 2
D 4
	rm -f *.o tek t300 t300s t450 vplot
E 4
I 4
	rm -f *.o ${ALL} a.out core errs
E 14
I 14
D 15
depend: FRC
E 15
I 15
cleandir: clean
D 18
	rm -f ${MAN} tags .depend
E 18
I 18
	rm -f ${MAN1} ${.CURDIR}/tags .depend
E 18

D 21
depend: ${SRCS}
E 21
I 21
depend: .depend
.depend: ${SRCS}
E 21
E 15
D 18
	mkdep ${CFLAGS} ${SRCS}
E 18
I 18
	mkdep ${CFLAGS:M-[ID]*} ${.ALLSRC}
E 18
E 14
I 11

D 14
depend:
E 14
I 14
D 15
install: FRC
E 15
I 15
D 18
install: ${MAN}
E 15
D 16
	for i in ${ALL}; do \
		(install -s -o bin -g bin -m 755 $$i ${DESTDIR}/usr/bin/$$i); \
	done
E 16
I 16
D 17
	install -s -o bin -g bin -m 755 ${ALL} ${DESTDIR}/usr/libexec
E 17
I 17
	install -s -o bin -g bin -m 755 ${ALL} ${DESTDIR}/usr/libexec/plot
E 17
E 16
	install -c -o bin -g bin -m 755 plot.sh ${DESTDIR}/usr/bin/plot
I 15
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 18
I 18
install: maninstall
	install ${STRIP} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} ${PROGS} \
	    ${DESTDIR}/usr/libexec/plot
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} ${.CURDIR}/plot.sh \
	    ${DESTDIR}${BINDIR}/plot
E 18
E 15

D 15
lint: FRC
E 15
I 15
lint: ${SRCS}
E 15
D 18
	lint ${CFLAGS} ${SRCS}
E 18
I 18
D 19
	${LINT} ${LINTFLAGS} ${CFLAGS} ${.ALLSRC}
E 19
I 19
	lint ${LINTFLAGS} ${CFLAGS} ${.ALLSRC}
E 19
E 18

D 15
tags: FRC
E 15
I 15
tags: ${SRCS}
E 15
D 18
	ctags ${SRCS}
E 18
I 18
D 19
	${CTAGS} -f ${.CURDIR}/tags ${.ALLSRC}
E 19
I 19
	ctags -f ${.CURDIR}/tags ${.ALLSRC}
I 20

${PROGS}: ${LIBC}
E 20
E 19

.include <bsd.prog.mk>
E 18
D 15

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

atoplot.o: atoplot.c /usr/include/stdio.h
chrtab.o: chrtab.c
crtdriver.o: crtdriver.c /usr/include/stdio.h
crtplot.o: crtplot.c /usr/include/curses.h /usr/include/stdio.h
crtplot.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
crtplot.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
crtplot.o: /usr/include/math.h /usr/include/signal.h
debug.o: debug.c /usr/include/stdio.h
driver.o: driver.c /usr/include/stdio.h
plottoa.o: plottoa.c /usr/include/stdio.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 15
E 14
E 11
E 4
E 2
E 1
