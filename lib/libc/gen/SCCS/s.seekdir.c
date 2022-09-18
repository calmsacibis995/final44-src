h18514
s 00002/00002/00024
d D 8.1 93/06/04 12:04:51 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00025
d D 5.7 90/06/01 14:14:10 bostic 19 18
c new copyright notice
e
s 00004/00023/00032
d D 5.6 89/07/11 18:11:33 mckusick 18 17
c stub to call to real seekdir located in telldir.c
e
s 00012/00007/00043
d D 5.5 89/07/10 15:15:51 mckusick 17 16
c update to use getdirentries
e
s 00002/00002/00048
d D 5.4 89/01/11 16:44:43 mckusick 16 15
c modifications to use POSIX defined <dirent.h>
e
s 00014/00003/00036
d D 5.3 88/06/18 15:12:28 bostic 15 14
c install approved copyright notice
e
s 00002/00002/00037
d D 5.2 86/03/09 19:54:54 donn 14 13
c added LIBC_SCCS condition for sccs ids
e
s 00007/00001/00032
d D 5.1 85/05/30 10:50:23 dist 13 12
c Add copyright
e
s 00004/00004/00029
d D 4.10 83/07/01 18:32:56 sam 12 11
c include fixes
e
s 00002/00001/00031
d D 4.9 83/03/25 09:44:30 mckusick 11 10
c lint
e
s 00001/00005/00031
d D 4.8 83/03/21 15:28:08 mckusick 10 9
c get rid of incorrect code reintroduced in 4.7
e
s 00004/00000/00032
d D 4.7 82/11/14 13:59:12 sam 9 8
c merge of 4.1b and 4.1c
e
s 00000/00004/00032
d D 4.6 82/09/12 18:33:19 mckusick 8 7
c remove unsafe optimization (might never read newe info)
e
s 00001/00001/00035
d D 4.5 82/05/07 20:37:10 mckusick 7 6
c update to new fs
e
s 00001/00001/00035
d D 4.4 82/03/30 13:15:31 mckusic 6 5
c convert to DEV_BSIZE size directory blocks
e
s 00001/00001/00035
d D 4.3 82/02/25 18:25:50 mckusic 5 4
c must force reading if file has been reopened
e
s 00019/00004/00017
d D 4.2 82/02/24 14:43:30 mckusic 4 3
c protect against seeks to directories that have been compacted in the interim
e
s 00000/00000/00021
d D 4.1 82/02/21 14:49:24 mckusic 3 2
c convert to version number 4.x
e
s 00009/00005/00012
d D 1.2 82/02/21 14:46:22 mckusic 2 1
c convert from resetdir to more general seekdir
e
s 00017/00000/00000
d D 1.1 82/02/11 12:01:42 mckusick 1 0
c date and time created 82/02/11 12:01:42 by mckusick
e
u
U
t
T
I 13
/*
D 20
 * Copyright (c) 1983 Regents of the University of California.
D 15
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 19
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
E 19
I 19
 * %sccs.include.redist.c%
E 19
E 15
 */

E 13
I 1
D 12
/* Copyright (c) 1982 Regents of the University of California */
E 12
I 12
D 14
#ifndef lint
E 14
I 14
#if defined(LIBC_SCCS) && !defined(lint)
E 14
static char sccsid[] = "%W% (Berkeley) %G%";
D 13
#endif
E 13
I 13
D 14
#endif not lint
E 14
I 14
D 15
#endif LIBC_SCCS and not lint
E 15
I 15
#endif /* LIBC_SCCS and not lint */
E 15
E 14
E 13
E 12

D 12
static char sccsid[] = "%Z%%M% %I% %G%";

E 12
D 6
#include <sys/types.h>
E 6
I 6
#include <sys/param.h>
E 6
D 7
#include <ndir.h>
E 7
I 7
D 12
#include <dir.h>
E 12
I 12
D 16
#include <sys/dir.h>
E 16
I 16
#include <dirent.h>
E 16
E 12
E 7

/*
D 2
 * reset a directory.
E 2
I 2
D 18
 * seek to an entry in a directory.
D 10
 * Only values returned by ``telldir'' should be passed to seekdir.
E 10
I 10
 * Only values returned by "telldir" should be passed to seekdir.
E 18
I 18
 * Seek to an entry in a directory.
 * _seekdir is in telldir.c so that it can share opaque data structures.
E 18
E 10
E 2
 */
void
D 2
resetdir(dirp)
	DIR *dirp;
E 2
I 2
seekdir(dirp, loc)
D 18
	register DIR *dirp;
E 18
I 18
	DIR *dirp;
E 18
	long loc;
E 2
{
D 2
	lseek(dirp->dd_fd, (long)0, 0);
	dirp->dd_loc = 0;
E 2
I 2
D 4
	lseek(dirp->dd_fd, loc & ~(DIRBLKSIZ - 1), 0);
	dirp->dd_loc = loc % DIRBLKSIZ;
	if (dirp->dd_loc != 0)
		dirp->dd_size = read(dirp->dd_fd, dirp->dd_buf, DIRBLKSIZ);
E 4
I 4
D 17
	long curloc, base, offset;
E 17
I 17
D 18
	register struct ddloc *lp;
E 17
D 16
	struct direct *dp;
E 16
I 16
	struct dirent *dp;
E 16
I 11
	extern long lseek();
E 18
E 11

D 17
	curloc = telldir(dirp);
	if (loc == curloc)
E 17
I 17
D 18
	lp = dirp->dd_hash[LOCHASH(loc)];
	while (lp != NULL) {
		if (lp->loc_index == loc)
			break;
		lp = lp->loc_next;
	}
	if (lp == NULL)
E 17
		return;
D 17
	base = loc & ~(DIRBLKSIZ - 1);
	offset = loc & (DIRBLKSIZ - 1);
I 9
D 10
	if (dirp->dd_loc != 0 && (curloc & ~(DIRBLKSIZ - 1)) == base) {
		dirp->dd_loc = offset;
		return;
	}
E 10
E 9
D 5
	if ((curloc & ~(DIRBLKSIZ - 1)) == base) {
E 5
I 5
D 8
	if (dirp->dd_loc != 0 && (curloc & ~(DIRBLKSIZ - 1)) == base) {
E 5
		dirp->dd_loc = offset;
		return;
	}
E 8
D 11
	lseek(dirp->dd_fd, base, 0);
E 11
I 11
	(void) lseek(dirp->dd_fd, base, 0);
E 17
I 17
	if (lp->loc_loc == dirp->dd_loc && lp->loc_seek == dirp->dd_seek)
		return;
	(void) lseek(dirp->dd_fd, lp->loc_seek, 0);
E 17
E 11
	dirp->dd_loc = 0;
D 17
	while (dirp->dd_loc < offset) {
E 17
I 17
	while (dirp->dd_loc < lp->loc_loc) {
E 17
		dp = readdir(dirp);
		if (dp == NULL)
			return;
	}
E 18
I 18
	_seekdir(dirp, loc);
E 18
E 4
E 2
}
E 1
