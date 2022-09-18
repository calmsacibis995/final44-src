h64932
s 00002/00002/00205
d D 8.1 93/06/11 15:02:27 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00207
d D 7.7 93/03/09 23:53:18 utashiro 7 6
c cleanup header and machine dependency.
e
s 00009/00023/00199
d D 7.6 93/01/21 02:52:15 utashiro 6 5
c Now enableclock is not used
e
s 00005/00005/00217
d D 7.5 92/12/17 01:28:20 utashiro 5 4
c make kernel includes standard
e
s 00012/00012/00210
d D 7.4 92/12/15 18:15:42 utashiro 4 3
c Changed the order of functions.
e
s 00027/00000/00195
d D 7.3 92/07/28 17:33:43 bostic 3 2
c update from Kazumasa Utashiro
e
s 00003/00003/00192
d D 7.2 92/06/25 18:28:21 utashiro 2 1
c fixed bug in bcd_to_int macro
e
s 00195/00000/00000
d D 7.1 92/06/04 16:06:51 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 8
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department, Ralph Campbell, and Kazumasa Utashiro of
 * Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: clock.c 1.18 91/01/21$
 *
 *	%W% (Berkeley) %G%
 */

D 5
#include "../include/fix_machine_type.h"
#include "../include/adrsmap.h"
E 5
I 5
D 7
#include <machine/fix_machine_type.h>
E 7
#include <machine/adrsmap.h>
E 5

D 5
#include "param.h"
#include "kernel.h"
E 5
I 5
#include <sys/param.h>
#include <sys/kernel.h>
E 5

D 5
#include "clockreg.h"
E 5
I 5
#include <news3400/news3400/clockreg.h>
E 5

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
I 3
D 4
 * Set up the real-time and statistics clocks.  Leave stathz 0 only if
 * no alternative timer is available.
 *
 */
cpu_initclocks()
{

	startrtclock();
	enablertclock();
}

/*
E 4
 * We assume newhz is either stathz or profhz, and that neither will
 * change after being set up above.  Could recalculate intervals here
 * but that would be a drag.
 */
void
setstatclockrate(newhz)
	int newhz;
{

	/* KU:XXX do something! */
}

/*
E 3
D 6
 * Start the real-time clock.
 */
I 3
static void
E 3
startrtclock()
{

	*(char *)ITIMER = IOCLOCK / 6144 / 100 - 1;
}

/*
 * Enable the real-time clock.
 */
I 3
static void
E 3
enablertclock()
{

	*(char *)INTEN0 |= (char)INTEN0_TIMINT;
I 4
}

/*
E 6
 * Set up the real-time and statistics clocks.  Leave stathz 0 only if
 * no alternative timer is available.
D 6
 *
E 6
 */
cpu_initclocks()
{

D 6
	startrtclock();
	enablertclock();
E 6
I 6
	/*
	 * Start the real-time clock.
	 */
	*(char *)ITIMER = IOCLOCK / 6144 / 100 - 1;

	/*
	 * Enable the real-time clock.
	 */
	*(char *)INTEN0 |= (char)INTEN0_TIMINT;
E 6
E 4
}

/*
 * This code is defunct after 2099.
 * Will Unix still be here then??
 */
static short dayyr[12] = {
	0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};

D 2
#define	bcd_to_int(BCD)	(i = BCD, (((i) >> 4) & 0xf) * 10 + (i) & 0xf)
E 2
I 2
#define	bcd_to_int(BCD)	(i = BCD, (((i) >> 4) & 0xf) * 10 + ((i) & 0xf))
E 2
#define	int_to_bcd(INT)	(i = INT, ((((i) / 10) % 10) << 4) + (i) % 10)

/*
 * Initialze the time of day register, based on the time base which is, e.g.
 * from a filesystem.  Base provides the time to within six months,
 * and the time of year clock (if any) provides the rest.
 */
inittodr(base)
	time_t base;
{
	register volatile u_char *rtc_port = (u_char *)RTC_PORT;
	register volatile u_char *rtc_data = (u_char *)DATA_PORT;
	register int days, yr;
	int sec, min, hour, week, day, mon, year;
	long deltat, badbase = 0;
D 2
	register int i;
E 2
I 2
	register u_int i;
E 2

	if (base < 5*SECYR) {
		printf("WARNING: preposterous time in file system\n");
		/* read the system clock anyway */
		base = 6*SECYR + 186*SECDAY + SECDAY/2;
		badbase = 1;
	}

	*rtc_port = READ_CLOCK;
	sec  = bcd_to_int(*rtc_data++);
	min  = bcd_to_int(*rtc_data++);
	hour = bcd_to_int(*rtc_data++);
	week = bcd_to_int(*rtc_data++);
	day  = bcd_to_int(*rtc_data++);
	mon  = bcd_to_int(*rtc_data++);
	year = bcd_to_int(*rtc_data++);
	*rtc_port = 0;

	/* simple sanity checks */
	if (year < 70 || mon < 1 || mon > 12 || day < 1 || day > 31 ||
	    hour > 23 || min > 59 || sec > 59) {
D 2
		printf("WARNING: preposterous clock chip time");
E 2
I 2
		printf("WARNING: preposterous clock chip time\n");
E 2
		/*
		 * Believe the time in the file system for lack of
		 * anything better, resetting the TODR.
		 */
		time.tv_sec = base;
		if (!badbase)
			resettodr();
		return (0);
	}
	days = 0;
	for (yr = 70; yr < year; yr++)
		days += LEAPYEAR(yr) ? 366 : 365;
	days += dayyr[mon - 1] + day - 1;
	if (LEAPYEAR(yr) && mon > 2)
		days++;
	/* now have days since Jan 1, 1970; the rest is easy... */
	time.tv_sec = days * SECDAY + hour * 3600 + min * 60 + sec;

	if (!badbase) {
		/*
		 * See if we gained/lost two or more days;
		 * if so, assume something is amiss.
		 */
		deltat = time.tv_sec - base;
		if (deltat < 0)
			deltat = -deltat;
		if (deltat < 2 * SECDAY)
			return;
		printf("WARNING: clock %s %d days",
		    time.tv_sec < base ? "lost" : "gained", deltat / SECDAY);
	}
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
	register volatile u_char *rtc_port = (u_char *)RTC_PORT;
	register volatile u_char *rtc_data = (u_char *)DATA_PORT;
	int sec, min, hour, week, day, mon, year;
	register int t, t2, t3;
	register int i;

	/* compute the year */
	t2 = time.tv_sec / SECDAY;
	t = 69;
	while (t2 >= 0) {	/* whittle off years */
		t3 = t2;
		t++;
		t2 -= LEAPYEAR(t) ? 366 : 365;
	}

	year = t;

	/* t3 = month + day; separate */
	t = LEAPYEAR(t);
	for (t2 = 1; t2 < 12; t2++)
		if (t3 < dayyr[t2] + (t && t2 > 1))
			break;

	/* t2 is month */
	mon = t2;
	t3 = t3 - dayyr[t2 - 1] + 1;
	if (t && t2 > 2)
		t3--;
	day = t3;

	week = 0;

	/* the rest is easy */
	t = time.tv_sec % SECDAY;
	hour = t / 3600;
	t %= 3600;
	min = t / 60;
	sec = t % 60;

	*rtc_port = SET_CLOCK;
	*rtc_data++ = int_to_bcd(sec);
	*rtc_data++ = int_to_bcd(min);
	*rtc_data++ = int_to_bcd(hour);
	*rtc_data++ = int_to_bcd(week);
	*rtc_data++ = int_to_bcd(day);
	*rtc_data++ = int_to_bcd(mon);
	*rtc_data   = int_to_bcd(year);
	*rtc_port = 0;
}
E 1
