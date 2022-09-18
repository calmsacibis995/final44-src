h07190
s 00002/00002/00008
d D 8.1 93/06/06 14:59:46 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00009
d D 5.5 90/06/01 16:55:44 bostic 5 4
c new copyright notice
e
s 00001/00001/00019
d D 5.4 90/03/11 12:17:41 bostic 4 3
c rename to locate command
e
s 00000/00002/00020
d D 5.3 90/03/06 11:09:07 bostic 3 2
c rename fast find code as locate; don't need paths.h anymore
e
s 00001/00001/00021
d D 5.2 89/05/19 19:10:30 bostic 2 1
c find.database moves to /var
e
s 00022/00000/00000
d D 5.1 89/05/11 14:40:49 bostic 1 0
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
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include <paths.h>

E 3
D 2
#define	_PATH_FCODES	"/usr/libdata/find.database"
E 2
I 2
D 4
#define	_PATH_FCODES	"/var/db/find.database"
E 4
I 4
#define	_PATH_FCODES	"/var/db/locate.database"
E 4
E 2
E 1
