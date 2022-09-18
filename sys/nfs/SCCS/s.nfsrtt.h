h44335
s 00007/00000/00070
d D 8.2 95/03/30 11:26:57 mckusick 4 3
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00002/00002/00068
d D 8.1 93/06/10 23:39:49 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00051/00011/00019
d D 7.2 93/02/02 14:33:27 mckusick 2 1
c update for 4.4BSD from Rick Macklem
e
s 00030/00000/00000
d D 7.1 92/01/07 21:08:51 mckusick 1 0
c new modules for NFS from Rick Macklem
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 4

#ifndef _NFS_NFSRTT_H_
#define _NFS_NFSRTT_H_

E 4
/*
D 2
 * Definitions for client side performance monitor.
E 2
I 2
 * Definitions for performance monitor.
 * The client and server logging are turned on by setting the global
 * constant "nfsrtton" to 1.
E 2
 */
#define	NFSRTTLOGSIZ	128
I 2

/*
 * Circular log of client side rpc activity. Each log entry is for one
 * rpc filled in upon completion. (ie. in order of completion)
 * The "pos" is the table index for the "next" entry, therefore the
 * list goes from nfsrtt.rttl[pos] --> nfsrtt.rttl[pos - 1] in
 * chronological order of completion.
 */
E 2
struct nfsrtt {
D 2
	int pos;
E 2
I 2
	int pos;			/* Position in array for next entry */
E 2
	struct rttl {
D 2
		int	proc;
		int	rtt;
		int	rto;
		int	sent;
		int	cwnd;
		int	srtt;
		int	sdrtt;
		fsid_t	fsid;
		struct timeval tstamp;
E 2
I 2
		int	proc;		/* NFS procedure number */
		int	rtt;		/* Measured round trip time */
		int	rto;		/* Round Trip Timeout */
		int	sent;		/* # rpcs in progress */
		int	cwnd;		/* Send window */
		int	srtt;		/* Ave Round Trip Time */
		int	sdrtt;		/* Ave mean deviation of RTT */
		fsid_t	fsid;		/* Fsid for mount point */
		struct timeval tstamp;	/* Timestamp of log entry */
E 2
	} rttl[NFSRTTLOGSIZ];
I 2
};

/*
 * And definitions for server side performance monitor.
 * The log organization is the same as above except it is filled in at the
 * time the server sends the rpc reply.
 */

/*
 * Bits for the flags field.
 */
#define	DRT_NQNFS	0x01	/* Rpc used Nqnfs protocol */
#define	DRT_TCP		0x02	/* Client used TCP transport */
#define	DRT_CACHEREPLY	0x04	/* Reply was from recent request cache */
#define	DRT_CACHEDROP	0x08	/* Rpc request dropped, due to recent reply */
I 4
#define DRT_NFSV3	0x10	/* Rpc used NFS Version 3 */
E 4

/*
 * Server log structure
 * NB: ipadr == INADDR_ANY indicates a client using a non IP protocol.
 *	(ISO perhaps?)
 */
struct nfsdrt {
	int pos;			/* Position of next log entry */
	struct drt {
		int	flag;		/* Bits as defined above */
		int	proc;		/* NFS procedure number */
		u_long	ipadr;		/* IP address of client */
		int	resptime;	/* Response time (usec) */
		struct timeval tstamp;	/* Timestamp of log entry */
	} drt[NFSRTTLOGSIZ];
E 2
};
I 4

#endif
E 4
E 1
