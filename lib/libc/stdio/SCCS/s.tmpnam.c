h38084
s 00006/00004/00026
d D 8.3 94/03/28 08:25:28 bostic 7 6
c Lost Jeff Forys' changes to keep from leaving two slashes in the
c pathname (rev 5.4) when bought back Donn's changes in 8.2
e
s 00004/00002/00026
d D 8.2 93/11/16 12:23:02 bostic 6 5
c ANSI or the SVID guarantees that no name gets reused.
c From: donn@BSDI.COM (Donn Seeley)
e
s 00002/00002/00026
d D 8.1 93/06/04 13:10:02 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00027
d D 5.4 93/03/25 07:31:34 bostic 4 3
c Jeff Forys' changes to keep from leaving two slashes in the pathname
c GNU Emacs doesn't like this
e
s 00000/00001/00028
d D 5.3 91/02/24 13:30:24 bostic 3 2
c Add include files to get prototype declarations, and fix bugs found.
e
s 00004/00004/00025
d D 5.2 91/02/22 16:59:58 bostic 2 1
c cleanup, update, reimplement to work as correctly as possible
e
s 00029/00000/00000
d D 5.1 91/01/20 21:35:02 bostic 1 0
c new stdio
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
D 7
 * Copyright (c) 1990, 1993
E 7
I 7
 * Copyright (c) 1990, 1993, 1994
E 7
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 3
#include <sys/param.h>
E 3
I 2
D 7
#include <unistd.h>
E 7
I 7
#include <sys/types.h>

E 7
E 2
#include <stdio.h>
I 7
#include <unistd.h>
E 7

char *
tmpnam(s)
	char *s;
{
I 6
D 7
	static unsigned long tmpcount;
E 7
I 7
	static u_long tmpcount;
E 7
E 6
D 2
	static char buf[MAXPATHLEN];
	char *mktemp();
E 2
I 2
	static char buf[L_tmpnam];
E 2

	if (s == NULL)
		s = buf;
D 2
	(void) sprintf(s, "%s/XXXXXX", P_tmpdir);
	return (mktemp(s));
E 2
I 2
D 4
	(void)snprintf(s, L_tmpnam, "%s/tmp.XXXXXX", P_tmpdir);
E 4
I 4
D 6
	(void)snprintf(s, L_tmpnam, "%stmp.XXXXXX", P_tmpdir);
E 4
	return(mktemp(s));
E 6
I 6
D 7
	(void)snprintf(s, L_tmpnam, "%s/tmp.%lu.XXXXXX", P_tmpdir, tmpcount);
E 7
I 7
	(void)snprintf(s, L_tmpnam, "%stmp.%lu.XXXXXX", P_tmpdir, tmpcount);
E 7
	++tmpcount;
	return (mktemp(s));
E 6
E 2
}
E 1
