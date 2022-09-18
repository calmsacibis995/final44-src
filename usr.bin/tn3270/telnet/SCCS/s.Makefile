h01586
s 00000/00000/00087
d D 8.1 93/06/06 16:53:32 bostic 13 12
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00017/00087
d D 4.5 91/04/26 16:02:13 bostic 12 11
c new copyright; att/bsd/shared
e
s 00004/00060/00100
d D 4.4 90/06/06 09:53:55 borman 11 9
c Fix up makefile so that it will work with new make and
c obj directory.  Had to comment out the .c.obj line because the
c new make doesn't deal with it properly.
e
s 00004/00060/00100
d R 4.4 90/06/06 09:51:25 borman 10 9
c /usr/src/usr.bin/tn3270/telnet/SCCS
e
s 00003/00004/00157
d D 4.3 90/03/01 07:03:11 borman 9 8
c Clean up Makefile so that tn3270 will compile (add -DUSE_TERMIO)
e
s 00023/00000/00138
d D 4.2 89/09/02 14:53:29 minshall 8 7
c Add in new DEFINES to keep up to date with Dave Borman's telnet.
e
s 00000/00000/00138
d D 4.1 88/12/04 15:12:38 minshall 7 6
c Release 4.1
e
s 00011/00005/00127
d D 1.6 88/07/09 10:44:41 bostic 6 5
c install approved copyright notice
e
s 00001/00001/00131
d D 1.5 88/06/04 12:13:59 minshall 5 4
c Remove main target on a clean.
e
s 00003/00003/00129
d D 1.4 88/05/15 20:55:05 minshall 4 3
c Makefile_ultrix to sourcelist.
e
s 00004/00004/00128
d D 1.3 88/05/15 20:48:26 minshall 3 2
c Swap some things.  Target is now telprog.o.  For convenience, 
c distribute the main "telnet" makefile too.
e
s 00035/00010/00097
d D 1.2 88/05/15 12:46:21 minshall 2 1
c New targets for linting and tags; new telnet structure.
e
s 00107/00000/00000
d D 1.1 88/05/14 11:47:07 minshall 1 0
c date and time created 88/05/14 11:47:07 by minshall
e
u
U
t
T
I 6
D 12
#
E 6
I 1
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 6
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 12
#	%W% (Berkeley) %G%
D 12
#
E 12

# The following is the telnet makefile for tn3270, using the shared telnet
# sources.

I 8
#
# TERMCAP	Define this if your system is termcap based,
#		otherwise a terminfo based system is assumed.
#
# SRCRT		Includes code to allow you to specify source routes.
#		Format is:
#			[!]@hop1@hop2...[@|:]dst
#		Leading ! means strict source route.
#
# NOSTRNCASECMP	Define this if you do not have strncasecmp() in
#		your C libarary.
#
# USE_TERMIO	Define this if you have System V termio structures.
#		What is here is how things are on Cray computers.
#
# KLUDGELINEMODE Define this to get the kludged up version of linemode
#		that was in 4.3BSD.  This is a good thing to have
#		around for talking to older systems.
#

D 9
DEFINES= -DTERMCAP -DSRCRT -DKLUDGELINEMODE
E 9
I 9
DEFINES= -DTERMCAP -DSRCRT -DKLUDGELINEMODE -DUSE_TERMIO
E 9


E 8
D 11
VPATH	=	../../telnet/Source
D 2
INCLUDES=	-I../../telnet/Source -I.
DEFINES	=	-DTN3270
CFLAGS	=	-O ${INCLUDES} ${DEFINES}
E 2
I 2
XINCLUDES=	-I../../telnet/Source
INCLUDES=	-I.
E 11
I 11
VPATH	=	${.CURDIR}/../../telnet
XINCLUDES=	-I${.CURDIR}/../../telnet -I${.CURDIR}
INCLUDES=
E 11
XDEFINES	=	-DTN3270
OPTIMIZE=	-O
CFLAGS	=	${OPTIMIZE} ${INCLUDES} ${DEFINES}
XCFLAGS=	${XINCLUDES} ${XDEFINES}
E 2
LD	=	ld
LDFLAGS	=	-r
I 2
PRINT	= print
ACTION = sccs tell
E 2
D 11
LIBC=	/lib/libc.a
E 11
I 11
LIBC=	/usr/lib/libc.a
E 11
I 2
ALLH=	defines.h externs.h fdset.h general.h ring.h types.h
E 2
SRCS=	commands.c main.c network.c ring.c \
D 9
	sys_bsd.c sys_dos.c telnet.c terminal.c \
E 9
I 9
	sys_bsd.c telnet.c terminal.c \
E 9
	tn3270.c utilities.c
I 2
ALLHC=		${ALLH} ${SRCS}
D 3
ALLSOURCE=	${ALLHC}
ALLPRINT =	${ALLSOURCE}
E 3
I 3
ALLPRINT =	${ALLHC}
D 4
ALLSOURCE=	${ALLHC} Makefile
E 4
I 4
ALLSOURCE=	${ALLHC} Makefile Makefile_ultrix
E 4
E 3
E 2
D 9
OBJS=	commands.o main.o network.o ring.o sys_bsd.o sys_dos.o \
E 9
I 9
OBJS=	commands.o main.o network.o ring.o sys_bsd.o \
E 9
	telnet.o terminal.o tn3270.o utilities.o

D 2
all: telnet
E 2
I 2
.c.o:
	${CC} -c ${CFLAGS} ${XCFLAGS} $<
E 2

D 3
telnet:	${OBJS} ${LIBC}
E 3
I 3
telprog.o:	${OBJS} ${LIBC}
E 3
	${LD} ${LDFLAGS} -o $@ ${OBJS}

clean: FRC
D 5
	rm -f ${OBJS} core telnet
E 5
I 5
	rm -f telprog.o ${OBJS} core telnet
E 5

depend: FRC ${SRCS}
	mkdep ${CFLAGS} ${SRCS}

D 2
install: FRC
	install -s -o bin -g bin -m 755 telnet ${DESTDIR}/usr/ucb/telnet

lint: FRC
E 2
I 2
lint: FRC ${SRCS}
E 2
	lint ${CFLAGS} ${SRCS}

D 2
tags: FRC
	ctags ${SRCS}
E 2
I 2
D 4
tags: FRC ${ALLSOURCE}
	ctags ${ALLSOURCE}
E 4
I 4
tags: FRC ${ALLHC}
	ctags ${ALLHC}
E 4

print:	FRC ${ALLPRINT}
	${PRINT} ${ALLPRINT}

action: FRC
	${ACTION}

clist:	FRC ${SRCS}
	@for i in ${SRCS} ; \
		do (echo ${DIRPATH}$$i); done

hclist:	FRC ${ALLHC}
	@for i in ${ALLHC} ; \
		do (echo ${DIRPATH}$$i); done

sourcelist:	FRC ${ALLSOURCE}
D 3
	@for i in ${ALLSOURCE} ; \
E 3
I 3
	@for i in ${ALLSOURCE} ../../telnet/Makefile ; \
E 3
		do (echo ${DIRPATH}$$i); done
E 2

FRC:
D 11

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

commands.o: ../../telnet/Source/commands.c /usr/include/sys/types.h
commands.o: /usr/include/sys/socket.h /usr/include/netinet/in.h
commands.o: /usr/include/signal.h /usr/include/machine/trap.h
commands.o: /usr/include/netdb.h /usr/include/ctype.h
commands.o: /usr/include/arpa/telnet.h ../../telnet/Source/ring.h
commands.o: ../../telnet/Source/externs.h /usr/include/stdio.h
commands.o: /usr/include/setjmp.h ../../telnet/Source/defines.h
commands.o: ../../telnet/Source/types.h
main.o: ../../telnet/Source/main.c /usr/include/sys/types.h
main.o: ../../telnet/Source/ring.h ../../telnet/Source/externs.h
main.o: /usr/include/stdio.h /usr/include/setjmp.h
main.o: ../../telnet/Source/defines.h
network.o: ../../telnet/Source/network.c /usr/include/sys/types.h
network.o: /usr/include/sys/socket.h /usr/include/sys/time.h
network.o: /usr/include/time.h /usr/include/errno.h /usr/include/arpa/telnet.h
network.o: ../../telnet/Source/ring.h ../../telnet/Source/defines.h
network.o: ../../telnet/Source/externs.h /usr/include/stdio.h
network.o: /usr/include/setjmp.h ../../telnet/Source/fdset.h
ring.o: ../../telnet/Source/ring.c /usr/include/stdio.h /usr/include/errno.h
ring.o: /usr/include/sys/types.h /usr/include/sys/ioctl.h
ring.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
ring.o: /usr/include/sys/socket.h ../../telnet/Source/ring.h
ring.o: ../../telnet/Source/general.h
sys_bsd.o: ../../telnet/Source/sys_bsd.c /usr/include/sys/ioctl.h
sys_bsd.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
sys_bsd.o: /usr/include/sys/types.h /usr/include/sys/time.h /usr/include/time.h
sys_bsd.o: /usr/include/sys/socket.h /usr/include/signal.h
sys_bsd.o: /usr/include/machine/trap.h /usr/include/errno.h
sys_bsd.o: ../../telnet/Source/ring.h ../../telnet/Source/fdset.h
sys_bsd.o: ../../telnet/Source/defines.h ../../telnet/Source/externs.h
sys_bsd.o: /usr/include/stdio.h /usr/include/setjmp.h
sys_bsd.o: ../../telnet/Source/types.h
D 9
sys_dos.o: ../../telnet/Source/sys_dos.c
E 9
telnet.o: ../../telnet/Source/telnet.c /usr/include/sys/types.h
telnet.o: /usr/include/curses.h /usr/include/stdio.h /usr/include/sgtty.h
telnet.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
telnet.o: /usr/include/sys/ttydev.h /usr/include/arpa/telnet.h
telnet.o: /usr/include/strings.h ../../telnet/Source/ring.h
telnet.o: ../../telnet/Source/defines.h ../../telnet/Source/externs.h
telnet.o: /usr/include/stdio.h /usr/include/setjmp.h
telnet.o: ../../telnet/Source/types.h ../../telnet/Source/general.h
telnet.o: /usr/include/varargs.h
terminal.o: ../../telnet/Source/terminal.c /usr/include/arpa/telnet.h
terminal.o: /usr/include/sys/types.h ../../telnet/Source/ring.h
terminal.o: ../../telnet/Source/externs.h /usr/include/stdio.h
terminal.o: /usr/include/setjmp.h ../../telnet/Source/types.h
tn3270.o: ../../telnet/Source/tn3270.c ../../telnet/Source/fdset.h
utilities.o: ../../telnet/Source/utilities.c /usr/include/arpa/telnet.h
utilities.o: /usr/include/sys/types.h /usr/include/ctype.h
utilities.o: ../../telnet/Source/ring.h ../../telnet/Source/externs.h
utilities.o: /usr/include/stdio.h /usr/include/setjmp.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 11
E 1
