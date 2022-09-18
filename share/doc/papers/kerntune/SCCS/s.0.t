h63859
s 00008/00001/00095
d D 1.2 90/11/08 20:38:40 mckusick 2 1
c update copyright notice
e
s 00096/00000/00000
d D 1.1 84/05/21 17:58:48 mckusick 1 0
c date and time created 84/05/21 17:58:48 by mckusick
e
u
U
t
T
I 1
D 2
.\"	%W%	(Copyright 1984 M. K. McKusick)	%E%
E 2
I 2
.\" Copyright (c) 1984 M. K. McKusick
.\" Copyright (c) 1984 The Regents of the University of California.
.\" All rights reserved.
.\"
.\" %sccs.include.redist.man%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 2
.EQ
delim $$
.EN
.if n .ND
.TL
Using gprof to Tune the 4.2BSD Kernel
.AU
Marshall Kirk McKusick
.AI
Computer Systems Research Group
Computer Science Division
Department of Electrical Engineering and Computer Science
University of California, Berkeley
Berkeley, California  94720
.AB
This paper describes how the \fIgprof\fP profiler 
accounts for the running time of called routines
in the running time of the routines that call them.
It then explains how to configure a profiling kernel on
the 4.2 Berkeley Software Distribution of 
.UX
for the VAX\(dd
.FS
\(dd VAX is a trademark of Digital Equipment Corporation.
.FE
and discusses tradeoffs in techniques for collecting
profile data.
\fIGprof\fP identifies problems
that severely affects the overall performance of the kernel.
Once a potential problem areas is identified
benchmark programs are devised to highlight the bottleneck.
These benchmarks verify that the problem exist and provide
a metric against which to validate proposed solutions.
Two caches are added to the kernel to alleviate the bottleneck
and \fIgprof\fP is used to validates their effectiveness.
.AE
.LP
.de PT
.lt \\n(LLu
.pc %
.nr PN \\n%
.tl '\\*(LH'\\*(CH'\\*(RH'
.lt \\n(.lu
..
.af PN i
.ds LH 4.2BSD Performance
.ds RH Contents
.bp 1
.if t .ds CF May 21, 1984
.if t .ds LF
.if t .ds RF McKusick
.ce
.B "TABLE OF CONTENTS"
.LP
.sp 1
.nf
.B "1.  Introduction"
.LP
.sp .5v
.nf
.B "2.  The \fIgprof\fP Profiler"
\0.1.    Data Presentation"
\0.1.1.   The Flat Profile
\0.1.2.   The Call Graph Profile
\0.2     Profiling the Kernel
.LP
.sp .5v
.nf
.B "3.  Using \fIgprof\fP to Improve Performance
\0.1.    Using the Profiler
\0.2.    An Example of Tuning
.LP
.sp .5v
.nf
.B "4.  Conclusions"
.LP
.sp .5v
.nf
.B Acknowledgements
.LP
.sp .5v
.nf
.B References
.af PN 1
.bp 1
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
