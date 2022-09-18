h19903
s 00005/00005/00123
d D 8.1 93/05/31 16:21:37 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00127
d D 5.4 90/06/01 13:01:55 bostic 4 3
c new copyright notice
e
s 00065/00060/00073
d D 5.3 89/09/05 15:43:35 bostic 3 2
c don't re-decrypt each line; get a large sample and use it all to calculate
c frequencies -- why should each line be rotated differently?  Display all
c input instead of sample only.
e
s 00095/00086/00038
d D 5.2 89/09/05 15:08:20 bostic 2 1
c cleanup, reformat; handle arguments right, print the whole file
e
s 00124/00000/00000
d D 5.1 89/09/05 15:07:36 bostic 1 0
c version from USENET software
e
u
U
t
T
I 1
/*
D 2
 * program to to decrypt caesar(tm) cypher
 * (caesar is a trademark of the roman empire)
E 2
I 2
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
E 2
 *
D 2
 * to compile:
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * Rick Adams.
E 2
 *
D 2
 *	cc decrypt.c -lm -o decrypt.c
 *
 * usage:
 *
 *	decrypt [n] < file
 *
 * where n is an optional forced rotation.
 *
 * authors: Stan King, John Eldridge, based on algorithm suggested by
 *		Bob Morris
E 2
I 2
 * Authors:
 *	Stan King, John Eldridge, based on algorithm suggested by
 *	Bob Morris
E 2
 * 29-Sep-82
 *
I 2
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
E 2
 */

D 2
#ifdef SCCSID
static char	*SccsId = "@(#)caesar.c	1.7	4/16/85";
#endif /* SCCSID */
E 2
I 2
#ifndef lint
D 5
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 5
I 5
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 5
#endif /* not lint */
E 2

I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <math.h>
E 2
#include <stdio.h>
#include <ctype.h>
I 3
#include <unistd.h>
E 3
D 2
#include <math.h>
extern char *calloc();
E 2

I 2
#define	LINELENGTH	2048
#define	ROTATE(ch, perm) \
D 3
	isupper(ch) ? ('A' + (ch - 'A' + perm % 26)) : \
E 3
I 3
	isupper(ch) ? ('A' + (ch - 'A' + perm) % 26) : \
E 3
	    islower(ch) ? ('a' + (ch - 'a' + perm) % 26) : ch

I 3
/*
 * letter frequencies (taken from some unix(tm) documentation)
 * (unix is a trademark of Bell Laboratories)
 */
double stdf[26] = {
	7.97, 1.35, 3.61, 4.78, 12.37, 2.01, 1.46, 4.49, 6.39, 0.04,
	0.42, 3.81, 2.69, 5.92,  6.96, 2.91, 0.08, 6.63, 8.77, 9.68,
	2.62, 0.81, 1.88, 0.23,  2.07, 0.06,
};

E 3
E 2
main(argc, argv)
D 2
int argc;
char *argv[];
E 2
I 2
	int argc;
	char **argv;
E 2
{
D 2
	/* letter frequencies (taken from some unix(tm) documentation) */
	/* (unix is a trademark of Bell Laboratories) */
	static double stdf[ 26 ] =
	{
		7.97, 1.35, 3.61, 4.78, 12.37, 2.01, 1.46, 4.49,
		6.39, 0.04, 0.42, 3.81, 2.69, 5.92, 6.96, 2.91,
		0.08, 6.63, 8.77, 9.68, 2.62, 0.81, 1.88, 0.23,
		2.07, 0.06,
E 2
I 2
D 3
	/*
	 * letter frequencies (taken from some unix(tm) documentation)
	 * (unix is a trademark of Bell Laboratories)
	 */
	static double stdf[26] = {
		7.97, 1.35, 3.61, 4.78, 12.37, 2.01, 1.46, 4.49, 6.39, 0.04,
		0.42, 3.81, 2.69, 5.92,  6.96, 2.91, 0.08, 6.63, 8.77, 9.68,
		2.62, 0.81, 1.88, 0.23,  2.07, 0.06,
E 2
	};
D 2
	int obs[26];
	int bufsize;
	int c, i, try;
	double dot, winnerdot;  /* .. */
	int winner, forced = 0;
	char *inbuf;
E 2
I 2
	double dot, winnerdot;
	register int i, ch;
E 3
I 3
	extern int errno;
	register int ch, dot, i, nread, winnerdot;
E 3
	register char *inbuf;
D 3
	int bufsize, obs[26], rot, try, winner;
	char *malloc();
E 3
I 3
	int obs[26], try, winner;
	char *malloc(), *strerror();
E 3
E 2

D 2
	bufsize = 0;
	if( argc > 1 )
		sscanf( argv[1], "%d", &forced );
	if( forced == 0 )
		forced = -1000;
		
	inbuf = calloc( BUFSIZ, 1 );
E 2
I 2
D 3
	if (argc > 1) {
		if ((rot = atoi(argv[1])) < 0) {
			(void)fprintf(stderr, "caesar: bad rotation value.\n");
			exit(1);
		}
		printit(rot);
		exit(0);
	}
E 3
I 3
	if (argc > 1)
		printit(argv[1]);
E 3
E 2

D 2
	/* adjust frequency table to weight low probs REAL low */
	for (i=0; i<26; i++)	{
		stdf[i] = log(stdf[i]) + log(26.0/100.0);
E 2
I 2
	if (!(inbuf = malloc(LINELENGTH))) {
		(void)fprintf(stderr, "caesar: out of memory.\n");
		exit(1);
E 2
	}

D 2
	/* Decode each line separately */
	for (;;) {
		for (i=0; i<=25; obs[i++]=0)
			;
E 2
I 2
	/* adjust frequency table to weight low probs REAL low */
	for (i = 0; i < 26; ++i)
		stdf[i] = log(stdf[i]) + log(26.0 / 100.0);
E 2

I 2
D 3
	/* decode each line separately */
	for (bufsize = 0;;) {
		for (i = 0; i < 26; obs[i++] = 0);
E 3
I 3
	/* zero out observation table */
	bzero(obs, 26 * sizeof(int));
E 3

E 2
D 3
		/* get a sample of the text */
D 2
		for( i = 0; i < BUFSIZ; i++ ) {
			if( (c = getchar()) == EOF ) {
E 2
I 2
		for (i = 0; i < LINELENGTH; i++) {
			if ((ch = getchar()) == EOF)
E 2
				exit(0);
D 2
			}	
			inbuf[i] = c;
			if (c == '\n') {
				bufsize = i+1; 
E 2
I 2
			inbuf[i] = ch;
			if (ch == '\n')
E 2
				break;
D 2
			}
			if (islower(c))
				obs[c-'a'] += 1;
			else if (isupper(c))
				obs[c-'A'] += 1;
E 2
I 2
			if (islower(ch))
				obs[ch - 'a'] += 1;
			else if (isupper(ch))
				obs[ch - 'A'] += 1;
E 2
		}
I 2
		bufsize = i + 1;
E 3
I 3
	if ((nread = read(STDIN_FILENO, inbuf, LINELENGTH)) < 0) {
		(void)fprintf(stderr, "caesar: %s\n", strerror(errno));
		exit(1);
	}
	for (i = nread; i--;) {
		ch = inbuf[i];
		if (islower(ch))
			++obs[ch - 'a'];
		else if (isupper(ch))
			++obs[ch - 'A'];
	}
E 3
E 2

D 2
		/* now "dot" the freqs with the observed letter freqs */
		/*	and keep track of best fit */
		winner = 0;	
		for (try = 0; try<26; try+=13) {
E 2
I 2
D 3
		/*
		 * now "dot" the freqs with the observed letter freqs
		 * and keep track of best fit
		 */
		for (try = winner = 0; try < 26; try += 13) {
E 2
			dot = 0;
D 2
			for ( i=0; i<26; i++ ) {
				dot += obs[i] * stdf[ (i+try) % 26 ];
				}
E 2
I 2
			for (i = 0; i < 26; i++)
				dot += obs[i] * stdf[(i + try) % 26];
E 2
			/* initialize winning score */
D 2
			if( try == 0 )
E 2
I 2
			if (try == 0)
E 2
				winnerdot = dot;
D 2
			if( dot > winnerdot ) {
E 2
I 2
			if (dot > winnerdot) {
E 2
				/* got a new winner! */
				winner = try;
				winnerdot = dot;
			}
E 3
I 3
	/*
	 * now "dot" the freqs with the observed letter freqs
	 * and keep track of best fit
	 */
	for (try = winner = 0; try < 26; ++try) { /* += 13) { */
		dot = 0;
		for (i = 0; i < 26; i++)
			dot += obs[i] * stdf[(i + try) % 26];
		/* initialize winning score */
		if (try == 0)
			winnerdot = dot;
		if (dot > winnerdot) {
			/* got a new winner! */
			winner = try;
			winnerdot = dot;
E 3
		}
I 3
	}
E 3

D 2
		if (forced != -1000)
			winner = forced;

E 2
D 3
		/* print out sample buffer */
D 2
		for( i = 0; i < bufsize; i++ )
			putchar( rotate( inbuf[i], winner ) );
E 2
I 2
		while (bufsize--) {
			ch = *inbuf++;
E 3
I 3
	for (;;) {
		for (i = 0; i < nread; ++i) {
			ch = inbuf[i];
E 3
			putchar(ROTATE(ch, winner));
		}
I 3
		if (nread < LINELENGTH)
			break;
		if ((nread = read(STDIN_FILENO, inbuf, LINELENGTH)) < 0) {
			(void)fprintf(stderr, "caesar: %s\n", strerror(errno));
			exit(1);
		}
E 3
E 2
	}
I 3
	exit(0);
E 3
D 2
 }
E 2
I 2
}
E 2

D 2

static int
rotate( c, perm )
char c;
int perm;
E 2
I 2
D 3
printit(rot)
	register int rot;
E 3
I 3
printit(arg)
	char *arg;
E 3
E 2
{
D 2
	if (isupper(c))	{
		return 'A' + (c - 'A' + perm) % 26 ;
	}
	else if (islower(c)) {
		return 'a' + (c-'a'+perm) % 26 ;
	}
	else return c;
E 2
I 2
D 3
	register int ch;
E 3
I 3
	register int ch, rot;
E 3

I 3
	if ((rot = atoi(arg)) < 0) {
		(void)fprintf(stderr, "caesar: bad rotation value.\n");
		exit(1);
	}
E 3
	while ((ch = getchar()) != EOF)
		putchar(ROTATE(ch, rot));
I 3
	exit(0);
E 3
E 2
}
E 1
