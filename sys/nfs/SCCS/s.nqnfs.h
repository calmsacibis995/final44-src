h30301
s 00030/00017/00157
d D 8.3 95/03/30 11:26:59 mckusick 9 8
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00011/00009/00163
d D 8.2 94/08/18 23:33:50 mckusick 8 7
c conversion to queue.h list manipulation (from mycroft)
e
s 00002/00002/00170
d D 8.1 93/06/10 23:39:59 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00171
d D 7.6 93/05/03 18:36:58 mckusick 6 5
c the final polish to leases from Rick Macklem
e
s 00003/00003/00169
d D 7.5 92/09/16 18:06:37 mckusick 5 4
c update from Rick Macklem
e
s 00006/00004/00166
d D 7.4 92/07/22 15:25:12 mckusick 4 3
c update to current hashing techniques
e
s 00001/00001/00169
d D 7.3 92/03/13 18:08:02 mckusick 3 2
c up the default threshold for complaining about server not responding
e
s 00002/00002/00168
d D 7.2 92/03/09 22:27:42 mckusick 2 1
c first cut at fixing discconect/reconnect hanging confusion
e
s 00170/00000/00000
d D 7.1 92/01/07 21:08:51 mckusick 1 0
c new modules for NFS from Rick Macklem
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 9

#ifndef _NFS_NQNFS_H_
#define _NFS_NQNFS_H_

E 9
/*
 * Definitions for NQNFS (Not Quite NFS) cache consistency protocol.
 */

/* Tunable constants */
#define	NQ_CLOCKSKEW	3	/* Clock skew factor (sec) */
#define	NQ_WRITESLACK	5	/* Delay for write cache flushing */
D 5
#define	NQ_MAXLEASE	30	/* Max lease duration (sec) */
#define	NQ_MINLEASE	2	/* Min lease duration (sec) */
#define	NQ_DEFLEASE	10	/* Default lease duration (sec) */
E 5
I 5
#define	NQ_MAXLEASE	60	/* Max lease duration (sec) */
#define	NQ_MINLEASE	5	/* Min lease duration (sec) */
#define	NQ_DEFLEASE	30	/* Default lease duration (sec) */
E 5
#define	NQ_RENEWAL	3	/* Time before expiry (sec) to renew */
#define	NQ_TRYLATERDEL	15	/* Initial try later delay (sec) */
#define	NQ_MAXNUMLEASE	2048	/* Upper bound on number of server leases */
D 3
#define	NQ_DEADTHRESH	2	/* Default nm_deadthresh */
E 3
I 3
D 6
#define	NQ_DEADTHRESH	5	/* Default nm_deadthresh */
E 6
I 6
#define	NQ_DEADTHRESH	NQ_NEVERDEAD	/* Default nm_deadthresh */
E 6
E 3
#define	NQ_NEVERDEAD	9	/* Greater than max. nm_timeouts */
#define	NQLCHSZ		256	/* Server hash table size */

#define	NQNFS_PROG	300105	/* As assigned by Sun */
D 9
#define	NQNFS_VER1	1
E 9
I 9
#define	NQNFS_VER3	3
E 9
#define	NQNFS_EVICTSIZ	156	/* Size of eviction request in bytes */

/*
 * Definitions used for saving the "last lease expires" time in Non-volatile
 * RAM on the server. The default definitions below assume that NOVRAM is not
 * available.
 */
I 9
#ifdef HASNVRAM
#  undef HASNVRAM
#endif
E 9
#define	NQSTORENOVRAM(t)
#define	NQLOADNOVRAM(t)

/*
 * Defn and structs used on the server to maintain state for current leases.
 * The list of host(s) that hold the lease are kept as nqhost structures.
 * The first one lives in nqlease and any others are held in a linked
 * list of nqm structures hanging off of nqlease.
 *
 * Each nqlease structure is chained into two lists. The first is a list
 * ordered by increasing expiry time for nqsrv_timer() and the second is a chain
 * hashed on lc_fh.
 */
#define	LC_MOREHOSTSIZ	10

struct nqhost {
	union {
		struct {
			u_short udp_flag;
			u_short	udp_port;
			union nethostaddr udp_haddr;
		} un_udp;
		struct {
			u_short connless_flag;
			u_short connless_spare;
			union nethostaddr connless_haddr;
		} un_connless;
		struct {
			u_short conn_flag;
D 2
			u_short conn_sref;
E 2
I 2
			u_short conn_spare;
E 2
			struct nfssvc_sock *conn_slp;
		} un_conn;
	} lph_un;
};
#define	lph_flag	lph_un.un_udp.udp_flag
#define	lph_port	lph_un.un_udp.udp_port
#define	lph_haddr	lph_un.un_udp.udp_haddr
#define	lph_inetaddr	lph_un.un_udp.udp_haddr.had_inetaddr
#define	lph_claddr	lph_un.un_connless.connless_haddr
#define	lph_nam		lph_un.un_connless.connless_haddr.had_nam
D 2
#define	lph_sref	lph_un.un_conn.conn_sref
E 2
#define	lph_slp		lph_un.un_conn.conn_slp

struct nqlease {
D 8
	struct nqlease *lc_chain1[2];	/* Timer queue list (must be first) */
	struct nqlease *lc_fhnext;	/* Fhandle hash list */
D 4
	struct nqlease *lc_fhprev;
E 4
I 4
	struct nqlease **lc_fhprev;
E 8
I 8
	LIST_ENTRY(nqlease) lc_hash;	/* Fhandle hash list */
	CIRCLEQ_ENTRY(nqlease) lc_timer; /* Timer queue list */
E 8
E 4
	time_t		lc_expiry;	/* Expiry time (sec) */
	struct nqhost	lc_host;	/* Host that got lease */
	struct nqm	*lc_morehosts;	/* Other hosts that share read lease */
	fsid_t		lc_fsid;	/* Fhandle */
	char		lc_fiddata[MAXFIDSZ];
	struct vnode	*lc_vp;		/* Soft reference to associated vnode */
};
#define	lc_flag		lc_host.lph_un.un_udp.udp_flag

/* lc_flag bits */
#define	LC_VALID	0x0001	/* Host address valid */
#define	LC_WRITE	0x0002	/* Write cache */
#define	LC_NONCACHABLE	0x0004	/* Non-cachable lease */
#define	LC_LOCKED	0x0008	/* Locked */
#define	LC_WANTED	0x0010	/* Lock wanted */
#define	LC_EXPIREDWANTED 0x0020	/* Want lease when expired */
#define	LC_UDP		0x0040	/* Host address for udp socket */
#define	LC_CLTP		0x0080	/* Host address for other connectionless */
#define	LC_LOCAL	0x0100	/* Host is server */
#define	LC_VACATED	0x0200	/* Host has vacated lease */
#define	LC_WRITTEN	0x0400	/* Recently wrote to the leased file */
I 2
#define	LC_SREF		0x0800	/* Holds a nfssvc_sock reference */
E 2

struct nqm {
	struct nqm	*lpm_next;
	struct nqhost	lpm_hosts[LC_MOREHOSTSIZ];
};

/*
D 9
 * Flag bits for flags argument to nqsrv_getlease.
 */
#define	NQL_READ	LEASE_READ	/* Read Request */
#define	NQL_WRITE	LEASE_WRITE	/* Write Request */
#define	NQL_CHECK	0x4		/* Check for lease */
#define	NQL_NOVAL	0xffffffff	/* Invalid */

/*
E 9
 * Special value for slp for local server calls.
 */
#define	NQLOCALSLP	((struct nfssvc_sock *) -1)

/*
 * Server side macros.
 */
#define	nqsrv_getl(v, l) \
		(void) nqsrv_getlease((v), &nfsd->nd_duration, \
D 9
		 ((nfsd->nd_nqlflag != 0 && nfsd->nd_nqlflag != NQL_NOVAL) ? nfsd->nd_nqlflag : \
		 ((l) | NQL_CHECK)), \
		 nfsd, nam, &cache, &frev, cred)
E 9
I 9
		 ((nfsd->nd_flag & ND_LEASE) ? (nfsd->nd_flag & ND_LEASE) : \
		 ((l) | ND_CHECK)), \
		 slp, procp, nfsd->nd_nam, &cache, &frev, cred)
E 9

/*
 * Client side macros that check for a valid lease.
 */
#define	NQNFS_CKINVALID(v, n, f) \
 ((time.tv_sec > (n)->n_expiry && \
 VFSTONFS((v)->v_mount)->nm_timeouts < VFSTONFS((v)->v_mount)->nm_deadthresh) \
D 9
  || ((f) == NQL_WRITE && ((n)->n_flag & NQNFSWRITE) == 0))
E 9
I 9
  || ((f) == ND_WRITE && ((n)->n_flag & NQNFSWRITE) == 0))
E 9

#define	NQNFS_CKCACHABLE(v, f) \
 ((time.tv_sec <= VTONFS(v)->n_expiry || \
  VFSTONFS((v)->v_mount)->nm_timeouts >= VFSTONFS((v)->v_mount)->nm_deadthresh) \
   && (VTONFS(v)->n_flag & NQNFSNONCACHE) == 0 && \
D 9
   ((f) == NQL_READ || (VTONFS(v)->n_flag & NQNFSWRITE)))
E 9
I 9
   ((f) == ND_READ || (VTONFS(v)->n_flag & NQNFSWRITE)))
E 9

#define	NQNFS_NEEDLEASE(v, p) \
		(time.tv_sec > VTONFS(v)->n_expiry ? \
		 ((VTONFS(v)->n_flag & NQNFSEVICTED) ? 0 : nqnfs_piggy[p]) : \
		 (((time.tv_sec + NQ_RENEWAL) > VTONFS(v)->n_expiry && \
		   nqnfs_piggy[p]) ? \
		   ((VTONFS(v)->n_flag & NQNFSWRITE) ? \
D 9
		    NQL_WRITE : nqnfs_piggy[p]) : 0))
E 9
I 9
		    ND_WRITE : nqnfs_piggy[p]) : 0))
E 9

/*
D 4
 * List heads for timer queues.
E 4
I 4
 * List head for timer queue.
E 4
 */
D 4
union nqsrvthead {
E 4
I 4
D 8
extern union nqsrvthead {
E 4
	union	nqsrvthead *th_head[2];
	struct	nqlease *th_chain[2];
D 4
};
E 4
I 4
} nqthead;
extern struct nqlease **nqfhead;
extern u_long nqfheadhash;
E 8
I 8
D 9
CIRCLEQ_HEAD(nqleases, nqlease) nqtimerhead;
E 9
I 9
CIRCLEQ_HEAD(, nqlease) nqtimerhead;
E 9

/*
 * List head for the file handle hash table.
 */
#define	NQFHHASH(f) \
	(&nqfhhashtbl[(*((u_long *)(f))) & nqfhhash])
LIST_HEAD(nqfhhashhead, nqlease) *nqfhhashtbl;
u_long nqfhhash;
E 8
E 4

/*
 * Nqnfs return status numbers.
 */
#define	NQNFS_EXPIRED	500
#define	NQNFS_TRYLATER	501
D 9
#define NQNFS_AUTHERR	502
E 9
I 9

#ifdef KERNEL
void	nqnfs_lease_updatetime __P((int));
int	nqsrv_cmpnam __P((struct nfssvc_sock *,struct mbuf *,struct nqhost *));
int	nqsrv_getlease __P((struct vnode *, u_long *, int,
		struct nfssvc_sock *, struct proc *, struct mbuf *, int *,
		u_quad_t *, struct ucred *));
int	nqnfs_getlease __P((struct vnode *, int, struct ucred *,struct proc *));
int	nqnfs_callback __P((struct nfsmount *, struct mbuf *, struct mbuf *,
		caddr_t));
int	nqnfs_clientd __P((struct nfsmount *, struct ucred *,
		struct nfsd_cargs *, int, caddr_t, struct proc *));
#endif

#endif
E 9
E 1
