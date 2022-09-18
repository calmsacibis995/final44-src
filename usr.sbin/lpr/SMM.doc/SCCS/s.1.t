h32881
s 00002/00002/00049
d D 8.1 93/06/08 14:07:17 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00050
d D 6.5 91/04/17 11:38:21 bostic 6 5
c new copyright; att/bsd/shared
e
s 00014/00003/00047
d D 6.4 89/03/07 14:33:03 bostic 5 4
c add Berkeley specific copyright, networking release
e
s 00001/00001/00049
d D 6.3 86/04/28 19:08:32 bloom 4 3
c more comments about syslog, phrasing cleanup
e
s 00004/00004/00046
d D 6.2 86/04/17 19:53:43 bloom 3 2
c clean up diction
e
s 00000/00000/00050
d D 6.1 86/04/17 16:43:52 mckusick 2 1
c 4.3BSD beta release document
e
s 00050/00000/00000
d D 5.1 86/04/17 16:43:41 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 5
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 5
I 5
D 7
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 7
I 7
.\" Copyright (c) 1983, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 7
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
.NH 1
Overview
.PP
The line printer system supports:
.IP \(bu 3
multiple printers,
.IP \(bu 3
multiple spooling queues,
.IP \(bu 3
both local and remote
printers, and
.IP \(bu 3
D 3
printers attached via serial lines which require
E 3
I 3
printers attached via serial lines that require
E 3
line initialization such as the baud rate.
.LP
Raster output devices
such as a Varian or Versatec, and laser printers such as an Imagen,
are also supported by the line printer system.
.PP
The line printer system consists mainly of the
following files and commands:
.DS
.TS
l l.
/etc/printcap	printer configuration and capability data base
/usr/lib/lpd	line printer daemon, does all the real work
/usr/ucb/lpr	program to enter a job in a printer queue
/usr/ucb/lpq	spooling queue examination program
/usr/ucb/lprm	program to delete jobs from a queue
/etc/lpc	program to administer printers and spooling queues
/dev/printer	socket on which lpd listens
.TE
.DE
The file /etc/printcap is a master data base describing line
printers directly attached to a machine and, also, printers
accessible across a network. The manual page entry
.IR printcap (5)
D 3
provides the ultimate definition of
E 3
I 3
provides the authoritative definition of
E 3
the format of this data base, as well as
D 3
indicating default values for important items
E 3
I 3
specifying default values for important items
E 3
such as the directory in which spooling is performed.
D 4
This document highlights the important
E 4
I 4
This document introduces some of the
E 4
D 3
information which may be placed
E 3
I 3
information that may be placed
E 3
.IR printcap .
E 1
