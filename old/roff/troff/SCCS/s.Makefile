h60915
s 00009/00054/00005
d D 5.5 90/05/11 14:24:56 bostic 5 4
c first pass for new make
e
s 00001/00001/00058
d D 5.4 89/08/05 12:23:19 bostic 4 3
c need lcompat
e
s 00001/00001/00058
d D 5.3 89/05/11 10:05:40 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00025/00080/00034
d D 5.2 88/10/25 18:28:51 bostic 2 1
c add man page, cleanup
e
s 00114/00000/00000
d D 5.1 87/12/12 17:37:00 bostic 1 0
c date and time created 87/12/12 17:37:00 by bostic
e
u
U
t
T
I 1
D 5
#
D 2
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 2
I 2
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 2
#
D 2
#	%W%	(Berkeley)	%G%
E 2
I 2
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
E 2
#
E 5
I 2
#	%W% (Berkeley) %G%
D 5
#
E 2
COMMON=	../common_source
CFLAGS=	-O -DVMUNIX -I${COMMON}
VPATH=	${COMMON}
LIBC=	/lib/libc.a
E 5
I 5

PROG=	troff
CFLAGS+=-DVMUNIX -I${.CURDIR}/../common_source
E 5
SRCS=	ni.c nii.c n1.c n2.c n3.c n4.c n5.c t6.c n7.c n8.c n9.c t10.c \
	hytab.c suftab.c tab3.c
D 5
OBJS=	ni.o nii.o n1.o n2.o n3.o n4.o n5.o t6.o n7.o n8.o n9.o t10.o \
	hytab.o suftab.o tab3.o
I 2
MAN=	troff.0
E 5
I 5
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
.PATH:	${.CURDIR}/../common_source
E 5
E 2

D 5
all: troff
E 5
I 5
hytab.o suftab.o:
	${CC} ${CFLAGS} -R -c ${.IMPSRC}
E 5

D 5
troff: ${OBJS} ${LIBC}
D 4
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 4
I 4
	${CC} -o $@ ${CFLAGS} ${OBJS} -lcompat
E 4

hytab.o: ${COMMON}/hytab.c
	${CC} -R -c ${COMMON}/hytab.c

suftab.o: ${COMMON}/suftab.c
	${CC} -R -c ${COMMON}/suftab.c

D 2
clean: FRC
E 2
I 2
clean:
E 2
	rm -f ${OBJS} core troff

D 2
depend: ${SRCS} FRC
E 2
I 2
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 2
	mkdep ${CFLAGS} ${SRCS}

D 2
install: FRC
E 2
I 2
install: ${MAN}
E 2
D 3
	install -s -o bin -g bin -m 755 troff ${DESTDIR}/usr/bin/troff
E 3
I 3
	install -s -o bin -g bin -m 755 troff ${DESTDIR}/usr/bin
E 3
I 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 2

D 2
lint: ${SRCS} FRC
E 2
I 2
lint: ${SRCS}
E 2
	lint ${CFLAGS} ${SRCS}

D 2
tags: ${SRCS} FRC
E 2
I 2
tags: ${SRCS}
E 2
	ctags ${SRCS}

FRC:
E 5
I 5
.include <bsd.prog.mk>
E 5
D 2

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

ni.o: ../common_source/ni.c ../common_source/tdef.h /usr/include/sys/param.h
ni.o: /usr/include/sys/types.h /usr/include/signal.h
ni.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
ni.o: /usr/include/signal.h
nii.o: ../common_source/nii.c ../common_source/tdef.h /usr/include/sys/param.h
nii.o: /usr/include/sys/types.h /usr/include/signal.h
nii.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
nii.o: /usr/include/signal.h ../common_source/sdef.h ../common_source/d.h
nii.o: ../common_source/v.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
nii.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
n1.o: ../common_source/n1.c ../common_source/tdef.h /usr/include/sys/param.h
n1.o: /usr/include/sys/types.h /usr/include/signal.h
n1.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
n1.o: /usr/include/signal.h /usr/include/sys/types.h /usr/include/sys/stat.h
n1.o: /usr/include/time.h ../common_source/d.h ../common_source/v.h
n1.o: ../common_source/sdef.h /usr/include/setjmp.h /usr/include/sgtty.h
n1.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
n1.o: /usr/include/sys/ttydev.h
n2.o: ../common_source/n2.c ../common_source/tdef.h /usr/include/sys/param.h
n2.o: /usr/include/sys/types.h /usr/include/signal.h
n2.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
n2.o: /usr/include/signal.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
n2.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
n2.o: ../common_source/d.h ../common_source/v.h ../common_source/sdef.h
n2.o: /usr/include/setjmp.h
n3.o: ../common_source/n3.c ../common_source/tdef.h /usr/include/sys/param.h
n3.o: /usr/include/sys/types.h /usr/include/signal.h
n3.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
n3.o: /usr/include/signal.h ../common_source/d.h ../common_source/v.h
n3.o: ../common_source/sdef.h
n4.o: ../common_source/n4.c ../common_source/tdef.h /usr/include/sys/param.h
n4.o: /usr/include/sys/types.h /usr/include/signal.h
n4.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
n4.o: /usr/include/signal.h ../common_source/d.h ../common_source/v.h
n4.o: ../common_source/sdef.h
n5.o: ../common_source/n5.c ../common_source/tdef.h /usr/include/sys/param.h
n5.o: /usr/include/sys/types.h /usr/include/signal.h
n5.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
n5.o: /usr/include/signal.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
n5.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
n5.o: ../common_source/d.h ../common_source/v.h ../common_source/sdef.h
t6.o: t6.c ../common_source/tdef.h /usr/include/sys/param.h
t6.o: /usr/include/sys/types.h /usr/include/signal.h
t6.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
t6.o: /usr/include/signal.h ../common_source/d.h ../common_source/v.h
n7.o: ../common_source/n7.c ../common_source/tdef.h /usr/include/sys/param.h
n7.o: /usr/include/sys/types.h /usr/include/signal.h
n7.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
n7.o: /usr/include/signal.h ../common_source/d.h ../common_source/v.h
n7.o: ../common_source/sdef.h
n8.o: ../common_source/n8.c ../common_source/tdef.h /usr/include/sys/param.h
n8.o: /usr/include/sys/types.h /usr/include/signal.h
n8.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
n8.o: /usr/include/signal.h
n9.o: ../common_source/n9.c ../common_source/tdef.h /usr/include/sys/param.h
n9.o: /usr/include/sys/types.h /usr/include/signal.h
n9.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
n9.o: /usr/include/signal.h ../common_source/d.h ../common_source/v.h
t10.o: t10.c ../common_source/tdef.h /usr/include/sys/param.h
t10.o: /usr/include/sys/types.h /usr/include/signal.h
t10.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
t10.o: /usr/include/signal.h ../common_source/d.h ../common_source/v.h
hytab.o: ../common_source/hytab.c
suftab.o: ../common_source/suftab.c
tab3.o: tab3.c

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 2
E 1
