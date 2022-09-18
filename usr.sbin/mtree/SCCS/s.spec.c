h09631
s 00001/00001/00253
d D 8.2 95/04/28 17:32:17 bostic 20 19
c st_size may be a quad, not a long
e
s 00002/00002/00252
d D 8.1 93/06/06 14:03:21 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/00249
d D 5.18 92/06/18 17:51:45 bostic 18 17
c stat structure changes for quad/POSIX times
e
s 00004/00003/00246
d D 5.17 92/04/17 17:21:25 bostic 17 16
c add needvalue argument to parsekey
e
s 00004/00000/00245
d D 5.16 92/02/19 12:19:20 bostic 16 15
c initialize root
e
s 00107/00179/00138
d D 5.15 91/12/11 17:56:18 bostic 15 14
c version 2; add cksum, make keywords flexible, new output format
e
s 00001/00001/00316
d D 5.14 91/03/02 15:40:41 bostic 14 13
c ANSNI
e
s 00001/00001/00316
d D 5.13 90/07/21 09:56:19 bostic 13 12
c it's not ignored, mtree quits
e
s 00005/00000/00312
d D 5.12 90/05/25 16:50:51 bostic 12 11
c add modification time keyword
e
s 00003/00009/00309
d D 5.11 90/05/25 12:59:17 bostic 11 10
c don't make routines static, dbx doesn't like it
e
s 00002/00000/00316
d D 5.10 90/05/25 12:54:09 bostic 10 9
c add FIFO support
e
s 00015/00017/00301
d D 5.9 90/05/25 12:19:30 bostic 9 8
c fold INFO and ENTRY structures together into NODE structure
e
s 00003/00003/00315
d D 5.8 90/05/25 11:48:45 bostic 8 7
c lint
e
s 00014/00006/00304
d D 5.7 90/05/25 11:08:32 bostic 7 6
c make symbolic modes work, disallow commas in specification
e
s 00008/00006/00302
d D 5.6 90/05/25 10:43:32 bostic 6 5
c implement the magic characters in specification file names
e
s 00115/00142/00193
d D 5.5 90/05/25 10:30:31 bostic 5 4
c general cleanup, multiple keywords per line
e
s 00218/00016/00117
d D 5.4 90/05/22 12:58:45 bostic 4 3
c rearrange and make the world static
e
s 00001/00001/00132
d D 5.3 90/05/15 20:04:35 bostic 3 2
c string.h is ANSI C include file
e
s 00015/00010/00118
d D 5.2 89/09/06 13:51:53 bostic 2 1
c one more try at F_DONE bits, and making .. work right
e
s 00128/00000/00000
d D 5.1 89/09/04 16:24:55 bostic 1 0
c date and time created 89/09/04 16:24:55 by bostic
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
D 19
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
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

#include <sys/types.h>
I 15
#include <sys/stat.h>
#include <fts.h>
E 15
I 4
#include <pwd.h>
#include <grp.h>
E 4
D 5
#include <ctype.h>
E 5
D 15
#include <stdio.h>
E 15
I 5
#include <errno.h>
I 15
#include <unistd.h>
#include <stdio.h>
E 15
#include <ctype.h>
E 5
D 3
#include <strings.h>
E 3
I 3
D 4
#include <string.h>
E 4
E 3
#include "mtree.h"
I 15
#include "extern.h"
E 15

D 9
extern ENTRY *root;			/* root of the tree */
E 9
I 9
D 15
extern NODE *root;			/* root of the tree */
E 15
I 15
int lineno;				/* Current spec line number. */
E 15
E 9
D 4
int lineno;				/* current spec line number */
E 4
D 5
mode_t dmode;
mode_t fmode;
E 5

I 4
D 15
static int lineno;			/* current spec line number */
E 15
I 15
static void	 set __P((char *, NODE *));
static void	 unset __P((char *, NODE *));
E 15

I 15
NODE *
E 15
E 4
spec()
{
I 9
	register NODE *centry, *last;
E 9
	register char *p;
D 9
	ENTRY *centry, *last;
D 5
	INFO info;
	int ch, ignore;
D 4
	char buf[2048], *emalloc();
E 4
I 4
	char buf[1024], *emalloc();
E 5
I 5
	INFO info, ginfo;
E 9
I 9
D 15
	NODE ginfo, *emalloc();
E 15
I 15
	NODE ginfo, *root;
	int c_cur, c_next;
E 15
E 9
	char buf[2048];
D 6
	void *emalloc();
E 6
I 6
D 9
	ENTRY *emalloc();
E 9
E 6
E 5
E 4

I 16
	root = NULL;
E 16
D 5
	info.flags = 0;
	last = NULL;
E 5
I 5
D 9
	ginfo.flags = info.flags = 0;
	ginfo.type = info.type = F_NONE;
E 9
I 9
D 15
	bzero((void *)&ginfo, sizeof(ginfo));
E 9
E 5
	for (lineno = 1; fgets(buf, sizeof(buf), stdin); ++lineno) {
		if (!(p = index(buf, '\n'))) {
			(void)fprintf(stderr,
D 4
			    "mtree: line %d too long.\n", lineno);
E 4
I 4
D 13
			    "mtree: line %d too long, ignored.\n", lineno);
E 13
I 13
			    "mtree: line %d too long.\n", lineno);
E 13
E 4
D 5
			while ((ch = getchar()) != '\n' && ch != EOF);
			continue;
E 5
I 5
			exit(1);
E 15
I 15
	bzero(&ginfo, sizeof(ginfo));
	c_cur = c_next = 0;
	for (lineno = 1; fgets(buf, sizeof(buf), stdin);
	    ++lineno, c_cur = c_next, c_next = 0) {
		/* Skip empty lines. */
		if (buf[0] == '\n')
			continue;

		/* Find end of line. */
		if ((p = index(buf, '\n')) == NULL)
			err("line %d too long", lineno);

		/* See if next line is continuation line. */
		if (p[-1] == '\\') {
			--p;
			c_next = 1;
E 15
E 5
		}
I 15

		/* Null-terminate the line. */
E 15
		*p = '\0';
I 15

		/* Skip leading whitespace. */
E 15
		for (p = buf; *p && isspace(*p); ++p);
I 15

		/* If nothing but whitespace or comment char, continue. */
E 15
		if (!*p || *p == '#')
			continue;

I 16
#ifdef DEBUG
		(void)fprintf(stderr, "line %d: {%s}\n", lineno, p);
#endif
E 16
D 15
		/* grab file name, "$", "set", or "unset" */
D 5
		if (!(p = strtok(buf, "\n\t ")))
E 5
I 5
D 7
		if (!(p = strtok(p, "\n\t ,")))
E 7
I 7
		if (!(p = strtok(p, "\n\t ")))
E 7
E 5
			specerr();
E 15
I 15
		if (c_cur) {
			set(p, centry);
			continue;
		}
			
		/* Grab file name, "$", "set", or "unset". */
		if ((p = strtok(p, "\n\t ")) == NULL)
			err("missing field");
E 15

D 5
		ignore = 0;
E 5
		if (p[0] == '/')
			switch(p[1]) {
D 5
			case 'i':
				ignore = 1;
				if (!(p = strtok((char *)NULL, "\t ")))
					specerr();
				break;
E 5
			case 's':
				if (strcmp(p + 1, "set"))
					break;
D 5
				if (!(p = strtok((char *)NULL, "\t ")))
					specerr();
				set(p, &info, 1);
E 5
I 5
D 15
				set(&ginfo);
E 15
I 15
				set(NULL, &ginfo);
E 15
E 5
				continue;
			case 'u':
D 5
				if (strcmp(p + 1, "unset"))
E 5
I 5
D 14
				if (strncmp(p + 1, "unset"))
E 14
I 14
				if (strcmp(p + 1, "unset"))
E 14
E 5
					break;
D 5
				if (!(p = strtok((char *)NULL, "\t ")))
					specerr();
				unset(p, &info);
E 5
I 5
D 15
				unset(&ginfo);
E 15
I 15
				unset(NULL, &ginfo);
E 15
E 5
				continue;
			}

D 15
		if (index(p, '/')) {
			(void)fprintf(stderr,
			    "mtree: file names may not contain slashes.\n");
			specerr();
		}
E 15
I 15
		if (index(p, '/'))
			err("slash character in file name");
E 15

D 5
		if (!(info.flags&F_TYPE)) {
			(void)fprintf(stderr, "mtree: no type set.\n");
			specerr();
		}

E 5
		if (!strcmp(p, "..")) {
D 15
			/* don't go up, if haven't gone down */
E 15
I 15
			/* Don't go up, if haven't gone down. */
E 15
D 2
			if (last != root) {
				if (last->info.type != F_DIR ||
				    last->flags&F_DONE)
					last = last->parent;
				last->flags |= F_DONE;
				continue;
E 2
I 2
			if (!root)
D 15
				noparent();
E 15
I 15
				goto noparent;
E 15
D 9
			if (last->info.type != F_DIR || last->flags&F_DONE) {
E 9
I 9
			if (last->type != F_DIR || last->flags & F_DONE) {
E 9
				if (last == root)
D 15
					noparent();
E 15
I 15
					goto noparent;
E 15
				last = last->parent;
E 2
			}
D 2
			(void)fprintf(stderr, "mtree: no parent node.\n");
			specerr();
E 2
I 2
			last->flags |= F_DONE;
			continue;
I 15

noparent:		err("no parent node");
E 15
E 2
		}

D 6
		centry = (ENTRY *)emalloc(sizeof(ENTRY));
		if (!(centry->name = strdup(p)))
			nomem();
E 6
I 6
D 9
		centry = emalloc(sizeof(ENTRY) + strlen(p));
E 9
I 9
D 15
		centry = emalloc(sizeof(NODE) + strlen(p));
E 15
I 15
		if ((centry = calloc(1, sizeof(NODE) + strlen(p))) == NULL)
			err("%s", strerror(errno));
E 15
		*centry = ginfo;
E 9
		(void)strcpy(centry->name, p);
#define	MAGIC	"?*["
		if (strpbrk(p, MAGIC))
			centry->flags |= F_MAGIC;
E 6
D 5
		centry->info = info;
		centry->info.st_mode = info.type == F_DIR ? dmode : fmode;
		centry->flags = ignore;
		while (p = strtok((char *)NULL, "\t "))
			set(p, &centry->info, 0);
E 5
I 5
D 9
		centry->info = ginfo;
		set(&centry->info);
E 9
I 9
D 15
		set(centry);
E 15
I 15
		set(NULL, centry);
E 15
E 9
E 5

		if (!root) {
			last = root = centry;
			root->parent = root;
D 2
		} else if (last->info.type == F_DIR &&
		    !(last->flags&F_DONE)) {
E 2
I 2
D 9
		} else if (last->info.type == F_DIR && !(last->flags&F_DONE)) {
E 9
I 9
		} else if (last->type == F_DIR && !(last->flags & F_DONE)) {
E 9
E 2
			centry->parent = last;
			last = last->child = centry;
		} else {
			centry->parent = last->parent;
I 5
			centry->prev = last;
E 5
			last = last->next = centry;
		}
	}
I 15
	return (root);
E 15
I 2
}

I 4
D 11
static
E 11
D 5
set(p, ip, override)
	register char *p;
E 5
I 5
D 15
set(ip)
E 15
I 15
static void
set(t, ip)
	char *t;
E 15
E 5
D 9
	INFO *ip;
E 9
I 9
	register NODE *ip;
E 9
D 5
	int override;
E 5
{
D 5
	extern mode_t dmode, fmode;
	int val;
	char *kw;
E 5
I 5
D 9
	int type;
	char *kw, *val;
E 9
I 9
	register int type;
	register char *kw, *val;
E 9
E 5
D 15
	gid_t getgroup();
	uid_t getowner();
	long atol(), strtol();
E 15
I 15
	struct group *gr;
	struct passwd *pw;
	mode_t *m;
I 17
	int value;
E 17
	char *ep;
E 15

D 5
	for (kw = p; *p && *p != '='; ++p);
	if (!*p)
		specerr();
	*p++ = '\0';
	ip->flags |= val = key(kw);

	switch(val) {
	case F_CKSUM:
		ip->cksum = atol(p);
		break;
	case F_DMODE:
		if (!override) {
			(void)fprintf(stderr,
			    "mtree: keyword dmode is global only.\n");
E 5
I 5
D 7
	while (kw = strtok((char *)NULL, "= \t\n,")) {
E 7
I 7
D 15
	while (kw = strtok((char *)NULL, "= \t\n")) {
E 7
		ip->flags |= type = key(kw);
D 7
		val = strtok((char *)NULL, "= \t\n,");
E 7
I 7
		val = strtok((char *)NULL, " \t\n");
E 7
		if (!val)
E 5
			specerr();
E 15
I 15
	for (; kw = strtok(t, "= \t\n"); t = NULL) {
D 17
		ip->flags |= type = parsekey(kw);
		if ((val = strtok(NULL, " \t\n")) == NULL)
E 17
I 17
		ip->flags |= type = parsekey(kw, &value);
		if (value && (val = strtok(NULL, " \t\n")) == NULL)
E 17
			err("missing value");
E 15
I 5
		switch(type) {
		case F_CKSUM:
D 15
			ip->cksum = atol(val);
E 15
I 15
			ip->cksum = strtoul(val, &ep, 10);
			if (*ep)
				err("invalid checksum %s", val);
E 15
			break;
D 15
		case F_GROUP:
			ip->st_gid = getgroup(val);
E 15
I 15
		case F_GID:
			ip->st_gid = strtoul(val, &ep, 10);
			if (*ep)
				err("invalid gid %s", val);
E 15
			break;
I 15
		case F_GNAME:
			if ((gr = getgrnam(val)) == NULL)
			    err("unknown group %s", val);
			ip->st_gid = gr->gr_gid;
			break;
E 15
		case F_IGN:
			/* just set flag bit */
			break;
D 7
		case F_MODE:
			ip->st_mode = (mode_t)strtol(val, (char **)NULL, 8);
E 7
I 7
D 15
		case F_MODE: {
D 8
			mode_t *set, *setmode();
E 8
I 8
			mode_t *m, *setmode();
E 8

D 8
			if (!(set = setmode(val))) {
E 8
I 8
			if (!(m = setmode(val))) {
E 8
				(void)fprintf(stderr,
				    "mtree: invalid file mode %s.\n", val);
				specerr();
			}
E 15
I 15
		case F_MODE:
			if ((m = setmode(val)) == NULL)
				err("invalid file mode %s", val);
E 15
D 8
			ip->st_mode = getmode(set, 0);
E 8
I 8
			ip->st_mode = getmode(m, 0);
E 8
E 7
			break;
I 7
D 15
		}
E 15
E 7
		case F_NLINK:
D 15
			ip->st_nlink = atoi(val);
E 15
I 15
			ip->st_nlink = strtoul(val, &ep, 10);
			if (*ep)
				err("invalid link count %s", val);
E 15
			break;
D 15
		case F_OWNER:
			ip->st_uid = getowner(val);
			break;
E 15
		case F_SIZE:
D 15
			ip->st_size = atol(val);
E 15
I 15
D 20
			ip->st_size = strtoul(val, &ep, 10);
E 20
I 20
			ip->st_size = strtouq(val, &ep, 10);
E 20
			if (*ep)
				err("invalid size %s", val);
E 15
			break;
		case F_SLINK:
D 15
			if (!(ip->slink = strdup(val)))
				nomem();
E 15
I 15
			if ((ip->slink = strdup(val)) == NULL)
				err("%s", strerror(errno));
E 15
			break;
I 12
		case F_TIME:
D 15
			ip->st_mtime = atol(val);
E 15
I 15
D 18
			ip->st_mtime = strtoul(val, &ep, 10);
E 18
I 18
			ip->st_mtimespec.ts_sec = strtoul(val, &ep, 10);
			if (*ep != '.')
				err("invalid time %s", val);
			val = ep + 1;
			ip->st_mtimespec.ts_nsec = strtoul(val, &ep, 10);
E 18
			if (*ep)
				err("invalid time %s", val);
E 15
			break;
E 12
		case F_TYPE:
			switch(*val) {
			case 'b':
				if (!strcmp(val, "block"))
					ip->type = F_BLOCK;
				break;
			case 'c':
				if (!strcmp(val, "char"))
					ip->type = F_CHAR;
				break;
			case 'd':
				if (!strcmp(val, "dir"))
					ip->type = F_DIR;
				break;
			case 'f':
				if (!strcmp(val, "file"))
					ip->type = F_FILE;
I 10
				if (!strcmp(val, "fifo"))
					ip->type = F_FIFO;
E 10
				break;
			case 'l':
				if (!strcmp(val, "link"))
					ip->type = F_LINK;
				break;
			case 's':
				if (!strcmp(val, "socket"))
					ip->type = F_SOCK;
				break;
			default:
D 15
				(void)fprintf(stderr,
				    "mtree: unknown file type %s.\n", val);
				specerr();
E 15
I 15
				err("unknown file type %s", val);
E 15
			}
			break;
I 15
		case F_UID:
			ip->st_uid = strtoul(val, &ep, 10);
			if (*ep)
				err("invalid uid %s", val);
			break;
		case F_UNAME:
			if ((pw = getpwnam(val)) == NULL)
			    err("unknown user %s", val);
			ip->st_uid = pw->pw_uid;
			break;
E 15
E 5
		}
D 5
		dmode = (mode_t)strtol(p, (char **)NULL, 8);
		break;
	case F_FMODE:
		if (!override) {
			(void)fprintf(stderr,
			    "mtree: keyword fmode is global only.\n");
			specerr();
		}
		fmode = (mode_t)strtol(p, (char **)NULL, 8);
		break;
	case F_GROUP:
		ip->st_gid = getgroup(p);
		break;
	case F_MODE:
		if (override) {
			(void)fprintf(stderr,
			    "mtree: keyword mode is local only.\n");
			specerr();
		}
		ip->st_mode = (mode_t)strtol(p, (char **)NULL, 8);
		break;
	case F_NLINK:
		if ((ip->st_nlink = atoi(p)) <= 0)
			specerr();
		break;
	case F_OWNER:
		ip->st_uid = getowner(p);
		break;
	case F_SIZE:
		if ((ip->st_size = atol(p)) < 0)
			specerr();
		break;
	case F_SLINK:
		if (!(ip->slink = strdup(p)))
			nomem();
		break;
	case F_TYPE:
		ip->type = fkey(p);
		break;
E 5
	}
}

D 11
static
E 11
D 5
unset(p, ip)
	char *p;
	INFO *ip;
E 5
I 5
D 15
unset(ip)
E 15
I 15
static void
unset(t, ip)
	char *t;
E 15
D 9
	register INFO *ip;
E 9
I 9
	register NODE *ip;
E 9
E 5
{
D 5
	ip->flags &= !key(p);
E 5
I 5
	register char *p;

D 7
	while (p = strtok((char *)NULL, "\n\t ,"))
E 7
I 7
D 15
	while (p = strtok((char *)NULL, "\n\t "))
E 7
		ip->flags &= ~key(p);
E 5
}

D 11
static
E 11
key(p)
	char *p;
{
	switch(*p) {
	case 'c':
		if (!strcmp(p, "cksum"))
			return(F_CKSUM);
		break;
D 5
	case 'd':
		if (!strcmp(p, "dmode"))
			return(F_DMODE);
		break;
	case 'f':
		if (!strcmp(p, "fmode"))
			return(F_FMODE);
		break;
E 5
	case 'g':
		if (!strcmp(p, "group"))
			return(F_GROUP);
		break;
I 5
	case 'i':
		if (!strcmp(p, "ignore"))
			return(F_IGN);
		break;
	case 'l':
		if (!strcmp(p, "link"))
			return(F_SLINK);
		break;
E 5
	case 'm':
		if (!strcmp(p, "mode"))
			return(F_MODE);
		break;
	case 'n':
		if (!strcmp(p, "nlink"))
			return(F_NLINK);
		break;
	case 'o':
		if (!strcmp(p, "owner"))
			return(F_OWNER);
		break;
	case 's':
		if (!strcmp(p, "size"))
			return(F_SIZE);
D 5
		if (!strcmp(p, "slink"))
			return(F_SLINK);
E 5
		break;
	case 't':
		if (!strcmp(p, "type"))
			return(F_TYPE);
I 12
		if (!strcmp(p, "time"))
			return(F_TIME);
E 12
		break;
	}
D 5
	(void)fprintf(stderr, "mtree: unknown keyword.\n");
E 5
I 5
	(void)fprintf(stderr, "mtree: unknown keyword %s.\n", p);
E 5
	specerr();
	/* NOTREACHED */
}

D 5
static
fkey(p)
	char *p;
{
	switch(*p) {
	case 'b':
		if (!strcmp(p, "block"))
			return(F_BLOCK);
		break;
	case 'c':
		if (!strcmp(p, "char"))
			return(F_CHAR);
		break;
	case 'd':
		if (!strcmp(p, "dir"))
			return(F_DIR);
		break;
	case 'f':
		if (!strcmp(p, "file"))
			return(F_FILE);
		break;
	case 'l':
		if (!strcmp(p, "link"))
			return(F_LINK);
		break;
	case 's':
		if (!strcmp(p, "socket"))
			return(F_SOCK);
		break;
	}
	(void)fprintf(stderr, "mtree: unknown file type.\n");
	specerr();
	/* NOTREACHED */
}
E 5

D 11
static uid_t
E 11
I 11
uid_t
E 11
getowner(p)
	register char *p;
{
	struct passwd *pw;
	int val;

	if (isdigit(*p)) {
		if ((val = atoi(p)) >= 0)
			return((uid_t)val);
		(void)fprintf(stderr, "mtree: illegal uid value %s.\n", p);
	} else if (pw = getpwnam(p))
		return(pw->pw_uid);
	else
		(void)fprintf(stderr, "mtree: unknown user %s.\n", p);
	specerr();
	/* NOTREACHED */
}

D 11
static gid_t
E 11
I 11
gid_t
E 11
getgroup(p)
	register char *p;
{
	struct group *gr;
	int val;

	if (isdigit(*p)) {
		if ((val = atoi(p)) >= 0)
			return((gid_t)val);
		(void)fprintf(stderr, "mtree: illegal gid value %s.\n", p);
	} else if (gr = getgrnam(p))
		return(gr->gr_gid);
	else
		(void)fprintf(stderr, "mtree: unknown group %s.\n", p);
	specerr();
	/* NOTREACHED */
}

D 11
static
E 11
E 4
noparent()
{
	(void)fprintf(stderr, "mtree: no parent node.\n");
	specerr();
I 4
}

D 11
static
E 11
specerr()
{
	(void)fprintf(stderr,
	    "mtree: line %d of the specification is incorrect.\n", lineno);
I 5
	exit(1);
}

D 6
static void *
E 6
I 6
D 9
static ENTRY *
E 9
I 9
D 11
static NODE *
E 11
I 11
NODE *
E 11
E 9
E 6
emalloc(size)
	int size;
{
	void *p;

	/* NOSTRICT */
	if (!(p = malloc((u_int)size)))
		nomem();
	bzero(p, size);
D 6
	return(p);
E 6
I 6
D 9
	return((ENTRY *)p);
E 9
I 9
	return((NODE *)p);
E 9
E 6
}

D 11
static
E 11
nomem()
{
	(void)fprintf(stderr, "mtree: %s.\n", strerror(ENOMEM));
E 5
	exit(1);
E 15
I 15
	while (p = strtok(t, "\n\t "))
D 17
		ip->flags &= ~parsekey(p);
E 17
I 17
		ip->flags &= ~parsekey(p, NULL);
E 17
E 15
E 4
E 2
}
E 1
