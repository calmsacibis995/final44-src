/* 
 * Copyright (c) 1995
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
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
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <vm/vm.h>

/*
 *	MACH VM locking to kernel locking conversion.
 */
#define	lock_read_done(l)	lock_done(l)
#define	lock_write_done(l)	lock_done(l)
void		lock_clear_recursive __P((lock_t));
void		lock_done __P((lock_t));
void		lock_init __P((lock_t, boolean_t));
void		lock_read __P((lock_t));
boolean_t	lock_read_to_write __P((lock_t));
void		lock_set_recursive __P((lock_t));
void		lock_sleepable __P((lock_t, boolean_t));
boolean_t	lock_try_read __P((lock_t));
boolean_t	lock_try_read_to_write __P((lock_t));
boolean_t	lock_try_write __P((lock_t));
void		lock_write __P((lock_t));
void		lock_write_to_read __P((lock_t));

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
	lockinit(l, PVM, "thrd_sleep", 0, can_sleep ? 0 : LK_NOWAIT);
}

void lock_sleepable(l, can_sleep)
	lock_t		l;
	boolean_t	can_sleep;
{
	simple_lock(&l->lk_interlock);
	if (can_sleep)
		l->lk_flags &= ~LK_NOWAIT;
	else
		l->lk_flags |= LK_NOWAIT;
	simple_unlock(&l->lk_interlock);
}


/*
 *	Sleep locks.  These use the same data structure and algorithm
 *	as the spin locks, but the process sleeps while it is waiting
 *	for the lock.  These work on uniprocessor systems.
 */
#define CURPID	(curproc == 0 ? LK_KERNPROC : curproc->p_pid)

void lock_write(l)
	register lock_t	l;
{
	register int	i;

	lockmgr(l, LK_EXCLUSIVE, 0, CURPID);
}

void lock_done(l)
	register lock_t	l;
{
	lockmgr(l, LK_RELEASE, 0, CURPID);
}

void lock_read(l)
	register lock_t	l;
{
	lockmgr(l, LK_SHARED, 0, CURPID);
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

	if (lockmgr(l, LK_EXCLUPGRADE, 0, CURPID))
		return (TRUE);
	return (FALSE);
}

void lock_write_to_read(l)
	register lock_t	l;
{
	lockmgr(l, LK_DOWNGRADE, 0, CURPID);
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
	if (lockmgr(l, LK_EXCLUSIVE|LK_NOWAIT, 0, CURPID))
		return (FALSE);
	return (TRUE);
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
	if (lockmgr(l, LK_SHARED|LK_NOWAIT, 0, CURPID))
		return (FALSE);
	return (TRUE);
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
	if (lockmgr(l, LK_EXCLUPGRADE|LK_NOWAIT, 0, CURPID))
		return (FALSE);
	return (TRUE);
}

/*
 *	Allow a process that has a lock for write to acquire it
 *	recursively (for read, write, or update).
 */
void lock_set_recursive(l)
	lock_t		l;
{
	simple_lock(&l->lk_interlock);
	l->lk_flags |= LK_CANRECURSE;
	simple_unlock(&l->lk_interlock);
}

/*
 *	Prevent a lock from being re-acquired.
 */
void lock_clear_recursive(l)
	lock_t		l;
{
	simple_lock(&l->lk_interlock);
	l->lk_flags &= ~LK_CANRECURSE;
	simple_unlock(&l->lk_interlock);
}
