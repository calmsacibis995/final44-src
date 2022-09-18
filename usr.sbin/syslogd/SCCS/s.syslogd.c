h24681
s 00071/00084/01034
d D 8.3 94/04/04 03:09:50 pendry 69 68
c prettiness police
e
s 00007/00004/01111
d D 8.2 93/11/16 11:41:49 bostic 68 67
c As with wall, syslogd wasn't strictly terminating the string it passes
c to ttymsg(). I also fixed some new gcc warnings.
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00005/00005/01110
d D 8.1 93/06/06 14:08:34 bostic 67 66
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00002/01114
d D 5.52 93/04/28 10:46:24 bostic 66 65
c daemon(3) now in the C library
e
s 00009/00006/01107
d D 5.51 93/03/08 19:34:09 ralph 65 64
c check for sizeof(buf) so strcpy doesn't trash stack.
e
s 00058/00057/01055
d D 5.50 93/02/25 17:01:28 torek 64 62
c use SUN_LEN macro instead of a local hack; prettiness police
e
s 00058/00057/01055
d R 5.50 93/02/25 16:59:34 torek 63 62
c use SUN_LEN macro instead of a local hack; prettiness police
e
s 00054/00037/01058
d D 5.49 93/02/10 23:14:03 bostic 62 61
c ANSI C, prototypes
e
s 00001/00000/01094
d D 5.48 92/05/16 15:58:20 ralph 61 60
c clear sin struct before using it.
e
s 00001/00001/01093
d D 5.47 91/09/06 19:23:24 ralph 60 59
c fix extern decl to match actual declaration.
e
s 00002/00002/01092
d D 5.46 91/08/01 16:06:32 marc 59 58
c ttymsg now takes timeout parameter
e
s 00005/00003/01089
d D 5.45 91/03/02 17:17:04 bostic 58 57
c ANSI
e
s 00001/00001/01091
d D 5.44 90/09/30 20:40:15 bostic 57 56
c remove -d (debug) from usage statement
e
s 00013/00013/01079
d D 5.43 90/09/30 17:44:50 bostic 56 55
c allow '*' as a priority
e
s 00005/00030/01087
d D 5.42 90/06/29 20:14:33 karels 55 54
c use daemon() call
e
s 00001/00011/01116
d D 5.41 90/06/01 19:01:17 bostic 54 53
c new copyright notice
e
s 00001/00001/01126
d D 5.40 90/05/15 20:03:25 bostic 53 52
c string.h is ANSI C include file
e
s 00001/00004/01126
d D 5.39 90/04/04 16:00:51 bostic 52 51
c undo revision 5.33, log missing utmp files, /etc/rc now creates it
e
s 00002/00002/01128
d D 5.38 89/11/22 20:24:59 mckusick 51 50
c loss of controlling terminal now returns EIO instead of EBADF
e
s 00017/00057/01113
d D 5.37 89/11/13 18:41:11 bostic 50 49
c move shared internal facilities into syslog.h; probably should be read
c out of a configuration file, though.
e
s 00071/00107/01099
d D 5.36 89/10/28 13:52:31 bostic 49 48
c use wall's ttymsg() routine; lots of lint
e
s 00018/00021/01188
d D 5.35 89/10/28 10:50:58 bostic 48 47
c user system defines where available, strerror not sys_errlist, minor stuff
e
s 00005/00001/01204
d D 5.34 89/10/03 15:30:27 bostic 47 46
c POSIX signals
e
s 00004/00001/01201
d D 5.33 89/05/12 18:17:36 bostic 46 45
c don't log utmp errors; may not have mounted file systems yet
e
s 00001/00001/01201
d D 5.32 89/05/11 14:13:38 bostic 45 44
c file reorg, pathnames.h, paths.h
e
s 00016/00016/01186
d D 5.31 89/04/02 15:33:22 bostic 44 43
c add pathnames.h
e
s 00010/00006/01192
d D 5.30 89/02/28 16:30:39 bostic 43 42
c pass tabs through just like spaces; Rick Adams request
e
s 00001/00000/01197
d D 5.29 89/01/24 12:46:44 bostic 42 41
c close UDP ports, too; bug report 4.3BSD-tahoe/etc/10
e
s 00003/00001/01194
d D 5.28 88/12/19 12:08:19 bostic 41 40
c for Mike; clean up bind code
e
s 00004/00004/01191
d D 5.27 88/10/10 22:09:59 bostic 40 39
c use herror 
e
s 00021/00028/01174
d D 5.26 88/09/18 15:59:58 bostic 39 38
c use getopt; translate newlines to spaces; minor lint cleanups
e
s 00001/00001/01201
d D 5.25 88/08/08 10:28:45 bostic 38 37
c supply pointer to the message; bug report 4.3BSD/etc/143
e
s 00010/00005/01192
d D 5.24 88/06/18 14:34:48 bostic 37 36
c install approved copyright notice
e
s 00001/00000/01196
d D 5.23 88/06/06 09:31:53 bostic 36 35
c add LOG_UUCP
e
s 00022/00015/01174
d D 5.22 88/06/03 17:18:24 bostic 35 34
c add Berkeley specific header; trim trailing spaces from configuration
c file entry; set f_file to F_UNUSED if can't open logging file
e
s 00036/00027/01153
d D 5.21 88/05/27 11:42:03 karels 34 32
c fix handling of long messages in last delta;
c use macros in syslog.h for manipulating encoded priorities
e
s 00010/00009/01171
d R 5.21 88/05/27 08:57:49 karels 33 32
c macros in syslog.h for manipulating encoded priorities
e
s 00307/00226/00873
d D 5.20 88/05/24 08:51:52 karels 32 31
c suppress duplicates per output file, other cleanups
e
s 00001/00001/01098
d D 5.19 87/04/06 11:45:31 bostic 31 30
c printf format/argument mismatch
e
s 00004/00000/01095
d D 5.18 87/02/23 18:41:27 mckusick 30 29
c avoid throwing away errors when reinitializing (from guy@sun.com)
e
s 00006/00006/01089
d D 5.17 87/01/29 13:53:25 mckusick 29 28
c strcpyn => strncpy; variable `sun' changed to `sunx' to avoid conflict
e
s 00008/00002/01087
d D 5.16 86/11/23 20:53:02 karels 28 27
c don't print to unwritable ttys (blits); missing untty
e
s 00002/00000/01087
d D 5.15 86/10/27 19:20:18 eric 27 26
c add "news" priority
e
s 00008/00002/01079
d D 5.14 86/10/21 18:02:35 eric 26 25
c Steve Schoch <schoch@orion.arpa>: syslogd can run out of file descriptors
c if you reconfigure it too many times
e
s 00012/00010/01069
d D 5.13 86/05/26 22:02:44 karels 25 24
c separate syslog and mark facilities
e
s 00002/00002/01077
d D 5.12 86/03/11 12:37:38 mckusick 24 23
c log to remote machines correctly (from kjpires@calder.berkeley.edu)
e
s 00006/00080/01073
d D 5.11 86/02/11 19:47:23 karels 23 22
c minor cleanups & remove 4.3alpha compat
e
s 00001/00000/01152
d D 5.10 85/11/17 11:34:01 eric 22 21
c add "lpr" facility
e
s 00057/00019/01095
d D 5.9 85/10/12 23:14:35 eric 21 20
c restore marking; add syslog (mark) facility; allow "none" as a priority
c so that *.debug;mark.none will work
e
s 00002/00001/01112
d D 5.8 85/09/23 18:49:44 eric 20 19
c clean up signal masks -- it seems like this needs more work
e
s 00001/00000/01112
d D 5.7 85/09/19 02:13:23 eric 19 18
c add "daemon" to list of known facility names
e
s 00001/00000/01111
d D 5.6 85/09/18 22:24:07 eric 18 17
c include <sys/param.h> for MAXHOSTNAMELEN
e
s 00003/00003/01108
d D 5.5 85/09/18 22:14:13 eric 17 16
c allocate adequate room for host names
e
s 00003/00001/01108
d D 5.4 85/09/18 11:16:47 eric 16 15
c try to make more resilient to signals
e
s 00001/00001/01108
d D 5.3 85/09/17 22:06:23 eric 15 14
c get definition of f_uname right (?)
e
s 00650/00448/00459
d D 5.2 85/09/17 17:59:57 eric 14 13
c extensive rewrite to add facilities
e
s 00013/00001/00894
d D 5.1 85/05/28 15:38:15 dist 13 12
c Add copyright
e
s 00001/00001/00894
d D 4.12 85/03/12 11:59:30 ralph 12 11
c change default system log priority to KERN_ERR.
e
s 00001/00001/00894
d D 4.11 85/02/20 11:10:01 ralph 11 10
c change wall priority.
e
s 00001/00000/00894
d D 4.10 85/02/05 13:34:16 ralph 10 9
c don't forget to unblock signals before returning in logmsg().
e
s 00081/00083/00813
d D 4.9 85/01/31 15:19:21 ralph 9 8
c lots of bug fixes - console bad fileno, repeated messages, reapchild.
e
s 00257/00153/00639
d D 4.8 84/12/19 09:59:42 ralph 8 7
c changes for more priorities, use priority mask not levels, added
e
s 00036/00020/00756
d D 4.7 84/10/18 11:33:48 ralph 7 6
c fsync file for kernel messages. Fix logmsg - logerror loop.
e
s 00030/00033/00746
d D 4.6 84/09/10 09:41:50 ralph 6 5
c read all files that select indicates are ready.
e
s 00061/00032/00718
d D 4.5 84/08/28 14:15:29 ralph 5 4
c changes for kernel error logging.
e
s 00069/00007/00681
d D 4.4 84/07/23 10:59:51 ralph 4 3
c added code to handle kernel printf's (/dev/klog).
e
s 00081/00058/00607
d D 4.3 84/06/29 11:23:10 ralph 3 2
c fixes to message forwarding. only prepend host at final destination.
e
s 00006/00004/00659
d D 4.2 84/05/07 16:10:34 ralph 2 1
c fix alarm routine for marking files.
e
s 00663/00000/00000
d D 4.1 84/04/24 14:27:53 ralph 1 0
c date and time created 84/04/24 14:27:53 by ralph
e
u
U
t
T
I 13
/*
D 32
 * Copyright (c) 1983 Regents of the University of California.
E 32
I 32
D 35
 * Copyright (c) 1983,1988 Regents of the University of California.
E 32
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 35
I 35
D 67
 * Copyright (c) 1983, 1988 Regents of the University of California.
 * All rights reserved.
E 67
I 67
D 69
 * Copyright (c) 1983, 1988, 1993
E 69
I 69
 * Copyright (c) 1983, 1988, 1993, 1994
E 69
 *	The Regents of the University of California.  All rights reserved.
E 67
 *
D 54
 * Redistribution and use in source and binary forms are permitted
D 37
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 37
I 37
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
E 54
I 54
 * %sccs.include.redist.c%
E 54
E 37
E 35
 */

E 13
I 1
#ifndef lint
I 13
D 67
char copyright[] =
D 32
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 32
I 32
D 35
"%Z% Copyright (c) 1983,1988 Regents of the University of California.\n\
E 35
I 35
"%Z% Copyright (c) 1983, 1988 Regents of the University of California.\n\
E 35
E 32
 All rights reserved.\n";
E 67
I 67
static char copyright[] =
D 69
"%Z% Copyright (c) 1983, 1988, 1993\n\
E 69
I 69
"%Z% Copyright (c) 1983, 1988, 1993, 1994\n\
E 69
	The Regents of the University of California.  All rights reserved.\n";
E 67
D 35
#endif not lint
E 35
I 35
#endif /* not lint */
E 35

#ifndef lint
E 13
D 3
static char SccsId[] = "%W% (Berkeley) %G%";
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
D 13
#endif
E 13
I 13
D 35
#endif not lint
E 35
I 35
#endif /* not lint */
E 35
E 13

I 14
D 23
#define COMPAT		/* include 4.3 Alpha compatibility */

E 23
E 14
/*
 *  syslogd -- log system messages
 *
 * This program implements a system log. It takes a series of lines.
 * Each line may have a priority, signified as "<n>" as
D 8
 * the first three characters of the line.  If this is
 * not present, a default priority (DefPri) is used, which
D 4
 * starts out as LOG_NOTICE.  The default priority can get
E 4
I 4
D 5
 * starts out as LOG_ERR.  The default priority can get
E 5
I 5
 * starts out as LOG_NOTICE.  The default priority can get
E 5
E 4
 * changed using "<*>n".
E 8
I 8
 * the first characters of the line.  If this is
 * not present, a default priority is used.
E 8
 *
 * To kill syslogd, send a signal 15 (terminate).  A signal 1 (hup) will
 * cause it to reread its configuration file.
 *
 * Defined Constants:
 *
D 8
 * DAEMON -- Userid number to setuid to after setup.
E 8
 * MAXLINE -- the maximimum line length that can be handled.
D 8
 * NLOGS -- the maximum number of simultaneous log files.
 * NUSERS -- the maximum number of people that can
 *	be designated as "superusers" on your system.
E 8
I 8
D 32
 * NLOGS   -- the maximum number of simultaneous log files.
E 32
D 14
 * NUSERS  -- the maximum number of people that can
 *		be designated as "superusers" on your system.
E 14
 * DEFUPRI -- the default priority for user messages
 * DEFSPRI -- the default priority for kernel messages
E 8
I 3
 *
 * Author: Eric Allman
D 8
 * Modified to use UNIX domain IPC by Ralph Campbell
E 8
I 8
 * extensive changes by Ralph Campbell
I 27
 * more extensive changes by Eric Allman (again)
E 27
E 8
E 3
 */

D 8
#define DAEMON		1	/* Daemon user-id */
#define	NLOGS		10	/* max number of log files */
#define	NSUSERS		10	/* max number of special users */
#define	MAXLINE		1024	/* maximum line length */
E 8
I 8
D 14
#define	NLOGS		10		/* max number of log files */
#define	NSUSERS		10		/* max number of special users */
E 14
I 14
D 32
#define	NLOGS		20		/* max number of log files */
E 32
E 14
#define	MAXLINE		1024		/* maximum line length */
I 32
D 34
#define	MAXSVLINE	100		/* maximum saved line length */
E 34
I 34
#define	MAXSVLINE	120		/* maximum saved line length */
E 34
E 32
D 14
#define DEFUPRI		LOG_NOTICE
D 12
#define DEFSPRI		LOG_EMERG
E 12
I 12
#define DEFSPRI		KERN_ERR
E 14
I 14
#define DEFUPRI		(LOG_USER|LOG_NOTICE)
#define DEFSPRI		(LOG_KERN|LOG_CRIT)
I 21
D 32
#define MARKCOUNT	10		/* ratio of minor to major marks */
E 32
I 32
#define TIMERINTVL	30		/* interval for checking flush, mark */
E 32
E 21
E 14
E 12
E 8

D 25
#include <syslog.h>
E 25
D 32
#include <errno.h>
E 32
D 44
#include <stdio.h>
#include <utmp.h>
#include <ctype.h>
I 6
D 32
#include <signal.h>
#include <sysexits.h>
E 32
#include <strings.h>
I 32
#include <setjmp.h>
E 32

I 25
#include <sys/syslog.h>
E 44
E 25
E 6
D 32
#include <sys/types.h>
E 32
I 18
#include <sys/param.h>
I 44
D 50
#include <sys/syslog.h>
E 50
E 44
I 32
D 62
#include <sys/errno.h>
E 62
E 32
E 18
#include <sys/ioctl.h>
#include <sys/stat.h>
I 9
#include <sys/wait.h>
E 9
D 6
#include <signal.h>
#include <sysexits.h>
E 6
#include <sys/socket.h>
D 62
#include <sys/file.h>
E 62
I 4
#include <sys/msgbuf.h>
E 4
I 3
#include <sys/uio.h>
E 3
#include <sys/un.h>
I 14
#include <sys/time.h>
#include <sys/resource.h>
I 32
D 62
#include <sys/signal.h>
E 62
E 32
E 14
I 6

E 6
#include <netinet/in.h>
#include <netdb.h>
I 62
#include <arpa/inet.h>
E 62

I 32
D 44
#define	CTTY	"/dev/console"
E 32
D 14
char	logname[] = "/dev/log";
char	defconf[] = "/etc/syslog.conf";
char	defpid[] = "/etc/syslog.pid";
E 14
I 14
char	*LogName = "/dev/log";
char	*ConfFile = "/etc/syslog.conf";
char	*PidFile = "/etc/syslog.pid";
E 14
D 32
char	ctty[] = "/dev/console";
E 32
I 32
char	ctty[] = CTTY;
E 44
I 44
D 62
#include <utmp.h>
E 62
I 62
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
E 62
#include <setjmp.h>
I 62
#include <signal.h>
E 62
#include <stdio.h>
D 62
#include <ctype.h>
E 62
I 62
#include <stdlib.h>
E 62
D 53
#include <strings.h>
E 53
I 53
#include <string.h>
E 53
I 49
#include <unistd.h>
I 62
#include <utmp.h>
E 62
E 49
#include "pathnames.h"
E 44
E 32

I 50
#define SYSLOG_NAMES
#include <sys/syslog.h>

E 50
I 44
char	*LogName = _PATH_LOG;
char	*ConfFile = _PATH_LOGCONF;
char	*PidFile = _PATH_LOGPID;
char	ctty[] = _PATH_CONSOLE;

E 44
I 14
#define FDMASK(fd)	(1 << (fd))

E 14
D 3
typedef char	bool;
#define	TRUE	1
#define	FALSE	0

E 3
#define	dprintf		if (Debug) printf

D 14
#define UNAMESZ	8	/* length of a login name */
E 14
I 14
D 48
#define UNAMESZ		8	/* length of a login name */
E 48
#define MAXUNAMES	20	/* maximum number of user names */
D 48
#define MAXFNAME	200	/* max file pathname length */
E 48
E 14

I 8
D 14
#define mask(x)	(1 << (x))
E 14
I 14
D 50
#define NOPRI		0x10	/* the "no priority" priority */
I 25
D 34
#define	LOG_MARK	(LOG_NFACILITIES << 3)	/* mark "facility" */
E 34
I 34
#define	LOG_MARK	LOG_MAKEPRI(LOG_NFACILITIES, 0)	/* mark "facility" */
E 34
E 25
E 14

E 50
E 8
/*
I 7
 * Flags to logmsg().
 */
D 14
#define IGN_CONS	0x1
#define SYNC_FILE	0x2
I 8
#define NOCOPY		0x4
#define ISMARK		0x10
E 14
E 8

I 14
#define IGN_CONS	0x001	/* don't print on console */
#define SYNC_FILE	0x002	/* do fsync on file after printing */
D 32
#define NOCOPY		0x004	/* don't suppress duplicate messages */
#define ADDDATE		0x008	/* add a date to the message */
I 21
#define MARK		0x010	/* this message is a mark */
E 32
I 32
#define ADDDATE		0x004	/* add a date to the message */
#define MARK		0x008	/* this message is a mark */
E 32
E 21

E 14
/*
E 7
 * This structure represents the files that will have log
 * copies printed.
 */

struct filed {
I 32
	struct	filed *f_next;		/* next in linked list */
E 32
D 14
	int	f_file;			/* file descriptor */
D 8
	short	f_pmask;		/* priority mask */
	short	f_flags;		/* see #defines below */
E 8
I 8
	u_int	f_pmask;		/* priority mask */
	u_int	f_flags;		/* see #defines below */
E 8
	struct	sockaddr_in f_addr;	/* forwarding address */
	char	f_name[248];		/* filename */
E 14
I 14
	short	f_type;			/* entry type, see below */
	short	f_file;			/* file descriptor */
I 21
	time_t	f_time;			/* time this was last written */
E 21
D 25
	u_char	f_pmask[LOG_NFACILITIES];	/* priority mask */
E 25
I 25
	u_char	f_pmask[LOG_NFACILITIES+1];	/* priority mask */
E 25
	union {
D 15
		char	f_uname[UNAMESZ+1][MAXUNAMES];
E 15
I 15
D 48
		char	f_uname[MAXUNAMES][UNAMESZ+1];
E 48
I 48
		char	f_uname[MAXUNAMES][UT_NAMESIZE+1];
E 48
E 15
D 25
		struct
		{
E 25
I 25
		struct {
E 25
D 17
			char	f_hname[32];
E 17
I 17
			char	f_hname[MAXHOSTNAMELEN+1];
E 17
			struct sockaddr_in	f_addr;
D 25
		}	f_forw;		/* forwarding address */
E 25
I 25
		} f_forw;		/* forwarding address */
E 25
D 48
		char	f_fname[MAXFNAME];
E 48
I 48
		char	f_fname[MAXPATHLEN];
E 48
D 25
	}	f_un;
E 25
I 25
	} f_un;
I 32
	char	f_prevline[MAXSVLINE];		/* last message logged */
	char	f_lasttime[16];			/* time of last occurrence */
	char	f_prevhost[MAXHOSTNAMELEN+1];	/* host from which recd. */
	int	f_prevpri;			/* pri of f_prevline */
	int	f_prevlen;			/* length of f_prevline */
	int	f_prevcount;			/* repetition cnt of prevline */
	int	f_repeatcount;			/* number of "repeated" msgs */
E 32
E 25
E 14
};

I 32
/*
 * Intervals at which we flush out "message repeated" messages,
 * in seconds after previous message is logged.  After each flush,
 * we move to the next interval until we reach the largest.
 */
int	repeatinterval[] = { 30, 120, 600 };	/* # of secs before flush */
#define	MAXREPEAT ((sizeof(repeatinterval) / sizeof(repeatinterval[0])) - 1)
#define	REPEATTIME(f)	((f)->f_time + repeatinterval[(f)->f_repeatcount])
#define	BACKOFF(f)	{ if (++(f)->f_repeatcount > MAXREPEAT) \
				 (f)->f_repeatcount = MAXREPEAT; \
			}

E 32
D 5
#define F_TTY	01		/* file is a tty */
#define F_MARK	02		/* write to the file periodically */
#define F_FORW	04		/* forward message to another host */
E 5
I 5
D 14
#define F_TTY	001		/* file is a tty */
#define F_MARK	002		/* write to the file periodically */
#define F_FORW	004		/* forward message to another host */
#define F_CONS	010		/* file is the console */
E 14
I 14
/* values for f_type */
#define F_UNUSED	0		/* unused entry */
#define F_FILE		1		/* regular file */
#define F_TTY		2		/* terminal */
#define F_CONSOLE	3		/* console terminal */
#define F_FORW		4		/* remote machine */
#define F_USERS		5		/* list of users */
#define F_WALL		6		/* everyone logged on */
E 14
E 5

D 14
struct filed	Files[NLOGS];

/* list of superusers */
struct susers {
D 8
	short	s_pmask;		/* priority mask */
E 8
I 8
	u_int	s_pmask;		/* priority mask */
E 8
	char	s_name[UNAMESZ+1];
E 14
I 14
char	*TypeNames[7] = {
	"UNUSED",	"FILE",		"TTY",		"CONSOLE",
	"FORW",		"USERS",	"WALL"
E 14
};

D 14
struct	susers Susers[NSUSERS];
E 14
I 14
D 32
struct filed	Files[NLOGS];
E 32
I 32
struct	filed *Files;
struct	filed consfile;
E 32
E 14

int	Debug;			/* debug flag */
D 14
int	LogFile;		/* log file descriptor */
D 4
int	DefPri = LOG_NOTICE;	/* the default priority for untagged msgs */
E 4
I 4
D 5
int	DefPri = LOG_ERR;	/* the default priority for untagged msgs */
E 5
I 5
D 8
int	DefPri = LOG_NOTICE;	/* default priority for untagged msgs */
int	DefSysPri = LOG_EMERG;	/* default priority for untagged system msgs */
E 5
E 4
D 3
int	Sumask = LOG_SALERT;	/* lowest priority written to super-users */
E 3
I 3
int	Sumask;			/* lowest priority written to super-users */
E 8
I 8
u_int	Sumask;			/* priorities written to super-users */
E 8
E 3
int	MarkIntvl = 15;		/* mark interval in minutes */
char	*ConfFile = defconf;	/* configuration file */
I 3
char	host[32];		/* our hostname */
E 3
char	rhost[32];		/* hostname of sender (forwarded messages) */
I 3
int	inet = 0;		/* non-zero if INET sockets are being used */
int	port;			/* port number for INET connections */
I 8
u_int	Copymask = 0xffffffff;	/* priorities to supress multiple copies */
char	prevline[MAXLINE + 1];	/* copy of last line to supress repeats */
char	*prevdate;		/* pointer to the date in prevline */
char	prevhost[32];		/* previous host */
int	prevflags;
int	prevpri;
int	count = 0;		/* number of times seen */
E 14
I 14
D 17
char	LocalHostName[32];	/* our hostname */
E 17
I 17
char	LocalHostName[MAXHOSTNAMELEN+1];	/* our hostname */
I 21
char	*LocalDomain;		/* our local domain name */
E 21
E 17
int	InetInuse = 0;		/* non-zero if INET sockets are being used */
I 32
int	finet;			/* Internet datagram socket */
E 32
int	LogPort;		/* port number for INET connections */
D 32
char	PrevLine[MAXLINE + 1];	/* copy of last line to supress repeats */
D 17
char	PrevHost[32];		/* previous host */
E 17
I 17
char	PrevHost[MAXHOSTNAMELEN+1];		/* previous host */
E 17
int	PrevFlags;
int	PrevPri;
int	PrevCount = 0;		/* number of times seen */
E 32
int	Initialized = 0;	/* set when we have initialized ourselves */
I 21
D 32
int	MarkInterval = 20;	/* interval between marks in minutes */
E 32
I 32
int	MarkInterval = 20 * 60;	/* interval between marks in seconds */
E 32
int	MarkSeq = 0;		/* mark sequence number */
E 21
E 14
E 8
E 3

D 48
extern	int errno, sys_nerr;
extern	char *sys_errlist[];
E 48
I 48
D 62
extern	int errno;
E 48
D 8
extern	char *ctime();
E 8
I 8
D 32
extern	char *ctime(), *index();
E 32
I 32
extern	char *ctime(), *index(), *calloc();
E 62
I 62
D 69
void  cfline __P((char *, struct filed *));
char *cvthname __P((struct sockaddr_in *));
D 66
void  daemon __P((int, int));
E 66
D 65
int   decode __P((char *, CODE *));
E 65
I 65
int   decode __P((const char *, CODE *));
E 65
void  die __P((int));
void  domark __P((int));
void  fprintlog __P((struct filed *, int, char *));
void  init __P((int));
void  logerror __P((char *));
void  logmsg __P((int, char *, char *, int));
void  printline __P((char *, char *));
void  printsys __P((char *));
void  reapchild __P((int));
char *ttymsg __P((struct iovec *, int, char *, int));
void  usage __P((void));
void  wallmsg __P((struct filed *, struct iovec *));
E 69
I 69
void	cfline __P((char *, struct filed *));
char   *cvthname __P((struct sockaddr_in *));
int	decode __P((const char *, CODE *));
void	die __P((int));
void	domark __P((int));
void	fprintlog __P((struct filed *, int, char *));
void	init __P((int));
void	logerror __P((char *));
void	logmsg __P((int, char *, char *, int));
void	printline __P((char *, char *));
void	printsys __P((char *));
void	reapchild __P((int));
char   *ttymsg __P((struct iovec *, int, char *, int));
void	usage __P((void));
void	wallmsg __P((struct filed *, struct iovec *));
E 69
E 62
E 32
E 8

I 62
int
E 62
I 14
D 23
#ifdef COMPAT
int	CompatMode = 0;		/* run in compatibility mode */
int	CompatCodes[32] = {
		LOG_USER|LOG_ALERT,	/* 0 -- undefined */
			/* kernel priorities */
		LOG_KERN|LOG_EMERG,	/* KERN_EMERG */
		LOG_KERN|LOG_ALERT,	/* KERN_ALERT */
		LOG_KERN|LOG_CRIT,	/* KERN_ERR */
		LOG_KERN|LOG_ERR,	/* KERN_FAIL */
		LOG_KERN|LOG_WARNING,	/* KERN_RECOV */
		LOG_KERN|LOG_INFO,	/* KERN_INFO */
			/* user abnormal conditions priorities */
		LOG_USER|LOG_EMERG,	/* LOG_EMERG */
		LOG_USER|LOG_ALERT,	/* LOG_ALERT */
		LOG_USER|LOG_CRIT,	/* LOG_CRIT */
		LOG_USER|LOG_ERR,	/* LOG_ERR */
		LOG_USER|LOG_ERR,	/* LOG_ERR */
		LOG_USER|LOG_WARNING,	/* LOG_WARNING */
			/* user priorities */
		LOG_USER|LOG_ALERT,	/* LOG_SALERT */
		LOG_AUTH|LOG_NOTICE,	/* LOG_SECURITY */
		LOG_USER|LOG_INFO,	/* LOG_FIXED */
		LOG_MAIL|LOG_ERR,	/* LOG_MAIL */
		LOG_DAEMON|LOG_ERR,	/* LOG_REJECT */
		LOG_USER|LOG_NOTICE,	/* LOG_NOTICE */
			/* user information priorities */
		LOG_USER|LOG_INFO,	/* LOG_INFO */
		LOG_LOCAL1|LOG_INFO,	/* LOG_INFO1 */
		LOG_LOCAL2|LOG_INFO,	/* LOG_INFO2 */
		LOG_LOCAL3|LOG_INFO,	/* LOG_INFO3 */
		LOG_LOCAL4|LOG_INFO,	/* LOG_INFO4 */
		LOG_LOCAL5|LOG_INFO,	/* LOG_INFO5 */
			/* user debug/local priorities */
		LOG_USER|LOG_DEBUG,	/* LOG_DEBUG */
		LOG_LOCAL1|LOG_DEBUG,	/* LOG_LOCAL1 */
		LOG_LOCAL2|LOG_DEBUG,	/* LOG_LOCAL2 */
		LOG_LOCAL3|LOG_DEBUG,	/* LOG_LOCAL3 */
		LOG_LOCAL4|LOG_DEBUG,	/* LOG_LOCAL4 */
		LOG_LOCAL5|LOG_DEBUG,	/* LOG_LOCAL5 */
		LOG_LOCAL6|LOG_DEBUG,	/* LOG_LOCAL6 */
};
#endif COMPAT

E 23
E 14
main(argc, argv)
	int argc;
D 62
	char **argv;
E 62
I 62
	char *argv[];
E 62
{
D 69
	register int i;
	register char *p;
D 4
	int funix, finet, defreadfds, len;
E 4
I 4
D 8
	int klog, funix, finet, defreadfds, len;
E 8
I 8
D 9
	int klog, funix, finet, defreadfds, klogm, len;
E 9
I 9
D 32
	int funix, finet, inetm, fklog, klogm, len;
E 32
I 32
	int funix, inetm, fklog, klogm, len;
E 69
I 69
	int ch, funix, i, inetm, fklog, klogm, len;
E 69
E 32
E 9
E 8
E 4
D 29
	struct sockaddr_un sun, fromunix;
E 29
I 29
	struct sockaddr_un sunx, fromunix;
E 29
	struct sockaddr_in sin, frominet;
	FILE *fp;
I 39
D 69
	int ch;
E 39
D 4
	char line[MAXLINE + 1];
E 4
I 4
	char line[MSG_BSIZE + 1];
E 69
I 69
	char *p, line[MSG_BSIZE + 1];
E 69
E 4
D 3
	extern die();
	extern int domark();
E 3
I 3
D 9
	extern int die(), domark();
E 9
I 9
D 39
	extern int die(), domark(), reapchild();
E 39
I 39
D 47
	extern int optind, die(), domark(), reapchild();
E 47
I 47
D 62
	extern int optind;
E 47
	extern char *optarg;
I 47
D 49
	void die(), domark(), reapchild();
E 49
I 49
	void die(), domark(), init(), reapchild();
E 62
E 49
E 47
E 39
E 9
E 3

D 14
	sun.sun_family = AF_UNIX;
	strncpy(sun.sun_path, logname, sizeof sun.sun_path);
I 3
	gethostname(host, sizeof host);
E 3

E 14
D 39
	while (--argc > 0) {
		p = *++argv;
D 8
		if (p[0] == '-') {
			switch (p[1]) {
			case 'm':		/* set mark interval */
				MarkIntvl = atoi(&p[2]);
				if (MarkIntvl <= 0)
					MarkIntvl = 1;
				break;
E 8
I 8
		if (p[0] != '-')
			usage();
		switch (p[1]) {
D 14
		case 'm':		/* set mark interval */
			MarkIntvl = atoi(&p[2]);
			if (MarkIntvl <= 0)
				MarkIntvl = 1;
			break;
E 8

E 14
D 8
			case 'f':		/* configuration file */
				if (p[2] != '\0')
					ConfFile = &p[2];
				break;
E 8
I 8
		case 'f':		/* configuration file */
			if (p[2] != '\0')
				ConfFile = &p[2];
			break;
E 8

E 39
I 39
	while ((ch = getopt(argc, argv, "df:m:p:")) != EOF)
D 69
		switch((char)ch) {
E 69
I 69
		switch(ch) {
E 69
E 39
D 8
			case 'd':		/* debug */
				Debug++;
				break;
E 8
I 8
		case 'd':		/* debug */
			Debug++;
			break;
E 8
D 39

I 14
D 23
#ifdef COMPAT
		case 'C':		/* run in compat mode */
			CompatMode++;
			break;
#endif COMPAT

E 23
E 14
D 3
			case 'p':		/* port */
E 3
I 3
D 8
			case 'p':		/* path */
E 3
				if (p[2] != '\0')
					strncpy(sun.sun_path, &p[2], 
						sizeof sun.sun_path);
				break;
			}
E 8
I 8
		case 'p':		/* path */
			if (p[2] != '\0')
D 14
				strncpy(sun.sun_path, &p[2], 
					sizeof sun.sun_path);
E 14
I 14
				LogName = &p[2];
E 39
I 39
		case 'f':		/* configuration file */
			ConfFile = optarg;
E 39
E 14
			break;
D 39

E 39
I 21
		case 'm':		/* mark interval */
D 39
			if (p[2] != '\0')
D 32
				MarkInterval = atoi(&p[2]);
E 32
I 32
				MarkInterval = atoi(&p[2]) * 60;
E 39
I 39
			MarkInterval = atoi(optarg) * 60;
E 39
E 32
			break;
D 39

E 39
I 39
		case 'p':		/* path */
			LogName = optarg;
			break;
		case '?':
E 39
E 21
		default:
			usage();
E 8
		}
D 39
	}
E 39
I 39
D 68
	if (argc -= optind)
E 68
I 68
	if ((argc -= optind) != 0)
E 68
		usage();
E 39

D 55
	if (!Debug) {
		if (fork())
			exit(0);
		for (i = 0; i < 10; i++)
			(void) close(i);
D 49
		(void) open("/", 0);
		(void) dup2(0, 1);
		(void) dup2(0, 2);
E 49
I 49
		(void) open("/", O_RDONLY, 0);
		(void) dup2(STDIN_FILENO, STDOUT_FILENO);
		(void) dup2(STDIN_FILENO, STDERR_FILENO);
E 49
D 3
		i = open("/dev/tty", 2);
E 3
I 3
D 8
		i = open("/dev/tty", O_RDWR);
E 3
	  	if (i >= 0) {
			ioctl(i, TIOCNOTTY, (char *)0);
			(void) close(i);
	  	}
E 8
I 8
		untty();
E 8
D 9
	}
E 9
I 9
	} else
E 55
I 55
	if (!Debug)
D 66
		daemon(0, 0);
E 66
I 66
		(void)daemon(0, 0);
E 66
	else
E 55
		setlinebuf(stdout);

I 32
	consfile.f_type = F_CONSOLE;
D 64
	(void) strcpy(consfile.f_un.f_fname, ctty);
E 32
I 21
	(void) gethostname(LocalHostName, sizeof LocalHostName);
E 64
I 64
	(void)strcpy(consfile.f_un.f_fname, ctty);
D 69
	(void)gethostname(LocalHostName, sizeof LocalHostName);
E 64
D 68
	if (p = index(LocalHostName, '.')) {
E 68
I 68
	if ((p = index(LocalHostName, '.')) != NULL) {
E 69
I 69
	(void)gethostname(LocalHostName, sizeof(LocalHostName));
	if ((p = strchr(LocalHostName, '.')) != NULL) {
E 69
E 68
		*p++ = '\0';
		LocalDomain = p;
D 64
	}
	else
E 64
I 64
	} else
E 64
		LocalDomain = "";
E 21
E 9
D 14
	signal(SIGTERM, die);
I 8
	signal(SIGINT, die);
I 9
	signal(SIGCHLD, reapchild);
E 14
I 14
D 64
	(void) signal(SIGTERM, die);
D 16
	(void) signal(SIGINT, die);
E 16
I 16
	(void) signal(SIGINT, Debug ? die : SIG_IGN);
	(void) signal(SIGQUIT, Debug ? die : SIG_IGN);
E 16
	(void) signal(SIGCHLD, reapchild);
I 21
	(void) signal(SIGALRM, domark);
D 32
	(void) alarm(MarkInterval * 60 / MARKCOUNT);
E 32
I 32
	(void) alarm(TIMERINTVL);
E 32
E 21
	(void) unlink(LogName);
E 64
I 64
	(void)signal(SIGTERM, die);
	(void)signal(SIGINT, Debug ? die : SIG_IGN);
	(void)signal(SIGQUIT, Debug ? die : SIG_IGN);
	(void)signal(SIGCHLD, reapchild);
	(void)signal(SIGALRM, domark);
	(void)alarm(TIMERINTVL);
	(void)unlink(LogName);
E 64

I 64
#ifndef SUN_LEN
#define SUN_LEN(unp) (strlen((unp)->sun_path) + 2)
#endif
E 64
I 41
D 69
	bzero((char *)&sunx, sizeof(sunx));
E 69
I 69
	memset(&sunx, 0, sizeof(sunx));
E 69
E 41
D 29
	sun.sun_family = AF_UNIX;
	(void) strncpy(sun.sun_path, LogName, sizeof sun.sun_path);
E 29
I 29
	sunx.sun_family = AF_UNIX;
D 64
	(void) strncpy(sunx.sun_path, LogName, sizeof sunx.sun_path);
E 64
I 64
D 69
	(void)strncpy(sunx.sun_path, LogName, sizeof sunx.sun_path);
E 69
I 69
	(void)strncpy(sunx.sun_path, LogName, sizeof(sunx.sun_path));
E 69
E 64
E 29
D 21
	(void) gethostname(LocalHostName, sizeof LocalHostName);
E 21
E 14
E 9
E 8
D 2
	signal(SIGALRM, domark);
	alarm(MarkIntvl * 60);
	
E 2
	funix = socket(AF_UNIX, SOCK_DGRAM, 0);
D 9
	if (funix >= 0 && bind(funix, &sun,
	    sizeof(sun.sun_family)+strlen(sun.sun_path)) < 0) {
		close(funix);
		funix = -1;
	}
	if (funix < 0) {
E 9
I 9
D 14
	if (funix < 0 || bind(funix, &sun,
E 14
I 14
D 29
	if (funix < 0 || bind(funix, (struct sockaddr *) &sun,
E 14
	    sizeof(sun.sun_family)+strlen(sun.sun_path)) < 0 ||
E 29
I 29
D 64
	if (funix < 0 || bind(funix, (struct sockaddr *) &sunx,
D 41
	    sizeof(sunx.sun_family)+strlen(sunx.sun_path)) < 0 ||
E 41
I 41
	    sizeof(sunx.sun_family)+sizeof(sunx.sun_len)+
	    strlen(sunx.sun_path)) < 0 ||
E 64
I 64
	if (funix < 0 ||
	    bind(funix, (struct sockaddr *)&sunx, SUN_LEN(&sunx)) < 0 ||
E 64
E 41
E 29
D 14
	    chmod(sun.sun_path, 0666) < 0) {
E 9
		fp = fopen(ctty, "w");
D 8
		fprintf(fp, "\r\nsyslog: cannot create %s (%d)\r\n", logname, errno);
E 8
I 8
		fprintf(fp, "\r\nsyslogd: cannot create %s (%d)\r\n", logname, errno);
E 8
		dprintf("cannot create %s (%d)\n", logname, errno);
		exit(1);
E 14
I 14
	    chmod(LogName, 0666) < 0) {
		(void) sprintf(line, "cannot create %s", LogName);
		logerror(line);
		dprintf("cannot create %s (%d)\n", LogName, errno);
		die(0);
E 14
	}
D 8
	defreadfds = 1 << funix;
E 8
I 8
D 9
	defreadfds = mask(funix);
E 9
E 8
	finet = socket(AF_INET, SOCK_DGRAM, 0);
I 62
	inetm = 0;
E 62
	if (finet >= 0) {
		struct servent *sp;

		sp = getservbyname("syslog", "udp");
		if (sp == NULL) {
			errno = 0;
			logerror("syslog/udp: unknown service");
D 14
			die();
E 14
I 14
			die(0);
E 14
		}
I 61
D 69
		bzero((char *)&sin, sizeof(sin));
E 69
I 69
		memset(&sin, 0, sizeof(sin));
E 69
E 61
		sin.sin_family = AF_INET;
D 3
		sin.sin_port = sp->s_port;
E 3
I 3
D 14
		sin.sin_port = port = sp->s_port;
E 3
		if (bind(finet, &sin, sizeof(sin), 0) < 0) {
E 14
I 14
		sin.sin_port = LogPort = sp->s_port;
D 49
		if (bind(finet, &sin, sizeof(sin)) < 0) {
E 49
I 49
		if (bind(finet, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
E 49
E 14
			logerror("bind");
D 14
			die();
E 14
I 14
			if (!Debug)
				die(0);
		} else {
			inetm = FDMASK(finet);
			InetInuse = 1;
E 14
		}
D 8
		defreadfds |= 1 << finet;
E 8
I 8
D 9
		defreadfds |= mask(finet);
E 9
I 9
D 14
		inetm = mask(finet);
E 9
E 8
I 3
		inet = 1;
E 14
E 3
	}
I 4
D 8
	if ((klog = open("/dev/klog", O_RDONLY)) >= 0)
		defreadfds |= 1 << klog;
	else
E 8
I 8
D 9
	if ((klog = open("/dev/klog", O_RDONLY)) >= 0) {
		klogm = mask(klog);
		defreadfds |= klogm;
	} else {
E 9
I 9
D 44
	if ((fklog = open("/dev/klog", O_RDONLY)) >= 0)
E 44
I 44
	if ((fklog = open(_PATH_KLOG, O_RDONLY, 0)) >= 0)
E 44
D 14
		klogm = mask(fklog);
E 14
I 14
		klogm = FDMASK(fklog);
E 14
	else {
E 9
E 8
D 44
		dprintf("can't open /dev/klog (%d)\n", errno);
E 44
I 44
		dprintf("can't open %s (%d)\n", _PATH_KLOG, errno);
E 44
I 8
		klogm = 0;
	}
E 8
E 4

	/* tuck my process id away */
D 14
	fp = fopen(defpid, "w");
E 14
I 14
	fp = fopen(PidFile, "w");
E 14
	if (fp != NULL) {
		fprintf(fp, "%d\n", getpid());
D 14
		fclose(fp);
E 14
I 14
		(void) fclose(fp);
E 14
	}

	dprintf("off & running....\n");

D 14
	for (i = 0; i < NLOGS; i++)
		Files[i].f_file = -1;
E 14
D 62
	init();
E 62
I 62
	init(0);
E 62
I 9
D 14
	signal(SIGHUP, init);
E 9
I 2
	signal(SIGALRM, domark);
	alarm(MarkIntvl * 60);
E 14
I 14
D 64
	(void) signal(SIGHUP, init);
E 64
I 64
	(void)signal(SIGHUP, init);
E 64
E 14

E 2
	for (;;) {
D 6
		int domain, nfds, readfds = defreadfds;
E 6
I 6
D 9
		int nfds, readfds = defreadfds;
E 9
I 9
D 14
		int nfds, readfds = mask(funix) | inetm | klogm;
E 14
I 14
		int nfds, readfds = FDMASK(funix) | inetm | klogm;
E 14
E 9
E 6

I 14
D 69
		errno = 0;
E 69
E 14
I 9
D 31
		dprintf("readfds = %#x\n", readfds, funix, finet, fklog);
E 31
I 31
		dprintf("readfds = %#x\n", readfds);
E 31
E 9
D 14
		nfds = select(20, &readfds, 0, 0, 0);
E 14
I 14
D 64
		nfds = select(20, (fd_set *) &readfds, (fd_set *) NULL,
D 49
				  (fd_set *) NULL, (struct timeval *) NULL);
E 49
I 49
		    (fd_set *) NULL, (struct timeval *) NULL);
E 64
I 64
		nfds = select(20, (fd_set *)&readfds, (fd_set *)NULL,
		    (fd_set *)NULL, (struct timeval *)NULL);
E 64
E 49
E 14
I 8
D 32
		dprintf("got a message (%d, %#x)\n", nfds, readfds);
E 32
E 8
		if (nfds == 0)
			continue;
		if (nfds < 0) {
D 14
			if (errno == EINTR)
				continue;
			logerror("select");
E 14
I 14
			if (errno != EINTR)
				logerror("select");
E 14
			continue;
		}
I 32
		dprintf("got a message (%d, %#x)\n", nfds, readfds);
E 32
I 7
D 8
		if (readfds & (1 << klog)) {
E 8
I 8
		if (readfds & klogm) {
E 8
D 9
			i = read(klog, line, sizeof(line) - 1);
E 9
I 9
			i = read(fklog, line, sizeof(line) - 1);
E 9
			if (i > 0) {
				line[i] = '\0';
				printsys(line);
D 8
			} else if (i < 0 && errno != EINTR)
E 8
I 8
			} else if (i < 0 && errno != EINTR) {
E 8
D 9
				logerror("read");
I 8
				defreadfds &= ~klogm;
				klog = -1;
E 9
I 9
				logerror("klog");
				fklog = -1;
E 9
				klogm = 0;
			}
E 8
		}
E 7
D 8
		if (readfds & (1 << funix)) {
E 8
I 8
D 14
		if (readfds & mask(funix)) {
E 14
I 14
		if (readfds & FDMASK(funix)) {
E 14
E 8
D 6
			domain = AF_UNIX;
E 6
D 69
			len = sizeof fromunix;
E 69
I 69
			len = sizeof(fromunix);
E 69
D 14
			i = recvfrom(funix, line, MAXLINE, 0, &fromunix, &len);
E 14
I 14
			i = recvfrom(funix, line, MAXLINE, 0,
D 49
				     (struct sockaddr *) &fromunix, &len);
E 49
I 49
D 64
			    (struct sockaddr *) &fromunix, &len);
E 64
I 64
			    (struct sockaddr *)&fromunix, &len);
E 64
E 49
E 14
D 6
		} else if (readfds & (1 << finet)) {
			domain = AF_INET;
E 6
I 6
			if (i > 0) {
				line[i] = '\0';
D 14
				printline(1, line);
E 14
I 14
				printline(LocalHostName, line);
E 14
			} else if (i < 0 && errno != EINTR)
D 14
				logerror("recvfrom");
E 14
I 14
				logerror("recvfrom unix");
E 14
		}
D 8
		if (readfds & (1 << finet)) {
E 8
I 8
D 9
		if (readfds & mask(finet)) {
E 9
I 9
		if (readfds & inetm) {
E 9
E 8
E 6
D 69
			len = sizeof frominet;
E 69
I 69
			len = sizeof(frominet);
E 69
D 49
			i = recvfrom(finet, line, MAXLINE, 0, &frominet, &len);
E 49
I 49
			i = recvfrom(finet, line, MAXLINE, 0,
D 64
			    (struct sockaddr *) &frominet, &len);
E 64
I 64
			    (struct sockaddr *)&frominet, &len);
E 64
E 49
I 4
D 6
		} else {
E 6
I 6
D 14
			if (i > 0 && chkhost(&frominet)) {
E 14
I 14
			if (i > 0) {
D 62
				extern char *cvthname();

E 62
E 14
				line[i] = '\0';
D 14
				printline(0, line);
E 14
I 14
				printline(cvthname(&frominet), line);
E 14
			} else if (i < 0 && errno != EINTR)
D 14
				logerror("recvfrom");
E 14
I 14
				logerror("recvfrom inet");
E 14
		} 
D 7
		if (readfds & (1 << klog)) {
E 6
			i = read(klog, line, sizeof(line) - 1);
D 6
			if (i < 0) {
E 6
I 6
			if (i > 0) {
				line[i] = '\0';
				printsys(line);
			} else if (i < 0 && errno != EINTR)
E 6
				logerror("read");
D 6
				continue;
			}
			line[i] = '\0';
			printsys(line);
			continue;
E 6
E 4
		}
E 7
D 6
		if (i < 0) {
			if (errno == EINTR)
				continue;
			logerror("recvfrom");
			continue;
		}
		if (domain == AF_INET && !chkhost(&frominet))
			continue;
		line[i] = '\0';
D 4
		printline(domain == AF_UNIX, line);
E 4
I 4
		printline(domain != AF_INET, line);
E 6
E 4
	}
}

I 62
void
E 62
I 8
usage()
{
I 69

E 69
D 14
	fprintf(stderr, "usage: syslogd [-m#] [-d] [-ppath] [-fconffile]\n");
E 14
I 14
D 21
	fprintf(stderr, "usage: syslogd [-d] [-ppath] [-fconffile]\n");
E 21
I 21
D 39
	fprintf(stderr, "usage: syslogd [-d] [-mmarkinterval] [-ppath] [-fconffile]\n");
E 39
I 39
D 48
	fprintf(stderr, "usage: syslogd [-d] [-m markinterval] [-p path] [-f conffile]\n");
E 48
I 48
D 64
	(void) fprintf(stderr,
E 64
I 64
	(void)fprintf(stderr,
E 64
D 57
	    "usage: syslogd [-d] [-f conffile] [-m markinterval] [-p path]\n");
E 57
I 57
	    "usage: syslogd [-f conffile] [-m markinterval] [-p logpath]\n");
E 57
E 48
E 39
E 21
E 14
	exit(1);
}

D 55
untty()
{
	int i;

	if (!Debug) {
D 45
		i = open("/dev/tty", O_RDWR);
E 45
I 45
D 49
		i = open(_PATH_TTY, O_RDWR);
E 49
I 49
		i = open(_PATH_TTY, O_RDWR, 0);
E 49
E 45
		if (i >= 0) {
D 14
			ioctl(i, TIOCNOTTY, (char *)0);
E 14
I 14
			(void) ioctl(i, (int) TIOCNOTTY, (char *)0);
E 14
			(void) close(i);
		}
	}
}

E 55
E 8
/*
 * Take a raw input line, decode the message, and print the message
 * on the appropriate log files.
 */
D 62

E 62
I 62
void
E 62
D 14
printline(local, msg)
	int local;
E 14
I 14
printline(hname, msg)
	char *hname;
E 14
	char *msg;
{
D 69
	register char *p, *q;
	register int c;
D 4
	char line[MAXLINE + sizeof(rhost) + 4];
E 4
I 4
	char line[MAXLINE + 1];
E 4
	int pri;
E 69
I 69
	int c, pri;
	char *p, *q, line[MAXLINE + 1];
E 69

	/* test for special codes */
D 8
	pri = DefPri;
E 8
I 8
	pri = DEFUPRI;
E 8
	p = msg;
D 8
	if (p[0] == '<' && p[2] == '>') {
		switch (p[1]) {
		case '*':	/* reset default message priority */
			dprintf("default priority = %c\n", p[3]);
			c = p[3] - '0';
			if ((unsigned) c <= 9)
				DefPri = c;
			break;

		case '$':	/* reconfigure */
			dprintf("reconfigure\n");
			init();
		}
		p++;
		pri = *p++ - '0';
		p++;
		if ((unsigned) pri > LOG_DEBUG)
			pri = DefPri;
E 8
I 8
	if (*p == '<') {
		pri = 0;
		while (isdigit(*++p))
			pri = 10 * pri + (*p - '0');
		if (*p == '>')
			++p;
D 14
		if (pri <= 0 || pri >= 32)
E 14
I 14
D 34
		if (pri <= 0 || pri >= (LOG_NFACILITIES << 3))
E 14
			pri = DEFUPRI;
E 34
E 8
	}
I 34
	if (pri &~ (LOG_FACMASK|LOG_PRIMASK))
		pri = DEFUPRI;
E 34

I 14
	/* don't allow users to log kernel messages */
D 34
	if ((pri & LOG_PRIMASK) == LOG_KERN)
		pri |= LOG_USER;
E 34
I 34
	if (LOG_FAC(pri) == LOG_KERN)
		pri = LOG_MAKEPRI(LOG_USER, LOG_PRI(pri));
E 34

E 14
	q = line;
I 14
D 23
#ifdef COMPAT
	if (CompatMode) {
		register char *lp = index(p, ':');
E 23

D 23
		if (lp && lp[1] == ' ' && lp[17] == '-' && lp[18] == '-') {
			/*
			 * Old format message
			 */
			dprintf("mapping <%d> to <%d>\n", pri, CompatCodes[pri]);
			pri = CompatCodes[pri];
			(void) strncpy(q, lp + 2, 15);
			q += 15;
			*q++ = ' ';
			(void) strncpy(q, p, lp - p + 1);
			q += lp - p + 1;
			p = lp + 19;
		}
	}
#endif COMPAT

E 23
E 14
D 3
	if (!local) {
		sprintf(q, "%s: ", rhost);
		q += strlen(q);
	}
E 3
D 39
	while ((c = *p++ & 0177) != '\0' && c != '\n' &&
D 4
	    q < &line[sizeof(line) - 2]) {
E 4
I 4
	    q < &line[sizeof(line) - 1]) {
E 4
		if (iscntrl(c)) {
E 39
I 39
	while ((c = *p++ & 0177) != '\0' &&
	    q < &line[sizeof(line) - 1])
D 43
		if (c == '\n')
			*q++ = ' ';
		else if (iscntrl(c)) {
E 39
			*q++ = '^';
			*q++ = c ^ 0100;
		} else
E 43
I 43
		if (iscntrl(c))
			if (c == '\n')
				*q++ = ' ';
			else if (c == '\t')
				*q++ = '\t';
			else {
				*q++ = '^';
				*q++ = c ^ 0100;
			}
		else
E 43
			*q++ = c;
D 39
	}
E 39
D 3
	*q++ = '\n';
E 3
	*q = '\0';

D 3
	logmsg(pri, line);
E 3
I 3
D 5
	logmsg(pri, line, local ? host : rhost);
E 5
I 5
D 14
	logmsg(pri, line, local ? host : rhost, 0);
E 14
I 14
	logmsg(pri, line, hname, 0);
E 14
E 5
I 4
}

/*
 * Take a raw input line from /dev/klog, split and format similar to syslog().
 */
D 62

E 62
I 62
void
E 62
printsys(msg)
	char *msg;
{
D 69
	register char *p, *q;
	register int c;
	char line[MAXLINE + 1];
D 5
	int pri;
E 5
I 5
D 8
	static char prevline[MAXLINE + 1];
	static int count = 0;
E 8
D 7
	int pri, ign;
E 7
I 7
	int pri, flags;
I 8
	char *lp;
E 69
I 69
	int c, pri, flags;
	char *lp, *p, *q, line[MAXLINE + 1];
E 69
E 8
E 7
E 5
D 14
	long now;
E 14
I 14
D 32
	time_t now;
E 32
E 14

D 14
	time(&now);
I 8
	sprintf(line, "vmunix: %.15s-- ", ctime(&now) + 4);
E 14
I 14
D 32
	(void) time(&now);
	(void) sprintf(line, "%.15s vmunix: ", ctime(&now) + 4);
E 32
I 32
D 48
	(void) sprintf(line, "vmunix: ");
E 48
I 48
D 64
	(void) strcpy(line, "vmunix: ");
E 64
I 64
	(void)strcpy(line, "vmunix: ");
E 64
E 48
E 32
E 14
	lp = line + strlen(line);
E 8
	for (p = msg; *p != '\0'; ) {
D 8
		/* test for special codes */
E 8
D 5
		pri = DefPri;
E 5
I 5
D 7
		ign = 0;
E 7
I 7
D 32
		flags = SYNC_FILE;	/* fsync file after write */
E 32
I 32
		flags = SYNC_FILE | ADDDATE;	/* fsync file after write */
E 32
E 7
D 8
		pri = DefSysPri;
E 5
		if (p[0] == '<' && p[2] == '>') {
			switch (p[1]) {
			case '*':	/* reset default message priority */
				dprintf("default priority = %c\n", p[3]);
				c = p[3] - '0';
				if ((unsigned) c <= 9)
D 5
					DefPri = c;
E 5
I 5
					DefSysPri = c;
E 5
				break;

			case '$':	/* reconfigure */
				dprintf("reconfigure\n");
				init();
			}
			p++;
			pri = *p++ - '0';
			p++;
			if ((unsigned) pri > LOG_DEBUG)
D 5
				pri = DefPri;
		}
E 5
I 5
				pri = DefSysPri;
E 8
I 8
		pri = DEFSPRI;
		if (*p == '<') {
			pri = 0;
			while (isdigit(*++p))
				pri = 10 * pri + (*p - '0');
			if (*p == '>')
				++p;
D 14
			if (pri <= 0 || pri >= 32)
E 14
I 14
D 34
			if (pri <= 0 || pri >= (LOG_NFACILITIES << 3))
E 14
				pri = DEFSPRI;
E 34
I 14
D 23
#ifdef COMPAT
			else if (CompatMode) {
				dprintf("mapping <%d> to <%d>\n", pri, CompatCodes[pri]);
				pri = CompatCodes[pri];
			}
#endif COMPAT
E 23
E 14
E 8
D 7
		} else
			ign = 1; /* kernel printf's come out on console */
E 7
I 7
		} else {
			/* kernel printf's come out on console */
			flags |= IGN_CONS;
		}
I 34
		if (pri &~ (LOG_FACMASK|LOG_PRIMASK))
			pri = DEFSPRI;
E 34
E 7
E 5
D 8

		q = line;
		sprintf(q, "vmunix: %.15s-- ", ctime(&now) + 4);
		q += strlen(q);
		while ((c = *p++) != '\0' && c != '\n' &&
		    q < &line[sizeof(line) - 1])
E 8
I 8
		q = lp;
		while (*p != '\0' && (c = *p++) != '\n' &&
		    q < &line[MAXLINE])
E 8
			*q++ = c;
		*q = '\0';
D 5
		logmsg(pri, line, host);
E 5
I 5
D 8
		if (strcmp(line+26, prevline+26) == 0) {
			count++;
			strncpy(prevline+8, line+8, 15); /* update time */
			continue;
		}
		if (count) {
			if (count > 1)
				sprintf(prevline+26,
				    "last message repeated %d times", count);
D 7
			logmsg(pri, prevline, host, ign);
E 7
I 7
			logmsg(pri, prevline, host, flags);
E 7
		}
		count = 0;
		strcpy(prevline, line);
E 8
D 7
		logmsg(pri, line, host, ign);
E 7
I 7
D 14
		logmsg(pri, line, host, flags);
E 14
I 14
		logmsg(pri, line, LocalHostName, flags);
E 14
E 7
E 5
	}
E 4
E 3
}

I 32
time_t	now;

E 32
/*
 * Log a message to the appropriate log files, users, etc. based on
 * the priority.
 */
D 62

E 62
I 62
void
E 62
D 3
logmsg(pri, msg)
E 3
I 3
D 5
logmsg(pri, msg, from)
E 5
I 5
D 7
logmsg(pri, msg, from, igncons)
E 7
I 7
logmsg(pri, msg, from, flags)
E 7
E 5
E 3
D 14
	int	pri;
D 3
	char	*msg;
E 3
I 3
	char	*msg, *from;
I 5
D 7
	int	igncons;
E 7
I 7
	int	flags;
E 14
I 14
	int pri;
	char *msg, *from;
	int flags;
E 14
E 7
E 5
E 3
{
D 21
	char line[MAXLINE + 1];
E 21
D 69
	register struct filed *f;
D 32
	register int l;
E 32
I 3
D 14
	struct iovec iov[4];
E 14
I 14
	int fac, prilev;
I 21
D 32
	time_t now;
	int omask;
E 21
	struct iovec iov[6];
E 14
	register struct iovec *v = iov;
I 9
D 21
	int omask;
E 21
I 21
	char line[MAXLINE + 1];
E 32
I 32
	int omask, msglen;
E 69
I 69
	struct filed *f;
	int fac, msglen, omask, prilev;
E 69
	char *timestamp;
I 49
D 62
	time_t time();
E 62
E 49
E 32
E 21
E 9
E 3

I 14
D 48
	dprintf("logmsg: pri %o, flags %x, from %s, msg %s\n", pri, flags, from, msg);
E 48
I 48
	dprintf("logmsg: pri %o, flags %x, from %s, msg %s\n",
	    pri, flags, from, msg);
E 48

E 14
I 9
D 20
	omask = sigblock(sigmask(SIGALRM)|sigmask(SIGHUP));
E 20
I 20
D 21
	omask = sigblock(sigmask(SIGHUP));
E 21
I 21
	omask = sigblock(sigmask(SIGHUP)|sigmask(SIGALRM));
E 21
E 20

E 9
I 8
D 14
	if ((flags & NOCOPY) == 0) {
		register char *cp;
E 14
I 14
	/*
	 * Check to see if msg looks non-standard.
	 */
D 21
	if (!(flags & ADDDATE) && (strlen(msg) < 16 ||
	    msg[3] != ' ' || msg[6] != ' ' ||
	    msg[9] != ':' || msg[12] != ':' || msg[15] != ' '))
E 21
I 21
D 32
	if (strlen(msg) < 16 || msg[3] != ' ' || msg[6] != ' ' ||
E 32
I 32
	msglen = strlen(msg);
	if (msglen < 16 || msg[3] != ' ' || msg[6] != ' ' ||
E 32
	    msg[9] != ':' || msg[12] != ':' || msg[15] != ' ')
E 21
		flags |= ADDDATE;
E 14

D 14
		/*
		 * Check to see if copies should be supressed or
		 * msg looks non-standard (e.g., 'prog: Feb 16 13:23:56-- ').
		 */
		if ((Copymask & mask(pri)) == 0 ||
		    (cp = index(msg, ':')) == NULL || strlen(cp) < 20 ||
		    cp[5] != ' ' || cp[8] != ' ' || cp[11] != ':' ||
		    cp[14] != ':' || cp[17] != '-' || cp[18] != '-' ||
		    cp[19] != ' ')
E 14
I 14
D 21
	if ((flags & NOCOPY) == 0) {
		if (flags & ADDDATE)
E 21
I 21
D 32
	if (!(flags & NOCOPY)) {
		if (flags & (ADDDATE|MARK))
E 21
E 14
			flushmsg();
D 14
		else if (!strncmp(msg, prevline, cp-msg) &&
		    !strcmp(cp+20, prevdate+18)) {
E 14
I 14
		else if (!strcmp(msg + 16, PrevLine + 16)) {
E 14
			/* we found a match, update the time */
D 14
			strncpy(prevdate, cp+2, 15);
			count++;
E 14
I 14
			(void) strncpy(PrevLine, msg, 15);
			PrevCount++;
E 14
I 10
			(void) sigsetmask(omask);
E 10
			return;
		} else {
			/* new line, save it */
			flushmsg();
D 14
			strcpy(prevline, msg);
			strcpy(prevhost, from);
			prevdate = prevline + (cp - msg) + 2;
			prevflags = flags;
			prevpri = pri;
E 14
I 14
			(void) strcpy(PrevLine, msg);
			(void) strcpy(PrevHost, from);
			PrevFlags = flags;
			PrevPri = pri;
E 14
		}
	}

E 32
I 14
D 21
	if (flags & ADDDATE) {
		time_t now;

		(void) time(&now);
E 21
I 21
D 64
	(void) time(&now);
E 64
I 64
	(void)time(&now);
E 64
	if (flags & ADDDATE)
E 21
D 32
		v->iov_base = ctime(&now) + 4;
D 21
	} else
E 21
I 21
	else
E 21
		v->iov_base = msg;
	v->iov_len = 15;
	v++;
	v->iov_base = " ";
	v->iov_len = 1;
	v++;
E 14
E 8
I 3
	v->iov_base = from;
	v->iov_len = strlen(v->iov_base);
	v++;
	v->iov_base = " ";
	v->iov_len = 1;
	v++;
D 14
	v->iov_base = msg;
E 14
I 14
	if (flags & ADDDATE)
		v->iov_base = msg;
	else
		v->iov_base = msg + 16;
E 14
	v->iov_len = strlen(v->iov_base);
	v++;
E 32
I 32
		timestamp = ctime(&now) + 4;
	else {
		timestamp = msg;
		msg += 16;
		msglen -= 16;
	}
E 32
I 14

	/* extract facility and priority level */
D 34
	fac = (pri & LOG_FACMASK) >> 3;
E 34
I 25
	if (flags & MARK)
		fac = LOG_NFACILITIES;
E 25
D 34
	prilev = pri & LOG_PRIMASK;
E 34
I 34
	else
		fac = LOG_FAC(pri);
	prilev = LOG_PRI(pri);
E 34

E 14
E 3
	/* log the message to the particular outputs */
I 14
	if (!Initialized) {
D 32
		int cfd = open(ctty, O_WRONLY);
E 32
I 32
		f = &consfile;
D 49
		f->f_file = open(ctty, O_WRONLY);
E 49
I 49
		f->f_file = open(ctty, O_WRONLY, 0);
E 49
E 32

D 32
		if (cfd >= 0) {
			v->iov_base = "\r\n";
			v->iov_len = 2;
			(void) writev(cfd, iov, 6);
			(void) close(cfd);
E 32
I 32
		if (f->f_file >= 0) {
D 55
			untty();
E 55
D 34
			fprintlog(f, flags);
E 34
I 34
D 38
			fprintlog(f, flags, (char *)NULL);
E 38
I 38
			fprintlog(f, flags, msg);
E 38
E 34
D 64
			(void) close(f->f_file);
E 64
I 64
			(void)close(f->f_file);
E 64
E 32
		}
I 16
D 32
		untty();
E 32
I 20
D 64
		(void) sigsetmask(omask);
E 64
I 64
		(void)sigsetmask(omask);
E 64
E 20
E 16
		return;
	}
E 14
D 32
	for (f = Files; f < &Files[NLOGS]; f++) {
E 32
I 32
	for (f = Files; f; f = f->f_next) {
E 32
D 8
		if (f->f_file < 0 || f->f_pmask < pri)
E 8
I 8
D 14
		if (f->f_file < 0)
E 14
I 14
		/* skip messages that are incorrect priority */
D 50
		if (f->f_pmask[fac] < prilev || f->f_pmask[fac] == NOPRI)
E 50
I 50
		if (f->f_pmask[fac] < prilev ||
		    f->f_pmask[fac] == INTERNAL_NOPRI)
E 50
E 14
E 8
			continue;
I 5
D 7
		if (igncons && (f->f_flags & F_CONS))
E 7
I 7
D 8
		if ((flags & IGN_CONS) && (f->f_flags & F_CONS))
E 7
			continue;
		if (pri < 0) {	/* mark message */
E 8
I 8
D 14
		if (flags & ISMARK) {	/* mark message */
E 8
D 9
			struct stat stb;
			long now;

E 9
			if (!(f->f_flags & F_MARK))
				continue;
D 9
			if (fstat(f->f_file, &stb) < 0)
				continue;
			time(&now);
			if (!(f->f_flags & F_CONS) &&
			    stb.st_mtime > now - MarkIntvl * 60)
				continue;
E 9
I 9
			if (!(f->f_flags & F_CONS)) {
				struct stat stb;
				long now;
E 14

I 34
		if (f->f_type == F_CONSOLE && (flags & IGN_CONS))
			continue;

E 34
I 21
		/* don't output marks to recently written files */
D 32
		if ((flags & MARK) && (now - f->f_time) < (MarkInterval * 60 / 2))
E 32
I 32
		if ((flags & MARK) && (now - f->f_time) < MarkInterval / 2)
E 32
			continue;

E 21
D 14
				if (fstat(f->f_file, &stb) < 0)
					continue;
				time(&now);
				if (stb.st_mtime > now - MarkIntvl * 60)
					continue;
			}
E 9
D 8
		}
E 8
I 8
		} else if ((f->f_pmask & mask(pri)) == 0 ||
		    (flags & IGN_CONS) && (f->f_flags & F_CONS))
			continue;
E 8
E 5
		if (f->f_flags & F_FORW) {
			sprintf(line, "<%d>%s", pri, msg);
E 14
I 14
D 32
		dprintf("Logging to %s", TypeNames[f->f_type]);
I 21
		f->f_time = now;
E 21
		switch (f->f_type) {
		case F_UNUSED:
			dprintf("\n");
			break;

		case F_FORW:
			dprintf(" %s\n", f->f_un.f_forw.f_hname);
D 24
			(void) sprintf(line, "<%d>%.15s %s", pri, v[0].iov_base,
				v[4].iov_base);
E 24
I 24
			(void) sprintf(line, "<%d>%.15s %s", pri,
				iov[0].iov_base, iov[4].iov_base);
E 24
E 14
			l = strlen(line);
			if (l > MAXLINE)
				l = MAXLINE;
			if (sendto(f->f_file, line, l, 0,
D 7
			    &f->f_addr, sizeof f->f_addr) != l)
E 7
I 7
D 14
			    &f->f_addr, sizeof f->f_addr) != l) {
E 14
I 14
			    &f->f_un.f_forw.f_addr,
			    sizeof f->f_un.f_forw.f_addr) != l) {
E 14
				int e = errno;
				(void) close(f->f_file);
D 14
				f->f_file = -1;
E 14
I 14
				f->f_type = F_UNUSED;
E 14
				errno = e;
E 7
				logerror("sendto");
E 32
I 32
		/*
		 * suppress duplicate lines to this file
		 */
		if ((flags & MARK) == 0 && msglen == f->f_prevlen &&
		    !strcmp(msg, f->f_prevline) &&
		    !strcmp(from, f->f_prevhost)) {
D 64
			(void) strncpy(f->f_lasttime, timestamp, 15);
E 64
I 64
			(void)strncpy(f->f_lasttime, timestamp, 15);
E 64
			f->f_prevcount++;
D 39
			dprintf("msg repeated %d times, %d sec of %d\n",
E 39
I 39
			dprintf("msg repeated %d times, %ld sec of %d\n",
E 39
			    f->f_prevcount, now - f->f_time,
			    repeatinterval[f->f_repeatcount]);
			/*
			 * If domark would have logged this by now,
			 * flush it now (so we don't hold isolated messages),
			 * but back off so we'll flush less often
			 * in the future.
			 */
			if (now > REPEATTIME(f)) {
D 34
				fprintlog(f, flags);
E 34
I 34
				fprintlog(f, flags, (char *)NULL);
E 34
				BACKOFF(f);
E 32
I 7
			}
E 7
D 14
			continue;
		}
D 3
		l = strlen(msg);
		if (write(f->f_file, msg, l) != l) {
			logerror(f->f_name);
			(void) close(f->f_file);
			f->f_file = -1;
E 3
I 3
		if (f->f_flags & F_TTY) {
			v->iov_base = "\r\n";
			v->iov_len = 2;
		} else {
			v->iov_base = "\n";
			v->iov_len = 1;
E 3
		}
D 3
		if ((f->f_flags & F_TTY) && write(f->f_file, "\r", 1) != 1) {
E 3
I 3
		if (writev(f->f_file, iov, 4) < 0) {
E 3
D 7
			logerror(f->f_name);
E 7
I 7
			int e = errno;
E 7
			(void) close(f->f_file);
D 9
			f->f_file = -1;
D 7
		}
E 7
I 7
			errno = e;
			logerror(f->f_name);
E 9
I 9
			/*
			 * Check for EBADF on the console due to vhangup() XXX
			 */
			if (e == EBADF && (f->f_flags & F_TTY)) {
				f->f_file = open(f->f_name, O_WRONLY|O_APPEND);
				if (f->f_file < 0)
					logerror(f->f_name);
			} else {
				f->f_file = -1;
				errno = e;
				logerror(f->f_name);
E 14
I 14
D 32
			break;

		case F_CONSOLE:
			if (flags & IGN_CONS) {
				dprintf(" (ignored)\n");
				break;
E 32
I 32
		} else {
			/* new line, save it */
D 34
			if (f->f_prevcount) {
				fprintlog(f, 0);
				f->f_repeatcount = 0;
E 32
E 14
			}
E 34
I 34
			if (f->f_prevcount)
				fprintlog(f, 0, (char *)NULL);
			f->f_repeatcount = 0;
E 34
I 32
D 64
			(void) strncpy(f->f_lasttime, timestamp, 15);
D 34
			if (msglen < MAXSVLINE && (f->f_type != F_CONSOLE ||
			    (flags & IGN_CONS) == 0)) {
E 34
I 34
			(void) strncpy(f->f_prevhost, from,
E 64
I 64
			(void)strncpy(f->f_lasttime, timestamp, 15);
			(void)strncpy(f->f_prevhost, from,
E 64
					sizeof(f->f_prevhost));
			if (msglen < MAXSVLINE) {
E 34
				f->f_prevlen = msglen;
				f->f_prevpri = pri;
D 64
				(void) strcpy(f->f_prevline, msg);
E 64
I 64
				(void)strcpy(f->f_prevline, msg);
E 64
D 34
				(void) strncpy(f->f_prevhost, from,
					sizeof(f->f_prevhost));
			} else
E 34
I 34
				fprintlog(f, flags, (char *)NULL);
			} else {
E 34
				f->f_prevline[0] = 0;
D 34
			fprintlog(f, flags);
E 34
I 34
				f->f_prevlen = 0;
				fprintlog(f, flags, msg);
			}
E 34
		}
	}
D 64
	(void) sigsetmask(omask);
E 64
I 64
	(void)sigsetmask(omask);
E 64
}
E 32
E 9
D 14
		} else if (flags & SYNC_FILE)
			(void) fsync(f->f_file);
E 7
	}
E 14

I 62
void
E 62
D 14
	/*
	 * Output high priority messages to terminals.
	 */
D 5
	if (pri <= Sumask)
E 5
I 5
D 8
	if (pri >= 0 && pri <= Sumask)
E 8
I 8
D 9
	if (mask(pri) & Sumask)
E 9
I 9
	if (!(flags & ISMARK) && (mask(pri) & Sumask))
E 9
E 8
E 5
D 3
		wallmsg(pri, msg);
E 3
I 3
		wallmsg(pri, msg, from);
I 9

	(void) sigsetmask(omask);
E 9
E 3
}

/*
D 8
 *  INIT -- Initialize syslog from configuration table
E 8
I 8
 *  INIT -- Initialize syslogd from configuration table
E 8
 *
D 8
 *	The configuration table consists of a series of lines
 *	broken into two sections by a blank line.  The first
 *	section gives a list of files to log on.  The first
 *	character is a digit which is the priority mask for
 *	that file.  If the second character is an asterisk, then
 *	syslog arranges for something to be printed every fifteen
 *	minutes (even if only a null line), so that crashes and
 *	other events can be localized.  The rest of the line is
 *	the pathname of the log file.  The second section is
 *	a list of user names; these people are all notified
 *	when subalert messages occur (if they are logged on).
E 8
I 8
 *	The configuration table consists of a series of lines broken
 *	into two sections by a blank line.  The first section gives a
 *	list of files to log on.  Each line begins with a
 *	comma-separated list of digits or ranges of digits (pairs of
 *	digits separated by a dash); if the priority of a message falls
 *	in the set of digits defined by this list, then the message is
 *	logged in the file corresponding to this line.  If the
 *	following character is an asterisk, then syslogd arranges for
 *	something to be printed every fifteen minutes (even if only a
 *	null line), so that crashes and other events can be localized.
 *	The rest of the line is the pathname of the log file.  The
 *	second section is a list of user names; these people are all
 *	notified when subalert messages occur (if they are logged on).
 *	These lines may also have associated priority lists.
E 8
 *
D 8
 *	The configuration table will be reread by this routine
 *	if a signal 1 occurs; for that reason, it is tricky
 *	about not re-opening files and closing files it will
 *	not be using.
E 8
I 8
 *	The configuration table will be reread by this routine if a
 *	SIGHUP signal occurs; for that reason, it is tricky about not
 *	re-opening files and closing files it will not be using.
E 8
 */

init()
{
	register int i;
	register FILE *cf;
	register struct filed *f;
	register char *p;
	char cline[BUFSIZ];
D 8
	struct servent *sp;
E 8
	struct hostent *hp;
	int pmask, flags;
	long now;
I 8
	char *getpmask();
E 8

	dprintf("init\n");

D 9
	/* ignore interrupts during this routine */
	signal(SIGHUP, SIG_IGN);

E 9
I 8
	/* flush any pending output */
	flushmsg();

E 8
	/*
	 *  Close all open log files.
	 */
	for (f = Files; f < &Files[NLOGS]; f++) {
D 5
		if (f->f_file < 0)
E 5
I 5
		if (f->f_file >= 0)
E 5
			(void) close(f->f_file);
		f->f_file = -1;
	}

	/* open the configuration file */
	if ((cf = fopen(ConfFile, "r")) == NULL) {
		dprintf("cannot open %s\n", ConfFile);
		f = Files;
		if ((f->f_file = open(ctty, O_WRONLY)) >= 0) {
			strncpy(f->f_name, ctty, sizeof(f->f_name)-1);
D 8
			f->f_pmask = LOG_CRIT;
E 8
I 8
			f->f_pmask = mask(LOG_CRIT);
E 8
D 5
			f->f_flags = F_TTY|F_MARK;
E 5
I 5
			f->f_flags = F_TTY|F_MARK|F_CONS;
I 8
			untty();
E 8
E 5
		}
		return;
	}

	/*
	 *  Foreach line in the conf table, open that file.
	 */
	f = Files;
D 8
	sp = getservbyname("syslogd", "udp");
E 8
	while (fgets(cline, sizeof cline, cf) != NULL) {
		/* check for end-of-section */
		if (cline[0] == '\n')
E 14
I 14
D 32
		case F_TTY:
		case F_FILE:
			dprintf(" %s\n", f->f_un.f_fname);
			if (f->f_type != F_FILE) {
				v->iov_base = "\r\n";
				v->iov_len = 2;
			} else {
				v->iov_base = "\n";
				v->iov_len = 1;
			}
			if (writev(f->f_file, iov, 6) < 0) {
				int e = errno;
				(void) close(f->f_file);
				/*
				 * Check for EBADF on TTY's due to vhangup() XXX
				 */
				if (e == EBADF && f->f_type != F_FILE) {
					f->f_file = open(f->f_un.f_fname, O_WRONLY|O_APPEND);
					if (f->f_file < 0) {
						f->f_type = F_UNUSED;
						logerror(f->f_un.f_fname);
					}
I 28
					untty();
E 28
				} else {
					f->f_type = F_UNUSED;
					errno = e;
					logerror(f->f_un.f_fname);
				}
			} else if (flags & SYNC_FILE)
				(void) fsync(f->f_file);
E 32
I 32
D 34
fprintlog(f, flags)
E 34
I 34
fprintlog(f, flags, msg)
E 34
D 69
	register struct filed *f;
E 69
I 69
	struct filed *f;
E 69
	int flags;
I 34
	char *msg;
E 34
{
	struct iovec iov[6];
D 49
	register struct iovec *v = iov;
E 49
I 49
D 69
	register struct iovec *v;
E 49
	register int l;
E 69
I 69
	struct iovec *v;
	int l;
E 69
D 49
	char line[MAXLINE + 1];
	char repbuf[80];
E 49
I 49
	char line[MAXLINE + 1], repbuf[80], greetings[200];
E 49

D 49
	v->iov_base = f->f_lasttime;
	v->iov_len = 15;
	v++;
	v->iov_base = " ";
	v->iov_len = 1;
	v++;
E 49
I 49
	v = iov;
	if (f->f_type == F_WALL) {
		v->iov_base = greetings;
		v->iov_len = sprintf(greetings,
		    "\r\n\7Message from syslogd@%s at %.24s ...\r\n",
		    f->f_prevhost, ctime(&now));
		v++;
		v->iov_base = "";
		v->iov_len = 0;
		v++;
	} else {
		v->iov_base = f->f_lasttime;
		v->iov_len = 15;
		v++;
		v->iov_base = " ";
		v->iov_len = 1;
		v++;
	}
E 49
	v->iov_base = f->f_prevhost;
	v->iov_len = strlen(v->iov_base);
	v++;
	v->iov_base = " ";
	v->iov_len = 1;
	v++;
I 49

E 49
D 34
	if (f->f_prevcount > 1) {
E 34
I 34
	if (msg) {
		v->iov_base = msg;
		v->iov_len = strlen(msg);
	} else if (f->f_prevcount > 1) {
E 34
D 49
		(void) sprintf(repbuf, "last message repeated %d times",
		    f->f_prevcount);
E 49
		v->iov_base = repbuf;
D 49
		v->iov_len = strlen(repbuf);
E 49
I 49
		v->iov_len = sprintf(repbuf, "last message repeated %d times",
		    f->f_prevcount);
E 49
	} else {
		v->iov_base = f->f_prevline;
		v->iov_len = f->f_prevlen;
	}
	v++;

	dprintf("Logging to %s", TypeNames[f->f_type]);
	f->f_time = now;

	switch (f->f_type) {
	case F_UNUSED:
		dprintf("\n");
		break;

	case F_FORW:
		dprintf(" %s\n", f->f_un.f_forw.f_hname);
D 49
		(void) sprintf(line, "<%d>%.15s %s", f->f_prevpri,
			iov[0].iov_base, iov[4].iov_base);
		l = strlen(line);
E 49
I 49
		l = sprintf(line, "<%d>%.15s %s", f->f_prevpri,
		    iov[0].iov_base, iov[4].iov_base);
E 49
		if (l > MAXLINE)
			l = MAXLINE;
D 58
		if (sendto(finet, line, l, 0, &f->f_un.f_forw.f_addr,
E 58
I 58
		if (sendto(finet, line, l, 0,
		    (struct sockaddr *)&f->f_un.f_forw.f_addr,
E 58
D 69
		    sizeof f->f_un.f_forw.f_addr) != l) {
E 69
I 69
		    sizeof(f->f_un.f_forw.f_addr)) != l) {
E 69
			int e = errno;
D 64
			(void) close(f->f_file);
E 64
I 64
			(void)close(f->f_file);
E 64
			f->f_type = F_UNUSED;
			errno = e;
			logerror("sendto");
		}
		break;

	case F_CONSOLE:
		if (flags & IGN_CONS) {
			dprintf(" (ignored)\n");
E 32
E 14
			break;
I 32
		}
		/* FALLTHROUGH */
E 32

D 14
		/* strip off newline character */
D 6
		for (p = cline; *p != '\0'; p++)
			if (*p == '\n') {
				*p = '\0';
				break;
			}
E 6
I 6
		p = index(cline, '\n');
		if (p)
			*p = '\0';
E 6

		dprintf("F: got line '%s'\n", cline);

		/* extract priority mask and mark flag */
		p = cline;
		flags = 0;
D 8
		pmask = *p++ - '0';
E 8
I 8
		p = getpmask(p, &pmask);
E 8
		if (*p == '*') {
			p++;
			flags |= F_MARK;
E 14
I 14
D 32
		case F_USERS:
		case F_WALL:
			dprintf("\n");
E 32
I 32
	case F_TTY:
	case F_FILE:
		dprintf(" %s\n", f->f_un.f_fname);
		if (f->f_type != F_FILE) {
E 32
			v->iov_base = "\r\n";
			v->iov_len = 2;
D 32
			wallmsg(f, iov);
			break;
E 32
I 32
		} else {
			v->iov_base = "\n";
			v->iov_len = 1;
E 32
E 14
		}
D 14

		if (f >= &Files[NLOGS])
			continue;

		/* mark entry as used and update flags */
		if (*p == '@') {
I 3
			if (!inet)
				continue;
E 3
			hp = gethostbyname(++p);
D 3
			if (sp != NULL && hp != NULL) {
				bzero(&f->f_addr, sizeof f->f_addr);
				f->f_addr.sin_family = AF_INET;
				f->f_addr.sin_port = sp->s_port;
				bcopy(hp->h_addr, (char *) &f->f_addr.sin_addr, hp->h_length);
				f->f_file = socket(AF_INET, SOCK_DGRAM, 0);
				if (f->f_file < 0) {
					logerror("socket");
					continue;
				}
E 3
I 3
			if (hp == NULL) {
				char buf[100];

				sprintf(buf, "unknown host %s", p);
				errno = 0;
				logerror(buf);
				continue;
E 3
			}
I 3
			bzero(&f->f_addr, sizeof f->f_addr);
			f->f_addr.sin_family = AF_INET;
			f->f_addr.sin_port = port;
			bcopy(hp->h_addr, (char *) &f->f_addr.sin_addr, hp->h_length);
			f->f_file = socket(AF_INET, SOCK_DGRAM, 0);
			if (f->f_file < 0) {
				logerror("socket");
				continue;
			}
E 3
			flags |= F_FORW;
			f->f_pmask = pmask;
			f->f_flags = flags;
D 8
			dprintf("Host %s pmask %d flags %o\n", p, pmask, flags);
E 8
I 8
			dprintf("Host %s pmask %#x flags %#x\n", p, pmask, flags);
E 8
			f++;
			continue;
		}
		strncpy(f->f_name, p, sizeof(f->f_name)-1);
D 5
		if ((f->f_file = open(p, O_WRONLY|O_APPEND)) < 0) {
E 5
I 5
D 9
		if ((f->f_file = open(p, O_WRONLY|O_APPEND|O_NDELAY)) < 0) {
E 9
I 9
		if ((f->f_file = open(p, O_WRONLY|O_APPEND)) < 0) {
E 9
E 5
			logerror(p);
			continue;
		}
D 8
		if (isatty(f->f_file))
E 8
I 8
		if (isatty(f->f_file)) {
E 8
			flags |= F_TTY;
I 8
			untty();
		}
E 8
I 5
		if (strcmp(p, ctty) == 0)
			flags |= F_CONS;
E 5
		f->f_pmask = pmask;
		f->f_flags = flags;
D 8
		dprintf("File %s pmask %d flags %o\n", p, pmask, flags);
E 8
I 8
		dprintf("File %s pmask %#x flags %#x\n", p, pmask, flags);
E 8
		f++;
E 14
D 32
	}
E 32
I 32
	again:
		if (writev(f->f_file, iov, 6) < 0) {
			int e = errno;
D 64
			(void) close(f->f_file);
E 64
I 64
			(void)close(f->f_file);
E 64
			/*
D 51
			 * Check for EBADF on TTY's due to vhangup() XXX
E 51
I 51
			 * Check for errors on TTY's due to loss of tty
E 51
			 */
D 51
			if (e == EBADF && f->f_type != F_FILE) {
E 51
I 51
			if ((e == EIO || e == EBADF) && f->f_type != F_FILE) {
E 51
D 49
				f->f_file = open(f->f_un.f_fname, O_WRONLY|O_APPEND);
E 49
I 49
				f->f_file = open(f->f_un.f_fname,
				    O_WRONLY|O_APPEND, 0);
E 49
				if (f->f_file < 0) {
					f->f_type = F_UNUSED;
					logerror(f->f_un.f_fname);
D 55
				} else {
					untty();
E 55
I 55
				} else
E 55
					goto again;
D 55
				}
E 55
			} else {
				f->f_type = F_UNUSED;
				errno = e;
				logerror(f->f_un.f_fname);
			}
		} else if (flags & SYNC_FILE)
D 64
			(void) fsync(f->f_file);
E 64
I 64
			(void)fsync(f->f_file);
E 64
		break;
E 32

D 14
	/*
	 *  Read the list of users.
	 *
	 *	Anyone in this list is informed directly if s/he
	 *	is logged in when a high priority message comes through.
	 */
I 3
D 8
	Sumask = LOG_SALERT;
E 8
I 8
D 9
	Sumask = mask(LOG_SALERT);
E 9
I 9
D 11
	Sumask = mask(LOG_ALERT);
E 11
I 11
	Sumask = mask(KERN_EMERG)|mask(LOG_EMERG);
E 11
E 9
E 8
E 3
	for (i = 0; i < NSUSERS && fgets(cline, sizeof cline, cf) != NULL; i++) {
		/* strip off newline */
D 6
		for (p = cline; *p != '\0'; p++)
			if (*p == '\n') {
				*p = '\0';
				break;
			}
E 6
I 6
		p = index(cline, '\n');
		if (p)
			*p = '\0';
E 6
		dprintf("U: got line '%s'\n", cline);
		p = cline;
D 9
		if (isdigit(*p)) {
E 9
I 9
		if (isdigit(*p))
E 9
D 8
			Susers[i].s_pmask = pmask = *p++ - '0';
			if (pmask > Sumask)
				Sumask = pmask;
E 8
I 8
			p = getpmask(p, &pmask);
D 9
			Sumask |= pmask;
			Susers[i].s_pmask = pmask;
E 8
		} else
D 3
			Susers[i].s_pmask = LOG_SALERT;
E 3
I 3
D 8
			Susers[i].s_pmask = pmask = LOG_SALERT;
E 8
I 8
			Susers[i].s_pmask = pmask = mask(LOG_SALERT);
E 9
I 9
		else
			pmask = mask(LOG_SALERT);
		Susers[i].s_pmask = pmask;
		Sumask |= pmask;
E 9
E 8
E 3
		strncpy(Susers[i].s_name, p, UNAMESZ);
D 8
		dprintf("Suser %s pmask %d\n", p, pmask);
E 8
I 8
		dprintf("Suser %s pmask %#x\n", p, pmask);
E 8
	}

	/* zero the rest of the old superusers */
	while (i < NSUSERS)
		Susers[i++].s_name[0] = '\0';

	/* close the configuration file */
	(void) fclose(cf);

D 3
	time(&now);
	sprintf(cline, "syslog restarted %s", ctime(&now));
	logmsg(LOG_DEBUG, cline);
E 3
I 3
	dprintf("syslogd: restarted\n");
E 14
I 14
D 32
	(void) sigsetmask(omask);
E 32
I 32
	case F_USERS:
	case F_WALL:
		dprintf("\n");
		v->iov_base = "\r\n";
		v->iov_len = 2;
		wallmsg(f, iov);
		break;
	}
	f->f_prevcount = 0;
E 32
E 14
E 3
D 9

	/* arrange for signal 1 to reconfigure */
	signal(SIGHUP, init);
E 9
}

I 32
D 49
jmp_buf ttybuf;
E 32
I 14

I 32
endtty()
{
	longjmp(ttybuf, 1);
}

E 49
E 32
E 14
/*
 *  WALLMSG -- Write a message to the world at large
 *
 *	Write the specified message to either the entire
 *	world, or a list of approved users.
 */
D 62

E 62
I 62
void
E 62
D 3
wallmsg(pri, msg)
E 3
I 3
D 14
wallmsg(pri, msg, from)
E 3
	int pri;
D 3
	char *msg;
E 3
I 3
	char *msg, *from;
E 14
I 14
wallmsg(f, iov)
D 69
	register struct filed *f;
E 69
I 69
	struct filed *f;
E 69
	struct iovec *iov;
E 14
E 3
{
D 49
	register char *p;
E 49
I 49
	static int reenter;			/* avoid calling ourselves */
D 69
	register FILE *uf;
E 49
	register int i;
E 69
I 69
	FILE *uf;
E 69
D 3
	int f, uf, flags, len, e;
E 3
I 3
D 14
	int f, flags, len, e;
E 14
I 14
D 49
	int ttyf, len;
E 14
	FILE *uf;
I 14
	static int reenter = 0;
E 49
E 14
E 3
	struct utmp ut;
I 69
	int i;
E 69
D 14
	long now;
	char line[MAXLINE + 100];
E 14
I 14
D 32
	time_t now;
E 32
D 49
	char greetings[200];
E 49
I 49
D 62
	char *p, *ttymsg();
E 62
I 62
	char *p;
I 68
	char line[sizeof(ut.ut_line) + 1];
E 68
E 62
E 49
E 14
D 3
	char hbuf[32];
E 3

I 14
	if (reenter++)
		return;
D 49

E 14
	/* open the user login file */
E 49
D 3
	uf = open("/etc/utmp", 0);
	if (uf < 0)
E 3
I 3
D 44
	if ((uf = fopen("/etc/utmp", "r")) == NULL) {
I 9
D 14
		i = Sumask;
		Sumask = 0;
E 14
E 9
		logerror("/etc/utmp");
E 44
I 44
	if ((uf = fopen(_PATH_UTMP, "r")) == NULL) {
D 46
		logerror(_PATH_UTMP);
E 46
I 46
D 52
		/*
D 49
		 * don't log, may not have mounted file systems yet
E 49
I 49
		 * don't log, as may not have mounted file systems yet
E 49
		 * logerror(_PATH_UTMP);
		 */
E 52
I 52
		logerror(_PATH_UTMP);
E 52
E 46
E 44
I 9
D 14
		Sumask = i;
E 14
I 14
		reenter = 0;
E 14
E 9
E 3
		return;
I 3
	}
E 3
D 49

D 14
	time(&now);
D 3
	gethostname(hbuf, sizeof hbuf);
E 3
	sprintf(line,
D 2
	    "\r\n\007Broadcast message from syslog@%s at %.24s ...\r\n%s\r",
E 2
I 2
D 3
	    "\r\n\007Message from syslogd@%s at %.24s ...\r\n%s\r",
E 2
		hbuf, ctime(&now), msg);
E 3
I 3
	    "\r\n\7Message from syslogd@%s at %.24s ...\r\n%s\r\n",
		from, ctime(&now), msg);
E 3
	len = strlen(line);
E 14
I 14
D 32
	(void) time(&now);
	(void) sprintf(greetings,
	    "\r\n\7Message from syslogd@%s at %.24s ...\r\n",
		iov[2].iov_base, ctime(&now));
	len = strlen(greetings);
E 32
I 32
	/*
	 * Might as well fork instead of using nonblocking I/O
	 * and doing notty().
	 */
	if (fork() == 0) {
		(void) signal(SIGTERM, SIG_DFL);
		(void) alarm(0);
		(void) signal(SIGALRM, endtty);
		(void) signal(SIGTTOU, SIG_IGN);
		(void) sigsetmask(0);
		(void) sprintf(greetings,
		    "\r\n\7Message from syslogd@%s at %.24s ...\r\n",
			iov[2].iov_base, ctime(&now));
		len = strlen(greetings);
E 32
E 14

D 32
	/* scan the user login file */
D 3
	while (read(uf, &ut, sizeof ut) == sizeof ut) {
E 3
I 3
D 14
	while (fread(&ut, sizeof ut, 1, uf) == 1) {
E 14
I 14
	while (fread((char *) &ut, sizeof ut, 1, uf) == 1) {
E 14
E 3
		/* is this slot used? */
		if (ut.ut_name[0] == '\0')
			continue;
E 32
I 32
		/* scan the user login file */
		while (fread((char *) &ut, sizeof ut, 1, uf) == 1) {
			/* is this slot used? */
			if (ut.ut_name[0] == '\0')
				continue;
E 32

D 32
		/* should we send the message to this user? */
D 14
		if (pri != LOG_ALERT) {
			for (i = 0; i < NSUSERS; i++) {
D 8
				if (pri > Susers[i].s_pmask)
E 8
I 8
				if ((mask(pri) & Susers[i].s_pmask) == 0)
E 8
					continue;
				if (strncmp(Susers[i].s_name, ut.ut_name,
E 14
I 14
		if (f->f_type == F_USERS) {
			for (i = 0; i < MAXUNAMES; i++) {
				if (!f->f_un.f_uname[i][0]) {
					i = MAXUNAMES;
					break;
E 32
I 32
			/* should we send the message to this user? */
			if (f->f_type == F_USERS) {
				for (i = 0; i < MAXUNAMES; i++) {
					if (!f->f_un.f_uname[i][0]) {
						i = MAXUNAMES;
						break;
					}
					if (strncmp(f->f_un.f_uname[i],
D 48
					    ut.ut_name, UNAMESZ) == 0)
E 48
I 48
					    ut.ut_name, UT_NAMESIZE) == 0)
E 48
						break;
E 32
				}
D 32
				if (strncmp(f->f_un.f_uname[i], ut.ut_name,
E 14
D 9
				    sizeof ut.ut_name) == 0)
E 9
I 9
				    UNAMESZ) == 0)
E 9
D 14
					goto prmsg;
E 14
I 14
					break;
E 32
I 32
				if (i >= MAXUNAMES)
					continue;
E 49
I 49
	/* NOSTRICT */
D 64
	while (fread((char *) &ut, sizeof ut, 1, uf) == 1) {
E 64
I 64
D 69
	while (fread((char *)&ut, sizeof ut, 1, uf) == 1) {
E 69
I 69
	while (fread((char *)&ut, sizeof(ut), 1, uf) == 1) {
E 69
E 64
		if (ut.ut_name[0] == '\0')
			continue;
I 68
		strncpy(line, ut.ut_line, sizeof(ut.ut_line));
		line[sizeof(ut.ut_line)] = '\0';
E 68
		if (f->f_type == F_WALL) {
D 50
			if (p = ttymsg(iov, 6, ut.ut_line, 1))
E 50
I 50
D 59
			if (p = ttymsg(iov, 6, ut.ut_line, 1)) {
E 59
I 59
D 62
			if (p = ttymsg(iov, 6, ut.ut_line, 1, 60*5)) {
E 62
I 62
D 68
			if (p = ttymsg(iov, 6, ut.ut_line, 60*5)) {
E 68
I 68
			if ((p = ttymsg(iov, 6, line, 60*5)) != NULL) {
E 68
E 62
E 59
				errno = 0;	/* already in msg */
E 50
				logerror(p);
I 50
			}
E 50
			continue;
		}
		/* should we send the message to this user? */
		for (i = 0; i < MAXUNAMES; i++) {
			if (!f->f_un.f_uname[i][0])
				break;
			if (!strncmp(f->f_un.f_uname[i], ut.ut_name,
			    UT_NAMESIZE)) {
D 50
				if (p = ttymsg(iov, 6, ut.ut_line, 1))
E 50
I 50
D 59
				if (p = ttymsg(iov, 6, ut.ut_line, 1)) {
E 59
I 59
D 62
				if (p = ttymsg(iov, 6, ut.ut_line, 1, 60*5)) {
E 62
I 62
D 68
				if (p = ttymsg(iov, 6, ut.ut_line, 60*5)) {
E 68
I 68
				if ((p = ttymsg(iov, 6, line, 60*5)) != NULL) {
E 68
E 62
E 59
					errno = 0;	/* already in msg */
E 50
					logerror(p);
I 50
				}
E 50
				break;
E 49
E 32
E 14
			}
D 14
			continue;
E 14
I 14
D 32
			if (i >= MAXUNAMES)
				continue;
E 14
		}
E 32
D 5
		prmsg:
E 5
I 5
D 14
	prmsg:
E 14
E 5
D 49

D 32
		/* compute the device name */
		p = "/dev/12345678";
D 29
		strcpyn(&p[5], ut.ut_line, UNAMESZ);
E 29
I 29
		strncpy(&p[5], ut.ut_line, UNAMESZ);
E 32
I 32
			/* compute the device name */
			p = "/dev/12345678";
D 48
			strncpy(&p[5], ut.ut_line, UNAMESZ);
E 48
I 48
			strncpy(&p[5], ut.ut_line, UT_NAMESIZE);
E 48
E 32
E 29

D 9
		/* open the terminal */
		f = open(p, O_WRONLY|O_NDELAY);
		if (f < 0)
			continue;
D 5
		if ((flags = fcntl(f, F_GETFL, 0)) == -1)
E 5
I 5
		if ((flags = fcntl(f, F_GETFL, 0)) == -1) {
			(void) close(f);
E 5
			continue;
I 5
		}
E 5
		if (fcntl(f, F_SETFL, flags | FNDELAY) == -1)
			goto oldway;
		i = write(f, line, len);
		e = errno;
		(void) fcntl(f, F_SETFL, flags);
		if (i == len || e != EWOULDBLOCK) {
			(void) close(f);
			continue;
		}
	oldway:
E 9
I 9
D 32
		/*
		 * Might as well fork instead of using nonblocking I/O
		 * and doing notty().
		 */
E 9
		if (fork() == 0) {
E 32
D 9
			(void) write(f, line, len);
E 9
I 9
D 14
			signal(SIGALRM, SIG_DFL);
			alarm(30);
E 14
I 14
			if (f->f_type == F_WALL) {
				iov[0].iov_base = greetings;
				iov[0].iov_len = len;
I 21
				iov[1].iov_len = 0;
E 21
			}
D 32
			(void) signal(SIGALRM, SIG_DFL);
			(void) alarm(30);
E 14
			/* open the terminal */
D 14
			f = open(p, O_WRONLY);
			if (f >= 0)
				(void) write(f, line, len);
E 14
I 14
			ttyf = open(p, O_WRONLY);
D 28
			if (ttyf >= 0)
				(void) writev(ttyf, iov, 6);
E 28
I 28
			if (ttyf >= 0) {
				struct stat statb;
E 32
I 32
			if (setjmp(ttybuf) == 0) {
				(void) alarm(15);
				/* open the terminal */
				ttyf = open(p, O_WRONLY);
				if (ttyf >= 0) {
					struct stat statb;
E 32

D 32
				if (fstat(ttyf, &statb) == 0 &&
				    (statb.st_mode & S_IWRITE))
					(void) writev(ttyf, iov, 6);
E 32
I 32
					if (fstat(ttyf, &statb) == 0 &&
					    (statb.st_mode & S_IWRITE))
						(void) writev(ttyf, iov, 6);
					close(ttyf);
					ttyf = -1;
				}
E 32
			}
E 28
E 14
E 9
D 32
			exit(0);
E 32
I 32
			(void) alarm(0);
E 49
E 32
		}
I 32
D 49
		exit(0);
E 49
E 32
I 14
D 21
		/* avoid having them all pile up at once */
		sleep(1);
E 21
E 14
D 9
		(void) close(f);
E 9
	}
D 9

E 9
D 49
	/* close the user login file */
E 49
D 9
	(void) close(uf);
E 9
I 9
D 64
	(void) fclose(uf);
E 64
I 64
	(void)fclose(uf);
E 64
I 14
	reenter = 0;
E 14
E 9
}

I 47
void
E 47
I 9
D 62
reapchild()
E 62
I 62
reapchild(signo)
	int signo;
E 62
{
	union wait status;

D 14
	while (wait3(&status, WNOHANG, 0) > 0)
E 14
I 14
D 58
	while (wait3(&status, WNOHANG, (struct rusage *) NULL) > 0)
E 58
I 58
D 64
	while (wait3((int *)&status, WNOHANG, (struct rusage *) NULL) > 0)
E 64
I 64
	while (wait3((int *)&status, WNOHANG, (struct rusage *)NULL) > 0)
E 64
E 58
E 14
		;
}

E 9
/*
D 14
 * Make sure every marked file gets written to periodically.
 * Reset the alarm clock to call itself after MarkIntvl minutes.
E 14
I 14
 * Return a printable representation of a host address.
E 14
 */
D 14
domark()
{
D 5
	register struct filed *f;
	struct stat stb;
E 5
D 9
	char buf[40];
E 9
I 9
	char buf[50];
E 9
	long now;

	dprintf("domark\n");

	time(&now);
D 5
	for (f = Files; f < &Files[NLOGS]; f++) {
I 2
		if (!(f->f_flags & F_MARK))
			continue;
E 2
		if (f->f_file < 0 || fstat(f->f_file, &stb) < 0)
			continue;
		if (stb.st_mtime >= now - MarkIntvl * 60)
			continue;
D 3
		sprintf(buf, " --- MARK --- %s", ctime(&now));
		logmsg(-1, buf);
E 3
I 3
		sprintf(buf, "syslogd: %.24s-- MARK", ctime(&now));
		logmsg(-1, buf, host);
E 3
	}
E 5
I 5
	sprintf(buf, "syslogd: %.24s-- MARK", ctime(&now));
D 8
	logmsg(-1, buf, host, 0);
E 8
I 8
	flushmsg();
	logmsg(0, buf, host, NOCOPY|ISMARK);
E 8
E 5
	alarm(MarkIntvl * 60);
}

/*
 * Check to see if we should log this message.
 */
chkhost(f)
E 14
I 14
char *
cvthname(f)
E 14
	struct sockaddr_in *f;
{
	struct hostent *hp;
I 21
D 69
	register char *p;
E 69
I 69
	char *p;
E 69
E 21
D 62
	extern char *inet_ntoa();
E 62

D 14
	dprintf("chkhost\n");
E 14
I 14
	dprintf("cvthname(%s)\n", inet_ntoa(f->sin_addr));
E 14

	if (f->sin_family != AF_INET) {
		dprintf("Malformed from address\n");
D 14
		return (0);
E 14
I 14
		return ("???");
E 14
	}
D 58
	hp = gethostbyaddr(&f->sin_addr, sizeof(struct in_addr), f->sin_family);
E 58
I 58
	hp = gethostbyaddr((char *)&f->sin_addr,
	    sizeof(struct in_addr), f->sin_family);
E 58
	if (hp == 0) {
		dprintf("Host name for your address (%s) unknown\n",
			inet_ntoa(f->sin_addr));
D 14
		return (0);
E 14
I 14
		return (inet_ntoa(f->sin_addr));
E 14
	}
I 21
D 69
	if ((p = index(hp->h_name, '.')) && strcmp(p + 1, LocalDomain) == 0)
E 69
I 69
	if ((p = strchr(hp->h_name, '.')) && strcmp(p + 1, LocalDomain) == 0)
E 69
		*p = '\0';
E 21
D 14
	strncpy(rhost, hp->h_name, sizeof rhost);
	return (1);
E 14
I 14
	return (hp->h_name);
E 14
}

I 47
void
E 47
I 21
D 62
domark()
E 62
I 62
domark(signo)
	int signo;
E 62
{
D 32
	int pri;
E 32
I 32
D 69
	register struct filed *f;
E 69
I 69
	struct filed *f;
E 69
I 49
D 62
	time_t time();
E 62
E 49
E 32

D 32
	if ((++MarkSeq % MARKCOUNT) == 0)
E 32
I 32
D 49
	now = time(0);
E 49
I 49
	now = time((time_t *)NULL);
E 49
	MarkSeq += TIMERINTVL;
	if (MarkSeq >= MarkInterval) {
E 32
D 25
		logmsg(LOG_SYSLOG|LOG_INFO, "-- MARK --", LocalHostName, ADDDATE|MARK);
E 25
I 25
		logmsg(LOG_INFO, "-- MARK --", LocalHostName, ADDDATE|MARK);
E 25
D 32
	else
		flushmsg();
	alarm(MarkInterval * 60 / MARKCOUNT);
}
E 32
I 32
		MarkSeq = 0;
	}
E 32

E 21
D 9
/*
I 8
 * Compare current message with previous and return true if match.
 * Side effect is to update the time in the previous message.
 */
match(msg)
	char *msg;
{
	register char *cp;

}

E 9
D 32
flushmsg()
{
D 14
	if (count == 0)
E 14
I 14
	if (PrevCount == 0)
E 14
		return;
D 14
	if (count > 1)
		sprintf(prevdate+18, "last message repeated %d times", count);
I 9
	count = 0;
E 9
	logmsg(prevpri, prevline, prevhost, prevflags|NOCOPY);
	prevline[0] = '\0';
E 14
I 14
	if (PrevCount > 1)
		(void) sprintf(PrevLine+16, "last message repeated %d times", PrevCount);
	PrevCount = 0;
	logmsg(PrevPri, PrevLine, PrevHost, PrevFlags|NOCOPY);
	PrevLine[0] = '\0';
E 32
I 32
	for (f = Files; f; f = f->f_next) {
		if (f->f_prevcount && now >= REPEATTIME(f)) {
			dprintf("flush %s: repeated %d times, %d sec.\n",
			    TypeNames[f->f_type], f->f_prevcount,
			    repeatinterval[f->f_repeatcount]);
D 34
			fprintlog(f, 0);
E 34
I 34
			fprintlog(f, 0, (char *)NULL);
E 34
			BACKOFF(f);
		}
	}
D 64
	(void) alarm(TIMERINTVL);
E 64
I 64
	(void)alarm(TIMERINTVL);
E 64
E 32
E 14
D 9
	count = 0;
E 9
}

/*
E 8
 * Print syslogd errors some place.
 */
I 62
void
E 62
logerror(type)
	char *type;
{
D 48
	char buf[100];
E 48
I 48
D 62
	char buf[100], *strerror();
E 62
I 62
	char buf[100];
E 62
E 48
I 3
D 14
	long now;
E 14
E 3

I 3
D 14
	time(&now);
E 14
E 3
D 48
	if (errno == 0)
D 3
		sprintf(buf, "syslogd: %s\n", type);
E 3
I 3
D 14
		sprintf(buf, "syslogd: %.24s-- %s", ctime(&now), type);
E 14
I 14
		(void) sprintf(buf, "syslogd: %s", type);
E 14
E 3
	else if ((unsigned) errno > sys_nerr)
D 3
		sprintf(buf, "syslogd: %s: error %d\n", type, errno);
E 3
I 3
D 14
		sprintf(buf, "syslogd: %.24s-- %s: error %d",
			ctime(&now), type, errno);
E 14
I 14
		(void) sprintf(buf, "syslogd: %s: error %d", type, errno);
E 48
I 48
	if (errno)
D 62
		(void) sprintf(buf, "syslogd: %s: %s", type, strerror(errno));
E 62
I 62
D 64
		(void) snprintf(buf,
E 64
I 64
		(void)snprintf(buf,
E 64
		    sizeof(buf), "syslogd: %s: %s", type, strerror(errno));
E 62
E 48
E 14
E 3
	else
D 3
		sprintf(buf, "syslogd: %s: %s\n", type, sys_errlist[errno]);
E 3
I 3
D 14
		sprintf(buf, "syslogd: %.24s-- %s: %s",
			ctime(&now), type, sys_errlist[errno]);
E 14
I 14
D 48
		(void) sprintf(buf, "syslogd: %s: %s", type, sys_errlist[errno]);
E 48
I 48
D 62
		(void) sprintf(buf, "syslogd: %s", type);
E 62
I 62
D 64
		(void) snprintf(buf, sizeof(buf), "syslogd: %s", type);
E 64
I 64
		(void)snprintf(buf, sizeof(buf), "syslogd: %s", type);
E 64
E 62
E 48
E 14
E 3
	errno = 0;
D 3
	dprintf(buf);
	logmsg(LOG_ERR, buf);
E 3
I 3
	dprintf("%s\n", buf);
D 5
	logmsg(LOG_ERR, buf, host);
E 5
I 5
D 14
	logmsg(LOG_ERR, buf, host, 0);
E 14
I 14
D 21
	logmsg(LOG_DAEMON|LOG_ERR, buf, LocalHostName, ADDDATE);
E 21
I 21
	logmsg(LOG_SYSLOG|LOG_ERR, buf, LocalHostName, ADDDATE);
E 21
E 14
E 5
E 3
}

I 47
void
E 47
D 14
die()
E 14
I 14
D 62
die(sig)
E 62
I 62
die(signo)
	int signo;
E 62
E 14
{
I 32
D 69
	register struct filed *f;
E 69
I 69
	struct filed *f;
E 69
E 32
I 14
	char buf[100];
E 14
D 3
	logmsg(LOG_DEBUG, "syslog: down\n");
E 3
I 3

I 32
	for (f = Files; f != NULL; f = f->f_next) {
		/* flush any pending output */
		if (f->f_prevcount)
D 34
			fprintlog(f, 0);
E 34
I 34
			fprintlog(f, 0, (char *)NULL);
E 34
	}
E 32
I 14
D 23
	dprintf("syslogd: going down on signal %d\n", sig);
E 14
I 8
	flushmsg();
E 8
D 14
	dprintf("syslogd: going down\n");
E 3
	(void) unlink(logname);
E 14
I 14
	(void) sprintf(buf, "going down on signal %d", sig);
	logerror(buf);
E 23
I 23
D 62
	if (sig) {
D 32
		dprintf("syslogd: going down on signal %d\n", sig);
		flushmsg();
		(void) sprintf(buf, "going down on signal %d", sig);
E 32
I 32
		dprintf("syslogd: exiting on signal %d\n", sig);
		(void) sprintf(buf, "exiting on signal %d", sig);
E 62
I 62
	if (signo) {
		dprintf("syslogd: exiting on signal %d\n", signo);
D 64
		(void) sprintf(buf, "exiting on signal %d", signo);
E 64
I 64
		(void)sprintf(buf, "exiting on signal %d", signo);
E 64
E 62
E 32
I 30
		errno = 0;
E 30
		logerror(buf);
	}
E 23
D 64
	(void) unlink(LogName);
E 64
I 64
	(void)unlink(LogName);
E 64
E 14
	exit(0);
I 8
}

/*
D 14
 * getpmask() parses a string cp looking for a set of numbers like
 * '1-5,8,16' and returns in *ppmask the set of bits represented by
 * these numbers.  A notation '1-5' is interpreted to mean 'turn on
 * bits 1 through 5 inclusive'.  getpmask() returns the address of
 * first byte after the number set.
E 14
I 14
 *  INIT -- Initialize syslogd from configuration table
E 14
 */
D 14
char *
getpmask(cp, ppmask)
	register char *cp;
	unsigned *ppmask;
E 14
I 14
D 62

E 62
I 49
void
E 49
D 62
init()
E 62
I 62
init(signo)
	int signo;
E 62
E 14
{
D 14
	int count1, count2;
E 14
D 69
	register int i;
I 14
	register FILE *cf;
D 32
	register struct filed *f;
E 32
I 32
	register struct filed *f, *next, **nextp;
E 32
	register char *p;
	char cline[BUFSIZ];
E 69
I 69
	int i;
	FILE *cf;
	struct filed *f, *next, **nextp;
	char *p;
	char cline[LINE_MAX];
E 69
E 14

D 14
	*ppmask = 0;
	while (isdigit(*cp)) {
		count1 = count2 = 0;
		do {
			count1 = 10 * count1 + (*cp++ - '0');
		} while (isdigit(*cp));
		switch (*cp) {
		case ',':
			++cp;
			/* FALL THRU */
		default:
			*ppmask |= mask(count1);
E 14
I 14
	dprintf("init\n");

D 32
	/* flush any pending output */
	flushmsg();

E 32
	/*
	 *  Close all open log files.
	 */
I 30
	Initialized = 0;
E 30
D 32
	for (f = Files; f < &Files[NLOGS]; f++) {
E 32
I 32
	for (f = Files; f != NULL; f = next) {
		/* flush any pending output */
		if (f->f_prevcount)
D 34
			fprintlog(f, 0);
E 34
I 34
			fprintlog(f, 0, (char *)NULL);
E 34

E 32
D 26
		if (f->f_type == F_FILE || f->f_type == F_TTY)
E 26
I 26
		switch (f->f_type) {
D 64
		  case F_FILE:
		  case F_TTY:
D 32
		  case F_FORW:
E 32
		  case F_CONSOLE:
I 42
		  case F_FORW:
E 42
E 26
			(void) close(f->f_file);
E 64
I 64
		case F_FILE:
		case F_TTY:
		case F_CONSOLE:
		case F_FORW:
			(void)close(f->f_file);
E 64
D 26
		f->f_type = F_UNUSED;
E 26
I 26
D 32
			f->f_type = F_UNUSED;
E 32
			break;
		}
I 32
		next = f->f_next;
D 64
		free((char *) f);
E 64
I 64
		free((char *)f);
E 64
E 32
E 26
	}
I 32
	Files = NULL;
	nextp = &Files;
E 32

	/* open the configuration file */
	if ((cf = fopen(ConfFile, "r")) == NULL) {
		dprintf("cannot open %s\n", ConfFile);
D 32
		cfline("*.ERR\t/dev/console", &Files[0]);
		cfline("*.PANIC\t*", &Files[1]);
E 32
I 32
		*nextp = (struct filed *)calloc(1, sizeof(*f));
		cfline("*.ERR\t/dev/console", *nextp);
		(*nextp)->f_next = (struct filed *)calloc(1, sizeof(*f));
		cfline("*.PANIC\t*", (*nextp)->f_next);
		Initialized = 1;
E 32
		return;
	}

	/*
	 *  Foreach line in the conf table, open that file.
	 */
D 32
	f = Files;
	while (fgets(cline, sizeof cline, cf) != NULL && f < &Files[NLOGS]) {
E 32
I 32
	f = NULL;
D 69
	while (fgets(cline, sizeof cline, cf) != NULL) {
E 69
I 69
	while (fgets(cline, sizeof(cline), cf) != NULL) {
E 69
E 32
D 35
		/* check for end-of-section */
		if (cline[0] == '\n' || cline[0] == '#')
E 35
I 35
		/*
		 * check for end-of-section, comments, strip off trailing
		 * spaces and newline character.
		 */
D 69
		for (p = cline; isspace(*p); ++p);
E 69
I 69
		for (p = cline; isspace(*p); ++p)
			continue;
E 69
		if (*p == NULL || *p == '#')
E 35
E 14
			continue;
D 35

E 35
I 35
D 69
		for (p = index(cline, '\0'); isspace(*--p););
E 69
I 69
		for (p = strchr(cline, '\0'); isspace(*--p);)
			continue;
E 69
		*++p = '\0';
E 35
I 32
		f = (struct filed *)calloc(1, sizeof(*f));
		*nextp = f;
		nextp = &f->f_next;
E 32
D 14
		case '-':
			while (isdigit(*++cp))
				count2 = 10 * count2 + (*cp - '0');
			for (i = count1; i <= count2; ++i)
				*ppmask |= mask(i);
			if (*cp == ',')
				++cp;
E 14
I 14
D 35
		/* strip off newline character */
		p = index(cline, '\n');
		if (p)
			*p = '\0';

E 35
D 32
		cfline(cline, f++);
E 32
I 32
		cfline(cline, f);
E 32
	}

	/* close the configuration file */
D 64
	(void) fclose(cf);
E 64
I 64
	(void)fclose(cf);
E 64

	Initialized = 1;

	if (Debug) {
D 32
		for (f = Files; f < &Files[NLOGS]; f++) {
E 32
I 32
		for (f = Files; f; f = f->f_next) {
E 32
D 25
			for (i = 0; i < LOG_NFACILITIES; i++)
E 25
I 25
			for (i = 0; i <= LOG_NFACILITIES; i++)
E 25
D 50
				if (f->f_pmask[i] == NOPRI)
E 50
I 50
				if (f->f_pmask[i] == INTERNAL_NOPRI)
E 50
					printf("X ");
				else
					printf("%d ", f->f_pmask[i]);
			printf("%s: ", TypeNames[f->f_type]);
			switch (f->f_type) {
			case F_FILE:
			case F_TTY:
			case F_CONSOLE:
				printf("%s", f->f_un.f_fname);
				break;

			case F_FORW:
				printf("%s", f->f_un.f_forw.f_hname);
				break;

			case F_USERS:
				for (i = 0; i < MAXUNAMES && *f->f_un.f_uname[i]; i++)
					printf("%s, ", f->f_un.f_uname[i]);
				break;
			}
			printf("\n");
		}
	}

D 21
	logmsg(LOG_DAEMON|LOG_INFO, "syslogd: restart", LocalHostName, ADDDATE);
E 21
I 21
	logmsg(LOG_SYSLOG|LOG_INFO, "syslogd: restart", LocalHostName, ADDDATE);
E 21
	dprintf("syslogd: restarted\n");
}

/*
 * Crack a configuration file line
 */
D 62

E 62
I 62
void
E 62
D 50
struct code {
	char	*c_name;
	int	c_val;
};

struct code	PriNames[] = {
	"panic",	LOG_EMERG,
	"emerg",	LOG_EMERG,
	"alert",	LOG_ALERT,
	"crit",		LOG_CRIT,
	"err",		LOG_ERR,
	"error",	LOG_ERR,
	"warn",		LOG_WARNING,
	"warning",	LOG_WARNING,
	"notice",	LOG_NOTICE,
	"info",		LOG_INFO,
	"debug",	LOG_DEBUG,
I 21
	"none",		NOPRI,
E 21
	NULL,		-1
};

struct code	FacNames[] = {
	"kern",		LOG_KERN,
	"user",		LOG_USER,
	"mail",		LOG_MAIL,
I 19
	"daemon",	LOG_DAEMON,
E 19
	"auth",		LOG_AUTH,
	"security",	LOG_AUTH,
I 21
D 25
	"mark",		LOG_SYSLOG,
E 25
I 25
	"mark",		LOG_MARK,
E 25
	"syslog",	LOG_SYSLOG,
I 22
	"lpr",		LOG_LPR,
I 27
	"news",		LOG_NEWS,
I 36
	"uucp",		LOG_UUCP,
E 36
E 27
E 22
E 21
	"local0",	LOG_LOCAL0,
	"local1",	LOG_LOCAL1,
	"local2",	LOG_LOCAL2,
	"local3",	LOG_LOCAL3,
	"local4",	LOG_LOCAL4,
	"local5",	LOG_LOCAL5,
	"local6",	LOG_LOCAL6,
	"local7",	LOG_LOCAL7,
	NULL,		-1
};

E 50
cfline(line, f)
	char *line;
D 69
	register struct filed *f;
E 69
I 69
	struct filed *f;
E 69
{
D 69
	register char *p;
	register char *q;
	register int i;
	char *bp;
	int pri;
E 69
	struct hostent *hp;
I 69
	int i, pri;
	char *bp, *p, *q;
E 69
D 56
	char buf[MAXLINE];
E 56
I 56
	char buf[MAXLINE], ebuf[100];
E 56

	dprintf("cfline(%s)\n", line);
I 30

D 35
	errno = 0;      /* keep sys_errlist stuff out of logerror messages */
E 35
I 35
D 48
	errno = 0;	/* keep sys_errlist stuff out of logerror messages */
E 48
I 48
	errno = 0;	/* keep strerror() stuff out of logerror messages */
E 48
E 35
E 30

	/* clear out file entry */
D 64
	bzero((char *) f, sizeof *f);
E 64
I 64
D 69
	bzero((char *)f, sizeof *f);
E 69
I 69
	memset(f, 0, sizeof(*f));
E 69
E 64
D 25
	for (i = 0; i < LOG_NFACILITIES; i++)
E 25
I 25
	for (i = 0; i <= LOG_NFACILITIES; i++)
E 25
D 50
		f->f_pmask[i] = NOPRI;
E 50
I 50
		f->f_pmask[i] = INTERNAL_NOPRI;
E 50

	/* scan through the list of selectors */
	for (p = line; *p && *p != '\t';) {

		/* find the end of this facility name list */
		for (q = p; *q && *q != '\t' && *q++ != '.'; )
E 14
			continue;
I 14

		/* collect priority name */
D 69
		for (bp = buf; *q && !index("\t,;", *q); )
E 69
I 69
		for (bp = buf; *q && !strchr("\t,;", *q); )
E 69
			*bp++ = *q++;
		*bp = '\0';

		/* skip cruft */
D 69
		while (index(", ;", *q))
E 69
I 69
		while (strchr(", ;", *q))
E 69
			q++;

		/* decode priority name */
D 50
		pri = decode(buf, PriNames);
E 50
I 50
D 56
		pri = decode(buf, prioritynames);
E 50
		if (pri < 0) {
			char xbuf[200];

D 49
			(void) sprintf(xbuf, "unknown priority name \"%s\"", buf);
E 49
I 49
			(void) sprintf(xbuf, "unknown priority name \"%s\"",
			    buf);
E 49
			logerror(xbuf);
			return;
E 56
I 56
		if (*buf == '*')
			pri = LOG_PRIMASK + 1;
		else {
			pri = decode(buf, prioritynames);
			if (pri < 0) {
D 64
				(void) sprintf(ebuf,
E 64
I 64
				(void)sprintf(ebuf,
E 64
				    "unknown priority name \"%s\"", buf);
				logerror(ebuf);
				return;
			}
E 56
E 14
		}
I 14

		/* scan facilities */
D 69
		while (*p && !index("\t.;", *p)) {
D 39
			int i;

E 39
			for (bp = buf; *p && !index("\t,;.", *p); )
E 69
I 69
		while (*p && !strchr("\t.;", *p)) {
			for (bp = buf; *p && !strchr("\t,;.", *p); )
E 69
				*bp++ = *p++;
			*bp = '\0';
			if (*buf == '*')
				for (i = 0; i < LOG_NFACILITIES; i++)
					f->f_pmask[i] = pri;
			else {
D 50
				i = decode(buf, FacNames);
E 50
I 50
				i = decode(buf, facilitynames);
E 50
				if (i < 0) {
D 56
					char xbuf[200];

D 49
					(void) sprintf(xbuf, "unknown facility name \"%s\"", buf);
E 49
I 49
					(void) sprintf(xbuf,
E 56
I 56
D 64
					(void) sprintf(ebuf,
E 64
I 64
					(void)sprintf(ebuf,
E 64
E 56
					    "unknown facility name \"%s\"",
					    buf);
E 49
D 56
					logerror(xbuf);
E 56
I 56
					logerror(ebuf);
E 56
					return;
				}
				f->f_pmask[i >> 3] = pri;
			}
			while (*p == ',' || *p == ' ')
				p++;
		}

		p = q;
E 14
	}

D 14
	return (cp);
E 14
I 14
	/* skip to action part */
	while (*p == '\t')
		p++;

	switch (*p)
	{
	case '@':
		if (!InetInuse)
			break;
D 64
		(void) strcpy(f->f_un.f_forw.f_hname, ++p);
E 64
I 64
		(void)strcpy(f->f_un.f_forw.f_hname, ++p);
E 64
		hp = gethostbyname(p);
		if (hp == NULL) {
D 40
			char buf[100];
E 40
I 40
D 69
			extern int h_errno, h_nerr;
D 60
			extern char **h_errlist;
E 60
I 60
			extern char *h_errlist[];
E 69
I 69
			extern int h_errno;
E 69
E 60
E 40

D 40
			(void) sprintf(buf, "unknown host %s", p);
			errno = 0;
			logerror(buf);
E 40
I 40
D 69
			logerror((u_int)h_errno < h_nerr ?
			    h_errlist[h_errno] : "Unknown error");
E 69
I 69
			logerror(hstrerror(h_errno));
E 69
E 40
			break;
		}
D 64
		bzero((char *) &f->f_un.f_forw.f_addr,
E 64
I 64
D 69
		bzero((char *)&f->f_un.f_forw.f_addr,
E 64
			 sizeof f->f_un.f_forw.f_addr);
E 69
I 69
		memset(&f->f_un.f_forw.f_addr, 0,
			 sizeof(f->f_un.f_forw.f_addr));
E 69
		f->f_un.f_forw.f_addr.sin_family = AF_INET;
		f->f_un.f_forw.f_addr.sin_port = LogPort;
D 64
		bcopy(hp->h_addr, (char *) &f->f_un.f_forw.f_addr.sin_addr, hp->h_length);
E 64
I 64
D 69
		bcopy(hp->h_addr, (char *)&f->f_un.f_forw.f_addr.sin_addr, hp->h_length);
E 69
I 69
		memmove(&f->f_un.f_forw.f_addr.sin_addr, hp->h_addr, hp->h_length);
E 69
E 64
D 32
		f->f_file = socket(AF_INET, SOCK_DGRAM, 0);
		if (f->f_file < 0) {
			logerror("socket");
			break;
		}
E 32
		f->f_type = F_FORW;
		break;

	case '/':
D 64
		(void) strcpy(f->f_un.f_fname, p);
E 64
I 64
		(void)strcpy(f->f_un.f_fname, p);
E 64
D 49
		if ((f->f_file = open(p, O_WRONLY|O_APPEND)) < 0) {
E 49
I 49
		if ((f->f_file = open(p, O_WRONLY|O_APPEND, 0)) < 0) {
E 49
I 35
			f->f_file = F_UNUSED;
E 35
			logerror(p);
			break;
		}
D 55
		if (isatty(f->f_file)) {
E 55
I 55
		if (isatty(f->f_file))
E 55
			f->f_type = F_TTY;
D 55
			untty();
		}
E 55
		else
			f->f_type = F_FILE;
		if (strcmp(p, ctty) == 0)
			f->f_type = F_CONSOLE;
		break;

	case '*':
		f->f_type = F_WALL;
		break;

	default:
		for (i = 0; i < MAXUNAMES && *p; i++) {
			for (q = p; *q && *q != ','; )
				q++;
D 48
			(void) strncpy(f->f_un.f_uname[i], p, UNAMESZ);
			if ((q - p) > UNAMESZ)
				f->f_un.f_uname[i][UNAMESZ] = '\0';
E 48
I 48
D 64
			(void) strncpy(f->f_un.f_uname[i], p, UT_NAMESIZE);
E 64
I 64
			(void)strncpy(f->f_un.f_uname[i], p, UT_NAMESIZE);
E 64
			if ((q - p) > UT_NAMESIZE)
				f->f_un.f_uname[i][UT_NAMESIZE] = '\0';
E 48
			else
				f->f_un.f_uname[i][q - p] = '\0';
			while (*q == ',' || *q == ' ')
				q++;
			p = q;
		}
		f->f_type = F_USERS;
		break;
	}
}


/*
 *  Decode a symbolic name to a numeric value
 */
D 62

E 62
I 62
int
E 62
decode(name, codetab)
D 65
	char *name;
E 65
I 65
	const char *name;
E 65
D 50
	struct code *codetab;
E 50
I 50
	CODE *codetab;
E 50
{
D 50
	register struct code *c;
E 50
I 50
D 69
	register CODE *c;
E 50
	register char *p;
	char buf[40];
E 69
I 69
	CODE *c;
	char *p, buf[40];
E 69

	if (isdigit(*name))
		return (atoi(name));

D 64
	(void) strcpy(buf, name);
E 64
I 64
D 65
	(void)strcpy(buf, name);
E 64
	for (p = buf; *p; p++)
		if (isupper(*p))
			*p = tolower(*p);
E 65
I 65
	for (p = buf; *name && p < &buf[sizeof(buf) - 1]; p++, name++) {
		if (isupper(*name))
			*p = tolower(*name);
		else
			*p = *name;
	}
	*p = '\0';
E 65
	for (c = codetab; c->c_name; c++)
		if (!strcmp(buf, c->c_name))
			return (c->c_val);

	return (-1);
E 14
E 8
}
E 1
