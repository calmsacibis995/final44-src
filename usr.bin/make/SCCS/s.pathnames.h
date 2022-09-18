h02557
s 00000/00000/00013
d D 8.2 95/04/28 17:08:24 christos 5 4
c Updated to the latest version from the NetBSD source
e
s 00002/00002/00011
d D 8.1 93/06/06 15:16:57 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00012
d D 5.3 93/02/27 10:32:12 bostic 3 2
c allow system make file to be replaced
e
s 00001/00011/00012
d D 5.2 90/06/01 17:09:31 bostic 2 1
c new copyright notice
e
s 00023/00000/00000
d D 5.1 90/06/01 17:06:29 bostic 1 0
c date and time created 90/06/01 17:06:29 by bostic
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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

#define	_PATH_OBJDIR		"obj"
#define	_PATH_DEFSHELLDIR	"/bin"
D 3
#define	_PATH_DEFSYSMK		"/usr/share/mk/sys.mk"
E 3
I 3
#define	_PATH_DEFSYSMK		"sys.mk"
E 3
#define	_PATH_DEFSYSPATH	"/usr/share/mk"
E 1
