h11422
s 00001/00013/00014
d D 5.6 91/04/03 16:50:55 bostic 6 5
c move stdarg.h to machine dependent include directory
e
s 00005/00000/00022
d D 5.5 91/02/22 14:02:38 bostic 5 4
c protect stdarg.h -- used by syslog.h and probably by others
e
s 00000/00007/00022
d D 5.4 90/06/26 15:46:06 bostic 4 3
c comment wasn't right...
e
s 00001/00001/00028
d D 5.3 90/06/24 18:27:58 bostic 3 2
c make this work for an ANSI compiler, where abort is a void function
e
s 00015/00005/00014
d D 5.2 90/05/18 12:25:10 bostic 2 1
c ANSI doesn't allow promotions for the user
e
s 00019/00000/00000
d D 5.1 90/05/13 18:49:18 bostic 1 0
c date and time created 90/05/13 18:49:18 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 5
#ifndef _STDARG_H
#define	_STDARG_H

E 5
D 6
typedef char *va_list;

D 2
#define	__va_round(type) \
	(((sizeof(type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

E 2
I 2
D 4
/*
 * ANSI says: "If there is no actual next argument, or if type is not
 * compatible with the type of the actual next argument (as promoted
 * according to the default argument promotions), the behavior is
 * undefined."  We read this to mean that we're not allowed to do the
 * promotion for the user, so shorts and chars drop core.
 */
E 4
E 2
#define	va_arg(ap, type) \
D 2
	((type *)(ap += __va_round(type)))[-1]
E 2
I 2
	((type *)(ap += sizeof(type) < sizeof(int) ? \
D 3
		abort() : sizeof(type)))[-1]
E 3
I 3
		(abort(), 0) : sizeof(type)))[-1]
E 3

E 2
#define	va_end(ap)
I 2

#define	__va_promote(type) \
	(((sizeof(type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

E 2
#define	va_start(ap, last) \
D 2
	(ap = ((char *)&(last) + __va_round(last)))
E 2
I 2
	(ap = ((char *)&(last) + __va_promote(last)))
E 6
I 6
#include <machine/stdarg.h>
E 6
I 5

#endif /* !_STDARG_H */
E 5
E 2
E 1
