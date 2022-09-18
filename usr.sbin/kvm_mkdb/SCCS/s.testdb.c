h10713
s 00002/00002/00085
d D 8.1 93/06/06 13:58:37 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00002/00081
d D 5.2 92/07/01 17:05:36 bostic 2 1
c off_t's are now quad's -- ANSI C says fseek/ftell use longs
e
s 00083/00000/00000
d D 5.1 92/05/04 17:04:12 bostic 1 0
c update from LBL (Chris, Craig and Steve)
c date and time created 92/05/04 17:04:12 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/file.h>
#include <errno.h>
#include <limits.h>
#include <kvm.h>
#include <db.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <paths.h>

#include "extern.h"

/* Return true if the db file is valid, else false */
int
testdb()
{
	register DB *db;
	register int cc, kd, ret, dbversionlen;
	register char *cp, *uf;
	DBT rec;
	struct nlist nitem;
	char dbname[MAXPATHLEN], dbversion[_POSIX2_LINE_MAX];
	char kversion[_POSIX2_LINE_MAX];

	ret = 0;
	db = NULL;

	if ((kd = open(_PATH_KMEM, O_RDONLY, 0)) < 0)
		goto close;

	uf = _PATH_UNIX;
	if ((cp = rindex(uf, '/')) != 0)
		uf = cp + 1;
	(void) snprintf(dbname, sizeof(dbname), "%skvm_%s.db", _PATH_VARDB, uf);
	if ((db = dbopen(dbname, O_RDONLY, 0, DB_HASH, NULL)) == NULL)
		goto close;

	/* Read the version out of the database */
	rec.data = VRS_KEY;
	rec.size = sizeof(VRS_KEY) - 1;
	if ((db->get)(db, &rec, &rec, 0))
		goto close;
	if (rec.data == 0 || rec.size > sizeof(dbversion))
		goto close;
	bcopy(rec.data, dbversion, rec.size);
	dbversionlen = rec.size;

	/* Read version string from kernel memory */
	rec.data = VRS_SYM;
	rec.size = sizeof(VRS_SYM) - 1;
	if ((db->get)(db, &rec, &rec, 0))
		goto close;
	if (rec.data == 0 || rec.size != sizeof(struct nlist))
		goto close;
D 2
	bcopy((char *)rec.data, (char *)&nitem, sizeof(nitem));
E 2
I 2
	bcopy(rec.data, &nitem, sizeof(nitem));
	/*
	 * Theoretically possible for lseek to be seeking to -1.  Not
	 * that it's something to lie awake nights about, however.
	 */
E 2
	errno = 0;
D 2
	if (lseek(kd, (off_t)nitem.n_value, 0) == -1 && errno != 0)
E 2
I 2
	if (lseek(kd, (off_t)nitem.n_value, SEEK_SET) == -1 && errno != 0)
E 2
		goto close;
	cc = read(kd, kversion, sizeof(kversion));
	if (cc < 0 || cc != sizeof(kversion))
		goto close;

	/* If they match, we win */
	ret = bcmp(dbversion, kversion, dbversionlen) == 0;

close:	if (kd >= 0)
		(void)close(kd);
	if (db)
		(void)(db->close)(db);
	return (ret);
}
E 1
