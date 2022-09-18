h48195
s 00002/00002/00243
d D 8.1 93/06/06 14:02:51 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00244
d D 5.13 92/09/01 13:52:50 bostic 13 12
c sizes are quad's, not
e
s 00004/00004/00241
d D 5.12 92/07/15 17:52:03 bostic 12 11
c prettiness police
e
s 00010/00003/00235
d D 5.11 92/06/18 17:51:41 bostic 11 10
c stat structure changes for quad/POSIX times
e
s 00002/00001/00236
d D 5.10 92/03/31 16:20:00 bostic 10 9
c missing parameter for printf
e
s 00021/00020/00216
d D 5.9 92/01/27 16:02:23 bostic 9 8
c fts_statb -> fts_statp
e
s 00106/00064/00130
d D 5.8 91/12/11 17:56:11 bostic 8 7
c version 2; add cksum, make keywords flexible, new output format
e
s 00007/00000/00187
d D 5.7 90/05/25 16:50:43 bostic 7 6
c add modification time keyword
e
s 00006/00000/00181
d D 5.6 90/05/25 12:54:10 bostic 6 5
c add FIFO support
e
s 00009/00009/00172
d D 5.5 90/05/25 12:19:23 bostic 5 4
c fold INFO and ENTRY structures together into NODE structure
e
s 00060/00050/00121
d D 5.4 90/05/25 10:28:34 bostic 4 3
c integrate with fts(3), move rlink() here
e
s 00002/00002/00169
d D 5.3 90/05/22 12:58:40 bostic 3 2
c rearrange and make the world static
e
s 00001/00001/00170
d D 5.2 90/05/15 20:04:30 bostic 2 1
c string.h is ANSI C include file
e
s 00171/00000/00000
d D 5.1 89/09/04 16:24:49 bostic 1 0
c date and time created 89/09/04 16:24:49 by bostic
e
u
U
t
T
I 1
D 4
/*
E 4
I 4
/*-
E 4
D 14
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 4
#include <sys/types.h>
E 4
I 4
#include <sys/param.h>
E 4
#include <sys/stat.h>
I 8
#include <fcntl.h>
E 8
I 4
#include <fts.h>
E 4
I 3
#include <errno.h>
E 3
#include <stdio.h>
I 7
#include <time.h>
I 8
#include <unistd.h>
E 8
E 7
D 2
#include <strings.h>
E 2
I 2
D 3
#include <string.h>
E 3
E 2
#include "mtree.h"
I 8
#include "extern.h"
E 8

I 8
extern int uflag;

static char *ftype __P((u_int));

#define	INDENTNAMELEN	8
E 8
D 4
#define	LABEL { \
E 4
I 4
#define	LABEL \
E 4
D 8
	if (!label++) \
D 4
		(void)printf("%s: ", path + 2); \
}
E 4
I 4
		(void)printf("%s: ", RP(p)); \
E 8
I 8
	if (!label++) { \
		len = printf("%s: ", RP(p)); \
		if (len > INDENTNAMELEN) { \
			tab = "\t"; \
			(void)printf("\n"); \
		} else { \
			tab = ""; \
			(void)printf("%*s", INDENTNAMELEN - len, ""); \
		} \
	}
E 8
E 4

I 8
int
E 8
D 4
compare(name, s1, s2)
E 4
I 4
compare(name, s, p)
E 4
	char *name;
D 4
	register INFO *s1;
	register struct stat *s2;
E 4
I 4
D 5
	register INFO *s;
E 5
I 5
	register NODE *s;
E 5
	register FTSENT *p;
E 4
{
D 3
	extern int errno, exitval, uflag;
E 3
I 3
D 8
	extern int exitval, uflag;
E 3
D 4
	extern char path[];
E 4
	int label;
D 4
	char *p, *ftype(), *inotype(), *rlink();
E 4
I 4
	char *ftype(), *inotype(), *rlink();
E 8
I 8
	extern int uflag;
	u_long len, val;
	int fd, label;
	char *cp, *tab;
E 8
E 4

	label = 0;
D 4
	switch(s1->type) {
E 4
I 4
	switch(s->type) {
E 4
	case F_BLOCK:
D 4
		if (!S_ISBLK(s2->st_mode))
E 4
I 4
D 9
		if (!S_ISBLK(p->fts_statb.st_mode))
E 9
I 9
		if (!S_ISBLK(p->fts_statp->st_mode))
E 9
E 4
			goto typeerr;
		break;
	case F_CHAR:
D 4
		if (!S_ISCHR(s2->st_mode))
E 4
I 4
D 9
		if (!S_ISCHR(p->fts_statb.st_mode))
E 9
I 9
		if (!S_ISCHR(p->fts_statp->st_mode))
E 9
E 4
			goto typeerr;
		break;
	case F_DIR:
D 4
		if (!S_ISDIR(s2->st_mode))
E 4
I 4
D 9
		if (!S_ISDIR(p->fts_statb.st_mode))
E 9
I 9
		if (!S_ISDIR(p->fts_statp->st_mode))
E 9
E 4
			goto typeerr;
		break;
I 6
	case F_FIFO:
D 9
		if (!S_ISFIFO(p->fts_statb.st_mode))
E 9
I 9
		if (!S_ISFIFO(p->fts_statp->st_mode))
E 9
			goto typeerr;
		break;
E 6
	case F_FILE:
D 4
		if (!S_ISREG(s2->st_mode))
E 4
I 4
D 9
		if (!S_ISREG(p->fts_statb.st_mode))
E 9
I 9
		if (!S_ISREG(p->fts_statp->st_mode))
E 9
E 4
			goto typeerr;
		break;
	case F_LINK:
D 4
		if (!S_ISLNK(s2->st_mode))
E 4
I 4
D 9
		if (!S_ISLNK(p->fts_statb.st_mode))
E 9
I 9
		if (!S_ISLNK(p->fts_statp->st_mode))
E 9
E 4
			goto typeerr;
		break;
	case F_SOCK:
D 4
		if (!S_ISFIFO(s2->st_mode)) {
E 4
I 4
D 8
		if (!S_ISFIFO(p->fts_statb.st_mode)) {
E 8
I 8
D 9
		if (!S_ISSOCK(p->fts_statb.st_mode)) {
E 9
I 9
		if (!S_ISSOCK(p->fts_statp->st_mode)) {
E 9
E 8
E 4
typeerr:		LABEL;
D 8
			(void)printf("\n\ttype (%s, %s)",
E 8
I 8
			(void)printf("\ttype (%s, %s)\n",
E 8
D 4
			    ftype(s1->type), inotype(s2->st_mode));
E 4
I 4
D 9
			    ftype(s->type), inotype(p->fts_statb.st_mode));
E 9
I 9
			    ftype(s->type), inotype(p->fts_statp->st_mode));
E 9
E 4
		}
		break;
	}
D 4
	if (s1->flags&F_MODE && s1->st_mode != (s2->st_mode&07777)) {
E 4
I 4
D 5
	if (s->flags&F_MODE && s->st_mode != (p->fts_statb.st_mode&MBITS)) {
E 5
I 5
D 8
	if (s->flags & F_MODE && s->st_mode != (p->fts_statb.st_mode & MBITS)) {
E 8
I 8
	/* Set the uid/gid first, then set the mode. */
D 9
	if (s->flags & (F_UID | F_UNAME) && s->st_uid != p->fts_statb.st_uid) {
E 9
I 9
	if (s->flags & (F_UID | F_UNAME) && s->st_uid != p->fts_statp->st_uid) {
E 9
E 8
E 5
E 4
		LABEL;
D 8
		(void)printf("\n\tpermissions (%#o, %#o%s",
D 4
		    s1->st_mode, s2->st_mode&07777, uflag ? "" : ")");
E 4
I 4
D 5
		    s->st_mode, p->fts_statb.st_mode&MBITS, uflag ? "" : ")");
E 5
I 5
		    s->st_mode, p->fts_statb.st_mode & MBITS, uflag ? "" : ")");
E 8
I 8
		(void)printf("%suser (%u, %u",
D 9
		    tab, s->st_uid, p->fts_statb.st_uid);
E 9
I 9
		    tab, s->st_uid, p->fts_statp->st_uid);
E 9
E 8
E 5
E 4
		if (uflag)
D 4
			if (chmod(path, s1->st_mode))
E 4
I 4
D 8
			if (chmod(p->fts_accpath, s->st_mode))
E 4
				(void)printf(", not modified: %s)",
E 8
I 8
			if (chown(p->fts_accpath, s->st_uid, -1))
				(void)printf(", not modified: %s)\n",
E 8
				    strerror(errno));
			else
D 8
				(void)printf(", modified)");
E 8
I 8
				(void)printf(", modified)\n");
		else
			(void)printf(")\n");
		tab = "\t";
E 8
	}
D 4
	if (s1->flags&F_OWNER && s1->st_uid != s2->st_uid) {
E 4
I 4
D 5
	if (s->flags&F_OWNER && s->st_uid != p->fts_statb.st_uid) {
E 5
I 5
D 8
	if (s->flags & F_OWNER && s->st_uid != p->fts_statb.st_uid) {
E 8
I 8
D 9
	if (s->flags & (F_GID | F_GNAME) && s->st_gid != p->fts_statb.st_gid) {
E 9
I 9
	if (s->flags & (F_GID | F_GNAME) && s->st_gid != p->fts_statp->st_gid) {
E 9
E 8
E 5
E 4
		LABEL;
D 8
		(void)printf("\n\towner (%u, %u%s",
D 4
		    s1->st_uid, s2->st_uid, uflag ? "" : ")");
E 4
I 4
		    s->st_uid, p->fts_statb.st_uid, uflag ? "" : ")");
E 8
I 8
D 9
		(void)printf("%sgid (%u, %u", s->st_gid, p->fts_statb.st_gid);
E 9
I 9
D 10
		(void)printf("%sgid (%u, %u", s->st_gid, p->fts_statp->st_gid);
E 10
I 10
		(void)printf("%sgid (%u, %u",
		    tab, s->st_gid, p->fts_statp->st_gid);
E 10
E 9
E 8
E 4
		if (uflag)
D 4
			if (chown(path, s1->st_uid, -1))
E 4
I 4
D 8
			if (chown(p->fts_accpath, s->st_uid, -1))
E 8
I 8
			if (chown(p->fts_accpath, -1, s->st_gid))
E 8
E 4
D 12
				(void)printf(", not modified: %s)",
E 12
I 12
				(void)printf(", not modified: %s)\n",
E 12
				    strerror(errno));
			else
D 12
				(void)printf(", modified)");
E 12
I 12
				(void)printf(", modified)\n");
E 12
I 8
		else
			(void)printf(")\n");
		tab = "\t";
E 8
	}
D 4
	if (s1->flags&F_GROUP && s1->st_gid != s2->st_gid) {
E 4
I 4
D 5
	if (s->flags&F_GROUP && s->st_gid != p->fts_statb.st_gid) {
E 5
I 5
D 8
	if (s->flags & F_GROUP && s->st_gid != p->fts_statb.st_gid) {
E 8
I 8
D 9
	if (s->flags & F_MODE && s->st_mode != (p->fts_statb.st_mode & MBITS)) {
E 9
I 9
	if (s->flags & F_MODE &&
	    s->st_mode != (p->fts_statp->st_mode & MBITS)) {
E 9
E 8
E 5
E 4
		LABEL;
D 8
		(void)printf("\n\tgroup (%u, %u%s",
D 4
		    s1->st_gid, s2->st_gid, uflag ? "" : ")");
E 4
I 4
		    s->st_gid, p->fts_statb.st_gid, uflag ? "" : ")");
E 8
I 8
		(void)printf("%spermissions (%#o, %#o",
D 9
		    tab, s->st_mode, p->fts_statb.st_mode & MBITS);
E 9
I 9
		    tab, s->st_mode, p->fts_statp->st_mode & MBITS);
E 9
E 8
E 4
		if (uflag)
D 4
			if (chown(path, -1, s1->st_gid))
E 4
I 4
D 8
			if (chown(p->fts_accpath, -1, s->st_gid))
E 8
I 8
			if (chmod(p->fts_accpath, s->st_mode))
E 8
E 4
D 12
				(void)printf(", not modified: %s)",
E 12
I 12
				(void)printf(", not modified: %s)\n",
E 12
				    strerror(errno));
			else
D 12
				(void)printf(", modified)");
E 12
I 12
				(void)printf(", modified)\n");
E 12
I 8
		else
			(void)printf(")\n");
		tab = "\t";
E 8
	}
D 4
	if (s1->flags&F_NLINK && s1->type != F_DIR &&
	    s1->st_nlink != s2->st_nlink) {
E 4
I 4
D 5
	if (s->flags&F_NLINK && s->type != F_DIR &&
E 5
I 5
	if (s->flags & F_NLINK && s->type != F_DIR &&
E 5
D 9
	    s->st_nlink != p->fts_statb.st_nlink) {
E 9
I 9
	    s->st_nlink != p->fts_statp->st_nlink) {
E 9
E 4
		LABEL;
D 8
		(void)printf("\n\tlink count (%u, %u)",
D 4
		    s1->st_nlink, s2->st_nlink);
E 4
I 4
		    s->st_nlink, p->fts_statb.st_nlink);
E 8
I 8
		(void)printf("%slink count (%u, %u)\n",
D 9
		    tab, s->st_nlink, p->fts_statb.st_nlink);
E 9
I 9
		    tab, s->st_nlink, p->fts_statp->st_nlink);
E 9
		tab = "\t";
E 8
E 4
	}
D 4
	if (s1->flags&F_SIZE && s1->st_size != s2->st_size) {
E 4
I 4
D 5
	if (s->flags&F_SIZE && s->st_size != p->fts_statb.st_size) {
E 5
I 5
D 9
	if (s->flags & F_SIZE && s->st_size != p->fts_statb.st_size) {
E 9
I 9
	if (s->flags & F_SIZE && s->st_size != p->fts_statp->st_size) {
E 9
E 5
E 4
		LABEL;
D 4
		(void)printf("\n\tsize (%ld, %ld)", s1->st_size, s2->st_size);
E 4
I 4
D 8
		(void)printf("\n\tsize (%ld, %ld)",
		    s->st_size, p->fts_statb.st_size);
E 8
I 8
D 13
		(void)printf("%ssize (%ld, %ld)\n",
E 13
I 13
		(void)printf("%ssize (%qd, %qd)\n",
E 13
D 9
		    tab, s->st_size, p->fts_statb.st_size);
E 9
I 9
		    tab, s->st_size, p->fts_statp->st_size);
E 9
		tab = "\t";
E 8
E 4
	}
D 4
	if (s1->flags&F_SLINK) {
		p = rlink(name);
		if (strcmp(p, s1->slink)) {
E 4
I 4
D 5
	if (s->flags&F_SLINK) {
E 5
I 5
D 8
	if (s->flags & F_SLINK) {
E 5
		char *cp;

		if (strcmp(cp = rlink(name), s->slink)) {
E 8
I 8
D 9
	if (s->flags & F_TIME && s->st_mtime != p->fts_statb.st_mtime) {
E 9
I 9
D 11
	if (s->flags & F_TIME && s->st_mtime != p->fts_statp->st_mtime) {
E 11
I 11
	/*
	 * XXX
	 * Catches nano-second differences, but doesn't display them.
	 */
	if (s->flags & F_TIME &&
	    s->st_mtimespec.ts_sec != p->fts_statp->st_mtimespec.ts_sec ||
	    s->st_mtimespec.ts_nsec != p->fts_statp->st_mtimespec.ts_nsec) {
E 11
E 9
		LABEL;
		(void)printf("%smodification time (%.24s, ",
D 11
		    tab, ctime(&s->st_mtime));
D 9
		(void)printf("%.24s)\n", ctime(&p->fts_statb.st_mtime));
E 9
I 9
		(void)printf("%.24s)\n", ctime(&p->fts_statp->st_mtime));
E 11
I 11
		    tab, ctime(&s->st_mtimespec.ts_sec));
		(void)printf("%.24s)\n",
		    ctime(&p->fts_statp->st_mtimespec.ts_sec));
E 11
E 9
		tab = "\t";
	}
	if (s->flags & F_CKSUM)
		if ((fd = open(p->fts_accpath, O_RDONLY, 0)) < 0) {
E 8
E 4
			LABEL;
D 4
			(void)printf("\n\tlink ref (%s, %s)", p, s1->slink);
E 4
I 4
D 8
			(void)printf("\n\tlink ref (%s, %s)", cp, s->slink);
E 8
I 8
			(void)printf("%scksum: %s: %s\n",
			    tab, p->fts_accpath, strerror(errno));
			tab = "\t";
		} else if (crc(fd, &val, &len)) {
			(void)close(fd);
			LABEL;
			(void)printf("%scksum: %s: %s\n",
			    tab, p->fts_accpath, strerror(errno));
			tab = "\t";
		} else {
			(void)close(fd);
			if (s->cksum != val) {
				LABEL;
				(void)printf("%scksum (%lu, %lu)\n", 
				    tab, s->cksum, val);
			}
			tab = "\t";
E 8
E 4
		}
I 7
D 8
	}
	if (s->flags & F_TIME && s->st_mtime != p->fts_statb.st_mtime) {
E 8
I 8
	if (s->flags & F_SLINK && strcmp(cp = rlink(name), s->slink)) {
E 8
		LABEL;
D 8
		(void)printf("\n\tmodification time (%.24s, ",
		    ctime(&s->st_mtime));
		(void)printf("%.24s)", ctime(&p->fts_statb.st_mtime));
E 8
I 8
		(void)printf("%slink ref (%s, %s)\n", tab, cp, s->slink);
E 8
E 7
	}
D 8
	if (label) {
		exitval = 2;
		putchar('\n');
	}
E 8
I 8
	return (label);
E 8
}

char *
inotype(type)
D 8
	mode_t type;
E 8
I 8
	u_int type;
E 8
{
D 5
	switch(type&S_IFMT) {
E 5
I 5
	switch(type & S_IFMT) {
E 5
D 4
	case S_IFCHR:
		return("char");
E 4
	case S_IFBLK:
D 8
		return("block");
E 8
I 8
		return ("block");
E 8
I 4
	case S_IFCHR:
D 8
		return("char");
E 8
I 8
		return ("char");
E 8
E 4
	case S_IFDIR:
D 4
		return("directory");
E 4
I 4
D 8
		return("dir");
E 8
I 8
		return ("dir");
	case S_IFIFO:
		return ("fifo");
E 8
E 4
	case S_IFREG:
D 8
		return("file");
E 8
I 8
		return ("file");
E 8
	case S_IFLNK:
D 8
		return("link");
E 8
I 8
		return ("link");
E 8
	case S_IFSOCK:
D 8
		return("socket");
E 8
I 8
		return ("socket");
E 8
	default:
D 8
		return("unknown");
E 8
I 8
		return ("unknown");
E 8
	}
	/* NOTREACHED */
}

D 8
char *
E 8
I 8
static char *
E 8
ftype(type)
	u_int type;
{
	switch(type) {
	case F_BLOCK:
D 8
		return("block");
E 8
I 8
		return ("block");
E 8
	case F_CHAR:
D 8
		return("char");
E 8
I 8
		return ("char");
E 8
	case F_DIR:
D 8
		return("dir");
E 8
I 8
		return ("dir");
E 8
I 6
	case F_FIFO:
D 8
		return("fifo");
E 8
I 8
		return ("fifo");
E 8
E 6
	case F_FILE:
D 8
		return("file");
E 8
I 8
		return ("file");
E 8
	case F_LINK:
D 8
		return("link");
E 8
I 8
		return ("link");
E 8
	case F_SOCK:
D 8
		return("socket");
E 8
I 8
		return ("socket");
E 8
I 4
	default:
D 8
		return("unknown");
E 8
I 8
		return ("unknown");
E 8
E 4
	}
	/* NOTREACHED */
I 4
}

char *
rlink(name)
	char *name;
{
D 8
	register int len;
E 8
	static char lbuf[MAXPATHLEN];
I 8
	register int len;
E 8

D 8
	len = readlink(name, lbuf, sizeof(lbuf));
	if (len == -1) {
		(void)fprintf(stderr, "mtree: %s: %s.\n",
		    name, strerror(errno));
		exit(1);
	}
E 8
I 8
	if ((len = readlink(name, lbuf, sizeof(lbuf))) == -1)
		err("%s: %s", name, strerror(errno));
E 8
	lbuf[len] = '\0';
D 8
	return(lbuf);
E 8
I 8
	return (lbuf);
E 8
E 4
}
E 1
