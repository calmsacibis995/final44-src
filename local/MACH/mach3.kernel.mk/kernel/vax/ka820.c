/* 
 * Mach Operating System
 * Copyright (c) 1991,1989 Carnegie Mellon University
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
 * $Log:	ka820.c,v $
 * Revision 2.5  91/06/19  12:01:06  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:49:53  rvb]
 * 
 * Revision 2.4  91/05/14  17:44:01  mrt
 * 	Correcting copyright
 * 
 * Revision 2.3  91/05/08  13:18:22  dbg
 * 	Ignore BI-error machine checks while configuring system (they
 * 	may arise from BI bus resets).
 * 	[91/04/19            dbg]
 * 
 * Revision 2.2  90/01/11  11:45:47  dbg
 * 	Add ka820_start.
 * 	[89/12/19            dbg]
 * 
 * 	Make ka820_init and ka820_slave_config return CPU subtype.
 * 	[89/12/04            dbg]
 * 
 * Revision 2.1  89/08/03  16:37:14  rwd
 * Created.
 * 
 *  3-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 * 8200 routines.
 */

#include <cpus.h>
#include <platforms.h>

#if	VAX820

#include <kern/cpu_number.h>
#include <mach/machine.h>

#include <vm/vm_kern.h>

#include <vax/io_map.h>
#include <vax/ka820.h>
#include <vax/watch_chip.h>
#include <vax/mtpr.h>
#include <vax/cpu_data.h>
#include <vax/bi_node.h>
#include <vax/node.h>
#include <vax/cons.h>

int *	ka820_csr;
int *	ka820_ber;

int	ka820_setup(), ka820_init(), ka820_config(),
	ka820_slave_config(),
	ka820_reboot_ok(), ka820_crd(), ka820_mchk(),
	ka820_clear_mchk(), ka820_halt(), ka820_interrupt(),
	ka820_start();

struct model_dep ka820_model = {
	ka820_setup,
	ka820_init,
	ka820_config,
	ka820_slave_config,
	ka820_reboot_ok,
	ka820_crd,
	ka820_mchk,
	ka820_clear_mchk,
	ka820_halt,
	ka820_interrupt,
	2,
	ka820_start
};

union cpusid_820 {
	unsigned int	sid;
	struct sid820 {
	    unsigned int	ucode_rev:8,	/* ucode rev */
				sec_patch:1,	/* secondary patch */
				patch_rev:10,	/* patch revision */
				cpu_rev:5,	/* cpu revision */
				cpu_type:8;	/* VAX_820 */
	} sid820;
};

int	intmask;
int	crd;
int	crd_cnt;

ka820_cache_on()
{
	mtpr(CADR, 0);
	if (crd)
	    *ka820_csr |= PCCSR_CRD;
}

/*
 * Map in required memory for the 8200.
 */
ka820_setup()
{
	ka820_ber = (int *)(io_map((vm_offset_t) 0x20080000, sizeof(int))
			+ 2*sizeof(int));
	ka820_csr = (int *)io_map((vm_offset_t)0x20088000, sizeof(int));
	watch_chip = (struct watch_chip *)io_map((vm_offset_t)0x200b8000,
						 sizeof(struct watch_chip));
	ka820_cache_on();
}

int
ka820_init()
{
	union cpusid_820	cpusid;
	extern int		cpuspeed;
	extern int 		intmask;
	register struct ioa_node *ioa;

	extern void scan_bix();

	cpusid.sid = mfpr(SID);
	printf("VAX 8200, urev=%d, patch rev=%d, cpu rev=%d\n",
		cpusid.sid820.ucode_rev,
		cpusid.sid820.patch_rev,
		cpusid.sid820.cpu_rev);

	master_cpu = mfpr(BINID);
	intmask = 1 << master_cpu;

	/*
	 * An 8200 system has one BI bus.  Scan it for CPUs and memory.
	 */
	ioa = &ioa_node[nioa];
	ioa->bi_paddr = BI_ADDR(0);
	scan_bix(ioa);

	return (CPU_SUBTYPE_VAX8200);
}

ka820_config()
{
	bi_settle();
	probe_bi(0, 0, 1 << master_cpu);
	nioa++;
}

int
ka820_start(i)
	int	i;
{
	send_string_to_console(i, "I\015S 80000010\015");
}

int
ka820_slave_config()
{
	ka820_cache_on();

	return (CPU_SUBTYPE_VAX8200);
}

ka820_reboot_ok()
{
	tocons(TXDB_CWSI);
	tocons(TXDB_CCSI);
}

ka820_crd()
{
	register int i;

	printf("ka820 crd error\n");
	print_ka820();

	for (i = 0; i < nmem; i++) {
	    register struct bi_node *mp = (struct bi_node *) mem_node[i].addr;

	    printf("MEMORY Node %x at %x\n",
		   mem_node[i].node,
		   pmap_extract(kernel_pmap, (vm_offset_t)mp));
	    print_bi(mp);
	}
	if (crd_cnt++ >= 10)
	    *ka820_csr = ((*ka820_csr & PCCSR_RW) | PCCSR_ERR) & ~PCCSR_CRD;
}

struct mc820frame {
	int	mc82_bcnt;		/* byte count = 0x20 */
	int	mc82_summary;
	int	mc82_parm1;		/* parameter 1 */
	int	mc82_var;		/* va register */
	int	mc82_vapr;		/* va prime register */
	int	mc82_mar;		/* memory address */
	int	mc82_status;		/* status word */
	int	mc82_pcf;		/* PC at failure */
	int	mc82_upc;		/* microcode pc */
	int	mc82_pc;		/* current PC */
	int	mc82_psl;		/* current PSL */
};

#define	MC82_BIERR	0x10		/* BI error */

extern int	cold;

ka820_mchk(cmcf)
	char *	cmcf;
{
	register struct mc820frame *mcf = (struct mc820frame *)cmcf;
	register struct bi_node *biv = &ioa_node[0].bi_vaddr[cpu_number()];

	/*
	 * Ignore BI bus errors during configuration
	 */
	if (cold && mcf->mc82_summary == MC82_BIERR) {
	    printf("BI error ignored\n");
	    mtpr(MCESR, 0xf);
	    return (1);
	}

	printf("Machine Check: status %b\n", mcf->mc82_status, KA820MCHK);
	printf("va %x vap %x mar %x pc %x pcf = %x psl %x\n",
		mcf->mc82_var, mcf->mc82_vapr, mcf->mc82_mar, mcf->mc82_pc,
		mcf->mc82_pcf, mcf->mc82_psl);
	print_ka820();
	if (biv) {
		print_bi(biv);
		biv->ber = biv->ber & BER_ERR;
	}
	*ka820_csr = (*ka820_csr & PCCSR_RW) | PCCSR_ERR;
	mtpr(MCESR, 0);

	return (0);
}

/*ARGSUSED*/
ka820_clear_mchk(ioa_number)
	int	ioa_number;
{
	mtpr(MCESR, 0xf);
}

ka820_halt(reboot)
	boolean_t	reboot;
{
	if (reboot) {
	    tocons(TXDB_BOOT);
	    asm("halt");
	}

	mtpr(MAPEN, 0);	/* seems to confuse it enough that it does not
			   restart */
	asm("halt");
}

ka820_interrupt(dest)
	int	dest;
{
	mtpr(IPIR, 1<<dest);
}

/* ---- */

print_ka820()
{
	printf("\tPort Controller CSR\t%b\n", *ka820_csr, PCCSR);
}

/*
 * rxcd_intr is called at interrupt time to receive a character from
 * the logical console.
 */

rxcd_intr()
{
	register int	val;
	register int	c;

#if	NCPUS > 1
	val = rxcd_receive();	/* need flow control, test V bit... */

	c = val & 0xff;
#ifdef unneeded
	sender = (val & 0xf00) >> 8;
#endif unneeded

	/*
	 * If we are the master, echo the character for the slave.
	 * If we are a slave, simulate receiving a character on
	 * the console.
	 */
	if (cpu_number() == master_cpu) {
	    cnputc(c);
	}
	else {
	    slave_input(c);
	}
#else	NCPUS > 1
	panic("rxcd_intr");
#endif	NCPUS > 1
}

/*
 * send the string to the specified console.
 */
send_string_to_console(dest, str)
	register int	dest;
	register char *str;
{
	register int i;

	while (i = *str++) {
	    rxcd_send(dest, i);
	    for (i = 10000; i-- > 0;)
		;	/* delay */
	}
}

#endif	VAX820
