h20339
s 00002/00002/00020
d D 8.1 93/06/04 12:07:30 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00019
d D 5.4 91/02/23 19:50:20 donn 4 3
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00001/00021
d D 5.3 90/10/30 08:16:52 bostic 3 2
c POSIX return is pid_t
e
s 00001/00011/00021
d D 5.2 90/06/01 14:17:59 bostic 2 1
c new copyright notice
e
s 00032/00000/00000
d D 5.1 88/11/28 16:17:56 bostic 1 0
c date and time created 88/11/28 16:17:56 by bostic
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
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

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>

I 3
pid_t
E 3
D 4
wait(pstat)
	union wait *pstat;
E 4
I 4
wait(istat)
	int *istat;
E 4
{
D 3

E 3
D 4
	return (wait4(WAIT_ANY, pstat, 0, (struct rusage *)0));
E 4
I 4
	return (wait4(WAIT_ANY, istat, 0, (struct rusage *)0));
E 4
}
E 1
