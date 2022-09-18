h36488
s 00002/00002/00020
d D 8.1 93/06/04 13:05:55 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00003/00008
d D 5.3 91/01/20 21:20:41 bostic 5 4
c new stdio
e
s 00002/00002/00009
d D 5.2 86/03/09 20:50:42 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00007
d D 5.1 85/06/05 13:34:02 mckusick 3 2
c Add copyright
e
s 00001/00001/00007
d D 4.2 85/02/13 15:48:38 serge 2 1
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00008/00000/00000
d D 4.1 80/12/21 16:50:21 wnj 1 0
c date and time created 80/12/21 16:50:21 by wnj
e
u
U
t
T
I 5
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

E 5
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
D 4
#ifndef lint
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 5
#endif LIBC_SCCS and not lint
E 5
I 5
#endif /* LIBC_SCCS and not lint */
E 5
E 4

E 3
#include <stdio.h>

fputc(c, fp)
D 2
FILE *fp;
E 2
I 2
D 5
register FILE *fp;
E 5
I 5
	int c;
	register FILE *fp;
E 5
E 2
{
D 5
	return(putc(c, fp));
E 5
I 5
	return (putc(c, fp));
E 5
}
E 1
