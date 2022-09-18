/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_le.c,v $
 * Revision 2.9  89/10/11  14:52:46  dlb
 * 	New vm_map_pageable calling sequence.
 * 	[89/10/07            dlb]
 * 
 * Revision 2.8  89/07/11  18:20:27  jjc
 * 	Conditionalized allocation of SCSI controller table under
 * 	DVMA_KLUGE instead of CS_GENERIC.
 * 	Included "machine/cpu.h" for definition of DVMA_KLUGE.
 * 	[88/07/08            jjc]
 * 
 * Revision 2.7  89/03/09  21:52:21  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  20:02:53  gm0w
 * 	Added new copyright and fixed includes as part of kernel cleanup.
 * 	Switched CMU conditionals to MACH.
 * 	[89/02/12            jjc]
 * 
 * Revision 2.5  88/11/21  16:59:05  rvb
 * 	IF_CNTRS says whether packet statistics are kept.  For now this
 * 	is always true iff MACH is true.
 * 	MACH_DEVICE (and DLI) turns on the special hack to let the
 * 	emulation guys read and write the raw ether.
 * 	
 * 		Add counters: if_[le]{out,in} -- e is log packet size, l is size
 * 		in 8 byte multiples to 128.  in and out are measured at the
 * 		interface.  if_narp says don't count arp packets if_arp is
 * 		always the arp count.
 * 	[88/10/18            rvb]
 * 
 * Revision 2.4  88/08/24  02:18:47  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 *
 *  1-Mar-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Made VOLATILE
 *
 * 20-Mar-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added le_falloc() to allocate virtual memory in the F segment
 *	so the Ethernet chip can access the initialization block
 *	and the buffers.
 *	[ V5.1(F8) ]
 *
 * 26-Jan-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Converted to 4.3 BSD under CS_GENERIC.
 *	Modified to Mach VM under MACH_VM.
 *
 */ 

#ifndef	lint
static  char sccsid[] = "@(#)if_le.c 1.1 86/02/03 Copyr 1985 Sun Micro";
#endif

#define IF_CNTRS MACH

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */
/* XXX for debugging FIXME */
/* #define DEBUG	*/
/* #define LEDEBUG	*/


/*
 * Guide to FIXMEs:
 *
 * FIXME MULTICAST means that this section of code may have to be changed
 *   if the driver has to handle Multicasting.
 * Other FIXMEs are usually deficiencies in the code.
 */

#include <le.h>

#if	NLE > 0
#include <dli.h>

/*
 * AMD Am7990 LANCE Ethernet Controller driver
 */

#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/map.h>
#include <sys/socket.h>
#include <sys/errno.h>

#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/ioctl.h>

#include <net/if.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>

#include <sundev/mbvar.h>
#include <sunif/if_lereg.h>
#ifdef	MACH
#include <sunif/ether_addr.h>
#endif	MACH
#ifdef	MACH
#include <vm/vm_kern.h>
#include <mach/vm_prot.h>
#include <mach/vm_param.h>
#include <machine/cpu.h>
#endif	MACH

#if	DLI
#include <net/dli_var.h>
extern struct dli_var if_dlv[];
#endif	DLI

int	leprobe(), leattach(), leintr();
struct	mb_device *leinfo[NLE];
struct	mb_driver ledriver = {
	leprobe, 0, leattach, 0, 0, leintr,
	sizeof (struct le_device), "le", leinfo, 0, 0, 0,
};

int	leinit(),leioctl(),leoutput(),lereset();

struct mbuf *copy_to_mbufs();
struct mbuf *mclgetx();


/*
 * Transmit and receive buffer layout.
 *	The chip sees only the fields from lb_ehdr onwards; the
 *	preceding fields are for the driver's benefit. The e_to_lb
 *	and b_to_lb macros defined below convert the address of the
 *	start of a lb_ehdr or lb_buffer field to the address of the
 *	start of the containing le_buf structure.
 *
 *	The buffer size is chosen to give room for the maximum ether
 *	transmission unit, an overrun consisting of the entire fifo
 *	contents, and slop that experience indicates is necessary.
 *	(The exact amount of slop required is still unknown.)
 */
struct le_buf {
	/* Fields used only by driver: */
	struct le_buf	*lb_next;		/* Link to next buffer */
	struct le_softc	*lb_es;			/* Link back to sw status */
	/* Fields seen by LANCE chip: */
	struct ether_header	lb_ehdr;	/* Packet's ether header */
	u_char		lb_buffer[MAXBUF];	/* Packet's data */
};
/*
 * Given a lb_ehdr or lb_buffer address, produce the address of its
 * containing le_buf structure.
 *
 * N.B.: These definitions assume that the compiler inserts no padding
 * between the fields of the le_buf structure.  (If it did, we'd be
 * in trouble on other grounds as well.)
 */
#define e_to_lb(e) \
	(struct le_buf *)((caddr_t)(e) - sizeof(struct le_softc *) \
			- sizeof(struct le_buf *))
#define b_to_lb(b) \
	(struct le_buf *)((caddr_t)(b) - sizeof(struct ether_header) \
			- sizeof(struct le_softc *) - sizeof(struct le_buf *))


/*
 * Ethernet software status per interface.
 *
 * Each interface is referenced by a network interface structure,
 * es_if, which the routing code uses to locate the interface.
 * This structure contains the output queue for the interface, its address, ...
 * "es" indicates Ethernet Software status.
 */
struct	le_softc {
	struct	arpcom es_ac;		/* common ethernet structures */
#define es_if		es_ac.ac_if	/* network-visible interface */
#define es_enaddr	es_ac.ac_enaddr	/* hardware ethernet address */
volatile
	struct	le_init_block *es_ib;	/* Initialization block */
	struct	le_md *es_rdrp;		/* Receive Descriptor Ring Ptr */
	struct	le_md *es_rdrend;	/* Receive Descriptor Ring End */
	int	es_nrmdp2;		/* log(2) Num. Rcv. Msg. Descs. */
	int	es_nrmds;		/* Num. Rcv. Msg. Descs. */
	struct	le_md *es_tdrp;		/* Transmit Descriptor Ring Ptr */
	struct	le_md *es_tdrend;	/* Receive Descriptor Ring End */
	int	es_ntmdp2;		/* log(2) Num. Tran. Msg. Descs. */
	int	es_ntmds;		/* Num. Xmit. Msg. Descs. */
	struct	le_buf *es_rbufs;	/* Receive Buffers */
	int	es_nrbufs;		/* Number of Receive Buffers */
	struct	le_buf *es_tbufs;	/* Transmit Buffers */
	int	es_ntbufs;		/* Number of Transmit Buffers */
	struct	le_md *es_his_rmd;	/* Next descriptor in ring */
	struct	le_md *es_cur_tmd;	/* Tmd for start of current packet */
	struct	le_md *es_nxt_tmd;	/* Tmd for start of next packet */
	struct	le_buf *es_rbuf_free;	/* Head of free list */
	struct	le_buf *es_tbuf_free;	/* Head of free list */
	struct	le_buf *es_rbuf_loaned;	/* Head of loan-out list */
	struct	mbuf *es_tmbuf;		/* Packet being transmitted */
	u_int	es_flags;		/* State info */

	/* Error counters */
	int	es_extrabyte;		/* Rev C Lance extra byte problem */
	int	es_fram;		/* Receive Framing Errors (dribble) */
	int	es_crc;			/* Receive CRC Errors */
	int	es_oflo;		/* Receive overruns */
	int	es_uflo;		/* Transmit underruns */
	int	es_retries;		/* Transmit retries */
	int	es_missed;		/* Number of missed packets */
	int	es_noheartbeat;		/* Number of nonexistent heartbeats */

	/* Performance statistics counters */
	int	es_started;		/* Times through lestart with > 0
					   packets ready to go out */
	int	es_started2;		/* Times through lestart with > 1
					   packet ready to go out */
	int	es_potential_rloans;	/* Number of opportunities to loan
					   out a receive buffer */
	int	es_actual_rloans;	/* Cumulative number of receive buffers
					   loaned to protocol layers */
	int	es_pullups;		/* Number of opackets with short
					   initial mbufs */
	int	es_no_tmds;		/* Number of resource exhaustion
					   instances on output */
#ifdef	MACH
	short	es_old_ifflags;		/* old value of if_flags */
#endif	MACH
} le_softc[NLE];

/*
 * Bit definitions for es_flags field:
 */
#define LE_TBUSY	0x01	/* Packet transmission in progress */
#define LE_TOPENDING	0x02	/* Transmit timeout pending */


/*
 * Resource amounts.
 *	For now, at least, these never change, and resources
 *	are allocated once and for all.  However, we potentially
 *	could recast them into advisory variables (changing to
 *	one instance per interface) with the meaning that, the
 *	next time resources are allocated to the interface, grab
 *	these amounts.
 *
 *	Reducing the number of tmds below 16 causes them to run
 *	out occasionally.  (This is somewhat surprising.)  Since
 *	the incremental cost of going from 8 to 16 is only 64
 *	bytes, we stick with the higher number.
 *
 *	Reducing the number of rmds below 16 leads to occasional
 *	missed packets.  By the same reasoning, we stick with
 *	the higher value.  [Even 16 doesn't seem to be enough on
 *	a loaded net, so we'll try 32 for a while.]
 */
/* Numbers of ring descriptors */
int le_ntmdp2 = 4;
int le_nrmdp2 = 5;

/* Numbers of buffers */
int le_ntbufs = 1;
int le_nrbufs = 40;	/* Ouch! one per rmd plus eight for loan-outs */


/*
 * Allocate an array of "number" structures
 * of type "structure" in kernel memory.
 */
#ifdef	MACH
#define getstruct(structure, number)   \
	(structure *) kmem_alloc( kernel_map, \
				  (vm_size_t)(sizeof(structure) * number), \
				  TRUE )
#else	MACH
#define getstruct(structure, number)   \
	(structure *) kmem_alloc( (sizeof(structure) * number) )
#endif	MACH

/*
 * Convert a stored Lance address to a CPU virtual address.
 *	FIXME: make this reasonable.
 */
#define le_buf_addr(md)  (DVMA_KLUGE + \
			    (u_char *)((md->lmd_hadr << 16) + md->lmd_ladr))

/*
 * Return the address of an adjacent descriptor in the given ring.
 */
#define next_rmd(es,rmdp)	((rmdp) == (es)->es_rdrend		\
					? (es)->es_rdrp : ((rmdp) + 1))
#define next_tmd(es,tmdp)	((tmdp) == (es)->es_tdrend		\
					? (es)->es_tdrp : ((tmdp) + 1))
#define prev_tmd(es,tmdp)	((tmdp) == (es)->es_tdrp		\
					? (es)->es_tdrend : ((tmdp) - 1))

/*
 * Buffer manipulation macros (see below for routines).
 *
 * A receive buffer can be in one of three states:
 *	free:		inactive and available for use
 *	attached:	awaiting packet reception and visible to
 *			the LANCE chip as a packet receptacle
 *	loaned:		contains packet data that is being processed
 *			by the higher-level protocol code
 * Free buffers are chained together through their lb_next fields into
 * a free list rooted at the le_softc.es_rbuf_free field.  Attached
 * buffers can be found only by working back from the receive ring
 * descriptors.  Loaned buffers are chained onto the list rooted at
 * le_softc.es_rbuf_loaned.
 *
 * List manipulation consitutes a critical region.  Callers of these
 * routines must lock things appropriately.
 */

/*
 * Link the buffer *bp into the list rooted at lp.
 */
#define le_linkin(lp, bp) \
	(bp)->lb_next = (lp), \
	(lp) = (bp)

/*
 * Take a receive buffer and put it on the free or loaned list.
 */
#define free_rbuf(es, rb)	le_linkin(es->es_rbuf_free, rb)
#define loan_rbuf(es, rb)	le_linkin(es->es_rbuf_loaned, rb)

/*
 * Return nonzero iff *bp is on the list rooted at *lpp.
 *	Assumes lpp and bp are both nonnull.
 */
#define le_onlist(lpp, bp)	le_lpredp(lpp, bp)

struct le_buf	*get_rbuf();
struct le_buf	**le_lpredp();

/*
 * Probe for device.
 */
leprobe(reg)
	caddr_t reg;
{
	register volatile struct le_device *le = (volatile struct le_device *)reg;

	if (pokec((char *)&le->le_rdp, 0))	/* FIXME - need better test */
		return (0);
	return (sizeof (struct le_device));
}

/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.
 */
leattach(md)
	struct mb_device *md;
{
	struct le_softc *es = &le_softc[md->md_unit];

	/* Reset the chip. */
	((volatile struct le_device *)md->md_addr)->le_rap = LE_CSR0;
	((volatile struct le_device *)md->md_addr)->le_csr = LE_STOP;

#ifdef	MACH
	(void) localetheraddr((struct ether_addr *)NULL, es->es_enaddr);
#else	MACH
	(void) localetheraddr((struct ether_addr *)NULL, &es->es_enaddr);
#endif	MACH

#ifdef	notdef
	/*
	 * We would like to allocate buffer and descriptor memory
	 * now, but we can't do it now, since kmem_alloc hasn't been
	 * initialized yet.  Thus we defer it to init time.
	 */
	le_alloc_buffers(es);
#endif	notdef

	/* Do hardware-independent attach stuff. */
	ether_attach(&es->es_if, md->md_unit, "le",
		     leinit, leioctl, leoutput, lereset);
}

#ifdef	DVMA_KLUGE
/*
 *	Allocate wired virtual memory from the F segment
 *	for use by the Ethernet chip
 */
caddr_t le_falloc(byte_size, panic_msg)
int	byte_size;
char	*panic_msg;
{
	static caddr_t	cur_va = (caddr_t)DVMA_KLUGE;
	static caddr_t	end_va = (caddr_t)DVMA_KLUGE;
	kern_return_t	retval;
	vm_offset_t	size;

	if (cur_va + byte_size > end_va){
		cur_va = (caddr_t)round_page(cur_va);
		size = round_page(byte_size);
		retval = vm_map_find(kernel_map, VM_OBJECT_NULL, 0, &cur_va,
					size, TRUE);
		if (retval == KERN_SUCCESS){
			(void)vm_map_pageable(kernel_map, cur_va,
				cur_va + size, VM_PROT_READ|VM_PROT_WRITE);
			end_va = cur_va + size - 1;
		}
		else
			panic(panic_msg);
	}
	cur_va += byte_size;
	return(cur_va - byte_size);
}
#endif	DVMA_KLUGE

/*
 * Grab memory for message descriptors and buffers and set fields
 * in the interfaces's software status structure accordingly.  The
 * memory obtained is _not_ intialized; this is done later.
 * Called from leinit, since attach time is too early.
 *
 * It must be possible to call this routine repeatedly with
 * no ill effects.
 */
le_alloc_buffers(es)
	register struct le_softc *es;
{
	/*
	 * If resources are already allocated, don't mess with them.
	 *	We could consider dynamic resource reallocation here,
	 *	but it would require adding code to wait for active
	 *	resources to become free.
	 */
	if (es->es_ib == (struct le_init_block *)0) {
		/* Initialization block */
#ifdef	DVMA_KLUGE
		es->es_ib = (volatile struct le_init_block *)le_falloc(
				sizeof(struct le_init_block),
				"Could not allocate initialization block");
#else	DVMA_KLUGE
		es->es_ib = getstruct(struct le_init_block , 1);
#endif	DVMA_KLUGE

		/* Set numbers of message descriptors. */
		es->es_nrmdp2 = le_nrmdp2;
		es->es_ntmdp2 = le_ntmdp2;
		es->es_nrmds = 1 << es->es_nrmdp2;
		es->es_ntmds = 1 << es->es_ntmdp2;

		/* Set numbers of buffers. */
		es->es_nrbufs = le_nrbufs;
		es->es_ntbufs = le_ntbufs;

		/*
		 * Allocate the message descriptor rings.
		 *	Force 8-byte alignment by allocating an extra
		 *	one and then rounding the starting address.
		 *	This code depends on message descriptors being
		 *	>= 8 bytes long.  (Bletch!)
		 */
#ifdef	DVMA_KLUGE
		es->es_rdrp = (struct le_md *)((u_long)le_falloc(
			sizeof(struct le_md) * (es->es_nrmds + 1),
			"Could not allocate receive message ring") & ~7) + 1;
		es->es_tdrp = (struct le_md *)((u_long)le_falloc(
			sizeof(struct le_md) * (es->es_ntmds + 1),
			"Could not allocate transmit message ring") & ~7) + 1;
#else	DVMA_KLUGE
#if	MACH
		es->es_rdrp = (struct le_md *) ((u_long) kmem_alloc(kernel_map,
			sizeof (struct le_md) * (es->es_nrmds+1)) & ~7, TRUE)
			+ 1;
		es->es_tdrp = (struct le_md *) ((u_long) kmem_alloc(kernel_map,
			sizeof (struct le_md) * (es->es_ntmds+1)) & ~7, TRUE)
			+ 1;
#else	MACH
		es->es_rdrp = (struct le_md *) ((u_long) kmem_alloc(
			sizeof (struct le_md) * (es->es_nrmds+1)) & ~7) + 1;
		es->es_tdrp = (struct le_md *) ((u_long) kmem_alloc(
			sizeof (struct le_md) * (es->es_ntmds+1)) & ~7) + 1;
#endif	MACH
#endif	DVMA_KLUGE
		/*
		 * Remember address of last descriptor in the ring for
		 * ease of bumping pointers around the ring.
		 */
		es->es_rdrend = &((es->es_rdrp)[es->es_nrmds-1]);
		es->es_tdrend = &((es->es_tdrp)[es->es_ntmds-1]);

		/* Allocate buffers. */
#ifdef	DVMA_KLUGE
		es->es_rbufs = (struct le_buf *)le_falloc(
				sizeof(struct le_buf) * es->es_nrbufs,
				"Could not allocate receive buffers");
		es->es_tbufs = (struct le_buf *)le_falloc(
				sizeof(struct le_buf) * es->es_ntbufs,
				"Could not allocate transmit buffers");
#else	DVMA_KLUGE
		es->es_rbufs = getstruct(struct le_buf , es->es_nrbufs);
		es->es_tbufs = getstruct(struct le_buf , es->es_ntbufs);
#endif	DVMA_KLUGE
	}
}

/*
 * Reset of interface after system reset.
 */
lereset(unit)
	int unit;
{
	register struct mb_device *md;

	if (unit >= NLE || (md = leinfo[unit]) == 0 || md->md_alive == 0)
		return;
	printf(" le%d", unit);
	leinit(unit);
}


/*
 * Initialization of interface; clear recorded pending
 * operations.
 */
leinit(unit)
	int unit;
{
	register struct le_softc *es = &le_softc[unit];
	register volatile struct le_device *le;
	register volatile struct le_init_block *ib;
	register int s;
	struct ifnet *ifp = &es->es_if;

	ifp->if_flags &= ~(IFF_UP | IFF_RUNNING);

	if (!address_known(ifp))
		return;

	s = splimp();

	/*
	 * Insure that resources are available.
	 *	(The first time through, this will allocate them.)
	 */
	le_alloc_buffers(es);

	le = (volatile struct le_device *)leinfo[unit]->md_addr;

	le->le_csr = LE_STOP;		/* reset the chip */

	/*
	 * Reset message descriptors.
	 */
	es->es_his_rmd = es->es_rdrp;
	es->es_cur_tmd = es->es_tdrend;
	es->es_nxt_tmd = es->es_tdrp;

	/* Initialize buffer allocation information. */

	/*
	 * Set up the receive buffer free list.
	 *	All receive buffers but those that are currently
	 *	loaned out go on it.
	 *
	 *	Note that this code relies on the integrity of
	 *	the loan-out list.
	 */
	{
		register int i;

		es->es_rbuf_free = (struct le_buf *)0;
		for (i = 0; i < es->es_nrbufs; i++) {
			register struct le_buf	*rb = &es->es_rbufs[i];

			if (le_onlist(&es->es_rbuf_loaned, rb))
				continue;
			free_rbuf(es, rb);
		}
	}

	/* Construct the initialization block */
	ib = es->es_ib;
	bzero((caddr_t)ib, sizeof (struct le_init_block));

	/*
	 * Mode word 0 should be all zeroes except
	 * possibly for the promiscuous mode bit.
	 */
	if (ifp->if_flags & IFF_PROMISC)
		ib->ib_prom = 1;

#ifdef	MACH
	ib->ib_padr[0] = es->es_enaddr[1];
	ib->ib_padr[1] = es->es_enaddr[0];
	ib->ib_padr[2] = es->es_enaddr[3];
	ib->ib_padr[3] = es->es_enaddr[2];
	ib->ib_padr[4] = es->es_enaddr[5];
	ib->ib_padr[5] = es->es_enaddr[4];
#else	MACH
	ib->ib_padr[0] = es->es_enaddr.ether_addr_octet[1];
	ib->ib_padr[1] = es->es_enaddr.ether_addr_octet[0];
	ib->ib_padr[2] = es->es_enaddr.ether_addr_octet[3];
	ib->ib_padr[3] = es->es_enaddr.ether_addr_octet[2];
	ib->ib_padr[4] = es->es_enaddr.ether_addr_octet[5];
	ib->ib_padr[5] = es->es_enaddr.ether_addr_octet[4];
#endif	MACH
						
	/* No multicast filter yet, FIXME MULTICAST, leave zeros. */

	ib->ib_rdrp.drp_laddr = (long)es->es_rdrp;
	ib->ib_rdrp.drp_haddr = (long)es->es_rdrp >> 16;
	ib->ib_rdrp.drp_len   = (long)es->es_nrmdp2;
	ib->ib_tdrp.drp_laddr = (long)es->es_tdrp;
	ib->ib_tdrp.drp_haddr = (long)es->es_tdrp >> 16;
	ib->ib_tdrp.drp_len   = (long)es->es_ntmdp2;

	/* Clear all the descriptors */
	bzero((caddr_t)es->es_rdrp, es->es_nrmds * sizeof (struct le_md));
	bzero((caddr_t)es->es_tdrp, es->es_ntmds * sizeof (struct le_md));

	/* Hang out the receive buffers. */
	{
		register struct le_buf *rb;

		while (rb = get_rbuf(es)) {
			register struct le_md *rmd = es->es_his_rmd;

			install_buf_in_rmd(rb, rmd);
			rmd->lmd_flags = LMD_OWN;
			es->es_his_rmd = next_rmd(es, rmd);
			if (es->es_his_rmd == es->es_rdrp)
				break;
		}
		/*
		 * Verify that all receive ring descriptor slots
		 * were filled.
		 */
		if (es->es_his_rmd != es->es_rdrp) {
			identify(&es->es_if);
			panic("leinitrbufs");
		}
	}

	/* Give the init block to the chip */
	le->le_rap = LE_CSR1;	/* select the low address register */
	le->le_rdp = (long)ib & 0xffff;

	le->le_rap = LE_CSR2;	/* select the high address register */
	le->le_rdp = ((long)ib >> 16) & 0xff;

	le->le_rap = LE_CSR3;	/* Bus Master control register */
	le->le_rdp = LE_BSWP;

	le->le_rap = LE_CSR0;	/* main control/status register */
	le->le_csr = LE_INIT;

	{
		int i;

		for (i = 10000; ! (le->le_csr & LE_IDON); i-- ) {
			if (i <= 0) {
				identify(&es->es_if);
				panic("chip didn't initialize");
			}
		}
	}
	le->le_csr = LE_IDON;		/* Now reset the interrupt */

	/*
	 * Clear software record of pending operations
	 * and clear pending timeouts.
	 */
	if (es->es_flags & LE_TBUSY) {
		if (es->es_tmbuf)
			m_freem(es->es_tmbuf);
		es->es_flags &= ~LE_TBUSY;
	}
	if (es->es_flags & LE_TOPENDING) {
		int	le_xmit_reset();

		untimeout(le_xmit_reset, (caddr_t) es);
		es->es_flags &= ~LE_TOPENDING;
	}

	/* (Re)start the chip. */
	le->le_csr = LE_STRT | LE_INEA;

	ifp->if_flags |= IFF_UP|IFF_RUNNING;
	if (ifp->if_snd.ifq_head)
		lestart(unit);

#ifdef	MACH
	/* remember old flag values */
	es->es_old_ifflags = es->es_if.if_flags;
#endif	MACH
	(void) splx(s);

#ifdef	MACH
	/* Don't need this for 4.3 BSD */
#else	MACH
	route_arp(ifp, &es->es_ac);
#endif	MACH

#if	DLI
	dli_init(&if_dlv[unit], ifp, es->es_enaddr, etherbroadcastaddr,
		 sizeof(etherbroadcastaddr), sizeof(struct ether_header));
#endif	DLI
}

/*
 * Set the receive descriptor rmd to refer to the buffer rb.
 *	Note that we don't give the descriptor/buffer pair
 *	back to the chip here, since our caller may not be
 *	ready to give it up yet.
 */
install_buf_in_rmd(rb, rmd)
	struct le_buf *rb;
	register struct le_md *rmd;
{
	/*
	 * Careful here -- the chip considers the buffer to start
	 * with an ether header, so we really have to point it at
	 * the lb_ehdr field of our buffer structure.
	 */
	register u_char *buffer = (u_char *) &rb->lb_ehdr;

	rmd->lmd_ladr = (u_short) buffer;
	rmd->lmd_hadr = (long)buffer >> 16;
	rmd->lmd_bcnt = -MAXBUF;
	rmd->lmd_mcnt = 0;
}

/*
 * Repossess a loaned-out receive buffer.
 *	Called from within MFREE by the loanee when disposing
 *	of the cluster-type mbuf wrapped around the buffer.
 *
 *	Assumes called with lists locked.
 */
leclfree(lbp)
	register struct le_buf	*lbp;
{
	register struct le_softc	*es;
	register struct le_buf		**predp;

	if (!lbp)
		panic("leclfree");

	es = lbp->lb_es;
	if (!es) {
		printf("lbp: %x\n", lbp);
		panic("leclfree2");
	}

	/*
	 * Transfer it from the loan-out list to the free list.
	 */
	predp = le_lpredp(&es->es_rbuf_loaned, lbp);
	if (!predp) {
		identify(&es->es_if);
		printf("lbp: %x, es: %x\n", lbp, es);
		panic("leclfree4");
	}
	*predp = lbp->lb_next;
	free_rbuf(es, lbp);
}

/*
 * Handle transmitter freeze-up by resetting the chip.
 *	This routine shouldn't be necessary, but the LANCE is still buggy.
 *	This code could be rewritten to eliminate the LE_TOPENDING flag,
 *	but retaining it makes it more obvious what's going on.
 */
le_xmit_reset(es)
	struct le_softc	*es;
{
	register int		s = splimp();
	volatile struct le_device	*le;

	/*
	 * The timeout occurred and therefore is no longer pending.
	 */
	es->es_flags &= ~LE_TOPENDING;

	le = (volatile struct le_device *) leinfo[es - le_softc]->md_addr;

	identify(&es->es_if);
	printf("transmitter frozen -- resetting\n");

	leinit(es - le_softc);

	(void) splx(s);
}

#ifdef	IF_CNTRS
extern int if_narp, if_arp;
extern int if_ein[32], if_eout[32]; 
extern int if_lin[128/8], if_lout[128/8]; 
int if_mchain_raw[20], if_mchain_overflowed;
#endif	IF_CNTRS
/*
 * Start or restart output on interface.
 * If interface is already active, then this is a nop.
 * If interface is not already active, get another packet
 * to send from the interface queue, and map it to the
 * interface before starting the output.
 */
lestart(dev)
	dev_t dev;
{
	int unit = minor(dev);
	struct le_softc *es = &le_softc[unit];
	volatile struct le_device *le;
	register struct le_md	*t,
				*t0;
	struct le_md		*tnext;
	u_char			*tbuf;
	register int		bcnt;
	register struct mbuf	*m,
				*mprev;
	int			cnt;
	int			len;
	extern struct mbuf	*ether_pullup();

	/*
	 * Check for transmit buffer busy.
	 */
	if (es->es_flags & LE_TBUSY)
		return;
	le = (volatile struct le_device *)leinfo[unit]->md_addr;

	/*
	 * FIXME BACK_TO_BACK: (Well, maybe not...)
	 * We may eventually want to pull as many packets as possible off
	 * the send queue and put them in the transmit descriptor ring
	 * for back-to-back transmission.  For now, however, we'll keep
	 * it simple and just send one transmit buffer at a time.
	 *
	 * In fact experience indicates that it's unprofitable to
	 * contemplate back-to-back transmission.  The frequency
	 * of arriving here with more than one packet to send turns
	 * out to be very low.  Moreover, supporting back-to-back
	 * transmission would make the code that avoids copying
	 * outgoing packet mbufs much more hairy.
	 */

	IF_DEQUEUE(&es->es_if.if_snd, m);
	if (m == (struct mbuf *) 0)
		return;

	/* Gather statistics. */
	es->es_started++;
	if (es->es_if.if_snd.ifq_len > 0)
		es->es_started2++;

	/* Set the ethernet source address because the hardware won't. */
#ifdef	MACH
	/*
	 * We will do this in if_subr:ether_output() so we can get
	 * DLI to work correctly.
	 */
#else	MACH
	mtod(m, struct ether_header *)->ether_shost = es->es_enaddr;
#endif	MACH

	/*
	 * Force the first buffer of the outgoing packet
	 * to be at least the minimum size the chip requires.
	 *	There's a potential inefficiency here.  If we end up
	 *	copying the entire packet into a transmit buffer after
	 *	having pulled up to the min TU, we'll have done a
	 *	redundant copy.  Add an additional check?
	 */
	es->es_pullups++;
	m = ether_pullup(m, LANCE_MIN_TU);
	if (m == (struct mbuf *) 0) {
		identify(&es->es_if);
		printf("out of mbufs: output packet dropped\n");
		return;
	}
	/*
	 * If the resulting length is still small, we know that
	 * the packet is entirely contained in the pulled-up
	 * mbuf.  In this case, we must insure that the packet's
	 * length is at least the Ethernet minimum transmission
	 * unit.  We can reach in and adjust the mbuf's size with
	 * impunity because: ether_pullup has returned us an mbuf
	 * whose data begins at the head of mbuf's data area (so
	 * that the entire mbuf is available), and the required size
	 * is less than the mbuf size.
	 */
	if (m->m_len < ETHER_MIN_TU)
		m->m_len = ETHER_MIN_TU;
	/*
	 * Record the address of the start of the packet's mbuf chain,
	 * so that we can free it after the chip's through with it.
	 *	N.B.: This scheme assumes there's at most one outgoing
	 *	packet transmission in progress at a time.  If this
	 *	assumption changes, this code will require nontrivial
	 *	modification.
	 */
	es->es_tmbuf = m;
	/*
	 * Wrap a transmit descriptor around each of the packet's
	 * mbufs.  Check for resource exhaustion and handle it by
	 * copying the remainder of the packet into a statically
	 * allocated transmit buffer, pointing the last tmd at it.
	 */
	mprev = (struct mbuf *) 0;
	t0 = t = es->es_cur_tmd = es->es_nxt_tmd;
	cnt = 0; len = 0;
	do {
		cnt++;
		tnext = next_tmd(es, t);

		if (tnext != t0 || ! m->m_next) {
			/* Normal case: use the mbuf itself as the buffer. */
			tbuf = mtod(m, u_char *);
			bcnt = m->m_len;
		}
		else {
			/*
			 * Resource exhaustion: copy the remainder,
			 * after breaking it off the mbuf chain
			 * leading to it.
			 */
			es->es_no_tmds++;
			if (mprev)
				mprev->m_next = (struct mbuf *) 0;
			else
				es->es_tmbuf = (struct mbuf *) 0;
			tbuf = (u_char *) &es->es_tbufs->lb_ehdr;
			bcnt = copy_from_mbufs (tbuf, m);
			m = (struct mbuf *) 0;
#ifdef	IF_CNTRS
			if_mchain_overflowed++;
#endif	IF_CNTRS
		}
		if (t->lmd_flags & LMD_OWN) {
			identify(&es->es_if);
			panic("lestart: tmd ownership conflict");
		}
		/*
		 * Point the tmd at the buffer.
		 */
		t->lmd_ladr = (u_short) tbuf;
		t->lmd_hadr = (int) tbuf >> 16;
		t->lmd_bcnt = -bcnt;
		t->lmd_flags3 = 0; 
		t->lmd_flags = 0;
		len += bcnt;
		t = tnext;
		mprev = m;
	} while (m && (m = m->m_next));
#ifdef	IF_CNTRS
	if_eout[if_log_2(len)]++;
	if (len < 128)  if_lout[len>>3]++;
	if_mchain_raw[cnt]++;
#endif	IF_CNTRS
	/*
	 * T and tnext now point to the first slot to be used
	 * for the next packet.
	 */
	es->es_nxt_tmd = t;

	/*
	 * Fire off the packet by giving each of its associated descriptors to
	 * the LANCE chip, setting the start- and end-of-packet flags as well.
	 *	We give the descriptors back in reverse order to prevent
	 *	race conditions with the chip.
	 */
	t0->lmd_flags = LMD_STP;
	prev_tmd(es,t)->lmd_flags |= LMD_ENP;
	do {
		t = prev_tmd(es, t);
		t->lmd_flags |= LMD_OWN;
	} while (t != t0);
	es->es_flags |= LE_TBUSY;

	le->le_csr = LE_TDMD | LE_INEA;

	/*
	 * Schedule a timeout to guard against transmitter freeze-up.
	 * This timeout is cancelled when we get the transmitter interrupt
	 * for this packet.  Eventually (when we get bug free parts) we
	 * should be able to remove it altogether.
	 */
	es->es_flags |= LE_TOPENDING;
	timeout(le_xmit_reset, (caddr_t) es, hz << 2);
}

/*
 * Ethernet interface interrupt.
 */
leintr()
{
	register struct le_softc *es;
	register volatile struct le_device *le;
	register struct le_md *lmd;
	register struct mb_device *md;
	register int unit;
	int serviced = 0;

	es = &le_softc[0];
	for (unit = 0; unit < NLE; unit++, es++) {
		if ((md = leinfo[unit]) == 0 || md->md_alive == 0)
			continue;
		le = (volatile struct le_device *)md->md_addr;

		if (!(le->le_csr & LE_INTR))
			continue;

		/* Keep statistics for lack of heartbeat */
		if (le->le_csr & LE_CERR) {
			le->le_csr = LE_CERR | LE_INEA;
			es->es_noheartbeat++;
		}

		/*
		 * The chip's internal (externally invisble) pointer
		 * always points to the rmd just after the last
		 * one that the software has taken from the chip.
		 * Es_his_rmd always points to the rmd just after the
		 * last one that was given to the chip.
		 */

/*
 * It is possible to omit the RINT test and to just check for
 * the OWN bit clear in the next rmd.  However, the RINT bit
 * provides a nice consistency check that should probably
 * stay in until the driver is stable.
 */
		/* Check for receive activity */
		if ( (le->le_csr & LE_RINT) && (le->le_csr & LE_RXON) ) {
			/* Pull packets off interface */
			for (lmd = es->es_his_rmd;
			     !(lmd->lmd_flags & LMD_OWN);
			     es->es_his_rmd = lmd = next_rmd(es, lmd)) {
				serviced = 1;

/*
 * We acknowledge the RINT inside the loop so that the own bit for the
 * next packet will be checked *after* RINT is acknowledged.  If we were
 * to acknowledge the RINT just once after the loop, a packet could come in
 * between the last test of the own bit and the time we do the RINT,
 * in which case we might not see the packet (because we cleared its
 * RINT indication but we did not see the own bit become clear).
 *
 * Race prevention: since the chip uses the order <clear own bit, set RINT>,
 * we must use the opposite order <clear RINT, set own bit>.
 */
				le->le_csr = LE_RINT | LE_INEA;

				leread(es, lmd);

				/*
				 * Give the descriptor and associated
				 * buffer back to the chip.
				 */
				lmd->lmd_mcnt = 0;
				lmd->lmd_flags = LMD_OWN;
			}
			if (!serviced) {
				/*
				 * This code isn't satisfactory -- we
				 * really should be able to handle cases
				 * where it turns out there's nothing
				 * to do.
				 */
				identify(&es->es_if);
#ifdef	DEBUG
				halt("RINT with buffer owned by chip");
#else	DEBUG
				panic("RINT with buffer owned by chip");
#endif	DEBUG
			}
		}

		/* Check for transmit activity */
		if ((le->le_csr & LE_TINT) && (le->le_csr & LE_TXON)) {
		    /*
		     * Check each of the packet's descriptors
		     * for errors.
		     */
		    lmd = es->es_cur_tmd;
		    do {
			/*
			 * Check for loss of descriptor synchronization with
			 * the LANCE chip.  Following a transmit error the chip
			 * immediately sets TINT and then clears the OWN bit
			 * for the remaining tmds of the packet, opening a
			 * small window where it can appear we've gotten out of
			 * sync.  Therefore we check again after delaying for
			 * a bit.
			 */
			if (lmd->lmd_flags & LMD_OWN) {
			    DELAY(1000);
			    if (lmd->lmd_flags & LMD_OWN) {
				printf("tmd=%x, flags=%x, chip=%x, csr=%x\n",
				    lmd, lmd->lmd_flags, le, le->le_csr);
				panic("TINT but buffer owned by LANCE");
			    }
			}

			/*
			 * Keep retry statistics.  Note that they don't result
			 * in aborted transmissions.  Since the chip duplicates
			 * this information into each descriptor for a packet,
			 * we check only the first.
			 */
			if (  (lmd->lmd_flags & (TMD_MORE | TMD_ONE))
			   && (lmd->lmd_flags & LMD_STP)
			   )
				es->es_retries++;

			/*
			 * These errors cause the packet to be aborted.  (What
			 * happens if the packet's aborted before the chip gets
			 * to its last descriptor?  Does the chip advance past
			 * the offending descriptor?)
			 */
			if (lmd->lmd_flags3 &
			    (TMD_BUFF|TMD_UFLO|TMD_LCOL|TMD_LCAR|TMD_RTRY)) {
				le_xmit_error(es, lmd->lmd_flags3, le);
				es->es_if.if_oerrors++;
			}
			lmd = next_tmd(es, lmd);
		    } while (lmd != es->es_nxt_tmd);

		    le->le_csr = LE_TINT | LE_INEA;
		    serviced = 1;
		    es->es_if.if_opackets++;

		    /*
		     * Free the mbuf chain associated with the
		     * packet that just completed transmission.
		     * Cancel the watchdog timeout.
		     */
		    if (es->es_flags & LE_TBUSY) {
			    if (es->es_tmbuf)
				    m_freem(es->es_tmbuf);
			    es->es_flags &= ~LE_TBUSY;
		    }
		    else {
			    identify(&es->es_if);
			    printf("stray transmitter interrupt\n");
		    }
		    if (es->es_flags & LE_TOPENDING) {
			    untimeout(le_xmit_reset, (caddr_t) es);
			    es->es_flags &= ~LE_TOPENDING;
		    }

		    /* Send more packets if there are any. */
		    if (es->es_if.if_snd.ifq_head)
			    lestart(unit);
		}

		/*
		 * Check for errors not specifically related
		 * to transmission or reception.
		 */
		if ( (le->le_csr & (LE_BABL|LE_MERR|LE_MISS|LE_TXON|LE_RXON))
		     != (LE_RXON|LE_TXON) ) {
			serviced = 1;
			le_chip_error(es, le);
		}
	}
	return (serviced);
}

/*
 * Move info from driver toward protocol interface
 */
leread(es, rmd)
	register struct le_softc *es;
	register struct le_md *rmd;
{
	register struct ether_header *header;
	register caddr_t buffer;
	register struct mbuf *m;
	register struct le_buf *rcvbp;
	struct le_buf *rplbp;
	int length;
	int off;

	es->es_if.if_ipackets++;

	/* Check for packet errors. */

	/*
	 * ! ENP is an error because we have allocated huge receive buffers.
	 * I.e., we don't do buffer chaining.
	 */
	if ((rmd->lmd_flags & ~RMD_OFLO) != (LMD_STP|LMD_ENP)) {
		le_rcv_error(es, rmd->lmd_flags);
		es->es_if.if_ierrors++;
		return;
	}

	/*
	 * Convert the buffer address embedded in the receive
	 * descriptor to the address of the le_buf structure
	 * containing the buffer.
	 */
	rcvbp = e_to_lb(le_buf_addr(rmd));
	/*
	 * Get input data length (minus crc), pointer to ethernet header,
	 * and address of data buffer.
	 */
	length = rmd->lmd_mcnt - 4;	/* subtract off trailing crc */
#ifdef	IF_CNTRS
	if_ein[if_log_2(length)]++;
	if (length < 128) if_lin[length>>3]++;
#endif	IF_CNTRS
	header = &rcvbp->lb_ehdr;
	buffer = (caddr_t) &rcvbp->lb_buffer[0];

	/*
	 * Check for unreported packet errors.  Revs C and D of the LANCE
	 * chip have a bug that can cause "random" bytes to be prepended
	 * to the start of the packet.  The work-around is to make sure
	 * that the Ethernet destination address in the packet matches
	 * our address.
	 */
#ifdef	MACH
/*
 * Ethernet address in 4.3 is stored as an array of bytes not a structure
 * containing only an array of bytes
 */
#define ether_addr_not_equal(a,b)	\
	(  ( *(long  *)(&(a)[0]) != \
	     *(long  *)(&(b)[0]) )  \
	|| ( *(short *)(&(a)[4]) != \
	     *(short *)(&(b)[4]) )  \
	)
#else	MACH
#define ether_addr_not_equal(a,b)	\
	(  ( *(long  *)(&(a).ether_addr_octet[0]) != \
	     *(long  *)(&(b).ether_addr_octet[0]) )  \
	|| ( *(short *)(&(a).ether_addr_octet[4]) != \
	     *(short *)(&(b).ether_addr_octet[4]) )  \
	)
#endif	MACH

	/*
	 * FIXME MULTICAST: this disallows multicast packet reception.
	 * The fix is either to check against the entire list of multicast
	 * addresses (which we don't even have a mechanism for setting
	 * right now), or to get chips that don't have this bug.
	 *
	 * Moreover, if we've gone into promiscuous mode, there's no
	 * way at all we can tell whether we've been hit by the bug.
	 * In this case, we must disable the check.
	 */
	if (ether_addr_not_equal(header->ether_dhost, es->es_enaddr) &&
	    ether_addr_not_equal(header->ether_dhost, etherbroadcastaddr) &&
	    ! (es->es_if.if_flags & IFF_PROMISC)) {
#ifdef	LEDEBUG
		identify(&es->es_if);
		printf("LANCE Rev C/D Extra Byte(s) bug; Packet dropped\n");
#endif	LEDEBUG
		es->es_extrabyte++;
		es->es_if.if_ierrors++;
		return;
	}

	if (check_trailer(header, buffer, &length, &off)) {
		identify(&es->es_if);
		printf("trailer error\n");
		es->es_if.if_ierrors++;
		return;
	}

	/* Check for runt packet */
	if (length == 0) {
		identify(&es->es_if);
		printf("runt packet\n");
		es->es_if.if_ierrors++;
		return;
	}

	/*
	 * Pull packet off interface.  Off is nonzero if packet
	 * has trailing header; copy_to_mbufs will then force this header
	 * information to be at the front, but we still have to drop
	 * the type and length which are at the front of any trailer data.
	 */
#ifdef	MACH
	/*
	 * Copy data from interface buffer into mbufs instead of using
	 * Sun's funny mbufs to just point at data.
	 */
	length -= sizeof (struct ether_header);
	m = copy_to_mbufs(buffer, length, off, &es->es_if);
	length += sizeof (struct ether_header);
#else	MACH
	/*
	 * Receive buffer loan-out:
	 *	We're willing to loan the buffer containing this
	 *	packet to the higher protocol layers provided that
	 *	the packet's big enough and doesn't have a trailer
	 *	and that we have a spare receive buffer to use as
	 *	a replacement for it.
	 *
	 * FIXME STATISTICS: keep track of current and maximum loan-out
	 * list length.
	 */
	if (length > MLEN && off == 0)
		es->es_potential_rloans++;
	/*
	 * If everything's go, wrap the receive buffer up
	 * in a cluster-type mbuf and make sure it worked.
	 */
	if (  length > MLEN && off == 0
	   && (rplbp = es->es_rbuf_free)
	   && (m = mclgetx(leclfree, (int) rcvbp, buffer, length, M_DONTWAIT))
	   ) {
		es->es_actual_rloans++;
		/*
		 * Link the receive buffer into the loan-out list
		 * and set its softc pointer.
		 */
		loan_rbuf(es, rcvbp);
		rcvbp->lb_es = es;
		/*
		 * Replace the newly loaned buffer and move the
		 * replacement out of the free list.
		 */
		install_buf_in_rmd(rplbp, rmd);
		es->es_rbuf_free = rplbp->lb_next;
	}
	else
		m = copy_to_mbufs(buffer, length, off);
#endif	MACH
	if (m == (struct mbuf *) 0)
		return;

	do_protocol(header, m, &es->es_ac, length);
}

leoutput(ifp, m0, dst)
	struct ifnet *ifp;
	struct mbuf *m0;
	struct sockaddr *dst;
{
	return (ether_output(ifp, m0, dst, lestart,
	                             &le_softc[ifp->if_unit].es_ac));
}

/*
 * Process an ioctl request.
 */
leioctl(ifp, cmd, data)
	register struct ifnet *ifp;
	int cmd;
	caddr_t data;
{
	register int			unit = ifp->if_unit;
	register struct le_softc	*es = &le_softc[unit];
	register int			error = 0;
	int				s = splimp();

	switch (cmd) {

#ifdef	MACH
	case SIOCSIFADDR:
		error = set_if_addr(ifp, data);
		break;

	case SIOCGIFADDR:
		bcopy((caddr_t) es->es_enaddr,
			(caddr_t) &((struct ifreq *)data)->ifr_addr.sa_data[0],
			sizeof (struct ether_addr));
		break;

	case SIOCGIFFLAGS:
		((struct ifreq *)data)->ifr_flags = ifp->if_flags;
		break;

	case SIOCSIFFLAGS:
	    {
		/*
		 * Set interface flags.  Possibilities are: bringing
		 * the interface up or down and setting it into or out
		 * of promiscuous mode.
		 */
		short flags = ((struct ifreq *)data)->ifr_flags;
		register int	up;
		register int	promisc;
		/*
		 * Our caller changes the flag values for us,
		 * THEN tells us he's done so.  We therefore
		 * have to keep our own copy of what the flags
		 * are.
		 */
		short old_flags = es->es_old_ifflags;

		up = flags & IFF_UP;
		promisc = flags & IFF_PROMISC;
		if (  up != (old_flags & IFF_UP)
		   || promisc != (old_flags & IFF_PROMISC)
		   ) {
			struct ifaddr	*ifa;

			/*
			 * To bring the interface down, we temporarily
			 * zap its address, so that leinit will decide
			 * it can't meaningfully be initialized.
			 */
			if (!up) {
				ifa = ifp->if_addrlist;
				bzero((caddr_t) &ifp->if_addrlist,
				    sizeof (ifp->if_addrlist));
			}

			leinit(unit);

			/*
			 * Restore the interface address and make
			 * sure that the interface flags are mutually
			 * consistent.
			 */
			if (!up)
				ifp->if_addrlist = ifa;
			if (ifp->if_flags & IFF_UP)
				ifp->if_flags |= IFF_RUNNING;
			else
				ifp->if_flags &= ~(IFF_RUNNING | IFF_PROMISC);

			if (promisc & ! (ifp->if_flags & IFF_PROMISC))
				error = ENETDOWN;

			/*
			 * Keep a copy of the flags for next time
			 */
			es->es_old_ifflags = ifp->if_flags;
		}
		break;
#ifdef	IF_CNTRS
	case SIOCCIFCNTRS:
		if (!suser()) {
			error = EPERM;
			break;
		}
		bzero((caddr_t)if_ein, sizeof (if_ein));
		bzero((caddr_t)if_eout, sizeof (if_eout));
		bzero((caddr_t)if_lin, sizeof (if_lin));
		bzero((caddr_t)if_lout, sizeof (if_lout));
		bzero((caddr_t)&if_arp, sizeof (int));
		bzero((caddr_t)if_mchain_raw, sizeof (if_mchain_raw));
		bzero((caddr_t)&if_mchain_overflowed, sizeof (int));
		break;
#endif	IF_CNTRS
	    }
#else	MACH
	case SIOCSIFADDR:
		error = set_if_addr(ifp, data, &es->es_enaddr);
		break;

	case SIOCGIFADDR:
		bcopy((caddr_t) &es->es_enaddr,
			(caddr_t) &((struct ifreq *)data)->ifr_addr.sa_data[0],
			sizeof (struct ether_addr));
		break;

	case SIOCGIFFLAGS:
		*(short *) data = ifp->if_flags;
		break;

	case SIOCSIFFLAGS:
	    {
		/*
		 * Set interface flags.  Possibilities are: bringing
		 * the interface up or down and setting it into or out
		 * of promiscuous mode.
		 */
		short		flags = *(short *) data;
		register int	up;
		register int	promisc;

		/*
		 * See whether anything needs to change.
		 */
		up = flags & IFF_UP;
		promisc = flags & IFF_PROMISC;
		if (  up != (ifp->if_flags & IFF_UP)
		   || promisc != (ifp->if_flags & IFF_PROMISC)
		   ) {
			struct sockaddr	sa;

			/*
			 * To bring the interface down, we temporarily
			 * zap its address, so that leinit will decide
			 * it can't meaningfully be initialized.
			 */
			if (!up) {
				sa = ifp->if_addr;
				bzero((caddr_t) &ifp->if_addr,
				    sizeof (ifp->if_addr));
			}

			/* Bring the new state into effect. */
			ifp->if_flags = flags;
			leinit(unit);

			/*
			 * Restore the interface address and make
			 * sure that the interface flags are mutually
			 * consistent.
			 */
			if (!up)
				ifp->if_addr = sa;
			if (ifp->if_flags & IFF_UP)
				ifp->if_flags |= IFF_RUNNING;
			else
				ifp->if_flags &= ~(IFF_RUNNING | IFF_PROMISC);

			if (promisc & ! (ifp->if_flags & IFF_PROMISC))
				error = ENETDOWN;
		}
		break;
	    }
#endif	MACH

	default:
		error = EINVAL;
	}

	(void) splx(s);

	return (error);
}

le_rcv_error(es, flags)
	struct le_softc *es;
	u_char flags;
{
	if (flags & RMD_FRAM)
		es->es_fram++;
	if (flags & RMD_CRC )
		es->es_crc++;
	if (flags & RMD_OFLO)
		es->es_oflo++;
	if (flags & RMD_BUFF) {
		identify(&es->es_if);
		printf("Receive buffer error - BUFF bit set in rmd\n");
	}
	if (!(flags & LMD_STP)) {
		identify(&es->es_if);
		printf("Received packet with STP bit in rmd cleared\n");
	}
	if (!(flags & LMD_ENP)) {
		identify(&es->es_if);
		printf("Received packet with ENP bit in rmd cleared\n");
	}
}

le_xmit_error(es, flags, le)
	struct le_softc *es;
	u_short flags;
	volatile struct le_device *le;
{
	/*
	 * The BUFF bit isn't valid if the RTRY bit is set.
	 */
	if ((flags & (TMD_BUFF | TMD_RTRY)) == TMD_BUFF) {
		identify(&es->es_if);
		printf("Transmit buffer error - BUFF bit set in tmd\n");
#ifdef	LEDEBUG
		le_print_csr(le->le_csr);
		le_print_tmd(es->es_cur_tmd);
#endif	LEDEBUG
	}
	if (flags & TMD_UFLO) {
		identify(&es->es_if);
		printf("Transmit underflow error\n");
		es->es_uflo++;
	}
	if (flags & TMD_LCOL) {
		identify(&es->es_if);
		printf("Transmit late collision - net problem?\n");
	}
	if (flags & TMD_LCAR) {
		identify(&es->es_if);
		printf("No carrier - transceiver cable problem?\n");
	}
	if (flags & TMD_RTRY) {
		identify(&es->es_if);
		printf("Transmit retried more than 16 times - net jammed\n");
	}
}

/* Handles errors that are reported in the chip's status register */
/* ARGSUSED */
le_chip_error(es, le)
	struct le_softc  *es;
	volatile struct le_device *le;
{
	register u_short	csr = le->le_csr;
	int restart = 0;

	if (csr & LE_MISS) {
		es->es_missed++;
#ifdef	LEDEBUG
		identify(&es->es_if);
		printf("missed packet\n");
#endif	
		le->le_csr = LE_MISS | LE_INEA;
	}

	if (csr & LE_BABL) {
	    identify(&es->es_if);
	    printf("Babble error - sent a packet longer than the maximum length\n");
	    le->le_csr = LE_BABL | LE_INEA;
	}
	/*
	 * If a memory error has occurred, both the transmitter
	 * and the receiver will have shut down.
	 */
	if (csr & LE_MERR) {
	    identify(&es->es_if);
	    printf("Memory Error!  Ethernet chip memory access timed out\n");
	    le->le_csr = LE_MERR | LE_INEA;
	}
	if ( !(csr & LE_RXON) ) {
	    identify(&es->es_if);
	    printf("Reception stopped\n");
	    restart++;
	}
	if ( !(csr & LE_TXON) ) {
	    identify(&es->es_if);
	    printf("Transmission stopped\n");
	    restart++;
	}
	if (restart) {
	    identify(&es->es_if);
	    le_print_csr(csr);
	    leinit(es - le_softc);
	}
}

/*
 * Print out a csr value in a nicely formatted way.
 */
le_print_csr (csr)
	register u_short	csr;
{
	printf("csr: %b\n", csr,
"\20\20ERR\17BABL\16CERR\15MISS\14MERR\13RINT\12TINT\11IDON\10INTR\7INEA\6RXON\5TXON\4TDMD\3STOP\2STRT\1INIT\n");
}


/*
 * Buffer manipulation routines.
 */

/*
 * Remove a receive buffer from the free list, returning a pointer to it.
 * Any free buffer will do.
 *
 *	Should this be done in-line for speed?
 *
 *	Perhaps should be generalized to grab the first entry of
 *	any of the buffer lists.
 */
struct le_buf *
get_rbuf(es)
	register struct le_softc *es;
{
	register struct le_buf *rb = es->es_rbuf_free;

	if (rb)
		es->es_rbuf_free = rb->lb_next;
	return (rb);
}

/*
 * Given a list rooted at *lpp, return the address of the pointer
 * leading to *ip or NULL if *ip isn't contained in the list.
 */
struct le_buf **
le_lpredp(lpp, ip)
	struct le_buf	**lpp;
	register struct le_buf	*ip;
{
	register struct le_buf	*trailp,
				*p;

	/* Special case for first entry on list. */
	if (!lpp || ((p = *lpp) == ip && ip))
		return (lpp);

	trailp = (struct le_buf *) 0;
	while (p) {
		if (p == ip)
			return (&trailp->lb_next);
		trailp = p;
		p = p->lb_next;
	}

	return ((struct le_buf **) 0);
}


#ifdef	LEDEBUG

/*
 * Debugging routines.
 */

le_plist(list, llen)
	struct le_buf	*list;
	register int	llen;
{
	register struct le_buf *p = list;

	do {
		printf("LEDEBUG: le_plist: 0x%x\n", p);
	} while (llen-- > 0 && (p = p->lb_next));
}

le_chkmbuf(m)
	register struct mbuf *m;
{
	while (m) {
		if ((m->m_type != 1 && m->m_type != 2) || m != dtom(m))
			panic("le_chkmbuf");
		m = m->m_next;
	}
}

/*
 * Print out a transmit message descriptor.
 */
le_print_tmd(t)
	register struct le_md	*t;
{
	printf("tmd: %x, count: %d, flags: %b, flags3: %b\n",
		t, t->lmd_bcnt, t->lmd_flags,
		"\20\10OWN\7ERR\5MORE\4ONE\3DEF\2STP\1ENP",
		t->lmd_flags3,
		"\20\20BUFF\17UFLO\15LCOL\14LCAR\13RTRY");
}
#endif	LEDEBUG

#endif	NLE > 0
