h02386
s 00002/00002/00017
d D 8.1 93/06/06 14:27:19 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00000/00000
d D 5.1 91/04/04 12:24:44 bostic 1 0
c date and time created 91/04/04 12:24:44 by bostic
e
u
U
t
T
I 1
/*-
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
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/cdefs.h>

__BEGIN_DECLS
int	crc __P((int, unsigned long *, unsigned long *));
void	pcrc __P((char *, unsigned long, unsigned long));
void	psum1 __P((char *, unsigned long, unsigned long));
void	psum2 __P((char *, unsigned long, unsigned long));
int	csum1 __P((int, unsigned long *, unsigned long *));
int	csum2 __P((int, unsigned long *, unsigned long *));
__END_DECLS
E 1
