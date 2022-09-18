h33595
s 00007/00006/00198
d D 8.2 93/10/30 22:32:23 torek 10 9
c work around ss1+ hardware bug by moving cache enable to after autoconfig
e
s 00002/00002/00202
d D 8.1 93/07/19 18:33:49 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00202
d D 7.7 93/07/19 18:18:07 torek 8 6
c clarify cache init (AC_CACHETAGS is too big for signed int)
e
s 00002/00002/00202
d R 8.1 93/06/11 15:16:06 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00035/00025/00169
d D 7.6 93/05/05 02:36:20 torek 6 5
c add hardware assist for segment and context flush;
c just call seg/ctx flush code from range flush, as needed
e
s 00062/00027/00132
d D 7.5 93/04/27 07:34:03 torek 5 4
c preliminary SS2 support (seems to work)
e
s 00003/00003/00156
d D 7.4 93/04/20 21:20:14 torek 4 3
c spelling; ctlreg.h moves
e
s 00005/00005/00154
d D 7.3 92/10/11 12:57:06 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00154
d D 7.2 92/07/21 16:54:20 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00154/00000/00000
d D 7.1 92/07/13 00:44:29 torek 1 0
c date and time created 92/07/13 00:44:29 by torek
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: cache.c,v 1.5 92/06/17 05:21:56 torek Exp $ (LBL)
E 4
I 4
D 5
 * from: $Header: cache.c,v 1.7 92/11/26 03:04:46 torek Exp $ (LBL)
E 5
I 5
D 6
 * from: $Header: cache.c,v 1.8 93/04/27 14:33:36 torek Exp $ (LBL)
E 6
I 6
D 8
 * from: $Header: cache.c,v 1.9 93/05/05 09:16:17 torek Exp $ (LBL)
E 8
I 8
D 10
 * from: $Header: cache.c,v 1.10 93/07/18 06:23:51 torek Exp $ (LBL)
E 10
I 10
 * from: $Header: cache.c,v 1.12 93/10/31 05:27:47 torek Exp $ (LBL)
E 10
E 8
E 6
E 5
E 4
 */

/*
 * Cache routines.
I 5
 *
 * TODO:
D 6
 *	- fill in hardware assist for context and segment flush
E 6
 *	- rework range flush
E 5
 */

D 3
#include "param.h"
E 3
I 3
#include <sys/param.h>
E 3

I 4
#include <machine/ctlreg.h>
E 4
D 3
#include "machine/pte.h"
E 3
I 3
#include <machine/pte.h>
E 3

D 3
#include "asm.h"
#include "cache.h"
#include "ctlreg.h"
E 3
I 3
#include <sparc/sparc/asm.h>
#include <sparc/sparc/cache.h>
D 4
#include <sparc/sparc/ctlreg.h>
E 4
E 3

enum vactype vactype;
I 5
struct cachestats cachestats;
E 5

/*
 * Enable the cache.
 * We need to clear out the valid bits first.
 */
void
cache_enable()
{
D 5
	register int i;
E 5
I 5
D 8
	register int i, lim, ls;
E 8
I 8
D 10
	register u_int i, lim, ls;
E 10
I 10
	register u_int i, lim, ls, ts;
E 10
E 8
E 5

D 5
	for (i = AC_CACHETAGS; i < AC_CACHETAGS + 4096 * 4; i += 4)
E 5
I 5
D 10
	i = AC_CACHETAGS;
	lim = i + cacheinfo.c_totalsize;
E 10
	ls = cacheinfo.c_linesize;
D 10
	for (; i < lim; i += ls)
E 10
I 10
	ts = cacheinfo.c_totalsize;
	for (i = AC_CACHETAGS, lim = i + ts; i < lim; i += ls)
E 10
E 5
		sta(i, ASI_CONTROL, 0);

D 5
	vactype = VAC_WRITETHROUGH;		/* XXX must be set per cpu */
E 5
	stba(AC_SYSENABLE, ASI_CONTROL,
	    lduba(AC_SYSENABLE, ASI_CONTROL) | SYSEN_CACHE);
I 5
	cacheinfo.c_enabled = 1;
E 5
D 10
	printf("cache enabled\n");
E 10
I 10

	printf("%d byte (%d/line) write-through %cw flush cache enabled\n",
	    ts, ls, cacheinfo.c_hwflush ? 'h' : 's');
E 10
}


/*
 * Flush the current context from the cache.
 *
 * This is done by writing to each cache line in the `flush context'
D 5
 * address space.  Cache lines are 16 bytes, hence the declaration of `p'.
E 5
I 5
D 6
 * address space.
E 6
I 6
 * address space (or, for hardware flush, once to each page in the
 * hardware flush space, for all cache pages).
E 6
E 5
 */
void
cache_flush_context()
{
D 5
	register int i;
	register char (*p)[16];
E 5
I 5
D 6
	register int i, ls;
E 6
	register char *p;
I 6
	register int i, ls;
E 6
E 5

D 5
	p = 0;
	for (i = 0x1000; --i >= 0; p++)
E 5
I 5
	cachestats.cs_ncxflush++;
D 6
	ls = cacheinfo.c_linesize;
	i = cacheinfo.c_totalsize >> cacheinfo.c_l2linesize;
	for (p = 0; --i >= 0; p += ls)
E 5
		sta(p, ASI_FLUSHCTX, 0);
E 6
I 6
	p = (char *)0;	/* addresses 0..cacheinfo.c_totalsize will do fine */
	if (cacheinfo.c_hwflush) {
		ls = NBPG;
		i = cacheinfo.c_totalsize >> PGSHIFT;
		for (; --i >= 0; p += ls)
			sta(p, ASI_HWFLUSHCTX, 0);
	} else {
		ls = cacheinfo.c_linesize;
		i = cacheinfo.c_totalsize >> cacheinfo.c_l2linesize;
		for (; --i >= 0; p += ls)
			sta(p, ASI_FLUSHCTX, 0);
	}
E 6
}

/*
 * Flush the given virtual segment from the cache.
 *
 * This is also done by writing to each cache line, except that
 * now the addresses must include the virtual segment number, and
 * we use the `flush segment' space.
I 6
 *
 * Again, for hardware, we just write each page (in hw-flush space).
E 6
 */
void
cache_flush_segment(vseg)
	register int vseg;
{
D 5
	register int i;
	register char (*p)[16];
E 5
I 5
	register int i, ls;
	register char *p;
E 5

D 5
	p = (char (*)[16])VSTOVA(vseg);
	for (i = 0x1000; --i >= 0; p++)
E 5
I 5
	cachestats.cs_nsgflush++;
D 6
	ls = cacheinfo.c_linesize;
	i = cacheinfo.c_totalsize >> cacheinfo.c_l2linesize;
	for (p = (char *)VSTOVA(vseg); --i >= 0; p += ls)
E 5
		sta(p, ASI_FLUSHSEG, 0);
E 6
I 6
	p = (char *)VSTOVA(vseg);	/* seg..seg+sz rather than 0..sz */
	if (cacheinfo.c_hwflush) {
		ls = NBPG;
		i = cacheinfo.c_totalsize >> PGSHIFT;
		for (; --i >= 0; p += ls)
			sta(p, ASI_HWFLUSHSEG, 0);
	} else {
		ls = cacheinfo.c_linesize;
		i = cacheinfo.c_totalsize >> cacheinfo.c_l2linesize;
		for (; --i >= 0; p += ls)
			sta(p, ASI_FLUSHSEG, 0);
	}
E 6
}

/*
 * Flush the given virtual page from the cache.
 * (va is the actual address, and must be aligned on a page boundary.)
 * Again we write to each cache line.
 */
void
cache_flush_page(va)
	int va;
{
D 5
	register int i;
	register char (*p)[16];
E 5
I 5
	register int i, ls;
	register char *p;
E 5

D 5
	p = (char (*)[16])va;
	for (i = NBPG >> 4; --i >= 0; p++)
		sta(p, ASI_FLUSHPG, 0);
E 5
I 5
	cachestats.cs_npgflush++;
	p = (char *)va;
	if (cacheinfo.c_hwflush)
		sta(p, ASI_HWFLUSHPG, 0);
	else {
		ls = cacheinfo.c_linesize;
		i = NBPG >> cacheinfo.c_l2linesize;
		for (; --i >= 0; p += ls)
			sta(p, ASI_FLUSHPG, 0);
	}
E 5
}

/*
 * Flush a range of virtual addresses (in the current context).
 * The first byte is at (base&~PGOFSET) and the last one is just
 * before byte (base+len).
 *
 * We choose the best of (context,segment,page) here.
 */
void
cache_flush(base, len)
	caddr_t base;
	register u_int len;
{
D 5
	register int i, baseoff;
	register char (*p)[16];
E 5
I 5
	register int i, ls, baseoff;
	register char *p;
E 5

	/*
	 * Figure out how much must be flushed.
	 *
	 * If we need to do 16 pages, we can do a segment in the same
	 * number of loop iterations.  We can also do the context.  If
	 * we would need to do two segments, do the whole context.
	 * This might not be ideal (e.g., fsck likes to do 65536-byte
	 * reads, which might not necessarily be aligned).
	 *
	 * We could try to be sneaky here and use the direct mapping
	 * to avoid flushing things `below' the start and `above' the
	 * ending address (rather than rounding to whole pages and
	 * segments), but I did not want to debug that now and it is
	 * not clear it would help much.
I 5
	 *
	 * (XXX the magic number 16 is now wrong, must review policy)
E 5
	 */
	baseoff = (int)base & PGOFSET;
	i = (baseoff + len + PGOFSET) >> PGSHIFT;
I 5

	cachestats.cs_nraflush++;
#ifdef notyet
	cachestats.cs_ra[min(i, MAXCACHERANGE)]++;
#endif

D 6
	ls = cacheinfo.c_linesize;
E 6
E 5
	if (i <= 15) {
		/* cache_flush_page, for i pages */
D 5
		p = (char (*)[16])((int)base & ~baseoff);
		for (i <<= PGSHIFT - 4; --i >= 0; p++)
			sta(p, ASI_FLUSHPG, 0);
E 5
I 5
		p = (char *)((int)base & ~baseoff);
		if (cacheinfo.c_hwflush) {
			for (; --i >= 0; p += NBPG)
				sta(p, ASI_HWFLUSHPG, 0);
		} else {
I 6
			ls = cacheinfo.c_linesize;
E 6
			i <<= PGSHIFT - cacheinfo.c_l2linesize;
			for (; --i >= 0; p += ls)
				sta(p, ASI_FLUSHPG, 0);
		}
E 5
		return;
	}
	baseoff = (u_int)base & SGOFSET;
	i = (baseoff + len + SGOFSET) >> SGSHIFT;
D 6
	if (i == 1) {
		/* cache_flush_segment */
D 5
		p = (char (*)[16])((int)base & ~baseoff);
		for (i = 0x1000; --i >= 0; p++)
E 5
I 5
		p = (char *)((int)base & ~baseoff);
		i = cacheinfo.c_totalsize >> cacheinfo.c_l2linesize;
		for (; --i >= 0; p += ls)
E 5
			sta(p, ASI_FLUSHSEG, 0);
		return;
	}
	/* cache_flush_context */
D 5
	p = 0;
	for (i = 0x1000; --i >= 0; p++)
E 5
I 5
	i = cacheinfo.c_totalsize >> cacheinfo.c_l2linesize;
	for (p = 0; --i >= 0; p += ls)
E 5
		sta(p, ASI_FLUSHCTX, 0);
E 6
I 6
	if (i == 1)
		cache_flush_segment(VA_VSEG(base));
	else
		cache_flush_context();
E 6
}
E 1
