h23191
s 00001/00000/00420
d D 8.3 95/01/09 18:27:11 cgd 22 21
c microtime returns void
e
s 00001/00000/00419
d D 8.2 94/01/12 09:38:50 bostic 21 20
c lint
e
s 00002/00002/00417
d D 8.1 93/06/10 21:40:26 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00031/00025/00388
d D 7.19 93/02/18 21:17:14 hibler 19 18
c two significant fixes:
c 1. clock was losing time due to microtime implementation
c    (reading SR followed by reading timer value would clear any pending INT)
c 2. stat timer was running slow
c    (significant time elapsed between INT and reload of timer)
e
s 00001/00001/00412
d D 7.18 93/01/19 13:08:32 hibler 18 17
c properly scale value read from HW in microtime
e
s 00002/00004/00411
d D 7.17 92/12/27 09:44:27 hibler 17 16
c stat clock interrupt cleared in locore
e
s 00007/00007/00408
d D 7.16 92/10/11 09:42:30 bostic 16 15
c make kernel includes standard
e
s 00001/00001/00414
d D 7.15 92/09/21 21:26:41 hibler 15 14
c gprof.h -> gmon.h
e
s 00146/00288/00269
d D 7.14 92/07/08 01:17:03 torek 14 13
c delete mmap'ed clock; new clock handling
e
s 00001/00001/00556
d D 7.13 92/06/23 17:11:55 mckusick 13 12
c MAP_FILE is now the default
e
s 00024/00046/00533
d D 7.12 92/06/20 11:53:34 mckusick 12 11
c initprofclock now told whether profiling is happening
e
s 00003/00002/00576
d D 7.11 92/06/05 15:36:56 hibler 11 10
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00577
d D 7.10 92/05/14 15:24:09 heideman 10 9
c include reordering due to vn_if change
e
s 00001/00001/00577
d D 7.9 92/05/04 15:58:40 mckusick 9 8
c lint inspired bug fix
e
s 00005/00000/00573
d D 7.8 92/02/25 17:14:13 mckusick 8 7
c calculate hz, tick, and profhz
e
s 00002/00002/00571
d D 7.7 92/02/17 21:16:35 mckusick 7 6
c fix up syntax errors
e
s 00006/00010/00567
d D 7.6 91/05/07 09:59:48 hibler 6 5
c DIO-II support
e
s 00022/00017/00555
d D 7.5 91/04/20 17:22:48 karels 5 4
c new proc structure, fix includes
e
s 00016/00016/00556
d D 7.4 90/12/16 16:35:57 bostic 4 3
c kernel reorg
e
s 00031/00060/00541
d D 7.3 90/12/05 18:53:29 mckusick 3 2
c update from Mike Hibler for new VM and other machine support
e
s 00014/00014/00587
d D 7.2 90/06/22 09:33:07 hibler 2 1
c get rid of u_error uses
e
s 00601/00000/00000
d D 7.1 90/05/08 18:09:06 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 20
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 6
 * from: Utah $Hdr: clock.c 1.17 89/11/30$
E 6
I 6
 * from: Utah $Hdr: clock.c 1.18 91/01/21$
E 6
 *
 *	%W% (Berkeley) %G%
 */

I 19
/*
 * HPs use the MC6840 PTM with the following arrangement:
 *	Timers 1 and 3 are externally driver from a 25Mhz source.
 *	Output from timer 3 is tied to the input of timer 2.
 * The latter makes it possible to use timers 3 and 2 together to get
 * a 32-bit countdown timer.
 */

E 19
D 4
#include "param.h"
#include "user.h"
#include "kernel.h"
#include "../hpdev/hilreg.h"
E 4
I 4
D 5
#include "sys/param.h"
#include "sys/user.h"
#include "sys/kernel.h"
E 5
I 5
D 16
#include "param.h"
#include "kernel.h"
E 5
D 11
#include "../dev/hilreg.h"
E 11
I 11
#include "hp/dev/hilreg.h"
E 11
E 4
#include "clockreg.h"
E 16
I 16
#include <sys/param.h>
#include <sys/kernel.h>
#include <hp/dev/hilreg.h>
#include <hp300/hp300/clockreg.h>
E 16

I 5
D 6
#include "vm/vm.h"
E 6
E 5
D 4
#include "machine/psl.h"
#include "machine/cpu.h"
E 4
I 4
D 16
#include "../include/psl.h"
#include "../include/cpu.h"
E 16
I 16
#include <machine/psl.h>
#include <machine/cpu.h>
E 16
E 4

D 14
#if defined(GPROF) && defined(PROFTIMER)
E 14
I 14
#ifdef GPROF
E 14
D 4
#include "gprof.h"
E 4
I 4
D 15
#include "sys/gprof.h"
E 15
I 15
D 16
#include "sys/gmon.h"
E 16
I 16
#include <sys/gmon.h>
E 16
E 15
E 4
#endif

D 3
int    clkstd[] = { IOV(0x5F8000) };
E 3
I 3
int    clkstd[1];
I 8
D 14
int    profhz;
E 14
E 8
E 3

I 14
static int clkint;		/* clock interval, as loaded */
/*
 * Statistics clock interval and variance, in usec.  Variance must be a
 * power of two.  Since this gives us an even number, not an odd number,
 * we discard one case and compensate.  That is, a variance of 1024 would
 * give us offsets in [0..1023].  Instead, we take offsets in [1..1023].
 * This is symmetric about the point 512, or statvar/2, and thus averages
 * to that value (assuming uniform random numbers).
 */
static int statvar = 1024 / 4;	/* {stat,prof}clock variance */
static int statmin;		/* statclock interval - variance/2 */
static int profmin;		/* profclock interval - variance/2 */
static int timer3min;		/* current, from above choices */
I 19
static int statprev;		/* previous value in stat timer */
E 19

E 14
static int month_days[12] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
struct bbc_tm *gmt_to_bbc();
u_char bbc_registers[13];
u_char write_bbc_reg(), read_bbc_reg();
struct hil_dev *bbcaddr = NULL;

/*
 * Machine-dependent clock routines.
 *
D 14
 * Startrtclock restarts the real-time clock, which provides
 * hardclock interrupts to kern_clock.c.
 *
 * Inittodr initializes the time of day hardware which provides
 * date functions.
 *
 * Resettodr restores the time of day hardware after a time change.
 *
E 14
 * A note on the real-time clock:
D 14
 * We actually load the clock with CLK_INTERVAL-1 instead of CLK_INTERVAL.
E 14
I 14
 * We actually load the clock with interval-1 instead of interval.
E 14
 * This is because the counter decrements to zero after N+1 enabled clock
 * periods where N is the value loaded into the counter.
I 14
 *
 * The frequencies of the HP300 clocks must be a multiple of four
 * microseconds (since the clock counts in 4 us units).
E 14
 */
I 14
#define	COUNTS_PER_SEC	(1000000 / CLK_RESOLUTION)
E 14

/*
D 14
 * Start the real-time clock.
E 14
I 14
 * Set up the real-time and statistics clocks.  Leave stathz 0 only if
 * no alternative timer is available.
 *
E 14
 */
D 14
startrtclock()
E 14
I 14
cpu_initclocks()
E 14
{
D 3
	register struct clkreg *clk = (struct clkreg *)clkstd[0];
E 3
I 3
D 14
	register struct clkreg *clk;
E 14
I 14
	register volatile struct clkreg *clk;
	register int intvl, statint, profint, minint;
E 14
E 3

I 3
D 6
	clkstd[0] = IOV(0x5F8000);
E 6
I 6
D 14
	clkstd[0] = IIOV(0x5F8000);
E 6
	clk = (struct clkreg *) clkstd[0];
E 14
I 14
	clkstd[0] = IIOV(0x5F8000);		/* XXX grot */
	clk = (volatile struct clkreg *)clkstd[0];
E 14

E 3
D 14
	clk->clk_cr2 = CLK_CR1;
	clk->clk_cr1 = CLK_RESET;
	clk->clk_cr2 = CLK_CR3;
	clk->clk_cr3 = 0;
	clk->clk_msb1 = (CLK_INTERVAL-1) >> 8 & 0xFF;
	clk->clk_lsb1 = (CLK_INTERVAL-1) & 0xFF;
	clk->clk_msb2 = 0;
	clk->clk_lsb2 = 0;
	clk->clk_msb3 = 0;
	clk->clk_lsb3 = 0;
	clk->clk_cr2 = CLK_CR1;
	clk->clk_cr1 = CLK_IENAB;
I 8

	tick = CLK_INTERVAL * CLK_RESOLUTION;
	hz = 1000000 / (CLK_INTERVAL * CLK_RESOLUTION);
E 8
}

/*
 * Returns number of usec since last recorded clock "tick"
 * (i.e. clock interrupt).
 */
clkread()
{
	register struct clkreg *clk = (struct clkreg *) clkstd[0];
	register int high, low;

	high = clk->clk_msb1;
	low = clk->clk_lsb1;
	if (high != clk->clk_msb1)
		high = clk->clk_msb1;

	high = (CLK_INTERVAL-1) - ((high << 8) | low);
E 14
I 14
	if (COUNTS_PER_SEC % hz) {
		printf("cannot get %d Hz clock; using 100 Hz\n", hz);
		hz = 100;
	}
E 14
	/*
D 14
	 * Pending interrupt indicates that the counter has wrapped
	 * since we went to splhigh().  Need to compensate.
E 14
I 14
	 * Clock has several counters, so we can always use separate
	 * statclock.
E 14
	 */
D 14
	if (clk->clk_sr & CLK_INT1)
		high += CLK_INTERVAL;
	return((high * tick) / CLK_INTERVAL);
}

#include "clock.h"
#if NCLOCK > 0
/*
 * /dev/clock: mappable high resolution timer.
 *
 * This code implements a 32-bit recycling counter (with a 4 usec period)
 * using timers 2 & 3 on the 6840 clock chip.  The counter can be mapped
 * RO into a user's address space to achieve low overhead (no system calls),
 * high-precision timing.
 *
 * Note that timer 3 is also used for the high precision profiling timer
 * (PROFTIMER code above).  Care should be taken when both uses are
 * configured as only a token effort is made to avoid conflicting use.
 */
D 4
#include "proc.h"
#include "ioctl.h"
D 3
#include "mapmem.h"
E 3
#include "malloc.h"
E 4
I 4
#include "sys/proc.h"
I 6
#include "sys/resourcevar.h"
E 6
#include "sys/ioctl.h"
#include "sys/malloc.h"
I 6
#include "vm/vm.h"
E 6
E 4
#include "clockioctl.h"
I 3
D 4
#include "../vm/vm_param.h"
#include "../vm/vm_pager.h"
#include "../vm/vm_prot.h"
#include "specdev.h"
#include "vnode.h"
#include "mman.h"
E 4
I 4
D 6
#include "vm/vm_param.h"
#include "vm/vm_pager.h"
#include "vm/vm_prot.h"
E 6
D 10
#include "sys/specdev.h"
E 10
#include "sys/vnode.h"
I 10
#include "sys/specdev.h"
E 10
#include "sys/mman.h"
E 4
E 3

int clockon = 0;		/* non-zero if high-res timer enabled */
#ifdef PROFTIMER
int  profprocs = 0;		/* # of procs using profiling timer */
#endif
#ifdef DEBUG
int clockdebug = 0;
#endif

/*ARGSUSED*/
clockopen(dev, flags)
	dev_t dev;
{
#ifdef PROFTIMER
#ifdef GPROF
	/*
	 * Kernel profiling enabled, give up.
	 */
	if (profiling)
		return(EBUSY);
#endif
	/*
	 * If any user processes are profiling, give up.
	 */
	if (profprocs)
		return(EBUSY);
#endif
	if (!clockon) {
		startclock();
		clockon++;
E 14
I 14
	if (stathz == 0)		/* XXX should be set in param.c */
		stathz = hz;
	else if (COUNTS_PER_SEC % stathz) {
		printf("cannot get %d Hz statclock; using 100 Hz\n", stathz);
		stathz = 100;
E 14
	}
D 14
	return(0);
}

/*ARGSUSED*/
clockclose(dev, flags)
	dev_t dev;
{
D 3
#ifdef MAPMEM
E 3
D 5
	(void) clockunmmap(dev, (caddr_t)0);
E 5
I 5
	(void) clockunmmap(dev, (caddr_t)0, curproc);	/* XXX */
E 5
D 3
#endif
E 3
	stopclock();
	clockon = 0;
	return(0);
}

/*ARGSUSED*/
D 5
clockioctl(dev, cmd, data, flag)
E 5
I 5
clockioctl(dev, cmd, data, flag, p)
E 5
	dev_t dev;
	caddr_t data;
I 5
	struct proc *p;
E 5
{
	int error = 0;
	
	switch (cmd) {

D 3
#ifdef MAPMEM
E 3
	case CLOCKMAP:
D 5
		error = clockmmap(dev, (caddr_t *)data);
E 5
I 5
		error = clockmmap(dev, (caddr_t *)data, p);
E 5
		break;

	case CLOCKUNMAP:
D 5
		error = clockunmmap(dev, *(caddr_t *)data);
E 5
I 5
		error = clockunmmap(dev, *(caddr_t *)data, p);
E 5
		break;

	case CLOCKGETRES:
		*(int *)data = CLK_RESOLUTION;
		break;
D 3
#endif
E 3

	default:
		error = EINVAL;
		break;
E 14
I 14
	if (profhz == 0)		/* XXX should be set in param.c */
		profhz = stathz * 5;
	else if (profhz < stathz || COUNTS_PER_SEC % profhz) {
		printf("cannot get %d Hz profclock; using %d Hz\n",
		    profhz, stathz);
		profhz = stathz;
E 14
	}
D 14
	return(error);
}
E 14

D 14
/*ARGSUSED*/
clockmap(dev, off, prot)
	dev_t dev;
{
D 3
#ifdef MMAP
	return((off + (IOBASE+CLKSR-1)) >> PGSHIFT);
#endif
E 3
I 3
D 6
	return((off + (IOBASE+CLKBASE+CLKSR-1)) >> PGSHIFT);
E 6
I 6
	return((off + (INTIOBASE+CLKBASE+CLKSR-1)) >> PGSHIFT);
E 6
E 3
}
E 14
I 14
	intvl = COUNTS_PER_SEC / hz;
	statint = COUNTS_PER_SEC / stathz;
	profint = COUNTS_PER_SEC / profhz;
	minint = statint / 2 + 100;
	while (statvar > minint)
		statvar >>= 1;
E 14

D 3
#ifdef MAPMEM

struct mapmemops clockops = {
	(int (*)())0, (int (*)())0, (int (*)())0, (int (*)())0
};

E 3
D 5
clockmmap(dev, addrp)
E 5
I 5
D 14
clockmmap(dev, addrp, p)
E 5
	dev_t dev;
	caddr_t *addrp;
I 5
	struct proc *p;
E 5
{
D 2
	register struct mapmem *mp;
	int id, clockmapin();
E 2
I 2
D 5
	struct proc *p = u.u_procp;		/* XXX */
E 5
D 3
	struct mapmem *mp;
	int id, error, clockmapin();
E 3
I 3
	int error;
	struct vnode vn;
	struct specinfo si;
	int flags;
E 14
I 14
	tick = intvl * CLK_RESOLUTION;
E 14
E 3
E 2

D 3
	id = minor(dev);	/* XXX */
D 2
	mp = mmalloc(id, addrp, NBPG, MM_RO|MM_CI|MM_NOCORE, &clockops);
E 2
I 2
	error = mmalloc(p, id, addrp, NBPG, MM_RO|MM_CI|MM_NOCORE,
			&clockops, &mp);
E 2
#ifdef DEBUG
	if (clockdebug)
D 2
		printf("clockmmap(%d): addr %x\n", u.u_procp->p_pid, *addrp);
E 2
I 2
		printf("clockmmap(%d): addr %x\n", p->p_pid, *addrp);
E 2
#endif
D 2
	if (mp == MMNIL)
		return(u.u_error);
	if (!mmmapin(mp, clockmapin)) {
		mmfree(mp);
		return(u.u_error);
	}
	return(0);
E 2
I 2
	if (error == 0)
		if (error = mmmapin(p, mp, clockmapin))
			(void) mmfree(p, mp);
E 3
I 3
D 13
	flags = MAP_FILE|MAP_SHARED;
E 13
I 13
D 14
	flags = MAP_SHARED;
E 13
	if (*addrp)
		flags |= MAP_FIXED;
	else
		*addrp = (caddr_t)0x1000000;	/* XXX */
	vn.v_type = VCHR;			/* XXX */
	vn.v_specinfo = &si;			/* XXX */
	vn.v_rdev = dev;			/* XXX */
D 5
	error = vm_mmap(u.u_procp->p_map, (vm_offset_t *)addrp,
E 5
I 5
	error = vm_mmap(&p->p_vmspace->vm_map, (vm_offset_t *)addrp,
E 5
			PAGE_SIZE, VM_PROT_ALL, flags, (caddr_t)&vn, 0);
E 3
	return(error);
E 2
}
E 14
I 14
	/* adjust interval counts, per note above */
	intvl--;
	statint--;
	profint--;
E 14

D 5
clockunmmap(dev, addr)
E 5
I 5
D 14
clockunmmap(dev, addr, p)
E 5
	dev_t dev;
	caddr_t addr;
I 5
	struct proc *p;
E 5
{
I 2
D 5
	struct proc *p = u.u_procp;		/* XXX */
E 5
E 2
D 3
	register struct mapmem *mp, **mpp;
	int found, id;
E 3
I 3
	int rv;
E 14
I 14
	/* calculate base reload values */
	clkint = intvl;
	statmin = statint - (statvar >> 1);
	profmin = profint - (statvar >> 1);
	timer3min = statmin;
I 19
	statprev = statint;
E 19
E 14
E 3

D 3
#ifdef DEBUG
	if (clockdebug)
D 2
		printf("clockunmmap(%d): addr %x\n", u.u_procp->p_pid, addr);
E 2
I 2
		printf("clockunmmap(%d): addr %x\n", p->p_pid, addr);
E 2
#endif
	id = minor(dev);	/* XXX */
	found = 0;
	mpp = &u.u_mmap;
	for (mp = *mpp; mp; mp = *mpp) {
		if (mp->mm_id != id || mp->mm_ops != &clockops) {
			mpp = &mp->mm_next;
			continue;
		}
		if (addr &&
		    (addr < mp->mm_uva || addr >= mp->mm_uva+mp->mm_size)) {
			mpp = &mp->mm_next;
			continue;
		}
D 2
		mmmapout(mp);
		mmfree(mp);
E 2
I 2
		mmmapout(p, mp);
		(void) mmfree(p, mp);
E 2
		found++;
	}
	return(found ? 0 : EINVAL);
E 3
I 3
D 14
	if (addr == 0)
		return(EINVAL);		/* XXX: how do we deal with this? */
D 5
	rv = vm_deallocate(u.u_procp->p_map, (vm_offset_t)addr, PAGE_SIZE);
E 5
I 5
D 9
	rv = vm_deallocate(p->p_vmspace->vm_map, (vm_offset_t)addr, PAGE_SIZE);
E 9
I 9
D 11
	rv = vm_deallocate(&p->p_vmspace->vm_map, (vm_offset_t)addr, PAGE_SIZE);
E 11
I 11
	rv = vm_deallocate(&p->p_vmspace->vm_map,
			   (vm_offset_t)addr, PAGE_SIZE);
E 11
E 9
E 5
	return(rv == KERN_SUCCESS ? 0 : EINVAL);
E 3
}
D 3

/*ARGSUSED*/
clockmapin(mp, off)
	struct mapmem *mp;
{
	return((off + (IOBASE+CLKSR-1)) >> PGSHIFT);
}
#endif
E 3

startclock()
{
	register struct clkreg *clk = (struct clkreg *)clkstd[0];

	clk->clk_msb2 = -1; clk->clk_lsb2 = -1;
	clk->clk_msb3 = -1; clk->clk_lsb3 = -1;

	clk->clk_cr2 = CLK_CR3;
	clk->clk_cr3 = CLK_OENAB|CLK_8BIT;
E 14
I 14
	/* finally, load hardware */
E 14
	clk->clk_cr2 = CLK_CR1;
I 14
	clk->clk_cr1 = CLK_RESET;
D 19
	clk->clk_msb1 = intvl >> 8;
	clk->clk_lsb1 = intvl;
	clk->clk_msb2 = 0;
	clk->clk_lsb2 = 0;
	clk->clk_msb3 = statint >> 8;
	clk->clk_lsb3 = statint;
E 19
I 19
	asm volatile(" movpw %0,%1@(5)" : : "d" (intvl), "a" (clk));
	asm volatile(" movpw %0,%1@(9)" : : "d" (0), "a" (clk));
	asm volatile(" movpw %0,%1@(13)" : : "d" (statint), "a" (clk));
E 19
	clk->clk_cr2 = CLK_CR1;
E 14
	clk->clk_cr1 = CLK_IENAB;
I 14
	clk->clk_cr2 = CLK_CR3;
	clk->clk_cr3 = CLK_IENAB;
E 14
}

D 14
stopclock()
E 14
I 14
/*
 * We assume newhz is either stathz or profhz, and that neither will
 * change after being set up above.  Could recalculate intervals here
 * but that would be a drag.
 */
void
setstatclockrate(newhz)
	int newhz;
E 14
{
D 14
	register struct clkreg *clk = (struct clkreg *)clkstd[0];
E 14

D 14
	clk->clk_cr2 = CLK_CR3;
	clk->clk_cr3 = 0;
	clk->clk_cr2 = CLK_CR1;
	clk->clk_cr1 = CLK_IENAB;
E 14
I 14
	if (newhz == stathz)
		timer3min = statmin;
	else
		timer3min = profmin;
E 14
}
D 14
#endif
E 14

D 14
#ifdef PROFTIMER
E 14
/*
D 14
 * This code allows the hp300 kernel to use one of the extra timers on
 * the clock chip for profiling, instead of the regular system timer.
 * The advantage of this is that the profiling timer can be turned up to
 * a higher interrupt rate, giving finer resolution timing. The profclock
 * routine is called from the lev6intr in locore, and is a specialized
 * routine that calls addupc. The overhead then is far less than if
 * hardclock/softclock was called. Further, the context switch code in
 * locore has been changed to turn the profile clock on/off when switching
 * into/out of a process that is profiling (startprofclock/stopprofclock).
 * This reduces the impact of the profiling clock on other users, and might
 * possibly increase the accuracy of the profiling. 
E 14
I 14
D 17
 * Statistics/profiling clock interrupt.  Clear the interrupt and
 * compute a new interval.
E 17
I 17
 * Statistics/profiling clock interrupt.  Compute a new interval.
 * Interrupt has already been cleared.
E 17
 *
 * DO THIS INLINE IN locore.s?
E 14
 */
D 14
int  profint   = PRF_INTERVAL;	/* Clock ticks between interrupts */
int  profscale = 0;		/* Scale factor from sys clock to prof clock */
char profon    = 0;		/* Is profiling clock on? */

/* profon values - do not change, locore.s assumes these values */
#define PRF_NONE	0x00
#define	PRF_USER	0x01
#define	PRF_KERNEL	0x80

I 5
D 6

#ifdef notcalled
E 6
E 5
D 12
initprofclock()
E 12
I 12
initprofclock(profprocs)
	int profprocs;
E 14
I 14
void
statintr(fp)
	struct clockframe *fp;
E 14
E 12
{
D 12
#if NCLOCK > 0
I 5
	struct proc *p = curproc;		/* XXX */
E 12
I 12
D 14
	register struct clkreg *clk = (struct clkreg *)clkstd[0];
E 14
I 14
	register volatile struct clkreg *clk;
	register int newint, r, var;
D 17
	register u_char discard;
E 17
E 14
E 12
I 6

E 6
E 5
D 14
	/*
D 12
	 * If the high-res timer is running, force profiling off.
	 * Unfortunately, this gets reflected back to the user not as
	 * an error but as a lack of results.
	 */
	if (clockon) {
D 5
		u.u_prof.pr_scale = 0;
E 5
I 5
		p->p_stats->p_prof.pr_scale = 0;
E 5
		return;
	}
	/*
	 * Keep track of the number of user processes that are profiling
	 * by checking the scale value.
	 *
	 * XXX: this all assumes that the profiling code is well behaved;
	 * i.e. profil() is called once per process with pcscale non-zero
	 * to turn it on, and once with pcscale zero to turn it off.
	 * Also assumes you don't do any forks or execs.  Oh well, there
	 * is always adb...
	 */
D 5
	if (u.u_prof.pr_scale)
E 5
I 5
	if (p->p_stats->p_prof.pr_scale)
E 5
		profprocs++;
	else
		profprocs--;
#endif
	/*
E 12
	 * The profile interrupt interval must be an even divisor
	 * of the CLK_INTERVAL so that scaling from a system clock
	 * tick to a profile clock tick is possible using integer math.
	 */
	if (profint > CLK_INTERVAL || (CLK_INTERVAL % profint) != 0)
		profint = CLK_INTERVAL;
	profscale = CLK_INTERVAL / profint;
I 8
	profhz = hz * profscale;
E 8
D 12
}
I 5
D 6
#endif
E 6
E 5

startprofclock()
{
	register struct clkreg *clk = (struct clkreg *)clkstd[0];

	clk->clk_msb3 = (profint-1) >> 8 & 0xFF;
	clk->clk_lsb3 = (profint-1) & 0xFF;

	clk->clk_cr2 = CLK_CR3;
	clk->clk_cr3 = CLK_IENAB;
}

stopprofclock()
{
	register struct clkreg *clk = (struct clkreg *)clkstd[0];

	clk->clk_cr2 = CLK_CR3;
	clk->clk_cr3 = 0;
E 12
I 12
	/*
	 * If a process maps the clock, we fail silently.
	 * Unfortunately, this gets reflected back to the user not as
	 * an error but as a lack of results.
	 */
	if (clockon)
		return;
	switch (profprocs) {
	case 1:
		/* start clock */
		clk->clk_msb3 = (profint-1) >> 8 & 0xFF;
		clk->clk_lsb3 = (profint-1) & 0xFF;
		clk->clk_cr2 = CLK_CR3;
		clk->clk_cr3 = CLK_IENAB;
		break;
	case 0:
		/* stop clock */
		clk->clk_cr2 = CLK_CR3;
		clk->clk_cr3 = 0;
		break;
	}
E 14
I 14
	clk = (volatile struct clkreg *)clkstd[0];
D 17
	discard = clk->clk_msb3;	/* clear interrupt */
E 17
	var = statvar;
	do {
		r = random() & (var - 1);
	} while (r == 0);
	newint = timer3min + r;
D 19
	clk->clk_msb3 = newint >> 8;
	clk->clk_lsb3 = newint;
E 19
I 19

	/*
	 * The timer was automatically reloaded with the previous latch
	 * value at the time of the interrupt.  Compensate now for the
	 * amount of time that has run off since then (minimum of 2-12
	 * timer ticks depending on CPU type) plus one tick roundoff.
	 * This should keep us closer to the mean.
	 */
	asm volatile(" clrl %0; movpw %1@(13),%0" : "=d" (r) : "a" (clk));
	newint -= (statprev - r + 1);

	asm volatile(" movpw %0,%1@(13)" : : "d" (newint), "a" (clk));
	statprev = newint;
E 19
	statclock(fp);
E 14
E 12
}

D 14
#ifdef GPROF
E 14
/*
D 14
 * profclock() is expanded in line in lev6intr() unless profiling kernel.
 * Assumes it is called with clock interrupts blocked.
E 14
I 14
 * Return the best possible estimate of the current time.
E 14
 */
I 22
void
E 22
D 14
profclock(pc, ps)
	caddr_t pc;
	int ps;
E 14
I 14
microtime(tvp)
	register struct timeval *tvp;
E 14
{
I 14
	register volatile struct clkreg *clk;
D 19
	register int s, u, h, l, sr, l2, h2, u2, s2;
E 19
I 19
	register int s, u, t, u2, s2;
E 19

E 14
	/*
D 14
	 * Came from user mode.
	 * If this process is being profiled record the tick.
E 14
I 14
	 * Read registers from slowest-changing to fastest-changing,
	 * then re-read out to slowest.  If the values read before the
	 * innermost match those read after, the innermost value is
	 * consistent with the outer values.  If not, it may not be and
	 * we must retry.  Typically this loop runs only once; occasionally
	 * it runs twice, and only rarely does it run longer.
	 *
	 * (Using this loop avoids the need to block interrupts.)
E 14
	 */
D 14
	if (USERMODE(ps)) {
D 5
		if (u.u_prof.pr_scale)
			addupc(pc, &u.u_prof, 1);
E 5
I 5
D 7
		if (p->p_stats.p_prof.pr_scale)
			addupc(pc, &curproc->p_stats.p_prof, 1);
E 7
I 7
		if (curproc->p_stats->p_prof.pr_scale)
			addupc(pc, &curproc->p_stats->p_prof, 1);
E 7
E 5
	}
	/*
	 * Came from kernel (supervisor) mode.
	 * If we are profiling the kernel, record the tick.
	 */
	else if (profiling < 2) {
		register int s = pc - s_lowpc;
E 14
I 14
	clk = (volatile struct clkreg *)clkstd[0];
	do {
		s = time.tv_sec;
		u = time.tv_usec;
D 19
		h = clk->clk_msb1;
		l = clk->clk_lsb1;
		sr = clk->clk_sr;
		l2 = clk->clk_lsb1;
		h2 = clk->clk_msb1;
E 19
I 19
		asm volatile (" clrl %0; movpw %1@(5),%0"
			      : "=d" (t) : "a" (clk));
E 19
		u2 = time.tv_usec;
		s2 = time.tv_sec;
D 19
	} while (l != l2 || h != h2 || u != u2 || s != s2);
E 19
I 19
	} while (u != u2 || s != s2);
E 19
E 14

D 14
		if (s < s_textsize)
			kcount[s / (HISTFRACTION * sizeof (*kcount))]++;
	}
E 14
D 19
	/*
D 14
	 * Kernel profiling was on but has been disabled.
	 * Mark as no longer profiling kernel and if all profiling done,
	 * disable the clock.
E 14
I 14
	 * Pending interrupt means that the counter wrapped and we did not
	 * take the interrupt yet (can only happen if clock interrupts are
	 * blocked).  If so, add one tick.  Then in any case, add remaining
	 * count.  This should leave u < 2 seconds, since we can add at most
	 * two clock intervals (assuming hz > 2!).
E 14
	 */
D 14
	if (profiling && (profon & PRF_KERNEL)) {
		profon &= ~PRF_KERNEL;
		if (profon == PRF_NONE)
			stopprofclock();
E 14
I 14
	if (sr & CLK_INT1)
		u += tick;
D 18
	u += clkint - ((h << 8) | l);
E 18
I 18
	u += (clkint - ((h << 8) | l)) * CLK_RESOLUTION;
E 19
I 19
	u += (clkint - t) * CLK_RESOLUTION;
E 19
E 18
	if (u >= 1000000) {		/* normalize */
		s++;
		u -= 1000000;
E 14
	}
I 14
	tvp->tv_sec = s;
	tvp->tv_usec = u;
E 14
}
D 14
#endif
#endif
E 14

/*
 * Initialize the time of day register, based on the time base which is, e.g.
 * from a filesystem.
 */
inittodr(base)
	time_t base;
{
	u_long timbuf = base;	/* assume no battery clock exists */
	static int bbcinited = 0;

	/* XXX */
	if (!bbcinited) {
		if (badbaddr(&BBCADDR->hil_stat))
			printf("WARNING: no battery clock\n");
		else
			bbcaddr = BBCADDR;
		bbcinited = 1;
	}

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

I 14
/*
 * Restore the time of day hardware after a time change.
 */
E 14
resettodr()
{
	register int i;
	register struct bbc_tm *tmptr;

	tmptr = gmt_to_bbc(time.tv_sec);

	decimal_to_bbc(0, 1,  tmptr->tm_sec);
	decimal_to_bbc(2, 3,  tmptr->tm_min);
	decimal_to_bbc(4, 5,  tmptr->tm_hour);
	decimal_to_bbc(7, 8,  tmptr->tm_mday);
	decimal_to_bbc(9, 10, tmptr->tm_mon);
	decimal_to_bbc(11, 12, tmptr->tm_year);

	/* Some bogusness to deal with seemingly broken hardware. Nonsense */
	bbc_registers[5] = ((tmptr->tm_hour / 10) & 0x03) + 8;

	write_bbc_reg(15, 13);	/* reset prescalar */

	for (i = 0; i <= NUM_BBC_REGS; i++)
	  	if (bbc_registers[i] != write_bbc_reg(i, bbc_registers[i])) {
			printf("Cannot set battery backed clock\n");
			break;
		}
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
	register int i;
	register u_long tmp;
	int year, month, day, hour, min, sec;

	read_bbc();

	sec = bbc_to_decimal(1, 0);
	min = bbc_to_decimal(3, 2);

	/*
	 * Hours are different for some reason. Makes no sense really.
	 */
	hour  = ((bbc_registers[5] & 0x03) * 10) + bbc_registers[4];
	day   = bbc_to_decimal(8, 7);
	month = bbc_to_decimal(10, 9);
	year  = bbc_to_decimal(12, 11) + 1900;

	range_test(hour, 0, 23);
	range_test(day, 1, 31);
	range_test(month, 1, 12);
	range_test(year, STARTOFTIME, 2000);

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

read_bbc()
{
  	register int i, read_okay;

	read_okay = 0;
	while (!read_okay) {
		read_okay = 1;
		for (i = 0; i <= NUM_BBC_REGS; i++)
			bbc_registers[i] = read_bbc_reg(i);
		for (i = 0; i <= NUM_BBC_REGS; i++)
			if (bbc_registers[i] != read_bbc_reg(i))
				read_okay = 0;
	}
}

u_char
read_bbc_reg(reg)
	int reg;
{
	u_char data = reg;

	if (bbcaddr) {
		send_hil_cmd(bbcaddr, BBC_SET_REG, &data, 1, NULL);
		send_hil_cmd(bbcaddr, BBC_READ_REG, NULL, 0, &data);
	}
	return(data);
}

u_char
write_bbc_reg(reg, data)
I 21
	int reg;
E 21
	u_int data;
{
	u_char tmp;

	tmp = (u_char) ((data << HIL_SSHIFT) | reg);

	if (bbcaddr) {
		send_hil_cmd(bbcaddr, BBC_SET_REG, &tmp, 1, NULL);
		send_hil_cmd(bbcaddr, BBC_WRITE_REG, NULL, 0, NULL);
		send_hil_cmd(bbcaddr, BBC_READ_REG, NULL, 0, &tmp);
	}
	return(tmp);
}	
E 1
