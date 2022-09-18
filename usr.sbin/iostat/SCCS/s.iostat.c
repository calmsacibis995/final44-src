h18961
s 00001/00001/00364
d D 8.3 95/04/28 17:08:54 bostic 40 39
c add another state, CP_INTR
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00018/00045/00347
d D 8.2 94/01/26 06:53:56 bostic 39 38
c minor cleanups
e
s 00005/00005/00387
d D 8.1 93/06/06 13:57:35 bostic 38 37
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00388
d D 5.17 93/05/28 22:27:36 ralph 37 36
c added mips support
e
s 00019/00018/00369
d D 5.16 93/02/24 17:22:20 bostic 36 35
c rename namelist to nl
e
s 00001/00001/00386
d D 5.15 92/09/02 11:59:21 bostic 35 34
c add luna68k
e
s 00002/00001/00385
d D 5.14 92/07/24 12:46:54 bostic 34 33
c read_names now returns a value so systat can use it
e
s 00024/00019/00362
d D 5.13 92/06/23 10:57:46 mccanne 33 32
c port to new kvm; use stathz instead of phz
e
s 00012/00005/00369
d D 5.12 92/01/27 12:08:49 bostic 32 31
c don't let users create their own symbol table for the running kernel
e
s 00005/00002/00369
d D 5.11 91/11/13 10:59:06 bostic 31 30
c function redeclarations
e
s 00001/00001/00370
d D 5.10 91/11/13 10:56:33 marc 30 29
c fix X_END
e
s 00054/00052/00317
d D 5.9 91/06/27 15:02:30 bostic 29 28
c delete unused variable, cleanup error routine
e
s 00001/00002/00368
d D 5.8 91/04/24 12:13:44 bostic 28 27
c interval is never 0, now
e
s 00009/00001/00361
d D 5.7 91/04/24 11:43:34 bostic 27 26
c make default interval 1, make "iostat -w 3" repeat indefinitely
e
s 00040/00039/00322
d D 5.6 91/04/24 11:02:52 bostic 26 25
c redo man page, source, removing last of AT&T proprietary source
c change bps to sps, change seek calculation to take rotation and implied
c seeks into account.
e
s 00009/00009/00352
d D 5.5 91/04/23 17:07:04 bostic 25 24
c make kvm_read take a void *
e
s 00009/00010/00352
d D 5.4 91/04/23 16:44:59 bostic 24 23
c didn't get usage and flags right, forgot to finish buf overwrite fix
e
s 00113/00176/00249
d D 5.3 91/04/23 16:40:47 bostic 23 22
c share read_names with vmstat(1); use kvm library, ANSI/lint
e
s 00017/00001/00408
d D 5.2 91/04/23 10:55:37 bostic 22 21
c support old syntax of [drives] [interval [count]]
e
s 00185/00150/00224
d D 5.1 91/04/22 17:51:01 bostic 21 20
c ANSI/lint, general cleanup of code and style, getopt the arguments
e
s 00015/00002/00359
d D 4.20 91/04/20 15:45:58 bostic 20 19
c new copyright; att/bsd/shared
e
s 00002/00002/00359
d D 4.19 91/04/11 11:18:22 sklower 19 18
c vax{u,m}ba --> vax/{u,m}ba for inclusion
e
s 00001/00001/00360
d D 4.18 91/01/14 18:02:58 bostic 18 17
c kernel reorg
e
s 00009/00009/00352
d D 4.17 89/05/29 17:45:42 mckusick 17 16
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00010/00009/00351
d D 4.16 89/05/11 14:08:20 bostic 16 15
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00359
d D 4.15 87/01/12 15:32:36 mckusick 15 14
c wrong subscript (from srk@sun.com (Steve Kleiman))
e
s 00039/00003/00321
d D 4.14 86/10/19 23:07:49 sam 14 13
c add tahoe support
e
s 00150/00080/00174
d D 4.13 85/04/25 21:27:13 sam 13 12
c handle lotsa drives as done for vmstat; also print header after continue
e
s 00000/00034/00254
d D 4.12 84/11/26 10:54:55 ralph 12 11
c take out sun code
e
s 00002/00001/00286
d D 4.11 84/11/24 01:01:51 lepreau 11 10
c fix negative times due to overflow; add fflush so works over net
e
s 00010/00004/00277
d D 4.10 83/10/19 20:16:37 sam 10 9
c disk stats are collected off alternate clock, if it exists
e
s 00010/00007/00271
d D 4.9 83/09/25 12:49:39 sam 9 8
c 60 no, hz yes
e
s 00004/00004/00274
d D 4.8 83/05/30 21:14:35 mckusick 8 7
c list "bps" (Kbytes per second) instead of "sps" (seeks per second)
e
s 00047/00011/00231
d D 4.7 83/02/23 19:28:21 shannon 7 6
c fixes for sun
e
s 00002/00001/00240
d D 4.6 81/04/21 01:49:39 root 6 5
c allow for no mba's
e
s 00001/00001/00240
d D 4.5 81/04/01 12:52:28 wnj 5 4
c restore sccsline
e
s 00001/00001/00240
d D 4.4 81/04/01 12:31:49 root 4 3
c aaa
e
s 00065/00003/00176
d D 4.3 81/03/09 20:22:32 toy 3 2
c Made it look up disk device names
e
s 00014/00011/00165
d D 4.2 80/10/19 13:38:33 bill 2 1
c reprint headers
e
s 00176/00000/00000
d D 4.1 80/10/19 13:32:17 bill 1 0
c date and time created 80/10/19 13:32:17 by bill
e
u
U
t
T
I 20
/*-
D 21
 * Copyright (c) 1986 The Regents of the University of California.
E 21
I 21
D 38
 * Copyright (c) 1986, 1991 The Regents of the University of California.
E 21
 * All rights reserved.
E 38
I 38
 * Copyright (c) 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 38
 *
D 26
 * %sccs.include.proprietary.c%
E 26
I 26
 * %sccs.include.redist.c%
E 26
 */

E 20
I 13
#ifndef lint
E 13
I 1
D 4
static	char *sccsid = "%W% (Berkeley) %G%";
E 4
I 4
D 5
static	char *sccsid = "@(#)iostat.c	4.3 (Berkeley) 3/9/81";
E 5
I 5
D 20
static	char *sccsid = "%W% (Berkeley) %E%";
I 13
#endif
E 20
I 20
D 38
char copyright[] =
D 21
"%Z% Copyright (c) 1986 The Regents of the University of California.\n\
E 21
I 21
"%Z% Copyright (c) 1986, 1991 The Regents of the University of California.\n\
E 21
 All rights reserved.\n";
E 38
I 38
static char copyright[] =
"%Z% Copyright (c) 1986, 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 38
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 20

E 13
E 5
E 4
D 21
/*
 * iostat
 */
E 21
I 3
D 16
#include <stdio.h>
I 13
#include <ctype.h>
E 13
E 3
#include <nlist.h>
I 13
#include <signal.h>

E 16
E 13
I 3
D 26
#include <sys/types.h>
E 26
I 26
#include <sys/param.h>
E 26
I 13
D 21
#include <sys/file.h>
E 21
E 13
#include <sys/buf.h>
I 7
D 14
#include <sys/dk.h>
E 14
I 14
#include <sys/dkstat.h>
I 16
D 21
#include <sys/signal.h>
E 21
I 21
D 36
#include <signal.h>
E 36
I 36

I 39
#include <err.h>
E 39
#include <ctype.h>
E 36
#include <fcntl.h>
I 36
#include <kvm.h>
#include <limits.h>
E 36
#include <nlist.h>
D 36
#include <unistd.h>
E 36
I 36
#include <paths.h>
#include <signal.h>
E 36
E 21
#include <stdio.h>
D 36
#include <ctype.h>
E 36
D 21
#include <nlist.h>
E 21
I 21
#include <stdlib.h>
I 23
D 29
#include <stdarg.h>
E 29
E 23
#include <string.h>
E 21
D 36
#include <paths.h>
I 23
#include <kvm.h>
I 33
#include <limits.h>
E 36
I 36
#include <unistd.h>
E 36
E 33
E 23
E 16
E 14
D 13
#ifdef vax
E 7
D 8
#include <sys/ubavar.h>
#include <sys/mbavar.h>
E 8
I 8
#include <vaxuba/ubavar.h>
#include <vaxmba/mbavar.h>
E 8
E 3
D 7
#include <sys/dk.h>
E 7
I 7
#endif
E 13
D 12
#ifdef sun
#include <sundev/mbvar.h>
#endif
E 12
E 7

D 36
struct nlist nl[] = {
E 36
I 36
struct nlist namelist[] = {
E 36
D 23
	{ "_dk_busy" },
E 23
D 29
#define	X_DK_BUSY	0
D 23
	{ "_dk_time" },
E 23
I 23
	{ "_dk_busy" },
E 23
#define	X_DK_TIME	1
E 29
I 29
#define	X_DK_TIME	0
E 29
D 23
	{ "_dk_xfer" },
E 23
I 23
	{ "_dk_time" },
E 23
D 29
#define	X_DK_XFER	2
E 29
I 29
#define	X_DK_XFER	1
E 29
D 23
	{ "_dk_wds" },
E 23
I 23
	{ "_dk_xfer" },
E 23
D 29
#define	X_DK_WDS	3
E 29
I 29
#define	X_DK_WDS	2
E 29
D 23
	{ "_tk_nin" },
E 23
I 23
	{ "_dk_wds" },
E 23
D 29
#define	X_TK_NIN	4
E 29
I 29
#define	X_TK_NIN	3
E 29
D 23
	{ "_tk_nout" },
E 23
I 23
	{ "_tk_nin" },
E 23
D 29
#define	X_TK_NOUT	5
E 29
I 29
#define	X_TK_NOUT	4
E 29
D 23
	{ "_dk_seek" },
E 23
I 23
	{ "_tk_nout" },
E 23
D 29
#define	X_DK_SEEK	6
E 29
I 29
#define	X_DK_SEEK	5
E 29
D 23
	{ "_cp_time" },
E 23
I 23
	{ "_dk_seek" },
E 23
D 29
#define	X_CP_TIME	7
E 29
I 29
#define	X_CP_TIME	6
E 29
D 17
	{ "_dk_mspw" },
#define	X_DK_MSPW	8
E 17
I 17
D 23
	{ "_dk_wpms" },
E 23
I 23
	{ "_cp_time" },
E 23
D 29
#define	X_DK_WPMS	8
E 29
I 29
#define	X_DK_WPMS	7
E 29
E 17
I 9
D 23
	{ "_hz" },
E 23
I 23
	{ "_dk_wpms" },
E 23
D 29
#define	X_HZ		9
E 29
I 29
#define	X_HZ		8
E 29
E 9
I 7
D 10

E 10
I 10
D 23
	{ "_phz" },
E 23
I 23
	{ "_hz" },
E 23
D 29
#define	X_PHZ		10
E 29
I 29
D 33
#define	X_PHZ		9
E 29
I 13
D 23
	{ "_dk_ndrive" },
E 23
I 23
	{ "_phz" },
E 33
I 33
#define	X_STATHZ	9
	{ "_stathz" },
E 33
E 23
D 29
#define	X_DK_NDRIVE	11
E 29
I 29
#define	X_DK_NDRIVE	10
E 29
E 13
E 10
D 23
#ifdef vax
E 7
I 3
	{ "_mbdinit" },
D 9
#define X_MBDINIT	9
E 9
I 9
D 10
#define X_MBDINIT	10
E 10
I 10
D 13
#define X_MBDINIT	11
E 13
I 13
D 14
#define X_MBDINIT	12
E 14
I 14
#define X_MBDINIT	(X_DK_NDRIVE+1)
E 14
E 13
E 10
E 9
	{ "_ubdinit" },
D 9
#define X_UBDINIT	10
E 9
I 9
D 10
#define X_UBDINIT	11
E 10
I 10
D 13
#define X_UBDINIT	12
E 13
I 13
D 14
#define X_UBDINIT	13
E 14
I 14
#define X_UBDINIT	(X_DK_NDRIVE+2)
E 23
I 23
	{ "_dk_ndrive" },
D 30
#define	X_END		11
E 30
I 30
#define	X_END		10
E 30
D 35
#ifdef hp300
E 35
I 35
#if defined(hp300) || defined(luna68k)
E 35
#define	X_HPDINIT	(X_END+1)
	{ "_hp_dinit" },
E 23
E 14
E 13
E 10
E 9
I 7
#endif
I 37
#ifdef mips
#define	X_SCSI_DINIT	(X_END+1)
	{ "_scsi_dinit" },
#endif
E 37
I 14
#ifdef tahoe
D 23
#define	X_VBDINIT	(X_DK_NDRIVE+1)
E 23
I 23
#define	X_VBDINIT	(X_END+1)
E 23
	{ "_vbdinit" },
#endif
I 23
#ifdef vax
	{ "_mbdinit" },
#define X_MBDINIT	(X_END+1)
	{ "_ubdinit" },
#define X_UBDINIT	(X_END+2)
#endif
E 23
E 14
D 9

E 9
D 12
#ifdef sun
	{ "_mbdinit" },
D 9
#define X_MBDINIT	9
E 9
I 9
D 10
#define X_MBDINIT	10
E 10
I 10
#define X_MBDINIT	11
E 10
E 9
#endif
E 12
D 9

E 9
E 7
E 3
D 29
	{ 0 },
E 29
I 29
	{ NULL },
E 29
};
I 3

D 13
char dr_name[DK_NDRIVE][10];
E 13
I 13
D 21
char	**dr_name;
int	*dr_select;
D 17
float	*dk_mspw;
E 17
I 17
long	*dk_wpms;
E 17
int	dk_ndrive;
int	ndrives = 0;
E 21
I 21
D 23
double etime;
long *dk_wpms;
int *dr_select;
int dk_ndrive, hz, kmemfd, ndrives;
char **dr_name;

E 21
#ifdef vax
char	*defdrives[] = { "hp0", "hp1", "hp2",  0 };
#else
char	*defdrives[] = { 0 };
#endif
E 13

E 3
D 13
struct
{
E 13
I 13
struct {
E 23
I 23
struct _disk {
E 23
E 13
D 29
	int	dk_busy;
E 29
	long	cp_time[CPUSTATES];
D 13
	long	dk_time[DK_NDRIVE];
	long	dk_wds[DK_NDRIVE];
	long	dk_seek[DK_NDRIVE];
	long	dk_xfer[DK_NDRIVE];
	float	dk_mspw[DK_NDRIVE];
E 13
I 13
	long	*dk_time;
	long	*dk_wds;
	long	*dk_seek;
	long	*dk_xfer;
E 13
	long	tk_nin;
	long	tk_nout;
D 23
} s, s1;
E 23
I 23
} cur, last;
E 23

I 23
D 39
double etime;
long *dk_wpms;
int dk_ndrive, *dr_select, hz, kmemfd, ndrives;
char **dr_name;
E 39
I 39
kvm_t	 *kd;
double	  etime;
long	 *dk_wpms;
int	  dk_ndrive, *dr_select, hz, kmemfd, ndrives;
char	**dr_name;
E 39

I 33
D 39
kvm_t *kd;

E 39
E 33
D 29
#include "names.c"				/* XXX */

E 29
#define nlread(x, v) \
D 25
	kvm_read(nl[x].n_value, (void *)&(v), sizeof(v))
E 25
I 25
D 33
	kvm_read((void *)nl[x].n_value, (void *)&(v), sizeof(v))
E 33
I 33
D 36
	kvm_read(kd, nl[x].n_value, &(v), sizeof(v))
E 36
I 36
	kvm_read(kd, namelist[x].n_value, &(v), sizeof(v))
E 36
E 33
E 25

I 29
#include "names.c"				/* XXX */

D 31
static void cpustats __P((void)), dkstats __P((void)), phdr __P((int));
static void usage __P((void)), err __P((const char *, ...));
E 31
I 31
void cpustats __P((void));
void dkstats __P((void));
D 39
void err __P((const char *, ...));
E 39
void phdr __P((int));
void usage __P((void));
E 31

I 39
int
E 39
E 29
E 23
D 21
int	mf;
I 9
int	hz;
I 10
int	phz;
E 10
E 9
double	etime;
I 13
int	tohdr = 1;
int	printhdr();
E 13

E 21
main(argc, argv)
D 13
char *argv[];
E 13
I 13
D 21
	char *argv[];
E 21
I 21
	int argc;
D 39
	char **argv;
E 39
I 39
	char *argv[];
E 39
E 21
E 13
{
D 21
	extern char *ctime();
	register  i;
D 13
	int iter;
E 13
I 13
	int iter, ndrives;
E 13
	double f1, f2;
E 21
I 21
D 29
	extern int optind;
E 29
	register int i;
E 21
D 23
	long t;
E 23
I 23
	long tmp;
E 23
I 2
D 13
	int tohdr = 1;
E 13
I 13
D 21
	char *arg, **cp, name[6], buf[BUFSIZ];
E 21
I 21
D 33
	int ch, hdrcnt, reps, interval, phz, ndrives;
E 33
I 33
	int ch, hdrcnt, reps, interval, stathz, ndrives;
E 33
D 23
	char *arg, **cp, buf[BUFSIZ];
	void printhdr(), read_names(), stats(), stat1(), usage();
E 23
I 23
D 24
	char *arg, **cp, *memfile, *namelist, buf[30];
E 24
I 24
D 32
	char **cp, *memfile, *namelist, buf[30];
E 32
I 32
	char **cp, *memf, *nlistf, buf[30];
I 33
        char errbuf[_POSIX2_LINE_MAX];
E 33
E 32
E 24
D 26
	void printhdr(), read_names(), stats(), stat1(), usage(), error();
E 26
I 26
D 29
	void cpustats(), dkstats(), phdr(), read_names(), usage(), error();
E 29
E 26
E 23
E 21
E 13
E 2

I 21
	interval = reps = 0;
D 23
	while ((ch = getopt(argc, argv, "c:i:")) != EOF)
E 23
I 23
D 32
	namelist = memfile = NULL;
E 32
I 32
	nlistf = memf = NULL;
E 32
D 24
	while ((ch = getopt(argc, argv, "c:i:M:N:")) != EOF)
E 24
I 24
	while ((ch = getopt(argc, argv, "c:M:N:w:")) != EOF)
E 24
E 23
		switch(ch) {
		case 'c':
D 39
			reps = atoi(optarg);
E 39
I 39
			if ((reps = atoi(optarg)) <= 0)
				errx(1, "repetition count <= 0.");
E 39
			break;
D 24
		case 'i':
			interval = atoi(optarg);
			break;
E 24
I 23
		case 'M':
D 32
			memfile = optarg;
E 32
I 32
			memf = optarg;
E 32
			break;
		case 'N':
D 32
			namelist = optarg;
E 32
I 32
			nlistf = optarg;
E 32
			break;
I 24
		case 'w':
D 39
			interval = atoi(optarg);
E 39
I 39
			if ((interval = atoi(optarg)) <= 0)
				errx(1, "interval <= 0.");
E 39
			break;
E 24
E 23
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

E 21
D 16
	nlist("/vmunix", nl);
E 16
I 16
D 23
	nlist(_PATH_UNIX, nl);
E 16
D 21
	if(nl[X_DK_BUSY].n_type == 0) {
D 16
		printf("dk_busy not found in /vmunix namelist\n");
E 16
I 16
		fprintf(stderr, "iostat: dk_busy not found in %s namelist\n",
E 21
I 21
	if (nl[X_DK_BUSY].n_type == 0) {
		(void)fprintf(stderr,
		    "iostat: dk_busy not found in %s namelist\n",
E 21
		    _PATH_UNIX);
E 23
I 23
D 29
	if (kvm_openfiles(namelist, memfile, NULL) == -1) {
		error("kvm_openfiles: %s", kvm_geterr());
E 23
E 16
		exit(1);
	}
D 16
	mf = open("/dev/kmem", 0);
E 16
I 16
D 21
	mf = open(_PATH_KMEM, 0);
E 16
	if(mf < 0) {
D 16
		printf("cannot open /dev/kmem\n");
E 16
I 16
		fprintf(stderr, "iostat: cannot open %s\n", _PATH_KMEM);
E 21
I 21
D 23
	kmemfd = open(_PATH_KMEM, O_RDONLY);
	if (kmemfd < 0) {
		(void)fprintf(stderr, "iostat: cannot open %s\n", _PATH_KMEM);
E 23
I 23
	if (kvm_nlist(nl) == -1) {
		error("kvm_nlist: %s", kvm_geterr());
E 23
E 21
E 16
		exit(1);
	}
D 21
	iter = 0;
D 13
	while (argc>1&&argv[1][0]=='-') {
		argc--;
		argv++;
E 13
I 13
	for (argc--, argv++; argc > 0 && argv[0][0] == '-'; argc--, argv++)
		;
E 21
I 21
D 23

E 21
D 15
	if (nl[DK_NDRIVE].n_value == 0) {
E 15
I 15
	if (nl[X_DK_NDRIVE].n_value == 0) {
E 15
D 21
		printf("dk_ndrive undefined in system\n");
E 21
I 21
		(void)fprintf(stderr,
		    "iostat: dk_ndrive not found in %s namelist\n",
		    _PATH_UNIX);
E 23
I 23
	if (nl[X_DK_BUSY].n_type == 0) {
		error("dk_busy not found namelist");
E 23
E 21
		exit(1);
E 13
	}
D 13
	lseek(mf, (long)nl[X_DK_MSPW].n_value, 0);
	read(mf, s.dk_mspw, sizeof s.dk_mspw);
I 3
	for (i = 0; i < DK_NDRIVE; i++)
E 13
I 13
D 21
	lseek(mf, nl[X_DK_NDRIVE].n_value, L_SET);
	read(mf, &dk_ndrive, sizeof (dk_ndrive));
E 21
I 21
D 23
	(void)lseek(kmemfd, nl[X_DK_NDRIVE].n_value, L_SET);
	(void)read(kmemfd, &dk_ndrive, sizeof(dk_ndrive));
E 23
I 23
	if (nl[X_DK_NDRIVE].n_type == 0) {
		error("dk_ndrive not found in namelist");
		exit(1);
	}
E 29
I 29
D 32
	if (kvm_openfiles(namelist, memfile, NULL) == -1)
E 32
I 32
	/*
	 * Discard setgid privileges if not the running kernel so that bad
	 * guys can't print interesting stuff from kernel memory.
	 */
	if (nlistf != NULL || memf != NULL)
		setgid(getgid());

D 33
	if (kvm_openfiles(nlistf, memf, NULL) == -1)
E 32
		err("kvm_openfiles: %s", kvm_geterr());
	if (kvm_nlist(nl) == -1)
		err("kvm_nlist: %s", kvm_geterr());
E 33
I 33
        kd = kvm_openfiles(nlistf, memf, NULL, O_RDONLY, errbuf);
	if (kd == 0)
D 39
		err("kvm_openfiles: %s", errbuf);
E 39
I 39
		errx(1, "kvm_openfiles: %s", errbuf);
E 39
D 36
	if (kvm_nlist(kd, nl) == -1)
E 36
I 36
	if (kvm_nlist(kd, namelist) == -1)
E 36
D 39
		err("kvm_nlist: %s", kvm_geterr(kd));
E 39
I 39
		errx(1, "kvm_nlist: %s", kvm_geterr(kd));
E 39
E 33
D 36
	if (nl[X_DK_NDRIVE].n_type == 0)
E 36
I 36
	if (namelist[X_DK_NDRIVE].n_type == 0)
E 36
D 39
		err("dk_ndrive not found in namelist");
E 39
I 39
		errx(1, "dk_ndrive not found in namelist");
E 39
E 29
	(void)nlread(X_DK_NDRIVE, dk_ndrive);
E 23
E 21
D 29
	if (dk_ndrive <= 0) {
D 21
		printf("dk_ndrive %d\n", dk_ndrive);
E 21
I 21
D 23
		(void)fprintf(stderr, "iostat: dk_ndrive %d\n", dk_ndrive);
E 23
I 23
		error("invalid dk_ndrive %d\n", dk_ndrive);
E 23
E 21
		exit(1);
	}
E 29
I 29
	if (dk_ndrive <= 0)
D 39
		err("invalid dk_ndrive %d\n", dk_ndrive);
E 39
I 39
		errx(1, "invalid dk_ndrive %d\n", dk_ndrive);
E 39
E 29
D 21
	dr_select = (int *)calloc(dk_ndrive, sizeof (int));
	dr_name = (char **)calloc(dk_ndrive, sizeof (char *));
D 17
	dk_mspw = (float *)calloc(dk_ndrive, sizeof (float));
E 17
I 17
	dk_wpms = (long *)calloc(dk_ndrive, sizeof (long));
E 17
#define	allocate(e, t) \
    s./**/e = (t *)calloc(dk_ndrive, sizeof (t)); \
    s1./**/e = (t *)calloc(dk_ndrive, sizeof (t));
	allocate(dk_time, long);
	allocate(dk_wds, long);
	allocate(dk_seek, long);
	allocate(dk_xfer, long);
E 21
I 21

D 23
	s.dk_time = calloc(dk_ndrive, sizeof(long));
	s.dk_wds = calloc(dk_ndrive, sizeof(long));
	s.dk_seek = calloc(dk_ndrive, sizeof(long));
	s.dk_xfer = calloc(dk_ndrive, sizeof(long));
	s1.dk_time = calloc(dk_ndrive, sizeof(long));
	s1.dk_wds = calloc(dk_ndrive, sizeof(long));
	s1.dk_seek = calloc(dk_ndrive, sizeof(long));
	s1.dk_xfer = calloc(dk_ndrive, sizeof(long));
E 23
I 23
	cur.dk_time = calloc(dk_ndrive, sizeof(long));
	cur.dk_wds = calloc(dk_ndrive, sizeof(long));
	cur.dk_seek = calloc(dk_ndrive, sizeof(long));
	cur.dk_xfer = calloc(dk_ndrive, sizeof(long));
	last.dk_time = calloc(dk_ndrive, sizeof(long));
	last.dk_wds = calloc(dk_ndrive, sizeof(long));
	last.dk_seek = calloc(dk_ndrive, sizeof(long));
	last.dk_xfer = calloc(dk_ndrive, sizeof(long));
E 23
	dr_select = calloc(dk_ndrive, sizeof(int));
	dr_name = calloc(dk_ndrive, sizeof(char *));
	dk_wpms = calloc(dk_ndrive, sizeof(long));

E 21
D 24
	for (arg = buf, i = 0; i < dk_ndrive; i++) {
		dr_name[i] = arg;
E 13
D 21
		sprintf(dr_name[i], "dk%d", i);
E 21
I 21
		(void)sprintf(dr_name[i], "dk%d", i);
E 21
I 13
		arg += strlen(dr_name[i]) + 1;
E 24
I 24
	for (i = 0; i < dk_ndrive; i++) {
		(void)sprintf(buf, "dk%d", i);
		dr_name[i] = strdup(buf);
E 24
	}
E 13
D 34
	read_names();
E 34
I 34
	if (!read_names())
		exit(1);
E 34
E 3
D 13
	if(argc > 2)
		iter = atoi(argv[2]);
D 2
	printf("      TTY");
	for (i = 0; i < DK_NDRIVE; i++)
		if (s.dk_mspw[i] != 0.0)
			printf("           D%d ", i);
	printf("         CPU\n");
	printf(" tin tout");
	for (i = 0; i < DK_NDRIVE; i++)
		if (s.dk_mspw[i] != 0.0)
			printf(" sps tps msps ");
	printf(" us ni sy id\n");

E 2
loop:
I 2
	if (--tohdr == 0) {
D 3
		printf("      TTY");
E 3
I 3
		printf("      tty");
E 3
		for (i = 0; i < DK_NDRIVE; i++)
			if (s.dk_mspw[i] != 0.0)
D 3
				printf("           D%d ", i);
		printf("         CPU\n");
E 3
I 3
				printf("          %3.3s ", dr_name[i]);
		printf("         cpu\n");
E 3
		printf(" tin tout");
		for (i = 0; i < DK_NDRIVE; i++)
			if (s.dk_mspw[i] != 0.0)
D 8
				printf(" sps tps msps ");
E 8
I 8
				printf(" bps tps msps ");
E 8
		printf(" us ni sy id\n");
		tohdr = 19;
E 13
I 13
D 21
	lseek(mf, (long)nl[X_HZ].n_value, L_SET);
	read(mf, &hz, sizeof hz);
	lseek(mf, (long)nl[X_PHZ].n_value, L_SET);
	read(mf, &phz, sizeof phz);
E 21
I 21
D 23
	(void)lseek(kmemfd, (long)nl[X_HZ].n_value, L_SET);
	(void)read(kmemfd, &hz, sizeof(hz));
	(void)lseek(kmemfd, (long)nl[X_PHZ].n_value, L_SET);
	(void)read(kmemfd, &phz, sizeof(phz));
E 23
I 23
	(void)nlread(X_HZ, hz);
D 33
	(void)nlread(X_PHZ, phz);
E 23
E 21
	if (phz)
		hz = phz;
D 17
	lseek(mf, (long)nl[X_DK_MSPW].n_value, L_SET);
	read(mf, dk_mspw, dk_ndrive*sizeof (dk_mspw));
E 17
I 17
D 21
	lseek(mf, (long)nl[X_DK_WPMS].n_value, L_SET);
	read(mf, dk_wpms, dk_ndrive*sizeof (dk_wpms));
E 21
I 21
D 23
	(void)lseek(kmemfd, (long)nl[X_DK_WPMS].n_value, L_SET);
	(void)read(kmemfd, dk_wpms, dk_ndrive * sizeof(dk_wpms));
E 23
I 23
D 25
	(void)kvm_read(nl[X_DK_WPMS].n_value, dk_wpms,
E 25
I 25
	(void)kvm_read((void *)nl[X_DK_WPMS].n_value, dk_wpms,
E 33
I 33
	(void)nlread(X_STATHZ, stathz);
	if (stathz)
		hz = stathz;
D 36
	(void)kvm_read(kd, nl[X_DK_WPMS].n_value, dk_wpms,
E 36
I 36
	(void)kvm_read(kd, namelist[X_DK_WPMS].n_value, dk_wpms,
E 36
E 33
E 25
		dk_ndrive * sizeof(dk_wpms));
E 23

E 21
E 17
	/*
D 21
	 * Choose drives to be displayed.  Priority
	 * goes to (in order) drives supplied as arguments,
	 * default drives.  If everything isn't filled
	 * in and there are drives not taken care of,
	 * display the first few that fit.
E 21
I 21
	 * Choose drives to be displayed.  Priority goes to (in order) drives
	 * supplied as arguments and default drives.  If everything isn't
	 * filled in and there are drives not taken care of, display the first
	 * few that fit.
I 22
	 *
	 * The backward compatibility #ifdefs permit the syntax:
	 *	iostat [ drives ] [ interval [ count ] ]
E 22
E 21
	 */
D 21
	ndrives = 0;
	while (argc > 0 && !isdigit(argv[0][0])) {
E 21
I 21
D 22
	for (ndrives = 0; *argv; ++argv)
E 22
I 22
#define	BACKWARD_COMPATIBILITY
	for (ndrives = 0; *argv; ++argv) {
#ifdef	BACKWARD_COMPATIBILITY
		if (isdigit(**argv))
			break;
#endif
E 22
E 21
		for (i = 0; i < dk_ndrive; i++) {
D 21
			if (strcmp(dr_name[i], argv[0]))
E 21
I 21
			if (strcmp(dr_name[i], *argv))
E 21
				continue;
			dr_select[i] = 1;
D 21
			ndrives++;
E 21
I 21
			++ndrives;
E 21
		}
I 22
	}
#ifdef	BACKWARD_COMPATIBILITY
	if (*argv) {
		interval = atoi(*argv);
		if (*++argv)
			reps = atoi(*argv);
	}
#endif
I 27

	if (interval) {
		if (!reps)
			reps = -1;
	} else
		if (reps)
			interval = 1;

E 27
E 22
D 21
		argc--, argv++;
E 13
	}
E 21
E 2
D 13
	lseek(mf, (long)nl[X_DK_BUSY].n_value, 0);
E 13
I 13
	for (i = 0; i < dk_ndrive && ndrives < 4; i++) {
D 17
		if (dr_select[i] || dk_mspw[i] == 0.0)
E 17
I 17
		if (dr_select[i] || dk_wpms[i] == 0)
E 17
			continue;
		for (cp = defdrives; *cp; cp++)
			if (strcmp(dr_name[i], *cp) == 0) {
				dr_select[i] = 1;
D 21
				ndrives++;
E 21
I 21
				++ndrives;
E 21
				break;
			}
	}
	for (i = 0; i < dk_ndrive && ndrives < 4; i++) {
		if (dr_select[i])
			continue;
		dr_select[i] = 1;
D 21
		ndrives++;
E 21
I 21
		++ndrives;
E 21
	}
D 21
	if (argc > 1)
		iter = atoi(argv[1]);
	signal(SIGCONT, printhdr);
loop:
	if (--tohdr == 0)
		printhdr();
	lseek(mf, (long)nl[X_DK_BUSY].n_value, L_SET);
E 13
 	read(mf, &s.dk_busy, sizeof s.dk_busy);
D 13
 	lseek(mf, (long)nl[X_DK_TIME].n_value, 0);
 	read(mf, s.dk_time, sizeof s.dk_time);
 	lseek(mf, (long)nl[X_DK_XFER].n_value, 0);
 	read(mf, s.dk_xfer, sizeof s.dk_xfer);
 	lseek(mf, (long)nl[X_DK_WDS].n_value, 0);
 	read(mf, s.dk_wds, sizeof s.dk_wds);
 	lseek(mf, (long)nl[X_TK_NIN].n_value, 0);
E 13
I 13
 	lseek(mf, (long)nl[X_DK_TIME].n_value, L_SET);
 	read(mf, s.dk_time, dk_ndrive*sizeof (long));
 	lseek(mf, (long)nl[X_DK_XFER].n_value, L_SET);
 	read(mf, s.dk_xfer, dk_ndrive*sizeof (long));
 	lseek(mf, (long)nl[X_DK_WDS].n_value, L_SET);
 	read(mf, s.dk_wds, dk_ndrive*sizeof (long));
	lseek(mf, (long)nl[X_DK_SEEK].n_value, L_SET);
	read(mf, s.dk_seek, dk_ndrive*sizeof (long));
 	lseek(mf, (long)nl[X_TK_NIN].n_value, L_SET);
E 13
 	read(mf, &s.tk_nin, sizeof s.tk_nin);
D 13
 	lseek(mf, (long)nl[X_TK_NOUT].n_value, 0);
E 13
I 13
 	lseek(mf, (long)nl[X_TK_NOUT].n_value, L_SET);
E 13
 	read(mf, &s.tk_nout, sizeof s.tk_nout);
D 13
	lseek(mf, (long)nl[X_DK_SEEK].n_value, 0);
	read(mf, s.dk_seek, sizeof s.dk_seek);
	lseek(mf, (long)nl[X_CP_TIME].n_value, 0);
E 13
I 13
	lseek(mf, (long)nl[X_CP_TIME].n_value, L_SET);
E 13
	read(mf, s.cp_time, sizeof s.cp_time);
D 13
	lseek(mf, (long)nl[X_DK_MSPW].n_value, 0);
	read(mf, s.dk_mspw, sizeof s.dk_mspw);
I 9
	lseek(mf, (long)nl[X_HZ].n_value, 0);
	read(mf, &hz, sizeof hz);
I 10
	lseek(mf, (long)nl[X_PHZ].n_value, 0);
	read(mf, &phz, sizeof phz);
	if (phz)
		hz = phz;
E 10
E 9
	for (i = 0; i < DK_NDRIVE; i++) {
E 13
I 13
	for (i = 0; i < dk_ndrive; i++) {
		if (!dr_select[i])
			continue;
E 21
I 21

D 26
	(void)signal(SIGCONT, printhdr);
E 26
I 26
	(void)signal(SIGCONT, phdr);
E 26

	for (hdrcnt = 1;;) {
		if (!--hdrcnt) {
D 26
			printhdr();
E 26
I 26
D 29
			phdr();
E 29
I 29
			phdr(0);
E 29
E 26
			hdrcnt = 20;
		}
D 23
		(void)lseek(kmemfd, (long)nl[X_DK_BUSY].n_value, L_SET);
		(void)read(kmemfd, &s.dk_busy, sizeof(s.dk_busy));
		(void)lseek(kmemfd, (long)nl[X_DK_TIME].n_value, L_SET);
		(void)read(kmemfd, s.dk_time, dk_ndrive * sizeof(long));
		(void)lseek(kmemfd, (long)nl[X_DK_XFER].n_value, L_SET);
		(void)read(kmemfd, s.dk_xfer, dk_ndrive * sizeof(long));
		(void)lseek(kmemfd, (long)nl[X_DK_WDS].n_value, L_SET);
		(void)read(kmemfd, s.dk_wds, dk_ndrive * sizeof(long));
		(void)lseek(kmemfd, (long)nl[X_DK_SEEK].n_value, L_SET);
		(void)read(kmemfd, s.dk_seek, dk_ndrive * sizeof(long));
		(void)lseek(kmemfd, (long)nl[X_TK_NIN].n_value, L_SET);
		(void)read(kmemfd, &s.tk_nin, sizeof(s.tk_nin));
		(void)lseek(kmemfd, (long)nl[X_TK_NOUT].n_value, L_SET);
		(void)read(kmemfd, &s.tk_nout, sizeof(s.tk_nout));
		(void)lseek(kmemfd, (long)nl[X_CP_TIME].n_value, L_SET);
		(void)read(kmemfd, s.cp_time, sizeof(s.cp_time));
E 23
I 23
D 29
		(void)nlread(X_DK_BUSY, cur.dk_busy);
E 29
D 25
		(void)kvm_read(nl[X_DK_TIME].n_value,
E 25
I 25
D 33
		(void)kvm_read((void *)nl[X_DK_TIME].n_value,
E 33
I 33
D 36
		(void)kvm_read(kd, nl[X_DK_TIME].n_value,
E 36
I 36
		(void)kvm_read(kd, namelist[X_DK_TIME].n_value,
E 36
E 33
E 25
		    cur.dk_time, dk_ndrive * sizeof(long));
D 25
		(void)kvm_read(nl[X_DK_XFER].n_value,
E 25
I 25
D 33
		(void)kvm_read((void *)nl[X_DK_XFER].n_value,
E 33
I 33
D 36
		(void)kvm_read(kd, nl[X_DK_XFER].n_value,
E 36
I 36
		(void)kvm_read(kd, namelist[X_DK_XFER].n_value,
E 36
E 33
E 25
		    cur.dk_xfer, dk_ndrive * sizeof(long));
D 25
		(void)kvm_read(nl[X_DK_WDS].n_value,
E 25
I 25
D 33
		(void)kvm_read((void *)nl[X_DK_WDS].n_value,
E 33
I 33
D 36
		(void)kvm_read(kd, nl[X_DK_WDS].n_value,
E 36
I 36
		(void)kvm_read(kd, namelist[X_DK_WDS].n_value,
E 36
E 33
E 25
		    cur.dk_wds, dk_ndrive * sizeof(long));
D 25
		(void)kvm_read(nl[X_DK_SEEK].n_value,
E 25
I 25
D 33
		(void)kvm_read((void *)nl[X_DK_SEEK].n_value,
E 33
I 33
D 36
		(void)kvm_read(kd, nl[X_DK_SEEK].n_value,
E 36
I 36
		(void)kvm_read(kd, namelist[X_DK_SEEK].n_value,
E 36
E 33
E 25
		    cur.dk_seek, dk_ndrive * sizeof(long));
D 25
		(void)kvm_read(nl[X_TK_NIN].n_value,
E 25
I 25
D 33
		(void)kvm_read((void *)nl[X_TK_NIN].n_value,
E 33
I 33
D 36
		(void)kvm_read(kd, nl[X_TK_NIN].n_value,
E 36
I 36
		(void)kvm_read(kd, namelist[X_TK_NIN].n_value,
E 36
E 33
E 25
		    &cur.tk_nin, sizeof(cur.tk_nin));
D 25
		(void)kvm_read(nl[X_TK_NOUT].n_value,
E 25
I 25
D 33
		(void)kvm_read((void *)nl[X_TK_NOUT].n_value,
E 33
I 33
D 36
		(void)kvm_read(kd, nl[X_TK_NOUT].n_value,
E 36
I 36
		(void)kvm_read(kd, namelist[X_TK_NOUT].n_value,
E 36
E 33
E 25
		    &cur.tk_nout, sizeof(cur.tk_nout));
D 25
		(void)kvm_read(nl[X_CP_TIME].n_value,
E 25
I 25
D 33
		(void)kvm_read((void *)nl[X_CP_TIME].n_value,
E 33
I 33
D 36
		(void)kvm_read(kd, nl[X_CP_TIME].n_value,
E 36
I 36
		(void)kvm_read(kd, namelist[X_CP_TIME].n_value,
E 36
E 33
E 25
		    cur.cp_time, sizeof(cur.cp_time));
E 23
		for (i = 0; i < dk_ndrive; i++) {
			if (!dr_select[i])
				continue;
E 21
E 13
D 23
#define X(fld)	t = s.fld[i]; s.fld[i] -= s1.fld[i]; s1.fld[i] = t
E 23
I 23
#define X(fld)	tmp = cur.fld[i]; cur.fld[i] -= last.fld[i]; last.fld[i] = tmp
E 23
D 21
		X(dk_xfer); X(dk_seek); X(dk_wds); X(dk_time);
E 21
I 21
			X(dk_xfer);
			X(dk_seek);
			X(dk_wds);
			X(dk_time);
		}
D 23
		t = s.tk_nin;
		s.tk_nin -= s1.tk_nin;
		s1.tk_nin = t;
		t = s.tk_nout;
		s.tk_nout -= s1.tk_nout;
		s1.tk_nout = t;
E 23
I 23
		tmp = cur.tk_nin;
		cur.tk_nin -= last.tk_nin;
		last.tk_nin = tmp;
		tmp = cur.tk_nout;
		cur.tk_nout -= last.tk_nout;
		last.tk_nout = tmp;
E 23
		etime = 0;
		for (i = 0; i < CPUSTATES; i++) {
			X(cp_time);
D 23
			etime += s.cp_time[i];
E 23
I 23
			etime += cur.cp_time[i];
E 23
		}
		if (etime == 0.0)
			etime = 1.0;
D 23
		etime /= (float) hz;
		(void)printf("%4.0f%5.0f", s.tk_nin / etime, s.tk_nout / etime);
E 23
I 23
		etime /= (float)hz;
		(void)printf("%4.0f%5.0f",
		    cur.tk_nin / etime, cur.tk_nout / etime);
E 23
D 26
		for (i = 0; i < dk_ndrive; i++)
			if (dr_select[i])
				stats(i);
		for (i = 0; i < CPUSTATES; i++)
			stat1(i);
E 26
I 26
D 29
		dkstats(i);
		cpustats(i);
E 29
I 29
		dkstats();
		cpustats();
E 29
E 26
		(void)printf("\n");
		(void)fflush(stdout);

D 27
		if (--reps <= 0)
E 27
I 27
		if (reps >= 0 && --reps <= 0)
E 27
			break;
D 28
		if (interval)
			(void)sleep(interval);
E 28
I 28
		(void)sleep(interval);
E 28
E 21
	}
D 21
	t = s.tk_nin; s.tk_nin -= s1.tk_nin; s1.tk_nin = t;
	t = s.tk_nout; s.tk_nout -= s1.tk_nout; s1.tk_nout = t;
	etime = 0;
	for(i=0; i<CPUSTATES; i++) {
		X(cp_time);
		etime += s.cp_time[i];
	}
	if (etime == 0.0)
		etime = 1.0;
D 9
	etime /= 60.0;
E 9
I 9
	etime /= (float) hz;
E 9
	printf("%4.0f%5.0f", s.tk_nin/etime, s.tk_nout/etime);
D 13
	for (i=0; i<DK_NDRIVE; i++)
		if (s.dk_mspw[i] != 0.0)
E 13
I 13
	for (i=0; i<dk_ndrive; i++)
		if (dr_select[i])
E 13
			stats(i);
	for (i=0; i<CPUSTATES; i++)
		stat1(i);
	printf("\n");
I 11
	fflush(stdout);
E 11
contin:
D 13
	--iter;
	if(iter)
	if(argc > 1) {
		sleep(atoi(argv[1]));
E 13
I 13
	if (--iter && argc > 0) {
		sleep(atoi(argv[0]));
E 13
		goto loop;
	}
E 21
I 21
	exit(0);
E 21
}

I 29
/* ARGUSED */
E 29
I 21
void
E 21
I 13
D 26
printhdr()
E 26
I 26
D 29
phdr()
E 29
I 29
D 39
phdr(notused)
	int notused;
E 39
I 39
phdr(signo)
	int signo;
E 39
E 29
E 26
{
	register int i;

D 21
	printf("      tty");
E 21
I 21
	(void)printf("      tty");
E 21
	for (i = 0; i < dk_ndrive; i++)
		if (dr_select[i])
D 21
			printf("          %3.3s ", dr_name[i]);
	printf("         cpu\n");
	printf(" tin tout");
E 21
I 21
			(void)printf("          %3.3s ", dr_name[i]);
	(void)printf("         cpu\n tin tout");
E 21
	for (i = 0; i < dk_ndrive; i++)
		if (dr_select[i])
D 21
			printf(" bps tps msps ");
	printf(" us ni sy id\n");
	tohdr = 19;
E 21
I 21
D 26
			(void)printf(" bps tps msps ");
E 26
I 26
			(void)printf(" sps tps msps ");
E 26
D 40
	(void)printf(" us ni sy id\n");
E 40
I 40
	(void)printf(" us ni sy in id\n");
E 40
E 21
}

I 21
void
E 21
E 13
D 26
stats(dn)
I 21
	int dn;
E 26
I 26
dkstats()
E 26
E 21
{
D 21
	register i;
E 21
D 26
	double atime, words, xtime, itime;
E 26
I 26
	register int dn;
	double atime, itime, msps, words, xtime;
E 26

D 13
	if (s.dk_mspw[dn] == 0.0) {
E 13
I 13
D 17
	if (dk_mspw[dn] == 0.0) {
E 17
I 17
D 26
	if (dk_wpms[dn] == 0) {
E 17
E 13
D 21
		printf("%4.0f%4.0f%5.1f ", 0.0, 0.0, 0.0);
E 21
I 21
		(void)printf("%4.0f%4.0f%5.1f ", 0.0, 0.0, 0.0);
E 21
		return;
E 26
I 26
	for (dn = 0; dn < dk_ndrive; ++dn) {
		if (!dr_select[dn])
			continue;
		words = cur.dk_wds[dn] * 32;		/* words xfer'd */
		(void)printf("%4.0f",			/* sectors */
		    words / (DEV_BSIZE / 2) / etime);

		(void)printf("%4.0f", cur.dk_xfer[dn] / etime);

		if (dk_wpms[dn] && cur.dk_xfer[dn]) {
			atime = cur.dk_time[dn];	/* ticks disk busy */
			atime /= (float)hz;		/* ticks to seconds */
			xtime = words / dk_wpms[dn];	/* transfer time */
			itime = atime - xtime;		/* time not xfer'ing */
			if (itime < 0)
				msps = 0;
			else 
				msps = itime * 1000 / cur.dk_xfer[dn];
		} else
			msps = 0;
		(void)printf("%5.1f ", msps);
E 26
	}
D 23
	atime = s.dk_time[dn];
E 23
I 23
D 26
	atime = cur.dk_time[dn];
E 23
D 9
	atime /= 60.0;
E 9
I 9
D 21
	atime /= (float) hz;
E 9
	words = s.dk_wds[dn]*32.0;	/* number of words transferred */
D 13
	xtime = s.dk_mspw[dn]*words;	/* transfer time */
E 13
I 13
D 17
	xtime = dk_mspw[dn]*words;	/* transfer time */
E 17
I 17
	xtime = words/dk_wpms[dn];	/* transfer time */
E 21
I 21
	atime /= (float)hz;
D 23
	words = s.dk_wds[dn] * 32.0;	/* number of words transferred */
E 23
I 23
	words = cur.dk_wds[dn] * 32.0;	/* number of words transferred */
E 23
	xtime = words / dk_wpms[dn];	/* transfer time */
E 21
E 17
E 13
	itime = atime - xtime;		/* time not transferring */
D 13
/*
	printf("\ndn %d, words %8.2f, atime %6.2f, xtime %6.2f, itime %6.2f\n",
	    dn, words, atime, xtime, itime);
*/
E 13
	if (xtime < 0)
		itime += xtime, xtime = 0;
	if (itime < 0)
		xtime += itime, itime = 0;
D 8
	printf("%4.0f", s.dk_seek[dn]/etime);
E 8
I 8
D 21
	printf("%4.0f", words/512/etime);
E 8
	printf("%4.0f", s.dk_xfer[dn]/etime);
	printf("%5.1f ",
	    s.dk_seek[dn] ? itime*1000./s.dk_seek[dn] : 0.0);
E 21
I 21
	(void)printf("%4.0f", words / 512 / etime);
D 23
	(void)printf("%4.0f", s.dk_xfer[dn] / etime);
E 23
I 23
	(void)printf("%4.0f", cur.dk_xfer[dn] / etime);
E 23
	(void)printf("%5.1f ",
D 23
	    s.dk_seek[dn] ? itime * 1000. / s.dk_seek[dn] : 0.0);
E 23
I 23
	    cur.dk_seek[dn] ? itime * 1000. / cur.dk_seek[dn] : 0.0);
E 26
E 23
E 21
D 13
/*
	printf("%4.1f",
	    s.dk_xfer[dn] ? xtime*1000./s.dk_xfer[dn] : 0.0);
*/
E 13
}

D 21
stat1(o)
E 21
I 21
void
D 26
stat1(state)
	int state;
E 26
I 26
cpustats()
E 26
E 21
{
D 21
	register i;
E 21
I 21
D 26
	register int i;
E 26
I 26
	register int state;
E 26
E 21
	double time;

	time = 0;
D 21
	for(i=0; i<CPUSTATES; i++)
E 21
I 21
D 26
	for (i = 0; i < CPUSTATES; i++)
E 21
D 23
		time += s.cp_time[i];
E 23
I 23
		time += cur.cp_time[i];
E 23
	if (time == 0.0)
		time = 1.0;
D 11
	printf("%3.0f", 100*s.cp_time[o]/time);
E 11
I 11
D 21
	printf("%3.0f", 100.*s.cp_time[o]/time);
E 21
I 21
D 23
	(void)printf("%3.0f", 100. * s.cp_time[state] / time);
E 23
I 23
	(void)printf("%3.0f", 100. * cur.cp_time[state] / time);
E 26
I 26
	for (state = 0; state < CPUSTATES; ++state)
		time += cur.cp_time[state];
	for (state = 0; state < CPUSTATES; ++state)
		(void)printf("%3.0f",
		    100. * cur.cp_time[state] / (time ? time : 1));
E 26
E 23
E 21
E 11
I 3
}

D 7
/*
 * Read the drive names out of kmem.
 * ARGH ARGH ARGH ARGH !!!!!!!!!!!!
 */

E 7
D 13
#define steal(where, var) lseek(mf, where, 0); read(mf, &var, sizeof var);
E 13
I 13
D 21
#define steal(where, var) \
    lseek(mf, where, L_SET); read(mf, &var, sizeof var);
E 21
I 21
void
usage()
{
	(void)fprintf(stderr,
D 23
	    "usage: iostat [-c count] [-i interval] [drives]\n");
E 23
I 23
D 24
"usage: iostat [-c count] [-i interval] [-M core] [-N system] [drives]\n");
E 24
I 24
"usage: iostat [-c count] [-M core] [-N system] [-w wait] [drives]\n");
E 24
E 23
	exit(1);
D 39
}
E 21
E 13
I 7

I 29
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

E 29
I 21
D 23
#define	steal(where, var) \
	(void)lseek(kmemfd, (where), L_SET); \
	(void)read(kmemfd, &var, sizeof(var));

E 21
#ifdef vax
I 13
D 19
#include <vaxuba/ubavar.h>
#include <vaxmba/mbavar.h>
E 19
I 19
#include <vax/uba/ubavar.h>
#include <vax/mba/mbavar.h>
E 19

E 23
I 21
void
E 21
E 13
E 7
D 23
read_names()
E 23
I 23
D 29
error(fmt)
E 29
I 29
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
E 29
	char *fmt;
I 29
        va_dcl
#endif
E 29
E 23
{
D 23
	struct mba_device mdev;
	register struct mba_device *mp;
	struct mba_driver mdrv;
	short two_char;
	char *cp = (char *) &two_char;
	struct uba_device udev, *up;
	struct uba_driver udrv;
E 23
I 23
	va_list ap;
E 23
D 29

D 23
	mp = (struct mba_device *) nl[X_MBDINIT].n_value;
	up = (struct uba_device *) nl[X_UBDINIT].n_value;
D 6
	if (mp == 0 || up == 0)
E 6
I 6
D 13
	if (up == 0)
E 6
	{
E 13
I 13
	if (up == 0) {
E 13
D 21
		fprintf(stderr, "iostat: Disk init info not in namelist\n");
E 21
I 21
		(void)fprintf(stderr,
		    "iostat: disk init info not in namelist\n");
E 21
		exit(1);
	}
I 6
D 7
	if (mp)
E 6
	while(1)
	{
E 7
I 7
	if (mp) for (;;) {
E 7
		steal(mp++, mdev);
		if (mdev.mi_driver == 0)
			break;
		if (mdev.mi_dk < 0 || mdev.mi_alive == 0)
			continue;
		steal(mdev.mi_driver, mdrv);
		steal(mdrv.md_dname, two_char);
D 13
		sprintf(dr_name[mdev.mi_dk], "%c%c%d", cp[0], cp[1], mdev.mi_unit);
E 13
I 13
D 21
		sprintf(dr_name[mdev.mi_dk], "%c%c%d",
E 21
I 21
		(void)sprintf(dr_name[mdev.mi_dk], "%c%c%d",
E 21
		    cp[0], cp[1], mdev.mi_unit);
E 13
	}
D 7
	while(1)
	{
E 7
I 7
	if (up) for (;;) {
E 7
		steal(up++, udev);
		if (udev.ui_driver == 0)
			break;
		if (udev.ui_dk < 0 || udev.ui_alive == 0)
			continue;
		steal(udev.ui_driver, udrv);
		steal(udrv.ud_dname, two_char);
D 13
		sprintf(dr_name[udev.ui_dk], "%c%c%d", cp[0], cp[1], udev.ui_unit);
E 13
I 13
D 21
		sprintf(dr_name[udev.ui_dk], "%c%c%d",
E 21
I 21
		(void)sprintf(dr_name[udev.ui_dk], "%c%c%d",
E 21
		    cp[0], cp[1], udev.ui_unit);
I 14
	}
E 23
I 23
        va_start(ap, fmt);
        (void)fprintf(stderr, "iostat: ");
        (void)vfprintf(stderr, fmt, ap);
        (void)fprintf(stderr, "\n");
        va_end(ap);
E 29
I 29
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "iostat: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 39
E 29
E 23
}
D 21
#endif
E 21
I 21
D 23
#endif /* vax */
E 21

#ifdef tahoe
D 18
#include <tahoevba/vbavar.h>
E 18
I 18
#include <tahoe/vba/vbavar.h>
E 18

D 21
/*
 * Read the drive names out of kmem.
 */
E 21
I 21
void
E 21
read_names()
{
	struct vba_device udev, *up;
	struct vba_driver udrv;
	short two_char;
	char *cp = (char *)&two_char;

D 21
	up = (struct vba_device *) nl[X_VBDINIT].n_value;
E 21
I 21
	up = (struct vba_device *)nl[X_VBDINIT].n_value;
E 21
	if (up == 0) {
D 21
		fprintf(stderr, "vmstat: Disk init info not in namelist\n");
E 21
I 21
		(void)fprintf(stderr,
		    "iostat: disk init info not in namelist\n");
E 21
		exit(1);
	}
	for (;;) {
		steal(up++, udev);
		if (udev.ui_driver == 0)
			break;
		if (udev.ui_dk < 0 || udev.ui_alive == 0)
			continue;
		steal(udev.ui_driver, udrv);
		steal(udrv.ud_dname, two_char);
D 21
		sprintf(dr_name[udev.ui_dk], "%c%c%d",
E 21
I 21
		(void)sprintf(dr_name[udev.ui_dk], "%c%c%d",
E 21
		     cp[0], cp[1], udev.ui_unit);
E 14
E 13
D 12
	}
E 3
}
I 7
#endif

#ifdef sun
read_names()
{
	struct mb_device mdev;
	register struct mb_device *mp;
	struct mb_driver mdrv;
	short two_char;
	char *cp = (char *) &two_char;

	mp = (struct mb_device *) nl[X_MBDINIT].n_value;
	if (mp == 0) {
		fprintf(stderr, "iostat: Disk init info not in namelist\n");
		exit(1);
	}
	for (;;) {
		steal(mp++, mdev);
		if (mdev.md_driver == 0)
			break;
		if (mdev.md_dk < 0 || mdev.md_alive == 0)
			continue;
		steal(mdev.md_driver, mdrv);
		steal(mdrv.mdr_dname, two_char);
		sprintf(dr_name[mdev.md_dk], "%c%c%d", cp[0], cp[1], mdev.md_unit);
E 12
	}
}
D 21
#endif
E 21
I 21
#endif /* tahoe */
E 23
E 21
E 7
E 1
