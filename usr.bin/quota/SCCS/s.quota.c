h02415
s 00006/00003/00484
d D 8.4 95/04/28 14:33:25 bostic 23 22
c lint type for group IDs; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00007/00005/00480
d D 8.3 95/04/27 15:14:48 bostic 22 21
c lseek takes an off_t as a second argument, not a long
c From: Charles Hannum <mycroft@sun-lamp.cs.berkeley.edu>
e
s 00001/00000/00484
d D 8.2 94/11/22 16:53:44 mckusick 21 20
c needs queue.h
e
s 00005/00005/00479
d D 8.1 93/06/06 16:03:17 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00483
d D 5.13 91/11/11 11:47:59 bostic 19 18
c break UFS up into FFS/UFS/LFS/MFS
e
s 00003/00000/00481
d D 5.12 90/09/27 14:03:37 mckusick 18 17
c have to initialize quota variables here rather than in quota.h
e
s 00001/00011/00480
d D 5.11 90/06/01 17:31:36 bostic 17 16
c new copyright notice
e
s 00030/00018/00461
d D 5.10 90/05/06 16:09:33 mckusick 16 14
c allow fstab file to override location of quota files
e
s 00030/00018/00461
d R 5.10 90/05/06 15:45:30 mckusick 15 14
c allow fstab file to override location of quota file
e
s 00361/00182/00118
d D 5.9 90/05/04 23:09:04 mckusick 14 13
c first cut at new quotas
e
s 00001/00001/00299
d D 5.8 89/07/30 11:09:18 bostic 13 12
c vnodes
e
s 00004/00004/00296
d D 5.7 89/03/06 12:25:16 bostic 12 11
c pwd.h needs types.h
e
s 00010/00005/00290
d D 5.6 88/06/29 21:51:00 bostic 11 10
c install approved copyright notice
e
s 00010/00004/00285
d D 5.5 88/05/20 12:31:52 bostic 10 9
c add Berkeley specific header
e
s 00018/00018/00271
d D 5.4 86/02/24 05:05:29 lepreau 9 8
c reset overquota flags for each fs; lint
e
s 00003/00003/00286
d D 5.3 85/11/04 19:03:25 bloom 8 7
c rewrite to avoid division by zero
e
s 00021/00006/00268
d D 5.2 85/09/10 21:53:25 serge 7 6
c do EOF -> 0 quota conversion
e
s 00014/00002/00260
d D 5.1 85/05/30 19:57:00 mckusick 6 5
c Add copyright
e
s 00014/00010/00248
d D 4.5 85/05/30 12:40:42 mckusick 5 4
c check for non-existent quotas
e
s 00002/00002/00256
d D 4.4 83/06/21 11:40:26 sam 4 3
c make field a tad wider
e
s 00006/00006/00252
d D 4.3 83/05/25 16:01:19 mckusick 3 2
c update for new defines in sys/file.h; output in terms of 1K blocks
e
s 00005/00005/00253
d D 4.2 83/05/24 15:59:01 mckusick 2 1
c clean-ups for new fstab
e
s 00258/00000/00000
d D 4.1 83/05/24 15:51:08 mckusick 1 0
c date and time created 83/05/24 15:51:08 by mckusick
e
u
U
t
T
I 6
/*
D 14
 * Copyright (c) 1980 Regents of the University of California.
E 14
I 14
D 20
 * Copyright (c) 1980, 1990 Regents of the University of California.
E 14
D 10
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1980, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
I 14
 * This code is derived from software contributed to Berkeley by
 * Robert Elz at The University of Melbourne.
 *
E 14
D 17
 * Redistribution and use in source and binary forms are permitted
D 11
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 11
I 11
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
E 17
I 17
 * %sccs.include.redist.c%
E 17
E 11
E 10
 */

E 6
I 1
#ifndef lint
D 6
static char sccsid[] = "%W% (Berkeley, from Melbourne) %G%";
#endif
E 6
I 6
D 20
char copyright[] =
D 14
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 14
I 14
"%Z% Copyright (c) 1980, 1990 Regents of the University of California.\n\
E 14
 All rights reserved.\n";
E 20
I 20
static char copyright[] =
"%Z% Copyright (c) 1980, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 20
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
E 6

/*
 * Disk quota reporting program.
 */
I 12
#include <sys/param.h>
D 13
#include <sys/quota.h>
E 13
#include <sys/file.h>
#include <sys/stat.h>
I 21
#include <sys/queue.h>
I 22

E 22
E 21
I 13
D 19
#include <ufs/quota.h>
E 19
I 19
#include <ufs/ufs/quota.h>
E 19
E 13
E 12
D 22
#include <stdio.h>
#include <fstab.h>
E 22
I 22

E 22
#include <ctype.h>
D 22
#include <pwd.h>
I 14
#include <grp.h>
E 22
E 14
I 5
#include <errno.h>
I 22
#include <fstab.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
E 22
E 5

I 18
char *qfname = QUOTAFILENAME;
char *qfextension[] = INITQFNAMES;

E 18
I 14
struct quotause {
	struct	quotause *next;
	long	flags;
	struct	dqblk dqblk;
	char	fsname[MAXPATHLEN + 1];
} *getprivs();
#define	FOUND	0x01
E 14
D 12
#include <sys/param.h>
D 2
#define	QUOTA
E 2
#include <sys/quota.h>
#include <sys/file.h>
#include <sys/stat.h>
E 12

int	qflag;
int	vflag;
D 14
int	done;
int	morethanone;
I 2
char	*qfname = "quotas";
E 14
E 2

main(argc, argv)
	char *argv[];
{
D 14
	register char *cp;
I 5
	extern int errno;
E 14
I 14
D 23
	int ngroups, gidset[NGROUPS];
E 23
I 23
	int ngroups; 
	gid_t gidset[NGROUPS];
E 23
	int i, gflag = 0, uflag = 0;
	char ch;
	extern char *optarg;
	extern int optind, errno;
E 14
E 5

I 5
D 9
	if (quota(Q_SYNC, 0, 0, 0) < 0 && errno == EINVAL) {
E 9
I 9
D 14
	if (quota(Q_SYNC, 0, 0, (caddr_t)0) < 0 && errno == EINVAL) {
E 14
I 14
	if (quotactl("/", 0, 0, (caddr_t)0) < 0 && errno == EOPNOTSUPP) {
E 14
E 9
		fprintf(stderr, "There are no quotas on this system\n");
		exit(0);
	}
E 5
D 14
	argc--,argv++;
	while (argc > 0) {
		if (argv[0][0] == '-')
			for (cp = &argv[0][1]; *cp; cp++) switch (*cp) {

			case 'v':
				vflag++;
				break;

			case 'q':
				qflag++;
				break;

			default:
				fprintf(stderr, "quota: %c: unknown option\n",
					*cp);
				exit(1);
			}
		else
E 14
I 14
	while ((ch = getopt(argc, argv, "ugvq")) != EOF) {
		switch(ch) {
		case 'g':
			gflag++;
E 14
			break;
D 14
		argc--, argv++;
E 14
I 14
		case 'u':
			uflag++;
			break;
		case 'v':
			vflag++;
			break;
		case 'q':
			qflag++;
			break;
		default:
			usage();
		}
E 14
	}
D 14
	morethanone = argc > 1;
E 14
I 14
	argc -= optind;
	argv += optind;
	if (!uflag && !gflag)
		uflag++;
E 14
	if (argc == 0) {
D 14
		showuid(getuid());
E 14
I 14
		if (uflag)
			showuid(getuid());
		if (gflag) {
			ngroups = getgroups(NGROUPS, gidset);
			if (ngroups < 0) {
				perror("quota: getgroups");
				exit(1);
			}
			for (i = 1; i < ngroups; i++)
				showgid(gidset[i]);
		}
E 14
		exit(0);
	}
D 14
	for (; argc > 0; argc--, argv++) {
		if (alldigits(*argv))
			showuid(atoi(*argv));
		else
			showname(*argv);
E 14
I 14
	if (uflag && gflag)
		usage();
	if (uflag) {
		for (; argc > 0; argc--, argv++) {
			if (alldigits(*argv))
				showuid(atoi(*argv));
			else
				showusrname(*argv);
		}
		exit(0);
E 14
	}
I 14
	if (gflag) {
		for (; argc > 0; argc--, argv++) {
			if (alldigits(*argv))
				showgid(atoi(*argv));
			else
				showgrpname(*argv);
		}
		exit(0);
	}
E 14
}

I 14
usage()
{

	fprintf(stderr, "%s\n%s\n%s\n",
		"Usage: quota [-guqv]",
		"\tquota [-qv] -u username ...",
		"\tquota [-qv] -g groupname ...");
	exit(1);
}

/*
 * Print out quotas for a specified user identifier.
 */
E 14
showuid(uid)
D 14
	int uid;
E 14
I 14
	u_long uid;
E 14
{
	struct passwd *pwd = getpwuid(uid);
I 14
	u_long myuid;
	char *name;
E 14

	if (pwd == NULL)
D 14
		showquotas(uid, "(no account)");
E 14
I 14
		name = "(no account)";
E 14
	else
D 14
		showquotas(uid, pwd->pw_name);
E 14
I 14
		name = pwd->pw_name;
	myuid = getuid();
	if (uid != myuid && myuid != 0) {
		printf("quota: %s (uid %d): permission denied\n", name, uid);
		return;
	}
	showquotas(USRQUOTA, uid, name);
E 14
}

D 14
showname(name)
E 14
I 14
/*
 * Print out quotas for a specifed user name.
 */
showusrname(name)
E 14
	char *name;
{
	struct passwd *pwd = getpwnam(name);
I 14
	u_long myuid;
E 14

	if (pwd == NULL) {
		fprintf(stderr, "quota: %s: unknown user\n", name);
		return;
	}
D 14
	showquotas(pwd->pw_uid, name);
E 14
I 14
	myuid = getuid();
	if (pwd->pw_uid != myuid && myuid != 0) {
		fprintf(stderr, "quota: %s (uid %d): permission denied\n",
		    name, pwd->pw_uid);
		return;
	}
	showquotas(USRQUOTA, pwd->pw_uid, name);
E 14
}

D 14
showquotas(uid, name)
	int uid;
E 14
I 14
/*
 * Print out quotas for a specified group identifier.
 */
showgid(gid)
	u_long gid;
{
	struct group *grp = getgrgid(gid);
D 23
	int ngroups, gidset[NGROUPS];
E 23
I 23
	int ngroups;
	gid_t gidset[NGROUPS];
E 23
	register int i;
E 14
	char *name;
I 14

	if (grp == NULL)
		name = "(no entry)";
	else
		name = grp->gr_name;
	ngroups = getgroups(NGROUPS, gidset);
	if (ngroups < 0) {
		perror("quota: getgroups");
		return;
	}
	for (i = 1; i < ngroups; i++)
		if (gid == gidset[i])
			break;
	if (i >= ngroups && getuid() != 0) {
		fprintf(stderr, "quota: %s (gid %d): permission denied\n",
		    name, gid);
		return;
	}
	showquotas(GRPQUOTA, gid, name);
}

/*
 * Print out quotas for a specifed group name.
 */
showgrpname(name)
	char *name;
E 14
{
D 9
	register char c, *p;
E 9
D 14
	register struct fstab *fs;
D 5
	int myuid;
E 5
I 5
D 9
	register char *msgi = (char *)0, *msgb = (char *)0;
E 9
I 9
	register char *msgi, *msgb;
E 9
	register enab = 1;
	dev_t	fsdev;
	struct	stat statb;
	struct	dqblk dqblk;
	int myuid, fd;
	char qfilename[MAXPATHLEN + 1], iwarn[8], dwarn[8];
E 14
I 14
	struct group *grp = getgrnam(name);
D 23
	int ngroups, gidset[NGROUPS];
E 23
I 23
	int ngroups;
	gid_t gidset[NGROUPS];
E 23
	register int i;
E 14
E 5

D 14
	myuid = getuid();
	if (uid != myuid && myuid != 0) {
		printf("quota: %s (uid %d): permission denied\n", name, uid);
E 14
I 14
	if (grp == NULL) {
		fprintf(stderr, "quota: %s: unknown group\n", name);
E 14
		return;
	}
D 14
	done = 0;
D 9
	setfsent();
E 9
I 9
	(void) setfsent();
E 9
	while (fs = getfsent()) {
D 5
		register char *msgi = (char *)0, *msgb = (char *)0;
		register enab = 1;
		dev_t	fsdev;
		struct	stat statb;
		struct	dqblk dqblk;
D 2
		char qfname[MAXPATHLEN + 1], iwarn[8], dwarn[8];
E 2
I 2
		char qfilename[MAXPATHLEN + 1], iwarn[8], dwarn[8];
E 2

E 5
		if (stat(fs->fs_spec, &statb) < 0)
			continue;
I 9
		msgi = msgb = (char *) 0;
E 9
		fsdev = statb.st_rdev;
D 2
		(void) sprintf(qfname, "%s/%s", fs->fs_file, fs->fs_quotafile);
		if (stat(qfname, &statb) < 0 || statb.st_dev != fsdev)
E 2
I 2
		(void) sprintf(qfilename, "%s/%s", fs->fs_file, qfname);
		if (stat(qfilename, &statb) < 0 || statb.st_dev != fsdev)
E 2
			continue;
D 9
		if (quota(Q_GETDLIM, uid, fsdev, &dqblk) != 0) {
E 9
I 9
		if (quota(Q_GETDLIM, uid, fsdev, (caddr_t)&dqblk) != 0) {
E 9
D 2
			register fd = open(qfname, FRDONLY);
E 2
I 2
D 3
			register fd = open(qfilename, FRDONLY);
E 3
I 3
D 5
			register fd = open(qfilename, O_RDONLY);
E 3
E 2

E 5
I 5
			fd = open(qfilename, O_RDONLY);
E 5
			if (fd < 0)
				continue;
D 3
			lseek(fd, (long)(uid * sizeof (dqblk)), FSEEK_ABSOLUTE);
E 3
I 3
D 9
			lseek(fd, (long)(uid * sizeof (dqblk)), L_SET);
E 3
D 7
			if (read(fd, &dqblk, sizeof dqblk) != sizeof (dqblk)) {
E 7
I 7
			switch (read(fd, &dqblk, sizeof dqblk)) {
E 9
I 9
			(void) lseek(fd, (off_t)(uid * sizeof (dqblk)), L_SET);
			switch (read(fd, (char *)&dqblk, sizeof dqblk)) {
E 9
			case 0:			/* EOF */
				/*
				 * Convert implicit 0 quota (EOF)
				 * into an explicit one (zero'ed dqblk).
				 */
				bzero((caddr_t)&dqblk, sizeof dqblk);
				break;
E 14
I 14
	ngroups = getgroups(NGROUPS, gidset);
	if (ngroups < 0) {
		perror("quota: getgroups");
		return;
	}
	for (i = 1; i < ngroups; i++)
		if (grp->gr_gid == gidset[i])
			break;
	if (i >= ngroups && getuid() != 0) {
		fprintf(stderr, "quota: %s (gid %d): permission denied\n",
		    name, grp->gr_gid);
		return;
	}
	showquotas(GRPQUOTA, grp->gr_gid, name);
}
E 14

D 14
			case sizeof dqblk:	/* OK */
				break;
E 14
I 14
showquotas(type, id, name)
	int type;
	u_long id;
	char *name;
{
	register struct quotause *qup;
	struct quotause *quplist, *getprivs();
	char *msgi, *msgb, *timeprt();
	int myuid, fd, lines = 0;
	static int first;
	static time_t now;
E 14

D 14
			default:		/* ERROR */
				fprintf(stderr, "quota: read error in ");
				perror(qfilename);
E 7
D 9
				close(fd);
E 9
I 9
				(void) close(fd);
E 9
				continue;
			}
D 9
			close(fd);
E 9
I 9
			(void) close(fd);
E 9
D 7
			if (dqblk.dqb_isoftlimit == 0 &&
E 7
I 7
			if (!vflag && dqblk.dqb_isoftlimit == 0 &&
E 7
			    dqblk.dqb_bsoftlimit == 0)
				continue;
			enab = 0;
		}
		if (dqblk.dqb_ihardlimit &&
		    dqblk.dqb_curinodes >= dqblk.dqb_ihardlimit)
			msgi = "File count limit reached on %s";
		else if (enab && dqblk.dqb_iwarn == 0)
			msgi = "Out of inode warnings on %s";
		else if (dqblk.dqb_isoftlimit &&
		    dqblk.dqb_curinodes >= dqblk.dqb_isoftlimit)
			msgi = "Too many files on %s";
		if (dqblk.dqb_bhardlimit &&
		    dqblk.dqb_curblocks >= dqblk.dqb_bhardlimit)
			msgb = "Block limit reached on %s";
		else if (enab && dqblk.dqb_bwarn == 0)
			msgb = "Out of block warnings on %s";
		else if (dqblk.dqb_bsoftlimit &&
		    dqblk.dqb_curblocks >= dqblk.dqb_bsoftlimit)
			msgb = "Over disc quota on %s";
		if (dqblk.dqb_iwarn < MAX_IQ_WARN)
D 9
			sprintf(iwarn, "%d", dqblk.dqb_iwarn);
E 9
I 9
			(void) sprintf(iwarn, "%d", dqblk.dqb_iwarn);
E 9
		else
			iwarn[0] = '\0';
		if (dqblk.dqb_bwarn < MAX_DQ_WARN)
D 9
			sprintf(dwarn, "%d", dqblk.dqb_bwarn);
E 9
I 9
			(void) sprintf(dwarn, "%d", dqblk.dqb_bwarn);
E 9
		else
			dwarn[0] = '\0';
E 14
I 14
	if (now == 0)
		time(&now);
	quplist = getprivs(id, type);
	for (qup = quplist; qup; qup = qup->next) {
		if (!vflag &&
		    qup->dqblk.dqb_isoftlimit == 0 &&
		    qup->dqblk.dqb_ihardlimit == 0 &&
		    qup->dqblk.dqb_bsoftlimit == 0 &&
		    qup->dqblk.dqb_bhardlimit == 0)
			continue;
		msgi = (char *)0;
		if (qup->dqblk.dqb_ihardlimit &&
		    qup->dqblk.dqb_curinodes >= qup->dqblk.dqb_ihardlimit)
			msgi = "File limit reached on";
		else if (qup->dqblk.dqb_isoftlimit &&
		    qup->dqblk.dqb_curinodes >= qup->dqblk.dqb_isoftlimit)
			if (qup->dqblk.dqb_itime > now)
				msgi = "In file grace period on";
			else
				msgi = "Over file quota on";
		msgb = (char *)0;
		if (qup->dqblk.dqb_bhardlimit &&
		    qup->dqblk.dqb_curblocks >= qup->dqblk.dqb_bhardlimit)
			msgb = "Block limit reached on";
		else if (qup->dqblk.dqb_bsoftlimit &&
		    qup->dqblk.dqb_curblocks >= qup->dqblk.dqb_bsoftlimit)
			if (qup->dqblk.dqb_btime > now)
				msgb = "In block grace period on";
			else
				msgb = "Over block quota on";
E 14
		if (qflag) {
D 14
			if (msgi != (char *)0 || msgb != (char *)0)
				heading(uid, name);
E 14
I 14
			if ((msgi != (char *)0 || msgb != (char *)0) &&
			    lines++ == 0)
				heading(type, id, name, "");
E 14
			if (msgi != (char *)0)
D 14
				xprintf(msgi, fs->fs_file);
E 14
I 14
				printf("\t%s %s\n", msgi, qup->fsname);
E 14
			if (msgb != (char *)0)
D 14
				xprintf(msgb, fs->fs_file);
E 14
I 14
				printf("\t%s %s\n", msgb, qup->fsname);
E 14
			continue;
		}
D 14
		if (vflag || dqblk.dqb_curblocks || dqblk.dqb_curinodes) {
			heading(uid, name);
D 4
			printf("%8s%8d%c%7d%8d%8s%8d%c%7d%8d%8s\n"
E 4
I 4
			printf("%10s%8d%c%7d%8d%8s%8d%c%7d%8d%8s\n"
E 4
				, fs->fs_file
D 3
				, (dqblk.dqb_curblocks / (1024/DEV_BSIZE)) 
E 3
I 3
D 8
				, (dqblk.dqb_curblocks / btodb(1024)) 
E 8
I 8
				, dbtob(dqblk.dqb_curblocks) / 1024
E 14
I 14
		if (vflag ||
		    qup->dqblk.dqb_curblocks ||
		    qup->dqblk.dqb_curinodes) {
			if (lines++ == 0)
				heading(type, id, name, "");
			printf("%15s%8d%c%7d%8d%8s"
				, qup->fsname
				, dbtob(qup->dqblk.dqb_curblocks) / 1024
E 14
E 8
E 3
				, (msgb == (char *)0) ? ' ' : '*'
D 3
				, (dqblk.dqb_bsoftlimit / (1024/DEV_BSIZE)) 
				, ((dqblk.dqb_bhardlimit-1) / (1024/DEV_BSIZE)) 
E 3
I 3
D 8
				, (dqblk.dqb_bsoftlimit / btodb(1024)) 
				, (dqblk.dqb_bhardlimit / btodb(1024)) 
E 8
I 8
D 14
				, dbtob(dqblk.dqb_bsoftlimit) / 1024
				, dbtob(dqblk.dqb_bhardlimit) / 1024
E 8
E 3
				, dwarn
				, dqblk.dqb_curinodes
E 14
I 14
				, dbtob(qup->dqblk.dqb_bsoftlimit) / 1024
				, dbtob(qup->dqblk.dqb_bhardlimit) / 1024
				, (msgb == (char *)0) ? ""
				    : timeprt(qup->dqblk.dqb_btime));
			printf("%8d%c%7d%8d%8s\n"
				, qup->dqblk.dqb_curinodes
E 14
				, (msgi == (char *)0) ? ' ' : '*'
D 14
				, dqblk.dqb_isoftlimit
D 3
				, dqblk.dqb_ihardlimit-1
E 3
I 3
				, dqblk.dqb_ihardlimit
E 3
				, iwarn
E 14
I 14
				, qup->dqblk.dqb_isoftlimit
				, qup->dqblk.dqb_ihardlimit
				, (msgi == (char *)0) ? ""
				    : timeprt(qup->dqblk.dqb_itime)
E 14
			);
I 14
			continue;
E 14
		}
	}
D 9
	endfsent();
E 9
I 9
D 14
	(void) endfsent();
E 9
	if (!done && !qflag) {
		if (morethanone)
D 9
			putchar('\n');
E 9
I 9
			(void) putchar('\n');
E 9
		xprintf("Disc quotas for %s (uid %d):", name, uid);
		xprintf("none.");
E 14
I 14
	if (!qflag && lines == 0)
		heading(type, id, name, "none");
}

heading(type, id, name, tag)
	int type;
	u_long id;
	char *name, *tag;
{

	printf("Disk quotas for %s %s (%cid %d): %s\n", qfextension[type],
	    name, *qfextension[type], id, tag);
	if (!qflag && tag[0] == '\0') {
		printf("%15s%8s %7s%8s%8s%8s %7s%8s%8s\n"
			, "Filesystem"
			, "blocks"
			, "quota"
			, "limit"
			, "grace"
			, "files"
			, "quota"
			, "limit"
			, "grace"
		);
E 14
	}
D 7
	xprintf(0);
E 7
I 7
D 14
	xprintf((char *)0);
E 14
E 7
}

D 14
heading(uid, name)
	int uid;
	char *name;
E 14
I 14
/*
 * Calculate the grace period and return a printable string for it.
 */
char *
timeprt(seconds)
	time_t seconds;
E 14
{
I 14
	time_t hours, minutes;
	static char buf[20];
	static time_t now;
E 14

D 14
	if (done++)
		return;
D 7
	xprintf(0);
E 7
I 7
	xprintf((char *)0);
E 7
	if (qflag) {
		if (!morethanone)
			return;
		xprintf("User %s (uid %d):", name, uid);
D 7
		xprintf(0);
E 7
I 7
		xprintf((char *)0);
E 7
		return;
E 14
I 14
	if (now == 0)
		time(&now);
	if (now > seconds)
		return ("none");
	seconds -= now;
	minutes = (seconds + 30) / 60;
	hours = (minutes + 30) / 60;
	if (hours >= 36) {
		sprintf(buf, "%ddays", (hours + 12) / 24);
		return (buf);
E 14
	}
D 9
	putchar('\n');
E 9
I 9
D 14
	(void) putchar('\n');
E 9
	xprintf("Disc quotas for %s (uid %d):", name, uid);
D 7
	xprintf(0);
E 7
I 7
	xprintf((char *)0);
E 7
D 4
	printf("%8s%8s %7s%8s%8s%8s %7s%8s%8s\n"
E 4
I 4
	printf("%10s%8s %7s%8s%8s%8s %7s%8s%8s\n"
E 4
		, "Filsys"
		, "current"
		, "quota"
		, "limit"
		, "#warns"
		, "files"
		, "quota"
		, "limit"
		, "#warns"
	);
E 14
I 14
	if (minutes >= 60) {
		sprintf(buf, "%2d:%d", minutes / 60, minutes % 60);
		return (buf);
	}
	sprintf(buf, "%2d", minutes);
	return (buf);
E 14
}

I 7
D 14
/*VARARGS1*/
E 7
xprintf(fmt, arg1, arg2, arg3, arg4, arg5, arg6)
	char *fmt;
E 14
I 14
/*
 * Collect the requested quota information.
 */
struct quotause *
getprivs(id, quotatype)
	register long id;
	int quotatype;
E 14
{
D 14
	char	buf[100];
	static int column;
E 14
I 14
	register struct fstab *fs;
D 16
	char qfilename[MAXPATHLEN + 1];
E 16
	register struct quotause *qup, *quptail;
	struct quotause *quphead;
I 16
	char *qfpathname;
E 16
	int qcmd, fd;
E 14

D 14
	if (fmt == 0 && column || column >= 40) {
D 9
		putchar('\n');
E 9
I 9
		(void) putchar('\n');
E 9
		column = 0;
E 14
I 14
	setfsent();
	quphead = (struct quotause *)0;
	qcmd = QCMD(Q_GETQUOTA, quotatype);
	while (fs = getfsent()) {
D 16
		if (!hasquota(fs->fs_mntops, quotatype))
E 16
I 16
		if (strcmp(fs->fs_vfstype, "ufs"))
E 16
			continue;
D 16
		sprintf(qfilename, "%s/%s.%s", fs->fs_file, qfname,
		    qfextension[quotatype]);
		if ((fd = open(qfilename, O_RDONLY)) < 0) {
			perror(qfilename);
E 16
I 16
		if (!hasquota(fs, quotatype, &qfpathname))
E 16
			continue;
D 16
		}
E 16
		if ((qup = (struct quotause *)malloc(sizeof *qup)) == NULL) {
			fprintf(stderr, "quota: out of memory\n");
			exit(2);
		}
D 16
		if (quotactl(qfilename, qcmd, id, &qup->dqblk) != 0) {
E 16
I 16
		if (quotactl(fs->fs_file, qcmd, id, &qup->dqblk) != 0) {
			if ((fd = open(qfpathname, O_RDONLY)) < 0) {
				perror(qfpathname);
				free(qup);
				continue;
			}
E 16
D 22
			lseek(fd, (long)(id * sizeof(struct dqblk)), L_SET);
E 22
I 22
			lseek(fd, (off_t)(id * sizeof(struct dqblk)), L_SET);
E 22
			switch (read(fd, &qup->dqblk, sizeof(struct dqblk))) {
			case 0:			/* EOF */
				/*
				 * Convert implicit 0 quota (EOF)
				 * into an explicit one (zero'ed dqblk)
				 */
				bzero((caddr_t)&qup->dqblk,
				    sizeof(struct dqblk));
				break;

			case sizeof(struct dqblk):	/* OK */
				break;

			default:		/* ERROR */
				fprintf(stderr, "quota: read error");
D 16
				perror(qfilename);
E 16
I 16
				perror(qfpathname);
E 16
				close(fd);
				free(qup);
				continue;
			}
I 16
			close(fd);
E 16
		}
D 16
		close(fd);
E 16
		strcpy(qup->fsname, fs->fs_file);
		if (quphead == NULL)
			quphead = qup;
		else
			quptail->next = qup;
		quptail = qup;
		qup->next = 0;
E 14
	}
D 14
	if (fmt == 0)
		return;
D 9
	sprintf(buf, fmt, arg1, arg2, arg3, arg4, arg5, arg6);
E 9
I 9
	(void) sprintf(buf, fmt, arg1, arg2, arg3, arg4, arg5, arg6);
E 9
	if (column != 0 && strlen(buf) < 39)
		while (column++ < 40)
D 9
			putchar(' ');
E 9
I 9
			(void) putchar(' ');
E 9
	else if (column) {
D 9
		putchar('\n');
E 9
I 9
		(void) putchar('\n');
E 9
		column = 0;
E 14
I 14
	endfsent();
	return (quphead);
}

/*
 * Check to see if a particular quota is to be enabled.
 */
D 16
hasquota(options, type)
	char *options;
E 16
I 16
hasquota(fs, type, qfnamep)
	register struct fstab *fs;
E 16
	int type;
I 16
	char **qfnamep;
E 16
{
	register char *opt;
D 16
	char buf[BUFSIZ];
	char *strtok();
E 16
I 16
	char *cp, *index(), *strtok();
E 16
	static char initname, usrname[100], grpname[100];
I 16
	static char buf[BUFSIZ];
E 16

	if (!initname) {
		sprintf(usrname, "%s%s", qfextension[USRQUOTA], qfname);
		sprintf(grpname, "%s%s", qfextension[GRPQUOTA], qfname);
		initname = 1;
E 14
	}
D 14
	printf("%s", buf);
	column += strlen(buf);
E 14
I 14
D 16
	strcpy(buf, options);
E 16
I 16
	strcpy(buf, fs->fs_mntops);
E 16
	for (opt = strtok(buf, ","); opt; opt = strtok(NULL, ",")) {
I 16
		if (cp = index(opt, '='))
			*cp++ = '\0';
E 16
		if (type == USRQUOTA && strcmp(opt, usrname) == 0)
D 16
			return(1);
E 16
I 16
			break;
E 16
		if (type == GRPQUOTA && strcmp(opt, grpname) == 0)
D 16
			return(1);
E 16
I 16
			break;
E 16
	}
D 16
	return (0);
E 16
I 16
	if (!opt)
		return (0);
	if (cp) {
		*qfnamep = cp;
		return (1);
	}
	(void) sprintf(buf, "%s/%s.%s", fs->fs_file, qfname, qfextension[type]);
	*qfnamep = buf;
	return (1);
E 16
E 14
}

alldigits(s)
	register char *s;
{
	register c;

	c = *s++;
	do {
		if (!isdigit(c))
			return (0);
	} while (c = *s++);
	return (1);
}
E 1
