h27613
s 00013/00002/00384
d D 5.5 93/05/24 21:29:28 bostic 5 4
c revision 1.9 from Bob Corbett
e
s 00001/00000/00385
d D 5.4 91/02/26 14:58:27 bostic 4 3
c ANSI fix
e
s 00074/00026/00311
d D 5.3 91/01/20 19:58:21 corbett 3 2
c I added code to implement the -r option.  -rpc
e
s 00001/00011/00336
d D 5.2 90/06/01 16:13:34 bostic 2 1
c new copyright notice
e
s 00347/00000/00000
d D 5.1 89/12/25 14:24:33 bostic 1 0
c date and time created 89/12/25 14:24:33 by bostic
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Robert Paul Corbett.
 *
D 2
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <signal.h>
#include "defs.h"

char dflag;
char lflag;
I 3
char rflag;
E 3
char tflag;
char vflag;

I 5
char *symbol_prefix;
E 5
D 3
char *prefix = "y";
E 3
I 3
char *file_prefix = "y";
E 3
char *myname = "yacc";
char *temp_form = "yacc.XXXXXXX";

int lineno;
int outline;

char *action_file_name;
I 3
char *code_file_name;
E 3
char *defines_file_name;
char *input_file_name = "";
char *output_file_name;
char *text_file_name;
char *union_file_name;
char *verbose_file_name;

FILE *action_file;	/*  a temp file, used to save actions associated    */
			/*  with rules until the parser is written	    */
I 3
FILE *code_file;	/*  y.code.c (used when the -r option is specified) */
E 3
FILE *defines_file;	/*  y.tab.h					    */
FILE *input_file;	/*  the input file				    */
FILE *output_file;	/*  y.tab.c					    */
FILE *text_file;	/*  a temp file, used to save text until all	    */
			/*  symbols have been defined			    */
FILE *union_file;	/*  a temp file, used to save the union		    */
			/*  definition until all symbol have been	    */
			/*  defined					    */
FILE *verbose_file;	/*  y.output					    */

int nitems;
int nrules;
int nsyms;
int ntokens;
int nvars;

int   start_symbol;
char  **symbol_name;
short *symbol_value;
short *symbol_prec;
char  *symbol_assoc;

short *ritem;
short *rlhs;
short *rrhs;
short *rprec;
char  *rassoc;
short **derives;
char *nullable;

extern char *mktemp();
extern char *getenv();


done(k)
int k;
{
    if (action_file) { fclose(action_file); unlink(action_file_name); }
    if (text_file) { fclose(text_file); unlink(text_file_name); }
    if (union_file) { fclose(union_file); unlink(union_file_name); }
    exit(k);
}


I 4
void
E 4
D 5
onintr()
E 5
I 5
onintr(signo)
	int signo;
E 5
{
    done(1);
}


set_signals()
{
#ifdef SIGINT
    if (signal(SIGINT, SIG_IGN) != SIG_IGN)
	signal(SIGINT, onintr);
#endif
#ifdef SIGTERM
    if (signal(SIGTERM, SIG_IGN) != SIG_IGN)
	signal(SIGTERM, onintr);
#endif
#ifdef SIGHUP
    if (signal(SIGHUP, SIG_IGN) != SIG_IGN)
	signal(SIGHUP, onintr);
#endif
}


usage()
{
D 3
    fprintf(stderr, "usage: %s [-dltv] [-b prefix] filename\n", myname);
E 3
I 3
D 5
    fprintf(stderr, "usage: %s [-dlrtv] [-b file_prefix] filename\n", myname);
E 5
I 5
    fprintf(stderr, "usage: %s [-dlrtv] [-b file_prefix] [-p symbol_prefix] filename\n", myname);
E 5
E 3
    exit(1);
}


getargs(argc, argv)
int argc;
char *argv[];
{
    register int i;
    register char *s;

    if (argc > 0) myname = argv[0];
    for (i = 1; i < argc; ++i)
    {
	s = argv[i];
	if (*s != '-') break;
	switch (*++s)
	{
	case '\0':
	    input_file = stdin;
	    if (i + 1 < argc) usage();
	    return;

D 3
	case '_':
E 3
I 3
	case '-':
E 3
	    ++i;
	    goto no_more_options;

	case 'b':
D 3
	    if (*++s || ++i >= argc) usage();
	    prefix = argv[i];
E 3
I 3
	    if (*++s)
		 file_prefix = s;
	    else if (++i < argc)
		file_prefix = argv[i];
	    else
		usage();
E 3
	    continue;

	case 'd':
	    dflag = 1;
	    break;

	case 'l':
	    lflag = 1;
	    break;
I 5

	case 'p':
	    if (*++s)
		symbol_prefix = s;
	    else if (++i < argc)
		symbol_prefix = argv[i];
	    else
		usage();
	    continue;
E 5

I 3
	case 'r':
	    rflag = 1;
	    break;

E 3
	case 't':
	    tflag = 1;
	    break;

	case 'v':
	    vflag = 1;
	    break;

	default:
	    usage();
	}

	for (;;)
	{
	    switch (*++s)
	    {
	    case '\0':
		goto end_of_option;

	    case 'd':
		dflag = 1;
		break;

	    case 'l':
		lflag = 1;
		break;

I 3
	    case 'r':
		rflag = 1;
		break;

E 3
	    case 't':
		tflag = 1;
		break;

	    case 'v':
		vflag = 1;
		break;

	    default:
		usage();
	    }
	}
end_of_option:;
    }

no_more_options:;
    if (i + 1 != argc) usage();
    input_file_name = argv[i];
}


char *
allocate(n)
unsigned n;
{
    register char *p;

D 3
    p = calloc((unsigned) 1, n);
    if (!p) no_space();
E 3
I 3
    p = NULL;
    if (n)
    {
	p = CALLOC(1, n);
	if (!p) no_space();
    }
E 3
    return (p);
}


create_file_names()
{
    int i, len;
    char *tmpdir;

    tmpdir = getenv("TMPDIR");
    if (tmpdir == 0) tmpdir = "/tmp";

    len = strlen(tmpdir);
    i = len + 13;
    if (len && tmpdir[len-1] != '/')
	++i;

    action_file_name = MALLOC(i);
    if (action_file_name == 0) no_space();
    text_file_name = MALLOC(i);
    if (text_file_name == 0) no_space();
    union_file_name = MALLOC(i);
    if (union_file_name == 0) no_space();

    strcpy(action_file_name, tmpdir);
    strcpy(text_file_name, tmpdir);
    strcpy(union_file_name, tmpdir);

    if (len && tmpdir[len - 1] != '/')
    {
	action_file_name[len] = '/';
	text_file_name[len] = '/';
	union_file_name[len] = '/';
	++len;
    }

    strcpy(action_file_name + len, temp_form);
    strcpy(text_file_name + len, temp_form);
    strcpy(union_file_name + len, temp_form);

    action_file_name[len + 5] = 'a';
    text_file_name[len + 5] = 't';
    union_file_name[len + 5] = 'u';

    mktemp(action_file_name);
    mktemp(text_file_name);
    mktemp(union_file_name);

D 3
    len = strlen(prefix);
E 3
I 3
    len = strlen(file_prefix);

    output_file_name = MALLOC(len + 7);
    if (output_file_name == 0)
	no_space();
    strcpy(output_file_name, file_prefix);
    strcpy(output_file_name + len, OUTPUT_SUFFIX);

    if (rflag)
    {
	code_file_name = MALLOC(len + 8);
	if (code_file_name == 0)
	    no_space();
	strcpy(code_file_name, file_prefix);
	strcpy(code_file_name + len, CODE_SUFFIX);
    }
    else
	code_file_name = output_file_name;

E 3
    if (dflag)
    {
D 3
	/*  the number 7 below is the size of ".tab.h"; sizeof is not used  */
	/*  because of a C compiler that thinks sizeof(".tab.h") == 6	    */
E 3
	defines_file_name = MALLOC(len + 7);
D 3
	if (defines_file_name == 0) no_space();
	strcpy(defines_file_name, prefix);
E 3
I 3
	if (defines_file_name == 0)
	    no_space();
	strcpy(defines_file_name, file_prefix);
E 3
	strcpy(defines_file_name + len, DEFINES_SUFFIX);
    }

D 3
    output_file_name = MALLOC(len + 7);
    if (output_file_name == 0) no_space();
    strcpy(output_file_name, prefix);
    strcpy(output_file_name + len, OUTPUT_SUFFIX);

E 3
    if (vflag)
    {
	verbose_file_name = MALLOC(len + 8);
D 3
	if (verbose_file_name == 0) no_space();
	strcpy(verbose_file_name, prefix);
E 3
I 3
	if (verbose_file_name == 0)
	    no_space();
	strcpy(verbose_file_name, file_prefix);
E 3
	strcpy(verbose_file_name + len, VERBOSE_SUFFIX);
    }
}


open_files()
{
    create_file_names();

    if (input_file == 0)
    {
	input_file = fopen(input_file_name, "r");
D 3
	if (input_file == 0) open_error(input_file_name);
E 3
I 3
	if (input_file == 0)
	    open_error(input_file_name);
E 3
    }

    action_file = fopen(action_file_name, "w");
D 3
    if (action_file == 0) open_error(action_file_name);
E 3
I 3
    if (action_file == 0)
	open_error(action_file_name);
E 3

    text_file = fopen(text_file_name, "w");
D 3
    if (text_file == 0) open_error(text_file_name);
E 3
I 3
    if (text_file == 0)
	open_error(text_file_name);
E 3

    if (vflag)
    {
	verbose_file = fopen(verbose_file_name, "w");
D 3
	if (verbose_file == 0) open_error(verbose_file_name);
E 3
I 3
	if (verbose_file == 0)
	    open_error(verbose_file_name);
E 3
    }

    if (dflag)
    {
	defines_file = fopen(defines_file_name, "w");
D 3
	if (defines_file == 0) open_error(defines_file_name);
E 3
I 3
	if (defines_file == 0)
	    open_error(defines_file_name);
E 3
	union_file = fopen(union_file_name, "w");
D 3
	if (union_file ==  0) open_error(union_file_name);
E 3
I 3
	if (union_file ==  0)
	    open_error(union_file_name);
E 3
    }

    output_file = fopen(output_file_name, "w");
D 3
    if (output_file == 0) open_error(output_file_name);
E 3
I 3
    if (output_file == 0)
	open_error(output_file_name);

    if (rflag)
    {
	code_file = fopen(code_file_name, "w");
	if (code_file == 0)
	    open_error(code_file_name);
    }
    else
	code_file = output_file;
E 3
}


int
main(argc, argv)
int argc;
char *argv[];
{
    set_signals();
    getargs(argc, argv);
    open_files();
    reader();
    lr0();
    lalr();
    make_parser();
    verbose();
    output();
    done(0);
    /*NOTREACHED*/
}
E 1
