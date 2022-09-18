/* 
 * Mach Operating System
 * Copyright (c) 1991,1989,1988,1987 Carnegie Mellon University
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
 * $Log:	watch_chip.c,v $
 * Revision 2.5  93/05/15  18:58:40  mrt
 * 	machparam.h -> machspl.h
 * 
 * Revision 2.4  91/06/19  12:01:52  rvb
 * 	Support for VaxStation 3100:	shift two bits
 * 	[91/06/04            rvb]
 * 
 * Revision 2.3  91/05/14  17:46:36  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:28:33  dbg
 * 	Include vax/machparam.h for SPL definitions.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.1  89/08/03  16:36:59  rwd
 * Created.
 * 
 * 17-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	De-linted.
 *
 * 16-Dec-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added correct code (from libc/gen/ctime.c) to convert day to
 *	time format.
 *
 * 11-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	Merged with real 4.3 release.
 *
 * 29-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	Duplicated routine for normal and rotated cases of watch-chip.
 *
 * 20-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 *
 */

/*
 *	File:	vax/watch_chip.c
 *	Author:	Avadis Tevanian, Jr., 1986.
 *
 *	Support for VAX Watch Chip.
 */

#include <vax/clock.h>
#include <vax/watch_chip.h>
#include <vax/machspl.h>
#include <sys/tm.h>

#define	MINSEC	60
#define HRSEC	3600

/*
 *	Read the time from the watch chip into the time structure.
 */
watch_chip_read_normal(watch, time)
	register struct watch_chip	*watch;
	register struct tm		*time;
{
	int	s;

	/*
	 *	Spin while clock is busy, then disable all interrupts.
	 *	Check to be sure that an interrupt didn't sneak in
	 *	by spinning a second time.
	 */

	while (watch->csra & WATCH_CSRA_BUSY)
		;
	s = spl7();
	while (watch->csra & WATCH_CSRA_BUSY)
		;
	time->tm_sec = watch->seconds;
	time->tm_min = watch->minutes;
	time->tm_hour = watch->hours;
	time->tm_mday = watch->day;
	time->tm_mon = watch->month;
	time->tm_year = watch->year;
	splx(s);
}

watch_chip_read_rotated(watch, time)
	register struct watch_chip	*watch;
	register struct tm		*time;
{
	int	s;

	/*
	 *	Spin while clock is busy, then disable all interrupts.
	 *	Check to be sure that an interrupt didn't sneak in
	 *	by spinning a second time.
	 */

	while (watch->csra & WATCH_ROT_CSRA_BUSY)
		;
	s = spl7();
	while (watch->csra & WATCH_ROT_CSRA_BUSY)
		;
	time->tm_sec = watch->seconds;
	time->tm_min = watch->minutes;
	time->tm_hour = watch->hours;
	time->tm_mday = watch->day;
	time->tm_mon = watch->month;
	time->tm_year = watch->year;
	splx(s);

	time->tm_sec >>= 1;
	time->tm_min >>= 1;
	time->tm_hour >>= 1;
	time->tm_mday >>= 1;
	time->tm_mon >>= 1;
	time->tm_year >>= 1;
}

watch_chip_read_shifted(watch, time)
	register struct watch_chip_3100	*watch;
	register struct tm		*time;
{
	int	s;

	/*
	 *	Spin while clock is busy, then disable all interrupts.
	 *	Check to be sure that an interrupt didn't sneak in
	 *	by spinning a second time.
	 */

	while (watch->csra & WATCH_SHFT_CSRA_BUSY)
		;
	s = spl7();
	while (watch->csra & WATCH_SHFT_CSRA_BUSY)
		;
	time->tm_sec = watch->seconds;
	time->tm_min = watch->minutes;
	time->tm_hour = watch->hours;
	time->tm_mday = watch->day;
	time->tm_mon = watch->month;
	time->tm_year = watch->year;
	splx(s);

	time->tm_sec >>= 2;
	time->tm_min >>= 2;
	time->tm_hour >>= 2;
	time->tm_mday >>= 2;
	time->tm_mon >>= 2;
	time->tm_year >>= 2;
}

/*
 *	Write the time from the time structure into the watch chip.
 */
watch_chip_write_normal(watch, time)
	register struct watch_chip	*watch;
	register struct tm		*time;
{
	int	s;

	s = spl7();
	watch->csra = WATCH_CSRA_SETUP;
	watch->csrb = WATCH_CSRB_SETUP|WATCH_CSRB_OFF;
	watch->seconds = time->tm_sec;
	watch->minutes = time->tm_min;
	watch->hours = time->tm_hour;
	watch->day = time->tm_mday;
	watch->month = time->tm_mon;
	watch->year = time->tm_year;
	watch->csrb = WATCH_CSRB_SETUP;
	splx(s);
}

watch_chip_write_rotated(watch, time)
	register struct watch_chip	*watch;
	register struct tm		*time;
{
	int	s;

	struct tm	r_time;		/* holds shifted fields */

	r_time.tm_sec  = time->tm_sec << 1;
	r_time.tm_min  = time->tm_min << 1;
	r_time.tm_hour = time->tm_hour << 1;
	r_time.tm_mday = time->tm_mday << 1;
	r_time.tm_mon  = time->tm_mon << 1;
	r_time.tm_year = time->tm_year << 1;

	s = spl7();
	watch->csra = WATCH_ROT_CSRA_SETUP;
	watch->csrb = WATCH_ROT_CSRB_SETUP|WATCH_ROT_CSRB_OFF;
	watch->seconds = r_time.tm_sec;
	watch->minutes = r_time.tm_min;
	watch->hours   = r_time.tm_hour;
	watch->day     = r_time.tm_mday;
	watch->month   = r_time.tm_mon;
	watch->year    = r_time.tm_year;
	watch->csrb = WATCH_ROT_CSRB_SETUP;
	splx(s);
}

watch_chip_write_shifted(watch, time)
	register struct watch_chip_3100	*watch;
	register struct tm		*time;
{
	int	s;

	struct tm	r_time;		/* holds shifted fields */

	r_time.tm_sec  = time->tm_sec << 2;
	r_time.tm_min  = time->tm_min << 2;
	r_time.tm_hour = time->tm_hour << 2;
	r_time.tm_mday = time->tm_mday << 2;
	r_time.tm_mon  = time->tm_mon << 2;
	r_time.tm_year = time->tm_year << 2;

	s = spl7();
	watch->csra = WATCH_SHFT_CSRA_SETUP;
	watch->csrb = WATCH_SHFT_CSRB_SETUP|WATCH_SHFT_CSRB_OFF;
	watch->seconds = r_time.tm_sec;
	watch->minutes = r_time.tm_min;
	watch->hours   = r_time.tm_hour;
	watch->day     = r_time.tm_mday;
	watch->month   = r_time.tm_mon;
	watch->year    = r_time.tm_year;
	watch->csrb = WATCH_ROT_CSRB_SETUP;
	splx(s);
}

short dayyr[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, };

convert_tm(tm)
	struct tm	*tm;
{
	register int	tmp1, tmp2;

	tmp2 = 0;
	for (tmp1 = 70; tmp1 < tm->tm_year; tmp1++) {
		tmp2 += 365;
		/* I just luv leap years... */
		if (LEAPYEAR(tmp1))
			tmp2++;
	}
	tmp2 += (dayyr[tm->tm_mon-1]+tm->tm_mday-1);
	if (LEAPYEAR(tm->tm_year) && tm->tm_mon > 2)
		tmp2++;
	/* Finally got days past Jan. 1,1970. the rest is easy.. */
	tmp1 = tmp2*SECDAY+tm->tm_hour*HRSEC+
			tm->tm_min*MINSEC+tm->tm_sec;
	return(tmp1);
}

static	short	dmsize[12] = { 31, 28, 31, 30, 31, 30,
			       31, 31, 30, 31, 30, 31 };
static	short	ly_dmsize[12] =
			     { 31, 29, 31, 30, 31, 30,
			       31, 31, 30, 31, 30, 31 };

#define	dysize(year)	((year)%4 == 0 ? 366 : 365)

convert_sec(sec, tm)
	int	sec;
	struct tm	*tm;
{
	register int	hms, day, d1;
	register short	*dmtab;

	hms = sec % 86400;
	day = sec / 86400;
	if (hms < 0) {
		hms += 86400;
		day -= 1;
	}

	/*
	 *	generate seconds/minutes/hours
	 */
	tm->tm_sec = hms % 60;
	d1         = hms / 60;
	tm->tm_min = d1  % 60;
	tm->tm_hour = d1 / 60;

	/*
	 *	year number
	 */
	if (day >= 0) {
		for (d1 = 70; day >= dysize(d1); d1++)
			day -= dysize(d1);
	}
	else {
		for (d1 = 70; day < 0; d1--)
			day += dysize(d1-1);
	}
	tm->tm_year = d1;

	/*
	 *	generate month.  'day' is day-in-year, from 0.
	 */
	if (dysize(d1) == 366)
		dmtab = ly_dmsize;
	else
		dmtab = dmsize;
	for (d1 = 0; day >= dmtab[d1]; d1++)
		day -= dmtab[d1];
	tm->tm_mon = d1+1;
	tm->tm_mday = day + 1;
}
