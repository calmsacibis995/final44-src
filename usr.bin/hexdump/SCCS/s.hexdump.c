h12034
s 00005/00005/00081
d D 8.1 93/06/06 14:49:58 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00003/00050
d D 5.6 92/07/14 14:30:33 bostic 6 5
c fix for quads; prototype and cleanup in general
e
s 00001/00011/00052
d D 5.5 90/06/01 16:52:34 bostic 5 4
c new copyright notice
e
s 00006/00088/00057
d D 5.4 90/05/08 08:58:38 bostic 4 3
c break out arg parsing into od and hexdump modules
e
s 00002/00002/00143
d D 5.3 90/05/07 21:07:52 bostic 3 2
c fix bug so doesn't match first line in file of all NULL's
e
s 00005/00001/00140
d D 5.2 90/05/01 10:28:41 bostic 2 1
c add -x flag to specify hex output (default)
e
s 00141/00000/00000
d D 5.1 89/08/29 18:36:21 bostic 1 0
c date and time created 89/08/29 18:36:21 by bostic
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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
D 7
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 7
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 6

#include <errno.h>
#include <stdlib.h>
E 6
#include <stdio.h>
I 6
#include <string.h>
E 6
#include "hexdump.h"

D 3
enum _vflag vflag = WAIT;		/* display duplicate lines */
E 3
I 3
D 4
enum _vflag vflag = FIRST;		/* display duplicate lines */
E 4
E 3
FS *fshead;				/* head of format strings */
D 4
off_t skip;				/* bytes to skip */
E 4
int blocksize;				/* data block size */
int exitval;				/* final exit value */
D 4
int length;				/* max bytes to read */
E 4
I 4
int length = -1;			/* max bytes to read */
E 4

I 6
int
E 6
main(argc, argv)
	int argc;
D 6
	char **argv;
E 6
I 6
	char *argv[];
E 6
{
D 4
	extern int errno, optind;
	extern char *optarg;
E 4
I 4
D 6
	extern int errno;
E 6
E 4
	register FS *tfs;
D 4
	int ch;
E 4
D 6
	char *p, *rindex();
E 6
I 6
	char *p;
E 6

D 4
	length = -1;
D 2
	while ((ch = getopt(argc, argv, "bcde:f:n:os:v")) != EOF)
E 2
I 2
	while ((ch = getopt(argc, argv, "bcde:f:n:os:vx")) != EOF)
E 2
		switch (ch) {
		case 'b':
			add("\"%07.7_Ax\n\"");
			add("\"%07.7_ax \" 16/1 \"%03o \" \"\\n\"");
			break;
		case 'c':
			add("\"%07.7_Ax\n\"");
			add("\"%07.7_ax \" 16/1 \"%3_c \" \"\\n\"");
			break;
		case 'd':
			add("\"%07.7_Ax\n\"");
			add("\"%07.7_ax \" 8/2 \"%05u \" \"\\n\"");
			break;
		case 'e':
			add(optarg);
			break;
		case 'f':
			addfile(optarg);
			break;
		case 'n':
			if ((length = atoi(optarg)) < 0) {
				(void)fprintf(stderr,
				    "hexdump: bad length value.\n");
				exit(1);
			}
			break;
		case 'o':
			add("\"%07.7_Ax\n\"");
			add("\"%07.7_ax \" 8/2 \"%06o \" \"\\n\"");
			break;
		case 's':
			if ((skip = strtol(optarg, &p, 0)) < 0) {
				(void)fprintf(stderr,
				    "hexdump: bad skip value.\n");
				exit(1);
			}
			switch(*p) {
			case 'b':
				skip *= 512;
				break;
			case 'k':
				skip *= 1024;
				break;
			case 'm':
				skip *= 1048576;
				break;
			}
			break;
		case 'v':
			vflag = ALL;
I 2
			break;
		case 'x':
			add("\"%07.7_Ax\n\"");
			add("\"%07.7_ax \" 8/2 \"%04x \" \"\\n\"");
E 2
			break;
		case '?':
			usage();
			exit(1);
		}
E 4
I 4
	if (!(p = rindex(argv[0], 'o')) || strcmp(p, "od"))
		newsyntax(argc, &argv);
	else
		oldsyntax(argc, &argv);
E 4

D 4
	if (!fshead) {
		p = rindex(argv[0], 'o');
		if (p && !strcmp(p, "od")) {
			add("\"%07.7_Ao\n\"");
			add("\"%07.7_ao  \" 8/2 \"%06o \" \"\\n\"");
		} else {
			add("\"%07.7_Ax\n\"");
			add("\"%07.7_ax \" 8/2 \"%04x \" \"\\n\"");
		}
	}

	argv += optind;
	argc -= optind;

E 4
	/* figure out the data block size */
	for (blocksize = 0, tfs = fshead; tfs; tfs = tfs->nextfs) {
		tfs->bcnt = size(tfs);
		if (blocksize < tfs->bcnt)
			blocksize = tfs->bcnt;
	}
	/* rewrite the rules, do syntax checking */
	for (tfs = fshead; tfs; tfs = tfs->nextfs)
		rewrite(tfs);

	(void)next(argv);
	display();
	exit(exitval);
I 6
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
	(void)fprintf(stderr, "hexdump: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 6
D 4
}

usage()
{
	(void)fprintf(stderr,
D 3
"hexdump: [bcdov] [-e format] [-f file] [-n length] [-s skip] [file ...]\n");
E 3
I 3
"hexdump: [-bcdovx] [-e format] [-f file] [-n length] [-s skip] [file ...]\n");
E 3
	exit(1);
E 4
}
E 1
