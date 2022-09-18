h60012
s 00030/00000/00000
d D 8.1 94/01/04 17:25:14 bostic 1 0
c date and time created 94/01/04 17:25:14 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chuck Karish of Mindcraft, Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef	_SYS_UTSNAME_H
#define	_SYS_UTSNAME_H

struct utsname {
	char	sysname[256];	/* Name of this OS. */
	char	nodename[256];	/* Name of this network node. */
	char	release[256];	/* Release level. */
	char	version[256];	/* Version level. */
	char	machine[256];	/* Hardware type. */
};

#include <sys/cdefs.h>

__BEGIN_DECLS
int	uname __P((struct utsname *));
__END_DECLS

#endif	/* !_SYS_UTSNAME_H */
E 1
