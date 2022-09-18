/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pathname.h,v $
 * Revision 2.6  90/07/03  16:55:39  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:26:25  mrt]
 * 
 * Revision 2.5  89/04/22  15:33:07  gm0w
 * 	Added multiple include protection.  Fixed minor cleanup bug.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.4  89/03/09  22:43:11  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  11:11:53  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:22:32  jsb
 * 	CMUCS: declare pn_skipslash as returning an int (to return number of
 * 	slashes skipped). This is for symbolic link quoting.
 * 	[89/01/17  15:40:09  jsb]
 * 
 */
/*	@(#)pathname.h 1.1 86/09/25 SMI	*/

#ifndef	_VFS_PATHNAME_H_
#define	_VFS_PATHNAME_H_

/*
 * Pathname structure.
 * System calls which operate on path names gather the
 * pathname from system call into this structure and reduce
 * it by peeling off translated components.  If a symbolic
 * link is encountered the new pathname to be translated
 * is also assembled in this structure.
 */
struct pathname {
	char	*pn_buf;		/* underlying storage */
	char	*pn_path;		/* remaining pathname */
	u_int	pn_pathlen;		/* remaining length */
};

#define pn_peekchar(PNP)	((PNP)->pn_pathlen>0?*((PNP)->pn_path):0)
#define pn_pathleft(PNP)	((PNP)->pn_pathlen)

extern int	pn_alloc();		/* allocat buffer for pathname */
extern int	pn_get();		/* allocate buf and copy path into it */
#ifdef	notneeded
extern int	pn_getchar();		/* get next pathname char */
#endif
extern int	pn_set();		/* set pathname to string */
extern int	pn_combine();		/* combine to pathnames (for symlink) */
extern int	pn_getcomponent();	/* get next component of pathname */
#if	MACH_RFS
extern int	pn_skipslash();		/* skip over slashes */
#else	/* MACH_RFS */
extern void	pn_skipslash();		/* skip over slashes */
#endif	/* MACH_RFS */
extern void	pn_free();		/* free pathname buffer */
#endif	_VFS_PATHNAME_H_
