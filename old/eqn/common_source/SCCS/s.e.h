h00278
s 00008/00001/00052
d D 4.3 91/04/17 17:26:47 bostic 3 2
c new copyright; att/bsd/shared
e
s 00009/00000/00044
d D 4.2 83/02/12 18:03:16 shannon 2 1
c merge eqn and neqn
e
s 00044/00000/00000
d D 4.1 83/02/11 18:27:43 shannon 1 0
c date and time created 83/02/11 18:27:43 by shannon
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 3

#include <stdio.h>

#define	FATAL	1
#define	ROM	'1'
I 2
#ifndef NEQN
E 2
#define	ITAL	'2'
#define	BLD	'3'
I 2
#else NEQN
#define	ITAL	'1'
#define	BLD	'1'
#endif NEQN
E 2

I 2
#ifndef NEQN
E 2
#define	VERT(n)	((((n)+1)/3)*3)
I 2
#else NEQN
#define	VERT(n)	(20 * (n))
#endif NEQN
E 2
#define	EFFPS(p)	((p) >= 6 ? (p) : 6)

extern int	dbg;
extern int	ct;
extern int	lp[];
extern int	used[];	/* available registers */
extern int	ps;	/* dflt init pt size */
extern int	deltaps;	/* default change in ps */
extern int	gsize;	/* global size */
extern int	gfont;	/* global font */
extern int	ft;	/* dflt font */
extern FILE	*curfile;	/* current input file */
extern int	ifile;	/* input file number */
extern int	linect;	/* line number in current file */
extern int	eqline;	/* line where eqn started */
extern int	svargc;
extern char	**svargv;
extern int	eht[];
extern int	ebase[];
extern int	lfont[];
extern int	rfont[];
extern int	yyval;
extern int	*yypv;
extern int	yylval;
extern int	eqnreg, eqnht;
extern int	lefteq, righteq;
extern int	lastchar;	/* last character read by lex */
extern int	markline;	/* 1 if this EQ/EN contains mark or lineup */

typedef struct s_tbl {
	char	*name;
	char	*defn;
	struct s_tbl *next;
} tbl;
E 1
