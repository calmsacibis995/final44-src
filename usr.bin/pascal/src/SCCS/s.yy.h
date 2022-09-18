h19507
s 00002/00002/00310
d D 8.1 93/06/06 16:13:02 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00307
d D 5.3 91/04/16 16:25:30 bostic 8 7
c new copyright; att/bsd/shared
e
s 00001/00000/00310
d D 5.2 85/06/21 12:47:27 mckusick 7 6
c clear conflict with param.h
e
s 00007/00003/00303
d D 5.1 85/06/05 16:05:09 dist 6 5
c Add copyright
e
s 00000/00000/00306
d D 2.1 84/02/08 20:45:21 aoki 5 4
c synchronize to version 2
e
s 00000/00000/00306
d D 1.4 83/09/19 07:08:57 thien 4 3
c changing to unlinted source
e
s 00016/00001/00290
d D 1.3 83/08/19 05:07:18 thien 3 2
c Changed for linting
e
s 00005/00000/00286
d D 1.2 83/05/11 21:54:42 peter 2 1
c big machines get to input longer lines.
e
s 00286/00000/00000
d D 1.1 80/08/27 19:54:34 peter 1 0
c date and time created 80/08/27 19:54:34 by peter
e
u
U
t
T
I 1
D 6
/* Copyright (c) 1979 Regents of the University of California */

/* static	char sccsid[] = "%Z%%M% %I% %G%"; */
E 6
I 6
D 8
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
/*-
D 9
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
E 8
 *
 *	%W% (Berkeley) %G%
 */
E 6

#include "y.tab.h"
I 7
#undef CBSIZE	/* from paramsys/param.h */
E 7
/*
 * INPUT/OUTPUT 
 */

/*
 * The buffer for the input file is normally "ibuf".
 * When files are included, however, this may be
 * pushed down in the stack of currently active
 * files. For this reason, the pointer ibp always
 * references the i/o buffer of the current input file.
 */
FILE		*ibuf, *ibp;

/*
 * Line and token buffers.  Charbuf is the character buffer for
 * input lines, token the buffer for tokens returned
 * by the scanner.  CBSIZE defines the maximum line
 * length allowed on input and is doubtless too small.
 * The token buffer should be a local array in yylex.
 */
I 2
#ifdef ADDR16
E 2
#define CBSIZE 161
I 2
#endif ADDR16
#ifdef ADDR32
#define CBSIZE 1024
#endif ADDR32
E 2

char	charbuf[CBSIZE], *bufp, token[CBSIZE];

#define digit(c)	(c >= '0' && c <= '9')
#define alph(c)		((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

/*
 * Flag to prevent reprinting current line after
 * an error.
 */
char	yyprtd;

/*
 * The following variables are maintained by
 * the scanner in the file lex and used in scanning
 * and in parsing.
 *
 * The variable yychar is the current scanner character.
 * Currently, the scanner must be called as
 *	yychar = yylex()
 * even though it should set yychar itself.
 * Yychar has value YEOF at end of file, and negative value if
 * there is no yychar, e.g. after a shift in the parser.
 *
 * The variable yycol is the current column in the line whose number
 * is given by yyline.  Yyecol and yyeline give the position for an
 * error message to flag, usually the start of an input token.
 * Yylval is the semantic return from the scanner.
 *
 * In fact all of these variables are "per token".
 * In the usual case, only the copies in the scanner token structure
 * 'Y' are used, and the #defines below serve to make them look
 * like variables.
 *
 * For the purposes of the error recovery, however, they are copied
 * and restored quite freely.  For the error recovery also, the
 * file name which the input line this token is on and the seek
 * pointer of this line in its source file are saved as yyefile
 * and yyseekp.  The global variable yylinpt is the seek pointer
 * of the current input line.
 */
int	yycol;
int	yyline;
int	yyseqid;
int	yysavc;
int	yylinpt;

/* *** NOTE ***
 * It would be much better to not have the Yyeline and Yyefile
 * in the scanner structure and to have a mechanism for mapping
 * seqid's to these globally.
 */
struct yytok {
	int	Yychar;
	int	Yylval;
	int	Yyecol;
	int	Yyeline;
	int	Yyseekp;
	char	*Yyefile;
	int	Yyeseqid;
} Y, OY;

#define	yychar	Y.Yychar
#define	yylval	Y.Yylval
#define	yyecol	Y.Yyecol
#define	yyeline	Y.Yyeline
#define	yyseekp	Y.Yyseekp
#define	yyefile	Y.Yyefile
#define	yyeseqid Y.Yyeseqid

I 3
/* Semantic Stack so that y.tab.c will lint */

union semstack
{
    int		  i_entry;
    struct nl	 *nl_entry;
    struct tnode *tr_entry;
    char	 *cptr;
} yyval;

E 3
/*
 * Yyval is the semantic value returned by a reduction.
 * It is what "$$" is expanded to by yacc.
 */
D 3
int	*Ps, *yyval;
E 3

I 3
int	*Ps;

E 3
/*
 * N is the length of a reduction.
 * Used externally by "lineof" to get the left and
 * right margins for a reduction.
 */
int	N;
/*
 * Definitions for looking up keywords.
 * The keyword array is called yykey, and
 * lastkey points at the end of it.
 */
char	*lastkey;

struct kwtab {
	char	*kw_str;
	int	kw_val;
} yykey[];

/*
 * ERROR RECOVERY EXTERNALS
 */

#define	CLIMIT	40	/* see yyrecover.c */
char	*tokname();
char	*charname();

char	*classes[];

/*
 * Tokens which yacc doesn't define
 */
#define	YEOF	0
#define	ERROR	256

/*
 * Limit on the number of syntax errors
 */
#define	MAXSYNERR	100

/*
 * Big costs
 */
#define	HUGE		50
#define	INFINITY	100

/*
 * Kinds of panics
 */
#define	PDECL	0
#define	PSTAT	1
#define	PEXPR	2
#define	PPROG	3

#define	yyresume()	yyResume = 1;

char	yyResume;

char	dquote;

I 3
#ifndef PC
#ifndef OBJ
E 3
char	errout;
I 3
#endif OBJ
#endif PC
E 3

/*
 * Yyidwant and yyidhave are the namelist classes
 * of identifiers associated with a identifier reduce
 * error, set before the recovery is called.
 * Since they may be set again during the forward move
 * they must be saved by yyrecover, which uses them in printing
 * error messages.
 */
int	yyidhave, yyidwant;

/*
 * The variables yy*shifts are used to prevent looping and the printing
 * of spurious messages in the parser.  Yyshifts gives the number of
 * true input shifts since the last corrective action.  YyOshifts
 * is the value of yyshifts before it was last cleared, and is used
 * by yyPerror in yypanic.c to suppress messages.
 *
 * Yytshifts counts true input shifts.  It is used to prevent looping
 * inserting unique symbols.  If yytshifts == yyTshifts (local to
 * yyrecover.c) then there has been no shift over true input since
 * the last unique symbol insertion.  We refuse, in this case,
 * to insert more unique symbols so as to prevent looping.
 *
 * The recovery cannot loop because it guarantees the progress of the
 * parse, i.e.:
 *
 *	1) Any insertion guarantees to shift over 2 symbols, a replacement
 *	   over one symbol.
 *
 *	2) Unique symbol insertions are limited to one for each true
 *	   symbol of input, or "safe" insertion of the keywords "end"
 *	   and "until" at zero cost (safe since these are know to match
 *	   stack that cannot have been generated - e.g. "begin" or "repeat")
 *
 *	3) We never panic more than once from a given state without
 *	   shifting over input, i.e. we force the parse stack to shrink
 *	   after each unsuccessful panic.
 */
int	yyshifts, yyOshifts;
unsigned yytshifts;

#ifdef PXP

/*
 * Identifier class definitions
 */
#define	UNDEF	0
#define	CONST	1
#define	TYPE	2
#define	VAR	3
#define	ARRAY	4
#define	PTRFILE	5
#define	RECORD	6
#define	FIELD	7
#define	PROC	8
#define	FUNC	9
#define	FVAR	10
#define	REF	11
#define	PTR	12
#define	FILET	13
#define	SET	14
#define	RANGE	15
#define	LABEL	16
#define	WITHPTR 17
#define	SCAL	18
#define	STR	19
#define	PROG	20
#define	IMPROPER 21

/*
 * COMMENT FORMATTING DEFINITIONS
 */

/*
 * Count of tokens on this input line
 * Note that this can be off if input is not syntactically correct.
 */
int	yytokcnt;
int	yywhcnt;

/*
 * Types of comments
 */
#define	CLMARG	0
#define	CALIGN	1
#define	CTRAIL	2
#define	CRMARG	3
#define	CSRMARG	4
#define	CNL	5
#define	CNLBL	6
#define	CFORM	7
#define	CINCLUD	8

/*
 * Comment structure
 * Cmhp is the head of the current list of comments
 */
struct comment {
	struct	comment *cmnext;
	int	cmdelim;
	struct	commline *cml;
	int	cmjust;
	int	cmseqid;
} *cmhp;

/*
 * Structure for holding a comment line
 */
struct commline {
	char	*cmtext;
	int	cmcol;	/* Only used for first line of comment currently */
	struct	commline *cml;
};

struct W {
	int	Wseqid;
	int	Wcol;
} yyw[MAXDEPTH + 1], *yypw;

#define	commform()	quickcomm(CFORM)
#define	commnl()	quickcomm(CNL)
#define	commnlbl()	quickcomm(CNLBL)
#endif
E 1
