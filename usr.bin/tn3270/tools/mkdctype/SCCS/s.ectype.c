h15536
s 00002/00002/00285
d D 8.1 93/06/06 16:49:52 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00284
d D 4.2 91/04/26 16:05:57 bostic 7 6
c new copyright; att/bsd/shared
e
s 00000/00000/00297
d D 4.1 88/12/04 15:13:07 minshall 6 5
c Release 4.1
e
s 00010/00005/00287
d D 3.3 88/06/29 20:04:43 bostic 5 4
c install approved copyright notice
e
s 00010/00003/00282
d D 3.2 88/03/28 12:08:12 bostic 4 3
c add Berkeley specific headers
e
s 00000/00000/00285
d D 3.1 87/08/11 10:20:38 minshall 3 2
c New version numbering.
e
s 00006/00001/00279
d D 1.2 87/07/17 10:05:58 minshall 2 1
c Install sccs headers and copyright notices.
e
s 00280/00000/00000
d D 1.1 86/11/12 16:44:11 minshall 1 0
c date and time created 86/11/12 16:44:11 by minshall
e
u
U
t
T
I 2
D 7
/*
I 4
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
E 4
 *
D 4
 * %W% (Berkeley) %G%
E 4
I 4
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
E 4
 */

E 2
I 1
D 4
#ifndef	lint
E 4
I 4
#ifndef lint
E 4
D 2
static	char	sccsid[] = "@(#)ectype.c	3.1  10/29/86";
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
D 4
#endif	/* ndef lint */
E 4
I 4
#endif /* not lint */
E 4

#include "ectype.h"

char	ectype[] = {
/* 0x00 */
    E_SPACE,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
/* 0x10 */
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
/* 0x20 */
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
/* 0x30 */
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
/* 0x40 */
    E_SPACE,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
/* 0x50 */
    E_PRINT|E_PUNCT,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
/* 0x60 */
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
/* 0x70 */
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
    E_PRINT|E_PUNCT,
/* 0x80 */
    0x00,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
/* 0x90 */
    0x00,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
/* 0xA0 */
    0x00,
    E_PRINT|E_PUNCT,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    E_PRINT|E_LOWER,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
/* 0xB0 */
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
/* 0xC0 */
    E_PRINT|E_PUNCT,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
/* 0xD0 */
    E_PRINT|E_PUNCT,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
/* 0xE0 */
    E_PRINT|E_PUNCT,
    0x00,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    E_PRINT|E_UPPER,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
/* 0xF0 */
    E_PRINT|E_DIGIT,
    E_PRINT|E_DIGIT,
    E_PRINT|E_DIGIT,
    E_PRINT|E_DIGIT,
    E_PRINT|E_DIGIT,
    E_PRINT|E_DIGIT,
    E_PRINT|E_DIGIT,
    E_PRINT|E_DIGIT,
    E_PRINT|E_DIGIT,
    E_PRINT|E_DIGIT,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};
E 1
