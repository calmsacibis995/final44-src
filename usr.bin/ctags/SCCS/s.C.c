h58388
s 00001/00001/00474
d D 8.4 94/04/02 10:08:16 pendry 9 8
c add 1994 copyright
e
s 00106/00100/00369
d D 8.3 94/04/01 13:02:04 pendry 8 7
c prettyness police
e
s 00081/00004/00388
d D 8.2 94/01/07 12:43:39 bostic 7 6
c fixed bugs recognizing new test case (or ignoring it)
c From: ralphc@pyramid.com (Ralph Campbell)
e
s 00002/00002/00390
d D 8.1 93/06/06 14:29:35 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00002/00386
d D 5.5 91/02/26 13:42:11 bostic 5 4
c ANSI fixes, use strdup instead of rolling your own
e
s 00001/00011/00387
d D 5.4 90/06/01 15:58:09 bostic 4 3
c new copyright notice
e
s 00015/00004/00383
d D 5.3 88/12/31 12:32:25 bostic 3 2
c original by Ken Arnold -- Berkeley copyright
e
s 00003/00001/00384
d D 5.2 88/12/31 12:27:34 bostic 2 1
c ctags -t and routines that return structs; bug report 4.3BSD/ucb/239
e
s 00385/00000/00000
d D 5.1 87/03/16 17:57:29 bostic 1 0
c date and time created 87/03/16 17:57:29 by bostic
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
D 6
 * Copyright (c) 1987 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
D 9
 * Copyright (c) 1987, 1993
E 9
I 9
 * Copyright (c) 1987, 1993, 1994
E 9
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3

I 8
#include <limits.h>
E 8
#include <stdio.h>
D 5
#include <ctags.h>
E 5
I 5
#include <string.h>
I 8

E 8
#include "ctags.h"
E 5

I 5
D 8
static int func_entry(), str_entry();
static void hash_entry();
I 7
static void skip_string();
E 8
I 8
static int	func_entry __P((void));
static void	hash_entry __P((void));
static void	skip_string __P((int));
static int	str_entry __P((int));
E 8
E 7

E 5
/*
 * c_entries --
 *	read .c and .h files and call appropriate routines
 */
I 8
void
E 8
c_entries()
{
D 8
	extern int	tflag;		/* -t: create tags for typedefs */
	register int	c,		/* current character */
			level;		/* brace level */
	register char	*sp;		/* buffer pointer */
	int	token,			/* if reading a token */
		t_def,			/* if reading a typedef */
		t_level;		/* typedef's brace level */
E 8
I 8
	int	c;			/* current character */
	int	level;			/* brace level */
	int	token;			/* if reading a token */
	int	t_def;			/* if reading a typedef */
	int	t_level;		/* typedef's brace level */
	char	*sp;			/* buffer pointer */
E 8
	char	tok[MAXTOKEN];		/* token buffer */

	lineftell = ftell(inf);
	sp = tok; token = t_def = NO; t_level = -1; level = 0; lineno = 1;
D 8
	while (GETC(!=,EOF)) {

	switch ((char)c) {
E 8
I 8
	while (GETC(!=, EOF)) {
		switch (c) {
E 8
		/*
D 8
		 * Here's where it DOESN'T handle:
E 8
I 8
		 * Here's where it DOESN'T handle: {
E 8
		 *	foo(a)
		 *	{
		 *	#ifdef notdef
		 *		}
		 *	#endif
		 *		if (a)
		 *			puts("hello, world");
		 *	}
		 */
		case '{':
			++level;
			goto endtok;
		case '}':
			/*
			 * if level goes below zero, try and fix
			 * it, even though we've already messed up
			 */
			if (--level < 0)
				level = 0;
			goto endtok;

		case '\n':
			SETLINE;
			/*
			 * the above 3 cases are similar in that they
			 * are special characters that also end tokens.
			 */
D 8
endtok:			if (sp > tok) {
E 8
I 8
	endtok:			if (sp > tok) {
E 8
				*sp = EOS;
				token = YES;
				sp = tok;
			}
			else
				token = NO;
			continue;

D 7
		/* we ignore quoted strings and comments in their entirety */
E 7
I 7
		/*
		 * We ignore quoted strings and character constants
		 * completely.
		 */
E 7
		case '"':
		case '\'':
D 7
			(void)skip_key(c);
E 7
I 7
			(void)skip_string(c);
E 7
			break;

		/*
		 * comments can be fun; note the state is unchanged after
		 * return, in case we found:
		 *	"foo() XX comment XX { int bar; }"
		 */
		case '/':
D 8
			if (GETC(==,'*')) {
E 8
I 8
			if (GETC(==, '*')) {
E 8
				skip_comment();
				continue;
			}
D 8
			(void)ungetc(c,inf);
E 8
I 8
			(void)ungetc(c, inf);
E 8
			c = '/';
			goto storec;

		/* hash marks flag #define's. */
		case '#':
			if (sp == tok) {
				hash_entry();
				break;
			}
			goto storec;

		/*
D 8
	 	 * if we have a current token, parenthesis on
E 8
I 8
		 * if we have a current token, parenthesis on
E 8
		 * level zero indicates a function.
		 */
		case '(':
			if (!level && token) {
				int	curline;

				if (sp != tok)
					*sp = EOS;
				/*
				 * grab the line immediately, we may
				 * already be wrong, for example,
				 *	foo\n
				 *	(arg1,
				 */
				getline();
				curline = lineno;
				if (func_entry()) {
					++level;
D 8
					pfnote(tok,curline);
E 8
I 8
					pfnote(tok, curline);
E 8
				}
				break;
			}
			goto storec;

		/*
		 * semi-colons indicate the end of a typedef; if we find a
		 * typedef we search for the next semi-colon of the same
		 * level as the typedef.  Ignoring "structs", they are
		 * tricky, since you can find:
		 *
		 *	"typedef long time_t;"
		 *	"typedef unsigned int u_int;"
		 *	"typedef unsigned int u_int [10];"
		 *
		 * If looking at a typedef, we save a copy of the last token
		 * found.  Then, when we find the ';' we take the current
		 * token if it starts with a valid token name, else we take
		 * the one we saved.  There's probably some reasonable
		 * alternative to this...
		 */
		case ';':
			if (t_def && level == t_level) {
				t_def = NO;
				getline();
				if (sp != tok)
					*sp = EOS;
D 8
				pfnote(tok,lineno);
E 8
I 8
				pfnote(tok, lineno);
E 8
				break;
			}
			goto storec;

		/*
		 * store characters until one that can't be part of a token
		 * comes along; check the current token against certain
		 * reserved words.
		 */
		default:
D 8
storec:			if (!intoken(c)) {
E 8
I 8
	storec:		if (!intoken(c)) {
E 8
				if (sp == tok)
					break;
				*sp = EOS;
				if (tflag) {
					/* no typedefs inside typedefs */
D 8
					if (!t_def && !bcmp(tok,"typedef",8)) {
E 8
I 8
					if (!t_def &&
						   !memcmp(tok, "typedef",8)) {
E 8
						t_def = YES;
						t_level = level;
						break;
					}
					/* catch "typedef struct" */
					if ((!t_def || t_level < level)
D 8
					    && (!bcmp(tok,"struct",7)
					    || !bcmp(tok,"union",6)
					    || !bcmp(tok,"enum",5))) {
E 8
I 8
					    && (!memcmp(tok, "struct", 7)
					    || !memcmp(tok, "union", 6)
					    || !memcmp(tok, "enum", 5))) {
E 8
						/*
						 * get line immediately;
						 * may change before '{'
						 */
						getline();
						if (str_entry(c))
							++level;
						break;
I 8
						/* } */
E 8
					}
				}
				sp = tok;
			}
			else if (sp != tok || begtoken(c)) {
				*sp++ = c;
				token = YES;
			}
			continue;
		}
I 8

E 8
		sp = tok;
		token = NO;
	}
}

/*
 * func_entry --
 *	handle a function reference
 */
D 7
static
E 7
I 7
static int
E 7
func_entry()
{
D 8
	register int	c;		/* current character */
I 7
	int		level = 0;	/* for matching '()' */
E 8
I 8
	int	c;			/* current character */
	int	level = 0;		/* for matching '()' */
E 8
E 7

	/*
I 7
	 * Find the end of the assumed function declaration.
	 * Note that ANSI C functions can have type definitions so keep
	 * track of the parentheses nesting level.
	 */
D 8
	while (GETC(!=,EOF)) {
		switch ((char)c) {
E 8
I 8
	while (GETC(!=, EOF)) {
		switch (c) {
E 8
		case '\'':
		case '"':
			/* skip strings and character constants */
			skip_string(c);
			break;
		case '/':
			/* skip comments */
D 8
			if (GETC(==,'*'))
E 8
I 8
			if (GETC(==, '*'))
E 8
				skip_comment();
			break;
		case '(':
			level++;
			break;
		case ')':
			if (level == 0)
				goto fnd;
			level--;
			break;
		case '\n':
			SETLINE;
		}
	}
D 8
	return(NO);
E 8
I 8
	return (NO);
E 8
fnd:
	/*
E 7
	 * we assume that the character after a function's right paren
	 * is a token character if it's a function and a non-token
	 * character if it's a declaration.  Comments don't count...
	 */
D 7
	(void)skip_key((int)')');
E 7
	for (;;) {
D 8
		while (GETC(!=,EOF) && iswhite(c))
			if (c == (int)'\n')
E 8
I 8
		while (GETC(!=, EOF) && iswhite(c))
			if (c == '\n')
E 8
				SETLINE;
D 8
		if (intoken(c) || c == (int)'{')
E 8
I 8
		if (intoken(c) || c == '{')
E 8
			break;
D 8
		if (c == (int)'/' && GETC(==,'*'))
E 8
I 8
		if (c == '/' && GETC(==, '*'))
E 8
			skip_comment();
		else {				/* don't ever "read" '/' */
D 8
			(void)ungetc(c,inf);
			return(NO);
E 8
I 8
			(void)ungetc(c, inf);
			return (NO);
E 8
		}
	}
D 8
	if (c != (int)'{')
		(void)skip_key((int)'{');
	return(YES);
E 8
I 8
	if (c != '{')
		(void)skip_key('{');
	return (YES);
E 8
}

/*
 * hash_entry --
 *	handle a line starting with a '#'
 */
D 5
static
E 5
I 5
static void
E 5
hash_entry()
{
D 8
	extern int	dflag;		/* -d: non-macro defines */
	register int	c,		/* character read */
			curline;	/* line started on */
	register char	*sp;		/* buffer pointer */
E 8
I 8
	int	c;			/* character read */
	int	curline;		/* line started on */
	char	*sp;			/* buffer pointer */
E 8
	char	tok[MAXTOKEN];		/* storage buffer */

	curline = lineno;
	for (sp = tok;;) {		/* get next token */
D 8
		if (GETC(==,EOF))
E 8
I 8
		if (GETC(==, EOF))
E 8
			return;
		if (iswhite(c))
			break;
		*sp++ = c;
	}
	*sp = EOS;
D 8
	if (bcmp(tok,"define",6))	/* only interested in #define's */
E 8
I 8
	if (memcmp(tok, "define", 6))	/* only interested in #define's */
E 8
		goto skip;
	for (;;) {			/* this doesn't handle "#define \n" */
D 8
		if (GETC(==,EOF))
E 8
I 8
		if (GETC(==, EOF))
E 8
			return;
		if (!iswhite(c))
			break;
	}
	for (sp = tok;;) {		/* get next token */
		*sp++ = c;
D 8
		if (GETC(==,EOF))
E 8
I 8
		if (GETC(==, EOF))
E 8
			return;
		/*
		 * this is where it DOESN'T handle
		 * "#define \n"
		 */
		if (!intoken(c))
			break;
	}
	*sp = EOS;
D 8
	if (dflag || c == (int)'(') {	/* only want macros */
E 8
I 8
	if (dflag || c == '(') {	/* only want macros */
E 8
		getline();
D 8
		pfnote(tok,curline);
E 8
I 8
		pfnote(tok, curline);
E 8
	}
D 8
skip:	if (c == (int)'\n') {		/* get rid of rest of define */
E 8
I 8
skip:	if (c == '\n') {		/* get rid of rest of define */
E 8
		SETLINE
		if (*(sp - 1) != '\\')
			return;
	}
D 8
	(void)skip_key((int)'\n');
E 8
I 8
	(void)skip_key('\n');
E 8
}

/*
 * str_entry --
 *	handle a struct, union or enum entry
 */
D 8
static
E 8
I 8
static int
E 8
str_entry(c)
D 8
	register int	c;		/* current character */
E 8
I 8
	int	c;			/* current character */
E 8
{
D 8
	register char	*sp;		/* buffer pointer */
E 8
	int	curline;		/* line started on */
D 8
	char	tok[BUFSIZ];		/* storage buffer */
E 8
I 8
	char	*sp;			/* buffer pointer */
	char	tok[LINE_MAX];		/* storage buffer */
E 8

	curline = lineno;
	while (iswhite(c))
D 8
		if (GETC(==,EOF))
			return(NO);
	if (c == (int)'{')		/* it was "struct {" */
		return(YES);
E 8
I 8
		if (GETC(==, EOF))
			return (NO);
	if (c == '{')		/* it was "struct {" */
		return (YES);
E 8
	for (sp = tok;;) {		/* get next token */
		*sp++ = c;
D 8
		if (GETC(==,EOF))
			return(NO);
E 8
I 8
		if (GETC(==, EOF))
			return (NO);
E 8
		if (!intoken(c))
			break;
	}
D 8
	switch ((char)c) {
E 8
I 8
	switch (c) {
E 8
		case '{':		/* it was "struct foo{" */
			--sp;
			break;
		case '\n':		/* it was "struct foo\n" */
			SETLINE;
			/*FALLTHROUGH*/
		default:		/* probably "struct foo " */
D 8
			while (GETC(!=,EOF))
E 8
I 8
			while (GETC(!=, EOF))
E 8
				if (!iswhite(c))
					break;
D 2
			if (c != (int)'{')
E 2
I 2
D 8
			if (c != (int)'{') {
E 8
I 8
			if (c != '{') {
E 8
				(void)ungetc(c, inf);
E 2
D 8
				return(NO);
E 8
I 8
				return (NO);
E 8
I 2
			}
E 2
	}
	*sp = EOS;
D 8
	pfnote(tok,curline);
	return(YES);
E 8
I 8
	pfnote(tok, curline);
	return (YES);
E 8
}

/*
 * skip_comment --
 *	skip over comment
 */
I 8
void
E 8
skip_comment()
{
D 8
	register int	c,		/* character read */
			star;		/* '*' flag */
E 8
I 8
	int	c;			/* character read */
	int	star;			/* '*' flag */
E 8

D 8
	for (star = 0;GETC(!=,EOF);)
		switch((char)c) {
			/* comments don't nest, nor can they be escaped. */
			case '*':
				star = YES;
				break;
			case '/':
				if (star)
					return;
				break;
			case '\n':
				SETLINE;
				/*FALLTHROUGH*/
			default:
				star = NO;
E 8
I 8
	for (star = 0; GETC(!=, EOF);)
		switch(c) {
		/* comments don't nest, nor can they be escaped. */
		case '*':
			star = YES;
			break;
		case '/':
			if (star)
				return;
			break;
		case '\n':
			SETLINE;
			/*FALLTHROUGH*/
		default:
			star = NO;
			break;
E 8
		}
}

/*
I 7
 * skip_string --
 *	skip to the end of a string or character constant.
 */
void
skip_string(key)
D 8
	register int	key;
E 8
I 8
	int	key;
E 8
{
D 8
	register int	c,
			skip;
E 8
I 8
	int	c,
		skip;
E 8

D 8
	for (skip = NO; GETC(!=,EOF); )
		switch ((char)c) {
E 8
I 8
	for (skip = NO; GETC(!=, EOF); )
		switch (c) {
E 8
		case '\\':		/* a backslash escapes anything */
			skip = !skip;	/* we toggle in case it's "\\" */
			break;
		case '\n':
			SETLINE;
			/*FALLTHROUGH*/
		default:
			if (c == key && !skip)
				return;
			skip = NO;
		}
}

/*
E 7
 * skip_key --
 *	skip to next char "key"
 */
I 7
int
E 7
skip_key(key)
D 8
	register int	key;
E 8
I 8
	int	key;
E 8
{
D 8
	register int	c,
			skip,
			retval;
E 8
I 8
	int	c,
		skip,
		retval;
E 8

D 8
	for (skip = retval = NO;GETC(!=,EOF);)
		switch((char)c) {
E 8
I 8
	for (skip = retval = NO; GETC(!=, EOF);)
		switch(c) {
E 8
		case '\\':		/* a backslash escapes anything */
			skip = !skip;	/* we toggle in case it's "\\" */
			break;
		case ';':		/* special case for yacc; if one */
		case '|':		/* of these chars occurs, we may */
			retval = YES;	/* have moved out of the rule */
			break;		/* not used by C */
I 7
		case '\'':
		case '"':
			/* skip strings and character constants */
			skip_string(c);
			break;
		case '/':
			/* skip comments */
D 8
			if (GETC(==,'*')) {
E 8
I 8
			if (GETC(==, '*')) {
E 8
				skip_comment();
				break;
			}
D 8
			(void)ungetc(c,inf);
E 8
I 8
			(void)ungetc(c, inf);
E 8
			c = '/';
			goto norm;
E 7
		case '\n':
			SETLINE;
			/*FALLTHROUGH*/
		default:
I 7
		norm:
E 7
			if (c == key && !skip)
D 8
				return(retval);
E 8
I 8
				return (retval);
E 8
			skip = NO;
		}
D 8
	return(retval);
E 8
I 8
	return (retval);
E 8
}
E 1
