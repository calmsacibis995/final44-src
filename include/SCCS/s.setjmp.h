h51246
s 00005/00000/00067
d D 8.2 94/01/21 16:53:06 bostic 15 14
c add USL's copyright notice
e
s 00002/00002/00065
d D 8.1 93/06/02 20:06:36 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00063
d D 5.8 92/06/27 07:13:16 torek 13 11
c sparc
e
s 00004/00000/00063
d R 5.8 92/06/24 02:19:55 torek 12 11
c sparc
e
s 00001/00001/00062
d D 5.7 92/06/19 17:45:53 mckusick 11 10
c support for luna68k
e
s 00004/00000/00059
d D 5.6 91/09/06 17:53:44 ralph 10 9
c added pmax/mips changes
e
s 00004/00004/00055
d D 5.5 91/06/08 16:27:21 bostic 9 8
c __hp300__ is defined if -ansi is specified, not hp300
e
s 00019/00012/00040
d D 5.4 91/02/22 08:05:57 donn 8 6
c Reorganized declarations to accommodate both ANSI and POSIX.  We still
c don't have implementations of sigsetjmp() and siglongjmp().
e
s 00006/00012/00040
d R 5.4 91/02/21 22:46:21 bostic 7 6
c sigsetjmp changes were wrong; back out for now
e
s 00014/00020/00038
d D 5.3 91/02/05 17:10:50 bostic 6 5
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00001/00057
d D 5.2 90/05/29 19:26:54 bostic 5 4
c C++ wants the prototypes, too
e
s 00031/00007/00027
d D 5.1 90/05/27 11:31:35 bostic 4 3
c POSIX 1003.1: sigsetjmp, siglongjmp, function prototypes
c add i386 values
e
s 00010/00004/00024
d D 4.3 90/05/06 15:55:51 bostic 3 2
c no more AT&T code left, add Berkeley copyright
e
s 00026/00001/00002
d D 4.2 89/10/16 16:17:58 mckusick 2 1
c update for ANSI C from jonathan@comp.vuw.ac.nz (4.3BSD/include/8)
e
s 00003/00000/00000
d D 4.1 83/05/03 13:48:15 sam 1 0
c date and time created 83/05/03 13:48:15 by sam
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
D 14
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
I 15
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 15
E 14
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 3

D 2
typedef int jmp_buf[10];
E 2
I 2
D 6
#ifndef _SETJMP_
#define _SETJMP_
E 6
I 6
#ifndef _SETJMP_H_
#define _SETJMP_H_
E 6

D 4
#ifdef vax
E 4
I 4
D 9
#ifdef hp300
E 9
I 9
D 11
#if defined(hp300) || defined(__hp300__)
E 11
I 11
#if defined(hp300) || defined(__hp300__) || defined(luna68k) || defined(__luna68k__)
E 11
E 9
#define _JBLEN	17
#endif

D 9
#ifdef i386
E 9
I 9
#if defined(i386) || defined(__i386__)
E 9
E 4
#define _JBLEN	10
#endif

I 10
#if defined(mips) || defined(__mips__)
#define _JBLEN	83
#endif

I 13
#if defined(sparc) || defined(__sparc__)
#define _JBLEN	10
#endif

E 13
E 10
D 9
#ifdef tahoe
E 9
I 9
#if defined(tahoe) || defined(__tahoe__)
E 9
#define _JBLEN	10
#endif

D 4
#ifdef hp300
#define _JBLEN	17
E 4
I 4
D 9
#ifdef vax
E 9
I 9
#if defined(vax) || defined(__vax__)
E 9
#define _JBLEN	10
E 4
#endif

I 8
#ifndef _ANSI_SOURCE
E 8
I 4
/*
D 8
 * sigsetjmp/siglongjmp use the first int to decide if the
 * signal mask was saved or not.
E 8
I 8
 * WARNING: sigsetjmp() isn't supported yet, this is a placeholder.
E 8
 */
typedef int sigjmp_buf[_JBLEN + 1];
I 8
#endif /* not ANSI */
E 8

D 8
#ifndef _POSIX_SOURCE
E 8
E 4
typedef int jmp_buf[_JBLEN];
I 4
D 8
#endif
E 8
E 4

D 5
#ifdef __STDC__
E 5
I 5
D 6
#if __STDC__ || c_plusplus
E 5
D 4
extern int setjmp(jmp_buf), _setjmp(jmp_buf);
extern void longjmp(jmp_buf, int), _longjmp(jmp_buf, int);
E 4
I 4
int sigsetjmp(sigjmp_buf, int);
void siglongjmp(sigjmp_buf, int);
E 6
I 6
#include <sys/cdefs.h>

__BEGIN_DECLS
D 8
int sigsetjmp __P((sigjmp_buf, int));
void siglongjmp __P((sigjmp_buf, int));
E 6
#ifndef _POSIX_SOURCE
D 6
extern int setjmp(jmp_buf);
extern int _setjmp(jmp_buf);
extern void longjmp(jmp_buf, int);
extern void _longjmp(jmp_buf, int);
E 6
I 6
int setjmp __P((jmp_buf));
int _setjmp __P((jmp_buf));
void longjmp __P((jmp_buf, int));
void _longjmp __P((jmp_buf, int));
E 6
#endif
E 8
I 8
int	setjmp __P((jmp_buf));
void	longjmp __P((jmp_buf, int));

#ifndef _ANSI_SOURCE
/*
 * WARNING: sigsetjmp() isn't supported yet, this is a placeholder.
 */
int	sigsetjmp __P((sigjmp_buf, int));
void	siglongjmp __P((sigjmp_buf, int));
#endif /* not ANSI */

#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
int	_setjmp __P((jmp_buf));
void	_longjmp __P((jmp_buf, int));
void	longjmperror __P((void));
#endif /* neither ANSI nor POSIX */
E 8
E 4
D 3
#else	/* !__STDC__ */
E 3
I 3
D 6
#else
E 3
D 4
extern int setjmp(), _setjmp();
extern int longjmp(), _longjmp();
E 4
I 4
int sigsetjmp();
void siglongjmp();
#ifndef _POSIX_SOURCE
extern int setjmp();
extern int _setjmp();
extern void longjmp();
extern void _longjmp();
#endif
E 4
D 3
#endif	/* !__STDC__ */

E 3
I 3
#endif
E 3
#endif
E 6
I 6
__END_DECLS

#endif /* !_SETJMP_H_ */
E 6
E 2
E 1
