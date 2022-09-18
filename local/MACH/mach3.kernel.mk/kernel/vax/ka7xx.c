/*
 * HISTORY
 * $Log:	ka7xx.c,v $
 * Revision 2.2  91/06/19  12:01:02  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:49:49  rvb]
 * 
 */

/*
 * Model-dependent code common to 730, 750, 780.
 */

/*
 * Most of this code was originally Berkeley's.
 */
#include <cpus.h>
#include <platforms.h>
#include <mach_mpm.h>

#if defined(VAX780) || defined(VAX750) || defined(VAX730)

#include <kern/cpu_number.h>
#include <mach/machine.h>
#include <kern/time_out.h>

#include <sys/types.h>

#include <vax/cpu_data.h>
#include <vax/cons.h>
#include <vax/mem.h>
#include <vax/mtpr.h>
#include <vax/nexus.h>

#if	NMACH_MPM > 0
#include <vax/io_map.h>
#include <vax/ma780reg.h>
#include <vax/ma780var.h>
#endif	NMACH_MPM > 0

#include <vaxuba/ubareg.h>

int	ka7xx_reboot_ok(), ka7xx_crd(), ka7xx_halt();

/*
 * Model description
 */
#if VAX730
int	ka730_init(), ka730_config(), ka730_mchk(), ka730_clear_mchk();

struct model_dep ka730_model = {
	(int (*)()) 0,	/* no setup */
	ka730_init,
	ka730_config,
	(int (*)()) 0,	/* no slave_config - no multiprocessor */
	ka7xx_reboot_ok,
	ka7xx_crd,
	ka730_mchk,
	ka730_clear_mchk,
	ka7xx_halt,
	(int (*)()) 0,	/* no processor interrupt - no multiprocessor */
	1
};

short	nexty730[NNEX730] = {
	NEX_MEM16,	NEX_ANY,	NEX_ANY,	NEX_ANY,
	NEX_ANY,	NEX_ANY,	NEX_ANY,	NEX_ANY
};

caddr_t	umaddr730[1] = {
	(caddr_t) UMEM730
};

struct nexusconnect xxx730 = {
	NNEX730, NEX730, DW730, NBDP730, umaddr730, nexty730
};
#endif

#if VAX750
int	ka750_init(), ka750_config(), ka750_mchk(), ka750_clear_mchk();

struct model_dep ka750_model = {
	(int (*)()) 0,	/* no setup */
	ka750_init,
	ka750_config,
	(int (*)()) 0,	/* no slave_config - no multiprocessor */
	ka7xx_reboot_ok,
	ka7xx_crd,
	ka750_mchk,
	ka750_clear_mchk,
	ka7xx_halt,
	(int (*)()) 0,	/* no processor interrupt - no multiprocessor */
	1
};

short	nexty750[NNEX750] = {
	NEX_MEM16,	NEX_MEM16,	NEX_MEM16,	NEX_MEM16,
	NEX_MBA,	NEX_MBA,	NEX_MBA,	NEX_MBA,
	NEX_UBA0,	NEX_UBA1,	NEX_ANY,	NEX_ANY,
	NEX_ANY,	NEX_ANY,	NEX_ANY,	NEX_ANY
};

caddr_t	umaddr750[2] = {
	(caddr_t) UMEM750(0), (caddr_t) UMEM750(1)
};

struct nexusconnect cmi750 = {
	NNEX750, NEX750, DW750, NBDP750, umaddr750, nexty750
};
#endif

#if VAX780
int	ka780_init(), ka780_config(), ka780_slave_config(),
	ka780_mchk(), ka780_clear_mchk(), ka780_interrupt();

#if	NMACH_MPM > 0
int	ka780_find_cpus();
#endif	NMACH_MPM > 0

struct model_dep ka780_model = {
#if	NMACH_MPM > 0
	ka780_find_cpus,
#else
	(int (*)()) 0,	/* no setup */
#endif	NMACH_MPM > 0
	ka780_init,
	ka780_config,
	ka780_slave_config,
	ka7xx_reboot_ok,
	ka7xx_crd,
	ka780_mchk,
	ka780_clear_mchk,
	ka7xx_halt,
	ka780_interrupt,
	2
};

caddr_t	umaddr780[4] = {
	(caddr_t) UMEM780(0), (caddr_t) UMEM780(1),
	(caddr_t) UMEM780(2), (caddr_t) UMEM780(3)
};

struct nexusconnect sbi780 = {
	NNEX780, NEX780, DW780, NBDP780, umaddr780, 0
};
#endif

#if VAX780
union cpusid_780 {
	unsigned int	sid;
	struct sid780 {
		unsigned int	serial_number:12,
				plant:3,
				eco_level:8,
				is_785:1,
				cpu_type:8;
	} sid780;
};

#if	NMACH_MPM
/*
 * Find multiport memory controller, so we know our CPU
 * number.
 */
ka780_find_cpus()
{
	register struct nexus *nxp, *nxv;
	register int	    i, nex_csr;

	for (i = 0, nxp = NEX780;
	     i < NNEX780;
	     i++, nxp++) {

	    nxv = (struct nexus *)io_map((vm_offset_t)nxp, sizeof(int));
	    if (!badaddr((char *)nxv, sizeof(int))) {
		nex_csr = nxv->nex_csr;
		if ((nex_csr & NEX_APD) == 0) {
		    nex_csr &= NEX_TYPE_MASK;
		    if (nex_csr == NEX_MPM0 ||
			nex_csr == NEX_MPM1 ||
			nex_csr == NEX_MPM2 ||
			nex_csr == NEX_MPM3) {

			/*
			 * Multiport memory type word also is used
			 * for the CPU number.  Since there are
			 * two CPU number bits, we can have at most
			 * 4 cpus.
			 */
			for (i = 0; i < 4; i++) {
			    if (i >= NCPUS)
				break;
			    machine_slot[i].is_cpu = TRUE;
			}
			mpm_port_addr = (int *)nxv;
			master_cpu = cpu_number();
			printf("Master cpu at slot %d\n", master_cpu);
			break;	/* exit loop */
		    }
		}
	    }
	    io_unmap((vm_offset_t)nxv, sizeof(int));
	}
}
#endif	NMACH_MPM

int ka780_init()
{
	union cpusid_780	cpusid;
	int	subtype;

	cpusid.sid = mfpr(SID);

	printf(
	    "VAX 11/78%c, serial#%d(%d), hardware ECO level=%d(%d)\n",
	    (cpusid.sid780.is_785) ? '5' : '0',
	    cpusid.sid780.serial_number,
	    cpusid.sid780.plant,
	    (cpusid.sid780.eco_level >> 4) & 0xf,
	    cpusid.sid780.eco_level & 0xf);

	if (cpusid.sid780.is_785 & 0x100)
		subtype = CPU_SUBTYPE_VAX785;
	else
		subtype = CPU_SUBTYPE_VAX780;

	ka780_cache_on();

	return (subtype);
}

int ka780_config()
{
	probenexi(&sbi780);

	ka7xx_memenable();
}

ka780_cache_on()
{
	mtpr(SBIMT, 0x200000);
	if ((mfpr(ACCS) & 0xff) != 0) {
		printf("Enabling FPA\n");
		mtpr(ACCS, 0x8000);
	}
}

#if	NMACH_MPM > 0
extern	int	nummpm;
#endif	NMACH_MPM > 0

int ka780_slave_config()
{
	union cpusid_780	cpusid;
	int	subtype;

	cpusid.sid = mfpr(SID);
	if (cpusid.sid780.is_785 & 0x100)
		subtype = CPU_SUBTYPE_VAX785;
	else
		subtype = CPU_SUBTYPE_VAX780;

	ka780_cache_on();
#if	NMACH_MPM > 0
	{
	    register int i;

	    for (i = 0; i < nummpm; i++)
		hack_mpm(i);
	}
#endif	NMACH_MPM > 0

	return (subtype);
}

/*ARGSUSED*/
ka780_clear_mchk(nioa)
	int	nioa;
{
	mtpr(SBIFS, 0);
}

ka780_interrupt(which_cpu)
	int	which_cpu;
{
#if	NMACH_MPM > 0
	if (nummpm > 0)
		mpm_interrupt_processor(which_cpu);
#endif	NMACH_MPM > 0
}

#endif

#if VAX750
int ka750_init()
{
	union cpusid {
	    unsigned int	sid;
	    struct sid750 {
		unsigned int	hardware_revision:8,
				microcode_revision:8,
				:8,
				cpu_type:8;
	    } sid750;
	} cpusid;

	cpusid.sid = mfpr(SID);

	printf("VAX 11/750, hardware level = %d, microcode level = %d\n",
	       cpusid.sid750.hardware_revision,
	       cpusid.sid750.microcode_revision);

	mtpr(CADR, 0);	/* turn on cache */

	return (CPU_SUBTYPE_VAX750);
}

int ka750_config()
{
	probenexi(&cmi750);
	ka7xx_memenable();
}

/*ARGSUSED*/
ka750_clear_mchk(nioa)
	int	nioa;
{
	mtpr(MCESR, 0xf);
}

#endif

#if VAX730
ka730_init()
{
	printf("VAX 11/730\n");
	return (CPU_SUBTYPE_VAX730);
}

int ka730_config()
{
	probenexi(&xxx730);

	ka7xx_memenable();
}

/*ARGSUSED*/
ka730_clear_mchk(nioa)
	int	nioa;
{
	mtpr(MCESR, 0xf);
}

#endif

int ka7xx_reboot_ok()
{
	/*
	 * Clear restart inhibit flags.
	 */
	tocons(TXDB_CWSI);
	tocons(TXDB_CCSI);

}


/*
 * Memenable enables the memory controller corrected data reporting.
 * This runs at regular intervals, turning on the interrupt.
 * The interrupt is turned off, per memory controller, when error
 * reporting occurs.  Thus we report at most once per memintvl.
 */
int	memintvl = MEMINTVL;

ka7xx_memenable()
{
	register struct mcr *mcr;
	register int m;

	for (m = 0; m < nmcr; m++) {
		mcr = mcraddr[m];
		switch (mcrtype[m]) {
#ifdef VAX780
#if	NMACH_MPM > 0
		case M780MA:
			M780MA_ENA(mcr);
			break;
#endif	NMACH_MPM > 0
		case M780C:
			M780C_ENA(mcr);
			break;
		case M780EL:
			M780EL_ENA(mcr);
			break;
		case M780EU:
			M780EU_ENA(mcr);
			break;
#endif
#ifdef VAX750
		case M750:
			M750_ENA(mcr);
			break;
#endif
#ifdef VAX730
		case M730:
			M730_ENA(mcr);
			break;
#endif
		}
	}
	if (memintvl > 0)
		timeout(ka7xx_memenable, (caddr_t)0, memintvl*hz);
}


/*
 * Corrected-read-data interrupt.
 */
#if	NMACH_MPM > 0
int	mcrcount = 0;
#endif	NMACH_MPM > 0
ka7xx_crd()
{
	register struct mcr *mcr;
	register int m;
#if	NMACH_MPM > 0
	mcrcount++;
#endif	NMACH_MPM > 0
	for (m = 0; m < nmcr; m++) {
	    mcr = mcraddr[m];
	    switch (mcrtype[m]) {
#ifdef	VAX780
#if	NMACH_MPM > 0
		case M780MA:
		    if (!m)
			printf("memerr: #%d: SBIERR = %x\n",
				mcrcount,
				mfpr(SBIER));

		    if (M780MA_ERR(mcr)) {
			printf("mcr%d: %s error",
				m,
				(mfpr(SBIER)&(1<<14)) ? "soft ecc"
						      : "parity");
			printf(" addr %x syn %x\n",
				M780MA_ADDR(mcr),
				M780MA_SYN(mcr));
			if (mfpr(SBIER) & (1 << 13)) {
			    printf("double bit memory error\n");
			    asm("halt");
			}
		    }
		    break;
#endif	NMACH_MPM > 0
		case M780C:
		    if (M780C_ERR(mcr)) {
			printf("mcr%d: soft ecc addr %x syn %x\n",
				m,
				M780C_ADDR(mcr),
				M780C_SYN(mcr));
			M780C_INH(mcr);
		    }
		    break;

		case M780EL:
		    if (M780EL_ERR(mcr)) {
			printf("mcr%d: soft ecc addr %x syn %x\n",
				m,
				M780EL_ADDR(mcr),
				M780EL_SYN(mcr));
			M780EL_INH(mcr);
		    }
		    break;

		case M780EU:
		    if (M780EU_ERR(mcr)) {
			printf("mcr%d: soft ecc addr %x syn %x\n",
				m,
				M780EU_ADDR(mcr),
				M780EU_SYN(mcr));
			M780EU_INH(mcr);
		    }
		    break;
#endif	VAX780
#ifdef	VAX750
		case M750:
		    if (M750_ERR(mcr)) {
			struct mcr	amcr;
			amcr.mc_reg[0] = mcr->mc_reg[0];
			printf("mcr%d: %s",
				m,
				(amcr.mc_reg[0] & M750_UNCORR)
				    ? "hard error"
				    : "soft ecc");
			printf(" addr %x syn %x\n",
				M750_ADDR(&amcr),
				M750_SYN(&amcr));
			M750_INH(mcr);
		    }
		    break;
#endif	VAX750
#ifdef	VAX730
		case M730:
		    {
			struct mcr	amcr;
			/*
			 * Must be careful on the 730 not to use invalid
			 * instructions in I/O space, so make a copy:
			 */
			amcr.mc_reg[0] = mcr->mc_reg[0];
			amcr.mc_reg[1] = mcr->mc_reg[1];
			if (M730_ERR(&amcr)) {
			    printf("mcr%d: %s",
				    m,
				    (amcr.mc_reg[1] & M730_UNCORR)
					? "hard error"
					: "soft ecc");
			    printf(" addr %x syn %x\n",
				    M730_ADDR(&amcr),
				    M730_SYN(&amcr));
			    M730_INH(mcr);
			}
		    }
		    break;
#endif	VAX750
	    }
	}
}

#if defined(VAX780) || defined(VAX750)
char *mc780[] = {
	"cp read",	"ctrl str par",	"cp tbuf par",	"cp cache par",
	"cp rdtimo", 	"cp rds",	"ucode lost",	0,
	0,		0,		"ib tbuf par",	0,
	"ib rds",	"ib rd timo",	0,		"ib cache par"
};
#define MC750_TBERR	2		/* type code of cp tbuf par */
#define	MC750_TBPAR	4		/* tbuf par bit in mcesr */
#endif

#if VAX730
#define	NMC730	12
char *mc730[] = {
	"tb par",	"bad retry",	"bad intr id",	"cant write ptem",
	"unkn mcr err",	"iib rd err",	"nxm ref",	"cp rds",
	"unalgn ioref",	"nonlw ioref",	"bad ioaddr",	"unalgn ubaddr",
};
#endif
struct mc780frame {
	int	mc8_bcnt;		/* byte count == 0x28 */
	int	mc8_summary;		/* summary parameter (as above) */
	int	mc8_cpues;		/* cpu error status */
	int	mc8_upc;		/* micro pc */
	int	mc8_vaviba;		/* va/viba register */
	int	mc8_dreg;		/* d register */
	int	mc8_tber0;		/* tbuf error reg 0 */
	int	mc8_tber1;		/* tbuf error reg 1 */
	int	mc8_timo;		/* timeout address divided by 4 */
	int	mc8_parity;		/* parity */
	int	mc8_sbier;		/* sbi error register */
	int	mc8_pc;			/* trapped pc */
	int	mc8_psl;		/* trapped psl */
};
struct mc750frame {
	int	mc5_bcnt;		/* byte count == 0x28 */
	int	mc5_summary;		/* summary parameter (as above) */
	int	mc5_va;			/* virtual address register */
	int	mc5_errpc;		/* error pc */
	int	mc5_mdr;
	int	mc5_svmode;		/* saved mode register */
	int	mc5_rdtimo;		/* read lock timeout */
	int	mc5_tbgpar;		/* tb group parity error register */
	int	mc5_cacherr;		/* cache error register */
	int	mc5_buserr;		/* bus error register */
	int	mc5_mcesr;		/* machine check status register */
	int	mc5_pc;			/* trapped pc */
	int	mc5_psl;		/* trapped psl */
};
struct mc730frame {
	int	mc3_bcnt;		/* byte count == 0xc */
	int	mc3_summary;		/* summary parameter */
	int	mc3_parm[2];		/* parameter 1 and 2 */
	int	mc3_pc;			/* trapped pc */
	int	mc3_psl;		/* trapped psl */
};

#ifdef	VAX780
int ka780_mchk(cmcf)
	char *cmcf;
{
	register struct mc780frame *mcf = (struct mc780frame *)cmcf;
	register int sbifs;
	register int type = mcf->mc8_summary;

	printf("%s%s\n", mc780[type&0xf],
	    (type&0xf0) ? " abort" : " fault"); 
	printf("\tcpues %x upc %x va/viba %x dreg %x tber %x %x\n",
	   mcf->mc8_cpues, mcf->mc8_upc, mcf->mc8_vaviba,
	   mcf->mc8_dreg, mcf->mc8_tber0, mcf->mc8_tber1);
	sbifs = mfpr(SBIFS);
	printf("\ttimo %x parity %x sbier %x pc %x psl %x sbifs %x\n",
	   mcf->mc8_timo*4, mcf->mc8_parity, mcf->mc8_sbier,
	   mcf->mc8_pc, mcf->mc8_psl, sbifs);
	/* THE FUNNY BITS IN THE FOLLOWING ARE FROM THE ``BLACK */
	/* BOOK'' AND SHOULD BE PUT IN AN ``sbi.h'' */
	mtpr(SBIFS, sbifs &~ 0x2000000);
	mtpr(SBIER, mfpr(SBIER) | 0x70c0);

	return (0);
}
#endif	VAX780

#ifdef	VAX750
int ka750_mchk(cmcf)
	char *cmcf;
{
	register struct mc750frame *mcf = (struct mc750frame *)cmcf;
	int mcsr = mfpr(MCSR);
	register int type = mcf->mc5_summary;

	printf("%s%s\n", mc780[type&0xf],
	    (type&0xf0) ? " abort" : " fault"); 
	mtpr(TBIA, 0);
	mtpr(MCESR, 0xf);
	printf("\tva %x errpc %x mdr %x smr %x rdtimo %x tbgpar %x cacherr %x\n",
	    mcf->mc5_va, mcf->mc5_errpc, mcf->mc5_mdr, mcf->mc5_svmode,
	    mcf->mc5_rdtimo, mcf->mc5_tbgpar, mcf->mc5_cacherr);
	printf("\tbuserr %x mcesr %x pc %x psl %x mcsr %x\n",
	    mcf->mc5_buserr, mcf->mc5_mcesr, mcf->mc5_pc, mcf->mc5_psl,
	    mcsr);
	if (type == MC750_TBERR && (mcf->mc5_mcesr&0xe) == MC750_TBPAR){
		printf("tbuf par: flushing and returning\n");
		return(1);
	}
	return (0);
}
#endif	VAX750

#ifdef	VAX730
int ka730_mchk(cmcf)
	char *cmcf;
{
	register struct mc730frame *mcf = (struct mc730frame *)cmcf;
	register int type = mcf->mc3_summary;

	if (type < NMC730)
		printf("%s", mc730[type]);
	printf("\n");
	printf("params %x,%x pc %x psl %x mcesr %x\n",
	    mcf->mc3_parm[0], mcf->mc3_parm[1],
	    mcf->mc3_pc, mcf->mc3_psl, mfpr(MCESR));
	mtpr(MCESR, 0xf);

	return (0);
}
#endif	VAX730

ka7xx_halt(reboot)
	boolean_t	reboot;
{
	if (reboot) {
	    tocons(TXDB_BOOT);
	    for (;;)
		asm("halt");
	}
	else {
	    printf("halting (in tight loop); hit\n\t^P\n\tHALT\n\n");
	    mtpr(IPL, 0x1f);
	    for (;;)
		;
	}
}

#endif defined(VAX780) || defined(VAX750) || defined(VAX730)
