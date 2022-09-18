h50687
s 00002/00002/00390
d D 8.1 93/06/06 14:52:28 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00388
d D 5.12 91/02/26 13:55:01 bostic 13 12
c ANSI fixes
e
s 00001/00012/00390
d D 5.11 90/06/01 16:08:06 bostic 12 11
c new copyright notice
e
s 00004/00004/00398
d D 5.10 90/03/05 11:36:43 bostic 11 10
c get rid of Reiser style cpp concatenation
e
s 00002/00005/00400
d D 5.9 88/09/15 13:07:39 bostic 10 9
c remove unused variables
e
s 00001/00001/00404
d D 5.8 88/09/15 12:34:28 bostic 9 8
c remove trailing semi-colons on include lines for ANSI C
e
s 00220/00203/00185
d D 5.7 88/09/15 12:19:17 bostic 8 7
c new version from James Gosling <jag@Sun.COM>
e
s 00011/00006/00377
d D 5.6 88/06/29 19:40:54 bostic 7 6
c install approved copyright notice
e
s 00012/00014/00371
d D 5.5 88/03/22 17:31:43 bostic 6 5
c add Berkeley and University of Illinois specific copyright
e
s 00001/00001/00384
d D 5.4 88/01/02 23:58:55 bostic 5 4
c remove trailing semi-colons on include lines for ANSI C
e
s 00000/00000/00385
d D 5.3 85/09/08 15:41:37 mckusick 4 3
c update on Sun stuff by Chris Torek
e
s 00291/00274/00094
d D 5.2 85/08/28 13:48:09 mckusick 3 2
c kernel normal form (from sun!shannon)
e
s 00009/00001/00359
d D 5.1 85/06/04 13:37:21 dist 2 1
c Add copyright
e
s 00360/00000/00000
d D 4.1 82/10/21 23:58:39 mckusick 1 0
c date and time created 82/10/21 23:58:39 by mckusick
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
D 8
 * Copyright (c) 1980 Regents of the University of California.
E 8
I 8
 * Copyright (c) 1985 Sun Microsystems, Inc.
D 14
 * Copyright (c) 1980 The Regents of the University of California.
E 8
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * Copyright (c) 1976 Board of Trustees of the University of Illinois.
E 14
I 14
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 * All rights reserved.
 *
D 12
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley and the University of
 * Illinois at Urbana.  The name of either University may not be used
 * to endorse or promote products derived from this software without
 * specific prior written permission. This software is provided
 * ``as is'' without express or implied warranty.
E 7
I 7
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 8
 * by the University of California, Berkeley and the University
 * of Illinois, Urbana.  The name of either
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
E 8
I 8
 * by the University of California, Berkeley, the University of Illinois,
 * Urbana, and Sun Microsystems, Inc.  The name of either University
 * or Sun Microsystems may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
E 8
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 7
E 6
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6
E 2

I 13
#include <stdio.h>
#include <stdlib.h>
#include "indent_globs.h"

E 13
I 3
D 6
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
E 6
I 6
/*
E 6
 * NAME:
 *	pr_comment
 *
 * FUNCTION:
 *	This routine takes care of scanning and printing comments.
 *
 * ALGORITHM:
 *	1) Decide where the comment should be aligned, and if lines should
 *	   be broken.
 *	2) If lines should not be broken and filled, just copy up to end of
 *	   comment.
 *	3) If lines should be filled, then scan thru input_buffer copying
 *	   characters to com_buf.  Remember where the last blank, tab, or
D 8
 *	   newline was.  When line is filled, print up to last blank and 
E 8
I 8
 *	   newline was.  When line is filled, print up to last blank and
E 8
 *	   continue copying.
 *
 * HISTORY:
 *	November 1976	D A Willcox of CAC	Initial coding
D 8
 *	12/6/76		D A Willcox of CAC	Modification to handle 
E 8
I 8
 *	12/6/76		D A Willcox of CAC	Modification to handle
E 8
 *						UNIX-style comments
 *
 */

E 3
/*
I 3
D 8
 * this routine processes comments.  It makes an attempt to keep comments
 * from going over the max line length.  If a line is too long, it moves
 * everything from the last blank to the next comment line.  Blanks and
 * tabs from the beginning of the input line are removed 
E 8
I 8
 * this routine processes comments.  It makes an attempt to keep comments from
 * going over the max line length.  If a line is too long, it moves everything
 * from the last blank to the next comment line.  Blanks and tabs from the
 * beginning of the input line are removed
E 8
 */
E 3
D 13

D 3
			  Copyright (C) 1976
				by the
			  Board of Trustees
				of the
			University of Illinois

			 All rights reserved


NAME:
	pr_comment

FUNCTION:
	This routine takes care of scanning and printing comments.

ALGORITHM:
	1) Decide where the comment should be aligned, and if lines should
	   be broken.
	2) If lines should not be broken and filled, just copy up to end of
	   comment.
	3) If lines should be filled, then scan thru input_buffer copying
	   characters to com_buf.  Remember where the last blank, tab, or
	   newline was.  When line is filled, print up to last blank and 
	   continue copying.

PARAMETERS:
	None

RETURNS:
	Nothing

GLOBALS:
	combuf =
	s_com
	e_com =

	buf_ptr =
	buf_end

	bl_line
	col_1
	com_col =
	com_ind
	decl_com_ind
	decl_on_line
	had_eof
	ind_level
	ind_size
	line_no =
	max_col
	out_com =	Count number of comments
	unindent_displace
	use_ff =

CALLS:
	count_spaces
	dump_line
	fill_buffer
	printf		(lib)

CALLED BY:
	main

HISTORY:
	November 1976	D A Willcox of CAC	Initial coding
	12/6/76		D A Willcox of CAC	Modification to handle 
						UNIX-style comments

*/

/* this routine processes comments.  It makes an attempt to keep comments from
   going over the max line length.  If a line is too long, it moves everything
   from the last blank to the next comment line.  Blanks and tabs from the
   beginning of the input line are removed */

E 3
D 5
#include "indent_globs.h";
E 5
I 5
D 8
#include "indent_globs.h"
E 8
E 5

I 8
D 9
#include "indent_globs.h";
E 9
I 9
#include "indent_globs.h"
E 13
E 9
E 8

I 8

E 8
D 3
pr_comment () {
    int     now_col;
 /* column we are in now */
    int     box_com;
 /* set to true when we are in a "boxed" comment. In that case, the first
    non-blank char should be lined up with the / in /* */
    int     col_1_com;
 /* this comment should not be touched */
    char   *last_bl;
 /* points to the last blank in the output buffer */
    char    achar;
    char   *t_ptr; /* used for movinf string */
    int     unix_comment;
 /* tri-state variable used to decide if it is a unix-style comment. 0 means
    only blanks since /*, 1 means regular style comment, 2 means unix style
    comment */
E 3
I 3
pr_comment()
{
    int         now_col;	/* column we are in now */
    int         adj_max_col;	/* Adjusted max_col for when we decide to
				 * spill comments over the right margin */
D 10
    int         col_1_com;	/* this comment should not be touched */
E 10
    char       *last_bl;	/* points to the last blank in the output
				 * buffer */
D 10
    char        achar;
E 10
    char       *t_ptr;		/* used for moving string */
D 8
    int         unix_comment;	/* tri-state variable used to decide if it
				 * is a unix-style comment. 0 means only
				 * blanks since /*, 1 means regular style
				 * comment, 2 means unix style comment */
E 8
I 8
    int         unix_comment;	/* tri-state variable used to decide if it is
				 * a unix-style comment. 0 means only blanks
				 * since /*, 1 means regular style comment, 2
				 * means unix style comment */
E 8
    int         break_delim = comment_delimiter_on_blankline;
D 8
    int		l_just_saw_decl = ps.just_saw_decl;
E 8
I 8
    int         l_just_saw_decl = ps.just_saw_decl;
E 8
    /*
D 8
     * int         ps.last_nl = 0;	/* true iff the last significant
     * thing weve seen is a newline 
E 8
I 8
     * int         ps.last_nl = 0;	/* true iff the last significant thing
     * weve seen is a newline
E 8
     */
    int         one_liner = 1;	/* true iff this comment is a one-liner */
    adj_max_col = max_col;
    ps.just_saw_decl = 0;
    last_bl = 0;		/* no blanks found so far */
D 8
    ps.box_com = col_1_com = false;	/* at first, assume that we are
					 * not in a boxed comment or some
					 * other comment that should not
					 * be touched */
E 8
I 8
D 10
    ps.box_com = col_1_com = false;	/* at first, assume that we are not in
E 10
I 10
    ps.box_com = false;		/* at first, assume that we are not in
E 10
					 * a boxed comment or some other
					 * comment that should not be touched */
E 8
    ++ps.out_coms;		/* keep track of number of comments */
D 8
    unix_comment = 1;		/* set flag to let us figure out if there
				 * is a unix-style comment ** DISABLED:
				 * use 0 to reenable this hack! */
E 8
I 8
    unix_comment = 1;		/* set flag to let us figure out if there is a
				 * unix-style comment ** DISABLED: use 0 to
				 * reenable this hack! */
E 8
E 3

I 3
    /* Figure where to align and how to treat the comment */
E 3

D 3
    last_bl = 0;	       /* no blanks found so far */
    box_com = col_1_com = false;
 /* at first, assume that we are not in a boxed comment or some other comment
    that should not be touched */
    ++out_coms;		       /* keep track of number of comments */
    unix_comment = 0;	       /* set flag to let us figure out if there is a
			          unix-style comment */

/*----------------------------------------------------------*\ 
|   Figure where to align and how to treat the comment
\*----------------------------------------------------------*/

    if (col_1) {	       /* if comment starts in column 1 it should not
			          be touched */
	col_1_com = box_com = true;
	com_col = 1;
    }
    else {
	if (*buf_ptr == '-')
	    box_com = true;    /* a comment with a '-' immediately after the /*
			          is assumed to be a boxed comment */
	if ( /* bl_line && */ (s_lab == e_lab) && (s_code == e_code)) {
	/* klg: check only if this line is blank */
	/* 
	 * If this (*and previous lines are*) blank,
	 * don't put comment way out at left
	 */
	    com_col = (ind_level - unindent_displace) * ind_size + 1;
	    if (com_col <= 1)
		com_col = 2;
E 3
I 3
D 8
    if (ps.col_1 && !format_col1_comments) {	/* if comment starts in
						 * column 1 it should not
						 * be touched */
E 8
I 8
    if (ps.col_1 && !format_col1_comments) {	/* if comment starts in column
						 * 1 it should not be touched */
E 8
D 10
	col_1_com = ps.box_com = true;
E 10
I 10
	ps.box_com = true;
E 10
	ps.com_col = 1;
D 8
    } else {
E 8
I 8
    }
    else {
E 8
	if (*buf_ptr == '-' || *buf_ptr == '*') {
	    ps.box_com = true;	/* a comment with a '-' or '*' immediately
				 * after the /* is assumed to be a boxed
				 * comment */
D 10
	    col_1_com = true;
E 10
	    break_delim = 0;
E 3
	}
D 3
	else {
	    com_col = (decl_on_line || ind_level == 0 ? decl_com_ind : com_ind);
E 3
I 3
	if ( /* ps.bl_line && */ (s_lab == e_lab) && (s_code == e_code)) {
	    /* klg: check only if this line is blank */
	    /*
D 8
	     * If this (*and previous lines are*) blank, dont put comment
	     * way out at left 
E 8
I 8
	     * If this (*and previous lines are*) blank, dont put comment way
	     * out at left
E 8
	     */
	    ps.com_col = (ps.ind_level - ps.unindent_displace) * ps.ind_size + 1;
	    adj_max_col = block_comment_max_col;
	    if (ps.com_col <= 1)
		ps.com_col = 1 + !format_col1_comments;
D 8
	} else {
E 8
I 8
	}
	else {
E 8
	    register    target_col;
	    break_delim = 0;
	    if (s_code != e_code)
		target_col = count_spaces(compute_code_target(), s_code);
	    else {
		target_col = 1;
		if (s_lab != e_lab)
		    target_col = count_spaces(compute_label_target(), s_lab);
	    }
	    ps.com_col = ps.decl_on_line || ps.ind_level == 0 ? ps.decl_com_ind : ps.com_ind;
	    if (ps.com_col < target_col)
		ps.com_col = ((target_col + 7) & ~7) + 1;
	    if (ps.com_col + 24 > adj_max_col)
		adj_max_col = ps.com_col + 24;
E 3
	}
    }
D 3

    *e_com++ = '/';	       /* put '/*' into buffer */
E 3
I 3
    if (ps.box_com) {
	buf_ptr[-2] = 0;
	ps.n_comment_delta = 1 - count_spaces(1, in_buffer);
D 8
	ps.comment_delta = 0;
E 8
	buf_ptr[-2] = '/';
D 8
    } else {
E 8
I 8
    }
    else {
E 8
	ps.n_comment_delta = 0;
D 8
	ps.comment_delta = 0;
E 8
	while (*buf_ptr == ' ' || *buf_ptr == '\t')
	    buf_ptr++;
    }
    ps.comment_delta = 0;
    *e_com++ = '/';		/* put '/*' into buffer */
E 3
    *e_com++ = '*';
D 3
    if (*buf_ptr != ' ' && !box_com)
E 3
I 3
    if (*buf_ptr != ' ' && !ps.box_com)
E 3
	*e_com++ = ' ';

    *e_com = '\0';
D 3
    now_col = count_spaces (com_col, s_com);
 /* figure where what column we would be in if we printed the comment now */
E 3
I 3
D 8
    now_col = count_spaces(ps.com_col, s_com);	/* figure what column we
						 * would be in if we
						 * printed the comment now */
E 8
I 8
    if (troff) {
	now_col = 1;
	adj_max_col = 80;
    }
    else
	now_col = count_spaces(ps.com_col, s_com);	/* figure what column we
							 * would be in if we
							 * printed the comment
							 * now */
E 8
E 3

I 3
    /* Start to copy the comment */
E 3

D 3
/*----------------------------------------------------------*\ 
|    Start to copy the comment
\*----------------------------------------------------------*/

    while (1) {		       /* this loop will go until the comment is copied 
			       */
	switch (*buf_ptr) {    /* this checks for various spcl cases */
	    case 014: 	       /* check for a form feed */
		if (!box_com) {/* in a text comment, break the line here */
		    use_ff = true;
		/* fix so dump_line uses a form feed */
		    dump_line ();
E 3
I 3
    while (1) {			/* this loop will go until the comment is
				 * copied */
	if (*buf_ptr > 040 && *buf_ptr != '*')
	    ps.last_nl = 0;
I 8
D 11
	check_size(com);
E 11
I 11
	CHECK_SIZE_COM;
E 11
E 8
	switch (*buf_ptr) {	/* this checks for various spcl cases */
D 8
	    case 014:		/* check for a form feed */
		if (!ps.box_com) {	/* in a text comment, break the
					 * line here */
		    ps.use_ff = true;
		    /* fix so dump_line uses a form feed */
		    dump_line();
E 3
		    last_bl = 0;
E 8
I 8
	case 014:		/* check for a form feed */
	    if (!ps.box_com) {	/* in a text comment, break the line here */
		ps.use_ff = true;
		/* fix so dump_line uses a form feed */
		dump_line();
		last_bl = 0;
		*e_com++ = ' ';
		*e_com++ = '*';
		*e_com++ = ' ';
		while (*++buf_ptr == ' ' || *buf_ptr == '\t');
	    }
	    else {
		if (++buf_ptr >= buf_end)
		    fill_buffer();
		*e_com++ = 014;
	    }
	    break;

	case '\n':
	    if (had_eof) {	/* check for unexpected eof */
		printf("Unterminated comment\n");
		*e_com = '\0';
		dump_line();
		return;
	    }
	    one_liner = 0;
	    if (ps.box_com || ps.last_nl) {	/* if this is a boxed comment,
						 * we dont ignore the newline */
		if (s_com == e_com) {
E 8
		    *e_com++ = ' ';
I 3
D 8
		    *e_com++ = '*';
E 8
E 3
		    *e_com++ = ' ';
D 3
		    *e_com++ = ' ';
		    do {       /* get rid of leading blanks */
			if (++buf_ptr >= buf_end)
			    fill_buffer ();
		    } while (*buf_ptr == ' ' || *buf_ptr == '\t');
		}
		else {
E 3
I 3
D 8
		    while (*++buf_ptr == ' ' || *buf_ptr == '\t');
		} else {
E 3
		    if (++buf_ptr >= buf_end)
D 3
			fill_buffer ();
E 3
I 3
			fill_buffer();
E 3
		    *e_com++ = 014;
E 8
		}
D 3

E 3
D 8
		break;

D 3
	    case '\n': 
		if (had_eof) { /* check for unexpected eof */
		    printf ("Unterminated comment\n");
E 3
I 3
	    case '\n':
		if (had_eof) {	/* check for unexpected eof */
		    printf("Unterminated comment\n");
E 3
		    *e_com = '\0';
D 3
		    dump_line ();
E 3
I 3
		    dump_line();
E 3
		    return;
		}
D 3

		if (box_com) { /* if this is a boxed comment, we don't ignore
			          the newline */
E 3
I 3
		one_liner = 0;
		if (ps.box_com || ps.last_nl) {	/* if this is a boxed
						 * comment, we dont ignore
						 * the newline */
		    if (s_com == e_com) {
			*e_com++ = ' ';
			*e_com++ = ' ';
		    }
E 3
		    *e_com = '\0';
D 3
		    dump_line ();
		    ++line_no;
		    now_col = com_col;

		    if (!col_1_com) {
		    /* if merely a boxed comment, we should line up first
		       non-blank character */
			do {   /* flush leading non-blanks */
			    if (++buf_ptr >= buf_end)
				fill_buffer ();
			} while (*buf_ptr == ' ' || *buf_ptr == '\t');
E 3
I 3
		    if (!ps.box_com && e_com - s_com > 3) {
			if (break_delim == 1 && s_com[0] == '/'
E 8
I 8
		*e_com = '\0';
		if (!ps.box_com && e_com - s_com > 3) {
		    if (break_delim == 1 && s_com[0] == '/'
E 8
			    && s_com[1] == '*' && s_com[2] == ' ') {
D 8
			    char       *t = e_com;
			    break_delim = 2;
			    e_com = s_com + 2;
			    *e_com = 0;
			    if (blanklines_before_blockcomments) prefix_blankline_requested = 1;
			    dump_line();
			    e_com = t;
			    s_com[0] = s_com[1] = s_com[2] = ' ';
			}
E 8
I 8
			char       *t = e_com;
			break_delim = 2;
			e_com = s_com + 2;
			*e_com = 0;
			if (blanklines_before_blockcomments)
			    prefix_blankline_requested = 1;
E 8
			dump_line();
D 8
			*e_com++ = ' ';
			*e_com++ = ' ';
E 8
I 8
			e_com = t;
			s_com[0] = s_com[1] = s_com[2] = ' ';
E 8
E 3
		    }
D 3
		    else {     /* make sure we at least flush the blank */
			if (++buf_ptr >= buf_end)
			    fill_buffer ();
		    }

		    break;
		}

		if (unix_comment != 1) {
		/* we are in unix_style comment */
E 3
I 3
		    dump_line();
D 8
		    now_col = ps.com_col;
		} else {
E 8
I 8
D 11
		    check_size(com);
E 11
I 11
		    CHECK_SIZE_COM;
E 11
		    *e_com++ = ' ';
		    *e_com++ = ' ';
		}
		dump_line();
		now_col = ps.com_col;
	    }
	    else {
E 8
		ps.last_nl = 1;
D 8
		if (unix_comment != 1) {	/* we not are in
						 * unix_style comment */
E 8
I 8
		if (unix_comment != 1) {	/* we not are in unix_style
						 * comment */
E 8
E 3
		    if (unix_comment == 0 && s_code == e_code) {
D 3
		    /* if it is a UNIX-style comment, ignore the requirement
		       that pervious line be blank for unindention */
			com_col = (ind_level - unindent_displace) * ind_size + 1;
			if (com_col <= 1)
			    com_col = 2;
E 3
I 3
			/*
			 * if it is a UNIX-style comment, ignore the
			 * requirement that previous line be blank for
D 8
			 * unindention 
E 8
I 8
			 * unindention
E 8
			 */
			ps.com_col = (ps.ind_level - ps.unindent_displace) * ps.ind_size + 1;
			if (ps.com_col <= 1)
			    ps.com_col = 2;
E 3
		    }
D 3

		    unix_comment = 2;
		/* permanently remember that we are in this type of comment */
		    dump_line ();
E 3
I 3
D 8
		    unix_comment = 2;	/* permanently remember that we
					 * are in this type of comment */
E 8
I 8
		    unix_comment = 2;	/* permanently remember that we are in
					 * this type of comment */
E 8
		    dump_line();
E 3
		    ++line_no;
D 3
		    now_col = com_col;
E 3
I 3
		    now_col = ps.com_col;
E 3
		    *e_com++ = ' ';
D 3
		/* fix so that the star at the start of the line will line up 
		*/
		    do	       /* flush leading white space */
E 3
I 3
		    /*
D 8
		     * fix so that the star at the start of the line will
		     * line up 
E 8
I 8
		     * fix so that the star at the start of the line will line
		     * up
E 8
		     */
		    do		/* flush leading white space */
E 3
			if (++buf_ptr >= buf_end)
D 3
			    fill_buffer ();
E 3
I 3
			    fill_buffer();
E 3
		    while (*buf_ptr == ' ' || *buf_ptr == '\t');
		    break;
		}
D 3

E 3
		if (*(e_com - 1) == ' ' || *(e_com - 1) == '\t')
		    last_bl = e_com - 1;
D 3
	    /* if there was a space at the end of the last line, remember where
	       it was */
		else {	       /* otherwise, insert one */
E 3
I 3
		/*
D 8
		 * if there was a space at the end of the last line,
		 * remember where it was 
E 8
I 8
		 * if there was a space at the end of the last line, remember
		 * where it was
E 8
		 */
		else {		/* otherwise, insert one */
E 3
		    last_bl = e_com;
I 8
D 11
		    check_size(com);
E 11
I 11
		    CHECK_SIZE_COM;
E 11
E 8
		    *e_com++ = ' ';
		    ++now_col;
		}
I 3
D 8
		}
		++line_no;	/* keep track of input line number */
		if (!ps.box_com) {
		    int         nstar = 1;
		    do {	/* flush any blanks and/or tabs at start
				 * of next line */
E 8
I 8
	    }
	    ++line_no;		/* keep track of input line number */
	    if (!ps.box_com) {
		int         nstar = 1;
		do {		/* flush any blanks and/or tabs at start of
				 * next line */
		    if (++buf_ptr >= buf_end)
			fill_buffer();
		    if (*buf_ptr == '*' && --nstar >= 0) {
E 8
			if (++buf_ptr >= buf_end)
			    fill_buffer();
D 8
			if (*buf_ptr == '*' && --nstar >= 0) {
			    if (++buf_ptr >= buf_end)
				fill_buffer();
			    if (*buf_ptr == '/')
				goto end_of_comment;
			}
		    } while (*buf_ptr == ' ' || *buf_ptr == '\t');
		} else if (++buf_ptr >= buf_end) fill_buffer();
		break;		/* end of case for newline */
E 8
I 8
			if (*buf_ptr == '/')
			    goto end_of_comment;
		    }
		} while (*buf_ptr == ' ' || *buf_ptr == '\t');
	    }
	    else if (++buf_ptr >= buf_end)
		fill_buffer();
	    break;		/* end of case for newline */
E 8
E 3

D 3
		++line_no;     /* keep track of input line number */
		do {	       /* copy any blanks and/or tabs at start of next
			          line */
		    if (++buf_ptr >= buf_end)
			fill_buffer ();
		} while (*buf_ptr == ' ' || *buf_ptr == '\t');
E 3
I 3
D 8
	    case '*':		/* must check for possibility of being at
				 * end of comment */
		if (++buf_ptr >= buf_end)	/* get to next char after * */
		    fill_buffer();
E 8
I 8
	case '*':		/* must check for possibility of being at end
				 * of comment */
	    if (++buf_ptr >= buf_end)	/* get to next char after * */
		fill_buffer();
E 8
E 3

D 3
		break;	       /* end of case for newline */

	    case '*': 	       /* must check for possibility of being at end of
			          comment */
		if (++buf_ptr >= buf_end)
			       /* get to next char after * */
		    fill_buffer ();

		if (unix_comment == 0)
			       /* set flag to show we are not in unix-style
			          comment */
E 3
I 3
D 8
		if (unix_comment == 0)	/* set flag to show we are not in
E 8
I 8
	    if (unix_comment == 0)	/* set flag to show we are not in
E 8
					 * unix-style comment */
E 3
D 8
		    unix_comment = 1;
E 8
I 8
		unix_comment = 1;
E 8

D 3
		if (*buf_ptr == '/') {
		/* it is the end!!! */
E 3
I 3
D 8
		if (*buf_ptr == '/') {	/* it is the end!!! */
	    end_of_comment:
E 3
		    if (++buf_ptr >= buf_end)
D 3
			fill_buffer ();
E 3
I 3
			fill_buffer();
E 8
I 8
	    if (*buf_ptr == '/') {	/* it is the end!!! */
	end_of_comment:
		if (++buf_ptr >= buf_end)
		    fill_buffer();
E 8
E 3

D 3
		    if (*(e_com - 1) != ' ' && !box_com) {
		    /* insure blank before end */
E 3
I 3
D 8
		    if (*(e_com - 1) != ' ' && !ps.box_com) {	/* insure blank before
E 8
I 8
		if (*(e_com - 1) != ' ' && !ps.box_com) {	/* insure blank before
E 8
								 * end */
E 3
D 8
			*e_com++ = ' ';
			++now_col;
		    }
D 3

		    if (now_col > max_col - 2 && !box_com) {
		    /* check if star-slash will go over line */
E 3
I 3
		    if (break_delim == 1 && !one_liner && s_com[0] == '/'
E 8
I 8
		    *e_com++ = ' ';
		    ++now_col;
		}
		if (break_delim == 1 && !one_liner && s_com[0] == '/'
E 8
			&& s_com[1] == '*' && s_com[2] == ' ') {
D 8
			char       *t = e_com;
			break_delim = 2;
			e_com = s_com + 2;
			*e_com = 0;
			    if (blanklines_before_blockcomments) prefix_blankline_requested = 1;
			dump_line();
			e_com = t;
			s_com[0] = s_com[1] = s_com[2] = ' ';
		    }
		    if (break_delim == 2 && e_com > s_com + 3
E 8
I 8
		    char       *t = e_com;
		    break_delim = 2;
		    e_com = s_com + 2;
		    *e_com = 0;
		    if (blanklines_before_blockcomments)
			prefix_blankline_requested = 1;
		    dump_line();
		    e_com = t;
		    s_com[0] = s_com[1] = s_com[2] = ' ';
		}
		if (break_delim == 2 && e_com > s_com + 3
E 8
			 /* now_col > adj_max_col - 2 && !ps.box_com */ ) {
E 3
D 8
			*e_com = '\0';
D 3
		    /* it will */
			dump_line ();
			now_col = com_col;
E 3
I 3
			dump_line();
			now_col = ps.com_col;
E 3
		    }
D 3

E 3
		    *e_com++ = '*';
D 3
		/* move end of comment */
E 3
		    *e_com++ = '/';
E 8
		    *e_com = '\0';
D 3
		    return;    /* we is done */
		}	       /* end of end of comment */


		else {	       /* handle isolated '*' */
E 3
I 3
D 8
		    ps.just_saw_decl = l_just_saw_decl;
		    return;
		} else {	/* handle isolated '*' */
E 3
		    *e_com++ = '*';
		    ++now_col;
E 8
I 8
		    dump_line();
		    now_col = ps.com_col;
E 8
D 3
		    break;
E 3
		}
D 3
	    /* end of processing of * */

	    default: 	       /* we have a random char */
E 3
I 3
D 8
		break;
	    default:		/* we have a random char */
E 3
		if (unix_comment == 0 && *buf_ptr != ' ' && *buf_ptr != '\t')
D 3
		    unix_comment = 1;
	    /* we are not in unix-style comment */
E 3
I 3
		    unix_comment = 1;	/* we are not in unix-style
					 * comment */
E 8
I 8
D 11
		check_size(com);
E 11
I 11
		CHECK_SIZE_COM;
E 11
		*e_com++ = '*';
		*e_com++ = '/';
		*e_com = '\0';
		ps.just_saw_decl = l_just_saw_decl;
		return;
	    }
	    else {		/* handle isolated '*' */
		*e_com++ = '*';
		++now_col;
	    }
	    break;
	default:		/* we have a random char */
	    if (unix_comment == 0 && *buf_ptr != ' ' && *buf_ptr != '\t')
		unix_comment = 1;	/* we are not in unix-style comment */
E 8
E 3

D 8
		*e_com = *buf_ptr++;
		if (buf_ptr >= buf_end)
D 3
		    fill_buffer ();
E 3
I 3
		    fill_buffer();
E 8
I 8
	    *e_com = *buf_ptr++;
	    if (buf_ptr >= buf_end)
		fill_buffer();
E 8
E 3

D 3
		if (*e_com == '\t')
			       /* keep track of column */
E 3
I 3
D 8
		if (*e_com == '\t')	/* keep track of column */
E 3
		    now_col = ((now_col - 1) & tabmask) + tabsize + 1;
I 3
		else if (*e_com == '\b')	/* this is a backspace */
		    --now_col;
E 3
		else
D 3
		    if (*e_com == '')
			       /* this is a backspace */
			--now_col;
		    else
			++now_col;
E 3
I 3
		    ++now_col;
E 8
I 8
	    if (*e_com == '\t')	/* keep track of column */
		now_col = ((now_col - 1) & tabmask) + tabsize + 1;
	    else if (*e_com == '\b')	/* this is a backspace */
		--now_col;
	    else
		++now_col;
E 8
E 3

D 8
		if (*e_com == ' ' || *e_com == '\t')
		    last_bl = e_com;
D 3
	    /* remember we saw a blank */
E 3
I 3
		/* remember we saw a blank */
E 8
I 8
	    if (*e_com == ' ' || *e_com == '\t')
		last_bl = e_com;
	    /* remember we saw a blank */
E 8
E 3

D 8
		++e_com;
D 3
		if (now_col > max_col && !box_com && unix_comment == 1) {
		/* the comment is too long, it must be broken up */
		    if (last_bl == 0) {
		    /* we have seen no blanks */
			printf ("%d: Comment too long\n", line_no);
			last_bl = e_com;
		    /* fake it */
E 3
I 3
		if (now_col > adj_max_col && !ps.box_com && unix_comment == 1 && e_com[-1] > ' ') {
		    /* the comment is too long, it must be broken up */
		    if (break_delim == 1 && s_com[0] == '/'
E 8
I 8
	    ++e_com;
	    if (now_col > adj_max_col && !ps.box_com && unix_comment == 1 && e_com[-1] > ' ') {
		/*
		 * the comment is too long, it must be broken up
		 */
		if (break_delim == 1 && s_com[0] == '/'
E 8
			&& s_com[1] == '*' && s_com[2] == ' ') {
D 8
			char       *t = e_com;
			break_delim = 2;
			e_com = s_com + 2;
			*e_com = 0;
			    if (blanklines_before_blockcomments) prefix_blankline_requested = 1;
			dump_line();
			e_com = t;
			s_com[0] = s_com[1] = s_com[2] = ' ';
		    }
		    if (last_bl == 0) {	/* we have seen no blanks */
			last_bl = e_com;	/* fake it */
E 3
			*e_com++ = ' ';
		    }
D 3

		    *e_com = '\0';
		/* print what we have */
E 3
I 3
		    *e_com = '\0';	/* print what we have */
E 3
		    *last_bl = '\0';
I 3
		    while (last_bl > s_com && last_bl[-1] < 040)
			*--last_bl = 0;
E 3
		    e_com = last_bl;
E 8
I 8
		    char       *t = e_com;
		    break_delim = 2;
		    e_com = s_com + 2;
		    *e_com = 0;
		    if (blanklines_before_blockcomments)
			prefix_blankline_requested = 1;
E 8
D 3
		    dump_line ();
E 3
I 3
		    dump_line();
E 3
D 8

I 3
		    *e_com++ = ' ';	/* add blanks for continuation */
E 8
I 8
		    e_com = t;
		    s_com[0] = s_com[1] = s_com[2] = ' ';
		}
		if (last_bl == 0) {	/* we have seen no blanks */
		    last_bl = e_com;	/* fake it */
E 8
E 3
		    *e_com++ = ' ';
D 3
		/* add blanks for continuation */
E 3
D 8
		    *e_com++ = ' ';
E 8
I 8
		}
		*e_com = '\0';	/* print what we have */
		*last_bl = '\0';
		while (last_bl > s_com && last_bl[-1] < 040)
		    *--last_bl = 0;
		e_com = last_bl;
		dump_line();
E 8
D 3
		    *e_com++ = ' ';
E 3

D 8
		    t_ptr = last_bl + 1;
		    last_bl = 0;
D 3
		    while (*t_ptr != '\0') {
		    /* move unprinted pare of comment down in buffer */
			if (*t_ptr == ' ' || *t_ptr == '\t')
			    last_bl = e_com;
			*e_com++ = *t_ptr++;
E 3
I 3
		    if (t_ptr >= e_com) {
			while (*t_ptr == ' ' || *t_ptr == '\t')
			    t_ptr++;
			while (*t_ptr != '\0') {	/* move unprinted part
							 * of comment down in
							 * buffer */
			    if (*t_ptr == ' ' || *t_ptr == '\t')
				last_bl = e_com;
			    *e_com++ = *t_ptr++;
			}
E 8
I 8
		*e_com++ = ' ';	/* add blanks for continuation */
		*e_com++ = ' ';
		*e_com++ = ' ';

		t_ptr = last_bl + 1;
		last_bl = 0;
		if (t_ptr >= e_com) {
		    while (*t_ptr == ' ' || *t_ptr == '\t')
			t_ptr++;
		    while (*t_ptr != '\0') {	/* move unprinted part of
						 * comment down in buffer */
			if (*t_ptr == ' ' || *t_ptr == '\t')
			    last_bl = e_com;
			*e_com++ = *t_ptr++;
E 8
E 3
		    }
D 3

E 3
D 8
		    *e_com = '\0';
D 3
		    now_col = count_spaces (com_col, s_com);
		/* recompute current position */
		}	       /* end of code for splitting a comment */
		break;	       /* end of default case */


	}		       /* end of switch */

    }			       /* end of while (1) */
}		   /* end of pr_comment */
E 3
I 3
		    now_col = count_spaces(ps.com_col, s_com);	/* recompute current
								 * position */
E 8
		}
D 8
		break;
E 8
I 8
		*e_com = '\0';
		now_col = count_spaces(ps.com_col, s_com);	/* recompute current
								 * position */
	    }
	    break;
E 8
	}
    }
}
E 3
E 1
