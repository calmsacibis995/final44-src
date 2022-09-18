h36653
s 00002/00002/00069
d D 8.1 93/06/04 12:05:34 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00003/00065
d D 5.6 91/02/23 19:50:06 donn 13 12
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00067
d D 5.5 90/06/01 14:16:12 bostic 12 11
c new copyright notice
e
s 00031/00020/00047
d D 5.4 89/09/18 12:43:17 bostic 11 10
c remove last vestige of AT&T code; it was really gone long ago
e
s 00002/00001/00065
d D 5.3 87/09/30 12:16:40 bostic 10 9
c long/int bug; bug report 4.3BSD/lib/27
e
s 00002/00002/00064
d D 5.2 86/03/09 19:57:06 donn 9 8
c added LIBC_SCCS condition for sccs ids
e
s 00007/00001/00059
d D 5.1 85/05/30 10:51:09 dist 8 7
c Add copyright
e
s 00003/00004/00057
d D 4.7 84/12/08 21:31:58 karels 7 6
c minor race problem
e
s 00001/00001/00060
d D 4.6 83/09/11 21:57:10 karels 6 5
c minor bugfix (avoid unlikely race)
e
s 00009/00014/00052
d D 4.5 83/08/14 16:15:12 karels 5 4
c don't use setjmp/longjmp, or problems if an interrupt routine
c does a lonjmp before the timer goes off.
e
s 00004/00002/00062
d D 4.4 83/07/01 18:33:00 sam 4 3
c include fixes
e
s 00008/00005/00056
d D 4.3 83/06/12 01:28:34 sam 3 2
c beware of signals other than SIGALRM interrupting sigpause; 
c also when alarm overlaps previous, use 1 sec reset value to allow time to return
e
s 00038/00018/00023
d D 4.2 83/06/10 22:43:32 sam 2 1
c modernized
e
s 00041/00000/00000
d D 4.1 80/12/21 16:40:06 wnj 1 0
c date and time created 80/12/21 16:40:06 by wnj
e
u
U
t
T
I 8
/*
D 11
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
D 14
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 12
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 11
 */

E 8
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 4
/*	%W% (Berkeley) %G%	*/
E 4
I 4
D 9
#ifndef lint
E 9
I 9
#if defined(LIBC_SCCS) && !defined(lint)
E 9
static char sccsid[] = "%W% (Berkeley) %G%";
D 8
#endif
E 8
I 8
D 9
#endif not lint
E 9
I 9
D 11
#endif LIBC_SCCS and not lint
E 11
I 11
#endif /* LIBC_SCCS and not lint */
E 11
E 9
E 8
E 4

I 4
#include <sys/time.h>
E 4
E 2
D 11
#include <signal.h>
E 11
I 11
#include <sys/signal.h>
I 13
#include <unistd.h>
E 13
E 11
D 5
#include <setjmp.h>
E 5
I 2
D 4
#include <time.h>
E 4
E 2

D 5
static jmp_buf jmp;

E 5
I 2
D 7
#define	mask(s)	(1<<((s)-1))
E 7
#define	setvec(vec, a) \
	vec.sv_handler = a; vec.sv_mask = vec.sv_onstack = 0

I 5
static int ringring;

I 13
unsigned int
E 13
E 5
E 2
D 11
sleep(n)
D 2
unsigned n;
E 2
I 2
	unsigned n;
E 11
I 11
sleep(seconds)
	unsigned int seconds;
E 11
E 2
{
D 2
	int sleepx();
	unsigned altime;
	int (*alsig)() = SIG_DFL;
E 2
I 2
D 10
	int sleepx(), omask;
E 10
I 10
D 11
	int sleepx();
	long omask;
E 11
I 11
	register struct itimerval *itp;
E 11
E 10
	struct itimerval itv, oitv;
D 11
	register struct itimerval *itp = &itv;
E 11
	struct sigvec vec, ovec;
I 11
	long omask;
D 13
	void sleephandler();
E 13
I 13
	static void sleephandler();
E 13
E 11
E 2

D 2
	if (n==0)
E 2
I 2
D 11
	if (n == 0)
E 11
I 11
	itp = &itv;
	if (!seconds)
E 11
E 2
D 13
		return;
E 13
I 13
		return 0;
E 13
D 2
	altime = alarm(1000);	/* time to maneuver */
E 2
I 2
	timerclear(&itp->it_interval);
	timerclear(&itp->it_value);
	if (setitimer(ITIMER_REAL, itp, &oitv) < 0)
D 13
		return;
E 13
I 13
		return seconds;
E 13
D 7
	setvec(ovec, SIG_DFL);
E 2
D 5
	if (setjmp(jmp)) {
D 2
		signal(SIGALRM, alsig);
		alarm(altime);
E 2
I 2
		(void) sigvec(SIGALRM, &ovec, (struct sigvec *)0);
		(void) setitimer(ITIMER_REAL, &oitv, (struct itimerval *)0);
E 2
		return;
	}
E 5
D 2
	if (altime) {
		if (altime > n)
			altime -= n;
E 2
I 2
	omask = sigblock(0);
E 7
D 11
	itp->it_value.tv_sec = n;
E 11
I 11
	itp->it_value.tv_sec = seconds;
E 11
	if (timerisset(&oitv.it_value)) {
		if (timercmp(&oitv.it_value, &itp->it_value, >))
			oitv.it_value.tv_sec -= itp->it_value.tv_sec;
E 2
		else {
D 2
			n = altime;
			altime = 1;
E 2
I 2
			itp->it_value = oitv.it_value;
			/*
D 3
			 * Set the reset value to the smallest possible,
			 * the system will round it to the clock resolution.
E 3
I 3
D 11
			 * This is a hack, but we must have time to
D 5
			 * return from the setitimer after the longjmp
E 5
I 5
			 * return from the setitimer after the alarm
E 5
			 * or else it'll be restarted.  And, anyway,
			 * sleep never did anything more than this before.
E 11
I 11
			 * This is a hack, but we must have time to return
			 * from the setitimer after the alarm or else it'll
			 * be restarted.  And, anyway, sleep never did
			 * anything more than this before.
E 11
E 3
			 */
D 3
			oitv.it_value.tv_sec = 0;
			oitv.it_value.tv_usec = 1;
E 3
I 3
			oitv.it_value.tv_sec = 1;
			oitv.it_value.tv_usec = 0;
E 3
E 2
		}
	}
D 2
	alsig = signal(SIGALRM, sleepx);
	alarm(n);
	for(;;)
		pause();
E 2
I 2
D 11
	setvec(vec, sleepx);
E 11
I 11
	setvec(vec, sleephandler);
E 11
	(void) sigvec(SIGALRM, &vec, &ovec);
I 7
	omask = sigblock(sigmask(SIGALRM));
E 7
D 5
	if (setitimer(ITIMER_REAL, itp, (struct itimerval *)0) < 0)
		longjmp(jmp, 1);
D 3
	sigpause(omask &~ mask(SIGALRM));
E 3
I 3
	for (;;)
E 5
I 5
D 6
	(void) setitimer(ITIMER_REAL, itp, (struct itimerval *)0);
E 6
	ringring = 0;
I 6
	(void) setitimer(ITIMER_REAL, itp, (struct itimerval *)0);
E 6
	while (!ringring)
E 5
D 7
		sigpause(omask &~ mask(SIGALRM));
E 7
I 7
		sigpause(omask &~ sigmask(SIGALRM));
E 7
E 3
E 2
D 5
	/*NOTREACHED*/
E 5
I 5
	(void) sigvec(SIGALRM, &ovec, (struct sigvec *)0);
I 7
	(void) sigsetmask(omask);
E 7
	(void) setitimer(ITIMER_REAL, &oitv, (struct itimerval *)0);
I 13
	return 0;
E 13
E 5
}

D 11
static
sleepx()
E 11
I 11
static void
sleephandler()
E 11
{
I 2
D 11

E 11
E 2
D 5
	longjmp(jmp, 1);
E 5
I 5
	ringring = 1;
E 5
}
E 1
