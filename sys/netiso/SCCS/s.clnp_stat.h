h35793
s 00002/00002/00075
d D 8.1 93/06/10 23:18:44 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00075
d D 7.5 93/05/25 11:51:30 bostic 5 4
c trailing comment after #else or #endif
e
s 00009/00000/00068
d D 7.4 91/05/06 18:58:54 bostic 4 3
c new copyright; att/bsd/shared
e
s 00026/00038/00042
d D 7.3 89/09/22 00:15:39 sklower 3 2
c make changes for SNMP
e
s 00004/00002/00076
d D 7.2 89/04/22 11:53:34 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00078/00000/00000
d D 7.1 88/12/14 15:29:28 sklower 1 0
c date and time created 88/12/14 15:29:28 by sklower
e
u
U
t
T
I 4
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 4
I 1
/***********************************************************
		Copyright IBM Corporation 1987

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of IBM not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
 */
D 2
/* $Header: clnp_stat.h,v 4.3 88/09/10 18:31:38 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/clnp_stat.h,v $ */
E 2
I 2
/* $Header: /var/src/sys/netiso/RCS/clnp_stat.h,v 5.1 89/02/09 16:20:42 hagens Exp $ */
/* $Source: /var/src/sys/netiso/RCS/clnp_stat.h,v $ */
E 2


#ifndef __CLNP_STAT__
#define __CLNP_STAT__

struct clnp_stat {
D 3
	u_short cns_total;			/* total pkts received */
	u_short	cns_toosmall;		/* fixed part of header too small */
	u_short	cns_badhlen;		/* header length is not reasonable */
	u_short	cns_badcsum;		/* checksum on packet failed */
	u_short cns_badaddr;		/* address fields were not reasonable */
	u_short cns_noseg;			/* segment information forgotten */
	u_short cns_badid;			/* incorrect protocol id */
	u_short	cns_badvers;		/* incorrect version */
	u_short	cns_ttlexpired;		/* ttl has expired */
	u_short cns_forward;		/* forwarded packets */
	u_short cns_errcvd;			/* ER packets received */
	u_short cns_frag;			/* fragments generated */
	u_short cns_sent;			/* total packets sent */
	u_short	cns_cachemiss;		/* cache misses */
I 2
	u_short cns_congest_set;	/* congestion experienced bit set */
	u_short cns_congest_rcvd;	/* congestion experienced bit received */
E 2
	u_short	er_protoerr;		/*	GEN_NOREAS
									GEN_PROTOERR
									GEN_HDRSYNTAX
									GEN_INCOMPLETE
									GEN_DUPOPT */
	u_short	er_badcsum;			/*	GEN_BADCSUM */
	u_short	er_congest;			/*	GEN_CONGEST */
	u_short er_segneeded;		/*	GEN_SEGNEEDED */
	u_short	er_reassfail;		/*	REASS_INTERFERE */
	u_short	er_dstunreach;		/*	ADDR_DESTUNREACH
									ADDR_DESTUNKNOWN */
	u_short	er_srcrterr;		/*	SRCRT_UNSPECERR
									SRCRT_SYNTAX
									SRCRT_UNKNOWNADDR
									SRCRT_BADPATH */
	u_short er_ttlexpired;		/*	TTL_EXPTRANSIT
									TTL_EXPREASS */
	u_short	er_unsupported;		/*	DISC_UNSUPPOPT
									DISC_UNSUPPVERS
									DISC_UNSUPPSECURE
									DISC_UNSUPPSRCRT
									DISC_UNSUPPRECRT */
E 3
I 3
	int cns_total;			/* total pkts received */
	int	cns_toosmall;		/* fixed part of header too small */
	int	cns_badhlen;		/* header length is not reasonable */
	int	cns_badcsum;		/* checksum on packet failed */
	int cns_badaddr;		/* address fields were not reasonable */
	int	cns_badvers;		/* incorrect version */
	int cns_noseg;			/* segment information forgotten */
	int cns_noproto;		/* incorrect protocol id */
	int	cns_delivered;		/* packets consumed by protocol */
	int	cns_ttlexpired;		/* ttl has expired */
	int cns_forward;		/* forwarded packets */
	int cns_sent;			/* total packets sent */
	int cns_odropped;		/* o.k. packets discarded, e.g. ENOBUFS */
	int cns_cantforward;	/* non-forwarded packets */
	int cns_fragmented;		/* packets fragmented */
	int cns_fragments;		/* fragments received */
	int cns_fragdropped;	/* fragments discarded */
	int cns_fragtimeout;	/* fragments timed out */
	int cns_ofragments;		/* fragments generated */
	int cns_cantfrag;		/* fragmentation prohibited */
	int cns_reassembled;	/* packets reconstructed */
	int	cns_cachemiss;		/* cache misses */
	int cns_congest_set;	/* congestion experienced bit set */
	int cns_congest_rcvd;	/* congestion experienced bit received */
	int cns_er_inhist[CLNP_ERRORS + 1];
	int cns_er_outhist[CLNP_ERRORS + 1];
E 3
} clnp_stat ;

#ifdef INCSTAT
#undef INCSTAT
D 5
#endif INCSTAT
E 5
I 5
#endif /* INCSTAT */
E 5
#define INCSTAT(x) clnp_stat./**/x/**/++

D 5
#endif __CLNP_STAT__
E 5
I 5
#endif /* __CLNP_STAT__ */
E 5
E 1
