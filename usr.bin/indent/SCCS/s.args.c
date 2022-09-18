h56478
s 00002/00002/00272
d D 8.1 93/06/06 14:51:46 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00270
d D 5.10 91/02/26 13:54:45 bostic 10 9
c ANSI fixes
e
s 00001/00012/00272
d D 5.9 90/06/01 16:07:05 bostic 9 8
c new copyright notice
e
s 00009/00006/00275
d D 5.8 89/05/15 17:07:41 bostic 8 7
c new version from James Gosling including various bug fixes
e
s 00000/00001/00281
d D 5.7 89/03/05 14:26:04 bostic 7 6
c cleanup from David MacKenzie (mackenzi@thor.stolaf.edu)
e
s 00006/00007/00276
d D 5.6 88/09/15 13:08:25 bostic 6 5
c lint cleanups; non-portable char comparison
e
s 00154/00141/00129
d D 5.5 88/09/15 12:18:51 bostic 5 4
c new version from James Gosling <jag@Sun.COM>
e
s 00011/00006/00259
d D 5.4 88/06/29 19:40:29 bostic 4 3
c install approved copyright notice
e
s 00011/00003/00254
d D 5.3 88/03/22 17:31:25 bostic 3 2
c add Berkeley and University of Illinois specific copyright
e
s 00002/00000/00255
d D 5.2 85/09/10 14:42:10 mckusick 2 1
c further updates from Chris Torek
e
s 00255/00000/00000
d D 5.1 85/09/08 15:40:13 mckusick 1 0
c split out by Chris Torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1980 Regents of the University of California.
E 5
I 5
 * Copyright (c) 1985 Sun Microsystems, Inc.
D 11
 * Copyright (c) 1980 The Regents of the University of California.
E 5
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * Copyright (c) 1976 Board of Trustees of the University of Illinois.
E 11
I 11
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 * All rights reserved.
 *
D 9
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley and the University of
 * Illinois at Urbana.  The name of either University may not be used
 * to endorse or promote products derived from this software without
 * specific prior written permission. This software is provided
 * ``as is'' without express or implied warranty.
E 4
I 4
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 5
 * by the University of California, Berkeley and the University
 * of Illinois, Urbana.  The name of either
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
E 5
I 5
 * by the University of California, Berkeley, the University of Illinois,
 * Urbana, and Sun Microsystems, Inc.  The name of either University
 * or Sun Microsystems may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
E 5
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 9
I 9
 * %sccs.include.redist.c%
E 9
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

/*
D 5
 * Argument scanning and profile reading code.  Default parameters
 * are set here as well.
E 5
I 5
 * Argument scanning and profile reading code.  Default parameters are set
 * here as well.
E 5
 */

D 10
#include "indent_globs.h"
E 10
I 10
#include <stdio.h>
E 10
D 7
#include <sys/types.h>
E 7
#include <ctype.h>
D 10

D 5
char *getenv(), *index();
E 5
I 5
char       *getenv(), *index();
E 10
I 10
#include <stdlib.h>
#include <string.h>
#include "indent_globs.h"
E 10
E 5

/* profile types */
#define	PRO_SPECIAL	1	/* special case */
#define	PRO_BOOL	2	/* boolean */
#define	PRO_INT		3	/* integer */
I 5
#define PRO_FONT	4	/* troff font */
E 5

/* profile specials for booleans */
#define	ON		1	/* turn it on */
#define	OFF		0	/* turn it off */

/* profile specials for specials */
#define	IGN		1	/* ignore it */
#define	CLI		2	/* case label indent (float) */
#define	STDIN		3	/* use stdin */
#define	KEY		4	/* type (keyword) */

I 8
char *option_source = "?";

E 8
/*
D 5
 * N.B.: because of the way the table here is scanned, options
 * whose names are substrings of other options must occur later;
 * that is, with -lp vs -l, -lp must be first.  Also, while (most)
 * booleans occur more than once, the last default value is the
 * one actually assigned.
E 5
I 5
 * N.B.: because of the way the table here is scanned, options whose names are
 * substrings of other options must occur later; that is, with -lp vs -l, -lp
 * must be first.  Also, while (most) booleans occur more than once, the last
 * default value is the one actually assigned.
E 5
 */
struct pro {
D 5
    char *p_name;		/* name, eg -bl, -cli */
    int   p_type;		/* type (int, bool, special) */
    int   p_default;		/* the default value (if int) */
    int   p_special;		/* depends on type */
    int  *p_obj;		/* the associated variable */
} pro[] = {
    "npro",	PRO_SPECIAL,	0,	IGN,	0,
    "lc",	PRO_INT,	0,	0,	&block_comment_max_col,
    "lp",	PRO_BOOL,	true,	ON,	&lineup_to_parens,
    "nlp",	PRO_BOOL,	true,	OFF,	&lineup_to_parens,
    "l",	PRO_INT,	78,	0,	&max_col,
    "psl",	PRO_BOOL,	true,	ON,	&procnames_start_line,
    "npsl",	PRO_BOOL,	true,	OFF,	&procnames_start_line,
    "fc1",	PRO_BOOL,	true,	ON,	&format_col1_comments,
    "nfc1",	PRO_BOOL,	true,	OFF,	&format_col1_comments,
    "pcs",	PRO_BOOL,	false,	ON,	&proc_calls_space,
    "npcs",	PRO_BOOL,	false,	OFF,	&proc_calls_space,
    "ip",	PRO_BOOL,	true,	ON,	&ps.indent_parameters,
    "nip",	PRO_BOOL,	true,	OFF,	&ps.indent_parameters,
 /* see set_defaults for initialization of -cli */
    "cli",	PRO_SPECIAL,	0,	CLI,	0,
    "ci",	PRO_INT,	0,	0,	&continuation_indent,
    "cdb",	PRO_BOOL,	true,	ON,  &comment_delimiter_on_blankline,
    "ncdb",	PRO_BOOL,	true,	OFF, &comment_delimiter_on_blankline,
    "i",	PRO_INT,	8,	0,	&ps.ind_size,
    "cd",	PRO_INT,	0,	0,	&ps.decl_com_ind,
    "ce",	PRO_BOOL,	true,	ON,	&cuddle_else,
    "nce",	PRO_BOOL,	true,	OFF,	&cuddle_else,
    "c",	PRO_INT,	33,	0,	&ps.com_ind,
    "v",	PRO_BOOL,	false,	ON,	&verbose,
    "nv",	PRO_BOOL,	false,	OFF,	&verbose,
    "dj",	PRO_BOOL,	false,	ON,	&ps.ljust_decl,
    "ndj",	PRO_BOOL,	false,	OFF,	&ps.ljust_decl,
 /* don't ask *me* why -bc/-nbc is backwards.... */
    "bc",	PRO_BOOL,	true,	OFF,	&ps.leave_comma,
    "nbc",	PRO_BOOL,	true,	ON,	&ps.leave_comma,
    "di",	PRO_INT,	16,	0,	&ps.decl_indent,
    "d",	PRO_INT,	0,	0,	&ps.unindent_displace,
    "br",	PRO_BOOL,	true,	ON,	&btype_2,
    "bl",	PRO_BOOL,	true,	OFF,	&btype_2,
    "st",	PRO_SPECIAL,	0,	STDIN,	0,
    "ei",	PRO_BOOL,	true,	ON,	&ps.else_if,
    "nei",	PRO_BOOL,	true,	OFF,	&ps.else_if,
    "sc",	PRO_BOOL,	true,	ON,	&star_comment_cont,
    "nsc",	PRO_BOOL,	true,	OFF,	&star_comment_cont,
    "bap",	PRO_BOOL,	false,	ON,	&blanklines_after_procs,
    "nbap",	PRO_BOOL,	false,	OFF,	&blanklines_after_procs,
    "sob",	PRO_BOOL,	false,	ON,	&swallow_optional_blanklines,
    "nsob",	PRO_BOOL,	false,	OFF,	&swallow_optional_blanklines,
    "bad",	PRO_BOOL,	false,	ON,  &blanklines_after_declarations,
    "nbad",	PRO_BOOL,	false,	OFF, &blanklines_after_declarations,
    "bbb",	PRO_BOOL,	false,	ON,  &blanklines_before_blockcomments,
    "nbbb",	PRO_BOOL,	false,	OFF, &blanklines_before_blockcomments,
I 2
    "ps",	PRO_BOOL,	false,	ON,	&pointer_as_binop,
    "nps",	PRO_BOOL,	false,	OFF,	&pointer_as_binop,
E 2
    "troff",	PRO_BOOL,	false,	ON,	&troff,
    "T",	PRO_SPECIAL,	0,	KEY,	0,
 /* whew! */
    0,		0,		0,	0,	0
E 5
I 5
    char       *p_name;		/* name, eg -bl, -cli */
    int         p_type;		/* type (int, bool, special) */
    int         p_default;	/* the default value (if int) */
    int         p_special;	/* depends on type */
    int        *p_obj;		/* the associated variable */
}           pro[] = {

    "T", PRO_SPECIAL, 0, KEY, 0,
    "bacc", PRO_BOOL, false, ON, &blanklines_around_conditional_compilation,
    "badp", PRO_BOOL, false, ON, &blanklines_after_declarations_at_proctop,
    "bad", PRO_BOOL, false, ON, &blanklines_after_declarations,
    "bap", PRO_BOOL, false, ON, &blanklines_after_procs,
    "bbb", PRO_BOOL, false, ON, &blanklines_before_blockcomments,
    "bc", PRO_BOOL, true, OFF, &ps.leave_comma,
    "bl", PRO_BOOL, true, OFF, &btype_2,
    "br", PRO_BOOL, true, ON, &btype_2,
    "bs", PRO_BOOL, false, ON, &Bill_Shannon,
    "cdb", PRO_BOOL, true, ON, &comment_delimiter_on_blankline,
    "cd", PRO_INT, 0, 0, &ps.decl_com_ind,
    "ce", PRO_BOOL, true, ON, &cuddle_else,
    "ci", PRO_INT, 0, 0, &continuation_indent,
    "cli", PRO_SPECIAL, 0, CLI, 0,
    "c", PRO_INT, 33, 0, &ps.com_ind,
    "di", PRO_INT, 16, 0, &ps.decl_indent,
    "dj", PRO_BOOL, false, ON, &ps.ljust_decl,
    "d", PRO_INT, 0, 0, &ps.unindent_displace,
    "eei", PRO_BOOL, false, ON, &extra_expression_indent,
    "ei", PRO_BOOL, true, ON, &ps.else_if,
    "fbc", PRO_FONT, 0, 0, (int *) &blkcomf,
    "fbx", PRO_FONT, 0, 0, (int *) &boxcomf,
    "fb", PRO_FONT, 0, 0, (int *) &bodyf,
    "fc1", PRO_BOOL, true, ON, &format_col1_comments,
    "fc", PRO_FONT, 0, 0, (int *) &scomf,
    "fk", PRO_FONT, 0, 0, (int *) &keywordf,
    "fs", PRO_FONT, 0, 0, (int *) &stringf,
    "ip", PRO_BOOL, true, ON, &ps.indent_parameters,
    "i", PRO_INT, 8, 0, &ps.ind_size,
    "lc", PRO_INT, 0, 0, &block_comment_max_col,
    "lp", PRO_BOOL, true, ON, &lineup_to_parens,
    "l", PRO_INT, 78, 0, &max_col,
    "nbacc", PRO_BOOL, false, OFF, &blanklines_around_conditional_compilation,
    "nbadp", PRO_BOOL, false, OFF, &blanklines_after_declarations_at_proctop,
    "nbad", PRO_BOOL, false, OFF, &blanklines_after_declarations,
    "nbap", PRO_BOOL, false, OFF, &blanklines_after_procs,
    "nbbb", PRO_BOOL, false, OFF, &blanklines_before_blockcomments,
    "nbc", PRO_BOOL, true, ON, &ps.leave_comma,
    "nbs", PRO_BOOL, false, OFF, &Bill_Shannon,
    "ncdb", PRO_BOOL, true, OFF, &comment_delimiter_on_blankline,
    "nce", PRO_BOOL, true, OFF, &cuddle_else,
    "ndj", PRO_BOOL, false, OFF, &ps.ljust_decl,
    "neei", PRO_BOOL, false, OFF, &extra_expression_indent,
    "nei", PRO_BOOL, true, OFF, &ps.else_if,
    "nfc1", PRO_BOOL, true, OFF, &format_col1_comments,
    "nip", PRO_BOOL, true, OFF, &ps.indent_parameters,
    "nlp", PRO_BOOL, true, OFF, &lineup_to_parens,
    "npcs", PRO_BOOL, false, OFF, &proc_calls_space,
    "npro", PRO_SPECIAL, 0, IGN, 0,
    "npsl", PRO_BOOL, true, OFF, &procnames_start_line,
    "nps", PRO_BOOL, false, OFF, &pointer_as_binop,
    "nsc", PRO_BOOL, true, OFF, &star_comment_cont,
    "nsob", PRO_BOOL, false, OFF, &swallow_optional_blanklines,
    "nv", PRO_BOOL, false, OFF, &verbose,
    "pcs", PRO_BOOL, false, ON, &proc_calls_space,
    "psl", PRO_BOOL, true, ON, &procnames_start_line,
    "ps", PRO_BOOL, false, ON, &pointer_as_binop,
    "sc", PRO_BOOL, true, ON, &star_comment_cont,
    "sob", PRO_BOOL, false, ON, &swallow_optional_blanklines,
    "st", PRO_SPECIAL, 0, STDIN, 0,
    "troff", PRO_BOOL, false, ON, &troff,
    "v", PRO_BOOL, false, ON, &verbose,
    /* whew! */
    0, 0, 0, 0, 0
E 5
};

/*
D 5
 * set_profile reads $HOME/.indent.pro and ./.indent.pro and
 * handles arguments given in these files.
E 5
I 5
 * set_profile reads $HOME/.indent.pro and ./.indent.pro and handles arguments
 * given in these files.
E 5
 */
set_profile()
{
    register FILE *f;
D 5
    char fname[BUFSIZ];
E 5
I 5
    char        fname[BUFSIZ];
E 5
D 6
    static char pro[] = ".indent.pro";
E 6
I 6
    static char prof[] = ".indent.pro";
E 6

D 6
    sprintf(fname, "%s/%s", getenv("HOME"), pro);
E 6
I 6
    sprintf(fname, "%s/%s", getenv("HOME"), prof);
E 6
D 8
    if ((f = fopen(fname, "r")) != NULL) {
E 8
I 8
    if ((f = fopen(option_source = fname, "r")) != NULL) {
E 8
	scan_profile(f);
	(void) fclose(f);
    }
D 6
    if ((f = fopen(pro, "r")) != NULL) {
E 6
I 6
D 8
    if ((f = fopen(prof, "r")) != NULL) {
E 8
I 8
    if ((f = fopen(option_source = prof, "r")) != NULL) {
E 8
E 6
	scan_profile(f);
	(void) fclose(f);
    }
I 8
    option_source = "Command line";
E 8
}

scan_profile(f)
    register FILE *f;
{
I 6
    register int i;
E 6
D 5
    register char *p, *arg;
    char buf[BUFSIZ];
E 5
I 5
    register char *p;
    char        buf[BUFSIZ];
E 5

D 5
    while (fgets(buf, sizeof buf, f)) {
	if ((p = index(buf, '\n')) != NULL)
	    *p = 0;
	if (verbose)
	    printf("profile: %s\n", buf);
E 5
I 5
    while (1) {
E 5
D 6
	p = buf;
D 5
	for (;;) {
	    while (isspace(*p))
		p++;
	    if (*p == 0)
		break;
	    arg = p;
	    while (*p) {
		if (isspace(*p)) {
		    *p++ = 0;
		    break;
		}
		p++;
	    }
	    set_option(arg);
E 5
I 5
	while ((*p = getc(f)) != EOF && *p > ' ')
	    p++;
E 6
I 6
	for (p = buf; (i = getc(f)) != EOF && (*p = i) > ' '; ++p);
E 6
	if (p != buf) {
	    *p++ = 0;
	    if (verbose)
		printf("profile: %s\n", buf);
	    set_option(buf);
E 5
	}
I 5
D 6
	else if (*p == EOF)
E 6
I 6
	else if (i == EOF)
E 6
	    return;
E 5
    }
}

char       *param_start;

eqin(s1, s2)
    register char *s1;
    register char *s2;
{
    while (*s1) {
	if (*s1++ != *s2++)
	    return (false);
    }
    param_start = s2;
    return (true);
}

/*
 * Set the defaults.
 */
set_defaults()
{
    register struct pro *p;

    /*
D 5
     * Because ps.case_indent is a float, we can't initialize it
     * from the table:
E 5
I 5
     * Because ps.case_indent is a float, we can't initialize it from the
     * table:
E 5
     */
    ps.case_indent = 0.0;	/* -cli0.0 */
    for (p = pro; p->p_name; p++)
D 5
	if (p->p_type != PRO_SPECIAL)
E 5
I 5
	if (p->p_type != PRO_SPECIAL && p->p_type != PRO_FONT)
E 5
	    *p->p_obj = p->p_default;
}

set_option(arg)
    register char *arg;
{
    register struct pro *p;
    extern double atof();

    arg++;			/* ignore leading "-" */
    for (p = pro; p->p_name; p++)
	if (*p->p_name == *arg && eqin(p->p_name, arg))
	    goto found;
D 8
    fprintf(stderr, "indent: unknown parameter \"%s\"\n", arg - 1);
E 8
I 8
    fprintf(stderr, "indent: %s: unknown parameter \"%s\"\n", option_source, arg - 1);
E 8
    exit(1);
found:
    switch (p->p_type) {

D 5
	case PRO_SPECIAL:
	    switch (p->p_special) {
E 5
I 5
    case PRO_SPECIAL:
	switch (p->p_special) {
E 5

D 5
		case IGN:
		    break;
E 5
I 5
	case IGN:
	    break;
E 5

D 5
		case CLI:
		    if (*param_start == 0)
			goto need_param;
		    ps.case_indent = atof(param_start);
		    break;

		case STDIN:
		    if (input == 0)
			input = stdin;
		    if (output == 0)
			output = stdout;
		    break;

		case KEY:
		    if (*param_start == 0)
			goto need_param;
		    addkey(param_start, 4);
		    break;

		default:
		    fprintf(stderr, "\
indent: set_option: internal error: p_special %d\n", p->p_special);
		    exit(1);
	    }
E 5
I 5
	case CLI:
	    if (*param_start == 0)
		goto need_param;
	    ps.case_indent = atof(param_start);
E 5
	    break;

D 5
	case PRO_BOOL:
	    if (p->p_special == OFF)
		*p->p_obj = false;
	    else
		*p->p_obj = true;
E 5
I 5
	case STDIN:
	    if (input == 0)
		input = stdin;
	    if (output == 0)
		output = stdout;
E 5
	    break;

D 5
	case PRO_INT:
	    if (*param_start == 0) {
need_param:
		fprintf(stderr, "indent: ``%s'' requires a parameter\n",
			arg - 1);
		exit(1);
E 5
I 5
	case KEY:
	    if (*param_start == 0)
		goto need_param;
	    {
		register char *str = (char *) malloc(strlen(param_start) + 1);
		strcpy(str, param_start);
		addkey(str, 4);
E 5
	    }
D 5
	    *p->p_obj = atoi(param_start);
E 5
	    break;

	default:
D 5
	    fprintf(stderr, "indent: set_option: internal error: p_type %d\n",
		    p->p_type);
E 5
I 5
	    fprintf(stderr, "\
indent: set_option: internal error: p_special %d\n", p->p_special);
E 5
	    exit(1);
I 5
	}
	break;

    case PRO_BOOL:
	if (p->p_special == OFF)
	    *p->p_obj = false;
	else
	    *p->p_obj = true;
	break;

    case PRO_INT:
D 8
	if (*param_start == 0) {
E 8
I 8
	if (!isdigit(*param_start)) {
E 8
    need_param:
D 8
	    fprintf(stderr, "indent: ``%s'' requires a parameter\n",
		    arg - 1);
E 8
I 8
	    fprintf(stderr, "indent: %s: ``%s'' requires a parameter\n",
		    option_source, arg - 1);
E 8
	    exit(1);
	}
	*p->p_obj = atoi(param_start);
	break;

    case PRO_FONT:
	parsefont((struct fstate *) p->p_obj, param_start);
	break;

    default:
	fprintf(stderr, "indent: set_option: internal error: p_type %d\n",
		p->p_type);
	exit(1);
E 5
    }
}
E 1
