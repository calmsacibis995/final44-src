h11760
s 00001/00017/00436
d D 8.2 94/04/16 07:50:59 bostic 12 11
c clnp needs sys/types.h (for u_short, etc.), so BYTE_ORDER isn't
c needed.
c From: "Chris G. Demetriou" <cgd@sun-lamp.cs.berkeley.edu>
e
s 00002/00002/00451
d D 8.1 93/06/10 23:18:15 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00449
d D 7.10 93/05/25 11:51:24 bostic 10 9
c trailing comment after #else or #endif
e
s 00005/00004/00448
d D 7.9 92/02/14 14:16:27 sklower 9 8
c changes proposed by hagens to make CLNP EchoReply work
e
s 00008/00001/00444
d D 7.8 91/05/06 18:58:45 bostic 8 7
c new copyright; att/bsd/shared
e
s 00010/00010/00435
d D 7.7 91/04/26 15:07:54 sklower 7 6
c SN_MTU now considers route; cl cache include ifp pointer
e
s 00004/00002/00441
d D 7.6 90/04/05 11:15:39 sklower 6 5
c if_output now called with pointer to rtentry.
e
s 00018/00000/00425
d D 7.5 89/09/22 00:15:01 sklower 5 4
c make changes for SNMP
e
s 00031/00021/00394
d D 7.4 89/04/22 11:53:11 sklower 4 3
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00022/00006/00393
d D 7.3 89/02/14 18:20:47 sklower 3 2
c include wisconsin revisions
e
s 00002/00002/00397
d D 7.2 89/02/14 18:13:56 sklower 2 1
c minimal berkeley change for clusters
e
s 00399/00000/00000
d D 7.1 88/12/14 15:29:20 sklower 1 0
c date and time created 88/12/14 15:29:20 by sklower
e
u
U
t
T
I 8
/*-
D 11
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
D 12
 * Copyright (c) 1991, 1993
E 12
I 12
 * Copyright (c) 1991, 1993, 1994
E 12
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 8
I 5

E 5
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
D 3
/* $Header: clnp.h,v 4.3 88/09/12 13:34:40 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/clnp.h,v $ */
E 3
I 3
D 9
/* $Header: /var/src/sys/netiso/RCS/clnp.h,v 5.1 89/02/09 16:17:22 hagens Exp $ */
/* $Source: /var/src/sys/netiso/RCS/clnp.h,v $ */
E 9
I 9
/* $Header: /big/BSD4.4/isis-usr/src/sys/netiso/RCS/clnp.h,v 1.1 1992/02/07 18:14:59 hagens Exp hagens $ */
/* $Source: /big/BSD4.4/isis-usr/src/sys/netiso/RCS/clnp.h,v $ */
E 9
E 3
I 2
D 8
/*	%W% (Berkeley) %G% */
E 8
E 2
D 12

#ifndef BYTE_ORDER
/*
 * Definitions for byte order,
 * according to byte significance from low address to high.
 */
#define	LITTLE_ENDIAN	1234	/* least-significant byte first (vax) */
#define	BIG_ENDIAN	4321	/* most-significant byte first (IBM, net) */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long (pdp) */

#ifdef vax
#define	BYTE_ORDER	LITTLE_ENDIAN
#else
#define	BYTE_ORDER	BIG_ENDIAN	/* mc68000, tahoe, most others */
#endif
D 10
#endif BYTE_ORDER
E 10
I 10
#endif /* BYTE_ORDER */
E 12
E 10

I 3
/* should be config option but cpp breaks with too many #defines */
#define	DECBIT

E 3
/*
 *	Return true if the mbuf is a cluster mbuf
 */
D 2
#define	IS_CLUSTER(m)\
	((m)->m_off > MMAXOFF)
E 2
I 2
#define	IS_CLUSTER(m)	((m)->m_flags & M_EXT)
E 2

/*
 *	Move the halfword into the two characters
 */
#define	HTOC(msb, lsb, hword)\
	(msb) = (u_char)((hword) >> 8);\
	(lsb) = (u_char)((hword) & 0xff)
/*
 *	Move the two charcters into the halfword
 */
#define	CTOH(msb, lsb, hword)\
	(hword) = ((msb) << 8) | (lsb)

/*
 *	Return true if the checksum has been set - ie. the checksum is
 *	not zero
 */
#define	CKSUM_REQUIRED(clnp)\
	(((clnp)->cnf_cksum_msb != 0) || ((clnp)->cnf_cksum_lsb != 0))

/*
 *	Fixed part of clnp header
 */
struct clnp_fixed {
	u_char	cnf_proto_id;		/* network layer protocol identifier */
	u_char	cnf_hdr_len;		/* length indicator (octets) */
	u_char	cnf_vers;			/* version/protocol identifier extension */
	u_char	cnf_ttl;			/* lifetime (500 milliseconds) */
D 4
#if BYTE_ORDER == LITTLE_ENDIAN
	u_char	cnf_type:5,			/* type code */
			cnf_err_ok:1,		/* flag: error report */
			cnf_more_segs:1,	/* flag: more segments */
			cnf_seg_ok:1;		/* flag: segmentation permitted */
#endif
#if BYTE_ORDER == BIG_ENDIAN
	u_char	cnf_seg_ok:1,		/* flag: segmentation permitted */
			cnf_more_segs:1,	/* flag: more segments */
			cnf_err_ok:1,		/* flag: error report */
			cnf_type:5;			/* type code */
#endif
E 4
I 4
	u_char	cnf_type;			/* type code */
								/* Includes err_ok, more_segs, and seg_ok */
E 4
	u_char	cnf_seglen_msb;		/* pdu segment length (octets) high byte */
	u_char	cnf_seglen_lsb;		/* pdu segment length (octets) low byte */
	u_char	cnf_cksum_msb;		/* checksum high byte */
	u_char	cnf_cksum_lsb;		/* checksum low byte */
};
I 4
#define CNF_TYPE	0x1f
#define CNF_ERR_OK	0x20
#define CNF_MORE_SEGS	0x40
#define CNF_SEG_OK	0x80

E 4
#define CLNP_CKSUM_OFF	0x07	/* offset of checksum */

#define	clnl_fixed	clnp_fixed

/*
 *	Segmentation part of clnp header
 */
struct clnp_segment {
	u_short	cng_id;				/* data unit identifier */
	u_short	cng_off;			/* segment offset */
	u_short	cng_tot_len;		/* total length */
};

/*
 *	Clnp fragment reassembly structures:
 *
 *	All packets undergoing reassembly are linked together in 
 *	clnp_fragl structures. Each clnp_fragl structure contains a
 *	pointer to the original clnp packet header, as well as a 
 *	list of packet fragments. Each packet fragment
 *	is headed by a clnp_frag structure. This structure contains the
 *	offset of the first and last byte of the fragment, as well as
 *	a pointer to the data (an mbuf chain) of the fragment.
 */

/*
 *	NOTE:
 *		The clnp_frag structure is stored in an mbuf immedately preceeding
 *	the fragment data. Since there are words in this struct,
 *	it must be word aligned. 
 *
 *	NOTE:
 *		All the fragment code assumes that the entire clnp header is 
 *	contained in the first mbuf.
 */
struct clnp_frag {
	u_int				cfr_first;		/* offset of first byte of this frag */
	u_int				cfr_last;		/* offset of last byte of this frag */
	u_int				cfr_bytes;		/* bytes to shave to get to data */
	struct mbuf			*cfr_data;		/* ptr to data for this frag */
	struct clnp_frag	*cfr_next;		/* next fragment in list */
};

struct clnp_fragl {
	struct iso_addr		cfl_src;		/* source of the pkt */
	struct iso_addr		cfl_dst;		/* destination of the pkt */
	u_short				cfl_id;			/* id of the pkt */
	u_char				cfl_ttl;		/* current ttl of pkt */
	u_short				cfl_last;		/* offset of last byte of packet */
	struct mbuf 		*cfl_orighdr;	/* ptr to original header */
	struct clnp_frag	*cfl_frags;		/* linked list of fragments for pkt */
	struct clnp_fragl	*cfl_next;		/* next pkt being reassembled */
};

/*
 *	The following structure is used to index into an options section
 *	of a clnp datagram. These values can be used without worry that
 *	offset or length fields are invalid or too big, etc. That is,
 *	the consistancy of the options will be guaranteed before this
 *	structure is filled in. Any pointer (field ending in p) is
 *	actually the offset from the beginning of the mbuf the option
 *	is contained in.  A value of NULL for any pointer
 *	means that the option is not present. The length any option
 *	does not include the option code or option length fields.
 */
struct clnp_optidx {
	u_short	cni_securep;		/* ptr to beginning of security option */
	char	cni_secure_len;		/* length of entire security option */

	u_short	cni_srcrt_s;		/* offset of start of src rt option */
	u_short	cni_srcrt_len;		/* length of entire src rt option */

	u_short	cni_recrtp;			/* ptr to beginning of recrt option */
	char	cni_recrt_len;		/* length of entire recrt option */

	char	cni_priorp;			/* ptr to priority option */

	u_short	cni_qos_formatp;	/* ptr to format of qos option */
	char	cni_qos_len;		/* length of entire qos option */

	u_char	cni_er_reason;		/* reason from ER pdu option */
I 4

								/* ESIS options */

	u_short	cni_esct;			/* value from ISH ESCT option */

	u_short	cni_netmaskp;		/* ptr to beginning of netmask option */
	char	cni_netmask_len;		/* length of entire netmask option */

	u_short	cni_snpamaskp;		/* ptr to beginning of snpamask option */
	char	cni_snpamask_len;		/* length of entire snpamask option */

E 4
};

#define	ER_INVALREAS	0xff	/* code for invalid ER pdu discard reason */

I 3
/* given an mbuf and addr of option, return offset from data of mbuf */
#define CLNP_OPTTOOFF(m, opt)\
D 4
	((u_short) (opts - mtod(m, caddr_t)))
E 4
I 4
	((u_short) (opt - mtod(m, caddr_t)))
E 4

/* given an mbuf and offset of option, return address of option */
#define CLNP_OFFTOOPT(m, off)\
	((caddr_t) (mtod(m, caddr_t) + off))

E 3
/*	return true iff src route is valid */
#define	CLNPSRCRT_VALID(oidx)\
	((oidx) && (oidx->cni_srcrt_s))

/*	return the offset field of the src rt */
#define CLNPSRCRT_OFF(oidx, options)\
D 3
	(*((u_char *)((caddr_t)options + oidx->cni_srcrt_s + 1)))
E 3
I 3
	(*((u_char *)(CLNP_OFFTOOPT(options, oidx->cni_srcrt_s) + 1)))
E 3

/*	return the type field of the src rt */
#define CLNPSRCRT_TYPE(oidx, options)\
D 3
	((u_char)(*((caddr_t)options + oidx->cni_srcrt_s)))
E 3
I 3
	((u_char)(*(CLNP_OFFTOOPT(options, oidx->cni_srcrt_s))))
E 3

/* return the length of the current address */
#define CLNPSRCRT_CLEN(oidx, options)\
D 3
	((u_char)(*((caddr_t)options + oidx->cni_srcrt_s + CLNPSRCRT_OFF(oidx, options) - 1)))
E 3
I 3
	((u_char)(*(CLNP_OFFTOOPT(options, oidx->cni_srcrt_s) + CLNPSRCRT_OFF(oidx, options) - 1)))
E 3

/* return the address of the current address */
#define CLNPSRCRT_CADDR(oidx, options)\
D 3
	((caddr_t)((caddr_t)options + oidx->cni_srcrt_s + CLNPSRCRT_OFF(oidx, options)))
E 3
I 3
	((caddr_t)(CLNP_OFFTOOPT(options, oidx->cni_srcrt_s) + CLNPSRCRT_OFF(oidx, options)))
E 3

/* 
 *	return true if the src route has run out of routes
 *	this is true if the offset of next route is greater than the end of the rt 
 */
#define	CLNPSRCRT_TERM(oidx, options)\
	(CLNPSRCRT_OFF(oidx, options) > oidx->cni_srcrt_len)

/*
 *	Options a user can set/get
 */
#define	CLNPOPT_FLAGS	0x01	/* flags: seg permitted, no er xmit, etc  */
#define	CLNPOPT_OPTS	0x02	/* datagram options */

/*
 *	Values for particular datagram options
 */
#define	CLNPOVAL_PAD		0xcc	/* padding */
#define	CLNPOVAL_SECURE		0xc5	/* security */
#define	CLNPOVAL_SRCRT		0xc8	/* source routing */
#define	CLNPOVAL_RECRT		0xcb	/* record route */
#define	CLNPOVAL_QOS		0xc3	/* quality of service */
#define	CLNPOVAL_PRIOR		0xcd	/* priority */
#define CLNPOVAL_ERREAS		0xc1	/* ER PDU ONLY: reason for discard */

#define	CLNPOVAL_SRCSPEC	0x40	/* source address specific */
#define	CLNPOVAL_DSTSPEC	0x80	/* destination address specific */
#define	CLNPOVAL_GLOBAL		0xc0	/* globally unique */
I 3

/* Globally Unique QOS */
#define	CLNPOVAL_SEQUENCING	0x10	/* sequencing preferred */
#define CLNPOVAL_CONGESTED	0x08	/* congestion experienced */
#define CLNPOVAL_LOWDELAY	0x04	/* low transit delay */
E 3

#define	CLNPOVAL_PARTRT		0x00	/* partial source routing */
#define CLNPOVAL_COMPRT		0x01	/* complete source routing */

/*
 *	Clnp flags used in a control block flags field. 
 *	NOTE: these must be out of the range of bits defined in ../net/raw_cb.h
 */
#define	CLNP_NO_SEG		0x010	/* segmentation not permitted */
#define	CLNP_NO_ER		0x020	/* do not generate ERs */
#define CLNP_SEND_RAW	0x080	/* send pkt as RAW DT rather than TP DT */
#define	CLNP_NO_CKSUM	0x100	/* don't use clnp checksum */
D 9
#define CLNP_ECHO		0x200	/* fake echo function */
E 9
I 9
#define CLNP_ECHO		0x200	/* send echo request */
E 9
#define	CLNP_NOCACHE	0x400	/* don't store cache information */
I 9
#define CLNP_ECHOR		0x800	/* send echo reply */
E 9

/* valid clnp flags */
#define CLNP_VFLAGS		(CLNP_SEND_RAW|CLNP_NO_SEG|CLNP_NO_ER|CLNP_NO_CKSUM\
D 9
	|CLNP_ECHO|CLNP_NOCACHE)
E 9
I 9
	|CLNP_ECHO|CLNP_NOCACHE|CLNP_ECHOR)
E 9

/* 
 *	Constants used by clnp
 */
#define	CLNP_HDR_MIN	(sizeof (struct clnp_fixed))
#define	CLNP_HDR_MAX	(254)
#define	CLNP_TTL_UNITS	2					/* 500 milliseconds */
#define CLNP_TTL		15*CLNP_TTL_UNITS	/* time to live (seconds) */
#define	ISO8473_V1		0x01

/*
 *	Clnp packet types
 *	In order to test raw clnp and tp/clnp simultaneously, a third type of
 *	packet has been defined: CLNP_RAW. This is done so that the input
 *	routine can switch to the correct input routine (rclnp_input or
 *	tpclnp_input) based on the type field. If clnp had a higher level protocol
 *	field, this would not be necessary.
 */
#define	CLNP_DT			0x1C	/* normal data */
#define	CLNP_ER			0x01	/* error report */
#define	CLNP_RAW		0x1D	/* debug only */
#define CLNP_EC			0x1E	/* echo packet */
#define CLNP_ECR		0x1F	/* echo reply */

/*
 *	ER pdu error codes
 */
#define GEN_NOREAS			0x00	/* reason not specified */
#define GEN_PROTOERR		0x01	/* protocol procedure error */
#define GEN_BADCSUM			0x02	/* incorrect checksum */
#define GEN_CONGEST			0x03	/* pdu discarded due to congestion */
#define GEN_HDRSYNTAX		0x04	/* header syntax error */
#define GEN_SEGNEEDED		0x05	/* segmentation needed, but not permitted */
#define GEN_INCOMPLETE		0x06	/* incomplete pdu received */
#define GEN_DUPOPT			0x07	/* duplicate option */

/* address errors */
#define ADDR_DESTUNREACH	0x80	/* destination address unreachable */
#define ADDR_DESTUNKNOWN	0x81	/* destination address unknown */

/* source routing */
#define SRCRT_UNSPECERR		0x90	/* unspecified src rt error */
#define SRCRT_SYNTAX		0x91	/* syntax error in src rt field */
#define SRCRT_UNKNOWNADDR	0x92	/* unknown addr in src rt field */
#define SRCRT_BADPATH		0x93	/* path not acceptable */

/* lifetime */
#define TTL_EXPTRANSIT		0xa0	/* lifetime expired during transit */
#define TTL_EXPREASS		0xa1	/* lifetime expired during reassembly */

/* pdu discarded */
#define DISC_UNSUPPOPT		0xb0	/* unsupported option not specified? */
#define DISC_UNSUPPVERS		0xb1	/* unsupported protocol version */
#define DISC_UNSUPPSECURE	0xb2	/* unsupported security option */
#define DISC_UNSUPPSRCRT	0xb3	/* unsupported src rt option */
#define DISC_UNSUPPRECRT	0xb4	/* unsupported rec rt option */

/* reassembly */
#define REASS_INTERFERE		0xc0	/* reassembly interference */
I 5
#define CLNP_ERRORS		22


#ifdef KERNEL
int clnp_er_index();
#endif

#ifdef CLNP_ER_CODES
u_char clnp_er_codes[CLNP_ERRORS] =  {
GEN_NOREAS, GEN_PROTOERR, GEN_BADCSUM, GEN_CONGEST,
GEN_HDRSYNTAX, GEN_SEGNEEDED, GEN_INCOMPLETE, GEN_DUPOPT,
ADDR_DESTUNREACH, ADDR_DESTUNKNOWN,
SRCRT_UNSPECERR, SRCRT_SYNTAX, SRCRT_UNKNOWNADDR, SRCRT_BADPATH,
TTL_EXPTRANSIT, TTL_EXPREASS,
DISC_UNSUPPOPT, DISC_UNSUPPVERS, DISC_UNSUPPSECURE,
DISC_UNSUPPSRCRT, DISC_UNSUPPRECRT, REASS_INTERFERE };
#endif
E 5

#ifdef	TROLL

#define	TR_DUPEND		0x01	/* duplicate end of fragment */
#define TR_DUPPKT		0x02	/* duplicate entire packet */
#define	TR_DROPPKT		0x04	/* drop packet on output */
#define TR_TRIM			0x08	/* trim bytes from packet */
#define TR_CHANGE		0x10	/* change bytes in packet */
#define TR_MTU			0x20	/* delta to change device mtu */
#define	TR_CHUCK		0x40	/* drop packet in rclnp_input */
#define	TR_BLAST		0x80	/* force rclnp_output to blast many packet */
#define	TR_RAWLOOP		0x100	/* make if_loop call clnpintr directly */
struct troll {
	int		tr_ops;				/* operations to perform */
	float	tr_dup_size;		/* % to duplicate */
	float	tr_dup_freq;		/* frequency to duplicate packets */
	float	tr_drop_freq;		/* frequence to drop packets */
	int		tr_mtu_adj;			/* delta to adjust if mtu */
	int		tr_blast_cnt;		/* # of pkts to blast out */
};

#define	SN_OUTPUT(clcp, m)\
D 4
	troll_output(clcp->clc_ifp, m, clcp->clc_firsthop)
E 4
I 4
D 6
	troll_output(clcp->clc_ifa->ia_ifp, m, clcp->clc_firsthop)
E 6
I 6
D 7
	troll_output(clcp->clc_ifa->ia_ifp, m, clcp->clc_firsthop, clcp->clc_rt)
E 7
I 7
	troll_output(clcp->clc_ifp, m, clcp->clc_firsthop, clcp->clc_rt)
E 7
E 6
E 4

D 7
#define	SN_MTU(ifp)\
	(ifp->if_mtu - trollctl.tr_mtu_adj)
E 7
I 7
#define	SN_MTU(ifp, rt) (((rt && rt->rt_rmx.rmx_mtu) ?\
	rt->rt_rmx.rmx_mtu : clnp_badmtu(ifp, rt, __LINE__, __FILE__))\
		- trollctl.tr_mtu_adj)
E 7

I 4
#ifdef KERNEL
extern float troll_random;
#endif

E 4
#else	/* NO TROLL */

#define	SN_OUTPUT(clcp, m)\
D 4
	(*clcp->clc_ifp->if_output)(clcp->clc_ifp, m, clcp->clc_firsthop)
E 4
I 4
D 6
	(*clcp->clc_ifa->ia_ifp->if_output)(clcp->clc_ifa->ia_ifp, m, clcp->clc_firsthop)
E 6
I 6
D 7
	(*clcp->clc_ifa->ia_ifp->if_output)(clcp->clc_ifa->ia_ifp, m, clcp->clc_firsthop, clcp->clc_rt)
E 7
I 7
	(*clcp->clc_ifp->if_output)(clcp->clc_ifp, m, clcp->clc_firsthop, clcp->clc_rt)
E 7
E 6
E 4

D 7
#define	SN_MTU(ifp)\
	(ifp->if_mtu)
E 7
I 7
#define	SN_MTU(ifp, rt) (((rt && rt->rt_rmx.rmx_mtu) ?\
	rt->rt_rmx.rmx_mtu : clnp_badmtu(ifp, rt, __LINE__, __FILE__)))
E 7

D 10
#endif	TROLL
E 10
I 10
#endif	/* TROLL */
E 10

/*
 *	Macro to remove an address from a clnp header
 */
#define CLNP_EXTRACT_ADDR(isoa, hoff, hend)\
	{\
		isoa.isoa_len = (u_char)*hoff;\
		if ((((++hoff) + isoa.isoa_len) > hend) ||\
			(isoa.isoa_len > 20) || (isoa.isoa_len == 0)) {\
			hoff = (caddr_t)0;\
		} else {\
D 4
			(void) bcopy(hoff, (caddr_t)&isoa, isoa.isoa_len);\
E 4
I 4
			(void) bcopy(hoff, (caddr_t)isoa.isoa_genaddr, isoa.isoa_len);\
E 4
			hoff += isoa.isoa_len;\
		}\
	}

/*
 *	Macro to insert an address into a clnp header
 */
D 4
#define CLNP_INSERT_ADDR(hoff, isoap)\
	*hoff++ = (isoap)->isoa_len;\
	(void) bcopy((caddr_t)(isoap), hoff, (isoap)->isoa_len);\
	hoff += (isoap)->isoa_len;
E 4
I 4
#define CLNP_INSERT_ADDR(hoff, isoa)\
	*hoff++ = (isoa).isoa_len;\
	(void) bcopy((caddr_t)((isoa).isoa_genaddr), hoff, (isoa).isoa_len);\
	hoff += (isoa).isoa_len;
E 4

/*
 *	Clnp hdr cache.	Whenever a clnp packet is sent, a copy of the
 *	header is made and kept in this cache. In addition to a copy of
 *	the cached clnp hdr, the cache contains
 *	information necessary to determine whether the new packet
 *	to send requires a new header to be built.
 */
struct clnp_cache {
	/* these fields are used to check the validity of the cache */
	struct iso_addr		clc_dst;		/* destination of packet */
	struct mbuf 		*clc_options;	/* ptr to options mbuf */
	int					clc_flags;		/* flags passed to clnp_output */

	/* these fields are state that clnp_output requires to finish the pkt */
	int					clc_segoff;		/* offset of seg part of header */
D 7
	struct sockaddr		*clc_firsthop;	/* first hop of packet (points into
											the route structure) */
D 4
	struct ifnet		*clc_ifp;		/* ptr to interface (points into
E 4
I 4
	struct iso_ifaddr	*clc_ifa;		/* ptr to interface (points into
I 6
											the route structure) */
E 7
	struct rtentry		*clc_rt;		/* ptr to rtentry (points into
E 6
E 4
											the route structure) */
I 7
	struct sockaddr		*clc_firsthop;	/* first hop of packet */
	struct ifnet		*clc_ifp;		/* ptr to interface structure */
	struct iso_ifaddr	*clc_ifa;		/* ptr to interface address */
E 7
	struct mbuf 		*clc_hdr;		/* cached pkt hdr (finally)! */
};

#ifndef	satosiso
#define	satosiso(sa)\
	((struct sockaddr_iso *)(sa))
#endif

#ifdef	KERNEL
caddr_t			clnp_insert_addr();
struct iso_addr	*clnp_srcaddr();
struct mbuf		*clnp_reass();
#ifdef	TROLL
struct troll	trollctl;
D 10
#endif	TROLL
#endif	KERNEL
E 10
I 10
#endif	/* TROLL */
#endif	/* KERNEL */
E 10
E 1
