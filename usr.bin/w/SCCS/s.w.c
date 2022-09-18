h04911
s 00003/00002/00399
d D 8.6 94/06/30 10:50:02 mckusick 64 63
c allow entries that do not have an associated tty (from cgd)
e
s 00002/00001/00399
d D 8.5 94/06/30 10:42:29 mckusick 63 62
c avoid garbage characters on long host names (from cgd)
e
s 00012/00002/00388
d D 8.4 94/04/16 15:39:02 bostic 62 61
c run arguments through strvis, so we don't whack the terminal
c From: "Chris G. Demetriou" <cgd@nobozo.CS.Berkeley.EDU>
e
s 00004/00003/00386
d D 8.3 94/04/04 07:28:13 bostic 61 60
c can't put %M% in a comment either
e
s 00029/00033/00360
d D 8.2 94/04/04 05:34:39 pendry 60 59
c prettiness police.
c fix error message
e
s 00005/00005/00388
d D 8.1 93/06/06 22:23:19 bostic 59 58
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00389
d D 5.39 93/05/26 18:54:26 torek 58 57
c sysctl arg 4 is size_t *, not int *
e
s 00022/00022/00369
d D 5.38 93/05/26 00:31:05 mckusick 57 56
c don't die if bootime is not available
e
s 00019/00037/00372
d D 5.37 93/05/21 18:16:31 mckusick 56 54
c use sysctl to get boottime and load average
e
s 00020/00037/00372
d R 5.37 93/05/21 18:15:01 mckusick 55 54
c vi w.c
e
s 00012/00005/00397
d D 5.36 93/04/27 16:10:18 bostic 54 53
c another SCCS botch
e
s 00199/00248/00203
d D 5.35 93/04/27 15:21:28 bostic 53 52
c make -n real, add -M, -N, lots of minor cleanups
e
s 00002/00002/00449
d D 5.34 93/03/31 16:57:58 mckusick 52 51
c convert from kinfo to sysctl
e
s 00005/00000/00446
d D 5.33 92/05/20 16:37:23 bostic 51 50
c don't segv if no utmp file
e
s 00130/00039/00316
d D 5.32 92/04/03 16:21:40 mckusick 50 49
c update from Steve McCanne for Sun compatible kvm
e
s 00002/00002/00353
d D 5.31 92/03/29 12:34:01 bostic 49 48
c The 386 has a virtual console just like the hp300.
e
s 00004/00000/00351
d D 5.30 91/11/01 18:17:09 leres 48 47
c Don't bomb if we can't find a process for a tty.
e
s 00010/00043/00341
d D 5.29 91/04/23 19:50:07 bostic 47 46
c minor cleanup -- written by Bill Joy, and no longer contains any
c tainted code.  Add Berkeley specific copyright notice
e
s 00008/00007/00376
d D 5.28 91/04/18 18:43:48 bostic 46 45
c new copyright; att/bsd/shared
e
s 00010/00003/00373
d D 5.27 91/03/22 14:39:28 karels 45 44
c #ifdef for new vm
e
s 00001/00000/00375
d D 5.26 91/03/15 10:18:46 bostic 44 43
c don't fall off the end of main
e
s 00002/00014/00373
d D 5.25 91/03/02 13:21:44 bostic 43 42
c ANSI, replace strsave with strdup
e
s 00003/00003/00384
d D 5.24 90/07/27 16:40:04 marc 42 41
c shit - everyone wants it back as -i
e
s 00003/00003/00384
d D 5.23 90/07/27 13:58:50 marc 41 40
c -i -> -t (more commands use -t to mean sort by time)
e
s 00026/00000/00361
d D 5.22 90/06/24 18:26:25 bostic 40 39
c fixes to make /dev/console work right on the HP300, where it's a
c virtual device.  From Mike Hibler
e
s 00001/00001/00360
d D 5.21 90/05/15 19:54:55 bostic 39 38
c string.h is ANSI C include file
e
s 00000/00060/00361
d D 5.20 90/05/04 15:47:53 marc 38 37
c move proc_compare to ps directory
e
s 00002/00002/00419
d D 5.19 90/04/12 19:15:42 marc 37 36
c backwards test in proc_compare.  pick one sleeping *less*
e
s 00005/00005/00416
d D 5.18 90/04/12 19:14:20 marc 36 35
c use SSINTR, not pri < PZERO, as indication of interruptability
e
s 00001/00001/00420
d D 5.17 90/03/28 10:35:29 marc 35 33
c cosmetic change
e
s 00001/00001/00420
d R 5.17 90/03/28 10:34:24 marc 34 33
c cosmetic change
e
s 00276/00590/00145
d D 5.16 90/03/27 09:57:15 marc 33 32
c new version
e
s 00004/00014/00731
d D 5.15 90/02/06 16:09:24 marc 32 31
c minor edits for structure renaming (checkin by mckusick)
e
s 00062/00036/00683
d D 5.14 90/01/18 19:44:43 marc 31 30
c first pass, use getkinfo syscall
e
s 00012/00010/00707
d D 5.13 89/10/24 15:51:24 marc 30 29
c standardize output format (no missing fields, upcase headers, etc)
e
s 00005/00009/00712
d D 5.12 89/06/07 17:15:49 mckusick 29 28
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00008/00004/00713
d D 5.11 89/06/07 17:06:10 marc 28 27
c tty changes
e
s 00023/00027/00694
d D 5.10 89/05/30 10:12:17 bostic 27 26
c file reorg, add paths.h
e
s 00001/00000/00720
d D 5.9 88/01/03 01:01:46 bostic 26 25
c fix findidle declaration for ANSI C
e
s 00016/00013/00704
d D 5.8 87/10/26 11:42:29 bostic 25 24
c uptime only needs few nlist entries; bug report 4.3BSD/ucb/129
e
s 00020/00005/00697
d D 5.7 87/10/10 21:29:26 marc 24 23
c reject STOPPED procs, don't reject by uid, and only accept
c procs where the controlling terminal has a pgrp equal to the pgrp of the proc
e
s 00000/00001/00702
d D 5.6 87/08/30 09:10:30 bostic 23 22
c misdeclaration of fread(); bug report 4.3BSD/ucb/108
e
s 00001/00001/00702
d D 5.5 87/05/28 23:09:24 sam 22 21
c set ttywidth properly from terminal state
e
s 00035/00006/00668
d D 5.4 86/12/22 09:23:54 karels 21 19
c don't make me use who too
e
s 00035/00006/00668
d R 5.4 86/12/21 16:28:36 karels 20 19
c don't make me use who too
e
s 00041/00029/00633
d D 5.3 86/02/23 23:38:54 karels 19 18
c don't make me do the arithmetic (he's been idle HOW long?)
e
s 00010/00002/00652
d D 5.2 85/11/15 09:52:15 lepreau 18 17
c ignore zombies; document obscure debug printout
e
s 00015/00002/00639
d D 5.1 85/05/31 09:38:31 dist 17 16
c Add copyright
e
s 00001/00001/00640
d D 4.15 85/05/11 17:10:13 sam 16 14
c print "user" when only 1 user on the machine
e
s 00001/00001/00640
d R 4.15 85/05/11 15:59:20 sam 15 14
c users only when nusers > 1
e
s 00005/00001/00636
d D 4.14 85/01/23 08:40:06 ralph 14 13
c better heuristic for calculating JCPU
e
s 00000/00002/00637
d D 4.13 84/09/17 10:46:38 ralph 13 12
c don't call setbuf.
e
s 00002/00002/00637
d D 4.12 83/05/27 12:14:22 sam 12 11
c fix it one more time....
e
s 00015/00004/00624
d D 4.11 83/05/22 17:31:41 sam 11 10
c changes for new swap area organization
e
s 00015/00008/00613
d D 4.10 83/03/10 19:05:54 sam 10 9
c from shannon
e
s 00001/00001/00620
d D 4.9 82/12/24 12:55:06 sam 9 8
c header files moved around a bit
e
s 00003/00003/00618
d D 4.8 82/11/19 00:47:00 sam 8 7
c times are now stored in seconds in kernel structures
e
s 00012/00010/00609
d D 4.7 82/11/15 11:32:58 sam 7 6
c conversion to 4.1c
e
s 00002/00001/00617
d D 4.6 82/07/14 17:36:58 kre 6 5
c fix rounding bugs in reporting system uptime
e
s 00000/00002/00618
d D 4.5 82/02/26 14:05:18 root 5 4
c get rid of SDETACH
e
s 00007/00007/00613
d D 4.4 81/06/05 15:52:00 root 4 3
c fix bug where hardly ever finds arg list
e
s 00014/00018/00606
d D 4.3 81/02/28 22:55:38 wnj 3 2
c changed for new system style
e
s 00001/00001/00623
d D 4.2 80/12/03 12:31:45 mark 2 1
c fixed bug in -w/-u option: changed 1 to i.
e
s 00624/00000/00000
d D 4.1 80/10/01 17:29:24 bill 1 0
c date and time created 80/10/01 17:29:24 by bill
e
u
U
t
T
I 17
D 46
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 46
I 46
/*-
D 59
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 59
I 59
D 60
 * Copyright (c) 1980, 1991, 1993
E 60
I 60
 * Copyright (c) 1980, 1991, 1993, 1994
E 60
 *	The Regents of the University of California.  All rights reserved.
E 59
 *
D 47
 * %sccs.include.proprietary.c%
E 47
I 47
 * %sccs.include.redist.c%
E 47
E 46
 */

E 17
I 11
#ifndef lint
E 11
I 1
D 17
static char *sccsid = "%W% (Berkeley) %G%";
I 11
#endif
E 17
I 17
D 59
char copyright[] =
D 46
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 46
I 46
"%Z% Copyright (c) 1980, 1991 The Regents of the University of California.\n\
E 46
 All rights reserved.\n";
E 59
I 59
static char copyright[] =
D 60
"%Z% Copyright (c) 1980, 1991, 1993\n\
E 60
I 60
"%Z% Copyright (c) 1980, 1991, 1993, 1994\n\
E 60
	The Regents of the University of California.  All rights reserved.\n";
E 59
D 46
#endif not lint
E 46
I 46
#endif /* not lint */
E 46

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 46
#endif not lint
E 46
I 46
#endif /* not lint */
E 46

I 50
D 53
#define ADDRHACK

E 53
E 50
E 17
E 11
/*
 * w - print system status (who and what)
 *
 * This program is similar to the systat command on Tenex/Tops 10/20
I 33
 *
E 33
D 27
 * It needs read permission on /dev/mem, /dev/kmem, and /dev/drum.
E 27
 */
#include <sys/param.h>
D 33
#include <nlist.h>
#include <stdio.h>
#include <ctype.h>
E 33
D 50
#include <utmp.h>
E 50
I 50
D 53
#include <sys/file.h>
E 53
E 50
I 45
#include <sys/time.h>
E 45
D 7
#include <time.h>
E 7
#include <sys/stat.h>
I 50
D 52
#include <sys/kinfo.h>
E 52
I 52
#include <sys/sysctl.h>
E 52
E 50
D 33
#include <sys/dir.h>
E 33
D 45
#include <sys/user.h>
E 45
#include <sys/proc.h>
I 45
#include <sys/user.h>
E 45
I 21
#include <sys/ioctl.h>
I 53
#include <sys/socket.h>
E 53
E 21
D 9
#include <sys/pte.h>
E 9
I 9
D 45
#include <machine/pte.h>
E 9
#include <sys/vm.h>
E 45
I 24
#include <sys/tty.h>
I 53

I 56
#include <machine/cpu.h>
E 56
#include <netinet/in.h>
#include <arpa/inet.h>

E 53
I 31
D 33
#include <sys/kinfo.h>
E 33
I 33
D 50
#include <nlist.h>
#include <kvm.h>
E 50
#include <ctype.h>
I 53
#include <err.h>
E 53
I 51
#include <errno.h>
I 53
#include <fcntl.h>
E 53
E 51
E 33
E 31
I 27
D 50
#include <paths.h>
I 33
D 39
#include <strings.h>
E 39
I 39
#include <string.h>
E 50
I 50
#include <kvm.h>
I 53
#include <netdb.h>
E 53
#include <nlist.h>
I 53
#include <paths.h>
E 53
E 50
E 39
#include <stdio.h>
I 50
#include <stdlib.h>
#include <string.h>
I 53
#include <tzfile.h>
#include <unistd.h>
E 53
#include <utmp.h>
I 62
#include <vis.h>
E 62
D 53
#include <paths.h>
E 53
E 50
I 45

D 50
#ifdef SPPWAIT
#define NEWVM
E 50
I 50
D 53
#ifdef ADDRHACK
#include <sys/socket.h>
#include <netdb.h>
E 50
#endif
E 53
I 53
#include "extern.h"
E 53
D 50
#ifndef NEWVM
#include <machine/pte.h>
#include <sys/vm.h>
#endif
E 50
E 45
E 33
E 27
E 24

D 27
#define NMAX sizeof(utmp.ut_name)
#define LMAX sizeof(utmp.ut_line)
I 21
#define HMAX sizeof(utmp.ut_host)
E 21

E 27
D 33
#define ARGWIDTH	33	/* # chars left on 80 col crt for args */

D 3
struct smproc {
E 3
I 3
struct pr {
E 3
	short	w_pid;			/* proc.p_pid */
	char	w_flag;			/* proc.p_flag */
	short	w_size;			/* proc.p_size */
	long	w_seekaddr;		/* where to find args */
	long	w_lastpg;		/* disk address of stack */
	int	w_igintr;		/* INTR+3*QUIT, 0=die, 1=ign, 2=catch */
	time_t	w_time;			/* CPU time used by this process */
	time_t	w_ctime;		/* CPU time used by children */
	dev_t	w_tty;			/* tty device of process */
I 14
	int	w_uid;			/* uid of process */
E 14
	char	w_comm[15];		/* user.u_comm, null terminated */
	char	w_args[ARGWIDTH+1];	/* args if interesting process */
D 3
} pr[NPROC];
E 3
I 3
} *pr;
int	nproc;
E 3

struct	nlist nl[] = {
I 25
D 29
	{ "_avenrun" },
#define	X_AVENRUN	0
E 29
I 29
	{ "_nproc" },
#define	X_NPROC		0
E 29
	{ "_boottime" },
#define	X_BOOTTIME	1
E 25
	{ "_proc" },
D 25
#define	X_PROC		0
E 25
I 25
#define	X_PROC		2
E 25
	{ "_swapdev" },
D 25
#define	X_SWAPDEV	1
E 25
I 25
#define	X_SWAPDEV	3
E 25
	{ "_Usrptmap" },
D 25
#define	X_USRPTMA	2
E 25
I 25
#define	X_USRPTMA	4
E 25
	{ "_usrpt" },
D 25
#define	X_USRPT		3
E 25
I 25
#define	X_USRPT		5
E 25
	{ "_nswap" },
D 25
#define	X_NSWAP		4
	{ "_avenrun" },
#define	X_AVENRUN	5
D 7
	{ "_bootime" },
#define	X_BOOTIME	6
E 7
I 7
	{ "_boottime" },
#define	X_BOOTTIME	6
E 25
I 25
#define	X_NSWAP		6
E 25
E 7
I 3
D 29
	{ "_nproc" },
#define	X_NPROC		7
E 29
I 11
	{ "_dmmin" },
D 29
#define	X_DMMIN		8
E 29
I 29
#define	X_DMMIN		7
E 29
	{ "_dmmax" },
D 29
#define	X_DMMAX		9
E 29
I 29
#define	X_DMMAX		8
E 29
E 11
E 3
D 10
	{ 0 },
E 10
I 10
	{ "" },
E 10
};

FILE	*ps;
FILE	*ut;
FILE	*bootfd;
int	kmem;
int	mem;
D 27
int	swap;			/* /dev/kmem, mem, and swap */
E 27
I 27
int	swap;			/* kmem, mem, and swap */
E 27
int	nswap;
I 11
int	dmmin, dmmax;
E 11
dev_t	tty;
I 14
int	uid;
E 14
char	doing[520];		/* process attached to terminal */
time_t	proctime;		/* cpu time of process in doing */
double	avenrun[3];
I 3
struct	proc *aproc;
I 24
D 28
struct  tty ttyent;
E 28
I 28
pid_t	pgid;
pid_t	tpgid;
E 28
E 24
E 3

D 8
#define	DIV60(t)	((t+30)/60)    /* x/60 rounded */ 
E 8
I 8
D 11
#define	DIV60(t)	((t + 30) / 60)    /* x/60 rounded */ 
E 11
I 11
#define	DIV60(t)	((t+30)/60)    /* x/60 rounded */ 
E 11
E 8
D 14
#define	TTYEQ		(tty == pr[i].w_tty)
E 14
I 14
D 24
#define	TTYEQ		(tty == pr[i].w_tty && uid == pr[i].w_uid)
E 24
I 24
#define	TTYEQ		(tty == pr[i].w_tty)
E 24
E 14
#define IGINT		(1+3*1)		/* ignoring both SIGINT & SIGQUIT */

char	*getargs();
D 23
char	*fread();
E 23
char	*ctime();
char	*rindex();
FILE	*popen();
struct	tm *localtime();
I 19
time_t	findidle();
E 19

int	debug;			/* true if -d flag: debugging output */
I 21
int	ttywidth = 80;		/* width of tty */
E 33
I 33
D 53
char	*program;
int	ttywidth;		/* width of tty */
int	argwidth;		/* width of tty */
E 33
E 21
int	header = 1;		/* true if -h flag: don't print heading */
D 33
int	lflag = 1;		/* true if -l flag: long style output */
I 21
int	prfrom = 1;		/* true if not -f flag: print host from */
E 21
int	login;			/* true if invoked as login shell */
D 19
int	idle;			/* number of minutes user is idle */
E 19
I 19
time_t	idle;			/* number of minutes user is idle */
E 33
I 33
int	wcmd = 1;		/* true if this is w(1), and not uptime(1) */
I 50
#ifdef ADDRHACK
int	nflag = 0;		/* true if -n flag: don't convert addrs */
#endif
E 50
E 33
E 19
int	nusers;			/* number of users logged in now */
char *	sel_user;		/* login of particular user selected */
D 33
char firstchar;			/* first char of name of prog invoked as */
time_t	jobtime;		/* total cpu time visible */
E 33
time_t	now;			/* the current time of day */
D 19
struct	tm *nowt;		/* current time as time struct */
E 19
D 7
time_t	bootime, uptime;	/* time of last reboot & elapsed time since */
E 7
I 7
struct	timeval boottime;
time_t	uptime;			/* time of last reboot & elapsed time since */
E 7
D 33
int	np;			/* number of processes currently active */
E 33
struct	utmp utmp;
D 31
struct	proc mproc;
E 31
D 10
struct	user up;
char	fill[512];
E 10
I 10
D 33
union {
	struct user U_up;
	char	pad[NBPG][UPAGES];
} Up;
#define	up	Up.U_up
E 33
I 33
struct	winsize ws;
int	sortidle;		/* sort bu idle time */
I 50
#ifdef ADDRHACK
char	domain[64];
#endif
E 53
I 53
D 60
struct timeval boottime;
struct utmp utmp;
struct winsize ws;
E 53
kvm_t *kd;
I 53
time_t now;			/* the current time of day */
time_t uptime;			/* time of last reboot & elapsed time since */
int ttywidth;			/* width of tty */
int argwidth;			/* width of tty */
int header = 1;			/* true if -h flag: don't print heading */
int nflag;			/* true if -n flag: don't convert addrs */
int sortidle;			/* sort bu idle time */
char *sel_user;			/* login of particular user selected */
char *program;
char domain[MAXHOSTNAMELEN];
E 60
I 60
struct timeval	boottime;
struct utmp	utmp;
struct winsize	ws;
kvm_t	       *kd;
time_t		now;		/* the current time of day */
time_t		uptime;		/* time of last reboot & elapsed time since */
int		ttywidth;	/* width of tty */
int		argwidth;	/* width of tty */
int		header = 1;	/* true if -h flag: don't print heading */
int		nflag;		/* true if -n flag: don't convert addrs */
int		sortidle;	/* sort bu idle time */
char	       *sel_user;	/* login of particular user selected */
char		domain[MAXHOSTNAMELEN];
E 60
E 53
E 50
E 33
E 10

I 50
D 53
#if __STDC__
void error(const char *fmt, ...);
#else
void error();
#endif
E 50
I 33

I 50
void prttime();

E 53
E 50
/*
D 50
 * One of these per active utmp entry.  
E 50
I 50
 * One of these per active utmp entry.
E 50
 */
struct	entry {
	struct	entry *next;
	struct	utmp utmp;
	dev_t	tdev;		/* dev_t of terminal */
D 53
	int	idle;		/* idle time of terminal in minutes */
E 53
I 53
	time_t	idle;		/* idle time of terminal in seconds */
E 53
D 50
	struct	proc *proc;	/* list of procs in foreground */
E 50
I 50
	struct	kinfo_proc *kp;	/* `most interesting' proc */
E 50
	char	*args;		/* arg list of interesting process */
} *ep, *ehead = NULL, **nextp = &ehead;

D 56
struct nlist nl[] = {
	{ "_boottime" },
#define X_BOOTTIME	0
I 40
D 49
#if defined(hp300)
E 49
I 49
#if defined(hp300) || defined(i386)
E 49
	{ "_cn_tty" },
#define X_CNTTY		1
#endif
E 40
	{ "" },
};

D 41
#define USAGE "[ -hi ] [ user ]"
E 41
I 41
D 42
#define USAGE "[ -ht ] [ user ]"
E 42
I 42
D 53
#define USAGE "[ -hi ] [ user ]"
E 42
E 41
#define usage()	fprintf(stderr, "usage: %s: %s\n", program, USAGE)
E 53
I 53
static void	 pr_header __P((kvm_t *, time_t *, int));
E 56
I 56
static void	 pr_header __P((time_t *, int));
E 56
static struct stat
		*ttystat __P((char *));
static void	 usage __P((int));
E 53

I 54
D 60
char *fmt_argv __P((char **, char *, int));
E 60
I 60
char *fmt_argv __P((char **, char *, int));	/* ../../bin/ps/fmt.c */
E 60

E 54
I 53
int
E 53
E 33
main(argc, argv)
I 47
	int argc;
E 47
	char **argv;
{
D 33
	int days, hrs, mins;
	register int i, j;
	char *cp;
	register int curpid, empty;
E 33
I 33
D 53
	register int i;
E 33
I 21
D 50
	struct winsize win;
I 33
	register struct proc *p;
	struct eproc *e;
E 50
I 50
	register struct kinfo_proc *kp;
E 50
	struct stat *stp, *ttystat();
	FILE *ut;
	char *cp;
I 50
	int nentries;
E 50
	int ch;
E 53
D 60
	extern char *optarg;
	extern int optind;
E 60
I 60
	extern char *__progname;
E 60
D 43
	char *strsave();
E 43
I 43
D 53
	char *attime();
I 50
	char errbuf[80];
E 53
I 53
	struct kinfo_proc *kp;
	struct hostent *hp;
	struct stat *stp;
	FILE *ut;
	u_long l;
I 62
	size_t arglen;
E 62
	int ch, i, nentries, nusers, wcmd;
D 62
	char *memf, *nlistf, *p, *x;
E 62
I 62
	char *memf, *nlistf, *p, *vis_args, *x;
E 62
	char buf[MAXHOSTNAMELEN], errbuf[256];
E 53
E 50
E 43
E 33
E 21
D 13
	char obuf[BUFSIZ];
E 13

I 53
	/* Are we w(1) or uptime(1)? */
E 53
D 13
	setbuf(stdout, obuf);
E 13
D 33
	login = (argv[0][0] == '-');
	cp = rindex(argv[0], '/');
	firstchar = login ? argv[0][1] : (cp==0) ? argv[0][0] : cp[1];
	cp = argv[0];	/* for Usage */
E 33
I 33
D 60
	program = argv[0];
D 53
	/*
	 * are we w(1) or uptime(1)
	 */
	if ((cp = rindex(program, '/')) || *(cp = program) == '-')
		cp++;
	if (*cp == 'u')
E 53
I 53
	if ((p = rindex(program, '/')) || *(p = program) == '-')
E 60
I 60
	p = __progname;
	if (*p == '-')
E 60
		p++;
	if (*p == 'u') {
E 53
		wcmd = 0;
I 53
		p = "";
	} else {
		wcmd = 1;
		p = "hiflM:N:nsuw";
	}
E 53
E 33

D 33
	while (argc > 1) {
		if (argv[1][0] == '-') {
			for (i=1; argv[1][i]; i++) {
				switch(argv[1][i]) {

				case 'd':
					debug++;
					break;

I 21
				case 'f':
					prfrom = !prfrom;
					break;

E 21
				case 'h':
					header = 0;
					break;

				case 'l':
					lflag++;
					break;

				case 's':
					lflag = 0;
					break;

				case 'u':
				case 'w':
D 2
					firstchar = argv[1][1];
E 2
I 2
					firstchar = argv[1][i];
E 2
					break;

				default:
D 31
					printf("Bad flag %s\n", argv[1]);
E 31
I 31
					fprintf(stderr, "w: Bad flag %s\n",
						argv[1]);
E 31
					exit(1);
				}
			}
		} else {
			if (!isalnum(argv[1][0]) || argc > 2) {
D 21
				printf("Usage: %s [ -hlsuw ] [ user ]\n", cp);
E 21
I 21
D 31
				printf("Usage: %s [ -hlsfuw ] [ user ]\n", cp);
E 31
I 31
				fprintf(stderr, 
				       "Usage: %s [ -hlsfuw ] [ user ]\n", cp);
E 31
E 21
				exit(1);
			} else
				sel_user = argv[1];
E 33
I 33
D 41
	while ((ch = getopt(argc, argv, "hiflsuw")) != EOF)
E 41
I 41
D 42
	while ((ch = getopt(argc, argv, "htflsuw")) != EOF)
E 42
I 42
D 50
	while ((ch = getopt(argc, argv, "hiflsuw")) != EOF)
E 50
I 50
D 53
	while ((ch = getopt(argc, argv, "hiflnsuw")) != EOF)
E 50
E 42
E 41
		switch((char)ch) {
E 53
I 53
	memf = nlistf = NULL;
	while ((ch = getopt(argc, argv, p)) != EOF)
		switch (ch) {
E 53
		case 'h':
			header = 0;
			break;
D 41
		case 'i':
E 41
I 41
D 42
		case 't':
E 42
I 42
		case 'i':
E 42
E 41
D 53
			sortidle++;
E 53
I 53
			sortidle = 1;
E 53
			break;
I 53
		case 'M':
I 56
			header = 0;
E 56
			memf = optarg;
			break;
		case 'N':
			nlistf = optarg;
			break;
E 53
I 50
		case 'n':
D 53
#ifdef ADDRHACK
			++nflag;
#endif
E 53
I 53
			nflag = 1;
E 53
			break;
E 50
		case 'f': case 'l': case 's': case 'u': case 'w':
D 53
			error("[-flsuw] no longer supported");
			usage();
			exit(1);
E 53
I 53
			warnx("[-flsuw] no longer supported");
			/* FALLTHROUGH */
E 53
		case '?':
		default:
D 53
			usage();
			exit(1);
E 53
I 53
			usage(wcmd);
E 53
E 33
		}
D 33
		argc--; argv++;
E 33
I 33
	argc -= optind;
	argv += optind;
D 47
	if (argc == 1) {
		sel_user = argv[0];
		argv++, argc--;
E 33
	}
D 33

I 21
D 22
	if (ioctl(1, TIOCGWINSZ, &win) == -1 || win.ws_col > 70)
E 22
I 22
D 25
	if (ioctl(1, TIOCGWINSZ, &win) != -1 && win.ws_col > 70)
E 22
		ttywidth = win.ws_col;
E 25
E 21
D 27
	if ((kmem = open("/dev/kmem", 0)) < 0) {
		fprintf(stderr, "No kmem\n");
E 27
I 27
	if ((kmem = open(_PATH_KMEM, 0)) < 0) {
		fprintf(stderr, "w: no %s.\n", _PATH_KMEM);
E 33
I 33
	if (argc) {
		usage();
E 33
E 27
		exit(1);
	}
E 47
D 27
	nlist("/vmunix", nl);
E 27
I 27
D 33
	nlist(_PATH_UNIX, nl);
E 27
	if (nl[0].n_type==0) {
D 27
		fprintf(stderr, "No namelist\n");
E 27
I 27
		fprintf(stderr, "w: no %s namelist.\n", _PATH_UNIX);
E 27
		exit(1);
	}
E 33

I 53
	if ((kd = kvm_openfiles(nlistf, memf, NULL, O_RDONLY, errbuf)) == NULL)
D 60
		err(1, "%s", errbuf);
E 60
I 60
		errx(1, "%s", errbuf);
E 60
D 56
	if (header && kvm_nlist(kd, nl) != 0)
		err(1, "can't read namelist");
E 56

	(void)time(&now);
	if ((ut = fopen(_PATH_UTMP, "r")) == NULL)
		err(1, "%s", _PATH_UTMP);

E 53
I 47
	if (*argv)
		sel_user = *argv;

E 47
D 24
	if (firstchar != 'u')
		readpr();
E 24
I 24
D 25
	if (firstchar != 'u')	/* if this program is not "uptime(1)" */
		readpr();	/* then read in procs */
E 25
I 25
D 33
	if (firstchar == 'u')	/* uptime(1) */
		nl[X_BOOTTIME+1].n_name = "";
	else {			/* then read in procs, get window size */
		readpr();
		if (ioctl(1, TIOCGWINSZ, &win) != -1 && win.ws_col > 70)
			ttywidth = win.ws_col;
E 33
I 33
D 50
	if (header && kvm_nlist(nl) != 0) {
E 50
I 50
D 53
	kd = kvm_openfiles((char *)0, (char *)0, (char *)0, O_RDONLY, errbuf);
	if (kd == NULL) {
		error("%s", errbuf);
		exit(1);
	}
	if (header && kvm_nlist(kd, nl) != 0) {
E 50
		error("can't get namelist");
D 50
		exit (1);
E 50
I 50
		exit(1);
E 50
E 33
	}
I 50
#ifdef ADDRHACK
	if (!nflag) {
		if (gethostname(domain, sizeof(domain) - 1) < 0 ||
		    (cp = index(domain, '.')) == 0)
			domain[0] = '\0';
		else {
			domain[sizeof(domain) - 1] = '\0';
			bcopy(cp, domain, strlen(cp) + 1);
		}
	}
#endif
E 50
E 25
E 24
D 33

D 27
	ut = fopen("/etc/utmp","r");
E 27
I 27
	ut = fopen(_PATH_UTMP, "r");
E 33
E 27
I 19
	time(&now);
E 19
D 33
	if (header) {
		/* Print time of day */
D 19
		time(&now);
		nowt = localtime(&now);
		prtat(nowt);
E 19
I 19
		prtat(&now);
E 33
I 33
	ut = fopen(_PATH_UTMP, "r");
I 51
	if (ut == NULL) {
		error("%s: %s", _PATH_UTMP, strerror(errno));
		exit(1);
	}
E 51
	while (fread(&utmp, sizeof(utmp), 1, ut)) {
E 53
I 53
	for (nusers = 0; fread(&utmp, sizeof(utmp), 1, ut);) {
E 53
		if (utmp.ut_name[0] == '\0')
			continue;
D 53
		nusers++;
E 53
I 53
		++nusers;
E 53
D 50
		if (wcmd == 0 || (sel_user && 
E 50
I 50
		if (wcmd == 0 || (sel_user &&
E 50
		    strncmp(utmp.ut_name, sel_user, UT_NAMESIZE) != 0))
			continue;
D 53
		if ((ep = (struct entry *)
		     calloc(1, sizeof (struct entry))) == NULL) {
			error("out of memory");
			exit(1);
		}
E 53
I 53
		if ((ep = calloc(1, sizeof(struct entry))) == NULL)
			err(1, NULL);
E 53
		*nextp = ep;
		nextp = &(ep->next);
D 60
		bcopy(&utmp, &(ep->utmp), sizeof (struct utmp));
E 60
I 60
		memmove(&(ep->utmp), &utmp, sizeof(struct utmp));
E 60
D 64
		stp = ttystat(ep->utmp.ut_line);
E 64
I 64
		if (!(stp = ttystat(ep->utmp.ut_line)))
			continue;
E 64
		ep->tdev = stp->st_rdev;
I 40
D 49
#if defined(hp300)
E 49
I 49
D 56
#if defined(hp300) || defined(i386)
E 56
I 56
#ifdef CPU_CONSDEV
E 56
E 49
		/*
D 53
		 * XXX  If this is the console device, attempt to ascertain
E 53
I 53
D 56
		 * XXX
E 56
		 * If this is the console device, attempt to ascertain
E 53
		 * the true console device dev_t.
		 */
		if (ep->tdev == 0) {
D 56
			static dev_t cn_dev;
E 56
I 56
D 58
			int mib[2], size;
E 58
I 58
			int mib[2];
			size_t size;
E 58
E 56

D 56
			if (nl[X_CNTTY].n_value) {
				struct tty cn_tty, *cn_ttyp;
				
D 47
				if (kvm_read(nl[X_CNTTY].n_value,
					     &cn_ttyp, sizeof (cn_ttyp)) > 0) {
E 47
I 47
D 50
				if (kvm_read((void *)nl[X_CNTTY].n_value,
				    &cn_ttyp, sizeof(cn_ttyp)) > 0) {
E 47
					(void)kvm_read(cn_ttyp, &cn_tty,
D 47
						       sizeof (cn_tty));
E 47
I 47
					    sizeof (cn_tty));
E 50
I 50
				if (kvm_read(kd, (u_long)nl[X_CNTTY].n_value,
				    (char *)&cn_ttyp, sizeof(cn_ttyp)) > 0) {
					(void)kvm_read(kd, (u_long)cn_ttyp,
					    (char *)&cn_tty, sizeof (cn_tty));
E 50
E 47
					cn_dev = cn_tty.t_dev;
				}
				nl[X_CNTTY].n_value = 0;
			}
			ep->tdev = cn_dev;
E 56
I 56
			mib[0] = CTL_MACHDEP;
			mib[1] = CPU_CONSDEV;
			size = sizeof(dev_t);
			(void) sysctl(mib, 2, &ep->tdev, &size, NULL, 0);
E 56
		}
#endif
E 40
D 53
		ep->idle = ((now - stp->st_atime) + 30) / 60; /* secs->mins */
		if (ep->idle < 0)
E 53
I 53
		if ((ep->idle = now - stp->st_atime) < 0)
E 53
			ep->idle = 0;
	}
D 53
	fclose(ut);
E 53
I 53
	(void)fclose(ut);
E 53
E 33
E 19

I 33
	if (header || wcmd == 0) {
D 53
		double	avenrun[3];
		int days, hrs, mins;
E 53
I 53
D 56
		pr_header(kd, &now, nusers);
E 56
I 56
		pr_header(&now, nusers);
E 56
		if (wcmd == 0)
			exit (0);
	}
E 53

E 33
D 53
		/*
I 33
D 50
		 * Print time of day 
E 50
I 50
		 * Print time of day
E 50
		 */
		fputs(attime(&now), stdout);
		/*
E 33
		 * Print how long system has been up.
D 7
		 * (Found by looking for "bootime" in kernel)
E 7
I 7
		 * (Found by looking for "boottime" in kernel)
E 7
		 */
D 7
		lseek(kmem, (long)nl[X_BOOTIME].n_value, 0);
		read(kmem, &bootime, sizeof (bootime));
E 7
I 7
D 33
		lseek(kmem, (long)nl[X_BOOTTIME].n_value, 0);
		read(kmem, &boottime, sizeof (boottime));
E 7

E 33
I 33
D 47
		(void)kvm_read((off_t)nl[X_BOOTTIME].n_value, &boottime, 
			sizeof (boottime));
E 47
I 47
D 50
		(void)kvm_read((void *)nl[X_BOOTTIME].n_value, &boottime, 
		    sizeof (boottime));
E 50
I 50
		(void)kvm_read(kd, (u_long)nl[X_BOOTTIME].n_value,
		    (char *)&boottime, sizeof (boottime));
E 50
E 47
E 33
D 7
		uptime = now - bootime;
E 7
I 7
		uptime = now - boottime.tv_sec;
E 7
I 6
		uptime += 30;
E 6
		days = uptime / (60*60*24);
		uptime %= (60*60*24);
		hrs = uptime / (60*60);
		uptime %= (60*60);
D 6
		mins = DIV60(uptime);
E 6
I 6
		mins = uptime / 60;
E 6

		printf("  up");
		if (days > 0)
			printf(" %d day%s,", days, days>1?"s":"");
		if (hrs > 0 && mins > 0) {
			printf(" %2d:%02d,", hrs, mins);
		} else {
			if (hrs > 0)
				printf(" %d hr%s,", hrs, hrs>1?"s":"");
			if (mins > 0)
				printf(" %d min%s,", mins, mins>1?"s":"");
		}

		/* Print number of users logged in to system */
D 33
		while (fread(&utmp, sizeof(utmp), 1, ut)) {
			if (utmp.ut_name[0] != '\0')
				nusers++;
		}
		rewind(ut);
E 33
D 16
		printf("  %d users", nusers);
E 16
I 16
		printf("  %d user%s", nusers, nusers>1?"s":"");
E 16

		/*
		 * Print 1, 5, and 15 minute load averages.
D 29
		 * (Found by looking in kernel for avenrun).
E 29
		 */
		printf(",  load average:");
D 29
		lseek(kmem, (long)nl[X_AVENRUN].n_value, 0);
		read(kmem, avenrun, sizeof(avenrun));
E 29
I 29
		(void)getloadavg(avenrun, sizeof(avenrun) / sizeof(avenrun[0]));
E 29
		for (i = 0; i < (sizeof(avenrun)/sizeof(avenrun[0])); i++) {
			if (i > 0)
				printf(",");
			printf(" %.2f", avenrun[i]);
		}
		printf("\n");
D 24
		if (firstchar == 'u')
E 24
I 24
D 33
		if (firstchar == 'u')	/* if this was uptime(1), finished */
E 33
I 33
		if (wcmd == 0)		/* if uptime(1) then done */
E 33
E 24
			exit(0);
E 53
D 33

		/* Headers for rest of output */
D 21
		if (lflag)
E 21
I 21
		if (lflag && prfrom)
D 30
			printf("User     tty from           login@  idle   JCPU   PCPU  what\n");
E 30
I 30
			printf("USER    TTY FROM            LOGIN@  IDLE   JCPU   PCPU  WHAT\n");
E 30
		else if (lflag)
E 21
D 30
			printf("User     tty       login@  idle   JCPU   PCPU  what\n");
E 30
I 30
			printf("USER     TTY       LOGIN@  IDLE   JCPU   PCPU  WHAT\n");
E 30
I 21
		else if (prfrom)
D 30
			printf("User    tty from            idle  what\n");
E 30
I 30
			printf("USER    TTY FROM            IDLE  WHAT\n");
E 30
E 21
		else
D 30
			printf("User    tty  idle  what\n");
E 30
I 30
			printf("USER    TTY  IDLE  WHAT\n");
E 30
		fflush(stdout);
E 33
I 33
#define HEADER	"USER    TTY FROM              LOGIN@  IDLE WHAT\n"
#define WUSED	(sizeof (HEADER) - sizeof ("WHAT\n"))
D 53
		printf(HEADER);
E 33
	}
E 53
I 53
	(void)printf(HEADER);
E 53

D 33

	for (;;) {	/* for each entry in utmp */
		if (fread(&utmp, sizeof(utmp), 1, ut) == NULL) {
			fclose(ut);
			exit(0);
		}
		if (utmp.ut_name[0] == '\0')
			continue;	/* that tty is free */
D 27
		if (sel_user && strcmpn(utmp.ut_name, sel_user, NMAX) != 0)
E 27
I 27
		if (sel_user && strncmp(utmp.ut_name, sel_user, UT_NAMESIZE) != 0)
E 27
			continue;	/* we wanted only somebody else */

		gettty();
		jobtime = 0;
		proctime = 0;
		strcpy(doing, "-");	/* default act: normally never prints */
		empty = 1;
		curpid = -1;
		idle = findidle();
		for (i=0; i<np; i++) {	/* for each process on this tty */
			if (!(TTYEQ))
				continue;
			jobtime += pr[i].w_time + pr[i].w_ctime;
			proctime += pr[i].w_time;
D 18
			if (debug) {
E 18
I 18
			/* 
			 * Meaning of debug fields following proc name is:
			 * & by itself: ignoring both SIGINT and QUIT.
			 *		(==> this proc is not a candidate.)
			 * & <i> <q>:   i is SIGINT status, q is quit.
			 *		0 == DFL, 1 == IGN, 2 == caught.
			 * *:		proc pgrp == tty pgrp.
			 */
			 if (debug) {
E 18
				printf("\t\t%d\t%s", pr[i].w_pid, pr[i].w_args);
				if ((j=pr[i].w_igintr) > 0)
					if (j==IGINT)
						printf(" &");
					else
						printf(" & %d %d", j%3, j/3);
				printf("\n");
E 33
I 33
D 35
	for (p = kvm_nextproc(); p != NULL; p = kvm_nextproc()) {
E 35
I 35
D 50
	while ((p = kvm_nextproc()) != NULL) {
E 35
		if (p->p_stat == SZOMB || (p->p_flag & SCTTY) == 0)
E 50
I 50
D 52
	if ((kp = kvm_getprocs(kd, KINFO_PROC_ALL, 0, &nentries)) == NULL)
E 52
I 52
	if ((kp = kvm_getprocs(kd, KERN_PROC_ALL, 0, &nentries)) == NULL)
E 52
D 53
		error("%s", kvm_geterr(kd));
E 53
I 53
		err(1, "%s", kvm_geterr(kd));
E 53
	for (i = 0; i < nentries; i++, kp++) {
D 60
		register struct proc *p = &kp->kp_proc;
		register struct eproc *e;
E 60
I 60
		struct proc *p = &kp->kp_proc;
		struct eproc *e;
E 60

		if (p->p_stat == SIDL || p->p_stat == SZOMB)
E 50
			continue;
D 50
		e = kvm_geteproc(p);
E 50
I 50
		e = &kp->kp_eproc;
E 50
		for (ep = ehead; ep != NULL; ep = ep->next) {
			if (ep->tdev == e->e_tdev && e->e_pgid == e->e_tpgid) {
				/*
				 * Proc is in foreground of this terminal
				 */
D 50
				if (proc_compare(ep->proc, p))
					ep->proc = p;
E 50
I 50
				if (proc_compare(&ep->kp->kp_proc, p))
					ep->kp = kp;
E 50
				break;
E 33
			}
D 33
			if (empty && pr[i].w_igintr!=IGINT) {
				empty = 0;
				curpid = -1;
			}
			if(pr[i].w_pid>curpid && (pr[i].w_igintr!=IGINT || empty)){
				curpid = pr[i].w_pid;
				strcpy(doing, lflag ? pr[i].w_args : pr[i].w_comm);
#ifdef notdef
				if (doing[0]==0 || doing[0]=='-' && doing[1]<=' ' || doing[0] == '?') {
					strcat(doing, " (");
					strcat(doing, pr[i].w_comm);
					strcat(doing, ")");
				}
#endif
			}
E 33
		}
D 33
		putline();
E 33
	}
I 33
D 53
	if ((ioctl(1, TIOCGWINSZ, &ws) == -1 &&
	     ioctl(2, TIOCGWINSZ, &ws) == -1 &&
	     ioctl(0, TIOCGWINSZ, &ws) == -1) || ws.ws_col == 0)
E 53
I 53
	if ((ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 &&
	     ioctl(STDERR_FILENO, TIOCGWINSZ, &ws) == -1 &&
	     ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1) || ws.ws_col == 0)
E 53
	       ttywidth = 79;
        else
	       ttywidth = ws.ws_col - 1;
	argwidth = ttywidth - WUSED;
	if (argwidth < 4)
		argwidth = 8;
	for (ep = ehead; ep != NULL; ep = ep->next) {
I 48
D 50
		if (ep->proc == 0) {
E 50
I 50
D 54
		char *fmt_argv();

E 54
		if (ep->kp == NULL) {
E 50
			ep->args = "-";
			continue;
		}
E 48
D 43
		ep->args = strsave(kvm_getargs(ep->proc, kvm_getu(ep->proc)));
E 43
I 43
D 50
		ep->args = strdup(kvm_getargs(ep->proc, kvm_getu(ep->proc)));
E 50
I 50
		ep->args = fmt_argv(kvm_getargv(kd, ep->kp, argwidth),
		    ep->kp->kp_proc.p_comm, MAXCOMLEN);
E 50
E 43
D 53
		if (ep->args == NULL) {
			error("out of memory");
			exit(1);
		}
E 53
I 53
		if (ep->args == NULL)
			err(1, NULL);
E 53
	}
	/* sort by idle time */
	if (sortidle && ehead != NULL) {
		struct entry *from = ehead, *save;
		
		ehead = NULL;
		while (from != NULL) {
D 50
			for (nextp = &ehead; 
E 50
I 50
			for (nextp = &ehead;
E 50
			    (*nextp) && from->idle >= (*nextp)->idle;
			    nextp = &(*nextp)->next)
D 50
				;
E 50
I 50
				continue;
E 50
			save = from;
			from = from->next;
			save->next = *nextp;
			*nextp = save;
		}
	}
			
D 53
	for (ep = ehead; ep != NULL; ep = ep->next) {
I 50
#ifdef ADDRHACK
		register char *x;
		register struct hostent *hp;
		unsigned long l;
		char buf[64];
#endif
E 53
I 53
	if (!nflag)
		if (gethostname(domain, sizeof(domain) - 1) < 0 ||
D 60
		    (p = index(domain, '.')) == 0)
E 60
I 60
		    (p = strchr(domain, '.')) == 0)
E 60
			domain[0] = '\0';
		else {
			domain[sizeof(domain) - 1] = '\0';
D 60
			bcopy(p, domain, strlen(p) + 1);
E 60
I 60
			memmove(domain, p, strlen(p) + 1);
E 60
		}
E 53

I 62
	if ((vis_args = malloc(argwidth * 4 + 1)) == NULL)
		err(1, NULL);
E 62
D 53
		cp = *ep->utmp.ut_host ? ep->utmp.ut_host : "-";
#ifdef ADDRHACK
		if (x = index(cp, ':'))
E 53
I 53
	for (ep = ehead; ep != NULL; ep = ep->next) {
		p = *ep->utmp.ut_host ? ep->utmp.ut_host : "-";
D 60
		if (x = index(p, ':'))
E 60
I 60
D 62
		if (x = strchr(p, ':'))
E 62
I 62
		if ((x = strchr(p, ':')) != NULL)
E 62
E 60
E 53
			*x++ = '\0';
D 53
		if (!nflag && isdigit(*cp) &&
		    (long)(l = inet_addr(cp)) != -1 &&
		    (hp = gethostbyaddr((char *)&l, sizeof(l),
		    AF_INET))) {
			    if (domain[0] != '\0') {
				    cp = hp->h_name;
				    cp += strlen(hp->h_name);
				    cp -= strlen(domain);
				    if (cp > hp->h_name &&
					strcmp(cp, domain) == 0)
					*cp = '\0';
			    }
			    cp = hp->h_name;
E 53
I 53
		if (!nflag && isdigit(*p) &&
		    (long)(l = inet_addr(p)) != -1 &&
		    (hp = gethostbyaddr((char *)&l, sizeof(l), AF_INET))) {
			if (domain[0] != '\0') {
				p = hp->h_name;
				p += strlen(hp->h_name);
				p -= strlen(domain);
D 60
				if (p > hp->h_name && !strcmp(p, domain))
E 60
I 60
				if (p > hp->h_name && strcmp(p, domain) == 0)
E 60
					*p = '\0';
			}
			p = hp->h_name;
E 53
		}
		if (x) {
D 53
			sprintf(buf, "%s:%s", cp, x);
			cp = buf;
E 53
I 53
D 63
			(void)snprintf(buf, sizeof(buf), "%s:%s", p, x);
E 63
I 63
			(void)snprintf(buf, sizeof(buf), "%s:%.*s", p,
				ep->utmp.ut_host + UT_HOSTSIZE - x, x);
E 63
			p = buf;
E 53
		}
D 53
#endif
E 50
		printf("%-*.*s %-2.2s %-*.*s %s",
			UT_NAMESIZE, UT_NAMESIZE, ep->utmp.ut_name,
D 50
			strncmp(ep->utmp.ut_line, "tty", 3) == 0 ? 
E 50
I 50
			strncmp(ep->utmp.ut_line, "tty", 3) == 0 ?
E 50
				ep->utmp.ut_line+3 : ep->utmp.ut_line,
D 50
			UT_HOSTSIZE, UT_HOSTSIZE, *ep->utmp.ut_host ?
				ep->utmp.ut_host : "-",
E 50
I 50
			UT_HOSTSIZE, UT_HOSTSIZE, *cp ? cp : "-",
E 50
			attime(&ep->utmp.ut_time));
		if (ep->idle >= 36 * 60)
			printf(" %ddays ", (ep->idle + 12 * 60) / (24 * 60));
		else
			prttime(ep->idle, " ");
		printf("%.*s\n", argwidth, ep->args);
E 53
I 53
		(void)printf("%-*.*s %-2.2s %-*.*s ",
		    UT_NAMESIZE, UT_NAMESIZE, ep->utmp.ut_name,
		    strncmp(ep->utmp.ut_line, "tty", 3) ?
		    ep->utmp.ut_line : ep->utmp.ut_line + 3,
		    UT_HOSTSIZE, UT_HOSTSIZE, *p ? p : "-");
		pr_attime(&ep->utmp.ut_time, &now);
		pr_idle(ep->idle);
I 62
		if (ep->args != NULL) {
			arglen = strlen(ep->args);
			strvisx(vis_args, ep->args,
			    arglen > argwidth ? argwidth : arglen,
			    VIS_TAB | VIS_NL | VIS_NOSLASH);
		}
E 62
		(void)printf("%.*s\n", argwidth, ep->args);
E 53
	}
I 44
	exit(0);
E 44
E 33
}

D 33
/* figure out the major/minor device # pair for this tty */
gettty()
{
	char ttybuf[20];
	struct stat statbuf;

	ttybuf[0] = 0;
D 27
	strcpy(ttybuf, "/dev/");
E 27
I 27
	strcpy(ttybuf, _PATH_DEV);
E 27
	strcat(ttybuf, utmp.ut_line);
	stat(ttybuf, &statbuf);
	tty = statbuf.st_rdev;
I 14
	uid = statbuf.st_uid;
E 14
}

E 33
D 38
/*
D 33
 * putline: print out the accumulated line of info about one user.
E 33
I 33
 * Returns 1 if p2 is "better" than p1
 *
 * The algorithm for picking the "interesting" process is thus:
 *
 *	1) (Only foreground processes are eligable - implied)
 *	2) Runnable processes are favored over anything
 *	   else.  The runner with the highest cpu
 *	   utilization is picked (p_cpu).  Ties are
 *	   broken by picking the highest pid.
 *	3  Next, the sleeper with the shortest sleep
 *	   time is favored.  With ties, we pick out
 *	   just short-term sleepers (p_pri <= PZERO).
 *	   Further ties are broken by picking the highest
 *	   pid.
 *
E 33
 */
D 33
putline()
E 33
I 33
#define isrun(p)	(((p)->p_stat == SRUN) || ((p)->p_stat == SIDL))
proc_compare(p1, p2)
	register struct proc *p1, *p2;
E 33
{
D 33
	register int tm;
I 21
	int width = ttywidth - 1;
E 33
E 21

D 33
	/* print login name of the user */
D 27
	printf("%-*.*s ", NMAX, NMAX, utmp.ut_name);
I 21
	width -= NMAX + 1;
E 27
I 27
	printf("%-*.*s ", UT_NAMESIZE, UT_NAMESIZE, utmp.ut_name);
	width -= UT_NAMESIZE + 1;
E 27
E 21

	/* print tty user is on */
D 21
	if (lflag)
E 21
I 21
	if (lflag && !prfrom) {
E 21
D 27
		/* long form: all (up to) LMAX chars */
		printf("%-*.*s", LMAX, LMAX, utmp.ut_line);
D 21
	else {
E 21
I 21
		width -= LMAX;
E 27
I 27
		/* long form: all (up to) UT_LINESIZE chars */
		printf("%-*.*s", UT_LINESIZE, UT_LINESIZE, utmp.ut_line);
		width -= UT_LINESIZE;
E 27
	 } else {
E 21
		/* short form: 2 chars, skipping 'tty' if there */
		if (utmp.ut_line[0]=='t' && utmp.ut_line[1]=='t' && utmp.ut_line[2]=='y')
			printf("%-2.2s", &utmp.ut_line[3]);
		else
			printf("%-2.2s", utmp.ut_line);
I 21
		width -= 2;
E 33
I 33
	if (p1 == NULL)
		return (1);
	/*
	 * see if at least one of them is runnable
	 */
	switch (isrun(p1)<<1 | isrun(p2)) {
	case 0x01:
		return (1);
	case 0x10:
		return (0);
	case 0x11:
		/*
		 * tie - favor one with highest recent cpu utilization
		 */
		if (p2->p_cpu > p1->p_cpu)
			return (1);
		if (p1->p_cpu > p2->p_cpu)
			return (0);
		return (p2->p_pid > p1->p_pid);	/* tie - return highest pid */
E 33
E 21
	}
I 33
	/* 
	 * pick the one with the smallest sleep time
	 */
	if (p2->p_slptime > p1->p_slptime)
D 37
		return (1);
	if (p1->p_slptime > p2->p_slptime)
E 37
		return (0);
I 37
	if (p1->p_slptime > p2->p_slptime)
		return (1);
E 37
	/*
D 36
	 * favor the one sleeping in a "short term" sleep
E 36
I 36
	 * favor one sleeping in a non-interruptible sleep
E 36
	 */
D 36
	if (p2->p_pri <= PZERO && p1->p_pri > PZERO)
		return (1);
	if (p1->p_pri <= PZERO && p2->p_pri > PZERO)
		return (0);
E 36
I 36
	 if (p1->p_flag&SSINTR && (p2->p_flag&SSINTR) == 0)
		 return (1);
	 if (p2->p_flag&SSINTR && (p1->p_flag&SSINTR) == 0)
		 return (0);
E 36
	return(p2->p_pid > p1->p_pid);		/* tie - return highest pid */
}
E 33

D 21
	if (lflag)
E 21
I 21
D 33
	if (prfrom) {
D 30
		printf(" %-14.14s", utmp.ut_host);
E 30
I 30
		if (*utmp.ut_host == '\0')
			printf(" -             ");
		else
			printf(" %-14.14s", utmp.ut_host);
E 30
		width -= 15;
	}
E 33

E 38
D 33
	if (lflag) {
E 21
		/* print when the user logged in */
D 19
		prtat(localtime(&utmp.ut_time));
E 19
I 19
		prtat(&utmp.ut_time);
I 21
		width -= 8;
	}
E 33
I 33
D 53
struct stat *
ttystat(line)
I 50
	char *line;
E 53
I 53
static void
D 56
pr_header(kd, nowp, nusers)
	kvm_t *kd;
E 56
I 56
pr_header(nowp, nusers)
E 56
	time_t *nowp;
	int nusers;
E 53
E 50
{
D 53
	static struct stat statbuf;
	char ttybuf[sizeof (_PATH_DEV) + UT_LINESIZE + 1];
E 53
I 53
	double avenrun[3];
	time_t uptime;
	int days, hrs, i, mins;
I 56
D 58
	int mib[2], size;
E 58
I 58
	int mib[2];
	size_t size;
E 58
E 56
D 54
	char buf[256];
E 54
I 54
D 60
	char buf[256], fmt[10];
E 60
I 60
	char buf[256];
E 60
E 54
E 53
E 33
E 21
E 19

D 33
	/* print idle time */
D 19
	prttime(idle," ");
E 19
I 19
	if (idle >= 36 * 60)
D 31
		printf("%2ddays ", (idle + 12 * 60) / (24 * 60));
E 31
I 31
		printf(" %ddays ", (idle + 12 * 60) / (24 * 60));
E 31
	else
		prttime(idle," ");
I 21
	width -= 7;
E 33
I 33
D 53
	sprintf(ttybuf, "%s/%.*s", _PATH_DEV, UT_LINESIZE, line);
	(void) stat(ttybuf, &statbuf);
E 53
I 53
D 54
	/* Print time of day. */
	(void)strftime(buf, sizeof(buf), "%l:%M%p", localtime(nowp));
E 54
I 54
	/*
	 * Print time of day.
	 *
D 61
	 * Note, SCCS forces the string manipulation below, as it
	 * replaces %M% with file information.
E 61
I 61
	 * SCCS forces the string manipulation below, as it replaces
	 * %, M, and % in a character string with the file name.
E 61
	 */
D 60
	(void)strcpy(fmt, "%l:%%%p");
	fmt[4] = 'M';
	(void)strftime(buf, sizeof(buf), fmt, localtime(nowp));
E 60
I 60
D 61
	(void)strftime(buf,sizeof(buf),__CONCAT("%l:%","M%p"),localtime(nowp));
E 61
I 61
	(void)strftime(buf, sizeof(buf),
	    __CONCAT("%l:%","M%p"), localtime(nowp));
E 61
E 60
E 54
	(void)printf("%s ", buf);
E 53
E 33
E 21
E 19

D 33
	if (lflag) {
		/* print CPU time for all processes & children */
D 8
		prttime(DIV60(jobtime)," ");
E 8
I 8
D 10
		prttime(jobtime," ");
E 10
I 10
D 12
		prttime(DIV60(jobtime)," ");
E 12
I 12
		prttime(jobtime," ");
I 21
		width -= 7;
E 21
E 12
E 10
E 8
		/* print cpu time for interesting process */
D 8
		prttime(DIV60(proctime)," ");
E 8
I 8
D 10
		prttime(proctime," ");
E 10
I 10
D 12
		prttime(DIV60(proctime)," ");
E 12
I 12
		prttime(proctime," ");
I 21
		width -= 7;
E 21
E 12
E 10
E 8
	}

	/* what user is doing, either command tail or args */
D 21
	printf(" %-.32s\n",doing);
E 21
I 21
	printf(" %-.*s\n", width-1, doing);
E 21
	fflush(stdout);
E 33
I 33
D 53
	return (&statbuf);
E 53
I 53
	/*
	 * Print how long system has been up.
D 56
	 * (Found by looking for "boottime" in kernel)
E 56
I 56
	 * (Found by looking getting "boottime" from the kernel)
E 56
	 */
D 56
	if ((kvm_read(kd, (u_long)nl[X_BOOTTIME].n_value,
	    &boottime, sizeof(boottime))) != sizeof(boottime))
		err(1, "can't read kernel bootime variable");
E 56
I 56
	mib[0] = CTL_KERN;
	mib[1] = KERN_BOOTTIME;
	size = sizeof(boottime);
D 57
	if (sysctl(mib, 2, &boottime, &size, NULL, 0) == -1)
		err(1, "cannot get kernel bootime");
E 56

	uptime = now - boottime.tv_sec;
	uptime += 30;
	days = uptime / SECSPERDAY;
	uptime %= SECSPERDAY;
	hrs = uptime / SECSPERHOUR;
	uptime %= SECSPERHOUR;
	mins = uptime / SECSPERMIN;
	(void)printf(" up");
	if (days > 0)
		(void)printf(" %d day%s,", days, days > 1 ? "s" : "");
	if (hrs > 0 && mins > 0)
		(void)printf(" %2d:%02d,", hrs, mins);
	else {
		if (hrs > 0)
			(void)printf(" %d hr%s,",
			    hrs, hrs > 1 ? "s" : "");
		if (mins > 0)
			(void)printf(" %d min%s,",
			    mins, mins > 1 ? "s" : "");
E 57
I 57
	if (sysctl(mib, 2, &boottime, &size, NULL, 0) != -1 &&
	    boottime.tv_sec != 0) {
		uptime = now - boottime.tv_sec;
		uptime += 30;
		days = uptime / SECSPERDAY;
		uptime %= SECSPERDAY;
		hrs = uptime / SECSPERHOUR;
		uptime %= SECSPERHOUR;
		mins = uptime / SECSPERMIN;
		(void)printf(" up");
		if (days > 0)
			(void)printf(" %d day%s,", days, days > 1 ? "s" : "");
		if (hrs > 0 && mins > 0)
			(void)printf(" %2d:%02d,", hrs, mins);
		else {
			if (hrs > 0)
				(void)printf(" %d hr%s,",
				    hrs, hrs > 1 ? "s" : "");
			if (mins > 0)
				(void)printf(" %d min%s,",
				    mins, mins > 1 ? "s" : "");
		}
E 57
	}

	/* Print number of users logged in to system */
	(void)printf(" %d user%s", nusers, nusers > 1 ? "s" : "");

	/*
	 * Print 1, 5, and 15 minute load averages.
	 */
D 56
	if (kvm_getloadavg(kd,
	    avenrun, sizeof(avenrun) / sizeof(avenrun[0])) == -1)
E 56
I 56
	if (getloadavg(avenrun, sizeof(avenrun) / sizeof(avenrun[0])) == -1)
E 56
		(void)printf(", no load average information available\n");
	else {
		(void)printf(", load averages:");
		for (i = 0; i < (sizeof(avenrun) / sizeof(avenrun[0])); i++) {
			if (i > 0)
				(void)printf(",");
			(void)printf(" %.2f", avenrun[i]);
		}
		(void)printf("\n");
	}
E 53
E 33
}

D 33
/* find & return number of minutes current tty has been idle */
I 26
time_t
E 26
findidle()
E 33
I 33
D 43
char *
strsave(cp)
	char *cp;
E 33
{
D 33
	struct stat stbuf;
	long lastaction, diff;
	char ttyname[20];
E 33
I 33
	register unsigned len;
	register char *dp;
E 33

D 27
	strcpy(ttyname, "/dev/");
	strcatn(ttyname, utmp.ut_line, LMAX);
E 27
I 27
D 33
	strcpy(ttyname, _PATH_DEV);
	strncat(ttyname, utmp.ut_line, UT_LINESIZE);
E 27
	stat(ttyname, &stbuf);
	time(&now);
	lastaction = stbuf.st_atime;
	diff = now - lastaction;
	diff = DIV60(diff);
	if (diff < 0) diff = 0;
	return(diff);
E 33
I 33
	len = strlen(cp);
	dp = (char *)calloc(len+1, sizeof (char));
	(void) strcpy(dp, cp);
	return (dp);
E 33
}
E 43
D 33

I 19
#define	HR	(60 * 60)
#define	DAY	(24 * HR)
#define	MON	(30 * DAY)

E 33
E 19
D 53
/*
D 19
 * prttime prints a time in hours and minutes.
E 19
I 19
 * prttime prints a time in hours and minutes or minutes and seconds.
E 19
 * The character string tail is printed at the end, obvious
 * strings to pass are "", " ", or "am".
 */
I 50
void
E 50
prttime(tim, tail)
	time_t tim;
	char *tail;
E 53
I 53
static struct stat *
ttystat(line)
	char *line;
E 53
{
I 53
	static struct stat sb;
	char ttybuf[MAXPATHLEN];
E 53
D 19
	register int didhrs = 0;
E 19

D 53
	if (tim >= 60) {
D 30
		printf("%3d:", tim/60);
E 30
I 30
		printf(" %2d:", tim/60);
E 30
D 19
		didhrs++;
	} else {
		printf("    ");
	}
	tim %= 60;
	if (tim > 0 || didhrs) {
		printf(didhrs&&tim<10 ? "%02d" : "%2d", tim);
	} else {
		printf("  ");
	}
E 19
I 19
		tim %= 60;
		printf("%02d", tim);
D 30
	} else if (tim > 0)
E 30
I 30
	} else if (tim >= 0)
E 30
		printf("    %2d", tim);
D 30
	else
		printf("      ");
E 30
E 19
	printf("%s", tail);
E 53
I 53
	(void)snprintf(ttybuf, sizeof(ttybuf), "%s/%s", _PATH_DEV, line);
	if (stat(ttybuf, &sb))
D 64
		err(1, "%s", ttybuf);
E 64
I 64
		return (NULL);
E 64
	return (&sb);
E 53
}

I 50
D 53
#if __STDC__
#include <stdarg.h>
#else
E 50
I 19
D 33
char *weekday[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
char *month[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
E 33
I 33
#include <varargs.h>
I 50
#endif
E 50
E 33

I 50
void
#if __STDC__
error(const char *fmt, ...)
#else
E 50
E 19
D 33
/* prtat prints a 12 hour time given a pointer to a time of day */
D 19
prtat(p)
	struct tm *p;
E 19
I 19
prtat(time)
	long *time;
E 33
I 33
D 47
warning(va_alist)
	va_dcl
E 33
E 19
{
D 19
	register int t, pm;
E 19
I 19
D 33
	struct tm *p;
	register int hr, pm;
E 33
I 33
	char *fmt;
	va_list ap;
E 33
E 19

D 19
	t = p -> tm_hour;
	pm = (t > 11);
	if (t > 11)
		t -= 12;
	if (t == 0)
		t = 12;
	prttime(t*60 + p->tm_min, pm ? "pm" : "am");
E 19
I 19
D 33
	p = localtime(time);
	hr = p->tm_hour;
	pm = (hr > 11);
	if (hr > 11)
		hr -= 12;
	if (hr == 0)
		hr = 12;
	if (now - *time <= 18 * HR)
		prttime(hr * 60 + p->tm_min, pm ? "pm" : "am");
	else if (now - *time <= 7 * DAY)
D 30
		printf(" %s%2d%s", weekday[p->tm_wday], hr, pm ? "pm" : "am");
E 30
I 30
		printf(" %*s%d%s", hr < 10 ? 4 : 3, weekday[p->tm_wday], hr,
		   pm ? "pm" : "am");
E 30
	else
		printf(" %2d%s%2d", p->tm_mday, month[p->tm_mon], p->tm_year);
E 33
I 33
	fprintf(stderr, "%s: warning: ", program);
	va_start(ap);
	fmt = va_arg(ap, char *);
	(void) vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
E 33
E 19
}

E 47
D 33
/*
 * readpr finds and reads in the array pr, containing the interesting
 * parts of the proc and user tables for each live process.
I 24
 * We only accept procs whos controlling tty has a pgrp equal to the
 * pgrp of the proc.  This accurately defines the notion of the current
 * process(s), but because of time skew, we always read in the tty struct
 * after reading the proc, even though the same tty struct may have been
 * read earlier on.
E 24
 */
readpr()
E 33
I 33
error(va_alist)
	va_dcl
I 50
#endif
E 53
I 53
static void
usage(wcmd)
	int wcmd;
E 53
E 50
E 33
{
I 50
D 53
#if !__STDC__
E 50
D 31
	int pn, mf, addr, c;
E 31
I 31
D 33
	int mf, addr, c;
E 31
	int szpt, pfnum, i;
	struct pte *Usrptma, *usrpt, *pte, apte;
	struct dblock db;
I 31
	struct kinfo_proc *kp;
	register struct proc *p;
	int nentries;
E 33
I 33
	char *fmt;
I 50
#endif
E 50
	va_list ap;
E 33
E 31

D 33
	Usrptma = (struct pte *) nl[X_USRPTMA].n_value;
	usrpt = (struct pte *) nl[X_USRPT].n_value;
D 27
	if((mem = open("/dev/mem", 0)) < 0) {
		fprintf(stderr, "No mem\n");
E 27
I 27
	if((mem = open(_PATH_MEM, 0)) < 0) {
		fprintf(stderr, "w: no %s.\n", _PATH_MEM);
E 27
		exit(1);
	}
D 27
	if ((swap = open("/dev/drum", 0)) < 0) {
		fprintf(stderr, "No drum\n");
E 27
I 27
	if ((swap = open(_PATH_DRUM, 0)) < 0) {
		fprintf(stderr, "w: no %s\n", _PATH_DRUM);
E 27
		exit(1);
	}
	/*
	 * read mem to find swap dev.
	 */
	lseek(kmem, (long)nl[X_SWAPDEV].n_value, 0);
	read(kmem, &nl[X_SWAPDEV].n_value, sizeof(nl[X_SWAPDEV].n_value));
	/*
D 11
	 * Find base of swap
E 11
I 11
	 * Find base of and parameters of swap
E 11
	 */
	lseek(kmem, (long)nl[X_NSWAP].n_value, 0);
	read(kmem, &nswap, sizeof(nswap));
I 11
	lseek(kmem, (long)nl[X_DMMIN].n_value, 0);
	read(kmem, &dmmin, sizeof(dmmin));
	lseek(kmem, (long)nl[X_DMMAX].n_value, 0);
	read(kmem, &dmmax, sizeof(dmmax));
E 11
	/*
D 31
	 * Locate proc table
E 31
I 31
	 * Read proc table.
E 31
	 */
I 3
D 31
	lseek(kmem, (long)nl[X_NPROC].n_value, 0);
	read(kmem, &nproc, sizeof(nproc));
	pr = (struct pr *)calloc(nproc, sizeof (struct pr));
E 31
E 3
	np = 0;
D 3
	for (pn=0; pn<NPROC; pn++) {
		lseek(kmem, (long)(nl[X_PROC].n_value + pn*(sizeof mproc)), 0);
E 3
I 3
D 31
	lseek(kmem, (long)nl[X_PROC].n_value, 0);
	read(kmem, &aproc, sizeof(aproc));
	for (pn=0; pn<nproc; pn++) {
		lseek(kmem, (int)(aproc + pn), 0);
E 3
		read(kmem, &mproc, sizeof mproc);
E 31
I 31
	nentries = kvm_getkproc(&kp);
	pr = (struct pr *)calloc(nentries, sizeof (struct pr));
	for (i=0; i < nentries; i++, kp++) {
D 32
fprintf(stderr, "kp->kp_pgid %d\n", kp->kp_pgid);
E 32
		p = &kp->kp_proc;
D 32
fprintf(stderr, "p->p_pid %d\n", p->p_pid);
E 32
E 31
		/* decide if it's an interesting process */
D 18
		if (mproc.p_stat==0 || mproc.p_pgrp==0)
E 18
I 18
D 24
		if (mproc.p_stat==0 || mproc.p_stat==SZOMB || mproc.p_pgrp==0)
E 24
I 24
D 31
		if (mproc.p_stat==0 || mproc.p_stat==SZOMB 
		    || mproc.p_stat==SSTOP || mproc.p_pgrp==0)
E 31
I 31
		if (p->p_stat==0 || p->p_stat==SZOMB 
		    || p->p_stat==SSTOP)
E 31
E 24
E 18
			continue;
D 5
		if (mproc.p_flag&SDETACH)
			continue;
E 5
D 3
		
#ifdef notdef
		/*
		 * The following speeds up w on systems with lots of ttys
		 * by ignoring inits and gettys, but loses on root login shells.
		 * On Ernie it reduced user and system time by .3 seconds,
		 * an insignificant amount.  It is commented out since it
		 * will lose when root logs in.
		 */
		if (mproc.p_uid == 0 & mproc.p_ppid == 1)
			continue;
#endif

E 3
		/* find & read in the user structure */
D 31
		if ((mproc.p_flag & SLOAD) == 0) {
E 31
I 31
		if ((p->p_flag & SLOAD) == 0) {
E 31
			/* not in memory - get from swap device */
D 10
			addr = mproc.p_swaddr<<9;
E 10
I 10
D 31
			addr = dtob(mproc.p_swaddr);
E 31
I 31
			addr = dtob(p->p_swaddr);
E 31
E 10
			lseek(swap, (long)addr, 0);
			if (read(swap, &up, sizeof(up)) != sizeof(up)) {
				continue;
			}
		} else {
			int p0br, cc;
#define INTPPG (NBPG / sizeof (int))
			struct pte pagetbl[NBPG / sizeof (struct pte)];
			/* loaded, get each page from memory separately */
D 31
			szpt = mproc.p_szpt;
			p0br = (int)mproc.p_p0br;
			pte = &Usrptma[btokmx(mproc.p_p0br) + szpt-1];
E 31
I 31
			szpt = p->p_szpt;
			p0br = (int)p->p_p0br;
			pte = &Usrptma[btokmx(p->p_p0br) + szpt-1];
E 31
			lseek(kmem, (long)pte, 0);
			if (read(kmem, &apte, sizeof(apte)) != sizeof(apte))
				continue;
			lseek(mem, ctob(apte.pg_pfnum), 0);
			if (read(mem,pagetbl,sizeof(pagetbl)) != sizeof(pagetbl))   
cont:
				continue;
			for(cc=0; cc<UPAGES; cc++) {	/* get u area */
				int upage = pagetbl[NPTEPG-UPAGES+cc].pg_pfnum;
				lseek(mem,ctob(upage),0);
				if (read(mem,((int *)&up)+INTPPG*cc,NBPG) != NBPG)
					goto cont;
			}
			szpt = up.u_pcb.pcb_szpt;
			pr[np].w_seekaddr = ctob(apte.pg_pfnum);
		}
D 4
		vstodb(0, 1, &up.u_smap, &db, 1);
E 4
I 4
		vstodb(0, CLSIZE, &up.u_smap, &db, 1);
E 4
D 10
		pr[np].w_lastpg = ctob(db.db_base);
E 10
I 10
		pr[np].w_lastpg = dtob(db.db_base);
E 10
D 31
		if (up.u_ttyp == NULL)
E 31
I 31
D 32
		if (kp->kp_tdev == NODEV)
E 32
I 32
		if (kp->kp_eproc.kp_tdev == NODEV)
E 32
E 31
I 24
			continue;

		/* only include a process whose tty has a pgrp which matchs its own */
D 28
		lseek(kmem, (long)up.u_ttyp, 0);
		if (read(kmem, &ttyent, sizeof(ttyent)) != sizeof(ttyent))
E 28
I 28
D 31
		lseek(kmem, (off_t)(&up.u_ttyp->t_pgid), 0);
		if (read(kmem, &tpgid, sizeof(tpgid)) != sizeof(tpgid))
E 31
I 31
D 32
		if (kp->kp_pgid != kp->kp_tpgid)
E 32
I 32
		if (kp->kp_eproc.kp_pgid != kp->kp_eproc.kp_tpgid)
E 32
E 31
E 28
			continue;
D 28
		if (ttyent.t_pgrp != mproc.p_pgrp)
E 28
I 28
D 31
		lseek(kmem, (off_t)(&mproc.p_pgrp->pg_id), 0);
		if (read(kmem, &pgid, sizeof(pgid)) != sizeof(pgid))
			continue;
		if (pgid != tpgid)
E 28
E 24
			continue;
E 31

		/* save the interesting parts */
D 31
		pr[np].w_pid = mproc.p_pid;
		pr[np].w_flag = mproc.p_flag;
		pr[np].w_size = mproc.p_dsize + mproc.p_ssize;
E 31
I 31
		pr[np].w_pid = p->p_pid;
		pr[np].w_flag = p->p_flag;
		pr[np].w_size = p->p_dsize + p->p_ssize;
E 31
D 10
		pr[np].w_igintr = (((int)up.u_signal[2]==1) + 2*((int)up.u_signal[2]>1) + 3*((int)up.u_signal[3]==1)) + 6*((int)up.u_signal[3]>1);
E 10
I 10
		pr[np].w_igintr = (((int)up.u_signal[2]==1) +
		    2*((int)up.u_signal[2]>1) + 3*((int)up.u_signal[3]==1)) +
		    6*((int)up.u_signal[3]>1);
E 10
D 7
		pr[np].w_time = up.u_vm.vm_utime + up.u_vm.vm_stime;
		pr[np].w_ctime = up.u_cvm.vm_utime + up.u_cvm.vm_stime;
E 7
I 7
		pr[np].w_time =
		    up.u_ru.ru_utime.tv_sec + up.u_ru.ru_stime.tv_sec;
		pr[np].w_ctime =
		    up.u_cru.ru_utime.tv_sec + up.u_cru.ru_stime.tv_sec;
E 7
D 31
		pr[np].w_tty = up.u_ttyd;
I 14
		pr[np].w_uid = mproc.p_uid;
E 14
		up.u_comm[14] = 0;	/* Bug: This bombs next field. */
		strcpy(pr[np].w_comm, up.u_comm);
E 31
I 31
D 32
		pr[np].w_tty = kp->kp_tdev;
E 32
I 32
		pr[np].w_tty = kp->kp_eproc.kp_tdev;
E 32
		pr[np].w_uid = p->p_uid;
		strcpy(pr[np].w_comm, p->p_comm, MAXCOMLEN+1);
E 31
		/*
		 * Get args if there's a chance we'll print it.
D 27
		 * Cant just save pointer: getargs returns static place.
		 * Cant use strcpyn: that crock blank pads.
E 27
I 27
		 * Can't just save pointer: getargs returns static place.
		 * Can't use strncpy, it blank pads.
E 27
		 */
		pr[np].w_args[0] = 0;
D 27
		strcatn(pr[np].w_args,getargs(&pr[np]),ARGWIDTH);
E 27
I 27
		strncat(pr[np].w_args,getargs(&pr[np]),ARGWIDTH);
E 27
		if (pr[np].w_args[0]==0 || pr[np].w_args[0]=='-' && pr[np].w_args[1]<=' ' || pr[np].w_args[0] == '?') {
			strcat(pr[np].w_args, " (");
			strcat(pr[np].w_args, pr[np].w_comm);
			strcat(pr[np].w_args, ")");
		}
		np++;
	}
E 33
I 33
	fprintf(stderr, "%s: ", program);
I 50
#if __STDC__
	va_start(ap, fmt);
#else
E 50
	va_start(ap);
	fmt = va_arg(ap, char *);
I 50
#endif
E 50
	(void) vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
E 53
I 53
	if (wcmd)
		(void)fprintf(stderr,
		    "usage: w: [-hin] [-M core] [-N system] [user]\n");
	else
		(void)fprintf(stderr, "uptime\n");
	exit (1);
E 53
E 33
D 47
}

D 33
/*
 * getargs: given a pointer to a proc structure, this looks at the swap area
 * and tries to reconstruct the arguments. This is straight out of ps.
 */
char *
getargs(p)
D 3
	struct smproc *p;
E 3
I 3
	struct pr *p;
E 33
I 33
syserror(va_alist)
	va_dcl
E 33
E 3
{
D 33
	int c, addr, nbad;
D 4
	static int abuf[512/sizeof(int)];
E 4
I 4
	static int abuf[CLSIZE*NBPG/sizeof(int)];
E 4
	struct pte pagetbl[NPTEPG];
	register int *ip;
	register char *cp, *cp1;
E 33
I 33
	char *fmt;
	va_list ap;
	extern errno;
E 33

D 33
	if ((p->w_flag & SLOAD) == 0) {
		lseek(swap, p->w_lastpg, 0);
		if (read(swap, abuf, sizeof(abuf)) != sizeof(abuf))
			return(p->w_comm);
	} else {
		c = p->w_seekaddr;
		lseek(mem,c,0);
		if (read(mem,pagetbl,NBPG) != NBPG)
			return(p->w_comm);
D 4
		if (pagetbl[NPTEPG-1-UPAGES].pg_fod==0 && pagetbl[NPTEPG-1-UPAGES].pg_pfnum) {
			lseek(mem,ctob(pagetbl[NPTEPG-1-UPAGES].pg_pfnum),0);
E 4
I 4
		if (pagetbl[NPTEPG-CLSIZE-UPAGES].pg_fod==0 && pagetbl[NPTEPG-CLSIZE-UPAGES].pg_pfnum) {
			lseek(mem,ctob(pagetbl[NPTEPG-CLSIZE-UPAGES].pg_pfnum),0);
E 4
			if (read(mem,abuf,sizeof(abuf)) != sizeof(abuf))
				return(p->w_comm);
		} else {
			lseek(swap, p->w_lastpg, 0);
			if (read(swap, abuf, sizeof(abuf)) != sizeof(abuf))
				return(p->w_comm);
		}
	}
D 4
	abuf[127] = 0;
	for (ip = &abuf[126]; ip > abuf;) {
E 4
I 4
	abuf[sizeof(abuf)/sizeof(abuf[0])-1] = 0;
	for (ip = &abuf[sizeof(abuf)/sizeof(abuf[0])-2]; ip > abuf;) {
E 4
		/* Look from top for -1 or 0 as terminator flag. */
		if (*--ip == -1 || *ip == 0) {
			cp = (char *)(ip+1);
			if (*cp==0)
				cp++;
			nbad = 0;	/* up to 5 funny chars as ?'s */
D 4
			for (cp1 = cp; cp1 < (char *)&abuf[128]; cp1++) {
E 4
I 4
			for (cp1 = cp; cp1 < (char *)&abuf[sizeof(abuf)/sizeof(abuf[0])]; cp1++) {
E 4
				c = *cp1&0177;
				if (c==0)  /* nulls between args => spaces */
					*cp1 = ' ';
				else if (c < ' ' || c > 0176) {
					if (++nbad >= 5) {
						*cp1++ = ' ';
						break;
					}
					*cp1 = '?';
				} else if (c=='=') {	/* Oops - found an
							 * environment var, back
							 * over & erase it. */
					*cp1 = 0;
					while (cp1>cp && *--cp1!=' ')
						*cp1 = 0;
					break;
				}
			}
			while (*--cp1==' ')	/* strip trailing spaces */
				*cp1 = 0;
			return(cp);
		}
	}
	return (p->w_comm);
}

/*
 * Given a base/size pair in virtual swap area,
 * return a physical base/size pair which is the
 * (largest) initial, physically contiguous block.
 */
vstodb(vsbase, vssize, dmp, dbp, rev)
	register int vsbase;
	int vssize;
	struct dmap *dmp;
	register struct dblock *dbp;
{
D 11
	register int blk = DMMIN;
E 11
I 11
	register int blk = dmmin;
E 11
	register swblk_t *ip = dmp->dm_map;

I 10
	vsbase = ctod(vsbase);
	vssize = ctod(vssize);
E 10
	if (vsbase < 0 || vsbase + vssize > dmp->dm_size)
		panic("vstodb");
	while (vsbase >= blk) {
		vsbase -= blk;
D 11
		if (blk < DMMAX)
E 11
I 11
		if (blk < dmmax)
E 11
			blk *= 2;
		ip++;
	}
	if (*ip <= 0 || *ip + blk > nswap)
		panic("vstodb *ip");
D 32
	dbp->db_size = min(vssize, blk - vsbase);
E 32
I 32
	dbp->db_size = MIN(vssize, blk - vsbase);
E 32
	dbp->db_base = *ip + (rev ? blk - (vsbase + dbp->db_size) : vsbase);
}

panic(cp)
	char *cp;
{

	/* printf("%s\n", cp); */
}

D 32
min(a, b)
{

	return (a < b ? a : b);
I 31
}

E 32
#define PROCSLOP	(5 * sizeof (struct kinfo_proc))
kvm_getkproc(bp)
	char **bp;
{
	int ret; 
	int copysize;
	int need;
	char *buff;

	if ((ret = syscall(63, KINFO_PROC_ALL, NULL, NULL, 0)) == -1) {
		perror("ktable, error getting estimate");
		return (0);
	}
	copysize = ret + PROCSLOP;   /* XXX PROCSLOP should be in header ? */
D 32
	fprintf(stderr, "kinfo: estimated %d, using %d\n", ret, copysize);
E 32
	buff = (char *)malloc(copysize);
	if (buff == NULL) {
		fprintf(stderr, "out of memory");
		exit (1);
	}
	if ((ret = syscall(63, KINFO_PROC_ALL, buff, &copysize, 0)) == -1) {
		perror("ktable");
		return (0);
	}
D 32
	fprintf(stderr, "kinfo: wanted: %d copied: %d\n", ret, copysize);
E 32
	*bp = buff;

	return (copysize / sizeof (struct kinfo_proc));
E 33
I 33
	fprintf(stderr, "%s: ", program);
	va_start(ap);
	fmt = va_arg(ap, char *);
	(void) vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, ": %s\n", strerror(errno));
E 47
E 33
E 31
}
E 1
