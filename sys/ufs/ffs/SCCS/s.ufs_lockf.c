h39140
s 00010/00003/00671
d D 8.3 94/01/06 16:17:30 mckusick 13 12
c avoid panic when process is signaled and lock clears before it gets to run
c (from karels@bsdi.com)
e
s 00000/00001/00674
d D 8.2 94/01/04 22:20:23 bostic 12 11
c lint
e
s 00002/00002/00673
d D 8.1 93/06/11 16:29:00 bostic 11 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00001/00674
d D 7.9.1.1 91/12/19 20:32:54 mckusick 10 9
c debugging code for tracking down stray locks;
c (needs spare to be initialized to zero in ufs_advlock)
e
s 00013/00002/00662
d D 7.9 91/12/19 20:29:33 mckusick 9 8
c have to remove lock from waiting chain when giving up
e
s 00022/00012/00642
d D 7.8 91/11/01 18:05:45 bostic 8 7
c prototype cleanups
e
s 00002/00003/00652
d D 7.7 91/07/02 17:13:18 mckusick 7 6
c avoid null pointers
e
s 00001/00001/00654
d D 7.6 91/05/30 10:37:45 mckusick 6 5
c type glitch
e
s 00002/00002/00653
d D 7.5 91/05/25 15:30:09 bostic 5 4
c delete obsolete printf formats (%X -> %lx)
e
s 00002/00000/00653
d D 7.4 91/05/15 09:19:28 mckusick 4 3
c return type == F_UNLCK to F_GETLK when no blocking lock (4.3BSD-reno/sys/11)
e
s 00004/00008/00649
d D 7.3 91/03/19 10:30:31 karels 3 2
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; remove ../ufs/ from includes; consolidate *nullops();
c chown/fchmod use proc's credentials, not file's
e
s 00398/00240/00259
d D 7.2 91/02/25 22:21:15 mckusick 2 1
c move locking specific code from ufs_vnops.c; fix numerous bugs
e
s 00499/00000/00000
d D 7.1 91/02/01 16:28:24 mckusick 1 0
c date and time created 91/02/01 16:28:24 by mckusick
e
u
U
f b 
t
T
I 1
/*
D 11
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * Scooter Morris at Genentech Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 8
#include "param.h"
#include "systm.h"
D 3
#include "user.h"
E 3
#include "kernel.h"
#include "file.h"
#include "proc.h"
D 3
#include "socketvar.h"
#include "socket.h"
E 3
#include "vnode.h"
D 3
#include "ioctl.h"
#include "tty.h"
E 3
#include "malloc.h"
#include "fcntl.h"
E 8
I 8
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/file.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/malloc.h>
#include <sys/fcntl.h>
E 8
D 3
#include "../ufs/lockf.h"
#include "../ufs/quota.h"
#include "../ufs/inode.h"
E 3
I 3

D 8
#include "lockf.h"
#include "quota.h"
#include "inode.h"
E 8
I 8
#include <ufs/ufs/lockf.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufs_extern.h>
E 8
E 3

D 2
#ifdef	LOCKF_DEBUG
E 2
I 2
/*
 * This variable controls the maximum number of processes that will
 * be checked in doing deadlock detection.
 */
int maxlockdepth = MAXDEPTH;

#ifdef LOCKF_DEBUG
E 2
int	lockf_debug = 0;
D 8
#endif /* LOCKF_DEBUG */
E 8
I 8
#endif
E 8

D 2
/*
 * Common code for ufs byte range locking
 */
E 2
I 2
#define NOLOCKF (struct lockf *)0
#define SELF	0x1
#define OTHERS	0x2
E 2

I 10
#define HASBLOCK 0x100

E 10
/*
D 2
 * Add a lock to the list.  Upgrade or downgrade our locks, if
 * they conflict.
E 2
I 2
 * Set a byte-range lock.
E 2
 */
I 8
int
E 8
D 2
struct lockf *
lf_addlock(lock)
E 2
I 2
lf_setlock(lock)
E 2
	register struct lockf *lock;
{
D 2
	register struct lockf *lf = lock->lf_inode->i_lockf;
	struct lockf *lastlock = (struct lockf *)0;
	struct lockf *prev, *overlap, *ltmp;
	int ovcase;
E 2
I 2
	register struct lockf *block;
	struct inode *ip = lock->lf_inode;
	struct lockf **prev, *overlap, *ltmp;
	static char lockstr[] = "lockf";
	int ovcase, priority, needtolink, error;
E 2

I 2
#ifdef LOCKF_DEBUG
	if (lockf_debug & 1)
		lf_print("lf_setlock", lock);
#endif /* LOCKF_DEBUG */

E 2
	/*
D 2
	 * First, see if we overlap with anything.
E 2
I 2
	 * Set the priority
E 2
	 */
D 2
	ovcase = lf_findoverlap(lf, lock, &prev, &overlap);
E 2
I 2
	priority = PLOCK;
	if (lock->lf_type == F_WRLCK)
		priority += 4;
	priority |= PCATCH;
E 2
	/*
D 2
	 * Add the new lock
E 2
I 2
	 * Scan lock list for this file looking for locks that would block us.
E 2
	 */
D 2
	if (prev != (struct lockf *)0)
		prev->lf_next = lock;
	else
		lock->lf_inode->i_lockf = lock;
	lock->lf_next = overlap;
E 2
I 2
	while (block = lf_getblock(lock)) {
		/*
		 * Free the structure and return if nonblocking.
		 */
		if ((lock->lf_flags & F_WAIT) == 0) {
			FREE(lock, M_LOCKF);
			return (EAGAIN);
		}
		/*
		 * We are blocked. Since flock style locks cover
		 * the whole file, there is no chance for deadlock.
		 * For byte-range locks we must check for deadlock.
		 *
		 * Deadlock detection is done by looking through the
		 * wait channels to see if there are any cycles that
		 * involve us. MAXDEPTH is set just to make sure we
		 * do not go off into neverland.
		 */
		if ((lock->lf_flags & F_POSIX) &&
		    (block->lf_flags & F_POSIX)) {
			register struct proc *wproc;
			register struct lockf *waitblock;
			int i = 0;

			/* The block is waiting on something */
			wproc = (struct proc *)block->lf_id;
			while (wproc->p_wchan &&
			       (wproc->p_wmesg == lockstr) &&
			       (i++ < maxlockdepth)) {
				waitblock = (struct lockf *)wproc->p_wchan;
				/* Get the owner of the blocking lock */
				waitblock = waitblock->lf_next;
				if ((waitblock->lf_flags & F_POSIX) == 0)
					break;
				wproc = (struct proc *)waitblock->lf_id;
				if (wproc == (struct proc *)lock->lf_id) {
					free(lock, M_LOCKF);
					return (EDEADLK);
				}
			}
		}
		/*
		 * For flock type locks, we must first remove
		 * any shared locks that we hold before we sleep
		 * waiting for an exclusive lock.
		 */
		if ((lock->lf_flags & F_FLOCK) &&
		    lock->lf_type == F_WRLCK) {
			lock->lf_type = F_UNLCK;
			(void) lf_clearlock(lock);
			lock->lf_type = F_WRLCK;
		}
		/*
		 * Add our lock to the blocked list and sleep until we're free.
		 * Remember who blocked us (for deadlock detection).
		 */
		lock->lf_next = block;
		lf_addblock(block, lock);
#ifdef LOCKF_DEBUG
		if (lockf_debug & 1) {
			lf_print("lf_setlock: blocking on", block);
			lf_printlist("lf_setlock", block);
		}
#endif /* LOCKF_DEBUG */
D 6
		if (error = tsleep((caddr_t *)lock, priority, lockstr, 0)) {
E 6
I 6
		if (error = tsleep((caddr_t)lock, priority, lockstr, 0)) {
E 6
D 9
			free(lock, M_LOCKF);
			return (error);
E 9
I 9
			/*
			 * Delete ourselves from the waiting to lock list.
			 */
			for (block = lock->lf_next;
			     block != NOLOCKF;
			     block = block->lf_block) {
				if (block->lf_block != lock)
					continue;
				block->lf_block = block->lf_block->lf_block;
I 10
				block->lf_spare = block->lf_block->lf_block;
				if ((block->lf_block->lf_flags & HASBLOCK) == 0)
					block->lf_flags &= ~HASBLOCK;
E 10
D 13
				free(lock, M_LOCKF);
				return (error);
E 13
I 13
				break;
E 13
			}
D 13
			panic("lf_setlock: lost lock");
E 13
I 13
			/*
			 * If we did not find ourselves on the list, but
			 * are still linked onto a lock list, then something
			 * is very wrong.
			 */
			if (block == NOLOCKF && lock->lf_next != NOLOCKF)
				panic("lf_setlock: lost lock");
			free(lock, M_LOCKF);
			return (error);
E 13
E 9
		}
	}
E 2
	/*
I 2
	 * No blocks!!  Add the lock.  Note that we will
	 * downgrade or upgrade any overlapping locks this
	 * process already owns.
	 *
E 2
	 * Skip over locks owned by other processes.
D 2
	 * Merge any locks that are owned by ourselves.
E 2
I 2
	 * Handle any locks that overlap and are owned by ourselves.
E 2
	 */
I 2
	prev = &ip->i_lockf;
	block = ip->i_lockf;
	needtolink = 1;
E 2
	for (;;) {
D 2
		for (;;) {
			/*
			 * If no overlap, we are done.
			 */
			if (ovcase == 0)
				return;
			lf = overlap->lf_next;
			if (overlap->lf_id == lock->lf_id)
				break;
			/*
			 * We overlap with another process.
			 * If it is a block, panic.
			 */
			if (lock->lf_type == F_WRLCK ||
			    overlap->lf_type == F_WRLCK)
				panic("blocked in addlock");
			ovcase = lf_findoverlap(lf, lock, &prev, &overlap);
		}
E 2
I 2
D 7
		ovcase = lf_findoverlap(block, lock, SELF, &prev, &overlap);
		block = overlap->lf_next;
E 7
I 7
		if (ovcase = lf_findoverlap(block, lock, SELF, &prev, &overlap))
			block = overlap->lf_next;
E 7
E 2
		/*
D 2
		 * Five cases:
E 2
I 2
		 * Six cases:
		 *	0) no overlap
E 2
		 *	1) overlap == lock
		 *	2) overlap contains lock
		 *	3) lock contains overlap
		 *	4) overlap starts before lock
		 *	5) overlap ends after lock
		 */
		switch (ovcase) {
I 2
		case 0: /* no overlap */
			if (needtolink) {
				*prev = lock;
				lock->lf_next = overlap;
			}
			break;
E 2

		case 1: /* overlap == lock */
			/*
D 2
			 * Undo spurious addition of lock to list.
			 */
			if (prev != (struct lockf *)0)
				prev->lf_next = overlap;
			else
				lock->lf_inode->i_lockf = overlap;
			/*
E 2
			 * If downgrading lock, others may be
			 * able to acquire it.
			 */
			if (lock->lf_type == F_RDLCK &&
			    overlap->lf_type == F_WRLCK)
				lf_wakelock(overlap);
			overlap->lf_type = lock->lf_type;
D 2
			free(lock, M_LOCKF);
			return;
E 2
I 2
			FREE(lock, M_LOCKF);
			lock = overlap; /* for debug output below */
			break;
E 2

		case 2: /* overlap contains lock */
			/*
D 2
			 * Undo spurious addition of lock to list.
E 2
I 2
			 * Check for common starting point and different types.
E 2
			 */
D 2
			if (prev != (struct lockf *)0)
				prev->lf_next = overlap;
			else
				lock->lf_inode->i_lockf = overlap;
E 2
			if (overlap->lf_type == lock->lf_type) {
				free(lock, M_LOCKF);
D 2
				return;
E 2
I 2
				lock = overlap; /* for debug output below */
				break;
E 2
			}
D 2
			lf_split(overlap, lock);
E 2
I 2
			if (overlap->lf_start == lock->lf_start) {
				*prev = lock;
				lock->lf_next = overlap;
				overlap->lf_start = lock->lf_end + 1;
			} else
				lf_split(overlap, lock);
E 2
			lf_wakelock(overlap);
D 2
			return;
E 2
I 2
			break;
E 2

		case 3: /* lock contains overlap */
			/*
			 * If downgrading lock, others may be able to
			 * acquire it, otherwise take the list.
			 */
			if (lock->lf_type == F_RDLCK &&
			    overlap->lf_type == F_WRLCK) {
				lf_wakelock(overlap);
			} else {
				ltmp = lock->lf_block;
				lock->lf_block = overlap->lf_block;
				lf_addblock(lock, ltmp);
			}
			/*
D 2
			 * Delete the overlap.
E 2
I 2
			 * Add the new lock if necessary and delete the overlap.
E 2
			 */
D 2
			lock->lf_next = overlap->lf_next;
E 2
I 2
			if (needtolink) {
				*prev = lock;
				lock->lf_next = overlap->lf_next;
				prev = &lock->lf_next;
				needtolink = 0;
			} else
				*prev = overlap->lf_next;
E 2
			free(overlap, M_LOCKF);
D 2
			break;
E 2
I 2
			continue;
E 2

		case 4: /* overlap starts before lock */
			/*
D 2
			 * Reverse lock and overlap on the list
E 2
I 2
			 * Add lock after overlap on the list.
E 2
			 */
D 2
			if (prev != (struct lockf *)0)
				prev->lf_next = overlap;
			else
				lock->lf_inode->i_lockf = overlap;
E 2
			lock->lf_next = overlap->lf_next;
			overlap->lf_next = lock;
			overlap->lf_end = lock->lf_start - 1;
I 2
			prev = &lock->lf_next;
E 2
			lf_wakelock(overlap);
D 2
			break;
E 2
I 2
			needtolink = 0;
			continue;
E 2

		case 5: /* overlap ends after lock */
I 2
			/*
			 * Add the new lock before overlap.
			 */
			if (needtolink) {
				*prev = lock;
				lock->lf_next = overlap;
			}
E 2
			overlap->lf_start = lock->lf_end + 1;
			lf_wakelock(overlap);
D 2
			return;
E 2
I 2
			break;
E 2
		}
D 2
		ovcase = lf_findoverlap(lf, lock, &prev, &overlap);
E 2
I 2
		break;
E 2
	}
D 2
	/* NOTREACHED */
E 2
I 2
D 7
out:
E 7
#ifdef LOCKF_DEBUG
	if (lockf_debug & 1) {
		lf_print("lf_setlock: got the lock", lock);
		lf_printlist("lf_setlock", lock);
	}
#endif /* LOCKF_DEBUG */
	return (0);
E 2
}

/*
I 2
 * Remove a byte-range lock on an inode.
 *
 * Generally, find the lock (or an overlap to that lock)
 * and remove it (or shrink it), then wakeup anyone we can.
 */
I 8
int
E 8
lf_clearlock(unlock)
	register struct lockf *unlock;
{
	struct inode *ip = unlock->lf_inode;
	register struct lockf *lf = ip->i_lockf;
	struct lockf *overlap, **prev;
	int ovcase;

	if (lf == NOLOCKF)
		return (0);
#ifdef LOCKF_DEBUG
	if (unlock->lf_type != F_UNLCK)
		panic("lf_clearlock: bad type");
	if (lockf_debug & 1)
		lf_print("lf_clearlock", unlock);
#endif /* LOCKF_DEBUG */
	prev = &ip->i_lockf;
	while (ovcase = lf_findoverlap(lf, unlock, SELF, &prev, &overlap)) {
		/*
		 * Wakeup the list of locks to be retried.
		 */
		lf_wakelock(overlap);

		switch (ovcase) {

		case 1: /* overlap == lock */
			*prev = overlap->lf_next;
			FREE(overlap, M_LOCKF);
			break;

		case 2: /* overlap contains lock: split it */
			if (overlap->lf_start == unlock->lf_start) {
				overlap->lf_start = unlock->lf_end + 1;
				break;
			}
			lf_split(overlap, unlock);
			overlap->lf_next = unlock->lf_next;
			break;

		case 3: /* lock contains overlap */
			*prev = overlap->lf_next;
			lf = overlap->lf_next;
			free(overlap, M_LOCKF);
			continue;

		case 4: /* overlap starts before lock */
			overlap->lf_end = unlock->lf_start - 1;
			prev = &overlap->lf_next;
			lf = overlap->lf_next;
			continue;

		case 5: /* overlap ends after lock */
			overlap->lf_start = unlock->lf_end + 1;
			break;
		}
		break;
	}
#ifdef LOCKF_DEBUG
	if (lockf_debug & 1)
		lf_printlist("lf_clearlock", unlock);
#endif /* LOCKF_DEBUG */
	return (0);
}

/*
 * Check whether there is a blocking lock,
 * and if so return its process identifier.
 */
I 8
int
E 8
lf_getlock(lock, fl)
	register struct lockf *lock;
	register struct flock *fl;
{
	register struct lockf *block;
D 12
	off_t start, end;
E 12

#ifdef LOCKF_DEBUG
	if (lockf_debug & 1)
		lf_print("lf_getlock", lock);
#endif /* LOCKF_DEBUG */

	if (block = lf_getblock(lock)) {
		fl->l_type = block->lf_type;
		fl->l_whence = SEEK_SET;
		fl->l_start = block->lf_start;
		if (block->lf_end == -1)
			fl->l_len = 0;
		else
			fl->l_len = block->lf_end - block->lf_start + 1;
		if (block->lf_flags & F_POSIX)
			fl->l_pid = ((struct proc *)(block->lf_id))->p_pid;
		else
			fl->l_pid = -1;
I 4
	} else {
		fl->l_type = F_UNLCK;
E 4
	}
	return (0);
}

/*
E 2
 * Walk the list of locks for an inode and
 * return the first blocking lock.
 */
struct lockf *
lf_getblock(lock)
	register struct lockf *lock;
{
D 2
	struct lockf *prev, *overlap, *lf = lock->lf_inode->i_lockf;
E 2
I 2
	struct lockf **prev, *overlap, *lf = lock->lf_inode->i_lockf;
E 2
	int ovcase;

D 2
	while (ovcase = lf_findoverlap(lf, lock, &prev, &overlap)) {
E 2
I 2
	prev = &lock->lf_inode->i_lockf;
	while (ovcase = lf_findoverlap(lf, lock, OTHERS, &prev, &overlap)) {
E 2
		/*
		 * We've found an overlap, see if it blocks us
		 */
D 2
		if ((lock->lf_type == F_WRLCK || overlap->lf_type == F_WRLCK) &&
		    overlap->lf_id != lock->lf_id)
E 2
I 2
		if ((lock->lf_type == F_WRLCK || overlap->lf_type == F_WRLCK))
E 2
			return (overlap);
		/*
		 * Nope, point to the next one on the list and
		 * see if it blocks us
		 */
		lf = overlap->lf_next;
	}
D 2
	return ((struct lockf *)0);
E 2
I 2
	return (NOLOCKF);
E 2
}

/*
 * Walk the list of locks for an inode to
 * find an overlapping lock (if any).
 *
 * NOTE: this returns only the FIRST overlapping lock.  There
 *	 may be more than one.
 */
I 8
int
E 8
D 2
lf_findoverlap(list, lock, prev, overlap)
	struct lockf *list;
E 2
I 2
lf_findoverlap(lf, lock, type, prev, overlap)
	register struct lockf *lf;
E 2
	struct lockf *lock;
D 2
	struct lockf **prev;
E 2
I 2
	int type;
	struct lockf ***prev;
E 2
	struct lockf **overlap;
{
D 2
	register struct lockf *lf = list;
E 2
	off_t start, end;

D 2
	*prev = (struct lockf *) 0;
E 2
	*overlap = lf;
D 2
	if ((lock == (struct lockf *)0) || (lf == (struct lockf *)0))
E 2
I 2
	if (lf == NOLOCKF)
E 2
		return (0);
#ifdef LOCKF_DEBUG
D 2
	if (lockf_debug & 1)
E 2
I 2
	if (lockf_debug & 2)
E 2
		lf_print("lf_findoverlap: looking for overlap in", lock);
#endif /* LOCKF_DEBUG */
	start = lock->lf_start;
	end = lock->lf_end;
D 2
	while (lf != (struct lockf *)0) {
#ifdef	LOCKF_DEBUG
		if (lockf_debug & 1)
E 2
I 2
	while (lf != NOLOCKF) {
		if (((type & SELF) && lf->lf_id != lock->lf_id) ||
		    ((type & OTHERS) && lf->lf_id == lock->lf_id)) {
			*prev = &lf->lf_next;
			*overlap = lf = lf->lf_next;
			continue;
		}
#ifdef LOCKF_DEBUG
		if (lockf_debug & 2)
E 2
			lf_print("\tchecking", lf);
#endif /* LOCKF_DEBUG */
		/*
D 2
		 * Have we gone far enough?
		 */
		if (end != -1 && lf->lf_start > end)
#ifdef	LOCKF_DEBUG
			if (lockf_debug & 1)
				print("no overlap\n");
#endif /* LOCKF_DEBUG */
			return (0);
		/*
		 * OK, find the overlap
E 2
I 2
		 * OK, check for overlap
E 2
		 *
D 2
		 * Five cases:
E 2
I 2
		 * Six cases:
		 *	0) no overlap
E 2
		 *	1) overlap == lock
		 *	2) overlap contains lock
		 *	3) lock contains overlap
		 *	4) overlap starts before lock
		 *	5) overlap ends after lock
		 */
I 2
		if ((lf->lf_end != -1 && start > lf->lf_end) ||
		    (end != -1 && lf->lf_start > end)) {
			/* Case 0 */
#ifdef LOCKF_DEBUG
			if (lockf_debug & 2)
				printf("no overlap\n");
#endif /* LOCKF_DEBUG */
			if ((type & SELF) && end != -1 && lf->lf_start > end)
				return (0);
			*prev = &lf->lf_next;
			*overlap = lf = lf->lf_next;
			continue;
		}
E 2
		if ((lf->lf_start == start) && (lf->lf_end == end)) {
			/* Case 1 */
#ifdef LOCKF_DEBUG
D 2
			if (lockf_debug & 1)
				printf("overlap == lock\n"); break;
E 2
I 2
			if (lockf_debug & 2)
				printf("overlap == lock\n");
E 2
#endif /* LOCKF_DEBUG */
			return (1);
D 2
		} else if ((lf->lf_start <= start) &&
E 2
I 2
		}
		if ((lf->lf_start <= start) &&
E 2
		    (end != -1) &&
		    ((lf->lf_end >= end) || (lf->lf_end == -1))) {
			/* Case 2 */
#ifdef LOCKF_DEBUG
D 2
			if (lockf_debug & 1)
				printf("overlap contains lock\n"); break;
E 2
I 2
			if (lockf_debug & 2)
				printf("overlap contains lock\n");
E 2
#endif /* LOCKF_DEBUG */
			return (2);
D 2
		} else if ((start <= lf->lf_start) &&
		    (lf->lf_end != -1) &&
		    ((end == -1) || (end >= lf->lf_end))) {
E 2
I 2
		}
		if (start <= lf->lf_start &&
		           (end == -1 ||
			   (lf->lf_end != -1 && end >= lf->lf_end))) {
E 2
			/* Case 3 */
#ifdef LOCKF_DEBUG
D 2
			if (lockf_debug & 1)
				printf("lock contains overlap\n"); break;
E 2
I 2
			if (lockf_debug & 2)
				printf("lock contains overlap\n");
E 2
#endif /* LOCKF_DEBUG */
			return (3);
D 2
		} else if ((lf->lf_start < start) &&
E 2
I 2
		}
		if ((lf->lf_start < start) &&
E 2
			((lf->lf_end >= start) || (lf->lf_end == -1))) {
			/* Case 4 */
#ifdef LOCKF_DEBUG
D 2
			if (lockf_debug & 1)
				printf("overlap starts before lock\n"); break;
E 2
I 2
			if (lockf_debug & 2)
				printf("overlap starts before lock\n");
E 2
#endif /* LOCKF_DEBUG */
			return (4);
D 2
		} else if ((lf->lf_start > start) &&
E 2
I 2
		}
		if ((lf->lf_start > start) &&
E 2
			(end != -1) &&
			((lf->lf_end > end) || (lf->lf_end == -1))) {
			/* Case 5 */
#ifdef LOCKF_DEBUG
D 2
			if (lockf_debug & 1)
				printf("overlap ends after lock\n"); break;
E 2
I 2
			if (lockf_debug & 2)
				printf("overlap ends after lock\n");
E 2
#endif /* LOCKF_DEBUG */
			return (5);
		}
D 2
		*prev = lf;
		*overlap = lf = lf->lf_next;
E 2
I 2
		panic("lf_findoverlap: default");
E 2
	}
D 2
	/* No overlap */
#ifdef	LOCKF_DEBUG
	if (lockf_debug & 1)
		print("no overlap\n");
#endif /* LOCKF_DEBUG */
E 2
	return (0);
}

/*
 * Add a lock to the end of the blocked list.
 */
I 8
void
E 8
lf_addblock(lock, blocked)
	struct lockf *lock;
	struct lockf *blocked;
{
	register struct lockf *lf;

D 2
	if (lock == (struct lockf *)0)
E 2
I 2
	if (blocked == NOLOCKF)
E 2
		return;
D 2
	if ((lf = lock->lf_block) == (struct lockf *)0) {
E 2
I 2
#ifdef LOCKF_DEBUG
	if (lockf_debug & 2) {
		lf_print("addblock: adding", blocked);
		lf_print("to blocked list of", lock);
	}
#endif /* LOCKF_DEBUG */
	if ((lf = lock->lf_block) == NOLOCKF) {
E 2
		lock->lf_block = blocked;
I 10
		lock->lf_spare = blocked;
		lock->lf_flags |= HASBLOCK;
E 10
		return;
	}
D 2
	while (lf->lf_block != (struct lockf *)0)
E 2
I 2
	while (lf->lf_block != NOLOCKF)
E 2
		lf = lf->lf_block;
	lf->lf_block = blocked;
I 10
	lf->lf_spare = blocked;
	lf->lf_flags |= HASBLOCK;
E 10
	return;
}

/*
D 2
 * Combine two locks into a single lock
 */
lf_combine(lock1, lock2)
	struct lockf *lock1;
	struct lockf *lock2;
{
#ifdef LOCKF_DEBUG
	if (lockf_debug & 1) {
		lf_print("lf_combine", lock1);
		lf_print("combining with", lock2);
	}
#endif /* LOCKF_DEBUG */
	/*
	 * Sanity check
	 */
	if ( (lock1->lf_id != lock2->lf_id) ||
	     (lock1->lf_type != lock2->lf_type) )
		panic("lf_combine");
	if (lock1->lf_start > lock2->lf_start)
		lock1->lf_start = lock2->lf_start;
	if ((lock1->lf_end == -1) || (lock2->lf_end == -1))
		lock1->lf_end == -1;
	else if (lock1->lf_end < lock2->lf_end)
		lock1->lf_end = lock2->lf_end;
	/* Add the block lists together */
	lf_addblock(lock1, lock2->lf_block);
	free(lock2, M_LOCKF);
}

/*
E 2
 * Split a lock and a contained region into
D 2
 * three locks
E 2
I 2
 * two or three locks as necessary.
E 2
 */
I 8
void
E 8
lf_split(lock1, lock2)
	register struct lockf *lock1;
	register struct lockf *lock2;
{
	register struct lockf *splitlock;

#ifdef LOCKF_DEBUG
D 2
	if (lockf_debug & 1) {
E 2
I 2
	if (lockf_debug & 2) {
E 2
		lf_print("lf_split", lock1);
		lf_print("splitting from", lock2);
	}
#endif /* LOCKF_DEBUG */
	/*
I 2
	 * Check to see if spliting into only two pieces.
	 */
	if (lock1->lf_start == lock2->lf_start) {
		lock1->lf_start = lock2->lf_end + 1;
		lock2->lf_next = lock1;
		return;
	}
	if (lock1->lf_end == lock2->lf_end) {
		lock1->lf_end = lock2->lf_start - 1;
		lock2->lf_next = lock1->lf_next;
		lock1->lf_next = lock2;
		return;
	}
	/*
E 2
	 * Make a new lock consisting of the last part of
	 * the encompassing lock
	 */
	MALLOC(splitlock, struct lockf *, sizeof *splitlock, M_LOCKF, M_WAITOK);
	bcopy((caddr_t)lock1, (caddr_t)splitlock, sizeof *splitlock);
D 2
	splitlock->lf_end = lock2->lf_end + 1;
E 2
I 2
	splitlock->lf_start = lock2->lf_end + 1;
	splitlock->lf_block = NOLOCKF;
I 10
	splitlock->lf_spare = NOLOCKF;
E 10
E 2
	lock1->lf_end = lock2->lf_start - 1;
	/*
	 * OK, now link it in
	 */
	splitlock->lf_next = lock1->lf_next;
	lock2->lf_next = splitlock;
	lock1->lf_next = lock2;
}

/*
D 2
 * lf_remove: remove a lock (or a portion of a lock) from the lock list
 */
struct lockf *
lf_remove(lfun)
	register struct lockf *lfun;
{
	struct inode *ip = lfun->lf_inode;
	register struct lockf *lf = ip->i_lockf;
	struct lockf *blocklist = (struct lockf *)0;
	struct lockf *overlap, *prev;
	int ovcase;

	if (lf == (struct lockf *)0)
		return((struct lockf *)0);
#ifdef	LOCKF_DEBUG
	if (lockf_debug & 1)
		printf("lf_remove", lfun);
#endif	LOCKF_DEBUG
	while (ovcase = lf_findoverlap(lf, lfun, &prev, &overlap)) {
		/*
		 * Point to the next element for the loop
		 */
		lf = overlap->lf_next;
		/*
		 * Check to see if it is our lock.
		 */
		if (lfun->lf_id == overlap->lf_id) {
			/*
			 * Save the list of locks to be retried.
			 */
			if (blocklist == (struct lockf *)0)
				blocklist = overlap->lf_block;
			else
				lf_addblock(blocklist, overlap->lf_block);

			switch (ovcase) {

			case 1: /* overlap == lock */
				if (prev != (struct lockf *)0)
					prev->lf_next = overlap->lf_next;
				else
					ip->i_lockf = overlap->lf_next;
				free(overlap, M_LOCKF);
				return (blocklist);

			case 2: /* overlap contains lock: split it */
				lf_split(overlap, lfun);
				overlap->lf_next = lfun->lf_next;
				return (blocklist);

			case 3: /* lock contains overlap */
				if (prev != (struct lockf *)0)
					prev->lf_next = overlap->lf_next;
				else
					ip->i_lockf = overlap->lf_next;
				free(overlap, M_LOCKF);
				break;

			case 4: /* overlap starts before lock */
				overlap->lf_end = lfun->lf_start - 1;
				break;

			case 5: /* overlap ends after lock */
				overlap->lf_start = lfun->lf_end + 1;
				return (blocklist);
			}
		}
	}
	return (blocklist);
}

/*
E 2
 * Wakeup a blocklist
 */
I 8
void
E 8
D 2
lf_wakelock(blocklist)
	register struct lockf *blocklist;
E 2
I 2
lf_wakelock(listhead)
	struct lockf *listhead;
E 2
{
D 2
        register struct lockf *wakelock;
E 2
I 2
        register struct lockf *blocklist, *wakelock;
E 2

I 10
	if (listhead->lf_block != NOLOCKF) {
	    	if ((listhead->lf_flags & HASBLOCK) == 0)
			panic("lf_wakelock: listhead unexpected ptr");
		if (listhead->lf_block != listhead->lf_spare)
			panic("lf_wakelock: listhead corrupted ptr");
	}
E 10
D 2
        while (blocklist != (struct lockf *)0) {
E 2
I 2
	blocklist = listhead->lf_block;
D 10
	listhead->lf_block = NOLOCKF;
E 10
        while (blocklist != NOLOCKF) {
E 2
                wakelock = blocklist;
                blocklist = blocklist->lf_block;
I 10
		if (blocklist != NOLOCKF) {
			if ((wakelock->lf_flags & HASBLOCK) == 0)
				panic("lf_wakelock: unexpected ptr");
			if (wakelock->lf_block != wakelock->lf_spare)
				panic("lf_wakelock: corrupted ptr");
		}
		wakelock->lf_flags &= ~HASBLOCK;
		wakelock->lf_spare = NOLOCKF;
E 10
D 2
		wakelock->lf_block = (struct lockf *)0;
		wakelock->lf_next = (struct lockf *)0;
E 2
I 2
		wakelock->lf_block = NOLOCKF;
		wakelock->lf_next = NOLOCKF;
E 2
#ifdef LOCKF_DEBUG
D 2
		if (lockf_debug & 4)
			lf_print("ufs_wakelock: awakening", wakelock);
E 2
I 2
		if (lockf_debug & 2)
			lf_print("lf_wakelock: awakening", wakelock);
E 2
#endif /* LOCKF_DEBUG */
                wakeup((caddr_t)wakelock);
        }
I 10
	listhead->lf_flags &= ~HASBLOCK;
	listhead->lf_spare = NOLOCKF;
	listhead->lf_block = NOLOCKF;
E 10
}

#ifdef LOCKF_DEBUG
/*
 * Print out a lock.
 */
I 8
void
E 8
lf_print(tag, lock)
	char *tag;
D 2
	register lockf *lock;
E 2
I 2
	register struct lockf *lock;
E 2
{
	
D 2
	printf("%s: lock 0x%X for proc %d in ino %d on dev <%d, %d>, ",
		tag, lock, lock->lp_proc->p_pid, lock->lf_inode->i_number,
		major(lock->lf_inode->i_dev), minor(lock->lf_inode->i_dev));
	printf("type %s, start %d, end %d\n",
E 2
I 2
D 5
	printf("%s: lock 0x%X for ", tag, lock);
E 5
I 5
	printf("%s: lock 0x%lx for ", tag, lock);
E 5
	if (lock->lf_flags & F_POSIX)
		printf("proc %d", ((struct proc *)(lock->lf_id))->p_pid);
	else
		printf("id 0x%x", lock->lf_id);
	printf(" in ino %d on dev <%d, %d>, %s, start %d, end %d",
		lock->lf_inode->i_number,
		major(lock->lf_inode->i_dev),
		minor(lock->lf_inode->i_dev),
E 2
		lock->lf_type == F_RDLCK ? "shared" :
		lock->lf_type == F_WRLCK ? "exclusive" :
D 2
		"unknown", start, end);
E 2
I 2
		lock->lf_type == F_UNLCK ? "unlock" :
		"unknown", lock->lf_start, lock->lf_end);
	if (lock->lf_block)
		printf(" block 0x%x\n", lock->lf_block);
	else
		printf("\n");
}

I 8
void
E 8
lf_printlist(tag, lock)
	char *tag;
	struct lockf *lock;
{
	register struct lockf *lf;

	printf("%s: Lock list for ino %d on dev <%d, %d>:\n",
		tag, lock->lf_inode->i_number,
		major(lock->lf_inode->i_dev),
		minor(lock->lf_inode->i_dev));
	for (lf = lock->lf_inode->i_lockf; lf; lf = lf->lf_next) {
D 5
		printf("\tlock 0x%X for ", lf);
E 5
I 5
		printf("\tlock 0x%lx for ", lf);
E 5
		if (lf->lf_flags & F_POSIX)
			printf("proc %d", ((struct proc *)(lf->lf_id))->p_pid);
		else
			printf("id 0x%x", lf->lf_id);
		printf(", %s, start %d, end %d",
			lf->lf_type == F_RDLCK ? "shared" :
			lf->lf_type == F_WRLCK ? "exclusive" :
			lf->lf_type == F_UNLCK ? "unlock" :
			"unknown", lf->lf_start, lf->lf_end);
		if (lf->lf_block)
			printf(" block 0x%x\n", lf->lf_block);
		else
			printf("\n");
	}
E 2
}
#endif /* LOCKF_DEBUG */
E 1
