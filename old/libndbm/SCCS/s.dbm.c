h55978
s 00001/00001/00109
d D 5.6 91/03/12 09:47:11 bostic 6 5
c ANSI
e
s 00001/00011/00109
d D 5.5 90/06/01 15:36:47 bostic 5 4
c new copyright notice
e
s 00016/00005/00104
d D 5.4 89/05/24 11:11:58 bostic 4 3
c done from scratch by Robert Elz; add Berkeley specific copyright
e
s 00002/00001/00107
d D 5.3 85/08/15 18:01:03 kre 3 2
c fix horrible bug (pointed out by Doug Kingston), was always
c assuming that 2nd attempt to open would fail!
e
s 00008/00002/00100
d D 5.2 85/06/26 14:37:52 bloom 2 1
c Add copyright
e
s 00102/00000/00000
d D 5.1 85/06/25 18:46:09 kre 1 0
c date and time created 85/06/25 18:46:09 by kre
e
u
U
t
T
I 2
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
 */

E 2
I 1
#ifndef lint
D 2
static char sccsid[] = "%Z% (Berkeley) %E%";
#endif
E 2
I 2
D 4
static char sccsid[] = "%W% (Berkeley) %E%";
#endif not lint
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4
E 2

#include	"dbm.h"

#define	NODB	((DBM *)0)

static DBM *cur_db = NODB;

static char no_db[] = "dbm: no open database\n";

dbminit(file)
	char *file;
{
	if (cur_db != NODB)
		dbm_close(cur_db);

	cur_db = dbm_open(file, 2, 0);
	if (cur_db == NODB) {
		cur_db = dbm_open(file, 0, 0);
D 3
		return (-1);
E 3
I 3
		if (cur_db == NODB)
			return (-1);
E 3
	}
	return (0);
}

long
forder(key)
datum key;
{
	if (cur_db == NODB) {
		printf(no_db);
		return (0L);
	}
	return (dbm_forder(cur_db, key));
}

datum
fetch(key)
datum key;
{
	datum item;

	if (cur_db == NODB) {
		printf(no_db);
		item.dptr = 0;
		return (item);
	}
	return (dbm_fetch(cur_db, key));
}

delete(key)
datum key;
{
	if (cur_db == NODB) {
		printf(no_db);
		return (-1);
	}
	if (dbm_rdonly(cur_db))
		return (-1);
	return (dbm_delete(cur_db, key));
}

store(key, dat)
datum key, dat;
{
	if (cur_db == NODB) {
		printf(no_db);
		return (-1);
	}
	if (dbm_rdonly(cur_db))
		return (-1);

	return (dbm_store(cur_db, key, dat, DBM_REPLACE));
}

datum
firstkey()
{
	datum item;

	if (cur_db == NODB) {
		printf(no_db);
		item.dptr = 0;
		return (item);
	}
	return (dbm_firstkey(cur_db));
}

datum
nextkey(key)
datum key;
{
	datum item;

	if (cur_db == NODB) {
		printf(no_db);
		item.dptr = 0;
		return (item);
	}
D 6
	return (dbm_nextkey(cur_db, key));
E 6
I 6
	return (dbm_nextkey(cur_db));
E 6
}
E 1
