h00721
s 00002/00002/00010
d D 8.1 93/06/09 22:50:01 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00012
d D 5.4 90/08/27 13:42:55 eric 4 3
c don't redefine _PATH_TMP; don't assume it begins "/tmp/";
c tmpfile => tempfile for System V
e
s 00001/00011/00013
d D 5.3 90/06/01 17:32:26 bostic 3 2
c new copyright notice
e
s 00000/00001/00024
d D 5.2 89/06/04 10:00:30 bostic 2 1
c sendmail -> paths.h
e
s 00025/00000/00000
d D 5.1 89/05/11 14:40:58 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
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

#include <paths.h>

#define	_PATH_RDIST	"rdist"
D 2
#define	_PATH_SENDMAIL	"/usr/libexec/sendmail"
E 2
D 4
#undef _PATH_TMP
#define	_PATH_TMP	"/tmp/rdistXXXXXX"
E 4
E 1
