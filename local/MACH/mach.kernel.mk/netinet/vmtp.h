/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vmtp.h,v $
 * Revision 2.4  89/03/09  20:47:43  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:02:49  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * Revision 2.2  88/08/24  02:03:39  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  18:56:45  mwyoung]
 * 
 * 07-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Defined VMTP_HOSTID, to use network ordering for IP addresses
 *	everywhere (including in eids) and to use a special vmtp_hostid
 *	instead of the kernel-wide hostid, which may be wrong.
 *
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 02-Jun-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Defined VCTL_INVALID.
 *
 * 29-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources.
 *
 */
/*
 * $ Header: vmtp.h,v 2.2 88/08/24 02:03:39 mwyoung Exp $
 */

/*
 * 	vmtp.h	0.1	10/19/86
 *	Written by Joyo Wijaya and Erik Nordmark
 */

#ifndef	VMTPH
#define VMTPH

/*
 * VMTP packet header (generic)
 */
struct vmtphdr {
	struct vmtpeid	vh_client;	/* client/requestor entity id */
	u_long		vh_vdl;		/* Version, domain and length */
	u_long		vh_ipcf;	/* Gap, prioriy, control, function */
/* 
 * This field is divided into the following fields: (in order as of spec.)
 *	unsigned	vh_version:4;	version of the protocol 
 *	unsigned	vh_domain:12;	client naming domain 
 *	unsigned	vh_length:16;	packet length
 *	unsigned	vh_control:16;	control flags, see below 
 *	unsigned	vh_inpktgap:8;	interpacket gap 
 *	unsigned	vh_priority:4;	priority, see below 
 *	unsigned	vh_fnctcode:4;	function code, see below
 */
	u_long		vh_transid;	/* transaction id */
	u_long		vh_dlvrmsk;	/* delivery mask */
	struct vmtpeid	vh_server;	/* server entity */
	struct vmtpucb	vh_ucb;		/* user control block */
};

/*
 * Selectors for the fields of vh_vdl and vh_ipcf
 */
#define getvh_version(vh)	((((vh).vh_vdl)>>28) & 0xf)
#define getvh_domain(vh)	((((vh).vh_vdl)>>16) & 0xfff)
#define getvh_length(vh)	(((vh).vh_vdl) & 0xffff)
#define getvh_control(vh)	((((vh).vh_ipcf)>>16) & 0xffff)
#define getvh_inpktgap(vh)	((((vh).vh_ipcf)>>8) & 0xff)
#define getvh_priority(vh)	((((vh).vh_ipcf)>>4) & 0xf)
#define getvh_fnctcode(vh)	(((vh).vh_ipcf) & 0xf)
#define setvh_version(vh,val)	{ (vh).vh_vdl &= 0x0fffffff; \
				  (vh).vh_vdl |= ((val) & 0xf)<<28; }
#define setvh_domain(vh,val)	{ (vh).vh_vdl &= 0xf000ffff; \
				  (vh).vh_vdl |= ((val) & 0xfff)<<16; }
#define setvh_length(vh,val)	{ (vh).vh_vdl &= 0xffff0000; \
				  (vh).vh_vdl |= ((val) & 0xffff); }
#define setvh_control(vh,val)	{ (vh).vh_ipcf &= 0x0000ffff; \
				  (vh).vh_ipcf |= ((val) & 0xffff)<<16; }
#define setvh_inpktgap(vh,val)	{ (vh).vh_ipcf &= 0xffff00ff; \
				  (vh).vh_ipcf |= ((val) & 0xff)<<8; }
#define setvh_priority(vh,val)	{ (vh).vh_ipcf &= 0xffffff0f; \
				  (vh).vh_ipcf |= ((val) & 0xf)<<4; }
#define setvh_fnctcode(vh,val)	{ (vh).vh_ipcf &= 0xfffffff0; \
				  (vh).vh_ipcf |= ((val) & 0xf); }
#define orvh_control(vh,val)	\
			(vh).vh_ipcf |= (((val) & 0xffff)<<16)
#define andvh_control(vh,val)	\
			(vh).vh_ipcf &= (0x0000ffff | ((val)<<16))

/*
 * VMTP packet function codes (Note: if even, it is sent to server;
 * if odd, it is sent to client.
 */
#define VMTP_REQ		0x0	/* request */
#define VMTP_RESP		0x1	/* response */
#define VMTP_FWDREQ		0x2	/* forward request */
#define VMTP_FWDRESP		0x3	/* forward response */
#define VMTP_RESPACK		0x4	/* response acknowledgement */
#define VMTP_REQACK		0x5	/* request acknowledgement */
#define VMTP_PROBERESP		0x6	/* probe response */
#define VMTP_PROBEREQ		0x7	/* probe request */

/*
 * Controls:
 */
/* Controls 0x0040 - 0x0001 are reserved for future use */
#define VCTL_CPG	0x8000	/* continued packet group */
#define VCTL_APG	0x4000	/* acknowledge packet group immediately */
#define VCTL_NSR	0x2000	/* not start run (streaming) */
#define VCTL_NER	0x1000	/* not end run (streaming) */
#define VCTL_NRT	0x0800	/* no retransmission (streaming) */
#define VCTL_MDG	0x0400	/* client is member of destination group */
#define VCTL_CMG	0x0200	/* continued message */
#define VCTL_CMT	VCTL_CMG /* client map translation (forwarding) */
#define VCTL_STI	0x0100	/* skip transaction identifiers (streaming) */
#define VCTL_DRT	0x0080	/* delay response transmission (multicast)*/
/*
 * VCTL_INVALID is not to be transmitted over the net, it is used to flag
 * an invalid vihdr in a csr, to avoid retransmitting garbage. (DPJ)
 */
#define VCTL_INVALID	0x0040

#define vmtp_delayedresp(ctl) ((ctl) & VCTL_DRT)
#define vmtp_notlastpacket(ctl) ((ctl) & VCTL_CPG)
#define vmtp_acknowledgepg(ctl) ((ctl) & VCTL_APG)
#define vmtp_notfirstpg(ctl) ((ctl) & VCTL_NSR)
#define vmtp_notlastpg(ctl) ((ctl) & VCTL_NER)
#define vmtp_dstgrpmember(ctl) ((ctl) & VCTL_MDG)
#define vmtp_noretransmission(ctl) ((ctl) & VCTL_NRT)
#define vmtp_contmsgtrans(ctl) ((ctl) & VCTL_CMG)
#define vmtp_clientmapping(ctl) ((ctl) & VCTL_CMT)
#define vmtp_skiptid(ctl) ((ctl) & VCTL_STI)
#define vmtp_invalidresp(ctl) ((ctl) & VCTL_INVALID)

/*
 * Priorities:
 */
#define VPR_URGENT	0	/* urgent/emergency */
#define VPR_IMPORTANT	2	/* important */
#define VPR_NORMAL	4	/* normal */
#define VPR_BACKGROUND	6	/* background */

/*
 * Codes:
 */
#define VMTP_OK		0	/* everything is OK */
#define VMTP_RETRY	1	/* retransmit packet group asap */
#define VMTP_RETRYALL	2	/* retransmit all */
#define VMTP_BUSY	3	/* busy, retry later */
#define VMTP_NONEXIST	4	/* no such entity */
#define VMTP_MIGRATED	5	/* entity migrated */
#define VMTP_NOPERMISSN 6	/* server unauthorized to serve this client */
#define VMTP_NOTAWAIT	7	/* not awaiting conditional msg, discard */
#define VMTP_PROERROR	8	/* packet protocolly in error */
#define VMTP_FREQRFSD	9	/* forward request refused */
#define VMTP_BADTID	10	/* bad transaction identifier (old) */
#define VMTP_NOSTREAMING 11	/* streaming not supported */
#define VMTP_NORUNREC	12	/* no record for this packet group */
#define VMTP_REXMTTIMEO	13	/* retransmission timeout */
#define VMTP_USERTIMEO	14	/* user timeout */
#define VMTP_RESPDISC	15	/* response discarded */
#define VMTP_NOSECURITY 16	/* security not supported */
#define VMTP_BADREPLY	17	/* idempotent reply without UDM set */
#define VMTP_SECUREREQ	18	/* security required */
#define VMTP_NOMULTICAST 19	/* multicast not supported */
#define VMTP_MANYRETRIES 20	/* to many retries requested */
#define VMTP_NOPRINCIPAL 21	/* server principal not known */
#define VMTP_NOKEY	22	/* there is no key for the server principal */
#define VMTP_CACHEMISS	23	/* miss in server cache and hint failed */

#define VMTP_NUMCODES	24


#define vmtp_ok(code) (((code) & 0x00ffffff) == VMTP_OK)
#define vmtp_retry(code) (((code) & 0x00ffffff) == VMTP_RETRY)
#define vmtp_retryall(code) (((code) & 0x00ffffff) == VMTP_RETRYALL)
#define vmtp_busy(code) (((code) & 0x00ffffff) == VMTP_BUSY)
#define vmtp_nonexistent(code) (((code) & 0x00ffffff) == VMTP_NONEXIST)
#define vmtp_migrated(code) (((code) & 0x00ffffff) == VMTP_MIGRATED)
#define vmtp_nopermission(code) (((code) & 0x00ffffff) == VMTP_NOPERMISSN)
#define vmtp_notawaiting(code) (((code) & 0x00ffffff) == VMTP_NOTAWAIT)
#define vmtp_protocolerror(code) (((code) & 0x00ffffff) == VMTP_PROERROR)
#define vmtp_freqrefused(code) (((code) & 0x00ffffff) == VMTP_FREQRFSD)
#define vmtp_badtid(code) (((code) & 0x00ffffff) == VMTP_BADTID)
#define vmtp_nostreaming(code) (((code) & 0x00ffffff) == VMTP_STRNOTSUPP)
#define vmtp_norunrec(code) (((code) & 0x00ffffff) == VMTP_NORUNREC)
#define vmtp_rexmttimeo(code) (((code) & 0x00ffffff) == VMTP_REXMTTIMEO)
#define vmtp_usertimeo(code) (((code) & 0x00ffffff) == VMTP_USERTIMEO)
#define vmtp_respdiscarded(code) (((code) & 0x00ffffff) == VMTP_RESPDISC)
#define vmtp_nosecurity(code) (((code) & 0x00ffffff) == VMTP_NOSECURITY)
#define vmtp_badreply(code) (((code) & 0x00ffffff) == VMTP_BADREPLY)
#define vmtp_securereq(code) (((code) & 0x00ffffff) == VMTP_SECUREREQ)
#define vmtp_nomulticast(code) (((code) & 0x00ffffff) == VMTP_NOMULTICAST)
#define vmtp_manyretries(code) (((code) & 0x00ffffff) == VMTP_MANYRETRIES)
#define vmtp_noprincipal(code) (((code) & 0x00ffffff) == VMTP_NOPRINCIPAL)
#define vmtp_nokey(code) (((code) & 0x00ffffff) == VMTP_NOKEY)
#define vmtp_cachemiss(code) (((code) & 0x00ffffff) == VMTP_CACHEMISS)

/*
 * Generic network address.
 * Note: type field should be in same position
 */
union vmtp_addr {        
	struct {
	        u_char	type;		/* address type */
        	u_char	enet[6];
	} vau_ether;
	struct {
	        u_char	type;		/* address type */
        	u_long	inet;
	} vau_inet;
};
#define va_type		vau_ether.type 		/* == vau_inet.type */
#define va_ether	vau_ether.enet
#define va_inet		vau_inet.inet

/*
 * Address types
 */
#define VAT_INET	1
#define VAT_ETHER	2

/*
 * Other definitions
 */
#define VMTP_MAXBLKSEG	32		/* max number of data blks per msg */
#define VMTP_MAXSEGMASK 0x80000000	/* highest bit in a delivery mask */
#define VMTP_BLKSIZE	512		/* bytes per block */
#define VMTP_BLKSIZESHIFT 9		/* 2log of previous */
#define VMTP_MAXSEGSIZE	(VMTP_MAXBLKSEG*VMTP_BLKSIZE)

#define VMTP_MAXBLKPACKET 	2	/* Max # of blocks per packet */
#define VMTP_MAXMASK 		0x3	/* Max mask for one packet */

#define vmtp_domainserved(domain) ((domain) == 0x1)

#define VMTP_HOSTID	1
#if	VMTP_HOSTID
extern u_long vmtp_hostid;
#endif	VMTP_HOSTID

#if	0
#define VMTP_DEBUG	1
#define VMTPDEBUG	1
#define ESP_DEBUG	1
#define GROUP_DEBUG	1
#define FORWARD_DEBUG	1
#define LOCAL_DEBUG	1
#define CACHE_DEBUG	1
#define MANAGER_DEBUG	1
#define KEY_DEBUG	1
#endif	0

#define MANAGER_DEBUG		1
#define VMTP_RETRANS_DEBUG	1

#endif
