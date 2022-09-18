/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/*
 * HISTORY
 * $Log:	biconf.c,v $
 * Revision 2.6  93/05/15  18:57:51  mrt
 * 	machparam.h -> machspl.h
 * 
 * Revision 2.5  91/05/14  17:41:41  mrt
 * 	Correcting copyright
 * 
 * Revision 2.4  91/05/08  13:13:55  dbg
 * 	Include vax/machparam.h for SPL definitions.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.3  91/03/16  15:01:59  rpd
 * 	Updated for new kmem_alloc interface.
 * 	[91/03/03            rpd]
 * 
 * Revision 2.2  90/01/11  11:44:52  dbg
 * 	8200 needs to have the KDB reset code run in the cache and wait
 * 	a while - we are resetting the bus that we fetch instructions
 * 	from!
 * 	[90/01/04            dbg]
 * 
 * 	Mangled for MACH_KERNEL.
 * 	[88/11/14            dbg]
 * 
 * Revision 2.1  89/08/03  16:22:51  rwd
 * Created.
 * 
 * Revision 2.4  88/10/11  13:05:40  rpd
 * 	New functions:
 * 		1) bi_node_reset(bi) to handle reseting a node while
 * 	saving/restoring its state.
 * 		2) bi_settle() waits for 10sec so the raw NRST to the
 * 	kdb50 nodes will finish.
 * 	bi_settle() is called once just before the probe_bi's are done.
 * 	Thus ud{,a}init will no longer have to do the node reset.
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
 * 	Don't start slaves if RB_UNIPROC is true.
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

#include <bi.h>
#include <ni.h>
#include <ra.h>
#include <uba.h>

#if	NBI > 0

#include <kern/cpu_number.h>
#include <mach/machine.h>

#include <vm/vm_kern.h>

#include <device/dk.h>

#include <vax/cpu_data.h>
#include <vax/bi_node.h>
#include <vax/node.h>
#include <vax/io_map.h>
#include <vax/scb.h>
#include <vax/vm_defs.h>
#include <vax/machspl.h>

#if	NUBA > 0
#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>
#endif

#if	VAX6200
#include <vax/ka6200.h>
#endif	VAX6200

#define	NNODES	16
			/* XXX */
int	ncpu;				/* number of cpus */
struct cpu_node	cpu_node[NNODES];	/* CPUs */
int	nmem;				/* number of memory controllers */
struct mem_node	mem_node[NNODES];
int	nioa;				/* number of IO adaptors */
struct ioa_node	ioa_node[NNODES];

int	max_cpus = NCPUS;		/* maximum configured -
					   patch for testing */
int	nbi;		/* current BI node */
int	numkdb;		/* number of KDB50s */
int	numni;		/* number of NIs */
int	intmask;	/* mask to interrupt master CPU */

#define	bi_int(nioa, node_num) \
	(((int)&biscb - (int)&scb + 64*nioa + 4*node_num)+0x80000)

extern char *	biscb;

#if	NRA > 0

extern int Xkdb0int(), Xkdb1int(), Xkdb2int(), Xkdb3int();
int	(*kdb50intv[4])() = 	{ Xkdb0int, Xkdb1int, Xkdb2int, Xkdb3int };
#endif	NRA > 0

#if	NNI > 0
extern int Xni0int();
int	(*niintv[1])() =	{ Xni0int };
#endif	NNI > 0

void scan_bix(ioa)
	struct ioa_node	*ioa;
{
	struct bi_node	*bip = (struct bi_node *)ioa->bi_paddr;
	struct bi_node	*biv;

	int	node_num, dev_type;

	biv = (struct bi_node *) io_map((vm_offset_t)bip,
		     BI_MAX_NODE * sizeof(struct bi_node));
	ioa->bi_vaddr = biv;

	for (node_num = 0;
	     node_num < BI_MAX_NODE;
	     node_num++, biv++, bip++) {

	    if (bi_badaddr((char *)biv, sizeof(int), nioa, biv))
		continue;

	    dev_type = biv->dev_type;
	    if (dev_type != BI_MEM && (biv->bicsr & BICSR_BROKE))
		continue;

	    switch (dev_type) {
#if	VAX6200
		case BI_XMI:
		case BI_XMI | 0x2000:
		case BI_XMI | 0x4000:
		    printf("\tBI-X @Node%x V/P %x/%x\n",
			   node_num,
			   biv,
			   bip);

		    ioa->bi_present |= (1 << node_num);
		    ioa->bddr = biv;		/* loopback */
		    ioa->bnode = node_num;

		    biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
		    biv->eintrcsr = bi_int(nioa, node_num);
		    biv->intrdes = 1 << node_num;
		    biv->bicsr |= BICSR_HEIE | BICSR_SEIE;

		    biv->bcicsr = BCI_RTOEVEN | BCI_INTREN;
		    biv->sadr = 0;
		    biv->eadr = mem_size;
		    break;
#endif	VAX6200
#if	VAX8800
		case 0xffff:	/* uninitialized NMI/BI adaptor */
		    biv->dev_type = BI_NBI;
		    /* fall through ... */
		case BI_NBI:
		    printf("\tBI-X @Node%x V/P %x/%x\n",
			   node_num,
			   biv,
			   bip);

		    ioa->bi_present |= (1 << node_num);
		    ioa->bddr = biv;		/* loopback */
		    ioa->bnode = node_num;

		    /*
		     * If we enable interrupts now, we will get hit
		     * with non-existent memory interrupts when we probe
		     * even if bi_badaddr clears ber before it lowers
		     * priority.
		     */
		    biv->eintrcsr = bi_int(nioa, node_num);
		    biv->intrdes = 1 << node_num;
		    biv->bicsr |= BICSR_BROKE;	/* clear broke bit */

		    biv->bcicsr |= BCI_INTREN;
		    biv->sadr = 0;
		    biv->eadr = mem_size;

		    biv->ipintrmsk = 0xffff0000;
		    break;
#endif	VAX8800
		case BI_KDB50:
#if	VAX820
		    /*
		     * We are resetting the bus that we access memory over.
		     * Run in cache while we reset the bus.
		     * Execute the loop once before reset to get the entire
		     * loop in the cache.
		     */
		    if (cpu == VAX_820) {
			register int	i;

			for (i = -1; i < 100; ) {
			    i++;
			    if (i == 0)
				biv->bicsr |= BICSR_NRST;
			}
		    }
		    else
#endif	VAX820
		    biv->bicsr |= BICSR_NRST;
		    /* fall through */
		case BI_DR32:
		case BI_KLESI:
		case BI_CI:
		case BI_DXX32:
		case BI_CIOBS:
		case BI_TK50:
		case BI_DEBNA:
		case BI_UBA:
		    /* not needed on this pass */
		    break;

#if	VAX820
		case BI_KA820:
		    printf("CPU %x: KA820 %x/%x %x ",
			   node_num,
			   biv,
			   bip,
			   dev_type);

		    ioa->bi_present |= (1 << node_num);

		    ncpu++;
		    if (node_num >= NCPUS || ncpu > max_cpus) {
			printf("not configured\n");
			break;
		    }

		    cpu_node[node_num].addr = (char *)biv;
		    cpu_node[node_num].node = node_num;

		    machine_slot[node_num].is_cpu = TRUE;
		    machine_slot[node_num].cpu_type = CPU_TYPE_VAX;
		    machine_slot[node_num].cpu_subtype = CPU_SUBTYPE_VAX8200;

		    /*
		     * Enable interrupt on errors, sending them to
		     * them to the master CPU.
		     */
		    biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
		    biv->eintrcsr = bi_int(nioa, node_num);
		    biv->intrdes = intmask;	/* interrupt master */
		    biv->bicsr |= BICSR_SEIE | BICSR_HEIE;

		    /*
		     * Let anyone send this CPU interprocessor interrupts.
		     */
		    biv->ipintrmsk = 0xffff0000;

		    if (node_num == master_cpu) {
			ioa->bnode = node_num;
			ioa->bddr = biv;
			printf("MASTER.\n");
		    }
		    else
			printf("\n");
		    break;

		case BI_MEM:
		    printf("MEM %x:       %x/%x   %x %d Meg .. %d Meg\n",
			   node_num,
			   biv,
			   bip,
			   dev_type,
			   biv->sadr >> 20,
			   biv->eadr >> 20);
		    mem_node[nmem].addr = (char *)biv;
		    mem_node[nmem].node = node_num;
		    nmem++;

		    ioa->bi_present |= (1 << node_num);

		    break;
#endif	VAX820
	    }
	}
}

probe_bi(ioanum, bus, focus)
	int	ioanum;
	int	bus;
	int	focus;
{
	register struct ioa_node *ioa = &ioa_node[ioanum];
	register struct bi_node *biv = ioa->bi_vaddr;
	struct bi_node		*bip = ioa->bi_paddr;
	int			node_num,
				dev_type;
	char *			tab;

	tab = bus ? "    " : "";
	printf("BI%d                  /%x\n", nbi, bip);

	for (node_num = 0;
	     node_num < BI_MAX_NODE;
	     node_num++, biv++, bip++) {

	    if (ioa->bi_present & (1<<node_num)) {
		/* already configured this node */
		continue;
	    }

	    if (bi_badaddr((char *)biv, sizeof(int), ioanum, biv))
		continue;

	    dev_type = biv->dev_type;
	    if (dev_type == 0) {
		/*
		 * 8800 seems to return this for nodes that do not
		 * exist
		 */
		continue;
	    }
	    if (dev_type != BI_MEM && biv->bicsr & BICSR_BROKE) {
		printf("NODE %x TYPE %x FAILED SELF TEST, bicsr = %x\n",
			node_num,
			dev_type,
			biv->bicsr);
		continue;
	    }

	    switch (dev_type) {
		case BI_XMI:
		case BI_XMI|0x2000:
		case BI_XMI|0x4000:
		case BI_NBI:
		case 0xffff:	/* uninitialized NMI/BI adapter */
		case BI_KA820:
		case BI_MEM:
		    /* got these on first pass */
		    break;
		case BI_UBA:
		{
		    extern int	numuba;

		    printf("%snode %x:  %x/%x %x uba%d\n",
			   tab,
			   node_num,
			   biv,
			   bip,
			   dev_type,
			   numuba);

		    ioa->bi_present |= (1 << node_num);

		    if (numuba >= NUBA) {
			printf("%s%d uba's not configured\n",
				tab,
				++numuba);
			break;
		    }

		    /*
		     * Enable interrupts.
		     * Select high priority arbitration.
		     */
		    biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
		    biv->eintrcsr = bi_int(nioa, node_num);
		    biv->intrdes = focus;
		    biv->bicsr |= BICSR_HEIE | BICSR_SEIE;

		    biv->bicsr = (biv->bicsr & ~BICSR_ARB_MASK)
				| BICSR_ARB_HIGH;

		    /*
		     * Probe the Unibus.
		     */
		    probe_dwbua((struct dwbua_regs *)biv,
				(struct dwbua_regs *)bip,
				(caddr_t) ioa->bi_paddr + 
				    UMEMBI_OFFSET(node_num));
		    break;
		}

		case BI_KDB50:
		    printf("%snode %x:  %x/%x %x kdb%d\n",
			   tab,
			   node_num,
			   biv,
			   bip,
			   dev_type,
			   numkdb);

		    ioa->bi_present |= (1 << node_num);

#if	NRA > 0
		    biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
		    biv->eintrcsr = bi_int(nioa, node_num);
		    biv->intrdes = focus;
		    biv->bicsr |= BICSR_HEIE | BICSR_SEIE;

		    kdb50_find(biv, bip, node_num, tab);
		    numkdb++;
#else
		    printf("not supported\n");
#endif
		    break;

		case BI_DEBNA:
		    printf("%snode %x:  %x/%x %x ni%d\n",
			   tab,
			   node_num,
			   biv,
			   bip,
			   dev_type,
			   numni);

		    ioa->bi_present |= (1 << node_num);

#if	NNI > 0
		    biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
		    biv->eintrcsr = bi_int(nioa, node_num);
		    biv->intrdes = focus;
		    biv->bicsr |= BICSR_HEIE | BICSR_SEIE;

		    if (biv->dev_rev != 0x023b)
			printf("NI: Warning -- revision level changed\n");
		    if ((biv->dev_rev & 0xff) < 0x3b)
			printf("NI: Error -- Old revision found\n");
		    if (ni_to_bi_attach(nbi, node_num, numni, biv))
			numni++;
		    else
			printf("ni%d not configured\n", numni);
#else
		    printf("ni not supported\n");
#endif
		    break;

		default:
		    printf("%snode %x:  %x/%x %x ",
			   tab,
			   node_num,
			   biv,
			   bip,
			   dev_type);
		    printf("not supported\n");
		    break;
	    }
	}
	nbi++;
}

#if	NRA > 0
/*
 * Find a KDB50.  Imitates unifind.
 */
kdb50_find(biv, bip, node_num, tab)
	struct bi_node	*biv;
	struct bi_node	*bip;
	int		node_num;
	char *		tab;
{
	register struct uba_ctlr *	um;
	register struct uba_device *	ui;
	register struct uba_driver *	udp;
	caddr_t				reg;

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
		if (um->um_ubanum != numuba && um->um_ubanum != '?')
			continue;

		reg = ((caddr_t)biv) + 0xf2;	/* offset */
		*((int *)(((caddr_t)&scb)+(0x140+node_num*4))) =
			(int)scbentry(kdb50intv[um->um_ctlr], SCB_ISTACK);
		biv->uintrcsr = 0x140+node_num*4;
		udaiskdb50(um->um_ctlr, biv, 0x140+node_num*4);

		/*
		 * WARNING: this probe only works with the UMD uda driver.
		 */
		(*udp->ud_probe)(0, um->um_ctlr, um);

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
		uhp->uh_type = UBA_MR_ONLY;
		/*
		 *	One MACH page is probably big enough
		 *	to hold all the mapping registers
		 *	(512*4)...
		 */
		(void) kmem_alloc_wired(kernel_map, &mapptr,
					NUBMREG*sizeof(struct pte));
		uhp->uh_uba = (struct uba_regs *)(mapptr - 0x800);
		uhp->uh_physuba = (struct uba_regs *)
					(pmap_extract(pmap_kernel(), mapptr) -
						0x800);
		uhp->uh_mr = (struct pte *)mapptr;
		uhp->uh_memsize = UBAPAGES;
				/* how much UBA space we get to map */

		(void) kmem_alloc_wired(kernel_map,
					(vm_offset_t *) &uhp->uh_map,
					UAMSIZ * sizeof (struct map));
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
}
#endif	NRA > 0

boolean_t bi_badaddr(addr, size, ioa_number, check_bi)
	char *	addr;
	int	size;
	int	ioa_number;
	struct bi_node *check_bi;
{
	register int spl;
	register struct bi_node *biv = ioa_node[ioa_number].bddr;

	spl = splblock();

	if (badaddr(addr, size)) {
	    if (biv) {
		biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
		if (check_bi != biv && (char *)check_bi != addr)
		    check_bi->ber = (check_bi->ber & BER_ERR) | BER_UPEN;
	    }
	    (*cpu_model->m_clear_mchk)(ioa_number);
	    splx(spl);
	    return (TRUE);
	}
	if (check_bi) {
	    if (check_bi->ber & BER_ICE) {
		check_bi->ber |= BER_ICE;
		(*cpu_model->m_clear_mchk)(ioa_number);
		splx(spl);
		return (TRUE);
	    }
	}

	splx(spl);	/* may get wtime interrupt here */
	return (FALSE);
}

bi_badaddr_end()
{
}

bi_bus_error()
{
	/* XXX */
}

bi_err(pc, psl, ioabi)
{
	register int ioa	= ioabi >> 4;
	register int bi		= ioabi & 0xf;

	register struct bi_node *biv;

	printf("bi_err (pc %x, psl %x, ioa %d, bi %d ",
		pc, psl, ioa, bi);

	if ((ioa_node[ioa].bi_present & (1 << bi)) == 0) {
	    printf("... node interrupted too early\n");
	    return;
	}

	biv = &ioa_node[ioa].bi_vaddr[bi];
	printf(" at %x) \n", biv);

	if (bi == ioa_node[ioa].bnode) {
	    printf("See Bcard below.\n");
	}
	else {
	    print_bi(biv);
	    biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
	}

	switch (cpu) {
#if	VAX820
	    case VAX_820:
		biv = (struct bi_node *)cpu_node[master_cpu].addr;
		printf("master cpu = Node %x\t V %x\n", master_cpu, biv);
		print_bi(biv);
		biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
		break;
#endif
#if	VAX6200
	    case VAX_6200:
		xmi_err(0, 0, ioa);
		break;
#endif
#if	VAX8800
	    case VAX_8800:
		nmi_err(0, 0, ioa);
		break;
#endif
	}
}

#define	DELAYnSEC(x) DELAY(x*454545);
/*
 * On the the scan_bix pass, we reset all the kdb50's (and
 * clearly there must be at least one).  So now we must wait
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


/*
 * Diagnostic print routines for various BI errors.
 */
#define PR(str,ptr) printf("\t%s \t%x\n", str, ptr)
#define Pb(str,ptr,bits) printf("\t%s \t%b\n", str, ptr, bits)
#define Pval(str,ptr) if (ptr || p0val) PR(str, ptr)
#define Pvalb(str,ptr,bits) if (ptr || p0val) Pb(str,ptr,bits)
int p0val = 0;

print_bi(biv)
register struct bi_node *biv;
{
	Pval("Device Type\t\t", biv->dev_type);
	Pval("Device Revision\t\t", biv->dev_rev);
	Pb("BI Control and Status\t", biv->bicsr, BICSR);
	Pb("Bus Error Register\t", biv->ber, BER);
	Pb("Error Intr Control Register", biv->eintrcsr, EINTRCSR);
	Pb("BCI Control and Status Reg", biv->bcicsr, BCI);
	PR("Interrupt Dest Register", biv->intrdes);
	Pb("User Interface Interrupt Cntl", biv->uintrcsr, UINTRCSR);
	PR("Starting Address Register", biv->sadr);
	PR("Ending Address Register", biv->eadr);
	PR("IPINTR Mask Register\t", biv->ipintrmsk);
	PR("Force-bit IPINTR/STOP Dest", biv->fipdes);
	PR("IPINTR Source\t\t", biv->ipintrsrc);
	Pb("Force-bit IPINTR/STOP Command", biv->fipscmd, FIPSCMD);
	Pb("Write Status Register\t", biv->wstat, WSTAT);
	Pval("General purpose Registers 0", biv->gpr[0]);
	Pval("General purpose Registers 1", biv->gpr[1]);
	Pval("General purpose Registers 2", biv->gpr[2]);
	Pval("General purpose Registers 3", biv->gpr[3]);
}
#endif	NBI > 0
