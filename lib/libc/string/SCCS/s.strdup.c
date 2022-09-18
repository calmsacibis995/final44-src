h37879
s 00002/00002/00028
d D 8.1 93/06/04 15:11:48 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00003/00025
d D 5.5 92/12/02 15:59:44 bostic 5 4
c typo...
e
s 00003/00004/00025
d D 5.4 91/02/24 13:57:51 bostic 4 3
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00028
d D 5.3 90/06/01 14:45:59 bostic 3 2
c new copyright notice
e
s 00003/00001/00036
d D 5.2 90/05/17 12:05:39 bostic 2 1
c keep string.h and source in sync
e
s 00037/00000/00000
d D 5.1 88/12/12 20:40:12 bostic 1 0
c date and time created 88/12/12 20:40:12 by bostic
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 3
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 5
#include <sys/types.h>

E 5
D 4
#include <sys/types.h>
E 4
D 2
#include <stdio.h>
E 2
I 2
#include <stddef.h>
I 4
#include <stdlib.h>
E 4
#include <string.h>

E 2
D 4

E 4
char *
strdup(str)
D 4
	char *str;
E 4
I 4
	const char *str;
E 4
{
D 5
	int len;
E 5
I 5
	size_t len;
E 5
D 4
	char *copy, *malloc();
E 4
I 4
	char *copy;
E 4

	len = strlen(str) + 1;
	if (!(copy = malloc((u_int)len)))
D 5
		return((char *)NULL);
E 5
I 5
		return (NULL);
E 5
	bcopy(str, copy, len);
D 5
	return(copy);
E 5
I 5
	return (copy);
E 5
}
E 1
