/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ka62a.c,v $
 * Revision 2.8  89/04/05  13:04:11  rvb
 * 	Find dwmba B card by loopback just like for a 8800.
 * 	[89/01/27            rvb]
 * 
 * Revision 2.7  89/03/09  22:30:33  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/26  10:58:22  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/01/15  16:38:30  rpd
 * 	Updated includes to the new style.
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  15:25:17  rpd]
 * 
 * Revision 2.4  88/10/11  13:06:39  rpd
 * 	VAX6200: Try ssc timer chip.
 * 	[88/10/08            rvb]
 * 	
 * 	Now we need a bi_settle() before probe_bi.
 * 	[88/10/05            rvb]
 * 	
 * 	Move crd and crd_cnt to ka62a.c where it belongs.
 * 	[88/09/29            rvb]
 * 
 * Revision 2.3  88/09/07  15:15:00  berman
 * 	   Machine check bus error no's should have been hex.
 * 	[88/08/29            rvb]
 * 
 * Revision 2.2  88/08/10  10:47:43  rvb
 *  19-Jul-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Handle cdal parity mchk.
 * 
 *  24-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Clearing a tag parity error might not clear correctly the first
 * 	time through, hence the loop.
 * 	Also clean up the HACK1 code a bit.
 * 
 *  10-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	1.	Slaves should turn on DLCKOUTEN
 * 	2.	better mchk diagnostics.
 * 	3.	printing_cpu is only a hint since the
 * 		console programs can shift the BP around.
 * 
 *   7-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 *   1.	Slaves are started with cadr = 0x0c not 0xcc.  So be sure to
 * 	turn their level one caches on correctly.
 *   2.	Use the "gross hack" to reset level 2 cache on IQO. (HACK1)
 *   3.	Print out "." every iqo_dot times.
 *   4.	Code to allow console to be acquired dynamically by the processor
 * 	that is printing.  Uses (for now a hack) version of WEI interrupt.
 * 
 *   8-Apr-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Created.  Week of 4/4.
 * 
 *
 */
/*
 *	File:	ka62a.c
 *	Author:	Robert V. Baron
 *
 *	Support for the 6200
 */
#include <cputypes.h>
#define HACK1
#if	VAX6200
#include <cpus.h>

#include <sys/param.h>
#include <mach/machine.h>
#include <mach/vm_param.h>
#include <vm/vm_kern.h>
#include <vax/cpu.h>
#include <vax/mtpr.h>
#include <vax/scb.h>
#include <vaxnb/ka62a.h>
#include <vax/bi_node.h>
#include <vaxnb/node.h>
#include <vaxnb/cca.h>

char *consel[8] = {	"Power Up", "Power Up All Fail",
			"Loopback", "Unused",
			"Unused", "Boot Processor",
			"Unused", "Loopback"};


/*		       0, 1, 2, 3, 4,  5,  6,  7,  8,  9,  a, b, c, d, e,  f */
int xmi_ioa_no[16] = {-1, 0, 1, 2, 3, -1, -1, -1, -1, -1, -1, 4, 5, 6, 7, -1};

caddr_t xmi_dwmba_addr[8] = {
			XMI_IOA_RANGE1+0*XMI_IOA_SIZE, XMI_IOA_RANGE1+1*XMI_IOA_SIZE,
			XMI_IOA_RANGE1+2*XMI_IOA_SIZE, XMI_IOA_RANGE1+3*XMI_IOA_SIZE,

			XMI_IOA_RANGE2+0*XMI_IOA_SIZE, XMI_IOA_RANGE2+1*XMI_IOA_SIZE,
			XMI_IOA_RANGE2+2*XMI_IOA_SIZE, XMI_IOA_RANGE2+3*XMI_IOA_SIZE
};

static int pr_ssc(), verify_ssc(), xmi_badaddr();
int crd = 1;
int crd_cnt = 0;

ka62a_init()
{
	register struct ka62a *cpp = cpunode[cpu_number()].addr62;
	register int cadr;
	register int mser;

	cadr = mfpr(CADR);
	cadr |= CADR_ON;			/* enable level 1 cache I space only*/
	mtpr(CADR, cadr);
	cadr = mfpr(CADR);			/* just checking */
	if (cadr != CADR_NORMAL)
		printf("cadr = %b\n", cadr, CADR_B);

	mser = mfpr(MSER);
	if (mser&0xff != MSER_NORMAL)
		printf("mser = %b\n", mser, MSER_B);

	*ka62a_csr1 |= ka62aCSR1_FCI;			/* invalidate */
	*ka62a_csr1 &= ~(ka62aCSR1_FCI|ka62aCSR1_FMISS);	/* enable level 2 cache */

	*ka62a_csr1 |= ka62aCSR1_DLCKOUTEN;		/* for slaves */

	if ((*ka62a_csr1&~0xf) != 0xfc0004c0) 
		printf("Control and Status Register 1 %b\n", *ka62a_csr1, ka62aCSR1);

	verify_ssc();
}

ka62a_conf()
{
	register caddr_t	node;		/* node's phys addr */
	register int		i;
	int			need_vm = 1;	/* implies need more vm */
	struct	xmi		*xmi;
	extern int		cpuspeed;

	cpuspeed = 3;
	master_cpu = cpu_number();

	printf("\n NODE REV ID        V/P        CVAX SSC FPA  MODULE  COMPAT\n");
	for (node = XMI_NODE_SPACE, i = 0; i < 16; node += XMI_NODE_SIZE, i++) {

		if (need_vm) {
			xmi = (struct xmi *)kmem_alloc_pageable(kernel_map, NBPG);
			if (xmi == 0)
				panic("new_configure");
			need_vm = 0;
		}
		ioaccess(node, xmi, NBPG);
		if (xmi_badaddr(xmi, 4))
			continue;

		need_vm++;

		if (xmi->dev & XMI_CPU) {
			struct hw_revision *hwp;
			struct ka62a *cpp = (struct ka62a *) xmi;
			hwp = &cca->hw_revision[i];

			printf("CPU %x   %x  %x %x/%x",
				i, cpp->rev, cpp->dev&~XMI_CPU, cpp, node);
			printf("   %x  %x  %x %x      %x",
				hwp->cvax_rev, hwp->ssc_rev, hwp->fpa_rev,
				hwp->mod_rev, hwp->com_grp);

			if (cpp->ber & (XMIBER_STF|XMIBER_ETF)) {
			    	printf(" FAILED.\n");
				pka62a(cpp);
				continue;
			}
				/* Remember stuff */
			cpunode[i].addr62 = cpp;
			cpunode[i].node = i;
			last_cpu = i;
			machine_slot[i].is_cpu = TRUE;
			machine_slot[i].cpu_type = CPU_TYPE_VAX;
			machine_slot[i].cpu_subtype = CPU_SUBTYPE_UVAXIII;
				/* reset */
			cpp->ber = cpp->ber & XMIBER_ERR;
			cpp->csr2 = cpp->csr2 | ka62aCSR2_ERR;
			cpp->csr2 |= 0x01<<21;		/* LOCKOUT == 01 */
			if (!crd)
				cpp->csr2 |= ka62aCSR2_CRDID;
			*ka62a_csr1 |= ka62aCSR1_DLCKOUTEN;

			if (i == master_cpu) {
				printf(" MASTER.\n");
			} else {
				printf("\n");
			}

		} else if (xmi->dev & XMI_MEM) {
			struct ms62a *mp = (struct ms62a *) xmi;
			printf("MEM %x   %x  %x %x/%x",
				i, mp->rev, mp->dev&~XMI_MEM, mp, node);

			if (mp->ber & (XMIBER_STF|XMIBER_ETF)) {
				printf("                              FAILED.\n");
				pms62a(mp);
				continue;
			}

				/* Remember stuff */
			memnode[nmem].addr62 = mp;
			memnode[nmem++].node = i;
			printf("   %d..%dM @%d [%dM]\n",
			        (mp->seadr&SEADR_STADR)>>8,
			       ((mp->seadr&SEADR_ENDADR)>>21) * 2,
			        (mp->seadr&SEADR_INADR)>>5,
				(mp->mctl1&M62aCTL1_MEMSIZ)>>20);

			mp->mctl1 |= M62aCTL1_ERR;
			mp->mctl2 |= M62aCTL2_ERR | M62aCTL2_DISH;
			mp->mecer |= M62aECER_ERR;

		} else if (xmi->dev & XMI_IOA) {
			extern caddr_t biscb;
			struct dwmba *ip = (struct dwmba *) xmi;
			struct ioanode *ioap = &ioanode[nioa];
			struct bi_node *biv;
			int no = xmi_ioa_no[i];

			printf("IOA %x   %x  %x %x/%x",
				i, ip->rev, ip->dev&~XMI_IOA, ip, node);

			if (ip->ber & (XMIBER_STF|XMIBER_ETF)) {
				printf("  FAILED.\n");
				pdwmba(ip);
				continue;
			}
				/* Remember stuff */
			ioap->addr62 = ip;
			ioap->node = i;
			ioap->bi_addr = (caddr_t) xmi_dwmba_addr[no];

				/* reset */
#define xi_int(nioa) ((int)&biscb - (int)&scb + 0x100+ 4*nioa);
			ip->bvr = xi_int(nioa);
			ip->aivintr = 1 << master_cpu;
			ip->aesr = AESR_ERR;
			ip->aimr = AIMR_EN;

			ip->bidr |= 1 << master_cpu;
			ip->bvor = 0;
			ip->besr = BESR_ERR;
			ip->bcsr |= BCSR_ENINTR | BCSR_EN;

			biv = (struct bi_node *)kmem_alloc_pageable(kernel_map, BI_NODE_SIZE);
			if (biv == 0)
				panic("ka62a_conf");
			ioaccess((caddr_t) xmi_dwmba_addr[no], biv, BI_NODE_SIZE);
			ip->bdcr1 |=  BDCR1_BIICLOOP;
			ioap->bddr = biv;
			ioap->bi[ioap->bnode = biv->bicsr & BICSR_NODE] = biv;
			ip->bdcr1 &=  ~BDCR1_BIICLOOP;
				/*
				 * N.B. va hasn't changed, but we need to straighten
				 * out the pa since loop back is off.
				 */
			ioaccess((caddr_t) xmi_dwmba_addr[no] + BI_NODE_SIZE * ioap->bnode,
				 biv, BI_NODE_SIZE);

			scan_bix(ioap);
			nioa++;

		} else
			panic("xdev: unknown node");
	}
	if (!need_vm)
    	 	 kmem_free(kernel_map, xmi, NBPG);

	bi_settle();
	for (i = nioa, nioa = 0; nioa < i; nioa++) {
		struct ioanode *ioap = &ioanode[nioa];

		probe_bi(ioap->bi_addr, XMI_BUS, 1<<ioap->bnode);
	}

	ip_space = kmem_alloc_pageable(kernel_map, round_page(1<<last_cpu));
	wei_space = kmem_alloc_pageable(kernel_map, round_page(1<<last_cpu));
	ioaccess((caddr_t) IP_SPACE, ip_space, round_page(1<<last_cpu));
	ioaccess((caddr_t) WEI_SPACE, wei_space, round_page(1<<last_cpu));

}

static xmi_badaddr(addr, size)
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

ka62a_halt(cpn)
{
	cpunode[cpn].addr62->ber = XMIBER_NHALT;
}

mchk_ka62a(cmcf)
caddr_t cmcf;
{
	register struct ka62a *cpp = cpunode[cpu_number()].addr62;
	register int mser;
struct mcka62aframe {
	int	mc62_bcnt;		/* byte count == 0xe */
	int	mc62_mcc;		/* machine check code */
	int	mc62_mrvaddr;		/* most recent virtual addr */
	int	mc62_istate1;		/* internal state */
	int	mc62_istate2;		/* internal state */
	int	mc62_pc;		/* trapped pc */
	int	mc62_psl;		/* trapped psl */
};

	register struct mcka62aframe *mcf = (struct mcka62aframe *)cmcf;
	*ka62a_csr1 = *ka62a_csr1 | ka62aCSR1_DLCKOUTEN | ka62aCSR1_FMISS;		/* for safety */
	printf("\n");
	printf("code %x vap %x istate1 %x istate2 %x pc %x psl %x\n",
		mcf->mc62_mcc, mcf->mc62_mrvaddr,
		mcf->mc62_istate1, mcf->mc62_istate2,
		mcf->mc62_pc, mcf->mc62_psl);

	printf("istate1 = %b\n", mcf->mc62_istate1, "\20\40\31OP\20\11CADR\10\01MSER");

	mser = mfpr(MSER);
	printf("mser = %b\n", mser, MSER_B);
	pka62a(cpp);

	if (mcf->mc62_mcc < 0x84 && mcf->mc62_mcc >= 0x80) {
		if (!(mcf->mc62_istate2 & 0x8000)) {
			/*
			 * We have a bus error and can't restart bit is 0.
			 * So we can restart.
			 */
			printf("Restarting after bus error machine check\n");
			mtpr(MSER, 0);			/* clear error */
			mser = mfpr(MSER);
			printf("mser = %b\n", mser, MSER_B);

			/*
			 * We could read the mrvaddr-4 both with and without
			 * parity enabled (csr1), to better locate the problem
			 */
#ifdef	HACK1
			ka62a_csr1_quad_iqo_hack();
#else	HACK1
			*ka62a_csr1 |= ka62aCSR1_FCI;			/* invalidate */
			*ka62a_csr1 &= ~(ka62aCSR1_FCI|ka62aCSR1_FMISS);	/* enable level 2 cache */
			*ka62a_csr1 |= ka62aCSR1_DLCKOUTEN;
#endif	HACK1
			return;
		} else {
			/*
			 * In theory, we could blow the user process away, if
			 * a user process were running and then continue.
			 * But for now we'll just die.
			 */
			printf("Can't restart bit is true.\n");
		}
	}
	panic("mchk");
}

/*
 * CRD And Friends
 */
int iqo_cnt = 1;
int iqo_dot = 100;
crd_ka62a()
{
	register int i;
	register struct ka62a *cpp = cpunode[cpu_number()].addr62;
	register int s;

	i = 7;		/* lucky 7 */
	do {
		if (cpp->csr2 & ka62aCSR2_IQO) {	/* INVAL Q OVERFLOW */
			if (iqo_dot && !(iqo_cnt % iqo_dot)) printf(".");
			iqo_cnt++;
			cpp->csr2 = (cpp->csr2 & ~ka62aCSR2_ERR) | ka62aCSR2_IQO;
#ifdef	HACK1
			ka62a_csr1_quad_iqo_hack();
#else	HACK1
			*ka62a_csr1 |= ka62aCSR1_FCI;			/* invalidate */
			*ka62a_csr1 &= ~(ka62aCSR1_FCI|ka62aCSR1_FMISS);	/* enable level 2 cache */
			*ka62a_csr1 |= ka62aCSR1_DLCKOUTEN;
#endif	HACK1
			if (! (cpp->csr2 & ka62aCSR2_ERR)) {
				return;
			}
		} else if (cpp->csr2 & ka62aCSR2_ERR) {	/* some other FMISS */
			printf("csr2: %b\n", cpp->csr2, ka62aCSR2);
			if (iqo_dot) printf("#");
			cpp->csr2 = cpp->csr2  | ka62aCSR2_ERR;
#ifdef	HACK1
			ka62a_csr1_quad_iqo_hack();
#else	HACK1
			*ka62a_csr1 |= ka62aCSR1_FCI;			/* invalidate */
			*ka62a_csr1 &= ~(ka62aCSR1_FCI|ka62aCSR1_FMISS);	/* enable level 2 cache */
			*ka62a_csr1 |= ka62aCSR1_DLCKOUTEN;
#endif	HACK1
		}
	} while ( (cpp->csr2 & ka62aCSR2_ERR) && --i > 0);
	if (i == 0) {
		printf("\ncrd_ka62a: can't reset csr2 error\n");
		pka62a(cpp);
	}

	if (cpp->ber & XMIBER_ES) {		/* some node problem */
		if (cpp->ber & XMIBER_CRD) {		/* crd */
			for (i = 0; i < nmem; i++) {
				register struct ms62a *mp = memnode[i].addr62;
				register int tmp;
				if (mp->ber & XMIBER_ES) {
					printf("\n");
					printf("NODE %x AT P %x\n",
						memnode[i].node, pmap_extract(kernel_pmap, mp));
					printf("crd: Error Addr %x, Error Register %b\n",
						mp->mecea, mp->mecer, M62aECER);
					printf("\n");
					mp->mecer = M62aECER_ERR;
					if (crd_cnt++ >= 3) {
						tmp = cpp->csr2 | ka62aCSR2_CRDID;
						cpp->csr2 = tmp;
					}
				}
			}
		} else if (cpp->ber & XMIBER_ERR) {	/* std */
			pka62a(cpp);
			cpp->ber = XMIBER_ERR;
		} else if (cpp->ber & XMIBER_NSES) {	/* node specific */
			if (cpp->csr2 & ka62aCSR2_ERR)
				pka62a(cpp);
		}
	}

	for (i = 0; i < nmem; i++) {
		register struct ms62a *mp = memnode[i].addr62;
		if (mp->ber & XMIBER_ES) {
			printf("\nMEMORY NODE %x AT P %x\n",
				memnode[i].node, pmap_extract(kernel_pmap, mp));
			pms62a(mp);
			mp->mctl1 |= M62aCTL1_ERR;
			mp->mctl2 |= M62aCTL2_ERR | M62aCTL2_DISH;
			mp->mecer |= M62aECER_ERR;
		}
	}
}

xmi_err(pc, psl, ioa)
{
	register struct dwmba *dwp = ioanode[ioa].addr62;
	register struct ioanode *ioap = &ioanode[ioa];
	register struct bi_node *biv  = ioanode[ioa].bddr;
	register struct ka62a *cpp = cpunode[cpu_number()].addr62;

	if (pc)
		printf("xmi_err(pc %x, psl %x, ioa %x)\n", pc, psl, ioa);
/*	else
		it was called by bi_err */

	if ((int) dwp) {
		printf("Bcard Node %x V %x\n",
			ioap->bnode, ioap->bddr);
		pbi(ioap->bddr);
		printf("IOA %x V %x\n", ioa, dwp);
		pdwmba(dwp);
		dwp->ber = dwp->ber & XMIBER_ERR;
		dwp->aesr = dwp->aesr & AESR_ERR;
		dwp->besr = dwp->besr & BESR_ERR;
		biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
	}

	printf("master cpu = Node%x\tV %x\n", master_cpu, cpunode[master_cpu]);
	if ((int) cpp) {
		pka62a(cpp);
		cpp->ber = cpp->ber & XMIBER_ERR;
		cpp->csr2 = cpp->csr2 | ka62aCSR2_ERR;
	}
}

int printing_cpu = 0;		/* who has console */
int acquiring_cpu = 0;
int console_control = 0;
int move_control = 0;

decl_simple_lock_data(,ka62a_console_lock)
decl_simple_lock_data(extern,printf_lock)

acquire_console(cpu)
{
register char x = 1;
register int i;

	acquiring_cpu = cpu;
	if (!(cpunode[printing_cpu].addr62->csr2 & ka62aCSR2_BP)) { /* find it */
		for (i = 0; i < NCPUS; i++) {
			if (!cpunode[i].node)
				continue;
			if (cpunode[i].addr62->csr2 & ka62aCSR2_BP)
				break;
		}
		if (i == NCPUS)		/* yuck */
			panic("acquire_console: bp");
		printing_cpu = i;
		if (i == acquiring_cpu)
			return;
	}
	simple_lock(&ka62a_console_lock);
	console_control = 1 << printing_cpu;
	/*
	 * this must expand to a movb ?
	 */

	*(char *)(wei_space + (1<<printing_cpu)) = x;
	simple_lock(&ka62a_console_lock);	/* yes, we want to spin*/
	simple_unlock(&ka62a_console_lock);	/* but we don't really want the lock */
	i = cpunode[cpu].addr62->csr2;
	cpunode[cpu].addr62->csr2 = i | ka62aCSR2_BP;
	ka62a_ssc->ssc_consel = 0xd;		/* use console */
	printing_cpu = cpu;
}

release_console()
{
int cpu = cpu_number();
register int i;

	if (cpu != printing_cpu) {
		asm("halt");
	}

	i = cpunode[cpu].addr62->csr2;
	cpunode[cpu].addr62->csr2 = i & (~ka62aCSR2_BP);
	ka62a_ssc->ssc_consel = 0x0;
	console_control = 0;
	simple_unlock(&ka62a_console_lock);
}

move_console(cpun)
{
register char x = 1;

	simple_lock(&printf_lock);
	move_control = 1;
	*(char *)(wei_space + (1<<cpun)) = x;
}

grab_console()
{
	acquire_console(cpu_number());
	move_control = 0;
	simple_unlock(&printf_lock);
}

	/* check against an expected value */
#define VE(str,addr,mask,value) \
	if ((addr & mask) != value) {\
		printf("\t%s: %x EXPECTED %x\n", str, addr, value);\
	}

	/* check against an expected value and set to that value*/
#define VS(str,addr,mask,value) \
	if ((addr & mask) != value) {register int new = ((addr&~mask)|value);\
		printf("\t%s: %x CHANGED TO %x\n", str, addr, new);\
		addr = new;\
	}

	/* check for bits that must be set to 1 to be cleared */
#define VC(str,addr,mask) \
	if ((addr & mask) == mask) {\
		printf("\t%s: %x CHANGED TO ", str, addr);\
		addr = mask;\
		printf("%x\n", addr);\
	}

#define PR(str,ptr) printf("\t%s \t%x\n", str, ptr)
#define Pb(str,ptr,bits) printf("\t%s \t%b\n", str, ptr, bits)
#define Pval(str,ptr) if (ptr || p0val) PR(str, ptr)
#define Pvalb(str,ptr,bits) if (ptr || p0val) Pb(str,ptr,bits)
extern int p0val;

pka62a(xcp)
register struct ka62a *xcp;
{
	Pb("XMI   BUS Error Register", xcp->ber, XMIBER);
	Pvalb("Failed Address Register", xcp->fadr, XMIFADR);
	Pvalb("Control and Status Register 2", xcp->csr2, ka62aCSR2);

	if ((*ka62a_csr1&~0xf) != 0xfc0004c0) 
		Pb("Control and Status Register 1", *ka62a_csr1, ka62aCSR1);

	if (xcp == cpunode[cpu_number()].addr62)
		verify_ssc();
}

pms62a(mp)
register struct ms62a *mp;
{
	Pvalb("XMI   BUS Error Register", mp->ber, XMIBER);

	Pb("Starting and Ending Address", mp->seadr, SEADR);
	Pb("Memory Control 1 Register", mp->mctl1, M62aCTL1);
	Pb("Memory Control 2 Register", mp->mctl2, M62aCTL2);
	Pvalb("Memory ECC Error Register", mp->mecer, M62aECER);
	Pval("Memory ECC Error Address", mp->mecea);
	Pval("TCY Tester Register\t", mp->tcy);
	Pval("Interlock 0 Flag Register", mp->int0);
	Pval("Interlock 1 Flag Register", mp->int1);
	Pval("Interlock 2 Flag Register", mp->int2);
	Pval("Interlock 3 Flag Register", mp->int3);
	Pval("Interlock 4 Flag Register", mp->int4);
	Pval("Interlock 5 Flag Register", mp->int5);
	Pval("Interlock 6 Flag Register", mp->int6);
	Pval("Interlock 7 Flag Register", mp->int7);
	Pval("Interlock 8 Flag Register", mp->int8);
	Pval("Interlock 9 Flag Register", mp->int9);
	Pval("Interlock a Flag Register", mp->inta);
	Pval("Interlock b Flag Register", mp->intb);
	Pval("Interlock c Flag Register", mp->intc);
	Pval("Interlock d Flag Register", mp->intd);
	Pval("Interlock e Flag Register", mp->inte);
	Pval("Interlock f Flag Register", mp->intf);
}

pdwmba(ip)
register struct dwmba *ip;
{
	Pb("XMI   BUS Error Register", ip->ber, XMIBER);
	Pvalb("Failed Address Register", ip->fadr, XMIFADR);

	Pb("Error Summary Register\t", ip->aesr, AESR);
	PR("Responder Error Address", ip->arear);	
	Pb("Interrupt Mask Register", ip->aimr, AIMR);
	PR("Implied Vector Interrupt ... ", ip->aivintr);
	Pval("Diagnostic 1 Register\t", ip->adg1);
	printf("\n");
	Pb("Control and Status Register", ip->bcsr, BCSR);
	Pb("Error Summary Register\t", ip->besr, BESR);
	PR("Interrupt Destination\t", ip->bidr);
	PR("Timeout Address Register", ip->btim);
	PR("Vector Offset Register\t", ip->bvor);
	PR("Vector Register\t\t", ip->bvr);
}

dump6200()
{
register int i, j;
register struct cpunode *cp = cpunode;
register struct memnode *mp = memnode;
register struct ioanode *ip = ioanode;

	for (i = 0; i < NCPUS; i++, cp++) {
		if (cp->addr62) {
			printf("CPU %x\tNODE %x\n", i, cp->node);
			pka62a(cp->addr62);
		}
	}

	for (i = 0; i < nmem; i++, mp++) {
		printf("MEM %x\tNODE %x\n", i, mp->node);
		pms62a(mp->addr62);
	}

	for (i = 0; i < nioa; i++, ip++) {
		printf("IOA %x\tNODE %x\tBNODE %x\t A/B %x/%x PHYS %x\n",
			i, ip->node, ip->bnode, ip->addr62, ip->bddr, ip->bi_addr);
		pdwmba(ip->addr62);
		for (j = 0; j < BI_MAX_NODE; j++) {
			if (ip->bi[j]) {
				printf("BI NODE %x\n", j);
				pbi(ip->bi[j]);
			}
		}
	}
}

dumpdwmba()
{
register int i, j;
register struct ioanode *ip = ioanode;

	for (i = 0; i < nioa; i++, ip++) {
		printf("IOA %x\tNODE %x\tBNODE %x\t A/B %x/%x PHYS %x\n",
			i, ip->node, ip->bnode, ip->addr62, ip->bddr, ip->bi_addr);
		pdwmba(ip->addr62);
		for (j = 0; j < BI_MAX_NODE; j++) {
			if (ip->bi[j]) {
				printf("BI NODE %x\n", j);
				pbi(ip->bi[j]);
			}
		}
	}
}
static pr_ssc()
{
	register struct ka62a_ssc *sp = ka62a_ssc;

	PR("SSC Base Address Register", sp->ssc_sscbr);
	Pb("SSC Configuration Register", sp->ssc_ssccr, SSCCR);
	PR("CDAL Bus Timeout Control", sp->ssc_cbtcr);
	PR("Console Select", sp->ssc_consel);
		printf("	%s\n", CONSEL(sp->ssc_consel));
	Pb("Timer 0 Control Register", sp->ssc_tcr0, TCR);
	PR("Timer 0 Interval Register", sp->ssc_tir0);
	PR("Timer 0 Next Interval Register", sp->ssc_tnir0);
	PR("Timer 0 Interrupt Vector", sp->ssc_tivr0);

	Pb("Timer 1 Control Register", sp->ssc_tcr1, TCR);
	PR("Timer 1 Interval Register", sp->ssc_tir1);
	PR("Timer 1 Next Interval Register", sp->ssc_tnir1);
	PR("Timer 1 Interrupt Vector", sp->ssc_tivr1);

	PR("CSR1 Base Address Register", sp->ssc_csr1badr);
	PR("CSR1 Address Decode Mask Register", sp->ssc_csr1admr);

	PR("EEPROM Base Address Register", sp->ssc_eebadr);
	PR("EEPROM Address Decode Mask Register", sp->ssc_eeadmr);

	printf("%s: ptr (@%x) = ...\n", "Battery Backed-up RAM", sp->nv_bburam);
}

static verify_ssc()
{
	register struct ka62a_ssc *sp = ka62a_ssc;
	extern int printing_cpu;

	/* The 5 values tested below REALLY should never be changed */
	VE("SSC Base Address Register", sp->ssc_sscbr, 0x3fffffff, 0x20140000);

	VE("CSR1 Base Address Register", sp->ssc_csr1badr, 0x3fffffff, 0x20000000);
#ifdef	HACK1
	sp->ssc_csr1admr |= 4;
	VE("CSR1 Address Decode Register", sp->ssc_csr1admr, 0x3fffffff, 04);
#else	HACK1
	VE("CSR1 Address Decode Register", sp->ssc_csr1admr, 0x3fffffff, 00);
#endif	HACK1
	VE("EEPROM Base Address Register", sp->ssc_eebadr, 0x3fffffff, 0x20080000);
	VE("EEPROM Address Decode Register", sp->ssc_eeadmr, 0x3fffffff, 0x7ffc);
		/* End of the 5 values */

/*	VE("SSC Configuration Register", sp->ssc_ssccr, 0xffffffff, 0x0160a047);*/
	VE("CDAL Bus Timeout Control", sp->ssc_cbtcr, 0xffffff, 0x9000);
	if (cpu_number() == printing_cpu) {
		VE("Console Select", sp->ssc_consel, 0xffffffff, 0xd);
	} else {
		VE("Console Select", sp->ssc_consel, 0xffffffff, 0x0);
	}

	sp->ssc_tcr0 = 0;
	sp->ssc_tcr0 = sp->ssc_tcr0;
	VE("Timer 0 Control Register", sp->ssc_tcr0, -1, 0);
	VE("Timer 0 Interrupt Vector", sp->ssc_tivr0, 0xff, 0x78);

	sp->ssc_tcr1 = 0;
	sp->ssc_tcr1 = sp->ssc_tcr1;
	VE("Timer 1 Control Register", sp->ssc_tcr1, -1, 0);
	VE("Timer 1 Interrupt Vector", sp->ssc_tivr1, 0xff, 0x7c);
}
#endif	VAX6200
