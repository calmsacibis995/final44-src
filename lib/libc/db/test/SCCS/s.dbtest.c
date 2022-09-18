h29567
s 00005/00005/00635
d D 8.8 94/02/21 17:41:04 bostic 26 25
c make SunOS shut up
e
s 00000/00001/00640
d D 8.7 94/01/02 12:12:13 bostic 25 24
c integrate latest version into 4.4BSD-Lite
e
s 00004/00000/00637
d D 8.6 93/09/16 16:39:46 bostic 24 23
c if btree STATISTICS compiled in, print them out
e
s 00008/00004/00629
d D 8.5 93/09/07 11:45:59 bostic 23 22
c add -l flag to set Db_LOCK
e
s 00001/00001/00632
d D 8.4 93/09/06 09:30:23 bostic 22 21
c strtol -> atoi
e
s 00002/00000/00631
d D 8.3 93/08/27 10:47:38 bostic 21 20
c there's no way to portably test this
e
s 00018/00017/00613
d D 8.2 93/08/17 10:24:48 bostic 20 19
c strtoul -> atoi, add compat.h for memmove() call
e
s 00005/00005/00625
d D 8.1 93/06/04 15:35:56 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00626
d D 5.18 93/05/22 14:09:45 bostic 18 17
c add psize to RECNO
e
s 00010/00010/00616
d D 5.17 93/05/19 11:36:35 bostic 17 16
c returning the wrong structure from the -i option
e
s 00006/00003/00620
d D 5.16 93/05/19 11:35:07 margo 16 15
c use TMPDIR to specify where the output goes, it can be quite large
e
s 00000/00002/00623
d D 5.15 93/05/10 11:56:43 bostic 15 14
c delete R_CURSORLOG
e
s 00015/00006/00610
d D 5.14 93/05/01 15:19:03 bostic 14 13
c add -f so can keep files across successive runs
e
s 00002/00001/00614
d D 5.13 93/04/29 10:52:01 bostic 13 12
c test for DB_RECNO type before freeing key.data
e
s 00002/00001/00613
d D 5.12 93/04/29 10:42:00 bostic 12 11
c put db.h last, so that compatibility version works.
e
s 00001/00001/00613
d D 5.11 93/02/28 14:48:28 bostic 11 10
c cast SIZE_T_MAX so compilers don't get upset
e
s 00001/00001/00613
d D 5.10 93/02/16 12:33:05 bostic 10 9
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00002/00001/00612
d D 5.9 93/01/10 13:53:37 bostic 9 8
c use strtok, not strsep for compatibility
e
s 00002/00000/00611
d D 5.8 93/01/10 13:39:08 bostic 8 7
c add optind, optarg for compatibility
e
s 00009/00000/00602
d D 5.7 93/01/10 13:05:30 bostic 7 6
c add global dbp pointer for gdb calls; add psize parameter
e
s 00038/00004/00564
d D 5.6 92/12/04 14:09:17 bostic 6 5
c add dump database command
e
s 00008/00006/00560
d D 5.5 92/11/13 17:11:00 bostic 5 4
c add R_SETCURSOR, R_APPEND -> R_CURSORLOG
e
s 00068/00015/00498
d D 5.4 92/10/13 12:58:29 bostic 4 3
c make 'e' handle a carriage return, add comparison command
e
s 00001/00000/00512
d D 5.3 92/10/09 16:25:06 bostic 3 2
c close read file descriptor
e
s 00065/00039/00447
d D 5.2 92/08/27 09:39:15 bostic 2 1
c add 'e' command, report on missing keys in get/seq/put etc.
e
s 00486/00000/00000
d D 5.1 92/08/26 12:58:48 bostic 1 0
c date and time created 92/08/26 12:58:48 by bostic
e
u
U
t
T
I 1
/*-
D 19
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 19
char copyright[] =
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
E 19
I 19
static char copyright[] =
"%Z% Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 19
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>

#include <ctype.h>
D 12
#include <db.h>
E 12
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
I 12

#include <db.h>
I 20
D 25
#include "../PORT/include/compat.h"
E 25
E 20
E 12

D 4
enum S { COMMAND, GET, PUT, REMOVE, SEQ, SEQFLAG, KEY, DATA };
E 4
I 4
enum S { COMMAND, COMPARE, GET, PUT, REMOVE, SEQ, SEQFLAG, KEY, DATA };
E 4

I 4
void	 compare __P((DBT *, DBT *));
E 4
DBTYPE	 dbtype __P((char *));
I 6
void	 dump __P((DB *, int));
E 6
void	 err __P((const char *, ...));
void	 get __P((DB *, DBT *));
I 4
void	 getdata __P((DB *, DBT *, DBT *));
E 4
void	 put __P((DB *, DBT *, DBT *));
void	 rem __P((DB *, DBT *));
void	*rfile __P((char *, size_t *));
D 2
void	 seq __P((DB *));
E 2
I 2
void	 seq __P((DB *, DBT *));
E 2
u_int	 setflags __P((char *));
void	*setinfo __P((DBTYPE, char *));
void	 usage __P((void));
void	*xmalloc __P((char *, size_t));

DBTYPE type;
void *infop;
u_long lineno;
u_int flags;
int ofd = STDOUT_FILENO;

I 7
DB *XXdbp;				/* Global for gdb. */

E 7
int
main(argc, argv)
	int argc;
	char *argv[];
{
I 8
	extern int optind;
	extern char *optarg;
E 8
	enum S command, state;
	DB *dbp;
D 4
	DBT data, key;
E 4
I 4
	DBT data, key, keydata;
E 4
	size_t len;
D 23
	int ch;
E 23
I 23
	int ch, oflags;
E 23
D 14
	char *infoarg, *p, buf[8 * 1024];
E 14
I 14
	char *fname, *infoarg, *p, buf[8 * 1024];
E 14

	infoarg = NULL;
D 14
	while ((ch = getopt(argc, argv, "i:o:")) != EOF)
E 14
I 14
	fname = NULL;
D 23
	while ((ch = getopt(argc, argv, "f:i:o:")) != EOF)
E 23
I 23
	oflags = O_CREAT | O_RDWR;
	while ((ch = getopt(argc, argv, "f:i:lo:")) != EOF)
E 23
E 14
		switch(ch) {
I 14
		case 'f':
			fname = optarg;
			break;
E 14
		case 'i':
			infoarg = optarg;
			break;
I 23
		case 'l':
			oflags |= DB_LOCK;
			break;
E 23
		case 'o':
			if ((ofd = open(optarg,
			    O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0)
				err("%s: %s", optarg, strerror(errno));
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

	/* Set the type. */
	type = dbtype(*argv++);

	/* Open the descriptor file. */
	if (freopen(*argv, "r", stdin) == NULL)
		err("%s: %s", *argv, strerror(errno));

	/* Set up the db structure as necessary. */
	if (infoarg == NULL)
		infop = NULL;
	else
D 9
		while ((p = strsep(&infoarg, ",\t ")) != NULL)
E 9
I 9
		for (p = strtok(infoarg, ",\t "); p != NULL;
		    p = strtok(0, ",\t "))
E 9
			if (*p != '\0')
				infop = setinfo(type, p);

D 14
#define	BACKINGFILE	"/tmp/__dbtest"
E 14
	/* Open the DB. */
D 14
	(void)unlink(BACKINGFILE);
	if ((dbp = dbopen(BACKINGFILE,
E 14
I 14
D 16
#define	BACKINGFILE	"/tmp/__dbtest"
E 16
	if (fname == NULL) {
D 16
		fname = BACKINGFILE;
		(void)unlink(BACKINGFILE);
E 16
I 16
		p = getenv("TMPDIR");
		if (p == NULL)
			p = "/var/tmp";
		(void)sprintf(buf, "%s/__dbtest", p);
		fname = buf;
		(void)unlink(buf);
E 16
	}
	if ((dbp = dbopen(fname,
E 14
D 23
	    O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, type, infop)) == NULL)
E 23
I 23
	    oflags, S_IRUSR | S_IWUSR, type, infop)) == NULL)
E 23
		err("dbopen: %s", strerror(errno));
I 7
	XXdbp = dbp;
E 7

	state = COMMAND;
	for (lineno = 1;
	    (p = fgets(buf, sizeof(buf), stdin)) != NULL; ++lineno) {
		len = strlen(buf);
		switch(*p) {
I 4
		case 'c':			/* compare */
			if (state != COMMAND)
				err("line %lu: not expecting command", lineno);
			state = KEY;
			command = COMPARE;
			break;
E 4
I 2
		case 'e':			/* echo */
			if (state != COMMAND)
				err("line %lu: not expecting command", lineno);
D 4
			(void)write(ofd, p + 1, len - 1);
E 4
I 4
			/* Don't display the newline, if CR at EOL. */
			if (p[len - 2] == '\r')
				--len;
			if (write(ofd, p + 1, len - 1) != len - 1)
				err("write: %s", strerror(errno));
E 4
			break;
E 2
		case 'g':			/* get */
			if (state != COMMAND)
				err("line %lu: not expecting command", lineno);
			state = KEY;
			command = GET;
			break;
		case 'p':			/* put */
			if (state != COMMAND)
				err("line %lu: not expecting command", lineno);
			state = KEY;
			command = PUT;
			break;
		case 'r':			/* remove */
			if (state != COMMAND)
				err("line %lu: not expecting command", lineno);
			state = KEY;
			command = REMOVE;
			break;
		case 's':			/* seq */
			if (state != COMMAND)
				err("line %lu: not expecting command", lineno);
D 2
			seq(dbp);
E 2
I 2
			if (flags == R_CURSOR) {
				state = KEY;
				command = SEQ;
			} else
				seq(dbp, &key);
E 2
			break;
		case 'f':
D 2
			flags |= setflags(p + 1);
E 2
I 2
			flags = setflags(p + 1);
E 2
			break;
		case 'D':			/* data file */
			if (state != DATA)
				err("line %lu: not expecting data", lineno);
D 4
			if (command != PUT)
				err("line %lu: command doesn't take data",
				    lineno);
E 4
			data.data = rfile(p + 1, &data.size);
D 4
			put(dbp, &key, &data);
			free(key.data);
			free(data.data);
			state = COMMAND;
			break;
E 4
I 4
D 6
			goto data;
E 6
I 6
			goto ldata;
E 6
E 4
		case 'd':			/* data */
			if (state != DATA)
				err("line %lu: not expecting data", lineno);
D 4
			if (command != PUT)
				err("line %lu: command doesn't take data",
				    lineno);
E 4
			data.data = xmalloc(p + 1, len - 1);
			data.size = len - 1;
D 4
			put(dbp, &key, &data);
E 4
I 4
D 6
data:			switch(command) {
E 6
I 6
ldata:			switch(command) {
E 6
			case COMPARE:
				compare(&keydata, &data);
				break;
			case PUT:
				put(dbp, &key, &data);
				break;
			default:
				err("line %lu: command doesn't take data",
				    lineno);
			}
E 4
D 13
			free(key.data);
E 13
I 13
			if (type != DB_RECNO)
				free(key.data);
E 13
			free(data.data);
			state = COMMAND;
			break;
		case 'K':			/* key file */
			if (state != KEY)
				err("line %lu: not expecting a key", lineno);
			if (type == DB_RECNO)
				err("line %lu: 'K' not available for recno",
				    lineno);
			key.data = rfile(p + 1, &key.size);
D 2
			switch(command) {
			case GET:
				get(dbp, &key);
				free(key.data);
				state = COMMAND;
				break;
			case PUT:
				state = DATA;
				break;
			case REMOVE:
				rem(dbp, &key);
				free(key.data);
				state = COMMAND;
				break;
			default:
				err("line %lu: command doesn't take a key",
				    lineno);
			}
			break;
E 2
I 2
D 6
			goto key;
E 6
I 6
			goto lkey;
E 6
E 2
		case 'k':			/* key */
			if (state != KEY)
				err("line %lu: not expecting a key", lineno);
			if (type == DB_RECNO) {
				static recno_t recno;
D 22
				recno = strtol(p + 1, NULL, 0);
E 22
I 22
				recno = atoi(p + 1);
E 22
				key.data = &recno;
				key.size = sizeof(recno);
			} else {
				key.data = xmalloc(p + 1, len - 1);
				key.size = len - 1;
			}
D 2
			switch(command) {
E 2
I 2
D 6
key:			switch(command) {
E 6
I 6
lkey:			switch(command) {
E 6
I 4
			case COMPARE:
				getdata(dbp, &key, &keydata);
				state = DATA;
				break;
E 4
E 2
			case GET:
				get(dbp, &key);
				if (type != DB_RECNO)
					free(key.data);
				state = COMMAND;
				break;
			case PUT:
				state = DATA;
				break;
			case REMOVE:
				rem(dbp, &key);
				if (type != DB_RECNO)
					free(key.data);
				state = COMMAND;
				break;
I 2
			case SEQ:
				seq(dbp, &key);
				if (type != DB_RECNO)
					free(key.data);
				state = COMMAND;
				break;
E 2
			default:
				err("line %lu: command doesn't take a key",
				    lineno);
			}
			break;
I 6
		case 'o':
			dump(dbp, p[1] == 'r');
			break;
E 6
		default:
			err("line %lu: %s: unknown command character",
D 2
			    *p, lineno);
E 2
I 2
			    p, lineno);
E 2
		}
	}
I 24
#ifdef STATISTICS
	if (type == DB_BTREE)
		__bt_stat(dbp);
#endif
E 24
I 14
	if (dbp->close(dbp))
		err("db->close: %s", strerror(errno));
E 14
	(void)close(ofd);
	exit(0);
}

I 2
#define	NOOVERWRITE	"put failed, would overwrite key\n"
#define	NOSUCHKEY	"get failed, no such key\n"

E 2
void
I 4
compare(db1, db2)
	DBT *db1, *db2;
{
	register size_t len;
	register u_char *p1, *p2;

	if (db1->size != db2->size)
		printf("compare failed: key->data len %lu != data len %lu\n",
		    db1->size, db2->size);

	len = MIN(db1->size, db2->size);
	for (p1 = db1->data, p2 = db2->data; len--;)
		if (*p1++ != *p2++) {
			printf("compare failed at offset %d\n",
			    p1 - (u_char *)db1->data);
			break;
		}
}

void
E 4
get(dbp, kp)
	DB *dbp;
	DBT *kp;
{
	DBT data;

D 2
	if (dbp->get(dbp, kp, &data, flags) == -1)
E 2
I 2
	switch(dbp->get(dbp, kp, &data, flags)) {
	case 0:
		(void)write(ofd, data.data, data.size);
		break;
	case -1:
E 2
		err("line %lu: get: %s", lineno, strerror(errno));
D 2
	(void)write(ofd, data.data, data.size);
E 2
I 2
		/* NOTREACHED */
	case 1:
		(void)write(ofd, NOSUCHKEY, sizeof(NOSUCHKEY) - 1);
I 7
		(void)fprintf(stderr, "%d: %.*s: %s\n", 
		    lineno, kp->size, kp->data, NOSUCHKEY);
E 7
		break;
I 4
	}
}

void
getdata(dbp, kp, dp)
	DB *dbp;
	DBT *kp, *dp;
{
	switch(dbp->get(dbp, kp, dp, flags)) {
	case 0:
		return;
	case -1:
		err("line %lu: getdata: %s", lineno, strerror(errno));
		/* NOTREACHED */
	case 1:
		err("line %lu: get failed, no such key", lineno);
		/* NOTREACHED */
E 4
	}
E 2
}

void
put(dbp, kp, dp)
	DB *dbp;
	DBT *kp, *dp;
{
D 2
	if (dbp->put(dbp, kp, dp, flags) == -1)
E 2
I 2
	switch(dbp->put(dbp, kp, dp, flags)) {
	case 0:
		break;
	case -1:
E 2
		err("line %lu: put: %s", lineno, strerror(errno));
I 2
		/* NOTREACHED */
	case 1:
		(void)write(ofd, NOOVERWRITE, sizeof(NOOVERWRITE) - 1);
		break;
	}
E 2
}

void
rem(dbp, kp)
	DB *dbp;
	DBT *kp;
{
D 2
	if (dbp->del(dbp, kp, flags) == -1)
E 2
I 2
	switch(dbp->del(dbp, kp, flags)) {
	case 0:
		break;
	case -1:
E 2
		err("line %lu: get: %s", lineno, strerror(errno));
I 2
		/* NOTREACHED */
	case 1:
		(void)write(ofd, NOSUCHKEY, sizeof(NOSUCHKEY) - 1);
		break;
	}
E 2
}

void
D 2
seq(dbp)
E 2
I 2
seq(dbp, kp)
E 2
	DB *dbp;
I 2
	DBT *kp;
E 2
{
D 2
	DBT key, data;
	size_t len;
	char nbuf[20];
E 2
I 2
	DBT data;
E 2

D 2
	if (dbp->seq(dbp, &key, &data, flags) == -1)
E 2
I 2
	switch(dbp->seq(dbp, kp, &data, flags)) {
	case 0:
		(void)write(ofd, data.data, data.size);
		break;
	case -1:
E 2
		err("line %lu: seq: %s", lineno, strerror(errno));
D 2
	if (type == DB_RECNO) {
		len = sprintf(nbuf, "%lu\n", *(u_long *)key.data);
		(void)write(ofd, nbuf, len);
	} else
		(void)write(ofd, key.data, key.size);
	(void)write(ofd, data.data, data.size);
E 2
I 2
		/* NOTREACHED */
	case 1:
		(void)write(ofd, NOSUCHKEY, sizeof(NOSUCHKEY) - 1);
		break;
	}
I 6
}

void
dump(dbp, rev)
	DB *dbp;
	int rev;
{
	DBT key, data;
	int flags, nflags;

	if (rev) {
		flags = R_LAST;
		nflags = R_PREV;
	} else {
		flags = R_FIRST;
		nflags = R_NEXT;
	}
	for (;; flags = nflags)
		switch(dbp->seq(dbp, &key, &data, flags)) {
		case 0:
			(void)write(ofd, data.data, data.size);
			break;
		case 1:
			goto done;
		case -1:
			err("line %lu: (dump) seq: %s",
			    lineno, strerror(errno));
			/* NOTREACHED */
		}
done:	return;
E 6
E 2
}
	
u_int
setflags(s)
	char *s;
{
D 26
	char *p;
E 26
I 26
	char *p, *index();
E 26

	for (; isspace(*s); ++s);
	if (*s == '\n')
		return (0);
	if ((p = index(s, '\n')) != NULL)
		*p = '\0';
D 5
	if (!strcmp(s, "R_APPEND"))
		return (R_APPEND);
E 5
	if (!strcmp(s, "R_CURSOR"))
		return (R_CURSOR);
I 5
D 15
	if (!strcmp(s, "R_CURSORLOG"))
		return (R_CURSORLOG);
E 15
	if (!strcmp(s, "R_FIRST"))
		return (R_FIRST);
E 5
	if (!strcmp(s, "R_IAFTER"))
		return (R_IAFTER);
	if (!strcmp(s, "R_IBEFORE"))
		return (R_IBEFORE);
D 5
	if (!strcmp(s, "R_NOOVERWRITE"))
		return (R_NOOVERWRITE);
	if (!strcmp(s, "R_FIRST"))
		return (R_FIRST);
E 5
	if (!strcmp(s, "R_LAST"))
		return (R_LAST);
	if (!strcmp(s, "R_NEXT"))
		return (R_NEXT);
I 5
	if (!strcmp(s, "R_NOOVERWRITE"))
		return (R_NOOVERWRITE);
E 5
	if (!strcmp(s, "R_PREV"))
		return (R_PREV);
I 5
	if (!strcmp(s, "R_SETCURSOR"))
		return (R_SETCURSOR);
E 5
	err("line %lu: %s: unknown flag", lineno, s);
	/* NOTREACHED */
}
	
DBTYPE
dbtype(s)
	char *s;
{
	if (!strcmp(s, "btree"))
		return (DB_BTREE);
	if (!strcmp(s, "hash"))
		return (DB_HASH);
	if (!strcmp(s, "recno"))
		return (DB_RECNO);
	err("%s: unknown type (use btree, hash or recno)", s);
	/* NOTREACHED */
}

void *
setinfo(type, s)
	DBTYPE type;
	char *s;
{
	static BTREEINFO ib;
	static HASHINFO ih;
	static RECNOINFO rh;
D 26
	char *eq;
E 26
I 26
	char *eq, *index();
E 26

	if ((eq = index(s, '=')) == NULL)
		err("%s: illegal structure set statement", s);
	*eq++ = '\0';
	if (!isdigit(*eq))
		err("%s: structure set statement must be a number", s);
		
	switch(type) {
	case DB_BTREE:
		if (!strcmp("flags", s)) {
D 20
			ib.flags = strtoul(eq, NULL, 0);
E 20
I 20
			ib.flags = atoi(eq);
E 20
			return (&ib);
		}
		if (!strcmp("cachesize", s)) {
D 20
			ib.cachesize = strtoul(eq, NULL, 0);
E 20
I 20
			ib.cachesize = atoi(eq);
E 20
			return (&ib);
		}
		if (!strcmp("maxkeypage", s)) {
D 20
			ib.maxkeypage = strtoul(eq, NULL, 0);
E 20
I 20
			ib.maxkeypage = atoi(eq);
E 20
			return (&ib);
		}
		if (!strcmp("minkeypage", s)) {
D 20
			ib.minkeypage = strtoul(eq, NULL, 0);
E 20
I 20
			ib.minkeypage = atoi(eq);
E 20
			return (&ib);
		}
		if (!strcmp("lorder", s)) {
D 20
			ib.lorder = strtoul(eq, NULL, 0);
E 20
I 20
			ib.lorder = atoi(eq);
E 20
I 7
			return (&ib);
		}
		if (!strcmp("psize", s)) {
D 20
			ib.psize = strtoul(eq, NULL, 0);
E 20
I 20
			ib.psize = atoi(eq);
E 20
E 7
			return (&ib);
		}
		break;
	case DB_HASH:
		if (!strcmp("bsize", s)) {
D 20
			ih.bsize = strtoul(eq, NULL, 0);
E 20
I 20
			ih.bsize = atoi(eq);
E 20
D 17
			return (&ib);
E 17
I 17
			return (&ih);
E 17
		}
		if (!strcmp("ffactor", s)) {
D 20
			ih.ffactor = strtoul(eq, NULL, 0);
E 20
I 20
			ih.ffactor = atoi(eq);
E 20
D 17
			return (&ib);
E 17
I 17
			return (&ih);
E 17
		}
		if (!strcmp("nelem", s)) {
D 20
			ih.nelem = strtoul(eq, NULL, 0);
E 20
I 20
			ih.nelem = atoi(eq);
E 20
D 17
			return (&ib);
E 17
I 17
			return (&ih);
E 17
		}
		if (!strcmp("cachesize", s)) {
D 20
			ih.cachesize = strtoul(eq, NULL, 0);
E 20
I 20
			ih.cachesize = atoi(eq);
E 20
D 17
			return (&ib);
E 17
I 17
			return (&ih);
E 17
		}
		if (!strcmp("lorder", s)) {
D 20
			ih.lorder = strtoul(eq, NULL, 0);
E 20
I 20
			ih.lorder = atoi(eq);
E 20
D 17
			return (&ib);
E 17
I 17
			return (&ih);
E 17
		}
		break;
	case DB_RECNO:
		if (!strcmp("flags", s)) {
D 20
			rh.flags = strtoul(eq, NULL, 0);
E 20
I 20
			rh.flags = atoi(eq);
E 20
D 17
			return (&ib);
E 17
I 17
			return (&rh);
E 17
		}
		if (!strcmp("cachesize", s)) {
D 20
			rh.cachesize = strtoul(eq, NULL, 0);
E 20
I 20
			rh.cachesize = atoi(eq);
E 20
D 17
			return (&ib);
E 17
I 17
			return (&rh);
E 17
		}
		if (!strcmp("lorder", s)) {
D 20
			rh.lorder = strtoul(eq, NULL, 0);
E 20
I 20
			rh.lorder = atoi(eq);
E 20
D 17
			return (&ib);
E 17
I 17
			return (&rh);
E 17
		}
		if (!strcmp("reclen", s)) {
D 20
			rh.reclen = strtoul(eq, NULL, 0);
E 20
I 20
			rh.reclen = atoi(eq);
E 20
D 17
			return (&ib);
E 17
I 17
			return (&rh);
E 17
		}
		if (!strcmp("bval", s)) {
D 20
			rh.bval = strtoul(eq, NULL, 0);
E 20
I 20
			rh.bval = atoi(eq);
E 20
D 17
			return (&ib);
E 17
I 17
			return (&rh);
E 17
		}
I 18
		if (!strcmp("psize", s)) {
D 20
			rh.psize = strtoul(eq, NULL, 0);
E 20
I 20
			rh.psize = atoi(eq);
E 20
			return (&rh);
		}
E 18
		break;
	}
	err("%s: unknown structure value", s);
	/* NOTREACHED */
}

void *
rfile(name, lenp)
	char *name;
	size_t *lenp;
{
	struct stat sb;
	void *p;
	int fd;
D 26
	char *np;
E 26
I 26
	char *np, *index();
E 26

	for (; isspace(*name); ++name);
	if ((np = index(name, '\n')) != NULL)
		*np = '\0';
	if ((fd = open(name, O_RDONLY, 0)) < 0 ||
	    fstat(fd, &sb))
		err("%s: %s\n", name, strerror(errno));
I 21
#ifdef NOT_PORTABLE
E 21
D 11
	if (sb.st_size > SIZE_T_MAX)
E 11
I 11
	if (sb.st_size > (off_t)SIZE_T_MAX)
E 11
		err("%s: %s\n", name, strerror(E2BIG));
I 21
#endif
E 21
D 26
	if ((p = malloc((u_int)sb.st_size)) == NULL)
E 26
I 26
	if ((p = (void *)malloc((u_int)sb.st_size)) == NULL)
E 26
		err("%s", strerror(errno));
	(void)read(fd, p, (int)sb.st_size);
	*lenp = sb.st_size;
I 3
	(void)close(fd);
E 3
	return (p);
}

void *
xmalloc(text, len)
	char *text;
	size_t len;
{
	void *p;

D 26
	if ((p = malloc(len)) == NULL)
E 26
I 26
	if ((p = (void *)malloc(len)) == NULL)
E 26
		err("%s", strerror(errno));
D 10
	bcopy(text, p, len);
E 10
I 10
	memmove(p, text, len);
E 10
	return (p);
}

void
usage()
{
	(void)fprintf(stderr,
D 14
	    "usage: dbtest [-i info] [-o file] type script\n");
E 14
I 14
D 23
	    "usage: dbtest [-f file] [-i info] [-o file] type script\n");
E 23
I 23
	    "usage: dbtest [-l] [-f file] [-i info] [-o file] type script\n");
E 23
E 14
	exit(1);
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
	(void)fprintf(stderr, "dbtest: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
}
E 1
