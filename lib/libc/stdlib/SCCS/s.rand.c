h26085
s 00002/00002/00026
d D 8.1 93/06/14 15:45:24 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00027
d D 5.7 93/06/14 15:45:16 bostic 9 7
c from Ralph; lint
e
s 00002/00002/00026
d R 8.1 93/06/04 13:08:06 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00027
d D 5.6 91/06/24 17:14:43 bostic 7 6
c off-by-one
e
s 00000/00000/00028
d D 5.5 91/02/23 22:56:42 donn 6 5
c Adjustments and bug fixes after adding prototypes to include files.
e
s 00000/00001/00028
d D 5.4 91/01/26 15:29:28 bostic 5 4
c doesn't need stdc.h
e
s 00018/00011/00011
d D 5.3 90/05/15 22:08:32 bostic 4 3
c from the ANSI standard
e
s 00002/00002/00020
d D 5.2 86/03/09 19:23:40 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00012
d D 5.1 85/05/30 10:28:28 dist 2 1
c Add copyright
e
s 00013/00000/00000
d D 4.1 80/12/21 16:40:01 wnj 1 0
c date and time created 80/12/21 16:40:01 by wnj
e
u
U
t
T
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 4
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
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
D 4
static	long	randx = 1;
E 4
I 4
#include <sys/types.h>
D 5
#include <sys/stdc.h>
E 5
#include <stdlib.h>
E 4

D 4
srand(x)
unsigned x;
E 4
I 4
static u_long next = 1;

int
rand()
E 4
{
D 4
	randx = x;
E 4
I 4
D 7
	return ((next = next * 1103515245 + 12345) % RAND_MAX);
E 7
I 7
D 9
	return ((next = next * 1103515245 + 12345) % (RAND_MAX + 1));
E 9
I 9
	return ((next = next * 1103515245 + 12345) % ((u_long)RAND_MAX + 1));
E 9
E 7
E 4
}

D 4
rand()
E 4
I 4
void
srand(seed)
u_int seed;
E 4
{
D 4
	return((randx = randx * 1103515245 + 12345) & 0x7fffffff);
E 4
I 4
	next = seed;
E 4
}
E 1
