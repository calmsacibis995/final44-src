/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	biconf.c,v $
 * Revision 2.9  89/04/07  14:58:36  rvb
 * 	1) 8200 lost some printout in the move to use xmi/nmi
 * 	   loopback.
 * 	2) Cleared a typeo in 8800; and initialize machine[] slot.
 * 	[89/04/07            rvb]
 * 
 * Revision 2.8  89/04/05  13:03:51  rvb
 * 	Use loopback to "unbreak" the BI_NBI.
 * 	[89/01/25            rvb]
 * 
 * Revision 2.7  89/03/09  22:30:21  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/26  10:57:48  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  88/12/19  02:56:22  mwyoung
 * 	Removed lots of unused variables.
 * 	[88/12/18            mwyoung]
 * 
 * Revision 2.4  88/10/11  13:05:40  rpd
 * 	New functions:
 * 		1) bi_node_reset(bi) to handle reseting a node while
 * 	saving/restoring its state.
 * 		2) bi_settle() wait for 10sec so a the raw NRST to the
 * 	kdb50 nodes will finish.
 * 	bi_settle() is called once just before the probe_bi's are done.
 * 	Thus ud{,a}init will no. longer have to do the node reset.
 * 	[88/10/03            rvb]
 * 
 * Revision 2.3  88/08/22  21:34:23  mja
 * 	Fixed to call device probe routine during KDB-50 configuration
 * 	so that any initialization code there (e.g. in the new UDA
 * 	driver) is executed.
 * 	[88/02/20            mja]
 * 
 * Revision 2.2  88/08/10  10:44:20  rvb
 *  24-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Don't touch a bi node that is BROKE.
 * 
 *   7-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Slave starting is now synchronous, done at start_init time.  Code
 * 	is in vaxmp.c
 * 
 *  27-May-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Don't start slaves if RB_UNIRPOC is true.
 * 
 *  25-May-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Use splblock(1f) in probe code.
 * 
 *   8-Apr-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Created.  Week of 4/4.
 * 
 */
/*
 *	File:	biconf.c
 *	Author:	Robert V. Baron
 *
 *	Split out configuration for machines with bi
 */
#include <cpus.h>
#include <cputypes.h>

#include <uba.h>
#include <bi.h>
#include <ni.h>

#include <net_uda.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/buf.h>
#include <sys/dk.h>
#include <mach/machine.h>
#include <sys/reboot.h>
#include <vm/vm_kern.h>
/*#include <mach/vm_param.h>*/

#include <vax/cpu.h>
#include <vax/mtpr.h>
#include <vax/scb.h>
#include <vax/bi_node.h>
#include <vax/pte.h>
#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>


#if	VAX820
#include <vaxnb/ka820.h>
#include <vax/watch_chip.h>
#endif	VAX820
#if	VAX6200
#include <vaxnb/ka62a.h>
#include <vaxnb/cca.h>
#endif	VAX6200
#if	VAX8800
#include <vaxnb/ka88.h>
#endif	VAX8800

#include <vaxnb/node.h>
int	ncpu;			/* number of cpu */
struct	cpunode	cpunode[NNODES];	/* remember node address */
int	nmem;
struct	memnode memnode[NNODES];
int	nioa;			/* number of io adapters */
struct	ioanode	ioanode[NNODES];	/* remember node address */

struct	bi_node *check_bi; /* bi address to check */

int	nbi;		/* current BI node */
int	numkdb;		/* KDB50s */
#if	NNI > 0
int	numni;
#endif	NNI > 0
int	max_bi_cpus = 4;
int	intmask;	/* mask to interrupt master CPU */

extern int dkn;

/*
 * XXX wrong conditionals.
 */
extern int Xkdb0int(), Xkdb1int(), Xkdb2int(), Xkdb3int();
int	(*kdb50intv[4])() = 	{ Xkdb0int, Xkdb1int, Xkdb2int, Xkdb3int };
#ifdef	NNI > 0
extern int Xni0int();
int	(*niintv[1])() =	{ Xni0int };
#endif	NNI > 0

/*
 *	Probe BI node space for the specified BI.
 */
bi_configure()
{
	switch (cpu) {
#if	VAX820
	case VAX_820:
		ka820_conf();
		break;
#endif	VAX820

#ifdef	VAX8800
	case VAX_8800:
		k88_conf();
		break;
#endif	VAX8800

#if	VAX6200
	case VAX_6200:
		ka62a_conf();
		break;
#endif	VAX6200
	}

}

	/*
	 * For reason's that do not currently understand,
	 * if this code is moved to ka88.c -- The kernel gets
	 * an interrupt thru a 0 vector.
	 */
k88_conf()
{
	register int		i;
	int			need_vm = 1;	/* implies need more vm */
	register struct ioanode *ioap;
	register struct nbi *ip;
	register struct bi_node *biv;
	union cpusid cpusid;

	cpusid.cpusid = mfpr(SID);
	cpuspeed = 8;

	printf("VAX 8800\n");
	printf("CPU 0:\n");
	mtpr(NICTRL, 0xe1);	/* enable NMI interrupts */
#if	NCPUS == 1
	master_cpu = 0;
#else	NCPUS == 1
	master_cpu = (cpusid.cpusid & (1 << 23)) >> 23;
	set_cpu_number();	/* to sync with master cpu number */
	/*
	 *	Processors are in slots 0 and 1.
	 */
	machine_slot[0].is_cpu = TRUE;
		machine_slot[0].cpu_type = CPU_TYPE_VAX;
		machine_slot[0].cpu_subtype = CPU_SUBTYPE_VAX8800;
	machine_slot[1].is_cpu = TRUE;
		machine_slot[1].cpu_type = CPU_TYPE_VAX;
		machine_slot[1].cpu_subtype = CPU_SUBTYPE_VAX8800;
	vax_putc(0);		/* wait for console to come ready */

	mtpr(TXDB, 0xf05);	/* boot other cpu */
#endif	NCPUS == 1
	{
		struct	mcl	*nmp;

		nmp = (struct mcl *)
				kmem_alloc_pageable(kernel_map,
				 sizeof(struct mcl));
		ioaccess((caddr_t)NMI_MCL, (vm_offset_t) nmp,
					 sizeof(struct mcl));

		/* Remember stuff */
		memnode[nmem].addr88 = nmp;
		memnode[nmem++].node = 0;

		printf("MEM 0:  V/P  %x/%x", nmp, NMI_MCL);
		pms88_size();
	}
	for (i = 0; i < 4; i++)	{
		extern int nmi_nbia_addr[], nmi_bi_addr[];

		if (need_vm) {
			ip = (struct nbi *)kmem_alloc_pageable(kernel_map, NBPG);
			biv = (struct bi_node *)kmem_alloc_pageable(kernel_map, BI_NODE_SIZE);
			if (ip == 0 || biv == 0)
				panic("new_configure");
			need_vm = 0;
		}
		ioaccess(nmi_bi_addr[i], biv, BI_NODE_SIZE);
		if (nmi_badaddr(biv, 4))		/* no bi space */
			continue;
		ioaccess(nmi_nbia_addr[i], ip, NBPG);
		if (nmi_badaddr(ip, 4))
			continue;

		need_vm++;

		printf("IOA %x:  V/P  %x/%x",
			i, ip, nmi_nbia_addr[i]);

		/* Remember stuff */
		ioap = &ioanode[nioa];
		ioap->addr88 = ip;
		ioap->node = i;
		ioap->bi_addr = (caddr_t) nmi_bi_addr[i];

		/* 
		 * As soon as we enable, we see a power interrupt
		 * unless...
		 */
		ip->csr1 |= (NBIACSR1_BI0PWR | NBIACSR1_BI1PWR);
		ip->csr0 |= NBIACSR0_IE;		/* interrupt enable */

		ip->csr0 |=  NBIACSR0_BIICLOOP;
		ioap->bddr = biv;
		ioap->bi[ioap->bnode = biv->bicsr & BICSR_NODE] = biv;
		biv->dev_type = BI_NBI;
		biv->dev_rev = 0x1234;
		biv->bicsr |= BICSR_BROKE;	/* clear broke */
		ip->csr0 &=  ~NBIACSR0_BIICLOOP;
			/*
			 * N.B. va hasn't changed, but we need to straighten
			 * out the pa since loop back is off.
			 */
		ioaccess(nmi_bi_addr[i] + BI_NODE_SIZE * ioap->bnode, biv, BI_NODE_SIZE);

		scan_bix(ioap);
		nioa++;
	}
	if (!need_vm) {
    	 	kmem_free(kernel_map, ip, NBPG);
		kmem_free(kernel_map, biv, BI_NODE_SIZE);
	}

	bi_settle();
	for (i = nioa, nioa = 0; nioa < i; nioa++) {

		ioap = &ioanode[nioa];
		biv = ioap->bddr;
		if (ioap->addr88) {
			probe_bi(ioap->bi_addr, 0, 1<<ioap->bnode);
			/*
			 * Enable Bcard interrupts now that we don't
			 * expect any
			 */
			biv->ber = (biv->ber & BER_ERR);
			biv->bicsr |=  BICSR_HEIE | BICSR_SEIE;
		}
	}
}

#define bi_int(nioa, nodenum) ((int)&biscb - (int)&scb + 64*nioa + 4*nodenum)+0x80000
scan_bix(iop)
struct	ioanode	*iop;
{
	register int	i;
	register struct bi_node	*bip = (struct bi_node *)iop->bi_addr;
	register struct bi_node	*biv = iop->bddr;	/* b card */
	int		nodenum = iop->bnode;
	unsigned short	dev_type;
	int		cpu_count = 0;
	int		need_vm = 1;
	extern caddr_t	biscb;

	/* now we are using loop back to find the "b" card. */
	switch (biv->dev_type) {
		case BI_NBI:
			printf("\tB Card @Node%x V/P %x/%x\n",
				nodenum, biv, pmap_extract(kernel_pmap, biv));
			/*
			 * If we enable interrupts now
			 * we will get hit with the nex's when we probe
			 * even if bi_badaddr clears ber before it lowers
			 * priority
			 */
			biv->ber = (biv->ber & BER_ERR);
			biv->eintrcsr = bi_int(nioa, nodenum);
			biv->intrdes = 1 << nodenum;
			biv->bicsr |= BICSR_BROKE;	/* clear broke */
/*			biv->bicsr |=  BICSR_HEIE | BICSR_SEIE;*/

			biv->bcicsr |= BCI_INTREN;	/* interrupt enable */
			biv->sadr = 0;
			biv->eadr = mem_size;

			biv->ipintrmsk = 0xffff0000;
			break;
		case BI_XMI:
		case BI_XMI|0x2000:
		case BI_XMI|0x4000:
			printf("\tB Card @Node%x V/P %x/%x\n",
				nodenum, biv, pmap_extract(kernel_pmap, biv));
			biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
			biv->eintrcsr = bi_int(nioa, nodenum);
			biv->intrdes = 1 << nodenum;
			biv->bicsr |= BICSR_HEIE | BICSR_SEIE;

			biv->bcicsr = BCI_RTOEVEN | BCI_INTREN;
			biv->sadr = 0;
			biv->eadr = mem_size;
			break;
	}
	/* we still want to look for 8200 cpus and mem and kdb50's */
	for (nodenum = 0; nodenum < BI_MAX_NODE; nodenum++, bip++) {
		/*
		 *	Make this node available in virtual space.
		 */
		if (need_vm) {
		    biv = (struct bi_node *)
		    	  kmem_alloc_pageable(kernel_map, BI_NODE_SIZE);
		    if (biv == 0)
			panic("scan_bix");
		    need_vm = 0;
		}
		ioaccess((caddr_t)bip, (vm_offset_t)biv, BI_NODE_SIZE);
		check_bi = biv;
		if (bi_badaddr((caddr_t)biv, sizeof(int))) {
			continue;
		}
		dev_type = biv->dev_type;
		if (biv->bicsr & BICSR_BROKE && dev_type != 1) {
			continue;
		}
		need_vm++;

		switch (dev_type) {

		case BI_KDB50:
#if	VAX820
				/*
				 * We are screwing up the bus that we access
				 * memory over.  We must be very careful.
				 * This code was originally hacked in by avie.
				 */
			if (cpu == VAX_820) {
				for (i = -1; i < 100;) {
					i++;
					/*
					 * run in cache
					 * wait for storm to clear
					 */
					if (!i)
						biv->bicsr |= BICSR_NRST;
				}
			} else
#endif	VAX820
			biv->bicsr |= BICSR_NRST;

		case BI_NBI:
		case BI_XMI:
		case BI_XMI|0x2000:
		case BI_XMI|0x4000:
		case BI_DR32:
		case BI_KLESI:
		case BI_CI:
		case BI_DXX32:
		case BI_CIOBS:
		case BI_TK50:
		case BI_DEBNA:
		case BI_UBA:
		case 0:
			need_vm = 0;
			break;
		default:
			printf("type 0x%x unknown\n", dev_type);
			need_vm = 0;
			break;

		case BI_KA820:
			printf("CPU %x: KA820 %x/%x %x ", nodenum, biv, bip, dev_type);
			cpu_count++;
			if ((nodenum >= NCPUS) || (cpu_count > max_bi_cpus)) {
				printf("not configured\n");
				break;
			}

				/* Remember stuff */
			cpunode[nodenum].addr82 = biv;
			cpunode[nodenum].node = nodenum;
			machine_slot[nodenum].is_cpu = TRUE;
			machine_slot[nodenum].cpu_type = CPU_TYPE_VAX;
			machine_slot[nodenum].cpu_subtype = CPU_SUBTYPE_VAX8200;

			/*
			 *	Enable interrupts on errors, sending
			 *	them to the master cpu.
			 */
			biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
			biv->eintrcsr = bi_int(nioa, nodenum);
			biv->intrdes = intmask;	/* interrupt master */
			biv->bicsr |= BICSR_SEIE | BICSR_HEIE;
			/*
			 *	Let anyone interrupt us.
			 */
			biv->ipintrmsk = 0xffff0000;

			iop->bi[nodenum] = biv;
			if (nodenum == master_cpu) {
				iop->bnode = nodenum;
				iop->bddr = biv;
				printf("MASTER.\n");
			} else {
				printf("\n");
			}
			break;
		case BI_MEM:
			iop->bi[nodenum] = biv;
			printf("MEM %x:       %x/%x   %x ", nodenum, biv, bip, dev_type);
			printf("%d Meg .. %d Meg\n",
				biv->sadr>>20, biv->eadr>>20);
				/* Remember stuff */
			biv->bicsr |= BICSR_BROKE;	/* clear broke but does not work */
			memnode[nmem].addr82 = biv;
			memnode[nmem++].node = nodenum;
			break;
		}
	}
	if (!need_vm)
	    	  kmem_free(kernel_map, biv, BI_NODE_SIZE);
}

probe_bi(bip, bus, focus)
struct bi_node	*bip;
int		bus;
{
	struct bi_node	*biv;
	int		nodenum;
	u_short		dev_type;
	int		nkdb = 0;
	int		need_vm = 1;
	char 		*tab;
	extern caddr_t	biscb;
	/*
	 *	Following variables are for the kdb50 hack.
	 */
	register struct uba_device *ui;
	register struct uba_ctlr *um;
	struct uba_driver *udp;
	caddr_t		reg;

	tab = bus ? "    " : "";
	printf("BI%d                  /%x\n", nbi, bip);

	for (nodenum = 0; nodenum < BI_MAX_NODE; nodenum++, bip++) {
		/*
		 *	See if we picked up this node in pass 1
		 */
		if (ioanode[nioa].bi[nodenum]) {
/*
			printf("%snode %x:  %x/%x %x PREVIOUSLY MAPPED.\n", tab, nodenum,
				ioanode[nioa].bi[nodenum],
				pmap_extract(kernel_pmap, ioanode[nioa].bi[nodenum]),
				dev_type);
*/
			continue;
		}
		/*
		 *	Make this node available in virtual space.
		 */
		if (need_vm) {
		    biv = (struct bi_node *)
		    	  kmem_alloc_pageable(kernel_map, BI_NODE_SIZE);
		    if (biv == 0)
			panic("probe_bi");
		    need_vm = 0;
		}
		ioaccess((caddr_t)bip, (vm_offset_t)biv, BI_NODE_SIZE);
		check_bi = biv;
		if (bi_badaddr((caddr_t)biv, sizeof(int))) {
			continue;
		}
		dev_type = biv->dev_type;
		if (!dev_type) {
			/*
			 * silently ignore nodes with ID 0 (8800 seems to
			 * return this for nodes that do not exist.)
			 */
			continue;
		}
		if (biv->bicsr & BICSR_BROKE && biv->dev_type != BI_MEM) {
			printf("NODE %x TYPE %x FAILED SELF TEST. bicsr = %x\n",
				nodenum, dev_type, biv->bicsr);
			continue;
		}
		need_vm++;
		ioanode[nioa].bi[nodenum] = biv;
		biv->ber = (biv->ber & BER_ERR) | BER_UPEN;  /* clear bus error register */
		biv->eintrcsr = bi_int(nioa, nodenum);
		biv->intrdes = focus;
		biv->bicsr |= BICSR_HEIE | BICSR_SEIE;

		switch (dev_type) {
		case BI_DR32:
			printf("%snode %x:  %x/%x %x ", tab, nodenum, biv, bip, dev_type);
			printf("DRB32-? Parallel Port Adapter "); goto not_supported;
		case BI_KLESI:
			printf("%snode %x:  %x/%x %x ", tab, nodenum, biv, bip, dev_type);
			printf("KLESI-B (Tape) Adapter "); goto not_supported;
		case BI_XMI:
		case BI_XMI|0x2000:
		case BI_XMI|0x4000:
/*			printf("X Bus Adapter.  [%x V/P %x/%x]\n",
				dev_type, biv, bip);*/
			break;
		case BI_CI:
			printf("%snode %x:  %x/%x %x ", tab, nodenum, biv, bip, dev_type);
			printf("CIBCA Computer Interconnect Adapter "); goto not_supported;
		case BI_DXX32:
			printf("%snode %x:  %x/%x %x ", tab, nodenum, biv, bip, dev_type);
			printf("DMB32/DHB32 {Communication} Adapter "); goto not_supported;
		case BI_CIOBS:
			printf("%snode %x:  %x/%x %x ", tab, nodenum, biv, bip, dev_type);
			printf("Obsolete CIBCA Computer Interconnect Adapter "); goto not_supported;
		case BI_TK50:
			printf("%snode %x:  %x/%x %x ", tab, nodenum, biv, bip, dev_type);
			printf("TK50 Losing Streamer Adapter "); goto not_supported;
		not_supported:
			printf("is NOT supported.\n");
			break;
		case BI_KA820:
			break;
#if	VAX8800
		case 0xffff:	/* unitialized NMI/BI adapter */
		case BI_NBI: {
			printf("%snode %x:  %x/%x %x ", tab, nodenum, biv, bip, dev_type);
			printf("NMI/BI adapter.\n");
			/* initialization done in nmi_search */
			break;
		}
#endif	VAX8800
		case BI_UBA: {
			extern int numuba;

			printf("%snode %x:  %x/%x %x ", tab, nodenum, biv, bip, dev_type);
			printf("uba%d\n", numuba);
			if (numuba >= NUBA) {
				printf("%s%d uba's not configured", tab, ++numuba);
				break;
			}
			/*
			 *	Enable interrupts.
			 *	Select high priority arbitration.
			 */
/*			biv->intrdes = focus;	/* interrupt master */
			uba_hd[numuba].uh_type = UBATYPE_DWBUA;
			biv->bicsr = (biv->bicsr & ~BICSR_ARB_MASK) |
							BICSR_ARB_HIGH;
			/*
			 *	Allocate enough virtual address space to map
			 *	the Unibus.
			 */
			unibus_start[numuba] = kmem_alloc_pageable(kernel_map,
					VAX_PGBYTES*UBAPAGES);
			unibus_end[numuba] = unibus_start[numuba] +
					VAX_PGBYTES*UBAPAGES;
			unifind((struct uba_regs *)biv,
				(struct uba_regs *)bip,
				(caddr_t)unibus_start[numuba],
#define WINDOW_BASE 0x400000
#define WINDOW_SIZE 0x040000
				(caddr_t)bip + WINDOW_BASE +
					       nodenum * WINDOW_SIZE,
				FALSE);
			((struct dwbua_regs *)biv)->csr =
				((struct dwbua_regs *)biv)->csr;
			numuba++;
			break;
		}
		case BI_MEM:
			break;
		case BI_KDB50:
			printf("%snode %x:  %x/%x %x ", tab, nodenum, biv, bip, dev_type);
			printf("kdb%d.\n", nkdb++);
#include <ra.h>
#if	NRA > 0
			/*
			 *	What follows is somewhat interesting.
			 *	We search the unibus devices for configured
			 *	UDA50s, pretending we are a Unibus.  Of course,
			 *	we do the proper fudging.
			 */
			for (um = ubminit; udp = um->um_driver; um++) {
				extern struct uba_driver udadriver;
				struct uba_hd	*uhp;
				vm_offset_t	mapptr;

				if (um->um_alive)
					continue;
				if (um->um_driver != &udadriver)
					continue;
				if (um->um_ubanum != numuba &&
							um->um_ubanum != '?')
					continue;
				reg = ((caddr_t)biv) + 0xf2;	/* offset */
				*((int *)(((caddr_t)&scb)+(0x140+nodenum*4))) =
					(int)scbentry(kdb50intv[um->um_ctlr],
								SCB_ISTACK);
				biv->uintrcsr = 0x140+nodenum*4;
				udaiskdb50(um->um_ctlr, biv, 0x140+nodenum*4);
#if	NET_UDA
				/*
				 *  We only seem to need this with the new
				 *  driver so we'll make it conditional for
				 *  now.  The old driver probe routine will
				 *  have to be altered to suppress the probe
				 *  part of its action before this conditional
				 *  can be removed.
				 */
				(*udp->ud_probe)(0, um->um_ctlr, um);
#endif	NET_UDA
				printf("%s%s%s%d at kdb%d\n",
					tab, "         ", udp->ud_mname, um->um_ctlr, numkdb);
				um->um_alive = 1;
				um->um_ubanum = numuba;
				um->um_hd = &uba_hd[numuba];
				um->um_addr = (caddr_t)reg;
				udp->ud_minfo[um->um_ctlr] = um;
				/*
				 *	The UNIBUS code expects the rest of
				 *	the nexus to be there, so we fudge
				 *	the pointer.
				 */
				uhp = &uba_hd[numuba];
				uhp->uh_type = UBATYPE_KDB50;
				/*
				 *	One MACH page is probably big enough
				 *	to hold all the mapping registers
				 *	(512*4)...
				 */
				mapptr = kmem_alloc(kernel_map,
						NUBMREG*sizeof(struct pte));
				uhp->uh_uba =
					(struct uba_regs *)(mapptr - 0x800);
				uhp->uh_physuba = (struct uba_regs *)
					(pmap_extract(pmap_kernel(), mapptr) -
						0x800);
				uhp->uh_map =
					(struct map *)calloc(UAMSIZ * sizeof (struct map));
				ubainitmaps(uhp);
				/*
				 *	Attach the slaves.
				 */
				for (ui = ubdinit; ui->ui_driver; ui++) {
					if (ui->ui_driver != udp ||
						ui->ui_alive ||
						ui->ui_ctlr != um->um_ctlr &&
						ui->ui_ctlr != '?' ||
						ui->ui_ubanum != numuba &&
						ui->ui_ubanum != '?')
						continue;
					if ((*udp->ud_slave)(ui, reg)) {
						ui->ui_alive = 1;
						ui->ui_ctlr = um->um_ctlr;
						ui->ui_ubanum = numuba;
						ui->ui_hd = &uba_hd[numuba];
						ui->ui_addr = (caddr_t)reg;
						ui->ui_physaddr = (caddr_t)bip + 0xf4;
						if (ui->ui_dk && dkn < DK_NDRIVE)
							ui->ui_dk = dkn++;
						else
							ui->ui_dk = -1;
						ui->ui_mi = um;
						/* ui_type comes from driver */
						udp->ud_dinfo[ui->ui_unit] = ui;
						printf("%s%s%s%d at %s%d slave %d\n%s%s",
						    tab,  "         ",
						    udp->ud_dname, ui->ui_unit,
						    udp->ud_mname, um->um_ctlr,
						    ui->ui_slave,
						    tab,  "         ");
						(*udp->ud_attach)(ui);
					}
				}
				break;
			}
			numkdb++;
			numuba++;	/* XXX - fake uba */
#else	NRA > 0
			printf("not supported\n");
#endif	NRA > 0
			break;
		case BI_DEBNA:
#if	NNI > 0
			printf("%snode %x:  %x/%x %x ", tab, nodenum, biv, bip, dev_type);
			printf("ni%d\n", numni);
			if (biv->dev_rev != 0x023b) 
			    printf("NI: Warning -- revision level changed\n");
			if ((biv->dev_rev & 0xff) < 0x3b)
			    printf("NI: Error -- Old revision found\n");
			if (ni_to_bi_attach(nbi, nodenum, numni, biv))
			    numni++;
			else
			    printf("ni%d not configured\n", numni);
#else	NNI > 0
			printf("ni not supported\n");
#endif	NNI > 0
			break;
		default:
			printf("%snode %x:  %x/%x %x ", tab, nodenum, biv, bip, dev_type);
			printf("type 0x%x unknown\n", dev_type);
		}
	}
	if (!need_vm)
	    	  kmem_free(kernel_map, biv, BI_NODE_SIZE);
	nbi++;
}

#if	VAX8800
nmi_badaddr(addr, size)
{
	register int spl = splblock();

	if (badaddr(addr, size)) {
		register int	dest;
		register struct mcl *mp= memnode[0].addr88;

		dest = mp->csr4;
		dest = mp->csr5;

		mtpr(TOSTS, 0);
		mtpr(MCSTS, 0);
		splx(spl);
		return(1);
	}
	splx(spl);
	return(0);
}
#endif	VAX8800

#if	VAX6200
xmi_badaddr(addr, size)
{
	register int spl = splblock();
	register struct ka62a *cpp = cpunode[cpu_number()].addr62;

	if (badaddr(addr, size)) {
		if ((int) cpp) {
			cpp->ber = cpp->ber & XMIBER_ERR;
			cpp->csr2 = cpp->csr2 | ka62aCSR2_ERR;
		}
		splx(spl);
		return(1);
	}

	if ((int) cpp) {
		cpp->ber = cpp->ber & XMIBER_ERR;
		cpp->csr2 = cpp->csr2 | ka62aCSR2_ERR;
	}
	splx(spl);
	return(0);
}
#endif	VAX6200

/*
 *	Check for a bad address not only by a machine check but also
 *	a BI error (necessary on 8800).
 *	On the 8800 unibus adaptor badaddr returns 0 (=> no nxm) but there is an
 *	RDS outstanding on the "B card", to indicate an error.
 */
bi_badaddr(addr, size)
	caddr_t	addr;
	int	size;
{
	register int spl = splblock();
	register int ret = 0;

#if	VAX8800
	if (cpu == VAX_8800) {
		register struct bi_node *biv  = ioanode[nioa].bddr;

		biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
		check_bi->ber = (check_bi->ber & BER_ERR) | BER_UPEN;
	}
#endif	VAX8800

	if (badaddr(addr, size)) {
#if	VAX8800
		if (cpu == VAX_8800) {
			register struct bi_node *biv  = ioanode[nioa].bddr;
			register struct nbi *nbip = ioanode[nioa].addr88;
			register int	dest;
			register struct mcl *mp= memnode[0].addr88;

			if (biv) {
				biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
				if (check_bi != biv && (caddr_t) check_bi != addr) {
					check_bi->ber = (check_bi->ber & BER_ERR) | BER_UPEN;
				}
			}
			nbip->csr0 = nbip->csr0;
			nbip->csr1 = nbip->csr1;
			dest = mp->csr4;
			dest = mp->csr5;
			mp->csr0 = mp->csr0 & MCLCSR0_TMOUT;
			mtpr(TOSTS, 0);
			mtpr(MCSTS, 0);
		} else
#endif	VAX8800
#if	VAX6200
		if (cpu == VAX_6200) {
			register struct dwmba *dwp = ioanode[nioa].addr62;
			register struct bi_node *biv  = ioanode[nioa].bddr;
			register struct ka62a *cpp = cpunode[cpu_number()].addr62;

			if (biv) {
				biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
				if (check_bi != biv && (caddr_t) check_bi != addr) {
					check_bi->ber = (check_bi->ber & BER_ERR) | BER_UPEN;
				}
			}
			if ((int) dwp) {
				dwp->ber = dwp->ber & BER_ERR;
				dwp->aesr = dwp->aesr & AESR_ERR;
				dwp->besr = dwp->besr & BESR_ERR;
			}
			if ((int) cpp) {
				cpp->ber = cpp->ber & XMIBER_ERR;
				cpp->csr2 = cpp->csr2 | ka62aCSR2_ERR;
			}
		} else
#endif	VAX6200
#if	VAX820
		if (cpu == VAX_820) {
			register struct bi_node *biv  = ioanode[nioa].bddr;

			if (biv) {
				biv->ber = biv->ber & BER_ERR;
				if (check_bi != biv && (caddr_t) check_bi != addr) {
					check_bi->ber = (check_bi->ber & BER_ERR) | BER_UPEN;
				}
			}
			mtpr(MCESR, 0);
		}
#endif	VAX820
		splx(spl);
		return(1);
	}

#if	VAX8800
	if (cpu == VAX_8800) {
		register struct bi_node *biv  = ioanode[nioa].bddr;
		register struct nbi *nbip = ioanode[nioa].addr88;
		register int	dest;
		register struct mcl *mp= memnode[0].addr88;

		if (biv) {
			if (biv->ber & BER_ERR)
				ret = 1;
			biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
			if (check_bi != biv && (caddr_t) check_bi != addr) {
				check_bi->ber = (check_bi->ber & BER_ERR) | BER_UPEN;
			}
		}
		nbip->csr0 = nbip->csr0;
		nbip->csr1 = nbip->csr1;
		dest = mp->csr4;
		dest = mp->csr5;
		mp->csr1 = mp->csr1 & MCLCSR0_TMOUT;
		mtpr(TOSTS, 0);
	} else
#endif	VAX8800
#if	VAX6200
	if (cpu == VAX_6200) {
		register struct dwmba *dwp = ioanode[nioa].addr62;
		register struct bi_node *biv  = ioanode[nioa].bddr;
		register struct ka62a *cpp = cpunode[cpu_number()].addr62;

		if (biv) {
			biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
			if (check_bi != biv && (caddr_t) check_bi != addr) {
				check_bi->ber = (check_bi->ber & BER_ERR) | BER_UPEN;
			}
		}
		if ((int) dwp) {
			dwp->ber = dwp->ber & XMIBER_ERR;
			dwp->aesr = dwp->aesr & AESR_ERR;
			dwp->besr = dwp->besr & BESR_ERR;
		}
		if ((int) cpp) {
			cpp->ber = cpp->ber & XMIBER_ERR;
			cpp->csr2 = cpp->csr2 | ka62aCSR2_ERR;
		}
	} else
#endif	VAX6200
#if	VAX820
	if (cpu == VAX_820) {
		register struct bi_node *biv  = ioanode[nioa].bddr;

		if (biv) {
			biv->ber = biv->ber & BER_ERR;
			if (check_bi != biv && (caddr_t) check_bi != addr) {
				check_bi->ber = (check_bi->ber & BER_ERR) | BER_UPEN;
			}
		}
		mtpr(MCESR, 0);
	} else
#endif	VAX820
	/* nothing else */;

	splx(spl);
	return(ret);
}

bi_badaddr_end()
{
}

bi_err(pc, psl, ioabi)
{

register int ioa = ioabi >> 4;
register int bi  = ioabi & 0xf;
register struct bi_node *biv = ioanode[ioa].bi[bi];
register struct bi_node *bivc;

	printf("bi_err(pc %x, psl %x, ioa %x, bi %x, biv %x)\n", pc, psl, ioa, bi, biv);

	if (!(int) biv) {
		printf("Node interrupted too early.\n");
	} else if (bi == ioanode[ioa].bnode) {
		printf("See Bcard below.\n");
	} else {
		pbi(biv);
		biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
	}

	switch(cpu) {
	case VAX_820:
		if (biv->dev_type == BI_KA820)
			break;
		biv = cpunode[master_cpu].addr82;
		printf("master cpu = Node%x\tV %x\n", master_cpu, biv);
		pbi(biv);
		biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
		break;
	case VAX_6200:
		xmi_err(0, 0, ioa);
		break;
	case VAX_8800:
		nmi_err(0, 0, ioa);
		break;
	}
}

#define DELAYnSEC(x) DELAY(x*454545);
		/*
		 * On the the scan_bix pass, we reset all the kdb50's (and
		 * clearly there must be atleast one.  So now we must wait
		 * for the adaptors to quiet down.
		 */
bi_settle()
{
	printf("Waiting 10 sec for kdb50 node resets to settle.\n");
	DELAYnSEC(10);
}

bi_node_reset(bi)
register struct bi_node *bi;
{
	/*
	 * Should we worry about the IPINTR stuff?
	 * No for now.
	 */
	int uintrcsr = bi->uintrcsr;
	int eintrcsr = bi->eintrcsr;
	int intrdes = bi->intrdes;
	int bcicsr = bi->bcicsr;
	int sadr = bi->sadr;
	int eadr = bi->eadr;

/*
 *	Below is what I was told should be done to reset a bi node.
 *	Unfortunately, the dwbma sees an IOWFAIL and we get an WEI
	bi->bicsr = BICSR_ARB_MASK;
	bi->bicsr = BICSR_NRST | BICSR_STS | BICSR_ARB_MASK;
*/
	bi->bicsr |= BICSR_NRST;

	DELAYnSEC(10);		/* 10 sec I am told */

	bi->uintrcsr = uintrcsr;
	bi->eintrcsr = eintrcsr;
	bi->intrdes = intrdes;
	bi->bicsr |= BICSR_HEIE | BICSR_SEIE;
	bi->bcicsr = bcicsr;

	bi->sadr = sadr;
	bi->eadr = eadr;
}

#define PR(str,ptr) printf("\t%s \t%x\n", str, ptr)
#define Pb(str,ptr,bits) printf("\t%s \t%b\n", str, ptr, bits)
#define Pval(str,ptr) if (ptr || p0val) PR(str, ptr)
#define Pvalb(str,ptr,bits) if (ptr || p0val) Pb(str,ptr,bits)
int p0val = 0;

pbi(bip)
register struct bi_node *bip;
{
	Pval("Device Type\t\t", bip->dev_type);
	Pval("Device Revision\t\t", bip->dev_rev);
	Pb("BI Control and Status\t", bip->bicsr, BICSR);
	Pb("Bus Error Register\t", bip->ber, BER);
	Pb("Error Intr Control Register", bip->eintrcsr, EINTRCSR);
	Pb("BCI Control and Status Reg", bip->bcicsr, BCI);
	PR("Interrupt Dest Register", bip->intrdes);
	Pb("User Interface Interrupt Cntl", bip->uintrcsr, UINTRCSR);
	PR("Starting Address Register", bip->sadr);
	PR("Ending Address Register", bip->eadr);
	PR("IPINTR Mask Register\t", bip->ipintrmsk);
	PR("Force-bit IPINTR/STOP Dest", bip->fipdes);
	PR("IPINTR Source\t\t", bip->ipintrsrc);
	Pb("Force-bit IPINTR/STOP Command", bip->fipscmd, FIPSCMD);
	Pb("Write Status Register\t", bip->wstat, WSTAT);
	Pval("General purpose Registers 0", bip->gpr[0]);
	Pval("General purpose Registers 1", bip->gpr[1]);
	Pval("General purpose Registers 2", bip->gpr[2]);
	Pval("General purpose Registers 3", bip->gpr[3]);
}
