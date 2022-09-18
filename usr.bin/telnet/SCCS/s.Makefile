h39871
s 00000/00000/00047
d D 8.1 93/06/06 16:34:02 bostic 28 27
c 4.4BSD snapshot (revision 8.1)
e
s 00022/00000/00025
d D 5.9 93/05/21 10:23:27 dab 27 26
c Add "nocrypt" target to create a subdirectory
e
s 00001/00000/00024
d D 5.8 93/04/05 17:05:48 dab 26 25
c Fix gcc2 warnings.
c Fix the generation/parsing of the Environment option SEND suboption.
c Add code (#ifdef ENV_HACK) to help interoperation with Telnet servers
c that have the definitions for ENV_VAR and ENV_VALUE reversed.
e
s 00001/00001/00023
d D 5.7 92/12/18 14:06:40 dab 25 24
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00001/00001/00023
d D 5.6 91/03/05 16:33:08 dab 24 23
c Change -I/usr/src/lib to -I${.CURDIR}/../../lib
c to make things a bit more portable.
e
s 00001/00001/00023
d D 5.5 91/03/01 02:12:52 dab 23 22
c fix sccs.include.redist line
e
s 00015/00025/00009
d D 5.4 91/03/01 01:31:59 dab 22 21
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
e
s 00002/00002/00032
d D 5.3 90/06/28 12:58:42 borman 21 20
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00002/00000/00032
d D 5.2 90/06/20 16:44:40 kfall 20 19
c towards Kerberized telnet
e
s 00006/00097/00026
d D 5.1 90/05/11 15:19:27 bostic 19 17
c first pass for new make
e
s 00001/00001/00122
d R 1.18 90/03/01 06:20:26 borman 18 17
c Add -DNEED_GETTOS for preliminary TOS support
e
s 00026/00007/00097
d D 1.17 89/11/14 10:21:02 borman 17 16
c Latest and greatest version of telnet
e
s 00036/00004/00068
d D 1.16 89/09/01 15:46:57 borman 16 15
c RFC 1091 term type support, STATUS support, BINARY changes
e
s 00003/00001/00069
d D 1.15 89/08/22 09:28:21 borman 15 14
c Add installation of the man page
e
s 00001/00001/00069
d D 1.14 89/08/21 14:59:37 borman 14 13
c Add support fro LINEMODE option
e
s 00001/00047/00069
d D 1.13 89/05/11 09:39:08 bostic 13 12
c file reorg, pathnames.h, paths.h
e
s 00004/00001/00112
d D 1.12 88/10/11 13:53:06 bostic 12 11
c add cleandir label
e
s 00010/00005/00103
d D 1.11 88/07/09 10:41:42 bostic 11 10
c install approved copyright notice
e
s 00001/00001/00107
d D 1.10 88/06/27 22:10:24 minshall 10 9
c Clean up "tags" file.
e
s 00018/00005/00090
d D 1.9 88/06/27 22:07:40 minshall 9 8
c Make "tags" and "lint" work.
e
s 00050/00032/00045
d D 1.8 88/03/21 22:18:49 minshall 8 7
c New structure; new 'make depend'.
e
s 00009/00003/00068
d D 1.7 88/03/08 10:30:41 bostic 7 6
c add Berkeley specific copyright
e
s 00000/00001/00071
d D 1.6 88/02/17 22:31:50 bostic 6 5
c compile optimized
e
s 00001/00000/00071
d D 1.5 87/10/10 14:27:19 minshall 5 4
c This is the first version to get near rings.  It compiles,
c but doesn't work.
e
s 00060/00116/00011
d D 1.4 87/10/10 12:35:56 minshall 4 3
c This is the approved style.
e
s 00002/00002/00125
d D 1.3 87/09/25 14:50:15 minshall 3 2
c Incorporate tn3270.c.
e
s 00001/00001/00126
d D 1.2 87/09/11 15:59:30 minshall 2 1
c Correct .h files.
e
s 00127/00000/00000
d D 1.1 87/09/11 15:40:53 minshall 1 0
c date and time created 87/09/11 15:40:53 by minshall
e
u
U
t
T
I 1
D 4
# msdos versus unix defines
O	= .o
#PC_O	= .obj
E 4
I 4
D 19
#
# Copyright (c) 1987 Regents of the University of California.
D 7
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 7
I 7
# All rights reserved.
E 7
#
D 7
#	%W%	(Berkeley)	%G%
E 7
I 7
# Redistribution and use in source and binary forms are permitted
D 11
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 11
I 11
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
E 19
D 22
#	%W% (Berkeley) %G%
E 22
E 7
#
D 8
CFLAGS=	-O
E 8
I 8
D 19

# The following is the telnet makefile.  The sources are down one level
# in directory "Source" because the sources are shared between telnet
# and tn3270.

VPATH	=	Source
INCLUDES=	-ISource
D 14
CFLAGS=	-O ${INCLUDES}
E 14
I 14
D 16
CFLAGS=	-O ${INCLUDES} -DSRCRT -DKLUDGELINEMODE
E 14
E 8
I 5
D 6
CFLAGS=	-g
E 6
E 5
LIBC=	/lib/libc.a
E 16
I 16

#
E 19
D 22
# TERMCAP	Define this if your system is termcap based,
#		otherwise a terminfo based system is assumed.
E 22
I 22
# Copyright (c) 1990 The Regents of the University of California.
# All rights reserved.
E 22
#
D 22
# SRCRT		Includes code to allow you to specify source routes.
#		Format is:
#			[!]@hop1@hop2...[@|:]dst
#		Leading ! means strict source route.
E 22
I 22
D 23
# %sccs.include.redist.sh
E 23
I 23
# %sccs.include.redist.sh%
E 23
E 22
#
D 17
# NOSTRNCASECMP	Define this if you do not have strncasecmp() in
#		your C libarary.
#
E 17
D 22
# USE_TERMIO	Define this if you have System V termio structures.
#		What is here is how things are on Cray computers.
E 22
I 22
#	%W% (Berkeley) %G%
E 22
#
D 22
# KLUDGELINEMODE Define this to get the kludged up version of linemode
#		that was in 4.3BSD.  This is a good thing to have
#		around for talking to older systems.
#
I 17
# NOSTRNCASECMP	Define this if you do not have strncasecmp() in
#		your C libarary.
#
# strrchr=rindex Define this if you do not have strrchr() in your
#		C libaray (but you do have rindex...)
#
E 22
I 22

E 22
I 19
PROG=	telnet
D 21
CFLAGS+=-DTERMCAP -DSRCRT -DKLUDGELINEMODE -DUSE_TERMIO
I 20
#CFLAGS+=-DTERMCAP -DSRCRT -DKLUDGELINEMODE -DUSE_TERMIO -DKERBEROS
E 21
I 21
D 22
CFLAGS+=-DTERMCAP -DSRCRT -DKLUDGELINEMODE -DUSE_TERMIO -DNEED_GETTOS
#CFLAGS+=-DTERMCAP -DSRCRT -DKLUDGELINEMODE -DUSE_TERMIO -DNEED_GETTOS -DKERBEROS
E 21
E 20
LDADD=	-ltermcap
I 20
#LDADD=	-ltermcap -ldes -lkrb
E 22
I 22

D 25
CFLAGS+=-DTERMCAP -DKLUDGELINEMODE -DUSE_TERMIO -DAUTHENTICATE -DENCRYPT
E 25
I 25
CFLAGS+=-DTERMCAP -DKLUDGELINEMODE -DUSE_TERMIO -DAUTHENTICATION -DENCRYPTION
I 26
CFLAGS+=-DENV_HACK
E 26
E 25
D 24
CFLAGS+=-I/usr/src/lib
E 24
I 24
CFLAGS+=-I${.CURDIR}/../../lib
E 24

CFLAGS+= -DKRB4

LDADD=	-ltermcap -ltelnet
LDADD+=	-lkrb -ldes
E 22
E 20
DPADD=	${LIBTERMCAP}
E 19
E 17

D 17
DEFINES= -DTERMCAP -DSRCRT -DKLUDGELINEMODE
E 17
I 17
D 19
DEFINES= -DTERMCAP -DSRCRT -DKLUDGELINEMODE -DUSE_TERMIO
E 17

#
# LIBS should be set to any libraries that need to be included,
# like the termcap or terminfo library.  LIBPATH is the paths
# to these libraries, for dependencies.
#	For CRAY: LIBS= -lcurses -lnet
#
LIBS=	-ltermcap
LIBPATH= /lib/libc.a /usr/lib/libtermcap.a

E 16
D 8
SRCS=	commands.c main.c network.c ring.c sys_bsd.c sys_dos.c \
	telnet.c terminal.c tn3270.c utilities.c
E 8
I 8
SRCS=	commands.c main.c network.c ring.c \
D 17
	sys_bsd.c sys_dos.c telnet.c terminal.c \
E 17
I 17
	sys_bsd.c telnet.c terminal.c \
E 19
I 19
D 22
SRCS=	commands.c main.c network.c ring.c sys_bsd.c telnet.c terminal.c \
E 19
E 17
	tn3270.c utilities.c
E 22
I 22
SRCS=	authenc.c commands.c main.c network.c ring.c sys_bsd.c telnet.c \
	terminal.c tn3270.c utilities.c
E 22
I 9

I 27
# These are the sources that have encryption stuff in them.
CRYPT_SRC= authenc.c commands.c externs.h main.c network.c
CRYPT_SRC+= ring.c ring.h telnet.c terminal.c utilities.c Makefile
NOCRYPT_DIR=${.CURDIR}/Nocrypt

E 27
I 16
D 19
CFLAGS=	-O ${INCLUDES} ${DEFINES}

E 16
ALLHC=	${SRCS} \
	Source/defines.h Source/externs.h Source/fdset.h Source/general.h \
	Source/ring.h Source/types.h

E 9
E 8
D 17
OBJS=	commands.o main.o network.o ring.o sys_bsd.o sys_dos.o \
E 17
I 17
OBJS=	commands.o main.o network.o ring.o sys_bsd.o \
E 17
	telnet.o terminal.o tn3270.o utilities.o
I 15
MAN=	telnet.0
E 15
E 4

I 17
#
# 4.4BSD
#		DEST=${DESTDIR}/usr/bin
#
# 4.3BSD
#		DEST=${DESTDIR}/usr/ucb
#
DEST=${DESTDIR}/usr/bin

#
# These next three lines are not needed in 4.4BSD
#
# .SUFFIXES: .0 .1
# .1.0:
# 	nroff -man -h $< > $@

E 17
D 4
X	=
#PC_X	= .exe
E 4
I 4
all: telnet
E 4

D 4
L	=
#PC_L	= -link
E 4
I 4
D 16
telnet:	${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 16
I 16
telnet:	${OBJS} ${LIBPATH}
	${CC} -o $@ ${CFLAGS} ${OBJS} ${LIBS}
E 16
E 4

D 4
CC	= cc
#PC_CC	= cl
E 4
I 4
clean: FRC
D 10
	rm -f ${OBJS} core telnet
E 10
I 10
D 12
	rm -f ${OBJS} core errs l.errs tags telnet
E 12
I 12
	rm -f ${OBJS} core errs l.errs telnet

cleandir: clean
	rm -f ${MAN} tags .depend
E 12
E 10
E 4

I 9
clist:	FRC ${SRCS}
	@for i in ${SRCS} ; \
		do (echo ${DIRPATH}$$i); done

hclist:	FRC ${ALLHC}
	@for i in ${ALLHC} ; \
		do (echo ${DIRPATH}$$i); done

E 9
D 4
MV	= mv
#PC_MV	= rename
E 4
I 4
D 8
depend: FRC
E 8
I 8
depend: FRC ${SRCS}
E 8
D 9
	mkdep ${CFLAGS} ${SRCS}
E 9
I 9
	mkdep ${CFLAGS} `make clist`
E 9
E 4

D 4
RM	= rm -f
#PC_RM= erase
E 4
I 4
D 15
install: FRC
E 15
I 15
install: ${MAN} FRC
E 15
D 13
	install -s -o bin -g bin -m 755 telnet ${DESTDIR}/usr/ucb/telnet
E 13
I 13
D 17
	install -s -o bin -g bin -m 755 telnet ${DESTDIR}/usr/bin
E 17
I 17
	install -s -o bin -g bin -m 755 telnet ${DEST}
E 17
I 15
	install -c -o bin -g bin -m 444 telnet.0 ${DESTDIR}/usr/man/cat1
E 15
E 13
E 4

D 4
LINT_ARGS =
#PC_LINT_ARGS = -DLINT_ARGS
E 4
I 4
D 9
lint: FRC
	lint ${CFLAGS} ${SRCS}
E 9
I 9
lint: FRC ${SRCS}
	lint ${CFLAGS} `make clist`
E 9
E 4

D 4
DEBUG_FLAGS = -g
#PC_DEBUG_FLAGS = -Zi -Od
E 4
I 4
D 9
tags: FRC
	ctags ${SRCS}
E 9
I 9
tags: FRC ${SRCS}
	ctags `make hclist`
E 9
E 4

D 4
AR	= ar
AR1	= cr
AR2	=
AR3	=
#PC_AR	= lib
#PC_AR1	=
#PC_AR2	= +
#PC_AR3	= ";"
E 4
I 4
FRC:
E 19
I 19
.include <bsd.prog.mk>
I 27

nocrypt:
#ifdef	ENCRYPTION
	@for i in ${CRYPT_SRC}; do \
	    if [ ! -d ${NOCRYPT_DIR} ]; then \
		echo Creating subdirectory ${NOCRYPT_DIR}; \
		mkdir ${NOCRYPT_DIR}; \
	    fi; \
	    echo ${NOCRYPT_DIR}/$$i; \
	    unifdef -UENCRYPTION ${.CURDIR}/$$i | \
		sed "s/ || defined(ENCRYPTION)//" > ${NOCRYPT_DIR}/$$i; \
	done

placeholder:
#else	/* ENCRYPTION */
	@echo "Encryption code already removed."
#endif	/* ENCRYPTION */
E 27
E 19
E 4
D 13

D 4
RANLIB	= ranlib
#PC_RANLIB = echo "Done with "
E 4
I 4
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 4

D 4
PRINT	= print
E 4
I 4
D 8
commands.o: commands.c /usr/include/sys/types.h /usr/include/sys/socket.h
commands.o: /usr/include/netinet/in.h /usr/include/signal.h
commands.o: /usr/include/machine/trap.h /usr/include/netdb.h
commands.o: /usr/include/ctype.h /usr/include/arpa/telnet.h externs.h
commands.o: /usr/include/stdio.h /usr/include/setjmp.h defines.h types.h
main.o: main.c externs.h /usr/include/stdio.h /usr/include/setjmp.h defines.h
network.o: network.c /usr/include/sys/types.h /usr/include/sys/socket.h
E 8
I 8
commands.o: Source/commands.c /usr/include/sys/types.h
commands.o: /usr/include/sys/socket.h /usr/include/netinet/in.h
commands.o: /usr/include/signal.h /usr/include/machine/trap.h
commands.o: /usr/include/netdb.h /usr/include/ctype.h
commands.o: /usr/include/arpa/telnet.h Source/ring.h Source/externs.h
commands.o: /usr/include/stdio.h /usr/include/setjmp.h Source/defines.h
commands.o: Source/types.h
main.o: Source/main.c /usr/include/sys/types.h Source/ring.h Source/externs.h
main.o: /usr/include/stdio.h /usr/include/setjmp.h Source/defines.h
network.o: Source/network.c /usr/include/sys/types.h /usr/include/sys/socket.h
E 8
network.o: /usr/include/sys/time.h /usr/include/time.h /usr/include/errno.h
D 8
network.o: /usr/include/arpa/telnet.h defines.h externs.h /usr/include/stdio.h
network.o: /usr/include/setjmp.h
sys_bsd.o: sys_bsd.c /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
sys_bsd.o: /usr/include/sys/ttydev.h /usr/include/sys/time.h
sys_bsd.o: /usr/include/time.h /usr/include/signal.h
sys_bsd.o: /usr/include/machine/trap.h defines.h externs.h /usr/include/stdio.h
sys_bsd.o: /usr/include/setjmp.h types.h
sys_dos.o: sys_dos.c
telnet.o: telnet.c /usr/include/sys/types.h /usr/include/sys/time.h
telnet.o: /usr/include/time.h /usr/include/sys/socket.h
telnet.o: /usr/include/netinet/in.h /usr/include/curses.h /usr/include/stdio.h
telnet.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
E 8
I 8
network.o: /usr/include/arpa/telnet.h Source/ring.h Source/defines.h
network.o: Source/externs.h /usr/include/stdio.h /usr/include/setjmp.h
network.o: Source/fdset.h
ring.o: Source/ring.c /usr/include/stdio.h /usr/include/errno.h
ring.o: /usr/include/sys/types.h /usr/include/sys/ioctl.h
ring.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
ring.o: /usr/include/sys/socket.h Source/ring.h Source/general.h
sys_bsd.o: Source/sys_bsd.c /usr/include/sys/ioctl.h
sys_bsd.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
sys_bsd.o: /usr/include/sys/types.h /usr/include/sys/time.h /usr/include/time.h
sys_bsd.o: /usr/include/sys/socket.h /usr/include/signal.h
sys_bsd.o: /usr/include/machine/trap.h /usr/include/errno.h Source/ring.h
sys_bsd.o: Source/fdset.h Source/defines.h Source/externs.h
sys_bsd.o: /usr/include/stdio.h /usr/include/setjmp.h Source/types.h
sys_dos.o: Source/sys_dos.c
telnet.o: Source/telnet.c /usr/include/sys/types.h /usr/include/curses.h
telnet.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
E 8
telnet.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
D 8
telnet.o: /usr/include/arpa/telnet.h /usr/include/arpa/inet.h
telnet.o: /usr/include/ctype.h /usr/include/errno.h /usr/include/netdb.h
telnet.o: /usr/include/strings.h defines.h externs.h /usr/include/stdio.h
telnet.o: /usr/include/setjmp.h types.h general.h
terminal.o: terminal.c /usr/include/arpa/telnet.h externs.h
terminal.o: /usr/include/stdio.h /usr/include/setjmp.h types.h
tn3270.o: tn3270.c
utilities.o: utilities.c /usr/include/arpa/telnet.h /usr/include/ctype.h
utilities.o: externs.h /usr/include/stdio.h /usr/include/setjmp.h
E 8
I 8
telnet.o: /usr/include/arpa/telnet.h /usr/include/strings.h Source/ring.h
telnet.o: Source/defines.h Source/externs.h /usr/include/stdio.h
telnet.o: /usr/include/setjmp.h Source/types.h Source/general.h
telnet.o: /usr/include/varargs.h
terminal.o: Source/terminal.c /usr/include/arpa/telnet.h
terminal.o: /usr/include/sys/types.h Source/ring.h Source/externs.h
terminal.o: /usr/include/stdio.h /usr/include/setjmp.h Source/types.h
tn3270.o: Source/tn3270.c Source/fdset.h
utilities.o: Source/utilities.c /usr/include/arpa/telnet.h
utilities.o: /usr/include/sys/types.h /usr/include/ctype.h Source/ring.h
utilities.o: Source/externs.h /usr/include/stdio.h /usr/include/setjmp.h
E 8
E 4

D 4
DEFINES = ${LINT_ARGS}

INCLUDES = -I.

OPTIMIZE = -O
OPTIMIZE = ${DEBUG_FLAGS}

CFLAGS	= $(OPTIMIZE) $(INCLUDES) $(DEFINES)

# Lint flags
LINTFLAGS	= -hbxaz

# The source files...
D 2
ALLH =	extern.h
E 2
I 2
ALLH =	defines.h externs.h general.h types.h
E 2

ALLC =	commands.c main.c network.c sys_bsd.c sys_dos.c telnet.c \
D 3
		terminal.c utilities.c
E 3
I 3
		terminal.c tn3270.c utilities.c
E 3

ALLO =	commands$O main$O network$O sys_bsd$O sys_dos$O telnet$O \
D 3
		terminal$O utilities$O
E 3
I 3
		terminal$O tn3270$O utilities$O
E 3

ALLPRINT =	${ALLH} ${ALLC}

ALLSOURCE =	${ALLPRINT} Makefile

.s.o:
	/lib/cpp -E $< | as -o $@

.c.obj:
	${CC} ${CFLAGS} -c $<

telnet$X:	${ALLO}
	${CC} ${CFLAGS} -o telnet ${ALLO}

clean:
	for i in $(ALLO) telnet$X errs \
		Makefile.bak; \
			do (${RM} $$i); done

sccsclean:
	-sccs clean
	-sccs get Makefile

sourcelist:	${ALLSOURCE}
	@for i in ${ALLSOURCE}; \
		do (echo ${DIRPATH}$$i); done

print:
	${PRINT} ${ALLPRINT}

tags:	${ALLC} ${ALLH}
	ctags -t ${ALLC} ${ALLH}

action:
	${ACTION}

lint:
	lint ${LINTFLAGS} ${INCLUDES} ${DEFINES} ${ALLC} -lcurses

.DEFAULT:
	sccs get $<

depend:
	grep '^#include' ${ALLC} | grep -v '<' | \
	sed -e 's/:[^"]*"\([^"]*\)".*/: \1/' \
	    -e 's/\.c/$$O/' | \
	awk ' { if ($$1 != prev) { print rec; rec = $$0; prev = $$1; } \
		else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
		       else rec = rec " " $$2 } } \
	      END { print rec } ' > makedep
	echo '$$r makedep' >>eddep
	echo '/^# DO NOT DELETE THIS LINE/+1,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	-rm -f Makefile.bak
	cp Makefile Makefile.bak
	ed - Makefile < eddep
	rm eddep makedep

# DO NOT DELETE THIS LINE

commands$O: externs.h defines.h types.h
main$O: externs.h
network$O: externs.h
sys_bsd$O: externs.h
telnet$O: externs.h types.h general.h
terminal$O: externs.h types.h
utilities$O: externs.h
E 4
I 4
# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 13
E 4
E 1
