h22732
s 00002/00002/00025
d D 8.1 93/06/06 16:39:24 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00024
d D 4.2 91/04/26 15:40:44 bostic 5 4
c new copyright; att/bsd/shared
e
s 00000/00000/00037
d D 4.1 88/12/04 15:12:09 minshall 4 3
c Release 4.1
e
s 00018/00001/00019
d D 1.3 88/08/28 18:14:12 minshall 3 2
c Add copyright.
e
s 00002/00000/00018
d D 1.2 88/08/28 17:58:03 minshall 2 1
c Lint (and, maybe, copyrights).
e
s 00018/00000/00000
d D 1.1 88/08/28 17:54:15 minshall 1 0
c date and time created 88/08/28 17:54:15 by minshall
e
u
U
t
T
I 1
D 5
/*
D 3
 * Declarations of routines from the controller.
E 3
I 3
 * Copyright (c) 1988 Regents of the University of California.
E 5
I 5
/*-
D 6
 * Copyright (c) 1988 The Regents of the University of California.
E 5
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
E 3
I 2
 *
I 3
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
E 3
 *	%W% (Berkeley) %G%
I 3
 */

/*
 * Declarations of routines from the controller.
E 3
E 2
 */

extern void
	AddHost(),
	DoReadModified(),
	DoReadBuffer(),
	OptInit(),
	SendToIBM(),
	SendTransparent();

extern int
	DataFrom3270(),
	DataFromNetwork(),
	OptOrder(),
	OutputClock,
	TransparentClock;
E 1
