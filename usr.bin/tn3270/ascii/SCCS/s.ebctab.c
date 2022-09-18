h53149
s 00000/00000/00069
d D 4.1 88/12/04 15:11:37 minshall 5 4
c Release 4.1
e
s 00010/00005/00059
d D 1.4 88/06/29 19:59:43 bostic 4 3
c install approved copyright notice
e
s 00016/00004/00048
d D 1.3 88/03/28 12:54:39 bostic 3 2
c add Berkeley specific header
e
s 00003/00003/00049
d D 1.2 87/05/12 11:17:46 minshall 2 1
c 'msdos' -> 'MSDOS'.
e
s 00052/00000/00000
d D 1.1 87/05/10 11:28:04 minshall 1 0
c date and time created 87/05/10 11:28:04 by minshall
e
u
U
t
T
I 1
/*
D 3
 * ebcdic to ascii translation tables
E 3
I 3
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 4
E 3
 */

D 3
#ifndef	lint
static	char	sccsid[] = "@(#)ebctab.c	3.1  10/29/86";
#endif	/* ndef lint */
E 3
I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * ebcdic to ascii translation tables
 */
E 3

#include "ascebc.h"

unsigned char	ebcasc[NEBCASC][NEBC] = {
/* 00 */   ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* 08 */   ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* 10 */   ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* 18 */   ' ',  ' ',  ' ',  ' ',  '*',  ' ',  ';',  ' ',
/* 20 */   ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* 28 */   ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* 30 */   ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* 38 */   ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* 40 */   ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',

/* 48 */   ' ',  ' ', 
D 2
#if	!defined(msdos)
E 2
I 2
#if	!defined(MSDOS)
E 2
        /* 4A */       '\\',
D 2
#else	/* !defined(msdos) */
E 2
I 2
#else	/* !defined(MSDOS) */
E 2
        /* 4A */       '\233',		/* PC cent sign */
D 2
#endif	/* !defined(msdos) */
E 2
I 2
#endif	/* !defined(MSDOS) */
E 2
        /* 4B */              '.',  '<',  '(',  '+',  '|',

/* 50 */   '&',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* 58 */   ' ',  ' ',  '!',  '$',  '*',  ')',  ';',  '^',
/* 60 */   '-',  '/',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* 68 */   ' ',  ' ',  '|',  ',',  '%',  '_',  '>',  '?',
/* 70 */   ' ',  '^',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* 78 */   ' ',  '`',  ':',  '#',  '@', '\'',  '=',  '"',
/* 80 */   ' ',  'a',  'b',  'c',  'd',  'e',  'f',  'g',
/* 88 */   'h',  'i',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* 90 */   ' ',  'j',  'k',  'l',  'm',  'n',  'o',  'p',
/* 98 */   'q',  'r',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* A0 */   ' ',  '~',  's',  't',  'u',  'v',  'w',  'x',
/* A8 */   'y',  'z',  ' ',  ' ',  ' ',  '[',  ' ',  ' ',
/* B0 */   ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* B8 */   ' ',  ' ',  ' ',  ' ',  ' ',  ']',  ' ',  ' ',
/* C0 */   '{',  'A',  'B',  'C',  'D',  'E',  'F',  'G',
/* C8 */   'H',  'I',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* D0 */   '}',  'J',  'K',  'L',  'M',  'N',  'O',  'P',
/* D8 */   'Q',  'R',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* E0 */  '\\',  ' ',  'S',  'T',  'U',  'V',  'W',  'X',
/* E8 */   'Y',  'Z',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
/* F0 */   '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',
/* F8 */   '8',  '9',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
};
E 1
