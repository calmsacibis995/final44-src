/* 
 * Mach Operating System
 * Copyright (c) 1994,1993,1992 Carnegie Mellon University
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
 * $Log:	clockpit.c,v $
 * Revision 2.4  94/12/15  15:30:21  dbg
 * 	RT-MERGE.
 * 	[94/06/07            dbg]
 * 
 * 	Renamed 'time_spec' to 'timespec'.
 * 	[94/05/24            dbg]
 * 
 * Revision 2.3  93/12/23  10:05:01  dbg
 * 	Added missing include files.
 * 	[93/12/14            dbg]
 * 
 * Revision 2.2  93/11/17  16:41:54  dbg
 * 	Used common routines from device/clock_dev.c
 * 	[93/06/02            dbg]
 * 
 * 	Changed mmap routines to return physical address instead of
 * 	physical page number.
 * 	[93/05/24            dbg]
 * 
 * 	Added to microkernel mainline.
 * 
 * 	Created
 * 	[92/06/22	savage]
 * 
 */
#include <clockpit.h>

#include <mach/boolean.h>
#include <mach/timespec.h>
#include <kern/mach_clock.h>
#include <kern/kern_io.h>
#include <vm/vm_kern.h>

#include <sys/types.h>
#include <chips/busses.h>
#include <device/device_types.h>

#include <i386/int_frame.h>
#include <i386/machspl.h>
#include <i386/pio.h>
#include <i386/pit.h>

/*
 *	Adjust for PIT clock round off... Ugly, but true...
 */
#define	HZ	100			/* default frequency */

#define CLOCKPIT_SKEW(res)		(((CLKNUM%(NANOSEC_PER_SEC/res)) \
					       * res) / CLKNUM)
#define CLOCKPIT_DEFAULT_RESOLUTION	(NANOSEC_PER_SEC/HZ - \
					 CLOCKPIT_SKEW((NANOSEC_PER_SEC/HZ)))

#define CLOCKPIT_MAX_RESOLUTION 	(10000000)

/*
 *	Minimum set to 1/2 a millisecond... if you want to play with lower
 *	then change this number.
 */
#define CLOCKPIT_MIN_RESOLUTION		(500000)


mach_clock_data_t	clockpit[NCLOCKPIT];

kern_return_t clockpit_set_resolution(
	mach_clock_t	clock,
	unsigned int	*resolution,	/* in/out */
	int		*skew);		/* in/out */
void clockpit_change_resolution(
	mach_clock_t	clock);
void clockpit_enable_interrupts(
	mach_clock_t	clock,
	boolean_t	on);

struct clock_ops	clockpit_ops = {
	0,			/* set_time */
	clockpit_set_resolution,
	0,			/* set_timeout */
	0,			/* update */
	clockpit_change_resolution,
	0,			/* stop */
	0,			/* start */
	0			/* enable_interrupts */
};

boolean_t clockpitprobe(
	vm_offset_t		port,
	struct bus_device 	*dev);
void clockpitattach(
	struct bus_device	*dev);

static vm_offset_t		clockpit_std[] = { 0 };
static struct bus_device	*clockpit_info[NCLOCKPIT];
struct bus_driver		clockpitdriver = {
	clockpitprobe, 0, clockpitattach, 0, clockpit_std, "clockpit",
	clockpit_info,0, 0, 0};

/*
 *	Make the PIT interrupt at the current
 *	clock frequency.
 */
void clockpit_setup(
	mach_clock_t	clock)
{
	unsigned int	pitval;
	unsigned int	frequency;

	/*
	 *	Set the new counter value in the clock chip.
	 */
	frequency = NANOSEC_PER_SEC/clock->resolution;

	pitval = CLKNUM/frequency;
	outb(PITCTL_PORT,  PIT_C0|PIT_SQUAREMODE|PIT_READMODE);
	outb(PITCTR0_PORT, pitval);
	outb(PITCTR0_PORT, pitval>>8);
}

boolean_t clockpitprobe(
	vm_offset_t		port,
	struct bus_device 	*dev)
{
	int	unit = dev->unit;

	if (unit < 0 || unit >= NCLOCKPIT)
	    return FALSE;

	/*
	 *	Always have one.
	 */
	return TRUE;
}

void clockpitattach(
	struct bus_device	*dev)
{
	int		unit = dev->unit;
	mach_clock_t	clock;

	clockpit_info[unit] = dev;

	clock = &clockpit[unit];
	clock->resolution = CLOCKPIT_DEFAULT_RESOLUTION;
	clock->best_resolution = CLOCKPIT_MIN_RESOLUTION;
	clock->periodic = TRUE;
	clock->can_time = TRUE;
	clock->name = "clockpit";
	clock->ops = &clockpit_ops;

	printf(", resolution = %u nsecs", clock->resolution);

	clock_add(clock);
	clockpit_setup(clock);

	take_dev_irq(dev);
}

kern_return_t clockpit_set_resolution(
	mach_clock_t	clock,
	unsigned int	*resolution,	/* in/out */
	int		*skew)		/* in/out */
{
	unsigned int	c_frequency;
	unsigned int	c_skew;
	spl_t		s;

	if (*resolution < CLOCKPIT_MIN_RESOLUTION ||
	    *resolution > CLOCKPIT_MAX_RESOLUTION)
	{
	    return KERN_INVALID_ARGUMENT;
	}
			
	c_frequency = NANOSEC_PER_SEC/(*resolution);	/* is comment! */
	c_skew = CLOCKPIT_SKEW(*resolution);
			
	if (c_skew > *skew)
	    return KERN_INVALID_ARGUMENT;

	s = splsched();
	clock_queue_lock(clock);

	clock->new_resolution = *resolution - c_skew;
	clock->new_skew = *skew + c_skew;	/* ? */

	clock_queue_unlock(clock);
	splx(s);
	return D_SUCCESS;
}

void clockpit_change_resolution(
	mach_clock_t	clock)
{
	unsigned int	pitval;
	unsigned int	frequency;

	/*
	 *	Set the new resolution.
	 */
	clock->resolution = clock->new_resolution;
	clock->skew	  = clock->new_skew;

	/*
	 *	Set the new counter value in the clock chip.
	 */
	clockpit_setup(clock);
}

void clockpitintr(
	int		unit,
	struct int_frame int_frame)
{
#ifdef	PS2
	outb(0x61, inb(0x61) | 0x80);	/* reset clock interrupt */
#endif
	clock_interrupt(&clockpit[0], USERMODE(int_frame));
}
