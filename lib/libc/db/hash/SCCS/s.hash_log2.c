h41328
s 00002/00002/00024
d D 8.1 93/06/04 15:22:04 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00004/00026
d D 5.4 91/09/26 16:17:30 bostic 4 3
c doesn't need all of these includes
e
s 00003/00003/00027
d D 5.3 91/09/08 12:30:57 bostic 3 2
c lint
e
s 00013/00006/00017
d D 5.2 91/09/04 12:56:34 bostic 2 1
c Rev #2.  ANSI/POSIX and reformatting, a few bug fixes thrown in
e
s 00023/00000/00000
d D 5.1 91/02/12 20:28:05 bostic 1 0
c date and time created 91/02/12 20:28:05 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 2
__log2( num )
int	num;
E 2
I 2
#include <sys/types.h>
D 4
#include <db.h>
#include "hash.h"
#include "page.h"
#include "extern.h"
E 4

D 3
int
E 3
I 3
u_int
E 3
__log2(num)
D 3
	int num;
E 3
I 3
	u_int num;
E 3
E 2
{
D 2
    register int	i;
    register int	limit = 1;
E 2
I 2
D 3
	register int i, limit;
E 3
I 3
	register u_int i, limit;
E 3
E 2

D 2
    for ( i = 0; limit < num; limit = limit << 1, i++ );
    return (i);
E 2
I 2
	limit = 1;
	for (i = 0; limit < num; limit = limit << 1, i++);
	return (i);
E 2
}
E 1
