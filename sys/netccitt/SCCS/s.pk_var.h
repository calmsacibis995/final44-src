h45336
s 00002/00002/00203
d D 8.1 93/06/10 22:54:13 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00067/00010/00138
d D 7.12 92/12/08 16:19:25 sklower 12 11
c contributions from Dirk Husemann
e
s 00011/00015/00137
d D 7.11 91/05/29 19:34:03 sklower 11 10
c go back to pkcb's being dynamically allocated for LLC2's sake
e
s 00010/00000/00142
d D 7.10 91/05/09 21:18:15 sklower 10 9
c add useful debugging cache for mbufs
e
s 00012/00006/00130
d D 7.9 91/03/12 15:08:37 sklower 9 8
c This version doubly links all pklcd's for debugging;
c also fixes problem with gnu cc for case where CCITT is not defined
c but file is included elsewhere (e.g. iso).
e
s 00004/00005/00132
d D 7.8 91/01/09 15:36:41 sklower 8 7
c change type of template to mbuf to get rid of dtom's;
c change name of ifrag to something more descriptive and add limit;
c move flags to x25.h even though user's won't use them.
e
s 00007/00001/00130
d D 7.7 90/10/04 19:50:15 sklower 7 6
c capture current work; fix minor bugs concerning packet lengths &
c conventions; add routine to fragment datagrams into complete sequences.
e
s 00020/00019/00111
d D 7.6 90/08/30 18:48:43 sklower 6 5
c this version compiles; completely untested
e
s 00005/00015/00125
d D 7.5 90/06/21 12:29:16 sklower 5 4
c assign SCCS numbers for ``June'' beta tape; not yet tested.
e
s 00009/00005/00131
d D 7.4 90/05/22 15:46:29 sklower 4 3
c checkpoint before changing pq structure to be a sockbuf for downq 
c and only retaining up method
e
s 00043/00013/00093
d D 7.3 90/05/16 15:46:06 sklower 3 2
c periodic checkpoint against catastrophic loss
e
s 00057/00012/00049
d D 7.2 90/05/15 11:27:50 sklower 2 1
c checkpoint before trying including old pkcb in ifaddr.
e
s 00061/00000/00000
d D 7.1 90/05/11 11:19:43 sklower 1 0
c date and time created 90/05/11 11:19:43 by sklower
e
u
U
t
T
I 1
D 2
/* Copyright (c) University of British Columbia, 1984 */
E 2
I 2
D 12
/*
 * Copyright (c) University of British Columbia, 1984
 * Copyright (c) 1990 The Regents of the University of California.
E 12
I 12
/* 
 * Copyright (c) Computing Centre, University of British Columbia, 1985 
 * Copyright (C) Computer Science Department IV, 
 * 		 University of Erlangen-Nuremberg, Germany, 1990, 1991, 1992
D 13
 * Copyright (c) 1992   Regents of the University of California.
E 12
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
I 12
 * 
 * This code is derived from software contributed to Berkeley by the
 * Laboratory for Computation Vision and the Computer Science Department
 * of the the University of British Columbia and the Computer Science
 * Department (IV) of the University of Erlangen-Nuremberg, Germany.
E 12
 *
D 12
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
 *
E 12
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

I 2
D 5
/*
 * Protocol-Protocol Packet Buffer.
 * (Eventually will be replace by system-wide structure).
 */
E 5
E 2
D 12

E 12
I 2
D 5
struct	pq	{
	int	(*pq_put)();	/* How to process data */
	struct	mbuf *pq_data;	/* Queued data */
	int	pq_space;	/* For accounting */
	int	pq_flags;
	int	(*pq_unblock)();/* called & cleared when unblocking */
	caddr_t pq_proto;	/* for other service entries */
	caddr_t pq_next;	/* next q, or route, or pcb */
};

E 5
E 2
/*
 *
 *  X.25 Logical Channel Descriptor
 *
 */

struct pklcd {
I 2
D 5
	struct	pq lcd_downq, lcd_upq;	/* protocol glue for datagram service */
E 5
I 5
D 9
	int	(*lcd_send)();		/* if X.25 front end, direct connect */
E 9
I 9
	struct 	pklcd_q {
		struct	pklcd_q *q_forw;	/* debugging chain */
		struct	pklcd_q *q_back;	/* debugging chain */
	} lcd_q;
E 9
	int	(*lcd_upper)();		/* switch to socket vs datagram vs ...*/
	caddr_t	lcd_upnext;		/* reference for lcd_upper() */
I 9
	int	(*lcd_send)();		/* if X.25 front end, direct connect */
	caddr_t lcd_downnext;		/* reference for lcd_send() */
E 9
E 5
E 2
	short   lcd_lcn;		/* Logical channel number */
	short   lcd_state;		/* Logical Channel state */
D 9
        bool	lcd_intrconf_pending;	/* Interrupt confirmation pending */
	octet	lcd_intrdata;		/* Octet of incoming intr data */
E 9
	short   lcd_timer;		/* Various timer values */
I 3
	short   lcd_dg_timer;		/* to reclaim idle datagram circuits */
I 9
        bool	lcd_intrconf_pending;	/* Interrupt confirmation pending */
	octet	lcd_intrdata;		/* Octet of incoming intr data */
E 9
E 3
	char	lcd_retry;		/* Timer retry count */
	char	lcd_rsn;		/* Seq no of last received packet */
	char	lcd_ssn;		/* Seq no of next packet to send */
	char	lcd_output_window;	/* Output flow control window */
	char	lcd_input_window;	/* Input flow control window */
	char	lcd_last_transmitted_pr;/* Last Pr value transmitted */
        bool	lcd_rnr_condition;	/* Remote in busy condition */
        bool	lcd_window_condition;	/* Output window size exceeded */
        bool	lcd_reset_condition;	/* True, if waiting reset confirm */
I 9
	bool	lcd_rxrnr_condition;	/* True, if we have sent rnr */
E 9
	char	lcd_packetsize;		/* Maximum packet size */
	char	lcd_windowsize;		/* Window size - both directions */
        octet	lcd_closed_user_group;	/* Closed user group specification */
	char	lcd_flags;		/* copy of sockaddr_x25 op_flags */
I 9
	struct	mbuf *lcd_facilities;	/* user supplied facilities for cr */
E 9
D 8
	struct	x25_packet *lcd_template;/* Address of current packet */
E 8
I 8
	struct	mbuf *lcd_template;	/* Address of response packet */
E 8
	struct	socket *lcd_so;		/* Socket addr for connection */
D 4
	struct	sockaddr_x25 *lcd_craddr;/* Calling address */
	struct	sockaddr_x25 *lcd_ceaddr;/* Called address */
E 4
I 4
	struct	sockaddr_x25 *lcd_craddr;/* Calling address pointer */
	struct	sockaddr_x25 *lcd_ceaddr;/* Called address pointer */
I 8
D 9
	struct	mbuf *lcd_facilities;	/* user supplied facilities for cr */
E 9
E 8
E 4
	time_t	lcd_stime;		/* time circuit established */
	long    lcd_txcnt;		/* Data packet transmit count */
	long    lcd_rxcnt;		/* Data packet receive count */
	short   lcd_intrcnt;		/* Interrupt packet transmit count */
	struct	pklcd *lcd_listen;	/* Next lcd on listen queue */
D 2
	struct	pkcb *lcd_pkp;		/* network this lcd is attached to */
E 2
I 2
D 3
	struct	ifaddr *lcd_ifa;	/* network this lcd is attached to */
E 3
I 3
D 4
	struct	pkcb *lcd_pkp;		/* network this lcd is attached to */
E 4
I 4
	struct	pkcb *lcd_pkp;		/* Network this lcd is attached to */
I 7
D 8
	struct	mbuf *lcd_ifrag;	/* IP, CLNP reassembly */
E 8
I 8
	struct	mbuf *lcd_cps;		/* Complete Packet Sequence reassembly*/
	long	lcd_cpsmax;		/* Max length for CPS */
E 8
E 7
D 6
	struct	sockaddr_x25 lcd_faddr	/* Remote Address (Calling) */
	struct	sockaddr_x25 lcd_laddr	/* Local Address (Called) */
E 6
I 6
	struct	sockaddr_x25 lcd_faddr;	/* Remote Address (Calling) */
	struct	sockaddr_x25 lcd_laddr;	/* Local Address (Called) */
E 6
I 5
	struct	sockbuf lcd_sb;		/* alternate for datagram service */
E 5
E 4
E 3
E 2
};
D 8

I 3
#define X25_DG_CIRCUIT	0x10		/* lcd_flag: used for datagrams */
#define X25_DG_ROUTING	0x20		/* lcd_flag: peer addr not yet known */
E 8
E 3
I 2

E 2
/*
I 3
 * Per network information, allocated dynamically
 * when a new network is configured.
 */

struct	pkcb {
D 12
	struct	pkcb *pk_next;
E 12
I 12
	struct pkcb_q {
		struct pkcb_q *q_forw;
		struct pkcb_q *q_backw;
	} pk_q;
E 12
D 11
	struct	x25_ifaddr *pk_ia;	/* backpointer to ifaddr */
E 11
I 11
	short	pk_state;		/* packet level status */
	short	pk_maxlcn;		/* local copy of xc_maxlcn */
E 11
D 4
	short	pk_state;		/* packet level status */
	int	(*pk_output) ();	/* link level output procedure */
E 4
I 4
	int	(*pk_lloutput) ();	/* link level output procedure */
I 12
	caddr_t (*pk_llctlinput) ();    /* link level ctloutput procedure */
E 12
I 5
	caddr_t pk_llnext;		/* handle for next level down */
E 5
D 11
	int	(*pk_start) ();		/* connect, confirm method */
E 11
E 4
	struct	x25config *pk_xcp;	/* network specific configuration */
I 4
D 11
	short	pk_state;		/* packet level status */
E 4
	struct	x25config pk_xc;	/* network specific configuration */
E 11
I 11
	struct	x25_ifaddr *pk_ia;	/* backpointer to ifaddr */
E 11
	struct	pklcd **pk_chan;	/* actual size == xc_maxlcn+1 */
I 12
	short	pk_dxerole;		/* DXE role of PLE over LLC2 */
	short	pk_restartcolls;	/* counting RESTART collisions til resolved */
	struct	rtentry *pk_rt;		/* back pointer to route */
	struct  rtentry *pk_llrt;       /* pointer to reverse mapping */
	u_short pk_refcount;  		/* ref count */
E 12
D 11
#define	pk_maxlcn pk_xc.xc_maxlcn	/* local copy of xc_maxlcn */
E 11
};
I 12

#define FOR_ALL_PKCBS(p) for((p) = (struct pkcb *)(pkcb_q.q_forw); \
			     (pkcb_q.q_forw != &pkcb_q) && ((struct pkcb_q *)(p) != &pkcb_q); \
			     (p) = (struct pkcb *)((p) -> pk_q.q_forw))

#define	PQEMPTY		(pkcb_q.q_forw == &pkcb_q)

E 12
/*
E 3
D 2
 * Per network information, allocated dynamically
 * when a new network is configured.
E 2
I 2
 *	Interface address, x25 version. Exactly one of these structures is 
 *	allocated for each interface with an x25 address.
 *
 *	The ifaddr structure conatins the protocol-independent part
 *	of the structure, and is assumed to be first.
E 2
 */
I 2
struct x25_ifaddr {
	struct	ifaddr ia_ifa;		/* protocol-independent info */
D 11
#define ia_ifp		ia_ifa.ifa_ifp
#define	ia_flags	ia_ifa.ifa_flags
D 3
	struct	x25_ifaddr *ia_next;	/* next in list of x25 addresses */
	struct	sockaddr_x25 ia_addr;	/* reserve space for interface name */
E 3
I 3
	struct	pkcb	ia_pkcb;	/* per network information */
#define ia_maxlcn	ia_pkcb.pk_maxlcn
#define ia_chan		ia_pkcb.pk_chan
D 6
#define	ia_addr		ia_pkcb.pk_xc.xc_addr
E 6
I 6
#define ia_xc		ia_pkcb.pk_xc
#define ia_xcp		ia_pkcb.pk_xcp
E 6
E 3
	struct	sockaddr_x25 ia_sockmask; /* reserve space for netmask */
E 11
I 11
#define ia_ifp	ia_ifa.ifa_ifp
#define	ia_flags ia_ifa.ifa_flags
	struct	x25config ia_xc;	/* network specific configuration */
I 12
	struct  pkcb *ia_pkcb;
E 12
#define ia_maxlcn ia_xc.xc_maxlcn
	int	(*ia_start) ();		/* connect, confirm method */
	struct	sockaddr_x25 ia_dstaddr; /* reserve space for route dst */
E 11
D 3
	struct	x25config *ia_xcp;	/* network specific configuration */
	struct	x25config *ia_xc;	/* network specific configuration */
	short	ia_state;		/* packet level status */
#define ia_maxlcn ia->ia_xc.xc_maxlcn	/* local copy of xc_maxlcn */
	struct	pklcd **ia_chan;	/* dispatch vector for ciruits */
E 3
};
E 2

D 2
struct	pkcb {
	struct	pkcb *pk_next;
	short	pk_state;		/* packet level status */
	short	pk_maxlcn;		/* local copy of xc_maxlcn */
	int	(*pk_output) ();	/* link level output procedure */
	struct	x25config *pk_xcp;	/* network specific configuration */
	struct	pklcd *pk_chan[1];	/* actual size == xc_maxlcn+1 */
E 2
I 2
/*
 * ``Link-Level'' extension to Routing Entry for upper level
 * packet switching via X.25 virtual circuits.
 */
D 3
struct rtext_x25 {
	struct	pklcd *rtx_lcd;
	int	rtx_state;
	struct	rtentry *rtx_rt;
E 3
I 3
D 6
struct rtextension_x25 {
	struct	pklcd *rtx_lcd;		/* local connection block */
	struct	rtentry *rtx_rt;	/* back pointer to route */
	struct	x25_ifaddr *rtx_ia;	/* may not be same as rt_ifa */
	int	rtx_state;		/* can't trust lcd->lcd_state */
	int	rtx_flags;
	int	rtx_timer;		/* for idle timeout */
E 6
I 6
struct llinfo_x25 {
D 7
	struct	pklcd *lx_lcd;		/* local connection block */
E 7
I 7
	struct	llinfo_x25 *lx_next;	/* chain together in linked list */
	struct	llinfo_x25 *lx_prev;	/* chain together in linked list */
E 7
	struct	rtentry *lx_rt;		/* back pointer to route */
I 7
	struct	pklcd *lx_lcd;		/* local connection block */
E 7
	struct	x25_ifaddr *lx_ia;	/* may not be same as rt_ifa */
	int	lx_state;		/* can't trust lcd->lcd_state */
	int	lx_flags;
	int	lx_timer;		/* for idle timeout */
I 7
	int	lx_family;		/* for dispatch */
E 7
E 6
E 3
E 2
};

I 3
D 6
/* States for rtx_state */
#define XRS_NEWBORN		0
#define XRS_RESOLVING		1
#define XRS_FREE		2
#define XRS_CONNECTED		3
#define XRS_CONNECTING		4
#define XRS_DISCONNECTING 	5
E 6
I 6
/* States for lx_state */
#define LXS_NEWBORN		0
#define LXS_RESOLVING		1
#define LXS_FREE		2
D 11
#define LXS_CONNECTED		3
#define LXS_CONNECTING		4
E 11
I 11
#define LXS_CONNECTING		3
#define LXS_CONNECTED		4
E 11
#define LXS_DISCONNECTING 	5
I 7
#define LXS_LISTENING 		6
E 7
E 6

/* flags */
D 6
#define XRF_VALID	0x1		/* Circuit is live, etc. */
#define XRF_RTHELD	0x2		/* this lcb references rtentry */
E 6
I 6
#define LXF_VALID	0x1		/* Circuit is live, etc. */
#define LXF_RTHELD	0x2		/* this lcb references rtentry */
I 7
#define LXF_LISTEN	0x4		/* accepting incoming calls */
E 7
E 6

I 10
/*
I 12
 * Definitions for accessing bitfields/bitslices inside X.25 structs
 */


struct x25bitslice {
	unsigned int bs_mask;
	unsigned int bs_shift;
};

#define	calling_addrlen	0
#define	called_addrlen	1
#define	q_bit	        2
#define	d_bit           3
#define	fmt_identifier	4
#define	lc_group_number	1
#define	p_r             5
#define	m_bit           6
#define	p_s             7
#define	zilch           8

#define	X25GBITS(Arg, Index)	(((Arg) & x25_bitslice[(Index)].bs_mask) >> x25_bitslice[(Index)].bs_shift)
#define	X25SBITS(Arg, Index, Val)	(Arg) |= (((Val) << x25_bitslice[(Index)].bs_shift) & x25_bitslice[(Index)].bs_mask)
#define	X25CSBITS(Arg, Index, Val)	(Arg) = (((Val) << x25_bitslice[(Index)].bs_shift) & x25_bitslice[(Index)].bs_mask)

extern struct x25bitslice x25_bitslice[];


#define ISOFIFTTYPE(i,t) ((i)->if_type == (t))
#define ISISO8802(i) ((ISOFIFTTYPE(i, IFT_ETHER) || \
		       ISOFIFTTYPE(i, IFT_ISO88023) || \
		       ISOFIFTTYPE(i, IFT_ISO88024) || \
		       ISOFIFTTYPE(i, IFT_ISO88025) || \
		       ISOFIFTTYPE(i, IFT_ISO88026) || \
		       ISOFIFTTYPE(i, IFT_P10) || \
		       ISOFIFTTYPE(i, IFT_P80) || \
		       ISOFIFTTYPE(i, IFT_FDDI)))

/*
E 12
 * miscellenous debugging info
 */
struct mbuf_cache {
	int	mbc_size;
	int	mbc_num;
	int	mbc_oldsize;
	struct	mbuf **mbc_cache;
};

E 10
E 3
D 9
#ifdef KERNEL
E 9
I 9
#if defined(KERNEL) && defined(CCITT)
E 9
D 2
struct	pkcb *pkcbhead;		/* head of linked list of networks */
E 2
I 2
D 3
struct	x25_ifaddr *x25_ifaddr;		/* head of linked list of networks */
E 3
I 3
D 12
struct	pkcb *pkcbhead;		/* head of linked list of networks */
E 12
I 12
extern struct pkcb_q pkcb_q;
E 12
E 3
E 2
struct	pklcd *pk_listenhead;
I 4
struct	pklcd *pk_attach();
E 4

D 9
char	*pk_name[], *pk_state[];
E 9
I 9
extern char	*pk_name[], *pk_state[];
E 9
int	pk_t20, pk_t21, pk_t22, pk_t23;
#endif
E 1
