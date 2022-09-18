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
 * $Log:	vmtp_var.h,v $
 * Revision 2.3  89/03/09  20:51:39  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:06:44  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 16-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	MACH_NP: Added a field in vmtpcsr to hold some user data.
 *
 * 07-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_HOSTID: converted to use vmtp_hostid and not byte-swap
 *	IP addresses in eids.
 *
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 05-Jun-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_LOGSTAT: put all the timeout parameters in a static
 *	variable so that they can be modified at run-time.
 *
 * 31-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_INVOKE: added support for split invoke call: need to find
 *	socket associated to csr.
 *
 * 29-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources.
 *
 */
/*
 * $ Header: vmtp_var.h,v 2.1 87/08/14 15:45:21 mrt Exp $
 */

#define VMTP_INVOKE	1
#define VMTP_LOGSTAT	1
#ifndef	VMTP_HOSTID
Make sure that you get VMTP_HOSTID from somewhere!
#endif	VMTP_HOSTID

/*
 * 	vmtp_var.h	0.1	10/19/86
 *	Written by Joyo Wijaya and Erik Nordmark
 */

#ifndef	VMTP_VARH
#define VMTP_VARH

#include <mach_np.h>

#if	VMTP_INVOKE
#include <sys/socket.h>
#endif	VMTP_INVOKE

/* 
 * A general synchronized queue - used for the timeout queue, request queues 
 * for servers, and response queues on client state records (multicasting)
 * The queue is a circular, doubly linked list with pointers from all entries
 * to the head of the queue. Each entry has a vmtpsynqovl in it and the head
 * of the queue is a struct vmtpsynq. If a pointer to an element is not the
 * same as a pointer to the vq_queue field of the head, then the element is
 * a car i.e. it the pointer to the synqovl can be cast to a csr pointer.
 *
 * Exclusive access to a queue is done by locking out interrupts i.e. 
 * at splimp()
 */
struct vmtpsynqovl {
	struct vmtpsynqovl *vq_next, *vq_prev; 
	struct vmtpsynq    *vq_head;
};

struct vmtpsynq {
	struct vmtpsynqovl vq_queue;		/* must be first in struct */
#define vq_chead	vq_queue.vq_next
#define vq_ctail	vq_queue.vq_prev
#define vq_qhead	vq_queue.vq_head  /* always NULL */
	u_short 	vq_type;
};

/* 
 * Types of synch queues
 */
#define VQ_TIMEOUT 	1
#define VQ_SERVER	2
#define VQ_RESPONSE	3



/*
 * VMTP client state record.
 * Some routines depend on the order of fields in the csr:
 *	esp_copyinfo copies from vc_mtu to vc_key
 *	vmtp_delivertogroup copies from vc_state to vc_effprincipalid
 */
struct vmtpcsr {
	struct vmtpsynqovl vc_queue;	/* must be first in struct */
#define vc_qnext	vc_queue.vq_next	/* link to next in queue */
#define vc_qprev	vc_queue.vq_prev	/* link to previous in queue */
#define vc_qhead	vc_queue.vq_head	/* link to the queue head */
	struct vmtpiphdr *vc_vihdr;	/* vmtp-ip header template */
#define vc_client	vc_vihdr->vi_client
#define vc_server	vc_vihdr->vi_server
#define vc_transid	vc_vihdr->vi_transid
#define vc_dlvrmsk	vc_vihdr->vi_dlvrmsk
#define vc_ucb		vc_vihdr->vi_ucb
#define vc_code		vc_vihdr->vi_ucb.vu_code
#define vc_data		vc_vihdr->vi_ucb.vu_data
#define vc_usrdlvrmsk	vc_vihdr->vi_ucb.vu_dlvrmsk
#define vc_segsize	vc_vihdr->vi_ucb.vu_segsize
#define vc_coresident	vc_vihdr->vi_ucb.vu_coresident
	struct vmtpcsr	*vc_next;	/* next csr in the overflow list */
	struct vmtpsynq *vc_responses;	/* for multiple responses */

	u_char		vc_state;	/* state of this client */
	u_char		vc_rexmtcnt;	/* number of retransmissions */
	u_char		vc_retrycnt;	/* number of retries */
	struct route	vc_iproute;	/* place for IP routing entry */
	u_char		vc_ipttl;	/* time-to-live to use for ip packets */
	u_long		vc_txmsk;	/* transmission mask */
	u_char		vc_flags; /* selector for vc_segment and vc_entities */
	union {
	    struct mbuf	*dataseg;	/* data segment chain */
	    caddr_t	segptr;		/* data segment address in user space */
	} vc_segment;
#define vc_dataseg	vc_segment.dataseg
#define vc_segptr	vc_segment.segptr
	u_short		vc_tleft;	/* time left before timeout */
	int		(*vc_hdltimeo)(); /* called when timed out */
	u_char		vc_action;	/* to signal to awoken process */

	/* communication state - refers to other entity. At server: */
	u_short		vc_mtu;		/* client's mtu in blocks */
	unsigned	vc_inpktgap:6;	/* clients interpacket gap */
	union vmtp_addr	vc_hostaddr;	/* clients host address */
	struct ifnet	*vc_ifp;
	int		vc_roundtrip;	/* roundtrip time in ms */
	int		vc_verifyint; 	/* for entity state timeouts - */
					/* - orphan detection */
/* end of response buffer */

	/* to remember state when probing and passing the result out */
	u_long		vc_tmstamp;	/* timestamp on last probe request */
	u_long		vc_probecode;	/* code in last probe response */

	/* used for multicast and forwarding */
	struct vmtpeid	vc_origserver;	/* original server - always set */
	union vmtp_addr	vc_clienthost; 	/* host addr of client */
	struct ifnet	*vc_clientifp;

	/* authetication state */
	u_long		vc_timelimit;	/* ttl for auth information or key */
	struct procid	vc_processid;
	struct princid	vc_principalid,
			vc_effprincipalid;
	struct mbuf 	*vc_principal,
			*vc_password,
			*vc_authenticator;
	u_long		vc_encryptqual;	/* encryption qualifier */
	union vmtpkey	vc_key;
#if	VMTP_INVOKE
	struct socket	*vc_so;		/* socket this csr depends on */
#endif	VMTP_INVOKE
#if	MACH_NP
	/*
	 * User info kept during mach_vmtp_invoke().
	 */
	long		vc_netport;
#endif	MACH_NP
};
#define VMTP_RBSIZE 	100	/* The size of the first part of the csr */
				/* up to and including the verifyint field. */
#define vmtp_rbsize(csr) \
	((caddr_t)(&csr->vc_verifyint) + sizeof(int) - (caddr_t)csr)


/*
 * States:
 */
#define VC_IDLE		0	/* idle state (at client) */
#define VC_PROCESSING	VC_IDLE /* processing state (at server) */
#define VC_AWAITRESP	1	/* awaiting response */
#define VC_RECVRESP	2	/* receiving response */
#define VC_AWAITREQ	3	/* awaiting request */
#define VC_AWAITPROBE	4	/* awaiting probe response */
#define VC_RECVREQ	5	/* receiving request */
#define VC_RESPONDED	6	/* response has been sent */
#define VC_GETREPLY	7	/* waiting for additional replies */

/*
 * Flags: (for vc_flags)
 *
 * VCF_MBUF is denoting what vc_segment really points to. Note: for the first 
 * transmission it is always an address in user space, and then vc_segmentflag 
 * indicates whether to get a copy of the segment into mbufs or keep it
 * in user space.
 * VCF_GROUP indicates if the current transaction was multicast.
 * VCF_FORWARDING at client: committed to forwarding; frp's are being received
 * VCF_FORWARDING at forwarder: request was forwarded. vc_hostaddr is the 
 *	address of the new server and vc_clienthost the address of the client!
 * VCF_RECVFORWARD at the new server: request was received as frq packets.
 *	vc_clienthost contains the client address until recvreq() is called.
 * VCF_REDO indicates that the request being processed is a retransmission
 *	(only if idempotent). This causes forward() to set the APG bit in
 *	forward packets to avoid timing out on the new server.
 * VCF_NILFWDRQ (Non-idempotent local forward request) indicates that the
 *	forward operation wasn't idempotent so the reply can't be idempotent 
 *	either (since there is only one remote csr which is either idempotent or
 *	has a copy of the reply attached to it.) So the DGM bit is reset when
 *	a reply is sent.
 */
#define VCF_NONE	0	
#define VCF_MBUF	0x1	
#define VCF_GROUP	0x2	
#define VCF_FORWARDING	0x4	
#define VCF_RECVFORWARD	0x8	
#define VCF_REDO	0x10
#define VCF_NILFWDRQ	0x20	

#define vcf_mbuf(csr)		((csr)->vc_flags & VCF_MBUF)
#define vcf_group(csr)		((csr)->vc_flags & VCF_GROUP)
#define vcf_forwarding(csr)	((csr)->vc_flags & VCF_FORWARDING)
#define vcf_recvforward(csr)	((csr)->vc_flags & VCF_RECVFORWARD)
#define vcf_redo(csr)		((csr)->vc_flags & VCF_REDO)
#define vcf_nilfwdrq(csr)	((csr)->vc_flags & VCF_NILFWDRQ)


/*
 * Signals to the awoken process sleeping waiting for a response
 * Kept in vc_action.
 */
#define VCA_NOOP	0	/* no operation - keep on sleeping */
#define VCA_DELIVER	1	/* deliver the response/error code in the csr */
				/* to the client process */
#define VCA_RETRANS	2	/* retransmit the request according to the */
				/* transmit mask (vc_txmsk) (vc_tleft is the */
				/* time to use when starting the timer) */


#define vmtp_sotocsr(so) ((struct vmtpcsr *)(so)->so_pcb)


/*
 * VMTP server entity record.
 * The queue of csr's contains all received requests that the server haven't
 * responded to yet. vs_cnext points to the next one to receive.
 */
struct vmtpser {
	struct vmtpsynq vs_queue;	/* queue of csr's with requests */
					/* must be first in struct */
#define vs_chead 	vs_queue.vq_chead
#define vs_ctail 	vs_queue.vq_ctail
#define vs_qhead	vs_queue.vq_qhead	/* must be NULL */
#define vs_type		vs_queue.vq_type	/* should be VQ_SERVER */
	struct vmtpsynqovl *vs_cnext;	/* next csr to receive */
	struct vmtpeid	vs_server;	/* server entity id */
	struct vmtpser	*vs_next;	/* overflow link in server map */
	u_short		vs_flags;	/* see below */
	struct vmtpeid	vs_orphan;	/* parent of orphaned request */
	union vmtpkey	vs_mkey;	/* master key for this server - */
				 /* corresponding roughly to a principal */
	u_long		vs_mencryptqual; /* encryption qualifier */
};

/* 
 * Server desriptor flags (in addition to those in vmtp_so.h)
 */
#define VS_REQQUEUED	0x0100	/* queue contains requests */
#define VS_WAITING	0x0200	/* the server is waiting for requests */
#define VS_ORPHAN	0x0400 /* a request being processed has been orphaned */

#define vmtp_mesgport(ser) 	((ser)->vs_flags & VS_MESGPORT)
#define vmtp_securityreq(ser) 	((ser)->vs_flags & VS_SECUREREQ)
#define vmtp_authreq(ser) 	((ser)->vs_flags & VS_AUTHREQ)
#define vmtp_masterkey(ser)	((ser)->vs_flags & VS_MASTERKEY)
#define vmtp_requestqueued(ser) ((ser)->vs_flags & VS_REQQUEUED)
#define vmtp_waiting(ser) 	((ser)->vs_flags & VS_WAITING)
#define vmtp_orphan(ser) 	((ser)->vs_flags & VS_ORPHAN)



#define vmtp_emptyeid(eid) ((eid).ve_inaddr == 0 \
			&& (eid).ve_fltm == 0) 
#define vmtp_sameeid(e1, e2) ((e1).ve_inaddr == (e2).ve_inaddr \
			      && (e1).ve_fltm == (e2).ve_fltm)
#if	VMTP_HOSTID
#define vmtp_eidtoinaddr(eid) ((eid).ve_inaddr)
#else	VMTP_HOSTID
#define vmtp_eidtoinaddr(eid) (ntohl((eid).ve_inaddr))
#endif	VMTP_HOSTID


/*
 * Hashing function for the maps (same for all the maps)
 * Note: e is a pointer to an eid struct
 */
#define VMTP_HASHMAPSIZE 	32

#if	(VMTP_HASHMAPSIZE & (VMTP_HASHMAPSIZE-1) == 0)
#define VMTP_HASHMAPOP	& (VMTP_HASHMAPSIZE-1)
#else
#define VMTP_HASHMAPOP	% VMTP_HASHMAPSIZE
#endif

#define vmtp_hash(e) 	\
	((((u_short *)(e))[0]^((u_short *)(e))[1]^((u_short *)(e))[2]^ \
	 ((u_short *)(e))[3]) VMTP_HASHMAPOP)


/*
 * VMTP Timeout Counts (counted down) and IP Time To Live.
 * Granularity is 20 msecs.
 */
#define VMTP_TIMEOFREQ	50	/* number of calls to vmtp_timeout per second */


/* 
 * Timeout values.
 * The +1 below steems from the fact that a timeout of k (20 ms) time units
 * will cause a wakeup in the interval from (k-1)*20 to k*20 milliseconds.
 */
#define vtc_awaitresp(csr) 	VTC_AWAITRESP
#define vtc_roundtrip(csr) 	((csr)->vc_roundtrip/20 + 1) 
						/* in 20 ms units */
#define vtc_receivepg(csr) 	((csr)->vc_mtu*VT_RECVPGFACTOR + 1)
#define vts_receivepg(csr) 	((csr)->vc_mtu*VT_RECVPGFACTOR + 1)
#define vts_orphan(csr)		VTS_ORPHAN
#define vts_roundtrip(csr)	((csr)->vc_roundtrip/20 + 1)
#define vts_discardcsr(csr)	VTS_DISCARDCSR
#define vts_retransmit(csr)	vts_roundtrip(csr)

#if	VMTP_LOGSTAT

struct vmtpparam {
	int ls_vt_recvpgfactor;
    	int ls_vtc_awaitresp;	/* TC1 - awaiting response */
	int ls_vtc_roundtrip;	/* TC2 - re-xmit request (roundtrip delay) */
	int ls_vtc_receivepg;	/* TC3 - concluding that no more packets */
	int ls_vts_receivepg;	/* TS1 - concluding that no more packets */
	int ls_vts_orphan;	/* TS2 - terminate processing of a request */
	int ls_vts_roundtrip;	/* TS3 - roundtrip delay */
	int ls_vts_discardcsr;	/* TS4 - discarding a remote csr */
	int ls_vts_retransmit;	/* TS5 - retransmitting response */
	int ls_vmtp_maxrexmtcnt;/* max number of retransmissions */
};

#define VT_RECVPGFACTOR		vmtpparam.ls_vt_recvpgfactor
#define VTC_AWAITRESP		vmtpparam.ls_vtc_awaitresp
#define VTC_ROUNDTRIP		vmtpparam.ls_vtc_roundtrip
#define VTC_RECEIVEPG		vmtpparam.ls_vtc_receivepg

#define VTS_RECEIVEPG		vmtpparam.ls_vts_receivepg
#define VTS_ORPHAN		vmtpparam.ls_vts_orphan
#define VTS_ROUNDTRIP 		vmtpparam.ls_vts_roundtrip
#define VTS_DISCARDCSR		vmtpparam.ls_vts_discardcsr
#define VTS_RETRANSMIT		vmtpparam.ls_vts_retransmit

#define VMTP_MAXREXMTCNT	vmtpparam.ls_vmtp_maxrexmtcnt

#else	VMTP_LOGSTAT
/*
 * Default/initial timeout values
 */
#ifdef	VMTP_DEBUG

#define VT_RECVPGFACTOR	25	/* 3 times transmision time of 512+84 bytes */
				/* on network (in 20 ms units) */
#define VTC_AWAITRESP	3000	/* TC1 - awaiting response */
#define VTC_ROUNDTRIP	3000	/* TC2 - retransmit request (roudtrip delay) */
#define VTC_RECEIVEPG	500	/* TC3 - concluding that no more packets */

#define VTS_RECEIVEPG	500	/* TS1 - concluding that no more packets */
#define VTS_ORPHAN	9000	/* TS2 - terminate processing of a request */
#define VTS_ROUNDTRIP 	3000	/* TS3 - roundtrip delay */
#define VTS_DISCARDCSR	6000	/* TS4 - discarding a remote csr */
#define VTS_RETRANSMIT	3000	/* TS5 - retransmitting response */

#else	VMTP_DEBUG

#define VT_RECVPGFACTOR   5	/* 3 times transmision time of 512+84 bytes */
				/* on network (in 20 ms units) */
#define VTC_AWAITRESP	40	/* TC1 - awaiting response */
#define VTC_ROUNDTRIP	10	/* TC2 - retransmit request (roudtrip delay) */
#define VTC_RECEIVEPG	5	/* TC3 - concluding that no more packets */

#define VTS_RECEIVEPG	5	/* TS1 - concluding that no more packets */
#define VTS_ORPHAN	1000	/* TS2 - terminate processing of a request */
#define VTS_ROUNDTRIP 	10	/* TS3 - roundtrip delay */
#define VTS_DISCARDCSR	6000	/* TS4 - discarding a remote csr */
#define VTS_RETRANSMIT	10	/* TS5 - retransmitting response */

#endif	VMTP_DEBUG

#define VMTP_MAXREXMTCNT 3	/* maximum number of retransmissions */

#endif	VMTP_LOGSTAT

#define VMTPIP_TTL	40	/* default time-to-live of IP packets */
#define VMTP_MAXRETRYCNT 10	/* maximum number of retries */

#define VMTP_INPKTGAP	0	/* default interpacket gap */

/*
 * Secure ip protocol numbers
 */
#define vmtp_securepacket(type) \
	((type) == IPPROTO_VMTPS || (type) == IPPROTO_VMTPS2 || \
	 (type) == ETHERTYPE_LE_VMTPS || (type) == ETHERTYPE_BE_VMTPS)

/*
 * Byte order handling:
 * Byteswaplong works only on little-endians machines. It's defined to
 * be a no-op on big-endians!
 */
#ifdef	LITTLE_ENDIAN
#define vmtp_oppositebyteorder(type) \
	((type) == IPPROTO_VMTP2 || (type) == IPPROTO_VMTPS2 || \
	 (type) == ETHERTYPE_BE_VMTP || (type) == ETHERTYPE_BE_VMTPS)

#define vmtp_byteswaplong(l)	ntohl(l)

#else	LITTLE_ENDIAN

#define vmtp_oppositebyteorder(type) \
	((type) == IPPROTO_VMTP || (type) == IPPROTO_VMTPS || \
	 (type) == ETHERTYPE_LE_VMTP || (type) == ETHERTYPE_LE_VMTPS)

#define vmtp_byteswaplong(l)	(l)

#endif	LITTLE_ENDIAN


struct vmtpstat {
	int	vst_badsum;
	int	vst_badencrsum;		/* On encrypted packet */
	int	vst_iphdrops;		/* IP packets */
	int	vst_ipintotal;
	int	vst_ipouttotal;
	int	vst_ethdrops;		/* Ethernet packets */
	int	vst_etintotal;
	int	vst_etouttotal;
	
};

#if	VMTP_HOSTID
#define vmtp_localaddr(addr) \
	((addr).va_type == VAT_INET && \
	 (addr).va_inet == vmtp_hostid)
#else	VMTP_HOSTID
#define vmtp_localaddr(addr) \
	((addr).va_type == VAT_INET && \
	 (addr).va_inet == hostid)
#endif	VMTP_HOSTID

#ifdef	KERNEL

struct vmtpcsr	*vmtp_newcsr(), *vmtp_maptocsr(), *vmtp_nextcsr();
struct vmtpser	*vmtp_newserver(), *vmtp_maptoserver(), *vmtp_nextserver();
struct vmtpcsr 	*vmtp_dequeuereq(), *vmtp_retrievereq();
struct vmtpcsr 	*vmtp_newrb();
struct vmtpcsr  *vmtp_findrb();
struct vmtpcsr	*vmtp_scanresponses();
struct vmtpeid vmtp_firstgroupmember(); 

/* timeout handlers et.c. */
int 	vmtp_hdllcsrtimeo(), vmtp_hdlrcsrtimeo(), vmtp_hdlgrtimeo();
int	vmtp_delayedreply(), esp_delayedprobe();

struct vmtpsynq	vtimeoqueue;		/* timeout queue of vmtpcsr's */
struct vmtpstat	vmtpstat;		/* vmtp statistics */

struct vmtpcsr 	*vlocalcsrmap[VMTP_HASHMAPSIZE];  /* local client map */
struct vmtpcsr 	*vremotecsrmap[VMTP_HASHMAPSIZE]; /* remote client map */
struct vmtpser 	*vservermap[VMTP_HASHMAPSIZE];    /* server map */

int	(*vmtp_handle[])();		/* packet handling routines */

#define vmtp_segsizetomsk(s) \
		(vmtp_sizemap[(s+VMTP_BLKSIZE-1)>>VMTP_BLKSIZESHIFT])
	 		/* Convert the segment size to a delivery mask */

u_long vmtp_sizemap[];		/* maps size in blocks to a delivery mask */

u_char vmtp_codetounix[];	/* maps vmtp reply codes to unix error codes */

#if	VMTP_LOGSTAT
extern	struct vmtpparam vmtpparam;
#endif	VMTP_LOGSTAT

#endif

#endif
