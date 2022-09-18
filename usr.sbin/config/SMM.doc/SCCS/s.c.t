h35325
s 00002/00002/00081
d D 8.1 93/06/08 14:01:12 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00079
d D 6.3 91/04/17 11:35:07 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00010/00079
d D 6.2 86/06/03 18:05:50 karels 3 2
c 4.3 version
e
s 00000/00000/00089
d D 6.1 86/05/25 16:40:18 mckusick 2 1
c 4.3BSD beta release document
e
s 00089/00000/00000
d D 5.1 86/05/25 16:40:14 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 4
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 4
I 4
D 5
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 5
I 5
.\" Copyright (c) 1983, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 5
.\"
.\" %sccs.include.redist.roff%
E 4
.\"
.\"	%W% (Berkeley) %G%
.\"
D 3
.ds LH "Building Systems With Config
.ds RH "Sample Config Files
.ds CF July 27, 1983
.LP
.nr H1 1
.ds CH "
E 3
I 3
.\".ds RH "Sample Config Files
E 3
.bp
D 3
.ds CH "\(hy \\n(PN \(hy
E 3
.LG
.B
.ce
APPENDIX C. SAMPLE CONFIGURATION FILES
D 3
.sp 2
E 3
I 3
.sp
E 3
.R
.NL
.PP
The following configuration files are developed in section 5;
they are included here for completeness.
.sp 2
.nf
.ta 1.5i 2.5i 4.0i
#
# ANSEL VAX (a picture perfect machine)
#
machine	vax
cpu	VAX780
timezone	8 dst
ident	ANSEL
maxusers	40

config	vmunix	root on hp0
config	hpvmunix	root on hp0 swap on hp0 and hp2
config	genvmunix	swap generic

controller	mba0	at nexus ?
disk	hp0	at mba? disk ?
disk	hp1	at mba? disk ?
controller	mba1	at nexus ?
disk	hp2	at mba? disk ?
disk	hp3	at mba? disk ?
controller	uba0	at nexus ?
controller	tm0	at uba? csr 0172520	vector tmintr
tape	te0	at tm0 drive 0
tape	te1	at tm0 drive 1
device	dh0	at uba? csr 0160020	vector dhrint dhxint
device	dm0	at uba? csr 0170500	vector dmintr
device	dh1	at uba? csr 0160040	vector dhrint dhxint
device	dh2	at uba? csr 0160060	vector dhrint dhxint
.bp
#
# UCBVAX - Gateway to the world
#
machine	vax
cpu	"VAX780"
cpu	"VAX750"
ident	UCBVAX
timezone	8 dst
maxusers	32
options	INET
I 3
options	NS
E 3

config	vmunix	root on hp swap on hp and rk0 and rk1
config	upvmunix	root on up
config	hkvmunix	root on hk swap on rk0 and rk1

controller	mba0	at nexus ?
controller	uba0	at nexus ?
disk	hp0	at mba? drive 0
disk	hp1	at mba? drive 1
controller	sc0	at uba? csr 0176700	vector upintr
disk	up0	at sc0 drive 0
disk	up1	at sc0 drive 1
controller	hk0	at uba? csr 0177440	vector rkintr
disk	rk0	at hk0 drive 0
disk	rk1	at hk0 drive 1
D 3
pseudo-device	inet
E 3
pseudo-device	pty
D 3
# software loopback device for testing
E 3
pseudo-device	loop
pseudo-device	imp
device	acc0	at uba? csr 0167600	vector accrint accxint
pseudo-device	ether
device	ec0	at uba? csr 0164330	vector ecrint eccollide ecxint
device	il0	at uba? csr 0164000	vector ilrint ilcint
E 1
