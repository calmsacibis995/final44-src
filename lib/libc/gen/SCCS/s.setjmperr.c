h00310
s 00002/00002/00025
d D 8.1 93/06/04 12:04:59 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00025
d D 5.8 91/02/23 19:50:02 donn 8 7
c Add include files to get prototype declarations, and fix bugs found.
e
s 00003/00003/00022
d D 5.7 90/11/28 00:13:19 bostic 7 6
c make error messages a little better, use constants in unistd.h
e
s 00001/00011/00024
d D 5.6 90/06/01 14:14:52 bostic 6 5
c new copyright notice
e
s 00003/00001/00032
d D 5.5 90/05/27 11:21:59 bostic 5 4
c stderr may have been redirected
e
s 00010/00005/00023
d D 5.4 88/06/27 17:45:38 bostic 4 3
c install approved copyright notice
e
s 00012/00007/00016
d D 5.3 88/05/23 20:43:29 bostic 3 2
c add Berkeley specific header; don't print out trailing NULL
e
s 00002/00002/00021
d D 5.2 86/03/09 21:14:12 donn 2 1
c added LIBC_SCCS condition for sccs ids
e
s 00023/00000/00000
d D 5.1 86/01/09 15:51:54 mckusick 1 0
c date and time created 86/01/09 15:51:54 by mckusick
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1980 Regents of the University of California.
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 6
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 4
E 3
 */

D 2
#ifndef lint
E 2
I 2
#if defined(LIBC_SCCS) && !defined(lint)
E 2
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
D 3
#endif LIBC_SCCS and not lint
E 3
I 3
#endif /* LIBC_SCCS and not lint */
E 3
E 2

D 3
#define ERRMSG	"longjmp botch\n"

E 3
/*
 * This routine is called from longjmp() when an error occurs.
 * Programs that wish to exit gracefully from this error may
 * write their own versions.
 * If this routine returns, the program is aborted.
 */
I 3

I 8
#include <setjmp.h>
E 8
I 5
D 7
#include <stdio.h>
E 7
I 7
#include <unistd.h>
E 7

I 8
void
E 8
E 5
E 3
longjmperror()
{
D 3

	write(2, ERRMSG, sizeof(ERRMSG));
E 3
I 3
D 7
#define	ERRMSG	"longjmp botch\n"
D 5
	write(2, ERRMSG, sizeof(ERRMSG) - 1);
E 5
I 5
	write(fileno(stderr), ERRMSG, sizeof(ERRMSG) - 1);
E 7
I 7
#define	ERRMSG	"longjmp botch.\n"
	(void)write(STDERR_FILENO, ERRMSG, sizeof(ERRMSG) - 1);
E 7
E 5
E 3
}
E 1
