h02511
s 00005/00005/00116
d D 8.1 93/06/06 16:46:19 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00013/00119
d D 5.1 90/06/01 17:52:50 bostic 2 1
c fix copyright notices, clean up man page
e
s 00132/00000/00000
d D 1.1 90/05/23 16:38:23 marc 1 0
c date and time created 90/05/23 16:38:23 by marc
e
u
U
t
T
I 1
D 2
/*
E 2
I 2
/*-
E 2
D 3
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
D 2
 * Redistribution and use in source and binary forms is permitted
 * provided that all copyright information, including this notice,
 * is retained in all such forms, and that any documentation,
 * advertising or other materials related to such distribution and
 * use acknowledge that the software was
 * developed by the University of California, Berkeley.  The name
 * of the University may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
D 3
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 3
I 3
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 3
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <stdio.h>
#include <vis.h>

char	*Program;
#define usage()	fprintf(stderr, "usage: %s %s\n", Program, USAGE)
#define USAGE "[file...]"

main(argc, argv)
	char *argv[];
{
	FILE *fp;
	extern char *optarg;
	extern int optind;
	int ch;

	Program = argv[0];
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch((char)ch) {
		case '?':
		default:
			usage();
			exit(1);
		}
	argc -= optind;
	argv += optind;

	if (*argv)
		while (*argv) {
			if ((fp=fopen(*argv, "r")) != NULL)
				process(fp, *argv);
			else
				syserror("%s", *argv);
			argv++;
		}
	else
		process(stdin, "<stdin>");
	exit(0);
}

process(fp, filename)
	FILE *fp;
	char *filename;
{
	register int offset = 0, c, ret;
	int state = 0;
	char outc;

	while ((c = getc(fp)) != EOF) {
		offset++;
	again:
		switch(ret = unvis(&outc, (char)c, &state, 0)) {
		case UNVIS_VALID:
			putchar(outc);
			break;
		case UNVIS_VALIDPUSH:
			putchar(outc);
			goto again;
		case UNVIS_SYNBAD:
			error("%s: offset: %d: can't decode", filename, offset);
			state = 0;
			break;
		case 0:
		case UNVIS_NOCHAR:
			break;
		default:
			error("bad return value (%d), can't happen", ret);
			exit(1);
		}
	}
	if (unvis(&outc, (char)0, &state, UNVIS_END) == UNVIS_VALID)
		putchar(outc);
}

#include <varargs.h>

error(va_alist)
	va_dcl
{
	char *fmt;
	va_list ap;
	extern errno;

	fprintf(stderr, "%s: ", Program);
	va_start(ap);
	fmt = va_arg(ap, char *);
	(void) vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
}

syserror(va_alist)
	va_dcl
{
	char *fmt;
	va_list ap;
	extern errno;

	fprintf(stderr, "%s: ", Program);
	va_start(ap);
	fmt = va_arg(ap, char *);
	(void) vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, ": %s\n", strerror(errno));
}
E 1
