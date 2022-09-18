h06129
s 00011/00007/00095
d D 8.3 94/03/06 08:59:31 eric 11 10
c handle non-null-terminated strings in the database
e
s 00001/00001/00101
d D 8.2 93/09/22 10:55:39 eric 10 9
c fix stepping through dbm database
e
s 00005/00005/00097
d D 8.1 93/06/07 10:23:54 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00049/00016/00053
d D 6.3 93/05/21 08:54:42 eric 8 7
c add support for NEWDB
e
s 00019/00016/00050
d D 6.2 93/05/20 16:05:24 bostic 7 6
c convert from dbm to ndbm
e
s 00000/00000/00066
d D 6.1 92/12/21 16:13:41 eric 6 5
c Release 6
e
s 00001/00011/00065
d D 5.5 90/06/01 18:59:03 bostic 5 4
c new copyright notice
e
s 00011/00005/00065
d D 5.4 88/06/29 22:00:48 bostic 4 3
c install approved copyright notice
e
s 00050/00022/00020
d D 5.3 88/04/21 17:01:39 bostic 3 2
c bring it up to date
e
s 00001/00001/00041
d D 5.2 87/04/06 14:43:02 bostic 2 1
c print format/argument mismatch
e
s 00042/00000/00000
d D 5.1 87/04/06 14:41:49 bostic 1 0
c date and time created 87/04/06 14:41:49 by bostic
e
u
U
t
T
I 1
D 3
# include "sendmail.h"
E 3
I 3
/*
I 4
 * Copyright (c) 1983 Eric P. Allman
E 4
D 9
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
 */
E 3

D 3
static	char sccsid[] = "%W%	%G%";
E 3
I 3
#ifndef lint
D 9
char copyright[] =
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
 All rights reserved.\n";
E 9
I 9
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 9
#endif /* not lint */
E 3

D 3
typedef struct { char *dptr; int dsize; } datum;
datum	firstkey(), nextkey(), fetch();
char	*filename = ALIASFILE;
E 3
I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

I 7
#include <ndbm.h>
E 7
I 3
#include <sendmail.h>
I 8
#ifdef NEWDB
#include <db.h>
#endif
E 8

D 7
typedef struct {
	char *dptr;
	int dsize;
} datum;


E 7
I 7
int
E 7
E 3
main(argc, argv)
I 7
	int argc;
E 7
	char **argv;
{
D 3
	datum content, key;
E 3
I 3
	extern char *optarg;
	extern int optind;
D 7
	static char *filename = "/usr/lib/aliases";
	datum content, key, firstkey(), nextkey(), fetch();
E 7
I 7
	DBM *dbp;
	datum content, key;
	char *filename;
E 7
	int ch;
I 8
#ifdef NEWDB
	const DB *db;
	DBT newdbkey, newdbcontent;
	char buf[MAXNAME];
#endif
E 8
E 3

I 7
	filename = "/etc/aliases";
E 7
D 3
	if (argc > 2 && strcmp(argv[1], "-f") == 0)
	{
		argv++;
		filename = *++argv;
		argc -= 2;
	}
E 3
I 3
	while ((ch = getopt(argc, argv, "f:")) != EOF)
		switch((char)ch) {
		case 'f':
			filename = optarg;
			break;
		case '?':
		default:
D 7
			fputs("usage: praliases [-f file]\n", stderr);
E 7
I 7
			(void)fprintf(stderr, "usage: praliases [-f file]\n");
E 7
			exit(EX_USAGE);
		}
	argc -= optind;
	argv += optind;
E 3

D 7
	if (dbminit(filename) < 0)
E 7
I 7
D 8
	if ((dbp = dbm_open(filename, O_RDONLY, 0)) == NULL) {
		(void)fprintf(stderr,
		    "praliases: %s: %s\n", filename, strerror(errno));
E 7
		exit(EX_OSFILE);
E 8
I 8
#ifdef NEWDB
	(void) strcpy(buf, filename);
	(void) strcat(buf, ".db");
	if (db = dbopen(buf, O_RDONLY, 0444 , DB_HASH, NULL)) {
		if (!argc) {
			while(!db->seq(db, &newdbkey, &newdbcontent, R_NEXT))
D 11
				printf("%s:%s\n", newdbkey.data,
						newdbcontent.data);
E 11
I 11
				printf("%.*s:%.*s\n",
					newdbkey.size, newdbkey.data,
					newdbcontent.size, newdbcontent.data);
E 11
		}
		else for (; *argv; ++argv) {
			newdbkey.data = *argv;
			newdbkey.size = strlen(*argv) + 1;
D 11
			if ( !db->get(db, &newdbkey, &newdbcontent, 0) )
				printf("%s:%s\n", newdbkey.data,
					newdbcontent.data);
E 11
I 11
			if (!db->get(db, &newdbkey, &newdbcontent, 0))
				printf("%s:%.*s\n", newdbkey.data,
					newdbcontent.size, newdbcontent.data);
E 11
			else
				printf("%s: No such key\n",
					newdbkey.data);
		}
E 8
I 7
	}
E 7
D 3
	argc--, argv++;
	if (argc == 0) {
E 3
I 3
D 8
	if (!argc)
E 3
D 7
		for (key = firstkey(); key.dptr; key = nextkey(key)) {
			content = fetch(key);
D 3
			printf("\n%s:%s\n", key.dptr, content.dptr);
E 3
I 3
			printf("%s:%s\n", key.dptr, content.dptr);
E 7
I 7
		for (key = dbm_nextkey(dbp);
		    key.dptr != NULL; key = dbm_nextkey(dbp)) {
E 8
I 8
	else {
#endif
		if ((dbp = dbm_open(filename, O_RDONLY, 0)) == NULL) {
			(void)fprintf(stderr,
			    "praliases: %s: %s\n", filename, strerror(errno));
			exit(EX_OSFILE);
		}
		if (!argc)
D 10
			for (key = dbm_nextkey(dbp);
E 10
I 10
			for (key = dbm_firstkey(dbp);
E 10
			    key.dptr != NULL; key = dbm_nextkey(dbp)) {
				content = dbm_fetch(dbp, key);
D 11
				(void)printf("%s:%s\n", key.dptr, content.dptr);
E 11
I 11
				(void)printf("%.*s:%.*s\n",
					key.dsize, key.dptr,
					content.dsize, content.dptr);
E 11
			}
		else for (; *argv; ++argv) {
			key.dptr = *argv;
			key.dsize = strlen(*argv) + 1;
E 8
			content = dbm_fetch(dbp, key);
D 8
			(void)printf("%s:%s\n", key.dptr, content.dptr);
E 8
I 8
			if (!content.dptr)
				(void)printf("%s: No such key\n", key.dptr);
			else
D 11
				(void)printf("%s:%s\n", key.dptr, content.dptr);
E 11
I 11
				(void)printf("%s:%.*s\n", key.dptr,
					content.dsize, content.dptr);
E 11
E 8
E 7
E 3
		}
D 3
		exit(EX_OK);
	}
	while (argc) {
E 3
I 3
D 8
	else for (; *argv; ++argv) {
E 3
		key.dptr = *argv;
D 3
		key.dsize = strlen(*argv)+1;
E 3
I 3
		key.dsize = strlen(*argv) + 1;
E 3
D 7
		content = fetch(key);
E 7
I 7
		content = dbm_fetch(dbp, key);
E 7
D 3
		if (content.dptr == 0)
E 3
I 3
		if (!content.dptr)
E 3
D 2
			printf("%s: No such key\n");
E 2
I 2
D 7
			printf("%s: No such key\n", key.dptr);
E 7
I 7
			(void)printf("%s: No such key\n", key.dptr);
E 7
E 2
		else
D 3
			printf("\n%s:%s\n", key.dptr, content.dptr);
		argc--, argv++;
E 3
I 3
D 7
			printf("%s:%s\n", key.dptr, content.dptr);
E 7
I 7
			(void)printf("%s:%s\n", key.dptr, content.dptr);
E 8
I 8
#ifdef NEWDB
E 8
E 7
E 3
	}
I 8
#endif
E 8
	exit(EX_OK);
}
E 1
