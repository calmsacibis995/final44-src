h41081
s 00020/00023/00357
d D 8.8 95/04/27 17:02:14 bostic 39 38
c Correct test for return value of getopt(3).
c Don't prompt twice to remove a directory.
c Don't print two error messages if a directory could not be removed.
c Get rid of bogus extra variable in rm_file().
c Add `-P' and -W options to usage string; random lint and prettiness police
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/00378
d D 8.7 94/10/18 15:34:56 mckusick 38 37
c unwhiteout => undelete
e
s 00040/00012/00340
d D 8.6 94/07/28 03:38:22 pendry 37 36
c changes for whiteouts and union filesystem
e
s 00086/00016/00266
d D 8.5 94/04/18 06:21:45 bostic 36 35
c add the -P (paranoid) option, overwrite regular files
e
s 00015/00011/00267
d D 8.4 94/04/01 10:05:32 bostic 35 34
c don't depend on errno being set by fts(3)
c check error return from fts_Read
c setting errno and then not exiting isn't safe
e
s 00009/00009/00269
d D 8.3 94/04/01 03:17:49 pendry 34 33
c prettyness police
e
s 00003/00002/00275
d D 8.2 94/01/02 18:05:44 bostic 33 32
c check stdin_ok first, may not have stat'ed the file
e
s 00005/00005/00272
d D 8.1 93/06/02 11:45:42 bostic 32 31
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00272
d D 5.2 93/06/02 11:45:21 bostic 31 28
c don't quit on FTS_DNR directories; the user entered 'rm -rf a a a b'
c and fts found the directory, but once it was deleted couldn't read it.
e
s 00005/00004/00272
d R 8.2 93/06/02 11:43:51 bostic 30 29
c don't quit on FTS_DNR directories; the user entered 'rm -rf a a a b' and
c fts found the directory, but once it was deleted couldn't read it.
e
s 00005/00005/00271
d R 8.1 93/05/31 15:09:05 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00056/00048/00220
d D 5.1 93/04/29 13:55:46 bostic 28 27
c use err/warn from C library; lint, minor cleanups
e
s 00002/00002/00266
d D 4.27 92/01/27 09:59:14 bostic 27 26
c fts_statb -> fts_statp
e
s 00008/00018/00260
d D 4.26 91/03/10 14:51:36 bostic 26 25
c new fts(3) sets errno correctly, don't second-guess it; bring man page
c up to date with POSIX.2 Draft 11, add COMPATIBILITY section
e
s 00226/00203/00052
d D 4.25 90/12/08 00:01:02 bostic 25 24
c new version of rm from scratch and the POSIX.2 description
e
s 00012/00007/00243
d D 4.24 90/11/05 11:07:15 karels 24 23
c use strerror, and tell me *why* things failed!
e
s 00009/00003/00241
d D 4.23 88/12/05 10:31:53 bostic 23 22
c find . and .. if not at the end of path, i.e. "rm -r /tmp/.*"
e
s 00039/00060/00205
d D 4.22 88/04/21 11:42:45 bostic 22 21
c add getopt for "--" capability
e
s 00002/00001/00263
d D 4.21 87/12/20 09:17:26 bostic 21 20
c "not removed" doesn't tell you a whole helluva lot
e
s 00001/00001/00263
d D 4.20 87/04/08 18:21:43 bostic 20 19
c realloc not used
e
s 00008/00006/00256
d D 4.19 87/04/07 18:14:38 bostic 19 18
c ask for protection override even if -i set; bug report 4.2BSD/bin/49
e
s 00001/00001/00261
d D 4.18 86/01/06 13:51:58 mckusick 18 17
c ``rm -f'' produces no error message (from whm%arizona.csnet)
e
s 00003/00007/00259
d D 4.17 85/11/05 18:57:36 bloom 17 16
c allocate only enough space for the maximum path length (should really walk
c the tree instead of building a path)
e
s 00071/00067/00195
d D 4.16 85/03/18 12:46:35 ralph 16 15
c don't use chdir(). Build full name & malloc size needed.
e
s 00025/00016/00237
d D 4.15 85/03/13 15:05:17 ralph 15 14
c always exit 0 if -f given.
e
s 00181/00092/00072
d D 4.14 85/03/08 13:40:40 ralph 14 13
c fix rm -r limitations on number of open files.
e
s 00008/00001/00156
d D 4.13 85/02/14 17:10:52 serge 13 12
c usage error message; BUFSIZ -> MAXPATHLEN
e
s 00002/00002/00155
d D 4.12 83/06/30 14:51:49 sam 12 11
c from sun
e
s 00012/00025/00145
d D 4.11 82/12/19 13:16:42 sam 11 10
c use rmdir sys call
e
s 00001/00001/00169
d D 4.10 82/06/25 12:53:01 sam 10 9
c can't access a symbolic link, get target
e
s 00001/00001/00169
d D 4.9 82/05/07 16:47:29 mckusick 9 8
c update to new fs
e
s 00001/00001/00169
d D 4.8 82/03/31 21:55:59 mckusic 8 7
c change <sys/types.h> to <sys/param.h> for benefit of <ndir.h>
e
s 00001/00001/00169
d D 4.7 82/03/31 12:04:56 root 7 6
c use lstat
e
s 00003/00012/00167
d D 4.6 82/02/28 13:55:00 root 6 5
c back out incorrect fix
e
s 00009/00008/00170
d D 4.5 82/02/19 17:37:02 mckusic 5 4
c convert to new directory structure
e
s 00011/00002/00167
d D 4.4 82/02/11 12:26:57 root 4 3
c new error message (if you can't rm 'cause you're not owner)
e
s 00005/00005/00164
d D 4.3 81/01/04 20:18:24 root 3 2
c I changed the messages printed out by rm to conform to those
c printed by mv and cp (which I changed some time ago). --- Dave Presotto
e
s 00006/00000/00163
d D 4.2 80/12/18 14:24:41 root 2 1
c A new option '-' has been added which forces all following 
c arguments to be interpreted as file names.  This allows file names 
c starting with - to be specified.
e
s 00163/00000/00000
d D 4.1 80/10/01 17:28:13 bill 1 0
c date and time created 80/10/01 17:28:13 by bill
e
u
U
t
T
I 1
D 25
static char *sccsid = "%W% (Berkeley) %G%";
D 14
int	errcode;
E 14
I 4
D 6
short	uid, euid;
E 6
E 4

I 14
/*
 * rm - for ReMoving files, directories & trees.
E 25
I 25
/*-
D 32
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 32
I 32
D 35
 * Copyright (c) 1990, 1993
E 35
I 35
 * Copyright (c) 1990, 1993, 1994
E 35
 *	The Regents of the University of California.  All rights reserved.
E 32
 *
 * %sccs.include.redist.c%
E 25
 */

E 14
D 25
#include <stdio.h>
D 8
#include <sys/types.h>
E 8
I 8
#include <sys/param.h>
I 24
#include <sys/errno.h>
E 24
E 8
#include <sys/stat.h>
D 5
#include <sys/dir.h>
E 5
I 5
D 9
#include <ndir.h>
E 9
I 9
D 12
#include <dir.h>
E 12
I 12
#include <sys/dir.h>
I 14
#include <sys/file.h>
E 25
I 25
#ifndef lint
D 32
char copyright[] =
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
E 32
I 32
static char copyright[] =
D 35
"%Z% Copyright (c) 1990, 1993\n\
E 35
I 35
"%Z% Copyright (c) 1990, 1993, 1994\n\
E 35
	The Regents of the University of California.  All rights reserved.\n";
E 32
#endif /* not lint */
E 25
E 14
E 12
E 9
E 5

D 14
char	*sprintf();
E 14
I 14
D 16
int	fflg;			/* -f force - supress error messages */
int	iflg;			/* -i interrogate user on each file */
int	rflg;			/* -r recurse */
E 16
I 16
D 25
int	fflg;		/* -f force - supress error messages */
int	iflg;		/* -i interrogate user on each file */
int	rflg;		/* -r recurse */
E 25
I 25
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 25
E 16
E 14

I 14
D 16
int	errcode;		/* true if errors occured */
E 16
I 16
D 25
int	errcode;	/* true if errors occured */
E 25
I 25
#include <sys/types.h>
#include <sys/stat.h>
D 34
#include <sys/errno.h>
E 34
I 28

#include <err.h>
I 34
#include <errno.h>
I 36
#include <fcntl.h>
E 36
E 34
E 28
#include <fts.h>
D 28
#include <unistd.h>
E 28
#include <stdio.h>
D 28
#include <string.h>
E 28
#include <stdlib.h>
I 28
#include <string.h>
#include <unistd.h>
E 28
E 25
E 16

D 16
char	*strcpy();
E 16
I 16
D 20
char	*strcpy(), *malloc(), *realloc();
E 20
I 20
D 23
char	*strcpy(), *malloc();
E 23
I 23
D 25
char	*strcpy();
E 25
I 25
D 28
int dflag, fflag, iflag, retval, stdin_ok;
E 28
I 28
D 36
int dflag, fflag, iflag, eval, stdin_ok;
E 36
I 36
D 37
int dflag, eval, fflag, iflag, Pflag, stdin_ok;
E 37
I 37
int dflag, eval, fflag, iflag, Pflag, Wflag, stdin_ok;
E 37
E 36
E 28
E 25
E 23
E 20
E 16

I 28
int	check __P((char *, char *, struct stat *));
void	checkdot __P((char **));
D 36
void	rmfile __P((char **));
void	rmtree __P((char **));
E 36
I 36
void	rm_file __P((char **));
void	rm_overwrite __P((char *, struct stat *));
void	rm_tree __P((char **));
E 36
void	usage __P((void));

E 28
I 25
/*
 * rm --
 *	This rm is different from historic rm's, but is expected to match
 *	POSIX 1003.2 behavior.  The most visible difference is that -f
 *	has two specific effects now, ignore non-existent files and force
 * 	file removal.
 */
D 28

E 28
I 28
int
E 28
E 25
E 14
main(argc, argv)
D 14
char *argv[];
E 14
I 14
D 22
	char *argv[];
E 22
I 22
	int argc;
D 28
	char **argv;
E 28
I 28
	char *argv[];
E 28
E 22
E 14
{
I 25
D 28
	extern char *optarg;
E 28
E 25
D 22
	register char *arg;
E 22
I 22
D 34
	extern int optind;
E 34
D 25
	int ch;
E 25
I 25
	int ch, rflag;
E 25
E 22
D 14
	int fflg, iflg, rflg;
E 14

D 14
	fflg = 0;
	if (isatty(0) == 0)
		fflg++;
E 14
I 14
D 25
	fflg = !isatty(0);
E 14
D 22
	iflg = 0;
	rflg = 0;
I 4
D 6
	uid = getuid();
	euid = geteuid();
E 6
E 4
D 14
	while(argc>1 && argv[1][0]=='-') {
E 14
I 14
	while (argc > 1 && argv[1][0] == '-') {
E 14
		arg = *++argv;
		argc--;
I 2

		/*
		 *  all files following a null option are considered file names
		 */
D 14
		if (*(arg+1) == '\0') break;
E 14
I 14
		if (arg[1] == '\0')
E 22
I 22
	while ((ch = getopt(argc, argv, "-Rfir")) != EOF)
		switch((char)ch) {
		case '-':
			goto endarg;
E 25
I 25
D 36
	rflag = 0;
	while ((ch = getopt(argc, argv, "dfiRr")) != EOF)
E 36
I 36
	Pflag = rflag = 0;
D 37
	while ((ch = getopt(argc, argv, "dfiPRr")) != EOF)
E 37
I 37
D 39
	while ((ch = getopt(argc, argv, "dfiPRrW")) != EOF)
E 39
I 39
	while ((ch = getopt(argc, argv, "dfiPRrW")) != -1)
E 39
E 37
E 36
		switch(ch) {
		case 'd':
			dflag = 1;
			break;
E 25
		case 'f':
D 25
			fflg++;
E 25
I 25
			fflag = 1;
			iflag = 0;
E 25
E 22
			break;
I 22
		case 'i':
D 25
			iflg++;
E 25
I 25
			fflag = 0;
			iflag = 1;
E 25
			break;
I 36
		case 'P':
			Pflag = 1;
			break;
E 36
		case 'R':
D 26
		case 'r':
E 26
I 26
D 36
		case 'r':			/* compatibility */
E 36
I 36
		case 'r':			/* Compatibility. */
E 36
E 26
D 25
			rflg++;
E 25
I 25
			rflag = 1;
E 25
			break;
I 37
		case 'W':
			Wflag = 1;
			break;
E 37
		case '?':
		default:
			usage();
		}
D 25
endarg:	argv += optind;
E 25
I 25
	argc -= optind;
	argv += optind;
E 25
E 22
E 14

E 2
D 14
		while(*++arg != '\0')
E 14
I 14
D 22
		while (*++arg != '\0')
E 14
			switch(*arg) {
			case 'f':
				fflg++;
				break;
I 14

E 14
			case 'i':
				iflg++;
				break;
I 14

E 14
I 13
			case 'R':
E 13
			case 'r':
				rflg++;
				break;
I 14

E 14
			default:
D 14
				printf("rm: unknown option %s\n", *argv);
E 14
I 14
				fprintf(stderr, "usage: rm [-rif] file ...\n");
E 14
				exit(1);
			}
E 22
I 22
D 25
	if (!*argv) {
		if (fflg)
			exit(0);
E 25
I 25
	if (argc < 1)
E 25
		usage();
E 22
D 25
	}
I 13
D 22

D 18
	if (argc < 2) {
E 18
I 18
	if (argc < 2 && !fflg) {
E 18
		fprintf(stderr, "usage: rm [-rif] file ...\n");
		exit(1);
	}

E 13
D 14
	while(--argc > 0) {
		if(!strcmp(*++argv, "..")) {
			fprintf(stderr, "rm: cannot remove `..'\n");
			continue;
		}
		rm(*argv, fflg, rflg, iflg, 0);
	}
E 14
I 14
	while (--argc > 0)
		(void) rm(*++argv, 0);
E 14

E 22
I 22
	do {
		(void)rm(*argv, 0);
	} while (*++argv);
E 22
D 14
	exit(errcode);
E 14
I 14
	exit(errcode != 0);
E 14
}
E 25

D 14
rm(arg, fflg, rflg, iflg, level)
char arg[];
E 14
I 14
D 16
struct nambuf {
	char	*name;			/* pointer to name */
	struct	nambuf *next;		/* linked list of names */
} path, *pathp;
E 16
I 16
D 25
char	*path;		/* pointer to malloc'ed buffer for path */
char	*pathp;		/* current pointer to end of path */
int	pathsz;		/* size of path */
E 25
I 25
	checkdot(argv);
D 39
	if (!*argv)
D 28
		exit(retval);
E 28
I 28
		exit (eval);
E 39
E 28
E 25
E 16

I 22
D 25
#define	isdot(a)	(a[0] == '.' && (!a[1] || a[1] == '.' && !a[2]))
E 22
/*
 * Return TRUE if sucessful. Recursive with -r (rflg)
 */
rm(arg, level)
	char arg[];
E 14
{
D 14
	struct stat buf;
D 5
	struct direct direct;
	char name[100];
E 5
I 5
	struct direct *dp;
	DIR *dirp;
D 13
	char name[BUFSIZ];
E 13
I 13
	char name[MAXPATHLEN + 1];
E 13
E 5
	int d;
E 14
I 14
	int ok;				/* true if recursive rm succeeded */
	struct stat buf;		/* for finding out what a file is */
	struct direct *dp;		/* for reading a directory */
	DIR *dirp;			/* for reading a directory */
D 16
	char name[MAXNAMLEN + 1];	/* buffer for file name */
E 16
	char prevname[MAXNAMLEN + 1];	/* previous name for -r */
D 16
	struct nambuf nambuf, *pp;
E 16
I 16
D 23
	char *cp;
E 23
I 23
	char *cp, *rindex();
E 25
I 25
D 39
	stdin_ok = isatty(STDIN_FILENO);
E 39
I 39
	if (*argv) {
		stdin_ok = isatty(STDIN_FILENO);
E 39
E 25
E 23
E 16
E 14

D 7
	if(stat(arg, &buf)) {
E 7
I 7
D 14
	if(lstat(arg, &buf)) {
E 7
		if (fflg==0) {
			printf("rm: %s nonexistent\n", arg);
			++errcode;
		}
		return;
E 14
I 14
D 22
	if (dotname(arg)) {
E 22
I 22
D 23
	if (isdot(arg)) {
E 23
I 23
D 25
	cp = rindex(arg, '/');
	if (cp == NULL)
		cp = arg;
E 25
I 25
D 39
	if (rflag)
D 36
		rmtree(argv);
E 36
I 36
		rm_tree(argv);
E 36
E 25
	else
D 25
		++cp;
	if (isdot(cp)) {
E 23
E 22
		fprintf(stderr, "rm: cannot remove `.' or `..'\n");
		return (0);
E 25
I 25
D 36
		rmfile(argv);
E 36
I 36
		rm_file(argv);
E 39
I 39
		if (rflag)
			rm_tree(argv);
		else
			rm_file(argv);
	}

E 39
E 36
D 28
	exit(retval);
E 28
I 28
	exit (eval);
E 28
}

I 28
void
E 28
D 36
rmtree(argv)
E 36
I 36
rm_tree(argv)
E 36
	char **argv;
{
D 34
	register FTS *fts;
	register FTSENT *p;
	register int needstat;
E 34
I 34
	FTS *fts;
	FTSENT *p;
	int needstat;
I 37
	int flags;
E 37
E 34
D 28
	struct stat sb;
E 28

	/*
	 * Remove a file hierarchy.  If forcing removal (-f), or interactive
	 * (-i) or can't ask anyway (stdin_ok), don't stat the file.
	 */
	needstat = !fflag && !iflag && stdin_ok;

	/*
	 * If the -i option is specified, the user can skip on the pre-order
	 * visit.  The fts_number field flags skipped directories.
	 */
#define	SKIPPED	1

D 37
	if (!(fts = fts_open(argv,
	    needstat ? FTS_PHYSICAL : FTS_PHYSICAL|FTS_NOSTAT,
D 28
	    (int (*)())NULL))) {
		(void)fprintf(stderr, "rm: %s.\n", strerror(errno));
		exit(1);
E 25
E 14
	}
E 28
I 28
	    (int (*)())NULL)))
E 37
I 37
	flags = FTS_PHYSICAL;
	if (!needstat)
		flags |= FTS_NOSTAT;
	if (Wflag)
		flags |= FTS_WHITEOUT;
	if (!(fts = fts_open(argv, flags, (int (*)())NULL)))
E 37
		err(1, NULL);
E 28
I 14
D 16
	if (level == 0) {
		path.name = arg;
		path.next = NULL;
		pathp = &path;
	}
E 16
D 25
	if (lstat(arg, &buf)) {
D 15
		if (!fflg)
E 15
I 15
		if (!fflg) {
E 15
D 16
			error("nonexistent");
E 16
I 16
D 24
			fprintf(stderr, "rm: %s nonexistent\n", arg);
E 24
I 24
			fprintf(stderr, "rm: %s: %s\n", arg, strerror(errno));
E 24
E 16
D 15
		errcode++;
E 15
I 15
			errcode++;
		}
E 15
		return (0);		/* error */
	}
E 14
	if ((buf.st_mode&S_IFMT) == S_IFDIR) {
D 14
		if(rflg) {
			if (access(arg, 02) < 0) {
				if (fflg==0)
					printf("%s not changed\n", arg);
				errcode++;
				return;
E 14
I 14
		if (!rflg) {
D 15
			error("directory");
			errcode++;
E 15
I 15
			if (!fflg) {
D 16
				error("directory");
E 16
I 16
				fprintf(stderr, "rm: %s directory\n", arg);
E 16
				errcode++;
			}
E 15
			return (0);
		}
I 16
		if (iflg && level != 0) {
			printf("rm: remove directory %s? ", arg);
			if (!yes())
				return (0);	/* didn't remove everything */
		}
E 16
		if (access(arg, R_OK|W_OK|X_OK) != 0) {
			if (rmdir(arg) == 0)
				return (1);	/* salvaged: removed empty dir */
D 15
			if (!fflg)
E 15
I 15
			if (!fflg) {
E 15
D 16
				error("not changed");
E 16
I 16
D 24
				fprintf(stderr, "rm: %s not changed\n", arg);
E 24
I 24
				fprintf(stderr, "rm: %s not removed: %s\n", arg,
				    strerror(errno));
E 24
E 16
D 15
			errcode++;
E 15
I 15
				errcode++;
			}
E 15
			return (0);		/* error */
		}
D 16
		if (iflg && level != 0) {
			if (!yes("remove directory"))
				return (0);	/* didn't remove everything */
		}
		if (chdir(arg) < 0 || (dirp = opendir(".")) == NULL) {
E 16
I 16
		if ((dirp = opendir(arg)) == NULL) {
E 16
D 15
			if (!fflg)
E 15
I 15
			if (!fflg) {
E 15
D 16
				error("cannot read?");
E 16
I 16
D 24
				fprintf(stderr, "rm: cannot read %s?\n", arg);
E 24
I 24
				fprintf(stderr, "rm: cannot read %s: %s\n",
				    arg, strerror(errno));
E 24
E 16
D 15
			errcode++;
E 15
I 15
				errcode++;
			}
E 15
			return (0);
		}
D 16
		nambuf.name = name;
		nambuf.next = NULL;
		pathp->next = &nambuf;
		pp = pathp;
		pathp = &nambuf;
E 16
I 16
		if (level == 0)
			append(arg);
E 16
		prevname[0] = '\0';
		while ((dp = readdir(dirp)) != NULL) {
D 22
			if (dotname(dp->d_name)) {
E 22
I 22
			if (isdot(dp->d_name)) {
E 22
				strcpy(prevname, dp->d_name);
				continue;
E 14
			}
D 14
			if(iflg && level!=0) {
D 3
				printf("directory %s: ", arg);
E 3
I 3
				printf("remove directory %s? ", arg);
E 3
				if(!yes())
					return;
			}
D 5
			if((d=open(arg, 0)) < 0) {
E 5
I 5
			if((dirp = opendir(arg)) == NULL) {
E 5
D 3
				printf("rm: %s: cannot read\n", arg);
E 3
I 3
				printf("rm: cannot read %s?\n", arg);
E 3
				exit(1);
			}
D 5
			while(read(d, (char *)&direct, sizeof(direct)) == sizeof(direct)) {
				if(direct.d_ino != 0 && !dotname(direct.d_name)) {
					sprintf(name, "%s/%.14s", arg, direct.d_name);
E 5
I 5
			while((dp = readdir(dirp)) != NULL) {
				if(dp->d_ino != 0 && !dotname(dp->d_name)) {
D 6
					sprintf(name, "%s/%.14s", arg, dp->d_name);
E 6
I 6
					sprintf(name, "%s/%s", arg, dp->d_name);
E 6
E 5
					rm(name, fflg, rflg, iflg, level+1);
				}
			}
E 14
I 14
D 16
			strcpy(name, dp->d_name);
E 16
I 16
			append(dp->d_name);
E 16
E 14
D 5
			close(d);
E 5
I 5
			closedir(dirp);
E 5
D 11
			errcode += rmdir(arg, iflg);
E 11
I 11
D 14
			if (dotname(arg))
				return;
			if (iflg) {
				printf("rm: remove %s? ", arg);
				if (!yes())
					return;
			}
			if (rmdir(arg) < 0) {
D 12
				fprintf("rm: ");
E 12
I 12
				fprintf(stderr, "rm: ");
E 12
				perror(arg);
E 14
I 14
D 16
			ok = rm(name, level + 1);
			if ((dirp = opendir(".")) == NULL) {
E 16
I 16
			ok = rm(path, level + 1);
			for (cp = pathp; *--cp != '/' && cp > path; )
				;
			pathp = cp;
			*cp++ = '\0';
			if ((dirp = opendir(arg)) == NULL) {
E 16
D 15
				if (!fflg)
E 15
I 15
				if (!fflg) {
E 15
D 16
					error("cannot read?");
E 16
I 16
D 24
					fprintf(stderr, "rm: cannot read %s?\n", arg);
E 24
I 24
					fprintf(stderr,
					    "rm: cannot reopen %s?: %s\n",
					    arg, strerror(errno));
E 24
E 16
E 14
D 15
				errcode++;
E 15
I 15
					errcode++;
				}
E 25
I 25
D 35
	while (p = fts_read(fts)) {
E 35
I 35
	while ((p = fts_read(fts)) != NULL) {
E 35
D 28
		switch(p->fts_info) {
E 28
I 28
		switch (p->fts_info) {
E 28
D 26
		case FTS_DC:
E 26
		case FTS_DNR:
I 31
D 35
			if (!fflag || errno != ENOENT) {
				warn("%s", p->fts_path);
E 35
I 35
			if (!fflag || p->fts_errno != ENOENT) {
				warnx("%s: %s",
				    p->fts_path, strerror(p->fts_errno));
E 35
				eval = 1;
			}
			continue;
E 31
D 26
		case FTS_DNX:
			break;
E 26
		case FTS_ERR:
D 28
			error(p->fts_path, errno);
			exit(1);
		/*
		 * FTS_NS: assume that if can't stat the file, it can't be
D 26
		 * unlinked.  If we need stat information, should never see
		 * FTS_NS (unless a file specified as an argument doesn't
		 * exist), since such files are in directories that will be
		 * returned FTS_DNX.
E 26
I 26
		 * unlinked.
E 26
		 */
E 28
I 28
D 35
			err(1, "%s", p->fts_path);
E 35
I 35
			errx(1, "%s: %s", p->fts_path, strerror(p->fts_errno));
E 35
D 31

E 31
E 28
		case FTS_NS:
I 28
			/*
			 * FTS_NS: assume that if can't stat the file, it
			 * can't be unlinked.
			 */
E 28
			if (!needstat)
E 25
E 15
I 14
				break;
I 25
D 26
			if (!lstat(p->fts_accpath, &sb))	/* XXX */
				break;
E 26
D 28
			if (!fflag || errno != ENOENT)
				error(p->fts_path, errno);
E 28
I 28
D 35
			if (!fflag || errno != ENOENT) {
				warn("%s", p->fts_path);
E 35
I 35
			if (!fflag || p->fts_errno != ENOENT) {
				warnx("%s: %s",
				    p->fts_path, strerror(p->fts_errno));
E 35
				eval = 1;
			}
E 28
			continue;
D 28
		/* Pre-order: give user chance to skip. */
E 28
I 28
D 31

E 31
E 28
		case FTS_D:
I 28
			/* Pre-order: give user chance to skip. */
E 28
D 39
			if (iflag && !check(p->fts_path, p->fts_accpath,
E 39
I 39
			if (!fflag && !check(p->fts_path, p->fts_accpath,
E 39
D 27
			    &p->fts_statb)) {
E 27
I 27
			    p->fts_statp)) {
E 27
				(void)fts_set(fts, p, FTS_SKIP);
				p->fts_number = SKIPPED;
E 25
E 14
			}
E 11
D 14
			return;
E 14
I 14
D 25
			/* pick up where we left off */
			if (prevname[0] != '\0') {
				while ((dp = readdir(dirp)) != NULL &&
				    strcmp(prevname, dp->d_name) != 0)
					;
			}
			/* skip the one we just failed to delete */
			if (!ok) {
				dp = readdir(dirp);
D 16
				if (dp != NULL && strcmp(name, dp->d_name) != 0)
					error("internal synchronization error");
				strcpy(prevname, name);
E 16
I 16
				if (dp != NULL && strcmp(cp, dp->d_name)) {
					fprintf(stderr,
			"rm: internal synchronization error: %s, %s, %s\n",
						arg, cp, dp->d_name);
				}
				strcpy(prevname, dp->d_name);
E 16
			}
E 25
I 25
			continue;
D 28
		/* Post-order: see if user skipped. */
E 28
I 28
D 31

E 31
E 28
		case FTS_DP:
I 28
			/* Post-order: see if user skipped. */
E 28
			if (p->fts_number == SKIPPED)
				continue;
			break;
I 39
		default:
			if (!fflag &&
			    !check(p->fts_path, p->fts_accpath, p->fts_statp))
				continue;
E 39
E 25
E 14
		}
D 14
		printf("rm: %s directory\n", arg);
		++errcode;
		return;
E 14
I 14
D 25
		closedir(dirp);
D 16
		pathp = pp;
		pathp->next = NULL;
		if (chdir("..") < 0) {
D 15
			if (!fflg)
E 15
I 15
			if (!fflg) {
E 15
				error("cannot cd to '..'?");
D 15
			errcode++;
E 15
I 15
				errcode++;
			}
E 15
			return (0);
E 16
I 16
		if (level == 0) {
			pathp = path;
			*pathp = '\0';
E 16
		}
		if (iflg) {
D 16
			if (!yes("remove"))
E 16
I 16
			printf("rm: remove %s? ", arg);
			if (!yes())
E 16
				return (0);
		}
		if (rmdir(arg) < 0) {
D 15
			if (!fflg || iflg)
E 15
I 15
			if (!fflg || iflg) {
E 15
D 16
				error("not removed");
E 16
I 16
D 24
				fprintf(stderr, "rm: %s not removed\n", arg);
E 24
I 24
				fprintf(stderr, "rm: %s not removed: %s\n", arg,
				    strerror(errno));
E 24
E 16
D 15
			errcode++;
E 15
I 15
				errcode++;
			}
E 15
			return (0);
		}
		return (1);
E 25
I 25
D 31

E 31
D 39
		if (!fflag &&
D 27
		    !check(p->fts_path, p->fts_accpath, &p->fts_statb))
E 27
I 27
		    !check(p->fts_path, p->fts_accpath, p->fts_statp))
E 27
			continue;
E 39

		/*
		 * If we can't read or search the directory, may still be
		 * able to remove it.  Don't print out the un{read,search}able
		 * message unless the remove fails.
		 */
D 26
		if (p->fts_info == FTS_DP || p->fts_info == FTS_DNR ||
		    p->fts_info == FTS_DNX) {
E 26
I 26
D 37
		if (p->fts_info == FTS_DP || p->fts_info == FTS_DNR) {
E 37
I 37
		switch (p->fts_info) {
		case FTS_DP:
		case FTS_DNR:
E 37
E 26
D 39
			if (!rmdir(p->fts_accpath))
E 39
I 39
			if (!rmdir(p->fts_accpath) || fflag && errno == ENOENT)
E 39
				continue;
D 39
			if (errno == ENOENT) {
				if (fflag)
					continue;
			} else if (p->fts_info != FTS_DP)
D 26
				(void)fprintf(stderr, "rm: unable to %s %s.\n",
				    p->fts_info == FTS_DNR ? "read" : "search",
				    p->fts_path);
E 26
I 26
D 28
				(void)fprintf(stderr,
				    "rm: unable to read %s.\n", p->fts_path);
E 28
I 28
				warnx("%s: unable to read", p->fts_path);
E 39
E 28
E 26
D 36
		} else if (!unlink(p->fts_accpath) || fflag && errno == ENOENT)
D 26
				continue;
E 26
I 26
			continue;
E 36
I 36
D 37
		} else {
E 37
I 37
			break;

		case FTS_W:
D 38
			if (!unwhiteout(p->fts_accpath) ||
E 38
I 38
			if (!undelete(p->fts_accpath) ||
E 38
			    fflag && errno == ENOENT)
				continue;
			break;

		default:
E 37
			if (Pflag)
				rm_overwrite(p->fts_accpath, NULL);
			if (!unlink(p->fts_accpath) || fflag && errno == ENOENT)
				continue;
		}
E 36
E 26
D 28
		error(p->fts_path, errno);
E 28
I 28
		warn("%s", p->fts_path);
		eval = 1;
E 28
E 25
E 14
	}
I 35
	if (errno)
		err(1, "fts_read");
E 35
I 25
}
E 25

I 28
void
E 28
D 14
	if(iflg) {
D 3
		printf("%s: ", arg);
E 3
I 3
		printf("rm: remove %s? ", arg);
E 3
		if(!yes())
			return;
	}
	else if(!fflg) {
D 10
		if (access(arg, 02)<0) {
E 10
I 10
		if ((buf.st_mode&S_IFMT) != S_IFLNK && access(arg, 02) < 0) {
E 10
D 3
			printf("rm: %s %o mode ", arg, buf.st_mode&0777);
E 3
I 3
D 4
			printf("rm: override protection %o for %s? ", buf.st_mode&0777, arg);
E 3
			if(!yes())
E 4
I 4
D 6
			if (uid == buf.st_uid || euid == buf.st_uid) {
				printf("rm: override protection %o for %s? ",
					buf.st_mode&0777, arg);
				if(!yes())
					return;
			} else {
				printf("rm: %s: not owner.\n", arg);
E 6
I 6
			printf("rm: override protection %o for %s? ", buf.st_mode&0777, arg);
			if(!yes())
E 6
E 4
				return;
E 14
I 14
D 19
	if (iflg) {
D 16
		if (!yes("remove"))
E 16
I 16
		printf("rm: remove %s? ", arg);
		if (!yes())
E 16
			return (0);
	} else if (!fflg) {
E 19
I 19
D 25
	if (!fflg) {
E 19
		if ((buf.st_mode&S_IFMT) != S_IFLNK && access(arg, W_OK) < 0) {
D 16
			sprintf(name, "override protection %o for",
				buf.st_mode&0777);
			if (!yes(name))
E 16
I 16
			printf("rm: override protection %o for %s? ",
				buf.st_mode&0777, arg);
			if (!yes())
E 16
				return (0);
I 19
			goto rm;
E 25
I 25
D 36
rmfile(argv)
E 36
I 36
rm_file(argv)
E 36
	char **argv;
{
D 34
	register int df;
	register char *f;
E 34
I 34
D 36
	int df;
	char *f;
E 36
E 34
	struct stat sb;
I 36
D 39
	int df, rval;
E 39
I 39
	int rval;
E 39
	char *f;
E 36

D 39
	df = dflag;
E 39
	/*
	 * Remove a file.  POSIX 1003.2 states that, by default, attempting
	 * to remove a directory is an error, so must always stat the file.
	 */
D 35
	while (f = *argv++) {
E 35
I 35
	while ((f = *argv++) != NULL) {
E 35
		/* Assume if can't stat the file, can't unlink it. */
		if (lstat(f, &sb)) {
D 28
			if (!fflag || errno != ENOENT)
				error(f, errno);
E 28
I 28
D 37
			if (!fflag || errno != ENOENT) {
				warn("%s", f);
				eval = 1;
E 37
I 37
			if (Wflag) {
				sb.st_mode = S_IFWHT|S_IWUSR|S_IRUSR;
			} else {
				if (!fflag || errno != ENOENT) {
					warn("%s", f);
					eval = 1;
				}
				continue;
E 37
			}
I 37
		} else if (Wflag) {
			warnx("%s: %s", f, strerror(EEXIST));
			eval = 1;
E 37
E 28
			continue;
E 25
E 19
E 14
I 4
D 6
			}
E 6
E 4
		}
I 37

E 37
D 25
	}
D 14
	if(unlink(arg) && (fflg==0 || iflg)) {
		printf("rm: %s not removed\n", arg);
		++errcode;
E 14
I 14
D 19
	if (unlink(arg) < 0) {
E 19
I 19
	if (iflg) {
		printf("rm: remove %s? ", arg);
		if (!yes())
			return (0);
	}
rm:	if (unlink(arg) < 0) {
E 19
D 15
		if (!fflg || iflg)
E 15
I 15
		if (!fflg || iflg) {
E 15
D 16
			error("not removed");
E 16
I 16
D 21
			fprintf(stderr, "rm: %s not removed\n", arg);
E 21
I 21
D 24
			fprintf(stderr, "rm: %s: ", arg);
			perror((char *)NULL);
E 24
I 24
			fprintf(stderr, "rm: %s: %s\n", arg, strerror(errno));
E 24
E 21
E 16
D 15
		errcode++;
E 15
I 15
			errcode++;
E 25
I 25
D 39
		if (S_ISDIR(sb.st_mode) && !df) {
E 39
I 39
		if (S_ISDIR(sb.st_mode) && !dflag) {
E 39
D 26
			(void)fprintf(stderr, "rm: %s: Is a directory.\n", f);
E 26
I 26
D 28
			(void)fprintf(stderr, "rm: %s: is a directory\n", f);
E 26
			retval = 1;
E 28
I 28
			warnx("%s: is a directory", f);
			eval = 1;
E 28
			continue;
E 25
		}
E 15
D 25
		return (0);
E 25
I 25
D 37
		if (!fflag && !check(f, f, &sb))
E 37
I 37
		if (!fflag && !S_ISWHT(sb.st_mode) && !check(f, f, &sb))
E 37
			continue;
D 36
		if ((S_ISDIR(sb.st_mode) ? rmdir(f) : unlink(f)) &&
D 28
		    (!fflag || errno != ENOENT))
			error(f, errno);
E 28
I 28
		    (!fflag || errno != ENOENT)) {
E 36
I 36
D 37
		if (S_ISDIR(sb.st_mode))
E 37
I 37
		if (S_ISWHT(sb.st_mode))
D 38
			rval = unwhiteout(f);
E 38
I 38
			rval = undelete(f);
E 38
		else if (S_ISDIR(sb.st_mode))
E 37
			rval = rmdir(f);
		else {
			if (Pflag)
				rm_overwrite(f, &sb);
			rval = unlink(f);
		}
		if (rval && (!fflag || errno != ENOENT)) {
E 36
			warn("%s", f);
			eval = 1;
		}
E 28
E 25
E 14
	}
I 14
D 25
	return (1);
E 25
E 14
}
I 36

/*
 * rm_overwrite --
 *	Overwrite the file 3 times with varying bit patterns.
 *
 * XXX
 * This is a cheap way to *really* delete files.  Note that only regular
 * files are deleted, directories (and therefore names) will remain.
 * Also, this assumes a fixed-block file system (like FFS, or a V7 or a
 * System V file system).  In a logging file system, you'll have to have
 * kernel support.
 */
void
rm_overwrite(file, sbp)
	char *file;
	struct stat *sbp;
{
	struct stat sb;
	off_t len;
	int fd, wlen;
	char buf[8 * 1024];

	fd = -1;
	if (sbp == NULL) {
		if (lstat(file, &sb))
			goto err;
		sbp = &sb;
	}
	if (!S_ISREG(sbp->st_mode))
		return;
	if ((fd = open(file, O_WRONLY, 0)) == -1)
		goto err;

#define	PASS(byte) {							\
	memset(buf, byte, sizeof(buf));					\
	for (len = sbp->st_size; len > 0; len -= wlen) {		\
		wlen = len < sizeof(buf) ? len : sizeof(buf);		\
		if (write(fd, buf, wlen) != wlen)			\
			goto err;					\
	}								\
}
	PASS(0xff);
	if (fsync(fd) || lseek(fd, (off_t)0, SEEK_SET))
		goto err;
	PASS(0x00);
	if (fsync(fd) || lseek(fd, (off_t)0, SEEK_SET))
		goto err;
	PASS(0xff);
	if (!fsync(fd) && !close(fd))
		return;

err:	eval = 1;
	warn("%s", file);
}

E 36

I 28
int
E 28
I 14
D 25
/*
D 22
 * boolean: is it "." or ".." ?
 */
E 14
dotname(s)
D 14
char *s;
E 14
I 14
	char *s;
E 14
{
D 14
	if(s[0] == '.')
		if(s[1] == '.')
			if(s[2] == '\0')
				return(1);
E 14
I 14
	if (s[0] == '.')
		if (s[1] == '.')
			if (s[2] == '\0')
				return (1);
E 14
			else
D 14
				return(0);
		else if(s[1] == '\0')
			return(1);
	return(0);
E 14
I 14
				return (0);
		else if (s[1] == '\0')
			return (1);
	return (0);
E 14
D 11
}

rmdir(f, iflg)
char *f;
{
	int status, i;

	if(dotname(f))
		return(0);
	if(iflg) {
D 3
		printf("%s: ", f);
E 3
I 3
		printf("rm: remove %s? ", f);
E 3
		if(!yes())
			return(0);
	}
	while((i=fork()) == -1)
		sleep(3);
	if(i) {
		wait(&status);
		return(status);
	}
	execl("/bin/rmdir", "rmdir", f, 0);
	execl("/usr/bin/rmdir", "rmdir", f, 0);
	printf("rm: can't find rmdir\n");
	exit(1);
E 11
}

D 14
yes()
E 14
I 14
/*
E 22
 * Get a yes/no answer from the user.
 */
D 16
yes(msg)
	char *msg;
E 16
I 16
yes()
E 25
I 25
check(path, name, sp)
	char *path, *name;
	struct stat *sp;
E 25
E 16
E 14
{
I 14
D 16
	register struct nambuf *pp;
E 16
E 14
D 25
	int i, b;
E 25
I 25
D 34
	register int first, ch;
E 34
I 34
	int ch, first;
E 34
D 28
	char modep[15], *user_from_uid(), *group_from_gid();
E 28
I 28
	char modep[15];
E 28
E 25

I 14
D 16
	printf("rm: %s %s", msg, path.name);
	for (pp = &path; pp->next != NULL; pp = pp->next)
		printf("/%s", pp->next->name);
	printf("? ");
E 16
E 14
D 25
	i = b = getchar();
D 14
	while(b != '\n' && b != EOF)
E 14
I 14
	while (b != '\n' && b != EOF)
E 14
		b = getchar();
D 14
	return(i == 'y');
E 14
I 14
	return (i == 'y');
E 25
I 25
	/* Check -i first. */
	if (iflag)
		(void)fprintf(stderr, "remove %s? ", path);
	else {
		/*
		 * If it's not a symbolic link and it's unwritable and we're
		 * talking to a terminal, ask.  Symbolic links are excluded
D 26
		 * because the permissions are meaningless.
E 26
I 26
D 33
		 * because their permissions are meaningless.
E 33
I 33
		 * because their permissions are meaningless.  Check stdin_ok
		 * first because we may not have stat'ed the file.
E 33
E 26
		 */
D 33
		if (S_ISLNK(sp->st_mode) || !stdin_ok || !access(name, W_OK))
E 33
I 33
		if (!stdin_ok || S_ISLNK(sp->st_mode) || !access(name, W_OK))
E 33
D 28
			return(1);
E 28
I 28
			return (1);
E 28
		strmode(sp->st_mode, modep);
		(void)fprintf(stderr, "override %s%s%s/%s for %s? ",
		    modep + 1, modep[9] == ' ' ? "" : " ",
		    user_from_uid(sp->st_uid, 0),
		    group_from_gid(sp->st_gid, 0), path);
	}
	(void)fflush(stderr);

	first = ch = getchar();
	while (ch != '\n' && ch != EOF)
		ch = getchar();
D 28
	return(first == 'y');
E 28
I 28
	return (first == 'y');
E 28
E 25
}

D 25
/*
D 16
 * Print the current path and error message.
E 16
I 16
 * Append 'name' to 'path'.
E 16
 */
D 16
error(msg)
	char *msg;
E 16
I 16
append(name)
	char *name;
E 25
I 25
#define ISDOT(a)	((a)[0] == '.' && (!(a)[1] || (a)[1] == '.' && !(a)[2]))
I 28
void
E 28
checkdot(argv)
	char **argv;
E 25
E 16
{
D 16
	register struct nambuf *pp;
E 16
I 16
D 25
	register int n;
I 23
	char *malloc();
E 25
I 25
D 34
	register char *p, **t, **save;
E 34
I 34
	char *p, **save, **t;
E 34
	int complained;
E 25
E 23
E 16

D 16
	fprintf(stderr, "rm: %s", path.name);
	for (pp = &path; pp->next != NULL; pp = pp->next)
		fprintf(stderr, "/%s", pp->next->name);
	fprintf(stderr, ": %s\n", msg);
E 16
I 16
D 25
	n = strlen(name);
	if (path == NULL) {
D 17
		pathsz = n + 2048;
E 17
I 17
		pathsz = MAXNAMLEN + MAXPATHLEN + 2;
E 17
D 22
		if ((path = malloc(pathsz)) == NULL) {
E 22
I 22
		if ((path = malloc((u_int)pathsz)) == NULL) {
E 22
			fprintf(stderr, "rm: ran out of memory\n");
			exit(1);
		}
		pathp = path;
	} else if (pathp + n + 2 > path + pathsz) {
D 17
		pathsz = n + 2048;
		if ((path = realloc(path, pathsz)) == NULL) {
			fprintf(stderr, "rm: ran out of memory\n");
			exit(1);
		}
		pathp = path;
E 17
I 17
		fprintf(stderr, "rm: path name too long: %s\n", path);
		exit(1);
E 17
	} else if (pathp != path && pathp[-1] != '/')
		*pathp++ = '/';
	strcpy(pathp, name);
	pathp += n;
E 25
I 25
	complained = 0;
	for (t = argv; *t;) {
D 28
		if (p = rindex(*t, '/'))
E 28
I 28
D 35
		if (p = strrchr(*t, '/'))
E 35
I 35
		if ((p = strrchr(*t, '/')) != NULL)
E 35
E 28
			++p;
		else
			p = *t;
		if (ISDOT(p)) {
			if (!complained++)
D 28
			    (void)fprintf(stderr,
				"rm: \".\" and \"..\" may not be removed.\n");
			retval = 1;
E 28
I 28
				warnx("\".\" and \"..\" may not be removed");
			eval = 1;
E 28
D 35
			for (save = t; t[0] = t[1]; ++t);
E 35
I 35
D 39
			for (save = t; (t[0] = t[1]) != NULL; ++t);
E 39
I 39
			for (save = t; (t[0] = t[1]) != NULL; ++t)
				continue;
E 39
E 35
			t = save;
		} else
			++t;
	}
E 25
I 22
}

I 25
D 28
error(name, val)
	char *name;
	int val;
{
	(void)fprintf(stderr, "rm: %s: %s.\n", name, strerror(val));
	retval = 1;
}

E 28
I 28
void
E 28
E 25
usage()
{
I 34

E 34
D 25
	fputs("usage: rm [-rif] file ...\n", stderr);
E 25
I 25
D 39
	(void)fprintf(stderr, "usage: rm [-dfiRr] file ...\n");
E 39
I 39
	(void)fprintf(stderr, "usage: rm [-dfiPRrW] file ...\n");
E 39
E 25
	exit(1);
E 22
E 16
E 14
}
E 1
