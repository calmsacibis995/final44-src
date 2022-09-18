h42779
s 00002/00002/00737
d D 8.1 93/06/04 15:32:05 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00028/00013/00711
d D 5.4 92/06/23 16:30:36 bostic 4 3
c recno cleanups
e
s 00082/00021/00642
d D 5.3 91/09/12 11:03:09 bostic 3 2
c add append, icursor; add ability to print out page 0
e
s 00460/00299/00203
d D 5.2 91/09/04 12:51:28 bostic 2 1
c Rev #2.  Redo the btree code add recno's and checkpoint
e
s 00502/00000/00000
d D 5.1 91/04/12 12:19:09 bostic 1 0
c date and time created 91/04/12 12:19:09 by bostic
e
u
U
t
T
I 1
/*-
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
 * Mike Olson.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 2
/*
 *  test1.c -- simple btree test program.
 */

#include <stdio.h>
#include <ctype.h>
E 2
#include <sys/param.h>
D 2
#include <sys/types.h>
#include <sys/file.h>
E 2
I 2
#include <fcntl.h>
E 2
#include <db.h>
D 2
#include <btree.h>
E 2
I 2
#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
E 2

D 2
#define	DICTIONARY	"/usr/share/dict/words"

E 2
typedef struct cmd_table {
	char *cmd;
	int nargs;
D 2
	int (*func)();
	char *descrip;
E 2
I 2
	int rconv;
	void (*func) __P((DB *, char **));
	char *usage, *descrip;
E 2
} cmd_table;

D 2
extern int cursor(), delcur(), delete(), first(), help(), insert();
extern int last(), lookup(), next(), previous();
E 2
I 2
int stopstop;
DB *globaldb;
E 2

I 3
void append	__P((DB *, char **));
E 3
D 2
cmd_table Commands[] = {
	"cursor", 2, cursor,
		"cursor <word>:  point the scan cursor at <word>",
	"delcur", 1, delcur,
		"delcur:  delete the word under the scan cursor",
	"delete", 2, delete,
		"delete <word>:  delete <word> from the dictionary",
	"first", 1, first,
		"first: point the scan cursor at the first dictionary entry",
	"help", 1, help,
		"help:  print this command summary",
	"insert", 3, insert,
		"insert <word> <def>:  insert <word> into the dictionary with definition <def>",
	"last", 1, last,
		"last:  point the scan cursor at the last dictionary entry",
	"lookup", 2, lookup,
		"lookup <word>:  look up <word> in the dictionary",
	"next", 1, next,
		"next:  move the scan cursor forward one word",
	"previous", 1, previous,
		"previous:  move the scan cursor back one word",
	(char *) NULL, 0, NULL, (char *) NULL,
E 2
I 2
void bstat	__P((DB *, char **));
void cursor	__P((DB *, char **));
void delcur	__P((DB *, char **));
void delete	__P((DB *, char **));
void dump	__P((DB *, char **));
void first	__P((DB *, char **));
void get	__P((DB *, char **));
void help	__P((DB *, char **));
void iafter	__P((DB *, char **));
void ibefore	__P((DB *, char **));
I 3
void icursor	__P((DB *, char **));
E 3
void insert	__P((DB *, char **));
void keydata	__P((DBT *, DBT *));
void last	__P((DB *, char **));
void list	__P((DB *, char **));
void load	__P((DB *, char **));
void mstat	__P((DB *, char **));
void next	__P((DB *, char **));
int  parse	__P((char *, char **, int));
void previous	__P((DB *, char **));
void show	__P((DB *, char **));
void usage	__P((void));
void user	__P((DB *));

cmd_table commands[] = {
	"?",	0, 0, help, "help", NULL,
I 3
	"a",	2, 1, append, "append key def", "append key with data def",
E 3
	"b",	0, 0, bstat, "bstat", "stat btree",
	"c",	1, 1, cursor,  "cursor word", "move cursor to word",
	"delc",	0, 0, delcur, "delcur", "delete key the cursor references",
	"dele",	1, 1, delete, "delete word", "delete word",
	"d",	0, 0, dump, "dump", "dump database",
	"f",	0, 0, first, "first", "move cursor to first record",
D 3
	"g",	1, 1, get, "get word", "locate word",
E 3
I 3
	"g",	1, 1, get, "get key", "locate key",
E 3
	"h",	0, 0, help, "help", "print command summary",
	"ia",	2, 1, iafter, "iafter key data", "insert data after key",
	"ib",	2, 1, ibefore, "ibefore key data", "insert data before key",
D 3
	"in",	2, 1, insert, "insert word def", "insert key with data def",
E 3
I 3
	"ic",	2, 1, icursor, "icursor key data", "replace cursor",
	"in",	2, 1, insert, "insert key def", "insert key with data def",
E 3
	"la",	0, 0, last, "last", "move cursor to last record",
	"li",	1, 1, list, "list file", "list to a file",
D 4
	"loa",	1, 1, load, "load file", NULL,
E 4
I 4
	"loa",	1, 0, load, "load file", NULL,
E 4
D 3
	"loc",	1, 1, get, "get word", NULL,
E 3
I 3
	"loc",	1, 1, get, "get key", NULL,
E 3
	"m",	0, 0, mstat, "mstat", "stat memory pool",
	"n",	0, 0, next, "next", "move cursor forward one record",
	"p",	0, 0, previous, "previous", "move cursor back one record",
	"q",	0, 0, NULL, "quit", "quit",
	"sh",	1, 0, show, "show page", "dump a page",
	{ NULL },
E 2
};

D 2
char *Usage = "[-p pagesize] [-c cachesize] [-u] [-l|b|n] [dbname]";
E 2
I 2
int recno;					/* use record numbers */
char *dict = "words";				/* default dictionary */
char *progname;
E 2

I 2
int
E 2
main(argc, argv)
	int argc;
	char **argv;
{
D 2
	char *dbname;
E 2
	int c;
D 2
	char *progname;
	extern int strcmp();
	extern char *optarg;
	extern int optind;
	DB *t;
E 2
I 2
	DB *db;
E 2
	BTREEINFO b;

	progname = *argv;

D 2
	b.psize = 0;
E 2
I 2
	b.flags = 0;
E 2
	b.cachesize = 0;
I 2
	b.maxkeypage = 0;
	b.minkeypage = 0;
	b.psize = 0;
	b.compare = NULL;
	b.prefix = NULL;
E 2
	b.lorder = 0;
D 2
	b.flags = R_DUP;
	b.compare = strcmp;
E 2

D 2
	while ((c = getopt(argc, argv, "p:c:ulb")) != EOF) {
E 2
I 2
	while ((c = getopt(argc, argv, "bc:di:lp:ru")) != EOF) {
E 2
		switch (c) {
D 2
		  case 'p':
			b.psize = atoi(optarg);
E 2
I 2
		case 'b':
			b.lorder = BIG_ENDIAN;
E 2
			break;
D 2

		  case 'c':
E 2
I 2
		case 'c':
E 2
			b.cachesize = atoi(optarg);
			break;
D 2

		  case 'u':
			b.flags = 0;
E 2
I 2
		case 'd':
			b.flags |= R_DUP;
E 2
			break;
D 2

		  case 'l':
E 2
I 2
		case 'i':
			dict = optarg;
			break;
		case 'l':
E 2
			b.lorder = LITTLE_ENDIAN;
			break;
D 2

		  case 'b':
			b.lorder = BIG_ENDIAN;
E 2
I 2
		case 'p':
			b.psize = atoi(optarg);
E 2
			break;
D 2

		  default:
			fprintf(stderr, "%s: usage: %s\n", progname, Usage);
			exit (1);
E 2
I 2
		case 'r':
			recno = 1;
			break;
		case 'u':
			b.flags = 0;
			break;
		default:
			usage();
E 2
		}
	}
I 2
	argc -= optind;
	argv += optind;
E 2

D 2
	if (argv[optind] != (char *) NULL)
		dbname = argv[optind];
E 2
I 2
	if (recno)
		db = dbopen(*argv == NULL ? NULL : *argv, O_RDWR,
		    0, DB_RECNO, NULL);
	else
		db = dbopen(*argv == NULL ? NULL : *argv, O_CREAT|O_RDWR,
		    0600, DB_BTREE, &b);
E 2

D 2
	if ((t = btree_open(dbname, O_CREAT|O_RDWR, 0600, &b)) == (DB *) NULL) {
		perror(progname);
		exit (1);
E 2
I 2
	if (db == NULL) {
		(void)fprintf(stderr, "dbopen: %s\n", strerror(errno));
		exit(1);
E 2
	}
D 2

	load(t);

	user(t);
E 2
I 2
	globaldb = db;
	user(db);
	exit(0);
	/* NOTREACHED */
E 2
}

D 2
load(t)
	DB *t;
E 2
I 2
void
user(db)
	DB *db;
E 2
{
D 2
	char *lbuf;
	int i, l;
	int status;
	FILE *fp;
	DBT key;
	DBT data;
	char word[64];
	char drow[64];
E 2
I 2
	FILE *ifp;
	int argc, i, last;
	char *lbuf, *argv[4], buf[512];
E 2

D 2
	printf("loading %s...\n", DICTIONARY);
	fflush(stdout);
	if ((fp = fopen(DICTIONARY, "r")) == (FILE *) NULL) {
		perror("/usr/dict/words");
		(void) (*(t->close))(t->internal);
		exit (1);
E 2
I 2
	if ((ifp = fopen("/dev/tty", "r")) == NULL) {
		(void)fprintf(stderr,
		    "/dev/tty: %s\n", strerror(errno));
		exit(1);
E 2
	}
D 2

	key.data = &word[0];
	data.data = &drow[0];
	while ((lbuf = fgets(word, 64, fp)) != (char *) NULL) {
		l = strlen(lbuf) - 1;
		lbuf[l] = '\0';
		for (i = 0; i < l; i++)
			drow[l - (i + 1)] = word[i];
		drow[l] = '\0';

		key.size = data.size = l + 1;

		status = (*(t->put))(t->internal, &key, &data, R_NOOVERWRITE);

		switch (status) {
		  case RET_SUCCESS:
E 2
I 2
	for (last = 0;;) {
		(void)printf("> ");
		(void)fflush(stdout);
		if ((lbuf = fgets(&buf[0], 512, ifp)) == NULL)
E 2
			break;
D 2

		  case RET_ERROR:
			perror("put");
			break;

		  case RET_SPECIAL:
			fprintf(stderr, "%s is a duplicate key!\n", lbuf);
			fflush(stderr);
			break;
E 2
I 2
		if (lbuf[0] == '\n') {
			i = last;
			goto uselast;
E 2
		}
D 2
	}

	(void) fclose(fp);
	printf("done\n");
	fflush(stdout);
}

user(t)
	DB *t;
{
	char *lbuf;
	int argc;
	int i;
	char *argv[4];
	char buf[512];

	for (;;) {
		printf("> ");
		fflush(stdout);
		if ((lbuf = fgets(&buf[0], 512, stdin)) == (char *) NULL)
			break;
E 2
		lbuf[strlen(lbuf) - 1] = '\0';

D 2
		if (strcmp(lbuf, "quit") == 0)
E 2
I 2
		if (lbuf[0] == 'q')
E 2
			break;

		argc = parse(lbuf, &argv[0], 3);
		if (argc == 0)
			continue;

D 2
		for (i = 0; Commands[i].cmd != (char *) NULL; i++) {
			if (strcmp(Commands[i].cmd, argv[0]) == 0)
E 2
I 2
		for (i = 0; commands[i].cmd != NULL; i++)
			if (strncmp(commands[i].cmd, argv[0],
			    strlen(commands[i].cmd)) == 0)
E 2
				break;
D 2
		}
E 2

D 2
		if (Commands[i].cmd == (char *) NULL) {
			fprintf(stderr,
				"%s: command unknown ('help' for help)\n",
				lbuf);
			fflush(stderr);
E 2
I 2
		if (commands[i].cmd == NULL) {
			(void)fprintf(stderr,
			    "%s: command unknown ('help' for help)\n", lbuf);
E 2
			continue;
		}

D 2
		if (Commands[i].nargs != argc) {
			fprintf(stderr, "arg count\n");
			fflush(stderr);
E 2
I 2
		if (commands[i].nargs != argc - 1) {
			(void)fprintf(stderr, "usage: %s\n", commands[i].usage);
E 2
			continue;
		}

D 2
		switch (argc) {
		  case 1:
			(*(Commands[i].func))(t);
			break;
		  case 2:
			(*(Commands[i].func))(t, argv[1]);
			break;
		  case 3:
			(*(Commands[i].func))(t, argv[1], argv[2]);
			break;
		  case 4:
			(*(Commands[i].func))(t, argv[1], argv[2], argv[3]);
			break;
E 2
I 2
		if (recno && commands[i].rconv) {
			static recno_t nlong;
			nlong = atoi(argv[1]);
			argv[1] = (char *)&nlong;
E 2
		}
I 2
uselast:	last = i;
		(*commands[i].func)(db, argv);
E 2
	}
D 2
	(void) (*(t->close))(t->internal);
	exit (0);
E 2
I 2
	if ((db->sync)(db) == RET_ERROR)
		perror("dbsync");
	else if ((db->close)(db) == RET_ERROR)
		perror("dbclose");
E 2
}

int
parse(lbuf, argv, maxargc)
D 2
	char *lbuf;
	char **argv;
E 2
I 2
	char *lbuf, **argv;
E 2
	int maxargc;
{
	int argc = 0;
	char *c;

	c = lbuf;
	while (isspace(*c))
		c++;
	while (*c != '\0' && argc < maxargc) {
		*argv++ = c;
		argc++;
		while (!isspace(*c) && *c != '\0') {
			c++;
		}
		while (isspace(*c))
			*c++ = '\0';
	}
	return (argc);
}

D 2
int
cursor(t, arg)
	DB *t;
	char *arg;
E 2
I 2
void
I 3
append(db, argv)
	DB *db;
	char **argv;
{
	DBT key, data;
	int status;

	if (!recno) {
		(void)fprintf(stderr,
		    "append only available for recno db's.\n");
		return;
	}
	key.data = argv[1];
	key.size = sizeof(recno_t);
	data.data = argv[2];
	data.size = strlen(data.data);
	status = (db->put)(db, &key, &data, R_APPEND);
	switch (status) {
	case RET_ERROR:
		perror("append/put");
		break;
	case RET_SPECIAL:
		(void)printf("%s (duplicate key)\n", argv[1]);
		break;
	case RET_SUCCESS:
		break;
	}
}

void
E 3
cursor(db, argv)
	DB *db;
	char **argv;
E 2
{
I 2
	DBT data, key;
E 2
	int status;
D 2
	DBT key;
	DBT data;
E 2

D 2
	key.data = arg;
	key.size = strlen(arg + 1);
	status = (*(t->seq))(t->internal, &key, &data, R_CURSOR);
	if (status == RET_SUCCESS)
		show(&key, &data);
E 2
I 2
	key.data = argv[1];
	if (recno)
		key.size = sizeof(recno_t);
E 2
	else
I 2
		key.size = strlen(argv[1]) + 1;
	status = (*db->seq)(db, &key, &data, R_CURSOR);
	switch (status) {
	case RET_ERROR:
E 2
D 3
		perror("cursor");
E 3
I 3
		perror("cursor/seq");
E 3
I 2
		break;
	case RET_SPECIAL:
		(void)printf("key not found\n");
		break;
	case RET_SUCCESS:
		keydata(&key, &data);
		break;
	}
E 2
}

D 2
int
delcur(t)
	DB *t;
E 2
I 2
void
delcur(db, argv)
	DB *db;
	char **argv;
E 2
{
	int status;

D 2
	status = (*(t->delete))(t->internal, (DBT *) NULL, R_CURSOR);
E 2
I 2
	status = (*db->del)(db, NULL, R_CURSOR);
E 2

	if (status == RET_ERROR)
D 3
		perror("delcur");
E 3
I 3
		perror("delcur/del");
E 3
}

D 2
int
delete(t, arg)
	DB *t;
	char *arg;
E 2
I 2
void
delete(db, argv)
	DB *db;
	char **argv;
E 2
{
D 2
	int status;
E 2
	DBT key;
I 2
	int status;
E 2

D 2
	key.data = arg;
	key.size = strlen(arg) + 1;
E 2
I 2
	key.data = argv[1];
	if (recno)
		key.size = sizeof(recno_t);
	else
		key.size = strlen(argv[1]) + 1;
E 2

D 2
	status = (*(t->delete))(t->internal, &key, 0);
E 2
I 2
	status = (*db->del)(db, &key, 0);
E 2
	switch (status) {
D 2
	  case RET_SUCCESS:
		break;

	  case RET_ERROR:
E 2
I 2
	case RET_ERROR:
E 2
D 3
		perror("delete");
E 3
I 3
		perror("delete/del");
E 3
		break;
D 2

	  case RET_SPECIAL:
		fprintf(stderr, "%s not found\n", arg);
		fflush(stderr);
E 2
I 2
	case RET_SPECIAL:
		(void)printf("key not found\n");
E 2
		break;
I 2
	case RET_SUCCESS:
		break;
E 2
	}
}

D 2
int
first(t)
	DB *t;
E 2
I 2
void
dump(db, argv)
	DB *db;
	char **argv;
E 2
{
I 2
	__bt_dump(db);
}

void
first(db, argv)
	DB *db;
	char **argv;
{
	DBT data, key;
E 2
	int status;
D 2
	DBT key;
	DBT data;
E 2

D 2
	status = (*(t->seq))(t->internal, &key, &data, R_FIRST);
E 2
I 2
	status = (*db->seq)(db, &key, &data, R_FIRST);
E 2

	switch (status) {
D 2
	  case RET_ERROR:
E 2
I 2
	case RET_ERROR:
E 2
D 3
		perror("first");
E 3
I 3
		perror("first/seq");
E 3
		break;
D 2

	  case RET_SPECIAL:
		printf("no more keys");
E 2
I 2
	case RET_SPECIAL:
		(void)printf("no more keys\n");
E 2
		break;
I 2
	case RET_SUCCESS:
		keydata(&key, &data);
		break;
	}
}
E 2

D 2
	  case RET_SUCCESS:
		show(&key, &data);
E 2
I 2
void
get(db, argv)
	DB *db;
	char **argv;
{
	DBT data, key;
	int status;

	key.data = argv[1];
	if (recno)
		key.size = sizeof(recno_t);
	else
		key.size = strlen(argv[1]) + 1;

	status = (*db->get)(db, &key, &data, 0);

	switch (status) {
	case RET_ERROR:
D 3
		perror("get");
E 3
I 3
		perror("get/get");
E 3
E 2
		break;
I 2
	case RET_SPECIAL:
		(void)printf("key not found\n");
		break;
	case RET_SUCCESS:
		keydata(&key, &data);
		break;
E 2
	}
}
D 2
int
help(t)
	DB *t;
E 2
I 2

void
help(db, argv)
	DB *db;
	char **argv;
E 2
{
	int i;

D 2
#ifdef lint
	t = t;
#endif /* lint */
	for (i = 0; Commands[i].cmd != (char *) NULL; i++)
		printf("%s\n", Commands[i].descrip);
	printf("type 'quit' to quit\n");
E 2
I 2
	for (i = 0; commands[i].cmd; i++)
		if (commands[i].descrip)
			(void)printf("%s: %s\n",
			    commands[i].usage, commands[i].descrip);
E 2
}

D 2
int
insert(t, arg, def)
	DB *t;
	char *arg;
	char *def;
E 2
I 2
void
iafter(db, argv)
	DB *db;
	char **argv;
E 2
{
I 2
	DBT key, data;
E 2
	int status;
D 2
	DBT key;
	DBT data;
E 2

D 2
	key.data = arg;
	key.size = strlen(arg) + 1;
	data.data = def;
	data.size = strlen(def) + 1;

	status = (*(t->put))(t->internal, &key, &data, R_NOOVERWRITE);
E 2
I 2
	if (!recno) {
		(void)fprintf(stderr,
		    "iafter only available for recno db's.\n");
		return;
	}
	key.data = argv[1];
	key.size = sizeof(recno_t);
	data.data = argv[2];
	data.size = strlen(data.data);
	status = (db->put)(db, &key, &data, R_IAFTER);
E 2
	switch (status) {
D 2
	  case RET_SUCCESS:
E 2
I 2
	case RET_ERROR:
D 3
		perror("iafter");
E 3
I 3
		perror("iafter/put");
E 3
E 2
		break;
D 2

	  case RET_ERROR:
		perror("put");
E 2
I 2
	case RET_SPECIAL:
		(void)printf("%s (duplicate key)\n", argv[1]);
E 2
		break;
I 2
	case RET_SUCCESS:
		break;
	}
}
E 2

D 2
	  case RET_SPECIAL:
		fprintf(stderr, "%s is a duplicate key!\n", arg);
		fflush(stderr);
E 2
I 2
void
ibefore(db, argv)
	DB *db;
	char **argv;
{
	DBT key, data;
	int status;

	if (!recno) {
		(void)fprintf(stderr,
		    "ibefore only available for recno db's.\n");
		return;
	}
	key.data = argv[1];
	key.size = sizeof(recno_t);
	data.data = argv[2];
	data.size = strlen(data.data);
	status = (db->put)(db, &key, &data, R_IBEFORE);
	switch (status) {
	case RET_ERROR:
D 3
		perror("ibefore");
E 3
I 3
		perror("ibefore/put");
E 3
E 2
		break;
I 2
	case RET_SPECIAL:
		(void)printf("%s (duplicate key)\n", argv[1]);
		break;
	case RET_SUCCESS:
		break;
E 2
	}
}

D 2
int
last(t)
	DB *t;
E 2
I 2
void
I 3
icursor(db, argv)
	DB *db;
	char **argv;
{
	int status;
	DBT data, key;

	key.data = argv[1];
	if (recno)
		key.size = sizeof(recno_t);
	else
		key.size = strlen(argv[1]) + 1;
	data.data = argv[2];
	data.size = strlen(argv[2]) + 1;

	status = (*db->put)(db, &key, &data, R_CURSOR);
	switch (status) {
	case RET_ERROR:
		perror("icursor/put");
		break;
	case RET_SPECIAL:
		(void)printf("%s (duplicate key)\n", argv[1]);
		break;
	case RET_SUCCESS:
		break;
	}
}

void
E 3
insert(db, argv)
	DB *db;
	char **argv;
E 2
{
	int status;
D 2
	DBT key;
	DBT data;
E 2
I 2
	DBT data, key;
E 2

D 2
	status = (*(t->seq))(t->internal, &key, &data, R_LAST);
E 2
I 2
	key.data = argv[1];
	if (recno)
		key.size = sizeof(recno_t);
	else
		key.size = strlen(argv[1]) + 1;
	data.data = argv[2];
	data.size = strlen(argv[2]) + 1;
E 2

I 2
	status = (*db->put)(db, &key, &data, R_NOOVERWRITE);
E 2
	switch (status) {
D 2
	  case RET_ERROR:
		perror("last");
E 2
I 2
	case RET_ERROR:
D 3
		perror("put");
E 3
I 3
		perror("insert/put");
E 3
E 2
		break;
D 2

	  case RET_SPECIAL:
		printf("no more keys");
E 2
I 2
	case RET_SPECIAL:
		(void)printf("%s (duplicate key)\n", argv[1]);
E 2
		break;
D 2

	  case RET_SUCCESS:
		show(&key, &data);
E 2
I 2
	case RET_SUCCESS:
E 2
		break;
	}
}

D 2
int
lookup(t, arg)
	DB *t;
	char *arg;
E 2
I 2
void
last(db, argv)
	DB *db;
	char **argv;
E 2
{
I 2
	DBT data, key;
E 2
	int status;
D 2
	DBT key;
	DBT data;
E 2

D 2
	key.data = arg;
	key.size = strlen(arg) + 1;
E 2
I 2
	status = (*db->seq)(db, &key, &data, R_LAST);
E 2

D 2
	status = (*(t->get))(t->internal, &key, &data, 0);

E 2
	switch (status) {
D 2
	  case RET_SPECIAL:
		printf("not found\n");
E 2
I 2
	case RET_ERROR:
D 3
		perror("last");
E 3
I 3
		perror("last/seq");
E 3
E 2
		break;
D 2
	  case RET_SUCCESS:
		show(&key, &data);
E 2
I 2
	case RET_SPECIAL:
		(void)printf("no more keys\n");
E 2
		break;
D 2
	  case RET_ERROR:
		perror("get");
E 2
I 2
	case RET_SUCCESS:
		keydata(&key, &data);
E 2
		break;
	}
}

D 2
int
next(t)
	DB *t;
E 2
I 2
void
list(db, argv)
	DB *db;
	char **argv;
E 2
{
I 2
	DBT data, key;
	FILE *fp;
E 2
	int status;
D 2
	DBT key;
	DBT data;
E 2

D 2
	status = (*(t->seq))(t->internal, &key, &data, R_NEXT);
E 2
I 2
	if ((fp = fopen(argv[1], "w")) == NULL) {
		(void)fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
		return;
	}
	status = (*db->seq)(db, &key, &data, R_FIRST);
	while (status == RET_SUCCESS) {
		(void)fprintf(fp, "%s\n", key.data);
		status = (*db->seq)(db, &key, &data, R_NEXT);
	}
	if (status == RET_ERROR)
D 3
		perror("list");
E 3
I 3
		perror("list/seq");
E 3
}
E 2

I 4
DB *BUGdb;
E 4
I 2
void
load(db, argv)
	DB *db;
	char **argv;
{
	register char *p, *t;
	FILE *fp;
	DBT data, key;
I 4
	recno_t cnt;
	size_t len;
E 4
	int status;
D 4
	char b1[256], b2[256];
E 4
I 4
	char *lp, buf[16 * 1024];
E 4

I 4
	BUGdb = db;
E 4
	if ((fp = fopen(argv[1], "r")) == NULL) {
D 4
		perror(argv[1]);
E 4
I 4
		(void)fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
E 4
		return;
	}
D 4
	(void)printf("loading %s...\n", dict);
E 4
I 4
	(void)printf("loading %s...\n", argv[1]);
E 4

D 4
	key.data = b1;
	data.data = b2;
	while (fgets(b1, sizeof(b1), fp) != NULL) {
		data.size = strlen(b1);
		b1[data.size - 1] = '\0';
		for (p = &b1[data.size - 2], t = b2; p >= b1; *t++ = *p--);
		b2[data.size - 1] = '\0';
		key.size = data.size;
E 4
I 4
	for (cnt = 1; (lp = fgetline(fp, &len)) != NULL; ++cnt) {
		if (recno) {
			key.data = &cnt;
			key.size = sizeof(recno_t);
			data.data = lp;
			data.size = len + 1;
		} else { 
			key.data = lp;
			key.size = len + 1;
			for (p = lp + len - 1, t = buf; p >= lp; *t++ = *p--);
			*t = '\0';
			data.data = buf;
			data.size = len + 1;
		}
E 4

		status = (*db->put)(db, &key, &data, R_NOOVERWRITE);
		switch (status) {
		case RET_ERROR:
			perror("load/put");
			exit(1);
		case RET_SPECIAL:
D 4
			(void)fprintf(stderr, "duplicate: %s\n", key.data);
E 4
I 4
			if (recno)
				(void)fprintf(stderr,
				    "duplicate: %ld {%s}\n", cnt, data.data);
			else
				(void)fprintf(stderr,
				    "duplicate: %ld {%s}\n", cnt, key.data);
E 4
			exit(1);
		case RET_SUCCESS:
			break;
		}
	}
	(void)fclose(fp);
}

void
next(db, argv)
	DB *db;
	char **argv;
{
	DBT data, key;
	int status;

	status = (*db->seq)(db, &key, &data, R_NEXT);

E 2
	switch (status) {
D 2
	  case RET_ERROR:
E 2
I 2
	case RET_ERROR:
E 2
D 3
		perror("next");
E 3
I 3
		perror("next/seq");
E 3
		break;
D 2

	  case RET_SPECIAL:
		printf("no more keys");
E 2
I 2
	case RET_SPECIAL:
		(void)printf("no more keys\n");
E 2
		break;
D 2

	  case RET_SUCCESS:
		show(&key, &data);
E 2
I 2
	case RET_SUCCESS:
		keydata(&key, &data);
E 2
		break;
	}
}

D 2
int
previous(t)
	DB *t;
E 2
I 2
void
previous(db, argv)
	DB *db;
	char **argv;
E 2
{
I 2
	DBT data, key;
E 2
	int status;
D 2
	DBT key;
	DBT data;
E 2

D 2
	status = (*(t->seq))(t->internal, &key, &data, R_PREV);
E 2
I 2
	status = (*db->seq)(db, &key, &data, R_PREV);
E 2

	switch (status) {
D 2
	  case RET_ERROR:
E 2
I 2
	case RET_ERROR:
E 2
D 3
		perror("previous");
E 3
I 3
		perror("previous/seq");
E 3
		break;
D 2

	  case RET_SPECIAL:
		printf("no more keys");
E 2
I 2
	case RET_SPECIAL:
		(void)printf("no more keys\n");
E 2
		break;
D 2

	  case RET_SUCCESS:
		show(&key, &data);
E 2
I 2
	case RET_SUCCESS:
		keydata(&key, &data);
E 2
		break;
	}
}

D 2
show(key, data)
	DBT *key;
	DBT *data;
E 2
I 2
void
show(db, argv)
	DB *db;
	char **argv;
E 2
{
D 2
	if (key->size > 0)
		printf("%s", key->data);
E 2
I 2
	BTREE *t;
	PAGE *h;
	pgno_t pg;

	pg = atoi(argv[1]);
D 3
	if (pg == 0) {
		(void)printf("page 0 is meta-data page.\n");
		return;
	}

E 3
	t = db->internal;
	if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL) {
		(void)printf("getpage of %ld failed\n", pg);
		return;
	}
D 3
	__bt_dpage(h);
E 3
I 3
	if (pg == 0)
		__bt_dmpage(h);
	else
		__bt_dpage(h);
E 3
	mpool_put(t->bt_mp, h, 0);
}

void
bstat(db, argv)
	DB *db;
	char **argv;
{
	(void)printf("BTREE\n");
	__bt_stat(db);
}

void
mstat(db, argv)
	DB *db;
	char **argv;
{
	(void)printf("MPOOL\n");
	mpool_stat(((BTREE *)db->internal)->bt_mp);
}

void
keydata(key, data)
	DBT *key, *data;
{
	if (!recno && key->size > 0)
		(void)printf("%s/", key->data);
E 2
	if (data->size > 0)
D 2
		printf("/%s", data->data);
	printf("\n");
E 2
I 2
		(void)printf("%s", data->data);
	(void)printf("\n");
}

void
usage()
{
	(void)fprintf(stderr,
	    "usage: %s [-bdlu] [-c cache] [-i file] [-p page] [file]\n",
	    progname);
	exit (1);
E 2
}
E 1
