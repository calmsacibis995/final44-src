h54606
s 00002/00002/00051
d D 8.1 93/06/06 11:50:30 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00001/00049
d D 5.4 92/02/09 08:30:43 pendry 4 3
c merge in new release
e
s 00003/00002/00047
d D 5.3 91/05/12 15:59:18 pendry 3 2
c checkpoint for network tape
e
s 00001/00001/00048
d D 5.2 91/03/17 13:48:56 pendry 2 1
c from amd5.3 alpha11
e
s 00049/00000/00000
d D 5.1 90/06/29 12:41:06 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: misc-hpux.h,v 5.2 90/06/23 22:20:48 jsp Rel $
E 2
I 2
D 3
 * $Id: misc-hpux.h,v 5.2.1.1 90/10/21 22:30:54 jsp Exp $
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
 * $Id: misc-hpux.h,v 5.2.1.2 91/05/07 22:19:45 jsp Alpha $
E 4
I 4
 * $Id: misc-hpux.h,v 5.2.2.1 1992/02/09 15:10:24 jsp beta $
E 4
 *
E 3
 */

/*
 * These definitions are from <nfs/nfs.h>
 * Unfortunately, that file cannot be included
 * because it contains lots of structure definitions
 * that are not wanted (they produce name clashes).
 * Isn't HP-UX wonderful!
 */

/*
 * HP-UX specific definitions
 */
struct nfs_args {
	struct sockaddr_in	*addr;		/* file server address */
	fhandle_t		*fh;		/* File handle to be mounted */
	int			flags;		/* flags */
	int			wsize;		/* write size in bytes */
	int			rsize;		/* read size in bytes */
	int			timeo;		/* initial timeout in .1 secs */
	int			retrans;	/* times to retry send */
	char			*hostname;	/* server's name */
I 4
#ifdef __hp9000s700 /* XXX for HPUX 8.0 */
	char			*fsname;	/* server's filesystem name */
#endif
E 4
};

/*
 * NFS mount option flags
 */
#define	NFSMNT_SOFT	0x001	/* soft mount (hard is default) */
#define	NFSMNT_WSIZE	0x002	/* set write size */
#define	NFSMNT_RSIZE	0x004	/* set read size */
#define	NFSMNT_TIMEO	0x008	/* set initial timeout */
#define	NFSMNT_RETRANS	0x010	/* set number of request retrys */
#define	NFSMNT_HOSTNAME	0x020	/* set hostname for error printf */
#define	NFSMNT_INT	0x040	/* set option to have interruptable mounts */
#define	NFSMNT_NODEVS   0x080   /* turn off device file access (default on) */
E 1
