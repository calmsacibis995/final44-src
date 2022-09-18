h58272
s 00002/00002/00026
d D 8.1 93/05/31 17:02:26 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00025
d D 5.8 91/04/08 17:55:17 bostic 8 7
c new copyright; att/bsd/shared
e
s 00002/00001/00036
d D 5.7 89/12/15 11:41:47 bostic 7 6
c make long-word aligned for structure padding
e
s 00009/00017/00028
d D 5.6 89/09/07 08:09:27 bostic 6 5
c do everything in network order
e
s 00001/00000/00044
d D 5.5 89/09/06 16:50:23 bostic 5 4
c change obscene files to be rotated on disk
e
s 00001/00001/00043
d D 5.4 89/09/05 19:54:21 bostic 4 3
c change delimiter string to %<newline> from %%<newline>
e
s 00021/00001/00023
d D 5.3 89/09/05 16:46:57 bostic 3 2
c add Berkeley specific copyright notices
e
s 00013/00015/00011
d D 5.2 89/09/05 15:53:46 bostic 2 1
c new distribution from Ken Arnold
e
s 00026/00000/00000
d D 5.1 86/12/09 13:53:42 bostic 1 0
c date and time created 86/12/09 13:53:42 by bostic
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */
E 2
I 2
D 3
/* $Header: strfile.h,v 1.10 88/07/28 19:11:02 arnold Exp $ */
E 3
I 3
D 8
/*
 * Copyright (c) 1989 The Regents of the University of California.
E 8
I 8
/*-
D 9
 * Copyright (c) 1991 The Regents of the University of California.
E 8
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
 * Ken Arnold.
 *
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
 *
 *	%W% (Berkeley) %G%
 */
E 3
E 2

D 2
/* @(#)strfile.h	1.2 (Berkeley) 5/14/81 */
E 2
I 2
D 6
# ifndef	__STRFILE__
E 6
I 6
#define	STR_ENDSTRING(line,tbl) \
	((line)[0] == (tbl).str_delim && (line)[1] == '\n')
E 6
E 2

D 2
# define	MAXDELIMS	3
E 2
I 2
D 6
# define	__STRFILE__
E 2

/*
 * bits for flag field
 */

# define	STR_RANDOM	0x1
# define	STR_ORDERED	0x2
I 5
# define	STR_ROTATED	0x4
E 5

D 2
struct	strfile {		/* information table */
	unsigned int	str_numstr;		/* # of strings in the file */
	unsigned int	str_longlen;		/* length of longest string */
	unsigned int	str_shortlen;		/* length of shortest string */
	long		str_delims[MAXDELIMS];	/* delimiter markings */
	int		str_flags;		/* bit field for flags */
};
E 2
I 2
D 4
# define	STR_ENDSTRING(line,tbl)	((line)[0] == (tbl).str_delim && (line)[1] == (tbl).str_delim)
E 4
I 4
# define	STR_ENDSTRING(line,tbl)	((line)[0] == (tbl).str_delim && (line)[1] == '\n')
E 4
E 2

E 6
D 2
typedef struct strfile	STRFILE;
E 2
I 2
typedef struct {				/* information table */
I 6
#define	VERSION		1
	unsigned long	str_version;		/* version number */
E 6
	unsigned long	str_numstr;		/* # of strings in the file */
	unsigned long	str_longlen;		/* length of longest string */
	unsigned long	str_shortlen;		/* length of shortest string */
D 6
	unsigned char	str_flags;		/* bit field for flags */
	char		str_delim;		/* delimiting character */
E 6
I 6
#define	STR_RANDOM	0x1			/* randomized pointers */
#define	STR_ORDERED	0x2			/* ordered pointers */
#define	STR_ROTATED	0x4			/* rot-13'd text */
	unsigned long	str_flags;		/* bit field for flags */
D 7
	unsigned char	str_delim;		/* delimiting character */
E 7
I 7
	unsigned char	stuff[4];		/* long aligned space */
#define	str_delim	stuff[0]		/* delimiting character */
E 7
E 6
} STRFILE;
D 6

# endif		/* __STRFILE__ */
E 6
E 2
E 1
