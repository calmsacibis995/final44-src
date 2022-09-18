h08613
s 00004/00003/00501
d D 8.18 95/05/21 22:24:24 mckusick 19 18
c more precise output from lockmgr_printinfo
e
s 00000/00013/00504
d D 8.17 95/05/20 12:13:09 mckusick 18 17
c get rid of dead code
e
s 00004/00001/00513
d D 8.16 95/05/20 01:20:23 mckusick 17 16
c allow drained locks to be reenabled
e
s 00019/00015/00495
d D 8.15 95/05/19 17:57:11 mckusick 16 15
c hack to try to avoid improperly detected recursive locks
e
s 00006/00000/00504
d D 8.14 95/05/19 14:32:32 pendry 15 14
c track number of simple locks
e
s 00004/00000/00500
d D 8.13 95/05/17 22:09:08 mckusick 14 12
c add back trace to simple lock diagnostic information (if available)
e
s 00003/00000/00500
d R 8.13 95/05/17 21:14:36 mckusick 13 12
c add back trace to simple lock diagnostic information (if available)
e
s 00047/00013/00453
d D 8.12 95/05/17 21:11:47 mckusick 12 11
c accounting for locks and unlocks; 
c give file and line in simple lock error diagnostics
e
s 00036/00007/00430
d D 8.11 95/05/14 18:24:05 mckusick 11 10
c allow simple lock failure to be a warning rather than a panic
e
s 00043/00013/00394
d D 8.10 95/05/14 00:12:56 mckusick 10 9
c get proc pointer rather than pid; more checking for DRAINING errors
e
s 00051/00008/00356
d D 8.9 95/05/11 14:51:47 mckusick 9 8
c minor cleanups; non-inline version of simple locking functions for NCPUS == 1
e
s 00026/00008/00338
d D 8.8 95/04/27 15:27:00 mckusick 8 7
c lockmgr now takes an interlock and a pid but no longer a proc ptr;
c LK_DRAIN now returns with exclusive lock; add lock print function
e
s 00020/00013/00326
d D 8.7 95/04/27 14:27:51 mckusick 7 6
c atomic_lock => simple_lock
e
s 00071/00047/00268
d D 8.6 95/04/13 16:59:29 mckusick 6 5
c add LK_DRAIN
e
s 00003/00001/00312
d D 8.5 95/04/11 15:16:01 mckusick 5 4
c nits
e
s 00018/00000/00295
d D 8.4 95/04/11 13:19:02 mckusick 4 3
c add lockstatus to querry lock status
e
s 00022/00010/00273
d D 8.3 95/04/11 12:56:19 mckusick 3 2
c comments from cgd and mycroft
e
s 00007/00010/00276
d D 8.2 95/04/10 23:00:07 mckusick 2 1
c feedback from cgd
e
s 00286/00000/00000
d D 8.1 95/04/09 23:17:34 mckusick 1 0
c date and time created 95/04/09 23:17:34 by mckusick
e
u
U
t
T
I 1
/* 
 * Copyright (c) 1995
 *	The Regents of the University of California.  All rights reserved.
 *
D 2
 * This code is derived from software contributed to Berkeley by
E 2
I 2
 * This code contains ideas from software contributed to Berkeley by
E 2
 * Avadis Tevanian, Jr., Michael Wayne Young, and the Mach Operating
 * System project at Carnegie-Mellon University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/proc.h>
#include <sys/lock.h>
I 14
#include <machine/cpu.h>
E 14

/*
 * Locking primitives implementation.
 * Locks provide shared/exclusive sychronization.
 */

I 12
#ifdef DEBUG
#define COUNT(p, x) if (p) (p)->p_locks += (x)
#else
#define COUNT(p, x)
#endif

E 12
#if NCPUS > 1

/*
 * For multiprocessor system, try spin lock first.
 *
 * This should be inline expanded below, but we cannot have #if
 * inside a multiline define.
 */
int lock_wait_time = 100;
#define PAUSE(lkp, wanted)						\
		if (lock_wait_time > 0) {				\
			int i;						\
									\
D 7
			atomic_unlock(&lkp->lk_interlock);		\
E 7
I 7
			simple_unlock(&lkp->lk_interlock);		\
E 7
			for (i = lock_wait_time; i > 0; i--)		\
				if (!(wanted))				\
					break;				\
D 7
			atomic_lock(&lkp->lk_interlock);		\
E 7
I 7
			simple_lock(&lkp->lk_interlock);		\
E 7
		}							\
		if (!(wanted))						\
			break;

#else /* NCPUS == 1 */

/*
 * It is an error to spin on a uniprocessor as nothing will ever cause
D 7
 * the atomic lock to clear while we are executing.
E 7
I 7
 * the simple lock to clear while we are executing.
E 7
 */
#define PAUSE(lkp, wanted)

I 7
D 9
/*
 * Panic messages for inline expanded simple locks.
 * Put text here to avoid hundreds of copies.
 */
const char *simple_lock_held = "simple_lock: lock held";
const char *simple_lock_not_held = "simple_lock: lock not held";

E 9
E 7
#endif /* NCPUS == 1 */

/*
 * Acquire a resource.
 */
#define ACQUIRE(lkp, error, extflags, wanted)				\
	PAUSE(lkp, wanted);						\
	for (error = 0; wanted; ) {					\
D 6
		(lkp)->lk_flags |= LK_WAITING;				\
E 6
I 6
		(lkp)->lk_waitcount++;					\
E 6
D 7
		atomic_unlock(&(lkp)->lk_interlock);			\
E 7
I 7
		simple_unlock(&(lkp)->lk_interlock);			\
E 7
D 3
		error = tsleep(lkp, (lkp)->lk_prio, (lkp)->lk_wmesg,	\
		    (lkp)->lk_timo);					\
E 3
I 3
		error = tsleep((void *)lkp, (lkp)->lk_prio,		\
		    (lkp)->lk_wmesg, (lkp)->lk_timo);			\
E 3
D 7
		atomic_lock(&(lkp)->lk_interlock);			\
E 7
I 7
		simple_lock(&(lkp)->lk_interlock);			\
E 7
I 6
		(lkp)->lk_waitcount--;					\
E 6
D 3
		(lkp)->lk_flags |= LK_SLEPT;				\
E 3
		if (error)						\
			break;						\
		if ((extflags) & LK_SLEEPFAIL) {			\
			error = ENOLCK;					\
			break;						\
		}							\
	}

/*
 * Initialize a lock; required before use.
 */
D 5
void lock_init(lkp, prio, wmesg, timo, flags)
E 5
I 5
void
D 9
lock_init(lkp, prio, wmesg, timo, flags)
E 9
I 9
lockinit(lkp, prio, wmesg, timo, flags)
E 9
E 5
	struct lock *lkp;
	int prio;
	char *wmesg;
	int timo;
	int flags;
{
I 9

E 9
	bzero(lkp, sizeof(struct lock));
D 7
	atomic_lock_init(&lkp->lk_interlock);
E 7
I 7
	simple_lock_init(&lkp->lk_interlock);
E 7
	lkp->lk_flags = flags & LK_EXTFLG_MASK;
	lkp->lk_prio = prio;
	lkp->lk_timo = timo;
	lkp->lk_wmesg = wmesg;
	lkp->lk_lockholder = LK_NOPROC;
}

/*
I 4
 * Determine the status of a lock.
 */
int
lockstatus(lkp)
	struct lock *lkp;
{
	int lock_type = 0;

D 7
	atomic_lock(&lkp->lk_interlock);
E 7
I 7
	simple_lock(&lkp->lk_interlock);
E 7
	if (lkp->lk_exclusivecount != 0)
		lock_type = LK_EXCLUSIVE;
	else if (lkp->lk_sharecount != 0)
		lock_type = LK_SHARED;
D 7
	atomic_unlock(&lkp->lk_interlock);
E 7
I 7
	simple_unlock(&lkp->lk_interlock);
E 7
	return (lock_type);
}

/*
E 4
 * Set, change, or release a lock.
 *
 * Shared requests increment the shared count. Exclusive requests set the
 * LK_WANT_EXCL flag (preventing further shared locks), and wait for already
 * accepted shared locks and shared-to-exclusive upgrades to go away.
 */
I 5
int
E 5
D 6
lockmgr(lkp, p, flags)
E 6
I 6
D 8
lockmgr(lkp, flags, p)
E 6
D 3
	struct lock *lkp;
E 3
I 3
	volatile struct lock *lkp;
E 8
I 8
D 10
lockmgr(lkp, flags, interlkp, pid)
E 10
I 10
lockmgr(lkp, flags, interlkp, p)
E 10
	__volatile struct lock *lkp;
E 8
E 3
D 6
	struct proc *p;
E 6
D 3
	int flags;
E 3
I 3
	u_int flags;
I 6
D 8
	struct proc *p;
E 8
I 8
D 10
	struct simple_lock *interlkp;
	pid_t pid;
E 10
I 10
	struct simplelock *interlkp;
	struct proc *p;
E 10
E 8
E 6
E 3
{
I 3
	int error;
E 3
D 8
	pid_t pid;
D 3
	int error, extflags;
E 3
I 3
	volatile int extflags;
E 8
I 8
D 10
	__volatile int extflags;
E 10
I 10
	pid_t pid;
	int extflags;
E 10
E 8
E 3

I 6
	error = 0;
I 10
	if (p)
		pid = p->p_pid;
	else
		pid = LK_KERNPROC;
E 10
E 6
D 8
	pid = p->p_pid;
E 8
I 2
D 7
	atomic_lock(&lkp->lk_interlock);
E 7
I 7
	simple_lock(&lkp->lk_interlock);
I 8
	if (flags & LK_INTERLOCK)
		simple_unlock(interlkp);
E 8
E 7
E 2
	extflags = (flags | lkp->lk_flags) & LK_EXTFLG_MASK;
I 6
D 8
	if (lkp->lk_flags & LK_DRAINED)
E 8
I 8
D 10
	if ((lkp->lk_flags & LK_DRAINED) &&
	    (((flags & LK_TYPE_MASK) != LK_RELEASE) ||
	    lkp->lk_lockholder != pid))
E 8
		panic("lockmgr: using decommissioned lock");
E 10
I 10
#ifdef DIAGNOSTIC
	/*
	 * Once a lock has drained, the LK_DRAINING flag is set and an
	 * exclusive lock is returned. The only valid operation thereafter
	 * is a single release of that exclusive lock. This final release
	 * clears the LK_DRAINING flag and sets the LK_DRAINED flag. Any
	 * further requests of any sort will result in a panic. The bits
	 * selected for these two flags are chosen so that they will be set
	 * in memory that is freed (freed memory is filled with 0xdeadbeef).
I 17
	 * The final release is permitted to give a new lease on life to
	 * the lock by specifying LK_REENABLE.
E 17
	 */
	if (lkp->lk_flags & (LK_DRAINING|LK_DRAINED)) {
		if (lkp->lk_flags & LK_DRAINED)
			panic("lockmgr: using decommissioned lock");
		if ((flags & LK_TYPE_MASK) != LK_RELEASE ||
		    lkp->lk_lockholder != pid)
			panic("lockmgr: non-release on draining lock: %d\n",
			    flags & LK_TYPE_MASK);
		lkp->lk_flags &= ~LK_DRAINING;
D 17
		lkp->lk_flags |= LK_DRAINED;
E 17
I 17
		if ((flags & LK_REENABLE) == 0)
			lkp->lk_flags |= LK_DRAINED;
E 17
	}
#endif DIAGNOSTIC
E 10
E 6
D 3
	lkp->lk_flags &= ~LK_SLEPT;
E 3

	switch (flags & LK_TYPE_MASK) {

	case LK_SHARED:
D 2
		atomic_lock(&lkp->lk_interlock);
E 2
		if (lkp->lk_lockholder != pid) {
			/*
			 * If just polling, check to see if we will block.
			 */
			if ((extflags & LK_NOWAIT) && (lkp->lk_flags &
			    (LK_HAVE_EXCL | LK_WANT_EXCL | LK_WANT_UPGRADE))) {
D 6
				atomic_unlock(&lkp->lk_interlock);
				return (EBUSY);
E 6
I 6
				error = EBUSY;
				break;
E 6
			}
			/*
			 * Wait for exclusive locks and upgrades to clear.
			 */
			ACQUIRE(lkp, error, extflags, lkp->lk_flags &
			    (LK_HAVE_EXCL | LK_WANT_EXCL | LK_WANT_UPGRADE));
D 6
			if (error) {
				atomic_unlock(&lkp->lk_interlock);
				return (error);
			}
E 6
I 6
			if (error)
				break;
E 6
			lkp->lk_sharecount++;
I 12
			COUNT(p, 1);
E 12
D 6
			atomic_unlock(&lkp->lk_interlock);
			return (0);
E 6
I 6
			break;
E 6
		}
		/*
		 * We hold an exclusive lock, so downgrade it to shared.
		 * An alternative would be to fail with EDEADLK.
		 */
		lkp->lk_sharecount++;
I 12
		COUNT(p, 1);
E 12
D 2
		atomic_unlock(&lkp->lk_interlock);
E 2
		/* fall into downgrade */

	case LK_DOWNGRADE:
D 2
		atomic_lock(&lkp->lk_interlock);
E 2
		if (lkp->lk_lockholder != pid || lkp->lk_exclusivecount == 0)
			panic("lockmgr: not holding exclusive lock");
		lkp->lk_sharecount += lkp->lk_exclusivecount;
		lkp->lk_exclusivecount = 0;
		lkp->lk_flags &= ~LK_HAVE_EXCL;
		lkp->lk_lockholder = LK_NOPROC;
D 6
		if (lkp->lk_flags & LK_WAITING) {
			lkp->lk_flags &= ~LK_WAITING;
E 6
I 6
		if (lkp->lk_waitcount)
E 6
D 3
			wakeup(lkp);
E 3
I 3
			wakeup((void *)lkp);
E 3
D 6
		}
		atomic_unlock(&lkp->lk_interlock);
		return (0);
E 6
I 6
		break;
E 6

I 3
	case LK_EXCLUPGRADE:
		/*
		 * If another process is ahead of us to get an upgrade,
		 * then we want to fail rather than have an intervening
		 * exclusive access.
		 */
		if (lkp->lk_flags & LK_WANT_UPGRADE) {
			lkp->lk_sharecount--;
I 12
			COUNT(p, -1);
E 12
D 6
			atomic_unlock(&lkp->lk_interlock);
			return (EBUSY);
E 6
I 6
			error = EBUSY;
			break;
E 6
		}
		/* fall into normal upgrade */

E 3
	case LK_UPGRADE:
		/*
		 * Upgrade a shared lock to an exclusive one. If another
		 * shared lock has already requested an upgrade to an
		 * exclusive lock, our shared lock is released and an
		 * exclusive lock is requested (which will be granted
D 2
		 * after the upgrade).
E 2
I 2
		 * after the upgrade). If we return an error, the file
		 * will always be unlocked.
E 2
		 */
D 2
		atomic_lock(&lkp->lk_interlock);
E 2
		if (lkp->lk_lockholder == pid || lkp->lk_sharecount <= 0)
			panic("lockmgr: upgrade exclusive lock");
I 2
		lkp->lk_sharecount--;
I 12
		COUNT(p, -1);
E 12
E 2
		/*
		 * If we are just polling, check to see if we will block.
		 */
		if ((extflags & LK_NOWAIT) &&
		    ((lkp->lk_flags & LK_WANT_UPGRADE) ||
		     lkp->lk_sharecount > 1)) {
D 6
			atomic_unlock(&lkp->lk_interlock);
			return (EBUSY);
E 6
I 6
			error = EBUSY;
			break;
E 6
		}
D 2
		lkp->lk_sharecount--;
E 2
		if ((lkp->lk_flags & LK_WANT_UPGRADE) == 0) {
			/*
			 * We are first shared lock to request an upgrade, so
			 * request upgrade and wait for the shared count to
			 * drop to zero, then take exclusive lock.
			 */
			lkp->lk_flags |= LK_WANT_UPGRADE;
			ACQUIRE(lkp, error, extflags, lkp->lk_sharecount);
			lkp->lk_flags &= ~LK_WANT_UPGRADE;
D 6
			if (error) {
				atomic_unlock(&lkp->lk_interlock);
				return (error);
			}
E 6
I 6
			if (error)
				break;
E 6
			lkp->lk_flags |= LK_HAVE_EXCL;
			lkp->lk_lockholder = pid;
			if (lkp->lk_exclusivecount != 0)
				panic("lockmgr: non-zero exclusive count");
			lkp->lk_exclusivecount = 1;
I 12
			COUNT(p, 1);
E 12
D 6
			atomic_unlock(&lkp->lk_interlock);
			return (0);
E 6
I 6
			break;
E 6
		}
		/*
		 * Someone else has requested upgrade. Release our shared
		 * lock, awaken upgrade requestor if we are the last shared
		 * lock, then request an exclusive lock.
		 */
D 6
		if (lkp->lk_sharecount == 0 && (lkp->lk_flags & LK_WAITING)) {
			lkp->lk_flags &= ~LK_WAITING;
E 6
I 6
		if (lkp->lk_sharecount == 0 && lkp->lk_waitcount)
E 6
D 3
			wakeup(lkp);
E 3
I 3
			wakeup((void *)lkp);
E 3
D 6
		}
E 6
D 2
		atomic_unlock(&lkp->lk_interlock);
E 2
		/* fall into exclusive request */

	case LK_EXCLUSIVE:
D 2
		atomic_lock(&lkp->lk_interlock);
E 2
D 11
		if (lkp->lk_lockholder == pid) {
E 11
I 11
		if (lkp->lk_lockholder == pid && pid != LK_KERNPROC) {
E 11
			/*
			 *	Recursive lock.
			 */
			if ((extflags & LK_CANRECURSE) == 0)
				panic("lockmgr: locking against myself");
			lkp->lk_exclusivecount++;
I 12
			COUNT(p, 1);
E 12
D 6
			atomic_unlock(&lkp->lk_interlock);
			return (0);
E 6
I 6
			break;
E 6
		}
		/*
		 * If we are just polling, check to see if we will sleep.
		 */
		if ((extflags & LK_NOWAIT) && ((lkp->lk_flags &
		     (LK_HAVE_EXCL | LK_WANT_EXCL | LK_WANT_UPGRADE)) ||
		     lkp->lk_sharecount != 0)) {
D 6
			atomic_unlock(&lkp->lk_interlock);
			return (EBUSY);
E 6
I 6
			error = EBUSY;
			break;
E 6
		}
		/*
		 * Try to acquire the want_exclusive flag.
		 */
		ACQUIRE(lkp, error, extflags, lkp->lk_flags &
		    (LK_HAVE_EXCL | LK_WANT_EXCL));
D 6
		if (error) {
			atomic_unlock(&lkp->lk_interlock);
			return (error);
		}
E 6
I 6
		if (error)
			break;
E 6
		lkp->lk_flags |= LK_WANT_EXCL;
		/*
		 * Wait for shared locks and upgrades to finish.
		 */
		ACQUIRE(lkp, error, extflags, lkp->lk_sharecount != 0 ||
		       (lkp->lk_flags & LK_WANT_UPGRADE));
		lkp->lk_flags &= ~LK_WANT_EXCL;
D 6
		if (error) {
			atomic_unlock(&lkp->lk_interlock);
			return (error);
		}
E 6
I 6
		if (error)
			break;
E 6
		lkp->lk_flags |= LK_HAVE_EXCL;
		lkp->lk_lockholder = pid;
		if (lkp->lk_exclusivecount != 0)
			panic("lockmgr: non-zero exclusive count");
		lkp->lk_exclusivecount = 1;
I 12
		COUNT(p, 1);
E 12
D 6
		atomic_unlock(&lkp->lk_interlock);
		return (0);
E 6
I 6
		break;
E 6

	case LK_RELEASE:
D 2
		atomic_lock(&lkp->lk_interlock);
E 2
		if (lkp->lk_exclusivecount != 0) {
I 6
			if (pid != lkp->lk_lockholder)
				panic("lockmgr: pid %d, not %s %d unlocking",
				    pid, "exclusive lock holder",
				    lkp->lk_lockholder);
E 6
			lkp->lk_exclusivecount--;
I 12
			COUNT(p, -1);
E 12
			if (lkp->lk_exclusivecount == 0) {
				lkp->lk_flags &= ~LK_HAVE_EXCL;
				lkp->lk_lockholder = LK_NOPROC;
			}
D 12
		} else if (lkp->lk_sharecount != 0)
E 12
I 12
		} else if (lkp->lk_sharecount != 0) {
E 12
			lkp->lk_sharecount--;
I 12
			COUNT(p, -1);
		}
E 12
D 6
		if (lkp->lk_flags & LK_WAITING) {
			lkp->lk_flags &= ~LK_WAITING;
E 6
I 6
		if (lkp->lk_waitcount)
E 6
D 3
			wakeup(lkp);
E 3
I 3
			wakeup((void *)lkp);
I 6
		break;

	case LK_DRAIN:
		/*
I 10
		 * Check that we do not already hold the lock, as it can 
		 * never drain if we do. Unfortunately, we have no way to
		 * check for holding a shared lock, but at least we can
		 * check for an exclusive one.
		 */
		if (lkp->lk_lockholder == pid)
			panic("lockmgr: draining against myself");
		/*
E 10
		 * If we are just polling, check to see if we will sleep.
		 */
		if ((extflags & LK_NOWAIT) && ((lkp->lk_flags &
		     (LK_HAVE_EXCL | LK_WANT_EXCL | LK_WANT_UPGRADE)) ||
		     lkp->lk_sharecount != 0 || lkp->lk_waitcount != 0)) {
			error = EBUSY;
			break;
E 6
E 3
		}
D 6
		atomic_unlock(&lkp->lk_interlock);
		return (0);
E 6
I 6
		PAUSE(lkp, ((lkp->lk_flags &
		     (LK_HAVE_EXCL | LK_WANT_EXCL | LK_WANT_UPGRADE)) ||
		     lkp->lk_sharecount != 0 || lkp->lk_waitcount != 0));
		for (error = 0; ((lkp->lk_flags &
		     (LK_HAVE_EXCL | LK_WANT_EXCL | LK_WANT_UPGRADE)) ||
		     lkp->lk_sharecount != 0 || lkp->lk_waitcount != 0); ) {
			lkp->lk_flags |= LK_WAITDRAIN;
D 7
			atomic_unlock(&lkp->lk_interlock);
E 7
I 7
			simple_unlock(&lkp->lk_interlock);
E 7
			if (error = tsleep((void *)&lkp->lk_flags, lkp->lk_prio,
			    lkp->lk_wmesg, lkp->lk_timo))
				return (error);
			if ((extflags) & LK_SLEEPFAIL)
				return (ENOLCK);
D 7
			atomic_lock(&lkp->lk_interlock);
E 7
I 7
			simple_lock(&lkp->lk_interlock);
E 7
		}
D 8
		lkp->lk_flags |= LK_DRAINED;
E 8
I 8
D 10
		lkp->lk_flags |= LK_DRAINED | LK_HAVE_EXCL;
E 10
I 10
		lkp->lk_flags |= LK_DRAINING | LK_HAVE_EXCL;
E 10
		lkp->lk_lockholder = pid;
		lkp->lk_exclusivecount = 1;
I 12
		COUNT(p, 1);
E 12
E 8
		break;
E 6

	default:
I 2
D 7
		atomic_unlock(&lkp->lk_interlock);
E 7
I 7
		simple_unlock(&lkp->lk_interlock);
E 7
E 2
		panic("lockmgr: unknown locktype request %d",
		    flags & LK_TYPE_MASK);
I 2
		/* NOTREACHED */
E 2
	}
I 6
	if ((lkp->lk_flags & LK_WAITDRAIN) && ((lkp->lk_flags &
	     (LK_HAVE_EXCL | LK_WANT_EXCL | LK_WANT_UPGRADE)) == 0 &&
	     lkp->lk_sharecount == 0 && lkp->lk_waitcount == 0)) {
		lkp->lk_flags &= ~LK_WAITDRAIN;
		wakeup((void *)&lkp->lk_flags);
	}
D 7
	atomic_unlock(&lkp->lk_interlock);
E 7
I 7
	simple_unlock(&lkp->lk_interlock);
E 7
	return (error);
I 8
}

I 9
/*
 * Print out information about state of a lock. Used by VOP_PRINT
 * routines to display ststus about contained locks.
 */
E 9
lockmgr_printinfo(lkp)
	struct lock *lkp;
{

	if (lkp->lk_sharecount)
D 19
		printf(" lock type %s: SHARED", lkp->lk_wmesg);
E 19
I 19
		printf(" lock type %s: SHARED (count %d)", lkp->lk_wmesg,
		    lkp->lk_sharecount);
E 19
	else if (lkp->lk_flags & LK_HAVE_EXCL)
D 19
		printf(" lock type %s: EXCL by pid %d", lkp->lk_wmesg,
		    lkp->lk_lockholder);
E 19
I 19
		printf(" lock type %s: EXCL (count %d) by pid %d",
		    lkp->lk_wmesg, lkp->lk_exclusivecount, lkp->lk_lockholder);
E 19
	if (lkp->lk_waitcount > 0)
		printf(" with %d pending", lkp->lk_waitcount);
E 8
E 6
}
I 9

#if defined(DEBUG) && NCPUS == 1
I 11
#include <sys/kernel.h>
#include <vm/vm.h>
#include <sys/sysctl.h>
D 16
int lockpausetime = 1;
E 16
I 16
int lockpausetime = 0;
E 16
struct ctldebug debug2 = { "lockpausetime", &lockpausetime };
I 16
int simplelockrecurse;
E 16
E 11
/*
 * Simple lock functions so that the debugger can see from whence
 * they are being called.
 */
void
simple_lock_init(alp)
D 10
	struct simple_lock *alp;
E 10
I 10
	struct simplelock *alp;
E 10
{

	alp->lock_data = 0;
}

void
D 12
simple_lock(alp)
E 12
I 12
_simple_lock(alp, id, l)
E 12
D 10
	__volatile struct simple_lock *alp;
E 10
I 10
	__volatile struct simplelock *alp;
I 12
	const char *id;
	int l;
E 12
E 10
{

I 16
	if (simplelockrecurse)
		return;
E 16
D 11
	if (alp->lock_data == 1)
		panic("simple_lock: lock held");
E 11
I 11
	if (alp->lock_data == 1) {
		if (lockpausetime == -1)
D 12
			panic("simple_lock: lock held");
		if (lockpausetime > 0) {
			printf("simple_lock: lock held...");
E 12
I 12
			panic("%s:%d: simple_lock: lock held", id, l);
D 16
		if (lockpausetime == 0) {
			printf("%s:%d: simple_lock: lock held\n", id, l);
E 16
I 16
		printf("%s:%d: simple_lock: lock held\n", id, l);
		if (lockpausetime == 1) {
E 16
I 14
			BACKTRACE(curproc);
E 14
D 16
		} else if (lockpausetime > 0) {
E 16
I 16
		} else if (lockpausetime > 1) {
E 16
			printf("%s:%d: simple_lock: lock held...", id, l);
E 12
			tsleep(&lockpausetime, PCATCH | PPAUSE, "slock",
			    lockpausetime * hz);
			printf(" continuing\n");
		}
	}
E 11
	alp->lock_data = 1;
I 15
	if (curproc)
		curproc->p_simple_locks++;
E 15
}

int
D 12
simple_lock_try(alp)
E 12
I 12
_simple_lock_try(alp, id, l)
E 12
D 10
	__volatile struct simple_lock *alp;
E 10
I 10
	__volatile struct simplelock *alp;
I 12
	const char *id;
	int l;
E 12
E 10
{

I 12
D 16
	/*
E 16
I 16
	if (alp->lock_data)
		return (0);
	if (simplelockrecurse)
		return (1);
E 16
E 12
D 11
	if (alp->lock_data == 1)
		panic("simple_lock: lock held");
E 11
I 11
D 18
	if (alp->lock_data == 1) {
		if (lockpausetime == -1)
D 12
			panic("simple_lock_try: lock held");
		if (lockpausetime > 0) {
			printf("simple_lock_try: lock held...");
E 12
I 12
			panic("%s:%d: simple_lock_try: lock held", id, l);
D 16
		if (lockpausetime == 0) {
			printf("%s:%d: simple_lock_try: lock held\n", id, l);
E 16
I 16
		printf("%s:%d: simple_lock_try: lock held\n", id, l);
		if (lockpausetime == 1) {
E 16
I 14
			BACKTRACE(curproc);
E 14
D 16
		} else if (lockpausetime > 0) {
E 16
I 16
		} else if (lockpausetime > 1) {
E 16
			printf("%s:%d: simple_lock_try: lock held...", id, l);
E 12
			tsleep(&lockpausetime, PCATCH | PPAUSE, "slock",
			    lockpausetime * hz);
			printf(" continuing\n");
		}
	}
E 18
I 12
D 16
	*/
	if (alp->lock_data)
		return (0);

E 16
E 12
E 11
	alp->lock_data = 1;
I 15
	if (curproc)
		curproc->p_simple_locks++;
E 15
	return (1);
}

void
D 12
simple_unlock(alp)
E 12
I 12
_simple_unlock(alp, id, l)
E 12
D 10
	__volatile struct simple_lock *alp;
E 10
I 10
	__volatile struct simplelock *alp;
I 12
	const char *id;
	int l;
E 12
E 10
{

I 16
	if (simplelockrecurse)
		return;
E 16
D 11
	if (alp->lock_data == 0)
		panic("simple_lock: lock not held");
E 11
I 11
	if (alp->lock_data == 0) {
		if (lockpausetime == -1)
D 12
			panic("simple_unlock: lock not held");
		if (lockpausetime > 0) {
			printf("simple_unlock: lock not held...");
E 12
I 12
			panic("%s:%d: simple_unlock: lock not held", id, l);
D 16
		if (lockpausetime == 0) {
			printf("%s:%d: simple_unlock: lock not held\n", id, l);
E 16
I 16
		printf("%s:%d: simple_unlock: lock not held\n", id, l);
		if (lockpausetime == 1) {
E 16
I 14
			BACKTRACE(curproc);
E 14
D 16
		} else if (lockpausetime > 0) {
E 16
I 16
		} else if (lockpausetime > 1) {
E 16
			printf("%s:%d: simple_unlock: lock not held...", id, l);
E 12
			tsleep(&lockpausetime, PCATCH | PPAUSE, "sunlock",
			    lockpausetime * hz);
			printf(" continuing\n");
		}
	}
E 11
	alp->lock_data = 0;
I 15
	if (curproc)
		curproc->p_simple_locks--;
E 15
}
#endif /* DEBUG && NCPUS == 1 */
E 9
E 1
