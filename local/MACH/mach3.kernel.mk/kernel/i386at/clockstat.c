/* 
 * Mach Operating System
 * Copyright (c) 1994,1993 Carnegie Mellon University
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
 * $Log:	clockstat.c,v $
 * Revision 2.2  94/12/15  15:30:43  dbg
 * 	Merged into Mach mainline.  Changed 48-bit-integer
 * 	conversion routine to use i386 assembler, so that it
 * 	can use the long divide instruction (64/32->32+32 bits).
 * 	[94/06/01            dbg]
 * 
 * 	 Re-wrote timeout mechanism to use 32 bits worth of timer
 * 	 instead of 16 bits (by counting up from complement of delay)
 * 	 also cleaned up a lot of other cruft here and there.
 * 	[94/02/18            jimz]
 * 
 * 	Tore out device structure. The clockstat board will now register
 * 	itself as a first-class aperiodic clock. This is part of the
 * 	larger clock/timer rewrite.
 * 	[94/03/15            jimz]
 * 
 * 	Added support for units > 0, units > 0 will not support
 * 	interrupt timers, but will instead time at 250ns instead
 * 	of 1us. Stripped out historic debugging cruft.
 * 	[94/03/27            jimz]
 * 
 * 	Created
 * 	[93/06/22            savage]
 * 
 */
#include <clockstat.h>

#include <mach/std_types.h>

#include <kern/mach_clock.h>
#include <vm/vm_kern.h>
#include <chips/busses.h>
#include <device/device_types.h>

#include <i386/int_frame.h>
#include <i386/machspl.h>
#include <i386/pio.h>
#include <i386at/clockstat.h>

/*
 *	Divide 64-bit dividend by 32-bit divisor,
 *	producing a 32-bit quotient and a 32-bit
 *	remainder.  Assumes that the division
 *	does not overflow.
 */
void long_divide(
	unsigned int	dividend_low,
	unsigned int	dividend_high,
	unsigned int	divisor,
	unsigned int	*quotient,
	unsigned int	*remainder)
{
	unsigned int	quo, rem;

	asm("divl %4, %%eax"
	    : "=a" (quo), "=d" (rem)
	    : "0" (dividend_low), "1" (dividend_high),
	      "rm" (quotient));

	*quotient = quo;
	*remainder = rem;
}


void clockstat_update(
	mach_clock_t clock);
void clockstat_timeout(
	mach_clock_t clock);
void clockstat_stop(
	mach_clock_t clock);
void clockstat_start(
	mach_clock_t clock);

struct clock_ops	clockstat_ops = {
	0,			/* set_time */
	0,			/* set_resolution */
	clockstat_timeout,
	clockstat_update,
	0,			/* change_resolution */
	clockstat_stop,
	clockstat_start,
	0			/* enable_interrupts */
};

boolean_t clockstatprobe(
	vm_offset_t		port,
	struct bus_device 	*dev);
void clockstatattach(
	struct bus_device	*dev);

/*
 *	The 'data' field points to clockstat_info[unit],
 *	to allow accessing the hardware structure given
 *	the clock.
 */
mach_clock_data_t	clockstat[NCLOCKSTAT];

vm_offset_t		clockstat_std[] = { 0 };
struct bus_device *	clockstat_info[NCLOCKSTAT];
struct bus_driver	clockstatdriver = {
	clockstatprobe, 0, clockstatattach, 0,
	clockstat_std, "clockstat", clockstat_info,0, 0, 0};

int clockstat_debug = 0;

boolean_t clockstatprobe(
	vm_offset_t		port,
	struct bus_device 	*dev)
{
	int unit = dev->unit;
	int iobase = dev->address;

	if (unit < 0 || unit >= NCLOCKSTAT) {
	    printf("%s%d out of range\n", dev->name,unit);
	    return FALSE;
	}

   	/* Disable interrupts from board */
	outb(STAT_INTERRUPT_PORT(iobase), STAT_INT_INT_DISABLE); 

	/* Master reset */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_RESET);

	/* Init pointer */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_INITPTR);

	/* Check out mode register of timer 1 */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_MODE | TG1);

	/* Is it set at default? */
	if (inw(STAT_DATA_PORT(iobase)) != STAT_TIMER_SOURCE_F1)
	    return FALSE;

	return TRUE;
}

void clockstatattach(
	struct bus_device	*dev)
{
	vm_offset_t	iobase = dev->address;
	int		unit = dev->unit;
	mach_clock_t	clock;

	take_dev_irq(dev);

	clockstat_info[unit] = dev;

	clock = &clockstat[unit];
	clock->data = (void *)dev;

	if (unit == 0) {
	    clock->resolution = CLOCKSTAT_DEFAULT_RESOLUTION;
	    clock->can_time = TRUE;
	    clock->name = "clockstat0";
	}
	else {
	    clock->resolution = 250;
	    clock->can_time = FALSE;
	    clock->name = "clockstat1";		/* KNOWN to be 2 at most! */
	}

	clock->best_resolution = clock->resolution;
	clock->periodic = FALSE;
	clock->ops = &clockstat_ops;

	/* Set F6 to count at 1us and enable AL2 */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_MASTER);

	if (unit == 0) {
		/*
		 * We can go for almost a decade before
		 * the clock rolls over. Somehow, I`m
		 * not worried.
		 */
		outw(STAT_DATA_PORT(iobase),
		    	 STAT_MSTR_SCALE_BIN |
		    	 STAT_MSTR_DPTR_INIT |
			     STAT_MSTR_F6_ENABLE |
			     STAT_MSTR_F6SCALE_04 |
	    		 STAT_MSTR_F6SOURCE_F1);
	}
	else {
		/*
		 * We`re good for > 2 years before rollover
		 * with 48 bits of clock.
		 */
		outw(STAT_DATA_PORT(iobase),
		    	 STAT_MSTR_SCALE_BIN |
		    	 STAT_MSTR_DPTR_INIT |
			     STAT_MSTR_F6_ENABLE |
			     STAT_MSTR_F6SCALE_01 |
	    		 STAT_MSTR_F6SOURCE_F1);
	}

	/*
	 *	Elapsed timers
	 */
	/* Set T3 to count up repeatedly driven by F6 */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_MODE | TG3);
	outw(STAT_DATA_PORT(iobase),
	     STAT_TIMER_SOURCE_F6 |
	     STAT_TIMER_CYCLE_REPEAT |
	     STAT_TIMER_DIR_UP);

	/* Zero T3 */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_LOAD | TG3);
	outw(STAT_DATA_PORT(iobase), 0x00); 

	/* Set T4 to count up repeatedly driven by T3 */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_MODE | TG4);
	outw(STAT_DATA_PORT(iobase),
	     STAT_TIMER_SOURCE_TNM1 |
	     STAT_TIMER_CYCLE_REPEAT |
	     STAT_TIMER_DIR_UP);

	/* Zero T4 */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_LOAD | TG4);
	outw(STAT_DATA_PORT(iobase), 0x00); 

	/* Set T5 to count up repeatedly driven by T4 */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_MODE | TG5);
	outw(STAT_DATA_PORT(iobase),
	     STAT_TIMER_SOURCE_TNM1 |
	     STAT_TIMER_CYCLE_REPEAT |
	     STAT_TIMER_DIR_UP);

	/* Zero T5 */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_LOAD | TG5);
	outw(STAT_DATA_PORT(iobase), 0x00); 

	/* Load timers */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADTIMERS | TF3 | TF4 | TF5);

	/* Arm timers */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_ARMTIMERS | TF3 | TF4 | TF5);

	/*
	 *	Interrupting timers
	 */
	/* Clear output */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_CLEAROUTPUT | TG2);

	/* Set T1 to count up repeatedly driven by F6 */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_MODE | TG1);
	outw(STAT_DATA_PORT(iobase),
	     STAT_TIMER_SOURCE_F6 |
	     STAT_TIMER_CYCLE_REPEAT |
	     STAT_TIMER_DIR_UP);

	/* Set T2 to count up once driven by T1 */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_MODE | TG2);
	outw(STAT_DATA_PORT(iobase),
	     STAT_TIMER_SOURCE_TNM1 |
	     STAT_TIMER_CYCLE_ONCE |
	     STAT_TIMER_DIR_UP |
	     STAT_TIMER_OUT_TOGGLE);

	/* Zero T1 */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_LOAD | TG1);
	outw(STAT_DATA_PORT(iobase), 0x00); 

	/* Zero T2 */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_LOAD | TG2);
	outw(STAT_DATA_PORT(iobase), 0x00); 

	/* Load timers */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADTIMERS | TF1 | TF2);

	/* Arm timers */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_ARMTIMERS | TF1 | TF2);

	/* Enable interrupts */
	outb(STAT_INTERRUPT_PORT(iobase), STAT_INT_INT_ENABLE | TG2);

	printf(", time = %u secs : %u nsecs, resolution = %u nsecs",
	       0,
	       0,
	       clock->resolution);

	dev->alive = 1;

	clock_add(clock);
}

void clockstat_stop(
	mach_clock_t clock)
{
	int iobase = ((struct bus_device *)clock->data)->address;

	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_DISARMTIMERS | TF3);
}

void clockstat_start(
	mach_clock_t clock)
{
	int iobase = ((struct bus_device *)clock->data)->address;

	/* Set T3 to count up repeatedly driven by F6 */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_MODE | TG3);
	outw(STAT_DATA_PORT(iobase),
	     STAT_TIMER_SOURCE_F6 |
	     STAT_TIMER_CYCLE_REPEAT |
	     STAT_TIMER_DIR_UP);

	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_ARMTIMERS | TF3);
}

static timespec_t clockstat_get_time(
	mach_clock_t	clock)
{
	int		iobase = ((struct bus_device *)clock->data)->address;
	unsigned short	resultlo, resultmed, resulthi;
	timespec_t	tp;	

	outb(STAT_CONTROL_PORT(iobase),
	     STAT_CMD_SAVETIMERS | TF3 | TF4 | TF5);

	outb(STAT_CONTROL_PORT(iobase),
	     STAT_CMD_LOADPTR_HOLD | TG3);
	resultlo = inw(STAT_DATA_PORT(iobase));

	if (resultlo == 0)
	   outb(STAT_CONTROL_PORT(iobase),
		STAT_CMD_SAVETIMERS | TF4);

	outb(STAT_CONTROL_PORT(iobase),
	     STAT_CMD_LOADPTR_HOLD | TG4);
	resultmed = inw(STAT_DATA_PORT(iobase));

	if (resultmed == 0)
	   outb(STAT_CONTROL_PORT(iobase),
		STAT_CMD_SAVETIMERS | TF5);

	outb(STAT_CONTROL_PORT(iobase),
	     STAT_CMD_LOADPTR_HOLD | TG5);
	resulthi = inw(STAT_DATA_PORT(iobase));

    {
	unsigned int	div_low, div_high, quotient, remainder,
			divisor, nsec_multiplier;

	div_low = (((unsigned short) resultmed) << 16) |
		  (((unsigned short) resultlo) & 0xffff);
	div_high = (unsigned short) resulthi;

	if (clock->resolution == CLOCKSTAT_DEFAULT_RESOLUTION) {
	    /*
	     *	Count in 1000 ns
	     */
	    divisor = NANOSEC_PER_SEC / 1000;
	    nsec_multiplier = 1000;
	}
	else {
	    /*
	     *	Count in 250 ns
	     */
	    divisor = NANOSEC_PER_SEC / 250;
	    nsec_multiplier = 250;
	}

	long_divide(div_low, div_high, divisor, &quotient, &remainder);
	tp.seconds = quotient;
	tp.nanoseconds = remainder * nsec_multiplier;
    }
	return tp;
}

/*
 * call with clock locked
 */
void clockstat_update(
	mach_clock_t clock)
{
	timespec_t t;

	t = clockstat_get_time(clock);
	clock->check_seconds = t.seconds;
	clock->time = t;
}

int clockstatintr(
	int	unit,
	struct int_frame int_frame)
{
	mach_clock_t	clock = &clockstat[unit];
	int		iobase = ((struct bus_device *)clock->data)->address;
	spl_t		s;

	s = sploff();

	/* Clear output */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_CLEAROUTPUT | TF2);

	/* Disarm timers */
	outb(STAT_CONTROL_PORT(iobase), STAT_CMD_DISARMTIMERS | TF1 | TF2);

	splon(s);

	if (clockstat_debug)
	    printf("clockstatintr(%d) iobase = %#x\n",
		   unit, iobase);

	aperiodic_clock_interrupt(clock, USERMODE(int_frame));
}

void stat_nmi_intr(
	int	unit)
{
	vm_offset_t	iobase = clockstat_info[0]->address;	

	outb(STAT_INTERRUPT_PORT(iobase), inb(STAT_INTERRUPT_PORT(iobase)));

}

void clockstat_timeout(
	mach_clock_t clock)
{
	int		iobase = ((struct bus_device *)clock->data)->address;
	unsigned long	microseconds, countlo, countmed;
	timespec_t	current_time, newtime, time;
	unsigned short	lo, med, slo, smed;
	timer_elt_t	telt;
	queue_t		q;
	spl_t		s;

	s = sploff();
	clock_queue_lock(clock);

	CLOCK_UPDATE(clock);
	clock_read(current_time, clock);

	telt = (timer_elt_t) queue_first(&clock->head.chain);
	if (!queue_end(q, (queue_entry_t) telt)) {
	    if (timespec_le(telt->te_expire_time, current_time)) {
		ast_on(cpu_number(), AST_TIMER);
		clock_queue_unlock(clock);
		splon(s);
		return;
	    }

	    time = telt->te_expire_time;

	    if (clockstat_debug) {
		printf("time=%d:%09d now=%d:%09d\n",
			time.seconds, time.nanoseconds,
			current_time.seconds, current_time.nanoseconds);
	    }

	    timespec_subtract(time, current_time);

	    /* set time onto board */

	    /* round up to timer unit (1000 nanoseconds) */
	    if (time.nanoseconds % 1000 > 500) {
		timespec_add_nsec(time, 1000);
	    }

	    if (time.seconds >= 4293) {
		/* 32-bit arithmetic will overflow */
		microseconds = 4293000000U;
	    }
	    else {
		microseconds = time.nanoseconds / 1000;
		microseconds += time.seconds * 1000000;
	    }

#if 1
	    countlo = microseconds & 0xffff;
	    countmed = microseconds & 0xffff0000;
	    countmed >>= 16;
	    lo  = (unsigned short)(countlo&0xffff);
	    med = (unsigned short)(countmed&0xffff);
	    if (lo == 0) {
		lo = 0xffff;
		med--;
	    }
	    else {
		lo--;
	    }
	    slo = ~lo;
	    smed = ~med;
#else
	    /* isn`t this the same as... */
	    microseconds = ~microseconds + 1;	/* -microseconds, unsigned */
	    slo = microseconds & 0xffff;
	    smed = microseconds >> 16;
#endif

	    /* Disarm timers */
	    outb(STAT_CONTROL_PORT(iobase), STAT_CMD_DISARMTIMERS | TF1 | TF2);

	    /* clear outputs */
	    outb(STAT_CONTROL_PORT(iobase), STAT_CMD_CLEAROUTPUT | TF2);

	    /*
	     * note that we're loading complements
	     * this is because we're counting _up_
	     * so that we can cascade two timers together
	     * without having to use two interrupt lines
	     *
	     * we start "negative" and count up until we
	     * rollover to zero
	     */

	    /* Set T2 */
	    outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_LOAD | TF2);
	    outw(STAT_DATA_PORT(iobase), smed);

	    /* Set T1 */
	    outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_LOAD | TF1);
	    outw(STAT_DATA_PORT(iobase), slo);

	    /* Load timers T1 and T2 */
	    outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADTIMERS | TF1 | TF2);

	    /*
	     * load T1 with 0 so that on first rollover,
	     * we get 0 instead of ~lsw
	     * But, you ask, doesn't this corrupt the value _in_ T1?
	     * No, because we just loaded it. However, it will re-load
	     * every time it rolls over. So what we've just done is make
	     * it re-load with zero on each rollover.
	     */
	    outb(STAT_CONTROL_PORT(iobase), STAT_CMD_LOADPTR_LOAD | TF1);
	    outw(STAT_DATA_PORT(iobase), 0x00);

	    /* Clear output */
	    outb(STAT_CONTROL_PORT(iobase), STAT_CMD_CLEAROUTPUT | TF2);

	    /* Arm timers */
	    outb(STAT_CONTROL_PORT(iobase), STAT_CMD_ARMTIMERS | TF1 | TF2);

	    /* sanity check */
	    newtime = clockstat_get_time(clock);
	    if (timespec_ge(newtime, telt->te_expire_time)) {
		ast_on(cpu_number(), AST_TIMER);
	    }
	}

	clock_queue_unlock(clock);
	splon(s);
}

