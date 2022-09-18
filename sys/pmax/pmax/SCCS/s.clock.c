h43735
s 00009/00003/00201
d D 8.2 94/10/09 21:09:36 mckusick 8 7
c Fix chip time to GMT convertion so PROM passes self tests and
c doesn't reset the chip time (from Ralph)
e
s 00002/00002/00202
d D 8.1 93/06/10 23:06:17 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00003/00199
d D 7.6 92/11/15 16:30:24 ralph 6 5
c updates from Rick Macklem for maxine.
e
s 00004/00004/00198
d D 7.5 92/10/11 11:23:04 bostic 5 4
c make kernel includes standard
e
s 00014/00002/00188
d D 7.4 92/09/13 11:43:43 ralph 4 3
c changes for cpu_initclocks()
e
s 00042/00033/00148
d D 7.3 92/04/19 08:56:20 ralph 3 2
c fix clock read/write for leap year and to match ULTRIX.
e
s 00007/00001/00174
d D 7.2 92/02/29 11:30:03 ralph 2 1
c block interrupts when updating the clock chip.
e
s 00175/00000/00000
d D 7.1 92/01/07 17:29:18 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: clock.c 1.18 91/01/21$
 *
 *	%W% (Berkeley) %G%
 */

D 5
#include "param.h"
#include "kernel.h"
E 5
I 5
#include <sys/param.h>
#include <sys/kernel.h>
E 5

D 5
#include "../include/machConst.h"
#include "clockreg.h"
E 5
I 5
#include <machine/machConst.h>
#include <pmax/pmax/clockreg.h>
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

I 6
volatile struct chiptime *Mach_clock_addr;

E 6
/*
D 4
 * Start the real-time clock.
E 4
I 4
 * Start the real-time and statistics clocks. Leave stathz 0 since there
 * are no other timers available.
E 4
 */
D 4
startrtclock()
E 4
I 4
cpu_initclocks()
E 4
{
	register volatile struct chiptime *c;
	extern int tickadj;

	tick = 15625;		/* number of micro-seconds between interrupts */
D 3
	hz = 1000000 / 15625;	/* about 64 */
E 3
I 3
	hz = 1000000 / 15625;	/* 64 Hz */
E 3
	tickadj = 240000 / (60000000 / 15625);
D 6
	c = (volatile struct chiptime *)MACH_CLOCK_ADDR;
E 6
I 6
	c = Mach_clock_addr;
E 6
	c->rega = REGA_TIME_BASE | SELECTED_RATE;
	c->regb = REGB_PER_INT_ENA | REGB_DATA_MODE | REGB_HOURS_FORMAT;
I 4
}

/*
 * We assume newhz is either stathz or profhz, and that neither will
 * change after being set up above.  Could recalculate intervals here
 * but that would be a drag.
 */
void
setstatclockrate(newhz)
	int newhz;
{
E 4
}

/*
I 8
 * This is the amount to add to the value stored in the clock chip
 * to get the current year.
 */
#define YR_OFFSET	22

/*
E 8
 * This code is defunct after 2099.
 * Will Unix still be here then??
 */
static short dayyr[12] = {
	0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};

/*
 * Initialze the time of day register, based on the time base which is, e.g.
 * from a filesystem.  Base provides the time to within six months,
 * and the time of year clock (if any) provides the rest.
 */
I 3
void
E 3
inittodr(base)
	time_t base;
{
	register volatile struct chiptime *c;
	register int days, yr;
	int sec, min, hour, day, mon, year;
D 3
	long deltat, badbase = 0;
	int s;
E 3
I 3
	long deltat;
	int badbase, s;
E 3

	if (base < 5*SECYR) {
D 3
		printf("WARNING: preposterous time in file system\n");
E 3
I 3
		printf("WARNING: preposterous time in file system");
E 3
		/* read the system clock anyway */
		base = 6*SECYR + 186*SECDAY + SECDAY/2;
		badbase = 1;
D 3
	}
E 3
I 3
	} else
		badbase = 0;
E 3

D 2
	s = splclock();
E 2
D 6
	c = (volatile struct chiptime *)MACH_CLOCK_ADDR;
E 6
I 6
	c = Mach_clock_addr;
E 6
	/* don't read clock registers while they are being updated */
I 2
	s = splclock();
E 2
	while ((c->rega & REGA_UIP) == 1)
		;
	sec = c->sec;
	min = c->min;
	hour = c->hour;
	day = c->day;
	mon = c->mon;
D 3
	year = c->year + 19;
E 3
I 3
D 8
	year = c->year + 20; /* must be multiple of 4 because chip knows leap */
E 8
I 8
	year = c->year + YR_OFFSET;
E 8
E 3
	splx(s);
I 2

E 2
	/* simple sanity checks */
	if (year < 70 || mon < 1 || mon > 12 || day < 1 || day > 31 ||
	    hour > 23 || min > 59 || sec > 59) {
D 3
		printf("WARNING: preposterous clock chip time");
E 3
		/*
		 * Believe the time in the file system for lack of
		 * anything better, resetting the TODR.
		 */
		time.tv_sec = base;
D 3
		if (!badbase)
E 3
I 3
		if (!badbase) {
D 8
			printf("WARNING: preposterous clock chip time\n");
E 8
I 8
			printf("WARNING: preposterous clock chip time");
E 8
E 3
			resettodr();
D 3
		return (0);
E 3
I 3
		}
		goto bad;
E 3
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
I 3
bad:
E 3
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
	register volatile struct chiptime *c;
D 3
	register int t, t2, t3;
E 3
I 3
	register int t, t2;
	int sec, min, hour, day, mon, year;
E 3
I 2
	int s;
E 2

	/* compute the year */
	t2 = time.tv_sec / SECDAY;
D 3
	t = 69;
E 3
I 3
	year = 69;
E 3
	while (t2 >= 0) {	/* whittle off years */
D 3
		t3 = t2;
		t++;
		t2 -= LEAPYEAR(t) ? 366 : 365;
E 3
I 3
		t = t2;
		year++;
		t2 -= LEAPYEAR(year) ? 366 : 365;
E 3
	}
I 2

E 2
D 3
	c = (volatile struct chiptime *)MACH_CLOCK_ADDR;
I 2
	s = splclock();
E 2
	c->regb |= REGB_SET_TIME;
	c->year = t - 19;

	/* t3 = month + day; separate */
	t = LEAPYEAR(t);
	for (t2 = 1; t2 < 12; t2++)
		if (t3 < dayyr[t2] + (t && t2 > 1))
E 3
I 3
	/* t = month + day; separate */
	t2 = LEAPYEAR(year);
	for (mon = 1; mon < 12; mon++)
		if (t < dayyr[mon] + (t2 && mon > 1))
E 3
			break;

D 3
	/* t2 is month */
	c->mon = t2;
	t3 = t3 - dayyr[t2 - 1] + 1;
	if (t && t2 > 2)
		t3--;
	c->day = t3;
E 3
I 3
	day = t - dayyr[mon - 1] + 1;
	if (t2 && mon > 2)
		day--;
E 3

	/* the rest is easy */
	t = time.tv_sec % SECDAY;
D 3
	c->hour = t / 3600;
E 3
I 3
	hour = t / 3600;
E 3
	t %= 3600;
D 3
	c->min = t / 60;
	c->sec = t % 60;
	c->regb &= ~REGB_SET_TIME;
E 3
I 3
	min = t / 60;
	sec = t % 60;

D 6
	c = (volatile struct chiptime *)MACH_CLOCK_ADDR;
E 6
I 6
	c = Mach_clock_addr;
E 6
	s = splclock();
	t = c->regb;
	c->regb = t | REGB_SET_TIME;
	MachEmptyWriteBuffer();
	c->sec = sec;
	c->min = min;
	c->hour = hour;
	c->day = day;
	c->mon = mon;
D 8
	c->year = year - 20; /* must be multiple of 4 because chip knows leap */
E 8
I 8
	c->year = year - YR_OFFSET;
E 8
	c->regb = t;
E 3
I 2
	MachEmptyWriteBuffer();
	splx(s);
E 2
}
E 1
