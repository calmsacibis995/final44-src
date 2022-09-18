h52776
s 00002/00002/00038
d D 8.1 93/06/06 16:39:31 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00037
d D 4.2 91/04/26 15:40:45 bostic 5 4
c new copyright; att/bsd/shared
e
s 00000/00000/00050
d D 4.1 88/12/04 15:12:08 minshall 4 3
c Release 4.1
e
s 00018/00001/00032
d D 1.3 88/08/28 18:14:10 minshall 3 2
c Add copyright.
e
s 00012/00001/00021
d D 1.2 88/08/28 17:58:02 minshall 2 1
c Lint (and, maybe, copyrights).
e
s 00022/00000/00000
d D 1.1 88/08/28 14:29:44 minshall 1 0
c date and time created 88/08/28 14:29:44 by minshall
e
u
U
t
T
I 1
D 5
/*
D 3
 * External references from the controller.
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
 * External references from the controller.
E 3
E 2
 */

#if	!defined(MSDOS)
extern char *access_api();
extern void movetous(), movetothem(), unaccess_api();
#endif	/* !defined(MSDOS) */

I 2
extern unsigned char
	*memNSchr();	/* Search for a character ANDED, increment by stride */

E 2
extern int
D 2
	TransparentClock,
E 2
I 2
	DataToNetwork(),
E 2
	OutputClock,
I 2
	suspend(),
	TransparentClock,
E 2
	UnLocked;		/* keyboard is UnLocked? */
I 2

E 2
extern void
I 2
	command(),
E 2
	ConnectScreen(),
I 2
	ExitString(),
E 2
	init_inbound(),
	LocalClearScreen(),
	RefreshScreen(),
	RingBell(),
I 2
	setconnmode(),
E 2
	StopScreen(),
	TransOut(),
	TransStop();
E 1
