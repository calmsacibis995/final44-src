h09832
s 00002/00002/00025
d D 8.1 93/06/10 23:48:58 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00000/00000
d D 7.1 92/06/04 15:55:33 mckusick 1 0
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
 * from: $Hdr: bitmapif.h,v 4.300 91/06/09 06:14:42 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

/*
 *  bitmap interface header
 */
#define	C_ON	1
#define	C_OFF	0

struct	csr_buf {
	int	csr_x;			/*XXX cursor position x	*/
	int	csr_y;			/*XXX cursor position y	*/
	lPoint	csr_p;			/*  cursor point	*/
	int	csr_sw;			/*  cursor activity	*/
	int	csr_number;		/*  which cursor use	*/
}; 
E 1
