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
 * Revision 2.13  91/04/10  16:33:59  mbj
 * 	Added some sun4 code to keep stack out of the mmu hole in setrlimit()
 * 	Reset u.u_error after suser() in donice().
 * 	[91/02/13            berman]
 * 
 * Revision 2.12  91/04/03  12:56:08  mbj
 * 	Omron changes[sic]
 * 
 * Revision 2.11  90/07/03  16:32:03  mrt
 * 	Rework donice() to use task->priority as base instead of
 * 	BASEPRI_USER and to nice all threads, not just the first one in
 * 	the task.  Based on code from Gregg Kellogg at NeXT.
 * 	[90/05/08            dlb]
 * 
 * Revision 2.10  89/10/11  13:37:52  dlb
 * 	Change priority computation in donice().
 * 	Have donice() call new interface routines.
 * 	[89/05/11            dlb]
 * 
 * Revision 2.9  89/05/21  22:35:15  mrt
 * 	Replaced include of mach/mach.h with mach/mach_interface.h
 * 	[89/05/21            mrt]
 * 
 * Revision 2.8  89/04/18  16:42:07  mwyoung
 * 	Include <mach/vm_param.h>.
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

#include <mach_host.h>

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
#if	sun4
extern caddr_t hole_end;
#endif	sun4

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
	register task_t	task;
	register thread_t th;
	register int	pri;
	register int	is_suser;

	if (u.u_uid && u.u_ruid &&
	    u.u_uid != p->p_uid && u.u_ruid != p->p_uid) {
		u.u_error = EPERM;
		return;
	}
	is_suser = suser();
	u.u_error = 0;		/* Nothing wrong yet.. suser() */
	if (n > PRIO_MAX)
		n = PRIO_MAX;
	if (n < PRIO_MIN)
		n = PRIO_MIN;
	if (n < p->p_nice && is_suser == 0) {
		u.u_error = EACCES;
		return;
	}
	/*
	 *	Compute nice from old priority and nice values and
	 *	update the task priority.  Cannot use change_threads = TRUE
	 *	because we have to catch max_priority violations.
	 */
	task = p->task;
	pri = task->priority - p->p_nice/2 + n/2;
	p->p_nice = n;
	task_priority(task,pri,FALSE);		/* Cannot fail */


	/*
	 *	Now change priority for all threads in the task.
	 */
        task_lock(task);
        for (  th = (thread_t) queue_first(&task->thread_list)
             ; !queue_end(&task->thread_list, (queue_t)th)
             ; th = (thread_t) queue_next(&th->thread_list))
        {
                if (th->max_priority > pri) {
			if (is_suser == 0) {
				u.u_error = EACCES;
				break;
			}
#if	MACH_HOST
			/*
			 *	Doing this at exactly the wrong moment
			 *	to a thread being assigned might fail.
			 *	Just repeat it until it works.
			 */
			while (
			    thread_max_priority(th, th->processor_set, pri)
				!= KERN_SUCCESS);
#else	MACH_HOST
			/*
			 *	This cannot fail.
			 */
                        thread_max_priority(th, th->processor_set, pri);
#endif	MACH_HOST
		}
                if (thread_priority(th, pri, TRUE) != KERN_SUCCESS) {
			u.u_error = EPERM;
			break;
		}
	}
        task_unlock(task);
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
#if	sun4
			/* Sun4 has VM hole to watch out for */
			if (new_stack <= (vm_offset_t) hole_end)
			    new_stack = round_page((vm_offset_t) hole_end + 1);
#endif	sun4
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
