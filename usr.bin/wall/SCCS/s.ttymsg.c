h13091
s 00015/00007/00122
d D 8.2 93/11/16 11:39:25 bostic 11 10
c The source ttymsg.c needed a check for slash in the utmp entries. Don't
c forget to recompile talkd and syslogd in addition to wall after fixing
c this. Also, I found that the string wall passes to ttymsg() wasn't
c strictly terminated. And there were some new gcc warnings to contend
c with.
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00002/00002/00127
d D 8.1 93/06/06 22:23:21 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00008/00120
d D 5.9 91/08/01 16:04:25 marc 9 8
c pass in tmout instead of hardwired 5 minutes (talk now uses ttymsg)
e
s 00001/00001/00127
d D 5.8 91/07/01 00:21:21 bostic 8 7
c FNDELAY -> O_NONBLOCK
e
s 00062/00064/00066
d D 5.7 91/02/25 10:44:07 bostic 7 6
c ANSI fixes
c don't return after forking, use _exit after forking
c reformat so it's clearer (well, at least to me)
e
s 00001/00011/00129
d D 5.6 90/09/07 12:04:52 bostic 6 5
c new copyright notice
e
s 00046/00015/00094
d D 5.5 90/06/29 00:44:41 marc 5 4
c fix ttymsg
e
s 00006/00004/00103
d D 5.4 90/02/24 17:31:25 karels 4 3
c ignore EIO on write
e
s 00005/00003/00102
d D 5.3 90/02/24 14:28:22 karels 3 2
c remove newline from error msg (callers both add it);
c EPERM => EACCES on open
e
s 00025/00016/00080
d D 5.2 89/11/07 08:45:19 karels 2 1
c don't log crap on fork; syslogd needs signals reset; KNF
e
s 00096/00000/00000
d D 5.1 89/10/28 13:48:49 bostic 1 0
c separate out for syslogd(8)
e
u
U
t
T
I 1
/*
D 10
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 6
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/uio.h>
D 7
#include <sys/file.h>
I 2
#include <sys/signal.h>
E 7
I 7
#include <signal.h>
#include <fcntl.h>
E 7
E 2
#include <dirent.h>
#include <errno.h>
#include <paths.h>
I 7
#include <unistd.h>
E 7
I 5
#include <stdio.h>
I 7
#include <string.h>
#include <stdlib.h>
E 7
E 5

/*
D 7
 * display the contents of a uio structure on a terminal.  Used by
D 2
 * wall(1) and syslogd(8).
E 2
I 2
 * wall(1) and syslogd(8).  Forks and finishes in child if write
 * would block, waiting at most five minutes.
I 3
D 4
 * Returns pointer to error string on error;
 * string is not newline-terminated.
E 4
I 4
 * Returns pointer to error string on unexpected error;
 * string is not newline-terminated.  Various "normal" errors
 * are ignored (exclusive-use, lack of permission, etc.).
E 7
I 7
D 9
 * Display the contents of a uio structure on a terminal.  Used by wall(1)
 * and syslogd(8).  Forks and finishes in child if write would block, waiting
 * at most five minutes.  Returns pointer to error string on unexpected error;
 * string is not newline-terminated.  Various "normal" errors are ignored
 * (exclusive-use, lack of permission, etc.).
E 9
I 9
 * Display the contents of a uio structure on a terminal.  Used by wall(1),
D 11
 * syslogd(8), and talk(1).  Forks and finishes in child if write would block, 
 * waiting up to tmout seconds.  Returns pointer to error string on unexpected 
 * error; string is not newline-terminated.  Various "normal" errors are 
E 11
I 11
 * syslogd(8), and talkd(8).  Forks and finishes in child if write would block,
 * waiting up to tmout seconds.  Returns pointer to error string on unexpected
 * error; string is not newline-terminated.  Various "normal" errors are
E 11
 * ignored (exclusive-use, lack of permission, etc.).
E 9
E 7
E 4
E 3
E 2
 */
char *
D 5
ttymsg(iov, iovcnt, line, nonblock)
E 5
I 5
D 9
ttymsg(iov, iovcnt, line)
E 9
I 9
ttymsg(iov, iovcnt, line, tmout)
E 9
E 5
	struct iovec *iov;
	int iovcnt;
	char *line;
I 9
	int tmout;
E 9
D 5
	int nonblock;
E 5
{
D 7
	extern int errno;
E 7
	static char device[MAXNAMLEN] = _PATH_DEV;
	static char errbuf[1024];
D 5
	register int cnt, fd, total, wret;
E 5
I 5
	register int cnt, fd, left, wret;
E 5
D 7
	char *strcpy(), *strerror();
E 7
I 5
	struct iovec localiov[6];
	int forked = 0;
E 5

I 5
D 11
	if (iovcnt > 6)
E 11
I 11
	if (iovcnt > sizeof(localiov) / sizeof(localiov[0]))
E 11
		return ("too many iov's (change code in wall/ttymsg.c)");
I 11

	(void) strcpy(device + sizeof(_PATH_DEV) - 1, line);
	if (strchr(device + sizeof(_PATH_DEV) - 1, '/')) {
		/* A slash is an attempt to break security... */
		(void) snprintf(errbuf, sizeof(errbuf), "'/' in \"%s\"",
		    device);
		return (errbuf);
	}

E 11
E 5
	/*
	 * open will fail on slip lines or exclusive-use lines
	 * if not running as root; not an error.
	 */
D 2
	(void)strcpy(device + sizeof(_PATH_DEV) - 1, line);
E 2
I 2
D 11
	(void) strcpy(device + sizeof(_PATH_DEV) - 1, line);
E 11
E 2
D 5
	if ((fd = open(device, O_WRONLY|(nonblock ? O_NONBLOCK : 0), 0)) < 0)
E 5
I 5
	if ((fd = open(device, O_WRONLY|O_NONBLOCK, 0)) < 0) {
E 5
D 2
		if (errno != EBUSY && errno != EPERM)
			goto bad;
		else
			return(NULL);
E 2
I 2
D 3
		if (errno != EBUSY && errno != EPERM) {
			(void) sprintf(errbuf, "open %s: %s\n", device,
E 3
I 3
D 7
		if (errno != EBUSY && errno != EACCES) {
			(void) sprintf(errbuf, "open %s: %s", device,
E 3
			    strerror(errno));
			return (errbuf);
		} else
E 7
I 7
		if (errno == EBUSY || errno == EACCES)
E 7
			return (NULL);
I 7
		(void) snprintf(errbuf, sizeof(errbuf),
		    "%s: %s", device, strerror(errno));
		return (errbuf);
E 7
I 5
	}
E 5
E 2

D 5
	for (cnt = total = 0; cnt < iovcnt; ++cnt)
		total += iov[cnt].iov_len;
E 5
I 5
	for (cnt = left = 0; cnt < iovcnt; ++cnt)
		left += iov[cnt].iov_len;
E 5

D 5
	for (;;)
		if ((wret = writev(fd, iov, iovcnt)) < 0)
E 5
I 5
	for (;;) {
D 7
		if ((wret = writev(fd, iov, iovcnt)) < 0) {
E 5
			if (errno == EWOULDBLOCK) {
D 2
				if (fork())
					goto bad;
E 2
I 2
D 5
				if (fork()) {
E 5
I 5
				int off = 0;
				int cpid;

				if (forked) {
E 5
					(void) close(fd);
I 5
					/* return ("already forked"); */
					/* "can't happen" */
					exit(1);
				}
				cpid = fork();
				if (cpid < 0) {
					(void) sprintf(errbuf, "can't fork: %s",
						strerror(errno));
					(void) close(fd);
					return (errbuf);
				}
				if (cpid) {	/* parent */
					(void) close(fd);
E 5
					return (NULL);
				}
I 5
				forked++;
E 5
E 2
				/* wait at most 5 minutes */
D 2
				(void)alarm((u_int)(60 * 5));
				(void)ttymsg(iov, iovcnt, line, 0);
E 2
I 2
				(void) signal(SIGALRM, SIG_DFL);
				(void) signal(SIGTERM, SIG_DFL); /* XXX */
				(void) sigsetmask(0);
				(void) alarm((u_int)(60 * 5));
D 5
				(void) ttymsg(iov, iovcnt, line, 0);
E 2
				exit(0);
E 5
I 5
				(void) fcntl(fd, FNDELAY, &off);
				continue;
E 5
			} else {
				/*
				 * we get ENODEV on a slip line if we're
D 4
				 * running as root
E 4
I 4
				 * running as root, and EIO if the line
				 * just went away
E 4
				 */
D 4
				if (errno == ENODEV)
E 4
I 4
				if (errno == ENODEV || errno == EIO)
E 4
					break;
D 2
bad:				(void)sprintf(errbuf, "%s: %s\n", device,
				    strerror(errno));
				(void)close(fd);
				return(errbuf);
E 2
I 2
D 3
				(void) sprintf(errbuf, "writing %s: %s\n",
E 3
I 3
				(void) sprintf(errbuf, "writing %s: %s",
E 3
				    device, strerror(errno));
				(void) close(fd);
				return (errbuf);
E 2
			}
D 5
		else if (wret) {
			if (wret == total)
				break;
E 5
I 5
		} 
		if (wret < left) {
E 7
I 7
		wret = writev(fd, iov, iovcnt);
		if (wret >= left)
			break;
		if (wret >= 0) {
E 7
			left -= wret;
			if (iov != localiov) {
D 11
				bcopy(iov, localiov, 
E 11
I 11
				bcopy(iov, localiov,
E 11
D 7
					iovcnt * sizeof (struct iovec));
E 7
I 7
				    iovcnt * sizeof(struct iovec));
E 7
				iov = localiov;
			}
E 5
			for (cnt = 0; wret >= iov->iov_len; ++cnt) {
				wret -= iov->iov_len;
				++iov;
				--iovcnt;
			}
			if (wret) {
				iov->iov_base += wret;
				iov->iov_len -= wret;
			}
D 5
		}
E 5
I 5
D 7
		} else
E 7
I 7
			continue;
		}
		if (errno == EWOULDBLOCK) {
			int cpid, off = 0;

			if (forked) {
				(void) close(fd);
				_exit(1);
			}
			cpid = fork();
			if (cpid < 0) {
				(void) snprintf(errbuf, sizeof(errbuf),
				    "fork: %s", strerror(errno));
				(void) close(fd);
				return (errbuf);
			}
			if (cpid) {	/* parent */
				(void) close(fd);
				return (NULL);
			}
			forked++;
D 9
			/* wait at most 5 minutes */
E 9
I 9
			/* wait at most tmout seconds */
E 9
			(void) signal(SIGALRM, SIG_DFL);
			(void) signal(SIGTERM, SIG_DFL); /* XXX */
			(void) sigsetmask(0);
D 9
			(void) alarm((u_int)(60 * 5));
E 9
I 9
			(void) alarm((u_int)tmout);
E 9
D 8
			(void) fcntl(fd, FNDELAY, &off);
E 8
I 8
			(void) fcntl(fd, O_NONBLOCK, &off);
E 8
			continue;
D 11
		} 
E 11
I 11
		}
E 11
		/*
		 * We get ENODEV on a slip line if we're running as root,
		 * and EIO if the line just went away.
		 */
		if (errno == ENODEV || errno == EIO)
E 7
			break;
I 7
		(void) close(fd);
		if (forked)
			_exit(1);
		(void) snprintf(errbuf, sizeof(errbuf),
		    "%s: %s", device, strerror(errno));
		return (errbuf);
E 7
	}
D 7
	if (forked)
		exit(0);
E 7
I 7

E 7
E 5
D 2
	(void)close(fd);
	return(NULL);
E 2
I 2
	(void) close(fd);
I 7
	if (forked)
		_exit(0);
E 7
	return (NULL);
E 2
}
E 1
