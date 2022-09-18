h04400
s 00005/00005/00220
d D 8.1 93/06/06 14:05:05 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00224
d D 5.13 91/11/11 11:50:26 bostic 17 16
c break UFS up into FFS/UFS/LFS/MFS
e
s 00003/00000/00222
d D 5.12 90/09/27 14:02:12 mckusick 16 15
c have to initialize quota variables here rather than in quota.h
e
s 00001/00011/00221
d D 5.11 90/06/01 18:54:18 bostic 15 14
c new copyright notice
e
s 00043/00029/00189
d D 5.10 90/05/06 15:37:13 mckusick 14 13
c allow fstab to override the defualt quota file name
e
s 00001/00001/00217
d D 5.9 90/05/05 19:28:36 mckusick 13 12
c missing (but critical) parenthesis
e
s 00001/00001/00217
d D 5.8 90/05/04 23:15:30 mckusick 12 11
c mount flags change from M_ to MNT_
e
s 00107/00045/00111
d D 5.7 90/05/04 23:14:06 mckusick 11 10
c first cut at new quotas
e
s 00012/00068/00144
d D 5.6 90/01/02 14:20:23 mckusick 10 9
c get rid of use of mtab.h
e
s 00005/00004/00207
d D 5.5 89/05/11 14:31:32 bostic 9 8
c file reorg, pathnames.h, paths.h
e
s 00010/00005/00201
d D 5.4 88/06/18 14:34:43 bostic 8 7
c install approved copyright notice
e
s 00010/00004/00196
d D 5.3 88/05/20 12:15:30 bostic 7 6
c add Berkeley specific header
e
s 00001/00001/00199
d D 5.2 85/08/08 17:20:15 mckusick 6 5
c be more persistent in looking for mount entry
e
s 00014/00002/00186
d D 5.1 85/05/30 19:55:23 mckusick 5 4
c Add copyright
e
s 00109/00024/00079
d D 4.4 83/05/28 14:20:23 sam 4 3
c reflect status in mtab
e
s 00014/00006/00089
d D 4.3 83/05/25 16:05:57 mckusick 3 2
c allow fs names or special devices as arguments
e
s 00043/00024/00052
d D 4.2 83/05/22 18:20:42 mckusick 2 1
c break out into "quotaon" and "quotaoff" (still same binary)
e
s 00076/00000/00000
d D 4.1 83/05/22 16:20:50 mckusick 1 0
c date and time created 83/05/22 16:20:50 by mckusick
e
u
U
t
T
I 5
/*
D 11
 * Copyright (c) 1980 Regents of the University of California.
E 11
I 11
D 18
 * Copyright (c) 1980, 1990 Regents of the University of California.
E 11
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1980, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
I 11
 * This code is derived from software contributed to Berkeley by
 * Robert Elz at The University of Melbourne.
 *
E 11
D 15
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 8
E 7
 */

E 5
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (Melbourne) %G%";
E 2
I 2
D 5
static char sccsid[] = "%W% (Berkeley, Melbourne) %G%";
E 2
#endif
E 5
I 5
D 18
char copyright[] =
D 11
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 11
I 11
"%Z% Copyright (c) 1980, 1990 Regents of the University of California.\n\
E 11
 All rights reserved.\n";
E 18
I 18
static char copyright[] =
"%Z% Copyright (c) 1980, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 18
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 5
I 4

E 4
/*
D 2
 * Turn quota on/off for a filesystem
E 2
I 2
 * Turn quota on/off for a filesystem.
D 4
 *
 * NEED TO REFLECT CURRENT STATUS IN MTAB.
E 4
E 2
 */
#include <sys/param.h>
I 4
#include <sys/file.h>
I 10
#include <sys/mount.h>
I 11
D 17
#include <ufs/quota.h>
E 17
I 17
#include <ufs/ufs/quota.h>
E 17
E 11
E 10
E 4
D 2

E 2
#include <stdio.h>
#include <fstab.h>
I 4
D 10
#include <mtab.h>
I 9
#include "pathnames.h"
E 10
E 9
E 4

I 16
char *qfname = QUOTAFILENAME;
char *qfextension[] = INITQFNAMES;

E 16
I 4
D 10
struct	mtab mtab[NMOUNT];

E 10
E 4
D 11
int	vflag;		/* verbose */
E 11
int	aflag;		/* all file systems */
I 3
D 11
int	done;
E 11
I 11
int	gflag;		/* operate on group quotas */
int	uflag;		/* operate on user quotas */
int	vflag;		/* verbose */
E 11
I 4
D 10
int	mf;
E 10
E 4
E 3

I 2
D 4
char *qfname = "quotas";
char quotafile[MAXPATHLEN + 1];
E 4
I 4
D 11
char	*qfname = "quotas";
char	quotafile[MAXPATHLEN + 1];
char	*index(), *rindex();
E 4

E 11
E 2
main(argc, argv)
I 2
	int argc;
E 2
	char **argv;
{
D 2
	register i, on;
E 2
	register struct fstab *fs;
I 2
D 11
	char *whoami, *rindex();
D 3
	int offmode = 0, errs = 0;
E 3
I 3
	int offmode = 0, errs = 0, i;
E 11
I 11
D 14
	char ch, *whoami, *rindex();
E 14
I 14
	char ch, *qfnp, *whoami, *rindex();
E 14
	long argnum, done = 0;
	int i, offmode = 0, errs = 0;
	extern char *optarg;
	extern int optind;
E 11
E 3
E 2

I 2
	whoami = rindex(*argv, '/') + 1;
	if (whoami == (char *)1)
		whoami = *argv;
	if (strcmp(whoami, "quotaoff") == 0)
		offmode++;
	else if (strcmp(whoami, "quotaon") != 0) {
		fprintf(stderr, "Name must be quotaon or quotaoff not %s\n",
			whoami);
		exit(1);
	}
E 2
D 11
again:
	argc--, argv++;
	if (argc > 0 && strcmp(*argv, "-v") == 0) {
		vflag++;
		goto again;
E 11
I 11
	while ((ch = getopt(argc, argv, "avug")) != EOF) {
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
			usage(whoami);
		}
E 11
	}
D 11
	if (argc > 0 && strcmp(*argv, "-a") == 0) {
		aflag++;
		goto again;
E 11
I 11
	argc -= optind;
	argv += optind;
	if (argc <= 0 && !aflag)
		usage(whoami);
	if (!gflag && !uflag) {
		gflag++;
		uflag++;
E 11
	}
D 2
	if (argc <= 0 || strcmp(*argv, "on") && strcmp(*argv, "off")) {
		fprintf(stderr,
			"usage: setquota [-v] [-a] on | off [filesys...]\n");
E 2
I 2
D 11
	if (argc <= 0 && !aflag) {
		fprintf(stderr, "Usage:\n\t%s [-v] -a\n\t%s [-v] filesys ...\n",
			whoami, whoami);
E 2
		exit(1);
	}
E 11
I 4
D 9
	mf = open("/etc/mtab", O_RDONLY);
E 9
I 9
D 10
	mf = open(_PATH_MTAB, O_RDONLY);
E 9
	if (mf < 0) {
D 9
		perror("/etc/mtab");
E 9
I 9
		perror(_PATH_MTAB);
E 9
		exit(1);
	}
	(void) read(mf, (char *)mtab, sizeof (mtab));
	close(mf);
E 10
E 4
D 2
	on = strcmp(*argv, "on") == 0;
	argc--, argv++;
E 2
	setfsent();
	while ((fs = getfsent()) != NULL) {
I 14
		if (strcmp(fs->fs_vfstype, "ufs") ||
		    strcmp(fs->fs_type, FSTAB_RW))
			continue;
E 14
D 2
		if (fs->fs_quotafile == 0 || *fs->fs_quotafile == '\0')
E 2
I 2
D 3
		if (fs->fs_type == 0)
E 3
I 3
D 11
		if (aflag &&
		    (fs->fs_type == 0 || strcmp(fs->fs_type, "rq") != 0))
E 11
I 11
		if (aflag) {
D 14
			if (gflag && hasquota(fs->fs_mntops, GRPQUOTA))
				errs += quotaonoff(fs, offmode, GRPQUOTA);
			if (uflag && hasquota(fs->fs_mntops, USRQUOTA))
				errs += quotaonoff(fs, offmode, USRQUOTA);
E 14
I 14
			if (gflag && hasquota(fs, GRPQUOTA, &qfnp))
				errs += quotaonoff(fs, offmode, GRPQUOTA, qfnp);
			if (uflag && hasquota(fs, USRQUOTA, &qfnp))
				errs += quotaonoff(fs, offmode, USRQUOTA, qfnp);
E 14
E 11
E 3
E 2
			continue;
D 2
		if (fs->fs_type == 0 || strcmp(fs->fs_type, "rw"))
E 2
I 2
D 3
		if (aflag && strcmp(fs->fs_type, "rq") != 0)
E 3
I 3
D 11
		if (!aflag &&
		    !(oneof(fs->fs_file, argv, argc) ||
		      oneof(fs->fs_spec, argv, argc)))
E 3
E 2
			continue;
D 3
		if (!aflag && !oneof(fs->fs_file, argv, argc))
			continue;
E 3
D 2
		if (vflag)
			printf("%s: quotas turned %s\n", fs->fs_file,
				on ? "on" : "off");
		if (on) {
			char quotafile[MAXPATHLEN + 1];

			(void) sprintf(quotafile, "%s/%s", fs->fs_file,
			   fs->fs_quotafile);
			i = setquota(fs->fs_spec, quotafile);
		} else
			i = setquota(fs->fs_spec, NULL);
		if (i < 0) {
E 2
I 2
D 4
		if (offmode) {
			if (setquota(fs->fs_spec, NULL) < 0) {
				fprintf(stderr, "setquota: ");
				perror(fs->fs_spec);
				errs++;
				continue;
			}
			if (vflag)
				printf("%s: quotas turned off\n", fs->fs_file);
			continue;
		}
		(void) sprintf(quotafile, "%s/%s", fs->fs_file, qfname);
		if (setquota(fs->fs_spec, quotafile) < 0) {
E 2
			fprintf(stderr, "setquota: ");
			perror(fs->fs_spec);
I 2
			errs++;
			continue;
E 2
		}
I 2
		if (vflag)
			printf("%s: quotas turned on\n", fs->fs_file);
E 4
I 4
		errs += quotaonoff(fs, offmode);
E 11
I 11
		}
D 13
		if ((argnum = oneof(fs->fs_file, argv, argc) >= 0) ||
E 13
I 13
		if ((argnum = oneof(fs->fs_file, argv, argc)) >= 0 ||
E 13
		    (argnum = oneof(fs->fs_spec, argv, argc)) >= 0) {
			done |= 1 << argnum;
D 14
			if (gflag && hasquota(fs->fs_mntops, GRPQUOTA))
				errs += quotaonoff(fs, offmode, GRPQUOTA);
			if (uflag && hasquota(fs->fs_mntops, USRQUOTA))
				errs += quotaonoff(fs, offmode, USRQUOTA);
E 14
I 14
			if (gflag && hasquota(fs, GRPQUOTA, &qfnp))
				errs += quotaonoff(fs, offmode, GRPQUOTA, qfnp);
			if (uflag && hasquota(fs, USRQUOTA, &qfnp))
				errs += quotaonoff(fs, offmode, USRQUOTA, qfnp);
E 14
		}
E 11
E 4
E 2
	}
	endfsent();
I 3
	for (i = 0; i < argc; i++)
		if ((done & (1 << i)) == 0)
D 9
			fprintf(stderr, "%s not found in /etc/fstab\n",
E 9
I 9
			fprintf(stderr, "%s not found in fstab\n",
E 9
				argv[i]);
E 3
D 2
	exit(i < 0);
E 2
I 2
	exit(errs);
E 2
}

I 4
D 11
quotaonoff(fs, offmode)
E 11
I 11
usage(whoami)
	char *whoami;
{

	fprintf(stderr, "Usage:\n\t%s [-g] [-u] [-v] -a\n", whoami);
	fprintf(stderr, "\t%s [-g] [-u] [-v] filesys ...\n", whoami);
	exit(1);
}

D 14
quotaonoff(fs, offmode, type)
E 14
I 14
quotaonoff(fs, offmode, type, qfpathname)
E 14
E 11
	register struct fstab *fs;
D 11
	int offmode;
E 11
I 11
	int offmode, type;
I 14
	char *qfpathname;
E 14
E 11
{
I 11
D 14
	char	quotafile[MAXPATHLEN + 1];
E 14
E 11

	if (strcmp(fs->fs_file, "/") && readonly(fs))
		return (1);
	if (offmode) {
D 11
		if (setquota(fs->fs_spec, NULL) < 0)
E 11
I 11
D 14
		if (quotactl(fs->fs_file, QCMD(Q_QUOTAOFF, type), 0, 0) < 0)
E 11
			goto bad;
E 14
I 14
		if (quotactl(fs->fs_file, QCMD(Q_QUOTAOFF, type), 0, 0) < 0) {
			fprintf(stderr, "quotaoff: ");
			perror(fs->fs_file);
			return (1);
		}
E 14
		if (vflag)
			printf("%s: quotas turned off\n", fs->fs_file);
D 10
		changemtab(fs, FSTAB_RW);
E 10
		return (0);
	}
D 11
	(void) sprintf(quotafile, "%s/%s", fs->fs_file, qfname);
	if (setquota(fs->fs_spec, quotafile) < 0)
E 11
I 11
D 14
	(void) sprintf(quotafile, "%s/%s.%s", fs->fs_file, qfname,
	    qfextension[type]);
	if (quotactl(fs->fs_file, QCMD(Q_QUOTAON, type), 0, quotafile) < 0)
E 11
		goto bad;
E 14
I 14
	if (quotactl(fs->fs_file, QCMD(Q_QUOTAON, type), 0, qfpathname) < 0) {
		fprintf(stderr, "quotaon: using %s on", qfpathname);
		perror(fs->fs_file);
		return (1);
	}
E 14
	if (vflag)
D 11
		printf("%s: quotas turned on\n", fs->fs_file);
E 11
I 11
		printf("%s: %s quotas turned on\n", fs->fs_file,
		    qfextension[type]);
E 11
D 10
	changemtab(fs, FSTAB_RQ);
E 10
	return (0);
D 14
bad:
	fprintf(stderr, "setquota: ");
D 11
	perror(fs->fs_spec);
E 11
I 11
	perror(fs->fs_file);
E 11
	return (1);
E 14
}

E 4
D 11
oneof(target, list, n)
	char *target, *list[];
	register int n;
E 11
I 11
/*
 * Check to see if target appears in list of size cnt.
 */
oneof(target, list, cnt)
	register char *target, *list[];
	int cnt;
E 11
{
	register int i;

D 11
	for (i = 0; i < n; i++)
D 3
		if (strcmp(target, list[i]) == 0)
E 3
I 3
		if (strcmp(target, list[i]) == 0) {
			done |= 1 << i;
E 3
			return (1);
I 3
		}
E 11
I 11
	for (i = 0; i < cnt; i++)
		if (strcmp(target, list[i]) == 0)
			return (i);
	return (-1);
}

/*
 * Check to see if a particular quota is to be enabled.
 */
D 14
hasquota(options, type)
	char *options;
E 14
I 14
hasquota(fs, type, qfnamep)
	register struct fstab *fs;
E 14
	int type;
I 14
	char **qfnamep;
E 14
{
	register char *opt;
D 14
	char buf[BUFSIZ];
	char *strtok();
E 14
I 14
	char *cp, *index(), *strtok();
E 14
	static char initname, usrname[100], grpname[100];
I 14
	static char buf[BUFSIZ];
E 14

	if (!initname) {
		sprintf(usrname, "%s%s", qfextension[USRQUOTA], qfname);
		sprintf(grpname, "%s%s", qfextension[GRPQUOTA], qfname);
		initname = 1;
	}
D 14
	strcpy(buf, options);
E 14
I 14
	strcpy(buf, fs->fs_mntops);
E 14
	for (opt = strtok(buf, ","); opt; opt = strtok(NULL, ",")) {
I 14
		if (cp = index(opt, '='))
			*cp++ = '\0';
E 14
		if (type == USRQUOTA && strcmp(opt, usrname) == 0)
D 14
			return(1);
E 14
I 14
			break;
E 14
		if (type == GRPQUOTA && strcmp(opt, grpname) == 0)
D 14
			return(1);
E 14
I 14
			break;
E 14
	}
E 11
E 3
D 14
	return (0);
E 14
I 14
	if (!opt)
		return (0);
	if (cp) {
		*qfnamep = cp;
		return (1);
	}
	(void) sprintf(buf, "%s/%s.%s", fs->fs_file, qfname, qfextension[type]);
	*qfnamep = buf;
	return (1);
E 14
I 4
}

D 10
changemtab(fs, type)
	register struct fstab *fs;
	char *type;
{
	register struct mtab *mp;
	register char *cp;

	cp = index(fs->fs_spec, '\0');
	while (*--cp == '/')
		*cp = '\0';
	cp = rindex(fs->fs_spec, '/');
	if (cp)
		cp++;
	else
		cp = fs->fs_spec;
	for (mp = mtab; mp < &mtab[NMOUNT]; mp++)
		if (strcmp(mp->m_dname, cp) == 0)
			goto replace;
	for (mp = mtab; mp < &mtab[NMOUNT]; mp++)
		if (mp->m_path[0] == '\0')
			goto replace;
	return;
replace:
	strcpy(mp->m_type, type);
	mp = mtab + NMOUNT - 1;
	while (mp > mtab && mp->m_path[0] == '\0')
		--mp;
D 9
	mf = creat("/etc/mtab", 0644);
E 9
I 9
	mf = creat(_PATH_MTAB, 0644);
E 9
	(void) write(mf, (char *)mtab, (mp - mtab + 1) * sizeof (struct mtab));
	close(mf);
}

E 10
/*
 * Verify file system is mounted and not readonly.
 */
readonly(fs)
	register struct fstab *fs;
{
D 10
	register struct mtab *mp;
	register char *cp;
E 10
I 10
	struct statfs fsbuf;
E 10

D 10
	cp = index(fs->fs_spec, '\0');
	while (*--cp == '/')
		*cp = '\0';
	cp = rindex(fs->fs_spec, '/');
	if (cp)
		cp++;
	else
		cp = fs->fs_spec;
	for (mp = mtab; mp < mtab + NMOUNT; mp++) {
		if (mp->m_path[0] == '\0')
D 6
			break;
E 6
I 6
			continue;
E 6
		if (strcmp(cp, mp->m_dname) == 0) {
			if (strcmp(mp->m_type, FSTAB_RO) == 0) {
				printf("%s: mounted read-only\n", fs->fs_file);
				return (1);
			}
			return (0);
		}
E 10
I 10
	if (statfs(fs->fs_file, &fsbuf) < 0 ||
	    strcmp(fsbuf.f_mntonname, fs->fs_file) ||
	    strcmp(fsbuf.f_mntfromname, fs->fs_spec)) {
		printf("%s: not mounted\n", fs->fs_file);
		return (1);
E 10
	}
D 10
	printf("%s: not mounted\n", fs->fs_file);
	return (1);
E 10
I 10
D 12
	if (fsbuf.f_flags & M_RDONLY) {
E 12
I 12
	if (fsbuf.f_flags & MNT_RDONLY) {
E 12
		printf("%s: mounted read-only\n", fs->fs_file);
		return (1);
	}
	return (0);
E 10
E 4
}
E 1
