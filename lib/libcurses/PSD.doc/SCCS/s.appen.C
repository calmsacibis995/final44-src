h37433
s 00002/00002/00099
d D 8.1 93/06/08 18:33:11 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00099
d D 6.5 93/06/07 00:17:15 bostic 9 6
c new doc.mk; document numbering changes for 4.4BSD
e
s 00002/00002/00099
d R 8.2 93/06/05 15:59:25 bostic 8 7
c new doc.mk; document numbering changes for 4.4BSD
e
s 00002/00002/00099
d R 8.1 93/06/04 16:43:59 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00031/00014/00070
d D 6.4 92/12/30 15:24:02 elan 6 5
c Added examples and changed to be appendix A so appendix C is no 
c longer in use.
e
s 00001/00011/00083
d D 6.3 91/04/17 10:37:44 bostic 5 4
c new copyright; att/bsd/shared
e
s 00014/00003/00080
d D 6.2 89/03/17 11:31:54 bostic 4 3
c add Berkeley specific copyright notices
e
s 00004/00003/00079
d D 6.1 86/04/23 23:47:42 mckusick 3 2
c Ken Arnold edits for document distributed with 4.3BSD
e
s 00000/00000/00082
d D 5.1 86/04/23 23:47:37 mckusick 2 1
c document distributed with 4.2BSD
e
s 00082/00000/00000
d D 4.1 86/04/23 23:47:33 mckusick 1 0
c document distributed with 4.1BSD
e
u
U
t
T
I 1
D 4
.\" Copyright (c) 1980 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 4
I 4
D 10
.\" Copyright (c) 1980 The Regents of the University of California.
.\" All rights reserved.
E 10
I 10
.\" Copyright (c) 1980, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 10
.\"
D 5
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
E 5
I 5
.\" %sccs.include.redist.roff%
E 5
E 4
.\"
.\"	%W% (Berkeley) %G%
.\"
D 3
.ie t .he ''\fBAppendix C\fR''
E 3
I 3
D 6
.ie t .oh '\*(Ln Appendix C''PS1:18-%'
.eh 'PS1:18-%''\*(Ln Appendix C'
E 3
.el .he ''\fIAppendix C\fR''
E 6
I 6
D 9
.ie t .oh '\*(Ln Appendix A''PS1:18-%'
.eh 'PS1:18-%''\*(Ln Appendix A'
E 9
I 9
.ie t .oh '\*(Ln Appendix A''PS1:19-%'
.eh 'PS1:19-%''\*(Ln Appendix A'
E 9
.el .he ''\fIAppendix A\fR''
E 6
.bp
.(x
.ti 0
D 6
.b "Appendix C"
E 6
I 6
.b "Appendix A"
E 6
.)x
.sh 1 "Examples" 1
.pp
Here we present a few examples
of how to use the package.
They attempt to be representative,
D 6
though not comprehensive.
.sh 1 "Screen Updating"
E 6
I 6
though not comprehensive.  Further examples can be found in the games section
of the source tree and in various utilities that use the screen such as 
.i systat(1) .
.sh 2 "Screen Updating"
E 6
.pp
The following examples are intended to demonstrate
the basic structure of a program
using the screen updating sections of the package.
Several of the programs require calculational sections
which are irrelevant of to the example,
and are therefore usually not included.
It is hoped that the data structure definitions
give enough of an idea to allow understanding
of what the relevant portions do.
D 6
The rest is left as an exercise to the reader,
and will not be on the final.
.sh 2 "Twinkle"
E 6
I 6
.sh 3 "Simple Character Output"
E 6
.pp
I 6
This program demonstrates how to set up a window and output characters to it.
Also, it demonstrates how one might control the output to the window.  If
you run this program, you will get a demonstration of the character output
chracteristics discussed in the above Character Output section.
.(l I
.so t2.gr
.)l
.sh 3 "A Small Screen Manipulator"
.pp
The next example follows the lines of the previous one but extends then to 
demonstrate the various othe uses of the package.  Make sure you understand 
how this program works as it encompasses most of anything you will
need to do with the package.
.(l I
.so t3.gr
.)l
.sh 3 "Twinkle"
.pp
E 6
This is a moderately simple program which prints
D 6
pretty patterns on the screen
that might even hold your interest for 30 seconds or more.
E 6
I 6
patterns on the screen.
E 6
It switches between patterns of asterisks,
putting them on one by one in random order,
and then taking them off in the same fashion.
It is more efficient to write this
using only the motion optimization,
as is demonstrated below.
.(l I
.so twinkle1.gr
.)l
D 6
.sh 2 "Life"
E 6
I 6
.sh 3 "Life"
E 6
.pp
D 3
This program plays the famous computer pattern game of life
E 3
I 3
This program fragment models the famous computer pattern game of life
E 3
(Scientific American, May, 1974).
The calculational routines create a linked list of structures
defining where each piece is.
Nothing here claims to be optimal,
merely demonstrative.
D 3
This program, however,
E 3
I 3
This code, however,
E 3
is a very good place to use the screen updating routines,
as it allows them to worry about what the last position looked like,
so you don't have to.
It also demonstrates some of the input routines.
.(l I
.so life.gr
.)l
D 6
.sh 1 "Motion optimization"
E 6
I 6
.sh 2 "Motion optimization"
E 6
.pp
The following example shows how motion optimization
is written on its own.
Programs which flit from one place to another without
regard for what is already there
usually do not need the overhead of both space and time
associated with screen updating.
They should instead use motion optimization.
D 6
.sh 2 "Twinkle"
E 6
I 6
.sh 3 "Twinkle"
E 6
.pp
The
.b twinkle
program
is a good candidate for simple motion optimization.
Here is how it could be written
(only the routines that have been changed are shown):
.(l
.so twinkle2.gr
.)l
E 1
