h55148
s 00002/00002/00118
d D 8.1 93/06/08 11:27:32 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00000/00112
d D 5.2 91/04/20 15:30:52 bostic 2 1
c new copyright; att/bsd/shared
e
s 00112/00000/00000
d D 5.1 90/06/02 18:36:39 karels 1 0
c from 4.1BSD, dated Feb 13, 1979
e
u
U
t
T
I 2
D 3
.\" Copyright (c) 1979 The Regents of the University of California.
.\" All rights reserved.
E 3
I 3
.\" Copyright (c) 1979, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 3
.\"
.\" %sccs.include.proprietary.roff%
.\"
.\"	%W% (Berkeley) %G%
.\"

E 2
I 1
.de HD
.ps 10
.ft 1
.if t .tl '\(rn'''
.if t 'sp  \\n(m1-1
.if n 'sp \\n(m1
.if e .1e
.if o .1o
.ps
.ft
'sp \\n(m2
.if \\n(:n .nm 1 1 2
.ns
..
.wh 0 HD
.de FT
'sp \\n(m3
.ps 10
.ft 1
.if e .2e
.if o .2o
.ps
.ft
'bp
..
.wh -1i FT
.de m1
.nr m1 \\$1
..
.de m2
.nr m2 \\$1
..
.de m3
.nr m3 \\$1
.ch FT -\\n(m3-\\n(m4
..
.de m4
.nr m4 \\$1
.ch FT -\\n(m3-\\n(m4
..
.m1 3
.m2 2
.m3 2
.m4 3
.de he
.de 1e
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
.de 1o
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
..
.de fo
.de 2e
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
.de 2o
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
..
.de eh
.de 1e
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
..
.de oh
.de 1o
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
..
.de ef
.de 2e
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
..
.de of
.de 2o
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
..
.he ''''
.fo ''''
.de bl
.rs
.sp \\$1
..
.de n1
.n2 \\$1
.nr :n 0
.if \\n(.$ .nr :n 1
..
.de n2
.if \\n(.$ .if \\$1=0 .nm
.if \\n(.$ .if !\\$1=0 .nm \\$1 1 2
.if !\\n(.$ .nm 1 1 2
..
.rn ds :d
.de ds
.if \\n(.$ .:d \\$1 "\\$2\\$3\\$4\\$5\\$6\\$7\\$8\\$9
.if !\\n(.$ .ls 2
..
.de ss
.ls 1
..
.de EQ
.nf
.sp
..
.de EN
.sp
.fi
..
E 1
