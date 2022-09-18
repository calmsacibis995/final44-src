h35868
s 00002/00002/00032
d D 8.1 93/06/10 23:03:02 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00029
d D 7.3 93/01/21 15:28:22 bostic 3 2
c protect against multiple inclusion
e
s 00001/00001/00028
d D 7.2 92/12/05 12:25:19 ralph 2 1
c need to bump 'ap' up to the next double aligned address, then add
e
s 00029/00000/00000
d D 7.1 92/11/04 08:19:08 bostic 1 0
c date and time created 92/11/04 08:19:08 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 3
#ifndef _STDARG_H_
#define	_STDARG_H_

E 3
typedef char *va_list;

#define	__va_promote(type) \
	(((sizeof(type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

#define	va_start(ap, last) \
	(ap = ((char *)&(last) + __va_promote(last)))

#ifdef KERNEL
#define	va_arg(ap, type) \
	((type *)(ap += sizeof(type)))[-1]
#else
#define	va_arg(ap, type) \
	((type *)(ap += sizeof(type) == sizeof(int) ? sizeof(type) : \
		sizeof(type) > sizeof(int) ? \
D 2
		(-(int)(ap) & ~(sizeof(type) - 1)) + sizeof(type) : \
E 2
I 2
		(-(int)(ap) & (sizeof(type) - 1)) + sizeof(type) : \
E 2
		(abort(), 0)))[-1]
#endif

#define	va_end(ap)
I 3

#endif /* !_STDARG_H_ */
E 3
E 1
