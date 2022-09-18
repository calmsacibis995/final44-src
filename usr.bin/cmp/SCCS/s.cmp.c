h15743
s 00002/00002/00118
d D 8.3 94/04/02 10:06:52 pendry 22 21
c add 1994 copyright
e
s 00014/00009/00106
d D 8.2 94/04/01 07:42:20 pendry 21 20
c prettyness police
e
s 00005/00005/00110
d D 8.1 93/06/06 14:27:48 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00114
d D 5.6 91/10/28 16:10:07 bostic 19 18
c fix usage message
e
s 00048/00200/00067
d D 5.5 91/10/27 14:15:16 bostic 18 17
c POSIX P1003.2/D11.2 compliance -- use mmap and make it simple
e
s 00072/00054/00195
d D 5.4 91/07/18 14:47:50 bostic 17 16
c ANSI; document skip1, skip2 args; use strtol, don't roll our own
c change "char" to "byte" in output message; minor cleanups
e
s 00001/00011/00248
d D 5.3 90/06/01 16:46:19 bostic 16 15
c new copyright notice
e
s 00035/00034/00224
d D 5.2 90/05/10 16:44:08 karels 15 14
c move EOF message back to stdout; something more like Berkeley format
e
s 00059/00057/00199
d D 5.1 89/02/15 11:35:48 bostic 14 13
c fix '-' parsing; make -l, -s mutually exclusive, KNF cleanups
e
s 00014/00009/00242
d D 4.9 88/06/18 13:19:18 bostic 13 12
c install approved copyright notice
e
s 00001/00001/00250
d D 4.8 87/12/21 12:37:45 bostic 12 11
c make ANSI C compatible
e
s 00008/00002/00243
d D 4.7 87/11/24 15:54:48 bostic 11 9
c Berkeley code, fix copyright
e
s 00010/00004/00241
d R 4.7 87/11/24 15:51:00 bostic 10 9
c Berkeley code; correct copyright
e
s 00106/00090/00139
d D 4.6 87/11/23 19:16:29 bostic 9 8
c fixes from guy@sun.com; better error messages/checking; fix usage 
c message to be on stderr a la S5; reformat to Berkeley standard
e
s 00027/00014/00202
d D 4.5 87/11/18 16:47:18 bostic 8 6
c add real header; make -s as fast as -l; minor reformatting
e
s 00015/00001/00215
d R 4.5 87/11/18 16:35:18 bostic 7 6
c add real header
e
s 00001/00001/00215
d D 4.4 87/03/12 17:06:01 bostic 6 5
c added newline to usage
e
s 00194/00100/00022
d D 4.3 86/12/11 06:24:06 bostic 5 2
c general speedups with larger buffers and bcmp
e
s 00001/00001/00121
d D 4.2 83/04/29 00:52:15 mckusick 2 1
c added perror
e
s 00122/00000/00000
d D 4.1 80/10/01 17:25:39 bill 1 0
c date and time created 80/10/01 17:25:39 by bill
e
u
U
t
T
I 1
D 8
static char *sccsid = "%W% (Berkeley) %G%";
E 8
I 8
/*
D 13
 * Copyright (c) 1987 Regents of the University of California.
E 13
I 13
D 20
 * Copyright (c) 1987 Regents of the University of California.
E 13
D 11
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
 * All rights reserved.
E 20
I 20
D 22
 * Copyright (c) 1987, 1990, 1993
E 22
I 22
 * Copyright (c) 1987, 1990, 1993, 1994
E 22
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 16
 * Redistribution and use in source and binary forms are permitted
D 13
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 13
I 13
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
E 16
I 16
 * %sccs.include.redist.c%
E 16
E 13
E 11
 */
E 8
I 5

I 8
#ifndef lint
D 20
char copyright[] =
D 13
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 13
I 13
D 15
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 15
I 15
"%Z% Copyright (c) 1987, 1990 Regents of the University of California.\n\
E 15
E 13
 All rights reserved.\n";
E 20
I 20
static char copyright[] =
D 22
"%Z% Copyright (c) 1987, 1990, 1993\n\
E 22
I 22
"%Z% Copyright (c) 1987, 1990, 1993, 1994\n\
E 22
	The Regents of the University of California.  All rights reserved.\n";
E 20
D 13
#endif /* !lint */
E 13
I 13
#endif /* not lint */
E 13

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 13
#endif /* !lint */
E 13
I 13
#endif /* not lint */
E 13

E 8
D 18
#include <sys/param.h>
E 18
I 18
#include <sys/types.h>
E 18
D 17
#include <sys/file.h>
E 17
#include <sys/stat.h>
I 21

#include <err.h>
E 21
I 17
#include <fcntl.h>
D 21
#include <errno.h>
#include <unistd.h>
E 21
E 17
E 5
#include <stdio.h>
I 17
#include <stdlib.h>
#include <string.h>
I 21
#include <unistd.h>

E 21
E 17
D 18
#include <ctype.h>
E 18
I 18
#include "extern.h"
E 18
I 9
D 17
#include <errno.h>
E 17
E 9

D 5
FILE	*file1,*file2;
int	eflg;
int	lflg	= 1;
long	line	= 1;
long	chr	= 0;
long	skip1;
long	skip2;
E 5
I 5
D 14
#define DIFF	1			/* found differences */
#define ERR	2			/* error during run */
#define NO	0			/* no/false */
#define OK	0			/* didn't find differences */
#define YES	1			/* yes/true */
E 14
I 14
D 18
#define	EXITNODIFF	0
#define	EXITDIFF	1
#define	EXITERR		2
E 18
I 18
int	lflag, sflag;
E 18
E 14
E 5

D 5
long	otoi();
E 5
I 5
D 9
static int	fd1,			/* descriptor, file 1 */
		fd2,			/* descriptor, file 2 */
E 9
I 9
D 12
static int	fd1, fd2;		/* file descriptors */
E 12
I 12
D 14
static int	fd1, fd2,		/* file descriptors */
E 12
E 9
D 8
		silent = NO;		/* if silent on error */
E 8
I 8
		silent = NO;		/* if silent run */
E 8
static short	all = NO;		/* if report all differences */
D 9
static	u_char	buf1[MAXBSIZE],		/* read buffers */
E 9
I 9
static u_char	buf1[MAXBSIZE],		/* read buffers */
E 9
		buf2[MAXBSIZE];
D 9
static char	*file1,			/* name, file 1 */
		*file2;			/* name, file 2 */
E 9
I 9
static char	*file1, *file2;		/* file names */
E 14
I 14
D 15
static int	all, fd1, fd2, silent;
static u_char	buf1[MAXBSIZE], buf2[MAXBSIZE];
static char	*file1, *file2;
E 15
I 15
D 18
int	all, fd1, fd2, silent;
u_char	buf1[MAXBSIZE], buf2[MAXBSIZE];
char	*file1, *file2;
E 18
I 18
static void usage __P((void));
E 18
E 15
E 14
E 9
E 5

I 21
int
E 21
I 17
D 18
void cmp __P((void));
void endoffile __P((char *));
void err __P((const char *fmt, ...));
void ferr __P((char *));
void skip __P((u_long, int, char *));
void usage __P((void));

E 18
E 17
D 5
main(argc, argv)
char **argv;
E 5
I 5
D 9
main(argc,argv)
int	argc;
char	**argv;
E 9
I 9
main(argc, argv)
D 14
	int	argc;
	char	**argv;
E 14
I 14
	int argc;
D 15
	char **argv;
E 15
I 15
	char *argv[];
E 15
E 14
E 9
E 5
{
D 5
	register c1, c2;
	char *arg;
E 5
I 5
D 9
	extern char	*optarg;	/* getopt externals */
E 9
I 9
D 14
	extern char	*optarg;
E 9
	extern int	optind;
D 9
	int	ch;			/* arguments */
E 9
I 9
	int	ch;
E 9
	u_long	otoi();
E 14
I 14
D 17
	extern char *optarg;
	extern int optind;
E 17
D 18
	int ch;
E 18
I 18
	struct stat sb1, sb2;
	off_t skip1, skip2;
	int ch, fd1, fd2, special;
	char *file1, *file2;
E 18
D 17
	u_long otoi();
E 17
E 14
E 5

D 5
	if(argc < 3)
		goto narg;
	arg = argv[1];
	if(arg[0] == '-' && arg[1] == 's') {
		lflg--;
		argv++;
		argc--;
E 5
I 5
D 9
	while ((ch = getopt(argc,argv,"ls")) != EOF)
E 9
I 9
D 14
	while ((ch = getopt(argc, argv, "ls")) != EOF)
E 14
I 14
	while ((ch = getopt(argc, argv, "-ls")) != EOF)
E 14
E 9
D 15
		switch(ch) {
E 15
I 15
		switch (ch) {
E 15
D 9
			case 'l':		/* print all differences */
				all = YES;
				break;
D 8
			case 's':		/* silent return */
E 8
I 8
			case 's':		/* silent run */
E 8
				silent = YES;
				break;
			case '?':
			default:
				usage();
E 9
I 9
		case 'l':		/* print all differences */
D 14
			all = YES;
E 14
I 14
D 18
			all = 1;
E 18
I 18
			lflag = 1;
E 18
E 14
			break;
		case 's':		/* silent run */
D 14
			silent = YES;
E 14
I 14
D 18
			silent = 1;
E 18
I 18
			sflag = 1;
E 18
E 14
			break;
I 14
D 18
		case '-':		/* must be after any flags */
E 18
I 18
		case '-':		/* stdin (must be after options) */
E 18
			--optind;
			goto endargs;
E 14
		case '?':
		default:
			usage();
E 9
		}
I 14
endargs:
E 14
	argv += optind;
	argc -= optind;

I 18
	if (lflag && sflag)
D 21
		err("only one of -l and -s may be specified");
E 21
I 21
		errx(ERR_EXIT, "only one of -l and -s may be specified");
E 21

E 18
	if (argc < 2 || argc > 4)
		usage();

D 14
	/* open up files; "-" is stdin */
	file1 = argv[0];
D 9
	if (strcmp(file1,"-") && (fd1 = open(file1,O_RDONLY)) < 0) {
		if (!silent)
			perror(file1);
		exit(ERR);
E 5
	}
E 9
I 9
	if (strcmp(file1, "-") && (fd1 = open(file1, O_RDONLY, 0)) < 0)
E 14
I 14
D 17
	if (all && silent) {
		fprintf(stderr,
		    "cmp: only one of -l and -s may be specified.\n");
		exit(EXITERR);
	}
E 17
I 17
D 18
	if (all && silent)
		err("only one of -l and -s may be specified");
E 17
D 15
	if (!strcmp(file1 = argv[0], "-"))
E 15
I 15
	if (strcmp(file1 = argv[0], "-") == 0)
E 18
I 18
	/* Backward compatibility -- handle "-" meaning stdin. */
	special = 0;
	if (strcmp(file1 = argv[0], "-") == 0) {
		special = 1;
E 18
E 15
		fd1 = 0;
I 18
		file1 = "stdin";
	}
E 18
	else if ((fd1 = open(file1, O_RDONLY, 0)) < 0)
E 14
D 17
		error(file1);
E 17
I 17
D 18
		ferr(file1);
E 17
E 9
D 5
	arg = argv[1];
	if(arg[0] == '-' && arg[1] == 'l') {
		lflg++;
		argv++;
		argc--;
E 5
I 5
D 14
	file2 = argv[1];
D 9
	if ((fd2 = open(file2,O_RDONLY)) < 0) {
		if (!silent)
			perror(file2);
		exit(ERR);
E 5
	}
E 9
I 9
	if ((fd2 = open(file2, O_RDONLY, 0)) < 0)
E 14
I 14
D 15
	if (!strcmp(file2 = argv[1], "-"))
E 15
I 15
	if (strcmp(file2 = argv[1], "-") == 0)
E 18
I 18
D 21
		err("%s: %s", file1, strerror(errno));
E 21
I 21
		err(ERR_EXIT, "%s", file1);
E 21
	if (strcmp(file2 = argv[1], "-") == 0) {
		if (special)
D 21
			err("standard input may only be specified once");
E 21
I 21
			errx(ERR_EXIT,
				"standard input may only be specified once");
E 21
		special = 1;
E 18
E 15
		fd2 = 0;
I 18
		file2 = "stdin";
	}
E 18
	else if ((fd2 = open(file2, O_RDONLY, 0)) < 0)
E 14
D 17
		error(file2);
I 14
	if (fd1 == fd2) {
		fprintf(stderr,
		    "cmp: standard input may only be specified once.\n");
		exit(EXITERR);
	}
E 17
I 17
D 18
		ferr(file2);
	if (fd1 == fd2)
		err("standard input may only be specified once");
E 18
I 18
D 21
		err("%s: %s", file2, strerror(errno));
E 21
I 21
		err(ERR_EXIT, "%s", file2);
E 21
E 18
E 17
E 14
E 9
D 5
	if(argc < 3)
		goto narg;
	arg = argv[1];
	if( arg[0]=='-' && arg[1]==0 )
		file1 = stdin;
	else if((file1 = fopen(arg, "r")) == NULL)
		goto barg;
	arg = argv[2];
	if((file2 = fopen(arg, "r")) == NULL)
		goto barg;
	if (argc>3)
		skip1 = otoi(argv[3]);
	if (argc>4)
		skip2 = otoi(argv[4]);
	while (skip1) {
		if ((c1 = getc(file1)) == EOF) {
			arg = argv[1];
			goto earg;
		}
		skip1--;
E 5
I 5

D 18
	/* handle skip arguments */
	if (argc > 2) {
D 9
		skip(otoi(argv[2]),fd1,file1);
E 9
I 9
D 17
		skip(otoi(argv[2]), fd1, file1);
E 17
I 17
		skip(strtol(argv[2], NULL, 10), fd1, file1);
E 17
E 9
		if (argc == 4)
D 9
			skip(otoi(argv[3]),fd2,file2);
E 9
I 9
D 17
			skip(otoi(argv[3]), fd2, file2);
E 17
I 17
			skip(strtol(argv[3], NULL, 10), fd2, file2);
E 17
E 9
E 5
	}
D 5
	while (skip2) {
		if ((c2 = getc(file2)) == EOF) {
			arg = argv[2];
			goto earg;
E 5
I 5
	cmp();
I 9
D 17
	/*NOTREACHED*/
E 17
I 17
	/* NOTREACHED */
E 17
E 9
}
E 18
I 18
	skip1 = argc > 2 ? strtol(argv[2], NULL, 10) : 0;
	skip2 = argc == 4 ? strtol(argv[3], NULL, 10) : 0;
E 18

D 18
/*
 * skip --
 *	skip first part of file
 */
I 17
void
E 17
D 15
static
E 15
D 9
skip(dist,fd,fname)
register u_long	dist;			/* length in bytes, to skip */
register int	fd;			/* file descriptor */
char	*fname;				/* file name for error */
E 9
I 9
skip(dist, fd, fname)
D 14
	register u_long	dist;		/* length in bytes, to skip */
	register int	fd;		/* file descriptor */
	char	*fname;			/* file name for error */
E 14
I 14
	register u_long dist;
	register int fd;
	char *fname;
E 14
E 9
{
D 14
	register int	rlen;		/* read length */
I 9
	register int	nread;
E 14
I 14
	register int rlen, nread;
E 14
E 9

D 9
	for (;dist;dist -= rlen) {
		rlen = MIN(dist,sizeof(buf1));
		if (read(fd,buf1,rlen) != rlen) {
			if (!silent)
				printf("cmp: EOF on %s\n",fname);
			exit(DIFF);
E 9
I 9
	for (; dist; dist -= rlen) {
		rlen = MIN(dist, sizeof(buf1));
		if ((nread = read(fd, buf1, rlen)) != rlen) {
			if (nread < 0)
D 17
				error(fname);
E 17
I 17
				ferr(fname);
E 17
			else
				endoffile(fname);
E 18
I 18
	if (!special) {
		if (fstat(fd1, &sb1))
D 21
			err("%s: %s", file1, strerror(errno));
E 21
I 21
			err(ERR_EXIT, "%s", file1);
E 21
		if (!S_ISREG(sb1.st_mode))
			special = 1;
		else {
			if (fstat(fd2, &sb2))
D 21
				err("%s: %s", file2, strerror(errno));
E 21
I 21
				err(ERR_EXIT, "%s", file2);
E 21
			if (!S_ISREG(sb2.st_mode))
				special = 1;
E 18
E 9
E 5
		}
D 5
		skip2--;
E 5
	}
I 5
D 18
}
E 18
E 5

I 17
D 18
void
E 17
D 5
loop:
	chr++;
	c1 = getc(file1);
	c2 = getc(file2);
	if(c1 == c2) {
		if (c1 == '\n')
			line++;
		if(c1 == EOF) {
			if(eflg)
				exit(1);
			exit(0);
E 5
I 5
D 15
static
E 15
cmp()
{
D 9
	register u_char	*C1,		/* traveling pointers */
			*C2;
E 9
I 9
D 14
	register u_char	*C1, *C2;	/* traveling pointers */
E 9
	register int	cnt,		/* counter */
D 9
			len1,		/* read length 1 */
			len2;		/* read length 2 */
E 9
I 9
			len1, len2;	/* read lengths */
E 9
	register long	byte,		/* byte count */
			line;		/* line count */
	short	dfound = NO;		/* if difference found */
E 14
I 14
D 15
	register u_char	*C1, *C2;
E 15
I 15
	register u_char	*p1, *p2;
E 15
	register int cnt, len1, len2;
	register long byte, line;
	int dfound = 0;
E 14

D 9
	for (byte = 0,line = 1;;) {
		switch(len1 = read(fd1,buf1,MAXBSIZE)) {
			case -1:
				if (!silent)
					perror(file1);
				exit(ERR);
			case 0:
				/*
				 * read of file 1 just failed, find out
				 * if there's anything left in file 2
				 */
				switch(read(fd2,buf2,1)) {
					case -1:
						if (!silent)
							perror(file2);
						exit(ERR);
					case 0:
						exit(dfound ? DIFF : OK);
					default:
						if (!silent)
							printf("cmp: EOF on %s\n",file1);
						exit(DIFF);
				}
E 9
I 9
D 15
	for (byte = 0, line = 1;;) {
		switch(len1 = read(fd1, buf1, MAXBSIZE)) {
E 15
I 15
	for (byte = 0, line = 1; ; ) {
		switch (len1 = read(fd1, buf1, MAXBSIZE)) {
E 15
		case -1:
D 17
			error(file1);
E 17
I 17
			ferr(file1);
E 17
		case 0:
			/*
			 * read of file 1 just failed, find out
			 * if there's anything left in file 2
			 */
D 15
			switch(read(fd2, buf2, 1)) {
E 15
I 15
			switch (read(fd2, buf2, 1)) {
E 15
				case -1:
D 17
					error(file2);
E 17
I 17
					ferr(file2);
E 17
I 15
					/* NOTREACHED */
E 15
				case 0:
D 14
					exit(dfound ? DIFF : OK);
E 14
I 14
					exit(dfound ? EXITDIFF : EXITNODIFF);
I 15
					/* NOTREACHED */
E 15
E 14
				default:
					endoffile(file1);
I 15
					break;
E 15
			}
E 9
E 5
		}
D 5
		goto loop;
E 5
I 5
		/*
		 * file1 might be stdio, which means that a read of less than
		 * MAXBSIZE might not mean an EOF.  So, read whatever we read
		 * from file1 from file2.
		 */
D 9
		if ((len2 = read(fd2,buf2,len1)) == -1)  {
			if (!silent)
				perror(file2);
			exit(ERR);
		}
		if (bcmp(buf1,buf2,len2)) {
E 9
I 9
		if ((len2 = read(fd2, buf2, len1)) == -1)
D 17
			error(file2);
E 17
I 17
			ferr(file2);
E 17
		if (bcmp(buf1, buf2, len2)) {
E 9
			if (silent)
D 14
				exit(DIFF);
E 14
I 14
				exit(EXITDIFF);
E 14
			if (all) {
D 14
				dfound = YES;
E 14
I 14
				dfound = 1;
E 14
D 9
				for (C1 = buf1,C2 = buf2,cnt = len2;cnt--;++C1,++C2) {
E 9
I 9
D 15
				for (C1 = buf1, C2 = buf2, cnt = len2; cnt--; ++C1, ++C2) {
E 15
I 15
				for (p1 = buf1, p2 = buf2, cnt = len2; cnt--;
				    ++p1, ++p2) {
E 15
E 9
					++byte;
D 15
					if (*C1 != *C2)
D 9
						printf("%6ld %3o %3o\n",byte,*C1,*C2);
E 9
I 9
						printf("%6ld %3o %3o\n", byte, *C1, *C2);
E 15
I 15
					if (*p1 != *p2)
						printf("%6ld %3o %3o\n",
						    byte, *p1, *p2);
E 15
E 9
				}
D 14
			}
D 8
			else
				for (C1 = buf1,C2 = buf2;;++C1,++C2) {
					++byte;
					if (*C1 != *C2) {
						printf("%s %s differ: char %ld, line %ld\n",file1,file2,byte,line);
						exit(DIFF);
					}
					if (*C1 == '\n')
						++line;
E 8
I 8
D 9
			else for (C1 = buf1,C2 = buf2;;++C1,++C2) {
E 9
I 9
			else for (C1 = buf1, C2 = buf2;; ++C1, ++C2) {
E 14
I 14
D 15
			} else for (C1 = buf1, C2 = buf2;; ++C1, ++C2) {
E 15
I 15
			} else for (p1 = buf1, p2 = buf2; ; ++p1, ++p2) {
E 15
E 14
E 9
				++byte;
D 15
				if (*C1 != *C2) {
E 15
I 15
				if (*p1 != *p2) {
E 15
D 9
					printf("%s %s differ: char %ld, line %ld\n",file1,file2,byte,line);
E 9
I 9
D 17
					printf("%s %s differ: char %ld, line %ld\n", file1, file2, byte, line);
E 17
I 17
					printf("%s %s differ: byte %ld, line %ld\n",
					    file1, file2, byte, line);
E 17
E 9
D 14
					exit(DIFF);
E 14
I 14
					exit(EXITDIFF);
E 14
E 8
				}
I 8
D 15
				if (*C1 == '\n')
E 15
I 15
				if (*p1 == '\n')
E 15
					++line;
			}
E 8
D 14
		}
		else {
E 14
I 14
		} else {
E 14
			byte += len2;
			/*
			 * here's the real performance problem, we've got to
			 * count the stupid lines, which means that -l is a
			 * *much* faster version, i.e., unless you really
D 8
			 * *want* to know the line number, run -sl.
E 8
I 8
			 * *want* to know the line number, run -s or -l.
E 8
			 */
D 8
			if (!all)
E 8
I 8
			if (!silent && !all)
E 8
D 9
				for (C1 = buf1,cnt = len2;cnt--;)
E 9
I 9
D 15
				for (C1 = buf1, cnt = len2; cnt--;)
E 9
					if (*C1++ == '\n')
E 15
I 15
				for (p1 = buf1, cnt = len2; cnt--; )
					if (*p1++ == '\n')
E 15
						++line;
		}
		/*
		 * couldn't read as much from file2 as from file1; checked
		 * here because there might be a difference before we got
		 * to this point, which would have precedence.
		 */
D 9
		if (len2 < len1) {
			if (!silent)
				printf("cmp: EOF on %s\n",file2);
			exit(DIFF);
		}
E 9
I 9
		if (len2 < len1)
			endoffile(file2);
E 9
E 5
	}
E 18
I 18
	if (special)
		c_special(fd1, file1, skip1, fd2, file2, skip2);
	else
		c_regular(fd1, file1, skip1, sb1.st_size,
		    fd2, file2, skip2, sb2.st_size);
	exit(0);
E 18
D 5
	if(lflg == 0)
		exit(1);
	if(c1 == EOF) {
		arg = argv[1];
		goto earg;
	}
	if(c2 == EOF)
		goto earg;
	if(lflg == 1) {
		printf("%s %s differ: char %ld, line %ld\n", argv[1], arg,
			chr, line);
		exit(1);
	}
	eflg = 1;
	printf("%6ld %3o %3o\n", chr, c1, c2);
	goto loop;
E 5
I 5
}
E 5

D 5
narg:
	printf("cmp: arg count\n");
	exit(2);
E 5
I 5
D 18
/*
D 17
 * otoi --
 *	octal/decimal string to u_long
E 17
I 17
 * ferr --
 *	print file error message and die
E 17
 */
D 15
static u_long
otoi(C)
D 9
register char	*C;		/* argument string */
E 9
I 9
D 14
	register char	*C;		/* argument string */
E 14
I 14
	register char *C;
E 15
I 15
D 17
u_long
otoi(s)
	register char *s;
E 17
I 17
void
ferr(name)
	char *name;
E 17
E 15
E 14
E 9
{
D 9
	register u_long	val;	/* return value */
	register int	base;	/* number base */
E 9
I 9
D 14
	register u_long	val;		/* return value */
	register int	base;		/* number base */
E 14
I 14
D 17
	register u_long val;
	register int base;
E 14
E 9
E 5

D 5
barg:
	if (lflg)
D 2
	printf("cmp: cannot open %s\n", arg);
E 2
I 2
	perror(arg);
E 2
	exit(2);

earg:
	printf("cmp: EOF on %s\n", arg);
	exit(1);
E 5
I 5
D 15
	base = (*C == '0') ? 8 : 10;
D 9
	for (val = 0;isdigit(*C);++C)
E 9
I 9
	for (val = 0; isdigit(*C); ++C)
E 9
		val = val * base + *C - '0';
	return(val);
E 15
I 15
	base = (*s == '0') ? 8 : 10;
	for (val = 0; isdigit(*s); ++s)
		val = val * base + *s - '0';
	return (val);
E 15
E 5
}

D 5
long otoi(s)
char *s;
E 5
I 5
/*
I 9
 * error --
 *	print I/O error message and die
 */
D 15
static
E 15
error(filename)
	char *filename;
{
	extern int errno;
D 14
	int sverrno;
E 14
I 14
	char *strerror();
E 14

E 17
D 14
	if (!silent) {
		sverrno = errno;
		(void)fprintf(stderr, "cmp: %s: ", filename);
		errno = sverrno;
		perror((char *)NULL);
	}
	exit(ERR);
E 14
I 14
	if (!silent)
D 15
		(void)fprintf(stderr, "cmp: %s: %s\n",
E 15
I 15
D 17
		(void) fprintf(stderr, "cmp: %s: %s\n",
E 15
		    filename, strerror(errno));
E 17
I 17
		err("%s: %s", name, strerror(errno));
E 17
	exit(EXITERR);
E 14
}

/*
 * endoffile --
 *	print end-of-file message and exit indicating the files were different
 */
I 17
void
E 17
D 15
static
E 15
endoffile(filename)
	char *filename;
{
D 17
	/* 32V put this message on stdout, S5 does it on stderr. */
I 15
	/* POSIX.2 currently does it on stdout-- Hooray! */
E 17
I 17
	/*
	 * 32V put this message on stdout, S5 does it on stderr.
	 * POSIX.2 currently does it on stdout -- Hooray!
	 */
E 17
E 15
	if (!silent)
D 15
		(void)fprintf(stderr, "cmp: EOF on %s\n", filename);
E 15
I 15
		(void) printf("cmp: EOF on %s\n", filename);
E 15
D 14
	exit(DIFF);
E 14
I 14
	exit(EXITDIFF);
E 14
}

/*
E 9
 * usage --
 *	print usage and die
 */
I 17
void
E 18
I 18
static void
E 18
E 17
D 15
static
E 15
usage()
E 5
{
I 21

E 21
D 5
	long v;
	int base;

	v = 0;
	base = 10;
	if (*s == '0')
		base = 8;
	while(isdigit(*s))
		v = v*base + *s++ - '0';
	return(v);
E 5
I 5
D 6
	fputs("usage: cmp [-ls] file1 file2 [skip1] [skip2]",stderr);
E 6
I 6
D 9
	fputs("usage: cmp [-ls] file1 file2 [skip1] [skip2]\n",stderr);
E 9
I 9
D 17
	fputs("usage: cmp [-ls] file1 file2 [skip1] [skip2]\n", stderr);
E 17
I 17
	(void)fprintf(stderr,
D 19
	    "usage: cmp [-ls] file1 file2 [skip1 [skip2]]\n");
E 19
I 19
	    "usage: cmp [-l | s] file1 file2 [skip1 [skip2]]\n");
E 19
E 17
E 9
E 6
D 14
	exit(ERR);
E 14
I 14
D 18
	exit(EXITERR);
I 17
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
	(void)fprintf(stderr, "cmp: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(EXITERR);
	/* NOTREACHED */
E 18
I 18
D 21
	exit(2);
E 21
I 21
	exit(ERR_EXIT);
E 21
E 18
E 17
E 14
E 5
}
E 1
