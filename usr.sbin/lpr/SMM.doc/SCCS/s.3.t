h54133
s 00002/00002/00045
d D 8.1 93/06/08 14:07:23 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00046
d D 6.6 91/04/17 11:38:22 bostic 7 6
c new copyright; att/bsd/shared
e
s 00014/00003/00043
d D 6.5 89/03/07 14:33:06 bostic 6 5
c add Berkeley specific copyright, networking release
e
s 00001/00001/00045
d D 6.4 86/04/28 19:07:21 bloom 5 4
c use daemon instead of spooling for group name
e
s 00002/00002/00044
d D 6.3 86/04/17 19:53:50 bloom 4 3
c clean up diction
e
s 00008/00008/00038
d D 6.2 86/04/17 17:58:00 bloom 3 2
c expand setuid and setgid, now setgid to daemon
e
s 00002/00002/00044
d D 6.1 86/04/17 16:44:56 mckusick 2 1
c 4.3BSD beta release document
e
s 00046/00000/00000
d D 5.1 86/04/17 16:44:46 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 6
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 6
I 6
D 8
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 8
I 8
.\" Copyright (c) 1983, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 8
.\"
D 7
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
E 7
I 7
.\" %sccs.include.redist.roff%
E 7
E 6
.\"
.\"	%W% (Berkeley) %G%
.\"
.NH 1
Access control
.PP
The printer system maintains protected spooling areas so that
users cannot circumvent printer accounting or
remove files other than their own.
The strategy used to maintain protected
spooling areas is as follows:
.IP \(bu 3
The spooling area is writable only by a \fIdaemon\fP user
D 5
and \fIspooling\fP group.
E 5
I 5
and \fIdaemon\fP group.
E 5
.IP \(bu 3
D 3
The \fIlpr\fP program runs setuid \fIroot\fP and
setgid \fIspooling\fP.  The \fIroot\fP access is used to
E 3
I 3
The \fIlpr\fP program runs set-user-id to \fIroot\fP and
D 4
set-group-id to group \fIdaemon\fP.  The \fIroot\fP access is used to
E 3
read any file required, verifying accessibility
E 4
I 4
set-group-id to group \fIdaemon\fP.  The \fIroot\fP access permits
reading any file required. Accessibility is verified
E 4
with an \fIaccess\fP\|(2) call.  The group ID
is used in setting up proper ownership of files
in the spooling area for \fIlprm\fP.
.IP \(bu 3
Control files in a spooling area are made with \fIdaemon\fP
D 3
ownership and group ownership \fIspooling\fP.  Their mode is 0660.
E 3
I 3
ownership and group ownership \fIdaemon\fP.  Their mode is 0660.
E 3
This insures control files are not modified by a user
and that no user can remove files except through \fIlprm\fP.
.IP \(bu 3
The spooling programs,
D 3
\fIlpd\fP, \fIlpq\fP, and \fIlprm\fP run setuid \fIroot\fP
and setgid \fIspooling\fP to access spool files and printers.
E 3
I 3
\fIlpd\fP, \fIlpq\fP, and \fIlprm\fP run set-user-id to \fIroot\fP
and set-group-id to group \fIdaemon\fP to access spool files and printers.
E 3
.IP \(bu 3
The printer server, \fIlpd\fP,
uses the same verification procedures as \fIrshd\fP\|(8C)
in authenticating remote clients.  The host on which a client
D 2
resides must be present in the file /etc/hosts.equiv, used
to create clusters of machines under a single administration. 
E 2
I 2
resides must be present in the file /etc/hosts.equiv or /etc/hosts.lpd and
the request message must come from a reserved port number.
E 2
.PP
In practice, none of \fIlpd\fP, \fIlpq\fP, or
\fIlprm\fP would have to run as user \fIroot\fP if remote
spooling were not supported.  In previous incarnations of
D 3
the printer system \fIlpd\fP ran setuid \fIdaemon\fP,
setgid \fIspooling\fP, and \fIlpq\fP and \fIlprm\fP ran
setgid \fIspooling\fP.
E 3
I 3
the printer system \fIlpd\fP ran set-user-id to \fIdaemon\fP,
set-group-id to group \fIspooling\fP, and \fIlpq\fP and \fIlprm\fP ran
set-group-id to group \fIspooling\fP.
E 3
E 1
