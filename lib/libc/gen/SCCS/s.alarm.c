h12501
s 00002/00002/00031
d D 8.1 93/06/04 12:00:14 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00030
d D 5.5 91/02/23 19:49:32 donn 7 6
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00030
d D 5.4 90/06/01 14:08:50 bostic 6 5
c new copyright notice
e
s 00014/00003/00027
d D 5.3 88/08/02 18:11:34 bostic 5 4
c add Berkeley specific header, written for compatibility
e
s 00002/00002/00028
d D 5.2 86/03/09 19:44:11 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00021
d D 5.1 85/06/05 12:01:18 mckusick 3 2
c Add copyright
e
s 00002/00000/00020
d D 4.2 84/03/22 09:52:53 ralph 2 1
c round up seconds so it doesn't return zero if there's time left.
e
s 00020/00000/00000
d D 4.1 83/06/10 21:58:57 sam 1 0
c date and time created 83/06/10 21:58:57 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*
D 8
 * Copyright (c) 1983 Regents of the University of California.
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
 */

D 4
#ifndef lint
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 5
#endif LIBC_SCCS and not lint
E 5
I 5
#endif /* LIBC_SCCS and not lint */
E 5
E 4
E 3

/*
 * Backwards compatible alarm.
 */
#include <sys/time.h>
I 7
#include <unistd.h>
E 7

I 7
unsigned int
E 7
alarm(secs)
D 7
	int secs;
E 7
I 7
	unsigned int secs;
E 7
{
	struct itimerval it, oitv;
	register struct itimerval *itp = &it;

	timerclear(&itp->it_interval);
	itp->it_value.tv_sec = secs;
	itp->it_value.tv_usec = 0;
	if (setitimer(ITIMER_REAL, itp, &oitv) < 0)
		return (-1);
I 2
	if (oitv.it_value.tv_usec)
		oitv.it_value.tv_sec++;
E 2
	return (oitv.it_value.tv_sec);
}
E 1
