h06014
s 00002/00002/00029
d D 8.1 93/06/06 15:04:40 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00030
d D 5.5 91/11/20 16:27:15 bostic 5 4
c add affiliation for Oz
e
s 00020/00005/00011
d D 5.4 91/09/03 11:38:24 bostic 4 3
c New version from Oz Yigit; BSD-ized
e
s 00001/00011/00015
d D 5.3 90/06/01 16:10:03 bostic 3 2
c new copyright notice
e
s 00007/00001/00019
d D 5.2 89/08/28 15:50:04 bostic 2 1
c pathnames for new version from Ozan Yigit
e
s 00020/00000/00000
d D 5.1 89/05/11 14:40:40 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
I 4
 * This code is derived from software contributed to Berkeley by
D 5
 * Ozan Yigit.
E 5
I 5
 * Ozan Yigit at York University.
E 5
 *
E 4
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 2
#define	_PATH_TMP	"/tmp/m4aXXXXX"
E 2
I 2
/*
D 4
 * definitions of diversion files. If the name of
 * the file is changed, adjust UNIQUE to point to the
 * wildcard (*) character in the filename.
E 4
I 4
 * Definitions of diversion files.  If the name of the file is changed,
 * adjust UNIQUE to point to the wildcard (*) character in the filename.
E 4
 */
D 4
#define	DIVNAM	"/tmp/m4*XXXXXX"	/* unix diversion files */
#define	UNIQUE	7			/* unique char location */
E 4
I 4

#ifdef msdos
#define _PATH_DIVNAME	"\\M4*XXXXXX"		/* msdos diversion files */
#define	UNIQUE		3			/* unique char location */
#endif

#ifdef unix
#define _PATH_DIVNAME	"/tmp/m4.0XXXXXX"	/* unix diversion files */
#define UNIQUE		8			/* unique char location */
#endif

#ifdef vms
#define _PATH_DIVNAME	"sys$login:m4*XXXXXX"	/* vms diversion files */
#define UNIQUE		12			/* unique char location */
#endif
E 4
E 2
E 1
