h18296
s 00001/00000/00160
d D 8.4 95/05/04 15:35:13 bostic 14 13
c optarg/optind moved to unistd.h
e
s 00002/00002/00158
d D 8.3 94/04/02 10:07:59 pendry 13 12
c add 1994 copyright
e
s 00016/00008/00144
d D 8.2 94/04/01 08:28:20 pendry 12 11
c prettyness police
e
s 00005/00005/00147
d D 8.1 93/06/06 14:28:51 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00004/00145
d D 5.8 91/07/26 14:19:53 bostic 10 9
c ANSI, minor cleanups
e
s 00002/00001/00147
d D 5.7 90/11/01 09:56:38 bostic 9 8
c initialize offset variables
e
s 00001/00001/00147
d D 5.6 90/10/30 09:29:17 bostic 8 7
c BSD_LINE_MAX -> POSIX2_LINE_MAX
e
s 00001/00001/00147
d D 5.5 90/06/25 16:47:28 bostic 7 6
c LINE_MAX -> _BSD_LINE_MAX
e
s 00001/00011/00147
d D 5.4 90/06/01 16:46:38 bostic 6 5
c new copyright notice
e
s 00006/00005/00152
d D 5.3 90/04/25 11:19:16 marc 5 4
c use LINE_MAX, don't hardwire 2048
e
s 00002/00002/00155
d D 5.2 90/04/25 11:13:49 marc 4 3
c New version wasn't flushing last file after first hit eof.
e
s 00129/00139/00028
d D 5.1 89/05/21 11:56:51 bostic 3 2
c from Case Larsen <laba-2ho@WEB.berkeley.edu>
c POSIX.2 compatible; yank to 5.1
e
s 00001/00001/00166
d D 4.2 83/04/29 01:46:29 mckusick 2 1
c added perror
e
s 00167/00000/00000
d D 4.1 80/10/01 17:25:50 bill 1 0
c date and time created 80/10/01 17:25:50 by bill
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
D 11
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
D 13
 * Copyright (c) 1989, 1993
E 13
I 13
 * Copyright (c) 1989, 1993, 1994
E 13
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * Case Larsen.
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */

#ifndef lint
D 11
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 11
I 11
static char copyright[] =
D 13
"%Z% Copyright (c) 1989, 1993\n\
E 13
I 13
"%Z% Copyright (c) 1989, 1993, 1994\n\
E 13
	The Regents of the University of California.  All rights reserved.\n";
E 11
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 10
#include <sys/file.h>
E 10
I 10
#include <fcntl.h>
E 10
I 5
#include <limits.h>
I 10
#include <errno.h>
E 10
E 5
E 3
#include <stdio.h>
I 10
#include <stdlib.h>
#include <string.h>
I 14
#include <unistd.h>
E 14
E 10
D 3
#define LB 256
int	one;
int	two;
int	three;
E 3

D 3
char	*ldr[3];
E 3
I 3
D 5
#define	MAXLINELEN	(2048 + 1)
E 5
I 5
D 7
#define	MAXLINELEN	(LINE_MAX + 1)
E 7
I 7
D 8
#define	MAXLINELEN	(_BSD_LINE_MAX + 1)
E 8
I 8
D 12
#define	MAXLINELEN	(_POSIX2_LINE_MAX + 1)
E 12
I 12
#define	MAXLINELEN	(LINE_MAX + 1)
E 12
E 8
E 7
E 5
E 3

D 3
FILE *ib1;
FILE *ib2;
FILE *openfil();
E 3
I 3
D 5
static char *tabs[] = { "", "\t", "\t\t" };
E 5
I 5
char *tabs[] = { "", "\t", "\t\t" };
E 5

E 3
D 12
main(argc,argv)
E 12
I 12
FILE   *file __P((char *));
void	show __P((FILE *, char *, char *));
void	usage __P((void));

int
main(argc, argv)
E 12
D 3
char	*argv[];
E 3
I 3
	int argc;
D 5
	char **argv;
E 5
I 5
	char *argv[];
E 5
E 3
{
D 3
	int	l;
	char	lb1[LB],lb2[LB];
E 3
I 3
D 5
	extern int optind;
	FILE *fp1, *fp2, *file();
E 5
D 12
	register int comp, file1done, file2done, read1, read2;
	register char *col1, *col2, *col3;
E 12
I 12
	int comp, file1done, file2done, read1, read2;
E 12
	int ch, flag1, flag2, flag3;
I 5
D 12
	FILE *fp1, *fp2, *file();
E 12
I 12
	FILE *fp1, *fp2;
	char *col1, *col2, *col3;
E 12
E 5
	char **p, line1[MAXLINELEN], line2[MAXLINELEN];
I 5
D 12
	extern int optind;
E 12
E 5
E 3

D 3
	ldr[0] = "";
	ldr[1] = "\t";
	ldr[2] = "\t\t";
	if(argc > 1)  {
		if(*argv[1] == '-' && argv[1][1] != 0) {
			l = 1;
			while(*++argv[1]) {
				switch(*argv[1]) {
				case'1':
					if(!one) {
						one = 1;
						ldr[1][0] =
						ldr[2][l--] = '\0';
					}
					break;
				case '2':
					if(!two) {
						two = 1;
						ldr[2][l--] = '\0';
					}
					break;
				case '3':
					three = 1;
					break;
				default:
				fprintf(stderr,"comm: illegal flag\n");
				exit(1);
				}
			}
			argv++;
			argc--;
E 3
I 3
	flag1 = flag2 = flag3 = 1;
	while ((ch = getopt(argc, argv, "-123")) != EOF)
		switch(ch) {
		case '-':
			--optind;
			goto done;
		case '1':
			flag1 = 0;
			break;
		case '2':
			flag2 = 0;
			break;
		case '3':
			flag3 = 0;
			break;
		case '?':
		default:
			usage();
E 3
		}
D 3
	}
E 3
I 3
done:	argc -= optind;
	argv += optind;
E 3

D 3
	if(argc < 3) {
		fprintf(stderr,"comm: arg count\n");
		exit(1);
	}
E 3
I 3
	if (argc != 2)
		usage();
E 3

D 3
	ib1 = openfil(argv[1]);
	ib2 = openfil(argv[2]);
E 3
I 3
	fp1 = file(argv[0]);
	fp2 = file(argv[1]);
E 3

I 3
	/* for each column printed, add another tab offset */
	p = tabs;
I 9
	col1 = col2 = col3 = NULL;
E 9
	if (flag1)
		col1 = *p++;
	if (flag2)
		col2 = *p++;
	if (flag3)
D 9
		col3 = *p++;
E 9
I 9
		col3 = *p;
E 9
E 3

D 3
	if(rd(ib1,lb1) < 0) {
		if(rd(ib2,lb2) < 0)	exit(0);
		copy(ib2,lb2,2);
	}
	if(rd(ib2,lb2) < 0)	copy(ib1,lb1,1);
E 3
I 3
	for (read1 = read2 = 1;;) {
		/* read next line, check for EOF */
		if (read1)
			file1done = !fgets(line1, MAXLINELEN, fp1);
		if (read2)
			file2done = !fgets(line2, MAXLINELEN, fp2);
E 3

D 3
	while(1) {
E 3
I 3
		/* if one file done, display the rest of the other file */
		if (file1done) {
			if (!file2done && col2)
D 4
				show(fp1, col2, line2);
E 4
I 4
				show(fp2, col2, line2);
E 4
			break;
		}
		if (file2done) {
			if (!file1done && col1)
D 4
				show(fp2, col1, line1);
E 4
I 4
				show(fp1, col1, line1);
E 4
			break;
		}
E 3

D 3
		switch(compare(lb1,lb2)) {

			case 0:
				wr(lb1,3);
				if(rd(ib1,lb1) < 0) {
					if(rd(ib2,lb2) < 0)	exit(0);
					copy(ib2,lb2,2);
				}
				if(rd(ib2,lb2) < 0)	copy(ib1,lb1,1);
				continue;

			case 1:
				wr(lb1,1);
				if(rd(ib1,lb1) < 0)	copy(ib2,lb2,2);
				continue;

			case 2:
				wr(lb2,2);
				if(rd(ib2,lb2) < 0)	copy(ib1,lb1,1);
				continue;
E 3
I 3
		/* lines are the same */
		if (!(comp = strcmp(line1, line2))) {
			read1 = read2 = 1;
			if (col3)
				(void)printf("%s%s", col3, line1);
			continue;
E 3
		}
D 3
	}
}
E 3

D 3
rd(file,buf)
FILE *file;
char *buf;
{

	register int i, c;
	i = 0;
	while((c = getc(file)) != EOF) {
		*buf = c;
		if(c == '\n' || i > LB-2) {
			*buf = '\0';
			return(0);
E 3
I 3
		/* lines are different */
		if (comp < 0) {
			read1 = 1;
			read2 = 0;
			if (col1)
				(void)printf("%s%s", col1, line1);
		} else {
			read1 = 0;
			read2 = 1;
			if (col2)
				(void)printf("%s%s", col2, line2);
E 3
		}
D 3
		i++;
		buf++;
E 3
	}
D 3
	return(-1);
E 3
I 3
	exit(0);
E 3
}

I 12
void
E 12
D 3
wr(str,n)
	char	*str;
E 3
I 3
show(fp, offset, buf)
	FILE *fp;
	char *offset, *buf;
E 3
{
I 12

E 12
D 3

	switch(n) {

		case 1:
			if(one)	return;
			break;

		case 2:
			if(two)	return;
			break;

		case 3:
			if(three)	return;
	}
	printf("%s%s\n",ldr[n-1],str);
}

copy(ibuf,lbuf,n)
FILE *ibuf;
char *lbuf;
{
E 3
	do {
D 3
		wr(lbuf,n);
	} while(rd(ibuf,lbuf) >= 0);

	exit(0);
E 3
I 3
		(void)printf("%s%s", offset, buf);
	} while (fgets(buf, MAXLINELEN, fp));
E 3
}

D 3
compare(a,b)
	char	*a,*b;
E 3
I 3
FILE *
file(name)
	char *name;
E 3
{
D 3
	register char *ra,*rb;
E 3
I 3
	FILE *fp;
E 3

D 3
	ra = --a;
	rb = --b;
	while(*++ra == *++rb)
		if(*ra == '\0')	return(0);
	if(*ra < *rb)	return(1);
	return(2);
}
FILE *openfil(s)
char *s;
{
	FILE *b;
	if(s[0]=='-' && s[1]==0)
		b = stdin;
	else if((b=fopen(s,"r")) == NULL) {
D 2
		fprintf(stderr,"comm: cannot open %s\n",s);
E 2
I 2
		perror(s);
E 3
I 3
	if (!strcmp(name, "-"))
D 12
		return(stdin);
E 12
I 12
		return (stdin);
E 12
D 10
	if (!(fp = fopen(name, "r"))) {
		(void)fprintf(stderr, "comm: can't read %s.\n", name);
E 10
I 10
	if ((fp = fopen(name, "r")) == NULL) {
		(void)fprintf(stderr, "comm: %s: %s\n", name, strerror(errno));
E 10
E 3
E 2
		exit(1);
	}
D 3
	return(b);
E 3
I 3
D 12
	return(fp);
E 12
I 12
	return (fp);
E 12
}

I 12
void
E 12
usage()
{
I 12

E 12
D 10
	(void)fprintf(stderr, "usage: comm [-123] [ - ] file1 file2\n");
E 10
I 10
	(void)fprintf(stderr, "usage: comm [-123] file1 file2\n");
E 10
	exit(1);
E 3
}
E 1
