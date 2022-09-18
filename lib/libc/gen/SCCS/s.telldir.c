h64697
s 00002/00002/00100
d D 8.1 93/06/04 12:06:11 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00002/00101
d D 5.10 92/06/24 12:15:39 bostic 16 15
c lseek takes a quad
e
s 00003/00001/00100
d D 5.9 91/02/23 19:50:08 donn 15 14
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00100
d D 5.8 90/06/01 14:16:36 bostic 14 13
c new copyright notice
e
s 00001/00000/00110
d D 5.7 90/01/30 17:50:16 mckusick 13 12
c have to set both seek and loc pointers
e
s 00069/00003/00041
d D 5.6 89/07/11 18:12:07 mckusick 12 11
c update for global telldir list
e
s 00011/00002/00033
d D 5.5 89/07/10 15:15:52 mckusick 11 10
c update to use getdirentries
e
s 00001/00001/00034
d D 5.4 89/01/11 16:44:45 mckusick 10 9
c modifications to use POSIX defined <dirent.h>
e
s 00014/00003/00021
d D 5.3 88/06/18 15:12:29 bostic 9 8
c install approved copyright notice
e
s 00002/00002/00022
d D 5.2 86/03/09 19:59:55 donn 8 7
c added LIBC_SCCS condition for sccs ids
e
s 00007/00001/00017
d D 5.1 85/05/30 10:52:21 dist 7 6
c Add copyright
e
s 00004/00004/00014
d D 4.5 83/07/01 18:33:04 sam 6 5
c include fixes
e
s 00002/00000/00016
d D 4.4 83/04/02 18:47:54 mckusick 5 4
c declare lseek to return a long
e
s 00001/00001/00015
d D 4.3 82/05/07 20:38:04 mckusick 4 3
c update to new fs
e
s 00001/00001/00015
d D 4.2 82/03/30 13:15:34 mckusic 3 2
c convert to DEV_BSIZE size directory blocks
e
s 00000/00000/00016
d D 4.1 82/02/21 14:49:30 mckusic 2 1
c convert to version number 4.x
e
s 00016/00000/00000
d D 1.1 82/02/21 14:47:03 mckusick 1 0
c date and time created 82/02/21 14:47:03 by mckusick
e
u
U
t
T
I 7
/*
D 17
 * Copyright (c) 1983 Regents of the University of California.
D 9
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
D 14
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 9
 */

E 7
I 1
D 6
/* Copyright (c) 1982 Regents of the University of California */
E 6
I 6
D 8
#ifndef lint
E 8
I 8
#if defined(LIBC_SCCS) && !defined(lint)
E 8
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif
E 7
I 7
D 8
#endif not lint
E 8
I 8
D 9
#endif LIBC_SCCS and not lint
E 9
I 9
#endif /* LIBC_SCCS and not lint */
E 9
E 8
E 7
E 6

D 6
static char sccsid[] = "%Z%%M% %I% %G%";

E 6
D 3
#include <sys/types.h>
E 3
I 3
#include <sys/param.h>
E 3
D 4
#include <ndir.h>
E 4
I 4
D 6
#include <dir.h>
E 6
I 6
D 10
#include <sys/dir.h>
E 10
I 10
#include <dirent.h>
I 15
#include <stdlib.h>
#include <unistd.h>
E 15
E 10
E 6
E 4

/*
I 12
 * The option SINGLEUSE may be defined to say that a telldir
 * cookie may be used only once before it is freed. This option
 * is used to avoid having memory usage grow without bound.
 */
#define SINGLEUSE

/*
 * One of these structures is malloced to describe the current directory
 * position each time telldir is called. It records the current magic 
 * cookie returned by getdirentries and the offset within the buffer
 * associated with that return value.
 */
struct ddloc {
	struct	ddloc *loc_next;/* next structure in list */
	long	loc_index;	/* key associated with structure */
	long	loc_seek;	/* magic cookie returned by getdirentries */
	long	loc_loc;	/* offset of entry in buffer */
};

#define	NDIRHASH	32	/* Num of hash lists, must be a power of 2 */
#define	LOCHASH(i)	((i)&(NDIRHASH-1))

static long	dd_loccnt;	/* Index of entry for sequential readdir's */
static struct	ddloc *dd_hash[NDIRHASH];   /* Hash list heads for ddlocs */

/*
E 12
 * return a pointer into a directory
 */
long
telldir(dirp)
D 15
	DIR *dirp;
E 15
I 15
	const DIR *dirp;
E 15
{
I 5
D 11
	extern long lseek();
E 11
I 11
	register int index;
	register struct ddloc *lp;
E 11

E 5
D 11
	return (lseek(dirp->dd_fd, 0L, 1) - dirp->dd_size + dirp->dd_loc);
E 11
I 11
	if ((lp = (struct ddloc *)malloc(sizeof(struct ddloc))) == NULL)
		return (-1);
D 12
	index = dirp->dd_loccnt++;
E 12
I 12
	index = dd_loccnt++;
E 12
	lp->loc_index = index;
	lp->loc_seek = dirp->dd_seek;
	lp->loc_loc = dirp->dd_loc;
D 12
	lp->loc_next = dirp->dd_hash[LOCHASH(index)];
	dirp->dd_hash[LOCHASH(index)] = lp;
E 12
I 12
	lp->loc_next = dd_hash[LOCHASH(index)];
	dd_hash[LOCHASH(index)] = lp;
E 12
	return (index);
I 12
}

/*
 * seek to an entry in a directory.
 * Only values returned by "telldir" should be passed to seekdir.
 */
void
_seekdir(dirp, loc)
	register DIR *dirp;
	long loc;
{
	register struct ddloc *lp;
	register struct ddloc **prevlp;
	struct dirent *dp;
D 16
	extern long lseek();
E 16

	prevlp = &dd_hash[LOCHASH(loc)];
	lp = *prevlp;
	while (lp != NULL) {
		if (lp->loc_index == loc)
			break;
		prevlp = &lp->loc_next;
		lp = lp->loc_next;
	}
	if (lp == NULL)
		return;
	if (lp->loc_loc == dirp->dd_loc && lp->loc_seek == dirp->dd_seek)
		goto found;
D 16
	(void) lseek(dirp->dd_fd, lp->loc_seek, 0);
E 16
I 16
	(void) lseek(dirp->dd_fd, (off_t)lp->loc_seek, SEEK_SET);
E 16
I 13
	dirp->dd_seek = lp->loc_seek;
E 13
	dirp->dd_loc = 0;
	while (dirp->dd_loc < lp->loc_loc) {
		dp = readdir(dirp);
		if (dp == NULL)
			break;
	}
found:
#ifdef SINGLEUSE
	*prevlp = lp->loc_next;
	free((caddr_t)lp);
#endif
E 12
E 11
}
E 1
