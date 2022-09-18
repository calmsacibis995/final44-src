h11046
s 00002/00002/00159
d D 8.1 93/06/02 19:55:39 bostic 38 37
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00160
d D 7.24 92/11/06 09:01:31 bostic 37 36
c typo
e
s 00002/00000/00159
d D 7.23 92/06/24 12:15:00 bostic 36 35
c add LOG_FTP facility
e
s 00001/00001/00158
d D 7.22 92/06/22 21:42:17 bostic 35 34
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00009/00002/00150
d D 7.21 92/02/21 14:40:17 bostic 34 33
c vsyslog prototype can't use va_list
e
s 00001/00001/00151
d D 7.20 91/02/23 19:08:41 donn 33 32
c Get the return type right for setlogmask().
e
s 00001/00001/00151
d D 7.19 91/02/22 14:01:18 bostic 32 31
c use stdarg, not varargs
e
s 00015/00000/00137
d D 7.18 91/02/22 11:59:52 donn 31 30
c Prototype declarations.
e
s 00005/00000/00132
d D 7.17 90/09/29 11:58:00 bostic 30 29
c add _PATH_LOG (syslogd and syslog(3) used it); add LOG_AUTHPRIV
e
s 00001/00011/00131
d D 7.16 90/06/28 22:01:02 bostic 29 28
c new copyright notice
e
s 00098/00044/00044
d D 7.15 89/11/13 18:39:20 bostic 28 27
c reorder and comment facilities/priorities defines; move string names
c out of syslogd/logger so they get updated.  Should probably be read out of a
c configuration file.
e
s 00002/00002/00086
d D 7.14 89/08/22 14:49:08 bostic 27 26
c deprecate LOG_NOWAIT
e
s 00001/00000/00087
d D 7.13 89/02/15 12:06:30 bostic 26 25
c add LOG_PERROR
e
s 00001/00001/00086
d D 7.12 88/12/21 18:34:35 bostic 25 24
c spelling is important
e
s 00001/00000/00086
d D 7.11 88/12/12 10:03:17 bostic 24 23
c add crontab entry
e
s 00010/00005/00076
d D 7.10 88/06/27 18:42:06 bostic 23 22
c install approved copyright notice
e
s 00009/00003/00072
d D 7.9 88/06/06 09:42:01 bostic 22 21
c add Berkeley specific header
e
s 00009/00000/00066
d D 7.8 88/05/26 09:02:23 karels 21 20
c add FAC, PRI, MAKEPRI macros; add LOG_PRINTF for diskerr
e
s 00000/00000/00066
d D 7.7 87/04/20 12:13:05 karels 20 19
x 19
c put back "obsolete cruft" again! (eric: don't delete it this time,
c routed was broken by your change!  logmask takes a mask, not a pri.)
e
s 00000/00000/00060
d D 7.6 86/11/24 19:20:51 eric 19 18
x 18
c no it isn't.... routed was broken.  Honest!
e
s 00006/00000/00060
d D 7.5 86/11/15 17:19:54 sam 18 17
c put back "obsolete cruft" -- it's used
e
s 00001/00000/00059
d D 7.4 86/11/13 18:15:18 eric 17 16
c add facility for UUCP
e
s 00001/00007/00058
d D 7.3 86/11/12 19:21:57 eric 16 15
c remove obsolete cruft
e
s 00001/00000/00064
d D 7.2 86/10/23 16:49:54 eric 15 14
c add network news subsystem facility
e
s 00001/00001/00063
d D 7.1 86/06/04 23:28:36 mckusick 14 13
c 4.3BSD release version
e
s 00001/00001/00063
d D 4.12 86/03/28 14:59:21 karels 13 12
c priorities, priorities
e
s 00005/00004/00059
d D 4.11 86/03/21 10:48:40 karels 12 11
c add LOG_NOWAIT
e
s 00007/00001/00056
d D 4.10 86/02/16 20:42:33 karels 11 10
c macros for masks
e
s 00001/00000/00056
d D 4.9 85/11/17 11:32:02 eric 10 9
c add LOG_LPR facility
e
s 00004/00000/00052
d D 4.8 85/10/13 15:20:29 eric 9 8
c add LOG_NDELAY
e
s 00002/00001/00050
d D 4.7 85/10/12 23:07:04 eric 8 7
c added LOG_SYSLOG facility for internally generated messages
e
s 00029/00039/00022
d D 4.6 85/09/17 18:02:35 eric 7 6
c extensive mods to add facilities
e
s 00007/00001/00054
d D 4.5 85/06/08 15:08:47 mckusick 6 5
c Add copyright
e
s 00001/00001/00054
d D 4.4 85/02/25 14:39:45 karels 5 4
c LOG_WARN -> LOG_WARNING
e
s 00044/00046/00011
d D 4.3 85/01/31 17:01:21 ralph 4 2
c added kernel priorities, range is now 1 - 31.
e
s 00001/00000/00057
d R 4.3 84/05/04 14:28:11 ralph 3 2
c added LOG_STAYOPEN flag to keep socket open after execve(2).
e
s 00002/00018/00055
d D 4.2 84/04/25 11:43:21 ralph 2 1
c version for UNIX domain sockets
e
s 00073/00000/00000
d D 4.1 83/05/27 11:11:47 sam 1 0
c date and time created 83/05/27 11:11:47 by sam
e
u
U
t
T
I 1
D 6
/*	%M%	%I%	%E%	*/
E 6
I 6
/*
D 14
 * Copyright (c) 1982 Regents of the University of California.
E 14
I 14
D 22
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 14
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 22
I 22
D 38
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.
E 38
I 38
 * Copyright (c) 1982, 1986, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 38
 *
D 29
 * Redistribution and use in source and binary forms are permitted
D 23
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 23
I 23
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 27
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 27
I 27
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 29
I 29
 * %sccs.include.redist.c%
E 29
E 27
E 23
E 22
 *
 *	%W% (Berkeley) %G%
 */
E 6

I 30
#define	_PATH_LOG	"/dev/log"

E 30
/*
D 4
 *  SYSLOG.H -- declarations for system logging program
E 4
I 4
D 7
 *  Declarations for system logging program
E 4
 *
D 4
 *	These are used as the first parameter to logmsg().
 *	Their meanings are approximately as follows:
 *
 *	LOG_ALERT -- this priority should essentially never
 *		be used.  It applies only to messages that
 *		are so important that every user should be
 *		aware of them, e.g., a serious hardware failure.
 *	LOG_SALERT -- messages of this priority should be
 *		issued only when immediate attention is needed
 *		by a qualified system person, e.g., when some
 *		valuable system resource dissappears.  They get
 *		sent to a list of system people.
 *	LOG_EMERG -- Emergency messages are not sent to users,
 *		but represent major conditions.  An example
 *		might be hard disk failures.  These could be
 *		logged in a separate file so that critical
 *		conditions could be easily scanned.
 *	LOG_ERR -- these represent error conditions, such as soft
 *		disk failures, etc.
 *	LOG_CRIT -- such messages contain critical information,
 *		but which can not be classed as errors, for example,
 *		'su' attempts.
 *	LOG_WARNING -- issued when an abnormal condition has been
 *		detected, but recovery can take place.
 *	LOG_NOTICE -- something that falls in the class of
 *		"important information"; this class is informational
 *		but important enough that you don't want to throw
 *		it away casually.
 *	LOG_INFO -- information level messages.  These messages
 *		could be thrown away without problems, but should
 *		be included if you want to keep a close watch on
 *		your system.
 *	LOG_DEBUG -- it may be useful to log certain debugging
 *		information.  Normally this will be thrown away.
E 4
I 4
 *	These are used as the first parameter to syslog().
E 7
I 7
D 28
 *  Facility codes
E 28
I 28
 * priorities/facilities are encoded into a single 32-bit quantity, where the
 * bottom 3 bits are the priority (0-7) and the top 28 bits are the facility
 * (0-big number).  Both the priorities and the facilities map roughly
 * one-to-one to strings in the syslogd(8) source code.  This mapping is
 * included in this file.
 *
 * priorities (these are ordered)
E 28
E 7
E 4
 */
I 28
#define	LOG_EMERG	0	/* system is unusable */
#define	LOG_ALERT	1	/* action must be taken immediately */
#define	LOG_CRIT	2	/* critical conditions */
#define	LOG_ERR		3	/* error conditions */
#define	LOG_WARNING	4	/* warning conditions */
#define	LOG_NOTICE	5	/* normal but significant condition */
#define	LOG_INFO	6	/* informational */
#define	LOG_DEBUG	7	/* debug-level messages */
E 28

D 2
/* some configuration parameters..... */
#define LOG_IPC				/* set if using 4.2 IPC, else mpx */
#define LOG_HOST 	"localhost"	/* name of host to log on */

E 2
D 4
/* defines for priorities */
#define	LOG_ALERT	1	/* alert -- send to all users */
#define	LOG_SALERT	2	/* subalert -- send to special users */
#define	LOG_EMERG	3	/* emergency conditions */
#define	LOG_ERROR	4	/* error */
#define	LOG_ERR		4	/* synonym of LOG_ERROR */
#define	LOG_CRIT	5	/* critical information */
#define	LOG_WARNING	6	/* warning */
#define	LOG_NOTICE	7	/* important information */
#define	LOG_INFO	8	/* informational message */
#define	LOG_DEBUG	9	/* debug level info */
E 4
I 4
D 7
	/* kernel priorities */
#define	KERN_EMERG	1	/* emergency -- send to all users (wall) */
#define	KERN_ALERT	2	/* alert -- system failure */
#define	KERN_ERR	3	/* hard errors */
#define	KERN_FAIL	4	/* table full/overflow */
#define	KERN_RECOV	5	/* recoverable errors (softecc) */
#define	KERN_INFO	6	/* inconsistency/configuration error */
E 7
I 7
D 28
#define LOG_KERN	(0<<3)	/* kernel messages */
#define LOG_USER	(1<<3)	/* random user-level messages */
#define LOG_MAIL	(2<<3)	/* mail system */
#define LOG_DAEMON	(3<<3)	/* system daemons */
#define LOG_AUTH	(4<<3)	/* security/authorization messages */
D 8
	/* codes 5 - 15 reserved for system use */
E 8
I 8
#define LOG_SYSLOG	(5<<3)	/* messages generated internally by syslogd */
I 10
#define LOG_LPR		(6<<3)	/* line printer subsystem */
I 15
#define LOG_NEWS	(7<<3)	/* network news subsystem */
I 17
#define LOG_UUCP	(8<<3)	/* UUCP subsystem */
I 24
#define LOG_CRON	(9<<3)	/* clock daemon */
E 24
E 17
E 15
E 10
	/* other codes through 15 reserved for system use */
E 8
#define LOG_LOCAL0	(16<<3)	/* reserved for local use */
#define LOG_LOCAL1	(17<<3)	/* reserved for local use */
#define LOG_LOCAL2	(18<<3)	/* reserved for local use */
#define LOG_LOCAL3	(19<<3)	/* reserved for local use */
#define LOG_LOCAL4	(20<<3)	/* reserved for local use */
#define LOG_LOCAL5	(21<<3)	/* reserved for local use */
#define LOG_LOCAL6	(22<<3)	/* reserved for local use */
#define LOG_LOCAL7	(23<<3)	/* reserved for local use */
E 28
I 28
#define	LOG_PRIMASK	0x07	/* mask to extract priority part (internal) */
				/* extract priority */
#define	LOG_PRI(p)	((p) & LOG_PRIMASK)
#define	LOG_MAKEPRI(fac, pri)	(((fac) << 3) | (pri))
E 28
E 7
E 4

I 4
D 7
	/* user abnormal conditions priorities */
#define	LOG_EMERG	7	/* system unusable -- send to all users */
#define	LOG_ALERT	8	/* missing files (e.g., /etc/utmp) */
#define	LOG_CRIT	9	/* critical conditions */
#define	LOG_ERR		10	/* init open faliures/fatal daemon errors */
#define	LOG_FAIL	11	/* getty failing, interface dropped */
D 5
#define	LOG_WARN	12	/* non-fatal daemon errs */
E 5
I 5
#define	LOG_WARNING	12	/* non-fatal daemon errs */
E 7
I 7
D 28
#define LOG_NFACILITIES	24	/* maximum number of facilities */
#define LOG_FACMASK	0x03f8	/* mask to extract facility part */
E 28
I 28
#ifdef SYSLOG_NAMES
#define	INTERNAL_NOPRI	0x10	/* the "no priority" priority */
				/* mark "facility" */
#define	INTERNAL_MARK	LOG_MAKEPRI(LOG_NFACILITIES, 0)
typedef struct _code {
	char	*c_name;
	int	c_val;
} CODE;
E 28
E 7
E 5

I 21
D 28
#define LOG_FAC(p)	(((p) & LOG_FACMASK) >> 3)	/* facility of pri */
E 28
I 28
CODE prioritynames[] = {
	"alert",	LOG_ALERT,
	"crit",		LOG_CRIT,
	"debug",	LOG_DEBUG,
	"emerg",	LOG_EMERG,
	"err",		LOG_ERR,
	"error",	LOG_ERR,		/* DEPRECATED */
	"info",		LOG_INFO,
	"none",		INTERNAL_NOPRI,		/* INTERNAL */
	"notice",	LOG_NOTICE,
	"panic", 	LOG_EMERG,		/* DEPRECATED */
	"warn",		LOG_WARNING,		/* DEPRECATED */
	"warning",	LOG_WARNING,
	NULL,		-1,
};
#endif
E 28

E 21
D 7
	/* user priorities */
#define	LOG_SALERT	13	/* important information */
#define	LOG_SECURITY	14	/* root/su logins */
#define	LOG_FIXED	15	/* abnormal condition fixed (recovery action) */
#define	LOG_MAIL	16	/* mail failures */
#define	LOG_REJECT	17	/* login/daemon rejections */
#define	LOG_NOTICE	18	/* important info */
E 7
I 7
D 28
/*
 *  Priorities (these are ordered)
 */
E 28
I 28
/* facility codes */
#define	LOG_KERN	(0<<3)	/* kernel messages */
#define	LOG_USER	(1<<3)	/* random user-level messages */
#define	LOG_MAIL	(2<<3)	/* mail system */
#define	LOG_DAEMON	(3<<3)	/* system daemons */
#define	LOG_AUTH	(4<<3)	/* security/authorization messages */
#define	LOG_SYSLOG	(5<<3)	/* messages generated internally by syslogd */
#define	LOG_LPR		(6<<3)	/* line printer subsystem */
#define	LOG_NEWS	(7<<3)	/* network news subsystem */
#define	LOG_UUCP	(8<<3)	/* UUCP subsystem */
#define	LOG_CRON	(9<<3)	/* clock daemon */
I 30
#define	LOG_AUTHPRIV	(10<<3)	/* security/authorization messages (private) */
I 36
#define	LOG_FTP		(11<<3)	/* ftp daemon */
E 36

E 30
	/* other codes through 15 reserved for system use */
#define	LOG_LOCAL0	(16<<3)	/* reserved for local use */
#define	LOG_LOCAL1	(17<<3)	/* reserved for local use */
#define	LOG_LOCAL2	(18<<3)	/* reserved for local use */
#define	LOG_LOCAL3	(19<<3)	/* reserved for local use */
#define	LOG_LOCAL4	(20<<3)	/* reserved for local use */
#define	LOG_LOCAL5	(21<<3)	/* reserved for local use */
#define	LOG_LOCAL6	(22<<3)	/* reserved for local use */
#define	LOG_LOCAL7	(23<<3)	/* reserved for local use */
E 28
E 7

D 7
	/* user information priorities */
#define	LOG_INFO	19	/* informational message */
#define	LOG_INFO1	20	/* informational message */
#define	LOG_INFO2	21	/* informational message */
#define	LOG_INFO3	22	/* informational message */
#define	LOG_INFO4	23	/* informational message */
#define	LOG_INFO5	24	/* informational message */
E 7
I 7
D 28
#define LOG_EMERG	0	/* system is unusable */
#define LOG_ALERT	1	/* action must be taken immediately */
#define LOG_CRIT	2	/* critical conditions */
#define LOG_ERR		3	/* error conditions */
#define LOG_WARNING	4	/* warning conditions */
D 25
#define LOG_NOTICE	5	/* normal but signification condition */
E 25
I 25
#define LOG_NOTICE	5	/* normal but significant condition */
E 25
#define LOG_INFO	6	/* informational */
#define LOG_DEBUG	7	/* debug-level messages */
E 28
I 28
#define	LOG_NFACILITIES	24	/* current number of facilities */
#define	LOG_FACMASK	0x03f8	/* mask to extract facility part */
				/* facility of pri */
#define	LOG_FAC(p)	(((p) & LOG_FACMASK) >> 3)
E 28
E 7

D 7
	/* user debug/local priorities */
#define	LOG_DEBUG	25	/* debugging info */
#define	LOG_LOCAL1	26	/* reserved for local use */
#define	LOG_LOCAL2	27	/* reserved for local use */
#define	LOG_LOCAL3	28	/* reserved for local use */
#define	LOG_LOCAL4	29	/* reserved for local use */
#define	LOG_LOCAL5	30	/* reserved for local use */
#define	LOG_LOCAL6	31	/* reserved for local use */
E 7
I 7
D 11
#define LOG_PRIMASK	0x0007	/* mask to extract priority part */
E 11
I 11
D 28
#define LOG_PRIMASK	0x0007	/* mask to extract priority part (internal) */
I 21
#define LOG_PRI(p)	((p) & LOG_PRIMASK)	/* extract priority */
E 28
I 28
#ifdef SYSLOG_NAMES
CODE facilitynames[] = {
	"auth",		LOG_AUTH,
I 30
	"authpriv",	LOG_AUTHPRIV,
E 30
	"cron", 	LOG_CRON,
	"daemon",	LOG_DAEMON,
I 36
	"ftp",		LOG_FTP,
E 36
	"kern",		LOG_KERN,
	"lpr",		LOG_LPR,
	"mail",		LOG_MAIL,
	"mark", 	INTERNAL_MARK,		/* INTERNAL */
	"news",		LOG_NEWS,
	"security",	LOG_AUTH,		/* DEPRECATED */
	"syslog",	LOG_SYSLOG,
	"user",		LOG_USER,
	"uucp",		LOG_UUCP,
	"local0",	LOG_LOCAL0,
	"local1",	LOG_LOCAL1,
	"local2",	LOG_LOCAL2,
	"local3",	LOG_LOCAL3,
	"local4",	LOG_LOCAL4,
	"local5",	LOG_LOCAL5,
	"local6",	LOG_LOCAL6,
	"local7",	LOG_LOCAL7,
	NULL,		-1,
};
#endif
E 28

D 28
#define	LOG_MAKEPRI(fac, pri)	(((fac) << 3) | (pri))

E 28
#ifdef KERNEL
D 28
#define LOG_PRINTF	-1	/* pseudo-priority to indicate use of printf */
E 28
I 28
#define	LOG_PRINTF	-1	/* pseudo-priority to indicate use of printf */
E 28
#endif
E 21

/*
I 18
 * arguments to setlogmask.
 */
#define	LOG_MASK(pri)	(1 << (pri))		/* mask for one priority */
#define	LOG_UPTO(pri)	((1 << ((pri)+1)) - 1)	/* all priorities through pri */

/*
E 18
D 16
 * arguments to setlogmask.
 */
#define	LOG_MASK(pri)	(1 << (pri))		/* mask for one priority */
D 13
#define	LOG_UPTO(pri)	(1 << ((pri) + 1) - 1)	/* all priorities through pri */
E 13
I 13
#define	LOG_UPTO(pri)	((1 << ((pri)+1)) - 1)	/* all priorities through pri */
E 13
E 11
E 7

E 4
/*
E 16
D 2
 *  Mode parameters to initlog.
E 2
I 2
D 28
 *  Option flags for openlog.
E 28
I 28
 * Option flags for openlog.
E 28
I 9
 *
D 28
 *	LOG_ODELAY no longer does anything; LOG_NDELAY is the
 *	inverse of what it used to be.
E 28
I 28
 * LOG_ODELAY no longer does anything.
 * LOG_NDELAY is the inverse of what it used to be.
E 28
E 9
E 2
 */
D 2
#define	LOG_NULL	0	/* don't touch log */
#define	LOG_SOUT	1	/* log standard & diag output */
#define	LOG_DIAG	2	/* log diagnostic output */
#define	LOG_INDEP	3	/* log independently */
#define	LOG_CLOSE	4	/* close the log */

/*
 *  Status parameters to initlog.
 */
#define	LOG_PID		0001	/* log the pid with each message */
#define	LOG_TIME	0002	/* log the time with each message */
#define	LOG_COOLIT	0004	/* suppress priority stuff */
#define	LOG_DGRAM	0010	/* running over a datagram socket */
E 2
I 2
D 12
#define	LOG_PID		01	/* log the pid with each message */
I 4
#define	LOG_CONS	02	/* log on the console if errors in sending */
#define	LOG_ODELAY	04	/* delay open until syslog() is called */
I 9
#define LOG_NDELAY	010	/* don't delay open */
E 12
I 12
#define	LOG_PID		0x01	/* log the pid with each message */
#define	LOG_CONS	0x02	/* log on the console if errors in sending */
D 16
#define	LOG_ODELAY	0x04	/* delay open until syslog() is called */
E 16
I 16
#define	LOG_ODELAY	0x04	/* delay open until first syslog() (default) */
E 16
D 28
#define LOG_NDELAY	0x08	/* don't delay open */
D 27
#define LOG_NOWAIT	0x10	/* if forking to log on console, don't wait() */
E 27
I 27
#define LOG_NOWAIT	0x10	/* don't wait for console forks: DEPRECATED */
E 28
I 28
#define	LOG_NDELAY	0x08	/* don't delay open */
#define	LOG_NOWAIT	0x10	/* don't wait for console forks: DEPRECATED */
E 28
E 27
I 26
#define	LOG_PERROR	0x20	/* log to stderr as well */
I 31

#ifndef KERNEL

I 34
/*
 * Don't use va_list in the vsyslog() prototype.   Va_list is typedef'd in two
 * places (<machine/varargs.h> and <machine/stdarg.h>), so if we include one
 * of them here we may collide with the utility's includes.  It's unreasonable
 * for utilities to have to include one of them to include syslog.h, so we get
D 37
 * _VA_LIST_ from <machine/ansi.h> and use it.
E 37
I 37
 * _BSD_VA_LIST_ from <machine/ansi.h> and use it.
E 37
 */
#include <machine/ansi.h>
E 34
#include <sys/cdefs.h>
D 32
#include <varargs.h>
E 32
I 32
D 34
#include <stdarg.h>
E 34
E 32

__BEGIN_DECLS
void	closelog __P((void));
void	openlog __P((const char *, int, int));
D 33
void	setlogmask __P((int));
E 33
I 33
int	setlogmask __P((int));
E 33
void	syslog __P((int, const char *, ...));
D 34
void	vsyslog __P((int, const char *, va_list));
E 34
I 34
D 35
void	vsyslog __P((int, const char *, _VA_LIST_));
E 35
I 35
void	vsyslog __P((int, const char *, _BSD_VA_LIST_));
E 35
E 34
__END_DECLS

#endif /* !KERNEL */
E 31
E 26
E 12
E 9
E 4
E 2
E 1
