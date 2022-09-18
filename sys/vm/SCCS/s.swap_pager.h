h56839
s 00002/00002/00062
d D 8.1 93/06/11 16:37:15 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00022/00064
d D 7.2 92/05/04 17:14:47 bostic 2 1
c definition of pagerops moves to swap_pager.c where it belongs
e
s 00086/00000/00000
d D 7.1 90/12/05 18:13:30 mckusick 1 0
c adopted from Mike Hibler at Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1990 University of Utah.
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
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef	_SWAP_PAGER_
#define	_SWAP_PAGER_	1

/*
 * In the swap pager, the backing store for an object is organized as an
 * array of some number of "swap blocks".  A swap block consists of a bitmask
 * and some number of contiguous DEV_BSIZE disk blocks.  The minimum size
 * of a swap block is:
 *
 *	max(PAGE_SIZE, dmmin*DEV_BSIZE)			[ 32k currently ]
 *
 * bytes (since the pager interface is page oriented), the maximum size is:
 *
 *	min(#bits(swb_mask)*PAGE_SIZE, dmmax*DEV_BSIZE)	[ 128k currently ]
 *
 * where dmmin and dmmax are left over from the old VM interface.  The bitmask
 * (swb_mask) is used by swap_pager_haspage() to determine if a particular
 * page has actually been written; i.e. the pager copy of the page is valid.
 * All swap blocks in the backing store of an object will be the same size.
 *
 * The reason for variable sized swap blocks is to reduce fragmentation of
 * swap resources.  Whenever possible we allocate smaller swap blocks to
 * smaller objects.  The swap block size is determined from a table of
 * object-size vs. swap-block-size computed at boot time.
 */
typedef	int	sw_bm_t;	/* pager bitmask */

struct	swblock {
	sw_bm_t	 swb_mask;	/* bitmask of valid pages in this block */
	daddr_t	 swb_block;	/* starting disk block for this block */
};
typedef struct swblock	*sw_blk_t;

/*
 * Swap pager private data.
 */
struct swpager {
	vm_size_t    sw_osize;	/* size of object we are backing (bytes) */
	int	     sw_bsize;	/* size of swap blocks (DEV_BSIZE units) */
	int	     sw_nblocks;/* number of blocks in list (sw_blk_t units) */
	sw_blk_t     sw_blocks;	/* pointer to list of swap blocks */
	short	     sw_flags;	/* flags */
	short	     sw_poip;	/* pageouts in progress */
};
typedef struct swpager	*sw_pager_t;

#define	SW_WANTED	0x01
#define SW_NAMED	0x02

D 2
#ifdef KERNEL

void		swap_pager_init();
vm_pager_t	swap_pager_alloc();
void		swap_pager_dealloc();
boolean_t	swap_pager_getpage(), swap_pager_putpage();
boolean_t	swap_pager_haspage();

struct pagerops swappagerops = {
	swap_pager_init,
	swap_pager_alloc,
	swap_pager_dealloc,
	swap_pager_getpage,
	swap_pager_putpage,
	swap_pager_haspage
};

int		swap_pager_iodone();
boolean_t	swap_pager_clean();

#endif

E 2
#endif	/* _SWAP_PAGER_ */
E 1
