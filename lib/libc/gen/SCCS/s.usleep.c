h15732
s 00002/00002/00071
d D 8.1 93/06/04 12:07:09 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00070
d D 5.6 91/02/23 19:50:15 donn 7 6
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00070
d D 5.5 90/06/01 14:17:41 bostic 6 5
c new copyright notice
e
s 00030/00019/00051
d D 5.4 89/09/18 12:47:17 bostic 5 4
c remove last vestige of AT&T code; it was really gone long ago
e
s 00002/00001/00068
d D 5.3 87/09/30 12:15:29 bostic 4 3
c long/int bug; bug report 4.3BSD/lib/28
e
s 00002/00002/00067
d D 5.2 86/03/09 20:01:08 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00007/00001/00062
d D 5.1 85/06/05 12:43:23 mckusick 2 1
c Add copyright
e
s 00063/00000/00000
d D 1.1 85/03/14 17:56:37 serge 1 0
c date and time created 85/03/14 17:56:37 by serge
e
u
U
t
T
I 2
/*
D 5
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
 */

E 2
I 1
D 3
#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
D 3
#endif not lint
E 3
I 3
D 5
#endif LIBC_SCCS and not lint
E 5
I 5
#endif /* LIBC_SCCS and not lint */
E 5
E 3
E 2

#include <sys/time.h>
D 5
#include <signal.h>
E 5
I 5
#include <sys/signal.h>
I 7
#include <unistd.h>
E 7
E 5

D 5
#define USPS	1000000		/* number of microseconds in a second */
#define TICK	10000		/* system clock resolution in microseconds */
E 5
I 5
#define	TICK	10000		/* system clock resolution in microseconds */
#define	USPS	1000000		/* number of microseconds in a second */
E 5

#define	setvec(vec, a) \
	vec.sv_handler = a; vec.sv_mask = vec.sv_onstack = 0

static int ringring;

I 7
void
E 7
D 5
usleep(n)
	unsigned n;
E 5
I 5
usleep(useconds)
	unsigned int useconds;
E 5
{
D 4
	int sleepx(), omask;
E 4
I 4
D 5
	int sleepx();
	long omask;
E 5
I 5
	register struct itimerval *itp;
E 5
E 4
	struct itimerval itv, oitv;
D 5
	register struct itimerval *itp = &itv;
E 5
	struct sigvec vec, ovec;
I 5
	long omask;
D 7
	void sleephandler();
E 7
I 7
	static void sleephandler();
E 7
E 5

D 5
	if (n == 0)
E 5
I 5
	itp = &itv;
	if (!useconds)
E 5
		return;
	timerclear(&itp->it_interval);
	timerclear(&itp->it_value);
	if (setitimer(ITIMER_REAL, itp, &oitv) < 0)
		return;
D 5
	itp->it_value.tv_sec = n / USPS;
	itp->it_value.tv_usec = n % USPS;
E 5
I 5
	itp->it_value.tv_sec = useconds / USPS;
	itp->it_value.tv_usec = useconds % USPS;
E 5
	if (timerisset(&oitv.it_value)) {
		if (timercmp(&oitv.it_value, &itp->it_value, >)) {
			oitv.it_value.tv_sec -= itp->it_value.tv_sec;
			oitv.it_value.tv_usec -= itp->it_value.tv_usec;
			if (oitv.it_value.tv_usec < 0) {
				oitv.it_value.tv_usec += USPS;
				oitv.it_value.tv_sec--;
			}
		} else {
			itp->it_value = oitv.it_value;
			oitv.it_value.tv_sec = 0;
			oitv.it_value.tv_usec = 2 * TICK;
		}
	}
D 5
	setvec(vec, sleepx);
E 5
I 5
	setvec(vec, sleephandler);
E 5
	(void) sigvec(SIGALRM, &vec, &ovec);
	omask = sigblock(sigmask(SIGALRM));
	ringring = 0;
	(void) setitimer(ITIMER_REAL, itp, (struct itimerval *)0);
	while (!ringring)
		sigpause(omask &~ sigmask(SIGALRM));
	(void) sigvec(SIGALRM, &ovec, (struct sigvec *)0);
	(void) sigsetmask(omask);
	(void) setitimer(ITIMER_REAL, &oitv, (struct itimerval *)0);
}

D 5
static
sleepx()
E 5
I 5
static void
sleephandler()
E 5
{
D 5

E 5
	ringring = 1;
}
E 1
