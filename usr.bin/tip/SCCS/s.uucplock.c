h06285
s 00002/00002/00081
d D 8.1 93/06/06 16:35:04 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00082
d D 5.5 90/06/01 17:48:09 bostic 11 10
c new copyright notice
e
s 00005/00009/00088
d D 5.4 89/05/11 09:38:47 bostic 10 9
c file reorg, pathnames.h, paths.h
e
s 00074/00195/00023
d D 5.3 88/09/02 11:29:20 bostic 9 8
c written from scratch uucp style locking routines
e
s 00001/00001/00217
d D 5.2 85/11/29 19:35:22 donn 8 7
c Bumped NAMESIZE from 15 to 32; the old value was clearly insufficient.
c From Terry Laskodi at Tektronix.
e
s 00008/00001/00210
d D 5.1 85/04/30 12:32:07 dist 7 6
c Add copyright
e
s 00003/00003/00208
d D 4.6 83/06/25 01:14:55 sam 6 5
c so much...clean up after ralph's merge of wendel and mo code;
c purge VMUNIX include since changes for signals make it no longer portable 
c to systems other than 4.2; fix ventel for no echo strapping; do setjmps 
c instead of assuming interrupted system calls; purge lcmd, if people use 
e
s 00004/00002/00207
d D 4.5 83/06/15 13:53:09 ralph 5 4
c changes for local info, parity, vadic auto dialers
e
s 00001/00001/00208
d D 4.4 82/07/29 15:25:51 shannon 4 3
c Make tempfile larger
e
s 00019/00021/00190
d D 4.3 81/11/29 22:51:15 sam 3 2
c reformatting
e
s 00008/00008/00203
d D 4.2 81/11/20 10:45:12 sam 2 1
c cosmetics
e
s 00211/00000/00000
d D 4.1 81/05/09 16:45:27 root 1 0
c date and time created 81/05/09 16:45:27 by root
e
u
U
t
T
I 7
/*
D 9
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
D 12
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 11
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 9
 */

E 7
I 1
D 6
/*	%M%	%I%	%E%	*/
E 6
I 6
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif
E 7
I 7
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9

E 7
E 6
D 9
/*
 * defs that come from uucp.h
 */
D 8
#define NAMESIZE 15
E 8
I 8
#define NAMESIZE 32
E 8
#define FAIL -1
#define SAME 0
D 5
#define SLCKTIME 5400	/* system/device timeout (LCK.. files) in seconds */
E 5
I 5
#define SLCKTIME 28800	/* system/device timeout (LCK.. files) in seconds (8 hours) */
E 5
#define ASSERT(e, f, v) if (!(e)) {\
	fprintf(stderr, "AERROR - (%s) ", "e");\
	fprintf(stderr, f, v);\
	finish(FAIL);\
}
E 9
I 9
#include <sys/types.h>
#include <sys/file.h>
#include <sys/dir.h>
#include <errno.h>
I 10
#include "pathnames.h"
E 10
E 9

D 9
#define LOCKPRE "/usr/spool/uucp/LCK."
E 9
I 9
D 10
/* pick the directory naming scheme you are using */
E 9

D 9
/*
 * This code is taken almost directly from uucp and follows the same
 * conventions.  This is important since uucp and tip should
 * respect each others locks.
 */
E 9
I 9
#define LOCKDIRNAME	"/usr/spool/uucp/LCK..%s"	/**/
/* #define LOCKDIRNAME	"/usr/spool/uucp/LCK/LCK..%s"	/**/
E 9

E 10
D 9
	/*  ulockf 3.2  10/26/79  11:40:29  */
/* #include "uucp.h" */
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
D 6

I 5
static char *sccsid = "%W% %G%";
E 6

E 5
/*******
 *	ulockf(file, atime)
 *	char *file;
 *	time_t atime;
 *
 *	ulockf  -  this routine will create a lock file (file).
 *	If one already exists, the create time is checked for
 *	older than the age time (atime).
 *	If it is older, an attempt will be made to unlink it
 *	and create a new one.
 *
 *	return codes:  0  |  FAIL
E 9
I 9
/* 
 * uucp style locking routines
 * return: 0 - success
 * 	  -1 - failure
E 9
 */

D 9
static
ulockf(file, atime)
D 2
char *file;
time_t atime;
E 2
I 2
	char *file;
	time_t atime;
E 9
I 9
uu_lock(ttyname)
	char *ttyname;
E 9
E 2
{
D 9
	struct stat stbuf;
	time_t ptime;
	int ret;
	static int pid = -1;
D 4
	static char tempfile[NAMESIZE];
E 4
I 4
D 5
	static char tempfile[30];
E 5
I 5
	static char tempfile[NAMESIZE];
E 9
I 9
	extern int errno;
	int fd, pid;
D 10
	char tbuf[sizeof(LOCKDIRNAME) + MAXNAMLEN];
E 10
I 10
	char tbuf[sizeof(_PATH_LOCKDIRNAME) + MAXNAMLEN];
E 10
	off_t lseek();
E 9
E 5
E 4

D 9
	if (pid < 0) {
		pid = getpid();
		sprintf(tempfile, "/usr/spool/uucp/LTMP.%d", pid);
	}
	if (onelock(pid, tempfile, file) == -1) {
		/* lock file exists */
		/* get status to check age of the lock file */
		ret = stat(file, &stbuf);
		if (ret != -1) {
			time(&ptime);
			if ((ptime - stbuf.st_ctime) < atime) {
				/* file not old enough to delete */
D 3
				return(FAIL);
E 3
I 3
				return (FAIL);
E 3
			}
E 9
I 9
D 10
	(void)sprintf(tbuf, LOCKDIRNAME, ttyname);
E 10
I 10
	(void)sprintf(tbuf, _PATH_LOCKDIRNAME, ttyname);
E 10
	fd = open(tbuf, O_RDWR|O_CREAT|O_EXCL, 0660);
	if (fd < 0) {
		/*
		 * file is already locked
		 * check to see if the process holding the lock still exists
		 */
		fd = open(tbuf, O_RDWR, 0);
		if (fd < 0) {
			perror("lock open");
			return(-1);
E 9
		}
D 9
		ret = unlink(file);
		ret = onelock(pid, tempfile, file);
		if (ret != 0)
D 3
			return(FAIL);
E 3
I 3
			return (FAIL);
E 3
	}
	stlock(file);
D 3
	return(0);
E 3
I 3
	return (0);
E 3
}
E 9
I 9
		if (read(fd, &pid, sizeof(pid)) != sizeof(pid)) {
			(void)close(fd);
			perror("lock read");
			return(-1);
		}
E 9

D 9
#define MAXLOCKS 10	/* maximum number of lock files */
char *Lockfile[MAXLOCKS];
int Nlocks = 0;

/***
 *	stlock(name)	put name in list of lock files
 *	char *name;
 *
 *	return codes:  none
 */

static
stlock(name)
D 2
char *name;
E 2
I 2
	char *name;
E 2
{
	char *p;
	extern char *calloc();
	int i;

	for (i = 0; i < Nlocks; i++) {
		if (Lockfile[i] == NULL)
			break;
	}
	ASSERT(i < MAXLOCKS, "TOO MANY LOCKS %d", i);
	if (i >= Nlocks)
		i = Nlocks++;
	p = calloc(strlen(name) + 1, sizeof (char));
	ASSERT(p != NULL, "CAN NOT ALLOCATE FOR %s", name);
	strcpy(p, name);
	Lockfile[i] = p;
	return;
}

/***
 *	rmlock(name)	remove all lock files in list
 *	char *name;	or name
 *
 *	return codes: none
 */

static
rmlock(name)
D 2
char *name;
E 2
I 2
	char *name;
E 2
{
	int i;

	for (i = 0; i < Nlocks; i++) {
		if (Lockfile[i] == NULL)
			continue;
D 3
		if (name == NULL
		|| strcmp(name, Lockfile[i]) == SAME) {
E 3
I 3
		if (name == NULL || strcmp(name, Lockfile[i]) == SAME) {
E 3
			unlink(Lockfile[i]);
			free(Lockfile[i]);
			Lockfile[i] = NULL;
E 9
I 9
		if (kill(pid, 0) == 0 || errno != ESRCH) {
			(void)close(fd);	/* process is still running */
			return(-1);
E 9
		}
I 9
		/*
		 * The process that locked the file isn't running, so
		 * we'll lock it ourselves
		 */
		if (lseek(fd, 0L, L_SET) < 0) {
			(void)close(fd);
			perror("lock lseek");
			return(-1);
		}
		/* fall out and finish the locking process */
E 9
	}
D 3
	return;
E 3
D 9
}

/*
 * this stuff from pjw 
 *  /usr/pjw/bin/recover - check pids to remove unnecessary locks
 *
 *	isalock(name) returns 0 if the name is a lock
 *
 *	onelock(pid,tempfile,name) makes lock a name
 *	on behalf of pid.  Tempfile must be in the same
 *	file system as name.
 *
 *	lock(pid,tempfile,names) either locks all the
 *	names or none of them
 */
static
isalock(name)
D 2
char *name;
E 2
I 2
	char *name;
E 2
{
	struct stat xstat;

D 3
	if(stat(name,&xstat)<0)
		return(0);
	if(xstat.st_size!=sizeof(int))
		return(0);
	return(1);
E 3
I 3
	if (stat(name, &xstat) < 0)
		return (0);
	if (xstat.st_size != sizeof(int))
		return (0);
	return (1);
E 3
}

static
D 3
onelock(pid,tempfile,name)
D 2
char *tempfile,*name;
E 2
I 2
	char *tempfile,*name;
E 3
I 3
onelock(pid, tempfile, name)
	char *tempfile, *name;
E 3
E 2
{
	int fd;

D 3
	fd=creat(tempfile,0444);
	if(fd<0)
		return(-1);
	write(fd,(char *) &pid,sizeof(int));
E 3
I 3
	fd = creat(tempfile, 0444);
	if (fd < 0)
		return (-1);
	write(fd,(char *)&pid, sizeof(int));
E 3
	close(fd);
D 3
	if(link(tempfile,name)<0) {
E 3
I 3
	if (link(tempfile, name) < 0) {
E 3
		unlink(tempfile);
D 3
		return(-1);
E 3
I 3
		return (-1);
E 9
I 9
	pid = getpid();
	if (write(fd, (char *)&pid, sizeof(pid)) != sizeof(pid)) {
		(void)close(fd);
		(void)unlink(tbuf);
		perror("lock write");
		return(-1);
E 9
E 3
	}
D 9
	unlink(tempfile);
D 3
	return(0);
E 3
I 3
	return (0);
E 9
I 9
	(void)close(fd);
	return(0);
E 9
E 3
}

D 9
/***
 *	delock(s)	remove a lock file
 *	char *s;
 *
 *	return codes:  0  |  FAIL
 */

delock(s)
D 2
char *s;
E 2
I 2
	char *s;
E 9
I 9
uu_unlock(ttyname)
	char *ttyname;
E 9
E 2
{
D 9
	char ln[30];
E 9
I 9
D 10
	char tbuf[sizeof(LOCKDIRNAME) + MAXNAMLEN];
E 10
I 10
	char tbuf[sizeof(_PATH_LOCKDIRNAME) + MAXNAMLEN];
E 10
E 9

D 9
	sprintf(ln, "%s.%s", LOCKPRE, s);
	rmlock(ln);
}

/***
 *	mlock(sys)	create system lock
 *	char *sys;
 *
 *	return codes:  0  |  FAIL
 */

mlock(sys)
D 2
char *sys;
E 2
I 2
	char *sys;
E 2
{
	char lname[30];
	sprintf(lname, "%s.%s", LOCKPRE, sys);
D 3
	return(ulockf(lname, (time_t) SLCKTIME ) < 0 ? FAIL : 0);
E 3
I 3
	return (ulockf(lname, (time_t) SLCKTIME ) < 0 ? FAIL : 0);
E 9
I 9
D 10
	(void)sprintf(tbuf, LOCKDIRNAME, ttyname);
E 10
I 10
	(void)sprintf(tbuf, _PATH_LOCKDIRNAME, ttyname);
E 10
	return(unlink(tbuf));
E 9
E 3
}
E 1
