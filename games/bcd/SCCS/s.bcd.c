h08551
s 00018/00004/00169
d D 8.2 94/03/20 15:17:33 bostic 8 6
c table errors; From: db@diana.ocunix.on.ca (Dyane Bruce)
e
s 00012/00002/00171
d R 8.2 93/11/16 12:36:16 bostic 7 6
c Error in the table; From: db@diana.ocunix.on.ca (Dyane Bruce)
e
s 00005/00005/00168
d D 8.1 93/05/31 16:14:17 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00172
d D 5.1 93/02/24 14:54:27 bostic 5 4
c typo
e
s 00001/00011/00172
d D 4.4 90/06/01 13:00:41 bostic 4 3
c new copyright notice
e
s 00169/00122/00014
d D 4.3 89/11/30 16:04:15 bostic 3 2
c new version from Steve Hayman <sahayman@iuvax.cs.indiana.edu>
e
s 00001/00001/00135
d D 4.2 88/06/11 18:03:15 bostic 2 1
c get rid of non-printable chars
e
s 00136/00000/00000
d D 4.1 82/10/24 18:25:48 mckusick 1 0
c date and time created 82/10/24 18:25:48 by mckusick
e
u
U
t
T
I 3
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
D 5
 * Steve Hayman of the Indiana University Computer Science Dept..
E 5
I 5
 * Steve Hayman of the Indiana University Computer Science Dept.
E 5
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */
E 3
I 1

D 3
static char sccsid[] = "	%M%	%I%	%E%	";
E 3
I 3
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
E 3

D 3
int chtab[] = {
00000, /*   */
03004, /* ! */
02404, /* " */
02040, /* sharp */
02042, /* $ */
02104, /* % */
00001, /* & */
03002, /* ' */
02201, /* ( */
02202, /* ) */
02102, /* * */
00005, /* + */
02044, /* , */
00002, /* - */
02041, /* . */
00014, /* / */
00004, /* 0 */
00010, /* 1 */
00020, /* 2 */
00040, /* 3 */
00100, /* 4 */
00200, /* 5 */
00400, /* 6 */
01000, /* 7 */
02000, /* 8 */
04000, /* 9 */
02200, /* : */
02402, /* ; */
02401, /* < */
02204, /* = */
02400, /* > */
03000, /* ? */
02100, /* at */
 011,
 021,
 041,
0101,
0201,
0401,
01001,
02001,
04001,
012,
022,
042,
0102,
0202,
0402,
01002,
02002,
02002,
024,
044,
0104,
0204,
0404,
01004,
02004,
04004,
02020, /* [ */
03001, /* \ */
02101, /* ] */
00006, /* ^ */
02024 /* _ */
E 3
I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * bcd --
 *
 * Read one line of standard input and produce something that looks like a
 * punch card.  An attempt to reimplement /usr/games/bcd.  All I looked at
 * was the man page.
 *
 * I couldn't find a BCD table handy so I wrote a shell script to deduce what
 * the patterns were that the old bcd was using for each possible 8-bit
 * character.  These are the results -- the low order 12 bits represent the
 * holes.  (A 1 bit is a hole.)  These may be wrong, but they match the old
 * program!
 *
 * Steve Hayman
 * sahayman@iuvax.cs.indiana.edu
 * 1989 11 30
I 8
 *
 *
 * I found an error in the table. The same error is found in the SunOS 4.1.1
 * version of bcd. It has apparently been around a long time. The error caused
 * 'Q' and 'R' to have the same punch code. I only noticed the error due to
 * someone pointing it out to me when the program was used to print a cover
 * for an APA!  The table was wrong in 4 places. The other error was masked
 * by the fact that the input is converted to upper case before lookup.
 *
 * Dyane Bruce
 * db@diana.ocunix.on.ca
 * Nov 5, 1993
E 8
 */

#include <sys/types.h>
I 8

E 8
#include <stdio.h>
#include <ctype.h>

u_short holes[256] = {
    0x0,	 0x0,	  0x0,	   0x0,	    0x0,     0x0,     0x0,     0x0,
    0x0,	 0x0,	  0x0,	   0x0,	    0x0,     0x0,     0x0,     0x0,
    0x0,	 0x0,	  0x0,	   0x0,	    0x0,     0x0,     0x0,     0x0,
    0x0,	 0x0,	  0x0,	   0x0,	    0x0,     0x0,     0x0,     0x0,
    0x0,	 0x206,	  0x20a,   0x042,   0x442,   0x222,   0x800,   0x406,
    0x812,	 0x412,	  0x422,   0xa00,   0x242,   0x400,   0x842,   0x300,
    0x200,	 0x100,	  0x080,   0x040,   0x020,   0x010,   0x008,   0x004,
    0x002,	 0x001,	  0x012,   0x40a,   0x80a,   0x212,   0x00a,   0x006,
    0x022,	 0x900,	  0x880,   0x840,   0x820,   0x810,   0x808,   0x804,
    0x802,	 0x801,	  0x500,   0x480,   0x440,   0x420,   0x410,   0x408,
D 8
    0x404,	 0x402,	  0x402,   0x280,   0x240,   0x220,   0x210,   0x208,
E 8
I 8
    0x404,	 0x402,	  0x401,   0x280,   0x240,   0x220,   0x210,   0x208,
E 8
    0x204,	 0x202,	  0x201,   0x082,   0x822,   0x600,   0x282,   0x30f,
    0x900,	 0x880,	  0x840,   0x820,   0x810,   0x808,   0x804,   0x802,
    0x801,	 0x500,	  0x480,   0x440,   0x420,   0x410,   0x408,   0x404,
D 8
    0x402,	 0x402,	  0x280,   0x240,   0x220,   0x210,   0x208,   0x204,
E 8
I 8
    0x402,	 0x401,	  0x280,   0x240,   0x220,   0x210,   0x208,   0x204,
E 8
    0x202,	 0x201,	  0x082,   0x806,   0x822,   0x600,   0x282,   0x0,
    0x0,	 0x0,	  0x0,	   0x0,	    0x0,     0x0,     0x0,     0x0,
    0x0,	 0x0,	  0x0,	   0x0,	    0x0,     0x0,     0x0,     0x0,
    0x0,	 0x0,	  0x0,	   0x0,	    0x0,     0x0,     0x0,     0x0,
    0x0,	 0x0,	  0x0,	   0x0,	    0x0,     0x0,     0x0,     0x0,
    0x206,	 0x20a,	  0x042,   0x442,   0x222,   0x800,   0x406,   0x812,
    0x412,	 0x422,	  0xa00,   0x242,   0x400,   0x842,   0x300,   0x200,
    0x100,	 0x080,	  0x040,   0x020,   0x010,   0x008,   0x004,   0x002,
    0x001,	 0x012,	  0x40a,   0x80a,   0x212,   0x00a,   0x006,   0x022,
    0x900,	 0x880,	  0x840,   0x820,   0x810,   0x808,   0x804,   0x802,
    0x801,	 0x500,	  0x480,   0x440,   0x420,   0x410,   0x408,   0x404,
D 8
    0x402,	 0x402,	  0x280,   0x240,   0x220,   0x210,   0x208,   0x204,
E 8
I 8
    0x402,	 0x401,	  0x280,   0x240,   0x220,   0x210,   0x208,   0x204,
E 8
    0x202,	 0x201,	  0x082,   0x806,   0x822,   0x600,   0x282,   0x30f,
    0x900,	 0x880,	  0x840,   0x820,   0x810,   0x808,   0x804,   0x802,
    0x801,	 0x500,	  0x480,   0x440,   0x420,   0x410,   0x408,   0x404,
D 8
    0x402,	 0x402,	  0x280,   0x240,   0x220,   0x210,   0x208,   0x204,
E 8
I 8
    0x402,	 0x401,	  0x280,   0x240,   0x220,   0x210,   0x208,   0x204,
E 8
    0x202,	 0x201,	  0x082,   0x806,   0x822,   0x600,   0x282,   0x0
E 3
};
D 3
	char s[128];
	char *sp = {&s[0]};
E 3
I 3

/*
 * i'th bit of w.
 */
#define	bit(w,i)	((w)&(1<<(i)))

I 8
int
E 8
E 3
main(argc, argv)
D 3
char *argv[];
E 3
I 3
	int argc;
	char **argv;
E 3
{
D 3
	char *spp;
	int i;
	int j;
	int c;
	int l;
E 3
I 3
	char cardline[80];
E 3

D 3
	if (argc<2) {
		puts("% ");
		while ((c=getchar())!='\0'&c!='\n')
			*sp++ = c;
		*sp = 0;
		sp = &s[0];
E 3
I 3
	/*
	 * The original bcd prompts with a "%" when reading from stdin,
	 * but this seems kind of silly.  So this one doesn't.
	 */

	if (argc > 1) {
		while (--argc)
			printcard(*++argv);
E 3
	} else
D 3
		sp = *++argv;
	puts("\n\n\n\n");
	puts(" ________________________________");
	puts("________________\n");
	spp = sp;
	while(*spp++);
	spp--;
	l = spp - sp;
E 3
I 3
		while (fgets(cardline, sizeof(cardline), stdin))
			printcard(cardline);
	exit(0);
}

#define	COLUMNS	48

printcard(str)
	register char *str;
{
	static char rowchars[] = "   123456789";
	register int i, row;
	register char *p;
	char *index();

	/* ruthlessly remove newlines and truncate at 48 characters. */
	if ((p = index(str, '\n')))
		*p = '\0';

	if (strlen(str) > COLUMNS)
		str[COLUMNS] = '\0';

	/* make string upper case. */
	for (p = str; *p; ++p)
		if (isascii(*p) && islower(*p))
			*p = toupper(*p);

	 /* top of card */
	putchar(' ');
	for (i = 1; i <= COLUMNS; ++i)
		putchar('_');
	putchar('\n');

	/*
	 * line of text.  Leave a blank if the character doesn't have
	 * a hole pattern.
	 */
	p = str;
E 3
	putchar('/');
D 3
	puts(sp);
	i = 49 - l;
	while(--i>0) putchar(' ');
	puts("|\n");
	j = 0;
	spp = sp;
	while (j++<12) {
E 3
I 3
	for (i = 1; *p; i++, p++)
		if (holes[*p])
			putchar(*p);
		else
			putchar(' ');
	while (i++ <= COLUMNS)
		putchar(' ');
	putchar('|');
	putchar('\n');

	/*
	 * 12 rows of potential holes; output a ']', which looks kind of
	 * like a hole, if the appropriate bit is set in the holes[] table.
	 * The original bcd output a '[', a backspace, five control A's,
	 * and then a ']'.  This seems a little excessive.
	 */
	for (row = 0; row <= 11; ++row) {
E 3
		putchar('|');
D 3
		i = 0;
		spp = sp;
		while (i<48) {
			if(i>l) c = 0;
			else c = *spp++ - 040;
			i++;
			if (c>='a'-040) c = c - 040;
			if (c<0 | c>137) c = 0;
			if ((chtab[c]>>(j-1))&1) 
D 2
				puts("[]");
E 2
I 2
				puts("[\010\01\01\01\01\01]");
E 3
I 3
		for (i = 0, p = str; *p; i++, p++) {
			if (bit(holes[*p], 11 - row))
				putchar(']');
E 3
E 2
			else
D 3
				putchar(j>3?'0'+j-3:' ');
E 3
I 3
				putchar(rowchars[row]);
E 3
		}
D 3
		puts("|\n");
E 3
I 3
		while (i++ < COLUMNS)
			putchar(rowchars[row]);
		putchar('|');
		putchar('\n');
E 3
	}
D 3
	putchar('|');
	puts("____________");
	puts("____________________________________");
	puts("|\n");
	puts("\n\n\n\n");
}
E 3

D 3
puts(ss) char *ss; {
	int i;
	char t;
	i = 0;
	while(t = *ss++) {
		if(t >= 'a' && t <= 'z')
			t += 'A'-'a';
		putchar(t);
	}
E 3
I 3
	/* bottom of card */
	putchar('|');
	for (i = 1; i <= COLUMNS; i++)
		putchar('_');
	putchar('|');
	putchar('\n');
E 3
}
E 1
