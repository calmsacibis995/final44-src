h39431
s 00000/00001/00013
d D 5.3 90/06/24 23:33:43 bostic 3 2
c move _PATH_MAILDIR into <paths.h>
e
s 00001/00011/00013
d D 5.2 90/06/01 17:42:50 bostic 2 1
c new copyright notice
e
s 00024/00000/00000
d D 5.1 89/05/11 14:41:04 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
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
#define	_PATH_MBOX	"/var/spool/mail"
E 3
#define	_PATH_RWHO	"/var/spool/rwho/whod."
#define	_PATH_SYSLINE	"/usr/src/ucb/sysline"
E 1
