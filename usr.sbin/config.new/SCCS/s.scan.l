h24276
s 00002/00002/00210
d D 8.1 93/06/06 13:55:04 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00212
d D 5.2 93/04/18 04:23:16 torek 2 1
c rm rcs headers (commit to maintenance on vangogh)
e
s 00214/00000/00000
d D 5.1 93/01/12 02:18:44 torek 1 0
c date and time created 93/01/12 02:18:44 by torek
e
u
U
t
T
I 1
%{
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
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratories.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
D 2
 *
 * from: $Header: scan.l,v 1.5 93/01/12 10:13:42 torek Exp $
E 2
 */

#include <sys/param.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "config.h"
#include "y.tab.h"

int	yyline;
const char *yyfile;
const char *lastfile;

int	include __P((const char *, int));

/*
 * Data for returning to previous files from include files.
 */
struct incl {
	struct	incl *in_prev;	/* previous includes in effect, if any */
	YY_BUFFER_STATE in_buf;	/* previous lex state */
	const char *in_fname;	/* previous file name */
	int	in_lineno;	/* previous line number */
	int	in_preveof;	/* previous eoftoken */
};
static struct incl *incl;
static int eoftoken;		/* current EOF token */
static void endinclude __P((void));

#define	yywrap() 1

%}

PATH	[-/A-Za-z0-9_.]*[./][-/A-Za-z0-9_.]*
WORD	[A-Za-z_][-A-Za-z_0-9]*

%%

		/* plain keywords */
and		{ return AND; }
at		{ return AT; }
compile-with	{ return COMPILE_WITH; }
config		{ return CONFIG; }
define		{ return DEFINE; }
device		{ return DEVICE; }
dumps		{ return DUMPS; }
flags		{ return FLAGS; }
file		{ return XFILE; }
include		{ return INCLUDE; }
machine		{ return XMACHINE; }
major		{ return MAJOR; }
makeoptions	{ return MAKEOPTIONS; }
maxusers	{ return MAXUSERS; }
minor		{ return MINOR; }
on		{ return ON; }
options		{ return OPTIONS; }
"pseudo-device"	{ return PSEUDO_DEVICE; }
root		{ return ROOT; }
swap		{ return SWAP; }
vector		{ return VECTOR; }

		/* keywords with values */
config-dependent { yylval.val = FI_CONFIGDEP; return FFLAG; }
device-driver	{ yylval.val = FI_DRIVER; return FFLAG; }
needs-count	{ yylval.val = FI_NEEDSCOUNT; return FFLAG; }
needs-flag	{ yylval.val = FI_NEEDSFLAG; return FFLAG; }

		/* all the rest */
{PATH}		{ yylval.str = intern(yytext); return PATHNAME; }
{WORD}		{ yylval.str = intern(yytext); return WORD; }

\"[^"]+/\" {
		yylval.str = intern(yytext + 1);
		(void)input();	/* eat closing quote */
		return WORD;
	}
0[0-7]*	{
		yylval.val = strtol(yytext, NULL, 8);
		return NUMBER;
	}
0[xX][0-9a-fA-F]+ {
		yylval.val = strtol(yytext + 2, NULL, 16);
		return NUMBER;
	}
[1-9][0-9]* {
		yylval.val = strtol(yytext, NULL, 10);
		return NUMBER;
	}
\n/[ \t] {
		yyline++;
	}
\n	{
		yyline++;
		return '\n';
	}
#.*	{ /* ignored (comment) */; }
[ \t]*	{ /* ignored (white space) */; }
.	{ return yytext[0]; }
<<EOF>> {
		int tok;

		tok = eoftoken;
		eoftoken = YY_NULL;
		if (incl != NULL)
			endinclude();
		return (tok);
	}

%%

/*
 * Open the "main" file (conffile).
 */
int
firstfile(fname)
	const char *fname;
{

	if ((yyin = fopen(fname, "r")) == NULL)
		return (-1);
	yyfile = conffile = fname;
	yyline = 1;
	eoftoken = YY_NULL;
	return (0);
}

/*
 * Open the named file for inclusion at the current point.  Returns 0 on
 * success (file opened and previous state pushed), nonzero on failure
 * (fopen failed, complaint made).  The `ateof' parameter controls the
 * token to be returned at the end of the include file (typically '\n'
 * or ENDFILE).
 */
int
include(fname, ateof)
	const char *fname;
	int ateof;
{
	register FILE *fp;
	register struct incl *in;

	if ((fp = fopen(fname, "r")) == NULL) {
		error("cannot open %s for reading: %s\n",
		    fname, strerror(errno));
		return (-1);
	}
	in = emalloc(sizeof *in);
	in->in_prev = incl;
	in->in_buf = YY_CURRENT_BUFFER;
	in->in_fname = yyfile;
	in->in_lineno = yyline;
	in->in_preveof = eoftoken;
	incl = in;
	yy_switch_to_buffer(yy_create_buffer(fp, YY_BUF_SIZE));
	yyfile = intern(fname);
	yyline = 1;
	eoftoken = ateof;
	return (0);
}

/*
 * Terminate the most recent inclusion.
 */
static void
endinclude()
{
	register struct incl *in;

	if ((in = incl) == NULL)
		panic("endinclude");
	incl = in->in_prev;
	lastfile = yyfile;
	yy_delete_buffer(YY_CURRENT_BUFFER);
	(void)fclose(yyin);
	yy_switch_to_buffer(in->in_buf);
	yyfile = in->in_fname;
	yyline = in->in_lineno;
	eoftoken = in->in_preveof;
	free(in);
}

/*
 * Return the current line number.  If yacc has looked ahead and caused
 * us to consume a newline, we have to subtract one.  yychar is yacc's
 * token lookahead, so we can tell.
 */
int
currentline()
{
	extern int yychar;

	return (yyline - (yychar == '\n'));
}
E 1
