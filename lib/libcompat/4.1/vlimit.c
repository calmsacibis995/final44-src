/*-
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)vlimit.c	8.1 (Berkeley) 6/4/93";
#endif /* LIBC_SCCS and not lint */

/*
 * (Almost) backwards compatible vlimit.
 */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

/* LIM_NORAISE is not emulated */
#define	LIM_NORAISE	0	/* if <> 0, can't raise limits */
#define	LIM_CPU		1	/* max secs cpu time */
#define	LIM_FSIZE	2	/* max size of file created */
#define	LIM_DATA	3	/* max growth of data space */
#define	LIM_STACK	4	/* max growth of stack */
#define	LIM_CORE	5	/* max size of ``core'' file */
#define	LIM_MAXRSS	6	/* max desired data+stack core usage */

#define	NLIMITS		6

vlimit(limit, value)
	int limit, value;
{
	struct rlimit rlim;

	if (limit <= 0 || limit > NLIMITS)
		return (EINVAL);
	if (value == -1) {
		if (getrlimit(limit - 1, &rlim) < 0)
			return (-1);
		return (rlim.rlim_cur);
	}
	rlim.rlim_cur = value;
	rlim.rlim_max = RLIM_INFINITY;
	return (setrlimit(limit - 1, &rlim));
}
