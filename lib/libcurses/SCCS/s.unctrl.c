h49955
s 00002/00002/00079
d D 8.1 93/06/04 16:49:37 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00051/00022/00030
d D 5.6 93/01/11 13:42:04 elan 10 9
c Made characters 8-but chracters.
e
s 00037/00014/00015
d D 5.5 92/08/23 12:23:32 bostic 9 7
c KNF, add __unctrllen array
e
s 00037/00014/00015
d R 5.5 92/05/15 15:23:40 bostic 8 7
c add array of lengths for __unctrl array
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00028
d D 5.4 90/06/01 15:40:53 bostic 7 6
c new copyright notice
e
s 00010/00005/00029
d D 5.3 88/06/30 17:22:11 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00024
d D 5.2 88/06/08 13:57:53 bostic 5 4
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00018
d D 5.1 85/06/07 08:17:51 dist 4 3
c Add copyright
e
s 00001/00001/00018
d D 1.2 85/05/01 17:37:32 bloom 3 1
c fix sccs id
e
s 00013/00003/00016
d R 1.2 83/07/02 21:54:34 sam 2 1
c no longer a macro, never deserved to be
e
s 00019/00000/00000
d D 1.1 81/01/26 17:03:17 arnold 1 0
c date and time created 81/01/26 17:03:17 by arnold
e
u
U
t
T
I 1
/*
I 4
D 5
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 11
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1981, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
E 5
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

D 10
/*
E 4
D 9
 * define unctrl codes for each character
 *
E 9
I 9
 * Define unctrl codes for each character.
E 9
D 3
 * %G% (Berkeley) %W%
E 3
I 3
D 4
 * %W% (Berkeley) %G%
E 4
E 3
 */
I 9
char *__unctrl[128] = {
E 10
I 10
char *__unctrl[256] = {
E 10
	"^@",  "^A",  "^B",  "^C",  "^D",  "^E",  "^F",  "^G",
	"^H",  "^I",  "^J",  "^K",  "^L",  "^M",  "^N",  "^O",
	"^P",  "^Q",  "^R",  "^S",  "^T",  "^U",  "^V",  "^W",
	"^X",  "^Y",  "^Z",  "^[", "^\\",  "^]",  "^~",  "^_",
	 " ",   "!",  "\"",   "#",   "$",   "%",   "&",   "'",
	 "(",   ")",   "*",   "+",   ",",   "-",   ".",   "/",
	 "0",   "1",   "2",   "3",   "4",   "5",   "6",   "7",
	 "8",   "9",   ":",   ";",   "<",   "=",   ">",   "?",
	 "@",   "A",   "B",   "C",   "D",   "E",   "F",   "G",
	 "H",   "I",   "J",   "K",   "L",   "M",   "N",   "O",
	 "P",   "Q",   "R",   "S",   "T",   "U",   "V",   "W",
	 "X",   "Y",   "Z",   "[",  "\\",   "]",   "^",   "_",
	 "`",   "a",   "b",   "c",   "d",   "e",   "f",   "g",
	 "h",   "i",   "j",   "k",   "l",   "m",   "n",   "o",
	 "p",   "q",   "r",   "s",   "t",   "u",   "v",   "w",
	 "x",   "y",   "z",   "{",   "|",   "}",   "~",   "^?",
I 10

	"0x80", "0x81",	"0x82", "0x83", "0x84", "0x85", "0x86", "0x87",
	"0x88", "0x89",	"0x8a", "0x8b", "0x8c", "0x8d", "0x8e", "0x8f",
	"0x90", "0x91",	"0x92", "0x93", "0x94", "0x95", "0x96", "0x97",
	"0x98", "0x99",	"0x9a", "0x9b", "0x9c", "0x9d", "0x9e", "0x9f",
	"0xa0", "0xa1",	"0xa2", "0xa3", "0xa4", "0xa5", "0xa6", "0xa7",
	"0xa8", "0xa9",	"0xaa", "0xab", "0xac", "0xad", "0xae", "0xaf",
	"0xb0", "0xb1",	"0xb2", "0xb3", "0xb4", "0xb5", "0xb6", "0xb7",
	"0xb8", "0xb9",	"0xba", "0xbb", "0xbc", "0xbd", "0xbe", "0xbf",
	"0xc0", "0xc1",	"0xc2", "0xc3", "0xc4", "0xc5", "0xc6", "0xc7",
	"0xc8", "0xc9",	"0xca", "0xcb", "0xcc", "0xcd", "0xce", "0xcf",
	"0xd0", "0xd1",	"0xd2", "0xd3", "0xd4", "0xd5", "0xd6", "0xd7",
	"0xd8", "0xd9",	"0xda", "0xdb", "0xdc", "0xdd", "0xde", "0xdf",
	"0xe0", "0xe1",	"0xe2", "0xe3", "0xe4", "0xe5", "0xe6", "0xe7",
	"0xe8", "0xe9",	"0xea", "0xeb", "0xec", "0xed", "0xee", "0xef",
	"0xf0", "0xf1",	"0xf2", "0xf3", "0xf4", "0xf5", "0xf6", "0xf7",
	"0xf8", "0xf9",	"0xfa", "0xfb", "0xfc", "0xfd", "0xfe", "0xff",
E 10
};
E 9

D 9
/* LINTLIBRARY */
char	*_unctrl[]	= {	/* unctrl codes for ttys		*/
	"^@", "^A", "^B", "^C", "^D", "^E", "^F", "^G", "^H", "^I", "^J", "^K",
	"^L", "^M", "^N", "^O", "^P", "^Q", "^R", "^S", "^T", "^U", "^V", "^W",
	"^X", "^Y", "^Z", "^[", "^\\", "^]", "^~", "^_",
	" ", "!", "\"", "#", "$",  "%", "&", "'", "(", ")", "*", "+", ",", "-",
	".", "/", "0",  "1", "2",  "3", "4", "5", "6", "7", "8", "9", ":", ";",
	"<", "=", ">",  "?", "@",  "A", "B", "C", "D", "E", "F", "G", "H", "I",
	"J", "K", "L",  "M", "N",  "O", "P", "Q", "R", "S", "T", "U", "V", "W",
	"X", "Y", "Z",  "[", "\\", "]", "^", "_", "`", "a", "b", "c", "d", "e",
	"f", "g", "h",  "i", "j",  "k", "l", "m", "n", "o", "p", "q", "r", "s",
	"t", "u", "v",  "w", "x",  "y", "z", "{", "|", "}", "~", "^?"
E 9
I 9
D 10
/* The length of the characters in the above array. */
char __unctrllen[128] = {
	   2,     2,     2,     2,     2,     2,     2,     2,
	   2,     2,     2,     2,     2,     2,     2,     2,
	   2,     2,     2,     2,     2,     2,     2,     2,
	   2,     2,     2,     2,     2,     2,     2,     2,
	   1,     1,     1,     1,     1,     1,     1,     1,
	   1,     1,     1,     1,     1,     1,     1,     1,
	   1,     1,     1,     1,     1,     1,     1,     1,
	   1,     1,     1,     1,     1,     1,     1,     1,
	   1,     1,     1,     1,     1,     1,     1,     1,
	   1,     1,     1,     1,     1,     1,     1,     1,
	   1,     1,     1,     1,     1,     1,     1,     1,
	   1,     1,     1,     1,     1,     1,     1,     1,
	   1,     1,     1,     1,     1,     1,     1,     1,
	   1,     1,     1,     1,     1,     1,     1,     1,
	   1,     1,     1,     1,     1,     1,     1,     1,
	   1,     1,     1,     1,     1,     1,     1,     2,
E 10
I 10
char __unctrllen[256] = {
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 2, 
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
E 10
E 9
};
E 1
