h06952
s 00005/00005/00115
d D 8.1 93/06/06 14:03:13 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00118
d D 5.10 92/04/17 17:21:08 bostic 10 9
c add needvalue argument to parsekey
e
s 00047/00025/00073
d D 5.9 91/12/11 17:56:16 bostic 9 8
c version 2; add cksum, make keywords flexible, new output format
e
s 00000/00001/00098
d D 5.8 90/05/25 13:00:02 bostic 8 7
c don't make routines static, dbx doesn't like it
e
s 00001/00001/00098
d D 5.7 90/05/25 12:19:27 bostic 7 6
c fold INFO and ENTRY structures together into NODE structure
e
s 00015/00016/00084
d D 5.6 90/05/25 10:29:38 bostic 6 5
c delete xflag, path
e
s 00022/00162/00078
d D 5.5 90/05/22 12:58:42 bostic 5 4
c rearrange and make the world static
e
s 00001/00001/00239
d D 5.4 90/05/15 20:04:33 bostic 4 3
c string.h is ANSI C include file
e
s 00043/00018/00197
d D 5.3 89/09/06 13:47:20 bostic 3 2
c set owner/group/permissions on created directories
e
s 00002/00002/00213
d D 5.2 89/09/05 12:21:29 bostic 2 1
c use lstat, not stat, so we don't indirect through anything
e
s 00215/00000/00000
d D 5.1 89/09/04 16:24:53 bostic 1 0
c date and time created 89/09/04 16:24:53 by bostic
e
u
U
t
T
I 1
D 5
/*
E 5
I 5
/*-
E 5
D 11
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 */

#ifndef lint
D 11
char copyright[] =
D 5
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
E 5
I 5
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
E 5
 All rights reserved.\n";
E 11
I 11
static char copyright[] =
"%Z% Copyright (c) 1989, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 11
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
I 6
#include <sys/stat.h>
E 6
D 5
#include <sys/stat.h>
#include <dirent.h>
E 5
I 5
#include <errno.h>
I 9
#include <unistd.h>
E 9
E 5
#include <stdio.h>
I 6
#include <fts.h>
E 6
D 4
#include <strings.h>
E 4
I 4
D 5
#include <string.h>
E 5
E 4
#include "mtree.h"
I 9
#include "extern.h"
E 9

D 5
extern int errno;
E 5
D 7
ENTRY *root;
E 7
I 7
D 9
NODE *root;
E 7
D 5
dev_t device;
E 5
D 6
int cflag, dflag, eflag, rflag, uflag, xflag, exitval;
char path[MAXPATHLEN];
E 6
I 6
int exitval;
int cflag, dflag, eflag, rflag, uflag;
E 9
I 9
extern int crc_total;
E 9
E 6

I 9
int ftsoptions = FTS_PHYSICAL;
int cflag, dflag, eflag, rflag, sflag, uflag;
u_short keys;
char fullpath[MAXPATHLEN];

static void usage __P((void));

int
E 9
main(argc, argv)
	int argc;
D 9
	char **argv;
E 9
I 9
	char *argv[];
E 9
{
I 5
D 6
	extern int optind;
E 6
I 6
D 9
	extern int ftsoptions, optind;
E 9
I 9
	extern int optind;
E 9
E 6
E 5
	extern char *optarg;
D 5
	struct stat sbuf;
E 5
	int ch;
D 6
	char *p;
E 6
I 6
D 9
	char *dir;
E 9
I 9
	char *dir, *p;
E 9
E 6

D 5
	p = NULL;
E 5
I 5
D 6
	p = (char *)NULL;
E 6
I 6
D 9
	dir = (char *)NULL;
E 6
E 5
	while ((ch = getopt(argc, argv, "cdef:p:rux")) != EOF)
E 9
I 9
	dir = NULL;
	keys = KEYDEFAULT;
	while ((ch = getopt(argc, argv, "cdef:K:k:p:rs:ux")) != EOF)
E 9
		switch((char)ch) {
		case 'c':
			cflag = 1;
			break;
		case 'd':
			dflag = 1;
			break;
		case 'e':
			eflag = 1;
			break;
		case 'f':
D 9
			if (!(freopen(optarg, "r", stdin))) {
				(void)fprintf(stderr,
				    "mtree: can't read %s.\n", optarg);
				exit(1);
			}
E 9
I 9
			if (!(freopen(optarg, "r", stdin)))
				err("%s: %s", optarg, strerror(errno));
E 9
			break;
I 9
		case 'K':
			while ((p = strsep(&optarg, " \t,")) != NULL)
				if (*p != '\0')
D 10
					keys |= parsekey(p);
E 10
I 10
					keys |= parsekey(p, NULL);
E 10
			break;
		case 'k':
			keys = F_TYPE;
			while ((p = strsep(&optarg, " \t,")) != NULL)
				if (*p != '\0')
D 10
					keys |= parsekey(p);
E 10
I 10
					keys |= parsekey(p, NULL);
E 10
			break;
E 9
		case 'p':
D 6
			p = optarg;
E 6
I 6
			dir = optarg;
E 6
			break;
		case 'r':
			rflag = 1;
			break;
I 9
		case 's':
			sflag = 1;
			crc_total = ~strtol(optarg, &p, 0);
			if (*p)
				err("illegal seed value -- %s", optarg);
E 9
		case 'u':
			uflag = 1;
			break;
		case 'x':
D 6
			xflag = 1;
E 6
I 6
			ftsoptions |= FTS_XDEV;
E 6
			break;
		case '?':
		default:
D 5
			(void)fprintf(stderr,
			    "usage: mtree [-cderux] [-p path] [-f spec]\n");
			exit(1);
E 5
I 5
			usage();
E 5
		}
I 5
	argc -= optind;
I 9
	argv += optind;

E 9
	if (argc)
		usage();

E 5
D 9
	if (!cflag)
		spec();
E 9
I 9
	if (dir && chdir(dir))
		err("%s: %s", dir, strerror(errno));
E 9
I 5

E 5
D 6
	if (p && chdir(p)) {
E 6
I 6
D 9
	if (dir && chdir(dir)) {
E 6
		(void)fprintf(stderr,
D 6
		    "mtree: %s: %s\n", p, strerror(errno));
E 6
I 6
		    "mtree: %s: %s\n", dir, strerror(errno));
E 6
		exit(1);
	}
E 9
I 9
	if ((cflag || sflag) && !getwd(fullpath))
		err("%s", fullpath);
E 9
D 6
	path[0] = '.';
E 6
I 5

E 5
D 6
	if (cflag) {
D 5
		headers();
		cwalk((ENTRY *)NULL, path + 1);
		shostats();
		pwalk(root, 0);
	} else {
		if (xflag) {
D 2
			if (stat(".", &sbuf)) {
E 2
I 2
			if (lstat(".", &sbuf)) {
E 2
				(void)fprintf(stderr, "mtree: root: %s\n",
				    strerror(errno));
				exit(1);
			}
			device = sbuf.st_dev;
		}
		vwalk(root, path + 1);
		miss(root, path + 1);
E 5
I 5
		create();
		exit(0);
E 5
	}
I 5

	verify();
E 6
I 6
D 9
	if (cflag)
E 9
I 9
	if (cflag) {
E 9
		cwalk();
D 9
	else
		verify();
E 6
E 5
	exit(exitval);
E 9
I 9
		exit(0);
	}
	exit(verify());
E 9
}

I 9
static void
E 9
D 5
vwalk(level, tail)
	register ENTRY *level;
	register char *tail;
E 5
I 5
D 8
static
E 8
usage()
E 5
{
D 5
	register ENTRY *ep;
	register DIR *dirp;
	register struct dirent *dp;
	struct stat sbuf;

	if (!(dirp = opendir("."))) {
		(void)fprintf(stderr, "mtree: %s: %s\n",
		    level == root ? "root" : path, strerror(errno));
		exit(1);
	}
	*tail++ = '/';
	while ((dp = readdir(dirp))) {
		if (dp->d_name[0] == '.' &&
		    (!dp->d_name[1] || dp->d_name[1] == '.' && !dp->d_name[2]))
			continue;
		bcopy(dp->d_name, tail, dp->d_namlen + 1);
		for (ep = level; ep; ep = ep->next)
			if (!strcmp(ep->name, dp->d_name))
				break;
		if (ep && ep->flags&F_IGN) {
			ep->flags |= F_VISIT;
			continue;
		}
D 2
		if (stat(dp->d_name, &sbuf)) {
E 2
I 2
		if (lstat(dp->d_name, &sbuf)) {
E 2
			(void)fprintf(stderr, "mtree: %s: %s\n",
			    path + 2, strerror(errno));
			exit(1);
		}
		if (!dflag || S_ISDIR(sbuf.st_mode))
			if (ep) {
				compare(ep->name, &ep->info, &sbuf);
				ep->flags |= F_VISIT;
			} else if (!eflag) {
				(void)printf("extra: %s%s",
				    path + 2, rflag ? "" : "\n");
				if (rflag)
					if (unlink(path))
					    (void)printf(", not removed: %s\n",
						strerror(errno));
					else
					    (void)printf(", removed\n");
			}
		if (S_ISDIR(sbuf.st_mode) &&
		    (!xflag || device == sbuf.st_dev)) {
			if (chdir(dp->d_name)) {
				(void)fprintf(stderr, "mtree: %s: %s\n",
				    path + 2, strerror(errno));
				exit(1);
			}
			vwalk(ep ? ep->child : ep, tail + dp->d_namlen);
			if (chdir("..")) {
				(void)fprintf(stderr, "mtree: ..: %s\n",
				    strerror(errno));
				exit(1);
			}
		}
	}
	(void)closedir(dirp);
}

miss(level, tail)
	register ENTRY *level;
	register char *tail;
{
	register int create;
	register char *p;

	for (*tail++ = '/'; level; level = level->next) {
		if (level->info.type != F_DIR &&
			(dflag || level->flags&F_VISIT))
				continue;
		(void)strcpy(tail, level->name);
		if (!(level->flags&F_VISIT))
			(void)printf("missing: %s%s", path + 2,
			    uflag ? "" : "\n");
D 3
		if (level->info.type == F_DIR) {
			create = 0;
			if (uflag)
				if (mkdir(path, 0777))
					(void)printf(" (not created: %s)\n",
					    strerror(errno));
				else {
					create = 1;
					(void)printf(" (created)\n");
				}
			for (p = tail; *p; ++p);
			miss(level->child, p);
			if (create &&
			   level->info.flags&(F_DMODE|F_FMODE|F_MODE)) {
				*p = '\0';
				if (chmod(path, level->info.st_mode))
					(void)printf("%s: %s\n", path,
					    strerror(errno));
E 3
I 3
		if (level->info.type != F_DIR)
			continue;
		create = 0;
		if (uflag)
			if (mkdir(path, 0777))
				(void)printf(" (not created: %s)\n",
				    strerror(errno));
			else {
				create = 1;
				(void)printf(" (created)\n");
E 3
			}
I 3
		for (p = tail; *p; ++p);
		miss(level->child, p);
		if (create) {
			*p = '\0';
			dirset(&level->info);
E 3
		}
	}
I 3
}

dirset(s1)
	register INFO *s1;
{
	extern int errno;
	register struct stat *s2;
	struct stat sbuf;

	if (stat(path, &sbuf)) {
		(void)fprintf(stderr,
		    "mtree: %s: %s\n", path, strerror(errno));
		return;
	}
	s2 = &sbuf;

	if (s1->flags&F_MODE && s1->st_mode != (s2->st_mode&07777) &&
	    chmod(path, s1->st_mode))
		(void)printf("%s: permissions not set: %s\n",
		    path + 2, strerror(errno));
	if (s1->flags&F_OWNER && s1->st_uid != s2->st_uid &&
	    chown(path, s1->st_uid, -1))
		(void)printf("%s: owner not modified: %s\n",
		    path + 2, strerror(errno));
	if (s1->flags&F_GROUP && s1->st_gid != s2->st_gid &&
	    chown(path, -1, s1->st_gid))
		(void)printf("%s: group not modified: %s\n",
		    path + 2, strerror(errno));
E 5
I 5
	(void)fprintf(stderr,
D 9
	    "usage: mtree [-cderux] [-p path] [-f spec]\n");
E 9
I 9
"usage: mtree [-cderux] [-f spec] [-K key] [-k key] [-p path] [-s seed]\n");
E 9
	exit(1);
E 5
E 3
}
E 1
