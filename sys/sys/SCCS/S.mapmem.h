h32896
s 00002/00002/00084
d R 8.1 93/06/02 19:54:08 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00085
d D 7.2 90/06/06 14:51:17 mckusick 2 1
c update new calling convention for mmalloc
e
s 00087/00000/00000
d D 7.1 90/05/08 22:59:06 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: mmap.h 1.4 89/08/14$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Mapped memory descriptors.
 *
 * A process has one of these for every "mapped" memory region.
 * Mapped memory is characterized by:
 *	- Corresponding physical memory is neither paged nor swapped.
 *	- User PTEs have both pg_v and pg_fod set.
 *	- Has no backing swap space unless mapped over existing data.
 *	- If mapped over existing data, original data is lost when
 *	  segment is unmapped. (i.e. pages are reinitialized to ZFOD)
 * Operations:
 *	(*mm_fork)(mp, ischild) struct mapmem *mp; int ischild;
 *		Called during fork in both parent and child.  Parent
 *		call can be used for maintaining reference counts and
 *		should NEVER destroy the region.  Child call should be
 *		used for unmapping regions not inherited across forks.
 *	(*mm_vfork)(mp, fup, tup) struct mapmem *mp; struct user *fup, *tup;
 *		Called twice during vfork (always in parent context)
 *		after exchanging resources (including u_mmap chains).
 *		`fup' is the donor and `tup' the recipient of the
 *		"parent" (full) context.  Needed for maintaining
 *		reference counts or if the underlying object contains
 *		references to owning process.  Routine should NEVER
 *		destroy the region.
 *	(*mm_exec)(mp) struct mapmem *mp;
 *		Called during exec before releasing old address space.
 *		Used for graceful cleanup of underlying object.  Resources
 *		will be freed regardless of what this routine does.
 *		Need to add a post-exec call to re-establish mappings
 *		in the new address space for regions inherited across execs.
 *	(*mm_exit)(mp) struct mapmem *mp;
 *		Called during exit just before releasing address space.
 *		Used for graceful cleanup of underlying object.  Resources
 *		will be freed regardless of what this routine does.
 * The default semantics for a region with routine addresses of zero are
 * that it is inherited across forks, stays with the "active" process during
 * vforks, and is destroyed by execs and exit.
 */

struct mapmem {
	struct	mapmem *mm_next;	/* next descriptor */
	int	mm_id;			/* identifier (e.g. fd, shmid) */
	caddr_t	mm_uva;			/* user VA at which region is mapped */
	int	mm_size;		/* size of mapped region */
	int	mm_prot;		/* attributes of region */
	struct mapmemops {		/* operations */
		int	(*mm_fork)();
		int	(*mm_vfork)();
		int	(*mm_exec)();
		int	(*mm_exit)();
	} *mm_ops;
};

#define MMNIL	((struct mapmem *)0)

/* attributes */
#define MM_RW		0x00	/* region is read-write */
#define	MM_RO		0x01	/* region is read-only */
#define MM_CI		0x02	/* caching is inhibited on region */
#define MM_NOCORE	0x04	/* cannot write region to core file;
				   e.g. mapped framebuffer hardware */

#ifdef KERNEL
D 2
extern struct mapmem *mmalloc();

E 2
#define MMALLOC(mp) \
	(mp) = (struct mapmem *)malloc((u_long)sizeof(struct mapmem), \
	    M_MAPMEM, M_WAITOK)

#define MMFREE(mp) \
	free((caddr_t)(mp), M_MAPMEM)
#endif
E 1
