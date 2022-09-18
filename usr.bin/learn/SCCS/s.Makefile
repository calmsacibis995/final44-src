h33998
s 00000/00000/00006
d D 8.1 93/06/06 15:03:37 bostic 15 14
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00004/00006
d D 5.1 90/05/24 16:03:18 bostic 14 13
c don't remove anything, no longer necessary
e
s 00006/00078/00004
d D 4.12 90/05/11 16:01:20 bostic 13 12
c first pass for new make
e
s 00012/00012/00070
d D 4.11 89/05/10 22:47:06 bostic 12 11
c file reorg, pathnames.h, paths.h
e
s 00040/00041/00042
d D 4.10 88/10/25 14:58:21 bostic 11 10
c fix copyright, move usr.lib/learn here, add manual page and new labels
e
s 00002/00002/00081
d D 4.9 88/06/10 14:32:00 bostic 10 9
c don't destructively install getline.c and getnum.c
e
s 00010/00003/00073
d D 4.8 88/06/08 15:20:15 jak 9 8
c getline.c and getnum.c from C lessons moved into src directory
e
s 00001/00000/00075
d D 4.7 87/09/11 14:05:31 jak 8 7
c added chmod to Init files since many installed systems break w/o it.
e
s 00061/00044/00014
d D 4.6 87/06/18 17:59:49 bostic 7 6
c new template
e
s 00002/00000/00056
d D 4.5 87/05/31 21:29:55 bostic 6 5
c added depend label
e
s 00003/00006/00053
d D 4.4 86/05/15 17:57:51 bloom 5 4
c updates from John Kunze
e
s 00001/00001/00058
d D 4.3 83/06/19 11:22:02 root 4 3
c fix instlal
e
s 00023/00026/00036
d D 4.2 83/04/26 01:45:41 mckusick 3 1
c 
e
s 00023/00026/00036
d R 4.2 83/04/25 23:58:28 mckusick 2 1
c 
e
s 00062/00000/00000
d D 4.1 83/02/24 12:56:31 mckusick 1 0
c date and time created 83/02/24 12:56:31 by mckusick
e
u
U
t
T
I 1
D 7
#	%W%	(Berkeley)	%E%
E 7
D 13
#
D 7
DESTDIR=
E 7
I 7
D 11
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 11
I 11
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 11
#
D 11
#	%W%	(Berkeley)	%G%
E 11
I 11
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
E 11
#
E 13
I 11
#	%W% (Berkeley) %G%
D 13
#
E 11
# Flag BSD4_2 means 4.2 or later.
CFLAGS=	-O -DBSD4_2
LIBC=	/lib/libc.a
D 12
LLIB=	${DESTDIR}/usr/lib/learn/bin
E 12
I 12
LLIB=	${DESTDIR}/usr/libdata/learn/bin
E 12
SRCS=	copy.c dounit.c getlesson.c learn.c list.c mem.c makpipe.c maktee.c \
	mysys.c selsub.c selunit.c start.c whatnow.c wrapup.c
OBJS=	copy.o dounit.o getlesson.o learn.o list.o mem.o makpipe.o maktee.o \
	mysys.o selsub.o selunit.o start.o whatnow.o wrapup.o
I 11
LESSONS=C editor eqn files macros morefiles
MAN=	learn.0
E 13
E 11
E 7

I 5
D 7
# The vi lessons come with the user-contributed software.
E 5
LESSONS = files editor morefiles macros eqn C
E 7
I 7
D 9
all: learn lrntee lcount
E 9
I 9
D 13
all: learn lrntee lcount getline.o getnum.o
E 13
I 13
SUBDIR=	lcount learn learnlib lrntee objects
E 13
E 9
E 7

D 7
FILES = lrnref.h \
D 3
	copy.c dounit.c learn.c list.c \
E 3
I 3
	copy.c dounit.c getlesson.c learn.c list.c \
E 3
	makpipe.c maktee.c mem.c mysys.c selsub.c selunit.c \
	start.c whatnow.c wrapup.c \
D 3
	lcount.c tee.c \
E 3
I 3
	lcount.c lrntee.c \
E 3
	makefile
E 7
I 7
D 13
learn: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 13
I 13
D 14
beforeinstall:
	(cd ${LLIB}/learn; rm -rf *)
	(cd ${LLIB}/learn; mkdir C bin editor eqn files macros morefiles)
E 13
E 7

E 14
D 3
OBJECTS = copy.o dounit.o learn.o list.o mem.o \
E 3
I 3
D 7
OBJECTS = copy.o dounit.o getlesson.o learn.o list.o mem.o \
E 3
	makpipe.o maktee.o mysys.o selsub.o selunit.o \
	start.o whatnow.o wrapup.o
E 7
I 7
D 11
lcount: lcount.c ${LIBC}
	${CC} ${CFLAGS} -o $@ lcount.c
E 11
I 11
D 13
lcount lrntee: ${LIBC}
	${CC} ${CFLAGS} -o $@ $@.c
E 11
E 7

D 5
CFLAGS = -O
E 5
I 5
D 7
# Flag BSD4_2 means 4.2 or later.
CFLAGS = -O -DBSD4_2
E 5
LIBRARY =
D 3
LLIB	= $(DESTDIR)/usr/lib/learn
E 3
I 3
LLIB	= $(DESTDIR)/usr/lib/learn/bin
E 7
I 7
D 11
lrntee: lrntee.c ${LIBC}
	${CC} ${CFLAGS} -o $@ lrntee.c
E 7
E 3

D 3
all:	learn tee lcount
	
E 3
I 3
D 7
all:	learn lrntee lcount
E 7
I 7
clean: FRC
E 11
I 11
clean:
E 11
D 9
	rm -f ${OBJS} core learn lrntee lcount
E 9
I 9
	rm -f ${OBJS} core learn lrntee lcount getline.o getnum.o
E 9
E 7

E 3
D 7
install:	all
D 4
	install -s learn $(DESTDIR)/usr/bin
E 4
I 4
	install -c -s learn $(DESTDIR)/usr/bin
E 4
D 3
	install -s tee $(LLIB)
E 3
I 3
	install -s learn $(LLIB)
	install -s lrntee $(LLIB)
E 3
	install -s lcount $(LLIB)
E 7
I 7
D 11
depend: FRC
D 9
	mkdep ${CFLAGS} ${SRCS} lcount.c lrntee.c
E 9
I 9
	mkdep ${CFLAGS} ${SRCS} lcount.c lrntee.c getline.c getnum.c
E 11
I 11
cleandir: clean
	rm -f ${MAN} tags .depend
E 11
E 9
E 7
D 3
	@echo "Then do 'make play; make log' to make playpen and log directories"
E 3
D 5

I 3
ccinstall:	all
	cp learn lrntee lcount $(LLIB)
	chmod 755 $(LLIB)/*
	strip $(LLIB)/*
E 5

E 3
D 7
clean:
D 3
	rm -f *.o learn tee lcount errs
E 3
I 3
	rm -f *.o learn lrntee lcount errs
E 7
I 7
D 11
install: FRC
E 11
I 11
depend: ${SRCS}
	mkdep -p ${CFLAGS} lcount.c lrntee.c
	mkdep -a ${CFLAGS} ${SRCS} getline.c getnum.c

install: ${MAN}
I 12
	-[ -d ${DESTDIR}/var/log/learn ] || mkdir ${DESTDIR}/var/log/learn
	-[ -d ${DESTDIR}/usr/libdata/learn ] || mkdir ${DESTDIR}/usr/libdata/learn
	-[ -d ${DESTDIR}/usr/libdata/learn/bin ] || mkdir ${DESTDIR}/usr/libdata/learn/bin
E 12
E 11
	install -c -s -o bin -g bin -m 755 learn ${DESTDIR}/usr/bin/learn
	install -s -o bin -g bin -m 755 learn ${LLIB}/learn
	install -s -o bin -g bin -m 755 lrntee ${LLIB}/lrntee
	install -s -o bin -g bin -m 755 lcount ${LLIB}/lcount
I 9
	install -o bin -g bin -m 644 getline.o ${LLIB}/getline.o
	install -o bin -g bin -m 644 getnum.o ${LLIB}/getnum.o
I 12
	install -c -o bin -g bin -m 644 learnlib/Linfo ${DESTDIR}/usr/libdata/learn/Linfo
	install -c -o bin -g bin -m 644 learnlib/Xinfo ${DESTDIR}/usr/libdata/learn/Xinfo
	cd learnlib; tar cf - ${LESSONS} | (cd ${DESTDIR}/usr/libdata/learn; tar xpf -);
	chmod 755 ${LLIB}/../*/Init
	chmod 755 ${DESTDIR}/usr/libdata/learn ${DESTDIR}/var/log/learn \
		${DESTDIR}/usr/libdata/learn/bin
	chown root.staff ${DESTDIR}/usr/bin/learn ${DESTDIR}/var/log/learn \
		${DESTDIR}/usr/libdata/learn/bin
E 12
	cd ${LLIB}; rm -f ../C/get*.o; ln getline.o getnum.o ../C
D 10
	install -o bin -g bin -m 644 getline.c ${LLIB}/../C/getline.c
	install -o bin -g bin -m 644 getnum.c ${LLIB}/../C/getnum.c
E 10
I 10
	install -c -o bin -g bin -m 644 getline.c ${LLIB}/../C/getline.c
	install -c -o bin -g bin -m 644 getnum.c ${LLIB}/../C/getnum.c
E 10
E 9
I 8
D 12
	chmod 755 ${LLIB}/../*/Init
I 11
	-[ -d ${DESTDIR}/usr/lib/learn ] || mkdir ${DESTDIR}/usr/lib/learn
	-[ -d ${DESTDIR}/usr/lib/learn/log ] || mkdir ${DESTDIR}/usr/lib/learn/log
	-[ -d ${DESTDIR}/usr/lib/learn/bin ] || mkdir ${DESTDIR}/usr/lib/learn/bin
	chmod 755 ${DESTDIR}/usr/lib/learn ${DESTDIR}/usr/lib/learn/log \
		${DESTDIR}/usr/lib/learn/bin
	chown root.staff ${DESTDIR}/usr/lib/learn ${DESTDIR}/usr/lib/learn/log \
		${DESTDIR}/usr/lib/learn/bin
	install -c -o bin -g bin -m 644 learnlib/Linfo ${DESTDIR}/usr/lib/learn/Linfo
	install -c -o bin -g bin -m 644 learnlib/Xinfo ${DESTDIR}/usr/lib/learn/Xinfo
	cd learnlib; tar cf - ${LESSONS} | (cd ${DESTDIR}/usr/lib/learn; tar xpf -);
E 12
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 11
E 8
E 7
E 3

D 7
cmp:	all
D 3
	cmp learn $(DESTDIR)/bin/learn
	cmp tee $(LLIB)/tee
E 3
I 3
	cmp learn $(DESTDIR)/usr/bin/learn
	cmp learn $(LLIB)/learn
	cmp lrntee $(LLIB)/lrntee
E 3
	cmp lcount $(LLIB)/lcount
D 3
	rm learn tee lcount *.o
E 3
I 3
	rm learn lrntee lcount *.o
E 7
I 7
D 11
lint: FRC
E 11
I 11
lint: ${SRCS}
E 11
	lint ${CFLAGS} ${SRCS}
	lint ${CFLAGS} lcount.c
	lint ${CFLAGS} lrntee.c
I 9
	lint ${CFLAGS} getline.c getnum.c
E 9
E 7
E 3

D 7
learn: $(OBJECTS)
	cc -o learn $(CFLAGS) $(OBJECTS) $(LIBRARY)
E 7
I 7
D 11
tags: FRC
E 11
I 11
tags: ${SRCS}
E 11
	ctags ${SRCS}
	ctags -a lcount.c
	ctags -a lrntee.c
I 9
	ctags -a getline.c getnum.c
E 9
	sort -o tags tags
E 13
I 13
.include "Makefile.inc"
.include <bsd.subdir.mk>
E 13
E 7
D 11

D 7
$(OBJECTS): lrnref.h
E 7
I 7
FRC:
E 7

D 3
lcount tee:
E 3
I 3
D 7
lcount lrntee:
E 3
	cc $(CFLAGS) $@.c -o $@ $(LIBRARY)
E 7
I 7
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 7

D 3
lessons:	$(LESSONS)
E 3
I 3
D 7
log:
	-rm -r $(LLIB)/../log; mkdir $(LLIB)/../log; chmod +w $(LLIB)/../log
E 7
I 7
copy.o: copy.c /usr/include/stdio.h /usr/include/signal.h lrnref.h
dounit.o: dounit.c /usr/include/stdio.h lrnref.h
getlesson.o: getlesson.c /usr/include/stdio.h lrnref.h
learn.o: learn.c /usr/include/stdio.h lrnref.h /usr/include/signal.h
list.o: list.c /usr/include/stdio.h lrnref.h /usr/include/signal.h
mem.o: mem.c /usr/include/stdio.h lrnref.h
makpipe.o: makpipe.c /usr/include/stdio.h
maktee.o: maktee.c /usr/include/stdio.h /usr/include/signal.h lrnref.h
mysys.o: mysys.c /usr/include/stdio.h /usr/include/signal.h
selsub.o: selsub.c /usr/include/stdio.h /usr/include/sys/types.h
selsub.o: /usr/include/sys/stat.h lrnref.h /usr/include/sys/dir.h
selunit.o: selunit.c /usr/include/stdio.h lrnref.h
start.o: start.c /usr/include/stdio.h lrnref.h /usr/include/sys/types.h
start.o: /usr/include/sys/dir.h
whatnow.o: whatnow.c /usr/include/stdio.h lrnref.h
wrapup.o: wrapup.c /usr/include/signal.h /usr/include/stdio.h lrnref.h
lcount.o: lcount.c /usr/include/stdio.h
lrntee.o: lrntee.c
E 7
E 3

D 3
$(LESSONS):
	-rm -r $(LLIB)/$@
	mkdir $(LLIB)/$@
	(cd $(LLIB)/$@; ar x ../$@.a)

play log:
	-rm -r $(LLIB)/$@; mkdir $(LLIB)/$@; chmod +w $(LLIB)/$@

E 3
D 7
check:
D 3
	-@test -r $(LLIB)/tee || echo 'tee not present; make tee'
E 3
I 3
	-@test -r $(LLIB)/lrntee || echo 'lrntee not present; make lrntee'
E 3
	-@test -r $(LLIB)/lcount || echo 'lcount not present; make lcount'
D 3
	-@test -r $(LLIB)/play || echo 'play directory not present; make play'
	-@test -r $(LLIB)/log || echo 'log directory not present; make log'
	-@for i in $(LESSONS); do test -r $(LLIB)/$$i/L0 || echo $$i not unarchived, make $$i; done
E 3
I 3
	-@test -r $(LLIB)/../log || echo 'log directory not present; make log if you want logging'
I 6

depend:
E 7
I 7
# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 11
E 7
E 6
E 3
E 1
