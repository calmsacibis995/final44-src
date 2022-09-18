h00283
s 00002/00002/00597
d D 8.1 93/06/06 14:52:10 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/00594
d D 5.15 91/02/26 13:54:55 bostic 16 15
c ANSI fixes
e
s 00001/00012/00594
d D 5.14 90/06/01 16:07:39 bostic 15 14
c new copyright notice
e
s 00027/00005/00579
d D 5.13 89/05/15 17:07:57 bostic 14 13
c new version from James Gosling including various bug fixes
e
s 00007/00008/00577
d D 5.12 89/03/05 14:35:42 bostic 13 12
c cleanup from David MacKenzie (mackenzi@thor.stolaf.edu)
e
s 00003/00001/00582
d D 5.11 89/02/17 11:32:56 mckusick 12 11
c avoid bad array references (4.3BSD-tahoe/ucb/36)
e
s 00010/00020/00573
d D 5.10 88/09/15 13:09:13 bostic 11 10
c unused function; lint cleanup; non-portable char comparison
e
s 00004/00001/00589
d D 5.9 88/09/15 12:36:41 bostic 10 9
c indent exits improperly; bug report 4.2BSD/ucb/197
c remove trailing semi-colons on include lines for ANSI C
e
s 00246/00182/00344
d D 5.8 88/09/15 12:19:07 bostic 9 8
c new version from James Gosling <jag@Sun.COM>
e
s 00011/00006/00515
d D 5.7 88/06/29 19:40:43 bostic 8 7
c install approved copyright notice
e
s 00012/00010/00509
d D 5.6 88/03/22 17:31:36 bostic 7 6
c add Berkeley and University of Illinois specific copyright
e
s 00002/00002/00517
d D 5.5 88/01/02 23:57:33 bostic 6 5
c fix include line and cast char for ANSI C
e
s 00003/00000/00516
d D 5.4 87/04/29 18:25:30 bostic 5 4
c indent exits improperly; bug report 4.2BSD/ucb/197
e
s 00000/00000/00516
d D 5.3 85/09/08 15:41:14 mckusick 4 3
c update on Sun stuff by Chris Torek
e
s 00432/00491/00084
d D 5.2 85/08/28 13:47:15 mckusick 3 2
c kernel normal form (from sun!shannon)
e
s 00009/00001/00566
d D 5.1 85/06/04 13:35:44 dist 2 1
c Add copyright
e
s 00567/00000/00000
d D 4.1 82/10/21 23:58:24 mckusick 1 0
c date and time created 82/10/21 23:58:24 by mckusick
e
u
U
t
T
I 1
D 2
static char sccsid[] = "%W%	(Berkeley)	%G%";
E 2
I 2
/*
D 9
 * Copyright (c) 1980 Regents of the University of California.
E 9
I 9
 * Copyright (c) 1985 Sun Microsystems, Inc.
D 17
 * Copyright (c) 1980 The Regents of the University of California.
E 9
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * Copyright (c) 1976 Board of Trustees of the University of Illinois.
E 17
I 17
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 * All rights reserved.
 *
D 15
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley and the University of
 * Illinois at Urbana.  The name of either University may not be used
 * to endorse or promote products derived from this software without
 * specific prior written permission. This software is provided
 * ``as is'' without express or implied warranty.
E 8
I 8
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 9
 * by the University of California, Berkeley and the University
 * of Illinois, Urbana.  The name of either
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
E 9
I 9
 * by the University of California, Berkeley, the University of Illinois,
 * Urbana, and Sun Microsystems, Inc.  The name of either University
 * or Sun Microsystems may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
E 9
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 8
E 7
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 2

D 3
/*

			  Copyright (C) 1976
				by the
			  Board of Trustees
				of the
			University of Illinois

			 All rights reserved


FILE NAME:
	io.c

PURPOSE:
	Contains routines to handle i/o related stuff for indent.

GLOBALS:
	None

FUNCTIONS:
	dump_line
	fill_buffer
	pad_output
	count_spaces
	eqin
	cmp

*/
/*

			  Copyright (C) 1976
				by the
			  Board of Trustees
				of the
			University of Illinois

			 All rights reserved


NAME:
	dump_line

FUNCTION:
	Does the actual printing of the stored up line

ALGORITHM:
	For each of the label, code, and comment sections which are used on 
	this line:

	1) Use pad_output to get the section aligned properly.
	2) write the section

	The indentation level used for the code is set by ind_level.  After
	printing, ind_level is set to i_l_follow.

	An extra level of indentation is added if ind_stmt is 1.  After 
	printing, ind_stmt is set to 1 iff the line just printed has an
	unterminated, non-declaration statement.

PARAMETERS:
	None

RETURNS:
	Nothing

GLOBALS:
	labbuf
	s_lab
	e_lab =		Reset to s_lab

	codebuf
	s_code
	e_code =	Reset to s_code

	combuf
	s_com
	e_com =		Reset to s_com

	bl_line =	Set to true iff the line was blank
	case_ind
	code_lines =	Count lines with code
	com_col
	com_lines =	Keep track of lines with comments
	decl_on_line =	Set to in_decl after line is printed
	i_l_follow
	in_decl
	in_stmt
	ind_level =	Set to i_l_follow at completion
	ind_size
	ind_stmt =	Set to in_stmt at completion if not in declaration
	out_lines =	Count output lines
	p_l_follow
	paren_level =	Set to p_l_follow at completion
	pcase
	use_ff =	Reset to false

CALLS:
	pad_output
	printf (lib)
	write (lib)

CALLED BY:
	main
	pr_comment

HISTORY:
	initial coding 	November 1976	D A Willcox of CAC

*/
E 3
I 3
D 7
/*-
 *			  Copyright (C) 1976
 *				by the
 *			  Board of Trustees
 *				of the
 *			University of Illinois
 *			 All rights reserved
E 7
I 7
D 9
/*
E 7
 * FILE NAME:
 *	io.c
 * PURPOSE:
 *	Contains routines to handle i/o related stuff for indent.
 * GLOBALS:
 *	None
 * FUNCTIONS:
 *	dump_line
 *	fill_buffer
 *	pad_output
 *	count_spaces
 *	eqin
 *	cmp
 *
 */
/*-
 *
 *			  Copyright (C) 1976
 *				by the
 *			  Board of Trustees
 *				of the
 *			University of Illinois
 *
 *			 All rights reserved
 *
 *
 * NAME:
 *	dump_line
 *
 * FUNCTION:
 *	Does the actual printing of the stored up line
 *
 * ALGORITHM:
 *	For each of the label, code, and comment sections which are used on 
 *	this line:
 *
 *	1) Use pad_output to get the section aligned properly.
 *	2) write the section
 *
 *	The indentation level used for the code is set by ps.ind_level.  After
 *	printing, ps.ind_level is set to ps.i_l_follow.
 *
 *	An extra level of indentation is added if ps.ind_stmt is 1.  After 
 *	printing, ps.ind_stmt is set to 1 iff the line just printed has an
 *	unterminated, non-declaration statement.
 *
 * HISTORY:
 *	initial coding 	November 1976	D A Willcox of CAC
 *
 */
E 3
D 6
#include "indent_globs.h";
E 6
I 6
#include "indent_globs.h"
E 9
I 9
D 10
#include "indent_globs.h";
E 10
I 10
D 16
#include "indent_globs.h"
E 16
I 16
#include <stdio.h>
E 16
E 10
#include <ctype.h>
I 16
#include <stdlib.h>
#include <string.h>
#include "indent_globs.h"
E 16
E 9
E 6


D 9

D 3
int     ff = 014;	       /* used to write a form feed */
E 3
I 3
int         ff = 014;		/* used to write a form feed */
E 9
int         comment_open;
static      paren_target;
E 3

I 3
dump_line()
{				/* dump_line is the routine that actually
D 9
				 * effects the printing of the new source.
				 * It prints the label section, followed
				 * by the code section with the
				 * appropriate nesting level, followed by
				 * any comments */
E 9
I 9
				 * effects the printing of the new source. It
				 * prints the label section, followed by the
				 * code section with the appropriate nesting
				 * level, followed by any comments */
E 9
    register int cur_col,
D 11
                temp_col,
E 11
                target_col;
I 9
    static      not_first_line;
E 9
E 3

D 3
dump_line () {		       /* dump_line is the routine that actually
			          effects the printing of the new source.
			          It prints the label section, followed by
			          the code section with the appropriate
			          nesting level, followed by any comments 
			       */
    register int    cur_col,
                    temp_col,
                    target_col;

    bl_line = true;	       /* if we don't find otherwise, assume a
			          blank line */

    if (ind_level == 0)
	ind_stmt = 0;	       /* this is a class A kludge. don't do
			          additional statement indentation if we
			          are at bracket level 0 */

    if (e_lab != s_lab || e_code != s_code)
	++code_lines;	       /* keep count of lines with code */

    if (e_lab != s_lab) {      /* print lab, if any */
	if (pcase)	       /* if the label is really a case, we must
			          indent */
	    cur_col = pad_output (1, case_ind * ind_size + 1);
E 3
I 3
    if (ps.procname[0]) {
D 9
	if (troff)
E 9
I 9
	if (troff) {
	    if (comment_open) {
		comment_open = 0;
		fprintf(output, ".*/\n");
	    }
E 9
	    fprintf(output, ".Pr \"%s\"\n", ps.procname);
I 9
	}
E 9
	ps.ind_level = 0;
	ps.procname[0] = 0;
    }
    if (s_code == e_code && s_lab == e_lab && s_com == e_com) {
D 9
	if (suppress_blanklines>0) suppress_blanklines--;
E 9
I 9
	if (suppress_blanklines > 0)
	    suppress_blanklines--;
E 9
E 3
	else {
D 3
	    if (*s_lab == '#') /* check for #define, etc */
		cur_col = 1;
	    else
		cur_col = pad_output (1, ind_size * (ind_level - label_offset) + 1);
E 3
I 3
D 9
	ps.bl_line = true;
	n_real_blanklines++;
E 9
I 9
	    ps.bl_line = true;
	    n_real_blanklines++;
E 9
E 3
	}
D 3

	write (output, s_lab, e_lab - s_lab);
	cur_col = count_spaces (cur_col, s_lab);
    /* count_spaces gives number of characters, considering tabs */
	bl_line = false;       /* line not blank after all */
E 3
    }
D 3
    else
	cur_col = 1;	       /* there is no label section */
E 3
I 3
    else if (!inhibit_formatting) {
	suppress_blanklines = 0;
	ps.bl_line = false;
D 9
	if (prefix_blankline_requested)
E 9
I 9
	if (prefix_blankline_requested && not_first_line)
E 9
	    if (swallow_optional_blanklines) {
		if (n_real_blanklines == 1)
		    n_real_blanklines = 0;
	    }
	    else {
		if (n_real_blanklines == 0)
		    n_real_blanklines = 1;
	    }
	while (--n_real_blanklines >= 0)
	    putc('\n', output);
	n_real_blanklines = 0;
	if (ps.ind_level == 0)
	    ps.ind_stmt = 0;	/* this is a class A kludge. dont do
D 9
				 * additional statement indentation if we
				 * are at bracket level 0 */
E 9
I 9
				 * additional statement indentation if we are
				 * at bracket level 0 */
E 9
E 3

D 3
    pcase = false;
E 3
I 3
	if (e_lab != s_lab || e_code != s_code)
	    ++code_lines;	/* keep count of lines with code */
E 3

D 3
    if (s_code != e_code) {    /* print code section, if any */
	target_col = ind_size * (ind_level + paren_level + ind_stmt) + 1;
E 3

D 3
	cur_col = pad_output (cur_col, target_col);
    /* pad_output writes enough tabs and spaces to get the current char
       position up to target_col */
	write (output, s_code, e_code - s_code);
	cur_col = count_spaces (cur_col, s_code);
	bl_line = false;       /* line not blank */
    }
E 3
I 3
	if (e_lab != s_lab) {	/* print lab, if any */
	    if (comment_open) {
		comment_open = 0;
		fprintf(output, ".*/\n");
	    }
	    while (e_lab > s_lab && (e_lab[-1] == ' ' || e_lab[-1] == '\t'))
		e_lab--;
	    cur_col = pad_output(1, compute_label_target());
D 14
	    fprintf(output, "%.*s", e_lab - s_lab, s_lab);
E 14
I 14
	    if (s_lab[0] == '#' && (strncmp(s_lab, "#else", 5) == 0
				    || strncmp(s_lab, "#endif", 6) == 0)) {
		register char *s = s_lab;
		if (e_lab[-1] == '\n') e_lab--;
		do putc(*s++, output);
		while (s < e_lab && 'a' <= *s && *s<='z');
		while ((*s == ' ' || *s == '\t') && s < e_lab)
		    s++;
		if (s < e_lab)
		    fprintf(output, s[0]=='/' && s[1]=='*' ? "\t%.*s" : "\t/* %.*s */",
			    e_lab - s, s);
	    }
	    else fprintf(output, "%.*s", e_lab - s_lab, s_lab);
E 14
	    cur_col = count_spaces(cur_col, s_lab);
	}
	else
	    cur_col = 1;	/* there is no label section */
E 3

D 3
    if ((cur_col - 1) > max_col && output!=1)/* check for line too long */
	printf ("%d: Code has %d chars, max is %d\n", line_no, (cur_col - 1), max_col);
E 3
I 3
	ps.pcase = false;
E 3

D 3
    if (s_com != e_com) {      /* print comment, if any */
	if (cur_col > com_col && count_spaces (cur_col, s_com) >= max_col) {
	/* if comment can't fit on this line, put it on next line */
	    write (output, "\n", 1);
	    cur_col = 1;
	    ++out_lines;
E 3
I 3
	if (s_code != e_code) {	/* print code section, if any */
	    register char *p;

	    if (comment_open) {
		comment_open = 0;
		fprintf(output, ".*/\n");
	    }
	    target_col = compute_code_target();
	    {
		register    i;

		for (i = 0; i < ps.p_l_follow; i++)
		    if (ps.paren_indents[i] >= 0)
			ps.paren_indents[i] = -(ps.paren_indents[i] + target_col);
	    }
	    cur_col = pad_output(cur_col, target_col);
	    for (p = s_code; p < e_code; p++)
D 6
		if (*p == 0200)
E 6
I 6
D 9
		if (*p == (char)0200)
E 9
I 9
		if (*p == (char) 0200)
E 9
E 6
		    fprintf(output, "%d", target_col * 7);
		else
		    putc(*p, output);
	    cur_col = count_spaces(cur_col, s_code);
E 3
	}
D 3
	cur_col = pad_output (cur_col, com_col);
	write (output, s_com, e_com - s_com);
E 3
I 3
	if (s_com != e_com)
	    if (troff) {
I 9
		int         all_here = 0;
E 9
		register char *p;
E 3

D 3
	cur_col = count_spaces (cur_col, s_com);
	if ((cur_col - 1) > max_col && output!=1)/* check for too long comment */
	    printf ("%d: Comment goes to column %d.  Max is %d\n",
		line_no, (cur_col - 1), max_col);
E 3
I 3
		if (e_com[-1] == '/' && e_com[-2] == '*')
D 9
		    e_com -= 2;
E 9
I 9
		    e_com -= 2, all_here++;
E 9
		while (e_com > s_com && e_com[-1] == ' ')
		    e_com--;
		*e_com = 0;
		p = s_com;
		while (*p == ' ')
		    p++;
		if (p[0] == '/' && p[1] == '*')
D 9
		    p += 2;
E 9
I 9
		    p += 2, all_here++;
E 9
		else if (p[0] == '*')
		    p += p[1] == '/' ? 2 : 1;
		while (*p == ' ')
		    p++;
		if (*p == 0)
		    goto inhibit_newline;
D 9
		if (!comment_open) {
E 9
I 9
		if (comment_open < 2 && ps.box_com) {
		    comment_open = 0;
		    fprintf(output, ".*/\n");
		}
		if (comment_open == 0) {
E 9
		    if ('a' <= *p && *p <= 'z')
			*p = *p + 'A' - 'a';
D 9
		    if (s_code != e_code || s_lab != e_lab) {
			fprintf(output, "\\c\n./* %dp 1 %dp\n",
				ps.com_col * 7, target_col * 7);
E 9
I 9
		    if (e_com - p < 50 && all_here == 2) {
			register char *follow = p;
			fprintf(output, "\n.nr C! \\w\1");
			while (follow < e_com) {
			    switch (*follow) {
			    case '\n':
				putc(' ', output);
			    case 1:
				break;
			    case '\\':
				putc('\\', output);
			    default:
				putc(*follow, output);
			    }
			    follow++;
			}
			putc(1, output);
E 9
		    }
D 9
		    else
			fprintf(output, "./* %dp 0 %dp\n",
				ps.com_col * 7, target_col * 7);
E 9
I 9
		    fprintf(output, "\n./* %dp %d %dp\n",
			    ps.com_col * 7,
			    (s_code != e_code || s_lab != e_lab) - ps.box_com,
			    target_col * 7);
E 9
		}
D 9
		comment_open = 1;
E 9
I 9
		comment_open = 1 + ps.box_com;
E 9
		while (*p) {
		    if (*p == BACKSLASH)
			putc(BACKSLASH, output);
		    putc(*p++, output);
		}
	    }
	    else {		/* print comment, if any */
		register    target = ps.com_col;
		register char *com_st = s_com;
E 3

D 3
	bl_line = false;
	++com_lines;	       /* count lines with comments */
E 3
I 3
		target += ps.comment_delta;
I 9
		while (*com_st == '\t')
		    com_st++, target += 8;	/* ? */
E 9
		while (target <= 0)
D 9
		    if (*s_com == ' ')
			target++, s_com++;
		    else if (*s_com == '\t')
			target = ((target - 1) & ~7) + 9, s_com++;
E 9
I 9
		    if (*com_st == ' ')
			target++, com_st++;
		    else if (*com_st == '\t')
			target = ((target - 1) & ~7) + 9, com_st++;
E 9
		    else
			target = 1;
D 9
		if (cur_col > target) {	/* if comment cant fit on this
					 * line, put it on next line */
E 9
I 9
		if (cur_col > target) {	/* if comment cant fit on this line,
					 * put it on next line */
E 9
		    putc('\n', output);
		    cur_col = 1;
		    ++ps.out_lines;
		}
I 9
		while (e_com > com_st && isspace(e_com[-1]))
		    e_com--;
E 9
		cur_col = pad_output(cur_col, target);
		if (!ps.box_com) {
D 9
		    if (star_comment_cont && com_st[1] != '*')
			if (com_st[1] == ' ' && com_st[0] == ' ')
E 9
I 9
		    if (star_comment_cont && (com_st[1] != '*' || e_com <= com_st + 1))
			if (com_st[1] == ' ' && com_st[0] == ' ' && e_com > com_st + 1)
E 9
			    com_st[1] = '*';
			else
			    fwrite(" * ", com_st[0] == '\t' ? 2 : com_st[0] == '*' ? 1 : 3, 1, output);
		}
		fwrite(com_st, e_com - com_st, 1, output);
		ps.comment_delta = ps.n_comment_delta;
		cur_col = count_spaces(cur_col, com_st);
		++ps.com_lines;	/* count lines with comments */
	    }
	if (ps.use_ff)
	    putc('\014', output);
	else
	    putc('\n', output);
inhibit_newline:
	++ps.out_lines;
	if (ps.just_saw_decl == 1 && blanklines_after_declarations) {
	    prefix_blankline_requested = 1;
	    ps.just_saw_decl = 0;
	}
	else
	    prefix_blankline_requested = postfix_blankline_requested;
	postfix_blankline_requested = 0;
E 3
    }
D 3

    if (use_ff)
	write (output, &ff, 1);/* end the output with a ff */
    else
	write (output, "\n", 1); /* or a newline */
    use_ff = false;
    *(e_lab = s_lab) = '\0';   /* reset buffers */
E 3
I 3
    ps.decl_on_line = ps.in_decl;	/* if we are in the middle of a
D 9
					 * declaration, remember that fact
					 * for proper comment indentation */
E 9
I 9
					 * declaration, remember that fact for
					 * proper comment indentation */
E 9
    ps.ind_stmt = ps.in_stmt & ~ps.in_decl;	/* next line should be
						 * indented if we have not
D 9
						 * completed this stmt and
						 * if we are not in the
						 * middle of a declaration */
E 9
I 9
						 * completed this stmt and if
						 * we are not in the middle of
						 * a declaration */
E 9
    ps.use_ff = false;
    ps.dumped_decl_indent = 0;
    *(e_lab = s_lab) = '\0';	/* reset buffers */
E 3
    *(e_code = s_code) = '\0';
    *(e_com = s_com) = '\0';
D 3

    ind_level = i_l_follow;
    paren_level = p_l_follow;
    ++out_lines;
    decl_on_line = in_decl;    /* if we are in the middle of a
			          declaration, remember that fact for
			          proper comment indentation */
    ind_stmt = in_stmt & ~in_decl;
 /* next line should be indented if we have not completed this stmt and if
    we are not in the middle of a declaration */

E 3
I 3
    ps.ind_level = ps.i_l_follow;
    ps.paren_level = ps.p_l_follow;
    paren_target = -ps.paren_indents[ps.paren_level - 1];
I 12
D 13
    paren_target = (ps.paren_level > 0 ? -ps.paren_indents[ps.paren_level - 1]
		    : 0);
E 13
E 12
I 9
    not_first_line = 1;
E 9
E 3
    return;
D 13
};
E 13
I 13
}
E 13
D 3
/*
E 3

D 3
			  Copyright (C) 1976
				by the
			  Board of Trustees
				of the
			University of Illinois
E 3
I 3
D 9
compute_code_target() {
E 9
I 9
compute_code_target()
{
E 9
    register    target_col = ps.ind_size * ps.ind_level + 1;
E 3

D 3
			 All rights reserved
E 3
I 3
    if (ps.paren_level)
	if (!lineup_to_parens)
	    target_col += continuation_indent * ps.paren_level;
	else {
	    register    w;
	    register    t = paren_target;
E 3

I 3
	    if ((w = count_spaces(t, s_code) - max_col) > 0
D 9
		&& count_spaces(target_col, s_code) <= max_col) {
E 9
I 9
		    && count_spaces(target_col, s_code) <= max_col) {
E 9
		t -= w + 1;
		if (t > target_col)
		    target_col = t;
	    }
	    else
		target_col = t;
	}
    else if (ps.ind_stmt)
	target_col += continuation_indent;
    return target_col;
}
E 3

D 3
NAME:
	fill_buffer
E 3
I 3
compute_label_target()
{
    return
D 9
	ps.pcase ? (int) (case_ind * ps.ind_size) +1
E 9
I 9
	ps.pcase ? (int) (case_ind * ps.ind_size) + 1
E 9
	: *s_lab == '#' ? 1
D 9
	: ps.ind_size * (ps.ind_level - label_offset) +1;
E 9
I 9
	: ps.ind_size * (ps.ind_level - label_offset) + 1;
E 9
}
E 3

D 3
FUNCTION:
	Reads one block of input into input_buffer
E 3

D 3
ALGORITHM:
	Trivial
E 3
I 3
/*
D 9
 * Copyright (C) 1976 by the Board of Trustees of the University of
 * Illinois 
 *
 * All rights reserved 
 *
 *
 * NAME: fill_buffer 
 *
 * FUNCTION: Reads one block of input into input_buffer 
 *
 * HISTORY: initial coding 	November 1976	D A Willcox of CAC 1/7/77
 * A Willcox of CAC	Added check for switch back to partly full input
 * buffer from temporary buffer 
 *
E 9
I 9
 * Copyright (C) 1976 by the Board of Trustees of the University of Illinois
 * 
 * All rights reserved
 * 
 * 
 * NAME: fill_buffer
 * 
 * FUNCTION: Reads one block of input into input_buffer
 * 
 * HISTORY: initial coding 	November 1976	D A Willcox of CAC 1/7/77 A
 * Willcox of CAC	Added check for switch back to partly full input
 * buffer from temporary buffer
 * 
E 9
D 14
 */
E 14
I 14
 */
E 14
int
fill_buffer()
{				/* this routine reads stuff from the input */
D 11
    int         count;
E 11
    register char *p;
    register int i;
    register FILE *f = input;
E 3

D 3
PARAMETERS:
	None

RETURNS:
	Nothing

GLOBALS:
	in_buffer =
	buf_end =	Set to 1 past last character read in
	buf_ptr =	Set to start of buffer
	be_save =	Set to zero if it was non-zero
	bp_save =	Set to zero

CALLS:
	read (lib)

CALLED BY:
	lexi
	main
	pr_comment

HISTORY:
	initial coding 	November 1976	D A Willcox of CAC
	1/7/77		D A Willcox of CAC	Added check for switch back to
						partly full input buffer from
						temporary buffer 

*/
int     fill_buffer () { /* this routine reads stuff from the input */
    int     count;
    register int    i;

    if (bp_save != 0) {	       /* there is a partly filled input buffer
			          left */
	buf_ptr = bp_save;     /* don't read anything, just switch buffers 
			       */
E 3
I 3
D 9
    if (bp_save != 0) {		/* there is a partly filled input buffer
				 * left */
E 9
I 9
    if (bp_save != 0) {		/* there is a partly filled input buffer left */
E 9
	buf_ptr = bp_save;	/* dont read anything, just switch buffers */
E 3
	buf_end = be_save;
	bp_save = be_save = 0;
	if (buf_ptr < buf_end)
D 3
	    return;	       /* only return if there is really something
			          in this buffer */
E 3
I 3
D 9
	    return;		/* only return if there is really
				 * something in this buffer */
E 9
I 9
	    return;		/* only return if there is really something in
				 * this buffer */
E 9
E 3
    }
D 3

    count = read (input, in_buffer, inp_bufs);

    buf_end = in_buffer + count;
    buf_ptr = in_buffer;

    if (count == 0) {	       /* count of zero means eof */
E 3
I 3
D 11
    p = in_buffer;
    buf_ptr = p;
    while ((*p++ = i = getc(f)) != EOF && i != '\n');
    if (i == EOF) {
	p[-1] = ' ';
	*p++ = '\n';
E 3
	had_eof = true;
E 11
I 11
D 14
    for (p = buf_ptr = in_buffer;;) {
E 14
I 14
    for (p = in_buffer;;) {
	if (p >= in_buffer_limit) {
	    register size = (in_buffer_limit - in_buffer) * 2 + 10;
	    register offset = p - in_buffer;
	    in_buffer = (char *) realloc(in_buffer, size);
	    if (in_buffer == 0)
		err("input line too long");
	    p = in_buffer + offset;
	    in_buffer_limit = in_buffer + size - 2;
	}
E 14
	if ((i = getc(f)) == EOF) {
		*p++ = ' ';
		*p++ = '\n';
		had_eof = true;
		break;
	}
	*p++ = i;
	if (i == '\n')
		break;
E 11
D 3
	*buf_end++ = ' ';
	*buf_end++ = '\n';     /* insert extra newline.  it will
			          eventually get indent to stop */
E 3
    }
I 14
    buf_ptr = in_buffer;
E 14
I 3
    buf_end = p;
D 12
    if (p[-2] == '/' && p[-3] == '*') {
E 12
I 12
D 13
    if (p - in_buffer > 3 && p[-2] == '/' && p[-3] == '*') {
E 13
I 13
    if (p[-2] == '/' && p[-3] == '*') {
E 13
E 12
	if (in_buffer[3] == 'I' && strncmp(in_buffer, "/**INDENT**", 11) == 0)
	    fill_buffer();	/* flush indent error message */
	else {
	    int         com = 0;
E 3

I 3
	    p = in_buffer;
	    while (*p == ' ' || *p == '\t')
		p++;
	    if (*p == '/' && p[1] == '*') {
		p += 2;
		while (*p == ' ' || *p == '\t')
		    p++;
		if (p[0] == 'I' && p[1] == 'N' && p[2] == 'D' && p[3] == 'E'
D 9
		    && p[4] == 'N' && p[5] == 'T') {
E 9
I 9
			&& p[4] == 'N' && p[5] == 'T') {
E 9
		    p += 6;
		    while (*p == ' ' || *p == '\t')
			p++;
		    if (*p == '*')
			com = 1;
		    else if (*p == 'O')
			if (*++p == 'N')
			    p++, com = 1;
			else if (*p == 'F' && *++p == 'F')
			    p++, com = 2;
		    while (*p == ' ' || *p == '\t')
			p++;
		    if (p[0] == '*' && p[1] == '/' && p[2] == '\n' && com) {
			if (s_com != e_com || s_lab != e_lab || s_code != e_code)
			    dump_line();
			if (!(inhibit_formatting = com - 1)) {
			    n_real_blanklines = 0;
			    postfix_blankline_requested = 0;
			    prefix_blankline_requested = 0;
			    suppress_blanklines = 1;
			}
		    }
		}
	    }
	}
    }
    if (inhibit_formatting) {
	p = in_buffer;
	do
	    putc(*p, output);
	while (*p++ != '\n');
    }
E 3
    return;
D 13
};
E 13
I 13
}
E 13
D 3
/*
E 3

D 3
			  Copyright (C) 1976
				by the
			  Board of Trustees
				of the
			University of Illinois

			 All rights reserved


NAME:
	pad_output

FUNCTION:
	Writes tabs and spaces to move the current column up to the
	desired position.

ALGORITHM:
	Put tabs and/or blanks into pobuf, then write pobuf.

PARAMETERS:
	current		integer		The current column
	target		integer		The desired column

RETURNS:
	Integer value of the new column.  (If current >= target,
	no action is taken, and current is returned.

GLOBALS:
	None

CALLS:
	write (sys)

CALLED BY:
	dump_line

HISTORY:
	initial coding 	November 1976	D A Willcox of CAC

*/
int     pad_output (current, target)/* writes tabs and blanks (if necessary) to
			          get the current output position up to
			          the target column */
int     current;	       /* the current column value */
int     target;		       /* position we want it at */
E 3
I 3
/*
D 9
 * Copyright (C) 1976 by the Board of Trustees of the University of
 * Illinois 
 *
 * All rights reserved 
 *
 *
 * NAME: pad_output 
 *
 * FUNCTION: Writes tabs and spaces to move the current column up to the
 * desired position. 
 *
 * ALGORITHM: Put tabs and/or blanks into pobuf, then write pobuf. 
 *
E 9
I 9
 * Copyright (C) 1976 by the Board of Trustees of the University of Illinois
 * 
 * All rights reserved
 * 
 * 
 * NAME: pad_output
 * 
 * FUNCTION: Writes tabs and spaces to move the current column up to the desired
 * position.
 * 
 * ALGORITHM: Put tabs and/or blanks into pobuf, then write pobuf.
 * 
E 9
 * PARAMETERS: current		integer		The current column target
D 9
 * nteger		The desired column 
 *
 * RETURNS: Integer value of the new column.  (If current >= target, no
 * action is taken, and current is returned. 
 *
 * GLOBALS: None 
 *
 * CALLS: write (sys) 
 *
 * CALLED BY: dump_line 
 *
 * HISTORY: initial coding 	November 1976	D A Willcox of CAC 
 *
E 9
I 9
 * nteger		The desired column
 * 
 * RETURNS: Integer value of the new column.  (If current >= target, no action is
 * taken, and current is returned.
 * 
 * GLOBALS: None
 * 
 * CALLS: write (sys)
 * 
 * CALLED BY: dump_line
 * 
 * HISTORY: initial coding 	November 1976	D A Willcox of CAC
 * 
E 9
D 14
 */
E 14
I 14
 */
E 14
D 9
pad_output(current, target)	/* writes tabs and blanks (if necessary)
				 * to get the current output position up
				 * to the target column */
E 9
I 9
pad_output(current, target)	/* writes tabs and blanks (if necessary) to
				 * get the current output position up to the
				 * target column */
E 9
    int         current;	/* the current column value */
    int         target;		/* position we want it at */
E 3
{
D 3
    register int    curr; /* internal column pointer */
    register char  *p; /* pointer into buffer of characters to be written */
    char    pobuf[256]; /* pad characters are stored here before writing */
E 3
I 3
    register int curr;		/* internal column pointer */
E 3
    register int tcur;

D 3
    if (current >= target)
	return (current);      /* line is already long enough */

    curr = current;
    p = pobuf;
    while (curr < target) {
	if ((tcur = ((curr - 1) & tabmask) + tabsize + 1) <= target){
	    *p++ = '\t';       /* put a tab into buffer */
E 3
I 3
    if (troff)
	fprintf(output, "\\h'|%dp'", (target - 1) * 7);
    else {
	if (current >= target)
	    return (current);	/* line is already long enough */
	curr = current;
	while ((tcur = ((curr - 1) & tabmask) + tabsize + 1) <= target) {
	    putc('\t', output);
E 3
	    curr = tcur;
	}
D 3
	else {
	    while (curr++ < target)
		*p++ = ' ';    /* pad with final blanks */
	}
E 3
I 3
	while (curr++ < target)
	    putc(' ', output);	/* pad with final blanks */
E 3
    }
D 3

    write (output, pobuf, p - pobuf); /* write the characters we saved */
E 3
    return (target);
D 13
};
E 13
I 13
}
E 13
D 3
/*
E 3

D 3
			  Copyright (C) 1976
				by the
			  Board of Trustees
				of the
			University of Illinois
E 3
I 3
/*
D 9
 * Copyright (C) 1976 by the Board of Trustees of the University of
 * Illinois 
 *
 * All rights reserved 
 *
 *
 * NAME: count_spaces 
 *
E 9
I 9
 * Copyright (C) 1976 by the Board of Trustees of the University of Illinois
 * 
 * All rights reserved
 * 
 * 
 * NAME: count_spaces
 * 
E 9
 * FUNCTION: Find out where printing of a given string will leave the current
D 9
 * character position on output. 
 *
E 9
I 9
 * character position on output.
 * 
E 9
 * ALGORITHM: Run thru input string and add appropriate values to current
D 9
 * position. 
 *
 * RETURNS: Integer value of position after printing "buffer" starting in
 * column "current". 
 *
 * HISTORY: initial coding 	November 1976	D A Willcox of CAC 
 *
E 9
I 9
 * position.
 * 
 * RETURNS: Integer value of position after printing "buffer" starting in column
 * "current".
 * 
 * HISTORY: initial coding 	November 1976	D A Willcox of CAC
 * 
E 9
D 14
 */
E 14
I 14
 */
E 14
int
count_spaces(current, buffer)
E 3
D 9

E 9
D 3
			 All rights reserved


NAME:
	count_spaces

FUNCTION:
	Find out where printing of a given string will leave the current
	character position on output.

ALGORITHM:
	Run thru input string and add appropriate values to current position.

PARAMETERS:
	current		integer		  The current line character position
	buffer		ptr to character  Pointer to input string

RETURNS:
	Integer value of position after printing "buffer" starting in
	column "current".

GLOBALS:
	None

CALLS:
	None

CALLED BY:
	pr_comment

HISTORY:
	initial coding 	November 1976	D A Willcox of CAC

*/
int     count_spaces (current, buffer)
			       /* this routine figures out where the
			          character position will be after
			          printing the text in buffer starting at
			          column "current" */
int     current;
char   *buffer;
E 3
I 3
/*
 * this routine figures out where the character position will be after
D 9
 * printing the text in buffer starting at column "current" 
E 9
I 9
 * printing the text in buffer starting at column "current"
E 9
 */
    int         current;
    char       *buffer;
E 3
{
D 3
    register char  *buf; /* used to look thru buffer */
    register int    cur; /* current character counter */
E 3
I 3
    register char *buf;		/* used to look thru buffer */
    register int cur;		/* current character counter */
E 3

    cur = current;

    for (buf = buffer; *buf != '\0'; ++buf) {
	switch (*buf) {

D 3
	    case '\n': 
	    case 014: 	       /* form feed */
E 3
I 3
D 9
	    case '\n':
	    case 014:		/* form feed */
E 3
		cur = 1;
		break;
E 9
I 9
	case '\n':
	case 014:		/* form feed */
	    cur = 1;
	    break;
E 9

D 3
	    case '\t': 
E 3
I 3
D 9
	    case '\t':
E 3
		cur = ((cur - 1) & tabmask) + tabsize + 1;
		break;
E 9
I 9
	case '\t':
	    cur = ((cur - 1) & tabmask) + tabsize + 1;
	    break;
E 9

D 3
	    case '': 	       /* this is a backspace */
E 3
I 3
D 9
	    case '':		/* this is a backspace */
E 3
		--cur;
		break;
E 9
I 9
D 13
	case '':		/* this is a backspace */
E 13
I 13
	case 010:		/* backspace */
E 13
	    --cur;
	    break;
E 9

D 3
	    default: 
E 3
I 3
D 9
	    default:
E 3
		++cur;
		break;
E 9
I 9
	default:
	    ++cur;
	    break;
E 9
D 3
	}		       /* end of switch */
    }			       /* end of for loop */

E 3
I 3
	}			/* end of switch */
    }				/* end of for loop */
E 3
    return (cur);
D 13
};
E 13
I 13
}
E 13
D 3
/*
E 3

I 10
int	found_err;
I 13
/* VARARGS2 */
E 13
E 10
I 5
D 9
int	found_err;
E 9
E 5
D 3
			  Copyright (C) 1976
				by the
			  Board of Trustees
				of the
			University of Illinois

			 All rights reserved


NAME:
	eqin

FUNCTION:
	Returns true if the first arg matches the beginning of the second arg.

ALGORITHM:
	Trivial

PARAMETERS:
	str1	pointer to character
	str2	pointer to character

RETURNS:
	1 if first string matches start of second string
	0 otherwise

GLOBALS:
	None

CALLS:
	None

CALLED BY:
	lexi
	main

HISTORY:
	initial coding November 1976 by D A Willcox of CAC

*/
eqin (str1, str2)
char   *str1;
char   *str2;
E 3
I 3
diag(level, msg, a, b)
I 16
	char *msg;
E 16
E 3
{
I 10
    if (level)
	found_err = 1;
E 10
I 5
D 9
    if (level)
	found_err = 1;
E 9
E 5
D 3
    register char  *s1; /* local pointer into first string */
    register char  *s2; /* local pointer into second string */

    s1 = str1;
    s2 = str2;
    while (*s1) {	       /* compare no further than end of first
			          string */
	if (*s2 == 0)	       /* check that second string isn't too short 
			       */
	    return (false);
	if (*s1++ != *s2++)
	    return (false);
E 3
I 3
    if (output == stdout) {
	fprintf(stdout, "/**INDENT** %s@%d: ", level == 0 ? "Warning" : "Error", line_no);
	fprintf(stdout, msg, a, b);
	fprintf(stdout, " */\n");
E 3
    }
D 3

    return (true);
}
/*
			  Copyright (C) 1976
				by the
			  Board of Trustees
				of the
			University of Illinois

			 All rights reserved

NAME:
	cmp

FUNCTION:
	Compares two strings

ALGORITHM:
	Trivial

PARAMETERS:
	a	Pointer to char		First string to compare
	b	Pointer to char		Second string to compare

RETURNS:
	-1 if a < b
	 0 if a = b
	 1 if a > b

GLOBALS:
	None

CALLS:
	None

CALLED BY:
	main

HISTORY:
	1/7/77		D A Willcox of CAC	Initial Coding
*/
int     cmp (a, b)
char   *a;
char   *b;
{
    register char  *ta,
                   *tb;

    ta = a;
    tb = b;

    while (*ta) {
	if (*ta > *tb)
	    return (1);
	if (*ta < *tb)
	    return (-1);
	++ta;
	++tb;
E 3
I 3
    else {
	fprintf(stderr, "%s@%d: ", level == 0 ? "Warning" : "Error", line_no);
	fprintf(stderr, msg, a, b);
	fprintf(stderr, "\n");
E 3
    }
I 9
}

writefdef(f, nm)
    register struct fstate *f;
{
    fprintf(output, ".ds f%c %s\n.nr s%c %d\n",
	    nm, f->font, nm, f->size);
}

char       *
chfont(of, nf, s)
    register struct fstate *of,
               *nf;
    char       *s;
{
    if (of->font[0] != nf->font[0]
	    || of->font[1] != nf->font[1]) {
	*s++ = '\\';
	*s++ = 'f';
	if (nf->font[1]) {
	    *s++ = '(';
	    *s++ = nf->font[0];
	    *s++ = nf->font[1];
	}
	else
	    *s++ = nf->font[0];
    }
    if (nf->size != of->size) {
	*s++ = '\\';
	*s++ = 's';
	if (nf->size < of->size) {
	    *s++ = '-';
	    *s++ = '0' + of->size - nf->size;
	}
	else {
	    *s++ = '+';
	    *s++ = '0' + nf->size - of->size;
	}
    }
    return s;
}

D 11

setfont(f)
    register struct fstate *f;
{
    if (f->font[0] != ps.cfont.font[0]
	    || f->font[1] != ps.cfont.font[1])
	fprintf(output, f->font[1] ? "\\f(%s" : "\\f%s", f->font);
    if (f->size != ps.cfont.size)
	fprintf(output, "\\s%d", f->size);
    ps.cfont = *f;
}
E 11

parsefont(f, s0)
    register struct fstate *f;
    char       *s0;
{
    register char *s = s0;
    int         sizedelta = 0;
    bzero(f, sizeof *f);
    while (*s) {
	if (isdigit(*s))
	    f->size = f->size * 10 + *s - '0';
	else if (isupper(*s))
	    if (f->font[0])
		f->font[1] = *s;
	    else
		f->font[0] = *s;
	else if (*s == 'c')
	    f->allcaps = 1;
	else if (*s == '+')
	    sizedelta++;
	else if (*s == '-')
	    sizedelta--;
	else {
	    fprintf(stderr, "indent: bad font specification: %s\n", s0);
	    exit(1);
	}
	s++;
    }
    if (f->font[0] == 0)
	f->font[0] = 'R';
    if (bodyf.size == 0)
	bodyf.size = 11;
    if (f->size == 0)
	f->size = bodyf.size + sizedelta;
    else if (sizedelta > 0)
	f->size += bodyf.size;
    else
	f->size = bodyf.size - f->size;
E 9
D 3
    if (*tb)
	return (1);
    else
	return (0);
E 3
}
E 1
