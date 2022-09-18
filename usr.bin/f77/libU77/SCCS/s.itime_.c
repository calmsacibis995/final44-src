h36395
s 00008/00005/00028
d D 5.2 91/04/12 15:33:09 bostic 4 3
c new copyright; att/bsd/shared
e
s 00007/00001/00026
d D 5.1 85/06/07 23:23:01 kre 3 2
c Add copyright
e
s 00001/00001/00026
d D 1.2 83/07/01 22:52:16 wnj 2 1
c include problem
e
s 00027/00000/00000
d D 1.1 81/02/10 13:55:58 dlw 1 0
c date and time created 81/02/10 13:55:58 by dlw
e
u
U
t
T
I 1
D 4
/*
D 3
char id_itime[] = "%W%";
E 3
I 3
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 4
E 3
 *
I 3
D 4
 *	%W%	%G%
E 4
I 4
 * %sccs.include.proprietary.c%
E 4
 */
I 4

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

/*
E 3
 * return the current time in numerical form
 *
 * calling sequence:
 *	integer iarray(3)
 *	call itime(iarray)
 * where:
 *	iarray will receive the current time; hour, min, sec.
 */

#include <sys/types.h>
D 2
#include <time.h>
E 2
I 2
#include <sys/time.h>
E 2

itime_(iar)
struct { long ihr; long imin; long isec; } *iar;
{
	struct tm *localtime(), *lclt;
	long int time(), t;

	t = time(0);
	lclt = localtime(&t);
	iar->ihr = lclt->tm_hour;
	iar->imin = lclt->tm_min;
	iar->isec = lclt->tm_sec;
}
E 1
