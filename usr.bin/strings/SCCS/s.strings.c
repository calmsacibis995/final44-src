h10419
s 00011/00006/00179
d D 8.2 94/01/28 17:03:38 bostic 15 14
c the -n option takes an argument
e
s 00005/00005/00180
d D 8.1 93/06/06 16:25:33 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00184
d D 5.11 91/09/01 17:47:43 bostic 13 12
c typo
e
s 00001/00001/00184
d D 5.10 91/05/23 18:15:27 bostic 12 11
c print out "stdin", don't dereference a NULL!
e
s 00036/00020/00149
d D 5.9 91/05/09 16:15:07 bostic 11 10
c cleanup, add COMPATIBILITY section to man page, make usage stuff right
e
s 00002/00002/00167
d D 5.8 91/05/09 14:19:50 donn 10 9
c Since strings may appear in the text segment, scan both the text and data
c segments for strings.
e
s 00024/00018/00145
d D 5.7 91/03/28 11:13:56 marc 9 8
c add -f to prepend filenmame to each line
e
s 00001/00011/00162
d D 5.6 90/06/01 16:10:31 bostic 8 7
c new copyright notice
e
s 00001/00001/00172
d D 5.5 89/11/13 17:35:06 bostic 7 6
c unitialized automatic variable
e
s 00080/00061/00093
d D 5.4 88/10/21 11:12:30 bostic 6 5
c add Berkeley copyright notice; reformat to KNF;
c I messed up kludge allowing getopt to handle -#
e
s 00001/00001/00153
d D 5.3 86/12/03 13:04:50 bostic 5 4
c changed to print decimal, not octal offsets
e
s 00115/00098/00039
d D 5.2 86/11/24 17:32:26 bostic 4 3
c tab as a printing character; bug report 4.3BSD/ucb/9
c heavily rewhacked
e
s 00014/00002/00123
d D 5.1 85/05/31 09:34:00 dist 3 2
c Add copyright
e
s 00007/00003/00118
d D 4.2 84/10/18 18:41:45 sam 2 1
c fix reported bug where seek is L_INCR instead of L_SET; also make 
c all seeks use symbolic names for whence
e
s 00121/00000/00000
d D 4.1 80/10/01 17:28:36 bill 1 0
c date and time created 80/10/01 17:28:36 by bill
e
u
U
t
T
I 3
/*
D 6
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
D 14
 * Copyright (c) 1980, 1987 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1980, 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 6
 */

E 3
I 2
#ifndef lint
E 2
I 1
D 3
static char *sccsid = "%W% (Berkeley) %G%";
I 2
#endif
E 3
I 3
D 14
char copyright[] =
D 6
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 6
I 6
"%Z% Copyright (c) 1980, 1987 The Regents of the University of California.\n\
E 6
 All rights reserved.\n";
E 14
I 14
static char copyright[] =
"%Z% Copyright (c) 1980, 1987, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 14
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6
E 3

E 2
D 4
#include <stdio.h>
E 4
I 4
#include <sys/types.h>
D 11
#include <sys/file.h>
E 11
I 11
D 15
#include <fcntl.h>
#include <errno.h>
E 15
I 15

E 15
E 11
E 4
#include <a.out.h>
I 11
D 15
#include <unistd.h>
E 11
I 4
#include <stdio.h>
E 15
E 4
#include <ctype.h>
I 15
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
E 15
I 11
#include <stdlib.h>
#include <string.h>
I 15
#include <unistd.h>
E 15
E 11
I 2
D 4
#include <sys/file.h>
E 4
E 2

D 4
long	ftell();
E 4
I 4
#define DEF_LEN		4		/* default minimum string length */
D 6
#define EOS		(char)NULL	/* end of string */
#define ERR		-1		/* general error */
#define ERREXIT		1		/* error exit */
#define NO		0		/* false/no */
#define OK		0		/* ok exit */
#define YES		1		/* true/yes */
E 4

E 6
D 4
/*
 * strings
 */
E 4
I 4
#define ISSTR(ch)	(isascii(ch) && (isprint(ch) || ch == '\t'))
E 4

D 4
struct	exec header;
E 4
I 4
typedef struct exec	EXEC;		/* struct exec cast */
E 4

D 4
char	*infile = "Standard input";
int	oflg;
int	asdata;
long	offset;
int	minlength = 4;
E 4
I 4
static long	foff;			/* offset in the file */
static int	hcnt,			/* head count */
		head_len,		/* length of header */
		read_len;		/* length to read */
static u_char	hbfr[sizeof(EXEC)];	/* buffer for struct exec */
E 4

I 11
static void usage();

E 11
D 4
main(argc, argv)
	int argc;
	char *argv[];
E 4
I 4
D 6
main(argc,argv)
int	argc;
char	**argv;
E 6
I 6
main(argc, argv)
	int argc;
	char **argv;
E 6
E 4
{
I 4
D 6
	register int	ch,		/* character */
			cnt;		/* general counter */
	register u_char	*C;		/* bfr pointer */
	EXEC	*head;			/* exec header pointer */
	int	minlen = DEF_LEN;	/* minimum string length */
	short	asdata = NO,		/* look in everything */
		oflg;			/* print octal location */
	u_char	*bfr;			/* collection buffer */
	char	*file,			/* file name for error */
		*malloc();
E 6
I 6
	extern char *optarg;
	extern int optind;
	register int ch, cnt;
	register u_char *C;
	EXEC *head;
D 11
	int minlen;
D 9
	short asdata, oflg;
E 9
I 9
	int exitcode = 0;
E 11
I 11
	int exitcode, minlen;
E 11
	short asdata, oflg, fflg;
E 9
	u_char *bfr;
D 11
	char *file, *p, *malloc();
E 11
I 11
	char *file, *p;
E 11
E 6
E 4

D 4
	argc--, argv++;
	while (argc > 0 && argv[0][0] == '-') {
		register int i;
		if (argv[0][1] == 0)
			asdata++;
		else for (i = 1; argv[0][i] != 0; i++) switch (argv[0][i]) {

		case 'o':
			oflg++;
			break;

		case 'a':
			asdata++;
			break;

		default:
			if (!isdigit(argv[0][i])) {
				fprintf(stderr, "Usage: strings [ -a ] [ -o ] [ -# ] [ file ... ]\n");
				exit(1);
E 4
I 4
	/*
	 * for backward compatibility, allow '-' to specify 'a' flag; no
	 * longer documented in the man page or usage string.
	 */
D 6
	for (++argv;*argv && **argv ==  '-';++argv) {
		for (cnt = 1;(*argv)[cnt];++cnt)
			switch ((*argv)[cnt]) {
				case 'a':
					asdata = YES;
					break;
				case 'o':
					oflg = YES;
					break;
				default:	/* getopt message compatible */
					if (!isdigit((*argv)[cnt])) {
						fprintf(stderr,"strings: illegal option -- %c\nusage: strings [-ao] [-#] [file ... ]\n",(*argv)[cnt]);
						exit(ERREXIT);
					}
					minlen = atoi(*argv + 1);
					break;
E 6
I 6
D 7
	asdata = 0;
E 7
I 7
D 9
	asdata = oflg = 0;
E 9
I 9
D 11
	asdata = oflg = fflg = 0;
E 11
I 11
	asdata = exitcode = fflg = oflg = 0;
E 11
E 9
E 7
	minlen = -1;
D 9
	while ((ch = getopt(argc, argv, "-0123456789ao")) != EOF)
E 9
I 9
D 11
	while ((ch = getopt(argc, argv, "-0123456789aof")) != EOF)
E 11
I 11
D 15
	while ((ch = getopt(argc, argv, "-0123456789anof")) != EOF)
E 11
E 9
		switch((char)ch) {
E 15
I 15
	while ((ch = getopt(argc, argv, "-0123456789an:of")) != EOF)
		switch (ch) {
E 15
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			/*
			 * kludge: strings was originally designed to take
			 * a number after a dash.
			 */
			if (minlen == -1) {
				p = argv[optind - 1];
				if (p[0] == '-' && p[1] == ch && !p[2])
					minlen = atoi(++p);
				else
					minlen = atoi(argv[optind] + 1);
E 6
E 4
			}
D 4
			minlength = argv[0][i] - '0';
			for (i++; isdigit(argv[0][i]); i++)
				minlength = minlength * 10 + argv[0][i] - '0';
			i--;
			break;
		}
		argc--, argv++;
E 4
I 4
D 6
		if (cnt == 1)
			asdata = YES;
E 4
	}
E 6
I 6
			break;
		case '-':
		case 'a':
			asdata = 1;
			break;
D 11
		case 'o':
			oflg = 1;
			break;
E 11
I 9
		case 'f':
			fflg = 1;
			break;
I 11
		case 'n':
			minlen = atoi(optarg);
			break;
		case 'o':
			oflg = 1;
			break;
E 11
E 9
		case '?':
		default:
D 11
			fprintf(stderr,
			    "usage: strings [-ao] [-#] [file ... ]\n");
			exit(1);
E 11
I 11
			usage();
E 11
		}
	argc -= optind;
	argv += optind;
E 6
I 4

I 6
	if (minlen == -1)
		minlen = DEF_LEN;
I 15
	else {
		(void)fprintf(stderr, "strings: length less than 1\n");
		exit (1);
	}
E 15

E 6
D 11
	if (!(bfr = (u_char *)malloc((u_int)minlen))) {
D 6
		fputs("strings: unable to allocate space.\n",stderr);
		exit(ERREXIT);
E 6
I 6
		fputs("strings: no space.\n", stderr);
E 11
I 11
	if (!(bfr = malloc((u_int)minlen))) {
		(void)fprintf(stderr, "strings: %s\n", strerror(errno));
E 11
		exit(1);
E 6
	}
D 6
	bfr[minlen] = EOS;
E 6
I 6
	bfr[minlen] = '\0';
E 6
D 9
	file = "stdin";
E 9
I 9
D 12
	file = NULL;
E 12
I 12
	file = "stdin";
E 12
E 9
E 4
	do {
D 4
		if (argc > 0) {
			if (freopen(argv[0], "r", stdin) == NULL) {
				perror(argv[0]);
				exit(1);
E 4
I 4
		if (*argv) {
D 6
			if (!freopen(*argv,"r",stdin)) {
E 6
I 6
D 9
			if (!freopen(*argv, "r", stdin)) {
E 6
				perror(*argv);
D 6
				exit(ERREXIT);
E 6
I 6
				exit(1);
E 6
E 4
			}
E 9
D 4
			infile = argv[0];
			argc--, argv++;
E 4
I 4
			file = *argv++;
I 9
			if (!freopen(file, "r", stdin)) {
D 11
				perror(file);
E 11
I 11
				(void)fprintf(stderr,
D 13
				    "strings; %s: %s\n", file, strerror(errno));
E 13
I 13
				    "strings: %s: %s\n", file, strerror(errno));
E 13
E 11
				exitcode = 1;
				goto nextfile;
			}
E 9
E 4
		}
D 2
		fseek(stdin, (long) 0, 0);
E 2
I 2
D 4
		fseek(stdin, (long) 0, L_SET);
E 2
		if (asdata ||
		    fread((char *)&header, sizeof header, 1, stdin) != 1 || 
		    N_BADMAG(header)) {
D 2
			fseek(stdin, (long) 0, 0);
E 2
I 2
			fseek(stdin, (long) 0, L_SET);
E 2
			find((long) 100000000L);
			continue;
E 4
I 4
		foff = 0;
I 9
#define DO_EVERYTHING()		{read_len = -1; head_len = 0; goto start;}
E 9
D 6
		read_len = ERR;
E 6
I 6
		read_len = -1;
E 6
		if (asdata)
D 9
			head_len = 0;
E 9
I 9
			DO_EVERYTHING()
E 9
		else {
			head = (EXEC *)hbfr;
D 6
			if ((head_len = read(fileno(stdin),(char *)head,sizeof(EXEC))) == ERR) {
E 6
I 6
D 9
			if ((head_len = read(fileno(stdin), (char *)head, sizeof(EXEC))) == -1) {
E 6
				perror(file);
D 6
				exit(ERREXIT);
E 6
I 6
				exit(1);
E 6
			}
E 9
I 9
D 11
			if ((head_len = read(fileno(stdin), (char *)head, sizeof(EXEC))) == -1)
E 11
I 11
			if ((head_len =
			    read(fileno(stdin), head, sizeof(EXEC))) == -1)
E 11
				DO_EVERYTHING()
E 9
			if (head_len == sizeof(EXEC) && !N_BADMAG(*head)) {
D 10
				foff = N_TXTOFF(*head) + head->a_text;
E 10
I 10
				foff = N_TXTOFF(*head);
E 10
D 6
				if (fseek(stdin,foff,L_SET) == ERR) {
E 6
I 6
D 9
				if (fseek(stdin, foff, L_SET) == -1) {
E 6
					perror(file);
D 6
					exit(ERREXIT);
E 6
I 6
					exit(1);
E 6
				}
E 9
I 9
D 11
				if (fseek(stdin, foff, L_SET) == -1)
E 11
I 11
				if (fseek(stdin, foff, SEEK_SET) == -1)
E 11
					DO_EVERYTHING()
E 9
D 10
				read_len = head->a_data;
E 10
I 10
				read_len = head->a_text + head->a_data;
E 10
				head_len = 0;
			}
			else
				hcnt = 0;
E 4
		}
I 9
start:
E 9
D 2
		fseek(stdin, (long) N_TXTOFF(header)+header.a_text, 1);
E 2
I 2
D 4
		fseek(stdin, (long) N_TXTOFF(header)+header.a_text, L_SET);
E 2
		find((long) header.a_data);
	} while (argc > 0);
}

find(cnt)
	long cnt;
{
	static char buf[BUFSIZ];
	register char *cp;
	register int c, cc;

	cp = buf, cc = 0;
	for (; cnt != 0; cnt--) {
		c = getc(stdin);
		if (c == '\n' || dirt(c) || cnt == 0) {
			if (cp > buf && cp[-1] == '\n')
				--cp;
			*cp++ = 0;
			if (cp > &buf[minlength]) {
E 4
I 4
D 6
		for (cnt = 0;(ch = getch()) != EOF;) {
E 6
I 6
		for (cnt = 0; (ch = getch()) != EOF;) {
E 6
			if (ISSTR(ch)) {
				if (!cnt)
					C = bfr;
				*C++ = ch;
				if (++cnt < minlen)
					continue;
I 9
				if (fflg)
					printf("%s:", file);
E 9
E 4
				if (oflg)
D 4
					printf("%7D ", ftell(stdin) - cc - 1);
				printf("%s\n", buf);
E 4
I 4
D 5
					printf("%07lo %s",foff - minlen,bfr);
E 5
I 5
D 6
					printf("%07ld %s",foff - minlen,bfr);
E 6
I 6
D 11
					printf("%07ld %s", foff - minlen,
					    (char *)bfr);
E 11
I 11
					printf("%07ld %s",
					    foff - minlen, (char *)bfr);
E 11
E 6
E 5
				else
D 6
					fputs((char *)bfr,stdout);
E 6
I 6
D 11
					fputs((char *)bfr, stdout);
E 11
I 11
					printf("%s", bfr);
E 11
E 6
				while ((ch = getch()) != EOF && ISSTR(ch))
					putchar((char)ch);
				putchar('\n');
E 4
			}
D 4
			cp = buf, cc = 0;
		} else {
			if (cp < &buf[sizeof buf - 2])
				*cp++ = c;
			cc++;
E 4
I 4
			cnt = 0;
E 4
		}
I 9
nextfile: ;
E 9
D 4
		if (ferror(stdin) || feof(stdin))
			break;
	}
E 4
I 4
	} while (*argv);
D 6
	exit(OK);
E 6
I 6
D 9
	exit(0);
E 9
I 9
	exit(exitcode);
E 9
E 6
E 4
}

D 4
dirt(c)
	int c;
E 4
I 4
/*
 * getch --
 *	get next character from wherever
 */
D 6
static
E 6
getch()
E 4
{
D 4

	switch (c) {

	case '\n':
	case '\f':
		return (0);

	case 0177:
		return (1);

	default:
		return (c > 0200 || c < ' ');
E 4
I 4
	++foff;
	if (head_len) {
		if (hcnt < head_len)
			return((int)hbfr[hcnt++]);
		head_len = 0;
E 4
	}
I 4
D 6
	if (read_len == ERR || read_len-- > 0)
E 6
I 6
	if (read_len == -1 || read_len-- > 0)
E 6
		return(getchar());
	return(EOF);
I 11
}

static void
usage()
{
	(void)fprintf(stderr,
	    "usage: strings [-afo] [-n length] [file ... ]\n");
	exit(1);
E 11
E 4
}
E 1
