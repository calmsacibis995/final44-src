h31806
s 00010/00003/00151
d D 8.2 94/04/02 10:16:18 bostic 12 11
c copyright cleanup
e
s 00002/00002/00152
d D 8.1 93/06/06 22:17:22 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00153
d D 5.10 90/06/01 18:31:21 bostic 10 9
c new copyright notice
e
s 00001/00001/00163
d D 5.9 90/05/15 19:56:08 bostic 9 8
c string.h is ANSI C include file
e
s 00002/00001/00162
d D 5.8 89/08/22 14:26:27 bostic 8 7
c guarantee that setuid/executable bits are off
e
s 00110/00109/00053
d D 5.7 89/07/19 17:02:00 bostic 7 6
c handle multiple file args -- lint/error message rework
e
s 00002/00002/00160
d D 5.6 89/05/10 22:45:36 bostic 6 5
c declare system includes first
e
s 00002/00040/00160
d D 5.5 88/07/06 14:57:23 bostic 5 4
c lint cleanup
e
s 00018/00001/00182
d D 5.4 88/07/06 11:06:50 bostic 4 3
c written by Mark Horton; add Berkeley specific copyrights
e
s 00000/00001/00183
d D 5.3 85/04/10 15:22:23 ralph 3 2
c more changes from rick adams.
e
s 00000/00000/00184
d D 5.2 85/01/22 14:13:03 ralph 2 1
c bug fixes and changes from Rick Adams
e
s 00184/00000/00000
d D 5.1 83/07/02 17:57:49 sam 1 0
c date and time created 83/07/02 17:57:49 by sam
e
u
U
t
T
I 4
D 12
/*
E 12
I 12
/*-
E 12
D 11
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
 */

E 4
I 1
#ifndef lint
I 12
char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 12
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
#endif /* not lint */
E 4

/*
D 7
 * uudecode [input]
E 7
I 7
 * uudecode [file ...]
E 7
 *
 * create the specified file, decoding as you go.
 * used with uuencode.
 */
D 6
#include <stdio.h>
#include <pwd.h>
E 6
D 7
#include <sys/types.h>
E 7
I 7
#include <sys/param.h>
E 7
#include <sys/stat.h>
I 12

E 12
I 6
D 7
#include <stdio.h>
E 7
#include <pwd.h>
I 7
#include <stdio.h>
D 9
#include <strings.h>
E 9
I 9
#include <string.h>
E 9
E 7
E 6

D 7
/* single character decode */
#define DEC(c)	(((c) - ' ') & 077)
E 7
I 7
char *filename;
E 7

I 7
D 12
/* ARGSUSED */
E 12
I 12
int
E 12
E 7
main(argc, argv)
D 7
char **argv;
E 7
I 7
	int argc;
D 12
	char **argv;
E 12
I 12
	char *argv[];
E 12
E 7
{
D 7
	FILE *in, *out;
D 3
	struct stat sbuf;
E 3
	int mode;
	char dest[128];
	char buf[80];
E 7
I 7
	extern int errno;
	int rval;
E 7

D 7
	/* optional input arg */
	if (argc > 1) {
		if ((in = fopen(argv[1], "r")) == NULL) {
			perror(argv[1]);
			exit(1);
		}
		argv++; argc--;
	} else
		in = stdin;

	if (argc != 1) {
		printf("Usage: uudecode [infile]\n");
		exit(2);
E 7
I 7
	if (*++argv) {
		rval = 0;
		do {
			if (!freopen(filename = *argv, "r", stdin)) {
				(void)fprintf(stderr, "uudecode: %s: %s\n",
				    *argv, strerror(errno));
				rval = 1;
				continue;
			}
			rval |= decode();
		} while (*++argv);
	} else {
		filename = "stdin";
		rval = decode();
E 7
	}
I 7
	exit(rval);
}
E 7

I 7
decode()
{
	extern int errno;
	struct passwd *pw;
	register int n;
	register char ch, *p;
	int mode, n1;
	char buf[MAXPATHLEN];

E 7
	/* search for header line */
D 7
	for (;;) {
		if (fgets(buf, sizeof buf, in) == NULL) {
			fprintf(stderr, "No begin line\n");
			exit(3);
E 7
I 7
	do {
		if (!fgets(buf, sizeof(buf), stdin)) {
			(void)fprintf(stderr,
			    "uudecode: %s: no \"begin\" line\n", filename);
			return(1);
E 7
		}
D 7
		if (strncmp(buf, "begin ", 6) == 0)
			break;
	}
D 5
	sscanf(buf, "begin %o %s", &mode, dest);
E 5
I 5
	(void)sscanf(buf, "begin %o %s", &mode, dest);
E 7
I 7
	} while (strncmp(buf, "begin ", 6));
	(void)sscanf(buf, "begin %o %s", &mode, buf);
E 7
E 5

	/* handle ~user/file format */
D 7
	if (dest[0] == '~') {
		char *sl;
		struct passwd *getpwnam();
D 5
		char *index();
E 5
		struct passwd *user;
D 5
		char dnbuf[100];
E 5
I 5
		char dnbuf[100], *index(), *strcat(), *strcpy();
E 5

		sl = index(dest, '/');
		if (sl == NULL) {
			fprintf(stderr, "Illegal ~user\n");
			exit(3);
E 7
I 7
	if (buf[0] == '~') {
		if (!(p = index(buf, '/'))) {
			(void)fprintf(stderr, "uudecode: %s: illegal ~user.\n",
			    filename);
			return(1);
E 7
		}
D 7
		*sl++ = 0;
		user = getpwnam(dest+1);
		if (user == NULL) {
			fprintf(stderr, "No such user as %s\n", dest);
			exit(4);
E 7
I 7
		*p++ = NULL;
		if (!(pw = getpwnam(buf + 1))) {
			(void)fprintf(stderr, "uudecode: %s: no user %s.\n",
			    filename, buf);
			return(1);
E 7
		}
D 7
		strcpy(dnbuf, user->pw_dir);
		strcat(dnbuf, "/");
		strcat(dnbuf, sl);
		strcpy(dest, dnbuf);
E 7
I 7
		n = strlen(pw->pw_dir);
		n1 = strlen(p);
		if (n + n1 + 2 > MAXPATHLEN) {
			(void)fprintf(stderr, "uudecode: %s: path too long.\n",
			    filename);
			return(1);
		}
		bcopy(p, buf + n + 1, n1 + 1);
		bcopy(pw->pw_dir, buf, n);
		buf[n] = '/';
E 7
	}

D 7
	/* create output file */
	out = fopen(dest, "w");
	if (out == NULL) {
		perror(dest);
		exit(4);
E 7
I 7
	/* create output file, set mode */
D 8
	if (!freopen(buf, "w", stdout) || fchmod(fileno(stdout), mode)) {
E 8
I 8
	if (!freopen(buf, "w", stdout) ||
	    fchmod(fileno(stdout), mode&0666)) {
E 8
		(void)fprintf(stderr, "uudecode: %s: %s: %s\n", buf,
		    filename, strerror(errno));
		return(1);
E 7
	}
D 7
	chmod(dest, mode);
E 7

D 7
	decode(in, out);

	if (fgets(buf, sizeof buf, in) == NULL || strcmp(buf, "end\n")) {
		fprintf(stderr, "No end line\n");
		exit(5);
	}
	exit(0);
}

/*
 * copy from in to out, decoding as you go along.
 */
decode(in, out)
FILE *in;
FILE *out;
{
	char buf[80];
	char *bp;
	int n;

E 7
I 7
	/* for each input line */
E 7
	for (;;) {
D 7
		/* for each input line */
		if (fgets(buf, sizeof buf, in) == NULL) {
			printf("Short file\n");
			exit(10);
E 7
I 7
		if (!fgets(p = buf, sizeof(buf), stdin)) {
			(void)fprintf(stderr, "uudecode: %s: short file.\n",
			    filename);
			return(1);
E 7
		}
D 7
		n = DEC(buf[0]);
		if (n <= 0)
E 7
I 7
#define	DEC(c)	(((c) - ' ') & 077)		/* single character decode */
		/*
		 * `n' is used to avoid writing out all the characters
		 * at the end of the file.
		 */
		if ((n = DEC(*p)) <= 0)
E 7
			break;
D 7

		bp = &buf[1];
		while (n > 0) {
			outdec(bp, out, n);
			bp += 4;
			n -= 3;
		}
E 7
I 7
		for (++p; n > 0; p += 4, n -= 3)
			if (n >= 3) {
				ch = DEC(p[0]) << 2 | DEC(p[1]) >> 4;
				putchar(ch);
				ch = DEC(p[1]) << 4 | DEC(p[2]) >> 2;
				putchar(ch);
				ch = DEC(p[2]) << 6 | DEC(p[3]);
				putchar(ch);
			}
			else {
				if (n >= 1) {
					ch = DEC(p[0]) << 2 | DEC(p[1]) >> 4;
					putchar(ch);
				}
				if (n >= 2) {
					ch = DEC(p[1]) << 4 | DEC(p[2]) >> 2;
					putchar(ch);
				}
				if (n >= 3) {
					ch = DEC(p[2]) << 6 | DEC(p[3]);
					putchar(ch);
				}
			}
E 7
	}
I 7
	if (!fgets(buf, sizeof(buf), stdin) || strcmp(buf, "end\n")) {
		(void)fprintf(stderr, "uudecode: %s: no \"end\" line.\n",
		    filename);
		return(1);
	}
	return(0);
E 7
}

D 7
/*
 * output a group of 3 bytes (4 input characters).
 * the input chars are pointed to by p, they are to
 * be output to file f.  n is used to tell us not to
 * output all of them at the end of the file.
 */
outdec(p, f, n)
char *p;
FILE *f;
E 7
I 7
usage()
E 7
{
D 7
	int c1, c2, c3;

	c1 = DEC(*p) << 2 | DEC(p[1]) >> 4;
	c2 = DEC(p[1]) << 4 | DEC(p[2]) >> 2;
	c3 = DEC(p[2]) << 6 | DEC(p[3]);
	if (n >= 1)
		putc(c1, f);
	if (n >= 2)
		putc(c2, f);
	if (n >= 3)
		putc(c3, f);
E 7
I 7
	(void)fprintf(stderr, "usage: uudecode [file ...]\n");
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
}

/*
 * Return the ptr in sp at which the character c appears;
 * NULL if not found
 */

#define	NULL	0

char *
index(sp, c)
register char *sp, c;
{
	do {
		if (*sp == c)
			return(sp);
	} while (*sp++);
	return(NULL);
E 5
}
E 1
