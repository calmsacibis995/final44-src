h09727
s 00002/00002/00021
d D 8.1 93/06/02 00:03:59 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00019
d D 5.2 91/02/24 10:34:40 bostic 2 1
c Add include files to get prototype declarations, and fix bugs found.
e
s 00019/00000/00000
d D 5.1 91/02/19 14:58:51 bostic 1 0
c rename setpgrp to setpgid, add setpgrp compat call, update man page
c date and time created 91/02/19 14:58:51 by bostic
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
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <unistd.h>

I 2
#if __STDC__
setpgrp(pid_t pid, pid_t pgid)
#else
E 2
setpgrp(pid, pgid)
	pid_t pid, pgid;
I 2
#endif
E 2
{
	return(setpgid(pid, pgid));
}
E 1
