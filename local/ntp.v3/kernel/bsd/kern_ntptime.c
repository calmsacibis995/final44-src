/******************************************************************************
 *                                                                            *
 * Copyright (c) David L. Mills 1993, 1994                                    *
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
 * Modification history kern_ntptime.c
 *
 * 24 Sep 94	David L. Mills
 *	Tightened code at exits.
 *
 * 24 Mar 94	David L. Mills
 *	Revised syscall interface to include new variables for PPS
 *	time discipline.
 *
 * 14 Feb 94	David L. Mills
 *	Added code for external clock
 *
 * 28 Nov 93	David L. Mills
 *	Revised frequency scaling to conform with adjusted parameters
 *
 * 17 Sep 93	David L. Mills
 *	Created file
 */
/*
 * ntp_gettime(), ntp_adjtime() - precision time interface for SunOS
 * V4.1.1 and V4.1.3
 *
 * These routines consitute the Network Time Protocol (NTP) interfaces
 * for user and daemon application programs. The ntp_gettime() routine
 * provides the time, maximum error (synch distance) and estimated error
 * (dispersion) to client user application programs. The ntp_adjtime()
 * routine is used by the NTP daemon to adjust the system clock to an
 * externally derived time. The time offset and related variables set by
 * this routine are used by hardclock() to adjust the phase and
 * frequency of the phase-lock loop which controls the system clock.
 */
#include <sys/param.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/timex.h>

/*
 * The following variables are used by the hardclock() routine in the
 * kern_clock.c module and are described in that module. 
 */
extern struct timeval time;	/* kernel time variable */
extern int time_state;		/* clock state */
extern int time_status;		/* clock status bits */
extern long time_offset;	/* time adjustment (us) */
extern long time_freq;		/* frequency offset (scaled ppm) */
extern long time_maxerror;	/* maximum error (us) */
extern long time_esterror;	/* estimated error (us) */
extern long time_constant;	/* pll time constant */
extern long time_precision;	/* clock precision (us) */
extern long time_tolerance;	/* frequency tolerance (scaled ppm) */

#ifdef PPS_SYNC
/*
 * The following variables are used only if the PPS signal discipline
 * is configured in the kernel.
 */
extern int pps_shift;		/* interval duration (s) (shift) */
extern long pps_freq;		/* pps frequency offset (scaled ppm) */
extern long pps_jitter;		/* pps jitter (us) */
extern long pps_stabil;		/* pps stability (scaled ppm) */
extern long pps_jitcnt;		/* jitter limit exceeded */
extern long pps_calcnt;		/* calibration intervals */
extern long pps_errcnt;		/* calibration errors */
extern long pps_stbcnt;		/* stability limit exceeded */
#endif /* PPS_SYNC */

/*
 * ntp_gettime() - NTP user application interface
 */
ntp_gettime()
{
	register struct a {
		struct ntptimeval *tp;
	} *uap = (struct a *)u.u_ap;
	struct timeval atv;
	struct ntptimeval ntv;
	int s;

	if (uap->tp) {
		s = splclock();
#ifdef EXT_CLOCK
		/*
		 * The microtime() external clock routine returns a
		 * status code. If less than zero, we declare an error
		 * in the clock status word and return the kernel
		 * (software) time variable. While there are other
		 * places that call microtime(), this is the only place
		 * that matters from an application point of view.
		 */
		if (microtime(&atv) < 0) {
			time_status |= STA_CLOCKERR;
			ntv.time = time;
		} else
			time_status &= ~STA_CLOCKERR;
#else /* EXT_CLOCK */
		microtime(&atv);
#endif /* EXT_CLOCK */
		ntv.time = atv;
		ntv.maxerror = time_maxerror;
		ntv.esterror = time_esterror;
		(void) splx(s);

		u.u_error = copyout((caddr_t)&ntv, (caddr_t)uap->tp,
		    sizeof (ntv));
	}
	if (!u.u_error) {

		/*
		 * Status word error decode. If any of these conditions
		 * occur, an error is returned, instead of the status
		 * word. Most applications will care only about the fact
		 * the system clock may not be trusted, not about the
		 * details.
		 *
		 * Hardware or software error
		 */
		if ((time_status & (STA_UNSYNC | STA_CLOCKERR)) ||

		/*
		 * PPS signal lost when either time or frequency
		 * synchronization requested
		 */
		    (time_status & (STA_PPSFREQ | STA_PPSTIME) &&
		    !(time_status & STA_PPSSIGNAL)) ||

		/*
		 * PPS jitter exceeded when time synchronization
		 * requested
		 */
		    (time_status & STA_PPSTIME &&
		    time_status & STA_PPSJITTER) ||

		/*
		 * PPS wander exceeded or calibration error when
		 * frequency synchronization requested
		 */
		    (time_status & STA_PPSFREQ &&
		    time_status & (STA_PPSWANDER | STA_PPSERROR)))
			u.u_r.r_val1 = TIME_ERROR;
		else
			u.u_r.r_val1 = time_state;
	}
}

/*
 * ntp_adjtime() - NTP daemon application interface
 */
ntp_adjtime()
{
	register struct a {
		struct timex *tp;
	} *uap = (struct a *)u.u_ap;
	struct timex ntv;
	int modes;
	int s;

	u.u_error = copyin((caddr_t)uap->tp, (caddr_t)&ntv, sizeof(ntv));
	if (u.u_error)
		return;

	/*
	 * Update selected clock variables - only the superuser can
	 * change anything. Note that there is no error checking here on
	 * the assumption the superuser should know what it is doing.
	 */
	modes = ntv.modes;
	if (!suser() && modes != 0)
		return;
	s = splclock();
	if (modes & MOD_FREQUENCY)
#ifdef PPS_SYNC
		time_freq = ntv.freq - pps_freq;
#else /* PPS_SYNC */
		time_freq = ntv.freq;
#endif /* PPS_SYNC */
	if (modes & MOD_MAXERROR)
		time_maxerror = ntv.maxerror;
	if (modes & MOD_ESTERROR)
		time_esterror = ntv.esterror;
	if (modes & MOD_STATUS) {
		time_status &= STA_RONLY;
		time_status |= ntv.status & ~STA_RONLY;
	}
	if (modes & MOD_TIMECONST)
		time_constant = ntv.constant;
	if (modes & MOD_OFFSET)
		hardupdate(ntv.offset);

	/*
	 * Retrieve all clock variables
	 */
	if (time_offset < 0)
		ntv.offset = -(-time_offset >> SHIFT_UPDATE);
	else
		ntv.offset = time_offset >> SHIFT_UPDATE;
#ifdef PPS_SYNC
	ntv.freq = time_freq + pps_freq;
#else /* PPS_SYNC */
	ntv.freq = time_freq;
#endif /* PPS_SYNC */
	ntv.maxerror = time_maxerror;
	ntv.esterror = time_esterror;
	ntv.status = time_status;
	ntv.constant = time_constant;
	ntv.precision = time_precision;
	ntv.tolerance = time_tolerance;
#ifdef PPS_SYNC
	ntv.shift = pps_shift;
	ntv.ppsfreq = pps_freq;
	ntv.jitter = pps_jitter >> PPS_AVG;
	ntv.stabil = pps_stabil;
	ntv.calcnt = pps_calcnt;
	ntv.errcnt = pps_errcnt;
	ntv.jitcnt = pps_jitcnt;
	ntv.stbcnt = pps_stbcnt;
#endif /* PPS_SYNC */
	(void)splx(s);

	u.u_error = copyout((caddr_t)&ntv, (caddr_t)uap->tp,
	    sizeof(ntv));
	if (!u.u_error) {

		/*
		 * Status word error decode. See comments in
		 * ntp_gettime() routine.
		 */
		if ((time_status & (STA_UNSYNC | STA_CLOCKERR)) ||
		    (time_status & (STA_PPSFREQ | STA_PPSTIME) &&
		    !(time_status & STA_PPSSIGNAL)) ||
		    (time_status & STA_PPSTIME &&
		    time_status & STA_PPSJITTER) ||
		    (time_status & STA_PPSFREQ &&
		    time_status & (STA_PPSWANDER | STA_PPSERROR)))
			u.u_r.r_val1 = TIME_ERROR;
		else
			u.u_r.r_val1 = time_state;
	}
}
