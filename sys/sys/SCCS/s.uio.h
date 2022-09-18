h08643
s 00002/00004/00055
d D 8.5 94/02/22 15:04:30 bostic 20 19
c uio_seg and uio_rw are used outside the kernel by ktrace/kdump
c and by systat; leave them outside of the #ifdef KERNEL
e
s 00002/00002/00057
d D 8.4 94/02/21 16:56:21 bostic 19 18
c make readv and writev return ssize_t's
e
s 00014/00011/00045
d D 8.3 94/02/21 09:54:25 bostic 18 17
c make iov_len a size_t, note that iov_base should be a void *
c make most of the file #ifdef KERNEL, hopefully nobody uses it...
e
s 00003/00003/00053
d D 8.2 94/01/04 16:16:57 bostic 17 16
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00054
d D 8.1 93/06/02 19:56:31 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00055
d D 7.8 91/04/15 23:22:12 mckusick 15 14
c add pointer to proc (only valid when UIO_USERSPACE set)
e
s 00011/00000/00044
d D 7.7 91/03/07 10:43:33 donn 14 11
c Prototype declarations.
e
s 00011/00000/00044
d R 7.7 91/03/07 10:42:21 donn 13 11
c Prototype declarations.
e
s 00011/00000/00044
d R 7.7 91/03/07 10:41:54 donn 12 11
c Add prototypes for freadv() and writev().
e
s 00003/00003/00041
d D 7.6 91/02/05 17:03:45 bostic 11 10
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00011/00043
d D 7.5 90/06/28 22:01:41 bostic 10 9
c new copyright notice
e
s 00013/00010/00041
d D 7.4 89/05/09 16:35:16 mckusick 9 8
c merge in vnodes
e
s 00006/00000/00045
d D 7.3 89/04/12 16:49:14 mckusick 8 7
c set limits on maximum size of uio's
e
s 00016/00004/00029
d D 7.2 89/01/17 08:23:09 bostic 7 6
c add Berkeley specific copyright notice
e
s 00001/00001/00032
d D 7.1 86/06/04 23:30:50 mckusick 6 5
c 4.3BSD release version
e
s 00001/00001/00032
d D 6.4 86/02/23 23:01:08 karels 5 4
c lint
e
s 00007/00001/00026
d D 6.3 85/06/08 15:11:30 mckusick 4 3
c Add copyright
e
s 00011/00000/00016
d D 6.2 84/07/08 15:47:42 mckusick 3 2
c rework `namei' interface to eliminate global variables
e
s 00000/00000/00016
d D 6.1 83/07/29 06:14:45 sam 2 1
c 4.2 distribution
e
s 00016/00000/00000
d D 4.1 82/09/04 09:27:46 root 1 0
c date and time created 82/09/04 09:27:46 by root
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*
D 6
 * Copyright (c) 1982 Regents of the University of California.
E 6
I 6
D 7
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
D 16
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
D 18
 * Copyright (c) 1982, 1986, 1993
E 18
I 18
 * Copyright (c) 1982, 1986, 1993, 1994
E 18
 *	The Regents of the University of California.  All rights reserved.
E 16
E 7
 *
I 7
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
 *
E 7
 *	%W% (Berkeley) %G%
 */
E 4

I 3
D 11
#ifndef _UIO_
#define	_UIO_
E 11
I 11
D 17
#ifndef _UIO_H_
#define	_UIO_H_
E 17
I 17
#ifndef _SYS_UIO_H_
#define	_SYS_UIO_H_
E 17
E 11

I 18
/*
 * XXX
 * iov_base should be a void *.
 */
E 18
E 3
struct iovec {
D 18
	caddr_t	iov_base;
	int	iov_len;
E 18
I 18
	char	*iov_base;	/* Base address. */
	size_t	 iov_len;	/* Length. */
E 18
};

I 18
D 20
#ifdef KERNEL
E 20
E 18
I 9
enum	uio_rw { UIO_READ, UIO_WRITE };

D 20
/*
 * Segment flag values.
 */
E 20
I 20
/* Segment flag values. */
E 20
D 18
enum	uio_seg {
E 18
I 18
enum uio_seg {
E 18
	UIO_USERSPACE,		/* from user data space */
	UIO_SYSSPACE,		/* from system space */
	UIO_USERISPACE		/* from user I space */
};

I 20
#ifdef KERNEL
E 20
E 9
struct uio {
	struct	iovec *uio_iov;
	int	uio_iovcnt;
D 5
	int	uio_offset;
E 5
I 5
	off_t	uio_offset;
E 5
D 9
	int	uio_segflg;
E 9
	int	uio_resid;
I 9
	enum	uio_seg uio_segflg;
	enum	uio_rw uio_rw;
I 15
	struct	proc *uio_procp;
E 15
E 9
};
D 9

enum	uio_rw { UIO_READ, UIO_WRITE };
I 3

/*
 * Segment flag values (should be enum).
 */
#define UIO_USERSPACE	0		/* from user data space */
#define UIO_SYSSPACE	1		/* from system space */
#define UIO_USERISPACE	2		/* from user I space */
E 9
D 7
#endif
E 7
I 7

I 8
D 18
 /*
  * Limits
  */
E 18
I 18
/*
 * Limits
 */
E 18
#define UIO_MAXIOV	1024		/* max 1K of iov's */
#define UIO_SMALLIOV	8		/* 8 on stack, else malloc */
I 18
#endif /* KERNEL */
E 18

I 14
#ifndef	KERNEL
D 18

E 18
#include <sys/cdefs.h>

__BEGIN_DECLS
D 19
int	readv __P((int, const struct iovec *, int));
int	writev __P((int, const struct iovec *, int));
E 19
I 19
ssize_t	readv __P((int, const struct iovec *, int));
ssize_t	writev __P((int, const struct iovec *, int));
E 19
__END_DECLS
D 18

#endif	/* !KERNEL */

E 18
I 18
#endif /* !KERNEL */
E 18
E 14
E 8
D 11
#endif /* !_UIO_ */
E 11
I 11
D 17
#endif /* !_UIO_H_ */
E 17
I 17
#endif /* !_SYS_UIO_H_ */
E 17
E 11
E 7
E 3
E 1
