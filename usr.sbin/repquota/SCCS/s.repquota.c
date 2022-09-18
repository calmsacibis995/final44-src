h45306
s 00001/00000/00353
d D 8.2 94/11/22 16:53:04 mckusick 18 17
c needs queue.h
e
s 00005/00005/00348
d D 8.1 93/06/06 14:05:13 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00352
d D 5.12 91/11/11 11:50:43 bostic 16 15
c break UFS up into FFS/UFS/LFS/MFS
e
s 00003/00000/00350
d D 5.11 90/09/27 14:04:40 mckusick 15 14
c have to initialize quota variables here rather than in quota.h
e
s 00001/00011/00349
d D 5.10 90/06/01 18:54:35 bostic 14 13
c new copyright notice
e
s 00037/00025/00323
d D 5.9 90/05/06 15:19:31 mckusick 13 12
c allow fstab to override default quota file location
e
s 00217/00110/00131
d D 5.8 90/05/05 19:29:20 mckusick 12 11
c first cut at new quotas
e
s 00003/00003/00238
d D 5.7 89/07/30 11:11:57 bostic 11 10
c vnodes
e
s 00010/00005/00231
d D 5.6 88/06/18 14:34:46 bostic 10 9
c install approved copyright notice
e
s 00010/00004/00226
d D 5.5 88/05/20 12:15:54 bostic 9 8
c add Berkeley specific header
e
s 00001/00002/00229
d D 5.4 86/03/05 20:16:47 mckusick 8 7
c do not print uid's with no blocks or files allocated
e
s 00003/00003/00228
d D 5.3 85/11/04 19:04:44 bloom 7 6
c rewrite to avoid division by zero
e
s 00012/00007/00219
d D 5.2 85/09/09 19:25:31 serge 6 5
c report quota for users who have 0 blocks on the file system
e
s 00014/00002/00212
d D 5.1 85/05/30 19:55:48 mckusick 5 4
c Add copyright
e
s 00009/00001/00205
d D 4.4 85/05/24 17:02:24 mckusick 4 3
c in verbose mode, warn of kernels not compiled for quotas
e
s 00003/00002/00203
d D 4.3 85/03/22 17:05:20 lepreau 3 2
c Use 1st, not last, passwd file entry for those with multiple entries per uid
e
s 00173/00076/00032
d D 4.2 83/05/27 15:14:06 mckusick 2 1
c Berkeleyize
e
s 00108/00000/00000
d D 4.1 83/05/25 15:03:54 mckusick 1 0
c date and time created 83/05/25 15:03:54 by mckusick
e
u
U
t
T
I 5
/*
D 13
 * Copyright (c) 1980 Regents of the University of California.
E 13
I 13
D 17
 * Copyright (c) 1980, 1990 Regents of the University of California.
E 13
D 9
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1980, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
I 12
 * This code is derived from software contributed to Berkeley by
 * Robert Elz at The University of Melbourne.
 *
E 12
D 14
 * Redistribution and use in source and binary forms are permitted
D 10
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 10
I 10
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 10
E 9
 */

E 5
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (Melbourne) %G%";
E 2
I 2
D 5
static char sccsid[] = "%W% (Berkeley, from Melbourne) %G%";
E 2
#endif
E 5
I 5
D 17
char copyright[] =
D 13
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 13
I 13
"%Z% Copyright (c) 1980, 1990 Regents of the University of California.\n\
E 13
 All rights reserved.\n";
E 17
I 17
static char copyright[] =
"%Z% Copyright (c) 1980, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 17
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9
E 5

/*
 * Quota report
 */
D 11
#include <stdio.h>
I 4
#include <errno.h>
E 11
E 4
D 2
#include <ctype.h>
#include <pwd.h>
E 2
#include <sys/param.h>
D 2
#define	QUOTA
E 2
D 11
#include <sys/quota.h>
E 11
I 2
#include <sys/stat.h>
I 18
#include <sys/queue.h>
E 18
I 11
D 16
#include <ufs/quota.h>
E 16
I 16
#include <ufs/ufs/quota.h>
E 16
E 11
#include <fstab.h>
#include <pwd.h>
I 12
#include <grp.h>
E 12
I 11
#include <stdio.h>
#include <errno.h>
E 11
E 2

I 15
char *qfname = QUOTAFILENAME;
char *qfextension[] = INITQFNAMES;

E 15
D 2
#define	NUID	3000
E 2
I 2
D 12
#define LOGINNAMESIZE 8
E 12
struct fileusage {
D 12
	struct fileusage *fu_next;
	struct dqblk fu_dqblk;
	u_short	fu_uid;
	char fu_name[LOGINNAMESIZE + 1];
E 12
I 12
	struct	fileusage *fu_next;
	struct	dqblk fu_dqblk;
	u_long	fu_id;
	char	fu_name[1];
	/* actually bigger */
E 12
};
D 12
#define FUHASH 997
struct fileusage *fuhead[FUHASH];
E 12
I 12
#define FUHASH 1024	/* must be power of two */
struct fileusage *fuhead[MAXQUOTAS][FUHASH];
E 12
struct fileusage *lookup();
D 12
struct fileusage *adduid();
int highuid;
E 12
I 12
struct fileusage *addid();
u_long highid[MAXQUOTAS];	/* highest addid()'ed identifier per type */
E 12
E 2

D 2
struct dqblk dq[NUID];
E 2
I 2
D 12
long done;
struct	passwd	*getpwent();
E 12
I 12
int	vflag;			/* verbose */
int	aflag;			/* all file systems */
E 12
E 2

D 2
char	*dn[NUID];
int	nuids;
E 2
I 2
D 12
int	vflag;		/* verbose */
int	aflag;		/* all file systems */
E 2

I 2
char *qfname = "quotas";
D 6
char quotafile[MAXPATHLEN + 1];
E 6
struct dqblk zerodqblk;

E 12
E 2
main(argc, argv)
I 2
	int argc;
E 2
	char **argv;
{
D 2
	register struct passwd *lp;
	register n;
	register i;
	register FILE *qf;
	char *copy();
	struct passwd *getpwent();
E 2
I 2
	register struct fstab *fs;
	register struct passwd *pw;
D 12
	register struct fileusage *fup;
	char quotafile[MAXPATHLEN];
	int i, errs = 0;
E 12
I 12
	register struct group *gr;
	int gflag = 0, uflag = 0, errs = 0;
	long i, argnum, done = 0;
	extern char *optarg;
	extern int optind;
D 13
	char ch;
E 13
I 13
	char ch, *qfnp;
E 13
E 12
E 2

D 2
	argc--;
	if ((qf = fopen(*++argv, "r")) == NULL) {
		fprintf(stderr, "Can't open %s\n", *argv);
E 2
I 2
D 12
again:
	argc--, argv++;
	if (argc > 0 && strcmp(*argv, "-v") == 0) {
		vflag++;
		goto again;
E 12
I 12
	while ((ch = getopt(argc, argv, "aguv")) != EOF) {
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
		default:
			usage();
		}
E 12
	}
D 12
	if (argc > 0 && strcmp(*argv, "-a") == 0) {
		aflag++;
		goto again;
E 12
I 12
	argc -= optind;
	argv += optind;
	if (argc == 0 && !aflag)
		usage();
	if (!gflag && !uflag) {
		if (aflag)
			gflag++;
		uflag++;
E 12
	}
D 12
	if (argc <= 0 && !aflag) {
		fprintf(stderr, "Usage:\n\t%s\n\t%s\n",
			"repquota [-v] -a",
			"repquota [-v] filesys ...");
E 2
		exit(1);
E 12
I 12
	if (gflag) {
		setgrent();
		while ((gr = getgrent()) != 0)
			(void) addid((u_long)gr->gr_gid, GRPQUOTA, gr->gr_name);
		endgrent();
E 12
	}
D 2
	argc--, argv++;
	nuids = fread(dq, sizeof(struct dqblk), NUID, qf);
	fclose(qf);
	while ((lp = getpwent()) != (struct passwd *)0) {
		n = lp->pw_uid;
		if (n >= NUID)
E 2
I 2
D 12
	setpwent();
	while ((pw = getpwent()) != 0) {
		fup = lookup(pw->pw_uid);
D 3
		if (fup == 0)
E 3
I 3
		if (fup == 0) {
E 3
			fup = adduid(pw->pw_uid);
D 3
		strncpy(fup->fu_name, pw->pw_name, sizeof(fup->fu_name));
E 3
I 3
			strncpy(fup->fu_name, pw->pw_name, sizeof(fup->fu_name));
		}
E 12
I 12
	if (uflag) {
		setpwent();
		while ((pw = getpwent()) != 0)
			(void) addid((u_long)pw->pw_uid, USRQUOTA, pw->pw_name);
		endpwent();
E 12
E 3
	}
D 12
	endpwent();
E 12
	setfsent();
	while ((fs = getfsent()) != NULL) {
I 13
		if (strcmp(fs->fs_vfstype, "ufs"))
			continue;
E 13
D 12
		if (aflag &&
		    (fs->fs_type == 0 || strcmp(fs->fs_type, "rq") != 0))
E 12
I 12
		if (aflag) {
D 13
			if (gflag && hasquota(fs->fs_mntops, GRPQUOTA))
				errs += repquota(fs, GRPQUOTA);
			if (uflag && hasquota(fs->fs_mntops, USRQUOTA))
				errs += repquota(fs, USRQUOTA);
E 13
I 13
			if (gflag && hasquota(fs, GRPQUOTA, &qfnp))
				errs += repquota(fs, GRPQUOTA, qfnp);
			if (uflag && hasquota(fs, USRQUOTA, &qfnp))
				errs += repquota(fs, USRQUOTA, qfnp);
E 13
E 12
E 2
			continue;
D 2
		if (dn[n])
E 2
I 2
D 12
		if (!aflag &&
		    !(oneof(fs->fs_file, argv, argc) ||
		      oneof(fs->fs_spec, argv, argc)))
E 2
			continue;
D 2
		dn[n] = copy(lp->pw_name);
E 2
I 2
		(void) sprintf(quotafile, "%s/%s", fs->fs_file, qfname);
D 6
		errs += repquota(fs->fs_spec, quotafile);
E 6
I 6
		errs += repquota(fs->fs_spec, fs->fs_file, quotafile);
E 12
I 12
		}
		if ((argnum = oneof(fs->fs_file, argv, argc)) >= 0 ||
		    (argnum = oneof(fs->fs_spec, argv, argc)) >= 0) {
			done |= 1 << argnum;
D 13
			if (gflag && hasquota(fs->fs_mntops, GRPQUOTA))
				errs += repquota(fs, GRPQUOTA);
			if (uflag && hasquota(fs->fs_mntops, USRQUOTA))
				errs += repquota(fs, USRQUOTA);
E 13
I 13
			if (gflag && hasquota(fs, GRPQUOTA, &qfnp))
				errs += repquota(fs, GRPQUOTA, qfnp);
			if (uflag && hasquota(fs, USRQUOTA, &qfnp))
				errs += repquota(fs, USRQUOTA, qfnp);
E 13
		}
E 12
E 6
E 2
	}
I 2
	endfsent();
	for (i = 0; i < argc; i++)
		if ((done & (1 << i)) == 0)
D 12
			fprintf(stderr, "%s not found in /etc/fstab\n",
				argv[i]);
E 12
I 12
			fprintf(stderr, "%s not found in fstab\n", argv[i]);
E 12
	exit(errs);
}
E 2

D 2
	for (n = 0; n < nuids; n++) {
		if (argc > 0) {
			for (i = 0; i < argc; i++) {
				register char *p;
E 2
I 2
D 6
repquota(fsdev, qffile)
E 6
I 6
D 12
repquota(fsdev, fsfile, qffile)
E 6
	char *fsdev;
I 6
	char *fsfile;
E 6
	char *qffile;
E 12
I 12
usage()
E 12
{
I 12
	fprintf(stderr, "Usage:\n\t%s\n\t%s\n",
		"repquota [-v] [-g] [-u] -a",
		"repquota [-v] [-g] [-u] filesys ...");
	exit(1);
}

D 13
repquota(fs, type)
E 13
I 13
repquota(fs, type, qfpathname)
E 13
	register struct fstab *fs;
	int type;
I 13
	char *qfpathname;
E 13
{
E 12
	register struct fileusage *fup;
	FILE *qf;
D 12
	u_short uid;
E 12
I 12
	u_long id;
E 12
	struct dqblk dqbuf;
D 12
	struct stat statb;
E 12
I 12
D 13
	char *timeprt(), quotafile[MAXPATHLEN + 1];
E 13
I 13
	char *timeprt();
E 13
	static struct dqblk zerodqblk;
E 12
I 4
	static int warned = 0;
I 12
	static int multiple = 0;
E 12
	extern int errno;
E 4
E 2

D 2
				for (p = argv[i]; *p && isdigit(*p); p++)
					;
				if (*p)
					continue;
				if (n == atoi(argv[i]))
					goto rep;
			}
			if (!dn[n])
				continue;
			for (i = 0; i < argc; i++)
				if (strcmp(argv[i], dn[n]) == 0)
					break;
			if (i >= argc)
				continue;
		} else if (dq[n].dqb_curinodes == 0 && dq[n].dqb_curblocks == 0)
E 2
I 2
D 12
	if (vflag)
D 6
		fprintf(stdout, "*** Quota report for %s\n", fsdev);
E 6
I 6
		fprintf(stdout, "*** Quota report for %s (%s)\n", fsdev, fsfile);
E 6
	qf = fopen(qffile, "r");
	if (qf == NULL) {
		perror(qffile);
		return (1);
	}
	if (fstat(fileno(qf), &statb) < 0) {
		perror(qffile);
I 6
		fclose(qf);
E 6
		return (1);
	}
D 4
	quota(Q_SYNC, 0, statb.st_dev, 0);
E 4
I 4
	if (quota(Q_SYNC, 0, statb.st_dev, 0) < 0 &&
	    errno == EINVAL && !warned && vflag) {
E 12
I 12
	if (quotactl(fs->fs_file, QCMD(Q_SYNC, type), 0, 0) < 0 &&
	    errno == EOPNOTSUPP && !warned && vflag) {
E 12
		warned++;
		fprintf(stdout,
		    "*** Warning: Quotas are not compiled into this kernel\n");
	}
E 4
D 12
	for (uid = 0; ; uid++) {
E 12
I 12
	if (multiple++)
		printf("\n");
	if (vflag)
		fprintf(stdout, "*** Report for %s quotas on %s (%s)\n",
		    qfextension[type], fs->fs_file, fs->fs_spec);
D 13
	(void) sprintf(quotafile, "%s/%s.%s", fs->fs_file, qfname,
	    qfextension[type]);
	if ((qf = fopen(quotafile, "r")) == NULL) {
		perror(quotafile);
E 13
I 13
	if ((qf = fopen(qfpathname, "r")) == NULL) {
		perror(qfpathname);
E 13
		return (1);
	}
	for (id = 0; ; id++) {
E 12
		fread(&dqbuf, sizeof(struct dqblk), 1, qf);
		if (feof(qf))
			break;
D 6
		if (dqbuf.dqb_curinodes == 0 && dqbuf.dqb_curblocks == 0)
E 2
			continue;
E 6
D 2
	rep:
		if (dn[n])
			printf("%-10s", dn[n]);
E 2
I 2
D 12
		fup = lookup(uid);
I 6
		if ((fup == 0 || fup->fu_name[0] == 0) &&
		    dqbuf.dqb_curinodes == 0 && dqbuf.dqb_curblocks == 0)
E 12
I 12
		if (dqbuf.dqb_curinodes == 0 && dqbuf.dqb_curblocks == 0)
E 12
			continue;
E 6
D 12
		if (fup == 0)
			fup = adduid(uid);
E 12
I 12
		if ((fup = lookup(id, type)) == 0)
			fup = addid(id, type, (char *)0);
E 12
		fup->fu_dqblk = dqbuf;
	}
I 12
	fclose(qf);
E 12
	printf("                        Block limits               File limits\n");
D 12
	printf("User            used    soft    hard  warn    used  soft  hard  warn\n");
	for (uid = 0; uid <= highuid; uid++) {
		fup = lookup(uid);
E 12
I 12
	printf("User            used    soft    hard  grace    used  soft  hard  grace\n");
	for (id = 0; id <= highid[type]; id++) {
		fup = lookup(id, type);
E 12
		if (fup == 0)
			continue;
D 6
		if (fup->fu_dqblk.dqb_curinodes == 0 &&
E 6
I 6
D 8
		if ((fup == 0 || fup->fu_name[0] == 0) &&
		    fup->fu_dqblk.dqb_curinodes == 0 &&
E 8
I 8
		if (fup->fu_dqblk.dqb_curinodes == 0 &&
E 8
E 6
		    fup->fu_dqblk.dqb_curblocks == 0)
			continue;
D 12
		if (fup->fu_name[0] != '\0')
			printf("%-10s", fup->fu_name);
E 2
		else
D 2
			printf("#%-9d", n);

		printf("%c%c %5d %5d %5d %5d %5d %5d %5d %5d\n"
			, dq[n].dqb_bsoftlimit && dq[n].dqb_curblocks >= dq[n].dqb_bsoftlimit
				? '+' : '-'
			, dq[n].dqb_isoftlimit && dq[n].dqb_curinodes >= dq[n].dqb_isoftlimit
				? '+' : '-'
			, dq[n].dqb_curblocks
			, dq[n].dqb_bsoftlimit
			, dq[n].dqb_bhardlimit
			, dq[n].dqb_bwarn
			, dq[n].dqb_curinodes
			, dq[n].dqb_isoftlimit
			, dq[n].dqb_ihardlimit
			, dq[n].dqb_iwarn
		);
E 2
I 2
			printf("#%-9d", uid);
		printf("%c%c%8d%8d%8d %5d   %5d %5d %5d %5d\n",
E 12
I 12
		printf("%-10s", fup->fu_name);
		printf("%c%c%8d%8d%8d%7s",
E 12
			fup->fu_dqblk.dqb_bsoftlimit && 
			    fup->fu_dqblk.dqb_curblocks >= 
			    fup->fu_dqblk.dqb_bsoftlimit ? '+' : '-',
			fup->fu_dqblk.dqb_isoftlimit &&
			    fup->fu_dqblk.dqb_curinodes >=
			    fup->fu_dqblk.dqb_isoftlimit ? '+' : '-',
D 7
			fup->fu_dqblk.dqb_curblocks / btodb(1024),
			fup->fu_dqblk.dqb_bsoftlimit / btodb(1024),
			fup->fu_dqblk.dqb_bhardlimit / btodb(1024),
E 7
I 7
			dbtob(fup->fu_dqblk.dqb_curblocks) / 1024,
			dbtob(fup->fu_dqblk.dqb_bsoftlimit) / 1024,
			dbtob(fup->fu_dqblk.dqb_bhardlimit) / 1024,
E 7
D 12
			fup->fu_dqblk.dqb_bwarn,
E 12
I 12
			fup->fu_dqblk.dqb_bsoftlimit && 
			    fup->fu_dqblk.dqb_curblocks >= 
			    fup->fu_dqblk.dqb_bsoftlimit ?
			    timeprt(fup->fu_dqblk.dqb_btime) : "");
		printf("  %6d%6d%6d%7s\n",
E 12
			fup->fu_dqblk.dqb_curinodes,
			fup->fu_dqblk.dqb_isoftlimit,
			fup->fu_dqblk.dqb_ihardlimit,
D 12
			fup->fu_dqblk.dqb_iwarn);
E 12
I 12
			fup->fu_dqblk.dqb_isoftlimit &&
			    fup->fu_dqblk.dqb_curinodes >=
			    fup->fu_dqblk.dqb_isoftlimit ?
			    timeprt(fup->fu_dqblk.dqb_itime) : "");
E 12
		fup->fu_dqblk = zerodqblk;
E 2
	}
I 6
D 12
	fclose(qf);
E 12
E 6
D 2
	exit(0);
E 2
I 2
	return (0);
E 2
}

D 2
char *
copy(s)
	char *s;
E 2
I 2
D 12
oneof(target, list, n)
	char *target, *list[];
	register int n;
E 12
I 12
/*
 * Check to see if target appears in list of size cnt.
 */
oneof(target, list, cnt)
	register char *target, *list[];
	int cnt;
E 12
E 2
{
D 2
	register char *p;
	register n;
	char *malloc();
E 2
I 2
	register int i;
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
D 12
	for (i = 0; i < n; i++)
		if (strcmp(target, list[i]) == 0) {
			done |= 1 << i;
			return (1);
		}
E 12
I 12
	for (i = 0; i < cnt; i++)
		if (strcmp(target, list[i]) == 0)
			return (i);
	return (-1);
}

/*
 * Check to see if a particular quota is to be enabled.
 */
D 13
hasquota(options, type)
	char *options;
E 13
I 13
hasquota(fs, type, qfnamep)
	register struct fstab *fs;
E 13
	int type;
I 13
	char **qfnamep;
E 13
{
	register char *opt;
D 13
	char buf[BUFSIZ];
	char *strtok();
E 13
I 13
	char *cp, *index(), *strtok();
E 13
	static char initname, usrname[100], grpname[100];
I 13
	static char buf[BUFSIZ];
E 13

	if (!initname) {
		sprintf(usrname, "%s%s", qfextension[USRQUOTA], qfname);
		sprintf(grpname, "%s%s", qfextension[GRPQUOTA], qfname);
		initname = 1;
	}
D 13
	strcpy(buf, options);
E 13
I 13
	strcpy(buf, fs->fs_mntops);
E 13
	for (opt = strtok(buf, ","); opt; opt = strtok(NULL, ",")) {
I 13
		if (cp = index(opt, '='))
			*cp++ = '\0';
E 13
		if (type == USRQUOTA && strcmp(opt, usrname) == 0)
D 13
			return(1);
E 13
I 13
			break;
E 13
		if (type == GRPQUOTA && strcmp(opt, grpname) == 0)
D 13
			return(1);
E 13
I 13
			break;
E 13
	}
E 12
D 13
	return (0);
E 13
I 13
	if (!opt)
		return (0);
	if (cp) {
		*qfnamep = cp;
		return (1);
	}
	(void) sprintf(buf, "%s/%s.%s", fs->fs_file, qfname, qfextension[type]);
	*qfnamep = buf;
	return (1);
E 13
}

I 12
/*
 * Routines to manage the file usage table.
 *
 * Lookup an id of a specific type.
 */
E 12
struct fileusage *
D 12
lookup(uid)
	u_short uid;
E 12
I 12
lookup(id, type)
	u_long id;
	int type;
E 12
{
	register struct fileusage *fup;

D 12
	for (fup = fuhead[uid % FUHASH]; fup != 0; fup = fup->fu_next)
		if (fup->fu_uid == uid)
E 12
I 12
	for (fup = fuhead[type][id & (FUHASH-1)]; fup != 0; fup = fup->fu_next)
		if (fup->fu_id == id)
E 12
			return (fup);
	return ((struct fileusage *)0);
}

I 12
/*
 * Add a new file usage id if it does not already exist.
 */
E 12
struct fileusage *
D 12
adduid(uid)
	u_short uid;
E 12
I 12
addid(id, type, name)
	u_long id;
	int type;
	char *name;
E 12
{
	struct fileusage *fup, **fhp;
I 12
	int len;
E 12
I 6
	extern char *calloc();
E 6

D 12
	fup = lookup(uid);
	if (fup != 0)
E 12
I 12
	if (fup = lookup(id, type))
E 12
		return (fup);
D 12
	fup = (struct fileusage *)calloc(1, sizeof(struct fileusage));
	if (fup == 0) {
E 12
I 12
	if (name)
		len = strlen(name);
	else
		len = 10;
	if ((fup = (struct fileusage *)calloc(1, sizeof(*fup) + len)) == NULL) {
E 12
		fprintf(stderr, "out of memory for fileusage structures\n");
		exit(1);
	}
D 12
	fhp = &fuhead[uid % FUHASH];
E 12
I 12
	fhp = &fuhead[type][id & (FUHASH - 1)];
E 12
	fup->fu_next = *fhp;
	*fhp = fup;
D 12
	fup->fu_uid = uid;
	if (uid > highuid)
		highuid = uid;
E 12
I 12
	fup->fu_id = id;
	if (id > highid[type])
		highid[type] = id;
	if (name) {
		bcopy(name, fup->fu_name, len + 1);
	} else {
		sprintf(fup->fu_name, "%u", id);
	}
E 12
	return (fup);
I 12
}

/*
 * Calculate the grace period and return a printable string for it.
 */
char *
timeprt(seconds)
	time_t seconds;
{
	time_t hours, minutes;
	static char buf[20];
	static time_t now;

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
	}
	if (minutes >= 60) {
		sprintf(buf, "%2d:%d", minutes / 60, minutes % 60);
		return (buf);
	}
	sprintf(buf, "%2d", minutes);
	return (buf);
E 12
E 2
}
E 1
