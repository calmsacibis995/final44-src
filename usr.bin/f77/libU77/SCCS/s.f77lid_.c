h08577
s 00008/00005/00012
d D 5.2 91/04/12 15:32:52 bostic 3 2
c new copyright; att/bsd/shared
e
s 00009/00001/00008
d D 5.1 85/06/07 23:13:50 kre 2 1
c Add copyright
e
s 00009/00000/00000
d D 1.1 83/04/20 23:19:50 dlw 1 0
c date and time created 83/04/20 23:19:50 by dlw
e
u
U
t
T
I 1
D 3
/*
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
 *
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
 * f77lid_ - the ID strings for f77 libraries.
D 2
 *	%W%
E 2
I 2
 *
E 2
 * Usage:
 *	include 'external f77lid' in the declarations in any f77 module.
 */

extern char	libU77_id[], libI77_id[], libF77_id[];
char	*f77lid_[] = { libU77_id, libI77_id, libF77_id };
E 1
