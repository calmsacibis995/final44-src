h12872
s 00002/00002/00040
d D 8.1 93/06/04 13:07:37 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00013/00008
d D 5.3 91/01/20 21:24:44 bostic 5 4
c new stdio
e
s 00002/00002/00019
d D 5.2 86/03/09 20:52:23 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00017
d D 5.1 85/06/05 13:37:24 mckusick 3 2
c Add copyright
e
s 00002/00002/00016
d D 4.2 85/02/13 15:49:08 serge 2 1
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00018/00000/00000
d D 4.1 80/12/21 16:50:41 wnj 1 0
c date and time created 80/12/21 16:50:41 by wnj
e
u
U
t
T
I 5
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

E 5
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
D 4
#ifndef lint
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 5
#endif LIBC_SCCS and not lint
E 5
I 5
#endif /* LIBC_SCCS and not lint */
E 5
E 4

E 3
D 5
#include	<stdio.h>
E 5
I 5
#include <unistd.h>
#include <stdio.h>
E 5

char *
D 5
gets(s)
char *s;
E 5
I 5
gets(buf)
	char *buf;
E 5
{
D 5
	register c;
	register char *cs;
E 5
I 5
	register int c;
	register char *s;
	static int warned;
	static char w[] =
	    "warning: this program uses gets(), which is unsafe.\r\n";
E 5

D 5
	cs = s;
D 2
	while ((c = getchar()) != '\n' && c >= 0)
E 2
I 2
	while ((c = getchar()) != '\n' && c != EOF)
E 2
		*cs++ = c;
D 2
	if (c<0 && cs==s)
E 2
I 2
	if (c == EOF && cs==s)
E 2
		return(NULL);
	*cs++ = '\0';
	return(s);
E 5
I 5
	if (!warned) {
		(void) write(STDERR_FILENO, w, sizeof(w) - 1);
		warned = 1;
	}
	for (s = buf; (c = getchar()) != '\n';)
		if (c == EOF)
			if (s == buf)
				return (NULL);
			else
				break;
		else
			*s++ = c;
	*s = 0;
	return (buf);
E 5
}
E 1
