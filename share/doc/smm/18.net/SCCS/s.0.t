h27239
s 00002/00002/00153
d D 8.1 93/06/10 17:52:09 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00153
d D 6.8 93/06/10 17:51:53 bostic 10 8
c move 13.net to 18.net
e
s 00002/00002/00153
d R 8.1 93/06/08 16:52:04 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00152
d D 6.7 93/06/06 12:21:15 mckusick 8 7
c crude update for 4.4BSD
e
s 00002/00002/00153
d D 6.6 93/06/05 16:38:04 bostic 7 6
c new doc.mk; document numbering changes for 4.4BSD
e
s 00001/00011/00154
d D 6.5 91/04/17 12:06:06 bostic 6 5
c new copyright; att/bsd/shared
e
s 00014/00003/00151
d D 6.4 89/03/07 10:53:00 bostic 5 4
c install Berkeley specific copyright, for networking release
e
s 00000/00001/00154
d D 6.3 86/06/05 09:51:29 karels 4 3
c formatting glitches
e
s 00004/00005/00151
d D 6.2 86/06/04 23:52:30 karels 3 2
c updates for 4.3
e
s 00045/00048/00111
d D 6.1 86/05/26 13:23:40 mckusick 2 1
c 4.3BSD beta release document
e
s 00159/00000/00000
d D 5.1 86/05/26 13:23:33 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 3
.\" Copyright (c) 1983 Regents of the University of California.
E 3
I 3
D 5
.\" Copyright (c) 1983,1986 Regents of the University of California.
E 3
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 5
I 5
D 11
.\" Copyright (c) 1983, 1986 The Regents of the University of California.
.\" All rights reserved.
E 11
I 11
.\" Copyright (c) 1983, 1986, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 11
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
E 5
.\"
.\"	%W% (Berkeley) %G%
.\"
I 8
.de IR
\fI\\$1\fP\\$2
..
E 8
.if n .ND
.TL
D 2
4.2BSD Networking Implementation Notes
.sp
Revised July, 1983
E 2
I 2
Networking Implementation Notes
.br
D 8
4.3BSD Edition
E 8
I 8
4.4BSD Edition
E 8
E 2
.AU
D 2
Samuel J. Leffler, William N. Joy, Robert S. Fabry
E 2
I 2
Samuel J. Leffler, William N. Joy, Robert S. Fabry, and Michael J. Karels
E 2
.AI
Computer Systems Research Group
Computer Science Division
Department of Electrical Engineering and Computer Science
University of California, Berkeley
Berkeley, CA  94720
D 2

(415) 642-7780
E 2
.AB
.FS
* UNIX is a trademark of Bell Laboratories.
.FE
This report describes the internal structure of the
D 2
networking facilities developed for the 4.2BSD version
E 2
I 2
D 8
networking facilities developed for the 4.3BSD version
E 8
I 8
networking facilities developed for the 4.4BSD version
E 8
E 2
of the UNIX* operating system
for the VAX\(dg.  These facilities
.FS
\(dg DEC, VAX, DECnet, and UNIBUS are trademarks of
Digital Equipment Corporation.
.FE
are based on several central abstractions which
structure the external (user) view of network communication
as well as the internal (system) implementation.
.PP
D 2
The report documents the internal structure of the
networking system.  The
``4.2BSD System Manual'' provides a
description of the user interface to the networking
facilities.
E 2
I 2
The report documents the internal structure of the networking system.
D 8
The ``Berkeley Software Architecture Manual, 4.3BSD Edition'' (PS1:6)
E 8
I 8
The ``Berkeley Software Architecture Manual, 4.4BSD Edition'' (PSD:5)
E 8
provides a description of the user interface to the networking facilities.
.sp
.LP
Revised %Q%
E 2
.AE
.LP
D 2
.de PT
.lt \\n(LLu
.pc %
.nr PN \\n%
.tl '\\*(LH'\\*(CH'\\*(RH'
.lt \\n(.lu
..
.af PN i
E 2
I 2
.\".de PT
.\".lt \\n(LLu
.\".pc %
.\".nr PN \\n%
.\".tl '\\*(LH'\\*(CH'\\*(RH'
.\".lt \\n(.lu
.\"..
E 2
D 3
.ds LH Networking Implementation
.ds RH Contents
E 3
I 3
.\".ds RH Contents
E 3
D 2
.bp 1
.if t .ds LF CSRG TR/6
.if t .ds RF Leffler, et. al.
E 2
I 2
D 7
.OH 'Networking Implementation Notes''SMM:15-%'
.EH 'SMM:15-%''Networking Implementation Notes'
E 7
I 7
D 10
.OH 'Networking Implementation Notes''SMM:13-%'
.EH 'SMM:13-%''Networking Implementation Notes'
E 10
I 10
.OH 'Networking Implementation Notes''SMM:18-%'
.EH 'SMM:18-%''Networking Implementation Notes'
E 10
E 7
.bp
E 2
.ce
.B "TABLE OF CONTENTS"
.LP
.sp 1
.nf
.B "1.  Introduction"
.LP
.sp .5v
.nf
.B "2.  Overview"
.LP
.sp .5v
.nf
.B "3.  Goals
.LP
.sp .5v
.nf
.B "4.  Internal address representation"
.LP
.sp .5v
.nf
.B "5.  Memory management"
.LP
.sp .5v
.nf
.B "6.  Internal layering
D 2
\0.1.    Socket layer
\0.1.1.    Socket state
\0.1.2.    Socket data queues
\0.1.3.    Socket connection queueing
\0.2.    Protocol layer(s)
\0.3.    Network-interface layer
\0.3.1.    UNIBUS interfaces
E 2
I 2
6.1.    Socket layer
6.1.1.    Socket state
6.1.2.    Socket data queues
D 3
6.1.3.    Socket connection queueing
E 3
I 3
6.1.3.    Socket connection queuing
E 3
6.2.    Protocol layer(s)
6.3.    Network-interface layer
6.3.1.    UNIBUS interfaces
E 2
.LP
.sp .5v
.nf
.B "7.  Socket/protocol interface"
.LP
.sp .5v
.nf
.B "8.  Protocol/protocol interface"
D 2
\0.1.     pr_output
\0.2.     pr_input
\0.3.     pr_ctlinput
\0.4.     pr_ctloutput
E 2
I 2
8.1.     pr_output
8.2.     pr_input
8.3.     pr_ctlinput
8.4.     pr_ctloutput
E 2
.LP
.sp .5v
.nf
.B "9.  Protocol/network-interface interface"
D 2
\0.1.     Packet transmission
\0.2.     Packet reception
E 2
I 2
9.1.     Packet transmission
9.2.     Packet reception
E 2
.LP
.sp .5v
.nf
.B "10. Gateways and routing issues
D 2
\0.1.     Routing tables
\0.2.     Routing table interface
\0.3.     User level routing policies
E 2
I 2
10.1.     Routing tables
10.2.     Routing table interface
10.3.     User level routing policies
E 2
.LP
.sp .5v
.nf
.B "11. Raw sockets"
D 2
\0.1.     Control blocks
\0.2.     Input processing
\0.3.     Output processing
E 2
I 2
11.1.     Control blocks
11.2.     Input processing
11.3.     Output processing
E 2
.LP
.sp .5v
.nf
.B "12. Buffering and congestion control"
D 2
\0.1.     Memory management
\0.2.     Protocol buffering policies
\0.3.     Queue limiting
\0.4.     Packet forwarding
E 2
I 2
12.1.     Memory management
12.2.     Protocol buffering policies
12.3.     Queue limiting
12.4.     Packet forwarding
E 2
.LP
.sp .5v
.nf
.B "13. Out of band data"
.LP
.sp .5v
.nf
.B "14. Trailer protocols"
.LP
.sp .5v
.nf
.B Acknowledgements
.LP
.sp .5v
.nf
.B References
D 3
.ds RH Introduction
E 3
I 3
D 4
.\".ds RH Introduction
E 4
E 3
D 2
.af PN 1
.bp 1
E 2
I 2
.bp
E 2
.de _d
.if t .ta .6i 2.1i 2.6i
.\" 2.94 went to 2.6, 3.64 to 3.30
.if n .ta .84i 2.6i 3.30i
..
.de _f
.if t .ta .5i 1.25i 2.5i
.\" 3.5i went to 3.8i
.if n .ta .7i 1.75i 3.8i
..
E 1
