h14450
s 00002/00000/00101
d D 8.2 95/05/04 15:39:08 bostic 5 4
c optarg/optind moved to unistd.h
e
s 00002/00002/00099
d D 8.1 93/06/06 14:50:05 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00013/00091
d D 5.3 92/07/14 14:30:35 bostic 3 2
c fix for quads; prototype and cleanup in general
e
s 00003/00003/00101
d D 5.2 90/05/08 10:35:46 bostic 2 1
c right justify the default outputs so multiple types line up
e
s 00104/00000/00000
d D 5.1 90/05/08 08:59:07 bostic 1 0
c date and time created 90/05/08 08:59:07 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 3

E 3
#include <stdio.h>
I 3
#include <stdlib.h>
#include <string.h>
I 5
#include <unistd.h>

E 5
E 3
#include "hexdump.h"

off_t skip;				/* bytes to skip */

I 3
void
E 3
newsyntax(argc, argvp)
	int argc;
	char ***argvp;
{
	extern enum _vflag vflag;
	extern FS *fshead;
D 3
	extern char *optarg;
	extern int length, optind;
E 3
I 3
	extern int length;
E 3
	int ch;
	char *p, **argv;

	argv = *argvp;
	while ((ch = getopt(argc, argv, "bcde:f:n:os:vx")) != EOF)
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
D 2
			add("\"%07.7_ax \" 8/2 \"%05u \" \"\\n\"");
E 2
I 2
			add("\"%07.7_ax \" 8/2 \"  %05u \" \"\\n\"");
E 2
			break;
		case 'e':
			add(optarg);
			break;
		case 'f':
			addfile(optarg);
			break;
		case 'n':
D 3
			if ((length = atoi(optarg)) < 0) {
				(void)fprintf(stderr,
				    "hexdump: bad length value.\n");
				exit(1);
			}
E 3
I 3
			if ((length = atoi(optarg)) < 0)
				err("%s: bad length value", optarg);
E 3
			break;
		case 'o':
			add("\"%07.7_Ax\n\"");
D 2
			add("\"%07.7_ax \" 8/2 \"%06o \" \"\\n\"");
E 2
I 2
			add("\"%07.7_ax \" 8/2 \" %06o \" \"\\n\"");
E 2
			break;
		case 's':
D 3
			if ((skip = strtol(optarg, &p, 0)) < 0) {
				(void)fprintf(stderr,
				    "hexdump: bad skip value.\n");
				exit(1);
			}
E 3
I 3
			if ((skip = strtol(optarg, &p, 0)) < 0)
				err("%s: bad skip value", optarg);
E 3
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
			break;
		case 'x':
			add("\"%07.7_Ax\n\"");
D 2
			add("\"%07.7_ax \" 8/2 \"%04x \" \"\\n\"");
E 2
I 2
			add("\"%07.7_ax \" 8/2 \"   %04x \" \"\\n\"");
E 2
			break;
		case '?':
			usage();
D 3
			exit(1);
E 3
		}

	if (!fshead) {
		add("\"%07.7_Ax\n\"");
		add("\"%07.7_ax \" 8/2 \"%04x \" \"\\n\"");
	}

	*argvp += optind;
}

I 3
void
E 3
usage()
{
	(void)fprintf(stderr,
"hexdump: [-bcdovx] [-e fmt] [-f fmt_file] [-n length] [-s skip] [file ...]\n");
	exit(1);
}
E 1
