h11870
s 00002/00002/00238
d D 8.1 93/06/06 15:04:37 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00007/00239
d D 5.8 91/11/20 16:27:14 bostic 8 7
c add affiliation for Oz
e
s 00168/00107/00078
d D 5.7 91/09/03 11:38:21 bostic 7 6
c New version from Oz Yigit; BSD-ized
e
s 00007/00018/00178
d D 5.6 91/02/26 14:05:44 bostic 6 5
c ANSI fixes, use strdup(3) instead of rolling your own
e
s 00001/00011/00195
d D 5.5 90/06/01 16:09:58 bostic 5 4
c new copyright notice
e
s 00000/00008/00206
d D 5.4 89/08/28 15:28:22 bostic 4 3
c remove vms defines
e
s 00000/00035/00214
d D 5.3 89/08/28 15:18:09 bostic 3 2
c private version of memcpy
e
s 00000/00066/00249
d D 5.2 89/08/28 15:17:01 bostic 2 1
c remove private getopt(3)
e
s 00315/00000/00000
d D 5.1 89/08/28 15:14:22 bostic 1 0
c date and time created 89/08/28 15:14:22 by bostic
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
D 8
 * Ozan Yigit.
E 8
I 8
 * Ozan Yigit at York University.
E 8
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
D 8

/*
 * misc.c
 * Facility: m4 macro processor
 * by: oz
 */
E 8
D 7
 
E 7
I 7

#include <sys/types.h>
#include <errno.h>
E 7
I 6
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 6
#include "mdef.h"
D 7
#include "extr.h" 
E 7
I 7
#include "stdd.h"
#include "extern.h"
E 7
I 6
#include "pathnames.h"
E 6
D 7
 
E 7
I 7

E 7
D 6
extern char *malloc();
 
E 6
/*
D 7
 * indx - find the index of second str in the
 *        first str.
E 7
I 7
 * find the index of second str in the first str.
E 7
 */
I 7
int
E 7
indx(s1, s2)
char *s1;
char *s2;
{
D 7
        register char *t;
        register char *p;
        register char *m;
 
        for (p = s1; *p; p++) {
                for (t = p, m = s2; *m && *m == *t; m++, t++)
                        ;
                if (!*m)
                        return(p - s1);
        }
        return (-1);
E 7
I 7
	register char *t;
	register char *p;
	register char *m;

	for (p = s1; *p; p++) {
		for (t = p, m = s2; *m && *m == *t; m++, t++);
		if (!*m)
			return (p - s1);
	}
	return (-1);
E 7
}
D 7
 
E 7
/*
 *  putback - push character back onto input
D 7
 *
E 7
 */
D 7
putback (c)
E 7
I 7
void
putback(c)
E 7
char c;
{
D 7
        if (bp < endpbb)
                *bp++ = c;
        else
                error("m4: too many characters pushed back");
E 7
I 7
	if (bp < endpbb)
		*bp++ = c;
	else
		oops("too many characters pushed back");
E 7
}
D 7
 
E 7
I 7

E 7
/*
 *  pbstr - push string back onto input
 *          putback is replicated to improve
 *          performance.
D 7
 *
E 7
 */
I 7
void
E 7
pbstr(s)
register char *s;
{
D 7
        register char *es;
E 7
I 7
	register char *es;
E 7
	register char *zp;

	es = s;
	zp = bp;

D 7
        while (*es)
                es++;
        es--;
        while (es >= s)
                if (zp < endpbb)
                        *zp++ = *es--;
        if ((bp = zp) == endpbb)
                error("m4: too many characters pushed back");
E 7
I 7
	while (*es)
		es++;
	es--;
	while (es >= s)
		if (zp < endpbb)
			*zp++ = *es--;
	if ((bp = zp) == endpbb)
		oops("too many characters pushed back");
E 7
}
D 7
 
E 7
I 7

E 7
/*
 *  pbnum - convert number to string, push back on input.
D 7
 *
E 7
 */
D 7
pbnum (n)
E 7
I 7
void
pbnum(n)
E 7
int n;
{
D 7
        register int num;
 
        num = (n < 0) ? -n : n;
        do {
                putback(num % 10 + '0');
        }
        while ((num /= 10) > 0);
E 7
I 7
	register int num;
E 7

D 7
        if (n < 0) putback('-');
E 7
I 7
	num = (n < 0) ? -n : n;
	do {
		putback(num % 10 + '0');
	}
	while ((num /= 10) > 0);

	if (n < 0)
		putback('-');
E 7
}
D 7
 
E 7
I 7

E 7
/*
 *  chrsave - put single char on string space
D 7
 *
E 7
 */
D 7
chrsave (c)
E 7
I 7
void
chrsave(c)
E 7
char c;
{
D 7
/***        if (sp < 0)
                putc(c, active);
        else ***/ if (ep < endest)
                *ep++ = c;
        else
                error("m4: string space overflow");
E 7
I 7
	if (ep < endest)
		*ep++ = c;
	else
		oops("string space overflow");
E 7
}
D 7
 
E 7
I 7

E 7
/*
D 7
 * getdiv - read in a diversion file, and
 *          trash it.
E 7
I 7
 * read in a diversion file, and dispose it.
E 7
 */
D 7
getdiv(ind) {
        register int c;
        register FILE *dfil;
 
        if (active == outfile[ind])
                error("m4: undivert: diversion still active.");
        (void) fclose(outfile[ind]);
        outfile[ind] = NULL;
        m4temp[UNIQUE] = ind + '0';
        if ((dfil = fopen(m4temp, "r")) == NULL)
                error("m4: cannot undivert.");
        else
                while((c = getc(dfil)) != EOF)
                        putc(c, active);
        (void) fclose(dfil);
E 7
I 7
void
getdiv(n)
int n;
{
	register int c;
	register FILE *dfil;
E 7

I 7
	if (active == outfile[n])
		oops("%s: diversion still active.", "undivert");
	(void) fclose(outfile[n]);
	outfile[n] = NULL;
	m4temp[UNIQUE] = n + '0';
	if ((dfil = fopen(m4temp, "r")) == NULL)
		oops("%s: cannot undivert.", m4temp);
	else
		while ((c = getc(dfil)) != EOF)
			putc(c, active);
	(void) fclose(dfil);

#ifdef vms
	if (remove(m4temp))
#else
E 7
D 4
#if vms
        if (remove(m4temp))
#else
E 4
	if (unlink(m4temp) == -1)
D 4
#endif
E 4
D 7
                error("m4: cannot unlink.");
E 7
I 7
#endif
		oops("%s: cannot unlink.", m4temp);
E 7
}
D 7
 
/*
 * Very fatal error. Close all files
 * and die hard.
 */
error(s)
char *s;
E 7
I 7

void
onintr(signo)
	int signo;
E 7
{
D 7
        killdiv();
        fprintf(stderr,"%s\n",s);
        exit(1);
E 7
I 7
	oops("interrupted.");
E 7
}
D 7
 
E 7
I 7

E 7
/*
D 7
 * Interrupt handling
E 7
I 7
 * killdiv - get rid of the diversion files
E 7
 */
D 7
static char *msg = "\ninterrupted.";
 
E 7
I 6
void
E 6
D 7
onintr() {
        error(msg);
E 7
I 7
killdiv()
{
	register int n;

	for (n = 0; n < MAXOUT; n++)
		if (outfile[n] != NULL) {
			(void) fclose(outfile[n]);
			m4temp[UNIQUE] = n + '0';
#ifdef vms
			(void) remove(m4temp);
#else
			(void) unlink(m4temp);
#endif
		}
E 7
}
D 7
 
/*
 * killdiv - get rid of the diversion files
 *
 */
killdiv() {
        register int n;
 
        for (n = 0; n < MAXOUT; n++)
                if (outfile[n] != NULL) {
                        (void) fclose (outfile[n]);
                        m4temp[UNIQUE] = n + '0';
D 4
#if vms
			(void) remove (m4temp);
#else
E 4
                        (void) unlink (m4temp);
D 4
#endif
E 4
                }
E 7
I 7

char *
xalloc(n)
unsigned long n;
{
	register char *p = malloc(n);

	if (p == NULL)
		oops("malloc: %s", strerror(errno));
	return p;
}

char *
xstrdup(s)
const char *s;
{
	register char *p = strdup(s);
	if (p == NULL)
		oops("strdup: %s", strerror(errno));
	return p;
E 7
}
D 7
 
D 6
/*
 * save a string somewhere..
 *
 */
char *strsave(s)
char *s;
{
	register int n;
        char *p;

        if ((p = malloc (n = strlen(s)+1)) != NULL)
                (void) memcpy(p, s, n);
        return (p);
}
 
E 6
usage() {
D 6
        fprintf(stderr, "Usage: m4 [-Dname[=val]] [-Uname]\n");
E 6
I 6
        fprintf(stderr, "usage: m4 [-Dname[=val]] [-Uname]\n");
E 6
        exit(1);
E 7
I 7

char *
basename(s)
register char *s;
{
	register char *p;
	extern char *strrchr();

	if ((p = strrchr(s, '/')) == NULL)
		return s;

	return ++p;
}

void
usage()
{
	fprintf(stderr, "usage: m4 [-Dname[=val]] [-Uname]\n");
	exit(1);
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
oops(const char *fmt, ...)
#else
oops(fmt, va_alist)
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
	(void)fprintf(stderr, "%s: ", progname);
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 7
}
D 3

D 2
#ifdef GETOPT
/*
 * H. Spencer getopt - get option letter from argv
 * 
 *
#include <stdio.h>
 *
 */

char	*optarg;	/* Global argument pointer. */
int	optind = 0;	/* Global argv index. */

static char	*scan = NULL;	/* Private scan pointer. */

extern char	*index();

int
getopt(argc, argv, optstring)
int argc;
char *argv[];
char *optstring;
{
	register char c;
	register char *place;

	optarg = NULL;

	if (scan == NULL || *scan == '\0') {
		if (optind == 0)
			optind++;
	
		if (optind >= argc || argv[optind][0] != '-' || argv[optind][1] == '\0')
			return(EOF);
		if (strcmp(argv[optind], "--")==0) {
			optind++;
			return(EOF);
		}
	
		scan = argv[optind]+1;
		optind++;
	}

	c = *scan++;
	place = index(optstring, c);

	if (place == NULL || c == ':') {
		fprintf(stderr, "%s: unknown option -%c\n", argv[0], c);
		return('?');
	}

	place++;
	if (*place == ':') {
		if (*scan != '\0') {
			optarg = scan;
			scan = NULL;
		} else {
			optarg = argv[optind];
			optind++;
		}
	}

	return(c);
}
   
#endif

E 2
#ifdef DUFFCP
/*
 * This code uses Duff's Device (tm Tom Duff)
 * to unroll the copying loop:
 * while (count-- > 0)
 *	*to++ = *from++;
 */

#define COPYBYTE 	*to++ = *from++

memcpy(to, from, count)
register char *from, *to;
register int count;
{
	if (count > 0) {
		register int loops = (count+8-1) >> 3;	/* div 8 round up */

		switch (count&(8-1)) {			/* mod 8 */
		case 0: do {
			COPYBYTE;
		case 7:	COPYBYTE;
		case 6:	COPYBYTE;
		case 5:	COPYBYTE;
		case 4:	COPYBYTE;
		case 3:	COPYBYTE;
		case 2:	COPYBYTE;
		case 1:	COPYBYTE;
			} while (--loops > 0);
		}

	}
}

#endif
E 3
E 1
