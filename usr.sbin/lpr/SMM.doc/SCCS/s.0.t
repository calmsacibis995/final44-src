h04269
s 00002/00002/00040
d D 8.1 93/06/08 14:07:14 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00040
d D 6.7 93/06/05 16:33:57 bostic 8 7
c new doc.mk; document numbering changes for 4.4BSD
e
s 00001/00011/00041
d D 6.6 91/04/17 11:38:20 bostic 7 6
c new copyright; att/bsd/shared
e
s 00014/00003/00038
d D 6.5 89/03/07 14:33:02 bostic 6 5
c add Berkeley specific copyright, networking release
e
s 00009/00008/00032
d D 6.4 86/05/14 15:09:40 mckusick 5 4
c minor reformating
e
s 00002/00002/00038
d D 6.3 86/04/29 23:57:53 mckusick 4 3
c doc changes to SMM:6
e
s 00009/00005/00031
d D 6.2 86/04/28 19:10:03 bloom 3 2
c add headers, add dynamic date, minor work
e
s 00001/00001/00035
d D 6.1 86/04/17 16:42:59 mckusick 2 1
c 4.3BSD beta release document
e
s 00036/00000/00000
d D 5.1 86/04/17 16:42:38 mckusick 1 0
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
D 9
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 9
I 9
.\" Copyright (c) 1983, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 9
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
I 3
D 4
.EH 'SMM:5-%''4.3BSD Line Printer Spooler Manual'
.OH '4.3BSD Line Printer Spooler Manual''SMM:5-%'
E 4
I 4
D 5
.EH 'SMM:6-%''4.3BSD Line Printer Spooler Manual'
.OH '4.3BSD Line Printer Spooler Manual''SMM:6-%'
E 5
E 4
E 3
.if n .ND
.TL
D 3
4.2BSD Line Printer Spooler Manual
E 3
I 3
4.3BSD Line Printer Spooler Manual
E 3
D 5
.sp
D 2
Revised July 27, 1983
E 2
I 2
D 3
Revised %Q%
E 3
I 3
.de D?
.ie \\n(.$>1 Revised \\$1 \\$2 \\$3
.el DRAFT of \n(mo/\n(dy/\n(yr
..
.D? %Q%
E 5
I 5
D 8
.EH 'SMM:6-%''4.3BSD Line Printer Spooler Manual'
.OH '4.3BSD Line Printer Spooler Manual''SMM:6-%'
E 8
I 8
.EH 'SMM:7-%''4.3BSD Line Printer Spooler Manual'
.OH '4.3BSD Line Printer Spooler Manual''SMM:7-%'
E 8
E 5
E 3
E 2
.AU
Ralph Campbell
.AI
Computer Systems Research Group
Computer Science Division
Department of Electrical Engineering and Computer Science
University of California, Berkeley
Berkeley, CA  94720
D 3

(415) 642-7780
E 3
.AB
.FS
* UNIX is a trademark of Bell Laboratories.
.FE
This document describes the structure and installation procedure
for the line printer spooling system
D 3
developed for the 4.2BSD version
E 3
I 3
developed for the 4.3BSD version
E 3
of the UNIX* operating system.
I 5
.de D?
.ie \\n(.$>1 Revised \\$1 \\$2 \\$3
.el DRAFT of \n(mo/\n(dy/\n(yr
..
.sp 2
.LP
.D? %Q%
E 5
.AE
.de IR
\fI\\$1\fP\\$2
..
.de DT
.TA 8 16 24 32 40 48 56 64 72 80
..
E 1
