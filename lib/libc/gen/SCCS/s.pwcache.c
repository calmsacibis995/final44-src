h51973
s 00002/00002/00084
d D 8.1 93/06/04 12:04:32 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00019/00067
d D 5.6 93/04/27 18:43:23 bostic 6 5
c move pwcache routines to libc from libutil
e
s 00001/00001/00085
d D 5.5 93/04/26 22:47:30 bostic 5 4
c off-by-one in group_from_gid; from Jeff Forys
e
s 00001/00011/00085
d D 5.4 90/06/01 15:49:10 bostic 4 3
c new copyright notice
e
s 00009/00004/00087
d D 5.3 90/03/13 12:07:48 bostic 3 2
c add nouser/nogroup flag so program can find out if failed
e
s 00011/00000/00080
d D 5.2 90/03/05 16:21:35 marc 2 1
c keep db files open
e
s 00080/00000/00000
d D 5.1 90/03/05 10:29:45 bostic 1 0
c date and time created 90/03/05 10:29:45 by bostic
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
D 6
#include <utmp.h>
#include <pwd.h>
E 6
I 6

E 6
#include <grp.h>
I 6
#include <pwd.h>
E 6
I 3
#include <stdio.h>
I 6
#include <utmp.h>
E 6
E 3

#define	NCACHE	64			/* power of 2 */
#define	MASK	NCACHE - 1		/* bits to store with */

I 2
D 6
static	int pwopen = 0;
static	int gropen = 0;

E 6
E 2
char *
D 3
user_from_uid(uid)
E 3
I 3
user_from_uid(uid, nouser)
E 3
	uid_t uid;
I 3
	int nouser;
E 3
{
	static struct ncache {
		uid_t	uid;
		char	name[UT_NAMESIZE + 1];
	} c_uid[NCACHE];
I 6
	static int pwopen;
E 6
	static char nbuf[15];		/* 32 bits == 10 digits */
	register struct passwd *pw;
	register struct ncache *cp;

	cp = c_uid + (uid & MASK);
	if (cp->uid != uid || !*cp->name) {
I 2
		if (pwopen == 0) {
			setpassent(1);
D 6
			pwopen++;
E 6
I 6
			pwopen = 1;
E 6
		}
E 2
D 3
		/* if can't find owner, use user id instead */
E 3
D 6
		if (!(pw = getpwuid(uid))) {
E 6
I 6
		if ((pw = getpwuid(uid)) == NULL) {
E 6
I 3
			if (nouser)
D 6
				return((char *)NULL);
E 3
			(void)sprintf(nbuf, "%u", uid);
			return(nbuf);
E 6
I 6
				return (NULL);
			(void)snprintf(nbuf, sizeof(nbuf), "%u", uid);
			return (nbuf);
E 6
		}
		cp->uid = uid;
		(void)strncpy(cp->name, pw->pw_name, UT_NAMESIZE);
		cp->name[UT_NAMESIZE] = '\0';
	}
D 6
	return(cp->name);
E 6
I 6
	return (cp->name);
E 6
}

char *
D 3
group_from_gid(gid)
E 3
I 3
group_from_gid(gid, nogroup)
E 3
	gid_t gid;
I 3
	int nogroup;
E 3
{
	static struct ncache {
		gid_t	gid;
D 5
		char	name[UT_NAMESIZE];
E 5
I 5
		char	name[UT_NAMESIZE + 1];
E 5
	} c_gid[NCACHE];
I 6
	static int gropen;
E 6
	static char nbuf[15];		/* 32 bits == 10 digits */
D 6
	register struct group *gr;
	register struct ncache *cp;
E 6
I 6
	struct group *gr;
	struct ncache *cp;
E 6

	cp = c_gid + (gid & MASK);
	if (cp->gid != gid || !*cp->name) {
I 2
		if (gropen == 0) {
			setgroupent(1);
D 6
			gropen++;
E 6
I 6
			gropen = 1;
E 6
		}
E 2
D 3
		/* if can't find group, use group id instead */
E 3
D 6
		if (!(gr = getgrgid(gid))) {
E 6
I 6
		if ((gr = getgrgid(gid)) == NULL) {
E 6
I 3
			if (nogroup)
D 6
				return((char *)NULL);
E 3
			(void)sprintf(nbuf, "%u", gid);
			return(nbuf);
E 6
I 6
				return (NULL);
			(void)snprintf(nbuf, sizeof(nbuf), "%u", gid);
			return (nbuf);
E 6
		}
		cp->gid = gid;
		(void)strncpy(cp->name, gr->gr_name, UT_NAMESIZE);
		cp->name[UT_NAMESIZE] = '\0';
	}
D 6
	return(cp->name);
E 6
I 6
	return (cp->name);
E 6
}
E 1
