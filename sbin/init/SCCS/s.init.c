h50566
s 00003/00003/01268
d D 8.2 95/04/28 10:39:40 bostic 65 64
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00005/00005/01266
d D 8.1 93/07/15 17:39:43 bostic 64 63
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00000/01264
d D 6.24 93/07/15 17:39:22 mckusick 63 61
c do setlogin("root") to establish the single-user user
e
s 00005/00005/01259
d R 8.1 93/06/05 11:00:30 bostic 62 61
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00003/01249
d D 6.23 93/06/03 15:12:09 mckusick 61 60
c final update from BSDI
e
s 00052/00034/01200
d D 6.22 93/06/02 16:38:32 mckusick 60 59
c fix clean_ttys to reparse both getty string and window string;
c add prototypes and other lint
e
s 00019/00006/01215
d D 6.21 93/06/01 23:12:45 mckusick 59 58
c pass second argument to getty; reparse getty entry on restart
e
s 00001/00001/01220
d D 6.20 93/05/30 13:50:01 mckusick 58 57
c fix prototype for pid_t
e
s 00001/00002/01220
d D 6.19 93/05/27 22:38:52 mckusick 57 56
c cannot provide extra argument to getty or it dies
e
s 00001/00001/01221
d D 6.18 93/05/26 10:15:57 bostic 56 55
c update Donn's organization for general release
e
s 00003/00002/01219
d D 6.17 93/05/24 18:24:12 mckusick 55 54
c provide both pieces of getty info, roundup wait time on getty sleep
e
s 00018/00070/01203
d D 6.16 93/05/24 18:02:18 mckusick 54 53
c bug fixes and cleanups from BSDI
e
s 00008/00007/01265
d D 6.15 93/04/28 10:42:33 bostic 53 52
c <sys/sysctl.h> now needs param.h, "struct session" used in <sys/proc.h>
e
s 00002/00001/01270
d D 6.14 93/03/09 14:00:07 mckusick 52 51
c get those types right
e
s 00001/00001/01270
d D 6.13 93/03/09 13:57:43 mckusick 51 50
c cannot put sysctl.h before types.h even if that is alphabetical!
e
s 00102/00027/01169
d D 6.12 93/03/03 15:28:57 mckusick 50 48
c add code to change the system security level
e
s 00027/00000/01196
d D 6.11.1.1 92/07/19 17:04:55 marc 49 48
c hack to allow enabling early ktracing of init
e
s 00019/00001/01177
d D 6.11 92/07/19 17:02:52 marc 48 47
c add DEBUGSHELL to prompt for shell when /bin/sh exits abnormally
e
s 00008/00008/01170
d D 6.10 92/04/10 01:29:04 torek 47 46
c fix logout on hardwired (getty) lines such as console;
c get rid of magic numbers (use sizeof(_PATH_DEV) instead)
e
s 00005/00001/01173
d D 6.9 92/03/15 14:45:58 mckusick 46 45
c proper handling on HUP (from karels@bsdi.com)
e
s 00015/00007/01159
d D 6.8 92/03/02 16:35:44 bostic 45 43
c don't let users reexec init
e
s 00039/00008/01158
d R 6.8 92/03/02 15:41:49 bostic 44 43
c don't permit multiple invocations
e
s 00006/00004/01160
d D 6.7 92/01/17 16:56:41 torek 43 42
c db library does not preserve alignment: use bcopy
c fix minor gcc warnings (plug empty loops with dummy continue)
e
s 00002/00002/01162
d D 6.6 91/11/11 11:34:45 bostic 42 41
c hash_open -> db_open, delete R_PUT flag
e
s 00006/00001/01158
d D 6.5 91/07/25 17:13:37 trent 41 40
c fixed ignoring of TERM in single user mode (added transition code)
e
s 00011/00002/01148
d D 6.4 91/07/25 15:39:59 trent 40 39
c fixed "six shells on reboot" problem
e
s 00012/00020/01138
d D 6.3 91/07/17 19:30:41 mckusick 39 38
c do not fork separate processes to log messages 
c (but do note that these things should be done by a separate process)
e
s 00182/00090/00976
d D 6.2 91/07/05 08:35:48 mckusick 38 36
c first cut at getting it working (unfortunately not suceesful)
e
s 00098/00056/01010
d R 6.2 91/07/04 14:42:23 mckusick 37 36
c check in for Kirk, going to look at the DB stuff
e
s 00934/00455/00132
d D 6.1 91/07/02 18:20:02 mckusick 36 35
c initial rewritten version from Donn Seeley
e
s 00016/00015/00571
d D 5.19 91/03/25 17:49:43 karels 35 34
c (part from william) clean up the #ifdefs in main (slightly),
c use howto from args if present on any machine, default to 0
e
s 00012/00005/00574
d D 5.18 90/06/26 10:04:12 karels 34 33
c ignore SIGTSTP, HUP in rc; open console for writing, too!; more cleanup
e
s 00023/00018/00556
d D 5.17 90/06/24 14:16:19 karels 33 32
c fix shutdown bug in last delta; revoke console so single() doesn't fail;
c attempt some cleanup of #ifdef mess
e
s 00017/00004/00557
d D 5.16 90/05/27 20:13:42 mckusick 32 31
c add hp300 support from Utah
e
s 00035/00017/00526
d D 5.15 90/05/27 20:02:45 marc 31 30
c checked in for marc by mckusick
e
s 00010/00009/00533
d D 5.14 89/04/02 14:17:12 bostic 30 29
c add pathnames.h
e
s 00001/00003/00541
d D 5.13 88/09/22 11:26:37 bostic 29 28
c use constants in utmp.h
e
s 00006/00030/00538
d D 5.12 88/09/20 15:26:43 bostic 28 27
c use logwtmp()
e
s 00006/00054/00562
d D 5.11 88/08/31 12:18:43 bostic 27 26
c use library version of rmut
e
s 00001/00000/00615
d D 5.10 88/01/10 12:27:48 bostic 26 24
c declare merge() externally; ANSI C fix
e
s 00001/00000/00615
d R 5.10 87/12/26 13:03:41 bostic 25 24
c declare merege() externally, ANSI C fix
e
s 00002/00002/00613
d D 5.9 87/04/13 17:59:43 lepreau 24 23
c trivial speedup
e
s 00005/00006/00610
d D 5.8 87/02/17 16:51:40 bostic 23 22
c check for null pointers; bug report 4.3BSD/etc/35
e
s 00005/00002/00611
d D 5.7 86/10/13 15:01:53 sam 22 21
c tahoe's first register variable is r12
e
s 00004/00002/00609
d D 5.6 86/05/26 22:12:07 karels 21 20
c consistency, use SIGTERM once then SIGKILL's, uniform logging (once)
e
s 00001/00001/00610
d D 5.5 85/09/17 19:16:55 eric 20 19
c facilities in syslog
e
s 00001/00001/00610
d D 5.4 85/08/30 09:45:45 karels 19 18
c lengthen space for getty/window commands (70->200)
e
s 00089/00038/00522
d D 5.3 85/06/08 12:20:10 bloom 18 17
c Dynamically allocate structures instead of fixed size array
c 	(from ks@purdue-ecn)
e
s 00030/00010/00530
d D 5.2 85/06/05 14:38:18 karels 17 16
c unblock signals before fork, window mgr changes from jg
e
s 00009/00002/00531
d D 5.1 85/05/28 14:24:33 dist 16 15
c add copyright
e
s 00123/00074/00410
d D 4.15 85/04/01 12:38:41 ralph 15 14
c changes to exec a command from /etc/ttys besides getty, let getty open tty.
e
s 00010/00000/00474
d D 4.14 84/12/23 17:02:27 sam 14 13
c after logout give port selectors an opportunity to detect DTR 
c transition; also after proper login reset error detection code; from brl
e
s 00021/00066/00453
d D 4.13 84/05/07 11:36:52 root 13 12
c uses new getttyent(3) routines.
e
s 00160/00152/00359
d D 4.12 83/06/12 01:39:07 sam 12 11
c ostensibly make it work with new signals; lots of reformatting done as well
e
s 00007/00000/00504
d D 4.11 83/05/22 23:57:45 sam 11 10
c utmp changed format
e
s 00025/00000/00479
d D 4.10 82/12/22 06:22:43 pugs 10 9
c sun boot arg flags
e
s 00008/00003/00471
d D 4.9 82/12/07 21:29:54 pugs 9 8
c fix error messages in dfork
e
s 00001/00001/00473
d D 4.8 82/05/12 18:04:35 sam 8 7
c lost keywords (argh)
e
s 00020/00007/00454
d D 4.7 82/05/12 18:03:15 sam 7 6
c letting console be controlling tty -- causes vhangup on conosle
e
s 00024/00000/00437
d D 4.6 82/02/26 14:05:51 root 6 5
c timeout when terminals crazy
e
s 00028/00010/00409
d D 4.5 81/04/26 23:31:16 wnj 5 4
c dont write null wtmp entries; print console message when terminals are not openable
e
s 00051/00005/00368
d D 4.4 81/02/28 22:58:26 wnj 4 3
c new shutdown style
e
s 00032/00006/00341
d D 4.3 80/10/13 19:18:16 bill 3 2
c dont hang when kill 1 and procs hung
e
s 00024/00008/00323
d D 4.2 80/10/11 23:41:42 bill 2 1
c auto reboot stuff; use getty not getty.vm
e
s 00331/00000/00000
d D 4.1 80/10/01 17:27:08 bill 1 0
c date and time created 80/10/01 17:27:08 by bill
e
u
U
f b 
t
T
I 16
D 17

E 17
D 36
/*
D 21
 * Copyright (c) 1980 Regents of the University of California.
E 21
I 21
 * Copyright (c) 1980,1986 Regents of the University of California.
E 21
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 36
I 36
/*-
D 64
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 64
I 64
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 64
 *
 * This code is derived from software contributed to Berkeley by
D 56
 * Donn Seeley at UUNET Technologies, Inc.
E 56
I 56
 * Donn Seeley at Berkeley Software Design, Inc.
E 56
 *
 * %sccs.include.redist.c%
E 36
 */

E 16
I 11
#ifndef lint
I 36
D 64
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 64
I 64
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 64
#endif /* not lint */

#ifndef lint
E 36
E 11
I 3
D 7
static	char *sccsid = "%W% (Berkeley) %G%";
E 7
I 7
D 8
static	char *sccsid = "@(#)init.c	4.6 (Berkeley) 2/26/82";
E 8
I 8
D 16
static	char *sccsid = "%W% (Berkeley) %G%";
I 11
#endif
E 16
I 16
static char sccsid[] = "%W% (Berkeley) %G%";
D 36
#endif not lint
E 36
I 36
#endif /* not lint */
E 36
E 16

I 50
D 51
#include <sys/sysctl.h>
E 51
E 50
E 11
E 8
E 7
E 3
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
D 30
#include <signal.h>
E 30
D 53
#include <sys/types.h>
E 53
I 53
#include <sys/param.h>
E 53
I 51
#include <sys/sysctl.h>
E 51
D 28
#include <utmp.h>
E 28
D 30
#include <setjmp.h>
E 30
I 30
D 36
#include <sys/file.h>
#include <sys/signal.h>
E 30
I 2
#include <sys/reboot.h>
I 30
#include <sys/syslog.h>
#include <sys/stat.h>
I 31
#include <sys/ioctl.h>
E 31
#include <setjmp.h>
E 30
I 28
#include <utmp.h>
E 36
I 36
#include <sys/wait.h>
I 53

E 53
#include <db.h>
E 36
E 28
I 4
#include <errno.h>
I 36
#include <fcntl.h>
#include <signal.h>
I 53
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 53
D 45
#include <stdlib.h>
#include <string.h>
E 45
#include <syslog.h>
#include <time.h>
E 36
I 12
D 30
#include <sys/file.h>
E 30
I 13
#include <ttyent.h>
I 36
#include <unistd.h>
I 45
D 53
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 53
E 45

#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#ifdef SECURE
#include <pwd.h>
#endif

E 36
I 15
D 21
#include <syslog.h>
E 21
I 21
D 30
#include <sys/syslog.h>
E 21
I 18
#include <sys/stat.h>
E 30
I 30
#include "pathnames.h"
E 30
E 18
E 15
E 13
E 12
E 4
E 2

D 28
#define	LINSIZ	sizeof(wtmp.ut_line)
E 28
I 28
D 29
struct utmp ut;
#define	LINSIZ	sizeof(ut.ut_line)
E 29
E 28
I 13
D 15
#define	TTYSIZ	16
E 15
I 15
D 19
#define	CMDSIZ	70	/* max string length for getty or window command*/
E 19
I 19
D 36
#define	CMDSIZ	200	/* max string length for getty or window command*/
E 19
E 15
E 13
D 18
#define	TABSIZ	100
#define	ALL	p = &itab[0]; p < &itab[TABSIZ]; p++
E 18
I 18
#define	ALL	p = itab; p ; p = p->next
E 18
#define	EVER	;;
#define SCPYN(a, b)	strncpy(a, b, sizeof(a))
#define SCMPN(a, b)	strncmp(a, b, sizeof(a))
E 36
I 36
/*
 * Until the mythical util.h arrives...
 */
extern int login_tty __P((int));
extern int logout __P((const char *));
extern void logwtmp __P((const char *, const char *, const char *));
E 36
I 12
D 15
#define	mask(s)	(1 << ((s)-1))
E 15
E 12

D 30
char	shell[]	= "/bin/sh";
E 30
I 30
D 36
char	shell[]	= _PATH_BSHELL;
E 30
D 2
char	getty[]	 = "/etc/getty.vm";
E 2
I 2
D 15
char	getty[]	 = "/etc/getty";
E 15
E 2
char	minus[]	= "-";
D 30
char	runc[]	= "/etc/rc";
D 13
char	ifile[]	= "/etc/ttys";
E 13
D 18
char	utmp[]	= "/etc/utmp";
E 18
I 18
char	utmpf[]	= "/etc/utmp";
E 18
D 28
char	wtmpf[]	= "/usr/adm/wtmp";
E 28
char	ctty[]	= "/dev/console";
E 30
I 30
char	runc[]	= _PATH_RC;
D 31
char	utmpf[]	= _PATH_UTMP;
E 31
char	ctty[]	= _PATH_CONSOLE;
E 36
I 36
/*
 * Sleep times; used to prevent thrashing.
 */
D 38
#define	GETTY_SPACING		60	/* fork getty on a port every N secs */
E 38
I 38
D 61
#define	GETTY_SPACING		10	/* fork getty on a port every N secs */
E 61
I 61
#define	GETTY_SPACING		 5	/* N secs minimum getty spacing */
#define	GETTY_SLEEP		30	/* sleep N secs after spacing problem */
E 61
E 38
#define	WINDOW_WAIT		 3	/* wait N secs after starting window */
#define	STALL_TIMEOUT		30	/* wait N secs after warning */
D 38
#define	DEATH_WATCH		30	/* wait N secs for procs to die */
E 38
I 38
#define	DEATH_WATCH		10	/* wait N secs for procs to die */
E 38
E 36
E 30
D 15
char	dev[]	= "/dev/";
E 15

D 28
struct utmp wtmp;
E 28
D 13
struct
{
	char	line[LINSIZ];
	char	comn;
	char	flag;
} line;
E 13
D 36
struct	tab
{
D 29
	char	line[LINSIZ];
E 29
I 29
	char	line[UT_LINESIZE];
E 29
D 13
	char	comn;
E 13
I 13
D 15
	char	comn[TTYSIZ];
E 15
I 15
	char	comn[CMDSIZ];
E 15
E 13
	char	xflag;
	int	pid;
I 15
	int	wpid;		/* window system pid for SIGHUP	*/
	char	wcmd[CMDSIZ];	/* command to start window system process */
E 15
I 6
	time_t	gettytime;
	int	gettycnt;
I 17
	time_t	windtime;
	int	windcnt;
E 17
E 6
D 18
} itab[TABSIZ];
E 18
I 18
	struct	tab *next;
} *itab;
E 36
I 36
void handle __P((sig_t, ...));
void delset __P((sigset_t *, ...));
E 36
E 18

D 36
int	fi;
int	mergflag;
char	tty[20];
D 3
jmp_buf	sjbuf;
E 3
I 3
jmp_buf	sjbuf, shutpass;
E 36
I 36
void stall __P((char *, ...));
void warning __P((char *, ...));
void emergency __P((char *, ...));
void disaster __P((int));
I 50
void badsys __P((int));
E 50
E 36
I 4
D 28
time_t	time0;
E 28
E 4
E 3

D 31
int	reset();
I 4
int	idle();
E 31
E 4
D 36
char	*strcpy(), *strcat();
long	lseek();
I 31
void	idle(), merge(), reset();
E 36
I 36
/*
 * We really need a recursive typedef...
 * The following at least guarantees that the return type of (*state_t)()
 * is sufficiently wide to hold a function pointer.
 */
typedef long (*state_func_t) __P((void));
typedef state_func_t (*state_t) __P((void));
E 36
E 31

I 10
D 12
#ifndef sun
E 12
I 12
D 15
struct	sigvec rvec = { reset, mask(SIGHUP), 0 };
E 15
I 15
D 36
struct	sigvec rvec = { reset, sigmask(SIGHUP), 0 };
E 36
I 36
state_func_t single_user __P((void));
state_func_t runcom __P((void));
state_func_t read_ttys __P((void));
state_func_t multi_user __P((void));
state_func_t clean_ttys __P((void));
state_func_t catatonia __P((void));
state_func_t death __P((void));
E 36
E 15

I 36
enum { AUTOBOOT, FASTBOOT } runcom_mode = AUTOBOOT;

void transition __P((state_t));
state_t requested_transition = runcom;

void setctty __P((char *));

D 53
typedef struct session {
E 53
I 53
typedef struct init_session {
E 53
	int	se_index;		/* index of entry in ttys file */
	pid_t	se_process;		/* controlling process */
	time_t	se_started;		/* used to avoid thrashing */
	int	se_flags;		/* status of session */
#define	SE_SHUTDOWN	0x1		/* session won't be restarted */
	char	*se_device;		/* filename of port */
	char	*se_getty;		/* what to run on that port */
	char	**se_getty_argv;	/* pre-parsed argument array */
	char	*se_window;		/* window system (started only once) */
	char	**se_window_argv;	/* pre-parsed argument array */
D 53
	struct	session *se_prev;
	struct	session *se_next;
E 53
I 53
	struct	init_session *se_prev;
	struct	init_session *se_next;
E 53
} session_t;

void free_session __P((session_t *));
session_t *new_session __P((session_t *, int, struct ttyent *));
session_t *sessions;

char **construct_argv __P((char *));
void start_window_system __P((session_t *));
I 38
D 58
void collect_child __P((int));
E 58
I 58
void collect_child __P((pid_t));
E 58
E 38
pid_t start_getty __P((session_t *));
D 38
void chld_handler __P((int));
E 38
void transition_handler __P((int));
void alrm_handler __P((int));
I 60
void setsecuritylevel __P((int));
int getsecuritylevel __P((void));
int setupargv __P((session_t *, struct ttyent *));
E 60
int clang;

D 54
int start_logger __P((void));
E 54
void clear_session_logs __P((session_t *));
D 54
int logger_enable;
E 54

D 38
void start_session_db __P((void));
E 38
I 38
int start_session_db __P((void));
E 38
void add_session __P((session_t *));
void del_session __P((session_t *));
session_t *find_session __P((pid_t));
DB *session_db;

D 38
sigset_t multi_sig_mask;
sigset_t death_mask;

E 38
I 38
/*
 * The mother of all processes.
 */
E 38
int
E 36
I 18
D 31

E 31
E 18
D 22
#ifdef vax
E 22
I 22
D 32
#if defined(vax) || defined(tahoe)
E 32
I 32
D 33
#if defined(vax) || defined(tahoe) || defined(hp300)
E 32
E 22
E 12
E 10
main()
E 33
I 33
main(argc, argv)
I 36
	int argc;
E 36
	char **argv;
E 33
{
I 35
D 36
	/* insure proper semantics for setjmp/longjmp */
	static int howto, oldhowto, started = 0;
E 35
I 22
#if defined(tahoe)
	register int r12;		/* make sure r11 gets bootflags */
#endif
I 33
#if defined(vax) || defined(tahoe) || defined(hp300)
I 35
	/* howto passed in high-order register XXX */
E 35
E 33
E 22
I 2
	register int r11;		/* passed thru from boot */
I 10
D 12
#else sun
E 12
I 12
D 33
#else
E 12
main(argc, argv)
	char **argv;
{
E 33
D 12
#endif sun
E 12
I 12
D 35
#endif
E 35
I 32
#ifdef __GNUC__
D 35
	/* insure proper semantics for setjmp/longjmp */
	static
#endif
E 32
E 12
E 10
D 31
	int howto, oldhowto;
E 31
I 31
D 33
	int howto, oldhowto, started;
E 33
I 33
	int howto, oldhowto, started = 0;
E 33
E 31

I 33
#if defined(vax) || defined(tahoe) || defined(hp300)
	/* howto passed in high-order register XXX */
E 33
I 4
D 28
	time0 = time(0);
E 28
I 10
D 12
#ifndef sun
E 12
I 12
D 22
#ifdef vax
E 22
I 22
D 32
#if defined(vax) || defined(tahoe)
E 32
I 32
#ifdef __GNUC__
E 35
#ifdef hp300
	asm("movl d7,%0" : "=rm" (howto));
#else
	asm("movl r11,%0" : "=rm" (howto));
#endif
#else
D 33
#if defined(vax) || defined(tahoe) || defined(hp300)
E 33
E 32
E 22
E 12
E 10
E 4
	howto = r11;
I 10
D 12
#else sun
E 12
I 12
D 33
#else
I 31
	howto = 0;
E 33
I 33
#endif /* __GNUC__ */
D 35
#else  /* defined(vax) || defined(tahoe) || defined(hp300) */
E 35
I 35
#else  /* vax || tahoe || hp300 */
E 35
	/* howto passed as argument */
I 35
	howto = 0;
#endif  /* ! (vax || tahoe || hp300) */
E 36
I 36
	int c;
I 38
	struct sigaction sa;
E 38
	sigset_t mask;
E 36

D 45
	/*
D 36
	 * We expect a single options argument from the kernel.
	 * If it is present, we ignore anything in registers from above.
E 36
I 36
	 * Silently dispose of random users running this program.
E 36
	 */
E 35
E 33
E 31
E 12
D 36
	if (argc > 1 && argv[1][0] == '-') {
		char *cp;
E 36
I 36
	if (getuid() != 0)
		return 1;
E 45
I 45

	/* Dispose of random users. */
	if (getuid() != 0) {
		(void)fprintf(stderr, "init: %s\n", strerror(EPERM));
		exit (1);
	}

	/* System V users like to reexec init. */
	if (getpid() != 1) {
		(void)fprintf(stderr, "init: already running\n");
		exit (1);
	}
E 45
E 36

I 32
D 36
		howto = 0;
E 32
D 31
		howto = 0;
E 31
		cp = &argv[1][1];
		while (*cp) switch (*cp++) {
D 35
		case 'a':
			howto |= RB_ASKNAME;
E 35
I 35
#ifdef notyet
E 36
I 36
	/*
	 * Note that this does NOT open a file...
	 * Does 'init' deserve its own facility number?
	 */
D 38
	openlog("init", LOG_CONS, LOG_DAEMON);
E 38
I 38
	openlog("init", LOG_CONS|LOG_ODELAY, LOG_AUTH);
E 38

	/*
I 38
	 * Create an initial session.
	 */
	if (setsid() < 0)
D 54
		syslog(LOG_ERR, "setsid failed (initial) %m");
E 54
I 54
		warning("initial setsid() failed: %m");
E 54

	/*
I 63
	 * Establish an initial user so that programs running
	 * single user do not freak out and die (like passwd).
	 */
	if (setlogin("root") < 0)
		warning("setlogin() failed: %m");

	/*
E 63
E 38
	 * This code assumes that we always get arguments through flags,
	 * never through bits set in some random machine register.
	 */
	while ((c = getopt(argc, argv, "sf")) != -1)
		switch (c) {
		case 's':
			requested_transition = single_user;
			break;
E 36
		case 'f':
D 36
			howto |= RB_FASTBOOT;
E 36
I 36
			runcom_mode = FASTBOOT;
E 36
E 35
			break;
I 35
D 36
#endif
E 35
		case 's':
			howto |= RB_SINGLE;
E 36
I 36
		default:
			warning("unrecognized flag '-%c'", c);
E 36
			break;
		}
I 36

	if (optind != argc)
		warning("ignoring excess arguments");

	/*
	 * We catch or block signals rather than ignore them,
	 * so that they get reset on exec.
	 */
I 50
	handle(badsys, SIGSYS, 0);
E 50
	handle(disaster, SIGABRT, SIGFPE, SIGILL, SIGSEGV,
D 50
	       SIGBUS, SIGSYS, SIGXCPU, SIGXFSZ, 0);
E 50
I 50
	       SIGBUS, SIGXCPU, SIGXFSZ, 0);
E 50
	handle(transition_handler, SIGHUP, SIGTERM, SIGTSTP, 0);
	handle(alrm_handler, SIGALRM, 0);
D 38
	handle(chld_handler, SIGCHLD, 0);
E 38
	sigfillset(&mask);
D 38
	delset(&mask, SIGABRT, SIGFPE, SIGILL, SIGSEGV,
		SIGBUS, SIGSYS, SIGXCPU, SIGXFSZ, 0);
E 38
I 38
	delset(&mask, SIGABRT, SIGFPE, SIGILL, SIGSEGV, SIGBUS, SIGSYS,
		SIGXCPU, SIGXFSZ, SIGHUP, SIGTERM, SIGTSTP, SIGALRM, 0);
E 38
	sigprocmask(SIG_SETMASK, &mask, (sigset_t *) 0);
D 38
	multi_sig_mask = mask;
	delset(&multi_sig_mask, SIGHUP, SIGTERM, SIGTSTP, SIGCHLD, 0);
	death_mask = mask;
	delset(&death_mask, SIGCHLD, SIGALRM);
E 38
I 38
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	(void) sigaction(SIGTTIN, &sa, (struct sigaction *)0);
	(void) sigaction(SIGTTOU, &sa, (struct sigaction *)0);
E 38

	/*
	 * Paranoia.
	 */
	close(0);
	close(1);
	close(2);

	/*
	 * Start the state machine.
	 */
	transition(requested_transition);

	/*
	 * Should never reach here.
	 */
	return 1;
}

I 38
/*
 * Associate a function with a signal handler.
 */
E 38
void
#ifdef __STDC__
handle(sig_t handler, ...)
#else
handle(va_alist)
	va_dcl
#endif
{
	int sig;
	struct sigaction sa;
	int mask_everything;
	va_list ap;
#ifndef __STDC__
	sig_t handler;

	va_start(ap);
	handler = va_arg(ap, sig_t);
#else
	va_start(ap, handler);
#endif

	sa.sa_handler = handler;
	sigfillset(&mask_everything);

	while (sig = va_arg(ap, int)) {
		sa.sa_mask = mask_everything;
		/* XXX SA_RESTART? */
		sa.sa_flags = sig == SIGCHLD ? SA_NOCLDSTOP : 0;
		sigaction(sig, &sa, (struct sigaction *) 0);
E 36
D 33
	} else {
E 33
I 33
D 35
	} else
E 33
		howto = RB_SINGLE;
D 33
	}
E 33
D 12
#endif sun
E 10
E 2
	setjmp(sjbuf);
	signal(SIGTERM, reset);
E 12
I 12
#endif
E 35
I 35
	}
I 61
	va_end(ap);
E 61
E 35
I 32
D 33
#endif /* !__GNUC__ */
E 33
E 32
I 31
D 36
	if (getuid() != 0)
		exit(1);
E 31
I 15
D 20
	openlog("init", LOG_CONS|LOG_ODELAY, 0);
E 20
I 20
	openlog("init", LOG_CONS|LOG_ODELAY, LOG_AUTH);
I 31
	if (setsid() < 0)
		syslog(LOG_ERR, "setsid failed (initial) %m");
E 31
E 20
E 15
	sigvec(SIGTERM, &rvec, (struct sigvec *)0);
E 12
I 4
	signal(SIGTSTP, idle);
E 4
D 34
	signal(SIGSTOP, SIG_IGN);
E 34
D 4
	signal(SIGTSTP, SIG_IGN);
E 4
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
D 12
	for(EVER) {
E 12
I 12
	(void) setjmp(sjbuf);
D 31
	for (EVER) {
E 31
I 31
D 33
	for (started = 0; ; ) {
E 33
I 33
	for (; ; ) {
E 33
E 31
E 12
I 2
		oldhowto = howto;
		howto = RB_SINGLE;
E 2
D 3
		shutdown();
E 3
I 3
D 31
		if (setjmp(shutpass) == 0)
E 31
I 31
		if (started && setjmp(shutpass) == 0)
E 31
			shutdown();
I 31
		started = 1;
E 31
E 3
D 2
		single();
		runcom();
E 2
I 2
		if (oldhowto & RB_SINGLE)
			single();
		if (runcom(oldhowto) == 0) 
			continue;
E 2
		merge();
		multiple();
	}
E 36
}

I 38
/*
 * Delete a set of signals from a mask.
 */
E 38
I 3
D 31
int	shutreset();
E 31
I 31
D 36
void	shutreset();
E 36
I 36
void
#ifdef __STDC__
delset(sigset_t *maskp, ...)
#else
delset(va_alist)
	va_dcl
#endif
{
	int sig;
	va_list ap;
#ifndef __STDC__
	sigset_t *maskp;
E 36
E 31

E 3
D 36
shutdown()
E 36
I 36
	va_start(ap);
	maskp = va_arg(ap, sigset_t *);
#else
	va_start(ap, maskp);
#endif

	while (sig = va_arg(ap, int))
		sigdelset(maskp, sig);
I 61
	va_end(ap);
E 61
}

/*
 * Log a message and sleep for a while (to give someone an opportunity
 * to read it and to save log or hardcopy output if the problem is chronic).
D 39
 * We fork so that we can't block on I/O when writing the message,
 * and so that init proper doesn't acquire another open file.
 * If the fork fails, or the child can't finish, too bad.
E 39
I 39
 * NB: should send a message to the session logger to avoid blocking.
E 39
 */
void
#ifdef __STDC__
stall(char *message, ...)
#else
stall(va_alist)
	va_dcl
#endif
E 36
{
D 36
	register i;
D 18
	register struct tab *p;
E 18
I 18
	register struct tab *p, *p1;
E 36
I 36
D 60
	pid_t pid;
E 60
	va_list ap;
#ifndef __STDC__
	char *message;
E 36
E 18

D 18
	close(creat(utmp, 0644));
E 18
I 18
D 31
	close(creat(utmpf, 0644));
E 31
E 18
D 36
	signal(SIGHUP, SIG_IGN);
D 12
	for(ALL) {
E 12
I 12
D 18
	for (ALL) {
E 18
I 18
	for (p = itab; p ; ) {
E 18
E 12
		term(p);
D 18
		p->line[0] = 0;
E 18
I 18
		p1 = p->next;
		free(p);
		p = p1;
E 36
I 36
	va_start(ap);
	message = va_arg(ap, char *);
#else
	va_start(ap, message);
#endif

D 39
	if ((pid = fork()) == 0) {
		vsyslog(LOG_ALERT, message, ap);
		_exit(0);
E 36
E 18
	}
E 39
I 39
	vsyslog(LOG_ALERT, message, ap);
E 39
I 18
D 36
	itab = (struct tab *)0;
E 18
D 3
	signal(SIGALRM, reset);
	alarm(60);
E 3
I 3
	signal(SIGALRM, shutreset);
I 21
	(void) kill(-1, SIGTERM);	/* one chance to catch it */
	sleep(5);
E 21
	alarm(30);
E 3
D 12
	for(i=0; i<5; i++)
E 12
I 12
	for (i = 0; i < 5; i++)
E 12
		kill(-1, SIGKILL);
D 12
	while(wait((int *)0) != -1)
E 12
I 12
	while (wait((int *)0) != -1)
E 12
		;
	alarm(0);
I 3
	shutend();
E 36
I 36
	va_end(ap);
	sleep(STALL_TIMEOUT);
D 39
	if (pid != -1)
		waitpid(pid, (int *) 0, WNOHANG);
E 39
E 36
}

D 23
char shutfailm[] = "WARNING: Something is hung (wont die); ps axl advised\n";
E 23
I 23
D 31
char shutfailm[] = "WARNING: Something is hung (won't die); ps axl advised\n";
E 31
I 31
D 36
char shutfailm[] = "init: WARNING: something is hung (won't die); ps axl advised\n";
E 31
E 23

E 36
I 36
/*
 * Like stall(), but doesn't sleep.
 * If cpp had variadic macros, the two functions could be #defines for another.
I 39
 * NB: should send a message to the session logger to avoid blocking.
E 39
 */
E 36
I 31
void
E 31
D 36
shutreset()
E 36
I 36
#ifdef __STDC__
warning(char *message, ...)
#else
warning(va_alist)
	va_dcl
#endif
E 36
{
D 36
	int status;
E 36
I 36
	va_list ap;
#ifndef __STDC__
	char *message;
E 36

I 36
	va_start(ap);
	message = va_arg(ap, char *);
#else
	va_start(ap, message);
#endif

E 36
D 39
	if (fork() == 0) {
D 36
		int ct = open(ctty, 1);
		write(ct, shutfailm, sizeof (shutfailm));
		sleep(5);
		exit(1);
E 36
I 36
		vsyslog(LOG_ALERT, message, ap);
		_exit(0);
E 36
	}
E 39
I 39
	vsyslog(LOG_ALERT, message, ap);
E 39
D 36
	sleep(5);
	shutend();
	longjmp(shutpass, 1);
E 36
I 36
	va_end(ap);
E 36
}

D 36
shutend()
E 36
I 36
/*
D 39
 * Log a message, no forking, no waiting.
 * We take care to close syslog's file descriptor, however.
E 39
I 39
 * Log an emergency message.
 * NB: should send a message to the session logger to avoid blocking.
E 39
 */
void
#ifdef __STDC__
emergency(char *message, ...)
#else
emergency(va_alist)
	va_dcl
#endif
E 36
{
D 4
	register i;
E 4
I 4
D 32
	register i, f;
E 32
I 32
D 36
	register i;
E 36
I 36
	va_list ap;
#ifndef __STDC__
	char *message;
E 36
E 32
E 4

I 4
D 36
	acct(0);
E 4
E 3
	signal(SIGALRM, SIG_DFL);
D 12
	for(i=0; i<10; i++)
E 12
I 12
	for (i = 0; i < 10; i++)
E 12
		close(i);
I 4
D 12
	f = open(wtmpf, 1);
E 12
I 12
D 28
	f = open(wtmpf, O_WRONLY|O_APPEND);
E 12
	if (f >= 0) {
D 12
		lseek(f, 0L, 2);
E 12
		SCPYN(wtmp.ut_line, "~");
		SCPYN(wtmp.ut_name, "shutdown");
I 11
		SCPYN(wtmp.ut_host, "");
E 11
		time(&wtmp.ut_time);
		write(f, (char *)&wtmp, sizeof(wtmp));
		close(f);
	}
D 12
	return(1);
E 12
I 12
	return (1);
E 28
I 28
	logwtmp("~", "shutdown", "");
E 36
I 36
	va_start(ap);
	message = va_arg(ap, char *);
#else
	va_start(ap, message);
#endif

	vsyslog(LOG_EMERG, message, ap);
	va_end(ap);
D 39
	closelog();
D 38
	openlog("init", LOG_CONS, LOG_DAEMON);
E 38
I 38
	openlog("init", LOG_CONS|LOG_ODELAY, LOG_AUTH);
E 39
E 38
E 36
E 28
E 12
E 4
}

I 38
/*
I 50
 * Catch a SIGSYS signal.
 *
 * These may arise if a system does not support sysctl.
 * We tolerate up to 25 of these, then throw in the towel.
 */
void
badsys(sig)
	int sig;
{
	static int badcount = 0;

	if (badcount++ < 25)
		return;
	disaster(sig);
}

/*
E 50
 * Catch an unexpected signal.
 */
E 38
D 36
single()
E 36
I 36
void
disaster(sig)
	int sig;
E 36
{
D 36
	register pid;
I 4
	register xpid;
I 33
	int fd;
E 33
D 28
	extern	errno;
E 28
I 28
	extern int errno;
E 36
I 36
	emergency("fatal signal: %s",
		sig < (unsigned) NSIG ? sys_siglist[sig] : "unknown signal");
E 36
E 28
E 4

I 4
D 12
   do {
E 4
	pid = fork();
	if(pid == 0) {
/*
		alarm(300);
*/
		signal(SIGTERM, SIG_DFL);
		signal(SIGHUP, SIG_DFL);
		signal(SIGALRM, SIG_DFL);
		open(ctty, 2);
		dup(0);
		dup(0);
		execl(shell, minus, (char *)0);
		exit(0);
	}
D 4
	while(wait((int *)0) != pid)
		;
E 4
I 4
	while((xpid = wait((int *)0)) != pid)
		if (xpid == -1 && errno == ECHILD)
			break;
   } while (xpid == -1);
E 12
I 12
D 36
	do {
		pid = fork();
		if (pid == 0) {
			signal(SIGTERM, SIG_DFL);
			signal(SIGHUP, SIG_DFL);
			signal(SIGALRM, SIG_DFL);
I 13
			signal(SIGTSTP, SIG_IGN);
I 31
			if (setsid() < 0)
				syslog(LOG_ERR, "setsid failed (single): %m");
E 31
E 13
D 33
			(void) open(ctty, O_RDWR);
I 31
			if (ioctl(0, TIOCSCTTY, 0) < 0)
E 33
I 33
			(void) revoke(ctty);
			if ((fd = open(ctty, O_RDWR)) < 0) {
				syslog(LOG_ERR, "open %s: %m", ctty);
				exit(1);
			}
			if (ioctl(fd, TIOCSCTTY, 0) < 0)
E 33
				syslog(LOG_ERR, "TIOCSCTTY failed: %m");
E 31
D 33
			dup2(0, 1);
			dup2(0, 2);
E 33
I 33
			dup2(fd, 0);
			dup2(fd, 1);
			dup2(fd, 2);
			if (fd > 2)
				close(fd);
E 33
			execl(shell, minus, (char *)0);
I 23
			perror(shell);
E 23
			exit(0);
		}
		while ((xpid = wait((int *)0)) != pid)
			if (xpid == -1 && errno == ECHILD)
				break;
	} while (xpid == -1);
E 36
I 36
	sleep(STALL_TIMEOUT);
	_exit(sig);		/* reboot */
E 36
E 12
E 4
}

D 2
runcom()
E 2
I 2
D 36
runcom(oldhowto)
	int oldhowto;
E 36
I 36
/*
I 50
 * Get the security level of the kernel.
 */
int
getsecuritylevel()
{
I 61
#ifdef KERN_SECURELVL
E 61
D 52
	int name[2], len, curlevel;
E 52
I 52
	int name[2], curlevel;
	size_t len;
E 52
	extern int errno;

	name[0] = CTL_KERN;
	name[1] = KERN_SECURELVL;
	len = sizeof curlevel;
	if (sysctl(name, 2, &curlevel, &len, NULL, 0) == -1) {
		emergency("cannot get kernel security level: %s",
		    strerror(errno));
		return (-1);
	}
	return (curlevel);
I 61
#else
	return (-1);
#endif
E 61
}

/*
 * Set the security level of the kernel.
 */
I 60
void
E 60
setsecuritylevel(newlevel)
	int newlevel;
{
I 61
#ifdef KERN_SECURELVL
E 61
D 60
	int name[2], len, curlevel;
E 60
I 60
	int name[2], curlevel;
E 60
	extern int errno;

	curlevel = getsecuritylevel();
	if (newlevel == curlevel)
		return;
	name[0] = CTL_KERN;
	name[1] = KERN_SECURELVL;
	if (sysctl(name, 2, NULL, NULL, &newlevel, sizeof newlevel) == -1) {
		emergency(
		    "cannot change kernel security level from %d to %d: %s",
		    curlevel, newlevel, strerror(errno));
		return;
	}
#ifdef SECURE
	warning("kernel security level changed from %d to %d",
	    curlevel, newlevel);
#endif
I 61
#endif
E 61
}

/*
E 50
 * Change states in the finite state machine.
 * The initial state is passed as an argument.
 */
void
transition(s)
	state_t s;
E 36
E 2
{
D 32
	register pid, f;
E 32
I 32
D 36
	register pid;
E 32
I 2
D 34
	int status;
E 34
I 34
	int fd, status;
E 36
I 36
	for (;;)
		s = (state_t) (*s)();
}
E 36
E 34
E 2

D 36
	pid = fork();
E 36
I 36
/*
D 54
 * We send requests for session logging to another process for two reasons.
 * First, we don't want to block if the log files go away (e.g. because
 * one or more are on hard-mounted NFS systems whose server crashes).
 * Second, despite all the crud already contained in init, it still isn't
 * right that init should care about session logging record formats and files.
 * We could use explicit 'Unix' IPC for this, but let's try to be POSIX...
 */
int
start_logger()
{
	static char *argv[] = { _PATH_SLOGGER, 0 };
	int fd, pfd[2];
	pid_t pid;
	sigset_t mask;

	if (pipe(pfd) == -1) {
		warning("session logging disabled: can't make pipe to %s: %m",
			  argv[0]);
		return -1;
	}
	if ((pid = fork()) == -1) {
		emergency("session logging disabled: can't fork for %s: %m",
			  argv[0]);
		return -1;
	}

E 36
D 12
	if(pid == 0) {
		open("/", 0);
		dup(0);
		dup(0);
E 12
I 12
	if (pid == 0) {
D 31
		(void) open("/", O_RDONLY);
E 31
I 31
D 34
		(void) open(ctty, O_RDONLY);
E 31
		dup2(0, 1);
		dup2(0, 2);
E 34
I 34
D 36
		signal(SIGTSTP, SIG_IGN);
		signal(SIGHUP, SIG_IGN);
		if ((fd = open(ctty, O_RDWR)) < 0)
			syslog(LOG_ERR, "open %s: %m", ctty);
		else {
			dup2(fd, 0);
			dup2(fd, 1);
			dup2(fd, 2);
			if (fd > 2)
E 36
I 36
		close(pfd[1]);
		if (pfd[0] != 0) {
			dup2(pfd[0], 0);
			close(pfd[0]);
		}
		if ((fd = open(_PATH_DEVNULL, O_WRONLY)) != -1) {
			if (fd != 1)
				dup2(fd, 1);
			if (fd != 2)
				dup2(fd, 2);
			if (fd != 1 && fd != 2)
E 36
				close(fd);
I 36
		} else {
			/* paranoid */
			close(1);
			close(2);
E 36
		}
E 34
I 31
D 36
		if (setsid() < 0)
			syslog(LOG_ERR, "setsid failed (runcom) %m");
		if (ioctl(0, TIOCSCTTY, 0) < 0) 
			syslog(LOG_ERR, "TIOCSCTTY failed (runcom) %m");
E 31
E 12
D 2
		execl(shell, shell, runc, (char *)0);
		exit(0);
E 2
I 2
		if (oldhowto & RB_SINGLE)
			execl(shell, shell, runc, (char *)0);
		else
			execl(shell, shell, runc, "autoboot", (char *)0);
		exit(1);
E 36
I 36
		sigemptyset(&mask);
		sigprocmask(SIG_SETMASK, &mask, (sigset_t *) 0);
		execv(argv[0], argv);
		stall("can't exec %s: %m", argv[0]);
		_exit(1);
E 36
E 2
	}
D 2
	while(wait((int *)0) != pid)
E 2
I 2
D 12
	while(wait(&status) != pid)
E 12
I 12
D 36
	while (wait(&status) != pid)
E 12
E 2
		;
I 2
D 12
	if(status)
		return(0);
E 2
	f = open(wtmpf, 1);
E 12
I 12
	if (status)
		return (0);
D 28
	f = open(wtmpf, O_WRONLY|O_APPEND);
E 12
	if (f >= 0) {
D 12
		lseek(f, 0L, 2);
E 12
		SCPYN(wtmp.ut_line, "~");
		SCPYN(wtmp.ut_name, "reboot");
I 11
		SCPYN(wtmp.ut_host, "");
E 11
D 4
		time(&wtmp.ut_time);
E 4
I 4
		if (time0) {
			wtmp.ut_time = time0;
			time0 = 0;
		} else
			time(&wtmp.ut_time);
E 4
		write(f, (char *)&wtmp, sizeof(wtmp));
		close(f);
	}
E 28
I 28
	logwtmp("~", "reboot", "");
E 28
I 2
D 12
	return(1);
E 12
I 12
	return (1);
E 36
I 36

	close(pfd[0]);
	fcntl(pfd[1], F_SETFD, FD_CLOEXEC);
	fcntl(pfd[1], F_SETFL, O_NONBLOCK);

	return pfd[1];
E 36
E 12
E 2
}

I 38
/*
E 54
 * Close out the accounting files for a login session.
I 39
 * NB: should send a message to the session logger to avoid blocking.
E 39
 */
E 38
I 26
D 31
int merge();
E 31
E 26
D 12
setmerge()
{

	signal(SIGHUP, setmerge);
	mergflag = 1;
}

E 12
I 12
D 15
struct	sigvec	mvec = { merge, mask(SIGTERM), 0 };
E 15
I 15
D 36
struct	sigvec	mvec = { merge, sigmask(SIGTERM), 0 };
E 36
I 36
void
clear_session_logs(sp)
	session_t *sp;
{
D 39
	if (fork() == 0 && logout(sp->se_device))
E 39
I 39
D 47
	if (logout(sp->se_device))
E 39
		logwtmp(sp->se_device, "", "");
E 47
I 47
	char *line = sp->se_device + sizeof(_PATH_DEV) - 1;

	if (logout(line))
		logwtmp(line, "", "");
E 47
}

E 36
E 15
/*
D 36
 * Multi-user.  Listen for users leaving, SIGHUP's
 * which indicate ttys has changed, and SIGTERM's which
 * are used to shutdown the system.
E 36
I 36
 * Start a session and allocate a controlling terminal.
 * Only called by children of init after forking.
E 36
 */
E 12
D 36
multiple()
E 36
I 36
void
setctty(name)
	char *name;
E 36
{
I 31
D 36
	extern int errno;
E 31
	register struct tab *p;
	register pid;
I 18
	int omask;
E 36
I 36
	int fd;
E 36
E 18

I 38
	(void) revoke(name);
I 54
	sleep (2);			/* leave DTR low */
E 54
E 38
D 12
loop:
	mergflag = 0;
	signal(SIGHUP, setmerge);
	for(EVER) {
E 12
I 12
D 36
	sigvec(SIGHUP, &mvec, (struct sigvec *)0);
	for (EVER) {
E 12
		pid = wait((int *)0);
D 12
		if(mergflag) {
			merge();
			goto loop;
		}
		if(pid == -1)
E 12
I 12
D 31
		if (pid == -1)
E 31
I 31
/* SHOULD FIX THIS IN THE KERNEL */
		if (pid == -1 && errno != EINTR)
E 31
E 12
			return;
I 18
D 23
		omask = sigblock(SIGHUP);
E 23
I 23
		omask = sigblock(sigmask(SIGHUP));
E 23
E 18
D 12
		for(ALL)
			if(p->pid == pid || p->pid == -1) {
E 12
I 12
D 15
		for (ALL)
E 15
I 15
		for (ALL) {
			/* must restart window system BEFORE emulator */
			if (p->wpid == pid || p->wpid == -1)
				wstart(p);
E 15
			if (p->pid == pid || p->pid == -1) {
I 15
				/* disown the window system */
				if (p->wpid)
					kill(p->wpid, SIGHUP);
E 15
E 12
D 27
				rmut(p);
E 27
I 27
				cleanutmp(p);
E 27
				dfork(p);
			}
I 15
		}
I 18
		sigsetmask(omask);
E 36
I 36
	if ((fd = open(name, O_RDWR)) == -1) {
		stall("can't open %s: %m", name);
		_exit(1);
E 36
E 18
E 15
	}
I 36
	if (login_tty(fd) == -1) {
		stall("can't get %s for controlling terminal: %m", name);
		_exit(1);
	}
E 36
}

I 38
/*
 * Bring the system up single user.
 */
E 38
I 12
D 36
/*
 * Merge current contents of ttys file
 * into in-core table of configured tty lines.
 * Entered as signal handler for SIGHUP.
 */
#define	FOUND	1
#define	CHANGE	2
I 15
#define WCHANGE 4
E 15

I 31
void
E 31
merge()
E 36
I 36
state_func_t
single_user()
E 36
{
D 36
	register struct tab *p;
I 13
	register struct ttyent *t;
I 18
	register struct tab *p1;
E 36
I 36
	pid_t pid, wpid;
	int status;
	sigset_t mask;
	char *shell = _PATH_BSHELL;
	char *argv[2];
#ifdef SECURE
	struct ttyent *typ;
	struct passwd *pp;
	static const char banner[] =
		"Enter root password, or ^D to go multi-user\n";
D 54
	char *password;
E 54
I 54
	char *clear, *password;
E 54
#endif
E 36
E 18
E 13

I 50
	/*
	 * If the kernel is in secure mode, downgrade it to insecure mode.
	 */
	if (getsecuritylevel() > 0)
		setsecuritylevel(0);

E 50
D 13
	fi = open(ifile, 0);
	if (fi < 0)
		return;
E 13
D 36
	for (ALL)
		p->xflag = 0;
D 13
	while (rline()) {
E 13
I 13
	setttyent();
	while (t = getttyent()) {
		if ((t->ty_status & TTY_ON) == 0)
			continue;
D 15
		strcpy(tty, dev);
		strcat(tty, t->ty_name);
		if (access(tty, R_OK|W_OK) < 0)
			continue;
E 15
E 13
		for (ALL) {
D 13
			if (SCMPN(p->line, line.line))
E 13
I 13
			if (SCMPN(p->line, t->ty_name))
E 13
				continue;
			p->xflag |= FOUND;
D 13
			if (line.comn != p->comn) {
E 13
I 13
			if (SCMPN(p->comn, t->ty_getty)) {
E 13
				p->xflag |= CHANGE;
D 13
				p->comn = line.comn;
E 13
I 13
				SCPYN(p->comn, t->ty_getty);
E 36
I 36
	if ((pid = fork()) == 0) {
		/*
		 * Start the single user session.
		 */
		setctty(_PATH_CONSOLE);

I 49
#ifdef KTRACEHACK
		{
			static int tracing = 0;
			int foo, pid;

			if (tracing) goto skip;
			foo = open("/traceinit", O_RDONLY, 0);
			if (foo != -1) {
				close(foo);
				if ((pid = fork()) == 0) {
					execl("/sbin/mount", "mount", "-uw",
						 "/", 0);
					_exit(-1);
				}
				waitpid(pid, 0, 0);
				if (fork() == 0) {
					execl("/ktrace", "ktrace", "-aip",
						 "1", 0);
					_exit(-1);
				}
				waitpid(pid, 0, 0);
				tracing = 1;
			}
			skip: ;
		}
#endif /* KTRACEHACK */
				
E 49
I 48
D 50
#ifdef DEBUGSHELL
		{
			char altshell[128], *cp = altshell;
			int num;

#define	SHREQUEST \
	"Enter pathname of shell or RETURN for sh: "
			(void)write(STDERR_FILENO,
			    SHREQUEST, sizeof(SHREQUEST) - 1);
			while ((num = read(STDIN_FILENO, cp, 1)) != -1 &&
			    num != 0 && *cp != '\n' && cp < &altshell[127])
					cp++;
			*cp = '\0';
			if (altshell[0] != '\0')
				shell = altshell;
		}
#endif /* DEBUGSHELL */

E 50
E 48
#ifdef SECURE
		/*
		 * Check the root password.
		 * We don't care if the console is 'on' by default;
		 * it's the only tty that can be 'off' and 'secure'.
		 */
		typ = getttynam("console");
		pp = getpwnam("root");
		if (typ && (typ->ty_status & TTY_SECURE) == 0 && pp) {
			write(2, banner, sizeof banner - 1);
			for (;;) {
D 54
				password = getpass("Password:");
				if (password == 0 || *password == '\0')
E 54
I 54
				clear = getpass("Password:");
				if (clear == 0 || *clear == '\0')
E 54
					_exit(0);
I 46
D 54
				password = crypt(password, pp->pw_passwd);
E 54
I 54
				password = crypt(clear, pp->pw_passwd);
D 65
				bzero(clear, _PASSWORD_LEN);
E 65
I 65
				memset(clear, 0, _PASSWORD_LEN);
E 65
E 54
E 46
				if (strcmp(password, pp->pw_passwd) == 0)
					break;
I 50
				warning("single-user login failed\n");
E 50
E 36
E 13
			}
I 15
D 23
			if (SCMPN(p->wcmd, t->ty_window)) {
E 23
I 23
D 36
			if (SCMPN(p->wcmd, t->ty_window ? t->ty_window : "")) {
E 23
				p->xflag |= WCHANGE|CHANGE;
				SCPYN(p->wcmd, t->ty_window);
			}
E 15
			goto contin1;
E 36
		}
I 36
D 48
#if 0
E 48
I 48
D 50
#ifdef notdef
E 48
		/*
		 * Make the single-user shell be root's standard shell?
		 */
		if (pp && pp->pw_shell)
			shell = pp->pw_shell;
#endif
E 50
		endttyent();
		endpwent();
D 50
#endif
E 50
I 50
#endif /* SECURE */
E 50
E 36
I 15

I 50
#ifdef DEBUGSHELL
		{
			char altshell[128], *cp = altshell;
			int num;

#define	SHREQUEST \
	"Enter pathname of shell or RETURN for sh: "
			(void)write(STDERR_FILENO,
			    SHREQUEST, sizeof(SHREQUEST) - 1);
			while ((num = read(STDIN_FILENO, cp, 1)) != -1 &&
			    num != 0 && *cp != '\n' && cp < &altshell[127])
					cp++;
			*cp = '\0';
			if (altshell[0] != '\0')
				shell = altshell;
		}
#endif /* DEBUGSHELL */

E 50
E 15
D 18
		for (ALL) {
			if (p->line[0] != 0)
				continue;
D 13
			SCPYN(p->line, line.line);
E 13
I 13
			SCPYN(p->line, t->ty_name);
E 13
			p->xflag |= FOUND|CHANGE;
D 13
			p->comn = line.comn;
E 13
I 13
			SCPYN(p->comn, t->ty_getty);
I 15
			if (strcmp(t->ty_window, "") != 0) {
				p->xflag |= WCHANGE;
				SCPYN(p->wcmd, t->ty_window);
			}
E 18
I 18
		/*
D 36
		 * Make space for a new one
E 36
I 36
		 * Unblock signals.
		 * We catch all the interesting ones,
		 * and those are reset to SIG_DFL on exec.
E 36
		 */
D 36
		p1 = (struct tab *)calloc(1, sizeof(*p1));
		if (!p1) {
			syslog(LOG_ERR, "no space for '%s' !?!", t->ty_name);
E 18
E 15
E 13
			goto contin1;
		}
E 36
I 36
		sigemptyset(&mask);
		sigprocmask(SIG_SETMASK, &mask, (sigset_t *) 0);

E 36
I 18
		/*
D 36
		 * Put new terminal at the end of the linked list.
E 36
I 36
		 * Fire off a shell.
		 * If the default one doesn't work, try the Bourne shell.
E 36
		 */
D 36
		if (itab) {
			for (p = itab; p->next ; p = p->next)
				;
			p->next = p1;
		} else
			itab = p1;
E 36
I 36
		argv[0] = "-sh";
		argv[1] = 0;
		execv(shell, argv);
		emergency("can't exec %s for single user: %m", shell);
		execv(_PATH_BSHELL, argv);
		emergency("can't exec %s for single user: %m", _PATH_BSHELL);
		sleep(STALL_TIMEOUT);
		_exit(1);
	}
E 36

D 36
		p = p1;
		SCPYN(p->line, t->ty_name);
		p->xflag |= FOUND|CHANGE;
		SCPYN(p->comn, t->ty_getty);
D 23
		if (strcmp(t->ty_window, "") != 0) {
E 23
I 23
		if (t->ty_window && strcmp(t->ty_window, "") != 0) {
E 23
			p->xflag |= WCHANGE;
			SCPYN(p->wcmd, t->ty_window);
E 36
I 36
	if (pid == -1) {
		/*
		 * We are seriously hosed.  Do our best.
		 */
		emergency("can't fork single-user shell, trying again");
		while (waitpid(-1, (int *) 0, WNOHANG) > 0)
D 43
			;
E 43
I 43
			continue;
E 43
		return (state_func_t) single_user;
	}

I 41
	requested_transition = 0;
E 41
D 38
	while ((wpid = waitpid(pid, &status, WUNTRACED)) != pid ||
	       WIFSTOPPED(status)) {
		if (wpid == -1 && errno != EINTR) {
E 38
I 38
	do {
		if ((wpid = waitpid(-1, &status, WUNTRACED)) != -1)
			collect_child(wpid);
		if (wpid == -1) {
			if (errno == EINTR)
				continue;
E 38
			warning("wait for single-user shell failed: %m; restarting");
			return (state_func_t) single_user;
E 36
		}
E 18
D 36
	contin1:
		;
E 36
I 36
		if (wpid == pid && WIFSTOPPED(status)) {
			warning("init: shell stopped, restarting\n");
			kill(pid, SIGCONT);
I 38
			wpid = -1;
E 38
		}
E 36
D 38
	}
E 38
I 38
D 41
	} while (wpid != pid);
E 41
I 41
	} while (wpid != pid && !requested_transition);
E 41
E 38
D 13
	close(fi);
E 13
I 13
D 36
	endttyent();
I 18
	p1 = (struct tab *)0;
E 18
E 13
	for (ALL) {
		if ((p->xflag&FOUND) == 0) {
			term(p);
D 18
			p->line[0] = 0;
E 18
I 15
			wterm(p);
I 18
			if (p1)
				p1->next = p->next;
			else
				itab = p->next;
			free(p);
			p = p1 ? p1 : itab;
		} else {
			/* window system should be started first */
			if (p->xflag&WCHANGE) {
				wterm(p);
				wstart(p);
			}
			if (p->xflag&CHANGE) {
				term(p);
				dfork(p);
			}
E 36
I 36

I 41
	if (requested_transition)
		return (state_func_t) requested_transition;

E 41
	if (!WIFEXITED(status)) {
D 40
		warning("single user shell terminated abnormally, restarting");
		return (state_func_t) single_user;
E 40
I 40
		if (WTERMSIG(status) == SIGKILL) { 
			/* 
			 *  reboot(8) killed shell? 
			 */
			warning("single user shell terminated.");
			sleep(STALL_TIMEOUT);
			_exit(0);
		} else {	
			warning("single user shell terminated, restarting");
			return (state_func_t) single_user;
		}
E 40
	}

	runcom_mode = FASTBOOT;
	return (state_func_t) runcom;
}

I 38
/*
 * Run the system startup script.
 */
E 38
state_func_t
runcom()
{
	pid_t pid, wpid;
	int status;
	char *argv[4];
D 38
	sigset_t mask;
E 38
I 38
	struct sigaction sa;
E 38

	if ((pid = fork()) == 0) {
I 38
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sa.sa_handler = SIG_IGN;
		(void) sigaction(SIGTSTP, &sa, (struct sigaction *)0);
		(void) sigaction(SIGHUP, &sa, (struct sigaction *)0);

E 38
		setctty(_PATH_CONSOLE);

		argv[0] = "sh";
		argv[1] = _PATH_RUNCOM;
		argv[2] = runcom_mode == AUTOBOOT ? "autoboot" : 0;
		argv[3] = 0;

D 38
		sigemptyset(&mask);
		sigprocmask(SIG_SETMASK, &mask, (sigset_t *) 0);
E 38
I 38
		sigprocmask(SIG_SETMASK, &sa.sa_mask, (sigset_t *) 0);
E 38

		execv(_PATH_BSHELL, argv);
		stall("can't exec %s for %s: %m", _PATH_BSHELL, _PATH_RUNCOM);
		_exit(1);	/* force single user mode */
	}

	if (pid == -1) {
		emergency("can't fork for %s on %s: %m",
			_PATH_BSHELL, _PATH_RUNCOM);
I 38
		while (waitpid(-1, (int *) 0, WNOHANG) > 0)
D 43
			;
E 43
I 43
			continue;
E 43
E 38
		sleep(STALL_TIMEOUT);
		return (state_func_t) single_user;
	}

	/*
D 38
	 * Copied from single_user().  Is this too paranoid?
E 38
I 38
	 * Copied from single_user().  This is a bit paranoid.
E 38
	 */
D 38
	while ((wpid = waitpid(pid, &status, WUNTRACED)) != pid ||
	       WIFSTOPPED(status)) {
		if (wpid == -1 && errno != EINTR) {
E 38
I 38
	do {
		if ((wpid = waitpid(-1, &status, WUNTRACED)) != -1)
			collect_child(wpid);
		if (wpid == -1) {
			if (errno == EINTR)
				continue;
E 38
			warning("wait for %s on %s failed: %m; going to single user mode",
				_PATH_BSHELL, _PATH_RUNCOM);
			return (state_func_t) single_user;
E 36
E 18
E 15
		}
I 15
D 18
		/* window system should be started first */
		if (p->xflag&WCHANGE) {
			wterm(p);
			wstart(p);
		}
E 15
		if (p->xflag&CHANGE) {
			term(p);
			dfork(p);
		}
E 18
I 18
D 36
		p1 = p;
E 36
I 36
		if (wpid == pid && WIFSTOPPED(status)) {
			warning("init: %s on %s stopped, restarting\n",
				_PATH_BSHELL, _PATH_RUNCOM);
			kill(pid, SIGCONT);
I 38
			wpid = -1;
E 38
		}
E 36
E 18
D 38
	}
E 38
I 38
	} while (wpid != pid);
E 38
I 36

I 54
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGTERM &&
	    requested_transition == catatonia) {
		/* /etc/rc executed /sbin/reboot; wait for the end quietly */
		sigset_t s;

		sigfillset(&s);
		for (;;)
			sigsuspend(&s);
	}

E 54
	if (!WIFEXITED(status)) {
		warning("%s on %s terminated abnormally, going to single user mode",
			_PATH_BSHELL, _PATH_RUNCOM);
		return (state_func_t) single_user;
	}

	if (WEXITSTATUS(status))
		return (state_func_t) single_user;

	runcom_mode = AUTOBOOT;		/* the default */
I 38
D 39
	logwtmp("~", "reboot", "");	/* XXX */
E 39
I 39
	/* NB: should send a message to the session logger to avoid blocking. */
	logwtmp("~", "reboot", "");
E 39
E 38
	return (state_func_t) read_ttys;
E 36
}

E 12
D 36
term(p)
D 12
register struct tab *p;
E 12
I 12
	register struct tab *p;
E 36
I 36
/*
D 38
 * The db library seems awfully heavyweight for this task.
 * This code may get replaced later.
 * We could pass in the size here; is it worth it?
E 38
I 38
 * Open the session database.
 *
 * NB: We could pass in the size here; is it necessary?
E 38
 */
D 38
void
E 38
I 38
int
E 38
start_session_db()
E 36
E 12
{
I 36
D 38
	if (session_db)
		(*session_db->close)(session_db);
	session_db = hash_open((char *) 0, 0, 0, (HASHINFO *) 0);
E 38
I 38
	if (session_db && (*session_db->close)(session_db))
		emergency("session database close: %s", strerror(errno));
D 42
	if ((session_db = hash_open(NULL, O_RDWR, 0, NULL)) == 0) {
E 42
I 42
	if ((session_db = dbopen(NULL, O_RDWR, 0, DB_HASH, NULL)) == 0) {
E 42
		emergency("session database open: %s", strerror(errno));
		return (1);
	}
	return (0);
		
E 38
}
E 36

I 38
/*
 * Add a new login session.
 */
E 38
D 12
	if(p->pid != 0) {
E 12
I 12
D 36
	if (p->pid != 0) {
E 12
D 27
		rmut(p);
E 27
I 27
		cleanutmp(p);
E 27
		kill(p->pid, SIGKILL);
E 36
I 36
void
add_session(sp)
	session_t *sp;
{
	DBT key;
	DBT data;

	key.data = &sp->se_process;
	key.size = sizeof sp->se_process;
	data.data = &sp;
	data.size = sizeof sp;

D 38
	(*session_db->put)(session_db, &key, &data, R_PUT);
E 38
I 38
D 42
	if ((*session_db->put)(session_db, &key, &data, R_PUT))
E 42
I 42
	if ((*session_db->put)(session_db, &key, &data, 0))
E 42
		emergency("insert %d: %s", sp->se_process, strerror(errno));
E 38
}

I 38
/*
 * Delete an old login session.
 */
E 38
void
del_session(sp)
	session_t *sp;
{
	DBT key;

	key.data = &sp->se_process;
	key.size = sizeof sp->se_process;

D 38
	(*session_db->del)(session_db, &key, 0);
E 38
I 38
	if ((*session_db->del)(session_db, &key, 0))
		emergency("delete %d: %s", sp->se_process, strerror(errno));
E 38
}

I 38
/*
 * Look up a login session by pid.
 */
E 38
session_t *
#ifdef __STDC__
find_session(pid_t pid)
#else
find_session(pid)
	pid_t pid;
#endif
{
	DBT key;
	DBT data;
I 43
	session_t *ret;
E 43

	key.data = &pid;
	key.size = sizeof pid;
	if ((*session_db->get)(session_db, &key, &data, 0) != 0)
		return 0;
D 43
	return *(session_t **)data.data;
E 43
I 43
D 65
	bcopy(data.data, (char *)&ret, sizeof(ret));
E 65
I 65
	memmove(&ret, data.data, sizeof(ret));
E 65
	return ret;
E 43
}

I 38
/*
 * Construct an argument vector from a command line.
 */
E 38
char **
construct_argv(command)
	char *command;
{
	register int argc = 0;
	register char **argv = (char **) malloc(((strlen(command) + 1) / 2 + 1)
						* sizeof (char *));
	static const char separators[] = " \t";

	if ((argv[argc++] = strtok(command, separators)) == 0)
		return 0;
	while (argv[argc++] = strtok((char *) 0, separators))
D 43
		;
E 43
I 43
		continue;
E 43
	return argv;
}

I 38
/*
 * Deallocate a session descriptor.
 */
E 38
void
free_session(sp)
	register session_t *sp;
{
	free(sp->se_device);
D 60
	free(sp->se_getty);
	free(sp->se_getty_argv);
E 60
I 60
	if (sp->se_getty) {
		free(sp->se_getty);
		free(sp->se_getty_argv);
	}
E 60
	if (sp->se_window) {
		free(sp->se_window);
		free(sp->se_window_argv);
E 36
	}
D 36
	p->pid = 0;
I 15
	/* send SIGHUP to get rid of connections */
	if (p->wpid > 0)
		kill(p->wpid, SIGHUP);
E 36
I 36
	free(sp);
E 36
E 15
}
D 23

D 13
rline()
{
	register c, i;

loop:
	c = get();
D 12
	if(c < 0)
E 12
I 12
	if (c < 0)
E 12
		return(0);
D 12
	if(c == 0)
E 12
I 12
	if (c == 0)
E 12
		goto loop;
	line.flag = c;
	c = get();
D 12
	if(c <= 0)
E 12
I 12
	if (c <= 0)
E 12
		goto loop;
	line.comn = c;
	SCPYN(line.line, "");
D 12
	for (i=0; i<LINSIZ; i++) {
E 12
I 12
	for (i = 0; i < LINSIZ; i++) {
E 12
		c = get();
D 12
		if(c <= 0)
E 12
I 12
		if (c <= 0)
E 12
			break;
		line.line[i] = c;
	}
D 12
	while(c > 0)
E 12
I 12
	while (c > 0)
E 12
		c = get();
D 12
	if(line.line[0] == 0)
E 12
I 12
	if (line.line[0] == 0)
E 12
		goto loop;
D 12
	if(line.flag == '0')
E 12
I 12
	if (line.flag == '0')
E 12
		goto loop;
	strcpy(tty, dev);
	strncat(tty, line.line, LINSIZ);
D 12
	if(access(tty, 06) < 0)
E 12
I 12
	if (access(tty, 06) < 0)
E 12
		goto loop;
D 12
	return(1);
E 12
I 12
	return (1);
E 12
}

get()
{
	char b;

D 12
	if(read(fi, &b, 1) != 1)
		return(-1);
	if(b == '\n')
		return(0);
	return(b);
E 12
I 12
	if (read(fi, &b, 1) != 1)
		return (-1);
	if (b == '\n')
		return (0);
	return (b);
E 12
}

E 13
D 12
#define	FOUND	1
#define	CHANGE	2

merge()
{
	register struct tab *p;

	fi = open(ifile, 0);
	if(fi < 0)
		return;
	for(ALL)
		p->xflag = 0;
	while(rline()) {
		for(ALL) {
			if (SCMPN(p->line, line.line))
				continue;
			p->xflag |= FOUND;
			if(line.comn != p->comn) {
				p->xflag |= CHANGE;
				p->comn = line.comn;
			}
			goto contin1;
		}
		for(ALL) {
			if(p->line[0] != 0)
				continue;
			SCPYN(p->line, line.line);
			p->xflag |= FOUND|CHANGE;
			p->comn = line.comn;
			goto contin1;
		}
	contin1:
		;
	}
	close(fi);
	for(ALL) {
		if((p->xflag&FOUND) == 0) {
			term(p);
			p->line[0] = 0;
		}
		if((p->xflag&CHANGE) != 0) {
			term(p);
			dfork(p);
		}
	}
}

E 12
I 7
#include <sys/ioctl.h>
E 23

I 38
/*
 * Allocate a new session descriptor.
 */
E 38
E 7
D 36
dfork(p)
D 12
struct tab *p;
E 12
I 12
	struct tab *p;
E 36
I 36
session_t *
new_session(sprev, session_index, typ)
	session_t *sprev;
	int session_index;
	register struct ttyent *typ;
E 36
E 12
{
D 36
	register pid;
I 6
	time_t t;
	int dowait = 0;
E 36
I 36
	register session_t *sp;
E 36
I 9
D 15
	extern char *sys_errlist[];
E 15
E 9
E 6

I 6
D 36
	time(&t);
	p->gettycnt++;
	if ((t - p->gettytime) >= 60) {
		p->gettytime = t;
		p->gettycnt = 1;
D 15
	} else {
		if (p->gettycnt >= 5) {
			dowait = 1;
			p->gettytime = t;
			p->gettycnt = 1;
		}
E 15
I 15
	} else if (p->gettycnt >= 5) {
		dowait = 1;
		p->gettytime = t;
		p->gettycnt = 1;
E 36
I 36
	if ((typ->ty_status & TTY_ON) == 0 ||
	    typ->ty_name == 0 ||
	    typ->ty_getty == 0)
		return 0;

	sp = (session_t *) malloc(sizeof (session_t));
I 60
D 65
	bzero(sp, sizeof *sp);
E 65
I 65
	memset(sp, 0, sizeof *sp);
E 65
E 60

	sp->se_index = session_index;
D 60
	sp->se_process = 0;
	sp->se_started = 0;
	sp->se_flags = 0;
	sp->se_window = 0;
E 60

D 47
	sp->se_device = malloc(6 + strlen(typ->ty_name));
	memcpy(sp->se_device, _PATH_DEV, 5);
	strcpy(sp->se_device + 5, typ->ty_name);
E 47
I 47
	sp->se_device = malloc(sizeof(_PATH_DEV) + strlen(typ->ty_name));
	(void) sprintf(sp->se_device, "%s%s", _PATH_DEV, typ->ty_name);
E 47

D 55
	sp->se_getty = strdup(typ->ty_getty);
E 55
I 55
D 57
	sp->se_getty = malloc(strlen(typ->ty_getty) + strlen(typ->ty_name) + 2);
	(void) sprintf(sp->se_getty, "%s %s", typ->ty_getty, typ->ty_name);
E 57
I 57
D 59
	sp->se_getty = strdup(typ->ty_getty);
E 59
I 59
D 60
	sp->se_getty = malloc(strlen(typ->ty_getty) + strlen(typ->ty_name) + 2);
	(void) sprintf(sp->se_getty, "%s %s", typ->ty_getty, typ->ty_name);
E 59
E 57
E 55
	sp->se_getty_argv = construct_argv(sp->se_getty);
	if (sp->se_getty_argv == 0) {
		warning("can't parse getty for port %s",
			sp->se_device);
E 60
I 60
	if (setupargv(sp, typ) == 0) {
E 60
		free_session(sp);
D 60
		return 0;
E 60
I 60
		return (0);
E 60
E 36
E 15
	}
E 6
D 36
	pid = fork();
D 12
	if(pid == 0) {
E 12
I 12
	if (pid == 0) {
E 12
I 7
D 15
		int oerrno, f;
		extern int errno;

E 15
		signal(SIGTERM, SIG_DFL);
		signal(SIGHUP, SIG_IGN);
I 17
		sigsetmask(0);	/* since can be called from masked code */
E 17
I 9
D 15
		strcpy(tty, dev);
		strncat(tty, p->line, LINSIZ);
E 15
E 9
E 7
I 6
		if (dowait) {
D 7
			int f = open("/dev/console", 1);
E 7
I 7
D 12
			f = open("/dev/console", 1);
E 12
I 12
D 15
			f = open("/dev/console", O_WRONLY);
E 12
E 7
			write(f, "init: ", 6);
			write(f, tty, strlen(tty));
			write(f, ": getty failing, sleeping\n\r", 27);
			close(f);
E 15
I 15
			syslog(LOG_ERR, "'%s %s' failing, sleeping", p->comn, p->line);
			closelog();
E 15
			sleep(30);
E 36
I 36
D 60
	if (typ->ty_window) {
		sp->se_window = strdup(typ->ty_window);
		sp->se_window_argv = construct_argv(sp->se_window);
		if (sp->se_window_argv == 0) {
			warning("can't parse window for port %s",
				sp->se_device);
			free_session(sp);
			return 0;
E 36
I 7
D 12
			if ((f = open("/dev/tty", 2)) >= 0) {
E 12
I 12
D 15
			if ((f = open("/dev/tty", O_RDWR)) >= 0) {
E 12
				ioctl(f, TIOCNOTTY, 0);
				close(f);
			}
E 15
E 7
		}
I 31
D 36
		if (setsid() < 0)
			syslog(LOG_ERR, "setsid failed(dfork) %m");
E 31
E 6
D 7
		signal(SIGTERM, SIG_DFL);
		signal(SIGHUP, SIG_IGN);
E 7
D 9
		strcpy(tty, dev);
		strncat(tty, p->line, LINSIZ);
E 9
D 15
		chown(tty, 0, 0);
		chmod(tty, 0622);
I 14
		/*
		 * Give port selectors an opportunity
		 * to see DTR transition.
		 */
		sleep(1);
E 14
D 5
		open(tty, 2);
E 5
I 5
D 12
		if (open(tty, 2) < 0) {
E 12
I 12
		if (open(tty, O_RDWR) < 0) {
E 12
			int repcnt = 0;
			do {
I 7
				oerrno = errno;
E 7
				if (repcnt % 10 == 0) {
D 7
					int f = open("/dev/console", 1);
E 7
I 7
D 12
					f = open("/dev/console", 1);
E 12
I 12
					f = open("/dev/console", O_WRONLY);
E 12
E 7
					write(f, "init: ", 6);
D 7
					write(f, tty, strlen(tty));
					write(f, ": cannot open\n\r", 15);
E 7
I 7
D 9
					errno = oerrno, perror(tty);
E 9
I 9
					write(f, tty, strlen(tty));
					write(f, ": ", 2);
					write(f, sys_errlist[oerrno],
						strlen(sys_errlist[oerrno]));
					write(f, "\n", 1);
E 9
E 7
					close(f);
I 7
					if ((f = open("/dev/tty", 2)) >= 0) {
						ioctl(f, TIOCNOTTY, 0);
						close(f);
					}
E 7
				}
				repcnt++;
				sleep(60);
D 12
			} while (open(tty, 2) < 0);
E 12
I 12
			} while (open(tty, O_RDWR) < 0);
E 12
			exit(0);	/* have wrong control tty, start over */
		}
E 5
		vhangup();
		signal(SIGHUP, SIG_DFL);
D 12
		open(tty, 2);
E 12
I 12
		(void) open(tty, O_RDWR);
E 12
		close(0);
		dup(1);
		dup(0);
D 13
		tty[0] = p->comn;
		tty[1] = 0;
E 13
I 13
		strncpy(tty, p->comn, sizeof(p->comn));
		tty[sizeof(p->comn)] = 0;
E 13
		execl(getty, minus, tty, (char *)0);
E 15
I 15
		execit(p->comn, p->line);
E 15
		exit(0);
E 36
	}
E 60
D 36
	p->pid = pid;
E 36
I 36

	sp->se_next = 0;
	if (sprev == 0) {
		sessions = sp;
		sp->se_prev = 0;
	} else {
		sprev->se_next = sp;
		sp->se_prev = sprev;
	}

	return sp;
E 36
}

I 38
/*
I 60
 * Calculate getty and if useful window argv vectors.
 */
int
setupargv(sp, typ)
	session_t *sp;
	struct ttyent *typ;
{

	if (sp->se_getty) {
		free(sp->se_getty);
		free(sp->se_getty_argv);
	}
	sp->se_getty = malloc(strlen(typ->ty_getty) + strlen(typ->ty_name) + 2);
	(void) sprintf(sp->se_getty, "%s %s", typ->ty_getty, typ->ty_name);
	sp->se_getty_argv = construct_argv(sp->se_getty);
	if (sp->se_getty_argv == 0) {
		warning("can't parse getty for port %s", sp->se_device);
		free(sp->se_getty);
		sp->se_getty = 0;
		return (0);
	}
	if (typ->ty_window) {
		if (sp->se_window)
			free(sp->se_window);
		sp->se_window = strdup(typ->ty_window);
		sp->se_window_argv = construct_argv(sp->se_window);
		if (sp->se_window_argv == 0) {
			warning("can't parse window for port %s",
				sp->se_device);
			free(sp->se_window);
			sp->se_window = 0;
			return (0);
		}
	}
	return (1);
}

/*
E 60
 * Walk the list of ttys and create sessions for each active line.
 */
E 38
I 12
D 27
/*
 * Remove utmp entry.
 */
E 12
rmut(p)
E 27
I 27
D 36
cleanutmp(p)
E 27
D 12
register struct tab *p;
E 12
I 12
	register struct tab *p;
E 36
I 36
state_func_t
read_ttys()
E 36
E 12
{
D 27
	register f;
I 5
	int found = 0;
I 18
	static unsigned utmpsize;
	static struct utmp *utmp;
	register struct utmp *u;
	int nutmp;
	struct stat statbf;
E 18
E 5

D 12
	f = open(utmp, 2);
	if(f >= 0) {
		while(read(f, (char *)&wtmp, sizeof(wtmp)) == sizeof(wtmp)) {
E 12
I 12
D 18
	f = open(utmp, O_RDWR);
E 18
I 18
	f = open(utmpf, O_RDWR);
E 18
	if (f >= 0) {
D 18
		while (read(f, (char *)&wtmp, sizeof(wtmp)) == sizeof(wtmp)) {
E 12
D 5
			if (SCMPN(wtmp.ut_line, p->line))
E 5
I 5
			if (SCMPN(wtmp.ut_line, p->line) || wtmp.ut_name[0]==0)
E 5
				continue;
			lseek(f, -(long)sizeof(wtmp), 1);
			SCPYN(wtmp.ut_name, "");
I 11
			SCPYN(wtmp.ut_host, "");
E 11
			time(&wtmp.ut_time);
			write(f, (char *)&wtmp, sizeof(wtmp));
I 5
			found++;
E 18
I 18
		fstat(f, &statbf);
		if (utmpsize < statbf.st_size) {
			utmpsize = statbf.st_size + 10 * sizeof(struct utmp);
			if (utmp)
				utmp = (struct utmp *)realloc(utmp, utmpsize);
			else
				utmp = (struct utmp *)malloc(utmpsize);
			if (!utmp)
				syslog(LOG_ERR, "utmp malloc failed");
		}
		if (statbf.st_size && utmp) {
			nutmp = read(f, utmp, statbf.st_size);
			nutmp /= sizeof(struct utmp);
			for (u = utmp ; u < &utmp[nutmp] ; u++) {
D 24
				if (SCMPN(u->ut_line, p->line) ||
				    u->ut_name[0]==0)
E 24
I 24
				if (u->ut_name[0] == 0 ||
				    SCMPN(u->ut_line, p->line))
E 24
					continue;
				lseek(f, ((long)u)-((long)utmp), L_SET);
				SCPYN(u->ut_name, "");
				SCPYN(u->ut_host, "");
				time(&u->ut_time);
				write(f, (char *)u, sizeof(*u));
				found++;
			}
E 18
E 5
		}
		close(f);
	}
D 5
	f = open(wtmpf, 1);
	if (f >= 0) {
		SCPYN(wtmp.ut_line, p->line);
		SCPYN(wtmp.ut_name, "");
		time(&wtmp.ut_time);
		lseek(f, (long)0, 2);
		write(f, (char *)&wtmp, sizeof(wtmp));
		close(f);
E 5
I 5
	if (found) {
D 12
		f = open(wtmpf, 1);
E 12
I 12
		f = open(wtmpf, O_WRONLY|O_APPEND);
E 12
		if (f >= 0) {
			SCPYN(wtmp.ut_line, p->line);
			SCPYN(wtmp.ut_name, "");
I 11
			SCPYN(wtmp.ut_host, "");
E 11
			time(&wtmp.ut_time);
D 12
			lseek(f, (long)0, 2);
E 12
			write(f, (char *)&wtmp, sizeof(wtmp));
			close(f);
		}
E 27
I 27
D 36
	if (logout(p->line)) {
D 31
		logwtmp(p->line);
E 31
I 31
		logwtmp(p->line, "", "");
E 31
E 27
I 14
		/*
		 * After a proper login force reset
		 * of error detection code in dfork.
		 */
		p->gettytime = 0;
I 17
		p->windtime = 0;
E 36
I 36
	int session_index = 0;
	register session_t *sp, *snext;
	register struct ttyent *typ;

	/*
	 * Destroy any previous session state.
	 * There shouldn't be any, but just in case...
	 */
	for (sp = sessions; sp; sp = snext) {
		if (sp->se_process)
			clear_session_logs(sp);
		snext = sp->se_next;
		free_session(sp);
E 36
E 17
E 14
E 5
	}
I 36
	sessions = 0;
D 38
	start_session_db();
E 38
I 38
	if (start_session_db())
		return (state_func_t) single_user;
E 38

	/*
	 * Allocate a session entry for each active port.
	 * Note that sp starts at 0.
	 */
	while (typ = getttyent())
		if (snext = new_session(sp, ++session_index, typ))
			sp = snext;

	endttyent();

D 54
	logger_enable = 1;
E 54
	return (state_func_t) multi_user;
E 36
}

I 38
/*
 * Start a window system running.
 */
E 38
I 31
void
E 31
D 36
reset()
E 36
I 36
start_window_system(sp)
	session_t *sp;
E 36
{
I 12
D 31

E 31
E 12
D 36
	longjmp(sjbuf, 1);
I 4
}
E 36
I 36
	pid_t pid;
	sigset_t mask;
E 36

I 12
D 36
jmp_buf	idlebuf;
E 36
I 36
	if ((pid = fork()) == -1) {
		emergency("can't fork for window system on port %s: %m",
			sp->se_device);
		/* hope that getty fails and we can try again */
		return;
	}
E 36

I 31
D 36
void
E 31
idlehup()
E 36
I 36
	if (pid)
		return;

	sigemptyset(&mask);
	sigprocmask(SIG_SETMASK, &mask, (sigset_t *) 0);

I 38
	if (setsid() < 0)
		emergency("setsid failed (window) %m");

E 38
	execv(sp->se_window_argv[0], sp->se_window_argv);
	stall("can't exec window system '%s' for port %s: %m",
		sp->se_window_argv[0], sp->se_device);
	_exit(1);
}

I 38
/*
 * Start a login session running.
 */
E 38
pid_t
start_getty(sp)
	session_t *sp;
E 36
{
D 31

E 31
D 36
	longjmp(idlebuf, 1);
E 36
I 36
	pid_t pid;
	sigset_t mask;
	time_t current_time = time((time_t *) 0);

	/*
	 * fork(), not vfork() -- we can't afford to block.
	 */
	if ((pid = fork()) == -1) {
		emergency("can't fork for getty on port %s: %m", sp->se_device);
		return -1;
	}

	if (pid)
		return pid;

	if (current_time > sp->se_started &&
	    current_time - sp->se_started < GETTY_SPACING) {
		warning("getty repeating too quickly on port %s, sleeping",
		        sp->se_device);
D 55
		sleep((unsigned) GETTY_SPACING -
E 55
I 55
D 61
		sleep((unsigned) GETTY_SPACING + 1 -
E 55
		      (current_time - sp->se_started));
E 61
I 61
		sleep((unsigned) GETTY_SLEEP);
E 61
	}

	if (sp->se_window) {
		start_window_system(sp);
		sleep(WINDOW_WAIT);
	}

D 59
	setctty(sp->se_device);

E 59
	sigemptyset(&mask);
	sigprocmask(SIG_SETMASK, &mask, (sigset_t *) 0);

	execv(sp->se_getty_argv[0], sp->se_getty_argv);
	stall("can't exec getty '%s' for port %s: %m",
		sp->se_getty_argv[0], sp->se_device);
	_exit(1);
E 36
}

I 38
/*
 * Collect exit status for a child.
 * If an exiting login, start a new login running.
 */
E 38
I 31
void
I 61
#ifdef __STDC__
collect_child(pid_t pid)
#else
E 61
E 31
E 12
D 36
idle()
E 36
I 36
D 38
chld_handler(sig)
	int sig;
E 36
{
E 38
I 38
collect_child(pid)
E 38
D 36
	register struct tab *p;
	register pid;
E 36
I 36
	pid_t pid;
I 61
#endif
E 61
I 38
{
E 38
	register session_t *sp, *sprev, *snext;
E 36

D 12
	signal(SIGTSTP, idle);
E 12
I 12
D 36
	signal(SIGHUP, idlehup);
E 12
D 15
	for (;;) {
E 15
I 15
	for (EVER) {
E 15
D 12
		pid = wait((int *) 0);
		if (mergflag)
E 12
I 12
		if (setjmp(idlebuf))
E 12
			return;
D 12
		if (pid == -1)
			pause();
		else {
			for (ALL)
				if (p->pid == pid) {
					rmut(p);
					p->pid = -1;
				}
E 12
I 12
		pid = wait((int *) 0);
		if (pid == -1) {
			sigpause(0);
E 36
I 36
D 38
	while (pid = waitpid(-1, (int *) 0, WNOHANG)) {
		if (pid == -1)
			if (errno == EINTR)
				continue;
			else
				break;
E 38
I 38
	if (! sessions)
		return;
E 38

D 38
		if (! sessions)
E 36
			continue;
E 38
I 38
	if (! (sp = find_session(pid)))
		return;
E 38
I 36

D 38
		if (! (sp = find_session(pid)))
			continue;
E 38
I 38
	clear_session_logs(sp);
	del_session(sp);
	sp->se_process = 0;
E 38

D 38
		clear_session_logs(sp);
		del_session(sp);
		sp->se_process = 0;
E 38
I 38
	if (sp->se_flags & SE_SHUTDOWN) {
		if (sprev = sp->se_prev)
			sprev->se_next = sp->se_next;
		else
			sessions = sp->se_next;
		if (snext = sp->se_next)
			snext->se_prev = sp->se_prev;
		free_session(sp);
		return;
	}
E 38

D 38
		if (sp->se_flags & SE_SHUTDOWN) {
			if (sprev = sp->se_prev)
				sprev->se_next = sp->se_next;
			else
				sessions = sp->se_next;
			if (snext = sp->se_next)
				snext->se_prev = sp->se_prev;
			free_session(sp);
			continue;
E 36
E 12
		}
I 12
D 15
		for (ALL)
E 15
I 15
D 36
		for (ALL) {
			/* if window system dies, mark it for restart */
			if (p->wpid == pid)
				p->wpid = -1;
E 15
			if (p->pid == pid) {
D 27
				rmut(p);
E 27
I 27
				cleanutmp(p);
E 27
				p->pid = -1;
			}
E 36
I 36

		if ((pid = start_getty(sp)) == -1) {
			/* serious trouble */
			requested_transition = clean_ttys;
			return;
E 36
I 15
		}
I 36

		sp->se_process = pid;
		sp->se_started = time((time_t *) 0);
		add_session(sp);
E 38
I 38
	if ((pid = start_getty(sp)) == -1) {
		/* serious trouble */
		requested_transition = clean_ttys;
		return;
E 38
E 36
E 15
E 12
	}
I 36

D 38
	requested_transition = 0;
E 38
I 38
	sp->se_process = pid;
	sp->se_started = time((time_t *) 0);
	add_session(sp);
E 38
E 36
I 15
}

I 38
/*
 * Catch a signal and request a state transition.
 */
E 38
D 36
wterm(p)
	register struct tab *p;
E 36
I 36
void
transition_handler(sig)
	int sig;
E 36
{
I 41

E 41
D 36
	if (p->wpid != 0) {
		kill(p->wpid, SIGKILL);
E 36
I 36
	switch (sig) {
	case SIGHUP:
		requested_transition = clean_ttys;
		break;
	case SIGTERM:
		requested_transition = death;
		break;
	case SIGTSTP:
		requested_transition = catatonia;
		break;
	default:
		requested_transition = 0;
		break;
E 36
	}
D 36
	p->wpid = 0;
E 36
}

I 38
/*
 * Take the system multiuser.
 */
E 38
D 36
wstart(p)
	register struct tab *p;
E 36
I 36
state_func_t
multi_user()
E 36
{
D 17
	int npid = fork();
E 17
I 17
D 36
	register pid;
	time_t t;
	int dowait = 0;
E 36
I 36
	pid_t pid;
	register session_t *sp;
E 36
E 17

D 17
	if (npid == 0) {
/*
E 17
I 17
D 36
	time(&t);
	p->windcnt++;
	if ((t - p->windtime) >= 60) {
		p->windtime = t;
		p->windcnt = 1;
	} else if (p->windcnt >= 5) {
		dowait = 1;
		p->windtime = t;
		p->windcnt = 1;
	}
E 36
I 36
	requested_transition = 0;
D 54
	logger_enable = 1;
E 54
I 50

	/*
	 * If the administrator has not set the security level to -1
	 * to indicate that the kernel should not run multiuser in secure
	 * mode, and the run script has not set a higher level of security 
	 * than level 1, then put the kernel into secure mode.
	 */
	if (getsecuritylevel() == 0)
		setsecuritylevel(1);
E 50
E 36

D 36
	pid = fork();
E 36
I 36
D 38
	for (sp = sessions; sp; sp = sp->se_next)
		if (! sp->se_process) {
			if ((pid = start_getty(sp)) == -1) {
				/* serious trouble */
				requested_transition = clean_ttys;
				break;
			}
E 36

D 36
	if (pid == 0) {
E 17
		signal(SIGTERM, SIG_DFL);
D 17
		signal(SIGHUP,  SIG_DFL);
		signal(SIGALRM, SIG_DFL);
		signal(SIGTSTP, SIG_IGN);
*/
E 17
I 17
		signal(SIGHUP,  SIG_IGN);
		sigsetmask(0);	/* since can be called from masked code */
		if (dowait) {
			syslog(LOG_ERR, "'%s %s' failing, sleeping", p->wcmd, p->line);
			closelog();
			sleep(30);
E 36
I 36
			sp->se_process = pid;
			sp->se_started = time((time_t *) 0);
			add_session(sp);
E 38
I 38
	for (sp = sessions; sp; sp = sp->se_next) {
		if (sp->se_process)
			continue;
		if ((pid = start_getty(sp)) == -1) {
			/* serious trouble */
			requested_transition = clean_ttys;
			break;
E 38
E 36
		}
I 38
		sp->se_process = pid;
		sp->se_started = time((time_t *) 0);
		add_session(sp);
	}
E 38
I 31
D 36
		if (setsid() < 0)
			syslog(LOG_ERR, "setsid failed (window) %m");
E 31
E 17
		execit(p->wcmd, p->line);
		exit(0);
	}
D 17
	p->wpid = npid;
E 17
I 17
	p->wpid = pid;
E 17
}
E 36

D 17
#define NARGS	20	/* must be at lease 4 */
E 17
I 17
D 36
#define NARGS	20	/* must be at least 4 */
E 17
#define ARGLEN	512	/* total size for all the argument strings */
E 36
I 36
	while (!requested_transition)
D 38
		sigsuspend(&multi_sig_mask);
E 38
I 38
		if ((pid = waitpid(-1, (int *) 0, 0)) != -1)
			collect_child(pid);
E 38
E 36

D 36
execit(s, arg)
	char *s;
	char *arg;	/* last argument on line */
E 36
I 36
	return (state_func_t) requested_transition;
}

/*
 * This is an n-squared algorithm.  We hope it isn't run often...
 */
state_func_t
clean_ttys()
E 36
{
D 36
	char *argv[NARGS], args[ARGLEN], *envp[1];
	register char *sp = s;
	register char *ap = args;
	register char c;
	register int i;
E 36
I 36
	register session_t *sp, *sprev;
	register struct ttyent *typ;
	register int session_index = 0;
I 46
	register int devlen;
E 46
E 36

D 36
	/*
	 * First we have to set up the argument vector.
	 * "prog arg1 arg2" maps to exec("prog", "-", "arg1", "arg2"). 
	 */
	for (i = 1; i < NARGS - 2; i++) {
		argv[i] = ap;
		for (EVER) {
			if ((c = *sp++) == '\0' || ap >= &args[ARGLEN-1]) {
				*ap = '\0';
				goto done;
			}
			if (c == ' ') {
				*ap++ = '\0';
				while (*sp == ' ')
					sp++;
				if (*sp == '\0')
					goto done;
E 36
I 36
	if (! sessions)
		return (state_func_t) multi_user;

I 46
D 47
	devlen = strlen(_PATH_DEV);
E 47
I 47
	devlen = sizeof(_PATH_DEV) - 1;
E 47
E 46
	while (typ = getttyent()) {
		++session_index;

D 54
		for (sp = sessions; sp; sprev = sp, sp = sp->se_next)
E 54
I 54
		for (sprev = 0, sp = sessions; sp; sprev = sp, sp = sp->se_next)
E 54
D 46
			if (strcmp(typ->ty_name, sp->se_device) == 0)
E 46
I 46
D 47
			if (strcmp(typ->ty_name, 
			    (char *)(sp->se_device + devlen)) == 0)
E 47
I 47
			if (strcmp(typ->ty_name, sp->se_device + devlen) == 0)
E 47
E 46
E 36
				break;
I 36

		if (sp) {
			if (sp->se_index != session_index) {
				warning("port %s changed utmp index from %d to %d",
				       sp->se_device, sp->se_index,
				       session_index);
				sp->se_index = session_index;
E 36
			}
D 36
			*ap++ = c;
E 36
I 36
D 59
			if (typ->ty_status & TTY_ON)
				sp->se_flags &= ~SE_SHUTDOWN;
			else {
E 59
I 59
			if ((typ->ty_status & TTY_ON) == 0 ||
			    typ->ty_getty == 0) {
				sp->se_flags |= SE_SHUTDOWN;
				kill(sp->se_process, SIGHUP);
				continue;
			}
			sp->se_flags &= ~SE_SHUTDOWN;
D 60
			free(sp->se_getty);
			sp->se_getty = malloc(strlen(typ->ty_getty) +
			    strlen(typ->ty_name) + 2);
			(void) sprintf(sp->se_getty, "%s %s", typ->ty_getty,
			    typ->ty_name);
			free(sp->se_getty_argv);
			sp->se_getty_argv = construct_argv(sp->se_getty);
			if (sp->se_getty_argv == 0) {
E 60
I 60
			if (setupargv(sp, typ) == 0) {
E 60
				warning("can't parse getty for port %s",
					sp->se_device);
E 59
				sp->se_flags |= SE_SHUTDOWN;
				kill(sp->se_process, SIGHUP);
			}
			continue;
E 36
		}
I 36

		new_session(sprev, session_index, typ);
E 36
	}
D 36
done:
	argv[0] = argv[1];
	argv[1] = "-";
	argv[i+1] = arg;
	argv[i+2] = 0;
	envp[0] = 0;
	execve(argv[0], &argv[1], envp);
	/* report failure of exec */
	syslog(LOG_ERR, "%s: %m", argv[0]);
	closelog();
	sleep(10);	/* prevent failures from eating machine */
E 36
I 36

	endttyent();

	return (state_func_t) multi_user;
}

I 38
/*
 * Block further logins.
 */
E 38
state_func_t
catatonia()
{
	register session_t *sp;

	for (sp = sessions; sp; sp = sp->se_next)
		sp->se_flags |= SE_SHUTDOWN;

	return (state_func_t) multi_user;
}

I 38
/*
 * Note SIGALRM.
 */
E 38
void
alrm_handler(sig)
	int sig;
{
	clang = 1;
}

I 38
/*
 * Bring the system down to single user.
 */
E 38
state_func_t
death()
{
	register session_t *sp;
	register int i;
I 38
	pid_t pid;
E 38
	static const int death_sigs[3] = { SIGHUP, SIGTERM, SIGKILL };

	for (sp = sessions; sp; sp = sp->se_next)
		sp->se_flags |= SE_SHUTDOWN;

I 38
D 39
	logwtmp("~", "shutdown", "");	/* XXX */
E 39
I 39
	/* NB: should send a message to the session logger to avoid blocking. */
	logwtmp("~", "shutdown", "");
E 39
E 38
D 54
	logger_enable = 0;
E 54

	for (i = 0; i < 3; ++i) {
		if (kill(-1, death_sigs[i]) == -1 && errno == ESRCH)
			return (state_func_t) single_user;

		clang = 0;
		alarm(DEATH_WATCH);
		do
D 38
			sigsuspend(&death_mask);
		while (! clang);
E 38
I 38
			if ((pid = waitpid(-1, (int *)0, 0)) != -1)
				collect_child(pid);
		while (clang == 0 && errno != ECHILD);
E 38

D 38
		if (waitpid(-1, (int *) 0, WNOHANG) == -1 && errno == ECHILD)
E 38
I 38
		if (errno == ECHILD)
E 38
			return (state_func_t) single_user;
	}

D 60
	warning("some processes wouldn't die");
E 60
I 60
	warning("some processes would not die; ps axl advised");
E 60

	return (state_func_t) single_user;
E 36
E 15
E 4
}
D 3


E 3
E 1
