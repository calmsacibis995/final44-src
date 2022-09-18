/*-
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char copyright[] =
"@(#) Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "@(#)quot.c	8.5 (Berkeley) 5/4/95";
#endif /* not lint */

#include <sys/param.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <ufs/ufs/dinode.h>
#include <ufs/ffs/fs.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <paths.h>

#define	ISIZ	(MAXBSIZE/sizeof(struct dinode))
union {
	struct fs u_sblock;
	char dummy[SBSIZE];
} sb_un;
#define sblock sb_un.u_sblock
struct dinode itab[MAXBSIZE/sizeof(struct dinode)];

struct du {
	struct	du *next;
	long	blocks;
	long	blocks30;
	long	blocks60;
	long	blocks90;
	long	nfiles;
	int	uid;
#define	NDU	2048
} du[NDU];
int	ndu;
#define	DUHASH	8209	/* smallest prime >= 4 * NDU */
#define	HASH(u)	((u) % DUHASH)
struct	du *duhash[DUHASH];

#define	TSIZE	500
int	sizes[TSIZE];
long	overflow;

int	nflg;
int	fflg;
int	cflg;
int	vflg;
int	hflg;
struct timeval now;

unsigned	ino;

char	*user_from_uid();

main(argc, argv)
	int argc;
	char *argv[];
{
	extern char *optarg;
	extern int optind;
	int ch;

	while ((ch = getopt(argc, argv, "cfhnv")) != EOF)
		switch((char)ch) {
		case 'c':
			cflg++; break;
		case 'f':
			fflg++; break;
		case 'h':		/* undocumented */
			hflg++; break;
		case 'n':
			nflg++; break;
		case 'v':		/* undocumented */
			vflg++; break;
		case '?':
		default:
			fputs("usage: quot [-cfn] [filesystem ...]\n", stderr);
			exit(1);
		}
	argc -= optind;
	argv += optind;

	(void)gettimeofday(&now, NULL);
	setpassent(1);
	if (argc)
		for (; *argv; ++argv) {
			if (check(*argv, (char *)NULL) == 0)
				report();
		}
	else
		quotall();
	exit(0);
}

#include <sys/dir.h>
#include <fstab.h>

quotall()
{
	register struct fstab *fs;
	register char *cp;
	char dev[MAXNAMLEN + 10], *rindex();

	while (fs = getfsent()) {
		if (strcmp(fs->fs_vfstype, "ufs") ||
		    (strcmp(fs->fs_type, FSTAB_RO) &&
		    strcmp(fs->fs_type, FSTAB_RW) &&
		    strcmp(fs->fs_type, FSTAB_RQ)))
			continue;
		cp = rindex(fs->fs_spec, '/');
		if (cp == 0)
			continue;
		(void)snprintf(dev, sizeof(dev), "%sr%s", _PATH_DEV, cp + 1);
		if (check(dev, fs->fs_file) == 0)
			report();
	}
}

check(file, fsdir)
	char *file;
	char *fsdir;
{
	register int i, j, nfiles;
	register struct du **dp;
	daddr_t iblk;
	long dev_bsize;
	int c, fd;
	struct stat sb;
	struct statfs sfs;
#define FNBSZ	128
	char filebuf[FNBSZ];

	/*
	 * Initialize tables between checks; because of the qsort done in
	 * report() the hash tables must be rebuilt each time.
	 */
	for (i = 0; i < TSIZE; i++)
		sizes[i] = 0;
	overflow = 0;
	for (dp = duhash; dp < &duhash[DUHASH]; dp++)
		*dp = 0;
	ndu = 0;
	/*
	 * Make sure "file" refers to a char special file.
	 * Convert if necessary.  Also make sure we have an fsdir.
	 */
	if (stat(file, &sb) < 0) {
		fprintf(stderr, "quot: ");
		perror(file);
		return (-1);
	}
	/*
	 * User specified "file".
	 * Attempt to come up with the appropriate char special file
	 * and a mount point.
	 */
	if (fsdir == NULL) {
		register struct fstab *fs;
		int len = strlen(_PATH_DEV);

		strcpy(filebuf, _PATH_DEV);
		if (S_ISCHR(sb.st_mode)) {
			if (strncmp(_PATH_DEV, file, len) == 0 &&
			    file[len] == 'r') {
				strncpy(&filebuf[len], &file[len+1], FNBSZ-6);
				fs = getfsspec(filebuf);
				if (fs != NULL)
					fsdir = fs->fs_file;
			}
		} else {
			if (S_ISBLK(sb.st_mode)) {
				fs = getfsspec(file);
				if (fs != NULL)
					fsdir = fs->fs_file;
			} else {
				if (statfs(file, &sfs) == 0) {
					file = sfs.f_mntfromname;
					fsdir = sfs.f_mntonname;
				}
			}
			if (strncmp(_PATH_DEV, file, len) == 0) {
				filebuf[len] = 'r';
				strncpy(&filebuf[len+1], &file[len], FNBSZ-7);
				file = filebuf;
			}
		}
	}
	fd = open(file, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "quot: ");
		perror(file);
		return (-1);
	}
	printf("%s", file);
	if (fsdir == NULL) {
		register struct fstab *fs = getfsspec(file);
		if (fs != NULL)
			fsdir = fs->fs_file;
	}
	if (fsdir != NULL && *fsdir != '\0')
		printf(" (%s)", fsdir);
	printf(":\n");
	sync();
	bread(fd, (off_t)SBOFF, (char *)&sblock, SBSIZE);
	dev_bsize = sblock.fs_fsize / fsbtodb(&sblock, 1);
	if (nflg) {
		if (isdigit(c = getchar()))
			(void)ungetc(c, stdin);
		else while (c != '\n' && c != EOF)
			c = getchar();
	}
	nfiles = sblock.fs_ipg * sblock.fs_ncg;
	for (ino = 0; ino < nfiles; ) {
		iblk = fsbtodb(&sblock, ino_to_fsba(&sblock, ino));
		bread(fd, (off_t)iblk * dev_bsize, itab, (int)sblock.fs_bsize);
		for (j = 0; j < INOPB(&sblock) && ino < nfiles; j++, ino++) {
			if (ino < ROOTINO)
				continue;
			qacct(&itab[j]);
		}
	}
	close(fd);
	return (0);
}

qacct(ip)
	register struct dinode *ip;
{
	register struct du *dp;
	struct du **hp;
	long blks, frags, size;
	int n;
	static fino;

	if ((ip->di_mode & IFMT) == 0)
		return;
	/*
	 * By default, take block count in inode.  Otherwise (-h),
	 * take the size field and estimate the blocks allocated.
	 * The latter does not account for holes in files.
	 */
	if (!hflg)
		size = ip->di_blocks / 2;
	else {
		blks = lblkno(&sblock, ip->di_size);
		frags = blks * sblock.fs_frag +
			numfrags(&sblock, dblksize(&sblock, ip, blks));
		size = frags * sblock.fs_fsize / 1024;
	}
	if (cflg) {
		if ((ip->di_mode&IFMT) != IFDIR && (ip->di_mode&IFMT) != IFREG)
			return;
		if (size >= TSIZE) {
			overflow += size;
			size = TSIZE-1;
		}
		sizes[size]++;
		return;
	}
	hp = &duhash[HASH(ip->di_uid)];
	for (dp = *hp; dp; dp = dp->next)
		if (dp->uid == ip->di_uid)
			break;
	if (dp == 0) {
		if (ndu >= NDU)
			return;
		dp = &du[ndu++];
		dp->next = *hp;
		*hp = dp;
		dp->uid = ip->di_uid;
		dp->nfiles = 0;
		dp->blocks = 0;
		dp->blocks30 = 0;
		dp->blocks60 = 0;
		dp->blocks90 = 0;
	}
	dp->blocks += size;
#define	DAY (60 * 60 * 24)	/* seconds per day */
	if (now.tv_sec - ip->di_atime > 30 * DAY)
		dp->blocks30 += size;
	if (now.tv_sec - ip->di_atime > 60 * DAY)
		dp->blocks60 += size;
	if (now.tv_sec - ip->di_atime > 90 * DAY)
		dp->blocks90 += size;
	dp->nfiles++;
	while (nflg) {
		register char *np;

		if (fino == 0)
			if (scanf("%d", &fino) <= 0)
				return;
		if (fino > ino)
			return;
		if (fino < ino) {
			while ((n = getchar()) != '\n' && n != EOF)
				;
			fino = 0;
			continue;
		}
		if (np = user_from_uid(dp->uid, 1))
			printf("%.7s\t", np);
		else
			printf("%u\t", ip->di_uid);
		while ((n = getchar()) == ' ' || n == '\t')
			;
		putchar(n);
		while (n != EOF && n != '\n') {
			n = getchar();
			putchar(n);
		}
		fino = 0;
		break;
	}
}

bread(fd, bno, buf, cnt)
	int fd, cnt;
	off_t bno;
	void *buf;
{
	(void)lseek(fd, bno, L_SET);
	if (read(fd, buf, cnt) != cnt) {
		fprintf(stderr, "quot: read error at block %ld\n", bno);
		exit(1);
	}
}

qcmp(p1, p2)
	register struct du *p1, *p2;
{
	char *s1, *s2;

	if (p1->blocks > p2->blocks)
		return (-1);
	if (p1->blocks < p2->blocks)
		return (1);
	s1 = user_from_uid(p1->uid, 1);
	if (s1 == 0)
		return (0);
	s2 = user_from_uid(p2->uid, 1);
	if (s2 == 0)
		return (0);
	return (strcmp(s1, s2));
}

report()
{
	register i;
	register struct du *dp;

	if (nflg)
		return;
	if (cflg) {
		register long t = 0;

		for (i = 0; i < TSIZE - 1; i++)
			if (sizes[i]) {
				t += i*sizes[i];
				printf("%d\t%d\t%ld\n", i, sizes[i], t);
			}
		printf("%d\t%d\t%ld\n",
		    TSIZE - 1, sizes[TSIZE - 1], overflow + t);
		return;
	}
	qsort(du, ndu, sizeof (du[0]), qcmp);
	for (dp = du; dp < &du[ndu]; dp++) {
		register char *cp;

		if (dp->blocks == 0)
			return;
		printf("%5D\t", dp->blocks);
		if (fflg)
			printf("%5D\t", dp->nfiles);
		if (cp = user_from_uid(dp->uid, 1))
			printf("%-8.8s", cp);
		else
			printf("#%-8d", dp->uid);
		if (vflg)
			printf("\t%5D\t%5D\t%5D",
			    dp->blocks30, dp->blocks60, dp->blocks90);
		printf("\n");
	}
}
