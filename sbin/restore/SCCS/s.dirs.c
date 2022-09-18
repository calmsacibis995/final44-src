h10028
s 00005/00005/00722
d D 8.7 95/05/01 23:23:19 mckusick 56 55
c new dinode organization and naming
e
s 00003/00003/00724
d D 8.6 95/04/28 10:57:36 bostic 55 54
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00004/00006/00723
d D 8.5 94/08/31 21:12:38 mckusick 54 53
c correct termination for readdir
e
s 00006/00003/00723
d D 8.4 94/08/23 10:36:27 mckusick 53 52
c set file flags on directories
e
s 00013/00008/00713
d D 8.3 94/06/20 13:40:17 mckusick 52 50
c byte swapping code for LITTLE_ENDIAN on old format tapes (from mycroft)
e
s 00015/00001/00720
d R 8.3 94/06/20 13:34:53 mckusick 51 50
c byte swapping code for LITTLE_ENDIAN on old format tapes (from mycroft)
e
s 00005/00000/00716
d D 8.2 94/01/21 17:05:45 bostic 50 49
c add USL's copyright notice
e
s 00002/00002/00714
d D 8.1 93/06/05 11:11:40 bostic 49 48
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00009/00706
d D 5.27 93/02/11 08:28:36 bostic 48 47
c gcc -Wall from Craig Leres (no substantive changes)
e
s 00010/00010/00705
d D 5.26 93/02/10 14:47:49 bostic 47 46
c make declarations work with new prototypes in globh
e
s 00027/00009/00688
d D 5.25 92/12/02 01:07:26 mckusick 46 45
c pathsearch and searchdir now return a dp instead of an ino_t;
c rst_opendir now really gets a new descriptor which is deleted by 
c the new function rst_closedir
e
s 00072/00047/00625
d D 5.24 92/10/16 16:21:16 bostic 45 44
c ANSI C, convert options handling to getopt(3)
e
s 00022/00034/00650
d D 5.23 92/10/06 00:57:05 mckusick 44 43
c eliminate last vestiges of AT&T code
e
s 00003/00002/00681
d D 5.22 92/08/09 14:02:06 mckusick 43 42
c allow setdirmodes to force setting of modes when used explicitly
e
s 00016/00009/00667
d D 5.21 92/06/30 18:27:55 mckusick 42 41
c add provision for new and old inode formats
e
s 00004/00002/00672
d D 5.20 92/06/20 14:06:35 mckusick 41 40
c timeval => timespec
e
s 00002/00004/00672
d D 5.19 92/05/20 15:19:21 mckusick 40 39
c dinode's now have timeval's instead of time_t's
e
s 00001/00001/00675
d D 5.18 91/11/11 11:39:08 bostic 39 38
c break UFS up into FFS/UFS/LFS/MFS
e
s 00024/00013/00652
d D 5.17 91/07/29 17:00:48 mckusick 38 37
c minor cleanups to help portability
e
s 00010/00010/00655
d D 5.16 91/07/29 16:17:31 mckusick 37 35
c use RST_DIR in place of DIR (to avoid conflicts with directory
c access routine library)
e
s 00009/00009/00656
d R 5.16 91/07/29 15:59:39 mckusick 36 35
c use RST_DIR in place of DIR (to avoid conflicts with dirirectory
c access routine library
e
s 00001/00003/00664
d D 5.15 91/02/26 21:42:36 torek 35 34
c declare rst_telldir correctly at top and not again everywhere
e
s 00002/00001/00665
d D 5.14 91/02/22 19:08:12 mckusick 34 33
c gdb does not allow writing of constant strings
e
s 00007/00002/00659
d D 5.13 91/02/22 18:30:15 mckusick 33 32
c must use maximum directory blocksize across all architectures;
c Be more paranoid about directory structure and print warnings when found
e
s 00008/00006/00653
d D 5.12 90/06/04 09:44:08 mckusick 32 31
c do not try to use null pointer after panic
e
s 00001/00011/00658
d D 5.11 90/06/01 16:20:36 bostic 31 30
c new copyright notice
e
s 00015/00000/00654
d D 5.10 90/02/15 13:15:26 mckusick 30 29
c move in info from restore.h that is specific to this file
e
s 00041/00006/00613
d D 5.9 90/02/13 18:40:41 mckusick 29 28
c include explicit telldir and opendir instead of expecting them from libc
e
s 00006/00004/00613
d D 5.8 89/10/31 23:15:55 mckusick 28 27
c convert utime to be utimes
e
s 00004/00003/00613
d D 5.7 89/05/11 13:55:31 bostic 27 26
c file reorg, pathnames.h, paths.h
e
s 00015/00004/00601
d D 5.6 88/10/24 16:38:15 bostic 26 25
c Berkeley copyright notice
e
s 00001/00001/00604
d D 5.5 88/05/13 14:47:51 mckusick 25 24
c add Nflag to request not to do any writes
e
s 00008/00014/00597
d D 5.4 86/04/23 12:04:39 mckusick 24 23
c do not dump core when missing `.' or `..' entries in directories
e
s 00004/00000/00607
d D 5.3 86/03/26 23:13:30 sklower 23 22
c restore sun and cci tapes
e
s 00001/00001/00606
d D 5.2 85/06/18 21:11:12 mckusick 22 21
c dumprestor.h moves to /usr/include/protocols
e
s 00008/00004/00599
d D 5.1 85/05/28 15:10:20 dist 21 20
c Add copyright
e
s 00004/00000/00599
d D 3.20 85/02/18 18:29:29 mckusick 20 19
c do not set owner and times on directories that already exist ('i' and 'x' only)
e
s 00001/00002/00598
d D 3.19 85/02/13 14:14:26 mckusick 19 18
c allow for no files on dump tape (from sun!shannon)
e
s 00018/00183/00582
d D 3.18 85/01/18 22:38:14 mckusick 18 17
c reorganize to split out interactive shell
e
s 00006/00003/00759
d D 3.17 83/12/30 00:38:07 mckusick 17 16
c missing ``modefile'' is a non-fatal error
e
s 00002/00002/00760
d D 3.16 83/08/11 23:04:32 sam 16 15
c standardize sccs keyword lines
e
s 00007/00003/00755
d D 3.15 83/08/11 16:46:36 mckusick 15 14
c in 'x' or 'i' mode, ask if mode of "." should be changed
e
s 00008/00001/00750
d D 3.14 83/07/08 16:49:09 mckusick 14 13
c guard all dynamic allocations
e
s 00001/00001/00750
d D 3.13 83/07/01 03:10:03 sam 13 12
c include fixes
e
s 00001/00001/00750
d D 3.12 83/06/02 17:06:20 sam 12 11
c file.h updated
e
s 00021/00017/00730
d D 3.11 83/05/19 01:22:52 mckusick 11 10
c use perror everywhere; lint
e
s 00042/00013/00705
d D 3.10 83/05/14 21:53:40 mckusick 10 9
c make readdir more robust; allow printing of dir entries not on tape
e
s 00001/00001/00717
d D 3.9 83/05/03 23:29:18 mckusick 9 8
c do not panic if directory is not marked NEW when setting time and ownership
e
s 00225/00020/00493
d D 3.8 83/04/19 02:11:46 mckusick 8 7
c add and debug interactive extraction mode
e
s 00004/00017/00509
d D 3.7 83/03/27 18:33:23 mckusick 7 6
c pass pruning argument back to treescan
e
s 00014/00040/00512
d D 3.6 83/03/27 12:54:01 mckusick 6 5
c lint; delete opendir (use standard version in library)
e
s 00005/00005/00547
d D 3.5 83/03/23 08:56:41 mckusick 5 4
c use MAXPATHLEN instead of BUFSIZ where appropriate
e
s 00006/00004/00546
d D 3.4 83/03/06 17:43:47 mckusick 4 3
c lint
e
s 00035/00011/00515
d D 3.3 83/02/28 00:37:44 mckusick 3 2
c get "h" and "m" flags working
e
s 00019/00013/00507
d D 3.2 83/02/27 14:39:22 mckusick 2 1
c get "x" command working
e
s 00520/00000/00000
d D 3.1 83/02/18 00:41:37 mckusick 1 0
c date and time created 83/02/18 00:41:37 by mckusick
e
u
U
t
T
I 1
D 16
/* Copyright (c) 1983 Regents of the University of California */

E 16
D 21
#ifndef lint
static char sccsid[] = "%W%	(Berkeley)	%E%";
#endif
E 21
I 21
/*
D 26
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 26
I 26
D 49
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 49
I 49
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
I 50
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 50
E 49
 *
D 31
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
E 31
I 31
 * %sccs.include.redist.c%
E 31
E 26
 */
E 21
I 16

D 21
/* Copyright (c) 1983 Regents of the University of California */
E 21
I 21
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 26
#endif not lint
E 26
I 26
#endif /* not lint */
E 26
E 21
E 16

D 45
#include "restore.h"
I 44
#include <string.h>
E 44
D 22
#include <dumprestor.h>
E 22
I 22
#include <protocols/dumprestore.h>
E 45
I 45
#include <sys/param.h>
E 45
E 22
D 2
#include <file.h>
E 2
I 2
#include <sys/file.h>
I 45
#include <sys/stat.h>
#include <sys/time.h>

D 56
#include <ufs/ffs/fs.h>
E 56
#include <ufs/ufs/dinode.h>
E 45
I 30
D 39
#include <ufs/dir.h>
E 39
I 39
#include <ufs/ufs/dir.h>
I 56
#include <ufs/ffs/fs.h>
E 56
I 45
#include <protocols/dumprestore.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

I 52
#include <machine/endian.h>

E 52
E 45
E 39
E 30
I 27
#include "pathnames.h"
I 45
#include "restore.h"
#include "extern.h"
E 45
E 27
E 2
D 13
#include <dir.h>
E 13
I 13
D 18
#include <sys/dir.h>
E 18
E 13

I 8
/*
 * Symbol table of directories read from tape.
 */
E 8
#define HASHSIZE	1000
D 8

E 8
#define INOHASH(val) (val % HASHSIZE)
struct inotab {
D 38
	struct inotab *t_next;
E 38
I 38
	struct	inotab *t_next;
E 38
	ino_t	t_ino;
D 38
	daddr_t	t_seekpt;
	long t_size;
E 38
I 38
	long	t_seekpt;
	long	t_size;
E 38
D 2
} *inotab[HASHSIZE];
struct inotab *inotablookup();
E 2
I 2
};
static struct inotab *inotab[HASHSIZE];
D 45
extern struct inotab *inotablookup();
I 3
extern struct inotab *allocinotab();
E 45
E 3
E 2

I 8
/*
 * Information retained about directories.
 */
E 8
struct modeinfo {
	ino_t ino;
D 28
	time_t timep[2];
E 28
I 28
	struct timeval timep[2];
E 28
D 53
	short mode;
	short uid;
	short gid;
E 53
I 53
	mode_t mode;
	uid_t uid;
	gid_t gid;
	int flags;
E 53
};
I 30

/*
 * Definitions for library routines operating on directories.
 */
D 33
#define DIRBLKSIZ DEV_BSIZE
E 33
I 33
#undef DIRBLKSIZ
#define DIRBLKSIZ 1024
E 33
D 37
struct dirdesc {
E 37
I 37
struct rstdirdesc {
E 37
	int	dd_fd;
	long	dd_loc;
	long	dd_size;
	char	dd_buf[DIRBLKSIZ];
};
D 37
extern DIR *opendirfile();
E 37
I 37
D 45
extern RST_DIR *opendirfile();
E 37
D 35
extern long rst_telldir();
E 35
I 35
D 38
extern off_t rst_telldir();
E 38
I 38
extern long rst_telldir();
E 38
E 35
extern void rst_seekdir();
E 45
E 30

I 8
/*
 * Global variables for this file.
 */
E 8
D 2
daddr_t	seekpt;
FILE	*df, *mf;
DIR	*dirp;
char	dirfile[] = "/tmp/rstaXXXXXX";
extern	ino_t search();
E 2
I 2
D 38
static daddr_t	seekpt;
E 38
I 38
static long	seekpt;
E 38
static FILE	*df, *mf;
D 37
static DIR	*dirp;
E 37
I 37
static RST_DIR	*dirp;
E 37
D 8
static char	dirfile[] = "/tmp/rstaXXXXXX";
E 8
I 8
static char	dirfile[32] = "#";	/* No file */
static char	modefile[32] = "#";	/* No file */
I 34
static char	dot[2] = ".";		/* So it can be modified */
E 34
E 8
D 44
extern ino_t	search();
E 44
I 44
D 45
extern ino_t	searchdir();
E 44
I 11
struct direct 	*rst_readdir();
E 45
D 38
extern void 	rst_seekdir();
E 38
E 11
E 2

I 8
/*
 * Format of old style directories.
 */
E 8
#define ODIRSIZ 14
struct odirect {
	u_short	d_ino;
	char	d_name[ODIRSIZ];
};

I 45
static struct inotab	*allocinotab __P((ino_t, struct dinode *, long));
static void		 dcvt __P((struct odirect *, struct direct *));
static void		 flushent __P((void));
static struct inotab	*inotablookup __P((ino_t));
D 47
static RST_DIR		*opendirfile __P((char *));
E 47
I 47
static RST_DIR		*opendirfile __P((const char *));
E 47
static void		 putdir __P((char *, long));
static void		 putent __P((struct direct *));
static void		 rst_seekdir __P((RST_DIR *, long, long));
static long		 rst_telldir __P((RST_DIR *));
D 46
static ino_t		 searchdir __P((ino_t, char *));
E 46
I 46
static struct direct	*searchdir __P((ino_t, char *));
E 46

E 45
/*
I 8
D 18
 * Structure and routines associated with listing directories.
 */
struct afile {
	ino_t	fnum;		/* inode number of file */
	char	*fname;		/* file name */
	short	fflags;		/* extraction flags, if any */
	char	ftype;		/* file type, e.g. LEAF or NODE */
};
extern int fcmp();
extern char *fmtentry();

/*
E 18
E 8
 *	Extract directory contents, building up a directory structure
 *	on disk for extraction by name.
D 8
 *	If modefile is requested, save mode, owner, and times for all
E 8
I 8
 *	If genmode is requested, save mode, owner, and times for all
E 8
 *	directories on the tape.
 */
I 45
void
E 45
D 8
extractdirs(modefile)
	char *modefile;
E 8
I 8
extractdirs(genmode)
	int genmode;
E 8
{
	register int i;
	register struct dinode *ip;
I 3
	struct inotab *itp;
E 3
	struct direct nulldir;
D 44
	int putdir(), null();
E 44
I 44
D 45
	int putdir(), xtrnull();
E 45
E 44

	vprintf(stdout, "Extract directories from tape\n");
D 4
	mktemp(dirfile);
E 4
I 4
D 8
	(void) mktemp(dirfile);
E 8
I 8
D 27
	(void) sprintf(dirfile, "/tmp/rstdir%d", dumpdate);
E 27
I 27
	(void) sprintf(dirfile, "%s/rstdir%d", _PATH_TMP, dumpdate);
E 27
E 8
E 4
	df = fopen(dirfile, "w");
D 48
	if (df == 0) {
E 48
I 48
	if (df == NULL) {
E 48
		fprintf(stderr,
D 17
		    "restor: %s - cannot create directory temporary\n",
E 17
I 17
		    "restore: %s - cannot create directory temporary\n",
E 17
		    dirfile);
D 45
		perror("fopen");
E 45
I 45
		fprintf(stderr, "fopen: %s\n", strerror(errno));
E 45
		done(1);
	}
D 8
	if (modefile != NULL) {
E 8
I 8
	if (genmode != 0) {
D 27
		(void) sprintf(modefile, "/tmp/rstmode%d", dumpdate);
E 27
I 27
		(void) sprintf(modefile, "%s/rstmode%d", _PATH_TMP, dumpdate);
E 27
E 8
		mf = fopen(modefile, "w");
D 2
		if (df == 0) {
E 2
I 2
D 48
		if (mf == 0) {
E 48
I 48
		if (mf == NULL) {
E 48
E 2
			fprintf(stderr,
D 17
			    "restor: %s - cannot create modefile \n",
E 17
I 17
			    "restore: %s - cannot create modefile \n",
E 17
			    modefile);
D 45
			perror("fopen");
E 45
I 45
			fprintf(stderr, "fopen: %s\n", strerror(errno));
E 45
			done(1);
		}
	}
D 3
	nulldir.d_ino = 1;
E 3
I 3
	nulldir.d_ino = 0;
I 42
	nulldir.d_type = DT_DIR;
E 42
E 3
	nulldir.d_namlen = 1;
D 8
	strncpy(nulldir.d_name, "/", nulldir.d_namlen);
E 8
I 8
D 10
	(void) strncpy(nulldir.d_name, "/", (int)nulldir.d_namlen);
E 10
I 10
	(void) strcpy(nulldir.d_name, "/");
E 10
E 8
D 42
	nulldir.d_reclen = DIRSIZ(&nulldir);
E 42
I 42
	nulldir.d_reclen = DIRSIZ(0, &nulldir);
E 42
	for (;;) {
		curfile.name = "<directory file - name unknown>";
		curfile.action = USING;
		ip = curfile.dip;
D 19
		i = ip->di_mode & IFMT;
		if (i != IFDIR) {
E 19
I 19
		if (ip == NULL || (ip->di_mode & IFMT) != IFDIR) {
E 19
D 6
			fclose(df);
E 6
I 6
			(void) fclose(df);
E 6
D 29
			dirp = opendir(dirfile);
E 29
I 29
			dirp = opendirfile(dirfile);
E 29
			if (dirp == NULL)
D 29
				perror("opendir");
E 29
I 29
D 45
				perror("opendirfile");
E 45
I 45
				fprintf(stderr, "opendirfile: %s\n",
				    strerror(errno));
E 45
E 29
			if (mf != NULL)
D 6
				fclose(mf);
E 6
I 6
				(void) fclose(mf);
E 6
I 4
D 8
			if ((i = psearch(".")) == 0 || BIT(i, dumpmap) == 0)
E 8
I 8
D 34
			i = dirlookup(".");
E 34
I 34
			i = dirlookup(dot);
E 34
			if (i == 0)
E 8
				panic("Root directory is not on tape\n");
E 4
			return;
		}
D 3
		allocinotab(curfile.ino, ip, seekpt);
E 3
I 3
		itp = allocinotab(curfile.ino, ip, seekpt);
E 3
D 44
		getfile(putdir, null);
E 44
I 44
		getfile(putdir, xtrnull);
E 44
		putent(&nulldir);
		flushent();
I 3
		itp->t_size = seekpt - itp->t_seekpt;
E 3
	}
}

/*
I 3
 * skip over all the directories on the tape
 */
I 45
void
E 45
skipdirs()
{

	while ((curfile.dip->di_mode & IFMT) == IFDIR) {
		skipfile();
	}
}

/*
E 3
 *	Recursively find names and inumbers of all files in subtree 
 *	pname and pass them off to be processed.
 */
I 45
void
E 45
treescan(pname, ino, todo)
	char *pname;
	ino_t ino;
D 7
	void (*todo)();
E 7
I 7
D 45
	long (*todo)();
E 45
I 45
	long (*todo) __P((char *, ino_t, int));
E 45
E 7
{
	register struct inotab *itp;
I 10
	register struct direct *dp;
D 45
	register struct entry *np;
E 45
E 10
	int namelen;
D 38
	daddr_t bpt;
E 38
I 38
	long bpt;
E 38
I 29
D 35
	off_t rst_telldir();
E 35
E 29
D 10
	register struct direct *dp;
E 10
D 5
	char locname[BUFSIZ + 1];
E 5
I 5
	char locname[MAXPATHLEN + 1];
E 5

	itp = inotablookup(ino);
	if (itp == NULL) {
		/*
		 * Pname is name of a simple file or an unchanged directory.
		 */
D 7
		(*todo)(pname, ino, LEAF);
E 7
I 7
		(void) (*todo)(pname, ino, LEAF);
E 7
		return;
	}
	/*
	 * Pname is a dumped directory name.
	 */
D 7
	(*todo)(pname, ino, NODE);
E 7
I 7
	if ((*todo)(pname, ino, NODE) == FAIL)
		return;
E 7
	/*
	 * begin search through the directory
	 * skipping over "." and ".."
	 */
D 5
	strncpy(locname, pname, BUFSIZ);
	strncat(locname, "/", BUFSIZ);
E 5
I 5
D 8
	strncpy(locname, pname, MAXPATHLEN);
	strncat(locname, "/", MAXPATHLEN);
E 8
I 8
	(void) strncpy(locname, pname, MAXPATHLEN);
	(void) strncat(locname, "/", MAXPATHLEN);
E 8
E 5
	namelen = strlen(locname);
D 11
	seekdir(dirp, itp->t_seekpt, itp->t_seekpt);
	dp = readdir(dirp); /* "." */
E 11
I 11
	rst_seekdir(dirp, itp->t_seekpt, itp->t_seekpt);
	dp = rst_readdir(dirp); /* "." */
E 11
D 10
	dp = readdir(dirp); /* ".." */
	dp = readdir(dirp); /* first real entry */
E 10
I 10
D 24
	if (dp != NULL && strcmp(dp->d_name, ".") == 0) {
E 24
I 24
	if (dp != NULL && strcmp(dp->d_name, ".") == 0)
E 24
D 11
		dp = readdir(dirp); /* ".." */
E 11
I 11
		dp = rst_readdir(dirp); /* ".." */
E 11
D 24
	} else {
		np = lookupino(ino);
		if (np == NULL)
			panic("corrupted symbol table\n");
		fprintf(stderr, ". missing from directory %s\n", myname(np));
	}
	if (dp != NULL && strcmp(dp->d_name, "..") == 0) {
E 24
I 24
	else
		fprintf(stderr, "Warning: `.' missing from directory %s\n",
			pname);
	if (dp != NULL && strcmp(dp->d_name, "..") == 0)
E 24
D 11
		dp = readdir(dirp); /* first real entry */
E 11
I 11
		dp = rst_readdir(dirp); /* first real entry */
E 11
D 24
	} else {
		np = lookupino(ino);
		if (np == NULL)
			panic("corrupted symbol table\n");
		fprintf(stderr, ".. missing from directory %s\n", myname(np));
	}
E 24
I 24
	else
		fprintf(stderr, "Warning: `..' missing from directory %s\n",
			pname);
E 24
E 10
D 29
	bpt = telldir(dirp);
E 29
I 29
	bpt = rst_telldir(dirp);
E 29
	/*
D 10
	 * "/" signals end of directory
E 10
I 10
	 * a zero inode signals end of directory
E 10
	 */
D 10
	while (dp != NULL && !(dp->d_namlen == 1 && dp->d_name[0] == '/')) {
E 10
I 10
D 54
	while (dp != NULL && dp->d_ino != 0) {
E 54
I 54
	while (dp != NULL) {
E 54
E 10
		locname[namelen] = '\0';
D 5
		if (namelen + dp->d_namlen >= BUFSIZ) {
E 5
I 5
		if (namelen + dp->d_namlen >= MAXPATHLEN) {
E 5
			fprintf(stderr, "%s%s: name exceeds %d char\n",
D 5
				locname, dp->d_name, BUFSIZ);
E 5
I 5
				locname, dp->d_name, MAXPATHLEN);
E 5
		} else {
D 8
			strncat(locname, dp->d_name, dp->d_namlen);
E 8
I 8
			(void) strncat(locname, dp->d_name, (int)dp->d_namlen);
E 8
			treescan(locname, dp->d_ino, todo);
D 11
			seekdir(dirp, bpt, itp->t_seekpt);
E 11
I 11
			rst_seekdir(dirp, bpt, itp->t_seekpt);
E 11
		}
D 11
		dp = readdir(dirp);
E 11
I 11
		dp = rst_readdir(dirp);
E 11
D 29
		bpt = telldir(dirp);
E 29
I 29
		bpt = rst_telldir(dirp);
E 29
	}
D 54
	if (dp == NULL)
		fprintf(stderr, "corrupted directory: %s.\n", locname);
E 54
}

/*
D 44
 * Search the directory tree rooted at inode ROOTINO
 * for the path pointed at by n
E 44
I 44
 * Lookup a pathname which is always assumed to start from the ROOTINO.
E 44
 */
D 46
ino_t
E 46
I 46
struct direct *
E 46
D 44
psearch(n)
	char	*n;
E 44
I 44
pathsearch(pathname)
D 47
	char *pathname;
E 47
I 47
	const char *pathname;
E 47
E 44
{
D 44
	register char *cp, *cp1;
E 44
	ino_t ino;
I 46
	struct direct *dp;
E 46
D 44
	char c;
E 44
I 44
D 47
	char *name, buffer[MAXPATHLEN];
E 47
I 47
	char *path, *name, buffer[MAXPATHLEN];
E 47
E 44

I 44
	strcpy(buffer, pathname);
D 47
	pathname = buffer;
E 47
I 47
	path = buffer;
E 47
E 44
	ino = ROOTINO;
D 44
	if (*(cp = n) == '/')
		cp++;
next:
	cp1 = cp + 1;
	while (*cp1 != '/' && *cp1)
		cp1++;
	c = *cp1;
	*cp1 = 0;
	ino = search(ino, cp);
	if (ino == 0) {
		*cp1 = c;
		return(0);
	}
	*cp1 = c;
	if (c == '/') {
		cp = cp1+1;
		goto next;
	}
	return(ino);
E 44
I 44
D 47
	while (*pathname == '/')
		pathname++;
D 46
	while ((name = strsep(&pathname, "/")) != NULL)
		if ((ino = searchdir(ino, name)) == 0)
			return ((ino_t)0);
	return (ino);
E 46
I 46
	while ((name = strsep(&pathname, "/")) != NULL && *name != NULL) {
E 47
I 47
	while (*path == '/')
		path++;
I 48
	dp = NULL;
E 48
	while ((name = strsep(&path, "/")) != NULL && *name != NULL) {
E 47
D 48
		if ((dp = searchdir(ino, name)) == 0)
E 48
I 48
		if ((dp = searchdir(ino, name)) == NULL)
E 48
			return (NULL);
		ino = dp->d_ino;
	}
	return (dp);
E 46
E 44
}

/*
D 44
 * search the directory inode ino
 * looking for entry cp
E 44
I 44
 * Lookup the requested name in directory inum.
 * Return its inode number if found, zero if it does not exist.
E 44
 */
D 45
ino_t
E 45
I 45
D 46
static ino_t
E 46
I 46
static struct direct *
E 46
E 45
D 44
search(inum, cp)
E 44
I 44
searchdir(inum, name)
E 44
	ino_t	inum;
D 44
	char	*cp;
E 44
I 44
	char	*name;
E 44
{
	register struct direct *dp;
	register struct inotab *itp;
	int len;

	itp = inotablookup(inum);
	if (itp == NULL)
D 48
		return(0);
E 48
I 48
		return (NULL);
E 48
D 11
	seekdir(dirp, itp->t_seekpt, itp->t_seekpt);
E 11
I 11
	rst_seekdir(dirp, itp->t_seekpt, itp->t_seekpt);
E 11
D 44
	len = strlen(cp);
E 44
I 44
	len = strlen(name);
E 44
	do {
D 11
		dp = readdir(dirp);
E 11
I 11
		dp = rst_readdir(dirp);
E 11
D 10
		if (dp->d_namlen == 1 && dp->d_name[0] == '/')
			return(0);
E 10
I 10
D 54
		if (dp == NULL || dp->d_ino == 0)
E 54
I 54
		if (dp == NULL)
E 54
D 46
			return (0);
E 46
I 46
			return (NULL);
E 46
E 10
D 8
	} while (dp->d_namlen != len || strncmp(dp->d_name, cp, len));
E 8
I 8
D 44
	} while (dp->d_namlen != len || strncmp(dp->d_name, cp, len) != 0);
E 44
I 44
	} while (dp->d_namlen != len || strncmp(dp->d_name, name, len) != 0);
E 44
E 8
D 46
	return(dp->d_ino);
E 46
I 46
	return (dp);
E 46
}

/*
 * Put the directory entries in the directory file
 */
I 45
static void
E 45
putdir(buf, size)
	char *buf;
D 45
	int size;
E 45
I 45
	long size;
E 45
{
	struct direct cvtbuf;
	register struct odirect *odp;
	struct odirect *eodp;
	register struct direct *dp;
	long loc, i;
I 23
D 42
	extern int Bcvt;
E 42
E 23

	if (cvtflag) {
		eodp = (struct odirect *)&buf[size];
		for (odp = (struct odirect *)buf; odp < eodp; odp++)
			if (odp->d_ino != 0) {
				dcvt(odp, &cvtbuf);
				putent(&cvtbuf);
			}
	} else {
		for (loc = 0; loc < size; ) {
			dp = (struct direct *)(buf + loc);
I 23
D 42
			if (Bcvt) {
				swabst("l2s", (char *) dp);
E 42
I 42
D 52
			if (oldinofmt) {
				if (Bcvt) {
D 45
					swabst("l2s", (char *) dp);
E 45
I 45
					swabst((u_char *)"l2s", (u_char *) dp);
E 45
				}
			} else {
				if (Bcvt) {
D 45
					swabst("ls", (char *) dp);
E 45
I 45
					swabst((u_char *)"ls", (u_char *) dp);
E 45
				}
E 52
I 52
			if (Bcvt)
				swabst((u_char *)"ls", (u_char *) dp);
			if (oldinofmt && dp->d_ino != 0) {
#				if BYTE_ORDER == BIG_ENDIAN
					if (Bcvt)
						dp->d_namlen = dp->d_type;
#				else
					if (!Bcvt)
						dp->d_namlen = dp->d_type;
#				endif
				dp->d_type = DT_UNKNOWN;
E 52
E 42
			}
E 23
			i = DIRBLKSIZ - (loc & (DIRBLKSIZ - 1));
D 33
			if (dp->d_reclen == 0 || dp->d_reclen > i) {
E 33
I 33
			if ((dp->d_reclen & 0x3) != 0 ||
			    dp->d_reclen > i ||
D 42
			    dp->d_reclen < DIRSIZ(dp) ||
E 42
I 42
			    dp->d_reclen < DIRSIZ(0, dp) ||
E 42
D 38
			    dp->d_namlen > MAXNAMLEN) {
				vprintf(stdout, "Mangled directory\n");
E 38
I 38
			    dp->d_namlen > NAME_MAX) {
				vprintf(stdout, "Mangled directory: ");
				if ((dp->d_reclen & 0x3) != 0)
					vprintf(stdout,
					   "reclen not multiple of 4 ");
D 42
				if (dp->d_reclen < DIRSIZ(dp))
E 42
I 42
				if (dp->d_reclen < DIRSIZ(0, dp))
E 42
					vprintf(stdout,
					   "reclen less than DIRSIZ (%d < %d) ",
D 42
					   dp->d_reclen, DIRSIZ(dp));
E 42
I 42
					   dp->d_reclen, DIRSIZ(0, dp));
E 42
				if (dp->d_namlen > NAME_MAX)
					vprintf(stdout,
					   "reclen name too big (%d > %d) ",
					   dp->d_namlen, NAME_MAX);
				vprintf(stdout, "\n");
E 38
E 33
				loc += i;
				continue;
			}
			loc += dp->d_reclen;
			if (dp->d_ino != 0) {
				putent(dp);
			}
		}
	}
}

/*
 * These variables are "local" to the following two functions.
 */
char dirbuf[DIRBLKSIZ];
long dirloc = 0;
long prev = 0;

/*
 * add a new directory entry to a file.
 */
I 45
static void
E 45
putent(dp)
	struct direct *dp;
{
D 3
	if (dp->d_ino == 0)
		return;
E 3
I 3
D 42
	dp->d_reclen = DIRSIZ(dp);
E 42
I 42
	dp->d_reclen = DIRSIZ(0, dp);
E 42
E 3
	if (dirloc + dp->d_reclen > DIRBLKSIZ) {
		((struct direct *)(dirbuf + prev))->d_reclen =
		    DIRBLKSIZ - prev;
D 6
		fwrite(dirbuf, 1, DIRBLKSIZ, df);
E 6
I 6
		(void) fwrite(dirbuf, 1, DIRBLKSIZ, df);
E 6
		dirloc = 0;
	}
D 55
	bcopy((char *)dp, dirbuf + dirloc, (long)dp->d_reclen);
E 55
I 55
	memmove(dirbuf + dirloc, dp, (long)dp->d_reclen);
E 55
	prev = dirloc;
	dirloc += dp->d_reclen;
}

/*
 * flush out a directory that is finished.
 */
I 45
static void
E 45
flushent()
{
D 45

E 45
	((struct direct *)(dirbuf + prev))->d_reclen = DIRBLKSIZ - prev;
D 6
	fwrite(dirbuf, (int)dirloc, 1, df);
E 6
I 6
	(void) fwrite(dirbuf, (int)dirloc, 1, df);
E 6
	seekpt = ftell(df);
	dirloc = 0;
}

I 45
static void
E 45
dcvt(odp, ndp)
	register struct odirect *odp;
	register struct direct *ndp;
{

D 55
	bzero((char *)ndp, (long)(sizeof *ndp));
E 55
I 55
	memset(ndp, 0, (long)(sizeof *ndp));
E 55
	ndp->d_ino =  odp->d_ino;
I 42
	ndp->d_type = DT_UNKNOWN;
E 42
D 8
	strncpy(ndp->d_name, odp->d_name, ODIRSIZ);
E 8
I 8
	(void) strncpy(ndp->d_name, odp->d_name, ODIRSIZ);
E 8
	ndp->d_namlen = strlen(ndp->d_name);
D 42
	ndp->d_reclen = DIRSIZ(ndp);
E 42
I 42
	ndp->d_reclen = DIRSIZ(0, ndp);
E 42
D 6
	/*
	 * this quickly calculates if this inode is a directory.
	 * Currently not maintained.
	 *
	itp = inotablookup(odp->d_ino);
	if (itp != NIL)
		ndp->d_fmt = IFDIR;
	 */
E 6
}

/*
D 6
 * Open a directory.
 * Modified to allow any random file to be a legal directory.
 */
DIR *
opendir(name)
	char *name;
{
	register DIR *dirp;

D 4
	dirp = (DIR *)malloc((unsigned long)sizeof(DIR));
E 4
I 4
	dirp = (DIR *)malloc((unsigned)sizeof(DIR));
E 4
	dirp->dd_fd = open(name, 0);
	if (dirp->dd_fd == -1) {
		free((char *)dirp);
		return NULL;
	}
	dirp->dd_loc = 0;
	return dirp;
}

/*
E 6
 * Seek to an entry in a directory.
D 11
 * Only values returned by ``telldir'' should be passed to seekdir.
E 11
I 11
D 29
 * Only values returned by ``telldir'' should be passed to rst_seekdir.
E 29
I 29
 * Only values returned by rst_telldir should be passed to rst_seekdir.
E 29
E 11
D 6
 * Modified to have many directories based in one file.
E 6
I 6
 * This routine handles many directories in a single file.
 * It takes the base of the directory in the file, plus
 * the desired seek offset into it.
E 6
 */
D 45
void
E 45
I 45
static void
E 45
D 11
seekdir(dirp, loc, base)
E 11
I 11
rst_seekdir(dirp, loc, base)
E 11
D 37
	register DIR *dirp;
E 37
I 37
	register RST_DIR *dirp;
E 37
D 38
	daddr_t loc, base;
E 38
I 38
	long loc, base;
E 38
{
I 29
D 35
	off_t rst_telldir();
E 35
E 29

D 29
	if (loc == telldir(dirp))
E 29
I 29
	if (loc == rst_telldir(dirp))
E 29
		return;
	loc -= base;
	if (loc < 0)
D 11
		fprintf(stderr, "bad seek pointer to seekdir %d\n", loc);
E 11
I 11
		fprintf(stderr, "bad seek pointer to rst_seekdir %d\n", loc);
E 11
D 45
	(void) lseek(dirp->dd_fd, base + (loc & ~(DIRBLKSIZ - 1)), 0);
E 45
I 45
	(void) lseek(dirp->dd_fd, base + (loc & ~(DIRBLKSIZ - 1)), SEEK_SET);
E 45
	dirp->dd_loc = loc & (DIRBLKSIZ - 1);
	if (dirp->dd_loc != 0)
		dirp->dd_size = read(dirp->dd_fd, dirp->dd_buf, DIRBLKSIZ);
}

/*
 * get next entry in a directory.
 */
struct direct *
D 11
readdir(dirp)
E 11
I 11
rst_readdir(dirp)
E 11
D 37
	register DIR *dirp;
E 37
I 37
	register RST_DIR *dirp;
E 37
{
	register struct direct *dp;

	for (;;) {
		if (dirp->dd_loc == 0) {
			dirp->dd_size = read(dirp->dd_fd, dirp->dd_buf, 
			    DIRBLKSIZ);
D 10
			if (dirp->dd_size <= 0)
E 10
I 10
			if (dirp->dd_size <= 0) {
				dprintf(stderr, "error reading directory\n");
E 10
D 45
				return NULL;
E 45
I 45
				return (NULL);
E 45
I 10
			}
E 10
		}
		if (dirp->dd_loc >= dirp->dd_size) {
			dirp->dd_loc = 0;
			continue;
		}
		dp = (struct direct *)(dirp->dd_buf + dirp->dd_loc);
		if (dp->d_reclen == 0 ||
D 10
		    dp->d_reclen > DIRBLKSIZ + 1 - dirp->dd_loc)
E 10
I 10
		    dp->d_reclen > DIRBLKSIZ + 1 - dirp->dd_loc) {
			dprintf(stderr, "corrupted directory: bad reclen %d\n",
				dp->d_reclen);
E 10
D 45
			return NULL;
E 45
I 45
			return (NULL);
E 45
I 10
		}
E 10
		dirp->dd_loc += dp->d_reclen;
I 10
D 54
		if (dp->d_ino == 0 && strcmp(dp->d_name, "/") != 0)
			continue;
E 54
I 54
		if (dp->d_ino == 0 && strcmp(dp->d_name, "/") == 0)
			return (NULL);
E 54
D 11
		if (dp->d_ino < 0 || dp->d_ino >= maxino) {
E 11
I 11
		if (dp->d_ino >= maxino) {
E 11
			dprintf(stderr, "corrupted directory: bad inum %d\n",
				dp->d_ino);
			continue;
		}
E 10
D 3
		if (dp->d_ino == 0)
			continue;
E 3
		return (dp);
	}
}

/*
I 18
 * Simulate the opening of a directory
 */
D 37
DIR *
E 37
I 37
RST_DIR *
E 37
rst_opendir(name)
D 47
	char *name;
E 47
I 47
	const char *name;
E 47
{
	struct inotab *itp;
I 46
	RST_DIR *dirp;
E 46
	ino_t ino;

	if ((ino = dirlookup(name)) > 0 &&
	    (itp = inotablookup(ino)) != NULL) {
I 46
		dirp = opendirfile(dirfile);
E 46
		rst_seekdir(dirp, itp->t_seekpt, itp->t_seekpt);
		return (dirp);
	}
D 48
	return (0);
E 48
I 48
	return (NULL);
E 48
I 46
}

/*
 * In our case, there is nothing to do when closing a directory.
 */
void
rst_closedir(dirp)
	RST_DIR *dirp;
{

D 47
	close(dirp->dd_fd);
E 47
I 47
	(void)close(dirp->dd_fd);
E 47
	free(dirp);
	return;
E 46
I 29
}

/*
 * Simulate finding the current offset in the directory.
 */
D 38
off_t
E 38
I 38
D 45
long
E 45
I 45
static long
E 45
E 38
rst_telldir(dirp)
D 37
	DIR *dirp;
E 37
I 37
	RST_DIR *dirp;
E 37
{
D 38
	off_t lseek();
E 38
I 38
D 45
	long lseek();
E 38

	return (lseek(dirp->dd_fd, 0L, 1) - dirp->dd_size + dirp->dd_loc);
E 45
I 45
	return ((long)lseek(dirp->dd_fd,
	    (off_t)0, SEEK_CUR) - dirp->dd_size + dirp->dd_loc);
E 45
}

/*
 * Open a directory file.
 */
D 37
DIR *
E 37
I 37
D 45
RST_DIR *
E 45
I 45
static RST_DIR *
E 45
E 37
opendirfile(name)
D 47
	char *name;
E 47
I 47
	const char *name;
E 47
{
D 37
	register DIR *dirp;
E 37
I 37
	register RST_DIR *dirp;
E 37
	register int fd;

D 45
	if ((fd = open(name, 0)) == -1)
		return NULL;
D 37
	if ((dirp = (DIR *)malloc(sizeof(DIR))) == NULL) {
E 37
I 37
	if ((dirp = (RST_DIR *)malloc(sizeof(RST_DIR))) == NULL) {
E 37
		close (fd);
		return NULL;
E 45
I 45
	if ((fd = open(name, O_RDONLY)) == -1)
		return (NULL);
	if ((dirp = malloc(sizeof(RST_DIR))) == NULL) {
		(void)close(fd);
		return (NULL);
E 45
	}
	dirp->dd_fd = fd;
	dirp->dd_loc = 0;
D 45
	return dirp;
E 45
I 45
	return (dirp);
E 45
E 29
}

/*
E 18
 * Set the mode, owner, and times for all new or changed directories
 */
I 45
void
E 45
D 8
setdirmodes(modefile)
	char *modefile;
E 8
I 8
D 43
setdirmodes()
E 43
I 43
setdirmodes(flags)
	int flags;
E 43
E 8
{
	FILE *mf;
	struct modeinfo node;
	struct entry *ep;
	char *cp;
	
	vprintf(stdout, "Set directory mode, owner, and times.\n");
I 17
D 27
	(void) sprintf(modefile, "/tmp/rstmode%d", dumpdate);
E 27
I 27
	(void) sprintf(modefile, "%s/rstmode%d", _PATH_TMP, dumpdate);
E 27
E 17
	mf = fopen(modefile, "r");
	if (mf == NULL) {
D 45
		perror("fopen");
E 45
I 45
		fprintf(stderr, "fopen: %s\n", strerror(errno));
E 45
D 17
		panic("cannot open mode file %s\n", modefile);
E 17
I 17
		fprintf(stderr, "cannot open mode file %s\n", modefile);
		fprintf(stderr, "directory mode, owner, and times not set\n");
		return;
E 17
	}
	clearerr(mf);
D 2
	fread((char *)&node, 1, sizeof(struct modeinfo), mf);
	while (!feof(mf)) {
E 2
I 2
	for (;;) {
D 6
		fread((char *)&node, 1, sizeof(struct modeinfo), mf);
E 6
I 6
		(void) fread((char *)&node, 1, sizeof(struct modeinfo), mf);
E 6
		if (feof(mf))
			break;
E 2
		ep = lookupino(node.ino);
D 2
		if (ep == NIL)
E 2
I 2
D 8
		if (ep == NIL) {
			if (command == 'x')
E 8
I 8
D 9
		if (ep == NIL || (ep->e_flags & NEW) == 0) {
E 9
I 9
D 15
		if (ep == NIL) {
E 9
			if (command != 'r' && command != 'R')
E 15
I 15
		if (command == 'i' || command == 'x') {
D 45
			if (ep == NIL)
E 45
I 45
			if (ep == NULL)
E 45
E 15
E 8
				continue;
I 20
D 43
			if (ep->e_flags & EXISTED) {
E 43
I 43
			if ((flags & FORCE) == 0 && ep->e_flags & EXISTED) {
E 43
				ep->e_flags &= ~NEW;
				continue;
			}
E 20
E 2
D 15
			panic("cannot find directory inode %d\n", node.ino);
E 15
I 15
			if (node.ino == ROOTINO &&
		   	    reply("set owner/mode for '.'") == FAIL)
				continue;
E 15
I 2
		}
I 15
D 32
		if (ep == NIL)
E 32
I 32
D 45
		if (ep == NIL) {
E 45
I 45
		if (ep == NULL) {
E 45
E 32
			panic("cannot find directory inode %d\n", node.ino);
E 15
E 2
D 32
		cp = myname(ep);
D 6
		chown(cp, node.uid, node.gid);
		chmod(cp, node.mode);
E 6
I 6
		(void) chown(cp, node.uid, node.gid);
		(void) chmod(cp, node.mode);
E 6
D 28
		utime(cp, node.timep);
E 28
I 28
		utimes(cp, node.timep);
E 28
I 8
		ep->e_flags &= ~NEW;
E 32
I 32
		} else {
			cp = myname(ep);
			(void) chown(cp, node.uid, node.gid);
			(void) chmod(cp, node.mode);
I 53
			(void) chflags(cp, node.flags);
E 53
			utimes(cp, node.timep);
			ep->e_flags &= ~NEW;
		}
E 32
E 8
D 2
		fread((char *)&node, 1, sizeof(struct modeinfo), mf);
E 2
	}
	if (ferror(mf))
		panic("error setting directory modes\n");
D 6
	fclose(mf);
E 6
I 6
	(void) fclose(mf);
E 6
I 2
D 4
	unlink(modefile);
E 4
I 4
D 8
	(void) unlink(modefile);
E 8
E 4
E 2
}

/*
 * Generate a literal copy of a directory.
 */
I 45
int
E 45
genliteraldir(name, ino)
	char *name;
	ino_t ino;
{
	register struct inotab *itp;
	int ofile, dp, i, size;
	char buf[BUFSIZ];

	itp = inotablookup(ino);
	if (itp == NULL)
D 3
		panic("cannot find directory inode %d named %s\n", ino, name);
E 3
I 3
		panic("Cannot find directory inode %d named %s\n", ino, name);
E 3
D 12
	if ((ofile = open(name, FWRONLY|FCREATE, 0666)) < 0) {
E 12
I 12
D 55
	if ((ofile = creat(name, 0666)) < 0) {
E 55
I 55
	if ((ofile = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0) {
E 55
E 12
D 11
		fprintf(stderr, "%s: cannot create file\n", name);
E 11
I 11
		fprintf(stderr, "%s: ", name);
		(void) fflush(stderr);
D 45
		perror("cannot create file");
E 45
I 45
		fprintf(stderr, "cannot create file: %s\n", strerror(errno));
E 45
E 11
		return (FAIL);
	}
D 11
	seekdir(dirp, itp->t_seekpt, itp->t_seekpt);
E 11
I 11
	rst_seekdir(dirp, itp->t_seekpt, itp->t_seekpt);
E 11
	dp = dup(dirp->dd_fd);
	for (i = itp->t_size; i > 0; i -= BUFSIZ) {
		size = i < BUFSIZ ? i : BUFSIZ;
		if (read(dp, buf, (int) size) == -1) {
			fprintf(stderr,
				"write error extracting inode %d, name %s\n",
				curfile.ino, curfile.name);
D 45
			perror("read");
E 45
I 45
			fprintf(stderr, "read: %s\n", strerror(errno));
E 45
			done(1);
		}
D 25
		if (write(ofile, buf, (int) size) == -1) {
E 25
I 25
		if (!Nflag && write(ofile, buf, (int) size) == -1) {
E 25
			fprintf(stderr,
				"write error extracting inode %d, name %s\n",
				curfile.ino, curfile.name);
D 45
			perror("write");
E 45
I 45
			fprintf(stderr, "write: %s\n", strerror(errno));
E 45
			done(1);
		}
	}
D 6
	close(dp);
	close(ofile);
E 6
I 6
	(void) close(dp);
	(void) close(ofile);
E 6
	return (GOOD);
D 7
}

/*
I 3
 * Determine the type of an inode
 */
inodetype(ino)
	ino_t ino;
{
	struct inotab *itp;

	itp = inotablookup(ino);
	if (itp == NULL)
		return (LEAF);
	return (NODE);
E 7
D 18
}

/*
I 8
 * Do an "ls" style listing of a directory
 */
printlist(name, ino)
	char *name;
	ino_t ino;
{
	register struct afile *fp;
	register struct inotab *itp;
	struct afile *dfp0, *dfplast;
	struct afile single;

	itp = inotablookup(ino);
	if (itp == NULL) {
		single.fnum = ino;
		single.fname = savename(rindex(name, '/') + 1);
		dfp0 = &single;
		dfplast = dfp0 + 1;
	} else {
D 11
		seekdir(dirp, itp->t_seekpt, itp->t_seekpt);
E 11
I 11
		rst_seekdir(dirp, itp->t_seekpt, itp->t_seekpt);
E 11
		if (getdir(dirp, &dfp0, &dfplast) == FAIL)
			return;
	}
	qsort((char *)dfp0, dfplast - dfp0, sizeof (struct afile), fcmp);
	formatf(dfp0, dfplast);
	for (fp = dfp0; fp < dfplast; fp++)
		freename(fp->fname);
}

/*
 * Read the contents of a directory.
 */
getdir(dirp, pfp0, pfplast)
	DIR *dirp;
	struct afile **pfp0, **pfplast;
{
	register struct afile *fp;
	register struct direct *dp;
	static struct afile *basefp = NULL;
	static long nent = 20;

D 14
	if (basefp == NULL)
E 14
I 14
	if (basefp == NULL) {
E 14
		basefp = (struct afile *)calloc((unsigned)nent,
			sizeof (struct afile));
I 14
		if (basefp == NULL) {
			fprintf(stderr, "ls: out of memory\n");
			return (FAIL);
		}
	}
E 14
	fp = *pfp0 = basefp;
	*pfplast = *pfp0 + nent;
D 11
	while (dp = readdir(dirp)) {
E 11
I 11
	while (dp = rst_readdir(dirp)) {
E 11
D 10
		if (dp->d_ino == 0 && strcmp(dp->d_name, "/") == 0)
E 10
I 10
		if (dp == NULL || dp->d_ino == 0)
E 10
			break;
D 10
		if (BIT(dp->d_ino, dumpmap) == 0)
E 10
I 10
		if (!dflag && BIT(dp->d_ino, dumpmap) == 0)
E 10
			continue;
		if (vflag == 0 &&
		    (strcmp(dp->d_name, ".") == 0 ||
		     strcmp(dp->d_name, "..") == 0))
			continue;
		fp->fnum = dp->d_ino;
		fp->fname = savename(dp->d_name);
		fp++;
		if (fp == *pfplast) {
			basefp = (struct afile *)realloc((char *)basefp,
			    (unsigned)(2 * nent * sizeof (struct afile)));
			if (basefp == 0) {
				fprintf(stderr, "ls: out of memory\n");
				return (FAIL);
			}
			*pfp0 = basefp;
			fp = *pfp0 + nent;
			*pfplast = fp + nent;
			nent *= 2;
		}
	}
	*pfplast = fp;
	return (GOOD);
}

/*
 * Print out a pretty listing of a directory
 */
formatf(fp0, fplast)
	struct afile *fp0, *fplast;
{
	register struct afile *fp;
	struct entry *np;
	int width = 0, w, nentry = fplast - fp0;
	int i, j, len, columns, lines;
	char *cp;

	if (fp0 == fplast)
		return;
	for (fp = fp0; fp < fplast; fp++) {
		fp->ftype = inodetype(fp->fnum);
		np = lookupino(fp->fnum);
		if (np != NIL)
			fp->fflags = np->e_flags;
		else
			fp->fflags = 0;
		len = strlen(fmtentry(fp));
		if (len > width)
			width = len;
	}
	width += 2;
	columns = 80 / width;
	if (columns == 0)
		columns = 1;
	lines = (nentry + columns - 1) / columns;
	for (i = 0; i < lines; i++) {
		for (j = 0; j < columns; j++) {
			fp = fp0 + j * lines + i;
			cp = fmtentry(fp);
			fprintf(stderr, "%s", cp);
			if (fp + lines >= fplast) {
				fprintf(stderr, "\n");
				break;
			}
			w = strlen(cp);
			while (w < width) {
				w++;
				fprintf(stderr, " ");
			}
		}
	}
}

/*
 * Comparison routine for qsort.
 */
fcmp(f1, f2)
	register struct afile *f1, *f2;
{

	return (strcmp(f1->fname, f2->fname));
}

/*
 * Format a directory entry.
 */
char *
fmtentry(fp)
	register struct afile *fp;
{
	static char fmtres[BUFSIZ];
	register char *cp, *dp;

	if (vflag)
		(void) sprintf(fmtres, "%5d ", fp->fnum);
	else
		fmtres[0] = '\0';
	dp = &fmtres[strlen(fmtres)];
D 10
	if ((fp->fflags & NEW) != 0)
E 10
I 10
	if (dflag && BIT(fp->fnum, dumpmap) == 0)
		*dp++ = '^';
	else if ((fp->fflags & NEW) != 0)
E 10
		*dp++ = '*';
	else
		*dp++ = ' ';
	for (cp = fp->fname; *cp; cp++)
		if (!vflag && (*cp < ' ' || *cp >= 0177))
			*dp++ = '?';
		else
			*dp++ = *cp;
	if (fp->ftype == NODE)
		*dp++ = '/';
	*dp++ = 0;
	return (fmtres);
E 18
}

/*
 * Determine the type of an inode
 */
I 45
int
E 45
inodetype(ino)
	ino_t ino;
{
	struct inotab *itp;

	itp = inotablookup(ino);
	if (itp == NULL)
		return (LEAF);
	return (NODE);
}

/*
E 8
E 3
 * Allocate and initialize a directory inode entry.
 * If requested, save its pertinent mode, owner, and time info.
 */
I 3
D 45
struct inotab *
E 45
I 45
static struct inotab *
E 45
E 3
allocinotab(ino, dip, seekpt)
	ino_t ino;
	struct dinode *dip;
D 38
	daddr_t seekpt;
E 38
I 38
	long seekpt;
E 38
{
	register struct inotab	*itp;
	struct modeinfo node;
D 3
	static int prevseekpt = 0;
E 3

D 45
	itp = (struct inotab *)calloc(1, sizeof(struct inotab));
I 14
	if (itp == 0)
E 45
I 45
	itp = calloc(1, sizeof(struct inotab));
	if (itp == NULL)
E 45
		panic("no memory directory table\n");
E 14
	itp->t_next = inotab[INOHASH(ino)];
	inotab[INOHASH(ino)] = itp;
	itp->t_ino = ino;
	itp->t_seekpt = seekpt;
D 3
	itp->t_size = seekpt - prevseekpt;
	prevseekpt = seekpt;
E 3
	if (mf == NULL)
D 3
		return;
E 3
I 3
D 48
		return(itp);
E 48
I 48
		return (itp);
E 48
E 3
	node.ino = ino;
D 28
	node.timep[0] = dip->di_atime;
	node.timep[1] = dip->di_mtime;
E 28
I 28
D 40
	node.timep[0].tv_sec = dip->di_atime;
	node.timep[0].tv_usec = 0;
	node.timep[1].tv_sec = dip->di_mtime;
	node.timep[1].tv_usec = 0;
E 40
I 40
D 41
	node.timep[0] = dip->di_atime;
	node.timep[1] = dip->di_mtime;
E 41
I 41
D 56
	node.timep[0].tv_sec = dip->di_atime.ts_sec;
	node.timep[0].tv_usec = dip->di_atime.ts_nsec / 1000;
	node.timep[1].tv_sec = dip->di_mtime.ts_sec;
	node.timep[1].tv_usec = dip->di_mtime.ts_nsec / 1000;
E 56
I 56
	node.timep[0].tv_sec = dip->di_atime;
	node.timep[0].tv_usec = dip->di_atimensec / 1000;
	node.timep[1].tv_sec = dip->di_mtime;
	node.timep[1].tv_usec = dip->di_mtimensec / 1000;
E 56
E 41
E 40
E 28
	node.mode = dip->di_mode;
I 53
	node.flags = dip->di_flags;
E 53
	node.uid = dip->di_uid;
	node.gid = dip->di_gid;
D 6
	fwrite((char *)&node, 1, sizeof(struct modeinfo), mf);
E 6
I 6
	(void) fwrite((char *)&node, 1, sizeof(struct modeinfo), mf);
E 6
I 3
D 48
	return(itp);
E 48
I 48
	return (itp);
E 48
E 3
}

/*
 * Look up an inode in the table of directories
 */
D 45
struct inotab *
E 45
I 45
static struct inotab *
E 45
inotablookup(ino)
	ino_t	ino;
{
	register struct inotab *itp;

	for (itp = inotab[INOHASH(ino)]; itp != NULL; itp = itp->t_next)
		if (itp->t_ino == ino)
D 48
			return(itp);
E 48
I 48
			return (itp);
E 48
D 45
	return ((struct inotab *)0);
E 45
I 45
	return (NULL);
E 45
}

/*
 * Clean up and exit
 */
I 45
D 48
void
E 48
I 48
__dead void
E 48
E 45
done(exitcode)
	int exitcode;
{

	closemt();
D 4
	unlink(dirfile);
E 4
I 4
D 8
	(void) unlink(dirfile);
E 8
I 8
	if (modefile[0] != '#')
		(void) unlink(modefile);
	if (dirfile[0] != '#')
		(void) unlink(dirfile);
E 8
E 4
	exit(exitcode);
}
E 1
