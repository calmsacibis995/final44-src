h00911
s 00002/00002/00068
d D 8.1 93/06/06 11:49:41 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00069
d D 5.4 92/02/09 08:30:39 pendry 4 3
c merge in new release
e
s 00003/00002/00067
d D 5.3 91/05/12 15:59:19 pendry 3 2
c checkpoint for network tape
e
s 00001/00001/00068
d D 5.2 91/03/17 13:48:55 pendry 2 1
c from amd5.3 alpha11
e
s 00069/00000/00000
d D 5.1 90/06/29 12:41:05 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: misc-aix3.h,v 5.2 90/06/23 22:20:34 jsp Rel $
E 2
I 2
D 3
 * $Id: misc-aix3.h,v 5.2.1.1 90/10/21 22:30:39 jsp Exp $
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
 * $Id: misc-aix3.h,v 5.2.1.2 91/05/07 22:19:26 jsp Alpha $
E 4
I 4
 * $Id: misc-aix3.h,v 5.2.2.1 1992/02/09 15:10:05 jsp beta $
E 4
 *
E 3
 */

struct ufs_args {
	char	*fspec;				/* Block device */
};

struct nfs_args {
	struct sockaddr_in	addr;		/* file server address */
	fhandle_t		fh;		/* File handle to be mounted */
	int			flags;		/* flags */
	int			wsize;		/* write size in bytes */
	int			rsize;		/* read size in bytes */
	int			timeo;		/* initial timeout in .1 secs */
	int			retrans;	/* times to retry send */
	char			*hostname;	/* server's hostname */
	int			acregmin;	/* attr cache file min secs */
	int			acregmax;	/* attr cache file max secs */
	int			acdirmin;	/* attr cache dir min secs */
	int			acdirmax;	/* attr cache dir max secs */
	char			*netname;	/* server's netname */
	int			biods;		/* number of BIODS */
};

/*
 * NFS mount option flags
 */
#define	MNTOPT_RO	"ro"	/* read only */
#define	MNTOPT_RW	"rw"	/* read/write */
#define	MNTOPT_SOFT	"soft"	/* soft mount */
#define	MNTOPT_HARD	"hard"	/* hard mount */
#define	MNTOPT_NOSUID	"nosuid"/* no set uid allowed */
#define	MNTOPT_NOAUTO	"noauto"/* hide entry from mount -a */
#define	MNTOPT_INTR	"intr"	/* allow interrupts on hard mount */
#define MNTOPT_SECURE 	"secure"/* use secure RPC for NFS */
#define MNTOPT_GRPID 	"grpid"	/* SysV-compatible group-id on create */
#define MNTOPT_NOSUB	"nosub"  /* disallow mounts beneath this one */
#define MNTOPT_MULTI	"multi"  /* Do multi-component lookup */
#define MNTOPT_NOAC 	"noac"   /* don't cache attributes */

#define NFSMNT_SOFT	0x001	/* soft mount (hard is default) */
#define NFSMNT_WSIZE	0x002	/* set write size */
#define NFSMNT_RSIZE	0x004	/* set read size */
#define NFSMNT_TIMEO	0x008	/* set initial timeout */
#define NFSMNT_RETRANS	0x010	/* set number of request retrys */
#define NFSMNT_HOSTNAME	0x020	/* set hostname for error printf */
#define NFSMNT_INT	0x040	/* allow interrupts on hard mount */
#define	NFSMNT_NOAC	0x080	/* don't cache attributes */
#define	NFSMNT_ACREGMIN	0x0100	/* set min secs for file attr cache */
#define	NFSMNT_ACREGMAX	0x0200	/* set max secs for file attr cache */
#define	NFSMNT_ACDIRMIN	0x0400	/* set min secs for dir attr cache */
#define	NFSMNT_ACDIRMAX	0x0800	/* set max secs for dir attr cache */
#define NFSMNT_SECURE	0x1000	/* secure mount */
#define NFSMNT_BIODS	0x10000	/* Number of biods for the file system */

#define DEF_BIODS	6
E 1
