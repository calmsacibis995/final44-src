h06835
s 00002/00002/00032
d D 8.1 93/06/10 23:49:50 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00000/00000
d D 7.1 92/06/04 15:55:41 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: vt100esc.h,v 4.300 91/06/09 06:15:01 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

/*
 *  escape sequence structure
 */
struct  esc_sequence {
	char	command;
	char	*terminators;
	int	(*esc_func)();
};

/*
 *  key pad structure
 */

struct	key_pad {
	char	kpd_numeric;
	char	kpd_applic;
};

#define	NUMERIC	0
#define	APPLIC	1
E 1
