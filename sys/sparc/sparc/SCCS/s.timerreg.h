h28816
s 00002/00002/00062
d D 8.1 93/06/11 15:17:33 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00062
d D 7.4 93/04/20 23:45:01 torek 4 3
c spelling
e
s 00001/00001/00063
d D 7.3 92/10/11 12:57:28 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00059
d D 7.2 92/07/21 16:54:43 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00059/00000/00000
d D 7.1 92/07/13 00:44:42 torek 1 0
c date and time created 92/07/13 00:44:42 by torek
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
 * from: $Header: timerreg.h,v 1.6 92/07/07 04:56:09 leres Exp $ (LBL)
E 4
I 4
 * from: $Header: timerreg.h,v 1.7 92/11/26 03:05:09 leres Exp $ (LBL)
E 4
 */

/*
 * Sun-4c counter/timer registers.  The timers are implemented within
 * the cache chip (!).  The counter and limit fields below could be
 * defined as:
 *
 *	struct {
 *		u_int	t_limit:1,	// limit reached
 *			t_usec:21,	// counter value in microseconds
 *			t_mbz:10;	// always zero
 *	};
 *
 * but this is more trouble than it is worth.
 *
 * These timers work in a rather peculiar fashion.  Most clock counters
 * run to 0 (as, e.g., on the VAX, where the ICR counts up to 0 from a
 * large unsigned number).  On the Sun-4c, it counts up to a limit.  But
 * for some reason, when it reaches the limit, it resets to 1, not 0.
 * Thus, if the limit is set to 4, the counter counts like this:
 *
 *	1, 2, 3, 1, 2, 3, ...
 *
 * and if we want to divide by N we must set the limit register to N+1.
 */
#ifndef LOCORE
struct timer {
	int	t_counter;		/* counter reg */
	int	t_limit;		/* limit reg */
};

struct timerreg {
	struct	timer t_c10;		/* counter that interrupts at ipl 10 */
	struct	timer t_c14;		/* counter that interrupts at ipl 14 */
};
#endif

#define	TMR_LIMIT	0x80000000	/* counter reached its limit */
#define	TMR_SHIFT	10		/* shift to obtain microseconds */
#define	TMR_MASK	0x1fffff	/* 21 bits */

/* Compute a limit that causes the timer to fire every n microseconds. */
#define	tmr_ustolim(n)	(((n) + 1) << TMR_SHIFT)

D 3
#include "vaddrs.h"
E 3
I 3
#include <sparc/sparc/vaddrs.h>
E 3
#define	TIMERREG	((volatile struct timerreg *)TIMERREG_VA)
E 1
