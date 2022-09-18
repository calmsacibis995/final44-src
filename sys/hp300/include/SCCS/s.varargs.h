h48431
s 00005/00000/00031
d D 8.2 94/03/22 08:26:37 bostic 7 6
c add USL's copyright notice
e
s 00002/00002/00029
d D 8.1 93/06/10 21:45:32 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00003/00019
d D 5.4 92/02/19 17:07:21 bostic 5 4
c break into separate machine-dependent files for Sparc port
c varargs.h moved from /usr/src/include
e
s 00005/00000/00017
d D 5.3 91/04/03 16:44:45 bostic 4 3
c protect all user-level include files against reinclusion
e
s 00004/00007/00013
d D 5.2 90/05/13 18:53:00 bostic 3 2
c version that uses stdargs.h instead of rolling its own
e
s 00018/00005/00002
d D 5.1 90/05/13 18:42:45 bostic 2 1
c redo from scratch; fix short/char round error in historic version
e
s 00007/00000/00000
d D 4.1 83/05/03 13:48:24 sam 1 0
c date and time created 83/05/03 13:48:24 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
I 7
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 7
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

I 4
#ifndef _VARARGS_H_
#define	_VARARGS_H_

E 4
D 3
typedef char *va_list;
E 3
I 3
D 5
#include <stdarg.h>
E 5
I 5
typedef char *va_list;
E 5
E 3
D 2
# define va_dcl int va_alist;
# define va_start(list) list = (char *) &va_alist
# define va_end(list)
# define va_arg(list,mode) ((mode *)(list += sizeof(mode)))[-1]
E 2
I 2

D 3
#define	__va_round(type) \
	(((sizeof(type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

#define	va_arg(ap, type) \
	((type *)(ap += __va_round(type)))[-1]
E 3
I 3
D 5
#undef	va_dcl
E 5
E 3
#define	va_dcl	int va_alist;
D 3
#define	va_end(ap)
E 3
I 3

D 5
#undef	va_start
E 5
E 3
#define	va_start(ap) \
	ap = (char *)&va_alist
I 5

#ifdef KERNEL
#define	va_arg(ap, type) \
	((type *)(ap += sizeof(type)))[-1]
#else
#define	va_arg(ap, type) \
	((type *)(ap += sizeof(type) < sizeof(int) ? \
		(abort(), 0) : sizeof(type)))[-1]
#endif

#define	va_end(ap)
E 5
I 4

#endif /* !_VARARGS_H_ */
E 4
E 2
E 1
