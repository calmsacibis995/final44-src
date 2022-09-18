/* 
 * Mach Operating System
 * Copyright (c) 1991,1989,1988 Carnegie Mellon University
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
 * $Log:	ka6200.c,v $
 * Revision 2.6  93/05/15  18:58:52  mrt
 * 	machparam.h -> machspl.h
 * 
 * Revision 2.5  92/01/03  20:32:49  dbg
 * 	Add ka6200_start.
 * 	[91/10/25            dbg]
 * 
 * Revision 2.4  91/06/19  12:00:43  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:47:56  rvb]
 * 
 * Revision 2.3  91/05/14  17:43:21  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:17:30  dbg
 * 	Include vax/machparam.h for SPL definitions.
 * 	[91/03/21            dbg]
 * 
 * 	Mangled for MACH_KERNEL.
 * 	[88/11/16            dbg]
 * 
 * Revision 2.1  89/08/03  16:29:13  rwd
 * Created.
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
 */

/*
 *	File:	ka62a.c
 *	Author:	Robert V. Baron
 *
 *	Support for the 6200
 */

#include <platforms.h>

#if	VAX6200

#include <kern/cpu_number.h>
#include <mach/machine.h>

#include <vm/pmap.h>

#include <vax/bi_node.h>
#include <vax/cpu_data.h>
#include <vax/ka6200.h>
#include <vax/cca.h>
#include <vax/mtpr.h>
#include <vax/io_map.h>
#include <vax/node.h>
#include <vax/pmap.h>
#include <vax/scb.h>
#include <vax/vm_defs.h>
#include <vax/machspl.h>

#include <vax/thread.h>	/* for pcb_t */

extern char *	biscb;

int *			ka62a_csr1;
struct ka62a_ssc *	ka62a_ssc;
struct cca *		ccap;		/* physical address */
struct cca *		cca;		/* virtual address */
int			last_cpu;
char *			ip_space;
char *			wei_space;

char *consel[8] = {	"Power Up", "Power Up All Fail",
			"Loopback", "Unused",
			"Unused", "Boot Processor",
			"Unused", "Loopback"};



/*		       0, 1, 2, 3, 4,  5,  6,  7,  8,  9,  a, b, c, d, e,  f */
int xmi_ioa_no[16] = {-1, 0, 1, 2, 3, -1, -1, -1, -1, -1, -1, 4, 5, 6, 7, -1};

vm_offset_t xmi_dwmba_addr[8] = {
	XMI_IOA_RANGE1+0*XMI_IOA_SIZE, XMI_IOA_RANGE1+1*XMI_IOA_SIZE,
	XMI_IOA_RANGE1+2*XMI_IOA_SIZE, XMI_IOA_RANGE1+3*XMI_IOA_SIZE,

	XMI_IOA_RANGE2+0*XMI_IOA_SIZE, XMI_IOA_RANGE2+1*XMI_IOA_SIZE,
	XMI_IOA_RANGE2+2*XMI_IOA_SIZE, XMI_IOA_RANGE2+3*XMI_IOA_SIZE
};

int	crd = 1;
int	crd_cnt = 0;

#define	IQO_HACK	1

int	ka6200_setup(), ka6200_init(), ka6200_config(), ka6200_slave_config(),
	ka6200_reboot_ok(), ka6200_crd(), ka6200_mchk(),
	ka6200_clear_mchk(), ka6200_halt(), ka6200_interrupt(),
	ka6200_start();

struct model_dep ka6200_model = {
	ka6200_setup,
	ka6200_init,
	ka6200_config,
	ka6200_slave_config,
	ka6200_reboot_ok,
	ka6200_crd,
	ka6200_mchk,
	ka6200_clear_mchk,
	ka6200_halt,
	ka6200_interrupt,
	10,
	ka6200_start
};

ka6200_cache_on()
{
	int	cadr;

	cadr = mfpr(CADR);
	cadr |= CADR_ON;	/* enable level 1 cache I space only */
	mtpr(CADR, cadr);

	*ka62a_csr1 |= ka62aCSR1_FCI;
				/* invalidate */
	*ka62a_csr1 &= ~(ka62aCSR1_FCI | ka62aCSR1_FMISS);
				/* enable level 2 cache */
	*ka62a_csr1 |= ka62aCSR1_DLCKOUTEN;

#if	IQO_HACK
	ka62a_ssc->ssc_csr1admr |= 4;	/* decode 2 copies of csr1 */
#endif	IQO_HACK
}

ka6200_setup()
{
	ka62a_csr1 = (int *)io_map((vm_offset_t)CSR1, sizeof(int));

	cca	   = (struct cca *)io_map((vm_offset_t)ccap,
					  sizeof(struct cca));

	ka62a_ssc  = (struct ka62a_ssc *)io_map((vm_offset_t)SSCC,
						sizeof(struct ka62a_ssc));
	ka6200_cache_on();
}

ka6200_init()
{
	register vm_offset_t	node;
	register int		i;

	extern void scan_bix();

	printf("\n");

	printf(" NODE REV ID        V/P        CVAX SSC FPA  MODULE  COMPAT\n");

	for (node = XMI_NODE_SPACE, i = 0;
	     i < 16;
	     node += XMI_NODE_SIZE, i++) {

	    register struct xmi *	xmi;

	    xmi = (struct xmi *)io_map(node, NBPG);
	    if (xmi_badaddr((vm_offset_t)xmi, sizeof(int))) {
		io_unmap((vm_offset_t)xmi, NBPG);
		continue;
	    }
	    if (xmi->dev & XMI_CPU) {
		struct hw_revision *	hwp;
		struct ka62a *		cpp = (struct ka62a *)xmi;

		hwp = &cca->hw_revision[i];

		printf("CPU %x   %x  %x %x/%x",
			i,
			cpp->rev,
			cpp->dev & ~XMI_CPU,
			cpp,
			node);
		printf("   %x  %x  %x %x      %x",
			hwp->cvax_rev,
			hwp->ssc_rev,
			hwp->fpa_rev,
			hwp->mod_rev,
			hwp->com_grp);
		if (cpp->ber & (XMIBER_STF | XMIBER_ETF)) {
		    printf(" FAILED\n");
		    print_ka6200(cpp);
		    continue;
		}

		cpu_node[i].addr = (char *)cpp;
		cpu_node[i].node = i;
		last_cpu = i;

		machine_slot[i].is_cpu = TRUE;
		machine_slot[i].cpu_type = CPU_TYPE_VAX;
		machine_slot[i].cpu_subtype = CPU_SUBTYPE_UVAXIII;

		/* reset */
		cpp->ber = cpp->ber & XMIBER_ERR;
		cpp->csr2 = cpp->csr2 | ka62aCSR2_ERR;
		cpp->csr2 |= 0x01 << 21;	/* LOCKOUT */
		if (!crd)
		    cpp->csr2 |= ka62aCSR2_CRDID;
		*ka62a_csr1 |= ka62aCSR1_DLCKOUTEN;

		if (i == master_cpu)
		    printf(" MASTER\n");
		else
		    printf("\n");
	    }
	    else if (xmi->dev & XMI_MEM) {
		struct ms62a *mp = (struct ms62a *)xmi;

		printf("MEM %x   %x  %x %x/%x",
			i,
			mp->rev,
			mp->dev & ~XMI_MEM,
			mp,
			node);
		if (mp->ber & (XMIBER_STF|XMIBER_ETF)){
		    printf("FAILED\n");
		    print_mem6200(mp);
		    continue;
		}

		mem_node[nmem].addr = (char *)mp;
		mem_node[nmem].node = i;
		nmem++;

		printf("   %d..%dM @%d [%dM]\n",
			(mp->seadr & SEADR_STADR)>>8,
			((mp->seadr & SEADR_ENDADR)>>21) * 2,
			(mp->seadr & SEADR_INADR)>>5,
			(mp->mctl1 & M62aCTL1_MEMSIZ)>>20);
		mp->mctl1 |= M62aCTL1_ERR;
		mp->mctl2 |= M62aCTL2_ERR | M62aCTL2_DISH;
		mp->mecer |= M62aECER_ERR;
	    }
	    else if (xmi->dev & XMI_IOA) {

		struct dwmba *ip = (struct dwmba *)xmi;
		struct ioa_node *ioa = &ioa_node[nioa];
		int	no = xmi_ioa_no[i];

		printf("IOA %x   %x  %x %x/%x",
			i,
			ip->rev,
			ip->dev & ~XMI_IOA,
			ip,
			node);
		if (ip->ber & (XMIBER_STF|XMIBER_ETF)) {
		    printf(" FAILED.\n");
		    continue;
		}

		ioa->addr = (char *)ip;
		ioa->node = i;
		ioa->bi_paddr = (struct bi_node *)xmi_dwmba_addr[no];

		ip->bvr = (int)&biscb - (int)&scb + 0x100 + 4*nioa;
		ip->aivintr = 1 << master_cpu;
		ip->aesr = AESR_ERR;
		ip->aimr = AIMR_EN;

		ip->bidr |= 1 << master_cpu;
		ip->bvor = 0;
		ip->besr = BESR_ERR;
		ip->bcsr |= BCSR_ENINTR | BCSR_EN;

		scan_bix(ioa);
		nioa++;
	    }
	    else {
		panic("xdev: unknown node");
	    }
	}

	ip_space  = (char *)io_map((vm_offset_t)IP_SPACE,
				   (vm_size_t) 1<<last_cpu);
	wei_space = (char *)io_map((vm_offset_t)WEI_SPACE,
				   (vm_size_t) 1<<last_cpu);
}

ka6200_config()
{
	register int	i;

	bi_settle();
	for (i = 0; i < nioa; i++) {
	    register struct ioa_node *ioa = &ioa_node[i];

	    probe_bi(i, XMI_BUS, 1<<ioa->bnode);
	}
}

ka6200_slave_config()
{
	ka6200_cache_on();
}

ka6200_reboot_ok()
{
	cca->hflag &= ~HFLAG_BOOTIP;
}

ka6200_start(i)
	int	i;
{
	cca_to_slave(i, "start 80000010");
}

/*
 * CRD And Friends
 */
int iqo_cnt = 1;
int iqo_dot = 100;

ka6200_crd()
{
	register int i;
	register struct ka62a *cpp = (struct ka62a *)
				cpu_node[cpu_number()].addr;

	i = 7;		/* lucky 7 */
	do {
	    if (cpp->csr2 & ka62aCSR2_IQO) {	/* INVAL Q OVERFLOW */
		if (iqo_dot && !(iqo_cnt % iqo_dot)) printf(".");
		iqo_cnt++;
		cpp->csr2 = (cpp->csr2 & ~ka62aCSR2_ERR) | ka62aCSR2_IQO;
#if	IQO_HACK
		ka62a_csr1_quad_iqo_hack();
#else	IQO_HACK
		*ka62a_csr1 |= ka62aCSR1_FCI;	/* invalidate */
		*ka62a_csr1 &= ~(ka62aCSR1_FCI|ka62aCSR1_FMISS);
						/* enable level 2 cache */
		*ka62a_csr1 |= ka62aCSR1_DLCKOUTEN;
#endif	IQO_HACK
		if (! (cpp->csr2 & ka62aCSR2_ERR)) {
		    return;
		}
	    }
	    else if (cpp->csr2 & ka62aCSR2_ERR) {	/* some other FMISS */
		printf("csr2: %b\n", cpp->csr2, ka62aCSR2);
		if (iqo_dot) printf("#");
		cpp->csr2 = cpp->csr2  | ka62aCSR2_ERR;
#if	IQO_HACK
		ka62a_csr1_quad_iqo_hack();
#else	IQO_HACK
		*ka62a_csr1 |= ka62aCSR1_FCI;   /* invalidate */
		*ka62a_csr1 &= ~(ka62aCSR1_FCI|ka62aCSR1_FMISS);
						/* enable level 2 cache */
		*ka62a_csr1 |= ka62aCSR1_DLCKOUTEN;
#endif	IQO_HACK
	    }
	} while ( (cpp->csr2 & ka62aCSR2_ERR) && --i > 0);
	if (i == 0) {
	    printf("\ncrd_ka62a: can't reset csr2 error\n");
	    print_ka6200(cpp);
	}

	if (cpp->ber & XMIBER_ES) {		/* some node problem */
	    if (cpp->ber & XMIBER_CRD) {		/* crd */
		for (i = 0; i < nmem; i++) {
		    register struct ms62a *mp = 
			(struct ms62a *)mem_node[i].addr;
		    register int tmp;

		    if (mp->ber & XMIBER_ES) {
			printf("\n");
			printf("NODE %x AT P %x\n",
				mem_node[i].node,
				pmap_extract(kernel_pmap, (vm_offset_t)mp));
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
	    }
	    else if (cpp->ber & XMIBER_ERR) {	/* std */
		print_ka6200(cpp);
		cpp->ber = XMIBER_ERR;
	    }
	    else if (cpp->ber & XMIBER_NSES) {	/* node specific */
		if (cpp->csr2 & ka62aCSR2_ERR)
		    print_ka6200(cpp);
	    }
	}

	for (i = 0; i < nmem; i++) {
	    register struct ms62a *mp = (struct ms62a *)mem_node[i].addr;
	    if (mp->ber & XMIBER_ES) {
		printf("\nMEMORY NODE %x AT P %x\n",
			mem_node[i].node,
			pmap_extract(kernel_pmap, (vm_offset_t)mp));
		print_mem6200(mp);
		mp->mctl1 |= M62aCTL1_ERR;
		mp->mctl2 |= M62aCTL2_ERR | M62aCTL2_DISH;
		mp->mecer |= M62aECER_ERR;
	    }
	}
}


ka6200_mchk(cmcf)
	char *	cmcf;
{
	register struct ka62a *cpp = (struct ka62a *)
					cpu_node[cpu_number()].addr;
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
	*ka62a_csr1 = *ka62a_csr1 | ka62aCSR1_DLCKOUTEN | ka62aCSR1_FMISS;
					/* for safety */
	printf("\n");
	printf("code %x vap %x istate1 %x istate2 %x pc %x psl %x\n",
		mcf->mc62_mcc, mcf->mc62_mrvaddr,
		mcf->mc62_istate1, mcf->mc62_istate2,
		mcf->mc62_pc, mcf->mc62_psl);

	printf("istate1 = %b\n",
		mcf->mc62_istate1, "\20\40\31OP\20\11CADR\10\01MSER");

	mser = mfpr(MSER);
	printf("mser = %b\n", mser, MSER_B);
	print_ka6200(cpp);

	if (mcf->mc62_mcc < 0x84 && mcf->mc62_mcc >= 0x80) {
	    if (!(mcf->mc62_istate2 & 0x8000)) {
		/*
		 * We have a bus error and can`t restart bit is 0.
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
#if	IQO_HACK
		ka62a_csr1_quad_iqo_hack();
#else	IQO_HACK
		*ka62a_csr1 |= ka62aCSR1_FCI;	/* invalidate */
		*ka62a_csr1 &= ~(ka62aCSR1_FCI|ka62aCSR1_FMISS);
						/* enable level 2 cache */
		*ka62a_csr1 |= ka62aCSR1_DLCKOUTEN;
#endif	IQO_HACK
		return;
	    }
	    else {
		/*
		 * In theory, we could blow the user process away, if
		 * a user process were running and then continue.
		 * But for now we`ll just die.
		 */
		printf("Can't restart bit is true.\n");
	    }
	}
	panic("mchk");
}


ka6200_clear_mchk(ioa_number)
	int	ioa_number;
{
	register struct dwmba *	dwp;
	register struct ka62a *	cpp;

	dwp = (struct dwmba *)ioa_node[ioa_number].addr;
	if (dwp) {
	    dwp->ber  = dwp->ber & XMIBER_ERR;
	    dwp->aesr = dwp->aesr & AESR_ERR;
	    dwp->besr = dwp->besr & BESR_ERR;
	}

	cpp = (struct ka62a *)cpu_node[cpu_number()].addr;
	if (cpp) {
	    cpp->ber  = cpp->ber & XMIBER_ERR;
	    cpp->csr2 = cpp->csr2 | ka62aCSR2_ERR;
	}
}

ka6200_halt(reboot)
	boolean_t	reboot;
{
	if (reboot) {
	    cca->hflag |= HFLAG_REBOOT;
	}
	cca->restartip[0] &= ~(1<<cpu_number());
	((struct ka62a *)cpu_node[cpu_number()].addr)->ber = XMIBER_NHALT;
}

ka6200_interrupt(which_cpu)
{
	register char x = 1;
	/* this must expand to a movb */
	ip_space[1<<which_cpu] = x;
}

/* ---- */
xmi_badaddr(addr, size)
	vm_offset_t	addr;
	int		size;
{
	register int spl;
	register struct ka62a *cpp;

	cpp = (struct ka62a *)cpu_node[cpu_number()].addr;
	spl = splblock();

	if (badaddr((char *)addr, size)) {
	    if (cpp) {
		cpp->ber  = cpp->ber & XMIBER_ERR;
		cpp->csr2 = cpp->csr2 |= ka62aCSR2_ERR;
	    }
	    splx(spl);
	    return (1);
	}
	splx(spl);
	return (0);
}

xmi_err(pc, psl, ioa_num)
	int	pc;
	int	psl;
	int	ioa_num;
{
	register struct ioa_node *ioa = &ioa_node[ioa_num];

	register struct dwmba *	dwp = (struct dwmba *)ioa->addr;
	register struct bi_node * biv = ioa->bddr;
	register struct ka62a *	cpp = 
		(struct ka62a *)cpu_node[cpu_number()].addr;

	if (pc)
	    printf("xmi_err(pc %x, psl %x, ioa %x)\n",
		   pc, psl, ioa);

	if (dwp) {
	    printf("Bcard Node %x V %x\n",
		   ioa->bnode,
		   biv);
	    print_bi(biv);
	    print_dwmba(dwp);

	    dwp->ber = dwp->ber & XMIBER_ERR;
	    dwp->aesr = dwp->aesr & AESR_ERR;
	    dwp->besr = dwp->besr & BESR_ERR;
	    biv->ber = (biv->ber & BER_ERR) | BER_UPEN;
	}

	printf("master cpu = Node %x\tV %x\n",
		master_cpu,
		cpp);
	if (cpp) {
	    print_ka6200(cpp);
	    cpp->ber  = cpp->ber & XMIBER_ERR;
	    cpp->csr2 = cpp->csr2 | ka62aCSR2_ERR;
	}
}

ka6200_wtime(pc, psl, pcbp)
	int	pc;
	int	psl;
	pcb_t	pcbp;
{
	register struct ka62a *cpp =
		(struct ka62a *)cpu_node[cpu_number()].addr;
	extern int bi_badaddr();
	extern int bi_badaddr_end();

	if (cpp->ber & XMIBER_WEI) {
	    cpp->ber = (cpp->ber & XMIBER_ERR) | XMIBER_WEI;
	    slave_attn(pc, psl, pcbp);
	}
	else if ((vm_offset_t)pc < (vm_offset_t)bi_badaddr_end &&
		 (vm_offset_t)pc > (vm_offset_t)bi_badaddr) {
	    cpp->ber = cpp->ber & XMIBER_ERR;
	}
	else {
	    printf("real timeout\n");
	    print_ka6200(cpp);
	    cpp->ber = cpp->ber & XMIBER_ERR;
	}
}


	/* check against an expected value */
#define VE(str,addr,mask,value) \
	if ((addr & mask) != value) {\
	    printf("\t%s: %x EXPECTED %x\n", str, addr, value);\
	}

	/* check against an expected value and set to that value*/
#define VS(str,addr,mask,value) \
	if ((addr & mask) != value) { \
	    register int new = ((addr&~mask)|value); \
	    printf("\t%s: %x CHANGED TO %x\n", str, addr, new); \
	    addr = new; \
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

print_ka6200(xcp)
	register struct ka62a *xcp;
{
	Pb("XMI   BUS Error Register", xcp->ber, XMIBER);
	Pvalb("Failed Address Register", xcp->fadr, XMIFADR);
	Pvalb("Control and Status Register 2", xcp->csr2, ka62aCSR2);

	if ((*ka62a_csr1&~0xf) != 0xfc0004c0) 
	    Pb("Control and Status Register 1", *ka62a_csr1, ka62aCSR1);

	if (xcp == (struct ka62a *)cpu_node[cpu_number()].addr)
	    verify_ssc();
}

print_mem6200(mp)
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

print_dwmba(ip)
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
	register int i;
	register struct cpu_node *cp = cpu_node;
	register struct mem_node *mp = mem_node;

	for (i = 0; i < NCPUS; i++, cp++) {
	    if (cp->addr) {
		printf("CPU %x\tNODE %x\n", i, cp->node);
		print_ka6200((struct ka62a *)cp->addr);
	    }
	}

	for (i = 0; i < nmem; i++, mp++) {
	    printf("MEM %x\tNODE %x\n", i, mp->node);
	    print_mem6200((struct ms62a *)mp->addr);
	}

	dumpdwmba();
}
dumpdwmba()
{
	register struct ioa_node *ip = ioa_node;
	register int i, j;

	for (i = 0; i < nioa; i++, ip++) {
	    printf("IOA %x\tNODE %x\tBNODE %x\t A/B %x/%x PHYS %x\n",
		   i,
		   ip->node,
		   ip->bnode,
		   ip->addr,
		   ip->bddr,
		   ip->bi_paddr);
	    print_dwmba((struct dwmba *)ip->addr);
	    for (j = 0; j < BI_MAX_NODE; j++) {
		if (ip->bi_present & (1<<j)) {
		    printf("BI NODE %x\n", j);
		    print_bi(&ip->bi_vaddr[j]);
		}
	    }
	}
}


#ifndef lint
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
#endif lint

verify_ssc()
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

cca_to_slave(no, msg)
int no;
char *msg;
{
	register struct com_buf *cbp = &cca->buf[no];
	register int len = strlen(msg);
	register int cnt = 1000;

	while ( (cbp->flags & XCBUF_RXRDY) && cnt-- > 0);
	if (cnt <= 0) {
		printf("\tcca: Cannot get interlock, giving up\n");
		return;
	}
	bcopy(msg, cbp->rx, len);
	cbp->rxlen = len;
	cbp->flags |= XCBUF_RXRDY;
}

#if 0
static int putsl();
cca_snarf(no, verbose)
int no;
{
	register int bit = 1<<no;
	register struct com_buf *cbp = &cca->buf[no];

	while (! (cca->ready[0] & bit));
	if (verbose)
		putsl(no, cbp->tx, cbp->txlen);
	cca->ready[0] &= ~(1<<no);
}
#endif 0

/* XXXX XXXX XXXX XXXX */
/*
 * Stubs for stuff I don't want to deal with yet.
 */
int	printing_cpu;

move_console()
{
}

/*ARGSUSED*/
slave_attn(pc, psl, pcbp)
	int	pc, psl;
	pcb_t	pcbp;
{
}

#endif	VAX6200
