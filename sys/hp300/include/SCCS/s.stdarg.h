h49678
s 00002/00002/00030
d D 8.1 93/06/10 21:45:24 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00027
d D 7.4 93/01/21 15:27:27 bostic 4 3
c protect against multiple inclusion
e
s 00006/00006/00021
d D 7.3 92/02/19 17:07:22 bostic 3 2
c break into separate machine-dependent files for Sparc port
c varargs.h moved from /usr/src/include
e
s 00005/00000/00022
d D 7.2 91/05/04 11:02:09 bostic 2 1
c kernel has no abort() function
e
s 00022/00000/00000
d D 7.1 91/04/03 16:51:31 bostic 1 0
c date and time created 91/04/03 16:51:31 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 4
#ifndef _STDARG_H_
#define	_STDARG_H_

E 4
typedef char *va_list;

I 3
#define	__va_promote(type) \
	(((sizeof(type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

#define	va_start(ap, last) \
	(ap = ((char *)&(last) + __va_promote(last)))

E 3
I 2
#ifdef KERNEL
E 2
#define	va_arg(ap, type) \
I 2
	((type *)(ap += sizeof(type)))[-1]
#else
#define	va_arg(ap, type) \
E 2
	((type *)(ap += sizeof(type) < sizeof(int) ? \
		(abort(), 0) : sizeof(type)))[-1]
I 2
#endif
E 2

#define	va_end(ap)
I 4

#endif /* !_STDARG_H_ */
E 4
D 3

#define	__va_promote(type) \
	(((sizeof(type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

#define	va_start(ap, last) \
	(ap = ((char *)&(last) + __va_promote(last)))
E 3
E 1
