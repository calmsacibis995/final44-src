h40097
s 00003/00003/00031
d D 8.2 94/01/04 16:16:27 bostic 16 15
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00032
d D 8.1 93/06/02 19:53:15 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00024/00016
d D 7.3 91/02/15 14:28:50 bostic 14 13
c add Berkeley specific copyright notice
e
s 00005/00000/00035
d D 7.2 91/02/05 17:03:39 bostic 13 12
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00001/00034
d D 7.1 86/06/04 23:21:47 mckusick 12 11
c 4.3BSD release version
e
s 00007/00001/00028
d D 6.3 85/06/08 14:56:15 mckusick 11 10
c Add copyright
e
s 00001/00001/00028
d D 6.2 85/03/07 19:39:48 karels 10 9
c NDMAP 16 -> 38
e
s 00000/00000/00029
d D 6.1 83/07/29 06:12:09 sam 9 8
c 4.2 distribution
e
s 00001/00005/00028
d D 4.5 83/05/18 02:11:33 sam 8 7
c stuff for variable sized swap partitions (note addition to bdevsw)
e
s 00002/00000/00031
d D 4.4 82/05/04 13:36:29 sam 7 6
c CAD kludges
e
s 00001/00001/00030
d D 4.3 81/04/23 01:24:17 wnj 6 5
c DMMIN -> 32 so out-clustering and fifo-clustering can be 16
e
s 00001/00001/00030
d D 4.2 81/02/19 21:40:17 wnj 5 4
c %G%->%E%
e
s 00000/00000/00031
d D 4.1 80/11/09 17:00:50 bill 4 3
c stamp for 4bsd
e
s 00001/00000/00030
d D 3.3 80/07/01 08:17:05 bill 3 2
c various minor fixups pre-split to dev dir
e
s 00001/00001/00029
d D 3.2 80/06/07 02:57:13 bill 2 1
c %H%->%G%
e
s 00030/00000/00000
d D 3.1 80/04/09 16:23:46 bill 1 0
c date and time created 80/04/09 16:23:46 by bill
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
D 11
/*	%M%	%I%	%E%	*/
E 11
I 11
D 14
/*
D 12
 * Copyright (c) 1982 Regents of the University of California.
E 12
I 12
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 12
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
/*-
D 15
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
E 14
 *
I 14
 * %sccs.include.redist.c%
 *
E 14
 *	%W% (Berkeley) %G%
 */
E 11
E 5
E 2

I 13
D 16
#ifndef _DMAP_H_
#define	_DMAP_H_
E 16
I 16
#ifndef _SYS_DMAP_H_
#define	_SYS_DMAP_H_
E 16

E 13
/*
D 14
 * Definitions for the mapping of vitual swap
 * space to the physical swap area - the disk map.
E 14
I 14
 * Definitions for the mapping of vitual swap space to the physical swap
 * area - the disk map.
E 14
 */
I 14
#define	NDMAP	38		/* size of the swap area map */
E 14

D 10
#define	NDMAP 		16	/* size of the swap area map */
E 10
I 10
D 14
#define	NDMAP 		38	/* size of the swap area map */
E 10
D 6
#define	DMMIN 		16	/* the initial block size in clicks */
E 6
I 6
D 8
#define	DMMIN 		32	/* the initial block size in clicks */
I 7
#ifndef DMMAX
E 7
E 6
#define	DMMAX		1024	/* max block size alloc on drum = .5M byte */
I 7
#endif
E 7
I 3
#define	DMTEXT		1024	/* size of blocks of pure text = .5M byte */
E 8
E 3

struct	dmap
{
	swblk_t	dm_size;	/* current size used by process */
	swblk_t	dm_alloc;	/* amount of physical swap space allocated */
	swblk_t	dm_map[NDMAP];	/* first disk block number in each chunk */
E 14
I 14
struct dmap {
	swblk_t dm_size;	/* current size used by process */
	swblk_t dm_alloc;	/* amount of physical swap space allocated */
	swblk_t dm_map[NDMAP];	/* first disk block number in each chunk */
E 14
};
#ifdef KERNEL
D 14
struct	dmap zdmap;
I 8
int	dmmin, dmmax, dmtext;
E 14
I 14
struct dmap zdmap;
int dmmin, dmmax, dmtext;
E 14
E 8
#endif

D 14
/*
 * The following structure is that ``returned''
 * from a call to vstodb().
 */
struct	dblock
{
	swblk_t	db_base;	/* base of physical contig drum block */
	swblk_t	db_size;	/* size of block */
E 14
I 14
/* The following structure is that ``returned'' from a call to vstodb(). */
struct dblock {
	swblk_t db_base;	/* base of physical contig drum block */
	swblk_t db_size;	/* size of block */
E 14
};
I 13
D 14

E 14
D 16
#endif	/* !_DMAP_H_ */
E 16
I 16
#endif	/* !_SYS_DMAP_H_ */
E 16
E 13
E 1
