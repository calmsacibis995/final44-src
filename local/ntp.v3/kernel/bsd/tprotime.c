/******************************************************************************
 *                                                                            *
 * Copyright (c) David L. Mills 1993                                          *
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
 * Modification history tprotime.c
 *
 * 20 Jul 94	David L. Mills
 *	Fixed microtime/uniqtime bug that resulted in incorrect return code.
 *
 * 30 Dec 93	David L. Mills
 *	Created file
 */
/*
 * tprotime() - KSI/Odetics TPRO IRIG interface
 */
#include <machine/reg.h>
#include <sys/param.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/vnode.h>
#include <sys/proc.h>
#include <machine/clock.h>
#include <machine/tpro.h>
#include <machine/pte.h>

/*
 * Global variables
 */
extern struct timeval time;		/* system time */

/*
 * Local variables
 */
static long lastday;			/* last day of year returned */
static struct tproregs *reg = NULL;	/* data/status pointer */
u_long tprolo, tprohi;			/* TPRO data values */
u_char tprostat;			/* TPRO status */
static long yrtab[] = { DAY_YEAR, DAY_YEAR, DAY_YEAR + DAY, DAY_YEAR };
static long dectab[] = {1, 10, 100, 1000, 10000, 100000}; /* decimal decode */

/*
 * TPRO error counters
 */
long tpro_nosig;			/* no signal (TPRO_SIG status) */
long tpro_nosync;			/* no sync (TPRO_SYNC status) */
long tpro_baddata;			/* bad IRIG data */
long tpro_badtime;			/* bad IRIG time */

/*
 * The year_offset variable is the offset of the current year since
 * 1 Jan 1970. It is initialized from the kernel time variable upon
 * first call to uniqtime() and on each call to the settimeofday()
 * system call. We also have to sneak a call in as the year overflows.
 * What a pain.
 */
static long year_offset;		/* current year offset (s) */

/*
 * This routine reads the day and time from the TPRO interface board and
 * returns a Unix timeval. It is intended as a dropin replacement for
 * the SunOS 4.1.x uniqtime() routine or the Van Jacobson microtime()
 * routine. Since the IRIG signal does not include the year, the year is
 * decoded from the ordinary system time, which is real ugly.
 */
void
uniqtime(tvp)
	struct timeval *tvp;
{
	(void)uniqtime(tvp);
}

int
microtime(tvp)
	struct timeval *tvp;
{
	long day, hour, min, sec, usec;
	long mtemp;
	register int i;

	/*
	 * Map the registers, if not done already. Initialize the return
	 * time from the system time, so if anything goes wrong the
	 * system doesn't lock up.
	 */
	if (reg == NULL) {
		reg = (struct tproregs *)map_regs(TPRO_ADDR,
		    sizeof(reg), OBIO);
		clock_set(&time);
	}
	*tvp = time;

	/*
	 * Read the day and time in bcd and convert to timeval format.
	 * This should be done in the silicon, not the following ugly
	 * bit of arithmetic. Return error flash if board has no signal,
	 * is out of synchronization, has data out of range, or has time
	 * more than MAXDIFF seconds different from system time. We don't
	 * bother checking for invalid bcd digits (a-f). If all checks
	 * succeed, return the IRIG time and set the system time as well.
	 */
	tprolo = reg->tprolo;
	tprohi = reg->tprohi;
	tprostat = reg->tprostat;
	if (!(tprostat & TPRO_SIG)) {
		tpro_nosig++;
		return (ENOSIG);
	}
	if (!(tprostat & TPRO_SYNC)) {
		tpro_nosync++;
		return (ENOSYNC);
	}
	usec = ((((((tprolo>> 20) & 0xf) * 10 +
	    ((tprolo >> 16) & 0xf)) * 10 +
	    ((tprolo >> 12) & 0xf)) * 10 +
	    ((tprolo >> 8) & 0xf)) * 10 +
	    ((tprolo >> 4) & 0xf)) * 10 + (tprolo & 0xf);
	sec = ((tprolo >> 28) & 0x7) * 10 + ((tprolo >> 24) & 0xf);
        min = ((tprohi >> 4) & 0x7) * 10 + (tprohi & 0xf);
	hour = ((tprohi >> 12) & 0x3) * 10 + ((tprohi >> 8) & 0xf);
	day = (((tprohi >> 24) & 0x3) * 10 + ((tprohi >> 20) &
	    0xf)) * 10 + ((tprohi >> 16) & 0xf);
	if (usec >= 1000000 || sec >= 60 || min >= 60 || hour >= 24 ||
	    day < 1 || day > 366) {
		tpro_baddata++;;
		return (EBADDATA);
	}
	if (day < lastday)
		clock_set(&time);
	lastday = day;
	sec += year_offset + ((((day - 1) * 24 + hour) * 60) + min) * 60;
	mtemp = sec - time.tv_sec;
	if (mtemp > MAXDIFF || mtemp < -MAXDIFF) {
		tpro_badtime++;
		return (EBADTIME);
	}
	tvp->tv_sec = sec;
	tvp->tv_usec = usec;
	return (0);
}

/*
 * This routine sets the year offset from the value given as argument.
 * It is called by the settimeofday() system call and its dependencies
 * and by the uniqtime() routine when the year rolls over.
 */
clock_set(tvp)
	struct timeval *tvp;
{
	long year, sec;
	register int i;

	year = tvp->tv_sec;
	sec = 0;
	while (year >= DAY_CYCLE){
		year -= DAY_CYCLE;
		sec += DAY_CYCLE;
	}
	for (i = 0; year >= yrtab[i]; i++) {
		year -= yrtab[i];
		sec += yrtab[i];
	}
	year_offset = sec;
}
