h58444
s 00002/00002/00134
d D 8.1 93/06/06 11:40:13 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00135
d D 5.4 92/02/09 08:48:21 pendry 4 3
c merge in new release
e
s 00003/00002/00133
d D 5.3 91/05/12 15:55:34 pendry 3 2
c checkpoint for network tape
e
s 00006/00002/00129
d D 5.2 91/03/17 13:33:23 pendry 2 1
c from amd5.3 alpha11
e
s 00131/00000/00000
d D 5.1 90/06/29 12:01:07 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: info_passwd.c,v 5.2 90/06/23 22:19:34 jsp Rel $
E 2
I 2
D 3
 * $Id: info_passwd.c,v 5.2.1.2 91/03/03 20:39:38 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: info_passwd.c,v 5.2.1.3 91/05/07 22:18:02 jsp Alpha $
E 4
I 4
 * $Id: info_passwd.c,v 5.2.2.1 1992/02/09 15:08:33 jsp beta $
E 4
 *
E 3
 */

/*
 * Get info from password "file"
 *
 * This is experimental and probably doesn't
 * do what you expect.
 */

#include "am.h"

#ifdef HAS_PASSWD_MAPS
#include <pwd.h>

#define	PASSWD_MAP	"/etc/passwd"

/*
 * Nothing to probe - check the map name is PASSWD_MAP.
 */
D 2
passwd_init(map)
E 2
I 2
int passwd_init P((char *map, time_t *tp));
int passwd_init(map, tp)
E 2
char *map;
I 2
time_t *tp;
E 2
{
I 2
	*tp = 0;
E 2
	return strcmp(map, PASSWD_MAP) == 0 ? 0 : ENOENT;
}


/*
 * Grab the entry via the getpwname routine
 * Modify time is ignored by passwd - XXX
 */
I 2
int passwd_search P((mnt_map *m, char *map, char *key, char **pval, time_t *tp));
E 2
int passwd_search(m, map, key, pval, tp)
mnt_map *m;
char *map;
char *key;
char **pval;
time_t *tp;
{
	char *dir = 0;
	struct passwd *pw;
	if (strcmp(key, "/defaults") == 0) {
		*pval = strdup("type:=nfs");
		return 0;
	}

	pw = getpwnam(key);
	if (pw) {
		/*
		 * We chop the home directory up as follows:
		 * /anydir/dom1/dom2/dom3/user
		 *
		 * and return
		 * rfs:=/anydir/dom3;rhost:=dom3.dom2.dom1;sublink:=user
		 *
		 * This allows cross-domain entries in your passwd file.
		 * ... but forget about security!
		 */
		char *user;
		char *p, *q;
		char val[MAXPATHLEN];
		char rhost[MAXHOSTNAMELEN];
		dir = strdup(pw->pw_dir);
		/*
		 * Find user name.  If no / then Invalid...
		 */
		user = strrchr(dir, '/');
		if (!user)
			goto enoent;
		*user++ = '\0';
		/*
		 * Find start of host "path".  If no / then Invalid...
		 */ 
		p = strchr(dir+1, '/');
		if (!p)
			goto enoent;
		*p++ = '\0';
		/*
		 * At this point, p is dom1/dom2/dom3
		 * Copy, backwards, into rhost replacing
		 * / with .
		 */
		rhost[0] = '\0';
		do {
			q = strrchr(p, '/');
			if (q) {
				strcat(rhost, q + 1);
				strcat(rhost, ".");
				*q = '\0';
			} else {
				strcat(rhost, p);
			}
		} while (q);
		/*
		 * Sanity check
		 */
		if (*rhost == '\0' || *user == '\0' || *dir == '\0')
			goto enoent;
		/*
		 * Make up return string
		 */
		q = strchr(rhost, '.');
		if (q)
			*q = '\0';
		sprintf(val, "rfs:=%s/%s;rhost:=%s;sublink:=%s;fs:=${autodir}%s",
			dir, rhost, rhost, user, pw->pw_dir);
		if (q)
			*q = '.';
		*pval = strdup(val);
		return 0;
	}

enoent:
	if (dir)
		free(dir);

	return ENOENT;
}
#endif /* HAS_PASSWD_MAPS */
E 1
