h13326
s 00002/00000/00308
d D 8.5 95/04/29 10:01:18 bostic 67 66
c bool means something to C++
c From: Chris Torek <torek@BSDI.COM>
e
s 00002/00002/00306
d D 8.4 94/08/10 07:49:03 bostic 66 65
c wstandend/wstandout return an int (that's what System V does)
e
s 00009/00010/00299
d D 8.3 94/07/27 14:51:19 bostic 65 64
c delete __FULLLINE, it's never used
c __tscroll has to take a second integer argument for CS string
e
s 00001/00001/00308
d D 8.2 94/01/02 12:25:13 bostic 64 63
c delete HZ, it's Hazeltine specific, and conflicts with HZ as Hertz
e
s 00002/00002/00307
d D 8.1 93/06/07 12:14:28 bostic 63 62
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00002/00308
d D 5.39 93/06/07 12:14:18 bostic 62 60
c prettiness police
e
s 00002/00002/00308
d R 8.1 93/06/04 16:47:38 bostic 61 60
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00005/00300
d D 5.38 93/06/04 16:11:55 marc 60 59
c changed to remember and restore TSTP handler, and also to resnapshot tty state when restarting from TSTP.  Also, hardwire GT variable since we always turn tab expansion off.  We still aren't sure what pfast is for, but we haven't given up yet.
e
s 00002/00002/00303
d D 5.37 93/05/25 16:06:44 bostic 59 58
c make mvcur a real function, it's just too painful otherwise
e
s 00005/00004/00300
d D 5.36 93/05/17 14:19:48 bostic 58 57
c make a few private functions public so the prototypes work
e
s 00000/00001/00304
d D 5.35 93/05/16 21:37:03 bostic 57 56
c some preprocessors try to redefine the mvcur prototype to be __mvcur
c which fails miserably; don't use mvcur internally, either
e
s 00001/00001/00304
d D 5.34 93/05/16 15:54:36 bostic 56 55
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00002/00000/00303
d D 5.33 93/05/11 15:38:07 elan 55 54
c Added __mvcur and made mvcur a #define.
e
s 00002/00001/00301
d D 5.32 93/05/07 10:10:49 bostic 54 53
c make __cputchar visible, the back compatibility stuff uses it
c bug report 4.4BSD-alpha/include/0
e
s 00001/00001/00301
d D 5.31 93/02/24 15:13:26 elan 53 52
c Fixed typo in insch decl.
e
s 00002/00000/00300
d D 5.30 93/02/18 16:59:32 elan 52 51
c Added waddch and hash prototypes.
e
s 00001/00001/00299
d D 5.29 93/02/18 16:19:40 elan 51 50
c bcopy, bcmp -> memcpy, memcmp.
e
s 00041/00036/00259
d D 5.28 93/02/13 14:31:54 bostic 50 49
c add the System V C-string oriented functions (from curs_addstr(TI_LIB));
c make waddstr a macro, minor cleanups
e
s 00003/00003/00292
d D 5.27 93/02/12 09:32:36 bostic 49 48
c make strings to addbytes and addstr const char * (for gcc2)
e
s 00003/00003/00292
d D 5.26 93/02/03 17:50:39 elan 48 47
c 0x80 -> 0xff in unctrl().
e
s 00008/00007/00287
d D 5.25 93/01/24 20:13:17 bostic 47 46
c rename origtermio to __orig_termios; delete tstp, add
c __stop_signal_handler and __startwin
e
s 00004/00004/00290
d D 5.24 93/01/11 13:41:35 elan 46 45
c unctrl -> 8-bit characters,
e
s 00076/00071/00218
d D 5.23 93/01/11 12:26:20 bostic 45 41
c make GT, NONL, UPPERCASE and termcap strings `backward compat only'
c export waddbytes(); tscroll -> __tscroll; make __cputchar private;
c prettiness police
e
s 00018/00018/00278
d R 5.25 93/01/11 11:53:43 bostic 44 43
c CURSES_{OK,ERR} -> OK,ERR
e
s 00017/00014/00279
d R 5.24 92/12/30 15:08:44 elan 43 42
c Made termcap capabilities private.
e
s 00018/00014/00275
d R 5.23 92/12/30 14:54:44 elan 42 41
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00003/00002/00286
d D 5.22 92/12/30 14:10:19 elan 41 40
c Made _sprintw and _sscans global and public. Changed the names to 
c vwprintw and vwscanw respectively.
e
s 00001/00001/00287
d D 5.21 92/11/12 14:09:03 elan 40 39
c Corrected previous fix.
e
s 00001/00001/00287
d D 5.20 92/11/12 14:07:12 elan 39 38
c Fixed bug in winch() definition.
e
s 00001/00000/00287
d D 5.19 92/11/11 17:35:11 elan 38 37
c Added pointers to firstch and lastch for correct operation of 
c subwindows.
e
s 00005/00002/00282
d D 5.18 92/10/27 14:37:51 elan 37 36
c Changed touchline to __touchline so that touchline forces repaint 
c of line whereas the internal __touchline does not.
e
s 00023/00018/00261
d D 5.17 92/10/26 12:46:31 elan 36 35
c Changed to new line data structures (__LDATA and __LINE) and 
c eliminated linked list representation of window (not useful).
e
s 00010/00007/00269
d D 5.16 92/10/20 10:44:25 elan 35 34
c Changed standout character representation so that characters are 
c eight bit clean.
e
s 00001/00000/00275
d D 5.15 92/09/22 13:37:39 elan 34 33
c Added standout
e
s 00004/00001/00271
d D 5.14 92/09/21 15:27:01 elan 33 32
c Added __ISPASTEOL, tscroll and SR, SF, AL, DL support along with 
c overrinding __noqch variable.
e
s 00043/00028/00229
d D 5.13 92/09/14 11:00:23 elan 32 31
c Converted to new data structures.
e
s 00000/00001/00257
d D 5.12 92/09/01 13:07:49 bostic 31 30
c forgot to remove scroll variable, abortive attempt at scrolling
e
s 00003/00003/00255
d D 5.11 92/08/31 14:30:33 elan 30 29
c Fixed puts, baudrate abd ospeed macros.
e
s 00217/00150/00041
d D 5.10 92/08/23 14:44:38 bostic 29 26
c massive cleanup, welcome to the 90's!
e
s 00001/00000/00255
d R 5.11 92/06/17 16:16:26 bostic 28 27
c add termios.h to curses.h, so old stuff compiles
e
s 00214/00150/00041
d R 5.10 92/05/15 15:17:41 bostic 27 26
c This file has been massively reorganized and reworked
c reformat to KNF, redo tracing interface, new version for vi
e
s 00003/00000/00188
d D 5.9 90/07/01 15:39:28 bostic 26 25
c restore terminal state correctly; bug report 4.3BSD-tahoe/include/1
e
s 00001/00011/00187
d D 5.8 90/06/01 15:38:04 bostic 25 24
c new copyright notice
e
s 00002/00000/00196
d D 5.7 90/06/01 15:36:23 marc 24 23
c for Marc; needs USE_OLD_TTY
e
s 00043/00043/00153
d D 5.6 89/08/28 21:26:06 karels 23 22
c make ctags work with this (wonder if the old ctags did this format?)
e
s 00021/00011/00175
d D 5.5 89/06/29 19:28:29 bostic 22 21
c remove references to [sg]tty
e
s 00010/00005/00176
d D 5.4 88/06/30 17:21:26 bostic 21 20
c install approved copyright notice
e
s 00009/00003/00172
d D 5.3 88/06/08 13:56:57 bostic 20 19
c written by Ken Arnold; add Berkeley specific header
e
s 00007/00002/00168
d D 5.2 87/06/24 14:17:16 minshall 19 18
c Add 'addbytes.c', plus some cleanup by K. Bostic in Makefile.
e
s 00008/00001/00162
d D 5.1 85/06/07 11:45:28 dist 18 17
c Add copyright
e
s 00001/00001/00162
d D 1.16 85/05/23 15:37:45 bloom 17 16
c Add support for XS
e
s 00026/00013/00137
d D 1.15 85/05/01 17:44:05 bloom 16 15
c new version from arnold
e
s 00001/00000/00149
d D 1.14 83/07/04 18:43:51 sam 15 14
c extern
e
s 00004/00000/00145
d D 1.13 83/07/03 18:08:05 sam 14 13
c put unctrl back in as a macro
e
s 00016/00016/00129
d D 1.12 83/05/09 21:13:00 arnold 13 12
c integrate subwindows fully into all parts of curses
e
s 00001/00001/00144
d D 1.11 83/02/02 15:19:13 arnold 12 11
c unctrl should strip off parity bit
e
s 00004/00004/00141
d D 1.10 82/02/17 14:10:44 arnold 11 10
c adopt latest version of fgoto() and plod() from vi
e
s 00002/00002/00143
d D 1.9 82/02/16 17:04:47 arnold 10 9
c forgot to add str as a parameter to getstr, mvgetstr
e
s 00001/00001/00144
d D 1.8 81/05/15 16:21:56 arnold 9 8
c add getcap() function
e
s 00003/00000/00142
d D 1.7 81/04/17 00:42:33 arnold 8 7
c add delch(), mvdelch(), and mvwdelch()
e
s 00003/00000/00139
d D 1.6 81/04/17 00:31:10 arnold 7 6
c add insch(), mvinsch(), and mvwinsch()
e
s 00001/00001/00138
d D 1.5 81/03/29 22:18:38 arnold 6 5
c fix up mxinch to use stdscr instead of win
e
s 00009/00009/00130
d D 1.4 81/03/05 20:50:52 arnold 5 3
c move all declarations from curses.h to curses.c
e
s 00005/00005/00134
d R 1.4 81/03/05 20:02:01 arnold 4 3
c make the "extern" variables not extern so they are defined
e
s 00003/00004/00136
d D 1.3 81/03/05 19:33:52 arnold 3 2
c make #ifndef WINDOW apply to whole file
e
s 00036/00096/00104
d D 1.2 81/02/17 15:52:42 arnold 2 1
c shorten everything up for faster compilation
e
s 00200/00000/00000
d D 1.1 81/01/26 17:02:47 arnold 1 0
c date and time created 81/01/26 17:02:47 by arnold
e
u
U
t
T
I 1
D 13
/* %G% (Berkeley) %W% */
E 13
I 13
D 16
/* %W% (Berkeley) %G% */
E 16
I 16
D 18
/* %G% (Berkeley) %W% */
E 18
I 18
/*
D 20
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 20
I 20
D 63
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 63
I 63
D 65
 * Copyright (c) 1981, 1993
E 65
I 65
 * Copyright (c) 1981, 1993, 1994
E 65
 *	The Regents of the University of California.  All rights reserved.
E 63
 *
D 25
 * Redistribution and use in source and binary forms are permitted
D 21
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 21
I 21
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 25
I 25
 * %sccs.include.redist.c%
E 25
E 21
E 20
 *
 *	%W% (Berkeley) %G%
 */

E 18
E 16
E 13
I 3
D 23
# ifndef WINDOW
E 23
I 23
D 29
#ifndef WINDOW
E 29
I 29
#ifndef _CURSES_H_
#define	_CURSES_H_
E 29
E 23
E 3

D 23
# include	<stdio.h>
E 23
I 23
D 29
#include	<stdio.h>
E 23
 
I 24
#define USE_OLD_TTY
E 24
D 22
# include	<sgtty.h>
E 22
I 22
D 23
# include	<sys/ioctl.h>
E 23
I 23
#include	<sys/ioctl.h>
I 24
#undef USE_OLD_TTY
E 29
I 29
#include <stdio.h>
E 29
E 24
E 23
E 22

I 29
/*
 * The following #defines and #includes are present for backward
 * compatibility only.  They should not be used in future code.
 *
 * START BACKWARD COMPATIBILITY ONLY.
 */
#ifndef _CURSES_PRIVATE
I 67
#ifndef __cplusplus
E 67
E 29
D 2
# define	bool	char		/* boolean variable		*/
# define	reg	register	/* register varaible abbr.	*/
E 2
I 2
D 23
# define	bool	char
# define	reg	register
E 23
I 23
#define	bool	char
I 67
#endif
E 67
#define	reg	register
E 23
E 2

I 29
#ifndef TRUE
E 29
D 23
# define	TRUE	(1)
# define	FALSE	(0)
D 2
# define	ERR	(0)		/* default return on error	*/
# define	OK	(1)		/* default return on good run	*/
E 2
I 2
# define	ERR	(0)
# define	OK	(1)
E 23
I 23
#define	TRUE	(1)
I 29
#endif
#ifndef FALSE
E 29
#define	FALSE	(0)
D 29
#define	ERR	(0)
#define	OK	(1)
E 29
I 29
#endif
E 29
E 23
E 2

D 2
# define	_SUBWIN		01	/* window is a subindow		*/
# define	_ENDLINE	02	/* lines go to end of screen	*/
# define	_FULLWIN	04	/* window is entire screen	*/
# define	_SCROLLWIN	010	/* window could cause scroll	*/
# define	_FLUSH		020	/* flush after refresh		*/
# define	_STANDOUT	0200	/* standout mode in effect	*/
# define	_NOCHANGE	-1	/* no change on this line	*/
E 2
I 2
D 13
# define	_SUBWIN		01
# define	_ENDLINE	02
# define	_FULLWIN	04
# define	_SCROLLWIN	010
# define	_FLUSH		020
E 13
I 13
D 23
# define	_ENDLINE	001
# define	_FULLWIN	002
# define	_SCROLLWIN	004
# define	_FLUSH		010
I 16
# define	_FULLLINE	020
# define	_IDLINE		040
E 16
E 13
# define	_STANDOUT	0200
# define	_NOCHANGE	-1
E 23
I 23
D 29
#define	_ENDLINE	001
#define	_FULLWIN	002
#define	_SCROLLWIN	004
#define	_FLUSH		010
#define	_FULLLINE	020
#define	_IDLINE		040
#define	_STANDOUT	0200
#define	_NOCHANGE	-1
E 23
E 2

E 29
D 16
# define	_puts(s)	tputs(s, 0, _putchar);
E 16
I 16
D 23
# define	_puts(s)	tputs(s, 0, _putchar)
E 23
I 23
D 30
#define	_puts(s)	tputs(s, 0, _putchar)
E 30
I 30
#define	_puts(s)	tputs(s, 0, __cputchar)
E 30
I 29
#define	_putchar(c)	__cputchar(c)
E 29
E 23
E 16

D 29
typedef	struct sgttyb	SGTTY;
E 29
I 29
/* Old-style terminal modes access. */
D 30
#define	baudrate()	(cfgetospeed(origtermio))
E 30
I 30
D 47
#define	baudrate()	(cfgetospeed(&origtermio))
E 47
I 47
D 60
#define	baudrate()	(cfgetospeed(&__orig_termios))
E 60
I 60
#define	baudrate()	(cfgetospeed(&__baset))
E 60
E 47
E 30
#define	crmode()	cbreak()
D 47
#define	erasechar()	(origtermio.c_cc[VERASE])
#define	killchar()	(origtermio.c_cc[VKILL])
E 47
I 47
D 60
#define	erasechar()	(__orig_termios.c_cc[VERASE])
#define	killchar()	(__orig_termios.c_cc[VKILL])
E 60
I 60
#define	erasechar()	(__baset.c_cc[VERASE])
#define	killchar()	(__baset.c_cc[VKILL])
E 60
E 47
#define	nocrmode()	nocbreak()
D 30
#define	ospeed		(cfgetospeed(origtermio))
E 30
I 30
D 47
#define	ospeed		(cfgetospeed(&origtermio))
E 47
I 47
D 60
#define	ospeed		(cfgetospeed(&__orig_termios))
E 60
I 60
#define	ospeed		(cfgetospeed(&__baset))
E 60
E 47
E 30
#endif /* _CURSES_PRIVATE */
E 29

I 45
extern char	 GT;			/* Gtty indicates tabs. */
extern char	 NONL;			/* Term can't hack LF doing a CR. */
extern char	 UPPERCASE;		/* Terminal is uppercase only. */

E 45
D 3
# ifndef WINDOW

E 3
D 2
/* Copyright (c) 1979 Regents of the University of California */
E 2
D 29
/*
 * Capabilities from termcap
E 29
I 29
extern int	 My_term;		/* Use Def_term regardless. */
extern char	*Def_term;		/* Default terminal type. */

I 45
/* Termcap capabilities. */
D 64
extern char	AM, BS, CA, DA, EO, HC, HZ, IN, MI, MS, NC, NS, OS,
E 64
I 64
extern char	AM, BS, CA, DA, EO, HC, IN, MI, MS, NC, NS, OS,
E 64
		PC, UL, XB, XN, XT, XS, XX;
extern char	*AL, *BC, *BT, *CD, *CE, *CL, *CM, *CR, *CS, *DC, *DL,
		*DM, *DO, *ED, *EI, *K0, *K1, *K2, *K3, *K4, *K5, *K6,
		*K7, *K8, *K9, *HO, *IC, *IM, *IP, *KD, *KE, *KH, *KL,
		*KR, *KS, *KU, *LL, *MA, *ND, *NL, *RC, *SC, *SE, *SF,
		*SO, *SR, *TA, *TE, *TI, *UC, *UE, *UP, *US, *VB, *VS,
		*VE, *al, *dl, *sf, *sr,
		*AL_PARM, *DL_PARM, *UP_PARM, *DOWN_PARM, *LEFT_PARM,
		*RIGHT_PARM;

E 45
/* END BACKWARD COMPATIBILITY ONLY. */

D 48
/* 7-bit ASCII characters. */
D 46
#define	unctrl(c)		__unctrl[(c) & 0x7f]
#define	unctrllen(ch)		__unctrllen[(ch) & 0x7f]
E 46
I 46
#define	unctrl(c)		__unctrl[(c) & 0x80]
#define	unctrllen(ch)		__unctrllen[(ch) & 0x80]
E 48
I 48
/* 8-bit ASCII characters. */
#define	unctrl(c)		__unctrl[(c) & 0xff]
#define	unctrllen(ch)		__unctrllen[(ch) & 0xff]
E 48
E 46

I 45
D 46
extern char	*__unctrl[0x80];	/* Control strings. */
extern char	 __unctrllen[0x80];	/* Control strings length. */
E 46
I 46
extern char	*__unctrl[256];	/* Control strings. */
extern char	 __unctrllen[256];	/* Control strings length. */
E 46

E 45
D 32
typedef struct _win_st {		/* Window structure. */
	short		_cury, _curx;	/* Current x, y coordinates. */
	short		_maxy, _maxx;	/* Maximum values for curx, cury. */
	short		_begy, _begx;	/* Window home. */
E 32
I 32
/*
D 36
 * A window is a circular doubly linked list of LINEs who's first line is 
 * given by the topline pointer in the WINDOW structure.
E 36
I 36
 * A window an array of __LINE structures pointed to by the 'lines' pointer.
 * A line is an array of __LDATA structures pointed to by the 'line' pointer.
 *
 * IMPORTANT: the __LDATA structure must NOT induce any padding, so if new
 * fields are added -- padding fields with *constant values* should ensure 
 * that the compiler will not generate any padding when storing an array of
D 51
 *  __LDATA structures.  This is to enable consistent use of bcmp, and bcopy
E 51
I 51
 *  __LDATA structures.  This is to enable consistent use of memcmp, and memcpy
E 51
 * for comparing and copying arrays.
E 36
 */
E 32
D 45

E 45
D 32
#define	_ENDLINE	0x001		/* End of screen. */
#define	_FLUSH		0x002		/* fflush(stdout) after refresh. */
#define	_FULLLINE	0x004		/* Line width = terminal width. */
#define	_FULLWIN	0x008		/* Window is a screen. */
#define	_IDLINE		0x010		/* Insert/delete sequences. */
#define	_SCROLLWIN	0x020		/* Last char will scroll window. */
E 32
I 32
D 36
typedef struct __line {
	struct __line *next, *prev;	/* Next line, previous line. */
E 36
I 36
typedef struct {
	char ch;			/* the actual character */

#define	__STANDOUT	0x01  		/* Added characters are standout. */
	char attr;			/* attributes of character */
} __LDATA;

#define __LDATASIZE	(sizeof(__LDATA))

typedef struct {
E 36
#define	__ISDIRTY	0x01		/* Line is dirty. */
I 33
#define __ISPASTEOL	0x02		/* Cursor is past end of line */
I 37
#define __FORCEPAINT	0x04		/* Force a repaint of the line */
E 37
E 33
	u_int flags;
	u_int hash;			/* Hash value for the line. */
I 38
	size_t *firstchp, *lastchp;	/* First and last chngd columns ptrs */
E 38
	size_t firstch, lastch;		/* First and last changed columns. */
I 36
	__LDATA *line;			/* Pointer to the line text. */
} __LINE;
E 36
I 34
D 35
	char *standout;			/* standout character markers */
E 34
E 32
/* 
 * XXX
 * _STANDOUT is the 8th bit, characters themselves are encoded.
E 29
 */
I 29
D 32
#define	_STANDOUT	0x080		/* Added characters are standout. */
	unsigned short	_flags;
E 32
I 32
#define	__STANDOUT	0x080		/* Added characters are standout. */
	char *line;			/* Pointer to line itself. */
E 35
I 35

D 36
#define	__STANDOUT	0x01  		/* Added characters are standout. */
	char *standout;			/* Standout character markers.
					 * This field is stored as an 
					 * extension to the line, i.e., 
					 * lp->standout = lp->line + win->maxx
					 * is an invariant.
					 */
	
	char *line;			/* Pointer to the line text. */
E 35
} LINE;
E 32
E 29

E 36
D 2
char	*AL;			/* P* Add new blank line		*/
bool	AM;			/*    Automatic margins			*/
char	*BC;			/*    Back cursor			*/
bool	BS;			/*    Backspace works			*/
char	*BT;			/* P  Back tab				*/
bool	CA;			/*    Cursor addressible		*/
char	*CD;			/* P* Clear to end of display		*/
char	*CE;			/* P  Clear to end of line		*/
char	*CL;			/* P* Clear screen			*/
char	*CM;			/* P  Cursor motion			*/
bool	DA;			/*    Display may be retained above	*/
bool	DB;			/*    Display may be retained below	*/
char	*DC;			/* P* Delete character			*/
char	*DL;			/* P* Delete line sequence		*/
char	*DM;			/*    Delete mode (enter)		*/
char	*DO;			/*    Down line sequence		*/
char	*ED;			/*    End delete mode			*/
bool	EO;			/*    Can erase overstrikes with ' '	*/
char	*EI;			/*    End insert mode			*/
bool	GT;			/*    Gtty indicates tabs		*/
char	*HO;			/*    Home cursor			*/
bool	HZ;			/*    Hazeltine ~ braindamage		*/
char	*IC;			/* P  Insert character			*/
bool	IN;			/*    Insert-null blessing		*/
char	*IM;			/*    Insrt mode (as ':im=:' if 'ic')	*/
char	*IP;			/* P* pad after char ins'd using IM+IE	*/
char	*LL;			/*    Quick to last line, column 0	*/
char	*MA;			/*    Ctrl character map for cmd mode	*/
bool	MI;			/*    can Move in Insert mode		*/
bool	MS;			/*    can Move in Standout mode		*/
bool	NC;			/*    No Cr: \r sends \r\n then eats \n	*/
char	*ND;			/*    Non-destructive space		*/
bool	OS;			/*    Overstrike works			*/
char	PC;			/*    Pad character			*/
char	*SE;			/*    Standout end (may leave space)	*/
char	*SF;			/* P  Scroll forwards			*/
char	*SO;			/*    Stand out begin (may leave space)	*/
char	*SR;			/* P  Scroll backwards			*/
char	*TA;			/* P  Tab (not ^I or with padding)	*/
char	*TE;			/*    End sequence after TI		*/
char	*TI;			/*    Terminal Initialize		*/
char	*UC;			/*    Underline a single Character	*/
char	*UE;			/*    Underline End sequence		*/
bool	UL;			/*    Underlining works even though !os	*/
char	*UP;			/*    Upline				*/
char	*US;			/*    Underline Start sequence		*/
char	*VB;			/*    Visible bell			*/
char	*VE;			/*    Visual end sequence		*/
char	*VS;			/*    Visual start sequence		*/
bool	XN;			/*    A newline gets eaten after wrap	*/
	/* X? is reserved for severely nauseous glitches		*/
	/* If there are enough of these we may need bit masks!		*/
E 2
I 2
D 5
bool	AM, BS, CA, DA, DB, EO, GT, HZ, IN, MI, MS, NC, OS, UL, XN;
char    *AL, *BC, *BT, *CD, *CE, *CL, *CM, *DC, *DL, *DM, *DO, *ED,
	*EI, *HO, *IC, *IM, *IP, *LL, *MA, *ND, *SE, *SF, *SO, *SR,
	*TA, *TE, *TI, *UC, *UE, *UP, *US, *VB, *VE, *VS, PC;
E 5
I 5
D 16
extern bool     AM, BS, CA, DA, DB, EO, GT, HZ, IN, MI, MS, NC, OS, UL,
		XN;
D 11
extern char     *AL, *BC, *BT, *CD, *CE, *CL, *CM, *DC, *DL, *DM, *DO,
		*ED, *EI, *HO, *IC, *IM, *IP, *LL, *MA, *ND, *SE, *SF,
		*SO, *SR, *TA, *TE, *TI, *UC, *UE, *UP, *US, *VB, *VE,
		*VS, PC;
E 11
I 11
extern char     *AL, *BC, *BT, *CD, *CE, *CL, *CM, *CR, *DC, *DL, *DM,
		*DO, *ED, *EI, *HO, *IC, *IM, *IP, *LL, *MA, *ND, *NL,
		*SE, *SF, *SO, *SR, *TA, *TE, *TI, *UC, *UE, *UP, *US,
		*VB, *VE, *VS, PC;
E 16
I 16
D 29
extern bool     AM, BS, CA, DA, DB, EO, HC, HZ, IN, MI, MS, NC, NS, OS, UL,
D 17
		XB, XN, XT, XX;
E 17
I 17
		XB, XN, XT, XS, XX;
E 29
I 29
D 31
	short		scroll;		/* Scrolling offset. */
E 31
D 32
	short		_ch_off;	/* x offset for firstch/lastch. */
	char		_clear;		/* If clear on next refresh. */
	char		_leave;		/* If cursor left. */
	char		_scroll;	/* If scrolling permitted. */
	char		**_y;		/* Line describing the window. */
E 32
I 32
typedef struct __window {		/* Window structure. */
	struct __window	*nextp, *orig;	/* Subwindows list and parent. */
	size_t begy, begx;		/* Window home. */
	size_t cury, curx;		/* Current x, y coordinates. */
	size_t maxy, maxx;		/* Maximum values for curx, cury. */
	short ch_off;			/* x offset for firstch/lastch. */
D 36
	LINE **lines;			/* Array of pointers to the lines */
	LINE *topline;			/* Pointer to first line in window */
	char *wspace;			/* window space (for cleanup) */
E 36
I 36
	__LINE **lines;			/* Array of pointers to the lines */
	__LINE  *lspace;		/* line space (for cleanup) */
	__LDATA *wspace;		/* window space (for cleanup) */
E 36
E 32

D 32
#define	_NOCHANGE	-1		/* No change since last refresh. */
	short		*_firstch;	/* First and last changed in line. */
	short		*_lastch;
	struct _win_st	*_nextp, *_orig;/* Subwindows list and parent. */
E 32
I 32
#define	__ENDLINE	0x001		/* End of screen. */
#define	__FLUSH		0x002		/* Fflush(stdout) after refresh. */
D 65
#define	__FULLLINE	0x004		/* Line width = terminal width. */
#define	__FULLWIN	0x008		/* Window is a screen. */
#define	__IDLINE	0x010		/* Insert/delete sequences. */
#define	__SCROLLWIN	0x020		/* Last char will scroll window. */
#define	__SCROLLOK	0x040		/* Scrolling ok. */
#define	__CLEAROK	0x080		/* Clear on next refresh. */
#define __WSTANDOUT	0x100		/* Standout window */
#define __LEAVEOK	0x200		/* If curser left */	
E 65
I 65
#define	__FULLWIN	0x004		/* Window is a screen. */
#define	__IDLINE	0x008		/* Insert/delete sequences. */
#define	__SCROLLWIN	0x010		/* Last char will scroll window. */
#define	__SCROLLOK	0x020		/* Scrolling ok. */
#define	__CLEAROK	0x040		/* Clear on next refresh. */
#define __WSTANDOUT	0x080		/* Standout window */
#define __LEAVEOK	0x100		/* If curser left */	
E 65
	u_int flags;
E 32
} WINDOW;

D 45
/* Termcap capabilities. */
extern char	AM, BS, CA, DA, EO, HC, HZ, IN, MI, MS, NC, NS, OS,
		PC, UL, XB, XN, XT, XS, XX;
E 29
E 17
extern char	*AL, *BC, *BT, *CD, *CE, *CL, *CM, *CR, *CS, *DC, *DL,
		*DM, *DO, *ED, *EI, *K0, *K1, *K2, *K3, *K4, *K5, *K6,
		*K7, *K8, *K9, *HO, *IC, *IM, *IP, *KD, *KE, *KH, *KL,
		*KR, *KS, *KU, *LL, *MA, *ND, *NL, *RC, *SC, *SE, *SF,
		*SO, *SR, *TA, *TE, *TI, *UC, *UE, *UP, *US, *VB, *VS,
D 29
		*VE, *AL_PARM, *DL_PARM, *UP_PARM, *DOWN_PARM,
		*LEFT_PARM, *RIGHT_PARM;
extern char	PC;
E 29
I 29
D 33
		*VE,
E 33
I 33
		*VE, *al, *dl, *sf, *sr,
E 33
		*AL_PARM, *DL_PARM, *UP_PARM, *DOWN_PARM, *LEFT_PARM,
		*RIGHT_PARM;
E 29
E 16
E 11
E 5
E 2

E 45
D 29
/*
 * From the tty modes...
 */
E 29
I 29
/* Curses external declarations. */
extern WINDOW	*curscr;		/* Current screen. */
extern WINDOW	*stdscr;		/* Standard screen. */
E 29
D 2
bool	NONL;			/* Term can't hack linefeeds doing a CR	*/
bool	UPPERCASE;		/* Ick!					*/
E 2

D 2
bool	normtty;		/* set if must normal mode from normf	*/
bool	_pfast;			/* Have stty -nl'ed to go faster	*/
E 2
I 2
D 5
bool	NONL, UPPERCASE;
E 5
I 5
D 16
extern bool	NONL, UPPERCASE, normtty, _pfast;
E 16
I 16
D 29
extern bool	GT, NONL, UPPERCASE, normtty, _pfast;
E 29
I 29
D 47
extern struct termios origtermio;	/* Original terminal modes. */
E 47
I 47
D 60
extern struct termios __orig_termios;	/* Original terminal modes. */
E 60
I 60
extern struct termios __orig_termios;	/* Terminal state before curses */
extern struct termios __baset;		/* Our base terminal state */
D 62
extern int __tcaction;			/* Controls whether tcsetattr will
					   ignore hardware settings */
E 62
I 62
extern int __tcaction;			/* If terminal hardware set. */
E 62
E 60
E 47
E 29
E 16
E 5
E 2

D 2
# define	WINDOW	struct _win_st
E 2
I 2
D 5
bool	normtty, _pfast;
E 2

E 5
D 2
struct _win_st {		/* window description structure		*/
	short	_cury, _curx;		/* current y,x positions	*/
	short	_maxy, _maxx;		/* maximum y,x positions	*/
	short	_begy, _begx;		/* start y,x positions		*/
	short	_flags;			/* various window flags		*/
	bool	_clear;			/* need to clear		*/
	bool	_leave;			/* leave curx,y at last update	*/
	bool	_scroll;		/* scrolls allowed		*/
	char	**_y;			/* actual window		*/
	short	*_firstch;		/* first change on line		*/
	short	*_lastch;		/* last change on line		*/
E 2
I 2
D 29
struct _win_st {
D 13
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
E 13
I 13
	short		_cury, _curx;
	short		_maxy, _maxx;
	short		_begy, _begx;
	short		_flags;
I 16
	short		_ch_off;
E 16
	bool		_clear;
	bool		_leave;
	bool		_scroll;
	char		**_y;
	short		*_firstch;
	short		*_lastch;
	struct _win_st	*_nextp, *_orig;
E 13
E 2
};
E 29
I 29
extern int	 COLS;			/* Columns on the screen. */
extern int	 LINES;			/* Lines on the screen. */
E 29

D 2
extern bool	My_term,	/* set if user species terminal		*/
		_echoit,	/* set if echoing characters		*/
		_rawmode,	/* set if terminal in raw mode		*/
		_endwin;	/* endwin has been called		*/
E 2
I 2
D 23
# define	WINDOW	struct _win_st
E 23
I 23
D 29
#define	WINDOW	struct _win_st
E 29
I 29
D 45
extern char	 GT;			/* Gtty indicates tabs. */
extern char	 NONL;			/* Term can't hack LF doing a CR. */
extern char	 UPPERCASE;		/* Terminal is uppercase only. */
E 45
extern char	*ttytype;		/* Full name of current terminal. */
D 45
extern char	*__unctrl[0x80];	/* Control strings. */
extern char	 __unctrllen[0x80];	/* Control strings length. */
E 45
E 29
E 23
E 2

D 2
extern char	*Def_term,	/* default terminal type		*/
		ttytype[];	/* long name of current terminal	*/
E 2
I 2
D 29
extern bool	My_term, _echoit, _rawmode, _endwin;
E 29
I 29
#define	ERR	(0)			/* Error return. */
#define	OK	(1)			/* Success return. */
E 29
E 2

D 2
extern int	LINES, COLS,	/* number of lines and columns		*/
		_tty_ch,	/* channel with tty on it		*/
		_res_flg;	/* sgtty flags stored for reset		*/
E 2
I 2
D 29
extern char	*Def_term, ttytype[];
E 29
I 29
/* Standard screen pseudo functions. */
D 45
#define	addbytes(da, co)	waddbytes(stdscr, da, co)
#define	addch(ch)		waddch(stdscr, ch)
#define	addstr(str)		waddbytes(stdscr, str, strlen(str))
#define	clear()			wclear(stdscr)
#define	clrtobot()		wclrtobot(stdscr)
#define	clrtoeol()		wclrtoeol(stdscr)
#define	delch()			wdelch(stdscr)
#define	deleteln()		wdeleteln(stdscr)
#define	erase()			werase(stdscr)
#define	getch()			wgetch(stdscr)
#define	getstr(str)		wgetstr(stdscr, str)
#define	inch()			winch(stdscr)
#define	insch(ch))		winsch(stdscr, ch)
#define	insertln()		winsertln(stdscr)
#define	move(y, x)		wmove(stdscr, y, x)
#define	refresh()		wrefresh(stdscr)
#define	standend()		wstandend(stdscr)
#define	standout()		wstandout(stdscr)
E 45
I 45
D 50
#define	addbytes(da, co)		waddbytes(stdscr, da, co)
E 50
I 50
#define	addbytes(s, n)			__waddbytes(stdscr, s, n, 0)
E 50
#define	addch(ch)			waddch(stdscr, ch)
D 50
#define	addstr(str)			waddbytes(stdscr, str, strlen(str))
E 50
I 50
#define	addnstr(s, n)			waddnstr(stdscr, s, n)
#define	addstr(s)			__waddbytes(stdscr, s, strlen(s), 0)
E 50
#define	clear()				wclear(stdscr)
#define	clrtobot()			wclrtobot(stdscr)
#define	clrtoeol()			wclrtoeol(stdscr)
#define	delch()				wdelch(stdscr)
#define	deleteln()			wdeleteln(stdscr)
#define	erase()				werase(stdscr)
#define	getch()				wgetch(stdscr)
D 50
#define	getstr(str)			wgetstr(stdscr, str)
E 50
I 50
#define	getstr(s)			wgetstr(stdscr, s)
E 50
#define	inch()				winch(stdscr)
D 53
#define	insch(ch))			winsch(stdscr, ch)
E 53
I 53
#define	insch(ch)			winsch(stdscr, ch)
E 53
#define	insertln()			winsertln(stdscr)
#define	move(y, x)			wmove(stdscr, y, x)
I 55
D 59
#define mvcur(fx, fy, tx, ty)		__mvcur(fx, fy, tx, ty, 0)
E 59
E 55
#define	refresh()			wrefresh(stdscr)
#define	standend()			wstandend(stdscr)
#define	standout()			wstandout(stdscr)
I 50
#define	waddbytes(w, s, n)		__waddbytes(w, s, n, 0)
#define	waddstr(w, s)			__waddbytes(w, s, strlen(s), 0)
E 50
E 45
E 29
E 2

D 2
# ifdef DEBUG
FILE		*outf;		/* error outfile			*/
# endif
E 2
I 2
D 29
extern int	LINES, COLS, _tty_ch, _res_flg;
E 29
I 29
/* Standard screen plus movement pseudo functions. */
D 45
#define	mvaddbytes(y, x, da, co) \
				mvwaddbytes(stdscr, y, x, da, co)
#define	mvaddch(y, x, ch)	mvwaddch(stdscr, y, x, ch)
#define	mvaddstr(y, x, str)	mvwaddstr(stdscr, y, x, str)
#define	mvdelch(y, x)		mvwdelch(stdscr, y, x)
#define	mvgetch(y, x)		mvwgetch(stdscr, y, x)
#define	mvgetstr(y, x, str)	mvwgetstr(stdscr, y, x, str)
#define	mvinch(y, x)		mvwinch(stdscr, y, x)
#define	mvinsch(y, x, c)	mvwinsch(stdscr, y, x, c)
E 45
I 45
D 50
#define	mvaddbytes(y, x, da, co)	mvwaddbytes(stdscr, y, x, da, co)
E 50
I 50
#define	mvaddbytes(y, x, s, n)		mvwaddbytes(stdscr, y, x, s, n)
E 50
#define	mvaddch(y, x, ch)		mvwaddch(stdscr, y, x, ch)
D 50
#define	mvaddstr(y, x, str)		mvwaddstr(stdscr, y, x, str)
E 50
I 50
#define	mvaddnstr(y, x, s, n)		mvwaddnstr(stdscr, y, x, s, n)
#define	mvaddstr(y, x, s)		mvwaddstr(stdscr, y, x, s)
E 50
#define	mvdelch(y, x)			mvwdelch(stdscr, y, x)
#define	mvgetch(y, x)			mvwgetch(stdscr, y, x)
D 50
#define	mvgetstr(y, x, str)		mvwgetstr(stdscr, y, x, str)
E 50
I 50
#define	mvgetstr(y, x, s)		mvwgetstr(stdscr, y, x, s)
E 50
#define	mvinch(y, x)			mvwinch(stdscr, y, x)
#define	mvinsch(y, x, c)		mvwinsch(stdscr, y, x, c)
E 45
D 50
#define	mvwaddbytes(win, y, x, da, co) \
D 45
				(wmove(win, y, x) == ERR ? \
				    ERR : waddbytes(win, da, co))
#define	mvwaddch(win, y, x, ch)	(wmove(win, y, x) == ERR ? \
				    ERR : waddch(win, ch))
E 45
I 45
	(wmove(win, y, x) == ERR ? ERR : waddbytes(win, da, co))
#define	mvwaddch(win, y, x, ch) \
	(wmove(win, y, x) == ERR ? ERR : waddch(win, ch))
E 45
#define	mvwaddstr(win, y, x, str) \
D 45
				(wmove(win, y, x) == ERR ? \
				    ERR : waddbytes(win, str, strlen(str)))
#define	mvwdelch(win, y, x)	(wmove(win, y, x) == ERR ? ERR : wdelch(win))
#define	mvwgetch(win, y, x)	(wmove(win, y, x) == ERR ? ERR : wgetch(win))
E 45
I 45
	(wmove(win, y, x) == ERR ? ERR : waddbytes(win, str, strlen(str)))
#define	mvwdelch(win, y, x) \
	(wmove(win, y, x) == ERR ? ERR : wdelch(win))
#define	mvwgetch(win, y, x) \
	(wmove(win, y, x) == ERR ? ERR : wgetch(win))
E 45
#define	mvwgetstr(win, y, x, str) \
D 45
				(wmove(win, y, x) == ERR ? \
				    ERR : wgetstr(win, str))
#define	mvwinch(win, y, x)	(wmove(win, y, x) == ERR ? ERR : winch(win))
#define	mvwinsch(win, y, x, c)	(wmove(win, y, x) == ERR ? ERR : winsch(win, c))
E 45
I 45
	(wmove(win, y, x) == ERR ? ERR : wgetstr(win, str))
#define	mvwinch(win, y, x) \
	(wmove(win, y, x) == ERR ? ERR : winch(win))
#define	mvwinsch(win, y, x, c) \
	(wmove(win, y, x) == ERR ? ERR : winsch(win, c))
E 50
I 50
#define	mvwaddbytes(w, y, x, s, n) \
	(wmove(w, y, x) == ERR ? ERR : __waddbytes(w, s, n, 0))
#define	mvwaddch(w, y, x, ch) \
	(wmove(w, y, x) == ERR ? ERR : waddch(w, ch))
#define	mvwaddnstr(w, y, x, s, n) \
	(wmove(w, y, x) == ERR ? ERR : waddnstr(w, s, n))
#define	mvwaddstr(w, y, x, s) \
	(wmove(w, y, x) == ERR ? ERR : __waddbytes(w, s, strlen(s), 0))
#define	mvwdelch(w, y, x) \
	(wmove(w, y, x) == ERR ? ERR : wdelch(w))
#define	mvwgetch(w, y, x) \
	(wmove(w, y, x) == ERR ? ERR : wgetch(w))
#define	mvwgetstr(w, y, x, s) \
	(wmove(w, y, x) == ERR ? ERR : wgetstr(w, s))
#define	mvwinch(w, y, x) \
	(wmove(w, y, x) == ERR ? ERR : winch(w))
#define	mvwinsch(w, y, x, c) \
	(wmove(w, y, x) == ERR ? ERR : winsch(w, c))
E 50
E 45
E 29
E 2

D 2
SGTTY		_tty;		/* tty structure			*/
E 2
I 2
D 5
SGTTY		_tty;
E 5
I 5
D 29
extern SGTTY	_tty;
E 29
I 29
D 45
/* Random psuedo functions. */
D 32
#define	clearok(win, bf) 	(win->_clear = (bf))
#define	flushok(win, bf)	((bf) ? (win->_flags |= _FLUSH) : \
				    (win->_flags &= ~_FLUSH))
#define	getyx(win, y, x)	(y) = win->_cury, (x) = win->_curx
#define	leaveok(win, bf)	(win->_leave = (bf))
#define	scrollok(win, bf)	(win->_scroll = (bf))
#define	winch(win)		(win->_y[win->_cury][win->_curx] & 0177)
E 32
I 32
#define	clearok(win, bf)  ((bf) ? (win->flags |= __CLEAROK) : \
				  (win->flags &= ~__CLEAROK))
#define	flushok(win, bf)  ((bf) ? (win->flags |= __FLUSH) : \
				  (win->flags &= ~__FLUSH))
#define	scrollok(win, bf) ((bf) ? (win->flags |= __SCROLLOK) : \
				  (win->flags &= ~__SCROLLOK))
#define	leaveok(win, bf)  ((bf) ? (win->flags |= __LEAVEOK) : \
				  (win->flags &= ~__LEAVEOK))
#define	getyx(win, y, x)	(y) = win->cury, (x) = win->curx
D 39
#define	winch(win)		(win->lines[win->cury]->line[win->curx] & 0177)
E 39
I 39
D 40
#define	winch(win)		(win->lines[win->cury]->line[win->curx]->ch & 0177)
E 40
I 40
#define	winch(win)		(win->lines[win->cury]->line[win->curx].ch & 0177)
E 45
I 45
/* Psuedo functions. */
D 50
#define	clearok(win, bf) \
	((bf) ? (win->flags |= __CLEAROK) : (win->flags &= ~__CLEAROK))
#define	flushok(win, bf) \
	((bf) ? (win->flags |= __FLUSH) : (win->flags &= ~__FLUSH))
#define	getyx(win, y, x) \
	(y) = win->cury, (x) = win->curx
#define	leaveok(win, bf) \
	((bf) ? (win->flags |= __LEAVEOK) : (win->flags &= ~__LEAVEOK))
#define	scrollok(win, bf) \
	((bf) ? (win->flags |= __SCROLLOK) : (win->flags &= ~__SCROLLOK))
#define	winch(win) \
	(win->lines[win->cury]->line[win->curx].ch & 0177)
E 50
I 50
#define	clearok(w, bf) \
	((bf) ? ((w)->flags |= __CLEAROK) : ((w)->flags &= ~__CLEAROK))
#define	flushok(w, bf) \
	((bf) ? ((w)->flags |= __FLUSH) : ((w)->flags &= ~__FLUSH))
#define	getyx(w, y, x) \
	(y) = (w)->cury, (x) = (w)->curx
#define	leaveok(w, bf) \
	((bf) ? ((w)->flags |= __LEAVEOK) : ((w)->flags &= ~__LEAVEOK))
#define	scrollok(w, bf) \
	((bf) ? ((w)->flags |= __SCROLLOK) : ((w)->flags &= ~__SCROLLOK))
#define	winch(w) \
	((w)->lines[(w)->cury]->line[(w)->curx].ch & 0177)
E 50
E 45
E 40
E 39
E 32
E 29
E 5
E 2

D 2
WINDOW		*stdscr,	/* standard screen			*/
		*curscr;	/* current screen			*/
E 2
I 2
D 5
WINDOW		*stdscr, *curscr;
E 5
I 5
D 29
extern WINDOW	*stdscr, *curscr;
E 29
I 29
/* Public function prototypes. */
D 45
void	 __cputchar __P((int));
E 45
D 41
int	 _sprintw __P((WINDOW *, const char *, _BSD_VA_LIST_));
E 41
int	 box __P((WINDOW *, int, int));
int	 cbreak __P((void));
int	 delwin __P((WINDOW *));
int	 echo __P((void));
int	 endwin __P((void));
char	*fullname __P((char *, char *));
char	*getcap __P((char *));
int	 gettmode __P((void));
void	 idlok __P((WINDOW *, int));
WINDOW	*initscr __P((void));
char	*longname __P((char *, char *));
I 59
int	 mvcur __P((int, int, int, int));
E 59
D 57
int	 mvcur __P((int, int, int, int));
E 57
int	 mvprintw __P((int, int, const char *, ...));
int	 mvscanw __P((int, int, const char *, ...));
int	 mvwin __P((WINDOW *, int, int));
int	 mvwprintw __P((WINDOW *, int, int, const char *, ...));
int	 mvwscanw __P((WINDOW *, int, int, const char *, ...));
WINDOW	*newwin __P((int, int, int, int));
int	 nl __P((void));
int	 nocbreak __P((void));
int	 noecho __P((void));
int	 nonl __P((void));
int	 noraw __P((void));
int	 overlay __P((WINDOW *, WINDOW *));
int	 overwrite __P((WINDOW *, WINDOW *));
int	 printw __P((const char *, ...));
int	 raw __P((void));
int	 resetty __P((void));
int	 savetty __P((void));
int	 scanw __P((const char *, ...));
int	 scroll __P((WINDOW *));
int	 setterm __P((char *));
D 41
int	 sscans __P((WINDOW *, const char *, _BSD_VA_LIST_));
E 41
I 41
int	 sscans __P((WINDOW *, const char *, ...));
E 41
WINDOW	*subwin __P((WINDOW *, int, int, int, int));
int	 suspendwin __P((void));
int	 touchline __P((WINDOW *, int, int, int));
int	 touchoverlap __P((WINDOW *, WINDOW *));
int	 touchwin __P((WINDOW *));
D 47
void	 tstp __P((int));
E 47
I 41
int 	 vwprintw __P((WINDOW *, const char *, _BSD_VA_LIST_));
int      vwscanw __P((WINDOW *, const char *, _BSD_VA_LIST_));
I 45
D 49
int	 waddbytes __P((WINDOW *, char *, int));
E 49
I 49
D 50
int	 waddbytes __P((WINDOW *, const char *, int));
E 50
E 49
E 45
E 41
int	 waddch __P((WINDOW *, int));
D 49
int	 waddstr __P((WINDOW *, char *));
E 49
I 49
D 50
int	 waddstr __P((WINDOW *, const char *));
E 50
I 50
int	 waddnstr __P((WINDOW *, const char *, int));
E 50
E 49
int	 wclear __P((WINDOW *));
int	 wclrtobot __P((WINDOW *));
int	 wclrtoeol __P((WINDOW *));
int	 wdelch __P((WINDOW *));
int	 wdeleteln __P((WINDOW *));
int	 werase __P((WINDOW *));
int	 wgetch __P((WINDOW *));
int	 wgetstr __P((WINDOW *, char *));
int	 winsch __P((WINDOW *, int));
int	 winsertln __P((WINDOW *));
int	 wmove __P((WINDOW *, int, int));
int	 wprintw __P((WINDOW *, const char *, ...));
int	 wrefresh __P((WINDOW *));
int	 wscanw __P((WINDOW *, const char *, ...));
D 66
char	*wstandend __P((WINDOW *));
char	*wstandout __P((WINDOW *));
E 66
I 66
int	 wstandend __P((WINDOW *));
int	 wstandout __P((WINDOW *));
E 66
I 45
int	 vwprintw __P((WINDOW *, const char *, _BSD_VA_LIST_));
E 45
E 29
E 5
E 2

I 54
D 58
void	 __cputchar __P((int));		/* Public: backward compatibility */
E 58
I 58
/* Private functions that are needed for user programs prototypes. */
void	 __cputchar __P((int));
D 59
int	 __mvcur __P((int, int, int, int, int));
E 59
int	 __waddbytes __P((WINDOW *, const char *, int, int));
E 58

I 58
/* Private functions. */
E 58
E 54
D 29
/*
 *	Define VOID to stop lint from generating "null effect"
 * comments.
 */
D 23
# ifdef lint
E 23
I 23
#ifdef lint
E 23
D 2
int	__void__;		/* place to assign to			*/
E 2
I 2
int	__void__;
E 2
D 23
# define	VOID(x)	(__void__ = (int) (x))
# else
# define	VOID(x)	(x)
# endif
E 23
I 23
#define	VOID(x)	(__void__ = (int) (x))
#else
#define	VOID(x)	(x)
#endif
E 29
I 29
#ifdef _CURSES_PRIVATE
D 58
/* Private function prototypes. */
E 58
I 45
D 47
void	 __cputchar __P((int));
E 47
E 45
I 37
D 56
void	 __TRACE __P((const char *, ...));
E 56
I 56
void	 __CTRACE __P((const char *, ...));
E 56
I 47
D 54
void	 __cputchar __P((int));
E 54
I 52
u_int	 __hash __P((char *, int));
E 52
E 47
E 37
void	 __id_subwins __P((WINDOW *));
I 59
int	 __mvcur __P((int, int, int, int, int));
I 60
void	 __restore_stophandler __P((void));
void	 __set_stophandler __P((void));
E 60
E 59
I 55
D 58
int	 __mvcur __P((int, int, int, int, int));
E 58
E 55
void	 __set_subwin __P((WINDOW *, WINDOW *));
I 47
void	 __startwin __P((void));
void	 __stop_signal_handler __P((int));
E 47
void	 __swflags __P((WINDOW *));
D 37
void	 __TRACE __P((const char *, ...));
int	 waddbytes __P((WINDOW *, char *, int));
E 37
I 37
int	 __touchline __P((WINDOW *, int, int, int, int));
int	 __touchwin __P((WINDOW *));
E 37
I 33
D 45
char	*tscroll __P((const char *, int));
I 37
int	 waddbytes __P((WINDOW *, char *, int));
E 45
I 45
D 65
char	*__tscroll __P((const char *, int));
E 65
I 65
char	*__tscroll __P((const char *, int, int));
E 65
D 49
int	 __waddbytes __P((WINDOW *, char *, int, int));
E 49
I 49
D 58
int	 __waddbytes __P((WINDOW *, const char *, int, int));
E 58
I 52
int	 __waddch __P((WINDOW *, __LDATA *));
E 52
E 49
E 45
E 37
E 33
E 29
E 23

D 3
# endif

E 3
D 29
/*
 * psuedo functions for standard screen
 */
D 23
# define	addch(ch)	VOID(waddch(stdscr, ch))
# define	getch()		VOID(wgetch(stdscr))
D 19
# define	addstr(str)	VOID(waddstr(stdscr, str))
E 19
I 19
# define	addbytes(da,co)	VOID(waddbytes(stdscr, da,co))
# define	addstr(str)	VOID(waddbytes(stdscr, str, strlen(str)))
E 19
# define	getstr(str)	VOID(wgetstr(stdscr, str))
# define	move(y, x)	VOID(wmove(stdscr, y, x))
# define	clear()		VOID(wclear(stdscr))
# define	erase()		VOID(werase(stdscr))
# define	clrtobot()	VOID(wclrtobot(stdscr))
# define	clrtoeol()	VOID(wclrtoeol(stdscr))
# define	insertln()	VOID(winsertln(stdscr))
# define	deleteln()	VOID(wdeleteln(stdscr))
# define	refresh()	VOID(wrefresh(stdscr))
# define	inch()		VOID(winch(stdscr))
I 7
# define	insch(c)	VOID(winsch(stdscr,c))
I 8
# define	delch()		VOID(wdelch(stdscr))
E 8
E 7
# define	standout()	VOID(wstandout(stdscr))
# define	standend()	VOID(wstandend(stdscr))
E 23
I 23
#define	addch(ch)	VOID(waddch(stdscr, ch))
#define	getch()		VOID(wgetch(stdscr))
#define	addbytes(da,co)	VOID(waddbytes(stdscr, da,co))
#define	addstr(str)	VOID(waddbytes(stdscr, str, strlen(str)))
#define	getstr(str)	VOID(wgetstr(stdscr, str))
#define	move(y, x)	VOID(wmove(stdscr, y, x))
#define	clear()		VOID(wclear(stdscr))
#define	erase()		VOID(werase(stdscr))
#define	clrtobot()	VOID(wclrtobot(stdscr))
#define	clrtoeol()	VOID(wclrtoeol(stdscr))
#define	insertln()	VOID(winsertln(stdscr))
#define	deleteln()	VOID(wdeleteln(stdscr))
#define	refresh()	VOID(wrefresh(stdscr))
#define	inch()		VOID(winch(stdscr))
#define	insch(c)	VOID(winsch(stdscr,c))
#define	delch()		VOID(wdelch(stdscr))
#define	standout()	VOID(wstandout(stdscr))
#define	standend()	VOID(wstandend(stdscr))
E 29
I 29
/* Private #defines. */
#define	min(a,b)	(a < b ? a : b)
#define	max(a,b)	(a > b ? a : b)
E 29
E 23

D 29
/*
 * mv functions
 */
#define	mvwaddch(win,y,x,ch)	VOID(wmove(win,y,x)==ERR?ERR:waddch(win,ch))
#define	mvwgetch(win,y,x)	VOID(wmove(win,y,x)==ERR?ERR:wgetch(win))
D 19
#define	mvwaddstr(win,y,x,str)	VOID(wmove(win,y,x)==ERR?ERR:waddstr(win,str))
E 19
I 19
#define	mvwaddbytes(win,y,x,da,co) \
		VOID(wmove(win,y,x)==ERR?ERR:waddbytes(win,da,co))
#define	mvwaddstr(win,y,x,str) \
		VOID(wmove(win,y,x)==ERR?ERR:waddbytes(win,str,strlen(str)))
E 19
D 10
#define	mvwgetstr(win,y,x)	VOID(wmove(win,y,x)==ERR?ERR:wgetstr(win))
E 10
I 10
#define mvwgetstr(win,y,x,str)  VOID(wmove(win,y,x)==ERR?ERR:wgetstr(win,str))
E 10
#define	mvwinch(win,y,x)	VOID(wmove(win,y,x) == ERR ? ERR : winch(win))
I 8
#define	mvwdelch(win,y,x)	VOID(wmove(win,y,x) == ERR ? ERR : wdelch(win))
E 8
I 7
#define	mvwinsch(win,y,x,c)	VOID(wmove(win,y,x) == ERR ? ERR:winsch(win,c))
E 7
#define	mvaddch(y,x,ch)		mvwaddch(stdscr,y,x,ch)
#define	mvgetch(y,x)		mvwgetch(stdscr,y,x)
I 19
#define	mvaddbytes(y,x,da,co)	mvwaddbytes(stdscr,y,x,da,co)
E 19
#define	mvaddstr(y,x,str)	mvwaddstr(stdscr,y,x,str)
D 10
#define	mvgetstr(y,x)		mvwgetstr(stdscr,y,x)
E 10
I 10
#define mvgetstr(y,x,str)       mvwgetstr(stdscr,y,x,str)
E 10
D 6
#define	mvinch(y,x)		mvwinch(win,y,x)
E 6
I 6
#define	mvinch(y,x)		mvwinch(stdscr,y,x)
I 8
#define	mvdelch(y,x)		mvwdelch(stdscr,y,x)
E 8
I 7
#define	mvinsch(y,x,c)		mvwinsch(stdscr,y,x,c)
E 29
I 29
/* Private externs. */
extern int	 __echoit;
extern int	 __endwin;
extern int	 __pfast;
extern int	 __rawmode;
I 33
extern int	 __noqch;
E 33
#endif
E 29
E 7
E 6

D 29
/*
 * psuedo functions
 */
E 29
I 29
/* Termcap functions. */
int	 tgetent __P((char *, char *));
int	 tgetnum __P((char *));
int	 tgetflag __P((char *));
char	*tgetstr __P((char *, char **));
char	*tgoto __P((char *, int, int));
int	 tputs __P((char *, int, void (*)(int)));
E 29

D 29
#define	clearok(win,bf)	 (win->_clear = bf)
#define	leaveok(win,bf)	 (win->_leave = bf)
#define	scrollok(win,bf) (win->_scroll = bf)
#define flushok(win,bf)	 (bf ? (win->_flags |= _FLUSH):(win->_flags &= ~_FLUSH))
#define	getyx(win,y,x)	 y = win->_cury, x = win->_curx
D 12
#define	winch(win)	 (win->_y[win->_cury][win->_curx])
E 12
I 12
#define	winch(win)	 (win->_y[win->_cury][win->_curx] & 0177)
E 12

D 22
#define raw()	 (_tty.sg_flags|=RAW, _pfast=_rawmode=TRUE, stty(_tty_ch,&_tty))
#define noraw()	 (_tty.sg_flags&=~RAW,_rawmode=FALSE,_pfast=!(_tty.sg_flags&CRMOD),stty(_tty_ch,&_tty))
D 16
#define crmode() (_tty.sg_flags |= CBREAK, _rawmode = TRUE, stty(_tty_ch,&_tty))
#define nocrmode() (_tty.sg_flags &= ~CBREAK,_rawmode=FALSE,stty(_tty_ch,&_tty))
E 16
I 16
#define cbreak() (_tty.sg_flags |= CBREAK, _rawmode = TRUE, stty(_tty_ch,&_tty))
#define nocbreak() (_tty.sg_flags &= ~CBREAK,_rawmode=FALSE,stty(_tty_ch,&_tty))
E 22
I 22
#define raw()	 (_tty.sg_flags|=RAW, _pfast=_rawmode=TRUE, \
	ioctl(_tty_ch, TIOCSETP, &_tty))
#define noraw()	 (_tty.sg_flags&=~RAW,_rawmode=FALSE,\
	_pfast=!(_tty.sg_flags&CRMOD),ioctl(_tty_ch, TIOCSETP, &_tty))
#define cbreak() (_tty.sg_flags |= CBREAK, _rawmode = TRUE, \
	ioctl(_tty_ch, TIOCSETP, &_tty))
#define nocbreak() (_tty.sg_flags &= ~CBREAK,_rawmode=FALSE, \
	ioctl(_tty_ch, TIOCSETP, &_tty))
E 22
#define crmode() cbreak()	/* backwards compatability */
#define nocrmode() nocbreak()	/* backwards compatability */
E 16
D 22
#define echo()	 (_tty.sg_flags |= ECHO, _echoit = TRUE, stty(_tty_ch, &_tty))
#define noecho() (_tty.sg_flags &= ~ECHO, _echoit = FALSE, stty(_tty_ch, &_tty))
#define nl()	 (_tty.sg_flags |= CRMOD,_pfast = _rawmode,stty(_tty_ch, &_tty))
#define nonl()	 (_tty.sg_flags &= ~CRMOD, _pfast = TRUE, stty(_tty_ch, &_tty))
D 16
#define	savetty() (gtty(_tty_ch, &_tty), _res_flg = _tty.sg_flags)
#define	resetty() (_tty.sg_flags = _res_flg, stty(_tty_ch, &_tty))
E 16
I 16
#define	savetty() ((void) gtty(_tty_ch, &_tty), _res_flg = _tty.sg_flags)
#define	resetty() (_tty.sg_flags = _res_flg, (void) stty(_tty_ch, &_tty))
E 22
I 22
#define echo()	 (_tty.sg_flags |= ECHO, _echoit = TRUE, \
	ioctl(_tty_ch, TIOCSETP, &_tty))
#define noecho() (_tty.sg_flags &= ~ECHO, _echoit = FALSE, \
	ioctl(_tty_ch, TIOCSETP, &_tty))
#define nl()	 (_tty.sg_flags |= CRMOD,_pfast = _rawmode, \
	ioctl(_tty_ch, TIOCSETP, &_tty))
#define nonl()	 (_tty.sg_flags &= ~CRMOD, _pfast = TRUE, \
	ioctl(_tty_ch, TIOCSETP, &_tty))
#define	savetty() ((void) ioctl(_tty_ch, TIOCGETP, &_tty), \
	_res_flg = _tty.sg_flags)
#define	resetty() (_tty.sg_flags = _res_flg, \
I 26
	_echoit = ((_res_flg & ECHO) == ECHO), \
	_rawmode = ((_res_flg & (CBREAK|RAW)) != 0), \
	_pfast = ((_res_flg & CRMOD) ? _rawmode : TRUE), \
E 26
	(void) ioctl(_tty_ch, TIOCSETP, &_tty))
E 22

#define	erasechar()	(_tty.sg_erase)
#define	killchar()	(_tty.sg_kill)
#define baudrate()	(_tty.sg_ospeed)
E 16

WINDOW	*initscr(), *newwin(), *subwin();
I 2
D 9
char	*longname();
E 9
I 9
char	*longname(), *getcap();
E 9
I 3

I 14
/*
 * Used to be in unctrl.h.
 */
#define	unctrl(c)	_unctrl[(c) & 0177]
I 15
extern char *_unctrl[];
E 15
E 14
D 23
# endif
E 23
I 23
#endif
E 29
I 29
#endif /* !_CURSES_H_ */
E 29
E 23
E 3
E 2
E 1
