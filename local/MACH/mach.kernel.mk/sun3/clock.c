/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	clock.c,v $
 * Revision 2.5  89/03/09  21:32:10  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  19:33:21  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/12/19  12:52:19  mja
 * 	CMUCS: disable dosynctodr hack now that the clock tick
 * 	interrupt loss problem appears to be fixed;  convert
 * 	conditionals.
 * 	[88/09/30  17:02:20  mja]
 * 
 * Revision 2.2  88/08/24  02:10:03  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 * 13-Jan-88  Jonathan Chew (jjc) at Carnegie-Mellon University
 *	Fixed todset() correctly calculate month on leap years.
 *
 * 17-Sep-87  Jonathan Chew (jjc) at Carnegie-Mellon University
 *	In synctodr, make sure timedelta is a multiple of tickdelta (NOT
 *	tickadj!).
 *
 * 24-Oct-86  David Golub (dbg) and Jonathan J. Chew (jjc)
 *		at Carnegie-Mellon University
 *	Changed synctodr() to adjust time like adjtime() in kern_time.c.
 *
 */ 
#ifndef	lint
static	char sccsid[] = "@(#)clock.c 1.1 86/02/03 Copyr 1985 Sun Micro";
#endif

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <sys/param.h>
#include <sys/time.h>
#include <sys/kernel.h>

#include <sun3/clock.h>
#include <sun3/interreg.h>

struct timeval todget();

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
startrtclock()
{

	/*
	 * We will set things up to interrupt every 1/100 of a second.
	 * locore.s currently only calls hardclock every other clock
	 * interrupt, thus assuming 50 hz operation.
	 */
	if (hz != 50)
		panic("startrtclock");

	CLKADDR->clk_intrreg = CLK_INT_HSEC;	/* set 1/100 sec clock intr */
	set_clk_mode(IR_ENA_CLK5, 0);		/* turn on level 5 clock intr */
}

/*
 * Set and/or clear the desired clock bits in the interrupt
 * register.  We have to be extremely careful that we do it
 * in such a manner that we don't get ourselves lost.
 */
set_clk_mode(on, off)
	u_char on, off;
{
	register u_char interreg, dummy;

	/*
	 * make sure that we are only playing w/ 
	 * clock interrupt register bits
	 */
	on &= (IR_ENA_CLK7 | IR_ENA_CLK5);
	off &= (IR_ENA_CLK7 | IR_ENA_CLK5);

	/*
	 * Get a copy of current interrupt register,
	 * turning off any undesired bits (aka `off')
	 */
	interreg = *INTERREG & ~(off | IR_ENA_INT);
	*INTERREG &= ~IR_ENA_INT;

	/*
	 * Next we turns off the CLK5 and CLK7 bits to clear
	 * the flip-flops, then we disable clock interrupts.
	 * Now we can read the clock's interrupt register
	 * to clear any pending signals there.
	 */
	*INTERREG &= ~(IR_ENA_CLK7 | IR_ENA_CLK5);
	CLKADDR->clk_cmd = (CLK_CMD_NORMAL & ~CLK_CMD_INTRENA);
	dummy = CLKADDR->clk_intrreg;			/* clear clock */
#ifdef	lint
	dummy = dummy;
#endif

	/*
	 * Now we set all the desired bits
	 * in the interrupt register, then
	 * we turn the clock back on and
	 * finally we can enable all interrupts.
	 */
	*INTERREG |= (interreg | on);			/* enable flip-flops */
	CLKADDR->clk_cmd = CLK_CMD_NORMAL;		/* enable clock intr */
	*INTERREG |= IR_ENA_INT;			/* enable interrupts */
}

int clkdrift = 0;
int dosynctodr = 0;
#define ABS(x)	((x) < 0? -(x) : (x))

/*
 * Initialize the system time, based on the time base which is, e.g.
 * from a filesystem.
 */
inittodr(base)
	time_t base;
{
	register long deltat;
	int s;

	if (base < (85 - YRREF) * SECYR) {	/* ~1985 */
		printf("WARNING: preposterous time in file system");
		goto check;
	}
	s = splclock();
	time = todget();
	(void) splx(s);
	if (time.tv_sec < SECYR) {
		time.tv_sec = base;
		printf("WARNING: TOD clock not initialized");
		resettodr();
		goto check;
	}
	deltat = time.tv_sec - base;
	/*
	 * See if we gained/lost two or more days;
	 * if so, assume something is amiss.
	 */
	if (deltat < 0)
		deltat = -deltat;
	if (deltat < 2*SECDAY)
		goto out;
	printf("WARNING: clock %s %d days",
	    time.tv_sec < base ? "lost" : "gained", deltat / SECDAY);
check:
	printf(" -- CHECK AND RESET THE DATE!\n");
out:
	if (dosynctodr)
		synctodr(20*hz);
}

synctodr(interval)
{
	struct timeval tv;
	int deltat;
	extern	int tickadj;		/* "standard" clock skew, us./tick */
	extern int	tickdelta;	/* current clock skew, us. per tick */
	extern long	timedelta;	/* unapplied time correction, us. */
	extern long	bigadj;		/* use 10x skew above bigadj us. */

	/*
	 * If timedelta is non-zero, assume someone who
	 * knows better is already adjusting the time.
	 */
	if (dosynctodr && timedelta == 0) {
		int s = splclock();

		tv = todget();
		/*
		 * Set up new timedelta value if
		 * we have drifted over a clock tick.
		 */
		deltat = 1000000 * (tv.tv_sec - time.tv_sec) +
		    (tv.tv_usec - time.tv_usec);
		if (ABS(deltat) > 1000000 / hz) {
			timedelta = deltat;
			/*
			 *	Set up tickdelta as done in
			 *	kern_time:adjtime.
			 */
			if (timedelta > bigadj)
				tickdelta = 10 * tickadj;
			else
				tickdelta = tickadj;
			if (timedelta % tickdelta)
				timedelta = timedelta / tickdelta * tickdelta;
			if (clkdrift)
				printf("<[%d]> ", deltat / 1000);
		}
		(void) splx(s);
	}
	timeout(synctodr, (caddr_t)interval, interval);
}

/*
 * Reset the TODR based on the time value; used when the TODR
 * has a preposterous value and also when the time is reset
 * by the settimeofday system call.  We call tod_set at splclock()
 * to avoid synctodr() from running and getting confused.
 */
resettodr()
{
	struct timeval tv;
	int s;

	s = splclock();
	tv = time;
	todset(tv);
	(void) splx(s);
}

/*
 * For Sun-3, we use the Intersil ICM7170 for both the
 * real time clock and the time-of-day device.
 */

static u_int monthsec[12] = {
	31 * SECDAY,	/* Jan */
	28 * SECDAY,	/* Feb */
	31 * SECDAY,	/* Mar */
	30 * SECDAY,	/* Apr */
	31 * SECDAY,	/* May */
	30 * SECDAY,	/* Jun */
	31 * SECDAY,	/* Jul */
	31 * SECDAY,	/* Aug */
	30 * SECDAY,	/* Sep */
	31 * SECDAY,	/* Oct */
	30 * SECDAY,	/* Nov */
	31 * SECDAY	/* Dec */
};

#define MONTHSEC(mon, yr)	\
	(((((yr) % 4) == 0) && ((mon) == 2))? 29*SECDAY : monthsec[(mon) - 1])

/*
 * Set the TOD based on the argument value; used when the TOD
 * has a preposterous value and also when the time is reset
 * by the settimeofday system call.
 */
todset(tv)
struct timeval tv;
{
	register int t = tv.tv_sec;
	u_short hsec, sec, min, hour, day, mon, weekday, year;

	/*
	 * Figure out the (adjusted) year
	 */
	for (year = (YRREF - YRBASE); t > SECYEAR(year); year++)
		t -= SECYEAR(year);

	/*
	 * Figure out what month this is by subtracting off
	 * time per month, adjust for leap year if appropriate.
	 */
	for (mon = 1; t >= 0; mon++)
		t -= MONTHSEC(mon, year);

	/*
	 *	Back off one month before MONTHSEC because MONTHSEC will end
	 *	up backing off two months during leap years if you pass it
	 *	"--mon"
	 */
	mon--;
	t += MONTHSEC(mon, year);

	sec = t % 60;			/* seconds */
	t /= 60;
	min = t % 60;			/* minutes */
	t /= 60;
	hour = t % 24;			/* hours (24 hour format) */
	day = t / 24;			/* day of the month */
	day++;				/* adjust to start at 1 */
	weekday = day % 7;		/* not right, but it doesn't matter */

	hsec = tv.tv_usec / 10000;

	CLKADDR->clk_cmd = (CLK_CMD_NORMAL & ~CLK_CMD_RUN);
	CLKADDR->clk_weekday = weekday;
	CLKADDR->clk_year = year;
	CLKADDR->clk_mon = mon;
	CLKADDR->clk_day = day;
	CLKADDR->clk_hour = hour;
	CLKADDR->clk_min = min;
	CLKADDR->clk_sec = sec;
	CLKADDR->clk_hsec = hsec;
	CLKADDR->clk_cmd = CLK_CMD_NORMAL;
}

/*
 * Read the current time from the clock chip and convert to UNIX form.
 * Assumes that the year in the counter chip is valid.
 */
struct timeval
todget()
{
	struct timeval tv;
	u_char now[CLK_WEEKDAY];
	register int i;
	register u_char *cp = (u_char *)CLKADDR;
	register u_int t = 0;
	u_short year;

	for (i = CLK_HSEC; i < CLK_WEEKDAY; i++)	/* read counters */
		now[i] = *cp++;

	/*
	 * Add the number of seconds for each year onto our time t.
	 * We start at YRBASE, and count up to the year value given
	 * by the chip.  If the year is greater/equal to the difference
	 * between YRREF and YRBASE, then that time is added into
	 * the Unix time value we are calculating.
	 */
	for (year = 0; year < now[CLK_YEAR]; year++)
		if (year >= (YRREF - YRBASE))
			t += SECYEAR(year);

	/*
	 * Now add in the seconds for each month that has gone
	 * by this year, adjusting for leap year if appropriate.
	 */
	for (i = 1; i < now[CLK_MON]; i++)
		t += MONTHSEC(i, year);

	t += (now[CLK_DAY] - 1) * SECDAY;
	t += now[CLK_HOUR] * (60*60);
	t += now[CLK_MIN] * 60;
	t += now[CLK_SEC];

	tv.tv_usec = now[CLK_HSEC] * 10000;
	tv.tv_sec = t;
	return (tv);
}
