h39038
s 00005/00005/00105
d D 8.1 93/06/06 14:40:12 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00109
d D 5.7 91/03/01 14:20:20 bostic 9 8
c ANSI
e
s 00002/00001/00108
d D 5.6 90/07/21 09:27:20 bostic 8 7
c missed an absolute pathname!
e
s 00001/00011/00108
d D 5.5 90/06/01 16:50:15 bostic 7 6
c new copyright notice
e
s 00001/00000/00118
d D 5.4 89/03/06 12:19:51 bostic 6 5
c pwd.h needs types.h
e
s 00085/00064/00033
d D 5.3 88/09/29 10:05:20 bostic 5 4
c general cleanup, add the -f flag, search entire address for string
c add Berkeley copyright notice
e
s 00003/00001/00094
d D 5.2 85/11/04 11:04:25 bloom 4 3
c add error if can't open requested mailbox
e
s 00015/00001/00080
d D 5.1 85/05/31 09:13:27 dist 3 2
c Add copyright
e
s 00007/00018/00074
d D 4.2 84/08/25 11:41:13 sam 2 1
c eliminate internal version of library func
e
s 00092/00000/00000
d D 4.1 80/10/01 17:26:50 bill 1 0
c date and time created 80/10/01 17:26:50 by bill
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
D 5
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 10
 * Copyright (c) 1980, 1988 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1980, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 5
 */

#ifndef lint
D 10
char copyright[] =
D 5
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 5
I 5
"%Z% Copyright (c) 1980, 1988 The Regents of the University of California.\n\
E 5
 All rights reserved.\n";
E 10
I 10
static char copyright[] =
"%Z% Copyright (c) 1980, 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 10
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5
E 3
I 2

I 6
#include <sys/types.h>
E 6
E 2
D 5
#include <stdio.h>
E 5
#include <ctype.h>
#include <pwd.h>
I 5
#include <stdio.h>
I 8
#include <paths.h>
E 8
E 5

D 5
struct	passwd *getpwuid();

E 5
main(argc, argv)
D 2
int argc;
register char **argv;
E 2
I 2
	int argc;
D 5
	register char **argv;
E 5
I 5
	char **argv;
E 5
E 2
{
D 5
	char lbuf[BUFSIZ];
	char lbuf2[BUFSIZ];
	register struct passwd *pp;
	int stashed = 0;
	register char *name;
	char *sender;
	char *getlogin();
E 5
I 5
	extern char *optarg;
	extern int optind;
D 9
	struct passwd *pwd, *getpwuid();
E 9
I 9
	struct passwd *pwd;
E 9
	int ch, newline;
	char *file, *sender, *p;
#if MAXPATHLEN > BUFSIZ
	char buf[MAXPATHLEN];
#else
	char buf[BUFSIZ];
#endif
E 5

D 5
	if (argc > 1 && *(argv[1]) == '-' && (*++argv)[1] == 's') {
		if (--argc <= 1) {
			fprintf (stderr, "Usage: from [-s sender] [user]\n");
			exit (1);
E 5
I 5
	file = sender = NULL;
	while ((ch = getopt(argc, argv, "f:s:")) != EOF)
		switch((char)ch) {
		case 'f':
			file = optarg;
			break;
		case 's':
			sender = optarg;
			for (p = sender; *p; ++p)
				if (isupper(*p))
					*p = tolower(*p);
			break;
		case '?':
		default:
			fprintf(stderr, "usage: from [-f file] [-s sender] [user]\n");
			exit(1);
E 5
		}
D 5
		--argc;
		sender = *++argv;
		for (name = sender; *name; name++)
			if (isupper(*name))
				*name = tolower(*name);
E 5
I 5
	argv += optind;
E 5

D 2
	}
	else
E 2
I 2
D 5
	} else
E 2
		sender = NULL;
	if (chdir("/usr/spool/mail") < 0)
		exit(1);
	if (argc > 1)
		name = argv[1];
	else {
		name = getlogin ();
		if (name == NULL || strlen(name) == 0) {
			pp = getpwuid(getuid());
			if (pp == NULL) {
				fprintf(stderr, "Who are you?\n");
E 5
I 5
	if (!file) {
		if (!(file = *argv)) {
			if (!(pwd = getpwuid(getuid()))) {
				fprintf(stderr,
				    "from: no password file entry for you.\n");
E 5
				exit(1);
			}
D 5
			name = pp->pw_name;
E 5
I 5
			file = pwd->pw_name;
E 5
		}
I 5
D 8
		(void)sprintf(buf, "/usr/spool/mail/%s", file);
E 8
I 8
		(void)sprintf(buf, "%s/%s", _PATH_MAILDIR, file);
E 8
		file = buf;
E 5
	}
D 4
	if (freopen(name, "r", stdin) == NULL)
E 4
I 4
D 5
	if (freopen(name, "r", stdin) == NULL) {
		fprintf(stderr, "Can't open /usr/spool/mail/%s\n", name);
E 4
		exit(0);
E 5
I 5
	if (!freopen(file, "r", stdin)) {
		fprintf(stderr, "from: can't read %s.\n", file);
		exit(1);
E 5
I 4
	}
E 4
D 2
	while(fgets(lbuf, sizeof lbuf, stdin) != NULL)
E 2
I 2
D 5
	while (fgets(lbuf, sizeof lbuf, stdin) != NULL)
E 2
		if (lbuf[0] == '\n' && stashed) {
			stashed = 0;
			printf("%s", lbuf2);
D 2
		}
		else if (bufcmp(lbuf, "From ", 5) &&
E 2
I 2
		} else if (strncmp(lbuf, "From ", 5) == 0 &&
E 2
		    (sender == NULL || match(&lbuf[4], sender))) {
			strcpy(lbuf2, lbuf);
			stashed = 1;
E 5
I 5
	for (newline = 1; fgets(buf, sizeof(buf), stdin);) {
		if (*buf == '\n') {
			newline = 1;
			continue;
E 5
		}
D 5
	if (stashed)
		printf("%s", lbuf2);
E 5
I 5
		if (newline && !strncmp(buf, "From ", 5) &&
		    (!sender || match(buf + 5, sender)))
			printf("%s", buf);
		newline = 0;
	}
E 5
	exit(0);
}

D 2
bufcmp (b1, b2, n)
register char *b1, *b2;
register int n;
{
	while (n-- > 0)
		if (*b1++ != *b2++)
			return (0);
	return (1);
}

E 2
D 5
match (line, str)
D 2
register char *line, *str;
E 2
I 2
	register char *line, *str;
E 5
I 5
match(line, sender)
	register char *line, *sender;
E 5
E 2
{
D 5
	register char ch;
E 5
I 5
	register char ch, pch, first, *p, *t;
E 5

D 5
	while (*line == ' ' || *line == '\t')
E 5
I 5
	for (first = *sender++;;) {
		if (isspace(ch = *line))
			return(0);
E 5
		++line;
D 5
	if (*line == '\n')
		return (0);
	while (*str && *line != ' ' && *line != '\t' && *line != '\n') {
		ch = isupper(*line) ? tolower(*line) : *line;
		if (ch != *str++)
			return (0);
		line++;
E 5
I 5
		if (isupper(ch))
			ch = tolower(ch);
		if (ch != first)
			continue;
		for (p = sender, t = line;;) {
			if (!(pch = *p++))
				return(1);
			if (isupper(ch = *t++))
				ch = tolower(ch);
			if (ch != pch)
				break;
		}
E 5
	}
D 5
	return (*str == '\0');
E 5
I 5
	/* NOTREACHED */
E 5
}
E 1
