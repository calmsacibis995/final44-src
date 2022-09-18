h10866
s 00002/00002/00021
d D 8.1 93/06/02 00:03:34 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00002/00018
d D 5.3 91/02/24 10:34:38 bostic 3 2
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00019
d D 5.2 90/06/01 14:04:35 bostic 2 1
c new copyright notice
e
s 00030/00000/00000
d D 5.1 90/02/16 11:23:49 bostic 1 0
c date and time created 90/02/16 11:23:49 by bostic
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1993
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 3
#include <sys/types.h>
#include <sys/file.h>
E 3
I 3
#include <fcntl.h>
E 3

I 3
#if __STDC__
creat(const char *path, mode_t mode)
#else
E 3
creat(path, mode)
	char *path;
	mode_t mode;
I 3
#endif
E 3
{
	return(open(path, O_WRONLY|O_CREAT|O_TRUNC, mode));
}
E 1
