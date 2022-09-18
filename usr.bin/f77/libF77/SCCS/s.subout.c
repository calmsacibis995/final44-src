h54469
s 00008/00005/00021
d D 5.2 91/04/12 15:00:22 bostic 5 4
c new copyright; att/bsd/shared
e
s 00005/00001/00021
d D 5.1 85/06/07 22:38:24 kre 4 3
c Add copyright
e
s 00001/00002/00021
d D 1.2 85/05/09 23:08:11 libs 3 1
c call f77_abort() instead of abort() to get consistent error handling
c and dumps only when wanted.
e
s 00001/00001/00022
d R 1.2 85/05/06 14:13:51 libs 2 1
c Change all calls to abort() to f77_abort() and have f77_abort() 
c call abort() for dump only when environment and load flags so specify.
e
s 00023/00000/00000
d D 1.1 83/01/21 11:19:31 dlw 1 0
c date and time created 83/01/21 11:19:31 by dlw
e
u
U
t
T
I 1
D 5
/*
D 4
 *	"%W%"
E 4
I 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
 *
D 5
 *	%W%	%G%
E 5
I 5
 * %sccs.include.proprietary.c%
E 5
E 4
 */
I 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

#include <stdio.h>

subout(varn, offset, procn, line)
char *varn, *procn;
long int offset;
int line;
{
register int i;

fprintf(stderr, "Subscript out of range on line %d of procedure ", line);
for(i = 0 ; i < 8 && *procn!='_' ; ++i)
	putc(*procn++, stderr);
fprintf(stderr, ".\nAttempt to access the %ld-th element of variable ", offset+1);
for(i = 0 ; i < 6  && *varn!=' ' ; ++i)
	putc(*varn++, stderr);
fprintf(stderr, ".\n");
D 3
_cleanup();
abort();
E 3
I 3
f77_abort();
E 3
}
E 1
