h29683
s 00002/00002/00052
d D 8.2 95/04/29 11:29:16 bostic 22 21
c change devname(3) to return NULL on error, not "??"
e
s 00002/00002/00052
d D 8.1 93/06/04 12:01:09 bostic 21 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00052
d R 8.1 93/05/31 15:05:29 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00008/00045
d D 5.18 93/04/29 13:18:56 bostic 19 18
c use err/warn from the C library
e
s 00003/00001/00050
d D 5.17 93/03/09 03:16:22 torek 18 17
c device keys may contain padding, so make sure it is zero bytes
e
s 00001/00000/00050
d D 5.16 92/06/05 18:56:48 bostic 17 16
c ANSI prototypes (two real bugs)
e
s 00003/00002/00047
d D 5.15 91/11/04 22:24:59 bostic 16 15
c hash_open -> dbopen
e
s 00015/00004/00034
d D 5.14 91/05/06 17:53:42 bostic 15 14
c change dev database to use "mode_t type dev_t dev" as the key
e
s 00001/00001/00037
d D 5.13 91/03/03 13:32:13 bostic 14 13
c forgot to switch the include file from ndbm.h to db.h
e
s 00007/00007/00031
d D 5.12 91/03/03 13:29:41 bostic 13 12
c convert from ndbm(3) to db(3) interface
e
s 00001/00001/00037
d D 5.11 91/02/08 17:50:31 bostic 12 11
c only print the "no database" message once
e
s 00001/00001/00037
d D 5.10 91/02/08 17:21:47 bostic 11 10
c _PATH_DEVDB is in <paths.h> now
e
s 00017/00158/00021
d D 5.9 91/02/08 11:17:07 bostic 10 9
c Put print/keyword routines into separate modules; delete attime.c, use
c strftime(3) instead; put combination keywords into main keyword list,
c sort, delete aliases, and use bsearch(3); don't fail if nlist fails or
c devices aren't found.  Whack the manual page for consistency, correctness.
e
s 00002/00002/00177
d D 5.8 90/11/07 18:34:11 marc 9 8
c reduce size of devname entry 
e
s 00138/00050/00041
d D 5.7 90/08/30 11:55:08 marc 8 7
c fixes from chris
e
s 00001/00001/00090
d D 5.6 90/08/17 17:36:03 marc 7 6
c hash table off by 1
e
s 00001/00011/00090
d D 5.5 90/05/31 20:36:03 bostic 6 5
c new copyright notice
e
s 00001/00001/00100
d D 5.4 90/05/03 11:32:09 marc 5 4
c cleanup size of array
e
s 00005/00004/00096
d D 5.3 90/04/18 13:39:46 marc 4 2
c use S_IFBLK or S_IFCHR to indicate type of special file
e
s 00002/00002/00098
d R 5.3 90/04/18 13:31:35 marc 3 2
c use value S_IFCHR or S_IFBLK for specifying type of device
e
s 00055/00023/00045
d D 5.2 90/04/18 13:24:40 marc 2 1
c make work on block or character special
e
s 00068/00000/00000
d D 5.1 90/03/01 21:44:24 marc 1 0
c date and time created 90/03/01 21:44:24 by marc
e
u
U
t
T
I 2
/*
D 21
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

E 2
I 1
#include <sys/types.h>
D 2
#include <sys/dir.h>
E 2
D 10
#include <sys/stat.h>
D 2
#include "pathnames.h"
#include <stdio.h>
E 2
I 2
#include <sys/file.h>
#include <dirent.h>
E 10
I 10
D 19
#include <fcntl.h>
I 16
#include <errno.h>
E 19
I 19

E 19
E 16
D 14
#include <ndbm.h>
E 14
I 14
#include <db.h>
I 19
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <paths.h>
E 19
E 14
E 10
I 8
#include <stdio.h>
I 17
#include <string.h>
E 17
D 10
#include <stdlib.h>
#include <string.h>
E 8
#include <paths.h>
E 10
I 10
D 11
#include "pathnames.h"
E 11
I 11
D 19
#include <paths.h>
E 19
E 11
E 10
E 2

D 2
struct devs {
E 2
I 2
D 8
static struct devs {
E 8
I 8
D 10
/*
 * Routine to convert a major+minor device number (st_rdev field)
 * plus a mode (S_IFCHR or S_IFBLK) into a name relative to /dev.
 *
 * We build a hash table of everything in /dev, with the hash being
 * a function of the number and mode.
 */

#define	HASHSIZ	512		/* MUST BE A POWER OF 2 */
#define	hash(x, t)	((((t) >> 14) + 4*minor(x) + major(x)) & (HASHSIZ-1))

struct devs {
E 8
	struct	devs *next;
E 2
	dev_t	dev;
D 8
	char	name[MAXNAMLEN+1];
E 8
D 2
	struct	devs *next;
E 2
I 2
D 4
	char	type;
E 4
I 4
	mode_t	type;
I 8
D 9
	char	name[MAXNAMLEN + 1];
E 9
I 9
	char	*name;
E 9
E 8
E 4
E 2
};

D 2
struct devs *devhash[minor(~0)];
E 2
I 2
D 8
#define	hash(x)	((x)&0xff)
D 5
static struct devs *devhash[minor(~0)];
E 5
I 5
D 7
static struct devs *devhash[0xff];
E 7
I 7
static struct devs *devhash[0xff + 1];
E 8
I 8
static struct devs *devhash[HASHSIZ];
E 8
E 7
E 5
E 2

D 2
int devinit;
E 2
I 2
D 8
static int devinit;
E 8
I 8
#ifdef TEST
int	chainlen[HASHSIZ];
int	verbose;
#endif
E 8
E 2

I 8
static int
add(type, dev, name)
	mode_t type;
	dev_t dev;
	char *name;
{
	register struct devs *devp, **p;
	int h;

	devp = (struct devs *)malloc(sizeof *devp);
	if (devp == NULL)
		return (0);
	devp->next = NULL;
	devp->dev = dev;
	devp->type = type;
D 9
	(void) strcpy(devp->name, name);
E 9
I 9
	devp->name = strdup(name);
E 9
	h = hash(dev, type);
	for (p = &devhash[h]; *p; p = &(*p)->next)
		/* void */;
	*p = devp;
#ifdef TEST
	chainlen[h]++;
	if (verbose)
		(void) printf("adding %c %d,%d %s (hash=%d)\n",
		    type == S_IFBLK ? 'b': 'c', major(dev), minor(dev),
		    name, h);
#endif
	return (1);
}

static int
init_by_stat()
{
	register struct dirent *entry;
	struct stat sb;
	DIR *dp;
	int savewd;
	mode_t specialtype;

	if ((savewd = open(".", O_RDONLY, 0)) == -1)
		return (0);
	if (chdir(_PATH_DEV) == -1) {
		(void) close(savewd);
		return (0);
	}
	if ((dp = opendir(".")) == NULL) {
		(void) fchdir(savewd);
		(void) close(savewd);
		return (0);
	}
	while ((entry = readdir(dp)) != NULL) {
		if (stat(entry->d_name, &sb) == -1)
			continue;
		switch (sb.st_mode & S_IFMT) {
		case S_IFCHR:
			specialtype = S_IFCHR;
			break;
		case S_IFBLK:
			specialtype = S_IFBLK;
			break;
		default:
			continue;
		}
		if (!add(specialtype, sb.st_rdev, entry->d_name))
			break;
	}
	(void) fchdir(savewd);
	(void) close(savewd);
	(void) closedir(dp);
	return (1);
}

static int
init_by_db()
{
	register FILE *fp;
	char type, name[MAXNAMLEN + 1];
	int maj, min;
#define specialtype(c) ((c) == 'b' ? (mode_t)S_IFBLK : (mode_t)S_IFCHR)

	if ((fp = fopen("/var/run/devdatabase", "r")) == NULL)
		return (0);
	while (fscanf(fp, " %c %d,%d %s", &type, &maj, &min, name) == 4)
		if (!add(specialtype(type), makedev(maj, min), name))
			break;
	(void) fclose(fp);
	return (1);
#undef specialtype
}

E 10
E 8
D 2
/* TODO - use a database file stored in /dev, - just check mod time on /dev 
	hide data structures 
*/

E 2
char *
D 2
devname(dev)
E 2
I 2
D 10
devname(dev, type)
E 10
I 10
D 15
devname(dev)
E 15
I 15
devname(dev, type)
E 15
E 10
E 2
	dev_t dev;
I 15
	mode_t type;
E 15
I 4
D 10
	mode_t type;
E 10
E 4
{
I 15
	struct {
		mode_t type;
		dev_t dev;
	} bkey;
E 15
D 8
	struct devs *devp;
E 8
I 8
D 10
	register struct devs *devp;
	static int devinit;
E 10
I 10
D 13
	static DBM *db;
E 13
I 13
	static DB *db;
E 13
	static int failure;
D 13
	datum dp, key;
E 13
I 13
	DBT data, key;
E 13
E 10
E 8

D 8
	if (devinit == 0) {
D 2
		DIR *dp = opendir(_PATH_DEV);
		struct direct *entry;
E 2
I 2
		register struct devs *devpp;
		register struct dirent *entry;
E 2
		struct stat sb;
D 2
		struct devs *devpp;
E 2
I 2
		DIR *dp = opendir(_PATH_DEV);
		int savewd = open(".", O_RDONLY, 0);
D 4
		int specialtype;
E 4
I 4
		mode_t specialtype;
E 4
E 2

D 2
		/* XXX XXX - can't chdir as a library routine (add flag?) */
		if (dp == NULL || chdir(_PATH_DEV) == -1)
E 2
I 2
		if (savewd == -1 || dp == NULL || chdir(_PATH_DEV) == -1)
E 8
I 8
D 10
	if (!devinit) {
		if (!init_by_db() && !init_by_stat())
E 8
E 2
			return (NULL);
D 8
		while ((entry = readdir(dp)) != NULL) {
			if (stat(entry->d_name, &sb) == -1)
				continue;
D 2
			if ((sb.st_mode&S_IFMT) != S_IFCHR)
E 2
I 2
			switch(sb.st_mode&S_IFMT) {
			case S_IFCHR:
D 4
				specialtype = 1;
E 4
I 4
				specialtype = S_IFCHR;
E 4
				break;
			case S_IFBLK:
D 4
				specialtype = 0;
E 4
I 4
				specialtype = S_IFBLK;
E 4
				break;
			default:
E 2
				continue;
I 2
			}
E 2
			devp = (struct devs *)malloc(sizeof (struct devs));
			if (devp == NULL)
				return (NULL);
I 2
			devp->type = specialtype;
E 2
			devp->dev = sb.st_rdev;
			strcpy(devp->name, entry->d_name);
			devp->next = NULL;
D 2
			if ((devpp = devhash[minor(sb.st_rdev)]) == NULL)
				devhash[minor(sb.st_rdev)] = devp;
E 2
I 2
			if ((devpp = devhash[hash(sb.st_rdev)]) == NULL)
				devhash[hash(sb.st_rdev)] = devp;
E 2
			else {
				for (;devpp->next != NULL; devpp = devpp->next)
					;
				devpp->next = devp;
			}
		}
D 2
		devinit = 1; 	/* XXX - should have way to invalidate cache ?*/
E 2
I 2
		fchdir(savewd);
		close(savewd);
		closedir(dp);
E 8
		devinit = 1;
E 10
I 10
D 12
	if (!db && !(db = dbm_open(_PATH_DEVDB, O_RDONLY, 0))) {
E 12
I 12
D 13
	if (!db && !failure && !(db = dbm_open(_PATH_DEVDB, O_RDONLY, 0))) {
E 13
I 13
	if (!db && !failure &&
D 16
	    !(db = hash_open(_PATH_DEVDB, O_RDONLY, 0, NULL))) {
E 16
I 16
	    !(db = dbopen(_PATH_DEVDB, O_RDONLY, 0, DB_HASH, NULL))) {
E 16
E 13
E 12
D 19
		(void)fprintf(stderr,
D 15
		    "ps: no device database %s\n", _PATH_DEVDB);
E 15
I 15
D 16
		    "warning: no device database %s\n", _PATH_DEVDB);
E 16
I 16
		    "warning: %s: %s\n", _PATH_DEVDB, strerror(errno));
E 19
I 19
		warn("warning: %s", _PATH_DEVDB);
E 19
E 16
E 15
		failure = 1;
E 10
E 2
	}
D 2
	for (devp = devhash[minor(dev)]; devp != NULL; devp = devp->next)
		if (dev == devp->dev)
E 2
I 2
D 8
	for (devp = devhash[hash(dev)]; devp != NULL; devp = devp->next)
E 8
I 8
D 10
	for (devp = devhash[hash(dev, type)]; devp != NULL; devp = devp->next)
E 8
		if (dev == devp->dev && type == devp->type)
E 2
D 8
			return(devp->name);
E 8
I 8
			return (devp->name);
E 10
I 10
	if (failure)
D 19
		return("??");
E 19
I 19
D 22
		return ("??");
E 22
I 22
		return (NULL);
E 22
E 19
E 10
E 8

D 10
	return (NULL);
E 10
I 10
D 13
	key.dptr = (char *)&dev;
	key.dsize = sizeof(dev);
	dp = dbm_fetch(db, key);
	return(dp.dptr ? dp.dptr : "??");
E 13
I 13
D 15
	key.data = (u_char *)&dev;
	key.size = sizeof(dev);
E 15
I 15
	/*
	 * Keys are a mode_t followed by a dev_t.  The former is the type of
D 18
	 * the file (mode & S_IFMT), the latter is the st_rdev field.
E 18
I 18
	 * the file (mode & S_IFMT), the latter is the st_rdev field.  Be
	 * sure to clear any padding that may be found in bkey.
E 18
	 */
I 18
D 19
	bzero(&bkey, sizeof(bkey));
E 19
I 19
	memset(&bkey, 0, sizeof(bkey));
E 19
E 18
	bkey.dev = dev;
	bkey.type = type;
	key.data = &bkey;
	key.size = sizeof(bkey);
E 15
D 19
	return((db->get)(db, &key, &data, 0L) ? "??" : (char *)data.data);
E 19
I 19
D 22
	return ((db->get)(db, &key, &data, 0) ? "??" : (char *)data.data);
E 22
I 22
	return ((db->get)(db, &key, &data, 0) ? NULL : (char *)data.data);
E 22
E 19
E 13
E 10
}
D 10

#ifdef TEST
D 8
main() {
	printf(" %s \n", devname(0));
E 8
I 8
main(argc, argv)
	int argc;
	char **argv;
{
	register int i, sum, longest;
	struct stat st;
	char *p, *ttyname();

	if (argc > 1 && strcmp(argv[1], "-v") == 0)
		verbose = 1, argc--, argv++;
	p = argc > 1 ? argv[1] : ttyname(0);
	(void) stat(p, &st);
	(void) printf(" %s \n", devname(st.st_rdev, (mode_t)S_IFCHR));
	longest = sum = 0;
	for (i = 0; i < HASHSIZ; i++) {
		sum += chainlen[i];
		if (chainlen[i] > longest)
			longest = chainlen[i];
	}
	(void) printf("average hash chain length %.2f, longest %d\n",
	    (double)sum / HASHSIZ, longest);
E 8
}
#endif
E 10
E 1
