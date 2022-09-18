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
 * $Log:	kern_clock.c,v $
 * Revision 2.18  89/09/05  20:40:12  jsb
 * 	Update mach_tv along with time, to support Mach time device.
 * 	[89/09/05  20:00:20  jsb]
 * 
 * Revision 2.17  89/05/30  10:32:00  rvb
 * 	Cleaned up a little the mips dependencies.
 * 	Removed inclusion of psl.h for both ibmrt and mips.
 * 	[89/04/19            af]
 * 
 * Revision 2.16  89/03/10  03:18:46  rpd
 * 	Moved kern/time_stamp.h to mach/.
 * 
 * Revision 2.15  89/03/09  19:28:08  rpd
 * 	More cleanup.
 * 
 * Revision 2.14  89/02/25  14:22:40  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.13  89/02/09  04:30:37  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.12  89/01/24  12:48:47  af
 * 	Merging problems...
 * 
 * Revision 2.11  89/01/23  22:02:28  af
 * 	Changes for I386: different {hard,soft}clock args AND
 * 	 do setsoftclock directly vs checking to see if a call is in order
 * 	[89/01/09            rvb]
 * 	
 * 	Added mods for Mips.  Included uniqtime(), for Mips only.
 * 	[89/01/07            af]
 * 
 * Revision 2.10  89/01/15  16:16:55  rpd
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  14:46:01  rpd]
 * 
 * Revision 2.9  89/01/12  07:38:41  rpd
 * 	Moved callout_statistics.h to mach_debug/;
 * 	made conditional on MACH_CO_STATS.
 * 	[89/01/12  06:38:03  rpd]
 * 	
 * 	Changed MACH_COSTATS to MACH_CO_STATS.
 * 	[89/01/12  04:26:27  rpd]
 * 
 * Revision 2.8  88/12/19  02:33:11  mwyoung
 * 	Removed lint.
 * 	[88/12/17            mwyoung]
 * 
 * Revision 2.7  88/09/25  22:07:24  rpd
 * 	Added callout_statistics_invariant() assertions.
 * 	[88/09/12  22:44:26  rpd]
 * 	
 * 	Added include of kern/callout_statistics.h.
 * 	[88/09/10  01:16:54  rpd]
 * 	
 * 	Added call-out statistics gathering.
 * 	[88/09/09  23:12:34  rpd]
 * 	
 * 	Fixed some includes.  Defined some variables which previously weren't
 * 	defined extern in sys/callout.h.
 * 	[88/09/09  04:38:46  rpd]
 * 
 * Revision 2.6  88/08/25  18:09:09  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Avoid hc warnings.
 * 	[88/08/11  18:41:18  mwyoung]
 * 
 * Revision 2.5  88/08/22  21:23:29  mja
 * 	More bug fixes from Brad White to allow adjtime() to work
 * 	better on the SUN3.
 * 	[88/08/22  13:03:38  mja]
 * 	
 * 	Fix to resync TODR to clock when adjust time delta expires.
 * 	[88/08/04  12:19:27  mja]
 * 
 * Revision 2.4  88/07/15  15:25:39  mja
 * Changed to include <sys/table.h> instead of <sys/syscalls.h> for
 * setmodes bit definitons.
 * 
 * 12-May-88  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: eliminate updates to otherwise unused proc structure
 *	fields: p_rssize, p_cpticks.
 *
 *  4-May-88  David Black (dlb) at Carnegie-Mellon University
 *	MACH_TIME_NEW is now standard.  Removed slow_clock.
 *	Get rid of u_ru.ru_{utime,stime}.  Autonice code removed
 *	for MACH_TIME_NEW (see schedcpu() in kern_synch.c).
 *	Replaced cpu_idle checks with check to see if current_thread()
 *	is an idle thread.
 *
 * 11-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added missing check for UMODE_NONICE mode bit in softclock() to
 *	disable auto-nice mechanism.
 *	[ V5.1(XF23) ]
 *
 * 29-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Removed use of "sys/vm.h".
 *
 * 29-Dec-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Define softclock as a function before it is used as an argument
 *	to softcall so that gcc will get the correct type.
 *
 * 21-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Simplified conditionals, purged history.
 *
 */

#include <simple_clock.h>
#include <stat_time.h>
#include <mach_co_stats.h>

#ifdef	hc
pragma off (optimize);
#endif	hc

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)kern_clock.c	7.1 (Berkeley) 6/5/86
 */

#include <machine/reg.h>
#ifdef	ibmrt
#include <ca/scr.h>
#endif	ibmrt
#if	!defined(romp) && !defined(mips)
#include <machine/psl.h>
#endif	!defined(romp) && !defined(mips)

#include <kern/assert.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dk.h>
#include <sys/callout.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <mach/time_stamp.h>
#include <sys/table.h>
#if	MACH_CO_STATS
#include <mach_debug/callout_statistics.h>
#endif	MACH_CO_STATS

#ifdef	i386
#include <i386/clock.h>
#endif	i386
#ifdef	vax
#include <vax/mtpr.h>
#include <vax/clock.h>
#endif	vax

#ifdef	balance
#include <machine/slic.h>
#include <machine/intctl.h>
#include <machine/clock.h>
#include <machine/hwparam.h>
#endif	balance

#ifdef	GPROF
#include <sys/gprof.h>
#endif	GPROF

#include <machine/cpu.h>

#include <kern/thread.h>
#include <mach/machine.h>
#include <kern/sched.h>
#include <mach/time_value.h>
#include <kern/timer.h>

decl_simple_lock_data(,callout_lock)

struct callout *callfree, *callout, calltodo;
int ncallout;

/*
 * Clock handling routines.
 *
 * This code is written to operate with two timers which run
 * independently of each other. The main clock, running at hz
 * times per second, is used to do scheduling and timeout calculations.
 * The second timer does resource utilization estimation statistically
 * based on the state of the machine phz times a second. Both functions
 * can be performed by a single clock (ie hz == phz), however the 
 * statistics will be much more prone to errors. Ideally a machine
 * would have separate clocks measuring time spent in user state, system
 * state, interrupt state, and idle state. These clocks would allow a non-
 * approximate measure of resource utilization.
 */

/*
 * TODO:
 *	time of day, system/user timing, timeouts, profiling on separate timers
 *	allocate more timeout table slots when table overflows.
 */
#define BUMPTIME(t, usec) { \
	extern struct timeval *mach_tv; \
	register struct timeval *tp = (t); \
 \
	tp->tv_usec += (usec); \
	if (tp->tv_usec >= 1000000) { \
		tp->tv_usec -= 1000000; \
		tp->tv_sec++; \
	} \
	if (mach_tv) *mach_tv = time; \
}

/*
 * The hz hardware interval timer.
 * We update the events relating to real time.
 * If this timer is also being used to gather statistics,
 * we run through the statistics gathering routine as well.
 */

#define NTICKS	1

#ifdef	i386
int	dotimein = 0;
#define setsoftclock()	(dotimein++)
#endif	i386

/*ARGSUSED*/
#ifdef	mips
hardclock(intr_frame)
	u_int *intr_frame;
#define ps intr_frame[EF_SR]
#endif	mips

#ifdef	ibmrt
hardclock(dev,ps,pc)
	register dev_t dev;
	caddr_t pc;
	int ps;
#endif	ibmrt

#ifdef	i386
hardclock(pc,ps,oldpri)
	int oldpri;
	caddr_t pc;
	int ps;
#endif	i386

#if	!defined(mips) && !defined(ibmrt) && !defined(i386)
hardclock(pc, ps)
	caddr_t pc;
	int ps;
#endif	!defined(mips) && !defined(ibmrt) && !defined(i386)
{
	register struct callout *p1;
	register thread_t	thread;
	register int s;
#if	SIMPLE_CLOCK
#define tick	myticks
	register int myticks;
#endif	SIMPLE_CLOCK

	int needsoft = 0;
	extern int tickdelta;
	extern long timedelta;
	extern int doresettodr;

#if	defined(ibmrt) && defined(lint)
	if (dev++) return;
#endif	defined(ibmrt) && defined(lint)

#ifdef	mips
	ackrtclock();
#endif	mips

	thread = current_thread();

#if	SIMPLE_CLOCK
	/*
	 *	Simple hardware timer does not restart on overflow, hence
	 *	interrupts do not happen at a constant rate.  Must call
	 *	machine-dependent routine to find out how much time has
	 *	elapsed since last interrupt.
	 */
	myticks = usec_elapsed();

	/*
	 *	NOTE: tick was #define'd to myticks above.
	 */
#endif	SIMPLE_CLOCK

#if	TS_FORMAT == 1
/*
 *	Increment the tick count for the timestamping routine.
 */
	ts_tick_count += NTICKS;
#endif	TS_FORMAT == 1

#if	STAT_TIME
	if (USERMODE(ps)) {
		timer_bump(&thread->user_timer, NTICKS*tick);
	}
	else {
		timer_bump(&thread->system_timer, NTICKS*tick);
	}
#endif	STAT_TIME

	if (thread->state & TH_IDLE) {
		clock_tick(NTICKS, CPU_STATE_IDLE);
	} else if (USERMODE(ps)) {
		clock_tick(NTICKS, CPU_STATE_USER);
	} else {
		clock_tick(NTICKS, CPU_STATE_SYSTEM);
	}
	if (cpu_number() != master_cpu) {
#ifdef	mips
		slave_hardclock(intr_frame);
#else	mips
		slave_hardclock(pc, ps);
#endif	mips
		return;
	}

	/*
	 * Update real-time timeout queue.
	 * At front of queue are some number of events which are ``due''.
	 * The time to these is <= 0 and if negative represents the
	 * number of ticks which have passed since it was supposed to happen.
	 * The rest of the q elements (times > 0) are events yet to happen,
	 * where the time for each is given as a delta from the previous.
	 * Decrementing just the first of these serves to decrement the time
	 * to all events.
	 */
	s = splhigh();
	simple_lock(&callout_lock);
	p1 = calltodo.c_next;
	while (p1) {
		if (--p1->c_time > 0)
			break;
		needsoft = 1;
		if (p1->c_time == 0)
			break;
		p1 = p1->c_next;
	}
	simple_unlock(&callout_lock);
	splx(s);

	/*
	 * Charge the time out based on the mode the cpu is in.
	 * Here again we fudge for the lack of proper interval timers
	 * assuming that the current state has been around at least
	 * one tick.
	 */
	if (USERMODE(ps)) {
		if (u.u_prof.pr_scale)
			needsoft = 1;
		/*
		 * CPU was in user state.  Increment
		 * user time counter, and process process-virtual time
		 * interval timer. 
		 */
		if (timerisset(&u.u_timer[ITIMER_VIRTUAL].it_value) &&
		    itimerdecr(&u.u_timer[ITIMER_VIRTUAL], tick) == 0)
			psignal(u.u_procp, SIGVTALRM);
	}

	/*
	 * If the cpu is currently scheduled to a process, then
	 * charge it with resource utilization for a tick, updating
	 * statistics which run in (user+system) virtual time,
	 * such as the cpu time limit and profiling timers.
	 * This assumes that the current process has been running
	 * the entire last tick.
	 */
	if (!(thread->state & TH_IDLE))
	{
		if (u.u_rlimit[RLIMIT_CPU].rlim_cur != RLIM_INFINITY) {
		    time_value_t	sys_time, user_time;

		    thread_read_times(thread, &user_time, &sys_time);
		    if ((sys_time.seconds + user_time.seconds + 1) >
		        u.u_rlimit[RLIMIT_CPU].rlim_cur) {
			psignal(u.u_procp, SIGXCPU);
			if (u.u_rlimit[RLIMIT_CPU].rlim_cur <
			    u.u_rlimit[RLIMIT_CPU].rlim_max)
				u.u_rlimit[RLIMIT_CPU].rlim_cur += 5;
			}
		}
		if (timerisset(&u.u_timer[ITIMER_PROF].it_value) &&
		    itimerdecr(&u.u_timer[ITIMER_PROF], tick) == 0)
			psignal(u.u_procp, SIGPROF);
	}


	/*
	 * If the alternate clock has not made itself known then
	 * we must gather the statistics.
	 */
	if (phz == 0)
#ifdef	mips
		gatherstats(intr_frame);
#else	mips
		gatherstats(pc, ps);
#endif	mips

	/*
	 * Increment the time-of-day, and schedule
	 * processing of the callouts at a very low cpu priority,
	 * so we don't keep the relatively high clock interrupt
	 * priority any longer than necessary.
	 */
	if (timedelta == 0)
		BUMPTIME(&time, tick)
	else {
		register delta;

		if (timedelta < 0) {
			delta = tick - tickdelta;
			timedelta += tickdelta;
		} else {
			delta = tick + tickdelta;
			timedelta -= tickdelta;
		}
		BUMPTIME(&time, delta);
		if (timedelta == 0 && doresettodr) {
			doresettodr = 0;
			resettodr();
		}
	}
	if (needsoft) {
#ifdef	i386
		setsoftclock();
#else	i386
		if (BASEPRI(ps)) 
		{
			/*
			 * Save the overhead of a software interrupt;
			 * it will happen as soon as we return, so do it now.
			 */
			(void) splsoftclock();
#if	defined(sun3) || defined(sun4)
			softclock(USERMODE(ps) != 0);
#endif	defined(sun3) || defined(sun4)
#if	defined(vax) || defined(ns32000) || defined(ibmrt)
			softclock(pc, ps);
#endif	defined(vax) || defined(ns32000) || defined(ibmrt)
#ifdef	mips
			softclock(intr_frame);
#endif	mips
		} else
#if	defined(sun3) || defined(sun4)
		{
			int softclock();
	                softcall(softclock, USERMODE(ps) != 0);
		}
#else	defined(sun3) || defined(sun4)
			setsoftclock();
#endif	defined(sun3) || defined(sun4)
#endif	i386
	}
}
#if	SIMPLE_CLOCK
#undef	tick
#endif	SIMPLE_CLOCK

int	dk_ndrive = DK_NDRIVE;
/*
 * Gather statistics on resource utilization.
 *
 * We make a gross assumption: that the system has been in the
 * state it is in (user state, kernel state, interrupt state,
 * or idle state) for the entire last time interval, and
 * update statistics accordingly.
 */
/*ARGSUSED*/
#ifdef	mips
gatherstats(intr_frame)
	u_int *intr_frame;
#else	mips
gatherstats(pc, ps)
	caddr_t pc;
	int ps;
#endif	mips
{
	register int cpstate, s;

	/*
	 * Determine what state the cpu is in.
	 */
#ifdef	mips
	if (phz)
		ackstatclock();
#endif	mips
	if (USERMODE(ps)) {
		/*
		 * CPU was in user state.
		 */
		if (u.u_procp->p_nice > NZERO)
			cpstate = CP_NICE;
		else
			cpstate = CP_USER;
	} else {
		/*
		 * CPU was in system state.  If profiling kernel
		 * increment a counter.  If no process is running
		 * then this is a system tick if we were running
		 * at a non-zero IPL (in a driver).  If a process is running,
		 * then we charge it with system time even if we were
		 * at a non-zero IPL, since the system often runs
		 * this way during processing of system calls.
		 * This is approximate, but the lack of true interval
		 * timers makes doing anything else difficult.
		 */
		cpstate = CP_SYS;
		if ((current_thread()->state & TH_IDLE) && BASEPRI(ps))
			cpstate = CP_IDLE;
#ifdef	GPROF
#ifdef	mips
		s = intr_frame[EF_EPC] - (u_int)s_lowpc;
 		if (profiling < 2 && s < s_textsize && phz)
 			{
 			char *k = (char *)kcount;
 			(*(u_int *)(k + ((s >> 3) << 2)))++;
 			}
#else	mips
		s = pc - s_lowpc;
		if (profiling < 2 && s < s_textsize)
			kcount[s / (HISTFRACTION * sizeof (*kcount))]++;
#endif	mips
#endif	GPROF
	}
	/*
	 * We maintain statistics shown by user-level statistics
	 * programs:  the amount of time in each cpu state, and
	 * the amount of time each of DK_NDRIVE ``drives'' is busy.
	 */
	cp_time[cpstate]++;
	for (s = 0; s < DK_NDRIVE; s++)
		if (dk_busy & (1 << s))
			dk_time[s]++;
}

/*
 * Software priority level clock interrupt.
 * Run periodic events from timeout queue.
 */
#if	defined(sun3) || defined(sun4)
softclock(was_user_mode)
	int	was_user_mode;
#endif	defined(sun3) || defined(sun4)

#ifdef	mips
softclock(intr_frame)
	u_int *intr_frame;
#endif	mips

#if	!defined(sun3) && !defined(sun4) && !defined(mips)
/*ARGSUSED*/
softclock(pc, ps)
	caddr_t pc;
	int ps;
#endif	!defined(sun3) && !defined(sun4) && !defined(mips)
{
#ifdef	mips
	acksoftclock();
#endif	mips

	for (;;) {
		register struct callout *p1;
		register caddr_t arg;
		register int (*func)();
		register int a, s;

		s = splhigh();
		simple_lock(&callout_lock);
		if ((p1 = calltodo.c_next) == 0 || p1->c_time > 0) {
			simple_unlock(&callout_lock);
			splx(s);
			break;
		}
		arg = p1->c_arg; func = p1->c_func; a = p1->c_time;
		calltodo.c_next = p1->c_next;
		p1->c_next = callfree;
		callfree = p1;
#if	MACH_CO_STATS
		assert(callout_statistics.cos_current_size > 0);
		callout_statistics.cos_num_softclock++;
		callout_statistics.cos_current_size--;
		callout_statistics.cos_cum_softclock_size +=
			callout_statistics.cos_current_size;
		assert(callout_statistics_invariant());
#endif	MACH_CO_STATS
		simple_unlock(&callout_lock);
		splx(s);
		(*func)(arg, a);
	}
	/*
	 * If trapped user-mode and profiling, give it
	 * a profiling tick.
	 */
#if	defined(sun3) || defined(sun4)
	if (was_user_mode) {
#else	defined(sun3) || defined(sun4)
	if (USERMODE(ps)) {
#endif	defined(sun3) || defined(sun4)
		register struct proc *p = u.u_procp;

		if (u.u_prof.pr_scale) {
			p->p_flag |= SOWEUPC;
			aston();
		}
	}
}

/*
 * Arrange that (*fun)(arg) is called in t/hz seconds.
 */
timeout(fun, arg, t)
	int (*fun)();
	caddr_t arg;
	register int t;
{
	register struct callout *p1, *p2, *pnew;
	register int s = splhigh();
#if	MACH_CO_STATS
	register int pos = 0;
#endif	MACH_CO_STATS

	simple_lock(&callout_lock);
	if (t <= 0)
		t = 1;
	pnew = callfree;
	if (pnew == NULL)
		panic("timeout table overflow");
	callfree = pnew->c_next;
	pnew->c_arg = arg;
	pnew->c_func = fun;
	for (p1 = &calltodo; (p2 = p1->c_next) && p2->c_time < t; p1 = p2) {
		if (p2->c_time > 0)
			t -= p2->c_time;
#if	MACH_CO_STATS
		pos++;
#endif	MACH_CO_STATS
	}
	p1->c_next = pnew;
	pnew->c_next = p2;
	pnew->c_time = t;
	if (p2)
		p2->c_time -= t;
#if	MACH_CO_STATS
	callout_statistics.cos_num_timeout++;
	callout_statistics.cos_cum_timeout_size +=
		callout_statistics.cos_current_size;
	callout_statistics.cos_cum_timeout_pos += pos;
	callout_statistics.cos_current_size++;
	assert(callout_statistics.cos_current_size > 0);
	assert(callout_statistics_invariant());
#endif	MACH_CO_STATS
	simple_unlock(&callout_lock);
	splx(s);
}

/*
 * untimeout is called to remove a function timeout call
 * from the callout structure.
 */
untimeout(fun, arg)
	int (*fun)();
	caddr_t arg;
{
	register struct callout *p1, *p2;
	register int s;
#if	MACH_CO_STATS
	register int pos = 0;
#endif	MACH_CO_STATS

	s = splhigh();
	simple_lock(&callout_lock);
#if	MACH_CO_STATS
	callout_statistics.cos_num_untimeout++;
#endif	MACH_CO_STATS
	for (p1 = &calltodo; (p2 = p1->c_next) != 0; p1 = p2) {
		if (p2->c_func == fun && p2->c_arg == arg) {
			if (p2->c_next && p2->c_time > 0)
				p2->c_next->c_time += p2->c_time;
			p1->c_next = p2->c_next;
			p2->c_next = callfree;
			callfree = p2;
#if	MACH_CO_STATS
			assert(callout_statistics.cos_current_size > 0);
			callout_statistics.cos_num_untimeout_hit++;
			callout_statistics.cos_current_size--;
			callout_statistics.cos_cum_untimeout_pos += pos;
#endif	MACH_CO_STATS
			break;
		}
#if	MACH_CO_STATS
		pos++;
#endif	MACH_CO_STATS
	}
#if	MACH_CO_STATS
	callout_statistics.cos_cum_untimeout_size +=
		callout_statistics.cos_current_size;
	assert(callout_statistics_invariant());
#endif	MACH_CO_STATS
	simple_unlock(&callout_lock);
	splx(s);
}

/*
 * Compute number of hz until specified time.
 * Used to compute third argument to timeout() from an
 * absolute time.
 */
hzto(tv)
	struct timeval *tv;
{
	register long ticks;
	register long sec;
	int s = splhigh();

	/*
	 * If number of milliseconds will fit in 32 bit arithmetic,
	 * then compute number of milliseconds to time and scale to
	 * ticks.  Otherwise just compute number of hz in time, rounding
	 * times greater than representible to maximum value.
	 *
	 * Delta times less than 25 days can be computed ``exactly''.
	 * Maximum value for any timeout in 10ms ticks is 250 days.
	 */
	sec = tv->tv_sec - time.tv_sec;
	if (sec <= 0x7fffffff / 1000 - 1000)
		ticks = ((tv->tv_sec - time.tv_sec) * 1000 +
			(tv->tv_usec - time.tv_usec) / 1000) / (tick / 1000);
	else if (sec <= 0x7fffffff / hz)
		ticks = sec * hz;
	else
		ticks = 0x7fffffff;
	splx(s);
	return (ticks);
}

profil()
{
	register struct a {
		short	*bufbase;
		unsigned bufsize;
		unsigned pcoffset;
		unsigned pcscale;
	} *uap = (struct a *)u.u_ap;
	register struct uuprof *upp = &u.u_prof;

	upp->pr_base = uap->bufbase;
	upp->pr_size = uap->bufsize;
	upp->pr_off = uap->pcoffset;
	upp->pr_scale = uap->pcscale;
}

#ifdef	COMPAT
opause()
{

	for (;;)
		sleep((caddr_t)&u, PSLEP);
}
#endif

