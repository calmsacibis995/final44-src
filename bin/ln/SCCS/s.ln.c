h50059
s 00032/00021/00106
d D 8.2 94/03/31 12:54:26 bostic 21 20
c implement the POSIX 1003.2 -f flag
e
s 00005/00005/00122
d D 8.1 93/05/31 17:17:51 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00042/00041/00085
d D 5.1 93/04/29 12:30:57 bostic 19 18
c random cleanups, lint, for 4.4BSD freeze
e
s 00003/00000/00123
d D 4.15 91/02/24 22:12:41 donn 18 17
c Include files for function prototypes.
e
s 00017/00015/00106
d D 4.14 90/10/11 16:47:07 bostic 17 16
c minor cleanups, print program name on error, redo usage statement
e
s 00010/00010/00111
d D 4.13 90/06/19 14:10:53 bostic 16 15
c make -f option -F, S5 uses -f and POSIX is expected to.
e
s 00001/00011/00120
d D 4.12 90/06/01 16:54:56 bostic 15 14
c new copyright notice
e
s 00012/00007/00119
d D 4.11 88/06/18 13:17:09 bostic 14 13
c install approved copyright notice
e
s 00012/00006/00114
d D 4.10 87/11/30 21:00:32 bostic 13 12
c Berkeley code; add header
e
s 00101/00070/00019
d D 4.9 87/11/05 16:36:25 bostic 12 11
c add getopt; remove unused variables; use correct constants for 
c path length; simplify error checking; match usage statement to manual page 
c generally hack like I keep swearing I won't do
e
s 00002/00002/00087
d D 4.8 87/11/05 16:32:18 bostic 11 9
c fix "ln -s file1 file2 file3"; bug report 4.3BSD/bin/95
e
s 00002/00002/00087
d R 4.8 87/11/05 10:09:55 bostic 10 9
c fix "ln -s /etc/motd /etc/group /etc/passwd"; bug report 
c 4.3BSD/bin/95
e
s 00001/00001/00088
d D 4.7 87/10/22 09:51:07 bostic 9 8
c ANSI C; sprintf now returns an int.
e
s 00001/00001/00088
d D 4.6 85/11/15 09:29:05 lepreau 8 7
c avoid "ln -s nosuchfile non-writeable-dir" give misleading
c msg "nosuchfile: ENOENT..."
e
s 00003/00001/00086
d D 4.5 83/06/30 14:34:53 sam 7 6
c from sun
e
s 00006/00001/00081
d D 4.4 82/11/08 09:54:56 mckusick 6 5
c special case EEXIST for ln -s
e
s 00003/00003/00079
d D 4.3 82/03/31 12:02:02 root 5 4
c dont need lstat any more
e
s 00017/00007/00065
d D 4.2 82/03/15 04:11:16 root 4 3
c symbolic links
e
s 00000/00000/00072
d D 4.1 80/10/01 16:38:58 bill 3 2
c Define 4.1
e
s 00033/00040/00039
d D 3.2 80/08/24 13:26:28 bill 2 1
c fixed several bugs
e
s 00079/00000/00000
d D 3.1 80/08/15 01:55:16 bill 1 0
c date and time created 80/08/15 01:55:16 by bill
e
u
U
t
T
I 1
D 11
static	char sccsid[] = "%Z%%M% %I% %G%";
E 11
I 11
D 12
static char sccsid[] = "%W% (Berkeley) %G%";
E 12
E 11
/*
D 2
 * ln [ -f ] file ... name
 *
 * name must be dir if more than one file given
E 2
I 2
D 12
 * ln
E 12
I 12
D 14
 * Copyright (c) 1987 Regents of the University of California.
E 14
I 14
D 20
 * Copyright (c) 1987 Regents of the University of California.
E 14
D 13
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 13
I 13
 * All rights reserved.
E 20
I 20
D 21
 * Copyright (c) 1987, 1993
E 21
I 21
 * Copyright (c) 1987, 1993, 1994
E 21
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 15
 * Redistribution and use in source and binary forms are permitted
D 14
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 14
I 14
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 14
E 13
E 12
E 2
 */
D 2

E 2
D 12
#include <stdio.h>
#include <sys/types.h>
E 12
I 12

D 13
#ifndef	lint
E 13
I 13
#ifndef lint
E 13
D 20
char copyright[] =
D 14
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 14
I 14
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 14
 All rights reserved.\n";
E 20
I 20
static char copyright[] =
D 21
"%Z% Copyright (c) 1987, 1993\n\
E 21
I 21
"%Z% Copyright (c) 1987, 1993, 1994\n\
E 21
	The Regents of the University of California.  All rights reserved.\n";
E 20
D 13
#endif	/* !lint */
E 13
I 13
#endif /* not lint */
E 13

D 13
#ifndef	lint
E 13
I 13
#ifndef lint
E 13
static char sccsid[] = "%W% (Berkeley) %G%";
D 13
#endif	/* !lint */
E 13
I 13
#endif /* not lint */
E 13

#include <sys/param.h>
E 12
#include <sys/stat.h>
I 12
D 19
#include <stdio.h>
E 19
I 19

#include <err.h>
E 19
E 12
I 6
#include <errno.h>
I 17
D 19
#include <string.h>
E 19
I 19
#include <stdio.h>
E 19
I 18
#include <stdlib.h>
I 19
#include <string.h>
E 19
#include <unistd.h>
E 18
E 17
E 6

D 2
struct stat	stbuf;
E 2
I 2
D 12
struct	stat stb;
int	fflag;		/* force flag set? */
I 4
int	sflag;
E 4
char	name[BUFSIZ];
char	*rindex();
I 6
extern	int errno;
E 12
I 12
D 16
static int	fflag,				/* undocumented force flag */
E 16
I 16
D 19
static int	dirflag,			/* undocumented force flag */
E 16
		sflag,				/* symbolic, not hard, link */
		(*linkf)();			/* system link call */
I 18
static linkit(), usage();
E 19
I 19
D 21
int	dirflag,			/* Undocumented force flag. */
	sflag,				/* Symbolic, not hard, link. */
E 21
I 21
int	dirflag;			/* Undocumented directory flag. */
int	fflag;				/* Unlink existing files. */
int	sflag;				/* Symbolic, not hard, link. */
E 21
					/* System link call. */
D 21
	(*linkf) __P((const char *, const char *));
E 21
I 21
int (*linkf) __P((const char *, const char *));
E 21
E 19
E 18
E 12
E 6
E 2

I 19
D 21
static int	linkit __P((char *, char *, int));
static void	usage __P((void));
E 21
I 21
int	linkit __P((char *, char *, int));
void	usage __P((void));
E 21

int
E 19
D 2
int		fflag;		/* force flag set? */

char		_sobuf[BUFSIZ];

E 2
main(argc, argv)
D 2
register int	argc;
register char	*argv[];
E 2
I 2
D 12
	int argc;
	register char **argv;
E 12
I 12
D 17
	int	argc;
	char	**argv;
E 17
I 17
	int argc;
D 19
	char **argv;
E 19
I 19
	char *argv[];
E 19
E 17
E 12
E 2
{
D 2
	register	i, r;
E 2
I 2
D 12
	register int i, r;
E 12
I 12
D 16
	extern int	optind;
	struct stat	buf;
	int	ch, exitval, link(), symlink();
	char	*sourcedir;
E 16
I 16
	extern int optind;
D 19
	struct stat buf;
	int ch, exitval, link(), symlink();
E 19
I 19
	struct stat sb;
	int ch, exitval;
E 19
	char *sourcedir;
E 16
E 12
E 2

D 2
	if (argc > 1 && strcmp(argv[1], "-f") == 0) {
E 2
I 2
D 12
	argc--, argv++;
I 4
again:
E 4
	if (argc && strcmp(argv[0], "-f") == 0) {
E 2
		fflag++;
		argv++;
		argc--;
E 12
I 12
D 16
	while ((ch = getopt(argc, argv, "fs")) != EOF)
E 16
I 16
D 21
	while ((ch = getopt(argc, argv, "Fs")) != EOF)
E 16
		switch((char)ch) {
E 21
I 21
	while ((ch = getopt(argc, argv, "Ffs")) != EOF)
		switch (ch) {
E 21
D 16
		case 'f':
			fflag = 1;
E 16
I 16
		case 'F':
D 21
			dirflag = 1;
E 21
I 21
			dirflag = 1;	/* XXX: deliberately undocumented. */
E 21
E 16
			break;
I 21
		case 'f':
			fflag = 1;
			break;
E 21
		case 's':
			sflag = 1;
			break;
		case '?':
		default:
			usage();
		}

	argv += optind;
	argc -= optind;

	linkf = sflag ? symlink : link;

	switch(argc) {
	case 0:
		usage();
	case 1:				/* ln target */
		exit(linkit(argv[0], ".", 1));
	case 2:				/* ln target source */
		exit(linkit(argv[0], argv[1], 0));
D 19
	default:			/* ln target1 target2 directory */
		sourcedir = argv[argc - 1];
		if (stat(sourcedir, &buf)) {
D 17
			perror(sourcedir);
E 17
I 17
			(void)fprintf(stderr,
			    "ln: %s: %s\n", sourcedir, strerror(errno));
E 17
			exit(1);
		}
D 17
		if ((buf.st_mode & S_IFMT) != S_IFDIR)
E 17
I 17
		if (!S_ISDIR(buf.st_mode))
E 17
			usage();
		for (exitval = 0; *argv != sourcedir; ++argv)
			exitval |= linkit(*argv, sourcedir, 1);
		exit(exitval);
E 19
E 12
	}
I 4
D 12
	if (argc && strcmp(argv[0], "-s") == 0) {
		sflag++;
		argv++;
		argc--;
	}
E 4
D 2
	if (argc < 2) 
E 2
I 2
	if (argc == 0) 
E 2
		goto usage;
D 2
	else if (argc == 2)
E 2
I 2
	else if (argc == 1) {
E 2
		argv[argc] = ".";
D 2
	if (argc > 3) {
		if (stat(argv[argc-1], &stbuf) < 0)
E 2
I 2
		argc++;
	}
D 4
	if (argc > 2) {
		if (stat(argv[argc-1], &stb) < 0)
E 4
I 4
D 11
	if (sflag == 0 && argc > 2) {
E 11
I 11
	if (argc > 2) {
E 11
D 5
		if (lstat(argv[argc-1], &stb) < 0)
E 5
I 5
		if (stat(argv[argc-1], &stb) < 0)
E 5
E 4
E 2
			goto usage;
D 2
		if ((stbuf.st_mode&S_IFMT) != S_IFDIR) 
E 2
I 2
		if ((stb.st_mode&S_IFMT) != S_IFDIR) 
E 2
			goto usage;
	}
	r = 0;
D 2
	for(i=1; i<argc-1;i++)
E 2
I 2
	for(i = 0; i < argc-1; i++)
E 2
		r |= linkit(argv[i], argv[argc-1]);
	exit(r);
usage:
D 2
	fprintf(stderr, "Usage: ln: f1 f2; or ln f1 ... fn d2\n");
E 2
I 2
D 4
	fprintf(stderr, "Usage: ln f1\nor: ln f1 f2\nln f1 ... fn d2\n");
E 4
I 4
	fprintf(stderr, "Usage: ln [ -s ] f1\nor: ln [ -s ] f1 f2\nln [ -s ] f1 ... fn d2\n");
E 4
E 2
	exit(1);
E 12
I 12
D 17
	/*NOTREACHED*/
E 17
I 17
D 19
	/* NOTREACHED */
E 19
I 19
					/* ln target1 target2 directory */
	sourcedir = argv[argc - 1];
	if (stat(sourcedir, &sb))
		err(1, "%s", sourcedir);
	if (!S_ISDIR(sb.st_mode))
		usage();
	for (exitval = 0; *argv != sourcedir; ++argv)
		exitval |= linkit(*argv, sourcedir, 1);
	exit(exitval);
E 19
E 17
E 12
}

I 4
D 12
int	link(), symlink();

E 4
linkit(from, to)
D 2
register char	*from, *to;
E 2
I 2
	char *from, *to;
E 12
I 12
D 19
static
E 19
I 19
D 21
static int
E 21
I 21
int
E 21
E 19
linkit(target, source, isdir)
D 17
	char	*target, *source;
	int	isdir;
E 17
I 17
	char *target, *source;
	int isdir;
E 17
E 12
E 2
{
D 2
	register char	*p1, *p2, *bp;
E 2
I 2
D 12
	char *tail;
I 4
	int (*linkf)() = sflag ? symlink : link;
E 12
I 12
D 17
	extern int	errno;
	struct stat	buf;
	char	path[MAXPATHLEN],
		*cp, *rindex(), *strcpy();
E 17
I 17
D 19
	struct stat buf;
	char path[MAXPATHLEN], *cp;
E 19
I 19
	struct stat sb;
D 21
	char path[MAXPATHLEN], *p;
E 21
I 21
	int exists;
	char *p, path[MAXPATHLEN];
E 21
E 19
E 17
E 12
E 4
E 2

D 12
	/* is target a directory? */
D 2
	if (fflag == 0 && stat(from, &stbuf) >= 0
	    && (stbuf.st_mode&S_IFMT) == S_IFDIR) {
E 2
I 2
D 4
	if (fflag == 0 && stat(from, &stb) >= 0
E 4
I 4
D 5
	if (sflag == 0 && fflag == 0 && lstat(from, &stb) >= 0
E 5
I 5
	if (sflag == 0 && fflag == 0 && stat(from, &stb) >= 0
E 5
E 4
	    && (stb.st_mode&S_IFMT) == S_IFDIR) {
E 2
		printf("%s is a directory\n", from);
D 2
		return 1;
E 2
I 2
		return (1);
E 12
I 12
	if (!sflag) {
D 21
		/* if target doesn't exist, quit now */
E 21
I 21
		/* If target doesn't exist, quit now. */
E 21
D 19
		if (stat(target, &buf)) {
D 17
			perror(target);
E 17
I 17
			(void)fprintf(stderr,
			    "ln: %s: %s\n", target, strerror(errno));
E 17
			return(1);
E 19
I 19
		if (stat(target, &sb)) {
			warn("%s", target);
			return (1);
E 19
		}
D 16
		/* only symbolic links to directories, unless -f option used */
		if (!fflag && (buf.st_mode & S_IFMT) == S_IFDIR) {
E 16
I 16
D 21
		/* only symbolic links to directories, unless -F option used */
E 21
I 21
		/* Only symbolic links to directories, unless -F option used. */
E 21
D 19
		if (!dirflag && (buf.st_mode & S_IFMT) == S_IFDIR) {
E 16
D 17
			printf("%s is a directory.\n", target);
E 17
I 17
			(void)printf("ln: %s is a directory.\n", target);
E 17
			return(1);
E 19
I 19
		if (!dirflag && (sb.st_mode & S_IFMT) == S_IFDIR) {
			warnx("%s: is a directory", target);
			return (1);
E 19
		}
E 12
E 2
	}
D 2
	if (stat(to, &stbuf) >=0 && (stbuf.st_mode&S_IFMT) == S_IFDIR) {
		p1 = from;
		p2 = to;
		bp = _sobuf;
		while(*bp++ = *p2++)
			continue;
		bp[-1] = '/';
		p2 = bp;
		while(*bp = *p1++)
			if (*bp++ == '/')
				bp = p2;
		to = _sobuf;
E 2
I 2
D 4
	if (stat(to, &stb) >=0 && (stb.st_mode&S_IFMT) == S_IFDIR) {
E 4
I 4
D 5
	if (lstat(to, &stb) >= 0 && (stb.st_mode&S_IFMT) == S_IFDIR) {
E 5
I 5
D 12
	if (stat(to, &stb) >= 0 && (stb.st_mode&S_IFMT) == S_IFDIR) {
E 5
E 4
		tail = rindex(from, '/');
		if (tail == 0)
			tail = from;
E 12
I 12

D 21
	/* if the source is a directory, append the target's name */
D 19
	if (isdir || !stat(source, &buf) && (buf.st_mode & S_IFMT) == S_IFDIR) {
		if (!(cp = rindex(target, '/')))
			cp = target;
E 19
I 19
	if (isdir || !stat(source, &sb) && (sb.st_mode & S_IFMT) == S_IFDIR) {
		if (!(p = strrchr(target, '/')))
E 21
I 21
	/* If the source is a directory, append the target's name. */
	if (isdir || (exists = !stat(source, &sb)) && S_ISDIR(sb.st_mode)) {
		if ((p = strrchr(target, '/')) == NULL)
E 21
			p = target;
E 19
E 12
		else
D 12
			tail++;
D 9
		sprintf(name, "%s/%s", to, tail);
E 9
I 9
		(void)sprintf(name, "%s/%s", to, tail);
E 9
		to = name;
E 12
I 12
D 19
			++cp;
		(void)sprintf(path, "%s/%s", source, cp);
E 19
I 19
			++p;
		(void)snprintf(path, sizeof(path), "%s/%s", source, p);
E 19
		source = path;
E 12
E 2
D 21
	}
E 21
I 21
		exists = !stat(source, &sb);
	} else
		exists = !stat(source, &sb);
E 21
D 2
	else
		p1 = NULL;
E 2
D 4
	if (link(from, to) < 0) {
E 4
I 4
D 12
	if ((*linkf)(from, to) < 0) {
E 4
D 6
		perror(from);
E 6
I 6
D 8
		if (errno == EEXIST)
E 8
I 8
		if (errno == EEXIST || sflag)
E 8
			perror(to);
D 7
		else
E 7
I 7
		else if (access(from, 0) < 0)
E 7
			perror(from);
I 7
		else
			perror(to);
E 7
E 6
D 2
		return 1;
E 2
I 2
		return (1);
E 12
I 12

D 21
	if ((*linkf)(target, source)) {
E 21
I 21
	/*
	 * If the file exists, and -f was specified, unlink it.
	 * Attempt the link.
	 */
	if (fflag && exists && unlink(source) || (*linkf)(target, source)) {
E 21
D 17
		perror(source);
E 17
I 17
D 19
		(void)fprintf(stderr, "ln: %s: %s\n", source, strerror(errno));
E 17
		return(1);
E 19
I 19
		warn("%s", source);
		return (1);
E 19
E 12
E 2
	}
D 4
	return(0);
E 4
I 4
D 12
	return (0);
E 12
I 12
D 19
	return(0);
E 19
I 19
	return (0);
E 19
}

D 19
static
E 19
I 19
D 21
static void
E 21
I 21
void
E 21
E 19
usage()
{
D 17
	fputs("usage:\tln [-s] targetname [sourcename]\n\tln [-s] targetname1 targetname2 [... targetnameN] sourcedirectory\n", stderr);
E 17
I 17
	(void)fprintf(stderr,
D 21
	    "usage:\tln [-s] file1 file2\n\tln [-s] file ... directory\n");
E 21
I 21
	    "usage:\tln [-fs] file1 file2\n\tln [-fs] file ... directory\n");
E 21
E 17
	exit(1);
E 12
E 4
}
E 1
