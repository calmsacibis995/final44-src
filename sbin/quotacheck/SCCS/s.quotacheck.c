h44612
s 00002/00002/00581
d D 8.6 95/04/28 10:56:19 bostic 36 35
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00001/00000/00582
d D 8.5 94/11/22 16:50:46 mckusick 35 34
c needs queue.h
e
s 00009/00037/00573
d D 8.4 94/08/17 21:51:50 mckusick 34 33
c bug when checking multiple filesystems; use library err function
c (from mycroft)
e
s 00002/00001/00608
d D 8.3 94/01/29 06:05:01 bostic 33 32
c uninitialized variable
e
s 00001/00001/00608
d D 8.2 93/09/23 19:37:17 bostic 32 31
c changes for 4.4BSD-Lite requested by USL
e
s 00005/00005/00604
d D 8.1 93/06/05 11:10:16 bostic 31 30
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00608
d D 5.19 93/02/15 10:45:39 ralph 30 29
c use SEEK_SET #define instead of constant.
e
s 00106/00065/00503
d D 5.18 92/06/20 14:24:05 bostic 29 28
c broken by quads; welcome it to ANSI.
e
s 00003/00003/00565
d D 5.17 91/11/11 11:37:08 bostic 28 27
c break UFS up into FFS/UFS/LFS/MFS
e
s 00023/00018/00545
d D 5.16 91/02/28 17:56:38 bostic 27 26
c ANSI, minor cleanups.
e
s 00004/00000/00559
d D 5.15 90/09/27 14:00:50 mckusick 26 25
c have to initialize quota variables here rather than in quota.h
e
s 00001/00011/00558
d D 5.14 90/06/01 16:20:03 bostic 25 24
c new copyright notice
e
s 00077/00033/00492
d D 5.13 90/05/06 17:41:16 mckusick 24 23
c allow fstab to override default quota file name
e
s 00380/00313/00145
d D 5.12 90/05/04 23:19:59 mckusick 23 22
c first cut at new quotas
e
s 00009/00007/00449
d D 5.11 89/07/30 10:57:19 bostic 22 21
c vnodes
e
s 00010/00005/00446
d D 5.10 88/06/18 14:34:40 bostic 21 20
c install approved copyright notice
e
s 00010/00004/00441
d D 5.9 88/05/20 12:15:00 bostic 20 19
c add Berkeley specific header
e
s 00001/00001/00444
d D 5.8 87/10/22 10:37:29 bostic 19 18
c ANSI C; sprintf now returns an int.
e
s 00004/00005/00441
d D 5.7 87/02/23 17:40:04 mckusick 18 17
c convert SBLOCK to SBOFF; generalize use of dev_bsize
e
s 00038/00018/00408
d D 5.6 85/11/03 16:40:57 serge 17 14
c improve performance by using two FILE pointers instead of one
e
s 00032/00018/00408
d R 5.6 85/11/02 21:33:37 serge 16 14
c improve performance by using two FILE pointers instead of one
e
s 00031/00017/00409
d R 5.6 85/11/02 20:22:13 serge 15 14
c improve performance by using two FILE pointers instead of one
e
s 00003/00003/00423
d D 5.5 85/09/16 21:54:23 serge 14 13
c use raw device even if disk name begins with 'r'
e
s 00112/00043/00314
d D 5.4 85/09/15 17:57:44 serge 13 9
c added fsck like -p flag (from ulysses!amw)
e
s 00112/00043/00314
d R 5.4 85/09/15 17:52:31 serge 12 9
c added fsck like -p flag (from ulysses!amw)
e
s 00107/00041/00316
d R 5.4 85/09/15 17:08:41 serge 11 9
c added fsck like -p flag (from ulysses!amw)
e
s 00105/00039/00318
d R 5.4 85/09/15 17:01:05 serge 10 9
c add fsck like -p flag (from ulysses!amw)
e
s 00032/00019/00325
d D 5.3 85/09/09 19:34:46 serge 9 8
c do not unset quotas of users who have 0 blocks on file system
e
s 00008/00002/00336
d D 5.2 85/06/17 20:42:30 mckusick 8 7
c avoid brain damage in stdio
e
s 00014/00002/00324
d D 5.1 85/05/30 19:54:39 mckusick 7 6
c Add copyright
e
s 00009/00001/00317
d D 4.6 85/05/24 17:00:53 mckusick 6 5
c in verbose mode, warn of kernels not compiled for quotas
e
s 00009/00004/00309
d D 4.5 85/03/19 16:22:57 mckusick 5 4
c zero out quotas for deleted uids
e
s 00002/00002/00311
d D 4.4 83/06/22 16:24:01 mckusick 4 3
c have to use the value before zeroing it!
e
s 00029/00006/00284
d D 4.3 83/05/27 15:16:55 mckusick 3 2
c translate uid's to names; zero out blocks after using them
e
s 00182/00206/00108
d D 4.2 83/05/24 13:13:11 mckusick 2 1
c use fstab, add -a and -v flags
e
s 00314/00000/00000
d D 4.1 83/05/22 14:52:26 mckusick 1 0
c date and time created 83/05/22 14:52:26 by mckusick
e
u
U
t
T
I 7
/*
D 23
 * Copyright (c) 1980 Regents of the University of California.
E 23
I 23
D 31
 * Copyright (c) 1980, 1990 Regents of the University of California.
E 23
D 20
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 20
I 20
 * All rights reserved.
E 31
I 31
 * Copyright (c) 1980, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 31
 *
I 23
 * This code is derived from software contributed to Berkeley by
 * Robert Elz at The University of Melbourne.
 *
E 23
D 25
 * Redistribution and use in source and binary forms are permitted
D 21
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 21
I 21
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
E 25
I 25
 * %sccs.include.redist.c%
E 25
E 21
E 20
 */

E 7
I 1
D 2
#ifndef lit
static char sccsid[] = "%W% (Melbourne) %G%";
E 2
I 2
#ifndef lint
D 7
static char sccsid[] = "%W% (Berkeley, Melbourne) %G%";
E 2
#endif
E 7
I 7
D 31
char copyright[] =
D 23
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 23
I 23
"%Z% Copyright (c) 1980, 1990 Regents of the University of California.\n\
E 23
 All rights reserved.\n";
E 31
I 31
static char copyright[] =
"%Z% Copyright (c) 1980, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 31
D 20
#endif not lint
E 20
I 20
#endif /* not lint */
E 20

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 20
#endif not lint
E 20
I 20
#endif /* not lint */
E 20
E 7

/*
D 23
 * Fix up / report on disc quotas & usage
E 23
I 23
 * Fix up / report on disk quotas & usage
E 23
 */
D 22
#include <stdio.h>
#include <ctype.h>
#include <signal.h>
I 6
#include <errno.h>
E 22
E 6
D 3
#include <pwd.h>
E 3
#include <sys/param.h>
I 27
#include <sys/stat.h>
I 35
#include <sys/queue.h>
E 35
I 29

E 29
E 27
D 22
#include <sys/inode.h>
#include <sys/fs.h>
D 3
#define	QUOTA
E 3
#include <sys/quota.h>
E 22
I 22
D 23
#include <sys/time.h>
#include <sys/vnode.h>
#include <sys/signal.h>
E 22
#include <sys/stat.h>
I 13
#include <sys/wait.h>
I 22
#include <ufs/inode.h>
E 23
I 23
D 28
#include <ufs/dinode.h>
E 23
#include <ufs/fs.h>
#include <ufs/quota.h>
E 28
I 28
#include <ufs/ufs/dinode.h>
#include <ufs/ufs/quota.h>
#include <ufs/ffs/fs.h>
I 29

E 29
E 28
I 27
#include <fcntl.h>
E 27
E 22
E 13
I 2
#include <fstab.h>
I 3
#include <pwd.h>
I 23
#include <grp.h>
E 23
I 22
D 27
#include <stdio.h>
E 27
D 23
#include <ctype.h>
E 23
#include <errno.h>
I 27
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 34
#include <err.h>
E 34
E 27
E 22
E 3
E 2

I 26
char *qfname = QUOTAFILENAME;
char *qfextension[] = INITQFNAMES;
char *quotagroup = QUOTAGROUP;

E 26
D 2
#define	ITABSZ	256
#define	NUID	3500
E 2
union {
	struct	fs	sblk;
D 2
	char	___[MAXBSIZE];
E 2
I 2
	char	dummy[MAXBSIZE];
E 2
} un;
#define	sblock	un.sblk
I 23
D 34
long dev_bsize = 1;
E 34
I 34
long dev_bsize;
E 34
long maxino;
E 23
I 2

I 24
struct quotaname {
	long	flags;
	char	grpqfname[MAXPATHLEN + 1];
	char	usrqfname[MAXPATHLEN + 1];
};
#define	HASUSR	1
#define	HASGRP	2

E 24
D 23
#define	ITABSZ	256
E 2
struct	dinode	itab[ITABSZ];
struct	dinode	*dp;
D 2
struct	dqblk	du[NUID];
char	*dn[NUID];
struct	dqblk	zeroes;
u_short	iuse[NUID];
u_long	buse[NUID];
E 2
D 13
long	blocks;
dev_t	dev;
E 13

I 3
#define LOGINNAMESIZE 8
E 23
E 3
D 2
int	bflg;
int	iflg;
int	rflg;
int	sflg;
E 2
I 2
struct fileusage {
I 3
D 23
	struct fileusage *fu_next;
E 3
	struct dqusage fu_usage;
	u_short	fu_uid;
D 3
	struct fileusage *fu_next;
E 3
I 3
	char fu_name[LOGINNAMESIZE + 1];
E 23
I 23
	struct	fileusage *fu_next;
	u_long	fu_curinodes;
	u_long	fu_curblocks;
	u_long	fu_id;
	char	fu_name[1];
	/* actually bigger */
E 23
E 3
};
D 23
#define FUHASH 997
struct fileusage *fuhead[FUHASH];
E 23
I 23
#define FUHASH 1024	/* must be power of two */
struct fileusage *fuhead[MAXQUOTAS][FUHASH];
E 23
D 29
struct fileusage *lookup();
D 23
struct fileusage *adduid();
int highuid;
E 23
I 23
struct fileusage *addid();
struct dinode *getnextinode();
E 29
E 23
E 2

D 2
int	fi;
unsigned	ino;
unsigned	nfiles;
int	highuid;

E 2
I 2
D 23
int fi;
ino_t ino;
long done;
E 2
struct	passwd	*getpwent();
struct	dinode	*ginode();
D 2
char	*malloc();
char	*copy();
E 2
I 2
char *malloc(), *makerawname();
E 23
I 23
D 24
#define	HASUSR	1
#define	HASGRP	2
E 23
E 2

E 24
I 2
D 23
int	vflag;		/* verbose */
int	aflag;		/* all file systems */
I 13
int	pflag;		/* fsck like parallel check */
E 23
I 23
int	aflag;			/* all file systems */
int	gflag;			/* check group quotas */
int	uflag;			/* check user quotas */
int	vflag;			/* verbose */
int	fi;			/* open disk file descriptor */
u_long	highid[MAXQUOTAS];	/* highest addid()'ed identifier per type */
E 23
E 13

I 29
struct fileusage *
	 addid __P((u_long, int, char *));
char	*blockcheck __P((char *));
void	 bread __P((daddr_t, char *, long));
int	 chkquota __P((char *, char *, struct quotaname *));
D 34
void	 err __P((const char *, ...));
E 34
void	 freeinodebuf __P((void));
struct dinode *
	 getnextinode __P((ino_t));
int	 getquotagid __P((void));
int	 hasquota __P((struct fstab *, int, char **));
struct fileusage *
	 lookup __P((u_long, int));
void	*needchk __P((struct fstab *));
int	 oneof __P((char *, char*[], int));
void	 resetinodebuf __P((void));
int	 update __P((char *, char *, int));
void	 usage __P((void));

int
E 29
D 23
char *qfname = "quotas";
char quotafile[MAXPATHLEN + 1];
I 3
struct dqblk zerodqbuf;
I 13
struct fileusage zerofileusage;
I 18
long dev_bsize = 1;
E 18
E 13
E 3

E 23
E 2
main(argc, argv)
I 2
	int argc;
E 2
D 29
	char **argv;
E 29
I 29
	char *argv[];
E 29
{
D 2
	register int n;
	register struct passwd *lp;
	register char *p;
	register long unsigned i;
	register c;
	register cg;
	FILE *qf;
	struct stat statb;
E 2
I 2
	register struct fstab *fs;
I 3
D 23
	register struct fileusage *fup;
E 23
	register struct passwd *pw;
E 3
D 23
	int i, errs = 0;
E 23
I 23
	register struct group *gr;
I 29
	struct quotaname *auxdata;
E 29
D 33
	int i, argnum, maxrun, errs = 0;
E 33
I 33
	int i, argnum, maxrun, errs;
E 33
D 29
	long auxdata, done = 0;
	char ch, *name, *blockcheck();
	int needchk(), chkquota();
	extern char *optarg;
	extern int optind;
E 29
I 29
	long done = 0;
	char ch, *name;
E 29
E 23
E 2

I 33
	errs = maxrun = 0;
E 33
D 2
	while (--argc > 0 && *(p = *++argv) == '-')
		while (c = *++p) switch (c) {

		case 's':
			sflg++;
			break;

		case 'b':
			bflg++;
			break;

		case 'i':
			iflg++;
			break;

		case 'r':
			rflg++;
			break;
		}

	if (argc != 2) {
		fprintf(stderr, "Usage: fixquota filesys qfile\n");
		exit(1);
E 2
I 2
D 23
again:
	argc--, argv++;
	if (argc > 0 && strcmp(*argv, "-v") == 0) {
		vflag++;
		goto again;
E 23
I 23
	while ((ch = getopt(argc, argv, "aguvl:")) != EOF) {
		switch(ch) {
		case 'a':
			aflag++;
			break;
		case 'g':
			gflag++;
			break;
		case 'u':
			uflag++;
			break;
		case 'v':
			vflag++;
			break;
		case 'l':
			maxrun = atoi(optarg);
			break;
		default:
			usage();
		}
E 23
E 2
	}
D 2

	fi = open(p, 0);
	if (fi < 0) {
		fprintf(stderr, "Can't open %s\n", p);
E 2
I 2
D 23
	if (argc > 0 && strcmp(*argv, "-a") == 0) {
		aflag++;
		goto again;
E 23
I 23
	argc -= optind;
	argv += optind;
	if ((argc == 0 && !aflag) || (argc > 0 && aflag))
		usage();
	if (!gflag && !uflag) {
		gflag++;
		uflag++;
E 23
	}
I 13
D 23
	if (argc > 0 && strcmp(*argv, "-p") == 0) {
		pflag++;
		goto again;
E 23
I 23
	if (gflag) {
		setgrent();
		while ((gr = getgrent()) != 0)
			(void) addid((u_long)gr->gr_gid, GRPQUOTA, gr->gr_name);
		endgrent();
E 23
	}
E 13
D 23
	if (argc <= 0 && !aflag) {
		fprintf(stderr, "Usage:\n\t%s\n\t%s\n",
D 13
			"quotacheck [-v] -a",
			"quotacheck [-v] filesys ...");
E 13
I 13
			"quotacheck [-v] [-p] -a",
			"quotacheck [-v] [-p] filesys ...");
E 13
E 2
		exit(1);
E 23
I 23
	if (uflag) {
		setpwent();
		while ((pw = getpwent()) != 0)
			(void) addid((u_long)pw->pw_uid, USRQUOTA, pw->pw_name);
		endpwent();
E 23
	}
I 3
D 9
	if (vflag) {
		setpwent();
		while ((pw = getpwent()) != 0) {
			fup = lookup(pw->pw_uid);
			if (fup == 0)
				fup = adduid(pw->pw_uid);
			strncpy(fup->fu_name, pw->pw_name,
				sizeof(fup->fu_name));
		}
		endpwent();
E 9
I 9
D 23

	setpwent();
	while ((pw = getpwent()) != 0) {
		fup = lookup(pw->pw_uid);
D 13
		if (fup == 0)
E 13
I 13
		if (fup == 0) {
E 13
			fup = adduid(pw->pw_uid);
D 13
		strncpy(fup->fu_name, pw->pw_name,
			sizeof(fup->fu_name));
E 13
I 13
			strncpy(fup->fu_name, pw->pw_name,
				sizeof(fup->fu_name));
		}
E 23
I 23
	if (aflag)
		exit(checkfstab(1, maxrun, needchk, chkquota));
D 29
	if (setfsent() == 0) {
		fprintf(stderr, "Can't open ");
		perror(FSTAB);
		exit(8);
E 23
E 13
E 9
	}
E 29
I 29
	if (setfsent() == 0)
D 34
		err("%s: can't open", FSTAB);
E 34
I 34
		err(1, "%s: can't open", FSTAB);
E 34
E 29
I 9
D 23
	endpwent();

E 9
E 3
D 2

	if (iflg || bflg || rflg) {
		while((lp=getpwent()) != 0) {
			n = lp->pw_uid;
			if (n>=NUID)
				continue;
			if(dn[n])
				continue;
			dn[n] = copy(lp->pw_name);
		}
E 2
I 2
D 13
	setfsent();
	while ((fs = getfsent()) != NULL) {
		if (aflag &&
		    (fs->fs_type == 0 || strcmp(fs->fs_type, "rq") != 0))
			continue;
		if (!aflag &&
		    !(oneof(fs->fs_file, argv, argc) ||
		      oneof(fs->fs_spec, argv, argc)))
			continue;
		(void) sprintf(quotafile, "%s/%s", fs->fs_file, qfname);
D 9
		errs += chkquota(fs->fs_spec, quotafile);
E 9
I 9
		errs += chkquota(fs->fs_spec, fs->fs_file, quotafile);
E 13
I 13
	if (pflag)
		errs = preen(argc, argv);
	else {
		if (setfsent() == 0) {
			fprintf(stderr, "Can't open ");
			perror(FSTAB);
			exit(8);
E 23
I 23
	while ((fs = getfsent()) != NULL) {
		if (((argnum = oneof(fs->fs_file, argv, argc)) >= 0 ||
		    (argnum = oneof(fs->fs_spec, argv, argc)) >= 0) &&
		    (auxdata = needchk(fs)) &&
		    (name = blockcheck(fs->fs_spec))) {
			done |= 1 << argnum;
			errs += chkquota(name, fs->fs_file, auxdata);
E 23
		}
D 23
		while ((fs = getfsent()) != NULL) {
			if (aflag &&
			    (fs->fs_type == 0 ||
			     strcmp(fs->fs_type, FSTAB_RQ) != 0))
				continue;
			if (!aflag &&
			    !(oneof(fs->fs_file, argv, argc) ||
			      oneof(fs->fs_spec, argv, argc)))
				continue;
			(void) sprintf(quotafile, "%s/%s", fs->fs_file, qfname);
			errs += chkquota(fs->fs_spec, fs->fs_file, quotafile);
		}
		endfsent();
E 23
E 13
E 9
E 2
	}
I 2
D 13
	endfsent();
E 13
I 13
D 23

E 23
I 23
	endfsent();
E 23
E 13
	for (i = 0; i < argc; i++)
		if ((done & (1 << i)) == 0)
D 14
			fprintf(stderr, "%s not found in /etc/fstab\n",
				argv[i]);
E 14
I 14
			fprintf(stderr, "%s not found in %s\n",
				argv[i], FSTAB);
E 14
	exit(errs);
}
E 2

I 29
void
E 29
I 13
D 23
preen(argc, argv)
	int argc;
	char **argv;
E 23
I 23
usage()
E 23
{
D 23
	register struct fstab *fs;
	register int passno, anygtr;
	register int errs;
	union wait status;
E 23
D 27

D 23
	passno = 1;
	errs = 0;
	do {
		anygtr = 0;
E 23
I 23
	fprintf(stderr, "Usage:\n\t%s\n\t%s\n",
		"quotacheck [-g] [-u] [-v] -a",
		"quotacheck [-g] [-u] [-v] filesys ...");
E 27
I 27
D 29
	(void) fprintf(stderr, "usage:\t%s\n\t%s\n",
E 29
I 29
	(void)fprintf(stderr, "usage:\t%s\n\t%s\n",
E 29
		"quotacheck -a [-guv]",
		"quotacheck [-guv] filesys ...");
E 27
	exit(1);
}
E 23

I 29
void *
E 29
D 23
		if (setfsent() == 0) {
			fprintf(stderr, "Can't open ");
			perror(FSTAB);
			exit(8);
		}
E 23
I 23
needchk(fs)
	register struct fstab *fs;
{
D 24
	int auxdata = 0;
E 24
I 24
	register struct quotaname *qnp;
	char *qfnp;
E 24
E 23

D 23
		while ((fs = getfsent()) != NULL) {
			if (fs->fs_passno > passno)
				anygtr = 1;
E 23
I 23
D 24
	if (gflag && hasquota(fs->fs_mntops, GRPQUOTA))
		auxdata |= HASGRP;
	if (uflag && hasquota(fs->fs_mntops, USRQUOTA))
		auxdata |= HASUSR;
	return (auxdata);
E 24
I 24
	if (strcmp(fs->fs_vfstype, "ufs") ||
	    strcmp(fs->fs_type, FSTAB_RW))
D 29
		return (0);
	if ((qnp = (struct quotaname *)malloc(sizeof *qnp)) == 0) {
		fprintf(stderr, "out of memory for quota structures\n");
		exit(1);
	}
E 29
I 29
		return (NULL);
	if ((qnp = malloc(sizeof(*qnp))) == NULL)
D 34
		err("%s", strerror(errno));
E 34
I 34
		err(1, "%s", strerror(errno));
E 34
E 29
	qnp->flags = 0;
	if (gflag && hasquota(fs, GRPQUOTA, &qfnp)) {
		strcpy(qnp->grpqfname, qfnp);
		qnp->flags |= HASGRP;
	}
	if (uflag && hasquota(fs, USRQUOTA, &qfnp)) {
		strcpy(qnp->usrqfname, qfnp);
		qnp->flags |= HASUSR;
	}
	if (qnp->flags)
D 29
		return ((int)qnp);
	free((char *)qnp);
	return (0);
E 29
I 29
		return (qnp);
	free(qnp);
	return (NULL);
E 29
E 24
}
E 23

D 23
			if (aflag &&
			    (fs->fs_type == 0 ||
			     strcmp(fs->fs_type, FSTAB_RQ) != 0))
				continue;
E 23
I 23
/*
 * Scan the specified filesystem to check quota(s) present on it.
 */
I 29
int
E 29
D 24
chkquota(fsname, mntpt, auxdata)
E 24
I 24
chkquota(fsname, mntpt, qnp)
E 24
	char *fsname, *mntpt;
D 24
	long auxdata;
E 24
I 24
	register struct quotaname *qnp;
E 24
{
	register struct fileusage *fup;
	register struct dinode *dp;
	int cg, i, mode, errs = 0;
	ino_t ino;
E 23

D 23
			if (!aflag &&
			    !(oneof(fs->fs_file, argv, argc) ||
			      oneof(fs->fs_spec, argv, argc)))
E 23
I 23
D 29
	if ((fi = open(fsname, 0)) < 0) {
E 29
I 29
	if ((fi = open(fsname, O_RDONLY, 0)) < 0) {
E 29
		perror(fsname);
		return (1);
	}
	if (vflag) {
D 29
		fprintf(stdout, "*** Checking ");
E 29
I 29
		(void)printf("*** Checking ");
E 29
D 24
		if (auxdata & HASUSR)
E 24
I 24
		if (qnp->flags & HASUSR)
E 24
D 29
			fprintf(stdout, "%s%s", qfextension[USRQUOTA],
E 29
I 29
			(void)printf("%s%s", qfextension[USRQUOTA],
E 29
D 24
			    (auxdata & HASGRP) ? " and " : "");
		if (auxdata & HASGRP)
E 24
I 24
			    (qnp->flags & HASGRP) ? " and " : "");
		if (qnp->flags & HASGRP)
E 24
D 29
			fprintf(stdout, "%s", qfextension[GRPQUOTA]);
		fprintf(stdout, " quotas for %s (%s)\n", fsname, mntpt);
E 29
I 29
			(void)printf("%s", qfextension[GRPQUOTA]);
		(void)printf(" quotas for %s (%s)\n", fsname, mntpt);
E 29
	}
	sync();
I 34
	dev_bsize = 1;
E 34
	bread(SBOFF, (char *)&sblock, (long)SBSIZE);
	dev_bsize = sblock.fs_fsize / fsbtodb(&sblock, 1);
	maxino = sblock.fs_ncg * sblock.fs_ipg;
	resetinodebuf();
	for (ino = 0, cg = 0; cg < sblock.fs_ncg; cg++) {
		for (i = 0; i < sblock.fs_ipg; i++, ino++) {
			if (ino < ROOTINO)
E 23
				continue;
D 23

			if (fs->fs_passno != passno)
E 23
I 23
			if ((dp = getnextinode(ino)) == NULL)
E 23
				continue;
D 23

			switch (fork()) {
			case -1:
				perror("fork");
				exit(8);
				break;

			case 0:
D 19
				sprintf(quotafile, "%s/%s",
E 19
I 19
				(void) sprintf(quotafile, "%s/%s",
E 19
					fs->fs_file, qfname);
				exit(chkquota(fs->fs_spec,
					fs->fs_file, quotafile));
E 23
I 23
			if ((mode = dp->di_mode & IFMT) == 0)
				continue;
D 24
			if (auxdata & HASGRP) {
E 24
I 24
			if (qnp->flags & HASGRP) {
E 24
				fup = addid((u_long)dp->di_gid, GRPQUOTA,
				    (char *)0);
				fup->fu_curinodes++;
				if (mode == IFREG || mode == IFDIR ||
				    mode == IFLNK)
					fup->fu_curblocks += dp->di_blocks;
E 23
			}
I 23
D 24
			if (auxdata & HASUSR) {
E 24
I 24
			if (qnp->flags & HASUSR) {
E 24
				fup = addid((u_long)dp->di_uid, USRQUOTA,
				    (char *)0);
				fup->fu_curinodes++;
				if (mode == IFREG || mode == IFDIR ||
				    mode == IFLNK)
					fup->fu_curblocks += dp->di_blocks;
			}
E 23
		}
D 23

		while (wait(&status) != -1) 
			errs += status.w_retcode;

		passno++;
	} while (anygtr);

E 23
I 23
	}
	freeinodebuf();
D 24
	if (auxdata & HASUSR)
		errs += update(mntpt, USRQUOTA);
	if (auxdata & HASGRP)
		errs += update(mntpt, GRPQUOTA);
E 24
I 24
	if (qnp->flags & HASUSR)
		errs += update(mntpt, qnp->usrqfname, USRQUOTA);
	if (qnp->flags & HASGRP)
		errs += update(mntpt, qnp->grpqfname, GRPQUOTA);
E 24
	close(fi);
E 23
	return (errs);
}

E 13
D 2
	if (!(iflg || bflg))
		sflg++;
E 2
I 2
D 9
chkquota(fsdev, qffile)
E 9
I 9
D 23
chkquota(fsdev, fsfile, qffile)
E 9
	char *fsdev;
I 9
	char *fsfile;
E 9
	char *qffile;
E 23
I 23
/*
 * Update a specified quota file.
 */
I 29
int
E 29
D 24
update(fsname, type)
	char *fsname;
E 24
I 24
update(fsname, quotafile, type)
	char *fsname, *quotafile;
E 24
	register int type;
E 23
{
	register struct fileusage *fup;
D 23
	dev_t quotadev;
E 23
D 17
	FILE *qf;
E 17
I 17
	register FILE *qfi, *qfo;
E 17
D 23
	u_short uid;
D 17
	int cg, i;
E 17
I 17
	int cg, i, fdo;
E 17
	char *rawdisk;
	struct stat statb;
E 23
I 23
	register u_long id, lastid;
E 23
	struct dqblk dqbuf;
I 6
D 23
	static int warned = 0;
E 23
I 23
D 24
	char quotafile[MAXPATHLEN + 1];
E 24
E 23
D 27
	extern int errno;
E 27
I 23
	static int warned = 0;
	static struct dqblk zerodqbuf;
	static struct fileusage zerofileusage;
E 23
E 6
E 2

D 2
	qf = fopen(*++argv, "r");
	if (qf != NULL) {
		fstat(fileno(qf), &statb);
		dev = statb.st_dev;
		quota(Q_SYNC, 0, dev, 0);
		n = fread(du, sizeof(struct dqblk), NUID, qf);
		if (n == EOF)
			n = 0;
		highuid = n-1;
		fclose(qf);
	} else {
		highuid = -1;
		dev = NODEV;
E 2
I 2
D 23
	rawdisk = makerawname(fsdev);
	if (vflag)
D 9
		fprintf(stdout, "*** Check quotas for %s\n", rawdisk);
E 9
I 9
D 13
		fprintf(stdout, "*** Check quotas for %s (%s)\n", rawdisk, fsfile);
E 13
I 13
		fprintf(stdout, "*** Checking quotas for %s (%s)\n", rawdisk, fsfile);
E 13
E 9
	fi = open(rawdisk, 0);
	if (fi < 0) {
		perror(rawdisk);
		return (1);
E 23
I 23
D 24
	(void) sprintf(quotafile, "%s/%s.%s", fsname, qfname,
	    qfextension[type]);
E 24
	if ((qfo = fopen(quotafile, "r+")) == NULL) {
D 27
		if (errno != ENOENT) {
			perror(quotafile);
E 27
I 27
		if (errno == ENOENT)
			qfo = fopen(quotafile, "w+");
		if (qfo) {
			(void) fprintf(stderr,
			    "quotacheck: creating quota file %s\n", quotafile);
#define	MODE	(S_IRUSR|S_IWUSR|S_IRGRP)
			(void) fchown(fileno(qfo), getuid(), getquotagid());
			(void) fchmod(fileno(qfo), MODE);
		} else {
			(void) fprintf(stderr,
			    "quotacheck: %s: %s\n", quotafile, strerror(errno));
E 27
			return (1);
		}
D 27
		if ((qfo = fopen(quotafile, "w+")) == NULL) {
			perror(quotafile);
			return (1);
		}
I 24
		fprintf(stderr, "Creating quota file %s\n", quotafile);
		(void) fchown(fileno(qfo), getuid(), getquotagid());
		(void) fchmod(fileno(qfo), 0640);
E 27
E 24
E 23
E 2
	}
D 2
/*ZZprintf("highuid = %d\n", highuid);*/

	for (n = 0; n <= highuid; n++) {
		iuse[n] = du[n].dqb_curinodes;
		buse[n] = du[n].dqb_curblocks;
		du[n].dqb_curinodes = du[n].dqb_curblocks = 0;
E 2
I 2
D 17
	qf = fopen(qffile, "r+");
	if (qf == NULL) {
E 17
I 17
D 23
	qfi = fopen(qffile, "r");
	if (qfi == NULL) {
E 17
		perror(qffile);
I 9
		close(fi);
E 23
I 23
	if ((qfi = fopen(quotafile, "r")) == NULL) {
D 27
		perror(quotafile);
		fclose(qfo);
E 27
I 27
		(void) fprintf(stderr,
		    "quotacheck: %s: %s\n", quotafile, strerror(errno));
		(void) fclose(qfo);
E 27
E 23
E 9
		return (1);
E 2
	}
D 2

E 2
I 2
D 17
	if (fstat(fileno(qf), &statb) < 0) {
E 17
I 17
D 23
	if (fstat(fileno(qfi), &statb) < 0) {
E 17
		perror(qffile);
I 9
D 17
		fclose(qf);
E 17
I 17
		fclose(qfi);
E 17
		close(fi);
E 9
		return (1);
	}
	quotadev = statb.st_dev;
	if (stat(fsdev, &statb) < 0) {
		perror(fsdev);
I 9
D 17
		fclose(qf);
E 17
I 17
		fclose(qfi);
E 17
		close(fi);
E 9
		return (1);
	}
	if (quotadev != statb.st_rdev) {
		fprintf(stderr, "%s dev (0x%x) mismatch %s dev (0x%x)\n",
			qffile, quotadev, fsdev, statb.st_rdev);
I 9
D 17
		fclose(qf);
E 17
I 17
		fclose(qfi);
E 17
		close(fi);
E 9
		return (1);
	}
I 17
	/*
	 * Must do fdopen(open(qffile, 1), "w") instead of fopen(qffile, "w")
	 * because fopen(qffile, "w") would truncate the quota file.
	 */
	fdo = open(qffile, 1);
	if (fdo < 0 || (qfo = fdopen(fdo, "w")) == NULL) {
		perror(qffile);
		if (fdo >= 0)
			close(fdo);
		fclose(qfi);
		close(fi);
		return (1);
	}
E 17
D 6
	quota(Q_SYNC, 0, quotadev, 0);
E 6
I 6
D 13
	if (quota(Q_SYNC, 0, quotadev, 0) < 0 &&
E 13
I 13
	if (quota(Q_SYNC, 0, quotadev, (caddr_t)0) < 0 &&
E 13
	    errno == EINVAL && !warned && vflag) {
E 23
I 23
	if (quotactl(fsname, QCMD(Q_SYNC, type), (u_long)0, (caddr_t)0) < 0 &&
	    errno == EOPNOTSUPP && !warned && vflag) {
E 23
		warned++;
D 23
		fprintf(stdout,
		    "*** Warning: Quotas are not compiled into this kernel\n");
E 23
I 23
D 29
		fprintf(stdout, "*** Warning: %s\n",
E 29
I 29
		(void)printf("*** Warning: %s\n",
E 29
		    "Quotas are not compiled into this kernel");
E 23
	}
E 6
E 2
D 23
	sync();
D 18
	bread(SBLOCK, (char *)&sblock, SBSIZE);
E 18
I 18
	bread(SBOFF, (char *)&sblock, SBSIZE);
	dev_bsize = sblock.fs_fsize / fsbtodb(&sblock, 1);
E 18
	ino = 0;
	for (cg = 0; cg < sblock.fs_ncg; cg++) {
D 2
/*ZZprintf("cg %d <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", cg);*/
E 2
		dp = NULL;
		for (i = 0; i < sblock.fs_ipg; i++)
			acct(ginode());
	}
D 2
	if (sflg && highuid >= 0) {
		int sig;
		int ssig;

		sig = (int) signal(SIGINT, SIG_IGN);
		ssig = (int) signal(SIGTSTP, SIG_IGN);
		if ((qf = fopen(*argv, "a")) == NULL) {
			fprintf(stderr, "Can't create %s\n", *argv);
			exit(1);
E 2
I 2
	for (uid = 0; uid <= highuid; uid++) {
I 9
D 17
		fseek(qf, (long)uid * sizeof(struct dqblk), 0);
E 9
D 5
		fup = lookup(uid);
		if (fup == 0)
			continue;
		fseek(qf, uid * sizeof(struct dqblk), 0);
E 5
		i = fread(&dqbuf, sizeof(struct dqblk), 1, qf);
E 17
I 17
		i = fread(&dqbuf, sizeof(struct dqblk), 1, qfi);
E 17
		if (i == 0)
E 23
I 23
	for (lastid = highid[type], id = 0; id <= lastid; id++) {
		if (fread((char *)&dqbuf, sizeof(struct dqblk), 1, qfi) == 0)
E 23
D 3
			bzero(&dqbuf, sizeof(struct dqblk));
E 3
I 3
			dqbuf = zerodqbuf;
I 5
D 23
		fup = lookup(uid);
D 13
		if (fup == 0) {
D 8
			if (!feof(qf)) {
E 8
I 8
			if ((dqbuf.dqb_curinodes != 0 ||
			    dqbuf.dqb_curblocks != 0) &&
			    !feof(qf)) {
				dqbuf.dqb_curinodes = 0;
				dqbuf.dqb_curblocks = 0;
E 8
D 9
				fseek(qf, uid * sizeof(struct dqblk), 0);
E 9
I 9
				fseek(qf, (long)uid * sizeof(struct dqblk), 0);
E 9
D 8
				fwrite(&zerodqbuf, sizeof(struct dqblk), 1, qf);
E 8
I 8
				fwrite(&dqbuf, sizeof(struct dqblk), 1, qf);
D 9
				fseek(qf, (uid + 1) * sizeof(struct dqblk), 0);
E 9
E 8
			}
			continue;
		}
E 13
I 13
		if (fup == 0)
E 23
I 23
		if ((fup = lookup(id, type)) == 0)
E 23
			fup = &zerofileusage;
E 13
E 5
E 3
D 23
		if (dqbuf.dqb_curinodes == fup->fu_usage.du_curinodes &&
D 3
		    dqbuf.dqb_curblocks == fup->fu_usage.du_curblocks)
E 3
I 3
		    dqbuf.dqb_curblocks == fup->fu_usage.du_curblocks) {
			fup->fu_usage.du_curinodes = 0;
			fup->fu_usage.du_curblocks = 0;
E 23
I 23
		if (dqbuf.dqb_curinodes == fup->fu_curinodes &&
		    dqbuf.dqb_curblocks == fup->fu_curblocks) {
			fup->fu_curinodes = 0;
			fup->fu_curblocks = 0;
E 23
I 17
			fseek(qfo, (long)sizeof(struct dqblk), 1);
E 17
E 3
			continue;
I 3
		}
E 3
		if (vflag) {
I 13
D 23
			if (pflag)
				printf("%s: ", rawdisk);
E 13
D 3
			fprintf(stdout, "uid %d fixed:", uid);
E 3
I 3
			if (fup->fu_name[0] != '\0')
D 13
				printf("%-10s fixed:", fup->fu_name);
E 13
I 13
				printf("%-8s fixed:", fup->fu_name);
E 13
			else
D 13
				printf("#%-9d fixed:", uid);
E 3
			fprintf(stdout, " inodes (old %d, new %d)",
			    dqbuf.dqb_curinodes, fup->fu_usage.du_curinodes);
			fprintf(stdout, " blocks (old %d, new %d)\n",
			    dqbuf.dqb_curblocks, fup->fu_usage.du_curblocks);
E 13
I 13
				printf("#%-7d fixed:", uid);
			if (dqbuf.dqb_curinodes != fup->fu_usage.du_curinodes)
E 23
I 23
			if (aflag)
				printf("%s: ", fsname);
			printf("%-8s fixed:", fup->fu_name);
			if (dqbuf.dqb_curinodes != fup->fu_curinodes)
E 23
D 17
				fprintf(stdout, "  inodes %d -> %d",
E 17
I 17
D 29
				fprintf(stdout, "\tinodes %d -> %d",
E 29
I 29
				(void)printf("\tinodes %d -> %d",
E 29
E 17
D 23
					dqbuf.dqb_curinodes, fup->fu_usage.du_curinodes);
			if (dqbuf.dqb_curblocks != fup->fu_usage.du_curblocks)
E 23
I 23
					dqbuf.dqb_curinodes, fup->fu_curinodes);
			if (dqbuf.dqb_curblocks != fup->fu_curblocks)
E 23
D 17
				fprintf(stdout, "  blocks %d -> %d",
E 17
I 17
D 29
				fprintf(stdout, "\tblocks %d -> %d",
E 29
I 29
				(void)printf("\tblocks %d -> %d",
E 29
E 17
D 23
					dqbuf.dqb_curblocks, fup->fu_usage.du_curblocks);
E 23
I 23
					dqbuf.dqb_curblocks, fup->fu_curblocks);
E 23
D 29
			fprintf(stdout, "\n");
E 29
I 29
			(void)printf("\n");
E 29
E 13
E 2
		}
D 2

		rewind(qf);
		fwrite(du, sizeof(struct dqblk), highuid+1, qf);
		fclose(qf);
		signal(SIGTSTP, ssig);
		sysset();
		signal(SIGINT, sig);
E 2
I 2
D 23
		dqbuf.dqb_curinodes = fup->fu_usage.du_curinodes;
		dqbuf.dqb_curblocks = fup->fu_usage.du_curblocks;
I 3
D 4
		fup->fu_usage.du_curinodes = 0;
		fup->fu_usage.du_curblocks = 0;
E 4
E 3
D 9
		fseek(qf, uid * sizeof(struct dqblk), 0);
E 9
I 9
D 17
		fseek(qf, (long)uid * sizeof(struct dqblk), 0);
E 9
		fwrite(&dqbuf, sizeof(struct dqblk), 1, qf);
E 17
I 17
		fwrite(&dqbuf, sizeof(struct dqblk), 1, qfo);
E 17
I 8
D 9
		fseek(qf, (uid + 1) * sizeof(struct dqblk), 0);
E 9
E 8
		quota(Q_SETDUSE, uid, quotadev, &fup->fu_usage);
I 4
		fup->fu_usage.du_curinodes = 0;
		fup->fu_usage.du_curblocks = 0;
E 23
I 23
		/*
		 * Reset time limit if have a soft limit and were
		 * previously under it, but are now over it.
		 */
		if (dqbuf.dqb_bsoftlimit &&
		    dqbuf.dqb_curblocks < dqbuf.dqb_bsoftlimit &&
		    fup->fu_curblocks >= dqbuf.dqb_bsoftlimit)
			dqbuf.dqb_btime = 0;
		if (dqbuf.dqb_isoftlimit &&
		    dqbuf.dqb_curblocks < dqbuf.dqb_isoftlimit &&
		    fup->fu_curblocks >= dqbuf.dqb_isoftlimit)
			dqbuf.dqb_itime = 0;
		dqbuf.dqb_curinodes = fup->fu_curinodes;
		dqbuf.dqb_curblocks = fup->fu_curblocks;
		fwrite((char *)&dqbuf, sizeof(struct dqblk), 1, qfo);
		(void) quotactl(fsname, QCMD(Q_SETUSE, type), id,
		    (caddr_t)&dqbuf);
		fup->fu_curinodes = 0;
		fup->fu_curblocks = 0;
E 23
E 4
E 2
	}
I 9
D 17
	fflush(qf);
E 9
I 5
	ftruncate(fileno(qf), (highuid + 1) * sizeof(struct dqblk));
I 9
	fclose(qf);
E 17
I 17
D 23
	fflush(qfo);
	ftruncate(fileno(qfo), (off_t)((highuid + 1) * sizeof(struct dqblk)));
E 23
	fclose(qfi);
I 23
	fflush(qfo);
	ftruncate(fileno(qfo),
	    (off_t)((highid[type] + 1) * sizeof(struct dqblk)));
E 23
	fclose(qfo);
E 17
D 23
	close(fi);
E 23
E 9
E 5
D 2
	report();
E 2
I 2
	return (0);
E 2
}

D 23
acct(ip)
	register struct dinode *ip;
E 23
I 23
/*
 * Check to see if target appears in list of size cnt.
 */
I 29
int
E 29
oneof(target, list, cnt)
	register char *target, *list[];
	int cnt;
E 23
{
D 13
	register n;
E 13
I 2
D 23
	register struct fileusage *fup;
E 2

	if (ip == NULL)
		return;
	if (ip->di_mode == 0)
D 2
/*ZZ{printf(" unallocated\n");*/
E 2
		return;
D 2
/*ZZ}*/
	if (ip->di_uid >= NUID)
/*ZZ{printf(" uid oor\n");*/
		return;
/*ZZ}*/
	if (ip->di_uid > highuid) {
		for (n = highuid+1; n <= ip->di_uid; n++)
			du[n] = zeroes;
		highuid = ip->di_uid;
	}
	du[ip->di_uid].dqb_curinodes++;
E 2
I 2
D 13
	fup = lookup(ip->di_uid);
	if (fup == 0)
		fup = adduid(ip->di_uid);
E 13
I 13
	fup = adduid(ip->di_uid);
E 13
	fup->fu_usage.du_curinodes++;
E 2
	if ((ip->di_mode & IFMT) == IFCHR || (ip->di_mode & IFMT) == IFBLK)
D 2
/*ZZ{printf(" special\n");*/
E 2
		return;
D 2
/*ZZ}*/
	blocks = 0;
	for (n = 0; n < NDADDR; n++)
		if (ip->di_db[n])
			blocks += dblksize(&sblock, ip, n) / DEV_BSIZE;
	for (n = 0; n < NIADDR; n++)
		tloop(ip->di_ib[n], ip, n);
	du[ip->di_uid].dqb_curblocks += blocks;
	if (blocks != ip->di_blocks)
		printf("Ino %d: <calc %d, recorded %d>\n", ino, blocks, ip->di_blocks);
/*ZZprintf(" %d blks\n", blocks);*/
E 2
I 2
	fup->fu_usage.du_curblocks += ip->di_blocks;
E 2
}

D 2
tloop(bn, ip, f)
	long bn;
E 2
I 2
oneof(target, list, n)
	char *target, *list[];
	register int n;
E 2
{
E 23
D 2
	register i;
	long	iblk[MAXBSIZE/sizeof(long)];
E 2
I 2
	register int i;
E 2

D 2
	if (!bn)
		return;
	blocks += sblock.fs_bsize / DEV_BSIZE;
	bread(fsbtodb(&sblock, bn), iblk, sblock.fs_bsize);
	if (f) {
		for (i = 0; i < NINDIR(&sblock); i++)
			tloop(iblk[i], ip, f-1);
	} else {
		for (i = 0; i < NINDIR(&sblock); i++)
			if (iblk[i])
				blocks += sblock.fs_bsize / DEV_BSIZE;
	}
E 2
I 2
D 23
	for (i = 0; i < n; i++)
		if (strcmp(target, list[i]) == 0) {
			done |= 1 << i;
			return (1);
		}
	return (0);
E 23
I 23
	for (i = 0; i < cnt; i++)
		if (strcmp(target, list[i]) == 0)
			return (i);
	return (-1);
E 23
E 2
}

D 23
struct dinode *
ginode()
E 23
I 23
/*
I 24
 * Determine the group identifier for quota files.
 */
I 29
int
E 29
getquotagid()
{
	struct group *gr;

	if (gr = getgrnam(quotagroup))
		return (gr->gr_gid);
	return (-1);
}

/*
E 24
 * Check to see if a particular quota is to be enabled.
 */
I 29
int
E 29
D 24
hasquota(options, type)
	char *options;
E 24
I 24
hasquota(fs, type, qfnamep)
	register struct fstab *fs;
E 24
	int type;
I 24
	char **qfnamep;
E 24
E 23
{
D 23
	register unsigned long iblk;
E 23
I 23
	register char *opt;
D 24
	char buf[BUFSIZ];
	char *strtok();
E 24
I 24
D 29
	char *cp, *index(), *strtok();
E 29
I 29
	char *cp;
E 29
E 24
	static char initname, usrname[100], grpname[100];
I 24
	static char buf[BUFSIZ];
E 24
E 23

D 23
	if (dp == NULL || ++dp >= &itab[ITABSZ]) {
		iblk = itod(&sblock, ino);
D 2
/*ZZprintf("dp = %x, itab=%x", dp, itab);*/
/*ZZprintf(" Reading inodes from fs blk %d ", iblk);*/
E 2
		bread(fsbtodb(&sblock, iblk), (char *)itab, sizeof itab);
		dp = &itab[ino % INOPB(&sblock)];
E 23
I 23
	if (!initname) {
D 29
		sprintf(usrname, "%s%s", qfextension[USRQUOTA], qfname);
		sprintf(grpname, "%s%s", qfextension[GRPQUOTA], qfname);
E 29
I 29
		(void)snprintf(usrname, sizeof(usrname),
		    "%s%s", qfextension[USRQUOTA], qfname);
		(void)snprintf(grpname, sizeof(grpname),
		    "%s%s", qfextension[GRPQUOTA], qfname);
E 29
		initname = 1;
E 23
D 2
/*ZZprintf("dp = %x\n", dp, itab);*/
E 2
	}
D 2
/*ZZprintf("ino %d ", ino);*/
E 2
D 23
	if (ino++ < ROOTINO)
		return(NULL);
	return(dp);
}

bread(bno, buf, cnt)
	long unsigned bno;
	char *buf;
{
I 17
D 18
	extern	off_t lseek();
	register off_t pos;
E 18
E 17

D 2
	lseek(fi, (long)bno*DEV_BSIZE, 0);
E 2
I 2
D 17
	lseek(fi, (long)dbtob(bno), 0);
E 17
I 17
D 18
	pos = (off_t)dbtob(bno);
	if (lseek(fi, pos, 0) != pos) {
E 18
I 18
	if (lseek(fi, bno * dev_bsize, 0) < 0) {
E 18
		perror("lseek");
		exit(1);
E 23
I 23
D 24
	strcpy(buf, options);
E 24
I 24
	strcpy(buf, fs->fs_mntops);
E 24
	for (opt = strtok(buf, ","); opt; opt = strtok(NULL, ",")) {
I 24
D 36
		if (cp = index(opt, '='))
E 36
I 36
		if (cp = strchr(opt, '='))
E 36
			*cp++ = '\0';
E 24
		if (type == USRQUOTA && strcmp(opt, usrname) == 0)
D 24
			return(1);
E 24
I 24
			break;
E 24
		if (type == GRPQUOTA && strcmp(opt, grpname) == 0)
D 24
			return(1);
E 24
I 24
			break;
E 24
E 23
	}
D 23

E 17
E 2
	if (read(fi, buf, cnt) != cnt) {
D 13
		printf("read error %u\n", bno);
E 13
I 13
		perror("read");
E 13
		exit(1);
	}
E 23
I 23
D 24
	return (0);
E 24
I 24
	if (!opt)
		return (0);
D 29
	if (cp) {
E 29
I 29
	if (cp)
E 29
		*qfnamep = cp;
D 29
		return (1);
E 29
I 29
	else {
		(void)snprintf(buf, sizeof(buf),
		    "%s/%s.%s", fs->fs_file, qfname, qfextension[type]);
		*qfnamep = buf;
E 29
	}
D 29
	(void) sprintf(buf, "%s/%s.%s", fs->fs_file, qfname, qfextension[type]);
	*qfnamep = buf;
E 29
	return (1);
E 24
E 23
}

I 23
/*
 * Routines to manage the file usage table.
 *
 * Lookup an id of a specific type.
 */
E 23
D 2
sysset()
E 2
I 2
struct fileusage *
D 23
lookup(uid)
	u_short uid;
E 23
I 23
lookup(id, type)
	u_long id;
	int type;
E 23
E 2
{
D 2
	struct dqusage usage;
	register i;
E 2
I 2
	register struct fileusage *fup;
E 2

D 2
	for (i = 0; i <= highuid; i++) {
		if (du[i].dqb_curinodes != iuse[i] || du[i].dqb_curblocks != buse[i]) {
			if (du[i].dqb_isoftlimit == 0 && du[i].dqb_bsoftlimit == 0)
				continue;
			if (rflg) {
				if (dn[i])
					printf("%s", dn[i]);
				else
					printf("#%d", i);
				printf(": i %d->%d, b %d->%d\n"
					, iuse[i]
					, du[i].dqb_curinodes
					, buse[i]
					, du[i].dqb_curblocks
				);
			}
			usage.du_curinodes = du[i].dqb_curinodes;
			usage.du_curblocks = du[i].dqb_curblocks;
			quota(Q_SETDUSE, i, dev, &usage);
		}
	}
E 2
I 2
D 23
	for (fup = fuhead[uid % FUHASH]; fup != 0; fup = fup->fu_next)
		if (fup->fu_uid == uid)
E 23
I 23
	for (fup = fuhead[type][id & (FUHASH-1)]; fup != 0; fup = fup->fu_next)
		if (fup->fu_id == id)
E 23
			return (fup);
D 29
	return ((struct fileusage *)0);
E 29
I 29
	return (NULL);
E 29
E 2
}

I 23
/*
 * Add a new file usage id if it does not already exist.
 */
E 23
D 2
report()
E 2
I 2
struct fileusage *
D 23
adduid(uid)
	u_short uid;
E 23
I 23
addid(id, type, name)
	u_long id;
	int type;
	char *name;
E 23
E 2
{
D 2
	register i;
E 2
I 2
	struct fileusage *fup, **fhp;
I 23
	int len;
E 23
I 9
D 27
	extern char *calloc();
E 27
E 9
E 2

D 2
	if (iflg)
		for (i = 0; i <= highuid; i++)
			if (du[i].dqb_isoftlimit && du[i].dqb_curinodes >= du[i].dqb_isoftlimit) {
				if (dn[i])
					printf("%-10s", dn[i]);
				else
					printf("#%-9d", i);
				printf("%5d (iq = %d)\n", du[i].dqb_curinodes, du[i].dqb_isoftlimit);
			}

	if (bflg)
		for (i = 0; i <= highuid; i++)
			if (du[i].dqb_bsoftlimit && du[i].dqb_curblocks >= du[i].dqb_bsoftlimit) {
				if (dn[i])
					printf("%-10s", dn[i]);
				else
					printf("#%-9s", i);
				printf("%5d (quot = %d)\n", du[i].dqb_curblocks, du[i].dqb_bsoftlimit);
			}
E 2
I 2
D 23
	fup = lookup(uid);
	if (fup != 0)
E 23
I 23
	if (fup = lookup(id, type))
E 23
		return (fup);
D 23
	fup = (struct fileusage *)calloc(1, sizeof(struct fileusage));
	if (fup == 0) {
E 23
I 23
	if (name)
		len = strlen(name);
	else
		len = 10;
D 29
	if ((fup = (struct fileusage *)calloc(1, sizeof(*fup) + len)) == NULL) {
E 23
		fprintf(stderr, "out of memory for fileusage structures\n");
		exit(1);
	}
E 29
I 29
	if ((fup = calloc(1, sizeof(*fup) + len)) == NULL)
D 34
		err("%s", strerror(errno));
E 34
I 34
		err(1, "%s", strerror(errno));
E 34
E 29
D 23
	fhp = &fuhead[uid % FUHASH];
E 23
I 23
	fhp = &fuhead[type][id & (FUHASH - 1)];
E 23
	fup->fu_next = *fhp;
	*fhp = fup;
D 23
	fup->fu_uid = uid;
	if (uid > highuid)
		highuid = uid;
E 23
I 23
	fup->fu_id = id;
	if (id > highid[type])
		highid[type] = id;
D 29
	if (name) {
E 29
I 29
	if (name)
E 29
D 36
		bcopy(name, fup->fu_name, len + 1);
E 36
I 36
		memmove(fup->fu_name, name, len + 1);
E 36
D 29
	} else {
		sprintf(fup->fu_name, "%u", id);
	}
E 29
I 29
	else
		(void)sprintf(fup->fu_name, "%u", id);
E 29
E 23
	return (fup);
E 2
}

D 23
char *
D 2
copy(s)
	char *s;
E 2
I 2
makerawname(name)
	char *name;
E 23
I 23
/*
 * Special purpose version of ginode used to optimize pass
 * over all the inodes in numerical order.
 */
ino_t nextino, lastinum;
long readcnt, readpercg, fullcnt, inobufsize, partialcnt, partialsize;
struct dinode *inodebuf;
#define	INOBUFSIZE	56*1024	/* size of buffer to read inodes */

struct dinode *
getnextinode(inumber)
	ino_t inumber;
E 23
E 2
{
D 2
	register char *p;
	register n;
E 2
I 2
D 23
	register char *cp;
	char tmp, ch, *rindex();
	static char rawname[MAXPATHLEN];
E 23
I 23
	long size;
	daddr_t dblk;
	static struct dinode *dp;
E 23
E 2

D 2
	for(n=0; s[n]; n++)
		;
	p = malloc((unsigned)n+1);
	for(n=0; p[n] = s[n]; n++)
		;
	return(p);
E 2
I 2
D 23
	strcpy(rawname, name);
D 9
	cp = rindex(rawname, '/') + 1;
	if (cp == (char *)1 || *cp == 'r')
E 9
I 9
	cp = rindex(rawname, '/');
D 14
	if (cp == NULL || cp[1] == 'r')
E 14
I 14
	if (cp == NULL)
E 14
E 9
		return (name);
I 9
	else
		cp++;
E 9
	for (ch = 'r'; *cp != '\0'; ) {
		tmp = *cp;
		*cp++ = ch;
		ch = tmp;
E 23
I 23
D 29
	if (inumber != nextino++ || inumber > maxino) {
		fprintf(stderr, "bad inode number %d to nextinode\n", inumber);
		exit(1);
E 23
	}
E 29
I 29
	if (inumber != nextino++ || inumber > maxino)
D 34
		err("bad inode number %d to nextinode", inumber);
E 34
I 34
		err(1, "bad inode number %d to nextinode", inumber);
E 34
E 29
D 23
	*cp++ = ch;
	*cp = '\0';
	return (rawname);
E 23
I 23
	if (inumber >= lastinum) {
		readcnt++;
D 32
		dblk = fsbtodb(&sblock, itod(&sblock, lastinum));
E 32
I 32
		dblk = fsbtodb(&sblock, ino_to_fsba(&sblock, lastinum));
E 32
		if (readcnt % readpercg == 0) {
			size = partialsize;
			lastinum += partialcnt;
		} else {
			size = inobufsize;
			lastinum += fullcnt;
		}
		bread(dblk, (char *)inodebuf, size);
		dp = inodebuf;
	}
	return (dp++);
}

/*
 * Prepare to scan a set of inodes.
 */
I 29
void
E 29
resetinodebuf()
{

	nextino = 0;
	lastinum = 0;
	readcnt = 0;
	inobufsize = blkroundup(&sblock, INOBUFSIZE);
	fullcnt = inobufsize / sizeof(struct dinode);
	readpercg = sblock.fs_ipg / fullcnt;
	partialcnt = sblock.fs_ipg % fullcnt;
	partialsize = partialcnt * sizeof(struct dinode);
	if (partialcnt != 0) {
		readpercg++;
	} else {
		partialcnt = fullcnt;
		partialsize = inobufsize;
	}
	if (inodebuf == NULL &&
D 29
	   (inodebuf = (struct dinode *)malloc((unsigned)inobufsize)) == NULL) {
		fprintf(stderr, "Cannot allocate space for inode buffer\n");
		exit(1);
	}
E 29
I 29
	   (inodebuf = malloc((u_int)inobufsize)) == NULL)
D 34
		err("%s", strerror(errno));
E 34
I 34
		err(1, "%s", strerror(errno));
E 34
E 29
	while (nextino < ROOTINO)
		getnextinode(nextino);
}

/*
 * Free up data structures used to scan inodes.
 */
I 29
void
E 29
freeinodebuf()
{

	if (inodebuf != NULL)
D 29
		free((char *)inodebuf);
E 29
I 29
		free(inodebuf);
E 29
	inodebuf = NULL;
}

/*
 * Read specified disk blocks.
 */
I 29
void
E 29
bread(bno, buf, cnt)
	daddr_t bno;
	char *buf;
	long cnt;
{

D 29
	if (lseek(fi, bno * dev_bsize, 0) < 0) {
		perror("lseek");
		exit(1);
	}
E 29
I 29
D 30
	if (lseek(fi, (off_t)bno * dev_bsize, 0) < 0 ||
E 30
I 30
	if (lseek(fi, (off_t)bno * dev_bsize, SEEK_SET) < 0 ||
E 30
	    read(fi, buf, cnt) != cnt)
D 34
		err("block %ld", bno);
}
E 29

D 29
	if (read(fi, buf, cnt) != cnt) {
		perror("read");
		exit(1);
	}
E 29
I 29
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
	(void)fprintf(stderr, "quotacheck: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 34
I 34
		err(1, "block %ld", bno);
E 34
E 29
E 23
E 2
}
E 1
