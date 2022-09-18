h57557
s 00002/00002/00076
d D 8.1 93/05/31 14:45:41 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00076
d D 5.8 93/04/29 12:40:29 bostic 8 7
c prettiness police
e
s 00001/00000/00075
d D 5.7 92/03/01 13:22:09 bostic 7 6
c lint
e
s 00017/00016/00058
d D 5.6 92/01/29 16:13:32 elan 6 5
c Changed comparison fns to conform to new version using fts(3) structs.
e
s 00018/00009/00056
d D 5.5 91/10/28 15:45:19 bostic 5 4
c It's a brave new ANSI world!
e
s 00006/00006/00059
d D 5.4 91/03/08 18:19:09 bostic 4 3
c sort orders on times were reversed
e
s 00006/00006/00059
d D 5.3 91/03/07 21:50:26 bostic 3 2
c comparison functions returned a boolean, not integer difference
e
s 00001/00011/00064
d D 5.2 90/04/08 17:41:40 bostic 2 1
c get redist notice from /usr/share/misc
e
s 00072/00000/00000
d D 5.1 89/06/24 18:19:53 bostic 1 0
c date and time created 89/06/24 18:19:53 by bostic
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
 * Michael Fischbein.
 *
D 2
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
E 2
I 2
D 5
%sccs.include.redist.c%
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>
I 8

E 8
I 6
#include <fts.h>
I 7
#include <string.h>
I 8

E 8
E 7
E 6
#include "ls.h"
I 5
#include "extern.h"
E 5

I 5
int
E 5
namecmp(a, b)
D 6
	LS *a, *b;
E 6
I 6
	const FTSENT *a, *b;
E 6
{
D 5
	return(strcmp(a->name, b->name));
E 5
I 5
D 6
	return (strcmp(a->name, b->name));
E 6
I 6
	return (strcmp(a->fts_name, b->fts_name));
E 6
E 5
}

I 5
int
E 5
revnamecmp(a, b)
D 6
	LS *a, *b;
E 6
I 6
	const FTSENT *a, *b;
E 6
{
D 5
	return(strcmp(b->name, a->name));
E 5
I 5
D 6
	return (strcmp(b->name, a->name));
E 6
I 6
	return (strcmp(b->fts_name, a->fts_name));
E 6
E 5
}

I 5
int
E 5
modcmp(a, b)
D 6
	LS *a, *b;
E 6
I 6
	const FTSENT *a, *b;
E 6
{
D 3
	return(a->lstat.st_mtime < b->lstat.st_mtime);
E 3
I 3
D 4
	return(a->lstat.st_mtime - b->lstat.st_mtime);
E 4
I 4
D 5
	return(b->lstat.st_mtime - a->lstat.st_mtime);
E 5
I 5
D 6
	return (b->lstat.st_mtime - a->lstat.st_mtime);
E 6
I 6
	return (b->fts_statp->st_mtime - a->fts_statp->st_mtime);
E 6
E 5
E 4
E 3
}

I 5
int
E 5
revmodcmp(a, b)
D 6
	LS *a, *b;
E 6
I 6
	const FTSENT *a, *b;
E 6
{
D 3
	return(b->lstat.st_mtime < a->lstat.st_mtime);
E 3
I 3
D 4
	return(b->lstat.st_mtime - a->lstat.st_mtime);
E 4
I 4
D 5
	return(a->lstat.st_mtime - b->lstat.st_mtime);
E 5
I 5
D 6
	return (a->lstat.st_mtime - b->lstat.st_mtime);
E 6
I 6
	return (a->fts_statp->st_mtime - b->fts_statp->st_mtime);
E 6
E 5
E 4
E 3
}

I 5
int
E 5
acccmp(a, b)
D 6
	LS *a, *b;
E 6
I 6
	const FTSENT *a, *b;
E 6
{
D 3
	return(a->lstat.st_atime < b->lstat.st_atime);
E 3
I 3
D 4
	return(a->lstat.st_atime - b->lstat.st_atime);
E 4
I 4
D 5
	return(b->lstat.st_atime - a->lstat.st_atime);
E 5
I 5
D 6
	return (b->lstat.st_atime - a->lstat.st_atime);
E 6
I 6
	return (b->fts_statp->st_atime - a->fts_statp->st_atime);
E 6
E 5
E 4
E 3
}

I 5
int
E 5
revacccmp(a, b)
D 6
	LS *a, *b;
E 6
I 6
	const FTSENT *a, *b;
E 6
{
D 3
	return(b->lstat.st_atime < a->lstat.st_atime);
E 3
I 3
D 4
	return(b->lstat.st_atime - a->lstat.st_atime);
E 4
I 4
D 5
	return(a->lstat.st_atime - b->lstat.st_atime);
E 5
I 5
D 6
	return (a->lstat.st_atime - b->lstat.st_atime);
E 6
I 6
	return (a->fts_statp->st_atime - b->fts_statp->st_atime);
E 6
E 5
E 4
E 3
}

I 5
int
E 5
statcmp(a, b)
D 6
	LS *a, *b;
E 6
I 6
	const FTSENT *a, *b;
E 6
{
D 3
	return(a->lstat.st_ctime < b->lstat.st_ctime);
E 3
I 3
D 4
	return(a->lstat.st_ctime - b->lstat.st_ctime);
E 4
I 4
D 5
	return(b->lstat.st_ctime - a->lstat.st_ctime);
E 5
I 5
D 6
	return (b->lstat.st_ctime - a->lstat.st_ctime);
E 6
I 6
	return (b->fts_statp->st_ctime - a->fts_statp->st_ctime);
E 6
E 5
E 4
E 3
}

I 5
int
E 5
revstatcmp(a, b)
D 6
	LS *a, *b;
E 6
I 6
	const FTSENT *a, *b;
E 6
{
D 3
	return(b->lstat.st_ctime < a->lstat.st_ctime);
E 3
I 3
D 4
	return(b->lstat.st_ctime - a->lstat.st_ctime);
E 4
I 4
D 5
	return(a->lstat.st_ctime - b->lstat.st_ctime);
E 5
I 5
D 6
	return (a->lstat.st_ctime - b->lstat.st_ctime);
E 6
I 6
	return (a->fts_statp->st_ctime - b->fts_statp->st_ctime);
E 6
E 5
E 4
E 3
}
E 1
