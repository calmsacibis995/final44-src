h54509
s 00002/00002/00015
d D 8.1 93/06/04 16:24:52 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00016
d D 5.2 93/01/12 10:25:23 bostic 2 1
c free doesn't return a value
e
s 00017/00000/00000
d D 5.1 93/01/12 10:24:57 bostic 1 0
c date and time created 93/01/12 10:24:57 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

void
cfree(p)
	void *p;
{
D 2
	(void)free(p);
E 2
I 2
	free(p);
E 2
}
E 1
