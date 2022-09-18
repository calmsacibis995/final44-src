h04607
s 00001/00001/00043
d D 8.3 94/03/20 14:35:02 bostic 4 3
c delete UofT; requested change from Henry Spencer <henry@zoo.toronto.edu>
e
s 00002/00002/00042
d D 8.2 94/03/16 12:42:54 bostic 3 2
c alpha3.3
e
s 00002/00002/00042
d D 8.1 93/06/04 12:57:40 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00044/00000/00000
d D 5.1 92/08/06 11:57:59 bostic 1 0
c date and time created 92/08/06 11:57:59 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 Henry Spencer.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
E 3
I 3
 * Copyright (c) 1992, 1993, 1994 Henry Spencer.
 * Copyright (c) 1992, 1993, 1994
E 3
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
D 4
 * Henry Spencer of the University of Toronto.
E 4
I 4
 * Henry Spencer.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* character-class table */
static struct cclass {
	char *name;
	char *chars;
	char *multis;
} cclasses[] = {
	"alnum",	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\
0123456789",				"",
	"alpha",	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
					"",
	"blank",	" \t",		"",
	"cntrl",	"\007\b\t\n\v\f\r\1\2\3\4\5\6\16\17\20\21\22\23\24\
\25\26\27\30\31\32\33\34\35\36\37\177",	"",
	"digit",	"0123456789",	"",
	"graph",	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\
0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~",
					"",
	"lower",	"abcdefghijklmnopqrstuvwxyz",
					"",
	"print",	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\
0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ",
					"",
	"punct",	"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~",
					"",
	"space",	"\t\n\v\f\r ",	"",
	"upper",	"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
					"",
	"xdigit",	"0123456789ABCDEFabcdef",
					"",
	NULL,		0,		""
};
E 1
