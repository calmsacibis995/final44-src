h25392
s 00000/00000/00069
d D 8.1 93/06/08 18:02:15 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00000/00067
d D 6.2 91/04/17 10:43:39 bostic 4 3
c new copyright; att/bsd/shared
e
s 00000/00000/00067
d D 6.1 86/04/24 16:31:37 cuccia 3 2
c Mark Seiden edits for 4.3BSD release
e
s 00000/00000/00067
d D 5.1 86/04/24 16:31:24 cuccia 2 1
c document distributed with 4.2BSD
e
s 00067/00000/00000
d D 4.1 86/04/24 16:31:12 cuccia 1 0
c document distributed with 4.1BSD
e
u
U
t
T
I 4
.\" %sccs.include.proprietary.roff%
.\"
E 4
I 1
.\"	%W% (Berkeley) %G%
.\"
.SH
IX. STATISTICS
.PP
The following numbers
are presented to suggest the scale of the Research
.UX
operation.
Those of our users
not involved in document preparation
tend to use the system for
program development, especially language work.
There are few important
``applications'' programs.
.PP
Overall, we have today:
.PP
.SP .5
.TS
center;
r5 l.
125	user population
33	maximum simultaneous users
1,630	directories
28,300	files
301,700	512-byte secondary storage blocks used
.TE
.SP .5
There is a ``background'' process that
runs at the lowest possible priority; it is used
to soak up any idle \*sCPU\*n time.
It has been used to produce a million-digit
approximation to the constant \fIe\fR,
and other semi-infinite problems.
Not counting this background work, we average daily:
.SP .5
.TS
center;
r 5 l.
13,500	commands
9.6	\*sCPU\*n hours
230	connect hours
62	different users
240	log-ins
.TE
.SP .5
.SH
X. ACKNOWLEDGMENTS
.PP
The contributors to
.UX
are, in the traditional but here especially apposite
phrase, too numerous to mention.
Certainly, collective salutes are due to our colleagues in the
Computing Science Research Center.
R. H. Canaday contributed much to the basic design of the
file system.
We are particularly appreciative
of the inventiveness,
thoughtful criticism,
and constant support of
R. Morris, M. D. McIlroy,
and J. F. Ossanna.
.[
$LIST$
.]
E 1
