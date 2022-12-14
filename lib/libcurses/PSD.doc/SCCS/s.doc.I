h63904
s 00002/00002/00321
d D 8.1 93/06/04 16:44:11 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00322
d D 6.3 91/04/17 10:37:46 bostic 5 4
c new copyright; att/bsd/shared
e
s 00014/00003/00319
d D 6.2 89/03/17 11:31:57 bostic 4 3
c add Berkeley specific copyright notices
e
s 00044/00018/00278
d D 6.1 86/04/23 23:48:00 mckusick 3 2
c Ken Arnold edits for document distributed with 4.3BSD
e
s 00000/00000/00296
d D 5.1 86/04/23 23:47:54 mckusick 2 1
c document distributed with 4.2BSD
e
s 00296/00000/00000
d D 4.1 86/04/23 23:47:48 mckusick 1 0
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
D 6
.\" Copyright (c) 1980 The Regents of the University of California.
.\" All rights reserved.
E 6
I 6
.\" Copyright (c) 1980, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 6
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
.Ds
.Fd addch ch \*m
char	ch;
D 3
.sp .5
E 3
.Fd waddch win\*,ch
WINDOW	*win;
char	ch;
.De
Add the character
.Vn ch
on the window
at the current \*y.
If the character is a newline
(\'\en\')
the line will be cleared to the end,
and the current \*y will be changed to the
beginning off the next line
if newline mapping is on,
or to the next line at the same x co-ordinate
if it is off.
A return
(\'\er\')
will move to the beginning of the line on the window.
Tabs
(\'\et\')
will be expanded into spaces
in the normal tabstop positions of
every eight characters.
\*(Es
.Ds
.Fd addstr str \*m
char	*str;
D 3
.sp .5
E 3
.Fd waddstr win\*,str
WINDOW	*win;
char	*str;
.De
Add the string pointed to by
.Vn str
on the window at the current \*y.
\*(Es
In this case, it will put on as much as it can.
.Ds
.Fd box win\*,vert\*,hor
WINDOW	*win;
char	vert\*,hor;
.De
.Pp
Draws a box around the window using
.Vn vert
as the character for drawing the vertical sides, and
.Vn hor
for drawing the horizontal lines.
If scrolling is not allowed,
and the window encompasses the lower right-hand corner of the terminal,
the corners are left blank to avoid a scroll.
.Ds
.Fd clear "" \*m
D 3
.sp .5
E 3
.Fd wclear win
WINDOW	*win;
.De
Resets the entire window to blanks.
If
.Vn win
is a screen,
this sets the clear flag,
which will cause a clear-screen sequence to be sent
on the next
.Fn refresh
call.
This also moves the current \*y
to (0\*,0).
.Ds
.Fd clearok scr\*,boolf \*m
WINDOW	*scr;
bool	boolf;
.De
Sets the clear flag for the screen
.Vn scr .
If
.Vn boolf
is TRUE,
this will force a clear-screen to be printed on the next
.Fn refresh ,
or stop it from doing so if
.Vn boolf
is FALSE.
This only works on screens,
and,
unlike
.Fn clear ,
does not alter the contents of the screen.
If
.Vn scr
is
.Vn curscr ,
the next
.Fn refresh
call will cause a clear-screen,
even if the window passed to
.Fn refresh
is not a screen.
.Ds
.Fd clrtobot "" \*m
D 3
.sp .5
E 3
.Fd wclrtobot win
WINDOW	*win;
.De
Wipes the window clear from the current \*y to the bottom.
This does not force a clear-screen sequence on the next refresh
under any circumstances.
\*(Nm
.Ds
.Fd clrtoeol "" \*m
D 3
.sp .5
E 3
.Fd wclrtoeol win
WINDOW	*win;
.De
Wipes the window clear from the current \*y to the end of the line.
\*(Nm
.Ds
.Fd delch
D 3
.sp .5
E 3
.Fd wdelch win
WINDOW	*win;
.De
Delete the character at the current \*y.
Each character after it on the line shifts to the left,
and the last character becomes blank.
.Ds
.Fd deleteln
D 3
.sp .5
E 3
.Fd wdeleteln win
WINDOW	*win;
.De
Delete the current line.
Every line below the current one will move up,
and the bottom line will become blank.
The current \*y will remain unchanged.
.Ds
.Fd erase "" \*m
D 3
.sp .5
E 3
.Fd werase win
WINDOW	*win;
.De
Erases the window to blanks without setting the clear flag.
This is analagous to
.Fn clear ,
except that it never causes a clear-screen sequence to be generated
on a
.Fn refresh .
\*(Nm
.Ds
I 3
.Fd flushok win\*,boolf \*m
WINDOW	*win;
bool	boolf;
.De
Normally,
.Fn refresh
.Fn fflush 's
.Vn stdout
when it is finished.
.Fn flushok
allows you to control this.
if
.Vn boolf
is TRUE
(\c
.i i.e. ,
non-zero)
it will do the
.Fn fflush ;
if it is FALSE.
it will not.
.Ds
.Fd idlok win\*,boolf
WINDOW	*win;
bool	boolf;
.De
Reserved for future use.
This will eventually signal to
.Fn refresh
that it is all right to use the insert and delete line sequences
when updating the window.
.Ds
E 3
.Fd insch c
char	c;
D 3
.sp .5
E 3
.Fd winsch win\*,c
WINDOW	*win;
char	c;
.De
Insert
.Vn c
at the current \*y
Each character after it shifts to the right,
and the last character disappears.
\*(Es
.Ds
.Fd insertln
D 3
.sp .5
E 3
.Fd winsertln win
WINDOW	*win;
.De
Insert a line above the current one.
Every line below the current line
will be shifted down,
and the bottom line will disappear.
The current line will become blank,
and the current \*y will remain unchanged.
D 3
\*(Es
E 3
.Ds
.Fd move y\*,x \*m
int	y\*,x;
D 3
.sp .5
E 3
.Fd wmove win\*,y\*,x
WINDOW	*win;
int	y\*,x;
.De
Change the current \*y of the window to
.Vn y\*,x ). (
\*(Es
.Ds
.Fd overlay win1\*,win2
WINDOW	*win1\*,*win2;
.De
Overlay
.Vn win1
on
.Vn win2 .
The contents of
.Vn win1 ,
insofar as they fit,
are placed on
.Vn win2
at their starting \*y.
This is done non-destructively,
i.e., blanks on
.Vn win1
leave the contents of the space on
.Vn win2
untouched.
.Ds
.Fd overwrite win1\*,win2
WINDOW	*win1\*,*win2;
.De
Overwrite
.Vn win1
on
.Vn win2 .
The contents of
.Vn win1 ,
insofar as they fit,
are placed on
.Vn win2
at their starting \*y.
This is done destructively,
D 3
i.e., blanks on
E 3
I 3
.i i.e. ,
blanks on
E 3
.Vn win1
become blank on
.Vn win2 .
.Ds
.Fd printw fmt\*,arg1\*,arg2\*,...
char	*fmt;
D 3
.sp .5
E 3
.Fd wprintw win\*,fmt\*,arg1\*,arg2\*,...
WINDOW	*win;
char	*fmt;
.De
Performs a
.Fn printf
on the window starting at the current \*y.
It uses
.Fn addstr
to add the string on the window.
It is often advisable to use the field width options of
.Fn printf
to avoid leaving things on the window from earlier calls.
\*(Es
.Ds
.Fd refresh "" \*m
D 3
.sp .5
E 3
.Fd wrefresh win
WINDOW	*win;
.De
Synchronize the terminal screen with the desired window.
If the window is not a screen,
only that part covered by it is updated.
\*(Es
In this case, it will update whatever it can
without causing the scroll.
I 3
.sp
As a special case,
if
.Fn wrefresh
is called with the window
.Vn curscr
the screen is cleared
and repainted as it is currently.
This is very useful for allowing the redrawing of the screen
when the user has garbage dumped on his terminal.
E 3
.Ds
.Fd standout "" \*m
D 3
.sp .5
E 3
.Fd wstandout win
WINDOW	*win;
D 3
.sp .5
E 3
.Fd standend "" \*m
D 3
.sp .5
E 3
.Fd wstandend win
WINDOW	*win;
.De
Start and stop putting characters onto
.i win
in standout mode.
.Fn standout
causes any characters added to the window
to be put in standout mode on the terminal
(if it has that capability).
.Fn standend
stops this.
The sequences
.Vn SO
and
.Vn SE
(or
.Vn US
and
.Vn UE
if they are not defined)
are used (see Appendix A).
E 1
