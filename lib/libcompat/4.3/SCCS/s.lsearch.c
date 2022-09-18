h38203
s 00002/00002/00064
d D 8.1 93/06/04 16:25:10 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00065
d D 5.4 92/07/03 10:14:57 torek 4 3
c linear_base is static; say so up front
e
s 00001/00011/00065
d D 5.3 90/06/01 14:18:23 bostic 3 2
c new copyright notice
e
s 00000/00040/00076
d D 5.2 90/02/21 12:58:57 bostic 2 1
c minor manual page corrections; rip out rlsearch() and wlsearch().
e
s 00120/00000/00000
d D 5.1 89/10/14 11:39:29 bostic 1 0
c date and time created 89/10/14 11:39:29 by bostic
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Roger L. Snyder.
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <unistd.h>

D 4
char *linear_base();
E 4
I 4
static char *linear_base();
E 4

char *
lsearch(key, base, nelp, width, compar)
	char *key, *base;
	u_int *nelp, width;
	int (*compar)();
{
	return(linear_base(key, base, nelp, width, compar, 1));
}

char *
lfind(key, base, nelp, width, compar)
	char *key, *base;
	u_int *nelp, width;
	int (*compar)();
{
	return(linear_base(key, base, nelp, width, compar, 0));
}

static char *
linear_base(key, base, nelp, width, compar, add_flag)
	char *key, *base;
	u_int *nelp, width;
	int (*compar)(), add_flag;
{
	register char *element, *end;

	end = base + *nelp * width;
	for (element = base; element < end; element += width)
		if (!compar(element, key))		/* key found */
			return(element);

	if (!add_flag)					/* key not found */
		return(NULL);

	/*
	 * The UNIX System User's Manual, 1986 edition claims that
	 * a NULL pointer is returned by lsearch with errno set
	 * appropriately, if there is not enough room in the table
	 * to add a new item.  This can't be done as none of these
	 * routines have any method of determining the size of the
	 * table.  This comment was isn't in the 1986-87 System V
	 * manual.
	 */
	++*nelp;
	bcopy(key, end, (int)width);
	return(end);
}
D 2

char *
rlsearch(fd, nelp, width)
	int fd;
	u_int *nelp, *width;
{
	register u_int len;
	long val;
	char *base, *malloc();

	if (read(fd, (char *)&val, sizeof(long)) != sizeof(long))
		return(NULL);
	*nelp = (u_int)ntohl(val);
	if (read(fd, (char *)&val, sizeof(long)) != sizeof(long))
		return(NULL);
	*width = (u_int)ntohl(val);

	len = *nelp * *width;
	if (!(base = malloc(len)))
		return(NULL);
	return(read(fd, base, len) == len ? base : NULL);
}

wlsearch(fd, base, nelp, width)
	int fd;
	char *base;
	u_int nelp, width;
{
	long val;

	val = htonl((long)nelp);
	if (write(fd, (char *)&val, sizeof(long)) != sizeof(long))
		return(-1);
	val = htonl((long)width);
	if (write(fd, (char *)&val, sizeof(long)) != sizeof(long))
		return(-1);
	if (write(fd, base, nelp * width) != nelp * width)
		return(-1);
	return(0);
}
E 2
E 1
