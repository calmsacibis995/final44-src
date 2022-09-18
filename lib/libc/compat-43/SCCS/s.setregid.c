h17222
s 00002/00002/00034
d D 8.1 93/06/02 00:04:06 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00000/00000
d D 6.1 93/02/26 18:50:17 mckusick 1 0
c date and time created 93/02/26 18:50:17 by mckusick
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
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
setregid(rgid, egid)
	gid_t rgid, egid;
{
	static gid_t savedgid = -1;
	
	if (savedgid == -1)
		savedgid = getegid();
	/*
	 * we assume that the intent here is to be able to
	 * get back rgid priviledge. So we make sure that
	 * we will be able to do so, but do not actually
	 * set the rgid.
	 */
	if (rgid != -1 && rgid != getgid() && rgid != savedgid) {
		errno = EPERM;
		return (-1);
	}
	if (egid != -1 && setegid(egid) < 0)
		return (-1);
	return (0);
}
E 1
