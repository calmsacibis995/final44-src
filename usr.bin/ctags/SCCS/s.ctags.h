h40230
s 00001/00001/00063
d D 8.3 94/04/02 10:08:32 pendry 7 6
c add 1994 copyright
e
s 00031/00010/00033
d D 8.2 94/04/01 13:02:02 pendry 6 5
c prettyness police
e
s 00002/00002/00041
d D 8.1 93/06/06 14:29:45 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00003/00043
d D 5.4 91/02/26 13:42:15 bostic 4 3
c ANSI fixes, use strdup instead of rolling your own
e
s 00001/00011/00045
d D 5.3 90/06/01 15:58:19 bostic 3 2
c new copyright notice
e
s 00016/00003/00040
d D 5.2 88/12/31 12:32:30 bostic 2 1
c original by Ken Arnold -- Berkeley copyright
e
s 00043/00000/00000
d D 5.1 87/03/16 17:57:32 bostic 1 0
c date and time created 87/03/16 17:57:32 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
D 5
 * Copyright (c) 1987 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
D 7
 * Copyright (c) 1987, 1993
E 7
I 7
 * Copyright (c) 1987, 1993, 1994
E 7
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
E 2
 */

D 4
#include <stdio.h>
#include <ctype.h>

E 4
#define	bool	char

#define	YES		1
#define	NO		0
#define	EOS		'\0'

#define	ENDLINE		50		/* max length of pattern */
#define	MAXTOKEN	250		/* max size of single token */

#define	SETLINE		{++lineno;lineftell = ftell(inf);}
#define	GETC(op,exp)	((c = getc(inf)) op (int)exp)

D 6
#define	iswhite(arg)	(_wht[arg])	/* T if char is white */
#define	begtoken(arg)	(_btk[arg])	/* T if char can start token */
#define	intoken(arg)	(_itk[arg])	/* T if char can be in token */
#define	endtoken(arg)	(_etk[arg])	/* T if char ends tokens */
#define	isgood(arg)	(_gd[arg])	/* T if char can be after ')' */
E 6
I 6
#define	iswhite(arg)	(_wht[(unsigned)arg])	/* T if char is white */
#define	begtoken(arg)	(_btk[(unsigned)arg])	/* T if char can start token */
#define	intoken(arg)	(_itk[(unsigned)arg])	/* T if char can be in token */
#define	endtoken(arg)	(_etk[(unsigned)arg])	/* T if char ends tokens */
#define	isgood(arg)	(_gd[(unsigned)arg])	/* T if char can be after ')' */
E 6

typedef struct nd_st {			/* sorting structure */
	struct nd_st	*left,
			*right;		/* left and right sons */
	char	*entry,			/* function or type name */
		*file,			/* file name */
		*pat;			/* search pattern */
	int	lno;			/* for -x option */
	bool	been_warned;		/* set if noticed dup */
} NODE;

D 6
extern FILE	*inf;			/* ioptr for current input file */
E 6
I 6
extern char	*curfile;		/* current input file name */
extern NODE	*head;			/* head of the sorted binary tree */
extern FILE    *inf;			/* ioptr for current input file */
extern FILE    *outf;			/* ioptr for current output file */
E 6
extern long	lineftell;		/* ftell after getc( inf ) == '\n' */
D 6
extern int	lineno,			/* line number of current line */
		xflag;			/* -x: cxref style output */
extern bool	_wht[0177],_etk[0177],_itk[0177],_btk[0177],_gd[0177];
extern char	lbuf[BUFSIZ];
E 6
I 6
extern int	lineno;			/* line number of current line */
extern int	dflag;			/* -d: non-macro defines */
extern int	tflag;			/* -t: create tags for typedefs */
extern int	vflag;			/* -v: vgrind style index output */
extern int	wflag;			/* -w: suppress warnings */
extern int	xflag;			/* -x: cxref style output */
extern bool	_wht[], _etk[], _itk[], _btk[], _gd[];
extern char	lbuf[LINE_MAX];
extern char    *lbp;
extern char	searchar;		/* ex search character */

extern int	cicmp __P((char *));
extern void	getline __P((void));
extern void	pfnote __P((char *, int));
extern int	skip_key __P((int));
extern void	put_entries __P((NODE *));
extern void	toss_yysec __P((void));
extern void	l_entries __P((void));
extern void	y_entries __P((void));
extern int	PF_funcs __P((void));
extern void	c_entries __P((void));
extern void	skip_comment __P((void));
E 6
E 1
