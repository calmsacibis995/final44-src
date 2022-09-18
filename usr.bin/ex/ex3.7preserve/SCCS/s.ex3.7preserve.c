h26001
s 00005/00005/00312
d D 8.1 93/06/09 21:47:45 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00181/00265/00136
d D 7.18 91/04/01 08:56:55 bostic 26 25
c bug was that it used "/bin/mail", which got blindly translated to
c libexec/mail.local; change to use sendmil.  Massive changes to welcome it
c into the 90's.
e
s 00000/00001/00401
d D 7.17 91/03/01 14:07:49 bostic 25 24
c ANSI
e
s 00019/00016/00383
d D 7.16 90/12/29 18:14:15 karels 24 23
c don't save as Exaa`XXXXX; exit nonzero if /var/preserve doesn't exist
c (maybe even complain!)
e
s 00003/00003/00396
d D 7.15 89/11/14 17:18:50 bostic 23 22
c editor temporaries are in /var/tmp, now
e
s 00013/00014/00386
d D 7.14 89/05/11 09:51:45 bostic 22 21
c file reorg, pathnames.h, paths.h
e
s 00001/00000/00399
d D 7.13 86/01/22 11:23:32 bloom 21 20
c add file name (LOST) to the mailed message properly
e
s 00002/00002/00397
d D 7.12 85/06/07 18:25:51 bloom 20 19
c fix sccsid and copyright for xstr
e
s 00016/00002/00383
d D 7.11 85/05/31 15:19:18 dist 19 18
c Add copyright
e
s 00001/00000/00384
d D 7.10 84/12/05 09:56:46 ralph 18 17
c do setuid(getuid)) before popen to close security hole.
e
s 00039/00017/00345
d D 7.9 84/02/14 21:35:19 rrh 17 16
c add subject line, better description of what happened 
c and how to recover; fix English
e
s 00001/00001/00361
d D 7.8 83/08/14 22:43:56 mckusick 16 15
c close those security holes! (kre)
e
s 00006/00010/00356
d D 7.7 83/07/03 22:53:48 sam 15 13
c 
e
s 00006/00010/00356
d R 7.7 83/07/02 23:27:29 sam 14 13
c purge local/uparm.h; fix from sun for expreserve
e
s 00009/00010/00357
d D 7.6 83/06/10 10:08:19 ralph 13 12
c updating sccs files due to restoring an older SCCS directory
e
s 00001/00001/00366
d D 7.5 81/08/02 08:55:46 mark 12 11
c fix for portability on systems with big uids.  THIS CHANGES TEMP
c FILE FORMAT SO EXPRESERVE/RECOVER MUST BE UPDATED AT SAME TIME.
e
s 00000/00000/00367
d D 7.4 81/07/26 20:05:27 mark 11 10
c fixes for 3b
e
s 00002/00000/00365
d D 7.3 81/07/11 02:02:41 mark 10 9
c fixed non VMUNIX botch in HBLKS
e
s 00008/00007/00357
d D 7.2 81/07/09 23:08:35 mark 9 8
c fixed stuff broken by mjm
e
s 00007/00007/00357
d D 7.1 81/07/08 22:36:18 mark 8 7
c release 3.7 - a few bug fixes and a few new features.
e
s 00009/00004/00355
d D 6.1 80/10/19 01:23:07 mark 7 6
c preliminary release 3.6 10/18/80
e
s 00000/00000/00359
d D 5.1 80/08/20 16:16:43 mark 6 5
c Release 3.5, August 20, 1980
e
s 00002/00001/00357
d D 4.2 80/08/01 20:44:38 mark 5 4
c Bill added more buffers, and I put in sccs.
e
s 00000/00000/00358
d D 4.1 80/08/01 00:20:24 mark 4 3
c release 3.4, June 24, 1980
e
s 00000/00000/00358
d D 3.1 80/07/31 23:45:41 mark 3 2
c release 3.3, Feb 2, 1980
e
s 00015/00001/00343
d D 2.1 80/07/31 23:22:16 mark 2 1
c release 3.2, Jan 4, 1980
e
s 00344/00000/00000
d D 1.1 80/07/31 23:01:06 mark 1 0
c date and time created 80/07/31 23:01:06 by mark
e
u
U
t
T
I 1
D 5
/* Copyright (c) 1979 Regents of the University of California */
E 5
I 5
D 8
/* Copyright (c) 1980 Regents of the University of California */
static char *sccsid = "%W% %G%";
E 8
I 8
D 19
/* Copyright (c) 1981 Regents of the University of California */
static char *sccsid = "%W%	%G%";
E 19
I 19
D 26
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 26
I 26
/*-
D 27
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
 * %sccs.include.redist.c%
E 26
 */

#ifndef lint
D 20
char copyright[] =
E 20
I 20
D 26
char *copyright =
E 20
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 26
I 26
D 27
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
E 26
 All rights reserved.\n";
E 27
I 27
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 27
D 26
#endif not lint
E 26
I 26
#endif /* not lint */
E 26

#ifndef lint
D 20
static char sccsid[] = "%W% (Berkeley) %G%";
E 20
I 20
D 26
static char *sccsid = "%W% (Berkeley) %G%";
E 20
#endif not lint
E 26
I 26
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 26

E 19
E 8
E 5
D 22
#include <stdio.h>
#include <ctype.h>
E 22
D 13
#include <sys/types.h>
E 13
I 13
#include <sys/param.h>
E 13
#include <sys/stat.h>
D 26
#include <sys/dir.h>
E 26
I 26
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
E 26
#include <pwd.h>
I 26
#include <errno.h>
#include <unistd.h>
E 26
D 15
#include "local/uparm.h"
I 8
				/* mjm: "/tmp" --> TMP */
E 15
I 15
D 22
#include "uparm.h"
E 22
I 22
#include <stdio.h>
#include <ctype.h>
I 26
#include <stdlib.h>
#include <string.h>
E 26
#include "pathnames.h"
E 22

E 15
D 9
#define TMP	"/3b/tmp"
E 9
I 9
D 22
#define TMP	"/tmp"
E 9
E 8

E 22
I 2
D 26
#ifdef VMUNIX
#define	HBLKS	2
I 10
#else
#define HBLKS	1
E 10
D 8
#else
#define	HBLKS	1
E 8
#endif

I 9
char xstr[1];			/* make loader happy */

E 26
E 9
E 2
/*
D 22
 * Expreserve - preserve a file in usrpath(preserve)
E 22
I 22
 * Expreserve - preserve a file in _PATH_PRESERVE.
E 22
 * Bill Joy UCB November 13, 1977
 *
 * This routine is very naive - it doesn't remove anything from
D 9
 * usrpath(preserve)... this may mean that we will be unable to preserve
 * stuff there... the danger in doing anything with usrpath(preserve)
E 9
I 9
D 15
 * usrpath(preserve)... this may mean that we  * stuff there... the danger in doing anything with usrpath(preserve)
E 15
I 15
D 22
 * usrpath(preserve)... this may mean that we leave
 * stuff there... the danger in doing anything with usrpath(preserve)
E 22
I 22
D 26
 * _PATH_PRESERVE... this may mean that we leave
 * stuff there... the danger in doing anything with _PATH_PRESERVE
E 22
E 15
E 9
 * is that the clock may be screwed up and we may get confused.
E 26
I 26
 * _PATH_PRESERVE... this may mean that we leave stuff there...
 * the danger in doing anything with _PATH_PRESERVE is that the
 * clock may be screwed up and we may get confused.
E 26
 *
D 26
 * We are called in two ways - first from the editor with no argumentss
 * and the standard input open on the temp file. Second with an argument
 * to preserve the entire contents of /tmp (root only).
E 26
I 26
 * We are called in two ways - first from the editor with no arguments
 * and the standard input open on the temp file.  Second with an
 * argument to preserve the entire contents of _PATH_VARTMP (root only).
E 26
 *
 * BUG: should do something about preserving Rx... (register contents)
 *      temporaries.
 */

I 2
D 26
#ifndef VMUNIX
E 2
#define	LBLKS	125
I 2
#else
E 26
I 26
#ifdef VMUNIX
#define	HBLKS	2
E 26
#define	LBLKS	900
I 26
#else
#define HBLKS	1
#define	LBLKS	125
E 26
#endif
E 2
#define	FNSIZE	128

struct 	header {
	time_t	Time;			/* Time temp file last updated */
D 12
	short	Uid;			/* This users identity */
E 12
I 12
	int	Uid;			/* This users identity */
E 12
I 2
D 26
#ifndef VMUNIX
E 2
	short	Flines;			/* Number of lines in file */
I 2
#else
E 26
I 26
#ifdef VMUNIX
E 26
	int	Flines;
I 26
#else
	short	Flines;			/* Number of lines in file */
E 26
#endif
E 2
	char	Savedfile[FNSIZE];	/* The current file name */
	short	Blocks[LBLKS];		/* Blocks where line pointers stashed */
} H;

D 26
#ifdef	lint
#define	ignore(a)	Ignore(a)
#define	ignorl(a)	Ignorl(a)
#else
#define	ignore(a)	a
#define	ignorl(a)	a
#endif

D 25
struct	passwd *getpwuid();
E 25
off_t	lseek();
FILE	*popen();

#define eq(a, b) strcmp(a, b) == 0

main(argc)
E 26
I 26
main(argc, argv)
E 26
	int argc;
I 26
	char **argv;
E 26
{
I 26
	extern int optind;
E 26
D 13
	register FILE *tf;
	struct direct dirent;
E 13
I 13
	register DIR *tf;
D 26
	struct direct *dirent;
E 26
I 26
	struct dirent *dirent;
E 26
E 13
	struct stat stbuf;
I 24
D 26
	int err = 0;
E 26
I 26
	int aflag, ch, err;
E 26
	char path[MAXPATHLEN];
E 24

I 24
D 26
	if (chdir(_PATH_PRESERVE) < 0) {
		perror(_PATH_PRESERVE);
		exit(1);
	}
E 26
I 26
	aflag = 0;
	while ((ch = getopt(argc, argv, "a")) != EOF)
		switch(ch) {
		case 'a':
			aflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
E 26

I 26
	if (chdir(_PATH_PRESERVE) < 0)
		error(_PATH_PRESERVE);

E 26
E 24
	/*
	 * If only one argument, then preserve the standard input.
	 */
D 26
	if (argc == 1) {
		if (copyout((char *) 0))
			exit(1);
		exit(0);
	}
E 26
I 26
	if (!aflag)
		exit(copyout(NULL) ? 1 : 0);
E 26

	/*
	 * If not super user, then can only preserve standard input.
	 */
	if (getuid()) {
D 26
		fprintf(stderr, "NOT super user\n");
		exit(1);
E 26
I 26
		errno = EPERM;
		error(NULL);
E 26
	}

	/*
D 24
	 * ... else preserve all the stuff in /tmp, removing
E 24
I 24
	 * ... else preserve all the stuff in /var/tmp, removing
E 24
	 * it as we go.
	 */
I 26
	if (!(tf = opendir(_PATH_VARTMP)))
		error(_PATH_VARTMP);
E 26
D 9
	if (chdir("/tmp") < 0) {
		perror("/tmp");
E 9
D 8
		exit(1);
	}
E 8
I 8
D 22
	if (chdir(TMP) < 0) {
		perror(TMP);
E 22
I 22
D 23
	if (chdir(_PATH_TMP) < 0) {
		perror(_PATH_TMP);
E 23
I 23
D 24
	if (chdir(_PATH_VARTMP) < 0) {
		perror(_PATH_VARTMP);
E 23
E 22
I 9
		exit(1);
	}
E 24
E 9
E 8

D 13
	tf = fopen(".", "r");
E 13
I 13
D 24
	tf = opendir(".");
E 24
I 24
D 26
	tf = opendir(_PATH_VARTMP);
E 24
E 13
	if (tf == NULL) {
D 9
		perror("/tmp");
		exit(1);
E 9
D 8
	}
E 8
I 8
D 22
		perror(TMP);
E 22
I 22
D 23
		perror(_PATH_TMP);
E 23
I 23
		perror(_PATH_VARTMP);
E 23
E 22
I 9
		exit(1);
	}
E 26
I 26
	err = 0;
E 26
E 9
E 8
D 13
	while (fread((char *) &dirent, sizeof dirent, 1, tf) == 1) {
		if (dirent.d_ino == 0)
			continue;
E 13
I 13
	while ((dirent = readdir(tf)) != NULL) {
E 13
D 15
		/*
		 * Ex temporaries must begin with Ex;
		 * we check that the 10th character of the name is null
		 * so we won't have to worry about non-null terminated names
		 * later on.
		 */
D 13
		if (dirent.d_name[0] != 'E' || dirent.d_name[1] != 'x' || dirent.d_name[10])
E 13
I 13
		if (dirent->d_name[0] != 'E' || dirent->d_name[1] != 'x' || dirent->d_name[10])
E 15
I 15
		/* Ex temporaries must begin with Ex. */
		if (dirent->d_name[0] != 'E' || dirent->d_name[1] != 'x')
E 15
E 13
			continue;
D 13
		if (stat(dirent.d_name, &stbuf))
E 13
I 13
D 24
		if (stat(dirent->d_name, &stbuf))
E 24
I 24
D 26
		sprintf(path, "%s/%s", _PATH_VARTMP, dirent->d_name);
		if (stat(path, &stbuf))
E 26
I 26
		(void)sprintf(path, "%s/%s", _PATH_VARTMP, dirent->d_name);
		if (stat(path, &stbuf) || !S_ISREG(stbuf.st_mode))
E 26
E 24
E 13
			continue;
D 26
		if ((stbuf.st_mode & S_IFMT) != S_IFREG)
			continue;
E 26
		/*
		 * Save the bastard.
		 */
D 13
		ignore(copyout(dirent.d_name));
E 13
I 13
D 24
		ignore(copyout(dirent->d_name));
E 24
I 24
		err |= copyout(path);
E 24
E 13
	}
I 13
D 26
	closedir(tf);
E 26
I 26
	(void)closedir(tf);
E 26
E 13
D 24
	exit(0);
E 24
I 24
	exit(err);
E 24
}

D 22
char	pattern[] =	usrpath(preserve/Exaa`XXXXX);
E 22
I 22
D 24
char	pattern[MAXPATHLEN];
E 24
I 24
D 26
char	pattern[] = "Exaa`XXXXX";
E 24
E 22

/*
D 22
 * Copy file name into usrpath(preserve)/...
E 22
I 22
 * Copy file name into pattern[].
E 22
 * If name is (char *) 0, then do the standard input.
 * We make some checks on the input to make sure it is
 * really an editor temporary, generate a name for the
 * file (this is the slowest thing since we must stat
 * to find a unique name), and finally copy the file.
 */
E 26
copyout(name)
	char *name;
{
D 26
	int i;
	static int reenter;
	char buf[BUFSIZ];
E 26
I 26
	struct stat sb;
	register int ifd, ofd, nr, nw, off, rval;
	char buf[8*1024], fname[20];
E 26

I 22
D 24
	(void)sprintf(pattern, "%s/Exaa`XXXXX", _PATH_PRESERVE);
E 24
E 22
D 26
	/*
	 * The first time we put in the digits of our
	 * process number at the end of the pattern.
	 */
	if (reenter == 0) {
		mkdigits(pattern);
		reenter++;
E 26
I 26
	/* Open any given file name. */
	if (name) {
		if ((ifd = open(name, O_RDWR)) < 0)
			return(1);
		(void)fstat(ifd, &sb);
		if (!sb.st_size) {
			(void)unlink(name);
			return(0);
		}
	} else {
		ifd = STDIN_FILENO;
		/* vi hands us an fd, it's not necessarily at the beginning. */
		(void)lseek(ifd, 0l, SEEK_SET);
E 26
	}

D 26
	/*
	 * If a file name was given, make it the standard
	 * input if possible.
	 */
	if (name != 0) {
		ignore(close(0));
		/*
		 * Need read/write access for arcane reasons
		 * (see below).
		 */
		if (open(name, 2) < 0)
D 24
			return (-1);
E 24
I 24
			return (1);
E 24
	}
E 26
I 26
	if (read(ifd, &H, sizeof(H)) != sizeof(H))
		goto format;
E 26

	/*
D 26
	 * Get the header block.
	 */
	ignorl(lseek(0, 0l, 0));
	if (read(0, (char *) &H, sizeof H) != sizeof H) {
format:
		if (name == 0)
D 7
			fprintf(stderr, "Buffer format error\n");
E 7
I 7
			fprintf(stderr, "Buffer format error\t");
E 7
D 24
		return (-1);
E 24
I 24
		return (1);
E 24
	}

	/*
E 26
D 24
	 * Consistency checsks so we don't copy out garbage.
E 24
I 24
	 * Consistency checks so we don't copy out garbage.
E 24
	 */
	if (H.Flines < 0) {
D 26
#ifdef DEBUG
		fprintf(stderr, "Negative number of lines\n");
#endif
E 26
I 26
		(void)fprintf(stderr,
		    "ex3.7preserve: negative number of lines\n");
E 26
		goto format;
	}
I 26

E 26
D 2
	if (H.Blocks[0] != 1 || H.Blocks[1] != 2) {
E 2
I 2
	if (H.Blocks[0] != HBLKS || H.Blocks[1] != HBLKS+1) {
E 2
D 26
#ifdef DEBUG
		fprintf(stderr, "Blocks %d %d\n", H.Blocks[0], H.Blocks[1]);
#endif
E 26
I 26
		(void)fprintf(stderr,
		    "ex3.7preserve: blocks %d %d\n", H.Blocks[0], H.Blocks[1]);
E 26
		goto format;
	}
D 26
	if (name == 0 && H.Uid != getuid()) {
#ifdef DEBUG
		fprintf(stderr, "Wrong user-id\n");
#endif
E 26
I 26

	if (!name && H.Uid != getuid()) {
		(void)fprintf(stderr, "ex3.7preserve: wrong user-id\n");
E 26
		goto format;
	}
D 26
	if (lseek(0, 0l, 0)) {
#ifdef DEBUG
		fprintf(stderr, "Negative number of lines\n");
#endif
		goto format;
E 26
I 26

	if (lseek(ifd, 0l, SEEK_SET)) {
		(void)fprintf(stderr,
		    "ex3.7preserve: negative number of lines\n");
format:		(void)fprintf(stderr, "ex3.7preserve: %s\n", strerror(EFTYPE));
		return (1);
E 26
	}

	/*
	 * If no name was assigned to the file, then give it the name
D 26
	 * LOST, by putting this in the header.
E 26
I 26
	 * LOST, by putting this in the header.  This involves overwriting
	 * the "input" file.
E 26
	 */
	if (H.Savedfile[0] == 0) {
D 26
		strcpy(H.Savedfile, "LOST");
		ignore(write(0, (char *) &H, sizeof H));
E 26
I 26
		(void)strcpy(H.Savedfile, "LOST");
		(void)write(ifd, &H, sizeof(H));
E 26
		H.Savedfile[0] = 0;
D 26
		lseek(0, 0l, 0);
E 26
I 26
		(void)lseek(ifd, 0l, SEEK_SET);
E 26
	}

D 26
	/*
	 * File is good.  Get a name and create a file for the copy.
	 */
	mknext(pattern);
	ignore(close(1));
	if (creat(pattern, 0600) < 0) {
		if (name == 0)
			perror(pattern);
		return (1);
	}
E 26
I 26
	/* File is good.  Get a name and create a file for the copy. */
	(void)strcpy(fname, "ExXXXXXX");
	if ((ofd = mkstemp(fname)) == -1)
		return(1);
E 26

D 26
	/*
	 * Make the target be owned by the owner of the file.
	 */
	ignore(chown(pattern, H.Uid, 0));

	/*
	 * Copy the file.
	 */
	for (;;) {
		i = read(0, buf, BUFSIZ);
		if (i < 0) {
			if (name)
				perror("Buffer read error");
			ignore(unlink(pattern));
D 24
			return (-1);
E 24
I 24
			return (1);
E 24
		}
		if (i == 0) {
			if (name)
				ignore(unlink(name));
D 17
			notify(H.Uid, H.Savedfile, (int) name);
E 17
I 17
			notify(H.Uid, H.Savedfile, (int) name, H.Time);
E 17
			return (0);
		}
		if (write(1, buf, i) != i) {
			if (name == 0)
				perror(pattern);
			unlink(pattern);
D 24
			return (-1);
E 24
I 24
			return (1);
E 24
		}
E 26
I 26
	/* Copy the file. */
	rval = 0;
	while ((nr = read(ifd, buf, sizeof(buf))) > 0)
		for (off = 0; off < nr; nr -= nw, off += nw)
			if ((nw = write(ofd, buf + off, nr)) < 0) {
				(void)fprintf(stderr,
				    "ex3.7preserve: tmp file: %s\n",
				    strerror(errno));
				rval = 1;
				break;
			}
	if (nr < 0) {
		(void)fprintf(stderr, "ex3.7preserve: %s: %s\n",
		    name ? name : "stdin", strerror(errno));
		rval = 1;
E 26
	}
I 26
	    
	if (rval)
		(void)unlink(fname);
	else {
		(void)fchown(ofd, H.Uid, 0);
		notify(H.Uid, H.Savedfile, (int)name, H.Time);
		if (name)
			(void)unlink(name);
	}
	(void)close(ifd);
	(void)close(ofd);
	return(rval);
E 26
}

D 26
/*
 * Blast the last 5 characters of cp to be the process number.
 */
mkdigits(cp)
	char *cp;
{
	register int i, j;

	for (i = getpid(), j = 5, cp += strlen(cp); j > 0; i /= 10, j--)
		*--cp = i % 10 | '0';
}

/*
 * Make the name in cp be unique by clobbering up to
 * three alphabetic characters into a sequence of the form 'aab', 'aac', etc.
 * Mktemp gets weird names too quickly to be useful here.
 */
mknext(cp)
	char *cp;
{
	char *dcp;
	struct stat stb;

	dcp = cp + strlen(cp) - 1;
	while (isdigit(*dcp))
		dcp--;
whoops:
	if (dcp[0] == 'z') {
		dcp[0] = 'a';
		if (dcp[-1] == 'z') {
			dcp[-1] = 'a';
			if (dcp[-2] == 'z')
D 7
				fprintf(stderr, "Can't find a name\n");
E 7
I 7
				fprintf(stderr, "Can't find a name\t");
E 7
			dcp[-2]++;
		} else
			dcp[-1]++;
	} else
		dcp[0]++;
	if (stat(cp, &stb) == 0)
		goto whoops;
}

/*
 * Notify user uid that his file fname has been saved.
 */
E 26
I 26
/* Notify user uid that his file fname has been saved. */
E 26
D 17
notify(uid, fname, flag)
E 17
I 17
notify(uid, fname, flag, time)
E 17
	int uid;
	char *fname;
I 17
	time_t	time;
E 17
{
D 26
	struct passwd *pp = getpwuid(uid);
E 26
I 26
	struct passwd *pp;
E 26
	register FILE *mf;
D 17
	char cmd[BUFSIZ];
E 17
I 17
D 26
	char	cmd[BUFSIZ];
	char	hostname[128];
	char	croak[128];
	char	*timestamp, *ctime();
E 26
I 26
	static int reenter;
	static char hostname[MAXHOSTNAMELEN], *timestamp;
	char cmd[MAXPATHLEN + 50], croak[50];
E 26
E 17

I 26
	pp = getpwuid(uid);
E 26
	if (pp == NULL)
		return;
I 17
D 26
	gethostname(hostname, sizeof(hostname));
	timestamp = ctime(&time);
	timestamp[16] = 0;	/* blast from seconds on */
E 17
D 16
	sprintf(cmd, "mail %s", pp->pw_name);
E 16
I 16
D 22
	sprintf(cmd, "/bin/mail %s", pp->pw_name);
E 22
I 22
	sprintf(cmd, "%s %s", _PATH_BINMAIL, pp->pw_name);
E 22
I 18
	setuid(getuid());
E 26
I 26

	if (!reenter) {
		reenter = 1;
		(void)gethostname(hostname, sizeof(hostname));
		timestamp = ctime(&time);
		timestamp[16] = 0;	/* blast from seconds on */
	}

	(void)snprintf(cmd, sizeof(cmd), 
	    "%s -i -t -F \"The Editor\" -f root", _PATH_SENDMAIL);
E 26
E 18
E 16
	mf = popen(cmd, "w");
	if (mf == NULL)
		return;
D 26
	setbuf(mf, cmd);
E 26
I 26
	(void)fprintf(mf,
	    "Reply-To: root@%s\nFrom: root@%s (The Editor)\nTo: %s\n",
	    hostname, hostname, pp->pw_name);

E 26
I 17
	/*
D 26
	 *	flag says how the editor croaked:
	 * "the editor was killed" is perhaps still not an ideal
	 * error message.  Usually, either it was forcably terminated
	 * or the phone was hung up, but we don't know which.
E 26
I 26
	 * flag says how the editor croaked: "the editor was killed" is
	 * perhaps still not an ideal error message.  Usually, either it
	 * was forcably terminated or the phone was hung up, but we don't
	 * know which.
E 26
	 */
D 26
	sprintf(croak, flag
		? "the system went down"
		: "the editor was killed");
E 17
	if (fname[0] == 0) {
E 26
I 26
	(void)snprintf(croak, sizeof(croak), 
	    flag ? "the system went down"
		 : "the editor was killed");
	if (!fname  || !fname[0]) {
E 26
I 21
		fname = "LOST";
I 26
		fprintf(mf, "Subject: editor saved \"LOST\"\n\n");
		fprintf(mf, "You were editing a file without a name\n");
		fprintf(mf, "at %s on the machine %s when %s.\n",
		    timestamp, hostname, croak);
E 26
E 21
		fprintf(mf,
D 17
"A copy of an editor buffer of yours was saved when %s.\n",
D 7
		flag ? "the system went down" : "your phone was hung up");
E 7
I 7
		flag ? "the system went down" : "the editor was killed");
E 17
I 17
D 26
"Subject: editor saved ``LOST''\n");
E 17
E 7
		fprintf(mf,
D 17
"No name was associated with this buffer so it has been named \"LOST\".\n");
	} else
E 17
I 17
"You were editing a file without a name\n");
E 17
		fprintf(mf,
D 17
"A copy of an editor buffer of your file \"%s\"\nwas saved when %s.\n", fname,
D 7
		flag ? "the system went down" : "your phone was hung up");
E 7
I 7
		/*
		 * "the editor was killed" is perhaps still not an ideal
		 * error message.  Usually, either it was forcably terminated
		 * or the phone was hung up, but we don't know which.
		 */
		flag ? "the system went down" : "the editor was killed");
E 17
I 17
"at <%s> on the machine ``%s'' when %s.\n", timestamp, hostname, croak);
		fprintf(mf,
"Since the file had no name, it has been named \"LOST\".\n");
E 26
I 26
		   "Since the file had no name, it has been named \"LOST\".\n");
E 26
	} else {
D 26
		fprintf(mf,
"Subject: editor saved ``%s''\n", fname);
		fprintf(mf,
"You were editing the file \"%s\"\n", fname);
		fprintf(mf,
"at <%s> on the machine ``%s''\n", timestamp, hostname);
		fprintf(mf,
"when %s.\n", croak);
E 26
I 26
		fprintf(mf, "Subject: editor saved \"%s\"\n\n", fname);
		fprintf(mf, "You were editing the file %s\n", fname);
		fprintf(mf, "at %s on the machine %s\n", timestamp, hostname);
		fprintf(mf, "when %s.\n", croak);
E 26
	}
I 26
	fprintf(mf, "\nYou can retrieve most of your changes to this file\n");
	fprintf(mf, "using the \"recover\" command of the editor.\n");
E 26
E 17
E 7
	fprintf(mf,
D 17
"This buffer can be retrieved using the \"recover\" command of the editor.\n");
E 17
I 17
D 26
"\nYou can retrieve most of your changes to this file\n");
E 17
	fprintf(mf,
D 17
"An easy way to do this is to give the command \"ex -r %s\".\n",fname);
E 17
I 17
"using the \"recover\" command of the editor.\n");
E 17
	fprintf(mf,
D 17
"This works for \"edit\" and \"vi\" also.\n");
E 17
I 17
"An easy way to do this is to give the command \"vi -r %s\".\n", fname);
	fprintf(mf,
"This method also works using \"ex\" and \"edit\".\n");
E 26
I 26
	    "An easy way to do this is to give the command \"vi -r %s\".\n",
	    fname);
	fprintf(mf, "This method also works using \"ex\" and \"edit\".\n\n");
E 26
E 17
	pclose(mf);
}

/*
 *	people making love
 *	never exactly the same
 *	just like a snowflake 
 */
D 26

#ifdef lint
Ignore(a)
	int a;
E 26
I 26
error(msg)
	char *msg;
E 26
{
D 26

	a = a;
E 26
I 26
	(void)fprintf(stderr, "ex3.7preserve: ");
	if (msg)
		(void)fprintf(stderr, "%s: ", msg);
	(void)fprintf(stderr, "%s\n", strerror(errno));
	exit(1);
E 26
}

D 26
Ignorl(a)
	long a;
E 26
I 26
usage()
E 26
{
D 26

	a = a;
E 26
I 26
	(void)fprintf(stderr, "usage: ex3.7preserve [-a]\n");
	exit(1);
E 26
}
D 26
#endif
E 26
E 1
