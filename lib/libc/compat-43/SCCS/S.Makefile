h06305
s 00005/00005/00064
d D 5.3 90/03/15 21:08:51 mckusick 3 2
c update for separate machine compilation
e
s 00006/00006/00063
d D 5.2 90/03/11 16:40:43 karels 2 1
c add killpg and creat to compat-43 library
e
s 00069/00000/00000
d D 5.1 89/08/26 17:08:03 karels 1 0
c new makefile
e
u
U
t
T
I 1
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
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
#	%W% (Berkeley) %G%
#
D 2
OBJS=	sigcompat.o
SRCS=	sigcompat.c
MAN=	sigvec.0 sigblock.0 sigsetmask.0 sigpause.0
E 2
I 2
OBJS=	creat.o killpg.o sigcompat.o
SRCS=	creat.c killpg.c sigcompat.c
MAN=	creat.0 killpg.0 sigvec.0 sigblock.0 sigsetmask.0 sigpause.0
E 2

DEFS=	-DLIBC_SCCS
FLAGS=	-I../${MACHINE} ${DEFS}
CFLAGS=	-O ${DEFS}
MDIR=	${DESTDIR}/usr/man/cat3
TAGSFILE=tags

.SUFFIXES:
D 2
.SUFFIXES: .o .s .c .3 .0
E 2
I 2
.SUFFIXES: .o .s .c .2 .0
E 2

.s.o:
D 2
	@/lib/cpp -E ${FLAGS} -DPROF $*.s | ${AS} -o $*.o
E 2
I 2
	@/usr/bin/cpp -E ${FLAGS} -DPROF $*.s | ${AS} -o $*.o
E 2
	@ld -X -o profiled/$*.o -r $*.o
D 2
	/lib/cpp -E ${FLAGS} $*.s | ${AS} -o $*.o
E 2
I 2
	/usr/bin/cpp -E ${FLAGS} $*.s | ${AS} -o $*.o
E 2
	@ld -x -r $*.o
D 3
	@mv a.out $*.o
E 3
I 3
	@mv ${OBJDIR}a.out ${OBJDIR}$*.o
E 3

.c.o:
	@${CC} -p ${CFLAGS} -c $*.c
	@-ld -X -o profiled/$*.o -r $*.o
	${CC} ${CFLAGS} -c $*.c
	@-ld -x -r $*.o
D 3
	@mv a.out $*.o
E 3
I 3
	@mv ${OBJDIR}a.out ${OBJDIR}$*.o
E 3

all: ${OBJS}
	cd ../library; rm -f ${OBJS}
D 3
	ln ${OBJS} ../library
E 3
I 3
	cd ${OBJDIR}.; ln ${OBJS} ../library
E 3
	cd ../profiled; rm -f ${OBJS}
D 3
	cd profiled; ln ${OBJS} ../../profiled
E 3
I 3
	cd ${OBJDIR}./profiled; ln ${OBJS} ../../profiled
E 3

clean:
D 3
	rm -f *.o profiled/* a.out core
E 3
I 3
	rm -f ${OBJDIR}*.o profiled/* ${OBJDIR}a.out core
E 3

cleandir: clean
	rm -f ${MAN} tags .depend

depend:
	mkdep ${CFLAGS} ${SRCS}

tags:	${SRCS}
	rm -f ${TAGSFILE}
	(cwd=`pwd`; \
	for i in ${SRCS}; do \
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done;)

install: ${MAN}
	install -c -o bin -g bin -m 444 ${MAN} ${MDIR}
E 1
