h33505
s 00001/00001/00261
d D 8.3 94/04/25 11:42:32 bostic 12 10
c typo (NULL pointer dereference)
e
s 00001/00002/00260
d R 8.3 94/04/25 11:39:10 bostic 11 10
c typo (NULL pointer dereference)
e
s 00141/00127/00121
d D 8.2 94/04/16 10:41:41 bostic 10 9
c do most of POSIX.2 compliance, use getopt(3) to parse arguments
c general ANSI C cleanups, use err(3) functions
c original argument parsing was dropping core
e
s 00005/00005/00243
d D 8.1 93/06/06 16:24:42 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00247
d D 4.8 90/06/01 17:42:30 bostic 8 7
c new copyright notice
e
s 00046/00033/00212
d D 4.7 89/01/23 10:53:30 bostic 7 6
c exit if write fails, exit 1 on failure, minor cleanups
e
s 00010/00005/00235
d D 4.6 88/06/29 21:54:34 bostic 6 5
c install approved copyright notice
e
s 00106/00086/00134
d D 4.5 87/12/02 17:19:10 bostic 5 4
c reformat to standard, add Berkeley header
e
s 00001/00001/00219
d D 4.4 87/05/18 11:51:17 bostic 4 3
c bug report tahoe/usr.bin/1; number of lines arg handled incorrectly
e
s 00207/00069/00013
d D 4.3 86/11/20 15:30:05 bostic 3 2
c bug report 4.3BSD/usr.bin/13; fix max # of files bug; complete rewrite
e
s 00001/00001/00081
d D 4.2 83/04/29 01:48:11 mckusick 2 1
c added perror
e
s 00082/00000/00000
d D 4.1 80/10/01 17:28:33 bill 1 0
c date and time created 80/10/01 17:28:33 by bill
e
u
U
t
T
I 1
D 5
static char *sccsid = "%W% (Berkeley) %G%";
E 5
I 5
/*
D 9
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.
E 9
I 9
D 10
 * Copyright (c) 1987, 1993
E 10
I 10
 * Copyright (c) 1987, 1993, 1994
E 10
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 6
 */
E 5
I 3

I 5
#ifndef lint
D 9
char copyright[] =
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
 All rights reserved.\n";
E 9
I 9
static char copyright[] =
D 10
"%Z% Copyright (c) 1987, 1993\n\
E 10
I 10
"%Z% Copyright (c) 1987, 1993, 1994\n\
E 10
	The Regents of the University of California.  All rights reserved.\n";
E 9
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 5
#include <sys/param.h>
D 10
#include <sys/file.h>
E 3
#include <stdio.h>
E 10
I 10

E 10
I 3
#include <ctype.h>
I 10
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
E 10
E 3

D 3
unsigned count = 1000;
int	fnumber;
char	fname[100];
char	*ifil;
char	*ofil;
FILE	*is;
FILE	*os;
E 3
I 3
D 10
#define DEFLINE	1000			/* default num lines per file */
#define ERR	-1			/* general error */
D 7
#define ERREXIT	0			/* error exit */
E 7
#define NO	0			/* no/false */
#define OK	0			/* okay exit */
#define YES	1			/* yes/true */
E 10
I 10
#define DEFLINE	1000			/* Default num lines per file. */
E 10
E 3

D 3
main(argc, argv)
char *argv[];
E 3
I 3
D 10
static long	bytecnt,		/* byte count to split on */
		numlines;		/* lines in each file */
static int	ifd = ERR,		/* input file descriptor */
		ofd = ERR;		/* output file descriptor */
static short	file_open;		/* if a file open */
static char	bfr[MAXBSIZE],		/* I/O buffer */
		fname[MAXPATHLEN];	/* file name */
E 10
I 10
long	 bytecnt;			/* Byte count to split on. */
long	 numlines;			/* Line count to split on. */
int	 file_open;			/* If a file open. */
int	 ifd = -1, ofd = -1;		/* Input/output file descriptors. */
char	 bfr[MAXBSIZE];			/* I/O buffer. */
char	 fname[MAXPATHLEN];		/* File name prefix. */
E 10

I 10
void newfile __P((void));
void split1 __P((void));
void split2 __P((void));
void usage __P((void));

int
E 10
D 5
main(argc,argv)
int	argc;
char	**argv;
E 5
I 5
main(argc, argv)
D 7
	int	argc;
	char	**argv;
E 7
I 7
	int argc;
D 10
	char **argv;
E 10
I 10
	char *argv[];
E 10
E 7
E 5
E 3
{
D 3
	register i, c, f;
	int iflg = 0;
E 3
I 3
D 7
	register int	cnt;		/* general counter */
	long	atol();
	char	*strcpy();
E 7
I 7
D 10
	register int cnt;
	long atol();
	char *strcpy();
E 10
I 10
	int ch;
	char *ep, *p;
E 10
E 7
E 3

D 3
	for(i=1; i<argc; i++)
		if(argv[i][0] == '-')
			switch(argv[i][1]) {
		
			case '\0':
				iflg = 1;
				continue;
		
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				count = atoi(argv[i]+1);
				continue;
E 3
I 3
D 5
	for (cnt = 1;cnt < argc;++cnt) {
E 5
I 5
D 10
	for (cnt = 1; cnt < argc; ++cnt) {
E 5
		if (argv[cnt][0] == '-')
			switch(argv[cnt][1]) {
D 5
				case 0:		/* stdin by request */
					if (ifd != ERR)
						usage();
					ifd = 0;
					break;
				case 'b':	/* byte count split */
					if (numlines)
						usage();
					if (!argv[cnt][2])
						bytecnt = atol(argv[++cnt]);
					else
						bytecnt = atol(argv[cnt] + 2);
					if (bytecnt <= 0) {
						fputs("split: byte count must be greater than zero.\n",stderr);
						usage();
					}
					break;
				default:
					if (!isdigit(argv[cnt][1]) || bytecnt)
						usage();
D 4
					if ((numlines = atol(argv[cnt] + 2)) <= 0) {
E 4
I 4
					if ((numlines = atol(argv[cnt] + 1)) <= 0) {
E 4
						fputs("split: line count must be greater than zero.\n",stderr);
						usage();
					}
					break;
E 5
I 5
			case 0:		/* stdin by request */
				if (ifd != ERR)
					usage();
				ifd = 0;
				break;
			case 'b':	/* byte count split */
				if (numlines)
					usage();
				if (!argv[cnt][2])
					bytecnt = atol(argv[++cnt]);
E 10
I 10
	while ((ch = getopt(argc, argv, "-0123456789b:l:")) != EOF)
		switch (ch) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			/*
			 * Undocumented kludge: split was originally designed
			 * to take a number after a dash.
			 */
			if (numlines == 0) {
				p = argv[optind - 1];
				if (p[0] == '-' && p[1] == ch && !p[2])
					numlines = strtol(++p, &ep, 10);
E 10
				else
D 10
					bytecnt = atol(argv[cnt] + 2);
				if (bytecnt <= 0) {
					fputs("split: byte count must be greater than zero.\n", stderr);
					usage();
				}
				break;
			default:
				if (!isdigit(argv[cnt][1]) || bytecnt)
					usage();
				if ((numlines = atol(argv[cnt] + 1)) <= 0) {
					fputs("split: line count must be greater than zero.\n", stderr);
					usage();
				}
				break;
E 10
I 10
					numlines =
					    strtol(argv[optind] + 1, &ep, 10);
				if (numlines <= 0 || *ep)
					errx(1,
					    "%s: illegal line count.", optarg);
E 10
E 5
E 3
			}
D 3
		else if(iflg)
			ofil = argv[i];
		else {
			ifil = argv[i];
			iflg = 2;
E 3
I 3
D 10
		else if (ifd == ERR) {		/* input file */
D 5
			if ((ifd = open(argv[cnt],O_RDONLY,0)) < 0) {
E 5
I 5
			if ((ifd = open(argv[cnt], O_RDONLY, 0)) < 0) {
E 5
				perror(argv[cnt]);
D 7
				exit(ERREXIT);
E 7
I 7
				exit(1);
E 7
			}
E 3
		}
D 3
	if(iflg != 2)
		is = stdin;
	else
		if((is=fopen(ifil,"r")) == NULL) {
D 2
			fprintf(stderr,"cannot open input\n");
E 2
I 2
			perror(ifil);
E 2
			exit(1);
E 3
I 3
		else if (!*fname)		/* output file prefix */
D 5
			strcpy(fname,argv[cnt]);
E 5
I 5
			strcpy(fname, argv[cnt]);
E 5
		else
E 10
I 10
			break;
		case '-':		/* Undocumented: historic stdin flag. */
			if (ifd != -1)
				usage();
			ifd = 0;
			break;
		case 'b':		/* Byte count. */
			if ((bytecnt = strtol(optarg, &ep, 10)) <= 0 ||
			    *ep != '\0' && *ep != 'k' && *ep != 'm')
				errx(1, "%s: illegal byte count.", optarg);
			if (*ep == 'k')
				bytecnt *= 1024;
			else if (*ep == 'm')
				bytecnt *= 1048576;
			break;
		case 'l':		/* Line count. */
			if (numlines != 0)
				usage();
D 12
			if ((numlines = strtol(optarg, &ep, 10)) <= 0 || *p)
E 12
I 12
			if ((numlines = strtol(optarg, &ep, 10)) <= 0 || *ep)
E 12
				errx(1, "%s: illegal line count.", optarg);
			break;
		default:
E 10
			usage();
D 10
	}
	if (ifd == ERR)				/* stdin by default */
E 10
I 10
		}
	argv += optind;
	argc -= optind;

	if (*argv != NULL)
		if (ifd == -1) {		/* Input file. */
			if ((ifd = open(*argv, O_RDONLY, 0)) < 0)
				err(1, "%s", *argv);
			++argv;
		}
	if (*argv != NULL)			/* File name prefix. */
		(void)strcpy(fname, *argv++);
	if (*argv != NULL)
		usage();

	if (numlines == 0)
		numlines = DEFLINE;
	else if (bytecnt)
		usage();

	if (ifd == -1)				/* Stdin by default. */
E 10
		ifd = 0;
D 10
	if (bytecnt)
E 10
I 10

	if (bytecnt) {
E 10
		split1();
D 10
	if (!numlines)
		numlines = DEFLINE;
E 10
I 10
		exit (0);
	}
E 10
	split2();
I 7
	exit(0);
E 7
}

/*
 * split1 --
D 10
 *	split by bytes
E 10
I 10
 *	Split the input by bytes.
E 10
 */
I 10
void
E 10
D 7
static
E 7
split1()
{
D 7
	register long	bcnt;		/* byte counter */
	register int	dist,		/* buffer offset */
			len;		/* read length */
	register char	*C;		/* tmp pointer into buffer */
E 7
I 7
D 10
	register long bcnt;
	register int dist, len;
	register char *C;
E 10
I 10
	long bcnt;
	int dist, len;
	char *C;
E 10
E 7

	for (bcnt = 0;;)
D 5
		switch(len = read(ifd,bfr,MAXBSIZE)) {
			case 0:
				exit(OK);
			case ERR:
				perror("read");
				exit(ERREXIT);
			default:
				if (!file_open) {
E 5
I 5
D 10
		switch(len = read(ifd, bfr, MAXBSIZE)) {
E 10
I 10
		switch (len = read(ifd, bfr, MAXBSIZE)) {
E 10
		case 0:
D 10
			exit(OK);
		case ERR:
			perror("read");
D 7
			exit(ERREXIT);
E 7
I 7
			exit(1);
E 10
I 10
			exit(0);
		case -1:
			err(1, "read");
			/* NOTREACHED */
E 10
E 7
		default:
			if (!file_open) {
				newfile();
D 10
				file_open = YES;
E 10
I 10
				file_open = 1;
E 10
			}
			if (bcnt + len >= bytecnt) {
				dist = bytecnt - bcnt;
D 7
				write(ofd, bfr, dist);
E 7
I 7
				if (write(ofd, bfr, dist) != dist)
D 10
					wrerror();
E 10
I 10
					err(1, "write");
E 10
E 7
				len -= dist;
D 10
				for (C = bfr + dist; len >= bytecnt; len -= bytecnt, C += bytecnt) {
E 10
I 10
				for (C = bfr + dist; len >= bytecnt;
				    len -= bytecnt, C += bytecnt) {
E 10
E 5
					newfile();
D 5
					file_open = YES;
E 5
I 5
D 7
					write(ofd, C, (int)bytecnt);
E 7
I 7
D 10
					if (write(ofd, C, (int)bytecnt) != bytecnt)
						wrerror();
E 10
I 10
					if (write(ofd,
					    C, (int)bytecnt) != bytecnt)
						err(1, "write");
E 10
E 7
E 5
				}
D 5
				if (bcnt + len >= bytecnt) {
					dist = bytecnt - bcnt;
					write(ofd,bfr,dist);
					len -= dist;
					for (C = bfr + dist;len >= bytecnt;len -= bytecnt,C += bytecnt) {
						newfile();
						write(ofd,C,(int)bytecnt);
					}
					if (len) {
						newfile();
						write(ofd,C,len);
					}
					else
						file_open = NO;
					bcnt = len;
E 5
I 5
				if (len) {
					newfile();
D 7
					write(ofd, C, len);
E 7
I 7
					if (write(ofd, C, len) != len)
D 10
						wrerror();
E 7
E 5
				}
D 5
				else {
					bcnt += len;
					write(ofd,bfr,len);
				}
E 5
I 5
				else
					file_open = NO;
E 10
I 10
						err(1, "write");
				} else
					file_open = 0;
E 10
				bcnt = len;
D 10
			}
			else {
E 10
I 10
			} else {
E 10
				bcnt += len;
D 7
				write(ofd, bfr, len);
E 7
I 7
				if (write(ofd, bfr, len) != len)
D 10
					wrerror();
E 10
I 10
					err(1, "write");
E 10
E 7
			}
E 5
E 3
		}
D 3
	if(ofil == 0)
		ofil = "x";
E 3
I 3
}
E 3

D 3
loop:
	f = 1;
	for(i=0; i<count; i++)
	do {
		c = getc(is);
		if(c == EOF) {
			if(f == 0)
				fclose(os);
			exit(0);
E 3
I 3
/*
 * split2 --
D 10
 *	split by lines
E 10
I 10
 *	Split the input by lines.
E 10
 */
I 10
void
E 10
D 7
static
E 7
split2()
{
D 7
	register char	*Ce,			/* start/end pointers */
			*Cs;
	register long	lcnt;			/* line counter */
	register int	len;			/* read length */
E 7
I 7
D 10
	register char *Ce, *Cs;
	register long lcnt;
	register int len, bcnt;
E 10
I 10
	long lcnt;
	int len, bcnt;
	char *Ce, *Cs;
E 10
E 7

	for (lcnt = 0;;)
D 5
		switch(len = read(ifd,bfr,MAXBSIZE)) {
			case 0:
				exit(0);
			case ERR:
				perror("read");
				break;
			default:
				if (!file_open) {
					newfile();
					file_open = YES;
E 5
I 5
D 10
		switch(len = read(ifd, bfr, MAXBSIZE)) {
E 10
I 10
		switch (len = read(ifd, bfr, MAXBSIZE)) {
E 10
		case 0:
			exit(0);
D 10
		case ERR:
			perror("read");
D 7
			break;
E 7
I 7
			exit(1);
E 10
I 10
		case -1:
			err(1, "read");
			/* NOTREACHED */
E 10
E 7
		default:
			if (!file_open) {
				newfile();
D 10
				file_open = YES;
E 10
I 10
				file_open = 1;
E 10
			}
			for (Cs = Ce = bfr; len--; Ce++)
				if (*Ce == '\n' && ++lcnt == numlines) {
D 7
					write(ofd, Cs, (int)(Ce - Cs) + 1);
E 7
I 7
					bcnt = Ce - Cs + 1;
					if (write(ofd, Cs, bcnt) != bcnt)
D 10
						wrerror();
E 10
I 10
						err(1, "write");
E 10
E 7
					lcnt = 0;
					Cs = Ce + 1;
					if (len)
						newfile();
					else
D 10
						file_open = NO;
E 10
I 10
						file_open = 0;
E 10
E 5
				}
D 5
				for (Cs = Ce = bfr;len--;Ce++)
					if (*Ce == '\n' && ++lcnt == numlines) {
						write(ofd,Cs,(int)(Ce - Cs) + 1);
						lcnt = 0;
						Cs = Ce + 1;
						if (len)
							newfile();
						else
							file_open = NO;
					}
				if (Cs < Ce)
					write(ofd,Cs,(int)(Ce - Cs));
E 5
I 5
D 7
			if (Cs < Ce)
				write(ofd, Cs, (int)(Ce - Cs));
E 7
I 7
			if (Cs < Ce) {
				bcnt = Ce - Cs;
				if (write(ofd, Cs, bcnt) != bcnt)
D 10
					wrerror();
E 10
I 10
					err(1, "write");
E 10
			}
E 7
E 5
E 3
		}
D 3
		if(f) {
			for(f=0; ofil[f]; f++)
				fname[f] = ofil[f];
			fname[f++] = fnumber/26 + 'a';
			fname[f++] = fnumber%26 + 'a';
			fname[f] = '\0';
			fnumber++;
			if((os=fopen(fname,"w")) == NULL) {
				fprintf(stderr,"Cannot create output\n");
				exit(1);
			}
			f = 0;
E 3
I 3
}

/*
 * newfile --
D 10
 *	open a new file
E 10
I 10
 *	Open a new output file.
E 10
 */
I 10
void
E 10
D 7
static
E 7
newfile()
{
D 7
	static long	fnum;		/* file name counter */
	static short	defname;	/* using default name, "x" */
	static char	*fpnt;		/* output file name pointer */
E 7
I 7
	static long fnum;
D 10
	static short defname;
E 10
I 10
	static int defname;
E 10
	static char *fpnt;
E 7

D 10
	if (ofd == ERR) {
		if (fname[0]) {
			fpnt = fname + strlen(fname);
			defname = NO;
E 3
		}
D 3
		putc(c, os);
	} while(c != '\n');
	fclose(os);
	goto loop;
E 3
I 3
		else {
E 10
I 10
	if (ofd == -1) {
		if (fname[0] == '\0') {
E 10
			fname[0] = 'x';
			fpnt = fname + 1;
D 10
			defname = YES;
E 10
I 10
			defname = 1;
		} else {
			fpnt = fname + strlen(fname);
			defname = 0;
E 10
		}
		ofd = fileno(stdout);
	}
	/*
D 10
	 * hack to increase max files; original code just wandered through
E 10
I 10
	 * Hack to increase max files; original code wandered through
E 10
	 * magic characters.  Maximum files is 3 * 26 * 26 == 2028
	 */
#define MAXFILES	676
	if (fnum == MAXFILES) {
D 10
		if (!defname || fname[0] == 'z') {
D 5
			fputs("split: too many files.\n",stderr);
E 5
I 5
			fputs("split: too many files.\n", stderr);
E 5
D 7
			exit(ERREXIT);
E 7
I 7
			exit(1);
E 7
		}
E 10
I 10
		if (!defname || fname[0] == 'z')
			errx(1, "too many files.");
E 10
		++fname[0];
		fnum = 0;
	}
	fpnt[0] = fnum / 26 + 'a';
	fpnt[1] = fnum % 26 + 'a';
	++fnum;
D 5
	if (!freopen(fname,"w",stdout)) {
		fprintf(stderr,"split: unable to write to %s.\n",fname);
E 5
I 5
D 10
	if (!freopen(fname, "w", stdout)) {
		fprintf(stderr, "split: unable to write to %s.\n", fname);
E 5
		exit(ERR);
	}
E 10
I 10
	if (!freopen(fname, "w", stdout))
		err(1, "%s", fname);
E 10
}

D 10
/*
 * usage --
 *	print usage message and die
 */
E 10
I 10
void
E 10
D 7
static
E 7
usage()
{
D 5
	fputs("usage: split [-] [-#] [-b byte_count] [file [prefix]]\n",stderr);
E 5
I 5
D 10
	fputs("usage: split [-] [-#] [-b byte_count] [file [prefix]]\n", stderr);
E 5
D 7
	exit(ERREXIT);
E 7
I 7
	exit(1);
}

/*
 * wrerror --
 *	write error
 */
wrerror()
{
	perror("split: write");
E 10
I 10
	(void)fprintf(stderr,
"usage: split [-b byte_count] [-l line_count] [file [prefix]]\n");
E 10
	exit(1);
E 7
E 3
}
E 1
