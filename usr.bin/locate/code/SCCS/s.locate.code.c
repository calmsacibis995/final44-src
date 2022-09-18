h18840
s 00004/00001/00183
d D 8.4 95/05/04 15:43:58 bostic 17 16
c optarg/optind moved to unistd.h
e
s 00007/00009/00177
d D 8.3 95/04/28 12:45:22 bostic 16 15
c more misuse of NULL, plus my version of Craig Leres's fix for PARITY chars
c From: Chris Torek <torek@BSDI.COM>
e
s 00001/00001/00185
d D 8.2 95/04/27 15:49:59 bostic 15 14
c If you clear the parity bit you can end up with a control character
c that you don't map to '?'.
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00005/00005/00181
d D 8.1 93/06/06 14:59:15 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00039/00177
d D 5.4 93/04/13 13:34:36 torek 13 12
c open the proper file.  use libc err().
e
s 00002/00002/00214
d D 5.3 92/05/27 16:46:32 elan 12 11
c Fixed if-else ambiguity bug.
e
s 00003/00000/00213
d D 5.2 92/03/01 15:33:06 mckusick 11 10
c check that write was successful (net2/usr.bin/9)
e
s 00122/00053/00091
d D 5.1 92/02/06 09:27:14 bostic 10 9
c fix exit change; major whitespace cleanup
e
s 00010/00005/00134
d D 4.9 92/01/31 21:28:16 leres 9 8
c Exit with an explicit status (non-zero if there were problems writing the
c output). Minor whitespace cleanup.
e
s 00001/00011/00138
d D 4.8 90/06/01 16:55:22 bostic 8 7
c new copyright notice
e
s 00002/00002/00147
d D 4.7 90/03/06 11:19:40 bostic 7 6
c rename fast find code to locate
e
s 00005/00001/00144
d D 4.6 89/10/13 09:34:11 bostic 6 5
c strip trailing newline; bug report 4.3BSD/usr.bin/215
e
s 00001/00002/00144
d D 4.5 89/05/19 19:10:20 bostic 5 4
c don't use gets
e
s 00028/00002/00118
d D 4.4 89/05/04 16:11:23 bostic 4 3
c add Berkeley specific copyright notices
e
s 00070/00070/00050
d D 4.3 89/05/04 14:32:32 jak 3 2
c added find.h to remove magic numbers shared by find.c and code.c,
c sped up code by 30% while reducing number of lines and fixing an encoding
c bug (thereby compressing the encoded database about another 2.5%), added
c explanatory comments
e
s 00009/00007/00111
d D 4.2 83/07/21 11:22:46 mckusick 2 1
c move database to /usr/lib/find; restrict database to /usr
e
s 00118/00000/00000
d D 4.1 83/07/21 00:14:44 mckusick 1 0
c date and time created 83/07/21 00:14:44 by mckusick
e
u
U
t
T
I 4
/*
D 14
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * This code is derived from software contributed to Berkeley by
 * James A. Woods.
 *
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
 */

E 4
I 1
#ifndef lint
D 4
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 4
I 4
D 14
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 14
I 14
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 14
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

/*
 * PURPOSE:	sorted list compressor (works with a modified 'find'
 *		to encode/decode a filename database)
 *
D 2
 * USAGE:	find.bigram < list > bigrams
 *		process bigrams (see find.squeeze) > common_bigrams
 *		find.code common_bigrams < list > squozen_list
E 2
I 2
 * USAGE:	bigram < list > bigrams
 *		process bigrams (see updatedb) > common_bigrams
 *		code common_bigrams < list > squozen_list
E 2
 *
D 3
 * METHOD:	Uses 'front compression' (see ";login:", March 1983, p. 8 ).
 *		Output format is, per line, an offset differential count byte
 *		followed by a partially bigram-encoded ascii residue. 
E 3
I 3
 * METHOD:	Uses 'front compression' (see ";login:", Volume 8, Number 1
D 10
 *		February/March 1983, p. 8 ).  Output format is, per line, an
E 10
I 10
 *		February/March 1983, p. 8).  Output format is, per line, an
E 10
 *		offset differential count byte followed by a partially bigram-
 *		encoded ascii residue.  A bigram is a two-character sequence,
 *		the first 128 most common of which are encoded in one byte.
E 3
 *
I 3
 * EXAMPLE:	For simple front compression with no bigram encoding,
 *		if the input is...		then the output is...
 *
 *		/usr/src			 0 /usr/src
 *		/usr/src/cmd/aardvark.c		 8 /cmd/aardvark.c
 *		/usr/src/cmd/armadillo.c	14 armadillo.c
 *		/usr/tmp/zoo			 5 tmp/zoo
 *
E 3
D 9
 *  	The codes are:
E 9
I 9
 *	The codes are:
E 9
 *
D 9
 *	0-28	likeliest differential counts + offset to make nonnegative 
E 9
I 9
 *	0-28	likeliest differential counts + offset to make nonnegative
E 9
D 3
 *	30	escape code for out-of-range count to follow in next word
D 2
 *	128-255 bigram codes, (128 most common, as determined by 'find.squeeze')
E 2
I 2
 *	128-255 bigram codes, (128 most common, as determined by 'updatedb')
E 2
 *	32-127  single character (printable) ascii residue
E 3
I 3
 *	30	switch code for out-of-range count to follow in next word
 *	128-255 bigram codes (128 most common, as determined by 'updatedb')
 *	32-127  single character (printable) ascii residue (ie, literal)
E 3
 *
D 2
 * SEE ALSO:	squeeze, bigram.c, find.c
E 2
I 2
D 10
 * SEE ALSO:	updatedb.csh, bigram.c, find.c
E 10
I 10
 * SEE ALSO:	updatedb.csh, bigram.c
E 10
E 2
D 9
 * 
E 9
I 9
 *
E 9
 * AUTHOR:	James A. Woods, Informatics General Corp.,
 *		NASA Ames Research Center, 10/82
 */

D 7
#include <stdio.h>
E 7
I 3
#include <sys/param.h>
I 17

E 17
I 13
#include <err.h>
E 13
I 10
#include <errno.h>
I 17
#include <stdio.h>
E 17
#include <stdlib.h>
#include <string.h>
E 10
D 7
#include "find.h"
E 7
I 7
D 17
#include <stdio.h>
E 17
I 17
#include <unistd.h>

E 17
#include "locate.h"
E 7
E 3

D 3
#define MAXPATH 1024		/* maximum pathname length */
#define	RESET	30		/* switch code */
E 3
I 3
D 10
#define BGBUFSIZE	(NBG * 2)	/* size of bigram buffer */
E 10
I 10
#define	BGBUFSIZE	(NBG * 2)	/* size of bigram buffer */
D 13
#define OERR		err("stdout: %s", strerror(errno))
E 13
E 10
E 3

D 3
char path[MAXPATH];
char oldpath[MAXPATH] = " ";	
char bigrams[257] = { 0 };
E 3
I 3
char buf1[MAXPATHLEN] = " ";	
char buf2[MAXPATHLEN];
char bigrams[BGBUFSIZE + 1] = { 0 };
E 3

D 10
main ( argc, argv )
	int argc; char *argv[];
E 10
I 10
int	bgindex __P((char *));
D 13
void	err __P((const char *, ...));
E 13
void	usage __P((void));

int
main(argc, argv)
	int argc;
	char *argv[];
E 10
{
D 3
  	int count, oldcount, diffcount;
	int j, code;
	char bigram[3];
E 3
I 3
D 10
	register char *cp, *oldpath = buf1, *path = buf2;
D 9
  	int code, count, diffcount, oldcount = 0;
E 9
I 9
	int code, count, diffcount, oldcount = 0;
E 10
I 10
	register char *cp, *oldpath, *path;
	int ch, code, count, diffcount, oldcount;
E 10
E 9
E 3
	FILE *fp;

D 3
	oldcount = 0;
	bigram[2] = NULL;

E 3
D 2
	if ( (fp = fopen ( argv[1], "r" )) == NULL )
		printf ( "Usage: find.code common_bigrams < list > coded_list\n" ), exit ( 1 );
E 2
I 2
D 10
	if ((fp = fopen(argv[1], "r")) == NULL) {
D 3
		printf("Usage: code common_bigrams < list > coded_list\n");
E 3
I 3
		printf("Usage: code common_bigrams < list > squozen_list\n");
E 3
		exit(1);
	}
E 2
D 3
	fgets ( bigrams, 257, fp );
	fwrite ( bigrams, 1, 256, stdout );
E 3
I 3
	/* first copy bigram array to stdout */
	fgets ( bigrams, BGBUFSIZE + 1, fp );
	fwrite ( bigrams, 1, BGBUFSIZE, stdout );
	fclose( fp );
E 10
I 10
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch(ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
E 10
E 3

I 3
D 5
	/* every path will fit in path buffer, so safe to use gets */
E 3
     	while ( gets ( path ) != NULL ) {
E 5
I 5
D 9
     	while ( fgets ( path, sizeof(buf2), stdin ) != NULL ) {
E 9
I 9
D 10
	while ( fgets ( path, sizeof(buf2), stdin ) != NULL ) {
E 9
I 6
		/* truncate newline */
E 10
I 10
	if (argc != 1)
		usage();

D 13
	if ((fp = fopen(argv[1], "r")) == NULL)
		err("%s: %s", argv[1], strerror(errno));
E 13
I 13
	if ((fp = fopen(argv[0], "r")) == NULL)
		err(1, "%s", argv[0]);
E 13

	/* First copy bigram array to stdout. */
	(void)fgets(bigrams, BGBUFSIZE + 1, fp);
	if (fwrite(bigrams, 1, BGBUFSIZE, stdout) != BGBUFSIZE)
D 13
		err("stdout: %s", strerror(errno));
E 13
I 13
		err(1, "stdout");
E 13
	(void)fclose(fp);

	oldpath = buf1;
	path = buf2;
	oldcount = 0;
	while (fgets(path, sizeof(buf2), stdin) != NULL) {
		/* Truncate newline. */
E 10
		cp = path + strlen(path) - 1;
		if (cp > path && *cp == '\n')
			*cp = '\0';
E 6
E 5
D 3
		/*
		   squelch unprintable chars so as not to botch decoding
		*/
		for ( j = 0; path[j] != NULL; j++ ) {	
			path[j] &= 0177;		
			if ( path[j] < 040 || path[j] == 0177 )
				path[j] = '?';
E 3
I 3
D 10
		/* squelch characters that would botch the decoding */
		for ( cp = path; *cp != NULL; cp++ ) {
D 6
			if ( *cp >= PARITY )
E 6
I 6
			if ( (unsigned char)*cp >= PARITY )
E 10
I 10

		/* Squelch characters that would botch the decoding. */
D 16
		for (cp = path; *cp != NULL; cp++) {
			if ((u_char)*cp >= PARITY)
E 10
E 6
				*cp &= PARITY-1;
D 10
			else if ( *cp <= SWITCH )
E 10
I 10
D 15
			else if (*cp <= SWITCH)
E 15
I 15
			if (*cp <= SWITCH)
E 16
I 16
		for (cp = path; *cp != '\0'; cp++) {
			if ((u_char)*cp >= PARITY || *cp <= SWITCH)
E 16
E 15
E 10
				*cp = '?';
E 3
		}
D 3
		count = prefix_length ( oldpath, path );
		diffcount = count - oldcount;
		if ( (diffcount < -14) || (diffcount > 14) ) {
			putc ( RESET, stdout );
			putw ( diffcount + 14, stdout );
E 3
I 3
D 10
		/* skip longest common prefix */
		for ( cp = path; *cp == *oldpath; cp++, oldpath++ )
			if ( *oldpath == NULL )
E 10
I 10

		/* Skip longest common prefix. */
		for (cp = path; *cp == *oldpath; cp++, oldpath++)
D 16
			if (*oldpath == NULL)
E 16
I 16
			if (*oldpath == '\0')
E 16
E 10
				break;
		count = cp - path;
		diffcount = count - oldcount + OFFSET;
		oldcount = count;
D 10
		if ( diffcount < 0 || diffcount > 2*OFFSET ) {
			putc ( SWITCH, stdout );
			putw ( diffcount, stdout );
E 3
		}
E 10
I 10
D 12
		if (diffcount < 0 || diffcount > 2 * OFFSET)
E 12
I 12
		if (diffcount < 0 || diffcount > 2 * OFFSET) {
E 12
			if (putchar(SWITCH) == EOF ||
			    putw(diffcount, stdout) == EOF)
D 13
				OERR;
E 13
I 13
				err(1, "stdout");
E 13
E 10
D 12
		else
E 12
I 12
		} else
E 12
D 3
			putc ( diffcount + 14, stdout );	
E 3
I 3
D 10
			putc ( diffcount, stdout );	
E 10
I 10
			if (putchar(diffcount) == EOF)
D 13
				OERR;
E 13
I 13
				err(1, "stdout");
E 13
E 10
E 3

D 3
		for ( j = count; path[j] != NULL; j += 2 ) {
			if ( path[j + 1] == NULL ) {
				putchar ( path[j] );
E 3
I 3
D 10
		while ( *cp != NULL ) {
			if ( *(cp + 1) == NULL ) {
				putchar ( *cp );
E 10
I 10
D 16
		while (*cp != NULL) {
			if (*(cp + 1) == NULL) {
E 16
I 16
		while (*cp != '\0') {
			if (*(cp + 1) == '\0') {
E 16
				if (putchar(*cp) == EOF)
D 13
					OERR;
E 13
I 13
					err(1, "stdout");
E 13
E 10
E 3
				break;
			}
D 3
			bigram[0] = path[j];
			bigram[1] = path[j + 1];
			/*
			    linear search for specific bigram in string table
			*/
			if ( (code = strindex ( bigrams, bigram )) % 2 == 0 )
				putchar ( (code / 2) | 0200 );	
			else 		
				fputs ( bigram, stdout );
E 3
I 3
D 10
			if ( (code = bgindex ( cp )) < 0 ) {
				putchar ( *cp++ );
				putchar ( *cp++ );
			}
			else {	/* found, so mark byte with parity bit */
				putchar ( (code / 2) | PARITY );
E 10
I 10
			if ((code = bgindex(cp)) < 0) {
				if (putchar(*cp++) == EOF ||
				    putchar(*cp++) == EOF)
D 13
					OERR;
E 13
I 13
					err(1, "stdout");
E 13
			} else {
				/* Found, so mark byte with parity bit. */
				if (putchar((code / 2) | PARITY) == EOF)
D 13
					OERR;
E 13
I 13
					err(1, "stdout");
E 13
E 10
				cp += 2;
			}
E 3
		}
D 3
		strcpy ( oldpath, path );	
		oldcount = count;
E 3
I 3
D 10
		if ( path == buf1 )		/* swap pointers */
			path = buf2, oldpath = buf1;
		else
			path = buf1, oldpath = buf2;
I 9

		/* Non-zero status if there were errors */
		if (fflush(stdout) != 0 || ferror(stdout))
			exit(1);
		exit(0);
E 10
I 10
		if (path == buf1) {		/* swap pointers */
			path = buf2;
			oldpath = buf1;
		} else {
			path = buf1;
			oldpath = buf2;
		}
E 10
E 9
E 3
	}
I 11
	/* Non-zero status if there were errors */
	if (fflush(stdout) != 0 || ferror(stdout))
		exit(1);
E 11
I 10
	exit(0);
E 10
}

D 3
strindex ( string, pattern )	/* return location of pattern in string or -1 */
	char *string, *pattern;
E 3
I 3
D 10
bgindex ( bg )			/* return location of bg in bigrams or -1 */
E 10
I 10
int
bgindex(bg)			/* Return location of bg in bigrams or -1. */
E 10
	char *bg;
E 3
{
D 3
	register char *s, *p, *q;
E 3
I 3
D 10
	register char *p;
	register char bg0 = bg[0], bg1 = bg[1];
E 10
I 10
	register char bg0, bg1, *p;
E 10
E 3

D 3
	for ( s = string; *s != NULL; s++ ) 
		if ( *s == *pattern ) {		/* fast first char check */
			for ( p = pattern + 1, q = s + 1; *p != NULL; p++, q++ )
				if ( *q != *p )
					break;
			if ( *p == NULL )	
				return ( q - strlen ( pattern ) - string );
		}
	return ( -1 );
}

prefix_length ( s1, s2 )	/* return length of longest common prefix */
	char *s1, *s2;		/* ... of strings s1 and s2 */
{
	register char *start;

    	for ( start = s1; *s1 == *s2; s1++, s2++ )	
		if ( *s1 == NULL )		
	    		break;
    	return ( s1 - start );
E 3
I 3
D 10
	for ( p = bigrams; *p != NULL; p++ )
		if ( *p++ == bg0 && *p == bg1 )
E 10
I 10
	bg0 = bg[0];
	bg1 = bg[1];
D 16
	for (p = bigrams; *p != NULL; p++)
E 16
I 16
	for (p = bigrams; *p != '\0'; p++)
E 16
		if (*p++ == bg0 && *p == bg1)
E 10
			break;
D 10
	return ( *p == NULL ? -1 : --p - bigrams );
E 10
I 10
D 16
	return (*p == NULL ? -1 : --p - bigrams);
E 16
I 16
	return (*p == '\0' ? -1 : --p - bigrams);
E 16
}

void
usage()
{
	(void)fprintf(stderr,
	    "usage: locate.code common_bigrams < list > squozen_list\n");
	exit(1);
D 13
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
	(void)fprintf(stderr, "locate.code: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 13
E 10
E 3
}
E 1
