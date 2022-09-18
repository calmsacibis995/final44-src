h50993
s 00002/00002/00466
d D 8.13 95/05/31 08:37:42 eric 18 17
c OLD_NEWDB is a 0/1 option, not def/ndef
e
s 00012/00000/00456
d D 8.12 95/05/12 08:08:37 eric 17 15
c include OLD_NEWDB support for consistency with sendmail
e
s 00000/00000/00351
d D 8.6.1.1 95/03/06 13:26:58 eric 16 10
i 15 13
c fixes for Alphas
e
s 00004/00000/00452
d D 8.11 95/03/06 13:25:43 eric 15 14
c sync the files immediately upon create (helps on Alphas?)
e
s 00003/00001/00449
d D 8.10 95/02/24 10:09:10 eric 14 13
c ISC Unix hacks
e
s 00001/00001/00449
d D 8.9 95/02/03 08:10:01 eric 13 12
c use size_t for xx.size for maximum compability (I hope)
e
s 00075/00000/00375
d D 8.8 95/01/10 09:03:17 eric 12 11
c do file locking
e
s 00031/00003/00344
d D 8.7 94/07/24 16:29:12 eric 11 10
c add -d flag to allow duplicate keys in B-Trees
e
s 00008/00001/00339
d D 8.6 93/11/22 11:44:08 eric 10 9
c fix core dump on no \n problem
e
s 00002/00002/00338
d D 8.5 93/09/22 09:05:29 eric 9 8
c fix -f flag to match ORA book
e
s 00001/00000/00339
d D 8.4 93/08/24 14:20:09 eric 8 7
c portability fix
e
s 00001/00000/00338
d D 8.3 93/08/08 12:54:14 eric 7 6
c compilation botch
e
s 00028/00000/00310
d D 8.2 93/08/08 12:52:52 eric 6 5
c default to adding ".db" extension on hash & btree maps for
c compatibility with K .cf line
e
s 00002/00002/00308
d D 8.1 93/06/07 10:22:25 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00018/00296
d D 6.2 93/05/28 14:27:19 eric 4 3
c use NDBM and NEWDB compile flags to match sendmail
e
s 00000/00000/00314
d D 6.1 92/12/21 16:10:00 eric 3 2
c Release 6
e
s 00010/00002/00304
d D 5.2 92/12/12 09:44:48 eric 2 1
c add -f flag to map upper->lower case in the keys
e
s 00306/00000/00000
d D 5.1 92/11/15 14:57:52 eric 1 0
c date and time created 92/11/15 14:57:52 by eric
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 Eric P. Allman.
D 5
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <stdio.h>
#include <sysexits.h>
I 8
#include <sys/types.h>
E 8
D 14
#include <sys/file.h>
E 14
#include <ctype.h>
#include <string.h>
I 12
#include <sys/errno.h>
I 14
#ifndef ISC_UNIX
# include <sys/file.h>
#endif
E 14
E 12
#include "useful.h"
#include "conf.h"

D 4
#ifdef DBM_MAP
E 4
I 4
#ifdef NDBM
E 4
#include <ndbm.h>
#endif

D 4
#if defined(HASH_MAP) || defined(BTREE_MAP)
E 4
I 4
#ifdef NEWDB
E 4
#include <db.h>
#endif

enum type { T_DBM, T_BTREE, T_HASH, T_ERR, T_UNKNOWN };

union dbent
{
D 4
#ifdef DBM_MAP
E 4
I 4
#ifdef NDBM
E 4
	datum	dbm;
#endif
D 4
#if defined(HASH_MAP) || defined(BTREE_MAP)
E 4
I 4
#ifdef NEWDB
E 4
	DBT	db;
#endif
	struct
	{
		char	*data;
D 13
		int	size;
E 13
I 13
		size_t	size;
E 13
	} xx;
};

#define BUFSIZE		1024

main(argc, argv)
	int argc;
	char **argv;
{
	char *progname;
	bool inclnull = FALSE;
	bool notrunc = FALSE;
	bool allowreplace = FALSE;
I 11
	bool allowdups = FALSE;
E 11
	bool verbose = FALSE;
I 2
D 9
	bool foldcase = FALSE;
E 9
I 9
	bool foldcase = TRUE;
E 9
E 2
	int exitstat;
	int opt;
	char *typename;
	char *mapname;
I 7
	char *ext;
E 7
	int lineno;
	int st;
	int mode;
	enum type type;
I 12
	int fd;
E 12
	union
	{
D 4
#ifdef DBM_MAP
E 4
I 4
#ifdef NDBM
E 4
		DBM	*dbm;
#endif
D 4
#if defined(HASH_MAP) || defined(BTREE_MAP)
E 4
I 4
#ifdef NEWDB
E 4
		DB	*db;
#endif
		void	*dbx;
	} dbp;
	union dbent key, val;
I 11
#ifdef NEWDB
	BTREEINFO bti;
#endif
E 11
	char ibuf[BUFSIZE];
I 6
	char fbuf[MAXNAME];
E 6
	extern char *optarg;
	extern int optind;
I 12
	extern bool lockfile();
E 12

	progname = argv[0];

D 2
	while ((opt = getopt(argc, argv, "Norv")) != EOF)
E 2
I 2
D 11
	while ((opt = getopt(argc, argv, "Nforv")) != EOF)
E 11
I 11
	while ((opt = getopt(argc, argv, "Ndforv")) != EOF)
E 11
E 2
	{
		switch (opt)
		{
		  case 'N':
			inclnull = TRUE;
			break;

I 11
		  case 'd':
			allowdups = TRUE;
			break;

E 11
I 2
		  case 'f':
D 9
			foldcase = TRUE;
E 9
I 9
			foldcase = FALSE;
E 9
			break;

E 2
		  case 'o':
			notrunc = TRUE;
			break;

		  case 'r':
			allowreplace = TRUE;
			break;

		  case 'v':
			verbose = TRUE;
			break;

		  default:
			type = T_ERR;
			break;
		}
	}

	argc -= optind;
	argv += optind;
	if (argc != 2)
		type = T_ERR;
	else
	{
		typename = argv[0];
		mapname = argv[1];
I 6
		ext = NULL;
E 6

		if (strcmp(typename, "dbm") == 0)
I 6
		{
E 6
			type = T_DBM;
I 6
		}
E 6
		else if (strcmp(typename, "btree") == 0)
I 6
		{
E 6
			type = T_BTREE;
I 6
			ext = ".db";
		}
E 6
		else if (strcmp(typename, "hash") == 0)
I 6
		{
E 6
			type = T_HASH;
I 6
			ext = ".db";
		}
E 6
		else
			type = T_UNKNOWN;
	}

	switch (type)
	{
	  case T_ERR:
D 11
		fprintf(stderr, "Usage: %s [-N] [-o] [-v] type mapname\n", progname);
E 11
I 11
		fprintf(stderr, "Usage: %s [-N] [-d] [-f] [-o] [-r] [-v] type mapname\n", progname);
E 11
		exit(EX_USAGE);

	  case T_UNKNOWN:
		fprintf(stderr, "%s: Unknown database type %s\n",
			progname, typename);
		exit(EX_USAGE);

D 4
#ifndef DBM_MAP
E 4
I 4
#ifndef NDBM
E 4
	  case T_DBM:
#endif
D 4
#ifndef BTREE_MAP
E 4
I 4
#ifndef NEWDB
E 4
	  case T_BTREE:
D 4
#endif
#ifndef HASH_MAP
E 4
	  case T_HASH:
#endif
		fprintf(stderr, "%s: Type %s not supported in this version\n",
			progname, typename);
		exit(EX_UNAVAILABLE);
I 11

#ifdef NEWDB
	  case T_BTREE:
		bzero(&bti, sizeof bti);
		if (allowdups)
			bti.flags |= R_DUP;
		break;

	  case T_HASH:
#endif
#ifdef NDBM
	  case T_DBM:
#endif
		if (allowdups)
		{
			fprintf(stderr, "%s: Type %s does not support -d (allow dups)\n",
				progname, typename);
			exit(EX_UNAVAILABLE);
		}
		break;
E 11
I 6
	}

	/*
	**  Adjust file names.
	*/

	if (ext != NULL)
	{
		int el, fl;

		el = strlen(ext);
		fl = strlen(mapname);
		if (fl < el || strcmp(&mapname[fl - el], ext) != 0)
		{
			strcpy(fbuf, mapname);
			strcat(fbuf, ext);
			mapname = fbuf;
		}
E 6
	}

	/*
	**  Create the database.
	*/

	mode = O_RDWR;
I 12
#ifdef O_EXLOCK
	mode |= O_EXLOCK;
#endif
E 12
	if (!notrunc)
		mode |= O_CREAT|O_TRUNC;
	switch (type)
	{
D 4
#ifdef DBM_MAP
E 4
I 4
#ifdef NDBM
E 4
	  case T_DBM:
		dbp.dbm = dbm_open(mapname, mode, 0644);
		break;
#endif

D 4
#ifdef HASH_MAP
E 4
I 4
#ifdef NEWDB
E 4
	  case T_HASH:
		dbp.db = dbopen(mapname, mode, 0644, DB_HASH, NULL);
I 15
		if (dbp.db != NULL)
I 17
		{
D 18
# ifdef OLD_NEWDB
E 18
I 18
# if OLD_NEWDB
E 18
			(void) (*dbp.db->sync)(dbp.db);
# else
E 17
			(void) (*dbp.db->sync)(dbp.db, 0);
I 17
# endif
		}
E 17
E 15
		break;
D 4
#endif
E 4

D 4
#ifdef BTREE_MAP
E 4
	  case T_BTREE:
D 11
		dbp.db = dbopen(mapname, mode, 0644, DB_BTREE, NULL);
E 11
I 11
		dbp.db = dbopen(mapname, mode, 0644, DB_BTREE, &bti);
I 15
		if (dbp.db != NULL)
I 17
		{
D 18
# ifdef OLD_NEWDB
E 18
I 18
# if OLD_NEWDB
E 18
			(void) (*dbp.db->sync)(dbp.db);
# else
E 17
			(void) (*dbp.db->sync)(dbp.db, 0);
I 17
# endif
		}
E 17
E 15
E 11
		break;
#endif

	  default:
		fprintf(stderr, "%s: internal error: type %d\n", progname, type);
		exit(EX_SOFTWARE);
	}

	if (dbp.dbx == NULL)
	{
		fprintf(stderr, "%s: cannot create type %s map %s\n",
			progname, typename, mapname);
		exit(EX_CANTCREAT);
	}

I 12
#ifndef O_EXLOCK
	switch (type)
	{
# ifdef NDBM
	  case T_DBM:
		fd = dbm_dirfno(dbp.dbm);
		if (fd >= 0)
			lockfile(fd);
		break;
# endif
# ifdef NEWDB
	  case T_HASH:
	  case T_BTREE:
		fd = dbp.db->fd(dbp.db);
		if (fd >= 0)
			lockfile(fd);
		break;
# endif
	}
#endif

E 12
	/*
	**  Copy the data
	*/

	lineno = 0;
	exitstat = EX_OK;
	while (fgets(ibuf, sizeof ibuf, stdin) != NULL)
	{
		register char *p;

		lineno++;

		/*
		**  Parse the line.
		*/

		p = strchr(ibuf, '\n');
D 10
		if (*p != '\0')
E 10
I 10
		if (p != NULL)
E 10
			*p = '\0';
I 10
		else if (!feof(stdin))
		{
			fprintf(stderr, "%s: %s: line %d: line too long (%d bytes max)\n",
				progname, mapname, lineno, sizeof ibuf);
			continue;
		}
			
E 10
		if (ibuf[0] == '\0' || ibuf[0] == '#')
			continue;
		if (isspace(ibuf[0]))
		{
			fprintf(stderr, "%s: %s: line %d: syntax error (leading space)\n",
				progname, mapname, lineno);
			continue;
		}
		key.xx.data = ibuf;
		for (p = ibuf; *p != '\0' && !isspace(*p); p++)
D 2
			continue;
E 2
I 2
		{
			if (foldcase && isupper(*p))
				*p = tolower(*p);
		}
E 2
		key.xx.size = p - key.xx.data;
		if (inclnull)
			key.xx.size++;
		if (*p != '\0')
			*p++ = '\0';
		while (isspace(*p))
			p++;
		if (*p == '\0')
		{
			fprintf(stderr, "%s: %s: line %d: no RHS for LHS %s\n",
				progname, mapname, lineno, key.xx.data);
			continue;
		}
		val.xx.data = p;
		val.xx.size = strlen(p);
		if (inclnull)
			val.xx.size++;

		/*
		**  Do the database insert.
		*/

		if (verbose)
		{
			printf("key=`%s', val=`%s'\n", key.xx.data, val.xx.data);
		}

		switch (type)
		{
D 4
#ifdef DBM_MAP
E 4
I 4
#ifdef NDBM
E 4
		  case T_DBM:
			st = dbm_store(dbp.dbm, key.dbm, val.dbm,
					allowreplace ? DBM_REPLACE : DBM_INSERT);
			break;
#endif

D 4
#if defined(BTREE_MAP) || defined(HASH_MAP)
E 4
I 4
#ifdef NEWDB
E 4
		  case T_BTREE:
		  case T_HASH:
			st = (*dbp.db->put)(dbp.db, &key.db, &val.db,
					allowreplace ? 0 : R_NOOVERWRITE);
			break;
#endif
		}

		if (st < 0)
		{
			fprintf(stderr, "%s: %s: line %d: key %s: put error\n",
				progname, mapname, lineno, key.xx.data);
			perror(mapname);
			exitstat = EX_IOERR;
		}
		else if (st > 0)
		{
			fprintf(stderr, "%s: %s: line %d: key %s: duplicate key\n",
				progname, mapname, lineno, key.xx.data);
		}
	}

	/*
	**  Now close the database.
	*/

	switch (type)
	{
D 4
#ifdef DBM_MAP
E 4
I 4
#ifdef NDBM
E 4
	  case T_DBM:
		dbm_close(dbp.dbm);
		break;
#endif

D 4
#if defined(HASH_MAP) || defined(BTREE_MAP)
E 4
I 4
#ifdef NEWDB
E 4
	  case T_HASH:
	  case T_BTREE:
		if ((*dbp.db->close)(dbp.db) < 0)
		{
			fprintf(stderr, "%s: %s: error on close\n",
				progname, mapname);
			perror(mapname);
			exitstat = EX_IOERR;
		}
#endif
	}

	exit (exitstat);
I 12
}
/*
**  LOCKFILE -- lock a file using flock or (shudder) fcntl locking
**
**	Parameters:
**		fd -- the file descriptor of the file.
**
**	Returns:
**		TRUE if the lock was acquired.
**		FALSE otherwise.
*/

bool
lockfile(fd)
	int fd;
{
# if !HASFLOCK
	int action;
	struct flock lfd;
	extern int errno;

	bzero(&lfd, sizeof lfd);
	lfd.l_type = F_WRLCK;
	action = F_SETLKW;

	if (fcntl(fd, action, &lfd) >= 0)
		return TRUE;

	/*
	**  On SunOS, if you are testing using -oQ/tmp/mqueue or
	**  -oA/tmp/aliases or anything like that, and /tmp is mounted
	**  as type "tmp" (that is, served from swap space), the
	**  previous fcntl will fail with "Invalid argument" errors.
	**  Since this is fairly common during testing, we will assume
	**  that this indicates that the lock is successfully grabbed.
	*/

	if (errno == EINVAL)
		return TRUE;

# else	/* HASFLOCK */

	if (flock(fd, LOCK_EX) >= 0)
		return TRUE;

# endif

	return FALSE;
E 12
}
E 1
