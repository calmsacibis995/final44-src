h08291
s 00003/00002/00223
d D 8.2 95/04/27 17:04:02 bostic 31 30
c prettiness police
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00005/00005/00220
d D 8.1 93/07/19 10:16:03 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00224
d D 5.18 93/07/19 10:15:47 bostic 29 26
c short-write calculations were wrong 
c from Chris Demetriou
e
s 00005/00005/00220
d R 8.1 93/05/31 14:10:47 bostic 28 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00220
d R 8.1 93/05/31 13:07:32 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00023/00049/00202
d D 5.17 93/02/21 18:14:43 bostic 26 25
c use err(3) functions, minor cleanups
e
s 00001/00001/00250
d D 5.16 92/02/03 20:38:49 bostic 25 24
c no error message for stdout; try "(cat 1>&0) < /"
e
s 00002/00002/00249
d D 5.15 91/05/23 18:14:51 bostic 24 23
c print out "stdin", not "-"
e
s 00002/00000/00249
d D 5.14 91/05/06 10:15:07 bostic 23 22
c explicitly close stdout, so can check for flush/write failure
e
s 00063/00042/00186
d D 5.13 91/05/02 15:51:34 bostic 22 21
c fix was to fail on unrecoverable errors, i.e. if can't stat or write
c to stdout, or can't malloc, quit.  Also put in various ANSI fixes, and rolled
c error messages into an err() routine.
e
s 00001/00003/00227
d D 5.12 90/12/29 17:41:02 bostic 21 20
c partial write code was wrong
e
s 00001/00011/00229
d D 5.11 90/05/31 20:16:41 bostic 20 19
c new copyright notice
e
s 00002/00002/00238
d D 5.10 90/03/05 11:11:30 bostic 19 18
c fix for ANSI variable scoping
e
s 00002/00005/00238
d D 5.9 89/12/14 10:43:38 bostic 18 17
c getopt handles - better, now, no reason for cat to do so.
e
s 00010/00012/00233
d D 5.8 89/09/01 08:53:14 bostic 17 16
c use the right macros
e
s 00005/00004/00240
d D 5.7 89/07/18 16:37:17 bostic 16 15
c cat -s fix to not remove all newlines after first extra one
e
s 00133/00009/00110
d D 5.6 89/03/15 16:47:49 bostic 15 14
c merge 5.4 and 5.5, general cleanup
e
s 00039/00114/00080
d D 5.5 89/03/15 16:31:48 bostic 14 13
c remove the -b, -e, -n, -s, -t, -v flags; quit using stdio;
c malloc read/write buffer
e
s 00151/00186/00042
d D 5.4 89/03/11 14:22:10 bostic 13 12
c new version from Kevin Fall -- only lightly tested!
c last version to have old flags.
e
s 00013/00007/00215
d D 5.3 88/04/24 14:53:42 bostic 12 11
c fix for ANSI C
e
s 00002/00000/00220
d D 5.2 85/12/06 02:05:21 lepreau 11 10
c reset sticky eof on stdin so can handle multiple "-" args
e
s 00008/00002/00212
d D 5.1 85/04/30 14:50:03 dist 10 9
c Add copyright
e
s 00021/00010/00193
d D 4.9 85/02/14 19:17:33 karels 9 8
c don't loop on output errors
e
s 00065/00007/00138
d D 4.8 85/02/12 15:52:41 ralph 8 7
c speedup from lepreau@utah-cs, exit code fix from donn@utah-cs.
e
s 00000/00002/00145
d D 4.7 84/05/02 12:00:02 ralph 7 6
c use optimal buffer size for stdio.
e
s 00004/00001/00143
d D 4.6 83/08/11 19:51:49 sam 6 5
c sccs keyword fixes
e
s 00001/00001/00143
d D 4.5 83/04/26 11:24:06 mckusick 5 4
c added perror
e
s 00002/00001/00142
d D 4.4 82/02/20 11:14:05 root 4 3
c check for regular file before complaining about cat a >> a
e
s 00013/00011/00130
d D 4.3 81/09/14 17:52:02 ecc 3 2
c checked return of fstat for "input == output" protection
e
s 00080/00003/00061
d D 4.2 80/10/10 00:41:25 bill 2 1
c new options version
e
s 00064/00000/00000
d D 4.1 80/10/01 17:25:10 bill 1 0
c date and time created 80/10/01 17:25:10 by bill
e
u
U
t
T
I 10
/*
D 13
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 13
I 13
D 30
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 30
I 30
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 30
 *
 * This code is derived from software contributed to Berkeley by
 * Kevin Fall.
 *
D 20
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
E 20
I 20
 * %sccs.include.redist.c%
E 20
E 13
 */

E 10
I 6
#ifndef lint
I 12
D 30
char copyright[] =
D 13
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 13
I 13
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
E 13
 All rights reserved.\n";
E 30
I 30
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 30
#endif /* not lint */

#ifndef lint
E 12
D 10
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 10
I 10
static char sccsid[] = "%W% (Berkeley) %G%";
D 12
#endif not lint
E 12
I 12
#endif /* not lint */
E 12
E 10

I 14
#include <sys/param.h>
#include <sys/stat.h>
D 22
#include <sys/file.h>
E 22
I 22
D 26
#include <fcntl.h>
E 26
I 26

#include <ctype.h>
#include <err.h>
E 26
#include <errno.h>
D 26
#include <unistd.h>
E 26
I 26
#include <fcntl.h>
E 26
E 22
E 14
E 6
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
D 13
/*
 * Concatenate files.
 */
I 2
D 6
static	char *Sccsid = "%W% (Berkeley) %G%";
E 6
E 2

E 13
#include <stdio.h>
I 22
#include <stdlib.h>
#include <string.h>
E 22
D 13
#include <sys/types.h>
#include <sys/stat.h>
E 13
I 13
D 26
#include <ctype.h>
E 26
I 26
#include <unistd.h>
E 26
E 13

I 19
D 22
extern int errno;
E 22
E 19
I 15
int bflag, eflag, nflag, sflag, tflag, vflag;
int rval;
E 15
D 7
char	stdbuf[BUFSIZ];
E 7
I 2
D 8
int	bflg, eflg, nflg, sflg, tflg, vflg;
int	spaced, col, lno, inline;
E 8
I 8
D 9
/* #define OPTSIZE BUFSIZ	/* define this only if not 4.2 BSD */
E 9
I 9
D 13
/* #define OPTSIZE BUFSIZ	/* define this only if not 4.2 BSD or beyond */
E 13
I 13
D 14
int bflag, eflag, nflag, sflag, tflag, vflag;
int rval;
E 14
char *filename;
E 13
E 9
E 8
E 2

I 22
D 26
void cook_args(), cook_buf(), raw_args(), raw_cat();
void err __P((int, const char *, ...));
E 26
I 26
void cook_args __P((char *argv[]));
void cook_buf __P((FILE *));
void raw_args __P((char *argv[]));
void raw_cat __P((int));
E 26

I 26
int
E 26
E 22
I 8
D 13
int	bflg, eflg, nflg, sflg, tflg, uflg, vflg;
D 12
int	spaced, col, lno, inline, ibsize, obsize;
E 12
I 12
int	spaced, col, lno, inaline, ibsize, obsize;
E 12

E 13
E 8
main(argc, argv)
D 13
char **argv;
E 13
I 13
	int argc;
D 26
	char **argv;
E 26
I 26
	char *argv[];
E 26
E 13
{
D 13
	int fflg = 0;
	register FILE *fi;
	register c;
	int dev, ino = -1;
	struct stat statb;
I 8
	int retval = 0;
E 13
I 13
D 19
	extern int errno, optind;
E 19
I 19
	extern int optind;
E 19
D 14
	register FILE *fp;
	int ch;
E 14
I 14
D 15
	register int fd, ch, rval;
E 15
I 15
	int ch;
E 15
E 14
D 22
	char *strerror();
E 22
E 13
E 8

I 2
D 13
	lno = 1;
E 2
D 7
	setbuf(stdout, stdbuf);
E 7
	for( ; argc>1 && argv[1][0]=='-'; argc--,argv++) {
		switch(argv[1][1]) {
		case 0:
E 13
I 13
D 14
	while ((ch = getopt(argc, argv, "-benstuv")) != EOF)
E 14
I 14
D 15
	while ((ch = getopt(argc, argv, "-u")) != EOF)
E 15
I 15
D 18
	while ((ch = getopt(argc, argv, "-benstuv")) != EOF)
E 18
I 18
D 31
	while ((ch = getopt(argc, argv, "benstuv")) != EOF)
E 31
I 31
	while ((ch = getopt(argc, argv, "benstuv")) != -1)
E 31
E 18
E 15
E 14
		switch (ch) {
D 18
		case '-':
			--optind;
			goto done;
E 18
D 14
		case 'b':
			bflag = nflag = 1;	/* -b implies -n */
E 14
I 14
D 15
		case 'u':			/* always unbuffered */
E 15
I 15
		case 'b':
			bflag = nflag = 1;	/* -b implies -n */
E 15
E 14
E 13
			break;
I 15
		case 'e':
			eflag = vflag = 1;	/* -e implies -v */
			break;
		case 'n':
			nflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case 't':
			tflag = vflag = 1;	/* -t implies -v */
			break;
		case 'u':
			setbuf(stdout, (char *)NULL);
			break;
		case 'v':
			vflag = 1;
			break;
I 31
		default:
E 31
E 15
D 13
		case 'u':
			setbuf(stdout, (char *)NULL);
I 8
			uflg++;
E 8
			continue;
E 13
I 13
D 14
		case 'e':
			eflag = vflag = 1;	/* -e implies -v */
			break;
E 13
I 2
		case 'n':
D 13
			nflg++;
			continue;
		case 'b':
			bflg++;
			nflg++;
			continue;
		case 'v':
			vflg++;
			continue;
E 13
I 13
			nflag = 1;
			break;
E 13
		case 's':
D 13
			sflg++;
			continue;
		case 'e':
			eflg++;
			vflg++;
			continue;
E 13
I 13
			sflag = 1;
			break;
E 13
		case 't':
D 13
			tflg++;
			vflg++;
			continue;
E 13
I 13
			tflag = vflag = 1;	/* -t implies -v */
			break;
		case 'u':
			setbuf(stdout, (char *)NULL);
			break;
		case 'v':
			vflag = 1;
			break;
E 14
		case '?':
			(void)fprintf(stderr,
D 14
			    "usage: cat [-benstuv] [-] [file ...]\n");
E 14
I 14
D 15
			    "usage: cat [-u] [-] [file ...]\n");
E 15
I 15
			    "usage: cat [-benstuv] [-] [file ...]\n");
E 15
E 14
			exit(1);
E 13
E 2
		}
D 13
		break;
	}
D 3
	fstat(fileno(stdout), &statb);
	statb.st_mode &= S_IFMT;
	if (statb.st_mode!=S_IFCHR && statb.st_mode!=S_IFBLK) {
		dev = statb.st_dev;
		ino = statb.st_ino;
E 3
I 3
	if (fstat(fileno(stdout), &statb) == 0) {
		statb.st_mode &= S_IFMT;
		if (statb.st_mode!=S_IFCHR && statb.st_mode!=S_IFBLK) {
			dev = statb.st_dev;
			ino = statb.st_ino;
		}
I 9
#ifndef	OPTSIZE
E 9
I 8
		obsize = statb.st_blksize;
I 9
#endif
E 9
E 8
E 3
	}
I 8
	else
		obsize = 0;
E 8
	if (argc < 2) {
		argc = 2;
		fflg++;
	}
	while (--argc > 0) {
		if (fflg || (*++argv)[0]=='-' && (*argv)[1]=='\0')
			fi = stdin;
		else {
			if ((fi = fopen(*argv, "r")) == NULL) {
D 5
				fprintf(stderr, "cat: can't open %s\n", *argv);
E 5
I 5
				perror(*argv);
I 8
				retval = 1;
E 8
E 5
				continue;
E 13
I 13
D 18
done:	argv += optind;
E 18
I 18
	argv += optind;
E 18

I 15
	if (bflag || eflag || nflag || sflag || tflag || vflag)
		cook_args(argv);
	else
		raw_args(argv);
I 23
	if (fclose(stdout))
D 26
		err(1, "stdout: %s", strerror(errno));
E 26
I 26
		err(1, "stdout");
E 26
E 23
	exit(rval);
}

I 22
void
E 22
cook_args(argv)
	char **argv;
{
	register FILE *fp;

	fp = stdin;
D 24
	filename = "-";
E 24
I 24
	filename = "stdin";
E 24
	do {
		if (*argv) {
			if (!strcmp(*argv, "-"))
				fp = stdin;
D 26
			else if (!(fp = fopen(*argv, "r"))) {
D 22
				(void)fprintf(stderr, 
				    "cat: %s: %s\n", *argv, strerror(errno));
				rval = 1;
E 22
I 22
				err(0, "%s: %s", *argv, strerror(errno));
E 26
I 26
			else if ((fp = fopen(*argv, "r")) == NULL) {
				warn("%s", *argv);
E 26
E 22
				++argv;
				continue;
			}
			filename = *argv++;
		}
		cook_buf(fp);
		if (fp != stdin)
			(void)fclose(fp);
	} while (*argv);
}

I 22
void
E 22
cook_buf(fp)
	register FILE *fp;
{
	register int ch, gobble, line, prev;

	line = gobble = 0;
	for (prev = '\n'; (ch = getc(fp)) != EOF; prev = ch) {
		if (prev == '\n') {
			if (ch == '\n') {
				if (sflag) {
D 16
					if (gobble)
						continue;
E 16
I 16
D 17
					if (!gobble && putc(ch, stdout) == EOF)
E 17
I 17
					if (!gobble && putchar(ch) == EOF)
E 17
						break;
E 16
					gobble = 1;
I 16
					continue;
E 16
				}
				if (nflag && !bflag) {
					(void)fprintf(stdout, "%6d\t", ++line);
					if (ferror(stdout))
						break;
				}
D 16
			}
			else if (nflag) {
E 16
I 16
			} else if (nflag) {
E 16
				(void)fprintf(stdout, "%6d\t", ++line);
				if (ferror(stdout))
					break;
			}
		}
I 16
		gobble = 0;
E 16
		if (ch == '\n') {
			if (eflag)
D 17
				if (putc('$', stdout) == EOF)
E 17
I 17
				if (putchar('$') == EOF)
E 17
					break;
		} else if (ch == '\t') {
			if (tflag) {
D 17
				if (putc('^', stdout) == EOF ||
				    putc('I', stdout) == EOF)
E 17
I 17
				if (putchar('^') == EOF || putchar('I') == EOF)
E 17
					break;
				continue;
			}
		} else if (vflag) {
D 17
			if (ch > 0177) {
				if (putc('M', stdout) == EOF ||
				    putc('-', stdout) == EOF)
E 17
I 17
			if (!isascii(ch)) {
				if (putchar('M') == EOF || putchar('-') == EOF)
E 17
					break;
D 17
				ch &= 0177;
E 17
I 17
				ch = toascii(ch);
E 17
			}
			if (iscntrl(ch)) {
D 17
				if (putc('^', stdout) == EOF ||
				    putc(ch == '\177' ? '?' :
				    ch | 0100, stdout) == EOF)
E 17
I 17
				if (putchar('^') == EOF ||
				    putchar(ch == '\177' ? '?' :
				    ch | 0100) == EOF)
E 17
					break;
				continue;
			}
		}
D 17
		if (putc(ch, stdout) == EOF)
E 17
I 17
		if (putchar(ch) == EOF)
E 17
			break;
	}
	if (ferror(fp)) {
D 22
		(void)fprintf(stderr, "cat: %s: read error\n", filename);
		rval = 1;
E 22
I 22
D 26
		err(0, "%s: %s", strerror(errno));
E 26
I 26
		warn("%s", filename);
E 26
		clearerr(fp);
E 22
	}
D 22
	if (ferror(stdout)) {
		clearerr(stdout);
		(void)fprintf(stderr, "cat: stdout: write error\n");
		rval = 1;
	}
E 22
I 22
	if (ferror(stdout))
D 26
		err(1, "stdout: %s", strerror(errno));
E 26
I 26
		err(1, "stdout");
E 26
E 22
}

I 22
void
E 22
raw_args(argv)
	char **argv;
{
	register int fd;

E 15
D 14
	fp = stdin;
E 14
I 14
	fd = fileno(stdin);
E 14
D 24
	filename = "-";
E 24
I 24
	filename = "stdin";
E 24
I 14
D 15
	rval = 0;
E 15
E 14
	do {
		if (*argv) {
D 14
			if (!strcmp(*argv, "-")) {
				fp = stdin;
				filename = "-";
E 13
			}
D 13
		}
D 3
		fstat(fileno(fi), &statb);
		if (statb.st_dev==dev && statb.st_ino==ino) {
			fprintf(stderr, "cat: input %s is output\n",
			   fflg?"-": *argv);
			fclose(fi);
			continue;
E 3
I 3
		if (fstat(fileno(fi), &statb) == 0) {
D 4
			if (statb.st_dev==dev && statb.st_ino==ino) {
E 4
I 4
			if ((statb.st_mode & S_IFMT) == S_IFREG &&
			    statb.st_dev==dev && statb.st_ino==ino) {
E 4
				fprintf(stderr, "cat: input %s is output\n",
				   fflg?"-": *argv);
				fclose(fi);
I 8
				retval = 1;
E 13
I 13
			else if (!(fp = fopen(filename = *argv, "r"))) {
				(void)fprintf(stderr, 
				    "cat: %s: %s\n", *argv, strerror(errno));
E 14
I 14
			if (!strcmp(*argv, "-"))
				fd = fileno(stdin);
			else if ((fd = open(*argv, O_RDONLY, 0)) < 0) {
D 22
				(void)fprintf(stderr, "cat: %s: %s\n",
				    *argv, strerror(errno));
				rval = 1;
E 22
I 22
D 26
				err(0, "%s: %s", *argv, strerror(errno));
E 26
I 26
				warn("%s", *argv);
E 26
E 22
E 14
				++argv;
E 13
E 8
				continue;
			}
I 9
D 13
#ifndef	OPTSIZE
E 9
I 8
			ibsize = statb.st_blksize;
I 9
#endif
E 13
I 13
D 14
			++argv;
E 14
I 14
			filename = *argv++;
E 14
E 13
E 9
E 8
E 3
		}
I 13
D 14
		if (bflag || eflag || nflag || sflag || tflag || vflag)
			process_buf(fp);
E 13
I 8
		else
D 13
			ibsize = 0;
E 8
D 2
		while ((c = getc(fi)) != EOF)
			putchar(c);
E 2
I 2
		if (nflg||sflg||vflg)
			copyopt(fi);
D 8
		else {
E 8
I 8
		else if (uflg) {
E 8
			while ((c = getc(fi)) != EOF)
				putchar(c);
D 8
		}
E 8
I 8
		} else
D 9
			fastcat(fileno(fi));	/* no flags specified */
E 9
I 9
			retval |= fastcat(fileno(fi));	/* no flags specified */
E 9
E 8
E 2
		if (fi!=stdin)
			fclose(fi);
I 11
		else
			clearerr(fi);		/* reset sticky eof */
E 11
I 8
		if (ferror(stdout)) {
			fprintf(stderr, "cat: output write error\n");
			retval = 1;
			break;
		}
E 8
	}
I 2
D 8
	if (ferror(stdout))
		fprintf(stderr, "cat: output write error\n");
E 2
	return(0);
E 8
I 8
	exit(retval);
E 13
I 13
			rawcat(fileno(fp));
		if (fp != stdin)
			(void)fclose(fp);
E 14
I 14
D 15
		rval |= rawcat(fd);
E 15
I 15
D 22
		rval |= raw_cat(fd);
E 22
I 22
		raw_cat(fd);
E 22
E 15
		if (fd != fileno(stdin))
			(void)close(fd);
E 14
	} while (*argv);
D 15
	exit(rval);
E 15
E 13
E 8
I 2
}

D 13
copyopt(f)
	register FILE *f;
E 13
I 13
D 14
process_buf(fp)
	register FILE *fp;
E 13
{
D 13
	register int c;
E 13
I 13
	register int ch, gobble, line, prev;
E 13

D 13
top:
	c = getc(f);
	if (c == EOF)
		return;
	if (c == '\n') {
D 12
		if (inline == 0) {
E 12
I 12
		if (inaline == 0) {
E 12
			if (sflg && spaced)
				goto top;
			spaced = 1;
E 13
I 13
	line = gobble = 0;
	for (prev = '\n'; (ch = getc(fp)) != EOF; prev = ch) {
		if (prev == '\n') {
			if (ch == '\n') {
				if (sflag) {
					if (gobble)
						continue;
					gobble = 1;
				}
				if (nflag && !bflag) {
					(void)fprintf(stdout, "%6d\t", ++line);
					if (ferror(stdout))
						break;
				}
			}
			else if (nflag) {
				(void)fprintf(stdout, "%6d\t", ++line);
				if (ferror(stdout))
					break;
			}
E 13
		}
D 12
		if (nflg && bflg==0 && inline == 0)
E 12
I 12
D 13
		if (nflg && bflg==0 && inaline == 0)
E 12
			printf("%6d\t", lno++);
		if (eflg)
			putchar('$');
		putchar('\n');
D 12
		inline = 0;
E 12
I 12
		inaline = 0;
E 12
		goto top;
	}
D 12
	if (nflg && inline == 0)
E 12
I 12
	if (nflg && inaline == 0)
E 12
		printf("%6d\t", lno++);
D 12
	inline = 1;
E 12
I 12
	inaline = 1;
E 12
	if (vflg) {
		if (tflg==0 && c == '\t')
			putchar(c);
		else {
			if (c > 0177) {
				printf("M-");
				c &= 0177;
E 13
I 13
		if (ch == '\n') {
			if (eflag)
				if (putc('$', stdout) == EOF)
					break;
		} else if (ch == '\t') {
			if (tflag) {
				if (putc('^', stdout) == EOF ||
				    putc('I', stdout) == EOF)
					break;
				continue;
E 13
			}
D 13
			if (c < ' ')
				printf("^%c", c+'@');
			else if (c == 0177)
				printf("^?");
			else
				putchar(c);
E 13
I 13
		} else if (vflag) {
			if (ch > 0177) {
				if (putc('M', stdout) == EOF ||
				    putc('-', stdout) == EOF)
					break;
				ch &= 0177;
			}
			if (iscntrl(ch)) {
				if (putc('^', stdout) == EOF ||
				    putc(ch == '\177' ? '?' :
				    ch | 0100, stdout) == EOF)
					break;
				continue;
			}
E 13
		}
D 13
	} else
		putchar(c);
	spaced = 0;
	goto top;
E 13
I 13
		if (putc(ch, stdout) == EOF)
			break;
	}
	if (ferror(fp)) {
		(void)fprintf(stderr, "cat: %s: read error\n", filename);
		rval = 1;
	}
	if (ferror(stdout)) {
		clearerr(stdout);
		(void)fprintf(stderr, "cat: stdout: write error\n");
		rval = 1;
	}
E 13
I 8
}

E 14
D 13
fastcat(fd)
register int fd;
E 13
I 13
D 15
rawcat(fd)
E 15
I 15
D 22
raw_cat(fd)
E 15
	register int fd;
E 22
I 22
void
raw_cat(rfd)
	register int rfd;
E 22
E 13
{
D 13
	register int	buffsize, n, nwritten, offset;
	register char	*buff;
	struct stat	statbuff;
	char		*malloc();
E 13
I 13
D 19
	extern int errno;
E 19
D 14
	static char buf[8*1024];
	register int nr, nw, off;
	char *strerror();
E 14
I 14
D 22
	register int nr, nw, off;
E 22
I 22
	register int nr, nw, off, wfd;
E 22
	static int bsize;
	static char *buf;
	struct stat sbuf;
D 22
	char *malloc(), *strerror();
E 22
E 14
E 13

I 22
	wfd = fileno(stdout);
E 22
D 13
#ifndef	OPTSIZE
D 9
	if (ibsize == 0)
		buffsize = BUFSIZ;	/* handle reads from a pipe */
	else if (obsize == 0)
E 9
I 9
	if (obsize)
		buffsize = obsize;	/* common case, use output blksize */
	else if (ibsize)
E 9
		buffsize = ibsize;
	else
D 9
		buffsize = obsize;	/* common case, use output blksize */
E 9
I 9
		buffsize = BUFSIZ;
E 9
#else
	buffsize = OPTSIZE;
#endif

D 9
	if ((buff = malloc(buffsize)) == NULL)
E 9
I 9
	if ((buff = malloc(buffsize)) == NULL) {
E 9
		perror("cat: no memory");
I 9
		return (1);
	}
E 9

	/*
	 * Note that on some systems (V7), very large writes to a pipe
	 * return less than the requested size of the write.
	 * In this case, multiple writes are required.
	 */
	while ((n = read(fd, buff, buffsize)) > 0) {
		offset = 0;
		do {
			nwritten = write(fileno(stdout), &buff[offset], n);
D 9
			if (nwritten <= 0)
E 9
I 9
			if (nwritten <= 0) {
E 9
				perror("cat: write error");
I 9
				exit(2);
E 13
I 13
D 14
	while ((nr = read(fd, buf, sizeof(buf))) > 0)
E 14
I 14
D 26
	if (!buf) {
E 26
I 26
	if (buf == NULL) {
E 26
D 22
		if (fstat(fileno(stdout), &sbuf)) {
			(void)fprintf(stderr, "cat: %s: %s\n", filename,
			    strerror(errno));
			return(1);
		}
E 22
I 22
		if (fstat(wfd, &sbuf))
D 26
			err(1, "%s: %s", filename, strerror(errno));
E 26
I 26
			err(1, "%s", filename);
E 26
E 22
		bsize = MAX(sbuf.st_blksize, 1024);
D 22
		if (!(buf = malloc((u_int)bsize))) {
D 15
			fprintf(stderr, "cat: %s: no memory.\n", filename);
E 15
I 15
			(void)fprintf(stderr, "cat: %s: no memory.\n",
			    filename);
E 15
			return(1);
		}
E 22
I 22
D 26
		if (!(buf = malloc((u_int)bsize)))
			err(1, "%s", strerror(errno));
E 26
I 26
		if ((buf = malloc((u_int)bsize)) == NULL)
D 31
			err(1, "");
E 31
I 31
			err(1, NULL);
E 31
E 26
E 22
	}
D 22
	while ((nr = read(fd, buf, bsize)) > 0)
E 22
I 22
	while ((nr = read(rfd, buf, bsize)) > 0)
E 22
E 14
D 21
		for (off = 0; off < nr;) {
E 21
I 21
D 29
		for (off = 0; off < nr; nr -= nw, off += nw)
E 29
I 29
		for (off = 0; nr; nr -= nw, off += nw)
E 29
E 21
D 22
			if ((nw = write(fileno(stdout), buf + off, nr)) < 0) {
				perror("cat: stdout");
D 14
				rval = 1;
				return;
E 14
I 14
				return(1);
E 14
E 13
			}
E 9
D 13
			offset += nwritten;
		} while ((n -= nwritten) > 0);
E 13
I 13
D 21
			off += nw;
		}
E 21
	if (nr < 0) {
		(void)fprintf(stderr, "cat: %s: %s\n", filename,
		    strerror(errno));
D 14
		rval = 1;
E 14
I 14
		return(1);
E 14
E 13
	}
I 14
	return(0);
E 22
I 22
			if ((nw = write(wfd, buf + off, nr)) < 0)
D 25
				err(1, "stdout");
E 25
I 25
D 26
				err(1, "stdout: %s", strerror(errno));
E 26
I 26
				err(1, "stdout");
E 26
E 25
	if (nr < 0)
D 26
		err(0, "%s: %s", filename, strerror(errno));
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(int ex, const char *fmt, ...)
#else
err(ex, fmt, va_alist)
	int ex;
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
	(void)fprintf(stderr, "cat: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	if (ex)
		exit(1);
	rval = 1;
E 26
I 26
		warn("%s", filename);
E 26
E 22
E 14
D 9
	if (n < 0)
		perror("cat: read error");
E 9
D 13

	free(buff);
I 9
	if (n < 0) {
		perror("cat: read error");
		return (1);
	}
	return (0);
E 13
E 9
E 8
E 2
}
E 1
