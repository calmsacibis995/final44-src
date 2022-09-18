h23495
s 00002/00002/00329
d D 8.3 95/04/28 17:36:39 bostic 22 21
c use memmove, not memcpy
e
s 00019/00043/00312
d D 8.2 95/04/28 17:35:57 bostic 21 20
c You may have already done the same (does the Alpha have alignment
c constraints? I think it does...).  I also changed it to use the libc
c err, instead of its own, and fixed most of the `gcc -Wall' complaints.
c The important changes are to memcpy the pointers from db->get and db->seq.
c From: Chris Torek <torek@BSDI.COM>
e
s 00002/00002/00353
d D 8.1 93/06/06 14:39:31 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00004/00344
d D 5.19 92/03/06 13:51:40 bostic 19 18
c last change broke loose matching
e
s 00004/00002/00344
d D 5.18 91/10/27 16:15:25 bostic 18 17
c use btree instead of hashing, don't have to resort later
e
s 00002/00002/00344
d D 5.17 91/09/23 16:07:01 bostic 17 16
c hash_open -> dbopen; R_PUT no longer required
e
s 00098/00100/00248
d D 5.16 91/07/27 17:59:20 bostic 16 15
c finger really didn't need its own hashing scheme
e
s 00052/00012/00296
d D 5.15 91/07/27 15:58:27 bostic 15 14
c Welcome to the Wonderful World of ANSI!
e
s 00001/00001/00307
d D 5.14 91/01/17 10:24:48 bostic 14 13
c don't die if tty unstatable; 4.3BSD-reno/usr.bin/9
e
s 00001/00001/00307
d D 5.13 90/06/24 23:27:34 bostic 13 12
c don't need pathnames.h, just paths.h
e
s 00001/00011/00307
d D 5.12 90/06/01 16:49:59 bostic 12 11
c new copyright notice
e
s 00001/00001/00317
d D 5.11 90/05/15 19:57:17 bostic 11 10
c string.h is ANSI C include file
e
s 00002/00002/00316
d D 5.10 90/05/10 17:54:04 marc 10 9
c max size of field is 1024, not 256
e
s 00008/00008/00310
d D 5.9 90/05/10 17:09:43 marc 9 8
c new strsep semantics
e
s 00000/00000/00318
d D 5.8 90/02/07 08:25:20 bostic 8 7
x 4
c exclude sccs changes to remove contrib line from copyright
e
s 00006/00003/00309
d D 5.7 89/08/14 17:51:58 bostic 7 6
c leave NULL if gecos field is ",,,"
e
s 00047/00000/00265
d D 5.6 89/05/18 11:29:35 bostic 6 5
c print out certain types of phone numbers in US formats
e
s 00002/00003/00263
d D 5.5 89/05/08 13:04:15 edward 5 4
c fd (in enter_lastlog()) needs to be static too
e
s 00000/00003/00266
d D 5.4 89/05/08 11:36:09 bostic 4 3
c clean up copyright notice
e
s 00014/00016/00255
d D 5.3 89/05/08 10:25:25 bostic 3 2
c don't read/seek lastlog if can't open the file
e
s 00144/00026/00127
d D 5.2 89/05/07 01:02:58 edward 2 1
c show last login time if more recent than current logins,
c cleaned up, speeded up, put people in hash table, separate login info
c from personal info
e
s 00153/00000/00000
d D 5.1 89/05/06 13:53:36 bostic 1 0
c Tony Nardo (trn@warper.jhuapl.edu) reworked the original, I
c redid his stuff; should handle multiple logons right.
e
u
U
t
T
I 1
/*
D 20
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 4
 * This code is derived from software contributed to Berkeley by
 * Tony Nardo of the Johns Hopkins University/Applied Physics Lab.
 *
E 4
D 12
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>
D 15
#include <sys/file.h>
E 15
I 15
#include <fcntl.h>
I 16
#include <db.h>
I 21
#include <err.h>
E 21
E 16
#include <pwd.h>
#include <utmp.h>
#include <errno.h>
#include <unistd.h>
E 15
#include <stdio.h>
#include <ctype.h>
I 15
#include <stdlib.h>
E 15
D 11
#include <strings.h>
E 11
I 11
#include <string.h>
I 13
#include <paths.h>
E 13
E 11
#include "finger.h"
D 13
#include "pathnames.h"
E 13

I 15
static void	 find_idle_and_ttywrite __P((WHERE *));
D 16
static int	 hash __P((char *));
E 16
static void	 userinfo __P((PERSON *, struct passwd *));
static WHERE	*walloc __P((PERSON *));

I 18
int
E 18
D 16
static void
E 15
D 2
find_idle_and_ttywrite(pn)
	register PERSON *pn;
E 2
I 2
find_idle_and_ttywrite(w)
	register WHERE *w;
E 2
{
	extern time_t now;
D 15
	extern int errno;
E 15
	struct stat sb;
D 15
	char *strerror();
E 15

D 2
	(void)sprintf(tbuf, "%s/%s", _PATH_DEV, pn->tty);
E 2
I 2
D 15
	(void)sprintf(tbuf, "%s/%s", _PATH_DEV, w->tty);
E 15
I 15
	(void)snprintf(tbuf, sizeof(tbuf), "%s/%s", _PATH_DEV, w->tty);
E 15
E 2
	if (stat(tbuf, &sb) < 0) {
		(void)fprintf(stderr,
		    "finger: %s: %s\n", tbuf, strerror(errno));
D 14
		exit(1);
E 14
I 14
		return;
E 14
	}
D 2
	pn->idletime = now < sb.st_atime ? 0 : now - sb.st_atime;
E 2
I 2
	w->idletime = now < sb.st_atime ? 0 : now - sb.st_atime;
E 2

#define	TALKABLE	0220		/* tty is writable if 220 mode */
D 2
	pn->writable = ((sb.st_mode & TALKABLE) == TALKABLE);
E 2
I 2
	w->writable = ((sb.st_mode & TALKABLE) == TALKABLE);
E 2
}

I 15
static void
E 15
userinfo(pn, pw)
	register PERSON *pn;
	register struct passwd *pw;
{
	register char *p, *t;
D 9
	char name[256];
E 9
I 9
D 10
	char *bp, name[256];
E 10
I 10
	char *bp, name[1024];
E 10
E 9

	pn->realname = pn->office = pn->officephone = pn->homephone = NULL;

	pn->uid = pw->pw_uid;
	pn->name = strdup(pw->pw_name);
	pn->dir = strdup(pw->pw_dir);
	pn->shell = strdup(pw->pw_shell);

	/* why do we skip asterisks!?!? */
D 9
	(void)strcpy(p = tbuf, pw->pw_gecos);
	if (*p == '*')
		++p;
E 9
I 9
	(void)strcpy(bp = tbuf, pw->pw_gecos);
	if (*bp == '*')
		++bp;
E 9

	/* ampersands get replaced by the login name */
D 9
	if (!(p = strsep(p, ",")))
E 9
I 9
	if (!(p = strsep(&bp, ",")))
E 9
		return;
	for (t = name; *t = *p; ++p)
		if (*t == '&') {
			(void)strcpy(t, pw->pw_name);
			if (islower(*t))
				*t = toupper(*t);
			while (*++t);
		}
		else
			++t;
	pn->realname = strdup(name);
D 7
	pn->office = (p = strsep((char *)NULL, ",")) ? strdup(p) : NULL;
	pn->officephone = (p = strsep((char *)NULL, ",")) ? strdup(p) : NULL;
	pn->homephone = (p = strsep((char *)NULL, ",")) ? strdup(p) : NULL;
E 7
I 7
D 9
	pn->office = ((p = strsep((char *)NULL, ",")) && *p) ?
E 9
I 9
	pn->office = ((p = strsep(&bp, ",")) && *p) ?
E 9
	    strdup(p) : NULL;
D 9
	pn->officephone = ((p = strsep((char *)NULL, ",")) && *p) ?
E 9
I 9
	pn->officephone = ((p = strsep(&bp, ",")) && *p) ?
E 9
	    strdup(p) : NULL;
D 9
	pn->homephone = ((p = strsep((char *)NULL, ",")) && *p) ?
E 9
I 9
	pn->homephone = ((p = strsep(&bp, ",")) && *p) ?
E 9
	    strdup(p) : NULL;
E 7
}

E 16
match(pw, user)
	struct passwd *pw;
	char *user;
{
	register char *p, *t;
D 10
	char name[256];
E 10
I 10
	char name[1024];
E 10

D 19
	/* why do we skip asterisks!?!? */
E 19
I 19
	if (!strcasecmp(pw->pw_name, user))
		return(1);

	/*
	 * XXX
	 * Why do we skip asterisks!?!?
	 */
E 19
	(void)strcpy(p = tbuf, pw->pw_gecos);
	if (*p == '*')
		++p;

D 19
	/* ampersands get replaced by the login name */
	if (!(p = strtok(p, ",")))
E 19
I 19
	/* Ampersands get replaced by the login name. */
	if ((p = strtok(p, ",")) == NULL)
E 19
		return(0);
I 19

E 19
D 21
	for (t = name; *t = *p; ++p)
E 21
I 21
	for (t = name; (*t = *p) != '\0'; ++p)
E 21
		if (*t == '&') {
			(void)strcpy(t, pw->pw_name);
			while (*++t);
		}
		else
			++t;
D 19
	for (t = name; p = strtok(t, "\t "); t = (char *)NULL)
E 19
I 19
D 21
	for (t = name; p = strtok(t, "\t "); t = NULL)
E 21
I 21
	for (t = name; (p = strtok(t, "\t ")) != NULL; t = NULL)
E 21
E 19
		if (!strcasecmp(p, user))
			return(1);
	return(0);
}

I 15
void
E 15
D 2
find_when(pn)
E 2
I 2
enter_lastlog(pn)
E 2
	register PERSON *pn;
{
I 2
	register WHERE *w;
E 2
D 3
	static int fd;
E 3
I 3
D 5
	static int opened;
E 5
I 5
	static int opened, fd;
E 5
E 3
	struct lastlog ll;
I 3
D 5
	int fd;
E 5
E 3
I 2
	char doit = 0;
E 2
D 15
	off_t lseek();
E 15

D 2
	if (!fd && (fd = open(_PATH_LASTLOG, O_RDONLY, 0)) < 0) {
		(void)fprintf(stderr,
		    "finger: %s: open error\n", _PATH_LASTLOG);
		exit(1);
E 2
I 2
D 3
	/*
	 * Some systems may choose not to keep lastlog,
	 * so we don't report any errors.
	 * Not only that, we leave fd at -1 so lseek and read
	 * will fail and act like there were no last logins.
	 * Not the fastest way to do it, but what the hell.
	 */
	if (fd == 0)
		fd = open(_PATH_LASTLOG, O_RDONLY, 0);
	(void) lseek(fd, (long) (pn->uid * sizeof ll), L_SET);
	if (read(fd, (char *)&ll, sizeof ll) != sizeof ll) {
		/* same as never logged in */
		ll.ll_line[0] = 0;
		ll.ll_host[0] = 0;
		ll.ll_time = 0;
E 3
I 3
	/* some systems may not maintain lastlog, don't report errors. */
	if (!opened) {
		fd = open(_PATH_LASTLOG, O_RDONLY, 0);
		opened = 1;
E 3
E 2
	}
I 3
	if (fd == -1 ||
D 15
	    lseek(fd, (long)pn->uid * sizeof(ll), L_SET) !=
E 15
I 15
	    lseek(fd, (long)pn->uid * sizeof(ll), SEEK_SET) !=
E 15
	    (long)pn->uid * sizeof(ll) ||
	    read(fd, (char *)&ll, sizeof(ll)) != sizeof(ll)) {
			/* as if never logged in */
			ll.ll_line[0] = ll.ll_host[0] = NULL;
			ll.ll_time = 0;
		}
E 3
D 2
	(void)lseek(fd, (long)(pn->uid * (sizeof(ll))), L_SET);
	if (read(fd, (char *)&ll, sizeof(ll)) != sizeof(ll)) {
		(void)fprintf(stderr,
		    "finger: %s: read error\n", _PATH_LASTLOG);
		exit(1);
E 2
I 2
	if ((w = pn->whead) == NULL)
		doit = 1;
D 5
	else {
E 5
I 5
	else if (ll.ll_time != 0) {
E 5
		/* if last login is earlier than some current login */
		for (; !doit && w != NULL; w = w->next)
			if (w->info == LOGGEDIN && w->loginat < ll.ll_time)
				doit = 1;
		/*
		 * and if it's not any of the current logins
		 * can't use time comparison because there may be a small
		 * discrepency since login calls time() twice
		 */
		for (w = pn->whead; doit && w != NULL; w = w->next)
			if (w->info == LOGGEDIN &&
			    strncmp(w->tty, ll.ll_line, UT_LINESIZE) == 0)
				doit = 0;
E 2
	}
D 2
	bcopy(ll.ll_line, pn->tty, UT_LINESIZE);
	pn->tty[UT_LINESIZE] = NULL;
	bcopy(ll.ll_host, pn->host, UT_HOSTSIZE);
	pn->host[UT_HOSTSIZE] = NULL;
	pn->loginat = ll.ll_time;
E 2
I 2
	if (doit) {
		w = walloc(pn);
		w->info = LASTLOG;
		bcopy(ll.ll_line, w->tty, UT_LINESIZE);
		w->tty[UT_LINESIZE] = 0;
		bcopy(ll.ll_host, w->host, UT_HOSTSIZE);
		w->host[UT_HOSTSIZE] = 0;
		w->loginat = ll.ll_time;
	}
E 2
}

I 15
void
E 15
D 2
utcopy(ut, pn)
E 2
I 2
enter_where(ut, pn)
E 2
	struct utmp *ut;
	PERSON *pn;
{
D 2
	bcopy(ut->ut_line, pn->tty, UT_LINESIZE);
	pn->tty[UT_LINESIZE] = 0;
	bcopy(ut->ut_host, pn->host, UT_HOSTSIZE);
	pn->host[UT_HOSTSIZE] = 0;
	pn->loginat = (time_t)ut->ut_time;
E 2
I 2
D 15
	register WHERE *w = walloc(pn);
E 15
I 15
	register WHERE *w;
E 15

I 15
	w = walloc(pn);
E 15
	w->info = LOGGEDIN;
	bcopy(ut->ut_line, w->tty, UT_LINESIZE);
	w->tty[UT_LINESIZE] = 0;
	bcopy(ut->ut_host, w->host, UT_HOSTSIZE);
	w->host[UT_HOSTSIZE] = 0;
	w->loginat = (time_t)ut->ut_time;
	find_idle_and_ttywrite(w);
}

PERSON *
enter_person(pw)
	register struct passwd *pw;
{
D 16
	register PERSON *pn, **pp;
E 16
I 16
D 18
	PERSON *pn;
E 18
	DBT data, key;
I 18
	PERSON *pn;
E 18
E 16

D 16
	for (pp = htab + hash(pw->pw_name);
	     *pp != NULL && strcmp((*pp)->name, pw->pw_name) != 0;
	     pp = &(*pp)->hlink)
		;
	if ((pn = *pp) == NULL) {
E 16
I 16
D 17
	if (db == NULL && (db = hash_open(NULL, O_RDWR, 0, NULL)) == NULL)
E 17
I 17
D 18
	if (db == NULL && (db = dbopen(NULL, O_RDWR, 0, DB_HASH, NULL)) == NULL)
E 18
I 18
	if (db == NULL &&
	    (db = dbopen(NULL, O_RDWR, 0, DB_BTREE, NULL)) == NULL)
E 18
E 17
D 21
		err("%s", strerror(errno));
E 21
I 21
		err(1, NULL);
E 21

	key.data = pw->pw_name;
	key.size = strlen(pw->pw_name);

D 21
	switch((*db->get)(db, &key, &data, 0)) {
E 21
I 21
	switch ((*db->get)(db, &key, &data, 0)) {
E 21
	case 0:
D 21
		return(*(PERSON **)data.data);
E 21
I 21
D 22
		memcpy(&pn, data.data, sizeof pn);
E 22
I 22
		memmove(&pn, data.data, sizeof pn);
E 22
		return (pn);
E 21
	default:
	case -1:
D 21
		err("db get: %s", strerror(errno));
E 21
I 21
		err(1, "db get");
E 21
		/* NOTREACHED */
	case 1:
		++entries;
E 16
		pn = palloc();
D 16
		entries++;
		if (phead == NULL)
			phead = ptail = pn;
		else {
			ptail->next = pn;
			ptail = pn;
		}
		pn->next = NULL;
		pn->hlink = NULL;
		*pp = pn;
E 16
		userinfo(pn, pw);
		pn->whead = NULL;
I 16

		data.size = sizeof(PERSON *);
		data.data = &pn;
D 17
		if ((*db->put)(db, &key, &data, R_PUT))
E 17
I 17
		if ((*db->put)(db, &key, &data, 0))
E 17
D 21
			err("%s", strerror(errno));
		return(pn);
E 21
I 21
			err(1, "db put");
		return (pn);
E 21
E 16
	}
D 16
	return(pn);
E 16
}

PERSON *
find_person(name)
	char *name;
{
D 16
	register PERSON *pn;
E 16
I 16
	register int cnt;
	DBT data, key;
I 21
	PERSON *p;
E 21
	char buf[UT_NAMESIZE + 1];
E 16

D 16
	/* name may be only UT_NAMESIZE long and not terminated */
	for (pn = htab[hash(name)];
	     pn != NULL && strncmp(pn->name, name, UT_NAMESIZE) != 0;
	     pn = pn->hlink)
		;
	return(pn);
}
E 16
I 16
	if (!db)
		return(NULL);
E 16

I 15
D 16
static
E 15
hash(name)
	register char *name;
{
	register int h, i;
E 16
I 16
	/* Name may be only UT_NAMESIZE long and not NUL terminated. */
	for (cnt = 0; cnt < UT_NAMESIZE && *name; ++name, ++cnt)
		buf[cnt] = *name;
	buf[cnt] = '\0';
	key.data = buf;
	key.size = cnt;
E 16

D 16
	h = 0;
	/* name may be only UT_NAMESIZE long and not terminated */
	for (i = UT_NAMESIZE; --i >= 0 && *name;)
		h = ((h << 2 | h >> HBITS - 2) ^ *name++) & HMASK;
	return(h);
E 16
I 16
D 21
	return((*db->get)(db, &key, &data, 0) ? NULL : *(PERSON **)data.data);
E 21
I 21
	if ((*db->get)(db, &key, &data, 0))
		return (NULL);
D 22
	memcpy(&p, data.data, sizeof p);
E 22
I 22
	memmove(&p, data.data, sizeof p);
E 22
	return (p);
E 21
E 16
}

PERSON *
palloc()
{
	PERSON *p;

D 15
	if ((p = (PERSON *)malloc((u_int) sizeof(PERSON))) == NULL) {
		(void)fprintf(stderr, "finger: out of space.\n");
		exit(1);
	}
E 15
I 15
	if ((p = malloc((u_int) sizeof(PERSON))) == NULL)
D 21
		err("%s", strerror(errno));
E 21
I 21
		err(1, NULL);
E 21
E 15
	return(p);
}

D 15
WHERE *
E 15
I 15
static WHERE *
E 15
walloc(pn)
	register PERSON *pn;
{
	register WHERE *w;

D 16
	if ((w = (WHERE *)malloc((u_int) sizeof(WHERE))) == NULL) {
		(void)fprintf(stderr, "finger: out of space.\n");
		exit(1);
	}
E 16
I 16
	if ((w = malloc((u_int) sizeof(WHERE))) == NULL)
D 21
		err("%s", strerror(errno));
E 21
I 21
		err(1, NULL);
E 21
E 16
	if (pn->whead == NULL)
		pn->whead = pn->wtail = w;
	else {
		pn->wtail->next = w;
		pn->wtail = w;
	}
	w->next = NULL;
	return(w);
E 2
}
I 6

char *
prphone(num)
	char *num;
{
	register char *p;
	int len;
	static char pbuf[15];

	/* don't touch anything if the user has their own formatting */
	for (p = num; *p; ++p)
		if (!isdigit(*p))
			return(num);
	len = p - num;
	p = pbuf;
	switch(len) {
	case 11:			/* +0-123-456-7890 */
		*p++ = '+';
		*p++ = *num++;
		*p++ = '-';
		/* FALLTHROUGH */
	case 10:			/* 012-345-6789 */
		*p++ = *num++;
		*p++ = *num++;
		*p++ = *num++;
		*p++ = '-';
		/* FALLTHROUGH */
	case 7:				/* 012-3456 */
		*p++ = *num++;
		*p++ = *num++;
		*p++ = *num++;
		break;
	case 5:				/* x0-1234 */
		*p++ = 'x';
		*p++ = *num++;
		break;
	default:
		return(num);
	}
	*p++ = '-';
	*p++ = *num++;
	*p++ = *num++;
	*p++ = *num++;
	*p++ = *num++;
	*p = '\0';
	return(pbuf);
I 16
}

static void
find_idle_and_ttywrite(w)
	register WHERE *w;
{
	extern time_t now;
	struct stat sb;

	(void)snprintf(tbuf, sizeof(tbuf), "%s/%s", _PATH_DEV, w->tty);
	if (stat(tbuf, &sb) < 0) {
D 21
		(void)fprintf(stderr,
		    "finger: %s: %s\n", tbuf, strerror(errno));
E 21
I 21
		warn(tbuf);
E 21
		return;
	}
	w->idletime = now < sb.st_atime ? 0 : now - sb.st_atime;

#define	TALKABLE	0220		/* tty is writable if 220 mode */
	w->writable = ((sb.st_mode & TALKABLE) == TALKABLE);
}

static void
userinfo(pn, pw)
	register PERSON *pn;
	register struct passwd *pw;
{
	register char *p, *t;
	char *bp, name[1024];

	pn->realname = pn->office = pn->officephone = pn->homephone = NULL;

	pn->uid = pw->pw_uid;
	pn->name = strdup(pw->pw_name);
	pn->dir = strdup(pw->pw_dir);
	pn->shell = strdup(pw->pw_shell);

	/* why do we skip asterisks!?!? */
	(void)strcpy(bp = tbuf, pw->pw_gecos);
	if (*bp == '*')
		++bp;

	/* ampersands get replaced by the login name */
	if (!(p = strsep(&bp, ",")))
		return;
D 21
	for (t = name; *t = *p; ++p)
E 21
I 21
	for (t = name; (*t = *p) != '\0'; ++p)
E 21
		if (*t == '&') {
			(void)strcpy(t, pw->pw_name);
			if (islower(*t))
				*t = toupper(*t);
			while (*++t);
		}
		else
			++t;
	pn->realname = strdup(name);
	pn->office = ((p = strsep(&bp, ",")) && *p) ?
	    strdup(p) : NULL;
	pn->officephone = ((p = strsep(&bp, ",")) && *p) ?
	    strdup(p) : NULL;
	pn->homephone = ((p = strsep(&bp, ",")) && *p) ?
	    strdup(p) : NULL;
E 16
I 15
D 21
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
	(void)fprintf(stderr, "finger: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 21
E 15
}
E 6
E 1
