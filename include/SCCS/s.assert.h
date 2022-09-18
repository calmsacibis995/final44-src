h42363
s 00005/00000/00034
d D 8.2 94/01/21 16:53:02 bostic 9 8
c add USL's copyright notice
e
s 00002/00002/00032
d D 8.1 93/06/02 20:04:59 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00033
d D 5.3 92/12/03 17:20:09 torek 7 6
c avoid warnings about _assert redeclaration
e
s 00002/00000/00031
d D 5.2 92/06/18 11:36:08 bostic 6 5
c add _assert for backward compatibility
e
s 00018/00015/00013
d D 5.1 92/04/23 15:54:39 bostic 5 4
c ANSI C version, from Chris Torek
e
s 00005/00000/00023
d D 4.4 91/04/03 16:07:50 bostic 4 3
c protect all user-level include files against reinclusion
e
s 00022/00008/00001
d D 4.3 90/05/06 15:52:12 bostic 3 2
c redo from scratch, print out assertion as well as line/file
e
s 00004/00004/00005
d D 4.2 85/01/21 22:21:51 serge 2 1
c clean up
e
s 00009/00000/00000
d D 4.1 83/05/03 13:47:52 sam 1 0
c date and time created 83/05/03 13:47:52 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
E 5
I 5
D 8
 * Copyright (c) 1992 The Regents of the University of California.
E 5
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
I 9
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 9
E 8
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 3

I 4
D 5
#ifndef _ASSERT_H_
#define	_ASSERT_H_
E 5
I 5
/*
 * Unlike other ANSI header files, <assert.h> may usefully be included
 * multiple times, with and without NDEBUG defined.
 */
E 5

I 5
#undef assert
I 7
#undef _assert
E 7

E 5
E 4
D 3
# ifndef NDEBUG
D 2
# define _assert(ex) {if (!(ex)){fprintf(stderr,"Assertion failed: file %s, line %d\n", __FILE__, __LINE__);exit(1);}}
# define assert(ex) {if (!(ex)){fprintf(stderr,"Assertion failed: file %s, line %d\n", __FILE__, __LINE__);exit(1);}}
E 2
I 2
# define _assert(ex)	{if (!(ex)){fprintf(stderr,"Assertion failed: file \"%s\", line %d\n", __FILE__, __LINE__);exit(1);}}
# define assert(ex)	_assert(ex)
E 2
# else
D 2
# define _assert(ex) ;
# define assert(ex) ;
E 2
I 2
# define _assert(ex)
# define assert(ex)
E 2
# endif
E 3
I 3
#ifdef NDEBUG
D 5
#define	assert
#define	_assert
E 5
I 5
#define	assert(e)	((void)0)
I 6
#define	_assert(e)	((void)0)
E 6
E 5
#else
I 6
#define	_assert(e)	assert(e)
E 6
D 5
#define	assert(expression) { \
	if (!(expression)) { \
		(void)fprintf(stderr, \
		    "assertion \"%s\" failed: file \"%s\", line %d\n", \
		    "expression", __FILE__, __LINE__); \
		exit(2); \
	} \
}
#define	_assert(expression)	assert(expression)
E 5
I 5
#ifdef __STDC__
#define	assert(e)	((e) ? (void)0 : __assert(__FILE__, __LINE__, #e))
#else	/* PCC */
#define	assert(e)	((e) ? (void)0 : __assert(__FILE__, __LINE__, "e"))
E 5
#endif
I 5
#endif
E 5
I 4

D 5
#endif /* !_ASSERT_H_ */
E 5
I 5
#include <sys/cdefs.h>

__BEGIN_DECLS
void __assert __P((const char *, int, const char *));
__END_DECLS
E 5
E 4
E 3
E 1
