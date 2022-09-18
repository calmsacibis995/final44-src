h62949
s 00001/00001/00145
d D 8.2 95/01/09 17:50:20 cgd 8 7
c KNF, and 64-bit safety.
e
s 00002/00002/00144
d D 8.1 93/06/11 16:37:01 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00144
d D 7.6 93/05/24 23:15:22 torek 6 5
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00026/00029/00120
d D 7.5 92/05/04 17:06:39 bostic 5 4
c add function prototypes
e
s 00001/00001/00148
d D 7.4 91/09/06 19:06:05 ralph 4 3
c fix #else for ANSI C.
e
s 00027/00004/00122
d D 7.3 91/04/21 18:36:04 mckusick 3 2
c update to new CMU copyright and distribution terms
e
s 00006/00006/00120
d D 7.2 91/02/05 17:04:19 bostic 2 1
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00126/00000/00000
d D 7.1 90/12/05 17:51:19 mckusick 1 0
c adopted from MACH 2.5 h/lock.h
e
u
U
t
T
I 1
/* 
D 3
 * Copyright (c) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 * Copyright (c) 1987 Carnegie-Mellon University
E 3
D 7
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University.
 *
D 3
 * The CMU software License Agreement specifies the terms and conditions
 * for use and redistribution.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
I 3
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
E 3
 */

/*
 *	Locking primitives definitions
 */

D 2
#ifndef	_LOCK_
#define	_LOCK_
E 2
I 2
#ifndef	_LOCK_H_
#define	_LOCK_H_
E 2

#define	NCPUS	1		/* XXX */

/*
 *	A simple spin lock.
 */

struct slock {
	int		lock_data;	/* in general 1 bit is sufficient */
};

typedef struct slock	simple_lock_data_t;
typedef struct slock	*simple_lock_t;

/*
 *	The general lock structure.  Provides for multiple readers,
 *	upgrading from read to write, and sleeping until the lock
 *	can be gained.
 */

struct lock {
#ifdef	vax
	/*
	 *	Efficient VAX implementation -- see field description below.
	 */
	unsigned int	read_count:16,
			want_upgrade:1,
			want_write:1,
			waiting:1,
			can_sleep:1,
			:0;

	simple_lock_data_t	interlock;
D 6
#else	vax
E 6
I 6
#else /* vax */
E 6
#ifdef	ns32000
	/*
	 *	Efficient ns32000 implementation --
	 *	see field description below.
	 */
	simple_lock_data_t	interlock;
	unsigned int	read_count:16,
			want_upgrade:1,
			want_write:1,
			waiting:1,
			can_sleep:1,
			:0;

D 6
#else	ns32000
E 6
I 6
#else /* ns32000 */
E 6
	/*	Only the "interlock" field is used for hardware exclusion;
	 *	other fields are modified with normal instructions after
	 *	acquiring the interlock bit.
	 */
	simple_lock_data_t
			interlock;	/* Interlock for remaining fields */
	boolean_t	want_write;	/* Writer is waiting, or locked for write */
	boolean_t	want_upgrade;	/* Read-to-write upgrade waiting */
	boolean_t	waiting;	/* Someone is sleeping on lock */
	boolean_t	can_sleep;	/* Can attempts to lock go to sleep */
	int		read_count;	/* Number of accepted readers */
D 2
#endif	ns32000
#endif	vax
E 2
I 2
#endif	/* ns32000 */
#endif	/* vax */
E 2
D 8
	char		*thread;	/* Thread that has lock, if recursive locking allowed */
E 8
I 8
	void		*thread;	/* Thread that has lock, if recursive locking allowed */
E 8
					/* (should be thread_t, but but we then have mutually
					   recursive definitions) */
	int		recursion_depth;/* Depth of recursion */
};

typedef struct lock	lock_data_t;
typedef struct lock	*lock_t;

D 5
#if	NCPUS > 1
void		simple_lock_init();
void		simple_lock();
void		simple_unlock();
boolean_t	simple_lock_try();
D 4
#else	NCPUS > 1
E 4
I 4
#else	/* NCPUS > 1 */
E 4
/*
 *	No multiprocessor locking is necessary.
 */
#define simple_lock_init(l)
#define simple_lock(l)
#define simple_unlock(l)
#define simple_lock_try(l)	(1)	/* always succeeds */
D 2
#endif	NCPUS > 1
E 2
I 2
#endif	/* NCPUS > 1 */
E 5
I 5
#if NCPUS > 1
__BEGIN_DECLS
void		simple_lock __P((simple_lock_t));
void		simple_lock_init __P((simple_lock_t));
boolean_t	simple_lock_try __P((simple_lock_t));
void		simple_unlock __P((simple_lock_t));
__END_DECLS
#else		/* No multiprocessor locking is necessary. */
#define	simple_lock(l)
#define	simple_lock_init(l)
#define	simple_lock_try(l)	(1)	/* Always succeeds. */
#define	simple_unlock(l)
#endif
E 5
E 2

D 5
/* Sleep locks must work even if no multiprocessing */
E 5
I 5
/* Sleep locks must work even if no multiprocessing. */
E 5

D 5
void		lock_init();
void		lock_sleepable();
void		lock_write();
void		lock_read();
void		lock_done();
boolean_t	lock_read_to_write();
void		lock_write_to_read();
boolean_t	lock_try_write();
boolean_t	lock_try_read();
boolean_t	lock_try_read_to_write();

E 5
#define	lock_read_done(l)	lock_done(l)
#define	lock_write_done(l)	lock_done(l)

D 5
void		lock_set_recursive();
void		lock_clear_recursive();

E 5
I 5
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
E 5
D 2
#endif	_LOCK_
E 2
I 2
#endif /* !_LOCK_H_ */
E 2
E 1
