h50946
s 00004/00004/00322
d D 8.2 94/01/03 10:08:50 bostic 8 7
c rename fgetline -> fgetln
e
s 00005/00005/00321
d D 8.1 93/06/06 16:16:15 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00325
d D 5.6 92/08/30 12:07:09 bostic 6 5
c don't access entries multiple times; from Diomidis
e
s 00017/00009/00309
d D 5.5 92/08/28 15:30:04 bostic 5 4
c MUST copy data from the stdio buffer, change interface to mf_fgets
e
s 00006/00003/00312
d D 5.4 92/08/26 15:26:32 bostic 4 3
c use snprintf, not strlen, don't make the message so long
e
s 00000/00003/00315
d D 5.3 92/08/24 20:48:06 bostic 3 2
c we can't survive some of the compile errors, just die
e
s 00003/00006/00315
d D 5.2 92/08/24 12:02:39 bostic 2 1
c update from Diomidis; increase the length of the string buffer
e
s 00321/00000/00000
d D 5.1 92/08/23 18:26:05 bostic 1 0
c date and time created 92/08/23 18:26:05 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Diomidis Spinellis.
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Diomidis Spinellis of Imperial College, University of London.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 7
char copyright[] =
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
"%Z% Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 7
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "defs.h"
#include "extern.h"

/*
 * Linked list of units (strings and files) to be compiled
 */
struct s_compunit {
	struct s_compunit *next;
	enum e_cut {CU_FILE, CU_STRING} type;
	char *s;			/* Pointer to string or fname */
};

/*
 * Linked list pointer to compilation units and pointer to current
 * next pointer.
 */
static struct s_compunit *script, **cu_nextp = &script;

/*
 * Linked list of files to be processed
 */
struct s_flist {
	char *fname;
	struct s_flist *next;
};

/*
 * Linked list pointer to files and pointer to current
 * next pointer.
 */
static struct s_flist *files, **fl_nextp = &files;

D 3
int compile_errors;		/* Compile error count. */
E 3
int aflag, eflag, nflag;

/*
 * Current file and line number; line numbers restart across compilation
 * units, but span across input files.
 */
char *fname;			/* File name. */
u_long linenum;
int lastline;			/* TRUE on the last line of the last file */

static void add_compunit __P((enum e_cut, char *));
static void add_file __P((char *));

int
main(argc, argv)
	int argc;
	char *argv[];
{
	int c, fflag;

	fflag = 0;
	while ((c = getopt(argc, argv, "ae:f:n")) != EOF)
		switch (c) {
		case 'a':
			aflag = 1;
			break;
		case 'e':
			eflag = 1;
			add_compunit(CU_STRING, optarg);
			break;
		case 'f':
			fflag = 1;
			add_compunit(CU_FILE, optarg);
			break;
		case 'n':
			nflag = 1;
			break;
		default:
		case '?':
			(void)fprintf(stderr,
"usage:\tsed script [-an] [file ...]\n\tsed [-an] [-e script] ... [-f scipt_file] ... [file ...]\n");
			exit(1);
		}
	argc -= optind;
	argv += optind;

	/* First usage case; script is the first arg */
	if (!eflag && !fflag && *argv) {
		add_compunit(CU_STRING, *argv);
		argv++;
	}

	compile();
D 3
	if (compile_errors)
		exit(1);
E 3

	/* Continue with first and start second usage */
	if (*argv)
		for (; *argv; argv++)
			add_file(*argv);
	else
		add_file(NULL);
	process();
D 6
	cfclose(prog);
E 6
I 6
	cfclose(prog, NULL);
E 6
	if (fclose(stdout))
		err(FATAL, "stdout: %s", strerror(errno));
	exit (0);
}

/*
 * Like fgets, but go through the chain of compilation units chaining them
 * together.  Empty strings and files are ignored.
 */
char *
cu_fgets(buf, n)
	char *buf;
	int n;
{
	static enum {ST_EOF, ST_FILE, ST_STRING} state = ST_EOF;
	static FILE *f;		/* Current open file */
	static char *s;		/* Current pointer inside string */
D 2
	static char string_ident[20];
E 2
I 2
D 4
	static char string_ident[60];
E 4
I 4
	static char string_ident[30];
E 4
E 2
	char *p;

again:
	switch (state) {
	case ST_EOF:
		if (script == NULL)
			return (NULL);
		linenum = 0;
		switch (script->type) {
		case CU_FILE:
			if ((f = fopen(script->s, "r")) == NULL)
				err(FATAL,
				    "%s: %s", script->s, strerror(errno));
			fname = script->s;
			state = ST_FILE;
			goto again;
		case CU_STRING:
D 2
			/* Have better handling here */
			(void)strncpy(string_ident,
			    script->s, sizeof(string_ident));
			(void)strcpy(string_ident + sizeof(string_ident) - 5,
			    "...");
E 2
I 2
D 4
			(void)sprintf(string_ident, "\"%.50s%s\"", script->s,
			    strlen(script->s) > 50 ? "..." : "");
E 4
I 4
			if ((snprintf(string_ident,
			    sizeof(string_ident), "\"%s\"", script->s)) >=
			    sizeof(string_ident) - 1)
				(void)strcpy(string_ident +
				    sizeof(string_ident) - 6, " ...\"");
E 4
E 2
			fname = string_ident;
			s = script->s;
			state = ST_STRING;
			goto again;
		}
	case ST_FILE:
		if ((p = fgets(buf, n, f)) != NULL) {
			linenum++;
			if (linenum == 1 && buf[0] == '#' && buf[1] == 'n')
				nflag = 1;
			return (p);
		}
		script = script->next;
		(void)fclose(f);
		state = ST_EOF;
		goto again;
	case ST_STRING:
		if (linenum == 0 && s[0] == '#' && s[1] == 'n')
			nflag = 1;
		p = buf;
		for (;;) {
			if (n-- <= 1) {
				*p = '\0';
				linenum++;
				return (buf);
			}
			switch (*s) {
			case '\0':
				state = ST_EOF;
				if (s == script->s) {
					script = script->next;
					goto again;
				} else {
					script = script->next;
					*p = '\0';
					linenum++;
					return (buf);
				}
			case '\n':
				*p++ = '\n';
				*p = '\0';
				s++;
				linenum++;
				return (buf);
			default:
				*p++ = *s++;
			}
		}
	}
	/* NOTREACHED */
}

/*
 * Like fgets, but go through the list of files chaining them together.
 * Set len to the length of the line.
 */
D 5
char *
mf_fgets(lenp)
	size_t *lenp;
E 5
I 5
int
mf_fgets(sp, spflag)
	SPACE *sp;
	enum e_spflag spflag;
E 5
{
	static FILE *f;		/* Current open file */
I 5
	size_t len;
E 5
	char c, *p;

	if (f == NULL)
		/* Advance to first non-empty file */
		for (;;) {
			if (files == NULL) {
				lastline = 1;
D 5
				return (NULL);
E 5
I 5
				return (0);
E 5
			}
			if (files->fname == NULL) {
				f = stdin;
				fname = "stdin";
			} else {
				fname = files->fname;
				if ((f = fopen(fname, "r")) == NULL)
					err(FATAL, "%s: %s",
					    fname, strerror(errno));
			}
			if ((c = getc(f)) != EOF) {
				(void)ungetc(c, f);
				break;
			}
			(void)fclose(f);
			files = files->next;
		}

	if (lastline) {
D 5
		*lenp = 0;
		return (NULL);
E 5
I 5
		sp->len = 0;
		return (0);
E 5
	}

D 5
	p = fgetline(f, lenp);
E 5
I 5
	/*
D 8
	 * Use fgetline so that we can handle essentially infinite input
	 * data.  Can't use the pointer into the stdio buffer as the process
	 * space because the ungetc() can cause it to move.
E 8
I 8
	 * Use fgetln so that we can handle essentially infinite input data.
	 * Can't use the pointer into the stdio buffer as the process space
	 * because the ungetc() can cause it to move.
E 8
	 */
D 8
	p = fgetline(f, &len);
E 8
I 8
	p = fgetln(f, &len);
E 8
E 5
	if (ferror(f))
		err(FATAL, "%s: %s", fname, strerror(errno ? errno : EIO));
I 5
	cspace(sp, p, len, spflag);
E 5

	linenum++;
	/* Advance to next non-empty file */
	while ((c = getc(f)) == EOF) {
		(void)fclose(f);
		files = files->next;
		if (files == NULL) {
			lastline = 1;
D 5
			return (p);
E 5
I 5
			return (1);
E 5
		}
		if (files->fname == NULL) {
			f = stdin;
			fname = "stdin";
		} else {
			fname = files->fname;
			if ((f = fopen(fname, "r")) == NULL)
				err(FATAL, "%s: %s", fname, strerror(errno));
		}
	}
	(void)ungetc(c, f);
D 5
	return (p);
E 5
I 5
	return (1);
E 5
}

/*
 * Add a compilation unit to the linked list
 */
static void
add_compunit(type, s)
	enum e_cut type;
	char *s;
{
	struct s_compunit *cu;

	cu = xmalloc(sizeof(struct s_compunit));
	cu->type = type;
	cu->s = s;
	cu->next = NULL;
	*cu_nextp = cu;
	cu_nextp = &cu->next;
}

/*
 * Add a file to the linked list
 */
static void
add_file(s)
	char *s;
{
	struct s_flist *fp;

	fp = xmalloc(sizeof(struct s_flist));
	fp->next = NULL;
	*fl_nextp = fp;
	fp->fname = s;
	fl_nextp = &fp->next;
}
E 1
