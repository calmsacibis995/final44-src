h15302
s 00001/00001/00152
d D 8.9 95/03/30 14:00:16 mckusick 66 65
c B_APPENDWRITE => B_NEEDCOMMIT for NFS version 3
e
s 00006/00005/00147
d D 8.8 95/01/09 18:16:28 cgd 65 64
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00005/00000/00147
d D 8.7 94/01/21 17:25:03 bostic 64 63
c add USL's copyright notice
e
s 00002/00000/00145
d D 8.6 94/01/06 22:43:54 mckusick 63 62
c need to define NOLIST for b_vnbufs list
e
s 00003/00003/00142
d D 8.5 94/01/04 16:16:23 bostic 62 61
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00003/00003/00142
d D 8.4 93/12/13 23:45:41 mckusick 61 60
c convert the hash chain, associated vnode, and free list to use <sys/queue.h>
e
s 00006/00007/00139
d D 8.3 93/09/23 15:29:50 bostic 60 59
c changes for 4.4BSD-Lite requested by USL
e
s 00092/00116/00054
d D 8.2 93/09/21 07:14:23 bostic 59 58
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00168
d D 8.1 93/06/02 19:52:35 bostic 58 57
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00031/00028/00139
d D 7.22 93/02/02 20:51:46 mckusick 57 56
c interruptable getnewbuf() and getblk(); incore returns buffer;
c add flags B_WRITEINPROG, B_APPENDWRITE, B_EINTR
e
s 00019/00000/00148
d D 7.21 92/12/09 16:09:26 mckusick 56 55
c add clustering structure and read, write, and callback routines
e
s 00011/00005/00137
d D 7.20 92/10/22 22:53:11 mckusick 55 54
c use new queue conventions
e
s 00004/00070/00138
d D 7.19 92/10/02 00:07:35 mckusick 54 53
c move crud out to vfs_bio.c where it belongs
e
s 00004/00000/00204
d D 7.18 92/07/03 00:34:48 mckusick 53 52
c protect against multiple includes
e
s 00001/00000/00203
d D 7.17 92/06/23 00:10:21 bostic 52 51
c add B_GATHERED flag; LFS flag if buffer already in a segment
e
s 00002/00002/00201
d D 7.16 92/05/27 07:11:21 bostic 51 50
c Flags word needs to be volatile; from Chris Torek/Craig Leres
e
s 00001/00001/00202
d D 7.15 92/05/04 15:55:52 mckusick 50 49
c b_iodone routine has no return value
e
s 00001/00001/00202
d D 7.14 92/01/14 12:00:15 mckusick 49 48
c breada generalized to breadn
e
s 00002/00000/00201
d D 7.13 92/01/09 21:57:27 mckusick 48 47
c new fields to support NFS leases
e
s 00021/00006/00180
d D 7.12 91/11/01 16:33:46 bostic 47 46
c LFS version 1; add LFS superblock area plus function prototypes
e
s 00002/00011/00184
d D 7.11 90/05/09 10:39:29 mckusick 46 45
c update for hp300 support
e
s 00000/00011/00195
d D 7.10 90/01/04 16:13:19 mckusick 45 44
c expand notavail inline to avoid spl's
e
s 00003/00000/00203
d D 7.9 89/11/30 22:35:58 mckusick 44 43
c add linkage fields to allow claiming by vnodes
e
s 00005/00001/00198
d D 7.8 89/08/26 14:19:06 mckusick 43 42
c generalize the buffer pool so that NFS can become a client
e
s 00021/00012/00178
d D 7.7 89/05/09 16:13:47 mckusick 42 41
c merge in vnodes
e
s 00001/00000/00189
d D 7.6 88/05/14 11:25:49 karels 41 40
c raw read/write support from torek: add strategy to cdevsw, B_RAW flag
e
s 00001/00002/00188
d D 7.5 87/05/16 10:46:49 bostic 40 39
c can't ref bio.c it's gone
e
s 00000/00000/00190
d D 7.4 87/04/02 15:36:20 karels 39 37
c working again
e
s 00009/00000/00190
d D 7.3.1.1 87/04/02 15:17:31 karels 38 37
c ifdef for dev_bsize
e
s 00000/00008/00190
d D 7.3 87/03/03 22:32:20 karels 37 36
c rm tahoe grot
e
s 00008/00000/00190
d D 7.2 86/10/13 20:46:13 karels 36 35
c merge in tahoe system
e
s 00001/00001/00189
d D 7.1 86/06/04 23:20:02 mckusick 35 34
c 4.3BSD release version
e
s 00001/00001/00189
d D 6.8 86/05/14 15:35:30 karels 34 33
c an spl6 that almost got away...
e
s 00002/00002/00188
d D 6.7 86/02/23 23:00:51 karels 33 32
c lint
e
s 00007/00001/00183
d D 6.6 85/06/08 14:54:29 mckusick 32 31
c Add copyright
e
s 00006/00001/00178
d D 6.5 85/03/13 20:22:09 mckusick 31 30
c use power of two to avoid modulo
e
s 00000/00015/00179
d D 6.4 85/01/10 23:39:08 mckusick 30 29
c get rid of swapbuf macro
e
s 00015/00000/00179
d D 6.3 84/12/03 00:00:09 mckusick 29 28
c add swapbuf macro
e
s 00001/00001/00178
d D 6.2 84/08/03 20:30:36 mckusick 28 27
c increase size of hash chain head to reduce collisions
e
s 00000/00000/00179
d D 6.1 83/07/29 06:11:42 sam 27 26
c 4.2 distribution
e
s 00000/00024/00179
d D 4.22 83/07/01 02:24:46 root 26 25
c purge #if sun's
e
s 00006/00003/00197
d D 4.21 83/05/18 02:11:23 sam 25 24
c stuff for variable sized swap partitions (note addition to bdevsw)
e
s 00002/00001/00198
d D 4.20 83/01/16 15:09:15 mckusick 24 23
c add "bufpages", the number of memory pages in the buffer pool
e
s 00021/00000/00178
d D 4.19 82/12/17 12:10:49 sam 23 22
c sun merge
e
s 00005/00007/00173
d D 4.18 82/11/13 23:07:55 sam 22 21
c merge 4.1b and 4.1c
e
s 00006/00000/00174
d D 4.17 82/10/10 17:12:05 root 21 20
c header file cleanup while moving vax files to their own directory
e
s 00046/00002/00128
d D 4.16 82/05/31 19:12:05 mckusick 20 19
c make queue insertion and deletion into macros
e
s 00018/00002/00112
d D 4.15 82/05/31 17:03:43 mckusick 19 18
c update for split of swap.c from bio.c
e
s 00006/00001/00108
d D 4.14 82/04/19 19:26:40 mckusic 18 17
c merge in the new file system
e
s 00021/00020/00088
d D 4.13 81/05/09 22:38:12 root 17 16
c more definitions, for bad block handling
e
s 00010/00010/00098
d D 4.12 81/03/09 00:26:36 wnj 16 15
c lint
e
s 00002/00000/00106
d D 4.11 81/02/27 17:50:48 wnj 15 14
c for dynamic kernel allocate version
e
s 00001/00000/00105
d D 4.10 81/02/27 02:38:30 wnj 14 13
c dynamic alloc kernel version
e
s 00004/00004/00101
d D 4.9 81/02/27 00:01:58 wnj 13 12
c move to pointer base to allow dyn allocation
e
s 00001/00001/00104
d D 4.8 81/02/19 21:39:07 wnj 12 11
c %G%->%E%
e
s 00057/00062/00048
d D 4.7 81/02/07 15:51:15 wnj 11 10
c reformatting; bufhd, queues to 3 ...
e
s 00009/00000/00101
d D 4.6 81/01/31 20:39:38 kre 10 9
c mussing
e
s 00001/00001/00100
d D 4.5 81/01/30 20:04:56 kre 9 8
c reduced BQUEUES from 4 to 3
e
s 00000/00001/00101
d D 4.4 81/01/30 01:48:33 wnj 8 7
c remove crud
e
s 00006/00001/00096
d D 4.3 81/01/30 01:39:56 wnj 7 6
c new bfreelist scheme
e
s 00019/00018/00078
d D 4.2 81/01/27 13:35:55 kre 6 5
c /b_flags/s/int/long/		added B_INVAL flag (invalid buffer)
e
s 00000/00000/00096
d D 4.1 80/11/09 17:00:35 bill 5 4
c stamp for 4bsd
e
s 00001/00001/00095
d D 3.4 80/06/07 02:56:05 bill 4 3
c %H%->%G%
e
s 00016/00016/00080
d D 3.3 80/06/04 13:42:17 bill 3 2
c reformat
e
s 00001/00000/00095
d D 3.2 80/04/11 20:57:11 bill 2 1
c added b_hlink for hashing
e
s 00095/00000/00000
d D 3.1 80/04/09 16:23:18 bill 1 0
c date and time created 80/04/09 16:23:18 by bill
e
u
U
f b 
t
T
I 1
D 4
/*	%M%	%I%	%H%	*/
E 4
I 4
D 12
/*	%M%	%I%	%G%	*/
E 12
I 12
D 32
/*	%M%	%I%	%E%	*/
E 32
I 32
/*
D 35
 * Copyright (c) 1982 Regents of the University of California.
E 35
I 35
D 42
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 35
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 42
I 42
D 58
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 58
I 58
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 64
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 64
E 58
E 42
 *
I 42
D 46
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 46
I 46
 * %sccs.include.redist.c%
E 46
 *
E 42
 *	%W% (Berkeley) %G%
 */
E 32
E 12
E 4

I 53
D 62
#ifndef _BUF_H_
#define	_BUF_H_
E 62
I 62
#ifndef _SYS_BUF_H_
#define	_SYS_BUF_H_
E 62
I 55
#include <sys/queue.h>
E 55

I 63
#define NOLIST ((struct buf *)0x87654321)

E 63
E 53
I 18
D 19
/*	buf.h	2.1	3/25/82	*/

E 19
E 18
/*
I 11
D 59
 * The header for buffers in the buffer pool and otherwise used
D 40
 * to describe a block i/o request is given here.  The routines
 * which manipulate these things are given in bio.c.
E 40
I 40
 * to describe a block i/o request is given here.
E 40
 *
E 11
 * Each buffer in the pool is usually doubly linked into 2 lists:
D 11
 * the device with which it is currently associated (always)
 * and also on a list of blocks available for allocation
 * for other use (usually).
 * The latter list is kept in last-used order, and the two
 * lists are doubly linked to make it easy to remove
 * a buffer from one list when it was found by
 * looking through the other.
 * A buffer is on the available list, and is liable
 * to be reassigned to another disk block, if and only
 * if it is not marked BUSY.  When a buffer is busy, the
 * available-list pointers can be used for other purposes.
 * Most drivers use the forward ptr as a link in their I/O
 * active queue.
 * A buffer header contains all the information required
 * to perform I/O.
 * Most of the routines which manipulate these things
 * are in bio.c.
E 11
I 11
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
E 59
I 59
 * The buffer header describes an I/O operation in the kernel.
E 59
E 11
 */
I 11
D 59

E 59
D 54
/*
 * Bufhd structures used at the head of the hashed buffer queues.
 * We only need three words for these, so this abbreviated
 * definition saves some space.
 */
E 11
I 10
struct bufhd
{
D 51
	long	b_flags;		/* see defines below */
E 51
I 51
	volatile long	b_flags;	/* see defines below */
E 51
D 11
	struct	buf *b_forw;		/* headed by d_tab of conf.c */
	struct	buf *b_back;		/*  "  */
E 11
I 11
	struct	buf *b_forw, *b_back;	/* fwd/bkwd pointer in chain */
E 11
};
E 10
struct buf
{
E 54
I 54
struct buf {
E 54
D 6
	int	b_flags;		/* see defines below */
E 6
I 6
D 11
	long	b_flags;		/* see defines below */
E 6
	struct	buf *b_forw;		/* headed by d_tab of conf.c */
	struct	buf *b_back;		/*  "  */
	struct	buf *av_forw;		/* position on free list, */
	struct	buf *av_back;		/*     if not BUSY*/
E 11
I 11
D 51
	long	b_flags;		/* too much goes here to describe */
E 51
I 51
D 59
	volatile long	b_flags;	/* too much goes here to describe */
E 51
D 54
	struct	buf *b_forw, *b_back;	/* hash chain (2 way street) */
	struct	buf *av_forw, *av_back;	/* position on free list if not BUSY */
E 54
I 54
D 55
	struct	buf *b_forw, **b_back;	/* hash chain (2 way street) */
E 54
I 44
	struct	buf *b_blockf, **b_blockb;/* associated vnode */
E 44
D 54
#define	b_actf	av_forw			/* alternate names for driver queue */
#define	b_actl	av_back			/*    head - isn't history wonderful */
E 54
I 54
	struct	buf *b_actf, **b_actb;	/* position on free list if not BUSY */
E 55
I 55
	struct 	queue_entry b_hash;	/* hash chain */
	struct 	queue_entry b_vnbufs;	/* associated vnode */
	struct 	queue_entry b_freelist;	/* position on free list if not BUSY */
	struct	buf *b_actf, **b_actb;  /* device driver I/O queue when BUSY */
E 55
E 54
	long	b_bcount;		/* transfer count */
I 22
	long	b_bufsize;		/* size of allocated buffer */
E 22
D 55
#define	b_active b_bcount		/* driver queue head: drive active */
E 55
	short	b_error;		/* returned after I/O */
E 11
	dev_t	b_dev;			/* major+minor device name */
D 11
	unsigned b_bcount;		/* transfer count */
E 11
	union {
	    caddr_t b_addr;		/* low order core address */
	    int	*b_words;		/* words for clearing */
D 18
	    struct filsys *b_filsys;	/* superblocks */
E 18
I 18
D 47
	    struct fs *b_fs;		/* superblocks */
E 47
I 47
	    struct fs *b_fs;		/* UFS superblocks */
	    struct lfs *b_lfs;		/* LFS superblocks */
E 47
	    struct csum *b_cs;		/* superblock summary information */
	    struct cg *b_cg;		/* cylinder group block */
E 18
	    struct dinode *b_dino;	/* ilist */
	    daddr_t *b_daddr;		/* indirect block */
E 59
I 59
D 61
	struct 	queue_entry b_hash;	/* Hash chain. */
	struct 	queue_entry b_vnbufs;	/* Buffer's associated vnode. */
	struct 	queue_entry b_freelist;	/* Free list position if not active. */
E 61
I 61
	LIST_ENTRY(buf) b_hash;		/* Hash chain. */
	LIST_ENTRY(buf) b_vnbufs;	/* Buffer's associated vnode. */
	TAILQ_ENTRY(buf) b_freelist;	/* Free list position if not active. */
E 61
	struct	buf *b_actf, **b_actb;	/* Device driver queue when active. */
	struct  proc *b_proc;		/* Associated proc; NULL if kernel. */
	volatile long	b_flags;	/* B_* flags. */
	int	b_error;		/* Errno value. */
	long	b_bufsize;		/* Allocated buffer size. */
	long	b_bcount;		/* Valid bytes in buffer. */
	long	b_resid;		/* Remaining I/O. */
	dev_t	b_dev;			/* Device associated with buffer. */
	struct {
		caddr_t	b_addr;		/* Memory, superblocks, indirect etc. */
E 59
	} b_un;
I 44
D 59
	daddr_t	b_lblkno;		/* logical block number */
E 44
	daddr_t	b_blkno;		/* block # on device */
I 38
#ifdef SECSIZE
	long	b_blksize;		/* size of device blocks */
#endif SECSIZE
E 38
D 11
	char	b_xmem;			/* high order core address */
	char	b_error;		/* returned after I/O */
I 2
	short	b_hlink;		/* hash links for buffer cache */
E 2
	unsigned int b_resid;		/* words not transferred after error */
	struct  proc  *b_proc;		/* process doing physical or swap I/O */
E 11
I 11
	long	b_resid;		/* words not transferred after error */
D 55
#define	b_errcnt b_resid		/* while i/o in progress: # retries */
E 55
D 25
#define	b_pfcent b_resid		/* garbage: don't ask */
E 25
	struct  proc *b_proc;		/* proc doing physical or swap I/O */
I 23
D 50
	int	(*b_iodone)();		/* function called by iodone */
E 50
I 50
	void	(*b_iodone)();		/* function called by iodone */
E 50
I 42
D 43
	struct vnode *b_vp;		/* Vnode for dev */
E 43
I 43
	struct	vnode *b_vp;		/* vnode for dev */
E 43
E 42
I 25
	int	b_pfcent;		/* center page when swapping cluster */
I 43
	struct	ucred *b_rcred;		/* ref to read credentials */
	struct	ucred *b_wcred;		/* ref to write credendtials */
	int	b_dirtyoff;		/* offset in buffer of dirty region */
	int	b_dirtyend;		/* offset of end of dirty region */
I 46
	caddr_t	b_saveaddr;		/* original b_addr for PHYSIO */
I 48
	int	b_validoff;		/* offset in buffer of valid region */
	int	b_validend;		/* offset of end of valid region */
E 59
I 59
	void	*b_saveaddr;		/* Original b_addr for physio. */
	daddr_t	b_lblkno;		/* Logical block number. */
	daddr_t	b_blkno;		/* Underlying physical block number. */
					/* Function to call upon completion. */
	void	(*b_iodone) __P((struct buf *));
	struct	vnode *b_vp;		/* Device vnode. */
D 65
	int	b_pfcent;		/* Center page when swapping cluster. */
E 65
I 65
	long	b_pfcent;		/* Center page when swapping cluster. */
					/* XXX pfcent should be int; overld. */
E 65
	int	b_dirtyoff;		/* Offset in buffer of dirty region. */
	int	b_dirtyend;		/* Offset of end of dirty region. */
	struct	ucred *b_rcred;		/* Read credentials reference. */
	struct	ucred *b_wcred;		/* Write credentials reference. */
	int	b_validoff;		/* Offset in buffer of valid region. */
	int	b_validend;		/* Offset of end of valid region. */
E 59
E 48
E 46
E 43
I 36
D 37
#if defined(tahoe)
#define	MAXBPTE	32			/* must be >=KLMAX */
	long	b_upte[MAXBPTE+1];	/* user pte's for swap/raw I/O */
	int	b_ptecnt;		/* number of user pte's in b_upte */
#endif
E 37
E 36
D 26
#ifdef sun
	caddr_t	b_saddr;		/* saved address */
	short	b_kmx;			/* saved kernelmap index */
	short	b_npte;			/* number of pte's mapped */
#endif
E 26
E 25
E 23
E 11
};
I 55

I 59
D 60
#define	b_data	b_un.b_addr	
E 60
I 60
/* Device driver compatibility definitions. */
#define	b_active b_bcount		/* Driver queue head: drive active. */
#define	b_data	 b_un.b_addr		/* b_un.b_addr is not changeable. */
#define	b_errcnt b_resid		/* Retry count while I/O in progress. */
#define	iodone	 biodone		/* Old name for biodone. */
#define	iowait	 biowait		/* Old name for biowait. */
E 60

E 59
/*
D 59
 * Defines for device drivers.
E 59
I 59
 * These flags are kept in b_flags.
E 59
 */
D 59
#define	b_active b_bcount		/* driver queue head: drive active */
#define	b_errcnt b_resid		/* while i/o in progress: # retries */
E 59
I 59
#define	B_AGE		0x00000001	/* Move to age queue when I/O done. */
D 66
#define	B_APPENDWRITE	0x00000002	/* Append-write in progress. */
E 66
I 66
#define	B_NEEDCOMMIT	0x00000002	/* Append-write in progress. */
E 66
#define	B_ASYNC		0x00000004	/* Start I/O, do not wait. */
#define	B_BAD		0x00000008	/* Bad block revectoring in progress. */
#define	B_BUSY		0x00000010	/* I/O in progress. */
#define	B_CACHE		0x00000020	/* Bread found us in the cache. */
#define	B_CALL		0x00000040	/* Call b_iodone from biodone. */
#define	B_DELWRI	0x00000080	/* Delay I/O until buffer reused. */
#define	B_DIRTY		0x00000100	/* Dirty page to be pushed out async. */
#define	B_DONE		0x00000200	/* I/O completed. */
#define	B_EINTR		0x00000400	/* I/O was interrupted */
#define	B_ERROR		0x00000800	/* I/O error occurred. */
#define	B_GATHERED	0x00001000	/* LFS: already in a segment. */
#define	B_INVAL		0x00002000	/* Does not contain valid info. */
#define	B_LOCKED	0x00004000	/* Locked in core (not reusable). */
#define	B_NOCACHE	0x00008000	/* Do not cache block after use. */
#define	B_PAGET		0x00010000	/* Page in/out of page table space. */
#define	B_PGIN		0x00020000	/* Pagein op, so swap() can count it. */
#define	B_PHYS		0x00040000	/* I/O to user memory. */
#define	B_RAW		0x00080000	/* Set by physio for raw transfers. */
#define	B_READ		0x00100000	/* Read buffer. */
#define	B_TAPE		0x00200000	/* Magnetic tape I/O. */
#define	B_UAREA		0x00400000	/* Buffer describes Uarea I/O. */
#define	B_WANTED	0x00800000	/* Process wants this buffer. */
#define	B_WRITE		0x00000000	/* Write buffer (pseudo flag). */
#define	B_WRITEINPROG	0x01000000	/* Write in progress. */
#define	B_XXX		0x02000000	/* Debugging flag. */
E 59
E 55
D 60

I 59
/* Device driver compatibility definitions. */
#define	b_active b_bcount		/* Driver queue head: drive active. */
#define	b_errcnt b_resid		/* Retry count while I/O in progress. */
#define	iodone	 biodone		/* Old name for biodone. */
#define	iowait	 biowait		/* Old name for biowait. */
E 60

E 59
I 56
/*
D 59
 * This structure describes a clustered I/O.  It is
 * stored in the b_saveaddr field of the buffer on
 * which I/O is performed.  At I/O completion, cluster
 * callback uses the structure to parcel I/Os to
 * individual buffers, and then frees this structure.
E 59
I 59
 * This structure describes a clustered I/O.  It is stored in the b_saveaddr
 * field of the buffer on which I/O is done.  At I/O completion, cluster
 * callback uses the structure to parcel I/O's to individual buffers, and
 * then free's this structure.
E 59
 */
struct cluster_save {
D 59
	long	bs_bcount;
	long	bs_bufsize;
	caddr_t	bs_saveaddr;
	int	bs_nchildren;
	struct buf **bs_children;
E 59
I 59
	long	bs_bcount;		/* Saved b_bcount. */
	long	bs_bufsize;		/* Saved b_bufsize. */
	void	*bs_saveaddr;		/* Saved b_addr. */
	int	bs_nchildren;		/* Number of associated buffers. */
	struct buf **bs_children;	/* List of associated buffers. */
E 59
};

I 59
/*
 * Zero out the buffer's data area.
 */
#define	clrbuf(bp) {							\
D 65
	blkclr((bp)->b_data, (u_int)(bp)->b_bcount);			\
E 65
I 65
	bzero((bp)->b_data, (u_int)(bp)->b_bcount);			\
E 65
	(bp)->b_resid = 0;						\
}

/* Flags to low-level allocation routines. */
#define B_CLRBUF	0x01	/* Request allocated buffer be cleared. */
#define B_SYNC		0x02	/* Do all allocations synchronously. */

E 59
E 56
I 7
D 9
#define	BQUEUES		4		/* number of free buffer queues */
E 9
I 9
D 22
#define	BQUEUES		3		/* number of free buffer queues */
E 22
I 22
D 54
#define	BQUEUES		4		/* number of free buffer queues */

E 22
I 10
#define	BQ_LOCKED	0		/* super-blocks &c */
#define	BQ_LRU		1		/* lru, useful buffers */
#define	BQ_AGE		2		/* rubbish */
I 22
#define	BQ_EMPTY	3		/* buffer headers with no memory */
E 22
E 10
E 9

E 7
#ifdef	KERNEL
I 38
#ifdef SECSIZE
#define	BUFHSZ		512
#define	MINSECSIZE	512
#define RND	(MAXBSIZE/MINSECSIZE)
#else SECSIZE
E 38
I 19
D 28
#define	BUFHSZ	63
E 28
I 28
D 31
#define	BUFHSZ	509
E 31
I 31
#define	BUFHSZ	512
E 31
E 28
#define RND	(MAXBSIZE/DEV_BSIZE)
I 38
#endif SECSIZE
E 38
I 31
#if	((BUFHSZ&(BUFHSZ-1)) == 0)
E 31
D 42
#define	BUFHASH(dev, dblkno)	\
I 31
	((struct buf *)&bufhash[((int)(dev)+(((int)(dblkno))/RND))&(BUFHSZ-1)])
E 42
I 42
#define	BUFHASH(dvp, dblkno)	\
	((struct buf *)&bufhash[((int)(dvp)+(((int)(dblkno))/RND))&(BUFHSZ-1)])
E 42
#else
D 42
#define	BUFHASH(dev, dblkno)	\
E 31
	((struct buf *)&bufhash[((int)(dev)+(((int)(dblkno))/RND)) % BUFHSZ])
E 42
I 42
#define	BUFHASH(dvp, dblkno)	\
	((struct buf *)&bufhash[((int)(dvp)+(((int)(dblkno))/RND)) % BUFHSZ])
E 42
I 31
#endif
E 31

E 54
I 54
#ifdef KERNEL
E 54
E 19
D 11
extern	struct buf buf[];		/* The buffer pool itself */
E 11
I 11
D 13
extern	struct buf buf[];		/* the buffer pool itself */
E 11
extern	struct buf swbuf[];		/* swap I/O headers */
E 13
I 13
D 16
extern	struct buf *buf;		/* the buffer pool itself */
I 14
extern	char *buffers;
E 14
extern	int nbuf;
extern	struct buf *swbuf;		/* swap I/O headers */
extern	int nswbuf;
I 15
extern	short *swsize;
extern	int *swpf;
E 15
E 13
I 7
extern	struct buf bfreelist[BQUEUES];	/* heads of available lists */
E 7
D 8
extern	struct buf bfreelist;		/* head of available list */
E 8
extern	struct buf bswlist;		/* head of free swap header list */
extern	struct buf *bclnlist;		/* head of cleaned page list */
E 16
I 16
D 59
struct	buf *buf;		/* the buffer pool itself */
char	*buffers;
D 24
int	nbuf;
E 24
I 24
int	nbuf;			/* number of buffer headers */
int	bufpages;		/* number of memory pages in the buffer pool */
E 24
struct	buf *swbuf;		/* swap I/O headers */
int	nswbuf;
D 25
short	*swsize;
int	*swpf;
E 25
I 19
D 54
struct	bufhd bufhash[BUFHSZ];	/* heads of hash lists */
E 19
struct	buf bfreelist[BQUEUES];	/* heads of available lists */
E 54
struct	buf bswlist;		/* head of free swap header list */
struct	buf *bclnlist;		/* head of cleaned page list */
E 59
I 59
int	nbuf;			/* The number of buffer headers */
struct	buf *buf;		/* The buffer headers. */
char	*buffers;		/* The buffer contents. */
int	bufpages;		/* Number of memory pages in the buffer pool. */
struct	buf *swbuf;		/* Swap I/O buffer headers. */
int	nswbuf;			/* Number of swap I/O buffer headers. */
struct	buf bswlist;		/* Head of swap I/O buffer headers free list. */
struct	buf *bclnlist;		/* Head of cleaned page list. */
E 59
E 16

D 42
struct	buf *alloc();
I 18
struct	buf *realloccg();
E 18
struct	buf *baddr();
E 42
D 47
struct	buf *getblk();
struct	buf *geteblk();
I 22
struct	buf *getnewbuf();
E 22
D 42
struct	buf *bread();
struct	buf *breada();
E 42

unsigned minphys();
E 47
I 47
__BEGIN_DECLS
int	allocbuf __P((struct buf *, int));
D 65
int	bawrite __P((struct buf *));
int	bdwrite __P((struct buf *));
E 65
I 65
void	bawrite __P((struct buf *));
void	bdwrite __P((struct buf *));
E 65
void	biodone __P((struct buf *));
int	biowait __P((struct buf *));
int	bread __P((struct vnode *, daddr_t, int,
	    struct ucred *, struct buf **));
D 49
int	breada __P((struct vnode *, daddr_t, int, daddr_t, int,
E 49
I 49
int	breadn __P((struct vnode *, daddr_t, int, daddr_t *, int *, int,
E 49
	    struct ucred *, struct buf **));
D 65
int	brelse __P((struct buf *));
E 65
I 65
void	brelse __P((struct buf *));
E 65
void	bufinit __P((void));
int	bwrite __P((struct buf *));
I 56
void	cluster_callback __P((struct buf *));
int	cluster_read __P((struct vnode *, u_quad_t, daddr_t, long,
	    struct ucred *, struct buf **));
void	cluster_write __P((struct buf *, u_quad_t));
E 56
D 57
struct buf *getblk __P((struct vnode *, daddr_t, int));
E 57
I 57
struct buf *getblk __P((struct vnode *, daddr_t, int, int, int));
E 57
struct buf *geteblk __P((int));
D 57
struct buf *getnewbuf __P((void));
int	incore __P((struct vnode *, daddr_t));
E 57
I 57
struct buf *getnewbuf __P((int slpflag, int slptimeo));
struct buf *incore __P((struct vnode *, daddr_t));
E 57
u_int	minphys __P((struct buf *bp));
__END_DECLS
E 47
#endif
D 13

#define	NSWBUF	48			/* number of swap I/O headers */
E 13
D 59

/*
 * These flags are kept in b_flags.
 */
D 6
#define	B_WRITE	 0x0000	/* non-read pseudo-flag */
D 3
#define	B_READ	 0x0001	/* read when I/O occurs */
#define	B_DONE	 0x0002	/* transaction finished */
#define	B_ERROR	 0x0004	/* transaction aborted */
#define	B_BUSY	 0x0008	/* not on av_forw/back list */
#define	B_PHYS	 0x0010	/* Physical IO potentially using UNIBUS map */
#define	B_MAP	 0x0020	/* This block has the UNIBUS map allocated */
#define	B_WANTED 0x0040	/* issue wakeup when BUSY goes off */
#define	B_AGE	 0x0080	/* delayed write for correct aging */
#define	B_ASYNC	 0x0100	/* don't wait for I/O completion */
#define	B_DELWRI 0x0200	/* don't write till block leaves available list */
#define	B_TAPE	 0x0400	/* this is a magtape (no bdwrite) */
#define	B_UAREA  0x0800	/* add u-area to a swap operation */
#define	B_PAGET	 0x1000	/* page in/out of page table space */
#define	B_DIRTY	 0x2000	/* dirty page to be pushed out async */
#define	B_PGIN	 0x4000 /* page in flag to swap(), for counting */
#define	B_CACHE	 0x8000	/* did bread find this block in the cache? */
E 3
I 3
#define	B_READ		0x0001	/* read when I/O occurs */
#define	B_DONE		0x0002	/* transaction finished */
#define	B_ERROR		0x0004	/* transaction aborted */
#define	B_BUSY		0x0008	/* not on av_forw/back list */
#define	B_PHYS		0x0010	/* physical IO */
#define	B_MAP		0x0020	/* UNIBUS map allocated */
#define	B_WANTED	0x0040	/* issue wakeup when BUSY goes off */
#define	B_AGE		0x0080	/* delayed write for correct aging */
#define	B_ASYNC		0x0100	/* don't wait for I/O completion */
#define	B_DELWRI	0x0200	/* write at exit of avail list */
#define	B_TAPE		0x0400	/* this is a magtape (no bdwrite) */
#define	B_UAREA		0x0800	/* add u-area to a swap operation */
#define	B_PAGET		0x1000	/* page in/out of page table space */
#define	B_DIRTY		0x2000	/* dirty page to be pushed out async */
#define	B_PGIN		0x4000	/* pagein op, so swap() can count it */
#define	B_CACHE		0x8000	/* did bread find us in the cache ? */
E 6
I 6
D 11
#define	B_WRITE		0x00000	/* non-read pseudo-flag */
#define	B_READ		0x00001	/* read when I/O occurs */
#define	B_DONE		0x00002	/* transaction finished */
#define	B_ERROR		0x00004	/* transaction aborted */
#define	B_BUSY		0x00008	/* not on av_forw/back list */
#define	B_PHYS		0x00010	/* physical IO */
#define	B_MAP		0x00020	/* UNIBUS map allocated */
#define	B_WANTED	0x00040	/* issue wakeup when BUSY goes off */
#define	B_AGE		0x00080	/* delayed write for correct aging */
#define	B_ASYNC		0x00100	/* don't wait for I/O completion */
#define	B_DELWRI	0x00200	/* write at exit of avail list */
#define	B_TAPE		0x00400	/* this is a magtape (no bdwrite) */
#define	B_UAREA		0x00800	/* add u-area to a swap operation */
#define	B_PAGET		0x01000	/* page in/out of page table space */
#define	B_DIRTY		0x02000	/* dirty page to be pushed out async */
#define	B_PGIN		0x04000	/* pagein op, so swap() can count it */
#define	B_CACHE		0x08000	/* did bread find us in the cache ? */
D 7
#define	B_INVAL		0x10000	/* buffer contains invalid data */
E 7
I 7
#define	B_INVAL		0x10000	/* does not contain valid info (if not BUSY) */
#define	B_LOCKED	0x20000	/* this buffer locked in core (not reusable) */
#define	B_HEAD		0x40000	/* this is a buffer header, not a buffer */
E 7
E 6
E 3

/*
 * special redeclarations for
 * the head of the queue per
 * device driver.
 */
#define	b_actf		av_forw
#define	b_actl		av_back
#define	b_active	b_bcount
#define	b_errcnt	b_resid
#define	b_pfcent	b_resid
E 11
I 11
D 17
#define	B_WRITE		0x00000		/* non-read pseudo-flag */
#define	B_READ		0x00001		/* read when I/O occurs */
#define	B_DONE		0x00002		/* transaction finished */
#define	B_ERROR		0x00004		/* transaction aborted */
#define	B_BUSY		0x00008		/* not on av_forw/back list */
#define	B_PHYS		0x00010		/* physical IO */
#define	B_XXX		0x00020		/* was B_MAP, alloc UNIBUS on pdp-11 */
#define	B_WANTED	0x00040		/* issue wakeup when BUSY goes off */
#define	B_AGE		0x00080		/* delayed write for correct aging */
#define	B_ASYNC		0x00100		/* don't wait for I/O completion */
#define	B_DELWRI	0x00200		/* write at exit of avail list */
#define	B_TAPE		0x00400		/* this is a magtape (no bdwrite) */
#define	B_UAREA		0x00800		/* add u-area to a swap operation */
#define	B_PAGET		0x01000		/* page in/out of page table space */
#define	B_DIRTY		0x02000		/* dirty page to be pushed out async */
#define	B_PGIN		0x04000		/* pagein op, so swap() can count it */
#define	B_CACHE		0x08000		/* did bread find us in the cache ? */
#define	B_INVAL		0x10000		/* does not contain valid info  */
#define	B_LOCKED	0x20000		/* locked in core (not reusable) */
#define	B_HEAD		0x40000		/* a buffer header, not a buffer */
E 17
I 17
D 57
#define	B_WRITE		0x000000	/* non-read pseudo-flag */
#define	B_READ		0x000001	/* read when I/O occurs */
#define	B_DONE		0x000002	/* transaction finished */
#define	B_ERROR		0x000004	/* transaction aborted */
#define	B_BUSY		0x000008	/* not on av_forw/back list */
#define	B_PHYS		0x000010	/* physical IO */
#define	B_XXX		0x000020	/* was B_MAP, alloc UNIBUS on pdp-11 */
#define	B_WANTED	0x000040	/* issue wakeup when BUSY goes off */
#define	B_AGE		0x000080	/* delayed write for correct aging */
#define	B_ASYNC		0x000100	/* don't wait for I/O completion */
#define	B_DELWRI	0x000200	/* write at exit of avail list */
#define	B_TAPE		0x000400	/* this is a magtape (no bdwrite) */
#define	B_UAREA		0x000800	/* add u-area to a swap operation */
#define	B_PAGET		0x001000	/* page in/out of page table space */
#define	B_DIRTY		0x002000	/* dirty page to be pushed out async */
#define	B_PGIN		0x004000	/* pagein op, so swap() can count it */
#define	B_CACHE		0x008000	/* did bread find us in the cache ? */
#define	B_INVAL		0x010000	/* does not contain valid info  */
#define	B_LOCKED	0x020000	/* locked in core (not reusable) */
#define	B_HEAD		0x040000	/* a buffer header, not a buffer */
I 52
#define	B_GATHERED	0x080000	/* LFS: already in a segment */
E 52
#define	B_BAD		0x100000	/* bad block revectoring in progress */
I 23
#define	B_CALL		0x200000	/* call b_iodone from iodone */
I 41
#define	B_RAW		0x400000	/* set by physio for raw transfers */
I 42
#define	B_NOCACHE	0x800000	/* do not cache block after use */
E 57
I 57
#define	B_WRITE		0x00000000	/* non-read pseudo-flag */
#define	B_READ		0x00000001	/* read when I/O occurs */
#define	B_DONE		0x00000002	/* transaction finished */
#define	B_ERROR		0x00000004	/* transaction aborted */
#define	B_BUSY		0x00000008	/* not on av_forw/back list */
#define	B_PHYS		0x00000010	/* physical IO */
#define	B_XXX		0x00000020	/* was B_MAP, alloc UNIBUS on pdp-11 */
#define	B_WANTED	0x00000040	/* issue wakeup when BUSY goes off */
#define	B_AGE		0x00000080	/* delayed write for correct aging */
#define	B_ASYNC		0x00000100	/* don't wait for I/O completion */
#define	B_DELWRI	0x00000200	/* write at exit of avail list */
#define	B_TAPE		0x00000400	/* this is a magtape (no bdwrite) */
#define	B_UAREA		0x00000800	/* add u-area to a swap operation */
#define	B_PAGET		0x00001000	/* page in/out of page table space */
#define	B_DIRTY		0x00002000	/* dirty page to be pushed out async */
#define	B_PGIN		0x00004000	/* pagein op, so swap() can count it */
#define	B_CACHE		0x00008000	/* did bread find us in the cache ? */
#define	B_INVAL		0x00010000	/* does not contain valid info  */
#define	B_LOCKED	0x00020000	/* locked in core (not reusable) */
#define	B_HEAD		0x00040000	/* a buffer header, not a buffer */
#define	B_GATHERED	0x00080000	/* LFS: already in a segment */
#define	B_BAD		0x00100000	/* bad block revectoring in progress */
#define	B_CALL		0x00200000	/* call b_iodone from iodone */
#define	B_RAW		0x00400000	/* set by physio for raw transfers */
#define	B_NOCACHE	0x00800000	/* do not cache block after use */
#define	B_WRITEINPROG	0x01000000	/* write in progress on buffer */
#define	B_APPENDWRITE	0x02000000	/* append-write in progress on buffer */
#define	B_EINTR		0x04000000	/* I/O was interrupted */
E 57
E 42
E 41
I 36
D 37
#if defined(tahoe)
#define B_NOT1K		0x400000	/* I/O is through intermediate buffer */
#endif
E 37
E 36
E 23
I 19
D 54

/*
I 20
 * Insq/Remq for the buffer hash lists.
 */
#define	bremhash(bp) { \
	(bp)->b_back->b_forw = (bp)->b_forw; \
	(bp)->b_forw->b_back = (bp)->b_back; \
}
#define	binshash(bp, dp) { \
	(bp)->b_forw = (dp)->b_forw; \
	(bp)->b_back = (dp); \
	(dp)->b_forw->b_back = (bp); \
	(dp)->b_forw = (bp); \
}

/*
 * Insq/Remq for the buffer free lists.
 */
#define	bremfree(bp) { \
	(bp)->av_back->av_forw = (bp)->av_forw; \
	(bp)->av_forw->av_back = (bp)->av_back; \
}
#define	binsheadfree(bp, dp) { \
	(dp)->av_forw->av_back = (bp); \
	(bp)->av_forw = (dp)->av_forw; \
	(dp)->av_forw = (bp); \
	(bp)->av_back = (dp); \
}
#define	binstailfree(bp, dp) { \
	(dp)->av_back->av_forw = (bp); \
	(bp)->av_back = (dp)->av_back; \
	(dp)->av_back = (bp); \
	(bp)->av_forw = (dp); \
}
E 54

D 45
/*
E 20
 * Take a buffer off the free list it's on and
 * mark it as being use (B_BUSY) by a device.
 */
#define	notavail(bp) { \
D 34
	int x = spl6(); \
E 34
I 34
	int x = splbio(); \
E 34
D 20
	(bp)->av_back->av_forw = (bp)->av_forw; \
	(bp)->av_forw->av_back = (bp)->av_back; \
E 20
I 20
	bremfree(bp); \
E 20
	(bp)->b_flags |= B_BUSY; \
	splx(x); \
I 20
}

E 45
#define	iodone	biodone
#define	iowait	biowait

/*
 * Zero out a buffer's data portion.
 */
#define	clrbuf(bp) { \
D 33
	blkclr(bp->b_un.b_addr, bp->b_bcount); \
	bp->b_resid = 0; \
E 33
I 33
	blkclr((bp)->b_un.b_addr, (unsigned)(bp)->b_bcount); \
	(bp)->b_resid = 0; \
E 33
E 20
}
I 42
#define B_CLRBUF	0x1	/* request allocated buffer be cleared */
I 44
#define B_SYNC		0x2	/* do all allocations synchronously */
E 59
I 53
D 62
#endif /* !_BUF_H_ */
E 62
I 62
#endif /* !_SYS_BUF_H_ */
E 62
E 53
E 44
E 42
I 29
D 30

/*
 * Swap two buffer's data areas
 */
#define swapbuf(bp1, bp2) { \
	long bcount = (bp1)->b_bcount; \
	long bufsize = (bp1)->b_bufsize; \
	caddr_t addr = (bp1)->b_un.b_addr; \
	(bp1)->b_bcount = (bp2)->b_bcount; \
	(bp1)->b_bufsize = (bp2)->b_bufsize; \
	(bp1)->b_un.b_addr = (bp2)->b_un.b_addr; \
	(bp2)->b_bcount = bcount; \
	(bp2)->b_bufsize = bufsize; \
	(bp2)->b_un.b_addr = addr; \
}
E 30
E 29
I 23
D 26

#ifdef sun
/*
 * Declarations for buffer space rmaps
 */
struct map *buffermap;
#define BUFMAPSIZE	256

/*
 * "Average" size of a buffer
 * nbuf*AVGBSIZE is total amount of buffer data
 */
#define	AVGBSIZE	2048

/*
 * Unit of buffer space allocation
 */
#define	BUFALLOCSIZE	1024
#endif
E 26
E 23
I 21
D 22

#ifdef KERNEL
struct	buf	bfreelist[BQUEUES];	/* buffer chain headers */
struct	buf	bswlist;	/* free list of swap headers */
struct	buf	*bclnlist;	/* header for list of cleaned pages */
#endif
E 22
E 21
E 19
E 17
E 11
E 1
