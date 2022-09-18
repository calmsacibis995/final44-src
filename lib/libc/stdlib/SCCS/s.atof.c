h65087
s 00002/00002/00018
d D 8.1 93/06/04 13:05:00 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00018
d D 5.3 93/01/08 17:40:16 bostic 3 2
c lint
e
s 00001/00011/00019
d D 5.2 90/06/01 14:43:56 bostic 2 1
c new copyright notice
e
s 00031/00000/00000
d D 5.1 88/09/12 11:06:39 bostic 1 0
c date and time created 88/09/12 11:06:39 by bostic
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

#include <stdlib.h>
#include <stddef.h>

double
atof(ascii)
D 3
	char *ascii;
E 3
I 3
	const char *ascii;
E 3
{
D 3
	return(strtod(ascii, (char **)NULL));
E 3
I 3
	return (strtod(ascii, NULL));
E 3
}
E 1
