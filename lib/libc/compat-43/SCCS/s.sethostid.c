h01872
s 00002/00002/00029
d D 8.1 93/06/02 00:03:56 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00031/00000/00000
d D 5.1 93/04/04 13:47:33 mckusick 1 0
c date and time created 93/04/04 13:47:33 by mckusick
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
#include <sys/sysctl.h>

#if __STDC__
long
sethostid(long hostid)
#else
long
sethostid(hostid)
	long hostid;
#endif
{
	int mib[2];

	mib[0] = CTL_KERN;
	mib[1] = KERN_HOSTID;
	if (sysctl(mib, 2, NULL, NULL, &hostid, sizeof hostid) == -1)
		return (-1);
	return (0);
}
E 1
