h10121
s 00002/00002/00023
d D 8.1 93/06/04 18:15:56 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00017
d D 4.3 91/04/22 16:05:59 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00001/00018
d D 4.2 85/01/02 19:16:44 jak 2 1
c delete sleep(2): didn't work right since no flush() and better
c done by driver with dF#1000 in /etc/termcap.
e
s 00019/00000/00000
d D 4.1 83/06/27 14:19:18 sam 1 0
c date and time created 83/06/27 14:19:18 by sam
e
u
U
t
T
I 3
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

E 3
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
#endif /* not lint */
E 3

extern int ohiy;
extern int ohix;
extern int oloy;
extern int oextra;
erase(){
	int i;
		putch(033);
		putch(014);
		ohiy= -1;
		ohix = -1;
		oextra = -1;
		oloy = -1;
D 2
		sleep(2);
E 2
		return;
}
E 1
