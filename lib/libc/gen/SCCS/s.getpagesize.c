h13797
s 00002/00002/00025
d D 8.1 93/06/04 12:03:07 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00006/00025
d D 5.2 93/05/25 00:00:34 torek 2 1
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00031/00000/00000
d D 5.1 93/04/04 13:51:40 mckusick 1 0
c date and time created 93/04/04 13:51:40 by mckusick
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

D 2
#if __STDC__
E 2
int
D 2
getpagesize(void)
#else
int
E 2
getpagesize()
D 2
#endif
E 2
{
D 2
	int mib[2], size, value;
E 2
I 2
	int mib[2], value;
	size_t size;
E 2

	mib[0] = CTL_HW;
	mib[1] = HW_PAGESIZE;
	size = sizeof value;
	if (sysctl(mib, 2, &value, &size, NULL, 0) == -1)
		return (-1);
	return (value);
}
E 1
