h10894
s 00003/00002/00695
d D 8.3 95/04/27 15:11:47 bostic 26 25
c lseek's second argument isn't a long, it's an off_t
c From: Charles Hannum <mycroft@sun-lamp.cs.berkeley.edu>
e
s 00001/00000/00696
d D 8.2 94/11/22 16:52:25 mckusick 25 24
c needs queue.h
e
s 00005/00005/00691
d D 8.1 93/06/06 13:56:29 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00695
d D 5.17 93/05/19 14:47:52 bostic 23 22
c include  unistd.h for truncate prototype
e
s 00001/00001/00694
d D 5.16 91/11/11 11:49:00 bostic 22 21
c break UFS up into FFS/UFS/LFS/MFS
e
s 00003/00000/00692
d D 5.15 90/09/27 14:05:59 mckusick 21 20
c have to initialize quota variables here rather than in quota.h
e
s 00002/00002/00690
d D 5.14 90/06/19 13:52:12 mckusick 20 19
c missing parameter to ftruncate
e
s 00001/00011/00691
d D 5.13 90/06/01 18:40:14 bostic 19 18
c new copyright notice
e
s 00048/00027/00654
d D 5.12 90/05/06 17:42:35 mckusick 18 17
c allow fstab to override the default quota file name
e
s 00526/00262/00155
d D 5.11 90/05/04 23:12:26 mckusick 17 16
c first cut at new quotas
e
s 00002/00002/00415
d D 5.10 89/07/30 11:09:51 bostic 16 15
c vnodes
e
s 00003/00003/00414
d D 5.9 89/05/11 14:14:20 bostic 15 14
c file reorg, pathnames.h, paths.h
e
s 00002/00003/00415
d D 5.8 89/04/02 12:31:48 bostic 14 13
c add pathnames.h
e
s 00006/00007/00412
d D 5.7 89/03/05 14:07:58 bostic 13 12
c pwd.h needs types.h
e
s 00010/00005/00409
d D 5.6 88/06/18 14:34:13 bostic 12 11
c install approved copyright notice
e
s 00010/00004/00404
d D 5.5 88/05/20 12:08:55 bostic 11 10
c add Berkeley specific header
e
s 00004/00004/00404
d D 5.4 88/02/27 14:45:45 bostic 10 9
c 2.10BSD long/int fixes
e
s 00004/00004/00404
d D 5.3 85/11/04 19:04:50 bloom 9 8
c rewrite to avoid division by zero
e
s 00015/00013/00393
d D 5.2 85/09/09 19:21:40 serge 8 7
c allow editing of user's quota on file systems where he has 0 blocks
e
s 00014/00002/00392
d D 5.1 85/05/30 19:54:08 mckusick 7 6
c Add copyright
e
s 00013/00006/00381
d D 4.6 85/05/24 17:03:05 mckusick 6 5
c warn of kernels not compiled for quotas
e
s 00005/00013/00382
d D 4.5 83/06/12 01:41:18 sam 5 4
c new signals
e
s 00039/00015/00356
d D 4.4 83/05/27 16:06:33 mckusick 4 3
c add -p (prototype) flag to allow bulk quota setting
e
s 00002/00002/00369
d D 4.3 83/05/25 16:03:15 mckusick 3 2
c new defines in file.h
e
s 00026/00026/00345
d D 4.2 83/05/25 14:50:16 mckusick 2 1
c fix bug in updating quota files; change to work in 1K units
e
s 00371/00000/00000
d D 4.1 83/05/24 14:34:12 mckusick 1 0
c date and time created 83/05/24 14:34:12 by mckusick
e
u
U
t
T
I 7
/*
D 17
 * Copyright (c) 1980 Regents of the University of California.
E 17
I 17
D 24
 * Copyright (c) 1980, 1990 Regents of the University of California.
E 17
D 11
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
 * All rights reserved.
E 24
I 24
 * Copyright (c) 1980, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 24
 *
I 17
 * This code is derived from software contributed to Berkeley by
 * Robert Elz at The University of Melbourne.
 *
E 17
D 19
 * Redistribution and use in source and binary forms are permitted
D 12
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 12
I 12
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
E 19
I 19
 * %sccs.include.redist.c%
E 19
E 12
E 11
 */

E 7
I 1
#ifndef lint
D 7
static char sccsid[] = "%W% (Berkeley, from Melbourne) %G%";
#endif
E 7
I 7
D 24
char copyright[] =
D 17
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 17
I 17
"%Z% Copyright (c) 1980, 1990 Regents of the University of California.\n\
E 17
 All rights reserved.\n";
E 24
I 24
static char copyright[] =
"%Z% Copyright (c) 1980, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 24
D 11
#endif not lint
E 11
I 11
#endif /* not lint */
E 11

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 11
#endif not lint
E 11
I 11
#endif /* not lint */
E 11
E 7

/*
 * Disk quota editor.
 */
D 13
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <pwd.h>
#include <ctype.h>
#include <fstab.h>

E 13
#include <sys/param.h>
D 2
#define	QUOTA
E 2
I 2
D 4
#define QUOTA
E 2
#include <sys/quota.h>
E 4
#include <sys/stat.h>
#include <sys/file.h>
I 4
D 5
#define QUOTA
E 5
D 16
#include <sys/quota.h>
I 13
#include <signal.h>
E 16
I 16
D 17
#include <sys/signal.h>
E 17
I 17
#include <sys/wait.h>
I 25
#include <sys/queue.h>
E 25
E 17
D 22
#include <ufs/quota.h>
E 22
I 22
#include <ufs/ufs/quota.h>
E 22
E 16
#include <errno.h>
#include <fstab.h>
#include <pwd.h>
I 17
#include <grp.h>
E 17
#include <ctype.h>
#include <stdio.h>
I 17
#include <string.h>
I 23
#include <unistd.h>
E 23
E 17
I 14
#include "pathnames.h"
E 14
E 13
E 4

I 21
char *qfname = QUOTAFILENAME;
char *qfextension[] = INITQFNAMES;
char *quotagroup = QUOTAGROUP;
E 21
D 2
#ifdef MELBOURNE
#define	DEFEDITOR	"/bin/ed"
#else
E 2
D 14
#define	DEFEDITOR	"/usr/ucb/vi"
D 2
#endif
E 2

E 14
D 17
struct	dquot dq[NMOUNT];
struct	dquot odq[NMOUNT];
char	dqf[NMOUNT][MAXPATHLEN + 1];
char	odqf[NMOUNT][MAXPATHLEN + 1];
E 17
I 17
char tmpfil[] = _PATH_TMP;
E 17

D 15
char	tmpfil[] = "/tmp/EdP.aXXXXX";
E 15
I 15
D 17
char	tmpfil[] = _PATH_TMP;
E 15
I 2
char	*qfname = "quotas";
E 2
D 4
char	*arg0;
E 4
char	*getenv();
E 17
I 17
struct quotause {
	struct	quotause *next;
	long	flags;
	struct	dqblk dqblk;
	char	fsname[MAXPATHLEN + 1];
I 18
	char	qfname[1];	/* actually longer */
E 18
} *getprivs();
#define	FOUND	0x01
E 17

main(argc, argv)
D 17
	char **argv;
E 17
I 17
	register char **argv;
	int argc;
E 17
{
I 4
D 17
	int uid;
	char *arg0;
E 17
I 17
	register struct quotause *qup, *protoprivs, *curprivs;
	extern char *optarg;
	extern int optind;
	register long id, protoid;
	register int quotatype, tmpfd;
	char *protoname, ch;
	int tflag = 0, pflag = 0;
E 17
E 4

D 17
	mktemp(tmpfil);
	close(creat(tmpfil, 0600));
	chown(tmpfil, getuid(), getgid());
	arg0 = *argv++;
	if (argc < 2) {
D 4
		fprintf(stderr, "Usage: %s username ...\n", arg0);
E 4
I 4
		fprintf(stderr, "Usage: %s [-p username] username ...\n", arg0);
E 4
		unlink(tmpfil);
		exit(1);
	}
	--argc;
E 17
I 17
	if (argc < 2)
		usage();
E 17
	if (getuid()) {
D 17
		fprintf(stderr, "%s: permission denied\n", arg0);
		unlink(tmpfil);
E 17
I 17
		fprintf(stderr, "edquota: permission denied\n");
E 17
		exit(1);
	}
D 4
	while (--argc >= 0)
		doedit(*argv++);
E 4
I 4
D 17
	if (argc > 2 && strcmp(*argv, "-p") == 0) {
		argc--, argv++;
		uid = getentry(*argv++);
		if (uid < 0) {
			unlink(tmpfil);
E 17
I 17
	quotatype = USRQUOTA;
	while ((ch = getopt(argc, argv, "ugtp:")) != EOF) {
		switch(ch) {
		case 'p':
			protoname = optarg;
			pflag++;
			break;
		case 'g':
			quotatype = GRPQUOTA;
			break;
		case 'u':
			quotatype = USRQUOTA;
			break;
		case 't':
			tflag++;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	if (pflag) {
		if ((protoid = getentry(protoname, quotatype)) == -1)
E 17
			exit(1);
I 17
		protoprivs = getprivs(protoid, quotatype);
		for (qup = protoprivs; qup; qup = qup->next) {
			qup->dqblk.dqb_btime = 0;
			qup->dqblk.dqb_itime = 0;
E 17
		}
D 17
		getprivs(uid);
		argc--;
E 17
		while (argc-- > 0) {
D 17
			uid = getentry(*argv++);
			if (uid < 0)
E 17
I 17
			if ((id = getentry(*argv++, quotatype)) < 0)
E 17
				continue;
D 17
			getdiscq(uid, odq, odqf);
			putprivs(uid);
E 17
I 17
			putprivs(id, quotatype, protoprivs);
E 17
		}
D 17
		unlink(tmpfil);
E 17
		exit(0);
	}
D 17
	while (--argc >= 0) {
		uid = getentry(*argv++);
		if (uid < 0)
E 17
I 17
	tmpfd = mkstemp(tmpfil);
	fchown(tmpfd, getuid(), getgid());
	if (tflag) {
		protoprivs = getprivs(0, quotatype);
		if (writetimes(protoprivs, tmpfd, quotatype) == 0)
			exit(1);
		if (editit(tmpfil) && readtimes(protoprivs, tmpfd))
			putprivs(0, quotatype, protoprivs);
		freeprivs(protoprivs);
		exit(0);
	}
	for ( ; argc > 0; argc--, argv++) {
		if ((id = getentry(*argv, quotatype)) == -1)
E 17
			continue;
D 17
		getprivs(uid);
		if (editit())
			putprivs(uid);
E 17
I 17
		curprivs = getprivs(id, quotatype);
		if (writeprivs(curprivs, tmpfd, *argv, quotatype) == 0)
			continue;
		if (editit(tmpfil) && readprivs(curprivs, tmpfd))
			putprivs(id, quotatype, curprivs);
		freeprivs(curprivs);
E 17
	}
I 17
	close(tmpfd);
E 17
E 4
	unlink(tmpfil);
	exit(0);
}

D 4
doedit(name)
	register char *name;
E 4
I 4
D 17
getentry(name)
E 17
I 17
usage()
{
	fprintf(stderr, "%s%s%s%s",
		"Usage: edquota [-u] [-p username] username ...\n",
		"\tedquota -g [-p groupname] groupname ...\n",
		"\tedquota [-u] -t\n", "\tedquota -g -t\n");
	exit(1);
}

/*
 * This routine converts a name for a particular quota type to
 * an identifier. This routine must agree with the kernel routine
 * getinoquota as to the interpretation of quota types.
 */
getentry(name, quotatype)
E 17
	char *name;
I 17
	int quotatype;
E 17
E 4
{
D 4
	register uid;
	register struct passwd *pw;
E 4
I 4
	struct passwd *pw;
D 17
	int uid;
E 17
I 17
	struct group *gr;
E 17
E 4

	if (alldigits(name))
D 17
		uid = atoi(name);
	else if (pw = getpwnam(name))
		uid = pw->pw_uid;
	else {
E 17
I 17
		return (atoi(name));
	switch(quotatype) {
	case USRQUOTA:
		if (pw = getpwnam(name))
			return (pw->pw_uid);
E 17
D 4
		fprintf(stderr, "%s: no such user\n");
E 4
I 4
		fprintf(stderr, "%s: no such user\n", name);
E 4
D 17
		sleep(1);
D 4
		return;
E 4
I 4
		return (-1);
E 17
I 17
		break;
	case GRPQUOTA:
		if (gr = getgrnam(name))
			return (gr->gr_gid);
		fprintf(stderr, "%s: no such group\n", name);
		break;
	default:
		fprintf(stderr, "%d: unknown quota type\n", quotatype);
		break;
E 17
E 4
	}
D 4
	getprivs(uid);
	if (editit())
		putprivs(uid);
E 4
I 4
D 17
	return (uid);
E 17
I 17
	sleep(1);
	return (-1);
E 17
E 4
}

D 17
editit()
E 17
I 17
/*
 * Collect the requested quota information.
 */
struct quotause *
getprivs(id, quotatype)
	register long id;
	int quotatype;
E 17
{
D 10
	register pid, xpid;
D 5
	int stat;
E 5
I 5
	int stat, omask;
E 10
I 10
D 17
	register int pid, xpid;
E 17
I 17
	register struct fstab *fs;
D 18
	char qfilename[MAXPATHLEN + 1];
E 18
	register struct quotause *qup, *quptail;
	struct quotause *quphead;
D 18
	int qcmd, fd;
E 18
I 18
	int qcmd, qupsize, fd;
	char *qfpathname;
E 18
	static int warned = 0;
	extern int errno;

	setfsent();
	quphead = (struct quotause *)0;
	qcmd = QCMD(Q_GETQUOTA, quotatype);
	while (fs = getfsent()) {
D 18
		if (!hasquota(fs->fs_mntops, quotatype))
E 18
I 18
		if (strcmp(fs->fs_vfstype, "ufs"))
E 18
			continue;
D 18
		sprintf(qfilename, "%s/%s.%s", fs->fs_file, qfname,
		    qfextension[quotatype]);
		if ((fd = open(qfilename, O_RDWR|O_CREAT, 0640)) < 0) {
			perror(qfilename);
E 18
I 18
		if (!hasquota(fs, quotatype, &qfpathname))
E 18
			continue;
D 18
		}
		if ((qup = (struct quotause *)malloc(sizeof *qup)) == NULL) {
E 18
I 18
		qupsize = sizeof(*qup) + strlen(qfpathname);
		if ((qup = (struct quotause *)malloc(qupsize)) == NULL) {
E 18
			fprintf(stderr, "edquota: out of memory\n");
			exit(2);
		}
D 18
		if (quotactl(qfilename, qcmd, id, &qup->dqblk) != 0) {
E 18
I 18
		if (quotactl(fs->fs_file, qcmd, id, &qup->dqblk) != 0) {
E 18
	    		if (errno == EOPNOTSUPP && !warned) {
				warned++;
				fprintf(stderr, "Warning: %s\n",
				    "Quotas are not compiled into this kernel");
				sleep(3);
			}
I 18
			if ((fd = open(qfpathname, O_RDONLY)) < 0) {
				fd = open(qfpathname, O_RDWR|O_CREAT, 0640);
				if (fd < 0 && errno != ENOENT) {
					perror(qfpathname);
					free(qup);
					continue;
				}
				fprintf(stderr, "Creating quota file %s\n",
				    qfpathname);
				sleep(3);
				(void) fchown(fd, getuid(),
				    getentry(quotagroup, GRPQUOTA));
				(void) fchmod(fd, 0640);
			}
E 18
D 26
			lseek(fd, (long)(id * sizeof(struct dqblk)), L_SET);
E 26
I 26
			lseek(fd, (off_t)(id * sizeof(struct dqblk)), L_SET);
E 26
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
				fprintf(stderr, "edquota: read error in ");
D 18
				perror(qfilename);
E 18
I 18
				perror(qfpathname);
E 18
				close(fd);
				free(qup);
				continue;
			}
I 18
			close(fd);
E 18
		}
D 18
		close(fd);
E 18
I 18
		strcpy(qup->qfname, qfpathname);
E 18
		strcpy(qup->fsname, fs->fs_file);
		if (quphead == NULL)
			quphead = qup;
		else
			quptail->next = qup;
		quptail = qup;
		qup->next = 0;
	}
	endfsent();
	return (quphead);
}

/*
 * Store the requested quota information.
 */
putprivs(id, quotatype, quplist)
	long id;
	int quotatype;
	struct quotause *quplist;
{
	register struct quotause *qup;
D 18
	char qfilename[MAXPATHLEN + 1];
E 18
	int qcmd, fd;

	qcmd = QCMD(Q_SETQUOTA, quotatype);
	for (qup = quplist; qup; qup = qup->next) {
D 18
		sprintf(qfilename, "%s/%s.%s", qup->fsname, qfname,
		    qfextension[quotatype]);
		if (quotactl(qfilename, qcmd, id, &qup->dqblk) == 0)
E 18
I 18
		if (quotactl(qup->fsname, qcmd, id, &qup->dqblk) == 0)
E 18
			continue;
D 18
		if ((fd = open(qfilename, O_WRONLY)) < 0) {
			perror(qfilename);
E 18
I 18
		if ((fd = open(qup->qfname, O_WRONLY)) < 0) {
			perror(qup->qfname);
E 18
		} else {
D 26
			lseek(fd, (long)id * (long)sizeof (struct dqblk), 0);
E 26
I 26
			lseek(fd,
			    (off_t)(id * (long)sizeof (struct dqblk)), L_SET);
E 26
			if (write(fd, &qup->dqblk, sizeof (struct dqblk)) !=
			    sizeof (struct dqblk)) {
				fprintf(stderr, "edquota: ");
D 18
				perror(qfilename);
E 18
I 18
				perror(qup->qfname);
E 18
			}
			close(fd);
		}
	}
}

/*
 * Take a list of priviledges and get it edited.
 */
editit(tmpfile)
	char *tmpfile;
{
E 17
	long omask;
D 17
	int stat;
E 17
I 17
	int pid, stat;
	extern char *getenv();
E 17
E 10
E 5

D 5
	sighold(SIGINT);
	sighold(SIGQUIT);
	sighold(SIGHUP);

E 5
I 5
D 10
#define	mask(s)	(1<<((s)-1))
	omask = sigblock(mask(SIGINT)|mask(SIGQUIT)|mask(SIGHUP));
E 10
I 10
	omask = sigblock(sigmask(SIGINT)|sigmask(SIGQUIT)|sigmask(SIGHUP));
E 10
E 5
 top:
	if ((pid = fork()) < 0) {
		extern errno;

		if (errno == EPROCLIM) {
			fprintf(stderr, "You have too many processes\n");
			return(0);
		}
		if (errno == EAGAIN) {
			sleep(1);
			goto top;
		}
		perror("fork");
		return (0);
	}
	if (pid == 0) {
		register char *ed;

D 5
		sigrelse(SIGINT);
		sigrelse(SIGQUIT);
		sigrelse(SIGHUP);
E 5
I 5
		sigsetmask(omask);
E 5
		setgid(getgid());
		setuid(getuid());
D 5

E 5
		if ((ed = getenv("EDITOR")) == (char *)0)
D 14
			ed = DEFEDITOR;
E 14
I 14
D 15
			ed = _PATH_EDITOR;
E 15
I 15
			ed = _PATH_VI;
E 15
E 14
D 17
		execlp(ed, ed, tmpfil, 0);
E 17
I 17
		execlp(ed, ed, tmpfile, 0);
E 17
		perror(ed);
		exit(1);
	}
D 17
	while ((xpid = wait(&stat)) >= 0)
		if (xpid == pid)
			break;
E 17
I 17
	waitpid(pid, &stat, 0);
E 17
D 5
	sigrelse(SIGINT);
	sigrelse(SIGQUIT);
	sigrelse(SIGHUP);
E 5
I 5
	sigsetmask(omask);
E 5
D 17
	return (!stat);
E 17
I 17
	if (!WIFEXITED(stat) || WEXITSTATUS(stat) != 0)
		return (0);
	return (1);
E 17
}

D 17
getprivs(uid)
	register uid;
E 17
I 17
/*
 * Convert a quotause list to an ASCII file.
 */
writeprivs(quplist, outfd, name, quotatype)
	struct quotause *quplist;
	int outfd;
	char *name;
	int quotatype;
E 17
{
D 17
	register i;
E 17
I 17
	register struct quotause *qup;
E 17
	FILE *fd;

D 17
	getdiscq(uid, dq, dqf);
	for (i = 0; i < NMOUNT; i++) {
		odq[i] = dq[i];
		strcpy(odqf[i], dqf[i]);
	}
	if ((fd = fopen(tmpfil, "w")) == NULL) {
E 17
I 17
D 20
	ftruncate(outfd);
E 20
I 20
	ftruncate(outfd, 0);
E 20
	lseek(outfd, 0, L_SET);
	if ((fd = fdopen(dup(outfd), "w")) == NULL) {
E 17
		fprintf(stderr, "edquota: ");
		perror(tmpfil);
		exit(1);
	}
D 17
	for (i = 0; i < NMOUNT; i++) {
		if (*dqf[i] == '\0')
			continue;
		fprintf(fd,
"fs %s blocks (soft = %d, hard = %d) inodes (soft = %d, hard = %d)\n"
			, dqf[i]
D 2
			, dq[i].dq_bsoftlimit
			, dq[i].dq_bhardlimit
E 2
I 2
D 9
			, dq[i].dq_bsoftlimit / btodb(1024)
			, dq[i].dq_bhardlimit / btodb(1024)
E 9
I 9
			, dbtob(dq[i].dq_bsoftlimit) / 1024
			, dbtob(dq[i].dq_bhardlimit) / 1024
E 9
E 2
			, dq[i].dq_isoftlimit
			, dq[i].dq_ihardlimit
		);
E 17
I 17
	fprintf(fd, "Quotas for %s %s:\n", qfextension[quotatype], name);
	for (qup = quplist; qup; qup = qup->next) {
		fprintf(fd, "%s: %s %d, limits (soft = %d, hard = %d)\n",
		    qup->fsname, "blocks in use:",
		    dbtob(qup->dqblk.dqb_curblocks) / 1024,
		    dbtob(qup->dqblk.dqb_bsoftlimit) / 1024,
		    dbtob(qup->dqblk.dqb_bhardlimit) / 1024);
		fprintf(fd, "%s %d, limits (soft = %d, hard = %d)\n",
		    "\tinodes in use:", qup->dqblk.dqb_curinodes,
		    qup->dqblk.dqb_isoftlimit, qup->dqblk.dqb_ihardlimit);
E 17
	}
	fclose(fd);
I 17
	return (1);
E 17
}

D 17
putprivs(uid)
	register uid;
E 17
I 17
/*
 * Merge changes to an ASCII file into a quotause list.
 */
readprivs(quplist, infd)
	struct quotause *quplist;
	int infd;
E 17
{
D 17
	register i, j;
	int n;
E 17
I 17
	register struct quotause *qup;
E 17
	FILE *fd;
D 17
	char line[BUFSIZ];
E 17
I 17
	int cnt;
	register char *cp;
	struct dqblk dqblk;
	char *fsp, line1[BUFSIZ], line2[BUFSIZ];
E 17

D 17
	fd = fopen(tmpfil, "r");
E 17
I 17
	lseek(infd, 0, L_SET);
	fd = fdopen(dup(infd), "r");
E 17
	if (fd == NULL) {
		fprintf(stderr, "Can't re-read temp file!!\n");
D 17
		return;
E 17
I 17
		return (0);
E 17
	}
D 17
	for (i = 0; i < NMOUNT; i++) {
		char *cp, *dp, *next();

		if (fgets(line, sizeof (line), fd) == NULL)
E 17
I 17
	/*
	 * Discard title line, then read pairs of lines to process.
	 */
	(void) fgets(line1, sizeof (line1), fd);
	while (fgets(line1, sizeof (line1), fd) != NULL &&
	       fgets(line2, sizeof (line2), fd) != NULL) {
		if ((fsp = strtok(line1, " \t:")) == NULL) {
			fprintf(stderr, "%s: bad format\n", line1);
			return (0);
		}
		if ((cp = strtok((char *)0, "\n")) == NULL) {
			fprintf(stderr, "%s: %s: bad format\n", fsp,
			    &fsp[strlen(fsp) + 1]);
			return (0);
		}
		cnt = sscanf(cp,
		    " blocks in use: %d, limits (soft = %d, hard = %d)",
		    &dqblk.dqb_curblocks, &dqblk.dqb_bsoftlimit,
		    &dqblk.dqb_bhardlimit);
		if (cnt != 3) {
			fprintf(stderr, "%s:%s: bad format\n", fsp, cp);
			return (0);
		}
		dqblk.dqb_curblocks = btodb(dqblk.dqb_curblocks * 1024);
		dqblk.dqb_bsoftlimit = btodb(dqblk.dqb_bsoftlimit * 1024);
		dqblk.dqb_bhardlimit = btodb(dqblk.dqb_bhardlimit * 1024);
		if ((cp = strtok(line2, "\n")) == NULL) {
			fprintf(stderr, "%s: %s: bad format\n", fsp, line2);
			return (0);
		}
		cnt = sscanf(cp,
		    "\tinodes in use: %d, limits (soft = %d, hard = %d)",
		    &dqblk.dqb_curinodes, &dqblk.dqb_isoftlimit,
		    &dqblk.dqb_ihardlimit);
		if (cnt != 3) {
			fprintf(stderr, "%s: %s: bad format\n", fsp, line2);
			return (0);
		}
		for (qup = quplist; qup; qup = qup->next) {
			if (strcmp(fsp, qup->fsname))
				continue;
			/*
			 * Cause time limit to be reset when the quota
			 * is next used if previously had no soft limit
			 * or were under it, but now have a soft limit
			 * and are over it.
			 */
			if (dqblk.dqb_bsoftlimit &&
			    qup->dqblk.dqb_curblocks >= dqblk.dqb_bsoftlimit &&
			    (qup->dqblk.dqb_bsoftlimit == 0 ||
			     qup->dqblk.dqb_curblocks <
			     qup->dqblk.dqb_bsoftlimit))
				qup->dqblk.dqb_btime = 0;
			if (dqblk.dqb_isoftlimit &&
			    qup->dqblk.dqb_curinodes >= dqblk.dqb_isoftlimit &&
			    (qup->dqblk.dqb_isoftlimit == 0 ||
			     qup->dqblk.dqb_curinodes <
			     qup->dqblk.dqb_isoftlimit))
				qup->dqblk.dqb_itime = 0;
			qup->dqblk.dqb_bsoftlimit = dqblk.dqb_bsoftlimit;
			qup->dqblk.dqb_bhardlimit = dqblk.dqb_bhardlimit;
			qup->dqblk.dqb_isoftlimit = dqblk.dqb_isoftlimit;
			qup->dqblk.dqb_ihardlimit = dqblk.dqb_ihardlimit;
			qup->flags |= FOUND;
			if (dqblk.dqb_curblocks == qup->dqblk.dqb_curblocks &&
			    dqblk.dqb_curinodes == qup->dqblk.dqb_curinodes)
				break;
			fprintf(stderr,
			    "%s: cannot change current allocation\n", fsp);
E 17
			break;
D 17
		cp = next(line, " \t");
		if (cp == NULL)
			break;
		*cp++ = '\0';
		while (*cp && *cp == '\t' && *cp == ' ')
			cp++;
		dp = cp, cp = next(cp, " \t");
		if (cp == NULL)
			break;
		*cp++ = '\0';
		while (*cp && *cp == '\t' && *cp == ' ')
			cp++;
		strcpy(dqf[i], dp);
		n = sscanf(cp,
"blocks (soft = %d, hard = %d) inodes (soft = %hd, hard = %hd)\n"
			, &dq[i].dq_bsoftlimit
			, &dq[i].dq_bhardlimit
			, &dq[i].dq_isoftlimit
			, &dq[i].dq_ihardlimit
		);
D 2
		if (n != 4)
			break;
E 2
I 2
		if (n != 4) {
			fprintf(stderr, "%s: bad format\n", cp);
E 17
I 17
		}
	}
	fclose(fd);
	/*
	 * Disable quotas for any filesystems that have not been found.
	 */
	for (qup = quplist; qup; qup = qup->next) {
		if (qup->flags & FOUND) {
			qup->flags &= ~FOUND;
E 17
			continue;
		}
D 9
		dq[i].dq_bsoftlimit *= btodb(1024);
		dq[i].dq_bhardlimit *= btodb(1024);
E 9
I 9
D 17
		dq[i].dq_bsoftlimit = btodb(dq[i].dq_bsoftlimit * 1024);
		dq[i].dq_bhardlimit = btodb(dq[i].dq_bhardlimit * 1024);
E 17
I 17
		qup->dqblk.dqb_bsoftlimit = 0;
		qup->dqblk.dqb_bhardlimit = 0;
		qup->dqblk.dqb_isoftlimit = 0;
		qup->dqblk.dqb_ihardlimit = 0;
E 17
E 9
E 2
	}
I 17
	return (1);
}

/*
 * Convert a quotause list to an ASCII file of grace times.
 */
writetimes(quplist, outfd, quotatype)
	struct quotause *quplist;
	int outfd;
	int quotatype;
{
	register struct quotause *qup;
	char *cvtstoa();
	FILE *fd;

D 20
	ftruncate(outfd);
E 20
I 20
	ftruncate(outfd, 0);
E 20
	lseek(outfd, 0, L_SET);
	if ((fd = fdopen(dup(outfd), "w")) == NULL) {
		fprintf(stderr, "edquota: ");
		perror(tmpfil);
		exit(1);
	}
	fprintf(fd, "Time units may be: days, hours, minutes, or seconds\n");
	fprintf(fd, "Grace period before enforcing soft limits for %ss:\n",
	    qfextension[quotatype]);
	for (qup = quplist; qup; qup = qup->next) {
		fprintf(fd, "%s: block grace period: %s, ",
		    qup->fsname, cvtstoa(qup->dqblk.dqb_btime));
		fprintf(fd, "file grace period: %s\n",
		    cvtstoa(qup->dqblk.dqb_itime));
	}
E 17
	fclose(fd);
D 17
	n = i;
	for (i = 0; i < n; i++) {
		if (*dqf[i] == '\0')
E 17
I 17
	return (1);
}

/*
 * Merge changes of grace times in an ASCII file into a quotause list.
 */
readtimes(quplist, infd)
	struct quotause *quplist;
	int infd;
{
	register struct quotause *qup;
	FILE *fd;
	int cnt;
	register char *cp;
	time_t itime, btime, iseconds, bseconds;
	char *fsp, bunits[10], iunits[10], line1[BUFSIZ];

	lseek(infd, 0, L_SET);
	fd = fdopen(dup(infd), "r");
	if (fd == NULL) {
		fprintf(stderr, "Can't re-read temp file!!\n");
		return (0);
	}
	/*
	 * Discard two title lines, then read lines to process.
	 */
	(void) fgets(line1, sizeof (line1), fd);
	(void) fgets(line1, sizeof (line1), fd);
	while (fgets(line1, sizeof (line1), fd) != NULL) {
		if ((fsp = strtok(line1, " \t:")) == NULL) {
			fprintf(stderr, "%s: bad format\n", line1);
			return (0);
		}
		if ((cp = strtok((char *)0, "\n")) == NULL) {
			fprintf(stderr, "%s: %s: bad format\n", fsp,
			    &fsp[strlen(fsp) + 1]);
			return (0);
		}
		cnt = sscanf(cp,
		    " block grace period: %d %s file grace period: %d %s",
		    &btime, bunits, &itime, iunits);
		if (cnt != 4) {
			fprintf(stderr, "%s:%s: bad format\n", fsp, cp);
			return (0);
		}
		if (cvtatos(btime, bunits, &bseconds) == 0)
			return (0);
		if (cvtatos(itime, iunits, &iseconds) == 0)
			return (0);
		for (qup = quplist; qup; qup = qup->next) {
			if (strcmp(fsp, qup->fsname))
				continue;
			qup->dqblk.dqb_btime = bseconds;
			qup->dqblk.dqb_itime = iseconds;
			qup->flags |= FOUND;
E 17
			break;
D 17
		for (j = 0; j < NMOUNT; j++) {
			if (strcmp(dqf[i], odqf[j]) == 0)
				break;
E 17
		}
D 17
		if (j >= NMOUNT)
			continue;
		*odqf[j] = '\0';
D 8
		if (dq[i].dq_isoftlimit == odq[j].dq_isoftlimit &&
		    dq[i].dq_ihardlimit == odq[j].dq_ihardlimit &&
		    dq[i].dq_bsoftlimit == odq[j].dq_bsoftlimit &&
		    dq[i].dq_bhardlimit == odq[j].dq_bhardlimit) {
D 2
			for (j = i; j < 15; j++) {
E 2
I 2
			for (j = i; j < NMOUNT; j++) {
E 2
				dq[j] = dq[j+1];
				strcpy(dqf[j], dqf[j+1]);
			}
			*dqf[j] = '\0';
			i--;
			continue;
		}
E 8
		/*
		 * This isn't really good enough, it is quite likely
		 * to have changed while we have been away editing,
		 * but it's not important enough to worry about at
		 * the minute.
		 */
		dq[i].dq_curblocks = odq[j].dq_curblocks;
		dq[i].dq_curinodes = odq[j].dq_curinodes;
		/*
		 * If we've upped the inode or disk block limits
		 * and the guy is out of warnings, reinitialize.
		 */
		if (dq[i].dq_bsoftlimit > odq[j].dq_bsoftlimit &&
		    dq[i].dq_bwarn == 0)
			dq[i].dq_bwarn = MAX_DQ_WARN;
		if (dq[i].dq_isoftlimit > odq[j].dq_isoftlimit &&
		    dq[i].dq_iwarn == 0)
			dq[i].dq_iwarn = MAX_IQ_WARN;
E 17
	}
D 17
	if (i < NMOUNT) {
		for (j = 0; j < NMOUNT; j++) {
			if (*odqf[j] == '\0')
				continue;
			strcpy(dqf[i], odqf[j]);
			dq[i].dq_isoftlimit = 0;
			dq[i].dq_ihardlimit = 0;
			dq[i].dq_bsoftlimit = 0;
			dq[i].dq_bhardlimit = 0;
			/*
			 * Same applies as just above
			 * but matters not at all, as we are just
			 * turning quota'ing off for this filesys.
			 */
			dq[i].dq_curblocks = odq[j].dq_curblocks;
			dq[i].dq_curinodes = odq[j].dq_curinodes;
			if (++i >= NMOUNT)
				break;
E 17
I 17
	fclose(fd);
	/*
	 * reset default grace periods for any filesystems
	 * that have not been found.
	 */
	for (qup = quplist; qup; qup = qup->next) {
		if (qup->flags & FOUND) {
			qup->flags &= ~FOUND;
			continue;
E 17
		}
I 17
		qup->dqblk.dqb_btime = 0;
		qup->dqblk.dqb_itime = 0;
E 17
	}
D 17
	if (*dqf[0])
		putdiscq(uid, dq, dqf);
E 17
I 17
	return (1);
E 17
}

I 17
/*
 * Convert seconds to ASCII times.
 */
E 17
char *
D 17
next(cp, match)
	register char *cp;
	char *match;
E 17
I 17
cvtstoa(time)
	time_t time;
E 17
{
D 17
	register char *dp;
E 17
I 17
	static char buf[20];
E 17

D 17
	while (cp && *cp) {
		for (dp = match; dp && *dp; dp++)
			if (*dp == *cp)
				return (cp);
		cp++;
E 17
I 17
	if (time % (24 * 60 * 60) == 0) {
		time /= 24 * 60 * 60;
		sprintf(buf, "%d day%s", time, time == 1 ? "" : "s");
	} else if (time % (60 * 60) == 0) {
		time /= 60 * 60;
		sprintf(buf, "%d hour%s", time, time == 1 ? "" : "s");
	} else if (time % 60 == 0) {
		time /= 60;
		sprintf(buf, "%d minute%s", time, time == 1 ? "" : "s");
	} else
		sprintf(buf, "%d second%s", time, time == 1 ? "" : "s");
	return (buf);
}

/*
 * Convert ASCII input times to seconds.
 */
cvtatos(time, units, seconds)
	time_t time;
	char *units;
	time_t *seconds;
{

	if (bcmp(units, "second", 6) == 0)
		*seconds = time;
	else if (bcmp(units, "minute", 6) == 0)
		*seconds = time * 60;
	else if (bcmp(units, "hour", 4) == 0)
		*seconds = time * 60 * 60;
	else if (bcmp(units, "day", 3) == 0)
		*seconds = time * 24 * 60 * 60;
	else {
		printf("%s: bad units, specify %s\n", units,
		    "days, hours, minutes, or seconds");
		return (0);
E 17
	}
D 17
	return ((char *)0);
E 17
I 17
	return (1);
E 17
}

I 17
/*
 * Free a list of quotause structures.
 */
freeprivs(quplist)
	struct quotause *quplist;
{
	register struct quotause *qup, *nextqup;

	for (qup = quplist; qup; qup = nextqup) {
		nextqup = qup->next;
		free(qup);
	}
}

/*
 * Check whether a string is completely composed of digits.
 */
E 17
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

D 17
getdiscq(uid, dq, dqf)
	register uid;
	register struct dquot *dq;
	register char (*dqf)[MAXPATHLEN + 1];
E 17
I 17
/*
 * Check to see if a particular quota is to be enabled.
 */
D 18
hasquota(options, type)
	char *options;
E 18
I 18
hasquota(fs, type, qfnamep)
	register struct fstab *fs;
E 18
	int type;
I 18
	char **qfnamep;
E 18
E 17
{
D 17
	register struct fstab *fs;
D 2
	char qfname[MAXPATHLEN + 1];
E 2
I 2
	char qfilename[MAXPATHLEN + 1];
I 6
	struct stat statb;
	struct dqblk dqblk;
	dev_t fsdev;
	int fd;
	static int warned = 0;
	extern int errno;
E 17
I 17
	register char *opt;
D 18
	char buf[BUFSIZ];
	char *strtok();
E 18
I 18
	char *cp, *index(), *strtok();
E 18
	static char initname, usrname[100], grpname[100];
I 18
	static char buf[BUFSIZ];
E 18
E 17
E 6
E 2

D 17
	setfsent();
	while (fs = getfsent()) {
D 6
		struct	stat statb;
		struct	dqblk dqblk;
		dev_t	fsdev;

E 6
		if (stat(fs->fs_spec, &statb) < 0)
			continue;
		fsdev = statb.st_rdev;
D 2
		if (fs->fs_quotafile == 0 || *fs->fs_quotafile == '\0')
E 2
I 2
		sprintf(qfilename, "%s/%s", fs->fs_file, qfname);
		if (stat(qfilename, &statb) < 0 || statb.st_dev != fsdev)
E 2
			continue;
D 2
		sprintf(qfname, "%s/%s", fs->fs_file, fs->fs_quotafile);
		if (stat(qfname, &statb) < 0 || statb.st_dev != fsdev)
			continue;
E 2
		if (quota(Q_GETDLIM, uid, fsdev, &dqblk) != 0) {
D 2
			register fd = open(qfname, FRDONLY);
E 2
I 2
D 3
			register fd = open(qfilename, FRDONLY);
E 3
I 3
D 6
			register fd = open(qfilename, O_RDONLY);
E 3
E 2

E 6
I 6
	    		if (errno == EINVAL && !warned) {
				warned++;
				fprintf(stderr, "Warning: %s\n",
				    "Quotas are not compiled into this kernel");
				sleep(3);
			}
			fd = open(qfilename, O_RDONLY);
E 6
			if (fd < 0)
				continue;
D 3
			lseek(fd, (long)(uid * sizeof dqblk), FSEEK_ABSOLUTE);
E 3
I 3
			lseek(fd, (long)(uid * sizeof dqblk), L_SET);
E 3
D 8
			if (read(fd, &dqblk, sizeof dqblk) != sizeof (dqblk)) {
E 8
I 8
			switch (read(fd, &dqblk, sizeof dqblk)) {
			case 0:			/* EOF */
				/*
				 * Convert implicit 0 quota (EOF)
				 * into an explicit one (zero'ed dqblk)
				 */
				bzero((caddr_t)&dqblk, sizeof dqblk);
				break;

			case sizeof dqblk:	/* OK */
				break;

			default:		/* ERROR */
				fprintf(stderr, "edquota: read error in ");
				perror(qfilename);
E 8
				close(fd);
				continue;
			}
			close(fd);
D 2
#ifdef notdef
			if (dqblk.dqb_isoftlimit == 0 && dqblk.dqb_bsoftlimit == 0)
				continue;
#endif
E 2
		}
		dq->dq_dqb = dqblk;
		dq->dq_dev = fsdev;
		strcpy(*dqf, fs->fs_file);
		dq++, dqf++;
E 17
I 17
	if (!initname) {
		sprintf(usrname, "%s%s", qfextension[USRQUOTA], qfname);
		sprintf(grpname, "%s%s", qfextension[GRPQUOTA], qfname);
		initname = 1;
E 17
	}
D 17
	endfsent();
	**dqf = '\0';
}

putdiscq(uid, dq, dqf)
	register uid;
	register struct dquot *dq;
	register char (*dqf)[MAXPATHLEN + 1];
{
	register fd, cnt;
	struct stat sb;
	struct fstab *fs;

	cnt = 0;
	for (cnt = 0; ++cnt <= NMOUNT && **dqf; dq++, dqf++) {
		fs = getfsfile(*dqf);
D 2
		if (fs == NULL)
			goto nofile;
		strcat(*dqf, fs->fs_quotafile);
		if (stat(*dqf, &sb) >= 0 && (fd = open(*dqf, 1)) >= 0) {
E 2
I 2
		if (fs == NULL) {
D 15
			fprintf(stderr, "%s: not in /etc/fstab\n", *dqf);
E 15
I 15
			fprintf(stderr, "%s: not in fstab\n", *dqf);
E 15
			continue;
		}
		strcat(*dqf, "/");
		strcat(*dqf, qfname);
		if (stat(*dqf, &sb) >= 0)
			quota(Q_SETDLIM, uid, sb.st_dev, &dq->dq_dqb);
		if ((fd = open(*dqf, 1)) < 0) {
			perror(*dqf);
		} else {
E 2
			lseek(fd, (long)uid * (long)sizeof (struct dqblk), 0);
			if (write(fd, &dq->dq_dqb, sizeof (struct dqblk)) !=
			    sizeof (struct dqblk)) {
				fprintf(stderr, "edquota: ");
				perror(*dqf);
			}
			close(fd);
		}
E 17
I 17
D 18
	strcpy(buf, options);
E 18
I 18
	strcpy(buf, fs->fs_mntops);
E 18
	for (opt = strtok(buf, ","); opt; opt = strtok(NULL, ",")) {
I 18
		if (cp = index(opt, '='))
			*cp++ = '\0';
E 18
		if (type == USRQUOTA && strcmp(opt, usrname) == 0)
D 18
			return(1);
E 18
I 18
			break;
E 18
		if (type == GRPQUOTA && strcmp(opt, grpname) == 0)
D 18
			return(1);
E 18
I 18
			break;
E 18
E 17
D 2
nofile:
		quota(Q_SETDLIM, uid, sb.st_dev, &dq->dq_dqb);
E 2
	}
I 17
D 18
	return (0);
E 18
I 18
	if (!opt)
		return (0);
	if (cp) {
		*qfnamep = cp;
		return (1);
	}
	(void) sprintf(buf, "%s/%s.%s", fs->fs_file, qfname, qfextension[type]);
	*qfnamep = buf;
	return (1);
E 18
E 17
}
E 1
