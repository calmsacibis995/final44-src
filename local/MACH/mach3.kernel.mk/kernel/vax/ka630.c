/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ka630.c,v $
 * Revision 2.2  91/06/19  12:00:50  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:48:01  rvb]
 * 
 * Revision 2.1  89/08/03  16:26:49  rwd
 * Created.
 * 
 *  3-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *	KA630 model-dependent routines.
 */
#include <platforms.h>
#include <qd.h>
#include <qv.h>

#if	VAX630

#include <kern/cpu_number.h>
#include <mach/machine.h>

#include <vax/cpu_data.h>
#include <vax/io_map.h>
#include <vax/ka630.h>
#include <vax/cpmbx.h>

#include <vaxuba/ubavar.h>

extern int	v_console;

struct cldevice *	cldevice;	/* the watch chip */
struct sie {
	long	sie_pad;
	short	sie_reserved;
	char	sie_version;
	char	sie_syscode;
} *sie;					/* system ID at start of boot ROM */
struct ka630cpu *	ka630cpu;	/* memory controler */

int	ka630_setup(), ka630_init(), ka630_config(),
	ka630_reboot_ok(), ka630_crd(), ka630_mchk(),
	ka630_clear_mchk(), ka630_halt();

struct model_dep ka630_model = {
	ka630_setup,
	ka630_init,
	ka630_config,
	0,				/* no slave_config */
	ka630_reboot_ok,
	ka630_crd,
	ka630_mchk,
	ka630_clear_mchk,
	ka630_halt,
	0,				/* no interrupt */
	2
};

/*
 * Map required memory for the 630, and find the console.
 * Called running virtual, but with VM not initialized.
 */
ka630_setup()
{
	/*
	 * Map in the watch chip, system ID register, and
	 * memory controller.
	 */
	cldevice = (struct cldevice *)io_map((vm_offset_t)0x200b8000,
					sizeof (struct cldevice));
	sie = (struct sie *)io_map((vm_offset_t)0x20040000,
					sizeof(struct sie));
	ka630cpu = (struct ka630cpu *)io_map((vm_offset_t)0x20080000,
					sizeof(struct ka630cpu));

	/*
	 * Point to the console mailbox.
	 */
	cpmbx = (char *)&cldevice->cpmbx;

	/*
	 * Map in the Qbus.
	 */
	qbus_map();

	/*
	 * Configure the console, if it is in use.
	 *
	 *  The first entry in the watch chip RAM (following CPMBX) evidently
	 *  records the console state.  From experimentation, this value
	 *  has been observed as 0x66 or 0x60 when the display is the console
	 *  and 0x6 when the serial line unit is the console.  For now, we'll
	 *  guess that the 0x70 bits are significant and check those.
	 */
	if (v_console || (cldevice->wcram[0] & 0x70) != 0x60) {
	    /*
	     * Console not in use
	     */
	    v_console = 0;
	}
	else {
#if	NQV > 0
	    qvcons_init();
#endif
#if	NQD > 0
	    qdcons_init();
#endif
	}
}

int ka630_init()
{
	extern int	D_float;
	static char *cpumodes[] = {
	    "Normal",
	    "Language Query",
	    "Loopback",
	    "Maintenance"
	};
	unsigned short bdr;

	printf("MicroVAX-II (with%s FPU, SYSCODE:%d, ROM Rev:%d)\n",
		D_float ? "" : "out",
		sie->sie_syscode,
		sie->sie_version);

	bdr = ka630cpu->ka630_bdr;
	printf("bdr at tr0 (HALT %sabled, %s Mode)\n",
		(bdr & KA630BDR_HLTENB) ? "En" : "Dis",
		cpumodes[(bdr >> 8) & 0x3]);

	/*
	 * Enable parity.
	 */
	ka630cpu->ka630_mser = KA630MSER_PAREN;

	return (CPU_SUBTYPE_UVAXII);
}

ka630_config()
{
	/*
	 * There is only one QBus on a MicroVax II, and
	 * qbus_init has already disguised it as a Unibus.
	 */
	unifind(&uba_hd[0]);
	numuba++;
}

ka630_reboot_ok()
{
	set_cpmbx(0);	/* ? */
}

/*
 * Corrected read data interrupt.
 */
ka630_crd()
{
	/* do nothing */
}

struct mc630frame {
	int	mc63_bcnt;		/* byte count == 0xc */
	int	mc63_summary;		/* summary parameter */
	int	mc63_mrvaddr;		/* most recent vad */
	int	mc63_istate;		/* internal state */
	int	mc63_pc;		/* trapped pc */
	int	mc63_psl;		/* trapped psl */
};

/*
 * Machine check.
 */
int ka630_mchk(cmcf)
	char *	cmcf;	/* common machine-check frame */
{
	register struct ka630cpu *ka630addr = ka630cpu;

	register struct mc630frame *mcf = (struct mc630frame *)cmcf;
	printf("vap %x istate %x pc %x psl %x\n",
	    mcf->mc63_mrvaddr, mcf->mc63_istate,
	    mcf->mc63_pc, mcf->mc63_psl);
	if (ka630addr->ka630_mser & KA630MSER_MERR) {
		printf("mser=0x%x ",ka630addr->ka630_mser);
		if (ka630addr->ka630_mser & KA630MSER_CPUER)
			printf("page=%d",ka630addr->ka630_cear);
		if (ka630addr->ka630_mser & KA630MSER_DQPE)
			printf("page=%d",ka630addr->ka630_dear);
		printf("\n");
	}

	return (0);
}

/*ARGSUSED*/
ka630_clear_mchk(nioa)
	int	nioa;
{
}

/*
 * Halt CPU
 */
ka630_halt(reboot)
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
#endif	VAX630
