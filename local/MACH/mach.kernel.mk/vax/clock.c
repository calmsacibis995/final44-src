/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	clock.c,v $
 * Revision 2.6  89/02/25  20:11:50  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  88/10/11  13:00:37  rpd
 * 	VAX6200: Try ssc timer chip.
 * 	[88/10/08            rvb]
 * 
 * Revision 2.4  88/08/23  23:04:03  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Fix the time-of-day clock reading on MicroVaxen.  [Fix found by
 * 	rvb, related to mrt, dumped on me.]
 * 	[88/08/23            mwyoung]
 * 
 * Revision 2.3  88/08/10  10:14:10  rvb
 * Conditionalize properly for only BI vaxen.
 * Treat 6200 like a 630 for now (vs 650).
 * 
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
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)clock.c	7.1 (Berkeley) 6/5/86
 */
 
#include <cputypes.h>

#include <sys/param.h>
#include <sys/time.h>
#include <sys/kernel.h>

#include <vax/mtpr.h>
#include <vax/clock.h>
#include <vax/cpu.h>

#if	VAX820 || VAX630 
#include <vax/watch_chip.h>

#endif	VAX820 || VAX630
 
#if	VAX650
#include <vax/ka650.h>
#endif	VAX650

#if	VAX6200
#include <vaxnb/ka62a.h>
#endif	VAX6200
/*
 * Machine-dependent clock routines.
 *
 * Startrtclock restarts the real-time clock, which provides
 * hardclock interrupts to kern_clock.c.
 *
 * Inittodr initializes the time of day hardware which provides
 * date functions.  Its primary function is to use some file
 * system information in case the hardare clock lost state.
 *
 * Resettodr restores the time of day hardware after a time change.
 */

/*
 * Start the real-time clock.
 */
#if	VAX650 || VAX6200
struct ssclock *ssclock;
#endif	VAX650 || VAX6200
startrtclock()
{
	switch(cpu) {
#if	VAX630 
	case VAX_630:
		mtpr(ICCS, ICCS_IE);
		break;
#endif	VAX630
#if	VAX650
	case VAX_650:
		ssclock = (struct ssclock *) ssc;
 		ssclock->ssc_tnir0 = -1000000/hz;
 		ssclock->ssc_tcr0=(ICCS_RUN+ICCS_IE+ICCS_TRANS+ICCS_INT+ICCS_ERR);
		break;
#endif	VAX650
#if	VAX6200
	case VAX_6200:
/*		mtpr(ICCS, ICCS_IE);*/
		ssclock = (struct ssclock *) ka62a_ssc;
 		ssclock->ssc_tnir0 = -1000000/hz;
 		ssclock->ssc_tcr0=(ICCS_RUN+ICCS_IE+ICCS_TRANS+ICCS_INT+ICCS_ERR);
		break;
#endif	VAX6200
	default:
		mtpr(NICR, -1000000/hz);
		mtpr(ICCS, ICCS_RUN+ICCS_IE+ICCS_TRANS+ICCS_INT+ICCS_ERR);
		break;
	}
}

/*
 * Initialze the time of day register, based on the time base which is, e.g.
 * from a filesystem.  Base provides the time to within six months,
 * and the time of year clock provides the rest.
 */
inittodr(base)
	time_t base;
{
	register u_int todr;
	long deltat;
	int year = YRREF;
#if	VAX630 || VAX820
	struct tm	tm;
#endif	VAX630 || VAX820 

	switch (cpu) {
#if	VAX630
	/*
	 * If this is a VAX630, call ka630tod to handle the funny tod clock.
	 */
	case VAX_630:
		watch_chip_read_normal(watch_chip, &tm);
		todr = convert_tm(&tm);
		todr = (todr*100) + TODRZERO;	/* make it look like other Vaxes */
		break;
#endif	VAX630 
#if	VAX820
	case VAX_820:
		watch_chip_read_rotated(watch_chip, &tm);
		todr = convert_tm(&tm);
		todr = (todr*100) + TODRZERO;	/* make it look like other Vaxes */
		break;
#endif	VAX820
#if	VAX8800
	case VAX_8800:
		todr = 0;
		break;
#endif	VAX8800
	default:
		todr = mfpr(TODR);
	}
	if (base < 5*SECYR) {
		printf("WARNING: preposterous time in file system");
		time.tv_sec = 6*SECYR + 186*SECDAY + SECDAY/2;
		resettodr();
		goto check;
	}
	/*
	 * TODRZERO is base used by VMS, which runs on local time.
	 */
	if (todr < TODRZERO) {
#if	VAX1
		if(cpu == VAX_1)
			printf("WARNING: no clock");
		else
#endif	VAX1
		printf("WARNING: todr too small");
		time.tv_sec = base;
		/*
		 * Believe the time in the file system for lack of
		 * anything better, resetting the TODR.
		 */
		resettodr();
		goto check;
	}

	/*
	 * Sneak to within 6 month of the time in the filesystem,
	 * by starting with the time of the year suggested by the TODR,
	 * and advancing through succesive years.  Adding the number of
	 * seconds in the current year takes us to the end of the current year
	 * and then around into the next year to the same position.
	 */
	time.tv_sec = (todr-TODRZERO)/100;
	while (time.tv_sec < base-SECYR/2) {
		if (LEAPYEAR(year))
			time.tv_sec += SECDAY;
		year++;
		time.tv_sec += SECYR;
	}

	/*
	 * See if we gained/lost two or more days;
	 * if so, assume something is amiss.
	 */
	deltat = time.tv_sec - base;
	if (deltat < 0)
		deltat = -deltat;
	if (deltat < 2*SECDAY)
		return;
	printf("WARNING: clock %s %d days",
	    time.tv_sec < base ? "lost" : "gained", deltat / SECDAY);
check:
	printf(" -- CHECK AND RESET THE DATE!\n");
}

/*
 * Reset the TODR based on the time value; used when the TODR
 * has a preposterous value and also when the time is reset
 * by the stime system call.  Also called when the TODR goes past
 * TODRZERO + 100*(SECYEAR+2*SECDAY) (e.g. on Jan 2 just after midnight)
 * to wrap the TODR around.
 */
resettodr()
{
	int year = YRREF;
	u_int secyr;
	u_int yrtime = time.tv_sec;
#if	VAX630 || VAX820
	struct tm	tm;
#endif	VAX630 || VAX820

	/*
	 * Whittle the time down to an offset in the current year,
	 * by subtracting off whole years as long as possible.
	 */
	for (;;) {
		secyr = SECYR;
		if (LEAPYEAR(year))
			secyr += SECDAY;
		if (yrtime < secyr)
			break;
		yrtime -= secyr;
		year++;
	}
	switch (cpu) {
#if	VAX630
	case VAX_630:
		convert_sec(yrtime, &tm);
		watch_chip_write_normal(watch_chip, &tm);
		break;
#endif	VAX630
#if	VAX820
	case VAX_820:
		convert_sec(yrtime, &tm);
		watch_chip_write_rotated(watch_chip, &tm);
		break;
#endif	VAX820
#if	VAX8800
	case VAX_8800:
		break;
#endif	VAX8800
	default:
		mtpr(TODR, TODRZERO + yrtime*100);
		break;
	}
}
