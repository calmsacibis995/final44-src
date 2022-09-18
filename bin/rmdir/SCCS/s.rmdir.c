h40558
s 00002/00002/00058
d D 8.3 94/04/02 10:01:58 pendry 16 15
c add 1994 copyright
e
s 00001/00000/00059
d D 8.2 94/04/01 03:23:02 pendry 15 14
c prettyness police
e
s 00005/00005/00054
d D 8.1 93/05/31 15:11:05 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00055
d D 5.5 93/04/29 14:48:40 bostic 13 12
c usee err/warn from the C library
e
s 00034/00015/00025
d D 5.4 92/06/18 11:49:21 bostic 12 11
c It's an ANSI kind of morning!  (Getopt, too.)
e
s 00001/00011/00039
d D 5.3 90/05/31 20:38:53 bostic 11 10
c new copyright notice
e
s 00025/00014/00025
d D 5.2 88/08/30 15:29:33 bostic 10 9
c from scratch; add Berkeley specific header
e
s 00016/00001/00023
d D 5.1 85/04/30 15:05:14 dist 9 8
c Add copyright
e
s 00001/00001/00023
d D 4.8 85/01/31 14:02:12 serge 8 7
c reasonable error message
e
s 00001/00000/00023
d D 4.7 82/12/19 13:07:28 sam 7 6
c label perror's
e
s 00010/00104/00013
d D 4.6 82/12/19 13:06:05 sam 6 5
c use sys call
e
s 00001/00001/00116
d D 4.5 82/05/07 16:26:37 mckusick 5 4
c update to new fs
e
s 00001/00001/00116
d D 4.4 82/03/31 21:56:04 mckusic 4 3
c change <sys/types.h> to <sys/param.h> for benefit of <ndir.h>
e
s 00010/00010/00107
d D 4.3 82/02/19 17:37:09 mckusic 3 2
c convert to new directory structure
e
s 00017/00005/00100
d D 4.2 80/11/10 22:28:50 bill 2 1
c fixes per presotto
e
s 00105/00000/00000
d D 4.1 80/10/01 17:28:17 bill 1 0
c date and time created 80/10/01 17:28:17 by bill
e
u
U
t
T
I 1
D 9
static char *sccsid = "%W% (Berkeley) %G%";
E 9
I 9
D 12
/*
D 10
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
 * Copyright (c) 1983 The Regents of the University of California.
E 12
I 12
/*-
D 14
 * Copyright (c) 1992 The Regents of the University of California.
E 12
 * All rights reserved.
E 14
I 14
D 16
 * Copyright (c) 1992, 1993
E 16
I 16
 * Copyright (c) 1992, 1993, 1994
E 16
 *	The Regents of the University of California.  All rights reserved.
E 14
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
E 10
 */

#ifndef lint
D 14
char copyright[] =
D 10
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 10
I 10
D 12
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 12
I 12
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
E 12
E 10
 All rights reserved.\n";
E 14
I 14
static char copyright[] =
D 16
"%Z% Copyright (c) 1992, 1993\n\
E 16
I 16
"%Z% Copyright (c) 1992, 1993, 1994\n\
E 16
	The Regents of the University of California.  All rights reserved.\n";
E 14
D 10
#endif not lint
E 10
I 10
#endif /* not lint */
E 10

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 10
#endif not lint
E 10
I 10
#endif /* not lint */
E 10

I 13
#include <err.h>
E 13
E 9
D 12
/*
 * Remove directory
 */
E 12
I 12
#include <errno.h>
D 13
#include <unistd.h>
#include <stdlib.h>
E 13
E 12
D 6

D 4
#include <sys/types.h>
E 4
I 4
#include <sys/param.h>
E 4
D 3
#include <sys/dir.h>
E 3
#include <sys/stat.h>
I 3
D 5
#include <ndir.h>
E 5
I 5
#include <dir.h>
E 6
E 5
E 3
#include <stdio.h>
I 13
#include <stdlib.h>
E 13
I 12
#include <string.h>
I 13
#include <unistd.h>
E 13
E 12

I 12
void usage __P((void));

int
E 12
D 6
int	Errors = 0;
char	*rindex();
char	*strcat();
char	*strcpy();

E 6
D 10
main(argc,argv)
E 10
I 10
main(argc, argv)
E 10
D 6
int argc;
char **argv;
E 6
I 6
	int argc;
D 12
	char **argv;
E 12
I 12
	char *argv[];
E 12
E 6
{
I 6
D 10
	int errors = 0;
E 10
I 10
D 12
	int errors;
E 12
I 12
	int ch, errors;
E 12
E 10
E 6

D 6
	if(argc < 2) {
E 6
I 6
D 12
	if (argc < 2) {
E 6
D 8
		fprintf(stderr, "rmdir: arg count\n");
E 8
I 8
D 10
		fprintf(stderr, "usage: %s directory ...\n", argv[0]);
E 10
I 10
		fprintf(stderr, "usage: rmdir directory ...\n");
E 10
E 8
		exit(1);
	}
D 6
	while(--argc)
		rmdir(*++argv);
	exit(Errors!=0);
}

rmdir(d)
char *d;
{
D 3
	int	fd;
	char	*np, name[500];
E 3
I 3
	char	*np, name[BUFSIZ];
E 3
	struct	stat	st, cst;
D 3
	struct	direct	dir;
E 3
I 3
	struct	direct	*dp;
	DIR	*dirp;
E 3

	strcpy(name, d);
I 2

	/* eat trailing slashes */
	np = &(name[strlen(name)-1]);
	while (*np == '/' && np != name) {
		*np = '\0';
		np--;
	}

	/* point after last slash */
E 2
	if((np = rindex(name, '/')) == NULL)
		np = name;
I 2
	else
		np++;

	if(!strcmp(np, ".") || !strcmp(np, "..")) {
		fprintf(stderr, "rmdir: cannot remove . or ..\n");
		++Errors;
		return;
	}
E 2
	if(stat(name,&st) < 0) {
		fprintf(stderr, "rmdir: %s non-existent\n", name);
		++Errors;
		return;
	}
	if (stat("", &cst) < 0) {
		fprintf(stderr, "rmdir: cannot stat \"\"");
		++Errors;
		exit(1);
	}
	if((st.st_mode & S_IFMT) != S_IFDIR) {
		fprintf(stderr, "rmdir: %s not a directory\n", name);
		++Errors;
		return;
	}
	if(st.st_ino==cst.st_ino &&st.st_dev==cst.st_dev) {
		fprintf(stderr, "rmdir: cannot remove current directory\n");
		++Errors;
		return;
	}
D 3
	if((fd = open(name,0)) < 0) {
E 3
I 3
	if((dirp = opendir(name)) == NULL) {
E 3
		fprintf(stderr, "rmdir: %s unreadable\n", name);
		++Errors;
		return;
	}
D 3
	while(read(fd, (char *)&dir, sizeof dir) == sizeof dir) {
		if(dir.d_ino == 0) continue;
		if(!strcmp(dir.d_name, ".") || !strcmp(dir.d_name, ".."))
E 3
I 3
	while((dp = readdir(dirp)) != NULL) {
		if(dp->d_ino == 0) continue;
		if(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
E 3
			continue;
		fprintf(stderr, "rmdir: %s not empty\n", name);
		++Errors;
D 3
		close(fd);
E 3
I 3
		closedir(dirp);
E 3
		return;
	}
D 3
	close(fd);
E 3
I 3
	closedir(dirp);
E 3
D 2
	if(!strcmp(np, ".") || !strcmp(np, "..")) {
		fprintf(stderr, "rmdir: cannot remove . or ..\n");
		++Errors;
		return;
	}
E 2
	strcat(name, "/.");
	if((access(name, 0)) < 0) {		/* name/. non-existent */
		strcat(name, ".");
		goto unl;
	}
	strcat(name, ".");
	if((access(name, 0)) < 0)		/* name/.. non-existent */
		goto unl2;
	if(access(name, 02)) {
		name[strlen(name)-3] = '\0';
		fprintf(stderr, "rmdir: %s: no permission\n", name);
		++Errors;
		return;
	}
unl:
	unlink(name);	/* unlink name/.. */
unl2:
	name[strlen(name)-1] = '\0';
	unlink(name);	/* unlink name/.  */
	name[strlen(name)-2] = '\0';
	if (unlink(name) < 0) {
		fprintf(stderr, "rmdir: %s not removed\n", name);
		++Errors;
	}
E 6
I 6
D 10
	while (--argc)
		if (rmdir(*++argv) < 0) {
E 10
I 10
	for (errors = 0; *++argv;)
E 12
I 12
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch(ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc == 0)
		usage();

	for (errors = 0; *argv; ++argv)
E 12
		if (rmdir(*argv) < 0) {
E 10
I 7
D 12
			fprintf(stderr, "rmdir: ");
E 7
D 10
			perror(*argv);;
			errors++;
E 10
I 10
			perror(*argv);
E 12
I 12
D 13
			(void)fprintf(stderr,
			    "rmdir: %s: %s\n", *argv, strerror(errno));
E 13
I 13
			warn("%s", *argv);
E 13
E 12
			errors = 1;
E 10
		}
D 10
	exit(errors != 0);
E 10
I 10
	exit(errors);
I 12
}

void
usage()
{
I 15

E 15
	(void)fprintf(stderr, "usage: rmdir directory ...\n");
	exit(1);
E 12
E 10
E 6
}
E 1
