h41437
s 00001/00004/00065
d D 8.3 94/04/01 02:56:17 pendry 13 12
c prettyness police
e
s 00013/00006/00056
d D 8.2 94/03/31 17:11:14 bostic 12 11
c POSIX 1003.2B/D9 symbolic links
e
s 00005/00005/00057
d D 8.1 93/05/31 15:07:35 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00009/00052
d D 5.6 93/04/29 13:21:32 bostic 10 9
c use err/warn from C library
e
s 00029/00002/00032
d D 5.5 91/12/15 16:25:44 bostic 9 8
c add getopt front-end
e
s 00012/00014/00022
d D 5.4 91/02/20 08:33:44 bostic 8 7
c use getcwd(3) malloc functionality to handle paths > 1024
e
s 00001/00011/00035
d D 5.3 90/05/31 20:37:53 bostic 7 6
c new copyright notice
e
s 00015/00004/00031
d D 5.2 88/07/18 15:19:57 bostic 6 5
c rewritten by Sam Leffler; add appropriate copyright
e
s 00016/00001/00019
d D 5.1 85/04/30 15:05:10 dist 5 4
c Add copyright
e
s 00008/00068/00012
d D 4.4 83/01/05 15:40:10 sam 4 3
c use getwd from libc now
e
s 00001/00001/00079
d D 4.3 82/05/07 16:22:08 mckusick 3 2
c update to new fs
e
s 00015/00016/00065
d D 4.2 82/02/12 00:51:23 mckusic 2 1
c convert to use library routines to access directories
e
s 00081/00000/00000
d D 4.1 80/10/01 17:28:00 bill 1 0
c date and time created 80/10/01 17:28:00 by bill
e
u
U
t
T
I 1
D 5
static char *sccsid = "%W% (Berkeley) %G%";
E 5
I 5
/*
D 8
 * Copyright (c) 1980 Regents of the University of California.
E 8
I 8
D 11
 * Copyright (c) 1991 Regents of the University of California.
E 8
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 11
I 11
D 12
 * Copyright (c) 1991, 1993
E 12
I 12
 * Copyright (c) 1991, 1993, 1994
E 12
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
 */

#ifndef lint
D 11
char copyright[] =
D 8
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 8
I 8
"%Z% Copyright (c) 1991 Regents of the University of California.\n\
E 8
 All rights reserved.\n";
E 11
I 11
static char copyright[] =
D 12
"%Z% Copyright (c) 1991, 1993\n\
E 12
I 12
"%Z% Copyright (c) 1991, 1993, 1994\n\
E 12
	The Regents of the University of California.  All rights reserved.\n";
E 11
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6

I 9
D 13
#include <sys/types.h>
E 9
E 5
D 8
/*
 * Print working (current) directory
 */
E 8
I 8
D 10
#include <unistd.h>
I 9
#include <stdlib.h>
E 10
I 10

E 13
#include <err.h>
E 10
E 9
D 13
#include <errno.h>
E 13
E 8
D 4
#include	<stdio.h>
#include	<sys/param.h>
#include	<sys/stat.h>
D 2
#include	<sys/dir.h>
E 2
I 2
D 3
#include	<ndir.h>
E 3
I 3
#include	<dir.h>
E 4
I 4
#include <stdio.h>
I 10
#include <stdlib.h>
E 10
D 8
#include <sys/param.h>
E 8
I 8
D 13
#include <string.h>
E 13
I 10
#include <unistd.h>
E 10
E 8
E 4
E 3
E 2

D 4
char	dot[]	= ".";
char	dotdot[] = "..";
char	name[BUFSIZ];
D 2
int	file;
E 2
I 2
DIR	*file;
E 2
int	off	= -1;
struct	stat	d, dd;
D 2
struct	direct	dir;
E 2
I 2
struct	direct	*dir;
E 4
I 4
D 8
char *getwd();
E 4
E 2

E 8
D 9
main()
E 9
I 9
void usage __P((void));

int
main(argc, argv)
	int argc;
	char *argv[];
E 9
{
I 9
	int ch;
E 9
D 4
	int rdev, rino;
E 4
I 4
D 8
	char pathname[MAXPATHLEN + 1];
E 8
I 8
	char *p;
E 8
E 4

D 4
	stat("/", &d);
	rdev = d.st_dev;
	rino = d.st_ino;
	for (;;) {
		stat(dot, &d);
		if (d.st_ino==rino && d.st_dev==rdev)
			prname();
D 2
		if ((file = open(dotdot,0)) < 0) {
E 2
I 2
		if ((file = opendir(dotdot)) == NULL) {
E 2
			fprintf(stderr,"pwd: cannot open ..\n");
			exit(1);
		}
D 2
		fstat(file, &dd);
E 2
I 2
		fstat(file->dd_fd, &dd);
E 2
		chdir(dotdot);
		if(d.st_dev == dd.st_dev) {
			if(d.st_ino == dd.st_ino)
				prname();
			do
D 2
				if (read(file, (char *)&dir, sizeof(dir)) < sizeof(dir)) {
E 2
I 2
				if ((dir = readdir(file)) == NULL) {
E 2
					fprintf(stderr,"read error in ..\n");
					exit(1);
				}
D 2
			while (dir.d_ino != d.st_ino);
		}
		else do {
				if(read(file, (char *)&dir, sizeof(dir)) < sizeof(dir)) {
E 2
I 2
			while (dir->d_ino != d.st_ino);
		} else
			do {
				if ((dir = readdir(file)) == NULL) {
E 2
					fprintf(stderr,"read error in ..\n");
					exit(1);
				}
D 2
				stat(dir.d_name, &dd);
E 2
I 2
				stat(dir->d_name, &dd);
E 2
			} while(dd.st_ino != d.st_ino || dd.st_dev != d.st_dev);
D 2
		close(file);
E 2
I 2
		closedir(file);
E 2
		cat();
E 4
I 4
D 8
	if (getwd(pathname) == NULL) {
		fprintf(stderr, "pwd: %s\n", pathname);
		exit(1);
E 8
I 8
D 9
	p = getcwd((char *)NULL, 0);
E 9
I 9
D 12
	while ((ch = getopt(argc, argv, "")) != EOF)
E 12
I 12
	/*
	 * Flags for pwd are a bit strange.  The POSIX 1003.2B/D9 document
	 * has an optional -P flag for physical, which is what this program
	 * will produce by default.  The logical flag, -L, should fail, as
	 * there's no way to display a logical path after forking.  We don't
	 * document either flag, only adding -P for future portability.
	 */
	while ((ch = getopt(argc, argv, "P")) != EOF)
E 12
D 10
		switch(ch) {
E 10
I 10
		switch (ch) {
I 12
		case 'P':
			break;
E 12
E 10
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 0)
		usage();

D 10
	p = getcwd(NULL, 0);
E 9
	if (p) {
		(void)printf("%s\n", p);
		exit(0);
E 10
I 10
D 12
	if ((p = getcwd(NULL, 0)) == NULL) {
E 12
I 12
	if ((p = getcwd(NULL, 0)) == NULL)
E 12
		err(1, NULL);
D 12
		exit(1);
E 10
E 8
E 4
	}
E 12
D 4
}

prname()
{
	write(1, "/", 1);
	if (off<0)
		off = 0;
	name[off] = '\n';
	write(1, name, off+1);
E 4
I 4
D 8
	printf("%s\n", pathname);
E 4
	exit(0);
E 8
I 8
D 10
	(void)fprintf(stderr, "pwd: %s\n", strerror(errno));
I 9
	exit(1);
E 10
I 10
	(void)printf("%s\n", p);
	exit(0);
E 10
}

void
usage()
{
I 13

E 13
	(void)fprintf(stderr, "usage: pwd\n");
E 9
	exit(1);
E 8
D 4
}

cat()
{
	register i, j;

D 2
	i = -1;
	while (dir.d_name[++i] != 0);
	if ((off+i+2) > BUFSIZ-1)
E 2
I 2
	i = dir->d_namlen;
	if ((off + dir->d_namlen + 2) > BUFSIZ-1)
E 2
		prname();
	for(j=off+1; j>=0; --j)
		name[j+i+1] = name[j];
	off=i+off+1;
	name[i] = '/';
	for(--i; i>=0; --i)
D 2
		name[i] = dir.d_name[i];
E 2
I 2
		name[i] = dir->d_name[i];
E 4
E 2
}
E 1
