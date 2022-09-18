h17792
s 00002/00002/00034
d D 8.1 93/06/02 00:04:12 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00000/00000
d D 5.1 92/07/09 14:30:14 mckusick 1 0
c date and time created 92/07/09 14:30:14 by mckusick
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <errno.h>

int
setreuid(ruid, euid)
	uid_t ruid, euid;
{
	static uid_t saveduid = -1;
	
	if (saveduid == -1)
		saveduid = geteuid();
	/*
	 * we assume that the intent here is to be able to
	 * get back ruid priviledge. So we make sure that
	 * we will be able to do so, but do not actually
	 * set the ruid.
	 */
	if (ruid != -1 && ruid != getuid() && ruid != saveduid) {
		errno = EPERM;
		return (-1);
	}
	if (euid != -1 && seteuid(euid) < 0)
		return (-1);
	return (0);
}
E 1
