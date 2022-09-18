h05178
s 00005/00003/00149
d D 8.12 95/05/19 18:09:25 mckusick 12 11
c add LK_REENABLE flag
e
s 00006/00003/00146
d D 8.11 95/05/17 21:17:16 pendry 11 10
c give file and line in simple lock error diagnostics
e
s 00009/00009/00138
d D 8.10 95/05/14 00:06:36 mckusick 10 9
c struct simple_lock => struct simplelock; 
c move DRAIN bits to be set in freed memory
e
s 00006/00003/00143
d D 8.9 95/05/12 11:45:04 mckusick 9 8
c update draing to two stage; lockmgr goes back to taking a proc ptr
e
s 00010/00114/00136
d D 8.8 95/05/11 14:44:11 mckusick 8 7
c move stuff out to <machine/param.h> and kern_lock.c
e
s 00011/00001/00239
d D 8.7 95/04/27 14:04:58 mckusick 7 6
c add interlock; change proc pointer to pid
e
s 00044/00036/00196
d D 8.6 95/04/27 14:00:13 mckusick 6 5
c atomic_lock => simple_lock
e
s 00036/00012/00196
d D 8.5 95/04/13 16:58:07 mckusick 5 4
c add LK_DRAIN; add atomic_lock_try(); lint
e
s 00001/00000/00207
d D 8.4 95/04/11 13:19:01 mckusick 4 3
c add lockstatus to querry lock status
e
s 00037/00010/00170
d D 8.3 95/04/11 12:56:18 mckusick 3 2
c comments from cgd and mycroft
e
s 00010/00010/00170
d D 8.2 95/04/10 23:00:05 mckusick 2 1
c feedback from cgd
e
s 00180/00000/00000
d D 8.1 95/04/09 23:16:10 mckusick 1 0
c date and time created 95/04/09 23:16:10 by mckusick
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

#ifndef	_LOCK_H_
#define	_LOCK_H_

/*
D 8
 * XXX This belongs in <machine/param.h>, but is here for now.
 */
#define NCPUS 1

/*
D 6
 * An atomic spin lock.
E 6
I 6
 * A simple spin lock.
E 6
 *
 * This structure only sets one bit of data, but is sized based on the
 * minimum word size that can be operated on by the hardware test-and-set
 * instruction. It is only needed for multiprocessors, as uniprocessors
 * will always run to completion or a sleep. It is an error to hold one
 * of these locks while a process is sleeping.
 */
D 6
struct atomic_lk {
E 6
I 6
struct simple_lock {
E 6
	int	lock_data;
};

/*
I 6
 * XXX end of stuff that belongs in <machine/param.h>
 */

/*
E 8
E 6
 * The general lock structure.  Provides for multiple shared locks,
 * upgrading from shared to exclusive, and sleeping until the lock
D 8
 * can be gained.
E 8
I 8
D 10
 * can be gained. The simple_lock is defined in <machine/param.h>.
E 10
I 10
 * can be gained. The simple locks are defined in <machine/param.h>.
E 10
E 8
 */
struct lock {
D 6
	struct	atomic_lk lk_interlock;	/* lock on remaining fields */
E 6
I 6
D 10
	struct	simple_lock lk_interlock; /* lock on remaining fields */
E 10
I 10
	struct	simplelock lk_interlock; /* lock on remaining fields */
E 10
E 6
D 2
	int	lk_flags;		/* see below */
E 2
I 2
	u_int	lk_flags;		/* see below */
E 2
	int	lk_sharecount;		/* # of accepted shared locks */
D 8
	int	lk_exclusivecount;	/* # of recursive exclusive locks */
E 8
I 5
	int	lk_waitcount;		/* # of processes sleeping for lock */
E 5
D 8
	int	lk_prio;		/* priority at which to sleep */
E 8
I 8
	short	lk_exclusivecount;	/* # of recursive exclusive locks */
	short	lk_prio;		/* priority at which to sleep */
E 8
	char	*lk_wmesg;		/* resource sleeping (for tsleep) */
	int	lk_timo;		/* maximum sleep time (for tsleep) */
	pid_t	lk_lockholder;		/* pid of exclusive lock holder */
};
/*
D 3
 * Lock request types.
E 3
I 3
 * Lock request types:
 *   LK_SHARED - get one of many possible shared locks. If a process
 *	holding an exclusive lock requests a shared lock, the exclusive
 *	lock(s) will be downgraded to shared locks.
 *   LK_EXCLUSIVE - stop further shared locks, when they are cleared,
 *	grant a pending upgrade if it exists, then grant an exclusive
 *	lock. Only one exclusive lock may exist at a time, except that
 *	a process holding an exclusive lock may get additional exclusive
 *	locks if it explicitly sets the LK_CANRECURSE flag in the lock
 *	request, or if the LK_CANRECUSE flag was set when the lock was
 *	initialized.
 *   LK_UPGRADE - the process must hold a shared lock that it wants to
 *	have upgraded to an exclusive lock. Other processes may get
 *	exclusive access to the resource between the time that the upgrade
 *	is requested and the time that it is granted.
 *   LK_EXCLUPGRADE - the process must hold a shared lock that it wants to
 *	have upgraded to an exclusive lock. If the request succeeds, no
 *	other processes will have gotten exclusive access to the resource
 *	between the time that the upgrade is requested and the time that
 *	it is granted. However, if another process has already requested
 *	an upgrade, the request will fail (see error returns below).
 *   LK_DOWNGRADE - the process must hold an exclusive lock that it wants
 *	to have downgraded to a shared lock. If the process holds multiple
 *	(recursive) exclusive locks, they will all be downgraded to shared
 *	locks.
 *   LK_RELEASE - release one instance of a lock.
I 5
 *   LK_DRAIN - wait for all activity on the lock to end, then mark it
 *	decommissioned. This feature is used before freeing a lock that
 *	is part of a piece of memory that is about to be freed.
E 5
E 3
 *
 * These are flags that are passed to the lockmgr routine.
 */
D 9
#define LK_TYPE_MASK	0x00000007	/* type of lock sought */
E 9
I 9
#define LK_TYPE_MASK	0x0000000f	/* type of lock sought */
E 9
#define LK_SHARED	0x00000001	/* shared lock */
#define LK_EXCLUSIVE	0x00000002	/* exclusive lock */
#define LK_UPGRADE	0x00000003	/* shared-to-exclusive upgrade */
D 3
#define LK_DOWNGRADE	0x00000004	/* exclusive-to-shared downgrade */
#define LK_RELEASE	0x00000005	/* release any type of lock */
E 3
I 3
#define LK_EXCLUPGRADE	0x00000004	/* first shared-to-exclusive upgrade */
#define LK_DOWNGRADE	0x00000005	/* exclusive-to-shared downgrade */
#define LK_RELEASE	0x00000006	/* release any type of lock */
I 5
#define LK_DRAIN	0x00000007	/* wait for all lock activity to end */
E 5
E 3
/*
 * External lock flags.
 *
D 12
 * These flags may be set in lock_init to set their mode permanently,
 * or passed in as arguments to the lock manager.
E 12
I 12
 * The first three flags may be set in lock_init to set their mode permanently,
 * or passed in as arguments to the lock manager. The LK_REENABLE flag may be
 * set only at the release of a lock obtained by drain.
E 12
 */
D 12
#define LK_EXTFLG_MASK	0x000000f0	/* mask of external flags */
E 12
I 12
#define LK_EXTFLG_MASK	0x00000070	/* mask of external flags */
E 12
#define LK_NOWAIT	0x00000010	/* do not sleep to await lock */
#define LK_SLEEPFAIL	0x00000020	/* sleep, then return failure */
#define LK_CANRECURSE	0x00000040	/* allow recursive exclusive lock */
I 12
#define LK_REENABLE	0x00000080	/* lock is be reenabled after drain */
E 12
/*
 * Internal lock flags.
 *
 * These flags are used internally to the lock manager.
 */
D 5
#define LK_WAITING	0x00000100	/* process is sleeping on lock */
#define LK_WANT_UPGRADE	0x00000200	/* waiting for share-to-excl upgrade */
#define LK_WANT_EXCL	0x00000400	/* exclusive lock sought */
#define LK_HAVE_EXCL	0x00000800	/* exclusive lock obtained */
E 5
I 5
#define LK_WANT_UPGRADE	0x00000100	/* waiting for share-to-excl upgrade */
#define LK_WANT_EXCL	0x00000200	/* exclusive lock sought */
#define LK_HAVE_EXCL	0x00000400	/* exclusive lock obtained */
#define LK_WAITDRAIN	0x00000800	/* process waiting for lock to drain */
D 9
#define LK_DRAINED	0x00001000	/* lock has been decommissioned */
E 9
I 9
D 10
#define LK_DRAINING	0x00001000	/* lock is being drained */
#define LK_DRAINED	0x00002000	/* lock has been decommissioned */
E 10
I 10
#define LK_DRAINING	0x00004000	/* lock is being drained */
#define LK_DRAINED	0x00008000	/* lock has been decommissioned */
E 10
E 9
I 7
/*
 * Control flags
 *
 * Non-persistent external flags.
 */
#define LK_INTERLOCK	0x00010000	/* unlock passed simple lock after
					   getting lk_interlock */
#define LK_RETRY	0x00020000	/* vn_lock: retry until locked */
E 7
I 6

E 6
E 5
/*
 * Lock return status.
 *
 * Successfully obtained locks return 0. Locks will always succeed
 * unless one of the following is true:
I 3
 *	LK_FORCEUPGRADE is requested and some other process has already
 *	    requested a lock upgrade (returns EBUSY).
E 3
 *	LK_WAIT is set and a sleep would be required (returns EBUSY).
 *	LK_SLEEPFAIL is set and a sleep was done (returns ENOLCK).
 *	PCATCH is set in lock priority and a signal arrives (returns
 *	    either EINTR or ERESTART if system calls is to be restarted).
 *	Non-null lock timeout and timeout expires (returns EWOULDBLOCK).
D 3
 * A failed lock attempt always returns a non-zero error value.
 * If the lock acquisition caused the process to sleep, the LK_SLEPT
 * flag is set otherwise it is cleared.
E 3
I 3
 * A failed lock attempt always returns a non-zero error value. No lock
 * is held after an error return (in particular, a failed LK_UPGRADE
 * or LK_FORCEUPGRADE will have released its shared access lock).
E 3
 */
D 3
#define LK_SLEPT	0x00001000	/* process slept while acquiring lock */
E 3

/*
 * Indicator that no process holds exclusive lock
 */
I 7
#define LK_KERNPROC ((pid_t) -2)
E 7
#define LK_NOPROC ((pid_t) -1)

I 9
struct proc;

E 9
D 8
void	lock_init __P((struct lock *, int prio, char *wmesg, int timo,
E 8
I 8
void	lockinit __P((struct lock *, int prio, char *wmesg, int timo,
E 8
			int flags));
D 2
int	lockmgr __P((struct lock *, struct proc *, int flags));
E 2
I 2
D 3
int	lockmgr __P((struct lock *, struct proc *, u_int flags));
E 3
I 3
D 5
int	lockmgr __P((volatile struct lock *, struct proc *, u_int flags));
E 5
I 5
D 7
int	lockmgr __P((__volatile struct lock *, u_int flags, struct proc *));
E 7
I 7
int	lockmgr __P((__volatile struct lock *, u_int flags,
D 9
			struct simple_lock *, pid_t pid));
E 9
I 9
D 10
			struct simple_lock *, struct proc *p));
E 10
I 10
			struct simplelock *, struct proc *p));
E 10
E 9
E 7
E 5
I 4
int	lockstatus __P((struct lock *));
E 4
E 3
E 2

D 8
#if NCPUS > 1
/*
 * The simple-lock routines are the primitives out of which the lock
 * package is built. The machine-dependent code must implement an
D 6
 * atomic test_and_set operation that indivisibly sets the atomic_lk
E 6
I 6
 * atomic test_and_set operation that indivisibly sets the simple_lock
E 6
 * to non-zero and returns its old value. It also assumes that the
D 6
 * setting of the lock to zero below is indivisible. Atomic locks may
E 6
I 6
 * setting of the lock to zero below is indivisible. Simple locks may
E 6
 * only be used for exclusive locks.
 */
D 2
inline void
E 2
I 2
D 6
__inline void
E 2
atomic_lock_init(lkp)
	struct atomic_lk *lkp;
E 6
I 6
static __inline void
simple_lock_init(lkp)
	struct simple_lock *lkp;
E 6
{

	lkp->lock_data = 0;
}

D 2
inline void
E 2
I 2
D 6
__inline void
E 2
atomic_lock(lkp)
D 3
	struct atomic_lk *lkp;
E 3
I 3
D 5
	volatile struct atomic_lk *lkp;
E 5
I 5
	__volatile struct atomic_lk *lkp;
E 6
I 6
static __inline void
simple_lock(lkp)
	__volatile struct simple_lock *lkp;
E 6
E 5
E 3
{

	while (test_and_set(&lkp->lock_data))
		continue;
}

I 5
D 6
__inline int
atomic_lock_try(lkp)
	__volatile struct atomic_lk *lkp;
E 6
I 6
static __inline int
simple_lock_try(lkp)
	__volatile struct simple_lock *lkp;
E 6
{

	return (!test_and_set(&lkp->lock_data))
}

E 5
D 2
inline void
E 2
I 2
D 6
__inline void
E 2
atomic_unlock(lkp)
	struct atomic_lk *lkp;
E 6
I 6
static __inline void
simple_unlock(lkp)
	struct simple_lock *lkp;
E 6
{

	lkp->lock_data = 0;
}

#else /* NCPUS == 1, so no multiprocessor locking is necessary */

E 8
D 2
#ifdef DIAGNOSTIC
inline void
E 2
I 2
#ifdef DEBUG
D 6
__inline void
E 2
atomic_lock_init(alp)
	struct atomic_lk *alp;
E 6
I 6
D 8
static __inline void
simple_lock_init(alp)
	struct simple_lock *alp;
E 6
{

	alp->lock_data = 0;
}

D 2
inline void
E 2
I 2
D 6
__inline void
E 2
atomic_lock(alp)
D 3
	struct atomic_lk *alp;
E 3
I 3
D 5
	volatile struct atomic_lk *alp;
E 5
I 5
	__volatile struct atomic_lk *alp;
E 6
I 6
static __inline void
simple_lock(alp)
	__volatile struct simple_lock *alp;
E 6
E 5
E 3
{
I 6
	extern const char *simple_lock_held;
E 6

	if (alp->lock_data == 1)
D 6
		panic("atomic lock held");
E 6
I 6
		panic(simple_lock_held);
E 6
D 5
	else
		alp->lock_data = 1;
E 5
I 5
	alp->lock_data = 1;
E 5
}

I 5
D 6
__inline int
atomic_lock_try(alp)
	__volatile struct atomic_lk *alp;
E 6
I 6
static __inline int
simple_lock_try(alp)
	__volatile struct simple_lock *alp;
E 6
{
I 6
	extern const char *simple_lock_held;
E 6

	if (alp->lock_data == 1)
D 6
		panic("atomic lock held");
E 6
I 6
		panic(simple_lock_held);
E 6
	alp->lock_data = 1;
	return (1);
}

E 5
D 2
inline void
E 2
I 2
D 6
__inline void
E 2
atomic_unlock(alp)
	struct atomic_lk *alp;
E 6
I 6
static __inline void
simple_unlock(alp)
	struct simple_lock *alp;
E 6
{
I 6
	extern const char *simple_lock_not_held;
E 6

	if (alp->lock_data == 0)
D 6
		panic("atomic lock not held");
E 6
I 6
		panic(simple_lock_not_held);
E 6
D 5
	else
		alp->lock_data = 0;
E 5
I 5
	alp->lock_data = 0;
E 5
}

E 8
I 8
D 10
void simple_unlock __P((__volatile struct simple_lock *alp));
int simple_lock_try __P((__volatile struct simple_lock *alp));
void simple_lock __P((__volatile struct simple_lock *alp));
void simple_lock_init __P((struct simple_lock *alp));
E 10
I 10
D 11
void simple_unlock __P((__volatile struct simplelock *alp));
int simple_lock_try __P((__volatile struct simplelock *alp));
void simple_lock __P((__volatile struct simplelock *alp));
E 11
I 11
void _simple_unlock __P((__volatile struct simplelock *alp, const char *, int));
#define simple_unlock(alp) _simple_unlock(alp, __FILE__, __LINE__)
int _simple_lock_try __P((__volatile struct simplelock *alp, const char *, int));
#define simple_lock_try(alp) _simple_lock_try(alp, __FILE__, __LINE__)
void _simple_lock __P((__volatile struct simplelock *alp, const char *, int));
#define simple_lock(alp) _simple_lock(alp, __FILE__, __LINE__)
E 11
void simple_lock_init __P((struct simplelock *alp));
E 10
E 8
D 5
#else /* !DIAGNOSTIC */
E 5
I 5
#else /* !DEBUG */
I 8
#if NCPUS == 1 /* no multiprocessor locking is necessary */
E 8
E 5
D 6
#define	atomic_lock_init(alp)
#define	atomic_lock(alp)
I 5
#define	atomic_lock_try(alp)	(1)	/* always succeeds */
E 5
#define	atomic_unlock(alp)
E 6
I 6
#define	simple_lock_init(alp)
#define	simple_lock(alp)
#define	simple_lock_try(alp)	(1)	/* always succeeds */
#define	simple_unlock(alp)
E 6
D 8
#endif /* !DIAGNOSTIC */

E 8
#endif /* NCPUS == 1 */
I 8
#endif /* !DEBUG */
E 8

#endif /* !_LOCK_H_ */
E 1
