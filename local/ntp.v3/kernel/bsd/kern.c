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
 * Modification history kern.c
 *
 * 28 Sep 94	David L. Mills
 *	Added support for hybrid phase/frequency-lock loop.
 *
 * 18 Feb 94	David L. Mills
 *	Added PPS signal and external clock segments.
 *
 * 17 Sep 93    David L. Mills
 *      Created file
 */
/*
 * This program simulates a hybrid phase/frequency-lock loop using
 * actual code segments from modified kernel distributions for SunOS,
 * Ultrix and OSF/1 kernels. These segments involve no licensed code.
 *
 * Note: This program runs on Microsoft QuickC for Windows and IBM
 * compatibles. It runs on Unix systems when compiled with either cc or
 * gcc.
 */
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#ifndef MSDOS			/* Microsoft specific */
#include <sys/time.h>
#else /* MSDOS */
struct timeval {
	long tv_sec;
	long tv_usec;
};
#endif /* MSDOS */

/* #define PPS_SYNC		/* PPS frequency discipline option */
/* #define EXT_CLOCK		/* external clock option */

#include "timex.h"

/*
 * Simulation definitions
 *
 * The HZ define specifies the frequency of the CPU clock oscillator and
 * is normally defined in the system environment. The TAU define
 * specifies the PLL time constant, which is ordinarily set by the
 * synchronization daemon using the ntp_adjtime() system call. The POLL
 * define specifies the interval between updates, as determined by the
 * daemon.
 */
#define HZ 100			/* timer interrupt frequency (Hz) */
#define TAU 2			/* time constant (shift 0 - 6) */
#define POLL 64			/* interval between updates (s) */

/*
 * Phase/frequency-lock loop (PLL/FLL) definitions
 *
 * The following variables are read and set by the ntp_adjtime() system
 * call.
 *
 * time_state shows the state of the system clock, with values defined
 * in the timex.h header file.
 *
 * time_status shows the status of the system clock, with bits defined
 * in the timex.h header file.
 *
 * time_offset is used by the PLL/FLL to adjust the system time in small
 * increments.
 *
 * time_constant determines the bandwidth or "stiffness" of the PLL.
 *
 * time_tolerance determines maximum frequency error or tolerance of the
 * CPU clock oscillator and is a property of the architecture; however,
 * in principle it could change as result of the presence of external
 * discipline signals, for instance.
 *
 * time_precision is usually equal to the kernel tick variable; however,
 * in cases where a precision clock counter or external clock is
 * available, the resolution can be much less than this and depend on
 * whether the external clock is working or not.
 *
 * time_maxerror is initialized by a ntp_adjtime() call and increased by
 * the kernel once each second to reflect the maximum error bound
 * growth.
 *
 * time_esterror is set and read by the ntp_adjtime() call, but
 * otherwise not used by the kernel.
 */
int time_state = TIME_OK;	/* clock state */
int time_status = STA_UNSYNC;	/* clock status bits */
long time_offset = 0;		/* time offset (us) */
long time_constant = 0;		/* pll time constant */
long time_tolerance = MAXFREQ;	/* frequency tolerance (scaled ppm) */
long time_precision = 1;	/* clock precision (us) */
long time_maxerror = MAXPHASE;	/* maximum error (us) */
long time_esterror = MAXPHASE;	/* estimated error (us) */

/*
 * The following variables establish the state of the PLL/FLL and the
 * residual time and frequency offset of the local clock. The scale
 * factors are defined in the timex.h header file.
 *
 * time_phase and time_freq are the phase increment and the frequency
 * increment, respectively, of the kernel time variable.
 *
 * time_freq is set via ntp_adjtime() from a value stored in a file when
 * the synchronization daemon is first started. Its value is retrieved
 * via ntp_adjtime() and written to the file about once per hour by the
 * daemon.
 *
 * time_adj is the adjustment added to the value of tick at each timer
 * interrupt and is recomputed from time_phase and time_freq at each
 * seconds rollover.
 *
 * time_reftime is the second's portion of the system time at the last
 * call to ntp_adjtime(). It is used to adjust the time_freq variable
 * and to increase the time_maxerror as the time since last update
 * increases.
 */
long time_phase = 0;		/* phase offset (scaled us) */
long time_freq = 0;		/* frequency offset (scaled ppm) */
long time_adj = 0;		/* tick adjust (scaled 1 / hz) */
long time_reftime = 0;		/* time at last adjustment (s) */

#ifdef PPS_SYNC
/*
 * The following variables are used only if the kernel PPS discipline
 * code is configured (PPS_SYNC). The scale factors are defined in the
 * timex.h header file.
 *
 * pps_time contains the time at each calibration interval, as read by
 * microtime(). pps_count counts the seconds of the calibration
 * interval, the duration of which is nominally pps_shift in powers of
 * two.
 *
 * pps_offset is the time offset produced by the time median filter
 * pps_tf[], while pps_jitter is the dispersion (jitter) measured by
 * this filter.
 *
 * pps_freq is the frequency offset produced by the frequency median
 * filter pps_ff[], while pps_stabil is the dispersion (wander) measured
 * by this filter.
 *
 * pps_usec is latched from a high resolution counter or external clock
 * at pps_time. Here we want the hardware counter contents only, not the
 * contents plus the time_tv.usec as usual.
 *
 * pps_valid counts the number of seconds since the last PPS update. It
 * is used as a watchdog timer to disable the PPS discipline should the
 * PPS signal be lost.
 *
 * pps_glitch counts the number of seconds since the beginning of an
 * offset burst more than tick/2 from current nominal offset. It is used
 * mainly to suppress error bursts due to priority conflicts between the
 * PPS interrupt and timer interrupt.
 *
 * pps_intcnt counts the calibration intervals for use in the interval-
 * adaptation algorithm. It's just too complicated for words.
 */
struct timeval pps_time;	/* kernel time at last interval */
long pps_tf[] = {0, 0, 0};	/* pps time offset median filter (us) */
long pps_offset = 0;		/* pps time offset (us) */
long pps_jitter = MAXTIME;	/* time dispersion (jitter) (us) */
long pps_ff[] = {0, 0, 0};	/* pps frequency offset median filter */
long pps_freq = 0;		/* frequency offset (scaled ppm) */
long pps_stabil = MAXFREQ;	/* frequency dispersion (scaled ppm) */
long pps_usec = 0;		/* microsec counter at last interval */
long pps_valid = PPS_VALID;	/* pps signal watchdog counter */
int pps_glitch = 0;		/* pps signal glitch counter */
int pps_count = 0;		/* calibration interval counter (s) */
int pps_shift = PPS_SHIFT;	/* interval duration (s) (shift) */
int pps_intcnt = 0;		/* intervals at current duration */

/*
 * PPS signal quality monitors
 *
 * pps_jitcnt counts the seconds that have been discarded because the
 * jitter measured by the time median filter exceeds the limit MAXTIME
 * (100 us).
 *
 * pps_calcnt counts the frequency calibration intervals, which are
 * variable from 4 s to 256 s.
 *
 * pps_errcnt counts the calibration intervals which have been discarded
 * because the wander exceeds the limit MAXFREQ (100 ppm) or where the
 * calibration interval jitter exceeds two ticks.
 *
 * pps_stbcnt counts the calibration intervals that have been discarded
 * because the frequency wander exceeds the limit MAXFREQ / 4 (25 us).
 */
long pps_jitcnt = 0;		/* jitter limit exceeded */
long pps_calcnt = 0;		/* calibration intervals */
long pps_errcnt = 0;		/* calibration errors */
long pps_stbcnt = 0;		/* stability limit exceeded */
#endif /* PPS_SYNC */

#ifdef EXT_CLOCK
/*
 * External clock definitions
 *
 * The following definitions and declarations are used only if an
 * external clock is configured on the system.
 */
#define CLOCK_INTERVAL 30	/* CPU clock update interval (s) */

/*
 * The clock_count variable is set to CLOCK_INTERVAL at each PPS
 * interrupt and decremented once each second.
 */
int clock_count = 0;		/* CPU clock counter */

#ifdef HIGHBALL
/*
 * The clock_offset and clock_cpu variables are used by the HIGHBALL
 * interface. The clock_offset variable defines the offset between
 * system time and the HIGBALL counters. The clock_cpu variable contains
 * the offset between the system clock and the HIGHBALL clock for use in
 * disciplining the kernel time variable.
 */
extern struct timeval clock_offset; /* Highball clock offset */
long clock_cpu = 0;		/* CPU clock adjust */
#endif /* HIGHBALL */
#endif /* EXT_CLOCK */

/*
 * Function declarations
 */
#if defined(__GNUC__) || defined(MSDOS) /* for gcc and Microsoft C */
void hardupdate(long);
void hardclock(void);
void second_overflow(void);
void hardpps(struct timeval *, long);
int microtime(struct timeval *);
#else /* __GNUC__ */		/* for cc */
void hardupdate();
void hardclock();
void second_overflow();
void hardpps();
int microtime();
#endif /* __GNUC__ */

/*
 * Kernel variables
 */
static int hz = HZ;		/* CPU oscillator frequency (Hz) */
static int tick;		/* timer interrupt period (us) */
static int fixtick;		/* amortization constant (ppm) */
static struct timeval time;	/* kernel time variable */

/*
 * Simulation variables
 */
static double timey = 0;	/* simulation time (us) */
static long timez = 0;		/* current error (us) */
static long poll_interval = 0;	/* poll counter */

#ifdef PPS_SYNC
#define PPSFREQ -100		/* PPS offset frequency (ppm) */
static long ppsusec;		/* pps microseconds counter */
#endif /* PPS_SYNC */

/*
 * Simulation test program
 *
 * This program is designed to test the code segments actually used in
 * the kernel modifications for SunOS 4, Ultrix 4 and OSF/1. It includes
 * segments which support the PPS signal and external clocks (e.g.,
 * KSI/Odetics TPRO IRIG-B interface), but do not fully test the
 * functionality of the PPS signal or clock interfaces.
 */
void
main()
{

	tick = (int)(1000000 / hz);
	fixtick = (int)(1000000 % hz);
	time.tv_sec = 0;
	time.tv_usec = 512000;
/*
 	time_freq = 512L << SHIFT_USEC;
*/
	time_constant = TAU;
	time_status = STA_PLL | STA_FLL;
#ifdef PPS_SYNC
	ppsusec = 0;
	time_status |= STA_PPSFREQ;
#endif /* PPS_SYNC */
	printf("tick %d us, fixtick %d us\n", tick, fixtick);
	printf("  time  offset    freq  ppsofs  ppsfrq  cal  _offset    _freq     _adj\n");

	/*
	 * Grind the loop until ^C
	 */
	while (1) {
		timey += (double)(1000000) / hz;
		if (timey >= 1000000)
			timey -= 1000000;
		hardclock();
		if (time.tv_usec >= 1000000) {
			second_overflow();
#ifdef PPS_SYNC
			ppsusec += PPSFREQ;
			if (ppsusec >= tick)
				ppsusec -= tick;
			if (ppsusec < 0)
				ppsusec += tick;
			hardpps(&time, ppsusec);
#endif /* PPS_SYNC */
			poll_interval++;
			if (!(poll_interval % POLL)) {
				timez = (long)timey - time.tv_usec;
				if (timez > 500000)
					timez -= 1000000;
				if (timez < -500000)
					timez += 1000000;
				hardupdate(timez);
#ifdef PPS_SYNC
				printf("%6li%8li%8.3lf%8li%8.3lf %4i %08lx %08lx %08lx\n",
				    time.tv_sec, timez,
				    (double)time_freq / (1L <<
				    SHIFT_USEC), pps_offset,
				    (double)pps_freq / (1L <<
				    SHIFT_USEC), 1 << pps_shift,
				    time_offset, time_freq, time_adj);
#else /* PPS_SYNC */
				printf("%6li%8li%8.3lf%8li%8.3lf %4i %08lx %08lx %08lx\n",
				    time.tv_sec, timez,
				    (double)time_freq / (1L <<
				    SHIFT_USEC), 0L, 0., 0,
				    time_offset, time_freq, time_adj);
#endif /* PPS_SYNC */
			}
		}
	}
}

/*
 * This code fragment is inserted in the kernel hardclock() routine
 * where the kernel time variable is updated.
 */
void
hardclock()
{
	long ltemp, time_update;

	time_update = tick;		/* from preceding code */

	/*
	 * Beginning of precision-kernel code fragment
	 *
	 * Compute the phase adjustment. If the low-order bits
	 * (time_phase) of the update overflow, bump the high-order bits
	 * (time_update).
	 */
	time_phase += time_adj;
	if (time_phase <= -FINEUSEC) {
		ltemp = -time_phase >> SHIFT_SCALE;
		time_phase += ltemp << SHIFT_SCALE;
		time_update -= ltemp;
	}
	else if (time_phase >= FINEUSEC) {
		ltemp = time_phase >> SHIFT_SCALE;
		time_phase -= ltemp << SHIFT_SCALE;
		time_update += ltemp;
	}
	time.tv_usec += time_update;

#ifdef HIGHBALL
	/*
	 * If the HIGHBALL board is installed, we need to adjust the
	 * external clock offset in order to close the hardware feedback
	 * loop. This will adjust the external clock phase and frequency
	 * in small amounts. The additional phase noise and frequency
	 * wander this causes should be minimal. We also need to
	 * discipline the kernel time variable, since the PLL is used to
	 * discipline the external clock. If the Highball board is not
	 * present, we discipline kernel time with the PLL as usual. We
	 * assume that the external clock phase adjustment (time_update)
	 * and kernel phase adjustment (clock_cpu) are less than the
	 * value of tick.
	 */
	clock_offset.tv_usec += time_update;
	if (clock_offset.tv_usec >= 1000000) {
		clock_offset.tv_sec++;
		clock_offset.tv_usec -= 1000000;
	}
	if (clock_offset.tv_usec < 0) {
		clock_offset.tv_sec--;
		clock_offset.tv_usec += 1000000;
	}
	time.tv_usec += clock_cpu;
	clock_cpu = 0;
#else
	time.tv_usec += time_update;
#endif /* HIGHBALL */

	/*
	 * End of precision-kernel code fragment
	 */
}

/*
 * This code fragment is inserted in the kernel hardclock() routine at
 * the point where overflow of the microsecond field is tested.
 */
void
second_overflow()
{
	long ltemp;
#ifdef EXT_CLOCK
	struct timeval delta, clock_ext;
#endif /* EXT_CLOCK */

	/*
	 * Beginning of precision-kernel code fragment
	 *
	 * On rollover of the second the phase adjustment to be used for
	 * the next second is calculated. Also, the maximum error is
	 * increased by the tolerance. If the PPS frequency discipline
	 * code is present, the phase is increased to compensate for the
	 * CPU clock oscillator frequency error.
	 *
 	 * On a 32-bit machine and given parameters in the timex.h
	 * header file, the maximum phase adjustment is +-512 ms and
	 * maximum frequency offset is (a tad less than) +-512 ppm. On a
	 * 64-bit machine, you shouldn't need to ask.
	 */
	if (time.tv_usec >= 1000000) {
		time.tv_usec -= 1000000;
		time.tv_sec++;
		time_maxerror += time_tolerance >> SHIFT_USEC;

		/*
		 * Leap second processing. If in leap-insert state at
		 * the end of the day, the system clock is set back one
		 * second; if in leap-delete state, the system clock is
		 * set ahead one second. The microtime() routine or
		 * external clock driver will insure that reported time
		 * is always monotonic. The ugly divides should be
		 * replaced.
		 */
		switch (time_state) {

			case TIME_OK:
			if (time_status & STA_INS)
				time_state = TIME_INS;
			else if (time_status & STA_DEL)
				time_state = TIME_DEL;
			break;

			case TIME_INS:
			if (time.tv_sec % 86400 == 0) {
				time.tv_sec--;
				time_state = TIME_OOP;
			}
			break;

			case TIME_DEL:
			if ((time.tv_sec + 1) % 86400 == 0) {
				time.tv_sec++;
				time_state = TIME_WAIT;
			}
			break;

			case TIME_OOP:
			time_state = TIME_WAIT;
			break;

			case TIME_WAIT:
			if (!(time_status & (STA_INS | STA_DEL)))
				time_state = TIME_OK;
		}

		/*
		 * Compute the phase adjustment for the next second. In
		 * PLL mode, the offset is reduced by a fixed factor
		 * times the time constant. In FLL mode the offset is
		 * used directly. In either mode, the maximum phase
		 * adjustment for each second is clamped so as to spread
		 * the adjustment over not more than the number of
		 * seconds between updates.
		 */
		if (time_offset < 0) {
			ltemp = -time_offset;
			if (!(time_status & STA_FLL))
				ltemp >>= SHIFT_KG + time_constant;
			if (ltemp > (MAXPHASE / MINSEC) << SHIFT_UPDATE)
				ltemp = (MAXPHASE / MINSEC) <<
				    SHIFT_UPDATE;
			time_offset += ltemp;
			time_adj = -ltemp << (SHIFT_SCALE - SHIFT_HZ -
			    SHIFT_UPDATE);
		} else {
			ltemp = time_offset;
			if (!(time_status & STA_FLL))
				ltemp >>= SHIFT_KG + time_constant;
			if (ltemp > (MAXPHASE / MINSEC) << SHIFT_UPDATE)
				ltemp = (MAXPHASE / MINSEC) <<
				    SHIFT_UPDATE;
			time_offset -= ltemp;
			time_adj = ltemp << (SHIFT_SCALE - SHIFT_HZ -
			    SHIFT_UPDATE);
		}

		/*
		 * Compute the frequency estimate and additional phase
		 * adjustment due to frequency error for the next
		 * second. When the PPS signal is engaged, gnaw on the
		 * watchdog counter and update the frequency computed by
		 * the pll and the PPS signal.
		 */
#ifdef PPS_SYNC
		pps_valid++;
		if (pps_valid == PPS_VALID) {
			pps_jitter = MAXTIME;
			pps_stabil = MAXFREQ;
			time_status &= ~(STA_PPSSIGNAL | STA_PPSJITTER |
			    STA_PPSWANDER | STA_PPSERROR);
		}
		ltemp = time_freq + pps_freq;
#else
		ltemp = time_freq;
#endif /* PPS_SYNC */
		if (ltemp < 0)
			time_adj -= -ltemp >>
			    (SHIFT_USEC + SHIFT_HZ - SHIFT_SCALE);
		else
			time_adj += ltemp >>
			    (SHIFT_USEC + SHIFT_HZ - SHIFT_SCALE);
		time_adj += (long)fixtick << (SHIFT_SCALE - SHIFT_HZ);

#if SHIFT_HZ == 7
		/*
		 * When the CPU clock oscillator frequency is not a
		 * power of 2 in Hz, the SHIFT_HZ is only an approximate
		 * scale factor. In the SunOS kernel, this results in a
		 * PLL gain factor of 1/1.28 = 0.78 what it should be.
		 * In the following code the overall gain is increased
		 * by a factor of 1.25, which results in a residual
		 * error less than 3 percent.
		 */
		if (hz == 100) {
			if (time_adj < 0)
				time_adj -= -time_adj >> 2;
			else
				time_adj += time_adj >> 2;
		}
#endif /* SHIFT_HZ */

#ifdef EXT_CLOCK
		/*
		 * If an external clock is present, it is necessary to
		 * discipline the kernel time variable anyway, since not
		 * all system components use the microtime() interface.
		 * Here, the time offset between the external clock and
		 * kernel time variable is computed every so often.
		 */
		clock_count++;
		if (clock_count > CLOCK_INTERVAL) {
			clock_count = 0;
			microtime(&clock_ext);
			delta.tv_sec = clock_ext.tv_sec - time.tv_sec;
			delta.tv_usec = clock_ext.tv_usec -
			    time.tv_usec;
			if (delta.tv_usec < 0)
				delta.tv_sec--;
			if (delta.tv_usec >= 500000) {
				delta.tv_usec -= 1000000;
				delta.tv_sec++;
			}
			if (delta.tv_usec < -500000) {
				delta.tv_usec += 1000000;
				delta.tv_sec--;
			}
			if (delta.tv_sec > 0 || (delta.tv_sec == 0 &&
			    delta.tv_usec > MAXPHASE) ||
			    delta.tv_sec < -1 || (delta.tv_sec == -1 &&
			    delta.tv_usec < -MAXPHASE)) {
				time = clock_ext;
				delta.tv_sec = 0;
				delta.tv_usec = 0;
			}
#ifdef HIGHBALL 
			clock_cpu = delta.tv_usec;
#else /* HIGHBALL */
			hardupdate(delta.tv_usec);
#endif /* HIGHBALL */
		}
#endif /* EXT_CLOCK */
	}

	/*
	 * End of precision-kernel code fragment
	 */
}

/*
 * hardupdate() - local clock update
 *
 * This routine is called by ntp_adjtime() to update the local clock
 * phase and frequency. The implementation is of an adaptive-parameter,
 * hybrid phase/frequency-lock loop (PLL/FLL). The routine computes new
 * time and frequency offset estimates for each call. If the kernel PPS
 * discipline code is configured (PPS_SYNC), the PPS signal itself
 * determines the new time offset, instead of the calling argument.
 * Presumably, calls to ntp_adjtime() occur only when the caller
 * believes the local clock is valid within some bound (+-128 ms with
 * NTP). If the caller's time is far different than the PPS time, an
 * argument will ensue, and it's not clear who will lose.
 *
 * For uncompensated quartz crystal oscillatores and nominal update
 * intervals less than 1024 s, operation should be in phase-lock mode
 * (STA_FLL = 0), where the loop is disciplined to phase. For update
 * intervals greater than thiss, operation should be in frequency-lock
 * mode (STA_FLL = 1), where the loop is disciplined to frequency.
 *
 * Note: splclock() is in effect.
 */
void
hardupdate(offset)
	long offset;
{
	long ltemp, mtemp;

	if (!(time_status & STA_PLL) && !(time_status & STA_PPSTIME))
		return;
	ltemp = offset;
#ifdef PPS_SYNC
	if (time_status & STA_PPSTIME && time_status & STA_PPSSIGNAL)
		ltemp = pps_offset;
#endif /* PPS_SYNC */

	/*
	 * Scale the phase adjustment and clamp to the operating range.
	 */
	if (ltemp > MAXPHASE)
		time_offset = MAXPHASE << SHIFT_UPDATE;
	else if (ltemp < -MAXPHASE)
		time_offset = -(MAXPHASE << SHIFT_UPDATE);
	else
		time_offset = ltemp << SHIFT_UPDATE;

	/*
	 * Select whether the frequency is to be controlled and in which
	 * mode (PLL or FLL). Clamp to the operating range. Ugly
	 * multiply/divide should be replaced someday.
	 */
	if (time_status & STA_FREQHOLD || time_reftime == 0)
		time_reftime = time.tv_sec;
	mtemp = time.tv_sec - time_reftime;
	time_reftime = time.tv_sec;
	if (time_status & STA_FLL) {
		if (mtemp >= MINSEC) {
			ltemp = ((time_offset / mtemp) << (SHIFT_USEC -
			    SHIFT_UPDATE)) - time_freq;
			if (ltemp < 0)
				time_freq -= -ltemp >> SHIFT_KH;
			else
				time_freq += ltemp >> SHIFT_KH;
		}
	} else {
		if (mtemp < MAXSEC) {
			ltemp *= mtemp;
			if (ltemp < 0)
				time_freq -= -ltemp >> (time_constant +
				    time_constant + SHIFT_KF -
				    SHIFT_USEC);
			else
				time_freq += ltemp >> (time_constant +
				    time_constant + SHIFT_KF -
				    SHIFT_USEC);
		}
	}
	if (time_freq > time_tolerance)
		time_freq = time_tolerance;
	else if (time_freq < -time_tolerance)
		time_freq = -time_tolerance;
}

#ifdef PPS_SYNC
/*
 * hardpps() - discipline CPU clock oscillator to external PPS signal
 *
 * This routine is called at each PPS interrupt in order to discipline
 * the CPU clock oscillator to the PPS signal. It measures the PPS phase
 * and leaves it in a handy spot for the hardclock() routine. It
 * integrates successive PPS phase differences and calculates the
 * frequency offset. This is used in hardclock() to discipline the CPU
 * clock oscillator so that intrinsic frequency error is cancelled out.
 * The code requires the caller to capture the time and hardware counter
 * value at the on-time PPS signal transition.
 *
 * Note that, on some Unix systems, this routine runs at an interrupt
 * priority level higher than the timer interrupt routine hardclock().
 * Therefore, the variables used are distinct from the hardclock()
 * variables, except for certain exceptions: The PPS frequency pps_freq
 * and phase pps_offset variables are determined by this routine and
 * updated atomically. The time_tolerance variable can be considered a
 * constant, since it is infrequently changed, and then only when the
 * PPS signal is disabled. The watchdog counter pps_valid is updated
 * once per second by hardclock() and is atomically cleared in this
 * routine.
 */
void
hardpps(tvp, usec)
	struct timeval *tvp;		/* time at PPS */
	long usec;			/* hardware counter at PPS */
{
	long u_usec, v_usec, bigtick;
	long cal_sec, cal_usec;

	/*
	 * An occasional glitch can be produced when the PPS interrupt
	 * occurs in the hardclock() routine before the time variable is
	 * updated. Here the offset is discarded when the difference
	 * between it and the last one is greater than tick/2, but not
	 * if the interval since the first discard exceeds 30 s.
	 */
	time_status |= STA_PPSSIGNAL;
	time_status &= ~(STA_PPSJITTER | STA_PPSWANDER | STA_PPSERROR);
	pps_valid = 0;
	u_usec = -tvp->tv_usec;
	if (u_usec < -500000)
		u_usec += 1000000;
	v_usec = pps_offset - u_usec;
	if (v_usec < 0)
		v_usec = -v_usec;
	if (v_usec > (tick >> 1)) {
		if (pps_glitch > MAXGLITCH) {
			pps_glitch = 0;
			pps_tf[2] = u_usec;
			pps_tf[1] = u_usec;
		} else {
			pps_glitch++;
			u_usec = pps_offset;
		}
	} else
		pps_glitch = 0;

	/*
	 * A three-stage median filter is used to help deglitch the pps
	 * time. The median sample becomes the time offset estimate; the
	 * difference between the other two samples becomes the time
	 * dispersion (jitter) estimate.
	 */
	pps_tf[2] = pps_tf[1];
	pps_tf[1] = pps_tf[0];
	pps_tf[0] = u_usec;
	if (pps_tf[0] > pps_tf[1]) {
		if (pps_tf[1] > pps_tf[2]) {
			pps_offset = pps_tf[1];		/* 0 1 2 */
			v_usec = pps_tf[0] - pps_tf[2];
		} else if (pps_tf[2] > pps_tf[0]) {
			pps_offset = pps_tf[0];		/* 2 0 1 */
			v_usec = pps_tf[2] - pps_tf[1];
		} else {
			pps_offset = pps_tf[2];		/* 0 2 1 */
			v_usec = pps_tf[0] - pps_tf[1];
		}
	} else {
		if (pps_tf[1] < pps_tf[2]) {
			pps_offset = pps_tf[1];		/* 2 1 0 */
			v_usec = pps_tf[2] - pps_tf[0];
		} else  if (pps_tf[2] < pps_tf[0]) {
			pps_offset = pps_tf[0];		/* 1 0 2 */
			v_usec = pps_tf[1] - pps_tf[2];
		} else {
			pps_offset = pps_tf[2];		/* 1 2 0 */
			v_usec = pps_tf[1] - pps_tf[0];
		}
	}
	if (v_usec > MAXTIME)
		pps_jitcnt++;
	v_usec = (v_usec << PPS_AVG) - pps_jitter;
	if (v_usec < 0)
		pps_jitter -= -v_usec >> PPS_AVG;
	else
		pps_jitter += v_usec >> PPS_AVG;
	if (pps_jitter > (MAXTIME >> 1))
		time_status |= STA_PPSJITTER;

	/*
	 * During the calibration interval adjust the starting time when
	 * the tick overflows. At the end of the interval compute the
	 * duration of the interval and the difference of the hardware
	 * counters at the beginning and end of the interval. This code
	 * is deliciously complicated by the fact valid differences may
	 * exceed the value of tick when using long calibration
	 * intervals and small ticks. Note that the counter can be
	 * greater than tick if caught at just the wrong instant, but
	 * the values returned and used here are correct.
	 */
	bigtick = (long)tick << SHIFT_USEC;
	pps_usec -= pps_freq;
	if (pps_usec >= bigtick)
		pps_usec -= bigtick;
	if (pps_usec < 0)
		pps_usec += bigtick;
	pps_time.tv_sec++;
	pps_count++;
	if (pps_count < (1 << pps_shift))
		return;
	pps_count = 0;
	pps_calcnt++;
	u_usec = usec << SHIFT_USEC;
	v_usec = pps_usec - u_usec;
	if (v_usec >= bigtick >> 1)
		v_usec -= bigtick;
	if (v_usec < -(bigtick >> 1))
		v_usec += bigtick;
	if (v_usec < 0)
		v_usec = -(-v_usec >> pps_shift);
	else
		v_usec = v_usec >> pps_shift;
	pps_usec = u_usec;
	cal_sec = tvp->tv_sec;
	cal_usec = tvp->tv_usec;
	cal_sec -= pps_time.tv_sec;
	cal_usec -= pps_time.tv_usec;
	if (cal_usec < 0) {
		cal_usec += 1000000;
		cal_sec--;
	}
	pps_time = *tvp;

	/*
	 * Check for lost interrupts, noise, excessive jitter and
	 * excessive frequency error. The number of timer ticks during
	 * the interval may vary +-1 tick. Add to this a margin of one
	 * tick for the PPS signal jitter and maximum frequency
	 * deviation. If the limits are exceeded, the calibration
	 * interval is reset to the minimum and we start over.
	 */
	u_usec = (long)tick << 1;
	if (!((cal_sec == -1 && cal_usec > (1000000 - u_usec))
	    || (cal_sec == 0 && cal_usec < u_usec))
	    || v_usec > time_tolerance || v_usec < -time_tolerance) {
		pps_errcnt++;
		pps_shift = PPS_SHIFT;
		pps_intcnt = 0;
		time_status |= STA_PPSERROR;
		return;
	}

	/*
	 * A three-stage median filter is used to help deglitch the pps
	 * frequency. The median sample becomes the frequency offset
	 * estimate; the difference between the other two samples
	 * becomes the frequency dispersion (stability) estimate.
	 */
	pps_ff[2] = pps_ff[1];
	pps_ff[1] = pps_ff[0];
	pps_ff[0] = v_usec;
	if (pps_ff[0] > pps_ff[1]) {
		if (pps_ff[1] > pps_ff[2]) {
			u_usec = pps_ff[1];		/* 0 1 2 */
			v_usec = pps_ff[0] - pps_ff[2];
		} else if (pps_ff[2] > pps_ff[0]) {
			u_usec = pps_ff[0];		/* 2 0 1 */
			v_usec = pps_ff[2] - pps_ff[1];
		} else {
			u_usec = pps_ff[2];		/* 0 2 1 */
			v_usec = pps_ff[0] - pps_ff[1];
		}
	} else {
		if (pps_ff[1] < pps_ff[2]) {
			u_usec = pps_ff[1];		/* 2 1 0 */
			v_usec = pps_ff[2] - pps_ff[0];
		} else  if (pps_ff[2] < pps_ff[0]) {
			u_usec = pps_ff[0];		/* 1 0 2 */
			v_usec = pps_ff[1] - pps_ff[2];
		} else {
			u_usec = pps_ff[2];		/* 1 2 0 */
			v_usec = pps_ff[1] - pps_ff[0];
		}
	}

	/*
	 * Here the frequency dispersion (stability) is updated. If it
	 * is less than one-fourth the maximum (MAXFREQ), the frequency
	 * offset is updated as well, but clamped to the tolerance. It
	 * will be processed later by the hardclock() routine.
	 */
	v_usec = (v_usec >> 1) - pps_stabil;
	if (v_usec < 0)
		pps_stabil -= -v_usec >> PPS_AVG;
	else
		pps_stabil += v_usec >> PPS_AVG;
	if (pps_stabil > MAXFREQ >> 2) {
		pps_stbcnt++;
		time_status |= STA_PPSWANDER;
		return;
	}
	if (time_status & STA_PPSFREQ) {
		if (u_usec < 0) {
			pps_freq -= -u_usec >> PPS_AVG;
			if (pps_freq < -time_tolerance)
				pps_freq = -time_tolerance;
			u_usec = -u_usec;
		} else {
			pps_freq += u_usec >> PPS_AVG;
			if (pps_freq > time_tolerance)
				pps_freq = time_tolerance;
		}
	}

	/*
	 * Here the calibration interval is adjusted. If the maximum
	 * time difference is greater than tick / 4, reduce the interval
	 * by half. If this is not the case for four consecutive
	 * intervals, double the interval.
	 */
	if (u_usec << pps_shift > bigtick >> 2) {
		pps_intcnt = 0;
		if (pps_shift > PPS_SHIFT)
			pps_shift--;
	} else if (pps_intcnt >= 4) {
		pps_intcnt = 0;
		if (pps_shift < PPS_SHIFTMAX)
			pps_shift++;
	} else
		pps_intcnt++;
}
#endif /* PPS_SYNC */

#if defined(PPS_SYNC) || defined(EXT_CLOCK)
/*
 * microtime() - get system time with microsecond resolution
 *
 * This routine is called by the gettimeofday() system call and certain
 * other routings. It is implemented here only as a dummy routine.
 */
int microtime(tvp)
	struct timeval *tvp;
{
	*tvp = time;
	return (0);
}
#endif /* PPS_SYNC EXT_CLOCK */
