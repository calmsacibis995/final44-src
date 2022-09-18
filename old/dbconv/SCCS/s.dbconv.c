h19896
s 00001/00002/00087
d D 5.2 91/11/19 14:40:07 bostic 2 1
c new db routine interface
e
s 00089/00000/00000
d D 5.1 91/02/14 14:48:53 bostic 1 0
c date and time created 91/02/14 14:48:53 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ndbm.h>
#include <errno.h>
#include <stdio.h>

main(argc, argv)
	int argc;
	char **argv;
{
	extern int optind;
	DB *db;
	DBM *dbm;
	DBT t_key, t_data;
	datum f_key, f_data;
	int ch, dup, rec;

	while ((ch = getopt(argc, argv, "")) != EOF)
		switch((char)ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	dbm = dbm_open(*argv, O_RDONLY, 0);
	if (!dbm)
		error(*argv);
D 2
	db = hash_open(*++argv, O_CREAT|O_WRONLY, DEFFILEMODE,
	    (HASHINFO *)NULL);
E 2
I 2
	db = dbopen(*++argv, O_CREAT|O_WRONLY, DEFFILEMODE, DB_HASH, NULL);
E 2
	if (!db)
		error(*argv);

	dup = rec = 0;
	for (f_key = dbm_firstkey(dbm); f_key.dptr; f_key = dbm_nextkey(dbm)) {
		f_data = dbm_fetch(dbm, f_key);
		t_key.data = f_key.dptr;
		t_key.size = f_key.dsize;
		t_data.data = f_data.dptr;
		t_data.size = f_data.dsize;
		switch((db->put)(db, &t_key, &t_data, R_NOOVERWRITE)) {
		case -1:
			error(*argv);
		case 0:
			++rec;
			break;
		case 1:
			if (!dup++)
				(void)fprintf(stderr,
				    "dbconv: duplicate records discarded\n");
			break;
		}
	}
	(void)(db->close)(db);
	(void)printf("%d records, %d duplicates discarded.\n", rec + dup, dup);
	exit(dup ? 1 : 0);
}

error(p)
	char *p;
{
	(void)fprintf(stderr, "dbconv: %s: %s\n", p, strerror(errno));
	exit(1);
}

usage()
{
	(void)fprintf(stderr, "usage: dbconv from to\n");
	exit(1);
}
E 1
