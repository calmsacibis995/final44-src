/* 
 * Mach Operating System
 * Copyright (c) 1994,1993,1992,1991 Carnegie Mellon University
 * Copyright (c) 1991 Sequent Computer Systems
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON AND SEQUENT COMPUTER SYSTEMS ALLOW FREE USE OF
 * THIS SOFTWARE IN ITS "AS IS" CONDITION.  CARNEGIE MELLON AND
 * SEQUENT COMPUTER SYSTEMS DISCLAIM ANY LIABILITY OF ANY KIND FOR
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
 * $Log:	clock.c,v $
 * Revision 2.5  94/12/16  11:33:37  dbg
 * 	RT merge.  Split machine clock into two "clock" objects:
 * 	the interrupt clock and the time-of-"day" (century?)
 * 	clock.  Moved the hardclock interrupt routine here,
 * 	since it needs the clock as an argument.
 * 	[94/06/07            dbg]
 * 
 * 	Renamed 'time_spec' to 'timespec'.
 * 	[94/05/24            dbg]
 * 
 * Revision 2.4  93/11/17  18:45:58  dbg
 * 	Added clock device code for new real-time clocks.  Clock rate is
 * 	(currently) fixed.
 * 	[93/04/16            dbg]
 * 
 * Revision 2.3  91/07/31  18:00:21  dbg
 * 	Changed copyright.
 * 	[91/07/31            dbg]
 * 
 * Revision 2.2  91/05/08  12:55:04  dbg
 * 	Adapted from Sequent Symmetry sources.
 * 	[91/04/26  14:50:24  dbg]
 * 
 */

#ifndef	lint
static	char	rcsid[] = "$Header: clock.c,v 2.5 94/12/16 11:33:37 dbg Exp $";
#endif

/*
 * Machine-dependent clock routines.
 *
 * Included are the time-of-day clock initialization and
 * the per processor real-time clock initialization.
 */

/*
 * Revision 1.2  89/07/20  18:05:38  kak
 * moved balance includes
 * 
 * Revision 1.1  89/07/05  13:15:27  kak
 * Initial revision
 * 
 */

#include <mach/boolean.h>
#include <mach/timespec.h>

#include <kern/assert.h>
#include <kern/cpu_number.h>
#include <kern/kern_io.h>
#include <kern/mach_clock.h>

#include <i386/int_frame.h>
#include <i386/machspl.h>

#include <sqt/cfg.h>
#include <sqt/clock.h>
#include <sqt/slic.h>

#include <sqt/ioconf.h>
#include <sqt/vm_defs.h>
#include <sqt/hwparam.h>
#include <sqt/intctl.h>

#include <sqtsec/sec.h>

/*
 *	The system clock interrupts at "HZ" (100/sec),
 *	and counts time from 0 at system boot.
 */

#define CLOCKSQT_DEFAULT_RESOLUTION	(NANOSEC_PER_SEC/HZ)	/* 100 hz */

mach_clock_data_t	clocksqt;

/*
 * clocksqt_enable_interrupts restarts the real-time clock, which provides
 * hardclock interrupts to kern_clock.c.  On Sequent HW, this
 * is one-time only per processor (eg, no restart, clock reprimes
 * itself).
 *
 * Called by localinit() during selfinit().
 * This turns on the processor-local SLIC timer.
 *
 * For testing/performance measurement convenience, enable_local_clock
 * allows the per-processor clock to be left OFF.  Need to patch the
 * kernel binary or system memory to effect this.
 */
static	boolean_t	enable_local_clock = TRUE;	/* default ON */

void clocksqt_enable_interrupts(
	mach_clock_t	clock,
	boolean_t	on)
{
	struct cpuslic *sl = va_slic;
	spl_t	s;

	if (!enable_local_clock)
		return;

	/*
	 * Stop updates while we fix it 
	 */
	s = splhi();

	sl->sl_trv = ((sys_clock_rate * 1000000) / (SL_TIMERDIV * HZ)) - 1;
	/* clear prescaler, load reload value */
	sl->sl_tcont = 0;
	if (on)
	    sl->sl_tctl = SL_TIMERINT | LCLKBIN;
						/* timer on in given bin */
	else
	    sl->sl_tctl = 0;			/* timer off */

	splx(s);
}

struct clock_ops	clocksqt_ops = {
	0,			/* set_time */
	0,			/* set_resolution */
	0,			/* set_timeout */
	0,			/* update */
	0,			/* change_resolution */
	0,			/* stop */
	0,			/* start */
	clocksqt_enable_interrupts
};

void tod_clock_init(void);	/* forward */

/*
 *	Initialize system clock.
 */
void clocksqt_init(void)
{
	mach_clock_t	clock;

	clock = &clocksqt;

	clock->resolution = CLOCKSQT_DEFAULT_RESOLUTION;	/* @100 hz */
	clock->best_resolution = clock->resolution;
	clock->periodic = TRUE;
	clock->can_time = TRUE;
	clock->ops = &clocksqt_ops;
	clock->name = "clock";

	(void) clock_add(clock);

	tod_clock_init();
}

/*
 *	Clock interrupt routine.
 */
void hardclock(
	int	bin_number,
	struct int_frame int_frame)
{
	if (cpu_number() == master_cpu)
	    clock_interrupt(&clocksqt, USERMODE(int_frame));
	else
	    system_clock_interrupt(USERMODE(int_frame));
}

/*
 * Routines to manipulate the SCED based time-of-day register.
 * TOD clock interrupt handling done by todclock in kern_clock.c
 *
 *
 * Inittodr initializes the time-of-day hardware which provides
 * date functions. This starts the time-of-day clock.
 *
 */

extern u_char	cons_scsi;		/* console scsi slic address */

/* For time-of-day handling */
struct	sec_cib *todcib;
struct	sec_gmode todgm;	/* getmodes command */
struct	sec_smode todsm;	/* setmodes command */

/*
 *	The time-of-day clock does not interrupt,
 *	and counts time from the start of the Epoch:
 *	January 1, 1970, midnight GMT.
 */
mach_clock_t	sqt_tod_clock;

timespec_t tod_clock_read(void)
{
	timespec_t todr = { 0, 0 };
	register struct	sec_gmode *todgmptr = &todgm;
	register int i;
	spl_t s_ipl;

	if (todcib == 0) {
		printf("todcib null - inittodr returning!\n");
		return todr;
	}

	/*
	 * Find console SCED and check if the TOD clock has
	 * failed powerup diagnostics.
	 */
	for (i = 0; i < NSEC; i++) {
		/* is SEC there? */
		if ((SECvec & (1 << i)) == 0)
			continue;

		if (SEC_desc[i].sec_is_cons)
			break;
	}
	if (SEC_desc[i].sec_diag_flags & CFG_S_TOD) {
		/*
		 * Clear todr if TOD failed powerup diagnostics.
		 */
		printf("WARNING: TOD failed powerup diagnostics\n");
	} else {
		/*
		 * get the current time-of-day from the SCED tod clock.
		 */
		todgmptr->gm_status = 0;
		todcib->cib_inst = SINST_GETMODE;
		todcib->cib_status = KVTOPHYS(&todgm, int *);
		s_ipl = splhi();
		mIntr(cons_scsi, TODCLKBIN, SDEV_TOD);
		splx(s_ipl);

		while ((todgmptr->gm_status & SINST_INSDONE) == 0)
			continue;

		if (todgmptr->gm_status != SINST_INSDONE)
			panic("Cannot get TOD value");

		todr.seconds = todgmptr->gm_un.gm_tod.tod_newtime;
	}

	if (todr.seconds < 13*SECYR) {
		printf("WARNING: TOD value bad -- ");
		printf("Setting TOD to default time\n");
		todr.seconds = 13*SECYR + 19*SECDAY + (2*SECDAY)/3;
	}

	/*
	 * Return the time.
	 */

	return todr;
}

/*
 *	Set TOD clock from clock.
 */
kern_return_t tod_clock_set_time(
	mach_clock_t	clock,
	timespec_t	*new_time)
{
	register struct sec_smode *todsmptr = &todsm;
	spl_t s_ipl;

	/*
	 *	Update hardware, to nearest second
	 */
	todsmptr->sm_status = 0;
	todsmptr->sm_un.sm_tod.tod_freq = TODFREQ;
	todcib->cib_inst = SINST_SETMODE;
	todcib->cib_status = KVTOPHYS(&todsm, int *);

	s_ipl = splhi();
	todsmptr->sm_un.sm_tod.tod_newtime = new_time->seconds;

	/*
	 * Bin 3 is sufficient, helps avoid SLIC-bus lockup.
	 */
	mIntr(cons_scsi, 3, SDEV_TOD);
	splx(s_ipl);

	while ((todsmptr->sm_status & SINST_INSDONE) == 0)
		continue;

	if (todsmptr->sm_status != SINST_INSDONE)
		panic("Cannot set TOD value");

	return KERN_SUCCESS;
}

/*
 *	Initialize the time-of-day clock.
 */
void tod_clock_init(void)
{
	tod_clock_attach(tod_clock_read(), tod_clock_set_time);
}

