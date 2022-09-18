h36371
s 00002/00001/00141
d D 5.3 93/05/24 12:15:49 bostic 3 2
c use fstat not lseek, it's probably cleaner
e
s 00010/00003/00132
d D 5.2 93/05/24 11:22:24 bostic 2 1
c ISO requires that bad paths or fd's fail
e
s 00135/00000/00000
d D 5.1 93/05/04 12:12:05 bostic 1 0
c date and time created 93/05/04 12:12:05 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/sysctl.h>

#include <errno.h>
#include <unistd.h>
#include <string.h>

static long local_fs __P((int));

long
fpathconf(fd, name)
	int fd;
	int name;
{
I 3
	struct stat sb;
E 3
	struct statfs fsb;

I 2
	/* ISO/IEC 9945-1, 5.7.1.3 requires -1 return if an invalid fd. */
D 3
	if (lseek(fd, (off_t)0, SEEK_CUR) == -1)
E 3
I 3
	if (fstat(fd, &sb))
E 3
		return (-1);

E 2
#ifdef LOCAL_DIFFERENT_FROM_FOREIGN
	/* Find out if it's a local file system. */
	if (fstatfs(fd, &fsb))
		return (-1);
	if (fsb.f_flags & MNT_LOCAL)
		/* Local file system. */
		;
	else
		/* Foreign file system. */
		;
#endif

	return (local_fs(name));
}

long
pathconf(path, name)
	const char *path;
	int name;
{
	struct stat sb;
	struct statfs fsb;
	int built;
	const char *p;
	char lpath[MAXPATHLEN];

D 2
#ifdef LOCAL_DIFFERENT_FROM_FOREIGN
E 2
	/*
D 2
	 * Statfs follows symlinks; we want the link's file
	 * system, not where it points.
E 2
I 2
	 * Statfs follows symlinks; we want the link's file system, not
	 * where it points.
	 *
	 * ISO/IEC 9945-1, 5.7.1.3 requires -1 return if an invalid fd.
E 2
	 */
	if (lstat(path, &sb))
		return (-1);
I 2

#ifdef LOCAL_DIFFERENT_FROM_FOREIGN
E 2
	if (S_ISLNK(sb.st_mode)) {
		if ((p = strrchr(path, '/')) == NULL)
			p = path;
		(void)snprintf(lpath, sizeof(lpath), "%s/.", p);
		built = 1;
	} else
		built = 0;

	/* Find out if it's a local file system. */
	if (statfs(built ? lpath : path, &fsb))
		return (-1);
	if (fsb.f_flags & MNT_LOCAL)
		/* Local file system. */
		;
	else
		/* Foreign file system. */
		;
#endif

	return (local_fs(name));
}

static long
local_fs(name)
	int name;
{
	size_t len;
	int mib[2], value;

	switch (name) {
	case _PC_LINK_MAX:
		mib[0] = CTL_KERN;
		mib[1] = KERN_LINK_MAX;
		break;
	case _PC_MAX_CANON:
		mib[0] = CTL_KERN;
		mib[1] = KERN_MAX_CANON;
		break;
	case _PC_MAX_INPUT:
		mib[0] = CTL_KERN;
		mib[1] = KERN_MAX_INPUT;
		break;
	case _PC_NAME_MAX:
		mib[0] = CTL_KERN;
		mib[1] = KERN_NAME_MAX;
		break;
	case _PC_PATH_MAX:
		mib[0] = CTL_KERN;
		mib[1] = KERN_PATH_MAX;
		break;
	case _PC_PIPE_BUF:
		mib[0] = CTL_KERN;
		mib[1] = KERN_PIPE_BUF;
		break;
	case _PC_CHOWN_RESTRICTED:
		mib[0] = CTL_KERN;
		mib[1] = KERN_CHOWN_RESTRICTED;
		break;
	case _PC_NO_TRUNC:
		mib[0] = CTL_KERN;
		mib[1] = KERN_NO_TRUNC;
		break;
	case _PC_VDISABLE:
		mib[0] = CTL_KERN;
		mib[1] = KERN_VDISABLE;
		break;
	default:
		errno = EINVAL;
		return (-1);
	}
	len = sizeof(value);
	return (sysctl(mib, 2, &value, &len, NULL, 0) == -1 ? -1 : value);
}
E 1
