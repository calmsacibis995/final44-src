/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
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
 * $Log:	ka650.c,v $
 * Revision 2.5  91/06/19  12:00:58  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:48:15  rvb]
 * 
 * Revision 2.4  91/05/14  17:43:44  mrt
 * 	Correcting copyright
 * 
 * Revision 2.3  91/05/08  13:17:57  dbg
 * 	Add forward declarations (gcc fix).
 * 	[91/03/21            dbg]
 * 
 * Revision 2.2  90/01/11  11:45:40  dbg
 * 	Make ka650_init return CPU subtype.
 * 	[89/12/04            dbg]
 * 
 * Revision 2.1  89/08/03  16:28:05  rwd
 * Created.
 * 
 *  3-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *	KA650 model-dependent routines.
 */

#include <platforms.h>
#include <qd.h>
#include <qv.h>

#if	VAX650

#include <kern/cpu_number.h>
#include <mach/machine.h>

#include <vax/cpu_data.h>
#include <vax/io_map.h>
#include <vax/ka650.h>
#include <vax/mtpr.h>
#include <vax/cpmbx.h>

#include <vaxuba/ubavar.h>

extern int	v_console;

struct ka650_ssc *	ssc;		/* SSC chip */
struct ka650_cacr_bdr *	c2cntl;		/* 2nd level cache control */
long *			c2diag;		/* 2nd level cache diagnostic regs. */
struct ka650_mem *	ka650_mem;	/* memory controller */

struct sie {
    long  sie_pad;
    short sie_reserved;
    char  sie_version;
    char  sie_syscode;
} *sie;					/* system ID register */

vm_size_t		rawmem_size;

int	ka650_setup(), ka650_init(), ka650_config(),
	ka650_reboot_ok(), ka650_crd(), ka650_mchk(),
	ka650_clear_mchk(), ka650_halt();

struct model_dep ka650_model = {
	ka650_setup,
	ka650_init,
	ka650_config,
	0,				/* no slave_config */
	ka650_reboot_ok,
	ka650_crd,
	ka650_mchk,
	ka650_clear_mchk,
	ka650_halt,
	0,				/* no interrupt */
	6
};

/*
 * Map required memory for the 650, and find the console.
 * Called running virtual, but with VM not initialized.
 */
ka650_setup()
{
	/*
	 * Map in the SSC, 2nd level cache, system ID register, and
	 * memory controller.
	 */
	ssc = (struct ka650_ssc *)io_map((vm_offset_t)SSC,
					sizeof(struct ka650_ssc));
	c2diag = (long *)io_map((vm_offset_t)C2DIAG, C2DIAG_SIZE);
	c2cntl = (struct ka650_cacr_bdr *)io_map((vm_offset_t)C2CNTL,
					sizeof(struct ka650_cacr_bdr));
	ka650_mem = (struct ka650_mem *)io_map((vm_offset_t)MEM_CTL,
					sizeof(struct ka650_mem));
	sie = (struct sie *)io_map((vm_offset_t)ROM650_RUN,
					sizeof(struct sie));

	/*
	 * Point to the console mailbox.
	 */
	cpmbx = (char *)ssc->nv_ram;

	/*
	 * Enable the caches.
	 */
	ka650_cache_on();

	/*
	 * Map in the Qbus.
	 */
	qbus_map();

	/*
	 * Configure the console, if it is in use.
	 */
	switch ((cpmbx[1]&0xe0)>>5) {
#if	NQV > 0
	    case 1:
		/*
		 * QVSS
		 */
		qvcons_init();
		v_console = 1;
		break;
#endif
#if	NQD > 0
	    case 2:
		/*
		 * QDSS
		 */
		qdcons_init();
		v_console = 1;
		break;
#endif
	    default:
		v_console = 0;
	}
}

int
ka650_init()
{
	register struct ka650_mem *mp = ka650_mem;

	extern int	D_float;
	static char *cpumodes[] = {
		"Normal",
		"Language Inquiry",
		"Test",
		"Manufacturing"
	};
	char bdr;

	printf("MicroVax-III (with%s FPU, SYSCODE:%d, ROM Rev:%d)\n",
	       D_float ?"" : "out",
	       sie->sie_syscode,
	       sie->sie_version);

	ka650_memctl(mp);
	ka650_cacr_bdr(c2cntl);

	bdr = c2cntl->bdr;
	printf("BDR: HALT %sabled, %d baud, %s Mode\n",
		(bdr&KA650BDR_HLTENB)?"En":"Dis",
		(1<<((bdr&KA650BDR_BRS)>>4))*300,
		cpumodes[bdr&3]);

	/*
	 * Set up memory controller.
	 */
	mtpr(MSER, mfpr(MSER) & MSER_ERR);	/* c1 cache and parity */
	c2cntl->cacr |= c2cntl->cacr & CACR_ERR;
						/* c2 cache parity error */
	mp->mem_csr16 = mp->mem_csr16 & M16_ERR;
						/* clear memory errors */
	mp->mem_csr17 |= M17_CRD;		/* enable crd */
	mp->mem_dser = mp->mem_dser & DSER_ERR;
						/* clear qbus nxms */

	return (CPU_SUBTYPE_UVAXIII);
}

ka650_config()
{
	/*
	 * There is only one QBus on a MicroVax III, and
	 * qbus_init has already disguised it as a Unibus.
	 */
	unifind(&uba_hd[0]);
	numuba++;
}

ka650_reboot_ok()
{
	set_cpmbx(0);	/* ? */
}

struct mc650frame {
	int	mc65_bcnt;		/* byte count == 0xe */
	int	mc65_mcc;		/* machine check code */
	int	mc65_mrvaddr;		/* most recent virtual addr */
	int	mc65_istate1;		/* internal state */
	int	mc65_istate2;		/* internal state */
	int	mc65_pc;		/* trapped pc */
	int	mc65_psl;		/* trapped psl */
};

ka650_crd()
{

	struct ka650_mem *mp = ka650_mem;

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

int ka650_mchk(cmcf)
	char *	cmcf;
{
	register struct mc650frame *mcf = (struct mc650frame *)cmcf;

	printf("\n");
	printf("code %x vap %x istate1 %x istate2 %x pc %x psl %x\n",
	    mcf->mc65_mcc, mcf->mc65_mrvaddr,
	    mcf->mc65_istate1, mcf->mc65_istate2,
	    mcf->mc65_pc, mcf->mc65_psl);
	ka650_crd();

	return (0);
}

/*ARGSUSED*/
int ka650_clear_mchk(nioa)
	int	nioa;
{
}

ka650_halt(reboot)
	boolean_t	reboot;
{
	if (reboot) {
	    set_cpmbx(CPMBX_REBOOT);
	}
	else {
	    set_cpmbx(CPMBX_HALT);
	    printf("\nHalting...\n");
	}

	for (;;)
	    asm("halt");
	/*NOTREACHED*/
}

/* ---- */

static verify_memctl();		/* forward */
static verify_cacr_bdr();	/* forward */
static verify_ssc();		/* forward */

ka650_cache_on()
{
	register int i;

	/* enable level 1 cache */
	mtpr(CADR, 0xf0);

	/* enable cacr and bdr addresses in ssc */
	ssc->ssc_ssccr = (ssc->ssc_ssccr & ~0xff) | 0x77;
	verify_ssc(ssc);

	/* flush level 2 cache */
	for (i = 0; i < C2DIAG_SIZE/sizeof(long); i++)
	    c2diag[i] = 0;

	/* enable level 2 cache */
	c2cntl->cacr = (c2cntl->cacr & ~0x10) | 0x10;
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

	/* check against an expected value */
#define VE(str,addr,mask,value) \
	if ((addr & mask) != value) { \
		printf("%s: %x EXPECTED %x\n", str, addr, value); \
	}

	/* check against an expected value and set to that value*/
#define VS(str,addr,mask,value) \
	if ((addr & mask) != value) { \
		register int new = ((addr&~mask)|value); \
		printf("%s: %x CHANGED TO %x\n", str, addr, new); \
		addr = new; \
	}

	/* check for bits that must be set to 1 to be cleared */
#define VC(str,addr,mask) \
	if ((addr & mask) == mask) { \
		printf("%s: %x CHANGED TO ", str, addr); \
		addr = mask; \
		printf("%x\n", addr); \
	}

static verify_memctl(mp)
register struct ka650_mem *mp;
{
	int qbm = mp->mem_qbmbr & ~( (1<<MEM_QBM_SHFT) - 1);
	extern vm_size_t mem_size;
	extern int	mem_bitmap_size;
	extern vm_offset_t mem_bitmap;

		/* read only register */
	VE("System Configuration Register", mp->mem_scr, 0xffff, 0xc000);

	if (mem_size != mem_bitmap) {
		printf("mem_size %x != mem_bitmap %x\n", mem_size, mem_bitmap);
	}

	if (mem_bitmap + mem_bitmap_size != qbm) {
		printf("mem_bitmap %x + mem_bitmap_size %x != qbm %x\n",
			mem_bitmap,
			mem_bitmap_size,
			qbm);
		printf("memory bit map appears incorrect.  TILT\n");
	}

	if (qbm + 32*1024 != rawmem_size) {
		printf("qbm %x + 32*1024 != rawmem_size %x\n",
			qbm,
			rawmem_size);
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

		/* ^P halts
	VS("SSC Configuration Register", sp->ssc_ssccr, 0xffff80ff, 0xd48077);
		 */
		/* F5 halts */
	VS("SSC Configuration Register", sp->ssc_ssccr, 0xffff80ff, 0xd40077);

	VS("Timer 0 Control Register", sp->ssc_tcr0, 0xff, 00);
	VC("Timer 0 Control Register", sp->ssc_tcr0, 0x80000000);
	VC("Timer 0 Control Register", sp->ssc_tcr0, 0x80);
	VS("Timer 0 Interrupt Vector", sp->ssc_tivr0, 0xff, 0x78);

	VS("Timer 1 Control Register", sp->ssc_tcr1, 0xff, 00);
	VC("Timer 1 Control Register", sp->ssc_tcr1, 0x80000000);
	VC("Timer 1 Control Register", sp->ssc_tcr1, 0x80);
	VS("Timer 1 Interrupt Vector", sp->ssc_tivr1, 0xff, 0x7c);
}

#ifdef	__STDC__
#define PR(str,ptr) printf("%s:\t ## ptr ## \t(@%x) = %x\n", str, &ptr, ptr)
#else
#define PR(str,ptr) printf("%s:\t/**/ptr/**/\t(@%x) = %x\n", str, &ptr, ptr)
#endif	/* __STDC__ */

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
