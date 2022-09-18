h12336
s 00001/00001/00018
d D 8.3 94/04/02 10:06:57 pendry 4 3
c add 1994 copyright
e
s 00004/00001/00015
d D 8.2 94/04/01 07:42:22 pendry 3 2
c prettyness police
e
s 00002/00002/00014
d D 8.1 93/06/06 14:27:53 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00000/00000
d D 5.1 91/10/27 14:14:51 bostic 1 0
c date and time created 91/10/27 14:14:51 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
D 4
 * Copyright (c) 1991, 1993
E 4
I 4
 * Copyright (c) 1991, 1993, 1994
E 4
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 3
#define OK_EXIT		0
#define DIFF_EXIT	1
#define ERR_EXIT	2	/* error exit code */

E 3
void	c_regular __P((int, char *, off_t, off_t, int, char *, off_t, off_t));
void	c_special __P((int, char *, off_t, int, char *, off_t));
void	diffmsg __P((char *, char *, off_t, off_t));
void	eofmsg __P((char *));
D 3
void	err __P((const char *fmt, ...));
E 3

extern int lflag, sflag;
E 1
