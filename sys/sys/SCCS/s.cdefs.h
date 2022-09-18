h37586
s 00002/00001/00095
d D 8.8 95/01/09 18:16:14 cgd 15 14
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00000/00000/00096
d D 8.7 94/01/21 14:33:59 bostic 14 12
c yank to 8.7 -- there's an 8.6 out there that has the #ifndef consistency
c cahnges.  We can't do it here because Eric has been redistributing cdefs.h
c with sendmail.
e
s 00003/00003/00093
d R 8.6 94/01/04 16:16:25 bostic 13 12
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00005/00003/00091
d D 8.5 94/01/04 10:52:01 bostic 12 11
c Mike's new comment
e
s 00007/00001/00087
d D 8.4 94/01/04 09:33:41 bostic 11 10
c provide a way to leave ANSI C variables alone, and delete them 
c by default
e
s 00037/00021/00051
d D 8.3 94/01/03 17:58:38 bostic 10 9
c use latest BSDI version of <sys/cdefs.h>
e
s 00004/00000/00068
d D 8.2 93/10/04 16:07:14 bostic 9 8
c if __STDC__, but not __GNUC__, and not __cplusplus, toss inline
e
s 00002/00002/00066
d D 8.1 93/06/02 19:52:42 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00000/00052
d D 7.7 92/03/02 20:13:28 torek 7 6
c add dead and pure function qualifiers, with appropiate #ifdef's
e
s 00016/00011/00036
d D 7.6 91/05/04 14:59:45 karels 6 5
c attempt to clarify comment, move ansi/traditional cognates next to each other
e
s 00010/00005/00037
d D 7.5 91/03/04 11:19:27 bostic 5 4
c comments about what's really going on
e
s 00028/00013/00014
d D 7.4 91/02/05 17:03:53 bostic 4 3
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00011/00026
d D 7.3 90/06/28 22:00:51 bostic 3 2
c new copyright notice
e
s 00001/00001/00036
d D 7.2 90/05/29 19:29:54 bostic 2 1
c C++ needs prototypes, too
e
s 00037/00000/00000
d D 7.1 89/02/16 15:18:53 bostic 1 0
c date and time created 89/02/16 15:18:53 by bostic
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1988 The Regents of the University of California.
E 6
I 6
D 8
 * Copyright (c) 1991 The Regents of the University of California.
E 6
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
I 10
 * This code is derived from software contributed to Berkeley by
 * Berkeley Software Design, Inc.
 *
E 10
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 4
/*
 * This file is designed to ease the porting from standard C to ANSI C.
 * It will eventually go away.
 * Questions to K. Bostic.
 */
E 4
I 4
#ifndef	_CDEFS_H_
#define	_CDEFS_H_
E 4

D 2
#ifdef __STDC__
E 2
I 2
D 4
#if __STDC__ || c_plusplus
E 2
#define	CONCAT(x,y)	x ## y
#define	PROTOTYPE(p)	p
#define	STRING(x)	#x
E 4
I 4
#if defined(__cplusplus)
#define	__BEGIN_DECLS	extern "C" {
#define	__END_DECLS	};
E 4
#else
I 4
#define	__BEGIN_DECLS
#define	__END_DECLS
#endif

I 5
/*
D 6
 * The __CONCAT macro is a bit tricky -- make sure you don't put
 * spaces in between its arguments, also you can't use strings in
 * code that's intended for historical compilers.
E 6
I 6
 * The __CONCAT macro is used to concatenate parts of symbol names, e.g.
 * with "#define OLD(foo) __CONCAT(old,foo)", OLD(foo) produces oldfoo.
 * The __CONCAT macro is a bit tricky -- make sure you don't put spaces
 * in between its arguments.  __CONCAT can also concatenate double-quoted
 * strings produced by the __STRING macro, but this only works with ANSI C.
E 6
 */
E 5
#if defined(__STDC__) || defined(__cplusplus)
D 5
#define	__P(protos)	protos
E 5
I 5
#define	__P(protos)	protos		/* full-blown ANSI C */
E 5
#define	__CONCAT(x,y)	x ## y
#define	__STRING(x)	#x
D 5
#else
E 5
I 5
D 6
#else					/* traditional style */
E 6
I 6

I 9
D 10
#if !defined(__GNUC__) && !defined(__cplusplus)
#define	inline
#endif
E 10
I 10
#define	__const		const		/* define reserved names to standard */
#define	__signed	signed
#define	__volatile	volatile
#if defined(__cplusplus)
#define	__inline	inline		/* convert to C++ keyword */
#else
#ifndef __GNUC__
#define	__inline			/* delete GCC keyword */
#endif /* !__GNUC__ */
#endif /* !__cplusplus */
E 10

E 9
#else	/* !(__STDC__ || __cplusplus) */
#define	__P(protos)	()		/* traditional C preprocessor */
#define	__CONCAT(x,y)	x/**/y
#define	__STRING(x)	"x"

E 6
E 5
D 10
#ifdef __GNUC__
D 5
#define	const		__const
E 5
I 5
#define	const		__const		/* GCC: ANSI C with -traditional */
E 5
#define	inline		__inline
#define	signed		__signed
#define	volatile	__volatile
D 6
#else
E 6
I 6

#else	/* !__GNUC__ */
E 10
I 10
#ifndef __GNUC__
#define	__const				/* delete pseudo-ANSI C keywords */
#define	__inline
#define	__signed
#define	__volatile
D 11
#ifdef KERNEL
E 11
I 11
/*
D 12
 * In non-ANSI C environments, new programs will want ANSI C keywords
E 12
I 12
 * In non-ANSI C environments, new programs will want ANSI-only C keywords
E 12
 * deleted from the program and old programs will want them left alone.
D 12
 * Programs using the ANSI C keywords const, inline etc. as variables
 * should define -DNO_ANSI_KEYWORDS.
E 12
I 12
 * When using a compiler other than gcc, programs using the ANSI C keywords
 * const, inline etc. as normal identifiers should define -DNO_ANSI_KEYWORDS.
 * When using "gcc -traditional", we assume that this is the intent; if
 * __GNUC__ is defined but __STDC__ is not, we leave the new keywords alone.
E 12
 */
#ifndef	NO_ANSI_KEYWORDS
E 11
E 10
E 6
E 4
D 5
#define	const
E 5
I 5
#define	const				/* delete ANSI C keywords */
E 5
D 4
#define	volatile
E 4
I 4
#define	inline
E 4
#define	signed
D 4
#define	CONCAT(x,y)	x/**/y
#define	PROTOTYPE(p)	()
#define	STRING(x)	"x"
E 4
I 4
#define	volatile
I 10
#endif
E 10
E 4
D 6
#endif
I 4
D 5
#define	__P(protos)	()
E 5
I 5
#define	__P(protos)	()		/* traditional C preprocessor */
E 5
#define	__CONCAT(x,y)	x/**/y
#define	__STRING(x)	"x"
#endif
E 6
I 6
#endif	/* !__GNUC__ */
#endif	/* !(__STDC__ || __cplusplus) */
E 6

I 7
/*
D 10
 * GCC has extensions for declaring functions as `pure' (always returns
 * the same value given the same inputs, i.e., has no external state and
 * no side effects) and `dead' (nonreturning).  These mainly affect
 * optimization and warnings.  Unfortunately, GCC complains if these are
 * used under strict ANSI mode (`gcc -ansi -pedantic'), hence we need to
 * define them only if compiling without this.
E 10
I 10
 * GCC1 and some versions of GCC2 declare dead (non-returning) and
 * pure (no side effects) functions using "volatile" and "const";
 * unfortunately, these then cause warnings under "-ansi -pedantic".
 * GCC2 uses a new, peculiar __attribute__((attrs)) style.  All of
 * these work for GNU C++ (modulo a slight glitch in the C++ grammar
 * in the distribution version of 2.5.5).
E 10
 */
I 10
D 15
#if !defined(__GNUC__) || __GNUC__ < 2 || __GNUC_MINOR__ < 5
E 15
I 15
#if !defined(__GNUC__) || __GNUC__ < 2 || \
	(__GNUC__ == 2 && __GNUC_MINOR__ < 5)
E 15
#define	__attribute__(x)	/* delete __attribute__ if non-gcc or gcc1 */
E 10
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
D 10
#define __dead __volatile
#define __pure __const
#else
#define __dead
#define __pure
E 10
I 10
#define	__dead		__volatile
#define	__pure		__const
#endif
#endif

/* Delete pseudo-keywords wherever they are not available or needed. */
#ifndef __dead
#define	__dead
#define	__pure
E 10
#endif

E 7
#endif /* !_CDEFS_H_ */
E 4
E 1
