h60462
s 00001/00001/00008
d D 4.12 91/05/22 14:48:44 bostic 12 11
c needs writable strings -- see files.c
e
s 00001/00000/00008
d D 4.11 90/07/02 15:59:29 bostic 11 10
c clean gram.c, y.tab.h
e
s 00005/00044/00003
d D 4.10 90/05/31 16:50:13 bostic 10 9
c pmake
e
s 00003/00003/00044
d D 4.9 90/05/03 11:13:22 bostic 9 8
c move to /usr/old
e
s 00002/00002/00045
d D 4.8 89/05/11 13:36:16 bostic 8 7
c file reorg, pathnames.h, paths.h
e
s 00029/00046/00018
d D 4.7 88/09/13 09:24:24 bostic 7 6
c cleanup, add manual page
e
s 00026/00040/00038
d D 4.6 87/06/03 00:10:29 bostic 6 5
c reorg
e
s 00061/00008/00017
d D 4.5 87/05/05 09:04:10 bostic 5 4
c bug report 4.3BSD/bin/70
e
s 00002/00001/00023
d D 4.4 85/04/16 14:57:21 mckusick 4 3
c vpath additions from Greg Couch (gregc@ucsfcgl)
e
s 00009/00057/00015
d D 4.3 82/10/19 15:38:12 sam 3 2
c clean up and so on
e
s 00005/00005/00067
d D 4.2 82/10/18 21:16:15 mckusick 2 1
c use ``rm -f'' so clean will always work
e
s 00072/00000/00000
d D 4.1 81/02/28 21:15:50 wnj 1 0
c date and time created 81/02/28 21:15:50 by wnj
e
u
U
t
T
I 1
D 6
# Description file for the Make command
# %M% %I% %E%

I 4
D 5
VPATH=.:/usr/src/bin/make
E 5
E 4
D 3
P = und -3 | opr -r2
T =
FILES = Makefile ident.c defs main.c doname.c misc.c files.c dosys.c\
	gram.y gcos.c
OBJECTS = ident.o main.o doname.o misc.o files.o dosys.o gram.o 
E 3
I 3
OBJECTS=ident.o main.o doname.o misc.o files.o dosys.o gram.o 
E 3
D 5
LIBES= 
D 3
LINT = lint -ps
CFLAGS = -O -DASCARCH
E 3
I 3
LINT=	lint -ps
E 5
I 5
SOURCES=ident.c main.c doname.c misc.c files.c dosys.c gram.c
E 6
I 6
D 10
#
D 7
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 7
I 7
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 7
#
D 7
#	%W%	(Berkeley)	%G%
E 7
I 7
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
E 7
#
E 10
I 7
#	%W% (Berkeley) %G%
D 10
#
E 7
E 6
E 5
D 4
CFLAGS=	-O -DASCARCH
E 4
I 4
D 9
CFLAGS=	-O -DASCARCH -I. -I/usr/src/bin/make 
E 9
I 9
CFLAGS=	-O -DASCARCH -I.
E 9
I 5
D 6
LIBES= 
LINT=	lint -chapx
E 6
I 6
LIBC=	/lib/libc.a
E 10
I 10

PROG=	make
D 12
CFLAGS+=-DASCARCH -I${.CURDIR}
E 12
I 12
CFLAGS+=-DASCARCH -I${.CURDIR} -fwritable-strings
E 12
E 10
D 7
SRCS=	ident.c main.c doname.c misc.c files.c dosys.c gram.c
OBJS=	ident.o main.o doname.o misc.o files.o dosys.o gram.o
E 7
I 7
SRCS=	main.c doname.c misc.c files.c dosys.c gram.c
D 10
OBJS=	main.o doname.o misc.o files.o dosys.o gram.o
MAN=	make.0
E 10
I 10
MAN1=	make.0
I 11
CLEANFILES=gram.c y.tab.h
E 11
E 10
E 7
E 6
E 5
E 4
E 3

D 3
GCOSFILES = defs ident.c main.c doname.c misc.c gram.c gcos.c

E 3
D 7
all:	make
E 7
I 7
D 10
all: make
E 7

D 3
cmp:	make
	cmp make /bin/make
D 2
	rm *.o gram.c make
E 2
I 2
	rm -f *.o gram.c make
E 3
I 3
D 6
make:	${OBJECTS}
D 5
	${CC} -o make ${CFLAGS} ${OBJECTS} ${LIBES}
E 5
I 5
	${CC} -o $@ ${CFLAGS} ${OBJECTS} ${LIBES}
E 6
I 6
D 7
make:	${OBJS} ${LIBC}
E 7
I 7
make: ${OBJS} ${LIBC}
E 7
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 6
E 5
E 3
E 2

D 3
cp:	make
	cp make /bin/make
D 2
	rm *.o gram.c make
E 2
I 2
	rm -f *.o gram.c make
E 3
I 3
D 5
${OBJECTS}:  defs
E 5
I 5
D 6
${OBJECTS}: defs
E 6
I 6
D 7
clean: FRC
E 7
I 7
clean:
E 7
	rm -f ${OBJS} core make gram.c
E 6
E 5
E 3
E 2

D 3
make:  $(OBJECTS)
	$(CC) -n -s $(CFLAGS) $(OBJECTS) $(LIBES) -o make

$(OBJECTS):  defs

E 3
D 6
clean:
D 2
	-rm *.o gram.c
E 2
I 2
D 3
	-rm -f *.o gram.c
E 3
I 3
D 5
	-rm -f *.o gram.c make a.out errs
E 5
I 5
	rm -f ${OBJECTS} gram.c make a.out errs core
E 6
I 6
D 7
depend: gram.c FRC
E 7
I 7
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 7
	mkdep ${CFLAGS} ${SRCS}
E 6
E 5
E 3
E 2

D 6
install:
D 3
	install make $(DESTDIR)/bin/make
E 3
I 3
	install -s make ${DESTDIR}/bin/make
E 6
I 6
D 7
install: FRC
E 7
I 7
install: ${MAN}
E 7
D 8
	install -s -o bin -g bin -m 755 make ${DESTDIR}/bin/make
I 7
	install -o bin -g bin -m 444 make.0 ${DESTDIR}/usr/man/cat1/make.0
E 8
I 8
D 9
	install -s -o bin -g bin -m 755 make ${DESTDIR}/usr/bin
	install -c -o bin -g bin -m 444 make.0 ${DESTDIR}/usr/man/cat1
E 9
I 9
	install -s -o bin -g bin -m 755 make ${DESTDIR}/usr/old
	install -c -o bin -g bin -m 444 make.0 ${DESTDIR}/usr/man/cat.old
E 9
E 8
E 7
E 6
E 3

D 3
printall: # Print files off line.
	-pr $(FILES) | $P
	touch print

print:  $(FILES)	# print recently changed files
	-pr $? | $P
	touch print

save: # Write files on Spider store.
	-nfs -ucv make $(FILES)

test: 1zap 2zap
	diff 1zap 2zap
D 2
	rm 1zap 2zap
E 2
I 2
	rm -f 1zap 2zap
E 2

1zap:
	./make -dp | grep -v TIME >1zap

2zap:
	/bin/make -dp | grep -v TIME >2zap

time:  time1 time2 ;

time1 time2 :
	time ./make $T
	time /bin/make $T

E 3
D 5
lint :  dosys.c doname.c files.c main.c misc.c ident.c gram.c
D 3
	$(LINT) dosys.c doname.c files.c main.c misc.c ident.c gram.c
E 3
I 3
	${LINT} dosys.c doname.c files.c main.c misc.c ident.c gram.c
E 5
I 5
D 6
lint: FRC
	${LINT} ${SOURCES}
E 5
E 3
D 2
	rm gram.c
E 2
I 2
	rm -f gram.c
E 6
I 6
D 7
lint: gram.c FRC
E 7
I 7
lint: ${SRCS}
E 7
	lint ${CFLAGS} ${SRCS}
E 6
I 5

D 6
tags: FRC
	ctags ${SOURCES}
E 6
I 6
D 7
tags: gram.c FRC
E 7
I 7
tags: ${SRCS}
E 7
	ctags ${SRCS}
E 10
I 10
.include <bsd.prog.mk>
E 10
E 6
D 7

FRC:

D 6
depend: ${SOURCES}
	cc -M ${CFLAGS} ${SOURCES} | sed -e 's, ./, ,g' | \
	    awk ' { if ($$1 != prev) \
		{ if (rec != "") print rec; rec = $$0; prev = $$1; } \
		else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
		else rec = rec " " $$2 } } \
		END { print rec } ' >makedep
	echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	cp Makefile Makefile.bak
	ed - Makefile < eddep
	rm eddep makedep
	echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	echo '# see make depend above' >> Makefile
E 6
I 6
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 6

D 6
# DO NOT DELETE THIS LINE -- make depend uses it

E 6
ident.o: ident.c
main.o: main.c defs /usr/include/stdio.h /usr/include/ctype.h
main.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
main.o: /usr/include/machine/machparam.h /usr/include/sys/dir.h
main.o: /usr/include/signal.h /usr/include/sys/stat.h
doname.o: doname.c defs /usr/include/stdio.h /usr/include/ctype.h
doname.o: /usr/include/sys/param.h /usr/include/sys/types.h
doname.o: /usr/include/signal.h /usr/include/machine/machparam.h
doname.o: /usr/include/sys/dir.h /usr/include/strings.h /usr/include/signal.h
misc.o: misc.c defs /usr/include/stdio.h /usr/include/ctype.h
misc.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
misc.o: /usr/include/machine/machparam.h /usr/include/sys/dir.h
files.o: files.c /usr/include/fcntl.h defs /usr/include/stdio.h
files.o: /usr/include/ctype.h /usr/include/sys/param.h /usr/include/sys/types.h
files.o: /usr/include/signal.h /usr/include/machine/machparam.h
files.o: /usr/include/sys/dir.h /usr/include/sys/stat.h /usr/include/ar.h
files.o: /usr/include/a.out.h /usr/include/sys/exec.h /usr/include/sys/stat.h
dosys.o: dosys.c defs /usr/include/stdio.h /usr/include/ctype.h
dosys.o: /usr/include/sys/param.h /usr/include/sys/types.h
dosys.o: /usr/include/signal.h /usr/include/machine/machparam.h
dosys.o: /usr/include/sys/dir.h /usr/include/signal.h /usr/include/errno.h
dosys.o: /usr/include/sys/stat.h
gram.o: gram.c defs /usr/include/stdio.h /usr/include/ctype.h
gram.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
gram.o: /usr/include/machine/machparam.h /usr/include/sys/dir.h
D 6
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
E 6
I 6

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 7
E 6
E 5
E 2
D 3

src:
	cp $(FILES) /usr/src/cmd/make

gcos: $(GCOSFILES)
	fsend -c -u sif $?
	touch gcos
E 3
E 1
