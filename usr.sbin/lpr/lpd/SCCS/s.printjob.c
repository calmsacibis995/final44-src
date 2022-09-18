h33994
s 00008/00006/01459
d D 8.7 95/05/10 05:57:52 bostic 50 49
c Paul Vixie tested this and found some problems.
e
s 00004/00003/01461
d D 8.6 95/04/28 15:39:31 tef 49 48
c Better portability to other systems.
e
s 00127/00044/01337
d D 8.5 95/04/28 12:16:07 tef 48 47
c Support for printers connected via ethernet/TCP and terminal servers.
e
s 00037/00011/01344
d D 8.4 95/04/28 11:34:52 tef 47 46
c Better error handling and diagnostics.
e
s 00007/00003/01348
d D 8.3 95/04/27 21:38:39 tef 46 45
c Bug fixes.
e
s 00001/00001/01350
d D 8.2 94/04/16 12:45:56 bostic 45 44
c  lpd was overriding the paper width setting from /etc/printcap
c From: "John F. Woods" <jfw@jfwhome.funhouse.com>
e
s 00005/00005/01346
d D 8.1 93/06/06 14:00:21 bostic 44 43
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00028/01341
d D 5.17 92/09/15 10:51:58 elan 43 42
c Added SCCS keywords.
e
s 00101/00067/01268
d D 5.16 92/09/01 11:09:44 elan 42 41
c Rewrote to use new getcap(3) library.  Major prototyping and cleanup.
e
s 00093/00024/01242
d D 5.15 92/07/21 10:29:24 bostic 41 40
c prototype lpr to fix quad's
e
s 00002/00001/01264
d D 5.14 92/06/27 13:21:45 bostic 40 39
c remove hard-coded length
e
s 00006/00004/01259
d D 5.13 91/03/02 14:58:14 bostic 39 38
c ANSI
e
s 00001/00011/01262
d D 5.12 90/06/01 18:45:31 bostic 38 37
c new copyright notice
e
s 00001/00001/01272
d D 5.11 90/02/09 09:33:23 tef 37 36
c don't fork off an output filter if it won't ever be used
e
s 00018/00007/01255
d D 5.10 90/01/30 13:14:26 mckusick 36 35
c output errors to log file (4.3BSD-tahoe/usr.sbin/6)
e
s 00004/00033/01258
d D 5.9 89/08/22 21:02:24 tef 35 34
c common code for checking if rm==localhost
e
s 00000/00008/01291
d D 5.8 89/08/22 11:04:48 bostic 34 33
c only one line discipline
e
s 00018/00016/01281
d D 5.7 89/05/11 14:09:45 bostic 33 32
c file reorg, pathnames.h, paths.h
e
s 00010/00005/01287
d D 5.6 88/06/30 18:00:07 bostic 32 31
c install approved copyright notice
e
s 00010/00004/01282
d D 5.5 88/05/05 18:08:26 bostic 31 30
c written by Ralph Campbell; add Berkeley specific header
e
s 00005/00000/01281
d D 5.4 85/11/17 15:53:55 eric 30 29
c clean up logging
e
s 00041/00005/01240
d D 5.3 85/11/11 15:34:05 tef 29 28
c Can now specify both lp= and rm=/rp= in same printcap entry; lpd
c will figure out if printer is on local machine or not and do the right thing.
e
s 00001/00001/01244
d D 5.2 85/09/17 19:26:42 eric 28 27
c facilities in syslog
e
s 00007/00001/01238
d D 5.1 85/06/06 10:07:47 dist 27 26
c Add copyright
e
s 00007/00001/01232
d D 4.24 85/02/27 16:19:41 ralph 26 25
c added 'hl' flag to printcap to print the banner last.
e
s 00131/00061/01102
d D 4.23 84/12/05 14:09:07 ralph 25 24
c close -s (symbolic links) security bug.
e
s 00001/00000/01162
d D 4.22 84/11/07 10:01:18 ralph 24 23
c reset width too.
e
s 00001/00001/01161
d D 4.21 84/10/23 09:47:13 ralph 23 22
c truncate error file before starting filter.
e
s 00001/00000/01161
d D 4.20 84/10/23 09:18:09 ralph 22 21
c reset indent before next job.
e
s 00008/00000/01153
d D 4.19 84/09/06 15:24:21 ralph 21 20
c change to new tty driver if xs or xc used.
e
s 00119/00129/01034
d D 4.18 84/07/25 09:08:14 ralph 20 19
c use syslog(). Check for free space before transfering file.
e
s 00014/00004/01149
d D 4.17 84/02/10 11:58:01 ralph 19 18
c don't log errs if remote queue off, use SO_KEEPALIVE to timeout conn.
e
s 00058/00027/01095
d D 4.16 84/01/05 16:13:16 ralph 18 17
c mail filters errors back to the user.
e
s 00008/00008/01114
d D 4.15 83/11/18 10:34:03 ralph 17 16
c use strncpy for jobname, class, etc. to prevent overflows.
e
s 00004/00001/01118
d D 4.14 83/08/18 15:23:26 ralph 16 15
c signal to minor daemon caused /dev/printer to be removed.
e
s 00001/00001/01118
d D 4.13 83/08/02 08:41:47 ralph 15 14
c fixed -c option to `if' filter
e
s 00017/00014/01102
d D 4.12 83/07/27 09:27:15 ralph 14 13
c bug fixes for `rs' printcap entry
e
s 00004/00001/01112
d D 4.11 83/07/17 00:12:01 sam 13 12
c put sccs id's to some use
e
s 00001/00000/01112
d D 4.10 83/06/29 17:09:32 ralph 12 11
c changed to use unix domain ipc.
e
s 00005/00002/01107
d D 4.9 83/06/22 09:31:12 ralph 11 10
c added -n option to print ditroff files.
e
s 00030/00017/01079
d D 4.8 83/06/17 15:07:49 ralph 10 9
c fixed `fc' and `fs' when 0177777 is needed.
e
s 00012/00008/01084
d D 4.7 83/06/15 14:57:32 sam 9 8
c open and flock defines changed
e
s 00040/00026/01052
d D 4.6 83/06/02 12:24:00 ralph 8 7
c made local variables static to improve separation between functions.
e
s 00009/00003/01069
d D 4.5 83/05/23 09:40:11 ralph 7 6
c forgot to close file in sendfile under some error conditions.
e
s 00012/00006/01060
d D 4.4 83/05/19 14:37:39 ralph 6 4
c add `fo' option and now pass indent parameter to `if' filter.
e
s 00002/00001/01065
d R 4.4 83/05/19 11:49:31 ralph 5 4
c added `fo' flag to print form feed after first open of printer.
e
s 00001/00001/01065
d D 4.3 83/05/18 16:45:49 ralph 4 3
c fixed lprm segmentation fault when remote is down.
e
s 00195/00109/00871
d D 4.2 83/05/16 13:40:08 ralph 3 1
c bug fixes and changes for lpc command.
e
s 00193/00107/00873
d R 4.2 83/05/13 11:53:24 ralph 2 1
c bug fixes and changes for lpc command.
e
s 00980/00000/00000
d D 4.1 83/04/29 11:29:35 ralph 1 0
c date and time created 83/04/29 11:29:35 by ralph
e
u
U
t
T
I 27
/*
D 43
 * Copyright (c) 1983 Regents of the University of California.
E 43
I 43
D 44
 * Copyright (c) 1983 The Regents of the University of California.
E 43
D 31
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 31
I 31
 * All rights reserved.
E 44
I 44
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 44
 *
D 38
 * Redistribution and use in source and binary forms are permitted
D 32
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 32
I 32
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
E 38
I 38
D 42
 * %sccs.include.redist.c%
E 42
I 42
D 43
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 43
 *
D 43
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 43
I 43
 * %sccs.include.redist.c%
E 43
E 42
E 38
E 32
E 31
 */

E 27
I 1
D 13
/*	%M%	%I%	%E%	*/
E 13
I 13
#ifndef lint
D 29
static char sccsid[] = "%W% (Berkeley) %G%";
E 29
I 29
D 31
static char sccsid[] = "@(#)printjob.c	5.2 (Berkeley) 9/17/85";
E 29
D 27
#endif
E 27
I 27
#endif not lint
E 31
I 31
D 42
static char sccsid[] = "%W% (Berkeley) %G%";
E 42
I 42
D 43
static char sccsid[] = "@(#)printjob.c	5.16 (Berkeley) 8/6/92";
E 43
I 43
D 44
char copyright[] =
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
 All rights reserved.\n";
E 44
I 44
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 44
E 43
E 42
#endif /* not lint */
I 43

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 43
E 31
E 27

E 13
/*
 * printjob -- print jobs in the queue.
 *
 *	NOTE: the lock file is used to pass information to lpq and lprm.
 *	it does not need to be removed because file locks are dynamic.
 */

I 41
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/stat.h>
I 42
#include <sys/types.h>
I 49
#include <sys/file.h>
E 49
E 42

I 42
#include <pwd.h>
#include <unistd.h>
E 42
#include <signal.h>
#include <sgtty.h>
#include <syslog.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
I 42
#include <stdlib.h>
E 42
E 41
#include "lp.h"
I 41
#include "lp.local.h"
E 41
I 33
#include "pathnames.h"
I 41
#include "extern.h"
E 41
E 33

D 8
#define DORETURN	0	/* absorb fork error */
#define DOABORT		1	/* abort if dofork fails */
E 8
I 8
D 20
#define DORETURN	0		/* absorb fork error */
#define DOABORT		1		/* abort if dofork fails */
E 20
I 20
#define DORETURN	0	/* absorb fork error */
#define DOABORT		1	/* abort if dofork fails */
E 20
E 8

I 25
/*
 * Error tokens
 */
#define REPRINT		-2
#define ERROR		-1
#define	OK		0
#define	FATALERR	1
#define	NOACCT		2
#define	FILTERERR	3
#define	ACCESS		4

E 25
D 8
char	title[80];		/* ``pr'' title */
FILE	*cfp;			/* control file */
int	pfd;			/* printer file descriptor */
int	ofd;			/* output filter file descriptor */
int	lfd;			/* lock file descriptor */
int	pid;			/* pid of lpd process */
int	prchild;		/* id of pr process */
int	child;			/* id of any filters */
int	ofilter;		/* id of output filter, if any */
D 6
int	tof = 1;		/* top of form; init true if open does ff */
E 6
I 6
int	tof;			/* true if at top of form */
E 6
int	remote;			/* non zero if sending files to remote */
E 8
I 8
D 20
static char	title[80];		/* ``pr'' title */
static FILE	*cfp;			/* control file */
static int	pfd;			/* printer file descriptor */
static int	ofd;			/* output filter file descriptor */
static int	lfd;			/* lock file descriptor */
static int	pid;			/* pid of lpd process */
static int	prchild;		/* id of pr process */
static int	child;			/* id of any filters */
static int	ofilter;		/* id of output filter, if any */
static int	tof;			/* true if at top of form */
I 14
static int	count;			/* Number of files actually printed */
E 14
static int	remote;			/* true if sending files to remote */
E 20
I 20
D 42
char	title[80];		/* ``pr'' title */
FILE	*cfp;			/* control file */
int	pfd;			/* printer file descriptor */
int	ofd;			/* output filter file descriptor */
int	lfd;			/* lock file descriptor */
int	pid;			/* pid of lpd process */
int	prchild;		/* id of pr process */
int	child;			/* id of any filters */
int	ofilter;		/* id of output filter, if any */
int	tof;			/* true if at top of form */
int	remote;			/* true if sending files to remote */
I 25
dev_t	fdev;			/* device of file pointed to by symlink */
ino_t	fino;			/* inode of file pointed to by symlink */
E 42
I 42
static dev_t	 fdev;		/* device of file pointed to by symlink */
static ino_t	 fino;		/* inode of file pointed to by symlink */
static FILE	*cfp;		/* control file */
static int	 child;		/* id of any filters */
static int	 lfd;		/* lock file descriptor */
static int	 ofd;		/* output filter file descriptor */
static int	 ofilter;	/* id of output filter, if any */
static int	 pfd;		/* prstatic inter file descriptor */
static int	 pid;		/* pid of lpd process */
static int	 prchild;	/* id of pr process */
D 48
static int	 remote;	/* true if sending files to remote */
E 48
static char	 title[80];	/* ``pr'' title */
static int	 tof;		/* true if at top of form */
E 42
E 25
E 20
E 8

I 14
D 20
static char	fromhost[32];		/* user's host machine */
E 14
D 8
extern	banner();		/* big character printer */
char	logname[32];		/* user's login name */
char	jobname[32];		/* job or file name */
char	class[32];		/* classification field */
D 3
char	width[10] = "-w";	/* page width for `pr' */
char	length[10] = "-l";	/* page length for `pr' */
E 3
I 3
char	width[10] = "-w";	/* page width in characters */
char	length[10] = "-l";	/* page length in lines */
char	pxwidth[10] = "-x";	/* page width in pixels */
char	pxlength[10] = "-y";	/* page length in pixels */
I 6
char	indent[10] = "-i0";	/* indentation size in characters */
E 8
I 8
static char	logname[32];		/* user's login name */
D 17
static char	jobname[32];		/* job or file name */
E 17
I 17
static char	jobname[100];		/* job or file name */
E 17
static char	class[32];		/* classification field */
static char	width[10] = "-w";	/* page width in characters */
static char	length[10] = "-l";	/* page length in lines */
static char	pxwidth[10] = "-x";	/* page width in pixels */
static char	pxlength[10] = "-y";	/* page length in pixels */
static char	indent[10] = "-i0";	/* indentation size in characters */
I 18
static char	tmpfile[] = "errsXXXXXX"; /* file name for filter output */
E 20
I 20
D 42
char	fromhost[32];		/* user's host machine */
char	logname[32];		/* user's login name */
char	jobname[100];		/* job or file name */
char	class[32];		/* classification field */
char	width[10] = "-w";	/* page width in characters */
char	length[10] = "-l";	/* page length in lines */
char	pxwidth[10] = "-x";	/* page width in pixels */
char	pxlength[10] = "-y";	/* page length in pixels */
char	indent[10] = "-i0";	/* indentation size in characters */
D 36
char	tmpfile[] = "errsXXXXXX"; /* file name for filter output */
E 36
I 36
char	tempfile[] = "errsXXXXXX"; /* file name for filter output */
E 42
I 42
static char	class[32];		/* classification field */
static char	fromhost[32];		/* user's host machine */
				/* indentation size in static characters */
static char	indent[10] = "-i0"; 
static char	jobname[100];		/* job or file name */
static char	length[10] = "-l";	/* page length in lines */
static char	logname[32];		/* user's login name */
static char	pxlength[10] = "-y";	/* page length in pixels */
static char	pxwidth[10] = "-x";	/* page width in pixels */
static char	tempfile[] = "errsXXXXXX"; /* file name for filter output */
static char	width[10] = "-w";	/* page width in static characters */
E 42
E 36
E 20
E 18
E 8
E 6
E 3

I 41
static void       abortpr __P((int));
static void       banner __P((char *, char *));
static int        dofork __P((int));
static int        dropit __P((int));
static void       init __P((void));
static void       openpr __P((void));
I 48
static void       opennet __P((char *));
static void       opentty __P((void));
static void       openrem __P((void));
E 48
static int        print __P((int, char *));
static int        printit __P((char *));
static void       pstatus __P((const char *, ...));
static char       response __P((void));
static void       scan_out __P((int, char *, int));
static char      *scnline __P((int, char *, int));
static int        sendfile __P((int, char *));
static int        sendit __P((char *));
static void       sendmail __P((char *, int));
static void       setty __P((void));

void
E 41
printjob()
{
	struct stat stb;
	register struct queue *q, **qp;
	struct queue **queue;
	register int i, nitems;
D 46
	long pidoff;
E 46
I 46
	off_t pidoff;
E 46
D 20
	extern int onintr();
E 20
I 20
D 47
	int count = 0;
E 47
I 47
	int errcnt, count = 0;
E 47
D 39
	extern int abortpr();
E 39
I 39
D 41
	void abortpr();
E 41
E 39
E 20

D 3
	name = "printjob";
E 3
	init();					/* set up capabilities */
I 12
	(void) write(1, "", 1);			/* ack that daemon is started */
I 30
	(void) close(2);			/* set up log file */
	if (open(LF, O_WRONLY|O_APPEND, 0664) < 0) {
		syslog(LOG_ERR, "%s: %m", LF);
D 33
		(void) open("/dev/null", O_WRONLY);
E 33
I 33
		(void) open(_PATH_DEVNULL, O_WRONLY);
E 33
	}
E 30
E 12
D 8
	(void) close(2);			/* set up log file */
	(void) open(LF, FWRONLY|FAPPEND, 0);
D 3
	dup2(2, 1);
	pid = getpid();
E 3
I 3
	dup2(2, 1);				/* closes original connection */
E 8
I 8
D 20
	(void) close(1);			/* set up log file */
	(void) close(2);
D 9
	if (open(LF, FWRONLY|FAPPEND, 0) < 0)
		(void) open("/dev/null", FWRONLY);
E 9
I 9
	if (open(LF, O_WRONLY|O_APPEND) < 0)
		(void) open("/dev/null", O_WRONLY);
E 9
	dup(1);
E 20
I 20
	setgid(getegid());
E 20
E 8
	pid = getpid();				/* for use with lprm */
E 3
	setpgrp(0, pid);
I 16
D 20
	signal(SIGHUP, onintr);
E 16
D 3
	sigset(SIGINT, onintr);			/* for use with lprm */
E 3
I 3
D 9
	sigset(SIGINT, onintr);
E 9
I 9
	signal(SIGINT, onintr);
I 16
	signal(SIGQUIT, onintr);
	signal(SIGTERM, onintr);
E 20
I 20
	signal(SIGHUP, abortpr);
	signal(SIGINT, abortpr);
	signal(SIGQUIT, abortpr);
	signal(SIGTERM, abortpr);
E 20
E 16
E 9
E 3

I 18
D 36
	(void) mktemp(tmpfile);
E 36
I 36
	(void) mktemp(tempfile);
E 36

E 18
	/*
	 * uses short form file names
	 */
	if (chdir(SD) < 0) {
D 20
		log("cannot chdir to %s", SD);
E 20
I 20
		syslog(LOG_ERR, "%s: %m", SD);
E 20
		exit(1);
	}
I 3
	if (stat(LO, &stb) == 0 && (stb.st_mode & 0100))
		exit(0);		/* printing disabled */
E 3
D 9
	if ((lfd = open(LO, FWRONLY|FCREATE|FTRUNCATE|FEXLOCK|FNBLOCK, 0664)) < 0) {
E 9
I 9
D 10
	lfd = open(LO, O_WRONLY|O_CREAT, 0664);
	if (lfd < 0 || flock(lfd, LOCK_EX|LOCK_NB) < 0) {
E 10
I 10
D 14
	lfd = open(LO, O_WRONLY|O_CREAT|O_TRUNC, 0644);
E 14
I 14
	lfd = open(LO, O_WRONLY|O_CREAT, 0644);
E 14
	if (lfd < 0) {
D 20
		log("cannot create %s", LO);
E 20
I 20
		syslog(LOG_ERR, "%s: %s: %m", printer, LO);
E 20
		exit(1);
	}
	if (flock(lfd, LOCK_EX|LOCK_NB) < 0) {
E 10
E 9
		if (errno == EWOULDBLOCK)	/* active deamon present */
			exit(0);
D 10
		log("cannot create %s", LO);
E 10
I 10
D 20
		log("cannot lock %s", LO);
E 20
I 20
		syslog(LOG_ERR, "%s: %s: %m", printer, LO);
E 20
E 10
		exit(1);
	}
I 9
	ftruncate(lfd, 0);
E 9
	/*
	 * write process id for others to know
	 */
	sprintf(line, "%u\n", pid);
	pidoff = i = strlen(line);
D 3
	if (write(lfd, line, i) != i)
E 3
I 3
	if (write(lfd, line, i) != i) {
E 3
D 20
		log("cannot write daemon pid");
E 20
I 20
		syslog(LOG_ERR, "%s: %s: %m", printer, LO);
E 20
D 3
	/*
	 * acquire line printer or remote connection
 	 */
restart:
	if (*LP) {
		for (i = 1; ; i = i < 32 ? i << 1 : i) {
			pfd = open(LP, RW ? FRDWR : FWRONLY, 0);
			if (pfd >= 0)
				break;
			if (errno == ENOENT) {
				log("cannot open %s", LP);
				exit(1);
			}
			if (i == 1)
				status("waiting for %s to become ready (offline ?)", printer);
			sleep(i);
		}
		if (isatty(pfd))
			setty();
		status("%s is ready and printing", printer);
	} else if (RM != NULL) {
		for (i = 1; ; i = i < 512 ? i << 1 : i) {
			pfd = getport();
			if (pfd >= 0) {
				(void) sprintf(line, "\2%s\n", RP);
				nitems = strlen(line);
				if (write(pfd, line, nitems) != nitems)
					break;
				if (noresponse())
					(void) close(pfd);
				else
					break;
			}
			if (i == 1)
				status("waiting for %s to come up", RM);
			sleep(i);
		}
		status("sending to %s", RM);
		remote = 1;
	} else {
		log("no line printer device or remote machine name");
E 3
		exit(1);
	}
	/*
D 3
	 * Start running as daemon instead of root
	 */
	setuid(DU);
	/*
	 * Start up an output filter, if needed.
	 */
	if (OF) {
		int p[2];
		char *cp;

		pipe(p);
		if ((ofilter = dofork(DOABORT)) == 0) {	/* child */
			dup2(p[0], 0);		/* pipe is std in */
			dup2(pfd, 1);		/* printer is std out */
			for (i = 3; i < NOFILE; i++)
				(void) close(i);
			if ((cp = rindex(OF, '/')) == NULL)
				cp = OF;
			else
				cp++;
			execl(OF, cp, 0);
			log("can't execl output filter %s", OF);
			exit(1);
		}
		(void) close(p[0]);		/* close input side */
		ofd = p[1];			/* use pipe for output */
	} else {
		ofd = pfd;
		ofilter = 0;
	}

	/*
E 3
	 * search the spool directory for work and sort by queue order.
	 */
D 3
again:
E 3
	if ((nitems = getq(&queue)) < 0) {
D 20
		log("can't scan spool directory %s", SD);
E 20
I 20
		syslog(LOG_ERR, "%s: can't scan %s", printer, SD);
E 20
		exit(1);
	}
D 3
	if (nitems == 0) {		/* EOF => no work to do */
		if (!SF && !tof)
			(void) write(ofd, FF, strlen(FF));
		if (TR != NULL)		/* output trailer */
			(void) write(ofd, TR, strlen(TR));
E 3
I 3
	if (nitems == 0)		/* no work to do */
E 3
		exit(0);
I 10
	if (stb.st_mode & 01) {		/* reset queue flag */
		if (fchmod(lfd, stb.st_mode & 0776) < 0)
D 20
			log("cannot chmod %s", LO);
E 20
I 20
			syslog(LOG_ERR, "%s: %s: %m", printer, LO);
E 20
	}
E 10
D 3
	}

E 3
I 3
	openpr();			/* open printer or remote */
again:
E 3
	/*
	 * we found something to do now do it --
	 *    write the name of the current control file into the lock file
	 *    so the spool queue program can tell what we're working on
	 */
	for (qp = queue; nitems--; free((char *) q)) {
		q = *qp++;
		if (stat(q->q_name, &stb) < 0)
			continue;
I 47
		errcnt = 0;
E 47
I 3
	restart:
E 3
D 41
		(void) lseek(lfd, pidoff, 0);
E 41
I 41
D 46
		(void) lseek(lfd, (off_t)pidoff, 0);
E 46
I 46
		(void) lseek(lfd, pidoff, 0);
E 46
E 41
		(void) sprintf(line, "%s\n", q->q_name);
		i = strlen(line);
		if (write(lfd, line, i) != i)
D 20
			log("can't write (%d) control file name", errno);
E 20
I 20
			syslog(LOG_ERR, "%s: %s: %m", printer, LO);
E 20
		if (!remote)
			i = printit(q->q_name);
		else
			i = sendit(q->q_name);
D 3
		if (i > 0) {	/* restart daemon to reprint job */
E 3
I 3
		/*
D 10
		 * Check to see if we are supposed to stop printing.
E 10
I 10
		 * Check to see if we are supposed to stop printing or
		 * if we are to rebuild the queue.
E 10
		 */
D 10
		if (stat(LO, &stb) == 0 && (stb.st_mode & 0100))
			goto done;
E 10
I 10
		if (fstat(lfd, &stb) == 0) {
I 20
			/* stop printing before starting next job? */
E 20
			if (stb.st_mode & 0100)
				goto done;
I 20
			/* rebuild queue (after lpc topq) */
E 20
			if (stb.st_mode & 01) {
				for (free((char *) q); nitems--; free((char *) q))
					q = *qp++;
				if (fchmod(lfd, stb.st_mode & 0776) < 0)
D 20
					log("cannot chmod %s", LO);
E 20
I 20
					syslog(LOG_WARNING, "%s: %s: %m",
						printer, LO);
E 20
				break;
			}
		}
E 10
D 14
		/*
		 * Check to see if we should try reprinting the job.
		 */
		if (i > 0) {
E 14
I 14
D 25
		if (i == 0)		/* file ok and printed */
E 25
I 25
		if (i == OK)		/* file ok and printed */
E 25
			count++;
D 25
		else if (i > 0) {	/* try reprinting the job */
E 25
I 25
D 47
		else if (i == REPRINT) { /* try reprinting the job */
E 47
I 47
		else if (i == REPRINT && ++errcnt < 5) {
			/* try reprinting the job */
E 47
E 25
E 14
E 3
D 20
			log("restarting");
E 20
I 20
			syslog(LOG_INFO, "restarting %s", printer);
E 20
			if (ofilter > 0) {
				kill(ofilter, SIGCONT);	/* to be sure */
				(void) close(ofd);
D 49
				while ((i = wait(0)) > 0 && i != ofilter)
E 49
I 49
				while ((i = wait(NULL)) > 0 && i != ofilter)
E 49
					;
				ofilter = 0;
			}
D 3
			(void) close(pfd);
			free((char *) q);
			while (nitems--)
				free((char *) *qp++);
			free((char *) queue);
E 3
I 3
			(void) close(pfd);	/* close printer */
D 18
			(void) lseek(lfd, pidoff, 0);
			if (write(lfd, "\n", 1) != 1)
				log("can't write (%d) control file name", errno);
E 18
I 18
			if (ftruncate(lfd, pidoff) < 0)
D 20
				log("can't truncate lock file (%d)", errno);
E 20
I 20
				syslog(LOG_WARNING, "%s: %s: %m", printer, LO);
E 20
E 18
			openpr();		/* try to reopen printer */
E 3
			goto restart;
I 47
		} else {
			syslog(LOG_WARNING, "%s: job could not be %s (%s)", printer,
				remote ? "sent to remote host" : "printed", q->q_name);
			if (i == REPRINT) {
				/* insure we don't attempt this job again */
				(void) unlink(q->q_name);
				q->q_name[0] = 'd';
				(void) unlink(q->q_name);
				if (logname[0])
					sendmail(logname, FATALERR);
			}
E 47
		}
	}
	free((char *) queue);
I 3
	/*
	 * search the spool directory for more work.
	 */
	if ((nitems = getq(&queue)) < 0) {
D 20
		log("can't scan spool directory %s", SD);
E 20
I 20
		syslog(LOG_ERR, "%s: can't scan %s", printer, SD);
E 20
		exit(1);
	}
	if (nitems == 0) {		/* no more work to do */
	done:
D 14
		if (!SF && !tof)
			(void) write(ofd, FF, strlen(FF));
		if (TR != NULL)		/* output trailer */
			(void) write(ofd, TR, strlen(TR));
E 14
I 14
		if (count > 0) {	/* Files actually printed */
			if (!SF && !tof)
				(void) write(ofd, FF, strlen(FF));
			if (TR != NULL)		/* output trailer */
				(void) write(ofd, TR, strlen(TR));
		}
I 18
D 36
		(void) unlink(tmpfile);
E 36
I 36
		(void) unlink(tempfile);
E 36
E 18
E 14
		exit(0);
	}
E 3
	goto again;
}

char	fonts[4][50];	/* fonts for troff */

D 20
static char ifonts[4][18] = {
E 20
I 20
D 33
char ifonts[4][18] = {
E 20
	"/usr/lib/vfont/R",
	"/usr/lib/vfont/I",
	"/usr/lib/vfont/B",
	"/usr/lib/vfont/S"
E 33
I 33
char ifonts[4][40] = {
	_PATH_VFONTR,
	_PATH_VFONTI,
	_PATH_VFONTB,
	_PATH_VFONTS,
E 33
};

/*
 * The remaining part is the reading of the control file (cf)
 * and performing the various actions.
D 25
 * Returns 0 if everthing was OK, 1 if we should try to reprint the job and
 * -1 if a non-recoverable error occured.
E 25
 */
I 41
static int
E 41
I 8
D 20
static
E 20
E 8
printit(file)
	char *file;
{
	register int i;
D 25
	int bombed = 0;
E 25
I 25
	char *cp;
	int bombed = OK;
E 25

	/*
D 25
	 * open control file
E 25
I 25
	 * open control file; ignore if no longer there.
E 25
	 */
	if ((cfp = fopen(file, "r")) == NULL) {
D 20
		log("control file (%s) open failure <errno = %d>", file, errno);
E 20
I 20
		syslog(LOG_INFO, "%s: %s: %m", printer, file);
E 20
D 25
		return(0);
E 25
I 25
		return(OK);
E 25
	}
	/*
	 * Reset troff fonts.
	 */
	for (i = 0; i < 4; i++)
		strcpy(fonts[i], ifonts[i]);
I 24
D 45
	strcpy(width+2, "0");
E 45
I 45
	sprintf(&width[2], "%d", PW);
E 45
E 24
I 22
	strcpy(indent+2, "0");
E 22

	/*
	 *      read the control file for work to do
	 *
	 *      file format -- first character in the line is a command
	 *      rest of the line is the argument.
	 *      valid commands are:
	 *
I 25
	 *		S -- "stat info" for symbolic link protection
E 25
	 *		J -- "job name" on banner page
	 *		C -- "class name" on banner page
	 *              L -- "literal" user's name to print on banner
	 *		T -- "title" for pr
	 *		H -- "host name" of machine where lpr was done
	 *              P -- "person" user's login name
D 6
	 *              I -- "indent" changes default indents driver
	 *                   must have stty/gtty avaialble
E 6
I 6
	 *              I -- "indent" amount to indent output
I 47
	 *		R -- laser dpi "resolution"
E 47
E 6
	 *              f -- "file name" name of text file to print
	 *		l -- "file name" text file with control chars
	 *		p -- "file name" text file to print with pr(1)
	 *		t -- "file name" troff(1) file to print
I 11
	 *		n -- "file name" ditroff(1) file to print
E 11
	 *		d -- "file name" dvi file to print
	 *		g -- "file name" plot(1G) file to print
	 *		v -- "file name" plain raster file to print
	 *		c -- "file name" cifplot file to print
	 *		1 -- "R font file" for troff
	 *		2 -- "I font file" for troff
	 *		3 -- "B font file" for troff
	 *		4 -- "S font file" for troff
	 *		N -- "name" of file (used by lpq)
	 *              U -- "unlink" name of file to remove
	 *                    (after we print it. (Pass 2 only)).
	 *		M -- "mail" to user when done printing
	 *
	 *      getline reads a line and expands tabs to blanks
	 */

	/* pass 1 */

	while (getline(cfp))
		switch (line[0]) {
		case 'H':
D 14
			strcpy(host, line+1);
E 14
I 14
			strcpy(fromhost, line+1);
E 14
			if (class[0] == '\0')
D 17
				strcpy(class, line+1);
E 17
I 17
				strncpy(class, line+1, sizeof(class)-1);
E 17
			continue;

		case 'P':
D 17
			strcpy(logname, line+1);
E 17
I 17
			strncpy(logname, line+1, sizeof(logname)-1);
E 17
I 3
			if (RS) {			/* restricted */
D 41
				if (getpwnam(logname) == (struct passwd *)0) {
E 41
I 41
				if (getpwnam(logname) == NULL) {
E 41
D 25
					bombed = 2;
E 25
I 25
					bombed = NOACCT;
E 25
D 18
					sendmail(bombed);
E 18
I 18
					sendmail(line+1, bombed);
E 18
					goto pass2;
				}
			}
E 3
			continue;

I 25
		case 'S':
			cp = line+1;
			i = 0;
			while (*cp >= '0' && *cp <= '9')
				i = i * 10 + (*cp++ - '0');
			fdev = i;
			cp++;
			i = 0;
			while (*cp >= '0' && *cp <= '9')
				i = i * 10 + (*cp++ - '0');
			fino = i;
			continue;

E 25
		case 'J':
			if (line[1] != '\0')
D 17
				strcpy(jobname, line+1);
E 17
I 17
				strncpy(jobname, line+1, sizeof(jobname)-1);
E 17
			else
				strcpy(jobname, " ");
			continue;

		case 'C':
			if (line[1] != '\0')
D 17
				strcpy(class, line+1);
E 17
I 17
				strncpy(class, line+1, sizeof(class)-1);
E 17
			else if (class[0] == '\0')
D 18
				gethostname(class, sizeof (class));
E 18
I 18
				gethostname(class, sizeof(class));
E 18
			continue;

		case 'T':	/* header title for pr */
D 17
			strcpy(title, line+1);
E 17
I 17
			strncpy(title, line+1, sizeof(title)-1);
E 17
			continue;

		case 'L':	/* identification line */
D 26
			if (!SH)
E 26
I 26
			if (!SH && !HL)
E 26
				banner(line+1, jobname);
			continue;

		case '1':	/* troff fonts */
		case '2':
		case '3':
		case '4':
			if (line[1] != '\0')
				strcpy(fonts[line[0]-'1'], line+1);
			continue;

		case 'W':	/* page width */
D 17
			strcpy(width+2, line+1);
E 17
I 17
			strncpy(width+2, line+1, sizeof(width)-3);
E 17
			continue;

I 6
		case 'I':	/* indent amount */
D 17
			strcpy(indent+2, line+1);
E 17
I 17
			strncpy(indent+2, line+1, sizeof(indent)-3);
E 17
			continue;

E 6
		default:	/* some file to print */
D 18
			if ((i = print(line[0], line+1)) > 0) {
E 18
I 18
			switch (i = print(line[0], line+1)) {
D 25
			case -1:
				if (!bombed)
					bombed = 1;
E 25
I 25
			case ERROR:
				if (bombed == OK)
					bombed = FATALERR;
E 25
				break;
D 25
			case 1:
E 25
I 25
			case REPRINT:
E 25
E 18
				(void) fclose(cfp);
D 25
				return(1);
D 18
			} else if (i < 0)
				bombed = 1;
E 18
I 18
			case 2:
				bombed = 3;
E 25
I 25
				return(REPRINT);
			case FILTERERR:
			case ACCESS:
				bombed = i;
E 25
				sendmail(logname, bombed);
			}
E 18
			title[0] = '\0';
			continue;

D 6
		case 'I':
E 6
		case 'N':
		case 'U':
		case 'M':
I 47
		case 'R':
E 47
			continue;
		}

	/* pass 2 */

I 3
pass2:
E 3
	fseek(cfp, 0L, 0);
	while (getline(cfp))
		switch (line[0]) {
I 26
		case 'L':	/* identification line */
			if (!SH && HL)
				banner(line+1, jobname);
			continue;

E 26
		case 'M':
D 3
			sendmail(bombed);
E 3
I 3
D 18
			if (bombed != 2)		/* already sent if 2 */
				sendmail(bombed);
E 18
I 18
D 25
			if (bombed < 2)		/* already sent if >= 2 */
E 25
I 25
			if (bombed < NOACCT)	/* already sent if >= NOACCT */
E 25
				sendmail(line+1, bombed);
E 18
E 3
			continue;

		case 'U':
			(void) unlink(line+1);
		}
	/*
D 18
	 * clean-up incase another control file exists
E 18
I 18
	 * clean-up in case another control file exists
E 18
	 */
	(void) fclose(cfp);
	(void) unlink(file);
D 14
	return(0);
E 14
I 14
D 25
	return(bombed ? -1 : 0);
E 25
I 25
	return(bombed == OK ? OK : ERROR);
E 25
E 14
}

/*
 * Print a file.
D 11
 * Set up the chain [ PR [ | {IF, OF} ] ] or {IF, TF, CF, VF}.
E 11
I 11
 * Set up the chain [ PR [ | {IF, OF} ] ] or {IF, RF, TF, NF, DF, CF, VF}.
E 11
D 18
 * Return -1 if a non-recoverable error occured, 1 if a recoverable error and
E 18
I 18
 * Return -1 if a non-recoverable error occured,
 * 2 if the filter detected some errors (but printed the job anyway),
 * 1 if we should try to reprint this job and
E 18
 * 0 if all is well.
 * Note: all filters take stdin as the file, stdout as the printer,
 * stderr as the log file, and must not ignore SIGINT.
 */
I 41
static int
E 41
I 8
D 20
static
E 20
E 8
print(format, file)
	int format;
	char *file;
{
D 18
	register int n, fi, fo;
E 18
I 18
	register int n;
E 18
	register char *prog;
I 18
	int fi, fo;
I 36
	FILE *fp;
E 36
E 18
	char *av[15], buf[BUFSIZ];
	int pid, p[2], stopped = 0;
	union wait status;
I 25
	struct stat stb;
E 25

D 9
	if ((fi = open(file, FRDONLY, 0)) < 0) {
E 9
I 9
D 20
	if ((fi = open(file, O_RDONLY)) < 0) {
E 9
		log("%s: open failure <errno = %d>", file, errno);
E 20
I 20
D 25
	if ((fi = open(file, O_RDONLY)) < 0)
E 20
		return(-1);
E 25
I 25
	if (lstat(file, &stb) < 0 || (fi = open(file, O_RDONLY)) < 0)
		return(ERROR);
	/*
	 * Check to see if data file is a symbolic link. If so, it should
	 * still point to the same file or someone is trying to print
	 * something he shouldn't.
	 */
	if ((stb.st_mode & S_IFMT) == S_IFLNK && fstat(fi, &stb) == 0 &&
	    (stb.st_dev != fdev || stb.st_ino != fino))
		return(ACCESS);
E 25
D 20
	}
E 20
	if (!SF && !tof) {		/* start on a fresh page */
		(void) write(ofd, FF, strlen(FF));
		tof = 1;
	}
	if (IF == NULL && (format == 'f' || format == 'l')) {
		tof = 0;
		while ((n = read(fi, buf, BUFSIZ)) > 0)
			if (write(ofd, buf, n) != n) {
				(void) close(fi);
D 25
				return(1);
E 25
I 25
				return(REPRINT);
E 25
			}
		(void) close(fi);
D 25
		return(0);
E 25
I 25
		return(OK);
E 25
	}
	switch (format) {
	case 'p':	/* print file using 'pr' */
		if (IF == NULL) {	/* use output filter */
D 33
			prog = PR;
E 33
I 33
			prog = _PATH_PR;
E 33
			av[0] = "pr";
			av[1] = width;
			av[2] = length;
			av[3] = "-h";
			av[4] = *title ? title : " ";
			av[5] = 0;
			fo = ofd;
			goto start;
		}
		pipe(p);
		if ((prchild = dofork(DORETURN)) == 0) {	/* child */
			dup2(fi, 0);		/* file is stdin */
			dup2(p[1], 1);		/* pipe is stdout */
I 46
			closelog();
E 46
			for (n = 3; n < NOFILE; n++)
				(void) close(n);
D 33
			execl(PR, "pr", width, length, "-h", *title ? title : " ", 0);
D 20
			log("cannot execl %s", PR);
E 20
I 20
			syslog(LOG_ERR, "cannot execl %s", PR);
E 33
I 33
			execl(_PATH_PR, "pr", width, length,
			    "-h", *title ? title : " ", 0);
			syslog(LOG_ERR, "cannot execl %s", _PATH_PR);
E 33
E 20
			exit(2);
		}
		(void) close(p[1]);		/* close output side */
		(void) close(fi);
		if (prchild < 0) {
			prchild = 0;
			(void) close(p[0]);
D 25
			return(-1);
E 25
I 25
			return(ERROR);
E 25
		}
		fi = p[0];			/* use pipe for input */
	case 'f':	/* print plain text file */
		prog = IF;
		av[1] = width;
		av[2] = length;
D 6
		n = 3;
E 6
I 6
		av[3] = indent;
		n = 4;
E 6
		break;
	case 'l':	/* like 'f' but pass control characters */
		prog = IF;
D 15
		av[1] = "-l";
E 15
I 15
		av[1] = "-c";
E 15
		av[2] = width;
		av[3] = length;
D 6
		n = 4;
E 6
I 6
		av[4] = indent;
		n = 5;
E 6
		break;
I 3
	case 'r':	/* print a fortran text file */
		prog = RF;
		av[1] = width;
		av[2] = length;
		n = 3;
		break;
E 3
	case 't':	/* print troff output */
I 11
	case 'n':	/* print ditroff output */
E 11
D 3
	case 'd':	/* print troff output */
E 3
I 3
	case 'd':	/* print tex output */
E 3
		(void) unlink(".railmag");
D 3
		if ((fo = creat(".railmag", 0666)) < 0) {
E 3
I 3
		if ((fo = creat(".railmag", FILMOD)) < 0) {
E 3
D 20
			log("cannot create .railmag");
E 20
I 20
			syslog(LOG_ERR, "%s: cannot create .railmag", printer);
E 20
			(void) unlink(".railmag");
		} else {
			for (n = 0; n < 4; n++) {
				if (fonts[n][0] != '/')
D 33
					(void) write(fo, "/usr/lib/vfont/", 15);
E 33
I 33
D 40
					(void) write(fo, _PATH_VFONT, 15);
E 40
I 40
					(void) write(fo, _PATH_VFONT,
					    sizeof(_PATH_VFONT) - 1);
E 40
E 33
				(void) write(fo, fonts[n], strlen(fonts[n]));
				(void) write(fo, "\n", 1);
			}
			(void) close(fo);
		}
D 11
		prog = (format == 't') ? TF : DF;
E 11
I 11
		prog = (format == 't') ? TF : (format == 'n') ? NF : DF;
E 11
D 3
		n = 1;
E 3
I 3
		av[1] = pxwidth;
		av[2] = pxlength;
		n = 3;
E 3
		break;
	case 'c':	/* print cifplot output */
		prog = CF;
D 3
		n = 1;
E 3
I 3
		av[1] = pxwidth;
		av[2] = pxlength;
		n = 3;
E 3
		break;
	case 'g':	/* print plot(1G) output */
		prog = GF;
D 3
		n = 1;
E 3
I 3
		av[1] = pxwidth;
		av[2] = pxlength;
		n = 3;
E 3
		break;
	case 'v':	/* print raster output */
		prog = VF;
D 3
		n = 1;
E 3
I 3
		av[1] = pxwidth;
		av[2] = pxlength;
		n = 3;
E 3
		break;
	default:
		(void) close(fi);
D 20
		log("illegal format character '%c'", format);
E 20
I 20
		syslog(LOG_ERR, "%s: illegal format character '%c'",
			printer, format);
E 20
D 25
		return(-1);
E 25
I 25
		return(ERROR);
E 25
	}
I 47
	if (prog == NULL) {
		(void) close(fi);
		syslog(LOG_ERR,
		   "%s: no filter found in printcap for format character '%c'",
		   printer, format);
		return(ERROR);
	}
E 47
	if ((av[0] = rindex(prog, '/')) != NULL)
		av[0]++;
	else
		av[0] = prog;
	av[n++] = "-n";
	av[n++] = logname;
	av[n++] = "-h";
D 14
	av[n++] = host;
E 14
I 14
	av[n++] = fromhost;
E 14
	av[n++] = AF;
	av[n] = 0;
	fo = pfd;
	if (ofilter > 0) {		/* stop output filter */
		write(ofd, "\031\1", 2);
D 39
		while ((pid = wait3(&status, WUNTRACED, 0)) > 0 && pid != ofilter)
E 39
I 39
		while ((pid =
		    wait3((int *)&status, WUNTRACED, 0)) > 0 && pid != ofilter)
E 39
			;
		if (status.w_stopval != WSTOPPED) {
			(void) close(fi);
D 20
			log("output filter died (%d)", status.w_retcode);
E 20
I 20
D 47
			syslog(LOG_WARNING, "%s: output filter died (%d)",
				printer, status.w_retcode);
E 47
I 47
			syslog(LOG_WARNING,
				"%s: output filter died (retcode=%d termsig=%d)",
				printer, status.w_retcode, status.w_termsig);
E 47
E 20
D 25
			return(1);
E 25
I 25
			return(REPRINT);
E 25
		}
		stopped++;
	}
start:
	if ((child = dofork(DORETURN)) == 0) {	/* child */
		dup2(fi, 0);
		dup2(fo, 1);
I 18
D 23
		n = open(tmpfile, O_WRONLY|O_CREAT, 0664);
E 23
I 23
D 36
		n = open(tmpfile, O_WRONLY|O_CREAT|O_TRUNC, 0664);
E 36
I 36
		n = open(tempfile, O_WRONLY|O_CREAT|O_TRUNC, 0664);
E 36
E 23
		if (n >= 0)
			dup2(n, 2);
I 46
		closelog();
E 46
E 18
		for (n = 3; n < NOFILE; n++)
			(void) close(n);
		execv(prog, av);
D 20
		log("cannot execl %s", prog);
E 20
I 20
		syslog(LOG_ERR, "cannot execv %s", prog);
E 20
		exit(2);
	}
	(void) close(fi);
	if (child < 0)
		status.w_retcode = 100;
	else
D 39
		while ((pid = wait(&status)) > 0 && pid != child)
E 39
I 39
		while ((pid = wait((int *)&status)) > 0 && pid != child)
E 39
			;
	child = 0;
	prchild = 0;
	if (stopped) {		/* restart output filter */
		if (kill(ofilter, SIGCONT) < 0) {
D 20
			log("cannot restart output filter");
E 20
I 20
			syslog(LOG_ERR, "cannot restart output filter");
E 20
			exit(1);
		}
	}
	tof = 0;
I 36

	/* Copy filter output to "lf" logfile */
	if (fp = fopen(tempfile, "r")) {
D 42
		char tbuf[512];

E 42
		while (fgets(buf, sizeof(buf), fp))
			fputs(buf, stderr);
D 42
		close(fp);
E 42
I 42
		fclose(fp);
E 42
	}

E 36
D 18
	if (!WIFEXITED(status) || status.w_retcode > 1) {
		log("Daemon Filter '%c' Malfunction (%d)", format, status.w_retcode);
E 18
I 18
	if (!WIFEXITED(status)) {
D 20
		log("Daemon filter '%c' terminated (%d)", format, status.w_termsig);
E 20
I 20
D 47
		syslog(LOG_WARNING, "%s: Daemon filter '%c' terminated (%d)",
E 47
I 47
		syslog(LOG_WARNING, "%s: filter '%c' terminated (termsig=%d)",
E 47
			printer, format, status.w_termsig);
E 20
E 18
D 25
		return(-1);
D 18
	} else if (status.w_retcode == 1)
		return(1);
	tof = 1;
	return(0);
E 18
I 18
	} else if (status.w_retcode > 2) {
E 25
I 25
		return(ERROR);
	}
	switch (status.w_retcode) {
	case 0:
		tof = 1;
		return(OK);
	case 1:
		return(REPRINT);
D 47
	default:
E 25
D 20
		log("Daemon filter '%c' exited (%d)", format, status.w_retcode);
E 20
I 20
		syslog(LOG_WARNING, "%s: Daemon filter '%c' exited (%d)",
			printer, format, status.w_retcode);
E 47
E 20
D 25
		return(-1);
	} else if (status.w_retcode == 0)
		tof = 1;
	return(status.w_retcode);
E 25
I 25
	case 2:
		return(ERROR);
I 47
	default:
		syslog(LOG_WARNING, "%s: filter '%c' exited (retcode=%d)",
			printer, format, status.w_retcode);
		return(FILTERERR);
E 47
	}
E 25
E 18
}

/*
 * Send the daemon control file (cf) and any data files.
 * Return -1 if a non-recoverable error occured, 1 if a recoverable error and
 * 0 if all is well.
 */
I 41
static int
E 41
I 8
D 20
static
E 20
E 8
sendit(file)
	char *file;
{
D 25
	register int linelen, err = 0;
	char last[132];
E 25
I 25
	register int i, err = OK;
	char *cp, last[BUFSIZ];
E 25

	/*
	 * open control file
	 */
D 20
	if ((cfp = fopen(file, "r")) == NULL) {
		log("control file (%s) open failure <errno = %d>", file, errno);
E 20
I 20
	if ((cfp = fopen(file, "r")) == NULL)
E 20
D 25
		return(0);
E 25
I 25
		return(OK);
E 25
D 20
	}
E 20
	/*
	 *      read the control file for work to do
	 *
	 *      file format -- first character in the line is a command
	 *      rest of the line is the argument.
	 *      commands of interest are:
	 *
	 *            a-z -- "file name" name of file to print
	 *              U -- "unlink" name of file to remove
	 *                    (after we print it. (Pass 2 only)).
	 */

	/*
	 * pass 1
	 */
	while (getline(cfp)) {
	again:
I 25
		if (line[0] == 'S') {
			cp = line+1;
			i = 0;
			while (*cp >= '0' && *cp <= '9')
				i = i * 10 + (*cp++ - '0');
			fdev = i;
			cp++;
			i = 0;
			while (*cp >= '0' && *cp <= '9')
				i = i * 10 + (*cp++ - '0');
			fino = i;
			continue;
		}
E 25
		if (line[0] >= 'a' && line[0] <= 'z') {
			strcpy(last, line);
D 25
			while (linelen = getline(cfp))
E 25
I 25
			while (i = getline(cfp))
E 25
				if (strcmp(last, line))
					break;
D 25
			if ((err = sendfile('\3', last+1)) > 0) {
				(void) fclose(cfp);
				return(1);
			} else if (err)
E 25
I 25
			switch (sendfile('\3', last+1)) {
			case OK:
				if (i)
					goto again;
E 25
				break;
D 25
			if (linelen)
				goto again;
E 25
I 25
			case REPRINT:
				(void) fclose(cfp);
				return(REPRINT);
			case ACCESS:
				sendmail(logname, ACCESS);
			case ERROR:
				err = ERROR;
			}
E 25
			break;
		}
	}
D 25
	if (!err && sendfile('\2', file) > 0) {
E 25
I 25
	if (err == OK && sendfile('\2', file) > 0) {
E 25
		(void) fclose(cfp);
D 25
		return(1);
E 25
I 25
		return(REPRINT);
E 25
	}
	/*
	 * pass 2
	 */
	fseek(cfp, 0L, 0);
	while (getline(cfp))
		if (line[0] == 'U')
			(void) unlink(line+1);
	/*
D 25
	 * clean-up incase another control file exists
E 25
I 25
	 * clean-up in case another control file exists
E 25
	 */
	(void) fclose(cfp);
	(void) unlink(file);
D 25
	return(0);
E 25
I 25
	return(err);
E 25
}

/*
 * Send a data file to the remote machine and spool it.
 * Return positive if we should try resending.
 */
I 41
static int
E 41
I 8
D 20
static
E 20
E 8
sendfile(type, file)
D 41
	char type, *file;
E 41
I 41
	int type;
	char *file;
E 41
{
	register int f, i, amt;
	struct stat stb;
	char buf[BUFSIZ];
D 20
	int sizerr;
E 20
I 20
	int sizerr, resp;
E 20

D 9
	if ((f = open(file, FRDONLY, 0)) < 0 || fstat(f, &stb) < 0) {
E 9
I 9
D 20
	if ((f = open(file, O_RDONLY)) < 0 || fstat(f, &stb) < 0) {
E 9
		log("file (%s) open failure <errno = %d>", file, errno);
E 20
I 20
D 25
	if ((f = open(file, O_RDONLY)) < 0 || fstat(f, &stb) < 0)
E 20
		return(-1);
E 25
I 25
	if (lstat(file, &stb) < 0 || (f = open(file, O_RDONLY)) < 0)
		return(ERROR);
	/*
	 * Check to see if data file is a symbolic link. If so, it should
	 * still point to the same file or someone is trying to print something
	 * he shouldn't.
	 */
	if ((stb.st_mode & S_IFMT) == S_IFLNK && fstat(f, &stb) == 0 &&
	    (stb.st_dev != fdev || stb.st_ino != fino))
		return(ACCESS);
E 25
D 20
	}
E 20
D 41
	(void) sprintf(buf, "%c%d %s\n", type, stb.st_size, file);
E 41
I 41
D 46
	(void) sprintf(buf, "%c%qd %s\n", type, stb.st_size, file);
E 46
I 46
	(void) sprintf(buf, "%c%ld %s\n", type, (long)stb.st_size, file);
E 46
E 41
	amt = strlen(buf);
D 7
	if (write(pfd, buf, amt) != amt)
E 7
I 7
D 20
	if (write(pfd, buf, amt) != amt) {
		(void) close(f);
E 7
		return(1);
E 20
I 20
	for (i = 0;  ; i++) {
		if (write(pfd, buf, amt) != amt ||
		    (resp = response()) < 0 || resp == '\1') {
			(void) close(f);
D 25
			return(1);
E 25
I 25
			return(REPRINT);
E 25
		} else if (resp == '\0')
			break;
		if (i == 0)
D 41
			status("no space on remote; waiting for queue to drain");
E 41
I 41
			pstatus("no space on remote; waiting for queue to drain");
E 41
		if (i == 10)
D 28
			syslog(LOG_SALERT, "%s: can't send to %s; queue full",
E 28
I 28
			syslog(LOG_ALERT, "%s: can't send to %s; queue full",
E 28
				printer, RM);
		sleep(5 * 60);
E 20
D 7
	if (noresponse())
E 7
I 7
	}
D 20
	if (noresponse()) {
		(void) close(f);
E 7
		return(1);
I 7
	}
E 20
I 20
	if (i)
D 41
		status("sending to %s", RM);
E 41
I 41
		pstatus("sending to %s", RM);
E 41
E 20
E 7
	sizerr = 0;
	for (i = 0; i < stb.st_size; i += BUFSIZ) {
		amt = BUFSIZ;
		if (i + amt > stb.st_size)
			amt = stb.st_size - i;
		if (sizerr == 0 && read(f, buf, amt) != amt)
			sizerr = 1;
D 7
		if (write(pfd, buf, amt) != amt)
E 7
I 7
		if (write(pfd, buf, amt) != amt) {
			(void) close(f);
E 7
D 25
			return(1);
E 25
I 25
			return(REPRINT);
E 25
I 7
		}
E 7
	}
I 41




E 41
	(void) close(f);
	if (sizerr) {
D 20
		log("%s: changed size", file);
E 20
I 20
		syslog(LOG_INFO, "%s: %s: changed size", printer, file);
E 20
D 25
		(void) write(pfd, "\1", 1);  /* tell recvjob to ignore this file */
D 20
		return(-1);
	}
	if (write(pfd, "", 1) != 1)
		return(1);
	if (noresponse())
		return(1);
	return(0);
E 20
I 20
		i = -1;
	} else if (write(pfd, "", 1) != 1)
		i = 1;
	else if (response())
		i = 1;
	else
		i = 0;
	return(i);
E 25
I 25
		/* tell recvjob to ignore this file */
		(void) write(pfd, "\1", 1);
		return(ERROR);
	}
	if (write(pfd, "", 1) != 1 || response())
		return(REPRINT);
	return(OK);
E 25
E 20
}

/*
 * Check to make sure there have been no errors and that both programs
 * are in sync with eachother.
 * Return non-zero if the connection was lost.
 */
I 41
static char
E 41
D 20
static
noresponse()
E 20
I 20
response()
E 20
{
	char resp;

D 20
	if (read(pfd, &resp, 1) != 1 || resp != '\0') {
		log("lost connection or error in recvjob");
		return(1);
E 20
I 20
	if (read(pfd, &resp, 1) != 1) {
		syslog(LOG_INFO, "%s: lost connection", printer);
		return(-1);
E 20
	}
D 20
	return(0);
E 20
I 20
	return(resp);
E 20
}

/*
 * Banner printing stuff
 */
I 41
static void
E 41
I 8
D 20
static
E 20
E 8
banner(name1, name2)
	char *name1, *name2;
{
	time_t tvec;
	extern char *ctime();

	time(&tvec);
	if (!SF && !tof)
		(void) write(ofd, FF, strlen(FF));
	if (SB) {	/* short banner only */
		if (class[0]) {
			(void) write(ofd, class, strlen(class));
			(void) write(ofd, ":", 1);
		}
		(void) write(ofd, name1, strlen(name1));
		(void) write(ofd, "  Job: ", 7);
		(void) write(ofd, name2, strlen(name2));
		(void) write(ofd, "  Date: ", 8);
		(void) write(ofd, ctime(&tvec), 24);
		(void) write(ofd, "\n", 1);
	} else {	/* normal banner */
		(void) write(ofd, "\n\n\n", 3);
		scan_out(ofd, name1, '\0');
		(void) write(ofd, "\n\n", 2);
		scan_out(ofd, name2, '\0');
		if (class[0]) {
			(void) write(ofd,"\n\n\n",3);
			scan_out(ofd, class, '\0');
		}
		(void) write(ofd, "\n\n\n\n\t\t\t\t\tJob:  ", 15);
		(void) write(ofd, name2, strlen(name2));
		(void) write(ofd, "\n\t\t\t\t\tDate: ", 12);
		(void) write(ofd, ctime(&tvec), 24);
		(void) write(ofd, "\n", 1);
	}
	if (!SF)
		(void) write(ofd, FF, strlen(FF));
	tof = 1;
}

D 8
char *
E 8
I 8
D 20
static char *
E 20
I 20
D 41
char *
E 41
I 41
static char *
E 41
E 20
E 8
scnline(key, p, c)
D 41
	register char key, *p;
	char c;
E 41
I 41
	register int key;
	register char *p;
	int c;
E 41
{
	register scnwidth;

	for (scnwidth = WIDTH; --scnwidth;) {
		key <<= 1;
		*p++ = key & 0200 ? c : BACKGND;
	}
	return (p);
}

#define TRC(q)	(((q)-' ')&0177)

I 41
static void
E 41
I 8
D 20
static
E 20
E 8
scan_out(scfd, scsp, dlm)
D 41
	int scfd;
	char *scsp, dlm;
E 41
I 41
	int scfd, dlm;
	char *scsp;
E 41
{
	register char *strp;
	register nchrs, j;
	char outbuf[LINELEN+1], *sp, c, cc;
	int d, scnhgt;
	extern char scnkey[][HEIGHT];	/* in lpdchar.c */

	for (scnhgt = 0; scnhgt++ < HEIGHT+DROP; ) {
		strp = &outbuf[0];
		sp = scsp;
		for (nchrs = 0; ; ) {
			d = dropit(c = TRC(cc = *sp++));
			if ((!d && scnhgt > HEIGHT) || (scnhgt <= DROP && d))
				for (j = WIDTH; --j;)
					*strp++ = BACKGND;
			else
				strp = scnline(scnkey[c][scnhgt-1-d], strp, cc);
			if (*sp == dlm || *sp == '\0' || nchrs++ >= PW/(WIDTH+1)-1)
				break;
			*strp++ = BACKGND;
			*strp++ = BACKGND;
		}
		while (*--strp == BACKGND && strp >= outbuf)
			;
		strp++;
		*strp++ = '\n';	
		(void) write(scfd, outbuf, strp-outbuf);
	}
}

I 41
static int
E 41
I 8
D 20
static
E 20
E 8
dropit(c)
D 41
	char c;
E 41
I 41
	int c;
E 41
{
	switch(c) {

	case TRC('_'):
	case TRC(';'):
	case TRC(','):
	case TRC('g'):
	case TRC('j'):
	case TRC('p'):
	case TRC('q'):
	case TRC('y'):
		return (DROP);

	default:
		return (0);
	}
}

/*
 * sendmail ---
 *   tell people about job completion
 */
I 41
static void
E 41
I 8
D 20
static
E 20
E 8
D 18
sendmail(bombed)
E 18
I 18
sendmail(user, bombed)
	char *user;
E 18
	int bombed;
{
D 18
	static int p[2];
E 18
	register int i;
D 18
	int stat;
E 18
I 18
	int p[2], s;
E 18
	register char *cp;
	char buf[100];
I 18
	struct stat stb;
	FILE *fp;
E 18

	pipe(p);
D 18
	if ((stat = dofork(DORETURN)) == 0) {		/* child */
E 18
I 18
	if ((s = dofork(DORETURN)) == 0) {		/* child */
E 18
		dup2(p[0], 0);
I 46
		closelog();
E 46
		for (i = 3; i < NOFILE; i++)
			(void) close(i);
D 33
		if ((cp = rindex(MAIL, '/')) != NULL)
E 33
I 33
		if ((cp = rindex(_PATH_SENDMAIL, '/')) != NULL)
E 33
			cp++;
D 41
		else
E 41
I 41
	else
E 41
D 33
			cp = MAIL;
E 33
I 33
			cp = _PATH_SENDMAIL;
E 33
D 14
		sprintf(buf, "%s@%s", line+1, host);
E 14
I 14
D 18
		sprintf(buf, "%s@%s", line+1, fromhost);
E 18
I 18
		sprintf(buf, "%s@%s", user, fromhost);
E 18
E 14
D 33
		execl(MAIL, cp, buf, 0);
E 33
I 33
		execl(_PATH_SENDMAIL, cp, buf, 0);
E 33
		exit(0);
D 18
	} else if (stat > 0) {				/* parent */
E 18
I 18
	} else if (s > 0) {				/* parent */
E 18
		dup2(p[1], 1);
D 14
		printf("To: %s\n", line+1);
E 14
I 14
D 18
		printf("To: %s@%s\n", line+1, fromhost);
E 18
I 18
		printf("To: %s@%s\n", user, fromhost);
E 18
E 14
D 47
		printf("Subject: printer job\n\n");
E 47
I 47
		printf("Subject: %s printer job \"%s\"\n", printer,
			*jobname ? jobname : "<unknown>");
		printf("Reply-To: root@%s\n\n", host);
E 47
		printf("Your printer job ");
		if (*jobname)
			printf("(%s) ", jobname);
D 3
		if (bombed)
			printf("bombed\n");
		else
			printf("is done\n");
E 3
I 3
		switch (bombed) {
D 25
		case 0:
E 25
I 25
		case OK:
E 25
			printf("\ncompleted successfully\n");
I 48
			cp = "OK";
E 48
			break;
		default:
D 25
		case 1:
E 25
I 25
		case FATALERR:
E 25
			printf("\ncould not be printed\n");
I 48
			cp = "FATALERR";
E 48
			break;
D 25
		case 2:
E 25
I 25
		case NOACCT:
E 25
			printf("\ncould not be printed without an account on %s\n", host);
I 48
			cp = "NOACCT";
E 48
			break;
I 18
D 25
		case 3:
E 25
I 25
		case FILTERERR:
E 25
D 36
			if (stat(tmpfile, &stb) < 0 || stb.st_size == 0 ||
			    (fp = fopen(tmpfile, "r")) == NULL) {
E 36
I 36
			if (stat(tempfile, &stb) < 0 || stb.st_size == 0 ||
			    (fp = fopen(tempfile, "r")) == NULL) {
E 36
D 47
				printf("\nwas printed but had some errors\n");
E 47
I 47
				printf("\nhad some errors and may not have printed\n");
E 47
				break;
			}
D 47
			printf("\nwas printed but had the following errors:\n");
E 47
I 47
			printf("\nhad the following errors and may not have printed:\n");
E 47
			while ((i = getc(fp)) != EOF)
				putchar(i);
			(void) fclose(fp);
I 48
			cp = "FILTERERR";
E 48
I 25
			break;
		case ACCESS:
			printf("\nwas not printed because it was not linked to the original file\n");
I 48
			cp = "ACCESS";
E 48
E 25
E 18
		}
E 3
		fflush(stdout);
		(void) close(1);
	}
	(void) close(p[0]);
	(void) close(p[1]);
D 18
	wait(&stat);
E 18
I 18
D 49
	wait(&s);
E 49
I 49
	wait(NULL);
E 49
I 48
	syslog(LOG_INFO, "mail sent to user %s about job %s on printer %s (%s)",
		user, *jobname ? jobname : "<unknown>", printer, cp);
E 48
E 18
}

/*
 * dofork - fork with retries on failure
 */
I 41
static int
E 41
I 8
D 20
static
E 20
E 8
dofork(action)
	int action;
{
	register int i, pid;

	for (i = 0; i < 20; i++) {
D 3
		if ((pid = fork()) < 0)
E 3
I 3
		if ((pid = fork()) < 0) {
E 3
			sleep((unsigned)(i*i));
D 3
		else
			return(pid);
E 3
I 3
			continue;
		}
		/*
		 * Child should run as daemon instead of root
		 */
		if (pid == 0)
			setuid(DU);
		return(pid);
E 3
	}
D 20
	log("can't fork");
E 20
I 20
	syslog(LOG_ERR, "can't fork");
E 20

	switch (action) {
	case DORETURN:
		return (-1);
	default:
D 20
		log("bad action (%d) to dofork", action);
E 20
I 20
		syslog(LOG_ERR, "bad action (%d) to dofork", action);
E 20
		/*FALL THRU*/
	case DOABORT:
		exit(1);
	}
	/*NOTREACHED*/
}

/*
D 16
 * Cleanup child processes when a SIGINT is caught.
E 16
I 16
D 20
 * Cleanup child processes when a signal is caught.
E 20
I 20
 * Kill child processes to abort current job.
E 20
E 16
 */
I 39
D 41
void
E 39
I 8
D 20
static
E 8
onintr()
E 20
I 20
abortpr()
E 41
I 41
static void
abortpr(signo)
	int signo;
E 41
E 20
{
I 18
D 36
	(void) unlink(tmpfile);
E 36
I 36
	(void) unlink(tempfile);
E 36
E 18
	kill(0, SIGINT);
	if (ofilter > 0)
		kill(ofilter, SIGCONT);
D 39
	while (wait(0) > 0)
E 39
I 39
	while (wait(NULL) > 0)
E 39
		;
	exit(0);
}

I 41
static void
E 41
I 8
D 20
static
E 20
E 8
init()
{
	int status;
I 35
	char *s;
E 35

D 10
	if ((status = pgetent(line, printer)) < 0) {
		log("can't open printer description file");
		exit(1);
	} else if (status == 0) {
		log("unknown printer");
		exit(1);
	}
E 10
I 10
D 29
	if ((status = pgetent(line, printer)) < 0)
		fatal("can't open printer description file");
	else if (status == 0)
		fatal("unknown printer");
E 29
I 29
D 42
	if ((status = pgetent(line, printer)) < 0) {
E 42
I 42
	if ((status = cgetent(&bp, printcapdb, printer)) == -2) {
E 42
		syslog(LOG_ERR, "can't open printer description file");
		exit(1);
D 42
	} else if (status == 0) {
E 42
I 42
	} else if (status == -1) {
E 42
		syslog(LOG_ERR, "unknown printer: %s", printer);
		exit(1);
D 42
	}
E 29
E 10
	if ((LP = pgetstr("lp", &bp)) == NULL)
E 42
I 42
	} else if (status == -3)
		fatal("potential reference loop detected in printcap file");

	if (cgetstr(bp, "lp", &LP) == -1)
E 42
D 33
		LP = DEFDEVLP;
E 33
I 33
		LP = _PATH_DEFDEVLP;
E 33
D 42
	if ((RP = pgetstr("rp", &bp)) == NULL)
E 42
I 42
	if (cgetstr(bp, "rp", &RP) == -1)
E 42
D 3
		RP = printer;
E 3
I 3
		RP = DEFLP;
E 3
D 42
	if ((LO = pgetstr("lo", &bp)) == NULL)
E 42
I 42
	if (cgetstr(bp, "lo", &LO) == -1)
E 42
		LO = DEFLOCK;
D 42
	if ((ST = pgetstr("st", &bp)) == NULL)
E 42
I 42
	if (cgetstr(bp, "st", &ST) == -1)
E 42
		ST = DEFSTAT;
D 42
	if ((LF = pgetstr("lf", &bp)) == NULL)
E 42
I 42
	if (cgetstr(bp, "lf", &LF) == -1)
E 42
D 33
		LF = DEFLOGF;
E 33
I 33
		LF = _PATH_CONSOLE;
E 33
D 42
	if ((SD = pgetstr("sd", &bp)) == NULL)
E 42
I 42
	if (cgetstr(bp, "sd", &SD) == -1)
E 42
D 33
		SD = DEFSPOOL;
E 33
I 33
		SD = _PATH_DEFSPOOL;
E 33
D 42
	if ((DU = pgetnum("du")) < 0)
E 42
I 42
	if (cgetnum(bp, "du", &DU) < 0)
E 42
		DU = DEFUID;
D 42
	if ((FF = pgetstr("ff", &bp)) == NULL)
E 42
I 42
	if (cgetstr(bp,"ff", &FF) == -1)
E 42
		FF = DEFFF;
D 42
	if ((PW = pgetnum("pw")) < 0)
E 42
I 42
	if (cgetnum(bp, "pw", &PW) < 0)
E 42
		PW = DEFWIDTH;
	sprintf(&width[2], "%d", PW);
D 42
	if ((PL = pgetnum("pl")) < 0)
E 42
I 42
	if (cgetnum(bp, "pl", &PL) < 0)
E 42
		PL = DEFLENGTH;
	sprintf(&length[2], "%d", PL);
I 3
D 42
	if ((PX = pgetnum("px")) < 0)
E 42
I 42
	if (cgetnum(bp,"px", &PX) < 0)
E 42
		PX = 0;
	sprintf(&pxwidth[2], "%d", PX);
D 42
	if ((PY = pgetnum("py")) < 0)
E 42
I 42
	if (cgetnum(bp, "py", &PY) < 0)
E 42
		PY = 0;
	sprintf(&pxlength[2], "%d", PY);
E 3
D 42
	RM = pgetstr("rm", &bp);
E 42
I 42
	cgetstr(bp, "rm", &RM);
E 42
I 29
D 35
	/*
	 * Figure out whether the local machine is the same as the remote 
	 * machine entry (if it exists).  If not, then ignore the local
	 * queue information.
	 */
	 if (RM != (char *) NULL) {
		char name[256];
		struct hostent *hp;
E 35
I 35
	if (s = checkremote())
		syslog(LOG_WARNING, s);
E 35

D 35
		/* get the standard network name of the local host */
		gethostname(name, sizeof(name));
		name[sizeof(name)-1] = '\0';
		hp = gethostbyname(name);
		if (hp == (struct hostent *) NULL) {
		    syslog(LOG_ERR,
			"unable to get network name for local machine %s",
			name);
		    goto localcheck_done;
		} else strcpy(name, hp->h_name);

		/* get the standard network name of RM */
		hp = gethostbyname(RM);
		if (hp == (struct hostent *) NULL) {
		    syslog(LOG_ERR,
			"unable to get hostname for remote machine %s", RM);
		    goto localcheck_done;
		}

		/* if printer is not on local machine, ignore LP */
		if (strcmp(name, hp->h_name) != 0) *LP = '\0';
	}
localcheck_done:

E 35
E 29
D 42
	AF = pgetstr("af", &bp);
	OF = pgetstr("of", &bp);
	IF = pgetstr("if", &bp);
I 3
	RF = pgetstr("rf", &bp);
E 3
	TF = pgetstr("tf", &bp);
I 11
	NF = pgetstr("nf", &bp);
E 11
	DF = pgetstr("df", &bp);
	GF = pgetstr("gf", &bp);
	VF = pgetstr("vf", &bp);
	CF = pgetstr("cf", &bp);
	TR = pgetstr("tr", &bp);
I 3
	RS = pgetflag("rs");
E 3
	SF = pgetflag("sf");
	SH = pgetflag("sh");
	SB = pgetflag("sb");
I 26
	HL = pgetflag("hl");
E 26
	RW = pgetflag("rw");
	BR = pgetnum("br");
	if ((FC = pgetnum("fc")) < 0)
E 42
I 42
	cgetstr(bp, "af", &AF);
	cgetstr(bp, "of", &OF);
	cgetstr(bp, "if", &IF);
	cgetstr(bp, "rf", &RF);
	cgetstr(bp, "tf", &TF);
	cgetstr(bp, "nf", &NF);
	cgetstr(bp, "df", &DF);
	cgetstr(bp, "gf", &GF);
	cgetstr(bp, "vf", &VF);
	cgetstr(bp, "cf", &CF);
	cgetstr(bp, "tr", &TR);

	RS = (cgetcap(bp, "rs", ':') != NULL);
	SF = (cgetcap(bp, "sf", ':') != NULL);
	SH = (cgetcap(bp, "sh", ':') != NULL);
	SB = (cgetcap(bp, "sb", ':') != NULL);
	HL = (cgetcap(bp, "hl", ':') != NULL);
	RW = (cgetcap(bp, "rw", ':') != NULL);

	cgetnum(bp, "br", &BR);
	if (cgetnum(bp, "fc", &FC) < 0)
E 42
		FC = 0;
D 42
	if ((FS = pgetnum("fs")) < 0)
E 42
I 42
	if (cgetnum(bp, "fs", &FS) < 0)
E 42
		FS = 0;
D 42
	if ((XC = pgetnum("xc")) < 0)
E 42
I 42
	if (cgetnum(bp, "xc", &XC) < 0)
E 42
		XC = 0;
D 42
	if ((XS = pgetnum("xs")) < 0)
E 42
I 42
	if (cgetnum(bp, "xs", &XS) < 0)
E 42
		XS = 0;
I 6
D 42
	tof = !pgetflag("fo");
E 42
I 42

	tof = (cgetcap(bp, "fo", ':') == NULL);
E 42
E 6
}

I 3
/*
 * Acquire line printer or remote connection.
 */
I 41
static void
E 41
I 8
D 20
static
E 20
E 8
openpr()
{
D 48
	register int i, n;
I 19
D 20
	char resp;
E 20
I 20
	int resp;
E 48
I 48
	register int i;
	char *cp;
E 48
E 20
E 19

D 35
	if (*LP) {
E 35
I 35
D 48
	if (!sendtorem && *LP) {
E 35
		for (i = 1; ; i = i < 32 ? i << 1 : i) {
D 9
			pfd = open(LP, RW ? FRDWR : FWRONLY, 0);
E 9
I 9
			pfd = open(LP, RW ? O_RDWR : O_WRONLY);
E 9
			if (pfd >= 0)
				break;
			if (errno == ENOENT) {
D 20
				log("cannot open %s", LP);
E 20
I 20
				syslog(LOG_ERR, "%s: %m", LP);
E 20
				exit(1);
			}
			if (i == 1)
D 41
				status("waiting for %s to become ready (offline ?)", printer);
E 41
I 41
				pstatus("waiting for %s to become ready (offline ?)", printer);
E 41
			sleep(i);
		}
		if (isatty(pfd))
			setty();
D 41
		status("%s is ready and printing", printer);
E 41
I 41
		pstatus("%s is ready and printing", printer);
E 41
	} else if (RM != NULL) {
D 20
		for (i = 1; ; i = i < 512 ? i << 1 : i) {
I 19
			resp = '\0';
E 20
I 20
		for (i = 1; ; i = i < 256 ? i << 1 : i) {
			resp = -1;
E 20
E 19
D 4
			pfd = getport();
E 4
I 4
			pfd = getport(RM);
E 4
			if (pfd >= 0) {
				(void) sprintf(line, "\2%s\n", RP);
				n = strlen(line);
D 20
				if (write(pfd, line, n) != n)
E 20
I 20
				if (write(pfd, line, n) == n &&
				    (resp = response()) == '\0')
E 20
					break;
D 19
				if (noresponse())
E 19
I 19
D 20
				if (read(pfd, &resp, 1) != 1) {
					log("lost connection");
E 19
					(void) close(pfd);
D 19
				else
E 19
I 19
				} else if (resp == '\0')
E 19
					break;
E 20
I 19
				(void) close(pfd);
E 19
			}
D 19
			if (i == 1)
				status("waiting for %s to come up", RM);
E 19
I 19
			if (i == 1) {
D 20
				if (resp == '\0')
E 20
I 20
				if (resp < 0)
E 20
D 41
					status("waiting for %s to come up", RM);
E 41
I 41
					pstatus("waiting for %s to come up", RM);
E 41
D 20
				else
E 20
I 20
				else {
E 20
D 41
					status("waiting for queue to be enabled on %s", RM);
E 41
I 41
					pstatus("waiting for queue to be enabled on %s", RM);
E 41
I 20
					i = 256;
				}
E 20
			}
E 19
			sleep(i);
		}
D 41
		status("sending to %s", RM);
E 41
I 41
		pstatus("sending to %s", RM);
E 41
		remote = 1;
E 48
I 48
	if (!remote && *LP) {
		if (cp = index(LP, '@'))
			opennet(cp);
		else
			opentty();
	} else if (remote) {
		openrem();
E 48
I 19
D 20
		if (setsockopt(pfd, SOL_SOCKET, SO_KEEPALIVE, 0, 0) < 0)
			log("setsockopt (SO_KEEPALIVE) failed");
E 20
E 19
	} else {
D 20
		log("no line printer device or remote machine name");
E 20
I 20
		syslog(LOG_ERR, "%s: no line printer device or host name",
			printer);
E 20
		exit(1);
	}
I 48

E 48
	/*
	 * Start up an output filter, if needed.
	 */
D 37
	if (OF) {
E 37
I 37
	if (!remote && OF) {
E 37
		int p[2];
D 48
		char *cp;
E 48

		pipe(p);
		if ((ofilter = dofork(DOABORT)) == 0) {	/* child */
			dup2(p[0], 0);		/* pipe is std in */
			dup2(pfd, 1);		/* printer is std out */
I 46
			closelog();
E 46
			for (i = 3; i < NOFILE; i++)
				(void) close(i);
			if ((cp = rindex(OF, '/')) == NULL)
				cp = OF;
			else
				cp++;
			execl(OF, cp, width, length, 0);
D 20
			log("can't execl output filter %s", OF);
E 20
I 20
			syslog(LOG_ERR, "%s: %s: %m", printer, OF);
E 20
			exit(1);
		}
		(void) close(p[0]);		/* close input side */
		ofd = p[1];			/* use pipe for output */
	} else {
		ofd = pfd;
		ofilter = 0;
	}
I 48
}

/*
 * Printer connected directly to the network
 * or to a terminal server on the net
 */
static void
opennet(cp)
	char *cp;
{
	register int i;
	int resp, port;
I 50
	char save_ch;
E 50

D 50
	*cp++ = '\0';
	port = atoi(cp);
E 50
I 50
	save_ch = *cp;
	*cp = '\0';
	port = atoi(LP);
E 50
	if (port <= 0) {
D 50
		syslog(LOG_ERR, "%s: bad port number: %s", printer, cp);
E 50
I 50
		syslog(LOG_ERR, "%s: bad port number: %s", printer, LP);
E 50
		exit(1);
	}
I 50
	*cp++ = save_ch;
E 50

	for (i = 1; ; i = i < 256 ? i << 1 : i) {
		resp = -1;
D 50
		pfd = getport(LP, port);
E 50
I 50
		pfd = getport(cp, port);
E 50
		if (pfd < 0 && errno == ECONNREFUSED)
			resp = 1;
		else if (pfd >= 0) {
			/*
			 * need to delay a bit for rs232 lines
			 * to stabilize in case printer is
			 * connected via a terminal server
			 */
			delay(500);
			break;
		}
		if (i == 1) {
		   if (resp < 0)
			pstatus("waiting for %s to come up", LP);
		   else
			pstatus("waiting for access to printer on %s", LP);
		}
		sleep(i);
	}
D 50
	pstatus("sending to %s port %d", LP, port);
	*(--cp) = '@';	/* restore LP parameter in case we are called again */
E 50
I 50
	pstatus("sending to %s port %d", cp, port);
E 50
}

/*
 * Printer is connected to an RS232 port on this host
 */
static void
opentty()
{
	register int i;
	int resp, port;

	for (i = 1; ; i = i < 32 ? i << 1 : i) {
		pfd = open(LP, RW ? O_RDWR : O_WRONLY);
		if (pfd >= 0) {
			delay(500);
			break;
		}
		if (errno == ENOENT) {
			syslog(LOG_ERR, "%s: %m", LP);
			exit(1);
		}
		if (i == 1)
			pstatus("waiting for %s to become ready (offline ?)",
				printer);
		sleep(i);
	}
	if (isatty(pfd))
		setty();
	pstatus("%s is ready and printing", printer);
}

/*
 * Printer is on a remote host
 */
static void
openrem()
{
	register int i, n;
	int resp, port;

	for (i = 1; ; i = i < 256 ? i << 1 : i) {
		resp = -1;
		pfd = getport(RM, 0);
		if (pfd >= 0) {
			(void) sprintf(line, "\2%s\n", RP);
			n = strlen(line);
			if (write(pfd, line, n) == n &&
			    (resp = response()) == '\0')
				break;
			(void) close(pfd);
		}
		if (i == 1) {
			if (resp < 0)
				pstatus("waiting for %s to come up", RM);
			else {
				pstatus("waiting for queue to be enabled on %s",
					RM);
				i = 256;
			}
		}
		sleep(i);
	}
	pstatus("sending to %s", RM);
E 48
}

E 3
struct bauds {
	int	baud;
	int	speed;
} bauds[] = {
	50,	B50,
	75,	B75,
	110,	B110,
	134,	B134,
	150,	B150,
	200,	B200,
	300,	B300,
	600,	B600,
	1200,	B1200,
	1800,	B1800,
	2400,	B2400,
	4800,	B4800,
	9600,	B9600,
	19200,	EXTA,
	38400,	EXTB,
	0,	0
};

/*
 * setup tty lines.
 */
I 41
static void
E 41
I 8
D 20
static
E 20
E 8
setty()
{
	struct sgttyb ttybuf;
	register struct bauds *bp;

	if (ioctl(pfd, TIOCEXCL, (char *)0) < 0) {
D 20
		log("cannot set exclusive-use");
E 20
I 20
		syslog(LOG_ERR, "%s: ioctl(TIOCEXCL): %m", printer);
E 20
		exit(1);
	}
	if (ioctl(pfd, TIOCGETP, (char *)&ttybuf) < 0) {
D 20
		log("cannot get tty parameters");
E 20
I 20
		syslog(LOG_ERR, "%s: ioctl(TIOCGETP): %m", printer);
E 20
		exit(1);
	}
	if (BR > 0) {
		for (bp = bauds; bp->baud; bp++)
			if (BR == bp->baud)
				break;
		if (!bp->baud) {
D 20
			log("illegal baud rate %d", BR);
E 20
I 20
			syslog(LOG_ERR, "%s: illegal baud rate %d", printer, BR);
E 20
			exit(1);
		}
		ttybuf.sg_ispeed = ttybuf.sg_ospeed = bp->speed;
	}
D 10
	if (FC)
		ttybuf.sg_flags &= ~FC;
	if (FS)
		ttybuf.sg_flags |= FS;
E 10
I 10
	ttybuf.sg_flags &= ~FC;
	ttybuf.sg_flags |= FS;
E 10
	if (ioctl(pfd, TIOCSETP, (char *)&ttybuf) < 0) {
D 20
		log("cannot set tty parameters");
E 20
I 20
		syslog(LOG_ERR, "%s: ioctl(TIOCSETP): %m", printer);
E 20
		exit(1);
	}
I 21
D 34
	if (XC || XS) {
		int ldisc = NTTYDISC;

		if (ioctl(pfd, TIOCSETD, &ldisc) < 0) {
			syslog(LOG_ERR, "%s: ioctl(TIOCSETD): %m", printer);
			exit(1);
		}
	}
E 34
E 21
	if (XC) {
		if (ioctl(pfd, TIOCLBIC, &XC) < 0) {
D 20
			log("cannot set local tty parameters");
E 20
I 20
			syslog(LOG_ERR, "%s: ioctl(TIOCLBIC): %m", printer);
E 20
			exit(1);
		}
	}
	if (XS) {
		if (ioctl(pfd, TIOCLBIS, &XS) < 0) {
D 20
			log("cannot set local tty parameters");
E 20
I 20
			syslog(LOG_ERR, "%s: ioctl(TIOCLBIS): %m", printer);
E 20
			exit(1);
		}
	}
I 3
}

D 41
/*VARARGS1*/
D 20
static
E 20
status(msg, a1, a2, a3)
E 41
I 41
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

D 49
void
E 49
I 49
static void
E 49
#if __STDC__
pstatus(const char *msg, ...)
#else
pstatus(msg, va_alist)
E 41
	char *msg;
I 41
        va_dcl
#endif
E 41
{
	register int fd;
	char buf[BUFSIZ];
I 41
	va_list ap;
#if __STDC__
	va_start(ap, msg);
#else
	va_start(ap);
#endif
E 41

	umask(0);
D 9
	if ((fd = open(ST, FWRONLY|FCREATE|FTRUNCATE|FEXLOCK, 0664)) < 0)
E 9
I 9
	fd = open(ST, O_WRONLY|O_CREAT, 0664);
D 20
	if (fd < 0 || flock(fd, LOCK_EX) < 0)
E 9
		fatal("cannot create status file");
E 20
I 20
	if (fd < 0 || flock(fd, LOCK_EX) < 0) {
		syslog(LOG_ERR, "%s: %s: %m", printer, ST);
		exit(1);
	}
E 20
I 9
	ftruncate(fd, 0);
E 9
D 41
	sprintf(buf, msg, a1, a2, a3);
E 41
I 41
	(void)vsnprintf(buf, sizeof(buf), msg, ap);
	va_end(ap);
E 41
	strcat(buf, "\n");
	(void) write(fd, buf, strlen(buf));
	(void) close(fd);
E 3
}
E 1
