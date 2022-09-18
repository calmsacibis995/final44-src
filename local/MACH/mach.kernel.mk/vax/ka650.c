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
 * $Log:	ka650.c,v $
 * Revision 2.7  89/02/25  20:20:29  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  88/09/27  17:32:13  rvb
 * 	Fixed Log
 * 
 * Revision 2.5  88/09/27  16:08:37  rvb
 * 	ka650_cntlp says let ^P at console work vs break.
 * 	[88/09/23            rvb]
 *
 * Revision 2.4  88/08/24  02:59:26  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  22:07:15  mwyoung]
 * 
 * Revision 2.3  88/08/10  10:24:42  rvb
 * CBCTR register seems to have made it thru as 4 vs the spec
 * Rename a couple registers for ssc printout
 * 
 * 11-Feb-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 11-Dec-87  Stephen Schwab (schwab) at Carnegie-Mellon University
 *	For 650, use ssc timer 0 vs uVax clock and set interrupts for
 *	timer0 and timer1 to dec standard of 0x78 and 0x7c
 *
 * 02-Nov-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Created
 *
 */

#include <cputypes.h>

#if	VAX650

#include <sys/types.h>
#include <vm/vm_kern.h>
#include <vax/ka650.h>
#include <vax/mtpr.h>
#include <vax/uvax.h>
#include <vax/mem.h>		/* for mcraddr[] */

static verify_memctl(), verify_cacr_bdr(), verify_ssc();

#ifndef	lint
static void pr_memctl(), pr_cacr_bdr(), pr_ssc();
#endif	lint


	/* ka650 specific structures */
struct ka650_ssc *ssc;
struct ka650_cacr_bdr *c2cntl;
int ka650_cntlp = 1;
long *c2diag;

	/* uVax specific structures; but found in a different
	 * place on the uVaxII vs MAYFAIR.
	 */
char *firmware;
char *cpmbx;
static rawmem_size;

#define vmdcl(space,type)\
		extern type *space
#define vmbind(space,type,addr,size)\
		space = (type *)kmem_alloc_pageable(kernel_map, size),\
		ioaccess((caddr_t)addr, (vm_offset_t) space, size)

	/*
	 * Map in some of the local IO space of the ka650 and enable the
	 * level 1 and level 2 caches.
	 */
ka650_init()
{
	register int i;
	vmdcl(ssc, struct ka650_ssc);
	vmdcl(c2diag, long);
	vmdcl(c2cntl, struct ka650_cacr_bdr);
	vmdcl(firmware, char);

	vmbind(ssc, struct ka650_ssc, SSC, SSC_SIZE);
	vmbind(c2diag, long, C2DIAG, C2DIAG_SIZE);
	vmbind(c2cntl, struct ka650_cacr_bdr, C2CNTL, C2CNTL_SIZE);

			/* enable level 1 cache */
	mtpr(CADR, 0x000000f0);
			/* enable cacr bdr addresses in ssc*/
	ssc->ssc_ssccr = (ssc->ssc_ssccr & ~0xff) | 0x77;
	verify_ssc(ssc);
			/* flush 2nd level cache */
	for (i=0; i < (C2DIAG_SIZE/sizeof(long)); i++)
		c2diag[i] = 0;
			/* enable 2nd level */
	c2cntl->cacr = ((c2cntl->cacr & ~0x10) | 0x10);


		/* general uVax structures */
	vmbind(firmware, char, ROM650_RUN, ROM650_SIZE);
	cpmbx = (char *)ssc->nv_ram;	/* mail box is at start of nonvolatile ram */
}

ka650_cacr_bdr(p)
struct ka650_cacr_bdr *p;
{
	verify_cacr_bdr(p);
}

ka650_memctl(mp)
struct ka650_mem *mp;
{
register int i;
register int *csr;
register int meg = 0;

	for (i = 0, csr = mp->mem_csr; i < 0x10; i++, csr++) {
		if (*csr & 0x80000000 && *csr & MEM_4MEG)
			meg+=4;
		else if (*csr & 0x80000000)
			meg+=1;
	}
        rawmem_size = meg * 0x100000;
	printf("CMCTL: %d Meg.  Bank #'s ", meg);
	for (i = 0, csr = mp->mem_csr; i < 0x10; i++, csr++)
		if (*csr & 0x80000000)
			printf("%x", (*csr & MEM_BANK) >> MEM_BANK_SHFT);
		else
			printf("-");
	printf(".  Sizes ");
	for (i = 0, csr = mp->mem_csr; i < 0x10; i++, csr++)
		if (*csr & 0x80000000 && *csr & MEM_4MEG)
			printf("4");
		else if (*csr & 0x80000000)
			printf("1");
		else
			printf("-");
	printf("\n", meg);

	verify_memctl(mp);

}

mchk_ka650(cmcf)
caddr_t cmcf;
{
struct mc650frame {
	int	mc65_bcnt;		/* byte count == 0xe */
	int	mc65_mcc;		/* machine check code */
	int	mc65_mrvaddr;		/* most recent virtual addr */
	int	mc65_istate1;		/* internal state */
	int	mc65_istate2;		/* internal state */
	int	mc65_pc;		/* trapped pc */
	int	mc65_psl;		/* trapped psl */
};
	register struct mc650frame *mcf = (struct mc650frame *)cmcf;

	printf("\n");
	printf("code %x vap %x istate1 %x istate2 %x pc %x psl %x\n",
	    mcf->mc65_mcc, mcf->mc65_mrvaddr,
	    mcf->mc65_istate1, mcf->mc65_istate2,
	    mcf->mc65_pc, mcf->mc65_psl);
	crd_ka650();
}

crd_ka650()
{

	struct ka650_mem *mp = (struct ka650_mem *)mcraddr[0];

	if (mfpr(MSER) & MSER_ERR)
		printf("MSER = %x\n", mfpr(MSER));

	if (c2cntl->cacr & CACR_ERR)
		printf("CACR = %x\n", c2cntl->cacr);

	if (mp->mem_csr16 & M16_ERR)
		printf("MEMCSR16 = %x Page = %x Syndrome = %x\n",
			mp->mem_csr16,
			(mp->mem_csr16&M16_PAGE)>>M16_SHIFT,
			mp->mem_csr16 & M16_SYNDROME);

	if (mp->mem_dser & DSER_ERR) {
		printf("DSER = %x ", mp->mem_dser);
		if (mp->mem_dser & (DSER_Q22NXM|DSER_Q22PE))
			printf("QBEAR = %x\n", mp->mem_qbear);
		else if (mp->mem_dser & (DSER_Q22GRNT|DSER_DMANXM))
			printf("DEAR = %x\n", mp->mem_dear);
		else
			printf("\n");
	}

	mtpr(MSER, mfpr(MSER) & MSER_ERR);	/* c1 cache & parity */
	c2cntl->cacr |= c2cntl->cacr & CACR_ERR;/* c2 cache parity error */

	mp->mem_csr16 = mp->mem_csr16 & M16_ERR;/* clear memory errors */
	mp->mem_csr17 = mp->mem_csr17&(~M17_CRD);/* enable crd */

	mp->mem_dser = mp->mem_dser & DSER_ERR;	/* clear qbus nxm's ... */
}

	/* check against an expected value */
#define VE(str,addr,mask,value) \
	if ((addr & mask) != value) {\
		printf("%s: %x EXPECTED %x\n", str, addr, value);\
	}

	/* check against an expected value and set to that value*/
#define VS(str,addr,mask,value) \
	if ((addr & mask) != value) {register int new = ((addr&~mask)|value);\
		printf("%s: %x CHANGED TO %x\n", str, addr, new);\
		addr = new;\
	}

	/* check for bits that must be set to 1 to be cleared */
#define VC(str,addr,mask) \
	if ((addr & mask) == mask) {\
		printf("%s: %x CHANGED TO ", str, addr);\
		addr = mask;\
		printf("%x\n", addr);\
	}

static verify_memctl(mp)
register struct ka650_mem *mp;
{
int qbm = mp->mem_qbmbr & ~( (1<<MEM_QBM_SHFT) - 1);
extern vm_size_t mem_size;
extern mem_bitmap_size, mem_bitmap;

		/* read only register */
	VE("System Configuration Register", mp->mem_scr, 0xffff, 0xc000);

	if (mem_size != mem_bitmap) {
		printf("mem_size %x != mem_bitmap %x\n", mem_size, mem_bitmap);
	}

	if (mem_bitmap + mem_bitmap_size != qbm) {
		printf("mem_bitmap %x + mem_bitmap_size %x != qbm %x\n", mem_bitmap, mem_bitmap_size, qbm);
		printf("memory bit map appears incorrect.  TILT\n");
	}

	if (qbm + 32*1024 != rawmem_size) {
		printf("qbm %x + 32*1024 != rawmem_size %x\n", qbm, rawmem_size);
		printf("Q22 Bus Map Base Register is incorrectly initialized.  TILT\n");
	}

/*	VE("Main Memory Configuration Reg", mp->mem_csr[0x0], -1, 0x80000016);
	VE("Main Memory Configuration Reg", mp->mem_csr[0x1], -1, 0x80400016);
	VE("Main Memory Configuration Reg", mp->mem_csr[0x2], -1, 0x16);
	VE("Main Memory Configuration Reg", mp->mem_csr[0x3], -1, 0x16);
	VE("Main Memory Configuration Reg", mp->mem_csr[0x4], -1, 0x80800016);
	VE("Main Memory Configuration Reg", mp->mem_csr[0x5], -1, 0x80c00016);
	VE("Main Memory Configuration Reg", mp->mem_csr[0x6], -1, 0x16);
	VE("Main Memory Configuration Reg", mp->mem_csr[0x7], -1, 0x16);

	VE("Main Memory Configuration Reg", mp->mem_csr[0x8], -1, 0);
	VE("Main Memory Configuration Reg", mp->mem_csr[0x9], -1, 0);
	VE("Main Memory Configuration Reg", mp->mem_csr[0xa], -1, 0);
	VE("Main Memory Configuration Reg", mp->mem_csr[0xb], -1, 0);
	VE("Main Memory Configuration Reg", mp->mem_csr[0xc], -1, 0);
	VE("Main Memory Configuration Reg", mp->mem_csr[0xd], -1, 0);
	VE("Main Memory Configuration Reg", mp->mem_csr[0xe], -1, 0);
	VE("Main Memory Configuration Reg", mp->mem_csr[0xf], -1, 0);
*/
}

static verify_cacr_bdr(p)
register struct ka650_cacr_bdr *p;
{
	VE("Cache Control Register", p->cacr, 0xff, 0x90);
		/* read only */
	VE("Boot and Diagnostic Register", p->bdr, 0x8f, 0x80);
}

static verify_ssc(sp)
register struct ka650_ssc *sp;
{
		/* The 5 values tested below REALLY should never be changed */
	VE("SSC Base Address Register", sp->ssc_sscbr, 0x3fffffff, 0x20140000);

	VE("CACR Address Decode Match Register", sp->ssc_cdmtr, 0x3fffffff, 0x20084000);
	VE("CACR Decode Mask Register", sp->ssc_cdmkr, 0x3fffffff, 00);

	VE("BDR Address Decode Match Register", sp->ssc_mdbtr, 0x3fffffff, 0x20084004);
	VE("BDR Decode Mask Register", sp->ssc_bdmkr, 0x3fffffff, 00);
		/* End of the 5 values */

		/* This value is not set up according to the spec
	VE("CDAL Bus Timeout Control Register", sp->ssc_cbtcr, 0xffffff, 0x3a98);
		 */
	VE("CDAL Bus Timeout Control Register", sp->ssc_cbtcr, 0xffffff, 0x4);

		/* ^P halts */
	if (ka650_cntlp) {
		VS("SSC Configuration Register", sp->ssc_ssccr, 0xffff80ff, 0xd48077);
	} else {
		/* F5 halts */
		VS("SSC Configuration Register", sp->ssc_ssccr, 0xffff80ff, 0xd40077);
	}

	VS("Timer 0 Control Register", sp->ssc_tcr0, 0xff, 00);
	VC("Timer 0 Control Register", sp->ssc_tcr0, 0x80000000);
	VC("Timer 0 Control Register", sp->ssc_tcr0, 0x80);
	VS("Timer 0 Interrupt Vector", sp->ssc_tivr0, 0xff, 0x78);

	VS("Timer 1 Control Register", sp->ssc_tcr1, 0xff, 00);
	VC("Timer 1 Control Register", sp->ssc_tcr1, 0x80000000);
	VC("Timer 1 Control Register", sp->ssc_tcr1, 0x80);
	VS("Timer 1 Interrupt Vector", sp->ssc_tivr1, 0xff, 0x7c);
}

#define PR(str,ptr) printf("%s:\t/**/ptr/**/\t(@%x) = %x\n", str, &ptr, ptr)

#ifndef	lint
static void  pr_memctl(mp)
register struct ka650_mem *mp;
{
	PR("System Configuration Register", mp->mem_scr);
	PR("System Error Register", mp->mem_dser);
	PR("Master Error Address Register", mp->mem_qbear);
	PR("Slave Error Address Register", mp->mem_dear);
	PR("q-22 Bus Map Base Register", mp->mem_qbmbr);

	PR("Main Memory Configuration Reg", mp->mem_csr[0x0]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0x1]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0x2]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0x3]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0x4]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0x5]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0x6]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0x7]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0x8]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0x9]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0xa]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0xb]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0xc]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0xd]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0xe]);
	PR("Main Memory Configuration Reg", mp->mem_csr[0xf]);

	PR("Main Memory Error Status Register", mp->mem_csr16);
	PR("Main Memory Control/Diag Status Reg", mp->mem_csr17);
}

static void pr_cacr_bdr(p)
register struct ka650_cacr_bdr *p;
{
	PR("Cache Control Register", p->cacr);
	PR("Boot and Diagnostic Register", p->bdr);
}

static void pr_ssc(sp)
register struct ka650_ssc *sp;
{
	PR("SSC Base Address Register", sp->ssc_sscbr);
	PR("SSC Configuration Register", sp->ssc_ssccr);
	PR("CDAL Bus Timeout Control Register", sp->ssc_cbtcr);
	PR("Diagnostic LED Register", sp->ssc_dledr);

	PR("Timer 0 Control Register", sp->ssc_tcr0);
	PR("Timer 0 Interval Register", sp->ssc_tir0);
	PR("Timer 0 Next Interval Register", sp->ssc_tnir0);
	PR("Timer 0 Interrupt Vector", sp->ssc_tivr0);

	PR("Timer 1 Control Register", sp->ssc_tcr1);
	PR("Timer 1 Interval Register", sp->ssc_tir1);
	PR("Timer 1 Next Interval Register", sp->ssc_tnir1);
	PR("Timer 1 Interrupt Vector", sp->ssc_tivr1);

	PR("CACR Decode Match Register", sp->ssc_cdmtr);
	PR("CACR Decode Mask Register", sp->ssc_cdmkr);

	PR("BDR Decode Match Register", sp->ssc_mdbtr);
	PR("BDR Decode Mask Register", sp->ssc_bdmkr);

	printf("%s: ptr (@%x) = ...\n", "Battery Backed-up RAM", sp->nv_ram);
}
#endif	lint
#endif	VAX650
