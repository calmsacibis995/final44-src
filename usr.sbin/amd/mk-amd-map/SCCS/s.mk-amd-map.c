h04649
s 00000/00000/00358
d D 8.1 93/06/28 08:12:20 bostic 13 12
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00356
d D 5.8 93/06/28 08:12:16 bostic 12 11
c make it work with -p, too
c From: Jan-Simon Pendry <pendry@vangogh.CS.Berkeley.EDU>
e
s 00000/00000/00357
d D 5.7 93/06/28 07:05:55 bostic 11 10
c 4.4BSD snapshot (revision 8.1)
e
s 00044/00009/00313
d D 5.6 93/06/28 07:05:47 bostic 10 5
c mk-amd-map wouldn't work with the new db library
c yank to 8.1 for the 4.4BSD release
c From: Jan-Simon Pendry <pendry@vangogh.CS.Berkeley.EDU>
e
s 00004/00004/00318
d R 8.1 93/06/07 20:18:54 bostic 9 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00318
d R 5.6 93/06/06 12:02:39 bostic 8 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00317
d R 8.1 93/06/06 12:01:47 bostic 7 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00317
d R 8.1 93/06/06 12:00:46 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00320
d D 5.5 92/02/09 08:45:53 pendry 5 4
c merge in new release
e
s 00005/00005/00317
d D 5.4 91/05/12 16:00:16 pendry 4 3
c checkpoint for network tape
e
s 00089/00067/00233
d D 5.3 91/03/17 13:47:09 pendry 3 2
c from amd5.3 alpha11
e
s 00003/00003/00297
d D 5.2 91/03/07 14:27:09 donn 2 1
c String constants are constant!
e
s 00300/00000/00000
d D 5.1 90/07/19 15:43:51 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 3
 * $Id: mk-amd-map.c,v 5.2 90/06/23 22:20:10 jsp Rel $
E 3
I 3
D 4
 * $Id: mk-amd-map.c,v 5.2.1.2 91/03/17 17:37:27 jsp Alpha $
E 3
 *
E 4
D 10
 * Copyright (c) 1990 Jan-Simon Pendry
E 10
I 10
 * Copyright (c) 1990, 1993 Jan-Simon Pendry
E 10
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 4
 *
D 5
 * $Id: mk-amd-map.c,v 5.2.1.4 91/05/07 22:18:47 jsp Alpha $
E 5
I 5
 * $Id: mk-amd-map.c,v 5.2.2.1 1992/02/09 15:09:18 jsp beta $
E 5
E 4
 */

/*
 * Convert a file map into an ndbm map
 */

#ifndef lint
char copyright[] = "\
D 10
@(#)Copyright (c) 1990 Jan-Simon Pendry\n\
E 10
I 10
@(#)Copyright (c) 1990, 1993 Jan-Simon Pendry\n\
E 10
@(#)Copyright (c) 1990 Imperial College of Science, Technology & Medicine\n\
D 10
@(#)Copyright (c) 1990 The Regents of the University of California.\n\
@(#)All rights reserved.\n";
E 10
I 10
@(#)Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 10
#endif /* not lint */

#ifndef lint
D 3
static char rcsid[] = "$Id: mk-amd-map.c,v 5.2 90/06/23 22:20:10 jsp Rel $";
E 3
I 3
D 4
static char rcsid[] = "$Id: mk-amd-map.c,v 5.2.1.2 91/03/17 17:37:27 jsp Alpha $";
E 4
I 4
D 5
static char rcsid[] = "$Id: mk-amd-map.c,v 5.2.1.4 91/05/07 22:18:47 jsp Alpha $";
E 5
I 5
static char rcsid[] = "$Id: mk-amd-map.c,v 5.2.2.1 1992/02/09 15:09:18 jsp beta $";
E 5
E 4
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "am.h"

D 3
#ifdef OS_HAS_GDBM
#define HAS_DATABASE
#include "gdbm.h"
#endif /* OS_HAS_GDBM */
E 3
I 3
#ifndef SIGINT
#include <signal.h>
#endif
E 3

D 3
#ifndef HAS_DATABASE
E 3
#ifdef OS_HAS_NDBM
#define HAS_DATABASE
D 3
#define	USE_NDBM
E 3
#include <ndbm.h>

D 10
#define create_database(name) dbm_open(name, O_RDWR|O_CREAT, 0444)
E 10
I 10
#ifdef DBM_SUFFIX
#define USING_DB
#endif
E 10

I 10
#define create_database(name) dbm_open(name, O_RDWR|O_CREAT, 0644)

E 10
static int store_data(db, k, v)
voidp db;
char *k, *v;
{
	datum key, val;

	key.dptr = k; val.dptr = v;
	key.dsize = strlen(k) + 1;
	val.dsize = strlen(v) + 1;
	return dbm_store((DBM *) db, key, val, DBM_INSERT);
}

#endif /* OS_HAS_NDBM */
D 3
#endif /* !OS_HAS_DATABASE */
E 3

#ifdef HAS_DATABASE
#include <fcntl.h>
#include <ctype.h>

static int read_line(buf, size, fp)
char *buf;
int size;
FILE *fp;
{
	int done = 0;

	do {
		while (fgets(buf, size, fp)) {
			int len = strlen(buf);
			done += len;
			if (len > 1 && buf[len-2] == '\\' &&
					buf[len-1] == '\n') {
				int ch;
				buf += len - 2;
				size -= len - 2;
I 4
				*buf = '\n'; buf[1] = '\0';
E 4
				/*
				 * Skip leading white space on next line
				 */
				while ((ch = getc(fp)) != EOF &&
					isascii(ch) && isspace(ch))
						;
				(void) ungetc(ch, fp);
			} else {
				return done;
			}
		}
	} while (size > 0 && !feof(fp));

	return done;
}

/*
 * Read through a map
 */
static int read_file(fp, map, db)
FILE *fp;
char *map;
voidp db;
{
	char key_val[2048];
	int chuck = 0;
	int line_no = 0;
	int errs = 0;

	while (read_line(key_val, sizeof(key_val), fp)) {
		char *kp;
		char *cp;
		char *hash;
		int len = strlen(key_val);
		line_no++;

		/*
		 * Make sure we got the whole line
		 */
		if (key_val[len-1] != '\n') {
			fprintf(stderr, "line %d in \"%s\" is too long", line_no, map);
			chuck = 1;
		} else {
			key_val[len-1] = '\0';
		}

		/*
		 * Strip comments
		 */
		hash = strchr(key_val, '#');
		if (hash)
			*hash = '\0';

		/*
		 * Find start of key
		 */
		for (kp = key_val; *kp && isascii(*kp) && isspace(*kp); kp++)
			;

		/*
		 * Ignore blank lines
		 */
		if (!*kp)
			goto again;

		/*
		 * Find end of key
		 */
		for (cp = kp; *cp&&(!isascii(*cp)||!isspace(*cp)); cp++)
			;

		/*
		 * Check whether key matches, or whether
		 * the entry is a wildcard entry.
		 */
		if (*cp)
			*cp++ = '\0';
		while (*cp && isascii(*cp) && isspace(*cp))
			cp++;
		if (*kp == '+') {
			fprintf(stderr, "Can't interpolate %s\n", kp);
			errs++;
		} else if (*cp) {
D 3
#ifdef DEBUG
			printf("%s\t%s\n", kp, cp);
#endif /* DEBUG */
			if (store_data(db, kp, cp) < 0) {
				fprintf(stderr, "Could store %s -> %s\n", kp, cp);
				errs++;
E 3
I 3
			if (db) {
				if (store_data(db, kp, cp) < 0) {
					fprintf(stderr, "Could store %s -> %s\n", kp, cp);
					errs++;
				}
			} else {
				printf("%s\t%s\n", kp, cp);
E 3
			}
		} else {
			fprintf(stderr, "%s: line %d has no value field", map, line_no);
			errs++;
		}

again:
		/*
		 * If the last read didn't get a whole line then
		 * throw away the remainder before continuing...
		 */
		if (chuck) {
			while (fgets(key_val, sizeof(key_val), fp) &&
				!strchr(key_val, '\n'))
					;
			chuck = 0;
		}
	}
	return errs;
}

D 2
static int remove(f)
E 2
I 2
D 3
static int xremove(f)
E 3
I 3
static int remove_file(f)
E 3
E 2
char *f;
{
	if (unlink(f) < 0 && errno != ENOENT)
		return -1;
	return 0;
}

main(argc, argv)
int argc;
char *argv[];
{
	FILE *mapf;
	char *map;
	int rc = 0;
	DBM *mapd;
D 2
	char *maptmp = "dbmXXXXXX";
E 2
I 2
D 3
	static char maptmp[] = "dbmXXXXXX";
E 3
I 3
D 4
	char *maptmp = "dbmXXXXXX";
E 4
I 4
	static char maptmp[] = "dbmXXXXXX";
E 4
E 3
E 2
D 10
	char maptpag[16], maptdir[16];
	char *mappag, *mapdir;
E 10
I 10
	char maptpag[16];
	char *mappag;
#ifndef USING_DB
	char maptdir[16];
	char *mapdir;
#endif
E 10
	int len;
	char *sl;
I 3
	int printit = 0;
	int usage = 0;
	int ch;
	extern int optind;
E 3

D 3
	if (argc != 2) {
		fputs("Usage: mk-amd-map file-map\n", stderr);
E 3
I 3
	while ((ch = getopt(argc, argv, "p")) != EOF)
	switch (ch) {
	case 'p':
		printit = 1;
		break;
	default:
		usage++;
		break;
	}

	if (usage || optind != (argc - 1)) {
		fputs("Usage: mk-amd-map [-p] file-map\n", stderr);
E 3
		exit(1);
	}

D 3
	map = argv[1];
E 3
I 3
	map = argv[optind];
E 3
	sl = strrchr(map, '/');
	if (sl) {
		*sl = '\0';
		if (chdir(map) < 0) {
			fputs("Can't chdir to ", stderr);
			perror(map);
			exit(1);
		}
		map = sl + 1;
	}
D 3
#ifdef USE_NDBM
	len = strlen(map);
	mappag = (char *) malloc(len + 5);
	mapdir = (char *) malloc(len + 5);
	if (!mappag || !mapdir) {
		perror("malloc");
		exit(1);
E 3
I 3

	if (!printit) {
		len = strlen(map);
I 10
#ifdef USING_DB
E 10
		mappag = (char *) malloc(len + 5);
I 10
		if (!mappag) {
			perror("mk-amd-map: malloc");
			exit(1);
		}
		mktemp(maptmp);
		sprintf(maptpag, "%s%s", maptmp, DBM_SUFFIX);
		if (remove_file(maptpag) < 0) {
			fprintf(stderr, "Can't remove existing temporary file");
			perror(maptpag);
			exit(1);
		}
#else
		mappag = (char *) malloc(len + 5);
E 10
		mapdir = (char *) malloc(len + 5);
		if (!mappag || !mapdir) {
			perror("mk-amd-map: malloc");
			exit(1);
		}
		mktemp(maptmp);
		sprintf(maptpag, "%s.pag", maptmp);
		sprintf(maptdir, "%s.dir", maptmp);
		if (remove_file(maptpag) < 0 || remove_file(maptdir) < 0) {
			fprintf(stderr, "Can't remove existing temporary files; %s and", maptpag);
			perror(maptdir);
			exit(1);
		}
I 10
#endif
E 10
E 3
	}
D 3
	mktemp(maptmp);
	sprintf(maptpag, "%s.pag", maptmp);
	sprintf(maptdir, "%s.dir", maptmp);
D 2
	if (remove(maptpag) < 0 || remove(maptdir) < 0) {
E 2
I 2
	if (xremove(maptpag) < 0 || xremove(maptdir) < 0) {
E 2
		fprintf(stderr, "Can't remove existing temporary files; %s and", maptpag);
		perror(maptdir);
		exit(1);
	}
#endif /* USE_NDBM */
E 3
I 3

E 3
	mapf =  fopen(map, "r");
D 3
	if (mapf)
E 3
I 3
	if (mapf && !printit)
E 3
		mapd = create_database(maptmp);
	else
		mapd = 0;
I 3

E 3
#ifndef DEBUG
	signal(SIGINT, SIG_IGN);
D 3
#endif /* DEBUG */
	if (mapd) {
E 3
I 3
#endif

	if (mapd || printit) {
E 3
		int error = read_file(mapf, map, mapd);
I 10
D 12
		dbm_close(mapd);
E 12
I 12
		if (mapd)
			dbm_close(mapd);
E 12
E 10
		(void) fclose(mapf);
D 3
		if (error) {
			fprintf(stderr, "Error creating ndbm map for %s\n", map);
			rc = 1;
E 3
I 3
		if (printit) {
			if (error) {
				fprintf(stderr, "Error creating ndbm map for %s\n", map);
				rc = 1;
			}
		} else {
			if (error) {
				fprintf(stderr, "Error reading source file  %s\n", map);
				rc = 1;
			} else {
I 10
#ifdef USING_DB
				sprintf(mappag, "%s%s", map, DBM_SUFFIX);
				if (rename(maptpag, mappag) < 0) {
					fprintf(stderr, "Couldn't rename %s to ", maptpag);
					perror(mappag);
					/* Throw away the temporary map */
					unlink(maptpag);
					rc = 1;
				}
#else
E 10
				sprintf(mappag, "%s.pag", map);
				sprintf(mapdir, "%s.dir", map);
				if (rename(maptpag, mappag) < 0) {
					fprintf(stderr, "Couldn't rename %s to ", maptpag);
					perror(mappag);
					/* Throw away the temporary map */
					unlink(maptpag);
					unlink(maptdir);
					rc = 1;
				} else if (rename(maptdir, mapdir) < 0) {
					fprintf(stderr, "Couldn't rename %s to ", maptdir);
					perror(mapdir);
					/* Put the .pag file back */
					rename(mappag, maptpag);
					/* Throw away remaining part of original map */
					unlink(mapdir);
					fprintf(stderr,
						"WARNING: existing map \"%s.{dir,pag}\" destroyed\n",
						map);
					rc = 1;
				}
I 10
#endif
E 10
			}
E 3
		}
D 3
#ifdef USE_NDBM
		sprintf(mappag, "%s.pag", map);
		sprintf(mapdir, "%s.dir", map);
		if (rename(maptpag, mappag) < 0) {
			fprintf(stderr, "Couldn't rename %s to ", maptpag);
			perror(mappag);
			/* Throw away the temporary map */
			unlink(maptpag);
			unlink(maptdir);
			rc = 1;
		} else if (rename(maptdir, mapdir) < 0) {
			fprintf(stderr, "Couldn't rename %s to ", maptdir);
			perror(mapdir);
			/* Put the .pag file back */
			rename(mappag, maptpag);
			/* Throw away remaining part of original map */
			unlink(mapdir);
			fprintf(stderr, "WARNING: existing map \"%s.{dir,pag}\" destroyed\n", map);
			rc = 1;
		}
#endif /* USE_NDBM */
E 3
	} else {
D 3
#ifdef USE_NDBM
E 3
		fprintf(stderr, "Can't open \"%s.{dir,pag}\" for ", map);
D 3
#endif /* USE_NDBM */
E 3
		perror("writing");
		rc = 1;
	}
	exit(rc);
}
#else
main()
{
D 3
	fputs("This system does not support hashed database files\n", stderr);
	exit(0);
E 3
I 3
	fputs("mk-amd-map: This system does not support hashed database files\n", stderr);
	exit(1);
E 3
}
I 3
D 4
 * %sccs.include.redist.c%
E 4
E 3
#endif /* HAS_DATABASE */
E 1
