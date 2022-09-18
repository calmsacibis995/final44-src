h00807
s 00002/00002/00020
d D 8.1 93/06/04 13:04:54 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00021
d D 5.2 92/08/19 15:08:33 marc 2 1
c return value was backwards
e
s 00022/00000/00000
d D 5.1 91/01/20 21:34:47 bostic 1 0
c new stdio
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <stdio.h>

fgetpos(fp, pos)
	FILE *fp;
	fpos_t *pos;
{
D 2
	return((*pos = ftell(fp)) != (fpos_t)-1);
E 2
I 2
	return((*pos = ftell(fp)) == (fpos_t)-1);
E 2
}
E 1
