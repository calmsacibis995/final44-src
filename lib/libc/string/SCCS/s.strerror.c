h12154
s 00002/00002/00039
d D 8.1 93/06/04 15:11:54 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00020/00006/00021
d D 5.6 91/05/04 13:45:45 bostic 6 5
c don't include stdio(3), do itoa inline
e
s 00001/00000/00026
d D 5.5 91/02/24 13:57:52 bostic 5 4
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00001/00025
d D 5.4 90/06/24 13:11:02 bostic 4 3
c handle really big numbers
e
s 00001/00011/00025
d D 5.3 90/06/01 14:46:07 bostic 3 2
c new copyright notice
e
s 00002/00000/00034
d D 5.2 90/05/17 12:05:41 bostic 2 1
c keep string.h and source in sync
e
s 00034/00000/00000
d D 5.1 89/04/09 17:42:03 bostic 1 0
c date and time created 89/04/09 17:42:03 by bostic
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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

I 2
#include <string.h>
I 5
D 6
#include <stdio.h>
E 6
E 5

E 2
char *
D 6
strerror(errnum)
	int errnum;
E 6
I 6
strerror(num)
	int num;
E 6
{
	extern int sys_nerr;
	extern char *sys_errlist[];
D 4
	static char ebuf[20];
E 4
I 4
D 6
	static char ebuf[40];		/* 64-bit number + slop */
E 6
I 6
#define	UPREFIX	"Unknown error: "
	static char ebuf[40] = UPREFIX;		/* 64-bit number + slop */
	register unsigned int errnum;
	register char *p, *t;
	char tmp[40];
E 6
E 4

D 6
	if ((unsigned int)errnum < sys_nerr)
E 6
I 6
	errnum = num;				/* convert to unsigned */
	if (errnum < sys_nerr)
E 6
		return(sys_errlist[errnum]);
D 6
	(void)sprintf(ebuf, "Unknown error: %d", errnum);
E 6
I 6

	/* Do this by hand, so we don't include stdio(3). */
	t = tmp;
	do {
		*t++ = "0123456789"[errnum % 10];
	} while (errnum /= 10);
	for (p = ebuf + sizeof(UPREFIX) - 1;;) {
		*p++ = *--t;
		if (t <= tmp)
			break;
	}
E 6
	return(ebuf);
}
E 1
