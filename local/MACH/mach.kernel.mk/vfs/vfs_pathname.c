/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	vfs_pathname.c,v $
 * Revision 2.6  90/07/03  16:56:00  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:26:20  mrt]
 * 
 * Revision 2.5  89/08/02  08:12:50  jsb
 * 	Eliminated MACH conditionals. Use zalloc instead of kalloc.
 * 	[89/07/31  16:10:33  jsb]
 * 
 * Revision 2.4  89/03/09  22:44:55  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  11:13:28  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:26:31  jsb
 * 	(stupidly) ripped out next_metalink;
 * 	CMUCS: make pn_skipslash return the number of slashes it has skipped,
 * 	for symbloic link quoting.
 * 	[89/01/17  17:29:52  jsb]
 *
 * 27-Aug-87  Peter King (king) at NeXT
 *	Original Sun source, upgraded to Mach
 *	MACH: Use pn_zone for memory allocation.
 */ 

/* @(#)vfs_pathname.c	1.2 87/06/25 3.2/4.3NFSSRC */
/*	@(#)vfs_pathname.c 1.1 86/09/25 SMI	*/

#if	MACH
#include "mach_rfs.h"
#endif	/* MACH */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/uio.h>
#include <sys/errno.h>
#include <vfs/pathname.h>

/*
 * Pathname utilities.
 *
 * In translating file names we copy each argument file
 * name into a pathname structure where we operate on it.
 * Each pathname structure can hold MAXPATHLEN characters
 * including a terminating null, and operations here support
 * allocating and freeing pathname structures, fetching
 * strings from user space, getting the next character from
 * a pathname, combining two pathnames (used in symbolic
 * link processing), and peeling off the first component
 * of a pathname.
 */

#include <kern/zalloc.h>

extern zone_t vfs_name_zone;

/*
 * Allocate contents of pathname structure.
 * Structure itself is typically automatic
 * variable in calling routine for convenience.
 */
pn_alloc(pnp)
	register struct pathname *pnp;
{

	ZALLOC(vfs_name_zone, pnp->pn_buf, char *);
	pnp->pn_path = (char *)pnp->pn_buf;
	pnp->pn_pathlen = 0;
}

/*
 * Pull a pathname from user user or kernel space
 */
int
pn_get(str, seg, pnp)
	register char *str;
	int seg;
	register struct pathname *pnp;
{
	register int error;

	pn_alloc(pnp);
	if (seg == UIO_USERSPACE) {
		error =
		    copyinstr(str, pnp->pn_path, MAXPATHLEN, &pnp->pn_pathlen);
	} else {

		error =
		    copystr(str, pnp->pn_path, MAXPATHLEN, &pnp->pn_pathlen);
	}
	pnp->pn_pathlen--;		/* don't count null byte */

	if (error)
		pn_free(pnp);
	return (error);
}

#ifdef	notneeded
/*
 * Get next character from a path.
 * Return null at end forever.
 */
pn_getchar(pnp)
	register struct pathname *pnp;
{

	if (pnp->pn_pathlen == 0)
		return (0);
	pnp->pn_pathlen--;
	return (*pnp->pn_path++);
}
#endif	notneeded

/*
 * Set pathname to argument string.
 */
pn_set(pnp, path)
	register struct pathname *pnp;
	register char *path;
{
	register int error;

	pnp->pn_path = pnp->pn_buf;
	error = copystr(path, pnp->pn_path, MAXPATHLEN, &pnp->pn_pathlen);
	pnp->pn_pathlen--;		/* don't count null byte */
	return (error);
}

/*
 * Combine two argument pathnames by putting
 * second argument before first in first's buffer,
 * and freeing second argument.
 * This isn't very general: it is designed specifically
 * for symbolic link processing.
 */
pn_combine(pnp, sympnp)
	register struct pathname *pnp;
	register struct pathname *sympnp;
{

	if (pnp->pn_pathlen + sympnp->pn_pathlen >= MAXPATHLEN)
		return (ENAMETOOLONG);
	ovbcopy(pnp->pn_path, pnp->pn_buf + sympnp->pn_pathlen,
	    (u_int)pnp->pn_pathlen);
	bcopy(sympnp->pn_path, pnp->pn_buf, (u_int)sympnp->pn_pathlen);
	pnp->pn_pathlen += sympnp->pn_pathlen;
	pnp->pn_path = pnp->pn_buf;
	return (0);
}

/*
 * Strip next component off a pathname and leave in
 * buffer comoponent which should have room for
 * MAXNAMLEN bytes and a null terminator character.
 */
pn_getcomponent(pnp, component)
	register struct pathname *pnp;
	register char *component;
{
	register char *cp;
	register int l;
	register int n;
	register char c;

	cp = pnp->pn_path;
	l = pnp->pn_pathlen;
	n = MAXNAMLEN;
	while ((l > 0) && (*cp != '/')) {
		if (--n < 0)
			return(ENAMETOOLONG);
		c = *cp++;
		if (c & 0x80)
			return (EINVAL);
		*component++ = c;
		--l;
	}
	pnp->pn_path = cp;
	pnp->pn_pathlen = l;
	*component = 0;
	return (0);
}

/*
 * skip over consecutive slashes in the pathname
 */
#if	MACH_RFS
int
#else	/* MACH_RFS */
void
#endif	/* MACH_RFS */
pn_skipslash(pnp)
	register struct pathname *pnp;
{
#if	MACH_RFS
	int slashcount = 0;
#endif	/* MACH_RFS */
	while ((pnp->pn_pathlen != 0) && (*pnp->pn_path == '/')) {
		pnp->pn_path++;
		pnp->pn_pathlen--;
#if	MACH_RFS
		slashcount++;
#endif	/* MACH_RFS */
	}
#if	MACH_RFS
	return slashcount;
#endif	/* MACH_RFS */
}

/*
 * Free pathname resources.
 */
void
pn_free(pnp)
	register struct pathname *pnp;
{

	ZFREE(vfs_name_zone, pnp->pn_buf);
	pnp->pn_buf = 0;
}
