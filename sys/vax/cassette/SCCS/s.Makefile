h27415
s 00001/00006/00059
d D 7.2 91/05/09 20:11:35 bostic 16 15
c makefiles don't need copyrights
e
s 00001/00001/00064
d D 7.1 86/06/05 01:56:49 mckusick 15 14
c 4.3BSD release version
e
s 00001/00000/00064
d D 6.5 86/03/12 11:48:53 karels 14 13
c delete defboo.cmd after using to force checking each time
e
s 00008/00001/00056
d D 6.4 85/09/19 08:44:26 karels 13 12
c warn about defboo.cmd
e
s 00006/00001/00051
d D 6.3 85/06/08 12:04:17 mckusick 12 10
c Add copyright
e
s 00006/00001/00051
d D 4.8 85/06/08 12:02:33 mckusick 11 8
c Add copyright
e
s 00001/00001/00051
d D 6.2 83/09/25 13:20:19 karels 10 9
c rm OBS from old cassette stuff
e
s 00000/00000/00052
d D 6.1 83/08/18 17:50:07 sam 9 8
c 4.2 distribution
e
s 00002/00002/00050
d D 4.7 83/08/05 09:49:49 karels 8 6
c CASSETTE=tu0; flcopy gets -f $CASSSETTE
e
s 00000/00000/00052
d R 6.1 83/07/29 07:50:12 sam 7 6
c 4.2 distribution
e
s 00001/00001/00051
d D 4.6 83/07/27 20:34:12 helge 6 5
c another kludge to make dd work properly with tu58/uu: conv=sync
e
s 00001/00001/00051
d D 4.5 83/07/22 14:44:16 helge 5 4
c dd with bs=2k to tu58
e
s 00017/00008/00035
d D 4.4 83/07/20 23:07:21 sam 4 3
c make big programs default on distribution cassettee
e
s 00001/00000/00042
d D 4.3 83/07/09 01:34:27 sam 3 2
c add warning
e
s 00020/00006/00022
d D 4.2 83/07/07 13:00:25 sam 2 1
c handle updates
e
s 00028/00000/00000
d D 4.1 83/07/06 21:39:48 sam 1 0
c date and time created 83/07/06 21:39:48 by sam
e
u
U
t
T
I 1
D 11
D 12
#	%M%	%I%	%E%
E 12
I 12
D 16
#
D 15
# Copyright (c) 1980 Regents of the University of California.
E 15
I 15
# Copyright (c) 1980, 1986 Regents of the University of California.
E 15
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 16
#	%W% (Berkeley) %G%
E 12
E 11
I 11
#
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W% (Berkeley) %G%
E 11
D 16
#
E 16
I 16

E 16
# Make a 750/730 tu58 cassette
# 
D 4
BOOTS=	boot boot.750
E 4
I 4
BOOTS=	boot.730 boot.750
E 4
STDBOO=	defboo.cmd anyboo.cmd restar.cmd
DEFBOO=	defboo.rb defboo.rl defboo.hk defboo.up defboo.ra
DEVBOO=	rbmboo.cmd rbsboo.cmd rlsboo.cmd hkmboo.cmd hksboo.cmd \
	upmboo.cmd upsboo.cmd ramboo.cmd rasboo.cmd
D 4
UTILS=	format.750 format copy copy.750 drtest drtest.750
E 4
I 4
UTILS=	format.730 format.750 copy.730 copy.750 drtest.730 drtest.750
I 13

E 13
E 4
D 2
CASSETTE=tu0
E 2
I 2
# order is NOT random...
D 4
OBJS=	${BOOTS} ${STDBOO} ${DEFBOO} ${DEVBOO} ${UTILS}
# this is ONLY for a 730...
BOOTOBJS=boot ${STDBOO} ${DEFBOO} ${DEVBOO} format copy drtest
E 4
I 4
OBJS=	boot ${STDBOO} ${DEFBOO} ${DEVBOO} format copy drtest
E 4
FROMDEC=d[lmq]* cs* *boo.* boot.exe vmb.exe
I 13

E 13
D 8
CASSETTE=/dev/uu0
E 8
I 8
CASSETTE=/dev/tu0
E 8
E 2

all:	cassette

D 2
# order is NOT random...
cassette: ${BOOTS} ${STDBOO} ${DEFBOO} ${DEVBOO} ${UTILS}
E 2
I 2
D 4
cassette: ${OBJS}
E 4
I 4
cassette: boot.750 ${STDBOO} ${DEFBOO} ${DEVBOO} format.750
cassette: copy.750 drtest.750
E 4
E 2
	cp /dev/null cassette
D 2
	arff mcrf cassette ${BOOTS} ${STDBOO} ${DEFBOO} ${DEVBOO} ${UTILS}
E 2
I 2
	cp /dev/null pad
I 4
	cp boot.750 boot
	cp format.750 format
	cp copy.750 copy
	cp drtest.750 drtest
E 4
	arff mcrf cassette ${OBJS} pad
	rm -f pad
E 2

../mdec/tuboot: ../mdec/tuboot.s
	cd ../mdec; make ${MFLAGS} tuboot

install: cassette ../mdec/tuboot
D 2
	dd if=cassette of=/dev/${CASSETTE}
	dd if=../mdec/tuboot of=/dev/${CASSETTE} bs=512 count=2
E 2
I 2
D 5
	dd if=cassette of=${CASSETTE}
E 5
I 5
D 6
	dd if=cassette of=${CASSETTE} bs=2k
E 6
I 6
	dd if=cassette of=${CASSETTE} bs=2k conv=sync
E 6
E 5
	dd if=../mdec/tuboot of=${CASSETTE} bs=512 count=2

# build a 730 boot cassette from a DEC console cassette
I 3
# DONT TRY THIS ON A 750 W/O MRSP, THE SYSTEM WILL CRASH
E 3
D 4
update:	${BOOTOBJS}
E 4
I 4
update:	boot.730 ${STDBOO} ${DEFBOO} ${DEVBOO} format.730
update:	copy.730 drtest.730
E 4
	-mkdir fromdec
D 10
	cd fromdec; arff mxf ${CASSETTE}; rm -f ${FROMDEC}; \
E 10
I 10
	cd fromdec; arff mxf ${CASSETTE}; rm -f ${FROMDEC} ${OBJS}; \
E 10
D 8
		flcopy -t3; arff mcrf ${CASSETTE} *
E 8
I 8
		flcopy -t3 -f ${CASSETTE}; arff mcrf ${CASSETTE} *
E 8
	rm -rf fromdec
D 4
	arff mrf ${CASSETTE} ${BOOTOBJS}
E 4
I 4
	cp boot.730 boot
	cp format.730 format
	cp copy.730 copy
	cp drtest.730 drtest
	arff mrf ${CASSETTE} ${OBJS}
I 14
	-rm -f defboo.cmd
E 14
E 4
E 2

I 13
defboo.cmd:
	@echo You must copy one of ${DEFBOO} to defboo.cmd.
	@echo See installing and operating guide for details.
	@/bin/false	#force exits

E 13
clean:
D 13
	rm -f ${BOOTS} ${UTILS} cassette form50 boot50 copy50
E 13
I 13
	rm -f ${BOOTS} ${UTILS} cassette form50 boot50 copy50 defboo.cmd
E 13
I 4
	rm -f boot format copy drtest
E 4
E 1
