h27747
s 00000/00000/00058
d D 8.1 93/06/04 16:30:27 bostic 17 16
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00000/00054
d D 5.16 93/01/12 10:32:06 bostic 16 15
c add cuserid
e
s 00002/00001/00052
d D 5.15 93/01/12 10:29:09 bostic 15 14
c add 4.3/cfree
e
s 00001/00001/00052
d D 5.14 93/01/03 14:47:17 ralph 14 13
c somehow I lost a '.'. Just fixing it.
e
s 00002/00000/00051
d D 5.13 92/12/24 09:27:20 ralph 13 12
c added mips files
e
s 00011/00003/00040
d D 5.12 92/12/17 16:21:16 bostic 12 11
c remove ruserpass.c; it had some broken DES from BerkNET in it.
e
s 00002/00002/00041
d D 5.11 92/08/05 12:13:19 bostic 11 10
c regex man page need by POSIX regex package
e
s 00001/00001/00042
d D 5.10 92/06/04 15:13:07 mckusick 10 9
c add support for luna68k from Omron
e
s 00002/00000/00041
d D 5.9 91/07/30 18:31:31 torek 9 8
c sparc
e
s 00004/00002/00037
d D 5.8 91/03/06 15:55:39 bostic 8 7
c move regex from libc to libcompat
e
s 00010/00005/00029
d D 5.7 91/03/06 15:52:33 bostic 7 6
c add insque, remque
e
s 00001/00001/00033
d D 5.6 91/01/15 18:11:34 bostic 6 5
c forgot the man pages...
e
s 00001/00001/00033
d D 5.5 90/08/27 17:29:25 bostic 5 4
c move utime and times back into the C library, POSIX.1 specifies them
e
s 00005/00002/00029
d D 5.4 90/06/23 16:22:58 bostic 4 3
c reset can't be done in C; use VAX version, there is no tahoe version
e
s 00009/00003/00022
d D 5.3 90/06/22 19:06:33 bostic 3 2
c add rand, nargs
e
s 00015/00053/00010
d D 5.2 90/05/11 12:49:11 bostic 2 1
c first pass for new make
e
s 00063/00000/00000
d D 5.1 89/05/17 23:04:27 bostic 1 0
c stripped down libc Makefile
e
u
U
t
T
I 1
D 2
#
# Copyright (c) 1989 Regents of the University of California.
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
E 2
#	%W% (Berkeley) %G%

D 2
# All library objects contain sccsid strings by default; they may be
# excluded as a space-saving measure.  To produce a library that does
# not contain these strings, remove -DLIBC_SCCS and -DSYSLIBC_SCCS
# from DEFS below.  To remove these strings from just the system call
# stubs, remove -DSYSLIBC_SCCS from DEFS below.
#DEFS=
DEFS="-DLIBC_SCCS -DSYSLIBC_SCCS"
E 2
I 2
LIB=compat
CFLAGS+=-DLIBC_SCCS -DSYSLIBC_SCCS
I 3
AINC=	-I${.CURDIR}/../libc/${MACHINE}
E 3
E 2

D 2
SUBDIR=	4.1 4.3
TAGSFILE=tags
E 2
I 2
.PATH:	${.CURDIR}/4.1/${MACHINE} ${.CURDIR}/4.1 \
D 12
	${.CURDIR}/4.3/${MACHINE} ${.CURDIR}/4.3
E 12
I 12
	${.CURDIR}/4.3/${MACHINE} ${.CURDIR}/4.3 \
I 16
	${.CURDIR}/4.4/${MACHINE} ${.CURDIR}/4.4 \
E 16
	${.CURDIR}/regexp
E 12
E 2

D 2
all: ${SUBDIR}
E 2
I 2
# compat 4.1 sources
D 3
SRCS=	ftime.c getpw.c gtty.c rand.c reset.c stty.c tell.c times.c \
E 3
I 3
D 4
SRCS=	ftime.c getpw.c gtty.c reset.c stty.c tell.c times.c \
E 3
	utime.c vlimit.c vtimes.c
E 4
I 4
D 5
SRCS=	ftime.c getpw.c gtty.c stty.c tell.c times.c utime.c vlimit.c vtimes.c
E 5
I 5
SRCS=	ftime.c getpw.c gtty.c stty.c tell.c vlimit.c vtimes.c
E 5

.if (${MACHINE} == "vax")
SRCS+=	reset.s
.endif
E 4
E 2

D 2
${SUBDIR}: FRC
	cd $@; make ${MFLAGS} DEFS=${DEFS}
E 2
I 2
D 3
MAN3+=	ftime.0 getpw.0 rand.0 stty.0 times.0 utime.0 vlimit.0 vtimes.0
E 3
I 3
D 6
MAN3+=	ftime.0 getpw.0 stty.0 times.0 utime.0 vlimit.0 vtimes.0
E 6
I 6
MAN3+=	ftime.0 getpw.0 stty.0 vlimit.0 vtimes.0
E 6
E 3
E 2

D 2
clean:
	for i in ${SUBDIR}; \
		do (cd $$i; make ${MFLAGS} clean); done
	rm -rf libcompat.a libcompat_p.a library profiled
E 2
I 2
D 3
MLINKS+=rand.3 srand.3
E 3
MLINKS+=stty.3 gtty.3
E 2

D 2
cleandir: clean
	for i in ${SUBDIR}; \
		do (cd $$i; make ${MFLAGS} cleandir); done
E 2
I 2
# compat 4.3 sources
D 8
SRCS+=	ecvt.c gcvt.c lsearch.c rexec.c ruserpass.c sibuf.c sobuf.c strout.c
E 8
I 8
D 12
SRCS+=	ecvt.c gcvt.c lsearch.c regex.c rexec.c ruserpass.c sibuf.c \
	sobuf.c strout.c
E 12
I 12
D 15
SRCS+=	ecvt.c gcvt.c lsearch.c regex.c rexec.c sibuf.c sobuf.c strout.c
E 15
I 15
SRCS+=	cfree.c ecvt.c gcvt.c lsearch.c regex.c rexec.c sibuf.c sobuf.c \
	strout.c
E 15
E 12
E 8
I 3

D 7
.if (${MACHINE} == "tahoe")
SRCS+=	nargs.s
.elif (${MACHINE} == "vax")
SRCS+=	nargs.s
E 7
I 7
D 10
.if	(${MACHINE} == "hp300")
E 10
I 10
.if	(${MACHINE} == "hp300" || ${MACHINE} == "luna68k")
E 10
SRCS+=	insque.s remque.s
.elif	(${MACHINE} == "i386")
SRCS+=	insque.c remque.c
I 13
D 14
elif	(${MACHINE} == "mips")
E 14
I 14
.elif	(${MACHINE} == "mips")
E 14
SRCS+=	insque.c remque.c
E 13
I 9
.elif	(${MACHINE} == "sparc")
SRCS+=	insque.c remque.c
E 9
.elif	(${MACHINE} == "tahoe")
SRCS+=	nargs.s insque.s remque.s
.elif	(${MACHINE} == "vax")
SRCS+=	nargs.s insque.s remque.s
E 7
.endif
E 3
E 2

D 2
depend tags:
	for i in ${SUBDIR}; \
		do (cd $$i; make ${MFLAGS} DEFS=${DEFS} $@); done
E 2
I 2
D 7
MAN3+=	ecvt.0 lsearch.0 rexec.0
E 7
I 7
D 8
MAN3+=	ecvt.0 insque.0 lsearch.0 rexec.0
E 8
I 8
D 11
MAN3+=	ecvt.0 insque.0 lsearch.0 regex.0 rexec.0
E 11
I 11
MAN3+=	ecvt.0 insque.0 lsearch.0 re_comp.0 rexec.0
E 11
E 8
E 7
E 2

D 2
install: tags
	rm -rf library profiled
	mkdir library profiled
	for i in ${SUBDIR}; \
		do (cd $$i; make ${MFLAGS} DEFS=${DEFS} $@); done
	ls library/*.o | sort -t/ +1 > t1
	ar cr libcompat.a `lorder \`cat t1\` | tsort` csu/${MACHINE}/${DFLMON}
	ls profiled/*.o | sort -t/ +1 > t1
	ar cr libcompat_p.a `lorder \`cat t1\` | tsort` csu/${MACHINE}/${DFLMON}
	rm -rf t1 library profiled
	install -o bin -g bin -m 644 libcompat.a ${DESTDIR}/usr/lib
	ranlib ${DESTDIR}/lib/libcompat.a
	install -o bin -g bin -m 644 libcompat_p.a ${DESTDIR}/usr/lib
	ranlib ${DESTDIR}/usr/lib/libcompat_p.a
E 2
I 2
MLINKS+=ecvt.3 fcvt.3 ecvt.3 gcvt.3
I 7
MLINKS+=insque.3 remque.3
I 8
D 11
MLINKS+=regex.3 re_comp.3 regex.3 re_exec.3
E 11
I 11
MLINKS+=re_comp.3 re_exec.3
I 16

# compat 4.4 sources
SRCS+=	cuserid.c
E 16
I 12

# regexp sources
SRCS+=	regerror.c regexp.c regsub.c

MAN3+=	regexp.0

MLINKS+=regexp.3 regcomp.3 regexp.3 regexec.3 regexp.3 regsub.3 \
	regexp.3 regerror.3
E 12
E 11
E 8
E 7
E 2

D 2
FRC:
E 2
I 2
.include <bsd.lib.mk>
E 2
E 1
