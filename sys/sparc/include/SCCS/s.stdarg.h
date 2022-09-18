h48689
s 00006/00002/00084
d D 8.2 93/09/27 14:13:27 torek 7 6
c add gcc 2.4.5 support
e
s 00002/00002/00084
d D 8.1 93/06/11 15:12:47 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00009/00059
d D 7.5 93/05/07 11:13:40 torek 5 4
c handle C++ and struct-values
e
s 00002/00002/00066
d D 7.4 93/04/20 18:54:43 torek 4 3
c spelling
e
s 00023/00005/00045
d D 7.3 92/10/15 21:18:13 torek 3 2
c compensate for gcc 2 being smarter than Sun calling conventions
e
s 00005/00000/00045
d D 7.2 92/07/21 16:41:40 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00045/00000/00000
d D 7.1 92/07/13 00:43:07 torek 1 0
c date and time created 92/07/13 00:43:07 by torek
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
 * from: $Header: stdarg.h,v 1.5 92/06/17 06:10:29 torek Exp $
E 3
I 3
D 4
 * from: $Header: stdarg.h,v 1.6 92/10/02 00:08:01 torek Exp $
E 4
I 4
D 5
 * from: $Header: stdarg.h,v 1.7 92/11/26 02:04:47 torek Exp $
E 5
I 5
D 7
 * from: $Header: stdarg.h,v 1.8 93/05/07 18:10:14 torek Exp $
E 7
I 7
 * from: $Header: stdarg.h,v 1.9 93/09/27 21:12:38 torek Exp $
E 7
E 5
E 4
E 3
 */

/*
 * SPARC stdarg.h
 */

#ifndef _MACHINE_STDARG_H
#define _MACHINE_STDARG_H

typedef char *va_list;

/*
 * va_start sets ap to point to the first variable argument.
 * The `last fixed argument' parameter l is ignored (and should
 * never have been included in the ANSI standard!).
 *
 * va_end cleans up after va_start.  There is nothing to do there.
 */
I 7
#ifdef __GCC_NEW_VARARGS__	/* gcc 2.4.5 */
#define va_start(ap, l)	((ap) = (char *)__builtin_saveregs())
#else				/* gcc 2.3.3 */
E 7
#define va_start(ap, l)	(__builtin_saveregs(), \
D 7
			 ap = (char *)__builtin_next_arg())
E 7
I 7
			 (ap) = (char *)__builtin_next_arg())
#endif
E 7
#define va_end(ap)	/* empty */

I 3
#if __GNUC__ == 1
#define __extension__	/* hack for bootstrapping via gcc 1.x */
#endif

E 3
/*
D 3
 * va_arg picks up the next argument of type `t'.  Appending an
 * asterisk to t must produce a pointer to t (i.e., t may not be,
 * e.g., `int (*)()').  In addition, t must not be any type which
E 3
I 3
 * va_arg picks up the next argument of type `ty'.  Appending an
 * asterisk to ty must produce a pointer to ty (i.e., ty may not be,
 * e.g., `int (*)()').  In addition, ty must not be any type which
E 3
 * undergoes promotion to some other type (e.g., char): it must
 * be the promoted type instead.
I 3
 *
 * Gcc-2.x tries to use ldd/std for double and quad_t values, but Sun's
 * brain-damaged calling convention does not quad-align these.  Thus,
 * for 8-byte arguments, we have to pick up the actual value four bytes
 * at a time, and use type punning (i.e., a union) to produce the result.
 * (We could also do this with a libc function, actually, by returning
 * 8 byte integers in %o0+%o1 and the same 8 bytes as a double in %f0+%f1.)
I 5
 *
 * Note: we cannot use the union trick (which generates better code) for
 * C++, since `ty' might be a type with a constructor (these may not appear
 * in a union).
 *
 * The extraneous casts through `void *' avoid gcc alignment warnings.
E 5
E 3
 */
D 3
#define va_arg(ap, t)	(((t *)(ap += sizeof(t)))[-1])
E 3
I 3
D 5
#define va_arg(ap, ty) \
    (sizeof(ty) == 8 ? __extension__ ({ \
	union { ty __d; int __i[2]; } __u; \
	__u.__i[0] = ((int *)(ap))[0]; \
	__u.__i[1] = ((int *)(ap))[1]; \
	(ap) += 8; \
	__u.__d; }) : \
    ((ty *)(ap += sizeof(ty)))[-1])
E 5
I 5
#ifdef __cplusplus
#define	__va_8byte(ap, ty) ({ \
	int __va_i[2]; \
	__va_i[0] = ((int *)(void *)(ap))[0]; \
	__va_i[1] = ((int *)(void *)(ap))[1]; \
	(ap) += 8; *(ty *)(void *)__va_i; })
#else
#define	__va_8byte(ap, ty) ({ \
	union { ty __d; int __i[2]; } __va_u; \
	__va_u.__i[0] = ((int *)(void *)(ap))[0]; \
	__va_u.__i[1] = ((int *)(void *)(ap))[1]; \
	(ap) += 8; __va_u.__d; })
#endif /* __cplusplus */

#define va_arg(ap, ty) __extension__ ({ \
    ty __va_temp; /* to check for invisible-ptr struct-valued args */ \
    __builtin_classify_type(__va_temp) >= 12 ? \
	((ty **)(void *)((ap) += sizeof(ty *)))[-1][0] : \
    sizeof(ty) == 8 ? __va_8byte(ap, ty) : \
	((ty *)(void *)(ap += sizeof(ty)))[-1]; })
E 5
E 3

#endif /* _MACHINE_STDARG_H */
E 1
