h48783
s 00000/00001/00247
d D 8.8 94/04/04 07:34:37 bostic 34 32
c optind is declared in the library
e
s 00007/00006/00242
d R 8.8 94/04/04 02:46:10 pendry 33 32
c prettiness police
e
s 00002/00004/00246
d D 8.7 94/04/01 09:49:00 bostic 32 31
c setting errno and then not exiting isn't safe
e
s 00002/00001/00248
d D 8.6 94/03/31 17:30:38 bostic 31 30
c chown has the same problem as all the others -- it has to know the
c file type so it can skip symbolic links.  Therefore, it can't set FTS_NOSTAT
e
s 00000/00002/00249
d D 8.5 94/03/31 17:26:06 bostic 30 29
c doing a chown on a directory causing a cycle is probably the
c right thing to do
e
s 00002/00000/00249
d D 8.4 94/03/31 17:04:10 bostic 29 28
c check for fts_read erorr
e
s 00010/00005/00239
d D 8.3 94/03/31 16:25:18 bostic 28 27
c clean up fts(3) return conditions
e
s 00133/00100/00111
d D 8.2 94/03/31 16:04:07 bostic 27 26
c POSIX 1003.2b/D9 symbolic links
e
s 00005/00005/00206
d D 8.1 93/06/06 13:51:51 bostic 26 25
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00003/00201
d D 5.20 92/06/01 12:14:36 elan 25 24
c Added -Hh flags.
e
s 00027/00020/00177
d D 5.19 92/05/28 12:06:54 elan 24 23
c Added -Hh flags and cleaned up the fts(3) operations.
e
s 00025/00020/00172
d D 5.18 91/03/09 13:08:39 bostic 23 22
c ANSI, POSIX.2 Draft 11; requires that "chgrp 22" use the group 22's
c group number if such a group exists
e
s 00002/00002/00190
d D 5.17 90/11/14 18:04:41 bostic 22 21
c change fts routine names
e
s 00047/00077/00145
d D 5.16 90/10/26 14:52:07 bostic 21 20
c change group character, dot, to colon (dot still permitted)
c change the -f flag to ONLY mask errors in changing owner/group
c new manual page, started from the POSIX.2 manual page
c use FTS to walk the tree
e
s 00001/00011/00221
d D 5.15 90/06/01 18:38:14 bostic 20 19
c new copyright notice
e
s 00002/00008/00230
d D 5.14 90/04/25 16:06:18 marc 19 18
c no static
e
s 00011/00008/00227
d D 5.13 89/07/07 09:06:25 bostic 18 17
c only check list of groups if EPERM is returned.
c sys/dir.h -> dirent.h, minor lint
e
s 00015/00004/00220
d D 5.12 89/03/05 12:14:01 bostic 17 16
c handle 'chown a b/c' right; 'chdir ..' isn't enough
e
s 00010/00005/00214
d D 5.11 88/06/18 14:34:06 bostic 16 15
c install approved copyright notice
e
s 00032/00024/00187
d D 5.10 88/04/23 12:33:13 bostic 15 14
c break out chown error into separate routine
e
s 00037/00021/00174
d D 5.9 88/04/22 12:18:07 bostic 14 13
c don't check group membership until after failure; don't do stat
c unless recursive, minor cleanups
e
s 00144/00146/00051
d D 5.8 88/04/21 11:04:00 bostic 13 12
c replacement code for chown and chgrp; major differences are use of
c getopt(3), much faster tree traversal code, fixed checking of group
c membership; complete rewrite, added Berkeley specific header
e
s 00002/00000/00195
d D 5.7 88/04/18 16:46:25 mckusick 12 11
c fail on null owner names (4.3BSD/etc/127)
e
s 00002/00002/00193
d D 5.6 86/05/29 15:30:43 mckusick 11 10
c fix those typos!
e
s 00002/00002/00193
d D 5.5 86/05/22 11:44:36 mckusick 10 9
c check mode properly
e
s 00020/00014/00175
d D 5.4 86/05/22 10:06:21 mckusick 9 8
c do not follow symbolic links; clean up error messages
e
s 00011/00015/00178
d D 5.3 86/04/29 19:50:22 bloom 8 7
c a dot without a group in the user field caused problems
e
s 00127/00097/00066
d D 5.2 85/08/31 17:45:13 sam 7 6
c cleanup
e
s 00015/00001/00148
d D 5.1 85/06/06 11:01:54 dist 6 5
c Add copyright
e
s 00002/00002/00147
d D 4.5 85/03/20 18:00:50 mckusick 5 4
c fix usage message
e
s 00106/00018/00043
d D 4.4 85/03/20 14:33:04 mckusick 4 3
c add -R option to work recursively (from layer)
e
s 00001/00001/00060
d D 4.3 83/11/23 15:18:28 mckusick 3 2
c chown does not follow symbolic links, so must use lstat to get gid
e
s 00007/00002/00054
d D 4.2 83/03/08 17:58:39 mckusick 2 1
c add -f option so install will not complain
e
s 00056/00000/00000
d D 4.1 80/10/01 17:25:32 bill 1 0
c date and time created 80/10/01 17:25:32 by bill
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
D 13
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 13
I 13
D 26
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 26
I 26
D 27
 * Copyright (c) 1988, 1993
E 27
I 27
 * Copyright (c) 1988, 1993, 1994
E 27
 *	The Regents of the University of California.  All rights reserved.
E 26
 *
D 20
 * Redistribution and use in source and binary forms are permitted
D 16
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 16
I 16
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
E 20
I 20
 * %sccs.include.redist.c%
E 20
E 16
E 13
 */

#ifndef lint
D 26
char copyright[] =
D 13
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 13
I 13
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
E 13
 All rights reserved.\n";
E 26
I 26
static char copyright[] =
D 27
"%Z% Copyright (c) 1988, 1993\n\
E 27
I 27
"%Z% Copyright (c) 1988, 1993, 1994\n\
E 27
	The Regents of the University of California.  All rights reserved.\n";
E 26
D 7
#endif not lint
E 7
I 7
D 13
#endif
E 13
I 13
#endif /* not lint */
E 13
E 7

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
D 13
#endif
E 13
I 13
#endif /* not lint */
E 13
E 7
E 6
I 4

E 4
D 13
/*
D 4
 * chown uid file ...
E 4
I 4
D 5
 * chown [-fr] uid[.gid] file ...
E 5
I 5
 * chown [-fR] uid[.gid] file ...
E 5
E 4
 */

#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
E 13
I 13
#include <sys/param.h>
E 13
#include <sys/stat.h>
D 13
#include <pwd.h>
E 13
I 4
D 18
#include <sys/dir.h>
E 18
I 18
D 27
#include <sys/errno.h>
E 27
I 27

#include <ctype.h>
E 27
#include <dirent.h>
I 27
#include <err.h>
#include <errno.h>
E 27
I 21
#include <fts.h>
E 21
E 18
I 13
D 27
#include <pwd.h>
E 27
E 13
#include <grp.h>
I 23
D 27
#include <unistd.h>
E 27
I 27
#include <pwd.h>
E 27
E 23
I 7
D 13
#include <strings.h>
E 13
I 13
#include <stdio.h>
D 27
#include <ctype.h>
E 27
I 23
#include <stdlib.h>
E 23
I 21
#include <string.h>
I 27
#include <unistd.h>
E 27
E 21
E 13
E 7
E 4

D 7
struct	passwd	*pwd,*getpwnam();
struct	stat	stbuf;
E 7
I 7
D 13
struct	passwd *pwd;
struct	passwd *getpwnam();
struct	stat stbuf;
E 7
int	uid;
int	status;
I 2
D 4
int	fflag;
E 4
I 4
D 7
int	fflag, rflag;
E 7
I 7
int	fflag;
int	rflag;
E 13
I 13
D 19
static int ischown, uid, gid, fflag, rflag, retval;
D 14
static char *myname;
E 14
I 14
static char *gname, *myname;
E 19
I 19
D 27
int ischown, uid, gid, fflag, rflag, retval;
E 27
I 27
void	a_gid __P((char *));
void	a_uid __P((char *));
void	chownerr __P((char *));
u_long	id __P((char *, char *));
void	usage __P((void));

uid_t uid;
gid_t gid;
int Rflag, ischown, fflag;
E 27
char *gname, *myname;
E 19
E 14
E 13
E 7
E 4
E 2

I 27
int
E 27
main(argc, argv)
D 7
char *argv[];
E 7
I 7
D 13
	char *argv[];
E 13
I 13
	int argc;
D 27
	char **argv;
E 27
I 27
	char *argv[];
E 27
E 13
E 7
{
D 4
	register c;
E 4
I 4
D 13
	register int c, gid;
D 7
	register char *flags, *group;
E 7
I 7
	register char *cp, *group;
E 7
	struct group *grp;
E 13
I 13
D 21
	extern char *optarg;
E 21
D 34
	extern int optind;
E 34
I 21
D 24
	register FTS *fts;
E 24
I 24
D 27
	register FTS *ftsp;
E 24
	register FTSENT *p;
E 21
	register char *cp;
	int ch;
I 24
	int fts_options;
E 24
D 17
	char *index(), *rindex();
E 17
I 17
D 21
	char curpath[MAXPATHLEN], *reset, *index(), *rindex();
E 21
E 17
E 13
E 4
D 25

E 25
I 25
	int hflag, Hflag;
E 27
I 27
	FTS *ftsp;
	FTSENT *p;
	int Hflag, Lflag, Pflag, ch, fts_options, hflag, rval;
	char *cp;
E 27
	
E 25
D 7
	if(argc < 3) {
E 7
I 7
D 13
	argc--, argv++;
	while (argc > 0 && argv[0][0] == '-') {
		for (cp = &argv[0][1]; *cp; cp++) switch (*cp) {
E 13
I 13
	myname = (cp = rindex(*argv, '/')) ? cp + 1 : *argv;
	ischown = myname[2] == 'o';
E 13
D 25

E 25
I 25
	
D 27
	hflag = Hflag = 0;
E 25
I 13
D 24
	while ((ch = getopt(argc, argv, "Rf")) != EOF)
E 24
I 24
	fts_options = FTS_NOSTAT | FTS_PHYSICAL;
	while ((ch = getopt(argc, argv, "HRfh")) != EOF)
E 24
		switch((char)ch) {
E 27
I 27
	Hflag = Lflag = Pflag = hflag = 0;
	while ((ch = getopt(argc, argv, "HLPRfh")) != EOF)
		switch (ch) {
		case 'H':
			Hflag = 1;
			Lflag = Pflag = 0;
			break;
		case 'L':
			Lflag = 1;
			Hflag = Pflag = 0;
			break;
		case 'P':
			Pflag = 1;
			Hflag = Lflag = 0;
			break;
E 27
		case 'R':
D 21
			rflag++;
E 21
I 21
D 27
			rflag = 1;
E 27
I 27
			Rflag = 1;
E 27
E 21
			break;
E 13
		case 'f':
D 21
			fflag++;
E 21
I 21
			fflag = 1;
E 21
			break;
I 24
		case 'h':
I 27
			/*
			 * In System V (and probably POSIX.2) the -h option
			 * causes chown/chgrp to change the owner/group of
			 * the symbolic link.  4.4BSD's symbolic links don't
			 * have owners/groups, so it's an undocumented noop.
			 * Do syntax checking, though.
			 */
E 27
I 25
			hflag = 1;
E 25
D 27
			fts_options &= ~FTS_PHYSICAL;
			fts_options |= FTS_LOGICAL;
E 27
			break;
D 27
		case 'H':
I 25
			Hflag = 1;
E 25
			fts_options |= FTS_COMFOLLOW;
			break;
E 27
E 24
I 13
		case '?':
		default:
			usage();
		}
	argv += optind;
	argc -= optind;
E 13

D 13
		case 'R':
			rflag++;
			break;
E 13
I 13
	if (argc < 2)
		usage();
E 13

I 27
D 31
	fts_options = FTS_NOSTAT | FTS_PHYSICAL;
E 31
I 31
	fts_options = FTS_PHYSICAL;
E 31
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

E 27
I 21
	uid = gid = -1;
E 21
D 13
		default:
			fatal(255, "unknown option: %c", *cp);
E 13
I 13
	if (ischown) {
I 21
#ifdef SUPPORT_DOT
E 21
D 27
		if (cp = index(*argv, '.')) {
E 27
I 27
		if ((cp = strchr(*argv, '.')) != NULL) {
E 27
			*cp++ = '\0';
D 23
			setgid(cp);
E 23
I 23
			a_gid(cp);
E 23
E 13
D 21
		}
D 13
		argv++, argc--;
E 13
I 13
		else
			gid = -1;
E 21
I 21
		} else
#endif
D 27
		if (cp = index(*argv, ':')) {
E 27
I 27
		if ((cp = strchr(*argv, ':')) != NULL) {
E 27
			*cp++ = '\0';
D 23
			setgid(cp);
E 23
I 23
			a_gid(cp);
E 23
		} 
E 21
D 23
		setuid(*argv);
E 23
I 23
		a_uid(*argv);
E 23
E 13
D 27
	}
D 13
	if (argc < 2) {
E 7
D 2
		printf("usage: chown uid file ...\n");
E 2
I 2
D 4
		printf("usage: chown -f uid file ...\n");
E 2
		exit(4);
E 4
I 4
D 5
		fprintf(stderr, "usage: chown [-fr] uid[.gid] file ...\n");
E 5
I 5
		fprintf(stderr, "usage: chown [-fR] owner[.group] file ...\n");
E 5
		exit(-1);
E 13
I 13
D 21
	else {
		uid = -1;
E 21
I 21
	else 
E 27
I 27
	} else 
E 27
E 21
D 23
		setgid(*argv);
E 23
I 23
		a_gid(*argv);
E 23
E 13
E 4
D 21
	}
E 21
I 8
D 13
	gid = -1;
E 8
I 2
D 4
	if (strcmp(argv[1], "-f") == 0) {
		fflag++;
E 4
I 4
D 7
	if (*argv[1] == '-') {
		for (flags = argv[1]; *flags; ++flags)
			switch (*flags) {
			  case '-':			break;
			  case 'f': 	fflag++;	break;
			  case 'R':	rflag++;	break;
			  default:
				printf("chown: unknown option: %c\n", *flags);
				exit(-2);
			}
E 4
		argv++, argc--;
E 7
I 7
	group = index(argv[0], '.');
	if (group != NULL) {
		*group++ = '\0';
		if (!isnumber(group)) {
			if ((grp = getgrnam(group)) == NULL)
				fatal(255, "unknown group: %s",group);
			gid = grp -> gr_gid;
D 8
			endgrent();
		} else
E 8
I 8
			(void) endgrent();
		} else if (*group != '\0')
E 8
			gid = atoi(group);
E 13
I 13

D 17
	while (*++argv)
E 17
I 17
D 21
	while (*++argv) {
		if (reset = index(*argv, '/'))
			(void)getwd(curpath);
E 17
		change(*argv);
I 17
		if (reset && chdir(curpath)) {
			if (fflag)
				exit(0);
			err(curpath);
			exit(-1);
E 21
I 21
D 24
	if (rflag) {
D 22
		if (!(fts = ftsopen(++argv, FTS_NOSTAT|FTS_PHYSICAL, 0))) {
E 22
I 22
		if (!(fts = fts_open(++argv, FTS_NOSTAT|FTS_PHYSICAL, 0))) {
E 22
			(void)fprintf(stderr,
			    "%s: %s.\n", myname, strerror(errno));
			exit(1);
E 21
		}
I 21
D 22
		while (p = ftsread(fts)) {
E 22
I 22
		while (p = fts_read(fts)) {
E 22
			if (p->fts_info == FTS_D)
E 24
I 24
D 27
	if (!(ftsp = fts_open(++argv, fts_options, 0))) {
		(void)fprintf(stderr,
		    "%s: %s.\n", myname, strerror(errno));
		exit(1);
	}
	while (p = fts_read(ftsp)) {
		if (p->fts_info == FTS_D) {
			if (rflag)
E 27
I 27
	if ((ftsp = fts_open(++argv, fts_options, 0)) == NULL)
		err(1, NULL);

	for (rval = 0; (p = fts_read(ftsp)) != NULL;) {
		switch (p->fts_info) {
		case FTS_D:
			if (Rflag)		/* Change it at FTS_DP. */
E 27
E 24
				continue;
D 24
			if (p->fts_info == FTS_ERR) {
				error(p->fts_path);
				continue;
			}
			if (chown(p->fts_accpath, uid, gid) && !fflag)
				chownerr(p->fts_path);
E 24
I 24
D 27
			else
				fts_set(ftsp, p, FTS_SKIP);
E 24
		}
I 25
		if (p->fts_info == FTS_SL &&
		    !(hflag || (Hflag && p->fts_level == FTS_ROOTLEVEL)))
E 27
I 27
			fts_set(ftsp, p, FTS_SKIP);
			break;
D 28
		case FTS_DC:
			warnx("tree cycle: %s", p->fts_path);
			rval = 1;
E 28
I 28
D 30
		case FTS_DC:			/* Ignore. */
E 28
E 27
			continue;
E 30
E 25
D 24
		exit(retval);
E 24
I 24
D 27
		if (p->fts_info == FTS_ERR) {
			error(p->fts_path);
E 27
I 27
D 28
		case FTS_ERR:
E 28
I 28
		case FTS_DNR:			/* Warn, chown, continue. */
E 28
D 32
			errno = p->fts_errno;
			warn("%s", p->fts_path);
E 32
I 32
			warnx("%s: %s", p->fts_path, strerror(p->fts_errno));
E 32
			rval = 1;
I 28
			break;
		case FTS_ERR:			/* Warn, continue. */
I 31
		case FTS_NS:
E 31
D 32
			errno = p->fts_errno;
			warn("%s", p->fts_path);
E 32
I 32
			warnx("%s: %s", p->fts_path, strerror(p->fts_errno));
E 32
			rval = 1;
E 28
E 27
			continue;
I 27
D 28
		case FTS_SL:
E 28
I 28
		case FTS_SL:			/* Ignore. */
E 28
		case FTS_SLNONE:
			/*
			 * The only symlinks that end up here are ones that
			 * don't point to anything and ones that we found
			 * doing a physical walk.
			 */
			continue;
I 28
		default:
			break;
E 28
E 27
		}
D 27
		if (chown(p->fts_accpath, uid, gid) && !fflag)
E 27
I 27
		if (chown(p->fts_accpath, uid, gid) && !fflag) {
E 27
			chownerr(p->fts_path);
I 27
			rval = 1;
		}
E 27
E 24
E 21
	}
I 29
	if (errno)
		err(1, "fts_read");
E 29
I 21
D 24
	while (*++argv)
		if (chown(*argv, uid, gid) && !fflag)
			chownerr(*argv);
E 24
E 21
E 17
D 27
	exit(retval);
E 27
I 27
	exit(rval);
E 27
}

I 27
void
E 27
D 19
static
E 19
D 23
setgid(s)
E 23
I 23
a_gid(s)
E 23
D 27
	register char *s;
E 27
I 27
	char *s;
E 27
{
D 14
	register int ngroups;
E 14
D 23
	struct group *gr, *getgrnam();
E 23
I 23
	struct group *gr;
E 23
D 14
	int groups[NGROUPS];
	char *beg;
E 14

D 27
	if (!*s) {
		gid = -1;			/* argument was "uid." */
E 27
I 27
	if (*s == '\0')			/* Argument was "uid[:.]". */
E 27
		return;
E 13
E 7
D 27
	}
E 27
E 2
D 4
	if(isnumber(argv[1])) {
E 4
I 4
D 7

	for (group = argv[1]; *group ; group++) {
		if (*group == '.') {
			*group = '\0';
			group++;
			if (isnumber(group))
				gid = atoi(group);
			else {
				if ((grp=getgrnam(group)) == NULL) {
					printf("unknown group: %s\n",group);
					exit(-3);
				}
				gid = grp -> gr_gid;
				endgrent();
			}
			goto owner;
		}
	}
	group = NULL;
	
owner:
	if (isnumber(argv[1])) {
E 4
		uid = atoi(argv[1]);
D 4
		goto cho;
E 4
I 4
	} else {
		if ((pwd=getpwnam(argv[1])) == NULL) {
			printf("unknown user id: %s\n",argv[1]);
			exit(-4);
		}
E 7
I 7
D 13
	if (!isnumber(argv[0])) {
		if ((pwd = getpwnam(argv[0])) == NULL)
			fatal(255, "unknown user id: %s",argv[0]);
E 7
		uid = pwd->pw_uid;
E 4
D 7
	}
D 4
	if((pwd=getpwnam(argv[1])) == NULL) {
		printf("unknown user id: %s\n",argv[1]);
		exit(4);
	}
	uid = pwd->pw_uid;
E 4

D 4
cho:
E 4
	for(c=2; c<argc; c++) {
D 3
		stat(argv[c], &stbuf);
E 3
I 3
D 4
		lstat(argv[c], &stbuf);
E 3
D 2
		if(chown(argv[c], uid, stbuf.st_gid) < 0) {
E 2
I 2
		if(chown(argv[c], uid, stbuf.st_gid) < 0 && !fflag) {
E 4
I 4
		if (lstat(argv[c], &stbuf) < 0) {
			printf("chown: couldn't stat %s\n", argv[c]);
			exit(-5);
E 7
I 7
	} else
		uid = atoi(argv[0]);
	for (c = 1; c < argc; c++) {
		/* do stat for directory arguments */
D 9
		if (stat(argv[c], &stbuf) < 0) {
			status += error("couldn't access %s", argv[c]);
E 9
I 9
		if (lstat(argv[c], &stbuf) < 0) {
			status += Perror(argv[c]);
E 9
			continue;
E 13
I 13
D 14
	for (beg = s; *s && isdigit(*s); ++s);
E 14
I 14
D 23
	for (gname = s; *s && isdigit(*s); ++s);
E 14
	if (!*s)
D 14
		gid = atoi(beg);
E 14
I 14
		gid = atoi(gname);
E 23
I 23
	gname = s;
D 27
	if (gr = getgrnam(s))
		gid = gr->gr_gid;
E 23
E 14
	else {
D 14
		if (!(gr = getgrnam(beg))) {
E 14
I 14
D 23
		if (!(gr = getgrnam(gname))) {
E 23
I 23
		for (; *s && isdigit(*s); ++s);
		if (!*s)
			gid = atoi(gname);
		else {
E 23
E 14
D 21
			if (fflag)
				exit(0);
E 21
D 18
			fprintf(stderr, "%s: unknown group id: %s\n",
E 18
I 18
			(void)fprintf(stderr, "%s: unknown group id: %s\n",
E 18
D 14
			    myname, beg);
E 14
I 14
			    myname, gname);
E 14
D 21
			exit(-1);
E 21
I 21
			exit(1);
E 21
E 13
E 7
		}
D 8
		if (group == NULL)
			gid = stbuf.st_gid;
E 8
D 7
		if (rflag && stbuf.st_mode & S_IFDIR)
			status += chownr(argv[c], group, uid, gid);
		else if (chown(argv[c], uid, gid) < 0 && !fflag) {
E 4
E 2
			perror(argv[c]);
D 4
			status = 1;
E 4
I 4
			status++;
E 7
I 7
D 10
		if (rflag && stbuf.st_mode&S_IFDIR) {
E 10
I 10
D 11
		if (rflag && (stbuf.st_mode&S_IFMT) == S_IFDIR) {
E 11
I 11
D 13
		if (rflag && ((stbuf.st_mode&S_IFMT) == S_IFDIR)) {
E 11
E 10
D 8
			status += chownr(argv[c], group != NULL, uid, gid);
E 8
I 8
			status += chownr(argv[c], uid, gid);
E 8
			continue;
E 7
E 4
		}
I 7
		if (chown(argv[c], uid, gid)) {
D 9
			status += error("couldn't change %s", argv[c]);
E 9
I 9
			status += Perror(argv[c]);
E 9
			continue;
		}
E 13
I 13
D 23
		gid = gr->gr_gid;
E 23
E 13
E 7
	}
E 27
I 27
	gid = ((gr = getgrnam(s)) == NULL) ? id(s, "group") : gr->gr_gid;
E 27
D 13
	exit(status);
E 13
I 13
D 14
	/* check now; the kernel returns "EPERM" on later failure */
	ngroups = getgroups(NGROUPS, groups);
	while (--ngroups >= 0 && gid != groups[ngroups]);
	if (ngroups < 0) {
		if (fflag)
			exit(0);
		fprintf(stderr, "%s: you are not a member of group %s.\n",
		    myname, beg);
		exit(-1);
	}
E 14
E 13
}

I 27
void
E 27
D 13
isnumber(s)
D 7
char *s;
E 7
I 7
	char *s;
E 13
I 13
D 19
static
E 19
D 23
setuid(s)
E 23
I 23
a_uid(s)
E 23
D 27
	register char *s;
E 27
I 27
	char *s;
E 27
E 13
E 7
{
D 13
	register c;
E 13
I 13
D 23
	struct passwd *pwd, *getpwnam();
	char *beg;
E 23
I 23
	struct passwd *pw;
D 27
	char *uname;
E 27
E 23
E 13

I 12
D 13
	if (*s == '\0')
		return 0;
E 12
	while(c = *s++)
D 7
		if(!isdigit(c))
			return(0);
	return(1);
E 7
I 7
		if (!isdigit(c))
			return (0);
	return (1);
E 13
I 13
D 27
	if (!*s) {
		uid = -1;			/* argument was ".gid" */
E 27
I 27
	if (*s == '\0')			/* Argument was "[:.]gid". */
E 27
		return;
D 27
	}
D 23
	for (beg = s; *s && isdigit(*s); ++s);
	if (!*s)
		uid = atoi(beg);
E 23
I 23
	if (pw = getpwnam(s))
		uid = pw->pw_uid;
E 23
	else {
D 23
		if (!(pwd = getpwnam(beg))) {
E 23
I 23
		for (uname = s; *s && isdigit(*s); ++s);
		if (!*s)
			uid = atoi(uname);
		else {
E 23
D 21
			if (fflag)
				exit(0);
E 21
D 18
			fprintf(stderr, "chown: unknown user id: %s\n", beg);
E 18
I 18
			(void)fprintf(stderr,
D 23
			    "chown: unknown user id: %s\n", beg);
E 23
I 23
			    "chown: unknown user id: %s\n", uname);
E 23
E 18
D 21
			exit(-1);
E 21
I 21
			exit(1);
E 21
		}
D 23
		uid = pwd->pw_uid;
E 23
	}
E 27
I 27
	uid = ((pw = getpwnam(s)) == NULL) ? id(s, "user") : pw->pw_uid;
E 27
E 13
E 7
I 4
}

I 27
u_long
id(name, type)
	char *name, *type;
{
	u_long val;
	char *ep;

	/*
	 * XXX
	 * We know that uid_t's and gid_t's are unsigned longs.
	 */
	errno = 0;
	val = strtoul(name, &ep, 10);
	if (errno)
		err(1, "%s", name);
	if (*ep != '\0')
		errx(1, "%s: illegal %s name", name, type);
	return (val);
}

void
E 27
D 7
chownr(dir, dogrp, uid, gid_save)
	char	*dir;
E 7
I 7
D 8
chownr(dir, dogrp, uid, ogid)
E 8
I 8
D 13
chownr(dir, uid, gid)
E 8
	char *dir;
E 13
I 13
D 19
static
E 19
D 21
change(file)
	char *file;
E 13
E 7
{
D 7
	register DIR		*dirp;
	register struct direct	*dp;
	register struct stat	st;
	char			savedir[1024];
	int			gid;
E 7
I 7
	register DIR *dirp;
D 18
	register struct direct *dp;
E 18
I 18
	register struct dirent *dp;
E 18
D 8
	register struct stat st;
E 8
I 8
D 13
	struct stat st;
E 8
	char savedir[1024];
D 8
	int ecode, gid;
E 8
I 8
	int ecode;
	extern char *getwd();
E 13
I 13
	struct stat buf;
E 13
E 8
E 7

D 7
	if (getwd(savedir) == 0) {
		fprintf(stderr, "chown: %s\n", savedir);
		exit(-6);
	}
	if (chown(dir, uid, gid_save) < 0 && !fflag) {
		perror(dir);
		return(1);
	}

	chdir(dir);
	if ((dirp = opendir(".")) == NULL) {
		perror(dir);
		exit(status);
	}
E 7
I 7
D 8
	if (getwd(savedir) == 0)
E 8
I 8
D 13
	if (getwd(savedir) == (char *)0)
E 8
		fatal(255, "%s", savedir);
	/*
	 * Change what we are given before doing it's contents.
	 */
D 8
	if (chown(dir, uid, ogid) < 0 && error("can't change %s", dir))
E 8
I 8
D 9
	if (chown(dir, uid, gid) < 0 && error("can't change %s", dir))
E 9
I 9
	if (chown(dir, uid, gid) < 0 && Perror(dir))
E 9
E 8
		return (1);
D 9
	if (chdir(dir) < 0)
		return (Perror(dir));
	if ((dirp = opendir(".")) == NULL)
		return (Perror(dir));
E 9
I 9
	if (chdir(dir) < 0) {
		Perror(dir);
		return (1);
E 13
I 13
D 14
	if (lstat(file, &buf) || chown(file, uid, gid)) {
E 14
I 14
	if (chown(file, uid, gid)) {
D 15
		static int euid = -1, ngroups = -1;

		if (uid != -1 && euid == -1 && (euid = geteuid())) {
			if (fflag)
				exit(0);
			err(file);
			exit(-1);
		}
		/* check group membership; kernel just returns EPERM */
		if (gid != -1 && ngroups == -1) {
			int groups[NGROUPS];

			ngroups = getgroups(NGROUPS, groups);
			while (--ngroups >= 0 && gid != groups[ngroups]);
			if (ngroups < 0) {
				if (fflag)
					exit(0);
				fprintf(stderr,
				    "%s: you are not a member of group %s.\n",
				    myname, gname);
				exit(-1);
			}
		}
E 14
		err(file);
E 15
I 15
		chownerr(file);
E 15
		return;
E 13
	}
D 13
	if ((dirp = opendir(".")) == NULL) {
		Perror(dir);
		return (1);
	}
E 9
E 7
	dp = readdir(dirp);
	dp = readdir(dirp); /* read "." and ".." */
D 7

E 7
I 7
	ecode = 0;
E 7
	for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp)) {
D 7
		if (lstat(dp->d_name, &st) < 0) {
			fprintf(stderr, "chown: can't access %s\n", dp->d_name);
			return(1);
E 7
I 7
D 9
		if (stat(dp->d_name, &st) < 0) {
			ecode = error("can't access %s", dp->d_name);
E 9
I 9
		if (lstat(dp->d_name, &st) < 0) {
			ecode = Perror(dp->d_name);
E 9
			if (ecode)
				break;
			continue;
E 13
I 13
D 14
	if (rflag && ((buf.st_mode & S_IFMT) == S_IFDIR)) {
E 14
I 14
	if (!rflag)
		return;
	if (lstat(file, &buf)) {
		err(file);
		return;
	}
	if ((buf.st_mode & S_IFMT) == S_IFDIR) {
E 14
		if (chdir(file) < 0 || !(dirp = opendir("."))) {
			err(file);
			return;
E 13
E 7
		}
D 8
		if (dogrp)
D 7
			gid = gid_save;
E 7
I 7
			gid = ogid;
E 7
		else
			gid = st.st_gid;
E 8
D 7
		if (st.st_mode & S_IFDIR)
			chownr(dp->d_name, dogrp, uid, gid);
		else
			if (chown(dp->d_name, uid, gid) < 0 && !fflag) {
				perror(dp->d_name);
				return(1);
			}
E 7
I 7
D 10
		if (st.st_mode&S_IFDIR) {
E 10
I 10
D 11
		if ((stbuf.st_mode&S_IFMT) == S_IFDIR) {
E 11
I 11
D 13
		if ((st.st_mode&S_IFMT) == S_IFDIR) {
E 11
E 10
D 8
			ecode = chownr(dp->d_name, dogrp, uid, gid);
E 8
I 8
			ecode = chownr(dp->d_name, uid, gid);
E 8
			if (ecode)
				break;
			continue;
E 13
I 13
		for (dp = readdir(dirp); dp; dp = readdir(dirp)) {
			if (dp->d_name[0] == '.' && (!dp->d_name[1] ||
			    dp->d_name[1] == '.' && !dp->d_name[2]))
				continue;
			change(dp->d_name);
E 13
		}
D 13
		if (chown(dp->d_name, uid, gid) < 0 &&
D 9
		    (ecode = error("can't change %s", dp->d_name)))
E 9
I 9
		    (ecode = Perror(dp->d_name)))
E 9
			break;
E 13
I 13
		closedir(dirp);
		if (chdir("..")) {
			err("..");
			exit(fflag ? 0 : -1);
		}
E 13
E 7
	}
I 15
}

E 21
D 19
static
E 19
chownerr(file)
	char *file;
{
I 18
D 21
	extern int errno;
E 21
E 18
	static int euid = -1, ngroups = -1;
I 27
	int groups[NGROUPS];
E 27

D 27
	/* check for chown without being root */
D 18
	if (uid != -1 && euid == -1 && (euid = geteuid())) {
E 18
I 18
	if (errno != EPERM || uid != -1 && euid == -1 && (euid = geteuid())) {
E 27
I 27
	/* Check for chown without being root. */
	if (errno != EPERM ||
	    uid != -1 && euid == -1 && (euid = geteuid()) != 0) {
E 27
E 18
		if (fflag)
			exit(0);
D 21
		err(file);
		exit(-1);
E 21
I 21
D 27
		error(file);
		exit(1);
E 27
I 27
		err(1, "%s", file);
E 27
E 21
	}
D 27
	/* check group membership; kernel just returns EPERM */
	if (gid != -1 && ngroups == -1) {
		int groups[NGROUPS];
E 27

I 27
	/* Check group membership; kernel just returns EPERM. */
	if (gid != -1 && ngroups == -1) {
E 27
		ngroups = getgroups(NGROUPS, groups);
		while (--ngroups >= 0 && gid != groups[ngroups]);
		if (ngroups < 0) {
			if (fflag)
				exit(0);
D 18
			fprintf(stderr,
E 18
I 18
D 27
			(void)fprintf(stderr,
E 18
			    "%s: you are not a member of group %s.\n",
			    myname, gname);
D 21
			exit(-1);
E 21
I 21
			exit(1);
E 27
I 27
			errx(1, "you are not a member of group %s", gname);
E 27
E 21
		}
	}
D 21
	err(file);
E 21
I 21
D 27
	if (!fflag)
		error(file);
E 21
E 15
D 13
	closedir(dirp);
D 7
	chdir(savedir);
	return(0);
E 7
I 7
	if (chdir(savedir) < 0)
		fatal(255, "can't change back to %s", savedir);
	return (ecode);
E 13
}
E 27

D 13
error(fmt, a)
	char *fmt, *a;
E 13
I 13
D 19
static
E 19
D 21
err(s)
	char *s;
E 21
I 21
D 27
error(name)
	char *name;
E 21
E 13
{
I 17
D 21
	extern int errno;
	char *strerror();

E 17
D 13

	if (!fflag) {
		fprintf(stderr, "chown: ");
		fprintf(stderr, fmt, a);
		putc('\n', stderr);
	}
	return (!fflag);
E 13
I 13
	if (fflag)
		return;
D 14
	fputs(ischown ? "chown: " : "chgrp: ", stderr);
E 14
I 14
D 17
	fprintf(stderr, "%s: ", myname);
E 14
	perror(s);
E 17
I 17
D 18
	fprintf(stderr, "%s: %s: %s", myname, s, strerror(errno));
E 18
I 18
	(void)fprintf(stderr, "%s: %s: %s\n", myname, s, strerror(errno));
E 18
E 17
	retval = -1;
E 21
I 21
	(void)fprintf(stderr, "%s: %s: %s\n", myname, name, strerror(errno));
	retval = 1;
E 27
I 27
	if (!fflag) 
		warn("%s", file);
E 27
E 21
E 13
}

I 27
void
E 27
D 13
fatal(status, fmt, a)
	int status;
	char *fmt, *a;
E 13
I 13
D 19
static
E 19
usage()
E 13
{
D 13

	fflag = 0;
	(void) error(fmt, a);
	exit(status);
}

Perror(s)
	char *s;
{

D 9
	fprintf(stderr, "chown: ");
	perror(s);
	return (1);
E 9
I 9
	if (!fflag) {
		fprintf(stderr, "chown: ");
		perror(s);
	}
	return (!fflag);
E 13
I 13
D 18
	fprintf(stderr, "usage: %s [-Rf] %s file ...\n", myname,
E 18
I 18
D 25
	(void)fprintf(stderr, "usage: %s [-Rf] %s file ...\n", myname,
E 25
I 25
D 27
	(void)fprintf(stderr, "usage: %s [-HRfh] %s file ...\n", myname,
E 25
E 18
D 21
	    ischown ? "owner[.group]" : "group");
	exit(-1);
E 21
I 21
	    ischown ? "[owner][:group]" : "group");
E 27
I 27
	(void)fprintf(stderr,
	    "usage: %s [-R [-H | -L | -P]] [-f] %s file ...\n",
	    myname, ischown ? "[owner][:group]" : "group");
E 27
	exit(1);
E 21
E 13
E 9
E 7
E 4
}
E 1
