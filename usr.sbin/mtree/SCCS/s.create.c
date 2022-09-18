h33387
s 00002/00002/00262
d D 8.1 93/06/06 14:02:57 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00262
d D 5.23 92/10/17 15:27:36 bostic 23 22
c snprintf returns printed length, not actual length
e
s 00001/00001/00264
d D 5.22 92/09/01 13:52:53 bostic 22 21
c sizes are quad's, not
e
s 00001/00001/00264
d D 5.21 92/07/15 12:07:29 bostic 21 20
c gname, not gid
e
s 00003/00001/00262
d D 5.20 92/06/18 17:51:43 bostic 20 19
c stat structure changes for quad/POSIX times
e
s 00001/00001/00262
d D 5.19 92/03/02 17:16:41 bostic 19 18
c fts_children now takes two arguments
e
s 00022/00022/00241
d D 5.18 92/01/27 16:02:25 bostic 18 17
c fts_statb -> fts_statp
e
s 00180/00125/00083
d D 5.17 91/12/11 17:56:13 bostic 17 16
c version 2; add cksum, make keywords flexible, new output format
e
s 00002/00016/00206
d D 5.16 91/03/12 08:56:40 bostic 16 15
c fts(3) now sets errno for DNR, NS; FTS_DNX no longer returned
e
s 00005/00005/00217
d D 5.15 90/11/14 18:04:07 bostic 15 14
c change fts routine names
e
s 00001/00000/00221
d D 5.14 90/06/25 10:44:43 bostic 14 13
c do ftsclose, otherwise may be in wrong directory
e
s 00004/00001/00217
d D 5.13 90/06/25 10:33:45 bostic 13 12
c ftsopen now only takes argv structure
e
s 00002/00000/00216
d D 5.12 90/05/25 16:50:46 bostic 12 11
c add modification time keyword
e
s 00000/00002/00216
d D 5.11 90/05/25 13:00:01 bostic 11 10
c don't make routines static, dbx doesn't like it
e
s 00001/00001/00217
d D 5.10 90/05/25 12:25:14 bostic 10 9
c don't comment empty lines
e
s 00002/00002/00216
d D 5.9 90/05/25 12:19:25 bostic 9 8
c fold INFO and ENTRY structures together into NODE structure
e
s 00001/00001/00217
d D 5.8 90/05/25 11:08:34 bostic 8 7
c make symbolic modes work, disallow commas in specification
e
s 00160/00246/00058
d D 5.7 90/05/25 10:29:20 bostic 7 6
c integrate with fts(3), do /set per directory
e
s 00031/00004/00273
d D 5.6 90/05/22 12:58:49 bostic 6 5
c rearrange and make the world static
e
s 00001/00001/00276
d D 5.5 90/05/15 20:04:32 bostic 5 4
c string.h is ANSI C include file
e
s 00001/00000/00276
d D 5.4 90/03/05 11:37:46 bostic 4 3
c fix dflag for ANSI C variable scoping
e
s 00009/00003/00267
d D 5.3 89/09/06 13:49:41 bostic 3 2
c if dflag, most common directory type is dir, so use it
e
s 00002/00002/00268
d D 5.2 89/09/05 12:21:12 bostic 2 1
c use lstat, not stat so we don't indirect through anything
e
s 00270/00000/00000
d D 5.1 89/09/04 16:24:50 bostic 1 0
c date and time created 89/09/04 16:24:50 by bostic
e
u
U
t
T
I 1
D 7
/*
E 7
I 7
/*-
E 7
D 24
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 24
I 24
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 24
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 6
#include <sys/types.h>
E 6
I 6
#include <sys/param.h>
E 6
#include <sys/stat.h>
I 6
D 7
#include <errno.h>
E 7
I 7
#include <time.h>
I 17
#include <fcntl.h>
E 17
#include <fts.h>
E 7
E 6
#include <dirent.h>
I 17
#include <grp.h>
#include <pwd.h>
E 17
I 7
#include <errno.h>
I 17
#include <unistd.h>
E 17
E 7
#include <stdio.h>
D 5
#include <strings.h>
E 5
I 5
D 6
#include <string.h>
E 6
E 5
#include "mtree.h"
I 17
#include "extern.h"
E 17

I 6
D 7
extern char path[];
extern ENTRY *root;
E 7
I 7
D 17
#define	LABEL \
	if (label++) \
		(void)putchar(' '); \
E 17
I 17
#define	INDENTNAMELEN	15
#define	MAXLINELEN	80
E 17
E 7

D 7
create()
E 7
I 7
D 17
int ftsoptions = FTS_PHYSICAL;
E 17
I 17
extern int crc_total, ftsoptions;
extern int dflag, sflag;
extern u_short keys;
extern char fullpath[MAXPATHLEN];
E 17

I 17
static gid_t gid;
static uid_t uid;
static mode_t mode;

static int	dsort __P((const FTSENT **, const FTSENT **));
static void	output __P((int *, const char *, ...));
static int	statd __P((FTS *, FTSENT *, uid_t *, gid_t *, mode_t *));
static void	statf __P((FTSENT *));

void
E 17
cwalk()
E 7
{
D 7
	time_t clock, time();
	char curp[MAXPATHLEN], *ctime(), *getlogin();
E 7
I 7
D 17
	extern int dflag;
E 17
	register FTS *t;
	register FTSENT *p;
D 17
	register int cnt, label, notset;
E 17
	time_t clock;
D 17
	uid_t uid;
	gid_t gid;
	mode_t mode;
	int tabs, dsort();
I 13
	char *argv[2];
E 13
	char curp[MAXPATHLEN], *inotype(), *getlogin(), *rlink();
E 17
I 17
	char *argv[2], host[MAXHOSTNAMELEN];
E 17
E 7

D 17
	if (!getwd(curp)) {
		(void)fprintf(stderr, "mtree: %s\n", curp);
		exit(1);
	}
E 17
	(void)time(&clock);
D 7
	(void)printf("#\n#\t%s\n#\tby: %s\n#\t%s#\n",
E 7
I 7
D 10
	(void)printf("#\n#\t  fs: %s\n#\t  by: %s\n#\tdate: %s#\n",
E 10
I 10
D 17
	(void)printf("#\t  fs: %s\n#\t  by: %s\n#\tdate: %s\n",
E 10
E 7
	    curp, getlogin(), ctime(&clock));
E 17
I 17
	(void)gethostname(host, sizeof(host));
	(void)printf(
	    "#\t   user: %s\n#\tmachine: %s\n#\t   tree: %s\n#\t   date: %s",
	    getlogin(), host, fullpath, ctime(&clock));
E 17

D 7
	cwalk((ENTRY *)NULL, path + 1);
	shostats();
	pwalk(root, 0);
	exit(0);
}

static
E 6
cwalk(parent, tail)
	ENTRY *parent;
	register char *tail;
{
	extern ENTRY *root;
D 6
	extern dev_t device;
	extern int dflag, xflag, errno, alphasort();
E 6
I 6
	extern int dflag, xflag, alphasort();
E 6
	extern char path[];
	register ENTRY *centry, *level;
	struct dirent *dp, **dir_list;
	struct stat sbuf;
I 6
	dev_t device;
E 6
	int cnt, dir_cnt;
	char *emalloc(), *rlink();

	*tail++ = '/';
	dir_cnt = scandir(".", &dir_list, NULL, alphasort);
D 2
	if (dir_cnt == -1 || xflag && stat(".", &sbuf)) {
E 2
I 2
	if (dir_cnt == -1 || xflag && lstat(".", &sbuf)) {
E 2
		(void)fprintf(stderr, "mtree: %s: %s\n", path + 2,
		    strerror(errno));
			exit(1);
E 7
I 7
D 13
	if (!(t = ftsopen(".", ftsoptions, dsort))) {
E 13
I 13
	argv[0] = ".";
D 17
	argv[1] = (char *)NULL;
D 15
	if (!(t = ftsopen(argv, ftsoptions, dsort))) {
E 15
I 15
	if (!(t = fts_open(argv, ftsoptions, dsort))) {
E 15
E 13
		(void)fprintf(stderr,
D 15
		    "mtree: ftsopen: %s.\n", strerror(errno));
E 15
I 15
		    "mtree: fts_open: %s.\n", strerror(errno));
E 15
		exit(1);
E 7
	}
D 7
	device = sbuf.st_dev;
	for (cnt = 0; cnt < dir_cnt; ++cnt) {
		dp = dir_list[cnt];
		if (dp->d_name[0] == '.' &&
		    (!dp->d_name[1] || dp->d_name[1] == '.' && !dp->d_name[2]))
			continue;
		bcopy(dp->d_name, tail, dp->d_namlen + 1);
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
		if (dflag && !S_ISDIR(sbuf.st_mode))
			continue;

		centry = (ENTRY *)emalloc(sizeof(ENTRY));
		if (!(centry->name = strdup(dp->d_name)))
			nomem();
		centry->nlen = dp->d_namlen;

		switch(sbuf.st_mode&S_IFMT) {
		case S_IFDIR:
			centry->info.type = F_DIR;
			break;
		case S_IFCHR:
			centry->info.type = F_CHAR;
			break;
		case S_IFBLK:
			centry->info.type = F_BLOCK;
			break;
		case S_IFREG:
			centry->info.type = F_FILE;
			break;
		case S_IFLNK:
			centry->info.type = F_LINK;
			centry->info.slink = strdup(rlink(dp->d_name));
			break;
		case S_IFSOCK:
			centry->info.type = F_SOCK;
E 7
I 7
D 15
	while (p = ftsread(t)) {
E 15
I 15
	while (p = fts_read(t)) {
E 17
I 17
	argv[1] = NULL;
	if ((t = fts_open(argv, ftsoptions, dsort)) == NULL)
		err("fts_open: %s", strerror(errno));
	while (p = fts_read(t))
E 17
E 15
		switch(p->fts_info) {
		case FTS_D:
D 17
			if (dflag)
				notset = 1;
			else
				notset =
				    statdir(t, p, &uid, &gid, &mode, &tabs);
			if (!strcmp(p->fts_name, "."))
				continue;
E 17
I 17
			(void)printf("\n# %s\n", p->fts_path);
			statd(t, p, &uid, &gid, &mode);
			statf(p);
E 17
E 7
			break;
I 7
D 16
		case FTS_DC:
			(void)fprintf(stderr,
			    "mtree: directory cycle: %s.\n", p->fts_path);
			continue;
		case FTS_DNR:
			(void)fprintf(stderr,
			    "mtree: %s: unable to read.\n", p->fts_path);
			continue;
		case FTS_DNX:
			(void)fprintf(stderr,
			    "mtree: %s: unable to search.\n", p->fts_path);
			continue;
E 16
		case FTS_DP:
D 17
			if (p->fts_level <= 0)
				continue;
			for (cnt = p->fts_level - 1; cnt-- > 0; )
				(void)putchar('\t');
			(void)printf("..\n");
			continue;
E 17
I 17
			if (p->fts_level > 0)
				(void)printf("# %s\n..\n\n", p->fts_path);
			break;
E 17
I 16
		case FTS_DNR:
E 16
		case FTS_ERR:
I 16
		case FTS_NS:
E 16
D 17
			(void)fprintf(stderr, "mtree: %s: %s.\n",
			    p->fts_path, strerror(errno));
D 16
			continue;
		case FTS_NS:
			(void)fprintf(stderr,
			    "mtree: can't stat: %s.\n", p->fts_path);
E 16
			continue;
E 17
I 17
			(void)fprintf(stderr,
			    "mtree: %s: %s\n", p->fts_path, strerror(errno));
			break;
E 17
E 7
		default:
D 7
			(void)fprintf(stderr, "mtree: unknown file type %s.\n",
			    path + 2);
			exit(1);
E 7
I 7
D 17
			if (dflag)
				continue;
E 17
I 17
			if (!dflag)
				statf(p);
			break;
			
E 17
E 7
		}
I 17
	(void)fts_close(t);
	if (sflag && keys & F_CKSUM)
		(void)fprintf(stderr,
		    "mtree: %s checksum: %lu\n", fullpath, crc_total);
}
E 17
D 7
		centry->info.st_uid = sbuf.st_uid;
		centry->info.st_gid = sbuf.st_gid;
		centry->info.st_size = sbuf.st_size;
		centry->info.st_mode = sbuf.st_mode&07777;
		centry->info.st_nlink = sbuf.st_nlink;
		centry->info.st_uid = sbuf.st_uid;
E 7

D 7
		if (!root) {
			level = root = centry;
			root->parent = root->child = NULL;
		}
		else if (parent) {
			centry->parent = parent;
			parent->child = centry;
			level = centry;
			parent = NULL;
		}
E 7
I 7
D 17
		for (cnt = p->fts_level - 1; cnt-- > 0; )
			(void)putchar('\t');
		(void)printf("%s", p->fts_name);
		if (p->fts_info == FTS_D)
			(void)putchar('\t');
E 7
		else {
D 7
			centry->parent = level->parent;
			level = level->next = centry;
E 7
I 7
			if (tabs > 1 && p->fts_namelen < 8)
				(void)putchar('\t');
			(void)putchar('\t');
E 7
		}
E 17
I 17
static void
statf(p)
	FTSENT *p;
{
	struct group *gr;
	struct passwd *pw;
	u_long len, val;
	int fd, indent;
E 17
D 7
		stats(&centry->info);
		if (!S_ISDIR(sbuf.st_mode) || xflag && device != sbuf.st_dev)
			continue;
		if (chdir(dp->d_name)) {
			(void)fprintf(stderr, "mtree: %s: %s\n", path + 2,
			    strerror(errno));
			exit(1);
		}
		cwalk(level, tail + dp->d_namlen);
		if (chdir("..")) {
			(void)fprintf(stderr, "mtree: ..: %s\n",
			    strerror(errno));
			exit(1);
		}
	}
}
E 7

D 7
#define	LABEL { \
	if (!label++) \
		(void)printf("%s", level->nlen > 7 ? "\t" : "\t\t"); \
	else \
		(void)putchar(' '); \
}

extern mode_t dmode;				/* default directory mode */
extern mode_t fmode;				/* default file mode */
uid_t uid, gid;					/* default owner, group */
D 3

E 3
I 3
u_int type;
I 6

static
E 6
E 3
pwalk(level, tabs)
	ENTRY *level;
	int tabs;
{
	INFO *ip;
	register int cnt;
	int label;
	char *ftype();

	for (; level; level = level->next) {
		for (cnt = tabs; cnt--; )
			(void)putchar('\t');
		(void)printf("%s", level->name);
E 7
D 17
		label = 0;
D 3
		if ((ip = &level->info)->type != F_FILE) {
E 3
I 3
D 7
		if ((ip = &level->info)->type != type) {
E 7
I 7
		if (!S_ISREG(p->fts_statb.st_mode) || notset) {
E 7
E 3
			LABEL;
D 7
			(void)printf("type=%s", ftype(ip->type));
E 7
I 7
			(void)printf("type=%s", inotype(p->fts_statb.st_mode));
E 7
		}
D 7
		if (ip->st_uid != uid) {
E 7
I 7
		if (p->fts_statb.st_uid != uid || notset) {
E 7
			LABEL;
D 7
			(void)printf("owner=%u", ip->st_uid);
E 7
I 7
			(void)printf("owner=%u", p->fts_statb.st_uid);
E 7
		}
D 7
		if (ip->st_gid != gid) {
E 7
I 7
		if (p->fts_statb.st_gid != gid || notset) {
E 7
			LABEL;
D 7
			(void)printf("group=%u", ip->st_gid);
E 7
I 7
			(void)printf("group=%u", p->fts_statb.st_gid);
E 7
		}
D 7
		if (ip->type == F_DIR) {
			if (ip->st_mode != dmode) {
				LABEL;
				(void)printf("mode=%o", ip->st_mode);
			}
		} else {
			if (ip->st_mode != fmode) {
				LABEL;
				(void)printf("mode=%o", ip->st_mode);
			}
			if (ip->st_nlink != 1) {
				LABEL;
				(void)printf("nlink=%u", ip->st_nlink);
			}
E 7
I 7
		if ((p->fts_statb.st_mode & MBITS) != mode || notset) {
			LABEL;
			(void)printf("mode=%#o", p->fts_statb.st_mode & MBITS);
E 7
		}
I 7
		if (p->fts_statb.st_nlink != 1 || notset) {
			LABEL;
			(void)printf("nlink=%u", p->fts_statb.st_nlink);
		}
E 7
		LABEL;
D 7
		(void)printf("size=%ld", ip->st_size);
		if (ip->slink)
			(void)printf(" link=%s", ip->slink);
		(void)putchar('\n');
		if (level->child)
			pwalk(level->child, tabs + 1);
		if (ip->type == F_DIR) {
			for (cnt = tabs; cnt--; )
				(void)putchar('\t');
			(void)printf("..\n");
E 7
I 7
		(void)printf("size=%ld", p->fts_statb.st_size);
I 12
		LABEL;
		(void)printf("time=%ld", p->fts_statb.st_mtime);
E 17
I 17
D 18
	if (S_ISDIR(p->fts_statb.st_mode))
E 18
I 18
	if (S_ISDIR(p->fts_statp->st_mode))
E 18
		indent = printf("%s", p->fts_name); 
	else
		indent = printf("    %s", p->fts_name);
E 17
E 12

D 17
		if (p->fts_info == FTS_SL || p->fts_info == FTS_SLNONE) {
			LABEL;
			(void)printf("link=%s", rlink(p->fts_accpath));
E 7
		}
I 7
		(void)putchar('\n');
E 17
I 17
	if (indent > INDENTNAMELEN)
		indent = MAXLINELEN;
	else
		indent += printf("%*s", INDENTNAMELEN - indent, "");

D 18
	if (!S_ISREG(p->fts_statb.st_mode))
		output(&indent, "type=%s", inotype(p->fts_statb.st_mode));
	if (keys & (F_UID | F_UNAME) && p->fts_statb.st_uid != uid)
		if (keys & F_UNAME && (pw = getpwuid(p->fts_statb.st_uid)))
E 18
I 18
	if (!S_ISREG(p->fts_statp->st_mode))
		output(&indent, "type=%s", inotype(p->fts_statp->st_mode));
	if (keys & (F_UID | F_UNAME) && p->fts_statp->st_uid != uid)
		if (keys & F_UNAME && (pw = getpwuid(p->fts_statp->st_uid)))
E 18
			output(&indent, "uname=%s", pw->pw_name);
		else /* if (keys & F_UID) */
D 18
			output(&indent, "uid=%u", p->fts_statb.st_uid);
	if (keys & (F_GID | F_GNAME) && p->fts_statb.st_gid != gid)
		if (keys & F_GNAME && (gr = getgrgid(p->fts_statb.st_gid)))
E 18
I 18
			output(&indent, "uid=%u", p->fts_statp->st_uid);
	if (keys & (F_GID | F_GNAME) && p->fts_statp->st_gid != gid)
		if (keys & F_GNAME && (gr = getgrgid(p->fts_statp->st_gid)))
E 18
D 21
			output(&indent, "gid=%s", gr->gr_name);
E 21
I 21
			output(&indent, "gname=%s", gr->gr_name);
E 21
		else /* if (keys & F_GID) */
D 18
			output(&indent, "gid=%u", p->fts_statb.st_gid);
	if (keys & F_MODE && (p->fts_statb.st_mode & MBITS) != mode)
		output(&indent, "mode=%#o", p->fts_statb.st_mode & MBITS);
	if (keys & F_NLINK && p->fts_statb.st_nlink != 1)
		output(&indent, "nlink=%u", p->fts_statb.st_nlink);
E 18
I 18
			output(&indent, "gid=%u", p->fts_statp->st_gid);
	if (keys & F_MODE && (p->fts_statp->st_mode & MBITS) != mode)
		output(&indent, "mode=%#o", p->fts_statp->st_mode & MBITS);
	if (keys & F_NLINK && p->fts_statp->st_nlink != 1)
		output(&indent, "nlink=%u", p->fts_statp->st_nlink);
E 18
	if (keys & F_SIZE)
D 18
		output(&indent, "size=%ld", p->fts_statb.st_size);
E 18
I 18
D 22
		output(&indent, "size=%ld", p->fts_statp->st_size);
E 22
I 22
		output(&indent, "size=%qd", p->fts_statp->st_size);
E 22
E 18
	if (keys & F_TIME)
D 18
		output(&indent, "time=%ld", p->fts_statb.st_mtime);
	if (keys & F_CKSUM && S_ISREG(p->fts_statb.st_mode)) {
E 18
I 18
D 20
		output(&indent, "time=%ld", p->fts_statp->st_mtime);
E 20
I 20
		output(&indent, "time=%ld.%ld",
		    p->fts_statp->st_mtimespec.ts_sec,
		    p->fts_statp->st_mtimespec.ts_nsec);
E 20
	if (keys & F_CKSUM && S_ISREG(p->fts_statp->st_mode)) {
E 18
		if ((fd = open(p->fts_accpath, O_RDONLY, 0)) < 0 ||
		    crc(fd, &val, &len))
			err("%s: %s", p->fts_accpath, strerror(errno));
		(void)close(fd);
		output(&indent, "cksum=%lu", val);
E 17
E 7
	}
I 14
D 15
	(void)ftsclose(t);
E 15
I 15
D 17
	(void)fts_close(t);
E 17
I 17
	if (keys & F_SLINK &&
	    (p->fts_info == FTS_SL || p->fts_info == FTS_SLNONE))
		output(&indent, "link=%s", rlink(p->fts_accpath));
	(void)putchar('\n');
E 17
E 15
E 14
}

D 7
ID *uhead;
ID *ghead;
u_long dmodes[0777 + 1];
u_long fmodes[0777 + 1];
E 7
I 7
#define	MAXGID	5000
#define	MAXUID	5000
D 9
#define	MAXMODE	0777 + 1
E 9
I 9
#define	MAXMODE	MBITS + 1
E 9
E 7

I 6
D 11
static
E 11
E 6
D 7
stats(ip)
	INFO *ip;
E 7
I 7
D 17
statdir(t, parent, puid, pgid, pmode, tabs)
E 17
I 17
static int
statd(t, parent, puid, pgid, pmode)
E 17
	FTS *t;
	FTSENT *parent;
	uid_t *puid;
	gid_t *pgid;
	mode_t *pmode;
D 17
	int *tabs;
E 17
E 7
{
D 7
	register ID *p;
E 7
I 7
	register FTSENT *p;
D 17
	register gid_t gid;
	register uid_t uid;
	register mode_t mode;
E 17
I 17
	register gid_t sgid;
	register uid_t suid;
	register mode_t smode;
	struct group *gr;
	struct passwd *pw;
E 17
	gid_t savegid;
	uid_t saveuid;
	mode_t savemode;
	u_short maxgid, maxuid, maxmode, g[MAXGID], u[MAXUID], m[MAXMODE];
E 7

D 7
	if (ip->type == F_DIR)
		++dmodes[ip->st_mode&0777];
	else
		++fmodes[ip->st_mode&0777];
	for (p = uhead;; p = p->next)
		if (!p) {
			p = (ID *)emalloc(sizeof(ID));
			p->id = ip->st_uid;
			p->next = uhead;
			uhead = p;
			break;
		} else if (p->id == ip->st_uid) {
			++p->cnt;
			break;
E 7
I 7
D 15
	if (!(p = ftschildren(t))) {
E 15
I 15
D 17
	if (!(p = fts_children(t))) {
E 15
		if (errno) {
			(void)fprintf(stderr, "mtree: %s: %s.\n",
			    RP(parent), strerror(errno));
			exit(1);
E 7
		}
D 7
	for (p = ghead;; p = p->next)
		if (!p) {
			p = (ID *)emalloc(sizeof(ID));
			p->id = ip->st_gid;
			p->next = ghead;
			ghead = p;
			break;
		} else if (p->id == ip->st_gid) {
			++p->cnt;
			break;
		}
}
E 7
I 7
		return(1);
E 17
I 17
D 19
	if ((p = fts_children(t)) == NULL) {
E 19
I 19
	if ((p = fts_children(t, 0)) == NULL) {
E 19
		if (errno)
			err("%s: %s", RP(parent), strerror(errno));
		return (1);
E 17
	}
E 7

I 6
D 7
static
E 6
shostats()
{
I 4
	extern int dflag;
E 4
	register ID *p;
	register mode_t cnt;
	register u_long max;
E 7
I 7
	bzero(g, sizeof(g));
	bzero(u, sizeof(u));
	bzero(m, sizeof(m));
E 7

D 7
	for (max = 0, cnt = 0777; cnt; --cnt)
		if (dmodes[cnt] > max) {
			max = dmodes[cnt];
			dmode = cnt;
E 7
I 7
D 17
	*tabs = 1;
E 17
	maxuid = maxgid = maxmode = 0;
	for (; p; p = p->fts_link) {
D 9
		mode = p->fts_statb.st_mode&0777;
E 9
I 9
D 17
		mode = p->fts_statb.st_mode & MBITS;
E 9
		if (mode < MAXMODE && ++m[mode] > maxmode) {
			savemode = mode;
			maxmode = m[mode];
E 17
I 17
D 18
		smode = p->fts_statb.st_mode & MBITS;
E 18
I 18
		smode = p->fts_statp->st_mode & MBITS;
E 18
		if (smode < MAXMODE && ++m[smode] > maxmode) {
			savemode = smode;
			maxmode = m[smode];
E 17
E 7
		}
D 7
	(void)printf("/set dmode=%o\n", dmode);
	for (max = 0, cnt = 0777; cnt; --cnt)
		if (fmodes[cnt] > max) {
			max = dmodes[cnt];
			fmode = cnt;
E 7
I 7
D 17
		gid = p->fts_statb.st_gid;
		if (gid < MAXGID && ++g[gid] > maxgid) {
			savegid = gid;
			maxgid = g[gid];
E 17
I 17
D 18
		sgid = p->fts_statb.st_gid;
E 18
I 18
		sgid = p->fts_statp->st_gid;
E 18
		if (sgid < MAXGID && ++g[sgid] > maxgid) {
			savegid = sgid;
			maxgid = g[sgid];
E 17
E 7
		}
D 7
	(void)printf("/set fmode=%o\n", fmode);
	for (max = 0, p = uhead; p; p = p->next)
		if (p->cnt > max) {
			max = p->cnt;
			uid = p->id;
E 7
I 7
D 17
		uid = p->fts_statb.st_uid;
		if (uid < MAXUID && ++u[uid] > maxuid) {
			saveuid = uid;
			maxuid = u[uid];
E 17
I 17
D 18
		suid = p->fts_statb.st_uid;
E 18
I 18
		suid = p->fts_statp->st_uid;
E 18
		if (suid < MAXUID && ++u[suid] > maxuid) {
			saveuid = suid;
			maxuid = u[suid];
E 17
E 7
		}
D 7
	(void)printf("/set owner=%u\n", uid);
	for (max = 0, p = ghead; p; p = p->next)
		if (p->cnt > max) {
			max = p->cnt;
			gid = p->id;
		}
	(void)printf("/set group=%u\n", gid);
	(void)printf("/set nlink=1\n");
D 3
	(void)printf("/set type=%s\n\n", dflag ? "dir" : "file");
E 3
I 3
	if (dflag) {
		type = F_DIR;
		(void)printf("/set type=dir\n\n");
	} else {
		type = F_FILE;
		(void)printf("/set type=file\n\n");
E 7
I 7
D 17
		if (p->fts_namelen > 7)
			*tabs = 2;
E 17
E 7
	}
I 7
D 8
	(void)printf("\n/set group=%u, mode=%#o, nlink=1, owner=%u, type=file\n",
E 8
I 8
D 17
	(void)printf("\n/set group=%u mode=%#o nlink=1 owner=%u type=file\n",
E 8
	    savegid, savemode, saveuid);
E 17
I 17
	(void)printf("/set type=file");
	if (keys & F_GID)
		(void)printf(" gid=%u", savegid);
	if (keys & F_GNAME)
		if ((gr = getgrgid(savegid)) != NULL)
			(void)printf(" gname=%s", gr->gr_name);
		else
			(void)printf(" gid=%u", savegid);
	if (keys & F_UNAME)
		if ((pw = getpwuid(saveuid)) != NULL)
			(void)printf(" uname=%s", pw->pw_name);
		else
			(void)printf(" uid=%u", saveuid);
	if (keys & F_UID)
		(void)printf(" uid=%u", saveuid);
	if (keys & F_MODE)
		(void)printf(" mode=%#o", savemode);
	if (keys & F_NLINK)
		(void)printf(" nlink=1");
	(void)printf("\n");
E 17
	*puid = saveuid;
	*pgid = savegid;
	*pmode = savemode;
D 17
	return(0);
E 17
I 17
	return (0);
E 17
}

D 11
static
E 11
D 17
dsort(p1, p2)
	FTSENT **p1, **p2;
E 17
I 17
static int
dsort(a, b)
	const FTSENT **a, **b;
E 17
{
D 17
	register FTSENT *a, *b;
E 17
I 17
D 18
	if (S_ISDIR((*a)->fts_statb.st_mode)) {
		if (!S_ISDIR((*b)->fts_statb.st_mode))
E 18
I 18
	if (S_ISDIR((*a)->fts_statp->st_mode)) {
		if (!S_ISDIR((*b)->fts_statp->st_mode))
E 18
			return (1);
D 18
	} else if (S_ISDIR((*b)->fts_statb.st_mode))
E 18
I 18
	} else if (S_ISDIR((*b)->fts_statp->st_mode))
E 18
		return (-1);
	return (strcmp((*a)->fts_name, (*b)->fts_name));
}
E 17

D 17
	a = *p1;
	b = *p2;
E 17
I 17
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
E 17

D 17
	if (S_ISDIR(a->fts_statb.st_mode)) {
		if (!S_ISDIR(b->fts_statb.st_mode))
			return(1);
	} else if (S_ISDIR(b->fts_statb.st_mode))
		return(-1);
	return(strcmp(a->fts_name, b->fts_name));
E 17
I 17
void
#if __STDC__
output(int *offset, const char *fmt, ...)
#else
output(offset, fmt, va_alist)
	int *offset;
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
D 23
	int len;
E 23
	char buf[1024];
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
D 23
	len = vsnprintf(buf, sizeof(buf), fmt, ap);
E 23
I 23
	(void)vsnprintf(buf, sizeof(buf), fmt, ap);
E 23
	va_end(ap);

D 23
	if (*offset + len > MAXLINELEN - 3) {
E 23
I 23
	if (*offset + strlen(buf) > MAXLINELEN - 3) {
E 23
		(void)printf(" \\\n%*s", INDENTNAMELEN, "");
		*offset = INDENTNAMELEN;
	}
	*offset += printf(" %s", buf) + 1;
E 17
E 7
E 3
}
E 1
