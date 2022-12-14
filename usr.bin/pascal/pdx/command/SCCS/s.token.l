h11310
s 00002/00002/00345
d D 8.1 93/06/06 15:35:47 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00341
d D 5.4 91/04/16 15:36:56 bostic 7 6
c new copyright; att/bsd/shared
e
s 00019/00019/00327
d D 5.3 90/06/29 17:08:45 bostic 6 5
c Vern Paxon's fixes for the new lex
e
s 00000/00027/00346
d D 5.2 87/04/07 15:53:00 mckusick 5 4
c port to tahoe by Nir peleg of CCI
e
s 00008/00002/00365
d D 5.1 85/06/07 19:45:51 mckusick 4 3
c Add copyright
e
s 00011/00001/00356
d D 1.3 82/01/25 23:04:55 linton 3 2
c prompts revisited
e
s 00002/00002/00355
d D 1.2 82/01/23 18:43:16 linton 2 1
c recognizing numerical filenames by putting filenames before numbers
e
s 00357/00000/00000
d D 1.1 82/01/18 19:20:12 linton 1 0
c date and time created 82/01/18 19:20:12 by linton
e
u
U
t
T
I 1
%{
D 4
/* Copyright (c) 1982 Regents of the University of California */
E 4
I 4
D 7
/*
 * Copyright (c) 1982 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 8
 * Copyright (c) 1982 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
E 7
 */
E 4

D 4
static char sccsid[] = "%Z%%M% %I% %G%";
E 4
I 4
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 4

/*
 * Token definitions for pdx scanner.
 */

#include "defs.h"
#include "command.h"
#include "y.tab.h"
I 3
#include "main.h"
E 3
#include "symtab.h"
#include "sym.h"
#include "process.h"
#include "process/pxinfo.h"

char *initfile = ".pdxinit";

D 6
/*
 * This is a silly "lex" thing.
 */
E 6
I 6
/* override Lex default input macro. */
LOCAL int pdxinput();
E 6

D 6
#define yywrap()	(1)
E 6
I 6
#undef  YY_INPUT
#define YY_INPUT(buf,result,max_size)	\
	{				\
	int c = pdxinput();		\
	if ( c == EOF )			\
		result = YY_NULL;	\
	else				\
		{			\
		buf[0] = c;		\
		result = 1;		\
		}			\
	}
E 6

D 6
/*
 * Override Lex default input macros.
 */

#undef  input
#undef  unput

#define unput(c)	ungetc(c, yyin)

E 6
%}

blank		[ \t]
white		{blank}+
alpha		[a-zA-Z]
digit		[0-9]
n		{digit}+
h		[0-9a-fA-F]+
e		(("e"|"E")("+"|"-")?{n})
alphanum	[a-zA-Z0-9]
ident		{alpha}{alphanum}*
filenm		[^ \t\n"<>!*"]+
D 6
qfilenm		{filenm}/":"
E 6
string		'[^']+'('[^']*')*
newline		"\n"
char		.

D 6
%Start file sh
E 6
I 6
%Start File sh
E 6

%%

{white}		;
^sh{white}.*$	{ BEGIN 0; yylval.y_string = &yytext[3]; return(SH); }
^sh		{ BEGIN 0; yylval.y_string = NIL; return(SH); }
^{ident}	{ return(findcmd(yytext)); }
I 2
D 6
<file>{filenm}	{ yylval.y_string = strdup(yytext); return(FILENAME); }
{qfilenm}	{ yylval.y_string = strdup(yytext); return(FILENAME); }
E 6
I 6
<File>{filenm}	{ yylval.y_string = strdup(yytext); return(FILENAME); }
{filenm}/":"	{ yylval.y_string = strdup(yytext); return(FILENAME); }
E 6
E 2
{n}?\.{n}{e}?	{ yylval.y_real = atof(yytext); return(REAL); }
0{n}		{ yylval.y_long = octal(yytext); return(INT); }
0x{h}		{ yylval.y_long = hex(yytext); return(INT); }
{n}		{ yylval.y_long = atol(yytext); return(INT); }
D 2
<file>{filenm}	{ yylval.y_string = strdup(yytext); return(FILENAME); }
{qfilenm}	{ yylval.y_string = strdup(yytext); return(FILENAME); }
E 2
at		{ return(AT); }
{ident}		{ return(ident(yytext)); }
{string}	{ yylval.y_string = yytext; return(STRING); }
"%dp"		{ yylval.y_long = (long) DP; return(INT); }
{newline}	{ BEGIN 0; nlflag = TRUE; return('\n'); }
{char}		{ return(yylval.y_int = yytext[0]); }

%%

LOCAL SYMTAB *dbtab, *specialtab;

/*
 * Look for the given string in the debugger keyword table.
 * If it's there, return the associated token, otherwise report an error.
 */

LOCAL int findcmd(s)
char *s;
{
	register SYM *p;

	if ((p = st_lookup(dbtab, s)) == NIL) {
		error("\"%s\" is not a command", s);
	}
	yylval.y_int = tokval(p);
	switch (toknum(p)) {
		case ALIAS:
		case DUMP:
		case EDIT:
		case CHFILE:
		case RUN:
		case SOURCE:
		case STATUS:
D 6
			BEGIN file;
E 6
I 6
			BEGIN File;
E 6
			break;

		default:
			/* do nothing */;
	}
	return(toknum(p));
}

/*
 * Look for a symbol, first in the special table (if, in, etc.)
 * then in the symbol table.  If it's there, return the SYM pointer,
 * otherwise it's an error.
 */

LOCAL int ident(s)
char *s;
{
	register SYM *p;

	if ((p = st_lookup(specialtab, s)) != NIL) {
		yylval.y_sym = p;
		return(toknum(p));
	}
	p = st_lookup(symtab, s);
	if (p == NIL) {
		if (strcmp(s, "nil") == 0) {
			yylval.y_long = 0L;
			return(INT);
		} else {
			error("\"%s\" is not defined", s);
		}
	}
	yylval.y_sym = p;
	return(NAME);
}

/*
 * Convert a string to octal.  No check that digits are less than 8.
 */

LOCAL int octal(s)
char *s;
{
	register char *p;
	register int n;

	n = 0;
	for (p = s; *p != '\0'; p++) {
		n = 8*n + (*p - '0');
	}
	return(n);
}

/*
 * Convert a string to hex.
 */

LOCAL int hex(s)
char *s;
{
	register char *p;
	register int n;

	n = 0;
	for (p = s+2; *p != '\0'; p++) {
		n *= 16;
		if (*p >= 'a' && *p <= 'f') {
			n += (*p - 'a' + 10);
		} else if (*p >= 'A' && *p <= 'F') {
			n += (*p - 'A' + 10);
		} else {
			n += (*p - '0');
		}
	}
	return(n);
}

/*
 * Initialize the debugger keyword table (dbtab) and special symbol
 * table (specialtab).
 */

#define db_keyword(nm, n)	make_keyword(dbtab, nm, n)
#define sp_keyword(nm, n)	make_keyword(specialtab, nm, n)

lexinit()
{
	dbtab = st_creat(150);
	db_keyword("alias", ALIAS);
	db_keyword("assign", ASSIGN);
	db_keyword("call", CALL);
	db_keyword("cont", CONT);
	db_keyword("delete", DELETE);
	db_keyword("dump", DUMP);
	db_keyword("edit", EDIT);
	db_keyword("file", CHFILE);
	db_keyword("gripe", GRIPE);
	db_keyword("help", HELP);
	db_keyword("list", LIST);
	db_keyword("next", NEXT);
	db_keyword("pi", REMAKE);
	db_keyword("print", PRINT);
	db_keyword("quit", QUIT);
	db_keyword("run", RUN);
	db_keyword("sh", SH);
	db_keyword("source", SOURCE);
	db_keyword("status", STATUS);
	db_keyword("step", STEP);
	db_keyword("stop", STOP);
	db_keyword("stopi", STOPI);
	db_keyword("trace", TRACE);
	db_keyword("tracei", TRACEI);
	db_keyword("whatis", WHATIS);
	db_keyword("where", WHERE);
	db_keyword("which", WHICH);
	db_keyword("xd", XD);
	db_keyword("xi", XI);

	specialtab = st_creat(10);
	sp_keyword("div", DIV);
	sp_keyword("mod", MOD);
	sp_keyword("in", IN);
	sp_keyword("if", IF);
	sp_keyword("and", AND);
	sp_keyword("or", OR);
}

/*
 * Send an alias directive over to the symbol table manager.
 */

alias(new, old)
char *new, *old;
{
	if (old == NIL) {
		print_alias(dbtab, new);
	} else {
		enter_alias(dbtab, new, old);
	}
}

/*
 * Input file management routines, "yyin" is Lex's idea of
 * where the input comes from.
 */

#define MAXINPUT 10

LOCAL FILE *infp[MAXINPUT];
LOCAL FILE **curfp = &infp[0];

LOCAL BOOLEAN isnewfile;
I 3
LOCAL BOOLEAN firsttime;
E 3

/*
 * Initially, we set the input to the initfile if it exists.
 * If it does exist, we play a game or two to avoid generating
 * multiple prompts.
 */

initinput()
{
	FILE *fp;

I 3
	firsttime = FALSE;
E 3
	fp = fopen(initfile, "r");
	if (fp != NIL) {
		fclose(fp);
		setinput(initfile);
I 3
		if (!option('r')) {
			firsttime = TRUE;
		}
E 3
	}
	nlflag = TRUE;
}

/*
 * Set the input to the named file.  It is expected that the file exists
 * and is readable.
 */

setinput(filename)
char *filename;
{
	register FILE *fp;

	if ((fp = fopen(filename, "r")) == NIL) {
		error("can't open %s", filename);
	}
	if (curfp >= &infp[MAXINPUT]) {
		error("unreasonable input nesting on %s", filename);
	}
	*curfp++ = yyin;
	yyin = fp;
	isnewfile = TRUE;
}

BOOLEAN isstdin()
{
	return((BOOLEAN) (yyin == stdin));
}

D 6
LOCAL int input()
E 6
I 6
LOCAL int pdxinput()
E 6
{
	register int c;

	if (isnewfile) {
		isnewfile = FALSE;
		return('\n');
	}
	while ((c = getc(yyin)) == EOF) {
		if (curfp == &infp[0]) {
			return(0);
		} else {
			fclose(yyin);
			yyin = *--curfp;
			if (yyin == stdin) {
D 3
				prompt();
E 3
I 3
				if (firsttime) {
					firsttime = FALSE;
				} else {
					prompt();
				}
E 3
			}
		}
	}
	return(c);
}

/*
D 5
 * Handle an input string by stripping the quotes and converting
 * two interior quotes to one.  Copy to newly allocated space and
 * return a pointer to it.
 *
 * The handling of strings here is not particularly efficient,
 * nor need it be.
 */

LOCAL char *pstring(p)
char *p;
{
	int i, len;
	char *r, *newp;

	len = strlen(p);
	r = newp = alloc(len - 2 + 1, char);
	for (i = 1; i < len - 1; i++) {
		if (p[i] == '\'' && p[i+1] == '\'') {
			i++;
		}
		*newp++ = p[i];
	}
	*newp = '\0';
	return(r);
}

/*
E 5
 * prompt for a command
 */

prompt()
{
	nlflag = FALSE;
	if (yyin == stdin) {
		printf("> ");
		fflush(stdout);
	}
}
E 1
