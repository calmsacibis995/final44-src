/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ka88.c,v $
 * Revision 2.4  89/04/05  13:04:38  rvb
 * 	More complete error recovery.
 * 	[89/02/28            rvb]
 * 
 * Revision 2.3  89/02/26  10:58:50  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/10  10:51:03  rvb
 * 	Created
 *
 */
/*
 *	File:	ka88.c
 *	Author:	Robert V. Baron
 *
 *	Support for the 6200
 */
#include <cputypes.h>
#if	VAX8800
#include <cpus.h>

#include <sys/param.h>
#include <mach/machine.h>
#include <vm/vm_kern.h>
#include <vax/cpu.h>
#include <vax/mtpr.h>
#include <vaxnb/ka88.h>
#include <vax/bi_node.h>
#include <vaxnb/node.h>

#include <sys/conf.h>		/* for linesw */
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <vax/cons.h>

caddr_t nmi_nbia_addr[4] = {
		NMI_NBI+0*NMI_NBI_SZ+NMI_NBIA, NMI_NBI+0*NMI_NBI_SZ+NMI_NBIA,
		NMI_NBI+2*NMI_NBI_SZ+NMI_NBIA, NMI_NBI+2*NMI_NBI_SZ+NMI_NBIA
		};

caddr_t nmi_bi_addr[4] = {
		NMI_NBI+0*NMI_NBI_SZ, NMI_NBI+1*NMI_NBI_SZ,
		NMI_NBI+2*NMI_NBI_SZ, NMI_NBI+3*NMI_NBI_SZ
		};

static char *mcl_size_code[] = {"   ", "res", "res", " 4M", " 8M", "16M", "32M", "cap"};
static int mcl_size_val[] = { 0, 0, 0, 4, 8, 16, 32, 0};
static int nmi_badaddr();

ka88_init()
{
	mtpr(COR, 1);
	/*
	 pka88();
	 */
}

ka88_conf()
{
	register caddr_t	node;		/* node's phys addr */
	register int		i;
	int			need_vm = 1;	/* implies need more vm */
	caddr_t			va;
	struct	xmi		*xmi;
	union cpusid cpusid;

	cpusid.cpusid = mfpr(SID);
	cpuspeed = 8;
	printf("VAX 8800\n");
	printf("CPU 0\n");
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
	machine_slot[1].is_cpu = TRUE;
	vax_putc(0);		/* wait for console to come ready */
/*	subtype = CPU_SUBTYPE_VAX8800;/
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

		printf("MEM 0 V/P %x/%x", nmp, NMI_MCL);
		pms88_size();
	}
	for (i = 0; i < 4; i++)	{
		struct ioanode *ioap = &ioanode[nioa];
		struct nbi *ip;
		if (need_vm) {
			va = (caddr_t)kmem_alloc_pageable(kernel_map, NBPG);
			if (va == 0)
				panic("new_configure");
			need_vm = 0;
		}
		ioaccess(nmi_bi_addr[i], va, NBPG);
		if (nmi_badaddr(va, 4))		/* no bi space */
			continue;
		ioaccess(nmi_nbia_addr[i], va, NBPG);
		if (nmi_badaddr(va, 4))
			continue;

		need_vm++;
		ip = (struct nbi *) va;

		/* Remember stuff */
		ioap->addr88 = ip;
		ioap->node = i;
		ioap->bi_addr = (caddr_t) nmi_bi_addr[i];

		/* 
		 * As soon as we enable, we see a power interrupt
		 * unless...
		 */
		ip->csr1 |= (NBIACSR1_BI0PWR | NBIACSR1_BI1PWR);
		ip->csr0 |= NBIACSR0_IE;		/* interrupt enable */

		printf("IOA %x V/P %x/%x",
			i, ip, nmi_nbia_addr[i]);
		scan_bix(ioap);
		nioa++;
	}
	if (!need_vm)
    	 	 kmem_free(kernel_map, va, NBPG);

	for (i = nioa, nioa = 0; nioa < i; nioa++) {
		struct ioanode *ioap = &ioanode[nioa];
		struct bi_node *biv = ioap->bddr;

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

static nmi_badaddr(addr, size)
{
	register int spl = splblock();
	if (badaddr(addr, size)) {
		mtpr(TOSTS, 0);
		mtpr(MCSTS, 0);
		splx(spl);
		return(1);
	}
	splx(spl);
	return(0);
}

int	mcheck_skips = 0;

mchk_ka88(cmcf)
caddr_t cmcf;
{
struct mc8800frame {
	int	mc88_bcnt;		/* byte count = 0x20 */
	int	mc88_mcsts;		/* machine check status register */
	int	mc88_mpc;		/* micro pc */
	int	mc88_va;		/* va register */
	int	mc88_iber;		/* ibox error register */
	int	mc88_cber;		/* cbox error register */
	int	mc88_eber;		/* ebox error register */
	int	mc88_nmifsr;		/* nmi fault summary register */
	int	mc88_nmiear;		/* nmi error address register */
	int	mc88_pc;		/* current PC */
	int	mc88_psl;		/* current PSL */
};
	register struct mc8800frame *mcf = (struct mc8800frame *)cmcf;

	/*
	 *	For reasons which I do not understand, the 8800
	 *	seems to take lots of unnecessary machine checks
	 *	so for now, ignore them (some of them anyway).
	 */
	if (mcf->mc88_nmifsr == 0xc0000) {
		printf("spurious machine check\n");
		pka88();
		mtpr(TOSTS, 0);
		mtpr(MCSTS, 0);
		mcheck_skips++;
		return;
	}

	printf("mcsts %x mpc %x va %x\n", mcf->mc88_mcsts,
		mcf->mc88_mpc, mcf->mc88_va);
	printf("ibox %b\n", mcf->mc88_iber, IBOX);
	printf("cbox %b\n", mcf->mc88_cber, CBOX);
	printf("ebox %b\n", mcf->mc88_eber, EBOX);
	printf("nmifsr %b\n", mcf->mc88_nmifsr, NMIFSR_B);
	printf("nmiear %x\n", mcf->mc88_nmiear, NMIEAR_B);
	printf("pc %x psl %x\n", mcf->mc88_pc, mcf->mc88_psl);
	pka88();
	printf("halting...\n");
	mtpr(TOSTS, 0);
	mtpr(MCSTS, 0);
	asm("halt");
	return;
}

crd_ka88()
{
	printf("ka88_crd\n");
	pka88();
	pms88();
}

nmi_fault()
{
	register int	dest;
	register struct mcl *mp= memnode[0].addr88;

	printf("nmi fault:");
	pka88();
	pms88();
	dest = mp->csr4;
	dest = mp->csr5;
	mp->csr0 = mp->csr0 & MCLCSR0_TMOUT;
}

nbib_error(which)
	int	which;
{
	register struct nbi *nbip = ioanode[which<<1].addr88;

	printf("nbib_error\n");
	pka88();
	pnbi(nbip);
	nbip->csr0 = nbip->csr0;
	nbip->csr1 = nbip->csr1;
}

nmi_err(pc, psl, ioa)
{
	register struct nbi *nbip = ioanode[ioa].addr88;
	register struct ioanode *ioap = &ioanode[ioa];
	register struct bi_node *biv  = ioanode[ioa].bddr;

	if (pc)
		printf("nmi_err(pc %x, psl %x, ioa %x)\n", pc, psl, ioa);
/*	else
		it was called by bi_err */

	if ((int) nbip) {
		register int	dest;

		printf("Bcard Node %x V %x\n",
			ioap->bnode, biv);
		pbi(biv);
		biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
		printf("IOA %x\tNODE %x\tBNODE %x\t A/B %x/%x PHYS %x\n",
			ioa, ioap->node, ioap->bnode, ioap->addr88, biv, ioap->bi_addr);
		pnbi(nbip);
		nbip->csr0 = nbip->csr0;
		nbip->csr1 = nbip->csr1;
	}

	printf("CPU = Node%x\n", master_cpu);
	{
		register struct mcl *mp= memnode[0].addr88;
		register int	dest;

		pka88();
		dest = mp->csr4;
		dest = mp->csr5;
		mp->csr0 = mp->csr0 & MCLCSR0_TMOUT;
		mtpr(TOSTS, 0);
	}
}

/*
 *	Handle a command received from the console.
 */
nautilus_cin(c)
	register int	c;
{
	register int		id;
	register struct tty	*tp;
	extern struct tty	cons;

	tp = &cons;
	id = c&RXDB_ID;
	switch (id) {
	/* Remote console input */
	case 0x300:
	case 0x600:
		(*linesw[tp->t_line].l_rint)(c&0177, tp);
		return;
	}
	printf("unexpected nautilus input: c = 0x%x.\n", c);
	asm("halt");
}

nautilus_cout()
{
}

#define PR(str,ptr) printf("\t%s \t%x\n", str, ptr)
#define Pb(str,ptr,bits) printf("\t%s \t%b\n", str, ptr, bits)
#define Pval(str,ptr) if (ptr || p0val) PR(str, ptr)
#define Pvalb(str,ptr,bits) if (ptr || p0val) Pb(str,ptr,bits)
extern int p0val;

static int pka88ed = 0;
pka88()
{
register int tmp;

	tmp = mfpr(MCSTS);
	Pb("Machine Check Status Register", tmp, C88MCSTS);

	/* Write Only
	  tmp = mfpr(NICTRL);
	  Pb("NMI Interrupt Control Register", tmp, NICTRL_B);
	*/

	tmp = mfpr(NMIFSR);
	Pb("NMI Fault Summary Register", tmp, NMIFSR_B);

	tmp = mfpr(NMISILO);
	Pb("NMI Silo Data Register ", tmp, NMISILO_B);

	tmp = mfpr(NMIEAR);
	Pb("NMI Error Address Register", tmp, NMIEAR_B);

	tmp = mfpr(COR);
	Pb("Cache Enable(On) Register", tmp, C88COR);

	if (!(++pka88ed)) {
		tmp = mfpr(REVR1);
		Pb("Revision Register 1", tmp, C88REVR1);

		tmp = mfpr(REVR2);
		Pb("Revision Register 2", tmp, C88REVR2);
	}

	/* Apparently also Write Only
	  tmp = mfpr(TOSTS);
	  Pval("TimeOut Status Register", tmp);
	 */
}

pms88()
{
register struct mcl *mp= memnode[0].addr88;

	printf("MEM  %x/%x\n", mp, NMI_MCL);

	Pb("MCL CSR 0", mp->csr0, MCLCSR0);
	Pb("MCL SR  1", mp->csr1, MCLSR1);
	Pb("MCL CSR 1", mp->csr1, MCLCSR1);
	Pb("MCL CSR 2", mp->csr2, MCLCSR2);
	Pb("MCL CSR 3", mp->csr3, MCLCSR3);
}

pms88_size()
{
register struct mcl *mp= memnode[0].addr88;
register int tmp;
register int i;
register int no;
register int sum = 0;

	for (i=0, tmp = mp->csr3; i < 8; i++, tmp >>= 3) {
		no = tmp & MCLCSR3_MSK;
		sum += mcl_size_val[no];
	}
	printf("	%dM: ", sum);
	for (i=0, tmp = mp->csr3; i < 8; i++, tmp >>= 3) {
		no = tmp & MCLCSR3_MSK;
		if (mcl_size_val[no])
			printf("%d - %s, ", i, mcl_size_code[no]);
	}
	printf("\n");
}

pnbi(nbiap)
	register struct nbi *nbiap;
{
	register caddr_t phys = (caddr_t)pmap_extract(kernel_pmap, nbiap);

	printf("ADAPTOR %x V/P %x/%x\n",
		phys == nmi_nbia_addr[0] ? 0 : 1,
		nbiap,
		phys);
	Pb("NBIA CSR0", nbiap->csr0, NBIACSR0);
	Pb("NBIA CSR1", nbiap->csr1, NBIACSR1);
	Pval("NBIA BR4", nbiap->br4vr);
	Pval("NBIA BR5", nbiap->br5vr);
	Pval("NBIA BR6", nbiap->br6vr);
	Pval("NBIA BR7", nbiap->br7vr);
}

dump8800()
{
	pka88();
	pms88();
	dumpnbi();
}

dumpnbi()
{
register int i, j;
register struct ioanode *ip = ioanode;

	for (i = 0; i < nioa; i++, ip++) {
		printf("IOA %x\tNODE %x\tBNODE %x\t A/B %x/%x PHYS %x\n",
			i, ip->node, ip->bnode, ip->addr88, ip->bddr, ip->bi_addr);
		pnbi(ip->addr88);
		for (j = 0; j < BI_MAX_NODE; j++) {
			if (ip->bi[j]) {
				printf("BI NODE %x\n", j);
				pbi(ip->bi[j]);
			}
		}
	}
}
#endif	VAX8800
