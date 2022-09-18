h58809
s 00005/00005/00165
d D 8.1 93/06/06 14:59:41 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00002/00165
d D 5.5 93/03/22 06:12:22 bostic 5 4
c lint for GCC 2
e
s 00002/00000/00165
d D 5.4 92/06/29 14:46:02 bostic 4 3
c new include file, fnmatch.h
e
s 00001/00001/00164
d D 5.3 92/06/29 13:41:29 bostic 3 2
c FNM_QUOTE is the default now, flip the return sense of fnmatch
e
s 00001/00011/00164
d D 5.2 90/06/01 16:55:32 bostic 2 1
c new copyright notice
e
s 00175/00000/00000
d D 5.1 90/03/06 11:20:06 bostic 1 0
c date and time created 90/03/06 11:20:06 by bostic
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * James A. Woods.
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
D 6
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Ref: Usenix ;login:, Vol 8, No 1, February/March, 1983, p. 8.
 *
 * Locate scans a file list for the full pathname of a file given only part
 * of the name.  The list has been processed with with "front-compression"
 * and bigram coding.  Front compression reduces space by a factor of 4-5,
 * bigram coding by a further 20-25%.
 *
 * The codes are:
 * 
 * 	0-28	likeliest differential counts + offset to make nonnegative
 *	30	switch code for out-of-range count to follow in next word
 *	128-255 bigram codes (128 most common, as determined by 'updatedb')
 *	32-127  single character (printable) ascii residue (ie, literal)
 * 
 * A novel two-tiered string search technique is employed:
 * 
 * First, a metacharacter-free subpattern and partial pathname is matched
 * BACKWARDS to avoid full expansion of the pathname list.  The time savings
 * is 40-50% over forward matching, which cannot efficiently handle
 * overlapped search patterns and compressed path residue.
 * 
 * Then, the actual shell glob-style regular expression (if in this form) is
 * matched against the candidate pathnames using the slower routines provided
 * in the standard 'find'.
 */

#include <sys/param.h>
I 4

#include <fnmatch.h>
E 4
#include <unistd.h>
#include <stdio.h>
I 5
#include <string.h>

E 5
#include "locate.h"
#include "pathnames.h"

FILE *fp;

I 5
int
E 5
main(argc, argv)
	int argc;
D 5
	char **argv;
E 5
I 5
	char *argv[];
E 5
{
	if (argc != 2) {
		(void)fprintf(stderr, "usage: locate pattern\n");
		exit(1);
	}
	if (!(fp = fopen(_PATH_FCODES, "r"))) {
		(void)fprintf(stderr, "locate: no database file %s.\n",
		    _PATH_FCODES);
		exit(1);
	}
	while (*++argv)
		fastfind(*argv);
	exit(0);
}

fastfind(pathpart)
	char *pathpart;
{
	register char *p, *s;
	register int c;
	int count, found, globflag;
D 5
	char *cutoff, *patend, *q, *index(), *patprep();
E 5
I 5
	char *cutoff, *patend, *q, *patprep();
E 5
	char bigram1[NBG], bigram2[NBG], path[MAXPATHLEN];

	for (c = 0, p = bigram1, s = bigram2; c < NBG; c++)
		p[c] = getc(fp), s[c] = getc(fp);

	p = pathpart;
	globflag = index(p, '*') || index(p, '?') || index(p, '[');
	patend = patprep(p);

	found = 0;
	for (c = getc(fp), count = 0; c != EOF;) {
		count += ((c == SWITCH) ? getw(fp) : c) - OFFSET;
		/* overlay old path */
		for (p = path + count; (c = getc(fp)) > SWITCH;)
			if (c < PARITY)
				*p++ = c;
			else {		/* bigrams are parity-marked */
				c &= PARITY - 1;
				*p++ = bigram1[c], *p++ = bigram2[c];
			}
		*p-- = NULL;
		cutoff = (found ? path : path + count);
		for (found = 0, s = p; s >= cutoff; s--)
			if (*s == *patend) {	/* fast first char check */
				for (p = patend - 1, q = s - 1; *p != NULL;
				    p--, q--)
					if (*q != *p)
						break;
				if (*p == NULL) {	/* fast match success */
					found = 1;
					if (!globflag ||
D 3
					    fnmatch(pathpart, path, FNM_QUOTE))
E 3
I 3
					    !fnmatch(pathpart, path, 0))
E 3
						(void)printf("%s\n", path);
					break;
				}
			}
	}
}

/*
 * extract last glob-free subpattern in name for fast pre-match; prepend
 * '\0' for backwards match; return end of new pattern
 */
static char globfree[100];

char *
patprep(name)
	char *name;
{
	register char *endmark, *p, *subp;

	subp = globfree;
	*subp++ = '\0';
	p = name + strlen(name) - 1;
	/* skip trailing metacharacters (and [] ranges) */
	for (; p >= name; p--)
		if (index("*?", *p) == 0)
			break;
	if (p < name)
		p = name;
	if (*p == ']')
		for (p--; p >= name; p--)
			if (*p == '[') {
				p--;
				break;
			}
	if (p < name)
		p = name;
	/*
	 * if pattern has only metacharacters, check every path (force '/'
	 * search)
	 */
	if ((p == name) && index("?*[]", *p) != 0)
		*subp++ = '/';
	else {
		for (endmark = p; p >= name; p--)
			if (index("]*?", *p) != 0)
				break;
		for (++p;
		    (p <= endmark) && subp < (globfree + sizeof(globfree));)
			*subp++ = *p++;
	}
	*subp = '\0';
	return(--subp);
}
E 1
