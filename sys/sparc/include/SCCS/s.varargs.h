h36041
s 00005/00000/00059
d D 8.3 94/03/22 08:28:53 bostic 8 7
c add USL's copyright notice
e
s 00011/00002/00048
d D 8.2 93/09/27 14:13:27 torek 7 6
c add gcc 2.4.5 support
e
s 00002/00002/00048
d D 8.1 93/06/11 15:12:57 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00013/00028
d D 7.5 93/05/07 11:13:43 torek 5 4
c handle C++ and struct-values
e
s 00002/00002/00039
d D 7.4 93/04/20 18:56:40 torek 4 3
c spelling
e
s 00013/00002/00028
d D 7.3 92/10/15 21:18:15 torek 3 2
c compensate for gcc 2 being smarter than Sun calling conventions
e
s 00005/00000/00025
d D 7.2 92/07/21 16:41:43 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00025/00000/00000
d D 7.1 92/07/13 00:43:08 torek 1 0
c date and time created 92/07/13 00:43:08 by torek
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
I 8
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 8
E 6
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: varargs.h,v 1.4 92/06/17 06:10:31 torek Exp $
E 3
I 3
D 4
 * from: $Header: varargs.h,v 1.5 92/10/16 04:16:09 torek Exp $
E 4
I 4
D 5
 * from: $Header: varargs.h,v 1.6 92/11/26 02:04:48 torek Exp $
E 5
I 5
D 7
 * from: $Header: varargs.h,v 1.7 93/05/07 18:10:36 torek Exp $
E 7
I 7
 * from: $Header: varargs.h,v 1.8 93/09/27 00:53:20 torek Exp $
E 7
E 5
E 4
E 3
 */

#ifndef _MACHINE_VARARGS_H_
#define	_MACHINE_VARARGS_H_

I 5
typedef char *va_list;

E 5
I 3
/* See <machine/stdarg.h> for comments. */
#if __GNUC__ == 1
#define __extension__
D 5
#endif
E 3
typedef char *va_list;
E 5
#define	va_dcl	int va_alist;
D 5
#define	va_start(ap) (__builtin_saveregs(), (ap) = (char *)&va_alist)
D 3
#define va_arg(ap, t)	(((t *)(ap += sizeof(t)))[-1])
E 3
I 3
#define va_arg(ap, ty) \
    (sizeof(ty) == 8 ? __extension__ ({ \
	union { ty __d; int __i[2]; } __u; \
	__u.__i[0] = ((int *)(ap))[0]; \
	__u.__i[1] = ((int *)(ap))[1]; \
	(ap) += 8; \
	__u.__d; }) : \
    ((ty *)(ap += sizeof(ty)))[-1])
E 3
#define va_end(ap) /* empty */
E 5
I 5
D 7
#else /* gcc2 wants to see the '...' token */
E 7
I 7
#else /* gcc2 */
#ifdef __GCC_NEW_VARARGS__	/* gcc 2.4.5 */
#define va_alist __builtin_va_alist
#define	va_dcl	int __builtin_va_alist;
#else				/* gcc 2.3.3 */
E 7
#define	va_dcl	int va_alist; ...
#endif
I 7
#endif
E 7

I 7
#ifdef __GCC_NEW_VARARGS__
#define	va_start(ap)	((ap) = (char *)__builtin_saveregs())
#else
E 7
#define	va_start(ap)	(__builtin_saveregs(), (ap) = (char *)&va_alist)
I 7
#endif
E 7
#define va_end(ap)	/* empty */

/* Note, we can assume C code here; C++ does not use <varargs.h>. */
#define	__va_8byte(ap, ty) ({ \
	union { ty __d; int __i[2]; } __va_u; \
	__va_u.__i[0] = ((int *)(void *)(ap))[0]; \
	__va_u.__i[1] = ((int *)(void *)(ap))[1]; \
	(ap) += 8; __va_u.__d; })
#define va_arg(ap, ty) __extension__ ({ \
    ty __va_temp; \
    __builtin_classify_type(__va_temp) >= 12 ? \
	((ty **)(void *)((ap) += sizeof(ty *)))[-1][0] : \
    sizeof(ty) == 8 ? __va_8byte(ap, ty) : \
	((ty *)(void *)(ap += sizeof(ty)))[-1]; })
E 5

#endif /* !_MACHINE_VARARGS_H_ */
E 1
