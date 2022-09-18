h20136
s 00008/00005/00023
d D 5.2 91/04/12 15:32:49 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00021
d D 5.1 85/06/07 23:12:15 kre 2 1
c Add copyright
e
s 00022/00000/00000
d D 1.1 81/02/18 19:10:05 dlw 1 0
c date and time created 81/02/18 19:10:05 by dlw
e
u
U
t
T
I 1
D 3
/*
D 2
char id_ctime[] = "%W%";
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 3
E 2
 *
I 2
D 3
 *	%W%	%G%
E 3
I 3
 * %sccs.include.proprietary.c%
E 3
 */
I 3

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

/*
E 2
 * convert system time to ascii string
 *
 * calling sequence:
 *	character*24 string, ctime
 *	integer clock
 *	string = ctime (clock)
 * where:
 *	string will receive the ascii equivalent of the integer clock time.
 */

char *ctime();

ctime_(str, len, clock)
char *str; long len, *clock;
{
	char *s = ctime(clock);
	s[24] = '\0';
	b_char(s, str, len);
}
E 1
