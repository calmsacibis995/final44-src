h31632
s 00002/00002/00042
d D 8.1 93/06/04 12:02:56 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00042
d D 6.5 91/11/19 13:41:42 bostic 5 4
c the export interface now permits credentials, needs new include files
e
s 00003/00001/00040
d D 6.4 91/02/23 19:49:44 donn 4 3
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00040
d D 6.3 90/06/01 14:10:50 bostic 3 2
c new copyright notice
e
s 00005/00004/00046
d D 6.2 90/03/06 21:17:49 mckusick 2 1
c add flags parameter to pass through to getfsstat(2)
e
s 00050/00000/00000
d D 6.1 89/10/17 15:14:56 mckusick 1 0
c date and time created 89/10/17 15:14:56 by mckusick
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 5
#include <sys/types.h>
E 5
I 5
#include <sys/param.h>
#include <sys/ucred.h>
E 5
#include <sys/mount.h>
I 4
#include <stdlib.h>
E 4

/*
 * Return information about mounted filesystems.
 */
int
D 2
getmntinfo(mntbufp)
E 2
I 2
getmntinfo(mntbufp, flags)
E 2
	struct statfs **mntbufp;
I 2
	int flags;
E 2
{
	static struct statfs *mntbuf;
D 4
	static int mntsize, bufsize;
E 4
I 4
	static int mntsize;
	static long bufsize;
E 4

D 2
	if (mntsize <= 0 && (mntsize = getfsstat(0, 0)) < 0)
E 2
I 2
	if (mntsize <= 0 && (mntsize = getfsstat(0, 0, MNT_NOWAIT)) < 0)
E 2
		return (0);
D 2
	if (bufsize > 0 && (mntsize = getfsstat(mntbuf, bufsize)) < 0)
E 2
I 2
	if (bufsize > 0 && (mntsize = getfsstat(mntbuf, bufsize, flags)) < 0)
E 2
		return (0);
	while (bufsize <= mntsize * sizeof(struct statfs)) {
		if (mntbuf)
			free(mntbuf);
		bufsize = (mntsize + 1) * sizeof(struct statfs);
		if ((mntbuf = (struct statfs *)malloc(bufsize)) == 0)
			return (0);
D 2
		if ((mntsize = getfsstat(mntbuf, bufsize)) < 0)
E 2
I 2
		if ((mntsize = getfsstat(mntbuf, bufsize, flags)) < 0)
E 2
			return (0);
	}
	*mntbufp = mntbuf;
	return (mntsize);
}
E 1
