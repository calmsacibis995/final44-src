/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_ievar.h,v $
 * Revision 2.2  89/07/11  18:20:12  jjc
 * 		SunOS 4.0 version.
 * 	[89/04/03            jjc]
 * 
 */
/*	@(#)if_ievar.h 1.10 88/02/08 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

#ifndef	_IF_IEVAR_
#define	_IF_IEVAR_

/*
 * Definitions for data structures that the
 * Intel 82586 Ethernet driver uses internally.
 *
 * This file exists primarily  to allow network monitoring
 * programs easy access to the definition of ie_softc.
 */

/*
 * Input error counters
 */
struct ieierr {
	u_int	crc;
	u_int	aln;
	u_int	rsc;
	u_int	ovr;
};


#ifdef	IE_FDADDR
#define	IE_BUFSZ	ETHERMTU
#else	IF_FDADDR
#define	IE_BUFSZ	(sizeof (struct ether_header) + ETHERMTU)
#endif	IE_FDADDR

/*
 * Transmit buffers
 */
union ietbuf {
	union ietbuf	*ietbuf_next;
	u_char		ietbuf_data[IE_BUFSZ];
};

/*
 * Receive buffers
 *	The ierbuf_next field links rbufs into the free and loan-out
 *	lists.  When loaned, the ierbuf_es field links back to the
 *	governing softc structure.
 *
 *	The ierbuf_pad field compensates for Ethernet header length
 *	so that the portion of a given packet that remains after
 *	stripping off the Ethernet header is int aligned.
 *	NOTE: The padding is used with sparc to make sure that the packet
 *	after the ethernet header is int aligned.
 */
struct ierbuf {
	struct ierbuf	*ierbuf_next;
	struct ie_softc	*ierbuf_es;
#if defined(sparc) && !defined(IE_FDADDR)
	u_short		ierbuf_pad;
#endif sparc && !IE_FDADDR
	u_char		ierbuf_data[IE_BUFSZ];
};


/*
 * Each interface is referenced by a network interface structure,
 * es_if, which the routing code uses to locate the interface.
 * This structure contains the output queue for the interface, its address,
 * etc.  "es" is an artifact and indicates Ethernet Software status.
 */
struct	ie_softc {
	struct	arpcom es_ac;		/* common Ethernet structures */
#define	es_if		es_ac.ac_if	/* network-visible interface */
#define	es_enaddr	es_ac.ac_enaddr	/* hardware ethernet address */
#define	es_mcaddr	es_ac.ac_mcaddr	/* multicast address vector */
#define	es_nmcaddr	es_ac.ac_nmcaddr
					/* count of multicast addrs */
	union {				/* device registers... */
	    struct mie_device	*esr_mie;
	    struct obie_device	*esr_obie;
	    struct tie_device	*esr_tie;
	} es_r;
#define	es_mie		es_r.esr_mie	/* IE_MB: Multibus board registers */
#define	es_obie		es_r.esr_obie	/* IE_OB: on-board registers */
#define	es_tie		es_r.esr_tie	/* IE_TE: 3E registers */
	caddr_t		es_memspace;	/* + chip addr = kernel addr */
	int		es_paddr;	/* starting page number for board */
	int		es_memsize;	/* size of memory consumed for buffers,
					   CBs, etc. */
	caddr_t		es_base;	/* our addr of control block base */
	struct map	*es_rmap;	/* rmap for chip-visible data */
	struct timeval	es_latest;	/* latest packet arrival time */

	char		es_type;	/* type of controller */
	char		es_synccmd;	/* doing synchronous command */
	char		es_pendreque;	/* requeued packet being transmitted */

	/* Control block info */
	struct iecb	*es_cbhead;	/* CBL head */
	struct iecb	*es_cbtail;	/* CBL tail */

	/* Dedicated control blocks */
	struct iescp	*es_scp;	/* SCP ptr */
	struct ieiscp	*es_iscp;	/* ISCP ptr */
	struct iescb	*es_scb;	/* SCB ptr */
	struct iecb	*es_cbnop;	/* no-op CB for use by iedog */
	struct iecb	*es_cbsync;	/* used by iesynccmd callers */

	/* Transmit Frame Descriptors */
	u_short		es_tfds;	/* total number of tfds */
	struct ietfd	*es_tfdpool;	/* tfd pool */
	struct ietfd	*es_tfd_free;	/* free list head */

	/* Transmit Buffer Descriptors */
	u_short		es_tbds;	/* total number of tbds */
	u_short		es_ftbds;	/* number of free tbds */
	struct ietbd	*es_tbdring;	/* tbd ring start */
	struct ietbd	*es_tbdlim;	/* one past end of ring */
	struct ietbd	*es_utbd;	/* queue head for in-use tbds */
	struct ietbd	*es_ftbd;	/* queue head for free tbds */

	/* Transmit Buffers */
	u_short		es_tbufs;	/* total number of tbufs */
	union ietbuf	*es_tbufpool;	/* tbuf pool */
	union ietbuf	*es_tbuf_free;	/* free list head */

	/* Receive Frame Descriptors */
	u_short		es_rfds;	/* total number of rfds */
	struct ierfd	*es_rfdring;	/* rfd ring start */
	struct ierfd	*es_rfdlim;	/* one past end of ring */
	struct ierfd	*es_rfdhd;	/* rfd list head */
	struct ierfd	*es_rfdtl;	/* rfd list tail */

	/* Receive Buffer Descriptors */
	u_short		es_rbds;	/* total number of rbds */
	struct ierbd	*es_rbdring;	/* rbd ring start */
	struct ierbd	*es_rbdlim;	/* one past end of ring */
	struct ierbd	*es_rbdhd;	/* rbd list head */
	struct ierbd	*es_rbdtl;	/* rbd list tail */

	/* Receive Buffers */
	u_short		es_rbufs;	/* total number of rbufs */
	u_short		es_loaned;	/* loan-out list length */
	struct ierbuf	*es_rbufpool;	/* rbuf pool */
	struct ierbuf	*es_rbuf_free;	/* free list head */
	struct ierbuf	*es_rbuf_loan;	/* loan-out list head;

	/* Error Counters */
	u_int		es_xmiturun;	/* xmit DMA underruns */
	u_int		es_dogreset;	/* iedog resets */
	u_int		es_trtry;	/* transmit collisions (net jams) */
	u_int		es_tnocar;	/* lost carrier on output */
	u_int		es_noCTS;	/* lost CTS on output */
	struct ieierr	es_ierr;	/* input errors of various sorts */

	/* Statistics Counters */
	u_int		es_runotready;	/* RU not ready occurrences */
	u_int		es_ieheart;	/* heartbeat counter */
	u_int		es_iedefer;	/* deferred transmission counter */
	u_int		es_started;	/* times into iestartout with > 0
					   packets on queue */
	u_int		es_started2;	/* times into iestartout with > 1
					   packet on queue */
	u_int		es_outcpy;	/* output copy operations */
	u_int		es_notbds;	/* output resource exhaustion (tbds) */
	u_int		es_prloans;	/* potential receive buffer loanouts */
	u_int		es_arloans;	/* actual receive buffer loanouts */
	u_int		es_requeues;	/* requeues after failed xmit attempts */
};

#endif	_IF_IEVAR_
