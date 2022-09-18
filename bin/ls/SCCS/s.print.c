h07771
s 00003/00000/00267
d D 8.5 94/07/28 03:38:20 pendry 45 44
c changes for whiteouts and union filesystem
e
s 00004/00001/00263
d D 8.4 94/04/17 09:45:05 bostic 44 43
c POSIX.2 says to print a pipe character after fifo names
e
s 00001/00001/00263
d D 8.3 94/04/02 09:56:18 pendry 43 42
c add 1994 copyright
e
s 00006/00006/00258
d D 8.2 94/04/01 02:08:14 pendry 42 41
c prettyness police
e
s 00002/00002/00262
d D 8.1 93/06/02 18:30:12 mckusick 41 40
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00262
d D 5.39 93/06/02 18:29:56 bostic 40 38
c correct ls -lR of trees with symbolic links (one more time with feeling)
e
s 00002/00002/00263
d R 8.1 93/05/31 14:45:59 bostic 39 38
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00009/00253
d D 5.38 93/04/29 12:40:03 bostic 38 37
c use err/warn(3) from C library, cast size arguments to printf
e
s 00003/00003/00259
d D 5.37 92/07/20 12:16:36 elan 37 36
c fix for symbolic links on relative pathnames
e
s 00003/00000/00259
d D 5.36 92/06/28 15:43:48 bostic 36 35
c make display line up if block/char devices displayed with other
c files.  (Jan-Simon has *way* too much free time...)
e
s 00002/00002/00257
d D 5.35 92/06/03 23:52:00 mckusick 35 34
c st_blocks is a quad
e
s 00001/00001/00258
d D 5.34 92/06/01 22:25:05 mckusick 34 33
c sizes are now 64-bit numbers
e
s 00062/00096/00197
d D 5.33 92/03/13 17:09:09 elan 33 32
c calculate all of the field sizes dynamically
e
s 00005/00008/00288
d D 5.32 92/03/01 16:52:59 bostic 32 31
c replace -k with the BLOCKSIZE environmental variable
e
s 00002/00000/00294
d D 5.31 92/03/01 13:22:08 bostic 31 30
c lint
e
s 00003/00001/00291
d D 5.30 92/02/04 16:42:20 bostic 30 29
c lint
e
s 00007/00003/00285
d D 5.29 92/01/30 10:14:34 elan 29 28
c Fixed bug of determining the path for reading links off the command 
c line arguments in printlink().
e
s 00102/00066/00186
d D 5.28 92/01/29 16:23:01 elan 28 27
c Changed print routines to conform to new ls(1) inplementation using 
c fts(3) routines.
e
s 00001/00001/00251
d D 5.27 91/12/12 17:39:00 mckusick 27 26
c missing static declaration
e
s 00031/00000/00221
d D 5.26 91/12/12 16:36:51 mckusick 26 25
c add -o option to list file flags
e
s 00028/00015/00193
d D 5.25 91/10/28 15:45:25 bostic 25 24
c It's a brave new ANSI world!
e
s 00004/00001/00204
d D 5.24 90/10/19 14:34:21 bostic 24 23
c for Marc; -T should display all time information
e
s 00001/00001/00204
d D 5.23 90/07/22 12:56:34 bostic 23 22
c there needs to be a way to get the hour/minute of a file that's more
c than six months old.  And ls(1) needs more options anyway.
e
s 00002/00006/00203
d D 5.22 90/05/10 21:31:49 bostic 22 21
c strmode doesn't allocate space anymore, just use the stack
e
s 00009/00111/00200
d D 5.21 90/04/19 16:05:45 bostic 21 20
c use strmode(3)
e
s 00001/00011/00310
d D 5.20 90/04/08 17:41:48 bostic 20 19
c get redist notice from /usr/share/misc
e
s 00002/00002/00319
d D 5.19 90/03/13 12:09:08 bostic 19 18
c new flag to user_from_uid and group_from_gid
e
s 00006/00051/00315
d D 5.18 90/03/05 10:30:39 bostic 18 17
c use utility routines user_from_uid and group_from_gid
e
s 00005/00000/00361
d D 5.17 90/02/23 14:50:22 bostic 17 16
c don't core dump on filenames larger than the terminal window
e
s 00002/00001/00359
d D 5.16 90/01/03 14:58:42 bostic 16 15
c make sure fields are space separated
e
s 00012/00005/00348
d D 5.15 89/08/22 12:26:44 bostic 15 14
c default sizes are in 512-byte blocks; add -k flag for kilobytes
e
s 00001/00001/00352
d D 5.14 89/06/28 17:20:14 bostic 14 13
c typo; wasn't printing wheel group files
e
s 00003/00002/00350
d D 5.13 89/06/27 18:02:27 bostic 13 12
c make `total' line, directory name, and preceding newline right
e
s 00002/00002/00350
d D 5.12 89/06/26 19:00:13 bostic 12 11
c don't zero pad uid/gid's
e
s 00004/00002/00348
d D 5.11 89/06/26 12:45:53 bostic 11 10
c print totals for -s flag, as well as -l
e
s 00002/00002/00348
d D 5.10 89/06/25 15:34:28 bostic 10 9
c fix blocks to be right for current system; eventually go to 512...
e
s 00005/00012/00345
d D 5.9 89/06/25 13:17:14 bostic 9 8
c use tabs all the time
e
s 00015/00020/00342
d D 5.8 89/06/25 11:10:03 bostic 8 7
c cleanup
e
s 00031/00026/00331
d D 5.7 89/06/25 11:01:00 bostic 7 6
c first working version, checkpoint
e
s 00003/00005/00354
d D 5.6 89/06/25 09:44:09 bostic 6 5
c checkpoint formatting code
e
s 00003/00017/00356
d D 5.5 89/06/25 09:40:31 bostic 5 4
c keep track of blocks and max file name length in tabdir
e
s 00062/00061/00311
d D 5.4 89/06/25 08:16:21 bostic 4 3
c break printdir up into three separate functions
e
s 00039/00021/00333
d D 5.3 89/06/24 22:01:01 bostic 3 2
c hash passwd/group files
e
s 00003/00000/00351
d D 5.2 89/06/24 18:57:44 bostic 2 1
c fix copyright notice
e
s 00351/00000/00000
d D 5.1 89/06/24 18:19:56 bostic 1 0
c date and time created 89/06/24 18:19:56 by bostic
e
u
U
t
T
I 1
/*
D 41
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 41
I 41
D 43
 * Copyright (c) 1989, 1993
E 43
I 43
 * Copyright (c) 1989, 1993, 1994
E 43
 *	The Regents of the University of California.  All rights reserved.
E 41
 *
I 2
 * This code is derived from software contributed to Berkeley by
 * Michael Fischbein.
 *
E 2
D 20
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
E 20
I 20
D 25
%sccs.include.redist.c%
E 25
I 25
 * %sccs.include.redist.c%
E 25
E 20
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>
I 28
D 38
#include <fts.h>
E 28
D 25
#include <stdio.h>
E 25
I 25
#include <time.h>
E 38
I 38

#include <err.h>
E 38
#include <errno.h>
I 38
#include <fts.h>
E 38
E 25
#include <grp.h>
#include <pwd.h>
I 3
D 38
#include <utmp.h>
I 31
#include <unistd.h>
E 31
E 3
#include <tzfile.h>
I 30
#include <stdlib.h>
E 38
E 30
I 25
#include <stdio.h>
I 38
#include <stdlib.h>
E 38
I 31
#include <string.h>
I 38
#include <time.h>
#include <tzfile.h>
#include <unistd.h>
#include <utmp.h>

E 38
E 31
E 25
#include "ls.h"
I 25
#include "extern.h"
E 25
D 28

I 25
static int	printaname __P((LS *));
static void	printlink __P((char *));
static void	printtime __P((time_t));
static int	printtype __P((u_int));
E 28
I 28
D 33
	
E 28
I 26
static char	*flags_from_fid __P((long));
I 28
static int	 printaname __P((FTSENT *));
static void	 printlink __P((FTSENT *));
static void	 printtime __P((time_t));
static int	 printtype __P((u_int));
E 33
E 28
E 26

I 28
D 33
#define	IS_NOPRINT(e)	((e)->fts_number == NO_PRINT)
E 33
I 33
static int	printaname __P((FTSENT *, u_long, u_long));
static void	printlink __P((FTSENT *));
static void	printtime __P((time_t));
static int	printtype __P((u_int));
E 33

D 33
/* ARGUSED */
E 33
I 33
#define	IS_NOPRINT(p)	((p)->fts_number == NO_PRINT)

E 33
E 28
void
E 25
D 4
printdir(stats, num)
	LS *stats;		/* the statted, sorted directory */
E 4
I 4
D 28
printscol(stats, num)
	register LS *stats;
E 4
	register int num;
E 28
I 28
D 33
printscol(dlist, entries, btotal, maxlen)
	FTSENT *dlist;
	int entries, maxlen;
	u_long btotal;
E 33
I 33
printscol(dp)
	DISPLAY *dp;
E 33
E 28
{
D 4
	extern int (*lengthfcn)();
	register int entry;
	long blocks;		/* sum of blocks in longform listing */
E 4
I 4
D 28
	for (; num--; ++stats) {
		(void)printaname(stats);
		(void)putchar('\n');
	}
E 28
I 28
D 42
	register FTSENT *p;
E 42
I 42
	FTSENT *p;
E 42

D 33
	for (p = dlist; p; p = p->fts_link)
		if (!IS_NOPRINT(p)) {
			(void)printaname(p);
			(void)putchar('\n');
		}
E 33
I 33
	for (p = dp->list; p; p = p->fts_link) {
		if (IS_NOPRINT(p))
			continue;
		(void)printaname(p, dp->s_inode, dp->s_block);
		(void)putchar('\n');
	}
E 33
E 28
}

I 28
D 33
/* ARGUSED */
E 33
E 28
I 25
void
E 25
D 28
printlong(stats, num)
	LS *stats;
	register int num;
E 28
I 28
D 33
printlong(dlist, entries, btotal, maxlen)
	FTSENT *dlist;
	int entries, maxlen;
	u_long btotal;
E 33
I 33
printlong(dp)
	DISPLAY *dp;
E 33
E 28
{
I 28
D 42
	register FTSENT *p;
	register struct stat *sp;
E 42
I 42
	struct stat *sp;
	FTSENT *p;
E 42
E 28
I 18
D 21
	char *user_from_uid(), *group_from_gid();
E 21
I 21
D 25
	extern int errno;
D 22
	static char *modep;
	char *user_from_uid(), *group_from_gid(), *strerror();
E 22
I 22
	char modep[15], *user_from_uid(), *group_from_gid(), *strerror();
E 25
I 25
D 33
	char modep[15], *user_from_uid(), *group_from_gid();
E 25
E 22
E 21
D 28

E 18
D 5
	register long blocks;	/* sum of blocks */
	register int i;

	for (i = 0, blocks = 0; i < num; ++i)
		blocks += stats[i].lstat.st_blocks;
	(void)printf("total %ld\n", blocks);
E 5
I 5
D 11
	(void)printf("total %lu\n", stats[0].lstat.st_flags);
E 11
I 11
D 13
	(void)printf("total %lu\n", stats[0].lstat.st_btotal);
E 13
I 13
	if (f_total)
D 15
		(void)printf("total %lu\n", stats[0].lstat.st_btotal);
E 15
I 15
		(void)printf("total %lu\n", f_kblocks ?
		    howmany(stats[0].lstat.st_btotal, 2) :
		    stats[0].lstat.st_btotal);
E 15
E 13
E 11
E 5
	for (; num--; ++stats) {
E 28
I 28
	
	
	if (dlist->fts_level != FTS_ROOTLEVEL && (f_longform || f_size))
D 32
		(void)printf("total %lu\n",
		    f_kblocks ? howmany(btotal, 2) : btotal);
E 32
I 32
		(void)printf("total %lu\n", howmany(btotal, blocksize));
E 32
	for (p = dlist; p; p = p->fts_link) {
E 33
I 33
	NAMES *np;
	char buf[20];

	if (dp->list->fts_level != FTS_ROOTLEVEL && (f_longform || f_size))
		(void)printf("total %lu\n", howmany(dp->btotal, blocksize));

	for (p = dp->list; p; p = p->fts_link) {
E 33
		if (IS_NOPRINT(p))
			continue;
		sp = p->fts_statp;
E 28
		if (f_inode)
D 28
			(void)printf("%6lu ", stats->lstat.st_ino);
E 28
I 28
D 33
			(void)printf("%6lu ", sp->st_ino);
E 33
I 33
			(void)printf("%*lu ", dp->s_inode, sp->st_ino);
E 33
E 28
		if (f_size)
D 10
			(void)printf("%4ld ", stats->lstat.st_blocks / 2);
E 10
I 10
D 15
			(void)printf("%4ld ", stats->lstat.st_blocks);
E 15
I 15
D 32
			(void)printf("%4ld ", f_kblocks ?
D 28
			    howmany(stats->lstat.st_blocks, 2) :
			    stats->lstat.st_blocks);
E 15
E 10
D 21
		printperms(stats->lstat.st_mode);
D 15
		(void)printf("%3d ", stats->lstat.st_nlink);
E 15
I 15
D 18
		(void)printf("%3u ", stats->lstat.st_nlink);
E 15
		printowner(stats->lstat.st_uid);
E 18
I 18
		(void)printf("%3u %-*s ", stats->lstat.st_nlink, UT_NAMESIZE,
D 19
		    user_from_uid(stats->lstat.st_uid)); 
E 19
I 19
		    user_from_uid(stats->lstat.st_uid, 0));
E 21
I 21
D 22
		if (strmode(stats->lstat.st_mode, &modep)) {
			(void)fprintf(stderr, "ls: %s.\n", strerror(errno));
			exit(1);
		}
E 22
I 22
		(void)strmode(stats->lstat.st_mode, modep);
E 22
		(void)printf("%s %3u %-*s ", modep, stats->lstat.st_nlink,
		    UT_NAMESIZE, user_from_uid(stats->lstat.st_uid, 0));
E 28
I 28
			    howmany(sp->st_blocks, 2) : sp->st_blocks);
E 32
I 32
D 33
			(void)printf("%4ld ",
			    howmany(sp->st_blocks, blocksize));
E 32
		(void)strmode(sp->st_mode, modep);
		(void)printf("%s %3u %-*s ", modep, sp->st_nlink,
		    UT_NAMESIZE, user_from_uid(sp->st_uid, 0));
E 28
E 21
E 19
E 18
		if (f_group)
D 18
			printgrp(stats->lstat.st_gid);
E 18
I 18
D 28
			(void)printf("%-*s ", UT_NAMESIZE,
D 19
			    group_from_gid(stats->lstat.st_gid));
E 19
I 19
			    group_from_gid(stats->lstat.st_gid, 0));
E 28
I 28
			(void)printf("%-*s ",
			    UT_NAMESIZE, group_from_gid(sp->st_gid, 0));
E 33
I 33
D 35
			(void)printf("%*ld ",
E 35
I 35
			(void)printf("%*qd ",
E 35
			    dp->s_block, howmany(sp->st_blocks, blocksize));
		(void)strmode(sp->st_mode, buf);
		np = p->fts_pointer;
		(void)printf("%s %*u %-*s  %-*s  ", buf, dp->s_nlink,
		    sp->st_nlink, dp->s_user, np->user, dp->s_group,
		    np->group);
E 33
E 28
I 26
		if (f_flags)
D 28
			(void)printf("%-*s ", FLAGSWIDTH,
			    flags_from_fid(stats->lstat.st_flags));
E 26
E 19
E 18
		if (S_ISCHR(stats->lstat.st_mode) ||
		    S_ISBLK(stats->lstat.st_mode))
D 16
			(void)printf("%3d,%4d ", major(stats->lstat.st_rdev),
E 16
I 16
			(void)printf("%3d, %3d ", major(stats->lstat.st_rdev),
E 16
			    minor(stats->lstat.st_rdev));
E 28
I 28
D 33
			(void)printf("%-*s ",
			    FLAGSWIDTH, flags_from_fid(sp->st_flags));
		if (S_ISCHR(sp->st_mode) ||
		    S_ISBLK(sp->st_mode))
E 33
I 33
			(void)printf("%-*s ", dp->s_flags, np->flags);
		if (S_ISCHR(sp->st_mode) || S_ISBLK(sp->st_mode))
E 33
			(void)printf("%3d, %3d ",
			    major(sp->st_rdev), minor(sp->st_rdev));
I 36
		else if (dp->bcfile)
			(void)printf("%*s%*qd ",
			    8 - dp->s_size, "", dp->s_size, sp->st_size);
E 36
E 28
		else
D 28
			(void)printf("%8ld ", stats->lstat.st_size);
E 28
I 28
D 33
			(void)printf("%8ld ", sp->st_size);
E 33
I 33
D 34
			(void)printf("%*ld ", dp->s_size, sp->st_size);
E 34
I 34
			(void)printf("%*qd ", dp->s_size, sp->st_size);
E 34
E 33
E 28
		if (f_accesstime)
D 28
			printtime(stats->lstat.st_atime);
E 28
I 28
			printtime(sp->st_atime);
E 28
		else if (f_statustime)
D 28
			printtime(stats->lstat.st_ctime);
E 28
I 28
			printtime(sp->st_ctime);
E 28
		else
D 28
			printtime(stats->lstat.st_mtime);
		(void)printf("%s", stats->name);
E 28
I 28
			printtime(sp->st_mtime);
		(void)printf("%s", p->fts_name);
E 28
		if (f_type)
D 28
			(void)printtype(stats->lstat.st_mode);
		if (S_ISLNK(stats->lstat.st_mode))
			printlink(stats->name);
E 28
I 28
			(void)printtype(sp->st_mode);
		if (S_ISLNK(sp->st_mode))
			printlink(p);
E 28
		(void)putchar('\n');
	}
}

I 9
#define	TAB	8

I 25
void
E 25
E 9
D 28
printcol(stats, num)
	LS *stats;
D 8
	register int num;
E 8
I 8
	int num;
E 28
I 28
D 33
printcol(dlist, entries, btotal, maxlen)
	FTSENT *dlist;
	u_long btotal;
	int entries, maxlen;
E 33
I 33
printcol(dp)
	DISPLAY *dp;
E 33
E 28
E 8
{
D 5
	extern int (*lengthfcn)(), termwidth;
E 5
I 5
	extern int termwidth;
E 5
E 4
D 7
	int i;			/* subscript to stats */
	int maxlen;		/* length of longest name string */
E 7
I 7
D 8
	int row, col;
E 7
	int colwidth;		/* width of a printing column */
	int numcols;		/* number of columns */
D 7
	int collength;		/* lines in longest column */
E 7
I 7
	int numrows;		/* number of rows */
E 8
I 8
D 9
	register int chcnt;	/* total row character count printed */
	register int col, row;	/* row/column counters */
	register int colwidth;	/* width of a printing column */
E 8
E 7
	int base;		/* subscript for leftmost column */
D 7
	int offset;		/* delta from base to next column */
E 7
D 8
	int chcnt;		/* character count printed */
I 7
	int newcnt;
	int curcol;
E 8
I 8
	int endcol;		/* last column for this entry */
	int numcols;		/* total number of columns */
	int numrows;		/* total number of rows */
	int cnt;
E 9
I 9
D 28
	register int base, chcnt, cnt, col, colwidth;
E 28
I 28
	static FTSENT **array;
	static int lastentries = -1;
D 42
	register FTSENT *p;
	register int base, chcnt, cnt, col, colwidth, num;
E 42
I 42
	FTSENT *p;
	int base, chcnt, cnt, col, colwidth, num;
E 42
E 28
	int endcol, numcols, numrows, row;
E 9
E 8
E 7

D 4
	if (f_singlecol) {
		for (entry = 0; entry < num; ++entry) {
			(void)printaname(&stats[entry]);
			(void)putchar('\n');
		}
		return;
	}

	if (f_longform) {
		if (!f_firsttime) {
			for (i = 0, blocks = 0; i < num; ++i)
				blocks += stats[i].lstat.st_blocks;
			(void)printf("total %ld\n", blocks / 2);
		}
		for (i = 0; i < num; ++i) {
			if (f_inode)
				(void)printf("%6lu ", stats[i].lstat.st_ino);
			if (f_size)
				(void)printf("%4ld ",
				    stats[i].lstat.st_blocks / 2);
			printperms(stats[i].lstat.st_mode);
			(void)printf("%3d ", stats[i].lstat.st_nlink);
			printowner(stats[i].lstat.st_uid);
			if (f_group)
				printgrp(stats[i].lstat.st_gid);
			if (S_ISCHR(stats[i].lstat.st_mode) ||
			    S_ISBLK(stats[i].lstat.st_mode))
				(void)printf("%3d,%4d ",
				    major(stats[i].lstat.st_rdev),
				    minor(stats[i].lstat.st_rdev));
			else
				(void)printf("%8ld ", stats[i].lstat.st_size);
			if (f_accesstime)
				printtime(stats[i].lstat.st_atime);
			else if (f_statustime)
				printtime(stats[i].lstat.st_ctime);
			else
				printtime(stats[i].lstat.st_mtime);
			(void)printf("%s", stats[i].name);
			if (f_type)
				(void)printtype(stats[i].lstat.st_mode);
			if (S_ISLNK(stats[i].lstat.st_mode))
				printlink(stats[i].name);
			(void)putchar('\n');
		}
		return;
	}

E 4
D 5
	/*
	 * assume tabs every 8 columns WARNING: bad code (hard coded
	 * constants) follows:
	 */
D 4

E 4
	/* figure out max width */
	maxlen = -1;
	for (i = 0; i < num; ++i) {
		if (maxlen < lengthfcn(stats[i].name))
			maxlen = lengthfcn(stats[i].name);
	}
E 5
I 5
D 7
	maxlen = stats[0].lstat.st_flags;
E 7
I 7
D 11
	colwidth = stats[0].lstat.st_flags;
E 11
I 11
D 28
	colwidth = stats[0].lstat.st_maxlen;
E 28
I 28
	/*
	 * Have to do random access in the linked list -- build a table
	 * of pointers.
	 */
D 33
	if (entries > lastentries) {
		lastentries = entries;
E 33
I 33
	if (dp->entries > lastentries) {
		lastentries = dp->entries;
E 33
D 30
		if ((array = (FTSENT **) realloc(array, entries * sizeof(FTSENT *))) == NULL) {
E 30
I 30
		if ((array =
D 33
		    realloc(array, entries * sizeof(FTSENT *))) == NULL) {
E 33
I 33
		    realloc(array, dp->entries * sizeof(FTSENT *))) == NULL) {
E 33
E 30
D 38
			err(0, "%s", strerror(errno));
E 38
I 38
			warn(NULL);
E 38
D 33
			printscol(dlist, entries, btotal, maxlen);
E 33
I 33
			printscol(dp);
E 33
		}
	}
D 33
	for (p = dlist, num = 0; p; p = p->fts_link)
E 33
I 33
	for (p = dp->list, num = 0; p; p = p->fts_link)
E 33
		if (p->fts_number != NO_PRINT)
			array[num++] = p;

D 33
	colwidth = maxlen;
E 33
I 33
	colwidth = dp->maxlen;
E 33
E 28
E 11
E 7
E 5
D 6

	/* add fudge factors to max name length */
E 6
	if (f_inode)
D 7
		maxlen += 6;
E 7
I 7
D 33
		colwidth += 6;
E 33
I 33
		colwidth += dp->s_inode + 1;
E 33
E 7
	if (f_size)
D 7
		maxlen += 5;
E 7
I 7
D 33
		colwidth += 5;
E 33
I 33
		colwidth += dp->s_block + 1;
E 33
E 7
	if (f_type)
D 7
		maxlen += 1;
D 6
	/* one tab after maxlen */
	colwidth = (maxlen + 9) & ~0x7;
	numcols = (80 + colwidth - maxlen) / colwidth;
E 6
I 6
#define	TAB	8
	colwidth = maxlen + TAB + 1 & ~(TAB - 1);
	numcols = (termwidth + colwidth - maxlen) / colwidth;
E 6
	collength = (int)((float)num / (float)numcols + 0.999);
E 7
I 7
		colwidth += 1;
I 17

E 17
D 8
	colwidth += 3;
E 8
I 8
D 9
	colwidth += 2;
E 9
I 9
	colwidth = (colwidth + TAB) & ~(TAB - 1);
I 17
	if (termwidth < 2 * colwidth) {
D 28
		printscol(stats, num);
E 28
I 28
D 33
		printscol(dlist, 0, 0, 0);
E 33
I 33
		printscol(dp);
E 33
E 28
		return;
	}
E 17
E 9
E 8
E 7

D 7
	for (base = 0; base < collength; base++) {
		for (offset = 0, i = 0; i < numcols; ++i, offset += collength) {
			if (base + offset >= num)
E 7
I 7
	numcols = termwidth / colwidth;
	numrows = num / numcols;
	if (num % numcols)
		++numrows;

I 11
D 13
	if (f_size)
E 13
I 13
D 28
	if (f_size && f_total)
E 13
D 15
		(void)printf("total %lu\n", stats[0].lstat.st_btotal);
E 15
I 15
		(void)printf("total %lu\n", f_kblocks ?
		    howmany(stats[0].lstat.st_btotal, 2) :
		    stats[0].lstat.st_btotal);
E 28
I 28
D 33
	if (dlist->fts_level != FTS_ROOTLEVEL && (f_longform || f_size))
D 32
		(void)printf("total %lu\n",
		    f_kblocks ? howmany(btotal, 2) : btotal);
E 32
I 32
		(void)printf("total %lu\n", howmany(btotal, blocksize));
E 33
I 33
	if (dp->list->fts_level != FTS_ROOTLEVEL && (f_longform || f_size))
		(void)printf("total %lu\n", howmany(dp->btotal, blocksize));
E 33
E 32
E 28
E 15
E 11
D 9
#define	TAB	8
E 9
	for (row = 0; row < numrows; ++row) {
D 8
		curcol = colwidth;
		chcnt = 0;
		for (base = row, col = 0; col < numcols; ++col) {
E 8
I 8
		endcol = colwidth;
		for (base = row, chcnt = col = 0; col < numcols; ++col) {
E 8
D 28
			chcnt += printaname(stats + base);
E 28
I 28
D 33
			chcnt += printaname(array[base]);
E 33
I 33
			chcnt += printaname(array[base], dp->s_inode,
			    dp->s_block);
E 33
E 28
			if ((base += numrows) >= num)
E 7
				break;
D 7
			chcnt = printaname(&stats[base + offset]);
			if (base + offset + collength < num) {
				while (chcnt + 8 < colwidth) {
					(void)putchar('\t');
					chcnt += 8;
E 7
I 7
D 8
			for (;;) {
				newcnt = (chcnt + TAB & ~(TAB - 1));
				if (newcnt > curcol) {
					break;
E 7
				}
E 8
I 8
			while ((cnt = (chcnt + TAB & ~(TAB - 1))) <= endcol) {
E 8
D 7
				if (chcnt < colwidth)
					(void)putchar('\t');
				chcnt = (chcnt + 8) & ~0x7;
E 7
I 7
				(void)putchar('\t');
D 8
				chcnt = newcnt;
E 8
I 8
				chcnt = cnt;
E 8
E 7
			}
I 7
D 8
			for (; chcnt < curcol; ++chcnt)
E 8
I 8
D 9
			for (; chcnt < endcol; ++chcnt)
E 8
				(void)putchar(' ');
E 9
D 8
			curcol += colwidth;
E 8
I 8
			endcol += colwidth;
E 8
E 7
		}
D 7
		if (base + offset < num)
			(void)printaname(&stats[base + offset]);
		(void)printf("\n");
E 7
I 7
D 28
		putchar('\n');
E 28
I 28
		(void)putchar('\n');
E 28
E 7
	}
}

/*
 * print [inode] [size] name
D 28
 * return # of characters printed, no trailing characters
E 28
I 28
 * return # of characters printed, no trailing characters.
E 28
 */
I 25
static int
E 25
D 4
printaname(entry)
	LS *entry;
E 4
I 4
D 28
printaname(lp)
	LS *lp;
E 28
I 28
D 33
printaname(p)
E 33
I 33
printaname(p, inodefield, sizefield)
E 33
D 42
	register FTSENT *p;
E 42
I 42
	FTSENT *p;
E 42
I 33
	u_long sizefield, inodefield;
E 33
E 28
E 4
{
I 28
	struct stat *sp;
E 28
D 4
	int chcnt = 0;
E 4
I 4
	int chcnt;
E 4

I 28
	sp = p->fts_statp;
E 28
I 4
	chcnt = 0;
E 4
	if (f_inode)
D 4
		chcnt += printf("%5lu ", entry->lstat.st_ino);
E 4
I 4
D 28
		chcnt += printf("%5lu ", lp->lstat.st_ino);
E 28
I 28
D 33
		chcnt += printf("%5lu ", sp->st_ino);
E 33
I 33
D 38
		chcnt += printf("%*lu ", inodefield, sp->st_ino);
E 38
I 38
		chcnt += printf("%*lu ", (int)inodefield, sp->st_ino);
E 38
E 33
E 28
E 4
	if (f_size)
D 4
		chcnt += printf("%4ld ", entry->lstat.st_blocks / 2);
	chcnt += printf("%s", entry->name);
E 4
I 4
D 10
		chcnt += printf("%4ld ", lp->lstat.st_blocks / 2);
E 10
I 10
D 15
		chcnt += printf("%4ld ", lp->lstat.st_blocks);
E 15
I 15
D 32
		chcnt += printf("%4ld ", f_kblocks ?
D 28
		    howmany(lp->lstat.st_blocks, 2) : lp->lstat.st_blocks);
E 15
E 10
	chcnt += printf("%s", lp->name);
E 28
I 28
		    howmany(sp->st_blocks, 2) : sp->st_blocks);
E 32
I 32
D 33
		chcnt += printf("%4ld ", howmany(sp->st_blocks, blocksize));
E 33
I 33
D 35
		chcnt += printf("%*ld ",
E 35
I 35
		chcnt += printf("%*qd ",
E 35
D 38
		    sizefield, howmany(sp->st_blocks, blocksize));
E 38
I 38
		    (int)sizefield, howmany(sp->st_blocks, blocksize));
E 38
E 33
E 32
	chcnt += printf("%s", p->fts_name);
E 28
E 4
	if (f_type)
D 4
		chcnt += printtype(entry->lstat.st_mode);
E 4
I 4
D 28
		chcnt += printtype(lp->lstat.st_mode);
E 28
I 28
		chcnt += printtype(sp->st_mode);
E 28
E 4
D 25
	return(chcnt);
E 25
I 25
	return (chcnt);
E 25
D 18
}

D 3
/*
 * print group and user name
 */
printgrp(gid)
	gid_t gid;
E 3
I 3
#define	NCACHE	64		/* power of 2 */
#define	LSMASK	NCACHE - 1	/* bits to store with */
printowner(uid)
	uid_t uid;
E 3
{
D 3
	struct group *groupentry;
E 3
I 3
	static struct ncache {
		uid_t	uid;
		char	name[UT_NAMESIZE];
	} c_uid[NCACHE];
	register struct passwd *pw;
	register struct ncache *cp;
E 3

D 3
	if ((groupentry = getgrgid((int)gid)) == NULL) {
		/* can't find group, print out number instead */
		(void)printf("%-9u ", gid);
		return;
E 3
I 3
	cp = c_uid + (uid & LSMASK);
	if (cp->uid != uid || !*cp->name) {
		/* if can't find owner, print out number instead */
		if (!(pw = getpwuid(uid))) {
D 12
			(void)printf("%-*.*u ", UT_NAMESIZE, UT_NAMESIZE, uid);
E 12
I 12
			(void)printf("%-*u ", UT_NAMESIZE, uid);
E 12
			return;
		}
		cp->uid = uid;
		(void)strncpy(cp->name, pw->pw_name, UT_NAMESIZE);
E 3
	}
D 3
	(void)printf("%-9s", groupentry->gr_name);
	(void)getgrent();		/* to rewind group file */
E 3
I 3
	(void)printf("%-*.*s ", UT_NAMESIZE, UT_NAMESIZE, cp->name);
E 3
}

D 3
printowner(uid)
	uid_t uid;
E 3
I 3
printgrp(gid)
	gid_t gid;
E 3
{
D 3
	struct passwd *pwentry;
E 3
I 3
	static struct ncache {
		gid_t	gid;
		char	name[UT_NAMESIZE];
	} c_gid[NCACHE];
	register struct group *gr;
	register struct ncache *cp;
E 3

D 3
	if ((pwentry = getpwuid((int)uid)) == NULL) {
		/* can't find owner, print out number instead */
		(void)printf("%-9u ", uid);
		return;
E 3
I 3
	cp = c_gid + (gid & LSMASK);
D 14
	if (cp->gid != gid || *cp->name) {
E 14
I 14
	if (cp->gid != gid || !*cp->name) {
E 14
		/* can't find group, print out number instead */
		if (!(gr = getgrgid(gid))) {
D 12
			(void)printf("%-*.*u ", UT_NAMESIZE, UT_NAMESIZE, gid);
E 12
I 12
			(void)printf("%-*u ", UT_NAMESIZE, gid);
E 12
			return;
		}
		cp->gid = gid;
		(void)strncpy(cp->name, gr->gr_name, UT_NAMESIZE);
E 3
	}
D 3
	(void)printf("%-9s", pwentry->pw_name);
	(void)getpwent();
E 3
I 3
	(void)printf("%-*.*s ", UT_NAMESIZE, UT_NAMESIZE, cp->name);
E 18
E 3
}

I 25
static void
E 25
printtime(ftime)
	time_t ftime;
{
	int i;
D 25
	char *longstring, *ctime();
	time_t time();
E 25
I 25
	char *longstring;
E 25

D 25
	longstring = ctime((long *)&ftime);
E 25
I 25
D 33
	longstring = ctime((time_t *)&ftime);
E 33
I 33
	longstring = ctime(&ftime);
E 33
E 25
	for (i = 4; i < 11; ++i)
		(void)putchar(longstring[i]);

#define	SIXMONTHS	((DAYSPERNYEAR / 2) * SECSPERDAY)
D 23
	if (ftime + SIXMONTHS > time((time_t *)NULL))
E 23
I 23
D 24
	if (f_sectime || ftime + SIXMONTHS > time((time_t *)NULL))
E 24
I 24
	if (f_sectime)
		for (i = 11; i < 24; i++)
			(void)putchar(longstring[i]);
D 33
	else if (ftime + SIXMONTHS > time((time_t *)NULL))
E 33
I 33
	else if (ftime + SIXMONTHS > time(NULL))
E 33
E 24
E 23
		for (i = 11; i < 16; ++i)
			(void)putchar(longstring[i]);
	else {
		(void)putchar(' ');
		for (i = 20; i < 24; ++i)
			(void)putchar(longstring[i]);
D 21
	}
	(void)putchar(' ');
}

/*
 * do the permissions printing, passed the mode
 */
printperms(mode)
	mode_t mode;
{
	 /* print type */
	switch (mode & S_IFMT) {
	case S_IFDIR:			/* directory */
		(void)putchar('d');
		break;
	case S_IFCHR:			/* character special */
		(void)putchar('c');
		break;
	case S_IFBLK:			/* block special */
		(void)putchar('b');
		break;
	case S_IFREG:			/* regular */
		(void)putchar('-');
		break;
	case S_IFLNK:			/* symbolic link */
		(void)putchar('l');
		break;
	case S_IFSOCK:			/* socket */
		(void)putchar('s');
		break;
#ifdef S_IFIFO
	case S_IFIFO:			/* fifo */
		(void)putchar('p');
		break;
#endif
	default:			/* unknown */
		(void)putchar('?');
		break;
	}
	/* usr */
	if (mode & S_IRUSR)
		(void)putchar('r');
	else
		(void)putchar('-');
	if (mode & S_IWUSR)
		(void)putchar('w');
	else
		(void)putchar('-');
	switch (mode & (S_IXUSR | S_ISUID)) {
	case 0:
		(void)putchar('-');
		break;
	case S_IXUSR:
		(void)putchar('x');
		break;
	case S_ISUID:
		(void)putchar('S');
		break;
	case S_IXUSR | S_ISUID:
		(void)putchar('s');
		break;
	}
	/* group */
	if (mode & S_IRGRP)
		(void)putchar('r');
	else
		(void)putchar('-');
	if (mode & S_IWGRP)
		(void)putchar('w');
	else
		(void)putchar('-');
	switch (mode & (S_IXGRP | S_ISGID)) {
	case 0:
		(void)putchar('-');
		break;
	case S_IXGRP:
		(void)putchar('x');
		break;
	case S_ISGID:
		(void)putchar('S');
		break;
	case S_IXGRP | S_ISGID:
		(void)putchar('s');
		break;
	}
	/* other */
	if (mode & S_IROTH)
		(void)putchar('r');
	else
		(void)putchar('-');
	if (mode & S_IWOTH)
		(void)putchar('w');
	else
		(void)putchar('-');
	switch (mode & (S_IXOTH | S_ISVTX)) {
	case 0:
		(void)putchar('-');
		break;
	case S_IXOTH:
		(void)putchar('x');
		break;
	case S_ISVTX:
		(void)putchar('T');
		break;
	case S_IXOTH | S_ISVTX:
		(void)putchar('t');
		break;
E 21
	}
I 16
	(void)putchar(' ');
E 16
}

I 25
static int
E 25
printtype(mode)
D 25
	mode_t mode;
E 25
I 25
	u_int mode;
E 25
{
D 44
	switch(mode & S_IFMT) {
E 44
I 44
	switch (mode & S_IFMT) {
E 44
	case S_IFDIR:
		(void)putchar('/');
I 44
		return (1);
	case S_IFIFO:
		(void)putchar('|');
E 44
D 25
		return(1);
E 25
I 25
		return (1);
E 25
	case S_IFLNK:
		(void)putchar('@');
D 25
		return(1);
E 25
I 25
		return (1);
E 25
	case S_IFSOCK:
		(void)putchar('=');
D 25
		return(1);
E 25
I 25
		return (1);
I 45
	case S_IFWHT:
		(void)putchar('%');
		return (1);
E 45
E 25
	}
	if (mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
		(void)putchar('*');
D 25
		return(1);
E 25
I 25
		return (1);
E 25
	}
D 25
	return(0);
E 25
I 25
	return (0);
E 25
}

I 25
static void
E 25
D 28
printlink(name)
	char *name;
E 28
I 28
printlink(p)
	FTSENT *p;
E 28
{
	int lnklen;
D 25
	char path[MAXPATHLEN + 1], *strerror();
E 25
I 25
D 28
	char path[MAXPATHLEN + 1];
E 25

E 28
I 28
	char name[MAXPATHLEN + 1], path[MAXPATHLEN + 1];
D 29
	
	(void)snprintf(name,
	    MAXPATHLEN, "%s/%s", p->fts_parent->fts_name,  p->fts_name);
E 29
I 29

I 37
D 40

E 40
E 37
D 33
        if (p->fts_level == FTS_ROOTLEVEL)
                (void)snprintf(name, MAXPATHLEN, "%s", p->fts_name);
        else
		(void)snprintf(name,
                   MAXPATHLEN, "%s/%s", p->fts_parent->fts_name,  p->fts_name);
E 33
I 33
	if (p->fts_level == FTS_ROOTLEVEL)
		(void)snprintf(name, sizeof(name), "%s", p->fts_name);
D 37
	else
E 37
I 37
	else 
E 37
		(void)snprintf(name, sizeof(name),
D 37
		    "%s/%s", p->fts_parent->fts_name, p->fts_name);
E 33

E 37
I 37
D 40
		    "%s/%s", p->fts_path, p->fts_name);
E 37
E 29
E 28
D 33
	if ((lnklen = readlink(name, path, MAXPATHLEN)) == -1) {
E 33
I 33
	if ((lnklen = readlink(name, path, sizeof(name) - 1)) == -1) {
E 40
I 40
		    "%s/%s", p->fts_parent->fts_accpath, p->fts_name);
	if ((lnklen = readlink(name, path, sizeof(path) - 1)) == -1) {
E 40
E 33
		(void)fprintf(stderr, "\nls: %s: %s\n", name, strerror(errno));
		return;
	}
	path[lnklen] = '\0';
	(void)printf(" -> %s", path);
I 26
D 33
}

D 27
char *
E 27
I 27
static char *
E 27
flags_from_fid(flags)
	long flags;
{
	static char buf[FLAGSWIDTH + 1];
	int size;

	size = FLAGSWIDTH;
	buf[0] = '\0';
	if (size && (flags & NODUMP)) {
		strncat(buf, "nodump", size);
		size -= 6;
	} else {
		strncat(buf, "dump", size);
		size -= 4;
	}
	if (size && (flags & IMMUTABLE)) {
		strncat(buf, ",nochg", size);
		size -= 6;
	}
	if (size && (flags & ARCHIVED)) {
		strncat(buf, ",arch", size);
		size -= 5;
	}
	return (buf);
E 33
E 26
}
E 1
