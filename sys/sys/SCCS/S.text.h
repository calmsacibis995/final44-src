h50167
s 00001/00011/00067
d D 7.7 90/06/28 22:01:15 bostic 19 18
c new copyright notice
e
s 00001/00001/00077
d D 7.6 90/05/15 22:28:47 mckusick 18 17
c size_t => segsz_t for bostic
e
s 00003/00001/00075
d D 7.5 90/05/10 12:46:32 mckusick 17 16
c merge in support for hp300 from Utah
e
s 00001/00000/00075
d D 7.4 90/02/23 17:05:02 mckusick 16 15
c add field to detect modification
e
s 00016/00005/00059
d D 7.3 89/05/09 16:35:22 mckusick 15 14
c merge in vnodes
e
s 00003/00000/00061
d D 7.2 86/10/13 22:04:23 karels 14 13
c merge in tahoe system
e
s 00001/00001/00060
d D 7.1 86/06/04 23:29:11 mckusick 13 12
c 4.3BSD release version
e
s 00022/00006/00039
d D 6.5 85/11/26 12:38:39 karels 12 11
c move text stats to header file
e
s 00004/00002/00041
d D 6.4 85/11/09 16:38:49 karels 11 10
c keep free list of texts
e
s 00007/00001/00036
d D 6.3 85/06/08 15:09:21 mckusick 10 9
c Add copyright
e
s 00002/00002/00035
d D 6.2 84/12/21 10:30:29 bloom 9 8
c avoid overflow of reference counts
e
s 00000/00000/00037
d D 6.1 83/07/29 06:14:17 sam 8 7
c 4.2 distribution
e
s 00002/00002/00035
d D 4.4 81/03/09 00:27:31 wnj 7 6
c lint
e
s 00002/00001/00035
d D 4.3 81/02/27 00:03:18 wnj 6 5
c go to pointer basis
e
s 00001/00001/00035
d D 4.2 81/02/19 21:42:22 wnj 5 4
c %G%->%E%
e
s 00000/00000/00036
d D 4.1 80/11/09 17:01:46 bill 4 3
c stamp for 4bsd
e
s 00004/00001/00032
d D 3.3 80/07/01 08:17:15 bill 3 2
c various minor fixups pre-split to dev dir
e
s 00001/00001/00032
d D 3.2 80/06/07 03:01:02 bill 2 1
c %H%->%G%
e
s 00033/00000/00000
d D 3.1 80/04/09 16:25:27 bill 1 0
c date and time created 80/04/09 16:25:27 by bill
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%H%	*/
E 2
I 2
D 5
/*	%M%	%I%	%G%	*/
E 5
I 5
D 10
/*	%M%	%I%	%E%	*/
E 10
I 10
/*
D 13
 * Copyright (c) 1982 Regents of the University of California.
E 13
I 13
D 15
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 13
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 15
 *
I 15
D 19
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
E 19
I 19
 * %sccs.include.redist.c%
E 19
 *
E 15
 *	%W% (Berkeley) %G%
 */
E 10
E 5
E 2

/*
 * Text structure.
 * One allocated per pure
 * procedure on swap device.
 * Manipulated by text.c
 */
I 3
D 11
#define	NXDAD	12		/* param.h:MAXTSIZ / dmap.h:DMTEXT */
E 11
I 11
#define	NXDAD	12		/* param.h:MAXTSIZ / vmparam.h:DMTEXT */
E 11

E 3
struct text
{
D 3
	swblk_t	x_daddr;	/* disk address of segment */
E 3
I 3
D 11
	swblk_t	x_daddr[NXDAD];	/* disk addresses of DMTEXT-page segments */
E 11
I 11
	struct	text *x_forw;	/* forward link in free list */
	struct	text **x_back;	/* backward link in free list */
	swblk_t	x_daddr[NXDAD];	/* disk addresses of dmtext-page segments */
E 11
	swblk_t	x_ptdaddr;	/* disk address of page table */
E 3
D 18
	size_t	x_size;		/* size (clicks) */
E 18
I 18
	segsz_t x_size;		/* size (clicks) */
E 18
	struct proc *x_caddr;	/* ptr to linked proc, if loaded */
D 15
	struct inode *x_iptr;	/* inode of prototype */
E 15
I 15
	struct vnode *x_vptr;	/* vnode of prototype */
I 16
	time_t	x_mtime;	/* last time modified */
E 16
E 15
	short	x_rssize;
	short	x_swrss;
D 9
	char	x_count;	/* reference count */
	char	x_ccount;	/* number of loaded references */
E 9
I 9
	short	x_count;	/* reference count */
	short	x_ccount;	/* number of loaded references */
E 9
	char	x_flag;		/* traced, written flags */
	char	x_slptime;
	short	x_poip;		/* page out in progress count */
I 14
#if defined(tahoe)
	short	x_ckey;		/* code cache key */
#endif
E 14
};

#ifdef	KERNEL
D 6
extern	struct text text[];
E 6
I 6
D 7
extern	struct text *text, *textNTEXT;
extern	int ntext;
E 7
I 7
struct	text *text, *textNTEXT;
int	ntext;
E 7
E 6
#endif

D 12
#define	XTRC	01		/* Text may be written, exclusive use */
#define	XWRIT	02		/* Text written into, must swap out */
#define	XLOAD	04		/* Currently being read from file */
#define	XLOCK	010		/* Being swapped in or out */
#define	XWANT	020		/* Wanted for swapping */
#define	XPAGI	040		/* Page in on demand from inode */
E 12
I 12
#define	XTRC	0x01		/* Text may be written, exclusive use */
#define	XWRIT	0x02		/* Text written into, must swap out */
#define	XLOAD	0x04		/* Currently being read from file */
#define	XLOCK	0x08		/* Being swapped in or out */
#define	XWANT	0x10		/* Wanted for swapping */
D 15
#define	XPAGI	0x20		/* Page in on demand from inode */
E 15
I 15
#define	XPAGV	0x20		/* Page in on demand from vnode */
E 15
D 17
#define	XUNUSED	0x40		/* unused since swapped out for cache */
E 17
I 17
#define	XUNUSED	0x40		/* Unused since swapped out for cache */
#define	XCACHED	0x80		/* Cached but not sticky */
E 17

/*
 * Text table statistics
 */
struct xstats {
	u_long	alloc;			/* calls to xalloc */
	u_long	alloc_inuse;		/*	found in use/sticky */
	u_long	alloc_cachehit;		/*	found in cache */
	u_long	alloc_cacheflush;	/*	flushed cached text */
	u_long	alloc_unused;		/*	flushed unused cached text */
	u_long	free;			/* calls to xfree */
	u_long	free_inuse;		/*	still in use/sticky */
	u_long	free_cache;		/*	placed in cache */
	u_long	free_cacheswap;		/*	swapped out to place in cache */
I 17
	u_long	purge;			/* calls to xpurge */
E 17
};
E 12
E 1
