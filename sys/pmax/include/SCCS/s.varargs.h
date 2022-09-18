h54203
s 00005/00000/00033
d D 8.2 94/03/22 08:28:07 bostic 4 3
c add USL's copyright notice
e
s 00002/00002/00031
d D 8.1 93/06/10 23:03:11 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00032
d D 7.2 92/12/05 12:25:20 ralph 2 1
c need to bump 'ap' up to the next double aligned address, then add
e
s 00033/00000/00000
d D 7.1 92/11/04 08:19:12 bostic 1 0
c date and time created 92/11/04 08:19:12 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
I 4
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 4
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef _VARARGS_H_
#define	_VARARGS_H_

typedef char *va_list;

#define	va_dcl	int va_alist;

#define	va_start(ap) \
	ap = (char *)&va_alist

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

#endif /* !_VARARGS_H_ */
E 1
