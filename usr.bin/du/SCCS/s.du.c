h44720
s 00001/00000/00203
d D 8.5 95/05/04 15:36:20 bostic 39 38
c optarg/optind moved to unistd.h
e
s 00009/00008/00194
d D 8.4 94/04/01 13:10:14 pendry 38 37
c prettyness police
e
s 00001/00002/00201
d D 8.3 94/04/01 09:52:01 bostic 37 36
c setting errno and then not exiting isn't safe
e
s 00053/00023/00150
d D 8.2 94/04/01 09:23:00 bostic 36 35
c POSIX 1003.2B/D9 symbolic links
e
s 00005/00005/00168
d D 8.1 93/06/06 14:37:03 bostic 35 34
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00173
d D 5.22 93/06/02 18:32:28 mckusick 34 33
c getbsize moved into libc
e
s 00002/00002/00172
d D 5.21 93/04/28 17:23:02 bostic 33 32
c getbsize doesn't need the program name any longer
e
s 00010/00038/00164
d D 5.20 93/03/07 12:35:25 bostic 32 31
c use library versions of err/warn
e
s 00001/00001/00201
d D 5.19 92/06/22 20:50:07 bostic 31 30
c st_blocks are quad's now
e
s 00009/00008/00193
d D 5.18 92/06/01 12:19:33 elan 30 29
c Added -Hh flags 
e
s 00001/00004/00200
d D 5.17 92/05/20 15:43:33 bostic 29 28
c delete -k
e
s 00036/00008/00168
d D 5.16 92/03/30 15:29:12 bostic 28 27
c check for failures when fts_read finishes
e
s 00003/00002/00173
d D 5.15 92/03/09 14:28:43 bostic 27 26
c make block size a long 
e
s 00026/00019/00149
d D 5.14 92/03/01 16:35:42 bostic 26 25
c replace -k with the BLOCKSIZE environmental variable
e
s 00007/00007/00161
d D 5.13 92/01/27 09:57:49 bostic 25 24
c fts_statb -> fts_statp
e
s 00023/00008/00145
d D 5.12 91/06/20 11:59:47 bostic 24 23
c make -a and -s mutually exclusive
e
s 00006/00000/00147
d D 5.11 91/05/23 18:29:16 bostic 23 22
c follow symbolic links if they are specified as command line args
e
s 00001/00001/00146
d D 5.10 91/03/21 11:45:35 bostic 22 21
c don't exit on error, fts_read will stop if it's unrecoverable
e
s 00002/00013/00145
d D 5.9 91/03/11 15:00:07 bostic 21 20
c fts(3) now returns reasonable error messages
c policy change, don't ignore FTS_DC items, stat as usual
e
s 00095/00123/00063
d D 5.8 90/11/21 14:31:16 bostic 20 19
c rewrite to use fts(3)
e
s 00013/00002/00173
d D 5.7 90/06/29 15:11:35 edward 19 18
c bug fix: missing chdir("..") when a directory is not readable
e
s 00001/00011/00174
d D 5.6 90/06/01 16:48:13 bostic 18 17
c new copyright notice
e
s 00001/00001/00184
d D 5.5 90/05/15 19:56:25 bostic 17 16
c string.h is ANSI C include file
e
s 00018/00012/00167
d D 5.4 89/08/21 22:44:43 bostic 16 15
c display 512-byte blocks, add -k option for 1024-byte blocks
e
s 00005/00003/00174
d D 5.3 89/06/24 19:43:13 bostic 15 14
c no way to avoid chdir -- user could do `du . ../foo'; minor lint
e
s 00001/00001/00176
d D 5.2 89/05/30 09:50:41 bostic 14 13
c path not set up yet, probably a typo
e
s 00148/00133/00029
d D 5.1 89/03/16 17:20:37 bostic 13 12
c from Chris Newcomb; new version of du, plus bug fixes
e
s 00001/00001/00161
d D 4.12 87/10/22 09:49:17 bostic 12 11
c ANSI C; sprintf now returns an int.
e
s 00000/00000/00162
d D 4.11 83/07/01 23:56:42 wnj 11 10
c include problems
e
s 00001/00001/00161
d D 4.10 83/06/30 14:30:19 sam 10 9
c include fix
e
s 00012/00010/00150
d D 4.9 83/05/22 18:05:36 sam 9 8
c user block count in inode (from kre)
e
s 00002/00000/00158
d D 4.8 82/11/12 11:01:59 mckusick 8 7
c don't forget to close "dirp" when chdir fails
e
s 00010/00003/00148
d D 4.7 82/11/11 19:23:07 mckusick 7 6
c fix bug that caused du to core dump while working on execute only directories
e
s 00025/00013/00126
d D 4.6 82/07/01 11:39:47 root 6 5
c fixed bug with multiple arguments which caused errors
c when arguments didn't begin with /
e
s 00001/00001/00138
d D 4.5 82/05/07 16:17:43 mckusick 5 4
c update to new fs
e
s 00089/00100/00050
d D 4.4 82/03/31 11:47:00 root 4 3
c cleaned up and uses lstat
e
s 00041/00058/00109
d D 4.3 82/03/29 15:48:51 mckusic 3 2
c convert to use new directory routines
e
s 00001/00005/00166
d D 4.2 82/03/10 12:46:24 wnj 2 1
c to 1024 byte units
e
s 00171/00000/00000
d D 4.1 80/10/01 17:26:22 bill 1 0
c date and time created 80/10/01 17:26:22 by bill
e
u
U
t
T
I 13
/*
D 35
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 35
I 35
D 36
 * Copyright (c) 1989, 1993
E 36
I 36
 * Copyright (c) 1989, 1993, 1994
E 36
 *	The Regents of the University of California.  All rights reserved.
E 35
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Newcomb.
 *
D 18
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
E 18
I 18
 * %sccs.include.redist.c%
E 18
 */

E 13
I 3
#ifndef lint
E 3
I 1
D 13
static char *sccsid = "%W% (Berkeley) %G%";
I 3
#endif
E 13
I 13
D 35
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 35
I 35
static char copyright[] =
D 36
"%Z% Copyright (c) 1989, 1993\n\
E 36
I 36
"%Z% Copyright (c) 1989, 1993, 1994\n\
E 36
	The Regents of the University of California.  All rights reserved.\n";
E 35
#endif /* not lint */
E 13

E 3
D 13
#include <stdio.h>
E 13
I 13
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 13
#include <sys/param.h>
#include <sys/stat.h>
I 20
D 32
#include <sys/errno.h>
E 32
I 32

E 32
E 20
D 3
#include <sys/dir.h>
E 3
I 3
D 5
#include <ndir.h>
E 5
I 5
D 10
#include <dir.h>
E 10
I 10
D 13
#include <sys/dir.h>
E 13
I 13
#include <dirent.h>
D 17
#include <strings.h>
E 17
I 17
D 20
#include <string.h>
E 20
E 17
D 32
#include <stdio.h>
E 32
I 32
#include <err.h>
#include <errno.h>
E 32
I 20
#include <fts.h>
D 32
#include <string.h>
E 32
I 32
#include <stdio.h>
E 32
#include <stdlib.h>
I 32
#include <string.h>
I 39
#include <unistd.h>
E 39
E 32
E 20
E 13
E 10
E 5

I 28
D 32
void	 err __P((const char *, ...));
E 32
E 28
I 26
D 27
char	*getbsize __P((char *, int *, int *));
E 27
I 27
D 33
char	*getbsize __P((char *, int *, long *));
E 33
I 33
D 34
char	*getbsize __P((int *, long *));
E 34
E 33
E 27
int	 linkchk __P((FTSENT *));
void	 usage __P((void));

I 32
int
E 32
E 26
D 4
#define howmany(x, y)	((x + y - 1) / y)
E 3
#define EQ(x,y)	(strcmp(x,y)==0)
#define ML	1000
E 4
I 4
D 6
#define howmany(x, y)	(((x) + (y) - 1) / (y))
E 4

E 6
D 4
struct stat Statb;
char	path[256], name[256];
int	Aflag = 0,
	Sflag = 0,
	Noarg = 0;
E 4
I 4
D 13
char	path[BUFSIZ], name[BUFSIZ];
int	aflg;
int	sflg;
char	*dot = ".";
E 13
I 13
D 16
/* this macro uses ints, not longs */
#define	kb(n)	(howmany(dbtob(n), 1024))
E 13

E 16
D 13
#define ML	1000
E 4
struct {
D 4
	int	dev,
		ino;
E 4
I 4
	int	dev;
	ino_t	ino;
E 4
} ml[ML];
I 4
int	mlx;
E 13
I 13
D 20
typedef struct _ID {
	dev_t	dev;
	ino_t	inode;
} ID;
E 13

E 4
D 13
long	descend();
D 4
char	*rindex();
char	*strcpy();
E 4
I 4
D 12
char	*index(), *rindex(), *strcpy(), *sprintf();
E 12
I 12
char	*index(), *rindex(), *strcpy();
E 13
I 13
ID *files;
dev_t device;
D 16
int crossmounts, listdirs, listfiles, maxfiles, numfiles;
E 16
I 16
int crossmounts, kvalue, listdirs, listfiles, maxfiles, numfiles;
E 16
char path[MAXPATHLEN + 1];
E 13
E 12
E 4

E 20
I 9
D 13
#define	kb(n)	(howmany(dbtob(n), 1024))

E 13
E 9
main(argc, argv)
D 4
char **argv;
E 4
I 4
	int argc;
D 26
	char **argv;
E 26
I 26
	char *argv[];
E 26
E 4
{
D 4
	register	i = 1;
	long	blocks = 0;
	register char	*np;
E 4
I 4
D 9
	long kbytes = 0;
E 9
I 9
D 13
	long blocks = 0;
E 9
	register char *np;
I 6
	int pid;
E 13
I 13
D 20
	extern int optind, errno;
D 15
	int ch, reset;
E 15
I 15
	int ch;
E 15
	char *malloc(), top[MAXPATHLEN + 1];
E 20
I 20
D 26
	extern int optind;
E 26
D 36
	register FTS *fts;
	register FTSENT *p;
D 26
	register int kvalue, listdirs, listfiles;
D 24
	int ch, ftsoptions;
E 24
I 24
	int aflag, ch, ftsoptions, sflag;
E 26
I 26
	register int listdirs, listfiles;
E 36
I 36
	FTS *fts;
	FTSENT *p;
E 36
D 27
	int aflag, blocksize, ch, ftsoptions, notused, sflag;
E 27
I 27
	long blocksize;
D 36
	int aflag, ch, ftsoptions, notused, sflag;
E 36
I 36
	int ftsoptions, listdirs, listfiles;
	int Hflag, Lflag, Pflag, aflag, ch, notused, rval, sflag;
E 36
E 27
E 26
E 24
	char **save;
E 20
E 13
E 6
E 4

D 4
	if (argc>1) {
		if(EQ(argv[i], "-s")) {
			++i;
			++Sflag;
		} else if(EQ(argv[i], "-a")) {
			++i;
			++Aflag;
		}
E 4
I 4
D 13
	argc--, argv++;
again:
	if (argc && !strcmp(*argv, "-s")) {
		sflg++;
		argc--, argv++;
		goto again;
E 4
	}
D 4
	if(i == argc)
		++Noarg;

E 4
I 4
	if (argc && !strcmp(*argv, "-a")) {
		aflg++;
		argc--, argv++;
		goto again;
	}
	if (argc == 0) {
		argv = &dot;
		argc = 1;
	}
E 4
	do {
D 3
		strcpy(path, Noarg? ".": argv[i]);
		strcpy(name, path);
E 3
I 3
D 4
		(void) strcpy(path, Noarg? ".": argv[i]);
		(void) strcpy(name, path);
E 3
		if(np = rindex(name, '/')) {
E 4
I 4
D 6
		(void) strcpy(path, *argv);
		(void) strcpy(name, *argv);
		if (np = rindex(name, '/')) {
E 4
			*np++ = '\0';
D 4
			if(chdir(*name? name: "/") == -1) {
				fprintf(stderr, "cannot chdir()\n");
E 4
I 4
			if (chdir(*name ? name : "/") < 0) {
				perror(*name ? name : "/");
E 6
I 6
		if (argc > 1) {
			pid = fork();
			if (pid == -1) {
				fprintf(stderr, "No more processes.\n");
E 13
I 13
D 20
	listdirs = crossmounts = 1;
E 20
I 20
D 36
	ftsoptions = FTS_PHYSICAL;
E 36
D 24
	kvalue = listfiles = 0;
	listdirs = 1;
E 24
I 24
D 26
	kvalue = 0;
E 26
E 24
	save = argv;
I 24
D 36
	aflag = sflag = 0;
E 24
E 20
D 16
	while ((ch = getopt(argc, argv, "asx")) != EOF)
E 16
I 16
D 29
	while ((ch = getopt(argc, argv, "aksx")) != EOF)
E 29
I 29
D 30
	while ((ch = getopt(argc, argv, "asx")) != EOF)
E 30
I 30
	while ((ch = getopt(argc, argv, "Hahsx")) != EOF)
E 30
E 29
E 16
		switch(ch) {
E 36
I 36
	Hflag = Lflag = Pflag = aflag = sflag = 0;
	ftsoptions = FTS_PHYSICAL;
	while ((ch = getopt(argc, argv, "HLPasx")) != EOF)
		switch (ch) {
E 36
I 30
		case 'H':
D 36
			ftsoptions |= FTS_COMFOLLOW;
E 36
I 36
			Hflag = 1;
			Lflag = Pflag = 0;
E 36
			break;
I 36
		case 'L':
			Lflag = 1;
			Hflag = Pflag = 0;
			break;
		case 'P':
			Pflag = 1;
			Hflag = Lflag = 0;
			break;
E 36
E 30
		case 'a':
D 24
			listfiles = 1;
E 24
I 24
			aflag = 1;
E 24
D 29
			break;
I 16
D 26
		case 'k':
			kvalue = 1;
E 26
I 26
		case 'k':		/* Delete before 4.4BSD. */
			(void)fprintf(stderr, "du: -k no longer supported\n");
E 29
E 26
			break;
I 30
D 36
		case 'h':
			ftsoptions &= ~FTS_PHYSICAL;
			ftsoptions |= FTS_LOGICAL;
			break;
E 36
E 30
E 16
		case 's':
D 24
			listfiles = listdirs = 0;
E 24
I 24
			sflag = 1;
E 24
			break;
		case 'x':
D 20
			crossmounts = 0;
E 20
I 20
			ftsoptions |= FTS_XDEV;
E 20
			break;
		case '?':
		default:
D 16
			fprintf(stderr, "usage: du [-asx] [name ...]\n");
E 16
I 16
D 24
			(void)fprintf(stderr,
			    "usage: du [-aksx] [name ...]\n");
E 16
			exit(1);
E 24
I 24
			usage();
E 24
		}
I 36
	argc -= optind;
E 36
	argv += optind;

I 36
	/*
	 * XXX
	 * Because of the way that fts(3) works, logical walks will not count
	 * the blocks actually used by symbolic links.  We rationalize this by
	 * noting that users computing logical sizes are likely to do logical
	 * copies, so not counting the links is correct.  The real reason is
	 * that we'd have to re-implement the kernel's symbolic link traversing
	 * algorithm to get this right.  If, for example, you have relative
	 * symbolic links referencing other relative symbolic links, it gets
	 * very nasty, very fast.  The bottom line is that it's documented in
	 * the man page, so it's a feature.
	 */
	if (Hflag)
		ftsoptions |= FTS_COMFOLLOW;
	if (Lflag) {
		ftsoptions &= ~FTS_PHYSICAL;
		ftsoptions |= FTS_LOGICAL;
	}

E 36
I 24
	if (aflag) {
		if (sflag)
			usage();
		listdirs = listfiles = 1;
	} else if (sflag)
		listdirs = listfiles = 0;
	else {
		listfiles = 0;
		listdirs = 1;
	}

E 24
D 20
	files = (ID *)malloc((u_int)(sizeof(ID) * (maxfiles = 128)));
E 20
I 20
	if (!*argv) {
		argv = save;
		argv[0] = ".";
		argv[1] = NULL;
	}
E 20

D 20
	if (!*argv)
		du(".");
	else {
		if (argv[1])
			(void)getwd(top);
D 15
		for (; *argv; ++argv) {
E 15
I 15
		for (;;) {
E 15
			du(*argv);
D 15
			if (argv[1] && index(*argv, '/') && chdir(top)) {
E 15
I 15
			if (!*++argv)
E 20
I 20
D 26
	if (!(fts = fts_open(argv, ftsoptions, (int (*)())NULL))) {
		(void)fprintf(stderr, "du: %s.\n", strerror(errno));
E 26
I 26
D 33
	(void)getbsize("du", &notused, &blocksize);
E 33
I 33
	(void)getbsize(&notused, &blocksize);
E 33
	blocksize /= 512;

D 28
	if ((fts = fts_open(argv, ftsoptions, NULL)) == NULL) {
		(void)fprintf(stderr, "du: %s\n", strerror(errno));
E 26
		exit(1);
	}
E 28
I 28
	if ((fts = fts_open(argv, ftsoptions, NULL)) == NULL)
D 32
		err("%s", strerror(errno));
E 32
I 32
D 36
		err(1, "");
E 36
I 36
		err(1, NULL);
E 36
E 32
E 28

D 36
	while (p = fts_read(fts))
		switch(p->fts_info) {
D 21
		case FTS_DNR:
			(void)fprintf(stderr,
			    "du: %s: unable to read.\n", p->fts_path);
			break;
		case FTS_DNX:
			(void)fprintf(stderr,
			    "du: %s: unable to search.\n", p->fts_path);
			break;
E 21
		case FTS_D:
E 36
I 36
	for (rval = 0; (p = fts_read(fts)) != NULL;)
		switch (p->fts_info) {
		case FTS_D:			/* Ignore. */
E 36
D 21
		case FTS_DC:
E 21
			break;
		case FTS_DP:
			p->fts_parent->fts_number += 
D 25
			    p->fts_number += p->fts_statb.st_blocks;
E 25
I 25
			    p->fts_number += p->fts_statp->st_blocks;
E 25
			/*
			 * If listing each directory, or not listing files
			 * or directories and this is post-order of the
			 * root of a traversal, display the total.
			 */
			if (listdirs || !listfiles && !p->fts_level)
D 26
				(void)printf("%ld\t%s\n", kvalue ?
				    howmany(p->fts_number, 2) :
				    p->fts_number, p->fts_path);
E 26
I 26
				(void)printf("%ld\t%s\n",
				    howmany(p->fts_number, blocksize),
				    p->fts_path);
E 26
			break;
I 21
D 36
		case FTS_DNR:
E 36
I 36
		case FTS_DC:			/* Ignore. */
			break;
		case FTS_DNR:			/* Warn, continue. */
E 36
E 21
		case FTS_ERR:
I 21
		case FTS_NS:
I 36
D 37
			errno = p->fts_errno;
E 36
E 21
D 32
			(void)fprintf(stderr,
D 26
			    "du: %s: %s.\n", p->fts_path, strerror(errno));
E 26
I 26
			    "du: %s: %s\n", p->fts_path, strerror(errno));
E 32
I 32
			warn("%s", p->fts_path);
E 37
I 37
			warnx("%s: %s", p->fts_path, strerror(p->fts_errno));
E 37
I 36
			rval = 1;
E 36
E 32
E 26
D 22
			exit(1);
E 22
I 22
			break;
I 23
D 30
		case FTS_SL:
			if (p->fts_level == FTS_ROOTLEVEL) {
				(void)fts_set(fts, p, FTS_FOLLOW);
				break;
			}
			/* FALLTHROUGH */
E 30
E 23
E 22
D 21
		case FTS_NS:
			(void)fprintf(stderr,
			    "du: unable to stat: %s.\n", p->fts_path);
			break;
E 21
		default:
D 25
			if (p->fts_statb.st_nlink > 1 && linkchk(p))
E 25
I 25
			if (p->fts_statp->st_nlink > 1 && linkchk(p))
E 25
E 20
				break;
D 20
			if (chdir(top)) {
E 15
				(void)fprintf(stderr, "du: %s: %s\n",
				    top, strerror(errno));
E 13
E 6
E 4
				exit(1);
			}
E 20
I 20
			/*
			 * If listing each file, or a non-directory file was
			 * the root of a traversal, display the total.
			 */
			if (listfiles || !p->fts_level)
D 26
				(void)printf("%ld\t%s\n", kvalue ?
D 25
				    howmany(p->fts_statb.st_blocks, 2) :
				    p->fts_statb.st_blocks, p->fts_path);
			p->fts_parent->fts_number += p->fts_statb.st_blocks;
E 25
I 25
				    howmany(p->fts_statp->st_blocks, 2) :
				    p->fts_statp->st_blocks, p->fts_path);
E 26
I 26
D 31
				(void)printf("%ld\t%s\n",
E 31
I 31
				(void)printf("%qd\t%s\n",
E 31
				    howmany(p->fts_statp->st_blocks, blocksize),
				    p->fts_path);
E 26
			p->fts_parent->fts_number += p->fts_statp->st_blocks;
E 25
E 20
D 6
		} else
			np = path;
D 4
		blocks = descend(path, *np? np: ".");
		if(Sflag)
			printf("%ld	%s\n", blocks, path);
	} while(++i < argc);

E 4
I 4
		kbytes = descend(path, *np ? np : ".");
		if (sflg)
			printf("%ld\t%s\n", kbytes, path);
E 6
I 6
D 13
			if (pid != 0)
				wait((int *)0);
E 13
		}
I 28
	if (errno)
D 32
		err("%s", strerror(errno));
E 32
I 32
D 36
		err(1, "");
E 36
I 36
		err(1, "fts_read");
E 36
E 32
E 28
D 13
		if (argc == 1 || pid == 0) {
			(void) strcpy(path, *argv);
			(void) strcpy(name, *argv);
			if (np = rindex(name, '/')) {
				*np++ = '\0';
				if (chdir(*name ? name : "/") < 0) {
					perror(*name ? name : "/");
					exit(1);
				}
			} else
				np = path;
D 9
			kbytes = descend(path, *np ? np : ".");
E 9
I 9
			blocks = descend(path, *np ? np : ".");
E 9
			if (sflg)
D 9
				printf("%ld\t%s\n", kbytes, path);
E 9
I 9
				printf("%ld\t%s\n", kb(blocks), path);
E 9
			if (argc > 1)
				exit(1);
		}
E 6
		argc--, argv++;
	} while (argc > 0);
E 13
I 13
D 20
	}
E 20
E 13
E 4
	exit(0);
}

I 3
D 4
DIR *dirp = NULL;
E 4
I 4
D 13
DIR	*dirp = NULL;
E 13
I 13
D 20
struct stat info;
E 20
I 20
typedef struct _ID {
	dev_t	dev;
	ino_t	inode;
} ID;
E 20
E 13

I 26
int
E 26
E 4
E 3
D 13
long
D 4
descend(np, fname)
char *np, *fname;
E 4
I 4
descend(base, name)
	char *base, *name;
E 13
I 13
D 20
du(arg)
	register char *arg;
E 20
I 20
linkchk(p)
D 38
	register FTSENT *p;
E 38
I 38
	FTSENT *p;
E 38
E 20
E 13
E 4
{
D 3
	int dir = 0, /* open directory */
		offset,
		dsize,
		entries,
		dirsize;

	struct direct dentry[BUFSIZ / sizeof (struct direct)];
E 3
D 4
	register  struct direct *dp;
D 3
	register char *c1, *c2;
E 3
I 3
	register char *c1;
E 4
I 4
D 13
	char *ebase0, *ebase;
	struct stat stb;
E 4
E 3
	int i;
D 4
	char *endofname;
	long blocks = 0;
E 4
I 4
D 9
	long kbytes = 0;
E 9
I 9
	long blocks = 0;
E 9
E 4
I 3
	long curoff = NULL;
I 4
	register struct direct *dp;
E 13
I 13
D 20
	extern int errno;
	u_long total, descend();
E 20
I 20
	static ID *files;
	static int maxfiles, nfiles;
D 38
	register ID *fp, *start;
	register ino_t ino;
	register dev_t dev;
E 38
I 38
	ID *fp, *start;
	ino_t ino;
	dev_t dev;
E 38
E 20
E 13
E 4
E 3

D 4
	if(stat(fname,&Statb)<0) {
		fprintf(stderr, "--bad status < %s >\n", name);
		return 0L;
E 4
I 4
D 13
	ebase0 = ebase = index(base, 0);
	if (ebase > base && ebase[-1] == '/')
		ebase--;
	if (lstat(name, &stb) < 0) {
		perror(base);
		*ebase0 = 0;
		return (0);
E 13
I 13
D 20
	if (lstat(arg, &info)) {
D 14
		(void)fprintf(stderr, "du: %s: %s\n", path, strerror(errno));
E 14
I 14
		(void)fprintf(stderr, "du: %s: %s\n", arg, strerror(errno));
E 14
		return;
E 13
E 4
	}
D 4
	if(Statb.st_nlink > 1 && (Statb.st_mode&S_IFMT)!=S_IFDIR) {
		static linked = 0;

		for(i = 0; i <= linked; ++i) {
			if(ml[i].ino==Statb.st_ino && ml[i].dev==Statb.st_dev)
				return 0;
E 4
I 4
D 13
	if (stb.st_nlink > 1 && (stb.st_mode&S_IFMT) != S_IFDIR) {
		for (i = 0; i <= mlx; i++)
			if (ml[i].ino == stb.st_ino && ml[i].dev == stb.st_dev)
				return (0);
		if (mlx < ML) {
			ml[mlx].dev = stb.st_dev;
			ml[mlx].ino = stb.st_ino;
			mlx++;
E 4
		}
E 13
I 13
	if ((info.st_mode&S_IFMT) != S_IFDIR) {
D 16
		(void)printf("%u\t%s\n", kb(info.st_blocks), arg);
E 16
I 16
		(void)printf("%ld\t%s\n", kvalue ?
		    howmany(info.st_blocks, 2) : info.st_blocks, arg);
E 16
		return;
E 13
D 4
		if (linked < ML) {
			ml[linked].dev = Statb.st_dev;
			ml[linked].ino = Statb.st_ino;
			++linked;
		}
E 4
	}
D 2
/*
	blocks = (Statb.st_size + BSIZE-1) >> BSHIFT;
*/
	blocks = (Statb.st_size + 511) >> 9;

E 2
I 2
D 3
	blocks = (Statb.st_size + 1023-1) >> 10;
E 2
	if((Statb.st_mode&S_IFMT)!=S_IFDIR) {
E 3
I 3
D 4
	blocks = howmany(Statb.st_size, 1024);

	if((Statb.st_mode&S_IFMT) != S_IFDIR) {
E 3
		if(Aflag)
			printf("%ld	%s\n", blocks, np);
		return(blocks);
E 4
I 4
D 9
	kbytes = howmany(stb.st_size, 1024);
E 9
I 9
D 13
	blocks = stb.st_blocks;
E 9
	if ((stb.st_mode&S_IFMT) != S_IFDIR) {
		if (aflg)
D 9
			printf("%ld\t%s\n", kbytes, base);
		return (kbytes);
E 9
I 9
			printf("%ld\t%s\n", kb(blocks), base);
		return (blocks);
E 13
I 13
	device = info.st_dev;
	(void)strcpy(path, arg);
	total = descend(path);
	if (!listfiles && !listdirs)
D 16
		(void)printf("%u\t%s\n", kb(total), path);
E 16
I 16
		(void)printf("%lu\t%s\n",
		    kvalue ? howmany(total, 2) : total, path);
E 16
}
E 20
I 20
D 25
	ino = p->fts_statb.st_ino;
	dev = p->fts_statb.st_dev;
E 25
I 25
	ino = p->fts_statp->st_ino;
	dev = p->fts_statp->st_dev;
E 25
D 36
	if (start = files)
E 36
I 36
	if ((start = files) != NULL)
E 36
		for (fp = start + nfiles - 1; fp >= start; --fp)
			if (ino == fp->inode && dev == fp->dev)
D 38
				return(1);
E 20

E 38
I 38
				return (1);

E 38
D 20
u_long
descend(endp)
	register char *endp;
{
	extern int errno;
	register DIR *dir;
	register ID *fp;
	register struct dirent *dp;
	u_long total;
	char *realloc();

	if (info.st_nlink > 1) {
		for (fp = files + numfiles - 1; fp >= files; --fp)
			if (info.st_ino == fp->inode &&
			    info.st_dev == fp->dev)
				return(0L);
		if (numfiles == maxfiles)
			files = (ID *)realloc((char *)files,
			    (u_int)(sizeof(ID) * (maxfiles += 128)));
		files[numfiles].inode = info.st_ino;
		files[numfiles].dev = info.st_dev;
		++numfiles;
E 20
I 20
D 26
	if (nfiles == maxfiles && !(files = (ID *)realloc((char *)files,
	    (u_int)(sizeof(ID) * (maxfiles += 128))))) {
E 26
I 26
	if (nfiles == maxfiles && (files = realloc((char *)files,
D 28
	    (u_int)(sizeof(ID) * (maxfiles += 128)))) == NULL) {
E 26
		(void)fprintf(stderr, "du: %s\n", strerror(errno));
		exit(1);
E 20
E 13
E 9
E 4
	}
E 28
I 28
	    (u_int)(sizeof(ID) * (maxfiles += 128)))) == NULL)
D 32
		err("%s", strerror(errno));
E 32
I 32
		err(1, "");
E 32
E 28
D 4

	for(c1 = np; *c1; ++c1);
	if(*(c1-1) == '/')
		--c1;
	endofname = c1;
D 3
	dirsize = Statb.st_size;
E 3
	if(chdir(fname) == -1)
		return 0;
E 4
I 4
D 7
	if (chdir(name) < 0)
		return (0);
E 7
E 4
D 3
	for(offset=0; offset < dirsize; offset += BUFSIZ) { /* each block */
		dsize = BUFSIZ<(dirsize-offset)? BUFSIZ: (dirsize-offset);
		if(!dir) {
			if((dir=open(".",0))<0) {
				fprintf(stderr, "--cannot open < %s >\n",
					np);
				goto ret;
			}
			if(offset) lseek(dir, (long)offset, 0);
			if(read(dir, (char *)dentry, dsize)<0) {
				fprintf(stderr, "--cannot read < %s >\n",
					np);
				goto ret;
			}
			if(dir > 10) {
				close(dir);
				dir = 0;
			}
		} else 
			if(read(dir, (char *)dentry, dsize)<0) {
				fprintf(stderr, "--cannot read < %s >\n",
					np);
				goto ret;
			}
		for(dp=dentry, entries=dsize>>4; entries; --entries, ++dp) {
			/* each directory entry */
			if(dp->d_ino==0
			|| EQ(dp->d_name, ".")
			|| EQ(dp->d_name, ".."))
				continue;
			c1 = endofname;
			*c1++ = '/';
			c2 = dp->d_name;
			for(i=0; i<DIRSIZ; ++i)
				if(*c2)
					*c1++ = *c2++;
				else
					break;
			*c1 = '\0';
			if(c1 == endofname) /* ?? */
				return 0L;
			blocks += descend(np, endofname+1);
E 3
I 3
D 13
	if (dirp != NULL)
		closedir(dirp);
D 4
	if ((dirp = opendir(".")) == NULL) {
		fprintf(stderr, "--cannot open < %s >\n", np);
		goto ret;
E 4
I 4
D 7
	dirp = opendir(".");
E 7
I 7
	dirp = opendir(name);
E 7
	if (dirp == NULL) {
		perror(base);
		*ebase0 = 0;
		return (0);
E 4
	}
I 7
	if (chdir(name) < 0) {
		perror(base);
		*ebase0 = 0;
I 8
		closedir(dirp);
		dirp = NULL;
E 8
		return (0);
	}
E 7
D 4
	if ((dp = readdir(dirp)) == NULL) {
		fprintf(stderr, "--cannot read < %s >\n", np);
		closedir(dirp);
		dirp = NULL;
		goto ret;
	}
	for ( ; dp != NULL; dp = readdir(dirp)) {
		/* each directory entry */
		if (EQ(dp->d_name, ".") || EQ(dp->d_name, ".."))
E 4
I 4
	while (dp = readdir(dirp)) {
		if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
E 4
			continue;
D 4
		c1 = endofname;
		*c1++ = '/';
		(void) strcpy(c1, dp->d_name);
E 4
I 4
		(void) sprintf(ebase, "/%s", dp->d_name);
E 4
		curoff = telldir(dirp);
D 4
		blocks += descend(np, endofname+1);
E 4
I 4
D 9
		kbytes += descend(base, ebase+1);
E 9
I 9
		blocks += descend(base, ebase+1);
E 9
		*ebase = 0;
E 4
		if (dirp == NULL) {
D 4
			/* previous entry was a directory */
E 4
			dirp = opendir(".");
I 7
			if (dirp == NULL) {
				perror(".");
				return (0);
E 13
I 13
D 20
	total = info.st_blocks;
	if ((info.st_mode&S_IFMT) == S_IFDIR) {
		if (info.st_dev != device && !crossmounts)
			return(0L);
D 19
		if (chdir(endp) || !(dir = opendir("."))) {
E 19
I 19
		if (chdir(endp)) {
E 19
D 16
			fprintf(stderr, "du: %s: %s\n", path, strerror(errno));
E 16
I 16
			(void)fprintf(stderr, "du: %s: %s\n",
			    path, strerror(errno));
E 16
			return(total);
D 19
		} 
E 19
I 19
		}
		if (!(dir = opendir("."))) {
			(void)fprintf(stderr, "du: %s: %s\n",
			    path, strerror(errno));
			if (chdir("..")) {
				/* very unlikely */
				(void)fprintf(stderr, "du: ..: %s\n",
				    strerror(errno));
				exit(1);
			}
			return(total);
		}
E 19
		for (; *endp; ++endp);
		if (endp[-1] != '/')
			*endp++ = '/';
		while (dp = readdir(dir)) {
			if (dp->d_name[0] == '.' && (!dp->d_name[1] ||
			    dp->d_name[1] == '.' && !dp->d_name[2]))
				continue;
			bcopy(dp->d_name, endp, dp->d_namlen + 1);
			if (lstat(dp->d_name, &info)) {
				(void)fprintf(stderr, "du: %s: %s\n", path,
				    strerror(errno));
				continue;
E 13
			}
E 7
D 13
			seekdir(dirp, curoff);
E 13
I 13
			total += descend(endp);
E 13
E 3
		}
I 13
		closedir(dir);
		if (chdir("..")) {
D 16
			fprintf(stderr, "du: ..: %s\n", strerror(errno));
E 16
I 16
			(void)fprintf(stderr, "du: ..: %s\n", strerror(errno));
E 16
			exit(1);
		}
		*--endp = '\0';
		if (listdirs)
D 16
			(void)printf("%u\t%s\n", kb(total), path);
E 16
I 16
			(void)printf("%lu\t%s\n",
			    kvalue ? howmany(total, 2) : total, path);
E 16
E 13
	}
I 3
D 13
	closedir(dirp);
	dirp = NULL;
E 3
D 4
	*endofname = '\0';
	if(!Sflag)
		printf("%ld	%s\n", blocks, np);
ret:
D 3
	if(dir)
		close(dir);
E 3
	if(chdir("..") == -1) {
		*endofname = '\0';
		fprintf(stderr, "Bad directory <%s>\n", np);
		while(*--endofname != '/');
		*endofname = '\0';
		if(chdir(np) == -1)
			exit(1);
E 4
I 4
	if (sflg == 0)
D 9
		printf("%ld\t%s\n", kbytes, base);
E 9
I 9
		printf("%ld\t%s\n", kb(blocks), base);
E 9
	if (chdir("..") < 0) {
		(void) sprintf(index(base, 0), "/..");
		perror(base);
		exit(1);
E 4
	}
D 4
	return(blocks);
E 4
I 4
	*ebase0 = 0;
D 9
	return (kbytes);
E 9
I 9
	return (blocks);
E 13
I 13
	else if (listfiles)
D 16
		(void)printf("%u\t%s\n", kb(total), path);
E 16
I 16
		(void)printf("%lu\t%s\n",
		    kvalue ? howmany(total, 2) : total, path);
E 16
	return(total);
E 20
I 20
	files[nfiles].inode = ino;
	files[nfiles].dev = dev;
	++nfiles;
D 38
	return(0);
E 38
I 38
	return (0);
E 38
I 24
}

I 26
void
E 26
usage()
{
I 38

E 38
D 26
	(void)fprintf(stderr, "usage: du [-a | -s] [-kx] [file ...]\n");
E 26
I 26
D 30
	(void)fprintf(stderr, "usage: du [-a | -s] [-x] [file ...]\n");
E 30
I 30
D 36
	(void)fprintf(stderr, "usage: du [-a | -s] [-Hhx] [file ...]\n");
E 36
I 36
	(void)fprintf(stderr,
D 38
"usage: du [-H | -L | -P] [-a | -s] [-x] [file ...]\n");
E 38
I 38
		"usage: du [-H | -L | -P] [-a | -s] [-x] [file ...]\n");
E 38
E 36
E 30
E 26
	exit(1);
I 28
D 32
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
	(void)fprintf(stderr, "du: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 32
E 28
E 24
E 20
E 13
E 9
E 4
}
E 1
