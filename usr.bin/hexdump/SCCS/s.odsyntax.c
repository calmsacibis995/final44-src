h47059
s 00004/00002/00235
d D 8.2 95/05/04 15:39:54 bostic 9 8
c optarg/optind moved to unistd.h
e
s 00002/00002/00235
d D 8.1 93/06/06 14:50:10 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00003/00230
d D 5.7 92/07/14 14:30:36 bostic 7 6
c fix for quads; prototype and cleanup in general
e
s 00031/00025/00202
d D 5.6 92/03/02 15:22:19 bostic 6 5
c make 'od file +3' work right
e
s 00006/00008/00221
d D 5.5 92/01/08 08:33:06 bostic 5 4
c is isxdigit(3), don't roll out own; don't call offset code if no
c more arguments left
e
s 00028/00067/00201
d D 5.4 91/03/08 07:01:31 bostic 4 3
c don't duplicate all of the preceding strings for each flag
e
s 00099/00000/00169
d D 5.3 90/09/06 19:24:46 bostic 3 2
c add the +offset syntax for od(1) compatibility
e
s 00080/00027/00089
d D 5.2 90/05/25 15:46:26 bostic 2 1
c don't print address except for first format, make outputs right justify
e
s 00116/00000/00000
d D 5.1 90/05/08 08:59:10 bostic 1 0
c date and time created 90/05/08 08:59:10 by bostic
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 7

E 7
I 3
D 9
#include <stdlib.h>
E 3
#include <stdio.h>
E 9
I 7
#include <ctype.h>
I 9
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

E 9
E 7
#include "hexdump.h"

int deprecated;

I 7
static void odoffset __P((int, char ***));
static void odprecede __P((void));

void
E 7
oldsyntax(argc, argvp)
	int argc;
	char ***argvp;
{
	extern enum _vflag vflag;
	extern FS *fshead;
D 7
	extern char *optarg;
	extern int length, optind;
E 7
D 2
	int ch;
E 2
I 2
D 4
	int ch, first;
E 4
I 4
	int ch;
E 4
E 2
	char **argv;
I 4
D 7
	static void odprecede();
E 7
E 4

	deprecated = 1;
I 2
D 4
	first = 0;
E 4
E 2
	argv = *argvp;
	while ((ch = getopt(argc, argv, "aBbcDdeFfHhIiLlOoPpswvXx")) != EOF)
		switch (ch) {
		case 'a':
D 2
			add("\"%07.7_Ao\n\"");
			add("\"%07.7_ao  \" 16/1 \"%3_u \" \"\\n\"");
E 2
I 2
D 4
			if (!first++) {
				add("\"%07.7_Ao\n\"");
				add("\"%07.7_ao  \"");
			} else
				add("\"         \"");
E 4
I 4
			odprecede();
E 4
			add("16/1 \"%3_u \" \"\\n\"");
E 2
			break;
		case 'B':
		case 'o':
D 2
			add("\"%07.7_Ao\n\"");
			add("\"%07.7_ao  \" 8/2 \"%06o \" \"\\n\"");
E 2
I 2
D 4
			if (!first++) {
				add("\"%07.7_Ao\n\"");
				add("\"%07.7_ao  \"");
			} else
				add("\"         \"");
E 4
I 4
			odprecede();
E 4
			add("8/2 \" %06o \" \"\\n\"");
E 2
			break;
		case 'b':
D 2
			add("\"%07.7_Ao\n\"");
			add("\"%07.7_ao  \" 16/1 \"%03o \" \"\\n\"");
E 2
I 2
D 4
			if (!first++) {
				add("\"%07.7_Ao\n\"");
				add("\"%07.7_ao  \"");
			} else
				add("\"         \"");
E 4
I 4
			odprecede();
E 4
			add("16/1 \"%03o \" \"\\n\"");
E 2
			break;
		case 'c':
D 2
			add("\"%07.7_Ao\n\"");
			add("\"%07.7_ao  \" 16/1 \"%3_c \" \"\\n\"");
E 2
I 2
D 4
			if (!first++) {
				add("\"%07.7_Ao\n\"");
				add("\"%07.7_ao  \"");
			} else
				add("\"         \"");
E 4
I 4
			odprecede();
E 4
			add("16/1 \"%3_c \" \"\\n\"");
E 2
			break;
		case 'd':
D 2
			add("\"%07.7_Ao\n\"");
			add("\"%07.7_ao  \" 8/2 \"%05u \" \"\\n\"");
E 2
I 2
D 4
			if (!first++) {
				add("\"%07.7_Ao\n\"");
				add("\"%07.7_ao  \"");
			} else
				add("\"         \"");
E 4
I 4
			odprecede();
E 4
			add("8/2 \"  %05u \" \"\\n\"");
E 2
			break;
		case 'D':
D 2
			add("\"%07.7_Ao\n\"");
			add("\"%07.7_ao  \" 4/4 \"%010u \" \"\\n\"");
E 2
I 2
D 4
			if (!first++) {
				add("\"%07.7_Ao\n\"");
				add("\"%07.7_ao  \"");
			} else
				add("\"         \"");
E 4
I 4
			odprecede();
E 4
			add("4/4 \"     %010u \" \"\\n\"");
E 2
			break;
		case 'e':		/* undocumented in od */
		case 'F':
D 2
			add("\"%07.7_Ao\n\"");
			add("\"%07.7_ao  \" 2/8 \"%21.14e \" \"\\n\"");
E 2
I 2
D 4
			if (!first++) {
				add("\"%07.7_Ao\n\"");
				add("\"%07.7_ao  \"");
			} else
				add("\"         \"");
E 4
I 4
			odprecede();
E 4
			add("2/8 \"          %21.14e \" \"\\n\"");
E 2
			break;
			
		case 'f':
D 2
			add("\"%07.7_Ao\n\"");
			add("\"%07.7_ao  \" 4/4 \"%14.7e \" \"\\n\"");
E 2
I 2
D 4
			if (!first++) {
				add("\"%07.7_Ao\n\"");
				add("\"%07.7_ao  \"");
			} else
				add("\"         \"");
E 4
I 4
			odprecede();
E 4
			add("4/4 \" %14.7e \" \"\\n\"");
E 2
			break;
		case 'H':
		case 'X':
D 2
			add("\"%07.7_Ao\n\"");
			add("\"%07.7_ao  \" 4/4 \"%08x \" \"\\n\"");
E 2
I 2
D 4
			if (!first++) {
				add("\"%07.7_Ao\n\"");
				add("\"%07.7_ao  \"");
			} else
				add("\"         \"");
E 4
I 4
			odprecede();
E 4
			add("4/4 \"       %08x \" \"\\n\"");
E 2
			break;
		case 'h':
		case 'x':
D 2
			add("\"%07.7_Ao\n\"");
			add("\"%07.7_ao  \" 8/2 \"%04x \" \"\\n\"");
E 2
I 2
D 4
			if (!first++) {
				add("\"%07.7_Ao\n\"");
				add("\"%07.7_ao  \"");
			} else
				add("\"         \"");
E 4
I 4
			odprecede();
E 4
			add("8/2 \"   %04x \" \"\\n\"");
E 2
			break;
		case 'I':
		case 'L':
		case 'l':
D 2
			add("\"%07.7_Ao\n\"");
			add("\"%07.7_ao  \" 4/4 \"%11d \" \"\\n\"");
E 2
I 2
D 4
			if (!first++) {
				add("\"%07.7_Ao\n\"");
				add("\"%07.7_ao  \"");
			} else
				add("\"         \"");
E 4
I 4
			odprecede();
E 4
			add("4/4 \"    %11d \" \"\\n\"");
E 2
			break;
		case 'i':
D 2
			add("\"%07.7_Ao\n\"");
			add("\"%07.7_ao  \" 8/2 \"%6d \" \"\\n\"");
E 2
I 2
D 4
			if (!first++) {
				add("\"%07.7_Ao\n\"");
				add("\"%07.7_ao  \"");
			} else
				add("\"         \"");
E 4
I 4
			odprecede();
E 4
			add("8/2 \" %6d \" \"\\n\"");
E 2
			break;
		case 'O':
D 2
			add("\"%07.7_Ao\n\"");
			add("\"%07.7_ao  \" 4/4 \"%011o \" \"\\n\"");
E 2
I 2
D 4
			if (!first++) {
				add("\"%07.7_Ao\n\"");
				add("\"%07.7_ao  \"");
			} else
				add("\"         \"");
E 4
I 4
			odprecede();
E 4
			add("4/4 \"    %011o \" \"\\n\"");
E 2
			break;
		case 'v':
			vflag = ALL;
			break;
		case 'P':
		case 'p':
		case 's':
		case 'w':
		case '?':
		default:
			(void)fprintf(stderr,
			    "od: od(1) has been deprecated for hexdump(1).\n");
			if (ch != '?')
				(void)fprintf(stderr,
"od: hexdump(1) compatibility doesn't support the -%c option%s\n",
				    ch, ch == 's' ? "; see strings(1)." : ".");
			usage();
		}

	if (!fshead) {
		add("\"%07.7_Ao\n\"");
		add("\"%07.7_ao  \" 8/2 \"%06o \" \"\\n\"");
	}

I 3
	argc -= optind;
E 3
	*argvp += optind;
I 3

D 5
	odoffset(argc, argvp);
E 5
I 5
	if (argc)
		odoffset(argc, argvp);
E 5
}

I 7
static void
E 7
D 5
#define	ishexdigit(c) \
	(c >= '0' && c <= '9' || c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F')

E 5
odoffset(argc, argvp)
	int argc;
	char ***argvp;
{
	extern off_t skip;
	register char *num, *p;
	int base;
	char *end;

	/*
	 * The offset syntax of od(1) was genuinely bizarre.  First, if
	 * it started with a plus it had to be an offset.  Otherwise, if
	 * there were at least two arguments, a number or lower-case 'x'
	 * followed by a number makes it an offset.  By default it was
	 * octal; if it started with 'x' or '0x' it was hex.  If it ended
	 * in a '.', it was decimal.  If a 'b' or 'B' was appended, it
	 * multiplied the number by 512 or 1024 byte units.  There was
	 * no way to assign a block count to a hex offset.
	 *
D 5
	 * We assumes it's a file if the offset is bad.
E 5
I 5
	 * We assume it's a file if the offset is bad.
E 5
	 */
D 6
	p = **argvp;
E 6
I 6
	p = argc == 1 ? (*argvp)[0] : (*argvp)[1];

E 6
	if (*p != '+' && (argc < 2 ||
D 5
	    (!isdigit(p[0]) && (p[0] != 'x' || !ishexdigit(p[1])))))
E 5
I 5
	    (!isdigit(p[0]) && (p[0] != 'x' || !isxdigit(p[1])))))
E 5
		return;

	base = 0;
	/*
	 * skip over leading '+', 'x[0-9a-fA-f]' or '0x', and
	 * set base.
	 */
	if (p[0] == '+')
		++p;
D 5
	if (p[0] == 'x' && ishexdigit(p[1])) {
E 5
I 5
	if (p[0] == 'x' && isxdigit(p[1])) {
E 5
		++p;
		base = 16;
	} else if (p[0] == '0' && p[1] == 'x') {
		p += 2;
		base = 16;
	}

	/* skip over the number */
	if (base == 16)
D 5
		for (num = p; ishexdigit(*p); ++p);
E 5
I 5
		for (num = p; isxdigit(*p); ++p);
E 5
	else
		for (num = p; isdigit(*p); ++p);

	/* check for no number */
	if (num == p)
		return;

	/* if terminates with a '.', base is decimal */
	if (*p == '.') {
		if (base)
			return;
		base = 10;
	}

	skip = strtol(num, &end, base ? base : 8);

	/* if end isn't the same as p, we got a non-octal digit */
D 6
	if (end != p)
E 6
I 6
	if (end != p) {
E 6
		skip = 0;
D 6
	else {
		if (*p) {
			if (*p == 'b')
				skip *= 512;
			else if (*p == 'B')
				skip *= 1024;
E 6
I 6
		return;
	}

	if (*p)
		if (*p == 'B') {
			skip *= 1024;
E 6
			++p;
I 6
		} else if (*p == 'b') {
			skip *= 512;
			++p;
E 6
		}
D 6
		if (*p)
			skip = 0;
		else {
			++*argvp;
			/*
			 * If the offset uses a non-octal base, the base of
			 * the offset is changed as well.  This isn't pretty,
			 * but it's easy.
			 */
E 6
I 6

	if (*p) {
		skip = 0;
		return;
	}

	/*
	 * If the offset uses a non-octal base, the base of the offset
	 * is changed as well.  This isn't pretty, but it's easy.
	 */
E 6
#define	TYPE_OFFSET	7
D 6
			if (base == 16) {
				fshead->nextfu->fmt[TYPE_OFFSET] = 'x';
				fshead->nextfs->nextfu->fmt[TYPE_OFFSET] = 'x';
			} else if (base == 10) {
				fshead->nextfu->fmt[TYPE_OFFSET] = 'd';
				fshead->nextfs->nextfu->fmt[TYPE_OFFSET] = 'd';
			}
		}
E 6
I 6
	if (base == 16) {
		fshead->nextfu->fmt[TYPE_OFFSET] = 'x';
		fshead->nextfs->nextfu->fmt[TYPE_OFFSET] = 'x';
	} else if (base == 10) {
		fshead->nextfu->fmt[TYPE_OFFSET] = 'd';
		fshead->nextfs->nextfu->fmt[TYPE_OFFSET] = 'd';
E 6
	}
I 6

	/* Terminate file list. */
	(*argvp)[1] = NULL;
E 6
I 4
}

static void
odprecede()
{
	static int first = 1;

	if (first) {
		first = 0;
		add("\"%07.7_Ao\n\"");
		add("\"%07.7_ao  \"");
	} else
		add("\"         \"");
E 4
E 3
}
E 1
