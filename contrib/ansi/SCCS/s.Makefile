h48701
s 00002/00000/00005
d D 5.8 93/06/29 07:40:45 bostic 10 9
c only get clean in contrib, not lceandir
e
s 00003/00046/00002
d D 5.7 90/06/30 22:32:22 bostic 9 8
c new makefiles
e
s 00000/00005/00048
d D 5.6 90/06/30 22:14:56 bostic 8 7
c don't need explicit rules any more
e
s 00010/00005/00043
d D 5.5 87/07/30 09:37:15 bostic 7 5
c new version from Tom Quarles (quarles@panic.berkeley.edu)
e
s 00005/00005/00043
d R 5.5 87/07/30 09:35:48 bostic 6 5
c new version from Tom Quarles (quarles@panic.berkeley.edu)
e
s 00026/00032/00022
d D 5.4 87/07/26 12:46:31 bostic 5 3
c new template
e
s 00007/00003/00051
d R 5.4 87/07/24 10:22:09 bostic 4 3
c copy man pages into place
e
s 00008/00009/00046
d D 5.3 86/05/15 05:03:05 lepreau 3 2
c fix make depend (zap .o's)
e
s 00002/00002/00053
d D 5.2 85/09/09 21:26:48 mckusick 2 1
c proper modes for manual pages
e
s 00055/00000/00000
d D 5.1 85/08/13 17:40:27 mckusick 1 0
c date and time created 85/08/13 17:40:27 by mckusick
e
u
U
t
T
I 1
D 7
#	%W%	(Berkeley)	%E%
E 7
D 9
#
I 7
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W%	(Berkeley)	%G%
#
E 7
DESTDIR=
CFLAGS=	-O
D 5
INCPATH=
LFLAGS=	
LIBS=
E 5
I 5
SRCS=	vmsprep.c ansitape.c
D 7
MSRC=	vmsprep.n ansitape.n
E 7
I 7
MSRC=	vmsprep.1 ansitape.1
E 7
MOBJ=	vmsprep.0 ansitape.0
E 9
I 9
#	%W% (Berkeley) %G%
E 9
E 5

D 5
all:	ansitape vmsprep
E 5
I 5
D 7
.SUFFIXES: .n .0
E 7
I 7
D 8
.SUFFIXES: .1 .0
E 7
E 5

D 5
ansitape: ansitape.c
	cc ${CFLAGS} -o ansitape ansitape.c
E 5
I 5
D 7
.n.0:
	../../man/manroff $*.n > $*.0
E 7
I 7
.1.0:
	/usr/man/manroff $*.1 > $*.0
E 7
E 5

E 8
D 5
vmsprep: vmsprep.c
	cc ${CFLAGS} -o vmsprep vmsprep.c
E 5
I 5
D 9
all: ansitape vmsprep
E 9
I 9
PROG=	ansitape
E 9
E 5

I 10
clean: cleandir

E 10
D 5
install: vmsprep ansitape
	install -s vmsprep ${DESTDIR}/usr/new/vmsprep
	install -s ansitape ${DESTDIR}/usr/new/ansitape
D 2
	install -c vmsprep.n ${DESTDIR}/usr/man/mann/vmsprep.n
	install -c ansitape.n ${DESTDIR}/usr/man/mann/ansitape.n
E 2
I 2
	install -c -m 444 vmsprep.n ${DESTDIR}/usr/man/mann/vmsprep.n
	install -c -m 444 ansitape.n ${DESTDIR}/usr/man/mann/ansitape.n
E 5
I 5
D 9
ansitape:
	${CC} ${CFLAGS} -o $@ ansitape.c
E 5
E 2

I 5
vmsprep:
	${CC} ${CFLAGS} -o $@ vmsprep.c

install: vmsprep ansitape ${MOBJ}
	install -s -o bin -g bin -m 755 vmsprep ${DESTDIR}/usr/new/vmsprep
	install -s -o bin -g bin -m 755 ansitape ${DESTDIR}/usr/new/ansitape
	install -c -o bin -g bin -m 444 vmsprep.0 ${DESTDIR}/usr/new/man/cat1/vmsprep.0
	install -c -o bin -g bin -m 444 ansitape.0 ${DESTDIR}/usr/new/man/cat1/ansitape.0

E 5
clean:
D 5
	rm -f a.out core errs makefile.bak Makefile.bak ansitape vmsprep
E 5
I 5
	rm -f a.out core errs makefile.bak Makefile.bak ansitape vmsprep *.0
E 5

depend:
D 3
	cc -M ${INCPATH} vmsprep.c ansitape.c | \
E 3
I 3
D 5
	cc -M ${INCPATH} vmsprep.c ansitape.c | sed 's/\.o//' | \
E 3
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
E 5
I 5
	mkdep -p ${SRCS}
E 5

D 5
# DO NOT DELETE THIS LINE -- make depend uses it
E 5
I 5
tags:
	ctags ${SRCS}
E 5

I 5
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 5

D 3
vmsprep.o: vmsprep.c /usr/include/stdio.h /usr/include/ctype.h
vmsprep.o: /usr/include/strings.h
ansitape.o: ansitape.c /usr/include/sys/types.h /usr/include/sys/time.h
ansitape.o: /usr/include/time.h /usr/include/sys/mtio.h
ansitape.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
ansitape.o: /usr/include/sys/ttydev.h /usr/include/sys/file.h
ansitape.o: /usr/include/sys/stat.h /usr/include/a.out.h
ansitape.o: /usr/include/sys/exec.h /usr/include/stdio.h /usr/include/ctype.h
E 3
I 3
vmsprep: vmsprep.c /usr/include/stdio.h /usr/include/ctype.h
vmsprep: /usr/include/strings.h
ansitape: ansitape.c /usr/include/sys/types.h /usr/include/sys/time.h
ansitape: /usr/include/time.h /usr/include/sys/mtio.h /usr/include/sys/ioctl.h
ansitape: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
ansitape: /usr/include/sys/file.h /usr/include/sys/stat.h /usr/include/a.out.h
ansitape: /usr/include/sys/exec.h /usr/include/stdio.h /usr/include/ctype.h
E 3
D 5
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
E 5
I 5

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 9
I 9
.include <bsd.prog.mk>
E 9
E 5
E 1
