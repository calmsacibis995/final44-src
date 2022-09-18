h23805
s 00002/00002/00122
d D 8.1 93/06/11 15:16:09 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00003/00094
d D 7.4 93/04/27 07:32:22 torek 4 3
c add cacheinfo, needed for SS2; add cachestats
e
s 00002/00002/00095
d D 7.3 93/04/20 21:20:48 torek 3 2
c spelling
e
s 00005/00000/00092
d D 7.2 92/07/21 16:54:20 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00092/00000/00000
d D 7.1 92/07/13 00:44:29 torek 1 0
c date and time created 92/07/13 00:44:29 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: cache.h,v 1.5 92/06/17 05:21:57 torek Exp $
E 3
I 3
D 4
 * from: $Header: cache.h,v 1.6 92/11/26 03:04:46 torek Exp $
E 4
I 4
 * from: $Header: cache.h,v 1.7 93/04/27 14:31:16 torek Exp $
E 4
E 3
 */

/*
 * Sun-4 and Sun-4c virtual address cache.
 *
 * Sun-4 virtual caches come in two flavors, write-through (Sun-4c)
 * and write-back (Sun-4).  The write-back caches are much faster
 * but require a bit more care.
 *
 * VAC_NONE is not actually used now, but if someone builds a physical
 * cache Sun-4 (or, more likely, a virtual index/physical tag cache)
 * everything will work (after pulling out the #ifdef notdef's: grep
 * for VAC_NONE to find them).
 */
enum vactype { VAC_NONE, VAC_WRITETHROUGH, VAC_WRITEBACK };

D 4
extern enum vactype vactype;
E 4
I 4
extern enum vactype vactype;	/* XXX  move into cacheinfo struct */
E 4

/*
 * Cache tags can be written in control space, and must be set to 0
 * (or invalid anyway) before turning on the cache.  The tags are
 * addressed as an array of 32-bit structures of the form:
 *
 *	struct cache_tag {
 *		u_int	:7,		(unused; must be zero)
 *			ct_cid:3,	(context ID)
 *			ct_w:1,		(write flag from PTE)
 *			ct_s:1,		(supervisor flag from PTE)
 *			ct_v:1,		(set => cache entry is valid)
 *			:3,		(unused; must be zero)
 *			ct_tid:14,	(cache tag ID)
 *			:2;		(unused; must be zero)
 *	};
 *
D 4
 * The cache sees virtual addresses as:
E 4
I 4
 * The SPARCstation 1 cache sees virtual addresses as:
E 4
 *
 *	struct cache_va {
 *		u_int	:2,		(unused; probably copies of va_tid<13>)
 *			cva_tid:14,	(tag ID)
 *			cva_line:12,	(cache line number)
 *			cva_byte:4;	(byte in cache line)
 *	};
 *
I 4
 * (The SS2 cache is similar but has half as many lines, each twice as long.)
 *
E 4
 * Note that, because the 12-bit line ID is `wider' than the page offset,
 * it is possible to have one page map to two different cache lines.
 * This can happen whenever two different physical pages have the same bits
 * in the part of the virtual address that overlaps the cache line ID, i.e.,
 * bits <15:12>.  In order to prevent cache duplication, we have to
 * make sure that no one page has more than one virtual address where
 * (va1 & 0xf000) != (va2 & 0xf000).  (The cache hardware turns off ct_v
 * when a cache miss occurs on a write, i.e., if va1 is in the cache and
 * va2 is not, and you write to va2, va1 goes out of the cache.  If va1
 * is in the cache and va2 is not, reading va2 also causes va1 to become
 * uncached, and the [same] data is then read from main memory into the
 * cache.)
 *
 * The other alternative, of course, is to disable caching of aliased
 * pages.  (In a few cases this might be faster anyway, but we do it
 * only when forced.)
 *
 * THE CURRENT VM CODE DOES NOT ALLOW US TO SPECIFY PREFERRED VIRTUAL
 * ADDRESSES ... THIS MUST BE FIXED!
 */

#define	CACHE_ALIAS_DISTANCE	(256 * 1024)	/* 256 kbytes */

/*
 * True iff a1 and a2 are `bad' aliases (will cause cache duplication).
 */
#define	BADALIAS(a1, a2) (((int)(a1) ^ (int)(a2)) & 0xf000)

/*
 * Routines for dealing with the cache.
 */
void	cache_enable __P((void));		/* turn it on */
void	cache_flush_context __P((void));	/* flush current context */
void	cache_flush_segment __P((int vseg));	/* flush seg in cur ctx */
void	cache_flush_page __P((int va));		/* flush page in cur ctx */
void	cache_flush __P((caddr_t base, u_int len));/* flush region */
I 4

/*
 * Cache control information.
 */
struct cacheinfo {
	int	c_totalsize;		/* total size, in bytes */
	int	c_enabled;		/* true => cache is enabled */
	int	c_hwflush;		/* true => have hardware flush */
	int	c_linesize;		/* line size, in bytes */
	int	c_l2linesize;		/* log2(linesize) */
};
extern struct cacheinfo cacheinfo;

/*
 * Cache control statistics.
 */
struct cachestats {
	int	cs_npgflush;		/* # page flushes */
	int	cs_nsgflush;		/* # seg flushes */
	int	cs_ncxflush;		/* # context flushes */
	int	cs_nraflush;		/* # range flushes */
#ifdef notyet
	int	cs_ra[65];		/* pages/range */
#endif
};
E 4
E 1
