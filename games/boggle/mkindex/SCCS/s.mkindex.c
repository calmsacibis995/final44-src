h18439
s 00005/00005/00089
d D 8.1 93/06/11 14:51:05 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00037/00017/00057
d D 5.2 93/06/11 14:51:01 bostic 2 1
c integrate into 4.4BDS
e
s 00074/00000/00000
d D 5.1 93/06/10 11:09:49 bostic 1 0
c date and time created 93/06/10 11:09:49 by bostic
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

I 2
#ifndef lint
D 3
char copyright[] =
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 3
I 3
static char copyright[] =
"%Z% Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 3
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
#include <stdio.h>

#include "bog.h"

I 2
char *nextword __P((FILE *, char *, int *, int *));

int
E 2
main(argc, argv)
D 2
int argc;
char **argv;
E 2
I 2
	int argc;
	char *argv[];
E 2
{
	int clen, rlen, prev;
	long off, start;
D 2
	char buf[MAXWORDLEN + 1], *p, *nextword();
E 2
I 2
	char buf[MAXWORDLEN + 1];
E 2

	prev = '\0';
	off = start = 0L;
D 2
	while (nextword(stdin, buf, &clen, &rlen) != (char *) NULL) {
E 2
I 2
	while (nextword(stdin, buf, &clen, &rlen) != NULL) {
E 2
		if (*buf != prev) {
			if (prev != '\0')
				printf("%c %6ld %6ld\n", prev, start, off - 1);
			prev = *buf;
			start = off;
		}
		off += clen + 1;
	}
	printf("%c %6ld %6ld\n", prev, start, off - 1);
	exit(0);
}

/*
 * Return the next word in the compressed dictionary in 'buffer' or
 * NULL on end-of-file
 * Also set clen to the length of the compressed word (for mkindex) and
 * rlen to the strlen() of the real word
 */
char *
nextword(fp, buffer, clen, rlen)
D 2
FILE *fp;
char *buffer;
int *clen, *rlen;
E 2
I 2
	FILE *fp;
	char *buffer;
	int *clen, *rlen;
E 2
{
D 2
    register int ch, pcount;
E 2
I 2
	register int ch, pcount;
E 2
	register char *p, *q;
	static char buf[MAXWORDLEN + 1];
	static int first = 1;
	static int lastch = 0;

   	if (first) {
D 2
        if ((pcount = getc(fp)) == EOF)
			return((char *) NULL);
E 2
I 2
		if ((pcount = getc(fp)) == EOF)
			return (NULL);
E 2
		first = 0;
	}
	else if ((pcount = lastch) == EOF)
D 2
		return((char *) NULL);
E 2
I 2
		return (NULL);
E 2

	p = buf + (*clen = pcount);
 
D 2
    while ((ch = getc(fp)) != EOF && ch >= 'a')
E 2
I 2
	while ((ch = getc(fp)) != EOF && ch >= 'a')
E 2
			*p++ = ch;
D 2
	    lastch = ch;
    *p = '\0';
E 2
I 2
		lastch = ch;
	*p = '\0';
E 2

	*rlen = (int) (p - buf);
	*clen = *rlen - *clen;

	p = buf;
	q = buffer;
	while ((*q++ = *p) != '\0') {
		if (*p++ == 'q')
			*q++ = 'u';
	}
D 2
    return(buffer);
E 2
I 2
	return (buffer);
E 2
}
D 2
 
E 2
E 1
