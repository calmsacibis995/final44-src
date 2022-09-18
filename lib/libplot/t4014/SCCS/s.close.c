h64793
s 00002/00002/00018
d D 8.1 93/06/07 20:44:22 bostic 4 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00018
d R 8.1 93/06/04 17:52:10 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00012
d D 4.2 91/04/22 16:05:58 bostic 2 1
c new copyright; att/bsd/shared
e
s 00013/00000/00000
d D 4.1 83/06/27 14:19:16 sam 1 0
c date and time created 83/06/27 14:19:16 by sam
e
u
U
t
T
I 2
/*-
D 4
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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
closevt(){
	putch(037);
	fflush(stdout);
}
closepl(){
	putch(037);
	fflush(stdout);
}
E 1
