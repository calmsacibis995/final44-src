h63880
s 00002/00002/00023
d D 8.1 93/06/06 16:12:22 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00024
d D 5.6 91/03/04 13:20:46 bostic 6 5
c wrong path for sccsdiff
e
s 00012/00001/00013
d D 5.5 91/03/04 13:06:10 bostic 5 4
c ANSI -- can't concatenate strings compatibly
e
s 00001/00001/00013
d D 5.4 91/03/02 14:33:30 bostic 4 3
c ANSI preprocessor works a bit differently...
e
s 00001/00001/00013
d D 5.3 90/08/26 14:11:53 karels 3 2
c /usr/local => /usr/local/bin
e
s 00001/00011/00013
d D 5.2 90/06/01 17:41:38 bostic 2 1
c new copyright notice
e
s 00024/00000/00000
d D 5.1 89/05/11 14:41:01 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

#include <paths.h>

D 3
#define	PROGPATH(name)	"/usr/local/name"
E 3
I 3
D 4
#define	PROGPATH(name)	"/usr/local/bin/name"
E 4
I 4
D 5
#define	_SCCSPATH	"/usr/local/bin/"
E 5
I 5
#define	_PATH_SCCSADMIN	"/usr/local/bin/admin"
#define	_PATH_SCCSBDIFF	"/usr/local/bin/bdiff"
#define	_PATH_SCCSCOMB	"/usr/local/bin/comb"
#define	_PATH_SCCSDELTA	"/usr/local/bin/delta"
D 6
#define	_PATH_SCCSDIFF	"/usr/local/bin/diff"
E 6
I 6
#define	_PATH_SCCSDIFF	"/usr/local/bin/sccsdiff"
E 6
#define	_PATH_SCCSGET	"/usr/local/bin/get"
#define	_PATH_SCCSHELP	"/usr/local/bin/help"
#define	_PATH_SCCSPRS	"/usr/local/bin/prs"
#define	_PATH_SCCSPRT	"/usr/local/bin/prt"
#define	_PATH_SCCSRMDEL	"/usr/local/bin/rmdel"
#define	_PATH_SCCSVAL	"/usr/local/bin/val"
#define	_PATH_SCCSWHAT	"/usr/local/bin/what"
E 5
E 4
E 3
#undef _PATH_TMP
#define	_PATH_TMP	"/tmp/sccsXXXXX"
E 1
