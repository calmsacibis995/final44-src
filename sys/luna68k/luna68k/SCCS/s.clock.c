h19006
s 00006/00004/00312
d D 8.2 93/08/15 11:28:33 mckusick 12 11
c final update from Akito Fujita
e
s 00002/00002/00314
d D 8.1 93/06/10 22:25:01 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00004/00315
d D 7.10 93/05/12 18:36:58 akito 10 9
c make include <machine/cpu.h> anytime
e
s 00014/00009/00305
d D 7.9 93/05/12 16:27:57 akito 9 8
c set hz for LUNA-I
e
s 00079/00017/00235
d D 7.8 93/05/12 04:11:01 akito 8 7
c LUNA-II (68040 based LUNA) support
e
s 00001/00001/00251
d D 7.7 93/05/02 05:36:52 akito 7 6
c bug fix clock initialization
e
s 00001/00001/00251
d D 7.6 93/03/17 11:09:28 akito 6 5
c header update
e
s 00001/00003/00251
d D 7.5 93/01/03 12:47:51 akito 5 4
c remaked from field
e
s 00004/00003/00250
d D 7.4 92/10/11 11:07:44 bostic 4 3
c make kernel includes standard
e
s 00003/00003/00250
d D 7.3 92/09/01 16:57:21 akito 3 2
c "clock_on" flag should be turned on
e
s 00023/00009/00230
d D 7.2 92/07/23 16:01:25 fujita 2 1
c update for 4.4BSD-alpha distribution
e
s 00239/00000/00000
d D 7.1 92/06/15 06:38:29 fujita 1 0
c date and time created 92/06/15 06:38:29 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1992 OMRON Corporation.
D 11
 * Copyright (c) 1982, 1990, 1992 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1982, 1990, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: clock.c 1.18 91/01/21$
D 5
 * OMRON: $Id: clock.c,v 1.1 92/05/27 14:24:06 moti Exp $
 *
D 2
 * from: hp300/hp300/clock.c	7.8 (Berkeley) 2/25/92
E 2
I 2
 * from: hp300/hp300/clock.c    7.14 (Berkeley) 7/8/92
E 5
I 5
D 6
 * from: hp300/hp300/clock.c	7.17 (Berkeley) 12/27/92
E 6
I 6
 * from: hp300/hp300/clock.c	7.19 (Berkeley) 2/18/93
E 6
E 5
E 2
 *
 *	%W% (Berkeley) %G%
 */

D 4
#include "param.h"
#include "kernel.h"
#include "clockreg.h"
E 4
I 4
#include <sys/param.h>
#include <sys/kernel.h>

D 10
#include <luna68k/luna68k/clockreg.h>
E 4

I 8
#ifdef LUNA2
E 10
#include <machine/cpu.h>
D 10
#endif
E 10
I 10
#include <luna68k/luna68k/clockreg.h>
E 10

E 8
I 2
extern int clock_on;

E 2
static int month_days[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
struct bbc_tm *gmt_to_bbc();

volatile struct bbc *bbc = (struct bbc *)BBC_ADDR;
I 8
#ifdef LUNA2
volatile struct bbc2 *bbc2 = (struct bbc2 *)BBC_ADDR;
#endif
E 8

int battery_clock;
int battery_chkfg;

/*
 * Machine-dependent clock routines.
 *
 * Startrtclock just checks battry backuped clock
 * (when it does not work, starts it).
 *
 * Enablertclock sets flag for clock interrupt.
 *
 * Inittodr initializes the time of day hardware which provides
 * date functions.
 *
 * Resettodr restores the time of day hardware after a time change.
 *
 */

/*
 * Start the real-time clock.
 */
D 2
startrtclock()
E 2
I 2
cpu_initclocks()
E 2
{
	static char *rtcstrings = "RTC";     /* For compat */

I 3
	/* set flag for clockintr. */
	clock_on = 1;

I 8
#ifdef LUNA2
	if (machineid == LUNA_II) {
		/* not yet */
		battery_chkfg = 1;
		battery_clock = 1;
		return;
	}
#endif

E 8
E 3
	batterychk();
	if (!battery_clock)
	  return;

	if (!strncmp(bbc->nvram.nv_calclock, rtcstrings, sizeof(rtcstrings))) /* Okey */
	  return;
	
	printf("Initialize Battery Backup Clock.\n");
	bbc->cal_ctl |= BBC_WRT;
	bbc->cal_sec &= ~BBC_STOP;
	bbc->cal_hour |= BBC_KICK;
	bbc->cal_dow &= ~BBC_FRQ;
	bbc->cal_ctl &= ~BBC_WRT;
	DELAY(BBC_DELAY);
	bbc->cal_ctl |= BBC_WRT;
	bbc->cal_hour &= ~BBC_KICK;
	bbc->cal_ctl &= ~BBC_WRT;
D 7
	strcpy(bbc->nvram,rtcstrings);
E 7
I 7
	strcpy(bbc->nvram.nv_calclock, rtcstrings);
E 7
I 2
D 3

	/* set flag for clockintr. */
	clock_on = 1;
E 3
E 2
}

D 2
/* 
 * Enable clock intrruupt.
 */
enablertclock()
E 2
I 2
void
setstatclockrate(newhz)
        int newhz;
E 2
{
D 2
        extern int clock_on;
E 2
I 2
}
E 2

D 2
	/* set flag for clockintr. */
	clock_on = 1;
E 2
I 2
microtime(tvp)
        register struct timeval *tvp;
{
        int s = splhigh();

        *tvp = time;
        tvp->tv_usec += tick;
        while (tvp->tv_usec > 1000000) {
                tvp->tv_sec++;
                tvp->tv_usec -= 1000000;
        }
        splx(s);
E 2
}

/*
 * Initialize the time of day register, based on the time base which is, e.g.
 * from a filesystem.
 */
inittodr(base)
	time_t base;
{
	u_long timbuf = base;	/* assume no battery clock exists */

	/*
	 * bbc_to_gmt converts and stores the gmt in timbuf.
	 * If an error is detected in bbc_to_gmt, or if the filesystem
	 * time is more recent than the gmt time in the clock,
	 * then use the filesystem time and warn the user.
 	 */
	if (!bbc_to_gmt(&timbuf) || timbuf < base) {
		printf("WARNING: bad date in battery clock\n");
		timbuf = base;
	}
	if (base < 5*SECYR) {
		printf("WARNING: preposterous time in file system");
		timbuf = 6*SECYR + 186*SECDAY + SECDAY/2;
		printf(" -- CHECK AND RESET THE DATE!\n");
	}
	
	/* Battery clock does not store usec's, so forget about it. */
	time.tv_sec = timbuf;
}

resettodr()
{
	register int i,s;
	register struct bbc_tm *tmptr;

	tmptr = gmt_to_bbc(time.tv_sec);

	s = splimp();

	/* set bb-clock */
D 8
	bbc->cal_ctl |= BBC_WRT;
	bbc->cal_sec = binary_to_bcd(tmptr->tm_sec);
	bbc->cal_min = binary_to_bcd(tmptr->tm_min);
	bbc->cal_hour = binary_to_bcd(tmptr->tm_hour);
	bbc->cal_day = binary_to_bcd(tmptr->tm_mday);
	bbc->cal_mon = binary_to_bcd(tmptr->tm_mon);
	bbc->cal_year = binary_to_bcd(tmptr->tm_year);
	bbc->cal_ctl &= ~BBC_WRT;
E 8
I 8
#ifdef LUNA2
	if (machineid == LUNA_II) {
I 12
		bbc2->cal_ctl_b |= BBC2_B_SET;
E 12
D 9
#if 1
		/* not yet */
		printf("WARNING: not supported resettodr() at LUNA2 yet.\n");
		return;
#else
		/* bbc2->cal_ctl_? |= BBC_WRT; */
E 9
		bbc2->cal_sec = tmptr->tm_sec;
		bbc2->cal_min = tmptr->tm_min;
		bbc2->cal_hour =tmptr->tm_hour;
		bbc2->cal_day = tmptr->tm_mday;
		bbc2->cal_mon = tmptr->tm_mon;
D 9
		bbc2->cal_year = tmptr->tm_year);
		/* bbc2->cal_ctl_? &= ~BBC_WRT; */
#endif
E 9
I 9
		bbc2->cal_year = tmptr->tm_year;
I 12
		bbc2->cal_ctl_b &= ~BBC2_B_SET;
E 12
E 9
	} else 
#endif
	{
		bbc->cal_ctl |= BBC_WRT;
		bbc->cal_sec = binary_to_bcd(tmptr->tm_sec);
		bbc->cal_min = binary_to_bcd(tmptr->tm_min);
		bbc->cal_hour = binary_to_bcd(tmptr->tm_hour);
		bbc->cal_day = binary_to_bcd(tmptr->tm_mday);
		bbc->cal_mon = binary_to_bcd(tmptr->tm_mon);
		bbc->cal_year = binary_to_bcd(tmptr->tm_year);
		bbc->cal_ctl &= ~BBC_WRT;
	}
E 8

	splx(s);
}

struct bbc_tm *
gmt_to_bbc(tim)
	long tim;
{
	register int i;
	register long hms, day;
	static struct bbc_tm rt;

	day = tim / SECDAY;
	hms = tim % SECDAY;

	/* Hours, minutes, seconds are easy */
	rt.tm_hour = hms / 3600;
	rt.tm_min  = (hms % 3600) / 60;
	rt.tm_sec  = (hms % 3600) % 60;

	/* Number of years in days */
	for (i = STARTOFTIME - 1900; day >= days_in_year(i); i++)
	  	day -= days_in_year(i);
	rt.tm_year = i;
	
	/* Number of months in days left */
	if (leapyear(rt.tm_year))
		days_in_month(FEBRUARY) = 29;
	for (i = 1; day >= days_in_month(i); i++)
		day -= days_in_month(i);
	days_in_month(FEBRUARY) = 28;
	rt.tm_mon = i;

	/* Days are what is left over (+1) from all that. */
	rt.tm_mday = day + 1;  
	
	return(&rt);
}

bbc_to_gmt(timbuf)
	u_long *timbuf;
{
	register int i,s;
	register u_long tmp;
	int year, month, day, hour, min, sec;

        if (!battery_clock)
	   return(0);

	s = splimp();

	/* read bb-clock */
D 8
	bbc->cal_ctl |= BBC_RD;
	sec = bcd_to_binary(bbc->cal_sec);
	min = bcd_to_binary(bbc->cal_min);
	hour = bcd_to_binary(bbc->cal_hour);
	day = bcd_to_binary(bbc->cal_day);
	month = bcd_to_binary(bbc->cal_mon);
	year = bcd_to_binary(bbc->cal_year) + 1900;
	bbc->cal_ctl &= ~BBC_RD;
	
E 8
I 8
#ifdef LUNA2
	if (machineid == LUNA_II) {
I 12
		while (bbc2->cal_ctl_a & BBC2_A_UIP) {} /* wait (max 224 us) */
		bbc2->cal_ctl_b |= BBC2_B_SET;
E 12
		sec = bbc2->cal_sec;
		min = bbc2->cal_min;
		hour = bbc2->cal_hour;
		day = bbc2->cal_day;
		month = bbc2->cal_mon;
		year = bbc2->cal_year + 1900;
I 12
		bbc2->cal_ctl_b &= ~BBC2_B_SET;
E 12
	} else
#endif
	{
		bbc->cal_ctl |= BBC_RD;
		sec = bcd_to_binary(bbc->cal_sec);
		min = bcd_to_binary(bbc->cal_min);
		hour = bcd_to_binary(bbc->cal_hour);
		day = bcd_to_binary(bbc->cal_day);
		month = bcd_to_binary(bbc->cal_mon);
		year = bcd_to_binary(bbc->cal_year) + 1900;
		bbc->cal_ctl &= ~BBC_RD;
	}

E 8
	splx(s);

	range_test(hour, 0, 23);
	range_test(day, 1, 31);
	range_test(month, 1, 12);
I 8
D 12
#if 1	/* limitted 2000 now ... */
E 8
	range_test(year, STARTOFTIME, 2000);
I 8
#else
E 12
I 12

E 12
	if (year < 1970) {
		year += 100;
	}
D 12
#endif
E 12
E 8
	
	tmp = 0;
	
	for (i = STARTOFTIME; i < year; i++)
	    tmp += days_in_year(i);
	if (leapyear(year) && month > FEBRUARY)
	    tmp++;

	for (i = 1; i < month; i++)
	    tmp += days_in_month(i);
	
	tmp += (day - 1);
	tmp = ((tmp * 24 + hour) * 60 + min) * 60 + sec;

	*timbuf = tmp;
	return(1);
}

batterychk()
{
	static char btchkdata[] = "chk";

I 8
#ifdef LUNA2
	if (machineid == LUNA_II) {
		/* not yet */
		battery_chkfg = 1;
		battery_clock = 1;
		return;
	}
#endif
E 8
	/* if already checked, return */
	if (battery_chkfg)
		return;

	battery_chkfg = 1;
	if (badaddr((caddr_t)bbc, 2))
		return;

	strcpy(bbc->nvram.nv_testwrite, btchkdata);
	if (strncmp(bbc->nvram.nv_testwrite, btchkdata, sizeof(btchkdata))) {
		printf("WARNING: calendar clock battery down\n");
		return;
	}
	battery_clock = 1;
	return;
I 9
}

#define	LUNA1_HZ	60

modify_clock_param()
{
	extern int	hz, tick, tickadj;

	if (machineid == LUNA_I) {
		hz = LUNA1_HZ;
		tick = 1000000 / hz;
		tickadj = 30000 / (60 * hz);	/* can adjust 30ms in 60s */
	}
E 9
}
E 1
