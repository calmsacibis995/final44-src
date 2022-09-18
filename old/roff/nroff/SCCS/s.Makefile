h41745
s 00009/00055/00005
d D 4.7 90/05/11 14:24:47 bostic 8 7
c first pass for new make
e
s 00001/00001/00059
d D 4.6 89/07/30 14:58:23 bostic 7 6
c needs libcompat
e
s 00026/00082/00034
d D 4.5 88/10/25 15:09:27 bostic 6 5
c add manual page, cleanups
e
s 00099/00056/00017
d D 4.4 87/06/19 07:31:48 bostic 5 3
c new template
e
s 00099/00056/00017
d R 4.4 87/06/18 22:11:40 bostic 4 3
c new template
e
s 00002/00000/00071
d D 4.3 87/05/31 21:31:24 bostic 3 2
c added depend label
e
s 00004/00002/00067
d D 4.2 83/06/30 14:16:27 sam 2 1
c stuff
e
s 00069/00000/00000
d D 4.1 83/04/03 18:19:06 sam 1 0
c date and time created 83/04/03 18:19:06 by sam
e
u
U
t
T
I 1
D 8
#
D 5
#	%W% %G%
E 5
I 5
D 6
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 6
I 6
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 6
E 5
#
D 5
DESTDIR =
SRCS = \
	ni.c nii.c n1.c n2.c \
	n3.c n4.c n5.c n6.c \
	n7.c n8.c n9.c n10.c \
	hytab.c ntab.c suftab.c \
	d.h tw.h v.h tdef.h sdef.h
E 5
I 5
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
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
#
E 8
I 6
#	%W% (Berkeley) %G%
D 8
#
E 6
COMMON=	../common_source
CFLAGS=	-O -DNROFF -DVMUNIX -I${COMMON}
VPATH=	${COMMON}
LIBC=	/lib/libc.a
E 8
I 8

PROG=	nroff
CFLAGS+=-DNROFF -DVMUNIX -I${.CURDIR}/../common_source
E 8
SRCS=	ni.c nii.c n1.c n2.c n3.c n4.c n5.c n6.c n7.c n8.c n9.c n10.c \
	hytab.c ntab.c suftab.c
D 8
OBJS=	ni.o nii.o n1.o n2.o n3.o n4.o n5.o n6.o n7.o n8.o n9.o n10.o \
	hytab.o ntab.o suftab.o
I 6
MAN=	nroff.0
E 8
I 8
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
.PATH:	${.CURDIR}/../common_source
E 8
E 6
E 5

D 2
CFLAGS = -O -DNROFF -DVMUNIX -I../troff/
E 2
I 2
D 5
CFLAGS = -O -DNROFF -DVMUNIX -I../troff/ 
E 2
c = ni.o nii.o n1.o n2.o n3.o n4.o n5.o n6.o n7.o n8.o n9.o n10.o
s = hytab.o ntab.o suftab.o
E 5
I 5
D 8
all: nroff
E 8
I 8
hytab.o suftab.o ntab.o:
	${CC} ${CFLAGS} -R -c ${.IMPSRC}
E 8
E 5

D 5
all:	nroff term
E 5
I 5
D 8
nroff: ${OBJS} ${LIBC}
D 6
	$(CC) -o $@ ${OBJS}
E 6
I 6
D 7
	${CC} -o $@ ${OBJS}
E 7
I 7
	${CC} -o $@ ${OBJS} -lcompat
E 7
E 6
E 5

D 5
nroff: $c $s
	$(CC) -o nroff  $s $c  
E 5
I 5
hytab.o: ${COMMON}/hytab.c
	${CC} -R -c ${COMMON}/hytab.c
E 5

D 5
ni.o:	../troff/ni.c
	$(CC) $(CFLAGS) -c ../troff/ni.c
E 5
I 5
suftab.o: ${COMMON}/suftab.c
	${CC} -R -c ${COMMON}/suftab.c
E 5

D 5
nii.o:	../troff/nii.c
	$(CC) $(CFLAGS) -c ../troff/nii.c
E 5
I 5
ntab.o: ntab.c
	${CC} -R -c ntab.c
E 5

D 5
n1.o:	../troff/n1.c
	$(CC) $(CFLAGS) -c ../troff/n1.c
E 5
I 5
D 6
clean: FRC
E 6
I 6
clean:
E 6
	rm -f ${OBJS} core nroff
E 5

D 5
n2.o:	../troff/n2.c
	$(CC) $(CFLAGS) -c ../troff/n2.c
E 5
I 5
D 6
depend: ${SRCS} FRC
E 6
I 6
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 6
	mkdep ${CFLAGS} ${SRCS}
E 5

D 5
n3.o:	../troff/n3.c
	$(CC) $(CFLAGS) -c ../troff/n3.c
E 5
I 5
D 6
install: FRC
E 6
I 6
install: ${MAN}
E 6
	install -s -o bin -g bin -m 755 nroff ${DESTDIR}/usr/bin/nroff
I 6
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 6
E 5

D 5
n4.o:	../troff/n4.c
	$(CC) $(CFLAGS) -c ../troff/n4.c
E 5
I 5
D 6
lint: ${SRCS} FRC
E 6
I 6
lint: ${SRCS}
E 6
	lint ${CFLAGS} ${SRCS}
E 5

D 5
n5.o:	../troff/n5.c
	$(CC) $(CFLAGS) -c ../troff/n5.c
E 5
I 5
D 6
tags: ${SRCS} FRC
E 6
I 6
tags: ${SRCS}
E 6
	ctags ${SRCS}
E 8
I 8
.include <bsd.prog.mk>
E 8
E 5
D 6

D 5
n7.o:	../troff/n7.c
	$(CC) $(CFLAGS) -c ../troff/n7.c

n8.o:	../troff/n8.c
	$(CC) $(CFLAGS) -c ../troff/n8.c

n9.o:	../troff/n9.c
	$(CC) $(CFLAGS) -c ../troff/n9.c

hytab.o:	../troff/hytab.c
	$(CC) -R -c ../troff/hytab.c

ntab.o:	../troff/ntab.c
	$(CC) -R -c ../troff/ntab.c

suftab.o:	../troff/suftab.c
	$(CC) -R -c ../troff/suftab.c

D 2
term:
E 2
I 2
term:	FRC
E 2
	cd term; make ${MFLAGS}
I 2

E 5
FRC:
E 2

D 5
install: all
	install -s nroff ${DESTDIR}/usr/bin
	cd term; make ${MFLAGS} DESTDIR=${DESTDIR} install
E 5
I 5
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 5

D 5
clean:
	rm -f *.o nroff
	cd term; make ${MFLAGS} clean
E 5
I 5
ni.o: ../common_source/ni.c ../common_source/tdef.h /usr/include/sys/param.h
ni.o: /usr/include/sys/types.h /usr/include/signal.h
ni.o: /usr/include/machine/machparam.h /usr/include/signal.h
nii.o: ../common_source/nii.c ../common_source/tdef.h /usr/include/sys/param.h
nii.o: /usr/include/sys/types.h /usr/include/signal.h
nii.o: /usr/include/machine/machparam.h /usr/include/signal.h
nii.o: ../common_source/tw.h ../common_source/sdef.h ../common_source/d.h
nii.o: ../common_source/v.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
nii.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
n1.o: ../common_source/n1.c ../common_source/tdef.h /usr/include/sys/param.h
n1.o: /usr/include/sys/types.h /usr/include/signal.h
n1.o: /usr/include/machine/machparam.h /usr/include/signal.h
n1.o: /usr/include/sys/types.h /usr/include/sys/stat.h /usr/include/time.h
n1.o: ../common_source/d.h ../common_source/v.h ../common_source/tw.h
n1.o: ../common_source/sdef.h /usr/include/setjmp.h /usr/include/sgtty.h
n1.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
n1.o: /usr/include/sys/ttydev.h
n2.o: ../common_source/n2.c ../common_source/tdef.h /usr/include/sys/param.h
n2.o: /usr/include/sys/types.h /usr/include/signal.h
n2.o: /usr/include/machine/machparam.h /usr/include/signal.h
n2.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
n2.o: /usr/include/sys/ttydev.h ../common_source/d.h ../common_source/v.h
n2.o: ../common_source/tw.h ../common_source/sdef.h /usr/include/setjmp.h
n3.o: ../common_source/n3.c ../common_source/tdef.h /usr/include/sys/param.h
n3.o: /usr/include/sys/types.h /usr/include/signal.h
n3.o: /usr/include/machine/machparam.h /usr/include/signal.h
n3.o: ../common_source/d.h ../common_source/v.h ../common_source/tw.h
n3.o: ../common_source/sdef.h
n4.o: ../common_source/n4.c ../common_source/tdef.h /usr/include/sys/param.h
n4.o: /usr/include/sys/types.h /usr/include/signal.h
n4.o: /usr/include/machine/machparam.h /usr/include/signal.h
n4.o: ../common_source/d.h ../common_source/v.h ../common_source/tw.h
n4.o: ../common_source/sdef.h
n5.o: ../common_source/n5.c ../common_source/tdef.h /usr/include/sys/param.h
n5.o: /usr/include/sys/types.h /usr/include/signal.h
n5.o: /usr/include/machine/machparam.h /usr/include/signal.h
n5.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
n5.o: /usr/include/sys/ttydev.h ../common_source/d.h ../common_source/v.h
n5.o: ../common_source/sdef.h
n6.o: n6.c ../common_source/tdef.h /usr/include/sys/param.h
n6.o: /usr/include/sys/types.h /usr/include/signal.h
n6.o: /usr/include/machine/machparam.h /usr/include/signal.h
n6.o: ../common_source/d.h ../common_source/v.h ../common_source/tw.h
n7.o: ../common_source/n7.c ../common_source/tdef.h /usr/include/sys/param.h
n7.o: /usr/include/sys/types.h /usr/include/signal.h
n7.o: /usr/include/machine/machparam.h /usr/include/signal.h
n7.o: ../common_source/d.h ../common_source/v.h ../common_source/tw.h
n7.o: ../common_source/sdef.h
n8.o: ../common_source/n8.c ../common_source/tdef.h /usr/include/sys/param.h
n8.o: /usr/include/sys/types.h /usr/include/signal.h
n8.o: /usr/include/machine/machparam.h /usr/include/signal.h
n9.o: ../common_source/n9.c ../common_source/tdef.h /usr/include/sys/param.h
n9.o: /usr/include/sys/types.h /usr/include/signal.h
n9.o: /usr/include/machine/machparam.h /usr/include/signal.h
n9.o: ../common_source/d.h ../common_source/v.h ../common_source/tw.h
n10.o: n10.c ../common_source/tdef.h /usr/include/sys/param.h
n10.o: /usr/include/sys/types.h /usr/include/signal.h
n10.o: /usr/include/machine/machparam.h /usr/include/signal.h
n10.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
n10.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
n10.o: ../common_source/d.h ../common_source/v.h ../common_source/tw.h
hytab.o: ../common_source/hytab.c
ntab.o: ntab.c
suftab.o: ../common_source/suftab.c
E 5
I 3

D 5
depend:
E 5
I 5
# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 6
E 5
E 3
E 1
