h44365
s 00000/00000/00016
d D 8.1 93/06/19 13:46:32 bostic 39 38
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00015
d D 5.9 93/06/19 13:46:16 bostic 38 36
c do dependency on kerberosIV for build
e
s 00000/00000/00016
d R 8.1 93/06/12 14:42:07 bostic 37 36
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00003/00013
d D 5.8 93/06/12 14:41:51 bostic 36 34
c fix build target for 4.4BSD
e
s 00000/00000/00016
d R 8.1 93/06/09 23:10:46 bostic 35 34
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00000/00009
d D 5.7 93/05/31 13:44:24 bostic 34 33
c add a make build to build the system from scratch
e
s 00002/00002/00007
d D 5.6 93/05/31 13:18:25 bostic 33 32
c install include, too
e
s 00002/00002/00007
d D 5.5 93/05/31 13:16:19 bostic 32 31
c 4.4BSD snapshot, add contrib back in
e
s 00003/00000/00006
d D 5.4 92/07/18 15:56:29 bostic 31 30
c do the man pages after an install
e
s 00001/00028/00005
d D 5.3 92/07/15 15:00:21 bostic 30 29
c delete build target, hasn't worked in a long while
e
s 00000/00000/00033
d D 5.2 92/03/01 14:23:40 bostic 29 26
c checkpoint
e
s 00002/00001/00004
d D 5.1.1.2 91/05/09 16:40:52 bostic 28 27
c add Kerberos to the 2nd network distribution
e
s 00001/00029/00004
d D 5.1.1.1 91/05/08 17:25:12 bostic 27 26
c branch for the 2nd network distribution
e
s 00002/00006/00031
d D 5.1 91/05/06 18:28:29 bostic 26 25
c checkpoint
e
s 00000/00010/00037
d D 4.23 90/12/14 11:53:58 bostic 25 24
c shouldn't need shadow any more, obj should do it all
e
s 00003/00002/00044
d D 4.22 90/06/30 22:36:09 bostic 24 23
c add contrib
e
s 00022/00031/00024
d D 4.21 90/06/25 11:07:59 bostic 23 22
c checkpoint for June tape -- this isn't ready yet...
e
s 00039/00149/00016
d D 4.20 90/06/08 12:41:39 bostic 22 21
c checkpoint, to save obj creation
e
s 00089/00089/00076
d D 4.19 90/03/23 07:35:51 bostic 21 20
c checkpoint before pmake
e
s 00015/00004/00150
d D 4.18 88/06/30 18:11:49 bostic 20 19
c add Berkeley copyright
e
s 00036/00016/00118
d D 4.17 88/05/31 16:09:02 karels 19 18
c I liked the old order better; add verbosity so I can find out
c where we are; add src target to restart build/whatever; separate clean
c and depend from build
e
s 00028/00022/00106
d D 4.16 87/12/05 16:02:19 bostic 18 16
c tahoe beta update
e
s 00029/00020/00108
d R 4.16 87/07/27 16:17:50 bostic 17 16
c various changes
e
s 00002/00001/00126
d D 4.15 87/05/13 09:44:20 bostic 16 15
c add MACHINE def 
e
s 00028/00015/00099
d D 4.14 87/03/29 17:26:41 bostic 15 14
c added new way to make
e
s 00001/00001/00113
d D 4.13 86/05/15 08:44:31 lepreau 14 13
c add "old" (it's just a skeleton down there)
e
s 00001/00001/00113
d D 4.12 86/03/17 11:35:27 karels 13 12
c missing \ 
e
s 00082/00013/00032
d D 4.11 86/03/15 17:32:11 karels 12 11
c add make build, libc flags
e
s 00004/00004/00041
d D 4.10 86/01/22 18:15:05 mckusick 11 10
c fix install entry
e
s 00002/00000/00043
d D 4.9 86/01/11 16:02:09 mckusick 10 9
c do not forget to install /usr/include
e
s 00005/00001/00038
d D 4.8 86/01/11 13:30:18 mckusick 9 7
c add installsrc
e
s 00004/00000/00039
d R 4.8 86/01/11 13:05:46 mckusick 8 7
c add installsrc
e
s 00013/00003/00026
d D 4.7 86/01/11 13:04:01 mckusick 7 6
c add build entry
e
s 00001/00001/00028
d D 4.6 85/06/06 12:23:33 kre 6 5
c added '-' before for look in make install, so it won't stop.
e
s 00006/00000/00023
d D 4.5 85/05/30 23:20:12 sam 5 4
c add tags
e
s 00001/00001/00022
d D 4.4 84/07/06 19:08:54 karels 4 3
c add new
e
s 00003/00001/00020
d D 4.3 83/08/20 12:24:33 sam 3 2
c another try at insuring subdirectories are always remade
e
s 00001/00001/00020
d D 4.2 82/10/25 01:18:37 mckusick 2 1
c sensible reordering
e
s 00021/00000/00000
d D 4.1 82/10/22 18:26:18 mckusick 1 0
c date and time created 82/10/22 18:26:18 by mckusick
e
u
U
f b 
t
T
I 12
D 22
#
D 20
# Copyright (c) 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 20
I 20
# Copyright (c) 1986, 1988 Regents of the University of California.
# All rights reserved.
E 20
#
E 12
I 1
D 20
#	%W%	(Berkeley)	%G%
E 20
I 20
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
E 22
#	%W% (Berkeley) %G%
E 20
D 22
#
I 12
D 15
# This makefile is designed to be run as:
E 15
I 15
D 21
# This makefile is designed to be run in one of three ways:
E 21
I 21
# This makefile is designed to be run in one of two ways:
E 21
#
I 19
D 21
#	make clean
#	make depend
E 21
E 19
E 15
#	make build
#	make installsrc
I 19
D 21
# This is the most rigorous way to rebuild the source tree.
# The first two steps will clean the source tree and remake the dependencies.
E 19
D 15
# The `make build' will compile and install the libraries
# before building the rest of the sources. The `make installsrc'
# will then install the remaining binaries.
# 
# It can also be run in the more conventional way:
#	make
E 15
I 15
# The `make build' will compile and install the libraries and the compiler
# twice before building the rest of the sources.  The `make installsrc' will
D 18
# then install the remaining binaries.
E 18
I 18
D 19
# then install the remaining binaries.  Only `make build' will clean out
# the source tree as well as remake the dependencies.
E 19
I 19
# then install the remaining binaries.
E 21
I 21
# This is the most rigorous way to rebuild the source tree.  `make build'
# will clean the source tree, install the include files, remake the
# dependencies, and then compile and install the libraries and the compiler
# twice before building the rest of the sources.  The `make installsrc'
# will then install the remaining binaries.
E 21
E 19
E 18
#
D 21
#	make libthenall
#	make installsrc
# The `make libthenall' will compile and install the libraries, compile
# and install the compiler and then compile everything else.  Note,
# however, that the libraries will have been built with the old compiler.
# The `make installsrc' will then install the remaining binaries.
#
E 21
#	make all
E 15
#	make install
D 15
# The `make' will compile everything without installing anything.
# The `make install' will then install everything. Note however
# that all the binaries will have been loaded with the old libraries.
E 15
I 15
# The `make all' (the default) will compile everything, and install
# nothing.  The `make install' will then install everything.
E 15
#
# C library options: passed to libc makefile.
D 21
# See lib/libc/Makefile for explanation.
E 21
I 21
# See usr.lib/libc/Makefile for explanation.
E 21
I 18
#
E 18
# HOSTLOOKUP must be either named or hosttable.
# DFLMON must be either mon.o or gmon.o.
# DEFS may include -DLIBC_SCCS, -DSYSLIBC_SCCS, both, or neither.
#
D 18
HOSTLOOKUP=named
DFLMON=mon.o
DEFS= -DLIBC_SCCS
D 16
LIBCDEFS= HOSTLOOKUP=${HOSTLOOKUP} DFLMON=${DFLMON} DEFS="${DEFS}"
E 16
I 16
MACHINE=tahoe
LIBCDEFS= MACHINE=${MACHINE} HOSTLOOKUP=${HOSTLOOKUP} DFLMON=${DFLMON} DEFS="${DEFS}"
E 18
I 18
DEFS=		-DLIBC_SCCS
DFLMON=		mon.o
D 21
HOSTLOOKUP=	named
LIBCDEFS=	HOSTLOOKUP=${HOSTLOOKUP} DFLMON=${DFLMON} DEFS="${DEFS}"
E 21
I 21
LIBCDEFS=	DFLMON=${DFLMON} DEFS="${DEFS}"
E 22
E 21
E 18
E 16

D 22
# global flags
# SRC_MFLAGS are used on makes in command source directories,
# but not in library or compiler directories that will be installed
# for use in compiling everything else.
#
E 12
DESTDIR=
D 18
CFLAGS=	-O
I 12
SRC_MFLAGS = -k
E 18
I 18
CFLAGS=		-O
SRC_MFLAGS=	-k
E 22
I 22
D 23
# skip old
SUBDIR=	bin games include lib libexec old pgrm sbin share usr.bin usr.sbin
E 23
I 23
D 24
SUBDIR=	bin games include kerberosIV lib libexec old pgrm sbin share \
	usr.bin usr.sbin
E 24
I 24
D 26
SUBDIR=	bin contrib games include kerberosIV lib libexec old pgrm sbin \
	share usr.bin usr.sbin
E 26
I 26
D 27
D 30
# contrib
E 30
I 30
D 32
# BROKEN: contrib
E 30
SUBDIR=	bin games kerberosIV lib libexec old sbin share usr.bin usr.sbin
E 32
I 32
D 33
SUBDIR=	bin contrib games kerberosIV lib libexec old sbin share \
	usr.bin usr.sbin
E 33
I 33
SUBDIR=	bin contrib games include kerberosIV lib libexec old sbin \
	share usr.bin usr.sbin
E 33
E 32
E 26
E 24
E 23
E 22
E 18
E 12
D 30

D 18
# Programs that live in subdirectories, and have makefiles of their own.
#
D 2
SUBDIR=	bin etc games lib ucb usr.bin usr.lib local
E 2
I 2
D 4
SUBDIR=	lib usr.lib bin usr.bin etc ucb games local
E 4
I 4
D 7
SUBDIR=	lib usr.lib bin usr.bin etc ucb new games local
E 7
I 7
LIBDIR= lib usr.lib
D 14
SRCDIR=	bin usr.bin etc ucb new games local
E 14
I 14
SRCDIR=	bin usr.bin etc ucb new games local old
E 18
I 18
D 21
LIBDIR=	lib usr.lib
# order is important, old and man must be #1 and #2
D 19
SRCDIR=	old man bin etc games local new ucb usr.bin
E 19
I 19
SRCDIR=	old man bin usr.bin etc ucb new games local
E 21
I 21
D 22
SRCLIB=	lib
# order is important, old must be first, man must be last; contrib is
# too big for the current file system
# bin
SRC=	old games libexec pgrm sbin share usr.bin usr.sbin local man
ALL=	${SRCLIB} ${SRC}
E 22
I 22
build:
	${MAKE} cleandir
E 22
E 21
E 19
E 18
E 14
E 7
E 4
E 2

D 7
all:	${SUBDIR}
E 7
I 7
D 15
all:	${LIBDIR} ${SRCDIR}
E 15
I 15
D 21
all: ${LIBDIR} ${SRCDIR}
E 21
I 21
D 22
all: ${ALL}
E 21
E 15
E 7

I 15
D 19
libthenall: buildlib1 buildlib3 ${SRCDIR}
E 19
I 19
D 21
libthenall: buildlib1 buildlib3 src
E 21
I 21
build: cleandir build1 ${SRC}
E 21
E 19

D 18
build: buildlib1 buildlib2 buildlib3 ${SRCDIR}
E 18
I 18
D 19
build: clean depend buildlib1 buildlib2 buildlib3 ${SRCDIR}
E 19
I 19
D 21
build: buildlib1 buildlib2 buildlib3 src
E 21
I 21
${ALL}: FRC
	@echo; echo +++ compiling $@
	cd $@; make ${MFLAGS}
E 21
E 19
E 18

I 19
D 21
src: ${SRCDIR}

E 19
E 15
D 3
${SUBDIR}: /tmp
E 3
I 3
D 7
${SUBDIR}: FRC
E 7
I 7
D 12
${LIBDIR} ${SRCDIR}: FRC
E 7
E 3
	cd $@; make ${MFLAGS}
E 12
I 12
D 18
lib:	FRC
E 18
I 18
lib: FRC
E 18
	cd lib/libc; make ${MFLAGS} ${LIBCDEFS}
	cd lib; make ${MFLAGS} pcc cpp c2
E 12
I 7

D 12
build: FRC
E 12
I 12
usr.lib ${SRCDIR}: FRC
I 19
	@echo
	@echo === compiling $@
E 19
	cd $@; make ${MFLAGS} ${SRC_MFLAGS}

D 15
build: buildlib ${SRCDIR}

buildlib: FRC
E 15
I 15
buildlib1: FRC
E 15
E 12
I 10
D 11
	echo installing /usr/include
E 11
I 11
D 19
	@echo installing /usr/include
E 19
I 19
	@echo === installing /usr/include
E 21
I 21
build1:
E 22
D 23
	@echo +++ installing includes
E 23
I 23
	@echo "+++ includes"
E 23
E 21
E 19
E 11
D 12
	cd include; make ${MFLAGS} install
E 10
	cd lib; make ${MFLAGS}
D 11
	echo installing /lib
E 11
I 11
	@echo installing /lib
E 11
	cd lib; make ${MFLAGS} install
	cd usr.lib; make ${MFLAGS}
E 12
I 12
D 22
	cd include; make ${MFLAGS} DESTDIR=${DESTDIR} install
	@echo
D 19
	@echo compiling libc.a
E 19
I 19
D 21
	@echo === compiling libc.a
E 19
	cd lib/libc; make ${MFLAGS} ${LIBCDEFS}
D 19
	@echo installing /lib/libc.a
E 19
I 19
	@echo === installing /lib/libc.a
E 19
	cd lib/libc; make ${MFLAGS} DESTDIR=${DESTDIR} install
E 21
I 21
	@echo +++ building dependencies
	@for i in ${ALL}; do \
		echo; echo +++ dependencies for $$i; \
		(cd $$i; make ${MFLAGS} depend); \
	done
	@echo +++ compiling C compiler
	cd usr.bin/cpp; make ${MFLAGS}
	cd usr.libexec/c2; make ${MFLAGS}
	cd usr.libexec/pcc; make ${MFLAGS}
E 21
	@echo
E 22
I 22
	cd include; ${MAKE} depend all install clean

E 22
D 19
	@echo compiling C compiler
E 19
I 19
D 21
	@echo === compiling C compiler
E 19
	cd lib; make ${MFLAGS} pcc cpp c2
E 21
I 21
D 23
	@echo +++ installing C compiler
E 23
I 23
.if ${MACHINE} == "vax" || ${MACHINE} == "tahoe"
	@echo "+++ C preprocessor, compiler, loader"
E 23
D 22
	cd usr.bin/cpp; make ${MFLAGS} install
	cd usr.libexec/c2; make ${MFLAGS} install
	cd usr.libexec/pcc; make ${MFLAGS} install
E 21
D 19
	@echo installing C compiler
E 19
I 19
	@echo
D 21
	@echo === installing C compiler
E 19
	cd lib/pcc; make ${MFLAGS} DESTDIR=${DESTDIR} install
	cd lib/cpp; make ${MFLAGS} DESTDIR=${DESTDIR} install
	cd lib/c2; make ${MFLAGS} DESTDIR=${DESTDIR} install
E 21
I 21
	@echo +++ compiling C library
	cd usr.lib/libc; make ${MFLAGS} ${LIBCDEFS}
E 21
D 15
	cd lib; make ${MFLAGS} clean
E 15
	@echo
E 22
I 22
	cd pgrm/cpp; ${MAKE} depend all install clean
D 23
	cd libexec/c2.${MACHINE}; ${MAKE} depend all install clean
E 23
	cd libexec/pcc; ${MAKE} depend all install clean
I 23
	cd pgrm/ld; ${MAKE} depend all install clean
E 23

E 22
I 15
D 21

buildlib2: FRC
I 19
	@echo === cleaning lib
E 19
	cd lib; make ${MFLAGS} clean
E 15
D 19
	@echo re-compiling libc.a
E 19
I 19
	@echo === re-compiling libc.a
E 19
	cd lib/libc; make ${MFLAGS} ${LIBCDEFS}
D 19
	@echo re-installing /lib/libc.a
E 19
I 19
	@echo === re-installing /lib/libc.a
E 19
	cd lib/libc; make ${MFLAGS} DESTDIR=${DESTDIR} install
E 21
I 21
D 23
	@echo +++ installing C library
E 23
I 23
	@echo "+++ C library"
E 23
D 22
	cd usr.lib/libc; make ${MFLAGS} DESTDIR=${DESTDIR} install
E 21
	@echo
D 19
	@echo re-compiling C compiler
E 19
I 19
D 21
	@echo === re-compiling C compiler
E 19
	cd lib; make ${MFLAGS} pcc cpp c2
D 19
	@echo re-installing C compiler
E 19
I 19
	@echo === re-installing C compiler
E 19
	cd lib/pcc; make ${MFLAGS} DESTDIR=${DESTDIR} install
	cd lib/cpp; make ${MFLAGS} DESTDIR=${DESTDIR} install
	cd lib/c2; make ${MFLAGS} DESTDIR=${DESTDIR} install
E 21
I 21
	@echo +++ cleaning C compiler
	cd usr.bin/cpp; make ${MFLAGS} clean
	cd usr.libexec/c2; make ${MFLAGS} clean
	cd usr.libexec/pcc; make ${MFLAGS} clean
E 21
	@echo
I 15
D 21

buildlib3: FRC
E 15
D 19
	@echo compiling usr.lib
E 19
I 19
	@echo === compiling usr.lib
E 19
	cd usr.lib; make ${MFLAGS} ${SRC_MFLAGS}
E 12
D 11
	echo installing /usr/lib
E 11
I 11
D 19
	@echo installing /usr/lib
E 19
I 19
	@echo === installing /usr/lib
E 19
E 11
D 12
	cd usr.lib; make ${MFLAGS} install
	-for i in ${SRCDIR}; do (cd $$i; make ${MFLAGS}); done
E 12
I 12
	cd usr.lib; make ${MFLAGS} ${SRC_MFLAGS} DESTDIR=${DESTDIR} install
I 19
	@echo === done with libraries
E 21
I 21
	@echo +++ re-compiling C compiler
	cd usr.bin/cpp; make ${MFLAGS}
	cd usr.libexec/c2; make ${MFLAGS}
	cd usr.libexec/pcc; make ${MFLAGS}
E 21
E 19
I 15
	@echo
E 22
I 22
	cd lib/libc; ${MAKE} depend all install clean

E 22
I 21
D 23
	@echo +++ re-installing C compiler
D 22
	cd usr.bin/cpp; make ${MFLAGS} install
	cd usr.libexec/c2; make ${MFLAGS} install
	cd usr.libexec/pcc; make ${MFLAGS} install
	@echo
	@echo +++ cleaning C library
	cd usr.lib/libc; make ${MFLAGS} clean
	@echo
	@echo +++ compiling all libraries
	cd usr.lib; make ${MFLAGS} ${LIBCDEFS}
	@echo
E 22
I 22
	cd pgrm/cpp; ${MAKE} all install all
	cd libexec/c2.${MACHINE}; ${MAKE} all install all
	cd libexec/pcc; ${MAKE} all install all
E 23
I 23
	@echo "+++ C preprocessor, compiler, loader (second time)"
	cd pgrm/cpp; ${MAKE} all install
	cd libexec/pcc; ${MAKE} all install
	cd pgrm/ld; ${MAKE} all install
.endif
E 23

E 22
D 23
	@echo +++ installing all libraries
E 23
I 23
	@echo "+++ libraries"
E 23
D 22
	cd usr.lib; make ${MFLAGS} DESTDIR=${DESTDIR} install
	@echo
	@echo +++ libraries done
	@echo
E 22
I 22
	cd lib; ${MAKE} depend all install all
I 23
	cd kerberosIV; ${MAKE} depend all install all
D 26

	@echo "+++ C library tags"
E 23
	cd lib/libc; rm -f tags; ${MAKE} tags; \
	    install -c -o ${BINOWN} -g ${BINGRP} -m 444 tags /usr/libdata/tags
E 26
E 22
E 21
E 15
E 12
E 7
I 3

D 18
FRC:
E 3

install:
E 18
I 18
D 21
install: FRC
E 18
D 6
	for i in ${SUBDIR}; do \
E 6
I 6
D 11
	-for i in ${SUBDIR}; do \
E 11
I 11
	-for i in ${LIBDIR} ${SRCDIR}; do \
E 21
I 21
D 22
installsrc: FRC
	@for i in ${SRC}; do \
E 21
I 19
		echo; \
D 21
		echo === installing $$i; \
E 21
I 21
		echo +++ installing $$i; \
E 21
E 19
E 11
E 6
D 12
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); done
E 12
I 12
D 13
		(cd $$i; 
E 13
I 13
		(cd $$i; \
E 13
D 21
		make ${MFLAGS} ${SRC_MFLAGS} DESTDIR=${DESTDIR} install); \
E 21
I 21
		    make ${MFLAGS} ${SRC_MFLAGS} DESTDIR=${DESTDIR} install); \
E 21
	done
E 22
I 22
D 23
	@echo +++ installing C library tags file
E 23
I 23
	${MAKE} depend all
E 30
E 27
I 27
D 28
SUBDIR=	bin contrib games include lib libexec sbin share usr.bin usr.sbin
E 28
I 28
SUBDIR=	bin contrib games include kerberosIV lib libexec sbin share \
	usr.bin usr.sbin
E 28
E 27
E 23
E 22
E 12

I 31
afterinstall:
	(cd share/man && make makedb)

I 34
build:
	(cd include && make install)
D 36
	make cleandir && make depend
	(cd lib && make && make install)
E 36
I 36
	make cleandir
	(cd lib && make depend && make && make install)
E 36
D 38
	(cd kerberosIV && make && make install)
E 38
I 38
	(cd kerberosIV && make depend  && make && make install)
E 38
D 36
	make && make install
E 36
I 36
	make depend && make && make install
E 36
	
E 34
E 31
I 9
D 18
installsrc:
E 18
I 18
D 21
installsrc: FRC
E 18
	-for i in ${SRCDIR}; do \
E 21
I 21
D 22
clean: FRC
	@for i in ${ALL}; do \
E 21
I 19
		echo; \
D 21
		echo === installing $$i; \
E 19
D 12
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); done
E 12
I 12
		(cd $$i; \
		make ${MFLAGS} ${SRC_MFLAGS} DESTDIR=${DESTDIR} install); \
E 21
I 21
		echo +++ cleaning $$i; \
		(cd $$i; make ${SRC_MFLAGS} clean); \
E 21
	done
E 22
I 22
D 23
	@echo +++ libraries done
	${MAKE}
E 22
E 12

E 23
I 21
D 22
cleandir: FRC
	@for i in include ${ALL}; do \
		echo; echo '+++ cleaning (cleandir)' $$i; \
		(cd $$i; make ${SRC_MFLAGS} cleandir); \
E 22
I 22
D 25
OBJ=	/usr/obj
D 23
objlinks:
	-for file in `find ${SUBDIR:S/^/-f /g} name SCCS prune or type dir print`; do \
		if [ -s $$file/Makefile -a ! -d ${OBJ}/$$file ] ; then \
			rm -rf ${OBJ}/$$file; \
			mkdir -p ${OBJ}/$$file > /dev/null 2>&1 ; \
			rm -f $$file/obj; \
			ln -s ${OBJ}/$$file $$file/obj; \
		fi; \
E 22
	done

E 23
E 21
E 9
I 5
D 18
tags:
E 18
I 18
D 22
depend: FRC
D 21
	for i in ${LIBDIR} ${SRCDIR}; do \
E 21
I 21
	@for i in ${ALL}; do \
E 21
I 19
		echo; \
D 21
		echo === doing dependencies for $$i; \
E 19
		(cd $$i; make ${MFLAGS} depend); \
E 21
I 21
		echo +++ doing dependencies for $$i; \
		(cd $$i; make ${SRC_MFLAGS} depend); \
E 22
I 22
shadow:
D 23
	-for file in `find ${SUBDIR:S/^/-f /g} name SCCS prune or type dir print`; do \
		if [ -s $$file/obj ] ; then \
			rm -rf ${OBJ}/$$file; \
			mkdir -p ${OBJ}/$$file > /dev/null 2>&1 ; \
		fi; \
E 23
I 23
	@-for file in \
	    `find ${SUBDIR:S/^/-f /g} name SCCS prune or name obj print`; do \
		d=`dirname $$file`; \
		echo ${OBJ}/$$d; \
		mkdir -p ${OBJ}/$$d > /dev/null 2>&1 ; \
I 24
		chown bin.bin ${OBJ}/$$d; \
E 24
E 23
E 22
E 21
	done

E 25
D 21
tags: FRC
E 18
	for i in include lib usr.lib; do \
E 21
I 21
D 22
install: FRC
	@for i in ${ALL}; do \
E 21
I 19
		echo; \
D 21
		echo === making tags for $$i; \
E 19
		(cd $$i; make ${MFLAGS} TAGSFILE=../tags tags); \
E 21
I 21
		echo +++ installing $$i; \
		(cd $$i; \
		    make ${MFLAGS} ${SRC_MFLAGS} DESTDIR=${DESTDIR} install); \
E 21
	done
D 21
	sort -u +0 -1 -o tags tags
E 21

E 5
D 18
clean:
	rm -f a.out core *.s *.o
D 9
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} clean); done
E 9
I 9
D 12
	for i in ${LIBDIR} ${SRCDIR}; do (cd $$i; make ${MFLAGS} clean); done
E 12
I 12
	for i in ${LIBDIR} ${SRCDIR}; do (cd $$i; make -k ${MFLAGS} clean); done
E 18
I 18
D 21
clean: FRC
	for i in ${LIBDIR} ${SRCDIR}; do \
E 21
I 21
tags: FRC
	@for i in include lib usr.lib; do \
E 21
I 19
		echo; \
D 21
		echo === cleaning $$i; \
E 19
		(cd $$i; make -k ${MFLAGS} clean); \
E 21
I 21
		echo +++ making tags for $$i; \
		(cd $$i; make ${SRC_MFLAGS} TAGSFILE=../tags tags); \
E 21
	done
I 21
	sort -u +0 -1 -o tags tags
E 21

FRC:
E 22
I 22
D 23
.include <bsd.own.mk>
E 23
.include <bsd.subdir.mk>
E 22
E 18
E 12
E 9
E 1
