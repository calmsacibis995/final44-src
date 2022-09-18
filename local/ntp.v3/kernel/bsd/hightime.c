/******************************************************************************
 *                                                                            *
 * Copyright (c) David L. Mills 1993                                    *
 *                                                                            *
 * Permission to use, copy, modify, and distribute this software and its      *
 * documentation for any purpose and without fee is hereby granted, provided  *
 * that the above copyright notice appears in all copies and that both the    *
 * copyright notice and this permission notice appear in supporting           *
 * documentation, and that the name University of Delaware not be used in     *
 * advertising or publicity pertaining to distribution of the software        *
 * without specific, written prior permission.  The University of Delaware    *
 * makes no representations about the suitability this software for any       *
 * purpose.  It is provided "as is" without express or implied warranty.      *
 *                                                                            *
 ******************************************************************************/

/*
 * Modification history hightime.c
 *
 * 31 Dec 93	David L. Mills
 *	Created file
 */
/*
 * uniqtime() - Highball counter/timer interface
 */
#include <machine/reg.h>
#include <sys/param.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/vnode.h>
#include <sys/proc.h>
#include <machine/clock.h>
#include <machine/high.h>
#include <machine/pte.h>

/*
 * Global variables
 */
extern int tick;			/* tick the clock tocks to */
extern struct timeval time;		/* system time */

/*
 * Local variables
 */
static struct timeval lasttime;		/* last time returned */
static struct highregs *reg = NULL;	/* data/status pointer */
u_long cnt_w0, cnt_w1, cnt_w2, cnt_w3;	/* counter registers */

/*
 * Highball error counters
 */
long high_badtime;			/* bad highball time */

/*
 * The clock_offset variable is the offset which converts the hardware
 * counters to system time. It is initialized from the kernel time
 * variable upon first call to uniqtime() and on each call to the
 * settimeofday() system call. Also, it is adjusted by the adjtime()
 * and ntp_adjtime() system calls with the same increment as the
 * kernel time variable.
 */
struct timeval clock_offset;		/* current time offset */

/*
 * This routine reads the seconds and microseconds from the Highball
 * counter/timer interface and returns a Unix timeval. It is intended as
 * a dropin replacement for the SunOS 4.1.x uniqtime() routine or the
 * Van Jacobson microtime() routine.
 */
microtime(tvp)
	struct timeval *tvp;
{
	uniqtime(tvp);
}
int
uniqtime(tvp)
	struct timeval *tvp;
{
	struct timeval dtime, htime;
	long ltemp;

	/*
	 * Map the registers and initialize the time offset. Initialize the
	 * return time from the original system time, so if anything goes
	 * wrong the system doesn't lock up.
	 */
	if (reg == NULL) {
		reg = (struct highregs *)map_regs(HIGH_ADDR + 0x2000,
		    sizeof(reg), OBIO);
		reg->csr = DIV5;
		clock_set(&time);
	}
	*tvp = time;

	/*
	 * Read the counter registers and convert to system time.
	 */
	highboard(&htime);
	htime.tv_sec += clock_offset.tv_sec;
	htime.tv_usec += clock_offset.tv_usec;
	if (htime.tv_usec > 1000000) {
		htime.tv_sec++;
		htime.tv_usec -= 1000000;
	}

	/*
	 * The following makes sure the clock is monotonically advancing
	 * and never stuck, unless off by more than a second. If the
	 * return time is too far different from the original system time,
	 * return the original system time instead.
	 */
	dtime.tv_sec = lasttime.tv_sec - htime.tv_sec;
	dtime.tv_usec = lasttime.tv_usec - htime.tv_usec;
	if (dtime.tv_usec < 0) {
		dtime.tv_usec += 1000000;
		dtime.tv_sec--;
	}
	if (dtime.tv_sec == 0) {
		if (dtime.tv_usec > tick - 2)
			dtime.tv_usec = tick - 2;
		htime.tv_usec += dtime.tv_usec + 1;
		if (htime.tv_usec >= 1000000) {
			htime.tv_usec -= 1000000;
			htime.tv_sec++;
		}
	}
	lasttime = htime;
	ltemp = htime.tv_sec - time.tv_sec;
	if (ltemp > MAXDIFF || ltemp < -MAXDIFF) {
		high_badtime++;
		return (EBADTIME);
	}
	*tvp = htime;
	return (0);
}

/*
 * clock_set(tvp)
 *
 * This routine sets the clock offset of the highball counter relative
 * to the time of the argument. It is called by the settimeofday()
 * system call through its dependencies.
 */
clock_set(tvp)
	struct timeval *tvp;
{
	struct timeval ntime;

	clock_offset = *tvp;
	highboard(&ntime);
	clock_offset.tv_sec -= ntime.tv_sec;
	clock_offset.tv_usec -= ntime.tv_usec;
	if (clock_offset.tv_usec < 0) {
		clock_offset.tv_sec--;
		clock_offset.tv_usec += 1000000;
	}
}

/*
 * highboard(tvp)
 *
 * Read the seconds and microseconds from the Highboard and convert to
 * timeval format. Each 64-bit long word of the counter array includes
 * 16 bits of the composite counter. Read from high to low-rder, then
 * compare in reverse order. If a compare discrepancy is found, do it
 * again. Pray for no hot/cold bits.
 */
highboard(tvp)
	struct timeval *tvp;
{
	while(1) {
		reg->clock_strobe = 1;
		cnt_w3 = reg->cnt_w3 & 0xffff;
		cnt_w2 = reg->cnt_w2 & 0xffff;
		cnt_w1 = reg->cnt_w1 & 0xf;
		cnt_w0 = reg->cnt_w0 & 0xffff;
		if (cnt_w1 != (reg->cnt_w1 & 0xf))
			continue;
		if (cnt_w2 != (reg->cnt_w2 & 0xffff))
			continue;
		if (cnt_w3 != (reg->cnt_w3 & 0xffff))
			continue;
		break;
	}
	tvp->tv_sec = (cnt_w3 << 16) + cnt_w2;
	tvp->tv_usec = (cnt_w1 << 16) + cnt_w0;
}
