h42118
s 00002/00002/00090
d D 8.1 93/06/06 14:39:09 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00006/00080
d D 5.8 93/05/01 11:51:38 bostic 8 7
c use library err/warn(3) functions; lint, prettiness police
e
s 00002/00002/00084
d D 5.7 92/07/23 12:49:08 bostic 7 6
c fix printf output for ls.c
e
s 00008/00004/00078
d D 5.6 91/03/09 18:44:15 bostic 6 5
c ANSI
e
s 00001/00003/00081
d D 5.5 90/11/15 12:23:06 bostic 5 4
c don't need to declare errno twice, use sys/errno
e
s 00001/00011/00083
d D 5.4 90/06/01 16:49:02 bostic 4 3
c new copyright notice
e
s 00002/00005/00093
d D 5.3 90/05/10 21:27:11 bostic 3 2
c strmode doesn't allocate space anymore, just use the stack
e
s 00008/00110/00090
d D 5.2 90/04/19 16:06:24 bostic 2 1
c use strmode(3)
e
s 00200/00000/00000
d D 5.1 90/04/16 17:23:09 bostic 1 0
c new version derived from Cimarron Taylor's
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
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
I 5
D 6
#include <sys/errno.h>
E 6
I 6
D 8
#include <time.h>
E 6
E 5
#include <tzfile.h>
E 8
I 8

#include <err.h>
E 8
I 6
#include <errno.h>
E 6
D 8
#include <utmp.h>
I 6
#include <unistd.h>
E 8
E 6
#include <stdio.h>
I 6
#include <string.h>
I 8
#include <time.h>
#include <tzfile.h>
#include <unistd.h>
#include <utmp.h>
E 8
E 6

/* Derived from the print routines in the ls(1) source code. */

I 8
static void printlink __P((char *));
static void printtime __P((time_t));

E 8
D 5
extern int errno;

E 5
void
printlong(name, accpath, sb)
	char *name;			/* filename to print */
	char *accpath;			/* current valid path to filename */
	struct stat *sb;		/* stat buffer */
{
D 2
	char *user_from_uid(), *group_from_gid();
E 2
I 2
D 5
	extern int errno;
E 5
D 3
	static char *modep;
	char *user_from_uid(), *group_from_gid(), *strerror();
E 3
I 3
D 6
	char modep[15], *user_from_uid(), *group_from_gid(), *strerror();
E 6
I 6
	char modep[15], *user_from_uid(), *group_from_gid();
E 6
E 3
E 2

D 7
	(void)printf("%6lu %4ld ", sb->st_ino, sb->st_blocks);
E 7
I 7
	(void)printf("%6lu %4qd ", sb->st_ino, sb->st_blocks);
E 7
D 2
	printperms(sb->st_mode);
	(void)printf("%3u %-*s %-*s ", sb->st_nlink, UT_NAMESIZE,
E 2
I 2
D 3
	if (strmode(sb->st_mode, &modep)) {
		(void)fprintf(stderr, "find: %s.\n", strerror(errno));
		exit(1);
	}
E 3
I 3
	(void)strmode(sb->st_mode, modep);
E 3
	(void)printf("%s %3u %-*s %-*s ", modep, sb->st_nlink, UT_NAMESIZE,
E 2
	    user_from_uid(sb->st_uid, 0), UT_NAMESIZE,
	    group_from_gid(sb->st_gid, 0));

	if (S_ISCHR(sb->st_mode) || S_ISBLK(sb->st_mode))
		(void)printf("%3d, %3d ", major(sb->st_rdev),
		    minor(sb->st_rdev));
	else
D 7
		(void)printf("%8ld ", sb->st_size);
E 7
I 7
		(void)printf("%8qd ", sb->st_size);
E 7
	printtime(sb->st_mtime);
	(void)printf("%s", name);
	if (S_ISLNK(sb->st_mode))
		printlink(accpath);
	(void)putchar('\n');
}

I 8
static void
E 8
printtime(ftime)
	time_t ftime;
{
	int i;
	char *longstring, *ctime();
	time_t time();

	longstring = ctime((long *)&ftime);
	for (i = 4; i < 11; ++i)
		(void)putchar(longstring[i]);

#define	SIXMONTHS	((DAYSPERNYEAR / 2) * SECSPERDAY)
	if (ftime + SIXMONTHS > time((time_t *)NULL))
		for (i = 11; i < 16; ++i)
			(void)putchar(longstring[i]);
	else {
		(void)putchar(' ');
		for (i = 20; i < 24; ++i)
			(void)putchar(longstring[i]);
D 2
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
E 2
	}
	(void)putchar(' ');
}

I 8
static void
E 8
printlink(name)
	char *name;
{
	int lnklen;
D 6
	char path[MAXPATHLEN + 1], *strerror();
E 6
I 6
	char path[MAXPATHLEN + 1];
E 6

	if ((lnklen = readlink(name, path, MAXPATHLEN)) == -1) {
D 6
		(void)fprintf(stderr, "\nfind: %s: %s\n", name, strerror(errno));
E 6
I 6
D 8
		(void)fprintf(stderr,
		    "\nfind: %s: %s\n", name, strerror(errno));
E 8
I 8
		warn("%s", name);
E 8
E 6
		return;
	}
	path[lnklen] = '\0';
	(void)printf(" -> %s", path);
}
E 1
