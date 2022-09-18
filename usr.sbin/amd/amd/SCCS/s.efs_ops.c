h24090
s 00002/00002/00107
d D 8.1 93/06/06 11:39:47 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00108
d D 5.4 92/02/09 08:48:03 pendry 4 3
c merge in new release
e
s 00003/00002/00106
d D 5.3 91/05/12 15:55:08 pendry 3 2
c checkpoint for network tape
e
s 00013/00011/00095
d D 5.2 91/03/17 13:33:01 pendry 2 1
c from amd5.3 alpha11
e
s 00106/00000/00000
d D 5.1 90/06/29 12:01:01 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: efs_ops.c,v 5.2 90/06/23 22:19:23 jsp Rel $
E 2
I 2
D 3
 * $Id: efs_ops.c,v 5.2.1.2 90/11/04 23:17:14 jsp Exp $
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
 * $Id: efs_ops.c,v 5.2.1.3 91/05/07 22:17:50 jsp Alpha $
E 4
I 4
 * $Id: efs_ops.c,v 5.2.2.1 1992/02/09 15:08:21 jsp beta $
E 4
 *
E 3
 */

#include "am.h"

#ifdef HAS_EFS

/*
 * Error file system.
 * This is used as a last resort catchall if
 * nothing else worked.  EFS just returns lots
 * of error codes, except for unmount which
 * always works of course.
 */

/*
 * EFS file system always matches
 */
D 2
static int efs_match(fo)
E 2
I 2
static char *efs_match(fo)
E 2
am_opts *fo;
{
D 2
	fo->fs_mtab = strealloc(fo->fs_mtab, "(error-hook)");
	return 1;
E 2
I 2
	return strdup("(error-hook)");
E 2
}

/*ARGSUSED*/
D 2
static int efs_mount(mp)
am_node *mp;
E 2
I 2
static int efs_fmount(mf)
mntfs *mf;
E 2
{
	return ENOENT;
}

/*ARGSUSED*/
D 2
static int efs_umount(mp)
am_node *mp;
E 2
I 2
static int efs_fumount(mf)
mntfs *mf;
E 2
{
	/*
	 * Always succeed
	 */

	return 0;
}

/*
 * EFS interface to RPC lookup() routine.
 * Should never get here in the automounter.
 * If we do then just give an error.
 */
/*ARGSUSED*/
am_node *efs_lookuppn(mp, fname, error_return, op)
am_node *mp;
char *fname;
int *error_return;
int op;
{
	*error_return = ESTALE;
	return 0;
}

/*
 * EFS interface to RPC readdir() routine.
 * Should never get here in the automounter.
 * If we do then just give an error.
 */
/*ARGSUSED*/
D 2
int efs_readdir(mp, cookie, dp, ep)
E 2
I 2
int efs_readdir(mp, cookie, dp, ep, count)
E 2
am_node *mp;
nfscookie cookie;
dirlist *dp;
entry *ep;
I 2
int count;
E 2
{
	return ESTALE;
}

/*
 * Ops structure
 */
am_ops efs_ops = {
	"error",
	efs_match,
	0, /* efs_init */
D 2
	efs_mount,
	efs_umount,
E 2
I 2
	auto_fmount,
	efs_fmount,
	auto_fumount,
	efs_fumount,
E 2
	efs_lookuppn,
	efs_readdir,
	0, /* efs_readlink */
	0, /* efs_mounted */
	0, /* efs_umounted */
	find_afs_srvr,
	FS_DISCARD
};

#endif /* HAS_EFS */
E 1
