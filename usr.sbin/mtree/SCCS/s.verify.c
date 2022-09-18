h65197
s 00002/00002/00174
d D 8.1 93/06/06 14:03:24 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00173
d D 5.12 92/07/06 14:10:10 bostic 12 11
c fnmatch has its own include file, and the sense of it changed
e
s 00003/00005/00172
d D 5.11 92/04/17 17:22:17 bostic 11 10
c do comparison on ignored node, just skip everything beneath it
e
s 00039/00023/00138
d D 5.10 91/12/11 17:56:19 bostic 10 9
c version 2; add cksum, make keywords flexible, new output format
e
s 00002/00012/00159
d D 5.9 91/03/12 08:56:38 bostic 9 8
c fts(3) now sets errno for DNR, NS; FTS_DNX no longer returned
e
s 00006/00006/00165
d D 5.8 90/11/14 18:04:09 bostic 8 7
c change fts routine names
e
s 00013/00008/00158
d D 5.7 90/07/01 15:27:31 trent 7 6
c add depth checking (fts versus spec file)
e
s 00001/00000/00165
d D 5.6 90/06/25 10:44:45 bostic 6 5
c do ftsclose, otherwise may be in wrong directory
e
s 00004/00001/00161
d D 5.5 90/06/25 10:33:47 bostic 5 4
c ftsopen now only takes argv structure
e
s 00014/00014/00148
d D 5.4 90/05/25 12:19:32 bostic 4 3
c fold INFO and ENTRY structures together into NODE structure
e
s 00004/00001/00158
d D 5.3 90/05/25 10:43:35 bostic 3 2
c implement the magic characters in specification file names
e
s 00107/00119/00052
d D 5.2 90/05/25 10:30:47 bostic 2 1
c integrate with fts(3)
e
s 00171/00000/00000
d D 5.1 90/05/24 10:19:29 bostic 1 0
c initial checkpoint before making work with fts(3)
c date and time created 90/05/24 10:19:29 by bostic
e
u
U
t
T
I 1
/*-
D 13
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 2
#include <sys/types.h>
E 2
I 2
#include <sys/param.h>
E 2
#include <sys/stat.h>
D 2
#include <errno.h>
E 2
#include <dirent.h>
I 2
#include <fts.h>
I 12
#include <fnmatch.h>
E 12
I 3
#include <unistd.h>
E 3
#include <errno.h>
E 2
#include <stdio.h>
#include "mtree.h"
I 10
#include "extern.h"
E 10

D 4
extern ENTRY *root;
E 4
I 4
D 10
extern NODE *root;
E 10
I 10
extern int crc_total, ftsoptions;
extern int dflag, eflag, rflag, sflag, uflag;
extern char fullpath[MAXPATHLEN];
E 10
E 4
D 2
extern char path[];
E 2

I 10
static NODE *root;
E 10
D 2
static dev_t device;
E 2
I 2
static char path[MAXPATHLEN];
E 2

I 10
static void	miss __P((NODE *, char *));
static int	vwalk __P((void));

int
E 10
verify()
{
D 2
	extern int xflag;
	struct stat sbuf;

	if (xflag) {
		if (lstat(".", &sbuf)) {
			(void)fprintf(stderr, "mtree: root: %s\n",
			    strerror(errno));
			exit(1);
		}
		device = sbuf.st_dev;
	}
	vwalk(root, path + 1);
	miss(root, path + 1);
E 2
I 2
D 10
	vwalk();
E 10
I 10
	int rval;

	root = spec();
	rval = vwalk();
E 10
	miss(root, path);
I 10
	return (rval);
E 10
E 2
}

I 10
static int
E 10
D 2
static
vwalk(level, tail)
	register ENTRY *level;
	register char *tail;
E 2
I 2
vwalk()
E 2
{
D 2
	extern int dflag, eflag, rflag, xflag;
	register ENTRY *ep;
	register DIR *dirp;
	register struct dirent *dp;
	struct stat sbuf;
E 2
I 2
D 10
	extern int ftsoptions, dflag, eflag, rflag;
E 10
	register FTS *t;
	register FTSENT *p;
D 4
	register ENTRY *ep, *level;
E 4
I 4
	register NODE *ep, *level;
I 10
	int ftsdepth, specdepth, rval;
E 10
I 5
	char *argv[2];
I 7
D 10
	int ftsdepth = 0, specdepth = 0;
E 10
E 7
E 5
E 4
E 2

D 2
	if (!(dirp = opendir("."))) {
		(void)fprintf(stderr, "mtree: %s: %s\n",
		    level == root ? "root" : path, strerror(errno));
E 2
I 2
D 5
	if (!(t = ftsopen(".", ftsoptions, (int (*)())NULL))) {
E 5
I 5
	argv[0] = ".";
D 10
	argv[1] = (char *)NULL;
D 8
	if (!(t = ftsopen(argv, ftsoptions, (int (*)())NULL))) {
E 8
I 8
	if (!(t = fts_open(argv, ftsoptions, (int (*)())NULL))) {
E 8
E 5
		(void)fprintf(stderr,
D 8
		    "mtree: ftsopen: %s.\n", strerror(errno));
E 8
I 8
		    "mtree: fts_open: %s.\n", strerror(errno));
E 8
E 2
		exit(1);
	}
E 10
I 10
	argv[1] = NULL;
	if ((t = fts_open(argv, ftsoptions, NULL)) == NULL)
		err("fts_open: %s", strerror(errno));
E 10
D 2
	*tail++ = '/';
	while ((dp = readdir(dirp))) {
		if (dp->d_name[0] == '.' &&
		    (!dp->d_name[1] || dp->d_name[1] == '.' && !dp->d_name[2]))
E 2
I 2
	level = root;
I 10
	ftsdepth = specdepth = rval = 0;
E 10
D 8
	while (p = ftsread(t)) {
E 8
I 8
	while (p = fts_read(t)) {
E 8
		switch(p->fts_info) {
		case FTS_D:
D 10
			if (!strcmp(p->fts_name, "."))
				continue;
I 7
			ftsdepth++; 
E 10
I 10
			++ftsdepth; 
E 10
E 7
			break;
D 9
		case FTS_DC:
			(void)fprintf(stderr,
			    "mtree: directory cycle: %s.\n", RP(p));
E 2
			continue;
D 2
		bcopy(dp->d_name, tail, dp->d_namlen + 1);
		for (ep = level; ep; ep = ep->next)
			if (!strcmp(ep->name, dp->d_name))
				break;
		if (ep && ep->flags&F_IGN) {
			ep->flags |= F_VISIT;
E 2
I 2
		case FTS_DNR:
D 7
			(void)fprintf(stderr,
			    "mtree: %s: unable to read.\n", RP(p));
E 2
			continue;
E 7
I 2
		case FTS_DNX:
			(void)fprintf(stderr,
D 7
			    "mtree: %s: unable to search.\n", RP(p));
			continue;
E 7
I 7
			    "mtree: %s: unable to read or search.\n", RP(p));
E 9
E 7
		case FTS_DP:
D 7
			for (level = level->parent; level->prev;
			    level = level->prev);
E 7
I 7
D 10
			ftsdepth--; 
E 10
I 10
			--ftsdepth; 
E 10
			if (specdepth > ftsdepth) {
				for (level = level->parent; level->prev;
				      level = level->prev);  
D 10
				specdepth--;
E 10
I 10
				--specdepth;
E 10
			}
E 7
			continue;
I 9
		case FTS_DNR:
E 9
		case FTS_ERR:
I 9
		case FTS_NS:
E 9
D 10
			(void)fprintf(stderr, "mtree: %s: %s.\n",
E 10
I 10
			(void)fprintf(stderr, "mtree: %s: %s\n",
E 10
			    RP(p), strerror(errno));
D 9
			continue;
		case FTS_NS:
			(void)fprintf(stderr,
			    "mtree: can't stat: %s.\n", RP(p));
E 9
			continue;
		default:
			if (dflag)
				continue;
E 2
		}
D 2
		if (lstat(dp->d_name, &sbuf)) {
			(void)fprintf(stderr, "mtree: %s: %s\n",
			    path + 2, strerror(errno));
			exit(1);
		}
		if (!dflag || S_ISDIR(sbuf.st_mode))
			if (ep) {
				compare(ep->name, &ep->info, &sbuf);
E 2
I 2

		for (ep = level; ep; ep = ep->next)
D 3
			if (!strcmp(ep->name, p->fts_name)) {
E 3
I 3
D 12
			if (ep->flags & F_MAGIC && fnmatch(ep->name,
			    p->fts_name, FNM_PATHNAME|FNM_QUOTE) ||
E 12
I 12
			if (ep->flags & F_MAGIC &&
			    !fnmatch(ep->name, p->fts_name, FNM_PATHNAME) ||
E 12
			    !strcmp(ep->name, p->fts_name)) {
E 3
E 2
				ep->flags |= F_VISIT;
D 2
			} else if (!eflag) {
				(void)printf("extra: %s%s",
				    path + 2, rflag ? "" : "\n");
				if (rflag)
					if (unlink(path))
					    (void)printf(", not removed: %s\n",
						strerror(errno));
					else
					    (void)printf(", removed\n");
E 2
I 2
D 4
				if (ep->info.flags&F_IGN) {
E 4
I 4
D 11
				if (ep->flags & F_IGN) {
E 4
D 8
					(void)ftsset(t, p, FTS_SKIP);
E 8
I 8
					(void)fts_set(t, p, FTS_SKIP);
E 8
					continue;
				}
E 11
D 4
				compare(ep->name, &ep->info, p);
				if (ep->child && ep->info.type == F_DIR &&
E 4
I 4
D 10
				compare(ep->name, ep, p);
E 10
I 10
				if (compare(ep->name, ep, p))
					rval = MISMATCHEXIT;
E 10
D 11
				if (ep->child && ep->type == F_DIR &&
E 11
I 11
				if (ep->flags & F_IGN)
					(void)fts_set(t, p, FTS_SKIP);
				else if (ep->child && ep->type == F_DIR &&
E 11
E 4
D 7
				    p->fts_info == FTS_D)
E 7
I 7
				    p->fts_info == FTS_D) {
E 7
					level = ep->child;
I 7
D 10
					specdepth++;
E 10
I 10
					++specdepth;
E 10
				}
E 7
				break;
E 2
			}
I 7

E 7
D 2
		if (S_ISDIR(sbuf.st_mode) &&
		    (!xflag || device == sbuf.st_dev)) {
			if (chdir(dp->d_name)) {
				(void)fprintf(stderr, "mtree: %s: %s\n",
				    path + 2, strerror(errno));
				exit(1);
E 2
I 2
		if (ep)
			continue;
		if (!eflag) {
			(void)printf("extra: %s", RP(p));
			if (rflag) {
				if (unlink(p->fts_accpath)) {
					(void)printf(", not removed: %s",
					    strerror(errno));
				} else
					(void)printf(", removed");
E 2
			}
D 2
			vwalk(ep ? ep->child : ep, tail + dp->d_namlen);
			if (chdir("..")) {
				(void)fprintf(stderr, "mtree: ..: %s\n",
				    strerror(errno));
				exit(1);
			}
E 2
I 2
			(void)putchar('\n');
E 2
		}
I 2
D 8
		(void)ftsset(t, p, FTS_SKIP);
E 8
I 8
		(void)fts_set(t, p, FTS_SKIP);
E 8
E 2
	}
I 6
D 8
	(void)ftsclose(t);
E 8
I 8
	(void)fts_close(t);
I 10
	if (sflag)
		(void)fprintf(stderr,
		    "mtree: %s checksum: %lu\n", fullpath, crc_total);
	return (rval);
E 10
E 8
E 6
D 2
	(void)closedir(dirp);
E 2
}

I 10
static void
E 10
D 2
static
miss(level, tail)
	register ENTRY *level;
E 2
I 2
miss(p, tail)
D 4
	register ENTRY *p;
E 4
I 4
	register NODE *p;
E 4
E 2
	register char *tail;
{
D 10
	extern int dflag, uflag;
E 10
	register int create;
D 2
	register char *p;
E 2
I 2
	register char *tp;
E 2

D 2
	for (*tail++ = '/'; level; level = level->next) {
		if (level->info.type != F_DIR &&
			(dflag || level->flags&F_VISIT))
				continue;
		(void)strcpy(tail, level->name);
		if (!(level->flags&F_VISIT))
			(void)printf("missing: %s%s", path + 2,
			    uflag ? "" : "\n");
		if (level->info.type != F_DIR)
E 2
I 2
	for (; p; p = p->next) {
D 4
		if (p->info.type != F_DIR && (dflag || p->flags&F_VISIT))
E 4
I 4
		if (p->type != F_DIR && (dflag || p->flags & F_VISIT))
E 4
E 2
			continue;
I 2
		(void)strcpy(tail, p->name);
D 4
		if (!(p->flags&F_VISIT))
E 4
I 4
		if (!(p->flags & F_VISIT))
E 4
			(void)printf("missing: %s", path);
D 4
		if (p->info.type != F_DIR) {
E 4
I 4
		if (p->type != F_DIR) {
E 4
			putchar('\n');
			continue;
		}

E 2
		create = 0;
D 2
		if (uflag)
			if (mkdir(path, 0777))
				(void)printf(" (not created: %s)\n",
E 2
I 2
D 4
		if (!(p->flags&F_VISIT) && uflag)
E 4
I 4
		if (!(p->flags & F_VISIT) && uflag)
E 4
D 10
#define	MINBITS	(F_GROUP|F_MODE|F_OWNER)
D 4
			if ((p->info.flags & MINBITS) != MINBITS)
E 4
I 4
			if ((p->flags & MINBITS) != MINBITS)
E 4
				(void)printf(" (not created -- group, mode or owner not specified)");
E 10
I 10
			if (!(p->flags & (F_UID | F_UNAME)))
			    (void)printf(" (not created: user not specified)");
			else if (!(p->flags & (F_GID | F_GNAME)))
			    (void)printf(" (not created: group not specified)");
			else if (!(p->flags & F_MODE))
			    (void)printf(" (not created: mode not specified)");
E 10
			else if (mkdir(path, S_IRWXU))
				(void)printf(" (not created: %s)",
E 2
				    strerror(errno));
			else {
				create = 1;
D 2
				(void)printf(" (created)\n");
E 2
I 2
				(void)printf(" (created)");
E 2
			}
D 2
		for (p = tail; *p; ++p);
		miss(level->child, p);
		if (create) {
			*p = '\0';
			dirset(&level->info);
		}
	}
}
E 2

D 2
static
dirset(s1)
	register INFO *s1;
{
	register struct stat *s2;
	struct stat sbuf;
E 2
I 2
D 4
		if (!(p->flags&F_VISIT))
E 4
I 4
		if (!(p->flags & F_VISIT))
E 4
			(void)putchar('\n');
E 2

D 2
	if (stat(path, &sbuf)) {
		(void)fprintf(stderr,
		    "mtree: %s: %s\n", path, strerror(errno));
		return;
	}
	s2 = &sbuf;
E 2
I 2
		for (tp = tail; *tp; ++tp);
		*tp = '/';
		miss(p->child, tp + 1);
		*tp = '\0';
E 2

D 2
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
E 2
I 2
		if (!create)
			continue;
D 4
		if (chown(path, p->info.st_uid, p->info.st_gid)) {
E 4
I 4
		if (chown(path, p->st_uid, p->st_gid)) {
E 4
D 10
			(void)printf("%s: owner/group/mode not modified: %s\n",
E 10
I 10
			(void)printf("%s: user/group/mode not modified: %s\n",
E 10
			    path, strerror(errno));
			continue;
		}
D 4
		if (chmod(path, p->info.st_mode))
E 4
I 4
		if (chmod(path, p->st_mode))
E 4
			(void)printf("%s: permissions not set: %s\n",
			    path, strerror(errno));
	}
E 2
}
D 2

E 2
E 1
