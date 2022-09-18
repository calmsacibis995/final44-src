h51844
s 00000/00000/00013
d D 8.1 93/06/04 17:32:35 bostic 13 12
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00011
d D 5.10 90/06/01 15:46:57 bostic 12 11
c do links right
e
s 00009/00075/00004
d D 5.9 90/05/11 12:51:12 bostic 11 10
c first pass for new make
e
s 00001/00001/00078
d D 5.8 90/02/14 06:29:13 tef 10 9
c fixed pathname typo
e
s 00010/00006/00069
d D 5.7 89/05/10 22:41:09 bostic 9 8
c file reorg, pathnames.h, paths.h
e
s 00007/00000/00068
d D 5.6 89/04/10 11:51:51 bostic 8 7
c add man page links
e
s 00004/00002/00064
d D 5.5 89/04/10 10:54:34 bostic 7 6
c add man page
e
s 00023/00022/00043
d D 5.4 89/01/03 21:17:49 bostic 6 5
c written by Bill Joy; add Berkeley specific copyright
e
s 00006/00000/00059
d D 5.3 87/09/11 16:13:18 jak 5 4
c added test target to compile test programs
e
s 00036/00026/00023
d D 5.2 87/06/19 16:28:10 bostic 4 3
c new template
e
s 00006/00001/00043
d D 5.1 85/06/05 11:32:41 dist 3 2
c Add copyright
e
s 00016/00007/00028
d D 4.2 85/05/30 23:05:42 sam 2 1
c add tags
e
s 00035/00000/00000
d D 4.1 83/06/27 13:57:07 sam 1 0
c date and time created 83/06/27 13:57:07 by sam
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
D 11
#
D 4
# Copyright (c) 1980 Regents of the University of California.
E 4
I 4
D 6
# Copyright (c) 1987 Regents of the University of California.
E 4
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 6
I 6
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 6
#
D 4
#	%W% (Berkeley) %G%
E 4
I 4
D 6
#	%W%	(Berkeley)	%G%
E 6
I 6
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
D 7
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
E 6
E 4
E 3
#
E 11
I 6
#	%W% (Berkeley) %G%
D 11
#
E 6
CFLAGS=	-O -DCM_N -DCM_GT -DCM_B -DCM_D
D 4
LD = ld
E 4
I 4
LIBC=	/lib/libc.a
E 11
I 11

LIB=	termcap
CFLAGS+=-DCM_N -DCM_GT -DCM_B -DCM_D
E 11
E 4
I 2
SRCS=	termcap.c tgoto.c tputs.c
D 11
OBJS=	termcap.o tgoto.o tputs.o
I 7
MAN=	termcap.0
I 8
MDIR=	${DESTDIR}/usr/man/cat3
E 11
E 8
E 7
D 4
TAGSFILE=tags
E 4
E 2

D 11
.c.o:
D 4
	$(CC) $(CFLAGS) -c -p $*.c
	$(LD) $(LDFLAGS) -x -r -o profiled/$*.o $*.o
	$(CC) $(CFLAGS) -c $*.c
	$(LD) $(LDFLAGS) -X -r $*.o
E 4
I 4
	${CC} ${CFLAGS} -c -p $*.c
	ld -x -r -o profiled/$*.o $*.o
	${CC} ${CFLAGS} -c $*.c
	ld -X -r $*.o
E 4
	mv a.out $*.o
E 11
I 11
MAN3=	termcap.0
MLINKS=	termcap.3 tgetent.3 termcap.3 tgetflag.3 termcap.3 tgetnum.3 \
	termcap.3 tgetstr.3 termcap.3 tgoto.3 termcap.3 tputs.3
D 12
LINKS=	${DESTDIR}/usr/lib/libtermcap.a ${DESTDIR}/usr/lib/libtermlib.a \
	${DESTDIR}/usr/lib/libtermcap_p.a ${DESTDIR}/usr/lib/libtermlib_p.a
E 12
I 12
LINKS=	${LIBDIR}/libtermcap.a ${LIBDIR}/libtermlib.a \
	${LIBDIR}/libtermcap_p.a ${LIBDIR}/libtermlib_p.a
E 12
E 11

I 4
D 11
all: termcap.a termcap_p.a

E 4
D 2
termcap.a termcap_p.a: termcap.o tgoto.o tputs.o
	ar cr termcap.a termcap.o tgoto.o tputs.o
	cd profiled; ar cr ../termcap_p.a termcap.o tgoto.o tputs.o
E 2
I 2
termcap.a termcap_p.a: ${OBJS}
D 9
	ar cr termcap.a ${OBJS}
	cd profiled; ar cr ../termcap_p.a ${OBJS}
E 9
I 9
	@echo building normal termcap
	@ar cr termcap.a ${OBJS}
	ranlib termcap.a
	@echo building profiled termcap
	@cd profiled; ar cr ../termcap_p.a ${OBJS}
	ranlib termcap_p.a
E 9
E 2

I 5
test:
D 9
	ranlib termcap.a
E 9
	${CC} ${CFLAGS} -o tc1 tc1.c termcap.a
	${CC} ${CFLAGS} -o tc2 tc2.c termcap.a
	${CC} ${CFLAGS} -o tc3 tc3.c termcap.a

E 5
D 2
clean:
	-rm -f *.o profiled/*.o
	-rm -f termcap.a termcap_p.a

E 2
D 4
install: termcap.a termcap_p.a
	install -c termcap.a ${DESTDIR}/usr/lib/libtermcap.a
	-rm -f ${DESTDIR}/usr/lib/libtermlib.a
E 4
I 4
D 6
clean: FRC
E 6
I 6
clean:
E 6
	rm -f ${OBJS} core profiled/*.o termcap.a termcap_p.a

D 6
depend: FRC
E 6
I 6
cleandir: clean
	rm -f ${MAN} tags .depend

depend:
E 6
	mkdep ${CFLAGS} ${SRCS}

D 6
install: FRC
E 6
I 6
D 7
install:
E 7
I 7
install: ${MAN}
E 7
E 6
	install -o bin -g bin -m 644 termcap.a ${DESTDIR}/usr/lib/libtermcap.a
I 9
	ranlib -t ${DESTDIR}/usr/lib/libtermcap.a
E 9
	rm -f ${DESTDIR}/usr/lib/libtermlib.a
E 4
	ln ${DESTDIR}/usr/lib/libtermcap.a ${DESTDIR}/usr/lib/libtermlib.a
D 9
	ranlib ${DESTDIR}/usr/lib/libtermcap.a
D 4
	install -c termcap_p.a ${DESTDIR}/usr/lib/libtermcap_p.a
	-rm -f ${DESTDIR}/usr/lib/libtermlib_p.a
E 4
I 4
	install -o bin -g bin -m 644 termcap_p.a ${DESTDIR}/usr/lib/libtermcap_p.a
E 9
I 9
	install -o bin -g bin -m 644 termcap_p.a \
	    ${DESTDIR}/usr/lib/libtermcap_p.a
D 10
	ranlib -t ${DESTDIR}/urs/lib/libtermcap_p.a
E 10
I 10
	ranlib -t ${DESTDIR}/usr/lib/libtermcap_p.a
E 10
E 9
	rm -f ${DESTDIR}/usr/lib/libtermlib_p.a
E 4
	ln ${DESTDIR}/usr/lib/libtermcap_p.a ${DESTDIR}/usr/lib/libtermlib_p.a
D 9
	ranlib ${DESTDIR}/usr/lib/libtermcap_p.a
E 9
I 7
	install -c -o bin -g bin -m 444 termcap.0 ${DESTDIR}/usr/man/cat3
I 8
	rm -f ${MDIR}/tgetent.0; ln ${MDIR}/termcap.0 ${MDIR}/tgetent.0
	rm -f ${MDIR}/tgetflag.0; ln ${MDIR}/termcap.0 ${MDIR}/tgetflag.0
	rm -f ${MDIR}/tgetnum.0; ln ${MDIR}/termcap.0 ${MDIR}/tgetnum.0
	rm -f ${MDIR}/tgetstr.0; ln ${MDIR}/termcap.0 ${MDIR}/tgetstr.0
	rm -f ${MDIR}/tgoto.0; ln ${MDIR}/termcap.0 ${MDIR}/tgoto.0
	rm -f ${MDIR}/tputs.0; ln ${MDIR}/termcap.0 ${MDIR}/tputs.0
E 8
E 7
I 2

D 4
tags:
	cwd=`pwd`; \
	for i in ${SRCS}; do \
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done
E 4
I 4
D 6
lint: FRC
E 6
I 6
lint:
E 6
	lint ${CFLAGS} ${SRCS}
E 4

D 4
clean:
	-rm -f *.o profiled/*.o
	-rm -f termcap.a termcap_p.a
E 4
I 4
D 6
tags: FRC
E 6
I 6
tags:
E 6
	ctags ${SRCS}
E 11
I 11
.include <bsd.lib.mk>
E 11
E 4
E 2
D 6

D 4
VGRIND=	csh /usr/ucb/vgrind
vgrind:
	cp /dev/null index
	${VGRIND} -h "Termcap library" termcap.c tputs.c tgoto.c
	${VGRIND} -h "Termcap library" -x index
E 4
I 4
FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

termcap.o: termcap.c /usr/include/ctype.h
tgoto.o: tgoto.c
tputs.o: tputs.c /usr/include/sgtty.h /usr/include/sys/ioctl.h
tputs.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
tputs.o: /usr/include/ctype.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 6
E 4
E 1
