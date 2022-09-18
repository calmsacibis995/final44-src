h59852
s 00002/00002/00153
d D 8.1 93/06/06 11:39:34 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00004/00146
d D 5.4 92/02/09 08:47:52 pendry 4 3
c merge in new release
e
s 00005/00002/00145
d D 5.3 91/05/12 15:56:29 pendry 3 2
c checkpoint for network tape
e
s 00035/00012/00112
d D 5.2 91/03/17 13:32:52 pendry 2 1
c from amd5.3 alpha11
e
s 00124/00000/00000
d D 5.1 90/06/29 12:00:59 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: am_ops.c,v 5.2 90/06/23 22:19:19 jsp Rel $
E 2
I 2
D 3
 * $Id: am_ops.c,v 5.2.1.3 91/03/03 20:37:39 jsp Alpha $
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
 * $Id: am_ops.c,v 5.2.1.5 91/05/07 22:17:46 jsp Alpha $
E 4
I 4
 * $Id: am_ops.c,v 5.2.2.1 1992/02/09 15:08:17 jsp beta $
E 4
 *
E 3
 */

#include "am.h"

static am_ops *vops[] = {
#ifdef HAS_UFS
	&ufs_ops,
D 2
#endif /* HAS_UFS */
E 2
I 2
#endif
E 2
#ifdef HAS_NFS
	&nfs_ops,
D 2
#endif /* HAS_NFS */
E 2
I 2
#endif
#ifdef HAS_NFSX
	&nfsx_ops,
#endif
E 2
#ifdef HAS_HOST
	&host_ops,
D 2
#endif /* HAS_HOST */
E 2
I 2
#endif
E 2
#ifdef HAS_SFS
	&sfs_ops,
D 2
#endif /* HAS_SFS */
E 2
I 2
#endif
I 4
#ifdef HAS_SFSX
	&sfsx_ops,
#endif
E 4
E 2
#ifdef HAS_LOFS
	&lofs_ops,
D 2
#endif /* HAS_LOFS */
E 2
I 2
#endif
E 2
#ifdef HAS_PFS
	&pfs_ops,
D 2
#endif /* HAS_PFS */
	&afs_ops,	/* These three should be last ... */
E 2
I 2
#endif
#ifdef HAS_UNION_FS
	&union_ops,
#endif
	&afs_ops,	/* These four should be last ... */
E 2
	&dfs_ops,	/* ... */
D 2
	&efs_ops,	/* ... in the order afs; dfs; efs */
E 2
I 2
	&toplvl_ops,	/* ... */
	&efs_ops,	/* ... in the order afs; dfs; toplvl; efs */
E 2
	0
};

I 2
void ops_showfstypes P((FILE *fp));
void ops_showfstypes(fp)
FILE *fp;
{
	struct am_ops **ap;
D 4
	char *sep = "";
E 4
I 4
	int l = 0;
E 4

	for (ap = vops; *ap; ap++) {
D 4
		fprintf(fp, "%s%s", sep, (*ap)->fs_type);
		sep = ", ";
E 4
I 4
		fputs((*ap)->fs_type, fp);
		if (ap[1]) fputs(", ", fp);
		l += strlen((*ap)->fs_type) + 2;
		if (l > 60) { l = 0; fputs("\n    ", fp); }
E 4
	}
}

E 2
#ifdef SUNOS4_COMPAT
I 3
#ifdef nomore
E 3
/*
 * Crack a SunOS4-style host:fs:sub-link line
 * Construct an amd-style line and call the
 * normal amd matcher.
 */
am_ops *sunos4_match(fo, key, g_key, path, keym, map)
am_opts *fo;
char *key;
char *g_key;
char *path;
char *keym;
char *map;
{
	char *host = key;
	char *fs = strchr(host, ':');
	char *sublink = fs ? strchr(fs+1, ':') : 0;
	char keybuf[MAXPATHLEN];

	sprintf(keybuf, "type:=nfs;rhost:=%s;rfs:=%s;sublink:=%s;opts:=%s", host,
		fs ? fs+1 : "",
		sublink ? sublink+1  : "",
		g_key);
	return ops_match(fo, keybuf, "", path, keym, map);
}
I 3
#endif
E 3
#endif /* SUNOS4_COMPAT */

am_ops *ops_match(fo, key, g_key, path, keym, map)
am_opts *fo;
char *key;
char *g_key;
char *path;
char *keym;
char *map;
{
	am_ops **vp;
	am_ops *rop = 0;

	/*
	 * First crack the global opts and the local opts
	 */
	if (!eval_fs_opts(fo, key, g_key, path, keym, map)) {
		rop = &efs_ops;
	} else if (fo->opt_type == 0) {
D 2
		plog(XLOG_USER, "No fs type specified (somewhere!)");
E 2
I 2
		plog(XLOG_USER, "No fs type specified (key = \"%s\", map = \"%s\")", keym, map);
E 2
		rop = &efs_ops;
	} else {
		/*
		 * Next find the correct filesystem type
		 */
		for (vp = vops; rop = *vp; vp++)
			if (strcmp(rop->fs_type, fo->opt_type) == 0)
				break;

		if (!rop) {
			plog(XLOG_USER, "fs type \"%s\" not recognised", fo->opt_type);
			rop = &efs_ops;
		}
	}

	/*
	 * Make sure we have a default mount option.
	 * Otherwise skip past any leading '-'.
	 */
	if (fo->opt_opts == 0)
		fo->opt_opts = "rw,defaults";
	else if (*fo->opt_opts == '-')
		fo->opt_opts++;

	/*
	 * Check the filesystem is happy
	 */
D 2
	if ((*rop->fs_match)(fo))
E 2
I 2
	if (fo->fs_mtab)
		free((voidp) fo->fs_mtab);

	if (fo->fs_mtab = (*rop->fs_match)(fo))
E 2
		return rop;

	/*
	 * Return error file system
	 */
D 2
	(void) (*efs_ops.fs_match)(fo);
E 2
I 2
	fo->fs_mtab = (*efs_ops.fs_match)(fo);
E 2
	return &efs_ops;
}
E 1
