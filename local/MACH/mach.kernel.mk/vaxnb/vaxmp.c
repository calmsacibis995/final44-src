/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vaxmp.c,v $
 * Revision 2.4  89/02/26  10:59:10  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/10/11  13:07:36  rpd
 * 	cca_snarf now takes a verbose switch.
 * 	[88/10/10            rvb]
 * 
 * Revision 2.2  88/08/10  10:53:14  rvb
 *  24-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Add freeze_processor.
 * 
 *  10-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Try to appease the VAX6200 console monitor.
 * 
 *   7-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	start_processors() now takes one flag arg.
 * 
 *   7-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Processor start/stop support.
 * 
 *   27-May-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Created.
 * 
 */
/*
 *	File:	ka62a.c
 *	Author:	Robert V. Baron
 *
 *	Multiprocessor support for the vax.
 */
#include <cpus.h>
#include <cputypes.h>

#include <sys/types.h>
#include <kern/lock.h>
#include <sys/reboot.h>
#include <mach/machine.h>
#include <vax/cpu.h>
#if	VAX6200
#include <vaxnb/ka62a.h>
vm_offset_t	ip_space;
vm_offset_t	wei_space;
int		freeze_control;
#endif	VAX6200
#if	VAX820
#include <vaxnb/ka820.h>
#endif	VAX820
#if	VAX8800
#include <vaxnb/ka88.h>
#endif	VAX8800

#if	NCPUS > 1
#include <vax/bi_node.h>
#include <vaxnb/node.h>

start_processors(flag)
{
	register int i;
	extern int boothowto;

	if (flag) {
		printf("Uni-processor boot; slaves will not be started.\n");
		return;
	}
	for (i = 0; i < NCPUS; i++) {
		if (cpunode[i].node == 0)
			continue;
		else if (machine_slot[i].running)
			continue;

		start_processor(i);
	}
}

start_processor(i)
{
register int j;
register struct machine_slot *mp = &machine_slot[i];

	if (cpunode[i].node == 0) {
		printf("Node %x not a processor.\n", i);
		return 0;
	} else if (mp->running) {
		printf("Processor %x already running.\n", i);
		return 0;
	}

	switch (cpu) {
	case VAX_820:
		send_string_to_console(i, "I\015S 80000010\015");
		break;
	case VAX_6200:
		cca_to_slave(i, "start 80000010");
		break;
	}

	for (j = 2000000; j && !mp->running; j--);

	if (mp->running) {
		printf("Processor %d started.\n", i);
		return 1;
	} else {
		printf("Processor %d did NOT start.\n", i);
		return 0;
	}
}

exit_processor(i)
{
register int j;
register struct machine_slot *mp = &machine_slot[i];

	if (cpunode[i].node == 0) {
		printf("Node %x not a processor.\n", i);
		return 0;
	} else if (!machine_slot[i].running) {
		printf("Processor %x already stopped.\n", i);
		return 0;
	} else if (i == master_cpu) {
		printf("Cute! but processor %x is the master.\n", i);
		return 0;
	}

	should_exit[i] = TRUE;

	for (j = 2000000; j && mp->running; j--);

	if (!mp->running) {
#if	VAX6200
		if (cpu == VAX_6200) {
			cca_snarf(i, 0);
			cca_snarf(i, 0);
			printf("Processor %x Exited.\n", i);
		}
#endif	VAX6200
		printf("Processor %x halted.\n", i);
		return 1;
	} else {
		printf("Processor %x did NOT halt.\n", i);
		return 0;
	}
}

halt_processor(i)
{
	if (cpunode[i].node == 0) {
		printf("Node %x not a processor.\n", i);
		return 0;
	} else if (!machine_slot[i].running) {
		printf("Processor %x already stopped.\n", i);
		return 0;
	} else if (i == master_cpu) {
		printf("Cute! but processor %x is the master.\n", i);
		return 0;
	}

	switch (cpu) {
	case VAX_820:
		send_string_to_console(i, "\015");
		break;
	case VAX_6200:
		cpunode[i].addr62->ber = XMIBER_NHALT;
		break;
	}
#if	VAX6200
		if (cpu == VAX_6200) {
			cca_snarf(i, 0);
			cca_snarf(i, 0);
			printf("Processor %x Node Halted.\n", i);
		}
#endif	VAX6200

	return 1;
}

continue_processor(i)
{
	if (cpunode[i].node == 0) {
		printf("Node %x not a processor.\n", i);
		return 0;
	} else if (!machine_slot[i].running) {
		printf("Processor %x is not running.\n", i);
		return 0;
	} else if (i == master_cpu) {
		printf("Cute! but processor %x is the master.\n", i);
		return 0;
	}

	switch (cpu) {
	case VAX_820:
		send_string_to_console(i, "\015C\015");
		break;
	case VAX_6200:
		cca_to_slave(i, "C");
		break;
	}
	return 1;
}

freeze_processor(i)
{
	if (cpunode[i].node == 0) {
		printf("Node %x not a processor.\n", i);
		return 0;
	} else if (!machine_slot[i].running) {
		printf("Processor %x already stopped.\n", i);
		return 0;
	} else if (i == master_cpu) {
		printf("Cute! but processor %x is the master.\n", i);
		return 0;
	}

#if	VAX6200
	if (cpu == VAX_6200) {
		register char x = 1;

		freeze_control |= 1<<i;
		*(char *)(wei_space + (1<<i)) = x;	/* tap processor */
		return 1;
	}
#endif	VAX6200
	return 0;
}

freeze_all_processors(but)
{
register int i;
register char x = 1;

#if	VAX6200
	if (cpu == VAX_6200) {
		for (i = 0; i < NCPUS; i++) {
			struct machine_slot *mp = &machine_slot[i];
			if (!mp->running)
				continue;
			if (i == but)
				continue;

			freeze_control |= 1<<i;
		}

		*(char *)(wei_space + freeze_control) = x;	/* tap processors */
	}
#endif	VAX6200
}

thaw_all_processors()
{
#if	VAX6200
	if (cpu == VAX_6200) {
		freeze_control  = 0;
	}
#endif	VAX6200
}
#endif	NCPUS > 1

int last_cpu;
int interrrupted[NCPUS];
interrupt_processor(which_cpu)
{
#if	NCPUS > 1

	interrrupted[which_cpu]++;

	switch (cpu) {
#if	VAX6200
	case VAX_6200:
		{
			register char x = 1;
			/*
			 * this must expand to a movb ?
			 */
			*(char *)(ip_space + (1<<which_cpu)) = x;
			return;
		}
#endif	VAX6200
#if	VAX8800
	case VAX_8800:
		{
			mtpr(INOP, 0);	/* assume interrupting other processor */
			return;
		}
#endif	VAX8800
#if	VAX820
	case VAX_820:
		bi_interrupt_processor(which_cpu);
		return;
#endif	VAX820
	}
#if	NMACH_MPM > 0
	{
		extern int nummpm;
		if (nummpm > 0) {
			mpm_interrupt_processor(which_cpu);
			return;
		}
	}
#endif	NMACH_MPM > 0
#endif	NCPUS > 1
}

#if	VAX6200
struct pcb *pcb[NCPUS];
#endif	VAX6200

slave_attn(pc, psl, pcbp)
int (*pc)();
struct pcb *pcbp;
{
#if	VAX6200
	register int bit = 1 << cpu_number();
	register int event = 0;
extern	int freeze_control;
extern	int console_control;
extern	int move_control;

	if (freeze_control & bit) { /* some one wants me to stop */
		pcb[cpu_number()] = pcbp;
		save_context();		/* for $k */
		while (freeze_control & bit) ;	/* spin */
		event++;
	}
	if (console_control & bit) { /* some one wants us to give up console */
		release_console();
		event++;
	} else if (move_control) {   /* some one wants us to acquire console */
		grab_console();
		event++;
	} else if (console_control) {
		panic("slave_attn: misdirected wei");
	}

	if (!event) {
		asm("halt");
	}
#endif	VAX6200
}
