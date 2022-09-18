h26164
s 00000/00000/00032
d D 8.1 93/06/08 18:32:17 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00030
d D 6.4 93/06/08 18:31:59 bostic 7 5
c do roff .c files by hand
e
s 00002/00002/00030
d R 8.1 93/06/04 16:45:24 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00019/00025
d D 6.3 91/04/17 10:37:58 bostic 5 4
c new copyright; att/bsd/shared
e
s 00015/00004/00029
d D 6.2 89/03/17 11:32:25 bostic 4 3
c add Berkeley specific copyright notices
e
s 00019/00015/00014
d D 6.1 86/04/24 00:03:11 mckusick 3 2
c document distributed with 4.3BSD
e
s 00003/00000/00026
d D 5.1 86/04/24 00:02:52 mckusick 2 1
c document distributed with 4.2BSD
e
s 00026/00000/00000
d D 4.1 86/04/24 00:02:02 mckusick 1 0
c document distributed with 4.1BSD
e
u
U
t
T
I 1
D 5
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 4
I 2
 *
D 4
 *	%W% (Berkeley) %G%";
E 4
I 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	%W% (Berkeley) %G%
E 4
E 2
 */
I 2

E 5
I 5
D 7
.\" Copyright (c) 1980 The Regents of the University of California.
.\" All rights reserved.
E 7
I 7
.\" Copyright (c) 1980, 1993
.\"	 The Regents of the University of California.  All rights reserved.
E 7
.\"
.\" %sccs.include.redist.roff%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 5
E 2
D 3

E 3
# define	WINDOW	struct _win_st

struct _win_st {
D 3
	short	_cury, _curx;
	short	_maxy, _maxx;
	short	_begy, _begx;
	short	_flags;
	bool	_clear;
	bool	_leave;
	bool	_scroll;
	char	**_y;
	short	*_firstch;
	short	*_lastch;
E 3
I 3
	short		_cury, _curx;
	short		_maxy, _maxx;
	short		_begy, _begx;
	short		_flags;
	short		_ch_off;
	bool		_clear;
	bool		_leave;
	bool		_scroll;
	char		**_y;
	short		*_firstch;
	short		*_lastch;
	struct _win_st	*_nextp, *_orig;
E 3
};

D 3
# define	_SUBWIN		01
# define	_ENDLINE	02
# define	_FULLWIN	04
# define	_SCROLLWIN	010
E 3
I 3
# define	_ENDLINE	001
# define	_FULLWIN	002
# define	_SCROLLWIN	004
# define	_FLUSH		010
# define	_FULLLINE	020
# define	_IDLINE		040
E 3
# define	_STANDOUT	0200
I 3
# define	_NOCHANGE	-1
E 3
E 1
