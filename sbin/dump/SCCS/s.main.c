h64269
s 00135/00109/00425
d D 8.6 95/05/01 23:40:00 mckusick 51 50
c use getopt option syntax
e
s 00003/00003/00531
d D 8.5 95/04/28 10:29:25 bostic 50 49
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00001/00001/00533
d D 8.4 94/04/15 13:09:39 mckusick 49 48
c do not dump core when invoked with no arguments (from leres@lbl)
e
s 00006/00002/00528
d D 8.3 94/03/28 08:03:12 bostic 48 47
c The 'for' loop checks the contents of cp w/o ever checking that
c it's not NULL.
c From: "Chris G. Demetriou" <cgd@sun-lamp.cs.berkeley.edu>
e
s 00001/00001/00529
d D 8.2 94/01/06 09:48:45 mckusick 47 46
c get with the times (from cgd@vangogh)
e
s 00005/00005/00525
d D 8.1 93/06/05 10:52:46 bostic 46 45
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00151/00143/00379
d D 5.26 93/05/11 14:01:36 torek 45 44
c less-hairy maxino logic; compat for SunOS and other 4.2/4.3 systems;
c control for honoring UF_NODUMP; lint; prettiness police
e
s 00027/00023/00495
d D 5.25 93/01/25 15:36:07 mckusick 44 43
c cleanups from leres@lbl
e
s 00029/00022/00489
d D 5.24 92/07/16 12:39:55 bostic 43 42
c fix the prototypes, minor cleanup to signal handlers
e
s 00002/00000/00509
d D 5.23 92/06/20 15:50:16 mckusick 42 41
c Mark tapes with new format inodes as DR_NEWINODEFMT
e
s 00071/00046/00438
d D 5.22 92/06/18 14:06:24 mckusick 41 40
c lint; add Tflag
e
s 00001/00000/00483
d D 5.21 92/05/26 10:07:00 mckusick 40 39
c add <sys/time.h> for dinode.h
e
s 00002/00002/00481
d D 5.20 91/11/10 13:05:06 bostic 39 38
c break UFS up into FFS/UFS/LFS/MFS
e
s 00000/00001/00483
d D 5.19 91/07/23 21:09:52 mckusick 38 37
c delete unneeded include of dir.h
e
s 00028/00000/00456
d D 5.18 91/07/23 16:48:43 mckusick 37 36
c temporarily add ifdef sunos (includes) to assist Steve Romig in debugging
e
s 00018/00032/00438
d D 5.17 91/07/23 16:47:53 mckusick 36 35
c merge rdump and dump
e
s 00001/00001/00469
d D 5.16 91/04/24 15:01:06 karels 35 34
c fix changes from last time: blockswritten isn't per volume (as the error msg
c said); more info on errors
e
s 00011/00004/00459
d D 5.15 91/03/07 17:49:58 mckusick 34 33
c verified to be free of AT&T code
e
s 00008/00008/00455
d D 5.14 91/03/07 12:01:13 mckusick 33 32
c lint, misc cleanups
e
s 00018/00002/00445
d D 5.13 91/02/28 19:33:50 bostic 32 31
c ANSI; break #includes out of dump.h into separate files
e
s 00182/00138/00265
d D 5.12 91/02/28 18:57:39 mckusick 31 30
c overhaul argument processing; use new traversal algorithms
e
s 00094/00059/00309
d D 5.11 91/02/24 14:03:28 mckusick 30 29
c updates from Mike to make messages more media independent;
c add 'B' flag to specify number of blocks per volume
e
s 00028/00023/00340
d D 5.10 91/02/23 16:15:16 torek 29 28
c add dev_bshift to reduce multiply and divide by dev_bsize to shifts,
c and likewise tp_bshift; fix gcc warnings; quit via new quit() function
e
s 00002/00002/00361
d D 5.9 91/02/03 01:47:12 torek 28 27
c rewind => trewind (for ANSI C)
e
s 00002/00002/00361
d D 5.8 89/05/11 13:52:28 bostic 27 26
c file reorg, pathnames.h, paths.h
e
s 00003/00002/00360
d D 5.7 89/04/02 12:31:32 bostic 26 25
c add pathnames.h
e
s 00003/00001/00359
d D 5.6 87/02/23 18:06:31 mckusick 25 24
c convert SBLOCK to SBOFF; generalize dev_bsize
e
s 00011/00001/00349
d D 5.5 86/10/21 15:52:33 mckusick 24 23
c place all the dump information in the new dump header
e
s 00001/00000/00349
d D 5.4 86/05/28 11:11:43 mckusick 23 22
c finally no longer need setuid root except for rmthost()
e
s 00001/00001/00348
d D 5.3 86/05/23 11:18:14 mckusick 22 21
c put back that newline!
e
s 00010/00004/00339
d D 5.2 86/01/09 21:28:37 mckusick 21 20
c speedup and cleanup by Chris Torek
e
s 00010/00001/00333
d D 5.1 85/06/05 08:45:48 dist 20 18
c Add copyright
e
s 00002/00000/00334
d R 1.19 85/04/16 14:10:26 mckusick 19 18
c assume infinite length tape when outputting to a pipe
e
s 00004/00001/00330
d D 1.18 85/03/24 18:06:47 mckusick 18 17
c use HIGHDENSITYTREC for 6250 BPI dumps
e
s 00001/00001/00330
d D 1.17 84/10/05 15:56:05 mckusick 17 16
c maintain consistent dump tapes on active systems (decvax!watmath!srradia)
e
s 00002/00002/00329
d D 1.16 84/03/28 19:04:17 mckusick 16 15
c correct estimate of number of cartridge tapes needed to dump
e
s 00000/00001/00331
d D 1.15 83/08/19 19:45:57 sam 15 14
c extraneous divide in dump size calculation (from bruce jerrick)
e
s 00002/00001/00330
d D 1.14 83/06/09 12:50:35 mckusick 14 13
c print out correct previous incremental number
e
s 00001/00005/00330
d D 1.13 83/05/19 19:26:35 mckusick 13 12
c introduce true locking on /etc/dumpdates; 
c get rid of -J option that converts from /etc/ddates to /etc/dumpdates
e
s 00014/00003/00321
d D 1.12 83/05/08 19:11:19 mckusick 12 11
c add ability to dump to standard output
e
s 00055/00007/00269
d D 1.11 83/02/11 12:58:20 sam 11 10
c merge from sun
e
s 00003/00002/00273
d D 1.10 82/10/11 17:58:26 mckusick 10 9
c output clean-up
e
s 00001/00001/00274
d D 1.9 82/10/07 18:40:50 mckusick 9 8
c format fix
e
s 00014/00014/00261
d D 1.8 82/05/20 16:30:33 sam 8 7
c back to the depths
e
s 00025/00001/00250
d D 1.7 82/05/20 15:11:05 sam 7 6
c convert to calder
e
s 00001/00001/00250
d D 1.6 82/01/06 23:01:32 mckusic 6 5
c incorporate fs.h -r1.10, and param.h -r1.8 reorganization
e
s 00029/00017/00222
d D 1.5 82/01/05 01:37:16 mckusic 5 4
c parameterize BSIZE, FSIZE, and FRAG into fs_bsize, fs_fsize, and fs_frag
e
s 00001/00001/00238
d D 1.4 81/11/07 14:53:12 mckusic 4 3
c dump to "standard" (ie 1K file system) dump tapes
e
s 00001/00000/00238
d D 1.3 81/10/25 17:36:38 mckusic 3 2
c shut type clash warning
e
s 00005/00001/00233
d D 1.2 80/10/16 10:12:33 root 2 1
c Option 'w' tells only what to dump; 'W' tells most recent dump(s)
e
s 00234/00000/00000
d D 1.1 80/10/13 17:30:26 root 1 0
c date and time created 80/10/13 17:30:26 by root
e
u
U
t
T
I 1
D 20
static	char *sccsid = "%W% (Berkeley) %G%";
E 20
I 20
D 34
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 34
I 34
/*-
D 46
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 46
I 46
D 48
 * Copyright (c) 1980, 1991, 1993
E 48
I 48
 * Copyright (c) 1980, 1991, 1993, 1994
E 48
 *	The Regents of the University of California.  All rights reserved.
E 46
 *
 * %sccs.include.redist.c%
E 34
 */
I 34

#ifndef lint
D 46
char copyright[] =
"%Z% Copyright (c) 1980, 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 46
I 46
static char copyright[] =
D 48
"%Z% Copyright (c) 1980, 1991, 1993\n\
E 48
I 48
"%Z% Copyright (c) 1980, 1991, 1993, 1994\n\
E 48
	The Regents of the University of California.  All rights reserved.\n";
E 46
#endif /* not lint */
E 34

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 29
#endif not lint
E 29
I 29
#endif /* not lint */
E 29

I 37
D 44
#ifdef sunos
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
E 44
E 37
E 20
D 32
#include "dump.h"
E 32
I 32
#include <sys/param.h>
I 37
D 44
#include <sys/stat.h>
E 44
I 44
#include <sys/time.h>
#ifdef sunos
#include <sys/vnode.h>

#include <ufs/inode.h>
E 44
D 41
#include <sys/time.h>
#include <sys/dir.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 41
I 41
#include <ufs/fs.h>
E 41
#else
D 44
#include <sys/param.h>
I 40
#include <sys/time.h>
E 44
E 40
E 37
D 38
#include <ufs/dir.h>
E 38
D 39
#include <ufs/dinode.h>
E 39
I 39
D 41
#include <ufs/ufs/dinode.h>
E 39
I 37
#endif
E 41
E 37
D 39
#include <ufs/fs.h>
E 39
I 39
D 51
#include <ufs/ffs/fs.h>
E 51
I 41
D 44
#endif
E 44
#include <ufs/ufs/dinode.h>
I 51
#include <ufs/ffs/fs.h>
E 51
E 41
E 39
D 44
#include <protocols/dumprestore.h>
#include <signal.h>
#ifdef __STDC__
#include <time.h>
E 44
#endif
I 44

#include <protocols/dumprestore.h>

I 45
#include <ctype.h>
I 51
#include <err.h>
E 51
E 45
#include <errno.h>
E 44
E 32
I 29
#include <fcntl.h>
I 32
#include <fstab.h>
I 44
#include <signal.h>
E 44
#include <stdio.h>
D 51
#ifdef __STDC__
E 51
D 44
#include <unistd.h>
E 44
#include <stdlib.h>
#include <string.h>
I 44
#include <unistd.h>
D 45
#else
extern	char *rindex();
extern char *calloc();
E 45
E 44
D 51
#endif
E 51
I 44

E 44
#include "dump.h"
E 32
E 29
I 26
#include "pathnames.h"
E 26

I 45
#ifndef SBOFF
#define SBOFF (SBLOCK * DEV_BSIZE)
#endif

E 45
int	notify = 0;	/* notify operator flag */
int	blockswritten = 0;	/* number of blocks written on current tape */
int	tapeno = 0;	/* current tape number */
D 11
int	density = 160;	/* density in 0.1" units */
E 11
I 11
int	density = 0;	/* density in bytes/0.1" */
int	ntrec = NTREC;	/* # tape blocks in each tape record */
int	cartridge = 0;	/* Assume non-cartridge tape */
I 25
long	dev_bsize = 1;	/* recalculated below */
I 30
long	blocksperfile;	/* output blocks per file */
I 36
char	*host = NULL;	/* remote host (if any) */
E 36
E 30
E 25
E 11
I 7
D 44
#ifdef RDUMP
D 36
char	*host;
E 36
I 29
int	rmthost();
E 29
#endif
E 44
I 21
D 31
int	anydskipped;	/* set true in mark() if any directories are skipped */
			/* this lets us avoid map pass 2 in some cases */
E 31
E 21
E 7

I 45
D 51
static long numarg __P((int, char *, long, long, int *, char ***));
static __dead void missingarg __P((int, char *));
E 51
I 51
static long numarg __P((char *, long, long));
static void obsolete __P((int *, char **[]));
static void usage __P((void));
E 51

E 45
I 44
int
E 44
main(argc, argv)
D 31
	int	argc;
	char	*argv[];
E 31
I 31
	int argc;
D 32
	char *argv[];
E 32
I 32
D 51
	char **argv;
E 51
I 51
	char *argv[];
E 51
E 32
E 31
{
D 31
	char		*arg;
D 5
	register	i;
E 5
I 5
D 18
	int		i;
E 18
I 18
	int		bflag = 0, i;
E 18
E 5
	float		fetapes;
	register	struct	fstab	*dt;
E 31
I 31
	register ino_t ino;
D 33
	register long bits; 
E 33
I 33
	register int dirty; 
E 33
	register struct dinode *dp;
	register struct	fstab *dt;
	register char *map;
D 51
	register char *cp;
E 51
I 51
	register int ch;
E 51
D 41
	int i, anydirskipped, bflag = 0;
E 41
I 41
D 45
	int i, anydirskipped, bflag = 0, Tflag = 0;
E 41
	float fetapes;
E 45
I 45
	int i, anydirskipped, bflag = 0, Tflag = 0, honorlevel = 1;
E 45
	ino_t maxino;
E 31

I 36
	spcl.c_date = 0;
E 36
D 41
	time(&(spcl.c_date));
E 41
I 41
D 45
	(void) time((time_t *) &(spcl.c_date));
E 45
I 45
	(void)time((time_t *)&spcl.c_date);
E 45
E 41

D 11
	tsize = 2300L*12L*10L;
E 11
I 11
	tsize = 0;	/* Default later, based on 'c' option for cart tapes */
E 11
D 27
	tape = TAPE;
	disk = DISK;
E 27
I 27
	tape = _PATH_DEFTAPE;
D 31
	disk = _PATH_DEFDISK;
E 27
D 26
	increm = NINCREM;
I 13
	temp = TEMP;
E 26
I 26
	increm = _PATH_DUMPDATES;
E 31
I 31
	dumpdates = _PATH_DUMPDATES;
E 31
	temp = _PATH_DTMP;
E 26
E 13
D 5

E 5
I 5
D 29
	if (TP_BSIZE / DEV_BSIZE == 0 || TP_BSIZE % DEV_BSIZE != 0) {
		msg("TP_BSIZE must be a multiple of DEV_BSIZE\n");
		dumpabort();
	}
E 29
I 29
	if (TP_BSIZE / DEV_BSIZE == 0 || TP_BSIZE % DEV_BSIZE != 0)
		quit("TP_BSIZE must be a multiple of DEV_BSIZE\n");
E 29
E 5
D 31
	incno = '9';
	uflag = 0;
	arg = "u";
I 7
D 8
#ifdef RDUMP
	if (argc < 2) {
		printf("usage: rdump machine ");
		Exit(X_ABORT);
	}
	host = argv[1];
	argv++, argc--;
	if (rmthost(host) == 0)
		Exit(X_ABORT);
#endif
E 8
E 7
	if(argc > 1) {
		argv++;
		argc--;
		arg = *argv;
		if (*arg == '-')
			argc++;
	}
	while(*arg)
	switch (*arg++) {
I 2
	case 'w':
		lastdump('w');		/* tell us only what has to be done */
		exit(0);
		break;
E 2
	case 'W':			/* what to do */
D 2
		lastdump();
E 2
I 2
		lastdump('W');		/* tell us the current state of what has been done */
E 2
D 13
		exit(0);		/* do nothing else */
		break;

	case 'J':			/* update old to new */
		o_nconvert();
E 13
		exit(0);		/* do nothing else */
		break;
E 31
I 31
	level = '0';
I 48
D 51
	if (argc == 1) {
		(void) fprintf(stderr, "Must specify a key.\n");
		Exit(X_ABORT);
	}
E 48
	argv++;
	argc -= 2;
D 49
	for (cp = *argv++; *cp; cp++) {
E 49
I 49
	for (cp = *argv++; cp != NULL && *cp != '\0'; cp++) {
E 49
		switch (*cp) {
		case '-':
E 51
I 51

	if (argc < 2)
		usage();

	obsolete(&argc, &argv);
	while ((ch = getopt(argc, argv, "0123456789B:b:cd:f:h:ns:T:uWw")) != -1)
		switch (ch) {
		/* dump level */
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			level = ch;
E 51
D 45
			continue;
E 45
I 45
			break;
E 45
E 31

D 31
	case 'f':			/* output file */
		if(argc > 1) {
			argv++;
			argc--;
			tape = *argv;
		}
		break;
E 31
I 31
D 51
		case 'w':
			lastdump('w');	/* tell us only what has to be done */
D 41
			exit(0);
E 41
I 41
D 44
			(void) exit(0);
E 44
I 44
			exit(0);
E 51
I 51
		case 'B':		/* blocks per output file */
			blocksperfile = numarg("blocks per file", 1L, 0L);
			break;
E 51
E 44
E 41
E 31

D 31
	case 'd':			/* density, in bits per inch */
		if (argc > 1) {
			argv++;
E 31
I 31
D 51
		case 'W':		/* what to do */
			lastdump('W');	/* tell us state of what is done */
D 41
			exit(0);	/* do nothing else */
E 41
I 41
D 44
			(void) exit(0);	/* do nothing else */
E 44
I 44
			exit(0);	/* do nothing else */
E 51
I 51
		case 'b':		/* blocks per tape write */
			ntrec = numarg("blocks per write", 1L, 1000L);
			break;
E 51
E 44
E 41

D 51
		case 'f':		/* output file */
			if (argc < 1)
D 45
				break;
E 45
I 45
				missingarg('f', "output file");
E 45
			tape = *argv++;
E 31
			argc--;
E 51
I 51
		case 'c':		/* Tape is cart. not 9-track */
			cartridge = 1;
E 51
I 31
D 45
			continue;
E 45
I 45
			break;
E 45

		case 'd':		/* density, in bits per inch */
D 45
			if (argc < 1)
				break;
E 31
			density = atoi(*argv) / 10;
I 31
			if (density < 1) {
D 41
				fprintf(stderr, "bad density \"%s\"\n", *argv);
E 41
I 41
				(void) fprintf(stderr, "bad density \"%s\"\n",
				    *argv);
E 41
				Exit(X_ABORT);
			}
			argc--;
			argv++;
E 45
I 45
D 51
			density = numarg('d', "density",
			    10L, 327670L, &argc, &argv) / 10;
E 51
I 51
			density = numarg("density", 10L, 327670L) / 10;
E 51
E 45
E 31
I 18
			if (density >= 625 && !bflag)
				ntrec = HIGHDENSITYTREC;
E 18
D 31
		}
		break;
E 31
I 31
D 45
			continue;
E 45
I 45
			break;
E 45
E 31

I 51
		case 'f':		/* output file */
			tape = optarg;
			break;

		case 'h':
			honorlevel = numarg("honor level", 0L, 10L);
			break;

		case 'n':		/* notify operators */
			notify = 1;
			break;

E 51
D 31
	case 's':			/* tape size, feet */
		if(argc > 1) {
			argv++;
			argc--;
E 31
I 31
		case 's':		/* tape size, feet */
D 45
			if (argc < 1)
				break;
E 31
			tsize = atol(*argv);
D 31
			tsize *= 12L*10L;
		}
		break;

I 11
	case 'b':			/* blocks per tape write */
		if(argc > 1) {
			argv++;
E 31
I 31
			if (tsize < 1) {
D 41
				fprintf(stderr, "bad size \"%s\"\n", *argv);
E 41
I 41
				(void) fprintf(stderr, "bad size \"%s\"\n",
				    *argv);
E 41
				Exit(X_ABORT);
			}
E 31
			argc--;
I 31
			argv++;
			tsize *= 12 * 10;
			continue;
E 45
I 45
D 51
			tsize = numarg('s', "size",
			    1L, 0L, &argc, &argv) * 12 * 10;
E 51
I 51
			tsize = numarg("tape size", 1L, 0L) * 12 * 10;
E 51
			break;
E 45

I 41
		case 'T':		/* time of last dump */
D 51
			if (argc < 1)
D 45
				break;
E 45
I 45
				missingarg('T', "time of last dump");
E 45
			spcl.c_ddate = unctime(*argv);
E 51
I 51
			spcl.c_ddate = unctime(optarg);
E 51
			if (spcl.c_ddate < 0) {
D 45
				(void) fprintf(stderr, "bad time \"%s\"\n",
E 45
I 45
				(void)fprintf(stderr, "bad time \"%s\"\n",
E 45
D 51
				    *argv);
E 51
I 51
				    optarg);
E 51
D 45
				Exit(X_ABORT);
E 45
I 45
				exit(X_ABORT);
E 45
			}
D 45
			Tflag++;
E 45
I 45
			Tflag = 1;
E 45
			lastlevel = '?';
D 51
			argc--;
			argv++;
E 51
D 45
			continue;
E 45
I 45
			break;
E 45

E 41
D 51
		case 'b':		/* blocks per tape write */
D 45
			if (argc < 1)
				break;
E 31
I 18
			bflag++;
E 18
D 33
			ntrec = atol(*argv);
E 33
I 33
			ntrec = atoi(*argv);
E 33
I 30
D 31
			if (ntrec <= 0) {
				fprintf(stderr,
				    "bad number of blocks per write \"%s\"\n",
				    *arg);
E 31
I 31
			if (ntrec < 1) {
D 41
				fprintf(stderr, "%s \"%s\"\n",
E 41
I 41
				(void) fprintf(stderr, "%s \"%s\"\n",
E 41
				    "bad number of blocks per write ", *argv);
E 31
				Exit(X_ABORT);
			}
E 30
D 31
		}
		break;

I 30
	case 'B':			/* blocks per output file */
		if(argc > 1) {
			argv++;
E 31
			argc--;
I 31
			argv++;
			continue;
E 45
I 45
			ntrec = numarg('b', "number of blocks per write",
			    1L, 1000L, &argc, &argv);
			break;
E 45

		case 'B':		/* blocks per output file */
D 45
			if (argc < 1)
				break;
E 31
			blocksperfile = atol(*argv);
D 31
		}
		break;
E 31
I 31
			if (blocksperfile < 1) {
D 41
				fprintf(stderr, "%s \"%s\"\n",
E 41
I 41
				(void) fprintf(stderr, "%s \"%s\"\n",
E 41
				    "bad number of blocks per file ", *argv);
				Exit(X_ABORT);
			}
			argc--;
			argv++;
			continue;
E 45
I 45
			blocksperfile = numarg('B', "number of blocks per file",
			    1L, 0L, &argc, &argv);
			break;
E 45
E 31

E 30
D 31
	case 'c':			/* Tape is cart. not 9-track */
		cartridge++;
		break;
E 31
I 31
		case 'c':		/* Tape is cart. not 9-track */
D 45
			cartridge++;
			continue;
E 45
I 45
			cartridge = 1;
			break;
E 45
E 31

E 11
D 31
	case '0':			/* dump level */
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		incno = arg[-1];
		break;
E 31
I 31
D 45
		case '0':		/* dump level */
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
E 45
I 45
		/* dump level */
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
E 45
			level = *cp;
D 45
			continue;
E 45
I 45
			break;
E 45
E 31

E 51
D 31
	case 'u':			/* update /etc/dumpdates */
		uflag++;
		break;
E 31
I 31
		case 'u':		/* update /etc/dumpdates */
D 45
			uflag++;
			continue;
E 45
I 45
			uflag = 1;
			break;
E 45
E 31

D 31
	case 'n':			/* notify operators */
		notify++;
		break;
E 31
I 31
D 51
		case 'n':		/* notify operators */
D 45
			notify++;
			continue;
E 45
I 45
			notify = 1;
			break;
E 51
I 51
		case 'W':		/* what to do */
		case 'w':
			lastdump(ch);
			exit(0);	/* do nothing else */
E 51
E 45
E 31

I 45
D 51
		case 'h':
			honorlevel = numarg('h', "honor level",
			    0L, 10L, &argc, &argv);
			break;

E 51
E 45
D 31
	default:
D 12
		printf("bad key '%c%'\n", arg[-1]);
E 12
I 12
D 30
		fprintf(stderr, "bad key '%c%'\n", arg[-1]);
E 30
I 30
		fprintf(stderr, "bad key '%c'\n", arg[-1]);
E 31
I 31
		default:
D 41
			fprintf(stderr, "bad key '%c'\n", *cp);
E 41
I 41
D 45
			(void) fprintf(stderr, "bad key '%c'\n", *cp);
E 41
			Exit(X_ABORT);
E 45
I 45
D 51
			(void)fprintf(stderr, "bad key '%c'\n", *cp);
			exit(X_ABORT);
E 51
I 51
			usage();
E 51
E 45
		}
D 41
		fprintf(stderr, "missing argument to '%c'\n", *cp);
E 41
I 41
D 45
		(void) fprintf(stderr, "missing argument to '%c'\n", *cp);
E 41
E 31
E 30
E 12
		Exit(X_ABORT);
E 45
D 51
	}
E 51
I 51
	argc -= optind;
	argv += optind;

E 51
D 31
	if(argc > 1) {
		argv++;
E 31
I 31
	if (argc < 1) {
D 41
		fprintf(stderr, "Must specify disk or filesystem\n");
E 41
I 41
D 45
		(void) fprintf(stderr, "Must specify disk or filesystem\n");
E 41
		Exit(X_ABORT);
	} else {
		disk = *argv++;
E 31
		argc--;
E 45
I 45
		(void)fprintf(stderr, "Must specify disk or filesystem\n");
		exit(X_ABORT);
E 45
D 31
		disk = *argv;
E 31
	}
I 45
	disk = *argv++;
	argc--;
E 45
I 31
	if (argc >= 1) {
D 41
		fprintf(stderr, "Unknown arguments to dump:");
E 41
I 41
D 45
		(void) fprintf(stderr, "Unknown arguments to dump:");
E 45
I 45
		(void)fprintf(stderr, "Unknown arguments to dump:");
E 45
E 41
		while (argc--)
D 41
			fprintf(stderr, " %s", *argv++);
		fprintf(stderr, "\n");
E 41
I 41
D 45
			(void) fprintf(stderr, " %s", *argv++);
		(void) fprintf(stderr, "\n");
E 41
		Exit(X_ABORT);
E 45
I 45
			(void)fprintf(stderr, " %s", *argv++);
		(void)fprintf(stderr, "\n");
		exit(X_ABORT);
E 45
	}
I 41
	if (Tflag && uflag) {
D 45
	        (void) fprintf(stderr,
E 45
I 45
	        (void)fprintf(stderr,
E 45
		    "You cannot use the T and u flags together.\n");
D 45
		Exit(X_ABORT);
E 45
I 45
		exit(X_ABORT);
E 45
	}
E 41
E 31
I 12
	if (strcmp(tape, "-") == 0) {
		pipeout++;
		tape = "standard output";
	}
E 12
I 11

D 30
	/*
	 * Determine how to default tape size and density
	 *
	 *         	density				tape size
	 * 9-track	1600 bpi (160 bytes/.1")	2300 ft.
	 * 9-track	6250 bpi (625 bytes/.1")	2300 ft.
D 16
	 * cartridge	8000 bpi (100 bytes/.1")	4000 ft. (450*9 - slop)
E 16
I 16
 	 * cartridge	8000 bpi (100 bytes/.1")	1700 ft. (450*4 - slop)
E 16
	 */
	if (density == 0)
		density = cartridge ? 100 : 160;
	if (tsize == 0)
D 16
		tsize = cartridge ? 4000L*120L : 2300L*120L;
E 16
I 16
 		tsize = cartridge ? 1700L*120L : 2300L*120L;
E 30
I 30
	if (blocksperfile)
		blocksperfile = blocksperfile / ntrec * ntrec; /* round down */
	else {
		/*
		 * Determine how to default tape size and density
		 *
		 *         	density				tape size
		 * 9-track	1600 bpi (160 bytes/.1")	2300 ft.
		 * 9-track	6250 bpi (625 bytes/.1")	2300 ft.
		 * cartridge	8000 bpi (100 bytes/.1")	1700 ft.
		 *						(450*4 - slop)
		 */
		if (density == 0)
			density = cartridge ? 100 : 160;
		if (tsize == 0)
			tsize = cartridge ? 1700L*120L : 2300L*120L;
	}
E 30
E 16

I 36
D 50
	if (index(tape, ':')) {
E 50
I 50
	if (strchr(tape, ':')) {
E 50
		host = tape;
D 50
		tape = index(host, ':');
E 50
I 50
		tape = strchr(host, ':');
E 50
D 45
		*tape++ = 0;
E 45
I 45
		*tape++ = '\0';
E 45
E 36
E 11
D 8

E 8
I 8
#ifdef RDUMP
D 36
	{ char *index();
	  host = tape;
	  tape = index(host, ':');
	  if (tape == 0) {
D 22
		msg("need keyletter ``f'' and device ``host:tape''");
E 22
I 22
		msg("need keyletter ``f'' and device ``host:tape''\n");
E 22
		exit(1);
	  }
	  *tape++ = 0;
	  if (rmthost(host) == 0)
E 36
I 36
		if (rmthost(host) == 0)
D 41
			exit(X_ABORT);
E 41
I 41
D 44
			(void) exit(X_ABORT);
E 44
I 44
			exit(X_ABORT);
E 44
E 41
#else
D 41
		fprintf(stderr, "remote dump not enabled\n");
E 36
		exit(X_ABORT);
E 41
I 41
D 45
		(void) fprintf(stderr, "remote dump not enabled\n");
E 45
I 45
		(void)fprintf(stderr, "remote dump not enabled\n");
E 45
D 44
		(void) exit(X_ABORT);
E 44
I 44
		exit(X_ABORT);
E 44
E 41
I 36
#endif
E 36
	}
I 23
D 41
	setuid(getuid());	/* rmthost() is the only reason to be setuid */
E 41
I 41
D 45
	(void) setuid(getuid()); /* rmthost() is the only reason to be setuid */
E 45
I 45
	(void)setuid(getuid()); /* rmthost() is the only reason to be setuid */
E 45
E 41
E 23
D 36
#endif
E 36
I 36

E 36
E 8
D 30
	if (signal(SIGHUP, sighup) == SIG_IGN)
		signal(SIGHUP, SIG_IGN);
	if (signal(SIGTRAP, sigtrap) == SIG_IGN)
		signal(SIGTRAP, SIG_IGN);
	if (signal(SIGFPE, sigfpe) == SIG_IGN)
		signal(SIGFPE, SIG_IGN);
	if (signal(SIGBUS, sigbus) == SIG_IGN)
		signal(SIGBUS, SIG_IGN);
	if (signal(SIGSEGV, sigsegv) == SIG_IGN)
		signal(SIGSEGV, SIG_IGN);
	if (signal(SIGTERM, sigterm) == SIG_IGN)
		signal(SIGTERM, SIG_IGN);
E 30
I 30
	if (signal(SIGHUP, SIG_IGN) != SIG_IGN)
D 43
		signal(SIGHUP, sighup);
E 43
I 43
		signal(SIGHUP, sig);
E 43
	if (signal(SIGTRAP, SIG_IGN) != SIG_IGN)
D 43
		signal(SIGTRAP, sigtrap);
E 43
I 43
		signal(SIGTRAP, sig);
E 43
	if (signal(SIGFPE, SIG_IGN) != SIG_IGN)
D 43
		signal(SIGFPE, sigfpe);
E 43
I 43
		signal(SIGFPE, sig);
E 43
	if (signal(SIGBUS, SIG_IGN) != SIG_IGN)
D 43
		signal(SIGBUS, sigbus);
E 43
I 43
		signal(SIGBUS, sig);
E 43
	if (signal(SIGSEGV, SIG_IGN) != SIG_IGN)
D 43
		signal(SIGSEGV, sigsegv);
E 43
I 43
		signal(SIGSEGV, sig);
E 43
	if (signal(SIGTERM, SIG_IGN) != SIG_IGN)
D 43
		signal(SIGTERM, sigterm);
E 43
I 43
		signal(SIGTERM, sig);
E 43
E 30
D 36
	

E 36
	if (signal(SIGINT, interrupt) == SIG_IGN)
		signal(SIGINT, SIG_IGN);

	set_operators();	/* /etc/group snarfed */
	getfstab();		/* /etc/fstab snarfed */
	/*
	 *	disk can be either the full special file name,
	 *	the suffix of the special file name,
	 *	the special name missing the leading '/',
	 *	the file system name with or without the leading '/'.
	 */
	dt = fstabsearch(disk);
D 24
	if (dt != 0)
E 24
I 24
D 45
	if (dt != 0) {
E 45
I 45
	if (dt != NULL) {
E 45
E 24
		disk = rawname(dt->fs_spec);
I 24
D 41
		strncpy(spcl.c_dev, dt->fs_spec, NAMELEN);
		strncpy(spcl.c_filesys, dt->fs_file, NAMELEN);
E 41
I 41
D 45
		(void) strncpy(spcl.c_dev, dt->fs_spec, NAMELEN);
		(void) strncpy(spcl.c_filesys, dt->fs_file, NAMELEN);
E 45
I 45
		(void)strncpy(spcl.c_dev, dt->fs_spec, NAMELEN);
		(void)strncpy(spcl.c_filesys, dt->fs_file, NAMELEN);
E 45
E 41
	} else {
D 41
		strncpy(spcl.c_dev, disk, NAMELEN);
		strncpy(spcl.c_filesys, "an unlisted file system", NAMELEN);
E 41
I 41
D 45
		(void) strncpy(spcl.c_dev, disk, NAMELEN);
		(void) strncpy(spcl.c_filesys, "an unlisted file system",
E 45
I 45
		(void)strncpy(spcl.c_dev, disk, NAMELEN);
		(void)strncpy(spcl.c_filesys, "an unlisted file system",
E 45
		    NAMELEN);
E 41
	}
D 41
	strcpy(spcl.c_label, "none");
	gethostname(spcl.c_host, NAMELEN);
E 41
I 41
D 45
	(void) strcpy(spcl.c_label, "none");
	(void) gethostname(spcl.c_host, NAMELEN);
E 45
I 45
	(void)strcpy(spcl.c_label, "none");
	(void)gethostname(spcl.c_host, NAMELEN);
E 45
E 41
D 31
	spcl.c_level = incno - '0';
E 31
I 31
	spcl.c_level = level - '0';
E 31
	spcl.c_type = TS_TAPE;
E 24
D 31
	getitime();		/* /etc/dumpdates snarfed */
E 31
I 31
D 41
	getdumptime();		/* /etc/dumpdates snarfed */
E 41
I 41
	if (!Tflag)
	        getdumptime();		/* /etc/dumpdates snarfed */
E 41
E 31

D 31
	msg("Date of this level %c dump: %s\n", incno, prdate(spcl.c_date));
D 14
	msg("Date of last level %c dump: %s\n", incno, prdate(spcl.c_ddate));
E 14
I 14
 	msg("Date of last level %c dump: %s\n",
		lastincno, prdate(spcl.c_ddate));
E 31
I 31
	msg("Date of this level %c dump: %s", level,
		spcl.c_date == 0 ? "the epoch\n" : ctime(&spcl.c_date));
 	msg("Date of last level %c dump: %s", lastlevel,
		spcl.c_ddate == 0 ? "the epoch\n" : ctime(&spcl.c_ddate));
E 31
E 14
	msg("Dumping %s ", disk);
D 45
	if (dt != 0)
E 45
I 45
	if (dt != NULL)
E 45
		msgtail("(%s) ", dt->fs_file);
I 7
D 8
#ifdef RDUMP
E 8
D 9
	msgtail("to %s", tape);
E 9
I 9
D 10
	msgtail("to %s\n", tape);
E 10
E 9
I 8
D 36
#ifdef RDUMP
E 8
D 10
	msgtail(" on host %s\n", host);
E 10
I 10
	msgtail("to %s on host %s\n", tape, host);
#else
	msgtail("to %s\n", tape);
E 10
D 8
#else
E 7
	msgtail("to %s\n", tape);
E 8
I 7
#endif
E 36
I 36
	if (host)
		msgtail("to %s on host %s\n", tape, host);
	else
		msgtail("to %s\n", tape);
E 36
E 7

D 31
	fi = open(disk, 0);
	if (fi < 0) {
E 31
I 31
	if ((diskfd = open(disk, O_RDONLY)) < 0) {
E 31
		msg("Cannot open %s\n", disk);
D 45
		Exit(X_ABORT);
E 45
I 45
		exit(X_ABORT);
E 45
	}
D 5
	CLR(clrmap);
	CLR(dirmap);
	CLR(nodmap);
E 5
D 31
	esize = 0;
I 5
	sblock = (struct fs *)buf;
E 31
	sync();
I 31
D 41
	sblock = (struct fs *)buf;
E 31
D 6
	bread(SBLOCK, sblock, MAXBSIZE);
E 6
I 6
D 25
	bread(SBLOCK, sblock, SBSIZE);
E 25
I 25
	bread(SBOFF, sblock, SBSIZE);
E 41
I 41
	sblock = (struct fs *)sblock_buf;
	bread(SBOFF, (char *) sblock, SBSIZE);
E 41
E 25
E 6
D 29
	if (sblock->fs_magic != FS_MAGIC) {
		msg("bad sblock magic number\n");
		dumpabort();
	}
E 29
I 29
	if (sblock->fs_magic != FS_MAGIC)
		quit("bad sblock magic number\n");
E 29
I 25
	dev_bsize = sblock->fs_fsize / fsbtodb(sblock, 1);
I 29
	dev_bshift = ffs(dev_bsize) - 1;
	if (dev_bsize != (1 << dev_bshift))
		quit("dev_bsize (%d) is not a power of 2", dev_bsize);
	tp_bshift = ffs(TP_BSIZE) - 1;
	if (TP_BSIZE != (1 << tp_bshift))
		quit("TP_BSIZE (%d) is not a power of 2", TP_BSIZE);
I 44
#ifdef FS_44INODEFMT
E 44
I 42
	if (sblock->fs_inodefmt >= FS_44INODEFMT)
		spcl.c_flags |= DR_NEWINODEFMT;
I 44
#endif
E 44
E 42
E 29
E 25
D 31
	msiz = roundup(howmany(sblock->fs_ipg * sblock->fs_ncg, NBBY),
E 31
I 31
D 45
	maxino = sblock->fs_ipg * sblock->fs_ncg - 1;
	mapsize = roundup(howmany(sblock->fs_ipg * sblock->fs_ncg, NBBY),
E 31
		TP_BSIZE);
E 45
I 45
	maxino = sblock->fs_ipg * sblock->fs_ncg;
	mapsize = roundup(howmany(maxino, NBBY), TP_BSIZE);
E 45
D 31
	clrmap = (char *)calloc(msiz, sizeof(char));
	dirmap = (char *)calloc(msiz, sizeof(char));
	nodmap = (char *)calloc(msiz, sizeof(char));
E 31
I 31
D 41
	usedinomap = (char *)calloc(mapsize, sizeof(char));
	dumpdirmap = (char *)calloc(mapsize, sizeof(char));
	dumpinomap = (char *)calloc(mapsize, sizeof(char));
E 41
I 41
	usedinomap = (char *)calloc((unsigned) mapsize, sizeof(char));
	dumpdirmap = (char *)calloc((unsigned) mapsize, sizeof(char));
	dumpinomap = (char *)calloc((unsigned) mapsize, sizeof(char));
E 41
	tapesize = 3 * (howmany(mapsize * sizeof(char), TP_BSIZE) + 1);
E 31
E 5

I 45
	nonodump = spcl.c_level < honorlevel;

E 45
I 21
D 31
	anydskipped = 0;
E 31
E 21
	msg("mapping (Pass I) [regular files]\n");
D 5
	pass(mark, (short *)NULL);		/* mark updates esize */
E 5
I 5
D 31
	pass(mark, (char *)NULL);		/* mark updates esize */
E 31
I 31
	anydirskipped = mapfiles(maxino, &tapesize);
E 31
E 5

D 21
	do {
E 21
I 21
D 31
	if (anydskipped) {
		do {
			msg("mapping (Pass II) [directories]\n");
			nadded = 0;
			pass(add, dirmap);
D 29
		} while(nadded);
E 29
I 29
		} while (nadded);
E 29
	} else				/* keep the operators happy */
E 21
		msg("mapping (Pass II) [directories]\n");
E 31
I 31
	msg("mapping (Pass II) [directories]\n");
	while (anydirskipped) {
		anydirskipped = mapdirs(maxino, &tapesize);
	}
E 31
D 21
		nadded = 0;
		pass(add, dirmap);
	} while(nadded);
E 21

D 31
	bmapest(clrmap);
	bmapest(nodmap);

E 31
D 11
	fetapes =
E 11
I 11
D 30
	if (cartridge) {
		/* Estimate number of tapes, assuming streaming stops at
		   the end of each block written, and not in mid-block.
		   Assume no erroneous blocks; this can be compensated for
		   with an artificially low tape size. */
		fetapes = 
E 11
D 5
		(	 esize		/* blocks */
D 4
			*BSIZE		/* bytes / block */
E 4
I 4
			*FSIZE		/* bytes / block */
E 4
			*(1.0/density)	/* 0.1" / byte */
E 5
I 5
		(	  esize		/* blocks */
I 11
			* TP_BSIZE	/* bytes/block */
			* (1.0/density)	/* 0.1" / byte */
		  +
			  esize		/* blocks */
			* (1.0/ntrec)	/* streaming-stops per block */
			* 15.48		/* 0.1" / streaming-stop */
		) * (1.0 / tsize );	/* tape / 0.1" */
	} else {
		/* Estimate number of tapes, for old fashioned 9-track tape */
		int tenthsperirg = (density == 625) ? 3 : 7;
		fetapes =
		(	  esize		/* blocks */
E 11
			* TP_BSIZE	/* bytes / block */
			* (1.0/density)	/* 0.1" / byte */
E 5
		  +
D 5
			 esize		/* blocks */
			*(1.0/NTREC)	/* IRG's / block */
			*7		/* 0.1" / IRG */
E 5
I 5
			  esize		/* blocks */
D 11
			* (1.0/NTREC)	/* IRG's / block */
E 11
I 11
			* (1.0/ntrec)	/* IRG's / block */
			* tenthsperirg	/* 0.1" / IRG */
E 11
D 15
			* 7		/* 0.1" / IRG */
E 15
E 5
D 11
		) * (1.0 / tsize )	/* tape / 0.1" */
	;
E 11
I 11
		) * (1.0 / tsize );	/* tape / 0.1" */
E 30
I 30
D 45
	if (pipeout)
E 45
I 45
	if (pipeout) {
E 45
D 31
		esize += 10;	/* 10 trailer blocks */
E 31
I 31
		tapesize += 10;	/* 10 trailer blocks */
E 31
D 45
	else {
E 45
I 45
		msg("estimated %ld tape blocks.\n", tapesize);
	} else {
		double fetapes;

E 45
		if (blocksperfile)
D 31
			fetapes = esize / blocksperfile;
E 31
I 31
D 35
			fetapes = tapesize / blocksperfile;
E 35
I 35
D 45
			fetapes = (float) tapesize / blocksperfile;
E 45
I 45
			fetapes = (double) tapesize / blocksperfile;
E 45
E 35
E 31
		else if (cartridge) {
			/* Estimate number of tapes, assuming streaming stops at
			   the end of each block written, and not in mid-block.
			   Assume no erroneous blocks; this can be compensated
			   for with an artificially low tape size. */
			fetapes = 
D 31
			(	  esize		/* blocks */
E 31
I 31
			(	  tapesize	/* blocks */
E 31
				* TP_BSIZE	/* bytes/block */
				* (1.0/density)	/* 0.1" / byte */
			  +
D 31
				  esize		/* blocks */
E 31
I 31
				  tapesize	/* blocks */
E 31
				* (1.0/ntrec)	/* streaming-stops per block */
				* 15.48		/* 0.1" / streaming-stop */
			) * (1.0 / tsize );	/* tape / 0.1" */
		} else {
			/* Estimate number of tapes, for old fashioned 9-track
			   tape */
			int tenthsperirg = (density == 625) ? 3 : 7;
			fetapes =
D 31
			(	  esize		/* blocks */
E 31
I 31
			(	  tapesize	/* blocks */
E 31
				* TP_BSIZE	/* bytes / block */
				* (1.0/density)	/* 0.1" / byte */
			  +
D 31
				  esize		/* blocks */
E 31
I 31
				  tapesize	/* blocks */
E 31
				* (1.0/ntrec)	/* IRG's / block */
				* tenthsperirg	/* 0.1" / IRG */
			) * (1.0 / tsize );	/* tape / 0.1" */
		}
		etapes = fetapes;		/* truncating assignment */
		etapes++;
D 31
		/* count the nodemap on each additional tape */
		for (i = 1; i < etapes; i++)
			bmapest(nodmap);
		esize += i + 10;	/* headers + 10 trailer blocks */
E 31
I 31
		/* count the dumped inodes map on each additional tape */
		tapesize += (etapes - 1) *
			(howmany(mapsize * sizeof(char), TP_BSIZE) + 1);
		tapesize += etapes + 10;	/* headers + 10 trailer blks */
E 31
E 30
D 45
	}
E 11
D 30
	etapes = fetapes;		/* truncating assignment */
	etapes++;
D 5
	/*
	 *	esize is typically about 5% too low; we frob it here
	 */
	esize += ((5*esize)/100);
E 5
I 5
	/* count the nodemap on each additional tape */
	for (i = 1; i < etapes; i++)
		bmapest(nodmap);
	esize += i + 10;	/* headers + 10 trailer blocks */
E 5
	msg("estimated %ld tape blocks on %3.2f tape(s).\n", esize, fetapes);
E 30
I 30
	if (pipeout)
D 31
		msg("estimated %ld tape blocks.\n", esize);
E 31
I 31
		msg("estimated %ld tape blocks.\n", tapesize);
E 31
	else
E 45
		msg("estimated %ld tape blocks on %3.2f tape(s).\n",
D 31
		    esize, fetapes);
E 31
I 31
		    tapesize, fetapes);
I 45
	}
E 45
E 31
E 30

I 11
D 41
	alloctape();			/* Allocate tape buffer */
E 41
I 41
	/*
D 45
	 * Allocate tape buffer
E 45
I 45
	 * Allocate tape buffer.
E 45
	 */
	if (!alloctape())
		quit("can't allocate tape buffers - try a smaller blocking factor.\n");
E 41

E 11
D 31
	otape();			/* bitmap is the first to tape write */
E 31
I 31
D 36
	startnewtape();
E 36
I 36
	startnewtape(1);
E 36
E 31
D 41
	time(&(tstart_writing));
E 41
I 41
D 45
	(void) time((time_t *)&(tstart_writing));
E 41
D 31
	bitmap(clrmap, TS_CLRI);
E 31
I 31
	dumpmap(usedinomap, TS_CLRI, maxino);
E 45
I 45
	(void)time((time_t *)&(tstart_writing));
	dumpmap(usedinomap, TS_CLRI, maxino - 1);
E 45
E 31

	msg("dumping (Pass III) [directories]\n");
D 17
	pass(dump, dirmap);
E 17
I 17
D 31
 	pass(dirdump, dirmap);
E 31
I 31
D 45
	for (map = dumpdirmap, ino = 0; ino < maxino; ) {
		if ((ino % NBBY) == 0)
E 45
I 45
	dirty = 0;		/* XXX just to get gcc to shut up */
	for (map = dumpdirmap, ino = 1; ino < maxino; ino++) {
		if (((ino - 1) % NBBY) == 0)	/* map is offset by 1 */
E 45
D 33
			bits = *map++;
E 33
I 33
			dirty = *map++;
E 33
		else
D 33
			bits >>= 1;
E 33
I 33
			dirty >>= 1;
E 33
D 45
		ino++;
E 45
D 33
		if ((bits & 1) == 0)
E 33
I 33
		if ((dirty & 1) == 0)
E 33
			continue;
		/*
		 * Skip directory inodes deleted and maybe reallocated
		 */
		dp = getino(ino);
		if ((dp->di_mode & IFMT) != IFDIR)
			continue;
D 41
		dumpino(dp, ino);
E 41
I 41
D 45
		(void) dumpino(dp, ino);
E 45
I 45
		(void)dumpino(dp, ino);
E 45
E 41
	}
E 31
E 17

	msg("dumping (Pass IV) [regular files]\n");
D 31
	pass(dump, nodmap);
E 31
I 31
D 45
	for (map = dumpinomap, ino = 0; ino < maxino; ) {
E 45
I 45
	for (map = dumpinomap, ino = 1; ino < maxino; ino++) {
E 45
I 44
		int mode;

E 44
D 45
		if ((ino % NBBY) == 0)
E 45
I 45
		if (((ino - 1) % NBBY) == 0)	/* map is offset by 1 */
E 45
D 33
			bits = *map++;
E 33
I 33
			dirty = *map++;
E 33
		else
D 33
			bits >>= 1;
E 33
I 33
			dirty >>= 1;
E 33
D 45
		ino++;
E 45
D 33
		if ((bits & 1) == 0)
E 33
I 33
		if ((dirty & 1) == 0)
E 33
			continue;
		/*
		 * Skip inodes deleted and reallocated as directories.
		 */
		dp = getino(ino);
D 44
		if ((dp->di_mode & IFMT) == IFDIR)
E 44
I 44
		mode = dp->di_mode & IFMT;
		if (mode == IFDIR)
E 44
			continue;
D 41
		dumpino(dp, ino);
E 41
I 41
D 45
		(void) dumpino(dp, ino);
E 45
I 45
		(void)dumpino(dp, ino);
E 45
E 41
	}
E 31

	spcl.c_type = TS_END;
D 5
	for(i=0; i<NTREC; i++)
E 5
I 5
D 7
	for(i = 0; i < NTREC; i++)
E 7
I 7
D 36
#ifndef RDUMP
E 36
D 11
	for(i=0; i<NTREC; i++)
E 11
I 11
D 31
	for(i=0; i<ntrec; i++)
E 11
E 7
E 5
		spclrec();
E 31
I 31
	for (i = 0; i < ntrec; i++)
D 45
		writeheader(maxino);
E 45
I 45
		writeheader(maxino - 1);
E 45
E 31
I 7
D 36
#endif
E 36
E 7
D 30
	msg("DUMP: %ld tape blocks on %d tape(s)\n",spcl.c_tapea,spcl.c_volume);
E 30
I 30
	if (pipeout)
		msg("DUMP: %ld tape blocks\n",spcl.c_tapea);
	else
		msg("DUMP: %ld tape blocks on %d volumes(s)\n",
		    spcl.c_tapea, spcl.c_volume);
E 30
D 36
	msg("DUMP IS DONE\n");

E 36
D 31
	putitime();
E 31
I 31
	putdumptime();
E 31
I 7
D 36
#ifndef RDUMP
E 7
D 12
	close(to);
E 12
I 12
	if (!pipeout) {
D 31
		close(to);
E 31
I 31
		close(tapefd);
E 31
D 28
		rewind();
E 28
I 28
		trewind();
E 28
	}
E 12
I 7
#else
D 31
	tflush(1);
E 31
I 31
	for (i = 0; i < ntrec; i++)
		writeheader(curino);
E 36
E 31
D 12
#endif
E 12
E 7
D 28
	rewind();
E 28
I 28
	trewind();
E 28
I 12
D 36
#endif
E 36
E 12
	broadcast("DUMP IS DONE!\7\7\n");
I 36
	msg("DUMP IS DONE\n");
E 36
	Exit(X_FINOK);
I 29
	/* NOTREACHED */
E 29
}

I 51
static void
usage()
{

	(void)fprintf(stderr, "usage: dump [-0123456789cnu] [-B records] [-b blocksize] [-d density] [-f file]\n            [-h level] [-s feet] [-T date] filesystem\n");
	(void)fprintf(stderr, "       dump [-W | -w]\n");
	exit(1);
}

E 51
I 45
/*
 * Pick up a numeric argument.  It must be nonnegative and in the given
 * range (except that a vmax of 0 means unlimited).
 */
static long
D 51
numarg(letter, meaning, vmin, vmax, pargc, pargv)
	int letter;
E 51
I 51
numarg(meaning, vmin, vmax)
E 51
	char *meaning;
	long vmin, vmax;
D 51
	int *pargc;
	char ***pargv;
E 51
{
D 51
	register char *p;
E 51
I 51
	char *p;
E 51
	long val;
D 51
	char *str;
E 51

D 51
	if (--*pargc < 0)
		missingarg(letter, meaning);
	str = *(*pargv)++;
	for (p = str; *p; p++)
		if (!isdigit(*p))
			goto bad;
	val = atol(str);
E 51
I 51
	val = strtol(optarg, &p, 10);
	if (*p)
		errx(1, "illegal %s -- %s", meaning, optarg);
E 51
	if (val < vmin || (vmax && val > vmax))
D 51
		goto bad;
E 51
I 51
		errx(1, "%s must be between %ld and %ld", meaning, vmin, vmax);
E 51
	return (val);
D 51

bad:
	(void)fprintf(stderr, "bad '%c' (%s) value \"%s\"\n",
	    letter, meaning, str);
	exit(X_ABORT);
E 51
}

D 51
static __dead void
missingarg(letter, meaning)
	int letter;
	char *meaning;
{

	(void)fprintf(stderr, "The '%c' flag (%s) requires an argument\n",
	    letter, meaning);
	exit(X_ABORT);
}

E 51
E 45
D 29
int	sighup(){	msg("SIGHUP()  try rewriting\n"); sigAbort();}
int	sigtrap(){	msg("SIGTRAP()  try rewriting\n"); sigAbort();}
int	sigfpe(){	msg("SIGFPE()  try rewriting\n"); sigAbort();}
int	sigbus(){	msg("SIGBUS()  try rewriting\n"); sigAbort();}
int	sigsegv(){	msg("SIGSEGV()  ABORTING!\n"); abort();}
int	sigalrm(){	msg("SIGALRM()  try rewriting\n"); sigAbort();}
int	sigterm(){	msg("SIGTERM()  try rewriting\n"); sigAbort();}

E 29
I 29
void
E 29
D 43
sigAbort()
E 43
I 43
sig(signo)
	int signo;
E 43
{
I 12
D 29
	if (pipeout) {
		msg("Unknown signal, cannot recover\n");
		dumpabort();
	}
E 29
I 29
D 43
	if (pipeout)
		quit("Unknown signal, cannot recover\n");
E 29
E 12
	msg("Rewriting attempted as response to unknown signal.\n");
D 41
	fflush(stderr);
	fflush(stdout);
E 41
I 41
	(void) fflush(stderr);
	(void) fflush(stdout);
E 41
	close_rewind();
D 41
	exit(X_REWRITE);
E 41
I 41
	(void) exit(X_REWRITE);
E 43
I 43
	switch(signo) {
	case SIGALRM:
	case SIGBUS:
	case SIGFPE:
	case SIGHUP:
	case SIGTERM:
	case SIGTRAP:
		if (pipeout)
			quit("Signal on pipe: cannot recover\n");
		msg("Rewriting attempted as response to unknown signal.\n");
D 45
		(void) fflush(stderr);
		(void) fflush(stdout);
E 45
I 45
		(void)fflush(stderr);
		(void)fflush(stdout);
E 45
		close_rewind();
D 44
		(void) exit(X_REWRITE);
E 44
I 44
		exit(X_REWRITE);
E 44
		/* NOTREACHED */
	case SIGSEGV:
		msg("SIGSEGV: ABORTING!\n");
D 45
		(void) signal(SIGSEGV, SIG_DFL);
		(void) kill(0, SIGSEGV);
E 45
I 45
		(void)signal(SIGSEGV, SIG_DFL);
		(void)kill(0, SIGSEGV);
E 45
		/* NOTREACHED */
	}
E 43
E 41
}
D 43

D 29
char *rawname(cp)
E 29
I 29
void	sighup(){	msg("SIGHUP()  try rewriting\n"); sigAbort();}
void	sigtrap(){	msg("SIGTRAP()  try rewriting\n"); sigAbort();}
void	sigfpe(){	msg("SIGFPE()  try rewriting\n"); sigAbort();}
void	sigbus(){	msg("SIGBUS()  try rewriting\n"); sigAbort();}
void	sigsegv(){	msg("SIGSEGV()  ABORTING!\n"); abort();}
void	sigalrm(){	msg("SIGALRM()  try rewriting\n"); sigAbort();}
void	sigterm(){	msg("SIGTERM()  try rewriting\n"); sigAbort();}
E 43

char *
rawname(cp)
E 29
	char *cp;
{
D 47
	static char rawbuf[32];
E 47
I 47
	static char rawbuf[MAXPATHLEN];
E 47
I 3
D 44
	char *rindex();
E 44
E 3
D 50
	char *dp = rindex(cp, '/');
E 50
I 50
	char *dp = strrchr(cp, '/');
E 50

D 45
	if (dp == 0)
		return (0);
	*dp = 0;
D 41
	strcpy(rawbuf, cp);
E 41
I 41
	(void) strcpy(rawbuf, cp);
E 45
I 45
	if (dp == NULL)
		return (NULL);
	*dp = '\0';
	(void)strcpy(rawbuf, cp);
E 45
E 41
	*dp = '/';
D 41
	strcat(rawbuf, "/r");
	strcat(rawbuf, dp+1);
E 41
I 41
D 45
	(void) strcat(rawbuf, "/r");
	(void) strcat(rawbuf, dp+1);
E 45
I 45
	(void)strcat(rawbuf, "/r");
	(void)strcat(rawbuf, dp + 1);
E 45
E 41
	return (rawbuf);
}
I 37

D 51
#ifdef sunos
D 45
char *
E 45
I 45
const char *
E 45
strerror(errnum)
	int errnum;
E 51
I 51
/*
 * obsolete --
 *	Change set of key letters and ordered arguments into something
 *	getopt(3) will like.
 */
static void
obsolete(argcp, argvp)
	int *argcp;
	char **argvp[];
E 51
{
D 51
	extern int sys_nerr;
D 45
	extern char *sys_errlist[];
E 45
I 45
	extern const char *const sys_errlist[];
E 51
I 51
	int argc, flags;
	char *ap, **argv, *flagsp, **nargv, *p;
E 51
E 45

D 45
	if (errnum < sys_nerr) {
		return(sys_errlist[errnum]);
	} else {
		return("bogus errno in strerror");
	}
E 45
I 45
D 51
	if (errnum < sys_nerr)
		return (sys_errlist[errnum]);
	else
		return ("bogus errno in strerror");
E 51
I 51
	/* Setup. */
	argv = *argvp;
	argc = *argcp;

	/* Return if no arguments or first argument has leading dash. */
	ap = argv[1];
	if (argc == 1 || *ap == '-')
		return;

	/* Allocate space for new arguments. */
	if ((*argvp = nargv = malloc((argc + 1) * sizeof(char *))) == NULL ||
	    (p = flagsp = malloc(strlen(ap) + 2)) == NULL)
		err(1, NULL);

	*nargv++ = *argv;
	argv += 2;

	for (flags = 0; *ap; ++ap) {
		switch (*ap) {
		case 'B':
		case 'b':
		case 'd':
		case 'f':
		case 'h':
		case 's':
		case 'T':
			if (*argv == NULL) {
				warnx("option requires an argument -- %c", *ap);
				usage();
			}
			if ((nargv[0] = malloc(strlen(*argv) + 2 + 1)) == NULL)
				err(1, NULL);
			nargv[0][0] = '-';
			nargv[0][1] = *ap;
			(void)strcpy(&nargv[0][2], *argv);
			++argv;
			++nargv;
			break;
		default:
			if (!flags) {
				*p++ = '-';
				flags = 1;
			}
			*p++ = *ap;
			break;
		}
	}

	/* Terminate flags. */
	if (flags) {
		*p = '\0';
		*nargv++ = flagsp;
	}

	/* Copy remaining arguments. */
	while (*nargv++ = *argv++);

	/* Update argument count. */
	*argcp = nargv - *argvp - 1;
E 51
E 45
}
D 51
#endif
E 51
E 37
E 1
