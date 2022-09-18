h47004
s 00002/00002/00080
d D 8.1 93/06/06 11:40:37 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00081
d D 5.4 92/02/09 08:48:38 pendry 4 3
c merge in new release
e
s 00003/00002/00079
d D 5.3 91/05/12 15:55:44 pendry 3 2
c checkpoint for network tape
e
s 00006/00002/00075
d D 5.2 91/03/17 13:33:34 pendry 2 1
c from amd5.3 alpha11
e
s 00077/00000/00000
d D 5.1 90/06/29 12:01:11 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: mtab.c,v 5.2 90/06/23 22:19:44 jsp Rel $
E 2
I 2
D 3
 * $Id: mtab.c,v 5.2.1.1 90/10/21 22:29:27 jsp Exp $
E 2
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: mtab.c,v 5.2.1.2 91/05/07 22:18:15 jsp Alpha $
E 4
I 4
 * $Id: mtab.c,v 5.2.2.1 1992/02/09 15:08:45 jsp beta $
E 4
 *
E 3
 */

#include "am.h"

/*
 * Firewall /etc/mtab entries
 */
I 2
void mnt_free P((struct mntent *mp));
E 2
void mnt_free(mp)
struct mntent *mp;
{
	free(mp->mnt_fsname);
	free(mp->mnt_dir);
	free(mp->mnt_type);
	free(mp->mnt_opts);
	free((voidp) mp);
}

/*
 * Discard memory allocated for mount list
 */
I 2
void discard_mntlist P((mntlist *mp));
E 2
void discard_mntlist(mp)
mntlist *mp;
{
	mntlist *mp2;

	while (mp2 = mp) {
		mp = mp->mnext;
		if (mp2->mnt)
			mnt_free(mp2->mnt);
D 2
		free(mp2);
E 2
I 2
		free((voidp) mp2);
E 2
	}
}

/*
 * Throw away a mount list
 */
I 2
void free_mntlist P((mntlist *mp));
E 2
void free_mntlist(mp)
mntlist *mp;
{
	discard_mntlist(mp);
	unlock_mntlist();
}

/*
 * Utility routine which determines the value of a
 * numeric option in the mount options (such as port=%d).
 * Returns 0 if the option is not specified.
 */
I 2
int hasmntval P((struct mntent *mnt, char *opt));
E 2
int hasmntval(mnt, opt)
struct mntent *mnt;
char *opt;
{
	char *str = hasmntopt(mnt, opt);
	if (str) {
		char *eq = strchr(str, '=');
		if (eq)
			return atoi(eq+1);
		else
			plog(XLOG_USER, "bad numeric option \"%s\" in \"%s\"", opt, str);
	}

	return 0;
}
E 1
