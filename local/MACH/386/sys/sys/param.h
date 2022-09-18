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
 * $Log:	param.h,v $
 * Revision 2.11  89/04/22  15:32:15  gm0w
 * 	Removed MACH_VFS changes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.10  89/03/09  22:06:20  rpd
 * 	More cleanup.
 * 
 * Revision 2.9  89/02/25  17:55:14  gm0w
 * 	Made CMUCS and MACH conditionals always true and got
 * 	rid of the non-CMUCS and non-MACH code. Changed
 * 	romp to ibmrt and EXL to exl.
 * 	[89/02/13            mrt]
 * 
 * Revision 2.8  89/01/23  22:27:51  af
 * 	Added definition of domainname string length, reduced some
 * 	extra #include statements.
 * 	[89/01/09            af]
 * 	
 * 	Changes for I386 -- define _bit_<foo> like for a vax??
 * 		I guess we just don't use them anymore.
 * 	[89/01/09            rvb]
 * 
 * Revision 2.7  89/01/21  13:33:29  jsb
 * 	Bump MAXSYMLINKS up from 8 to 32.
 * 
 * Revision 2.6  89/01/18  01:18:11  jsb
 * 	Vnode support: define MAXLINK, PMASK and PCATCH.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.5  88/12/21  14:19:01  mja
 * 	Allow the file to be included recursively.
 * 
 * Revision 2.4  88/08/24  02:38:21  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:19:37  mwyoung]
 *
 * 23-May-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Bump maximum user process count to 64 (it is patched
 *	down to the standard 40 on time-sharing systems).
 *	[ V5.1(XF26) ]
 *
 * 20-Apr-88  David Black (dlb) at Carnegie-Mellon University
 *	Change to signal macros to allow use of exception signals as
 *	back door ipc.  [XXX]
 *
 * 21-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: ISSIG() must check for per-thread exit conditions.
 *
 * 17-Sep-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Split up ISSIG() so I can tell if issig() would be called.  This
 *	is neccessary for astcheck which is running at interrupt level,
 *	and for trap() that does now want to acquire/release the
 *	unix_lock twice.
 *
 * 17-Mar-87  David L. Black (dlb) at Carnegie-Mellon :University
 *	MULTIMAX & BALANCE: MAXUPRC -> 100
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	machparam.h was a 4.3 *feature*, so I have changed the include
 *	of machine/param.h back to machine/machparam.h.
 *
 * 29-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Make tsleep stuff conditional on CMUCS instead of CS_COMPAT.
 *
 * 29-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Moved INCLUDE_VERSION to h/version.h
 *
 *  1-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	INCLUDE_VERSION changed to -5 to account for different proc
 *	structure and elimination of task and thread tables.
 *
 * 29-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Conditionalized which version of <machine/param.h> to get on
 *	CMUCS.  Added separate INCLUDE_VERSION for MACH case.
 *	Rearranged PSEM and PIPC under appropriate conditionals.
 *
 * 18-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Bumped include version to -4, to account for different
 *	TBL_* constants after merge with Facilities system.
 *	Shouldn't the INCLUDE_VERSION really be in another file?
 *
 *  2-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Bumped INCLUDE_VERSION to -3, to reflect changes in
 *	"vm/vm_map.h".
 *
 * 23-Aug-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Changed "machparam.h" reference to "machine/param.h".
 *
 * 27-Jul-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Changed ROMP to romp.
 *
 * 10-Jun-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Added INCLUDE_VERSION definition.
 *
 * 22-Mar-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merged VM and Romp versions.
 *
 * 19-Mar-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Fixed definitions of the bit manipulation macros (setbit, etc.)
 *	so that their arguments may be of any type (as opposed to having
 *	to be of a single byte length type).
 *
 * 28-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Added defintions of _bit_{set,clear,tst} for romp.
 *
 * 20-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Spiffed up and included IBM code for Sailboat which handles the
 *	inclusion of signal.h when we are running on the romp
 *	(specifically, not to include it when building locore, or all
 *	hell will break loose).
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3 and increased MAXHOSTNAMELEN to 256 [CMUCS].
 *	Also removed CS_NOFILE.
 *
 * 23-May-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	CS_COMPAT:  Added tsleep() return values from 4.1BSD [V1(1)].
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)param.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_PARAM_H_
#define _SYS_PARAM_H_

#define BSD	43		/* 4.3 * 10, as cpp doesn't do floats */
#define BSD4_3	1

#include <sys/types.h>
#include <machine/machparam.h>

#define NPTEPG		(NBPG/(sizeof (struct pte)))

/*
 * Machine-independent constants
 */
#define NMOUNT	20		/* number of mountable file systems */
/* NMOUNT must be <= 255 unless c_mdev (cmap.h) is expanded */
#define MSWAPX	NMOUNT		/* pseudo mount table index for swapdev */
#if	defined(multimax) || defined(balance)
#define MAXUPRC 100		/* max processes per user */
#else	defined(multimax) || defined(balance)
#define MAXUPRC 64		/* max processes per user */
#endif	defined(multimax) || defined(balance)
#define NOFILE	64		/* max open files per process */
#define MAXLINK 32767		/* ??? */
#define CANBSIZ	256		/* max size of typewriter line */
#define NCARGS	20480		/* # characters in exec arglist */
#define NGROUPS	16		/* max number groups */

#define NOGROUP	65535		/* marker for empty group set member */

/*
 * Priorities
 */
#define PSWP	0
#define PINOD	10
#define PRIBIO	20
#define PRIUBA	24
#define PZERO	25
#define PPIPE	26
#define PWAIT	30
#define PLOCK	35
#define PSLEP	40
#define PUSER	50
#define PMASK	0177
#define PCATCH	0400	/* return if sleep interrupted, don't longjmp */

#define NZERO	0

/*
 * Signals
 */
#if	!(defined(LOCORE) && defined(ibmrt))
#include <sys/signal.h> 
#endif	!(defined(LOCORE) && defined(ibmrt))


/*
 * Return values from tsleep().
 */
#define TS_OK	0	/* normal wakeup */
#define TS_TIME	1	/* timed-out wakeup */
#define TS_SIG	2	/* asynchronous signal wakeup */

/*
 *	Check for per-process and per thread signals.
 */
#define SHOULDissig(p,uthreadp) \
	(((p)->p_sig | (uthreadp)->uu_sig) && ((p)->p_flag&STRC || \
	 (((p)->p_sig | (uthreadp)->uu_sig) &~ \
	   ((p)->p_sigignore | (p)->p_sigmask))))

/*
 *	Check for signals, handling possible stop signals.
 *	Ignores signals already 'taken' and per-thread signals.
 *	Use before and after thread_block() in sleep().
 *	(p) is always current process.
 */
#define ISSIG(p) (thread_should_halt() || \
	 (SHOULDissig(p,current_thread()->u_address.uthread) && issig()))

/*
 *	Check for signals, including signals already taken and
 *	per-thread signals.  Use in trap() and syscall() before
 *	exiting kernel.
 */
#define CHECK_SIGNALS(p, uthreadp)	\
	(!thread_should_halt()		\
	 && ((p)->p_cursig		\
	     || SHOULDissig(p,uthreadp)))

#define NBPW	sizeof(int)	/* number of bytes in an integer */

#define NULL	0
#define CMASK	022		/* default mask for file creation */
#define NODEV	(dev_t)(-1)

/*
 * Clustering of hardware pages on machines with ridiculously small
 * page sizes is done here.  The paging subsystem deals with units of
 * CLSIZE pte's describing NBPG (from vm.h) pages each.
 *
 * NOTE: SSIZE, SINCR and UPAGES must be multiples of CLSIZE
 */
#define CLBYTES		(CLSIZE*NBPG)
#define CLOFSET		(CLSIZE*NBPG-1)	/* for clusters, like PGOFSET */
#define claligned(x)	((((int)(x))&CLOFSET)==0)
#define CLOFF		CLOFSET
#define CLSHIFT		(PGSHIFT+CLSIZELOG2)

#if	CLSIZE==1
#define clbase(i)	(i)
#define clrnd(i)	(i)
#else
/* give the base virtual address (first of CLSIZE) */
#define clbase(i)	((i) &~ (CLSIZE-1))
/* round a number of clicks up to a whole cluster */
#define clrnd(i)	(((i) + (CLSIZE-1)) &~ (CLSIZE-1))
#endif

/* CBLOCK is the size of a clist block, must be power of 2 */
#define CBLOCK	64
#define CBSIZE	(CBLOCK - sizeof(struct cblock *))	/* data chars/clist */
#define CROUND	(CBLOCK - 1)				/* clist rounding */


/*
 * File system parameters and macros.
 *
 * The file system is made out of blocks of at most MAXBSIZE units,
 * with smaller units (fragments) only in the last direct block.
 * MAXBSIZE primarily determines the size of buffers in the buffer
 * pool. It may be made larger without any effect on existing
 * file systems; however making it smaller make make some file
 * systems unmountable.
 *
 * Note that the blocked devices are assumed to have DEV_BSIZE
 * "sectors" and that fragments must be some multiple of this size.
 * Block devices are read in BLKDEV_IOSIZE units. This number must
 * be a power of two and in the range of
 *	DEV_BSIZE <= BLKDEV_IOSIZE <= MAXBSIZE
 * This size has no effect upon the file system, but is usually set
 * to the block size of the root file system, so as to maximize the
 * speed of ``fsck''.
 */
#define MAXBSIZE	8192
#ifdef	exl
#define DEV_BSIZE	1024
#define DEV_BSHIFT	10
#else	exl
#define DEV_BSIZE	512
#define DEV_BSHIFT	9		/* log2(DEV_BSIZE) */
#endif	exl
#define BLKDEV_IOSIZE	2048
#define MAXFRAG 	8

#define btodb(bytes)	 		/* calculates (bytes / DEV_BSIZE) */ \
	((unsigned)(bytes) >> DEV_BSHIFT)
#define dbtob(db)			/* calculates (db * DEV_BSIZE) */ \
	((unsigned)(db) << DEV_BSHIFT)

/*
 * Map a ``block device block'' to a file system block.
 * This should be device dependent, and will be after we
 * add an entry to cdevsw for that purpose.  For now though
 * just use DEV_BSIZE.
 */
#define bdbtofsb(bn)	((bn) / (BLKDEV_IOSIZE/DEV_BSIZE))

/*
 * MAXPATHLEN defines the longest permissable path length
 * after expanding symbolic links. It is used to allocate
 * a temporary buffer from the buffer pool in which to do the
 * name expansion, hence should be a power of two, and must
 * be less than or equal to MAXBSIZE.
 * MAXSYMLINKS defines the maximum number of symbolic links
 * that may be expanded in a path name. It should be set high
 * enough to allow all legitimate uses, but halt infinite loops
 * reasonably quickly.
 */
#define MAXPATHLEN	1024
#define MAXSYMLINKS	32

/*
 * bit map related macros
 */

#define setbit(a,i)	(*(((char *)(a)) + ((i)/NBBY)) |= 1<<((i)%NBBY))
#define clrbit(a,i)	(*(((char *)(a)) + ((i)/NBBY)) &= ~(1<<((i)%NBBY)))
#define isset(a,i)	(*(((char *)(a)) + ((i)/NBBY)) & (1<<((i)%NBBY)))
#define isclr(a,i)      ((*(((char *)(a)) + ((i)/NBBY)) & (1<<((i)%NBBY))) == 0)

#if	!defined(vax) && !defined(i386)
#define _bit_set(i,a)   setbit(a,i)
#define _bit_clear(i,a)	clrbit(a,i)
#define _bit_tst(i,a)	isset(a,i)
#endif	!defined(vax) && !defined(i386)


/*
 * Macros for fast min/max.
 */
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/*
 * Macros for counting and rounding.
 */
#ifndef	howmany
#define howmany(x, y)	(((x)+((y)-1))/(y))
#endif
#define roundup(x, y)	((((x)+((y)-1))/(y))*(y))

/*
 * Maximum size of hostname recognized and stored in the kernel.
 */

#define MAXHOSTNAMELEN	256
#define MAXDOMNAMELEN	256		/* maximum domain name length */

#endif	_SYS_PARAM_H_
