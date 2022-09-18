h09512
s 00004/00002/00329
d D 8.2 95/05/04 15:49:32 bostic 16 15
c optarg/optind moved to unistd.h
e
s 00005/00005/00326
d D 8.1 93/06/14 13:00:51 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00005/00315
d D 5.4 93/06/14 12:59:59 bostic 14 12
c add Sun's -t option; don't infinitely loop if the file changes
e
s 00005/00005/00315
d R 8.1 93/06/09 22:46:42 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00318
d D 5.3 92/10/24 15:20:56 ralph 12 11
c fix gcc2 static warning
e
s 00008/00003/00311
d D 5.2 92/06/24 09:48:12 bostic 11 10
c delete MAP_FILE, check file size before attempting to map
e
s 00245/00101/00069
d D 5.1 91/07/21 16:26:34 bostic 10 9
c new version from scratch
e
s 00008/00007/00162
d D 4.9 91/04/18 15:55:28 bostic 9 8
c new copyright; att/bsd/shared
e
s 00003/00005/00166
d D 4.8 91/03/01 14:57:35 bostic 8 7
c ANSI
e
s 00002/00001/00169
d D 4.7 89/05/11 09:57:51 bostic 7 6
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00169
d D 4.6 89/04/14 02:30:07 marc 6 5
c /usr/dict/words -> /usr/share/dict/words
e
s 00002/00003/00168
d D 4.5 87/10/06 17:09:20 bostic 5 4
c -df get set even if one or the other already set
e
s 00001/00001/00170
d D 4.4 87/10/06 14:37:35 bostic 4 3
c buf should have been a register
e
s 00138/00131/00033
d D 4.3 87/08/05 12:37:18 bostic 3 2
c well, I needed to understand it, so I rewrote it.  Added getopt(3),
c a usage message, removed the hooks for a 't' flag, replaced its private 
c compare routine with strncmp(2), made it faster (not that anyone would 
c ever notice), and made it lint cleanly.
e
s 00001/00000/00163
d D 4.2 81/07/02 02:07:18 root 2 1
c add exit(0) per day
e
s 00163/00000/00000
d D 4.1 80/10/01 17:27:22 bill 1 0
c date and time created 80/10/01 17:27:22 by bill
e
u
U
t
T
I 1
D 3
static char *sccsid = "%W% (Berkeley) %G%";
E 3
I 3
D 9
/*
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
/*-
D 10
 * Copyright (c) 1987 The Regents of the University of California.
E 10
I 10
D 15
 * Copyright (c) 1991 The Regents of the University of California.
E 10
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
D 10
 * %sccs.include.proprietary.c%
E 10
I 10
 * This code is derived from software contributed to Berkeley by
 * David Hitz of Auspex Systems, Inc.
 *
 * %sccs.include.redist.c%
E 10
E 9
 */

#ifndef lint
D 15
char copyright[] =
D 9
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 9
I 9
D 10
"%Z% Copyright (c) 1987 The Regents of the University of California.\n\
E 10
I 10
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
E 10
E 9
 All rights reserved.\n";
E 15
I 15
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 15
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9

I 10
/*
 * look -- find lines in a sorted list.
 * 
 * The man page said that TABs and SPACEs participate in -d comparisons.
 * In fact, they were ignored.  This implements historic practice, not
 * the manual page.
 */

E 10
#include <sys/types.h>
D 10
#include <sys/file.h>
E 10
I 10
#include <sys/mman.h>
E 10
#include <sys/stat.h>
I 11

D 16
#include <limits.h>
E 16
I 16
#include <ctype.h>
E 16
E 11
I 10
#include <errno.h>
#include <fcntl.h>
I 16
#include <limits.h>
E 16
E 10
E 3
#include <stdio.h>
I 10
#include <stdlib.h>
#include <string.h>
E 10
D 16
#include <ctype.h>
E 16
I 16
#include <unistd.h>

E 16
I 7
#include "pathnames.h"
E 7

D 3
FILE *dfile;
char *filenam  = "/usr/dict/words";
E 3
I 3
D 10
#define	EOS		'\0'
#define	MAXLINELEN	250
#define	YES		1
E 10
I 10
/*
 * FOLD and DICT convert characters to a normal form for comparison,
 * according to the user specified flags.
 * 
 * DICT expects integers because it uses a non-character value to
 * indicate a character which should not participate in comparisons.
 */
#define	EQUAL		0
#define	GREATER		1
#define	LESS		(-1)
#define NO_COMPARE	(-2)
E 10
E 3

D 3
int fold;
int dict;
int tab;
char entry[250];
char word[250];
char key[50];
E 3
I 3
D 10
static int	fold, dict, len;
E 10
I 10
#define	FOLD(c)	(isascii(c) && isupper(c) ? tolower(c) : (c))
#define	DICT(c)	(isascii(c) && isalnum(c) ? (c) : NO_COMPARE)
E 10
E 3

I 10
int dflag, fflag;

char	*binary_search __P((char *, char *, char *));
int	 compare __P((char *, char *, char *));
void	 err __P((const char *fmt, ...));
char	*linear_search __P((char *, char *, char *));
int	 look __P((char *, char *, char *));
void	 print_from __P((char *, char *, char *));
D 12
void	 usage __P((void));
E 12
I 12

static void usage __P((void));
E 12

E 10
D 3
main(argc,argv)
char **argv;
E 3
I 3
main(argc, argv)
D 10
	int	argc;
	char	**argv;
E 10
I 10
	int argc;
	char *argv[];
E 10
E 3
{
D 3
	register c;
	long top,bot,mid;
	while(argc>=2 && *argv[1]=='-') {
		for(;;) {
			switch(*++argv[1]) {
			case 'd':
				dict++;
				continue;
			case 'f':
				fold++;
				continue;
			case 't':
				tab = argv[1][1];
				if(tab)
					++argv[1];
				continue;
			case 0:
				break;
			default:
				continue;
			}
E 3
I 3
D 10
	extern char	*optarg;
	extern int	optind;
D 6
	static char	*filename = "/usr/dict/words";
E 6
I 6
D 7
	static char	*filename = "/usr/share/dict/words";
E 7
I 7
	static char	*filename = _PATH_WORDS;
E 7
E 6
	register off_t	bot, mid, top;
	register int	c;
	struct stat	sb;
	char	entry[MAXLINELEN], copy[MAXLINELEN];
E 10
I 10
	struct stat sb;
D 14
	int ch, fd;
	char *back, *file, *front, *string;
E 14
I 14
	int ch, fd, termchar;
	char *back, *file, *front, *string, *p;
E 14
E 10

D 10
	while ((c = getopt(argc, argv, "df")) != EOF)
		switch((char)c) {
E 10
I 10
	file = _PATH_WORDS;
D 14
	while ((ch = getopt(argc, argv, "df")) != EOF)
E 14
I 14
	termchar = '\0';
	while ((ch = getopt(argc, argv, "dft:")) != EOF)
E 14
		switch(ch) {
E 10
		case 'd':
D 10
			dict = YES;
E 10
I 10
			dflag = 1;
E 10
E 3
			break;
I 3
		case 'f':
D 10
			fold = YES;
E 10
I 10
			fflag = 1;
E 10
			break;
I 14
		case 't':
			termchar = *optarg;
			break;
E 14
		case '?':
		default:
			usage();
E 3
		}
D 3
		argc --;
		argv++;
E 3
I 3
D 10
	argv += optind;
E 10
	argc -= optind;
I 10
	argv += optind;
E 10

D 10
	switch(argc) {
D 5
	case 1:	/* if nothing set, default to dictionary order and folding */
		if (!dict && !fold)
			dict = fold = YES;
E 5
I 5
	case 1:	/* if default file, set to dictionary order and folding */
		dict = fold = YES;
E 10
I 10
	switch (argc) {
	case 2:				/* Don't set -df for user. */
		string = *argv++;
		file = *argv;
E 10
E 5
		break;
D 10
	case 2:
		filename = argv[1];
E 10
I 10
	case 1:				/* But set -df by default. */
		dflag = fflag = 1;
		string = *argv;
E 10
		break;
	default:
		usage();
E 3
	}
D 3
	if(argc<=1)
		return;
	if(argc==2) {
		fold++;
		dict++;
	} else
		filenam = argv[2];
	dfile = fopen(filenam,"r");
	if(dfile==NULL) {
		fprintf(stderr,"look: can't open %s\n",filenam);
E 3
I 3

I 14
	if (termchar != '\0' && (p = strchr(string, termchar)) != NULL)
		*++p = '\0';

E 14
D 10
	if (!freopen(filename, "r", stdin)) {
		fprintf(stderr,"look: can't read %s.\n", filename);
E 3
		exit(2);
	}
D 3
	canon(argv[1],key);
	bot = 0;
	fseek(dfile,0L,2);
	top = ftell(dfile);
	for(;;) {
		mid = (top+bot)/2;
		fseek(dfile,mid,0);
		do {
			c = getc(dfile);
			mid++;
		} while(c!=EOF && c!='\n');
		if(!getword(entry))
E 3
I 3
	if (fstat(fileno(stdin), &sb)) {
		perror("look: fstat");
		exit(2);
	}
E 10
I 10
D 11
	if ((fd = open(file, O_RDONLY, 0)) < 0 || fstat(fd, &sb) ||
	    (front = mmap(NULL, sb.st_size, PROT_READ, MAP_FILE, fd,
	    (off_t)0)) == NULL)
E 11
I 11
	if ((fd = open(file, O_RDONLY, 0)) < 0 || fstat(fd, &sb))
		err("%s: %s", file, strerror(errno));
	if (sb.st_size > SIZE_T_MAX)
		err("%s: %s", file, strerror(EFBIG));
	if ((front = mmap(NULL,
	    (size_t)sb.st_size, PROT_READ, 0, fd, (off_t)0)) == NULL)
E 11
		err("%s: %s", file, strerror(errno));
	back = front + sb.st_size;
	exit(look(string, front, back));
}
E 10

D 10
	len = strlen(*argv);
	canon(*argv, *argv);
	len = strlen(*argv);		/* may have changed */
	if (len > MAXLINELEN - 1) {
D 8
		fputs("look: search string is too long.\n", stderr);
E 8
I 8
		(void)fprintf(stderr,
		    "look: search string is too long.\n");
E 8
		exit(2);
E 10
I 10
look(string, front, back)
	char *string, *front, *back;
{
	register int ch;
	register char *readp, *writep;

	/* Reformat string string to avoid doing it multiple times later. */
	for (readp = writep = string; ch = *readp++;) {
		if (fflag)
			ch = FOLD(ch);
		if (dflag)
			ch = DICT(ch);
		if (ch != NO_COMPARE)
			*(writep++) = ch;
E 10
	}
I 10
	*writep = '\0';
E 10

D 10
	for (bot = 0, top = sb.st_size;;) {
		mid = (top + bot) / 2;
		(void)fseek(stdin, mid, L_SET);
E 10
I 10
	front = binary_search(string, front, back);
	front = linear_search(string, front, back);
E 10

D 10
		for (++mid; (c = getchar()) != EOF && c != '\n'; ++mid);
		if (!getline(entry))
E 3
			break;
D 3
		canon(entry,word);
		switch(compare(key,word)) {
		case -2:
		case -1:
		case 0:
			if(top<=mid)
E 3
I 3
		canon(entry, copy);
		if (strncmp(*argv, copy, len) <= 0) {
			if (top <= mid)
E 3
				break;
			top = mid;
D 3
			continue;
		case 1:
		case 2:
			bot = mid;
			continue;
E 3
		}
E 10
I 10
	if (front)
		print_from(string, front, back);
	return (front ? 0 : 1);
}


/*
 * Binary search for "string" in memory between "front" and "back".
 * 
 * This routine is expected to return a pointer to the start of a line at
 * *or before* the first word matching "string".  Relaxing the constraint
 * this way simplifies the algorithm.
 * 
 * Invariants:
 * 	front points to the beginning of a line at or before the first 
 *	matching string.
 * 
 * 	back points to the beginning of a line at or after the first 
 *	matching line.
 * 
 * Base of the Invariants.
 * 	front = NULL; 
 *	back = EOF;
 * 
 * Advancing the Invariants:
 * 
 * 	p = first newline after halfway point from front to back.
 * 
 * 	If the string at "p" is not greater than the string to match, 
 *	p is the new front.  Otherwise it is the new back.
 * 
 * Termination:
 * 
 * 	The definition of the routine allows it return at any point, 
 *	since front is always at or before the line to print.
 * 
 * 	In fact, it returns when the chosen "p" equals "back".  This 
 *	implies that there exists a string is least half as long as 
 *	(back - front), which in turn implies that a linear search will 
 *	be no more expensive than the cost of simply printing a string or two.
 * 
 * 	Trying to continue with binary search at this point would be 
 *	more trouble than it's worth.
 */
#define	SKIP_PAST_NEWLINE(p, back) \
	while (p < back && *p++ != '\n');

char *
binary_search(string, front, back)
	register char *string, *front, *back;
{
	register char *p;

	p = front + (back - front) / 2;
	SKIP_PAST_NEWLINE(p, back);

D 14
	while (p != back) {
E 14
I 14
	/*
	 * If the file changes underneath us, make sure we don't
	 * infinitely loop.
	 */
	while (p < back && back > front) {
E 14
		if (compare(string, p, back) == GREATER)
			front = p;
E 10
D 3
		break;
E 3
I 3
		else
D 10
			bot = mid;
E 10
I 10
			back = p;
		p = front + (back - front) / 2;
		SKIP_PAST_NEWLINE(p, back);
E 10
E 3
	}
D 3
	fseek(dfile,bot,0);
	while(ftell(dfile)<top) {
		if(!getword(entry))
			return;
		canon(entry,word);
		switch(compare(key,word)) {
		case -2:
			return;
		case -1:
		case 0:
			puts(entry,stdout);
E 3
I 3
D 10
	(void)fseek(stdin, bot, L_SET);
	while (ftell(stdin) < top) {
		register int val;
E 10
I 10
	return (front);
}
E 10

D 10
		if (!getline(entry))
			exit(0);
		canon(entry, copy);
		if (!(val = strncmp(*argv, copy, len))) {
			puts(entry);
E 10
I 10
/*
 * Find the first line that starts with string, linearly searching from front
 * to back.
 * 
 * Return NULL for no such line.
 * 
 * This routine assumes:
 * 
 * 	o front points at the first character in a line. 
 *	o front is before or at the first line to be printed.
 */
char *
linear_search(string, front, back)
	char *string, *front, *back;
{
	while (front < back) {
		switch (compare(string, front, back)) {
		case EQUAL:		/* Found it. */
			return (front);
E 10
E 3
			break;
I 10
		case LESS:		/* No such string. */
			return (NULL);
			break;
		case GREATER:		/* Keep going. */
			break;
E 10
D 3
		case 1:
		case 2:
			continue;
E 3
		}
D 3
		break;
E 3
I 3
D 10
		if (val < 0)
			exit(0);
E 10
I 10
		SKIP_PAST_NEWLINE(front, back);
E 10
E 3
	}
D 3
	while(getword(entry)) {
		canon(entry,word);
		switch(compare(key,word)) {
		case -1:
		case 0:
			puts(entry,stdout);
			continue;
		}
		break;
E 3
I 3
D 10
	while (getline(entry)) {
		canon(entry, copy);
		if (strncmp(*argv, copy, len))
			break;
		puts(entry);
E 3
	}
I 2
	exit(0);
E 10
I 10
	return (NULL);
E 10
E 2
}

D 3
compare(s,t)
register char *s,*t;
E 3
I 3
/*
D 10
 * getline --
 *	get a line
E 10
I 10
 * Print as many lines as match string, starting at front.
E 10
 */
D 8
static
E 8
D 10
getline(buf)
D 4
	char	*buf;
E 4
I 4
	register char	*buf;
E 10
I 10
void 
print_from(string, front, back)
	register char *string, *front, *back;
E 10
E 4
E 3
{
D 3
	for(;*s==*t;s++,t++)
		if(*s==0)
			return(0);
	return(*s==0? -1:
		*t==0? 1:
		*s<*t? -2:
		2);
}
E 3
I 3
D 10
	register int	c;
E 3

D 3
getword(w)
char *w;
{
	register c;
	for(;;) {
		c = getc(dfile);
		if(c==EOF)
E 3
I 3
	for (;;) {
		if ((c = getchar()) == EOF)
E 3
			return(0);
D 3
		if(c=='\n')
E 3
I 3
		if (c == '\n')
E 3
			break;
D 3
		*w++ = c;
E 3
I 3
		*buf++ = c;
E 10
I 10
	for (; front < back && compare(string, front, back) == EQUAL; ++front) {
		for (; front < back && *front != '\n'; ++front)
			if (putchar(*front) == EOF)
				err("stdout: %s", strerror(errno));
		if (putchar('\n') == EOF)
			err("stdout: %s", strerror(errno));
E 10
E 3
	}
D 3
	*w = 0;
E 3
I 3
D 10
	*buf = EOS;
E 3
	return(1);
E 10
}

D 3
canon(old,new)
char *old,*new;
E 3
I 3
/*
D 10
 * canon --
 *	create canonical version of word
E 10
I 10
 * Return LESS, GREATER, or EQUAL depending on how the string1 compares with
 * string2 (s1 ??? s2).
 * 
 * 	o Matches up to len(s1) are EQUAL. 
 *	o Matches up to len(s2) are GREATER.
 * 
 * Compare understands about the -f and -d flags, and treats comparisons
 * appropriately.
 * 
 * The string "s1" is null terminated.  The string s2 is '\n' terminated (or
 * "back" terminated).
E 10
 */
D 8
static
E 8
D 10
canon(src, copy)
	register char	*src, *copy;
E 10
I 10
int
compare(s1, s2, back)
	register char *s1, *s2, *back;
E 10
E 3
{
D 3
	register c;
	for(;;) {
		*new = c = *old++;
		if(c==0||c==tab) {
			*new = 0;
			break;
		}
		if(dict) {
			if(!isalnum(c))
				continue;
		}
		if(fold) {
			if(isupper(c))
				*new += 'a' - 'A';
		}
		new++;
	}
E 3
I 3
D 10
	register int	cnt;
	register char	c;
E 10
I 10
	register int ch;
E 10

D 10
	for (cnt = len + 1; (c = *src++) && cnt; --cnt)
		if (!dict || isalnum(c))
			*copy++ = fold && isupper(c) ? tolower(c) : c;
	*copy = EOS;
E 10
I 10
	for (; *s1 && s2 < back && *s2 != '\n'; ++s1, ++s2) {
		ch = *s2;
		if (fflag)
			ch = FOLD(ch);
		if (dflag)
			ch = DICT(ch);

		if (ch == NO_COMPARE) {
			++s2;		/* Ignore character in comparison. */
			continue;
		}
		if (*s1 != ch)
			return (*s1 < ch ? LESS : GREATER);
	}
	return (*s1 ? GREATER : EQUAL);
E 10
}

D 10
/*
 * usage --
 *	print a usage message and die
 */
E 10
I 10
static void
E 10
D 8
static
E 8
usage()
{
D 8
	fputs("usage: look [-df] string [file]\n", stderr);
E 8
I 8
D 14
	(void)fprintf(stderr, "usage: look [-df] string [file]\n");
E 14
I 14
	(void)fprintf(stderr, "usage: look [-df] [-t char] string [file]\n");
E 14
E 8
D 10
	exit(1);
E 10
I 10
	exit(2);
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "look: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(2);
	/* NOTREACHED */
E 10
E 3
}
E 1
