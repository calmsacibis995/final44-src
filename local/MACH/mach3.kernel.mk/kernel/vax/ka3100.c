/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ka3100.c,v $
 * Revision 2.6  93/05/17  10:24:52  rvb
 * 	Type casts, etc to quiet gcc 2.3.3 warnings
 * 
 * Revision 2.5  93/03/11  13:47:32  danner
 * 	u_long -> u_int
 * 	[93/03/09            danner]
 * 
 * Revision 2.4  91/08/24  12:29:54  af
 * 	pcc is gone, reflected other changes in calling seq or
 * 	function names.
 * 	[91/08/02  04:31:48  af]
 * 
 * Revision 2.3  91/06/25  20:56:59  rpd
 * 	Tweaks to make gcc happy.
 * 	[91/06/25            rpd]
 * 
 * Revision 2.2  91/06/20  11:38:53  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:57:52  rvb]
 * 
 * 	Support for VaxStation 3100: new processor cvax + different
 * 	memory and bus.
 * 	[91/06/04            rvb]
 * 
 *
 * Revision 2.1      91/06/06  14:29:16  rvb
 * 	Created.
 * 	[91/05/24            rvb]
 * 
 *
 */
/*
 *	KA3100 model-dependent routines.
 */

#include <platforms.h>
#include <bm.h>

#if	VAX3100

#include <sys/types.h>
#include <kern/cpu_number.h>
#include <mach/machine.h>

#include <vax/vm_defs.h>
#include <vax/cpu_data.h>
#include <vax/io_map.h>
#include <vax/ka3100.h>
#include <vax/mtpr.h>
#include <vax/cpmbx.h>
#include <vax/scb.h>
#include <vax/watch_chip.h>
#undef set_cpmbx
#define	set_cpmbx(code)	(*(int*)cpmbx=((((*(int*)cpmbx)>>2)&CPMBX_LANG)|(code))<<2)
#include <chips/vs42x_rb.h>

extern int	(*ka42_glu[])();
extern int	(*ka42_int[])();
extern int	  ka42_unt[];

u_int			*cacr;			/* 2nd level cache control */
u_int			*c2data;		/* 2nd level cache data storage. */
u_short			*cfgtst;
struct rom		*rom;
struct stat		*stat;
struct watch_chip_3100	*ka42_watch_chip;
u_char			*etheraddr;
struct ser		*ser_xxx;
u_short			*lance;
u_char			*cur_xxx;
u_char			*bm_mem;
u_char			*sci;
u_char			*scibuf;

int			ignore_tube = NBM == 0;

int	ka42_setup(), ka42_init(), ka42_config(),
	ka42_reboot_ok(), ka42_crd(), ka42_mchk(),
	ka42_clear_mchk(), ka42_halt();

static void verify_rom_intr();

struct model_dep ka42_model = {
	ka42_setup,
	ka42_init,
	ka42_config,
	0,				/* no slave_config */
	ka42_reboot_ok,
	ka42_crd,
	ka42_mchk,
	ka42_clear_mchk,
	ka42_halt,
	0,				/* no interrupt */
	6
};

/*
 * Map required memory for the 42, and find the console.
 * Called running virtual, but with VM not initialized.
 */
ka42_setup()
{
	c2data = (u_int *)io_map((vm_offset_t)C2DATA, C2DATA_SIZE);
	cacr = (u_int *)io_map((vm_offset_t)CACR, sizeof (u_int));
	cfgtst = (u_short *)io_map(CFGTST, sizeof (u_short));
	rom = (struct rom *)io_map((vm_offset_t)ROM3100,
					sizeof(struct rom));
	stat = (struct stat *)io_map((vm_offset_t)STAT, sizeof (struct stat));
	etheraddr = (u_char *)io_map((vm_offset_t)ETHERADDR, ETHER_SIZE);
	ser_xxx = (struct ser *)io_map((vm_offset_t)SER_xxx, SER_SIZE);
	ka42_watch_chip = (struct watch_chip_3100 *)io_map((vm_offset_t)WAT_xxx, WAT_SIZE);

/* WRONG!! */
	watch_chip = (struct watch_chip *)ka42_watch_chip;
/* WRONG!! */

	lance = (u_short *)io_map((vm_offset_t)LANCE, LANCE_SIZE);
	cur_xxx = (u_char *)io_map((vm_offset_t)CUR_xxx, CUR_SIZE);
	bm_mem = (u_char *) io_map((vm_offset_t)BM_MEM, BM_MEM_SIZE);

	sci = (u_char *)io_map((vm_offset_t)VAX3100_STC_BASE, SCI_REG_SIZE);
	scibuf = (u_char *)io_map((vm_offset_t)VAX3100_STC_RAM, SCI_RAM_SIZE);

	/*
	 * Point to the console mailbox.
	 */
	cpmbx = (char *) ka42_watch_chip->ram;

	stat->par_ctl = PAR_CTL_PEN;
	ka42_cache_on();

	if (!ignore_tube) {
		extern char *screen_data;
#if	0
		/*
		   this should work; but the system panic's
		   when you shutdown
		 */
		int vm_offset_t phys;
		pmap_next_page(&phys);
		screen_data = (char *) io_map((vm_offset_t)phys, PAGE_SIZE);
#else	0
		/*
		   this means that the screen clear and friends should
		   consider the screen only BM_MEM_SIZE - PAGE_SIZE
		 */
		screen_data = (char *) (bm_mem + BM_MEM_SIZE - PAGE_SIZE);
#endif	0
	}

	set_dz_address(0, ser_xxx, 0);
	{
		extern int ser_getc(), ser_putc(), ser_maygetc(), ser_pollc();
		extern int (*vgetc)(), (*vputc)(), (*vmaygetc)(), (*vpollc)();
		vgetc = ser_getc;
		vputc = ser_putc;
		vpollc = ser_pollc;
		vmaygetc = ser_maygetc;
		/*
		 * Change the console device slot to point to the QVSS.
		 */
		dev_change_indirect("console", "dz_", 0);
	} 

	if ((*cfgtst & ALCON) && ((*cfgtst & MULTU_) == 0) && !ignore_tube) {
		cons_find(1);

	} else if (*cfgtst & ALCON) {
		ignore_tube = 1;

		cons_find(0);

	} else if ((*cfgtst & MULTU_) == 0) {
		extern int rcline;

		rcline = 0;
		cons_find(1);
	}
}

static int csp[] = {0, 60, 90, 100};

ka42_init()
{
	int cfg = *cfgtst;
	extern int	D_float;

	printf("box : VaxStation 3100 %s rev %x.\n",
		rom->arch_ident == 2 ? "WorkStation" : rom->arch_ident == 1 ? "TimeShare" : "??",
		rom->revision);

	printf("cache : 1K first level cache");
	if (cfg & CACHPR)
		printf(" and 32K second level cache");
	printf(".\n");

	printf("memory: %d megabytes.\n", ((cfg&MTYPE)+1)*4);

	printf("cpu: cvax %d nanosec (rev %x).\n",
		csp[(*cacr&CACR_CSP)>>6],
		mfpr(SID)&0xff);
	printf("fpa: %s.\n", D_float ? "present" : "none");


	if ((cfg & MULTU_) == 0 || ((cfg & CURTEST) == 0)) {
		printf("pm0: ");
		if ((cfg & MULTU_) == 0)
			printf("B&W video ");
		if ((cfg & CURTEST) == 0)
			printf("with cursor");
		printf(".\n");
	}

	if (cfg & ALCON)
		printf("Alternate console enabled.\n");

	if (cfg & VIDOPT)
		printf("Option Board.\n");

#ifdef	DEBUG
	pr_rom_intr();
	pr_cacr(cacr);
#endif	DEBUG

	verify_rom_intr();
	verify_cacr(cacr);

	return (CPU_SUBTYPE_UVAXIII);
}

ka42_stray_int(i)
{
	printf("ka42 stray interrupt %d.  masking it off.\n", i);
	stat->int_msk &= ~(1 << i);
}

ka42_ie(level, fn, unit)
int (*fn)();
{
	if ((int)fn == 0)
		fn = ka42_stray_int;
	ka42_unt[level] = unit;
	ka42_int[level] = fn;
	if (fn != ka42_stray_int)
		stat->int_msk |= (1 << level);
	else
		stat->int_msk &= ~(1 << level);	
}

/* lance buffer */
char ka42_ln_ram[(64*1024)+8];	/* need it longword aligned */

ka42_config()
{
	extern int dz_intr();
	extern int se_intr();

	stat->int_msk = 0;		/* allow no interrupts */
	stat->int_clr = 0xff;		/* clear all outstanding interrupts */
	
	/*dz*/
	if (configure_bus_device( "dz", 0, 0, 2, "slot")) {
		ka42_ie(INT_SR, dz_intr, 0);
		ka42_ie(INT_ST, dz_intr, 0);
	} /* else panic ? */

/*	configure_bus_device( "pm", 0, 0, 0, "slot");*/
	if (!ignore_tube) {
		/* vertical retrace */
		if ((*cfgtst & MULTU_) == 0)	/* installed monochrome */
			stat->vdc_sel = 0;
		else
			stat->vdc_sel = 1;	/* Retrace signal from video option */
		ka42_vretrace(0, 1);
	}

	/* lance */
	setse_switch(0, (unsigned int)lance, (unsigned int)ka42_ln_ram,
			(unsigned int)ka42_ln_ram, (unsigned int)etheraddr);
	if (configure_bus_device( "se", 0, 0, 3, "slot"))
		ka42_ie(INT_NI, se_intr, 0);

	/* scsi */
	{
		int cfg = *cfgtst;
		int sci_intr();

		printf("I/O controller: ");
		switch (cfg & STCOPT) {
		case VS42X_RB:
			panic("VS42X_RB, unsupported"); break;
		case VS42X_SCSC:
			printf("SCSI/SCSI\n"); break;
		case VS42X_RD:
			panic("VS42X_RD, unsupported"); break;
		case VS42X_NONE:
			panic("VS42X_NONE, unsupported"); break;
		}
		ka42_ie(INT_SC, sci_intr, 0);
		ka42_ie(INT_DC, sci_intr, 1);

		sci_config(sci,scibuf);

	}
}

ka42_vretrace(unit, on)
{
	extern int pm_intr();

	if (on)
		ka42_ie(INT_VF, pm_intr, 0);
	else
		ka42_ie(INT_VF, ka42_stray_int, INT_VF);
}

struct mc42frame {
	int	mc65_bcnt;		/* byte count == 0xe */
	int	mc65_mcc;		/* machine check code */
	int	mc65_mrvaddr;		/* most recent virtual addr */
	int	mc65_istate1;		/* internal state */
	int	mc65_istate2;		/* internal state */
	int	mc65_pc;		/* trapped pc */
	int	mc65_psl;		/* trapped psl */
};

ka42_crd()
{

	stat->par_ctl = PAR_CTL_PEN;

	if (mfpr(MSER) & MSER_ERR)
		printf("MSER = %x\n", mfpr(MSER));

	if (*cacr & CACR_ERR)
		printf("CACR = %x\n", *cacr);

	ka42_cache_on();
}

ka42_cache_on()
{
	register int i;

	mtpr(MSER, mfpr(MSER) & MSER_ERR);	/* c1&cdal cache and parity */
	/* enable&flush level 1 cache */
	mtpr(CADR, 0xf0);

	*cacr = CACR_ERR;			/* cancel error and turn off */
	/* flush level 2 cache */
	for (i = 0; i < C2DATA_SIZE/sizeof(long); i++)
	    c2data[i] = 0;
	/* enable level 2 cache */
	*cacr = CACR_CEN;
}

int ka42_mchk(cmcf)
	char *	cmcf;
{
	register struct mc42frame *mcf = (struct mc42frame *)cmcf;

	printf("\n");
	printf("code %x vap %x istate1 %x istate2 %x pc %x psl %x\n",
	    mcf->mc65_mcc, mcf->mc65_mrvaddr,
	    mcf->mc65_istate1, mcf->mc65_istate2,
	    mcf->mc65_pc, mcf->mc65_psl);
	ka42_crd();

	return (0);
}

/*ARGSUSED*/
int ka42_clear_mchk(nioa)
	int	nioa;
{
}


ka42_reboot_ok()
{
	set_cpmbx(0);	/* ? */
}

ka42_halt(reboot)
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

delay(x)
{
extern int cpuspeed;

	if (cpuspeed == 0) {
		asm("movl $0x43211234,r0; halt");
		cpuspeed = 3;
	}
	DELAY(x);
}
/* ---- */

#define PR(str,ptr) printf("%s:\t/**/ptr/**/\t(@%x) = %x\n", str, &ptr, ptr)
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

static void verify_rom_intr()
{
register int i;
register int (*(*ip))() = scb.scb_ipl14;

		/* out with the bad vectors */
	for (i = 0; i < 4 * 16 + 128; i++)
		*ip++ = scbentry(0, SCB_HALT);

	VE("Interrupt 0", rom->intA[0], 0xffff, 0x03fc);
	VE("Interrupt 1", rom->intA[1], 0xffff, 0x03f8);
	VE("Interrupt 2", rom->intA[2], 0xffff, 0x0248);
	VE("Interrupt 3", rom->intA[3], 0xffff, 0x0244);
	VE("Interrupt 4", rom->intA[4], 0xffff, 0x0254);
	VE("Interrupt 5", rom->intA[5], 0xffff, 0x0250);
	VE("Interrupt 6", rom->intA[6], 0xffff, 0x02c4);
	VE("Interrupt 7", rom->intA[7], 0xffff, 0x02c0);

		/* in with the good vectors */
	scb.scb_ubaint[(rom->intA[0]-0x200)>>2] = scbentry(ka42_glu[0], SCB_ISTACK);
	scb.scb_ubaint[(rom->intA[1]-0x200)>>2] = scbentry(ka42_glu[1], SCB_ISTACK);
	scb.scb_ubaint[(rom->intA[2]-0x200)>>2] = scbentry(ka42_glu[2], SCB_ISTACK);
	scb.scb_ubaint[(rom->intA[3]-0x200)>>2] = scbentry(ka42_glu[3], SCB_ISTACK);
	scb.scb_ubaint[(rom->intA[4]-0x200)>>2] = scbentry(ka42_glu[4], SCB_ISTACK);
	scb.scb_ubaint[(rom->intA[5]-0x200)>>2] = scbentry(ka42_glu[5], SCB_ISTACK);
	scb.scb_ubaint[(rom->intA[6]-0x200)>>2] = scbentry(ka42_glu[6], SCB_ISTACK);
	scb.scb_ubaint[(rom->intA[7]-0x200)>>2] = scbentry(ka42_glu[7], SCB_ISTACK);
}

static pr_rom_intr()
{
	PR("Interrupt 0", rom->intA[0]);
	PR("Interrupt 1", rom->intA[1]);
	PR("Interrupt 2", rom->intA[2]);
	PR("Interrupt 3", rom->intA[3]);
	PR("Interrupt 4", rom->intA[4]);
	PR("Interrupt 5", rom->intA[5]);
	PR("Interrupt 6", rom->intA[6]);
	PR("Interrupt 7", rom->intA[7]);
}


verify_cacr(p)
register u_int *p;
{
	VE("Cache Control Register", *p, 0x3f, 0x14);
}

pr_cacr(p)
register u_int *p;
{
	PR("Cache Control Register", *p);
}

ka3100_scsi_id(ctlr)
{
	struct ka3100_nvram 	*nv = (struct ka3100_nvram *) ka42_watch_chip->ram;
	register int		i;

	i = nv->cpu_scsi_id >> 2;
	return (ctlr ? ((i >> 3) & 0x7) : (i & 0x7));
}

#if 1	/*pure hacking*/
#include <chips/busses.h>

extern struct bus_driver
/*	asc_driver, sii_driver,*/	sci_driver,
	se_driver, dz_driver,
	pm_driver, ga_driver, gq_driver/*, cfb_driver*/;
extern int
/*	asc_intr(), sii_intr(),*/	sci_intr(),
	se_intr(), dz_intr(),
	pm_intr(), ga_intr(), gq_intr()/*, cfb_intr()*/;

struct bus_ctlr bus_master_init[] = {
/*driver,	name,	unit, intr, address+am, phys, adpt, alive, flags, */
{ &sci_driver,	"sci",	0,    sci_intr,  0x0,0,	0,      0,    0,     0, },
{ &sci_driver,	"sci",	1,    sci_intr,  0x0,0,	0,      1,    0,     0, },
	0
};

struct bus_device bus_device_init[] = {
/* driver,      name, unit,intr,addr+am,phys, adaptor,alive,ctlr,slave,flags,*/
{ &sci_driver,	"rz",   0,  0,  0x0,0,	0,    '?',     0,   0,   0,    0, },
{ &sci_driver,	"rz",   1,  0,  0x0,0,	0,    '?',     0,   0,   1,    0, },
{ &sci_driver,	"rz",   2,  0,  0x0,0,	0,    '?',     0,   0,   2,    0, },
{ &sci_driver,	"rz",   3,  0,  0x0,0,	0,    '?',     0,   0,   3,    0, },
{ &sci_driver,	"rz",   4,  0,  0x0,0,	0,    '?',     0,   0,   4,    0, },
{ &sci_driver,	"rz",   5,  0,  0x0,0,	0,    '?',     0,   0,   5,    0, },
{ &sci_driver,	"rz",   6,  0,  0x0,0,	0,    '?',     0,   0,   6,    0, },
{ &sci_driver,	"rz",   7,  0,  0x0,0,	0,    '?',     0,   0,   7,    0, },
{ &sci_driver,	"rz",   8,  0,  0x0,0,	0,    '?',     0,   1,   0,    0, },
{ &sci_driver,	"rz",   9,  0,  0x0,0,	0,    '?',     0,   1,   1,    0, },
{ &sci_driver,	"rz",  10,  0,  0x0,0,	0,    '?',     0,   1,   2,    0, },
{ &sci_driver,	"rz",  11,  0,  0x0,0,	0,    '?',     0,   1,   3,    0, },
{ &sci_driver,	"rz",  12,  0,  0x0,0,	0,    '?',     0,   1,   4,    0, },
{ &sci_driver,	"rz",  13,  0,  0x0,0,	0,    '?',     0,   1,   5,    0, },
{ &sci_driver,	"rz",  14,  0,  0x0,0,	0,    '?',     0,   1,   6,    0, },
{ &sci_driver,	"rz",  15,  0,  0x0,0,	0,    '?',     0,   1,   7,    0, },

{ &sci_driver,	"tz",   0,  0,  0x0,0,	0,    '?',     0,   0,   0,    0, },
{ &sci_driver,	"tz",   1,  0,  0x0,0,	0,    '?',     0,   0,   1,    0, },
{ &sci_driver,	"tz",   2,  0,  0x0,0,	0,    '?',     0,   0,   2,    0, },
{ &sci_driver,	"tz",   3,  0,  0x0,0,	0,    '?',     0,   0,   3,    0, },
{ &sci_driver,	"tz",   4,  0,  0x0,0,	0,    '?',     0,   0,   4,    0, },
{ &sci_driver,	"tz",   5,  0,  0x0,0,	0,    '?',     0,   0,   5,    0, },
{ &sci_driver,	"tz",   6,  0,  0x0,0,	0,    '?',     0,   0,   6,    0, },
{ &sci_driver,	"tz",   7,  0,  0x0,0,	0,    '?',     0,   0,   7,    0, },
{ &sci_driver,	"tz",   8,  0,  0x0,0,	0,    '?',     0,   1,   0,    0, },
{ &sci_driver,	"tz",   9,  0,  0x0,0,	0,    '?',     0,   1,   1,    0, },
{ &sci_driver,	"tz",  10,  0,  0x0,0,	0,    '?',     0,   1,   2,    0, },
{ &sci_driver,	"tz",  11,  0,  0x0,0,	0,    '?',     0,   1,   3,    0, },
{ &sci_driver,	"tz",  12,  0,  0x0,0,	0,    '?',     0,   1,   4,    0, },
{ &sci_driver,	"tz",  13,  0,  0x0,0,	0,    '?',     0,   1,   5,    0, },
{ &sci_driver,	"tz",  14,  0,  0x0,0,	0,    '?',     0,   1,   6,    0, },
{ &sci_driver,	"tz",  15,  0,  0x0,0,	0,    '?',     0,   1,   7,    0, },


{ &se_driver,	"se",   1,se_intr,0x0,0, 0,     0,     0,  -1,  -1,    0, },
{ &se_driver,	"se",   1,se_intr,0x0,0, 0,     1,     0,  -1,  -1,    0, },
{ &se_driver,	"se",   1,se_intr,0x0,0, 0,     2,     0,  -1,  -1,    0, },
{ &se_driver,	"se",   0,se_intr,0x0,0, 0,   '?',     0,  -1,  -1,    0, },

{ &dz_driver,	"dz",   0,dz_intr,0x0,0, 0,    '?',     0,  -1,  -1,    0, },
{ &pm_driver,   "pm",   0,pm_intr,0x0,0, 0,    '?',	0,  -1,  -1,	0, },
	0
};


sci_config(regs,ram)
	char	*regs, *ram;
{
	sci_buffer_init((sci_dmaregs_t) (regs + VAX3100_STC_DMAREG_A), ram);

	/*
	 * Probe the sci based scsi busses. 
	 */
	configure_bus_master( "sci", (vm_offset_t)(regs + VAX3100_STC_5380_A), 0, 0, "slot");
	configure_bus_master( "sci", (vm_offset_t)(regs + VAX3100_STC_5380_B), 0, 1, "slot");
}
#endif

#endif	VAX3100
