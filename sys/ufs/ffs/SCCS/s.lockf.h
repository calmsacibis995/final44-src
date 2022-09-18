h31210
s 00002/00002/00051
d D 8.1 93/06/11 16:28:35 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00016/00029
d D 7.2 91/11/01 17:56:26 bostic 2 1
c clean up prototypes
e
s 00045/00000/00000
d D 7.1 91/02/01 16:28:24 mckusick 1 0
c date and time created 91/02/01 16:28:24 by mckusick
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Scooter Morris at Genentech Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
D 2
 * The lockf structure is a kernel structure which contains all the
 * information associated with a byte range lock. The lockf structures
 * are linked into the inode structure. Locks are sorted by the starting
 * byte of the lock for efficiency.
E 2
I 2
 * The lockf structure is a kernel structure which contains the information
 * associated with a byte range lock.  The lockf structures are linked into
 * the inode structure. Locks are sorted by the starting byte of the lock for
 * efficiency.
E 2
 */
struct lockf {
	short	lf_flags;	 /* Lock semantics: F_POSIX, F_FLOCK, F_WAIT */
	short	lf_type;	 /* Lock type: F_RDLCK, F_WRLCK */
	off_t	lf_start;	 /* The byte # of the start of the lock */
	off_t	lf_end;		 /* The byte # of the end of the lock (-1=EOF)*/
	caddr_t	lf_id;		 /* The id of the resource holding the lock */
	struct	inode *lf_inode; /* Back pointer to the inode */
	struct	lockf *lf_next;	 /* A pointer to the next lock on this inode */
	struct	lockf *lf_block; /* The list of blocked locks */
};

D 2
/*
 * Maximum length of sleep chains to traverse to try and detect deadlock.
 */
E 2
I 2
/* Maximum length of sleep chains to traverse to try and detect deadlock. */
E 2
#define MAXDEPTH 50

D 2
#ifdef	KERNEL
/*
 * Public lock manipulation routines
 */
extern struct lockf *lf_remove();	/* Remove a lock */
extern struct lockf *lf_getblock();	/* Return the first blocking lock */
E 2
I 2
__BEGIN_DECLS
void	 lf_addblock __P((struct lockf *, struct lockf *));
int	 lf_clearlock __P((struct lockf *));
int	 lf_findoverlap __P((struct lockf *,
	    struct lockf *, int, struct lockf ***, struct lockf **));
struct lockf *
	 lf_getblock __P((struct lockf *));
int	 lf_getlock __P((struct lockf *, struct flock *));
int	 lf_setlock __P((struct lockf *));
void	 lf_split __P((struct lockf *, struct lockf *));
void	 lf_wakelock __P((struct lockf *));
__END_DECLS
E 2

D 2
#ifdef	LOCKF_DEBUG
E 2
I 2
#ifdef LOCKF_DEBUG
E 2
extern int lockf_debug;
D 2
#endif	LOCKF_DEBUG
#endif	KERNEL
E 2
I 2

__BEGIN_DECLS
void	lf_print __P((char *, struct lockf *));
void	lf_printlist __P((char *, struct lockf *));
__END_DECLS
#endif
E 2
E 1
