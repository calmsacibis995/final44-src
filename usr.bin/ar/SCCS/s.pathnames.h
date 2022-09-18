h22740
s 00002/00002/00012
d D 8.1 93/06/06 14:19:42 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00011
d D 5.4 91/04/12 14:29:11 bostic 4 3
c lost the redist include line somewhere
e
s 00006/00006/00006
d D 5.3 91/01/17 18:24:07 bostic 3 2
c new version
e
s 00001/00011/00011
d D 5.2 90/06/01 15:57:33 bostic 2 1
c new copyright notice
e
s 00022/00000/00000
d D 5.1 89/05/11 14:40:35 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1989 The Regents of the University of California.
E 3
I 3
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
E 4
I 4
D 5
 * Copyright (c) 1991 The Regents of the University of California.
E 4
E 3
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 2
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
E 2
I 2
D 3
 * %sccs.include.redist.c%
E 3
I 3
 * This code is derived from software contributed to Berkeley by
 * Hugh Smith at The University of Guelph.
I 4
 *
 * %sccs.include.redist.c%
E 4
E 3
E 2
 *
 *	%W% (Berkeley) %G%
 */

D 3
#define	_PATH_TMP1	"/tmp/vXXXXX"
#define	_PATH_TMP2	"/tmp/v1XXXXX"
#define	_PATH_TMP3	"/tmp/v2XXXXX"
E 3
I 3
#define	_NAME_ARTMP	"ar.XXXXXX"
#define	_PATH_ARTMP	"/tmp/ar.XXXXXX"
E 3
E 1
