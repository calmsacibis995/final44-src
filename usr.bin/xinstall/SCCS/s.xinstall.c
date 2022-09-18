h35017
s 00005/00005/00327
d D 8.1 93/07/21 16:41:58 bostic 39 38
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00004/00326
d D 5.33 93/07/21 16:41:50 bostic 38 36
c turn off super-user changeable flags too!
e
s 00005/00005/00325
d R 8.1 93/06/06 22:28:52 bostic 37 36
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00326
d D 5.32 93/04/20 21:53:06 hibler 36 35
c fix a typo and init st_flags for devnull case
e
s 00005/00005/00323
d D 5.31 93/03/11 14:51:41 sklower 35 34
c APPEND, NODUMP, IMMUTABLE -> UF_*
e
s 00053/00021/00275
d D 5.30 93/03/03 20:34:25 bostic 34 33
c add uappend, uchange, sappend, schange flags as -f option to install
e
s 00008/00004/00288
d D 5.29 92/12/08 17:26:03 bostic 33 32
c print out type of error
e
s 00002/00002/00290
d D 5.28 92/06/29 19:02:05 bostic 32 31
c turn off the NODUMP flag
e
s 00029/00012/00263
d D 5.27 92/06/28 15:06:52 bostic 31 30
c mmap and write files less than 8M
e
s 00008/00008/00267
d D 5.26 92/06/28 14:53:01 bostic 30 29
c delete extra newlines
e
s 00115/00101/00160
d D 5.25 92/06/28 14:51:51 bostic 29 28
c preserve file flags across install; general ANSI C and style cleanup
e
s 00017/00043/00244
d D 5.24 90/07/01 20:00:31 bostic 28 27
c remove genbuild stuff
e
s 00001/00011/00286
d D 5.23 90/06/01 16:12:34 bostic 27 26
c new copyright notice
e
s 00003/00002/00294
d D 5.22 90/04/16 14:06:43 bostic 26 25
c new version of get/setmode
e
s 00043/00017/00253
d D 5.21 90/03/11 10:28:31 mckusick 25 24
c check first for sources in build area, then in current directory
e
s 00002/00003/00268
d D 5.20 90/03/11 10:24:40 bostic 24 23
c fix setting of mode (checkin for bostic by mckusick)
e
s 00001/00000/00270
d D 5.19 89/12/31 17:57:54 bostic 23 22
c declare setmode(3)
e
s 00006/00015/00264
d D 5.18 89/12/31 17:00:27 bostic 22 21
c add symbolic modes using setmode(3)
e
s 00002/00001/00277
d D 5.17 89/12/30 12:42:26 bostic 21 20
c stupid mistake in execl
e
s 00064/00083/00214
d D 5.16 89/12/09 14:14:25 bostic 20 19
c change to use strip(1) rather than stripping during the copy; Eric points
c out that this is more portable and will more easily support multiple
c binary types.
e
s 00005/00005/00292
d D 5.15 89/09/04 17:12:59 bostic 19 18
c do the chown first; under VFS chown loses setid bits
e
s 00009/00011/00288
d D 5.14 89/05/10 22:32:06 bostic 18 17
c cleanup, add pathnames.h
e
s 00004/00012/00295
d D 5.13 88/09/22 16:47:50 bostic 17 16
c minor cleanups, don't static routines
e
s 00026/00026/00281
d D 5.12 88/07/06 17:02:08 bostic 16 15
c do declarations in KNF
e
s 00010/00005/00297
d D 5.11 88/06/29 21:54:29 bostic 15 14
c install approved copyright notice
e
s 00042/00048/00260
d D 5.10 87/12/04 14:34:15 bostic 14 13
c if rename successful wasn't setting owner/mode; removed call to rename,
c redid logic to be a little more straight forward.  Berkeley headers.
e
s 00003/00003/00305
d D 5.9 87/11/02 09:04:37 bostic 13 12
c fix st_mode comparisons
e
s 00015/00013/00293
d D 5.8 87/09/10 13:08:28 bostic 12 10
c install shouldn't know about errno/sys_errlst[];
e
s 00001/00001/00305
d D 5.7 87/08/09 12:44:08 bostic 10 8
c rindex takes char pointer, not char
e
s 00003/00003/00303
d R 5.7 87/08/09 12:43:28 bostic 9 8
c rindex gets char pointer, not char
e
s 00012/00010/00294
d D 5.6 87/08/03 16:57:43 bostic 8 6
c no more default owner/group, use whoever running it; fix bug 
c where didn't set mode if successful rename; fix lseek argument order
e
s 00010/00009/00295
d R 5.6 87/08/03 16:53:41 bostic 7 6
c no more default owner/group, use whoever is running it unless 
c otherwise specified; fix bug where didn't set mode if successful rename
e
s 00127/00088/00177
d D 5.5 87/07/31 10:55:21 bostic 6 4
c rewritten to handle multiple files to a directory; fix so can 
c strip already stripped binaries
e
s 00124/00088/00177
d R 5.5 87/07/30 21:05:41 bostic 5 4
c rewrote to handle multiple files to a directory
e
s 00004/00002/00261
d D 5.4 87/07/25 10:15:05 bostic 4 3
c do it right, not according to K&R...
e
s 00014/00007/00249
d D 5.3 87/07/23 06:43:39 bostic 3 2
c check for special file target, allow "/dev/null" install
e
s 00046/00038/00210
d D 5.2 87/07/17 21:05:57 bostic 2 1
c provide "bad" exit routine; do all processing possible before 
c actually opening target; minor cleanups
e
s 00248/00000/00000
d D 5.1 87/07/17 14:52:06 bostic 1 0
c date and time created 87/07/17 14:52:06 by bostic
e
u
U
t
T
I 1
/*
D 39
 * Copyright (c) 1987 Regents of the University of California.
D 14
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
 * All rights reserved.
E 39
I 39
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 39
 *
D 27
 * Redistribution and use in source and binary forms are permitted
D 15
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 15
I 15
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
E 27
I 27
 * %sccs.include.redist.c%
E 27
E 15
E 14
 */

#ifndef lint
D 39
char copyright[] =
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
 All rights reserved.\n";
E 39
I 39
static char copyright[] =
"%Z% Copyright (c) 1987, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 39
D 14
#endif not lint
E 14
I 14
#endif /* not lint */
E 14

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 14
#endif not lint
E 14
I 14
#endif /* not lint */
E 14

#include <sys/param.h>
I 29
#include <sys/wait.h>
I 31
#include <sys/mman.h>
E 31
E 29
#include <sys/stat.h>
D 29
#include <sys/file.h>
E 29
I 29

I 34
#include <ctype.h>
#include <errno.h>
E 34
#include <fcntl.h>
E 29
D 20
#include <a.out.h>
E 20
#include <grp.h>
I 34
#include <paths.h>
E 34
#include <pwd.h>
I 29
D 34
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
E 34
E 29
#include <stdio.h>
D 34
#include <ctype.h>
E 34
I 34
#include <stdlib.h>
E 34
I 29
#include <string.h>
E 29
I 18
D 34
#include <paths.h>
E 34
I 34
#include <unistd.h>

E 34
I 20
#include "pathnames.h"
E 20
E 18

D 14
#define	YES		1			/* yes/true */
I 6
#define	NO		0			/* no/false */
E 14
I 14
D 18
#define	YES	1			/* yes/true */
#define	NO	0			/* no/false */
E 14
E 6
D 2
#define	DEF_GROUP	"root"			/* default group */
#define	DEF_OWNER	"staff"			/* default owner */
E 2
I 2
D 8
#define	DEF_GROUP	"staff"			/* default group */
#define	DEF_OWNER	"root"			/* default owner */
E 8
E 2

E 18
D 6
static int	docopy, dostrip,
		mode = 0755;
static char	*group = DEF_GROUP,
D 2
		*owner = DEF_OWNER;
E 2
I 2
		*owner = DEF_OWNER,
		*path;
E 6
I 4
D 12
extern int	errno;
extern char	*sys_errlist[];
E 12
I 12
D 20
#define	PERROR(head, msg) { \
	fputs(head, stderr); \
	perror(msg); \
}
E 12
E 4
E 2

E 20
I 6
D 17
static struct passwd	*pp;
static struct group	*gp;
static int	docopy, dostrip,
		mode = 0755;
D 8
static char	pathbuf[MAXPATHLEN];
E 8
I 8
static char	*group, *owner,
		pathbuf[MAXPATHLEN];
E 17
I 17
D 29
static struct passwd *pp;
static struct group *gp;
static int docopy, dostrip, mode = 0755;
static char *group, *owner, pathbuf[MAXPATHLEN];
E 29
I 29
struct passwd *pp;
struct group *gp;
int docopy, dostrip;
int mode = S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH;
char *group, *owner, pathbuf[MAXPATHLEN];
E 29
E 17
E 8

I 34
#define	DIRECTORY	0x01		/* Tell install it's a directory. */
#define	SETFLAGS	0x02		/* Tell install to set flags. */

E 34
I 29
D 31
void	copy __P((int, char *, int, char *));
E 31
I 31
void	copy __P((int, char *, int, char *, off_t));
E 31
void	err __P((const char *, ...));
D 34
void	install __P((char *, char *, int));
E 34
I 34
void	install __P((char *, char *, u_long, u_int));
u_long	string_to_flags __P((char **, u_long *, u_long *));
E 34
void	strip __P((char *));
void	usage __P((void));

int
E 29
E 6
main(argc, argv)
D 16
	int	argc;
	char	**argv;
E 16
I 16
	int argc;
D 29
	char **argv;
E 29
I 29
	char *argv[];
E 29
E 16
{
D 4
	extern char	*optarg, *sys_errlist[];
	extern int	optind, errno;
E 4
I 4
D 16
	extern char	*optarg;
	extern int	optind;
E 4
D 6
	register int	to_fd;
E 6
	struct stat	from_sb, to_sb;
D 6
	struct passwd	*pp;
	struct group	*gp;
D 3
	int	ch;
E 3
I 3
	int	ch, devnull;
E 3
D 2
	char	*path, pbuf[MAXPATHLEN];
E 2
I 2
	char	pbuf[MAXPATHLEN];
E 6
I 6
	int	ch, no_target;
D 8
	char	*group, *owner, *to_name;
E 8
I 8
	char	*to_name;
E 16
I 16
D 29
	extern char *optarg;
	extern int optind;
E 29
	struct stat from_sb, to_sb;
I 26
D 29
	mode_t *set, *setmode();
E 29
I 29
	mode_t *set;
I 34
	u_long fset;
	u_int iflags;
E 34
E 29
E 26
	int ch, no_target;
D 34
	char *to_name;
E 34
I 34
	char *flags, *to_name;
E 34
I 23
D 24
	mode_t setmode();
E 24
E 23
E 16
E 8
E 6
E 2

I 6
D 8
	group = DEF_GROUP;
	owner = DEF_OWNER;
E 8
E 6
D 34
	while ((ch = getopt(argc, argv, "cg:m:o:s")) != EOF)
E 34
I 34
	iflags = 0;
	while ((ch = getopt(argc, argv, "cf:g:m:o:s")) != EOF)
E 34
		switch((char)ch) {
		case 'c':
D 18
			docopy = YES;
E 18
I 18
			docopy = 1;
E 18
			break;
I 34
		case 'f':
			flags = optarg;
			if (string_to_flags(&flags, &fset, NULL))
				err("%s: invalid flag", flags);
			iflags |= SETFLAGS;
			break;
E 34
		case 'g':
			group = optarg;
			break;
		case 'm':
D 22
			mode = atoo(optarg);
E 22
I 22
D 24
			mode = setmode(optarg, (mode_t)0, 0);
			if (mode == (mode_t)-1) {
E 24
I 24
D 26
			if (setmode(optarg) == -1) {
E 26
I 26
D 29
			if (!(set = setmode(optarg))) {
E 26
E 24
				(void)fprintf(stderr,
				    "install: invalid file mode.\n");
				exit(1);
			}
E 29
I 29
			if (!(set = setmode(optarg)))
D 30
				err("%s: invalid file mode\n", optarg);
E 30
I 30
				err("%s: invalid file mode", optarg);
E 30
E 29
I 24
D 26
			mode = getmode(0);
E 26
I 26
			mode = getmode(set, 0);
E 26
E 24
E 22
			break;
		case 'o':
			owner = optarg;
			break;
		case 's':
D 18
			dostrip = YES;
E 18
I 18
			dostrip = 1;
E 18
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
D 6
	if (argc != 2)
E 6
I 6
	if (argc < 2)
E 6
		usage();

I 2
	/* get group and owner id's */
D 8
	if (!(gp = getgrnam(group))) {
E 8
I 8
D 29
	if (group && !(gp = getgrnam(group))) {
E 8
		fprintf(stderr, "install: unknown group %s.\n", group);
		exit(1);
	}
D 8
	if (!(pp = getpwnam(owner))) {
E 8
I 8
	if (owner && !(pp = getpwnam(owner))) {
E 8
		fprintf(stderr, "install: unknown user %s.\n", owner);
		exit(1);
	}
E 29
I 29
	if (group && !(gp = getgrnam(group)))
D 30
		err("unknown group %s\n", group);
E 30
I 30
		err("unknown group %s", group);
E 30
	if (owner && !(pp = getpwnam(owner)))
D 30
		err("unknown user %s\n", owner);
E 30
I 30
		err("unknown user %s", owner);
E 30
E 29

E 2
D 6
	/* check source */
	if (stat(argv[0], &from_sb)) {
		fprintf(stderr, "install: fstat: %s: %s\n", argv[0], sys_errlist[errno]);
		exit(1);
E 6
I 6
	no_target = stat(to_name = argv[argc - 1], &to_sb);
D 13
	if (!no_target && to_sb.st_mode & S_IFDIR) {
E 13
I 13
	if (!no_target && (to_sb.st_mode & S_IFMT) == S_IFDIR) {
E 13
D 25
		for (; *argv != to_name; ++argv)
E 25
I 25
D 28
		for (; *argv != to_name; ++argv) {
			if (stat_from(argv, &from_sb)) {
				fprintf(stderr, "install: can't find %s.\n",
				    *argv);
				exit(1);
			}
			if ((from_sb.st_mode & S_IFMT) != S_IFREG) {
				fprintf(stderr,
				    "install: %s isn't a regular file.\n",
				    *argv);
				exit(1);
			}
E 28
I 28
		for (; *argv != to_name; ++argv)
E 28
E 25
D 18
			install(*argv, to_name, YES);
E 18
I 18
D 34
			install(*argv, to_name, 1);
E 34
I 34
			install(*argv, to_name, fset, iflags | DIRECTORY);
E 34
I 25
D 28
		}
E 28
E 25
E 18
		exit(0);
E 6
	}
D 3
	if (!(from_sb.st_mode & S_IFREG)) {
E 3
I 3
D 6
	/* special case for removing files */
	devnull = !strcmp(argv[0], "/dev/null");
	if (!devnull && !(from_sb.st_mode & S_IFREG)) {
E 3
		fprintf(stderr, "install: %s isn't a regular file.\n", argv[0]);
		exit(1);
	}
E 6

D 6
	/* build target path, find out if target is same as source */
	if (!stat(path = argv[1], &to_sb)) {
		if (to_sb.st_mode & S_IFDIR) {
D 3
			(void)sprintf(path = pbuf, "%s/%s", argv[1], argv[0]);
E 3
I 3
			char	*C, *rindex();
E 6
I 6
	/* can't do file1 file2 directory/file */
	if (argc != 2)
		usage();
E 6

I 25
D 28
	if (stat_from(argv, &from_sb)) {
		fprintf(stderr, "install: can't find %s.\n", *argv);
		exit(1);
	}
E 28
E 25
D 6
			(void)sprintf(path = pbuf, "%s/%s", argv[1], (C = rindex(argv[0], '/')) ? ++C : argv[0]);
E 3
			if (stat(path, &to_sb))
				goto nocompare;
E 6
I 6
	if (!no_target) {
I 28
D 29
		if (stat(*argv, &from_sb)) {
			fprintf(stderr, "install: can't find %s.\n", *argv);
			exit(1);
		}
E 28
D 25
		if (stat(*argv, &from_sb)) {
			fprintf(stderr, "install: can't find %s.\n", *argv);
			exit(1);
E 6
D 3
			if (to_sb.st_mode & S_IFDIR) {
				fprintf(stderr, "install: %s is a directory.\n", path);
				exit(1);
			}
E 3
		}
E 25
I 3
D 13
		if (!(to_sb.st_mode & S_IFREG)) {
E 13
I 13
		if ((to_sb.st_mode & S_IFMT) != S_IFREG) {
E 13
D 6
			fprintf(stderr, "install: %s isn't a regular file.\n", path);
E 6
I 6
D 25
			fprintf(stderr, "install: %s isn't a regular file.\n", to_name);
E 25
I 25
D 28
			fprintf(stderr, "install: %s isn't a regular file.\n",
			    to_name);
E 28
I 28
			fprintf(stderr, "install: %s isn't a regular file.\n", to_name);
E 28
E 25
E 6
			exit(1);
		}
E 3
D 25
		if (to_sb.st_dev == from_sb.st_dev && to_sb.st_ino == from_sb.st_ino) {
D 6
			fprintf(stderr, "install: %s and %s are the same file.\n", argv[0], path);
E 6
I 6
			fprintf(stderr, "install: %s and %s are the same file.\n", *argv, to_name);
E 25
I 25
D 28
		if (to_sb.st_dev == from_sb.st_dev &&
		    to_sb.st_ino == from_sb.st_ino) {
			fprintf(stderr,
			    "install: %s and %s are the same file.\n",
			    *argv, to_name);
E 28
I 28
		if (to_sb.st_dev == from_sb.st_dev && to_sb.st_ino == from_sb.st_ino) {
			fprintf(stderr, "install: %s and %s are the same file.\n", *argv, to_name);
E 28
E 25
E 6
			exit(1);
		}
E 29
I 29
		if (stat(*argv, &from_sb))
D 30
			err("%s: %s\n", *argv, strerror(errno));
E 30
I 30
			err("%s: %s", *argv, strerror(errno));
E 30
		if (!S_ISREG(to_sb.st_mode))
D 30
			err("%s: %s\n", to_name, strerror(EFTYPE));
E 30
I 30
			err("%s: %s", to_name, strerror(EFTYPE));
E 30
		if (to_sb.st_dev == from_sb.st_dev &&
		    to_sb.st_ino == from_sb.st_ino)
D 30
			err("%s and %s are the same file\n", *argv, to_name);
E 30
I 30
			err("%s and %s are the same file", *argv, to_name);
E 30
E 29
D 34
		/* unlink now... avoid ETXTBSY errors later */
E 34
I 34
		/*
		 * Unlink now... avoid ETXTBSY errors later.  Try and turn
		 * off the append/immutable bits -- if we fail, go ahead,
		 * it might work.
		 */
D 35
		if (to_sb.st_mode & (IMMUTABLE | APPEND))
E 35
I 35
D 36
		if (to_sb.st_mode & (UF_IMMUTABLE | UF_APPEND))
E 36
I 36
D 38
		if (to_sb.st_flags & (UF_IMMUTABLE | UF_APPEND))
E 38
I 38
#define	NOCHANGEBITS	(UF_IMMUTABLE | UF_APPEND | SF_IMMUTABLE | SF_APPEND)
		if (to_sb.st_flags & NOCHANGEBITS)
E 38
E 36
E 35
			(void)chflags(to_name,
D 35
			    to_sb.st_flags & ~(APPEND | IMMUTABLE));
E 35
I 35
D 38
			    to_sb.st_flags & ~(UF_APPEND | UF_IMMUTABLE));
E 38
I 38
			    to_sb.st_flags & ~(NOCHANGEBITS));
E 38
E 35
E 34
D 6
		(void)unlink(path);
E 6
I 6
		(void)unlink(to_name);
E 6
	}
I 6
D 18
	install(*argv, to_name, NO);
E 18
I 18
D 34
	install(*argv, to_name, 0);
E 34
I 34
	install(*argv, to_name, fset, iflags);
E 34
E 18
	exit(0);
}
E 6

D 6
nocompare:
D 2
	/* get group and owner id's */
	if (!(gp = getgrnam(group))) {
		fprintf(stderr, "install: unknown group %s.\n", group);
		exit(1);
	}
	if (!(pp = getpwnam(owner))) {
		fprintf(stderr, "install: unknown user %s.\n", owner);
		exit(1);
	}

E 2
	/* open target, set mode, owner, group */
	if ((to_fd = open(path, O_CREAT|O_WRONLY|O_TRUNC, 0)) < 0) {
		fprintf(stderr, "install: %s: %s\n", path, sys_errlist[errno]);
E 6
I 6
/*
 * install --
 *	build a path name and install the file
 */
I 29
void
E 29
D 17
static
E 17
D 34
install(from_name, to_name, isdir)
E 34
I 34
install(from_name, to_name, fset, flags)
E 34
D 16
	char	*from_name, *to_name;
	int	isdir;
E 16
I 16
	char *from_name, *to_name;
D 34
	int isdir;
E 34
I 34
	u_long fset;
	u_int flags;
E 34
E 16
{
I 28
D 34
	struct stat from_sb;
E 34
I 34
	struct stat from_sb, to_sb;
E 34
E 28
D 16
	struct stat	from_sb;
	int	devnull, from_fd, to_fd;
D 14
	char	*C,
		*rindex();
E 14
I 14
	char	*C, *rindex();
E 16
I 16
D 25
	struct stat from_sb;
E 25
D 29
	int devnull, from_fd, to_fd;
	char *C, *rindex();
E 29
I 29
	int devnull, from_fd, to_fd, serrno;
	char *p;
E 29
E 16
E 14

D 14
	if ((from_fd = open(from_name, O_RDONLY, 0)) < 0) {
D 12
		fprintf(stderr, "install: open: %s: %s\n", from_name, sys_errlist[errno]);
E 12
I 12
		PERROR("install: open: ", from_name);
E 12
E 6
		exit(1);
	}
I 6

E 14
D 18
	/* if try to install "/dev/null" to a directory, fails */
D 14
	devnull = isdir ? NO : !strcmp(from_name, "/dev/null");
	if (!devnull) {
		if (fstat(from_fd, &from_sb)) {
E 14
I 14
	if (isdir || strcmp(from_name, "/dev/null")) {
E 18
I 18
D 29
	/* if try to install NULL file to a directory, fails */
E 29
I 29
	/* If try to install NULL file to a directory, fails. */
E 29
D 34
	if (isdir || strcmp(from_name, _PATH_DEVNULL)) {
E 34
I 34
	if (flags & DIRECTORY || strcmp(from_name, _PATH_DEVNULL)) {
E 34
I 28
D 29
		if (stat(from_name, &from_sb)) {
			fprintf(stderr, "install: can't find %s.\n", from_name);
			exit(1);
		}
		if ((from_sb.st_mode & S_IFMT) != S_IFREG) {
			fprintf(stderr, "install: %s isn't a regular file.\n", from_name);
			exit(1);
		}
E 28
E 18
D 25
		if (stat(from_name, &from_sb)) {
E 14
			fprintf(stderr, "install: can't find %s.\n", from_name);
			exit(1);
		}
D 13
		if (!(from_sb.st_mode & S_IFREG)) {
E 13
I 13
		if ((from_sb.st_mode & S_IFMT) != S_IFREG) {
E 13
			fprintf(stderr, "install: %s isn't a regular file.\n", from_name);
			exit(1);
		}
E 25
I 14
		/* build the target path */
E 29
I 29
		if (stat(from_name, &from_sb))
D 30
			err("%s: %s\n", from_name, strerror(errno));
E 30
I 30
			err("%s: %s", from_name, strerror(errno));
E 30
		if (!S_ISREG(from_sb.st_mode))
D 30
			err("%s: %s\n", from_name, strerror(EFTYPE));
E 30
I 30
			err("%s: %s", from_name, strerror(EFTYPE));
E 30
		/* Build the target path. */
E 29
D 34
		if (isdir) {
E 34
I 34
		if (flags & DIRECTORY) {
E 34
D 29
			(void)sprintf(pathbuf, "%s/%s", to_name, (C = rindex(from_name, '/')) ? ++C : from_name);
E 29
I 29
			(void)snprintf(pathbuf, sizeof(pathbuf), "%s/%s",
			    to_name,
			    (p = rindex(from_name, '/')) ? ++p : from_name);
E 29
			to_name = pathbuf;
		}
D 18
		devnull = NO;
E 18
I 18
		devnull = 0;
E 18
E 14
D 20
	}
I 14
	else
E 20
I 20
D 36
	} else
E 36
I 36
	} else {
		from_sb.st_flags = 0;	/* XXX */
E 36
E 20
D 18
		devnull = YES;
E 18
I 18
		devnull = 1;
I 36
	}
E 36
E 18
E 14

D 14
	/* build the path */
	if (isdir) {
D 10
		(void)sprintf(pathbuf, "%s/%s", to_name, (C = rindex(*from_name, '/')) ? ++C : from_name);
E 10
I 10
		(void)sprintf(pathbuf, "%s/%s", to_name, (C = rindex(from_name, '/')) ? ++C : from_name);
E 10
		to_name = pathbuf;
	}

E 14
D 29
	/* unlink now... avoid ETXTBSY errors later */
E 29
I 29
D 34
	/* Unlink now... avoid ETXTBSY errors later. */
E 34
I 34
	/*
	 * Unlink now... avoid ETXTBSY errors later.  Try and turn
	 * off the append/immutable bits -- if we fail, go ahead,
	 * it might work.
	 */
D 35
	if (stat(to_name, &to_sb) == 0 && to_sb.st_flags & (APPEND | IMMUTABLE))
		(void)chflags(to_name, to_sb.st_flags & ~(APPEND | IMMUTABLE));
E 35
I 35
D 38
	if (stat(to_name, &to_sb) == 0 && to_sb.st_flags & (UF_APPEND | UF_IMMUTABLE))
		(void)chflags(to_name, to_sb.st_flags & ~(UF_APPEND | UF_IMMUTABLE));
E 38
I 38
	if (stat(to_name, &to_sb) == 0 &&
	    to_sb.st_flags & (NOCHANGEBITS))
		(void)chflags(to_name, to_sb.st_flags & ~(NOCHANGEBITS));
E 38
E 35
E 34
E 29
	(void)unlink(to_name);

D 14
	/* open target, set owner, group, mode */
E 14
I 14
D 29
	/* create target */
E 14
D 20
	if ((to_fd = open(to_name, O_CREAT|O_WRONLY|O_TRUNC, 0)) < 0) {
D 12
		fprintf(stderr, "install: %s: %s\n", to_name, sys_errlist[errno]);
E 12
I 12
		PERROR("install: ", to_name);
E 20
I 20
	if ((to_fd = open(to_name, O_CREAT|O_WRONLY|O_TRUNC, 0600)) < 0) {
		error(to_name);
E 20
E 12
		exit(1);
	}
E 29
I 29
	/* Create target. */
D 31
	if ((to_fd = open(to_name, O_CREAT|O_WRONLY|O_TRUNC, 0600)) < 0)
E 31
I 31
	if ((to_fd = open(to_name,
D 34
	    O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR)) < 0)
E 34
I 34
	    O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
E 34
E 31
		err("%s: %s", to_name, strerror(errno));
E 29
I 14
	if (!devnull) {
		if ((from_fd = open(from_name, O_RDONLY, 0)) < 0) {
			(void)unlink(to_name);
D 20
			PERROR("install: open: ", from_name);
E 20
I 20
D 29
			error(from_name);
E 20
			exit(1);
E 29
I 29
			err("%s: %s", from_name, strerror(errno));
E 29
		}
D 20
		if (dostrip)
			strip(from_fd, from_name, to_fd, to_name);
		else
			copy(from_fd, from_name, to_fd, to_name);
E 20
I 20
D 31
		copy(from_fd, from_name, to_fd, to_name);
E 31
I 31
		copy(from_fd, from_name, to_fd, to_name, from_sb.st_size);
E 31
E 20
		(void)close(from_fd);
D 20
		if (!docopy)
			(void)unlink(from_name);
E 20
	}
D 19
	/* set owner, group, mode for target */
E 14
E 6
	if (fchmod(to_fd, mode)) {
D 6
		fprintf(stderr, "install: fchmod: %s: %s\n", path, sys_errlist[errno]);
E 6
I 6
D 12
		fprintf(stderr, "install: fchmod: %s: %s\n", to_name, sys_errlist[errno]);
E 12
I 12
		PERROR("install: fchmod: ", to_name);
E 12
E 6
D 2
		(void)unlink(path);
		exit(1);
E 2
I 2
		bad();
E 2
	}
E 19
D 8
	if (fchown(to_fd, pp->pw_uid, gp->gr_gid)) {
E 8
I 8
D 14
	if ((group || owner) && fchown(to_fd, owner ? pp->pw_uid : -1, group ? gp->gr_gid : -1)) {
E 14
I 14
D 20
	if ((group || owner) && fchown(to_fd, owner ? pp->pw_uid : -1,
	    group ? gp->gr_gid : -1)) {
E 14
E 8
D 6
		fprintf(stderr, "install: fchown: %s: %s\n", path, sys_errlist[errno]);
E 6
I 6
D 12
		fprintf(stderr, "install: fchown: %s: %s\n", to_name, sys_errlist[errno]);
E 12
I 12
		PERROR("install: fchown: ", to_name);
I 19
		bad();
E 20
I 20
	if (dostrip)
		strip(to_name);
	/*
D 29
	 * set owner, group, mode for target; do the chown first,
E 29
I 29
	 * Set owner, group, mode for target; do the chown first,
E 29
	 * chown may lose the setuid bits.
	 */
	if ((group || owner) &&
D 33
	    fchown(to_fd, owner ? pp->pw_uid : -1, group ? gp->gr_gid : -1) ||
	    fchmod(to_fd, mode)) {
E 33
I 33
	    fchown(to_fd, owner ? pp->pw_uid : -1, group ? gp->gr_gid : -1)) {
E 33
D 29
		error(to_name);
		bad(to_name);
E 29
I 29
		serrno = errno;
		(void)unlink(to_name);
D 33
		err("%s: %s", to_name, strerror(serrno));
E 33
I 33
		err("%s: chown/chgrp: %s", to_name, strerror(serrno));
E 33
E 29
E 20
	}
I 33
	if (fchmod(to_fd, mode)) {
		serrno = errno;
		(void)unlink(to_name);
		err("%s: chmod: %s", to_name, strerror(serrno));
	}
E 33
D 20
	/* set owner, group, mode for target */
	if (fchmod(to_fd, mode)) {
		PERROR("install: fchmod: ", to_name);
E 19
E 12
E 6
D 2
		(void)unlink(path);
		exit(1);
E 2
I 2
		bad();
E 2
	}
E 20
I 3
D 14

D 6
	if (devnull)
		exit(0);
E 6
I 6
	if (devnull) {
		(void)close(to_fd);
		return;
	}
E 6
E 3

	if (dostrip) {
D 6
		strip(to_fd, argv[0], path);
E 6
I 6
		strip(from_fd, from_name, to_fd, to_name);
E 6
		if (docopy)
D 6
			exit(0);
E 6
I 6
			goto done;
E 6
	}
	else if (docopy) {
D 6
		copy(argv[0], to_fd, path);
		exit(0);
E 6
I 6
		copy(from_fd, from_name, to_fd, to_name);
		goto done;
E 6
	}
D 6
	else if (rename(argv[0], path))
		copy(argv[0], to_fd, path);
	(void)unlink(argv[0]);
	exit(0);
}
E 6
I 6
	else if (rename(from_name, to_name))
		copy(from_fd, from_name, to_fd, to_name);
I 8
	else if (chmod(to_name, mode)) {
D 12
		fprintf(stderr, "install: chmod: %s: %s\n", to_name, sys_errlist[errno]);
E 12
I 12
		PERROR("install: chmod: ", to_name);
E 12
		bad();
	}
E 8
	(void)unlink(from_name);
E 6

D 6
/*
 * copy --
 *	copy from one file to another
 */
static
copy(from_name, to_fd, to_name)
	register int	to_fd;
	char	*from_name, *to_name;
{
	register int	n, from_fd;
	char	buf[MAXBSIZE];

	if ((from_fd = open(from_name, O_RDONLY, 0)) < 0) {
		fprintf(stderr, "install: open: %s: %s\n", from_name, sys_errlist[errno]);
D 2
		(void)unlink(to_name);
		exit(1);
E 2
I 2
		bad();
E 2
	}
	while ((n = read(from_fd, buf, sizeof(buf))) > 0)
		if (write(to_fd, buf, n) != n) {
			fprintf(stderr, "install: write: %s: %s\n", to_name, sys_errlist[errno]);
D 2
			(void)unlink(to_name);
E 2
I 2
			bad();
E 2
		}
	if (n == -1) {
D 2
		fprintf(stderr, "install: read: %s: %s\n", to_name, sys_errlist[errno]);
		(void)unlink(to_name);
E 2
I 2
		fprintf(stderr, "install: read: %s: %s\n", from_name, sys_errlist[errno]);
		bad();
E 2
	}
E 6
I 6
done:	(void)close(from_fd);
E 14
D 29
	(void)close(to_fd);
E 6
D 20
}

/*
 * strip --
 *	copy file, strip(1)'ing it at the same time
 */
D 17
static
E 17
D 6
strip(to_fd, from_name, to_name)
	register int	to_fd;
E 6
I 6
strip(from_fd, from_name, to_fd, to_name)
D 16
	register int	from_fd, to_fd;
E 6
	char	*from_name, *to_name;
E 16
I 16
	register int from_fd, to_fd;
	char *from_name, *to_name;
E 16
{
D 16
	typedef struct exec	EXEC;
	register long	size;
D 6
	register int	n, from_fd;
E 6
I 6
	register int	n;
E 6
	EXEC	head;
	char	buf[MAXBSIZE];
I 8
	off_t	lseek();
E 16
I 16
	typedef struct exec EXEC;
	register long size;
	register int n;
	EXEC head;
	char buf[MAXBSIZE];
	off_t lseek();
E 16
E 8

D 6
	if ((from_fd = open(from_name, O_RDONLY, 0)) < 0) {
		fprintf(stderr, "install: open: %s: %s\n", from_name, sys_errlist[errno]);
D 2
		(void)unlink(to_name);
		exit(1);
E 2
I 2
		bad();
E 2
	}
E 6
	if (read(from_fd, (char *)&head, sizeof(head)) < 0 || N_BADMAG(head)) {
		fprintf(stderr, "install: %s not in a.out format.\n", from_name);
D 2
		(void)unlink(to_name);
		exit(1);
E 2
I 2
		bad();
E 20
I 20
	if (!docopy && !devnull && unlink(from_name)) {
		error(from_name);
		exit(1);
E 29
I 29

D 32
	/* Always preserve the flags. */
	if (fchflags(to_fd, from_sb.st_flags)) {
E 32
I 32
D 34
	/* Always preserve the flags, except for the dump flag. */
	if (fchflags(to_fd, from_sb.st_flags & ~NODUMP)) {
E 34
I 34
	/*
	 * If provided a set of flags, set them, otherwise, preserve the
	 * flags, except for the dump flag.
	 */
	if (fchflags(to_fd,
D 35
	    flags & SETFLAGS ? fset : from_sb.st_flags & ~NODUMP)) {
E 35
I 35
	    flags & SETFLAGS ? fset : from_sb.st_flags & ~UF_NODUMP)) {
E 35
E 34
E 32
		serrno = errno;
		(void)unlink(to_name);
D 33
		err("%s: %s", to_name, strerror(serrno));
E 33
I 33
		err("%s: chflags: %s", to_name, strerror(serrno));
E 33
E 29
E 20
E 2
	}
I 29

	(void)close(to_fd);
	if (!docopy && !devnull && unlink(from_name))
		err("%s: %s", from_name, strerror(errno));
E 29
I 25
D 28
}

/*
 * Find the location of the file to be installed.
 */
stat_from(name, stbp)
	char **name;
	struct stat *stbp;
{
	char *newname;

	newname = (char *)genbuildname(*name);
	if (stat(newname, stbp) >= 0) {
		*name = newname;
		return (0);
	}
	if (stat(*name, stbp) < 0)
		return (-1);
	return (0);
E 28
E 25
D 20
	if (head.a_syms || head.a_trsize || head.a_drsize) {
		size = (long)head.a_text + head.a_data;
		head.a_syms = head.a_trsize = head.a_drsize = 0;
		if (head.a_magic == ZMAGIC)
			size += getpagesize() - sizeof(EXEC);
		if (write(to_fd, (char *)&head, sizeof(EXEC)) != sizeof(EXEC)) {
D 12
			fprintf(stderr, "install: write: %s: %s\n", to_name, sys_errlist[errno]);
E 12
I 12
			PERROR("install: write: ", to_name);
E 12
D 2
			(void)unlink(to_name);
			exit(1);
E 2
I 2
			bad();
E 2
		}
		for (; size; size -= n)
I 14
			/* sizeof(buf) guaranteed to fit in an int */
E 14
			if ((n = read(from_fd, buf, (int)MIN(size, sizeof(buf)))) <= 0)
				break;
			else if (write(to_fd, buf, n) != n) {
D 12
				fprintf(stderr, "install: write: %s: %s\n", to_name, sys_errlist[errno]);
E 12
I 12
				PERROR("install: write: ", to_name);
E 12
D 2
				(void)unlink(to_name);
				exit(1);
E 2
I 2
				bad();
E 2
			}
I 2
		if (size) {
			fprintf(stderr, "install: read: %s: premature EOF.\n", from_name);
			bad();
		}
E 2
		if (n == -1) {
D 12
			fprintf(stderr, "install: read: %s: %s\n", from_name, sys_errlist[errno]);
E 12
I 12
			PERROR("install: read: ", from_name);
E 12
D 2
			(void)unlink(to_name);
			exit(1);
E 2
I 2
			bad();
E 2
		}
	}
I 6
	else {
D 8
		(void)lseek(from_fd, L_SET, 0L);
E 8
I 8
		(void)lseek(from_fd, 0L, L_SET);
E 8
		copy(from_fd, from_name, to_fd, to_name);
	}
E 20
E 6
}

/*
I 6
 * copy --
 *	copy from one file to another
 */
I 29
void
E 29
D 17
static
E 17
D 31
copy(from_fd, from_name, to_fd, to_name)
E 31
I 31
copy(from_fd, from_name, to_fd, to_name, size)
E 31
D 16
	register int	from_fd, to_fd;
	char	*from_name, *to_name;
E 16
I 16
	register int from_fd, to_fd;
	char *from_name, *to_name;
I 31
	off_t size;
E 31
E 16
{
D 16
	register int	n;
	char	buf[MAXBSIZE];
E 16
I 16
D 29
	register int n;
E 29
I 29
	register int nr, nw;
	int serrno;
E 29
D 31
	char buf[MAXBSIZE];
E 31
I 31
	char *p, buf[MAXBSIZE];
E 31
E 16

D 29
	while ((n = read(from_fd, buf, sizeof(buf))) > 0)
		if (write(to_fd, buf, n) != n) {
D 12
			fprintf(stderr, "install: write: %s: %s\n", to_name, sys_errlist[errno]);
E 12
I 12
D 20
			PERROR("install: write: ", to_name);
E 12
			bad();
E 20
I 20
			error(to_name);
			bad(to_name);
E 29
I 29
D 31
	while ((nr = read(from_fd, buf, sizeof(buf))) > 0)
		if ((nw = write(to_fd, buf, nr)) != nr) {
E 31
I 31
	/*
	 * Mmap and write if less than 8M (the limit is so we don't totally
	 * trash memory on big files.  This is really a minor hack, but it
	 * wins some CPU back.
	 */
	if (size <= 8 * 1048576) {
		if ((p = mmap(NULL, (size_t)size, PROT_READ,
		    0, from_fd, (off_t)0)) == (char *)-1)
			err("%s: %s", from_name, strerror(errno));
		if (write(to_fd, p, size) != size)
			err("%s: %s", to_name, strerror(errno));
	} else {
		while ((nr = read(from_fd, buf, sizeof(buf))) > 0)
			if ((nw = write(to_fd, buf, nr)) != nr) {
				serrno = errno;
				(void)unlink(to_name);
				err("%s: %s",
				    to_name, strerror(nw > 0 ? EIO : serrno));
			}
		if (nr != 0) {
E 31
			serrno = errno;
			(void)unlink(to_name);
D 31
			err("%s: %s", to_name, strerror(nw > 0 ? EIO : serrno));
E 31
I 31
			err("%s: %s", from_name, strerror(serrno));
E 31
E 29
E 20
		}
D 29
	if (n == -1) {
D 12
		fprintf(stderr, "install: read: %s: %s\n", from_name, sys_errlist[errno]);
E 12
I 12
D 20
		PERROR("install: read: ", from_name);
E 12
		bad();
E 20
I 20
		error(from_name);
		bad(to_name);
E 29
I 29
D 31
	if (nr != 0) {
		serrno = errno;
		(void)unlink(to_name);
		err("%s: %s", from_name, strerror(serrno));
E 31
E 29
E 20
	}
}

/*
I 20
 * strip --
 *	use strip(1) to strip the target file
 */
I 29
void
E 29
strip(to_name)
	char *to_name;
{
D 29
	int status;
E 29
I 29
	int serrno, status;
E 29

	switch (vfork()) {
	case -1:
D 29
		error("fork");
		bad(to_name);
E 29
I 29
		serrno = errno;
		(void)unlink(to_name);
		err("forks: %s", strerror(errno));
E 29
	case 0:
D 21
		execl(_PATH_STRIP, "strip", to_name);
E 21
I 21
D 29
		execl(_PATH_STRIP, "strip", to_name, (char *)NULL);
		error(_PATH_STRIP);
E 21
		_exit(1);
E 29
I 29
		execl(_PATH_STRIP, "strip", to_name, NULL);
		err("%s: %s", _PATH_STRIP, strerror(errno));
E 29
	default:
		if (wait(&status) == -1 || status)
D 29
			bad(to_name);
E 29
I 29
			(void)unlink(to_name);
E 29
	}
D 22
}

/*
E 20
E 6
 * atoo --
 *	octal string to int
 */
D 17
static
E 17
D 2
atoo(C)
	register char	*C;		/* argument string */
E 2
I 2
atoo(str)
D 16
	register char	*str;
E 16
I 16
	register char *str;
E 16
E 2
{
D 2
	register int	val;		/* return value */
E 2
I 2
D 16
	register int	val;
E 16
I 16
	register int val;
E 16
E 2

D 2
	for (val = 0; isdigit(*C); ++C)
		val = val * 8 + *C - '0';
E 2
I 2
	for (val = 0; isdigit(*str); ++str)
		val = val * 8 + *str - '0';
E 2
	return(val);
E 22
}

/*
I 20
D 29
 * error --
 *	print out an error message
 */
error(s)
	char *s;
{
	extern int errno;
	char *strerror();

	(void)fprintf(stderr, "install: %s: %s\n", s, strerror(errno));
}

/*
E 20
D 6
 * usage --
 *	print a usage message and die
E 6
I 6
 * bad --
 *	remove created target and die
E 6
 */
D 17
static
E 17
D 6
usage()
E 6
I 6
D 20
bad()
E 20
I 20
bad(fname)
	char *fname;
E 20
E 6
{
D 6
	fputs("usage: install [-cs] [-g group] [-m mode] [-o owner] source destination\n", stderr);
E 6
I 6
D 20
	(void)unlink(pathbuf);
E 20
I 20
	(void)unlink(fname);
E 20
E 6
I 2
	exit(1);
}

/*
E 29
D 6
 * bad --
 *	remove created target and die
E 6
I 6
 * usage --
 *	print a usage message and die
E 6
 */
I 29
void
E 29
D 17
static
E 17
D 6
bad()
E 6
I 6
usage()
E 6
{
D 6
	(void)unlink(path);
E 6
I 6
D 12
	fputs("usage: install [-cs] [-g group] [-m mode] [-o owner] f1 f2;\n\tor f1 ... fn directory\n", stderr);
E 12
I 12
D 20
	fputs("usage: install [-cs] [-g group] [-m mode] [-o owner] file1 file2;\n\tor file1 ... fileN directory\n", stderr);
E 20
I 20
	(void)fprintf(stderr,
D 34
"usage: install [-cs] [-g group] [-m mode] [-o owner] file1 file2;\n\tor file1 ... fileN directory\n");
E 34
I 34
"usage: install [-cs] [-f flags] [-g group] [-m mode] [-o owner] file1 file2;\n\tor file1 ... fileN directory\n");
E 34
E 20
E 12
E 6
E 2
	exit(1);
I 29
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "install: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 29
}
E 1
