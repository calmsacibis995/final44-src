h36994
s 00002/00002/00342
d D 8.5 95/04/28 10:38:13 bostic 12 11
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00032/00020/00312
d D 8.4 95/04/27 11:32:50 mckusick 11 10
c add function prototypes
e
s 00014/00013/00318
d D 8.3 94/12/06 10:53:19 mckusick 10 9
c if attempts to translate name fails, return original
e
s 00005/00002/00326
d D 8.2 94/11/30 11:17:40 mckusick 9 8
c when given non block or character device to check, let user decide
e
s 00002/00002/00326
d D 8.1 93/06/05 10:56:50 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00325
d D 5.7 91/03/19 15:29:08 mckusick 7 6
c fix bletcherous code
e
s 00002/00002/00326
d D 5.6 90/08/07 11:00:00 karels 6 5
c fix QUIT processing for preen (was broken when preen.c split out)
e
s 00009/00008/00319
d D 5.5 90/07/20 16:51:49 mckusick 5 4
c lint (from Torek)
e
s 00001/00011/00326
d D 5.4 90/06/01 16:17:48 bostic 4 3
c new copyright notice
e
s 00001/00001/00336
d D 5.3 90/05/15 19:53:12 bostic 3 2
c string.h is ANSI C include file
e
s 00002/00001/00335
d D 5.2 90/05/05 12:59:08 mckusick 2 1
c hotroot is a char, not an int!
e
s 00336/00000/00000
d D 5.1 90/04/26 23:41:39 mckusick 1 0
c date and time created 90/04/26 23:41:39 by mckusick
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/wait.h>
I 11

#include <ufs/ufs/dinode.h>

#include <ctype.h>
E 11
#include <fstab.h>
D 3
#include <strings.h>
E 3
I 3
#include <string.h>
E 3
D 11
#include <stdio.h>
I 5
#include <stdlib.h>
E 5
#include <ctype.h>
E 11

D 5
char	*rawname(), *unrawname(), *blockcheck(), *malloc();
E 5
I 5
D 11
char	*rawname(), *unrawname(), *blockcheck();
E 11
I 11
#include "fsck.h"
E 11
E 5

struct part {
	struct	part *next;		/* forward link of partitions on disk */
	char	*name;			/* device name */
	char	*fsname;		/* mounted filesystem name */
	long	auxdata;		/* auxillary data for application */
} *badlist, **badnext = &badlist;

struct disk {
	char	*name;			/* disk base name */
	struct	disk *next;		/* forward link for list of disks */
	struct	part *part;		/* head of list of partitions on disk */
	int	pid;			/* If != 0, pid of proc working on */
} *disks;

D 2
int	nrun, ndisks, hotroot;
E 2
I 2
int	nrun, ndisks;
char	hotroot;
E 2

I 11
static void addpart __P((char *name, char *fsname, long auxdata));
static struct disk *finddisk __P((char *name));
static char *rawname __P((char *name));
static int startdisk __P((struct disk *dk,
		int (*checkit)(char *, char *, long, int)));
static char *unrawname __P((char *name));

int
E 11
checkfstab(preen, maxrun, docheck, chkit)
D 11
	int preen, maxrun;
	int (*docheck)(), (*chkit)();
E 11
I 11
	int preen;
	int maxrun;
	int (*docheck)(struct fstab *);
	int (*chkit)(char *, char *, long, int);
E 11
{
	register struct fstab *fsp;
	register struct disk *dk, *nextdisk;
	register struct part *pt;
	int ret, pid, retcode, passno, sumstatus, status;
	long auxdata;
	char *name;

	sumstatus = 0;
	for (passno = 1; passno <= 2; passno++) {
		if (setfsent() == 0) {
			fprintf(stderr, "Can't open checklist file: %s\n",
			    _PATH_FSTAB);
			return (8);
		}
		while ((fsp = getfsent()) != 0) {
			if ((auxdata = (*docheck)(fsp)) == 0)
				continue;
D 11
			if (preen == 0 || passno == 1 && fsp->fs_passno == 1) {
				if (name = blockcheck(fsp->fs_spec)) {
					if (sumstatus = (*chkit)(name,
D 6
					    fsp->fs_file, auxdata))
E 6
I 6
					    fsp->fs_file, auxdata, 0))
E 11
I 11
			if (preen == 0 ||
			    (passno == 1 && fsp->fs_passno == 1)) {
				if ((name = blockcheck(fsp->fs_spec)) != 0) {
					if ((sumstatus = (*chkit)(name,
					    fsp->fs_file, auxdata, 0)) != 0)
E 11
E 6
						return (sumstatus);
				} else if (preen)
					return (8);
			} else if (passno == 2 && fsp->fs_passno > 1) {
				if ((name = blockcheck(fsp->fs_spec)) == NULL) {
					fprintf(stderr, "BAD DISK NAME %s\n",
						fsp->fs_spec);
					sumstatus |= 8;
					continue;
				}
				addpart(name, fsp->fs_file, auxdata);
			}
		}
		if (preen == 0)
			return (0);
	}
	if (preen) {
		if (maxrun == 0)
			maxrun = ndisks;
		if (maxrun > ndisks)
			maxrun = ndisks;
		nextdisk = disks;
		for (passno = 0; passno < maxrun; ++passno) {
D 11
			while (ret = startdisk(nextdisk, chkit) && nrun > 0)
E 11
I 11
			while ((ret = startdisk(nextdisk, chkit)) && nrun > 0)
E 11
				sleep(10);
			if (ret)
				return (ret);
			nextdisk = nextdisk->next;
		}
		while ((pid = wait(&status)) != -1) {
			for (dk = disks; dk; dk = dk->next)
				if (dk->pid == pid)
					break;
			if (dk == 0) {
				printf("Unknown pid %d\n", pid);
				continue;
			}
			if (WIFEXITED(status))
				retcode = WEXITSTATUS(status);
			else
				retcode = 0;
			if (WIFSIGNALED(status)) {
				printf("%s (%s): EXITED WITH SIGNAL %d\n",
					dk->part->name, dk->part->fsname,
					WTERMSIG(status));
				retcode = 8;
			}
			if (retcode != 0) {
				sumstatus |= retcode;
				*badnext = dk->part;
				badnext = &dk->part->next;
				dk->part = dk->part->next;
				*badnext = NULL;
			} else
				dk->part = dk->part->next;
			dk->pid = 0;
			nrun--;
			if (dk->part == NULL)
				ndisks--;

			if (nextdisk == NULL) {
				if (dk->part) {
D 11
					while (ret = startdisk(dk, chkit) &&
E 11
I 11
					while ((ret = startdisk(dk, chkit)) &&
E 11
					    nrun > 0)
						sleep(10);
					if (ret)
						return (ret);
				}
			} else if (nrun < maxrun && nrun < ndisks) {
				for ( ;; ) {
					if ((nextdisk = nextdisk->next) == NULL)
						nextdisk = disks;
					if (nextdisk->part != NULL &&
					    nextdisk->pid == 0)
						break;
				}
D 11
				while (ret = startdisk(nextdisk, chkit) &&
E 11
I 11
				while ((ret = startdisk(nextdisk, chkit)) &&
E 11
				    nrun > 0)
					sleep(10);
				if (ret)
					return (ret);
			}
		}
	}
	if (sumstatus) {
		if (badlist == 0)
			return (sumstatus);
		fprintf(stderr, "THE FOLLOWING FILE SYSTEM%s HAD AN %s\n\t",
			badlist->next ? "S" : "", "UNEXPECTED INCONSISTENCY:");
		for (pt = badlist; pt; pt = pt->next)
			fprintf(stderr, "%s (%s)%s", pt->name, pt->fsname,
			    pt->next ? ", " : "\n");
		return (sumstatus);
	}
	(void)endfsent();
	return (0);
}

D 11
struct disk *
E 11
I 11
static struct disk *
E 11
finddisk(name)
	char *name;
{
	register struct disk *dk, **dkp;
	register char *p;
D 5
	int len;
E 5
I 5
	size_t len;
E 5

D 11
	for (p = name + strlen(name) - 1; p >= name; --p)
E 11
I 11
	for (len = strlen(name), p = name + len - 1; p >= name; --p)
E 11
		if (isdigit(*p)) {
			len = p - name + 1;
			break;
		}
D 11
	if (p < name)
		len = strlen(name);
E 11

	for (dk = disks, dkp = &disks; dk; dkp = &dk->next, dk = dk->next) {
		if (strncmp(dk->name, name, len) == 0 &&
		    dk->name[len] == 0)
			return (dk);
	}
	if ((*dkp = (struct disk *)malloc(sizeof(struct disk))) == NULL) {
		fprintf(stderr, "out of memory");
		exit (8);
	}
	dk = *dkp;
D 5
	if ((dk->name = malloc((unsigned int)len + 1)) == NULL) {
E 5
I 5
	if ((dk->name = malloc(len + 1)) == NULL) {
E 5
		fprintf(stderr, "out of memory");
		exit (8);
	}
D 5
	strncpy(dk->name, name, len);
E 5
I 5
	(void)strncpy(dk->name, name, len);
E 5
	dk->name[len] = '\0';
	dk->part = NULL;
	dk->next = NULL;
	dk->pid = 0;
	ndisks++;
	return (dk);
}

I 11
static void
E 11
addpart(name, fsname, auxdata)
	char *name, *fsname;
	long auxdata;
{
	struct disk *dk = finddisk(name);
	register struct part *pt, **ppt = &dk->part;

	for (pt = dk->part; pt; ppt = &pt->next, pt = pt->next)
		if (strcmp(pt->name, name) == 0) {
			printf("%s in fstab more than once!\n", name);
			return;
		}
	if ((*ppt = (struct part *)malloc(sizeof(struct part))) == NULL) {
		fprintf(stderr, "out of memory");
		exit (8);
	}
	pt = *ppt;
D 5
	if ((pt->name = malloc((unsigned int)strlen(name) + 1)) == NULL) {
E 5
I 5
	if ((pt->name = malloc(strlen(name) + 1)) == NULL) {
E 5
		fprintf(stderr, "out of memory");
		exit (8);
	}
D 5
	strcpy(pt->name, name);
	if ((pt->fsname = malloc((unsigned int)strlen(fsname) + 1)) == NULL) {
E 5
I 5
	(void)strcpy(pt->name, name);
	if ((pt->fsname = malloc(strlen(fsname) + 1)) == NULL) {
E 5
		fprintf(stderr, "out of memory");
		exit (8);
	}
D 5
	strcpy(pt->fsname, fsname);
E 5
I 5
	(void)strcpy(pt->fsname, fsname);
E 5
	pt->next = NULL;
	pt->auxdata = auxdata;
}

I 11
static int
E 11
startdisk(dk, checkit)
	register struct disk *dk;
D 11
	int (*checkit)();
E 11
I 11
	int (*checkit)(char *, char *, long, int);
E 11
{
	register struct part *pt = dk->part;

	dk->pid = fork();
	if (dk->pid < 0) {
		perror("fork");
		return (8);
	}
	if (dk->pid == 0)
D 6
		exit((*checkit)(pt->name, pt->fsname, pt->auxdata));
E 6
I 6
		exit((*checkit)(pt->name, pt->fsname, pt->auxdata, 1));
E 6
	nrun++;
	return (0);
}

char *
D 10
blockcheck(name)
	char *name;
E 10
I 10
blockcheck(origname)
	char *origname;
E 10
{
	struct stat stslash, stblock, stchar;
D 10
	char *raw;
E 10
I 10
	char *newname, *raw;
E 10
	int retried = 0;

	hotroot = 0;
	if (stat("/", &stslash) < 0) {
		perror("/");
		printf("Can't stat root\n");
D 10
		return (0);
E 10
I 10
		return (origname);
E 10
	}
I 10
	newname = origname;
E 10
retry:
D 10
	if (stat(name, &stblock) < 0) {
		perror(name);
		printf("Can't stat %s\n", name);
		return (0);
E 10
I 10
	if (stat(newname, &stblock) < 0) {
		perror(newname);
		printf("Can't stat %s\n", newname);
		return (origname);
E 10
	}
	if ((stblock.st_mode & S_IFMT) == S_IFBLK) {
		if (stslash.st_dev == stblock.st_rdev)
			hotroot++;
D 10
		raw = rawname(name);
E 10
I 10
		raw = rawname(newname);
E 10
		if (stat(raw, &stchar) < 0) {
			perror(raw);
			printf("Can't stat %s\n", raw);
D 10
			return (name);
E 10
I 10
			return (origname);
E 10
		}
		if ((stchar.st_mode & S_IFMT) == S_IFCHR) {
			return (raw);
		} else {
			printf("%s is not a character device\n", raw);
D 10
			return (name);
E 10
I 10
			return (origname);
E 10
		}
	} else if ((stblock.st_mode & S_IFMT) == S_IFCHR && !retried) {
D 10
		name = unrawname(name);
E 10
I 10
		newname = unrawname(newname);
E 10
		retried++;
		goto retry;
	}
D 9
	printf("Can't make sense out of name %s\n", name);
	return (0);
E 9
I 9
	/*
	 * Not a block or character device, just return name and
	 * let the user decide whether to use it.
	 */
D 10
	return (name);
E 10
I 10
	return (origname);
E 10
E 9
}

D 11
char *
E 11
I 11
static char *
E 11
unrawname(name)
	char *name;
{
	char *dp;
	struct stat stb;

D 12
	if ((dp = rindex(name, '/')) == 0)
E 12
I 12
	if ((dp = strrchr(name, '/')) == 0)
E 12
		return (name);
	if (stat(name, &stb) < 0)
		return (name);
	if ((stb.st_mode & S_IFMT) != S_IFCHR)
		return (name);
D 7
	if (*(dp + 1) != 'r')
E 7
I 7
	if (dp[1] != 'r')
E 7
		return (name);
D 7
	(void)strcpy(dp + 1, dp + 2);
E 7
I 7
	(void)strcpy(&dp[1], &dp[2]);
E 7
	return (name);
}

D 11
char *
E 11
I 11
static char *
E 11
rawname(name)
	char *name;
{
	static char rawbuf[32];
	char *dp;

D 12
	if ((dp = rindex(name, '/')) == 0)
E 12
I 12
	if ((dp = strrchr(name, '/')) == 0)
E 12
		return (0);
	*dp = 0;
	(void)strcpy(rawbuf, name);
	*dp = '/';
	(void)strcat(rawbuf, "/r");
D 7
	(void)strcat(rawbuf, dp + 1);
E 7
I 7
	(void)strcat(rawbuf, &dp[1]);
E 7
	return (rawbuf);
}
E 1
