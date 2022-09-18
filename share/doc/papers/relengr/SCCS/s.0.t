h23162
s 00007/00001/00058
d D 5.1 91/04/17 09:26:49 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00002/00057
d D 1.4 89/02/24 17:35:13 karels 4 3
c minor changes
e
s 00007/00002/00052
d D 1.3 89/02/23 23:27:06 mckusick 3 2
c editing pass after Keith
e
s 00014/00007/00040
d D 1.2 89/02/19 15:56:01 mckusick 2 1
c first pass at editing
e
s 00047/00000/00000
d D 1.1 89/02/18 19:24:02 mckusick 1 0
c date and time created 89/02/18 19:24:02 by mckusick
e
u
U
t
T
I 1
D 5
.\"	%W%	(Copyright 1989 M. K. McKusick)	%E%
E 5
I 5
.\" Copyright (c) 1989 The Regents of the University of California.
.\" All rights reserved.
.\"
.\" %sccs.include.redist.man%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 5
.rm CM
I 3
.nr PO 1.25i
.ds CH "
.ds CF "%
E 3
.nr Fn 0 1
.ds b3 4.3\s-1BSD\s+1
.de KI
.ds Lb "Fig. \\n+(Fn
.KF
.ce 1
Figure \\n(Fn - \\$1.
..
.de SM
D 2
\\s-1\\$1\\s+1
E 2
I 2
\\s-1\\$1\\s+1\\$2
E 2
..
.de NM
\&\fI\\$1\fP\\$2
..
.de RN
\&\fI\\$1\fP\^(\^)\\$2
..
.de PN
\&\fB\\$1\fP\\$2
..
.TL
D 4
The Release Engineering of 4.3BSD
E 4
I 4
The Release Engineering of 4.3\s-1BSD\s0
E 4
.AU
Marshall Kirk McKusick
.AU
Michael J. Karels
I 3
.AU
Keith Bostic
E 3
.AI
Computer Systems Research Group
Computer Science Division
Department of Electrical Engineering and Computer Science
University of California, Berkeley
Berkeley, California  94720
.AB
D 2
This paper gives a brief overview of the release engineering
techniques used during the release of the 4.3BSD UNIX\(dg
E 2
I 2
D 3
This paper describes the approach used by a small group of people
E 3
I 3
This paper describes an approach used by a small group of people
E 3
to develop and integrate a large software system.
It details the development and release engineering strategy
D 3
used during the preparation of the 4.3BSD UNIX\(dg
E 3
I 3
D 4
used during the preparation of the 4.3BSD version of the UNIX\(dg
E 4
I 4
used during the preparation of the \*(b3 version of the UNIX\(dg
E 4
E 3
E 2
.FS
\(dgUNIX is a registered trademark of AT&T in the US and other countries.
.FE
operating system.
D 2
It describes the approach that a small group of people can
use to develop and integrate a large software system.
It then describes the three step methodology used to
engineer a clean, correct, and coherent release.
E 2
I 2
Each release cycle is divided into an initial development phase
followed by a release engineering phase.
The release engineering of the distribution is done in three steps.
The first step has an informal control policy for tracking modifications;
it results in an alpha distribution.
The second step has more rigid change mechanisms in place;
it results in a beta release.
During the final step changes are tracked very closely;
the result is the final distribution.
E 2
.AE
.LP
E 1
