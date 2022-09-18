h62125
s 00001/00001/00114
d D 8.3 94/03/20 14:35:03 bostic 5 4
c delete UofT; requested change from Henry Spencer <henry@zoo.toronto.edu>
e
s 00002/00002/00113
d D 8.2 94/03/16 12:42:54 bostic 4 3
c alpha3.3
e
s 00002/00002/00113
d D 8.1 93/06/04 12:57:43 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00114
d D 5.2 93/05/21 16:06:47 bostic 2 1
c Henry Spencer's Alpha 3.0 regex release
e
s 00115/00000/00000
d D 5.1 92/08/06 11:58:01 bostic 1 0
c date and time created 92/08/06 11:58:01 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 Henry Spencer.
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
E 4
I 4
 * Copyright (c) 1992, 1993, 1994 Henry Spencer.
 * Copyright (c) 1992, 1993, 1994
E 4
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
D 5
 * Henry Spencer of the University of Toronto.
E 5
I 5
 * Henry Spencer.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* character-name table */
static struct cname {
	char *name;
D 2
	uchar code;
E 2
I 2
	char code;
E 2
} cnames[] = {
	"NUL",	'\0',
	"SOH",	'\001',
	"STX",	'\002',
	"ETX",	'\003',
	"EOT",	'\004',
	"ENQ",	'\005',
	"ACK",	'\006',
	"BEL",	'\007',
	"alert",	'\007',
	"BS",		'\010',
	"backspace",	'\b',
	"HT",		'\011',
	"tab",		'\t',
	"LF",		'\012',
	"newline",	'\n',
	"VT",		'\013',
	"vertical-tab",	'\v',
	"FF",		'\014',
	"form-feed",	'\f',
	"CR",		'\015',
	"carriage-return",	'\r',
	"SO",	'\016',
	"SI",	'\017',
	"DLE",	'\020',
	"DC1",	'\021',
	"DC2",	'\022',
	"DC3",	'\023',
	"DC4",	'\024',
	"NAK",	'\025',
	"SYN",	'\026',
	"ETB",	'\027',
	"CAN",	'\030',
	"EM",	'\031',
	"SUB",	'\032',
	"ESC",	'\033',
	"IS4",	'\034',
	"FS",	'\034',
	"IS3",	'\035',
	"GS",	'\035',
	"IS2",	'\036',
	"RS",	'\036',
	"IS1",	'\037',
	"US",	'\037',
	"space",		' ',
	"exclamation-mark",	'!',
	"quotation-mark",	'"',
	"number-sign",		'#',
	"dollar-sign",		'$',
	"percent-sign",		'%',
	"ampersand",		'&',
	"apostrophe",		'\'',
	"left-parenthesis",	'(',
	"right-parenthesis",	')',
	"asterisk",	'*',
	"plus-sign",	'+',
	"comma",	',',
	"hyphen",	'-',
	"hyphen-minus",	'-',
	"period",	'.',
	"full-stop",	'.',
	"slash",	'/',
	"solidus",	'/',
	"zero",		'0',
	"one",		'1',
	"two",		'2',
	"three",	'3',
	"four",		'4',
	"five",		'5',
	"six",		'6',
	"seven",	'7',
	"eight",	'8',
	"nine",		'9',
	"colon",	':',
	"semicolon",	';',
	"less-than-sign",	'<',
	"equals-sign",		'=',
	"greater-than-sign",	'>',
	"question-mark",	'?',
	"commercial-at",	'@',
	"left-square-bracket",	'[',
	"backslash",		'\\',
	"reverse-solidus",	'\\',
	"right-square-bracket",	']',
	"circumflex",		'^',
	"circumflex-accent",	'^',
	"underscore",		'_',
	"low-line",		'_',
	"grave-accent",		'`',
	"left-brace",		'{',
	"left-curly-bracket",	'{',
	"vertical-line",	'|',
	"right-brace",		'}',
	"right-curly-bracket",	'}',
	"tilde",		'~',
	"DEL",	'\177',
	NULL,	0,
};
E 1
