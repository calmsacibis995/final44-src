h52541
s 00002/00002/00088
d D 8.1 93/06/08 14:07:30 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00089
d D 6.6 91/04/17 11:38:24 bostic 7 6
c new copyright; att/bsd/shared
e
s 00014/00003/00086
d D 6.5 89/03/07 14:33:10 bostic 6 5
c add Berkeley specific copyright, networking release
e
s 00003/00002/00086
d D 6.4 86/04/28 19:08:39 bloom 5 4
c more comments about syslog, phrasing cleanup
e
s 00004/00004/00084
d D 6.3 86/04/17 19:54:02 bloom 4 3
c clean up diction
e
s 00001/00001/00087
d D 6.2 86/04/17 17:59:15 bloom 3 2
c change filter name for consistency
e
s 00000/00000/00088
d D 6.1 86/04/17 16:45:53 mckusick 2 1
c 4.3BSD beta release document
e
s 00088/00000/00000
d D 5.1 86/04/17 16:45:43 mckusick 1 0
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
Output filter specifications
.PP
D 5
The filters supplied with 4.2BSD
E 5
I 5
The filters supplied with 4.3BSD
E 5
handle printing and accounting for most common
line printers, the Benson-Varian, the wide (36") and
narrow (11") Versatec printer/plotters. For other devices or accounting
methods, it may be necessary to create a new filter.
.PP
Filters are spawned by \fIlpd\fP
with their standard input the data to be printed, and standard output
the printer.  The standard error is attached to the
.B lf
D 5
file for logging errors.  A filter must return a 0 exit
E 5
I 5
file for logging errors or \fIsyslogd\fP may be used for logging errors.
A filter must return a 0 exit
E 5
code if there were no errors, 1 if the job should be reprinted,
and 2 if the job should be thrown away.
When \fIlprm\fP
sends a kill signal to the \fIlpd\fP process controlling
printing, it sends a SIGINT signal 
to all filters and descendents of filters.
D 4
This signal can be trapped by filters which need
to perform cleanup operations such as
E 4
I 4
This signal can be trapped by filters that need
to do cleanup operations such as
E 4
deleting temporary files.
.PP
Arguments passed to a filter depend on its type.
The
.B of
filter is called with the following arguments.
.DS
D 3
\fIofiler\fP \fB\-w\fPwidth \fB\-l\fPlength
E 3
I 3
\fIfilter\fP \fB\-w\fPwidth \fB\-l\fPlength
E 3
.DE
The \fIwidth\fP and \fIlength\fP values come from the
.B pw
and
.B pl
entries in the printcap database.
The
.B if
filter is passed the following parameters.
.DS
\fIfilter\fP [\|\fB\-c\fP\|] \fB\-w\fPwidth \fB\-l\fPlength \fB\-i\fPindent \fB\-n\fP login \fB\-h\fP host accounting_file
.DE
The
.B \-c
flag is optional, and only supplied when control characters
D 4
are to be passed uninterpreted to the printer (when the
E 4
I 4
are to be passed uninterpreted to the printer (when using the
E 4
.B \-l
option of
.I lpr
D 4
is used to print the file).
E 4
I 4
to print the file).
E 4
The
.B \-w
and
.B \-l
parameters are the same as for the
.B of
filter.
The
.B \-n
and
.B \-h
parameters specify the login name and host name of the job owner.
The last argument is the name of the accounting file from
.IR printcap .
.PP
All other filters are called with the following arguments:
.DS
\fIfilter\fP \fB\-x\fPwidth \fB\-y\fPlength \fB\-n\fP login \fB\-h\fP host accounting_file
.DE
The
.B \-x
and
.B \-y
options specify the horizontal and vertical page
size in pixels (from the
.B px
and
.B py
entries in the printcap file).
The rest of the arguments are the same as for the
.B if
filter.
E 1
