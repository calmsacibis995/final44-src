h64392
s 00002/00002/00026
d D 8.1 93/06/02 00:03:43 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00000/00000
d D 5.1 91/02/20 08:15:42 bostic 1 0
c date and time created 91/02/20 08:15:42 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

char *
getwd(buf)
	char *buf;
{
	char *p;

	if (p = getcwd(buf, MAXPATHLEN))
		return(p);
	(void)strcpy(buf, strerror(errno));
	return((char *)NULL);
}
E 1
