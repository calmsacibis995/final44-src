/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)unlink_.c	5.2 (Berkeley) 4/12/91";
#endif /* not lint */

/*
 * unlink (remove) a file
 *
 * calling sequence:
 *	integer unlink
 *	ierror = unlink(filename)
 * where:
 *	ierror will be a returned status (0 == OK)
 *	filename is the file to be unlinked
 */

#include "../libI77/f_errno.h"
#include <sys/param.h>
#ifndef	MAXPATHLEN
#define MAXPATHLEN	128
#endif

long
unlink_(fname, namlen)
char *fname;
long namlen;
{
	char buf[MAXPATHLEN];

	if (namlen >= sizeof buf)
		return((long)(errno=F_ERARG));
	g_char(fname, namlen, buf);
	if (unlink(buf) != 0)
		return((long)errno);
	return(0L);
}
