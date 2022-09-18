h59009
s 00002/00004/00101
d D 8.2 94/05/14 18:34:44 mckusick 18 17
c cleanup for Usenix manuals
e
s 00000/00000/00105
d D 8.1 93/07/27 18:59:05 mckusick 17 16
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00000/00094
d D 6.9 93/07/27 17:55:49 mckusick 16 15
c add .Sh macro to generate table of contents
e
s 00003/00000/00091
d D 6.8 93/07/26 16:31:17 mckusick 15 14
c add blocksize macros
e
s 00007/00004/00084
d D 6.7 93/07/20 12:16:44 mckusick 14 13
c expand abstract to describe new areas
e
s 00008/00005/00080
d D 6.6 93/07/15 17:02:18 hibler 13 12
c correct hibler affiliation, get rid of .IR defn
e
s 00004/00004/00081
d D 6.5 93/07/12 21:47:09 mckusick 12 11
c get rid of last vestiges on Ux macro
e
s 00004/00008/00081
d D 6.4 93/07/12 20:08:35 mckusick 11 10
c number footnotes
e
s 00002/00002/00087
d D 6.3 93/07/09 20:47:42 mckusick 10 9
c typesetting nits
e
s 00015/00000/00074
d D 6.2 93/07/08 22:19:06 hibler 9 8
c add some more special macros
e
s 00021/00024/00053
d D 6.1 93/07/08 00:30:09 mckusick 8 6
c first pass at getting updated for 4.4BSD
e
s 00002/00002/00075
d R 8.1 93/06/08 13:57:47 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00076
d D 1.6 91/05/07 22:43:10 bostic 6 5
c new copyright; att/bsd/shared
e
s 00021/00011/00066
d D 1.5 91/05/06 17:48:47 karels 5 4
c add hcx-9, updates (still only 4.3-tahoe vintage)
e
s 00014/00003/00063
d D 1.4 89/03/07 13:52:08 bostic 4 3
c add Berkeley copyright, networking release
e
s 00001/00001/00065
d D 1.3 88/07/17 09:36:42 karels 3 2
c add keywords
e
s 00019/00013/00047
d D 1.2 88/07/17 09:31:47 karels 2 1
c karels, bostic editing
e
s 00060/00000/00000
d D 1.1 88/06/13 10:48:15 bostic 1 0
c date and time created 88/06/13 10:48:15 by bostic
e
u
U
t
T
I 1
D 2
.\" Copyright (c) 1980 Regents of the University of California.
E 2
I 2
D 4
.\" Copyright (c) 1988 Regents of the University of California.
E 2
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 4
I 4
D 8
.\" Copyright (c) 1988 The Regents of the University of California.
E 8
I 8
.\" Copyright (c) 1988, 1993 The Regents of the University of California.
E 8
.\" All rights reserved.
.\"
D 6
.\" Redistribution and use in source and binary forms are permitted
.\" provided that the above copyright notice and this paragraph are
.\" duplicated in all such forms and that any documentation,
.\" advertising materials, and other materials related to such
.\" distribution and use acknowledge that the software was developed
.\" by the University of California, Berkeley.  The name of the
.\" University may not be used to endorse or promote products derived
.\" from this software without specific prior written permission.
.\" THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
.\" IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
.\" WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
.\" %sccs.include.redist.roff%
E 6
E 4
.\"
D 3
.\"	@(#)0.t	6.1 (Berkeley) 5/13/86
E 3
I 3
.\"	%W% (Berkeley) %G%
E 3
.\"
D 2
.EH 'SMM:1-%''Installing and Operating 4.3BSD on the Tahoe'
.OH 'Installing and Operating 4.3BSD on the Tahoe''SMM:1-%'
.ds 4B 4.3BSD
E 2
I 2
D 5
.EH 'SMM:1-%''Installing and Operating 4.3BSD-tahoe UNIX on the Tahoe'
.OH 'Installing and Operating 4.3BSD-tahoe UNIX on the Tahoe''SMM:1-%'
.ds 4B 4.3BSD-tahoe
E 5
D 8
.nr Th 1		\" Tahoe version
D 5
.ds Mc Tahoe
E 5
I 5
.ds Th Tahoe
E 8
.ds Ux \s-1UNIX\s0
.ds Bs \s-1BSD\s0
.\" Current version:
D 8
.ds 4B 4.3\*(Bs-tahoe
.\" machine:
.ds Mc \*(Th
E 5
.ds mC tahoe
.ds Dk dk
.ds Dn Eagle
E 8
I 8
.ds 4B 4.4\*(Bs
.ds Ps 4.3\*(Bs
.\" tape and disk naming
.ds Mt mt
.ds Dk sd
.ds Dn disk
E 8
.ds Pa c
I 15
.\" block size used on the tape
.ds Bb 10240
.ds Bz 20
E 15
D 5
.ds Ps 4.3BSD-beta
E 5
I 5
D 8
.ds Ps 4.3\*(Bs-beta
.ds Vs \s-1VERSA\s0bus
.ds Vm "\s-1VME\s0 bus
E 8
I 8
.\" document date
.ds Dy %Q%
E 8
.de Sm
\s-1\\$1\s0\\$2
..
I 9
.de Pn		\" pathname
\f(CW\\$1\fP\\$2
..
.de Li		\" literal
\f(CW\\$1\fP\\$2
..
.de I		\" italicize first arg
\fI\\$1\fP\^\\$2
..
.de Xr		\" manual reference
\fI\\$1\fP\^\\$2
..
.de Fn		\" function
\fI\\$1\fP\^()\\$2
..
E 9
E 5
E 2
.bd S B 3
I 5
D 8
.EH 'SMM:1-%''Installing and Operating \*(4B \*(Ux on the \*(Th'
.OH 'Installing and Operating \*(4B \*(Ux on the \*(Th''SMM:1-%'
E 8
I 8
D 12
.EH 'SMM:1-%''Installing and Operating \*(4B \*(Ux'
.OH 'Installing and Operating \*(4B \*(Ux''SMM:1-%'
E 12
I 12
.EH 'SMM:1-%''Installing and Operating \*(4B UNIX'
.OH 'Installing and Operating \*(4B UNIX''SMM:1-%'
I 16
.de Sh
.NH \\$1
\\$2
.nr PD .1v
.XS \\n%
.ta 0.6i
\\*(SN	\\$2
.XE
.nr PD .3v
..
E 16
E 12
E 8
E 5
.TL
D 2
Installing and Operating \*(4B on the Tahoe
E 2
I 2
D 5
Installing and Operating \*(4B UNIX* on the Tahoe
E 5
I 5
D 8
Installing and Operating \*(4B \*(Ux* on the \*(Th
E 8
I 8
Installing and Operating \*(4B UNIX
E 8
E 5
E 2
.br
D 2
April 1, 1986
E 2
I 2
D 8
July 14, 1988
E 8
I 8
\*(Dy
E 8
E 2
.AU
D 8
Samuel J. Leffler
E 8
I 8
Marshall Kirk McKusick
E 8
.AU
I 2
Keith Bostic
.AU
I 8
D 13
Mike Hibler
.AU
E 13
E 8
E 2
Michael J. Karels
.AU
D 8
Marshall Kirk McKusick
E 8
I 8
Samuel J. Leffler
E 8
.AI
Computer Systems Research Group
Department of Electrical Engineering and Computer Science
University of California, Berkeley
Berkeley, California  94720
(415) 642-7780
D 13
.de IR
\\fI\\$1\|\\fP\\$2
..
E 13
I 13
.AU
Mike Hibler
.AI
Center for Software Science
Department of Computer Science
University of Utah
Salt Lake City, Utah  84112
(801) 581-5017
E 13
D 11
.de UX
D 5
UNIX\\$1
E 5
I 5
\*(Ux\\$1
E 5
..
E 11
.AB
.PP
D 11
.FS
D 2
* Tahoe is a trademark of Computer Consoles Incorporated.
E 2
I 2
D 5
*\s-2UNIX\s0 is a register trademark of AT&T in the USA and other countries.
E 5
I 5
D 8
*\*(Ux is a register trademark of AT&T in the USA and other countries.
E 8
I 8
*\*(Ux is a register trademark of USL in the USA and some other countries.
E 8
E 5
E 2
.FE
E 11
D 2
.FS
** \s-2UNIX\s0 is a Trademark of Bell Laboratories.
.FE
E 2
This document contains instructions for the
installation and operation of the
D 11
\*(4B release of
D 2
.UX **
E 2
I 2
.UX
E 11
I 11
D 18
\*(4B release of UNIX\**
E 18
I 18
\*(4B release of UNIX
E 18
E 11
E 2
D 8
as distributed by The University of California at Berkeley
D 2
for the Tahoe* (CCI Power 6/32 and similar machines).
E 2
I 2
D 5
for the Tahoe (CCI Power 6/32 and similar machines).
E 5
I 5
for the \*(Th (CCI Power 6/32 and similar machines).
E 8
I 8
as distributed by The University of California at Berkeley.
I 11
D 18
.FS
UNIX is a registered trademark of USL in the USA and some other countries.
.FE
E 18
E 11
E 8
E 5
E 2
.PP
D 2
It discusses procedures for installing UNIX on a new Tahoe,
E 2
I 2
D 5
It discusses procedures for installing UNIX on a new machine,
E 2
and for upgrading an existing 4.2BSD Tahoe UNIX system to the new release.
E 5
I 5
D 12
It discusses procedures for installing \*(Ux on a new machine,
D 8
and for upgrading an existing 4.2\*(Bs \*(Th \*(Ux system to the new release.
E 8
I 8
and for upgrading an existing \*(Ps \*(Ux system to the new release.
E 12
I 12
It discusses procedures for installing UNIX on a new machine,
and for upgrading an existing \*(Ps UNIX system to the new release.
E 12
E 8
E 5
D 10
An explanation of how to lay out file systems on available disks,
E 10
I 10
D 14
An explanation of how to lay out filesystems on available disks,
E 10
how to set up terminal lines and user accounts,
E 14
I 14
An explanation of how to lay out filesystems on available disks
and the space requirements for various parts of the system are given.
A brief overview of the major changes to
the system between \*(Ps and \*(4B are outlined.
An explanation of how to set up terminal lines and user accounts,
E 14
and how to do system-specific tailoring is provided.
D 14
A description of how to install and configure the networking
facilities included with \*(4B is included.
E 14
I 14
A description of how to install and configure the \*(4B networking
facilities is included.
E 14
Finally, the document details system operation procedures:
D 8
shutdown and startup,
hardware error reporting and diagnosis, file system backup procedures,
E 8
I 8
D 10
shutdown and startup, file system backup procedures,
E 10
I 10
shutdown and startup, filesystem backup procedures,
E 10
E 8
resource control, performance monitoring, and procedures for recompiling
and reinstalling system software.
.AE
I 18
.LP
E 18
I 16
.bp +3
E 16
E 1
