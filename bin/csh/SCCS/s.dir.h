h25571
s 00002/00002/00017
d D 8.1 93/05/31 16:41:42 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00019
d D 5.6 93/05/22 19:06:23 christos 8 7
c Fixed gcc -Wall warnings
e
s 00000/00000/00019
d D 5.5 91/07/19 17:30:35 christos 7 6
c stdio based version; brace glob fix; builtin prototypes
e
s 00005/00005/00014
d D 5.4 91/06/04 13:31:19 bostic 6 5
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00005/00004/00014
d D 5.3 91/04/04 18:17:34 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00001/00017
d D 5.2 85/06/06 13:09:42 edward 4 3
c cleaning up after bozos
e
s 00007/00001/00011
d D 5.1 85/06/04 11:10:32 dist 3 2
c Add copyright
e
s 00001/00001/00011
d D 4.2 84/12/13 14:39:59 edward 2 1
c performance
e
s 00012/00000/00000
d D 4.1 80/10/09 12:40:32 bill 1 0
c date and time created 80/10/09 12:40:32 by bill
e
u
U
t
T
I 1
D 2
/* %M% %I% %G% */
E 2
I 2
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
D 5
/*
 * Copyright (c) 1980 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
E 4
I 4
 * All rights reserved.  The Berkeley Software License Agreement
E 4
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
D 9
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */
E 3
E 2

/*
 * Structure for entries in directory stack.
 */
D 6
struct	directory	{
	struct	directory *di_next;	/* next in loop */
	struct	directory *di_prev;	/* prev in loop */
	unsigned short *di_count;	/* refcount of processes */
	char	*di_name;		/* actual name */
E 6
I 6
struct directory {
    struct directory *di_next;	/* next in loop */
    struct directory *di_prev;	/* prev in loop */
    unsigned short *di_count;	/* refcount of processes */
    Char   *di_name;		/* actual name */
E 6
};
struct directory *dcwd;		/* the one we are in now */
E 1
