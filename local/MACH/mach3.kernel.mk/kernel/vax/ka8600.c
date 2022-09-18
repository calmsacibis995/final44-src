/*
 * HISTORY
 * $Log:	ka8600.c,v $
 * Revision 2.3  91/06/19  12:01:10  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:49:58  rvb]
 * 
 * Revision 2.2  91/05/08  13:18:41  dbg
 * 	Fix inline assembler code for GNU C.
 * 	[91/04/25            dbg]
 * 
 */

/*
 * Vax 8600 model-dependent code - from Berkeley.
 */

#include <platforms.h>

#ifdef VAX8600

#include <mach/boolean.h>
#include <mach/machine.h>
#include <kern/time_out.h>

#include <vm/vm_kern.h>
#include <mach/vm_param.h>

#include <vax/cpu_data.h>
#include <vax/cons.h>
#include <vax/mem.h>
#include <vax/mtpr.h>
#include <vax/ioa.h>
#include <vax/nexus.h>

#include <vaxuba/ubareg.h>

int	ka8600_init(), ka8600_config(), ka8600_reboot_ok(),
	ka8600_crd(), ka8600_mchk(), ka8600_clear_mchk(), ka8600_halt();

struct model_dep ka8600_model = {
	(int (*)()) 0,	/* no setup */
	ka8600_init,
	ka8600_config,
	(int (*)()) 0,	/* no slave_config */
	ka8600_reboot_ok,
	ka8600_crd,
	ka8600_mchk,
	ka8600_clear_mchk,
	ka8600_halt,
	(int (*)()) 0,	/* no interrupt */
	6
};

caddr_t umaddr8600a[4] = {
	(caddr_t) UMEMA8600(0),	(caddr_t) UMEMA8600(1),
	(caddr_t) UMEMA8600(2),	(caddr_t) UMEMA8600(3),
};
caddr_t umaddr8600b[4] = {
	(caddr_t) UMEMB8600(0),	(caddr_t) UMEMB8600(1),
	(caddr_t) UMEMB8600(2),	(caddr_t) UMEMB8600(3),
};

struct nexusconnect sbi8600[] = {
	{ NNEX8600, NEXA8600, DW780, NBDP8600, umaddr8600a, 0 },
	{ NNEX8600, NEXB8600, DW780, NBDP8600, umaddr8600b, 0 }
};
struct ioa_connect io8600[] = {
	{ IOA8600(0), IOAMAPSIZ, &sbi8600[0] },
	{ IOA8600(1), IOAMAPSIZ, &sbi8600[1] },
};

int	nsbi = 0;

int ka8600_init()
{
	union cpusid {
	    int		sid;
	    struct sid8600 {
		unsigned int	serial_number:12,
				plant:4,
				eco_level:8,
				cpu_type:8;
	    } sid8600;
	} cpusid;

	cpusid.sid = mfpr(SID);
	printf("VAX 8600, serial#%d(%d), hardware ECO level=%d(%d)\n",
	       cpusid.sid8600.serial_number,
	       cpusid.sid8600.plant,
	       (cpusid.sid8600.eco_level>>4)&0xf,
	       cpusid.sid8600.eco_level&0xf);

	/*
	 * Enable cache and FPA.
	 */
	mtpr(CSWP, 3);
	if ((mfpr(ACCS) & 0xff) != 0) {
	    printf("Enabling FPA\n");
	    mtpr(ACCS, 0x8000);
	}

	ka8600_memenable();

	return (CPU_SUBTYPE_VAX8600);

}

int ka8600_config()
{
	probe_Abus(0, &io8600[0]);
	probe_Abus(1, &io8600[1]);
}

int ka8600_reboot_ok()
{
	/*
	 * Clear restart inhibit flags.
	 */
	tocons(TXDB_CWSI);
	tocons(TXDB_CCSI);
}

int	ka86_memintvl = MEMINTVL;

ka8600_memenable()
{
	M8600_ENA;
	if (ka86_memintvl > 0)
		timeout(ka8600_memenable, (caddr_t)0, ka86_memintvl*hz);
}

ka8600_crd()
{
#ifdef	__GNUC__
#define	read_ebox_reg(regno) \
	({  int _result__; \
	    asm("mtpr %1, $0x4e; mfpr $0x4f, %0" \
		: "=g" (_result__) \
		: "g" (regno) ); \
	    _result__; })
#else
	register int	reg11;	/* known to be r11 below */
#endif
	int mdecc, mear, mstat1, mstat2, array;

	/*
	 * Scratchpad registers in the Ebox must be read by
	 * storing their ID number in ESPA and then immediately
	 * reading ESPD's contents with no other intervening
	 * machine instructions!
	 *
	 * The asm's below have a number of constants which
	 * are defined correctly in mem.h and mtpr.h.
	 */
#ifdef lint
	reg11 = 0;
#endif

#ifdef	__GNUC__
	mdecc = read_ebox_reg(0x27);
#else
	asm("mtpr $0x27,$0x4e; mfpr $0x4f,r11");
	mdecc = reg11;	/* must acknowledge interrupt? */
#endif
	if (M8600_MEMERR(mdecc)) {
#ifdef	__GNUC__
		mear = read_ebox_reg(0x2a);
		mstat1 = read_ebox_reg(0x25);
		mstat2 = read_ebox_reg(0x25);
#else
		asm("mtpr $0x2a,$0x4e; mfpr $0x4f,r11");
		mear = reg11;
		asm("mtpr $0x25,$0x4e; mfpr $0x4f,r11");
		mstat1 = reg11;
		asm("mtpr $0x26,$0x4e; mfpr $0x4f,r11");
		mstat2 = reg11;
#endif
		array = M8600_ARRAY(mear);

		printf("mcr0: ecc error, addr %x (array %d) syn %x\n",
			M8600_ADDR(mear), array, M8600_SYN(mdecc));
		printf("\tMSTAT1 = %b\n\tMSTAT2 = %b\n",
			    mstat1, M8600_MSTAT1_BITS,
			    mstat2, M8600_MSTAT2_BITS);
		M8600_INH;
	}
}


#define NMC8600	7
char *mc8600[] = {
	"unkn type",	"fbox error",	"ebox error",	"ibox error",
	"mbox error",	"tbuf error",	"mbox 1D error"
};
/* codes for above */
#define	MC_FBOX		1
#define	MC_EBOX		2
#define	MC_IBOX		3
#define	MC_MBOX		4
#define	MC_TBUF		5
#define	MC_MBOX1D	6

/* error bits */
#define	MBOX_FE		0x8000		/* Mbox fatal error */
#define	FBOX_SERV	0x10000000	/* Fbox service error */
#define	IBOX_ERR	0x2000		/* Ibox error */
#define	EBOX_ERR	0x1e00		/* Ebox error */
#define	MBOX_1D		0x81d0000	/* Mbox 1D error */
#define EDP_PE		0x200


struct mc8600frame {
	int	mc6_bcnt;		/* byte count == 0x58 */
	int	mc6_ehmsts;
	int	mc6_evmqsav;
	int	mc6_ebcs;
	int	mc6_edpsr;
	int	mc6_cslint;
	int	mc6_ibesr;
	int	mc6_ebxwd1;
	int	mc6_ebxwd2;
	int	mc6_ivasav;
	int	mc6_vibasav;
	int	mc6_esasav;
	int	mc6_isasav;
	int	mc6_cpc;
	int	mc6_mstat1;
	int	mc6_mstat2;
	int	mc6_mdecc;
	int	mc6_merg;
	int	mc6_cshctl;
	int	mc6_mear;
	int	mc6_medr;
	int	mc6_accs;
	int	mc6_cses;
	int	mc6_pc;			/* trapped pc */
	int	mc6_psl;		/* trapped psl */
};

ka8600_mchk(cmcf)
	char *cmcf;
{
	register struct mc8600frame *mcf = (struct mc8600frame *)cmcf;
	register int	type;

	if (mcf->mc6_ebcs & MBOX_FE)
		mcf->mc6_ehmsts |= MC_MBOX;
	else if (mcf->mc6_ehmsts & FBOX_SERV)
		mcf->mc6_ehmsts |= MC_FBOX;
	else if (mcf->mc6_ebcs & EBOX_ERR) {
		if (mcf->mc6_ebcs & EDP_PE)
			mcf->mc6_ehmsts |= MC_MBOX;
		else
			mcf->mc6_ehmsts |= MC_EBOX;
	} else if (mcf->mc6_ehmsts & IBOX_ERR)
		mcf->mc6_ehmsts |= MC_IBOX;
	else if (mcf->mc6_mstat1 & M8600_TB_ERR)
		mcf->mc6_ehmsts |= MC_TBUF;
	else if ((mcf->mc6_cslint & MBOX_1D) == MBOX_1D)
		mcf->mc6_ehmsts |= MC_MBOX1D;

	type = mcf->mc6_ehmsts & 0x7;
	if (type < NMC8600)
		printf("machine check %x: %s", type, mc8600[type]);
	printf("\n");
	printf("\tehm.sts %x evmqsav %x ebcs %x edpsr %x cslint %x\n",
	    mcf->mc6_ehmsts, mcf->mc6_evmqsav, mcf->mc6_ebcs,
	    mcf->mc6_edpsr, mcf->mc6_cslint);
	printf("\tibesr %x ebxwd %x %x ivasav %x vibasav %x\n",
	    mcf->mc6_ibesr, mcf->mc6_ebxwd1, mcf->mc6_ebxwd2,
	    mcf->mc6_ivasav, mcf->mc6_vibasav);
	printf("\tesasav %x isasav %x cpc %x mstat %x %x mdecc %x\n",
	    mcf->mc6_esasav, mcf->mc6_isasav, mcf->mc6_cpc,
	    mcf->mc6_mstat1, mcf->mc6_mstat2, mcf->mc6_mdecc);
	printf("\tmerg %x cshctl %x mear %x medr %x accs %x cses %x\n",
	    mcf->mc6_merg, mcf->mc6_cshctl, mcf->mc6_mear,
	    mcf->mc6_medr, mcf->mc6_accs, mcf->mc6_cses);
	printf("\tpc %x psl %x\n", mcf->mc6_pc, mcf->mc6_psl);
	mtpr(EHSR, 0);

	return (0);
}

/*ARGSUSED*/
ka8600_clear_mchk(nioa)
	int	nioa;
{
	mtpr(EHSR, 0);
}

ka8600_halt(reboot)
	boolean_t	reboot;
{
	if (reboot) {
	    tocons(TXDB_BOOT);
	    for (;;)
		asm("halt");
	}
	else {
	    printf("halting (in tight loop); hit\n\t^p\n\tHALT\n\n");
	    mtpr(IPL, 0x1f);
	    for (;;)
		;
	}
}

#endif	VAX8600
