h35013
s 00002/00004/00173
d D 8.8 94/04/01 09:50:57 bostic 38 37
c setting errno and then not exiting isn't safe
e
s 00000/00002/00177
d D 8.7 94/03/31 17:26:31 bostic 37 36
c doing a chmod on a directory causing a cycle is probably the
c right thing to do
e
s 00002/00000/00177
d D 8.6 94/03/31 17:04:37 bostic 36 35
c check for fts_read error
e
s 00012/00005/00165
d D 8.5 94/03/31 16:52:11 bostic 35 34
c do some more error checking on the octal value
e
s 00069/00031/00101
d D 8.4 94/03/31 16:32:04 bostic 34 33
c POSIX 1003.2B/D9 symbolic links
e
s 00013/00017/00119
d D 8.3 94/03/25 14:11:36 bostic 33 32
c handle all of the 'weird' strings
c check only the first two chars, so that long perm specs (e.g. "-xr") are OK.
c From: "Chris G. Demetriou" <cgd@postgres.Berkeley.EDU>
e
s 00014/00002/00122
d D 8.2 93/12/16 15:54:27 bostic 32 31
c handle first argument of -r,o=rw, for example
e
s 00005/00005/00119
d D 8.1 93/06/27 19:12:16 bostic 31 30
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00005/00120
d D 5.24 93/06/27 19:12:08 bostic 30 28
c don't set FTS_NOSTAT, because don't want to "chmod" symbolic links
c From: Theo Deraadt <deraadt@sun-lamp.cs.berkeley.edu>
e
s 00005/00005/00120
d R 8.1 93/05/31 14:16:46 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00052/00112
d D 5.23 93/02/21 18:20:40 bostic 28 27
c use err(3) functions, minor cleanups
e
s 00040/00034/00124
d D 5.22 92/06/01 12:22:28 elan 27 26
c Added -Hh options.
e
s 00001/00001/00157
d D 5.21 92/01/27 09:57:56 bostic 26 25
c fts_statb -> fts_statp
e
s 00053/00020/00105
d D 5.20 91/12/28 14:42:34 bostic 25 24
c don't permit illegal file modes; lots of minor ANSI/cleanup
e
s 00002/00016/00123
d D 5.19 91/03/12 08:44:21 bostic 24 23
c fts(3) now sets errno correctly, FTS_DNX no longer exists
e
s 00005/00006/00134
d D 5.18 91/03/07 16:18:44 bostic 23 22
c -f is longer documented; left for compatibility
e
s 00029/00011/00111
d D 5.17 90/11/21 15:57:25 bostic 22 21
c put in rest of fts(3) error returns
e
s 00002/00002/00120
d D 5.16 90/11/14 17:57:42 bostic 21 20
c new fts routine names
e
s 00001/00001/00121
d D 5.15 90/06/16 16:32:10 bostic 20 19
c FTS_MULTIPLE is gone
e
s 00001/00011/00121
d D 5.14 90/05/31 20:27:52 bostic 19 18
c new copyright notice
e
s 00007/00006/00125
d D 5.13 90/05/17 16:37:08 bostic 18 17
c new structure names for fts
e
s 00001/00001/00130
d D 5.12 90/05/15 19:39:33 bostic 17 16
c string.h is ANSI C include file
e
s 00001/00001/00130
d D 5.11 90/04/28 12:41:22 bostic 16 15
c parenthetical mistake
e
s 00005/00004/00126
d D 5.10 90/04/16 14:10:08 bostic 15 14
c new version of get/setmode
e
s 00007/00007/00123
d D 5.9 90/03/05 11:12:09 bostic 14 13
c fix errno for ANSI variable scopign
e
s 00082/00205/00048
d D 5.8 90/01/01 13:05:51 bostic 13 12
c from scratch, using fts(3) and setmode(3) and the POSIX man page
e
s 00076/00131/00177
d D 5.7 88/04/21 11:37:37 bostic 12 11
c add getopt; clean up tree traversal; lint cleanups
e
s 00001/00001/00307
d D 5.6 87/12/21 12:30:57 bostic 11 10
c make ANSI C compatible; besides, structs don't fit in registers...
e
s 00027/00015/00281
d D 5.5 86/05/22 11:04:36 mckusick 10 9
c do not follow symbolic links; clarify error messages
e
s 00121/00077/00175
d D 5.4 85/08/31 17:44:44 sam 9 8
c add -f flag for install; cleanup -R code
e
s 00003/00002/00249
d D 5.3 85/06/18 12:58:48 mckusick 8 7
c fix mode propagation
e
s 00004/00007/00247
d D 5.2 85/06/09 12:08:42 mckusick 7 6
c make ``chmod -x ...'' work right
e
s 00009/00001/00245
d D 5.1 85/04/30 14:50:10 dist 6 5
c Add copyright
e
s 00013/00019/00233
d D 4.5 85/03/20 16:58:34 mckusick 5 4
c delete -X flag; replace with X mode to indicate conditional execute setting
e
s 00005/00002/00247
d D 4.4 84/06/18 14:54:22 ralph 4 3
c chmod follows links so don't use lstat.
e
s 00015/00006/00234
d D 4.3 84/03/31 21:43:20 layer 3 2
c -X flag:  set execute bits if set anywhere in mode
e
s 00000/00002/00240
d D 4.2 84/03/28 21:02:45 layer 2 1
c Don't fiddle with the modes with the -R flag...
e
s 00242/00000/00000
d D 4.1 84/03/26 15:26:11 layer 1 0
c date and time created 84/03/26 15:26:11 by layer
e
u
U
t
T
I 1
D 6
static char *sccsid = "%W% %G%";
E 6
I 6
/*
D 12
 * Copyright (c) 1980 Regents of the University of California.
E 12
I 12
D 13
 * Copyright (c) 1980, 1988 Regents of the University of California.
E 12
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 13
I 13
D 31
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 31
I 31
D 33
 * Copyright (c) 1989, 1993
E 33
I 33
 * Copyright (c) 1989, 1993, 1994
E 33
 *	The Regents of the University of California.  All rights reserved.
E 31
 *
D 19
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
E 19
I 19
 * %sccs.include.redist.c%
E 19
E 13
 */

#ifndef lint
I 12
D 31
char copyright[] =
D 13
"%Z% Copyright (c) 1980, 1988 Regents of the University of California.\n\
E 13
I 13
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
E 13
 All rights reserved.\n";
E 31
I 31
static char copyright[] =
D 33
"%Z% Copyright (c) 1989, 1993\n\
E 33
I 33
"%Z% Copyright (c) 1989, 1993, 1994\n\
E 33
	The Regents of the University of California.  All rights reserved.\n";
E 31
#endif /* not lint */

#ifndef lint
E 12
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
D 12
#endif
E 12
I 12
#endif /* not lint */
E 12
E 9
E 6

D 13
/*
 * chmod options mode files
 * where
D 5
 *	mode	is [ugoa][+-=][rwxstugo] or a octal number
E 5
I 5
D 9
 *	mode	is [ugoa][+-=][rwxXstugo] or a octal number
E 5
 *	options are -R
E 9
I 9
 *	mode is [ugoa][+-=][rwxXstugo] or an octal number
 *	options are -Rf
E 9
 */
#include <stdio.h>
E 13
#include <sys/types.h>
#include <sys/stat.h>
I 28

#include <err.h>
E 28
I 25
#include <errno.h>
E 25
D 13
#include <sys/dir.h>
E 13
I 13
#include <fts.h>
I 25
D 28
#include <unistd.h>
E 28
E 25
#include <stdio.h>
I 25
#include <stdlib.h>
E 25
D 17
#include <strings.h>
E 17
I 17
#include <string.h>
I 28
#include <unistd.h>
E 28
E 17
E 13

I 14
D 25
extern int errno;
E 25
E 14
D 9
#define	USER	05700	/* user's bits */
#define	GROUP	02070	/* group's bits */
#define	OTHER	00007	/* other's bits */
#define	ALL	01777	/* all (note absence of setuid, etc) */

#define	READ	00444	/* read permit */
#define	WRITE	00222	/* write permit */
#define	EXEC	00111	/* exec permit */
#define	SETID	06000	/* set[ug]id */
#define	STICKY	01000	/* sticky bit */

E 9
D 12
char	*modestring, *ms;
int	um;
int	status;
D 3
int	rflag = 0, debug = 0;
E 3
I 3
D 5
int	rflag, debug, Xflag;
E 5
I 5
D 9
int	rflag, debug;
E 9
I 9
int	fflag;
int	rflag;
E 12
I 12
D 13
static int	fflag, rflag, retval, um;
static char	*modestring, *ms;
E 13
I 13
D 28
int retval;
E 13
E 12
E 9
E 5
E 3

I 25
void err __P((const char *, ...));
void error __P((char *));
E 28
void usage __P((void));

int
E 25
D 9
main(argc,argv)
char **argv;
E 9
I 9
main(argc, argv)
D 12
	char *argv[];
E 12
I 12
	int argc;
D 25
	char **argv;
E 25
I 25
	char *argv[];
E 25
E 12
E 9
{
D 9
	register i;
E 9
D 3
	register char *p;
E 3
I 3
D 12
	register char *p, *flags;
E 3
D 9
	struct	stat st;
E 9
I 9
	register int i;
	struct stat st;
E 12
I 12
D 13
	extern char *optarg;
	extern int optind, opterr;
	int ch;
E 13
I 13
D 14
	extern int errno, optind;
E 14
I 14
D 25
	extern int optind;
E 25
E 14
D 27
	register FTS *fts;
E 27
I 27
D 35
	register FTS *ftsp;
E 27
	register FTSENT *p;
	register int oct, omode;
E 35
I 35
	FTS *ftsp;
	FTSENT *p;
E 35
D 25
	register char *mode;
I 15
	mode_t *set, *setmode();
E 25
E 15
D 28
	struct stat sb;
E 28
I 25
	mode_t *set;
I 35
	long val;
	int oct, omode;
E 35
E 25
D 27
	int ch, fflag, rflag;
E 27
I 27
D 34
	int ch, fflag, rflag, hflag, Hflag;
I 28
	int fts_options, retval;
E 34
I 34
	int Hflag, Lflag, Pflag, Rflag, ch, fflag, fts_options, hflag, rval;
E 34
E 28
E 27
I 25
	char *ep, *mode;
I 27
D 28
	int fts_options;
E 28
E 27
E 25
D 14
	mode_t setmode();
E 14
E 13
E 12
E 9

I 5
D 9
usage:
E 9
E 5
D 12
	if (argc < 3) {
D 9
		fprintf(stderr
D 3
			,"Usage: chmod [-R] [ugoa][+-=][rwxstugo] file ...\n");
E 3
I 3
D 5
			,"Usage: chmod [-RX] [ugoa][+-=][rwxstugo] file ...\n");
E 5
I 5
			,"Usage: chmod [-R] [ugoa][+-=][rwxXstugo] file ...\n");
E 9
I 9
		fprintf(stderr,
		    "Usage: chmod [-Rf] [ugoa][+-=][rwxXstugo] file ...\n");
E 9
E 5
E 3
		exit(-1);
	}
I 3
D 9

E 9
E 3
	argv++, --argc;
D 3
	if (strcmp(argv[0], "-R") == 0) {
		rflag++;
		argv++, --argc;
E 3
I 3
D 9
	if (*argv[0] == '-') {
D 7
		for (flags = argv[0]; *flags; ++flags)
			switch (*flags) {
			  case '-':			break;
			  case 'R':	rflag++;	break;
D 5
			  case 'X': 	Xflag++;	break;
E 5
I 5
			  default: 	argc = 0;	goto usage;
E 5
			}
		argv++, argc--;
E 7
I 7
		if (strcmp(argv[0], "-R") == 0) {
E 9
I 9
	while (argc > 0 && argv[0][0] == '-') {
		for (p = &argv[0][1]; *p; p++) switch (*p) {

E 12
I 12
D 13
	/*
	 * since "-[rwx]" etc. are valid file modes, we don't let getopt(3)
	 * print error messages, and we mess around with optind as necessary.
	 */
	opterr = 0;
	while ((ch = getopt(argc, argv, "Rf")) != EOF)
E 13
I 13
D 27
	fflag = rflag = 0;
	while ((ch = getopt(argc, argv, "Rfrwx")) != EOF)
E 27
I 27
D 34
	fts_options = FTS_PHYSICAL;
	fflag = rflag = hflag = Hflag = 0;
D 33
	while ((ch = getopt(argc, argv, "HRfhrwx")) != EOF)
E 27
E 13
		switch((char)ch) {
E 33
I 33
	while ((ch = getopt(argc, argv, "HRXfghorstuwx")) != EOF)
E 34
I 34
	Hflag = Lflag = Pflag = Rflag = fflag = hflag = 0;
	while ((ch = getopt(argc, argv, "HLPRXfgorstuwx")) != EOF)
E 34
		switch (ch) {
E 33
I 27
		case 'H':
			Hflag = 1;
D 34
			fts_options |= FTS_COMFOLLOW;
E 34
I 34
			Lflag = Pflag = 0;
E 34
			break;
I 34
		case 'L':
			Lflag = 1;
			Hflag = Pflag = 0;
			break;
		case 'P':
			Pflag = 1;
			Hflag = Lflag = 0;
			break;
E 34
E 27
E 12
		case 'R':
E 9
D 23
			rflag++;
E 23
I 23
D 34
			rflag = 1;
E 34
I 34
			Rflag = 1;
E 34
E 23
D 9
			argv++, argc--;
E 9
I 9
			break;
D 12

E 12
D 23
		case 'f':
			fflag++;
E 23
I 23
D 33
		case 'f':		/* no longer documented */
E 33
I 33
D 34
		case 'f':		/* XXX: no longer documented. */
E 34
I 34
		case 'f':		/* XXX: undocumented. */
E 34
E 33
			fflag = 1;
E 23
			break;
I 27
		case 'h':
I 34
			/*
			 * In System V (and probably POSIX.2) the -h option
			 * causes chmod to change the mode of the symbolic
			 * link.  4.4BSD's symbolic links don't have modes,
			 * so it's an undocumented noop.  Do syntax checking,
			 * though.
			 */
E 34
			hflag = 1;
D 34
			fts_options &= ~FTS_PHYSICAL;
			fts_options |= FTS_LOGICAL;
E 34
			break;
E 27
D 12

E 12
I 12
D 13
		case '?':
E 12
		default:
E 13
I 13
D 23
		/* "-[rwx]" are valid file modes */
		case 'r':
E 23
I 23
D 32
		case 'r':		/* "-[rwx]" are valid file modes */
E 32
I 32
		/*
I 33
		 * XXX
E 33
		 * "-[rwx]" are valid mode commands.  If they are the entire
		 * argument, getopt has moved past them, so decrement optind.
		 * Regardless, we're done argument processing.
		 */
D 33
		case 'r':
			if (!strcmp(argv[optind - 1], "-r"))
E 33
I 33
		case 'g': case 'o': case 'r': case 's':
		case 't': case 'u': case 'w': case 'X': case 'x':
			if (argv[optind - 1][0] == '-' &&
			    argv[optind - 1][1] == ch &&
			    argv[optind - 1][2] == '\0')
E 33
				--optind;
			goto done;
E 32
E 23
D 33
		case 'w':
I 32
			if (!strcmp(argv[optind - 1], "-w"))
				--optind;
			goto done;
E 32
		case 'x':
E 13
I 12
D 32
			--optind;
E 32
I 32
			if (!strcmp(argv[optind - 1], "-x"))
				--optind;
E 32
E 12
			goto done;
E 33
I 13
		case '?':
		default:
			usage();
E 13
E 9
		}
I 9
D 12
		argc--, argv++;
E 12
I 12
done:	argv += optind;
	argc -= optind;

D 13
	if (argc < 2) {
		fputs("usage: chmod [-Rf] [ugoa][+-=][rwxXstugo] file ...\n",
		    stderr);
		exit(-1);
E 12
E 9
E 7
E 3
	}
E 13
I 13
	if (argc < 2)
		usage();
E 13
I 3
D 9

E 9
I 9
D 12
done:
E 9
E 3
	modestring = argv[0];
E 12
I 12

I 34
	fts_options = FTS_PHYSICAL;
	if (Rflag) {
		if (hflag)
			errx(1,
		"the -R and -h options may not be specified together.");
		if (Hflag)
			fts_options |= FTS_COMFOLLOW;
		if (Lflag) {
			fts_options &= ~FTS_PHYSICAL;
			fts_options |= FTS_LOGICAL;
		}
	}

E 34
D 13
	modestring = *argv;
E 12
D 9

E 9
	um = umask(0);
D 12
	(void) newmode(0);
	for (i = 1; i < argc; i++) {
		p = argv[i];
I 9
		/* do stat for directory arguments */
E 9
D 4
		if (lstat(p, &st) < 0) {
E 4
I 4
D 10
		if (stat(p, &st) < 0) {
E 4
D 9
			fprintf(stderr, "chmod: can't access %s\n", p);
			++status;
E 9
I 9
			status += error("can't access %s", p);
E 10
I 10
		if (lstat(p, &st) < 0) {
			status += Perror(p);
E 10
E 9
			continue;
		}
D 9
		if (rflag && st.st_mode & S_IFDIR) {
E 9
I 9
D 10
		if (rflag && st.st_mode&S_IFDIR) {
E 10
I 10
		if (rflag && (st.st_mode&S_IFMT) == S_IFDIR) {
E 10
E 9
			status += chmodr(p, newmode(st.st_mode));
D 9
		} else if (chmod(p, newmode(st.st_mode)) < 0) {
			fprintf(stderr, "chmod: can't change %s\n", p);
			++status;
E 9
			continue;
		}
I 10
		if ((st.st_mode&S_IFMT) == S_IFLNK && stat(p, &st) < 0) {
			status += Perror(p);
			continue;
		}
E 10
I 9
		if (chmod(p, newmode(st.st_mode)) < 0) {
D 10
			status += error("can't change %s", p);
E 10
I 10
			status += Perror(p);
E 10
			continue;
		}
E 9
	}
	exit(status);
E 12
I 12
	(void)newmode((u_short)0);

	while (*++argv)
		change(*argv);
	exit(retval);
E 12
}

D 12
chmodr(dir, mode)
D 9
	char	*dir;
E 9
I 9
	char *dir;
E 12
I 12
change(file)
	char *file;
E 12
E 9
{
D 5
#define CHECK(name,sbuf)\
D 4
	if (lstat(name, sbuf) < 0) {\
E 4
I 4
	if (stat(name, sbuf) < 0) {\
E 4
		fprintf(stderr, "chmod: can't access %s\n", dp->d_name);\
		return(1);\
	}
	
E 5
D 9
	register DIR		*dirp;
	register struct direct	*dp;
	register struct stat	st;
	char			savedir[1024];
E 9
I 9
	register DIR *dirp;
	register struct direct *dp;
D 11
	register struct stat st;
E 11
I 11
D 12
	struct stat st;
E 11
	char savedir[1024];
	int ecode;
E 12
I 12
	struct stat buf;
E 12
E 9

D 9
	if (getwd(savedir) == 0) {
		fprintf(stderr, "chmod: %s\n", savedir);
		exit(255);
	}

E 9
I 9
D 12
	if (getwd(savedir) == 0)
		fatal(255, "%s", savedir);
E 9
	/*
D 9
	** chmod what we are given before doing it's contents
	*/
	chmod(dir, newmode(mode));
	
	chdir(dir);
	if ((dirp = opendir(".")) == NULL) {
		perror(dir);
		return(1);
	}
E 9
I 9
	 * Change what we are given before doing it's contents
	 */
D 10
	if (chmod(dir, newmode(mode)) < 0 && error("can't change %s", dir))
E 10
I 10
	if (chmod(dir, newmode(mode)) < 0 && Perror(dir))
E 10
		return (1);
D 10
	if (chdir(dir) < 0)
		return (Perror(dir));
	if ((dirp = opendir(".")) == NULL)
		return (Perror(dir));
E 10
I 10
	if (chdir(dir) < 0) {
		Perror(dir);
		return (1);
E 12
I 12
	if (lstat(file, &buf) || chmod(file, newmode(buf.st_mode))) {
		err(file);
		return;
E 12
	}
D 12
	if ((dirp = opendir(".")) == NULL) {
		Perror(dir);
		return (1);
	}
E 10
E 9
	dp = readdir(dirp);
	dp = readdir(dirp); /* read "." and ".." */
I 9
	ecode = 0;
E 9
	for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp)) {
D 5
		CHECK(dp->d_name, &st);
E 5
I 5
D 9
		if (stat(dp->d_name, &st) < 0) {
			fprintf(stderr, "chmod: can't access %s\n", dp->d_name);
			return(1);
E 9
I 9
		if (lstat(dp->d_name, &st) < 0) {
D 10
			ecode = error("can't access %s", dp->d_name);
E 10
I 10
			ecode = Perror(dp->d_name);
E 10
			if (ecode)
				break;
			continue;
E 12
I 12
	if (rflag && ((buf.st_mode & S_IFMT) == S_IFDIR)) {
		if (chdir(file) < 0 || !(dirp = opendir("."))) {
			err(file);
			return;
E 13
I 13
	mode = *argv;
	if (*mode >= '0' && *mode <= '7') {
D 25
		omode = (int)strtol(mode, (char **)NULL, 8);
E 25
I 25
D 35
		omode = (int)strtol(mode, &ep, 8);
		if (omode < 0 || *ep)
E 35
I 35
		errno = 0;
		val = strtol(mode, &ep, 8);
		if (val > INT_MAX || val < 0)
			errno = ERANGE;
		if (errno)
			err(1, "invalid file mode: %s", mode);
		if (*ep)
E 35
D 28
			err("invalid file mode: %s", mode);
E 28
I 28
			errx(1, "invalid file mode: %s", mode);
I 35
		omode = val;
E 35
E 28
E 25
		oct = 1;
	} else {
D 14
		if (setmode(mode, 0, 0) == (mode_t)-1) {
E 14
I 14
D 15
		if (setmode(mode) == -1) {
E 15
I 15
D 25
		if (!(set = setmode(mode))) {
E 15
E 14
			(void)fprintf(stderr, "chmod: invalid file mode.\n");
			exit(1);
E 13
E 12
E 9
		}
E 25
I 25
D 28
		if (!(set = setmode(mode)))
			err("invalid file mode: %s", mode);
E 28
I 28
		if ((set = setmode(mode)) == NULL)
			errx(1, "invalid file mode: %s", mode);
E 28
E 25
E 5
D 8
		chmod(dp->d_name, newmode(st.st_mode));
E 8
D 9
		if (st.st_mode & S_IFDIR)
D 8
			chmodr(dp->d_name, mode);
E 8
I 8
			chmodr(dp->d_name, newmode(st.st_mode));
		else
			chmod(dp->d_name, newmode(st.st_mode));
E 9
I 9
D 10
		if (st.st_mode&S_IFDIR) {
E 10
I 10
D 12
		if ((st.st_mode&S_IFMT) == S_IFDIR) {
E 10
			ecode = chmodr(dp->d_name, newmode(st.st_mode));
			if (ecode)
				break;
			continue;
E 12
I 12
D 13
		for (dp = readdir(dirp); dp; dp = readdir(dirp)) {
			if (dp->d_name[0] == '.' && (!dp->d_name[1] ||
			    dp->d_name[1] == '.' && !dp->d_name[2]))
				continue;
			change(dp->d_name);
E 12
		}
I 10
D 12
		if ((st.st_mode&S_IFMT) == S_IFLNK)
			continue;
E 10
		if (chmod(dp->d_name, newmode(st.st_mode)) < 0 &&
D 10
		    (ecode = error("can't change %s", dp->d_name)))
E 10
I 10
		    (ecode = Perror(dp->d_name)))
E 10
			break;
E 12
I 12
		closedir(dirp);
		if (chdir("..")) {
			err("..");
			exit(fflag ? 0 : -1);
		}
E 13
I 13
		oct = 0;
E 13
E 12
E 9
E 8
	}
D 12
	closedir(dirp);
D 9
	chdir(savedir);
	return(0);
E 9
I 9
	if (chdir(savedir) < 0)
		fatal(255, "can't change back to %s", savedir);
	return (ecode);
E 12
E 9
D 13
}
E 13

I 9
D 12
error(fmt, a)
	char *fmt, *a;
{

	if (!fflag) {
		fprintf(stderr, "chmod: ");
		fprintf(stderr, fmt, a);
		putc('\n', stderr);
	}
	return (!fflag);
}

fatal(status, fmt, a)
	int status;
	char *fmt, *a;
{

	fflag = 0;
	(void) error(fmt, a);
	exit(status);
}

Perror(s)
E 12
I 12
D 13
err(s)
E 12
	char *s;
{
D 12

D 10
	fprintf(stderr, "chmod: ");
	perror(s);
	return (1);
E 10
I 10
	if (!fflag) {
		fprintf(stderr, "chmod: ");
		perror(s);
	}
	return (!fflag);
E 12
I 12
	if (fflag)
		return;
	fputs("chmod: ", stderr);
	perror(s);
	retval = -1;
E 12
E 10
}

E 9
newmode(nm)
D 9
unsigned nm;
E 9
I 9
D 12
	unsigned nm;
E 12
I 12
	u_short nm;
E 12
E 9
{
D 12
	register o, m, b;
	int savem;
E 12
I 12
	register int o, m, b;
E 12

	ms = modestring;
D 12
	savem = nm;
E 12
	m = abs();
D 5
	if (!*ms) {
		nm = m;
		goto ret;
	}
E 5
I 5
D 9
	if (!*ms)
		return(m);
E 9
I 9
	if (*ms == '\0')
		return (m);
E 9
E 5
	do {
		m = who();
		while (o = what()) {
D 12
			b = where(nm);
E 12
I 12
			b = where((int)nm);
E 12
			switch (o) {
			case '+':
				nm |= b & m;
				break;
			case '-':
				nm &= ~(b & m);
				break;
			case '=':
				nm &= ~m;
				nm |= b & m;
				break;
E 13
I 13
D 34
	retval = 0;
E 34
D 27
	if (rflag) {
D 21
		if (!(fts = ftsopen(++argv,
E 21
I 21
D 25
		if (!(fts = fts_open(++argv,
E 21
D 20
		    (oct ? FTS_NOSTAT : 0)|FTS_MULTIPLE|FTS_PHYSICAL, 0))) {
E 20
I 20
		    oct ? FTS_NOSTAT|FTS_PHYSICAL : FTS_PHYSICAL, 0))) {
E 20
			(void)fprintf(stderr, "chmod: %s.\n", strerror(errno));
			exit(1);
		}
E 25
I 25
		if ((fts = fts_open(++argv,
		    oct ? FTS_NOSTAT|FTS_PHYSICAL : FTS_PHYSICAL, 0)) == NULL)
E 27
I 27
D 30
	if (oct)
		fts_options |= FTS_NOSTAT;
E 30
	if ((ftsp = fts_open(++argv, fts_options, 0)) == NULL)
E 27
D 28
			err("%s", strerror(errno));
E 28
I 28
D 30
			err(1, "");
E 30
I 30
D 34
		err(1, "");
E 30
E 28
E 25
D 21
		while (p = ftsread(fts)) {
E 21
I 21
D 22
		while (p = fts_read(fts)) {
E 21
D 18
			if (p->info == FTS_D)
E 18
I 18
			if (p->fts_info == FTS_D)
E 18
				continue;
D 18
			if (p->info == FTS_ERR) {
E 18
I 18
			if (p->fts_info == FTS_ERR) {
E 18
				if (!fflag)
E 22
I 22
D 27
		while (p = fts_read(fts))
			switch(p->fts_info) {
D 24
			case FTS_DNR:
				(void)fprintf(stderr,
				    "chmod: %s: unable to read.\n",
				    p->fts_path);
				break;
			case FTS_DNX:
				(void)fprintf(stderr,
				    "chmod: %s: unable to search.\n",
				    p->fts_path);
				break;
E 24
			case FTS_D:
D 24
			case FTS_DC:
E 24
				break;
I 24
			case FTS_DNR:
E 24
			case FTS_ERR:
I 24
			case FTS_NS:
E 24
D 25
				(void)fprintf(stderr, "chmod: %s: %s.\n",
				    p->fts_path, strerror(errno));
				exit(1);
E 25
I 25
				err("%s: %s", p->fts_path, strerror(errno));
E 25
D 24
			case FTS_NS:
				(void)fprintf(stderr,
				    "chmod: %s: unable to stat.\n",
				    p->fts_path);
				break;
E 24
			default:
				if (chmod(p->fts_accpath, oct ? omode :
D 26
				    getmode(set, p->fts_statb.st_mode)) &&
E 26
I 26
				    getmode(set, p->fts_statp->st_mode)) &&
E 26
				    !fflag)
E 22
D 18
					error(p->path);
E 18
I 18
					error(p->fts_path);
E 18
D 22
				continue;
E 22
I 22
				break;
E 22
E 13
			}
I 13
D 14
			if (chmod(p->accpath, oct ? omode :
			    (int)setmode(mode, p->statb.st_mode, 0)) && !fflag)
E 14
I 14
D 15
			if (chmod(p->accpath,
			    oct ? omode : getmode(p->statb.st_mode) && !fflag))
E 15
I 15
D 18
			if (chmod(p->accpath, oct ?
D 16
			    omode : getmode(set, p->statb.st_mode) && !fflag))
E 16
I 16
			    omode : getmode(set, p->statb.st_mode)) && !fflag)
E 16
E 15
E 14
				error(p->path);
E 18
I 18
D 22
			if (chmod(p->fts_accpath, oct ?
			    omode : getmode(set, p->fts_statb.st_mode)) &&
			    !fflag)
				error(p->fts_path);
E 18
E 13
		}
E 22
D 13
	} while (*ms++ == ',');
D 9
	if (*--ms) {
		fprintf(stderr, "chmod: invalid mode\n");
		exit(255);
	}
D 5
ret:
I 3
	if (Xflag && ((savem & S_IFDIR) || (savem & S_IEXEC)))
		nm = nm | ((nm & 0444) >> 2);
E 5
E 3
D 2
	if ((savem & S_IFDIR) || (savem & S_IEXEC))
		nm = nm | ((nm & 0444) >> 2);
E 2
	return(nm);
E 9
I 9
D 12
	if (*--ms)
		fatal(255, "invalid mode");
	return (nm);
E 12
I 12
	if (*--ms) {
		fputs("chmod: invalid mode.\n", stderr);
		exit(-1);
E 13
I 13
		exit(retval);
E 13
	}
D 13
	return ((int)nm);
E 13
I 13
	if (oct) {
		while (*++argv)
			if (chmod(*argv, omode) && !fflag)
				error(*argv);
	} else
		while (*++argv)
D 14
			if ((lstat(*argv, &sb) || chmod(*argv,
			    (int)setmode(mode, sb.st_mode, 0))) && !fflag)
E 14
I 14
			if ((lstat(*argv, &sb) ||
D 15
			    chmod(*argv, getmode(sb.st_mode))) && !fflag)
E 15
I 15
			    chmod(*argv, getmode(set, sb.st_mode))) && !fflag)
E 15
E 14
				error(*argv);
E 27
I 27
D 33
	while (p = fts_read(ftsp))
		switch(p->fts_info) {
E 33
I 33
	while ((p = fts_read(ftsp)) != NULL)
E 34
I 34
		err(1, NULL);
	for (rval = 0; (p = fts_read(ftsp)) != NULL;) {
E 34
		switch (p->fts_info) {
E 33
		case FTS_D:
D 34
			if (!rflag)
				fts_set(ftsp, p, FTS_SKIP);
I 30
		case FTS_SL:
		case FTS_SLNONE:
E 34
I 34
			if (Rflag)		/* Change it at FTS_DP. */
				continue;
			fts_set(ftsp, p, FTS_SKIP);
E 34
E 30
			break;
D 34
		case FTS_DNR:
		case FTS_ERR:
E 34
I 34
D 37
		case FTS_DC:			/* Ignore. */
			continue;
E 37
		case FTS_DNR:			/* Warn, chmod, continue. */
D 38
			errno = p->fts_errno;
			warn("%s", p->fts_path);
E 38
I 38
			warnx("%s: %s", p->fts_path, strerror(p->fts_errno));
E 38
			rval = 1;
			break;
		case FTS_ERR:			/* Warn, continue. */
E 34
		case FTS_NS:
D 28
			err("%s: %s", p->fts_path, strerror(errno));
E 28
I 28
D 34
			err(1, "%s", p->fts_path);
E 28
		default:	
D 30
			if (p->fts_info == FTS_SL && 
			    !(hflag || 
E 30
I 30
			if (p->fts_info == FTS_SL && !(hflag || 
E 30
			    (Hflag && p->fts_level == FTS_ROOTLEVEL)))
				continue;
			if (chmod(p->fts_accpath, oct ? omode :
D 28
			    getmode(set, p->fts_statp->st_mode)) &&
			    !fflag)
				error(p->fts_path);
E 28
I 28
			    getmode(set, p->fts_statp->st_mode)) && !fflag) {
				warn(p->fts_path);
				retval = 1;
			}
E 34
I 34
D 38
			errno = p->fts_errno;
			warn("%s", p->fts_path);
E 38
I 38
			warnx("%s: %s", p->fts_path, strerror(p->fts_errno));
E 38
			rval = 1;
			continue;
		case FTS_SL:			/* Ignore. */
		case FTS_SLNONE:
			/*
			 * The only symlinks that end up here are ones that
			 * don't point to anything and ones that we found
			 * doing a physical walk.
			 */
			continue;
		default:
E 34
E 28
			break;
		}
E 27
D 34
	exit(retval);
E 34
I 34
		if (chmod(p->fts_accpath, oct ? omode :
		    getmode(set, p->fts_statp->st_mode)) && !fflag) {
			warn(p->fts_path);
			rval = 1;
		}
	}
I 36
	if (errno)
		err(1, "fts_read");
E 36
	exit(rval);
E 34
E 13
E 12
E 9
}

I 25
void
E 25
D 13
abs()
E 13
I 13
D 28
error(name)
	char *name;
E 13
{
D 12
	register c, i;
E 12
I 12
D 13
	register int c, i;
E 12

	i = 0;
	while ((c = *ms++) >= '0' && c <= '7')
		i = (i << 3) + (c - '0');
	ms--;
D 9
	return(i);
E 9
I 9
	return (i);
E 13
I 13
D 25
	(void)fprintf(stderr, "chmod: %s: %s.\n", name, strerror(errno));
E 25
I 25
	(void)fprintf(stderr, "chmod: %s: %s\n", name, strerror(errno));
E 25
	retval = 1;
E 13
E 9
}

I 25
void
E 28
E 25
I 9
D 13
#define	USER	05700	/* user's bits */
#define	GROUP	02070	/* group's bits */
#define	OTHER	00007	/* other's bits */
#define	ALL	01777	/* all (note absence of setuid, etc) */

#define	READ	00444	/* read permit */
#define	WRITE	00222	/* write permit */
#define	EXEC	00111	/* exec permit */
#define	SETID	06000	/* set[ug]id */
#define	STICKY	01000	/* sticky bit */

E 9
who()
E 13
I 13
usage()
E 13
{
D 12
	register m;
E 12
I 12
D 13
	register int m;
E 12

	m = 0;
	for (;;) switch (*ms++) {
	case 'u':
		m |= USER;
		continue;
	case 'g':
		m |= GROUP;
		continue;
	case 'o':
		m |= OTHER;
		continue;
	case 'a':
		m |= ALL;
		continue;
	default:
		ms--;
		if (m == 0)
			m = ALL & ~um;
D 9
		return m;
E 9
I 9
		return (m);
E 9
	}
}

what()
{
D 12

E 12
	switch (*ms) {
	case '+':
	case '-':
	case '=':
D 9
		return *ms++;
E 9
I 9
		return (*ms++);
E 9
	}
D 9
	return(0);
E 9
I 9
	return (0);
E 9
}

where(om)
D 9
register om;
E 9
I 9
D 12
	register om;
E 12
I 12
	register int om;
E 12
E 9
{
D 12
	register m;
E 12
I 12
	register int m;
E 12

 	m = 0;
	switch (*ms) {
	case 'u':
		m = (om & USER) >> 6;
		goto dup;
	case 'g':
		m = (om & GROUP) >> 3;
		goto dup;
	case 'o':
		m = (om & OTHER);
	dup:
		m &= (READ|WRITE|EXEC);
		m |= (m << 3) | (m << 6);
		++ms;
D 9
		return m;
E 9
I 9
		return (m);
E 9
	}
	for (;;) switch (*ms++) {
	case 'r':
		m |= READ;
		continue;
	case 'w':
		m |= WRITE;
		continue;
	case 'x':
		m |= EXEC;
I 4
		continue;
	case 'X':
D 5
		Xflag++;
E 5
I 5
		if ((om & S_IFDIR) || (om & EXEC))
			m |= EXEC;
E 5
E 4
		continue;
	case 's':
		m |= SETID;
		continue;
	case 't':
		m |= STICKY;
		continue;
	default:
		ms--;
D 9
		return m;
E 9
I 9
		return (m);
E 9
	}
E 13
I 13
D 23
	(void)fprintf(stderr, "chmod: chmod [-fR] mode file ...\n");
E 23
I 23
D 25
	(void)fprintf(stderr, "chmod: chmod [-R] mode file ...\n");
E 25
I 25
D 27
	(void)fprintf(stderr, "usage: chmod [-R] mode file ...\n");
E 27
I 27
D 34
	(void)fprintf(stderr, "usage: chmod [-HRh] mode file ...\n");
E 34
I 34
	(void)fprintf(stderr,
	    "usage: chmod [-R [-H | -L | -P]] mode file ...\n");
E 34
E 27
E 25
E 23
	exit(1);
I 25
D 28
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
	(void)fprintf(stderr, "chmod: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 28
E 25
E 13
}
E 1
