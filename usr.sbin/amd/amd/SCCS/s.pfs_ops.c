h19208
s 00002/00002/00141
d D 8.1 93/06/06 11:41:02 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00142
d D 5.4 92/02/09 08:48:53 pendry 4 3
c merge in new release
e
s 00003/00002/00140
d D 5.3 91/05/12 15:55:58 pendry 3 2
c checkpoint for network tape
e
s 00015/00019/00127
d D 5.2 91/03/17 13:33:53 pendry 2 1
c from amd5.3 alpha11
e
s 00146/00000/00000
d D 5.1 90/06/29 12:01:15 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: pfs_ops.c,v 5.2 90/06/23 22:19:53 jsp Rel $
E 2
I 2
D 3
 * $Id: pfs_ops.c,v 5.2.1.1 90/10/21 22:29:36 jsp Exp $
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
 * $Id: pfs_ops.c,v 5.2.1.2 91/05/07 22:18:27 jsp Alpha $
E 4
I 4
 * $Id: pfs_ops.c,v 5.2.2.1 1992/02/09 15:08:56 jsp beta $
E 4
 *
E 3
 */

#include "am.h"

#ifdef HAS_PFS

/*
 * Program file system
 */

/*
 * Execute needs a mount and unmount command.
 */
D 2
static int pfs_match(fo)
E 2
I 2
static char *pfs_match(fo)
E 2
am_opts *fo;
{
	char *prog;
	if (!fo->opt_mount || !fo->opt_unmount) {
		plog(XLOG_USER, "program: no mount/unmount specified");
D 2
		return FALSE;
E 2
I 2
		return 0;
E 2
	}
	prog = strchr(fo->opt_mount, ' ');
D 2
	if (fo->fs_mtab = strealloc(fo->fs_mtab, prog ? prog+1 : fo->opt_mount))
		return TRUE;
	return FALSE;
E 2
I 2
	return strdup(prog ? prog+1 : fo->opt_mount);
E 2
}

static int pfs_init(mf)
mntfs *mf;
{
	/*
	 * Save unmount command
	 */
	if (mf->mf_refc == 1) {
		mf->mf_private = (voidp) strdup(mf->mf_fo->opt_unmount);
		mf->mf_prfree = (void (*) ()) free;
	}
	return 0;
}

static int pfs_exec(info)
char *info;
{
	char **xivec;
	int error;
	/*
	 * Split copy of command info string
	 */
	info = strdup(info);
	if (info == 0)
		return ENOBUFS;
D 2
	xivec = strsplit(info, '\'');
E 2
I 2
	xivec = strsplit(info, ' ', '\'');
E 2
	/*
	 * Put stdout to stderr
	 */
	(void) fclose(stdout);
	(void) dup(fileno(logfp));
	if (fileno(logfp) != fileno(stderr)) {
		(void) fclose(stderr);
		(void) dup(fileno(logfp));
	}
	/*
	 * Try the exec
	 */
#ifdef DEBUG
	Debug(D_FULL) {
		char **cp = xivec;
		plog(XLOG_DEBUG, "executing (un)mount command...");
		while (*cp) {
	  		plog(XLOG_DEBUG, "arg[%d] = '%s'", cp-xivec, *cp);
			cp++;
		}
	}
#endif /* DEBUG */
	if (xivec[0] == 0 || xivec[1] == 0) {
		errno = EINVAL;
		plog(XLOG_USER, "1st/2nd args missing to (un)mount program");
	} else {
		(void) execv(xivec[0], xivec+1);
	}
	/*
	 * Save error number
	 */
	error = errno;
	plog(XLOG_ERROR, "exec failed: %m");

	/*
	 * Free allocate memory
	 */
D 2
	free(info);
	free(xivec);
E 2
I 2
	free((voidp) info);
	free((voidp) xivec);
E 2
	/*
	 * Return error
	 */
	return error;
}

D 2
static int pfs_mount(mp)
am_node *mp;
E 2
I 2
static int pfs_fmount(mf)
mntfs *mf;
E 2
{
D 2
	mntfs *mf = mp->am_mnt;

E 2
	return pfs_exec(mf->mf_fo->opt_mount);
}

D 2
static int pfs_umount(mp)
am_node *mp;
E 2
I 2
static int pfs_fumount(mf)
mntfs *mf;
E 2
{
D 2
	mntfs *mf = mp->am_mnt;

E 2
	return pfs_exec((char *) mf->mf_private);
}

/*
 * Ops structure
 */
am_ops pfs_ops = {
	"program",
	pfs_match,
	pfs_init,
D 2
	pfs_mount,
	pfs_umount,
E 2
I 2
	auto_fmount,
	pfs_fmount,
	auto_fumount,
	pfs_fumount,
E 2
	efs_lookuppn,
	efs_readdir,
	0, /* pfs_readlink */
	0, /* pfs_mounted */
	0, /* pfs_umounted */
	find_afs_srvr,
	FS_BACKGROUND|FS_AMQINFO
};

#endif /* HAS_PFS */
E 1
