h38624
s 00001/00001/00124
d D 8.3 94/04/02 10:08:56 pendry 9 8
c add 1994 copyright
e
s 00042/00035/00083
d D 8.2 94/04/01 13:01:58 pendry 8 7
c prettyness police
e
s 00002/00002/00116
d D 8.1 93/06/06 14:30:02 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00116
d D 5.6 91/02/26 13:42:22 bostic 6 5
c ANSI fixes, use strdup instead of rolling your own
e
s 00001/00011/00116
d D 5.5 90/06/01 15:58:42 bostic 5 4
c new copyright notice
e
s 00001/00001/00126
d D 5.4 90/05/15 19:51:09 bostic 4 3
c string.h is ANSI C include file
e
s 00015/00004/00112
d D 5.3 88/12/31 12:32:36 bostic 3 2
c original by Ken Arnold -- Berkeley copyright
e
s 00000/00002/00116
d D 5.2 87/03/16 18:15:54 bostic 2 1
c fixed line numbers for xflag
e
s 00118/00000/00000
d D 5.1 87/03/16 17:57:37 bostic 1 0
c date and time created 87/03/16 17:57:37 by bostic
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
D 7
 * Copyright (c) 1987 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
D 9
 * Copyright (c) 1987, 1993
E 9
I 9
 * Copyright (c) 1987, 1993, 1994
E 9
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
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
#include <ctype.h>
#include <limits.h>
E 8
D 6
#include <ctags.h>
E 6
I 6
#include <stdio.h>
E 6
D 4
#include <strings.h>
E 4
I 4
#include <string.h>
I 8

E 8
I 6
#include "ctags.h"
E 6
E 4

/*
 * y_entries:
 *	find the yacc tags and put them in.
 */
I 8
void
E 8
y_entries()
{
D 8
	register int	c;
	register char	*sp;
	register bool	in_rule;
E 8
I 8
	int	c;
	char	*sp;
	bool	in_rule;
E 8
	char	tok[MAXTOKEN];

D 2
	(void)strcpy(lbuf,"%%$");		/* special case, "%%" */
	pfnote("yyparse",lineno);
E 2
D 8
	while (GETC(!=,EOF))
		switch ((char)c) {
E 8
I 8
	in_rule = NO;

	while (GETC(!=, EOF))
		switch (c) {
E 8
		case '\n':
			SETLINE;
			/* FALLTHROUGH */
		case ' ':
		case '\f':
		case '\r':
		case '\t':
			break;
		case '{':
D 8
			if (skip_key((int)'}'))
E 8
I 8
			if (skip_key('}'))
E 8
				in_rule = NO;
			break;
		case '\'':
		case '"':
			if (skip_key(c))
				in_rule = NO;
			break;
		case '%':
D 8
			if (GETC(==,'%'))
E 8
I 8
			if (GETC(==, '%'))
E 8
				return;
D 8
			(void)ungetc(c,inf);
E 8
I 8
			(void)ungetc(c, inf);
E 8
			break;
		case '/':
D 8
			if (GETC(==,'*'))
E 8
I 8
			if (GETC(==, '*'))
E 8
				skip_comment();
			else
D 8
				(void)ungetc(c,inf);
E 8
I 8
				(void)ungetc(c, inf);
E 8
			break;
		case '|':
		case ';':
			in_rule = NO;
			break;
		default:
D 8
			if (in_rule || !isalpha(c) && c != (int)'.'
			    && c != (int)'_')
E 8
I 8
			if (in_rule || !isalpha(c) && c != '.' && c != '_')
E 8
				break;
			sp = tok;
			*sp++ = c;
D 8
			while (GETC(!=,EOF) && (intoken(c) || c == (int)'.'))
E 8
I 8
			while (GETC(!=, EOF) && (intoken(c) || c == '.'))
E 8
				*sp++ = c;
			*sp = EOS;
			getline();		/* may change before ':' */
			while (iswhite(c)) {
D 8
				if (c == (int)'\n')
E 8
I 8
				if (c == '\n')
E 8
					SETLINE;
D 8
				if (GETC(==,EOF))
E 8
I 8
				if (GETC(==, EOF))
E 8
					return;
			}
D 8
			if (c == (int)':') {
				pfnote(tok,lineno);
E 8
I 8
			if (c == ':') {
				pfnote(tok, lineno);
E 8
				in_rule = YES;
			}
			else
D 8
				(void)ungetc(c,inf);
E 8
I 8
				(void)ungetc(c, inf);
E 8
		}
}

/*
 * toss_yysec --
 *	throw away lines up to the next "\n%%\n"
 */
I 8
void
E 8
toss_yysec()
{
D 8
	register int	c,			/* read character */
			state;
E 8
I 8
	int	c;			/* read character */
	int	state;
E 8

	/*
	 * state == 0 : waiting
	 * state == 1 : received a newline
	 * state == 2 : received first %
	 * state == 3 : recieved second %
	 */
	lineftell = ftell(inf);
D 8
	for (state = 0;GETC(!=,EOF);)
		switch ((char)c) {
			case '\n':
				++lineno;
				lineftell = ftell(inf);
				if (state == 3)		/* done! */
					return;
				state = 1;		/* start over */
				break;
			case '%':
				if (state)		/* if 1 or 2 */
					++state;	/* goto 3 */
				break;
			default:
				state = 0;		/* reset */
E 8
I 8
	for (state = 0; GETC(!=, EOF);)
		switch (c) {
		case '\n':
			++lineno;
			lineftell = ftell(inf);
			if (state == 3)		/* done! */
				return;
			state = 1;		/* start over */
			break;
		case '%':
			if (state)		/* if 1 or 2 */
				++state;	/* goto 3 */
			break;
		default:
			state = 0;		/* reset */
			break;
E 8
		}
}
E 1
