h29026
s 00004/00000/00059
d D 7.4 92/02/20 15:18:16 sklower 6 5
c mtpr.h is vax and tahoe specific, have net files which need it for spl()
c include cpu.h instead.
e
s 00001/00011/00058
d D 7.3 90/06/28 22:07:02 bostic 5 4
c new copyright notice
e
s 00017/00003/00052
d D 7.2 88/09/27 21:30:31 bostic 4 3
c add Berkeley specific copyright notice
e
s 00001/00001/00054
d D 7.1 88/05/21 18:35:10 karels 3 2
c bring up to revision 7 for tahoe release
e
s 00009/00001/00046
d D 1.2 87/03/13 10:49:53 karels 2 1
c move cache key defines to cpu.h, add counters
e
s 00047/00000/00000
d D 1.1 86/12/08 20:05:32 karels 1 0
c date and time created 86/12/08 20:05:32 by karels
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1986 Regents of the University of California.
E 3
I 3
D 4
 * Copyright (c) 1986, 1988 Regents of the University of California.
E 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * Copyright (c) 1986, 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
D 5
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Assorted definitions unique to TAHOE CPU support.
 */

#define	uncache(v)	mtpr(PDCS, (caddr_t)(v))
#define	movow(a,w)	_movow((u_short *)(a), (u_short)(w))
#define	movob(a,b)	_movob((u_char *)(a), (u_char)(b))

#define	resettodr()	/* no todr to set */

I 2
#define	MAXCKEY	255		/* maximal allowed code key */
#define	MAXDKEY	255		/* maximal allowed data key */
#define	NCKEY	(MAXCKEY+1)	/* # code keys, including 0 (reserved) */
#define	NDKEY	(MAXDKEY+1)	/* # data keys, including 0 (reserved) */

E 2
#ifndef LOCORE
#ifdef KERNEL
char	ckey_cache[NCKEY];	/* 1 =>'s key i may be in code cache */
short	ckey_cnt[NCKEY];	/* code key reference count */
char	dkey_cache[NDKEY];	/* 1 =>'s key i may be in data cache */
short	dkey_cnt[NDKEY];	/* data key reference count */
#endif

/*
 * Statistics maintained for code and
 * data cache key allocations algorithms.
 */
struct	keystats {
I 2
	long	ks_avail;	/* number of keys currently unallocated */
	long	ks_dirty;	/* number of keys currently waiting for purge */
E 2
	long	ks_allocs;	/* number of keys allocated */
D 2
	long	ks_free;	/* key allocated from free slot */
E 2
I 2
	long	ks_allocfree;	/* key allocated from free slot */
E 2
	long	ks_norefs;	/* key marked in use, but refcnt 0 */
	long	ks_taken;	/* key taken from single process */
	long	ks_shared;	/* key taken from multiple processes */
I 2
	long	ks_inval;	/* number of times keys exchanged */
E 2
};
#endif

long	*user_psl;		/* user mode psl for ast's */
int	intenable;		/* interrupts enable startup flag */
int	clk_enable;		/* clock enable startup flag */

/*
 * Enable realtime clock.
 */
#define	enablertclock()	(clk_enable = 1)
I 6

#ifndef _MTPR_H_
#include "mtpr.h"
#endif /* !_MTPR_H_ */
E 6
E 1
