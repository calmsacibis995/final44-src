h56388
s 00000/00000/00011
d D 8.1 93/06/04 16:26:46 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00001/00006
d D 5.3 91/04/20 14:12:53 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00002/00005
d D 5.2 86/03/09 20:54:10 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00003/00001/00004
d D 5.1 85/06/05 13:43:06 mckusick 2 1
c Add copyright
e
s 00005/00000/00000
d D 4.1 84/05/15 16:46:02 ralph 1 0
c date and time created 84/05/15 16:46:02 by ralph
e
u
U
t
T
I 4
/*-
 * %sccs.include.proprietary.c%
 */

E 4
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 3
#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
D 4
#endif LIBC_SCCS and not lint
E 4
I 4
#endif /* LIBC_SCCS and not lint */
E 4
E 3
E 2

#include <stdio.h>

char	_sobuf[BUFSIZ];
E 1
