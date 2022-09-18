h30235
s 00002/00002/00027
d D 8.1 93/06/04 12:02:42 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00006/00026
d D 5.3 93/05/25 00:00:35 torek 3 2
c pedantically ANSI, i.e., nothing after #else/#endif
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
D 4
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
#include <sys/sysctl.h>

D 3
#if __STDC__
E 3
long
D 3
gethostname(char *name, int namelen)
#else
long
E 3
gethostname(name, namelen)
	char *name;
	int namelen;
D 3
#endif
E 3
{
	int mib[2];
I 3
	size_t size;
E 3

	mib[0] = CTL_KERN;
	mib[1] = KERN_HOSTNAME;
D 2
	return (sysctl(mib, 2, name, &namelen, NULL, 0));
E 2
I 2
D 3
	if (sysctl(mib, 2, name, &namelen, NULL, 0) == -1)
E 3
I 3
	size = namelen;
	if (sysctl(mib, 2, name, &size, NULL, 0) == -1)
E 3
		return (-1);
	return (0);
E 2
}
E 1
