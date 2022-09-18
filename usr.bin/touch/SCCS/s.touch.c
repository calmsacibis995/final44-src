h61738
s 00001/00001/00315
d D 8.2 95/04/28 12:52:18 bostic 17 16
c Centuries, not millennia; From: Chris Torek <torek@BSDI.COM>
e
s 00005/00005/00311
d D 8.1 93/06/06 16:36:57 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00315
d D 5.6 93/06/02 11:31:13 bostic 15 14
c move past the obsolete time argument
e
s 00001/00001/00315
d D 5.5 93/03/07 16:24:12 bostic 14 13
c don't truncte the file when we create it, there's a race
e
s 00005/00005/00311
d D 5.4 93/03/07 15:24:31 bostic 13 12
c make default parsing correct, i.e. "-am" didn't work
e
s 00009/00000/00307
d D 5.3 93/03/06 13:41:07 bostic 12 11
c try utimes(f, NULL) before trying to read/write the file
e
s 00244/00107/00063
d D 5.2 93/03/06 13:34:38 bostic 11 10
c implement from scratch, using utimes(2), for POSIX 1003.2
e
s 00078/00043/00092
d D 5.1 92/10/02 09:27:39 bostic 10 9
c off_t's aren't longs anymore, from Craig Leres
c other miscellaneous cleanups/stylistic changes
e
s 00001/00011/00134
d D 4.8 90/06/01 17:47:12 bostic 9 8
c new copyright notice
e
s 00050/00027/00095
d D 4.7 88/08/09 18:34:11 bostic 8 7
c minor KNF changes, add Berkeley specific copyright
e
s 00051/00052/00071
d D 4.6 87/09/14 17:07:19 bostic 7 6
c usage if no args, exit correct value; bug report 4.3BSD/usr.bin/69
e
s 00019/00022/00104
d D 4.5 87/06/29 09:28:30 bostic 6 4
c long/int problems, getopt(3) added
e
s 00017/00020/00106
d R 4.5 87/05/02 16:11:23 bostic 5 4
c fix long/int problems, use getopt for arg parseing
e
s 00002/00001/00124
d D 4.4 87/04/06 12:28:29 bostic 4 3
c access had hard-coded values
e
s 00003/00003/00122
d D 4.3 83/08/11 20:27:58 sam 3 2
c standardize sccs keyword lines
e
s 00108/00054/00017
d D 4.2 82/06/09 16:57:17 mckusick 2 1
c merge system forced touch with user touch (peter)
e
s 00071/00000/00000
d D 4.1 80/10/01 17:28:59 bill 1 0
c date and time created 80/10/01 17:28:59 by bill
e
u
U
t
T
I 8
/*
D 11
 * Copyright (c) 1988 Regents of the University of California.
E 11
I 11
D 16
 * Copyright (c) 1993 Regents of the University of California.
E 11
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
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

E 8
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
D 3
#ifndef LINT
static	char *sccsid = "%W% (Berkeley) %E%";
#endif not LINT
E 3
I 3
#ifndef lint
D 8
static	char sccsid[] = "%W% (Berkeley) %G%";
#endif
E 8
I 8
D 16
char copyright[] =
D 11
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
E 11
I 11
"%Z% Copyright (c) 1993 Regents of the University of California.\n\
E 11
 All rights reserved.\n";
E 16
I 16
static char copyright[] =
"%Z% Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 16
#endif /* not lint */
E 8
E 3

I 8
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 8
D 11
/*
D 8
 *	attempt to set the modify date of a file to the current date.
 *	if the file exists, read and write its first character.
 *	if the file doesn't exist, create it, unless -c option prevents it.
 *	if the file is read-only, -f forces chmod'ing and touch'ing.
E 8
I 8
 * Attempt to set the modify date of a file to the current date.  If the
 * file exists, read and write its first character.  If the file doesn't
 * exist, create it, unless -c option prevents it.  If the file is read-only,
 * -f forces chmod'ing and touch'ing.
E 8
 */
E 11
D 8

E 2
#include <stdio.h>
E 8
I 2
#include <sys/types.h>
I 4
D 10
#include <sys/file.h>
E 10
E 4
#include <sys/stat.h>
I 11
#include <sys/time.h>
E 11
I 10

I 11
#include <err.h>
E 11
#include <errno.h>
#include <fcntl.h>
E 10
I 8
#include <stdio.h>
I 10
#include <stdlib.h>
#include <string.h>
I 11
#include <time.h>
E 11
#include <unistd.h>
E 10
E 8
E 2

I 2
D 8
int	dontcreate;	/* set if -c option */
int	force;		/* set if -f option */
E 8
I 8
D 11
static int	dontcreate;	/* set if -c option */
static int	force;		/* set if -f option */
E 11
I 11
int	rw __P((char *, struct stat *, int));
void	stime_arg1 __P((char *, struct timeval *));
void	stime_arg2 __P((char *, int, struct timeval *));
void	stime_file __P((char *, struct timeval *));
void	usage __P((void));
E 11
E 8
E 2

I 10
D 11
void	err __P((const char *, ...));
int	readwrite __P((char *, off_t));
int	touch __P((char *));
__dead	void usage __P((void));

E 11
int
E 10
I 2
D 7
char *whoami = "touch";

E 2
main(argc,argv)
E 7
I 7
main(argc, argv)
E 7
D 2
int argc;
char *argv[];
E 2
I 2
D 8
	int	argc;
	char	**argv;
E 8
I 8
	int argc;
D 10
	char **argv;
E 10
I 10
	char *argv[];
E 10
E 8
E 2
{
D 2
int i;
static int force = 1;
E 2
I 2
D 6
	char	*argp;
E 6
I 6
D 10
	extern int optind;
E 10
D 7
	int ch;
E 7
I 7
D 11
	int ch, retval;
E 11
I 11
	struct stat sb;
	struct timeval tv[2];
	int aflag, cflag, fflag, mflag, ch, fd, len, rval, timeset;
	char *p;
E 11
E 7
E 6
E 2

D 2
for(i = 1 ; i < argc ; ++i)
	if( strcmp(argv[i], "-c") )
		touch(force, argv[i]);
	else
		force = 0;
E 2
I 2
D 6
	dontcreate = 0;
	force = 0;
	for (argv++; **argv == '-'; argv++) {
		for (argp = &(*argv)[1]; *argp; argp++) {
			switch (*argp) {
			case 'c':
				dontcreate = 1;
				break;
			case 'f':
				force = 1;
				break;
			default:
				fprintf(stderr, "%s: bad option -%c\n",
					whoami, *argp);
				exit(1);
			}
E 6
I 6
D 7
	dontcreate = force = 0;
E 7
I 7
D 11
	dontcreate = force = retval = 0;
E 7
	while ((ch = getopt(argc, argv, "cf")) != EOF)
		switch((char)ch) {
E 11
I 11
D 13
	aflag = mflag = 1;
	cflag = fflag = timeset = 0;

E 13
I 13
	aflag = cflag = fflag = mflag = timeset = 0;
E 13
	if (gettimeofday(&tv[0], NULL))
		err(1, "gettimeofday");

	while ((ch = getopt(argc, argv, "acfmr:t:")) != EOF)
		switch(ch) {
		case 'a':
			aflag = 1;
D 13
			mflag = 0;
E 13
			break;
E 11
		case 'c':
D 11
			dontcreate = 1;
E 11
I 11
			cflag = 1;
E 11
			break;
		case 'f':
D 11
			force = 1;
E 11
I 11
			fflag = 1;
E 11
			break;
I 11
		case 'm':
D 13
			aflag = 0;
E 13
			mflag = 1;
			break;
		case 'r':
			timeset = 1;
			stime_file(optarg, tv);
			break;
		case 't':
			timeset = 1;
			stime_arg1(optarg, tv);
			break;
E 11
		case '?':
		default:
D 7
			fprintf(stderr, "usage: %s [-cf] file ...\n", whoami);
			exit(1);
E 7
I 7
			usage();
E 7
E 6
		}
D 6
	}
	for (/*void*/; *argv; argv++) {
E 6
I 6
D 7
	for (argv += optind; *argv; ++argv)
E 6
		touch(*argv);
E 7
I 7
D 11
	if (!*(argv += optind))
E 11
I 11
	argc -= optind;
	argv += optind;
I 13

	/* Default is both -a and -m. */
	if (aflag == 0 && mflag == 0)
		aflag = mflag = 1;
E 13

	/*
	 * If no -r or -t flag, at least two operands, the first of which
	 * is an 8 or 10 digit number, use the obsolete time specification.
	 */
	if (!timeset && argc > 1) {
		(void)strtol(argv[0], &p, 10);
		len = p - argv[0];
		if (*p == '\0' && (len == 8 || len == 10)) {
			timeset = 1;
D 15
			stime_arg2(argv[0], len == 10, tv);
E 15
I 15
			stime_arg2(*argv++, len == 10, tv);
E 15
		}
	}

	/* Otherwise use the current time of day. */
	if (!timeset)
		tv[1] = tv[0];

	if (*argv == NULL)
E 11
		usage();
D 11
	do {
		retval |= touch(*argv);
	} while (*++argv);
	exit(retval);
E 7
D 6
	}
E 6
E 2
}
E 11

I 10
D 11
int
E 10
D 2



#include <sys/types.h>
#include <sys/stat.h>


touch(force, name)
int force;
char *name;
E 2
I 2
touch(filename)
D 8
	char	*filename;
E 8
I 8
	char *filename;
E 8
E 2
{
D 2
struct stat stbuff;
char junk[1];
int fd;
E 2
I 2
D 8
	struct stat	statbuffer;
E 8
I 8
D 10
	struct stat statbuffer;
E 10
I 10
	struct stat sb;
E 11
I 11
	for (rval = 0; *argv; ++argv) {
		/* See if the file exists. */
		if (stat(*argv, &sb))
			if (!cflag) {
				/* Create the file. */
				fd = open(*argv,
D 14
				    O_WRONLY | O_CREAT | O_TRUNC, DEFFILEMODE);
E 14
I 14
				    O_WRONLY | O_CREAT, DEFFILEMODE);
E 14
				if (fd == -1 || fstat(fd, &sb) || close(fd)) {
					rval = 1;
					warn("%s", *argv);
					continue;
				}
E 11
E 10
E 8
E 2

D 2
if( stat(name,&stbuff) < 0)
	if(force)
		goto create;
	else
		{
		fprintf(stderr, "touch: file %s does not exist.\n", name);
E 2
I 2
D 7
	if (stat(filename,&statbuffer) == -1) {
		if (!dontcreate) {
D 6
			readwrite(filename,0);
E 6
I 6
			readwrite(filename,0L);
E 6
		} else {
			fprintf(stderr, "%s: %s: does not exist\n",
				whoami, filename);
		}
E 2
		return;
E 7
I 7
D 10
	if (stat(filename, &statbuffer) == -1) {
E 10
I 10
D 11
	if (stat(filename, &sb) == -1) {
E 10
		if (!dontcreate)
D 10
			return(readwrite(filename, 0L));
		fprintf(stderr, "touch: %s: does not exist\n", filename);
		return(1);
E 10
I 10
			return (readwrite(filename, (off_t)0));
		err("%s: %s", filename, strerror(ENOENT));
		return (1);
E 11
I 11
				/* If using the current time, we're done. */
				if (!timeset)
					continue;
			} else
				continue;

		if (!aflag)
			TIMESPEC_TO_TIMEVAL(&tv[0], &sb.st_atimespec);
		if (!mflag)
			TIMESPEC_TO_TIMEVAL(&tv[1], &sb.st_mtimespec);

		/* Try utimes(2). */
		if (!utimes(*argv, tv))
			continue;

		/* If the user specified a time, nothing else we can do. */
		if (timeset) {
			rval = 1;
			warn("%s", *argv);
		}

I 12
		/*
		 * System V and POSIX 1003.1 require that a NULL argument
		 * set the access/modification times to the current time.
		 * The permission checks are different, too, in that the
		 * ability to write the file is sufficient.  Take a shot.
		 */
		 if (!utimes(*argv, NULL))
			continue;

E 12
		/* Try reading/writing. */
		if (rw(*argv, &sb, fflag))
			rval = 1;
E 11
E 10
E 7
I 2
	}
D 10
	if ((statbuffer.st_mode & S_IFMT) != S_IFREG) {
D 7
		fprintf(stderr, "%s: %s: can only touch regular files\n",
			whoami, filename);
		return;
E 7
I 7
		fprintf(stderr, "touch: %s: can only touch regular files\n",
D 8
			filename);
E 8
I 8
		    filename);
E 8
		return(1);
E 10
I 10
D 11
	if ((sb.st_mode & S_IFMT) != S_IFREG) {
		err("%s: %s", filename, strerror(EFTYPE));
		return (1);
E 10
E 7
	}
D 4
	if (!access(filename,4|2)) {
E 4
I 4
D 7
	if (!access(filename,R_OK | W_OK)) {
E 4
		readwrite(filename,statbuffer.st_size);
		return;
	}
E 7
I 7
	if (!access(filename, R_OK | W_OK))
D 10
		return(readwrite(filename,statbuffer.st_size));
E 10
I 10
		return (readwrite(filename, sb.st_size));
E 10
E 7
	if (force) {
I 7
D 8
		int	retval;
E 8
I 8
		int retval;
E 11
I 11
	exit(rval);
}
E 11
E 8

E 7
D 8
		if (chmod(filename,0666)) {
D 7
			fprintf(stderr, "%s: %s: couldn't chmod: ",
				whoami, filename);
			perror("");
			return;
E 7
I 7
			fprintf(stderr, "touch: %s: couldn't chmod: ", filename);
E 8
I 8
D 10
		if (chmod(filename, 0666)) {
			fprintf(stderr, "touch: %s: couldn't chmod: ",
			    filename);
E 8
			perror((char *)NULL);
			return(1);
E 10
I 10
D 11
		if (chmod(filename, DEFFILEMODE)) {
			err("%s: add permissions: %s",
			    filename, strerror(errno));
			return (1);
E 11
I 11
#define	ATOI2(ar)	((ar)[0] - '0') * 10 + ((ar)[1] - '0'); (ar) += 2;

void
stime_arg1(arg, tvp)
	char *arg;
	struct timeval *tvp;
{
	struct tm *t;
	int yearset;
	char *p;
					/* Start with the current time. */
	if ((t = localtime(&tvp[0].tv_sec)) == NULL)
		err(1, "localtime");
					/* [[CC]YY]MMDDhhmm[.SS] */
	if ((p = strchr(arg, '.')) == NULL)
		t->tm_sec = 0;		/* Seconds defaults to 0. */
	else {
		if (strlen(p + 1) != 2)
			goto terr;
		*p++ = '\0';
		t->tm_sec = ATOI2(p);
	}
		
	yearset = 0;
	switch(strlen(arg)) {
	case 12:			/* CCYYMMDDhhmm */
		t->tm_year = ATOI2(arg);
D 17
		t->tm_year *= 1000;
E 17
I 17
		t->tm_year *= 100;
E 17
		yearset = 1;
		/* FALLTHOUGH */
	case 10:			/* YYMMDDhhmm */
		if (yearset) {
			yearset = ATOI2(arg);
			t->tm_year += yearset;
		} else {
			yearset = ATOI2(arg);
			if (yearset < 69)
				t->tm_year = yearset + 2000;
			else
				t->tm_year = yearset + 1900;
E 11
E 10
E 7
E 2
		}
I 2
D 7
		readwrite(filename,statbuffer.st_size);
E 7
I 7
D 8
		retval = readwrite(filename,statbuffer.st_size);
E 7
		if (chmod(filename,statbuffer.st_mode)) {
E 8
I 8
D 10
		retval = readwrite(filename, statbuffer.st_size);
		if (chmod(filename, statbuffer.st_mode)) {
E 8
D 7
			fprintf(stderr, "%s: %s: couldn't chmod back: ",
				whoami, filename);
			perror("");
			return;
E 7
I 7
			fprintf(stderr, "touch: %s: couldn't chmod back: ",
D 8
				filename);
E 8
I 8
			    filename);
E 8
			perror((char *)NULL);
			return(1);
E 10
I 10
D 11
		retval = readwrite(filename, sb.st_size);
		if (chmod(filename, sb.st_mode)) {
			err("%s: restore permissions: %s",
			    filename, strerror(errno));
			return (1);
E 10
E 7
		}
D 7
	} else {
		fprintf(stderr, "%s: %s: cannot touch\n", whoami, filename);
E 7
I 7
D 10
		return(retval);
E 10
I 10
		return (retval);
E 11
I 11
		t->tm_year -= 1900;	/* Convert to UNIX time. */
		/* FALLTHROUGH */
	case 8:				/* MMDDhhmm */
		t->tm_mon = ATOI2(arg);
		--t->tm_mon;		/* Convert from 01-12 to 00-11 */
		t->tm_mday = ATOI2(arg);
		t->tm_hour = ATOI2(arg);
		t->tm_min = ATOI2(arg);
		break;
	default:
		goto terr;
E 11
E 10
E 7
	}
I 7
D 10
	fprintf(stderr, "touch: %s: cannot touch\n", filename);
	return(1);
E 10
I 10
D 11
	err("%s: cannot touch\n", filename);
	return (1);
E 11
I 11

	t->tm_isdst = -1;		/* Figure out DST. */
	tvp[0].tv_sec = tvp[1].tv_sec = mktime(t);
	if (tvp[0].tv_sec == -1)
terr:		errx(1,
	"out of range or illegal time specification: [[CC]YY]MMDDhhmm[.SS]");

	tvp[0].tv_usec = tvp[1].tv_usec = 0;
E 11
E 10
E 7
}
E 2

I 11
void
stime_arg2(arg, year, tvp)
	char *arg;
	int year;
	struct timeval *tvp;
{
	struct tm *t;
					/* Start with the current time. */
	if ((t = localtime(&tvp[0].tv_sec)) == NULL)
		err(1, "localtime");

	t->tm_mon = ATOI2(arg);		/* MMDDhhmm[yy] */
	--t->tm_mon;			/* Convert from 01-12 to 00-11 */
	t->tm_mday = ATOI2(arg);
	t->tm_hour = ATOI2(arg);
	t->tm_min = ATOI2(arg);
	if (year)
		t->tm_year = ATOI2(arg);

	t->tm_isdst = -1;		/* Figure out DST. */
	tvp[0].tv_sec = tvp[1].tv_sec = mktime(t);
	if (tvp[0].tv_sec == -1)
		errx(1,
	"out of range or illegal time specification: MMDDhhmm[yy]");

	tvp[0].tv_usec = tvp[1].tv_usec = 0;
}

void
stime_file(fname, tvp)
	char *fname;
	struct timeval *tvp;
{
	struct stat sb;

	if (stat(fname, &sb))
		err(1, "%s", fname);
	TIMESPEC_TO_TIMEVAL(tvp, &sb.st_atimespec);
	TIMESPEC_TO_TIMEVAL(tvp + 1, &sb.st_mtimespec);
}

E 11
I 10
int
E 10
D 2
if(stbuff.st_size == 0)
	goto create;
E 2
I 2
D 7
readwrite(filename,size)
E 7
I 7
D 11
readwrite(filename, size)
E 7
D 8
	char	*filename;
D 6
	int	size;
E 6
I 6
	off_t	size;
E 8
I 8
	char *filename;
	off_t size;
E 11
I 11
rw(fname, sbp, force)
	char *fname;
	struct stat *sbp;
	int force;
E 11
E 8
E 6
{
D 8
	int	filedescriptor;
	char	first;
I 6
	off_t	lseek();
E 8
I 8
D 10
	int filedescriptor;
E 10
I 10
D 11
	int fd;
E 10
	char first;
E 11
I 11
	int fd, needed_chmod, rval;
	u_char byte;
E 11
D 10
	off_t lseek();
E 10
E 8
E 6
E 2

D 2
if( (fd = open(name, 2)) < 0)
	goto bad;

if( read(fd, junk, 1) < 1)
	{
	close(fd);
	goto bad;
E 2
I 2
D 11
	if (size) {
D 7
		filedescriptor = open(filename,2);
E 7
I 7
D 10
		filedescriptor = open(filename, O_RDWR, 0);
E 7
		if (filedescriptor == -1) {
D 7
error:
			fprintf(stderr, "%s: %s: ", whoami, filename);
			perror("");
			return;
E 7
I 7
error:			fprintf(stderr, "touch: %s: ", filename);
			perror((char *)NULL);
			return(1);
E 7
		}
D 7
		if (read(filedescriptor, &first, 1) != 1) {
E 7
I 7
		if (read(filedescriptor, &first, 1) != 1)
E 10
I 10
		fd = open(filename, O_RDWR, 0);
		if (fd == -1)
E 10
E 7
			goto error;
D 7
		}
		if (lseek(filedescriptor,0l,0) == -1) {
E 7
I 7
D 10
		if (lseek(filedescriptor, 0L, 0) == -1)
E 10
I 10
		if (read(fd, &first, 1) != 1)
E 10
E 7
			goto error;
E 11
I 11
	/* Try regular files and directories. */
	if (!S_ISREG(sbp->st_mode) && !S_ISDIR(sbp->st_mode)) {
		warnx("%s: %s", fname, strerror(EFTYPE));
		return (1);
	}

	needed_chmod = rval = 0;
	if ((fd = open(fname, O_RDWR, 0)) == -1) {
		if (!force || chmod(fname, DEFFILEMODE))
			goto err;
		if ((fd = open(fname, O_RDWR, 0)) == -1)
			goto err;
		needed_chmod = 1;
	}

	if (sbp->st_size != 0) {
		if (read(fd, &byte, sizeof(byte)) != sizeof(byte))
			goto err;
E 11
D 7
		}
		if (write(filedescriptor, &first, 1) != 1) {
E 7
I 7
D 10
		if (write(filedescriptor, &first, 1) != 1)
E 10
I 10
		if (lseek(fd, (off_t)0, SEEK_SET) == -1)
E 10
E 7
D 11
			goto error;
I 10
		if (write(fd, &first, 1) != 1)
			goto error;
E 11
I 11
			goto err;
		if (write(fd, &byte, sizeof(byte)) != sizeof(byte))
			goto err;
E 11
E 10
D 7
		}
E 7
	} else {
D 7
		filedescriptor = creat(filename,0666);
		if (filedescriptor == -1) {
E 7
I 7
D 10
		filedescriptor = creat(filename, 0666);
		if (filedescriptor == -1)
E 10
I 10
D 11
		fd = creat(filename, DEFFILEMODE);
		if (fd == -1)
E 10
E 7
			goto error;
E 11
I 11
		if (write(fd, &byte, sizeof(byte)) != sizeof(byte)) {
err:			rval = 1;
			warn("%s", fname);
		} else if (ftruncate(fd, (off_t)0)) {
			rval = 1;
			warn("%s: file modified", fname);
		}
E 11
D 7
		}
E 7
E 2
	}
D 2
lseek(fd, 0L, 0);
if( write(fd, junk, 1) < 1 )
	{
	close(fd);
	goto bad;
E 2
I 2
D 7
	if (close(filedescriptor) == -1) {
E 7
I 7
D 10
	if (close(filedescriptor) == -1)
E 7
		goto error;
E 2
D 7
	}
E 7
I 7
	return(0);
E 10
I 10
D 11
	if (close(fd) == -1) {
error:		err("%s: %s", filename, strerror(errno));
		return (1);
E 11
I 11

	if (close(fd) && rval != 1) {
		rval = 1;
		warn("%s", fname);
E 11
	}
D 11
	return (0);
E 11
I 11
	if (needed_chmod && chmod(fname, sbp->st_mode) && rval != 1) {
		rval = 1;
		warn("%s: permissions modified", fname);
	}
	return (rval);
E 11
E 10
}

I 10
__dead void
E 10
usage()
{
D 8
	fputs("usage: touch [-cf] file ...\n", stderr);
E 8
I 8
D 11
	fprintf(stderr, "usage: touch [-cf] file ...\n");
E 11
I 11
	(void)fprintf(stderr,
	    "usage: touch [-acfm] [-r file] [-t time] file ...\n");
E 11
E 8
	exit(1);
I 10
D 11
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
	(void)fprintf(stderr, "touch: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 11
E 10
E 7
D 2
close(fd);
return;

bad:
	fprintf(stderr, "Cannot touch %s\n", name);
	return;

create:
	if( (fd = creat(name, 0666)) < 0)
		goto bad;
	close(fd);
E 2
}
E 1
