h09324
s 00002/00002/00015
d D 8.1 93/06/06 16:36:59 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00014
d D 4.2 91/04/26 15:32:24 bostic 8 7
c new copyright; att/bsd/shared
e
s 00000/00000/00027
d D 4.1 88/12/04 15:11:12 minshall 7 6
c Release 4.1
e
s 00010/00005/00017
d D 3.3 88/06/29 19:55:33 bostic 6 5
c install approved copyright notice
e
s 00014/00002/00008
d D 3.2 88/03/28 13:46:55 bostic 5 4
c add Berkeley specific header
e
s 00000/00000/00010
d D 3.1 87/08/11 10:17:41 minshall 4 3
c New version numbering.
e
s 00002/00000/00008
d D 1.3 87/07/17 10:01:34 minshall 3 2
c Install sccs headers and copyright notices.
e
s 00001/00001/00007
d D 1.2 87/05/28 17:22:34 minshall 2 1
c Size problems.
e
s 00008/00000/00000
d D 1.1 87/05/28 15:33:24 minshall 1 0
c date and time created 87/05/28 15:33:24 by minshall
e
u
U
t
T
I 1
D 8
/*
I 5
 * Copyright (c) 1988 Regents of the University of California.
E 8
I 8
/*-
D 9
 * Copyright (c) 1988 The Regents of the University of California.
E 8
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 6
 *
 *	%W% (Berkeley) %G%
 */

/*
E 5
 * Define the translate tables used to go between 3270 display code
 * and ascii
I 3
D 5
 *
 * %W% (Berkeley) %G%
E 5
E 3
 */

extern unsigned char
	disp_asc[256],		/* Goes between display code and ascii */
D 2
	asc_disp[128];		/* Goes between ascii and display code */
E 2
I 2
	asc_disp[256];		/* Goes between ascii and display code */
E 2
E 1
