h48843
s 00002/00012/00021
d D 5.2 91/05/13 18:05:15 bostic 2 1
c new copyright; att/bsd/shared
e
s 00033/00000/00000
d D 5.1 88/10/25 16:10:06 bostic 1 0
c date and time created 88/10/25 16:10:06 by bostic
e
u
U
t
T
I 1
D 2
/*
E 2
I 2
/*-
E 2
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <stdio.h>

main()
{
	fputs("fp: fp has not been ported to the tahoe.\n", stderr);
}
E 1
