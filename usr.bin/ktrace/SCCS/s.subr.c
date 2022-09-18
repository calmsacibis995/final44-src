h59453
s 00002/00000/00081
d D 8.2 95/04/28 16:21:27 bostic 8 7
c ktrace is a kernel option, but the ktrace app reacts badly when it
c isn't compiled into the kernel.  also some knf changes.
c From: Adam Glass <glass@NetBSD.ORG>
e
s 00002/00002/00079
d D 8.1 93/06/06 14:53:30 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00000/00075
d D 5.2 92/04/15 17:28:47 marc 6 3
c add KTRFAC_CSW "w" -- context switching trace point
e
s 00001/00000/00074
d R 5.3 91/05/03 19:30:58 bostic 5 4
c nope, it does need sys/user.h
e
s 00000/00001/00074
d R 5.2 91/04/27 16:22:19 bostic 4 3
c don't need user.h anymore
e
s 00007/00004/00068
d D 5.1 91/01/17 15:57:42 bostic 3 2
c distribute includes around
e
s 00047/00012/00025
d D 1.2 90/06/29 00:38:53 marc 2 1
c textual changes; add timeval routines (should be in system library)
e
s 00037/00000/00000
d D 1.1 89/01/04 21:09:52 marc 1 0
c date and time created 89/01/04 21:09:52 by marc
e
u
U
t
T
I 2
/*-
D 7
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
I 1
D 3
#include "ktrace.h"
E 3
I 3
#include <sys/param.h>
#include <sys/file.h>
#include <sys/user.h>
#include <sys/proc.h>
E 3
I 2
#include <sys/time.h>
I 3
#include <sys/ktrace.h>
I 8

E 8
#include <stdio.h>
I 8

E 8
#include "ktrace.h"
E 3
E 2

D 2
getfacs(s)
E 2
I 2
getpoints(s)
E 2
	char *s;
{
	int facs = 0;

	while (*s) {
		switch(*s) {
		case 'c':
			facs |= KTRFAC_SYSCALL | KTRFAC_SYSRET;
			break;
		case 'n':
			facs |= KTRFAC_NAMEI;
			break;
D 2
		case 'g':
		case 'd':
E 2
I 2
		case 'i':
E 2
			facs |= KTRFAC_GENIO;
			break;
D 2
#ifdef notyet
E 2
		case 's':
D 2
			facs |= KTRFAC_SIGNAL;
E 2
I 2
			facs |= KTRFAC_PSIG;
E 2
			break;
I 6
		case 'w':
			facs |= KTRFAC_CSW;
			break;
		case '+':
			facs |= DEF_POINTS;
			break;
E 6
D 2
#endif
		case '+':
			facs |= DEF_FACS;
			break;
		case 'a':
			facs = KTRFAC_SYSCALL | KTRFAC_SYSRET | KTRFAC_GENIO;
			break;
E 2
		default:
			return (-1);
		}
		s++;
	}
	return (facs);
I 2
}

timevaladd(t1, t2)
	struct timeval *t1, *t2;
{
D 3

E 3
	t1->tv_sec += t2->tv_sec;
	t1->tv_usec += t2->tv_usec;
	timevalfix(t1);
}

timevalsub(t1, t2)
	struct timeval *t1, *t2;
{
D 3

E 3
	t1->tv_sec -= t2->tv_sec;
	t1->tv_usec -= t2->tv_usec;
	timevalfix(t1);
}

timevalfix(t1)
	struct timeval *t1;
{
D 3

E 3
	if (t1->tv_usec < 0) {
		t1->tv_sec--;
		t1->tv_usec += 1000000;
	}
	if (t1->tv_usec >= 1000000) {
		t1->tv_sec++;
		t1->tv_usec -= 1000000;
	}
E 2
}
E 1
