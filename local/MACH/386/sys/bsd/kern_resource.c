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
 * $Log:	kern_resource.c,v $
 * Revision 2.9  89/05/21  22:35:15  mrt
 * 	Replaced include of mach/mach.h with mach/mach_interface.h
 * 	[89/05/21            mrt]
 * 
 * Revision 2.8  89/04/18  16:42:07  mwyoung
 * 	Include <mach/vm_param.h>.
 * 	[89/01/28            mwyoung]
 * 
 * Revision 2.4.2.1  89/03/15  00:58:22  mwyoung
 * 	Include <vm/vm_param.h>.
 * 	[89/01/28            mwyoung]
 * 
 * Revision 2.7  89/02/25  14:41:56  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/02/09  04:31:19  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.5  89/01/15  16:17:17  rpd
 * 	Updated includes for the new style, new mach/ directory.
 * 	[89/01/15  14:47:20  rpd]
 * 
 * 16-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Actually grow or shrink stacks when requested in setrlimit().
 *
 *  4-May-88  David Black (dlb) at Carnegie-Mellon University
 *	MACH_TIME_NEW is now standard.
 *
 * 29-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Removed use of "sys/vm.h".
 *
 *  2-Mar-88  David Black (dlb) at Carnegie-Mellon University
 *	Use thread_read_times to get times for self.  This replaces
 *	and generalized the MACH_TIME_NEW code.
 *
 * 21-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Reduced conditionals, purged history.
 *
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)kern_resource.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/inode.h>
#include <sys/proc.h>
#include <sys/fs.h>
#include <sys/uio.h>
#include <sys/kernel.h>

#include <kern/thread.h>
#include <mach/time_value.h>
#include <mach/mach_interface.h>
#include <mach/vm_param.h>

/*
 * Resource controls and accounting.
 */

getpriority()
{
	register struct a {
		int	which;
		int	who;
	} *uap = (struct a *)u.u_ap;
	register struct proc *p;
	int low = PRIO_MAX + 1;

	switch (uap->which) {

	case PRIO_PROCESS:
		if (uap->who == 0)
			p = u.u_procp;
		else
			p = pfind(uap->who);
		if (p == 0)
			break;
		low = p->p_nice;
		break;

	case PRIO_PGRP:
		if (uap->who == 0)
			uap->who = u.u_procp->p_pgrp;
		for (p = allproc; p != NULL; p = p->p_nxt) {
			if (p->p_pgrp == uap->who &&
			    p->p_nice < low)
				low = p->p_nice;
		}
		break;

	case PRIO_USER:
		if (uap->who == 0)
			uap->who = u.u_uid;
		for (p = allproc; p != NULL; p = p->p_nxt) {
			if (p->p_uid == uap->who &&
			    p->p_nice < low)
				low = p->p_nice;
		}
		break;

	default:
		u.u_error = EINVAL;
		return;
	}
	if (low == PRIO_MAX + 1) {
		u.u_error = ESRCH;
		return;
	}
	u.u_r.r_val1 = low;
}

setpriority()
{
	register struct a {
		int	which;
		int	who;
		int	prio;
	} *uap = (struct a *)u.u_ap;
	register struct proc *p;
	int found = 0;

	switch (uap->which) {

	case PRIO_PROCESS:
		if (uap->who == 0)
			p = u.u_procp;
		else
			p = pfind(uap->who);
		if (p == 0)
			break;
		donice(p, uap->prio);
		found++;
		break;

	case PRIO_PGRP:
		if (uap->who == 0)
			uap->who = u.u_procp->p_pgrp;
		for (p = allproc; p != NULL; p = p->p_nxt)
			if (p->p_pgrp == uap->who) {
				donice(p, uap->prio);
				found++;
			}
		break;

	case PRIO_USER:
		if (uap->who == 0)
			uap->who = u.u_uid;
		for (p = allproc; p != NULL; p = p->p_nxt)
			if (p->p_uid == uap->who) {
				donice(p, uap->prio);
				found++;
			}
		break;

	default:
		u.u_error = EINVAL;
		return;
	}
	if (found == 0)
		u.u_error = ESRCH;
}

donice(p, n)
	register struct proc *p;
	register int n;
{
	register thread_t th;
	register int	s;

	if (u.u_uid && u.u_ruid &&
	    u.u_uid != p->p_uid && u.u_ruid != p->p_uid) {
		u.u_error = EPERM;
		return;
	}
	if (n > PRIO_MAX)
		n = PRIO_MAX;
	if (n < PRIO_MIN)
		n = PRIO_MIN;
	if (n < p->p_nice && !suser()) {
		u.u_error = EACCES;
		return;
	}
	p->p_nice = n;
	th = p->thread;
	th->priority = BASEPRI_USER + 2*n;
	s = splsched();
	thread_lock(th);
	compute_priority(th);
	thread_unlock(th);
	splx(s);
}

setrlimit()
{
	register struct a {
		u_int	which;
		struct	rlimit *lim;
	} *uap = (struct a *)u.u_ap;
	struct rlimit alim;
	register struct rlimit *alimp;

	if (uap->which >= RLIM_NLIMITS) {
		u.u_error = EINVAL;
		return;
	}
	alimp = &u.u_rlimit[uap->which];
	u.u_error = copyin((caddr_t)uap->lim, (caddr_t)&alim,
		sizeof (struct rlimit));
	if (u.u_error)
		return;
	if (alim.rlim_cur > alimp->rlim_max || alim.rlim_max > alimp->rlim_max)
		if (!suser())
			return;
	if (uap->which == RLIMIT_STACK) {
		vm_offset_t 	new_stack;
		vm_offset_t	old_stack;
		kern_return_t	ret;

		if (u.u_stack_grows_up) {
			new_stack = trunc_page(u.u_stack_start) +
					round_page(alim.rlim_cur);
			old_stack = (vm_offset_t) u.u_stack_end;
			if (new_stack > old_stack) {
				ret = vm_allocate(current_task()->map,
					&old_stack,
					(new_stack - old_stack),
					FALSE);
			} else if (new_stack < old_stack) {
				ret = vm_deallocate(current_task()->map,
					new_stack,
					(old_stack - new_stack));
			} else
				ret = KERN_SUCCESS;

			if (ret == KERN_SUCCESS)
				u.u_stack_end = (caddr_t) new_stack;
		} else {
			new_stack = round_page(u.u_stack_end) -
					round_page(alim.rlim_cur);
			old_stack = (vm_offset_t) u.u_stack_start;
			if (new_stack < old_stack) {
				ret = vm_allocate(current_task()->map,
					&new_stack,
					(old_stack - new_stack),
					FALSE);
			} else if (new_stack > old_stack) {
				ret = vm_deallocate(current_task()->map,
					old_stack,
					(new_stack - old_stack));
			} else
				ret = KERN_SUCCESS;

			if (ret == KERN_SUCCESS)
				u.u_stack_start = (caddr_t) new_stack;
		}
		if (ret != KERN_SUCCESS)
			u.u_error = EINVAL;
	}
	*alimp = alim;
	if (uap->which == RLIMIT_RSS)
		u.u_procp->p_maxrss = alim.rlim_cur/NBPG;
}

getrlimit()
{
	register struct a {
		u_int	which;
		struct	rlimit *rlp;
	} *uap = (struct a *)u.u_ap;

	if (uap->which >= RLIM_NLIMITS) {
		u.u_error = EINVAL;
		return;
	}
	u.u_error = copyout((caddr_t)&u.u_rlimit[uap->which], (caddr_t)uap->rlp,
	    sizeof (struct rlimit));
}

getrusage()
{
	register struct a {
		int	who;
		struct	rusage *rusage;
	} *uap = (struct a *)u.u_ap;
	register struct rusage *rup;
	time_value_t		sys_time, user_time;
	register struct timeval	*tvp;

	switch (uap->who) {

	case RUSAGE_SELF:
		/*
		 *	This is the current_thread.  Don't need to lock it.
		 */
		thread_read_times(current_thread(), &user_time, &sys_time);
		tvp = &u.u_ru.ru_utime;
		tvp->tv_sec = user_time.seconds;
		tvp->tv_usec = user_time.microseconds;
		tvp = &u.u_ru.ru_stime;
		tvp->tv_sec = sys_time.seconds;
		tvp->tv_usec = sys_time.microseconds;
		rup = &u.u_ru;
		break;

	case RUSAGE_CHILDREN:
		rup = &u.u_cru;
		break;

	default:
		u.u_error = EINVAL;
		return;
	}
	u.u_error = copyout((caddr_t)rup, (caddr_t)uap->rusage,
	    sizeof (struct rusage));
}

ruadd(ru, ru2)
	register struct rusage *ru, *ru2;
{
	register long *ip, *ip2;
	register int i;

	timevaladd(&ru->ru_utime, &ru2->ru_utime);
	timevaladd(&ru->ru_stime, &ru2->ru_stime);
	if (ru->ru_maxrss < ru2->ru_maxrss)
		ru->ru_maxrss = ru2->ru_maxrss;
	ip = &ru->ru_first; ip2 = &ru2->ru_first;
	for (i = &ru->ru_last - &ru->ru_first; i > 0; i--)
		*ip++ += *ip2++;
}
