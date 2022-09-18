h57462
s 00001/00001/00150
d D 8.2 94/01/04 14:49:28 bostic 4 3
c since timezones are named in the file system in 4BSD,
c my guess is that the right value is the max file name length
e
s 00002/00002/00149
d D 8.1 93/06/04 12:05:48 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00000/00144
d D 5.2 93/05/24 10:53:15 bostic 2 1
c add USER_STREAM_MAX, USER_TZNAME_MAX
e
s 00144/00000/00000
d D 5.1 93/05/15 12:04:55 bostic 1 0
c date and time created 93/05/15 12:04:55 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1993
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

#include <errno.h>
#include <limits.h>
#include <paths.h>
I 2
#include <stdio.h>
E 2
#include <unistd.h>

int
sysctl(name, namelen, oldp, oldlenp, newp, newlen)
	int *name;
	u_int namelen;
	void *oldp, *newp;
	size_t *oldlenp, newlen;
{
	if (name[0] != CTL_USER)
		return (__sysctl(name, namelen, oldp, oldlenp, newp, newlen));

	if (newp != NULL) {
		errno = EPERM;
		return (-1);
	}
	if (namelen != 2) {
		errno = EINVAL;
		return (-1);
	}

	switch (name[1]) {
	case USER_CS_PATH:
		if (oldp && *oldlenp < sizeof(_PATH_STDPATH))
			return (ENOMEM);
		*oldlenp = sizeof(_PATH_STDPATH);
		if (oldp != NULL)
			memmove(oldp, _PATH_STDPATH, sizeof(_PATH_STDPATH));
		return (0);
	}

	if (oldp && *oldlenp < sizeof(int))
		return (ENOMEM);
	*oldlenp = sizeof(int);
	if (oldp == NULL)
		return (0);

	switch (name[1]) {
	case USER_BC_BASE_MAX:
		*(int *)oldp = BC_BASE_MAX;
		return (0);
	case USER_BC_DIM_MAX:
		*(int *)oldp = BC_DIM_MAX;
		return (0);
	case USER_BC_SCALE_MAX:
		*(int *)oldp = BC_SCALE_MAX;
		return (0);
	case USER_BC_STRING_MAX:
		*(int *)oldp = BC_STRING_MAX;
		return (0);
	case USER_COLL_WEIGHTS_MAX:
		*(int *)oldp = COLL_WEIGHTS_MAX;
		return (0);
	case USER_EXPR_NEST_MAX:
		*(int *)oldp = EXPR_NEST_MAX;
		return (0);
	case USER_LINE_MAX:
		*(int *)oldp = LINE_MAX;
		return (0);
	case USER_RE_DUP_MAX:
		*(int *)oldp = RE_DUP_MAX;
		return (0);
	case USER_POSIX2_VERSION:
		*(int *)oldp = _POSIX2_VERSION;
		return (0);
	case USER_POSIX2_C_BIND:
#ifdef POSIX2_C_BIND
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_POSIX2_C_DEV:
#ifdef	POSIX2_C_DEV
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_POSIX2_CHAR_TERM:
#ifdef	POSIX2_CHAR_TERM
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_POSIX2_FORT_DEV:
#ifdef	POSIX2_FORT_DEV
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_POSIX2_FORT_RUN:
#ifdef	POSIX2_FORT_RUN
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_POSIX2_LOCALEDEF:
#ifdef	POSIX2_LOCALEDEF
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_POSIX2_SW_DEV:
#ifdef	POSIX2_SW_DEV
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_POSIX2_UPE:
#ifdef	POSIX2_UPE
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
I 2
		return (0);
	case USER_STREAM_MAX:
		*(int *)oldp = FOPEN_MAX;
		return (0);
	case USER_TZNAME_MAX:
D 4
		*(int *)oldp = 1024;
E 4
I 4
		*(int *)oldp = NAME_MAX;
E 4
E 2
		return (0);
	default:
		errno = EINVAL;
		return (-1);
	}
	/* NOTREACHED */
}
E 1
