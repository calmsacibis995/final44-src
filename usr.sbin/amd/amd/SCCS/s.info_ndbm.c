h55438
s 00002/00002/00095
d D 8.1 93/06/06 11:40:08 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00096
d D 5.4 92/02/09 08:48:17 pendry 4 3
c merge in new release
e
s 00003/00002/00094
d D 5.3 91/05/12 15:55:29 pendry 3 2
c checkpoint for network tape
e
s 00012/00002/00084
d D 5.2 91/03/17 13:33:20 pendry 2 1
c from amd5.3 alpha11
e
s 00086/00000/00000
d D 5.1 90/06/29 12:01:05 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: info_ndbm.c,v 5.2 90/06/23 22:19:31 jsp Rel $
E 2
I 2
D 3
 * $Id: info_ndbm.c,v 5.2.1.2 91/03/03 20:39:40 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
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
 * $Id: info_ndbm.c,v 5.2.1.3 91/05/07 22:18:00 jsp Alpha $
E 4
I 4
 * $Id: info_ndbm.c,v 5.2.2.1 1992/02/09 15:08:31 jsp beta $
E 4
 *
E 3
 */

/*
 * Get info from NDBM map
 */

#include "am.h"

#ifdef HAS_NDBM_MAPS

#include <ndbm.h>
#include <fcntl.h>
#include <sys/stat.h>

I 2
static int search_ndbm P((DBM *db, char *key, char **val));
E 2
static int search_ndbm(db, key, val)
DBM *db;
char *key;
char **val;
{
	datum k, v;
	k.dptr = key;
	k.dsize = strlen(key) + 1;
	v = dbm_fetch(db, k);
	if (v.dptr) {
		*val = strdup(v.dptr);
		return 0;
	}
	return ENOENT;
}

I 2
int ndbm_search P((mnt_map *m, char *map, char *key, char **pval, time_t *tp));
E 2
int ndbm_search(m, map, key, pval, tp)
mnt_map *m;
char *map;
char *key;
char **pval;
time_t *tp;
{
	DBM *db;

	db = dbm_open(map, O_RDONLY, 0);
	if (db) {
		struct stat stb;
		int error;
		error = fstat(dbm_pagfno(db), &stb);
		if (!error && *tp < stb.st_mtime) {
			*tp = stb.st_mtime;
			error = -1;
		} else {
			error = search_ndbm(db, key, pval);
		}
		(void) dbm_close(db);
		return error;
	}

	return errno;
}

D 2
int ndbm_init(map)
E 2
I 2
int ndbm_init P((char *map, time_t *tp));
int ndbm_init(map, tp)
E 2
char *map;
I 2
time_t *tp;
E 2
{
	DBM *db;

	db = dbm_open(map, O_RDONLY, 0);
	if (db) {
I 2
		struct stat stb;

		if (fstat(dbm_pagfno(db), &stb) < 0)
			*tp = clocktime();
		else
			*tp = stb.st_mtime;
E 2
		dbm_close(db);
		return 0;
	}

	return errno;
}

#endif /* HAS_NDBM_MAPS */
E 1
