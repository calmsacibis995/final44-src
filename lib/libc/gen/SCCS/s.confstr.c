h13067
s 00002/00002/00057
d D 8.1 93/06/04 12:00:31 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00058
d D 5.4 93/05/24 11:39:00 bostic 4 3
c return length + 1, for null terminator
e
s 00027/00002/00032
d D 5.3 93/05/04 12:10:02 bostic 3 2
c use sysctl(3), don't roll our own
e
s 00001/00001/00033
d D 5.2 93/05/03 16:54:43 bostic 2 1
c add /usr/sbin, so user's will find chown
e
s 00034/00000/00000
d D 5.1 93/05/03 16:52:11 bostic 1 0
c date and time created 93/05/03 16:52:11 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 3
#include <sys/param.h>
#include <sys/sysctl.h>

E 3
#include <errno.h>
#include <paths.h>
I 3
#include <stdlib.h>
E 3
#include <unistd.h>

size_t
confstr(name, buf, len)
	int name;
	char *buf;
	size_t len;
{
I 3
	size_t tlen;
	int mib[2], sverrno;
	char *p;

E 3
	switch (name) {
	case _CS_PATH:
I 3
		mib[0] = CTL_USER;
		mib[1] = USER_CS_PATH;
		if (sysctl(mib, 2, NULL, &tlen, NULL, 0) == -1)
			return (-1);
E 3
		if (len != 0 && buf != NULL) {
D 2
			(void)strncpy(buf, _PATH_DEFPATH, len - 1);
E 2
I 2
D 3
			(void)strncpy(buf, _PATH_STDPATH, len - 1);
E 3
I 3
			if ((p = malloc(tlen)) == NULL)
				return (-1);
			if (sysctl(mib, 2, p, &tlen, NULL, 0) == -1) {
				sverrno = errno;
				free(p);
				errno = sverrno;
				return (-1);
			}
			/*
			 * POSIX 1003.2 requires partial return of
			 * the string -- that should be *real* useful.
			 */
			(void)strncpy(buf, p, len - 1);
E 3
E 2
			buf[len - 1] = '\0';
I 3
			free(p);
E 3
		}
D 2
		return (sizeof(_PATH_DEFPATH));
E 2
I 2
D 3
		return (sizeof(_PATH_STDPATH));
E 3
I 3
D 4
		return (tlen);
E 4
I 4
		return (tlen + 1);
E 4
E 3
E 2
	default:
		errno = EINVAL;
		return (0);
	}
	/* NOTREACHED */
}
E 1
