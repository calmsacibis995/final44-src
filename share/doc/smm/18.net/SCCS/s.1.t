h43609
s 00002/00002/00038
d D 8.1 93/06/08 16:52:07 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00038
d D 6.6 93/06/06 12:21:16 mckusick 7 6
c crude update for 4.4BSD
e
s 00001/00011/00039
d D 6.5 91/04/17 12:06:07 bostic 6 5
c new copyright; att/bsd/shared
e
s 00014/00003/00036
d D 6.4 89/03/07 10:53:02 bostic 5 4
c install Berkeley specific copyright, for networking release
e
s 00002/00002/00037
d D 6.3 86/06/05 09:51:35 karels 4 3
c formatting glitches
e
s 00010/00007/00029
d D 6.2 86/06/04 23:52:37 karels 3 2
c updates for 4.3
e
s 00000/00000/00036
d D 6.1 86/05/26 13:23:53 mckusick 2 1
c 4.3BSD beta release document
e
s 00036/00000/00000
d D 5.1 86/05/26 13:23:49 mckusick 1 0
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
D 8
.\" Copyright (c) 1983, 1986 The Regents of the University of California.
.\" All rights reserved.
E 8
I 8
.\" Copyright (c) 1983, 1986, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 8
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
D 3
.ds RH Introduction
E 3
I 3
.\".ds RH Introduction
I 4
.br
.ne 2i
E 4
E 3
.NH
\s+2Introduction\s0
.PP
This report describes the internal structure of
facilities added to the
4.2BSD version of the UNIX operating system for
D 3
the VAX.  The system facilities provide
E 3
I 3
the VAX,
D 7
as modified in the 4.3BSD release.
E 7
I 7
as modified in the 4.4BSD release.
E 7
The system facilities provide
E 3
a uniform user interface to networking
within UNIX.  In addition, the implementation 
introduces a structure for network communications which may be
used by system implementors in adding new networking
facilities.  The internal structure is not visible
to the user, rather it is intended to aid implementors
of communication protocols and network services by
providing a framework which
promotes code sharing and minimizes implementation effort.
.PP
The reader is expected to be familiar with the C programming
D 3
language and system interface, as described in the \fI4.2BSD
System Manual\fP [Joy82a].  Basic understanding of network
E 3
I 3
language and system interface, as described in the
D 7
\fIBerkeley Software Architecture Manual, 4.3BSD Edition\fP [Joy86].
E 7
I 7
\fIBerkeley Software Architecture Manual, 4.4BSD Edition\fP [Joy86].
E 7
Basic understanding of network
E 3
communication concepts is assumed; where required
any additional ideas are introduced.
.PP
The remainder of this document
provides a description of the system internals,
avoiding, when possible, those portions which are utilized only
by the interprocess communication facilities.
D 3
.ds RH Overview
.bp
E 3
I 3
D 4
.\".ds RH Overview
'ne 2i
E 4
E 3
E 1
