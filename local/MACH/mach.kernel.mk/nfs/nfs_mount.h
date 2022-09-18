/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	nfs_mount.h,v $
 * Revision 2.4  89/03/09  20:54:07  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:09:19  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  00:55:21  jsb
 * 	Include file references.
 * 	[89/01/17  14:12:33  jsb]
 * 
 *
 * 24-Mar-88  Gregg Kellogg (gk) at NeXT
 *
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)mount.h	7.1 (Berkeley) 6/4/86
 */

/* @(#)mount.h	1.3 87/05/29 3.2/4.3NFSSRC */

struct nfs_args {
	struct sockaddr_in	*addr;		/* file server address */
	fhandle_t		*fh;		/* File handle to be mounted */
	int			flags;		/* flags */
	int			wsize;		/* write size in bytes */
	int			rsize;		/* read size in bytes */
	int			timeo;		/* initial timeout in .1 secs */
	int			retrans;	/* times to retry send */
	char			*hostname;	/* server's name */
};

/*
 * NFS mount option flags
 */
#define NFSMNT_SOFT	0x001	/* soft mount (hard is default) */
#define NFSMNT_WSIZE	0x002	/* set write size */
#define NFSMNT_RSIZE	0x004	/* set read size */
#define NFSMNT_TIMEO	0x008	/* set initial timeout */
#define NFSMNT_RETRANS	0x010	/* set number of request retrys */
#define NFSMNT_HOSTNAME	0x020	/* set hostname for error printf */
#define NFSMNT_INT	0x040	/* allow interrupts on hard mount */
