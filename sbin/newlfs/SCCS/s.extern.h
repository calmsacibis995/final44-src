h12770
s 00002/00002/00017
d D 8.2 95/05/24 19:45:44 margo 3 2
c Add support for fragments to make_lfs.
e
s 00002/00002/00017
d D 8.1 93/06/05 11:07:13 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00000/00000
d D 5.1 91/09/19 10:18:47 bostic 1 0
c date and time created 91/09/19 10:18:47 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

u_long	cksum __P((void *, size_t));
u_short	dkcksum __P((struct disklabel *));
void	fatal __P((const char *fmt, ...));
u_int	log2 __P((u_int));
D 3
int	make_lfs
	    __P((int, struct disklabel *, struct partition *, int, int, int));
E 3
I 3
int	make_lfs __P((int, struct disklabel *, struct partition *, int,
		int, int, int));
E 3
int	mkfs __P((struct partition *, char *, int, int));

extern char	*progname;
extern char	*special;
E 1
