h64775
s 00002/00002/00009
d D 8.1 93/06/04 18:56:24 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/00010
d D 5.3 91/01/17 14:39:32 bostic 3 2
c from scratch -- /bin/mail was a security problem, and not worth fixing
e
s 00000/00001/00013
d D 5.2 90/06/24 23:29:12 bostic 2 1
c move _PATH_MAILDIR into <paths.h>
e
s 00014/00000/00000
d D 5.1 90/04/29 15:50:28 bostic 1 0
c date and time created 90/04/29 15:50:28 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
D 3

E 3
#include <paths.h>

D 3
#undef _PATH_TMP
#define _PATH_TMP	"/tmp/maXXXXX"
E 3
I 3
#define _PATH_LOCTMP	"/tmp/local.XXXXXX"
E 3
D 2
#define _PATH_MAILDIR	"/var/mail/"
E 2
E 1
