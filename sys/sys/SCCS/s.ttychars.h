h04920
s 00003/00003/00034
d D 8.2 94/01/04 16:16:53 bostic 16 15
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00035
d D 8.1 93/06/02 19:56:11 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00007/00030
d D 7.6 91/05/09 20:55:52 bostic 14 13
c new copyright; att/bsd/shared
e
s 00003/00003/00034
d D 7.5 91/02/05 17:03:21 bostic 13 12
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00006/00008/00031
d D 7.4 89/11/20 18:10:19 marc 12 11
c posix
e
s 00006/00017/00033
d D 7.3 88/10/18 15:23:51 marc 11 10
c new terminal driver
e
s 00012/00012/00038
d D 7.2 87/12/18 11:28:13 bostic 10 9
c fix for ANSI C
e
s 00001/00001/00049
d D 7.1 86/06/04 23:30:18 mckusick 9 8
c 4.3BSD release version
e
s 00007/00001/00043
d D 6.2 85/06/08 15:10:54 mckusick 8 7
c Add copyright
e
s 00000/00000/00044
d D 6.1 83/07/29 06:14:37 sam 7 6
c 4.2 distribution
e
s 00003/00003/00041
d D 4.6 83/07/01 02:25:05 root 6 5
c purge #if sun's
e
s 00003/00003/00041
d D 4.5 83/06/20 20:54:09 root 5 4
c standards are hard to break, sigh
e
s 00000/00007/00044
d D 4.4 83/05/27 13:57:48 sam 4 3
c old goes the old, in comes the new
e
s 00007/00000/00044
d D 4.3 83/05/18 02:42:23 sam 3 2
c sun changes
e
s 00005/00003/00039
d D 4.2 82/12/05 21:54:08 sam 2 1
c handle multiple #include's cleanly
e
s 00042/00000/00000
d D 4.1 82/12/02 11:26:55 sam 1 0
c date and time created 82/12/02 11:26:55 by sam
e
u
U
t
T
I 1
D 8
/*	%M%	%I%	%E%	*/
E 8
I 8
D 14
/*
D 9
 * Copyright (c) 1982 Regents of the University of California.
E 9
I 9
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 9
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
/*-
D 15
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
E 14
 *
D 12
 *	%W% (Berkeley) %G%
E 12
I 12
D 14
 *	@(#)ttychars.h	7.3 (Berkeley) 10/18/88
E 14
I 14
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
E 14
E 12
 */
E 8

/*
I 12
 * 4.3 COMPATIBILITY FILE
 *
E 12
D 14
 * User visible structures and constants
 * related to terminal handling.
E 14
I 14
 * User visible structures and constants related to terminal handling.
E 14
 */
D 2

E 2
I 2
D 13
#ifndef _TTYCHARS_
#define	_TTYCHARS_
E 13
I 13
D 16
#ifndef _TTYCHARS_H_
#define	_TTYCHARS_H_
E 16
I 16
#ifndef _SYS_TTYCHARS_H_
#define	_SYS_TTYCHARS_H_
E 16
E 13
I 11

E 11
E 2
struct ttychars {
	char	tc_erase;	/* erase last character */
	char	tc_kill;	/* erase entire line */
	char	tc_intrc;	/* interrupt */
	char	tc_quitc;	/* quit */
	char	tc_startc;	/* start output */
	char	tc_stopc;	/* stop output */
	char	tc_eofc;	/* end-of-file */
	char	tc_brkc;	/* input delimiter (like nl) */
	char	tc_suspc;	/* stop process signal */
	char	tc_dsuspc;	/* delayed stop process signal */
	char	tc_rprntc;	/* reprint line */
	char	tc_flushc;	/* flush output (toggles) */
	char	tc_werasc;	/* word erase */
	char	tc_lnextc;	/* literal next character */
};
D 12

D 10
#define	CTRL(c)	('c'&037)
E 10
I 10
D 11
#define	CTRL(c)	(c&037)
E 11
I 11
#ifdef KERNEL
#include "ttydefaults.h"
#else
#include <sys/ttydefaults.h>
E 12
I 12
#ifdef USE_OLD_TTY
#include <sys/ttydefaults.h>	/* to pick up character defaults */
E 12
#endif
E 11
E 10
D 12

D 11
/* default special characters */
I 3
D 4
#ifdef vax
E 3
#define	CERASE	'#'
#define	CKILL	'@'
D 2
#define	CINTR	0177		/* DEL */
#define	CQUIT	034		/* FS, cntl shift L */
E 2
I 2
#define	CINTR	0177		/* DEL, ^? */
I 3
#endif
#ifdef sun
E 4
D 5
#define	CERASE	0177		/* DEL */
#define	CKILL	CTRL(u)
#define	CINTR	CTRL(c)
E 5
I 5
D 6
#define	CERASE	'#'
#define	CKILL	'@'
#define	CINTR	0177		/* DEL, ^? */
E 6
I 6
#define	CERASE	0177
D 10
#define	CKILL	CTRL(u)
#define	CINTR	CTRL(c)
E 10
I 10
#define	CKILL	CTRL('u')
#define	CINTR	CTRL('c')
E 10
E 6
E 5
D 4
#endif
E 4
E 3
#define	CQUIT	034		/* FS, ^\ */
E 2
D 10
#define	CSTART	CTRL(q)
#define	CSTOP	CTRL(s)
#define	CEOF	CTRL(d)
E 10
I 10
#define	CSTART	CTRL('q')
#define	CSTOP	CTRL('s')
#define	CEOF	CTRL('d')
E 10
#define	CEOT	CEOF
#define	CBRK	0377
D 10
#define	CSUSP	CTRL(z)
#define	CDSUSP	CTRL(y)
#define	CRPRNT	CTRL(r)
#define	CFLUSH	CTRL(o)
#define	CWERASE	CTRL(w)
#define	CLNEXT	CTRL(v)
E 10
I 10
#define	CSUSP	CTRL('z')
#define	CDSUSP	CTRL('y')
#define	CRPRNT	CTRL('r')
#define	CFLUSH	CTRL('o')
#define	CWERASE	CTRL('w')
#define	CLNEXT	CTRL('v')
E 11
E 10
I 2
#endif
E 12
I 12
D 13
#endif /* _TTYCHARS */
E 13
I 13
D 16
#endif /* !_TTYCHARS_H_ */
E 16
I 16
#endif /* !_SYS_TTYCHARS_H_ */
E 16
E 13
E 12
E 2
E 1
