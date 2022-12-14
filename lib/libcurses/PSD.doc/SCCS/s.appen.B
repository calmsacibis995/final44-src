h28354
s 00002/00002/00173
d D 8.1 93/06/08 18:33:08 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00173
d D 6.4 93/06/07 00:17:14 bostic 8 5
c new doc.mk; document numbering changes for 4.4BSD
e
s 00002/00002/00173
d R 8.2 93/06/05 15:59:25 bostic 7 6
c new doc.mk; document numbering changes for 4.4BSD
e
s 00002/00002/00173
d R 8.1 93/06/04 16:43:49 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00174
d D 6.3 91/04/17 10:37:44 bostic 5 4
c new copyright; att/bsd/shared
e
s 00014/00003/00171
d D 6.2 89/03/17 11:31:53 bostic 4 3
c add Berkeley specific copyright notices
e
s 00068/00009/00106
d D 6.1 86/04/23 23:47:25 mckusick 3 2
c Ken Arnold edits for document distributed with 4.3BSD
e
s 00000/00000/00115
d D 5.1 86/04/23 23:47:21 mckusick 2 1
c document distributed with 4.2BSD
e
s 00115/00000/00000
d D 4.1 86/04/23 23:47:15 mckusick 1 0
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
D 9
.\" Copyright (c) 1980 The Regents of the University of California.
.\" All rights reserved.
E 9
I 9
.\" Copyright (c) 1980, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 9
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
.ie t .he ''\fBAppendix B\fR''
E 3
I 3
D 8
.ie t .oh '\*(Ln Appendix B''PS1:18-%'
.eh 'PS1:18-%''\*(Ln Appendix B'
E 8
I 8
.ie t .oh '\*(Ln Appendix B''PS1:19-%'
.eh 'PS1:19-%''\*(Ln Appendix B'
E 8
E 3
.el .he ''\fIAppendix B\fR''
.bp
.(x
.ti 0
.b "Appendix B"
.)x
D 3
.sh 1 "The WINDOW structure" 1
E 3
I 3
.nr $1 0
.sh 1 "The WINDOW structure"
E 3
.pp
The WINDOW structure is defined as follows:
.(l I
.so win_st.gr
.)l
.pp
.Vn \*_cury \\*
.(f
\**
All variables not normally accessed directly by the user
are named with an initial
.Bq \*_
to avoid conflicts with the user's variables.
.)f
and
.Vn \*_curx
are the current \*y for the window.
New characters added to the screen
are added at this point.
.Vn \*_maxy
and
.Vn \*_maxx
are the maximum values allowed for
.Vn \*_cury\*,\*_curx ). (
.Vn \*_begy
and
.Vn \*_begx
are the starting \*y on the terminal for the window,
D 3
i.e.,
E 3
I 3
.i i.e. ,
E 3
the window's home.
.Vn \*_cury ,
.Vn \*_curx ,
.Vn \*_maxy ,
and
.Vn \*_maxx
are measured relative to
.Vn \*_begy\*,\*_begx ), (
not the terminal's home.
.pp
.Vn \*_clear
tells if a clear-screen sequence is to be generated
on the next
.Fn refresh
call.
This is only meaningful for screens.
The initial clear-screen for the first
.Fn refresh
call is generated by initially setting clear to be TRUE for
.Vn curscr ,
which always generates a clear-screen if set,
irrelevant of the dimensions of the window involved.
.Vn \*_leave
is TRUE if the current \*y and the cursor
are to be left after the last character changed on the terminal,
or not moved if there is no change.
.Vn \*_scroll
is TRUE
if scrolling is allowed.
.pp
.Vn \*_y
is a pointer to an array of lines which describe the terminal.
Thus:
.(l
\*_y[i]
.)l
.lp
is a pointer to the
.Vn i th
line, and
.(l
\*_y[i][j]
.)l
.lp
is the
.Vn j th
character on the
.Vn i th
line.
D 3
.pp
E 3
.Vn \*_flags
can have one or more values
or'd into it.
D 3
.b \*_SUBWIN
means that the window is a subwindow,
which indicates to
.Fn delwin
that the space for the lines is not to be freed.
E 3
I 3
.pp
For windows that are not subwindows,
.Vn \*_orig
is
NULL .
For subwindows,
it points to the main window
to which the window is subsidiary.
.Vn \*_nextp
is a pointer in a circularly linked list
of all the windows which are subwindows of the same main window,
plus the main window itself.
.pp
.Vn \*_firstch
and
.Vn \*_lastch
are
.Fn malloc ed
arrays which contain the index of the
first and last changed characters
on the line.
.Vn \*_ch\*_off
is the x offset for the window
in the
.Vn \*_firstch
and
.Vn \*_lastch
arrays for this window.
For main windows,
this is always 0;
for subwindows
it is the difference between the starting point of the main window
and that of the subindow,
so that change markers can be set relative to the main window.
This makes these markers global in scope.
.pp
All subwindows share the appropriate portions of
.Vn _y ,
.Vn _firstch ,
.Vn _lastch ,
and
.Vn _insdel
with their main window.
.pp
E 3
.b \*_ENDLINE
says that the end of the line for this window
is also the end of a screen.
.b \*_FULLWIN
says that this window is a screen.
.b \*_SCROLLWIN
indicates that the last character of this screen
is at the lower right-hand corner of the terminal;
.i i.e. ,
if a character was put there,
the terminal would scroll.
I 3
.b \*_FULLLINE
says that the width of a line is the same as the width of the terminal.
If
.b \*_FLUSH
is set,
it says that
.Fn fflush "" "" stdout
should be called at the end of each
.Fn refresh
E 3
.b \*_STANDOUT
says that all characters added to the screen
are in standout mode.
I 3
.b \*_INSDEL
is reserved for future use,
and is set by
.Fn idlok .
.Vn \*_firstch
is set to
.b \*_NOCHANGE
for lines on which there has been no change
since the last
.Fn refresh .
E 3
E 1
