h15722
s 00002/00002/00030
d D 8.1 93/06/02 00:03:50 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00003/00026
d D 5.3 91/02/24 10:34:39 bostic 3 2
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00028
d D 5.2 90/06/01 14:04:41 bostic 2 1
c new copyright notice
e
s 00039/00000/00000
d D 5.1 89/09/10 11:31:43 karels 1 0
c new compat file
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
D 3
#include <sys/errno.h>
E 3
I 3
#include <signal.h>
#include <errno.h>
E 3

/*
 * Backwards-compatible killpg().
 */
I 3
#if __STDC__
killpg(pid_t pgid, int sig)
#else
E 3
killpg(pgid, sig)
	pid_t pgid;
	int sig;
I 3
#endif
E 3
{
D 3
	extern int errno;

E 3
	if (pgid == 1) {
		errno = ESRCH;
		return (-1);
	}
	return (kill(-pgid, sig));
}
E 1
