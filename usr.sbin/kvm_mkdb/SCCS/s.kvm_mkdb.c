h46816
s 00001/00000/00094
d D 8.3 95/05/04 15:50:34 bostic 21 20
c optarg/optind moved to unistd.h
e
s 00010/00001/00084
d D 8.2 95/04/27 15:35:26 bostic 20 19
c Mycroft says he gets a major speed improvement with this.
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00005/00005/00080
d D 8.1 93/06/06 13:58:29 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00034/00068
d D 5.18 93/04/10 08:03:40 bostic 18 17
c general cleanup, use new err(3) routines
e
s 00001/00001/00101
d D 5.17 93/03/08 19:32:06 ralph 17 16
c fix args to dbopen so it doesn't fail.
e
s 00001/00001/00101
d D 5.16 92/06/02 13:52:56 bostic 16 15
c off-by-one, from Craig Leres
e
s 00018/00007/00084
d D 5.15 92/05/04 17:05:03 bostic 15 14
c update from LBL (Chris, Craig and Steve)
e
s 00002/00002/00089
d D 5.14 92/04/24 19:14:07 bostic 14 13
c delete extra slash
e
s 00003/00000/00088
d D 5.13 92/04/23 18:06:52 bostic 13 12
c too many args is a usage error
e
s 00002/00002/00086
d D 5.12 91/09/23 14:12:59 bostic 12 11
c hash_open -> dbopen
e
s 00000/00001/00088
d D 5.11 91/04/27 16:23:42 bostic 11 10
c don't need user.h anymore
e
s 00007/00006/00082
d D 5.10 91/03/03 13:44:04 bostic 10 9
c convert from ndbm(3) to db(3) interface
e
s 00001/00000/00087
d D 5.9 91/03/02 14:47:47 bostic 9 8
c ANSI
e
s 00001/00000/00086
d D 5.8 91/02/14 12:14:15 bostic 8 7
c use DBM_SUFFIX; db(3) now appends ".db" when old interface is used.
e
s 00035/00226/00051
d D 5.7 91/02/12 22:56:58 bostic 7 6
c integrate Margo Seltzer's hashing package instead of ndbm
c break out kernel nlist stuff into separate file.
e
s 00002/00002/00275
d D 5.6 90/10/30 09:35:50 bostic 6 5
c BSD_LINE_MAX -> POSIX2_LINE_MAX
e
s 00002/00003/00275
d D 5.5 90/06/25 01:08:36 bostic 5 4
c LINE_MAX -> BSD_LINE_MAX; errno declared in errno.h
e
s 00010/00007/00268
d D 5.4 90/06/07 11:37:47 bostic 4 3
c HP300 fixes from Mike Hibler
e
s 00005/00019/00270
d D 5.3 90/06/01 18:42:36 bostic 3 2
c fix copyright notice
e
s 00001/00001/00288
d D 5.2 90/05/15 20:02:18 bostic 2 1
c string.h is ANSI C include file
e
s 00289/00000/00000
d D 5.1 90/03/07 14:45:51 marc 1 0
c date and time created 90/03/07 14:45:51 by marc
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1989 The Regents of the University of California.
E 3
I 3
/*-
D 18
 * Copyright (c) 1990 The Regents of the University of California.
E 18
I 18
D 19
 * Copyright (c) 1990, 1993 The Regents of the University of California.
E 18
E 3
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
D 3
 * Redistribution and use in source and binary forms is permitted
 * provided that all copyright information, including this notice,
 * is retained in all such forms, and that any documentation,
 * advertising or other materials related to such distribution and
 * use acknowledge that the software was
 * developed by the University of California, Berkeley.  The name
 * of the University may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
D 19
char copyright[] =
D 3
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
E 3
I 3
D 18
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
E 18
I 18
"%Z% Copyright (c) 1990, 1993 The Regents of the University of California.\n\
E 18
E 3
 All rights reserved.\n";
E 19
I 19
static char copyright[] =
"%Z% Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 19
#endif /* not lint */

D 3
/*
 * kvm_mkdb -- Create kernel information database for running kernel.
 */

E 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
I 3

E 3
#include <sys/param.h>
D 7
#include <sys/file.h>
E 7
I 7
#include <sys/stat.h>
I 9
D 11
#include <sys/user.h>
E 11
E 9
D 18
#include <fcntl.h>
E 18
I 18

E 18
E 7
D 10
#include <ndbm.h>
E 10
I 10
#include <db.h>
I 18
#include <err.h>
E 18
E 10
D 7
#include <a.out.h>
#include <kvm.h>
#include <paths.h>
#include <limits.h>
E 7
#include <errno.h>
I 18
#include <fcntl.h>
#include <paths.h>
E 18
D 2
#include <strings.h>
E 2
I 2
D 7
#include <string.h>
E 7
E 2
#include <stdio.h>
I 15
#include <stdlib.h>
E 15
I 7
#include <string.h>
I 21
#include <unistd.h>
E 21
D 18
#include <paths.h>
E 18
E 7

D 15
char *tmp;
#define basename(cp)	((tmp=rindex((cp), '/')) ? tmp+1 : (cp))
E 15
I 15
#include "extern.h"
E 15
D 7
#define USAGE	"kvm_mkdb"
E 7
D 5
extern errno;
E 5

I 15
D 18
static void usage __P(());
E 18
I 18
static void usage __P((void));
E 18

I 20
HASHINFO openinfo = {
	4096,		/* bsize */
	128,		/* ffactor */
	1024,		/* nelem */
	2048 * 1024,	/* cachesize */
	NULL,		/* hash() */
	0		/* lorder */
};

E 20
int
E 15
D 7
char *progname;

E 7
main(argc, argv)
D 7
	char *argv[];
E 7
I 7
	int argc;
D 18
	char **argv;
E 18
I 18
	char *argv[];
E 18
E 7
{
D 7
	DBM *db;
	char *nlistpath, *nlistname;
	char dbtemp[MAXPATHLEN];
	char dbname[MAXPATHLEN];
	extern char *optarg;
E 7
D 15
	extern int optind;
E 15
I 7
D 10
	DBM *db;
E 10
I 10
	DB *db;
E 10
E 7
	int ch;
I 7
D 15
	char *nlistpath, *nlistname, dbtemp[MAXPATHLEN], dbname[MAXPATHLEN];
E 15
I 15
	char *p, *nlistpath, *nlistname, dbtemp[MAXPATHLEN], dbname[MAXPATHLEN];
E 15
E 7

D 7
	progname = argv[0];
E 7
	while ((ch = getopt(argc, argv, "")) != EOF)
D 18
		switch((char)ch) {
E 18
I 18
		switch (ch) {
E 18
		case '?':
		default:
D 7
			fprintf(stderr, "usage: %s", progname, USAGE);
			exit(1);
E 7
I 7
			usage();
E 7
		}
	argc -= optind;
	argv += optind;

I 13
	if (argc > 1)
		usage();

I 15
	/* If the existing db file matches the currently running kernel, exit */
	if (testdb())
		exit(0);

#define	basename(cp)	((p = rindex((cp), '/')) != NULL ? p + 1 : (cp))
E 15
E 13
D 16
	nlistpath = argc > 1 ? argv[0] : _PATH_UNIX;
E 16
I 16
	nlistpath = argc > 0 ? argv[0] : _PATH_UNIX;
E 16
	nlistname = basename(nlistpath);
I 10

E 10
D 7
	sprintf(dbtemp, "%s/kvm_tmp%s", KVMDBDIR, nlistname);
	sprintf(dbname, "%s/kvm_%s", KVMDBDIR, nlistname);
	rmdb(dbtemp);
	umask(0);
	if ((db = dbm_open(dbtemp, O_CREAT|O_WRONLY|O_EXCL, 0644)) == NULL)
		syserrexit("error opening dbmfile");
	if (create_knlist(nlistpath, db) == -1)
		errexit("error creating kernel namelist");
	if (create_devnames(db) == -1)
		errexit("error creating devnames");
	rmdb(dbname);
	mvdb(dbtemp, dbname);

E 7
I 7
D 14
	(void)sprintf(dbtemp, "%s/kvm_%s.tmp", _PATH_VARRUN, nlistname);
	(void)sprintf(dbname, "%s/kvm_%s.db", _PATH_VARRUN, nlistname);
E 14
I 14
D 15
	(void)sprintf(dbtemp, "%skvm_%s.tmp", _PATH_VARRUN, nlistname);
	(void)sprintf(dbname, "%skvm_%s.db", _PATH_VARRUN, nlistname);
E 15
I 15
	(void)snprintf(dbtemp, sizeof(dbtemp), "%skvm_%s.tmp",
	    _PATH_VARDB, nlistname);
	(void)snprintf(dbname, sizeof(dbname), "%skvm_%s.db",
	    _PATH_VARDB, nlistname);
E 15
E 14
	(void)umask(0);
D 10
	if ((db = dbm_open(dbtemp, O_CREAT|O_WRONLY|O_EXCL,
	    S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == NULL) {
E 10
I 10
D 12
	db = hash_open(dbtemp, O_CREAT|O_WRONLY|O_EXCL,
	    S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH, NULL);
E 12
I 12
D 15
	db = dbopen(dbtemp, O_CREAT|O_WRONLY|O_EXCL,
E 15
I 15
D 17
	db = dbopen(dbtemp, O_CREAT|O_EXLOCK|O_TRUNC|O_WRONLY,
E 17
I 17
D 18
	db = dbopen(dbtemp, O_CREAT|O_EXLOCK|O_TRUNC|O_RDWR,
E 17
E 15
	    S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH, DB_HASH, NULL);
E 12
	if (!db) {
E 10
		(void)fprintf(stderr,
		    "kvm_mkdb: %s: %s\n", dbtemp, strerror(errno));
		exit(1);
	}
E 18
I 18
	db = dbopen(dbtemp, O_CREAT | O_EXLOCK | O_TRUNC | O_RDWR,
D 20
	    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH, DB_HASH, NULL);
E 20
I 20
	    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH, DB_HASH, &openinfo);
E 20
	if (db == NULL)
		err(1, "%s", dbtemp);
E 18
	create_knlist(nlistpath, db);
D 10
	(void)dbm_close(db);
I 8
	(void)strcat(dbtemp, DBM_SUFFIX);
E 10
I 10
D 18
	(void)(db->close)(db);
E 10
E 8
	if (rename(dbtemp, dbname)) {
		(void)fprintf(stderr, "kvm_mkdb: %s to %s: %s.\n",
		    dbtemp, dbname, strerror(errno));
		exit(1);
	}
E 18
I 18
	if (db->close(db))
		err(1, "%s", dbtemp);
	if (rename(dbtemp, dbname))
		err(1, "rename %s to %s", dbtemp, dbname);
E 18
E 7
	exit(0);
D 18
}

I 15
void
E 15
D 7
rmdb(file)
	char *file;
E 7
I 7
error(n)
	char *n;
E 7
{
D 7
	int len = strlen(file);
E 7
I 7
	int sverr;
E 7

D 7
	if (len > (MAXPATHLEN - 5))
		errexit("pathname too long: %s", file);
	strcpy(file+len, ".dir");
	if (unlink(file) < 0 && errno != ENOENT)
		syserrexit("can't unlink %s", file);
	strcpy(file+len, ".pag");
	if (unlink(file) < 0 && errno != ENOENT)
		syserrexit("can't unlink %s", file);
	*(file+len) = '\0';
}
D 4
	
E 4
I 4

E 4
mvdb(from, to)
	char *from;
	char *to;
{
	int flen = strlen(from);
	int tlen = strlen(to);

	if (flen > (MAXPATHLEN - 5) || tlen > (MAXPATHLEN - 5))
		errexit("pathname too long: %s or %s", from, to);
	strcpy(from+flen, ".dir");
	strcpy(to+tlen, ".dir");
	if (rename(from, to) == -1)
		syserrexit("rename %s to %s", from, to);
	strcpy(from+flen, ".pag");
	strcpy(to+tlen, ".pag");
	if (rename(from, to) == -1)
		syserrexit("rename %s to %s", from, to);
	*(from+flen) = *(to+tlen) = '\0';
}

/* from libc/nlist.c */
#include <unistd.h>

typedef struct nlist NLIST;
#define	_strx	n_un.n_strx
#define	_name	n_un.n_name
#define	ISVALID(p)	(p->_name && p->_name[0])
#define MAXSYMSIZE	256

create_knlist(name, db)
	char *name;
	DBM *db;
{
	register NLIST *p, *s;
	struct exec ebuf;
	FILE *fstr, *fsym;
	NLIST nbuf;
	off_t strings_offset, symbol_offset, symbol_size, lseek();
	char sbuf[MAXSYMSIZE+1];
	register char *bp;
	register int c, len;
	datum key, data;

	if (!(fsym = fopen(name, "r")))
		syserrexit("can't open %s", name);
	if (fread((char *)&ebuf, sizeof(struct exec), 1, fsym) != 1 ||
	    N_BADMAG(ebuf))
		syserrexit("can't read exec");

	symbol_offset = N_SYMOFF(ebuf);
	symbol_size = ebuf.a_syms;
	strings_offset = symbol_offset + symbol_size;

	if (fseek(fsym, symbol_offset, SEEK_SET) == -1)
		syserrexit("can't seek symbol table: %x", symbol_offset);
	if ((fstr = fopen(name, "r")) == NULL)
		syserrexit("can't open %s", name);

	sbuf[0] = KVMDB_NLIST;
	key.dptr = sbuf;
	data.dptr = (char *)&nbuf;
	data.dsize = sizeof (NLIST);

	for (s = &nbuf; symbol_size; symbol_size -= sizeof (NLIST)) {
		if (fread((char *)s, sizeof (NLIST), 1, fsym) != 1)
			syserrexit("can't read nlist entry");
		if (!s->_strx || s->n_type&N_STAB)
			continue;
		if (fseek(fstr, strings_offset + s->_strx, SEEK_SET) == -1)
			syserrexit("can't seek string: %x", 
				strings_offset + s->_strx);
		/*
		 * read string
		 */
		bp = sbuf + 1;
		len = 0;
		while ((c = fgetc(fstr)) != EOF && c != '\0') {
			if (++len == MAXSYMSIZE)
				errexit("string too long");
			*bp++ = c;
		}
		*bp = '\0';
		/*
		 * and store it
		 */
		key.dsize = bp - sbuf;
		if (dbm_store(db, key, data, DBM_INSERT) < 0)
			syserrexit("dbm_store");
		if (strcmp(sbuf+1, "_version") == 0) {
			/* 
			 * store the value of version in VERSION
			 */
			datum vers;
D 5
			char versbuf[LINE_MAX];
E 5
I 5
D 6
			char versbuf[_BSD_LINE_MAX];
E 6
I 6
			char versbuf[_POSIX2_LINE_MAX];
E 6
E 5
			long versoff;
			long reloffset;

I 4
			/* offset relative to start of text image in VM. */
#ifdef hp300
			reloffset = s->n_value;
#endif
#ifdef tahoe
E 4
			/*
D 4
			 * Offset relative to start of text image in VM.
			 * On tahoe, first 0x800 is reserved for
			 * communication with the console processor.
E 4
I 4
			 * on tahoe, first 0x800 is reserved for communication
			 * with the console processor.
E 4
			 */
D 4
#ifdef tahoe
E 4
			reloffset = ((s->n_value & ~KERNBASE) - 0x800);
#endif
#ifdef vax
			reloffset = (s->n_value & ~KERNBASE);
#endif
			/*
			 * When loaded, data is rounded
D 4
			 * to next 1024 after text, but not in file.
E 4
I 4
			 * to next page cluster after text, but not in file.
E 4
			 */
D 4
			reloffset -= 1024 - (ebuf.a_text % 1024);
E 4
I 4
			reloffset -= CLBYTES - (ebuf.a_text % CLBYTES);
E 4
			versoff = N_TXTOFF(ebuf) + reloffset;
			if (fseek(fstr, versoff, SEEK_SET) == -1)
				syserrexit("seek (version): %x", s->n_value);
			/*
			 * Just read version string up to, and
			 * including newline.
			 */
D 5
			if (fgets(versbuf, LINE_MAX, fstr) == NULL)
E 5
I 5
D 6
			if (fgets(versbuf, _BSD_LINE_MAX, fstr) == NULL)
E 6
I 6
			if (fgets(versbuf, _POSIX2_LINE_MAX, fstr) == NULL)
E 6
E 5
				syserrexit("can't read version");
			strcpy(sbuf+1, "VERSION");
			key.dsize = (sizeof ("VERSION") - 1) + 1;
			vers.dptr = versbuf;
			vers.dsize = strlen(versbuf);
			if (dbm_store(db, key, vers, DBM_INSERT) < 0)
				syserrexit("dbm_store: can't store VERSION");
		}
	}
	(void)fclose(fstr);
	(void)fclose(fsym);
	return (0);
}

create_devnames() {}

#include <varargs.h>

warning(va_alist)
	va_dcl
{
	char *fmt;
	va_list ap;

	fprintf(stderr, "%s: warning: ", progname);
	va_start(ap);
	fmt = va_arg(ap, char *);
	(void) vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
}


errexit(va_alist)
	va_dcl
{
	char *fmt;
	va_list ap;

	fprintf(stderr, "%s: ", progname);
	va_start(ap);
	fmt = va_arg(ap, char *);
	(void) vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
E 7
I 7
	sverr = errno;
	(void)fprintf(stderr, "kvm_mkdb: ");
	if (n)
		(void)fprintf(stderr, "%s: ", n);
	(void)fprintf(stderr, "%s\n", strerror(sverr));
E 7
	exit(1);
E 18
}

I 15
void
E 15
D 7

syserrexit(va_alist)
	va_dcl
E 7
I 7
usage()
E 7
{
D 7
	char *fmt;
	va_list ap;

	fprintf(stderr, "%s: ", progname);
	va_start(ap);
	fmt = va_arg(ap, char *);
	(void) vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, ": %s\n", strerror(errno));
E 7
I 7
	(void)fprintf(stderr, "usage: kvm_mkdb [file]\n");
E 7
	exit(1);
}
E 1
