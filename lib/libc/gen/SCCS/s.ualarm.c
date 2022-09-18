h22214
s 00002/00002/00037
d D 8.1 93/06/04 12:06:56 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00038
d D 5.5 91/02/23 19:50:13 donn 6 5
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00037
d D 5.4 90/06/01 14:17:31 bostic 5 4
c new copyright notice
e
s 00014/00003/00034
d D 5.3 88/08/02 18:49:33 bostic 4 3
c written by Serge Granik; add Berkeley specific header
e
s 00002/00002/00035
d D 5.2 86/03/09 20:00:55 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00028
d D 5.1 85/06/05 12:42:53 mckusick 2 1
c Add copyright
e
s 00029/00000/00000
d D 1.1 85/03/14 17:52:57 serge 1 0
c date and time created 85/03/14 17:52:57 by serge
e
u
U
t
T
I 1
D 2
/* %W%	(Berkeley)	%G% */
E 2
I 2
/*
D 7
 * Copyright (c) 1985 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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
 */

D 3
#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
D 4
#endif LIBC_SCCS and not lint
E 4
I 4
#endif /* LIBC_SCCS and not lint */
E 4
E 3
E 2

#include <sys/time.h>
I 6
#include <unistd.h>
E 6

#define	USPS	1000000		/* # of microseconds in a second */

/*
 * Generate a SIGALRM signal in ``usecs'' microseconds.
 * If ``reload'' is non-zero, keep generating SIGALRM
 * every ``reload'' microseconds after the first signal.
 */
unsigned
ualarm(usecs, reload)
	register unsigned usecs;
	register unsigned reload;
{
	struct itimerval new, old;

	new.it_interval.tv_usec = reload % USPS;
	new.it_interval.tv_sec = reload / USPS;
	
	new.it_value.tv_usec = usecs % USPS;
	new.it_value.tv_sec = usecs / USPS;

	if (setitimer(ITIMER_REAL, &new, &old) == 0)
		return (old.it_value.tv_sec * USPS + old.it_value.tv_usec);
	/* else */
		return (-1);
}
E 1
