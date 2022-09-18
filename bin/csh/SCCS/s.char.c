h00948
s 00002/00002/00283
d D 8.1 93/05/31 16:41:19 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00282
d D 5.10 93/05/27 05:06:32 christos 11 10
c changed _Q,_Q1 to _QF,_QB to avoid conflict with new <ctype.h>
e
s 00000/00000/00285
d D 5.9 93/05/22 19:06:16 christos 10 9
c Fixed gcc -Wall warnings
e
s 00001/00001/00284
d D 5.8 91/08/25 17:16:04 christos 9 8
c fixed core dump with multi-line aliases
e
s 00000/00000/00285
d D 5.7 91/07/19 17:30:19 christos 8 7
c stdio based version; brace glob fix; builtin prototypes
e
s 00001/00001/00284
d D 5.6 91/06/07 11:13:09 bostic 7 6
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00204/00029/00081
d D 5.5 91/06/04 13:31:11 bostic 6 5
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00007/00006/00103
d D 5.4 91/04/04 18:17:32 bostic 5 4
c new copyright; att/bsd/shared
e
s 00019/00019/00090
d D 5.3 86/03/29 07:37:15 lepreau 4 3
c Minor speedups & cleanups:
c replace letter() et al with ctype-like cmap macros and expand cmap to short
c for new LET and DIG bits; use bzero in private calloc; make btell a macro.
e
s 00003/00003/00106
d D 5.2 85/06/06 13:09:15 edward 3 2
c cleaning up after bozos
e
s 00008/00002/00101
d D 5.1 85/06/04 10:55:24 dist 2 1
c Add copyright
e
s 00103/00000/00000
d D 4.1 84/12/13 16:26:23 edward 1 0
c date and time created 84/12/13 16:26:23 by edward
e
u
U
t
T
I 2
D 5
/*
 * Copyright (c) 1980 Regents of the University of California.
D 3
 * All rights reserved.  The Berkeley software License Agreement
E 3
I 3
 * All rights reserved.  The Berkeley Software License Agreement
E 3
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
D 12
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * %sccs.include.redist.c%
E 5
 */

E 2
I 1
#ifndef lint
D 2
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 2
I 2
D 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 3
I 3
D 5
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5
E 3
E 2

D 7
#include "sh.char.h"
E 7
I 7
#include "char.h"
E 7

D 4
char _cmap[256] = {
E 4
I 4
unsigned short _cmap[256] = {
E 4
/*	nul		soh		stx		etx	*/
D 6
	0,		0,		0,		0,
E 6
I 6
	_CTR,		_CTR,		_CTR,		_CTR,
E 6

/*	eot		enq		ack		bel	*/
D 6
	0,		0,		0,		0,
E 6
I 6
	_CTR,		_CTR,		_CTR,		_CTR,
E 6

/*	bs		ht		nl		vt	*/
D 6
	0,		_SP|_META,	_NL|_META,	0,
E 6
I 6
	_CTR,		_CTR|_SP|_META,	_CTR|_NL|_META,	_CTR,
E 6

/*	np		cr		so		si	*/
D 6
	0,		0,		0,		0,
E 6
I 6
	_CTR,		_CTR,		_CTR,		_CTR,
E 6

/*	dle		dc1		dc2		dc3	*/
D 6
	0,		0,		0,		0,
E 6
I 6
	_CTR,		_CTR,		_CTR,		_CTR,
E 6

/*	dc4		nak		syn		etb	*/
D 6
	0,		0,		0,		0,
E 6
I 6
	_CTR,		_CTR,		_CTR,		_CTR,
E 6

/*	can		em		sub		esc	*/
D 6
	0,		0,		0,		0,
E 6
I 6
	_CTR,		_CTR,		_CTR,		_CTR,
E 6

/*	fs		gs		rs		us	*/
D 6
	0,		0,		0,		0,
E 6
I 6
	_CTR,		_CTR,		_CTR,		_CTR,
E 6

/*	sp		!		"		#	*/
D 11
	_SP|_META,	0,		_Q,		_META,
E 11
I 11
	_SP|_META,	0,		_QF,		_META,
E 11

/*	$		%		&		'	*/
D 6
	_DOL,		0,		_META,		_Q,
E 6
I 6
D 11
	_DOL,		0,		_META|_CMD,	_Q,
E 11
I 11
	_DOL,		0,		_META|_CMD,	_QF,
E 11
E 6

/*	(		)		*		+	*/
D 6
	_META,		_META,		_GLOB,		0,
E 6
I 6
	_META|_CMD,	_META,		_GLOB,		0,
E 6

/*	,		-		.		/	*/
	0,		0,		0,		0,

/*	0		1		2		3	*/
D 4
	0,		0,		0,		0,
E 4
I 4
D 6
	_DIG,		_DIG,		_DIG,		_DIG,
E 6
I 6
	_DIG|_XD,	_DIG|_XD,	_DIG|_XD,	_DIG|_XD,
E 6
E 4

/*	4		5		6		7	*/
D 4
	0,		0,		0,		0,
E 4
I 4
D 6
	_DIG,		_DIG,		_DIG,		_DIG,
E 6
I 6
	_DIG|_XD,	_DIG|_XD,	_DIG|_XD,	_DIG|_XD,
E 6
E 4

/*	8		9		:		;	*/
D 4
	0,		0,		0,		_META,
E 4
I 4
D 6
	_DIG,		_DIG,		0,		_META,
E 6
I 6
	_DIG|_XD,	_DIG|_XD,	0,		_META|_CMD,
E 6
E 4

/*	<		=		>		?	*/
	_META,		0,		_META,		_GLOB,

/*	@		A		B		C	*/
D 4
	0,		0,		0,		0,
E 4
I 4
D 6
	0,		_LET,		_LET,		_LET,
E 6
I 6
	0,		_LET|_UP|_XD,	_LET|_UP|_XD,	_LET|_UP|_XD,
E 6
E 4

/*	D		E		F		G	*/
D 4
	0,		0,		0,		0,
E 4
I 4
D 6
	_LET,		_LET,		_LET,		_LET,
E 6
I 6
	_LET|_UP|_XD,	_LET|_UP|_XD,	_LET|_UP|_XD,	_LET|_UP,
E 6
E 4

/*	H		I		J		K	*/
D 4
	0,		0,		0,		0,
E 4
I 4
D 6
	_LET,		_LET,		_LET,		_LET,
E 6
I 6
	_LET|_UP,	_LET|_UP,	_LET|_UP,	_LET|_UP,
E 6
E 4

/*	L		M		N		O	*/
D 4
	0,		0,		0,		0,
E 4
I 4
D 6
	_LET,		_LET,		_LET,		_LET,
E 6
I 6
	_LET|_UP,	_LET|_UP,	_LET|_UP,	_LET|_UP,
E 6
E 4

/*	P		Q		R		S	*/
D 4
	0,		0,		0,		0,
E 4
I 4
D 6
	_LET,		_LET,		_LET,		_LET,
E 6
I 6
	_LET|_UP,	_LET|_UP,	_LET|_UP,	_LET|_UP,
E 6
E 4

/*	T		U		V		W	*/
D 4
	0,		0,		0,		0,
E 4
I 4
D 6
	_LET,		_LET,		_LET,		_LET,
E 6
I 6
	_LET|_UP,	_LET|_UP,	_LET|_UP,	_LET|_UP,
E 6
E 4

/*	X		Y		Z		[	*/
D 4
	0,		0,		0,		_GLOB,
E 4
I 4
D 6
	_LET,		_LET,		_LET,		_GLOB,
E 6
I 6
	_LET|_UP,	_LET|_UP,	_LET|_UP,	_GLOB,
E 6
E 4

/*	\		]		^		_	*/
D 4
	_ESC,		0,		0,		0,
E 4
I 4
D 6
	_ESC,		0,		0,		_LET,
E 6
I 6
	_ESC,		0,		0,		0,
E 6
E 4

/*	`		a		b		c	*/
D 4
	_Q1|_GLOB,	0,		0,		0,
E 4
I 4
D 6
	_Q1|_GLOB,	_LET,		_LET,		_LET,
E 6
I 6
D 9
  _Q1|_GLOB|_CMD|_META,	_LET|_LOW|_XD,	_LET|_LOW|_XD,	_LET|_LOW|_XD,
E 9
I 9
D 11
  _Q1|_GLOB|_META,	_LET|_LOW|_XD,	_LET|_LOW|_XD,	_LET|_LOW|_XD,
E 11
I 11
  _QB|_GLOB|_META,	_LET|_LOW|_XD,	_LET|_LOW|_XD,	_LET|_LOW|_XD,
E 11
E 9
E 6
E 4

/*	d		e		f		g	*/
D 4
	0,		0,		0,		0,
E 4
I 4
D 6
	_LET,		_LET,		_LET,		_LET,
E 6
I 6
	_LET|_LOW|_XD,	_LET|_LOW|_XD,	_LET|_LOW|_XD,	_LET|_LOW,
E 6
E 4

/*	h		i		j		k	*/
D 4
	0,		0,		0,		0,
E 4
I 4
D 6
	_LET,		_LET,		_LET,		_LET,
E 6
I 6
	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,
E 6
E 4

/*	l		m		n		o	*/
D 4
	0,		0,		0,		0,
E 4
I 4
D 6
	_LET,		_LET,		_LET,		_LET,
E 6
I 6
	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,
E 6
E 4

/*	p		q		r		s	*/
D 4
	0,		0,		0,		0,
E 4
I 4
D 6
	_LET,		_LET,		_LET,		_LET,
E 6
I 6
	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,
E 6
E 4

/*	t		u		v		w	*/
D 4
	0,		0,		0,		0,
E 4
I 4
D 6
	_LET,		_LET,		_LET,		_LET,
E 6
I 6
	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,
E 6
E 4

/*	x		y		z		{	*/
D 4
	0,		0,		0,		_GLOB,
E 4
I 4
D 6
	_LET,		_LET,		_LET,		_GLOB,
E 6
I 6
	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,	_GLOB,
E 6
E 4

/*	|		}		~		del	*/
D 6
	_META,		0,		0,		0,
E 6
I 6
	_META|_CMD,	0,		0,		_CTR,

#if defined(SHORT_STRINGS) && !defined(KANJI)
/****************************************************************/
/* 128 - 255 The below is supposedly ISO 8859/1			*/
/****************************************************************/
/*	(undef)		(undef)		(undef)		(undef)		*/
	_CTR,		_CTR,		_CTR,		_CTR,

/*	(undef)		(undef)		(undef)		(undef)		*/
	_CTR,		_CTR,		_CTR,		_CTR,

/*	(undef)		(undef)		(undef)		(undef)		*/
	_CTR,		_CTR,		_CTR,		_CTR,

/*	(undef)		(undef)		(undef)		(undef)		*/
	_CTR,		_CTR,		_CTR,		_CTR,

/*	(undef)		(undef)		(undef)		(undef)		*/
	_CTR,		_CTR,		_CTR,		_CTR,

/*	(undef)		(undef)		(undef)		(undef)		*/
	_CTR,		_CTR,		_CTR,		_CTR,

/*	(undef)		(undef)		(undef)		(undef)		*/
	_CTR,		_CTR,		_CTR,		_CTR,

/*	(undef)		(undef)		(undef)		(undef)		*/
	_CTR,		_CTR,		_CTR,		_CTR,

/*	nobreakspace	exclamdown	cent		sterling	*/
	_SP,		0,		0,		0,

/*	currency	yen		brokenbar	section		*/
	0,		0,		0,		0,

/*	diaeresis	copyright	ordfeminine	guillemotleft	*/
	0,		0,		0,		0,

/*	notsign		hyphen		registered	macron		*/
	0,		0,		0,		0,

/*	degree		plusminus	twosuperior	threesuperior	*/
	0,		0,		0,		0,

/*	acute		mu		paragraph	periodcentered	*/
	0,		0,		0,		0,

/*	cedilla		onesuperior	masculine	guillemotright	*/
	0,		0,		0,		0,

/*	onequarter	onehalf		threequarters	questiondown	*/
	0,		0,		0,		0,

/*	Agrave		Aacute		Acircumflex	Atilde		*/
	_LET|_UP,	_LET|_UP,	_LET|_UP,	_LET|_UP,

/*	Adiaeresis	Aring		AE		Ccedilla	*/
	_LET|_UP,	_LET|_UP,	_LET|_UP,	_LET|_UP,

/*	Egrave		Eacute		Ecircumflex	Ediaeresis	*/
	_LET|_UP,	_LET|_UP,	_LET|_UP,	_LET|_UP,

/*	Igrave		Iacute		Icircumflex	Idiaeresis	*/
	_LET|_UP,	_LET|_UP,	_LET|_UP,	_LET|_UP,

/*	ETH		Ntilde		Ograve		Oacute		*/
	_LET|_UP,	_LET|_UP,	_LET|_UP,	_LET|_UP,

/*	Ocircumflex	Otilde		Odiaeresis	multiply	*/
	_LET|_UP,	_LET|_UP,	_LET|_UP,	0,

/*	Ooblique	Ugrave		Uacute		Ucircumflex	*/
	_LET|_UP,	_LET|_UP,	_LET|_UP,	_LET|_UP,

/*	Udiaeresis	Yacute		THORN		ssharp		*/
	_LET|_UP,	_LET|_UP,	_LET|_UP,	_LET|_LOW,

/*	agrave		aacute		acircumflex	atilde		*/
	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,

/*	adiaeresis	aring		ae		ccedilla	*/
	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,

/*	egrave		eacute		ecircumflex	ediaeresis	*/
	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,

/*	igrave		iacute		icircumflex	idiaeresis	*/
	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,

/*	eth		ntilde		ograve		oacute		*/
	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,

/*	ocircumflex	otilde		odiaeresis	division	*/
	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,	0,

/*	oslash		ugrave		uacute		ucircumflex	*/
	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,

/*	udiaeresis	yacute		thorn		ydiaeresis	*/
	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,	_LET|_LOW,
#endif /* SHORT_STRINGS && !KANJI */
E 6
};
I 6

#ifndef NLS
/* _cmap_lower, _cmap_upper for ISO 8859/1 */

unsigned char _cmap_lower[256] = {
	0000,	0001,	0002,	0003,	0004,	0005,	0006,	0007,
	0010,	0011,	0012,	0013,	0014,	0015,	0016,	0017,
	0020,	0021,	0022,	0023,	0024,	0025,	0026,	0027,
	0030,	0031,	0032,	0033,	0034,	0035,	0036,	0037,
	0040,	0041,	0042,	0043,	0044,	0045,	0046,	0047,
	0050,	0051,	0052,	0053,	0054,	0055,	0056,	0057,
	0060,	0061,	0062,	0063,	0064,	0065,	0066,	0067,
	0070,	0071,	0072,	0073,	0074,	0075,	0076,	0077,
	0100,	0141,	0142,	0143,	0144,	0145,	0146,	0147,
	0150,	0151,	0152,	0153,	0154,	0155,	0156,	0157,
	0160,	0161,	0162,	0163,	0164,	0165,	0166,	0167,
	0170,	0171,	0172,	0133,	0134,	0135,	0136,	0137,
	0140,	0141,	0142,	0143,	0144,	0145,	0146,	0147,
	0150,	0151,	0152,	0153,	0154,	0155,	0156,	0157,
	0160,	0161,	0162,	0163,	0164,	0165,	0166,	0167,
	0170,	0171,	0172,	0173,	0174,	0175,	0176,	0177,
	0200,	0201,	0202,	0203,	0204,	0205,	0206,	0207,
	0210,	0211,	0212,	0213,	0214,	0215,	0216,	0217,
	0220,	0221,	0222,	0223,	0224,	0225,	0226,	0227,
	0230,	0231,	0232,	0233,	0234,	0235,	0236,	0237,
	0240,	0241,	0242,	0243,	0244,	0245,	0246,	0247,
	0250,	0251,	0252,	0253,	0254,	0255,	0256,	0257,
	0260,	0261,	0262,	0263,	0264,	0265,	0266,	0267,
	0270,	0271,	0272,	0273,	0274,	0275,	0276,	0277,
	0340,	0341,	0342,	0343,	0344,	0345,	0346,	0347,
	0350,	0351,	0352,	0353,	0354,	0355,	0356,	0357,
	0360,	0361,	0362,	0363,	0364,	0365,	0366,	0327,
	0370,	0371,	0372,	0373,	0374,	0375,	0376,	0337,
	0340,	0341,	0342,	0343,	0344,	0345,	0346,	0347,
	0350,	0351,	0352,	0353,	0354,	0355,	0356,	0357,
	0360,	0361,	0362,	0363,	0364,	0365,	0366,	0367,
	0370,	0371,	0372,	0373,	0374,	0375,	0376,	0377,
};

unsigned char _cmap_upper[256] = {
	0000,	0001,	0002,	0003,	0004,	0005,	0006,	0007,
	0010,	0011,	0012,	0013,	0014,	0015,	0016,	0017,
	0020,	0021,	0022,	0023,	0024,	0025,	0026,	0027,
	0030,	0031,	0032,	0033,	0034,	0035,	0036,	0037,
	0040,	0041,	0042,	0043,	0044,	0045,	0046,	0047,
	0050,	0051,	0052,	0053,	0054,	0055,	0056,	0057,
	0060,	0061,	0062,	0063,	0064,	0065,	0066,	0067,
	0070,	0071,	0072,	0073,	0074,	0075,	0076,	0077,
	0100,	0101,	0102,	0103,	0104,	0105,	0106,	0107,
	0110,	0111,	0112,	0113,	0114,	0115,	0116,	0117,
	0120,	0121,	0122,	0123,	0124,	0125,	0126,	0127,
	0130,	0131,	0132,	0133,	0134,	0135,	0136,	0137,
	0140,	0101,	0102,	0103,	0104,	0105,	0106,	0107,
	0110,	0111,	0112,	0113,	0114,	0115,	0116,	0117,
	0120,	0121,	0122,	0123,	0124,	0125,	0126,	0127,
	0130,	0131,	0132,	0173,	0174,	0175,	0176,	0177,
	0200,	0201,	0202,	0203,	0204,	0205,	0206,	0207,
	0210,	0211,	0212,	0213,	0214,	0215,	0216,	0217,
	0220,	0221,	0222,	0223,	0224,	0225,	0226,	0227,
	0230,	0231,	0232,	0233,	0234,	0235,	0236,	0237,
	0240,	0241,	0242,	0243,	0244,	0245,	0246,	0247,
	0250,	0251,	0252,	0253,	0254,	0255,	0256,	0257,
	0260,	0261,	0262,	0263,	0264,	0265,	0266,	0267,
	0270,	0271,	0272,	0273,	0274,	0275,	0276,	0277,
	0300,	0301,	0302,	0303,	0304,	0305,	0306,	0307,
	0310,	0311,	0312,	0313,	0314,	0315,	0316,	0317,
	0320,	0321,	0322,	0323,	0324,	0325,	0326,	0327,
	0330,	0331,	0332,	0333,	0334,	0335,	0336,	0337,
	0300,	0301,	0302,	0303,	0304,	0305,	0306,	0307,
	0310,	0311,	0312,	0313,	0314,	0315,	0316,	0317,
	0320,	0321,	0322,	0323,	0324,	0325,	0326,	0367,
	0330,	0331,	0332,	0333,	0334,	0335,	0336,	0377,
};
#endif /* NLS */
E 6
E 1
