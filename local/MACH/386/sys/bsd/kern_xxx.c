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
 * $Log:	kern_xxx.c,v $
 * Revision 2.13  89/05/30  10:34:46  rvb
 * 	Mips actually never needed owait().  And I suppose other
 * 	machines as well.
 * 	[89/05/15            af]
 * 
 * Revision 2.12  89/04/22  15:21:13  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.11  89/03/09  19:29:14  rpd
 * 	More cleanup.
 * 
 * Revision 2.10  89/02/25  14:42:36  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.9  89/02/09  04:31:43  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.8  89/01/31  01:20:29  rpd
 * 	printf_cpu_number --> new_printf_cpu_number.
 * 	[89/01/26            dlb]
 * 
 * Revision 2.7  89/01/23  22:04:39  af
 * 	Changes for I386: cut in 386 processor registers
 * 	[89/01/09            rvb]
 * 	
 * 	Added changes for Mips, e.g. to owait().
 * 	[89/01/08            af]
 * 
 * Revision 2.6  89/01/23  15:24:12  rvb
 * 	{get,set}domainname just became MACH_VFS vs SUN_RPC
 * 	[89/01/22            rvb]
 * 
 * Revision 2.5  89/01/18  00:38:00  jsb
 * 	Vnode support: remove Berkeley quota support.
 * 	SUN_RPC: add {get,set}domainname functions.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.4  88/08/09  17:50:14  rvb
 * Turn off cpu number printout in reboot.  There should(?)
 * possibly be a semaphore there also.
 * 
 *  3-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: added declaration of vm_object_shutdown.
 *
 * 20-Aug-87  Peter King (king) at NeXT
 *	SUN_RPC:  Added getdomainname() and setdomainname().
 *	MACH_VFS:  Remove Berkeley QUOTA support.
 *
 * 25-Jun-87  William Bolosky (bolosky) at Carnegie-Mellon University
 *	Made QUOTA a #if-type option.
 *
 * 30-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  updated owait() to pass correct WLOGINDEV capable
 *	rusage structure to wait1() (although this call won't care).
 *	[ V5.1(F1) ]
 *
 * 24-Jan-87  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	CMUCS: Removed "register" before structure definition in
 *	reboot since it was meaningless.
 *
 * 08-Jan-87  Robert Beck (beck) at Sequent Computer Systems, Inc.
 *	Add #include "cputypes.h".
 *	Modify "#ifdef ns32000" to "#ifdef MULTIMAX" in owait().
 *	Add BALANCE case in owait().
 *
 * 29-Oct-86  David L. Black (dlb) at Carnegie-Mellon University
 *	ns32000: modified owait to use same linkage as wait.
 *
 * 15-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Put psl.h and reg.h includes under not ibmrt again since Multimax
 *	also wants these.
 *
 *  7-Oct-86  David L. Black (dlb) at Carnegie-Mellon University
 *	Merged in Multimax changes to signal handling.
 *
 *  5-Apr-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added a call to shutdown the vm_object system at reboot time.
 *	This will cause the paging areas to be properly deallocated.
 *
 * 22-Mar-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merged VM and Romp versions.
 *
 * 14-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	ibmrt: removed include of psl.h and reg.h.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 16-Nov-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	CMUCS:  Fixed off by one errors in checking for validity of
 *	signal numbers.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)kern_xxx.c	7.1 (Berkeley) 6/5/86
 */

#include <cputypes.h>
#include <quota.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/reboot.h>

gethostid()
{

	u.u_r.r_val1 = hostid;
}

sethostid()
{
	struct a {
		long	hostid;
	} *uap = (struct a *)u.u_ap;

	if (suser())
		hostid = uap->hostid;
}

gethostname()
{
	register struct a {
		char	*hostname;
		u_int	len;
	} *uap = (struct a *)u.u_ap;
	register u_int len;

	len = uap->len;
	if (len > hostnamelen + 1)
		len = hostnamelen + 1;
	u.u_error = copyout((caddr_t)hostname, (caddr_t)uap->hostname, len);
}

sethostname()
{
	register struct a {
		char	*hostname;
		u_int	len;
	} *uap = (struct a *)u.u_ap;

	if (!suser())
		return;
	if (uap->len > sizeof (hostname) - 1) {
		u.u_error = EINVAL;
		return;
	}
	hostnamelen = uap->len;
	u.u_error = copyin((caddr_t)uap->hostname, hostname, uap->len);
	hostname[hostnamelen] = 0;
}

getdomainname()
{
	register struct a {
		char	*domainname;
		int	len;
	} *uap = (struct a *)u.u_ap;
	register u_int len;

	len = uap->len;
	if (len > domainnamelen + 1)
		len = domainnamelen + 1;
	u.u_error = copyout((caddr_t)domainname,(caddr_t)uap->domainname,len);
}

setdomainname()
{
	register struct a {
		char	*domainname;
		u_int	len;
	} *uap = (struct a *)u.u_ap;

	if (!suser())
		return;
	if (uap->len > sizeof (domainname) - 1) {
		u.u_error = EINVAL;
		return;
	}
	domainnamelen = uap->len;
	u.u_error = copyin((caddr_t)uap->domainname, domainname, uap->len);
	domainname[domainnamelen] = 0;
}

reboot()
{
	struct a {
		int	opt;
	};

	if (suser()) {
		extern void vm_object_shutdown();
#if	NCPUS > 1
		extern int new_printf_cpu_number;

		printf("Reboot()ing.\n");
		new_printf_cpu_number = 0;
#endif	NCPUS > 1

		vm_object_shutdown();
		boot(RB_BOOT, ((struct a *)u.u_ap)->opt);
	}
}

#ifdef	COMPAT
#include <sys/quota.h>

osetuid()
{
	register uid;
	register struct a {
		int	uid;
	} *uap;

	uap = (struct a *)u.u_ap;
	uid = uap->uid;
	if (u.u_ruid == uid || u.u_uid == uid || suser()) {
		u.u_identity = change_identity(u.u_identity);
#if	QUOTA
		if (u.u_quota->q_uid != uid)
			RESTART_QUOTA(uid);
#endif	QUOTA
		u.u_uid = uid;
		u.u_procp->p_uid = uid;
		u.u_ruid = uid;
	}
}

osetgid()
{
	register gid;
	register struct a {
		int	gid;
	} *uap;

	uap = (struct a *)u.u_ap;
	gid = uap->gid;
	if (u.u_rgid == gid || u.u_gid == gid || suser()) {
		leavegroup(u.u_rgid);
		(void) entergroup(gid);
		u.u_gid = gid;
		u.u_rgid = gid;
	}
}

/*
 * Pid of zero implies current process.
 * Pgrp -1 is getpgrp system call returning
 * current process group.
 */
osetpgrp()
{
	register struct proc *p;
	register struct a {
		int	pid;
		int	pgrp;
	} *uap;

	uap = (struct a *)u.u_ap;
	if (uap->pid == 0)
		p = u.u_procp;
	else {
		p = pfind(uap->pid);
		if (p == 0) {
			u.u_error = ESRCH;
			return;
		}
	}
	if (uap->pgrp <= 0) {
		u.u_r.r_val1 = p->p_pgrp;
		return;
	}
	if (p->p_uid != u.u_uid && u.u_uid && !inferior(p)) {
		u.u_error = EPERM;
		return;
	}
	p->p_pgrp = uap->pgrp;
}

otime()
{

	u.u_r.r_time = time.tv_sec;
}

ostime()
{
	register struct a {
		int	time;
	} *uap = (struct a *)u.u_ap;
	struct timeval tv;

	tv.tv_sec = uap->time;
	tv.tv_usec = 0;
	setthetime(&tv);
}

/* from old timeb.h */
struct timeb {
	time_t	time;
	u_short	millitm;
	short	timezone;
	short	dstflag;
};

oftime()
{
	register struct a {
		struct	timeb	*tp;
	} *uap;
	struct timeb tb;
	int s;

	uap = (struct a *)u.u_ap;
	s = splhigh();
	tb.time = time.tv_sec;
	tb.millitm = time.tv_usec / 1000;
	splx(s);
	tb.timezone = tz.tz_minuteswest;
	tb.dstflag = tz.tz_dsttime;
	u.u_error = copyout((caddr_t)&tb, (caddr_t)uap->tp, sizeof (tb));
}

oalarm()
{
	register struct a {
		int	deltat;
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;
	int s = splhigh();

	untimeout(realitexpire, (caddr_t)p);
	timerclear(&p->p_realtimer.it_interval);
	u.u_r.r_val1 = 0;
	if (timerisset(&p->p_realtimer.it_value) &&
	    timercmp(&p->p_realtimer.it_value, &time, >))
		u.u_r.r_val1 = p->p_realtimer.it_value.tv_sec - time.tv_sec;
	if (uap->deltat == 0) {
		timerclear(&p->p_realtimer.it_value);
		splx(s);
		return;
	}
	p->p_realtimer.it_value = time;
	p->p_realtimer.it_value.tv_sec += uap->deltat;
	timeout(realitexpire, (caddr_t)p, hzto(&p->p_realtimer.it_value));
	splx(s);
}

onice()
{
	register struct a {
		int	niceness;
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;

	donice(p, (p->p_nice-NZERO)+uap->niceness);
}

#include <sys/times.h>

otimes()
{
	register struct a {
		struct	tms *tmsb;
	} *uap = (struct a *)u.u_ap;
	struct tms atms;

	atms.tms_utime = scale60(&u.u_ru.ru_utime);
	atms.tms_stime = scale60(&u.u_ru.ru_stime);
	atms.tms_cutime = scale60(&u.u_cru.ru_utime);
	atms.tms_cstime = scale60(&u.u_cru.ru_stime);
	u.u_error = copyout((caddr_t)&atms, (caddr_t)uap->tmsb, sizeof (atms));
}

scale60(tvp)
	register struct timeval *tvp;
{

	return (tvp->tv_sec * 60 + tvp->tv_usec / 16667);
}

#include <sys/vtimes.h>

ovtimes()
{
	register struct a {
		struct	vtimes *par;
		struct	vtimes *chi;
	} *uap = (struct a *)u.u_ap;
	struct vtimes avt;

	if (uap->par) {
		getvtimes(&u.u_ru, &avt);
		u.u_error = copyout((caddr_t)&avt, (caddr_t)uap->par,
			sizeof (avt));
		if (u.u_error)
			return;
	}
	if (uap->chi) {
		getvtimes(&u.u_cru, &avt);
		u.u_error = copyout((caddr_t)&avt, (caddr_t)uap->chi,
			sizeof (avt));
		if (u.u_error)
			return;
	}
}

#ifdef	ibmrt
#else	ibmrt
#include <machine/psl.h>
#include <machine/reg.h>
#endif	ibmrt

#define wait1	wait3
#define rusage	rusage_dev

owait()
{
#if	defined(ibmrt) || defined(mips)
	return;	/* Bye, Bye */
#endif	defined(ibmrt) || defined(mips)
	struct rusage ru;
	struct vtimes *vtp, avt;

#ifdef	multimax
	if((u.u_error = wait1(fuword(u.u_ar0[R1] + 4), &ru)) != 0)
		return;
	getvtimes(&ru,&avt);
	if((vtp = (struct rusage *)fuword(u.u_ar0[R1] + 8)) != 0)
		(void)copyout((caddr_t)&avt,(caddr_t)vtp, sizeof(struct vtimes));
#endif	multimax
#ifdef	balance
	if ((u.u_ar0[PS] & (PSR_C<<PSRADJ)) == 0) {
		u.u_error = wait1(0, (struct rusage *)0);
		return;
	}
	vtp = (struct vtimes *)u.u_ar0[R2];
	u.u_error = wait1(u.u_ar0[R1], &ru);
#endif	balance
#ifdef	vax
	if ((u.u_ar0[PS] & PSL_ALLCC) != PS_ALLCC) {
		u.u_error = wait1(0, (struct rusage *)0);
		return;
	}
	vtp = (struct vtimes *)u.u_ar0[R1];
	u.u_error = wait1(u.u_ar0[R0], &ru);
#endif	vax
#ifdef	sun
	if ((u.u_ar0[PS] & PSL_ALLCC) != PS_ALLCC) {
		u.u_error = wait1(0, (struct rusage *)0);
		return;
	}
	vtp = (struct vtimes *)u.u_ar0[R1];
	u.u_error = wait1(u.u_ar0[R0], &ru);
#endif	sun
#ifdef	i386
	if ((u.u_ar0[EFL] & EFL_CF) != EFL_CF) {
		u.u_error = wait1(0, (struct rusage *)0);
		return;
	}
	vtp = (struct vtimes *)u.u_ar0[EDX];
	u.u_error = wait1(u.u_ar0[EAX], &ru);
#endif	i386
	if (u.u_error)
		return;
	getvtimes(&ru, &avt);
	(void) copyout((caddr_t)&avt, (caddr_t)vtp, sizeof (struct vtimes));
}
#undef	wait1
#undef	rusage

getvtimes(aru, avt)
	register struct rusage *aru;
	register struct vtimes *avt;
{

	avt->vm_utime = scale60(&aru->ru_utime);
	avt->vm_stime = scale60(&aru->ru_stime);
	avt->vm_idsrss = ((aru->ru_idrss+aru->ru_isrss) / hz) * 60;
	avt->vm_ixrss = aru->ru_ixrss / hz * 60;
	avt->vm_maxrss = aru->ru_maxrss;
	avt->vm_majflt = aru->ru_majflt;
	avt->vm_minflt = aru->ru_minflt;
	avt->vm_nswap = aru->ru_nswap;
	avt->vm_inblk = aru->ru_inblock;
	avt->vm_oublk = aru->ru_oublock;
}

ovlimit()
{

	u.u_error = EACCES;
}

ossig()
{
	struct a {
		int	signo;
		int	(*fun)();
	} *uap = (struct a *)u.u_ap;
	register int a;
	struct sigvec vec;
	register struct sigvec *sv = &vec;
	struct proc *p = u.u_procp;

	a = uap->signo;
	sv->sv_handler = uap->fun;
	/*
	 * Kill processes trying to use job control facilities
	 * (this'll help us find any vestiges of the old stuff).
	 */
	if ((a &~ 0377) ||
	    (sv->sv_handler != SIG_DFL && sv->sv_handler != SIG_IGN &&
	     ((int)sv->sv_handler) & 1)) {
		psignal(p, SIGSYS);
		return;
	}
	if (a <= 0 || a > NSIG || a == SIGKILL || a == SIGSTOP ||
	    a == SIGCONT && sv->sv_handler == SIG_IGN) {
		u.u_error = EINVAL;
		return;
	}
	sv->sv_mask = 0;
	sv->sv_flags = SV_INTERRUPT;
	u.u_r.r_val1 = (int)u.u_signal[a];
	setsigvec(a, sv);
	p->p_flag |= SOUSIG;		/* mark as simulating old stuff */
}
#endif
