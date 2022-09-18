h60679
s 00002/00002/00073
d D 8.1 93/06/06 22:10:48 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00067
d D 5.5 91/04/24 17:33:47 bostic 5 4
c new copyright; att/bsd/shared
e
s 00000/00001/00068
d D 5.4 91/03/02 13:14:07 bostic 4 3
c ANSI
e
s 00012/00010/00057
d D 5.3 85/06/19 19:27:24 bloom 3 2
c fixes from rick adams
e
s 00008/00012/00059
d D 5.2 85/01/22 14:08:36 ralph 2 1
c bug fixes and changes from Rick Adams
e
s 00071/00000/00000
d D 5.1 83/07/02 17:56:57 sam 1 0
c date and time created 83/07/02 17:56:57 by sam
e
u
U
t
T
I 5
/*-
D 6
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
 */

E 5
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif
E 5
I 5
#endif /* not lint */
E 5

#include "uucp.h"
#include <pwd.h>

D 3
/*******
 *	guinfo(uid, name, path)	get passwd file info for uid
 *	int uid;
 *	char *path, *name;
E 3
I 3
/*LINTLIBRARY*/

/*
 *	get passwd file info for uid
E 3
 *
D 3
 *	return codes:  0  |  FAIL
E 3
I 3
 *	return codes:  SUCCESS  |  FAIL
E 3
 *
D 3
 *	modified 3/16/81 to use the "real" login name -- mcnc!dennis
 *						(Dennis Rockwell)
E 3
 */

guinfo(uid, name, path)
int uid;
register char *path, *name;
{
	register struct passwd *pwd;
D 4
	struct passwd *getpwuid(), *getpwnam();
E 4
D 3
	char *getlogin(), *l;
E 3
I 3
	char *getlogin(), *getenv(), *l;
E 3

D 3
	if ((l = getlogin()) != NULL) {
E 3
I 3
	if ((l = getlogin()) == NULL) {
		l = getenv("USER");
	}
	if (l != NULL) {
E 3
		pwd = getpwnam(l);
D 2
		if (pwd->pw_uid == uid)
E 2
I 2
D 3
		if (pwd->pw_uid == uid || *l == 'U')
E 3
I 3
		if (pwd != NULL && pwd->pw_uid == uid)
E 3
E 2
			goto setup;
	}
	if ((pwd = getpwuid(uid)) == NULL) {
		/* can not find uid in passwd file */
I 3
		*name = '\0';
E 3
		*path = '\0';
D 2
		return(FAIL);
E 2
I 2
		return FAIL;
E 2
	}

    setup:
	strcpy(path, pwd->pw_dir);
	strcpy(name, pwd->pw_name);
D 2
	return(0);
E 2
I 2
	return SUCCESS;
E 2
}


D 2
/***
 *	gninfo(name, uid, path)	get passwd file info for name
 *	char *path, *name;
 *	int *uid;
E 2
I 2
/*
 *	get passwd file info for name
E 2
 *
D 2
 *	return codes:  0  |  FAIL
E 2
I 2
 *	return codes:  SUCCESS  |  FAIL
E 2
 */

gninfo(name, uid, path)
char *path, *name;
int *uid;
{
	register struct passwd *pwd;
	struct passwd *getpwnam();

	if ((pwd = getpwnam(name)) == NULL) {
		/* can not find name in passwd file */
		*path = '\0';
D 2
		return(FAIL);
E 2
I 2
		return FAIL;
E 2
	}

	strcpy(path, pwd->pw_dir);
	*uid = pwd->pw_uid;
D 2
	return(0);
E 2
I 2
	return SUCCESS;
E 2
}
D 2


E 2
E 1
