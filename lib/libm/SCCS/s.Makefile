h43369
s 00000/00000/00162
d D 8.1 93/06/04 16:57:37 bostic 33 32
c 4.4BSD snapshot (revision 8.1)
e
s 00012/00012/00150
d D 5.16 93/02/10 10:51:29 bostic 32 31
c add gamma.c to all architectures
e
s 00002/00002/00160
d D 5.15 93/02/08 18:54:26 torek 31 30
c sparc needs gamma.c
e
s 00003/00003/00159
d D 5.14 93/02/08 18:51:25 bostic 30 29
c check in for bostic by torek: don't use assembly exp() for mc68881 either
e
s 00002/00002/00160
d D 5.13 93/01/10 17:51:54 bostic 29 28
c don't use assembly log() for mc68881 (try #2)
e
s 00001/00001/00161
d D 5.12 93/01/10 17:47:51 bostic 28 27
c don't use assembly log() for mc68881, need support routines from
c general implementation
e
s 00002/00002/00160
d D 5.11 92/12/02 15:35:09 bostic 27 26
c add gamma function, from Peter McIlroy
e
s 00014/00000/00148
d D 5.10 92/07/29 11:47:45 bostic 26 25
c update from Chris Torek for the sparc
e
s 00001/00001/00147
d D 5.9 92/06/04 15:14:11 mckusick 25 24
c add support for luna68k from Omron
e
s 00016/00002/00132
d D 5.8 92/03/07 09:15:08 ralph 24 22
c added mips case
e
s 00013/00011/00123
d D 5.7.1.1 91/05/07 11:09:53 bostic 23 22
c branch for the 2nd network distribution
e
s 00004/00007/00130
d D 5.7 91/05/02 05:26:08 cael 22 21
c deleted links (floor,sin,asinh,sinh), added files (cos,cosh,acosh,
c tan,tanh,atan,atan2,atanh,sinh,asinh,asin,ceil,rint,fabs,fmod)
e
s 00020/00000/00117
d D 5.6 90/12/31 12:15:43 william 21 20
c added 386 support
e
s 00000/00000/00117
d D 5.5 90/12/31 12:12:48 william 20 19
c added 386 support (actually, 387) and placeholder for other insns.
e
s 00002/00001/00115
d D 5.4 90/06/23 12:27:28 bostic 19 18
c libm Makefile makes .depend too often
e
s 00001/00001/00115
d D 5.3 90/06/16 13:36:16 bostic 18 17
c typo
e
s 00071/00043/00045
d D 5.2 90/05/18 10:34:29 bostic 17 16
c add hp300 support
e
s 00001/00001/00087
d D 5.1 90/05/17 20:30:32 bostic 16 15
c don't use symlinks, use search order
e
s 00001/00001/00087
d D 1.13 90/05/16 12:45:51 bostic 15 14
c move abs.3 to lib/libc/stdlib
e
s 00059/00111/00029
d D 1.12 90/05/11 12:51:26 bostic 14 13
c first pass for new make
e
s 00002/00002/00138
d D 1.11 89/05/30 10:35:08 bostic 13 12
c add fmod.c
e
s 00052/00039/00088
d D 1.10 89/05/10 22:36:19 bostic 12 11
c add man pages, remove dependencies, cleanup
e
s 00010/00005/00117
d D 1.9 88/06/30 17:45:01 bostic 11 10
c install approved copyright notice
e
s 00001/00001/00121
d D 1.8 87/12/07 14:07:42 bostic 10 8
c tahoe release
e
s 00000/00000/00122
d R 5.1 87/11/30 18:33:45 bostic 9 8
c tahoe release
e
s 00025/00021/00097
d D 1.7 87/11/30 18:32:53 bostic 8 7
c new headers; handle subdirs
e
s 00016/00016/00102
d D 1.6 87/07/13 19:23:22 zliu 7 6
c clean-ups.
e
s 00005/00001/00113
d D 1.5 87/07/13 15:30:00 zliu 6 4
c adding NATIONAL support.
e
s 00004/00000/00114
d R 1.5 87/07/13 15:25:11 zliu 5 4
c adding NATIONAL support.
e
s 00014/00008/00100
d D 1.4 87/07/13 13:31:46 zliu 4 3
c re-structuring
e
s 00062/00037/00046
d D 1.3 87/07/07 01:32:14 zliu 3 2
c first shot at TAHOE.
e
s 00004/00004/00079
d D 1.2 85/09/11 23:53:14 elefunt 2 1
c 4.3BSD version dated 09/11/85.
e
s 00083/00000/00000
d D 1.1 85/09/06 17:52:35 zliu 1 0
c date and time created 85/09/06 17:52:35 by zliu
e
u
U
f b 
t
T
I 1
D 14
#
D 2
#	%W% (ELEFUNT) %G%
E 2
I 2
D 3
#	%Z%%M%	4.9	9/11/85; %I% (ucb.elefunt) %G%
E 3
I 3
# Copyright (c) 1987 Regents of the University of California.
D 8
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 8
I 8
# All rights reserved.
E 8
E 3
E 2
#
D 2
SCCSID = "%W% (ELEFUNT) %G%"
E 2
I 2
D 3
SCCSID = "%Z%%M%	4.9 9/11/85; %I% (ucb.elefunt) %G%"
E 3
I 3
D 4
#	@(#)Makefile	4.12	(Berkeley)	7/6/87
E 4
I 4
D 8
#	%Z%%M%	%I%	(ucb.elefunt)	%G%
E 8
I 8
# Redistribution and use in source and binary forms are permitted
D 11
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific written prior permission. This software
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
E 8
E 4
E 3
E 2
#
E 14
I 8
#	%W% (Berkeley) %G%
#
E 8
D 17
# This high quality math library is intended to run on either a VAX in
# D_floating format or a machine that conforms to the IEEE standard 754
# for double precision floating-point arithmetic.
#
# WARNING: On machines other than the ones mentioned above, run the original
# Version 7 math library, if nothing better is available.
D 3

E 3
#
D 3
# MACH indicates the type of floating point hardware you are using; legal
E 3
I 3
D 14
# MACHINE indicates the type of floating point hardware you are using; legal
E 3
# values are:
E 14
I 14
# HARDWARE indicates the type of floating point hardware you are using;
# we use MACHINE because we don't have anything better.
# Current legal values are:
E 14
#
D 7
# VAX		- for the VAX D_floating format, the default.
I 4
# TAHOE		- for the TAHOE double format.
E 4
# NATIONAL	- for those IEEE machines whose floating point implementation
E 7
I 7
# vax		- for the VAX D_floating format, the default.
# tahoe		- for the TAHOE double format.
# national	- for those IEEE machines whose floating point implementation
E 17
I 17
# ieee		- for most IEEE machines, we hope.
# mc68881	- the, ahem, mc68881.
# national	- for those ieee machines whose floating point implementation
E 17
E 7
#		  has similar byte ordering as the NATIONAL 32016 with 32081.
I 21
# i386		- i387 NPX, currently the same as "national"
I 24
# mips		- for MIPS achitecture machines
E 24
E 21
D 7
# IEEE		- for other IEEE machines, we hope.
E 7
I 7
D 17
# ieee		- for other IEEE machines, we hope.
E 17
I 17
# tahoe		- for the tahoe double format.
# vax		- for the vax D_floating format
E 17
E 7
D 14
#
D 3
MACH = VAX

E 3
I 3
D 4
CFLAGS=	-O
E 4
I 4
CFLAGS=	-O -D${MACHINE}
E 4
LIBC=	/lib/libc.a
I 8
SUBDIR=	vax tahoe national common ieee
E 8
E 3
#
D 3
# invoke object-code optimizer with appropriate MACH definition
#
CFLAGS=-O -D${MACH}

INSTALL=install

DESTDIR=

#
E 3
# Files comprising the standard Math library;
D 4
# actually there are more under ${MACH}/ subdirectory.
E 4
I 4
# actually there are more under ${MACHINE}/ subdirectory.
E 4
#
D 3
SRCS =	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c erf.c \
E 3
I 3
SRCS=	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c erf.c \
E 3
D 2
	exp.c exp__E.c expm1.c floor.c lgama.c j0.c j1.c jn.c \
E 2
I 2
D 13
	exp.c exp__E.c expm1.c floor.c lgamma.c j0.c j1.c jn.c \
E 13
I 13
	exp.c exp__E.c expm1.c floor.c fmod.c lgamma.c j0.c j1.c jn.c \
E 13
E 2
	log.c log10.c log1p.c log__L.c pow.c sinh.c tanh.c
D 3

FILES =	acosh.o asincos.o asinh.o atan.o atanh.o cosh.o erf.o \
E 3
I 3
OBJS=	acosh.o asincos.o asinh.o atan.o atanh.o cosh.o erf.o \
E 3
D 2
	exp.o exp__E.o expm1.o floor.o lgama.o j0.o j1.o jn.o \
E 2
I 2
D 13
	exp.o exp__E.o expm1.o floor.o lgamma.o j0.o j1.o jn.o \
E 13
I 13
	exp.o exp__E.o expm1.o floor.o fmod.o lgamma.o j0.o j1.o jn.o \
E 13
E 2
	log.o log10.o log1p.o log__L.o pow.o sinh.o tanh.o 
I 12
MAN=	abs.0 asinh.0 erf.0 exp.0 floor.0 hypot.0 ieee.0 infnan.0 j0.0 \
	lgamma.0 math.0 sin.0 sinh.0 sqrt.0
MDIR=	${DESTDIR}/usr/man/cat3
E 14
E 12

I 23
# Missing: erf.c, j0.c, j1.c, jn.c, lgamma.c

E 23
D 3
TAGSFILE=tags

E 3
D 14
.c.o:
####	generate additional code for profiling (-p)
	${CC} -p ${CFLAGS} -c $*.c
####	generate relocation bits (-r) & preserve symbols that begin with L (-X)
	-ld -X -r $*.o
	mv a.out profiled/$*.o
	${CC} ${CFLAGS} -c $*.c
####	generate relocation bits (-r) but don't preserve local symbols (-x)
	-ld -x -r $*.o
	mv a.out $*.o
E 14
I 14
LIB=	m
I 17
CFLAGS+=-I${.CURDIR}/common_source

.if (${MACHINE} == "ieee")

E 17
HARDWARE=${MACHINE}
D 17
CFLAGS+=-D${HARDWARE} -I${.CURDIR}/common_source
.PATH:	${.CURDIR}/common_source
E 17
I 17
.PATH:	${.CURDIR}/common_source ${.CURDIR}/common ${.CURDIR}/ieee
# common_source
D 23
SRCS+=	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c erf.c exp.c \
D 27
	exp__E.c expm1.c floor.c fmod.c lgamma.c j0.c j1.c jn.c log.c \
E 23
I 23
SRCS+=	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c exp.c \
	exp__E.c expm1.c floor.c fmod.c log.c \
E 23
	log10.c log1p.c log__L.c pow.c sinh.c tanh.c
E 27
I 27
	exp__E.c expm1.c floor.c fmod.c gamma.c lgamma.c j0.c j1.c \
	jn.c log.c log10.c log1p.c log__L.c pow.c sinh.c tanh.c
E 27
# common
SRCS+=	atan2.c sincos.c tan.c
# ieee
SRCS+=	cabs.c cbrt.c support.c
E 17
E 14

D 14
all: libm.a libm_p.a
E 14
I 14
D 17
SRCS=	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c erf.c exp.c \
E 17
I 17
D 25
.elif (${MACHINE} == "hp300")
E 25
I 25
.elif (${MACHINE} == "hp300" || ${MACHINE} == "luna68k")
E 25

HARDWARE=mc68881
.PATH:	${.CURDIR}/mc68881 ${.CURDIR}/common_source ${.CURDIR}/ieee
# common_source
D 23
D 29
SRCS+=	acosh.c asinh.c erf.c exp__E.c fmod.c lgamma.c j0.c j1.c log__L.c \
E 23
I 23
SRCS+=	acosh.c asinh.c exp__E.c fmod.c log__L.c \
E 23
	pow.c
E 29
I 29
D 30
SRCS+=	acosh.c asinh.c erf.c exp__E.c fmod.c lgamma.c j0.c j1.c log.c \
	log__L.c pow.c
E 30
I 30
D 32
SRCS+=	acosh.c asinh.c erf.c exp.c exp__E.c fmod.c lgamma.c j0.c j1.c \
	log.c log__L.c pow.c
E 32
I 32
SRCS+=	acosh.c asinh.c erf.c exp.c exp__E.c fmod.c gamma.c lgamma.c \
	j0.c j1.c log.c log__L.c pow.c
E 32
E 30
E 29
# mc68881
D 30
SRCS+=	asincos.s atan.s atan2.c atanh.s cosh.s exp.s expm1.s floor.s \
E 30
I 30
SRCS+=	asincos.s atan.s atan2.c atanh.s cosh.s expm1.s floor.s \
E 30
D 28
	log.s log10.s log1p.s sincos.s sinh.s sqrt.s support.s tan.s tanh.s
E 28
I 28
	log10.s log1p.s sincos.s sinh.s sqrt.s support.s tan.s tanh.s
E 28
# ieee
SRCS+=	cabs.c cbrt.c

I 21
.elif (${MACHINE} == "i386")

HARDWARE=i387
D 24
.PATH:	${.CURDIR}/common_source ${.CURDIR}/common \
	${.CURDIR}/ieee
E 24
I 24
.PATH:	${.CURDIR}/common_source ${.CURDIR}/common ${.CURDIR}/ieee
CFLAGS+= -Dnational
# common_source
SRCS+=	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c erf.c exp.c \
D 32
	exp__E.c expm1.c floor.c fmod.c lgamma.c j0.c j1.c jn.c log.c \
	log10.c log1p.c log__L.c pow.c sinh.c tanh.c
E 32
I 32
	exp__E.c expm1.c floor.c fmod.c gamma.c lgamma.c j0.c j1.c \
	jn.c log.c log10.c log1p.c log__L.c pow.c sinh.c tanh.c
E 32
# common
SRCS+=	atan2.c sincos.c tan.c
# ieee
SRCS+=	cabs.c cbrt.c support.c

.elif (${MACHINE} == "mips")

HARDWARE=${MACHINE}
.PATH:	${.CURDIR}/common_source ${.CURDIR}/common ${.CURDIR}/ieee
E 24
CFLAGS+= -Dnational
# common_source
D 23
SRCS+=	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c erf.c exp.c \
D 32
	exp__E.c expm1.c floor.c fmod.c lgamma.c j0.c j1.c jn.c log.c \
E 23
I 23
SRCS+=	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c exp.c \
	exp__E.c expm1.c floor.c fmod.c log.c \
E 23
	log10.c log1p.c log__L.c pow.c sinh.c tanh.c
E 32
I 32
	exp__E.c expm1.c floor.c fmod.c gamma.c lgamma.c j0.c j1.c \
	jn.c log.c log10.c log1p.c log__L.c pow.c sinh.c tanh.c
E 32
# common
SRCS+=	atan2.c sincos.c tan.c
# ieee
SRCS+=	cabs.c cbrt.c support.c

.elif (${MACHINE} == "national")

HARDWARE=${MACHINE}
.PATH:	${.CURDIR}/common_source ${.CURDIR}/common ${.CURDIR}/national \
E 21
.elif (${MACHINE} == "national")

HARDWARE=${MACHINE}
.PATH:	${.CURDIR}/common_source ${.CURDIR}/common ${.CURDIR}/national \
	${.CURDIR}/ieee
# common_source
D 23
SRCS+=	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c erf.c exp.c \
E 17
D 32
	exp__E.c expm1.c floor.c fmod.c lgamma.c j0.c j1.c jn.c log.c \
E 23
I 23
SRCS+=	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c exp.c \
	exp__E.c expm1.c floor.c fmod.c log.c \
E 23
	log10.c log1p.c log__L.c pow.c sinh.c tanh.c
E 32
I 32
	exp__E.c expm1.c floor.c fmod.c gamma.c lgamma.c j0.c j1.c jn.c \
	log.c log10.c log1p.c log__L.c pow.c sinh.c tanh.c
E 32
I 17
# common
SRCS+=	atan2.c sincos.c tan.c
# national
SRCS+=	sqrt.s support.s
# ieee
SRCS+=	cabs.c cbrt.c
E 17
E 14

I 26
.elif (${MACHINE} == "sparc")

HARDWARE=${MACHINE}
.PATH:  ${.CURDIR}/common_source ${.CURDIR}/common ${.CURDIR}/ieee
# common_source
SRCS+=	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c erf.c exp.c \
D 31
	exp__E.c expm1.c floor.c fmod.c lgamma.c j0.c j1.c jn.c log.c \
	log10.c log1p.c log__L.c pow.c sinh.c tanh.c
E 31
I 31
	exp__E.c expm1.c floor.c fmod.c gamma.c lgamma.c j0.c j1.c \
	jn.c log.c log10.c log1p.c log__L.c pow.c sinh.c tanh.c
E 31
# XXX should do sqrt & support functions in assembly
# common
SRCS+=	atan2.c sincos.c tan.c
# ieee
SRCS+=	cabs.c cbrt.c support.c

E 26
I 17
.elif (${MACHINE} == "tahoe")

HARDWARE=${MACHINE}
.PATH:	${.CURDIR}/common_source ${.CURDIR}/common ${.CURDIR}/tahoe \
# common_source
D 23
SRCS+=	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c erf.c exp.c \
D 32
	exp__E.c expm1.c floor.c fmod.c lgamma.c j0.c j1.c jn.c log.c \
E 23
I 23
SRCS+=	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c exp.c \
	exp__E.c expm1.c floor.c fmod.c log.c \
E 23
	log10.c log1p.c log__L.c pow.c sinh.c tanh.c
E 32
I 32
	exp__E.c expm1.c floor.c fmod.c gamma.c lgamma.c j0.c j1.c jn.c \
	log.c log10.c log1p.c log__L.c pow.c sinh.c tanh.c
E 32
# common
SRCS+=	atan2.c sincos.c tan.c
# tahoe
SRCS+=	cabs.s cbrt.s sqrt.s support.s infnan.s

.elif (${MACHINE} == "vax")

HARDWARE=${MACHINE}
.PATH:	${.CURDIR}/common_source ${.CURDIR}/vax
# common_source
D 23
SRCS+=	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c erf.c exp.c \
D 18
	exp__E.c expm1.c floor.c fmod.c lgamma.c j0.c j1.c jn.c log.c
E 18
I 18
D 32
	exp__E.c expm1.c floor.c fmod.c lgamma.c j0.c j1.c jn.c log.c \
E 23
I 23
SRCS+=	acosh.c asincos.c asinh.c atan.c atanh.c cosh.c exp.c \
	exp__E.c expm1.c floor.c fmod.c log.c \
E 23
E 18
	log10.c log1p.c log__L.c pow.c sinh.c tanh.c
E 32
I 32
	exp__E.c expm1.c floor.c fmod.c gamma.c lgamma.c j0.c j1.c jn.c \
	log.c log10.c log1p.c log__L.c pow.c sinh.c tanh.c
E 32
# vax
SRCS+=	atan2.s cabs.s cbrt.s sqrt.s sincos.s tan.s argred.s support.s \
	infnan.s

.endif

E 17
D 3
libm.a libm_p.a: ${FILES} more
	cd profiled; ar cru ../libm_p.a ${FILES}
	ar cru libm.a ${FILES}
E 3
I 3
D 14
libm.a libm_p.a: ${OBJS} more.${MACHINE}
D 12
	cd profiled; ar cru ../libm_p.a ${OBJS}
	ar cru libm.a ${OBJS}
E 12
I 12
	@echo building normal libm
	@ar cru libm.a ${OBJS}
	ranlib libm.a
	@echo building profiled libm
	@cd profiled; ar cru ../libm_p.a ${OBJS}
	ranlib libm_p.a
E 14
I 14
D 15
MAN3+=	abs.0 asinh.0 erf.0 exp.0 floor.0 hypot.0 ieee.0 infnan.0 j0.0 \
E 15
I 15
D 22
MAN3+=	asinh.0 erf.0 exp.0 floor.0 hypot.0 ieee.0 infnan.0 j0.0 \
E 15
	lgamma.0 math.0 sin.0 sinh.0 sqrt.0
E 22
I 22
MAN3+=	acos.0 acosh.0 asin.0 asinh.0 atan.0 atan2.0 atanh.0 ceil.0 \
	cos.0 cosh.0 erf.0 exp.0 fabs.0 floor.0 fmod.0 hypot.0 ieee.0 \
	infnan.0 j0.0 lgamma.0 math.0 rint.0 sin.0 sinh.0 sqrt.0 \
	tan.0 tanh.0
E 22
E 14
E 12
E 3

D 3
more:
	@cd ${MACH}; make "MACH=${MACH}" "CFLAGS=${CFLAGS}"
E 3
I 3
D 4
more.vax: FRC
	cd VAX; make "CFLAGS=${CFLAGS} -DVAX"
E 4
I 4
D 7
more.IEEE: FRC
	cd COMMON; make "CFLAGS=${CFLAGS}"
	cd IEEE; make "CFLAGS=${CFLAGS}"
E 7
I 7
D 14
more.ieee: FRC
D 8
	cd common; make "CFLAGS=${CFLAGS}"
	cd ieee; make "CFLAGS=${CFLAGS}"
E 8
I 8
	for i in common ieee; do (cd $$i; make ${MFLAGS}); done
E 14
I 14
D 22
MLINKS+=asinh.3 acosh.3 asinh.3 atanh.3
E 22
MLINKS+=erf.3 erfc.3
MLINKS+=exp.3 expm1.3 exp.3 log.3 exp.3 log10.3 exp.3 log1p.3 exp.3 pow.3
D 22
MLINKS+=floor.3 fabs.3 floor.3 ceil.3 floor.3 rint.3
E 22
MLINKS+=hypot.3 cabs.3
MLINKS+=ieee.3 copysign.3 ieee.3 drem.3 ieee.3 finite.3 ieee.3 logb.3 \
	ieee.3 scalb.3
MLINKS+=j0.3 j1.3 j0.3 jn.3 j0.3 y0.3 j0.3 y1.3 j0.3 yn.3
MLINKS+=lgamma.3 gamma.3
D 22
MLINKS+=sin.3 tan.3 sin.3 acos.3 sin.3 asin.3 sin.3 atan.3 sin.3 atan2.3 \
	sin.3 cos.3
MLINKS+=sinh.3 cosh.3
E 22
E 14
E 8
E 7
E 4
E 3

I 6
D 7
more.NATIONAL: FRC
	cd COMMON; make "CFLAGS=${CFLAGS}"
	cd NATIONAL; make "CFLAGS=${CFLAGS}"
E 7
I 7
D 14
more.national: FRC
D 8
	cd common; make "CFLAGS=${CFLAGS}"
	cd national; make "CFLAGS=${CFLAGS}"
E 8
I 8
	for i in common national; do (cd $$i; make ${MFLAGS}); done
E 14
I 14
D 17
.if $(HARDWARE) == "ieee"
.PATH:	${.CURDIR}/common ${.CURDIR}/ieee
SRCS+=	atan2.c sincos.c tan.c				# common
SRCS+=	cabs.c cbrt.c support.c				# ieee
.endif
E 14
E 8
E 7

E 6
D 3
install: libm.a libm_p.a
E 3
I 3
D 4
more.tahoe: FRC
	cd IEEE; make "CFLAGS=${CFLAGS} -DTAHOE"
E 4
I 4
D 7
more.TAHOE: FRC
	cd COMMON; make "CFLAGS=${CFLAGS}"
	cd TAHOE; make "CFLAGS=${CFLAGS}"
E 7
I 7
D 14
more.tahoe: FRC
D 8
	cd common; make "CFLAGS=${CFLAGS}"
	cd tahoe; make "CFLAGS=${CFLAGS}"
E 8
I 8
	for i in common tahoe; do (cd $$i; make ${MFLAGS}); done
E 14
I 14
.if $(HARDWARE) == "national"
D 16
.PATH:	${.CURDIR}/common ${.CURDIR}/national
E 16
I 16
.PATH:	${.CURDIR}/common ${.CURDIR}/national ${.CURDIR}/ieee
E 16
SRCS+=	atan2.c sincos.c tan.c				# common
SRCS+=	cabs.c cbrt.c sqrt.s support.s			# national
.endif
E 14
E 8
E 7
E 4

I 4
D 7
more.VAX: FRC
	cd VAX; make "CFLAGS=${CFLAGS}"
E 7
I 7
D 14
more.vax: FRC
	cd vax; make "CFLAGS=${CFLAGS}"
E 14
I 14
.if $(HARDWARE) == "tahoe"
.PATH:	${.CURDIR}/common ${.CURDIR}/tahoe
SRCS+=	atan2.c sincos.c tan.c				# common
SRCS+=	cabs.s cbrt.s sqrt.s support.s infnan.s		# tahoe
.endif
E 14
E 7

E 4
D 12
clean: FRC
E 12
I 12
D 14
clean: 
E 12
D 4
	rm -f ${OBJS} core libnm.a libnm_p.a IEEE/*.o VAX/*.o profiled/*.o
E 4
I 4
D 6
	rm -f ${OBJS} core libm.a libm_p.a COMMON/*.o IEEE/*.o TAHOE/*.o VAX/*.o profiled/*.o
E 6
I 6
D 7
	rm -f ${OBJS} core libm.a libm_p.a COMMON/*.o IEEE/*.o NATIONAL/*.o TAHOE/*.o VAX/*.o profiled/*.o
E 7
I 7
D 8
	rm -f ${OBJS} core libm.a libm_p.a common/*.o ieee/*.o national/*.o tahoe/*.o vax/*.o profiled/*.o
E 8
I 8
D 10
	rm -f ${OBJS} core libm.a libm_p.a
E 10
I 10
	rm -f ${OBJS} profiled/*.o core libm.a libm_p.a
E 10
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} clean); done
E 14
I 14
.if $(HARDWARE) == "vax"
.PATH:	${.CURDIR}/vax
SRCS+=	atan2.s cabs.s cbrt.s sqrt.s sincos.s tan.s \
	argred.s support.s infnan.s			# vax
.endif
E 14
E 8
E 7
E 6
E 4

E 17
D 12
depend: FRC
E 12
I 12
D 14
cleandir: clean
	rm -f ${MAN} tags .depend
E 14
I 14
# can't use the standard mkdep, because there are some .s files that
# are using '#' as a comment indicator and cpp thinks it's an undefined
# control.
E 14

D 14
depend: 
E 12
	mkdep ${CFLAGS} ${SRCS}
I 8
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} depend); done
E 14
I 14
D 19
depend: ${SRCS}
E 19
I 19
depend: .depend
.depend: ${SRCS}
E 19
	mkdep ${CFLAGS:M-[ID]*} ${.ALLSRC:M*.c}
E 14
E 8

D 12
install: FRC
E 3
D 8
	-rm -f ${DESTDIR}/usr/lib/libnm.a ${DESTDIR}/usr/lib/libnm_p.a
E 8
D 3
	${INSTALL} libm.a ${DESTDIR}/usr/lib
	ln ${DESTDIR}/usr/lib/libm.a ${DESTDIR}/usr/lib/libnm.a
E 3
I 3
	install -o bin -g bin -m 644 libm.a ${DESTDIR}/usr/lib/libm.a
D 8
#	ln ${DESTDIR}/usr/lib/libm.a ${DESTDIR}/usr/lib/libnm.a
E 8
E 3
	ranlib ${DESTDIR}/usr/lib/libm.a
D 3
	${INSTALL} libm_p.a ${DESTDIR}/usr/lib
	ln ${DESTDIR}/usr/lib/libm_p.a ${DESTDIR}/usr/lib/libnm_p.a
E 3
I 3
	install -o bin -g bin -m 644 libm_p.a ${DESTDIR}/usr/lib/libm_p.a
D 8
#	ln ${DESTDIR}/usr/lib/libm_p.a ${DESTDIR}/usr/lib/libnm_p.a
E 8
E 3
	ranlib ${DESTDIR}/usr/lib/libm_p.a
E 12
I 12
D 14
install: ${MAN}
	install -o bin -g bin -m 444 libm.a ${DESTDIR}/usr/lib/libm.a
	ranlib -t ${DESTDIR}/usr/lib/libm.a
	install -o bin -g bin -m 444 libm_p.a ${DESTDIR}/usr/lib/libm_p.a
	ranlib -t ${DESTDIR}/usr/lib/libm_p.a
	install -c -o bin -g bin -m 444 ${MAN} ${MDIR}
	rm -f ${MDIR}/acosh.0; ln ${MDIR}/asinh.0 ${MDIR}/acosh.0
	rm -f ${MDIR}/atanh.0; ln ${MDIR}/asinh.0 ${MDIR}/atanh.0
	rm -f ${MDIR}/erfc.0; ln ${MDIR}/erf.0 ${MDIR}/erfc.0
	rm -f ${MDIR}/expm1.0; ln ${MDIR}/exp.0 ${MDIR}/expm1.0
	rm -f ${MDIR}/log.0; ln ${MDIR}/exp.0 ${MDIR}/log.0
	rm -f ${MDIR}/log10.0; ln ${MDIR}/exp.0 ${MDIR}/log10.0
	rm -f ${MDIR}/log1p.0; ln ${MDIR}/exp.0 ${MDIR}/log1p.0
	rm -f ${MDIR}/pow.0; ln ${MDIR}/exp.0 ${MDIR}/pow.0
	rm -f ${MDIR}/fabs.0; ln ${MDIR}/floor.0 ${MDIR}/fabs.0
	rm -f ${MDIR}/ceil.0; ln ${MDIR}/floor.0 ${MDIR}/ceil.0
	rm -f ${MDIR}/rint.0; ln ${MDIR}/floor.0 ${MDIR}/rint.0
	rm -f ${MDIR}/cabs.0; ln ${MDIR}/hypot.0 ${MDIR}/cabs.0
	rm -f ${MDIR}/copysign.0; ln ${MDIR}/ieee.0 ${MDIR}/copysign.0
	rm -f ${MDIR}/drem.0; ln ${MDIR}/ieee.0 ${MDIR}/drem.0
	rm -f ${MDIR}/finite.0; ln ${MDIR}/ieee.0 ${MDIR}/finite.0
	rm -f ${MDIR}/logb.0; ln ${MDIR}/ieee.0 ${MDIR}/logb.0
	rm -f ${MDIR}/scalb.0; ln ${MDIR}/ieee.0 ${MDIR}/scalb.0
	rm -f ${MDIR}/j1.0; ln ${MDIR}/j0.0 ${MDIR}/j1.0
	rm -f ${MDIR}/jn.0; ln ${MDIR}/j0.0 ${MDIR}/jn.0
	rm -f ${MDIR}/y0.0; ln ${MDIR}/j0.0 ${MDIR}/y0.0
	rm -f ${MDIR}/y1.0; ln ${MDIR}/j0.0 ${MDIR}/y1.0
	rm -f ${MDIR}/yn.0; ln ${MDIR}/j0.0 ${MDIR}/yn.0
	rm -f ${MDIR}/gamma.0; ln ${MDIR}/lgamma.0 ${MDIR}/gamma.0
	rm -f ${MDIR}/tan.0; ln ${MDIR}/sin.0 ${MDIR}/tan.0
	rm -f ${MDIR}/acos.0; ln ${MDIR}/sin.0 ${MDIR}/acos.0
	rm -f ${MDIR}/asin.0; ln ${MDIR}/sin.0 ${MDIR}/asin.0
	rm -f ${MDIR}/atan.0; ln ${MDIR}/sin.0 ${MDIR}/atan.0
	rm -f ${MDIR}/atan2.0; ln ${MDIR}/sin.0 ${MDIR}/atan2.0
	rm -f ${MDIR}/cos.0; ln ${MDIR}/sin.0 ${MDIR}/cos.0
	rm -f ${MDIR}/cosh.0; ln ${MDIR}/sinh.0 ${MDIR}/cosh.0
E 14
I 14
.include <bsd.lib.mk>
E 14
E 12

D 3
tags:
	cwd=`pwd`; \
	for i in ${SRCS}; do \
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done
E 3
I 3
D 12
lint: FRC
E 12
I 12
D 14
lint: ${SRCS}
E 12
	lint ${CFLAGS} ${SRCS}
E 14
I 14
.s.o:
	${AS} -o ${.TARGET} ${.IMPSRC}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}
E 14
E 3

D 3
clean:
	-rm -f *.o ${MACH}/*.o profiled/*.o libm.a libm_p.a tags
E 3
I 3
D 12
tags: FRC
E 12
I 12
D 14
tags: ${SRCS}
E 12
	ctags ${SRCS}
I 8
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} tags); done
E 14
I 14
.s.po:
	sed -f ${.CURDIR}/${HARDWARE}/mcount.sed ${.IMPSRC} | \
	    ${AS} -o ${.TARGET}
	@${LD} -X -r ${.TARGET}
	@mv a.out ${.TARGET}
E 14
E 8
D 17

E 17
D 14
FRC:
E 14
D 12

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

acosh.o: acosh.c
asincos.o: asincos.c
asinh.o: asinh.c
atan.o: atan.c
D 8
atanh.o: atanh.c
E 8
I 8
atanh.o: atanh.c /usr/include/errno.h
E 8
cosh.o: cosh.c
erf.o: erf.c
exp.o: exp.c
exp__E.o: exp__E.c
expm1.o: expm1.c
floor.o: floor.c
D 8
lgamma.o: lgamma.c /usr/include/math.h
j0.o: j0.c /usr/include/math.h
j1.o: j1.c /usr/include/math.h
jn.o: jn.c /usr/include/math.h
log.o: log.c
E 8
I 8
lgamma.o: lgamma.c /usr/include/math.h /usr/include/errno.h
j0.o: j0.c /usr/include/math.h /usr/include/errno.h
j1.o: j1.c /usr/include/math.h /usr/include/errno.h
jn.o: jn.c /usr/include/math.h /usr/include/errno.h
log.o: log.c /usr/include/errno.h
E 8
log10.o: log10.c
D 8
log1p.o: log1p.c
E 8
I 8
log1p.o: log1p.c /usr/include/errno.h
E 8
log__L.o: log__L.c
D 8
pow.o: pow.c
E 8
I 8
pow.o: pow.c /usr/include/errno.h
E 8
sinh.o: sinh.c
tanh.o: tanh.c

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 12
E 3
E 1
