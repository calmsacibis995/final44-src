h19963
s 00002/00002/00022
d D 8.1 93/06/02 20:06:16 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00022
d D 5.3 92/06/19 15:16:17 bostic 5 4
c use long's explicitly, off_t's are now quads
e
s 00005/00000/00019
d D 5.2 91/04/03 16:19:23 bostic 4 3
c protect all user-level include files against reinclusion
e
s 00014/00014/00005
d D 5.1 91/01/18 18:39:05 bostic 3 2
c new version
e
s 00002/00000/00017
d D 4.2 87/04/06 19:08:03 bostic 2 1
c added RANLIBMAG
e
s 00017/00000/00000
d D 4.1 83/05/03 13:48:12 sam 1 0
c date and time created 83/05/03 13:48:12 by sam
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
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 3

I 4
#ifndef _RANLIB_H_
#define	_RANLIB_H_

E 4
I 2
D 3
#define	RANLIBMAG	"__.SYMDEF"
E 3
I 3
#define	RANLIBMAG	"__.SYMDEF"	/* archive file name */
#define	RANLIBSKEW	3		/* creation time offset */
E 3

E 2
D 3
/*
 * Structure of the __.SYMDEF table of contents for an archive.
 * __.SYMDEF begins with a word giving the number of ranlib structures
 * which immediately follow, and then continues with a string
 * table consisting of a word giving the number of bytes of strings
 * which follow and then the strings themselves.
 * The ran_strx fields index the string table whose first byte is numbered 0.
 */
struct	ranlib {
E 3
I 3
struct ranlib {
E 3
	union {
D 3
		off_t	ran_strx;	/* string table index of */
		char	*ran_name;	/* symbol defined by */
E 3
I 3
D 5
		off_t ran_strx;		/* string table index */
E 5
I 5
		long ran_strx;		/* string table index */
E 5
		char *ran_name;		/* in memory symbol name */
E 3
	} ran_un;
D 3
	off_t	ran_off;		/* library member at this offset */
E 3
I 3
D 5
	off_t ran_off;			/* archive file offset */
E 5
I 5
	long ran_off;			/* archive file offset */
E 5
E 3
};
I 4

#endif /* !_RANLIB_H_ */
E 4
E 1
