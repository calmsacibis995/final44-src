h20454
s 00002/00002/00188
d D 8.1 93/06/11 14:48:20 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00094/00103/00096
d D 5.2 93/06/11 14:44:01 bostic 2 1
c integrate into 4.4BSD
e
s 00199/00000/00000
d D 5.1 93/06/10 11:09:54 bostic 1 0
c date and time created 93/06/10 11:09:54 by bostic
e
u
U
t
T
I 1
D 2
/* vi: set tabstop=4 : */
E 2
I 2
/*-
D 3
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Barry Brachman.
 *
 * %sccs.include.redist.c%
 */
E 2

D 2
#include <stdio.h>
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

D 2
#include "bog.h"

#ifdef ATARI
#include <stat.h>
#include <osbind.h>
#define malloc(x)       Malloc(x)
#else
E 2
#include <sys/types.h>
#include <sys/stat.h>
D 2
#endif
E 2

I 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bog.h"
#include "extern.h"

E 2
static char *dictspace, *dictend;
static char *sp;

static int first = 1, lastch = 0;

D 2
char *index();
long atol();

E 2
/*
 * Return the next word in the compressed dictionary in 'buffer' or
 * NULL on end-of-file
 */
char *
nextword(fp)
D 2
FILE *fp;
E 2
I 2
	FILE *fp;
E 2
{
D 2
    register int ch, pcount;
E 2
I 2
	extern int wordlen;
	register int ch, pcount;
E 2
	register char *p;
	static char buf[MAXWORDLEN + 1];
D 2
	extern int wordlen;
E 2

D 2
	if (fp == (FILE *) NULL) {
	    if (sp == dictend)
			return((char *) NULL);

E 2
I 2
	if (fp == NULL) {
		if (sp == dictend)
			return (NULL);
	
E 2
		p = buf + (int) *sp++;

		/*
		 * The dictionary ends with a null byte
		 */
D 2
	    while (*sp >= 'a') {
E 2
I 2
		while (*sp >= 'a')
E 2
			if ((*p++ = *sp++) == 'q')
				*p++ = 'u';
D 2
		}
	}
	else {
    	if (first) {
	        if ((pcount = getc(fp)) == EOF)
				return((char *) NULL);
E 2
I 2
	} else {
		if (first) {
			if ((pcount = getc(fp)) == EOF)
				return (NULL);
E 2
			first = 0;
D 2
		}
		else if ((pcount = lastch) == EOF)
			return((char *) NULL);
E 2
I 2
		} else if ((pcount = lastch) == EOF)
			return (NULL);
E 2

		p = buf + pcount;
 
D 2
	    while ((ch = getc(fp)) != EOF && ch >= 'a') {
E 2
I 2
		while ((ch = getc(fp)) != EOF && ch >= 'a')
E 2
			if ((*p++ = ch) == 'q')
				*p++ = 'u';
D 2
		}
	    lastch = ch;
E 2
I 2
		lastch = ch;
E 2
	}
	wordlen = (int) (p - buf);
D 2
    *p = '\0';
    return(buf);
E 2
I 2
	*p = '\0';
	return (buf);
E 2
}
 
/*
 * Reset the state of nextword() and do the fseek()
 */
I 2
long
E 2
dictseek(fp, offset, ptrname)
D 2
FILE *fp;
long offset;
int ptrname;
E 2
I 2
	FILE *fp;
	long offset;
	int ptrname;
E 2
{
D 2

	if (fp == (FILE *) NULL) {
E 2
I 2
	if (fp == NULL) {
E 2
		if ((sp = dictspace + offset) >= dictend)
D 2
			return(-1);
		return(0);
E 2
I 2
			return (-1);
		return (0);
E 2
	}

	first = 1;
D 2
	return(fseek(fp, offset, ptrname));
E 2
I 2
	return (fseek(fp, offset, ptrname));
E 2
}

FILE *
opendict(dict)
D 2
char *dict;
E 2
I 2
	char *dict;
E 2
{
	FILE *fp;

D 2
#ifdef ATARI
	if ((fp = fopen(dict, "rb")) == (FILE *) NULL)
		return((FILE *) NULL);
#else
	if ((fp = fopen(dict, "r")) == (FILE *) NULL)
		return((FILE *) NULL);
#endif
	return(fp);
E 2
I 2
	if ((fp = fopen(dict, "r")) == NULL)
		return (NULL);
	return (fp);
E 2
}

/*
 * Load the given dictionary and initialize the pointers
 */
I 2
int
E 2
loaddict(fp)
D 2
FILE *fp;
E 2
I 2
	FILE *fp;
E 2
{
I 2
	struct stat statb;
	long n;
E 2
	int st;
	char *p;
D 2
	long n;
	struct stat statb;
E 2

D 2
#ifdef ATARI
	if (stat(DICT, &statb) < 0) {
		(void) fclose(fp);
		return(-1);
	}
#else
	char *malloc();

E 2
	if (fstat(fileno(fp), &statb) < 0) {
D 2
		(void) fclose(fp);
		return(-1);
E 2
I 2
		(void)fclose(fp);
		return (-1);
E 2
	}
D 2
#endif
E 2

	/*
D 2
	 * An extra character (a sentinel) is allocated and set to null to improve
	 * the expansion loop in nextword()
E 2
I 2
	 * An extra character (a sentinel) is allocated and set to null
	 * to improve the expansion loop in nextword().
E 2
	 */
D 2
	if ((dictspace = (char *) malloc(statb.st_size + 1)) == (char *) NULL) {
		(void) fclose(fp);
		return(-1);
E 2
I 2
	if ((dictspace = malloc(statb.st_size + 1)) == NULL) {
		(void)fclose(fp);
		return (-1);
E 2
	}
D 2
	n = (long) statb.st_size;
E 2
I 2
	n = (long)statb.st_size;
E 2
	sp = dictspace;
	dictend = dictspace + n;

	p = dictspace;
I 2
	st = -1;
E 2
	while (n > 0 && (st = fread(p, 1, BUFSIZ, fp)) > 0) {
		p += st;
		n -= st;
	}
	if (st < 0) {
D 2
		(void) fclose(fp);
		(void) fprintf(stderr, "Error reading dictionary\n");
		return(-1);
E 2
I 2
		(void)fclose(fp);
		(void)fprintf(stderr, "Error reading dictionary\n");
		return (-1);
E 2
	}
	*p = '\0';
D 2
	return(0);
E 2
I 2
	return (0);
E 2
}

/*
 * Dependent on the exact format of the index file:
 * Starting offset field begins in column 1 and length field in column 9
 * Taking the easy way out, the input buffer is made "large" and a check
 * is made for lines that are too long
 */
I 2
int
E 2
loadindex(indexfile)
D 2
char *indexfile;
E 2
I 2
	char *indexfile;
E 2
{
D 2
    register int i, j;
    char buf[BUFSIZ];
    FILE *fp;
E 2
I 2
	register int i, j;
	char buf[BUFSIZ];
	FILE *fp;
E 2
	extern struct dictindex dictindex[];
 
D 2
    if ((fp = fopen(indexfile, "r")) == (FILE *) NULL) {
        (void) fprintf(stderr, "Can't open '%s'\n", indexfile);
        return(-1);
    }
    i = 0;
    while (fgets(buf, sizeof(buf), fp) != (char *) NULL) {
		if (index(buf, '\n') == (char *) NULL) {
			(void) fprintf(stderr, "A line in the index file is too long\n");
E 2
I 2
	if ((fp = fopen(indexfile, "r")) == NULL) {
		(void) fprintf(stderr, "Can't open '%s'\n", indexfile);
		return (-1);
	}
	i = 0;
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		if (strchr(buf, '\n') == NULL) {
			(void)fprintf(stderr,
				"A line in the index file is too long\n");
E 2
			return(-1);
		}
D 2
        j = *buf - 'a';
        if (i != j) {
            (void) fprintf(stderr, "Bad index order\n");
            return(-1);
        }
        dictindex[j].start = atol(buf + 1);
        dictindex[j].length = atol(buf + 9) - dictindex[j].start;
        i++;
    }
    if (i != 26) {
        (void) fprintf(stderr, "Bad index length\n");
        return(-1);
    }
    (void) fclose(fp);
E 2
I 2
		j = *buf - 'a';
		if (i != j) {
		    (void) fprintf(stderr, "Bad index order\n");
		    return(-1);
		}
		dictindex[j].start = atol(buf + 1);
		dictindex[j].length = atol(buf + 9) - dictindex[j].start;
		i++;
	}
	if (i != 26) {
		(void) fprintf(stderr, "Bad index length\n");
		return(-1);
	}
	(void) fclose(fp);
E 2
	return(0);
} 
D 2
 
E 2
E 1
