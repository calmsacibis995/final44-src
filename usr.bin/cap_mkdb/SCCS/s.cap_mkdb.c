h01562
s 00011/00002/00222
d D 8.2 95/04/27 15:34:35 bostic 19 17
c Mycroft says this is a tremendous performance win over NFS
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00011/00002/00222
d R 8.2 95/04/27 15:31:49 bostic 18 17
c speedup for cap_mkdb when running over NFS
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00004/00004/00220
d D 8.1 93/06/06 14:26:05 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00007/00207
d D 5.6 93/03/08 17:21:03 bostic 16 15
c complain if records tc capabilities aren't fully expanded
e
s 00104/00154/00110
d D 5.5 93/03/06 10:44:01 bostic 15 14
c make shadow records really work
e
s 00002/00002/00262
d D 5.4 93/01/25 15:21:10 bostic 14 13
c minor cleanup
e
s 00001/00001/00263
d D 5.3 93/01/23 10:33:21 bostic 13 12
c forgot the usage message
e
s 00009/00005/00255
d D 5.2 93/01/23 10:32:20 bostic 12 11
c don't be so noisy...
e
s 00042/00051/00218
d D 5.1 92/10/17 11:30:26 bostic 11 10
c shut it up as much as possible; minor cleanups, new requirements for
c dbopen(3) use of open(2) flags
e
s 00001/00001/00268
d D 1.10 92/09/16 10:58:46 elan 10 9
c copyright[] -> static.
e
s 00001/00001/00268
d D 1.9 92/09/09 10:58:37 elan 9 8
c Changed reference data size since tag was eliminated.
e
s 00017/00018/00252
d D 1.8 92/09/08 11:59:06 elan 8 7
c Changed '.db' file conflict with ascii files to a warning to 
c the user rather than to try and fix it, because we can't know exactly what 
c the user wants to do.
e
s 00025/00003/00245
d D 1.7 92/09/08 11:09:09 elan 7 6
c Added creation of backup file -- foo.db.BAK so that records will
e
s 00010/00005/00238
d D 1.6 92/09/04 15:36:59 elan 6 5
c Eliminated REFERENCE and RECORD type and added TCERR flag in record 
c to mark a record with a tc expansion failure.
e
s 00032/00022/00211
d D 1.5 92/09/04 10:53:56 elan 5 4
c Made duplicate entries a warning, not a fatal error.
e
s 00015/00018/00218
d D 1.4 92/09/03 10:57:35 elan 4 3
c References are to name field rather than primary name.  Added 
c diagnostic message.
e
s 00078/00129/00158
d D 1.3 92/09/02 18:17:29 elan 3 2
c Cleanup.  Fixed bug in reallocation in db_build. Fixed 
c uninitialized variable problems.  Keith moved stuff around for knf.
e
s 00001/00001/00286
d D 1.2 92/09/01 11:37:34 elan 2 1
c Fixed usage().
e
s 00287/00000/00000
d D 1.1 92/09/01 11:36:23 elan 1 0
c date and time created 92/09/01 11:36:23 by elan
e
u
U
t
T
I 1
D 3
/*
E 3
I 3
/*-
E 3
D 17
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
D 3
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
D 10
char copyright[] =
E 10
I 10
static char copyright[] =
E 10
D 3
"@(#) Copyright (c) 1992 The Regents of the University of California.\n\
E 3
I 3
D 17
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
E 3
 All rights reserved.\n";
E 17
I 17
"%Z% Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 17
#endif /* not lint */

#ifndef lint
D 3
static char sccsid[] = "@(#)cap_mkdb.c	1.3 (Berkeley) 8/11/92";
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
#endif /* not lint */

D 11
#include <sys/types.h>
D 3
#include <limits.h>
E 3
I 3
#include <sys/stat.h>
E 11
I 8
#include <sys/param.h>
I 11
#include <sys/stat.h>
E 11
E 8

E 3
#include <db.h>
I 15
#include <err.h>
E 15
I 3
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
E 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
D 3
#include <fcntl.h>
E 3
#include <unistd.h>
D 3
#include <errno.h>
E 3

D 15
static void	 db_build __P((char **));
D 3
static void	 error __P((const char *, ...));
E 3
I 3
D 5
static void	 err __P((const char *, ...));
E 5
I 5
static void	 err __P((int, const char *, ...));
E 5
E 3
static void	 getnamefield __P((char **, char *));
static void	 usage __P((void));
E 15
I 15
void	 db_build __P((char **));
void	 dounlink __P((void));
void	 usage __P((void));
E 15

D 3
extern char *optarg;
extern int optind;
E 3
I 3
D 7
int docapdbunlink;
E 7
I 7
D 12
int docapdbunlink, printnl;
E 12
I 12
D 15
int docapdbunlink, printnl, verbose;
E 12
E 7
char *capdb, **inputfiles;
E 15
I 15
DB *capdbp;
int verbose;
char *capdb, *capname, buf[8 * 1024];
E 15
E 3

I 19
HASHINFO openinfo = {
	4096,		/* bsize */
	16,		/* ffactor */
	256,		/* nelem */
	2048 * 1024,	/* cachesize */
	NULL,		/* hash() */
	0		/* lorder */
};

E 19
D 3
#define CAPDBNAMEEXTLEN	3	/* "*.db" */
#define BUFSIZ		1024

static char  *capdb;
static char **inputfiles;

E 3
/*
D 3
 * Mkcapdb creates a capability hash database for faster retrieval of 
 * capbaility records.  The database contains 2 types of entries: records and
 * references marked by the first byte in the data.  A record entry contains
 * the actual capability record whereas a reference contains the name (key)
 * under which the correct record is stored.
E 3
I 3
 * Mkcapdb creates a capability hash database for quick retrieval of capability
 * records.  The database contains 2 types of entries: records and references
 * marked by the first byte in the data.  A record entry contains the actual
 * capability record whereas a reference contains the name (key) under which
 * the correct record is stored.
E 3
 */
D 3
void
E 3
I 3
int
E 3
main(argc, argv)
	int argc;
D 3
	char **argv;
E 3
I 3
	char *argv[];
E 3
{
D 8
	int c;
D 7
	char *outname;
E 7
I 7
	char *outname, *bak;
E 8
I 8
D 15
	int c, fd;
	char *outname, buf[MAXPATHLEN + 1], **f;
E 15
I 15
	int c;
E 15
D 11
	
E 11
E 8
E 7

D 15
	outname = NULL;
E 15
I 15
	capname = NULL;
E 15
D 12
	while ((c = getopt(argc, argv, "f:")) != EOF) {
E 12
I 12
	while ((c = getopt(argc, argv, "f:v")) != EOF) {
E 12
		switch(c) {
		case 'f':
D 15
			outname = optarg;
E 15
I 15
			capname = optarg;
E 15
			break;
I 12
		case 'v':
			verbose = 1;
			break;
E 12
		case '?':
D 3
		defualt:
E 3
I 3
		default:
E 3
			usage();
		}
D 11
	}		
E 11
I 11
	}
E 11
	argc -= optind;
D 11
	argv += optind;	
	
E 11
I 11
	argv += optind;

E 11
	if (*argv == NULL)
		usage();

D 15
	inputfiles = argv;

	if (outname == NULL)
		outname = *inputfiles;

D 3
	capdb = malloc(strlen(outname) + CAPDBNAMEEXTLEN + 1);
	if (capdb == NULL) {
		error("%s", strerror(ENOMEM));
		exit(1);
	}
	sprintf(capdb, "%s.db", outname);
E 3
I 3
#define CAPDBNAMEEXTLEN		3	/* ".db" */
	if ((capdb = malloc(strlen(outname) + CAPDBNAMEEXTLEN + 1)) == NULL)
D 5
		err("%s", strerror(errno));
E 5
I 5
		err(1, "%s", strerror(errno));
E 5
	(void)sprintf(capdb, "%s.db", outname);
E 3

E 15
I 7
D 8
	/* Create the backup: outname.db.BAK */

	if ((bak = malloc(strlen(outname) + CAPDBNAMEEXTLEN + 5)) == NULL)
		err(1, "%s", strerror(errno));
	(void)sprintf(bak, "%s.db.BAK", outname);
	
E 8
D 11
	/* 
	 * We want to avoid the confusion of where the capability record 
D 8
	 * is being read from.  Since we intend to read the ascii file, we
	 * should make sure that the corresponding .db file is not present to
	 * override.
E 8
I 8
	 * is being read from.  Since the user probably intends to read the 
	 * ascii file, we should make sure that user knows that the 
E 11
I 11
	/*
D 15
	 * We want to avoid the confusion of where the capability record
	 * is being read from.  Since the user probably intends to read the
	 * ascii file, we should make sure that user knows that the
E 11
	 * corresponding .db file will override.
E 15
I 15
	 * The database file is the first argument if no name is specified.
	 * Make arrangements to unlink it if exit badly.
E 15
E 8
D 11
         */
E 11
I 11
	 */
E 11
D 8
	if (unlink(bak) != 0 && errno != ENOENT)
		err(1, "unlink: %s -- %s", strerror(errno), bak);
	if (link(capdb, bak) != 0 && errno != ENOENT)
		err(1, "link: %s -- %s", strerror(errno), bak);
	if (errno != ENOENT && unlink(capdb) != 0)
		err(1, "unlink: %s -- %s", strerror(errno), capdb);
E 8
I 8
D 15
	for (f = inputfiles; *f != NULL; f++) {
		(void)sprintf(buf, "%s.db", *f);
D 12
		fd = open(buf, O_RDONLY, 0444);
E 12
I 12
		fd = open(buf, O_RDONLY, 0);
E 12
D 11
	        if (fd == -1 && errno != ENOENT)
			err(1, "open: %s", strerror(errno));
E 11
I 11
		if (fd == -1 && errno != ENOENT)
			err(1, "%s: %s", buf, strerror(errno));
E 11
		if (fd >= 0) {
D 12
			err(0, "Warning -- %s.db will override %s.", *f, *f);
E 12
I 12
			err(0, "%s.db overrides %s.", *f, *f);
E 12
			(void)close(fd);
		}
	}
E 15
I 15
	(void)snprintf(buf, sizeof(buf), "%s.db", capname ? capname : *argv);
	if ((capname = strdup(buf)) == NULL)
		err(1, "");
D 19
	if ((capdbp = dbopen(capname,
	    O_CREAT | O_TRUNC | O_RDWR, DEFFILEMODE, DB_HASH, NULL)) == NULL)
E 19
I 19
	if ((capdbp = dbopen(capname, O_CREAT | O_TRUNC | O_RDWR,
	    DEFFILEMODE, DB_HASH, &openinfo)) == NULL)
E 19
		err(1, "%s", buf);
E 15
E 8

E 7
D 11
        db_build(inputfiles);
E 11
I 11
D 15
	db_build(inputfiles);
E 15
I 15
	if (atexit(dounlink))
		err(1, "atexit");

	db_build(argv);

	if (capdbp->close(capdbp) < 0)
		err(1, "%s", capname);
	capname = NULL;
E 15
E 11
D 3
	free(capdb);
E 3
	exit(0);
}
D 11
   
E 11
I 11

I 15
void
dounlink()
{
	if (capname != NULL)
		(void)unlink(capname);
}

E 15
E 11
/*
 * Any changes to these definitions should be made also in the getcap(3)
 * library routines.
 */
I 3
D 6
#define	REFERENCE	(char)0
#define	RECORD		(char)1
E 6
E 3
D 15

E 15
I 6
#define RECOK	(char)0
#define TCERR	(char)1
I 15
#define SHADOW	(char)2
E 15
D 8

E 8

E 6
D 3
#define REFERENCE	(char)0
#define RECORD		(char)1
E 3
I 3
D 15
#define NBUFSIZ		(8 * 1024)
E 3

E 15
/*
 * Db_build() builds the name and capabilty databases according to the
 * details above.
 */
D 3

static void
E 3
I 3
void
E 3
D 15
db_build(inputfiles)
	char **inputfiles;
E 15
I 15
db_build(ifiles)
	char **ifiles;
E 15
{
D 15
	DB *capdbp;
E 15
	DBT key, data;
I 11
	recno_t reccnt;
E 11
D 3
	char *cp, *np, *bp, *nf, capstart;
	char namebuf[BUFSIZ];
E 3
D 15
	size_t lastlen, bplen;
D 5
	int st;
E 5
I 5
D 11
	int st, stdb, i;
E 11
I 11
	int st, stdb;
E 11
E 5
I 3
	char *cp, *np, *bp, *nf, namebuf[NBUFSIZ];
E 15
I 15
	size_t len, bplen;
	int st;
	char *bp, *p, *t;
E 15
I 4
D 5
	int i;
E 4
E 3

E 5
I 5
D 11
	
E 5
D 3
	if ((capdbp = dbopen(capdb, O_CREAT|O_TRUNC|O_WRONLY, 
            0644, DB_HASH, NULL)) == NULL) {
		error("Could not create capability database: %s\n", capdb);
		exit(1);
	}	
E 3
I 3
	if ((capdbp = dbopen(capdb, O_CREAT | O_TRUNC | O_WRONLY, 
            DEFFILEMODE, DB_HASH, NULL)) == NULL)
E 11
I 11

D 15
	if ((capdbp = dbopen(capdb, O_CREAT | O_TRUNC | O_RDWR,
	    DEFFILEMODE, DB_HASH, NULL)) == NULL)
E 11
D 5
		err("%s: %s", capdb, strerror(errno));
E 5
I 5
		err(1, "%s: %s", capdb, strerror(errno));
E 5
	docapdbunlink = 1;
E 3
D 11
	
E 11
I 11

E 11
	lastlen = 0;
I 3
	nf = NULL;
E 15
	data.data = NULL;
	key.data = NULL;
I 4
D 11
	i = 1;
E 4
E 3
	while((st = cgetnext(&bp, inputfiles)) > 0) {
E 11
I 11
D 15
	for (reccnt = 0; (st = cgetnext(&bp, inputfiles)) > 0;) {
E 11
		getnamefield(&nf, bp);
		if ((bplen = strlen(bp)) > lastlen) {
D 3
			data.data = realloc(data.data, lastlen + 2);
			if (data.data == NULL) {
				error("%s", strerror(ENOMEM));
				unlink(capdb);
				exit(1);
			}
E 3
I 3
D 11
			if ((data.data =
			    realloc(data.data, bplen + 2)) == NULL)
E 11
I 11
			if ((data.data = realloc(data.data, bplen + 2)) == NULL)
E 11
D 5
				err("%s", strerror(errno));
E 5
I 5
				err(1, "%s", strerror(errno));
E 5
E 3
			lastlen = bplen;
E 15
I 15
	for (reccnt = 0, bplen = 0; (st = cgetnext(&bp, ifiles)) > 0;) {

		/*
		 * Allocate enough memory to store record, terminating
		 * NULL and one extra byte.
		 */
		len = strlen(bp);
		if (bplen <= len + 2) {
			bplen += MAX(256, len + 2);
			if ((data.data = realloc(data.data, bplen)) == NULL)
				err(1, "");
E 15
		}

I 15
D 16
		/* First byte of stored record indicates error. */
		((char *)(data.data))[0] = st == 2 ? TCERR : RECOK;
E 16
I 16
		/* Find the end of the name field. */
		if ((p = strchr(bp, ':')) == NULL) {
			warnx("no name field: %.*s", MIN(len, 20), bp);
			continue;
		}
E 16

I 16
		/* First byte of stored record indicates status. */
		switch(st) {
		case 1:
			((char *)(data.data))[0] = RECOK;
			break;
		case 2:
			((char *)(data.data))[0] = TCERR;
			warnx("Record not tc expanded: %.*s", p - bp, bp);
			break;
		}

E 16
		/* Create the stored record. */
		memmove(&((u_char *)(data.data))[1], bp, len + 1);
		data.size = len + 2;

E 15
D 11
		/*
D 4
		 * Store record under primary name.
E 4
I 4
		 * Store record under name field.
E 4
		 */
E 11
I 11
D 16
		/* Store record under name field. */
E 11
D 6
		((char *)(data.data))[0] = RECORD;
E 6
I 6
D 15
		if (st == 2)
			((char *)(data.data))[0] = TCERR;
		else
			((char *)(data.data))[0] = RECOK;
E 15
I 15
		if ((p = strchr(bp, ':')) == NULL) {
			warn("no name field: %.*s", MIN(len, 20), bp);
			continue;
		}
E 16
I 16
		/* Store the record under the name field. */
E 16
		key.data = bp;
		key.size = p - bp;
E 15
D 11
			
E 11
I 11

E 11
E 6
D 3
		strcpy(&((char *)(data.data))[1], bp);
E 3
I 3
D 15
		(void)strcpy(&((char *)(data.data))[1], bp);
E 3
		data.size = bplen + 2;
D 4
		key.data = namebuf;
		np = namebuf;
		cp = nf;
		for (;;) {
			if (*cp == ':' || *cp == '|') {
                                *np = '\0';
                                key.size = strlen(namebuf) + 1;
D 3
                                if (capdbp->put(capdbp, &key, &data, 0) < 0) {
					error("%s", strerror(errno));
                                        exit(1);
                                }
E 3
I 3
                                if (capdbp->put(capdbp, &key, &data, 0) < 0)
					err("put: %s", strerror(errno));
E 3
				cp++;
				break;
			}
			*np++ = *cp++;
		}
E 4
I 4
		key.data = nf;
		key.size = strlen(nf) + 1;
D 5
		if (capdbp->put(capdbp, &key, &data, 0) < 0)
			err("put: %s", strerror(errno));
		
		printf("Hashed %d records.\r", i++);
E 5
I 5
D 11
		if ((stdb = capdbp->put(capdbp, &key, &data, R_NOOVERWRITE))
		    < 0)
E 11
I 11
		if ((stdb =
		    capdbp->put(capdbp, &key, &data, R_NOOVERWRITE)) < 0)
E 11
			err(1, "put: %s", strerror(errno));
		if (stdb == 1) {
D 11
			err(0, "put: record '%s' already exists -- only first reference is stored", nf);
E 11
I 11
			err(0, "ignored duplicate: %s", nf);
E 15
I 15
		switch(capdbp->put(capdbp, &key, &data, R_NOOVERWRITE)) {
		case -1:
			err(1, "put");
			/* NOTREACHED */
		case 1:
			warnx("ignored duplicate: %.*s",
			    key.size, (char *)key.data);
E 15
E 11
			continue;
		}
D 11
		printf("Hashed %d capability records.\r", i++);
I 7
		printnl = 1;
E 7
E 5
		fflush(stdout);
E 11
I 11
		++reccnt;
E 11
E 4

D 11
		/*
		 * Store references for other names.
		 */
E 11
I 11
D 15
		/* Store references for other names. */
E 11
D 6
		((char *)(data.data))[0] = REFERENCE;
D 3
		strcpy(&((char *)(data.data))[1], namebuf);
E 3
I 3
D 4
		(void)strcpy(&((char *)(data.data))[1], namebuf);
E 4
I 4
		(void)strcpy(&((char *)(data.data))[1], nf);
E 6
I 6
		(void)strcpy((char *)(data.data), nf);
E 15
I 15
		/* If only one name, ignore the rest. */
		if ((p = strchr(bp, '|')) == NULL)
			continue;
E 15
E 6
E 4
E 3

D 9
		data.size = key.size + 1;	/* need extra byte for tag */
E 9
I 9
D 15
		data.size = key.size;
E 9
D 4

		for (np = namebuf; *cp != '\0'; cp++) {
E 4
I 4
		key.data = namebuf;
		np = namebuf;
D 11
		for (cp = nf; *cp != '\0'; cp++) {
E 11
I 11
		for (cp = nf; *cp != '\0'; *np++ = *cp++)
E 11
E 4
			if (*cp == ':' || *cp == '|') {
				*np = '\0';
				key.size = strlen(namebuf) + 1;
D 3
				if (capdbp->put(capdbp, &key, &data, 0) < 0) {
					error("%s", strerror(errno));
					exit(1);
				}
E 3
I 3
D 5
				if (capdbp->put(capdbp, &key, &data, 0) < 0)
					err("put: %s", strerror(errno));
E 5
I 5
D 11
				if ((stdb = 
				    capdbp->put(capdbp, &key, &data, 
                   	  	    R_NOOVERWRITE)) < 0)
E 11
I 11
				if ((stdb = capdbp->put(capdbp, &key, &data,
				    R_NOOVERWRITE)) < 0)
E 11
					err(1, "put: %s", strerror(errno));
				if (stdb == 1)
D 11
					err(0, "put: record '%s' already exists -- only first reference is stored.", 
					    namebuf);
E 11
I 11
					err(0,
					    "ignored duplicate: %s", namebuf);
E 11
E 5
E 3
				np = namebuf;
				continue;
E 15
I 15
		/* The rest of the names reference the entire name. */
		((char *)(data.data))[0] = SHADOW;
		memmove(&((u_char *)(data.data))[1], key.data, key.size);
		data.size = key.size + 1;

		/* Store references for other names. */
		for (p = t = bp;; ++p) {
			if (p > t && (*p == ':' || *p == '|')) {
				key.size = p - t;
				key.data = t;
				switch(capdbp->put(capdbp,
				    &key, &data, R_NOOVERWRITE)) {
				case -1:
					err(1, "put");
					/* NOTREACHED */
				case 1:
					warnx("ignored duplicate: %.*s",
					    key.size, (char *)key.data);
				}
				t = p + 1;
E 15
D 11
			}	      	      
			*np++ = *cp;
		}
E 11
I 11
			}
I 15
			if (*p == ':')
				break;
		}
E 15
E 11
	}
D 3
	if (st == -1) {
		error("%s", strerror(errno));
		unlink(capdb);
		exit(1);
	}		
	if (st == -2) {
		error("Potential reference loop detected\n");
		unlink(capdb);
		exit(1);
	}		
	if (capdbp->close(capdbp) < 0) {
		error("%s", strerror(errno));
		exit(1);
	}
E 3
I 3
D 15
	if (capdbp->close(capdbp) < 0)
D 5
		err("%s", strerror(errno));
E 5
I 5
D 14
		err(1, "%s", strerror(errno));
E 14
I 14
		err(1, "%s: %s", capdb, strerror(errno));
E 15
E 14
I 11

E 11
E 5
D 15
	if (st == -1)
D 5
		err("%s", strerror(errno));
E 5
I 5
D 14
		err(1, "%s", strerror(errno));
E 14
I 14
		err(1, "file argument: %s", strerror(errno));
E 14
E 5
	if (st == -2)
D 5
		err("potential reference loop detected");
E 5
I 5
		err(1, "potential reference loop detected");
E 15
I 15
	switch(st) {
	case -1:
		err(1, "file argument");
		/* NOTREACHED */
	case -2:
		errx(1, "potential reference loop detected");
		/* NOTREACHED */
	}
E 15
I 11

E 11
E 5
E 3
D 15
	free(data.data);
	free(nf);
	free(bp);
I 4
D 11
	printf("\n");
E 11
I 11

E 15
D 12
	(void)printf("cap_mkdb: %d capability records\n", reccnt);
E 12
I 12
	if (verbose)
		(void)printf("cap_mkdb: %d capability records\n", reccnt);
E 12
E 11
E 4
}

D 3
static void
E 3
I 3
void
E 3
D 15
getnamefield(nf, bp)
	char **nf, *bp;
{
D 3
	static size_t nfsize = 0;
E 3
I 3
	static size_t nfsize;
E 3
	size_t newsize;
	char *cp, tmp;
D 11
	
E 11
I 11

E 11
D 3
	for (cp = bp; *cp != ':'; cp++) 
		;
E 3
I 3
	for (cp = bp; *cp != ':'; cp++);
E 3

D 3
	tmp = *(cp+1);
	*(cp+1) = '\0';
E 3
I 3
	tmp = *(cp + 1);
	*(cp + 1) = '\0';
E 3

	if ((newsize = cp - bp + 1) > nfsize) {
D 3
		*nf = realloc (*nf, newsize);
		if (*nf == NULL) {
			error("%s", strerror(ENOMEM));
			unlink(capdb);
			exit(1);
		}
E 3
I 3
		if ((*nf = realloc(*nf, newsize)) == NULL)
D 5
			err("%s", strerror(errno));
E 5
I 5
			err(1, "%s", strerror(errno));
E 5
E 3
		nfsize = newsize;
	}
D 3
	
	strcpy(*nf, bp);
	*(cp+1) = tmp;
E 3
I 3
	(void)strcpy(*nf, bp);
	*(cp + 1) = tmp;
E 3
}

D 3
static void
E 3
I 3
void
E 15
E 3
usage()
{
D 2
        (void)fprintf(stderr, "usage: mkcapdb [-f outfile] file1 [file2 ...]\n");
E 2
I 2
D 3
        (void)fprintf(stderr, "usage: cap_mkdb [-f outfile] file1 [file2 ...]\n");
E 3
I 3
D 11
        (void)fprintf(stderr,
E 11
I 11
	(void)fprintf(stderr,
E 11
D 13
	    "usage: cap_mkdb [-f outfile] file1 [file2 ...]\n");
E 13
I 13
	    "usage: cap_mkdb [-v] [-f outfile] file1 [file2 ...]\n");
E 13
E 3
E 2
D 11
        exit(1);
E 11
I 11
	exit(1);
E 11
D 15
}

D 3

E 3
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

D 3
static void
E 3
I 3
void
E 3
#if __STDC__
D 3
error(const char *fmt, ...)
E 3
I 3
D 5
err(const char *fmt, ...)
E 5
I 5
err(int fatal, const char *fmt, ...)
E 5
E 3
#else
D 3
error(fatal, fmt, va_alist)
        int fatal;
        char *fmt;
E 3
I 3
err(fmt, va_alist)
	char *fmt;
E 3
D 11
        va_dcl
E 11
I 11
	va_dcl
E 11
#endif
{
D 3
        va_list ap;
E 3
I 3
	va_list ap;
E 3
#if __STDC__
D 3
        va_start(ap, fmt);
E 3
I 3
	va_start(ap, fmt);
E 3
#else
D 3
        va_start(ap);
E 3
I 3
	va_start(ap);
E 3
#endif
I 5
D 7
	(void)fprintf(stderr, "\n");
E 7
I 7

	if (printnl)
		(void)fprintf(stderr, "\n");
E 7
E 5
D 3
        (void)fprintf(stderr, "cap_mkdb: ");
        (void)vfprintf(stderr, fmt, ap);
        va_end(ap);
        (void)fprintf(stderr, "\n");
E 3
I 3
	(void)fprintf(stderr, "cap_mkdb: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
D 5
	if (docapdbunlink)
		(void)unlink(capdb);
	exit(1);
	/* NOTREACHED */
E 5
I 5
	if (fatal) {
		if (docapdbunlink)
			(void)unlink(capdb);
		exit(1);
	}
E 15
E 5
E 3
}
E 1
