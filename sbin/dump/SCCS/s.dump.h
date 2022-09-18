h22088
s 00003/00002/00184
d D 8.2 95/04/28 10:29:23 bostic 38 37
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/00184
d D 8.1 93/06/05 10:52:36 bostic 37 36
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00005/00169
d D 5.23 93/05/11 14:02:42 torek 36 35
c control for honoring UF_NODUMP; fixups for compat code; lint
e
s 00009/00002/00165
d D 5.22 93/01/25 15:36:04 mckusick 35 34
c cleanups from leres@lbl
e
s 00021/00036/00146
d D 5.21 92/07/16 12:39:53 bostic 34 33
c fix the prototypes, minor cleanup to signal handlers
e
s 00001/00001/00181
d D 5.20 92/07/02 16:19:45 mckusick 33 32
c new function prototype
e
s 00059/00044/00123
d D 5.19 92/06/18 19:03:26 mckusick 32 31
c lint; add parametric functions
e
s 00007/00001/00160
d D 5.18 91/07/29 13:14:40 torek 31 30
c ANSI varargs, for sparc among others
e
s 00001/00001/00160
d D 5.17 91/07/23 21:09:16 mckusick 30 29
c use POSIX constant NAME_MAX rather than MAXNAMLEN from dir.h
e
s 00001/00002/00160
d D 5.16 91/05/29 19:29:52 mckusick 29 28
c update for new header files
e
s 00005/00004/00157
d D 5.15 91/03/07 17:50:02 mckusick 28 27
c verified to be free of AT&T code
e
s 00000/00001/00161
d D 5.14 91/03/07 12:01:16 mckusick 27 26
c lint, misc cleanups
e
s 00000/00004/00162
d D 5.13 91/03/01 10:43:46 bostic 26 25
c use tzfile.h seconds #defines instead of our own
e
s 00012/00000/00154
d D 5.12 91/02/28 22:25:47 mckusick 25 24
c add defines to provide compatibility with 4.3BSD-Tahoe systems
e
s 00000/00015/00154
d D 5.11 91/02/28 19:33:47 bostic 24 23
c ANSI; break #includes out of dump.h into separate files
e
s 00050/00051/00119
d D 5.10 91/02/28 18:52:23 mckusick 23 22
c more neumonic names; get rid of unnecessary global names
e
s 00063/00028/00107
d D 5.9 91/02/23 16:16:06 torek 22 21
c fix gcc warnings; add dev_bshift and tp_bshift variables
e
s 00002/00004/00133
d D 5.8 90/02/15 13:27:50 mckusick 21 20
c just need dinode.h, not vnode, inode, etc; want ufs/dir.h not sys/dir.h
e
s 00004/00003/00133
d D 5.7 89/09/12 17:32:50 mckusick 20 19
c new pathname locations
e
s 00003/00005/00133
d D 5.6 89/05/11 13:52:30 bostic 19 18
c file reorg, pathnames.h, paths.h
e
s 00001/00004/00137
d D 5.5 89/04/02 12:31:34 bostic 18 17
c add pathnames.h
e
s 00001/00000/00140
d D 5.4 87/02/23 17:57:06 mckusick 17 16
c generalize dev_bsize
e
s 00001/00001/00139
d D 5.3 86/05/23 10:57:02 mckusick 16 15
c use standard exit codes
e
s 00001/00001/00139
d D 5.2 85/06/18 21:06:52 mckusick 15 14
c dumpretore.h moves into protocols
e
s 00007/00001/00133
d D 5.1 85/06/05 08:49:58 dist 14 13
c Add copyright
e
s 00001/00000/00133
d D 1.13 84/10/05 15:56:20 mckusick 13 12
c maintain consistent dump tapes on active systems (decvax!watmath!srradia)
e
s 00003/00004/00130
d D 1.12 83/07/01 23:55:27 sam 12 11
c include fix
e
s 00001/00001/00133
d D 1.11 83/07/01 03:06:32 sam 11 10
c include fix
e
s 00003/00006/00131
d D 1.10 83/06/15 15:06:12 sam 10 9
c from kirk; handle locking of dumpdates data base
e
s 00000/00004/00137
d D 1.9 83/06/12 16:15:13 sam 9 8
c new fstab format
e
s 00001/00000/00140
d D 1.8 83/05/08 19:11:14 mckusick 8 7
c add ability to dump to standard output
e
s 00006/00000/00134
d D 1.7 82/10/07 19:28:11 mckusick 7 6
c move struct itime out of dumprestor.h into dump.h
e
s 00005/00005/00129
d D 1.6 82/05/07 15:27:42 sam 6 5
c old stuff
e
s 00000/00003/00134
d D 1.5 82/02/23 12:56:42 mckusic 5 4
c convert to new directory format
e
s 00013/00007/00124
d D 1.4 82/01/05 01:37:05 mckusic 4 3
c parameterize BSIZE, FSIZE, and FRAG into fs_bsize, fs_fsize, and fs_frag
e
s 00001/00001/00130
d D 1.3 81/11/07 14:53:02 mckusic 3 2
c dump to "standard" (ie 1K file system) dump tapes
e
s 00007/00007/00124
d D 1.2 81/10/31 18:29:53 mckusic 2 1
c 8K only dump/restor
e
s 00131/00000/00000
d D 1.1 80/10/13 17:30:23 root 1 0
c date and time created 80/10/13 17:30:23 by root
e
u
U
t
T
I 1
D 12
/*
 * "%W% (Berkeley) %G%"
 */
E 12
I 12
D 14
/*	%M%	%I%	%E%	*/
E 14
I 14
D 28
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 28
I 28
/*-
D 37
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 37
I 37
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 37
 *
 * %sccs.include.redist.c%
E 28
 *
 *	%W% (Berkeley) %G%
 */
E 14

E 12
D 4
#define	NI	16
#define	DIRPB	(BSIZE/sizeof(struct direct))
E 4
I 4
D 27
#define	NI		16
E 27
D 5
#define	DIRPB(fs)	((fs)->fs_bsize / sizeof(struct direct))
#define	MAXDIRPB	(MAXBSIZE / sizeof(struct direct))
E 5
#define MAXINOPB	(MAXBSIZE / sizeof(struct dinode))
#define MAXNINDIR	(MAXBSIZE / sizeof(daddr_t))
E 4

D 19
#include <stdio.h>
#include <ctype.h>
E 19
D 2
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/filsys.h>
#include <sys/ino.h>
#include <sys/inode.h>
#include <sys/fblk.h>
#include <sys/dir.h>
E 2
I 2
D 6
#include "../../h/param.h"
#include "../../h/stat.h"
#include "../../h/fs.h"
#include "../../h/inode.h"
D 5
#include "../../h/dir.h"
E 5
I 3
#include "../../h/dumprestor.h"
E 6
I 6
D 24
#include <sys/param.h>
#include <sys/stat.h>
I 22
#include <sys/time.h>
E 22
D 20
#include <sys/fs.h>
#include <sys/inode.h>
E 20
I 20
D 21
#include <sys/time.h>
E 21
#include <ufs/fs.h>
D 21
#include <sys/vnode.h>
#include <ufs/inode.h>
E 21
I 21
#include <ufs/dinode.h>
E 21
E 20
D 15
#include <dumprestor.h>
E 15
I 15
D 22
#include <protocols/dumprestore.h>
E 22
E 15
I 7
D 11
#include <dir.h>
E 11
I 11
D 21
#include <sys/dir.h>
E 21
I 21
#include <ufs/dir.h>
I 22
#include <protocols/dumprestore.h>
E 22
E 21
E 11
E 7
E 6
E 3
E 2
#include <utmp.h>
D 12
#include <time.h>
E 12
I 12
D 20
#include <sys/time.h>
E 20
E 12
D 19
#include <signal.h>
E 19
I 19
D 22
#include <sys/signal.h>
E 22
I 22
#include <signal.h>
E 22
E 19
I 2
D 9
int (*signal())();
E 9
E 2
D 3
#include <dumprestor.h>
E 3
#include <fstab.h>
I 19
#include <stdio.h>
I 22
#include <stdlib.h>
#include <string.h>
E 22
#include <ctype.h>
E 19

E 24
D 4
#define	MWORD(m,i)	(m[(unsigned)(i-1)/MLEN])
#define	MBIT(i)		(1<<((unsigned)(i-1)%MLEN))
E 4
I 4
D 23
#define	MWORD(m,i)	(m[(unsigned)(i-1)/NBBY])
#define	MBIT(i)		(1<<((unsigned)(i-1)%NBBY))
E 4
#define	BIS(i,w)	(MWORD(w,i) |=  MBIT(i))
#define	BIC(i,w)	(MWORD(w,i) &= ~MBIT(i))
#define	BIT(i,w)	(MWORD(w,i) & MBIT(i))
E 23
I 23
/*
 * Dump maps used to describe what is to be dumped.
 */
int	mapsize;	/* size of the state maps */
char	*usedinomap;	/* map of allocated inodes */
char	*dumpdirmap;	/* map of directories to be dumped */
char	*dumpinomap;	/* map of files to be dumped */
/*
 * Map manipulation macros.
 */
#define	SETINO(ino, map) \
	map[(u_int)((ino) - 1) / NBBY] |=  1 << ((u_int)((ino) - 1) % NBBY)
#define	CLRINO(ino, map) \
	map[(u_int)((ino) - 1) / NBBY] &=  ~(1 << ((u_int)((ino) - 1) % NBBY))
#define	TSTINO(ino, map) \
	(map[(u_int)((ino) - 1) / NBBY] &  (1 << ((u_int)((ino) - 1) % NBBY)))
E 23

D 4
short	clrmap[MSIZ];
short	dirmap[MSIZ];
short	nodmap[MSIZ];
E 4
I 4
D 23
int	msiz;
char	*clrmap;
char	*dirmap;
char	*nodmap;
E 4

E 23
/*
 *	All calculations done in 0.1" units!
 */
D 23

E 23
char	*disk;		/* name of the disk file */
char	*tape;		/* name of the tape file */
D 23
char	*increm;	/* name of the file containing incremental information*/
I 10
char	*temp;		/* name of the file for doing rewrite of increm */
char	lastincno;	/* increment number of previous dump */
E 10
char	incno;		/* increment number */
E 23
I 23
char	*dumpdates;	/* name of the file containing dump date information*/
char	*temp;		/* name of the file for doing rewrite of dumpdates */
char	lastlevel;	/* dump level of previous dump */
char	level;		/* dump level of this dump */
E 23
int	uflag;		/* update flag */
D 23
int	fi;		/* disk file descriptor */
int	to;		/* tape file descriptor */
E 23
I 23
int	diskfd;		/* disk file descriptor */
int	tapefd;		/* tape file descriptor */
E 23
I 8
int	pipeout;	/* true => output to standard output */
E 8
D 23
ino_t	ino;		/* current inumber; used globally */
int	nsubdir;
E 23
I 23
ino_t	curino;		/* current inumber; used globally */
E 23
int	newtape;	/* new tape flag */
D 23
int	nadded;		/* number of added sub directories */
int	dadded;		/* directory added flag */
E 23
int	density;	/* density in 0.1" units */
I 23
long	tapesize;	/* estimated tape size, blocks */
E 23
long	tsize;		/* tape size in 0.1" units */
D 23
long	esize;		/* estimated tape size, blocks */
E 23
long	asize;		/* number of 0.1" units written on current tape */
int	etapes;		/* estimated number of tapes */
I 36
int	nonodump;	/* if set, do not honor UF_NODUMP user flags */
E 36

int	notify;		/* notify operator flag */
int	blockswritten;	/* number of blocks written on current tape */
int	tapeno;		/* current tape number */
time_t	tstart_writing;	/* when started writing the first tape block */
D 32
char	*processname;
E 32
I 4
D 23
struct fs *sblock;	/* the file system super block */
E 23
I 23
struct	fs *sblock;	/* the file system super block */
E 23
D 32
char	buf[MAXBSIZE];
E 32
I 32
char	sblock_buf[MAXBSIZE];
E 32
I 17
D 22
long	dev_bsize;
E 22
I 22
long	dev_bsize;	/* block size of underlying disk device */
int	dev_bshift;	/* log2(dev_bsize) */
int	tp_bshift;	/* log2(TP_BSIZE) */
E 22
E 17
E 4

I 36
#ifndef __P
#include <sys/cdefs.h>
#endif

E 36
D 22
char	*ctime();
E 22
I 22
/* operator interface functions */
D 32
void	broadcast();
void	lastdump();
E 32
I 32
void	broadcast __P((char *message));
void	lastdump __P((int arg));	/* int should be char */
D 34
time_t	unctime __P((char *str));
E 32
I 31
#if __STDC__
void	msg(const char *fmt, ...);
void	msgtail(const char *fmt, ...);
void	quit(const char *fmt, ...);
#else
E 31
void	msg();
void	msgtail();
I 31
void	quit();
#endif
E 34
I 34
void	msg __P((const char *fmt, ...));
void	msgtail __P((const char *fmt, ...));
E 34
E 31
D 32
int	query();
void	set_operators();
void	timeest();
E 32
I 32
int	query __P((char *question));
D 34
void	set_operators __P(());
void	timeest __P(());
E 34
I 34
void	quit __P((const char *fmt, ...));
void	set_operators __P((void));
void	timeest __P((void));
time_t	unctime __P((char *str));
E 34
E 32

/* mapping rouintes */
D 23
void	est();
void	bmapest();
void	pass();
void	mark();
void	add();
E 23
I 23
D 32
long	blockest();
int	mapfiles();
int	mapdirs();
E 32
I 32
struct	dinode;
long	blockest __P((struct dinode *dp));
int	mapfiles __P((ino_t maxino, long *tapesize));
int	mapdirs __P((ino_t maxino, long *tapesize));
E 32
E 23

/* file dumping routines */
D 32
void	dirdump();
D 23
void	dump();
E 23
void	blksout();
D 23
void	bitmap();
void	spclrec();
E 23
I 23
void	dumpmap();
void	writeheader();
E 23
void	bread();
E 32
I 32
D 34
void	dumpino __P((struct dinode *dp, ino_t ino));
E 34
void	blksout __P((daddr_t *blkp, int frags, ino_t ino));
I 34
void	bread __P((daddr_t blkno, char *buf, int size));	
void	dumpino __P((struct dinode *dp, ino_t ino));
E 34
void	dumpmap __P((char *map, int type, ino_t ino));
void	writeheader __P((ino_t ino));
D 34
void	bread __P((daddr_t blkno, char *buf, int size));	
E 34
E 32

/* tape writing routines */
D 32
int	alloctape();
D 23
void	taprec();
void	dmpblk();
void	tflush();
E 23
I 23
void	writerec();
void	dumpblock();
void	flushtape();
E 23
void	trewind();
void	close_rewind();
D 23
void	otape();
E 23
I 23
void	startnewtape();
E 32
I 32
D 34
int	alloctape __P(());
D 33
void	writerec __P((char *dp));
E 33
I 33
void	writerec __P((char *dp, int isspcl));
E 34
I 34
int	alloctape __P((void));
void	close_rewind __P((void));
E 34
E 33
void	dumpblock __P((daddr_t blkno, int size));
D 34
void	flushtape __P(());
void	trewind __P(());
void	close_rewind __P(());
void	startnewtape __P(());
E 34
I 34
D 35
void	flushtape __P((void));
E 35
void	startnewtape __P((int top));
void	trewind __P((void));
void	writerec __P((char *dp, int isspcl));
E 34
E 32
E 23

D 32
void	dumpabort();
void	Exit();
void	getfstab();
E 32
I 32
D 34
void	dumpabort __P(());
E 34
D 36
void	Exit __P((int status));
E 36
I 36
__dead void Exit __P((int status));
E 36
D 34
void	getfstab __P(());
E 34
I 34
void	dumpabort __P((int signo));
void	getfstab __P((void));
E 34
E 32
D 31
void	quit();
E 31

E 22
D 23
char	*prdate();
E 23
D 22
long	atol();
int	mark();
int	add();
I 13
int	dirdump();
E 13
int	dump();
int	tapsrec();
int	dmpspc();
int	dsrch();
int	nullf();
char	*getsuffix();
E 22
D 32
char	*rawname();
I 2
struct dinode *getino();
E 32
I 32
char	*rawname __P((char *cp));
struct	dinode *getino __P((ino_t inum));
E 32
E 2

I 35
/* rdump routines */
#ifdef RDUMP
void	rmtclose __P((void));
int	rmthost __P((char *host));
int	rmtopen __P((char *tape, int mode));
int	rmtwrite __P((char *buf, int count));
#endif /* RDUMP */

E 35
D 22
int	interrupt();		/* in case operator bangs on console */
E 22
I 22
D 32
void	interrupt();		/* in case operator bangs on console */
E 32
I 32
D 34
void	interrupt __P(());	/* in case operator bangs on console */
E 34
I 34
void	interrupt __P((int signo));	/* in case operator bangs on console */
E 34
E 32
E 22

D 26
#define	HOUR	(60L*60L)
#define	DAY	(24L*HOUR)
#define	YEAR	(365L*DAY)

E 26
/*
 *	Exit status codes
 */
D 16
#define	X_FINOK		1	/* normal exit */
E 16
I 16
#define	X_FINOK		0	/* normal exit */
E 16
#define	X_REWRITE	2	/* restart writing from the check point */
D 32
#define	X_ABORT		3	/* abort all of dump; don't attempt checkpointing*/
E 32
I 32
#define	X_ABORT		3	/* abort dump; don't attempt checkpointing */
E 32

D 10
#ifdef DEBUG
#define	OINCREM	"./ddate"		/*old format incremental info*/
#define	NINCREM	"./dumpdates"		/*new format incremental info*/
#else not DEBUG
#define	OINCREM	"/etc/ddate"		/*old format incremental info*/
E 10
D 18
#define	NINCREM	"/etc/dumpdates"	/*new format incremental info*/
D 10
#endif
E 10
I 10
#define	TEMP	"/etc/dtmp"		/*output temp file*/
E 10

E 18
D 19
#define	TAPE	"/dev/rmt8"		/* default tape device */
#define	DISK	"/dev/rrp1g"		/* default disk */
E 19
#define	OPGRENT	"operator"		/* group entry to notify */
#define DIALUP	"ttyd"			/* prefix for dialups */

D 9
#define	MAXFSTAB		32
struct	fstab	fstab[MAXFSTAB];
E 9
D 32
struct	fstab	*fstabsearch();	/* search in fs_file and fs_spec */
E 32
I 32
struct	fstab *fstabsearch __P((char *key));	/* search fs_file and fs_spec */
E 32
D 9
int	nfstab;
E 9

I 32
#ifndef NAME_MAX
#define NAME_MAX 255
#endif

E 32
/*
D 18
 *	The contents of the file NINCREM is maintained both on
E 18
I 18
 *	The contents of the file _PATH_DUMPDATES is maintained both on
E 18
 *	a linked list, and then (eventually) arrayified.
 */
I 7
D 23
struct	idates {
	char	id_name[MAXNAMLEN+3];
	char	id_incno;
	time_t	id_ddate;
E 23
I 23
struct dumpdates {
D 30
	char	dd_name[MAXNAMLEN+3];
E 30
I 30
	char	dd_name[NAME_MAX+3];
E 30
	char	dd_level;
	time_t	dd_ddate;
E 23
};
E 7
D 22
struct	itime{
E 22
I 22
D 23
struct	itime {
E 22
	struct	idates	it_value;
	struct	itime	*it_next;
E 23
I 23
struct dumptime {
	struct	dumpdates dt_value;
	struct	dumptime *dt_next;
E 23
};
D 23
struct	itime	*ithead;	/* head of the list version */
int	nidates;		/* number of records (might be zero) */
int	idates_in;		/* we have read the increment file */
struct	idates	**idatev;	/* the arrayfied version */
D 22
#define	ITITERATE(i, ip) for (i = 0,ip = idatev[0]; i < nidates; i++, ip = idatev[i])
E 22
I 22
void	inititimes();
void	getitime();
void	putitime();
#define	ITITERATE(i, ip) for (ip = idatev[i = 0]; i < nidates; ip = idatev[++i])
E 23
I 23
struct	dumptime *dthead;	/* head of the list version */
int	nddates;		/* number of records (might be zero) */
int	ddates_in;		/* we have read the increment file */
struct	dumpdates **ddatev;	/* the arrayfied version */
D 32
void	initdumptimes();
void	getdumptime();
void	putdumptime();
E 32
I 32
D 34
void	initdumptimes __P(());
void	getdumptime __P(());
void	putdumptime __P(());
E 34
I 34
void	initdumptimes __P((void));
void	getdumptime __P((void));
void	putdumptime __P((void));
E 34
E 32
#define	ITITERATE(i, ddp) \
	for (ddp = ddatev[i = 0]; i < nddates; ddp = ddatev[++i])
E 23
E 22

D 34
/*
 *	We catch these interrupts
 */
D 22
int	sighup();
int	sigquit();
int	sigill();
int	sigtrap();
int	sigfpe();
int	sigkill();
int	sigbus();
int	sigsegv();
int	sigsys();
int	sigalrm();
int	sigterm();
E 22
I 22
D 32
void	sighup();
void	sigquit();
void	sigill();
void	sigtrap();
void	sigfpe();
void	sigkill();
void	sigbus();
void	sigsegv();
void	sigsys();
void	sigalrm();
void	sigterm();
E 32
I 32
void	sighup __P(());
void	sigtrap __P(());
void	sigfpe __P(());
void	sigbus __P(());
void	sigsegv __P(());
void	sigalrm __P(());
void	sigterm __P(());
E 34
I 34
void	sig __P((int signo));
E 34
E 32
I 25

/*
 * Compatibility with old systems.
 */
D 36
#ifndef __STDC__
E 36
I 36
#ifdef COMPAT
E 36
#include <sys/file.h>
D 36
#define _PATH_FSTAB	"/etc/fstab"
D 29
typedef int (*sig_t)();
extern char *strdup();
E 29
I 29
extern char *index(), *strdup();
E 36
I 36
D 38
extern char *index(), *rindex(), *strdup();
E 36
E 29
extern char *ctime();
E 38
I 38
#define	strchr(a,b)	index(a,b)
#define	strrchr(a,b)	rindex(a,b)
extern char *strdup(), *ctime();
E 38
I 36
extern int read(), write();
E 36
extern int errno;
I 32
#endif

I 36
#ifndef	_PATH_UTMP
#define	_PATH_UTMP	"/etc/utmp"
#endif
#ifndef	_PATH_FSTAB
#define	_PATH_FSTAB	"/etc/fstab"
#endif

E 36
#ifdef sunos
extern char *calloc();
extern char *malloc();
extern long atol();
extern char *strcpy();
extern char *strncpy();
extern char *strcat();
extern time_t time();
extern void endgrent();
D 35
extern void exit();
E 35
I 35
extern __dead void exit();
E 35
extern off_t lseek();
D 36
extern char *strerror();
E 36
I 36
extern const char *strerror();
E 36
E 32
#endif
E 25
E 22
E 1
