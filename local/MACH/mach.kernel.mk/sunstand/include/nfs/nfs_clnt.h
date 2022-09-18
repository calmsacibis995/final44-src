/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	nfs_clnt.h,v $
 * Revision 2.2  89/07/11  23:26:53  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*      @(#)nfs_clnt.h 2.19 88/02/08 SMI      */

#ifndef __NFS_CLNT_HEADER__
#define __NFS_CLNT_HEADER__

/*
 * vfs pointer to mount info
 */
#define	vftomi(vfsp)	((struct mntinfo *)((vfsp)->vfs_data))

/*
 * vnode pointer to mount info
 */
#define	vtomi(vp)	((struct mntinfo *)(((vp)->v_vfsp)->vfs_data))

/*
 * NFS vnode to server's block size
 */
#define	vtoblksz(vp)	(vtomi(vp)->mi_bsize)


#define	HOSTNAMESZ	32
#define	ACREGMIN	3	/* min secs to hold cached file attr */
#define	ACREGMAX	60	/* max secs to hold cached file attr */
#define	ACDIRMIN	30	/* min secs to hold cached dir attr */
#define	ACDIRMAX	60	/* max secs to hold cached dir attr */

/*
 * NFS private data per mounted file system
 */
struct mntinfo {
	struct sockaddr_in mi_addr;	/* server's address */
	struct vnode	*mi_rootvp;	/* root vnode */
	u_int		 mi_hard : 1;	/* hard or soft mount */
	u_int		 mi_printed : 1;/* not responding message printed */
	u_int		 mi_int : 1;	/* interrupts allowed on hard mount */
	u_int		 mi_down : 1;	/* server is down */
	u_int		 mi_noac : 1;	/* don't cache attributes */
	int		 mi_refct;	/* active vnodes for this vfs */
	long		 mi_tsize;	/* transfer size (bytes) */
	long		 mi_stsize;	/* server's max transfer size (bytes) */
	long		 mi_bsize;	/* server's disk block size */
	int		 mi_mntno;	/* kludge to set client rdev for stat*/
	int		 mi_timeo;	/* inital timeout in 10th sec */
	int		 mi_retrans;	/* times to retry request */
	char		 mi_hostname[HOSTNAMESZ];	/* server's hostname */
	char		*mi_netname;	/* server's netname */
	int		 mi_netnamelen;	/* length of netname */
	int		 mi_authflavor;	/* authentication type */
	u_int		 mi_acregmin;	/* min secs to hold cached file attr */
	u_int		 mi_acregmax;	/* max secs to hold cached file attr */
	u_int		 mi_acdirmin;	/* min secs to hold cached dir attr */
	u_int		 mi_acdirmax;	/* max secs to hold cached dir attr */
};

/*
 * Mark cached attributes invalid
 */
#define	PURGE_ATTRCACHE(vp)	(vtor(vp)->r_attrtime.tv_sec = 0)

/*
 * If returned error is ESTALE flush all caches.
 */
#define PURGE_STALE_FH(errno, vp) if ((errno) == ESTALE) {nfs_purge_caches(vp);}

/*
 * Is cache valid?
 * Swap is always valid
 * If no cached attributes, nothing to check against so it's valid
 * otherwise if mtime matches cached mtime it is valid
 */
#define	CACHE_VALID(rp, mtime) \
	((rtov(rp)->v_flag & VISSWAP) == VISSWAP || \
	 (rp)->r_attrtime.tv_sec == 0 || \
	 ((mtime).tv_sec == (rp)->r_attr.va_mtime.tv_sec && \
	 (mtime).tv_usec == (rp)->r_attr.va_mtime.tv_usec))

#endif !__NFS_CLNT_HEADER__
