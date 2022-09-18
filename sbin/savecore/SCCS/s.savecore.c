h61035
s 00002/00002/00621
d D 8.5 95/04/28 11:18:16 bostic 61 60
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00001/00001/00622
d D 8.4 95/04/24 16:01:17 mckusick 60 59
c bad getopt string
e
s 00005/00001/00618
d D 8.3 94/01/02 12:57:09 bostic 59 58
c Use lstat() when poking around in /dev.  The routine is converting a
c device number to a name (seems like there are very few cases where stat()
c is preferred over lstat()).  Exit with a nice message if dumpdev is NODEV,
c for running diskless.
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00001/00001/00618
d D 8.2 93/11/24 15:12:46 hibler 58 57
c needed (dumpsize+vmunixsize) needs to be in 1k chunks not bytes
e
s 00005/00005/00614
d D 8.1 93/06/05 11:17:40 bostic 57 56
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00003/00607
d D 5.38 93/05/11 13:45:25 torek 56 55
c account for size of vmunix in minfree calculations
e
s 00001/00001/00609
d D 5.37 93/02/26 14:42:45 mckusick 55 54
c reasonable mode for vmunix
e
s 00001/00001/00609
d D 5.36 92/12/11 11:35:35 bostic 54 53
c Kirk wants the crash dump mode to be 644
e
s 00003/00002/00607
d D 5.35 92/12/03 19:33:11 bostic 53 52
c less chatty, please
e
s 00007/00005/00602
d D 5.34 92/12/03 18:52:13 bostic 52 51
c change system operand to -N, minor cleanups
e
s 00352/00354/00255
d D 5.33 92/12/03 17:55:58 bostic 51 50
c add z option for compression, lots of minor stuff
e
s 00006/00002/00603
d D 5.32 92/07/15 00:32:31 bostic 50 49
c fix va_start macro usage
e
s 00003/00002/00602
d D 5.31 92/06/23 13:40:34 bostic 49 48
c my fault -- dev_t is a u_long
e
s 00102/00050/00502
d D 5.30 92/06/19 17:51:22 bostic 48 47
c don't clear the dump if out of space, plus cleanup; from Craig Leres
e
s 00007/00008/00545
d D 5.29 92/06/03 10:38:44 mckusick 47 46
c proper use of off_t in lseek
e
s 00007/00019/00546
d D 5.28 92/02/18 05:28:24 torek 46 45
c remove unnecessary machine dependencies; lint
e
s 00001/00001/00564
d D 5.27 92/01/27 11:22:11 bostic 45 44
c statfs.f_fsize =>statfs.f_bsize
e
s 00001/00002/00564
d D 5.26 91/04/08 08:27:28 bostic 44 43
c savecore can print out the message as easily as /etc/rc
e
s 00040/00031/00526
d D 5.25 91/04/07 21:45:20 bostic 43 42
c use getopt(3); make "savecore -c" work
e
s 00001/00005/00556
d D 5.24 91/02/27 17:03:34 bostic 42 40
c ANSI fixes
e
s 00001/00001/00560
d R 5.24 91/02/26 16:01:46 bostic 41 40
c ANSI fix
e
s 00004/00000/00557
d D 5.23 91/02/09 19:41:24 william 40 39
c i386 system base address (must be a better way...)
e
s 00001/00011/00556
d D 5.22 90/06/01 16:29:13 bostic 39 38
c new copyright notice
e
s 00010/00016/00557
d D 5.21 90/03/22 19:55:56 mckusick 38 37
c use statfs instead of reading superblock to get space threshold
e
s 00023/00008/00550
d D 5.20 89/12/19 10:42:36 karels 37 36
c update bounds file if write fails on vmcore
e
s 00019/00013/00539
d D 5.19 89/08/21 22:09:55 karels 36 35
c need to read dumpsize from blockdev, more cleanups
e
s 00054/00036/00498
d D 5.18 89/08/20 15:20:06 karels 35 34
c read dump from raw device, not block; minor cleanups
e
s 00003/00003/00531
d D 5.17 89/07/07 18:51:22 root 34 33
c gotta fire the idiot who didn't finish this...
e
s 00004/00004/00530
d D 5.16 89/05/11 14:01:51 bostic 33 32
c file reorg, pathnames.h, paths.h
e
s 00009/00008/00525
d D 5.15 89/04/02 15:07:00 bostic 32 31
c add pathnames.h
e
s 00017/00006/00516
d D 5.14 88/10/31 16:17:36 bostic 31 30
c written by Michael Toy; add Berkeley specific copyright notice
e
s 00002/00002/00520
d D 5.13 87/10/22 10:45:31 bostic 30 29
c ANSI C; sprintf now returns an int.
e
s 00022/00012/00500
d D 5.12 87/03/29 16:23:38 karels 29 28
c I *like* newlines on messages; add -c to clear dump magic
e
s 00001/00001/00511
d D 5.11 87/02/23 17:40:07 mckusick 28 27
c convert SBLOCK to SBOFF; generalize use of dev_bsize
e
s 00008/00003/00504
d D 5.10 87/01/08 20:32:40 karels 27 26
c do it anyway!
e
s 00043/00066/00464
d D 5.9 86/10/13 15:12:03 sam 26 25
c add tahoe stuff; consolidate common code in log+Perror
e
s 00053/00005/00477
d D 5.8 86/05/26 22:10:21 karels 25 24
c show error messages on stderr too
e
s 00004/00027/00478
d D 5.7 86/05/12 18:30:20 eric 24 23
c eliminate shutdownlog in favor of syslog
e
s 00001/00003/00504
d D 5.6 86/05/12 17:45:28 eric 23 22
c shutdownlog subsumed into syslog (as LOG_AUTH)
e
s 00120/00153/00387
d D 5.5 86/02/18 17:06:25 sam 22 21
c lots of mickey-mouse things; use syslog; compress nlist checks 
c into an array and a loop; use symbolic constants for open, lseek, access;
e
s 00014/00006/00526
d D 5.4 86/01/30 19:47:30 karels 21 20
c use larger buffer for those of us with swap and crash
c on same disk
e
s 00003/00004/00529
d D 5.3 86/01/09 14:27:35 mckusick 20 19
c better calculation of freespace
e
s 00006/00002/00527
d D 5.2 85/09/08 13:59:52 bloom 19 18
c portability cleanup, allow to work with core dumps which terminate when they
c reach the end of the partition
e
s 00014/00002/00515
d D 5.1 85/06/04 16:47:02 dist 18 17
c Add copyright
e
s 00001/00002/00516
d D 4.15 85/06/03 09:36:25 karels 17 16
c can get dumptime from specified system now
e
s 00098/00027/00420
d D 4.14 84/07/17 16:40:12 ralph 16 15
c added -v option, works correctly when given alt. system name.
e
s 00001/00001/00446
d D 4.13 83/07/02 00:19:23 sam 15 14
c include fixes
e
s 00003/00003/00444
d D 4.12 83/05/03 20:53:12 sam 14 13
c fix name conflict with kernel
e
s 00004/00004/00443
d D 4.11 83/03/21 11:25:44 sam 13 12
c read dumpsize from dump image instead of memory
e
s 00053/00084/00394
d D 4.10 83/02/21 00:28:39 sam 12 11
c merge of mods from sun now that system is changed
e
s 00001/00070/00477
d D 4.9 82/10/24 16:04:59 mckusick 11 8
i 10 9
c merge in mods from matisse
e
s 00082/00025/00370
d D 4.7.1.2 82/10/24 15:51:14 mckusick 10 9
c fixes per ark
e
s 00000/00000/00395
d D 4.7.1.1 82/10/24 15:49:21 mckusick 9 7
c branch-place-holder
e
s 00097/00027/00368
d D 4.8 82/10/21 14:21:24 sam 8 7
c new super block format, check for string termination, & lots more
e
s 00011/00004/00384
d D 4.7 81/05/20 17:47:02 root 7 6
c fix to have 3 args but kludged: should read dump* from argv[2] instead of /dev/kmem if argc > 2
e
s 00008/00003/00380
d D 4.6 81/05/20 16:40:51 root 6 5
c debug code
e
s 00002/00006/00381
d D 4.5 81/05/14 18:15:31 root 5 4
c version mismatch is a warning
e
s 00200/00283/00187
d D 4.4 81/04/28 00:45:44 root 4 3
c major cleanup
e
s 00008/00003/00462
d D 4.3 81/04/14 19:17:10 root 3 2
c make it work!
e
s 00004/00001/00461
d D 4.2 81/04/03 12:59:42 root 2 1
c fix to not double-save dumps
e
s 00462/00000/00000
d D 4.1 81/04/02 21:47:07 root 1 0
c date and time created 81/04/02 21:47:07 by root
e
u
U
f b 
t
T
I 18
D 48
/*
D 25
 * Copyright (c) 1980 Regents of the University of California.
E 25
I 25
D 31
 * Copyright (c) 1980,1986 Regents of the University of California.
E 25
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 31
I 31
D 35
 * Copyright (c) 1980, 1986 The Regents of the University of California.
E 35
I 35
 * Copyright (c) 1980, 1986, 1989 The Regents of the University of California.
E 48
I 48
/*-
D 57
 * Copyright (c) 1986, 1992 The Regents of the University of California.
E 48
E 35
 * All rights reserved.
E 57
I 57
 * Copyright (c) 1986, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 57
 *
D 39
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 39
I 39
 * %sccs.include.redist.c%
E 39
E 31
 */

E 18
I 12
#ifndef lint
E 12
I 4
D 18
static	char *sccsid = "%W% (Berkeley) %E%";
I 12
#endif
E 18
I 18
D 57
char copyright[] =
D 25
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 25
I 25
D 31
"%Z% Copyright (c) 1980,1986 Regents of the University of California.\n\
E 31
I 31
D 35
"%Z% Copyright (c) 1980, 1986 The Regents of the University of California.\n\
E 35
I 35
D 48
"@(#) Copyright (c) 1980, 1986, 1989 The Regents of the University of California.\n\
E 48
I 48
"%Z% Copyright (c) 1986, 1992 The Regents of the University of California.\n\
E 48
E 35
E 31
E 25
 All rights reserved.\n";
E 57
I 57
static char copyright[] =
"%Z% Copyright (c) 1986, 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 57
D 31
#endif not lint
E 31
I 31
#endif /* not lint */
E 31

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 31
#endif not lint
E 31
I 31
#endif /* not lint */
E 31
E 18

E 12
E 4
I 1
D 42
/*
D 4
 *	%M%	%I%	%E%
 * savecore dirname
 *	Written by Michael Toy (UCB)
 *	Program meant to be called from the /etc/rc file for saving the
 * dump of a crashed system.  If the core file has not already been saved
 * then save it in dirname (if there is at least minfree blocks on the
 * device the directory is on.)
 *	1) Make certain "dirname" exists
 *	2) Get dumpdev and dumplo from vmunix/kmem
 *	3) Find dump device name get time from core image
 *	4) Look in "dirname" generate a name se
 *		vmunix.n
 *		vmcore.n
 *	5) Check in "dirname"/minfree to be certain there is space
 *	6) Make entry in shutdown log with date and cause of crash
E 4
I 4
 * savecore
E 4
 */
I 16

E 42
E 16
D 12

E 12
D 32
#include <stdio.h>
#include <nlist.h>
E 32
#include <sys/param.h>
I 48
D 51
#include <sys/file.h>
E 48
D 38
#include <sys/dir.h>
E 38
I 38
#include <sys/mount.h>
E 51
E 38
#include <sys/stat.h>
I 51
#include <sys/mount.h>
E 51
D 8
D 10
#include <sys/filsys.h>
E 10
I 10
D 35
#include <sys/fs.h>
E 35
I 35
D 38
#include <ufs/fs.h>
E 38
E 35
E 10
E 8
I 8
D 11
#include <sys/fs.h>
E 11
E 8
D 15
#include <time.h>
E 15
I 15
D 48
#include <sys/time.h>
I 22
#include <sys/file.h>
E 48
D 25
#include <syslog.h>
E 25
I 25
#include <sys/syslog.h>
I 48
#include <sys/time.h>

D 51
#include <errno.h>
E 51
E 48
I 38
#include <dirent.h>
I 51
#include <errno.h>
#include <fcntl.h>
E 51
E 38
I 32
D 48
#include <stdio.h>
E 48
#include <nlist.h>
I 47
D 48
#include <unistd.h>
E 48
E 47
D 33
#include "pathnames.h"
E 33
I 33
#include <paths.h>
I 48
D 50
#include <stdarg.h>
E 50
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 51
#include <tzfile.h>
E 51
#include <unistd.h>
E 48
E 33
E 32
E 25
E 22
E 15

D 4
#define LEEWAY (60L*60L*24L*3L)	/* Maximum reasonable dump age diff (3 days )*/
#define eq(a,b) (strcmp(a,b)==0)
#define ok(number) (number&0x7fffffff)
E 4
I 4
D 51
#define	DAY	(60L*60L*24L)
#define	LEEWAY	(3*DAY)

E 51
D 48
#define eq(a,b) (!strcmp(a,b))
E 48
I 12
D 46
#ifdef vax
E 12
#define ok(number) ((number)&0x7fffffff)
I 12
#else
I 26
#ifdef tahoe
#define ok(number) ((number)&~0xc0000000)
#else
I 40
#ifdef i386
#define ok(number) ((number)&~0xfe000000)
#else
E 40
E 26
#define ok(number) (number)
I 40
#endif
E 40
#endif
I 26
#endif
E 46
I 46
#define ok(number) ((number) - KERNBASE)
E 46
E 26
E 12

E 4
D 23
#define SHUTDOWNLOG "/usr/adm/shutdownlog"
D 4
#define TRUE (1)
#define FALSE (0)
E 4

E 23
D 16
struct nlist nl[] = {
E 16
I 16
D 51
struct nlist current_nl[] = {	/* namelist for currently running system */
E 51
I 51
struct nlist current_nl[] = {	/* Namelist for currently running system. */
E 51
E 16
#define X_DUMPDEV	0
	{ "_dumpdev" },
#define X_DUMPLO	1
	{ "_dumplo" },
#define X_TIME		2
	{ "_time" },
D 12
#define X_PHYSMEM	3
	{ "_physmem" },
E 12
I 12
#define	X_DUMPSIZE	3
	{ "_dumpsize" },
E 12
#define X_VERSION	4
	{ "_version" },
#define X_PANICSTR	5
	{ "_panicstr" },
I 10
D 12
#define X_DOADUMP	6
	{ "_doadump" },
E 10
I 8
#define X_DOADUMP	6
	{ "_doadump" },
E 8
	{ 0 },
E 12
I 12
#define	X_DUMPMAG	6
	{ "_dumpmag" },
	{ "" },
E 12
};
I 51
int cursyms[] = { X_DUMPDEV, X_DUMPLO, X_VERSION, X_DUMPMAG, -1 };
int dumpsyms[] = { X_TIME, X_DUMPSIZE, X_VERSION, X_PANICSTR, X_DUMPMAG, -1 };
E 51

I 16
D 51
struct nlist dump_nl[] = {	/* name list for dumped system */
	{ "_dumpdev" },		/* entries MUST be the same as */
	{ "_dumplo" },		/*	those in current_nl[]  */
E 51
I 51
struct nlist dump_nl[] = {	/* Name list for dumped system. */
	{ "_dumpdev" },		/* Entries MUST be the same as */
	{ "_dumplo" },		/*	those in current_nl[].  */
E 51
	{ "_time" },
	{ "_dumpsize" },
	{ "_version" },
	{ "_panicstr" },
	{ "_dumpmag" },
	{ "" },
};

I 51
/* Types match kernel declarations. */
long	dumplo;				/* where dump starts on dumpdev */
int	dumpmag;			/* magic number in dump */
int	dumpsize;			/* amount of memory dumped */

E 51
E 16
I 10
D 12
/*
 *	this magic number is found in the kernel at label "doadump"
 *
 *	It is derived as follows:
 *
 *		doadump:	nop			01
 *				nop			01
 *				bicl2 $...		ca
 *							8f
 *
 *	Thus, it is likely to be moderately stable, even across
 *	operating system releases.
 */
#define DUMPMAG 0x8fca0101

E 10
I 8
/*
 *	this magic number is found in the kernel at label "doadump"
 *
 *	It is derived as follows:
 *
 *		doadump:	nop			01
 *				nop			01
 *				bicl2 $...		ca
 *							8f
 *
 *	Thus, it is likely to be moderately stable, even across
 *	operating system releases.
 */
#define DUMPMAG 0x8fca0101

E 12
E 8
I 7
D 48
char	*system;
E 48
I 48
char	*vmunix;
E 48
E 7
D 4
char *dirname;				/* Directory to save dumps in */
char *ddname;				/* Name of dump device */
char *find_dev();
int minfree;				/* Minimum free blocks on device */
dev_t dumpdev;				/* Dump device */
time_t dumptime;			/* Time the dump was taken */
int dumplo;				/* Where dump starts on dumpdev */
int physmem;				/* Amount of memory in machine */
time_t now;				/* Current date */
char *path(), *malloc();
char vers[80], core_vers[80];
char panic_mesg[80];
int panicstr;
int do_the_dump = TRUE;
E 4
I 4
char	*dirname;			/* directory to save dumps in */
char	*ddname;			/* name of dump device */
I 35
D 51
int	dumpfd;				/* read/write descriptor on block dev */
E 51
E 35
D 48
char	*find_dev();
E 48
dev_t	dumpdev;			/* dump device */
D 51
time_t	dumptime;			/* time the dump was taken */
int	dumplo;				/* where dump starts on dumpdev */
D 12
int	physmem;			/* amount of memory in machine */
E 12
I 12
int	dumpsize;			/* amount of memory dumped */
int	dumpmag;			/* magic number in dump */
E 51
I 51
int	dumpfd;				/* read/write descriptor on block dev */
E 51
E 12
time_t	now;				/* current date */
D 48
char	*path();
D 21
unsigned malloc();
E 21
I 21
char	*malloc();
E 21
char	*ctime();
E 48
D 51
char	vers[80];
char	core_vers[80];
char	panic_mesg[80];
E 51
I 51
char	panic_mesg[1024];
E 51
int	panicstr;
D 6
int	do_the_dump = 1;
E 6
D 47
off_t	lseek();
off_t	Lseek();
E 47
I 47
D 48
void	Lseek __P((int fd, off_t off, int flag));
E 48
E 47
I 16
D 43
int	Verbose;
E 43
I 43
D 51
int	verbose;
E 43
I 27
int	force;
I 29
int	clear;
E 51
I 51
char	vers[1024];
E 51
E 29
E 27
I 25
D 48
extern	int errno;
E 48
E 25
E 16
E 4

I 48
D 51
int	dump_exists __P(());
void	clear_dump __P(());
E 51
I 51
int	clear, compress, force, verbose;	/* flags */

void	 check_kmem __P((void));
int	 check_space __P((void));
void	 clear_dump __P((void));
int	 Create __P((char *, int));
int	 dump_exists __P((void));
E 51
D 49
char	*find_dev __P((int, int));
E 49
I 49
char	*find_dev __P((dev_t, int));
I 51
int	 get_crashtime __P((void));
void	 kmem_setup __P((void));
void	 log __P((int, char *, ...));
void	 Lseek __P((int, off_t, int));
int	 Open __P((char *, int rw));
int	 Read __P((int, void *, int));
E 51
E 49
char	*rawname __P((char *s));
D 51
void	read_kmem __P(());
void	check_kmem __P(());
int	get_crashtime __P(());
char	*path __P((char *));
int	check_space __P(());
int	read_number __P((char *));
int	save_core __P(());
int	Open __P((char *, int rw));
int	Read __P((int, char *, int));
void	Lseek __P((int, off_t, int));
int	Create __P((char *, int));
void	Write __P((int, char *, int));
void	log __P((int, char *, ...));
void	Perror __P((int, char *, char *));
void	usage __P(());
E 51
I 51
void	 save_core __P((void));
void	 usage __P((void));
void	 Write __P((int, void *, int));
E 51

int
E 48
main(argc, argv)
D 4
char **argv;
int argc;
E 4
I 4
D 48
	char **argv;
E 48
	int argc;
I 48
	char *argv[];
E 48
E 4
{
I 43
D 48
	extern char *optarg;
	extern int optind;
E 48
	int ch;
E 43
I 22
D 48
	char *cp;
E 48
E 22
D 4
	if (argc != 2)
	{
E 4
I 4

I 16
D 22
	while ((argc > 1) && (argv[1][0] == '-')) {
		switch (argv[1][1]) {
E 22
I 22
D 43
	argc--, argv++;
	while (argc > 0 && argv[0][0] == '-') {
		for (cp = &argv[0][1]; *cp; cp++) switch (*cp) {

I 27
		case 'f':
			force++;
E 43
I 43
D 51
	while ((ch = getopt(argc, argv, "cdfv")) != EOF)
E 51
I 51
	openlog("savecore", LOG_PERROR, LOG_DAEMON);

D 52
	while ((ch = getopt(argc, argv, "cdfvz")) != EOF)
E 52
I 52
D 60
	while ((ch = getopt(argc, argv, "cdfNvz")) != EOF)
E 60
I 60
	while ((ch = getopt(argc, argv, "cdfN:vz")) != EOF)
E 60
E 52
E 51
		switch(ch) {
		case 'c':
			clear = 1;
E 43
			break;
D 43

E 43
I 43
D 51
		case 'd':		/* not documented */
E 51
I 51
		case 'd':		/* Not documented. */
E 51
E 43
E 27
E 22
		case 'v':
I 35
D 43
		case 'd':
E 35
I 17
D 22
		case 'd':
E 17
			Verbose = 1;
E 22
I 22
			Verbose++;
E 43
I 43
			verbose = 1;
E 43
E 22
			break;
I 22
D 43

I 29
		case 'c':
			clear++;
E 43
I 43
		case 'f':
			force = 1;
E 43
			break;
I 52
		case 'N':
			vmunix = optarg;
			break;
E 52
I 51
		case 'z':
			compress = 1;
			break;
E 51
D 43

E 43
I 43
		case '?':
E 43
E 29
E 22
		default:
D 22
			fprintf(stderr, "savecore: illegal flag -%c\n",
				argv[1][1]);
E 22
I 22
D 43
		usage:
E 22
			fprintf(stderr,
D 22
				"usage: savecore [-v] dirname [ system ]\n");
E 22
I 22
D 27
			    "usage: savecore [-v] dirname [ system ]\n");
E 27
I 27
D 35
			    "usage: savecore [-f] [-v] dirname [ system ]\n");
E 35
I 35
			    "usage: savecore [-f] [-v] [-c] dirname [ system ]\n");
E 35
E 27
E 22
			exit(1);
E 43
I 43
			usage();
E 43
		}
D 22
		argc--;
		argv++;
E 22
I 22
D 43
		argc--, argv++;
E 43
I 43
	argc -= optind;
	argv += optind;

D 51
	/* This is wrong, but I want "savecore -c" to work. */
E 51
	if (!clear) {
		if (argc != 1 && argc != 2)
			usage();
		dirname = argv[0];
E 43
E 22
	}
D 22

E 16
D 7
	if (argc != 2) {
E 4
		fprintf(stderr, "usage: savecore dirname\n");
E 7
I 7
	if (argc != 2 && argc != 3) {
D 16
		fprintf(stderr, "usage: savecore dirname [ system ]\n");
E 16
I 16
		fprintf(stderr, "usage: savecore [-v] dirname [ system ]\n");
E 22
I 22
D 43
	if (argc != 1 && argc != 2)
		goto usage;
	dirname = argv[0];
E 43
	if (argc == 2)
D 48
		system = argv[1];
E 48
I 48
		vmunix = argv[1];
E 48
I 43

E 43
D 23
	openlog("savecore", LOG_ODELAY, LOG_USER);
E 23
I 23
D 51
	openlog("savecore", LOG_ODELAY, LOG_AUTH);
E 51
I 51
	(void)time(&now);
	kmem_setup();
E 51
E 23
D 43
	if (access(dirname, W_OK) < 0) {
I 25
D 26
		int oerrno = errno;

		perror(dirname);
		errno = oerrno;
E 25
		syslog(LOG_ERR, "%s: %m", dirname);
E 26
I 26
D 37
		Perror(LOG_ERR, "%s: %m", dirname);
E 37
I 37
		Perror(LOG_ERR, "%s: %m\n", dirname);
E 37
E 26
E 22
E 16
E 7
		exit(1);
	}
E 43
I 43

E 43
D 22
	dirname = argv[1];
I 7
	if (argc == 3)
		system = argv[2];
E 7
D 4
	if (access(dirname, 2) < 0)
	{
E 4
I 4
	if (access(dirname, 2) < 0) {
E 4
		perror(dirname);
D 4
		exit(4);
E 4
I 4
		exit(1);
E 4
	}
E 22
D 4
	/*
	 * Now invoke the local dieties so that things get done
	 */
	time(&now);
E 4
I 4
D 8
D 10
	(void) time(&now);
E 10
I 10
D 11

E 10
E 8
I 8

E 11
E 8
E 4
D 51
	read_kmem();
D 8
D 10
	log_entry();
D 6
	if (do_the_dump && get_crashtime() && check_space())
E 6
I 6
	if (get_crashtime() && check_space())
E 6
		save_core();
I 6
	else
		exit(1);
E 10
I 10
D 22
	if (dump_exists()) {
		(void) time(&now);
		check_kmem();
		log_entry();
		if (get_crashtime() && check_space()) {
			save_core();
			clear_dump();
D 16
		} else
E 16
I 16
		} else {
			if (Verbose)
				fprintf(stderr, "No space or time\n");
E 16
			exit(1);
I 16
		}
E 22
I 22
	if (!dump_exists()) {
D 43
		if (Verbose)
			fprintf(stderr, "savecore: No dump exists.\n");
E 43
I 43
D 44
		if (!verbose)
			(void)fprintf(stderr, "savecore: no dump exists\n");
E 44
I 44
		(void)fprintf(stderr, "savecore: no core dump\n");
E 44
E 43
D 35
		exit(0);
E 35
I 35
		if (!force)
			exit(0);
E 35
E 22
E 16
	}
E 51
I 29
	if (clear) {
		clear_dump();
		exit(0);
	}
E 29
I 16
D 22
	else if (Verbose) {
		fprintf(stderr, "No dump exists\n");
	}
E 16
	return 0;
E 22
I 22
D 51
	(void) time(&now);
E 51
I 51

	if (!dump_exists() && !force)
		exit(1);

E 51
	check_kmem();
I 51

E 51
D 24
	log_entry();
E 24
I 24
	if (panicstr)
D 29
		syslog(LOG_CRIT, "reboot after panic: %s", panic_mesg);
E 29
I 29
D 35
		syslog(LOG_CRIT, "reboot after panic: %s\n", panic_mesg);
E 35
I 35
D 51
		log(LOG_CRIT, "reboot after panic: %s\n", panic_mesg);
E 51
I 51
		syslog(LOG_ALERT, "reboot after panic: %s", panic_mesg);
E 51
E 35
E 29
	else
D 29
		syslog(LOG_CRIT, "reboot");
E 29
I 29
D 51
		syslog(LOG_CRIT, "reboot\n");
E 51
I 51
		syslog(LOG_ALERT, "reboot");
E 51
I 43

D 51
	if (access(dirname, W_OK) < 0) {
		Perror(LOG_ERR, "%s: %m\n", dirname);
		exit(1);
	}
E 51
E 43
E 29
E 24
D 27
	if (!get_crashtime() || !check_space())
E 27
I 27
	if ((!get_crashtime() || !check_space()) && !force)
E 27
		exit(1);
D 48
	save_core();
E 48
I 48
D 51
	if (!save_core())
		exit(1);
E 51
I 51

	save_core();

E 51
E 48
	clear_dump();
	exit(0);
E 22
E 10
E 8
I 8
D 11
	if (dump_exists()) {
		(void) time(&now);
		check_kmem();
		log_entry();
		if (get_crashtime() && check_space()) {
			save_core();
			clear_dump();
		} else
			exit(1);
	}
	return 0;
E 11
E 8
E 6
}

I 48
D 51
int
E 48
I 10
D 22
int
E 22
dump_exists()
{
D 35
	register int dumpfd;
E 35
	int word;

D 22
	dumpfd = Open(ddname, 0);
D 12
	Lseek(dumpfd, (off_t)(dumplo + ok(nl[X_DOADUMP].n_value)), 0);
E 12
I 12
D 16
	Lseek(dumpfd, (off_t)(dumplo + ok(nl[X_DUMPMAG].n_value)), 0);
E 16
I 16
	Lseek(dumpfd, (off_t)(dumplo + ok(dump_nl[X_DUMPMAG].n_value)), 0);
E 16
E 12
	Read(dumpfd, (char *)&word, sizeof word);
E 22
I 22
D 35
	dumpfd = Open(ddname, O_RDONLY);
E 35
	Lseek(dumpfd, (off_t)(dumplo + ok(dump_nl[X_DUMPMAG].n_value)), L_SET);
	Read(dumpfd, (char *)&word, sizeof (word));
E 22
D 35
	close(dumpfd);
I 16
D 22
	if (Verbose && (word != dumpmag)) {
E 22
I 22
	if (Verbose && word != dumpmag) {
E 22
D 19
		printf("dumplo = %d (%d bytes)\n", dumplo/512, dumplo);
E 19
I 19
		printf("dumplo = %d (%d bytes)\n", dumplo/DEV_BSIZE, dumplo);
E 35
I 35
D 36
	if (Verbose)
		printf("dumplo = %d (%d * 512)\n", dumplo, dumplo/512);
E 36
D 43
	if (Verbose && word != dumpmag)
E 43
I 43
	if (verbose && word != dumpmag)
E 43
E 35
E 19
		printf("magic number mismatch: %x != %x\n", word, dumpmag);
D 35
	}
E 35
E 16
D 11
	
E 11
D 12
	return (word == DUMPMAG);
E 12
I 12
	return (word == dumpmag);
E 12
}

E 51
I 48
void
E 48
D 51
clear_dump()
E 51
I 51
kmem_setup()
E 51
{
D 35
	register int dumpfd;
E 35
D 48
	int zero = 0;
E 48
I 48
D 51
	int zero;
E 48

I 48
	zero = 0;
E 48
D 22
	dumpfd = Open(ddname, 1);
D 12
	Lseek(dumpfd, (off_t)(dumplo + ok(nl[X_DOADUMP].n_value)), 0);
E 12
I 12
D 16
	Lseek(dumpfd, (off_t)(dumplo + ok(nl[X_DUMPMAG].n_value)), 0);
E 16
I 16
	Lseek(dumpfd, (off_t)(dumplo + ok(dump_nl[X_DUMPMAG].n_value)), 0);
E 16
E 12
	Write(dumpfd, (char *)&zero, sizeof zero);
E 22
I 22
D 35
	dumpfd = Open(ddname, O_WRONLY);
E 35
	Lseek(dumpfd, (off_t)(dumplo + ok(dump_nl[X_DUMPMAG].n_value)), L_SET);
	Write(dumpfd, (char *)&zero, sizeof (zero));
E 22
D 35
	close(dumpfd);
E 35
}

E 10
I 8
D 11
int
dump_exists()
{
	register int dumpfd;
	int word;

	dumpfd = Open(ddname, 0);
	Lseek(dumpfd, (off_t)(dumplo + ok(nl[X_DOADUMP].n_value)), 0);
	Read(dumpfd, (char *)&word, sizeof word);
	close(dumpfd);
	
	return (word == DUMPMAG);
}

clear_dump()
{
	register int dumpfd;
	int zero = 0;

	dumpfd = Open(ddname, 1);
	Lseek(dumpfd, (off_t)(dumplo + ok(nl[X_DOADUMP].n_value)), 0);
	Write(dumpfd, (char *)&zero, sizeof zero);
	close(dumpfd);
}

E 11
E 8
D 4
/*
 * find_dev
 *	Lookup a dev in the /dev directory, return the dev name
 */

char *find_dev(dev, type)
register dev_t dev;
register int type;
E 4
I 4
char *
find_dev(dev, type)
D 48
	register dev_t dev;
	register int type;
E 48
I 48
D 49
	register int dev, type;
E 49
I 49
	register dev_t dev;
	register int type;
E 49
E 48
E 4
{
D 8
D 10
	register int dfd = Open("/dev", 0);
	struct direct dir;
E 10
I 10
D 33
	register DIR *dfd = opendir("/dev");
E 33
I 33
D 48
	register DIR *dfd = opendir(_PATH_DEV);
E 48
I 48
	static char devname[MAXPATHLEN + 1];
	register DIR *dfd;
E 48
E 33
D 38
	struct direct *dir;
E 38
I 38
	struct dirent *dir;
E 38
E 10
E 8
I 8
D 11
	register DIR *dfd = opendir("/dev");
	struct direct *dir;
E 11
E 8
	struct stat statb;
D 8
D 10
	static char devname[DIRSIZ + 1];
E 10
I 10
D 48
	static char devname[MAXPATHLEN + 1];
E 48
E 10
E 8
I 8
D 11
	static char devname[MAXPATHLEN + 1];
E 11
E 8
I 3
	char *dp;
E 3

I 48
	dfd = opendir(_PATH_DEV);
E 48
D 33
	strcpy(devname, "/dev/");
E 33
I 33
	strcpy(devname, _PATH_DEV);
E 33
D 4
	while(Read(dfd, &dir, sizeof dir) > 0)
	{
E 4
I 4
D 8
D 10
	while(Read(dfd, (char *)&dir, sizeof dir) > 0) {
E 4
		if (dir.d_ino == 0)
			continue;
		strncpy(devname + 5, dir.d_name, DIRSIZ);
		devname[DIRSIZ] = '\0';
E 10
I 10
	while ((dir = readdir(dfd))) {
D 33
		strcpy(devname + 5, dir->d_name);
E 33
I 33
D 48
		strcpy(devname + sizeof(_PATH_DEV) - 1, dir->d_name);
E 48
I 48
		(void)strcpy(devname + sizeof(_PATH_DEV) - 1, dir->d_name);
E 48
E 33
E 10
E 8
I 8
D 11
	while ((dir = readdir(dfd))) {
		strcpy(devname + 5, dir->d_name);
E 11
E 8
D 4
		if (stat(devname, &statb))
E 4
I 4
		if (stat(devname, &statb)) {
E 4
			perror(devname);
D 4
		else
		{
			if ((statb.st_mode&S_IFMT) != type)
				continue;
			if (dev == statb.st_rdev)
			{
				close(dfd);
D 3
				return devname;
E 3
I 3
				dp = malloc(strlen(devname)+1);
				strcpy(dp, devname);
				return dp;
E 3
			}
E 4
I 4
			continue;
E 4
		}
I 4
		if ((statb.st_mode&S_IFMT) != type)
			continue;
		if (dev == statb.st_rdev) {
D 8
D 10
			close(dfd);
E 10
I 10
			closedir(dfd);
E 10
E 8
I 8
D 11
			closedir(dfd);
E 11
E 8
D 21
			dp = (char *)malloc(strlen(devname)+1);
E 21
I 21
			dp = malloc(strlen(devname)+1);
E 21
			strcpy(dp, devname);
D 22
			return dp;
E 22
I 22
			return (dp);
E 22
		}
E 4
	}
D 8
D 10
	close(dfd);
E 10
I 10
	closedir(dfd);
I 25
D 26
	fprintf(stderr, "Can't find device %d/%d\n", major(dev), minor(dev));
E 25
E 10
E 8
I 8
D 11
	closedir(dfd);
E 11
E 8
D 12
	fprintf(stderr, "Can't find device %d,%d\n", major(dev), minor(dev));
E 12
I 12
D 22
	fprintf(stderr, "savecore: Can't find device %d,%d\n",
		major(dev), minor(dev));
E 22
I 22
	syslog(LOG_ERR, "Can't find device %d/%d\n", major(dev), minor(dev));
E 26
I 26
	log(LOG_ERR, "Can't find device %d/%d\n", major(dev), minor(dev));
E 26
E 22
E 12
D 4
	exit(7);
E 4
I 4
	exit(1);
	/*NOTREACHED*/
E 4
}

I 35
char *
rawname(s)
	char *s;
{
	static char name[MAXPATHLEN];
D 48
	char *sl, *rindex();
E 48
I 48
	char *sl;
E 48

	if ((sl = rindex(s, '/')) == NULL || sl[1] == '0') {
		log(LOG_ERR, "can't make raw dump device name from %s?\n", s);
		return (s);
	}
D 48
	sprintf(name, "%.*s/r%s", sl - s, s, sl + 1);
E 48
I 48
	(void)snprintf(name, sizeof(name), "%.*s/r%s", sl - s, s, sl + 1);
E 48
	return (name);
}

E 35
I 22
int	cursyms[] =
    { X_DUMPDEV, X_DUMPLO, X_VERSION, X_DUMPMAG, -1 };
int	dumpsyms[] =
    { X_TIME, X_DUMPSIZE, X_VERSION, X_PANICSTR, X_DUMPMAG, -1 };
I 48

void
E 48
E 22
D 4
/*
 * Open
 *	Open and exit if open fails
 */

Open(name, rw)
char *name;
int rw;
{
	int fd;

	if ((fd = open(name, rw)) < 0)
	{
		perror(name);
		exit(2);
	}
	return fd;
}

/*
 * Read, like read but checks bad return codes
 */

Read(fd, buff, size)
int fd, size;
char *buff;
{
	int ret;

	if ((ret = read(fd, buff, size)) < 0)
	{
		perror("reading");
		exit(3);
	}
	return ret;
}

/*
 * Lseek
 *	A "safe" lseek
 */

long Lseek(fd, off, flag)
int fd, flag;
long off;
{
	long ret;

	if ((ret = lseek(fd, off, flag)) == -1L)
	{
		perror("lseek");
		exit(5);
	}
	return ret;
}

Create(file, mode)
char *file;
int mode;
{
	register int fd;

	if ((fd = creat(file, mode)) < 0)
	{
		perror(file);
		exit(9);
	}
	return fd;
}

Write(fd, buf, size)
int fd, size;
char *buf;
{
	if (write(fd, buf, size) < size)
	{
		perror("Writing");
		exit(10);
	}
}

/*
 * Get dumpdev and dumplo from kmem/vmunix
 */

E 4
read_kmem()
{
E 51
D 22
	int kmem;
	FILE *fp;
E 22
D 48
	register char *cp;
E 48
I 22
	FILE *fp;
E 22
I 16
D 48
	char *dump_sys;
E 48
I 22
	int kmem, i;
I 48
	char *dump_sys;
E 48
E 22
	
D 32
	dump_sys = system ? system : "/vmunix";
E 16
D 22

E 22
D 16
	nlist("/vmunix", nl);
D 4
	if (nl[X_DUMPDEV].n_value == 0)
	{
	    fprintf(stderr, "savecore: dumpdev not in namelist\n");
	    exit(6);
E 4
I 4
	if (nl[X_DUMPDEV].n_value == 0) {
E 16
I 16
	nlist("/vmunix", current_nl);
E 32
I 32
D 48
	dump_sys = system ? system : _PATH_UNIX;
E 48
I 48
D 51
	dump_sys = vmunix ? vmunix : _PATH_UNIX;
E 48
	nlist(_PATH_UNIX, current_nl);
E 32
	nlist(dump_sys, dump_nl);
E 51
D 22

E 22
	/*
D 51
	 * Some names we need for the currently running system,
	 * others for the system that was running when the dump was made.
	 * The values obtained from the current system are used
	 * to look for things in /dev/kmem that cannot be found
	 * in the dump_sys namelist, but are presumed to be the same
	 * (since the disk partitions are probably the same!)
E 51
I 51
	 * Some names we need for the currently running system, others for
	 * the system that was running when the dump was made.  The values
	 * obtained from the current system are used to look for things in
	 * /dev/kmem that cannot be found in the dump_sys namelist, but are
	 * presumed to be the same (since the disk partitions are probably
	 * the same!)
E 51
	 */
I 51
	if ((nlist(_PATH_UNIX, current_nl)) == -1)
		syslog(LOG_ERR, "%s: nlist: %s", _PATH_UNIX, strerror(errno));
E 51
D 22
	if (current_nl[X_DUMPDEV].n_value == 0) {
E 16
D 12
		fprintf(stderr, "/vmunix: dumpdev not in namelist\n");
E 12
I 12
		fprintf(stderr, "savecore: /vmunix: dumpdev not in namelist\n");
E 12
		exit(1);
E 4
	}
D 4
	if (nl[X_DUMPLO].n_value == 0)
	{
	    fprintf(stderr, "savecore: dumplo not in namelist\n");
	    exit(6);
E 4
I 4
D 16
	if (nl[X_DUMPLO].n_value == 0) {
E 16
I 16
	if (current_nl[X_DUMPLO].n_value == 0) {
E 16
D 12
		fprintf(stderr, "/vmunix: dumplo not in namelist\n");
E 12
I 12
		fprintf(stderr, "savecore: /vmunix: dumplo not in namelist\n");
E 12
		exit(1);
E 4
	}
D 4
	if (nl[X_TIME].n_value == 0)
	{
	    fprintf(stderr, "savecore: time not in namelist\n");
	    exit(6);
E 4
I 4
D 16
	if (nl[X_TIME].n_value == 0) {
D 12
		fprintf(stderr, "/vmunix: time not in namelist\n");
E 12
I 12
		fprintf(stderr, "savecore: /vmunix: time not in namelist\n");
E 16
I 16
	if (dump_nl[X_TIME].n_value == 0) {
		fprintf(stderr, "savecore: %s: time not in namelist\n",
				dump_sys);
E 16
E 12
		exit(1);
E 4
	}
D 4
	if (nl[X_PHYSMEM].n_value == 0)
	{
		fprintf("savecore: physmem not in namelist\n");
		exit(6);
E 4
I 4
D 12
	if (nl[X_PHYSMEM].n_value == 0) {
		fprintf(stderr, "/vmunix: physmem not in namelist\n");
E 12
I 12
D 16
	if (nl[X_DUMPSIZE].n_value == 0) {
		fprintf(stderr, "savecore: /vmunix: dumpsize not in namelist\n");
E 16
I 16
	if (dump_nl[X_DUMPSIZE].n_value == 0) {
		fprintf(stderr, "savecore: %s: dumpsize not in namelist\n",
				dump_sys);
E 16
E 12
		exit(1);
E 4
	}
D 4
	if (nl[X_VERSION].n_value == 0)
	{
		fprintf("savecore: version not in namelist\n");
		exit(6);
E 4
I 4
D 16
	if (nl[X_VERSION].n_value == 0) {
D 12
		fprintf(stderr, "/vmunix: version not in namelist\n");
E 12
I 12
		fprintf(stderr, "savecore: /vmunix: version not in namelist\n");
E 16
I 16
	/* we need VERSION in both images */
	if (current_nl[X_VERSION].n_value == 0) {
		fprintf(stderr, "savecore: /vmunix: version not in namelist\n",
				dump_sys);
E 16
E 12
		exit(1);
E 4
	}
D 4
	if (nl[X_PANICSTR].n_value == 0)
	{
		fprintf("savecore: panicstr not in namelist\n");
		exit(6);
E 4
I 4
D 16
	if (nl[X_PANICSTR].n_value == 0) {
D 12
		fprintf(stderr, "/vmunix: panicstr not in namelist\n");
E 12
I 12
		fprintf(stderr, "savecore: /vmunix: panicstr not in namelist\n");
E 16
I 16
	if (dump_nl[X_VERSION].n_value == 0) {
		fprintf(stderr, "savecore: %s: version not in namelist\n",
				dump_sys);
E 16
E 12
		exit(1);
E 4
	}
I 10
D 12
	if (nl[X_DOADUMP].n_value == 0) {
		fprintf(stderr, "/vmunix: doadump not in namelist\n");
E 12
I 12
D 16
	if (nl[X_DUMPMAG].n_value == 0) {
E 16
I 16
	if (dump_nl[X_PANICSTR].n_value == 0) {
		fprintf(stderr, "savecore: %s: panicstr not in namelist\n",
				dump_sys);
		exit(1);
	}
	/* we need DUMPMAG in both images */
	if (current_nl[X_DUMPMAG].n_value == 0) {
E 16
		fprintf(stderr, "savecore: /vmunix: dumpmag not in namelist\n");
E 12
		exit(1);
	}
I 16
	if (dump_nl[X_DUMPMAG].n_value == 0) {
		fprintf(stderr, "savecore: %s: dumpmag not in namelist\n",
				dump_sys);
		exit(1);
	}
E 16
E 10
I 8
D 12
	if (nl[X_DOADUMP].n_value == 0) {
		fprintf(stderr, "/vmunix: doadump not in namelist\n");
		exit(1);
	}
E 12
E 8
	kmem = Open("/dev/kmem", 0);
D 4
	Lseek(kmem, nl[X_DUMPDEV].n_value, 0);
	Read(kmem, &dumpdev, sizeof dumpdev);
	Lseek(kmem, nl[X_DUMPLO].n_value, 0);
	Read(kmem, &dumplo, sizeof dumplo);
	Lseek(kmem, nl[X_PHYSMEM].n_value, 0);
	Read(kmem, &physmem, sizeof physmem);
	Lseek(kmem, nl[X_PANICSTR].n_value, 0);
	Read(kmem, &panicstr, sizeof panicstr);
E 4
I 4
D 16
	Lseek(kmem, (long)nl[X_DUMPDEV].n_value, 0);
E 16
I 16
	Lseek(kmem, (long)current_nl[X_DUMPDEV].n_value, 0);
E 22
I 22
	for (i = 0; cursyms[i] != -1; i++)
		if (current_nl[cursyms[i]].n_value == 0) {
I 25
D 26
			fprintf(stderr, "/vmunix: %s not in namelist",
E 26
I 26
D 29
			log(LOG_ERR, "/vmunix: %s not in namelist",
E 29
I 29
D 32
			log(LOG_ERR, "/vmunix: %s not in namelist\n",
E 32
I 32
D 51
			log(LOG_ERR, "%s: %s not in namelist\n", _PATH_UNIX,
E 32
E 29
E 26
			    current_nl[cursyms[i]].n_name);
E 51
I 51
			syslog(LOG_ERR, "%s: %s not in namelist",
			    _PATH_UNIX, current_nl[cursyms[i]].n_name);
E 51
E 25
D 26
			syslog(LOG_ERR, "/vmunix: %s not in namelist",
			    current_nl[cursyms[i]].n_name);
E 26
			exit(1);
		}
I 51

	dump_sys = vmunix ? vmunix : _PATH_UNIX;
	if ((nlist(dump_sys, dump_nl)) == -1)
		syslog(LOG_ERR, "%s: nlist: %s", dump_sys, strerror(errno));
E 51
	for (i = 0; dumpsyms[i] != -1; i++)
		if (dump_nl[dumpsyms[i]].n_value == 0) {
I 25
D 26
			fprintf(stderr, "%s: %s not in namelist", dump_sys,
E 26
I 26
D 29
			log(LOG_ERR, "%s: %s not in namelist", dump_sys,
E 29
I 29
D 51
			log(LOG_ERR, "%s: %s not in namelist\n", dump_sys,
E 29
E 26
			    dump_nl[dumpsyms[i]].n_name);
E 51
I 51
			syslog(LOG_ERR, "%s: %s not in namelist",
			    dump_sys, dump_nl[dumpsyms[i]].n_name);
E 51
E 25
D 26
			syslog(LOG_ERR, "%s: %s not in namelist", dump_sys,
			    dump_nl[dumpsyms[i]].n_name);
E 26
			exit(1);
		}
I 51

E 51
D 32
	kmem = Open("/dev/kmem", O_RDONLY);
E 32
I 32
	kmem = Open(_PATH_KMEM, O_RDONLY);
E 32
D 47
	Lseek(kmem, (long)current_nl[X_DUMPDEV].n_value, L_SET);
E 47
I 47
	Lseek(kmem, (off_t)current_nl[X_DUMPDEV].n_value, L_SET);
E 47
E 22
E 16
D 12
	Read(kmem, (char *)&dumpdev, sizeof dumpdev);
E 12
I 12
D 51
	Read(kmem, (char *)&dumpdev, sizeof (dumpdev));
E 51
I 51
	(void)Read(kmem, &dumpdev, sizeof(dumpdev));
I 59
	if (dumpdev == NODEV) {
		syslog(LOG_WARNING, "no core dump (no dumpdev)");
		exit(1);
	}
E 59
E 51
E 12
D 16
	Lseek(kmem, (long)nl[X_DUMPLO].n_value, 0);
E 16
I 16
D 22
	Lseek(kmem, (long)current_nl[X_DUMPLO].n_value, 0);
E 22
I 22
D 47
	Lseek(kmem, (long)current_nl[X_DUMPLO].n_value, L_SET);
E 47
I 47
	Lseek(kmem, (off_t)current_nl[X_DUMPLO].n_value, L_SET);
E 47
E 22
E 16
D 12
	Read(kmem, (char *)&dumplo, sizeof dumplo);
	Lseek(kmem, (long)nl[X_PHYSMEM].n_value, 0);
	Read(kmem, (char *)&physmem, sizeof physmem);
E 12
I 12
D 51
	Read(kmem, (char *)&dumplo, sizeof (dumplo));
E 51
I 51
	(void)Read(kmem, &dumplo, sizeof(dumplo));
E 51
I 36
D 43
	if (Verbose)
E 43
I 43
	if (verbose)
E 43
D 51
		printf("dumplo = %d (%d * %d)\n", dumplo, dumplo/DEV_BSIZE,
		    DEV_BSIZE);
E 51
I 51
		(void)printf("dumplo = %d (%d * %d)\n",
		    dumplo, dumplo/DEV_BSIZE, DEV_BSIZE);
E 51
E 36
D 13
	Lseek(kmem, (long)nl[X_DUMPSIZE].n_value, 0);
	Read(kmem, (char *)&dumpsize, sizeof (dumpsize));
E 13
D 16
	Lseek(kmem, (long)nl[X_DUMPMAG].n_value, 0);
E 16
I 16
D 22
	Lseek(kmem, (long)current_nl[X_DUMPMAG].n_value, 0);
E 22
I 22
D 47
	Lseek(kmem, (long)current_nl[X_DUMPMAG].n_value, L_SET);
E 47
I 47
	Lseek(kmem, (off_t)current_nl[X_DUMPMAG].n_value, L_SET);
E 47
E 22
E 16
D 51
	Read(kmem, (char *)&dumpmag, sizeof (dumpmag));
E 51
I 51
	(void)Read(kmem, &dumpmag, sizeof(dumpmag));
E 51
E 12
E 4
D 19
	dumplo *= 512L;
E 19
I 19
	dumplo *= DEV_BSIZE;
E 19
	ddname = find_dev(dumpdev, S_IFBLK);
I 35
	dumpfd = Open(ddname, O_RDWR);
E 35
D 4
	/*
	 * Check for version mismatch
	 */
	if ((fp = fdopen(kmem, "r")) == NULL)
	{
E 4
I 4
D 22
	if ((fp = fdopen(kmem, "r")) == NULL) {
E 4
D 12
		fprintf(stderr, "Couldn't fdopen kmem\n");
E 12
I 12
		fprintf(stderr, "savecore: Couldn't fdopen kmem\n");
E 22
I 22
	fp = fdopen(kmem, "r");
	if (fp == NULL) {
D 26
		syslog(LOG_ERR, "Couldn't fdopen kmem");
E 26
I 26
D 29
		log(LOG_ERR, "Couldn't fdopen kmem");
E 29
I 29
D 51
		log(LOG_ERR, "Couldn't fdopen kmem\n");
E 51
I 51
		syslog(LOG_ERR, "%s: fdopen: %m", _PATH_KMEM);
E 51
E 29
E 26
E 22
E 12
D 4
		exit(11);
E 4
I 4
		exit(1);
E 4
	}
I 7
D 48
	if (system)
E 48
I 48
	if (vmunix)
E 48
		return;
E 7
D 4
	fseek(fp, nl[X_VERSION].n_value, 0);
E 4
I 4
D 16
	fseek(fp, (long)nl[X_VERSION].n_value, 0);
E 16
I 16
D 22
	fseek(fp, (long)current_nl[X_VERSION].n_value, 0);
E 16
E 4
	fgets(vers, sizeof vers, fp);
E 22
I 22
D 48
	fseek(fp, (long)current_nl[X_VERSION].n_value, L_SET);
E 48
I 48
D 51
	fseek(fp, (off_t)current_nl[X_VERSION].n_value, L_SET);
E 48
	fgets(vers, sizeof (vers), fp);
E 22
D 46
	fclose(fp);
E 46
I 46
	(void)fclose(fp);
E 51
I 51
	(void)fseek(fp, (off_t)current_nl[X_VERSION].n_value, L_SET);
	(void)fgets(vers, sizeof(vers), fp);

	/* Don't fclose(fp), we use dumpfd later. */
E 51
E 46
I 10
}

I 48
void
E 48
D 13
check_kmem() {
E 13
I 13
check_kmem()
{
E 13
D 51
	FILE *fp;
E 51
	register char *cp;
I 51
	FILE *fp;
	char core_vers[1024];
E 51

E 10
I 8
D 11
}

check_kmem() {
	FILE *fp;
	register char *cp;

E 11
E 8
D 4
	if ((fp = fopen(ddname, "r")) == NULL)
	{
E 4
I 4
D 22
	if ((fp = fopen(ddname, "r")) == NULL) {
E 4
		perror(ddname);
E 22
I 22
D 35
	fp = fopen(ddname, "r");
E 35
I 35
	fp = fdopen(dumpfd, "r");
E 35
	if (fp == NULL) {
I 25
D 26
		int oerrno = errno;

		perror(ddname);
		errno = oerrno;
E 25
		syslog(LOG_ERR, "%s: %m", ddname);
E 26
I 26
D 35
		Perror(LOG_ERR, "%s: %m", ddname);
E 35
I 35
D 37
		log(LOG_ERR, "Can't fdopen dumpfd");
E 37
I 37
D 51
		log(LOG_ERR, "Can't fdopen dumpfd\n");
E 51
I 51
		syslog(LOG_ERR, "%s: fdopen: %m", ddname);
E 51
E 37
E 35
E 26
E 22
D 4
		exit(12);
E 4
I 4
		exit(1);
E 4
	}
D 4
	fseek(fp, dumplo+ok(nl[X_VERSION].n_value), 0);
E 4
I 4
D 16
	fseek(fp, (off_t)(dumplo+ok(nl[X_VERSION].n_value)), 0);
E 16
I 16
D 22
	fseek(fp, (off_t)(dumplo+ok(dump_nl[X_VERSION].n_value)), 0);
E 16
E 4
	fgets(core_vers, sizeof core_vers, fp);
E 22
I 22
D 51
	fseek(fp, (off_t)(dumplo+ok(dump_nl[X_VERSION].n_value)), L_SET);
	fgets(core_vers, sizeof (core_vers), fp);
E 22
D 35
	fclose(fp);
E 35
D 4
	if (!eq(vers, core_vers))
	{
		fprintf(stderr, "Version mismatch:\n\t%sand\n\t%s",
				vers,core_vers);
		fprintf(stderr, "Core not saved\n");
		do_the_dump = FALSE;
E 4
I 4
D 5
	if (!eq(vers, core_vers)) {
		fprintf(stderr, "Vmunix version mismatch:\n\t%sand\n\t%s",
E 5
I 5
D 16
	if (!eq(vers, core_vers))
E 16
I 16
D 22
	if (!eq(vers, core_vers) && (system == 0))
E 22
I 22
D 29
	if (!eq(vers, core_vers) && system == 0)
E 22
E 16
D 12
		fprintf(stderr, "Warning: vmunix version mismatch:\n\t%sand\n\t%s",
E 5
		    vers,core_vers);
E 12
I 12
D 26
		fprintf(stderr,
E 26
I 26
		log(LOG_WARNING,
E 26
D 22
		   "savecore: Warning: vmunix version mismatch:\n\t%sand\n\t%s",
E 22
I 22
		   "Warning: vmunix version mismatch:\n\t%sand\n\t%s",
E 22
		   vers, core_vers);
E 29
I 29
D 48
	if (!eq(vers, core_vers) && system == 0) {
E 48
I 48
	if (strcmp(vers, core_vers) && vmunix == 0) {
E 48
D 32
		log(LOG_WARNING, "Warning: vmunix version mismatch:\n");
E 32
I 32
		log(LOG_WARNING, "Warning: %s version mismatch:\n", _PATH_UNIX);
E 32
		log(LOG_WARNING, "\t%s\n", vers);
		log(LOG_WARNING, "and\t%s\n", core_vers);
	}
E 29
I 25
D 26
		syslog(LOG_WARNING,
		   "Warning: vmunix version mismatch: %s and %s",
		   vers, core_vers);
E 26
E 25
E 12
D 5
		fprintf(stderr, "; image not saved\n");
		do_the_dump = 0;
E 4
		return;
	}
E 5
D 4
	/*
	 * Now check the panic string
	 */
	if (panicstr)
	{
		fp = fopen(ddname, "r");
		fseek(fp, dumplo + ok(panicstr));
E 4
I 4
D 35
	fp = fopen(ddname, "r");
E 35
D 16
	fseek(fp, (off_t)(dumplo + ok(nl[X_PANICSTR].n_value)), 0);
E 16
I 16
D 22
	fseek(fp, (off_t)(dumplo + ok(dump_nl[X_PANICSTR].n_value)), 0);
E 16
	fread((char *)&panicstr, sizeof panicstr, 1, fp);
E 22
I 22
	fseek(fp, (off_t)(dumplo + ok(dump_nl[X_PANICSTR].n_value)), L_SET);
	fread((char *)&panicstr, sizeof (panicstr), 1, fp);
E 51
I 51
	fseek(fp, (off_t)(dumplo + ok(dump_nl[X_VERSION].n_value)), L_SET);
	fgets(core_vers, sizeof(core_vers), fp);
	if (strcmp(vers, core_vers) && vmunix == 0)
		syslog(LOG_WARNING,
		    "warning: %s version mismatch:\n\t%s\nand\t%s\n",
		    _PATH_UNIX, vers, core_vers);
	(void)fseek(fp,
	    (off_t)(dumplo + ok(dump_nl[X_PANICSTR].n_value)), L_SET);
	(void)fread(&panicstr, sizeof(panicstr), 1, fp);
E 51
E 22
	if (panicstr) {
D 22
		fseek(fp, dumplo + ok(panicstr), 0);
E 22
I 22
D 51
		fseek(fp, dumplo + ok(panicstr), L_SET);
E 51
I 51
		(void)fseek(fp, dumplo + ok(panicstr), L_SET);
E 51
E 22
E 4
		cp = panic_mesg;
		do
			*cp = getc(fp);
D 35
		while (*cp++);
E 35
I 35
		while (*cp++ && cp < &panic_mesg[sizeof(panic_mesg)]);
E 35
D 4
		fclose(fp);
E 4
	}
I 4
D 35
	fclose(fp);
E 35
I 35
D 51
	/* don't fclose(fp); we want the file descriptor */
E 51
I 51
	/* Don't fclose(fp), we use dumpfd later. */
E 51
E 35
E 4
D 7
}	
E 7
I 7
}
E 7

I 51
void
clear_dump()
{
	long newdumplo;

	newdumplo = 0;
	Lseek(dumpfd, (off_t)(dumplo + ok(dump_nl[X_DUMPMAG].n_value)), L_SET);
	Write(dumpfd, &newdumplo, sizeof(newdumplo));
}

E 51
I 48
int
E 48
D 4
/*
 * Now get the time of the crash
 */

 get_crashtime()
 {
E 4
I 4
D 51
get_crashtime()
E 51
I 51
dump_exists()
E 51
{
I 51
	int newdumpmag;
E 51
E 4
D 35
	int dumpfd;
E 35
I 2
D 48
	time_t clobber = (time_t)0;
E 48
E 2

I 7
D 17
	if (system)
		return (1);
E 17
E 7
D 2
	dumpfd = Open(ddname, 0);
E 2
I 2
D 8
D 10
	dumpfd = Open(ddname, 2);
E 10
I 10
D 22
	dumpfd = Open(ddname, 0);
E 10
E 8
I 8
D 11
	dumpfd = Open(ddname, 0);
E 11
E 8
E 2
D 4
	Lseek(dumpfd, dumplo + ok(nl[X_TIME].n_value), 0);
	Read(dumpfd, &dumptime, sizeof dumptime);
I 2
	Lseek(dumpfd, dumplo + ok(nl[X_TIME].n_value), 0);
	Write(dumpfd, &clobber, sizeof clobber);
E 4
I 4
D 16
	Lseek(dumpfd, (off_t)(dumplo + ok(nl[X_TIME].n_value)), 0);
E 16
I 16
	Lseek(dumpfd, (off_t)(dumplo + ok(dump_nl[X_TIME].n_value)), 0);
E 22
I 22
D 35
	dumpfd = Open(ddname, O_RDONLY);
E 35
D 51
	Lseek(dumpfd, (off_t)(dumplo + ok(dump_nl[X_TIME].n_value)), L_SET);
E 22
E 16
	Read(dumpfd, (char *)&dumptime, sizeof dumptime);
D 8
D 10
	Lseek(dumpfd, (off_t)(dumplo + ok(nl[X_TIME].n_value)), 0);
	Write(dumpfd, (char *)&clobber, sizeof clobber);
E 10
E 8
E 4
E 2
D 35
	close(dumpfd);
E 35
I 3
D 6
	if (dumptime == 0)
E 6
I 6
D 12
	if (dumptime == 0) {
#ifdef DEBUG
		printf("dump time is 0\n");
#endif
E 6
D 4
		return FALSE;
E 4
I 4
		return 0;
I 6
	}
E 12
I 12
D 16
	if (dumptime == 0)
E 16
I 16
	if (dumptime == 0) {
D 43
		if (Verbose)
E 43
I 43
		if (verbose)
E 43
D 22
			printf("dump time not found\n");
E 22
I 22
D 27
			printf("Dump time not found.\n");
E 27
I 27
			printf("Dump time is zero.\n");
E 51
I 51
	Lseek(dumpfd, (off_t)(dumplo + ok(dump_nl[X_DUMPMAG].n_value)), L_SET);
	(void)Read(dumpfd, &newdumpmag, sizeof(newdumpmag));
	if (newdumpmag != dumpmag) {
D 53
		syslog(LOG_WARNING, "magic number mismatch (%x != %x)",
		    newdumpmag, dumpmag);
E 53
I 53
		if (verbose)
			syslog(LOG_WARNING, "magic number mismatch (%x != %x)",
			    newdumpmag, dumpmag);
E 53
		syslog(LOG_WARNING, "no core dump");
E 51
E 27
E 22
E 16
		return (0);
I 16
	}
E 16
E 12
E 6
E 4
E 3
D 51
	printf("System went down at %s", ctime(&dumptime));
	if (dumptime < now - LEEWAY || dumptime > now + LEEWAY) {
D 22
		printf("Dump time is unreasonable\n");
E 22
I 22
		printf("dump time is unreasonable\n");
E 22
D 4
		return FALSE;
	} else {
D 3
		printf("Dump time ok.\n");
E 3
		return TRUE;
E 4
I 4
D 12
		return 0;
E 12
I 12
		return (0);
E 12
E 4
	}
E 51
I 4
D 12
	return 1;
E 12
I 12
	return (1);
E 12
E 4
}

D 4
/*
 * Put a file name in the proper perspective
 */

char *path(file)
E 4
I 4
D 51
char *
path(file)
	char *file;
E 51
I 51
char buf[1024 * 1024];

void
save_core()
E 51
E 4
{
D 4
	register char *cp = malloc(strlen(file) + strlen(dirname) + 2);
E 4
I 4
D 21
	register char *cp = (char *)malloc(strlen(file) + strlen(dirname) + 2);
E 21
I 21
D 51
	register char *cp = malloc(strlen(file) + strlen(dirname) + 2);
E 51
I 51
	register FILE *fp;
	register int bounds, ifd, nr, nw, ofd;
	char *rawp, path[MAXPATHLEN];
E 51
E 21
E 4

D 4
	strcpy(cp, dirname);
	strcat(cp, "/");
	strcat(cp, file);
E 4
I 4
D 51
	(void) strcpy(cp, dirname);
	(void) strcat(cp, "/");
	(void) strcat(cp, file);
E 4
D 12
	return cp;
E 12
I 12
	return (cp);
E 51
I 51
	/*
	 * Get the current number and update the bounds file.  Do the update
	 * now, because may fail later and don't want to overwrite anything.
	 */
	(void)snprintf(path, sizeof(path), "%s/bounds", dirname);
	if ((fp = fopen(path, "r")) == NULL)
		goto err1;
	if (fgets(buf, sizeof(buf), fp) == NULL) {
		if (ferror(fp))
err1:			syslog(LOG_WARNING, "%s: %s", path, strerror(errno));
		bounds = 0;
	} else
		bounds = atoi(buf);
	if (fp != NULL)
		(void)fclose(fp);
	if ((fp = fopen(path, "w")) == NULL)
		syslog(LOG_ERR, "%s: %m", path);
	else {
		(void)fprintf(fp, "%d\n", bounds + 1);
		(void)fclose(fp);
	}
	(void)fclose(fp);

D 52
goto XXX;
E 52
	/* Create the core file. */
	(void)snprintf(path, sizeof(path), "%s/vmcore.%d%s",
	    dirname, bounds, compress ? ".Z" : "");
	if (compress) {
		if ((fp = zopen(path, "w", 0)) == NULL) {
			syslog(LOG_ERR, "%s: %s", path, strerror(errno));
			exit(1);
		}
	} else
D 54
		ofd = Create(path, S_IRUSR | S_IWUSR);
E 54
I 54
		ofd = Create(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
E 54

	/* Open the raw device. */
	rawp = rawname(ddname);
	if ((ifd = open(rawp, O_RDONLY)) == -1) {
		syslog(LOG_WARNING, "%s: %m; using block device", rawp);
		ifd = dumpfd;
	}

	/* Read the dump size. */
	Lseek(dumpfd, (off_t)(dumplo + ok(dump_nl[X_DUMPSIZE].n_value)), L_SET);
	(void)Read(dumpfd, &dumpsize, sizeof(dumpsize));

	/* Seek to the start of the core. */
	Lseek(ifd, (off_t)dumplo, L_SET);

	/* Copy the core file. */
	dumpsize *= NBPG;
	syslog(LOG_NOTICE, "writing %score to %s",
	    compress ? "compressed " : "", path);
	for (; dumpsize > 0; dumpsize -= nr) {
		(void)printf("%6dK\r", dumpsize / 1024);
		(void)fflush(stdout);
		nr = read(ifd, buf, MIN(dumpsize, sizeof(buf)));
		if (nr <= 0) {
			if (nr == 0)
				syslog(LOG_WARNING,
				    "WARNING: EOF on dump device");
			else
				syslog(LOG_ERR, "%s: %m", rawp);
			goto err2;
		}
		if (compress)
			nw = fwrite(buf, 1, nr, fp);
		else
			nw = write(ofd, buf, nr);
		if (nw != nr) {
			syslog(LOG_ERR, "%s: %s",
			    path, strerror(nw == 0 ? EIO : errno));
err2:			syslog(LOG_WARNING,
			    "WARNING: vmcore may be incomplete");
			(void)printf("\n");
			exit(1);
		}
	}
	(void)printf("\n");
	(void)close(ifd);
	if (compress)
		(void)fclose(fp);
	else 
		(void)close(ofd);

	/* Copy the kernel. */
D 52
XXX:	ifd = Open(vmunix ? vmunix : _PATH_UNIX, O_RDONLY);
E 52
I 52
	ifd = Open(vmunix ? vmunix : _PATH_UNIX, O_RDONLY);
E 52
	(void)snprintf(path, sizeof(path), "%s/vmunix.%d%s",
	    dirname, bounds, compress ? ".Z" : "");
	if (compress) {
		if ((fp = zopen(path, "w", 0)) == NULL) {
			syslog(LOG_ERR, "%s: %s", path, strerror(errno));
			exit(1);
		}
	} else
D 55
		ofd = Create(path, S_IRUSR | S_IWUSR);
E 55
I 55
		ofd = Create(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
E 55
	syslog(LOG_NOTICE, "writing %skernel to %s",
	    compress ? "compressed " : "", path);
	while ((nr = read(ifd, buf, sizeof(buf))) > 0) {
		if (compress)
			nw = fwrite(buf, 1, nr, fp);
		else
			nw = write(ofd, buf, nr);
		if (nw != nr) {
			syslog(LOG_ERR, "%s: %s",
			    path, strerror(nw == 0 ? EIO : errno));
			syslog(LOG_WARNING,
			    "WARNING: vmunix may be incomplete");
			exit(1);
		}
	}
	if (nr < 0) {
		syslog(LOG_ERR, "%s: %s",
		    vmunix ? vmunix : _PATH_UNIX, strerror(errno));
		syslog(LOG_WARNING,
		    "WARNING: vmunix may be incomplete");
		exit(1);
	}
	if (compress)
		(void)fclose(fp);
	else
		(void)close(ofd);
E 51
E 12
}

I 48
D 51
int
E 48
D 4
/*
 * Check to make certain that there is enough space for this dump
 */

E 4
check_space()
E 51
I 51
char *
find_dev(dev, type)
	register dev_t dev;
	register int type;
E 51
{
D 38
	struct stat dsb;
	register char *ddev;
D 8
	register int dfd;
D 10
	struct filsys sblk;
E 10
I 10
D 11
	struct fs sblk;
E 11
E 10
E 8
I 8
D 14
	int dfd, freespace;
E 14
I 14
	int dfd, spacefree;
E 14
	struct fs fs;
E 38
I 38
D 51
	long minfree, spacefree;
	struct statfs fsbuf;
E 51
I 51
	register DIR *dfd;
	struct dirent *dir;
	struct stat sb;
	char *dp, devname[MAXPATHLEN + 1];
E 51
E 38
E 8

D 4
	/*
	 * First find the number of free blocks
	 */
	stat(dirname, &dsb);
E 4
I 4
D 38
	if (stat(dirname, &dsb) < 0) {
E 38
I 38
D 51
	if (statfs(dirname, &fsbuf) < 0) {
E 38
I 25
D 26
		int oerrno = errno;

		perror(dirname);
		errno = oerrno;
E 25
D 22
		perror(dirname);
E 22
I 22
		syslog(LOG_ERR, "%s: %m", dirname);
E 26
I 26
D 37
		Perror(LOG_ERR, "%s: %m", dirname);
E 37
I 37
		Perror(LOG_ERR, "%s: %m\n", dirname);
E 51
I 51
	if ((dfd = opendir(_PATH_DEV)) == NULL) {
		syslog(LOG_ERR, "%s: %s", _PATH_DEV, strerror(errno));
E 51
E 37
E 26
E 22
		exit(1);
	}
E 4
D 38
	ddev = find_dev(dsb.st_dev, S_IFBLK);
D 22
	dfd = Open(ddev, 0);
D 8
D 10
	Lseek(dfd, 1L<<BSHIFT, 0);
E 10
I 10
D 11
	Lseek(dfd, SBLOCK*MAXBSIZE, 0);
E 11
E 10
D 4
	Read(dfd, &sblk, sizeof sblk);
E 4
I 4
	Read(dfd, (char *)&sblk, sizeof sblk);
E 8
I 8
	Lseek(dfd, (long)(SBLOCK * DEV_BSIZE), 0);
	Read(dfd, (char *)&fs, sizeof fs);
E 22
I 22
	dfd = Open(ddev, O_RDONLY);
D 28
	Lseek(dfd, (long)(SBLOCK * DEV_BSIZE), L_SET);
E 28
I 28
	Lseek(dfd, SBOFF, L_SET);
E 28
	Read(dfd, (char *)&fs, sizeof (fs));
E 22
E 8
E 4
	close(dfd);
D 4
	/*
	 * Now check against maximum allowed
	 */
	if (read_number("minfree") > sblk.s_tfree)
	{
		fprintf(stderr, "*** Dump not done, not enough space ***\n");
		return FALSE;
E 4
I 4
D 8
D 10
	if (read_number("minfree") > sblk.s_tfree) {
E 10
I 10
D 11
	if (read_number("minfree") > sblk.fs_cstotal.cs_nbfree) {
E 10
E 8
I 8
	/*
	 * Minimum free space is in terms of kilobytes.
	 * We ignore the "percent free space to be maintained"
	 * parameter in the super block in the believe that a
	 * crash dump is more important than the (temporary)
	 * degradation in performance one might experience.
	 */
	freespace = (fs.fs_cstotal.cs_nbfree * fs.fs_bsize +
			fs.fs_cstotal.cs_nffree * fs.fs_fsize) / 1024;
E 11
I 11
D 14
	freespace = fs.fs_cstotal.cs_nbfree * fs.fs_bsize / 1024;
E 11
	if (read_number("minfree") > freespace) {
E 14
I 14
D 20
	spacefree = fs.fs_cstotal.cs_nbfree * fs.fs_bsize / 1024;
	if (read_number("minfree") > spacefree) {
E 20
I 20
D 22
	spacefree = freespace(&fs, fs.fs_minfree) * fs.fs_fsize / 1024;
	if (spacefree < read_number("minfree")) {
E 20
E 14
E 8
D 12
		fprintf(stderr, "Dump omitted, not enough space on device\n");
E 12
I 12
		fprintf(stderr,
		   "savecore: Dump omitted, not enough space on device\n");
E 22
I 22
 	spacefree = freespace(&fs, fs.fs_minfree) * fs.fs_fsize / 1024;
 	if (spacefree < read_number("minfree")) {
E 38
I 38
D 45
 	spacefree = fsbuf.f_bavail * fsbuf.f_fsize / 1024;
E 45
I 45
D 51
 	spacefree = fsbuf.f_bavail * fsbuf.f_bsize / 1024;
E 45
	minfree = read_number("minfree");
 	if (minfree > 0 && spacefree - dumpsize < minfree) {
E 38
I 25
D 26
		printf("Dump omitted, not enough space on device");
E 25
		syslog(LOG_WARNING, "Dump omitted, not enough space on device");
E 26
I 26
D 29
		log(LOG_WARNING, "Dump omitted, not enough space on device");
E 29
I 29
		log(LOG_WARNING, "Dump omitted, not enough space on device\n");
E 29
E 26
E 22
E 12
		return (0);
E 51
I 51
	(void)strcpy(devname, _PATH_DEV);
	while ((dir = readdir(dfd))) {
		(void)strcpy(devname + sizeof(_PATH_DEV) - 1, dir->d_name);
D 59
		if (stat(devname, &sb)) {
E 59
I 59
		if (lstat(devname, &sb)) {
E 59
			syslog(LOG_ERR, "%s: %s", devname, strerror(errno));
			continue;
		}
		if ((sb.st_mode & S_IFMT) != type)
			continue;
		if (dev == sb.st_rdev) {
			closedir(dfd);
			if ((dp = strdup(devname)) == NULL) {
				syslog(LOG_ERR, "%s", strerror(errno));
				exit(1);
			}
			return (dp);
		}
E 51
E 4
	}
I 8
D 20
	if (fs.fs_cstotal.cs_nbfree * fs.fs_frag + fs.fs_cstotal.cs_nffree <
	    fs.fs_dsize * fs.fs_minfree / 100)
E 20
I 20
D 25
	if (freespace(&fs, fs.fs_minfree) < 0)
E 25
I 25
D 26
	if (freespace(&fs, fs.fs_minfree) < 0) {
		printf("Dump performed, but free space threshold crossed");
E 25
E 20
D 22
		fprintf(stderr,
			"Dump performed, but free space threshold crossed\n");
E 22
I 22
		syslog(LOG_WARNING,
E 26
I 26
D 38
	if (freespace(&fs, fs.fs_minfree) < 0)
E 38
I 38
D 51
	if (spacefree - dumpsize < minfree)
E 38
		log(LOG_WARNING,
E 26
D 29
		    "Dump performed, but free space threshold crossed");
E 29
I 29
		    "Dump performed, but free space threshold crossed\n");
E 29
I 25
D 26
	}
E 26
E 25
E 22
E 8
D 4
	else
		return TRUE;
E 4
I 4
	return (1);
E 51
I 51
	closedir(dfd);
	syslog(LOG_ERR, "can't find device %d/%d", major(dev), minor(dev));
	exit(1);
E 51
E 4
}

I 51
char *
rawname(s)
	char *s;
{
	char *sl, name[MAXPATHLEN];

D 61
	if ((sl = rindex(s, '/')) == NULL || sl[1] == '0') {
E 61
I 61
	if ((sl = strrchr(s, '/')) == NULL || sl[1] == '0') {
E 61
		syslog(LOG_ERR,
		    "can't make raw dump device name from %s", s);
		return (s);
	}
	(void)snprintf(name, sizeof(name), "%.*s/r%s", sl - s, s, sl + 1);
	if ((sl = strdup(name)) == NULL) {
		syslog(LOG_ERR, "%s", strerror(errno));
		exit(1);
	}
	return (sl);
}

E 51
I 48
int
E 48
D 4
/*
 * Read a number from a file
 */

E 4
D 51
read_number(fn)
D 4
char *fn;
E 4
I 4
	char *fn;
E 51
I 51
get_crashtime()
E 51
E 4
{
D 51
	char lin[80];
	register FILE *fp;
E 51
I 51
	time_t dumptime;			/* Time the dump was taken. */
E 51

D 22
	if ((fp = fopen(path(fn), "r")) == NULL)
E 22
I 22
D 51
	fp = fopen(path(fn), "r");
	if (fp == NULL)
E 51
I 51
	Lseek(dumpfd, (off_t)(dumplo + ok(dump_nl[X_TIME].n_value)), L_SET);
	(void)Read(dumpfd, &dumptime, sizeof(dumptime));
	if (dumptime == 0) {
		if (verbose)
			syslog(LOG_ERR, "dump time is zero");
E 51
E 22
D 12
		return 0;
E 12
I 12
		return (0);
E 12
D 4
	else
	{
		if (fgets(lin, 80, fp) == NULL)
		{
			fclose(fp);
			return 0;
		}
		else
		{
			fclose(fp);
			return atoi(lin);
		}
E 4
I 4
D 51
	if (fgets(lin, 80, fp) == NULL) {
D 46
		fclose(fp);
E 46
I 46
		(void)fclose(fp);
E 51
I 51
	}
	(void)printf("savecore: system went down at %s", ctime(&dumptime));
#define	LEEWAY	(7 * SECSPERDAY)
	if (dumptime < now - LEEWAY || dumptime > now + LEEWAY) {
		(void)printf("dump time is unreasonable\n");
E 51
E 46
D 12
		return 0;
E 12
I 12
		return (0);
E 12
E 4
	}
I 4
D 46
	fclose(fp);
E 46
I 46
D 51
	(void)fclose(fp);
E 46
D 12
	return atoi(lin);
E 12
I 12
	return (atoi(lin));
E 51
I 51
	return (1);
E 51
E 12
E 4
}

I 21
D 34
#define	BUFPAGES	(256*1024/NBPG)		/* 1/4 Mb */
E 34
I 34
D 35
#define	BUFSIZE	(256*1024)		/* 1/4 Mb */
E 35
I 35
D 36
#define	BUFPAGES	(256*1024/NBPG)		/* 1/4 Mb */
E 36
I 36
D 51
#define	BUFSIZE		(256*1024)		/* 1/4 Mb */
E 36
E 35
E 34

E 51
I 48
int
E 48
E 21
D 51
save_core()
E 51
I 51
check_space()
E 51
{
D 51
	register int n;
D 4
	char buffer[BUFSIZ];
E 4
I 4
D 21
	char buffer[32*NBPG];
E 4
	register char *cp = buffer;
E 21
I 21
	register char *cp;
E 21
D 48
	register int ifd, ofd, bounds;
I 37
	int ret;
E 48
I 48
	register int ifd, ofd, bounds, ret, stat;
E 48
E 37
I 35
	char *bfile;
E 51
E 35
	register FILE *fp;
I 56
	char *tvmunix;
	off_t minfree, spacefree, vmunixsize, needed;
	struct stat st;
E 56
I 51
	struct statfs fsbuf;
D 56
	off_t minfree, spacefree;
E 56
	char buf[100], path[MAXPATHLEN];
E 51

I 56
	tvmunix = vmunix ? vmunix : _PATH_UNIX;
	if (stat(tvmunix, &st) < 0) {
		syslog(LOG_ERR, "%s: %m", tvmunix);
		exit(1);
	}
	vmunixsize = st.st_blocks * S_BLKSIZE;
E 56
I 21
D 34
	cp = malloc(BUFPAGES*NBPG);
E 34
I 34
D 35
	cp = malloc(BUFSIZE);
E 35
I 35
D 36
	cp = malloc(BUFPAGES*NBPG);
E 36
I 36
D 51
	cp = malloc(BUFSIZE);
E 36
E 35
E 34
D 22
	if (cp == NULL) {
		fprintf(stderr, "can't malloc buffer\n");
E 22
I 22
	if (cp == 0) {
D 35
		fprintf(stderr, "savecore: Can't allocate i/o buffer.\n");
E 35
I 35
		log(LOG_ERR, "savecore: Can't allocate i/o buffer.\n");
E 35
E 22
D 48
		return;
E 48
I 48
		return (0);
E 51
I 51
	if (statfs(dirname, &fsbuf) < 0) {
		syslog(LOG_ERR, "%s: %m", dirname);
		exit(1);
E 51
E 48
	}
E 21
D 51
	bounds = read_number("bounds");
D 4
	/*
	 * Copy the vmunix file
	 */
E 4
D 7
	ifd = Open("/vmunix", 0);
E 7
I 7
D 22
	ifd = Open(system?system:"/vmunix", 0);
E 22
I 22
D 32
	ifd = Open(system?system:"/vmunix", O_RDONLY);
E 32
I 32
D 48
	ifd = Open(system ? system : _PATH_UNIX, O_RDONLY);
E 48
I 48
	ifd = Open(vmunix ? vmunix : _PATH_UNIX, O_RDONLY);
E 48
E 32
E 22
E 7
D 8
D 10
	ofd = Create(path(sprintf(cp, "vmunix.%d", bounds)), 0666);
E 10
I 10
D 30
	sprintf(cp, "vmunix.%d", bounds);
E 30
I 30
	(void)sprintf(cp, "vmunix.%d", bounds);
E 30
	ofd = Create(path(cp), 0644);
E 10
E 8
I 8
D 11
	sprintf(cp, "vmunix.%d", bounds);
	ofd = Create(path(cp), 0644);
E 11
E 8
D 34
	while((n = Read(ifd, cp, BUFSIZ)) > 0)
E 34
I 34
D 35
	while((n = Read(ifd, cp, BUFSIZE)) > 0)
E 35
I 35
D 36
	while((n = Read(ifd, cp, BUFPAGES*NBPG)) > 0)
E 36
I 36
	while((n = Read(ifd, cp, BUFSIZE)) > 0)
E 36
E 35
E 34
		Write(ofd, cp, n);
	close(ifd);
	close(ofd);
D 4
	/*
	 * Make the core file
	 */
E 4
D 22
	ifd = Open(ddname, 0);
I 13
D 16
	Lseek(ifd, (off_t)(dumplo + ok(nl[X_DUMPSIZE].n_value)), 0);
E 16
I 16
	Lseek(ifd, (off_t)(dumplo + ok(dump_nl[X_DUMPSIZE].n_value)), 0);
E 22
I 22
D 35
	ifd = Open(ddname, O_RDONLY);
E 35
I 35
	if ((ifd = open(rawname(ddname), O_RDONLY)) == -1) {
		log(LOG_WARNING, "Can't open %s (%m); using block device",
			rawname(ddname));
		ifd = dumpfd;
E 51
I 51
D 52
 	spacefree = fsbuf.f_bavail * fsbuf.f_bsize / 1024;
E 52
I 52
 	spacefree = (fsbuf.f_bavail * fsbuf.f_bsize) / 1024;
E 52

	(void)snprintf(path, sizeof(path), "%s/minfree", dirname);
	if ((fp = fopen(path, "r")) == NULL)
		minfree = 0;
	else {
		if (fgets(buf, sizeof(buf), fp) == NULL)
			minfree = 0;
		else
			minfree = atoi(buf);
		(void)fclose(fp);
E 51
	}
E 35
D 36
	Lseek(ifd, (off_t)(dumplo + ok(dump_nl[X_DUMPSIZE].n_value)), L_SET);
E 22
E 16
	Read(ifd, (char *)&dumpsize, sizeof (dumpsize));
E 36
I 36
D 51
	Lseek(dumpfd, (off_t)(dumplo + ok(dump_nl[X_DUMPSIZE].n_value)), L_SET);
	Read(dumpfd, (char *)&dumpsize, sizeof (dumpsize));
E 36
E 13
D 8
D 10
	ofd = Create(path(sprintf(cp, "vmcore.%d", bounds)), 0666);
E 10
I 10
D 11
	sprintf(cp, "vmcore.%d", bounds);
	ofd = Create(path(cp), 0644);
E 11
E 10
E 8
I 8
D 30
	sprintf(cp, "vmcore.%d", bounds);
E 30
I 30
	(void)sprintf(cp, "vmcore.%d", bounds);
E 30
	ofd = Create(path(cp), 0644);
E 8
D 4
	Lseek(ifd, dumplo, 0);
D 3
	printf("Vmcore should be %d bytes long\n", NBPG * physmem);
E 3
I 3
	printf("Saving %d bytes of image in vmcore.%d\n",
	    NBPG * physmem, bounds);
E 3
	while(physmem > 0)
	{
		n = Read(ifd, cp, BUFSIZ);
E 4
I 4
D 22
	Lseek(ifd, (off_t)dumplo, 0);
E 22
I 22
	Lseek(ifd, (off_t)dumplo, L_SET);
I 36
	dumpsize *= NBPG;
E 36
E 22
D 12
	printf("Saving %d bytes of image in vmcore.%d\n", NBPG*physmem, bounds);
	while(physmem > 0) {
		n = Read(ifd, cp, (physmem > 32 ? 32 : physmem) * NBPG);
E 12
I 12
D 26
	printf("Saving %d bytes of image in vmcore.%d\n", NBPG*dumpsize,
		bounds);
I 25
	syslog(LOG_NOTICE, "Saving %d bytes of image in vmcore.%d\n",
		NBPG*dumpsize, bounds);
E 26
I 26
	log(LOG_NOTICE, "Saving %d bytes of image in vmcore.%d\n",
D 36
	    NBPG*dumpsize, bounds);
E 36
I 36
	    dumpsize, bounds);
I 48
	stat = 1;
E 48
E 36
E 26
E 25
	while (dumpsize > 0) {
D 21
		n = Read(ifd, cp, (dumpsize > 32 ? 32 : dumpsize) * NBPG);
E 21
I 21
D 36
		n = Read(ifd, cp,
D 22
			(dumpsize > BUFPAGES ? BUFPAGES : dumpsize) * NBPG);
E 22
I 22
		    (dumpsize > BUFPAGES ? BUFPAGES : dumpsize) * NBPG);
E 22
E 21
I 19
		if (n == 0) {
D 25
			printf("WARNING: core may be incomplete\n");
E 25
I 25
D 26
			syslog(LOG_WARNING,
			    "WARNING: vmcore may be incomplete\n");
			printf("WARNING: vmcore may be incomplete\n");
E 26
I 26
D 29
			log(LOG_WARNING, "WARNING: vmcore may be incomplete");
E 29
I 29
			log(LOG_WARNING, "WARNING: vmcore may be incomplete\n");
E 36
I 36
D 48
		n = read(ifd, cp,
		    dumpsize > BUFSIZE ? BUFSIZE : dumpsize);
E 48
I 48
		n = read(ifd, cp, dumpsize > BUFSIZE ? BUFSIZE : dumpsize);
E 48
		if (n <= 0) {
			if (n == 0)
				log(LOG_WARNING,
D 37
				    "WARNING: vmcore may be incomplete\n");
E 37
I 37
				    "WARNING: EOF on dump device; %s\n",
				    "vmcore may be incomplete");
E 37
			else
D 37
				Perror(LOG_ERR, "read: %m", "read");
E 37
I 37
				Perror(LOG_ERR, "read from dumpdev: %m",
				    "read");
I 48
			stat = 0;
E 48
E 37
E 36
E 29
E 26
E 25
			break;
		}
E 19
E 12
E 4
D 37
		Write(ofd, cp, n);
E 37
I 37
		if ((ret = write(ofd, cp, n)) < n) {
			if (ret < 0)
				Perror(LOG_ERR, "write: %m", "write");
			else
				log(LOG_ERR, "short write: wrote %d of %d\n",
				    ret, n);
			log(LOG_WARNING, "WARNING: vmcore may be incomplete\n");
I 48
			stat = 0;
E 48
			break;
		}
E 37
D 12
		physmem -= n/NBPG;
E 12
I 12
D 36
		dumpsize -= n/NBPG;
E 36
I 36
		dumpsize -= n;
I 48
		(void)fprintf(stderr, "%6dK\r", dumpsize / 1024);
E 51
I 51

D 56
 	if (minfree > 0 && spacefree - dumpsize < minfree) {
E 56
I 56
D 58
	needed = dumpsize + vmunixsize;
E 58
I 58
	needed = (dumpsize + vmunixsize) / 1024;
E 58
 	if (minfree > 0 && spacefree - needed < minfree) {
E 56
		syslog(LOG_WARNING,
		    "no dump, not enough free space on device");
		return (0);
E 51
E 48
E 36
E 12
	}
I 48
D 51
	fputc('\n', stderr);
E 48
	close(ifd);
	close(ofd);
D 35
	fp = fopen(path("bounds"), "w");
	fprintf(fp, "%d\n", bounds+1);
	fclose(fp);
E 35
I 35
	bfile = path("bounds");
	fp = fopen(bfile, "w");
	if (fp) {
D 46
		fprintf(fp, "%d\n", bounds+1);
		fclose(fp);
E 46
I 46
		(void)fprintf(fp, "%d\n", bounds+1);
		(void)fclose(fp);
E 46
	} else
		Perror(LOG_ERR, "Can't create bounds file %s: %m", bfile);
E 35
I 21
	free(cp);
I 48
	return (stat);
E 51
I 51
D 56
	if (spacefree - dumpsize < minfree)
E 56
I 56
	if (spacefree - needed < minfree)
E 56
		syslog(LOG_WARNING,
		    "dump performed, but free space threshold crossed");
	return (1);
E 51
E 48
E 21
D 24
}

D 22
char *days[] = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

E 22
I 22
char *days[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
E 22
char *months[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep",
	"Oct", "Nov", "Dec"
};

log_entry()
{
	FILE *fp;
	struct tm *tm, *localtime();

D 22
	tm = localtime(&now);
E 22
D 4
	fp = fopen(SHUTDOWNLOG, "a");
E 4
I 4
	fp = fopen("/usr/adm/shutdownlog", "a");
	if (fp == 0)
		return;
E 4
D 22
	fseek(fp, 0L, 2);
E 22
I 22
	tm = localtime(&now);
	fseek(fp, 0L, L_XTND);
E 22
	fprintf(fp, "%02d:%02d  %s %s %2d, %4d.  Reboot", tm->tm_hour,
		tm->tm_min, days[tm->tm_wday], months[tm->tm_mon],
		tm->tm_mday, tm->tm_year + 1900);
	if (panicstr)
D 4
		fprintf(fp, " -- panic %s\n", panic_mesg);
E 4
I 4
		fprintf(fp, " after panic: %s\n", panic_mesg);
E 4
	else
		putc('\n', fp);
	fclose(fp);
E 24
I 4
}

D 51
/*
 * Versions of std routines that exit on error.
 */
E 51
I 48
int
E 48
D 22

E 22
Open(name, rw)
	char *name;
	int rw;
{
	int fd;

D 22
	if ((fd = open(name, rw)) < 0) {
		perror(name);
E 22
I 22
D 51
	fd = open(name, rw);
	if (fd < 0) {
I 25
D 26
		int oerrno = errno;

		perror(name);
		errno = oerrno;
E 25
		syslog(LOG_ERR, "%s: %m", name);
E 26
I 26
		Perror(LOG_ERR, "%s: %m", name);
E 51
I 51
	if ((fd = open(name, rw, 0)) < 0) {
		syslog(LOG_ERR, "%s: %m", name);
E 51
E 26
E 22
		exit(1);
	}
D 22
	return fd;
E 22
I 22
	return (fd);
E 22
}

I 48
int
E 48
D 51
Read(fd, buff, size)
D 48
	int fd, size;
E 48
I 48
	int fd;
E 48
	char *buff;
I 48
	int size;
E 51
I 51
Read(fd, bp, size)
	int fd, size;
	void *bp;
E 51
E 48
{
D 51
	int ret;
E 51
I 51
	int nr;
E 51

D 22
	if ((ret = read(fd, buff, size)) < 0) {
		perror("read");
E 22
I 22
D 51
	ret = read(fd, buff, size);
	if (ret < 0) {
I 25
D 26
		int oerrno = errno;

		perror("read");
		errno = oerrno;
E 25
		syslog(LOG_ERR, "read: %m");
E 26
I 26
D 35
		Perror(LOG_ERR, "read: %m");
E 35
I 35
		Perror(LOG_ERR, "read: %m", "read");
E 51
I 51
	nr = read(fd, bp, size);
	if (nr != size) {
		syslog(LOG_ERR, "read: %m");
E 51
E 35
E 26
E 22
		exit(1);
	}
D 22
	return ret;
E 22
I 22
D 51
	return (ret);
E 51
I 51
	return (nr);
E 51
E 22
}

D 47
off_t
E 47
I 47
void
E 47
Lseek(fd, off, flag)
D 48
	int fd, flag;
E 48
I 48
D 51
	int fd;
E 51
I 51
	int fd, flag;
E 51
E 48
D 47
	long off;
E 47
I 47
	off_t off;
I 48
D 51
	int flag;
E 51
E 48
E 47
{
D 51
	long ret;
E 51
I 51
	off_t ret;
E 51

D 22
	if ((ret = lseek(fd, off, flag)) == -1L) {
		perror("lseek");
E 22
I 22
D 48
	ret = lseek(fd, off, flag);
E 48
I 48
D 51
	ret = lseek(fd, (off_t)off, flag);
E 51
I 51
	ret = lseek(fd, off, flag);
E 51
E 48
	if (ret == -1) {
I 25
D 26
		int oerrno = errno;

		perror("lseek");
		errno = oerrno;
E 25
		syslog(LOG_ERR, "lseek: %m");
E 26
I 26
D 35
		Perror(LOG_ERR, "lseek: %m");
E 35
I 35
D 51
		Perror(LOG_ERR, "lseek: %m", "lseek");
E 51
I 51
		syslog(LOG_ERR, "lseek: %m");
E 51
E 35
E 26
E 22
		exit(1);
	}
D 22
	return ret;
E 22
I 22
D 47
	return (ret);
E 47
E 22
}

I 48
int
E 48
Create(file, mode)
	char *file;
	int mode;
{
	register int fd;

D 22
	if ((fd = creat(file, mode)) < 0) {
		perror(file);
E 22
I 22
D 61
	fd = creat(file, mode);
E 61
I 61
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, mode);
E 61
	if (fd < 0) {
I 25
D 26
		int oerrno = errno;

		perror(file);
		errno = oerrno;
E 25
		syslog(LOG_ERR, "%s: %m", file);
E 26
I 26
D 51
		Perror(LOG_ERR, "%s: %m", file);
E 51
I 51
		syslog(LOG_ERR, "%s: %m", file);
E 51
E 26
E 22
		exit(1);
	}
D 22
	return fd;
E 22
I 22
	return (fd);
E 22
}

I 48
void
E 48
D 51
Write(fd, buf, size)
D 48
	int fd, size;
E 48
I 48
	int fd;
E 48
	char *buf;
I 48
	int size;
E 51
I 51
Write(fd, bp, size)
	int fd, size;
	void *bp;
E 51
E 48
D 13

E 13
{
I 37
	int n;
E 37

D 37
	if (write(fd, buf, size) < size) {
I 25
D 26
		int oerrno = errno;

		perror("write");
		errno = oerrno;
E 25
D 22
		perror("write");
E 22
I 22
		syslog(LOG_ERR, "write: %m");
E 26
I 26
D 35
		Perror(LOG_ERR, "write: %m");
E 35
I 35
		Perror(LOG_ERR, "write: %m", "write");
E 37
I 37
D 51
	if ((n = write(fd, buf, size)) < size) {
		if (n < 0)
			Perror(LOG_ERR, "write: %m", "write");
		else
			log(LOG_ERR, "short write: wrote %d of %d\n", n, size);
E 51
I 51
	if ((n = write(fd, bp, size)) < size) {
		syslog(LOG_ERR, "write: %s", strerror(n == -1 ? errno : EIO));
E 51
E 37
E 35
E 26
E 22
		exit(1);
	}
I 26
}

I 35
D 50
/* VARARGS2 */
E 50
I 50
D 51
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

E 51
E 50
E 35
D 48
log(level, msg, a1, a2)
E 48
I 48
void
D 51
#if __STDC__
log(int level, char *fmt, ...)
#else
log(level, fmt, va_alist)
E 48
	int level;
D 48
	char *msg;
E 48
I 48
	char *fmt;
	va_dcl
#endif
E 48
{
I 48
	va_list ap;
E 48

D 46
	fprintf(stderr, msg, a1, a2);
E 46
I 46
D 48
	(void)fprintf(stderr, msg, a1, a2);
E 46
	syslog(level, msg, a1, a2);
E 48
I 48
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif

	(void)vfprintf(stderr, fmt, ap);
	vsyslog(level, fmt, ap);
	va_end(ap);
E 48
}

I 48
void
E 48
Perror(level, msg, s)
	int level;
D 42
	char *msg;
E 42
I 42
	char *msg, *s;
E 42
{
	int oerrno = errno;
	
	perror(s);
	errno = oerrno;
	syslog(level, msg, s);
I 43
}

I 48
void
E 51
E 48
usage()
{
D 51
	(void)fprintf(stderr, "usage: savecore [-cfv] dirname [system]\n");
E 51
I 51
D 52
	(void)syslog(LOG_ERR, "usage: savecore [-cfv] dirname [system]");
E 52
I 52
	(void)syslog(LOG_ERR, "usage: savecore [-cfvz] [-N system] directory");
E 52
E 51
	exit(1);
E 43
E 26
E 4
}
I 10
D 12


E 10
I 8


E 12
E 8
E 1
