h01770
s 00017/00002/00098
d D 8.3 95/03/30 11:26:22 mckusick 15 14
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00001/00002/00099
d D 8.2 94/08/18 23:33:34 mckusick 14 13
c conversion to queue.h list manipulation (from mycroft)
e
s 00002/00002/00099
d D 8.1 93/06/10 23:39:41 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00001/00097
d D 7.11 92/07/06 18:48:11 mckusick 12 11
c new parameters for fhtovp
e
s 00004/00003/00094
d D 7.10 92/06/25 13:07:50 mckusick 11 10
c quotactl takes uid_t; fhtovp drops setgen bogosity
e
s 00019/00013/00078
d D 7.9 92/01/14 12:41:09 mckusick 10 9
c update from Rick Macklem (including leases)
e
s 00001/00001/00090
d D 7.8 91/11/05 16:49:42 mckusick 9 8
c lint
e
s 00042/00000/00049
d D 7.7 91/04/16 00:26:22 mckusick 8 7
c add prototypes for NFS VFS operations
e
s 00001/00011/00048
d D 7.6 90/06/28 21:53:49 bostic 7 6
c new copyright notice
e
s 00012/00021/00047
d D 7.5 90/05/14 11:34:52 mckusick 6 5
c "update from Rick Macklem adding TCP support to NFS"
e
s 00006/00001/00062
d D 7.4 90/05/04 20:52:44 mckusick 5 4
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00000/00002/00063
d D 7.3 90/03/06 23:31:01 mckusick 4 3
c host and path are now found in m_stat
e
s 00031/00008/00034
d D 7.2 90/02/16 15:43:01 mckusick 3 1
c updates for new transport independent structure;
c nfshost structure to maintain per host congestion information
e
s 00000/00000/00042
d R 7.2 89/08/30 20:30:14 macklem 2 1
c first buffer cache implementation; name cache usage; code cleanups
e
s 00042/00000/00000
d D 7.1 89/07/05 11:32:28 mckusick 1 0
c first bootable NFS from Rick Macklem
e
u
U
t
T
I 1
/*
D 13
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 7
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
 *
 *	%W% (Berkeley) %G%
 */

I 15

#ifndef _NFS_NFSMOUNT_H_
#define _NFS_NFSMOUNT_H_

E 15
/*
 * Mount structure.
D 3
 * One allocated on every nfs mount.
 * Holds nfs specific info for mount (sockets...)
E 3
I 3
 * One allocated on every NFS mount.
 * Holds NFS specific information for mount.
E 3
 */
struct	nfsmount {
	int	nm_flag;		/* Flags for soft/hard... */
D 3
	struct	mount *nm_mountp;	/* vfs structure for this filesystem */
E 3
I 3
	struct	mount *nm_mountp;	/* Vfs structure for this filesystem */
I 10
	int	nm_numgrps;		/* Max. size of groupslist */
E 10
E 3
D 15
	nfsv2fh_t nm_fh;		/* File handle of root dir */
E 15
I 15
	u_char	nm_fh[NFSX_V3FHMAX];	/* File handle of root dir */
	int	nm_fhsize;		/* Size of root file handle */
E 15
D 3
	struct	mbuf *nm_sockaddr;	/* Address of server */
	struct	socket	*nm_so;		/* rpc socket */
	int	nm_timeo;		/* Timeout interval */
	int	nm_retrans;		/* # of retransmits */
E 3
I 3
D 6
	struct	socket	*nm_so;		/* Rpc socket */
	struct	nfshost *nm_hostinfo;	/* Host and congestion information */
E 6
I 6
	struct	socket *nm_so;		/* Rpc socket */
	int	nm_sotype;		/* Type of socket */
	int	nm_soproto;		/* and protocol */
	int	nm_soflags;		/* pr_flags for socket protocol */
	struct	mbuf *nm_nam;		/* Addr of server */
E 6
D 10
	short	nm_retry;		/* Max retry count */
	short	nm_rexmit;		/* Rexmit on previous request */
	short	nm_rtt;			/* Round trip timer ticks @ NFS_HZ */
	short	nm_rto;			/* Current timeout */
	short	nm_srtt;		/* Smoothed round trip time */
	short	nm_rttvar;		/* RTT variance */
I 6
	short	nm_currto;		/* Current rto of any nfsmount */
	short	nm_currexmit;		/* Max rexmit count of nfsmounts */
	short	nm_sent;		/* Request send count */
	short	nm_window;		/* Request send window (max) */
	short	nm_winext;		/* Window incremental value */
	short	nm_ssthresh;		/* Slowstart threshold */
	short	nm_salen;		/* Actual length of nm_sockaddr */
E 10
I 10
	int	nm_timeo;		/* Init timer for NFSMNT_DUMBTIMR */
	int	nm_retry;		/* Max retries */
	int	nm_srtt[4];		/* Timers for rpcs */
	int	nm_sdrtt[4];
	int	nm_sent;		/* Request send count */
	int	nm_cwnd;		/* Request send window */
	int	nm_timeouts;		/* Request timeouts */
	int	nm_deadthresh;		/* Threshold of timeouts-->dead server*/
E 10
E 6
E 3
	int	nm_rsize;		/* Max size of read rpc */
	int	nm_wsize;		/* Max size of write rpc */
I 15
	int	nm_readdirsize;		/* Size of a readdir rpc */
E 15
I 10
	int	nm_readahead;		/* Num. of blocks to readahead */
	int	nm_leaseterm;		/* Term (sec) for NQNFS lease */
D 14
	struct nfsnode *nm_tnext;	/* Head of lease timer queue */
	struct nfsnode *nm_tprev;
E 14
I 14
D 15
	CIRCLEQ_HEAD(nfsnodes, nfsnode) nm_timerhead; /* Lease timer queue */
E 15
I 15
	CIRCLEQ_HEAD(, nfsnode) nm_timerhead; /* Head of lease timer queue */
E 15
E 14
	struct vnode *nm_inprog;	/* Vnode in prog by nqnfs_clientd() */
	uid_t	nm_authuid;		/* Uid for authenticator */
	int	nm_authtype;		/* Authenticator type */
	int	nm_authlen;		/* and length */
	char	*nm_authstr;		/* Authenticator string */
I 15
	char	*nm_verfstr;		/* and the verifier */
	int	nm_verflen;
	u_char	nm_verf[NFSX_V3WRITEVERF]; /* V3 write verifier */
	NFSKERBKEY_T nm_key;		/* and the session key */
	int	nm_numuids;		/* Number of nfsuid mappings */
	TAILQ_HEAD(, nfsuid) nm_uidlruhead; /* Lists of nfsuid mappings */
	LIST_HEAD(, nfsuid) nm_uidhashtbl[NFS_MUIDHASHSIZ];
E 15
E 10
D 3
	char	nm_path[MNAMELEN];	/* Path mounted on */
E 3
D 4
	char	nm_host[MNAMELEN];	/* Remote host name */
I 3
	char	nm_path[MNAMELEN];	/* Path mounted on */
E 4
D 6
};

/*
 * Hostinfo/congestion structure.
 * One allocated per NFS server.
 * Holds host address, congestion limits, request count, etc.
 * Reference count is of nfsmounts which point to it.
 */
struct nfshost {
	struct	nfshost *nh_next, *nh_prev;
	short	nh_refcnt;		/* Reference count */
	short	nh_currto;		/* Current rto of any nfsmount */
	short	nh_currexmit;		/* Max rexmit count of nfsmounts */
	short	nh_sent;		/* Request send count */
	short	nh_window;		/* Request send window (max) */
	short	nh_winext;		/* Window incremental value */
	short	nh_ssthresh;		/* Slowstart threshold */
	short	nh_salen;		/* Actual length of nh_sockaddr */
	struct	mbuf *nh_sockaddr;	/* Address of server */
E 6
E 3
};

D 5
struct nfsmount *vfs_to_nfs();
E 5
I 5
#ifdef KERNEL
/*
 * Convert mount ptr to nfsmount ptr.
 */
#define VFSTONFS(mp)	((struct nfsmount *)((mp)->mnt_data))
#endif /* KERNEL */
I 8

/*
 * Prototypes for NFS mount operations
 */
int	nfs_mount __P((
		struct mount *mp,
		char *path,
		caddr_t data,
		struct nameidata *ndp,
		struct proc *p));
int	nfs_start __P((
		struct mount *mp,
		int flags,
		struct proc *p));
int	nfs_unmount __P((
		struct mount *mp,
		int mntflags,
		struct proc *p));
int	nfs_root __P((
		struct mount *mp,
		struct vnode **vpp));
int	nfs_quotactl __P((
		struct mount *mp,
		int cmds,
D 9
		int uid,	/* should be uid_t */
E 9
I 9
D 11
		u_int uid,	/* should be uid_t */
E 11
I 11
		uid_t uid,
E 11
E 9
		caddr_t arg,
		struct proc *p));
int	nfs_statfs __P((
		struct mount *mp,
		struct statfs *sbp,
		struct proc *p));
int	nfs_sync __P((
		struct mount *mp,
D 11
		int waitfor));
E 11
I 11
		int waitfor,
		struct ucred *cred,
		struct proc *p));
E 11
int	nfs_fhtovp __P((
		struct mount *mp,
		struct fid *fhp,
I 10
D 11
		int setgen,
E 11
E 10
D 12
		struct vnode **vpp));
E 12
I 12
		struct mbuf *nam,
		struct vnode **vpp,
		int *exflagsp,
		struct ucred **credanonp));
E 12
int	nfs_vptofh __P((
		struct vnode *vp,
		struct fid *fhp));
int	nfs_init __P(());
I 15

#endif
E 15
E 8
E 5
E 1
