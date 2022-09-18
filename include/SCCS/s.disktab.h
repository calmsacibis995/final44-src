h37123
s 00002/00002/00033
d D 8.1 93/06/02 20:05:14 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00035
d D 5.6 91/04/20 16:40:37 bostic 9 8
c getdiskbyname prototype is in <sys/diskabel.h>
e
s 00005/00000/00032
d D 5.5 91/04/03 16:09:59 bostic 8 7
c protect all user-level include files against reinclusion
e
s 00001/00011/00031
d D 5.4 90/06/01 14:00:31 bostic 7 6
c new copyright notice
e
s 00014/00003/00028
d D 5.3 88/09/30 12:33:50 bostic 6 5
c add Berkeley copyright notice
e
s 00002/00000/00029
d D 5.2 85/10/01 20:22:11 mckusick 5 4
c add fields for bad sector forwarding and sector offset addressing
e
s 00007/00001/00022
d D 5.1 85/05/30 09:35:32 dist 4 3
c Add copyright
e
s 00001/00001/00022
d D 4.3 83/08/11 23:17:03 sam 3 2
c standardize sccs keyword lines
e
s 00000/00001/00023
d D 4.2 83/03/06 12:44:12 sam 2 1
c crud
e
s 00024/00000/00000
d D 4.1 83/03/06 12:42:55 sam 1 0
c date and time created 83/03/06 12:42:55 by sam
e
u
U
t
T
I 1
D 3
/*	%W% (Berkeley) %G%	*/
E 3
I 3
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*
D 6
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
D 10
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 7
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
 *
 *	%W% (Berkeley) %G%
 */
E 4
E 3

I 8
#ifndef	_DISKTAB_H_
#define	_DISKTAB_H_

E 8
/*
 * Disk description table, see disktab(5)
 */
#define	DISKTAB		"/etc/disktab"
D 2
#define	DISKNMLG	32
E 2

struct	disktab {
	char	*d_name;		/* drive name */
	char	*d_type;		/* drive type */
	int	d_secsize;		/* sector size in bytes */
	int	d_ntracks;		/* # tracks/cylinder */
	int	d_nsectors;		/* # sectors/track */
	int	d_ncylinders;		/* # cylinders */
	int	d_rpm;			/* revolutions/minute */
I 5
	int	d_badsectforw;		/* supports DEC bad144 std */
	int	d_sectoffset;		/* use sect rather than cyl offsets */
E 5
	struct	partition {
		int	p_size;		/* #sectors in partition */
		short	p_bsize;	/* block size in bytes */
		short	p_fsize;	/* frag size in bytes */
	} d_partitions[8];
};

D 9
struct	disktab *getdiskbyname();
I 8

E 9
#endif /* !_DISKTAB_H_ */
E 8
E 1
