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
 * $Log:	buf.h,v $
 * Revision 2.11.2.1  89/12/22  22:22:11  rvb
 * 	Add B_MD1 & B_MD2 for driver's use.
 * 	[89/12/22            rvb]
 * 
 * Revision 2.11  89/09/22  13:58:10  af
 * 	Added b_command field to support Ultrix SCSI drivers.
 * 	[89/09/18            af]
 * 
 * Revision 2.10  89/04/22  15:31:17  gm0w
 * 	Removed MACH_VFS code.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.9  89/03/09  22:02:26  rpd
 * 	More cleanup.
 * 
 * Revision 2.8  89/02/25  17:52:06  gm0w
 * 	Put items that are conditional on MACH_VFS
 * 	under #ifdef KERNEL. Removed some #else MACH code.
 * 	The buf structure outside of the kernel is defined to
 * 	have both MACH_VFS and exl fields. Put buffer macros
 * 	under #ifdef KERNEL.
 * 	[89/02/13            mrt]
 * 
 * Revision 2.7  89/01/23  22:24:59  af
 * 	Added Mips specific B_NOCACHE flag, extern-alized some variables.
 * 	[89/01/09            af]
 * 	
 * 	Changes for I386: sysV fields and masks
 * 	[89/01/09            rvb]
 * 
 * Revision 2.1  88/11/25  13:05:20  rvb
 * 2.1
 * 
 * Revision 2.6  89/01/18  01:14:23  jsb
 * 	Added vnode support.
 * 	[88/12/17            jsb]
 * 
 * Revision 2.5  88/09/30  14:10:13  mrt
 * 	30-Sep-88 Mary R. Thompson (mrt) at Carnegie Mellon
 * 	made #include <mach.h> conditional on KERNEL
 * 	else #include <sys/features.h>
 * 	[88/09/30  13:37:16  mrt]
 * 
 * Revision 2.4  88/08/24  02:23:33  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:10:04  mwyoung]
 *
 * 29-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Removed unused variables.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)buf.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_BUF_H_
#define _SYS_BUF_H_

#include <sys/types.h>

/*
 * The header for buffers in the buffer pool and otherwise used
 * to describe a block i/o request is given here.  The routines
 * which manipulate these things are given in bio.c.
 *
 * Each buffer in the pool is usually doubly linked into 2 lists:
 * hashed into a chain by <dev,blkno> so it can be located in the cache,
 * and (usually) on (one of several) queues.  These lists are circular and
 * doubly linked for easy removal.
 *
 * There are currently three queues for buffers:
 *	one for buffers which must be kept permanently (super blocks)
 * 	one for buffers containing ``useful'' information (the cache)
 *	one for buffers containing ``non-useful'' information
 *		(and empty buffers, pushed onto the front)
 * The latter two queues contain the buffers which are available for
 * reallocation, are kept in lru order.  When not on one of these queues,
 * the buffers are ``checked out'' to drivers which use the available list
 * pointers to keep track of them in their i/o active queues.
 */

/*
 * Bufhd structures used at the head of the hashed buffer queues.
 * We only need three words for these, so this abbreviated
 * definition saves some space.
 */
struct bufhd
{
	long	b_flags;		/* see defines below */
	struct	buf *b_forw, *b_back;	/* fwd/bkwd pointer in chain */
};

struct buf
{
	long	b_flags;		/* too much goes here to describe */
	struct	buf *b_forw, *b_back;	/* hash chain (2 way street) */
	struct	buf *av_forw, *av_back;	/* position on free list if not BUSY */
#define b_actf	av_forw			/* alternate names for driver queue */
#define b_actl	av_back			/*    head - isn't history wonderful */
	long	b_bcount;		/* transfer count */
	long	b_bufsize;		/* size of allocated buffer */
#define b_active b_bcount		/* driver queue head: drive active */
	short	b_error;		/* returned after I/O */
	dev_t	b_dev;			/* major+minor device name */
	union {
	    caddr_t b_addr;		/* low order core address */
	    int	*b_words;		/* words for clearing */
	    struct fs *b_fs;		/* superblocks */
	    struct csum *b_cs;		/* superblock summary information */
	    struct cg *b_cg;		/* cylinder group block */
	    struct dinode *b_dino;	/* ilist */
	    daddr_t *b_daddr;		/* indirect block */
	} b_un;
	daddr_t	b_blkno;		/* block # on device */
	long	b_resid;		/* words not transferred after error */
#define b_errcnt b_resid		/* while i/o in progress: # retries */
	struct  proc *b_proc;		/* proc doing physical or swap I/O */
	struct	inode *b_ip;		/* inode associated with buffer */
	int	(*b_iodone)();		/* function called by iodone */
	int	b_pfcent;		/* center page when swapping cluster */
#ifdef	mips
	int	b_command;		/* SCSI command in progress */
#define b_gid b_command;
#endif	mips
#ifdef	exl
/* added the missing fields for System V driver (SCSI) --- csy */
	daddr_t b_sector;               /* physical sector of disk request */
	time_t	b_start;		/* request start time */
#endif	exl
};

#define BQUEUES		4		/* number of free buffer queues */

#define BQ_LOCKED	0		/* super-blocks &c */
#define BQ_LRU		1		/* lru, useful buffers */
#define BQ_AGE		2		/* rubbish */
#define BQ_EMPTY	3		/* buffer headers with no memory */

#ifdef	KERNEL
#define BUFHSZ	512
#define RND	(MAXBSIZE/DEV_BSIZE)
#if	((BUFHSZ&(BUFHSZ-1)) == 0)
#define BUFHASH(dev, dblkno)	\
	((struct buf *)&bufhash[((int)(dev)+(((int)(dblkno))/RND))&(BUFHSZ-1)])
#else
#define BUFHASH(dev, dblkno)	\
	((struct buf *)&bufhash[((int)(dev)+(((int)(dblkno))/RND)) % BUFHSZ])
#endif

extern struct	buf *buf;	/* the buffer pool itself */
extern char	*buffers;
extern int	nbuf;		/* number of buffer headers */
extern int	bufpages;	/* number of memory pages in the buffer pool */

extern struct	bufhd bufhash[BUFHSZ];	/* heads of hash lists */
extern struct	buf bfreelist[BQUEUES];	/* heads of available lists */

extern struct	buf *alloc();
extern struct	buf *realloccg();
extern struct	buf *baddr();
extern struct	buf *getblk();
extern struct	buf *geteblk();
extern struct	buf *getnewbuf();
extern struct	buf *bread();
extern struct	buf *breada();

extern unsigned minphys();
#endif	KERNEL

/*
 * These flags are kept in b_flags.
 */
#define B_WRITE		0x0000000	/* non-read pseudo-flag */
#define B_READ		0x0000001	/* read when I/O occurs */
#define B_DONE		0x0000002	/* transaction finished */
#define B_ERROR		0x0000004	/* transaction aborted */
#define B_BUSY		0x0000008	/* not on av_forw/back list */
#define B_PHYS		0x0000010	/* physical IO */
#define B_XXX		0x0000020	/* was B_MAP, alloc UNIBUS on pdp-11 */
#define B_WANTED	0x0000040	/* issue wakeup when BUSY goes off */
#define B_AGE		0x0000080	/* delayed write for correct aging */
#define B_ASYNC		0x0000100	/* don't wait for I/O completion */
#define B_DELWRI	0x0000200	/* write at exit of avail list */
#define B_TAPE		0x0000400	/* this is a magtape (no bdwrite) */
#define B_UAREA		0x0000800	/* add u-area to a swap operation */
#define B_PAGET		0x0001000	/* page in/out of page table space */
#define B_DIRTY		0x0002000	/* dirty page to be pushed out async */
#define B_PGIN		0x0004000	/* pagein op, so swap() can count it */
#define B_CACHE		0x0008000	/* did bread find us in the cache ? */
#define B_INVAL		0x0010000	/* does not contain valid info  */
#define B_LOCKED	0x0020000	/* locked in core (not reusable) */
#define B_HEAD		0x0040000	/* a buffer header, not a buffer */
#define B_BAD		0x0100000	/* bad block revectoring in progress */
#define B_CALL		0x0200000	/* call b_iodone from iodone */
#define B_NOCACHE	0x0400000	/* don't cache block when released */
#define	B_PRIVATE	0x0800000	/* private data, not part of buffers */
#define B_MD1		0x1000000	/* two bits for the driver */
#define B_MD2		0x2000000
#ifdef	i386
#define B_VERIFY	0x0400000	/* verify flag for floppy driver */
#define B_FORMAT	0x0800000	/* format flag for floppy driver */
#endif	i386
#ifdef	exl
/* added a few flags defined for System V drivers --- csy */
#define B_OPEN		0x1000000	/* open routine called */
#define B_STALE		0x2000000
#define B_RAMRD		0x4000000
#define B_RAMWT		0x8000000
#define B_PRIVLG	0x3c00000	/* privlg'd op (internal driver use) */
#endif	exl

#ifdef	KERNEL
#include <kern/macro_help.h>

/*
 * Insq/Remq for the buffer hash lists.
 */

#define bremhash(bp)						\
MACRO_BEGIN							\
	(bp)->b_back->b_forw = (bp)->b_forw;			\
	(bp)->b_forw->b_back = (bp)->b_back;			\
MACRO_END

#define binshash(bp, dp)					\
MACRO_BEGIN							\
	(bp)->b_forw = (dp)->b_forw;				\
	(bp)->b_back = (dp);					\
	(dp)->b_forw->b_back = (bp);				\
	(dp)->b_forw = (bp);					\
MACRO_END

/*
 * Insq/Remq for the buffer free lists.
 */

#define bremfree(bp)						\
MACRO_BEGIN							\
	(bp)->av_back->av_forw = (bp)->av_forw;			\
	(bp)->av_forw->av_back = (bp)->av_back;			\
MACRO_END

#define binsheadfree(bp, dp)					\
MACRO_BEGIN							\
	(dp)->av_forw->av_back = (bp);				\
	(bp)->av_forw = (dp)->av_forw;				\
	(dp)->av_forw = (bp);					\
	(bp)->av_back = (dp);					\
MACRO_END

#define binstailfree(bp, dp)					\
MACRO_BEGIN							\
	(dp)->av_back->av_forw = (bp);				\
	(bp)->av_back = (dp)->av_back;				\
	(dp)->av_back = (bp);					\
	(bp)->av_forw = (dp);					\
MACRO_END

/*
 * Take a buffer off the free list it's on and
 * mark it as being use (B_BUSY) by a device.
 */

#define notavail(bp)						\
MACRO_BEGIN							\
	int x = splbio();					\
	bremfree(bp);						\
	(bp)->b_flags |= B_BUSY;				\
	splx(x);						\
MACRO_END

#define iodone	biodone
#define iowait	biowait

/*
 * Zero out a buffer's data portion.
 */

#define clrbuf(bp)						\
MACRO_BEGIN							\
	blkclr((bp)->b_un.b_addr, (unsigned)(bp)->b_bcount);	\
	(bp)->b_resid = 0;					\
MACRO_END

#endif	KERNEL
#endif	_SYS_BUF_H_
