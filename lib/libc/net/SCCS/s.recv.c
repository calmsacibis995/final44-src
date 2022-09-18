h27612
s 00006/00003/00018
d D 8.2 94/02/21 09:35:40 bostic 5 4
c change recv() to return a ssize_t and take a size_t as a length
e
s 00002/00002/00019
d D 8.1 93/06/04 12:51:09 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00020
d D 5.3 91/02/24 12:40:22 bostic 3 2
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00020
d D 5.2 90/06/01 14:16:35 bostic 2 1
c new copyright notice
e
s 00031/00000/00000
d D 5.1 88/12/16 11:12:21 bostic 1 0
c date and time created 88/12/16 11:12:21 by bostic
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <sys/socket.h>
D 5
#include <stdio.h>
E 5

I 5
#include <stddef.h>

ssize_t
E 5
recv(s, buf, len, flags)
D 5
	int s, len, flags;
E 5
I 5
	int s, flags;
	size_t len;
E 5
D 3
	char *buf;
E 3
I 3
	void *buf;
E 3
{
D 5
	return(recvfrom(s, buf, len, flags, (struct sockaddr *)NULL, 0));
E 5
I 5
	return (recvfrom(s, buf, len, flags, NULL, 0));
E 5
}
E 1
