h47643
s 00002/00002/00022
d D 8.1 93/06/04 12:07:33 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00021
d D 5.6 91/02/23 19:50:21 donn 6 5
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00001/00023
d D 5.5 90/10/30 08:17:25 bostic 5 4
c POSIX return type is pid_t
e
s 00001/00011/00023
d D 5.4 90/06/01 14:18:06 bostic 4 3
c new copyright notice
e
s 00001/00001/00033
d D 5.3 89/07/07 12:36:00 karels 3 2
c WSIGRESTART is unnecessary
e
s 00001/00001/00033
d D 5.2 89/03/17 23:10:23 karels 2 1
c wait3 always gets restarted
e
s 00034/00000/00000
d D 5.1 88/11/28 16:18:04 bostic 1 0
c date and time created 88/11/28 16:18:04 by bostic
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>

I 5
pid_t
E 5
D 6
wait3(pstat, options, rup)
	union wait *pstat;
E 6
I 6
wait3(istat, options, rup)
	int *istat;
E 6
	int options;
	struct rusage *rup;
{
D 5

E 5
D 2
	return (wait4(WAIT_ANY, pstat, options, rup));
E 2
I 2
D 3
	return (wait4(WAIT_ANY, pstat, options | WSIGRESTART, rup));
E 3
I 3
D 6
	return (wait4(WAIT_ANY, pstat, options, rup));
E 6
I 6
	return (wait4(WAIT_ANY, istat, options, rup));
E 6
E 3
E 2
}
E 1
