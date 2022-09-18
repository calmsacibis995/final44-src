h05739
s 00002/00002/00025
d D 8.1 93/06/10 22:29:35 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00000/00000
d D 7.1 92/12/13 03:50:17 akito 1 0
c date and time created 92/12/13 03:50:17 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/types.h>

/*
 * The hz hardware interval timer.
 * We update the events relating to real time.
 * If this timer is also being used to gather statistics,
 * we run through the statistics gathering routine as well.
 */
/*ARGSUSED*/
hardclock(pc, ps)
	caddr_t pc;
	int ps;
{
}
E 1
