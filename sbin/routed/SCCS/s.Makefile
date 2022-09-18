h00469
s 00000/00000/00022
d D 8.1 93/06/19 09:23:36 bostic 29 28
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00021
d D 5.18 93/06/19 09:23:31 bostic 28 26
c don't install query and trace by defualt
e
s 00000/00000/00022
d R 8.1 93/06/05 11:14:32 bostic 27 26
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00020
d D 5.17 93/04/27 18:07:39 bostic 26 25
c daemon(3) now in the C library
e
s 00001/00001/00021
d D 5.16 91/04/26 18:49:12 sklower 25 24
c vax/inline lives in a different place now
e
s 00002/00001/00020
d D 5.15 91/02/26 15:58:57 bostic 24 23
c needs compat for insque/remque
e
s 00001/00000/00020
d D 5.14 90/06/29 20:07:01 karels 23 22
c use daemon() call
e
s 00004/00002/00016
d D 5.13 90/05/20 19:08:51 bostic 22 21
c only use inline on the vax
e
s 00002/00000/00016
d D 5.12 90/05/11 13:01:07 bostic 21 20
c add SCCS header
e
s 00009/00056/00007
d D 5.11 90/05/11 13:00:31 bostic 20 19
c first pass for new make
e
s 00001/00001/00062
d D 5.10 90/05/04 09:00:41 bostic 19 18
c checkpoint for pmake
e
s 00003/00003/00060
d D 5.9 89/05/11 14:11:41 bostic 18 17
c file reorg, pathnames.h, paths.h
e
s 00012/00070/00051
d D 5.8 89/02/18 11:29:52 karels 17 16
c for bostic, I think he's done after 5 months
e
s 00010/00005/00111
d D 5.7 88/07/09 11:19:33 bostic 16 15
c install approved copyright notice
e
s 00015/00009/00101
d D 5.6 88/05/31 14:21:08 karels 15 14
c do tags on headers, too; don't remove tags
e
s 00014/00005/00096
d D 5.5 87/12/01 17:34:26 bostic 14 13
c do tools directory also
e
s 00082/00019/00019
d D 5.4 87/06/02 21:54:12 bostic 13 11
c new template
e
s 00082/00019/00019
d R 5.4 87/06/02 21:20:37 bostic 12 11
c new template
e
s 00002/00000/00036
d D 5.3 87/05/31 20:41:34 bostic 11 10
c added depend label
e
s 00003/00000/00033
d D 5.2 86/02/07 10:04:52 karels 10 9
c dependencies
e
s 00005/00000/00028
d D 5.1 85/06/04 16:45:41 dist 9 8
c Add copyright
e
s 00002/00002/00026
d D 4.7 84/12/20 17:59:32 karels 8 7
c asm => inline
e
s 00011/00002/00017
d D 4.6 84/05/07 17:02:58 karels 7 5
c use asm.sed for ntohl inline expansion; fix keywords
e
s 00010/00001/00018
d R 4.6 84/05/03 13:45:52 karels 6 5
c optimizations: simplify inet_checkhost, use faster hashing,
c in-line expansions of ntohl et al.
e
s 00001/00001/00018
d D 4.5 84/04/09 15:29:36 karels 5 4
c subnet routing
e
s 00003/00002/00016
d D 4.4 83/06/12 02:46:19 sam 4 3
c new signals
e
s 00000/00003/00018
d D 4.3 83/01/11 14:37:39 sam 3 2
c 4.1c conversion contortions
e
s 00000/00005/00021
d D 4.2 82/12/25 21:17:42 sam 2 1
c no more asm.sed
e
s 00026/00000/00000
d D 4.1 82/11/02 22:30:26 sam 1 0
c date and time created 82/11/02 22:30:26 by sam
e
u
U
t
T
I 21
#	%W% (Berkeley) %G%

E 21
I 9
D 20
#
D 13
# Copyright (c) 1983 Regents of the University of California.
E 13
I 13
# Copyright (c) 1987 Regents of the University of California.
E 13
D 14
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 14
I 14
# All rights reserved.
E 14
#
E 9
I 1
D 4
# %M% %G%
E 4
I 4
D 7
#	%M% (Berkeley) %G%
E 7
I 7
D 13
#	%W% (Berkeley) %G%
E 13
I 13
D 14
#	%W%	(Berkeley)	%G%
E 14
I 14
# Redistribution and use in source and binary forms are permitted
D 16
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific written prior permission. This software
# is provided ``as is'' without express or implied warranty.
E 16
I 16
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
E 16
E 14
E 13
E 7
#
I 14
#	%W% (Berkeley) %G%
#
E 14
E 4
D 13
ALL=	routed
E 13
I 13
CFLAGS=	-O
LIBC=	/lib/libc.a
D 18
C2=	/lib/c2
INLINE=	/sys/machine/inline/inline
E 18
I 18
C2=	/usr/libexec/c2
D 19
INLINE=	/usr/include/${MACHINE}/inline/inline
E 19
I 19
INLINE=	/sys/${MACHINE}/inline/inline
E 20
I 20
PROG=	routed
E 20
E 19
E 18
SRCS=	af.c if.c input.c main.c output.c startup.c tables.c timer.c \
	trace.c inet.c
E 13
D 20
OBJS=	af.o if.o input.o main.o output.o startup.o tables.o timer.o \
D 5
	trace.o
E 5
I 5
	trace.o inet.o
I 15
HDRS=	af.h defs.h interface.h table.h trace.h
I 17
MAN=	routed.0
E 20
I 20
MAN8=	routed.0
D 28
SUBDIR=	query trace
E 28
I 28
#SUBDIR=	query trace
E 28
I 23
D 24
LDADD=	-lutil
E 24
I 24
D 26
DPADD=	${LIBUTIL} ${LIBCOMPAT}
LDADD=	-lutil -lcompat
E 26
I 26
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
E 26
E 24
E 23
D 22
C2=	/usr/libexec/c2
INLINE=	/sys/${MACHINE}/inline/inline
E 22
E 20
E 17
E 15
E 5
D 7
CFLAGS=	-O
E 7
I 7
D 13
CFLAGS=
C2=	/lib/c2
D 8
ASMSCRIPT= /sys/machine/asm.sed
E 8
I 8
INLINE= /sys/machine/inline/inline
E 8
E 7
DESTDIR=
LDFLAGS=
E 13

D 2
.c.o:
	${CC} -S ${CFLAGS} $*.c
	sed -f ../asm.sed $*.s | ${AS} -o $*.o
	rm -f $*.s

E 2
D 13
all:	${ALL}
E 13
I 13
D 20
all: routed
E 20
I 20
.include <bsd.prog.mk>
E 20
E 13

I 22
.if (${MACHINE} == "vax")
E 22
D 13
routed: ${OBJS}
D 4
	${CC} -o routed ${LDFLAGS} ${OBJS} -ljobs
E 4
I 4
	${CC} -o routed ${LDFLAGS} ${OBJS}
E 13
I 13
D 17
routed:	${OBJS} ${LIBC}
E 17
I 17
D 20
routed: ${OBJS} ${LIBC}
E 17
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 13
E 4

E 20
D 3
${ALL}:	rip.h
${ALL}:	router.h

E 3
D 13
install: routed
	install -s routed ${DESTDIR}/etc
I 7

E 13
# The following can be deleted where not appropriate to use the kernel's
# inline code expansions.
I 22
D 25
INLINE=	/sys/vax/inline/inline
E 25
I 25
INLINE=	/sys/vax/inline/obj/inline
E 25
C2=	/usr/libexec/c2
E 22
.c.o:
D 20
	${CC} -S ${CFLAGS} $*.c
D 8
	${C2} $*.s | sed -f ${ASMSCRIPT} | ${AS} -o $*.o
E 8
I 8
	${C2} $*.s | ${INLINE} | ${AS} -o $*.o
E 8
	rm -f $*.s
E 7

D 13
clean:
	rm -f routed *.o core a.out t.c linterrs typescript errs
E 13
I 13
D 17
clean: FRC
E 17
I 17
clean:
E 17
D 14
	rm -f ${OBJS} core routed
E 14
I 14
D 15
	rm -f ${OBJS} core routed tags
E 15
I 15
	rm -f ${OBJS} core routed
E 15
	(cd tools; make ${MFLAGS} clean)
E 14
E 13
I 10

I 11
D 13
depend:
E 13
I 13
D 17
depend: FRC
E 17
I 17
cleandir: clean
	rm -f ${MAN} tags .depend
	(cd tools; make ${MFLAGS} cleandir)

depend: ${SRCS}
E 17
	mkdep ${CFLAGS} ${SRCS}
I 14
	(cd tools; make ${MFLAGS} depend)
E 14
E 13

E 11
D 13
${OBJS}: defs.h af.h defs.h interface.h table.h trace.h \
	/usr/include/protocols/routed.h
E 13
I 13
D 17
install: FRC
E 17
I 17
install: ${MAN}
E 17
D 18
	install -s -o bin -g bin -m 755 routed ${DESTDIR}/etc/routed
E 18
I 18
	install -s -o bin -g bin -m 755 routed ${DESTDIR}/usr/sbin
E 18
I 17
	install -c -o bin -g bin -m 444 routed.0 ${DESTDIR}/usr/man/cat8
E 17

D 17
lint: FRC
E 17
I 17
lint: ${SRCS}
E 17
	lint ${CFLAGS} ${SRCS}

D 17
tags: FRC
E 17
I 17
tags: ${SRCS}
E 17
D 15
	ctags ${SRCS}
E 15
I 15
	ctags ${HDRS} ${SRCS}
E 15
I 14
	(cd tools; make ${MFLAGS} tags)
E 20
I 20
	${CC} -S ${CFLAGS} ${.CURDIR}/${.PREFIX}.c
	@${C2} ${.PREFIX}.s | ${INLINE} | ${AS} -o ${.PREFIX}.o
	@rm -f ${.PREFIX}.s
I 22
.endif
E 22
E 20
E 14
D 17

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

af.o: af.c defs.h /usr/include/sys/types.h /usr/include/sys/socket.h
af.o: /usr/include/net/route.h /usr/include/netinet/in.h
af.o: /usr/include/protocols/routed.h /usr/include/stdio.h /usr/include/netdb.h
af.o: trace.h interface.h table.h af.h
if.o: if.c defs.h /usr/include/sys/types.h /usr/include/sys/socket.h
if.o: /usr/include/net/route.h /usr/include/netinet/in.h
if.o: /usr/include/protocols/routed.h /usr/include/stdio.h /usr/include/netdb.h
if.o: trace.h interface.h table.h af.h
input.o: input.c defs.h /usr/include/sys/types.h /usr/include/sys/socket.h
input.o: /usr/include/net/route.h /usr/include/netinet/in.h
input.o: /usr/include/protocols/routed.h /usr/include/stdio.h
input.o: /usr/include/netdb.h trace.h interface.h table.h af.h
input.o: /usr/include/sys/syslog.h
main.o: main.c defs.h /usr/include/sys/types.h /usr/include/sys/socket.h
main.o: /usr/include/net/route.h /usr/include/netinet/in.h
main.o: /usr/include/protocols/routed.h /usr/include/stdio.h
main.o: /usr/include/netdb.h trace.h interface.h table.h af.h
main.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 15
main.o: /usr/include/sys/ttydev.h /usr/include/sys/time.h /usr/include/time.h
main.o: /usr/include/net/if.h /usr/include/net/if_arp.h /usr/include/errno.h
D 14
main.o: /usr/include/signal.h /usr/include/syslog.h
E 14
I 14
main.o: /usr/include/signal.h /usr/include/machine/trap.h /usr/include/syslog.h
E 15
I 15
main.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
main.o: /usr/include/sys/time.h /usr/include/time.h /usr/include/net/if.h
main.o: /usr/include/net/if_arp.h /usr/include/sys/errno.h
main.o: /usr/include/sys/signal.h /usr/include/machine/trap.h
main.o: /usr/include/sys/syslog.h
E 15
E 14
output.o: output.c defs.h /usr/include/sys/types.h /usr/include/sys/socket.h
output.o: /usr/include/net/route.h /usr/include/netinet/in.h
output.o: /usr/include/protocols/routed.h /usr/include/stdio.h
output.o: /usr/include/netdb.h trace.h interface.h table.h af.h
startup.o: startup.c defs.h /usr/include/sys/types.h /usr/include/sys/socket.h
startup.o: /usr/include/net/route.h /usr/include/netinet/in.h
startup.o: /usr/include/protocols/routed.h /usr/include/stdio.h
startup.o: /usr/include/netdb.h trace.h interface.h table.h af.h
startup.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 15
startup.o: /usr/include/sys/ttydev.h /usr/include/net/if.h
startup.o: /usr/include/net/if_arp.h /usr/include/syslog.h
E 15
I 15
startup.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
startup.o: /usr/include/net/if.h /usr/include/net/if_arp.h
startup.o: /usr/include/syslog.h
E 15
tables.o: tables.c defs.h /usr/include/sys/types.h /usr/include/sys/socket.h
tables.o: /usr/include/net/route.h /usr/include/netinet/in.h
tables.o: /usr/include/protocols/routed.h /usr/include/stdio.h
tables.o: /usr/include/netdb.h trace.h interface.h table.h af.h
tables.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 15
tables.o: /usr/include/sys/ttydev.h /usr/include/errno.h /usr/include/syslog.h
E 15
I 15
tables.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
tables.o: /usr/include/errno.h /usr/include/sys/syslog.h
E 15
timer.o: timer.c defs.h /usr/include/sys/types.h /usr/include/sys/socket.h
timer.o: /usr/include/net/route.h /usr/include/netinet/in.h
timer.o: /usr/include/protocols/routed.h /usr/include/stdio.h
timer.o: /usr/include/netdb.h trace.h interface.h table.h af.h
trace.o: trace.c defs.h /usr/include/sys/types.h /usr/include/sys/socket.h
trace.o: /usr/include/net/route.h /usr/include/netinet/in.h
trace.o: /usr/include/protocols/routed.h /usr/include/stdio.h
trace.o: /usr/include/netdb.h trace.h interface.h table.h af.h
D 15
trace.o: /usr/include/sys/stat.h
E 15
I 15
trace.o: /usr/include/sys/stat.h /usr/include/sys/signal.h
trace.o: /usr/include/machine/trap.h
E 15
inet.o: inet.c defs.h /usr/include/sys/types.h /usr/include/sys/socket.h
inet.o: /usr/include/net/route.h /usr/include/netinet/in.h
inet.o: /usr/include/protocols/routed.h /usr/include/stdio.h
inet.o: /usr/include/netdb.h trace.h interface.h table.h af.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 17
E 13
E 10
E 1
