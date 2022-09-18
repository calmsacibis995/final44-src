h39356
s 00032/00009/00327
d D 8.8 95/05/08 17:50:12 mckusick 37 36
c add -A option to unmount all mounted filesystems
e
s 00029/00093/00307
d D 8.7 95/05/08 17:23:44 mckusick 36 35
c update to use vfslist from mount; cleanups for vfsconf
e
s 00016/00013/00384
d D 8.6 95/02/03 06:25:51 pendry 35 33
c only do name lookup for nfs filesystems
e
s 00016/00013/00384
d R 8.6 95/02/03 06:16:10 pendry 34 33
c only do name lookup for nfs filesystems
e
s 00004/00004/00393
d D 8.5 94/10/09 19:49:45 mckusick 33 32
c get error return consistent
e
s 00003/00001/00394
d D 8.4 94/06/14 16:55:05 mkm 32 31
c walking mount list should be reentrant (from mycroft)
e
s 00161/00170/00234
d D 8.3 94/02/20 16:21:27 bostic 31 30
c NFS is always turned on; fix it so that the order of -h and -t doesn't
c matter; pass error values and exit with a reasonable exit status on failure;
c fix the usage statement; more error messages, more KNF, prettiness police
e
s 00113/00087/00291
d D 8.2 94/02/18 07:07:38 pendry 30 29
c lint, KNF.
c fixed so that nfs unmounts actually get round to calling the remote mountd.
e
s 00005/00005/00373
d D 8.1 93/06/05 11:26:34 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00377
d D 5.18 93/01/22 16:14:01 mckusick 28 27
c no more MNT_NOFORCE
e
s 00035/00058/00343
d D 5.17 92/07/09 22:37:34 mckusick 27 26
c short circuit testing for NFS unmounts to avoid hanging
e
s 00011/00004/00390
d D 5.16 91/06/03 15:45:38 mckusick 26 25
c bug fix to allow unmounting of stale filesystems
e
s 00002/00013/00392
d D 5.15 91/04/16 17:35:35 bostic 25 24
c new copyright; att/bsd/shared
e
s 00014/00017/00391
d D 5.14 91/02/27 17:04:47 bostic 24 21
c ANSI fixes
e
s 00003/00005/00391
d R 5.15 90/10/30 09:28:13 bostic 23 22
c ANSI malloc returns void *
e
s 00013/00025/00383
d R 5.14 90/06/01 16:33:15 bostic 22 21
c new copyright, rearrange headers, don't need errno
e
s 00001/00001/00407
d D 5.13 90/03/06 22:03:20 mckusick 21 20
c specify MNT_NOWAIT when getting filesystem information
e
s 00197/00051/00211
d D 5.12 90/02/13 18:06:09 mckusick 20 19
c update for NFS from Borman
e
s 00018/00006/00244
d D 5.11 90/01/05 18:09:28 mckusick 19 18
c now AT&T free
e
s 00009/00002/00241
d D 5.10 89/11/09 22:09:58 mckusick 18 17
c add -f flag for forcible unmount
e
s 00007/00022/00236
d D 5.9 89/10/17 15:25:18 mckusick 17 16
c getmntinfo is now a C library routine
e
s 00002/00005/00255
d D 5.8 89/08/16 17:12:19 mckusick 16 15
c use definition S_IFBLK from stat.h rather than IFBLK from inode.h
e
s 00012/00013/00248
d D 5.7 89/08/16 17:08:46 mckusick 15 14
c lint
e
s 00092/00047/00169
d D 5.6 89/08/16 11:41:15 mckusick 14 13
c look up block special devices so that they can be unmounted
e
s 00002/00027/00214
d D 5.5 89/08/16 00:38:03 mckusick 13 12
c eliminate mtab
e
s 00079/00003/00162
d D 5.4 89/07/11 19:14:12 mckusick 12 11
c update to support NFS (from Rick Macklem)
e
s 00001/00001/00164
d D 5.3 89/06/28 00:10:07 mckusick 11 10
c proper include path
e
s 00007/00010/00158
d D 5.2 89/05/19 15:49:18 mckusick 10 9
c merge in vnodes
e
s 00014/00002/00154
d D 5.1 85/05/28 15:42:25 dist 9 8
c Add copyright
e
s 00062/00019/00094
d D 4.8 83/05/28 13:08:10 sam 8 7
c lots of cleanups; use <mtab.h>; handle quotas more cleanly; add 
c type field to mtab so we can see read-only and quotas
e
s 00001/00001/00112
d D 4.7 83/05/10 15:40:19 sam 7 6
c back to good old umount
e
s 00002/00002/00111
d D 4.6 83/01/02 15:22:29 sam 6 5
c from sun
e
s 00001/00001/00112
d D 4.5 82/12/04 17:11:27 mckusick 5 4
c umount -> unmount
e
s 00067/00062/00046
d D 4.4 82/02/28 21:28:14 wnj 4 3
c cleanup and use perror
e
s 00035/00023/00073
d D 4.3 80/10/16 01:06:45 bill 3 2
c print on standard output; -a reverse order
e
s 00005/00006/00091
d D 4.2 80/10/13 17:04:48 bill 2 1
c adding calls to fstab routines
e
s 00097/00000/00000
d D 4.1 80/10/01 17:29:08 bill 1 0
c date and time created 80/10/01 17:29:08 by bill
e
u
U
t
T
I 9
D 25
/*
E 25
I 25
/*-
E 25
D 19
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 19
I 19
D 29
 * Copyright (c) 1980, 1989 The Regents of the University of California.
 * All rights reserved.
E 29
I 29
 * Copyright (c) 1980, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 29
 *
D 25
 * Redistribution and use in source and binary forms is permitted
 * provided that all copyright information, including this notice,
 * is retained in all such forms, and that any documentation,
 * advertising or other materials related to such distribution and
 * use acknowledge that the software was
 * developed by the University of California, Berkeley.  The name
 * of the University may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 25
I 25
 * %sccs.include.redist.c%
E 25
E 19
 */

E 9
I 8
#ifndef lint
E 8
I 1
D 9
static char *sccsid = "%W% (Berkeley) %G%";
I 8
#endif
E 9
I 9
D 29
char copyright[] =
D 19
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 19
I 19
"%Z% Copyright (c) 1980, 1989 The Regents of the University of California.\n\
E 19
 All rights reserved.\n";
E 29
I 29
static char copyright[] =
"%Z% Copyright (c) 1980, 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 29
D 19
#endif not lint
E 19
I 19
#endif /* not lint */
E 19

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 19
#endif not lint
E 19
I 19
#endif /* not lint */
E 19
E 9
E 8
I 4

E 4
D 8
#include <stdio.h>
#include <fstab.h>
I 4

E 8
E 4
D 24
/*
D 2
 *	umount name
 *
 *	umount -a
 *		This tries to unmount all of the block special file names
 *		as given in /etc/fstab.
E 2
I 2
 * umount
E 2
 */
E 24
I 8
#include <sys/param.h>
I 11
D 12
#include <sys/mount.h>
E 11
E 8

E 12
D 8
#define	NMOUNT	16
#define	NAMSIZ	32
E 8
I 8
D 24
#include <stdio.h>
#include <fstab.h>
E 24
I 14
#include <sys/stat.h>
E 14
D 13
#include <mtab.h>
E 13
I 12
#include <sys/mount.h>
I 24
D 31

E 24
D 14
#ifdef NFS
E 14
D 16
I 14
#include <sys/vnode.h>
#include <ufs/inode.h>
E 16
#ifdef NFS
E 31
E 14
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
I 31

E 31
#include <netdb.h>
#include <rpc/rpc.h>
#include <rpc/pmap_clnt.h>
#include <rpc/pmap_prot.h>
#include <nfs/rpcv2.h>
D 20
#endif
E 20
I 20
D 24
#endif /* NFS */
E 24
I 24
D 31
#endif
E 31
E 24
E 20
E 12
I 10
D 11
#include </usr/src/local/mkmsys/macklem/mkmsys/h/mount.h>
E 11
E 10
E 8

I 30
#include <err.h>
E 30
I 24
#include <fstab.h>
#include <stdio.h>
I 30
#include <stdlib.h>
E 30
#include <string.h>
I 30
#include <unistd.h>
E 30

E 24
D 8
struct mtab {
	char	file[NAMSIZ];
	char	spec[NAMSIZ];
} mtab[NMOUNT];
E 8
I 8
D 13
struct	mtab mtab[NMOUNT];
E 8

E 13
I 4
D 14
char	*rindex();
int	vflag, all, errs;
E 14
I 12
D 31
#ifdef NFS
D 24
extern int errno;
E 24
D 30
int xdr_dir();
D 24
char	*index();
E 24
D 20
#endif
I 14
int	vflag, all, errs;
E 20
I 20
char *nfshost;
E 30
I 30
char	*nfshost;
int	namematch __P((struct hostent *, char *));
int	xdr_dir __P((XDR *, char *));
E 30
D 24
#endif /* NFS */
E 24
I 24
#endif
E 24

E 31
D 30
int	vflag, all, errs, fake;
E 30
I 30
typedef enum { MNTON, MNTFROM } mntwhat;

D 31
int	all, errs, fake, vflag;
E 30
E 20
I 18
D 28
int	fflag = MNT_NOFORCE;
E 28
I 28
int	fflag = 0;
E 28
E 18
D 17
char	*rindex(), *getmntinfo();
E 17
I 17
D 24
char	*rindex(), *getmntname();
E 17
#define MNTON	1
#define MNTFROM	2
E 24
I 24
D 30
char	*getmntname();
E 30
I 30
char	*namelist[] = INITMOUNTNAMES;
int	*typelist;
E 31
I 31
D 36
int	fake, fflag, vflag, *typelist;
E 36
I 36
int	fake, fflag, vflag;
E 36
char	*nfshost;
E 31
E 30

D 30
#define	MNTON	1
#define	MNTFROM	2
E 24
I 20
#define	MNTTYPE 3
E 30
I 30
D 31
int	badtype __P((int, int *));
int	fsnametotype __P((char *));
E 31
I 31
D 36
int	 fsnametotype __P((char *));
E 31
char	*getmntname __P((char *, mntwhat, int *));
D 31
int	*maketypelist __P((char *));
void	umountall __P((int *));
int	umountfs __P((char *, int *));
void	usage __P((void));
E 31
I 31
void	 maketypelist __P((char *));
E 36
I 36
int	 checkvfsname __P((const char *, char **));
char	*getmntname __P((char *, mntwhat, char **));
char	**makevfslist __P((char *));
E 36
int	 selected __P((int));
int	 namematch __P((struct hostent *));
D 36
int	 umountall __P((void));
int	 umountfs __P((char *));
E 36
I 36
int	 umountall __P((char **));
int	 umountfs __P((char *, char **));
E 36
void	 usage __P((void));
int	 xdr_dir __P((XDR *, char *));
E 31
E 30
E 20
E 14
E 12

I 20
D 30
int *typelist, *maketypelist();

I 27
char *namelist[] = INITMOUNTNAMES;

E 30
I 30
int
E 30
E 27
E 20
E 4
main(argc, argv)
D 4
char **argv;
E 4
I 4
	int argc;
D 31
	char **argv;
E 31
I 31
	char *argv[];
E 31
E 4
{
I 20
D 30
	extern char *optarg;
	extern int optind;
E 30
D 31
	int ch;
E 31
I 31
D 37
	int all, ch, errs;
E 37
I 37
	int all, ch, errs, mnts;
E 37
I 36
	char **typelist = NULL;
I 37
	struct statfs *mntbuf;
E 37
E 36
E 31
E 20
D 13
	register struct mtab *mp;
E 13
D 15
	register char *p1, *p2;
E 15
D 13
	int mf;
E 13

I 31
	/* Start disks transferring immediately. */
E 31
I 4
D 20
	argc--, argv++;
E 20
E 4
	sync();
D 13
	mf = open("/etc/mtab", 0);
D 4
	read(mf, (char *)mtab, NMOUNT*2*NAMSIZ);
	if(argc != 2) {
		printf("arg count\n");
		return(1);
E 4
I 4
	read(mf, (char *)mtab, sizeof (mtab));
E 13
D 20
again:
D 6
	if (!strcmp(*argv, "-v")) {
E 6
I 6
	if (argc > 0 && !strcmp(*argv, "-v")) {
E 6
		vflag++;
		argc--, argv++;
		goto again;
E 4
	}
I 18
	if (argc > 0 && !strcmp(*argv, "-f")) {
		fflag = MNT_FORCE;
		argc--, argv++;
		goto again;
	}
E 18
D 4
	if (strcmp(argv[1], "-a") == 0){
E 4
I 4
D 6
	if (!strcmp(*argv, "-a")) {
E 6
I 6
	if (argc > 0 && !strcmp(*argv, "-a")) {
E 6
		all++;
		argc--, argv++;
		goto again;
	}
	if (argc == 0 && !all) {
D 18
		fprintf(stderr, "Usage: umount [ -a ] [ -v ] [ dev ... ]\n");
E 18
I 18
		fprintf(stderr,
			"Usage: umount [ -a ] [ -f ] [ -v ] [ dev ... ]\n");
E 18
		exit(1);
	}
E 20
I 20
D 31
	while ((ch = getopt(argc, argv, "afFh:t:v")) != EOF)
E 31
I 31

	all = 0;
D 37
	while ((ch = getopt(argc, argv, "aFfh:t:v")) != EOF)
E 37
I 37
	while ((ch = getopt(argc, argv, "AaFfh:t:v")) != EOF)
E 37
E 31
D 30
		switch((char)ch) {
		case 'v':
			vflag++;
E 30
I 30
		switch (ch) {
I 37
		case 'A':
			all = 2;
			break;
E 37
		case 'a':
D 31
			all++;
E 31
I 31
			all = 1;
E 31
E 30
			break;
I 31
		case 'F':
			fake = 1;
			break;
E 31
		case 'f':
			fflag = MNT_FORCE;
			break;
D 31
		case 'F':
			fake++;
			break;
D 30
		case 'a':
			all++;
			break;
		case 't':
			typelist = maketypelist(optarg);
			break;
E 30
#ifdef	NFS
		case 'h':
			/* -h flag implies -a, and "-t nfs" if no -t flag */
E 31
I 31
D 37
		case 'h':	/* -h implies -a. */
			all = 1;
E 37
I 37
		case 'h':	/* -h implies -A. */
			all = 2;
E 37
E 31
			nfshost = optarg;
D 31
			all++;
			if (typelist == NULL)
				typelist = maketypelist("nfs");
E 31
			break;
D 31
#endif /* NFS */
E 31
D 30
		case '?':
E 30
I 30
		case 't':
D 31
			typelist = maketypelist(optarg);
E 31
I 31
D 36
			maketypelist(optarg);
E 36
I 36
			if (typelist != NULL)
				errx(1, "only one -t option may be specified.");
			typelist = makevfslist(optarg);
E 36
E 31
			break;
		case 'v':
D 31
			vflag++;
E 31
I 31
			vflag = 1;
E 31
			break;
E 30
		default:
			usage();
			/* NOTREACHED */
		}
	argc -= optind;
	argv += optind;

D 31
	if (argc == 0 && !all)
E 31
I 31
	if (argc == 0 && !all || argc != 0 && all)
E 31
		usage();
I 30

D 31
	if (setfsent() == 0)
		err(1, "%s", FSTAB);

E 31
I 31
	/* -h implies "-t nfs" if no -t flag. */
	if ((nfshost != NULL) && (typelist == NULL))
D 36
		maketypelist("nfs");
E 36
I 36
		typelist = makevfslist("nfs");
E 36
		
E 31
E 30
E 20
D 37
	if (all) {
E 37
I 37
	switch (all) {
	case 2:
		if ((mnts = getmntinfo(&mntbuf, MNT_NOWAIT)) == 0) {
			warn("getmntinfo");
			errs = 1;
			break;
		}
		for (errs = 0, mnts--; mnts > 0; mnts--) {
			if (checkvfsname(mntbuf[mnts].f_fstypename, typelist))
				continue;
			if (umountfs(mntbuf[mnts].f_mntonname, typelist) != 0)
				errs = 1;
		}
		break;
	case 1:
E 37
I 20
D 31
		if (argc > 0)
			usage();
E 20
E 4
D 3
		FILE	*fs_file;
		struct	fstab	fs;
D 2
		if ( (fs_file = fopen(FSTAB, "r")) == NULL){
E 2
I 2
		if ((fs_file = fopen(FSTAB, "r")) == NULL){
E 2
			perror(FSTAB);
			exit(1);
		}
		while (!feof(fs_file)){
			fscanf(fs_file, FSTABFMT, FSTABARG(&fs));
			if (strcmp(fs.fs_file, "/") == 0)
I 2
				continue;
			if (strcmp(fs.fs_type, "rw") &&
			    strcmp(fs.fs_type, "ro"))
E 2
				continue;
			fprintf(stderr, "Unmounting special file %s\n",
				fs.fs_spec);
			fflush(stderr);
			if (umountfs(fs.fs_spec))
				continue;
		}
		fclose(fs_file);
E 3
I 3
D 30
		if (setfsent() == 0)
			perror(FSTAB), exit(1);
E 30
D 20
		umountall();
E 20
I 20
		umountall(typelist);
E 20
D 4
		endfsent();
E 3
	} else {
D 3
		if (umountfs(argv[1]))
E 3
I 3
		int	back;
		if (back = umountfs(argv[1])){
			if (back < 0)
				perror("umount");
E 3
			exit(1);
I 3
		}
E 4
I 4
		exit(0);
E 4
E 3
D 12
	}
E 12
I 12
D 30
	} else
		setfsent();
E 30
I 30
	}

E 30
E 12
D 4
	exit(0);
E 4
I 4
	while (argc > 0) {
D 20
		if (umountfs(*argv++) == 0)
E 20
I 20
		if (umountfs(*argv++, 0) == 0)
E 20
			errs++;
		argc--;
	}
D 30
	exit(errs);
E 30
I 30
	exit(errs ? 1 : 0);
E 31
I 31
		if (setfsent() == 0)
			err(1, "%s", _PATH_FSTAB);
D 36
		errs = umountall();
E 36
I 36
		errs = umountall(typelist);
E 36
D 37
	} else
E 37
I 37
		break;
	case 0:
E 37
		for (errs = 0; *argv != NULL; ++argv)
D 33
			if (umountfs(*argv) == 0)
E 33
I 33
D 36
			if (umountfs(*argv) != 0)
E 36
I 36
			if (umountfs(*argv, typelist) != 0)
E 36
E 33
				errs = 1;
I 37
		break;
	}
E 37
	exit(errs);
E 31
E 30
E 4
}
I 3
D 4
/*
 *	It is important to unmount the files in
 *	reverse! order from the order they were mounted,
 *	so that file systems mounted as children to other
 *	file systems get removed in the right order.
 */
E 4
I 4

I 30
D 31
void
E 30
E 4
D 20
umountall()
E 20
I 20
usage()
E 31
I 31
int
D 36
umountall()
E 36
I 36
umountall(typelist)
	char **typelist;
E 36
E 31
E 20
{
D 4
	struct	fstab	fs;
	struct	fstab	*fsp;
	if ( (fsp = getfsent()) == 0)
E 4
I 4
D 8
	struct fstab fs, *fsp;
E 8
I 8
D 20
	struct fstab *fs, *allocfsent();
E 20
I 20
D 31
	fprintf(stderr,
D 30
		"%s\n%s\n",
		"Usage: umount [-fv] special | node",
E 30
I 30
		"usage:\n%s\n%s\n",
		"  umount [-fv] special | node",
E 30
#ifndef	NFS
D 30
		"    or umount -a[fv] [-t fstypelist]"
E 30
I 30
		"  umount -a[fv] [-t fstypelist]"
E 30
#else
D 30
		"    or umount -a[fv] [-h host] [-t fstypelist]"
E 30
I 30
		"  umount -a[fv] [-h host] [-t fstypelist]"
E 30
#endif
	      );
	exit(1);
}
E 20
E 8

I 30
void
E 30
I 20
umountall(typelist)
D 30
	char **typelist;
E 30
I 30
	int *typelist;
E 30
{
D 30
	register struct fstab *fs;
E 30
D 27
	struct fstab *allocfsent();
E 27
I 27
	char *cp;
E 31
I 30
	struct fstab *fs;
I 31
	int rval, type;
	char *cp;
I 36
	struct vfsconf vfc;
E 36
E 31
E 30
E 27

E 20
D 8
	if ((fsp = getfsent()) == 0)
E 8
I 8
D 15
	if ((fs = getfsent()) == 0)
E 15
I 15
D 27
	if ((fs = getfsent()) == (struct fstab *)0)
E 15
E 8
E 4
		return;
D 8
	fs = *fsp;	/* save info locally; it is static from getfsent() */
E 8
I 8
	fs = allocfsent(fs);
E 8
D 20
	umountall();
E 20
I 20
	umountall(typelist);
E 20
D 8
	if (strcmp(fs.fs_file, "/") == 0)
E 8
I 8
	if (strcmp(fs->fs_file, "/") == 0) {
		freefsent(fs);
E 8
		return;
E 27
I 27
D 31
	while (fs = getfsent()) {
		if (badtype(fsnametotype(fs->fs_vfstype), typelist))
			continue;
E 31
I 31
	while ((fs = getfsent()) != NULL) {
		/* Ignore the root. */
E 31
		if (strcmp(fs->fs_file, "/") == 0)
			continue;
I 31
		/*
		 * !!!
		 * Historic practice: ignore unknown FSTAB_* fields.
		 */
E 31
		if (strcmp(fs->fs_type, FSTAB_RW) &&
		    strcmp(fs->fs_type, FSTAB_RO) &&
		    strcmp(fs->fs_type, FSTAB_RQ))
			continue;
D 30
		cp = (char *)malloc((unsigned)strlen(fs->fs_file) + 1);
		if (cp == NULL) {
			fprintf(stderr, "Out of memory.\n");
			exit(2);
		}
E 30
I 30
D 31
		cp = (char *)malloc((size_t)strlen(fs->fs_file) + 1);
		if (cp == NULL)
			err(2, "malloc");
E 30
		strcpy(cp, fs->fs_file);
		umountall(typelist);
		break;
E 31
I 31
		/* If an unknown file system type, complain. */
D 36
		if ((type = fsnametotype(fs->fs_vfstype)) == MOUNT_NONE) {
E 36
I 36
		if (getvfsbyname(fs->fs_vfstype, &vfc) < 0) {
E 36
			warnx("%s: unknown mount type", fs->fs_vfstype);
			continue;
		}
D 36
		if (!selected(type))
E 36
I 36
		if (checkvfsname(fs->fs_vfstype, typelist))
E 36
			continue;

		/* 
		 * We want to unmount the file systems in the reverse order
		 * that they were mounted.  So, we save off the file name
		 * in some allocated memory, and then call recursively.
		 */
		if ((cp = malloc((size_t)strlen(fs->fs_file) + 1)) == NULL)
			err(1, NULL);
		(void)strcpy(cp, fs->fs_file);
D 36
		rval = umountall();
		return (umountfs(cp) || rval);
E 36
I 36
		rval = umountall(typelist);
		return (umountfs(cp, typelist) || rval);
E 36
E 31
E 27
D 4
	if (strcmp(fs.fs_type, FSTAB_RW) &&
	    strcmp(fs.fs_type, FSTAB_RO))
E 4
I 4
D 8
	if (strcmp(fs.fs_type, FSTAB_RW) && strcmp(fs.fs_type, FSTAB_RO))
E 8
I 8
	}
D 27
	if (strcmp(fs->fs_type, FSTAB_RW) &&
	    strcmp(fs->fs_type, FSTAB_RO) &&
	    strcmp(fs->fs_type, FSTAB_RQ)) {
		freefsent(fs);
E 8
E 4
		return;
E 27
I 27
D 31
	if (fs) {
		(void) umountfs(cp, typelist);
		free(cp);
E 27
D 4
	if (umountfs(fs.fs_spec) < 0)
		fprintf(stdout, "Unmount of special file %s FAILED\n", fs.fs_spec);
	else
		fprintf(stdout, "Unmounted special file %s\n", fs.fs_spec);
	fflush(stdout);
E 4
I 4
D 8
	if (umountfs(fs.fs_spec) < 0) {
		perror(fs.fs_spec);
		return;
E 8
	}
E 31
I 31
	return (0);
E 31
I 8
D 10
	if (umountfs(fs->fs_spec) < 0)
		perror(fs->fs_spec);
E 10
I 10
D 14
	if (umountfs(fs->fs_file) < 0)
		perror(fs->fs_file);
E 14
I 14
D 20
	(void) umountfs(fs->fs_file);
E 20
I 20
D 27
	(void) umountfs(fs->fs_file, typelist);
E 20
E 14
E 10
	freefsent(fs);
E 27
E 8
E 4
}
E 3

I 30
int
E 30
I 8
D 27
struct fstab *
allocfsent(fs)
	register struct fstab *fs;
{
	register struct fstab *new;
	register char *cp;
D 24
	char *malloc();
E 24

D 15
	new = (struct fstab *)malloc(sizeof (*fs));
	cp = malloc(strlen(fs->fs_file) + 1);
E 15
I 15
	new = (struct fstab *)malloc((unsigned)sizeof (*fs));
D 24
	cp = malloc((unsigned)strlen(fs->fs_file) + 1);
E 24
I 24
	cp = (char *)malloc((unsigned)strlen(fs->fs_file) + 1);
E 24
E 15
	strcpy(cp, fs->fs_file);
	new->fs_file = cp;
D 15
	cp = malloc(strlen(fs->fs_type) + 1);
E 15
I 15
D 24
	cp = malloc((unsigned)strlen(fs->fs_type) + 1);
E 24
I 24
	cp = (char *)malloc((unsigned)strlen(fs->fs_type) + 1);
E 24
E 15
	strcpy(cp, fs->fs_type);
	new->fs_type = cp;
D 15
	cp = malloc(strlen(fs->fs_spec) + 1);
E 15
I 15
D 24
	cp = malloc((unsigned)strlen(fs->fs_spec) + 1);
E 24
I 24
	cp = (char *)malloc((unsigned)strlen(fs->fs_spec) + 1);
E 24
E 15
	strcpy(cp, fs->fs_spec);
	new->fs_spec = cp;
	new->fs_passno = fs->fs_passno;
	new->fs_freq = fs->fs_freq;
	return (new);
}

freefsent(fs)
	register struct fstab *fs;
{

	if (fs->fs_file)
		free(fs->fs_file);
	if (fs->fs_spec)
		free(fs->fs_spec);
	if (fs->fs_type)
		free(fs->fs_type);
	free((char *)fs);
}

E 27
E 8
D 4
int umountfs(name)
	char	*name;
E 4
I 4
D 13
struct	mtab zeromtab;

E 13
D 20
umountfs(name)
E 20
I 20
D 31
umountfs(name, typelist)
E 31
I 31
D 36
umountfs(name)
E 36
I 36
umountfs(name, typelist)
E 36
E 31
E 20
	char *name;
I 36
	char **typelist;
E 36
I 20
D 31
	int *typelist;
E 31
E 20
E 4
{
D 4
	register	char	*p1, *p2;
	register	struct	mtab	*mp;
	int	mf;
E 4
I 4
D 14
	register char *p1, *p2;
D 13
	register struct	mtab *mp;
	int mf;
E 13
I 8
	struct fstab *fs;
E 14
I 14
D 30
	char *mntpt;
	struct stat stbuf;
I 20
	int type;
E 30
E 20
E 14
I 12
D 31
#ifdef NFS
E 31
D 30
	register CLIENT *clp;
E 30
I 30
	enum clnt_stat clnt_stat;
D 31
	CLIENT *clp;
	char *delimp, *hostp;
E 30
D 20
	struct hostent *hp;
E 20
I 20
	struct hostent *hp = 0;
E 31
I 31
	struct hostent *hp;
E 31
E 20
	struct sockaddr_in saddr;
I 31
	struct stat sb;
E 31
	struct timeval pertry, try;
D 30
	enum clnt_stat clnt_stat;
E 30
D 31
	int so = RPC_ANYSOCK;
D 15
	u_short tport;
E 15
D 30
	char *hostp, *delimp;
E 30
D 20
#endif
E 20
I 20
#endif /* NFS */
I 30
	char *mntpt;
	struct stat stbuf;
	int type;
	char rname[MAXPATHLEN];
E 31
I 31
	CLIENT *clp;
D 36
	int so, type;
	char *delimp, *hostp, *mntpt, rname[MAXPATHLEN];
E 36
I 36
	int so;
	char *type, *delimp, *hostp, *mntpt, rname[MAXPATHLEN];
E 36
E 31
E 30
E 20
E 12
E 8
E 4

I 30
	if (realpath(name, rname) == NULL) {
		warn("%s", rname);
D 33
		return (0);
E 33
I 33
		return (1);
E 33
	}

	name = rname;

E 30
I 8
D 10
	fs = getfsfile(name);
E 10
I 10
D 14
	fs = getfsspec(name);
E 10
	if (fs != NULL)
D 10
		name = fs->fs_spec;
E 8
D 5
	if (umount(name) < 0) {
E 5
I 5
D 7
	if (unmount(name) < 0) {
E 7
I 7
	if (umount(name) < 0) {
E 10
I 10
		name = fs->fs_file;
I 12
#ifdef NFS
	else
		fs = getfsfile(name);
#endif
E 12
	if (umount(name, MNT_NOFORCE) < 0) {
E 10
E 7
E 5
D 3
		perror("umount");
		return(1);
E 3
I 3
D 4
		return(-1);
E 4
I 4
		perror(name);
E 14
I 14
D 31
	if (stat(name, &stbuf) < 0) {
D 17
		if ((mntpt = getmntinfo(name, MNTON)) == 0)
E 17
I 17
D 20
		if ((mntpt = getmntname(name, MNTON)) == 0)
E 20
I 20
D 26
		if ((mntpt = getmntname(name, MNTON, &type)) == 0)
E 26
I 26
D 30
		if (getmntname(name, MNTFROM, &type) != 0)
			mntpt = name;
		else if ((mntpt = getmntname(name, MNTON, &type)) == 0) {
			fprintf(stderr, "%s: not currently mounted\n", name);
E 30
I 30
		if (((mntpt = getmntname(name, MNTFROM, &type)) == 0) &&
		    ((mntpt = getmntname(name, MNTON, &type)) == 0)) {
E 31
I 31
	if (stat(name, &sb) < 0) {
		if (((mntpt = getmntname(name, MNTFROM, &type)) == NULL) &&
		    ((mntpt = getmntname(name, MNTON, &type)) == NULL)) {
E 31
			warnx("%s: not currently mounted", name);
E 30
E 26
E 20
E 17
D 31
			return (0);
E 31
I 31
			return (1);
E 31
I 26
		}
E 26
D 16
	} else if ((stbuf.st_mode & IFMT) == IFBLK) {
E 16
I 16
D 31
	} else if ((stbuf.st_mode & S_IFMT) == S_IFBLK) {
E 16
D 17
		if ((mntpt = getmntinfo(name, MNTON)) == 0)
E 17
I 17
D 20
		if ((mntpt = getmntname(name, MNTON)) == 0)
E 20
I 20
D 26
		if ((mntpt = getmntname(name, MNTON, &type)) == 0)
E 26
I 26
		if ((mntpt = getmntname(name, MNTON, &type)) == 0) {
E 31
I 31
	} else if (S_ISBLK(sb.st_mode)) {
		if ((mntpt = getmntname(name, MNTON, &type)) == NULL) {
E 31
D 30
			fprintf(stderr, "%s: not currently mounted\n", name);
E 30
I 30
			warnx("%s: not currently mounted", name);
E 30
E 26
E 20
E 17
D 31
			return (0);
E 31
I 31
			return (1);
E 31
I 26
		}
E 26
D 16
	} else if ((stbuf.st_mode & IFMT) == IFDIR) {
E 16
I 16
D 31
	} else if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
E 31
I 31
	} else if (S_ISDIR(sb.st_mode)) {
E 31
E 16
		mntpt = name;
D 17
		if ((name = getmntinfo(mntpt, MNTFROM)) == 0)
E 17
I 17
D 20
		if ((name = getmntname(mntpt, MNTFROM)) == 0)
E 20
I 20
D 26
		if ((name = getmntname(mntpt, MNTFROM, &type)) == 0)
E 26
I 26
D 30
		if (getmntname(mntpt, MNTFROM, &type) == 0) {
			fprintf(stderr, "%s: not currently mounted\n", name);
E 30
I 30
D 31
		if ((name = getmntname(mntpt, MNTFROM, &type)) == 0) {
E 31
I 31
		if ((name = getmntname(mntpt, MNTFROM, &type)) == NULL) {
E 31
			warnx("%s: not currently mounted", mntpt);
E 30
E 26
E 20
E 17
D 31
			return (0);
E 31
I 31
			return (1);
E 31
I 26
		}
E 26
	} else {
D 15
		fprintf(stderr, "%s: not a directory or special device\n");
E 15
I 15
D 30
		fprintf(stderr, "%s: not a directory or special device\n",
			name);
E 30
I 30
		warnx("%s: not a directory or special device", name);
E 30
E 15
E 14
D 31
		return (0);
E 31
I 31
		return (1);
E 31
E 4
E 3
	}
I 14
D 17
	if (umount(mntpt, MNT_NOFORCE) < 0) {
E 17
I 17
D 18
	if (unmount(mntpt, MNT_NOFORCE) < 0) {
E 18
I 18
D 20
	if (unmount(mntpt, fflag) < 0) {
E 20
I 20

D 31
	if (badtype(type, typelist))
D 30
		return(1);
E 30
I 30
		return (1);
E 30
#ifdef NFS
E 31
I 31
D 36
	if (!selected(type))
E 36
I 36
	if (checkvfsname(type, typelist))
E 36
D 33
		return (0);
E 33
I 33
		return (1);
E 33

E 31
D 30
	if ((delimp = index(name, '@')) != NULL) {
E 30
I 30
D 35
	if ((delimp = strchr(name, '@')) != NULL) {
E 30
		hostp = delimp + 1;
		*delimp = '\0';
		hp = gethostbyname(hostp);
		*delimp = '@';
D 30
	} else if ((delimp = index(name, ':')) != NULL) {
E 30
I 30
	} else if ((delimp = strchr(name, ':')) != NULL) {
E 30
		*delimp = '\0';
		hostp = name;
		hp = gethostbyname(hostp);
D 31
		name = delimp+1;
E 31
I 31
		name = delimp + 1;
E 31
		*delimp = ':';
D 31
	}
E 31
I 31
	} else
		hp = NULL;
E 35
I 35
	hp = NULL;
D 36
	if (type == MOUNT_NFS) {
E 36
I 36
	if (!strcmp(type, "nfs")) {
E 36
		if ((delimp = strchr(name, '@')) != NULL) {
			hostp = delimp + 1;
			*delimp = '\0';
			hp = gethostbyname(hostp);
			*delimp = '@';
		} else if ((delimp = strchr(name, ':')) != NULL) {
			*delimp = '\0';
			hostp = name;
			hp = gethostbyname(hostp);
			name = delimp + 1;
			*delimp = ':';
		}
	}

E 35
	if (!namematch(hp))
D 33
		return (0);
E 33
I 33
		return (1);
E 33
E 31

D 31
	if (!namematch(hp, nfshost))
D 30
		return(1);
E 30
I 30
		return (1);
E 30
#endif	/* NFS */
	if (!fake && unmount(mntpt, fflag) < 0) {
E 20
E 18
E 17
D 30
		perror(mntpt);
E 30
I 30
		warn("%s", mntpt);
E 31
I 31
	if (vflag)
		(void)printf("%s: unmount from %s\n", name, mntpt);
	if (fake)
E 31
E 30
		return (0);
I 31

	if (unmount(mntpt, fflag) < 0) {
		warn("%s", mntpt);
		return (1);
E 31
	}
D 31
	if (vflag)
D 30
		fprintf(stderr, "%s: Unmounted from %s\n", name, mntpt);
E 30
I 30
		warnx("%s: unmounted from %s", name, mntpt);
E 31
E 30
E 14
I 12
D 20
#ifdef NFS
D 14
	if (fs != NULL) {
		if ((delimp = index(fs->fs_spec, '@')) != NULL) {
			hostp = delimp+1;
			*delimp = '\0';
		} else {
			goto out;
E 14
I 14
	if ((delimp = index(name, '@')) != NULL) {
		hostp = delimp + 1;
E 20
I 20

D 31
#ifdef	NFS
D 30
	if (!fake && hp != NULL && (fflag & MNT_FORCE) == 0) {
E 30
I 30
	if (!fake && (hp != NULL) && ((fflag & MNT_FORCE) == 0)) {
E 31
I 31
	if ((hp != NULL) && !(fflag & MNT_FORCE)) {
E 31
E 30
E 20
		*delimp = '\0';
D 20
	} else {
		return (1);
	}
	if ((hp = gethostbyname(hostp)) != NULL) {
E 20
D 30
		bcopy(hp->h_addr,(caddr_t)&saddr.sin_addr,hp->h_length);
E 30
I 30
D 31
		bzero(&saddr, sizeof(saddr));
E 31
I 31
		memset(&saddr, 0, sizeof(saddr));
E 31
E 30
		saddr.sin_family = AF_INET;
		saddr.sin_port = 0;
I 30
D 31
		bcopy(hp->h_addr, &saddr.sin_addr, hp->h_length);
E 31
I 31
		memmove(&saddr.sin_addr, hp->h_addr, hp->h_length);
E 31
E 30
		pertry.tv_sec = 3;
		pertry.tv_usec = 0;
D 31
		if ((clp = clntudp_create(&saddr, RPCPROG_MNT, RPCMNT_VER1,
		    pertry, &so)) == NULL) {
E 31
I 31
		so = RPC_ANYSOCK;
		if ((clp = clntudp_create(&saddr,
		    RPCPROG_MNT, RPCMNT_VER1, pertry, &so)) == NULL) {
E 31
			clnt_pcreateerror("Cannot MNT PRC");
			return (1);
E 14
		}
D 14
		if ((hp = gethostbyname(hostp)) != NULL) {
			bcopy(hp->h_addr,(caddr_t)&saddr.sin_addr,hp->h_length);
			saddr.sin_family = AF_INET;
			saddr.sin_port = 0;
			pertry.tv_sec = 3;
			pertry.tv_usec = 0;
			if ((clp = clntudp_create(&saddr, RPCPROG_MNT,
				RPCMNT_VER1, pertry, &so)) == NULL) {
				clnt_pcreateerror("Cannot MNT PRC");
				goto out;
			}
			clp->cl_auth = authunix_create_default();
			try.tv_sec = 20;
			try.tv_usec = 0;
			clnt_stat = clnt_call(clp, RPCMNT_UMOUNT, xdr_dir, fs->fs_spec,
				xdr_void, (caddr_t)0, try);
			if (clnt_stat != RPC_SUCCESS) {
				clnt_perror(clp, "Bad MNT RPC");
				goto out;
			}
			auth_destroy(clp->cl_auth);
			clnt_destroy(clp);
E 14
I 14
		clp->cl_auth = authunix_create_default();
		try.tv_sec = 20;
		try.tv_usec = 0;
D 31
		clnt_stat = clnt_call(clp, RPCMNT_UMOUNT, xdr_dir, name,
			xdr_void, (caddr_t)0, try);
E 31
I 31
		clnt_stat = clnt_call(clp,
		    RPCMNT_UMOUNT, xdr_dir, name, xdr_void, (caddr_t)0, try);
E 31
		if (clnt_stat != RPC_SUCCESS) {
			clnt_perror(clp, "Bad MNT RPC");
			return (1);
E 14
		}
I 14
		auth_destroy(clp->cl_auth);
		clnt_destroy(clp);
E 14
D 13
	} else
		fprintf(stderr, "Warning: no /etc/fstab entry found\n");
E 13
I 13
	}
E 13
D 14
out:
E 14
D 20
#endif NFS
E 20
I 20
D 31
#endif /* NFS */
E 20
E 12
D 4
	p1 = name;
	while(*p1++)
		;
	p1--;
	while(*--p1 == '/')
		*p1 = '\0';
	while(p1 > name && *--p1 != '/')
		;
	if(*p1 == '/')
		p1++;
	name = p1;
E 4
I 4
D 14
	if (vflag)
		fprintf(stderr, "%s: Unmounted\n", name);
E 14
D 10
	while ((p1 = rindex(name, '/')) && p1[1] == 0)
		*p1 = 0;
	if (p1)
		name = p1 + 1;
E 10
E 4
D 13
	for (mp = mtab; mp < &mtab[NMOUNT]; mp++) {
D 4
		p1 = name;
		p2 = &mp->spec[0];
		while (*p1++ == *p2)
			if (*p2++ == 0) {
				for (p1 = mp->file; p1 < &mp->file[NAMSIZ*2];)
					*p1++ = 0;
				mp = &mtab[NMOUNT];
				while ((--mp)->file[0] == 0);
				mf = creat("/etc/mtab", 0644);
				write(mf, (char *)mtab, (mp-mtab+1)*2*NAMSIZ);
				return(0);
			}
E 4
I 4
D 8
		if (strncmp(mp->spec, name, sizeof (mp->spec)))
E 8
I 8
D 10
		if (strncmp(mp->m_dname, name, sizeof (mp->m_dname)))
E 10
I 10
		if (strncmp(mp->m_path, name, sizeof (mp->m_path)))
E 10
E 8
			continue;
		*mp = zeromtab;
		for (mp = &mtab[NMOUNT]; mp >= mtab; mp--)
D 8
			if (mp->file[0])
E 8
I 8
			if (mp->m_path[0])
E 8
				break;
		mp++;
		mf = creat("/etc/mtab", 0644);
		write(mf, (char *)mtab, (mp-mtab) * sizeof (struct mtab));
		return (1);
E 4
	}
D 4
	printf("%s not in mount table\n", name);
	return(1);
E 4
I 4
	fprintf(stderr, "%s: Not mounted\n", name);
	return (0);
E 13
I 13
	return (1);
E 31
I 31
	return (0);
E 31
I 14
}

char *
D 17
getmntinfo(name, what)
E 17
I 17
D 20
getmntname(name, what)
E 20
I 20
getmntname(name, what, type)
E 20
E 17
	char *name;
D 30
	int what;
E 30
I 30
	mntwhat what;
E 30
I 20
D 36
	int *type;
E 36
I 36
	char **type;
E 36
E 20
{
D 15
	long mntsize, i;
	struct statfs statfsbuf, *mntbuf;
E 15
I 15
D 30
	int mntsize, i;
E 30
I 30
D 31
	int i, mntsize;
E 31
E 30
D 37
	struct statfs *mntbuf;
I 31
	int i, mntsize;
E 37
I 37
	static struct statfs *mntbuf;
	static int mntsize;
	int i;
E 37
E 31
E 15

D 15
	if ((mntsize = getfsstat(0, 0)) < 0) {
E 15
I 15
D 17
	if ((mntsize = getfsstat((struct statfs *)0, 0)) < 0) {
E 17
I 17
D 21
	if ((mntsize = getmntinfo(&mntbuf)) == 0) {
E 21
I 21
D 37
	if ((mntsize = getmntinfo(&mntbuf, MNT_NOWAIT)) == 0) {
E 37
I 37
	if (mntbuf == NULL &&
	    (mntsize = getmntinfo(&mntbuf, MNT_NOWAIT)) == 0) {
E 37
E 21
E 17
E 15
D 30
		perror("umount");
		return (0);
E 30
I 30
		warn("getmntinfo");
		return (NULL);
E 30
	}
D 17
	mntbuf = 0;
	do {
		if (mntbuf)
D 15
			free(mntbuf);
E 15
I 15
			free((char *)mntbuf);
E 15
		i = (mntsize + 1) * sizeof(struct statfs);
D 15
		if ((mntbuf = (struct statfs *)malloc(i)) == 0) {
E 15
I 15
		if ((mntbuf = (struct statfs *)malloc((unsigned)i)) == 0) {
E 15
			fprintf(stderr,
				"no space for umount table buffer\n");
			return (0);
		}
		if ((mntsize = getfsstat(mntbuf, i)) < 0) {
			perror("umount");
			return (0);
		}
	} while (i == mntsize * sizeof(struct statfs));
E 17
	for (i = 0; i < mntsize; i++) {
D 20
		if (what == MNTON && !strcmp(mntbuf[i].f_mntfromname, name))
E 20
I 20
D 31
		if (what == MNTON && !strcmp(mntbuf[i].f_mntfromname, name)) {
E 31
I 31
		if ((what == MNTON) && !strcmp(mntbuf[i].f_mntfromname, name)) {
E 31
			if (type)
D 36
				*type = mntbuf[i].f_type;
E 36
I 36
				*type = mntbuf[i].f_fstypename;
E 36
E 20
			return (mntbuf[i].f_mntonname);
D 20
		if (what == MNTFROM && !strcmp(mntbuf[i].f_mntonname, name))
E 20
I 20
		}
D 31
		if (what == MNTFROM && !strcmp(mntbuf[i].f_mntonname, name)) {
E 31
I 31
		if ((what == MNTFROM) && !strcmp(mntbuf[i].f_mntonname, name)) {
E 31
			if (type)
D 36
				*type = mntbuf[i].f_type;
E 36
I 36
				*type = mntbuf[i].f_fstypename;
E 36
E 20
			return (mntbuf[i].f_mntfromname);
I 20
		}
E 20
	}
D 26
	fprintf(stderr, "%s: not currently mounted\n", name);
E 26
D 30
	return (0);
E 30
I 30
	return (NULL);
E 30
E 14
E 13
E 4
D 36
}
I 12

D 20
#ifdef NFS
E 20
I 20
D 31
static int skipvfs;
E 31
I 31
static enum { IN_LIST, NOT_IN_LIST } which;
E 31

I 30
int
E 30
D 31
badtype(type, typelist)
E 31
I 31
selected(type)
E 31
	int type;
D 31
	int *typelist;
E 31
{
I 32
	int *av;

E 32
D 31
	if (typelist == 0)
D 30
		return(0);
E 30
I 30
		return (0);

E 30
	while (*typelist) {
E 31
I 31
	/* If no type specified, it's always selected. */
	if (typelist == NULL)
		return (1);
D 32
	for (; *typelist != MOUNT_NONE; ++typelist)
E 32
I 32
	for (av = typelist; *av != NULL; ++av)
E 32
E 31
		if (type == *typelist)
D 30
			return(skipvfs);
E 30
I 30
D 31
			return (skipvfs);
E 30
		typelist++;
	}
D 30
	return(!skipvfs);
E 30
I 30
	return (!skipvfs);
E 31
I 31
			return (which == IN_LIST ? 1 : 0);
	return (which == IN_LIST ? 0 : 1);
E 31
E 30
}

D 31
int *
E 31
I 31
void
E 31
maketypelist(fslist)
	char *fslist;
{
D 30
	register char *nextcp;
	register int *av, i;
E 30
I 30
D 31
	char *nextcp;
E 31
	int *av, i;
I 31
	char *nextcp;
E 31
E 30
D 24
	char *malloc();
E 24

D 31
	if (fslist == NULL)
D 30
		return(NULL);
E 30
I 30
		return (NULL);
E 31
I 31
	if ((fslist == NULL) || (fslist[0] == '\0'))
		errx(1, "empty type list");
E 31

I 31
	/*
	 * XXX
	 * Note: the syntax is "noxxx,yyy" for no xxx's and
	 * no yyy's, not the more intuitive "noyyy,noyyy".
	 */
E 31
E 30
	if (fslist[0] == 'n' && fslist[1] == 'o') {
		fslist += 2;
D 31
		skipvfs = 1;
E 31
I 31
		which = NOT_IN_LIST;
E 31
	} else
D 31
		skipvfs = 0;
	for (i = 0, nextcp = fslist; *nextcp; nextcp++)
E 31
I 31
		which = IN_LIST;

	/* Count the number of types. */
	for (i = 0, nextcp = fslist; *nextcp != NULL; ++nextcp)
E 31
		if (*nextcp == ',')
			i++;
I 30

E 30
D 31
	av = (int *)malloc((i+2) * sizeof(int));
	if (av == NULL)
D 30
		return(NULL);
E 30
I 30
		return (NULL);

E 30
	for (i = 0; fslist; fslist = nextcp) {
D 30
		if (nextcp = index(fslist, ','))
E 30
I 30
		if (nextcp = strchr(fslist, ','))
E 31
I 31
	/* Build an array of that many types. */
	if ((av = typelist = malloc((i + 2) * sizeof(int))) == NULL)
		err(1, NULL);
	for (i = 0; fslist != NULL; fslist = nextcp, ++i) {
		if ((nextcp = strchr(fslist, ',')) != NULL)
E 31
E 30
			*nextcp++ = '\0';
D 27
		if (strcmp(fslist, "ufs") == 0)
			av[i++] = MOUNT_UFS;
		else if (strcmp(fslist, "nfs") == 0)
			av[i++] = MOUNT_NFS;
		else if (strcmp(fslist, "mfs") == 0)
			av[i++] = MOUNT_MFS;
		else if (strcmp(fslist, "pc") == 0)
			av[i++] = MOUNT_PC;
E 27
I 27
D 31
		av[i++] = fsnametotype(fslist);
E 31
I 31
		av[i] = fsnametotype(fslist);
		if (av[i] == MOUNT_NONE)
			errx(1, "%s: unknown mount type", fslist);
E 31
E 27
	}
D 31
	av[i++] = 0;
D 30
	return(av);
E 30
I 30
	return (av);
E 31
I 31
	/* Terminate the array. */
	av[i++] = MOUNT_NONE;
E 31
E 30
I 27
}

I 30
int
E 30
fsnametotype(name)
	char *name;
{
D 31
	char **cp;
E 31
I 31
	static char const *namelist[] = INITMOUNTNAMES;
	char const **cp;
E 31

D 31
	for (cp = namelist; *cp; cp++)
E 31
I 31
	for (cp = namelist; *cp; ++cp)
E 31
		if (strcmp(name, *cp) == 0)
			return (cp - namelist);
	return (MOUNT_NONE);
E 36
E 27
}

D 30
#ifdef	NFS
E 30
I 30
D 31
#ifdef NFS
E 31
int
E 30
D 31
namematch(hp, nfshost)
E 31
I 31
namematch(hp)
E 31
	struct hostent *hp;
D 31
	char *nfshost;
E 31
{
D 30
	register char *cp;
	register char **np;
E 30
I 30
D 31
	char *cp;
	char **np;
E 31
I 31
	char *cp, **np;
E 31
E 30

D 31
	if (hp == NULL || nfshost == NULL)
E 31
I 31
	if ((hp == NULL) || (nfshost == NULL))
E 31
D 30
		return(1);
E 30
I 30
		return (1);

E 30
	if (strcasecmp(nfshost, hp->h_name) == 0)
D 30
		return(1);
	if (cp = index(hp->h_name, '.')) {
E 30
I 30
		return (1);

D 31
	if (cp = strchr(hp->h_name, '.')) {
E 31
I 31
	if ((cp = strchr(hp->h_name, '.')) != NULL) {
E 31
E 30
		*cp = '\0';
		if (strcasecmp(nfshost, hp->h_name) == 0)
D 30
			return(1);
E 30
I 30
			return (1);
E 30
	}
	for (np = hp->h_aliases; *np; np++) {
		if (strcasecmp(nfshost, *np) == 0)
D 30
			return(1);
		if (cp = index(*np, '.')) {
E 30
I 30
			return (1);
D 31
		if (cp = strchr(*np, '.')) {

E 31
I 31
		if ((cp = strchr(*np, '.')) != NULL) {
E 31
E 30
			*cp = '\0';
			if (strcasecmp(nfshost, *np) == 0)
D 30
				return(1);
E 30
I 30
				return (1);
E 30
		}
	}
D 30
	return(0);
E 30
I 30
	return (0);
E 30
}

E 20
/*
 * xdr routines for mount rpc's
 */
I 30
int
E 30
xdr_dir(xdrsp, dirp)
	XDR *xdrsp;
	char *dirp;
{
	return (xdr_string(xdrsp, &dirp, RPCMNT_PATHLEN));
}
D 20
#endif NFS
E 20
I 20
D 31
#endif /* NFS */
E 31
I 31

void
usage()
{
	(void)fprintf(stderr,
	    "usage: %s\n       %s\n",
	    "umount [-fv] [-t fstypelist] special | node",
	    "umount -a[fv] [-h host] [-t fstypelist]");
	exit(1);
}
E 31
E 20
E 12
E 1
