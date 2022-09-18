h21095
s 00002/00002/00082
d D 8.1 93/06/06 16:36:33 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00081
d D 4.2 91/04/26 15:32:18 bostic 7 6
c new copyright; att/bsd/shared
e
s 00000/00000/00094
d D 4.1 88/12/04 15:11:05 minshall 6 5
c Release 4.1
e
s 00010/00005/00084
d D 3.3 88/06/29 19:55:21 bostic 5 4
c install approved copyright notice
e
s 00015/00004/00074
d D 3.2 88/03/28 13:46:40 bostic 4 3
c add Berkeley specific header
e
s 00000/00000/00078
d D 3.1 87/08/11 10:17:46 minshall 3 2
c New version numbering.
e
s 00001/00001/00077
d D 1.2 87/07/17 10:01:41 minshall 2 1
c Install sccs headers and copyright notices.
e
s 00078/00000/00000
d D 1.1 87/06/19 12:37:11 minshall 1 0
c date and time created 87/06/19 12:37:11 by minshall
e
u
U
t
T
I 1
D 7
/*
D 4
 * Ascii<->Ebcdic translation tables.
E 4
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
E 4
 */

D 4
#ifndef	lint
D 2
static	char	sccsid[] = "@(#)asctab.c	3.1  10/29/86";
E 2
I 2
static	char	sccsid[] = "%W% (Berkeley) %G%";
E 2
#endif	/* ndef lint */
E 4
I 4
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

I 4
/*
 * Ascii<->Ebcdic translation tables.
 */
E 4

#include "asc_ebc.h"

unsigned char asc_ebc[NASCII]	= {

/* 00 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 08 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 10 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 18 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 20 */   0x40,  0x5A,  0x7F,  0x7B,  0x5B,  0x6C,  0x50,  0x7D,
/* 28 */   0x4D,  0x5D,  0x5C,  0x4E,  0x6B,  0x60,  0x4B,  0x61,
/* 30 */   0xF0,  0xF1,  0xF2,  0xF3,  0xF4,  0xF5,  0xF6,  0xF7,
/* 38 */   0xF8,  0xF9,  0x7A,  0x5E,  0x4C,  0x7E,  0x6E,  0x6F,
/* 40 */   0x7C,  0xC1,  0xC2,  0xC3,  0xC4,  0xC5,  0xC6,  0xC7,
/* 48 */   0xC8,  0xC9,  0xD1,  0xD2,  0xD3,  0xD4,  0xD5,  0xD6,
/* 50 */   0xD7,  0xD8,  0xD9,  0xE2,  0xE3,  0xE4,  0xE5,  0xE6,
/* 58 */   0xE7,  0xE8,  0xE9,  0xAD,  0xE0,  0xBD,  0x5F,  0x6D,
/* 60 */   0x79,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,  0x87,
/* 68 */   0x88,  0x89,  0x91,  0x92,  0x93,  0x94,  0x95,  0x96,
/* 70 */   0x97,  0x98,  0x99,  0xA2,  0xA3,  0xA4,  0xA5,  0xA6,
/* 78 */   0xA7,  0xA8,  0xA9,  0xC0,  0x4F,  0xD0,  0xA1,  0x00,

};

/*
 * ebcdic to ascii translation tables
 */

unsigned char	ebc_asc[NEBC] = {
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
#if	!defined(MSDOS)
        /* 4A */       '\\',
#else	/* !defined(MSDOS) */
        /* 4A */       '\233',		/* PC cent sign */
#endif	/* !defined(MSDOS) */
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
