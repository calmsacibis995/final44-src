h16813
s 00002/00002/00030
d D 8.1 93/06/04 12:04:54 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00029
d D 5.2 93/04/04 14:03:26 mckusick 2 1
c have to explicitly return 0
e
s 00030/00000/00000
d D 5.1 93/04/04 13:58:57 mckusick 1 0
c date and time created 93/04/04 13:58:57 by mckusick
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
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
sethostname(const char *name, int namelen)
#else
long
sethostname(name, namelen)
	char *name;
	int namelen;
#endif
{
	int mib[2];

	mib[0] = CTL_KERN;
	mib[1] = KERN_HOSTNAME;
D 2
	return (sysctl(mib, 2, NULL, NULL, (void *)name, namelen));
E 2
I 2
	if (sysctl(mib, 2, NULL, NULL, (void *)name, namelen) == -1)
		return (-1);
	return (0);
E 2
}
E 1
