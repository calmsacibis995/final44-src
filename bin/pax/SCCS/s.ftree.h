h13819
s 00002/00002/00022
d D 8.1 93/05/31 14:52:50 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00000/00000
d D 1.1 92/12/13 22:51:35 muller 1 0
c date and time created 92/12/13 22:51:35 by muller
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Keith Muller.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Keith Muller of the University of California, San Diego.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Data structure used by the ftree.c routines to store the file args to be
 * handed to fts(). It keeps a reference count of which args generated a
 * "selected" member
 */

typedef struct ftree {
	char		*fname;		/* file tree name */
	int		refcnt;		/* has tree had a selected file? */
	struct ftree	*fow;		/* pointer to next entry on list */
} FTREE;
E 1
