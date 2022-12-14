h41153
s 00002/00002/00173
d D 8.1 93/06/10 23:49:29 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00171
d D 7.2 92/12/17 02:35:00 utashiro 2 1
c make kernel includes standard
e
s 00175/00000/00000
d D 7.1 92/06/04 15:55:38 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: keyconf.c,v 4.300 91/06/09 06:14:53 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

#ifdef CPU_DOUBLE
D 2
#include "../../iop/keyboard.h"
#include "../../iop/kbreg.h"
E 2
I 2
#include <news3400/iop/keyboard.h>
#include <news3400/iop/kbreg.h>
E 2
#else
D 2
#include "../iop/keyboard.h"
#include "../iop/kbreg.h"
E 2
I 2
#include <news3400/iop/keyboard.h>
#include <news3400/iop/kbreg.h>
E 2
#endif

#ifndef NULL
#define	    NULL	(char *)0
#endif /* NULL */

Pfk_table pfk_init[] = {
/* 00 */	/*	*/	0,	0,	NULL,	0,	NULL,
/* 01 */	/* F1	*/	1,	3,  "\033OP",	0,	NULL,
/* 02 */	/* F2	*/	2,	3,  "\033OQ",	0,	NULL,
/* 03 */	/* F3	*/	3,	3,  "\033OR",	0,	NULL,
/* 04 */	/* F4	*/	4,	3,  "\033OS",	0,	NULL,
/* 05 */	/* F5	*/	5,	3,  "\033OT",	0,	NULL,
/* 06 */	/* F6	*/	6,	3,  "\033OU",	0,	NULL,
/* 07 */	/* F7	*/	7,	3,  "\033OV",	0,	NULL,
/* 08 */	/* F8	*/	8,	3,  "\033OW",	0,	NULL,
/* 09 */	/* F9	*/	9,	3,  "\033OX",	0,	NULL,
/* 10 */	/* F10	*/	10,	3,  "\033OY",	0,	NULL,
/* 11 */	/* PF1	*/	12,	0,	NULL,	0,	NULL,
/* 12 */	/* PF2	*/	13,	0,	NULL,	0,	NULL,
/* 13 */	/* PF3	*/	14,	0,	NULL,	0,	NULL,
/* 14 */	/* PF4	*/	15,	0,	NULL,	0,	NULL,
/* 15 */	/* PF5	*/	16,	0,	NULL,	0,	NULL,
/* 16 */	/* PF6	*/	17,	0,	NULL,	0,	NULL,
/* 17 */	/* PF7	*/	18,	0,	NULL,	0,	NULL,
/* 18 */	/* PF8	*/	19,	0,	NULL,	0,	NULL,
/* 19 */	/* PF9	*/	20,	0,	NULL,	0,	NULL,
/* 20 */	/* PF10	*/	21,	0,	NULL,	0,	NULL,
/* 21 */	/* PF11	*/	22,	0,	NULL,	0,	NULL,
/* 22 */	/* PF12	*/	23,	0,	NULL,	0,	NULL,
/* 23 */	/* ncnv	*/	69,	0,	NULL,	0,	NULL,
/* 24 */	/* conv	*/	71,	0,	NULL,	0,	NULL,
/* 25 */	/* enter*/	74,	0,	NULL,	0,	NULL,
/* 26 */	/* 0	*/	87,	1,	"0",	1,	"0",
/* 27 */	/* 1	*/	83,	1,	"1",	1,	"1",
/* 28 */	/* 2	*/	84,	1,	"2",	1,	"2",
/* 29 */	/* 3	*/	85,	1,	"3",	1,	"3",
/* 30 */	/* 4	*/	79,	1,	"4",	1,	"4",
/* 31 */	/* 5	*/	80,	1,	"5",	1,	"5",
/* 32 */	/* 6	*/	81,	1,	"6",	1,	"6",
/* 33 */	/* 7	*/	75,	1,	"7",	1,	"7",
/* 34 */	/* 8	*/	76,	1,	"8",	1,	"8",
/* 35 */	/* 9	*/	77,	1,	"9",	1,	"9",
/* 36 */	/* .	*/	89,	1,	".",	1,	".",
/* 37 */	/* -	*/	78,	1,	"-",	1,	"/",
/* 38 */	/* +	*/	82,	1,	"+",	1,	"*",
/* 39 */	/* ,	*/	86,	1,	",",	1,	"=",
/* 40 */	/*nenter*/	90,	1,	"\r",	1,	"\r",
/* 41 */	/* up	*/	88,	3,  "\033[A",	3,  "\033[A",
/* 42 */	/* down	*/	92,	3,  "\033[B",	3,  "\033[B",
/* 43 */	/* rignt*/	93,	3,  "\033[C",	3,  "\033[C",
/* 44 */	/* left	*/	91,	3,  "\033[D",	3,  "\033[D",
};

Key_table default_table[] = {
/*	key_flags		normal	shift	ctrl	alt	kana	kshft */
/*  0*/	0,			0,	0,	0,	0,	0,	0,
/*  1*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/*  2*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/*  3*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/*  4*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/*  5*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/*  6*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/*  7*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/*  8*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/*  9*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 10*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 11*/	N|S|C|K|J|O,		0x1b,	0x1b,	0x1b,	0,	0x1b,	0x1b,
/* 12*/	N|S|K|L|ALT_FUNC,	'1',	'!',	0,	0,	0xc7,	0,
/* 13*/ N|S|C|K|L|ALT_FUNC,	'2',	'@',	0x00,	0,	0xcc,	0,
/* 14*/	N|S|C|K|J|L|ALT_FUNC,	'3',	'#',	0x1b,	0,	0xb1,	0xa7,
/* 15*/	N|S|C|K|J|L|ALT_FUNC,	'4',	'$',	0x1c,	0,	0xb3,	0xa9,
/* 16*/	N|S|C|K|J|L|ALT_FUNC,	'5',	'%',	0x1d,	0,	0xb4,	0xaa,
/* 17*/	N|S|C|K|J|R|ALT_FUNC,	'6',	'^',	0x1e,	0,	0xb5,	0xab,
/* 18*/	N|S|C|K|J|R|ALT_FUNC,	'7',	'&',	0x1f,	0,	0xd4,	0xac,
/* 19*/	N|S|C|K|J|R|ALT_FUNC,	'8',	'*',	0x0f,	0,	0xd5,	0xad,
/* 20*/	N|S|K|K|J|R|ALT_FUNC,	'9',	'(',	0,	0,	0xd6,	0xae,
/* 21*/ N|S|K|K|J|R|ALT_FUNC,	'0',	')',	0,	0,	0xdc,	0xa6,
/* 22*/ N|S|K|R|ALT_FUNC,	'-',	'_',	0,	0,	0xce,	0,
/* 23*/ N|S|K|R|ALT_FUNC,	'=',	'+',	0,	0,	0xcd,	0,
/* 24*/	N|S|C|L,		'\\',	'|',	0x1c,	0,	0,	0,
/* 25*/ N|S|C|K|J|O,		'\b',	'\b',	'\b',	0,	'\b',	'\b',
/* 26*/	N|S|C|K|J|O,		'\t',	'\t',	'\t',	0,	'\t',	'\t',
/* 27*/	N|S|C|K|L|CAP_LOCK,	'q',	'Q',	0x11,	0,	0xc0,	0,
/* 28*/	N|S|C|K|L|CAP_LOCK,	'w',	'W',	0x17,	0,	0xc3,	0,
/* 29*/	N|S|C|K|L|J|CAP_LOCK,	'e',	'E',	0x05,	0,	0xb2,	0xa8,
/* 30*/	N|S|C|K|L|CAP_LOCK,	'r',	'R',	0x12,	0,	0xbd,	0,
/* 31*/	N|S|C|K|L|CAP_LOCK,	't',	'T',	0x14,	0,	0xb6,	0,
/* 32*/	N|S|C|K|R|CAP_LOCK,	'y',	'Y',	0x19,	0,	0xdd,	0,
/* 33*/	N|S|C|K|R|CAP_LOCK,	'u',	'U',	0x15,	0,	0xc5,	0,
/* 34*/	N|S|C|K|R|CAP_LOCK,	'i',	'I',	'\t',	0,	0xc6,	0,
/* 35*/	N|S|C|K|R|CAP_LOCK,	'o',	'O',	0x0f,	0,	0xd7,	0,
/* 36*/	N|S|C|K|R|CAP_LOCK,	'p',	'P',	0x10,	0,	0xbe,	0,
/* 37*/	N|S|C|K|R,		'[',	'{',	0x1b,	0,	0xde,	0,
/* 38*/	N|S|C|K|R|J,		']',	'}',	0x1d,	0,	0xdf,	0xa2,
/* 39*/	N|C|K|O,		0x7f,	0,	0x7f,	0,	0x7f,	0,
/* 40*/	PSH_SHFT,		S_CTRL,	0,	0,	0,	0,	0,
/* 41*/	N|S|C|K|L|CAP_LOCK,	'a',	'A',	0x01,	0,	0xc1,	0,
/* 42*/	N|S|C|K|L|CAP_LOCK,	's',	'S',	0x13,	0,	0xc4,	0,
/* 43*/	N|S|C|K|L|CAP_LOCK,	'd',	'D',	0x04,	0,	0xbc,	0,
/* 44*/	N|S|C|K|L|CAP_LOCK,	'f',	'F',	0x06,	0,	0xca,	0,
/* 45*/	N|S|C|K|L|CAP_LOCK,	'g',	'G',	0x07,	0,	0xb7,	0,
/* 46*/	N|S|C|K|R|CAP_LOCK,	'h',	'H',	'\b',	0,	0xb8,	0,
/* 47*/	N|S|C|K|R|CAP_LOCK,	'j',	'J',	'\n',	0,	0xcf,	0,
/* 48*/	N|S|C|K|R|CAP_LOCK,	'k',	'K',	0x0b,	0,	0xc9,	0,
/* 49*/	N|S|C|K|R|CAP_LOCK,	'l',	'L',	'\f',	0,	0xd8,	0,
/* 50*/	N|S|K|R,		';',	':',	0,	0,	0xda,	0,
/* 51*/	N|S|K|L,		'\'',	'"',	0,	0,	0xb9,	0,
/* 52*/	N|S|C|K|L|J,		'`',	'~',	0x1e,	0,	0xd1,	0xa3,
/* 53*/	N|S|C|K|J|O,		'\r',	'\r',	'\r',	0,	'\r',	'\r',
/* 54*/	PSH_SHFT,		S_LSHFT,0,	0,	0,	0,	0,
/* 55*/	N|S|C|K|J|L|CAP_LOCK,	'z',	'Z',	0x1a,	0,	0xc2,	0xaf,
/* 56*/	N|S|C|K|L|CAP_LOCK,	'x',	'X',	0x18,	0,	0xbb,	0,
/* 57*/	N|S|C|K|L|CAP_LOCK,	'c',	'C',	0x03,	0,	0xbf,	0,
/* 58*/	N|S|C|K|L|CAP_LOCK,	'v',	'V',	0x16,	0,	0xcb,	0,
/* 59*/	N|S|C|K|L|CAP_LOCK,	'b',	'B',	0x02,	0,	0xba,	0,
/* 60*/	N|S|C|K|R|CAP_LOCK,	'n',	'N',	0x0e,	0,	0xd0,	0,
/* 61*/	N|S|C|K|R|CAP_LOCK,	'm',	'M',	'\r',	0,	0xd3,	0,
/* 62*/	N|S|K|J|R,		',',	'<',	0,	0,	0xc8,	0xa4,
/* 63*/	N|S|K|J|R,		'.',	'>',	0,	0,	0xd9,	0xa1,
/* 64*/	N|S|C|K|J|R,		'/',	'?',	0x1f,	0,	0xd2,	0xa5,
/* 65*/	K|J,			0,	0,	0,	0,	0xdb,	0xb0,
/* 66*/	PSH_SHFT,		S_RSHFT,0,	0,	0,	0,	0,
/* 67*/	PSH_SHFT|NOT_REPT,	S_ALT,	0,	0,	0,	0,	0,
/* 68*/	PSH_SHFT|NOT_REPT,	S_CAPS,	0,	0,	0,	0,	0,
/* 69*/	PRG_FUNC|NOT_REPT,	0,	0,	0,	0,	0,	0,
/* 70*/	N|S|C|K|J|O,		' ',	' ',	0x00,	0,	' ',	' ',
/* 71*/	PRG_FUNC|NOT_REPT,	0,	0,	0,	0,	0,	0,
/* 72*/	SW_SHFT|NOT_REPT,	S_AN,	0,	0,	0,	0,	0,
/* 73*/	SW_SHFT|NOT_REPT,	S_KANA,	0,	0,	0,	0,	0,
/* 74*/	PRG_FUNC|NOT_REPT,	0,	0,	0,	0,	0,	0,
/* 75*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 76*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 77*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 78*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 79*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 80*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 81*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 82*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 83*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 84*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 85*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 86*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 87*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 88*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 89*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 90*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 91*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 92*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
/* 93*/	PRG_FUNC,		0,	0,	0,	0,	0,	0,
};

#define	PFK_SIZE	sizeof(pfk_init)/sizeof(Pfk_table)
int N_Pfk = PFK_SIZE;
Pfk_table pfk_table[PFK_SIZE];
E 1
