h08596
s 00002/00002/00031
d D 8.1 93/06/02 00:03:40 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00031
d D 5.2 93/05/24 23:53:51 torek 2 1
c lint
e
s 00032/00000/00000
d D 5.1 93/04/04 13:47:33 mckusick 1 0
c date and time created 93/04/04 13:47:33 by mckusick
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
gethostid(void)
#else
long
gethostid()
#endif
{
D 2
	int mib[2], size;
E 2
I 2
	int mib[2];
	size_t size;
E 2
	long value;

	mib[0] = CTL_KERN;
	mib[1] = KERN_HOSTID;
	size = sizeof value;
	if (sysctl(mib, 2, &value, &size, NULL, 0) == -1)
		return (-1);
	return (value);
}
E 1
