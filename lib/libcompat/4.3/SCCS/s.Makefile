h46116
s 00017/00008/00043
d D 5.7 90/03/22 14:37:31 bostic 7 6
c checkpoint before pmake
e
s 00002/00002/00049
d D 5.6 88/12/16 09:50:41 bostic 6 5
c add recv, send, wait, wait3
e
s 00000/00011/00051
d D 5.5 88/08/30 16:06:50 bostic 5 4
c remove dependency list
e
s 00011/00005/00051
d D 5.4 88/07/09 11:10:00 bostic 4 3
c install approved copyright notice
e
s 00001/00000/00055
d D 5.3 88/05/20 15:07:13 bostic 3 2
c set DEFS to compile in SCCS ids.
e
s 00021/00013/00034
d D 5.2 88/05/20 13:48:03 bostic 2 1
c restructuring libc
e
s 00047/00000/00000
d D 5.1 88/05/19 12:14:02 bostic 1 0
c date and time created 88/05/19 12:14:02 by bostic
e
u
U
t
T
I 1
#
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 4
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 4
#
#	%W% (Berkeley) %G%
#
I 4

E 4
I 3
DEFS=	-DLIBC_SCCS
E 3
CFLAGS=	-O ${DEFS}
D 2
SRCS=
OBJS=
E 2
I 2
D 6
SRCS=	ecvt.c gcvt.c sibuf.c sobuf.c strout.c
OBJS=	ecvt.o gcvt.o sibuf.o sobuf.o strout.o
E 6
I 6
D 7
SRCS=	ecvt.c gcvt.c recv.c send.c sibuf.c sobuf.c strout.c wait.c wait3.c
OBJS=	ecvt.o gcvt.o recv.o send.o sibuf.o sobuf.o strout.o wait.o wait3.o
E 7
I 7
SRCS=	ecvt.c gcvt.c lsearch.c rexec.c ruserpass.c sibuf.c sobuf.c strout.c
OBJS=	ecvt.o gcvt.o lsearch.o rexec.o ruserpass.o sibuf.o sobuf.o strout.o
MAN=	ecvt.0 lsearch.0 rexec.0
E 7
E 6
E 2
TAGSFILE=tags
I 7
MDIR=	${DESTDIR}/usr/man/cat3
E 7

.c.o:
D 2
	${CC} -p ${CFLAGS} -c $*.c
	-ld -X -r $*.o
	mv a.out profiled/$*.o
E 2
I 2
	@${CC} -p ${CFLAGS} -c $*.c
	@-ld -X -o profiled/$*.o -r $*.o
E 2
	${CC} ${CFLAGS} -c $*.c
D 2
	-ld -x -r $*.o
	mv a.out $*.o
E 2
I 2
	@-ld -x -r $*.o
	@mv a.out $*.o
E 2

D 2
compat-4.3lib compat-4.3lib_p: ${OBJS}
	@echo "building profiled compat-4.3lib"
	@cd profiled; ar cru ../compat-4.3lib_p ${OBJS}
	@echo "building normal compat-4.3lib"
	@ar cru compat-4.3lib ${OBJS}
E 2
I 2
all: ${OBJS}
E 2

I 2
D 7
link: ${OBJS}
	(cd ../library; rm -f ${OBJS})
	(cd ../profiled; rm -f ${OBJS})
	ln ${OBJS} ../library
	(cd profiled; ln ${OBJS} ../../profiled)

E 7
E 2
tags:
I 7
	rm -f ${TAGSFILE}
E 7
	cwd=`pwd`; \
	for i in ${SRCS}; do \
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done

clean:
D 2
	rm -f compat-4.3lib compat-4.3lib_p *.o profiled/*.o tags
E 2
I 2
	rm -f *.o profiled/* a.out core ${TAGSFILE}
E 2

I 7
cleandir: clean
	rm -f ${MAN} tags .depend

E 7
depend:
	mkdep ${CFLAGS} ${SRCS}
I 7

install: ${MAN}
	cd ../library; rm -f ${OBJS}
	cd ../profiled; rm -f ${OBJS}
	ln ${OBJS} ../library
	cd profiled; ln ${OBJS} ../../profiled
	install -c -o bin -g bin -m 444 ${MAN} ${MDIR}
	rm -f ${MDIR}/fcvt.0; ln ${MDIR}/ecvt.0 ${MDIR}/fcvt.0
	rm -f ${MDIR}/gcvt.0; ln ${MDIR}/ecvt.0 ${MDIR}/gcvt.0
E 7
D 5

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

I 2
ecvt.o: ecvt.c
gcvt.o: gcvt.c
sibuf.o: sibuf.c /usr/include/stdio.h
sobuf.o: sobuf.c /usr/include/stdio.h
strout.o: strout.c /usr/include/stdio.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 5
E 2
E 1
