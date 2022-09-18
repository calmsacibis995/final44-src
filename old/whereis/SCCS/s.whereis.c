h01849
s 00004/00014/00352
d D 5.5 91/04/18 18:47:17 bostic 16 15
c new copyright; att/bsd/shared
e
s 00042/00000/00324
d D 5.4 90/06/29 00:46:00 marc 15 14
c add more source directories.  this whole thing needs to be redesigned.
e
s 00015/00004/00309
d D 5.3 90/03/10 13:38:42 bostic 14 13
c add Berkeley specific copyright notices
e
s 00003/00002/00310
d D 5.2 87/12/03 21:36:59 bostic 13 12
c bug report 4.3BSD/ucb/151; exit 0 on success
e
s 00014/00002/00298
d D 5.1 85/05/31 09:40:00 dist 12 11
c Add copyright
e
s 00003/00000/00297
d D 4.11 84/02/22 16:23:07 ralph 11 10
c added mann, manl, mano to search list.
e
s 00003/00001/00294
d D 4.10 83/07/02 01:01:41 sam 10 9
c include fixes
e
s 00002/00009/00293
d D 4.9 83/05/03 14:17:30 sam 9 8
c purge Cory crap; add places to look for .h files
e
s 00014/00008/00288
d D 4.8 83/02/03 18:36:08 mckusick 8 7
c add entries for .../ucb/net/misc .../ucb/pascal .../libc/net
e
s 00000/00005/00296
d D 4.7 82/10/24 16:33:20 mckusick 7 6
c get rid of src.monet and src.arpa
e
s 00034/00017/00267
d D 4.6 82/05/11 11:45:32 mckusick 6 5
c update to reflect new source layout
e
s 00001/00007/00283
d D 4.5 82/03/15 04:37:48 root 5 4
c machine independent
e
s 00000/00039/00290
d D 4.4 81/07/03 23:29:26 root 4 3
c remove conditional crap
e
s 00024/00010/00305
d D 4.3 81/02/07 20:12:06 kre 3 2
c added arpavax local directories
e
s 00016/00015/00299
d D 4.2 80/12/02 10:27:11 eric 2 1
c make directories realistic; simplify transport to other machines
e
s 00314/00000/00000
d D 4.1 80/10/01 17:29:33 bill 1 0
c date and time created 80/10/01 17:29:33 by bill
e
u
U
t
T
I 12
D 16
/*
D 14
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
 * Copyright (c) 1980, 1990 The Regents of the University of California.
E 16
I 16
/*-
 * Copyright (c) 1980 The Regents of the University of California.
E 16
 * All rights reserved.
 *
D 16
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
E 16
I 16
 * %sccs.include.redist.c%
E 16
E 14
 */

E 12
I 10
#ifndef lint
E 10
I 1
D 12
static char *sccsid = "%W% (Berkeley) %G%";
I 10
#endif
E 12
I 12
char copyright[] =
D 14
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 14
I 14
D 16
"%Z% Copyright (c) 1980, 1990 The Regents of the University of California.\n\
E 16
I 16
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 16
E 14
 All rights reserved.\n";
D 13
#endif not lint
E 13
I 13
#endif /* not lint */
E 13

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 13
#endif not lint
E 13
I 13
#endif /* not lint */
E 13
E 12
E 10
I 5

E 5
D 6
#include <sys/types.h>
E 6
I 6
#include <sys/param.h>
I 10
#include <sys/dir.h>
E 10
E 6
#include <stdio.h>
#include <ctype.h>
D 6
#include <sys/dir.h>
E 6
I 6
D 10
#include <dir.h>
E 10
E 6
D 5
#include <whoami.h>
E 5

static char *bindirs[] = {
I 15
	"/bin",
	"/sbin",
	"/usr/ucb",
	"/usr/bin",
	"/usr/sbin",
	"/usr/old",
	"/usr/contrib",
	"/usr/games",
	"/usr/local",
	"/usr/libexec",
	"/usr/include",
	"/usr/hosts",
	"/usr/share", /*?*/
E 15
	"/etc",
I 15
#ifdef notdef
	/* before reorg */
	"/etc",
E 15
	"/bin",
	"/usr/bin",
	"/usr/games",
I 3
D 4
#ifdef CSVAX
E 4
	"/lib",
	"/usr/ucb",
	"/usr/lib",
	"/usr/local",
	"/usr/new",
	"/usr/old",
I 6
	"/usr/hosts",
I 9
	"/usr/include",
I 15
#endif
E 15
E 9
E 6
D 4
#endif
E 3
D 2
#ifdef CSVAX
E 2
I 2
#ifdef CORY
	"/usr/bin/eecs",
	"/usr/bin/new",
	"/usr/bin/v7",
	"/usr/bin/old",
	"/usr/bin/UNSUPPORTED",
D 3
#else
E 3
I 3
#endif
#ifdef ARPAVAX
E 3
E 2
	"/lib",
	"/usr/ucb",
	"/usr/lib",
	"/usr/local",
	"/usr/new",
	"/usr/old",
#endif
E 4
D 2
#ifdef CORY
	"/usr/bin/eecs",
	"/usr/bin/new",
	"/usr/bin/v7",
	"/usr/bin/old",
	"/usr/bin/UNSUPPORTED",
#endif
E 2
	0
};
I 15
/* This needs to be redone - man pages live with sources */
E 15
static char *mandirs[] = {
	"/usr/man/man1",
	"/usr/man/man2",
	"/usr/man/man3",
	"/usr/man/man4",
	"/usr/man/man5",
	"/usr/man/man6",
	"/usr/man/man7",
	"/usr/man/man8",
I 11
	"/usr/man/manl",
	"/usr/man/mann",
	"/usr/man/mano",
E 11
D 4
#ifdef CORY
	"/usr/man/manu",
	"/usr/man/manc",
	"/usr/man/manv7",
	"/usr/bin/eecs/mane",
I 2
D 3
#else
	"/usr/man/manl",
E 3
E 2
#endif
E 4
I 2
D 3
	"/usr/doc",
E 3
E 2
	0
};
static char *srcdirs[]  = {
D 6
	"/usr/src/cmd",
E 6
I 6
D 8
	"/usr/src/etc",
E 8
	"/usr/src/bin",
I 15
	"/usr/src/sbin",
	"/usr/src/etc",
	"/usr/src/pgrm",
E 15
	"/usr/src/usr.bin",
I 15
	"/usr/src/usr.sbin",
	"/usr/src/usr.ucb",
	"/usr/src/usr.new",
	"/usr/src/usr.lib",
	"/usr/src/libexec",
	"/usr/src/libdata",
	"/usr/src/share",
	"/usr/src/contrib",
	"/usr/src/athena",
	"/usr/src/devel",
	"/usr/src/games",
	"/usr/src/local",
	"/usr/src/man",
	"/usr/src/root",
	"/usr/src/old",
	"/usr/src/include",
	/* still need libs */
#ifdef notdef /* before reorg */
	"/usr/src/bin",
	"/usr/src/usr.bin",
E 15
I 8
	"/usr/src/etc",
	"/usr/src/ucb",
E 8
E 6
	"/usr/src/games",
I 8
	"/usr/src/usr.lib",
E 8
D 6
	"/usr/src/libc/gen",
	"/usr/src/libc/stdio",
I 3
D 4
#ifdef CSVAX
E 4
	"/usr/src/libc/sys",
E 6
I 6
	"/usr/src/lib",
I 8
	"/usr/src/local",
	"/usr/src/new",
	"/usr/src/old",
I 9
	"/usr/src/include",
E 9
E 8
	"/usr/src/lib/libc/gen",
	"/usr/src/lib/libc/stdio",
	"/usr/src/lib/libc/sys",
D 8
	"/usr/src/ucb",
E 8
I 8
	"/usr/src/lib/libc/net/common",
	"/usr/src/lib/libc/net/inet",
	"/usr/src/lib/libc/net/misc",
E 8
D 9
	"/usr/src/ucb/netser",
I 8
	"/usr/src/ucb/netser/misc",
E 8
	"/usr/src/ucb/arpanet",
E 9
D 8
	"/usr/src/usr.lib",
	"/usr/src/local",
E 6
	"/usr/src/new",
	"/usr/src/old",
E 8
I 8
	"/usr/src/ucb/pascal",
	"/usr/src/ucb/pascal/utilities",
E 8
D 6
	"/usr/src/local",
E 6
	"/usr/src/undoc",
I 15
#endif
E 15
I 6
D 7
	/* these are temporary */
	"/usr/src/src.arpa/cmd",
	"/usr/src/src.monet/4.1",
	"/usr/src/src.monet/4.1a",
	"/usr/src/src.monet/4.1b",
E 7
E 6
D 4
#endif
E 3
D 2
#ifdef CSVAX
	"/usr/src/libc/sys",
	"/usr/src/new",
	"/usr/src/old",
	"/usr/src/local",
	"/usr/src/undoc",
#endif
E 2
#ifdef CORY
	"/usr/bin/eecs/src",
	"/usr/src/cmd/v7",
	"/usr/src/cmd/new",
	"/usr/src/cmd/old",
	"/usr/src/cmd/UNSUPPORTED",
I 2
D 3
#else
	"/usr/src/libc/sys",
	"/usr/src/new",
	"/usr/src/old",
	"/usr/local/src",
	"/usr/src/undoc",
E 3
I 3
#endif
#ifdef	ARPAVAX
	"/ra/src/cmd",
	"/ra/src/new",
	"/ra/src/old",
	"/ra/src/libc/gen",
	"/ra/src/libc/stdio",
E 3
E 2
#endif
E 4
	0
};

char	sflag = 1;
char	bflag = 1;
char	mflag = 1;
char	**Sflag;
int	Scnt;
char	**Bflag;
int	Bcnt;
char	**Mflag;
int	Mcnt;
char	uflag;
/*
 * whereis name
 * look for source, documentation and binaries
 */
main(argc, argv)
	int argc;
	char *argv[];
{

I 6
D 9
#ifdef CORY
	if (getuid() == 0)
		nice(-20);
	if (((getuid() >> 8) & 0377) > 10)
		setuid(getuid());
#endif
E 9
E 6
D 5
#ifdef CORY
	if (getuid() == 0)
		nice(-20);
	if (((getuid() >> 8) & 0377) > 10)
		setuid(getuid());
#endif
E 5
	argc--, argv++;
	if (argc == 0) {
usage:
		fprintf(stderr, "whereis [ -sbmu ] [ -SBM dir ... -f ] name...\n");
		exit(1);
	}
	do
		if (argv[0][0] == '-') {
			register char *cp = argv[0] + 1;
			while (*cp) switch (*cp++) {

			case 'f':
				break;

			case 'S':
				getlist(&argc, &argv, &Sflag, &Scnt);
				break;

			case 'B':
				getlist(&argc, &argv, &Bflag, &Bcnt);
				break;

			case 'M':
				getlist(&argc, &argv, &Mflag, &Mcnt);
				break;

			case 's':
				zerof();
				sflag++;
				continue;

			case 'u':
				uflag++;
				continue;

			case 'b':
				zerof();
				bflag++;
				continue;

			case 'm':
				zerof();
				mflag++;
				continue;

			default:
				goto usage;
			}
			argv++;
		} else
			lookup(*argv++);
	while (--argc > 0);
I 13
	exit(0);
E 13
}

getlist(argcp, argvp, flagp, cntp)
	char ***argvp;
	int *argcp;
	char ***flagp;
	int *cntp;
{

	(*argvp)++;
	*flagp = *argvp;
	*cntp = 0;
	for ((*argcp)--; *argcp > 0 && (*argvp)[0][0] != '-'; (*argcp)--)
		(*cntp)++, (*argvp)++;
	(*argcp)++;
	(*argvp)--;
}


zerof()
{

	if (sflag && bflag && mflag)
		sflag = bflag = mflag = 0;
}
int	count;
int	print;


lookup(cp)
	register char *cp;
{
	register char *dp;

	for (dp = cp; *dp; dp++)
		continue;
	for (; dp > cp; dp--) {
		if (*dp == '.') {
			*dp = 0;
			break;
		}
	}
	for (dp = cp; *dp; dp++)
		if (*dp == '/')
			cp = dp + 1;
	if (uflag) {
		print = 0;
		count = 0;
	} else
		print = 1;
again:
	if (print)
		printf("%s:", cp);
	if (sflag) {
		looksrc(cp);
		if (uflag && print == 0 && count != 1) {
			print = 1;
			goto again;
		}
	}
	count = 0;
	if (bflag) {
		lookbin(cp);
		if (uflag && print == 0 && count != 1) {
			print = 1;
			goto again;
		}
	}
	count = 0;
	if (mflag) {
		lookman(cp);
		if (uflag && print == 0 && count != 1) {
			print = 1;
			goto again;
		}
	}
	if (print)
		printf("\n");
}

looksrc(cp)
	char *cp;
{
	if (Sflag == 0) {
		find(srcdirs, cp);
	} else
		findv(Sflag, Scnt, cp);
}

lookbin(cp)
	char *cp;
{
	if (Bflag == 0)
		find(bindirs, cp);
	else
		findv(Bflag, Bcnt, cp);
}

lookman(cp)
	char *cp;
{
	if (Mflag == 0) {
		find(mandirs, cp);
	} else
		findv(Mflag, Mcnt, cp);
}

findv(dirv, dirc, cp)
	char **dirv;
	int dirc;
	char *cp;
{

	while (dirc > 0)
		findin(*dirv++, cp), dirc--;
}

find(dirs, cp)
	char **dirs;
	char *cp;
{

	while (*dirs)
		findin(*dirs++, cp);
}

findin(dir, cp)
	char *dir, *cp;
{
D 6
	register FILE *d;
	struct direct direct;
E 6
I 6
	DIR *dirp;
	struct direct *dp;
E 6

D 6
	d = fopen(dir, "r");
	if (d == NULL)
E 6
I 6
	dirp = opendir(dir);
	if (dirp == NULL)
E 6
		return;
D 6
	while (fread(&direct, sizeof direct, 1, d) == 1) {
		if (direct.d_ino == 0)
			continue;
		if (itsit(cp, direct.d_name)) {
E 6
I 6
	while ((dp = readdir(dirp)) != NULL) {
		if (itsit(cp, dp->d_name)) {
E 6
			count++;
			if (print)
D 6
				printf(" %s/%.14s", dir, direct.d_name);
E 6
I 6
D 8
				printf(" %s/%.14s", dir, dp->d_name);
E 8
I 8
				printf(" %s/%s", dir, dp->d_name);
E 8
E 6
		}
	}
D 6
	fclose(d);
E 6
I 6
	closedir(dirp);
E 6
}

itsit(cp, dp)
	register char *cp, *dp;
{
D 8
	register int i = 14;
E 8
I 8
	register int i = strlen(dp);
E 8

	if (dp[0] == 's' && dp[1] == '.' && itsit(cp, dp+2))
		return (1);
	while (*cp && *dp && *cp == *dp)
		cp++, dp++, i--;
	if (*cp == 0 && *dp == 0)
		return (1);
	while (isdigit(*dp))
		dp++;
	if (*cp == 0 && *dp++ == '.') {
		--i;
		while (i > 0 && *dp)
			if (--i, *dp++ == '.')
				return (*dp++ == 'C' && *dp++ == 0);
		return (1);
	}
	return (0);
}
E 1
