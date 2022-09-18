h64359
s 00002/00002/00055
d D 8.1 93/06/04 12:05:28 bostic 6 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00000/00057
d R 5.5 93/01/13 15:42:00 bostic 5 4
c sigaddset, sigdelset and sigismember have to return -1/EINVAL if the
c signal number is bogus.
e
s 00001/00001/00056
d D 5.4 91/11/12 10:41:09 bostic 4 3
c include user-level signal.h, not system level
e
s 00001/00001/00056
d D 5.3 91/02/23 19:50:05 donn 3 2
c Add include files to get prototype declarations, and fix bugs found.
e
s 00002/00000/00055
d D 5.2 90/07/01 16:23:46 karels 2 1
c correct return value for sig{empty,fill}set
e
s 00055/00000/00000
d D 5.1 90/06/28 10:03:23 karels 1 0
c initial version
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 4
#include <sys/signal.h>
E 4
I 4
#include <signal.h>
E 4

#undef sigemptyset
#undef sigfillset
#undef sigaddset
#undef sigdelset
#undef sigismember

sigemptyset(set)
	sigset_t *set;
{
	*set = 0;
I 2
	return (0);
E 2
}

sigfillset(set)
	sigset_t *set;
{
	*set = ~(sigset_t)0;
I 2
	return (0);
E 2
}

sigaddset(set, signo)
	sigset_t *set;
	int signo;
{
	*set |= sigmask(signo);
	return (0);
}

sigdelset(set, signo)
	sigset_t *set;
	int signo;
{
	*set &= ~sigmask(signo);
	return (0);
}

sigismember(set, signo)
D 3
	sigset_t *set;
E 3
I 3
	const sigset_t *set;
E 3
	int signo;
{
	return ((*set & ~sigmask(signo)) != 0);
}
E 1
