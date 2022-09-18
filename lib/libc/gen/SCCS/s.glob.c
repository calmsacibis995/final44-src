h09037
s 00001/00001/00819
d D 8.3 93/10/13 09:53:21 bostic 23 22
c don't automatically retain the pattern if GLOB_BRACE or GLOB_TILDE
c are set; don't retain the pattern if GLOB_NOMAGIC is set unless there aren't
c any magic characters
e
s 00000/00003/00820
d D 8.2 93/10/13 09:43:41 bostic 22 21
c glob0 shouldn't set pglob->gl_matchc to 0, it's done by glob, 
c and glob0 gets called recursively
e
s 00002/00002/00821
d D 8.1 93/06/04 12:03:38 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00821
d D 5.20 93/02/19 18:38:44 bostic 20 19
c lint
e
s 00322/00067/00502
d D 5.19 93/02/10 15:05:51 bostic 19 18
c add GLOB_BRACE, GLOB_TILDE, plus minor cleanups and prototyping
c from Christos Zoulas
e
s 00012/00009/00557
d D 5.18 92/12/04 19:44:07 bostic 18 17
c When glob() call errfunc, it doesn't convert extended char * (u_short *)
c to char *, so errfunc only printed first pathbuf letter.
c Minor cleanups.  Net posting from "Andrew A. Chernov, <ache@astral.msk.su>
e
s 00034/00014/00532
d D 5.17 92/12/02 00:50:06 mckusick 17 16
c add GLOB_ALTDIRFUNC to have glob use alternate directory access functions
e
s 00009/00004/00537
d D 5.16 92/10/01 13:09:13 bostic 16 15
c "touch foo; ls foo**" returned no match; from Christos
e
s 00001/00001/00540
d D 5.15 92/02/05 11:33:25 bostic 15 14
c fix globbing on symlinks without targets
e
s 00002/00001/00539
d D 5.14 92/02/04 15:32:41 bostic 14 13
c csh glob bug from Christos; example is:
c % echo .[^.]
c echo: No match.
c % echo .[^.]*
c .
e
s 00013/00003/00527
d D 5.13 91/07/15 14:39:20 bostic 13 12
c add GLOB_NOMAGIC
e
s 00012/00010/00518
d D 5.12 91/06/24 08:35:26 bostic 12 11
c from Christos; last fix not quite right
e
s 00001/00002/00527
d D 5.11 91/06/23 11:29:03 bostic 11 10
c from Christos; example is "echo 'foo*' *" results in "No match"
e
s 00149/00151/00380
d D 5.10 91/06/17 07:41:29 bostic 10 9
c The Prettiness Police + fixes from Christos
e
s 00098/00055/00433
d D 5.9 91/06/16 16:38:20 bostic 9 8
c Christos' changes to do quoting in ranges; glob(3) now requires that
c chars be shorts.  Add function prototypes
e
s 00113/00049/00375
d D 5.8 91/04/23 10:42:30 bostic 8 7
c 8-bit clean version from Christos Zoulas @ Cornell
e
s 00008/00007/00416
d D 5.7 91/04/19 16:32:21 bostic 7 6
c "echo ba?" didn't match symbolic links without targets
e
s 00002/00002/00421
d D 5.6 91/04/02 12:42:41 bostic 6 5
c globfree free'd the wrong pointer
e
s 00014/00004/00409
d D 5.5 91/03/19 19:58:28 bostic 5 4
c add gl_matchc, GLOB_MAGCHAR
e
s 00012/00005/00401
d D 5.4 91/02/23 19:49:49 donn 4 3
c Add include files to get prototype declarations, and fix bugs found.
e
s 00002/00002/00404
d D 5.3 90/06/23 16:37:06 bostic 3 2
c make the sort function type-correct
e
s 00001/00011/00405
d D 5.2 90/06/01 14:11:42 bostic 2 1
c new copyright notice
e
s 00416/00000/00000
d D 5.1 90/02/15 10:57:10 bostic 1 0
c date and time created 90/02/15 10:57:10 by bostic
e
u
U
t
T
I 1
/*
D 21
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
 * This code is derived from software contributed to Berkeley by
 * Guido van Rossum.
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

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

/*
D 10
 * Glob: the interface is a superset of the one defined in POSIX 1003.2,
 * draft 9.
E 10
I 10
 * glob(3) -- a superset of the one defined in POSIX 1003.2.
E 10
 *
 * The [!...] convention to negate a range is supported (SysV, Posix, ksh).
 *
 * Optional extra services, controlled by flags not defined by POSIX:
D 5
 *	GLOB_QUOTE: escaping convention: \ inhibits any special meaning
		the following character might have (except \ at end of
 *		string is kept);
E 5
I 5
 *
 * GLOB_QUOTE:
 *	Escaping convention: \ inhibits any special meaning the following
 *	character might have (except \ at end of string is retained).
 * GLOB_MAGCHAR:
D 8
 *	Set in gl_flags is pattern contained a globbing character.
E 8
I 8
 *	Set in gl_flags if pattern contained a globbing character.
I 13
 * GLOB_NOMAGIC:
 *	Same as GLOB_NOCHECK, but it will only append pattern if it did
 *	not contain any magic characters.  [Used in csh style globbing]
I 17
 * GLOB_ALTDIRFUNC:
 *	Use alternately specified directory access functions.
I 19
 * GLOB_TILDE:
 *	expand ~user/foo to the /home/dir/of/user/foo
 * GLOB_BRACE:
 *	expand {1,2}{a,b} to 1a 1b 2a 2b 
E 19
E 17
E 13
E 8
 * gl_matchc:
 *	Number of matches in the current invocation of glob.
E 5
 */

I 8
D 13
#include <sys/cdefs.h>
E 13
E 8
#include <sys/param.h>
#include <sys/stat.h>
D 19
#include <dirent.h>
#include <glob.h>
E 19
I 19

E 19
#include <ctype.h>
I 19
#include <dirent.h>
E 19
#include <errno.h>
D 19
#include <string.h>
E 19
I 19
#include <glob.h>
#include <pwd.h>
E 19
#include <stdio.h>
I 4
#include <stdlib.h>
I 19
#include <string.h>
#include <unistd.h>
E 19
E 4

D 4
char *malloc(), *realloc();

E 4
D 8
typedef int bool_t;
E 8
I 8
D 9
static int glob1(), glob2(), glob3(), globextend(), match();
E 8

E 9
I 4
D 8
static glob1();
static glob2();
static glob3();
static globextend();
static bool_t match();

E 8
E 4
#define	DOLLAR		'$'
#define	DOT		'.'
#define	EOS		'\0'
#define	LBRACKET	'['
#define	NOT		'!'
#define	QUESTION	'?'
#define	QUOTE		'\\'
#define	RANGE		'-'
#define	RBRACKET	']'
#define	SEP		'/'
#define	STAR		'*'
#define	TILDE		'~'
#define	UNDERSCORE	'_'
I 19
#define	LBRACE		'{'
#define	RBRACE		'}'
#define	SLASH		'/'
#define	COMMA		','
E 19

I 19
#ifndef DEBUG

E 19
I 8
D 9
#define	SHORT_STRINGS
#ifdef SHORT_STRINGS
typedef u_short shortchar_t;
#define	METABIT		0x8000
E 9
I 9
#define	M_QUOTE		0x8000
#define	M_PROTECT	0x4000
E 9
#define	M_MASK		0xffff
I 12
#define	M_ASCII		0x00ff
E 12
D 9
#else
typedef char shortchar_t;
E 8
#define	METABIT		0x80
I 8
#define	M_MASK		0xff
#endif
E 9

I 12
D 19
#define	CHAR(c)		((c)&M_ASCII)
E 12
E 8
D 9
#define	META(c)		((c)|METABIT)
E 9
I 9
#define	META(c)		((c)|M_QUOTE)
E 19
I 19
typedef u_short Char;

#else

#define	M_QUOTE		0x80
#define	M_PROTECT	0x40
#define	M_MASK		0xff
#define	M_ASCII		0x7f

typedef char Char;

#endif


#define	CHAR(c)		((Char)((c)&M_ASCII))
#define	META(c)		((Char)((c)|M_QUOTE))
E 19
E 9
#define	M_ALL		META('*')
#define	M_END		META(']')
#define	M_NOT		META('!')
#define	M_ONE		META('?')
#define	M_RNG		META('-')
#define	M_SET		META('[')
D 9
#define	ismeta(c)	(((c)&METABIT) != 0)
E 9
I 9
#define	ismeta(c)	(((c)&M_QUOTE) != 0)
E 9

D 8
static
E 8
I 8
D 9
#ifdef SHORT_STRINGS
E 9
I 9
D 10
typedef u_short shortchar_t;
E 10
I 10
D 19
typedef u_short Char;
E 19
E 10

D 10
static int glob1 __P((shortchar_t *, glob_t *));
static int glob2 __P((shortchar_t *, shortchar_t *, shortchar_t *, glob_t *));
static int glob3 __P((shortchar_t *,
	shortchar_t *, shortchar_t *, shortchar_t *, glob_t *));
static int globextend __P((shortchar_t *, glob_t *));
static int match __P((shortchar_t *, shortchar_t *, shortchar_t *));
static DIR *Opendir __P((shortchar_t *));
static int Lstat __P((shortchar_t *, struct stat *));
static int Stat __P((shortchar_t *, struct stat *));
static shortchar_t *Strchr __P((shortchar_t *, int));
E 10
I 10
static int	 compare __P((const void *, const void *));
D 19
static void	 g_Ctoc __P((Char *, char *));
E 19
I 19
static void	 g_Ctoc __P((const Char *, char *));
E 19
D 17
static int	 g_lstat __P((Char *, struct stat *));
static DIR	*g_opendir __P((Char *));
E 17
I 17
static int	 g_lstat __P((Char *, struct stat *, glob_t *));
static DIR	*g_opendir __P((Char *, glob_t *));
E 17
static Char	*g_strchr __P((Char *, int));
I 19
#ifdef notdef
static Char	*g_strcat __P((Char *, const Char *));
#endif
E 19
D 17
static int	 g_stat __P((Char *, struct stat *));
E 17
I 17
static int	 g_stat __P((Char *, struct stat *, glob_t *));
I 19
static int	 glob0 __P((const Char *, glob_t *));
E 19
E 17
static int	 glob1 __P((Char *, glob_t *));
static int	 glob2 __P((Char *, Char *, Char *, glob_t *));
static int	 glob3 __P((Char *, Char *, Char *, Char *, glob_t *));
D 19
static int	 globextend __P((Char *, glob_t *));
E 19
I 19
static int	 globextend __P((const Char *, glob_t *));
static const Char *	 globtilde __P((const Char *, Char *, glob_t *));
static int	 globexp1 __P((const Char *, glob_t *));
static int	 globexp2 __P((const Char *, const Char *, glob_t *, int *));
E 19
static int	 match __P((Char *, Char *, Char *));
E 10
#ifdef DEBUG
D 10
static void qprintf __P((shortchar_t *));
E 10
I 10
D 19
static void	 qprintf __P((Char *));
E 19
I 19
static void	 qprintf __P((const char *, Char *));
E 19
E 10
#endif

E 9
D 10
static DIR *
Opendir(str)
D 9
register shortchar_t *str;
E 9
I 9
	register shortchar_t *str;
E 9
{
	register char *dc;
	char buf[MAXPATHLEN];

	if (!*str)
		return(opendir("."));
	for (dc = buf; *dc++ = *str++;);
	return(opendir(buf));
}

static int
Lstat(fn, sb)
D 9
register shortchar_t *fn;
struct stat *sb;
E 9
I 9
	register shortchar_t *fn;
	struct stat *sb;
E 9
{
	register char *dc;
	char buf[MAXPATHLEN];

	for (dc = buf; *dc++ = *fn++;);
	return(lstat(buf, sb));
}

static int
Stat(fn, sb)
D 9
register shortchar_t *fn;
struct stat *sb;
E 9
I 9
	register shortchar_t *fn;
	struct stat *sb;
E 9
{
	register char *dc;
	char buf[MAXPATHLEN];

	for (dc = buf; *dc++ = *fn++;);
	return(stat(buf, sb));
}
D 9
#else
#define	Opendir	opendir
#define	Stat	stat
#define	Lstat	lstat
E 9
I 9

static shortchar_t *
Strchr(str, ch)
	shortchar_t *str;
	int ch;
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++);
	return (NULL);
}

#ifdef DEBUG
static void 
qprintf(s)
shortchar_t *s;
{
	shortchar_t *p;

	for (p = s; *p; p++)
		printf("%c", *p & 0xff);
	printf("\n");
	for (p = s; *p; p++)
		printf("%c", *p & M_PROTECT ? '"' : ' ');
	printf("\n");
	for (p = s; *p; p++)
		printf("%c", *p & M_META ? '_' : ' ');
	printf("\n");
}
E 9
#endif

static int
E 8
compare(p, q)
D 3
	char **p, **q;
E 3
I 3
	void **p, **q;
E 3
{
D 3
	return(strcmp(*p, *q));
E 3
I 3
	return(strcmp(*(char **)p, *(char **)q));
E 3
}

E 10
D 8

E 8
D 19
/*
 * The main glob() routine: compiles the pattern (optionally processing
 * quotes), calls glob1() to do the real pattern matching, and finally
 * sorts the list (unless unsorted operation is requested).  Returns 0
 * if things went well, nonzero if errors occurred.  It is not an error
 * to find no matches.
 */
E 19
I 19
int
E 19
glob(pattern, flags, errfunc, pglob)
D 4
	char *pattern;
	int flags, (*errfunc)();
E 4
I 4
	const char *pattern;
D 10
	int flags;
	int (*errfunc) __P((char *, int));
E 10
I 10
D 19
	int flags, (*errfunc) __P((char *, int));
E 19
I 19
	int flags, (*errfunc) __P((const char *, int));
E 19
E 10
E 4
	glob_t *pglob;
{
D 10
	int err, oldpathc;
D 4
	char *bufnext, *bufend, *compilebuf, *compilepat, *patnext;
E 4
I 4
D 8
	char *bufnext, *bufend, *compilebuf;
E 8
I 8
	shortchar_t *bufnext, *bufend, *compilebuf;
E 10
E 8
D 12
	const char *compilepat, *patnext;
E 12
I 12
D 19
	const u_char *compilepat, *patnext;
E 12
I 10
D 11
	int err, oldpathc;
E 11
I 11
	int c, err, oldpathc;
E 11
	Char *bufnext, *bufend, *compilebuf, *qpatnext, patbuf[MAXPATHLEN+1];
E 19
I 19
	const u_char *patnext;
	int c;
	Char *bufnext, *bufend, patbuf[MAXPATHLEN+1];
E 19
E 10
E 4
D 8
	char c, patbuf[MAXPATHLEN+1];
E 8
I 8
D 11
	char c;
E 11
D 9
	shortchar_t patbuf[MAXPATHLEN+1];
E 9
I 9
D 10
	shortchar_t patbuf[MAXPATHLEN+1], *qpatnext;
E 10
E 9
E 8

D 12
	patnext = pattern;
E 12
I 12
	patnext = (u_char *) pattern;
E 12
	if (!(flags & GLOB_APPEND)) {
		pglob->gl_pathc = 0;
		pglob->gl_pathv = NULL;
		if (!(flags & GLOB_DOOFFS))
			pglob->gl_offs = 0;
	}
D 5
	pglob->gl_flags = flags;
E 5
I 5
	pglob->gl_flags = flags & ~GLOB_MAGCHAR;
E 5
	pglob->gl_errfunc = errfunc;
D 19
	oldpathc = pglob->gl_pathc;
E 19
I 5
	pglob->gl_matchc = 0;
E 5

	bufnext = patbuf;
D 9
	bufend = bufnext+MAXPATHLEN;
E 9
I 9
	bufend = bufnext + MAXPATHLEN;
I 10
D 19
	compilebuf = bufnext;
	compilepat = patnext;
E 19
E 10
	if (flags & GLOB_QUOTE) {
D 10
		/* Protect the quoted characters */
E 10
I 10
		/* Protect the quoted characters. */
E 10
		while (bufnext < bufend && (c = *patnext++) != EOS) 
			if (c == QUOTE) {
				if ((c = *patnext++) == EOS) {
					c = QUOTE;
					--patnext;
				}
				*bufnext++ = c | M_PROTECT;
			}
			else
				*bufnext++ = c;
	}
	else 
	    while (bufnext < bufend && (c = *patnext++) != EOS) 
		    *bufnext++ = c;
	*bufnext = EOS;
E 9

I 9
D 19
	bufnext = patbuf;
	qpatnext = patbuf;
E 19
I 19
	if (flags & GLOB_BRACE)
	    return globexp1(patbuf, pglob);
	else
	    return glob0(patbuf, pglob);
}

/*
 * Expand recursively a glob {} pattern. When there is no more expansion
 * invoke the standard globbing routine to glob the rest of the magic
 * characters
 */
static int globexp1(pattern, pglob)
	const Char *pattern;
	glob_t *pglob;
{
	const Char* ptr = pattern;
	int rv;

	/* Protect a single {}, for find(1), like csh */
	if (pattern[0] == LBRACE && pattern[1] == RBRACE && pattern[2] == EOS)
		return glob0(pattern, pglob);

	while ((ptr = (const Char *) g_strchr((Char *) ptr, LBRACE)) != NULL)
		if (!globexp2(ptr, pattern, pglob, &rv))
			return rv;

	return glob0(pattern, pglob);
}


/*
 * Recursive brace globbing helper. Tries to expand a single brace.
 * If it succeeds then it invokes globexp1 with the new pattern.
 * If it fails then it tries to glob the rest of the pattern and returns.
 */
static int globexp2(ptr, pattern, pglob, rv)
	const Char *ptr, *pattern;
	glob_t *pglob;
	int *rv;
{
	int     i;
	Char   *lm, *ls;
	const Char *pe, *pm, *pl;
	Char    patbuf[MAXPATHLEN + 1];

	/* copy part up to the brace */
	for (lm = patbuf, pm = pattern; pm != ptr; *lm++ = *pm++)
		continue;
	ls = lm;

	/* Find the balanced brace */
	for (i = 0, pe = ++ptr; *pe; pe++)
		if (*pe == LBRACKET) {
			/* Ignore everything between [] */
			for (pm = pe++; *pe != RBRACKET && *pe != EOS; pe++)
				continue;
			if (*pe == EOS) {
				/* 
				 * We could not find a matching RBRACKET.
				 * Ignore and just look for RBRACE
				 */
				pe = pm;
			}
		}
		else if (*pe == LBRACE)
			i++;
		else if (*pe == RBRACE) {
			if (i == 0)
				break;
			i--;
		}

	/* Non matching braces; just glob the pattern */
	if (i != 0 || *pe == EOS) {
		*rv = glob0(patbuf, pglob);
		return 0;
	}

	for (i = 0, pl = pm = ptr; pm <= pe; pm++)
		switch (*pm) {
		case LBRACKET:
			/* Ignore everything between [] */
			for (pl = pm++; *pm != RBRACKET && *pm != EOS; pm++)
				continue;
			if (*pm == EOS) {
				/* 
				 * We could not find a matching RBRACKET.
				 * Ignore and just look for RBRACE
				 */
				pm = pl;
			}
			break;

		case LBRACE:
			i++;
			break;

		case RBRACE:
			if (i) {
			    i--;
			    break;
			}
			/* FALLTHROUGH */
		case COMMA:
			if (i && *pm == COMMA)
				break;
			else {
				/* Append the current string */
				for (lm = ls; (pl < pm); *lm++ = *pl++)
					continue;
				/* 
				 * Append the rest of the pattern after the
				 * closing brace
				 */
				for (pl = pe + 1; (*lm++ = *pl++) != EOS;)
					continue;

				/* Expand the current pattern */
#ifdef DEBUG
				qprintf("globexp2:", patbuf);
#endif
				*rv = globexp1(patbuf, pglob);

				/* move after the comma, to the next string */
				pl = pm + 1;
			}
			break;

		default:
			break;
		}
	*rv = 0;
	return 0;
}



/*
 * expand tilde from the passwd file.
 */
static const Char *
globtilde(pattern, patbuf, pglob)
	const Char *pattern;
	Char *patbuf;
	glob_t *pglob;
{
	struct passwd *pwd;
	char *h;
	const Char *p;
	Char *b;

	if (*pattern != TILDE || !(pglob->gl_flags & GLOB_TILDE))
		return pattern;

	/* Copy up to the end of the string or / */
	for (p = pattern + 1, h = (char *) patbuf; *p && *p != SLASH; 
	     *h++ = *p++)
		continue;

	*h = EOS;

	if (((char *) patbuf)[0] == EOS) {
		/* 
		 * handle a plain ~ or ~/ by expanding $HOME 
		 * first and then trying the password file
		 */
		if ((h = getenv("HOME")) == NULL) {
			if ((pwd = getpwuid(getuid())) == NULL)
				return pattern;
			else
				h = pwd->pw_dir;
		}
	}
	else {
		/*
		 * Expand a ~user
		 */
		if ((pwd = getpwnam((char*) patbuf)) == NULL)
			return pattern;
		else
			h = pwd->pw_dir;
	}

	/* Copy the home directory */
	for (b = patbuf; *h; *b++ = *h++)
		continue;
	
	/* Append the rest of the pattern */
	while ((*b++ = *p++) != EOS)
		continue;

	return patbuf;
}
	

/*
 * The main glob() routine: compiles the pattern (optionally processing
 * quotes), calls glob1() to do the real pattern matching, and finally
 * sorts the list (unless unsorted operation is requested).  Returns 0
 * if things went well, nonzero if errors occurred.  It is not an error
 * to find no matches.
 */
static int
glob0(pattern, pglob)
	const Char *pattern;
	glob_t *pglob;
{
	const Char *qpatnext;
	int c, err, oldpathc;
D 20
	Char *bufnext, *bufend, patbuf[MAXPATHLEN+1];
E 20
I 20
	Char *bufnext, patbuf[MAXPATHLEN+1];
E 20

	qpatnext = globtilde(pattern, patbuf, pglob);
D 22

E 22
	oldpathc = pglob->gl_pathc;
D 22
	pglob->gl_matchc = 0;

E 22
D 20
	bufnext  = patbuf;
	bufend   = bufnext + MAXPATHLEN;
E 20
I 20
	bufnext = patbuf;
E 20

E 19
E 9
D 10
	compilebuf = bufnext;
	compilepat = patnext;
D 9
	while (bufnext < bufend && (c = *patnext++) != EOS) {
E 9
I 9
	/* we don't need to check for buffer overflow any more */
E 10
I 10
	/* We don't need to check for buffer overflow any more. */
E 10
	while ((c = *qpatnext++) != EOS) {
E 9
		switch (c) {
		case LBRACKET:
I 5
D 13
			pglob->gl_flags |= GLOB_MAGCHAR;
E 13
E 5
D 9
			c = *patnext;
E 9
I 9
			c = *qpatnext;
E 9
			if (c == NOT)
D 9
				++patnext;
			if (*patnext == EOS ||
			    strchr(patnext+1, RBRACKET) == NULL) {
E 9
I 9
				++qpatnext;
			if (*qpatnext == EOS ||
D 10
			    Strchr(qpatnext+1, RBRACKET) == NULL) {
E 10
I 10
D 19
			    g_strchr(qpatnext+1, RBRACKET) == NULL) {
E 19
I 19
			    g_strchr((Char *) qpatnext+1, RBRACKET) == NULL) {
E 19
E 10
E 9
				*bufnext++ = LBRACKET;
				if (c == NOT)
D 9
					--patnext;
E 9
I 9
					--qpatnext;
E 9
				break;
			}
			*bufnext++ = M_SET;
			if (c == NOT)
				*bufnext++ = M_NOT;
D 9
			c = *patnext++;
E 9
I 9
			c = *qpatnext++;
E 9
			do {
D 9
				/* todo: quoting */
E 9
D 12
				*bufnext++ = c;
E 12
I 12
				*bufnext++ = CHAR(c);
E 12
D 9
				if (*patnext == RANGE &&
				    (c = patnext[1]) != RBRACKET) {
E 9
I 9
				if (*qpatnext == RANGE &&
				    (c = qpatnext[1]) != RBRACKET) {
E 9
					*bufnext++ = M_RNG;
D 12
					*bufnext++ = c;
E 12
I 12
					*bufnext++ = CHAR(c);
E 12
D 9
					patnext += 2;
E 9
I 9
					qpatnext += 2;
E 9
				}
D 9
			} while ((c = *patnext++) != RBRACKET);
E 9
I 9
			} while ((c = *qpatnext++) != RBRACKET);
I 13
			pglob->gl_flags |= GLOB_MAGCHAR;
E 13
E 9
			*bufnext++ = M_END;
			break;
		case QUESTION:
I 5
			pglob->gl_flags |= GLOB_MAGCHAR;
E 5
			*bufnext++ = M_ONE;
			break;
D 9
		case QUOTE:
			if (!(flags & GLOB_QUOTE))
				*bufnext++ = QUOTE;
			else {
				if ((c = *patnext++) == EOS) {
					c = QUOTE;
					--patnext;
				}
				*bufnext++ = c;
			}
			break;
E 9
		case STAR:
I 5
			pglob->gl_flags |= GLOB_MAGCHAR;
E 5
D 16
			*bufnext++ = M_ALL;
E 16
I 16
			/* collapse adjacent stars to one, 
			 * to avoid exponential behavior
			 */
			if (bufnext == patbuf || bufnext[-1] != M_ALL)
			    *bufnext++ = M_ALL;
E 16
			break;
		default:
D 12
			*bufnext++ = c;
E 12
I 12
			*bufnext++ = CHAR(c);
E 12
			break;
		}
	}
	*bufnext = EOS;
I 9
#ifdef DEBUG
D 19
	qprintf(patbuf);
E 19
I 19
	qprintf("glob0:", patbuf);
E 19
#endif
E 9

	if ((err = glob1(patbuf, pglob)) != 0)
		return(err);

D 13
	if (pglob->gl_pathc == oldpathc && flags & GLOB_NOCHECK) {
E 13
I 13
	/*
	 * If there was no match we are going to append the pattern 
	 * if GLOB_NOCHECK was specified or if GLOB_NOMAGIC was specified
	 * and the pattern did not contain any magic characters
	 * GLOB_NOMAGIC is there just for compatibility with csh.
	 */
	if (pglob->gl_pathc == oldpathc && 
D 19
	    ((flags & GLOB_NOCHECK) || 
	     ((flags & GLOB_NOMAGIC) && !(pglob->gl_flags & GLOB_MAGCHAR)))) {
E 13
D 8
		if (!(flags & GLOB_QUOTE))
			(void)strcpy(compilebuf, compilepat);
E 8
I 8
		if (!(flags & GLOB_QUOTE)) {
D 10
			shortchar_t *dp = compilebuf;
E 10
I 10
			Char *dp = compilebuf;
E 10
D 12
			const char *sp = compilepat;
			while (*dp++ = (u_char)*sp++);
E 12
I 12
			const u_char *sp = compilepat;
			while (*dp++ = *sp++);
E 12
		}
E 8
		else {
			/*
D 10
			 * copy pattern, interpreting quotes; this is slightly
E 10
I 10
			 * Copy pattern, interpreting quotes; this is slightly
E 10
			 * different than the interpretation of quotes above
			 * -- which should prevail?
			 */
			while (*compilepat != EOS) {
				if (*compilepat == QUOTE) {
					if (*++compilepat == EOS)
						--compilepat;
				}
D 8
				*compilebuf++ = *compilepat++;
E 8
I 8
				*compilebuf++ = (u_char)*compilepat++;
E 8
			}
			*compilebuf = EOS;
		}
		return(globextend(patbuf, pglob));
D 8
	} else if (!(flags & GLOB_NOSORT))
		qsort((char*) (pglob->gl_pathv + pglob->gl_offs + oldpathc),
E 8
I 8
	} else if (!(flags & GLOB_NOSORT)) 
E 19
I 19
	    ((pglob->gl_flags & GLOB_NOCHECK) || 
D 23
	      ((pglob->gl_flags & (GLOB_NOMAGIC|GLOB_BRACE|GLOB_TILDE)) || 
E 23
I 23
	      ((pglob->gl_flags & GLOB_NOMAGIC) &&
E 23
	       !(pglob->gl_flags & GLOB_MAGCHAR))))
		return(globextend(pattern, pglob));
	else if (!(pglob->gl_flags & GLOB_NOSORT)) 
E 19
D 10
		qsort((char*)(pglob->gl_pathv + pglob->gl_offs + oldpathc),
E 8
		    pglob->gl_pathc - oldpathc, sizeof(char*), compare);
E 10
I 10
		qsort(pglob->gl_pathv + pglob->gl_offs + oldpathc,
		    pglob->gl_pathc - oldpathc, sizeof(char *), compare);
E 10
	return(0);
}

I 10
static int
compare(p, q)
	const void *p, *q;
{
	return(strcmp(*(char **)p, *(char **)q));
}

E 10
D 19
static
E 19
I 19
static int
E 19
glob1(pattern, pglob)
D 8
	char *pattern;
E 8
I 8
D 10
	shortchar_t *pattern;
E 10
I 10
	Char *pattern;
E 10
E 8
	glob_t *pglob;
{
D 8
	char pathbuf[MAXPATHLEN+1];
E 8
I 8
D 10
	shortchar_t pathbuf[MAXPATHLEN+1];
E 10
I 10
	Char pathbuf[MAXPATHLEN+1];
E 10
E 8

D 10
	/*
D 8
	 * a null pathname is invalid -- POSIX 1003.1 sect. 2.4. */
E 8
I 8
D 9
	 * a null pathname is invalid -- POSIX 1003.1 sect. 2.4. 
E 9
I 9
	 * A null pathname is invalid -- POSIX 1003.1 sect. 2.4. 
E 9
	 */
E 10
I 10
	/* A null pathname is invalid -- POSIX 1003.1 sect. 2.4. */
E 10
E 8
	if (*pattern == EOS)
		return(0);
	return(glob2(pathbuf, pathbuf, pattern, pglob));
}

/*
D 10
 * functions glob2 and glob3 are mutually recursive; there is one level
 * of recursion for each segment in the pattern that contains one or
 * more meta characters.
E 10
I 10
 * The functions glob2 and glob3 are mutually recursive; there is one level
 * of recursion for each segment in the pattern that contains one or more
 * meta characters.
E 10
 */
D 19
static
E 19
I 19
static int
E 19
glob2(pathbuf, pathend, pattern, pglob)
D 8
	char *pathbuf, *pathend, *pattern;
E 8
I 8
D 10
	shortchar_t *pathbuf, *pathend, *pattern;
E 10
I 10
	Char *pathbuf, *pathend, *pattern;
E 10
E 8
	glob_t *pglob;
{
D 7
	struct stat sbuf;
	bool_t anymeta = 0;
E 7
I 7
D 8
	struct stat sb;
	bool_t anymeta;
E 7
	char *p, *q;
E 8
I 8
D 10
	struct stat sbuf;
	shortchar_t *p, *q;
E 10
I 10
	struct stat sb;
	Char *p, *q;
E 10
	int anymeta;
E 8

	/*
D 10
	 * loop over pattern segments until end of pattern or until
E 10
I 10
	 * Loop over pattern segments until end of pattern or until
E 10
	 * segment with meta character found.
	 */
D 7
	for (;;) {
E 7
I 7
	for (anymeta = 0;;) {
E 7
D 10
		if (*pattern == EOS) {		/* end of pattern? */
E 10
I 10
		if (*pattern == EOS) {		/* End of pattern? */
E 10
			*pathend = EOS;
D 7
			if (stat(pathbuf, &sbuf) != 0)
				return(0);	/* need error call here? */
			if ((pglob->gl_flags & GLOB_MARK) &&
			    pathend[-1] != SEP && S_ISDIR(sbuf.st_mode)) {
E 7
I 7
D 8
			if (lstat(pathbuf, &sb))
E 8
I 8
D 10
			if (Lstat(pathbuf, &sbuf))
E 10
I 10
D 15
			if (g_stat(pathbuf, &sb))
E 15
I 15
D 17
			if (g_lstat(pathbuf, &sb))
E 17
I 17
			if (g_lstat(pathbuf, &sb, pglob))
E 17
E 15
E 10
E 8
				return(0);
D 8
			if (pglob->gl_flags & GLOB_MARK && pathend[-1] != SEP &&
			    (S_ISDIR(sb.st_mode) || S_ISLNK(sb.st_mode) &&
			    !stat(pathbuf, &sb) && S_ISDIR(sb.st_mode))) {
E 8
I 8
		
			if (((pglob->gl_flags & GLOB_MARK) &&
D 10
			    pathend[-1] != SEP) && (S_ISDIR(sbuf.st_mode)
			    || (S_ISLNK(sbuf.st_mode) &&
			    (Stat(pathbuf, &sbuf) == 0) &&
			    S_ISDIR(sbuf.st_mode)))) {
E 10
I 10
			    pathend[-1] != SEP) && (S_ISDIR(sb.st_mode)
			    || (S_ISLNK(sb.st_mode) &&
D 17
			    (g_stat(pathbuf, &sb) == 0) &&
E 17
I 17
			    (g_stat(pathbuf, &sb, pglob) == 0) &&
E 17
			    S_ISDIR(sb.st_mode)))) {
E 10
E 8
E 7
				*pathend++ = SEP;
				*pathend = EOS;
			}
I 5
			++pglob->gl_matchc;
E 5
			return(globextend(pathbuf, pglob));
		}

D 10
		/* find end of next segment, copy tentatively to pathend */
E 10
I 10
		/* Find end of next segment, copy tentatively to pathend. */
E 10
		q = pathend;
		p = pattern;
		while (*p != EOS && *p != SEP) {
			if (ismeta(*p))
				anymeta = 1;
			*q++ = *p++;
		}

D 10
		if (!anymeta) {		/* no expansion, do next segment */
E 10
I 10
		if (!anymeta) {		/* No expansion, do next segment. */
E 10
			pathend = q;
			pattern = p;
			while (*pattern == SEP)
				*pathend++ = *pattern++;
D 10
		} else			/* need expansion, recurse */
E 10
I 10
		} else			/* Need expansion, recurse. */
E 10
			return(glob3(pathbuf, pathend, pattern, p, pglob));
	}
	/* NOTREACHED */
}

I 8
D 9

E 9
E 8
D 19
static
E 19
I 19
static int
E 19
glob3(pathbuf, pathend, pattern, restpattern, pglob)
D 8
	char *pathbuf, *pathend, *pattern, *restpattern;
E 8
I 8
D 10
	shortchar_t *pathbuf, *pathend, *pattern, *restpattern;
E 10
I 10
	Char *pathbuf, *pathend, *pattern, *restpattern;
E 10
E 8
	glob_t *pglob;
{
D 10
	extern int errno;
E 10
I 10
	register struct dirent *dp;
I 17
D 19
	struct dirent *(*readdirfunc)();
E 19
E 17
E 10
	DIR *dirp;
D 10
	struct dirent *dp;
E 10
D 19
	int len, err;
E 19
I 19
	int err;
E 19
I 18
	char buf[MAXPATHLEN];
E 18

I 19
	/*
	 * The readdirfunc declaration can't be prototyped, because it is
	 * assigned, below, to two functions which are prototyped in glob.h
	 * and dirent.h as taking pointers to differently typed opaque
	 * structures.
	 */
	struct dirent *(*readdirfunc)();

E 19
	*pathend = EOS;
	errno = 0;
D 8
	if (!(dirp = opendir(pathbuf)))
E 8
I 8
	    
D 10
	if (!(dirp = Opendir(pathbuf)))
E 8
		/* todo: don't call for ENOENT or ENOTDIR? */
E 10
I 10
D 17
	if (!(dirp = g_opendir(pathbuf)))
E 17
I 17
D 18
	if (!(dirp = g_opendir(pathbuf, pglob)))
E 18
I 18
	if ((dirp = g_opendir(pathbuf, pglob)) == NULL) {
E 18
E 17
		/* TODO: don't call for ENOENT or ENOTDIR? */
E 10
D 18
		if (pglob->gl_errfunc &&
		    (*pglob->gl_errfunc)(pathbuf, errno) ||
		    (pglob->gl_flags & GLOB_ERR))
			return(GLOB_ABEND);
		else
			return(0);
E 18
I 18
		if (pglob->gl_errfunc) {
			g_Ctoc(pathbuf, buf);
			if (pglob->gl_errfunc(buf, errno) ||
			    pglob->gl_flags & GLOB_ERR)
				return (GLOB_ABEND);
		}
		return(0);
	}
E 18

	err = 0;

D 10
	/* search directory for matching names */
E 10
I 10
	/* Search directory for matching names. */
E 10
D 17
	while ((dp = readdir(dirp))) {
E 17
I 17
	if (pglob->gl_flags & GLOB_ALTDIRFUNC)
		readdirfunc = pglob->gl_readdir;
	else
		readdirfunc = readdir;
	while ((dp = (*readdirfunc)(dirp))) {
E 17
I 8
D 12
		register char *sc;
E 12
I 12
		register u_char *sc;
E 12
D 10
		register shortchar_t *dc;
E 8
		/* initial DOT must be matched literally */
E 10
I 10
		register Char *dc;

		/* Initial DOT must be matched literally. */
E 10
		if (dp->d_name[0] == DOT && *pattern != DOT)
			continue;
D 8
		if (!match(dp->d_name, pattern, restpattern))
E 8
I 8
D 12
		for (sc = dp->d_name, dc = pathend; 
		     *dc++ = (u_char)*sc++;);
E 12
I 12
		for (sc = (u_char *) dp->d_name, dc = pathend; 
D 19
		     *dc++ = *sc++;);
E 19
I 19
		     (*dc++ = *sc++) != EOS;)
			continue;
E 19
E 12
		if (!match(pathend, pattern, restpattern)) {
			*pathend = EOS;
E 8
			continue;
D 8
		len = dp->d_namlen;
		(void)strcpy(pathend, dp->d_name);
		err = glob2(pathbuf, pathend+len, restpattern, pglob);
E 8
I 8
		}
		err = glob2(pathbuf, --dc, restpattern, pglob);
E 8
		if (err)
			break;
	}
D 10
	/* todo: check error from readdir? */
E 10
I 10

D 17
	/* TODO: check error from readdir? */
E 10
	(void)closedir(dirp);
E 17
I 17
	if (pglob->gl_flags & GLOB_ALTDIRFUNC)
		(*pglob->gl_closedir)(dirp);
	else
		closedir(dirp);
E 17
	return(err);
}


/*
 * Extend the gl_pathv member of a glob_t structure to accomodate a new item,
 * add the new item, and update gl_pathc.
 *
 * This assumes the BSD realloc, which only copies the block when its size
 * crosses a power-of-two boundary; for v7 realloc, this would cause quadratic
 * behavior.
 *
 * Return 0 if new item added, error code if memory couldn't be allocated.
 *
 * Invariant of the glob_t structure:
 *	Either gl_pathc is zero and gl_pathv is NULL; or gl_pathc > 0 and
D 10
 *	 gl_pathv points to (gl_offs + gl_pathc + 1) items.
E 10
I 10
 *	gl_pathv points to (gl_offs + gl_pathc + 1) items.
E 10
 */
D 8
static
E 8
I 8
static int
E 8
globextend(path, pglob)
D 8
	char *path;
E 8
I 8
D 10
	shortchar_t *path;
E 10
I 10
D 19
	Char *path;
E 19
I 19
	const Char *path;
E 19
E 10
E 8
	glob_t *pglob;
{
	register char **pathv;
	register int i;
D 8
	u_int copysize, newsize;
E 8
I 8
	u_int newsize;
E 8
	char *copy;
I 8
D 10
	shortchar_t *p;
E 10
I 10
D 19
	Char *p;
E 19
I 19
	const Char *p;
E 19
E 10
E 8

	newsize = sizeof(*pathv) * (2 + pglob->gl_pathc + pglob->gl_offs);
D 8
	pathv = (char **)realloc((char *)(pathv = pglob->gl_pathv), newsize);
E 8
I 8
D 19
	pathv = (char **)realloc((char *)pglob->gl_pathv, newsize);
E 19
I 19
	pathv = pglob->gl_pathv ? 
		    realloc((char *)pglob->gl_pathv, newsize) :
		    malloc(newsize);
E 19
E 8
	if (pathv == NULL)
		return(GLOB_NOSPACE);

	if (pglob->gl_pathv == NULL && pglob->gl_offs > 0) {
		/* first time around -- clear initial gl_offs items */
		pathv += pglob->gl_offs;
		for (i = pglob->gl_offs; --i >= 0; )
			*--pathv = NULL;
	}
	pglob->gl_pathv = pathv;

D 8
	copysize = strlen(path) + 1;
	if ((copy = malloc(copysize)) != NULL) {
		(void)strcpy(copy, path);
E 8
I 8
D 19
	for (p = path; *p++;);
E 19
I 19
	for (p = path; *p++;)
		continue;
E 19
	if ((copy = malloc(p - path)) != NULL) {
D 9
		register char *dc = copy;
		register shortchar_t *sc = path;
		while (*dc++ = *sc++);
E 9
I 9
D 10
		register char *dc;
		register shortchar_t *sc;

		for (dc = copy, sc = path; *dc++ = *sc++;);
E 10
I 10
		g_Ctoc(path, copy);
E 10
E 9
E 8
		pathv[pglob->gl_offs + pglob->gl_pathc++] = copy;
	}
	pathv[pglob->gl_offs + pglob->gl_pathc] = NULL;
D 10
	return((copy == NULL) ? GLOB_NOSPACE : 0);
E 10
I 10
	return(copy == NULL ? GLOB_NOSPACE : 0);
E 10
}


/*
 * pattern matching function for filenames.  Each occurrence of the *
 * pattern causes a recursion level.
 */
D 8
static bool_t
E 8
I 8
D 19
static
E 19
I 19
static int
E 19
E 8
match(name, pat, patend)
D 8
	register char *name, *pat, *patend;
E 8
I 8
D 10
	register shortchar_t *name, *pat, *patend;
E 10
I 10
	register Char *name, *pat, *patend;
E 10
E 8
{
D 8
	bool_t ok, negate_range;
	char c, k;
E 8
I 8
	int ok, negate_range;
D 10
	shortchar_t c, k;
E 10
I 10
	Char c, k;
E 10
E 8

	while (pat < patend) {
		c = *pat++;
D 8
		switch (c & 0xff) {
E 8
I 8
		switch (c & M_MASK) {
E 8
		case M_ALL:
			if (pat == patend)
				return(1);
D 10
			for (; *name != EOS; ++name) {
E 10
I 10
D 16
			for (; *name != EOS; ++name)
E 10
				if (match(name, pat, patend))
					return(1);
E 16
I 16
			do 
			    if (match(name, pat, patend))
				    return(1);
			while (*name++ != EOS);
E 16
D 10
			}
E 10
			return(0);
		case M_ONE:
			if (*name++ == EOS)
				return(0);
			break;
		case M_SET:
			ok = 0;
D 14
			k = *name++;
E 14
I 14
			if ((k = *name++) == EOS)
				return(0);
E 14
D 8
			if (negate_range = (*pat & 0xff) == M_NOT)
E 8
I 8
D 19
			if (negate_range = ((*pat & M_MASK) == M_NOT))
E 19
I 19
			if ((negate_range = ((*pat & M_MASK) == M_NOT)) != EOS)
E 19
E 8
				++pat;
D 8
			while (((c = *pat++) & 0xff) != M_END) {
				if ((*pat & 0xff) == M_RNG) {
E 8
I 8
D 10
			while (((c = *pat++) & M_MASK) != M_END) {
E 10
I 10
			while (((c = *pat++) & M_MASK) != M_END)
E 10
				if ((*pat & M_MASK) == M_RNG) {
E 8
					if (c <= k && k <= pat[1])
						ok = 1;
					pat += 2;
D 10
				}
				else if (c == k)
E 10
I 10
				} else if (c == k)
E 10
					ok = 1;
D 10
			}
E 10
			if (ok == negate_range)
				return(0);
			break;
		default:
			if (*name++ != c)
				return(0);
			break;
		}
	}
	return(*name == EOS);
}

D 10
/* free allocated data belonging to a glob_t structure */
E 10
I 10
/* Free allocated data belonging to a glob_t structure. */
E 10
void
globfree(pglob)
	glob_t *pglob;
{
	register int i;
	register char **pp;

	if (pglob->gl_pathv != NULL) {
		pp = pglob->gl_pathv + pglob->gl_offs;
		for (i = pglob->gl_pathc; i--; ++pp)
			if (*pp)
D 6
				(void)free(*pp);
		(void)free((char *)pp);
E 6
I 6
D 9
				free((void *)*pp);
		free((void *)pglob->gl_pathv);
E 9
I 9
D 10
				free(pp);
E 10
I 10
				free(*pp);
E 10
		free(pglob->gl_pathv);
E 9
E 6
	}
}
I 10

static DIR *
D 17
g_opendir(str)
E 17
I 17
g_opendir(str, pglob)
E 17
	register Char *str;
I 17
	glob_t *pglob;
E 17
{
	char buf[MAXPATHLEN];
I 17
D 19
	char *dirname;
E 19
E 17

	if (!*str)
D 17
		return(opendir("."));
	g_Ctoc(str, buf);
E 17
I 17
		strcpy(buf, ".");
	else
		g_Ctoc(str, buf);
I 19

E 19
	if (pglob->gl_flags & GLOB_ALTDIRFUNC)
		return((*pglob->gl_opendir)(buf));
I 19

E 19
E 17
	return(opendir(buf));
}

static int
D 17
g_lstat(fn, sb)
E 17
I 17
g_lstat(fn, sb, pglob)
E 17
	register Char *fn;
	struct stat *sb;
I 17
	glob_t *pglob;
E 17
{
	char buf[MAXPATHLEN];

	g_Ctoc(fn, buf);
I 17
	if (pglob->gl_flags & GLOB_ALTDIRFUNC)
		return((*pglob->gl_lstat)(buf, sb));
E 17
	return(lstat(buf, sb));
}

static int
D 17
g_stat(fn, sb)
E 17
I 17
g_stat(fn, sb, pglob)
E 17
	register Char *fn;
	struct stat *sb;
I 17
	glob_t *pglob;
E 17
{
	char buf[MAXPATHLEN];

	g_Ctoc(fn, buf);
I 17
	if (pglob->gl_flags & GLOB_ALTDIRFUNC)
		return((*pglob->gl_stat)(buf, sb));
E 17
	return(stat(buf, sb));
}

static Char *
g_strchr(str, ch)
	Char *str;
	int ch;
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++);
	return (NULL);
}

I 19
#ifdef notdef
static Char *
g_strcat(dst, src)
	Char *dst;
	const Char* src;
{
	Char *sdst = dst;

	while (*dst++)
		continue;
	--dst;
	while((*dst++ = *src++) != EOS)
	    continue;

	return (sdst);
}
#endif

E 19
static void
g_Ctoc(str, buf)
D 19
	register Char *str;
E 19
I 19
	register const Char *str;
E 19
	char *buf;
{
	register char *dc;

D 19
	for (dc = buf; *dc++ = *str++;);
E 19
I 19
	for (dc = buf; (*dc++ = *str++) != EOS;)
		continue;
E 19
}

#ifdef DEBUG
static void 
D 19
qprintf(s)
E 19
I 19
qprintf(str, s)
	const char *str;
E 19
	register Char *s;
{
	register Char *p;

I 19
	(void)printf("%s:\n", str);
E 19
	for (p = s; *p; p++)
D 18
		(void)printf("%c", *p & 0xff);
E 18
I 18
		(void)printf("%c", CHAR(*p));
E 18
	(void)printf("\n");
	for (p = s; *p; p++)
		(void)printf("%c", *p & M_PROTECT ? '"' : ' ');
	(void)printf("\n");
	for (p = s; *p; p++)
D 18
		(void)printf("%c", *p & M_META ? '_' : ' ');
E 18
I 18
		(void)printf("%c", ismeta(*p) ? '_' : ' ');
E 18
	(void)printf("\n");
}
#endif
E 10
E 1
