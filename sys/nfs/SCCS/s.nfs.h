h01045
s 00002/00000/00538
d D 8.4 95/05/01 15:43:48 mckusick 25 24
c add version field so we can detect old nfs_args structures
e
s 00304/00046/00234
d D 8.3 95/03/30 11:26:24 mckusick 24 23
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00030/00021/00250
d D 8.2 94/08/18 23:33:35 mckusick 23 22
c conversion to queue.h list manipulation (from mycroft)
e
s 00002/00002/00269
d D 8.1 93/06/10 23:38:34 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00270
d D 7.20 93/04/27 16:30:18 mckusick 21 20
c bug fixes for LEASES from Rick Macklem
e
s 00003/00003/00267
d D 7.19 92/10/20 11:36:55 mckusick 20 19
c more accurate backoff
e
s 00011/00001/00259
d D 7.18 92/09/16 17:57:43 mckusick 19 18
c update from Rick Macklem
e
s 00008/00000/00252
d D 7.17 92/08/11 23:49:20 mckusick 18 17
c define nethostaddr locally for NFS
e
s 00004/00002/00248
d D 7.16 92/03/16 15:34:22 mckusick 17 16
c add mask of all used SLP_ flags
e
s 00002/00000/00248
d D 7.15 92/03/16 15:25:28 mckusick 16 15
c fix from Rick Macklem for multiple free's of NFSD structures
e
s 00001/00002/00247
d D 7.14 92/03/09 22:27:31 mckusick 15 14
c first cut at fixing discconect/reconnect hanging confusion
e
s 00169/00058/00080
d D 7.13 92/01/07 21:20:19 mckusick 14 13
c -yupdate from Rick Macklem
e
s 00001/00001/00137
d D 7.12 91/12/15 13:27:17 mckusick 13 12
c restore alignment
e
s 00004/00002/00134
d D 7.11 91/04/19 18:35:43 mckusick 12 11
c redefine sillyrename structure to avoid use of nameidata structure
c (thus reducing its allocation size from 512 to 64 bytes)
e
s 00002/00001/00134
d D 7.10 91/04/16 00:25:58 mckusick 11 10
c add constant for NFS_DIRBLKSIZ
e
s 00001/00011/00134
d D 7.9 90/06/28 21:51:31 bostic 10 9
c new copyright notice
e
s 00007/00007/00138
d D 7.8 90/06/21 11:13:56 mckusick 9 8
c "update from Rick Macklem"
e
s 00034/00005/00111
d D 7.7 90/05/14 11:48:58 mckusick 8 7
c "update from Rick Macklem adding TCP support to NFS"
e
s 00002/00000/00114
d D 7.6 90/03/05 19:38:06 mckusick 7 6
c readdir fixes from Rick Macklem
e
s 00030/00012/00084
d D 7.5 90/02/16 13:40:49 mckusick 6 5
c generalize a number of constants
e
s 00010/00000/00086
d D 7.4 89/12/20 12:00:01 mckusick 5 4
c "December update from Rick Macklem"
e
s 00003/00000/00083
d D 7.3 89/10/19 22:30:57 mckusick 4 2
c "update from Rick Macklem"
e
s 00000/00000/00083
d R 7.3 89/08/30 20:29:46 macklem 3 2
c first buffer cache implementation; name cache usage; code cleanups
e
s 00004/00003/00079
d D 7.2 89/07/06 17:42:17 mckusick 2 1
c update of July 5th from Rick Macklem
e
s 00082/00000/00000
d D 7.1 89/07/05 11:32:20 mckusick 1 0
c first bootable NFS from Rick Macklem
e
u
U
t
T
I 1
/*
D 22
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 22
I 22
D 24
 * Copyright (c) 1989, 1993
E 24
I 24
 * Copyright (c) 1989, 1993, 1995
E 24
 *	The Regents of the University of California.  All rights reserved.
E 22
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
 *
 *	%W% (Berkeley) %G%
 */

I 24
#ifndef _NFS_NFS_H_
#define _NFS_NFS_H_

E 24
/*
 * Tunable constants for nfs
 */
I 6

E 6
D 8
#define	MAX_IOVEC	10
E 8
I 8
D 9
#define	NFS_MAXIOVEC	10
E 9
I 9
#define	NFS_MAXIOVEC	34
E 9
E 8
D 2
#define	NFS_TIMEO	10	/* Timeout in .01 sec intervals */
E 2
I 2
D 6
#define	NFS_TIMEO	10	/* Timeout in .1 sec intervals */
#define	NFS_MAXTIMEO	600	/* Max timeout to backoff too in .1 sec */
E 2
#define	NFS_ATTRTIMEO	5	/* Attribute cache timeout in sec */
#define	NFS_RETRANS	10	/* Num of retrans for soft mounts */
D 2
#define	NFS_WSIZE	8196	/* Max. write data size <= 8192 */
#define	NFS_RSIZE	8196	/* Max. read data size <= 8192 */
E 2
I 2
#define	NFS_WSIZE	8192	/* Max. write data size <= 8192 */
#define	NFS_RSIZE	8192	/* Max. read data size <= 8192 */
E 6
I 6
D 14
#define NFS_HZ		10		/* Ticks per second for NFS timeouts */
E 14
I 14
D 24
#define NFS_HZ		25		/* Ticks per second for NFS timeouts */
E 14
#define	NFS_TIMEO	(1*NFS_HZ)	/* Default timeout = 1 second */
D 9
#define	NFS_MINTIMEO	(NFS_HZ/2)	/* Min timeout to use */
E 9
I 9
D 14
#define	NFS_MINTIMEO	(NFS_HZ)	/* Min timeout to use */
E 14
I 14
#define	NFS_MINTIMEO	(1*NFS_HZ)	/* Min timeout to use */
E 14
E 9
#define	NFS_MAXTIMEO	(60*NFS_HZ)	/* Max timeout to backoff to */
I 8
D 14
#define	NFS_MINIDEMTIMEO (2*NFS_HZ)	/* Min timeout for non-idempotent ops*/
D 9
#define	NFS_RELIABLETIMEO (300*NFS_HZ)	/* Min timeout on reliable sockets */
E 9
I 9
#define	NFS_RELIABLETIMEO (5*NFS_HZ)	/* Min timeout on reliable sockets */
E 14
I 14
#define	NFS_MINIDEMTIMEO (5*NFS_HZ)	/* Min timeout for non-idempotent ops*/
E 24
I 24
#define NFS_TICKINTVL	5		/* Desired time for a tick (msec) */
#define NFS_HZ		(hz / nfs_ticks) /* Ticks/sec */
#define	NFS_TIMEO	(1 * NFS_HZ)	/* Default timeout = 1 second */
#define	NFS_MINTIMEO	(1 * NFS_HZ)	/* Min timeout to use */
#define	NFS_MAXTIMEO	(60 * NFS_HZ)	/* Max timeout to backoff to */
#define	NFS_MINIDEMTIMEO (5 * NFS_HZ)	/* Min timeout for non-idempotent ops*/
E 24
E 14
E 9
E 8
#define	NFS_MAXREXMIT	100		/* Stop counting after this many */
#define	NFS_MAXWINDOW	1024		/* Max number of outstanding requests */
#define	NFS_RETRANS	10		/* Num of retrans for soft mounts */
D 9
#define NFS_FISHY	6		/* Host not responding at this count */
E 9
I 9
D 14
#define NFS_FISHY	8		/* Host not responding at this count */
E 14
I 14
#define	NFS_MAXGRPS	16		/* Max. size of groups list */
I 24
#ifndef NFS_MINATTRTIMO
E 24
E 14
E 9
D 19
#define	NFS_ATTRTIMEO	5		/* Attribute cache timeout in sec */
E 19
I 19
#define	NFS_MINATTRTIMO 5		/* Attribute cache timeout in sec */
I 24
#endif
#ifndef NFS_MAXATTRTIMO
E 24
#define	NFS_MAXATTRTIMO 60
I 24
#endif
E 24
E 19
D 9
#define	NFS_WSIZE	8192		/* Max. write data size <= 8192 */
#define	NFS_RSIZE	8192		/* Max. read data size <= 8192 */
E 6
E 2
D 8
#define	MAX_READDIR	NFS_RSIZE	/* Max. size of directory read */
I 4
D 6
#define	MAX_ASYNCDAEMON	20	/* Max. number of async_daemons runnable */
E 6
I 6
#define	MAX_ASYNCDAEMON	20		/* Max. number async_daemons runnable */
E 8
I 8
#define	NFS_MAXREADDIR	NFS_RSIZE	/* Max. size of directory read */
E 9
I 9
#define	NFS_WSIZE	8192		/* Def. write data size <= 8192 */
#define	NFS_RSIZE	8192		/* Def. read data size <= 8192 */
I 24
#define NFS_READDIRSIZE	8192		/* Def. readdir size */
E 24
I 14
#define	NFS_DEFRAHEAD	1		/* Def. read ahead # blocks */
#define	NFS_MAXRAHEAD	4		/* Max. read ahead # blocks */
E 14
D 24
#define	NFS_MAXREADDIR	NFS_MAXDATA	/* Max. size of directory read */
E 24
E 9
D 11
#define	NFS_MAXASYNCDAEMON 20	/* Max. number async_daemons runable */
E 11
I 11
D 14
#define	NFS_MAXASYNCDAEMON 20		/* Max. number async_daemons runable */
E 14
I 14
#define	NFS_MAXUIDHASH	64		/* Max. # of hashed uid entries/mp */
D 24
#define	NFS_MAXASYNCDAEMON 20	/* Max. number async_daemons runable */
E 14
#define	NFS_DIRBLKSIZ	1024		/* Size of an NFS directory block */
E 24
I 24
#define	NFS_MAXASYNCDAEMON 	20	/* Max. number async_daemons runable */
#define NFS_MAXGATHERDELAY	100	/* Max. write gather delay (msec) */
#ifndef NFS_GATHERDELAY
#define NFS_GATHERDELAY		10	/* Default write gather delay (msec) */
#endif
#define	NFS_DIRBLKSIZ	4096		/* Must be a multiple of DIRBLKSIZ */

/*
 * Oddballs
 */
E 24
E 11
E 8
E 6
#define	NMOD(a)		((a) % nfs_asyncdaemons)
I 24
#define NFS_CMPFH(n, f, s) \
	((n)->n_fhsize == (s) && !bcmp((caddr_t)(n)->n_fhp, (caddr_t)(f), (s)))
#define NFS_ISV3(v)	(VFSTONFS((v)->v_mount)->nm_flag & NFSMNT_NFSV3)
#define NFS_SRVMAXDATA(n) \
		(((n)->nd_flag & ND_NFSV3) ? (((n)->nd_nam2) ? \
		 NFS_MAXDGRAMDATA : NFS_MAXDATA) : NFS_V2MAXDATA)
E 24
I 19

/*
I 24
 * XXX
 * The B_INVAFTERWRITE flag should be set to whatever is required by the
 * buffer cache code to say "Invalidate the block after it is written back".
 */
#define	B_INVAFTERWRITE	B_INVAL

/*
 * The IO_METASYNC flag should be implemented for local file systems.
 * (Until then, it is nothin at all.)
 */
#ifndef IO_METASYNC
#define IO_METASYNC	0
#endif

/*
E 24
 * Set the attribute timeout based on how recently the file has been modified.
 */
#define	NFS_ATTRTIMEO(np) \
	((((np)->n_flag & NMODIFIED) || \
D 20
	 5 * (time.tv_sec - (np)->n_mtime) < NFS_MINATTRTIMO) ? NFS_MINATTRTIMO : \
	 (5 * (time.tv_sec - (np)->n_mtime) > NFS_MAXATTRTIMO ? NFS_MAXATTRTIMO : \
	  5 * (time.tv_sec - (np)->n_mtime)))
E 20
I 20
	 (time.tv_sec - (np)->n_mtime) / 10 < NFS_MINATTRTIMO) ? NFS_MINATTRTIMO : \
	 ((time.tv_sec - (np)->n_mtime) / 10 > NFS_MAXATTRTIMO ? NFS_MAXATTRTIMO : \
	  (time.tv_sec - (np)->n_mtime) / 10))
E 20
E 19
E 4

I 8
/*
I 24
 * Expected allocation sizes for major data structures. If the actual size
 * of the structure exceeds these sizes, then malloc() will be allocating
 * almost twice the memory required. This is used in nfs_init() to warn
 * the sysadmin that the size of a structure should be reduced.
 * (These sizes are always a power of 2. If the kernel malloc() changes
 *  to one that does not allocate space in powers of 2 size, then this all
 *  becomes bunk!)
 */
#define NFS_NODEALLOC	256
#define NFS_MNTALLOC	512
#define NFS_SVCALLOC	256
#define NFS_UIDALLOC	128

/*
 * Arguments to mount NFS
 */
I 25
#define NFS_ARGSVERSION	3		/* change when nfs_args changes */
E 25
struct nfs_args {
I 25
	int		version;	/* args structure version number */
E 25
	struct sockaddr	*addr;		/* file server address */
	int		addrlen;	/* length of address */
	int		sotype;		/* Socket type */
	int		proto;		/* and Protocol */
	u_char		*fh;		/* File handle to be mounted */
	int		fhsize;		/* Size, in bytes, of fh */
	int		flags;		/* flags */
	int		wsize;		/* write size in bytes */
	int		rsize;		/* read size in bytes */
	int		readdirsize;	/* readdir size in bytes */
	int		timeo;		/* initial timeout in .1 secs */
	int		retrans;	/* times to retry send */
	int		maxgrouplist;	/* Max. size of group list */
	int		readahead;	/* # of blocks to readahead */
	int		leaseterm;	/* Term (sec) of lease */
	int		deadthresh;	/* Retrans threshold */
	char		*hostname;	/* server's name */
};

/*
 * NFS mount option flags
 */
#define	NFSMNT_SOFT		0x00000001  /* soft mount (hard is default) */
#define	NFSMNT_WSIZE		0x00000002  /* set write size */
#define	NFSMNT_RSIZE		0x00000004  /* set read size */
#define	NFSMNT_TIMEO		0x00000008  /* set initial timeout */
#define	NFSMNT_RETRANS		0x00000010  /* set number of request retries */
#define	NFSMNT_MAXGRPS		0x00000020  /* set maximum grouplist size */
#define	NFSMNT_INT		0x00000040  /* allow interrupts on hard mount */
#define	NFSMNT_NOCONN		0x00000080  /* Don't Connect the socket */
#define	NFSMNT_NQNFS		0x00000100  /* Use Nqnfs protocol */
#define	NFSMNT_NFSV3		0x00000200  /* Use NFS Version 3 protocol */
#define	NFSMNT_KERB		0x00000400  /* Use Kerberos authentication */
#define	NFSMNT_DUMBTIMR		0x00000800  /* Don't estimate rtt dynamically */
#define	NFSMNT_LEASETERM	0x00001000  /* set lease term (nqnfs) */
#define	NFSMNT_READAHEAD	0x00002000  /* set read ahead */
#define	NFSMNT_DEADTHRESH	0x00004000  /* set dead server retry thresh */
#define	NFSMNT_RESVPORT		0x00008000  /* Allocate a reserved port */
#define	NFSMNT_RDIRPLUS		0x00010000  /* Use Readdirplus for V3 */
#define	NFSMNT_READDIRSIZE	0x00020000  /* Set readdir size */
#define	NFSMNT_INTERNAL		0xfffc0000  /* Bits set internally */
#define NFSMNT_HASWRITEVERF	0x00040000  /* Has write verifier for V3 */
#define NFSMNT_GOTPATHCONF	0x00080000  /* Got the V3 pathconf info */
#define NFSMNT_GOTFSINFO	0x00100000  /* Got the V3 fsinfo */
#define	NFSMNT_MNTD		0x00200000  /* Mnt server for mnt point */
#define	NFSMNT_DISMINPROG	0x00400000  /* Dismount in progress */
#define	NFSMNT_DISMNT		0x00800000  /* Dismounted */
#define	NFSMNT_SNDLOCK		0x01000000  /* Send socket lock */
#define	NFSMNT_WANTSND		0x02000000  /* Want above */
#define	NFSMNT_RCVLOCK		0x04000000  /* Rcv socket lock */
#define	NFSMNT_WANTRCV		0x08000000  /* Want above */
#define	NFSMNT_WAITAUTH		0x10000000  /* Wait for authentication */
#define	NFSMNT_HASAUTH		0x20000000  /* Has authenticator */
#define	NFSMNT_WANTAUTH		0x40000000  /* Wants an authenticator */
#define	NFSMNT_AUTHERR		0x80000000  /* Authentication error */

/*
E 24
I 14
 * Structures for the nfssvc(2) syscall. Not that anyone but nfsd and mount_nfs
 * should ever try and use it.
 */
struct nfsd_args {
	int	sock;		/* Socket to serve */
D 24
	caddr_t	name;		/* Client address for connection based sockets */
E 24
I 24
	caddr_t	name;		/* Client addr for connection based sockets */
E 24
	int	namelen;	/* Length of name */
};

struct nfsd_srvargs {
	struct nfsd	*nsd_nfsd;	/* Pointer to in kernel nfsd struct */
	uid_t		nsd_uid;	/* Effective uid mapped to cred */
	u_long		nsd_haddr;	/* Ip address of client */
	struct ucred	nsd_cr;		/* Cred. uid maps to */
	int		nsd_authlen;	/* Length of auth string (ret) */
D 24
	char		*nsd_authstr;	/* Auth string (ret) */
E 24
I 24
	u_char		*nsd_authstr;	/* Auth string (ret) */
	int		nsd_verflen;	/* and the verfier */
	u_char		*nsd_verfstr;
	struct timeval	nsd_timestamp;	/* timestamp from verifier */
	u_long		nsd_ttl;	/* credential ttl (sec) */
	NFSKERBKEY_T	nsd_key;	/* Session key */
E 24
};

struct nfsd_cargs {
	char		*ncd_dirp;	/* Mount dir path */
	uid_t		ncd_authuid;	/* Effective uid */
	int		ncd_authtype;	/* Type of authenticator */
	int		ncd_authlen;	/* Length of authenticator string */
D 24
	char		*ncd_authstr;	/* Authenticator string */
E 24
I 24
	u_char		*ncd_authstr;	/* Authenticator string */
	int		ncd_verflen;	/* and the verifier */
	u_char		*ncd_verfstr;
	NFSKERBKEY_T	ncd_key;	/* Session key */
E 24
};

/*
 * Stats structure
 */
struct nfsstats {
	int	attrcache_hits;
	int	attrcache_misses;
	int	lookupcache_hits;
	int	lookupcache_misses;
	int	direofcache_hits;
	int	direofcache_misses;
	int	biocache_reads;
	int	read_bios;
	int	read_physios;
	int	biocache_writes;
	int	write_bios;
	int	write_physios;
	int	biocache_readlinks;
	int	readlink_bios;
	int	biocache_readdirs;
	int	readdir_bios;
	int	rpccnt[NFS_NPROCS];
	int	rpcretries;
	int	srvrpccnt[NFS_NPROCS];
	int	srvrpc_errs;
	int	srv_errs;
	int	rpcrequests;
	int	rpctimeouts;
	int	rpcunexpected;
	int	rpcinvalid;
	int	srvcache_inproghits;
	int	srvcache_idemdonehits;
	int	srvcache_nonidemdonehits;
	int	srvcache_misses;
	int	srvnqnfs_leases;
	int	srvnqnfs_maxleases;
	int	srvnqnfs_getleases;
I 24
	int	srvvop_writes;
E 24
};

/*
 * Flags for nfssvc() system call.
 */
#define	NFSSVC_BIOD	0x002
#define	NFSSVC_NFSD	0x004
#define	NFSSVC_ADDSOCK	0x008
#define	NFSSVC_AUTHIN	0x010
#define	NFSSVC_GOTAUTH	0x040
#define	NFSSVC_AUTHINFAIL 0x080
#define	NFSSVC_MNTD	0x100

/*
I 24
 * fs.nfs sysctl(3) identifiers
 */
#define NFS_NFSSTATS	1		/* struct: struct nfsstats */

#define FS_NFS_NAMES { \
		       { 0, 0 }, \
		       { "nfsstats", CTLTYPE_STRUCT }, \
}

/*
E 24
E 14
 * The set of signals the interrupt an I/O in progress for NFSMNT_INT mounts.
 * What should be in this set is open to debate, but I believe that since
 * I/O system calls on ufs are never interrupted by signals the set should
 * be minimal. My reasoning is that many current programs that use signals
 * such as SIGALRM will not expect file I/O system calls to be interrupted
 * by them and break.
 */
I 14
#ifdef KERNEL
I 24

struct uio; struct buf; struct vattr; struct nameidata;	/* XXX */

E 24
E 14
#define	NFSINT_SIGMASK	(sigmask(SIGINT)|sigmask(SIGTERM)|sigmask(SIGKILL)| \
			 sigmask(SIGHUP)|sigmask(SIGQUIT))
E 8
I 6

E 6
/*
I 8
 * Socket errors ignored for connectionless sockets??
 * For now, ignore them all
 */
#define	NFSIGNORE_SOERROR(s, e) \
		((e) != EINTR && (e) != ERESTART && (e) != EWOULDBLOCK && \
		((s) & PR_CONNREQUIRED) == 0)

/*
E 8
 * Nfs outstanding request list element
 */
struct nfsreq {
D 23
	struct nfsreq	*r_next;
	struct nfsreq	*r_prev;
E 23
I 23
	TAILQ_ENTRY(nfsreq) r_chain;
E 23
	struct mbuf	*r_mreq;
	struct mbuf	*r_mrep;
I 14
	struct mbuf	*r_md;
	caddr_t		r_dpos;
E 14
D 8
	struct nfsmount *r_mntp;
E 8
I 8
	struct nfsmount *r_nmp;
E 8
	struct vnode	*r_vp;
D 8
	int		r_msiz;
E 8
	u_long		r_xid;
I 4
D 6
	u_long		r_inaddr;
E 4
	u_long		r_retry;
	u_long		r_timeout;
	u_long		r_timer;
E 6
I 6
D 14
	short		r_flags;	/* flags on request, see below */
	short		r_retry;	/* max retransmission count */
	short		r_rexmit;	/* current retrans count */
	short		r_timer;	/* tick counter on reply */
	short		r_timerinit;	/* reinit tick counter on reply */
E 14
I 14
	int		r_flags;	/* flags on request, see below */
	int		r_retry;	/* max retransmission count */
	int		r_rexmit;	/* current retrans count */
	int		r_timer;	/* tick counter on reply */
	int		r_procnum;	/* NFS procedure number */
	int		r_rtt;		/* RTT for rpc */
E 14
I 8
	struct proc	*r_procp;	/* Proc that did I/O system call */
E 8
E 6
};

I 23
/*
 * Queue head for nfsreq's
 */
D 24
TAILQ_HEAD(nfsreqs, nfsreq) nfs_reqq;
E 24
I 24
TAILQ_HEAD(, nfsreq) nfs_reqq;
E 24

E 23
I 6
/* Flag values for r_flags */
#define R_TIMING	0x01		/* timing request (in mntp) */
#define R_SENT		0x02		/* request has been sent */
I 8
#define	R_SOFTTERM	0x04		/* soft mnt, too many retries */
#define	R_INTR		0x08		/* intr mnt, signal pending */
#define	R_SOCKERR	0x10		/* Fatal error on socket */
#define	R_TPRINTFMSG	0x20		/* Did a tprintf msg. */
#define	R_MUSTRESEND	0x40		/* Must resend request */
I 21
#define	R_GETONEREP	0x80		/* Probe for one reply only */
E 21
E 8

D 14
#ifdef	KERNEL
E 14
I 14
D 24
struct nfsstats nfsstats;

E 24
E 14
E 6
/*
D 14
 * Silly rename structure that hangs off the nfsnode until the name
 * can be removed by nfs_inactive()
E 14
I 14
 * A list of nfssvc_sock structures is maintained with all the sockets
 * that require service by the nfsd.
 * The nfsuid structs hang off of the nfssvc_sock structs in both lru
 * and uid hash lists.
E 14
 */
D 14
struct sillyrename {
D 12
	int	s_flag;
E 12
	nfsv2fh_t s_fh;
D 12
	struct nameidata s_namei;
E 12
I 12
	struct	ucred *s_cred;
	struct	vnode *s_dvp;
D 13
	u_short	s_namlen;
E 13
I 13
	long	s_namlen;
E 13
	char	s_name[20];
E 14
I 14
D 24
#define	NUIDHASHSIZ	32
E 24
I 24
#ifndef NFS_UIDHASHSIZ
#define	NFS_UIDHASHSIZ	29	/* Tune the size of nfssvc_sock with this */
#endif
E 24
D 23
#define	NUIDHASH(uid)	((uid) & (NUIDHASHSIZ - 1))
E 23
I 23
#define	NUIDHASH(sock, uid) \
D 24
	(&(sock)->ns_uidhashtbl[(uid) & (sock)->ns_uidhash])
E 24
I 24
	(&(sock)->ns_uidhashtbl[(uid) % NFS_UIDHASHSIZ])
#ifndef NFS_WDELAYHASHSIZ
#define	NFS_WDELAYHASHSIZ 16	/* and with this */
#endif
#define	NWDELAYHASH(sock, f) \
	(&(sock)->ns_wdelayhashtbl[(*((u_long *)(f))) % NFS_WDELAYHASHSIZ])
#ifndef NFS_MUIDHASHSIZ
#define NFS_MUIDHASHSIZ	67	/* Tune the size of nfsmount with this */
#endif
#define	NMUIDHASH(nmp, uid) \
	(&(nmp)->nm_uidhashtbl[(uid) % NFS_MUIDHASHSIZ])
#define	NFSNOHASH(fhsum) \
	(&nfsnodehashtbl[(fhsum) & nfsnodehash])
E 24
E 23

I 18
/*
 * Network address hash list element
 */
union nethostaddr {
	u_long had_inetaddr;
	struct mbuf *had_nam;
};

E 18
struct nfsuid {
D 23
	struct nfsuid	*nu_lrunext;	/* MUST be first */
	struct nfsuid	*nu_lruprev;
	struct nfsuid	*nu_hnext;
	struct nfsuid	*nu_hprev;
E 23
I 23
	TAILQ_ENTRY(nfsuid) nu_lru;	/* LRU chain */
	LIST_ENTRY(nfsuid) nu_hash;	/* Hash list */
E 23
	int		nu_flag;	/* Flags */
D 24
	uid_t		nu_uid;		/* Uid mapped by this entry */
E 24
	union nethostaddr nu_haddr;	/* Host addr. for dgram sockets */
	struct ucred	nu_cr;		/* Cred uid mapped to */
I 24
	int		nu_expire;	/* Expiry time (sec) */
	struct timeval	nu_timestamp;	/* Kerb. timestamp */
	u_long		nu_nickname;	/* Nickname on server */
	NFSKERBKEY_T	nu_key;		/* and session key */
E 24
E 14
E 12
};

D 14
/* And its flag values */
#define REMOVE		0
#define	RMDIR		1
I 6
#endif	/* KERNEL */
E 14
I 14
#define	nu_inetaddr	nu_haddr.had_inetaddr
#define	nu_nam		nu_haddr.had_nam
/* Bits for nu_flag */
#define	NU_INETADDR	0x1
I 24
#define NU_NAM		0x2
#define NU_NETFAM(u)	(((u)->nu_flag & NU_INETADDR) ? AF_INET : AF_ISO)
E 24
E 14
E 6

I 14
struct nfssvc_sock {
D 23
	struct nfsuid	*ns_lrunext;	/* MUST be first */
	struct nfsuid	*ns_lruprev;
	struct nfssvc_sock *ns_next;
	struct nfssvc_sock *ns_prev;
E 23
I 23
	TAILQ_ENTRY(nfssvc_sock) ns_chain;	/* List of all nfssvc_sock's */
D 24
	TAILQ_HEAD(nfsuidlru, nfsuid) ns_uidlruhead;
	LIST_HEAD(nfsuidhash, nfsuid) *ns_uidhashtbl;
	u_long		ns_uidhash;

E 23
	int		ns_flag;
	u_long		ns_sref;
E 24
I 24
	TAILQ_HEAD(, nfsuid) ns_uidlruhead;
E 24
	struct file	*ns_fp;
	struct socket	*ns_so;
D 24
	int		ns_solock;
E 24
	struct mbuf	*ns_nam;
D 24
	int		ns_cc;
E 24
	struct mbuf	*ns_raw;
	struct mbuf	*ns_rawend;
D 24
	int		ns_reclen;
E 24
	struct mbuf	*ns_rec;
	struct mbuf	*ns_recend;
I 24
	struct mbuf	*ns_frag;
	int		ns_flag;
	int		ns_solock;
	int		ns_cc;
	int		ns_reclen;
E 24
	int		ns_numuids;
I 24
	u_long		ns_sref;
	LIST_HEAD(, nfsrv_descript) ns_tq;	/* Write gather lists */
	LIST_HEAD(, nfsuid) ns_uidhashtbl[NFS_UIDHASHSIZ];
	LIST_HEAD(nfsrvw_delayhash, nfsrv_descript) ns_wdelayhashtbl[NFS_WDELAYHASHSIZ];
E 24
D 23
	struct nfsuid	*ns_uidh[NUIDHASHSIZ];
E 23
};

/* Bits for "ns_flag" */
#define	SLP_VALID	0x01
D 15
#define	SLP_GOTIT	0x02
E 15
I 15
#define	SLP_DOREC	0x02
E 15
#define	SLP_NEEDQ	0x04
#define	SLP_DISCONN	0x08
#define	SLP_GETSTREAM	0x10
I 24
#define	SLP_LASTFRAG	0x20
E 24
I 17
D 23
#define	SLP_INIT	0x20
#define	SLP_WANTINIT	0x40
E 17

E 23
I 17
#define SLP_ALLFLAGS	0xff

I 23
D 24
TAILQ_HEAD(nfssvc_socks, nfssvc_sock) nfssvc_sockhead;
E 24
I 24
TAILQ_HEAD(, nfssvc_sock) nfssvc_sockhead;
E 24
int nfssvc_sockhead_flag;
#define	SLP_INIT	0x01
#define	SLP_WANTINIT	0x02

E 23
E 17
E 14
/*
D 14
 * Stats structure
E 14
I 14
 * One of these structures is allocated for each nfsd.
E 14
 */
D 14
struct nfsstats {
	int	attrcache_hits;
	int	attrcache_misses;
	int	lookupcache_hits;
	int	lookupcache_misses;
I 7
	int	direofcache_hits;
	int	direofcache_misses;
E 7
I 5
	int	biocache_reads;
	int	read_bios;
	int	read_physios;
	int	biocache_writes;
	int	write_bios;
	int	write_physios;
I 8
	int	biocache_readlinks;
	int	readlink_bios;
	int	biocache_readdirs;
	int	readdir_bios;
E 8
E 5
	int	rpccnt[NFS_NPROCS];
	int	rpcretries;
	int	srvrpccnt[NFS_NPROCS];
	int	srvrpc_errs;
	int	srv_errs;
I 6
	int	rpcrequests;
	int	rpctimeouts;
	int	rpcunexpected;
	int	rpcinvalid;
E 6
I 5
	int	srvcache_inproghits;
	int	srvcache_idemdonehits;
	int	srvcache_nonidemdonehits;
	int	srvcache_misses;
E 14
I 14
struct nfsd {
D 23
	struct nfsd	*nd_next;	/* Must be first */
	struct nfsd	*nd_prev;
E 23
I 23
D 24
	TAILQ_ENTRY(nfsd) nd_chain;	/* List of all nfsd's */
E 23
	int		nd_flag;	/* NFSD_ flags */
	struct nfssvc_sock *nd_slp;	/* Current socket */
D 15
	u_long		nd_sref;
E 15
	struct mbuf	*nd_nam;	/* Client addr for datagram req. */
	struct mbuf	*nd_mrep;	/* Req. mbuf list */
	struct mbuf	*nd_md;
	caddr_t		nd_dpos;	/* Position in list */
	int		nd_procnum;	/* RPC procedure number */
	u_long		nd_retxid;	/* RPC xid */
	int		nd_repstat;	/* Reply status value */
	struct ucred	nd_cr;		/* Credentials for req. */
	int		nd_nqlflag;	/* Leasing flag */
	int		nd_duration;	/* Lease duration */
	int		nd_authlen;	/* Authenticator len */
	u_char		nd_authstr[RPCAUTH_MAXSIZ]; /* Authenticator data */
	struct proc	*nd_procp;	/* Proc ptr */
E 24
I 24
	TAILQ_ENTRY(nfsd) nfsd_chain;	/* List of all nfsd's */
	int		nfsd_flag;	/* NFSD_ flags */
	struct nfssvc_sock *nfsd_slp;	/* Current socket */
	int		nfsd_authlen;	/* Authenticator len */
	u_char		nfsd_authstr[RPCAUTH_MAXSIZ]; /* Authenticator data */
	int		nfsd_verflen;	/* and the Verifier */
	u_char		nfsd_verfstr[RPCVERF_MAXSIZ];
	struct proc	*nfsd_procp;	/* Proc ptr */
	struct nfsrv_descript *nfsd_nd;	/* Associated nfsrv_descript */
E 24
E 14
E 5
};

I 23
D 24
/* Bits for "nd_flag" */
E 24
I 24
/* Bits for "nfsd_flag" */
E 24
E 23
D 14
#ifdef KERNEL
struct nfsstats nfsstats;
D 6
#endif
E 6
I 6
#endif /* KERNEL */
E 14
I 14
#define	NFSD_WAITING	0x01
D 23
#define	NFSD_CHECKSLP	0x02
#define	NFSD_REQINPROG	0x04
#define	NFSD_NEEDAUTH	0x08
#define	NFSD_AUTHFAIL	0x10
E 23
I 23
#define	NFSD_REQINPROG	0x02
#define	NFSD_NEEDAUTH	0x04
#define	NFSD_AUTHFAIL	0x08

D 24
TAILQ_HEAD(nfsds, nfsd) nfsd_head;
E 24
I 24
/*
 * This structure is used by the server for describing each request.
 * Some fields are used only when write request gathering is performed.
 */
struct nfsrv_descript {
	u_quad_t		nd_time;	/* Write deadline (usec) */
	off_t			nd_off;		/* Start byte offset */
	off_t			nd_eoff;	/* and end byte offset */
	LIST_ENTRY(nfsrv_descript) nd_hash;	/* Hash list */
	LIST_ENTRY(nfsrv_descript) nd_tq;		/* and timer list */
	LIST_HEAD(,nfsrv_descript) nd_coalesce;	/* coalesced writes */
	struct mbuf		*nd_mrep;	/* Request mbuf list */
	struct mbuf		*nd_md;		/* Current dissect mbuf */
	struct mbuf		*nd_mreq;	/* Reply mbuf list */
	struct mbuf		*nd_nam;	/* and socket addr */
	struct mbuf		*nd_nam2;	/* return socket addr */
	caddr_t			nd_dpos;	/* Current dissect pos */
	int			nd_procnum;	/* RPC # */
	int			nd_stable;	/* storage type */
	int			nd_flag;	/* nd_flag */
	int			nd_len;		/* Length of this write */
	int			nd_repstat;	/* Reply status */
	u_long			nd_retxid;	/* Reply xid */
	u_long			nd_duration;	/* Lease duration */
	struct timeval		nd_starttime;	/* Time RPC initiated */
	fhandle_t		nd_fh;		/* File handle */
	struct ucred		nd_cr;		/* Credentials */
};

/* Bits for "nd_flag" */
#define	ND_READ		LEASE_READ
#define ND_WRITE	LEASE_WRITE
#define ND_CHECK	0x04
#define ND_LEASE	(ND_READ | ND_WRITE | ND_CHECK)
#define ND_NFSV3	0x08
#define ND_NQNFS	0x10
#define ND_KERBNICK	0x20
#define ND_KERBFULL	0x40
#define ND_KERBAUTH	(ND_KERBNICK | ND_KERBFULL)

TAILQ_HEAD(, nfsd) nfsd_head;
E 24
int nfsd_head_flag;
#define	NFSD_CHECKSLP	0x01

I 24
/*
 * These macros compare nfsrv_descript structures.
 */
#define NFSW_CONTIG(o, n) \
		((o)->nd_eoff >= (n)->nd_off && \
		 !bcmp((caddr_t)&(o)->nd_fh, (caddr_t)&(n)->nd_fh, NFSX_V3FH))

#define NFSW_SAMECRED(o, n) \
	(((o)->nd_flag & ND_KERBAUTH) == ((n)->nd_flag & ND_KERBAUTH) && \
 	 !bcmp((caddr_t)&(o)->nd_cr, (caddr_t)&(n)->nd_cr, \
		sizeof (struct ucred)))

int	nfs_reply __P((struct nfsreq *));
int	nfs_getreq __P((struct nfsrv_descript *,struct nfsd *,int));
int	nfs_send __P((struct socket *,struct mbuf *,struct mbuf *,struct nfsreq *));
int	nfs_rephead __P((int,struct nfsrv_descript *,struct nfssvc_sock *,int,int,u_quad_t *,struct mbuf **,struct mbuf **,caddr_t *));
int	nfs_sndlock __P((int *,struct nfsreq *));
int	nfs_disct __P((struct mbuf **,caddr_t *,int,int,caddr_t *));
int	nfs_vinvalbuf __P((struct vnode *,int,struct ucred *,struct proc *,int));
int	nfs_readrpc __P((struct vnode *,struct uio *,struct ucred *));
int	nfs_writerpc __P((struct vnode *,struct uio *,struct ucred *,int *,int *));
int	nfs_readdirrpc __P((register struct vnode *,struct uio *,struct ucred *));
int	nfs_setattrrpc __P((struct vnode *,struct vattr *,struct ucred *,struct proc *));
int	nfs_asyncio __P((struct buf *,struct ucred *));
int	nfs_doio __P((struct buf *,struct ucred *,struct proc *));
int	nfs_readlinkrpc __P((struct vnode *,struct uio *,struct ucred *));
int	nfs_sigintr __P((struct nfsmount *,struct nfsreq *r,struct proc *));
int	nfs_readdirplusrpc __P((struct vnode *,register struct uio *,struct ucred *));
int	nfsm_disct __P((struct mbuf **,caddr_t *,int,int,caddr_t *));
void	nfsm_srvfattr __P((struct nfsrv_descript *,struct vattr *,struct nfs_fattr *));
void	nfsm_srvwcc __P((struct nfsrv_descript *,int,struct vattr *,int,struct vattr *,struct mbuf **,char **));
void	nfsm_srvpostopattr __P((struct nfsrv_descript *,int,struct vattr *,struct mbuf **,char **));
int	nfsrv_fhtovp __P((fhandle_t *,int,struct vnode **,struct ucred *,struct nfssvc_sock *,struct mbuf *,int *,int));
int	nfsrv_access __P((struct vnode *,int,struct ucred *,int,struct proc *));
int	netaddr_match __P((int,union nethostaddr *,struct mbuf *));
int	nfs_request __P((struct vnode *,struct mbuf *,int,struct proc *,struct ucred *,struct mbuf **,struct mbuf **,caddr_t *));
int	nfs_loadattrcache __P((struct vnode **,struct mbuf **,caddr_t *,struct vattr *));
int	nfs_namei __P((struct nameidata *,fhandle_t *,int,struct nfssvc_sock *,struct mbuf *,struct mbuf **,caddr_t *,struct vnode **,struct proc *,int));
void	nfsm_adj __P((struct mbuf *,int,int));
int	nfsm_mbuftouio __P((struct mbuf **,struct uio *,int,caddr_t *));
void	nfsrv_initcache __P((void));
int	nfs_rcvlock __P((struct nfsreq *));
int	nfs_getauth __P((struct nfsmount *,struct nfsreq *,struct ucred *,char **,int *,char *,int *,NFSKERBKEY_T));
int	nfs_getnickauth __P((struct nfsmount *,struct ucred *,char **,int *,char *,int));
int	nfs_savenickauth __P((struct nfsmount *,struct ucred *,int,NFSKERBKEY_T,struct mbuf **,char **,struct mbuf *));
int	nfs_msg __P((struct proc *,char *,char *));
int	nfs_adv __P((struct mbuf **,caddr_t *,int,int));
int	nfsrv_getstream __P((struct nfssvc_sock *,int));
void	nfs_nhinit __P((void));
void	nfs_timer __P((void*));
u_long nfs_hash __P((nfsfh_t *,int));
int	nfssvc_iod __P((struct proc *));
int	nfssvc_nfsd __P((struct nfsd_srvargs *,caddr_t,struct proc *));
int	nfssvc_addsock __P((struct file *,struct mbuf *));
int	nfsrv_dorec __P((struct nfssvc_sock *,struct nfsd *,struct nfsrv_descript **));
int	nfsrv_getcache __P((struct nfsrv_descript *,struct nfssvc_sock *,struct mbuf **));
void	nfsrv_updatecache __P((struct nfsrv_descript *,int,struct mbuf *));
int	mountnfs __P((struct nfs_args *,struct mount *,struct mbuf *,char *,char *,struct vnode **));
int	nfs_connect __P((struct nfsmount *,struct nfsreq *));
int	nfs_getattrcache __P((struct vnode *,struct vattr *));
int	nfsm_strtmbuf __P((struct mbuf **,char **,char *,long));
int	nfs_bioread __P((struct vnode *,struct uio *,int,struct ucred *));
int	nfsm_uiotombuf __P((struct uio *,struct mbuf **,int,caddr_t *));
void	nfsrv_init __P((int));
void	nfs_clearcommit __P((struct mount *));
int	nfsrv_errmap __P((struct nfsrv_descript *, int));
void	nfsrvw_coalesce __P((struct nfsrv_descript *,struct nfsrv_descript *));
void	nfsrvw_sort __P((gid_t [],int));
void	nfsrv_setcred __P((struct ucred *,struct ucred *));
int	nfs_flush __P((struct vnode *,struct ucred *,int,struct proc *,int));
int	nfs_writebp __P((struct buf *,int));
E 24
E 23
#endif	/* KERNEL */
I 24

#endif
E 24
I 16
D 17
#define	SLP_INIT	0x20
#define	SLP_WANTINIT	0x40
E 17
E 16
E 14
E 6
E 1
