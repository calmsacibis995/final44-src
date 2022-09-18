/* 
 * Mach Operating System
 * Copyright (c) 1991 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	clock.c,v $
 * Revision 2.6  93/05/15  18:58:08  mrt
 * 	machparam.h -> machspl.h
 * 
 * Revision 2.5  91/06/20  11:29:45  rvb
 * 	funny thing: before you could not build STD+BI because ka650.h was necessary to define ssc
 * 
 * Revision 2.4  91/06/19  12:00:08  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:57:41  rvb]
 * 
 * 	Support for VaxStation 3100: like Cvax II
 * 	[91/06/04            rvb]
 * 
 * Revision 2.3  91/05/08  13:14:21  dbg
 * 	Include vax/machparam.h for SPL definitions.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.2  90/01/11  11:44:58  dbg
 * 	Fix conditional for VAX820.  Change VAX650 conditionals
 * 	governing interval timer code to check VAX6200 also.
 * 	[89/11/21            dbg]
 * 
 * Revision 2.1  89/08/03  16:23:20  rwd
 * Created.
 * 
 * 21-Feb-89  David Golub (dbg) at Carnegie-Mellon University
 *	Re-added inittodr, resettodr.
 *
 * 11-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	Removed all but startrtclock; added microtime.
 *
 * 11-Dec-87  Stephen Schwab (schwab) at Carnegie-Mellon University
 *	For 650, use ssc timer 0 vs uVax clock
 *
 * 24-Oct-87  Stephen Schwab (schwab) at Carnegie-Mellon Universit
 *      Changes for VAX650.
 *
 * 19-May-87  Mike Accetta (mja) and David Golub (dbg)
 *				     at Carnegie-Mellon University
 *	Added special case code to adjust for lack of TODR on
 *	8800.
 *
 * 30-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed Ultrix watch_chip code.
 *
 * 19-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Eliminated CS_NEWCPU and replaced with 820 or 630.
 *
 * 11-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	Use new routines to read/write rotated watch chip for 8200.
 *
 * 20-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Generalized clock access routines so they can be used with 8200
 *	(and with future DEC products with the "watch chip").
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 */
 
#include <platforms.h>

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)clock.c	7.1 (Berkeley) 6/5/86
 */

#include <kern/time_out.h>

#include <sys/time.h>
#include <sys/tm.h>

#include <vax/machspl.h>
#include <vax/mtpr.h>
#include <vax/clock.h>
#include <vax/cpu_data.h>

#ifdef	VAX630
#include <vax/ka630.h>
#endif	VAX630
#ifdef	VAX650
#include <vax/ka650.h>
#endif	VAX650
#ifdef	VAX6200
#include <vax/ka6200.h>
#endif	VAX6200
#if	defined(VAX820) || defined(VAX3100)
#include <vax/watch_chip.h>
#endif	defined(VAX820) || defined(VAX3100)

/*
 * Machine-dependent clock routines.
 *
 * Startrtclock restarts the real-time clock, which provides
 * hardclock interrupts to kern_clock.c.
 *
 */

/*
 * Start the real-time clock.
 */
startrtclock()
{
#if	defined(VAX630) || defined(VAX3100)
	if (cpu == VAX_630 || cpu == VAX_3100) {
		mtpr(ICCS, ICCS_IE);
	}
	else
#endif	defined(VAX630) || defined(VAX3100)
#ifdef	VAX650
 	if (cpu == VAX_650) {
 		ssc->ssc_tnir0 = -1000000/hz;
 		ssc->ssc_tcr0=(ICCS_RUN+ICCS_IE+ICCS_TRANS+ICCS_INT+ICCS_ERR);
 	}
	else
#endif	VAX650
#ifdef	VAX6200
 	if (cpu == VAX_6200) {
 		ka62a_ssc->ssc_tnir0 = -1000000/hz;
 		ka62a_ssc->ssc_tcr0=(ICCS_RUN+ICCS_IE+ICCS_TRANS+ICCS_INT+ICCS_ERR);
 	}
	else
#endif	VAX6200
	{
		mtpr(NICR, -1000000/hz);
		mtpr(ICCS, ICCS_RUN+ICCS_IE+ICCS_TRANS+ICCS_INT+ICCS_ERR);
	}
}

/*
 * Return the best possible estimate of the time in the timeval
 * to which tvp points.  We do this by reading the interval count
 * register to determine the time remaining to the next clock tick.
 * We must compensate for wraparound which is not yet reflected in the time
 * (which happens when the ICR hits 0 and wraps after the splhigh(),
 * but before the mfpr(ICR)).  Also check that this time is no less than
 * any previously-reported time, which could happen around the time
 * of a clock adjustment.  Just for fun, we guarantee that the time
 * will be greater than the value obtained by a previous call.
 */
void microtime(tvp)
	register time_value_t *tvp;
{
	int s = splhigh();
	static time_value_t lasttime;
	register long t;

	*tvp = time;
#ifdef	VAX650
 	if (cpu == VAX_650) {
 		t = ssc->ssc_tir0;
 		if (t < -tick / 2 && (ssc->ssc_tcr0 & ICCS_INT))
 			t += tick;
	}
	else
#endif	VAX650
#ifdef	VAX6200
 	if (cpu == VAX_6200) {
 		t = ka62a_ssc->ssc_tir0;
 		if (t < -tick / 2 && (ka62a_ssc->ssc_tcr0 & ICCS_INT))
 			t += tick;
	}
	else
#endif	VAX6200
	{
		t =  mfpr(ICR);
		if (t < -tick / 2 && (mfpr(ICCS) & ICCS_INT))
			t += tick;
	}
	time_value_add_usec(tvp, tick + t);

	if (tvp->seconds == lasttime.seconds &&
	    tvp->microseconds <= lasttime.microseconds &&
	    (tvp->microseconds = lasttime.microseconds + 1) >= 1000000) {
		tvp->seconds++;
		tvp->microseconds -= 1000000;
	}
	lasttime = *tvp;
	splx(s);
}

/*
 * Initialize the time from whatever hardware there is.
 */
void
inittodr()
{
	time_value_t	new_time;

	new_time.seconds = 0;
	new_time.microseconds = 0;

	switch (cpu) {
#if VAX630
	    /*
	     * Get the time from the watch chip.  Set the year to
	     * 1982 if it is too early.
	     */
	    case VAX_630:
	    {
		struct tm	tm;
		watch_chip_read_normal((struct watch_chip *)cldevice, &tm);
		if (tm.tm_year < 80)
		    tm.tm_year = 82;
		new_time.seconds = convert_tm(&tm);
		break;
	    }
#endif
#if VAX820
	    /*
	     * Get the time from the watch chip.  Set the year to
	     * 1982 if it is too early.
	     */
	    case VAX_820:
	    {
		struct tm	tm;
		watch_chip_read_rotated(watch_chip, &tm);
		if (tm.tm_year < 80)
		    tm.tm_year = 82;
		new_time.seconds = convert_tm(&tm);
		break;
	    }
#endif
#if VAX3100
	    /*
	     * Get the time from the watch chip.  Set the year to
	     * 1982 if it is too early.
	     */
	    case VAX_3100:
	    {
		struct tm	tm;
		watch_chip_read_shifted((struct watch_chip_3100 *)watch_chip, &tm);
		if (tm.tm_year < 80)
		    tm.tm_year = 82;
		new_time.seconds = convert_tm(&tm);
		break;
	    }
#endif
#if VAX8800
	    case VAX_8800:
	    {
		/*
		 * Stupid machine does not have ANY todr!
		 */
		break;
	    }
#endif
	    default:
	    {
		register unsigned int	todr;

		todr = mfpr(TODR);
		if (todr >= TODRZERO) {
		    /*
		     * Set the year to 1982 to show that year
		     * is unknown.
		     */
		    new_time.seconds = (todr - TODRZERO) / 100
					+ (1982-1970)*SECYR
					+ 3 * SECDAY;
					/* 3 leap years */
		    new_time.microseconds = todr % 100;
		}
	    }
	}

	/*
	 * Set the time.
	 */
	{
	    int s = splhigh();
	    time = new_time;
	    splx(s);
	}
}

/*
 * Set the time-of-day hardware.
 */
void
resettodr()
{
	switch (cpu) {
#if VAX630
	    case VAX_630:
	    {
		struct tm	tm;

		convert_sec(time.seconds, &tm);
		watch_chip_write_normal((struct watch_chip *)cldevice, &tm);
		break;
	    }
#endif
#if VAX820
	    case VAX_820:
	    {
		struct tm	tm;

		convert_sec(time.seconds, &tm);
		watch_chip_write_rotated(watch_chip, &tm);
		break;
	    }
#endif
#if VAX3100
	    case VAX_3100:
	    {
		struct tm	tm;

		convert_sec(time.seconds, &tm);
		watch_chip_write_shifted((struct watch_chip_3100 *)watch_chip, &tm);
		break;
	    }
#endif
#if VAX8800
	    case VAX_8800:
		break;	/* no TODR */
#endif
	    default:
	    {
		/*
		 * Strip off the year.
		 */
		register unsigned int yrtime = time.seconds;
		register unsigned int secyr;
		register int year = 1970;

		for (;;) {
		    secyr = SECYR;
		    if (LEAPYEAR(year))
			secyr += SECDAY;
		    if (yrtime < secyr)
			break;
		    yrtime -= secyr;
		    year++;
		}
		mtpr(TODR, yrtime * 100 + TODRZERO);
		break;
	    }
	}
}
