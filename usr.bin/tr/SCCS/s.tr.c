h21575
s 00003/00000/00261
d D 8.2 95/05/04 15:47:37 bostic 13 12
c optarg/optind moved to unistd.h
e
s 00005/00005/00256
d D 8.1 93/06/06 16:38:19 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00000/00245
d D 5.4 93/03/03 11:14:18 bostic 11 10
c don't zero out meta characters; from Donn Seeley at BSDI
e
s 00002/00004/00243
d D 5.3 92/01/16 16:04:24 bostic 10 9
c rewording, no real change
e
s 00028/00055/00219
d D 5.2 91/10/27 10:38:23 bostic 9 8
c various bug fixes, don't restrict class usage at all on the grounds
c that you can't get it right.  Hal Jesperson agrees that this is correct,
c it's not clear from the POSIX draft.
e
s 00204/00132/00070
d D 5.1 91/10/24 17:49:20 bostic 8 7
c POSIX 1003.2/D11.2 version
e
s 00014/00005/00188
d D 4.7 90/07/23 16:25:47 torek 7 6
c fix octal-escape code: beware end of string, etc
e
s 00001/00011/00192
d D 4.6 90/06/01 17:47:36 bostic 6 5
c new copyright notice
e
s 00002/00002/00201
d D 4.5 90/05/10 20:29:17 bostic 5 4
c increment pointer for "\a"
e
s 00022/00018/00181
d D 4.4 88/10/27 12:17:23 bostic 4 3
c allow end of range to be octal number; failed on "-d '\13-\37'"
e
s 00177/00115/00022
d D 4.3 88/09/03 15:41:58 bostic 3 2
c new version, from scratch; pass through NUL's like everything else
e
s 00005/00001/00132
d D 4.2 85/04/22 15:07:25 mckusick 2 1
c check for write failure
e
s 00133/00000/00000
d D 4.1 80/10/01 17:29:00 bill 1 0
c date and time created 80/10/01 17:29:00 by bill
e
u
U
t
T
I 1
D 3
static char *sccsid = "%W% (Berkeley) %G%";
E 3
I 3
/*
D 12
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 6
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */

#ifndef lint
D 12
char copyright[] =
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
E 12
I 12
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 12
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 13

E 13
E 3
#include <stdio.h>
I 3
D 8
#include <ctype.h>
E 8
I 8
#include <stdlib.h>
#include <string.h>
I 13
#include <unistd.h>

E 13
#include "extern.h"
E 8
E 3

D 3
/* tr - transliterate data stream */
int	dflag	= 0;
int	sflag	= 0;
int	cflag = 0;
int	save	= 0;
char	code[256];
char	squeez[256];
char	vect[256];
struct string { int last, max; char *p; } string1, string2;
E 3
I 3
D 8
#define	NCHARS	256				/* size of u_char */
#define	OOBCH	257				/* out of band value */
E 8
I 8
static int string1[NCHARS] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,		/* ASCII */
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
	0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
	0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
I 11
	0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
	0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
	0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
	0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
	0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
	0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
	0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
	0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
	0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
	0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
	0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
	0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
	0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
	0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
	0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff,
E 11
}, string2[NCHARS];
E 8
E 3

D 3
main(argc,argv)
char **argv;
E 3
I 3
D 8
typedef struct {
	char *str;
	int lastch, endrange;
	enum { NORM, INRANGE, EOS } state;
} STR;
E 8
I 8
D 9
static void setup __P((int *, char *, STR *, int, u_int));
E 9
I 9
STR s1 = { STRING1, NORMAL, 0, OOBCH, { 0, OOBCH }, NULL, NULL };
STR s2 = { STRING2, NORMAL, 0, OOBCH, { 0, OOBCH }, NULL, NULL };

static void setup __P((int *, char *, STR *, int));
E 9
static void usage __P((void));
E 8

I 8
int
E 8
main(argc, argv)
	int argc;
	char **argv;
E 3
{
D 3
	register i;
	int j;
	register c, d;
	char *compl;
	int lastd;
E 3
I 3
D 8
	extern int optind;
E 8
I 8
	register int ch, cnt, lastch, *p;
E 8
D 9
	STR s1, s2;
E 9
D 8
	register int ch, indx, lastch;
	int cflag, dflag, sflag;
	u_char *tp, tab[NCHARS], squeeze[NCHARS];
E 8
I 8
	int cflag, dflag, sflag, isstring2;
E 8
E 3

D 3
	string1.last = string2.last = 0;
	string1.max = string2.max = 0;
	string1.p = string2.p = "";

	if(--argc>0) {
		argv++;
		if(*argv[0]=='-'&&argv[0][1]!=0) {
			while(*++argv[0])
				switch(*argv[0]) {
				case 'c':
					cflag++;
					continue;
				case 'd':
					dflag++;
					continue;
				case 's':
					sflag++;
					continue;
				}
			argc--;
			argv++;
E 3
I 3
	cflag = dflag = sflag = 0;
	while ((ch = getopt(argc, argv, "cds")) != EOF)
		switch((char)ch) {
		case 'c':
			cflag = 1;
			break;
		case 'd':
			dflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case '?':
		default:
D 8
			fprintf(stderr,
			    "usage: tr [-cds] [string1 [string2]]\n");
			exit(1);
E 8
I 8
			usage();
E 8
E 3
		}
I 3
	argc -= optind;
	argv += optind;

I 8
	switch(argc) {
	case 0:
	default:
		usage();
		/* NOTREACHED */
	case 1:
		isstring2 = 0;
		break;
	case 2:
		isstring2 = 1;
		break;
	}

D 9
	if (argv[0][0] == '\0')
		err("empty string1");
	if (isstring2 && argv[1][0] == '\0')
		err("empty string2");
	
E 9
E 8
	/*
D 8
	 * the original tr was amazingly tolerant of the command line.
	 * Neither -c or -s have any effect unless there are two strings.
	 * Extra arguments are silently ignored.  Bag this noise, they
	 * should all be errors.
E 8
I 8
	 * tr -ds [-c] string1 string2
	 * Delete all characters (or complemented characters) in string1.
	 * Squeeze all characters in string2.
E 8
	 */
D 8
	if (argc < 2 && !dflag) {
E 8
I 8
	if (dflag && sflag) {
		if (!isstring2)
			usage();

D 9
		setup(string1, argv[0], &s1, cflag, T_CLASS | T_UL);
		setup(string2, argv[1], &s2, 0, T_CLASS | T_SEQ | T_UL);
E 9
I 9
		setup(string1, argv[0], &s1, cflag);
		setup(string2, argv[1], &s2, 0);
E 9
		
		for (lastch = OOBCH; (ch = getchar()) != EOF;)
			if (!string1[ch] && (!string2[ch] || lastch != ch)) {
				lastch = ch;
				(void)putchar(ch);
			}
		exit(0);
	}

	/*
	 * tr -d [-c] string1
	 * Delete all characters (or complemented characters) in string1.
	 */
	if (dflag) {
		if (isstring2)
			usage();

D 9
		setup(string1, argv[0], &s1, cflag, T_CLASS | T_UL);
E 9
I 9
		setup(string1, argv[0], &s1, cflag);
E 9

E 8
		while ((ch = getchar()) != EOF)
D 8
			putchar(ch);
E 8
I 8
			if (!string1[ch])
				(void)putchar(ch);
E 8
		exit(0);
E 3
	}
D 3
	if(argc>0) string1.p = argv[0];
	if(argc>1) string2.p = argv[1];
	for(i=0; i<256; i++)
		code[i] = vect[i] = 0;
	if(cflag) {
		while(c = next(&string1))
			vect[c&0377] = 1;
		j = 0;
		for(i=1; i<256; i++)
			if(vect[i]==0) vect[j++] = i;
		vect[j] = 0;
		compl = vect;
	}
	for(i=0; i<256; i++)
		squeez[i] = 0;
	lastd = 0;
	for(;;){
		if(cflag) c = *compl++;
		else c = next(&string1);
		if(c==0) break;
		d = next(&string2);
		if(d==0) d = lastd;
		else lastd = d;
		squeez[d&0377] = 1;
		code[c&0377] = dflag?1:d;
	}
	while(d = next(&string2))
		squeez[d&0377] = 1;
	squeez[0] = 1;
	for(i=0;i<256;i++) {
		if(code[i]==0) code[i] = i;
		else if(dflag) code[i] = 0;
	}
E 3

I 2
D 3
	clearerr(stdout);
E 2
	while((c=getc(stdin)) != EOF ) {
		if(c == 0) continue;
		if(c = code[c&0377]&0377)
D 2
			if(!sflag || c!=save || !squeez[c&0377])
E 2
I 2
			if(!sflag || c!=save || !squeez[c&0377]) {
E 2
				putchar(save = c);
I 2
				if(ferror(stdout))
					exit(1);
E 3
I 3
D 8
	bzero(tab, NCHARS);
	if (sflag) {
		s1.str = argv[1];
		s1.state = NORM;
		s1.lastch = OOBCH;
		while (next(&s1))
			squeeze[s1.lastch] = 1;
E 8
I 8
	/*
	 * tr -s [-c] string1
	 * Squeeze all characters (or complemented characters) in string1.
	 */
	if (sflag && !isstring2) {
D 9
		setup(string1, argv[0], &s1, cflag, T_CLASS | T_UL);
E 9
I 9
		setup(string1, argv[0], &s1, cflag);
E 9

		for (lastch = OOBCH; (ch = getchar()) != EOF;)
			if (!string1[ch] || lastch != ch) {
				lastch = ch;
				(void)putchar(ch);
			}
		exit(0);
E 8
	}
D 8
	if (dflag) {
		s1.str = argv[0];
		s1.state = NORM;
		s1.lastch = OOBCH;
E 8
I 8

	/*
	 * tr [-cs] string1 string2
	 * Replace all characters (or complemented characters) in string1 with
	 * the character in the same position in string2.  If the -s option is
	 * specified, squeeze all the characters in string2.
	 */
	if (!isstring2)
		usage();

	s1.str = argv[0];
D 9
	s1.state = NORMAL;
	s1.lastch = OOBCH;
	s1.type = T_CLASS | T_UL;

E 9
	s2.str = argv[1];
D 9
	s2.state = NORMAL;
	s2.lastch = OOBCH;
	s2.type = T_SEQ;
E 9

D 9
	if (cflag) {
E 9
I 9
	if (cflag)
E 9
		for (cnt = NCHARS, p = string1; cnt--;)
			*p++ = OOBCH;
D 9
		/*
		 * More than a single character is meaningless with -c, but
		 * allow "tr abc [\n*]".
		 */
		if (!next(&s2))
			err("empty string2");
		for (ch = s2.lastch; next(&s2) && s2.state != INFINITE;);
		if (ch != s2.lastch)
			err("-c option and string2 has multiple characters");
E 8
		while (next(&s1))
E 9
I 9

	if (!next(&s2))
		err("empty string2");

	/* If string2 runs out of characters, use the last one specified. */
	if (sflag)
		while (next(&s1)) {
D 10
			ch = s2.lastch;
E 9
D 8
			tab[s1.lastch] = 1;
		if (cflag)
			for (tp = tab, indx = 0; indx < NCHARS; ++tp, ++indx)
				*tp = !*tp;
E 8
I 8
			string1[s1.lastch] = ch;
E 10
I 10
			string1[s1.lastch] = ch = s2.lastch;
E 10
E 8
D 9
		if (sflag)
E 9
D 8
			for (lastch = OOBCH; (ch = getchar()) != EOF;) {
				if (tab[ch] || (squeeze[ch] && lastch == ch))
					continue;
				lastch = ch;
				putchar(ch);
E 3
			}
I 3
		else
			while ((ch = getchar()) != EOF)
				if (!tab[ch])
					putchar(ch);
E 8
I 8
			string2[ch] = 1;
D 9
		for (cnt = 0, p = string1; cnt < NCHARS; ++p, ++cnt)
			*p = *p == OOBCH ? ch : cnt;
E 8
	} else {
D 8
		s1.str = argv[0];
		s2.str = argv[1];
		s1.state = s2.state = NORM;
		s1.lastch = s2.lastch = OOBCH;
		if (cflag) {
E 8
I 8
		s2.type |= T_UL;
E 9
I 9
			(void)next(&s2);
		}
	else
E 9
		while (next(&s1)) {
E 8
D 9
			/*
D 8
			 * if cflag is set, tr just pretends it only got one
			 * character in string2.  As reasonable as anything
			 * else.  Should really be an error.
E 8
I 8
			 * If the second string runs out of characters, just
			 * use the last one specified.
E 8
			 */
D 8
			while (next(&s2));
			lastch = s2.lastch;
			for (tp = tab, indx = 0; indx < NCHARS; ++tp, ++indx)
				*tp = lastch;
			while (next(&s1))
				tab[s1.lastch] = s1.lastch;
		} else {
			for (tp = tab, indx = 0; indx < NCHARS; ++tp, ++indx)
				*tp = indx;
			while (next(&s1)) {
				(void)next(&s2);
				tab[s1.lastch] = s2.lastch;
			}
E 8
I 8
			if (!next(&s2))
				err("empty string2");
			if ((s1.state == ULSET || s2.state == ULSET) &&
			    s1.state != s2.state)
				err("mismatched lower/upper classes");
			string1[s1.lastch] = s2.lastch;
			if (sflag)
				string2[s2.lastch] = 1;
E 9
I 9
D 10
			ch = s2.lastch;
			string1[s1.lastch] = ch;
E 10
I 10
			string1[s1.lastch] = ch = s2.lastch;
E 10
			(void)next(&s2);
E 9
E 8
		}
D 8
		if (sflag)
			for (lastch = OOBCH; (ch = getchar()) != EOF;) {
				ch = tab[ch];
				if (squeeze[ch] && lastch == ch)
					continue;
E 8
I 8
D 9
		if (*s2.str)
			err("string2 longer than string1");
	}
E 9

I 9
	if (cflag)
		for (cnt = 0, p = string1; cnt < NCHARS; ++p, ++cnt)
			*p = *p == OOBCH ? ch : cnt;

E 9
	if (sflag)
		for (lastch = OOBCH; (ch = getchar()) != EOF;) {
			ch = string1[ch];
			if (!string2[ch] || lastch != ch) {
E 8
				lastch = ch;
D 8
				putchar(ch);
E 8
I 8
				(void)putchar(ch);
E 8
			}
D 8
		else
			while ((ch = getchar()) != EOF)
				putchar((int)tab[ch]);
E 3
E 2
	}
	exit(0);
E 8
I 8
		}
	else
		while ((ch = getchar()) != EOF)
			(void)putchar(string1[ch]);
	exit (0);
E 8
}

D 8
next(s)
D 3
struct string *s;
E 3
I 3
D 7
	STR *s;
E 7
I 7
	register STR *s;
E 8
I 8
static void
D 9
setup(string, arg, str, cflag, type)
E 9
I 9
setup(string, arg, str, cflag)
E 9
	int *string;
	char *arg;
	STR *str;
	int cflag;
D 9
	u_int type;
E 9
E 8
E 7
E 3
{
I 3
D 8
	register int ch;
E 8
I 8
	register int cnt, *p;
E 8
D 4
	int cnt, val;
E 4
E 3

D 3
again:
	if(s->max) {
		if(s->last++ < s->max)
			return(s->last);
		s->max = s->last = 0;
E 3
I 3
D 8
	if (s->state == EOS)
		return(0);
	if (s->state == INRANGE) {
		if (++s->lastch == s->endrange)
			s->state = NORM;
		return(1);
E 3
	}
D 3
	if(s->last && *s->p=='-') {
		nextc(s);
		s->max = nextc(s);
		if(s->max==0) {
			s->p--;
			return('-');
E 3
I 3
	if (!(ch = *s->str++)) {
		s->state = EOS;
		return(0);
	}
D 4
	if (ch == '\\') {			/* escape; \nnn is octal # */
		for (val = cnt = 0; isascii(ch = *s->str) && isdigit(ch)
		    && cnt++ < 3; ++s->str)
			val = val * 8 + ch - '0';
		s->lastch = cnt ? val : ch;
E 4
I 4
	if (ch == '\\') {			/* \### */
		s->lastch = tran(s);
E 4
		return(1);
	}
	if (ch == '-') {			/* ranges */
D 4
		if (s->lastch == OOBCH) {	/* "-a" */
			s->lastch = '-';
			return(1);
E 3
		}
D 3
		if(s->max < s->last)  {
			s->last = s->max-1;
			return('-');
E 3
I 3
		s->endrange = ch = *s->str;
		if (!ch) {			/* "a-" */
			s->lastch = '-';
			return(1);
E 3
		}
E 4
I 4
		if (s->lastch == OOBCH)		/* "-a" */
			goto fail2;
		if (!(ch = *s->str++))		/* "a-" */
			goto fail1;
		if (ch == '\\')			/* \### */
			ch = tran(s);
E 4
D 3
		goto again;
	}
	return(s->last = nextc(s));
}

nextc(s)
struct string *s;
{
	register c, i, n;

	c = *s->p++;
	if(c=='\\') {
		i = n = 0;
		while(i<3 && (c = *s->p)>='0' && c<='7') {
			n = n*8 + c - '0';
			i++;
			s->p++;
E 3
I 3
		if (s->lastch > ch) { 		/* "z-a" */
D 4
			s->lastch = '-';
E 4
I 4
fail1:			--s->str;
fail2:			s->lastch = '-';
E 4
			return(1);
E 3
		}
D 3
		if(i>0) c = n;
		else c = *s->p++;
E 3
I 3
D 4
		++s->str;
E 4
		if (s->lastch == ch)		/* "a-a" */
			return(next(s));
		s->state = INRANGE;		/* "a-z" */
D 4
		++s->lastch;
E 4
I 4
		s->endrange = ch;
E 4
		return(1);
E 3
	}
D 3
	if(c==0) *--s->p = 0;
	return(c&0377);
E 3
I 3
	s->lastch = ch;
	return(1);
E 8
I 8
	str->str = arg;
D 9
	str->state = NORMAL;
	str->lastch = OOBCH;
	str->type = type;

E 9
	bzero(string, NCHARS * sizeof(int));
	while (next(str))
		string[str->lastch] = 1;
	if (cflag)
		for (p = string, cnt = NCHARS; cnt--; ++p)
			*p = !*p;
E 8
I 4
}

I 7
D 8
/*
 * Translate \-escapes.  Up to 3 octal digits => char; no digits => literal.
 * Unadorned backslash "\" is like \000.
 */
E 7
tran(s)
	register STR *s;
E 8
I 8
static void
usage()
E 8
{
D 7
	register int ch, cnt, val;
E 7
I 7
D 8
	register int ch, cnt = 0, val = 0;
E 8
I 8
	(void)fprintf(stderr, "usage: tr [-cs] string1 string2\n");
	(void)fprintf(stderr, "       tr [-c] -d string1\n");
	(void)fprintf(stderr, "       tr [-c] -s string1\n");
	(void)fprintf(stderr, "       tr [-c] -ds string1 string2\n");
	exit(1);
}
E 8
E 7

D 5
	for (val = cnt = 0; isascii(ch = *s->str) && isdigit(ch)
	    && cnt++ < 3; ++s->str)
E 5
I 5
D 7
	for (val = cnt = 0; isascii(ch = *s->str++) && isdigit(ch)
	    && cnt++ < 3;)
E 7
I 7
D 8
	for (;;) {
		ch = *s->str++;
		if (!isascii(ch) || !isdigit(ch) || ++cnt > 3)
			break;
E 7
E 5
		val = val * 8 + ch - '0';
D 7
	return(cnt ? val : ch);
E 7
I 7
	}
	if (cnt || ch == 0)
		s->str--;
	return (cnt ? val : ch);
E 8
I 8
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
	(void)fprintf(stderr, "tr: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 8
E 7
E 4
E 3
}
E 1
