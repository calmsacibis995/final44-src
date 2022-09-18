h00298
s 00005/00005/00025
d D 8.3 94/05/26 22:30:48 bostic 7 6
c cleanups and edits for accuracy
e
s 00010/00010/00020
d D 8.2 94/05/16 10:09:31 mckusick 6 5
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00028
d D 8.1 93/06/08 18:05:00 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00026
d D 6.3 91/04/17 10:01:51 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00001/00028
d D 6.2 86/05/12 01:00:37 karels 3 2
c update, correct, rephrase and re-propose
e
s 00000/00001/00029
d D 6.1 86/05/08 12:26:21 mckusick 2 1
c format updates for 4.3BSD
e
s 00030/00000/00000
d D 5.1 86/05/08 00:02:15 mckusick 1 0
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
D 7
.\" Copyright (c) 1983, 1993
E 7
I 7
.\" Copyright (c) 1983, 1993, 1994
E 7
.\"	The Regents of the University of California.  All rights reserved.
E 5
.\"
.\" %sccs.include.redist.roff%
E 4
.\"
.\"	%W% (Berkeley) %G%
.\"
D 2
.\" %M% %I% %E%
E 2
D 6
.ds ss 1
.sh "Kernel primitives
E 6
I 6
.Sh 1 "Kernel primitives
E 6
.PP
D 6
The facilities available to a UNIX user process are logically
E 6
I 6
The facilities available to a user process are logically
E 6
divided into two parts: kernel facilities directly implemented by
D 6
UNIX code running in the operating system, and system facilities
E 6
I 6
code running in the operating system, and system facilities
E 6
implemented either by the system, or in cooperation with a
D 6
\fIserver process\fP.  These kernel facilities are described in
this section 1.
E 6
I 6
D 7
\fIserver process\fP.  These kernel facilities are described
in this, section
E 7
I 7
\fIserver process\fP.
The kernel facilities are described in section
E 7
.Xr 1 .
E 6
.PP
The facilities implemented in the kernel are those which define the
D 3
\fIUNIX virtual machine\fP which each process runs in.
E 3
I 3
D 6
\fIUNIX virtual machine\fP in which each process runs.
E 6
I 6
\fI4.4BSD virtual machine\fP in which each process runs.
E 6
E 3
Like many real machines, this virtual machine has memory management hardware,
D 6
an interrupt facility, timers and counters.  The UNIX
E 6
I 6
an interrupt facility, timers and counters.  The 4.4BSD
E 6
D 7
virtual machine also allows access to files and other objects through a set of
E 7
I 7
virtual machine allows access to files and other objects through a set of
E 7
\fIdescriptors\fP.  Each descriptor resembles a device controller,
and supports a set of operations.  Like devices on real machines, some
of which are internal to the machine and some of which are external,
parts of the descriptor machinery are built-in to the operating system, while
D 7
other parts are often implemented in server processes on other machines.
E 7
I 7
other parts are implemented in server processes on other machines.
E 7
The facilities provided through the descriptor machinery are described in
D 6
section 2.
.ds ss 2
E 6
I 6
section
.Xr 2 .
E 6
E 1
