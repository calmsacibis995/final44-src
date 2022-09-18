/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)getcwd_.c	5.2 (Berkeley) 4/12/91";
#endif /* not lint */

/*
 * Get pathname of current working directory.
 *
 * calling sequence:
 *	character*128 path
 *	ierr = getcwd(path)
 * where:
 *	path will receive the pathname of the current working directory.
 *	ierr will be 0 if successful, a system error code otherwise.
 */

#include <sys/param.h>
#ifndef	MAXPATHLEN
#define MAXPATHLEN	128
#endif

extern int errno;
char	*getwd();

long
getcwd_(path, len)
char *path;
long len;
{
	char	*p;
	char	pathname[MAXPATHLEN];

	p = getwd(pathname);
	b_char(pathname, path, len);
	if (p)
		return(0L);
	else
		return((long)errno);
}
