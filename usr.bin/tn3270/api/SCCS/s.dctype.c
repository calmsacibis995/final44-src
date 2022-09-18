h64405
s 00002/00002/00217
d D 8.1 93/06/06 16:36:44 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00216
d D 4.2 91/04/26 15:32:21 bostic 7 6
c new copyright; att/bsd/shared
e
s 00000/00000/00229
d D 4.1 88/12/04 15:11:06 minshall 6 5
c Release 4.1
e
s 00010/00005/00219
d D 3.3 88/06/29 19:55:29 bostic 5 4
c install approved copyright notice
e
s 00013/00001/00211
d D 3.2 88/03/28 13:46:50 bostic 4 3
c add Berkeley specific header
e
s 00000/00000/00212
d D 3.1 87/08/11 10:17:41 minshall 3 2
c New version numbering.
e
s 00004/00000/00208
d D 1.2 87/07/17 10:01:36 minshall 2 1
c Install sccs headers and copyright notices.
e
s 00208/00000/00000
d D 1.1 86/11/11 22:53:58 minshall 1 0
c date and time created 86/11/11 22:53:58 by minshall
e
u
U
t
T
I 4
D 7
/*
 * Copyright (c) 1988 Regents of the University of California.
E 7
I 7
/*-
D 8
 * Copyright (c) 1988 The Regents of the University of California.
E 7
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 5
 */

E 4
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif	/* not lint */
E 4
I 4
#endif /* not lint */
E 4

E 2
I 1
#include "dctype.h"

unsigned char dctype[192] = {
/*00*/
	D_SPACE,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
/*10*/
	D_SPACE,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	0,
	0,
	0,
	0,
/*20*/
	D_DIGIT|D_PRINT,
	D_DIGIT|D_PRINT,
	D_DIGIT|D_PRINT,
	D_DIGIT|D_PRINT,
	D_DIGIT|D_PRINT,
	D_DIGIT|D_PRINT,
	D_DIGIT|D_PRINT,
	D_DIGIT|D_PRINT,
	D_DIGIT|D_PRINT,
	D_DIGIT|D_PRINT,
	0,
	0,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
/*30*/
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
	0,
	0,
	0,
	0,
	D_PUNCT|D_PRINT,
	0,
	D_PUNCT|D_PRINT,
	0,
	0,
/*40*/
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
/*50*/
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
/*60*/
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
/*70*/
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
/*80*/
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
/*90*/
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	D_LOWER|D_PRINT,
	0,
	0,
	0,
	0,
	0,
	0,
/*A0*/
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
/*B0*/
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	D_UPPER|D_PRINT,
	0,
	0,
	0,
	0,
	D_PUNCT|D_PRINT,
	D_PUNCT|D_PRINT,
};
E 1
