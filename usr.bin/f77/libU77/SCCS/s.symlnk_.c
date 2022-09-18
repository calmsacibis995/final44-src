h54942
s 00008/00005/00038
d D 5.2 91/04/12 15:33:22 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00036
d D 5.1 85/06/07 23:28:59 kre 2 1
c Add copyright
e
s 00037/00000/00000
d D 1.1 83/04/30 16:34:40 dlw 1 0
c date and time created 83/04/30 16:34:40 by dlw
e
u
U
t
T
I 1
D 3
/*
D 2
char id_symlnk[] = "%W%";
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 3
E 2
 *
I 2
D 3
 *	%W%	%G%
E 3
I 3
 * %sccs.include.proprietary.c%
E 3
 */
I 3

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

/*
E 2
 * make a symbolic link to a file
 *
 * calling sequence:
 *	ierror = symlnk(name1, name2)
 * where:
 *	name1 is the pathname of an existing file
 *	name2 is a pathname that will become a symbolic link to name1
 *	ierror will be 0 if successful; a system error code otherwise.
 */

#include <sys/param.h>
#include "../libI77/f_errno.h"

#ifndef	MAXPATHLEN
#define	MAXPATHLEN	128
#endif

long symlnk_(name1, name2, n1len, n2len)
char *name1, *name2;
long n1len, n2len;
{
	char buf1[MAXPATHLEN];
	char buf2[MAXPATHLEN];

	if (n1len >= sizeof buf1 || n2len >= sizeof buf2)
		return((long)(errno=F_ERARG));
	g_char(name1, n1len, buf1);
	g_char(name2, n2len, buf2);
	if (buf1[0] == '\0' || buf2[0] == '\0')
		return((long)(errno=F_ERARG));
	if (symlink(buf1, buf2) != 0)
		return((long)errno);
	return(0L);
}
E 1
