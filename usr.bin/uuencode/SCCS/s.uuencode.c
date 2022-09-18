h20758
s 00010/00002/00114
d D 8.2 94/04/02 10:14:14 bostic 11 10
c copyright cleanup
e
s 00002/00002/00114
d D 8.1 93/06/06 22:17:54 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00115
d D 5.9 90/06/01 18:33:06 bostic 9 8
c new copyright notice
e
s 00001/00001/00125
d D 5.8 90/05/18 18:06:41 sam 8 7
c fix botched conversion
e
s 00074/00058/00052
d D 5.7 90/05/10 14:41:08 bostic 7 6
c general cleanup, retain exec bits, note read/write errors
e
s 00018/00001/00092
d D 5.6 88/07/06 11:06:51 bostic 6 5
c written by Mark Horton; add Berkeley specific copyrights
e
s 00008/00026/00085
d D 5.5 88/02/24 20:03:58 rick 5 4
c use library fread instead of rolling your own
e
s 00004/00002/00107
d D 5.4 86/12/22 14:43:09 bostic 4 3
c bug report 4.1BSD/usr.bin/2 and 4.1BSD/usr.bin/3
e
s 00001/00003/00108
d D 5.3 85/01/22 14:13:07 ralph 3 2
c bug fixes and changes from Rick Adams
e
s 00002/00000/00109
d D 5.2 83/12/19 15:42:38 ralph 2 1
c use a reasonable mode for encoding data piped in.
e
s 00109/00000/00000
d D 5.1 83/07/02 17:57:51 sam 1 0
c date and time created 83/07/02 17:57:51 by sam
e
u
U
t
T
I 6
D 11
/*
E 11
I 11
/*-
E 11
D 10
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 9
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
 */

E 6
I 1
#ifndef lint
I 11
char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 11
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif
E 6
I 6
#endif /* not lint */
E 6

/*
 * uuencode [input] output
 *
 * Encode a file so it can be mailed to a remote system.
 */
D 7
#include <stdio.h>
E 7
#include <sys/types.h>
#include <sys/stat.h>
I 11

E 11
I 7
#include <stdio.h>
E 7

I 11
int
E 11
D 7
/* ENC is the basic 1 character encoding function to make a char printing */
D 3
#define ENC(c) (((c) & 077) + ' ')
E 3
I 3
#define ENC(c) ((c) ? ((c) & 077) + ' ': '`')
E 3

E 7
main(argc, argv)
D 7
char **argv;
E 7
I 7
	int argc;
D 11
	char **argv;
E 11
I 11
	char *argv[];
E 11
E 7
{
D 7
	FILE *in;
	struct stat sbuf;
E 7
I 7
	extern int optind;
	extern int errno;
	struct stat sb;
E 7
	int mode;
I 7
	char *strerror();
E 7

D 7
	/* optional 1st argument */
	if (argc > 2) {
		if ((in = fopen(argv[1], "r")) == NULL) {
			perror(argv[1]);
E 7
I 7
	while (getopt(argc, argv, "") != EOF)
		usage();
	argv += optind;
	argc -= optind;

	switch(argc) {
	case 2:			/* optional first argument is input file */
		if (!freopen(*argv, "r", stdin) || fstat(fileno(stdin), &sb)) {
			(void)fprintf(stderr, "uuencode: %s: %s.\n",
			    *argv, strerror(errno));
E 7
			exit(1);
		}
D 7
		argv++; argc--;
	} else
		in = stdin;

	if (argc != 2) {
D 5
		printf("Usage: uuencode [infile] remotefile\n");
E 5
I 5
		fprintf(stderr,"Usage: uuencode [infile] remotefile\n");
E 5
		exit(2);
E 7
I 7
#define	RWX	(S_IRWXU|S_IRWXG|S_IRWXO)
		mode = sb.st_mode & RWX;
		++argv;
		break;
	case 1:
#define	RW	(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
		mode = RW & ~umask(RW);
		break;
	case 0:
	default:
		usage();
E 7
	}

D 7
	/* figure out the input file mode */
D 4
	fstat(fileno(in), &sbuf);
	mode = sbuf.st_mode & 0777;
E 4
I 4
	if (fstat(fileno(in), &sbuf) < 0 || !isatty(fileno(in)))
		mode = 0666 & ~umask(0666);
	else
		mode = sbuf.st_mode & 0777;
E 4
I 2
D 3
	if (in == stdin && mode == 0)
		mode = 0600;	/* use a reasonable mode in case of pipes */
E 3
E 2
	printf("begin %o %s\n", mode, argv[1]);

	encode(in, stdout);

	printf("end\n");
E 7
I 7
	(void)printf("begin %o %s\n", mode, *argv);
	encode();
	(void)printf("end\n");
	if (ferror(stdout)) {
		(void)fprintf(stderr, "uuencode: write error.\n");
		exit(1);
	}
E 7
	exit(0);
}

I 7
/* ENC is the basic 1 character encoding function to make a char printing */
#define	ENC(c) ((c) ? ((c) & 077) + ' ': '`')

E 7
/*
 * copy from in to out, encoding as you go along.
 */
D 7
encode(in, out)
D 5
FILE *in;
FILE *out;
E 5
I 5
register FILE *in;
register FILE *out;
E 7
I 7
encode()
E 7
E 5
{
I 7
	register int ch, n;
	register char *p;
E 7
	char buf[80];
D 5
	int i, n;
E 5
I 5
D 7
	register int i, n;
E 7
E 5

D 7
	for (;;) {
		/* 1 (up to) 45 character line */
D 5
		n = fr(in, buf, 45);
E 5
I 5
		n = fread(buf, 1, 45, in);
E 5
		putc(ENC(n), out);

		for (i=0; i<n; i += 3)
			outdec(&buf[i], out);

		putc('\n', out);
		if (n <= 0)
E 7
I 7
	while (n = fread(buf, 1, 45, stdin)) {
		ch = ENC(n);
		if (putchar(ch) == EOF)
E 7
			break;
I 7
D 8
		for (p = buf; n; n -= 3, p += 3) {
E 8
I 8
		for (p = buf; n > 0; n -= 3, p += 3) {
E 8
			ch = *p >> 2;
			ch = ENC(ch);
			if (putchar(ch) == EOF)
				break;
			ch = (*p << 4) & 060 | (p[1] >> 4) & 017;
			ch = ENC(ch);
			if (putchar(ch) == EOF)
				break;
			ch = (p[1] << 2) & 074 | (p[2] >> 6) & 03;
			ch = ENC(ch);
			if (putchar(ch) == EOF)
				break;
			ch = p[2] & 077;
			ch = ENC(ch);
			if (putchar(ch) == EOF)
				break;
		}
		if (putchar('\n') == EOF)
			break;
E 7
	}
I 7
	if (ferror(stdin)) {
		(void)fprintf(stderr, "uuencode: read error.\n");
		exit(1);
	}
	ch = ENC('\0');
	(void)putchar(ch);
	(void)putchar('\n');
E 7
}

D 7
/*
 * output one group of 3 bytes, pointed at by p, on file f.
 */
outdec(p, f)
D 5
char *p;
FILE *f;
E 5
I 5
register char *p;
register FILE *f;
E 7
I 7
usage()
E 7
E 5
{
D 5
	int c1, c2, c3, c4;
E 5
I 5
D 7
	register int c1, c2, c3, c4;
E 5

	c1 = *p >> 2;
	c2 = (*p << 4) & 060 | (p[1] >> 4) & 017;
	c3 = (p[1] << 2) & 074 | (p[2] >> 6) & 03;
	c4 = p[2] & 077;
	putc(ENC(c1), f);
	putc(ENC(c2), f);
	putc(ENC(c3), f);
	putc(ENC(c4), f);
E 7
I 7
	(void)fprintf(stderr,"usage: uuencode [infile] remotefile\n");
	exit(1);
E 7
D 5
}

/* fr: like read but stdio */
int
fr(fd, buf, cnt)
FILE *fd;
char *buf;
int cnt;
{
	int c, i;

	for (i=0; i<cnt; i++) {
		c = getc(fd);
		if (c == EOF)
			return(i);
		buf[i] = c;
	}
	return (cnt);
E 5
}
E 1
