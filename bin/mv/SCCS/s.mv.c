h22542
s 00024/00018/00250
d D 8.2 94/04/02 09:23:26 bostic 29 28
c display the file modes, not just the octal value on overwrite
c new flags for cp
e
s 00005/00005/00263
d D 8.1 93/05/31 14:47:51 bostic 28 27
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00058/00051/00210
d D 5.13 93/04/29 12:57:06 bostic 27 26
c be more informative and careful about error conditions
e
s 00070/00042/00191
d D 5.12 92/11/23 14:22:02 bostic 26 25
c use "cp -pR", not "cp -pr"; minor error changes
c lots of lint/ANSI cleanups
e
s 00002/00002/00231
d D 5.11 91/04/03 12:42:47 bostic 25 24
c use execl, not execlp; bug was args weren't NULL terminated
e
s 00040/00035/00193
d D 5.10 91/04/03 12:30:13 bostic 24 23
c minor cleanups, ANSIisms, no fundamental changes
e
s 00001/00011/00227
d D 5.9 90/05/31 20:35:25 bostic 23 22
c new copyright notice
e
s 00172/00232/00065
d D 5.8 89/10/01 17:07:53 bostic 22 21
c new version of mv from Ken Smith (kensmith@cs.Buffalo.EDU)
c use cp and rm to copy anything not a regular file across partitions.
c expect to be POSIX .2 compliant
e
s 00034/00044/00263
d D 5.7 88/04/21 11:42:58 bostic 21 20
c add getopt for "--" capability
e
s 00009/00007/00298
d D 5.6 88/01/21 16:54:32 bostic 20 19
c don't ask about access modes, if already asked for i flag.
e
s 00004/00005/00301
d D 5.5 87/10/22 09:52:55 bostic 19 18
c ANSI C; sprintf now returns an int.
e
s 00002/00002/00304
d D 5.4 87/04/13 17:38:38 lepreau 18 16
c When forced to copy a regular or special file, ignore the
c current umask so preserve the original mode.
e
s 00002/00002/00304
d R 5.4 87/04/13 17:33:06 lepreau 17 16
c When forced to copy a regular or special file, ignore the
e
s 00002/00001/00304
d D 5.3 86/05/15 10:20:09 lepreau 16 15
c make "mv <file> <non-existent-dir>" print reasonable msg
e
s 00058/00030/00247
d D 5.2 85/06/07 01:25:10 serge 15 14
c don't exec /bin/cp, do the copy ourselves
e
s 00014/00002/00263
d D 5.1 85/04/30 15:04:53 dist 14 13
c Add copyright
e
s 00001/00001/00264
d D 4.13 83/06/30 14:50:40 sam 13 12
c include fix
e
s 00017/00022/00248
d D 4.12 83/03/21 21:49:54 sam 12 11
c rename may fail when target doesn't exist for unrecoverable reasons
e
s 00002/00004/00268
d D 4.11 83/01/31 18:02:18 mckusick 11 10
c fix up usage text
e
s 00008/00015/00264
d D 4.10 83/01/31 17:44:24 mckusick 10 9
c if last argument is a directory, always move into it even if only two arguments
e
s 00011/00002/00268
d D 4.9 83/01/05 23:06:46 sam 9 8
c kludge utime stuff prior to utimes inclusion in the system
e
s 00003/00004/00267
d D 4.8 83/01/03 20:41:49 sam 8 7
c mv doesn't need to be setuid anymore; fix problem with symbolic links
e
s 00176/00259/00095
d D 4.7 83/01/01 13:25:24 sam 7 6
c rewrite to use rename
e
s 00020/00005/00334
d D 4.6 82/10/23 20:19:40 mckusick 6 5
c fix to understand symbolic links
e
s 00003/00003/00336
d D 4.5 82/02/11 23:50:58 mckusic 5 4
c convert to use library routines to access directories
e
s 00000/00004/00339
d D 4.4 81/04/26 12:53:47 sklower 4 3
c Cannot rename or give away directories which you can't write (srb)
e
s 00001/00008/00342
d D 4.3 81/02/28 21:43:54 wnj 3 2
c fix bug with -i when moving directories
e
s 00012/00005/00338
d D 4.2 80/12/18 14:23:07 root 2 1
c A new option '-' has been added which forces all following 
c arguments to be interpreted as file names.  This allows file names 
c starting with - to be specified.
e
s 00343/00000/00000
d D 4.1 80/10/07 02:26:43 bill 1 0
c date and time created 80/10/07 02:26:43 by bill
e
u
U
t
T
I 14
/*
D 22
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 22
I 22
D 28
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 28
I 28
D 29
 * Copyright (c) 1989, 1993
E 29
I 29
 * Copyright (c) 1989, 1993, 1994
E 29
 *	The Regents of the University of California.  All rights reserved.
E 28
 *
 * This code is derived from software contributed to Berkeley by
 * Ken Smith of The State University of New York at Buffalo.
 *
D 23
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
E 23
I 23
 * %sccs.include.redist.c%
E 23
E 22
 */

E 14
I 7
#ifndef lint
E 7
I 1
D 3
static char *sccsid = "%W% (Berkeley) %G%";
E 3
I 3
D 14
static	char *sccsid = "%W% (Berkeley) %E%";
I 7
#endif
E 14
I 14
D 28
char copyright[] =
D 22
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 22
I 22
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
E 22
 All rights reserved.\n";
E 28
I 28
static char copyright[] =
D 29
"%Z% Copyright (c) 1989, 1993\n\
E 29
I 29
"%Z% Copyright (c) 1989, 1993, 1994\n\
E 29
	The Regents of the University of California.  All rights reserved.\n";
E 28
D 21
#endif not lint
E 21
I 21
#endif /* not lint */
E 21

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 21
#endif not lint
E 21
I 21
#endif /* not lint */
E 21
E 14
E 7
I 6

E 6
E 3
D 22
/*
 * mv file1 file2
 */
E 22
I 7
#include <sys/param.h>
D 22
#include <sys/stat.h>
E 22
I 15
#include <sys/time.h>
I 22
#include <sys/wait.h>
#include <sys/stat.h>
E 22
I 20
D 24
#include <sys/file.h>
I 22
#include <sys/errno.h>
E 24
I 24
D 26
#include <fcntl.h>
E 26
I 26

I 27
#include <err.h>
E 27
E 26
#include <errno.h>
D 26
#include <unistd.h>
E 26
I 26
#include <fcntl.h>
E 26
E 24
E 22
E 20
E 15
E 7
D 21

E 21
#include <stdio.h>
I 24
#include <stdlib.h>
E 24
D 7
#include <sys/types.h>
#include <sys/stat.h>
E 7
I 7
D 13
#include <dir.h>
E 13
I 13
D 21
#include <sys/dir.h>
E 21
E 13
D 22
#include <errno.h>
E 22
I 22
#include <string.h>
I 26
#include <unistd.h>

E 26
#include "pathnames.h"
E 22
E 7
D 5
#include <sys/dir.h>
E 5
D 21
#include <signal.h>
E 21

D 7
#define	DOT	"."
#define	DOTDOT	".."
E 7
D 22
#define	DELIM	'/'
D 7
#define SDELIM "/"
D 6
#define	MAXN	100
E 6
I 6
#define	MAXN	300
E 7
E 6
#define MODEBITS 07777
E 22
I 22
D 24
extern int errno;
E 24
int fflg, iflg;
E 22
D 7
#define ROOTINO 2
E 7

I 26
int	copy __P((char *, char *));
int	do_move __P((char *, char *));
D 27
void	err __P((const char *, ...));
E 27
int	fastcopy __P((char *, char *, struct stat *));
void	usage __P((void));

int
E 26
D 7
char	*pname();
E 7
I 7
D 22
#define	ISDIR(st)	(((st).st_mode&S_IFMT) == S_IFDIR)
#define	ISLNK(st)	(((st).st_mode&S_IFMT) == S_IFLNK)
#define	ISREG(st)	(((st).st_mode&S_IFMT) == S_IFREG)
#define	ISDEV(st) \
	(((st).st_mode&S_IFMT) == S_IFCHR || ((st).st_mode&S_IFMT) == S_IFBLK)

E 7
D 19
char	*sprintf();
E 19
char	*dname();
D 21
struct	stat s1, s2;
E 21
D 7
int	iflag = 0;	/* interactive flag. If this flag is set,
			 * the user is queried before files are
			 * destroyed by cp.
			 */
int	fflag = 0;	/* force flag. supercedes all restrictions */
E 7
I 7
int	iflag = 0;	/* interactive mode */
int	fflag = 0;	/* force overwriting */
extern	unsigned errno;
E 7

E 22
main(argc, argv)
D 7
register char *argv[];
E 7
I 7
D 21
	register char *argv[];
E 21
I 21
D 22
	register int argc;
	register char **argv;
E 22
I 22
	int argc;
D 26
	char **argv;
E 26
I 26
	char *argv[];
E 26
E 22
E 21
E 7
{
I 22
D 26
	extern char *optarg;
E 22
D 21
	register i, r;
I 2
	register char *arg;
E 21
I 21
	extern int optind;
E 26
D 22
	struct stat st;
	int ch, r;
E 21
I 10
	char *dest;
E 22
I 22
D 29
	register int baselen, exitval, len;
E 29
I 29
	register int baselen, len, rval;
E 29
	register char *p, *endp;
D 24
	struct stat sbuf;
E 24
I 24
	struct stat sb;
E 24
	int ch;
	char path[MAXPATHLEN + 1];
E 22
E 10
E 2

D 7
	/* get the flag(s) */

E 7
D 21
	if (argc < 2)
		goto usage;
D 2
	if (*argv[1] == '-') {
E 2
I 2
D 7
	while (argc>1 && *argv[1] == '-') {
E 7
I 7
	while (argc > 1 && *argv[1] == '-') {
E 7
E 2
		argc--;
D 2
		while (*++argv[1] != '\0')
			switch (*argv[1]) {
E 2
I 2
		arg = *++argv;
E 2

I 2
		/*
D 7
		 *  all files following a null option are considered file names
E 7
I 7
		 * all files following a null option
		 * are considered file names
E 7
		 */
D 7
		if (*(arg+1) == '\0') break;
E 7
I 7
		if (*(arg+1) == '\0')
E 21
I 21
D 22
	while ((ch = getopt(argc, argv, "-fi")) != EOF)
E 22
I 22
D 29
	while (((ch = getopt(argc, argv, "-if")) != EOF))
E 22
		switch((char)ch) {
E 29
I 29
	while ((ch = getopt(argc, argv, "-if")) != EOF)
		switch (ch) {
E 29
D 22
		case '-':
			goto endarg;
		case 'f':
			fflag++;
E 21
			break;
E 22
D 21
		while (*++arg != '\0') switch (*arg) {
E 7

E 21
D 7
		while (*++arg != '\0')
			switch (*arg) {
E 7
I 7
		case 'i':
D 22
			iflag++;
E 22
I 22
D 24
			++iflg;
E 24
I 24
			iflg = 1;
E 24
E 22
			break;
I 22
		case 'f':
D 24
			++fflg;
E 24
I 24
			fflg = 1;
E 24
			break;
D 26
		case '-':		/* undocumented; for compatibility */
E 26
I 26
		case '-':		/* Undocumented; for compatibility. */
E 26
			goto endarg;
E 22
E 7
D 21

E 2
D 7
			/* interactive mode */
			case 'i':
				iflag++;
				break;
E 7
I 7
		case 'f':
			fflag++;
			break;
E 7

E 21
I 21
		case '?':
E 21
D 7
			/* force moves */
			case 'f':
				fflag++;
				break;

			/* don't live with bad options */
			default:
				goto usage;
			}
E 7
I 7
		default:
D 21
			goto usage;
E 21
I 21
			usage();
E 21
		}
E 7
D 2
		argv++;
E 2
D 21
	}
	if (argc < 3)
		goto usage;
D 6
	if (stat(argv[1], &s1) < 0) {
E 6
I 6
D 7
	if (lstat(argv[1], &s1) < 0) {
E 6
		fprintf(stderr, "mv: cannot access %s\n", argv[1]);
		return(1);
	}
	if ((s1.st_mode & S_IFMT) == S_IFDIR) {
		if (argc != 3)
			goto usage;
		return mvdir(argv[1], argv[2]);
	}
E 7
D 8
	setuid(getuid());
D 7
	if (argc > 3)
		if (stat(argv[argc-1], &s2) < 0 || (s2.st_mode & S_IFMT) != S_IFDIR)
			goto usage;
E 7
	r = 0;
E 8
D 7
	for (i=1; i<argc-1; i++)
		r |= move(argv[i], argv[argc-1]);
	return(r);
E 7
I 7
D 10
	if (argc > 3) {
		register char *dest;

		dest = argv[argc-1];
		if (stat(dest, &s2) < 0 || !ISDIR(s2))
			goto usage;
E 10
I 10
	dest = argv[argc-1];
D 11
	if (stat(dest, &s2) < 0)
		goto usage;
	if (ISDIR(s2)) {
E 11
I 11
	if (stat(dest, &s2) >= 0 && ISDIR(s2)) {
E 11
E 10
I 8
		r = 0;
E 8
		for (i = 1; i < argc-1; i++)
			r |= movewithshortname(argv[i], dest);
E 21
I 21
D 22
endarg:	argv += optind;
	argc -= optind;
E 22
I 22
endarg:	argc -= optind;
	argv += optind;
E 22

	if (argc < 2)
		usage();
D 22
	dest = argv[argc - 1];
	if (stat(dest, &st) >= 0 && ISDIR(st)) {
		for (r = 0; --argc; ++argv)
			r |= movewithshortname(*argv, dest);
E 21
		exit(r);
E 22
I 22

	/*
D 24
	 * if stat fails on target, it doesn't exist (or can't be accessed
	 * by the user, doesn't matter which) try the move.  If target exists,
	 * and isn't a directory, try the move.  More than 2 arguments is an
	 * error.
E 24
I 24
	 * If the stat on the target fails or the target isn't a directory,
	 * try the move.  More than 2 arguments is an error in this case.
E 24
	 */
D 24
	if (stat(argv[argc - 1], &sbuf) || !S_ISDIR(sbuf.st_mode)) {
E 24
I 24
	if (stat(argv[argc - 1], &sb) || !S_ISDIR(sb.st_mode)) {
E 24
		if (argc > 2)
			usage();
		exit(do_move(argv[0], argv[1]));
E 22
	}
D 8
	if (stat(argv[2], &s2) >= 0 && ISDIR(s2)) {
E 8
I 8
D 10
	if (lstat(argv[2], &s2) >= 0 && ISDIR(s2)) {
E 8
		struct stat s1;

D 8
		if (stat(argv[1], &s1) >= 0 && ISDIR(s1))
E 8
I 8
		if (lstat(argv[1], &s1) >= 0 && ISDIR(s1))
E 8
			r = move(argv[1], argv[2]);
		else
			r = movewithshortname(argv[1], argv[2]);
	} else
		r = move(argv[1], argv[2]);
E 10
I 10
D 21
	if (argc > 3)
		goto usage;
	r = move(argv[1], argv[2]);
E 21
I 21
D 22
	if (argc != 2)
		usage();
	r = move(argv[0], argv[1]);
E 21
E 10
	exit(r);
D 21
	/*NOTREACHED*/
E 7
usage:
D 2
	fprintf(stderr, "usage: mv f1 f2; or mv d1 d2; or mv f1 ... fn d1\n");
E 2
I 2
D 7
	fprintf(stderr, "usage: mv [-if] f1 f2; or mv [-if] d1 d2; or mv [-if] f1 ... fn d1\n");
E 2
	return(1);
E 7
I 7
	fprintf(stderr,
D 11
"usage: mv [-if] f1 ... fn d1 (where `fn' is a file or directory)\n");
E 11
I 11
"usage: mv [-if] f1 f2 or mv [-if] f1 ... fn d1 (`fn' is a file or directory)\n");
E 11
	return (1);
E 21
E 7
}
E 22

I 7
D 22
movewithshortname(src, dest)
	char *src, *dest;
{
	register char *shortname;
	char target[MAXPATHLEN + 1];

	shortname = dname(src);
	if (strlen(dest) + strlen(shortname) > MAXPATHLEN - 1) {
		error("%s/%s: pathname too long", dest,
			shortname);
		return (1);
E 22
I 22
D 24
	/* got a directory, move each file into it */
E 24
I 24
	/* It's a directory, move each file into it. */
E 24
	(void)strcpy(path, argv[argc - 1]);
	baselen = strlen(path);
	endp = &path[baselen];
	*endp++ = '/';
	++baselen;
D 29
	for (exitval = 0; --argc; ++argv) {
E 29
I 29
	for (rval = 0; --argc; ++argv) {
E 29
D 27
		if ((p = rindex(*argv, '/')) == NULL)
E 27
I 27
		if ((p = strrchr(*argv, '/')) == NULL)
E 27
			p = *argv;
		else
			++p;
D 26
		if ((baselen + (len = strlen(p))) >= MAXPATHLEN)
			(void)fprintf(stderr,
			    "mv: %s: destination pathname too long\n", *argv);
		else {
E 26
I 26
		if ((baselen + (len = strlen(p))) >= MAXPATHLEN) {
D 27
			err("%s: destination pathname too long", *argv);
E 27
I 27
			warnx("%s: destination pathname too long", *argv);
E 27
D 29
			exitval = 1;
E 29
I 29
			rval = 1;
E 29
		} else {
E 26
D 27
			bcopy(p, endp, len + 1);
E 27
I 27
			memmove(endp, p, len + 1);
E 27
D 29
			exitval |= do_move(*argv, path);
E 29
I 29
			if (do_move(*argv, path))
				rval = 1;
E 29
		}
E 22
	}
D 19
	sprintf(target, "%s/%s", dest, shortname);
E 19
I 19
D 22
	(void)sprintf(target, "%s/%s", dest, shortname);
E 19
	return (move(src, target));
E 22
I 22
D 29
	exit(exitval);
E 29
I 29
	exit(rval);
E 29
E 22
}

I 26
int
E 26
E 7
D 22
move(source, target)
D 7
char *source, *target;
E 7
I 7
	char *source, *target;
E 22
I 22
do_move(from, to)
	char *from, *to;
E 22
E 7
{
I 12
D 22
	int targetexists;
I 21
	struct stat s1, s2;
E 22
I 22
D 24
	struct stat sbuf;
E 24
I 24
	struct stat sb;
E 24
	int ask, ch;
I 29
	char modep[15];
E 29
E 22
E 21
E 12
D 7
	register c, i;
	int	status;
	char	buf[MAXN];
E 7

D 6
	if (stat(source, &s1) < 0) {
E 6
I 6
D 22
	if (lstat(source, &s1) < 0) {
E 6
D 7
		fprintf(stderr, "mv: cannot access %s\n", source);
		return(1);
E 7
I 7
D 15
		error("cannot access %s", source);
E 15
I 15
		Perror2(source, "Cannot access");
E 15
		return (1);
E 7
	}
E 22
D 7
	if ((s1.st_mode & S_IFMT) == S_IFDIR) {
		fprintf(stderr, "mv: directory rename only\n");
		return(1);
	}
	if (stat(target, &s2) >= 0) {
		if ((s2.st_mode & S_IFMT) == S_IFDIR) {
			sprintf(buf, "%s/%s", target, dname(source));
			target = buf;
E 7
I 7
	/*
D 22
	 * First, try to rename source to destination.
	 * The only reason we continue on failure is if
	 * the move is on a nondirectory and not across
	 * file systems.
E 22
I 22
D 24
	 * Check access.  If interactive and file exists ask user if it
E 24
I 24
	 * Check access.  If interactive and file exists, ask user if it
E 24
	 * should be replaced.  Otherwise if file exists but isn't writable
	 * make sure the user wants to clobber it.
E 22
	 */
D 12
	if (lstat(target, &s2) >= 0) {
E 12
I 12
D 22
	targetexists = lstat(target, &s2) >= 0;
	if (targetexists) {
E 12
D 15
		if (iflag && !fflag && query("remove %s? ", target) == 0)
			return (1);
E 15
		if (s1.st_dev == s2.st_dev && s1.st_ino == s2.st_ino) {
			error("%s and %s are identical", source, target);
			return (1);
E 22
I 22
	if (!fflg && !access(to, F_OK)) {
		ask = 0;
		if (iflg) {
			(void)fprintf(stderr, "overwrite %s? ", to);
			ask = 1;
E 22
E 7
D 29
		}
I 15
D 20
		if (iflag && !fflag && isatty(fileno(stdin)) &&
		    query("remove %s? ", target) == 0)
			return (1);
E 15
D 6
		if (stat(target, &s2) >= 0) {
E 6
I 6
D 7
		if (lstat(target, &s2) >= 0) {
E 6
			if ((s2.st_mode & S_IFMT) == S_IFDIR) {
				fprintf(stderr, "mv: %s is a directory\n", target);
				return(1);
			} else if (iflag && !fflag) {
				fprintf(stderr, "remove %s? ", target);
				i = c = getchar();
				while (c != '\n' && c != EOF)
					c = getchar();
				if (i != 'y')
					return(1);
			}
			if (s1.st_dev==s2.st_dev && s1.st_ino==s2.st_ino) {
				fprintf(stderr, "mv: %s and %s are identical\n",
						source, target);
				return(1);
			}
			if (access(target, 2) < 0 && !fflag && isatty(fileno(stdin))) {
				fprintf(stderr, "override protection %o for %s? ", 
					s2.st_mode & MODEBITS, target);
				i = c = getchar();
				while (c != '\n' && c != EOF)
					c = getchar();
				if (i != 'y')
					return(1);
			}
			if (unlink(target) < 0) {
				fprintf(stderr, "mv: cannot unlink %s\n", target);
				return(1);
			}
E 7
I 7
		if (access(target, 2) < 0 && !fflag && isatty(fileno(stdin))) {
			if (query("override protection %o for %s? ",
			  s2.st_mode & MODEBITS, target) == 0)
E 20
I 20
D 22
		if (!fflag && isatty(fileno(stdin)))
			if (iflag) {
				if (!query("remove %s? ", target))
					return (1);
			}
			else if (access(target, W_OK) < 0 &&
			    !query("override protection %o for %s? ",
			    s2.st_mode & MODEBITS, target))
E 20
				return (1);
E 22
I 22
D 24
		else if (access(to, W_OK) && !stat(to, &sbuf)) {
E 24
I 24
		else if (access(to, W_OK) && !stat(to, &sb)) {
E 24
			(void)fprintf(stderr, "override mode %o on %s? ",
D 24
			    sbuf.st_mode & 07777, to);
E 24
I 24
			    sb.st_mode & 07777, to);
E 29
I 29
		} else if (access(to, W_OK) && !stat(to, &sb)) {
			strmode(sb.st_mode, modep);
			(void)fprintf(stderr, "override %s%s%s/%s for %s? ",
			    modep + 1, modep[9] == ' ' ? "" : " ",
			    user_from_uid(sb.st_uid, 0),
			    group_from_gid(sb.st_gid, 0), to);
E 29
E 24
			ask = 1;
		}
		if (ask) {
			if ((ch = getchar()) != EOF && ch != '\n')
				while (getchar() != '\n');
			if (ch != 'y')
D 26
				return(0);
E 26
I 26
				return (0);
E 26
		}
E 22
E 7
D 20
		}
E 20
I 7
D 12
		if (rename(source, target) >= 0)
			return (0);
		if (errno != EXDEV) {
			Perror2(source, "rename");
			return (1);
		}
		if (ISDIR(s1)) {
			error("can't mv directories across file systems");
			return (1);
		}
		if (unlink(target) < 0) {
			error("cannot unlink %s", target);
			return (1);
		}
	} else {
		if (rename(source, target) >= 0)
			return (0);
		if (ISDIR(s1)) {
			Perror2(source, "rename");
			return (1);
		}
E 12
I 12
	}
D 22
	if (rename(source, target) >= 0)
		return (0);
E 22
I 22
	if (!rename(from, to))
D 26
		return(0);
E 26
I 26
		return (0);
E 26
I 24

E 24
E 22
	if (errno != EXDEV) {
D 16
		Perror2(source, "rename");
E 16
I 16
D 22
		Perror2(errno == ENOENT && targetexists == 0 ? target : source,
		    "rename");
E 16
		return (1);
E 22
I 22
D 26
		(void)fprintf(stderr,
		    "mv: rename %s to %s: %s\n", from, to, strerror(errno));
		return(1);
E 26
I 26
D 27
		err("rename %s to %s: %s", from, to, strerror(errno));
E 27
I 27
		warn("rename %s to %s", from, to);
E 27
		return (1);
E 26
E 22
	}
I 24

E 24
D 22
	if (ISDIR(s1)) {
		error("can't mv directories across file systems");
		return (1);
	}
	if (targetexists && unlink(target) < 0) {
D 15
		error("cannot unlink %s", target);
E 15
I 15
		Perror2(target, "Cannot unlink");
E 15
		return (1);
E 12
E 7
	}
E 22
D 6
	if (link(source, target) < 0) {
E 6
I 6
D 7
	if ((s1.st_mode & S_IFMT) == S_IFLNK) {
E 7
I 7
	/*
D 22
	 * File can't be renamed, try to recreate the symbolic
	 * link or special device, or copy the file wholesale
	 * between file systems.
E 22
I 22
D 24
	 * if rename fails, and it's a regular file, do the copy
	 * internally; otherwise, use cp and rm.
E 24
I 24
D 29
	 * If rename fails, and it's a regular file, do the copy internally;
	 * otherwise, use cp and rm.
E 29
I 29
	 * If rename fails because we're trying to cross devices, and
	 * it's a regular file, do the copy internally; otherwise, use
	 * cp and rm.
E 29
E 24
E 22
	 */
D 22
	if (ISLNK(s1)) {
E 7
		register m;
D 7
		char symln[MAXN];
E 7
I 7
D 15
		char symln[MAXPATHLEN];
E 15
I 15
		char symln[MAXPATHLEN + 1];
E 15
E 7

D 15
		if (readlink(source, symln, sizeof (symln)) < 0) {
E 15
I 15
		m = readlink(source, symln, sizeof (symln) - 1);
		if (m < 0) {
E 15
D 7
			perror(source);
E 7
I 7
			Perror(source);
E 7
			return (1);
		}
I 15
		symln[m] = '\0';

E 15
D 18
		m = umask(~(s1.st_mode & MODEBITS));
E 18
I 18
		(void) umask(~(s1.st_mode & MODEBITS));
E 18
		if (symlink(symln, target) < 0) {
D 7
			perror(target);
E 7
I 7
			Perror(target);
E 7
			return (1);
		}
D 7
		umask(m);
	} else if (link(source, target) < 0) {
E 7
I 7
D 18
		(void) umask(m);
E 18
		goto cleanup;
E 22
I 22
D 24
	if (stat(from, &sbuf)) {
		(void)fprintf(stderr,
		    "mv: %s: %s\n", from, strerror(errno));
E 24
I 24
	if (stat(from, &sb)) {
D 26
		(void)fprintf(stderr, "mv: %s: %s\n", from, strerror(errno));
E 24
		return(1);
E 26
I 26
D 27
		err("%s: %s", from, strerror(errno));
E 27
I 27
		warn("%s", from);
E 27
		return (1);
E 26
E 22
	}
I 18
D 22
	(void) umask(0);
E 18
	if (ISDEV(s1)) {
I 9
D 15
		time_t tv[2];
E 15
I 15
		struct timeval tv[2];
E 22
I 22
D 24
	return(S_ISREG(sbuf.st_mode) ?
	    fastcopy(from, to, &sbuf) : copy(from, to));
E 24
I 24
D 26
	return(S_ISREG(sb.st_mode) ?
E 26
I 26
	return (S_ISREG(sb.st_mode) ?
E 26
	    fastcopy(from, to, &sb) : copy(from, to));
E 24
}
E 22
E 15

I 26
int
E 26
E 9
D 22
		if (mknod(target, s1.st_mode, s1.st_rdev) < 0) {
			Perror(target);
			return (1);
		}
E 22
I 22
fastcopy(from, to, sbp)
	char *from, *to;
	struct stat *sbp;
{
	struct timeval tval[2];
	static u_int blen;
	static char *bp;
	register int nread, from_fd, to_fd;
D 24
	char *malloc();
E 24
E 22
D 9
		(void) utime(target, &s1.st_atime);
E 9
I 9
D 15
		/* kludge prior to utimes */
		tv[0] = s1.st_atime;
		tv[1] = s1.st_mtime;
		(void) utime(target, tv);
E 15
I 15

D 22
		tv[0].tv_sec = s1.st_atime;
		tv[0].tv_usec = 0;
		tv[1].tv_sec = s1.st_mtime;
		tv[1].tv_usec = 0;
		(void) utimes(target, tv);
E 15
E 9
		goto cleanup;
E 22
I 22
	if ((from_fd = open(from, O_RDONLY, 0)) < 0) {
D 24
		(void)fprintf(stderr,
		    "mv: %s: %s\n", from, strerror(errno));
E 24
I 24
D 26
		error(from);
E 24
		return(1);
E 26
I 26
D 27
		err("%s: %s", from, strerror(errno));
E 27
I 27
		warn("%s", from);
E 27
		return (1);
E 26
E 22
	}
D 22
	if (ISREG(s1)) {
D 15
		int i, c, status;
I 9
		time_t tv[2];
E 15
I 15
		register int fi, fo, n;
		struct timeval tv[2];
		char buf[MAXBSIZE];
E 15
E 9

E 7
E 6
D 15
		i = fork();
		if (i == -1) {
D 7
			fprintf(stderr, "mv: try again\n");
			return(1);
E 7
I 7
			error("try again");
E 15
I 15
		fi = open(source, 0);
		if (fi < 0) {
			Perror(source);
E 15
			return (1);
E 22
I 22
D 24
	if ((to_fd = open(to, O_WRONLY|O_CREAT|O_TRUNC, sbp->st_mode)) < 0) {
		(void)fprintf(stderr,
		    "mv: %s: %s\n", to, strerror(errno));
E 24
I 24
D 29
	if ((to_fd = open(to, O_CREAT|O_TRUNC|O_WRONLY, sbp->st_mode)) < 0) {
E 29
I 29
	if ((to_fd =
	    open(to, O_CREAT | O_TRUNC | O_WRONLY, sbp->st_mode)) < 0) {
E 29
D 26
		error(to);
E 26
I 26
D 27
		err("%s: %s", to, strerror(errno));
E 27
I 27
		warn("%s", to);
E 27
E 26
E 24
		(void)close(from_fd);
D 26
		return(1);
E 26
I 26
		return (1);
E 26
	}
	if (!blen && !(bp = malloc(blen = sbp->st_blksize))) {
D 24
		(void)fprintf(stderr, "mv: %s: out of memory.\n", from);
E 24
I 24
D 26
		error(NULL);
E 24
		return(1);
E 26
I 26
D 27
		err("%s", strerror(errno));
E 27
I 27
		warn(NULL);
E 27
		return (1);
E 26
	}
	while ((nread = read(from_fd, bp, blen)) > 0)
		if (write(to_fd, bp, nread) != nread) {
D 24
			(void)fprintf(stderr, "mv: %s: %s\n",
			    to, strerror(errno));
E 24
I 24
D 26
			error(to);
E 26
I 26
D 27
			err("%s: %s", to, strerror(errno));
E 27
I 27
			warn("%s", to);
E 27
E 26
E 24
			goto err;
E 22
E 7
		}
D 15
		if (i == 0) {
			execl("/bin/cp", "cp", source, target, 0);
D 7
			fprintf(stderr, "mv: cannot exec cp\n");
E 7
I 7
			error("cannot exec /bin/cp");
E 7
			exit(1);
		}
		while ((c = wait(&status)) != i && c != -1)
			;
		if (status != 0)
E 15
I 15
D 22

		fo = creat(target, s1.st_mode & MODEBITS);
		if (fo < 0) {
			Perror(target);
			close(fi);
E 15
D 7
			return(1);
		utime(target, &s1.st_atime);
E 7
I 7
			return (1);
D 9
		(void) utime(target, &s1.st_atime);
E 9
I 9
D 15
		/* kludge prior to utimes */
		tv[0] = s1.st_atime;
		tv[1] = s1.st_mtime;
		(void) utime(target, tv);
E 15
I 15
		}

		for (;;) {
			n = read(fi, buf, sizeof buf);
			if (n == 0) {
				break;
			} else if (n < 0) {
				Perror2(source, "read");
				close(fi);
				close(fo);
				return (1);
			} else if (write(fo, buf, n) != n) {
				Perror2(target, "write");
				close(fi);
				close(fo);
				return (1);
			}
		}

		close(fi);
		close(fo);

		tv[0].tv_sec = s1.st_atime;
		tv[0].tv_usec = 0;
		tv[1].tv_sec = s1.st_mtime;
		tv[1].tv_usec = 0;
		(void) utimes(target, tv);
E 15
E 9
		goto cleanup;
E 22
I 22
	if (nread < 0) {
D 24
		(void)fprintf(stderr, "mv: %s: %s\n", from, strerror(errno));
E 24
I 24
D 26
		error(from);
E 26
I 26
D 27
		err("%s: %s", from, strerror(errno));
E 26
E 24
err:		(void)unlink(to);
E 27
I 27
		warn("%s", from);
err:		if (unlink(to))
			warn("%s: remove", to);
E 27
		(void)close(from_fd);
		(void)close(to_fd);
D 26
		return(1);
E 26
I 26
		return (1);
E 26
E 22
E 7
	}
D 7
	if (unlink(source) < 0) {
		fprintf(stderr, "mv: cannot unlink %s\n", source);
		return(1);
	}
	return(0);
}
E 7
I 7
D 22
	error("%s: unknown file type %o", source, s1.st_mode);
	return (1);
E 22
I 22
D 27
	(void)fchown(to_fd, sbp->st_uid, sbp->st_gid);
	(void)fchmod(to_fd, sbp->st_mode);
E 22
E 7

E 27
D 7
mvdir(source, target)
char *source, *target;
{
	register char *p;
	register i;
	char buf[MAXN];
	char c,cc;

	if (stat(target, &s2) >= 0) {
		if ((s2.st_mode&S_IFMT) != S_IFDIR) {
			fprintf(stderr, "mv: %s exists\n", target);
			return(1);
D 3
		} else if (iflag && !fflag) {
			fprintf(stderr, "remove %s? ", target);
			cc = c = getchar();
			while (c != '\n' && c != EOF)
				c = getchar();
			if (cc != 'y')
				return(1);
E 3
		}
D 5
		if (strlen(target) > MAXN-DIRSIZ-2) {
E 5
I 5
		p = dname(source);
		if (strlen(target) > MAXN-strlen(p)-2) {
E 5
			fprintf(stderr, "mv :target name too long\n");
			return(1);
		}
		strcpy(buf, target);
		target = buf;
		strcat(buf, SDELIM);
D 5
		strcat(buf, dname(source));
E 5
I 5
		strcat(buf, p);
E 5
		if (stat(target, &s2) >= 0) {
			fprintf(stderr, "mv: %s exists\n", buf);
			return(1);
		}
	}
	if (strcmp(source, target) == 0) {
		fprintf(stderr, "mv: ?? source == target, source exists and target doesnt\n");
		return(1);
	}
	p = dname(source);
	if (!strcmp(p, DOT) || !strcmp(p, DOTDOT) || !strcmp(p, "") || p[strlen(p)-1]=='/') {
		fprintf(stderr, "mv: cannot rename %s\n", p);
		return(1);
	}
	if (stat(pname(source), &s1) < 0 || stat(pname(target), &s2) < 0) {
		fprintf(stderr, "mv: cannot locate parent\n");
		return(1);
	}
	if (access(pname(target), 2) < 0) {
		fprintf(stderr, "mv: no write access to %s\n", pname(target));
		return(1);
	}
	if (access(pname(source), 2) < 0) {
		fprintf(stderr, "mv: no write access to %s\n", pname(source));
		return(1);
	}
D 4
	if (access(source, 2) < 0) {
		fprintf(stderr, "mv: no write access to %s\n", source);
		return(1);
	}
E 4
	if (s1.st_dev != s2.st_dev) {
		fprintf(stderr, "mv: cannot move directories across devices\n");
		return(1);
	}
	if (s1.st_ino != s2.st_ino) {
		char dst[MAXN+5];

		if (chkdot(source) || chkdot(target)) {
			fprintf(stderr, "mv: Sorry, path names including %s aren't allowed\n", DOTDOT);
			return(1);
		}
		stat(source, &s1);
		if (check(pname(target), s1.st_ino))
			return(1);
		for (i = 1; i <= NSIG; i++)
			signal(i, SIG_IGN);
		if (link(source, target) < 0) {
			fprintf(stderr, "mv: cannot link %s to %s\n", target, source);
			return(1);
		}
		if (unlink(source) < 0) {
			fprintf(stderr, "mv: %s: cannot unlink\n", source);
			unlink(target);
			return(1);
		}
		strcat(dst, target);
		strcat(dst, "/");
		strcat(dst, DOTDOT);
		if (unlink(dst) < 0) {
			fprintf(stderr, "mv: %s: cannot unlink\n", dst);
			if (link(target, source) >= 0)
				unlink(target);
			return(1);
		}
		if (link(pname(target), dst) < 0) {
			fprintf(stderr, "mv: cannot link %s to %s\n",
				dst, pname(target));
			if (link(pname(source), dst) >= 0)
				if (link(target, source) >= 0)
					unlink(target);
			return(1);
		}
		return(0);
	}
	if (link(source, target) < 0) {
		fprintf(stderr, "mv: cannot link %s and %s\n",
			source, target);
		return(1);
	}
E 7
I 7
D 22
cleanup:
E 7
	if (unlink(source) < 0) {
D 7
		fprintf(stderr, "mv: ?? cannot unlink %s\n", source);
		return(1);
E 7
I 7
D 15
		error("cannot unlink %s", source);
E 15
I 15
		Perror2(source, "Cannot unlink");
E 15
		return (1);
E 7
	}
D 7
	return(0);
E 7
I 7
	return (0);
E 7
}
E 22
I 22
	(void)close(from_fd);
D 27
	(void)close(to_fd);
E 27
E 22

I 27
	if (fchown(to_fd, sbp->st_uid, sbp->st_gid))
		warn("%s: set owner/group", to);
	if (fchmod(to_fd, sbp->st_mode))
		warn("%s: set mode", to);

E 27
D 7
char *
pname(name)
register char *name;
E 7
I 7
D 22
/*VARARGS*/
query(prompt, a1, a2)
	char *a1;
E 7
{
D 7
	register c;
	register char *p, *q;
	static	char buf[MAXN];
E 7
I 7
D 15
	register char i, c;
E 15
I 15
	register int i, c;
E 15
E 7

D 7
	p = q = buf;
	while (c = *p++ = *name++)
		if (c == DELIM)
			q = p-1;
	if (q == buf && *q == DELIM)
		q++;
	*q = 0;
	return buf[0]? buf : DOT;
E 7
I 7
	fprintf(stderr, prompt, a1, a2);
	i = c = getchar();
	while (c != '\n' && c != EOF)
		c = getchar();
	return (i == 'y');
E 22
I 22
	tval[0].tv_sec = sbp->st_atime;
	tval[1].tv_sec = sbp->st_mtime;
	tval[0].tv_usec = tval[1].tv_usec = 0;
D 27
	(void)utimes(to, tval);
	(void)unlink(from);
E 27
I 27
	if (utimes(to, tval))
		warn("%s: set times", to);

	if (close(to_fd)) {
		warn("%s", to);
		return (1);
	}

	if (unlink(from)) {
		warn("%s: remove", from);
		return (1);
	}
E 27
D 26
	return(0);
E 26
I 26
	return (0);
E 26
E 22
E 7
}

I 26
int
E 26
D 22
char *
dname(name)
D 7
register char *name;
E 7
I 7
	register char *name;
E 22
I 22
copy(from, to)
	char *from, *to;
E 22
E 7
{
D 22
	register char *p;
E 22
I 22
	int pid, status;
E 22

D 22
	p = name;
	while (*p)
		if (*p++ == DELIM && *p)
			name = p;
	return name;
E 22
I 22
D 29
	if (!(pid = vfork())) {
D 25
		execlp(_PATH_CP, "mv", "-pr", from, to);
E 25
I 25
D 26
		execl(_PATH_CP, "mv", "-pr", from, to, NULL);
E 25
D 24
		(void)fprintf(stderr, "mv: can't exec %s.\n", _PATH_CP);
E 24
I 24
		error(_PATH_CP);
E 26
I 26
		execl(_PATH_CP, "mv", "-pR", from, to, NULL);
E 29
I 29
	if ((pid = vfork()) == 0) {
		execl(_PATH_CP, "mv", "-PRp", from, to, NULL);
E 29
D 27
		err("%s: %s", _PATH_CP, strerror(errno));
E 27
I 27
		warn("%s", _PATH_CP);
E 27
E 26
E 24
		_exit(1);
	}
D 27
	(void)waitpid(pid, &status, 0);
	if (!WIFEXITED(status) || WEXITSTATUS(status))
E 27
I 27
	if (waitpid(pid, &status, 0) == -1) {
		warn("%s: waitpid", _PATH_CP);
E 27
D 26
		return(1);
E 26
I 26
		return (1);
I 27
	}
	if (!WIFEXITED(status)) {
		warn("%s: did not terminate normally", _PATH_CP);
		return (1);
	}
	if (WEXITSTATUS(status)) {
		warn("%s: terminated with %d (non-zero) status",
		    _PATH_CP, WEXITSTATUS(status));
		return (1);
	}
E 27
E 26
	if (!(pid = vfork())) {
D 25
		execlp(_PATH_RM, "mv", "-rf", from);
E 25
I 25
		execl(_PATH_RM, "mv", "-rf", from, NULL);
E 25
D 24
		(void)fprintf(stderr, "mv: can't exec %s.\n", _PATH_RM);
E 24
I 24
D 26
		error(_PATH_RM);
E 26
I 26
D 27
		err("%s: %s", _PATH_RM, strerror(errno));
E 27
I 27
		warn("%s", _PATH_RM);
E 27
E 26
E 24
		_exit(1);
	}
D 27
	(void)waitpid(pid, &status, 0);
D 26
	return(!WIFEXITED(status) || WEXITSTATUS(status));
E 26
I 26
	return (!WIFEXITED(status) || WEXITSTATUS(status));
E 27
I 27
	if (waitpid(pid, &status, 0) == -1) {
		warn("%s: waitpid", _PATH_RM);
		return (1);
	}
	if (!WIFEXITED(status)) {
		warn("%s: did not terminate normally", _PATH_RM);
		return (1);
	}
	if (WEXITSTATUS(status)) {
		warn("%s: terminated with %d (non-zero) status",
		    _PATH_RM, WEXITSTATUS(status));
		return (1);
	}
	return (0);
E 27
E 26
I 24
}

D 26
error(s)
	char *s;
{
	if (s)
		(void)fprintf(stderr, "mv: %s: %s\n", s, strerror(errno));
	else
		(void)fprintf(stderr, "mv: %s\n", strerror(errno));
E 24
E 22
}

E 26
I 26
void
E 26
D 7
check(spth, dinode)
char *spth;
ino_t dinode;
E 7
I 7
D 22
/*VARARGS*/
error(fmt, a1, a2)
	char *fmt;
E 7
{
D 7
	char nspth[MAXN];
	struct stat sbuf;
E 7

D 7
	sbuf.st_ino = 0;
E 7
I 7
	fprintf(stderr, "mv: ");
	fprintf(stderr, fmt, a1, a2);
	fprintf(stderr, "\n");
}
E 7

D 7
	strcpy(nspth, spth);
	while (sbuf.st_ino != ROOTINO) {
		if (stat(nspth, &sbuf) < 0) {
			fprintf(stderr, "mv: cannot access %s\n", nspth);
			return(1);
		}
		if (sbuf.st_ino == dinode) {
			fprintf(stderr, "mv: cannot move a directory into itself\n");
			return(1);
		}
		if (strlen(nspth) > MAXN-2-sizeof(DOTDOT)) {
			fprintf(stderr, "mv: name too long\n");
			return(1);
		}
		strcat(nspth, SDELIM);
		strcat(nspth, DOTDOT);
	}
	return(0);
E 7
I 7
Perror(s)
	char *s;
{
	char buf[MAXPATHLEN + 10];
D 19
	
	sprintf(buf, "mv: %s", s);
E 19
I 19

	(void)sprintf(buf, "mv: %s", s);
E 19
	perror(buf);
E 7
}

D 7
chkdot(s)
register char *s;
E 7
I 7
Perror2(s1, s2)
	char *s1, *s2;
E 7
{
D 7
	do {
		if (strcmp(dname(s), DOTDOT) == 0)
			return(1);
		s = pname(s);
	} while (strcmp(s, DOT) != 0 && strcmp(s, SDELIM) != 0);
	return(0);
E 7
I 7
	char buf[MAXPATHLEN + 20];

D 19
	sprintf(buf, "mv: %s: %s", s1, s2);
E 19
I 19
	(void)sprintf(buf, "mv: %s: %s", s1, s2);
E 19
	perror(buf);
I 21
}

E 22
usage()
{
D 22
	fputs("usage: mv [-if] file1 file2 or mv [-if] file/directory ... directory\n", stderr);
E 22
I 22
	(void)fprintf(stderr,
"usage: mv [-if] src target;\n   or: mv [-if] src1 ... srcN directory\n");
E 22
	exit(1);
I 26
D 27
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
	(void)fprintf(stderr, "mv: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 27
E 26
E 21
E 7
}
E 1
