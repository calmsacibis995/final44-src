h13182
s 00071/00027/00072
d D 8.2 94/01/25 13:06:47 bostic 16 15
c add the -m (mode) flag, make it POSIX.2 compliant
e
s 00005/00005/00094
d D 8.1 93/05/31 14:46:55 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00044/00080
d D 5.9 93/02/16 11:01:50 bostic 14 13
c use err(3) routines
e
s 00061/00029/00063
d D 5.8 92/11/10 09:19:19 bostic 13 12
c Marc's changes to fix the path beginning with '/', plus ANSI C stuff
e
s 00001/00011/00091
d D 5.7 90/05/31 20:34:26 bostic 12 11
c new copyright notice
e
s 00001/00001/00101
d D 5.6 90/05/15 19:41:48 bostic 11 10
c string.h is ANSI C include file
e
s 00003/00001/00099
d D 5.5 90/03/05 11:13:04 bostic 10 9
c fix errno scoping for ANSI C
e
s 00064/00011/00036
d D 5.4 89/09/02 16:02:16 bostic 9 8
c add -p flag; POSIX 1003.2 compliant
e
s 00012/00007/00035
d D 5.3 88/06/18 13:19:42 bostic 8 7
c install approved copyright notice
e
s 00019/00015/00023
d D 5.2 88/05/06 12:35:34 bostic 7 6
c don't need printf; add Berkeley header, this is a complete rewrite
e
s 00016/00001/00022
d D 5.1 85/04/30 15:04:44 dist 6 5
c Add copyright
e
s 00001/00001/00022
d D 4.5 85/01/31 14:01:55 serge 5 4
c reasonable error message
e
s 00001/00000/00022
d D 4.4 82/12/19 13:07:33 sam 4 3
c label perror's
e
s 00012/00067/00010
d D 4.3 82/12/19 13:05:37 sam 3 2
c use sys call
e
s 00006/00001/00071
d D 4.2 82/05/21 18:43:36 mckusick 2 1
c jkf's fix for group ownership
e
s 00072/00000/00000
d D 4.1 80/10/01 17:27:26 bill 1 0
c date and time created 80/10/01 17:27:26 by bill
e
u
U
t
T
I 1
D 6
static char *sccsid = "%W% (Berkeley) %G%";
E 6
I 6
/*
D 8
 * Copyright (c) 1983 Regents of the University of California.
E 8
I 8
D 13
 * Copyright (c) 1983 Regents of the University of California.
E 13
I 13
D 15
 * Copyright (c) 1983, 1992 Regents of the University of California.
E 13
E 8
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1983, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
D 12
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 8
E 7
 */

#ifndef lint
D 15
char copyright[] =
D 8
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 8
I 8
D 13
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 13
I 13
"%Z% Copyright (c) 1983, 1992 Regents of the University of California.\n\
E 13
E 8
 All rights reserved.\n";
E 15
I 15
static char copyright[] =
"%Z% Copyright (c) 1983, 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 15
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7

I 9
#include <sys/types.h>
#include <sys/stat.h>
I 13

I 14
#include <err.h>
E 14
E 13
#include <errno.h>
E 9
E 6
D 7
/*
D 3
** make directory
*/
E 3
I 3
 * make directory
 */
E 7
#include <stdio.h>
I 13
#include <stdlib.h>
E 13
I 9
D 11
#include <strings.h>
E 11
I 11
#include <string.h>
I 16
#include <unistd.h>
E 16
E 11
E 9
E 3

I 10
D 13
extern int errno;
E 13
I 13
D 14
int exitval;
E 14
I 14
int	build __P((char *));
void	usage __P((void));
E 14
E 13

I 13
D 14
void build __P((char *));
void usage __P((void));
void err __P((const char *, ...));

E 14
int
E 13
E 10
D 3
#include	<signal.h>
#include	<stdio.h>
I 2
#include	<sys/types.h>
#include	<stat.h>
E 2

int	Errors = 0;
char	*strcat();
char	*strcpy();

E 3
main(argc, argv)
D 3
char *argv[];
E 3
I 3
D 7
	char *argv[];
E 7
I 7
	int argc;
D 13
	char **argv;
E 13
I 13
	char *argv[];
E 13
E 7
E 3
{
I 3
D 7
	int errors = 0;
E 7
I 7
D 9
	int err;
E 9
I 9
D 10
	extern int errno, optind;
E 10
I 10
D 13
	extern int optind;
E 10
	int ch, exitval, pflag;
E 13
I 13
D 14
	int ch, pflag;
E 14
I 14
D 16
	int ch, exitval, pflag;
E 16
I 16
	int ch, exitval, oct, omode, pflag;
	mode_t *set;
	char *ep, *mode;
E 16
E 14
E 13
E 9
E 7
E 3

D 3
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGTERM, SIG_IGN);

	if(argc < 2) {
E 3
I 3
D 9
	if (argc < 2) {
E 3
D 5
		fprintf(stderr, "mkdir: arg count\n");
E 5
I 5
D 7
		fprintf(stderr, "usage: %s directory ...\n", argv[0]);
E 7
I 7
		fputs("usage: mkdir directory ...\n", stderr);
E 7
E 5
		exit(1);
	}
D 3
	while(--argc)
		mkdir(*++argv);
	exit(Errors!=0);
}

mkdir(d)
char *d;
{
	char pname[128], dname[128];
I 2
	struct stat statblk;
E 2
	register i, slash = 0;

	pname[0] = '\0';
	for(i = 0; d[i]; ++i)
		if(d[i] == '/')
			slash = i + 1;
	if(slash)
		strncpy(pname, d, slash);
	strcpy(pname+slash, ".");
	if (access(pname, 02)) {
		fprintf(stderr,"mkdir: cannot access %s\n", pname);
		++Errors;
		return;
	}
	if ((mknod(d, 040777, 0)) < 0) {
		fprintf(stderr,"mkdir: cannot make directory %s\n", d);
		++Errors;
		return;
	}
D 2
	chown(d, getuid(), getgid());
E 2
I 2
	(void) stat(d,&statblk);
	
	chown(d, getuid(), (int) statblk.st_gid);
E 2
	strcpy(dname, d);
	strcat(dname, "/.");
	if((link(d, dname)) < 0) {
		fprintf(stderr, "mkdir: cannot link %s\n", dname);
		unlink(d);
		++Errors;
		return;
	}
	strcat(dname, ".");
	if((link(pname, dname)) < 0) {
		fprintf(stderr, "mkdir: cannot link %s\n",dname);
		dname[strlen(dname)] = '\0';
		unlink(dname);
		unlink(d);
		++Errors;
	}
E 3
I 3
D 7
	while (--argc)
		if (mkdir(*++argv, 0777) < 0) {
I 4
			fprintf(stderr, "mkdir: ");
E 7
I 7
	for (err = 0; *++argv;)
		if (mkdir(*argv, 0777) < 0) {
			fputs("mkdir: ", stderr);
E 7
E 4
			perror(*argv);
D 7
			errors++;
E 7
I 7
			++err;
E 9
I 9
	pflag = 0;
D 16
	while ((ch = getopt(argc, argv, "p")) != EOF)
E 16
I 16
	mode = NULL;
	while ((ch = getopt(argc, argv, "m:p")) != EOF)
E 16
		switch(ch) {
		case 'p':
			pflag = 1;
			break;
I 16
		case 'm':
			mode = optarg;
			break;
E 16
		case '?':
		default:
			usage();
E 9
E 7
		}
D 7
	exit(errors != 0);
E 7
I 7
D 9
	exit(err ? 1 : 0);
E 9
I 9

D 16
	if (!*(argv += optind))
E 16
I 16
	argc -= optind;
	argv += optind;
	if (argv[0] == NULL)
E 16
		usage();

D 13
	for (exitval = 0; *argv; ++argv)
E 13
I 13
D 14
	for (; *argv; ++argv)
E 14
I 14
D 16
	for (exitval = 0; *argv; ++argv)
E 14
E 13
		if (pflag)
D 13
			exitval |= build(*argv);
		else if (mkdir(*argv, 0777) < 0) {
			(void)fprintf(stderr, "mkdir: %s: %s\n",
			    *argv, strerror(errno));
			exitval = 1;
		}
E 13
I 13
D 14
			build(*argv);
		else if (mkdir(*argv, S_IRWXU | S_IRWXG | S_IRWXO) < 0)
			err("%s: %s", *argv, strerror(errno));
E 14
I 14
			exitval |= build(*argv);
		else if (mkdir(*argv, S_IRWXU | S_IRWXG | S_IRWXO) < 0) {
E 16
I 16
	if (mode == NULL) {
		omode = S_IRWXU | S_IRWXG | S_IRWXO;
		oct = 1;
	} else if (*mode >= '0' && *mode <= '7') {
		omode = (int)strtol(mode, &ep, 8);
		if (omode < 0 || *ep)
			errx(1, "invalid file mode: %s", mode);
		oct = 1;
	} else {
		if ((set = setmode(mode)) == NULL)
			errx(1, "invalid file mode: %s", mode);
		oct = 0;
	}

	for (exitval = 0; *argv != NULL; ++argv) {
		if (pflag && build(*argv)) {
			exitval = 1;
			continue;
		}
		if (mkdir(*argv, oct ?
		    omode : getmode(set, S_IRWXU | S_IRWXG | S_IRWXO)) < 0) {
E 16
			warn("%s", *argv);
			exitval = 1;
		}
I 16
	}
E 16
E 14
E 13
	exit(exitval);
}

I 13
D 14
void
E 14
I 14
int
E 14
E 13
build(path)
	char *path;
{
D 16
	register char *p;
E 16
	struct stat sb;
D 13
	int create, ch;
E 13
I 13
D 16
	int create, savech;
E 16
I 16
	mode_t numask, oumask;
	int first;
	char *p;
E 16
E 13

D 13
	for (create = 0, p = path;; ++p)
		if (!*p || *p  == '/') {
			ch = *p;
E 13
I 13
	p = path;
D 16
	if (*p)				/* Skip leading '/'. */
E 16
I 16
	if (p[0] == '/')		/* Skip leading '/'. */
E 16
		++p;
D 16
	for (create = 0;; ++p)
		if (!*p || *p == '/') {
			savech = *p;
E 13
			*p = '\0';
			if (stat(path, &sb)) {
D 13
				if (errno != ENOENT || mkdir(path, 0777) < 0) {
					(void)fprintf(stderr, "mkdir: %s: %s\n",
					    path, strerror(errno));
					return(1);
E 13
I 13
				if (errno != ENOENT || mkdir(path,
				    S_IRWXU | S_IRWXG | S_IRWXO) < 0) {
D 14
					err("%s: %s", path, strerror(errno));
					return;
E 14
I 14
					warn("%s", path);
					return (1);
E 14
E 13
				}
				create = 1;
E 16
I 16
	for (first = 1;; ++p) {
		if (p[0] == '\0' || p[0] == '/' && p[1] == '\0')
			break;
		if (p[0] != '/')
			continue;
		*p = '\0';
		if (first) {
			/*
			 * POSIX 1003.2:
			 * For each dir operand that does not name an existing
			 * directory, effects equivalent to those cased by the
			 * following command shall occcur:
			 *
			 * mkdir -p -m $(umask -S),u+wx $(dirname dir) &&
			 *    mkdir [-m mode] dir
			 *
			 * We change the user's umask and then restore it,
			 * instead of doing chmod's.
			 */
			oumask = umask(0);
			numask = oumask & ~(S_IWUSR | S_IXUSR);
			(void)umask(numask);
			first = 0;
		}
		if (stat(path, &sb)) {
			if (errno != ENOENT ||
			    mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) < 0) {
				warn("%s", path);
				return (1);
E 16
			}
D 13
			if (!(*p = ch))
E 13
I 13
D 16
			if (!(*p = savech))
E 13
				break;
E 16
		}
D 13
	if (!create) {
		(void)fprintf(stderr, "mkdir: %s: %s\n", path,
		    strerror(EEXIST));
		return(1);
	}
	return(0);
E 13
I 13
D 14
	if (!create)
		err("%s: %s", path, strerror(EEXIST));
E 14
I 14
D 16
	if (!create) {
		warnx("%s: %s", path, strerror(EEXIST));
		return (1);
E 16
I 16
		*p = '/';
E 16
	}
I 16
	if (!first)
		(void)umask(oumask);
E 16
	return (0);
E 14
E 13
}

I 13
void
E 13
usage()
{
D 13
	(void)fprintf(stderr, "usage: mkdir [-p] dirname ...\n");
E 13
I 13
D 16
	(void)fprintf(stderr, "usage: mkdir [-p] directory ...\n");
E 16
I 16
	(void)fprintf(stderr, "usage: mkdir [-p] [-m mode] directory ...\n");
E 16
E 13
D 14
	exit(1);
I 13
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
	(void)fprintf(stderr, "mkdir: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exitval = 1;
E 14
I 14
	exit (1);
E 14
E 13
E 9
E 7
E 3
}
E 1
