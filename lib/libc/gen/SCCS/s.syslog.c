h36588
s 00001/00001/00208
d D 8.5 95/04/29 10:00:17 bostic 51 50
c Operator precedence bug, "setlogmask(LOG_UPTO(LOG_INFO))" wasn't
c working.
c From: Ted Lemon <mellon@fugue.com>
e
s 00019/00030/00190
d D 8.4 94/03/18 05:46:39 bostic 50 49
c use sprintf() instead of loop counts, for consistency
c From: Craig Leres <leres@ee.lbl.gov>
c KNF, from me
e
s 00004/00001/00216
d D 8.3 94/03/17 07:09:46 eric 49 48
c use __progname (from crt0) as default syslog tag if none specified
e
s 00007/00010/00210
d D 8.2 94/03/17 07:08:45 bostic 48 46
c If you call syslog() with a pointer to ctime()'s static buffer, it gets
c updated by syslog()'s call before copying the stuff out).
c From: Craig Leres <leres@ee.lbl.gov>
c The code contains '(void)sprintf(...)' and (now) '(void)strftime(...)' casts,
c but sprintf() and strftime() both return a character count
c From: Donn Seeley <donn@BSDI.COM>
e
s 00004/00001/00219
d R 8.2 94/02/20 11:41:33 eric 47 46
c use __progname (from crt0) as default syslog tag if none specified
e
s 00002/00002/00218
d D 8.1 93/06/04 12:05:56 bostic 46 45
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00006/00212
d D 5.36 92/10/04 12:54:50 bostic 45 44
c <sys/errno.h> -> <errno.h>
e
s 00013/00005/00205
d D 5.35 92/06/24 12:07:40 bostic 44 43
c the logmask (from setlogmask(3)) and priority masking were wrong
e
s 00003/00003/00207
d D 5.34 91/06/26 18:52:51 mckusick 43 42
c syslog() checks mask set by setlogmask() (4.3BSD-reno/lib/4)
e
s 00032/00008/00178
d D 5.33 91/02/23 19:50:07 donn 42 41
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00001/00185
d D 5.32 90/11/28 00:13:17 bostic 41 40
c make error messages a little better, use constants in unistd.h
e
s 00008/00022/00178
d D 5.31 90/10/29 15:53:36 bostic 40 39
c back out change to return error values
e
s 00006/00004/00194
d D 5.30 90/09/30 20:58:53 bostic 39 38
c return EINVAL if the priority parameter to syslog/vsyslog is bad
e
s 00054/00055/00144
d D 5.29 90/09/30 17:38:03 bostic 38 37
c move _PATH_LOGNAME to <sys/syslog.h>; fix priority bit test
c change all syslog routines to return value, set errno correctly
e
s 00002/00001/00197
d D 5.28 90/06/27 09:59:58 karels 37 36
c off by one when logging to console (was missing \n)
e
s 00001/00011/00197
d D 5.27 90/06/01 14:16:24 bostic 36 35
c new copyright notice
e
s 00001/00001/00207
d D 5.26 90/05/15 19:45:56 bostic 35 34
c string.h is ANSI C include file
e
s 00001/00002/00207
d D 5.25 89/10/28 15:17:44 bostic 34 33
c don't reject based on the facility number, syslogd can if necessary
e
s 00001/00001/00208
d D 5.24 89/08/24 19:54:49 bostic 33 32
c need newline for console, too
e
s 00010/00022/00199
d D 5.23 89/08/04 09:54:38 bostic 32 31
c don't worry about blocking on the console, or about inheriting the
c console as the controlling terminal (fixed in kernel).
e
s 00008/00007/00213
d D 5.22 89/08/02 15:45:20 bostic 31 30
c use waitpid to avoid swallowing children; minor cleanups
e
s 00020/00002/00200
d D 5.21 89/02/15 12:28:40 bostic 30 29
c add LOG_PERROR 
e
s 00001/00000/00201
d D 5.20 89/01/19 15:41:08 bostic 29 28
c end format string, you silly boy!
e
s 00022/00004/00179
d D 5.19 88/12/19 15:56:34 bostic 28 27
c put %m back in
e
s 00010/00001/00173
d D 5.18 88/12/19 14:01:19 bostic 27 26
c add vsyslog
e
s 00043/00082/00131
d D 5.17 88/12/19 13:35:26 bostic 26 25
c some general cleanup; move %m into _doprnt(); handle N arguments;
c increase buffer size to 2K; block all signals when writing to console
e
s 00010/00006/00203
d D 5.16 88/06/27 17:34:15 bostic 25 24
c install approved copyright notice
e
s 00016/00013/00193
d D 5.15 88/05/31 10:49:08 karels 24 23
c use connect instead of sendto (for chrooted programs)
e
s 00001/00001/00205
d D 5.14 88/05/20 17:28:26 karels 23 22
c ... and do it right
e
s 00017/00008/00189
d D 5.13 88/03/24 16:51:28 karels 22 21
c pri 0 is legal; clear facility bits before computing pri mask;
c check for nonsensical values
e
s 00005/00005/00192
d D 5.12 87/10/22 17:45:34 bostic 21 20
c ANSI C; sprintf now returns an int.
e
s 00001/00001/00196
d D 5.11 87/09/30 12:19:50 bostic 20 19
c long/int bug; bug report 4.3BSD/lib/24
e
s 00002/00002/00195
d D 5.10 87/04/20 12:17:30 karels 19 18
c use header macro
e
s 00006/00004/00191
d D 5.9 86/05/07 15:18:41 karels 18 16
c fix problems created by using vfork
e
s 00007/00005/00190
d R 5.9 86/05/07 14:36:48 karels 17 16
c fix problems created by using vfork
e
s 00005/00004/00190
d D 5.8 86/04/24 09:21:47 karels 16 15
c add LOG_NOWAIT, correct console logging
e
s 00004/00003/00190
d D 5.7 86/03/13 20:36:45 karels 15 14
c oops, too much Fortran lately
e
s 00002/00002/00191
d D 5.6 86/03/09 19:59:20 donn 14 13
c added LIBC_SCCS condition for sccs ids
e
s 00003/00002/00190
d D 5.5 86/03/08 20:25:22 karels 13 12
c don't need to print priority on console; s/fork/vfork
e
s 00003/00002/00189
d D 5.4 85/10/13 15:21:46 eric 12 11
c use LOG_NDELAY to \immediately/ open log; LOG_ODELAY is the default
e
s 00005/00000/00186
d D 5.3 85/09/17 22:24:16 eric 11 10
c timeout on attempts to open the console if the log is unavailable
e
s 00034/00021/00152
d D 5.2 85/09/17 18:37:08 eric 10 9
c changes to support facility/level mode of priorities
e
s 00007/00001/00166
d D 5.1 85/05/30 10:51:50 dist 9 8
c Add copyright
e
s 00003/00001/00164
d D 4.7 85/02/20 11:02:26 ralph 8 7
c make the default priority mask ignore kernel priorities.
e
s 00014/00006/00151
d D 4.6 85/02/04 15:16:00 ralph 7 6
c changes for more priorities & added LOG_ODELAY to delay open.
e
s 00010/00010/00147
d D 4.5 84/12/14 14:53:56 ralph 6 5
c changes for more priorities and use mask instead of range.
e
s 00017/00015/00140
d D 4.4 84/08/16 10:11:16 ralph 5 4
c standardize log format, save errno.
e
s 00001/00000/00154
d D 4.3 84/05/04 14:58:15 ralph 4 3
c close socket on exec() since descriptor var is static and gets cleared
e
s 00096/00087/00058
d D 4.2 84/04/25 11:36:33 ralph 3 1
c uses UNIX domain sockets now.
e
s 00002/00000/00145
d R 4.2 83/06/24 00:30:13 sam 2 1
c missing closes on files
e
s 00145/00000/00000
d D 4.1 83/05/27 11:12:45 sam 1 0
c date and time created 83/05/27 11:12:45 by sam
e
u
U
t
T
I 9
/*
D 22
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 22
I 22
D 46
 * Copyright (c) 1983, 1988 Regents of the University of California.
 * All rights reserved.
E 46
I 46
 * Copyright (c) 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 46
 *
D 36
 * Redistribution and use in source and binary forms are permitted
D 25
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 25
I 25
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
E 36
I 36
 * %sccs.include.redist.c%
E 36
E 25
E 22
 */

E 9
I 1
D 14
#ifndef lint
E 14
I 14
#if defined(LIBC_SCCS) && !defined(lint)
E 14
D 5
static char SccsId[] =	"%W% (Berkeley) %G%";
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
D 9
#endif
E 9
I 9
D 14
#endif not lint
E 14
I 14
D 22
#endif LIBC_SCCS and not lint
E 22
I 22
#endif /* LIBC_SCCS and not lint */
E 22
E 14
E 9
D 25

E 25
I 22

E 22
D 38
/*
 * SYSLOG -- print message on log file
 *
D 26
 * This routine looks a lot like printf, except that it
 * outputs to the log file instead of the standard output.
D 3
 * Also, it prints the module name in front of lines,
 * and has some other formatting types (or will sometime).
 * Also, it adds a newline on the end of messages.
E 3
I 3
 * Also:
E 26
I 26
 * This routine looks a lot like printf, except that it outputs to the
 * log file instead of the standard output.  Also:
E 26
 *	adds a timestamp,
 *	prints the module name in front of the message,
 *	has some other formatting types (or will sometime),
 *	adds a newline on the end of the message.
E 3
 *
D 3
 * The output of this routine is intended to be read by
 * /etc/syslog, which will add timestamps.
E 3
I 3
D 26
 * The output of this routine is intended to be read by /etc/syslogd.
E 26
I 26
 * The output of this routine is intended to be read by syslogd(8).
E 26
I 5
 *
 * Author: Eric Allman
 * Modified to use UNIX domain IPC by Ralph Campbell
E 5
E 3
 */
I 3

E 38
E 3
#include <sys/types.h>
#include <sys/socket.h>
D 3
#include <netinet/in.h>

E 3
I 3
D 45
#include <sys/file.h>
E 45
I 11
D 15
#include <signal.h>
E 11
E 3
#include <syslog.h>
E 15
I 15
D 38
#include <sys/signal.h>
E 38
#include <sys/syslog.h>
I 30
#include <sys/uio.h>
I 31
D 38
#include <sys/wait.h>
E 38
I 38
D 45
#include <sys/errno.h>
E 45
E 38
E 31
E 30
E 15
#include <netdb.h>
I 45

#include <errno.h>
#include <fcntl.h>
#include <paths.h>
#include <stdio.h>
E 45
I 15
D 35
#include <strings.h>
E 35
I 35
#include <string.h>
I 45
#include <time.h>
#include <unistd.h>

E 45
I 42
#if __STDC__
#include <stdarg.h>
#else
E 42
E 35
I 27
#include <varargs.h>
I 42
#endif
D 45
#include <time.h>
#include <unistd.h>
E 42
I 31
#include <paths.h>
E 31
E 27
I 26
#include <stdio.h>
E 45
E 26
E 15

D 3
#define	MAXLINE	1024		/* max message size */
#define BUFSLOP	20		/* space to allow for "extra stuff" */
#define NULL	0		/* manifest */
E 3
I 3
D 26
#define	MAXLINE	1024			/* max message size */
#define NULL	0			/* manifest */
E 26
I 26
D 31
#define	LOGNAME	"/dev/log"
#define	CONSOLE	"/dev/console"
E 31
I 31
D 38
#define	_PATH_LOGNAME	"/dev/log"
E 31
E 26
E 3

E 38
I 7
D 10
#define mask(p)	(1 << (p))
#define IMPORTANT (mask(KERN_EMERG)|mask(KERN_ALERT)|mask(KERN_ERR)|mask(KERN_FAIL)\
	|mask(KERN_RECOV)|mask(KERN_INFO)|mask(LOG_EMERG)|mask(LOG_ALERT)\
	|mask(LOG_CRIT)|mask(LOG_ERR)|mask(LOG_FAIL))
E 10
I 10
D 19
#define PRIMASK(p)	(1 << ((p) & LOG_PRIMASK))
E 19
D 24
#define PRIFAC(p)	(((p) & LOG_FACMASK) >> 3)
I 22
					/* XXX should be in <syslog.h> */
E 24
E 22
D 26
#define IMPORTANT 	LOG_ERR
E 10

E 7
D 3
int	LogFile = -1;		/* fd for log */
int	LogStat	= 0;		/* status bits, set by initlog */
char	*LogTag = NULL;		/* string to tag the entry with */
int	LogMask = LOG_DEBUG;	/* lowest priority to be logged */
E 3
I 3
static char	logname[] = "/dev/log";
static char	ctty[] = "/dev/console";
E 3

E 26
D 3
struct sockaddr_in SyslogAddr;
static char *SyslogHost = LOG_HOST;
E 3
I 3
static int	LogFile = -1;		/* fd for log */
I 24
static int	connected;		/* have done connect */
E 24
D 26
static int	LogStat	= 0;		/* status bits, set by openlog() */
E 26
I 26
static int	LogStat = 0;		/* status bits, set by openlog() */
E 26
D 10
static char	*LogTag = NULL;		/* string to tag the entry with */
D 6
static int	LogMask = LOG_DEBUG;	/* lowest priority to be logged */
E 6
I 6
D 8
static int	LogMask = 0xffffffff;	/* mask of priorities to be logged */
E 8
I 8
		    			/* mask of priorities to be logged */
static int	LogMask = ~(mask(KERN_EMERG)|mask(KERN_ALERT)|mask(KERN_ERR)|
		    mask(KERN_FAIL)|mask(KERN_RECOV)|mask(KERN_INFO));
E 10
I 10
D 42
static char	*LogTag = "syslog";	/* string to tag the entry with */
E 42
I 42
D 49
static const char *LogTag = "syslog";	/* string to tag the entry with */
E 49
I 49
static const char *LogTag = NULL;	/* string to tag the entry with */
E 49
E 42
D 26
static int	LogMask = 0xff;		/* mask of priorities to be logged */
E 26
static int	LogFacility = LOG_USER;	/* default facility code */
I 43
static int	LogMask = 0xff;		/* mask of priorities to be logged */
I 49
extern char	*__progname;		/* Program name, from crt0. */
E 49
E 43
E 10
E 8
E 6
E 3

I 38
/*
 * syslog, vsyslog --
 *	print message on log file; output is intended for syslogd(8).
 */
E 38
I 3
D 10
static struct sockaddr SyslogAddr;
E 10
I 10
D 26
static struct sockaddr SyslogAddr;	/* AF_UNIX address of local logger */
E 10

E 3
extern	int errno, sys_nerr;
extern	char *sys_errlist[];

syslog(pri, fmt, p0, p1, p2, p3, p4)
	int pri;
E 26
I 26
D 42
syslog(pri, fmt, args)
	int pri, args;
E 42
I 42
void
#if __STDC__
syslog(int pri, const char *fmt, ...)
#else
syslog(pri, fmt, va_alist)
	int pri;
E 42
E 26
	char *fmt;
I 42
	va_dcl
#endif
E 42
{
I 27
D 38
	vsyslog(pri, fmt, &args);
E 38
I 38
D 40
	return(vsyslog(pri, fmt, &args));
E 40
I 40
D 42
	vsyslog(pri, fmt, &args);
E 42
I 42
	va_list ap;

#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	vsyslog(pri, fmt, ap);
	va_end(ap);
E 42
E 40
E 38
}

I 42
void
E 42
vsyslog(pri, fmt, ap)
	int pri;
D 28
	char *fmt;
E 28
I 28
D 42
	register char *fmt;
E 42
I 42
	register const char *fmt;
E 42
E 28
	va_list ap;
{
I 28
D 38
	extern int errno;
E 38
E 28
E 27
D 3
	char buf[MAXLINE+BUFSLOP], outline[MAXLINE + 1];
	register char *b, *f;
E 3
I 3
D 26
	char buf[MAXLINE + 1], outline[MAXLINE + 1];
	register char *b, *f, *o;
	register int c;
	long now;
D 5
	int pid;
E 5
I 5
	int pid, olderrno = errno;
E 26
I 26
	register int cnt;
D 50
	register char *p;
E 50
I 50
	register char ch, *p, *t;
E 50
D 44
	time_t now, time();
E 44
I 44
	time_t now;
E 44
D 28
	int pid;
	char tbuf[2048], *ctime();
E 28
I 28
D 32
	int pid, saved_errno;
E 32
I 32
	int fd, saved_errno;
E 32
D 30
	char tbuf[2048], fmt_cpy[1024], *ctime();
E 30
I 30
D 44
	char tbuf[2048], fmt_cpy[1024], *stdp, *ctime();
E 44
I 44
	char *stdp, tbuf[2048], fmt_cpy[1024];
E 44
E 30
E 28
E 26
E 5
E 3

I 28
D 39
	saved_errno = errno;
E 39
I 39
D 44
	/* check for invalid bits or no priority set */
D 40
	if (!LOG_PRI(pri) || (pri &~ (LOG_PRIMASK|LOG_FACMASK))) {
		errno = EINVAL;
		return(-1);
	}
E 40
I 40
D 43
	if (!LOG_PRI(pri) || (pri &~ (LOG_PRIMASK|LOG_FACMASK)))
E 43
I 43
	if (!LOG_PRI(pri) || (pri &~ (LOG_PRIMASK|LOG_FACMASK)) ||
	    !(LOG_MASK(pri) & LogMask))
E 44
I 44
#define	INTERNALLOG	LOG_ERR|LOG_CONS|LOG_PERROR|LOG_PID
	/* Check for invalid bits. */
	if (pri & ~(LOG_PRIMASK|LOG_FACMASK)) {
		syslog(INTERNALLOG,
		    "syslog: unknown facility/priority: %x", pri);
		pri &= LOG_PRIMASK|LOG_FACMASK;
	}

	/* Check priority against setlogmask values. */
D 51
	if (!LOG_MASK(LOG_PRI(pri)) & LogMask)
E 51
I 51
	if (!(LOG_MASK(LOG_PRI(pri)) & LogMask))
E 51
E 44
E 43
		return;
E 40
E 39

E 28
D 3
	if (LogFile < 0)
		openlog(0, 0);
E 3
D 38
	/* see if we should just throw out this message */
D 5
	if (pri > LogMask)
E 5
I 5
D 6
	if (pri < LOG_ALERT || pri > LogMask)
E 6
I 6
D 7
	if (pri <= 0 || pri >= 32 || ((1 << pri) & LogMask) == 0)
E 7
I 7
D 10
	if (pri <= 0 || pri >= 32 || (mask(pri) & LogMask) == 0)
E 10
I 10
D 19
	if (pri <= 0 || PRIFAC(pri) >= LOG_NFACILITIES || (PRIMASK(pri) & LogMask) == 0)
E 19
I 19
D 22
	if (pri <= 0 || PRIFAC(pri) >= LOG_NFACILITIES ||
	    (LOG_MASK(pri) & LogMask) == 0)
E 22
I 22
D 24
	if ((unsigned) PRIFAC(pri) >= LOG_NFACILITIES ||
	    (LOG_MASK(pri & LOG_PRIMASK) & LogMask) == 0 ||
E 24
I 24
D 26
	if ((unsigned) LOG_FAC(pri) >= LOG_NFACILITIES ||
	    LOG_MASK(LOG_PRI(pri)) == 0 ||
E 24
D 23
	    (pri &~ (LOG_PRIMASK|LOG_PRIMASK)) != 0)
E 23
I 23
	    (pri &~ (LOG_PRIMASK|LOG_FACMASK)) != 0)
E 26
I 26
D 34
	if ((u_int)LOG_FAC(pri) >= LOG_NFACILITIES ||
	    !LOG_MASK(LOG_PRI(pri)) || (pri &~ (LOG_PRIMASK|LOG_FACMASK)))
E 34
I 34
	if (!LOG_MASK(LOG_PRI(pri)) || (pri &~ (LOG_PRIMASK|LOG_FACMASK)))
E 34
E 26
E 23
E 22
E 19
E 10
E 7
E 6
E 5
		return;
D 3
	for (b = buf, f = fmt; f && *f; b = buf) {
		register char c;
E 3
I 3
D 24
	if (LogFile < 0)
E 24
I 24
	if (LogFile < 0 || !connected)
E 24
D 7
		openlog(NULL, 0, 0);
E 7
I 7
D 12
		openlog(LogTag, LogStat & ~LOG_ODELAY, 0);
E 12
I 12
		openlog(LogTag, LogStat | LOG_NDELAY, 0);
E 38
I 38
D 39
	/* discard if invalid bits or no priority set */
	if (!LOG_PRI(pri) || (pri &~ (LOG_PRIMASK|LOG_FACMASK)))
		return(0);
E 39
I 39
	saved_errno = errno;
E 39
E 38
E 12
I 10

D 50
	/* set default facility if none specified */
E 50
I 50
	/* Set default facility if none specified. */
E 50
	if ((pri & LOG_FACMASK) == 0)
		pri |= LogFacility;

D 50
	/* build the message */
E 50
I 50
	/* Build the message. */
E 50
E 10
E 7
D 26
	o = outline;
D 5
	if (pri > 0) {
		sprintf(o, "<%d>", pri);
		o += strlen(o);
	}
E 5
I 5
D 21
	sprintf(o, "<%d>", pri);
E 21
I 21
	(void)sprintf(o, "<%d>", pri);
E 21
	o += strlen(o);
I 10
	time(&now);
D 21
	sprintf(o, "%.15s ", ctime(&now) + 4);
E 21
I 21
	(void)sprintf(o, "%.15s ", ctime(&now) + 4);
E 21
	o += strlen(o);
E 26
I 26
	(void)time(&now);
D 48
	(void)sprintf(tbuf, "<%d>%.15s ", pri, ctime(&now) + 4);
	for (p = tbuf; *p; ++p);
E 48
I 48
	p = tbuf + sprintf(tbuf, "<%d>", pri);
	p += strftime(p, sizeof (tbuf) - (p - tbuf), "%h %e %T ",
	    localtime(&now));
E 48
I 30
	if (LogStat & LOG_PERROR)
		stdp = p;
I 49
D 50
	if (!LogTag)
E 50
I 50
	if (LogTag == NULL)
E 50
		LogTag = __progname;
E 49
E 30
E 26
E 10
E 5
D 50
	if (LogTag) {
D 26
		strcpy(o, LogTag);
		o += strlen(o);
E 26
I 26
		(void)strcpy(p, LogTag);
		for (; *p; ++p);
E 26
	}
E 50
I 50
	if (LogTag != NULL)
		p += sprintf(p, "%s", LogTag);
E 50
D 48
	if (LogStat & LOG_PID) {
D 5
		sprintf(o, " (%d)", getpid());
E 5
I 5
D 21
		sprintf(o, "[%d]", getpid());
E 21
I 21
D 26
		(void)sprintf(o, "[%d]", getpid());
E 21
E 5
		o += strlen(o);
E 26
I 26
		(void)sprintf(p, "[%d]", getpid());
		for (; *p; ++p);
E 26
	}
E 48
I 48
	if (LogStat & LOG_PID)
		p += sprintf(p, "[%d]", getpid());
E 48
D 10
	time(&now);
D 5
	sprintf(o, " %.15s -- ", ctime(&now) + 4);
E 5
I 5
	sprintf(o, ": %.15s-- ", ctime(&now) + 4);
E 5
	o += strlen(o);
E 10
I 10
D 50
	if (LogTag) {
E 50
I 50
	if (LogTag != NULL) {
E 50
D 26
		strcpy(o, ": ");
		o += 2;
E 26
I 26
		*p++ = ':';
		*p++ = ' ';
E 26
	}
E 10
E 3

D 3
		if (pri > 0 && (LogStat & LOG_COOLIT) == 0) {
			sprintf(b, "<%d>", pri);
			b += strlen(b);
E 3
I 3
D 26
	b = buf;
	f = fmt;
	while ((c = *f++) != '\0' && c != '\n' && b < &buf[MAXLINE]) {
		if (c != '%') {
			*b++ = c;
			continue;
E 3
		}
D 3
		if (LogStat & LOG_PID) {
			sprintf(b, "%d ", getpid());
			b += strlen(b);
E 3
I 3
		if ((c = *f++) != 'm') {
			*b++ = '%';
			*b++ = c;
			continue;
E 3
		}
D 3
		if (LogTag) {
			sprintf(b, "%s: ", LogTag);
			b += strlen(b);
		}
		while ((c = *f++) != '\0' && c != '\n' && b < buf + MAXLINE) {
			if (c != '%') {
				*b++ = c;
				continue;
			}
			c = *f++;
			if (c != 'm') {
				*b++ = '%', *b++ = c, *b++ = '\0';
				continue;
			}
			if ((unsigned)errno > sys_nerr)
				sprintf(b, "error %d", errno);
			else
				strcat(b, sys_errlist[errno]);
			b += strlen(b);
		}
		if (c == '\0')
			f--;
		*b++ = '\n', *b = '\0';
		sprintf(outline, buf, p0, p1, p2, p3, p4);
		errno = 0;
		if (LogStat & LOG_DGRAM)
			(void) sendto(LogFile, outline, strlen(outline), 0,
				   &SyslogAddr, sizeof SyslogAddr);
E 3
I 3
D 5
		if ((unsigned)errno > sys_nerr)
			sprintf(b, "error %d", errno);
E 5
I 5
		if ((unsigned)olderrno > sys_nerr)
D 21
			sprintf(b, "error %d", olderrno);
E 21
I 21
			(void)sprintf(b, "error %d", olderrno);
E 21
E 5
E 3
		else
D 3
			(void) write(LogFile, outline, strlen(outline));
		if (errno)
			perror("syslog: sendto");
E 3
I 3
D 5
			strcpy(b, sys_errlist[errno]);
E 5
I 5
			strcpy(b, sys_errlist[olderrno]);
E 5
		b += strlen(b);
E 3
	}
I 3
	*b++ = '\n';
	*b = '\0';
D 21
	sprintf(o, buf, p0, p1, p2, p3, p4);
E 21
I 21
	(void)sprintf(o, buf, p0, p1, p2, p3, p4);
E 21
	c = strlen(outline);
	if (c > MAXLINE)
		c = MAXLINE;
E 26
I 26
D 27
	(void)vsprintf(p, fmt, &args);
E 27
I 27
D 28
	(void)vsprintf(p, fmt, ap);
E 28
I 28
D 50
	/* substitute error message for %m */
	{
		register char ch, *t1, *t2;
E 50
I 50
	/* Substitute error message for %m. */
	for (t = fmt_cpy; ch = *fmt; ++fmt)
		if (ch == '%' && fmt[1] == 'm') {
			++fmt;
			t += sprintf(t, "%s", strerror(saved_errno));
		} else
			*t++ = ch;
	*t = '\0';
E 50
D 48
		char *strerror();
E 48

D 50
		for (t1 = fmt_cpy; ch = *fmt; ++fmt)
			if (ch == '%' && fmt[1] == 'm') {
				++fmt;
				for (t2 = strerror(saved_errno);
				    *t1 = *t2++; ++t1);
			}
			else
				*t1++ = ch;
I 29
		*t1 = '\0';
E 29
	}

E 50
D 48
	(void)vsprintf(p, fmt_cpy, ap);
E 28
E 27
E 26
I 10

I 30
	cnt = strlen(tbuf);
E 48
I 48
	p += vsprintf(p, fmt_cpy, ap);
	cnt = p - tbuf;
E 48

D 50
	/* output to stderr if requested */
E 50
I 50
	/* Output to stderr if requested. */
E 50
	if (LogStat & LOG_PERROR) {
		struct iovec iov[2];
		register struct iovec *v = iov;

		v->iov_base = stdp;
		v->iov_len = cnt - (stdp - tbuf);
		++v;
		v->iov_base = "\n";
		v->iov_len = 1;
D 41
		(void)writev(2, iov, 2);
E 41
I 41
		(void)writev(STDERR_FILENO, iov, 2);
E 41
	}

E 30
D 38
	/* output the message to the local logger */
E 10
D 24
	if (sendto(LogFile, outline, c, 0, &SyslogAddr, sizeof SyslogAddr) >= 0)
E 24
I 24
D 26
	if (send(LogFile, outline, c, 0) >= 0)
E 26
I 26
D 30
	if (send(LogFile, tbuf, cnt = strlen(tbuf), 0) >= 0 ||
E 30
I 30
D 31
	if (send(LogFile, tbuf, cnt, 0) >= 0 ||
E 30
	    !(LogStat&LOG_CONS))
E 31
I 31
	if (send(LogFile, tbuf, cnt, 0) >= 0 || !(LogStat&LOG_CONS))
E 31
E 26
E 24
		return;
E 38
I 38
D 50
	/* get connected, output the message to the local logger */
E 50
I 50
	/* Get connected, output the message to the local logger. */
E 50
D 42
	if ((connected || !openlog(LogTag, LogStat | LOG_NDELAY, 0)) &&
	    send(LogFile, tbuf, cnt, 0) >= 0)
E 42
I 42
	if (!connected)
		openlog(LogTag, LogStat | LOG_NDELAY, 0);
	if (send(LogFile, tbuf, cnt, 0) >= 0)
E 42
D 40
		return(0);
E 40
I 40
		return;
E 40
E 38
D 7
	if (pri > LOG_CRIT)
E 7
I 7
D 10
	if (!(LogStat & LOG_CONS) && !(mask(pri) & IMPORTANT))
E 10
I 10
D 16
	if (!(LogStat & LOG_CONS) && (pri & LOG_PRIMASK) <= LOG_ERR)
E 16
I 16
D 26
	if (!(LogStat & LOG_CONS))
E 16
E 10
E 7
		return;
E 26
I 10

I 38
D 50
	/* see if should attempt the console */
	if (!(LogStat&LOG_CONS))
D 40
		return(-1);
E 40
I 40
		return;
E 40

E 50
E 38
D 32
	/* output the message to the console */
E 10
D 13
	pid = fork();
E 13
I 13
	pid = vfork();
E 13
	if (pid == -1)
E 32
I 32
	/*
D 38
	 * output the message to the console; don't worry about
	 * blocking, if console blocks everything will.
E 38
I 38
	 * Output the message to the console; don't worry about blocking,
	 * if console blocks everything will.  Make sure the error reported
	 * is the one from the syslogd failure.
E 38
	 */
D 38
	if ((fd = open(_PATH_CONSOLE, O_WRONLY, 0)) < 0)
E 32
		return;
D 32
	if (pid == 0) {
I 18
		int fd;
I 26
		long sigsetmask();
E 26

E 18
I 11
D 26
		signal(SIGALRM, SIG_DFL);
D 20
		sigsetmask(sigblock(0) & ~sigmask(SIGALRM));
E 20
I 20
		sigsetmask(sigblock(0L) & ~sigmask(SIGALRM));
E 20
		alarm(5);
E 11
D 10
		LogFile = open(ctty, O_RDWR);
E 10
I 10
D 18
		LogFile = open(ctty, O_WRONLY);
E 18
I 18
		fd = open(ctty, O_WRONLY);
E 18
I 11
		alarm(0);
E 11
E 10
D 7
		write(LogFile, outline, c);
E 7
I 7
		strcat(o, "\r");
D 13
		write(LogFile, outline, c+1);
E 13
I 13
D 15
		o = outline + index(outline, '>') + 1;
E 15
I 15
		o = index(outline, '>') + 1;
E 15
D 16
		write(LogFile, outline, c + 1 - (o - outline));
E 16
I 16
D 18
		write(LogFile, o, c + 1 - (o - outline));
E 16
E 13
E 7
		close(LogFile);
		exit(0);
E 18
I 18
		write(fd, o, c + 1 - (o - outline));
		close(fd);
E 26
I 26
		(void)signal(SIGALRM, SIG_DFL);
		sigsetmask((long)~sigmask(SIGALRM));
		(void)alarm((u_int)5);
D 31
		if ((fd = open(CONSOLE, O_WRONLY, 0)) < 0)
E 31
I 31
		if ((fd = open(_PATH_CONSOLE, O_WRONLY, 0)) < 0)
E 31
			return;
		(void)alarm((u_int)0);
		(void)strcat(tbuf, "\r");
		p = index(tbuf, '>') + 1;
		(void)write(fd, p, cnt + 1 - (p - tbuf));
		(void)close(fd);
E 26
		_exit(0);
E 18
	}
D 5
	while (wait((int *)0) != pid)
E 5
I 5
D 16
	while ((c = wait((int *)0)) > 0 && c != pid)
E 5
		;
E 16
I 16
	if (!(LogStat & LOG_NOWAIT))
D 26
		while ((c = wait((int *)0)) > 0 && c != pid)
			;
E 26
I 26
D 31
		while ((cnt = wait((int *)0)) > 0 && cnt != pid);
E 31
I 31
		(void)waitpid(pid, (union wait *)NULL, WSIGRESTART);
E 32
I 32
D 33
	(void)strcat(tbuf, "\r");
E 33
I 33
	(void)strcat(tbuf, "\r\n");
I 37
	cnt += 2;
E 37
E 33
	p = index(tbuf, '>') + 1;
D 37
	(void)write(fd, p, cnt + 1 - (p - tbuf));
E 37
I 37
	(void)write(fd, p, cnt - (p - tbuf));
E 37
	(void)close(fd);
E 38
I 38
D 40
	saved_errno = errno;
E 40
D 50
	if ((fd = open(_PATH_CONSOLE, O_WRONLY, 0)) >= 0) {
E 50
I 50
	if (LogStat & LOG_CONS &&
	    (fd = open(_PATH_CONSOLE, O_WRONLY, 0)) >= 0) {
E 50
		(void)strcat(tbuf, "\r\n");
		cnt += 2;
		p = index(tbuf, '>') + 1;
		(void)write(fd, p, cnt - (p - tbuf));
		(void)close(fd);
D 40
	} else
		errno = saved_errno;
	return(-1);
E 40
I 40
	}
E 40
E 38
E 32
E 31
E 26
E 16
E 3
}

I 26
static struct sockaddr SyslogAddr;	/* AF_UNIX address of local logger */
E 26
D 38
/*
 * OPENLOG -- open system log
 */
E 38
I 38

I 42
void
E 42
E 38
D 3
openlog(ident, logstat)
E 3
I 3
D 10
openlog(ident, logstat, logmask)
E 10
I 10
D 26

E 26
openlog(ident, logstat, logfac)
E 10
E 3
D 42
	char *ident;
E 42
I 42
	const char *ident;
E 42
D 3
	int logstat;
E 3
I 3
D 10
	int logstat, logmask;
E 10
I 10
	int logstat, logfac;
E 10
E 3
{
I 38
D 40
	int saved_errno;

E 40
E 38
D 3
	struct servent *sp;
	struct hostent *hp;
E 3
D 10

D 5
	LogTag = ident;
E 5
I 5
	LogTag = (ident != NULL) ? ident : "syslog";
E 10
I 10
	if (ident != NULL)
		LogTag = ident;
E 10
E 5
	LogStat = logstat;
I 3
D 6
	if (logmask > 0 && logmask <= LOG_DEBUG)
E 6
I 6
D 10
	if (logmask != 0)
E 6
		LogMask = logmask;
E 10
I 10
D 22
	if (logfac != 0)
		LogFacility = logfac & LOG_FACMASK;
E 22
I 22
	if (logfac != 0 && (logfac &~ LOG_FACMASK) == 0)
		LogFacility = logfac;
I 38

E 38
E 22
E 10
E 3
D 24
	if (LogFile >= 0)
		return;
D 3
	sp = getservbyname("syslog", "udp");
	hp = gethostbyname(SyslogHost);
	if (sp == NULL || hp == NULL)
		goto bad;
	LogFile = socket(AF_INET, SOCK_DGRAM, 0);
	if (LogFile < 0) {
		perror("syslog: socket");
		goto bad;
	}
	bzero(&SyslogAddr, sizeof SyslogAddr);
	SyslogAddr.sin_family = hp->h_addrtype;
	bcopy(hp->h_addr, (char *)&SyslogAddr.sin_addr, hp->h_length);
	SyslogAddr.sin_port = sp->s_port;
	LogStat |= LOG_DGRAM;
	return;
bad:
	LogStat |= LOG_COOLIT;
	LogStat &= ~LOG_DGRAM;
	LogMask = LOG_CRIT;
	LogFile = open("/dev/console", 1);
	if (LogFile < 0) {
		perror("syslog: /dev/console");
		LogFile = 2;
	}
E 3
I 3
	SyslogAddr.sa_family = AF_UNIX;
	strncpy(SyslogAddr.sa_data, logname, sizeof SyslogAddr.sa_data);
D 7
	LogFile = socket(AF_UNIX, SOCK_DGRAM, 0);
I 4
	fcntl(LogFile, F_SETFD, 1);
E 7
I 7
D 12
	if (!(LogStat & LOG_ODELAY)) {
E 12
I 12
	if (LogStat & LOG_NDELAY) {
E 12
		LogFile = socket(AF_UNIX, SOCK_DGRAM, 0);
		fcntl(LogFile, F_SETFD, 1);
E 24
I 24
	if (LogFile == -1) {
		SyslogAddr.sa_family = AF_UNIX;
D 26
		strncpy(SyslogAddr.sa_data, logname, sizeof SyslogAddr.sa_data);
E 26
I 26
D 31
		strncpy(SyslogAddr.sa_data, LOGNAME, sizeof SyslogAddr.sa_data);
E 31
I 31
D 38
		strncpy(SyslogAddr.sa_data, _PATH_LOGNAME,
E 38
I 38
		(void)strncpy(SyslogAddr.sa_data, _PATH_LOG,
E 38
		    sizeof(SyslogAddr.sa_data));
E 31
E 26
		if (LogStat & LOG_NDELAY) {
D 38
			LogFile = socket(AF_UNIX, SOCK_DGRAM, 0);
			fcntl(LogFile, F_SETFD, 1);
E 38
I 38
			if ((LogFile = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1)
D 40
				return(-1);
E 40
I 40
				return;
E 40
			(void)fcntl(LogFile, F_SETFD, 1);
E 38
		}
E 24
	}
I 24
D 38
	if (LogFile != -1 && !connected &&
	    connect(LogFile, &SyslogAddr, sizeof(SyslogAddr)) != -1)
		connected = 1;
E 38
I 38
	if (LogFile != -1 && !connected)
		if (connect(LogFile, &SyslogAddr, sizeof(SyslogAddr)) == -1) {
D 40
			saved_errno = errno;
E 40
			(void)close(LogFile);
D 40
			errno = saved_errno;
E 40
			LogFile = -1;
D 40
			return(-1);
E 40
		} else
			connected = 1;
D 40
	return(0);
E 40
E 38
E 24
E 7
E 4
E 3
}

I 42
void
E 42
D 38
/*
 * CLOSELOG -- close the system log
 */
E 38
I 12
D 26

E 26
E 12
closelog()
{
D 26

E 26
D 38
	(void) close(LogFile);
E 38
I 38
D 40
	int rval;

	rval = close(LogFile);
E 40
I 40
	(void)close(LogFile);
E 40
E 38
	LogFile = -1;
I 24
	connected = 0;
I 38
D 40
	return(rval);
E 40
E 38
E 24
I 3
}
D 43

I 26
static int	LogMask = 0xff;		/* mask of priorities to be logged */
E 43
E 26
D 38
/*
 * SETLOGMASK -- set the log mask level
 */
E 38
I 38

/* setlogmask -- set the log mask level */
I 44
int
E 44
E 38
D 6
setlogmask(pri)
	int pri;
E 6
I 6
setlogmask(pmask)
	int pmask;
E 6
{
D 6
	int opri;
E 6
I 6
	int omask;
E 6

D 6
	opri = LogMask;
D 5
	LogMask = pri;
E 5
I 5
	if (pri > 0 && pri <= LOG_DEBUG)
		LogMask = pri;
E 5
	return (opri);
E 6
I 6
	omask = LogMask;
	if (pmask != 0)
		LogMask = pmask;
	return (omask);
E 6
E 3
}
E 1
