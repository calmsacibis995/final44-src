h65046
s 00002/00002/00028
d D 8.1 93/06/04 13:07:07 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00000/00000
d D 5.1 91/01/20 21:34:53 bostic 1 0
c new stdio
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * I/O descriptors for __sfvwrite().
 */
struct __siov {
	void	*iov_base;
	size_t	iov_len;
};
struct __suio {
	struct	__siov *uio_iov;
	int	uio_iovcnt;
	int	uio_resid;
};

#if __STDC__ || c_plusplus
extern int __sfvwrite(FILE *, struct __suio *);
#else
extern int __sfvwrite();
#endif
E 1
