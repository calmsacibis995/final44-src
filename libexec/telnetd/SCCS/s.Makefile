h03254
s 00002/00001/00034
d D 8.2 93/12/15 11:50:00 dab 21 20
c A support for new ENVIRON option
e
s 00000/00000/00035
d D 8.1 93/06/04 19:07:36 bostic 20 19
c 4.4BSD snapshot (revision 8.1)
e
s 00022/00000/00013
d D 5.19 93/05/21 10:28:09 dab 19 18
c Add "nocrypt" target to create a subdirectory
c with source with encryption removed.
e
s 00001/00001/00012
d D 5.18 93/04/05 16:48:19 dab 18 17
c Fix gcc2 warnings.
c Add ENV_HACK stuff to deal with telnet clients that
c have the wrong definitions for ENV_VAR and ENV_VALUE.
c Fix up the flow-control processing to work on systems
c that don't use Linemode in the server.
e
s 00001/00001/00012
d D 5.17 92/12/18 14:05:38 dab 17 16
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00000/00007/00013
d D 5.16 91/05/13 17:35:20 bostic 16 15
c new copyright; att/bsd/shared
e
s 00001/00001/00019
d D 5.15 91/03/05 16:30:51 bostic 15 14
c relative includes
e
s 00001/00001/00019
d D 5.14 91/03/01 02:15:39 dab 14 13
c Fix sccs.include.redist.sh line
e
s 00012/00004/00008
d D 5.13 91/03/01 01:35:19 dab 13 12
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
c Bug fixes and code cleanup
e
s 00001/00001/00011
d D 5.12 91/01/21 09:44:41 bostic 12 11
c delete get_date, just use strftime
e
s 00001/00001/00011
d D 5.11 90/06/30 14:39:46 bostic 11 10
c use relative path
e
s 00002/00001/00010
d D 5.10 90/06/28 13:05:58 borman 10 9
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00000/00001/00011
d D 5.9 90/06/27 17:07:58 karels 9 8
c add IP type-of-service without gettos (at least for now)
e
s 00009/00087/00003
d D 5.8 90/05/11 12:55:27 bostic 8 7
c first pass for new make
e
s 00001/00001/00089
d D 5.7 90/02/28 15:36:08 borman 7 6
c Many fixes.  1) Use the cc_t typedef from termios.h
c 2) Fix for SYSV VEOF/VMIN overlap
c 3) Add two missing "break" statements
c 4) Add SLC_FORW[12] support
c 5) start of TOS support
c 6) Make sure things get initialized properly
c 7) Don't send Urgent mode data, since some clients go into infinate loops...
e
s 00016/00002/00074
d D 5.6 89/11/10 10:22:53 borman 6 5
c Fix bugs in state machine, add more TERMIOS support
e
s 00033/00005/00043
d D 5.5 89/09/01 15:16:34 borman 5 4
c New telnetd, with LINEMODE support
e
s 00001/00001/00047
d D 5.4 89/05/11 14:34:02 bostic 4 3
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00047
d D 5.3 89/03/18 17:55:30 minshall 3 2
c Install in /usr/libexec, just like rlogind.
e
s 00005/00006/00043
d D 5.2 88/09/20 09:48:01 bostic 2 1
c cleanup
e
s 00049/00000/00000
d D 5.1 88/08/31 12:08:11 bostic 1 0
c date and time created 88/08/31 12:08:11 by bostic
e
u
U
t
T
I 13
D 16
#
# Copyright (c) 1990 The Regents of the University of California.
# All rights reserved.
#
D 14
# %sccs.include.redist.sh
E 14
I 14
# %sccs.include.redist.sh%
E 14
#
E 16
E 13
I 1
D 8
#
# Copyright (c) 1988 The Regents of the University of California.
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
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
E 8
#	%W% (Berkeley) %G%
I 13
D 16
#
E 16
E 13
D 8
#
E 8
D 5
CFLAGS=	-O
E 5
I 5

D 7
DEFINES=
E 7
I 7
D 8
DEFINES= -DNEED_GETTOS
E 7
E 5
LIBC=	/lib/libc.a
D 5
SRCS=	telnetd.c get_date.c gettytab.c
OBJS=	telnetd.o get_date.o gettytab.o
E 5
I 5
# 4.4BSD
#		LIBS= -lutil -ltermcap
#		GETTYOBJ= get_date.o gettytab.o
#		GETTYSRC= get_date.c gettytab.c
#		LIBEXEC=${DESTDIR}/usr/libexec
I 6
#		VPATH=../getty
#			or
#		VPATH=/usr/src/libexec/getty
E 6
#
# 4.3BSD	LIBS= -ltermcap
#		GETTYOBJ= get_date.o gettytab.o
#		GETTYSRC= get_date.c gettytab.c
#		LIBEXEC=${DESTDIR}/etc
I 6
#		VPATH=../getty
#			or
#		VPATH=/usr/src/etc/getty
E 6
#
# Cray UNICOS
#		LIBS= -lnet -lcurses
#		GETTYOBJ=
#		GETTYSRC=
#		LIBEXEC=${DESTDIR}/etc
E 8
I 8
PROG=	telnetd
I 10
D 13
CFLAGS+=-DNEED_GETTOS -DLINEMODE -DKLUDGELINEMODE -DUSE_TERMIO -DDIAGNOSTICS
E 10
D 9
CFLAGS+=-DNEED_GETTOS
E 9
D 12
SRCS=	get_date.c gettytab.c global.c slc.c state.c sys_term.c telnetd.c \
E 12
I 12
SRCS=	gettytab.c global.c slc.c state.c sys_term.c telnetd.c \
E 13
I 13
D 18
CFLAGS+=-DLINEMODE -DKLUDGELINEMODE -DUSE_TERMIO -DDIAGNOSTICS
E 18
I 18
D 21
CFLAGS+=-DLINEMODE -DKLUDGELINEMODE -DUSE_TERMIO -DDIAGNOSTICS -DENV_HACK
E 21
I 21
CFLAGS+=-DLINEMODE -DKLUDGELINEMODE -DUSE_TERMIO -DDIAGNOSTICS
CFLAGS+=-DOLD_ENVIRON -DENV_HACK
E 21
E 18
D 15
CFLAGS+=-DAUTHENTICATE -DENCRYPT -I/usr/src/lib
E 15
I 15
D 17
CFLAGS+=-DAUTHENTICATE -DENCRYPT -I${.CURDIR}/../../lib
E 17
I 17
CFLAGS+=-DAUTHENTICATION -DENCRYPTION -I${.CURDIR}/../../lib
E 17
E 15
SRCS=	authenc.c global.c slc.c state.c sys_term.c telnetd.c \
E 13
E 12
	termstat.c utility.c
DPADD=	${LIBUTIL} ${LIBTERM}
D 13
LDADD=	-lutil -ltermcap
E 13
I 13
LDADD=	-lutil -ltermcap -ltelnet
LDADD+=	-lkrb -ldes
E 13
MAN8=	telnetd.0
D 10
.PATH:	${.CURDIR}/../getty
E 10
I 10
D 11
.PATH:	/usr/src/libexec/getty
E 11
I 11
D 13
.PATH:	${.CURDIR}/../getty
E 13
E 11
E 10
E 8

I 19
# These are the sources that have encryption stuff in them.
CRYPT_SRC= authenc.c ext.h state.c telnetd.c termstat.c
CRYPT_SRC+= utility.c Makefile
NOCRYPT_DIR=${.CURDIR}/Nocrypt

E 19
D 8
LIBS=	-lutil -ltermcap
GETTYOBJ= get_date.o gettytab.o
GETTYSRC= get_date.c gettytab.c
D 6
LIBEXEC= ${DESTDIR}/usr/libexec
E 6
I 6
LIBEXEC=${DESTDIR}/usr/libexec
VPATH=	../getty
E 6

SRC1=	telnetd.c state.c termstat.c slc.c sys_term.c utility.c global.c
OBJ1=	telnetd.o state.o termstat.o slc.o sys_term.o utility.o global.o

OBJS=	${OBJ1} ${GETTYOBJ}
SRCS=	${SRC1} ${GETTYSRC}

E 5
D 6
VPATH=	../getty
E 6
MAN=	telnetd.0
I 5
CFLAGS=	-O ${DEFINES}
I 6

#
# These next three lines are not needed in 4.4BSD
#
#.SUFFIXES: .0 .8
#.8.0:
#	nroff -man -h $< > $@

E 6
E 5
D 2
MAN8=	/usr/man/cat8/
E 2

all: telnetd

telnetd: ${OBJS} ${LIBC}
D 5
	${CC} -o $@ ${CFLAGS} ${OBJS} -lutil
E 5
I 5
	${CC} -o $@ ${CFLAGS} ${OBJS} ${LIBS}
E 5

D 2
cleandir: clean
	rm -f tags .depend

E 2
clean:
D 2
	rm -f ${OBJS} core telnetd ${MAN}
E 2
I 2
	rm -f ${OBJS} core telnetd
E 2

I 2
cleandir: clean
	rm -f ${MAN} tags .depend

E 2
depend: ${SRCS}
	mkdep ${CFLAGS} ${SRCS}

install: ${MAN}
D 3
	install -s -o bin -g bin -m 755 telnetd ${DESTDIR}/etc/telnetd
E 3
I 3
D 4
	install -s -o bin -g bin -m 755 telnetd ${DESTDIR}/usr/libexec/telnetd
E 4
I 4
D 5
	install -s -o bin -g bin -m 755 telnetd ${DESTDIR}/usr/libexec
E 5
I 5
	install -s -o bin -g bin -m 755 telnetd ${LIBEXEC}
E 5
E 4
E 3
D 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}${MAN8}${MAN}
E 2
I 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8
E 2

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 8
I 8
.include <bsd.prog.mk>
I 19

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
E 19
E 8
E 1
