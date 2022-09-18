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
 * $Log:	if_ni.c,v $
 * Revision 2.7  89/03/09  22:27:19  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/26  10:54:29  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  88/12/19  02:55:44  mwyoung
 * 	Remove lots of lint.
 * 	[88/12/17            mwyoung]
 * 
 * Revision 2.4  88/11/21  16:59:52  rvb
 * 	IF_CNTRS says whether packet statistics are kept.  For now this
 * 	is always true iff MACH is true.
 * 	MACH_DEVICE (and DLI) turns on the special hack to let the
 * 	emulation guys read and write the raw ether.
 * 	[88/11/09            rvb]
 * 
 * Revision 2.3  88/10/11  13:04:59  rpd
 * 	counters ni_mchain_{raw,cooked}.
 * 	[88/09/28            rvb]
 * 
 * Revision 2.2  88/08/10  10:40:00  rvb
 * Replaced calls to pmap_kernel_addr with a table lookup. The
 * virtual address of bde buffers is stored in the table when
 * the bde's are allocated.  Also replaced memory allocation using
 * kmem_alloc (Ultrix) with zones.
 * Type out what the wrong initial state actually is.
 * 
 * 01-Mar-88  David Bohman (bohman) at Carnegie-Mellon University
 *	Modified ultrix driver to work with MACH.  Merged several
 *	support files into driver.
 *
 */

/*
 * if_ni.c
 */

#ifndef	lint
static char *sccsid = "@(#)if_ni.c	1.14	ULTRIX	3/31/87";
#endif	lint

/************************************************************************
 *									*
 *			Copyright (c) 1986 by				*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any  other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or  reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/

#include <ni.h>
#if	NNI > 0

#ifdef	MACH
#include <dli.h>
#include <mach_device.h>
#define IF_CNTRS	MACH
#endif	MACH

/*
 * 31-Mar-87  -- lp	
 *			Put apa back on a reset for decnet.
 * 06-Feb-87  -- lp
 *			Check return of ifproto_type to gaurantee that
 *			we dont jump to 0.
 * 28-Jan-87  -- lp
 *			Cleanup as LINT showed some extra
 *			variables.
 *
 * 12-Dec-86  -- lp	Post FT-v2.0. Added dpaddr, Bumped up 
 *			freeq0 allocation.
 *
 * 23-Oct-86  -- lp	Type 2 mbuf are forced to return on respq.
 *
 * 2-Sep-86   -- lp	Cleanup. Bugfix for long (improperly chained)
 *			packets.
 *
 * 7-Aug-86   -- lp	Removed some printf's ('I' baseline).
 *
 * 7-Jul-86   -- lp	Fixed a timing problem in niattach.
 *
 * 5-Jun-86   -- lp 	Fixed a little bug in reset code.
 *
 * 5-Jun-86   -- jaw 	changes to config.
 *
 * 22 May 86 -- bjg
 *	Include types.h and errlog.h for error logging.
 *
 * 21 May 86 -- lp
 *	Reworked sptdb routine to allow clear prior to setting. Bugfixes
 *	for decnet. Errlog for SUME errors.
 *
 * 08 May 86 -- lp
 *	Trailer packets work. General cleanup. Vaddr no longer saved
 *	in receive packets.
 *
 * 09 Apr 1986 -- lp
 * 	DEC AIE/NI ethernet driver
 *		By 
 * 	Larry Palmer (decvax!lp).
 *	(rev 40 or higher aie firmware needed)
 *
 */

#include <machine/pte.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/vmmac.h>
#include <sys/ioctl.h>
#include <sys/errno.h>

#include <net/if.h>
#include <net/netisr.h>
#include <net/route.h>

#ifdef	INET
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#endif

#ifdef	NS
#include <netns/ns.h>
#include <netns/ns_if.h>
#endif

#if	DLI
#include <net/dli_var.h>
struct dli_var ni_dlv[NNI];
#endif	DLI

#include <vax/cpu.h>
#include <vax/mtpr.h>
#include <vax/scb.h>
#include <vax/bi_node.h>
#include <vaxif/if_ni.h>
#include <vaxif/if_nireg.h>
#include <vaxif/if_uba.h>
#include <vm/vm_kern.h>
#include <kern/zalloc.h>

#define remqhi(q, cnt)     remqhi_ul(q, cnt)
#define insqti(el, q, cnt) insqti_ul(el, q, cnt)

/************************************************************/
/* debugging of core leak for ni zone512 ********************/
/************************************************************/

typedef struct nizone_t {
	char 		*ni_base;
	zone_t		ni_zone;
	int		*ni_inuse;
	int		ni_size;
	int 		ni_elm;
} *nizone_t;

int	packet_count = 0;

char *
nizalloc(x)
nizone_t x;
{
char *y;

	y = (char *) zalloc(x->ni_zone);
	x->ni_inuse[(y - x->ni_base) / x->ni_elm]++;
	return y;
}

nizfree(x, y)
nizone_t x;
char *y;
{
	x->ni_inuse[(y - x->ni_base) / x->ni_elm]--;
	zfree(x->ni_zone, y);
}

ni_recover_memory(x)
nizone_t x;
/*
 * Go through ni_inuse fields, nizfree'ing elements still out there.
 */
{
register int i;	
register int cnt = 0;
char *y;

	for (i=0 ; i<x->ni_size; i++) {
		if (x->ni_inuse[i]) {
			y = x->ni_base + i * x->ni_elm;
			x->ni_inuse[i]--;
			zfree(x->ni_zone, y);
			cnt++;
		}
	}

	if (cnt)
		printf("ni_recover: %s found %d cells\n",
			x->ni_zone->zone_name,
			cnt);
}

/************************************************************/

extern int	(*niintv[])();
struct	mbuf *niget();
int	niattach(), niintr(), niprobe();
int	niinit(),nioutput(),niioctl(),nireset(), ni_ignore;
struct ni niinfo[NNI];
u_char  ni_multi[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00};
u_char  ni_notset[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
u_short nistd[] = { 0 };
#define svtopte(x)	((unsigned long)pmap_pte(pmap_kernel(), (x)))
#define svtophy(x)	((unsigned long)pmap_extract(pmap_kernel(), (x)))
#define vaddr(y,table,base) ((table)[(((int)y-(int)(base))/sizeof(struct _bd))])

/*
 * Ethernet software status per interface.
 *
 * Each interface is referenced by a network interface structure,
 * ds_if, which the routing code uses to locate the interface.
 * This structure contains the output queue for the interface, its address, ...
 */
struct	ni_softc {
	struct	arpcom ds_ac;		/* Ethernet common part */
#define ds_if	ds_ac.ac_if		/* network-visible interface */
#define ds_addr	ds_ac.ac_enaddr		/* hardware Ethernet address */
	int	ds_flags;
	long	ds_devid;
	u_char  ds_multi[NMULTI][8];
	long	ds_muse[NMULTI];
	u_char  ds_dpaddr[6];
} ni_softc[NNI];

struct nizone_t  nizone512, /* nizone124, */ nizone52, nizone14;
int niarray512[ZONE512_SZ/512];
/*int niarray124[ZONE124_SZ/128];*/
int niarray52[ZONE52_SZ/64];
int niarray14[ZONE14_SZ/14];

struct _fqb static_fqb;
int hack_flag = 0;

int nidebug = 0;

ni_to_bi_attach(bi, node, unit, biv)
int bi, node, unit;
register struct bi_node *biv;
{
    register struct ni *pni;
    register struct _fqb *p_fqb;

    if (unit >= NNI)
	return (0);

    nizone512.ni_base = (char *)kmem_alloc(kernel_map, ZONE512_SZ);
    nizone512.ni_zone = zinit(512, ZONE512_SZ, ZONE512_SZ, FALSE, "ni nizone512");
    nizone512.ni_inuse = niarray512;
    nizone512.ni_elm = 512;
    nizone512.ni_size = ZONE512_SZ/512;
    zcram(nizone512.ni_zone, nizone512.ni_base, ZONE512_SZ);

#ifdef	notdef
    nizone124.ni_zone = kmem_alloc(kernel_map, ZONE124_SZ);
    nizone124.ni_zone = zinit(128, ZONE124_SZ, ZONE124_SZ, FALSE, "ni nizone124");
    nizone124.ni_inuse = niarray124;
    nizone124.ni_elm = 128;
    nizone124.ni_size = ZONE124_SZ/128;
    zcram(nizone124.ni_zone, nizone124.ni_zone, ZONE124_SZ);
#endif	notdef

    nizone52.ni_base = (char *)kmem_alloc(kernel_map,ZONE52_SZ);
    nizone52.ni_zone = zinit(NI_DQHEAD+NI_DGRLEN+12, ZONE52_SZ, ZONE52_SZ,
		FALSE,"ni nizone52");
    nizone52.ni_inuse = niarray52;
    nizone52.ni_elm = 64;
    nizone52.ni_size = ZONE52_SZ/64;
    zcram(nizone52.ni_zone, nizone52.ni_base, ZONE52_SZ);

    nizone14.ni_base = (char *)kmem_alloc(kernel_map, ZONE14_SZ);
    nizone14.ni_zone = zinit(sizeof(struct ether_header), ZONE14_SZ, ZONE14_SZ,
		FALSE,"ni nizone14");
    nizone14.ni_inuse = niarray14;
    nizone14.ni_elm = 14;
    nizone14.ni_size = ZONE14_SZ/14;
    zcram(nizone14.ni_zone, nizone14.ni_base, ZONE14_SZ);

    pni = &niinfo[unit];
    pni->ni_regs = (struct nidevice *) ((caddr_t)biv + NI_NI_ADDR);
    pni->unit = unit;
    pni->alive = 1;
/*    pni->ni_pqb = (VPPQB *) nizalloc(&nizone512);*/
    pni->ni_pqb = (VPPQB *) kmem_alloc(kernel_map, 512);

    pni->phys_pqb = svtophy(pni->ni_pqb);

    pni->ni_pqb->ni.piv.level = 1;

    pni->ni_pqb->ni.piv.vector =
    	((int *)(((caddr_t)&scb)+(bi*512)+(0x100|(node*4)))) -
	(int *)&scb.scb_stray;

    pni->ni_pqb->ni.piv.bi_node = biv->intrdes;
    pni->ni_pqb->ni.vpqb_base = (caddr_t)pni->ni_pqb;

    pni->ni_pqb->ni.spt_base = (unsigned long) mfpr(SBR);
    pni->ni_pqb->ni.spt_len = (long) mfpr(SLR);

    pni->ni_pqb->ni.gpt_base = (unsigned long) mfpr(SBR);
    pni->ni_pqb->ni.gpt_len = (long) mfpr(SLR);

    pni->ni_pqb->ni.func_mask = 0;
    pni->ni_pqb->ni.bvp_level = 1;

    pni->ni_pqb->ni.vfqb_base = (struct _fqb *)kmem_alloc(kernel_map, 512);

/* Setup buffer descriptor table */
    pni->ni_pqb->ni.bdt_base = (caddr_t)kmem_alloc(kernel_map,
    						   (NI_NBUF*(NI_NFREEQ-1)*
						    sizeof(struct _bd)));
    pni->ni_pqb->ni.bdt_len = NI_NBUF*(NI_NFREEQ-1);

    niinfo[unit].bde_base_addr = pni->ni_pqb->ni.bdt_base;
    
/* Set up free queue block */
    pni->ni_pqb->ni.num_freeq = NI_NFREEQ;
    p_fqb = (struct _fqb *)pni->ni_pqb->ni.vfqb_base;
    p_fqb->mfreeq_size = NI_MQSIZE;
    p_fqb->dfreeq_size = NI_DQSIZE;
    p_fqb->rfreeq_size = NI_DQHEAD+34;
    p_fqb->mfreeq.flink = p_fqb->mfreeq.blink = 0;
    p_fqb->dfreeq.flink = p_fqb->dfreeq.blink = 0;
    p_fqb->rfreeq.flink = p_fqb->rfreeq.blink = 0;

/* Init the queues */
    pni->ni_pqb->cmdq0.flink = pni->ni_pqb->cmdq0.blink = 0;
    pni->ni_pqb->rspq.flink = pni->ni_pqb->rspq.blink = 0;

/* Only use cmdq0 & respq */
    pni->ni_pqb->cmdq1.flink = pni->ni_pqb->cmdq1.blink = 0;
    pni->ni_pqb->cmdq2.flink = pni->ni_pqb->cmdq2.blink = 0;
    pni->ni_pqb->cmdq3.flink = pni->ni_pqb->cmdq3.blink = 0;

    *((int *)(((caddr_t)&scb)+(bi*512)+(0x100|(node*4)))) =
    			(int)scbentry(niintv[unit], SCB_ISTACK);

    niattach(pni);
    return (1);
}

/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.  We get the ethernet address here.
 * We initialize big mbuf storage for receives here.
 */
niattach(ni)
	struct ni *ni;
{
	register struct ni_softc *ds = &ni_softc[ni->unit];
	register struct ifnet *ifp = &ds->ds_if;
	int i=0;

	ds->ds_devid = 0;

	ifp->if_unit = ni->unit;
	ifp->if_name = "ni";
	ifp->if_mtu = ETHERMTU;
	ifp->if_flags |= IFF_BROADCAST;

	/* 
	 * Set ni to initialized state
	 */
	i=0;
	while((ni->ni_regs->ps&PS_STATEMASK) != PS_UNDEFINED) {
	    if(++i > 200) {
		printf("ni%d in wrong state: %x\n",
			ni->unit, ni->ni_regs->ps&PS_STATEMASK);
		return;
	    }
	    DELAY(100000);
	}

	DELAY(200000);
	ni->ni_regs->ps &= ~PS_OWN;
	ni->ni_regs->pc &= ~PC_OWN;

	/* Go to initialized state */
	ni->ni_regs->pc = ni->phys_pqb|PC_INIT|PC_OWN;
	DELAY(1000000);
	while((ni->ni_regs->pc&PC_OWN)) 
		;
	i=0;
	while((ni->ni_regs->ps&PS_INITIALIZED) == 0) {
		if(i++ > 15) {
			printf("ni%d Cannot initialize\n", ni->unit);
			return;
		} else 
			DELAY(1000000);
	}
	ni->ni_regs->ps &= ~PS_OWN;

	/*
	 * Fill the multicast address table with unused entries (broadcast
	 * address) so that we can always give the full table to the device
	 * and we don't have to worry about gaps.
	 */
	for(i=0; i<NMULTI; i++)
		bcopy(ni_multi, ds->ds_multi[i], 8);

	/* Since we cant free mbuf storage we only do this once! */
	for(i=NI_FREEQ_1; i<(NI_FREEQ_1+NI_FREEQ_2); i += NI_RBUF) {
		ni->mbuf_clusters[i+1] = (char *) m_clalloc(1, MPG_SPACE,
		M_DONTWAIT);
	}

	ifp->if_init = niinit;
	ifp->if_output = nioutput;
	ifp->if_ioctl = niioctl;
	ifp->if_reset = nireset;
	if_attach(ifp);
}

/*
 * Reset of interface after reset.
 */
nireset(unit)
	int unit;
{
	register struct ni *ni;
	register struct ni_softc *ds = &ni_softc[unit];
	register char *mem;
	register int i;
	struct ifnet *ifp = &ds->ds_if;

	if (unit >= NNI || (ni = &niinfo[unit]) == 0 || ni->alive == 0)
		return(0);
	printf("reset ni%d %x %x %x %x\n", unit, ni->ni_regs->pc,
		ni->ni_regs->ps, ni->ni_regs->pe, ni->ni_regs->pd);
	if((ni->ni_regs->ps&PS_STATEMASK) != PS_ENABLED) {
	/* Eat freeq 2 */
		while((mem = (char *)remqhi(&ni->freeq2, NI_MAXITRY)) != (char *)QEMPTY) {
			struct _bd *bde = (struct _bd *)ni->ni_pqb->ni.bdt_base;
			bde += ((struct ni_data *)mem)->cbufs[0].bdt_index;
			for(i=0; i<NI_RBUF; bde++, i++) {
			    if (i == 0)
			        nizfree(&nizone14,vaddr(bde,ni->bde_virtual,
				    ni->bde_base_addr));
			    else if (i == 2)
				nizfree(&nizone512,vaddr(bde,ni->bde_virtual,
				    ni->bde_base_addr));
			}
			nizfree(&nizone52,mem);
		}
	/* Eat freeq0 & freeq1 */
		while((mem = (char *)remqhi(&ni->freeq0, NI_MAXITRY)) != (char *)QEMPTY)
		{
/*			nizfree(&nizone124,mem);*/
			nizfree(&nizone512,mem);
		}
		while((mem = (char *)remqhi(&ni->freeq1, NI_MAXITRY)) != (char *)QEMPTY)
		{
/*			nizfree(&nizone124,mem);*/
			nizfree(&nizone512,mem);
		}

	/* Eat the respq */
		while((mem = (char *)remqhi(&ni->respq, NI_MAXITRY)) != (char *)QEMPTY) {
			if(((struct ni_data *)mem)->opcode == DGREC) {
			struct _bd *bde = (struct _bd *)ni->ni_pqb->ni.bdt_base;
			bde += ((struct ni_data *)mem)->cbufs[0].bdt_index;
			for(i=0; i<NI_RBUF; bde++, i++) {
				if (i == 0)
				    nizfree(&nizone14,vaddr(bde,ni->bde_virtual,
					ni->bde_base_addr));
				else if (i == 2)
				    nizfree(&nizone512,vaddr(bde,ni->bde_virtual,
					ni->bde_base_addr));
			}
			nizfree(&nizone52,mem);
			} else if(((struct ni_data *)mem)->opcode == SNDDG) {
			if (*( (int *) ( (int) mem + 124 ) ) != 321 )
				panic("NI: wrong magic number\n");
/*				nizfree(&nizone124,mem);*/
				nizfree(&nizone512,mem);
			} else {
/*				nizfree(&nizone124,mem);*/
				nizfree(&nizone512,mem);
			}
		}
			
		ni_recover_memory(&nizone512);
/*		ni_recover_memory(&nizone124);*/
		ni_recover_memory(&nizone52);
		ni_recover_memory(&nizone14);

		if((ni->ni_regs->ps&PS_STATEMASK) == PS_STOPPED) {
			ni->ni_regs->ps &= ~PS_OWN;
			ni->ni_regs->pc = PC_RESTART|PC_OWN;
			DELAY(1000000);
			while((ni->ni_regs->pc&PC_OWN)) 
				;
		}
		ni->ni_regs->ps &= ~PS_OWN;
		/* 
	 	* Set ni to initialized state
	 	*/
		i=0;
		while((ni->ni_regs->ps&PS_STATEMASK) != PS_UNDEFINED) {
	    		if(++i > 200) {
				printf("ni%d in wrong state: %x\n",
					ni->unit, ni->ni_regs->ps&PS_STATEMASK);
				return(0);
		    	}
	    		DELAY(100000);
		}
		ni->ni_regs->ps &= ~PS_OWN;
		/* Go to initialized state */
		ni->ni_regs->pc = ni->phys_pqb|PC_INIT|PC_OWN;
		DELAY(100000);
		while((ni->ni_regs->pc&PC_OWN)) 
			;
		if((ni->ni_regs->ps&PS_INITIALIZED) == 0) {
			printf("ni%d Cannot initialize\n", ni->unit);
			return(0);
		}
		ni->ni_regs->ps &= ~PS_OWN;
		ni->ni_regs->pe = 0;
		ni->ni_regs->pd = 0;
		ifp->if_flags &= ~(IFF_RUNNING);

		untimeout(niinit, unit);
		timeout(niinit, unit, 1);
		return(0);
	}
	return(1);
}

/*
 * Initialization of interface; clear recorded pending
 * operations.
 */
niinit(unit)
	int unit;
{
	register struct ni_softc *ds = &ni_softc[unit];
	register struct ni *ni = &niinfo[unit];
	register struct nidevice *addr;
	struct ifnet *ifp = &ds->ds_if;
	int s,i,empty;

	/* not yet, if address still unknown */
	/* DECnet must set this somewhere to make device happy */

	if (ifp->if_addrlist == (struct ifaddr *)0)
			return;
	if (ifp->if_flags & IFF_RUNNING)
		return;

	/* 
	 * Set ni to enabled state. Still dont have freeq ready.
	 */

	addr = (struct nidevice *)ni->ni_regs;
	while((addr->pc&PC_OWN))
		;
	addr->pc = PC_ENABLE|PC_OWN;
	/* Should interrupt here */
	while((addr->pc&PC_OWN))
		;
	while((addr->ps&PS_OWN))
		;
	i = 0;
	while((addr->ps&PS_STATEMASK) != PS_ENABLED) {
		if(i++ > 500000) {
			printf("ni%d Cannot enable\n", ni->unit);
			return;
		}
	}
	addr->ps &= ~PS_OWN;

	/* 
	 * Setup message freeq Just a few so its not empty 
	 */
	{
		struct ni_msg *ni_msg;

		for(i=0; i<6; i++) {
			ni_msg = (struct ni_msg *) nizalloc(&nizone512);
			bzero(ni_msg,124);
			if((empty=insqti(ni_msg, &ni->freeq0, NI_MAXITRY)) > 0)
				printf("insqti failed\n");
			else if(empty == QEMPTY) {
				while((addr->pc&PC_OWN))
					;
				addr->pc = PC_FREEQNE|PC_MFREEQ|PC_OWN;
				while((addr->pc&PC_OWN))
					;
			}
		}
	}
	/* Setup xmit buffers (empty) */
	for(i=0; i<NI_FREEQ_1; i += NI_NUMBUF) {
		struct ni_data *ni_data;
		struct _bd *bde;
		int j;

/*		ni_data = (struct ni_data *) nizalloc(&nizone124);*/
		ni_data = (struct ni_data *) nizalloc(&nizone512);
		ni_data->status = 0;
		ni_data->dg_len = NI_DQSIZE-NI_DQHEAD;
		ni_data->dg_ptdb_index = 1;
		ni_data->opcode = SNDDG;
		for(j=0; j<NI_NUMBUF; j++) {	
			ni_data->cbufs[j].offset = 0;
			ni_data->cbufs[j].buffer_key = 1;	
			bde = (struct _bd *) ni->ni_pqb->ni.bdt_base;
			bde += i+j;
			bde->key = 1;
			bde->valid = 0;
			ni_data->cbufs[j].bdt_index = i+j;
		}
		if((empty=insqti(ni_data, &ni->freeq1, NI_MAXITRY)) > 0)
			printf("xmit insqti failed %d\n", i);
		else if(empty == QEMPTY) {
			while((addr->pc&PC_OWN))
				;
			addr->pc =  PC_FREEQNE|PC_DFREEQ|PC_OWN;
			while((addr->pc&PC_OWN))
				;
		}
	}
	/*
	 * Setup recv buffers 
	 */	
	/* Note that these have mbuf data areas associated */
	for(i=NI_FREEQ_1; i<(NI_FREEQ_1+NI_FREEQ_2); i += NI_RBUF) {
		struct ni_data *ni_data;
	  	struct _bd *bde;
	  	char *buffer;
		int j=0;

		ni_data = (struct ni_data *) nizalloc(&nizone52);
		if (ni_data == NULL) {
			panic("NI: &nizone52 exhausted\n");
		}

		/* header + space for DGRLEN buffer names */
		ni_data->dg_len = NI_DGRLEN;
		ni_data->opcode = DGREC;
		ni_data->dg_ptdb_index = 2;
		for(j=0; j<NI_RBUF; j++) {
			bde = (struct _bd *) ni->ni_pqb->ni.bdt_base;
			bde += i+j;
	/* Need to have 1st buffer be ether_header */
			if(j == 0) {
				buffer = (char *) nizalloc(&nizone14);
				bde->buf_len = sizeof(struct ether_header);
				bde->pt_addr = svtopte(buffer);
				bde->offset = (unsigned)buffer&PGOFSET;
			} else if( j == 1) {
				buffer = (char *)ni->mbuf_clusters[i+j];
				bde->pt_addr = svtopte(buffer);
				bde->offset = (unsigned)buffer&PGOFSET;
				bde->buf_len = NI_MAXPACKETSZ;
			} else {
				buffer = (char *) nizalloc(&nizone512);
				bde->buf_len = 512;
				bde->pt_addr = svtopte(buffer);
				bde->offset = (unsigned)buffer&PGOFSET;
			}
			ni->bde_virtual[(((int)bde-
			    (int)ni->bde_base_addr)/
			    sizeof(struct _bd))] = buffer;
			bde->key = 1;
			bde->valid = 1;
			ni_data->cbufs[j].offset = 0;
			ni_data->cbufs[j].s_len = bde->buf_len;
			ni_data->cbufs[j].bdt_index = i+j;
			ni_data->cbufs[j].buffer_key = 1;
		}
		if((empty=insqti(ni_data, &ni->freeq2, NI_MAXITRY)) > 0)
			printf("recv insqti failed %d\n", i);
		else if(empty == QEMPTY) {
			while((addr->pc&PC_OWN))
				;
			addr->pc = PC_FREEQNE|PC_RFREEQ|PC_OWN;
			while((addr->pc&PC_OWN))
				;
		}
	}
	while((addr->ps&PS_OWN))
		;
	/* Write Parameters */
	{
		struct ni_msg *ni_msg;

		ni_msg = (struct ni_msg *) nizalloc(&nizone512);
		if (ni_msg == NULL) {
			panic("NI: ni_msg is NULL\n");
		}
		bzero(ni_msg,124);
		* ((int *)(ni_msg+124)) = 5555; 	/* XXX debug */

		ni_msg->opcode = SNDMSG;
		ni_msg->status = 0;
		ni_msg->msg_len = sizeof(struct ni_param) + 6;
		ni_msg->ni_opcode = NIOP_WPARAM;

		/* Someone has set the apa at least once */
		if((bcmp(ds->ds_addr, ni_notset, 6) != 0))
		bcopy(ds->ds_addr,((struct ni_param *)&ni_msg->text[0])->apa, 6);
		((struct ni_param *)&ni_msg->text[0])->flags = NI_PAD;
		if((empty=insqti(ni_msg, &ni->comq0, NI_MAXITRY)) > 0)
			printf("insqti failed\n");
		else if(empty == QEMPTY) {
			while((addr->pc&PC_OWN))
				; 
			addr->pc = PC_CMDQNE|PC_CMDQ0|PC_OWN;
			while((addr->pc&PC_OWN))
				; 
		}
	}
	{
		struct ni_msg *ni_msg;

		ni_msg = (struct ni_msg *) nizalloc(&nizone512);
		if (ni_msg == NULL) {
			panic("NI: ni_msg is NULL\n");
		}
		bzero(ni_msg,124);
		* ((int *)(ni_msg+124)) = 5555;	/* XXX debug */

		ni_msg->opcode = SNDMSG;
		ni_msg->status = 0;
		ni_msg->msg_len = sizeof(struct ni_param) + 6;
		ni_msg->ni_opcode = NIOP_RCCNTR;
		if((empty=insqti(ni_msg, &ni->comq0, NI_MAXITRY)) > 0)
			printf("insqti failed\n");
		else if(empty == QEMPTY) {
			while((addr->pc&PC_OWN))
				; 
			addr->pc = PC_CMDQNE|PC_CMDQ0|PC_OWN;
			while((addr->pc&PC_OWN))
				; 
		}
	}
	/* Let all these commands complete */
	while((addr->ps & PS_OWN))
		;
	/* Hardware address not set yet */
	while((bcmp(ds->ds_addr, ni_notset, 6) == 0))
		;
	/* Set up PTDB's */
	ni_sptdb(ni,0,1,1,0,1);	/* #1 for send queue returns */
	ni_sptdb(ni,ETHERTYPE_IP,2,2,PTDB_UNK|PTDB_BDC,1); /* #2 all incoming */
	/* The board is up (ooo rah) */
	s = splimp();
	ds->ds_if.if_flags |= IFF_UP|IFF_RUNNING;
	nistart(unit);				/* queue output packets */
	splx(s);
#if	DLI
	dli_init(&ni_dlv[ifp->if_unit], ifp, ds->ds_addr, etherbroadcastaddr,
		 sizeof(etherbroadcastaddr), sizeof(struct ether_header));
#endif	DLI
}

#ifdef	IF_CNTRS
int ni_narp = 1, ni_arp = 0;
int ni_ein[32], ni_eout[32]; 
int ni_lin[128/8], ni_lout[128/8]; 
int ni_mchain_raw[20];
int ni_mchain_cooked[20];
static
log_2(i)
{
#ifndef	lint
	register int no = i;	/* Required for assembly language hackery below */
#endif	lint
	register int ffs = -1;
	register int offs;

#ifdef	lint
	i++;
#endif	lint

	while (ffs < 33) {
		offs = ffs;
		ffs++;
		asm("ffs r10, $32, r11, r10");
	}
	return (offs);
}
#endif	IF_CNTRS
/*
 * Setup output on interface.
 */
nistart(unit)
	int unit;
{
	register struct ni *ni = &niinfo[unit];
	register struct mbuf *m, *n;
	register struct _bd *bde;
	register struct ni_data *nid;
	register int len, curindex;
	struct mbuf *m_compress();
	struct ni_softc *ds = &ni_softc[unit];
	struct nidevice *addr = (struct nidevice *)ni->ni_regs;
        int empty;


	if((addr->ps&PS_STATEMASK) != PS_ENABLED) {
		printf("ni%d state(nistart) %x %x %x %x\n", unit, addr->ps, 
			addr->pe, addr->pc, addr->pd);
		if((addr->ps&PS_STATEMASK) == PS_UNDEFINED ||
		   (addr->ps&PS_STATEMASK) == PS_STOPPED)
			nireset(unit);
	}
#if	0
/************************************************************/
	if (++packet_count == 5000) {
		printf("ni%d state(nistart) extra-debugging reset\n", unit);
		packet_count = 0;
		nireset(unit);
	}
/************************************************************/
#endif	0
	for(;;) {
		IF_DEQUEUE(&ds->ds_if.if_snd, m);
		if(m == 0)
			break;
		if((nid = (struct ni_data *)remqhi(&ni->freeq1, NI_MAXITRY))
			== (struct ni_data *)QEMPTY) {
			goto drop;
		}
		if(nid->mbuf_tofree) { /* Free last mbuf sent */
			m_freem((struct mbuf *)nid->mbuf_tofree);
			nid->mbuf_tofree = 0;
		}
		/* force a match on broadcasts */
		if((bcmp(mtod(m, struct ether_header *), ni_multi, 6) == 0))
			nid->R = 1;
		else
			nid->R = 0;

		for(n = m,curindex = 0; n; n = n->m_next) {
			curindex++;
#ifdef	notdef
			if(n->m_cltype == 2)
				nid->R = 1;
#endif	notdef
		}
#ifdef	IF_CNTRS
		ni_mchain_raw[curindex]++;
#endif	IF_CNTRS
		if(curindex >= NI_NUMBUF) {
			n = m;
			m = m_compress(n);
		}

		bde = (struct _bd *) ni->ni_pqb->ni.bdt_base;
		bde += nid->cbufs[0].bdt_index;

		nid->mbuf_tofree = (unsigned long)m;

		for(len=0, curindex=0;m; m = m->m_next,bde++) {
			bde->offset = mtod(m, unsigned)&PGOFSET;
			bde->pt_addr = svtopte(mtod(m, char *));
				ni->bde_virtual[(((int)bde-
				    (int)ni->bde_base_addr)/
				    sizeof(struct _bd))] = mtod(m, char *);
			bde->buf_len = m->m_len;
			bde->valid = 1;
			nid->cbufs[curindex].offset = 0;
			nid->cbufs[curindex].s_len = bde->buf_len;
			nid->cbufs[curindex].chain = 1;
			len += m->m_len;
			curindex++;
		}
#ifdef	IF_CNTRS
		ni_mchain_cooked[curindex]++;
		ni_eout[log_2(len)]++;
		if (len < 128)  ni_lout[len>>3]++;
#endif	IF_CNTRS
		if(len < 64) { /* Last buffer may get something tacked on */
			(--bde)->buf_len += 64 - len;
			nid->cbufs[curindex-1].s_len += 64 - len;
		}
		nid->opcode = SNDDG;
		nid->status = 0;
		nid->dg_ptdb_index = 1;
		nid->dg_len = 10 + curindex*8;
		nid->cbufs[--curindex].chain = 0;
		ds->ds_if.if_opackets++;
		if((empty=insqti(nid, &ni->comq0, NI_MAXITRY)) > 0)
			printf("insqti failed\n");
		else if(empty == QEMPTY) {
			while((addr->pc&PC_OWN))
				;
			addr->pc =  PC_CMDQNE|PC_CMDQ0|PC_OWN;
		} 
	}
	return;
drop: 
	IF_ENQUEUE(&ds->ds_if.if_snd, m);
}

/*
 * Command done interrupt.
 */
niintr(unit)
	register int unit;
{
	register struct ni *ni = &niinfo[unit];
	register struct nidevice *addr = (struct nidevice *)ni->ni_regs;

retry:
#ifdef	NIDEBUG
	if (addr->ps&0x02000000) {
		printf("NI debug:  Free queue exhausted!!!\n");
	}
#endif	NIDEBUG
	if((addr->ps&PS_STATEMASK) != PS_ENABLED) {
		if((addr->ps&PS_STATEMASK) == PS_UNDEFINED ||
		   (addr->ps&PS_STATEMASK) == PS_STOPPED)
			nireset(unit);
		addr->ps &= ~PS_SUME;
		goto done;
	}

	/*
	 * Check for incoming packets.
	 */
		if(addr->ps&PS_RSQ) {
			nirecv(unit);
		}
	/*
	 * Check for outgoing packets.
	 */
		{
		int s = splimp();
			nistart(unit);
		splx(s);
		}
done:
	if(addr->ps & PS_SUME) {
#ifdef	notdef
		register struct el_rec *elrp;

		if((elrp = ealloc(sizeof(struct el_bvp), EL_PRILOW))) {
		register struct el_bvp *elbod;
		struct biic_regs *nxv;
		elbod = &elrp->el_body.elbvp;
		nxv = (struct biic_regs *)
			((char *)(ni->ni_regs) - NI_NI_ADDR);
		elbod->bvp_biic_typ = nxv->biic_typ;
		elbod->bvp_biic_csr = nxv->biic_ctrl;
		elbod->bvp_pcntl = addr->pc;
		elbod->bvp_pstatus = addr->ps;
		elbod->bvp_perr = addr->pe;
		elbod->bvp_pdata = addr->pd;
		LSUBID(elrp,ELCT_DCNTL,ELBI_BVP,ELBVP_AIE,
			ni->ni_pqb->ni.piv.bi_node,unit,addr->pe);
		EVALID(elrp);
		}
#endif	notdef
		if((addr->ps&PS_STATEMASK) == PS_UNDEFINED ||
		   (addr->ps&PS_STATEMASK) == PS_STOPPED)
		goto retry;
	}
		
	addr->ps &= ~(PS_OWN|PS_SUME|PS_RSQ);

}

/*
 * Ethernet interface receiver interface.
 */

nirecv(unit)
	int unit;
{
	register struct ni *ni = &niinfo[unit];
	register struct ni_data *nid;
	register struct nidevice *addr = (struct nidevice *)ni->ni_regs;
	register struct ni_softc *ds = &ni_softc[unit];
	int len, empty;
	struct _bd *bde;

	/* First guess is that its a data gram recieve */
	
	for(;;) {
	if((nid = (struct ni_data *)remqhi(&ni->respq, NI_MAXITRY)) 
		>= (struct ni_data *)QEMPTY) 
		break;
#ifdef	notdef
		if(nid->status&PCK_FAIL) {
			register struct el_rec *elrp;

			if((elrp = ealloc(sizeof(struct el_bvp), EL_PRILOW))) {
			register struct el_bvp *elbod;
			struct biic_regs *nxv;
			elbod = &elrp->el_body.elbvp;
			nxv = (struct biic_regs *)
				((char *)(ni->ni_regs) - NI_NI_ADDR);
			elbod->bvp_biic_typ = nxv->biic_typ;
			elbod->bvp_biic_csr = nxv->biic_ctrl;
			elbod->bvp_pcntl = addr->pc;
			elbod->bvp_pstatus = addr->ps;
			elbod->bvp_perr = addr->pe;
			elbod->bvp_pdata = addr->pd;
			LSUBID(elrp,ELCT_DCNTL,ELBI_BVP,ELBVP_AIE,
				ni->ni_pqb->ni.piv.bi_node,unit,nid->status);
			EVALID(elrp);
			}
		}
#endif	notdef
		switch(nid->opcode) {
		case DGIREC:
		case DGISNT:
			break;
		case DGREC:
			ds->ds_if.if_ipackets++;
			bde = (struct _bd *) ni->ni_pqb->ni.bdt_base;
			bde += nid->cbufs[0].bdt_index;
			if(nid->status&PCK_FAIL)
				ds->ds_if.if_ierrors++;
			len = -4;		/* to flush crc */
			/* Walk buffers & add length */
			{ register int curindex = 0;
			  register struct _bd *pbde = bde;
			while(curindex < NI_RBUF ) {
				len += nid->cbufs[curindex].s_len;
				nid->cbufs[curindex].s_len = pbde++->buf_len;
				if(nid->cbufs[curindex].chain == 0)
					break;
				curindex++;
			}
			}
#ifdef	IF_CNTRS
			ni_ein[log_2(len)]++;
			if (len < 128) ni_lin[len>>3]++;
#endif	IF_CNTRS
			niread(ni, ds, bde, len, 0);
			nid->opcode=DGREC;
			nid->dg_len = NI_DGRLEN;
			nid->status=0;
	/* DGREC must end up on freeq2 */
			if((empty=insqti(nid, &ni->freeq2, NI_MAXITRY)) > 0)
				printf("insqti failed\n");
			else if(empty == QEMPTY) {
				while((addr->pc&PC_OWN))
					;
				addr->pc =  PC_FREEQNE|PC_RFREEQ|PC_OWN;
			}
			break;

		case DGSNT:
	/* DGSNT must end up on freeq1 */
			if(nid->status&PCK_FAIL)
				ds->ds_if.if_oerrors++;
			else {
#ifdef	notdef
			struct mbuf *n, *m = (struct mbuf *)nid->mbuf_tofree;
#else	notdef
			struct mbuf *m = (struct mbuf *)nid->mbuf_tofree;
#endif	notdef

#ifdef	notdef
			for(n = m; n; n = n->m_next)
				if(n->m_cltype == 2) { /* Stupid nfs */
					m_freem(m);
					goto cnt;
				}
#endif	notdef
			/* else A loopback */
				niread(ni, ds, 0, 64, m);
			}
#ifdef	notdef
cnt:
#endif	notdef
			nid->mbuf_tofree = 0;
			if((empty=insqti(nid, &ni->freeq1, NI_MAXITRY)) > 0)
				printf("insqti failed\n");
			else if(empty == QEMPTY) {
				while((addr->pc&PC_OWN))
					;
				addr->pc =  PC_FREEQNE|PC_DFREEQ|PC_OWN;
			}
			break;
		case MSGSNT:
		case MSGREC:
			{ 
			struct ni_msg *ni_msg;
			ni_msg = (struct ni_msg *)nid;
			switch(ni_msg->ni_opcode) {
				case NIOP_WPARAM:
				case NIOP_RPARAM:
				bcopy(((struct ni_param *)&ni_msg->text[0])->apa, ds->ds_addr, 6);
				bcopy(((struct ni_param *)&ni_msg->text[0])->dpa, ds->ds_dpaddr, 6);
					break;
				case NIOP_RCCNTR:
				case NIOP_RDCNTR:
				/* User may be waiting for info to come back */
					wakeup((caddr_t)ni_msg);
					break;
				case NIOP_STPTDB:
				case NIOP_CLPTDB:
				default:
					break;
			}
	/* MSGSNT must end up on freeq0 */
			if((empty=insqti(ni_msg, &ni->freeq0, NI_MAXITRY))>0)
				printf("insqti failed\n");
			else if(empty == QEMPTY) {
				while((addr->pc&PC_OWN))
					;
				addr->pc = PC_FREEQNE|PC_MFREEQ|PC_OWN;
			}
			}
			break;
		default:
			printf("ni%d unknown respq opcode\n", unit);
			if((empty=insqti(nid, &ni->freeq0, NI_MAXITRY))>0)
				printf("insqti failed\n");
			else if(empty == QEMPTY) {
				while((addr->pc&PC_OWN))
					;
				addr->pc = PC_FREEQNE|PC_MFREEQ|PC_OWN;
			}
			break;
		}
	}	
}
#if	MACH_DEVICE
extern char dli_from[6];
extern char dli_all[6];
extern int dli_active;
#endif	MACH_DEVICE
/*
 * Pass a packet to the higher levels.
 * We deal with the trailer protocol here.
 */
niread(ni, ds, bde, len, swloop)
	struct ni *ni;
	register struct ni_softc *ds;
	register struct _bd *bde;
	int len;
	struct mbuf *swloop; 
{
    	register struct mbuf *m, *swloop_tmp1;
	struct ether_header *eh, swloop_eh;
	int off, resid;
	struct ifqueue *inq;
	struct _bd *pbde = 0;
	int toff = 0;

	/*
	 * Deal with trailer protocol: if type is trailer
	 * get true type from first 16-bit word past data.
	 * Remember that type was trailer by setting off.
	 */
	if (swloop) {
		eh = mtod(swloop, struct ether_header *);
		swloop_eh = *eh;
		eh = &swloop_eh;
		if ( swloop->m_len > sizeof(struct ether_header))
			m_adj(swloop, sizeof(struct ether_header));
		else {
			MFREE(swloop, swloop_tmp1);
			if ( ! swloop_tmp1 )
				return;
			else
				swloop = swloop_tmp1;
		}
	} else  
	    eh = (struct ether_header *)(vaddr(bde,ni->bde_virtual,
		ni->bde_base_addr));
	eh->ether_type = ntohs((u_short)eh->ether_type);
#define dataaddr(eh, off, type)	((type)(((caddr_t)(eh)+(off))))
#if	DLI
#if	MACH_DEVICE
	/* ************************************ *
	 * NOTE:
	 * I am ignoring the swloop !=0 case.  Who knows what
	 * swloop != 0 means
	 */
	if ( (dli_active && !bcmp(eh->ether_shost, dli_from, 6)) ||
	     (dli_active && !bcmp(dli_from, dli_all, 6))) {

		eh->ether_type = ntohs((u_short)eh->ether_type);
		off = 0;
	} else
#endif	MACH_DEVICE
#endif	DLI

	if (eh->ether_type >= ETHERTYPE_TRAIL &&
	    eh->ether_type < ETHERTYPE_TRAIL+ETHERTYPE_NTRAILER) {
		off = (eh->ether_type - ETHERTYPE_TRAIL) * 512;
		if (off >= ETHERMTU)
			return;		/* sanity */
		if (swloop) {
			struct mbuf *mprev, *m0 = swloop;
/* need to check this against off */
			mprev = m0;
			while (swloop->m_next){/*real header at end of chain*/
				mprev = swloop;
				swloop = swloop->m_next;
			}
			/* move to beginning of chain */
			mprev->m_next = 0;
			swloop->m_next = m0;
			eh->ether_type = ntohs( *mtod(swloop, u_short *));

		} else {
			struct ether_header *peh;
			toff = (off < NI_MAXPACKETSZ ? off 
				: off - NI_MAXPACKETSZ);
			pbde = (off < NI_MAXPACKETSZ ? (bde + 1) : (bde + 2));
			peh = (struct ether_header *)vaddr(pbde,
				ni->bde_virtual, ni->bde_base_addr);
			eh->ether_type = ntohs(*dataaddr(peh, toff, u_short *));
			resid = ntohs(*(dataaddr(peh, toff+2, u_short *)));
			if (off + resid > len)
			return;		/* sanity */
			len = off + resid + sizeof(struct ether_header);
		}
	} else
		off = 0;
	if (len == 0)
		return;

	/*
	 * Pull packet off interface.  Off is nonzero if packet
	 * has trailing header; niget will then force this header
	 * information to be at the front, but we still have to drop
	 * the type and length which are at the front of any trailer data.
	 */
	if (swloop) {
		m = m_copy(swloop, 0, M_COPYALL);
		m_freem(swloop);
	} else {
	/* Header was in the 1st buffer */
		bde++;
		len -= sizeof(struct ether_header);
		m = niget(ni, bde, len, off, pbde, toff, &ds->ds_if);
	}
	if (m == 0)
		return;
	if (off) {
		struct ifnet *ifp;

		ifp = *(mtod(m, struct ifnet **));
		m->m_off += 2 * sizeof (u_short);
		m->m_len -= 2 * sizeof (u_short);
		*(mtod(m, struct ifnet **)) = ifp;
	}
#if	DLI
#if	MACH_DEVICE
	if ( (dli_active && !bcmp(eh->ether_shost, dli_from, 6)) ||
	     (dli_active && !bcmp(dli_from, dli_all, 6))) {
		dli_input(m, eh->ether_type, &eh->ether_shost[0], 
 			  &ni_dlv[ds->ds_if.if_unit], eh);
		return;
	} else
#endif	MACH_DEVICE
#endif	DLI
	switch (eh->ether_type) {

#ifdef	INET
	case ETHERTYPE_IP:
		schednetisr(NETISR_IP);
		inq = &ipintrq;
		break;

	case ETHERTYPE_ARP:
		arpinput(&ds->ds_ac, m);
#ifdef	IF_CNTRS
		ni_arp++;
		if (ni_narp) {int l = len + sizeof (struct ether_header);
			ni_ein[log_2(l)]--;
			if (l < 128) ni_lin[l>>3]--;
		}
#endif	IF_CNTRS
		return;
#endif
#ifdef	NS
	case ETHERTYPE_NS:
		schednetisr(NETISR_NS);
		inq = &nsintrq;
		break;

#endif
	default:
#if	DLI
#if	MACH_DEVICE
		m_freem(m);
#else	MACH_DEVICE
		eh->ether_type = htons(eh->ether_type);
		dli_input(m, eh->ether_type, &eh->ether_shost[0], 
 			  &ni_dlv[ds->ds_if.if_unit], eh);
#endif	MACH_DEVICE
#else	DLI
		m_freem(m);
#endif	DLI
		return;

	}

	if (IF_QFULL(inq)) {
		IF_DROP(inq);
		m_freem(m);
		return;
	}
	IF_ENQUEUE(inq, m);
}

/*
 * Ethernet output routine.
 * Encapsulate a packet of type family for the local net.
 * Use trailer local net encapsulation if enough data in first
 * packet leaves a multiple of 512 bytes of data in remainder.
 */
nioutput(ifp, m0, dst)
	struct ifnet *ifp;
	struct mbuf *m0;
	struct sockaddr *dst;
{
	int type, s, error;
	u_char edst[6]; 
	struct in_addr idst;
	register struct ni_softc *ds = &ni_softc[ifp->if_unit];
	register struct mbuf *m = m0;
	register struct ether_header *eh;
	register int off;
	int usetrailers;

	switch (dst->sa_family) {

#ifdef	INET
	case AF_INET:
		idst = ((struct sockaddr_in *)dst)->sin_addr;
		if (!arpresolve(&ds->ds_ac, m, &idst, edst, &usetrailers))
			return (0);	/* if not yet resolved */
		off = ntohs((u_short)mtod(m, struct ip *)->ip_len) - m->m_len;
		if (usetrailers && off > 0 && (off & 0x1ff) == 0 &&
		    m->m_off >= MMINOFF + 2 * sizeof (u_short)) {
			type = ETHERTYPE_TRAIL + (off>>9);
			m->m_off -= 2 * sizeof (u_short);
			m->m_len += 2 * sizeof (u_short);
			*mtod(m, u_short *) = htons((u_short)ETHERTYPE_IP);
			*(mtod(m, u_short *) + 1) = htons((u_short)m->m_len);
			goto gottrailertype;
		}
		type = ETHERTYPE_IP;
		off = 0;
		goto gottype;
#endif
#ifdef	NS
	case AF_NS:
		type = ETHERTYPE_NS;
 		bcopy((caddr_t)&(((struct sockaddr_ns *)dst)->sns_addr.x_host),
		(caddr_t)edst, sizeof (edst));
		off = 0;
		goto gottype;
#endif

	case AF_UNSPEC:
		eh = (struct ether_header *)dst->sa_data;
 		bcopy((caddr_t)eh->ether_dhost, (caddr_t)edst, sizeof (edst));
		type = eh->ether_type;
		goto gottype;

#if	DLI
	case AF_DLI:
		if (m->m_len < sizeof(struct ether_header))
		{
			error = EMSGSIZE;
			goto bad;
		}
#if	MACH_DEVICE
		goto pure;
#else	MACH_DEVICE
		eh = mtod(m, struct ether_header *);
 		bcopy(dst->sa_data, (caddr_t)eh->ether_dhost, sizeof (eh->ether_dhost));
		goto gotheader;
#endif	MACH_DEVICE
#endif	DLI
	default:
		printf("ni%d: can't handle af%d\n", ifp->if_unit,
			dst->sa_family);
		error = EAFNOSUPPORT;
		goto bad;
	}

gottrailertype:
	/*
	 * Packet to be sent as trailer: move first packet
	 * (control information) to end of chain.
	 */
	while (m->m_next)
		m = m->m_next;
	m->m_next = m0;
	m = m0->m_next;
	m0->m_next = 0;
	m0 = m;

gottype:
	/*
	 * Add local net header.  If no space in first mbuf,
	 * allocate another.
	 */
	if (m->m_off > MMAXOFF ||
	    MMINOFF + sizeof (struct ether_header) > m->m_off) {
		m = m_get(M_DONTWAIT, MT_HEADER);
		if (m == 0) {
			error = ENOBUFS;
			goto bad;
		}
		m->m_next = m0;
		m->m_off = MMINOFF;
		m->m_len = sizeof (struct ether_header);
	} else {
		m->m_off -= sizeof (struct ether_header);
		m->m_len += sizeof (struct ether_header);
	}
	eh = mtod(m, struct ether_header *);
	eh->ether_type = htons((u_short)type);
 	bcopy((caddr_t)edst, (caddr_t)eh->ether_dhost, sizeof (edst));
#if	DLI
#if	MACH_DEVICE
 	bcopy((caddr_t)ds->ds_addr, (caddr_t)eh->ether_shost, sizeof (ds->ds_addr));
pure:
#else	MACH_DEVICE
gotheader:
 	bcopy((caddr_t)ds->ds_addr, (caddr_t)eh->ether_shost, sizeof (ds->ds_addr));
#endif	MACH_DEVICE
#else	DLI
 	bcopy((caddr_t)ds->ds_addr, (caddr_t)eh->ether_shost, sizeof (ds->ds_addr));
#endif	DLI

	/*
	 * Queue message on interface, and start output if interface
	 * not yet active.
	 */
	s = splimp();
	if (IF_QFULL(&ifp->if_snd)) {
		IF_DROP(&ifp->if_snd);
		splx(s);
		m_freem(m);
		return (ENOBUFS);
	}
	IF_ENQUEUE(&ifp->if_snd, m);
	nistart(ifp->if_unit);
	splx(s);
	return (0);

bad:
	m_freem(m0);
	return (error);
}

/*
 * Process an ioctl request.
 */
niioctl(ifp, cmd, data)
	register struct ifnet *ifp;
	int cmd;
	caddr_t data;
{
	register struct ifaddr *ifa = (struct ifaddr *)data;
	int s = splnet(), error = 0;

	switch (cmd) {

	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
		niinit(ifp->if_unit);
		switch(ifa->ifa_addr.sa_family) {
#ifdef	INET
		case AF_INET:
			((struct arpcom *)ifp)->ac_ipaddr =
				IA_SIN(ifa)->sin_addr;
			/* 1st packet out */
			arpwhohas((struct arpcom *)ifp, &IA_SIN(ifa)->sin_addr);
			break;
#endif
#ifdef	NS
		case AF_NS:
		    {
			register struct ns_addr *ina = &(IA_SNS(ifa)->sns_addr);
			
			if (ns_nullhost(*ina)) {
				ina->x_host = * (union ns_host *) 
				     (il_softc[ifp->if_unit].is_addr);
			} else {
				il_setaddr(ina->x_host.c_host, ifp->if_unit);
				return (0);
			}
			break;
		    }
#endif
		}
		break;
#ifdef	IF_CNTRS
	case SIOCCIFCNTRS:
		if (!suser()) {
			error = EPERM;
			break;
		}
		bzero((caddr_t)ni_ein, sizeof (ni_ein));
		bzero((caddr_t)ni_eout, sizeof (ni_eout));
		bzero((caddr_t)ni_lin, sizeof (ni_lin));
		bzero((caddr_t)ni_lout, sizeof (ni_lout));
		bzero((caddr_t)&ni_arp, sizeof (int));
		bzero((caddr_t)ni_mchain_raw, sizeof (ni_mchain_raw));
		bzero((caddr_t)ni_mchain_cooked, sizeof (ni_mchain_cooked));
		break;
#endif	IF_CNTRS
	default:
		error = EINVAL;
	}
	splx(s);
	return (error);
}

/*
 * Pull read data off a interface.
 * Len is length of data, with local net header stripped.
 * Off is non-zero if a trailer protocol was used, and
 * gives the offset of the trailer information.
 * We copy the trailer information and then all the normal
 * data into mbufs.
 */
struct mbuf *
niget(ni, bde, totlen, off0, pbde, trailoff, ifp)
	struct ni *ni;
	struct _bd *bde, *pbde;
	int totlen, off0, trailoff;
	struct ifnet *ifp;
{
	struct mbuf *top, **mp, *m;
	int off = off0, len = 0;
	/* setup for 1st buffer */
	int cp = (int) vaddr(bde, ni->bde_virtual, ni->bde_base_addr); 
	int bdelen = bde->buf_len;

	top = 0;
	mp = &top;
	while (totlen > 0) {
		MGET(m, M_DONTWAIT, MT_DATA);
		if (m == 0)
			goto bad;
		if (off) {
			cp = (int) vaddr(pbde, ni->bde_virtual, 
			    ni->bde_base_addr) + trailoff;
			bdelen = pbde->buf_len;
			len = totlen - off;
		} else
			len = totlen;

		if (bdelen >= CLBYTES && len >= CLBYTES) {
			register caddr_t pp;
			struct pte *cpte, *ppte;
			int i;

			/*
			 * If doing the first mbuf and
			 * the interface pointer hasn't been put in,
			 * put it in a separate mbuf to preserve alignment.
			 */
			if (ifp) {
				len = 0;
				goto nopage;
			}
			MCLGET(m);
			if (m->m_len != CLBYTES)
				goto nopage;
			len = CLBYTES;
			if (!claligned(cp))
				goto copy;

		/* Swap cluster 1 for 1 */
			pp = mtod(m, caddr_t);
			cpte = &Mbmap[mtocl(cp)*CLSIZE];
			ppte = &Mbmap[mtocl(pp)*CLSIZE];
			for(i=0; i<CLSIZE; i++) {
				struct pte t;
				t = *ppte; *ppte++ = *cpte; *cpte++ = t;
				mtpr(TBIS, (caddr_t)cp);
				cp += NBPG;
				mtpr(TBIS, (caddr_t)pp);
				pp += NBPG;
			} 
			goto nocopy;
		}
nopage:
		m->m_off = MMINOFF;
		if (ifp) {
			/*
			 * Leave room for ifp.
			 */
			m->m_len = MIN(MLEN - sizeof(ifp), len);
			m->m_off += sizeof(ifp);
		} else
			m->m_len = MIN(MLEN, len);
		m->m_len = MIN(m->m_len, bdelen);
copy:
		bcopy((caddr_t)cp, mtod(m, caddr_t), (unsigned)m->m_len);
		cp += m->m_len;

nocopy:
		bdelen -= m->m_len;

		if(bdelen <= 0 && off == 0) { /* next buffer */
				bde++;
				bdelen=bde->buf_len;
				cp = (int)vaddr(bde, ni->bde_virtual, 
				    ni->bde_base_addr);
		}

		*mp = m;
		mp = &m->m_next;
		if (off) {
			/* sort of an ALGOL-W style for statement... */
			off += m->m_len;
			if (off == totlen) {
				cp = (int) vaddr(bde, ni->bde_virtual,
				    ni->bde_base_addr);
				bdelen = bde->buf_len;
				off = 0;
				totlen = off0;
			}
		} else
			totlen -= m->m_len;
		if (ifp) {
			/*
			 * Prepend interface pointer to first mbuf.
			 */
			m->m_len += sizeof(ifp);
			m->m_off -= sizeof(ifp);
			*(mtod(m, struct ifnet **)) = ifp;
			ifp = (struct ifnet *)0;
		}
	}
	return (top);
bad:
	m_freem(top);
	return (0);
}

ni_sptdb(ni, type, index, q, flags, doclear)
	struct ni *ni;
	/* Set Protocol Type Definition Block */
{
		register struct ni_softc *ds = &ni_softc[ni->unit];
		struct ni_msg *ni_msg;
		struct ptdb *ptdb;
		int empty,i;
		struct nidevice *addr = (struct nidevice *)ni->ni_regs;
		int clear = doclear;


loop:
		ni_msg = (struct ni_msg *)remqhi(&ni->freeq0, NI_MAXITRY);
		if(ni_msg == (struct ni_msg *)QEMPTY)
			return;
		bzero(&ni_msg->text[0], sizeof(struct ptdb));
		ni_msg->status = 0;
		if(clear)
			ni_msg->ni_opcode = NIOP_CLPTDB;
		else
			ni_msg->ni_opcode = NIOP_STPTDB;
		ni_msg->opcode = SNDMSG;
		ptdb = (struct ptdb *)&ni_msg->text[0];
		ptdb->flags = flags;
		ptdb->fq_index = q;
		ptdb->ptt = type;
		ptdb->ptdb_index = index;
		ptdb->adr_len = 0;
		ni_msg->msg_len = 18;
		if(!clear && flags&(PTDB_AMC|PTDB_BDC)) {
		   int nptdb=0;

		/* 1st reserved for -1 broadcast addr */			
		   ptdb->adr_len++;
		   ni_msg->msg_len += 8;
		   bcopy(ni_multi, (&ptdb->multi[nptdb++])->addr,6);

		   for (i = 0; i < NMULTI - 1; i++)
		        if (ds->ds_muse[i] > 0) {
			ptdb->adr_len++;
			ni_msg->msg_len += 8;
			bcopy(ds->ds_multi[i],(&ptdb->multi[nptdb++])->addr,6);
		       }
		}

		if((empty=insqti(ni_msg, &ni->comq0, NI_MAXITRY)) > 0)
			printf("insqti failed\n");
		else if(empty == QEMPTY) {
			while((addr->pc&PC_OWN))
				;
			addr->pc = PC_CMDQNE|PC_CMDQ0|PC_OWN;
			while((addr->pc&PC_OWN))
				;
		}
	while((addr->ps&PS_OWN))
		;
		if(clear) {
			clear = 0;
			goto loop;
		}
}	
struct mbuf *
m_compress(n) /* compress silly LONG mbuf chains */
	register struct mbuf *n;
{
	register struct mbuf *m, *q, *p;
	int len, count;

	MGET(m, M_DONTWAIT, n->m_type);
	p = m;
	m->m_len = 0;
	for(;;) {
		len = MLEN;
	do {
		count = MIN(n->m_len, len);
		bcopy(mtod(n, caddr_t), mtod(m, caddr_t)+m->m_len,
		  (unsigned)count);
		len -= count;
		m->m_len += count;
		n->m_len -= count;
		if (n->m_len)
			n->m_off += count;
		else
			n = m_free(n);
		if(!n)
			return(p);
	} while (len && n);
	MGET(q, M_DONTWAIT, n->m_type);
	q->m_len = 0;
	m->m_next = q;
	m = q;
	}
}
#endif
