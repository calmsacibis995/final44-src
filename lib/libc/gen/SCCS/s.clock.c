h27021
s 00002/00002/00028
d D 8.1 93/06/04 12:00:23 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00013/00020
d D 5.4 90/08/27 20:31:28 bostic 4 3
c rewrite to look like times()
e
s 00001/00011/00032
d D 5.3 90/06/01 14:08:58 bostic 3 2
c new copyright notice
e
s 00009/00008/00034
d D 5.2 90/05/17 15:56:52 karels 2 1
c simplify rounding, KNF
e
s 00042/00000/00000
d D 5.1 89/03/09 17:51:34 bostic 1 0
c date and time created 89/03/09 17:51:34 by bostic
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 4
#include <machine/machlimits.h>
#include <sys/types.h>
E 4
I 4
#include <sys/param.h>
E 4
#include <sys/time.h>
#include <sys/resource.h>

I 4
/*
 * Convert usec to clock ticks; could do (usec * CLK_TCK) / 1000000,
 * but this would overflow if we switch to nanosec.
 */
#define	CONVTCK(r)	(r.tv_sec * CLK_TCK + r.tv_usec / (1000000 / CLK_TCK))

E 4
clock_t
clock()
{
D 4
	struct rusage rusage;
	clock_t val;
E 4
I 4
	struct rusage ru;
E 4

D 4
	if (getrusage(RUSAGE_SELF, &rusage))
E 4
I 4
	if (getrusage(RUSAGE_SELF, &ru))
E 4
D 2
		return((clock_t)-1);
	val = rusage.ru_utime.tv_sec * CLK_TCK;
	val += rusage.ru_stime.tv_sec * CLK_TCK;
	val += rusage.ru_utime.tv_usec / (1000000/CLK_TCK);
	val += rusage.ru_stime.tv_usec / (1000000/CLK_TCK);
	val += (rusage.ru_utime.tv_usec % (1000000/CLK_TCK) +
	    rusage.ru_utime.tv_usec % (1000000/CLK_TCK)) / (1000000/CLK_TCK);
	return(val);
E 2
I 2
		return ((clock_t) -1);
D 4
	val = (rusage.ru_utime.tv_sec + rusage.ru_stime.tv_sec) * CLK_TCK;
	/*
	 * Convert usec to clock ticks; could do (usec * CLK_TCK) / 1000000,
	 * but this would overflow if we switch to nanosec.
	 */
	val += (rusage.ru_utime.tv_usec + rusage.ru_stime.tv_usec) /
		(1000000 / CLK_TCK);
	return (val);
E 4
I 4
	return((clock_t)((CONVTCK(ru.ru_utime) + CONVTCK(ru.ru_stime))));
E 4
E 2
}
E 1
