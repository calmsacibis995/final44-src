h01513
s 00002/00002/00020
d D 8.1 93/06/04 12:03:46 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00020
d D 5.6 91/02/23 19:49:52 donn 8 7
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00019
d D 5.5 90/06/01 14:12:06 bostic 7 6
c new copyright notice
e
s 00003/00003/00027
d D 5.4 90/02/15 16:43:31 marc 6 5
c termios
e
s 00021/00009/00009
d D 5.3 88/08/31 22:55:47 bostic 5 4
c from scratch; add Berkeley specific header
e
s 00002/00002/00016
d D 5.2 86/03/09 19:50:04 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00014
d D 5.1 85/06/05 12:26:43 mckusick 3 2
c Add copyright
e
s 00001/00001/00014
d D 4.2 84/05/16 10:50:36 ralph 2 1
c inline expand gtty (i.e. change gtty to ioctl).
e
s 00015/00000/00000
d D 4.1 80/12/21 16:39:45 wnj 1 0
c date and time created 80/12/21 16:39:45 by wnj
e
u
U
t
T
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
D 4
#ifndef lint
E 4
I 4
D 5
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif LIBC_SCCS and not lint
E 4

E 5
E 3
/*
D 5
 * Returns 1 iff file is a tty
E 5
I 5
D 9
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 5
 */

I 5
#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

E 5
D 6
#include <sgtty.h>
E 6
I 6
#include <termios.h>
I 8
#include <unistd.h>
E 8
E 6

I 8
int
E 8
D 5
isatty(f)
E 5
I 5
isatty(fd)
	int fd;
E 5
{
D 6
	struct sgttyb ttyb;
E 6
I 6
	struct termios t;
E 6

D 2
	if (gtty(f, &ttyb) < 0)
E 2
I 2
D 5
	if (ioctl(f, TIOCGETP, &ttyb) < 0)
E 2
		return(0);
	return(1);
E 5
I 5
D 6
	return(ioctl(fd, TIOCGETP, &ttyb) >= 0);
E 6
I 6
	return(tcgetattr(fd, &t) != -1);
E 6
E 5
}
E 1
