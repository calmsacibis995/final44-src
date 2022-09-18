h59076
s 00007/00001/00055
d D 8.3 95/03/30 11:26:19 mckusick 10 9
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00002/00004/00054
d D 8.2 94/08/18 23:33:32 mckusick 9 8
c conversion to queue.h list manipulation (from mycroft)
e
s 00002/00002/00056
d D 8.1 93/06/10 23:39:53 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00005/00058
d D 7.7 93/05/20 13:09:01 mckusick 7 6
c performance fixes from Rick Macklem
e
s 00001/00000/00062
d D 7.6 93/02/02 14:52:33 mckusick 6 5
c update for 4.4BSD from Rick Macklem
e
s 00004/00007/00058
d D 7.5 92/07/22 15:24:52 mckusick 5 4
c update to current hashing techniques
e
s 00024/00026/00041
d D 7.4 92/01/14 12:41:05 mckusick 4 3
c update from Rick Macklem (including leases)
e
s 00001/00011/00066
d D 7.3 90/06/28 21:54:04 bostic 3 2
c new copyright notice
e
s 00001/00001/00076
d D 7.2 90/05/14 11:35:10 mckusick 2 1
c "update from Rick Macklem adding TCP support to NFS"
e
s 00077/00000/00000
d D 7.1 89/12/20 11:56:28 mckusick 1 0
c from Rick Macklem
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

I 10

#ifndef _NFS_NFSRVCACHE_H_
#define _NFS_NFSRVCACHE_H_

E 10
/*
 * Definitions for the server recent request cache
 */

D 4
#define	NFSRVCACHESIZ	128
#define	NFSRCHSZ	32
E 4
I 4
D 10
#define	NFSRVCACHESIZ	256
E 10
I 10
#define	NFSRVCACHESIZ	64
E 10
D 5
#define	NFSRCHSZ	256
E 5
E 4

struct nfsrvcache {
D 5
	struct	nfsrvcache *rc_chain[2];	/* Hash chain links */
D 4
	struct	nfsrvcache *rc_next;	/* Lru list */
	struct	nfsrvcache *rc_prev;
	int	rc_state;		/* Current state of request */
	int	rc_flag;		/* Flag bits */
D 2
	u_long	rc_saddr;		/* Internet addr. of requestor */
E 2
I 2
	struct	mbuf rc_nam;		/* Sockaddr of requestor */
E 2
	u_long	rc_xid;			/* rpc id number */
	int	rc_proc;		/* rpc proc number */
	long	rc_timestamp;		/* Time stamp */
E 4
I 4
	struct	nfsrvcache *rc_lchain[2];	/* Lru list */
E 5
I 5
D 9
	struct	nfsrvcache *rc_forw;		/* Hash chain links */
	struct	nfsrvcache **rc_back;		/* Hash chain links */
	struct	nfsrvcache *rc_next;		/* Lru list */
	struct	nfsrvcache **rc_prev;		/* Lru list */
E 9
I 9
	TAILQ_ENTRY(nfsrvcache) rc_lru;		/* LRU chain */
	LIST_ENTRY(nfsrvcache) rc_hash;		/* Hash chain */
E 9
E 5
	u_long	rc_xid;				/* rpc id number */
D 7
	time_t	rc_timestamp;			/* Time stamp */
E 7
E 4
	union {
D 4
		struct mbuf *rc_repmb;	/* Reply mbuf list OR */
		int rc_repstat;		/* Reply status */
E 4
I 4
		struct mbuf *ru_repmb;		/* Reply mbuf list OR */
		int ru_repstat;			/* Reply status */
E 4
	} rc_un;
I 4
	union nethostaddr rc_haddr;		/* Host address */
	short	rc_proc;			/* rpc proc number */
	u_char	rc_state;		/* Current state of request */
	u_char	rc_flag;		/* Flag bits */
E 4
};

D 5
#define	rc_forw		rc_chain[0]
#define	rc_back		rc_chain[1]
D 4
#define	rc_status	rc_un.rc_repstat
#define	rc_reply	rc_un.rc_repmb
E 4
I 4
#define	rc_next		rc_lchain[0]
#define	rc_prev		rc_lchain[1]
E 5
#define	rc_reply	rc_un.ru_repmb
#define	rc_status	rc_un.ru_repstat
#define	rc_inetaddr	rc_haddr.had_inetaddr
#define	rc_nam		rc_haddr.had_nam
E 4

D 4
#define	put_at_head(rp) \
		(rp)->rc_prev->rc_next = (rp)->rc_next; \
		(rp)->rc_next->rc_prev = (rp)->rc_prev; \
		(rp)->rc_next = nfsrvcachehead.rc_next; \
		(rp)->rc_next->rc_prev = (rp); \
		nfsrvcachehead.rc_next = (rp); \
		(rp)->rc_prev = &nfsrvcachehead

E 4
/* Cache entry states */
#define	RC_UNUSED	0
#define	RC_INPROG	1
#define	RC_DONE		2

/* Return values */
#define	RC_DROPIT	0
#define	RC_REPLY	1
#define	RC_DOIT		2
I 6
#define	RC_CHECKIT	3
E 6

/* Flag bits */
D 4
#define	RC_LOCKED	0x1
#define	RC_WANTED	0x2
#define	RC_REPSTATUS	0x4
#define	RC_REPMBUF	0x8
E 4
I 4
#define	RC_LOCKED	0x01
#define	RC_WANTED	0x02
#define	RC_REPSTATUS	0x04
#define	RC_REPMBUF	0x08
#define	RC_NQNFS	0x10
#define	RC_INETADDR	0x20
#define	RC_NAM		0x40
I 10

#endif
E 10
E 4
D 7

/* Delay time after completion that request is dropped */
#define	RC_DELAY	2		/* seconds */

E 7
E 1
