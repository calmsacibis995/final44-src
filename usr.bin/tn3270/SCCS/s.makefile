h57549
s 00000/00017/00294
d D 4.9 91/05/08 13:37:18 bostic 39 38
c makefiles don't need copyrights
e
s 00004/00004/00307
d D 4.8 91/04/25 15:16:43 minshall 38 37
c checked in for Minshall (bostic)
e
s 00006/00005/00305
d D 4.7 90/06/06 09:47:37 borman 37 36
c Fix up makefile so that it will work with new make and
c obj directory.  Had to comment out the .c.obj line because the
c new make doesn't deal with it properly.
e
s 00002/00002/00308
d D 4.6 90/03/01 07:02:34 borman 36 35
c Clean up the makefile so that tn3270 will compile (add -DUSE_TERMIO)
e
s 00024/00001/00286
d D 4.5 89/09/02 14:53:52 minshall 35 34
c Add in new DEFINES to keep up to date with Dave Borman's telnet.
e
s 00001/00001/00286
d D 4.4 89/08/15 18:53:09 bostic 34 33
c reorg
e
s 00002/00001/00285
d D 4.3 89/06/10 11:44:33 minshall 33 32
c Need to use compatibility mode with newer and newer kernels.
e
s 00001/00001/00285
d D 4.2 89/03/06 11:51:32 bostic 32 31
c add cleandir label
e
s 00000/00000/00286
d D 4.1 88/12/04 15:10:51 minshall 31 30
c Release 4.1
e
s 00019/00009/00267
d D 3.6 88/10/30 13:17:31 minshall 30 29
c Correct copyright.  Man page installation.  Lint fix up.  Name change.
e
s 00003/00003/00273
d D 3.5 88/05/15 20:31:15 minshall 29 28
c Recover telnet.ext, which several .c files include.  Use telnet/telprog.o,
e
s 00029/00022/00247
d D 3.4 88/05/15 12:44:38 minshall 28 27
c Various pieces are new for new telnet structure and for lint/tags.
e
s 00013/00001/00256
d D 3.3 88/03/28 13:46:20 bostic 27 26
c add Berkeley specific header
e
s 00003/00011/00254
d D 3.2 87/08/13 11:06:57 minshall 26 25
c 4.3+ install actions.
e
s 00000/00000/00265
d D 3.1 87/08/11 10:16:45 minshall 25 24
c New version numbering.
e
s 00001/00001/00264
d D 1.24 87/07/31 15:53:21 minshall 24 23
c Add "makefile_4.2".
e
s 00007/00009/00258
d D 1.23 87/07/17 10:09:01 minshall 23 22
c New directory structure.
e
s 00002/00002/00265
d D 1.22 87/07/09 10:43:37 minshall 22 21
c 1) Add apilib/apiliblib.a as tn3270 dependancy; 2) Fix PC link
c statement to create tn3270.
e
s 00015/00013/00252
d D 1.21 87/07/03 15:48:28 minshall 21 20
c Add in stuff for PC version.
e
s 00038/00017/00227
d D 1.20 87/07/03 15:37:37 minshall 20 19
c PC mkmake compatibility
e
s 00001/00001/00243
d D 1.19 87/07/03 10:15:08 minshall 19 18
c makefiles.pc
e
s 00042/00006/00202
d D 1.18 87/06/30 23:52:52 minshall 18 17
c mkmake, etc.
e
s 00027/00014/00181
d D 1.17 87/06/30 21:42:44 minshall 17 16
c First version of mkmake.
e
s 00011/00013/00184
d D 1.16 87/06/19 15:03:41 minshall 16 15
c New directories, new cleanup.
e
s 00006/00019/00191
d D 1.15 87/06/19 09:21:14 minshall 15 14
c Get rid of SLOWSCREEN (yeah!).  Make "make clean; make" work.
e
s 00008/00002/00202
d D 1.14 87/06/18 11:57:04 minshall 14 13
c Add in 'arpa' as an extra directory.
e
s 00000/00000/00204
d D 1.13 87/06/15 10:45:05 minshall 13 12
c null
e
s 00003/00003/00201
d D 1.12 87/06/15 10:44:33 minshall 12 11
c sourcelist target.
e
s 00029/00011/00175
d D 1.11 87/06/15 10:02:16 minshall 11 10
c Add ACTION default; add sourcelist target.
e
s 00012/00019/00174
d D 1.10 87/06/15 09:28:26 minshall 10 9
c Don't build tn3270.a (takes a long time, and not needed).
e
s 00003/00004/00190
d D 1.9 87/06/12 15:25:14 minshall 9 8
c We got rid of DEBUG flag (yeah!); link with apilib/apilib.a.
e
s 00003/00003/00191
d D 1.8 87/05/31 17:09:13 minshall 8 7
c Version without termcodes.m4.
e
s 00012/00013/00182
d D 1.7 87/05/22 15:08:40 minshall 7 6
c New directory structure.
e
s 00001/00001/00194
d D 1.6 87/05/15 16:05:28 minshall 6 5
c Don't need libcurses for mset.
e
s 00001/00001/00194
d D 1.5 87/05/11 11:08:05 minshall 5 4
c Change rules for mset
e
s 00006/00000/00189
d D 1.4 87/05/10 14:48:06 minshall 4 3
c ACTION
e
s 00001/00001/00188
d D 1.3 87/04/01 13:57:40 minshall 3 2
c Fix close/open sequences in a rational way.
e
s 00001/00001/00188
d D 1.2 86/12/19 17:05:58 minshall 2 1
c seems to work with 'close' then 'open'.
e
s 00189/00000/00000
d D 1.1 86/11/16 15:23:16 minshall 1 0
c date and time created 86/11/16 15:23:16 by minshall
e
u
U
t
T
I 27
D 39
#
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 30
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 30
I 30
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
E 30
#
E 39
#	%W% (Berkeley) %G%
D 39
#
E 39
I 28

E 28
E 27
I 1
# Makefile for tn3270 and friends...
D 27
# @(#)makefile	3.1  10/29/86
E 27
#
D 28
#	This is the makefile for tn3270.  Note that we use ../telnet.c
E 28
I 28
#	This is the makefile for tn3270.  Note that we use the 4.3+ telnet
E 28
# (compiled with special options; see below) to provide the telnet
# support we need.
#
#	The following are the defines that may be passed (via the cc
# -D option) to the compiler.
#
D 28
#	The first group relate only to ../telnet.c:
#
E 28
#	TN3270		- 	This is to be linked with tn3270.  Necessary
D 28
#				for creating tn3270.
E 28
I 28
#				for creating tn3270.  Only for compiling
#				telnet.
E 28
#
D 9
#	DEBUG		-	Allow for some extra debugging operations.
#
E 9
#	NOT43		-	Allows the program to compile and run on
#				a 4.2BSD system.
#
#	PUTCHAR		-	Within tn3270, on a NOT43 system,
#				allows the use of the 4.3 curses
#				(greater speed updating the screen).
#				You need the 4.3 curses for this to work.
#
#	FD_SETSIZE	-	On whichever system, if this isn't defined,
#				we patch over the FD_SET, etc., macros with
#				some homebrewed ones.
#
#	SO_OOBINLINE	-	This is a socket option which we would like
#				to set to allow TCP urgent data to come
#				to us "inline".  This is NECESSARY for
#				CORRECT operation, and desireable for
#				simpler operation.
#
#	LNOFLSH		-	Detects the presence of the LNOFLSH bit
#				in the tty structure.
#
#
I 35
#
#	TERMCAP		-	Define this if your system is termcap based,
#				otherwise a terminfo based system is assumed.
#
#	SRCRT		-	Includes code to allow you to specify
#				source routes.
#				Format is:
#					[!]@hop1@hop2...[@|:]dst
#				Leading ! means strict source route.
#
#	NOSTRNCASECMP	-	Define this if you do not have strncasecmp() in
#				your C libarary.
#
#	USE_TERMIO	-	Define this if you have System V termio
#				structures.  What is here is how things
#				are on Cray computers.
#
#	KLUDGELINEMODE	-	Define this to get the kludged up version
#				of linemode that was in 4.3BSD.  This is a
#				good thing to have around for talking to
#				older systems.
#
#
E 35
#	Here are some which are used throughout the system:
#
D 15
#	SLOWSCREEN	-	If SLOWSCREEN is defined, we generate code
#				that attempts to optimize the line between
#				the computer (on which tn3270 runs) and the
#				user's terminal (which line may be 1200 baud,
#				or some such) at the cost of CPU time on
#				the above referenced computer.
#
E 15
#	unix		-	Compiles in unix specific stuff.
#
#	msdos		-	Compiles in msdos specific stuff.
#

I 17
# msdos versus unix defines
O	= .o
D 20
PC_O	= .obj
E 20
I 20
#PC_O	= .obj
E 20

X	=
D 20
PC_X	= .exe
E 20
I 20
#PC_X	= .exe
E 20

I 20
L	=
#PC_L	= -link

E 20
E 17
CC	= cc
I 18
D 20
PC_CC	= cl
E 20
I 20
#PC_CC	= cl
E 20

MV	= mv
D 20
PC_MV	= rename
E 20
I 20
#PC_MV	= rename
E 20

RM	= rm -f
D 20
PC_RM= erase
E 20
I 20
#PC_RM= erase
E 20

LINT_ARGS =
D 20
PC_LINT_ARGS = -DLINT_ARGS
E 20
I 20
#PC_LINT_ARGS = -DLINT_ARGS
E 20

DEBUG_FLAGS = -g
D 20
PC_DEBUG_FLAGS = -Zi -Od
E 20
I 20
#PC_DEBUG_FLAGS = -Zi -Od
E 20

AR	= ar
D 20
C	=
PC_AR	= lib
PC_C	= +
E 20
I 20
AR1	= cr
AR2	=
AR3	=
#PC_AR	= lib
#PC_AR1	=
#PC_AR2	= +
#PC_AR3	= ";"
E 20

RANLIB	= ranlib
D 20
PC_RANLIB = echo "Done with "
E 20
I 20
#PC_RANLIB = echo "Done with "
E 20


E 18
PRINT	= print
I 11
D 28
ACTION = sccs tell
E 28
I 28
ACTION = @sccs tell
E 28
E 11

D 15
DEFINES = -DSLOWSCREEN
D 9
DEFINES = -DSLOWSCREEN -DDEBUG
E 9
I 9
DEFINES = -DSLOWSCREEN
E 15
I 15
D 18
DEFINES =
E 18
I 18
D 35
DEFINES = ${LINT_ARGS}
E 35
I 35
D 36
DEFINES= ${LINT_ARGS} -DTERMCAP -DSRCRT -DKLUDGELINEMODE
E 36
I 36
DEFINES= ${LINT_ARGS} -DTERMCAP -DSRCRT -DKLUDGELINEMODE -DUSE_TERMIO
E 36
E 35
E 18
E 15
E 9

D 3
INCLUDES = -I.
E 3
I 3
INCLUDES = -I. -I..
E 3

OPTIMIZE = -O
D 18
OPTIMIZE = -g
E 18
I 18
OPTIMIZE = ${DEBUG_FLAGS}
E 18

CFLAGS	= $(OPTIMIZE) $(INCLUDES) $(DEFINES)

# Lint flags
LINTFLAGS	= -hbxaz
# How to install the bloody thing...

I 11
D 16
DIRPATH=.
E 16
E 11
DESTDIR=

D 34
BINDIR		= $(DESTDIR)/usr/ucb
E 34
I 34
BINDIR		= $(DESTDIR)/usr/bin
E 34
I 30
MAN1DIR		= $(DESTDIR)/usr/man/cat1
MAN5DIR		= $(DESTDIR)/usr/man/cat5
E 30
D 26
ETCDIR		= $(DESTDIR)/etc
MANDIR		= $(DESTDIR)/usr/man/man
E 26

# Names for the terminal libraries...
LIBCURSES	= -lcurses
LIBTERM		= -ltermlib

I 20
#PC_LIBCURSES	=
#PC_LIBTERM	=

E 20
# The source files...
D 7
ALLH =	general.h
E 7
I 7
D 11
ALLH =
E 11
I 11
D 28
ALLH = telnet.ext
E 28
I 28
D 29
ALLH =
E 29
I 29
D 30
ALLH =	telnet.ext
E 30
I 30
ALLH =	telextrn.h
E 30
E 29
E 28
E 11
E 7

D 28
TNMAIN = ../telnet.c
TNMAIN = telnet.c
E 28
D 7
MSMAIN = keyboard/mset.c
E 7
I 7
D 37
MSMAIN = ascii/mset.c
E 37
I 37
MSMAIN = ${.CURDIR}/ascii/mset.c
E 37
E 7

I 11
D 28
ALLC = ${TNMAIN}
E 28
I 28
ALLC =
E 28

D 17
ALLO	= telnet.o mset.o
E 17
I 17
D 28
ALLO	= telnet$O mset$O
E 28
I 28
ALLO	= mset$O
E 28
E 17

D 28
ALLPRINT =	${ALLH} ${ALLC}
E 28
I 28
ALLHC=	${ALLH} ${ALLC}
ALLPRINT =	${ALLHC}
E 28

D 24
ALLSOURCE =	${ALLPRINT} makefile makefile.mak README
E 24
I 24
D 30
ALLSOURCE =	${ALLPRINT} makefile makefile.mak makefile_4.2 README
E 30
I 30
ALLSOURCE =	${ALLPRINT} makefile makefile.mak makefile_4.2 README \
		mset.1 tn3270.1 map3270.5
E 30
E 24

I 18
D 20
SYS	= sys
PC_SYS	= sys_dos
E 20
I 20
SYS	= sys_curses
#PC_SYS	= sys_dos
E 20

E 18
E 11
# The places where the various components live...
D 7
SUBDIR =	ascii ctlr keyboard screen system
SUBLIB =	ascii/asciilib ctlr/ctlrlib keyboard/keyboardlib \
			screen/screenlib system/systemlib
E 7
I 7
D 14
SUBDIR =	ascii ctlr sys general api
E 14
I 14
D 15
# (We put ctlr first so that a 'make clean; make' will work.  If
#	ascii is first, then since the make in ascii does some
#	sub-makes in ctlr, the bsd make utility decides not to
#	bother with doing a full make in ctlr.)
E 15
E 14
D 10
SUBLIB =	ascii/ascii.lib ctlr/ctlr.lib \
			sys/sys.lib general/general.lib api/api.lib
E 10
E 7

I 14
D 15
SUBDIR =	ctlr ascii sys general api
E 15
I 15
D 18
SUBDIR =	api apilib ascii ctlr general sys
E 18
I 18
D 23
SUBDIR =	api apilib ascii ctlr general ${SYS}
E 23
I 23
D 28
SUBDIR =	api ascii ctlr general ${SYS}
E 28
I 28
D 37
SUBDIR =	api ascii ctlr general ${SYS} telnet
E 37
I 37
SUBDIR =	${.CURDIR}/api ${.CURDIR}/ascii ${.CURDIR}/ctlr \
		${.CURDIR}/general ${.CURDIR}/${SYS} ${.CURDIR}/telnet
E 37
E 28
E 23
E 18
E 15

E 14
I 11
# The following are directories we don't do regular make's in, but
# we do make everywhere, print, and sourcelist in.
D 14
EXTRADIR =	apilib sys_dos tools
E 14
I 14

D 15
EXTRADIR =	apilib arpa sys_dos tools
E 15
I 15
D 16
EXTRADIR =	arpa sys_dos tools
E 16
I 16
D 36
EXTRADIR =	arpa sys_dos tools utilities
E 36
I 36
D 37
EXTRADIR =	tools
E 37
I 37
EXTRADIR =	${.CURDIR}/tools
E 37
E 36
E 16
E 15
E 14

E 11
I 10
# The libraries we use.  The order here is important.
D 16
# ctlr.lib and sys.lib should come first, then api.lib
E 16
I 16
D 21
# ctlrlib.a and syslib.a should come first, then apilib.a
E 21
I 21
D 23
# ctlrlib.a and syslib.a should come first, then apiliblib.a
E 21
E 16
# then the rest.
D 16
SUBLIB =	ctlr/ctlr.lib sys/sys.lib \
		api/api.lib \
		ascii/ascii.lib general/general.lib
E 16
I 16
D 18
SUBLIB =	ctlr/ctlrlib.a sys/syslib.a \
E 18
I 18
SUBLIB =	ctlr/ctlrlib.a ${SYS}/syslib.a \
E 18
		api/apilib.a \
E 23
I 23
# syslib.a and ctlrlib.a should come first, then the rest.
SUBLIB =	${SYS}/syslib.a ctlr/ctlrlib.a \
E 23
		ascii/asciilib.a general/generallib.a
E 16
E 10

I 10
D 16

E 16
E 10
D 11
ALLC = ${TNMAIN} ${MSMAIN}

ALLO	= telnet.o mset.o

E 11
.s.o:
	/lib/cpp -E $< | as -o $@

I 18
D 37
.c.obj:
	${CC} ${CFLAGS} -c $<
E 37
I 37
#.c.obj:
#	${CC} ${CFLAGS} -c $<
E 37

E 18
D 10
all:	${SUBDIR} tn3270.a tn3270 mset
E 10
I 10
D 15
all:	${SUBDIR} tn3270 mset
E 15
I 15
D 17
all:	FRC tn3270 mset
E 17
I 17
all:	FRC tn3270$X mset$X
E 17
E 15
E 10

D 10
tn3270.a: ${SUBLIB}
	-mkdir tmp
D 7
	for i in ${SUBDIR}; do (cd tmp; ar x ../$$i/$${i}lib); done
E 7
I 7
	for i in ${SUBDIR}; do (cd tmp; ar x ../$$i/$${i}.lib); done
E 7
	ls tmp/*.o | sort -t/ +1 > t1
	ar cr tn3270.a `lorder \`cat t1\` | tsort`
	rm -f t1 tmp/*
	ranlib tn3270.a
D 7
#	for i in ${SUBDIR}; do (cd tmp; ar x ../$$i/$${i}lib_p); done
E 7
I 7
#	for i in ${SUBDIR}; do (cd tmp; ar x ../$$i/$${i}.lib_p); done
E 7
#	ls tmp/*.o | sort -t/ +1 > t1
#	ar cr tn3270_p.a `lorder \`cat t1\` | tsort`
#	rm -rf t1 tmp

E 10
D 15
${SUBDIR}: FRC
	cd $@; make ${MFLAGS} "CFLAGS=${CFLAGS}"

E 15
FRC:
I 15
	for i in ${SUBDIR}; \
		do (cd $$i; make ${MFLAGS} "CFLAGS=${CFLAGS}"); done
E 15

D 10
tn3270:	telnet.o tn3270.a
D 9
	${CC} ${CFLAGS} -o tn3270 telnet.o tn3270.a $(LIBCURSES) $(LIBTERM)
E 9
I 9
	${CC} ${CFLAGS} -o tn3270 telnet.o tn3270.a apilib/apilib.a \
					$(LIBCURSES) $(LIBTERM)
E 10
I 10
D 17
tn3270:	telnet.o ${SUBLIB}
	${CC} ${CFLAGS} -o tn3270 telnet.o \
E 17
I 17
D 22
tn3270$X:	telnet$O ${SUBLIB}
E 22
I 22
D 23
tn3270$X:	telnet$O ${SUBLIB} apilib/apiliblib.a
E 23
I 23
D 28
tn3270$X:	telnet$O ${SUBLIB} api/apilib.a
E 23
E 22
	${CC} ${CFLAGS} -o tn3270 telnet$O \
E 28
I 28
D 29
tn3270$X:	telnet/telnet ${SUBLIB} api/apilib.a
	${CC} ${CFLAGS} -o tn3270 telnet/telnet \
E 29
I 29
D 38
tn3270$X:	telnet/telprog.o ${SUBLIB} api/apilib.a
E 38
I 38
tn3270$X:	telnet/telprog.o ${SUBLIB} api/libapi.a
E 38
	${CC} ${CFLAGS} -o tn3270 telnet/telprog.o \
E 29
E 28
E 17
D 20
		${SUBLIB} apilib/apilib.a $(LIBCURSES) $(LIBTERM)
E 20
I 20
D 21
		$L ${SUBLIB} apilib/apilib.a $(LIBCURSES) $(LIBTERM)
E 21
I 21
D 23
		$L ${SUBLIB} apilib/apiliblib.a $(LIBCURSES) $(LIBTERM)
E 23
I 23
D 33
		$L ${SUBLIB} api/apilib.a $(LIBCURSES) $(LIBTERM)
E 33
I 33
D 38
		$L ${SUBLIB} api/apilib.a $(LIBCURSES) $(LIBTERM) \
E 38
I 38
		$L ${SUBLIB} api/libapi.a $(LIBCURSES) $(LIBTERM) \
E 38
		-lcompat
E 33
E 23
E 21
E 20
E 10
E 9

I 20
#PC_tn3270$X:
D 21
	link <@<
	telnet
	telnet
	nul
	${SUBLIB} apilib/apilib.a+
	\lib\ublib\ubtcp
	_PC_<
E 21
I 21
#PC_	link <@<
#PC_	telnet
D 22
#PC_	telnet
E 22
I 22
#PC_	tn3270
E 22
#PC_	nul
D 23
#PC_	${SUBLIB} apilib/apiliblib.a+
E 23
I 23
D 38
#PC_	${SUBLIB} api/apilib.a+
E 38
I 38
#PC_	${SUBLIB} api/libapi.a+
E 38
E 23
#PC_	\lib\ublib\ubtcp
#PC_	_PC_<
E 21

D 21

E 21
E 20
D 5
mset:	mset.o tn3270.a
E 5
I 5
D 7
mset:	mset.o keyboard/map3270.o
E 5
D 6
	${CC} ${CFLAGS} -o mset mset.o keyboard/map3270.o $(LIBCURSES)
E 6
I 6
	${CC} ${CFLAGS} -o mset mset.o keyboard/map3270.o
E 7
I 7
D 8
mset:	mset.o ascii/map3270.o
	${CC} ${CFLAGS} -o mset mset.o ascii/map3270.o
E 8
I 8
D 16
mset:	mset.o ascii/map3270.o ascii/astosc.o
	${CC} ${CFLAGS} -o mset mset.o ascii/map3270.o ascii/astosc.o
E 16
I 16
D 17
mset:	mset.o ascii/map3270.o
	${CC} ${CFLAGS} -o mset mset.o ascii/map3270.o apilib/apilib.a
E 17
I 17
mset$X:	mset$O ascii/map3270$O
D 20
	${CC} ${CFLAGS} -o mset mset$O ascii/map3270$O apilib/apilib.a
E 20
I 20
D 21
	${CC} ${CFLAGS} -o mset mset$O ascii/map3270$O $L apilib/apilib.a
E 21
I 21
D 23
	${CC} ${CFLAGS} -o mset mset$O ascii/map3270$O $L apilib/apiliblib.a
E 23
I 23
D 38
	${CC} ${CFLAGS} -o mset mset$O ascii/map3270$O $L api/apilib.a
E 38
I 38
	${CC} ${CFLAGS} -o mset mset$O ascii/map3270$O $L api/libapi.a
E 38
E 23
E 21
E 20
E 17
E 16
E 8
E 7
E 6

D 17
telnet.o:	$(TNMAIN)
E 17
I 17
D 28
telnet$O:	$(TNMAIN)
E 17
	$(CC) $(CFLAGS) -DTN3270 -c $(TNMAIN)

E 28
D 17
mset.o:	$(MSMAIN)
E 17
I 17
mset$O:	$(MSMAIN)
E 17
	$(CC) $(CFLAGS) -c $(MSMAIN)

D 26
install:
	install -s tn3270 $(BINDIR)
	install -s mset $(BINDIR)
	if [ ! -f ${ETCDIR}/map3270 ]; then \
		install -c -m 444 map3270.dat ${ETCDIR}/map3270; \
	fi
#	install -c -m 444 man/tn3270.1 $(MANDIR)1/tn3270.1
#	install -c -m 444 man/mset.1 $(MANDIR)1/mset.1
#	install -c -m 444 man/map3270.5 $(MANDIR)5/map3270.5
E 26
I 26
D 30
install:	tn3270$X mset$X
E 30
I 30
install:	tn3270$X mset$X tn3270.0 mset.0 map3270.0
E 30
	install -m 755 -o bin -g bin -s tn3270 $(BINDIR)
	install -m 755 -o bin -g bin -s mset $(BINDIR)
I 30
	install -c -o bin -g bin -m 444 tn3270.0 mset.0 $(MAN1DIR)
	install -c -o bin -g bin -m 444 map3270.0 $(MAN5DIR)
E 30
E 26

I 4
action:
	${ACTION}

I 28
clist:	${ALLHC}
	@for i in ${SUBDIR}; \
		do (cd $$i; make ${MFLAGS} "DIRPATH=${DIRPATH}$$i/" \
							    clist); done

hclist:	${ALLHC}
	@for i in ${SUBDIR}; \
		do (cd $$i; make ${MFLAGS} "DIRPATH=${DIRPATH}$$i/" \
							    hclist); done

E 28
D 11
everywhere:
	for i in ${SUBDIR} tools; do (echo "[$$i]"; cd $$i; make ${MFLAGS} action "ACTION=${ACTION}"); done
E 11
I 11
everywhere:	action
	for i in ${SUBDIR} ${EXTRADIR}; \
		do (echo "[$$i]"; cd $$i; make ${MFLAGS} action \
						"ACTION=${ACTION}"); done
E 11

E 4
D 32
clean:
E 32
I 32
cleandir clean:
E 32
D 10
	rm -f $(ALLO) mset tn3270 errs makefile.bak tn3270.a
E 10
I 10
D 18
	rm -f $(ALLO) mset tn3270 errs makefile.bak
E 18
I 18
	for i in $(ALLO) mset tn3270 errs makefile.bak; \
			do (${RM} $$i); done
	for i in ${SUBDIR} ${EXTRADIR}; \
			do (cd $$i; make ${MFLAGS} clean); done

sccsclean:
E 18
I 16
	-sccs clean
	-sccs get makefile
E 16
E 10
D 2
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} clean); done
E 2
I 2
D 11
	for i in ${SUBDIR} tools; do (cd $$i; make ${MFLAGS} clean); done
E 11
I 11
D 18
	for i in ${SUBDIR} ${EXTRADIR}; do (cd $$i; make ${MFLAGS} clean); done
E 18
I 18
	for i in ${SUBDIR} ${EXTRADIR}; \
			do (cd $$i; make ${MFLAGS} sccsclean); done
E 18
E 11
E 2
D 16
	rm -f t1 tmp/*.o
	-rmdir tmp
E 16

print:
D 11
	${PRINT} ${ALLH} ${MSMAIN} ${TNMAIN}
	for i in ${SUBDIR}; \
E 11
I 11
	${PRINT} ${ALLPRINT}
	for i in ${SUBDIR} ${EXTRADIR}; \
E 11
			do (cd $$i; make ${MFLAGS} "PRINT=${PRINT}" print); done
D 11
	cd tools; make ${MFLAGS} "PRINT=${PRINT}" print
E 11

tags:	${ALLC} ${ALLH}
D 28
	ctags -t ${ALLC} ${ALLH}
E 28
I 28
	ctags -t `make ${MFLAGS} hclist`
E 28
I 11

D 12
sourcelist:
	for i in ${ALLSOURCE}; \
E 12
I 12
sourcelist:	${ALLSOURCE}
	@for i in ${ALLSOURCE}; \
E 12
D 16
		do (echo ${DIRPATH}/$$i); done
E 16
I 16
		do (echo ${DIRPATH}$$i); done
E 16
D 12
	for i in ${SUBDIR} ${EXTRADIR}; \
E 12
I 12
	@for i in ${SUBDIR} ${EXTRADIR}; \
E 12
D 16
		do (cd $$i; make ${MFLAGS} "DIRPATH=${DIRPATH}/$$i" \
E 16
I 16
		do (cd $$i; make ${MFLAGS} "DIRPATH=${DIRPATH}$$i/" \
E 16
							    sourcelist); done
E 11

lint:
D 30
	lint ${LINTFLAGS} ${INCLUDES} ${DEFINES} -DTN3270 \
E 30
I 30
	lint ${LINTFLAGS} -Itelnet ${INCLUDES} ${DEFINES} -DTN3270 \
E 30
D 28
				${TNMAIN} -lcurses
	lint ${LINTFLAGS} ${INCLUDES} ${DEFINES} ${MSMAIN} map3270.c -lcurses
E 28
I 28
				`make clist` -lcurses
E 28

I 28
lintmset:
	lint ${LINTFLAGS} ${INCLUDES} ${DEFINES} ${MSMAIN} \
				ascii/map3270.c -lcurses

E 28
I 17
D 19
makefile.mak:	makefile
E 19
I 19
D 21
makefiles.pc:
E 21
I 21
makefiles.pc:	tools/mkmake
E 21
E 19
	for i in . ${SUBDIR} ${EXTRADIR}; \
D 20
	do (sed -e "s/lib\.a/.lib/g" -e "s/^PC_//" < $$i/makefile | \
			    mkmake | sed -e "sx/x\\\\x" > $$i/makefile.mak); \
E 20
I 20
	do (sed -e "s/lib\.a/.lib/g" -e "s/^#PC_//" < $$i/makefile | \
D 21
		mkmake | \
E 21
I 21
		./tools/mkmake | \
E 21
		sed -e "sx/x\\\\xg" -e "s/[ 	]*_PC_//" > $$i/makefile.mak); \
E 20
	    done
I 21

tools/mkmake:
	(cd tools; make mkmake)
E 21

E 17
.DEFAULT:
	sccs get $<

depend:	thisdepend
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} depend); done

thisdepend:
D 17
	grep '^#include' ${ALLC} | grep -v '<' | \
E 17
I 17
	echo > eddep.c
	grep '^#include' ${ALLC} eddep.c | grep -v '<' | \
E 17
	sed -e 's/:[^"]*"\([^"]*\)".*/: \1/' \
D 17
	    -e 's/\.c/.o/' | \
E 17
I 17
	    -e 's/\.c/$$O/' | \
E 17
	awk ' { if ($$1 != prev) { print rec; rec = $$0; prev = $$1; } \
		else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
		       else rec = rec " " $$2 } } \
	      END { print rec } ' > makedep
	echo '$$r makedep' >>eddep
	echo '/^# DO NOT DELETE THIS LINE/+1,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
I 18
	-rm -f makefile.bak
E 18
	cp makefile makefile.bak
	ed - makefile < eddep
D 17
	rm eddep makedep
E 17
I 17
	rm eddep makedep eddep.c
E 17

# DO NOT DELETE THIS LINE

D 7
telnet.o: ctlr/screen.h system/globals.h telnet.ext ctlr/options.ext
telnet.o: ctlr/outbound.ext keyboard/termin.ext
keyboard/mset.o: keyboard/state.h keyboard/m4.out ../system/globals.h
keyboard/mset.o: keyboard/map3270.ext
E 7
I 7
D 17
telnet.o: ctlr/screen.h general/globals.h telnet.ext ctlr/options.ext
telnet.o: ctlr/outbound.ext ascii/termin.ext general/general.h
D 8
ascii/mset.o: state.h m4.out ../general/globals.h map3270.ext
E 8
I 8
ascii/mset.o: state.h ../general/globals.h map3270.ext
E 17
I 17
D 28
telnet$O: ascii/termin.ext ctlr/screen.h ctlr/oia.h ctlr/options.ext
telnet$O: ctlr/outbound.ext general/globals.h telnet.ext general/general.h
E 28
E 17
E 8
E 7
E 1
