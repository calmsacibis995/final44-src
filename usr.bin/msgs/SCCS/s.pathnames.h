h39990
s 00002/00002/00012
d D 8.1 93/06/06 15:39:16 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00013
d D 5.3 90/06/01 17:05:38 bostic 5 4
c new copyright notice
e
s 00019/00010/00005
d D 5.2 89/05/11 10:02:22 bostic 4 3
c file reorg, pathnames.h, paths.h
e
s 00007/00001/00008
d D 5.1 85/06/04 15:29:55 dist 3 2
c Add copyright
e
s 00002/00003/00007
d D 4.2 83/08/11 22:39:16 sam 2 1
c standardize sccs keyword lines
e
s 00010/00000/00000
d D 4.1 82/05/19 10:14:30 rrh 1 0
c date and time created 82/05/19 10:14:30 by rrh
e
u
U
t
T
I 1
D 2
/*
 *	%W% %G%
 */
E 2
I 2
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
E 4
 *
I 4
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
E 4
 *	%W% (Berkeley) %G%
 */
E 3

E 2
D 4
/*
 * Local definitions for msgs.
 */

#define USRMSGS	"/usr/msgs"		/* msgs directory */
#define MAIL	"/usr/ucb/Mail -f %s"	/* could set destination also */
#define PAGE	"/usr/ucb/more -%d"	/* crt screen paging program */
E 4
I 4
#define	_PATH_MSGS	"/var/msgs"
#define	_PATH_MAIL	"/usr/bin/Mail -f %s"
#define	_PATH_PAGER	"/usr/bin/more -%d"
#undef _PATH_TMP
#define	_PATH_TMP	"/tmp/msgXXXXXX"
E 4
E 1
