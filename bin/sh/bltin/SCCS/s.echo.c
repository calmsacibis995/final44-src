h13736
s 00005/00001/00077
d D 8.2 95/05/04 18:03:56 christos 4 3
c misc cleanup
e
s 00002/00002/00076
d D 8.1 93/05/31 15:15:36 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00041/00063/00037
d D 5.2 91/03/13 19:49:31 marc 2 1
c wrong source
e
s 00100/00000/00000
d D 5.1 91/03/07 20:22:39 bostic 1 0
c date and time created 91/03/07 20:22:39 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Echo command.
 */

#define main echocmd

#include "bltin.h"

D 2
#define EOF (-1)
E 2
I 2
/* #define eflag 1 */
E 2

D 2
main(argc, argv)  
	char **argv; 
{
E 2
I 2
D 4
main(argc, argv)  char **argv; {
E 4
I 4
int
main(argc, argv)
	int argc;
	char **argv;
{
E 4
	register char **ap;
E 2
	register char *p;
	register char c;
	int count;
	int nflag = 0;
I 2
#ifndef eflag
E 2
	int eflag = 0;
D 2
	extern char *optarg;
	extern int optind, opterr;
	int ch;
E 2
I 2
#endif
E 2

D 2
	opterr = 0;
	while ((ch = getopt(argc, argv, "ne")) != EOF)
		switch((char)ch) {
		case 'n':
E 2
I 2
	ap = argv;
	if (argc)
		ap++;
	if ((p = *ap) != NULL) {
		if (equal(p, "-n")) {
E 2
			nflag++;
D 2
			break;
		case 'e':
E 2
I 2
			ap++;
		} else if (equal(p, "-e")) {
#ifndef eflag
E 2
			eflag++;
D 2
			break;
		case '?':
		default:
			error("usage: %s [-ne] [arg]...", *argv);
			return 0;
E 2
I 2
#endif
			ap++;
E 2
		}
D 2
	argc -= optind;
	argv += optind;

	if (!eflag) {
		while (p = *argv++) {
			while (*p) {
				putchar(*p);
				p++;
			}
			if (*argv) putchar(' ');
		}
	} else {
		while (p = *argv++) {
			while (c = *p++) {
				if (c == '\\') {
					switch (*p++) {
					case 'b':  c = '\b';  break;
					case 'c':  return 0;	/* exit */
					case 'f':  c = '\f';  break;
					case 'n':  c = '\n';  break;
					case 'r':  c = '\r';  break;
					case 't':  c = '\t';  break;
					case 'v':  c = '\v';  break;
					case '\\':  break;	/* c = '\\' */
					case '0':	/* should be [0-7] */
					      c = 0;
					      count = 3;
					      while (--count >= 0 && (unsigned)(*p - '0') < 8)
						    c = (c << 3) + (*p++ - '0');
					      break;
					default:
						p--;
					      break;
					}
E 2
I 2
	}
	while ((p = *ap++) != NULL) {
		while ((c = *p++) != '\0') {
			if (c == '\\' && eflag) {
				switch (*p++) {
				case 'b':  c = '\b';  break;
				case 'c':  return 0;		/* exit */
				case 'f':  c = '\f';  break;
				case 'n':  c = '\n';  break;
				case 'r':  c = '\r';  break;
				case 't':  c = '\t';  break;
				case 'v':  c = '\v';  break;
				case '\\':  break;		/* c = '\\' */
				case '0':
					c = 0;
					count = 3;
					while (--count >= 0 && (unsigned)(*p - '0') < 8)
						c = (c << 3) + (*p++ - '0');
					break;
				default:
					p--;
					break;
E 2
				}
D 2
				putchar(c);
E 2
			}
D 2
			if (*argv) putchar(' ');
E 2
I 2
			putchar(c);
E 2
		}
I 2
		if (*ap)
			putchar(' ');
E 2
	}
D 2
	if (!nflag)
E 2
I 2
	if (! nflag)
E 2
		putchar('\n');
	return 0;
}
D 2

#ifndef SHELL
void
error(f, a)
{
	_doprnt(f, &a, stderr);
}
#endif
E 2
E 1
