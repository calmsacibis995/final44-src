h04507
s 00002/00002/00282
d D 8.1 93/06/06 14:52:04 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00284
d D 5.11 91/02/26 13:54:54 bostic 13 12
c ANSI fixes
e
s 00001/00012/00285
d D 5.10 90/06/01 16:07:24 bostic 12 11
c new copyright notice
e
s 00031/00007/00266
d D 5.9 90/03/05 11:36:38 bostic 11 10
c get rid of Reiser style cpp concatenation
e
s 00009/00004/00264
d D 5.8 89/05/15 17:07:54 bostic 10 9
c new version from James Gosling including various bug fixes
e
s 00194/00158/00074
d D 5.7 88/09/15 12:19:05 bostic 9 8
c new version from James Gosling <jag@Sun.COM>
e
s 00011/00006/00221
d D 5.6 88/06/29 19:40:39 bostic 8 7
c install approved copyright notice
e
s 00011/00012/00216
d D 5.5 88/03/22 17:31:33 bostic 7 6
c add Berkeley and University of Illinois specific copyright
e
s 00002/00000/00226
d D 5.4 85/09/10 14:41:56 mckusick 6 5
c further updates from Chris Torek
e
s 00000/00000/00226
d D 5.3 85/09/08 15:41:09 mckusick 5 4
c update on Sun stuff by Chris Torek
e
s 00156/00092/00070
d D 5.2 85/08/28 13:47:06 mckusick 4 3
c kernel normal form (from sun!shannon)
e
s 00007/00001/00155
d D 5.1 85/06/04 13:38:53 dist 3 2
c Add copyright
e
s 00001/00001/00155
d D 4.2 83/08/11 22:38:22 sam 2 1
c standardize sccs keyword lines
e
s 00156/00000/00000
d D 4.1 82/10/21 23:58:19 mckusick 1 0
c date and time created 82/10/21 23:58:19 by mckusick
e
u
U
t
T
I 1
D 2
/*	%W%	(Berkeley)	%G%	*/
E 2
I 2
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*
D 9
 * Copyright (c) 1980 Regents of the University of California.
E 9
I 9
 * Copyright (c) 1985 Sun Microsystems, Inc.
D 14
 * Copyright (c) 1980 The Regents of the University of California.
E 9
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * Copyright (c) 1976 Board of Trustees of the University of Illinois.
E 14
I 14
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 * All rights reserved.
E 7
 *
I 7
D 12
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 8
 *
E 7
 *	%W% (Berkeley) %G%
 */
E 3
E 2

D 4
/*
E 4
I 4
D 7
/*-
E 4

			  Copyright (C) 1976
				by the
			  Board of Trustees
				of the
			University of Illinois

			 All rights reserved

E 7
I 7
D 9
/*
E 7
FILE NAME:
	indent_globs.h

PURPOSE:
	This include file contains the declarations for all global variables
	used in indent.

GLOBALS:
	The names of all of the variables will not be repeated here.  The 
	declarations start on the next page.

FUNCTIONS:
	None
D 4
*/
#define bufsize 600/* size of internal buffers */
#define inp_bufs 512
		   /* size of input buffer */
#define sc_size 5000
		   /* size of save_com buffer */
#define label_offset 2
		   /* number of levels a label is placed to left of code 
		   */
E 4
I 4
*/
E 4

E 9
D 4
#define d_ljust 0  /* default for ljust_decl */
#define d_max_col 75
		   /* default for max_col */
#define d_com_ind 33
		   /* default com_ind */
#define d_ind_size 4
		   /* default ind_size */
#define d_verbose 0/* default verbose */
#define d_unindent 1
		   /* default value for unindent_displace */
#define d_leave_comma 0
		   /* default value for leave_comma */
#define d_btype_2 1/* default value for btype_2 */
E 4
I 4
D 13
#include <stdio.h>
E 4

E 13
I 4
#define BACKSLASH '\\'
D 9
#define bufsize 600	   /* size of internal buffers */
#define inp_bufs 600	   /* size of input buffer */
#define sc_size 5000	   /* size of save_com buffer */
#define label_offset 2	   /* number of levels a label is placed to left of code 
		   */
E 9
I 9
#define bufsize 200		/* size of internal buffers */
D 10
#define inp_bufs 600		/* size of input buffer */
E 10
#define sc_size 5000		/* size of save_com buffer */
#define label_offset 2		/* number of levels a label is placed to left
				 * of code */
E 9

E 4
D 9
#define tabsize 8  /* the size of a tab */
D 4
#define tabmask 0177770
		   /* mask used when figuring length of lines with tabs */
E 4
I 4
#define tabmask 0177770	   /* mask used when figuring length of lines with tabs */
E 9
I 9
#define tabsize 8		/* the size of a tab */
#define tabmask 0177770		/* mask used when figuring length of lines
				 * with tabs */
E 9
E 4


#define false 0
#define true  1


D 4
int     input;     /* the fid for the input file */
int     output;    /* the fid for the output file */
E 4
I 4
D 9
FILE   *input;     /* the fid for the input file */
FILE   *output;    /* the output file */
E 9
I 9
FILE       *input;		/* the fid for the input file */
FILE       *output;		/* the output file */
E 9
E 4

D 4
char    labbuf[bufsize];
		   /* buffer for label */
E 4
I 4
D 9
char    labbuf[bufsize];	/* buffer for label */
E 4
char   *s_lab;     /* start ... */
char   *e_lab;     /* .. and end of stored label */
E 9
I 9
D 11
#define check_size(name) \
	if (e_/**/name >= l_/**/name) { \
	    register nsize = l_/**/name-s_/**/name+400; \
	    name/**/buf = (char *) realloc(name/**/buf, nsize); \
	    e_/**/name = name/**/buf + (e_/**/name-s_/**/name) + 1; \
	    l_/**/name = name/**/buf + nsize - 5; \
	    s_/**/name = name/**/buf + 1; \
E 11
I 11
#define CHECK_SIZE_CODE \
	if (e_code >= l_code) { \
	    register nsize = l_code-s_code+400; \
	    codebuf = (char *) realloc(codebuf, nsize); \
	    e_code = codebuf + (e_code-s_code) + 1; \
	    l_code = codebuf + nsize - 5; \
	    s_code = codebuf + 1; \
	}
#define CHECK_SIZE_COM \
	if (e_com >= l_com) { \
	    register nsize = l_com-s_com+400; \
	    combuf = (char *) realloc(combuf, nsize); \
	    e_com = combuf + (e_com-s_com) + 1; \
	    l_com = combuf + nsize - 5; \
	    s_com = combuf + 1; \
	}
#define CHECK_SIZE_LAB \
	if (e_lab >= l_lab) { \
	    register nsize = l_lab-s_lab+400; \
	    labbuf = (char *) realloc(labbuf, nsize); \
	    e_lab = labbuf + (e_lab-s_lab) + 1; \
	    l_lab = labbuf + nsize - 5; \
	    s_lab = labbuf + 1; \
	}
#define CHECK_SIZE_TOKEN \
	if (e_token >= l_token) { \
	    register nsize = l_token-s_token+400; \
	    tokenbuf = (char *) realloc(tokenbuf, nsize); \
	    e_token = tokenbuf + (e_token-s_token) + 1; \
	    l_token = tokenbuf + nsize - 5; \
	    s_token = tokenbuf + 1; \
E 11
	}
E 9

D 4
char    codebuf[bufsize];
		   /* buffer for code section */
E 4
I 4
D 9
char    codebuf[bufsize];	/* buffer for code section */
E 4
char   *s_code;    /* start ... */
char   *e_code;    /* .. and end of stored code */
E 9
I 9
char       *labbuf;		/* buffer for label */
char       *s_lab;		/* start ... */
char       *e_lab;		/* .. and end of stored label */
char       *l_lab;		/* limit of label buffer */
E 9

D 4
char    combuf[bufsize];
		   /* buffer for comments */
E 4
I 4
D 9
char    combuf[bufsize];	/* buffer for comments */
E 4
char   *s_com;     /* start ... */
char   *e_com;     /* ... and end of stored comments */
E 9
I 9
char       *codebuf;		/* buffer for code section */
char       *s_code;		/* start ... */
char       *e_code;		/* .. and end of stored code */
char       *l_code;		/* limit of code section */
E 9

D 4
char    in_buffer[inp_bufs];
		   /* input buffer */
E 4
I 4
D 9
char    in_buffer[inp_bufs];	/* input buffer */
E 4
char   *buf_ptr;   /* ptr to next character to be taken from in_buffer */
char   *buf_end;   /* ptr to first after last char in in_buffer */
E 9
I 9
char       *combuf;		/* buffer for comments */
char       *s_com;		/* start ... */
char       *e_com;		/* ... and end of stored comments */
char       *l_com;		/* limit of comment buffer */
E 9

D 4
char    save_com[sc_size];
		   /* input text is saved here when looking for the brace
E 4
I 4
D 9
char    save_com[sc_size];	/* input text is saved here when looking for the brace
E 4
		      after an if, while, etc */
char   *sc_end;    /* pointer into save_com buffer */
E 9
I 9
D 10
char        in_buffer[inp_bufs];/* input buffer */
E 10
I 10
#define token s_token
char       *tokenbuf;		/* the last token scanned */
char	   *s_token;
char       *e_token;
char	   *l_token;

char       *in_buffer;		/* input buffer */
char	   *in_buffer_limit;	/* the end of the input buffer */
E 10
char       *buf_ptr;		/* ptr to next character to be taken from
				 * in_buffer */
char       *buf_end;		/* ptr to first after last char in in_buffer */
E 9

D 9
char   *bp_save;   /* saved value of buf_ptr when taking input from
		      save_com */
char   *be_save;   /* similarly saved value of buf_end */
E 9
I 9
char        save_com[sc_size];	/* input text is saved here when looking for
				 * the brace after an if, while, etc */
char       *sc_end;		/* pointer into save_com buffer */
E 9

D 4
char    token[bufsize];
		   /* the last token scanned */
E 4
I 4
D 9
char    token[bufsize];	/* the last token scanned */
E 9
I 9
char       *bp_save;		/* saved value of buf_ptr when taking input
				 * from save_com */
char       *be_save;		/* similarly saved value of buf_end */
E 9
E 4

I 9
D 10
char        token[bufsize];	/* the last token scanned */
E 10
E 9

D 10

E 10
D 4

int     bl_line;   /* set to 1 by dump_line if the line is blank */
int     break_comma;
		   /* when true and not in parens, break after a comma */
E 4
I 4
D 9
int	blanklines_after_declarations;
int	blanklines_before_blockcomments;
int	blanklines_after_procs;
int	swallow_optional_blanklines;
int	n_real_blanklines;
int	prefix_blankline_requested;
int	postfix_blankline_requested;
int     break_comma;	/* when true and not in parens, break after a comma */
E 4
int     btype_2;   /* when true, brace should be on same line as if,
		      while, etc */
D 4
int     case_ind;  /* indentation level to be used for a "case n:" */
E 4
I 4
float   case_ind;  /* indentation level to be used for a "case n:" */
E 4
int     code_lines;/* count of lines with code */
D 4
int     col_1;     /* set to true if the last token started in column 1 */
int     com_col;   /* this is the column in which the current coment
		      should start */
int     com_ind;   /* the column in which comments to the right of code
		      should start */
int     com_lines; /* the number of lines with comments, set by dump_line 
		   */
int     dec_nest;  /* current nesting level for structure or init */
int     decl_com_ind;
		   /* the column in which comments after declarations
		      should be put */
int     decl_on_line;
		   /* set to true if this line of code has part of a
		      declaration on it */
E 4
int     had_eof;   /* set to true when input is exhausted */
D 4
int     i_l_follow;/* the level to which ind_level should be set after the
		      current line is printed */
int     in_decl;   /* set to true when we are in a declaration stmt.  The
		      processing of braces is then slightly different */
int     in_stmt;   /* set to 1 while in a stmt */
int     ind_level; /* the current indentation level */
int     ind_size;  /* the size of one indentation level */
int     ind_stmt;  /* set to 1 if next line should have an extra
		      indentation level because we are in the middle of a
		      stmt */
int     last_u_d;  /* set to true after scanning a token which forces a
		      following operator to be unary */
int     leave_comma;
		   /* if true, never break declarations after commas */
E 4
int     line_no;   /* the current line number. */
D 4
int     ljust_decl;/* true if declarations should be left justified */
E 4
int     max_col;   /* the maximum allowable line length */
I 6
int     pointer_as_binop;	/* when true, "->" is treated as a binary
				   operator (giving, e.g., "p -> f") */
E 6
D 4
int     out_coms;  /* the number of comments processed, set by pr_comment 
		   */
int     out_lines; /* the number of lines written, set by dump_line */
int     p_l_follow;/* used to remember how to indent following statement 
		   */
int     paren_level;
		   /* parenthesization level. used to indent within stmts 
		   */
int     pcase;     /* set to 1 if the current line label is a case.  It is
		      printed differently from  a regular label */
int     search_brace;
		   /* set to true by parse when it is necessary to buffer
		      up all info up to the start of a stmt after an if,
		      while, etc */
int     unindent_displace;
		   /* comments not to the right of code will be placed
		      this many indentation levels to the left of code */
int     use_ff;    /* set to one if the current line should be terminated
		      with a form feed */
E 4
int     verbose;   /* when true, non-essential error messages are printed 
		   */
I 4
int	cuddle_else;		/* true if else should cuddle up to '}' */
int	star_comment_cont;	/* true iff comment continuation lines should
				   have stars at the beginning of each line.
				   */
int     comment_delimiter_on_blankline;
int     troff;			/* true iff were generating troff input */
int	procnames_start_line;	/* if true, the names of procedures being
				   defined get placed in column 1 (ie. a
				   newline is placed between the type of the
				   procedure and its name) */
int	proc_calls_space;	/* If true, procedure calls look like:
				   foo(bar) rather than foo (bar) */
int	format_col1_comments;	/* If comments which start in column 1 are to
				   be magically reformatted (just like comments that
				   begin in later columns) */
int	inhibit_formatting;	/* true if INDENT OFF is in effect */
int	suppress_blanklines;	/* set iff following blanklines should be
				   suppressed */
int	continuation_indent;	/* set to the indentation between the edge of
				   code and continuation lines */
int	lineup_to_parens;	/* if true, continued code within parens will
				   be lined up to the open paren */
int	block_comment_max_col;
E 9
I 9
int         pointer_as_binop;
int         blanklines_after_declarations;
int         blanklines_before_blockcomments;
int         blanklines_after_procs;
int         blanklines_around_conditional_compilation;
int         swallow_optional_blanklines;
int         n_real_blanklines;
int         prefix_blankline_requested;
int         postfix_blankline_requested;
int         break_comma;	/* when true and not in parens, break after a
				 * comma */
int         btype_2;		/* when true, brace should be on same line as
				 * if, while, etc */
float       case_ind;		/* indentation level to be used for a "case
				 * n:" */
int         code_lines;		/* count of lines with code */
int         had_eof;		/* set to true when input is exhausted */
int         line_no;		/* the current line number. */
int         max_col;		/* the maximum allowable line length */
int         verbose;		/* when true, non-essential error messages are
				 * printed */
int         cuddle_else;	/* true if else should cuddle up to '}' */
int         star_comment_cont;	/* true iff comment continuation lines should
				 * have stars at the beginning of each line. */
int         comment_delimiter_on_blankline;
int         troff;		/* true iff were generating troff input */
int         procnames_start_line;	/* if true, the names of procedures
					 * being defined get placed in column
					 * 1 (ie. a newline is placed between
					 * the type of the procedure and its
					 * name) */
int         proc_calls_space;	/* If true, procedure calls look like:
				 * foo(bar) rather than foo (bar) */
int         format_col1_comments;	/* If comments which start in column 1
					 * are to be magically reformatted
					 * (just like comments that begin in
					 * later columns) */
int         inhibit_formatting;	/* true if INDENT OFF is in effect */
int         suppress_blanklines;/* set iff following blanklines should be
				 * suppressed */
int         continuation_indent;/* set to the indentation between the edge of
				 * code and continuation lines */
int         lineup_to_parens;	/* if true, continued code within parens will
				 * be lined up to the open paren */
int         Bill_Shannon;	/* true iff a blank should always be inserted
				 * after sizeof */
int         blanklines_after_declarations_at_proctop;	/* This is vaguely
							 * similar to
							 * blanklines_after_decla
							 * rations except that
							 * it only applies to
							 * the first set of
							 * declarations in a
							 * procedure (just after
							 * the first '{') and it
							 * causes a blank line
							 * to be generated even
							 * if there are no
							 * declarations */
int         block_comment_max_col;
int         extra_expression_indent;	/* True if continuation lines from the
					 * expression part of "if(e)",
					 * "while(e)", "for(e;e;e)" should be
					 * indented an extra tab stop so that
					 * they don't conflict with the code
					 * that follows */
E 9

I 9
/* -troff font state information */
E 9

I 9
struct fstate {
    char        font[4];
    char        size;
    int         allcaps:1;
};
char       *chfont();

struct fstate
            keywordf,		/* keyword font */
            stringf,		/* string font */
            boxcomf,		/* Box comment font */
            blkcomf,		/* Block comment font */
            scomf,		/* Same line comment font */
            bodyf;		/* major body font */


#define STACKSIZE 150

E 9
struct parser_state {
    int         last_token;
D 9
    int         p_stack[50];	/* this is the parsers stack */
    int         il[50];		/* this stack stores indentation levels */
    float       cstk[50];	/* used to store case stmt indentation
				 * levels */
E 9
I 9
    struct fstate cfont;	/* Current font */
    int         p_stack[STACKSIZE];	/* this is the parsers stack */
    int         il[STACKSIZE];	/* this stack stores indentation levels */
    float       cstk[STACKSIZE];/* used to store case stmt indentation levels */
E 9
    int         box_com;	/* set to true when we are in a "boxed"
D 9
				 * comment. In that case, the first
				 * non-blank char should be lined up with
				 * the / in /* */
E 9
I 9
				 * comment. In that case, the first non-blank
				 * char should be lined up with the / in /* */
E 9
    int         comment_delta,
                n_comment_delta;
    int         cast_mask;	/* indicates which close parens close off
				 * casts */
D 9
    int		sizeof_mask;	/* indicates which close parens close off
				   sizeof''s */
E 9
I 9
    int         sizeof_mask;	/* indicates which close parens close off
				 * sizeof''s */
E 9
    int         block_init;	/* true iff inside a block initialization */
D 9
    int         last_nl;	/* this is true if the last thing scanned
				 * was a newline */
E 9
I 9
    int         block_init_level;	/* The level of brace nesting in an
					 * initialization */
    int         last_nl;	/* this is true if the last thing scanned was
				 * a newline */
E 9
    int         in_or_st;	/* Will be true iff there has been a
D 9
				 * declarator (e.g. int or char) and no
				 * left paren since the last semicolon.
				 * When true, a '{' is starting a
				 * structure definition or an
				 * initialization list */
    int         bl_line;	/* set to 1 by dump_line if the line is
				 * blank */
    int         col_1;		/* set to true if the last token started
				 * in column 1 */
E 9
I 9
				 * declarator (e.g. int or char) and no left
				 * paren since the last semicolon. When true,
				 * a '{' is starting a structure definition or
				 * an initialization list */
    int         bl_line;	/* set to 1 by dump_line if the line is blank */
    int         col_1;		/* set to true if the last token started in
				 * column 1 */
E 9
    int         com_col;	/* this is the column in which the current
				 * coment should start */
D 9
    int         com_ind;	/* the column in which comments to the
				 * right of code should start */
    int         com_lines;	/* the number of lines with comments, set
				 * by dump_line */
    int         dec_nest;	/* current nesting level for structure or
				 * init */
E 9
I 9
    int         com_ind;	/* the column in which comments to the right
				 * of code should start */
    int         com_lines;	/* the number of lines with comments, set by
				 * dump_line */
    int         dec_nest;	/* current nesting level for structure or init */
E 9
    int         decl_com_ind;	/* the column in which comments after
				 * declarations should be put */
D 9
    int         decl_on_line;	/* set to true if this line of code has
				 * part of a declaration on it */
    int         i_l_follow;	/* the level to which ind_level should be
				 * set after the current line is printed */
    int         in_decl;	/* set to true when we are in a
				 * declaration stmt.  The processing of
				 * braces is then slightly different */
E 9
I 9
    int         decl_on_line;	/* set to true if this line of code has part
				 * of a declaration on it */
    int         i_l_follow;	/* the level to which ind_level should be set
				 * after the current line is printed */
    int         in_decl;	/* set to true when we are in a declaration
				 * stmt.  The processing of braces is then
				 * slightly different */
E 9
    int         in_stmt;	/* set to 1 while in a stmt */
    int         ind_level;	/* the current indentation level */
    int         ind_size;	/* the size of one indentation level */
D 9
    int         ind_stmt;	/* set to 1 if next line should have an
				 * extra indentation level because we are
				 * in the middle of a stmt */
    int         last_u_d;	/* set to true after scanning a token
				 * which forces a following operator to be
				 * unary */
E 9
I 9
    int         ind_stmt;	/* set to 1 if next line should have an extra
				 * indentation level because we are in the
				 * middle of a stmt */
    int         last_u_d;	/* set to true after scanning a token which
				 * forces a following operator to be unary */
E 9
    int         leave_comma;	/* if true, never break declarations after
				 * commas */
    int         ljust_decl;	/* true if declarations should be left
				 * justified */
D 9
    int         out_coms;	/* the number of comments processed, set
				 * by pr_comment */
E 9
I 9
    int         out_coms;	/* the number of comments processed, set by
				 * pr_comment */
E 9
    int         out_lines;	/* the number of lines written, set by
				 * dump_line */
D 9
    int         p_l_follow;	/* used to remember how to indent
				 * following statement */
E 9
I 9
    int         p_l_follow;	/* used to remember how to indent following
				 * statement */
E 9
    int         paren_level;	/* parenthesization level. used to indent
				 * within stmts */
    short       paren_indents[20];	/* column positions of each paren */
    int         pcase;		/* set to 1 if the current line label is a
D 9
				 * case.  It is printed differently from 
				 * a regular label */
    int         search_brace;	/* set to true by parse when it is
				 * necessary to buffer up all info up to
				 * the start of a stmt after an if, while,
				 * etc */
    int         unindent_displace;	/* comments not to the right of
					 * code will be placed this many
					 * indentation levels to the left
					 * of code */
    int         use_ff;		/* set to one if the current line should
				 * be terminated with a form feed */
    int         want_blank;	/* set to true when the following token
				 * should be prefixed by a blank. (Said
				 * prefixing is ignored in some cases.) */
    int         else_if;	/* True iff else if pairs should be
				 * handled specially */
    int         decl_indent;	/* column to indent declared identifiers
				 * to */
E 9
I 9
				 * case.  It is printed differently from a
				 * regular label */
    int         search_brace;	/* set to true by parse when it is necessary
				 * to buffer up all info up to the start of a
				 * stmt after an if, while, etc */
    int         unindent_displace;	/* comments not to the right of code
					 * will be placed this many
					 * indentation levels to the left of
					 * code */
    int         use_ff;		/* set to one if the current line should be
				 * terminated with a form feed */
    int         want_blank;	/* set to true when the following token should
				 * be prefixed by a blank. (Said prefixing is
				 * ignored in some cases.) */
    int         else_if;	/* True iff else if pairs should be handled
				 * specially */
    int         decl_indent;	/* column to indent declared identifiers to */
E 9
    int         its_a_keyword;
D 9
    int		sizeof_keyword;
E 9
I 9
    int         sizeof_keyword;
E 9
    int         dumped_decl_indent;
D 9
    float       case_indent;	/* The distance to indent case labels from
				 * the switch statement */
E 9
I 9
    float       case_indent;	/* The distance to indent case labels from the
				 * switch statement */
E 9
    int         in_parameter_declaration;
    int         indent_parameters;
    int         tos;		/* pointer to top of stack */
    char        procname[100];	/* The name of the current procedure */
D 9
    int		just_saw_decl;
E 9
I 9
    int         just_saw_decl;
E 9
}           ps;

D 9
int ifdef_level;
E 9
I 9
int         ifdef_level;
I 10
int	    rparen_count;
E 10
E 9
struct parser_state state_stack[5];
struct parser_state match_state[5];
E 4
E 1
