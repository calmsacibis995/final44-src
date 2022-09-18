h56588
s 00002/00002/00021
d D 8.1 93/06/04 12:43:11 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00023/00000/00000
d D 5.1 91/02/18 00:45:07 torek 1 0
c date and time created 91/02/18 00:45:07 by torek
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <locale.h>

/*
 * Return the current locale conversion.
 */
struct lconv *
localeconv()
{
	extern struct lconv *__lconv;

	return (__lconv);
}
E 1
