h54829
s 00002/00002/00015
d D 8.1 93/06/04 17:48:31 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00009
d D 4.2 91/04/22 15:57:44 bostic 2 1
c new copyright; att/bsd/shared
e
s 00010/00000/00000
d D 4.1 83/06/27 14:43:14 sam 1 0
c date and time created 83/06/27 14:43:14 by sam
e
u
U
t
T
I 2
/*-
D 3
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
#endif /* not lint */
E 2

#include <stdio.h>
cont(xi,yi){
	putc('n',stdout);
	putsi(xi);
	putsi(yi);
}
E 1
