h60503
s 00002/00002/00059
d D 8.1 93/06/06 15:36:23 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00012/00060
d D 5.9 90/06/01 17:03:59 bostic 9 8
c new copyright notice
e
s 00001/00000/00071
d D 5.8 88/12/06 15:16:36 bostic 8 7
c add ":a[rgs]" command from vi
e
s 00040/00055/00031
d D 5.7 88/11/22 16:51:25 bostic 7 6
c less -> more
e
s 00002/00004/00084
d D 5.6 88/07/25 12:04:48 bostic 6 5
c update copyright notice
e
s 00000/00003/00088
d D 5.5 88/07/22 12:07:31 bostic 5 4
c don't define NULL here
e
s 00000/00001/00091
d D 5.4 88/07/22 11:14:54 bostic 4 3
c remove SIGNAL define
e
s 00003/00005/00089
d D 5.3 88/07/22 11:11:47 bostic 3 2
c add param.h, file.h, remove defines.h
e
s 00001/00004/00093
d D 5.2 88/07/21 19:02:02 bostic 2 1
c offset_t -> off_t; compiler defines void
e
s 00097/00000/00000
d D 5.1 88/07/21 18:52:45 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 10
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 6
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 6
D 9
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 6
 * by the University of California, Berkeley.  The name of the
E 6
I 6
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 6
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 9
I 9
 * %sccs.include.redist.c%
E 9
 *
 *	%W% (Berkeley) %G%
 */

D 7
/*
 * Standard include file for "less".
 */
E 7
I 7
#define	RECOMP
E 7

D 7
/*
D 3
 * Include the file of compile-time options.
 */
#include "defines.h"

/*
E 3
 * Language details.
 */
D 2
#if !VOID
#define	void  int
#endif
E 2
#define	public		/* PUBLIC FUNCTION */
E 7
I 7
#define	NULL_POSITION	((off_t)(-1))
E 7

D 7
/*
 * Special types and constants.
 */
typedef long		POSITION;
/*
 * {{ Warning: if POSITION is changed to other than "long",
 *    you may have to change some of the printfs which use "%ld"
 *    to print a variable of type POSITION. }}
 */

#define	NULL_POSITION	((POSITION)(-1))

/*
 * The type of signal handler functions.
 * Usually int, although it should be void.
 */
typedef	int		HANDLER;


#define	FILENAME	128	/* Max size of a filename */

E 7
#define	EOI		(0)
D 5
#ifndef NULL
#define	NULL		(0)
#endif
E 5
D 7

E 7
#define	READ_INTR	(-2)

D 7
/* How quiet should we be? */
#define	NOT_QUIET	0	/* Ring bell at eof and for errors */
#define	LITTLE_QUIET	1	/* Ring bell only for errors */
#define	VERY_QUIET	2	/* Never ring bell */

/* How should we prompt? */
#define	PR_SHORT	0	/* Prompt with colon */
#define	PR_MEDIUM	1	/* Prompt with message */
#define	PR_LONG		2	/* Prompt with longer message */

/* How should we handle backspaces? */
#define	BS_SPECIAL	0	/* Do special things for underlining and bold */
#define	BS_NORMAL	1	/* \b treated as normal char; actually output */
#define	BS_CONTROL	2	/* \b treated as control char; prints as ^H */

E 7
/* Special chars used to tell put_line() to do something special */
D 7
#define	UL_CHAR		'\201'	/* Enter underline mode */
#define	UE_CHAR		'\202'	/* Exit underline mode */
#define	BO_CHAR		'\203'	/* Enter boldface mode */
#define	BE_CHAR		'\204'	/* Exit boldface mode */
E 7
I 7
#define	UL_CHAR		'\201'		/* Enter underline mode */
#define	UE_CHAR		'\202'		/* Exit underline mode */
#define	BO_CHAR		'\203'		/* Enter boldface mode */
#define	BE_CHAR		'\204'		/* Exit boldface mode */
E 7

D 7
#define	CONTROL(c)		((c)&037)
E 7
I 7
#define	CONTROL_CHAR(c)		(iscntrl(c))
#define	CARAT_CHAR(c)		((c == '\177') ? '?' : (c | 0100))
E 7
D 4
#define	SIGNAL(sig,func)	signal(sig,func)
E 4
I 3

D 7
#include <sys/param.h>
#include <sys/file.h>
E 7
I 7
#define	TOP		(0)
#define	TOP_PLUS_ONE	(1)
#define	BOTTOM		(-1)
#define	BOTTOM_PLUS_ONE	(-2)
#define	MIDDLE		(-3)
E 7
E 3

D 7
/* Library function declarations */
D 2
offset_t lseek();
E 2
I 2
off_t lseek();
E 2
char *calloc();
E 7
I 7
#define	A_INVALID		-1
E 7

D 7
#include "funcs.h"
E 7
I 7
#define	A_AGAIN_SEARCH		1
#define	A_B_LINE		2
#define	A_B_SCREEN		3
#define	A_B_SCROLL		4
#define	A_B_SEARCH		5
#define	A_DIGIT			6
#define	A_EXAMINE		7
#define	A_FREPAINT		8
#define	A_F_LINE		9
#define	A_F_SCREEN		10
#define	A_F_SCROLL		11
#define	A_F_SEARCH		12
#define	A_GOEND			13
#define	A_GOLINE		14
#define	A_GOMARK		15
#define	A_HELP			16
#define	A_NEXT_FILE		17
#define	A_PERCENT		18
#define	A_PREFIX		19
#define	A_PREV_FILE		20
#define	A_QUIT			21
#define	A_REPAINT		22
#define	A_SETMARK		23
#define	A_STAT			24
#define	A_VISUAL		25
#define	A_TAGFILE		26
I 8
#define	A_FILE_LIST		27
E 8
E 7
E 1
