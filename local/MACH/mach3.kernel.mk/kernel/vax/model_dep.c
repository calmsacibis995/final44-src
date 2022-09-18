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
 * $Log:	model_dep.c,v $
 * Revision 2.14  93/05/15  18:58:30  mrt
 * 	machparam.h -> machspl.h
 * 
 * Revision 2.13  92/01/27  16:43:23  rpd
 * 	Added simple_lock_pause.
 * 	[92/01/26            rpd]
 * 
 * Revision 2.12  92/01/03  20:33:08  dbg
 * 	Rename kdb_init to ddb_init.  Remove esym.
 * 	RB_KDB is unused.
 * 	[91/09/11            dbg]
 * 
 * Revision 2.11  91/07/31  18:19:26  dbg
 * 	Allocate interrupt stacks here for multiprocessors.
 * 	Remove call to pcb_module_init.
 * 	Replace blkclr with bzero.
 * 	[91/07/25            dbg]
 * 
 * Revision 2.10  91/06/19  12:01:25  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:57:55  rvb]
 * 
 * 	Support for VaxStation 3100: new processor
 * 	[91/06/04            rvb]
 * 
 * Revision 2.9  91/05/14  17:44:30  mrt
 * 	Correcting copyright
 * 
 * Revision 2.8  91/05/08  13:19:36  dbg
 * 	Add memory and CPU configuration declarations that had
 * 	been in vax_init.c.  Call pmap_bootstrap here.
 * 	[91/04/11            dbg]
 * 
 * 	Add volatile declarations where needed.
 * 	[91/03/28            dbg]
 * 
 * 	Call pcb_module_init.
 * 	Include vax/machparam.h for SPL definitions.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.7  91/01/08  16:41:42  rpd
 * 	Added continuation argument to thread_block.
 * 	[90/12/08            rpd]
 * 
 * Revision 2.6  90/10/12  12:39:01  rpd
 * 	Fixed call to thread_bind in halt_all_cpus.
 * 	[90/10/10            rpd]
 * 
 * Revision 2.5  90/08/27  22:14:07  dbg
 * 	Add cpu_start, cpu_control for multiprocessors.  Revise startup
 * 	and shutdown code for new processor structures.
 * 	[90/07/18            dbg]
 * 
 * Revision 2.4  90/06/02  15:08:22  rpd
 * 	Fixed timemmap to not require execute permission.
 * 	[90/05/01            rpd]
 * 
 * Revision 2.3  90/01/11  11:46:02  dbg
 * 	Start up and shut down other CPUs.
 * 	[89/12/19            dbg]
 * 
 * 	Add start_other_cpus.  Remove lint.
 * 	[89/12/01            dbg]
 * 
 * Revision 2.2  89/08/09  14:33:30  rwd
 * 	Include mach/vm_prot.h
 * 	[89/08/08            rwd]
 * 	Must define mtime as external
 * 	[89/08/08            rwd]
 * 	Add timemmap function.
 * 	[89/08/08            rwd]
 * 
 * Revision 2.1  89/08/03  16:28:39  rwd
 * Created.
 * 
 *  3-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */
#include <cpus.h>
#include <platforms.h>
#include <mach_kdb.h>

#include <mach/boolean.h>
#include <kern/cpu_number.h>
#include <kern/thread.h>
#include <mach/machine.h>
#include <sys/reboot.h>
#include <kern/processor.h>
#include <vm/vm_kern.h>

#include <vax/cons.h>
#include <vax/cpu_data.h>
#include <vax/io_map.h>
#include <vax/mtpr.h>
#include <vax/vm_defs.h>
#include <vax/thread.h>		/* for pcb_t */
#include <vax/machspl.h>
#include <kern/sched_prim.h>

extern char	version[];
extern int	cold;		/* cold_start */
#if	NCPUS > 1
extern void	set_cpu_number_ptr();
void		interrupt_stack_alloc();	/* forward */
#endif	NCPUS > 1

extern void	setup_main();
extern void	inittodr();

/*
 *	Cpu and memory configuration variables.
 */
#if	MACH_LOAD
vm_offset_t	loadpt;		/* kernel is loaded at this physical address */
#endif

vm_size_t	mem_size = 0;	/* patch to limit physica memory use */
vm_offset_t	avail_start;	/* first available physical address */
vm_offset_t	avail_end;	/* last available physical address */
vm_offset_t	virtual_avail;	/* first available virtual address */
vm_offset_t	virtual_end;	/* last available virtual address */

int		cpu;		/* VAX cpu type code */
cpu_model_t	cpu_model;	/* vector for CPU-specific routines */

/*
 *	Bootstrap information passed to kernel.
 */
int		boothowto;	/* boot flags */

#if	VAX6200 || VAX650 || VAX3100
int		boot_reg7;
int		boot_reg8;
int		mem_bitmap_size;
vm_offset_t	mem_bitmap;
#endif	VAX6200 || VAX650 || VAX3100

/*
 *	Cpu initialization, running virtual, but without MACH VM
 *	set up.
 */
void machine_startup()
{
	int	subtype;

	/*
	 * Bootstrap pmap module.  Page tables are already set up.
	 */
	pmap_bootstrap();

	/*
	 * Set up CPU description.
	 */
	cpu_model = cpu_descriptions[cpu];
	cpuspeed = cpu_model->m_cpuspeed;

	/*
	 * Set up the CPU hardware registers, and console if necessary.
	 * Find the master CPU number.
	 */
	if (cpu_model->m_setup)
	    (*cpu_model->m_setup)();
#if	NCPUS > 1
	set_cpu_number_ptr();
#endif	NCPUS > 1
	master_cpu = cpu_number();

#if	MACH_KDB
	/*
	 * Initialize the kernel debugger.
	 */
	ddb_init();

	/*
	 * Cause a breakpoint trap to the debugger before proceeding
	 * any further if the proper option bit was specified in
	 * the boot flags.
	 */
	if (boothowto & RB_HALT)
		gimmeabreak();
#endif	MACH_KDB

	printf(version);

	/*
	 * Allow interrupts.
	 */
	(void) spl1();

	/*
	 * Set up CPU-specific registers, cache, etc.
	 */
	subtype = (*cpu_model->m_init)();

#if	NCPUS > 1
	printf("Master cpu at slot %d.\n", master_cpu);
#endif	NCPUS > 1

	machine_slot[master_cpu].is_cpu = TRUE;
	machine_slot[master_cpu].running = TRUE;
	machine_slot[master_cpu].cpu_type = CPU_TYPE_VAX;
	machine_slot[master_cpu].cpu_subtype = subtype;


	/*
	 * Fix the address map so that VM initialization can work.
	 */
	io_map_done();

	/*
	 * Start the system.
	 */
	setup_main();

}

/*
 * Find devices.  The system is alive.
 */
void machine_init()
{
#if	NCPUS > 1
	/*
	 * Allocate interrupt stacks.
	 */
	interrupt_stack_alloc();
#endif

	/*
	 * Find the devices
	 */
	(*cpu_model->m_configure)();

	/*
	 * Vector IO interrupts normally
	 */
	cold = 0;
	scb_write_protect();

	/*
	 * Find the root device
	 */
	get_root_device();

	/*
	 * Turn off reboot/restart inhibit flags
	 */
	(*cpu_model->m_reboot_ok)();

	/*
	 * Get the time
	 */
	inittodr();
}

#if	NCPUS > 1

/*
 * Addresses of bottom of interrupt stacks.
 */
vm_offset_t	interrupt_stack[NCPUS];

/*
 * First cpu`s interrupt stack.
 */
char		intstack[];


void interrupt_stack_alloc()
{
	register int	i;
	int		cpu_count;
	vm_offset_t	stack_start;
	vm_offset_t	stack_size;

	/*
	 * Count the number of CPUs found.
	 */
	cpu_count = 0;
	for (i = 0; i < NCPUS; i++)
	    if (machine_slot[i].is_cpu)
		cpu_count++;

	/*
	 * Allocate an interrupt stack for each CPU except for
	 * the master CPU (which uses the bootstrap stack).
	 */
	stack_size = INTSTACK_SIZE * (cpu_count - 1);
	if (kmem_alloc_wired(kernel_map, &stack_start, stack_size)
		!= KERN_SUCCESS)
	    panic("interrupt_stack_alloc");

	bzero((char *)stack_start, stack_size);

	/*
	 * Set up pointers.
	 */
	for (i = 0; i < NCPUS; i++) {
	    if (i == master_cpu)
		interrupt_stack[i] = (vm_offset_t) &intstack[0];
	    else if (machine_slot[i].is_cpu) {
		interrupt_stack[i] = stack_start;
		stack_start += INTSTACK_SIZE;
	    }
	}

}

void start_other_cpus()
{
	extern int	start_lock;
	register int	i;
	register struct machine_slot *ms;

	/*
	 * Allow other CPUs to run if started
	 */
	bit_unlock(1, (char *)&start_lock);	/* XXX - see locore.s */

	if (boothowto & RB_UNIPROC) {
	    printf("Uni-processor boot; slaves will not be started.\n");
	    return;
	}

	/*
	 * Start up other CPUs
	 */
	for (i = 0, ms = &machine_slot[0];
	     i < NCPUS;
	     i++, ms++)
	{
	    if (ms->is_cpu && i != master_cpu && !ms->running) {
		(*cpu_model->m_startcpu)(i);
	    }
	}
}

void slave_machine_init()
{
	register int	my_cpu = cpu_number();
	int	subtype;

	printf("\n");

	/*
	 * Assume slave and master processor are same type XXX
	 */
	subtype = (*cpu_model->m_slave_config)();
	machine_slot[my_cpu].cpu_type = CPU_TYPE_VAX;
	machine_slot[my_cpu].cpu_subtype = subtype;


	printf("Slave started at slot %d.\n", my_cpu);
	printf("Master cpu at slot %d.\n", master_cpu);
	printf("Hit <E> to exit slave.\n");
	slave_cnenable();

}

/*
 * Start up a processor, by processor number.
 */
kern_return_t
cpu_start(processor_number)
	int	processor_number;
{
	(*cpu_model->m_startcpu)(processor_number);
	return (KERN_SUCCESS);
}

/*
 * Random cpu control functions.
 */
/*ARGSUSED*/
kern_return_t
cpu_control(processor_number, info, count)
	int	processor_number;
	int	*info;
	long	count;
{
	/* nothing here */
	return (KERN_FAILURE);
}

/* XXX should be adjusted per CPU speed */
int simple_lock_pause_loop = 100;

unsigned int simple_lock_pause_count = 0;	/* debugging */

void
simple_lock_pause()
{
	static volatile int dummy;
	int i;

	simple_lock_pause_count++;

	/*
	 * Used in loops that are trying to acquire locks out-of-order.
	 */

	for (i = 0; i < simple_lock_pause_loop; i++)
	    dummy++;	/* keep the compiler from optimizing the loop away */
}

#endif	NCPUS > 1

tocons(c)
	char	c;
{
	register oldmask;

	while (((oldmask = mfpr(TXCS)) & TXCS_RDY) == 0)
		continue;

#ifdef	VAX8600
	if (cpu == VAX_8600) {

	    mtpr(TXCS, TXCS_LCONS | TXCS_WMASK);
	    while ((mfpr(TXCS) & TXCS_RDY) == 0)
		continue;

	    mtpr(TXDB, c);

	    while ((mfpr(TXCS) & TXCS_RDY) == 0)
		continue;
	    mtpr(TXCS, oldmask | TXCS_WMASK);
	}
	else
#endif	VAX8600
	{
	    c |= TXDB_CONS;
	    mtpr(TXDB, c);
	}
#ifdef lint
	oldmask = oldmask;
#endif lint
}

/*
 * Corrected read data interrupt.
 */
memerr()
{
	(*cpu_model->m_crd)();
}

/*
 * Machine check.
 */
struct cmcframe {			/* common to all processors */
	int	cmc_bytecount;
	int	cmc_summary;
};

void machinecheck(cmcf)
	char *	cmcf;
{
	register int type = ((struct cmcframe *)cmcf)->cmc_summary;
	int	result;

	printf("machine check %x: ", type);
	result = (*cpu_model->m_mchk)(cmcf);
	if (result)
		return;

	memerr();
	panic("mchk");
}

halt_cpu()
{
	mtpr(IPL, 0x1f);
	(*cpu_model->m_haltcpu)(FALSE);
}

halt_all_cpus(reboot)
	boolean_t	reboot;
{
#if	NCPUS > 1
#define	LOOPCOUNT	1000
#define	WAITCOUNT	1000

	register int	i, j;
	register processor_t	processor;

	thread_bind(current_thread(), master_processor);
	if (current_processor() != master_processor)
	    thread_block((void (*)()) 0);

	for (i = 0; i < NCPUS; i++) {
	    processor = cpu_to_processor(i);
	    if (processor->state != PROCESSOR_OFF_LINE &&
		processor != current_processor())
	    {
		processor_shutdown(processor);

		for (j = 2000000;
		     j > 0 && *(volatile boolean_t *)&machine_slot[i].running;
		     j--)
		    continue;
	    }
	}
#endif	NCPUS > 1
	mtpr(IPL, 0x1f);
	(*cpu_model->m_haltcpu)(reboot);
}

interrupt_processor(which_cpu)
{
	(*cpu_model->m_interrupt)(which_cpu);
}

wtime(pc, psl, pcb)
	int	pc;
	int	psl;
	pcb_t	pcb;
{
#if	VAX6200
	if (cpu == VAX_6200)
	    ka6200_wtime(pc, psl, pcb);
	else
#endif	VAX6200
	    panic("write_timeout at %x", pc);
}

#include <mach/vm_prot.h>
#include <vm/pmap.h>
#include <mach/time_value.h>

timemmap(dev,off,prot)
	vm_prot_t prot;
{
	extern time_value_t *mtime;

#ifdef	lint
	dev++; off++;
#endif	lint

	if (prot & VM_PROT_WRITE)
		return (-1);

	return (btop(pmap_extract(pmap_kernel(), (vm_offset_t) mtime)));
}
