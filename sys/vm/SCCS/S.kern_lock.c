h00218
s 00009/00009/00499
d D 8.2 95/01/09 17:50:28 cgd 9 8
c KNF, and 64-bit safety.
e
s 00002/00002/00506
d D 8.1 93/06/11 16:36:56 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00504
d D 7.7 93/05/24 23:40:41 torek 7 6
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00001/00001/00507
d D 7.6 92/10/11 13:04:01 bostic 6 5
c make kernel includes standard
e
s 00004/00003/00504
d D 7.5 92/05/04 17:25:42 bostic 5 4
c new include format
e
s 00027/00004/00480
d D 7.4 91/04/21 18:36:03 mckusick 4 3
c update to new CMU copyright and distribution terms
e
s 00001/00002/00483
d D 7.3 91/04/20 15:00:44 karels 3 2
c rm user.h, fix vm header; move from kern directory
e
s 00002/00002/00483
d D 7.2 91/03/17 15:41:22 karels 2 1
c more-or-less working with new proc & user structs
e
s 00485/00000/00000
d D 7.1 90/12/05 17:46:38 mckusick 1 0
c adopted from MACH 2.5 kern/kern_lock.c
e
u
U
t
T
I 1
/* 
D 4
 * Copyright (c) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 * Copyright (c) 1987 Carnegie-Mellon University
E 4
D 8
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University.
 *
D 4
 * The CMU software License Agreement specifies the terms and conditions
 * for use and redistribution.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
I 4
 *
 *
 * Copyright (c) 1987, 1990 Carnegie-Mellon University.
 * All rights reserved.
 *
 * Authors: Avadis Tevanian, Jr., Michael Wayne Young
 * 
 * Permission to use, copy, modify and distribute this software and
 * its documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" 
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND 
 * FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
E 4
 */

/*
 *	Locking primitives implementation
 */

D 5
#include "param.h"
D 2
#include "../vm/vm_param.h"
E 2
I 2
D 3
#include "vm/vm_param.h"
E 3
I 3
#include "vm_param.h"
E 3
E 2
#include "lock.h"
E 5
I 5
#include <sys/param.h>
#include <sys/systm.h>

#include <vm/vm.h>
E 5

/* XXX */
D 3
#include "user.h"
E 3
D 6
#include "proc.h"
E 6
I 6
#include <sys/proc.h>
E 6
D 9
typedef	int *thread_t;
E 9
I 9
typedef	void *thread_t;
E 9
D 2
#define	current_thread()	((thread_t)&u.u_procp->p_thread)
E 2
I 2
#define	current_thread()	((thread_t)&curproc->p_thread)
E 2
/* XXX */

#if	NCPUS > 1

/*
 *	Module:		lock
 *	Function:
 *		Provide reader/writer sychronization.
 *	Implementation:
 *		Simple interlock on a bit.  Readers first interlock
 *		increment the reader count, then let go.  Writers hold
 *		the interlock (thus preventing further readers), and
 *		wait for already-accepted readers to go away.
 */

/*
 *	The simple-lock routines are the primitives out of which
 *	the lock package is built.  The implementation is left
 *	to the machine-dependent code.
 */

#ifdef	notdef
/*
 *	A sample implementation of simple locks.
 *	assumes:
 *		boolean_t test_and_set(boolean_t *)
 *			indivisibly sets the boolean to TRUE
 *			and returns its old value
 *		and that setting a boolean to FALSE is indivisible.
 */
/*
 *	simple_lock_init initializes a simple lock.  A simple lock
 *	may only be used for exclusive locks.
 */

void simple_lock_init(l)
	simple_lock_t	l;
{
	*(boolean_t *)l = FALSE;
}

void simple_lock(l)
	simple_lock_t	l;
{
	while (test_and_set((boolean_t *)l))
		continue;
}

void simple_unlock(l)
	simple_lock_t	l;
{
	*(boolean_t *)l = FALSE;
}

boolean_t simple_lock_try(l)
	simple_lock_t	l;
{
    	return (!test_and_set((boolean_t *)l));
}
D 7
#endif	notdef
#endif	NCPUS > 1
E 7
I 7
#endif /* notdef */
#endif /* NCPUS > 1 */
E 7

#if	NCPUS > 1
int lock_wait_time = 100;
D 7
#else	NCPUS > 1
E 7
I 7
#else /* NCPUS > 1 */
E 7

	/*
	 * 	It is silly to spin on a uni-processor as if we
	 *	thought something magical would happen to the
	 *	want_write bit while we are executing.
	 */
int lock_wait_time = 0;
D 7
#endif	NCPUS > 1
E 7
I 7
#endif /* NCPUS > 1 */
E 7


/*
 *	Routine:	lock_init
 *	Function:
 *		Initialize a lock; required before use.
 *		Note that clients declare the "struct lock"
 *		variables and then initialize them, rather
 *		than getting a new one from this module.
 */
void lock_init(l, can_sleep)
	lock_t		l;
	boolean_t	can_sleep;
{
	bzero(l, sizeof(lock_data_t));
	simple_lock_init(&l->interlock);
	l->want_write = FALSE;
	l->want_upgrade = FALSE;
	l->read_count = 0;
	l->can_sleep = can_sleep;
	l->thread = (char *)-1;		/* XXX */
	l->recursion_depth = 0;
}

void lock_sleepable(l, can_sleep)
	lock_t		l;
	boolean_t	can_sleep;
{
	simple_lock(&l->interlock);
	l->can_sleep = can_sleep;
	simple_unlock(&l->interlock);
}


/*
 *	Sleep locks.  These use the same data structure and algorithm
 *	as the spin locks, but the process sleeps while it is waiting
 *	for the lock.  These work on uniprocessor systems.
 */

void lock_write(l)
	register lock_t	l;
{
	register int	i;

	simple_lock(&l->interlock);

	if (((thread_t)l->thread) == current_thread()) {
		/*
		 *	Recursive lock.
		 */
		l->recursion_depth++;
		simple_unlock(&l->interlock);
		return;
	}

	/*
	 *	Try to acquire the want_write bit.
	 */
	while (l->want_write) {
		if ((i = lock_wait_time) > 0) {
			simple_unlock(&l->interlock);
			while (--i > 0 && l->want_write)
				continue;
			simple_lock(&l->interlock);
		}

		if (l->can_sleep && l->want_write) {
			l->waiting = TRUE;
D 9
			thread_sleep((int) l, &l->interlock, FALSE);
E 9
I 9
			thread_sleep(l, &l->interlock, FALSE);
E 9
			simple_lock(&l->interlock);
		}
	}
	l->want_write = TRUE;

	/* Wait for readers (and upgrades) to finish */

	while ((l->read_count != 0) || l->want_upgrade) {
		if ((i = lock_wait_time) > 0) {
			simple_unlock(&l->interlock);
			while (--i > 0 && (l->read_count != 0 ||
					l->want_upgrade))
				continue;
			simple_lock(&l->interlock);
		}

		if (l->can_sleep && (l->read_count != 0 || l->want_upgrade)) {
			l->waiting = TRUE;
D 9
			thread_sleep((int) l, &l->interlock, FALSE);
E 9
I 9
			thread_sleep(l, &l->interlock, FALSE);
E 9
			simple_lock(&l->interlock);
		}
	}
	simple_unlock(&l->interlock);
}

void lock_done(l)
	register lock_t	l;
{
	simple_lock(&l->interlock);

	if (l->read_count != 0)
		l->read_count--;
	else
	if (l->recursion_depth != 0)
		l->recursion_depth--;
	else
	if (l->want_upgrade)
	 	l->want_upgrade = FALSE;
	else
	 	l->want_write = FALSE;

	if (l->waiting) {
		l->waiting = FALSE;
D 9
		thread_wakeup((int) l);
E 9
I 9
		thread_wakeup(l);
E 9
	}
	simple_unlock(&l->interlock);
}

void lock_read(l)
	register lock_t	l;
{
	register int	i;

	simple_lock(&l->interlock);

	if (((thread_t)l->thread) == current_thread()) {
		/*
		 *	Recursive lock.
		 */
		l->read_count++;
		simple_unlock(&l->interlock);
		return;
	}

	while (l->want_write || l->want_upgrade) {
		if ((i = lock_wait_time) > 0) {
			simple_unlock(&l->interlock);
			while (--i > 0 && (l->want_write || l->want_upgrade))
				continue;
			simple_lock(&l->interlock);
		}

		if (l->can_sleep && (l->want_write || l->want_upgrade)) {
			l->waiting = TRUE;
D 9
			thread_sleep((int) l, &l->interlock, FALSE);
E 9
I 9
			thread_sleep(l, &l->interlock, FALSE);
E 9
			simple_lock(&l->interlock);
		}
	}

	l->read_count++;
	simple_unlock(&l->interlock);
}

/*
 *	Routine:	lock_read_to_write
 *	Function:
 *		Improves a read-only lock to one with
 *		write permission.  If another reader has
 *		already requested an upgrade to a write lock,
 *		no lock is held upon return.
 *
 *		Returns TRUE if the upgrade *failed*.
 */
boolean_t lock_read_to_write(l)
	register lock_t	l;
{
	register int	i;

	simple_lock(&l->interlock);

	l->read_count--;

	if (((thread_t)l->thread) == current_thread()) {
		/*
		 *	Recursive lock.
		 */
		l->recursion_depth++;
		simple_unlock(&l->interlock);
		return(FALSE);
	}

	if (l->want_upgrade) {
		/*
		 *	Someone else has requested upgrade.
		 *	Since we've released a read lock, wake
		 *	him up.
		 */
		if (l->waiting) {
			l->waiting = FALSE;
D 9
			thread_wakeup((int) l);
E 9
I 9
			thread_wakeup(l);
E 9
		}

		simple_unlock(&l->interlock);
		return (TRUE);
	}

	l->want_upgrade = TRUE;

	while (l->read_count != 0) {
		if ((i = lock_wait_time) > 0) {
			simple_unlock(&l->interlock);
			while (--i > 0 && l->read_count != 0)
				continue;
			simple_lock(&l->interlock);
		}

		if (l->can_sleep && l->read_count != 0) {
			l->waiting = TRUE;
D 9
			thread_sleep((int) l, &l->interlock, FALSE);
E 9
I 9
			thread_sleep(l, &l->interlock, FALSE);
E 9
			simple_lock(&l->interlock);
		}
	}

	simple_unlock(&l->interlock);
	return (FALSE);
}

void lock_write_to_read(l)
	register lock_t	l;
{
	simple_lock(&l->interlock);

	l->read_count++;
	if (l->recursion_depth != 0)
		l->recursion_depth--;
	else
	if (l->want_upgrade)
		l->want_upgrade = FALSE;
	else
	 	l->want_write = FALSE;

	if (l->waiting) {
		l->waiting = FALSE;
D 9
		thread_wakeup((int) l);
E 9
I 9
		thread_wakeup(l);
E 9
	}

	simple_unlock(&l->interlock);
}


/*
 *	Routine:	lock_try_write
 *	Function:
 *		Tries to get a write lock.
 *
 *		Returns FALSE if the lock is not held on return.
 */

boolean_t lock_try_write(l)
	register lock_t	l;
{

	simple_lock(&l->interlock);

	if (((thread_t)l->thread) == current_thread()) {
		/*
		 *	Recursive lock
		 */
		l->recursion_depth++;
		simple_unlock(&l->interlock);
		return(TRUE);
	}

	if (l->want_write || l->want_upgrade || l->read_count) {
		/*
		 *	Can't get lock.
		 */
		simple_unlock(&l->interlock);
		return(FALSE);
	}

	/*
	 *	Have lock.
	 */

	l->want_write = TRUE;
	simple_unlock(&l->interlock);
	return(TRUE);
}

/*
 *	Routine:	lock_try_read
 *	Function:
 *		Tries to get a read lock.
 *
 *		Returns FALSE if the lock is not held on return.
 */

boolean_t lock_try_read(l)
	register lock_t	l;
{
	simple_lock(&l->interlock);

	if (((thread_t)l->thread) == current_thread()) {
		/*
		 *	Recursive lock
		 */
		l->read_count++;
		simple_unlock(&l->interlock);
		return(TRUE);
	}

	if (l->want_write || l->want_upgrade) {
		simple_unlock(&l->interlock);
		return(FALSE);
	}

	l->read_count++;
	simple_unlock(&l->interlock);
	return(TRUE);
}

/*
 *	Routine:	lock_try_read_to_write
 *	Function:
 *		Improves a read-only lock to one with
 *		write permission.  If another reader has
 *		already requested an upgrade to a write lock,
 *		the read lock is still held upon return.
 *
 *		Returns FALSE if the upgrade *failed*.
 */
boolean_t lock_try_read_to_write(l)
	register lock_t	l;
{

	simple_lock(&l->interlock);

	if (((thread_t)l->thread) == current_thread()) {
		/*
		 *	Recursive lock
		 */
		l->read_count--;
		l->recursion_depth++;
		simple_unlock(&l->interlock);
		return(TRUE);
	}

	if (l->want_upgrade) {
		simple_unlock(&l->interlock);
		return(FALSE);
	}
	l->want_upgrade = TRUE;
	l->read_count--;

	while (l->read_count != 0) {
		l->waiting = TRUE;
D 9
		thread_sleep((int) l, &l->interlock, FALSE);
E 9
I 9
		thread_sleep(l, &l->interlock, FALSE);
E 9
		simple_lock(&l->interlock);
	}

	simple_unlock(&l->interlock);
	return(TRUE);
}

/*
 *	Allow a process that has a lock for write to acquire it
 *	recursively (for read, write, or update).
 */
void lock_set_recursive(l)
	lock_t		l;
{
	simple_lock(&l->interlock);
	if (!l->want_write) {
		panic("lock_set_recursive: don't have write lock");
	}
	l->thread = (char *) current_thread();
	simple_unlock(&l->interlock);
}

/*
 *	Prevent a lock from being re-acquired.
 */
void lock_clear_recursive(l)
	lock_t		l;
{
	simple_lock(&l->interlock);
	if (((thread_t) l->thread) != current_thread()) {
		panic("lock_clear_recursive: wrong thread");
	}
	if (l->recursion_depth == 0)
		l->thread = (char *)-1;		/* XXX */
	simple_unlock(&l->interlock);
}
E 1
