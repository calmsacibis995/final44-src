h01934
s 00002/00002/00025
d D 8.1 93/06/04 12:00:44 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00026
d D 5.2 91/02/20 09:07:30 bostic 2 1
c save four bytes
e
s 00027/00000/00000
d D 5.1 91/02/19 15:39:22 bostic 1 0
c date and time created 91/02/19 15:39:22 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <stdio.h>
#include <paths.h>
#include <string.h>

char *
ctermid(s)
	char *s;
{
D 2
	static char *def = _PATH_TTY;
E 2
I 2
	static char def[] = _PATH_TTY;
E 2

	if (s) {
		bcopy(def, s, sizeof(_PATH_TTY));
		return(s);
	}
	return(def);
}
E 1
