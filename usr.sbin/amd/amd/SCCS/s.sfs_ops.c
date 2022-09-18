h09298
s 00002/00002/00180
d D 8.1 93/06/06 11:41:19 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00070/00003/00112
d D 5.4 92/02/09 08:49:01 pendry 4 3
c merge in new release
e
s 00003/00002/00112
d D 5.3 91/05/12 15:56:09 pendry 3 2
c checkpoint for network tape
e
s 00012/00013/00102
d D 5.2 91/03/17 13:34:01 pendry 2 1
c from amd5.3 alpha11
e
s 00115/00000/00000
d D 5.1 90/06/29 12:01:19 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: sfs_ops.c,v 5.2 90/06/23 22:19:59 jsp Rel $
E 2
I 2
D 3
 * $Id: sfs_ops.c,v 5.2.1.2 90/12/21 16:41:47 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
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
 * $Id: sfs_ops.c,v 5.2.1.3 91/05/07 22:18:33 jsp Alpha $
E 4
I 4
 * $Id: sfs_ops.c,v 5.2.2.1 1992/02/09 15:09:04 jsp beta $
E 4
 *
E 3
 */

#include "am.h"

D 4
#ifdef HAS_SFS
E 4
I 4
#if defined(HAS_SFS) || defined(HAS_SFSX)
#define NEED_SFS_MATCH
#define NEED_SFS_UMOUNT
#endif
E 4

/*
 * Symbol-link file system
 */

I 4
#ifdef HAS_SFSX
#include <sys/stat.h>
#endif

#ifdef NEED_SFS_MATCH
E 4
/*
 * SFS needs a link.
 */
D 2
static int sfs_match(fo)
E 2
I 2
static char *sfs_match(fo)
E 2
am_opts *fo;
{
	if (!fo->opt_fs) {
		plog(XLOG_USER, "link: no fs specified");
		return 0;
	}

	/*
	 * Bug report (14/12/89) from Jay Plett <jay@princeton.edu>
	 * If an automount point has the same name as an existing
	 * link type mount Amd hits a race condition and either hangs
	 * or causes a symlink loop.
	 *
	 * If fs begins with a '/' change the opt_fs & opt_sublink
	 * fields so that the fs option doesn't end up pointing at
	 * an existing symlink.
	 *
	 * If sublink is nil then set sublink to fs
	 * else set sublink to fs / sublink
	 *
	 * Finally set fs to ".".
	 */
	if (*fo->opt_fs == '/') {
		char *fullpath;
		char *link = fo->opt_sublink;
		if (link) {
			if (*link == '/')
				fullpath = strdup(link);
			else
				fullpath = str3cat((char *)0, fo->opt_fs, "/", link);
		} else {
			fullpath = strdup(fo->opt_fs);
		}

		if (fo->opt_sublink)
			free(fo->opt_sublink);
		fo->opt_sublink = fullpath;
D 2
		free(fo->opt_fs);
		fo->opt_fs = strdup(".");
E 2
I 2
		fo->opt_fs = str3cat(fo->opt_fs, ".", fullpath, "");
E 2
	}

D 2
	fo->fs_mtab = strealloc(fo->fs_mtab, fo->opt_fs);

	return 1;
E 2
I 2
	return strdup(fo->opt_fs);
E 2
}
I 4
#endif
E 4

I 4
#ifdef HAS_SFSX
E 4
/*ARGUSED*/
I 4
static int sfsx_mount P((am_node *mp));
static int sfsx_mount(mp)
am_node *mp;
{
	/*
	 * Check for existence of target.
	 */
	struct stat stb;
	char *ln;

	if (mp->am_link)
		ln = mp->am_link;
	else /* should never occur */
		ln = mp->am_mnt->mf_mount;

	/*
	 * Use lstat, not stat, since we don't
	 * want to know if the ultimate target of
	 * a symlink chain exists, just the first.
	 */
	if (lstat(ln, &stb) < 0)
		return errno;

	return 0;
}
#endif

#ifdef HAS_SFS
/*ARGUSED*/
E 4
D 2
static int sfs_mount(mp)
am_node *mp;
E 2
I 2
static int sfs_fmount(mf)
mntfs *mf;
E 2
{
	/*
	 * Wow - this is hard to implement!
	 */

	return 0;
}
I 4
#endif
E 4

I 4
#ifdef NEED_SFS_UMOUNT
E 4
/*ARGUSED*/
D 2
static int sfs_umount(mp)
am_node *mp;
E 2
I 2
static int sfs_fumount(mf)
mntfs *mf;
E 2
{
	return 0;
}
I 4
#endif
E 4

/*
D 4
 * Ops structure
E 4
I 4
 * Ops structures
E 4
 */
I 4
#ifdef HAS_SFS
E 4
am_ops sfs_ops = {
	"link",
	sfs_match,
	0, /* sfs_init */
D 2
	sfs_mount,
	sfs_umount,
E 2
I 2
	auto_fmount,
	sfs_fmount,
	auto_fumount,
	sfs_fumount,
E 2
	efs_lookuppn,
	efs_readdir,
	0, /* sfs_readlink */
	0, /* sfs_mounted */
	0, /* sfs_umounted */
	find_afs_srvr,
#ifdef FLUSH_KERNEL_NAME_CACHE
	FS_UBACKGROUND
#else /* FLUSH_KERNEL_NAME_CACHE */
	0
#endif /* FLUSH_KERNEL_NAME_CACHE */
};

#endif /* HAS_SFS */
I 4

#ifdef HAS_SFSX
struct am_ops sfsx_ops = {
	"linkx",
	sfs_match,
	0, /* sfsx_init */
	sfsx_mount,
	0,
	auto_fumount,
	sfs_fumount,
	efs_lookuppn,
	efs_readdir,
	0, /* sfsx_readlink */
	0, /* sfsx_mounted */
	0, /* sfsx_umounted */
	find_afs_srvr,
#ifdef FLUSH_KERNEL_NAME_CACHE
	FS_BACKGROUND
#else /* FLUSH_KERNEL_NAME_CACHE */
	FS_MBACKGROUND
#endif /* FLUSH_KERNEL_NAME_CACHE */
};

#endif /* HAS_SFSX */
E 4
E 1
