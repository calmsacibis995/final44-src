h47482
s 00004/00228/00059
d D 5.3 90/05/22 12:58:46 bostic 3 2
c rearrange and make the world static
e
s 00001/00001/00286
d D 5.2 90/05/15 20:04:36 bostic 2 1
c string.h is ANSI C include file
e
s 00287/00000/00000
d D 5.1 89/09/04 16:24:57 bostic 1 0
c date and time created 89/09/04 16:24:57 by bostic
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
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
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
D 3
#include <sys/time.h>
#include <pwd.h>
#include <grp.h>
E 3
I 3
#include <errno.h>
E 3
#include <stdio.h>
D 3
#include <ctype.h>
E 3
D 2
#include <strings.h>
E 2
I 2
#include <string.h>
E 2
D 3
#include "mtree.h"
E 3
I 3
#include <stdlib.h>
E 3

D 3
set(p, ip, override)
	register char *p;
	INFO *ip;
	int override;
{
	extern mode_t dmode, fmode;
	int val;
	char *kw;
	gid_t getgroup();
	uid_t getowner();
	long atol(), strtol();

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
			specerr();
		}
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
	}
}

unset(p, ip)
	char *p;
	INFO *ip;
{
	ip->flags &= !key(p);
}

key(p)
	char *p;
{
	switch(*p) {
	case 'c':
		if (!strcmp(p, "cksum"))
			return(F_CKSUM);
		break;
	case 'd':
		if (!strcmp(p, "dmode"))
			return(F_DMODE);
		break;
	case 'f':
		if (!strcmp(p, "fmode"))
			return(F_FMODE);
		break;
	case 'g':
		if (!strcmp(p, "group"))
			return(F_GROUP);
		break;
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
		if (!strcmp(p, "slink"))
			return(F_SLINK);
		break;
	case 't':
		if (!strcmp(p, "type"))
			return(F_TYPE);
		break;
	}
	(void)fprintf(stderr, "mtree: unknown keyword.\n");
	specerr();
	/* NOTREACHED */
}

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

uid_t
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

gid_t
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

E 3
char *
rlink(name)
	char *name;
{
D 3
	extern int errno;
E 3
	extern char path[];
	int len;
	static char lbuf[MAXPATHLEN];

	len = readlink(name, lbuf, sizeof(lbuf));
	if (len == -1) {
		(void)fprintf(stderr, "mtree: %s: %s.\n",
		    path + 2, strerror(errno));
		exit(1);
	}
	lbuf[len] = '\0';
	return(lbuf);
}

D 3
headers()
{
	time_t clock, time();
	char curp[MAXPATHLEN], *ctime(), *getlogin();

	if (!getwd(curp)) {
		(void)fprintf(stderr, "mtree: %s\n", curp);
		exit(1);
	}
	(void)time(&clock);
	(void)printf("#\n#\t%s\n#\tby: %s\n#\t%s#\n",
	    curp, getlogin(), ctime(&clock));
}

specerr()
{
	extern int lineno;

	(void)fprintf(stderr,
	    "mtree: line %d of the specification is incorrect.\n", lineno);
	exit(1);
}

E 3
char *
emalloc(size)
	int size;
{
D 3
	char *p, *malloc();
E 3
I 3
	char *p;
E 3

	/* NOSTRICT */
	if (!(p = malloc((u_int)size)))
		nomem();
	bzero(p, size);
	return(p);
}

nomem()
{
D 3
	(void)fprintf(stderr, "mtree: no more memory.\n");
E 3
I 3
	(void)fprintf(stderr, "mtree: %s.\n", strerror(ENOMEM));
E 3
	exit(1);
}
E 1
