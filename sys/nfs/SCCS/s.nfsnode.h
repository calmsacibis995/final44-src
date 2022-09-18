h14948
s 00003/00003/00191
d D 8.9 95/05/14 00:31:09 mckusick 50 49
c use vop_nolock* locking functions
e
s 00083/00029/00111
d D 8.8 95/03/30 11:26:19 mckusick 49 48
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00001/00000/00139
d D 8.7 95/02/23 13:54:07 mckusick 48 47
c nfs_revoke uses vop_revoke
e
s 00002/00004/00137
d D 8.6 94/08/18 23:33:33 mckusick 47 46
c conversion to queue.h list manipulation (from mycroft)
e
s 00001/00000/00140
d D 8.5 94/08/11 00:12:26 mckusick 46 45
c add vop_lease
e
s 00002/00000/00138
d D 8.4 94/02/13 11:35:19 hibler 45 44
c add define for null reallocblks routine (is this needed?)
e
s 00005/00000/00133
d D 8.3 93/12/30 16:18:51 mckusick 44 43
c new queue structure
e
s 00001/00001/00132
d D 8.2 93/11/14 13:43:07 hibler 43 42
c make n_size u_quad_t instead of off_t 
c ensures consistant size and alignment for implementations with off_t==long
e
s 00002/00002/00131
d D 8.1 93/06/10 23:39:44 bostic 42 41
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00132
d D 7.34 93/05/25 15:50:11 mckusick 41 40
c add pathconf
e
s 00000/00001/00132
d D 7.33 93/03/19 14:35:27 hibler 40 39
c vattr struct is now 2 longwords larger so get rid of some spares
e
s 00002/00018/00131
d D 7.32 93/02/02 14:31:46 mckusick 39 38
c update for 4.4BSD from Rick Macklem
e
s 00018/00000/00131
d D 7.31 92/11/01 23:16:36 mckusick 38 37
c fix from Jeff Forys for tracking changing NFS file sizes
e
s 00001/00000/00130
d D 7.30 92/09/30 16:07:44 mckusick 37 36
c September update from Rick Macklem to add accept protocol to NQMFS
e
s 00009/00023/00121
d D 7.29 92/09/16 18:04:35 mckusick 36 35
c update from Rick Macklem
e
s 00008/00007/00136
d D 7.28 92/07/24 11:26:50 bostic 35 34
c fix public/private declarations for fstat
e
s 00002/00004/00141
d D 7.27 92/07/22 15:24:54 mckusick 34 33
c update to current hashing techniques
e
s 00001/00001/00144
d D 7.26 92/07/03 01:53:41 mckusick 33 32
c nfs_vget moves from vop to vfs
e
s 00002/00001/00143
d D 7.25 92/06/26 09:23:49 mckusick 32 31
c padding for quad alignment
e
s 00001/00001/00143
d D 7.24 92/06/02 14:29:27 mckusick 31 30
c quad's need 8-byte alignment
e
s 00016/00001/00128
d D 7.23 92/05/20 10:54:30 mckusick 30 29
c update for spec and fifo times for NFS (from Macklem)
e
s 00001/00001/00128
d D 7.22 92/05/15 12:24:40 heideman 29 28
c nfs_vfree prototype changed for vn_if
e
s 00039/00174/00090
d D 7.21 92/05/14 17:41:04 heideman 28 20
c vnode interface conversion
e
s 00039/00174/00090
d R 7.21 92/05/14 16:00:00 heideman 27 20
c vnode interface conversion
e
s 00039/00174/00090
d R 7.21 92/05/14 14:59:20 heideman 26 20
c vnode interface conversion
e
s 00039/00174/00090
d R 7.21 92/05/14 13:07:29 heideman 25 20
c vnode interface conversion
e
s 00038/00170/00094
d R 7.21 92/05/14 12:03:44 heideman 24 20
c vnode interface conversion
e
s 00038/00170/00094
d R 7.21 92/05/14 11:27:13 heideman 23 20
c vnode interface conversion
e
s 00038/00170/00094
d R 7.21 92/05/13 23:23:00 heideman 22 20
c vnode interface conversion
e
s 00038/00170/00094
d R 7.21 92/05/13 19:05:45 heideman 21 20
c vnode interface conversion
e
s 00002/00002/00262
d D 7.20 92/05/13 15:04:04 mckusick 20 19
c n_size is now 64-bits
e
s 00002/00001/00262
d D 7.19 92/04/21 13:27:34 mckusick 19 18
c VOP_TRUNCATE now takes a cred argument
e
s 00001/00001/00262
d D 7.18 92/04/21 10:53:52 mckusick 18 17
c ensure proper types for local variables and parameters
e
s 00036/00027/00227
d D 7.17 92/01/22 09:39:27 heideman 17 16
c lookup converted to new form
e
s 00046/00017/00208
d D 7.16 92/01/14 12:41:06 mckusick 16 15
c update from Rick Macklem (including leases)
e
s 00001/00001/00224
d D 7.15 91/12/19 13:02:45 mckusick 15 14
c vattr grew, so number of spares shrank
e
s 00002/00000/00223
d D 7.14 91/12/16 15:30:23 mckusick 14 13
c reorganize for private allocation
e
s 00028/00000/00195
d D 7.13 91/11/05 15:46:41 mckusick 13 12
c reorganization to move ufsmount ops to be vnode ops
e
s 00141/00000/00054
d D 7.12 91/04/16 00:25:35 mckusick 12 11
c add prototypes for NFS vnode ops
e
s 00001/00011/00053
d D 7.11 90/06/28 21:53:55 bostic 11 10
c new copyright notice
e
s 00001/00004/00063
d D 7.10 90/05/14 11:35:01 mckusick 10 9
c "update from Rick Macklem adding TCP support to NFS"
e
s 00003/00001/00064
d D 7.9 90/03/05 19:38:19 mckusick 9 8
c readdir fixes from Rick Macklem
e
s 00001/00000/00064
d D 7.8 90/03/01 13:50:24 mckusick 8 7
c add previous create time for name cache consistency
e
s 00002/00000/00062
d D 7.7 90/01/14 10:56:24 mckusick 7 6
c debugging, add n_lockholder and n_lockwaiter
e
s 00000/00001/00062
d D 7.6 90/01/14 10:55:35 mckusick 6 5
c n_lastr is superceeded by v_lastr
e
s 00000/00003/00063
d D 7.5 89/10/29 23:52:41 mckusick 5 4
c clean out trash
e
s 00002/00010/00064
d D 7.4 89/10/24 19:48:46 mckusick 4 3
c merge inode and nfsnode tables into a single vnode table
e
s 00007/00003/00067
d D 7.3 89/10/19 22:36:16 mckusick 3 2
c "update from Rick Macklem"
e
s 00004/00000/00066
d D 7.2 89/08/30 20:30:15 macklem 2 1
c first buffer cache implementation; name cache usage; code cleanups
e
s 00066/00000/00000
d D 7.1 89/07/05 11:32:28 mckusick 1 0
c first bootable NFS from Rick Macklem
e
u
U
t
T
I 1
/*
D 42
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 42
I 42
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 42
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 11
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
 *
 *	%W% (Berkeley) %G%
 */

I 49

#ifndef _NFS_NFSNODE_H_
#define _NFS_NFSNODE_H_

#ifndef _NFS_NFS_H_
#include <nfs/nfs.h>
#endif

E 49
/*
I 16
 * Silly rename structure that hangs off the nfsnode until the name
 * can be removed by nfs_inactive()
 */
struct sillyrename {
	struct	ucred *s_cred;
	struct	vnode *s_dvp;
	long	s_namlen;
	char	s_name[20];
};

/*
I 49
 * This structure is used to save the logical directory offset to
 * NFS cookie mappings.
 * The mappings are stored in a list headed
 * by n_cookies, as required.
 * There is one mapping for each NFS_DIRBLKSIZ bytes of directory information
 * stored in increasing logical offset byte order.
 */
#define NFSNUMCOOKIES		31

struct nfsdmap {
	LIST_ENTRY(nfsdmap)	ndm_list;
	int			ndm_eocookie;
	nfsuint64		ndm_cookies[NFSNUMCOOKIES];
};

/*
E 49
E 16
 * The nfsnode is the nfs equivalent to ufs's inode. Any similarity
 * is purely coincidental.
 * There is a unique nfsnode allocated for each active file,
 * each current directory, each mounted-on file, text file, and the root.
 * An nfsnode is 'named' by its file handle. (nget/nfs_node.c)
I 49
 * If this structure exceeds 256 bytes (it is currently 256 using 4.4BSD-Lite
 * type definitions), file handles of > 32 bytes should probably be split out
 * into a separate MALLOC()'d data structure. (Reduce the size of nfsfh_t by
 * changing the definition in sys/mount.h of NFS_SMALLFH.)
 * NB: Hopefully the current order of the fields is such that everything will
 *     be well aligned and, therefore, tightly packed.
E 49
 */
D 49

E 49
struct nfsnode {
D 34
	struct	nfsnode *n_chain[2];	/* must be first */
E 34
I 34
D 47
	struct	nfsnode *n_forw;	/* hash, forward */
	struct	nfsnode **n_back;	/* hash, backward */
E 47
I 47
D 49
	LIST_ENTRY(nfsnode) n_hash;	/* Hash chain */
	CIRCLEQ_ENTRY(nfsnode) n_timer;	/* Nqnfs timer chain */
E 47
E 34
	nfsv2fh_t n_fh;			/* NFS File Handle */
	long	n_flag;			/* Flag for locking.. */
D 4
	long	n_id;		/* unique identifier */
	struct	vnode n_vnode;	/* vnode associated with this nfsnode */
E 4
I 4
D 16
	struct	vnode *n_vnode;	/* vnode associated with this nfsnode */
E 4
D 9
	long	n_attrstamp;	/* Time stamp (sec) for attributes */
E 9
I 9
	time_t	n_attrstamp;	/* Time stamp (sec) for attributes */
E 9
	struct	vattr n_vattr;	/* Vnode attribute cache */
	struct	sillyrename *n_sillyrename;	/* Ptr to silly rename struct */
D 4
	struct nfsnode  *n_freef;	/* free list forward */
	struct nfsnode **n_freeb;	/* free list back */
E 4
I 2
D 6
	daddr_t	n_lastr;	/* Last block read for read ahead */
E 6
	u_long	n_size;		/* Current size of file */
	time_t	n_mtime;	/* Prev modify time to maintain data cache consistency*/
I 8
	time_t	n_ctime;	/* Prev create time for name cache consistency*/
E 8
I 3
	int	n_error;	/* Save write error value */
I 7
	pid_t	n_lockholder;	/* holder of nfsnode lock */
	pid_t	n_lockwaiter;	/* most recent waiter for nfsnode lock */
I 9
	u_long	n_direofoffset;	/* Dir. EOF offset cache */
I 14
	struct	sillyrename n_silly;	/* allocate here since we have room */
D 15
	long	n_spare[9];	/* round up to size 256 */
E 15
I 15
	long	n_spare[7];	/* round up to size 256 */
E 16
I 16
	struct	vnode *n_vnode;		/* vnode associated with this node */
D 31
	time_t	n_attrstamp;		/* Time stamp for cached attributes */
E 31
	struct	vattr n_vattr;		/* Vnode attribute cache */
I 31
	time_t	n_attrstamp;		/* Time stamp for cached attributes */
E 31
	struct	sillyrename *n_sillyrename; /* Ptr to silly rename struct */
D 20
	u_long	n_size;			/* Current size of file */
E 20
I 20
D 43
	off_t	n_size;			/* Current size of file */
E 43
I 43
	u_quad_t n_size;		/* Current size of file */
E 43
E 20
	int	n_error;		/* Save write error value */
	u_long	n_direofoffset;		/* Dir. EOF offset cache */
D 36
	union {
		struct {
			time_t	un_mtime; /* Prev modify time. */
			time_t	un_ctime; /* Prev create time. */
		} un_nfs;
		struct {
			u_quad_t un_brev; /* Modify rev when cached */
			u_quad_t un_lrev; /* Modify rev for lease */
			time_t	un_expiry; /* Lease expiry time */
			struct	nfsnode *un_tnext; /* Nqnfs timer chain */
			struct	nfsnode *un_tprev;
I 32
			long	un_spare; /* pad to 8-byte boundary */
E 32
		} un_nqnfs;
	} n_un;
E 36
I 36
	time_t	n_mtime;		 /* Prev modify time. */
	time_t	n_ctime;		 /* Prev create time. */
	u_quad_t n_brev;		 /* Modify rev when cached */
	u_quad_t n_lrev;		 /* Modify rev for lease */
	time_t	n_expiry;		 /* Lease expiry time */
D 47
	struct	nfsnode *n_tnext;	 /* Nqnfs timer chain */
	struct	nfsnode *n_tprev;		
E 47
	long	spare1;			/* To 8 byte boundary */
E 36
	struct	sillyrename n_silly;	/* Silly rename struct */
D 20
	long	n_spare[11];		/* Up to a power of 2 */
E 20
I 20
D 30
	long	n_spare[9];		/* Up to a power of 2 */
E 30
I 30
	struct	timeval n_atim;		/* Special file times */
	struct	timeval n_mtim;
E 49
I 49
	LIST_ENTRY(nfsnode)	n_hash;		/* Hash chain */
	CIRCLEQ_ENTRY(nfsnode)	n_timer;	/* Nqnfs timer chain */
	u_quad_t		n_size;		/* Current size of file */
	u_quad_t		n_brev;		/* Modify rev when cached */
	u_quad_t		n_lrev;		/* Modify rev for lease */
	struct vattr		n_vattr;	/* Vnode attribute cache */
	time_t			n_attrstamp;	/* Attr. cache timestamp */
	time_t			n_mtime;	/* Prev modify time. */
	time_t			n_ctime;	/* Prev create time. */
	time_t			n_expiry;	/* Lease expiry time */
	nfsfh_t			*n_fhp;		/* NFS File Handle */
	struct vnode		*n_vnode;	/* associated vnode */
	struct lockf		*n_lockf;	/* Locking record of file */
	int			n_error;	/* Save write error value */
	union {
		struct timespec	nf_atim;	/* Special file times */
		nfsuint64	nd_cookieverf;	/* Cookie verifier (dir only) */
	} n_un1;
	union {
		struct timespec	nf_mtim;
		off_t		nd_direof;	/* Dir. EOF offset cache */
	} n_un2;
	union {
		struct sillyrename *nf_silly;	/* Ptr to silly rename struct */
		LIST_HEAD(, nfsdmap) nd_cook;	/* cookies */
	} n_un3;
	short			n_fhsize;	/* size in bytes, of fh */
	short			n_flag;		/* Flag for locking.. */
	nfsfh_t			n_fh;		/* Small File Handle */
E 49
D 32
	long	n_spare[5];		/* Up to a power of 2 */
E 32
I 32
D 36
	long	n_spare[4];		/* Up to a power of 2 */
E 36
I 36
D 40
	long	n_spare[2];		/* Up to a power of 2 */
E 40
E 36
E 32
E 30
E 20
E 16
E 15
E 14
D 10
	time_t	n_direofstamp;	/* Time stamp for dir. EOF offset cache */
E 10
E 9
E 7
E 3
E 2
};
D 36

I 16
#define	n_mtime		n_un.un_nfs.un_mtime
#define	n_ctime		n_un.un_nfs.un_ctime
#define	n_brev		n_un.un_nqnfs.un_brev
#define	n_lrev		n_un.un_nqnfs.un_lrev
#define	n_expiry	n_un.un_nqnfs.un_expiry
#define	n_tnext		n_un.un_nqnfs.un_tnext
#define	n_tprev		n_un.un_nqnfs.un_tprev
E 36
D 34

E 16
#define	n_forw		n_chain[0]
#define	n_back		n_chain[1]
E 34

I 49
#define n_atim		n_un1.nf_atim
#define n_mtim		n_un2.nf_mtim
#define n_sillyrename	n_un3.nf_silly
#define n_cookieverf	n_un1.nd_cookieverf
#define n_direofoffset	n_un2.nd_direof
#define n_cookies	n_un3.nd_cook

E 49
D 35
#ifdef KERNEL
E 35
D 4
struct nfsnode *nfsnode;		/* the nfsnode table itself */
struct nfsnode *nfsnodeNNFSNODE;	/* the end of the nfsnode table */
int	nnfsnode;			/* number of slots in the table */
long	nextnfsnodeid;		/* unique id generator */

E 4
D 5
extern struct vnodeops nfsv2_vnodeops;	/* vnode operations for nfsv2 */
extern struct vnodeops nfsv2chr_vnodeops; /* vnode operations for chr devices */

E 5
/*
D 35
 * Convert between nfsnode pointers and vnode pointers
 */
#define VTONFS(vp)	((struct nfsnode *)(vp)->v_data)
D 4
#define NFSTOV(np)	((struct vnode *)&(np)->n_vnode)
E 4
I 4
#define NFSTOV(np)	((struct vnode *)(np)->n_vnode)
E 4
#endif
/*
E 35
 * Flags for n_flag
 */
I 39
#define	NFLUSHWANT	0x0001	/* Want wakeup from a flush in prog. */
E 39
I 38
#define	NFLUSHINPROG	0x0002	/* Avoid multiple calls to vinvalbuf() */
E 38
D 3
#define	NLOCKED		0x1
#define	NWANT		0x2
I 2
#define NMODIFIED	0x4
E 3
I 3
D 16
#define	NLOCKED		0x1	/* Lock the node for other local accesses */
#define	NWANT		0x2	/* Want above lock */
#define	NMODIFIED	0x4	/* Might have a modified buffer in bio */
D 10
#define	NBUFFERED	0x8	/* Might have a buffer in bio */
#define	NPAGEDON	0x10	/* Might have associated memory pages */
#define	NWRITEERR	0x20	/* Flag write errors so close will know */
E 10
I 10
#define	NWRITEERR	0x8	/* Flag write errors so close will know */
E 16
I 16
#define	NMODIFIED	0x0004	/* Might have a modified buffer in bio */
#define	NWRITEERR	0x0008	/* Flag write errors so close will know */
#define	NQNFSNONCACHE	0x0020	/* Non-cachable lease */
#define	NQNFSWRITE	0x0040	/* Write lease */
#define	NQNFSEVICTED	0x0080	/* Has been evicted */
I 30
#define	NACC		0x0100	/* Special file accessed */
#define	NUPD		0x0200	/* Special file updated */
#define	NCHG		0x0400	/* Special file times changed */
I 38

D 39
#define	NFS_VINVBUF(np, vp, flags, cred, p) {		\
	if ((np->n_flag & NFLUSHINPROG) == 0) {		\
		np->n_flag |= NFLUSHINPROG;		\
		(void) vinvalbuf(vp, flags, cred, p);	\
		np->n_flag &= ~(NFLUSHINPROG|NMODIFIED);\
	}						\
}

#define	NFS_VINVBUFE(np, vp, flags, cred, p, error) {	\
	if ((np->n_flag & NFLUSHINPROG) == 0) {		\
		np->n_flag |= NFLUSHINPROG;		\
		error = vinvalbuf(vp, flags, cred, p);	\
		np->n_flag &= ~(NFLUSHINPROG|NMODIFIED);\
	} else						\
		error = 0;				\
}
E 38
E 30
E 16
I 12

E 39
/*
I 35
 * Convert between nfsnode pointers and vnode pointers
 */
#define VTONFS(vp)	((struct nfsnode *)(vp)->v_data)
#define NFSTOV(np)	((struct vnode *)(np)->n_vnode)

I 44
/*
 * Queue head for nfsiod's
 */
D 49
TAILQ_HEAD(nfsbufs, buf) nfs_bufq;
E 49
I 49
TAILQ_HEAD(, buf) nfs_bufq;
E 49

E 44
#ifdef KERNEL
/*
E 35
 * Prototypes for NFS vnode operations
 */
D 28
int	nfs_lookup __P((
D 17
		struct vnode *vp,
		struct nameidata *ndp,
		struct proc *p));
E 17
I 17
		struct vnode *dvp,
		struct vnode **vpp,
		struct componentname *cnp));
E 17
int	nfs_create __P((
D 17
		struct nameidata *ndp,
		struct vattr *vap,
		struct proc *p));
E 17
I 17
		struct vnode *dvp,
		struct vnode **vpp,
		struct componentname *cnp,
		struct vattr *vap));
E 17
int	nfs_mknod __P((
D 17
		struct nameidata *ndp,
		struct vattr *vap,
		struct ucred *cred,
		struct proc *p));
E 17
I 17
		struct vnode *dvp,
		struct vnode **vpp,
		struct componentname *cnp,
		struct vattr *vap));
E 17
int	nfs_open __P((
		struct vnode *vp,
		int mode,
		struct ucred *cred,
		struct proc *p));
int	nfs_close __P((
		struct vnode *vp,
		int fflag,
		struct ucred *cred,
		struct proc *p));
int	nfs_access __P((
		struct vnode *vp,
		int mode,
		struct ucred *cred,
		struct proc *p));
int	nfs_getattr __P((
		struct vnode *vp,
		struct vattr *vap,
		struct ucred *cred,
		struct proc *p));
int	nfs_setattr __P((
		struct vnode *vp,
		struct vattr *vap,
		struct ucred *cred,
		struct proc *p));
int	nfs_read __P((
		struct vnode *vp,
		struct uio *uio,
		int ioflag,
		struct ucred *cred));
int	nfs_write __P((
		struct vnode *vp,
		struct uio *uio,
		int ioflag,
		struct ucred *cred));
#define nfs_ioctl ((int (*) __P(( \
		struct vnode *vp, \
		int command, \
		caddr_t data, \
		int fflag, \
		struct ucred *cred, \
		struct proc *p))) enoioctl)
#define nfs_select ((int (*) __P(( \
		struct vnode *vp, \
		int which, \
		int fflags, \
		struct ucred *cred, \
		struct proc *p))) seltrue)
int	nfs_mmap __P((
		struct vnode *vp,
		int fflags,
		struct ucred *cred,
		struct proc *p));
int	nfs_fsync __P((
		struct vnode *vp,
		int fflags,
		struct ucred *cred,
		int waitfor,
		struct proc *p));
#define nfs_seek ((int (*) __P(( \
		struct vnode *vp, \
		off_t oldoff, \
		off_t newoff, \
		struct ucred *cred))) nullop)
int	nfs_remove __P((
D 17
		struct nameidata *ndp,
		struct proc *p));
int	nfs_link __P((
E 17
I 17
		struct vnode *dvp,
E 17
		struct vnode *vp,
D 17
		struct nameidata *ndp,
		struct proc *p));
E 17
I 17
		struct componentname *cnp));
int	nfs_link __P((
		register struct vnode *vp,
		struct vnode *tdvp,
		struct componentname *cnp));
E 17
int	nfs_rename __P((
D 17
		struct nameidata *fndp,
		struct nameidata *tdnp,
		struct proc *p));
E 17
I 17
		struct vnode *fdvp,
		struct vnode *fvp,
		struct componentname *fcnp,
		struct vnode *tdvp,
		struct vnode *tvp,
		struct componentname *tcnp));
E 17
int	nfs_mkdir __P((
D 17
		struct nameidata *ndp,
		struct vattr *vap,
		struct proc *p));
E 17
I 17
		struct vnode *dvp,
		struct vnode **vpp,
		struct componentname *cnp,
		struct vattr *vap));
E 17
int	nfs_rmdir __P((
D 17
		struct nameidata *ndp,
		struct proc *p));
E 17
I 17
		struct vnode *dvp,
		struct vnode *vp,
		struct componentname *cnp));
E 17
int	nfs_symlink __P((
D 17
		struct nameidata *ndp,
E 17
I 17
		struct vnode *dvp,
		struct vnode **vpp,
		struct componentname *cnp,
E 17
		struct vattr *vap,
D 17
		char *target,
		struct proc *p));
E 17
I 17
		char *nm));
E 17
int	nfs_readdir __P((
		struct vnode *vp,
		struct uio *uio,
		struct ucred *cred,
		int *eofflagp));
int	nfs_readlink __P((
		struct vnode *vp,
		struct uio *uio,
		struct ucred *cred));
int	nfs_abortop __P((
D 17
		struct nameidata *ndp));
E 17
I 17
		struct vnode *,
		struct componentname *));
E 17
int	nfs_inactive __P((
		struct vnode *vp,
		struct proc *p));
int	nfs_reclaim __P((
		struct vnode *vp));
int	nfs_lock __P((
		struct vnode *vp));
int	nfs_unlock __P((
		struct vnode *vp));
int	nfs_bmap __P((
		struct vnode *vp,
		daddr_t bn,
		struct vnode **vpp,
		daddr_t *bnp));
int	nfs_strategy __P((
		struct buf *bp));
int	nfs_print __P((
		struct vnode *vp));
int	nfs_islocked __P((
		struct vnode *vp));
int	nfs_advlock __P((
		struct vnode *vp,
		caddr_t id,
		int op,
		struct flock *fl,
		int flags));
I 13
int	nfs_blkatoff __P((
		struct vnode *vp,
		off_t offset,
		char **res,
		struct buf **bpp));
int	nfs_vget __P((
		struct mount *mp,
		ino_t ino,
		struct vnode **vpp));
int	nfs_valloc __P((
		struct vnode *pvp,
		int mode,
		struct ucred *cred,
		struct vnode **vpp));
void	nfs_vfree __P((
		struct vnode *pvp,
		ino_t ino,
		int mode));
int	nfs_truncate __P((
		struct vnode *vp,
D 18
		u_long length,
E 18
I 18
		off_t length,
E 18
D 19
		int flags));
E 19
I 19
		int flags,
		struct ucred *cred));
E 19
int	nfs_update __P((
		struct vnode *vp,
		struct timeval *ta,
		struct timeval *tm,
		int waitfor));
E 28
I 28
int	nfs_lookup __P((struct vop_lookup_args *));
int	nfs_create __P((struct vop_create_args *));
int	nfs_mknod __P((struct vop_mknod_args *));
int	nfs_open __P((struct vop_open_args *));
int	nfs_close __P((struct vop_close_args *));
I 30
int	nfsspec_close __P((struct vop_close_args *));
D 49
#ifdef FIFO
E 49
int	nfsfifo_close __P((struct vop_close_args *));
D 49
#endif
E 49
E 30
int	nfs_access __P((struct vop_access_args *));
I 37
int	nfsspec_access __P((struct vop_access_args *));
E 37
int	nfs_getattr __P((struct vop_getattr_args *));
int	nfs_setattr __P((struct vop_setattr_args *));
int	nfs_read __P((struct vop_read_args *));
int	nfs_write __P((struct vop_write_args *));
I 46
D 49
#define nfs_lease_check ((int (*) __P((struct  vop_lease_args *)))nullop)
E 49
I 49
#define	nfs_lease_check ((int (*) __P((struct  vop_lease_args *)))nullop)
#define nqnfs_vop_lease_check	lease_check
E 49
E 46
I 30
int	nfsspec_read __P((struct vop_read_args *));
int	nfsspec_write __P((struct vop_write_args *));
D 49
#ifdef FIFO
E 49
int	nfsfifo_read __P((struct vop_read_args *));
int	nfsfifo_write __P((struct vop_write_args *));
D 49
#endif
E 49
E 30
#define nfs_ioctl ((int (*) __P((struct  vop_ioctl_args *)))enoioctl)
#define nfs_select ((int (*) __P((struct  vop_select_args *)))seltrue)
I 48
D 49
#define	nfs_revoke vop_revoke
E 49
I 49
#define nfs_revoke vop_revoke
E 49
E 48
int	nfs_mmap __P((struct vop_mmap_args *));
int	nfs_fsync __P((struct vop_fsync_args *));
#define nfs_seek ((int (*) __P((struct  vop_seek_args *)))nullop)
int	nfs_remove __P((struct vop_remove_args *));
int	nfs_link __P((struct vop_link_args *));
int	nfs_rename __P((struct vop_rename_args *));
int	nfs_mkdir __P((struct vop_mkdir_args *));
int	nfs_rmdir __P((struct vop_rmdir_args *));
int	nfs_symlink __P((struct vop_symlink_args *));
int	nfs_readdir __P((struct vop_readdir_args *));
int	nfs_readlink __P((struct vop_readlink_args *));
int	nfs_abortop __P((struct vop_abortop_args *));
int	nfs_inactive __P((struct vop_inactive_args *));
int	nfs_reclaim __P((struct vop_reclaim_args *));
D 50
int	nfs_lock __P((struct vop_lock_args *));
int	nfs_unlock __P((struct vop_unlock_args *));
E 50
I 50
#define nfs_lock ((int (*) __P((struct vop_lock_args *)))vop_nolock)
#define nfs_unlock ((int (*) __P((struct vop_unlock_args *)))vop_nounlock)
#define nfs_islocked ((int (*) __P((struct vop_islocked_args *)))vop_noislocked)
E 50
int	nfs_bmap __P((struct vop_bmap_args *));
int	nfs_strategy __P((struct vop_strategy_args *));
int	nfs_print __P((struct vop_print_args *));
D 50
int	nfs_islocked __P((struct vop_islocked_args *));
E 50
I 41
int	nfs_pathconf __P((struct vop_pathconf_args *));
E 41
int	nfs_advlock __P((struct vop_advlock_args *));
int	nfs_blkatoff __P((struct vop_blkatoff_args *));
I 49
int	nfs_bwrite __P((struct vop_bwrite_args *));
E 49
D 33
int	nfs_vget __P((struct vop_vget_args *));
E 33
I 33
int	nfs_vget __P((struct mount *, ino_t, struct vnode **));
E 33
int	nfs_valloc __P((struct vop_valloc_args *));
I 45
#define nfs_reallocblks \
	((int (*) __P((struct  vop_reallocblks_args *)))eopnotsupp)
E 45
D 29
void	nfs_vfree __P((struct vop_vfree_args *));
E 29
I 29
int	nfs_vfree __P((struct vop_vfree_args *));
E 29
int	nfs_truncate __P((struct vop_truncate_args *));
int	nfs_update __P((struct vop_update_args *));
E 28
D 39
int	bwrite();		/* NFS needs a bwrite routine */
E 39
I 39
D 49
int	nfs_bwrite __P((struct vop_bwrite_args *));
E 49
I 49

/* other stuff */
int	nfs_removeit __P((struct sillyrename *));
int	nfs_nget __P((struct mount *,nfsfh_t *,int,struct nfsnode **));
int	nfs_lookitup __P((struct vnode *,char *,int,struct ucred *,struct proc *,struct nfsnode **));
int	nfs_sillyrename __P((struct vnode *,struct vnode *,struct componentname *));
nfsuint64 *nfs_getcookie __P((struct nfsnode *, off_t, int));
void nfs_invaldir __P((struct vnode *));
#define nqnfs_lease_updatetime	lease_updatetime

E 49
E 39
I 35
#endif /* KERNEL */
I 49

#endif
E 49
E 35
E 13
E 12
E 10
E 3
E 2
E 1
