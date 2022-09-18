h12322
s 00002/00002/00068
d D 8.1 93/05/31 16:41:22 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00068
d D 5.9 93/05/27 05:06:36 christos 10 9
c changed _Q,_Q1 to _QF,_QB to avoid conflict with new <ctype.h>
e
s 00000/00000/00070
d D 5.8 93/05/22 19:06:16 christos 9 8
c Fixed gcc -Wall warnings
e
s 00000/00000/00070
d D 5.7 91/07/19 17:30:20 christos 8 7
c stdio based version; brace glob fix; builtin prototypes
e
s 00055/00036/00015
d D 5.6 91/06/04 13:31:13 bostic 7 6
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00005/00004/00046
d D 5.5 91/04/04 18:17:32 bostic 6 5
c new copyright; att/bsd/shared
e
s 00038/00024/00012
d D 5.4 88/06/06 11:46:14 bostic 5 4
c make cshputchar a macro; some reformatting
e
s 00006/00001/00030
d D 5.3 86/03/29 07:37:10 lepreau 4 3
c Minor speedups & cleanups:
c replace letter() et al with ctype-like cmap macros and expand cmap to short
c for new LET and DIG bits; use bzero in private calloc; make btell a macro.
e
s 00001/00001/00030
d D 5.2 85/06/06 13:12:09 edward 3 2
c cleaning up after bozos
e
s 00007/00001/00024
d D 5.1 85/06/04 11:10:04 dist 2 1
c Add copyright
e
s 00025/00000/00000
d D 4.1 84/12/13 16:26:24 edward 1 0
c date and time created 84/12/13 16:26:24 by edward
e
u
U
t
T
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 6
/*
 * Copyright (c) 1980 Regents of the University of California.
D 3
 * All rights reserved.  The Berkeley software License Agreement
E 3
I 3
 * All rights reserved.  The Berkeley Software License Agreement
E 3
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
D 11
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * %sccs.include.redist.c%
E 6
 *
 *	%W% (Berkeley) %G%
 */
E 2

I 7
#include <ctype.h>

E 7
D 5
/*
 * Table for spotting special characters quickly
 *
 * Makes for very obscure but efficient coding.
 */

E 5
D 4
extern char _cmap[];
E 4
I 4
extern unsigned short _cmap[];
E 4

D 5
#define _Q	0x01		/* '" */
#define _Q1	0x02		/* ` */
#define _SP	0x04		/* space and tab */
#define _NL	0x08		/* \n */
#define _META	0x10		/* lex meta characters, sp #'`";&<>()|\t\n */
#define _GLOB	0x20		/* glob characters, *?{[` */
#define _ESC	0x40		/* \ */
#define _DOL	0x80		/* $ */
I 4
#define _DIG   0x100		/* 0-9 */
#define _LET   0x200		/* a-z, A-Z, _ */
E 5
I 5
D 7
#define	_Q	0x001		/* '" */
#define	_Q1	0x002		/* ` */
#define	_SP	0x004		/* space and tab */
#define	_NL	0x008		/* \n */
#define	_META	0x010		/* lex meta characters, sp #'`";&<>()|\t\n */
#define	_GLOB	0x020		/* glob characters, *?{[` */
#define	_ESC	0x040		/* \ */
#define	_DOL	0x080		/* $ */
#define	_DIG	0x100		/* 0-9 */
#define	_LET	0x200		/* a-z, A-Z, _ */
E 7
I 7
#ifndef NLS
extern unsigned char _cmap_lower[], _cmap_upper[];
E 7
E 5
E 4

D 5
#define cmap(c, bits)	(_cmap[(unsigned char)(c)] & (bits))
E 5
I 5
D 7
#define	cmap(c, bits)	(_cmap[(unsigned char)(c)] & (bits))
E 7
I 7
#endif
E 7
E 5

D 5
#define isglob(c)	cmap(c, _GLOB)
#define isspace(c)	cmap(c, _SP)
#define isspnl(c)	cmap(c, _SP|_NL)
#define ismeta(c)	cmap(c, _META)
I 4
#define digit(c)	cmap(c, _DIG)
#define letter(c)	cmap(c, _LET)
#define alnum(c)	(digit(c) || letter(c))
E 5
I 5
D 7
#define	isglob(c)	cmap(c, _GLOB)
#define	isspace(c)	cmap(c, _SP)
#define	isspnl(c)	cmap(c, _SP|_NL)
#define	ismeta(c)	cmap(c, _META)
#define	digit(c)	cmap(c, _DIG)
#define	letter(c)	cmap(c, _LET)
#define	alnum(c)	(digit(c) || letter(c))
E 7
I 7
D 10
#define	_Q	0x0001		/* '" */
#define	_Q1	0x0002		/* ` */
E 10
I 10
#define	_QF	0x0001		/* '" (Forward quotes) */
#define	_QB	0x0002		/* ` (Backquote) */
E 10
#define	_SP	0x0004		/* space and tab */
#define	_NL	0x0008		/* \n */
#define	_META	0x0010		/* lex meta characters, sp #'`";&<>()|\t\n */
#define	_GLOB	0x0020		/* glob characters, *?{[` */
#define	_ESC	0x0040		/* \ */
#define	_DOL	0x0080		/* $ */
#define	_DIG  	0x0100		/* 0-9 */
#define	_LET  	0x0200		/* a-z, A-Z, _ */
#define	_UP   	0x0400		/* A-Z */
#define	_LOW  	0x0800		/* a-z */
#define	_XD 	0x1000		/* 0-9, a-f, A-F */
#define	_CMD	0x2000		/* lex end of command chars, ;&(|` */
#define _CTR	0x4000		/* control */
E 7

D 7
#define	LINELEN		128
extern char *linp, linbuf[LINELEN];
E 7
I 7
#define cmap(c, bits)	\
	(((c) & QUOTE) ? 0 : (_cmap[(unsigned char)(c)] & (bits)))
E 7

D 7
#define	CSHPUTCHAR { \
	if (!(ch&QUOTE) && (ch == 0177 || ch < ' ' && ch != '\t' && \
	    ch != '\n')) { \
		*linp++ = '^'; \
		if (ch == 0177) \
			ch = '?'; \
		else \
			ch |= 'A' - 1; \
		if (linp >= &linbuf[sizeof linbuf - 2]) \
			flush(); \
	} \
	ch &= TRIM; \
	*linp++ = ch; \
	if (ch == '\n' || linp >= &linbuf[sizeof(linbuf) - 2]) \
		flush(); \
}
E 7
I 7
#define isglob(c)	cmap(c, _GLOB)
#define isspc(c)	cmap(c, _SP)
#define ismeta(c)	cmap(c, _META)
#define iscmdmeta(c)	cmap(c, _CMD)
#define letter(c)	(((c) & QUOTE) ? 0 : \
			 (isalpha((unsigned char) (c)) || (c) == '_'))
#define alnum(c)	(((c) & QUOTE) ? 0 : \
		         (isalnum((unsigned char) (c)) || (c) == '_'))
#ifdef NLS
#define Isspace(c)	(((c) & QUOTE) ? 0 : isspace((unsigned char) (c)))
#define Isdigit(c)	(((c) & QUOTE) ? 0 : isdigit((unsigned char) (c)))
#define Isalpha(c)	(((c) & QUOTE) ? 0 : isalpha((unsigned char) (c)))
#define Islower(c)	(((c) & QUOTE) ? 0 : islower((unsigned char) (c)))
#define Isupper(c)	(((c) & QUOTE) ? 0 : isupper((unsigned char) (c)))
#define Tolower(c) 	(((c) & QUOTE) ? 0 : tolower((unsigned char) (c)))
#define Toupper(c) 	(((c) & QUOTE) ? 0 : toupper((unsigned char) (c)))
#define Isxdigit(c)	(((c) & QUOTE) ? 0 : isxdigit((unsigned char) (c)))
#define Isalnum(c)	(((c) & QUOTE) ? 0 : isalnum((unsigned char) (c)))
#define Iscntrl(c) 	(((c) & QUOTE) ? 0 : iscntrl((unsigned char) (c)))
#define Isprint(c) 	(((c) & QUOTE) ? 0 : isprint((unsigned char) (c)))
#else
#define Isspace(c)	cmap(c, _SP|_NL)
#define Isdigit(c)	cmap(c, _DIG)
#define Isalpha(c)	(cmap(c,_LET) && !(((c) & META) && AsciiOnly))
#define Islower(c)	(cmap(c,_LOW) && !(((c) & META) && AsciiOnly))
#define Isupper(c)	(cmap(c, _UP) && !(((c) & META) && AsciiOnly))
#define Tolower(c)  (_cmap_lower[(unsigned char)(c)])
#define Toupper(c)  (_cmap_upper[(unsigned char)(c)])
#define Isxdigit(c)	cmap(c, _XD)
#define Isalnum(c)	(cmap(c, _DIG|_LET) && !(((c) & META) && AsciiOnly))
#define Iscntrl(c)  (cmap(c,_CTR) && !(((c) & META) && AsciiOnly))
#define Isprint(c)  (!cmap(c,_CTR) && !(((c) & META) && AsciiOnly))
#endif
E 7
E 5
E 4
E 1
