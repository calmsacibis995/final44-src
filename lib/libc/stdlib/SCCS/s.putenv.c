h57895
s 00006/00006/00026
d D 8.2 94/03/27 05:40:46 bostic 6 5
c return -1 on failure, so it matches the man page and setenv
e
s 00002/00002/00030
d D 8.1 93/06/04 13:07:31 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00031
d D 5.4 91/02/23 22:56:38 donn 4 3
c Adjustments and bug fixes after adding prototypes to include files.
e
s 00010/00004/00022
d D 5.3 90/05/17 14:31:05 bostic 3 2
c putenv shouldn't modify the user's string, it might be read-only
e
s 00004/00013/00022
d D 5.2 90/05/16 13:51:44 bostic 2 1
c cleanup includes
e
s 00035/00000/00000
d D 5.1 89/02/14 20:32:54 bostic 1 0
c date and time created 89/02/14 20:32:54 by bostic
e
u
U
t
T
I 1
D 2
/*
E 2
I 2
/*-
E 2
D 5
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 2
#include <stdlib.h>
I 3
#include <string.h>
E 3

I 3
int
E 3
E 2
putenv(str)
D 4
	char *str;
E 4
I 4
	const char *str;
E 4
{
D 3
	register char *equal;
E 3
I 3
D 6
	register char *p, *equal;
E 6
I 6
	char *p, *equal;
E 6
E 3
	int rval;
D 2
	char *index();
E 2

D 3
	if (!(equal = index(str, '=')))
E 3
I 3
D 6
	if (!(p = strdup(str)))
E 3
		return(1);
I 3
	if (!(equal = index(p, '='))) {
E 6
I 6
	if ((p = strdup(str)) == NULL)
		return (-1);
	if ((equal = index(p, '=')) == NULL) {
E 6
		(void)free(p);
D 6
		return(1);
E 6
I 6
		return (-1);
E 6
	}
E 3
	*equal = '\0';
D 3
	rval = setenv(str, equal + 1, 1);
	*equal = '=';
E 3
I 3
	rval = setenv(p, equal + 1, 1);
	(void)free(p);
E 3
D 6
	return(rval);
E 6
I 6
	return (rval);
E 6
}
E 1
