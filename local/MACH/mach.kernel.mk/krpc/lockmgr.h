/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	lockmgr.h,v $
 * Revision 2.3  89/02/25  18:11:49  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  00:51:46  jsb
 * 	Merged.
 * 	[89/01/17  12:21:50  jsb]
 * 
 */
/* @(#)lockmgr.h	1.1 87/06/30 3.2/4.3NFSSRC */
/*	@(#)lockmgr.h 1.1 86/09/25 SMI	*/

/*
 * Header file for Kernel<->Network Lock-Manager implementation
 */

/* NOTE: size of a lockhandle-id should track the size of an fhandle */
#define KLM_LHSIZE	32

/* the lockhandle uniquely describes any file in a domain */
typedef struct {
	struct vnode *lh_vp;			/* vnode of file */
	char *lh_servername;			/* file server machine name */
	struct {				/* fhandle (sort of) */
		struct __lh_ufsid {
			fsid_t		__lh_fsid;
			struct fid	__lh_fid;
		} __lh_ufs;
#define KLM_LHPAD	(KLM_LHSIZE - sizeof (struct __lh_ufsid))
		char	__lh_pad[KLM_LHPAD];
	} lh_id;
} lockhandle_t;
#define lh_fsid	lh_id.__lh_ufs.__lh_fsid
#define lh_fid	lh_id.__lh_ufs.__lh_fid


/* define 'well-known' information */
#define KLM_PROTO	IPPROTO_UDP

/* define public routines */
int  klm_lockctl();
