h26864
s 00001/00001/00331
d D 8.2 95/04/27 21:38:41 tef 34 33
c Bug fixes.
e
s 00004/00004/00328
d D 8.1 93/06/06 14:00:32 bostic 33 32
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00329
d D 5.21 92/11/30 13:35:45 bostic 32 31
c add hostname to recvjob screwup message, print out messed up line
e
s 00001/00001/00329
d D 5.20 92/09/16 10:52:29 elan 31 30
c copyright -> static
e
s 00009/00028/00321
d D 5.19 92/09/15 10:52:01 elan 30 29
c Added SCCS keywords.
e
s 00048/00017/00301
d D 5.18 92/09/01 11:09:46 elan 29 28
c Rewrote to use new getcap(3) library.  Major prototyping and cleanup.
e
s 00051/00010/00267
d D 5.17 92/07/21 10:29:28 bostic 28 27
c prototype lpr to fix quad's
e
s 00001/00001/00276
d D 5.16 92/01/27 15:57:25 bostic 27 26
c statfs.f_fsize =>statfs.f_bsize
e
s 00003/00003/00274
d D 5.15 91/05/04 18:06:10 mckusick 26 25
c more informative error messages; fix bug from 5.13
e
s 00010/00046/00267
d D 5.14 91/05/02 18:21:35 mckusick 25 24
c use statfs in place of trying to read the superblock;
c fix typo in previous delta
e
s 00002/00001/00311
d D 5.13 91/04/30 09:38:20 bostic 24 23
c continue from revision 5.10 -- if the user creates a symlink to the
c target file, using the -s option, then can use a symlink to get to the file.
c Add O_EXCL to the open of the spool file.
e
s 00003/00001/00309
d D 5.12 91/03/02 15:02:05 bostic 23 22
c ANSI
e
s 00001/00011/00309
d D 5.11 90/06/01 18:45:43 bostic 22 21
c new copyright notice
e
s 00003/00003/00317
d D 5.10 89/09/26 10:52:38 bostic 21 20
c don't allow remote to specify path; bug report 4.3BSD-tahoe/usr.bin/30
e
s 00001/00001/00319
d D 5.9 89/07/28 12:39:01 karels 20 19
c vnodes
e
s 00006/00005/00314
d D 5.8 89/05/11 14:09:50 bostic 19 18
c file reorg, pathnames.h, paths.h
e
s 00010/00005/00309
d D 5.7 88/06/30 18:00:11 bostic 18 17
c install approved copyright notice
e
s 00009/00003/00305
d D 5.6 88/05/05 18:08:34 bostic 17 16
c written by Ralph Campbell; add Berkeley specific header
e
s 00002/00004/00306
d D 5.5 87/03/19 14:38:01 mckusick 16 15
c SBLOCK => SBOFF
e
s 00005/00003/00305
d D 5.4 86/06/06 11:18:45 mckusick 15 14
c save data file name in a separate buffer in case it needs to be removed
e
s 00007/00000/00301
d D 5.3 86/04/15 15:16:17 bloom 14 13
c use our version of host name to avoid problems with local and remote
c end having different ideas of the machine name
e
s 00006/00000/00295
d D 5.2 85/11/17 15:54:25 eric 13 12
c clean up logging
e
s 00007/00001/00288
d D 5.1 85/06/06 10:08:48 dist 12 11
c Add copyright
e
s 00003/00004/00286
d D 4.8 84/08/13 16:47:25 ralph 11 9
c fix uninitialized loop variable
e
s 00001/00000/00290
d R 4.8 84/08/13 16:37:08 ralph 10 9
c initialize loop variable
e
s 00121/00035/00169
d D 4.7 84/07/25 09:08:55 ralph 9 8
c use syslog(). Check for free space before transfering file.
e
s 00004/00001/00200
d D 4.6 83/07/17 00:12:18 sam 8 7
c put sccs id's to some use
e
s 00003/00001/00198
d D 4.5 83/06/17 15:09:45 ralph 7 6
c fixed `fc' and `fs' when 0177777 is needed.
e
s 00002/00002/00197
d D 4.4 83/06/15 14:57:56 sam 6 5
c open and flock defines changed
e
s 00004/00002/00195
d D 4.3 83/06/02 12:23:47 ralph 5 4
c made local variables static to improve separation between functions.
e
s 00008/00002/00189
d D 4.2 83/05/16 14:12:32 ralph 4 1
c bug fixes and changes for lpc command.
e
s 00007/00002/00189
d R 4.2 83/05/16 13:40:29 ralph 3 1
c bug fixes and changes for lpc command.
e
s 00000/00002/00189
d R 4.2 83/05/13 11:53:50 ralph 2 1
c bug fixes and changes for lpc command.
e
s 00191/00000/00000
d D 4.1 83/04/29 11:31:04 ralph 1 0
c date and time created 83/04/29 11:31:04 by ralph
e
u
U
t
T
I 12
/*
D 30
 * Copyright (c) 1983 Regents of the University of California.
E 30
I 30
D 33
 * Copyright (c) 1983 The Regents of the University of California.
E 30
D 17
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 17
I 17
 * All rights reserved.
E 33
I 33
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 33
 *
D 22
 * Redistribution and use in source and binary forms are permitted
D 18
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 18
I 18
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
E 22
I 22
D 29
 * %sccs.include.redist.c%
E 29
I 29
D 30
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
E 30
 *
D 30
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
E 30
I 30
 * %sccs.include.redist.c%
E 30
E 29
E 22
E 18
E 17
 */

E 12
I 1
D 8
/*	%M%	%I%	%E%	*/
E 8
I 8
#ifndef lint
D 29
static char sccsid[] = "%W% (Berkeley) %G%";
E 29
I 29
D 30
static char sccsid[] = "@(#)recvjob.c	5.18 (Berkeley) 8/6/92";
E 30
I 30
D 31
char copyright[] =
E 31
I 31
static char copyright[] =
E 31
D 33
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
 All rights reserved.\n";
E 33
I 33
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 33
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
E 30
E 29
D 12
#endif
E 12
I 12
D 17
#endif not lint
E 17
I 17
#endif /* not lint */
E 17
E 12

E 8
/*
 * Receive printer jobs from the network, queue them and
 * start the printer daemon.
 */
I 28
#include <sys/param.h>
#include <sys/mount.h>
#include <sys/stat.h>
E 28

I 29
#include <unistd.h>
E 29
I 28
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <syslog.h>
#include <stdio.h>
I 29
#include <stdlib.h>
#include <string.h>
E 29
E 28
#include "lp.h"
I 28
#include "lp.local.h"
#include "extern.h"
E 28
I 9
D 20
#include <sys/fs.h>
E 20
I 20
D 25
#include <ufs/fs.h>
E 25
E 20
I 19
#include "pathnames.h"
I 25
D 28
#include <sys/mount.h>
E 28
E 25
E 19
E 9

D 5
char    tfname[40];		/* tmp copy of cf before linking */
char    *dfname;		/* data files */
E 5
I 5
D 9
static char    tfname[40];	/* tmp copy of cf before linking */
static char    *dfname;		/* data files */
E 9
I 9
D 29
char	*sp = "";
E 29
#define ack()	(void) write(1, sp, 1);
E 9
E 5

I 9
D 29
char    tfname[40];		/* tmp copy of cf before linking */
D 15
char    *dfname;		/* data files */
E 15
I 15
char    dfname[40];		/* data files */
E 15
int	minfree;		/* keep at least minfree blocks available */
E 29
I 29
static char	 dfname[40];	/* data files */
static int	 minfree;       /* keep at least minfree blocks available */
static char	*sp = "";
static char	 tfname[40];	/* tmp copy of cf before linking */
E 29
D 25
char	*ddev;			/* disk device (for checking free space) */
int	dfd;			/* file system device descriptor */
E 25

D 25
char	*find_dev();
E 25
I 23
D 28
void	rcleanup();
E 28
I 28
D 29
static int        readjob __P((void));
static int        readfile __P((char *, int));
static int        noresponse __P((void));
E 29
static int        chksize __P((int));
static void       frecverr __P((const char *, ...));
D 29
static int        read_number __P((char *));
E 29
I 29
static int        noresponse __P((void));
E 29
static void       rcleanup __P((int));
I 29
static int        read_number __P((char *));
static int        readfile __P((char *, int));
static int        readjob __P((void));
E 29
E 28
E 23

I 28

D 29
int
E 29
I 29
void
E 29
E 28
E 9
recvjob()
{
I 4
	struct stat stb;
E 4
D 29
	char *bp = pbuf;
E 29
D 9
	int status;
E 9
I 9
D 23
	int status, rcleanup();
E 23
I 23
	int status;
E 23
E 9

D 4
	name = "recvjob";

E 4
	/*
	 * Perform lookup for printer name or abbreviation
	 */
D 29
	if ((status = pgetent(line, printer)) < 0)
E 29
I 29
	if ((status = cgetent(&bp, printcapdb, printer)) == -2)
E 29
D 9
		fatal("cannot open printer description file");
E 9
I 9
		frecverr("cannot open printer description file");
E 9
D 29
	else if (status == 0)
E 29
I 29
	else if (status == -1)
E 29
D 9
		fatal("unknown printer");
E 9
I 9
		frecverr("unknown printer %s", printer);
E 9
D 29
	if ((LF = pgetstr("lf", &bp)) == NULL)
E 29
I 29
	else if (status == -3)
		fatal("potential reference loop detected in printcap file");
	
	if (cgetstr(bp, "lf", &LF) == -1)
E 29
D 19
		LF = DEFLOGF;
E 19
I 19
		LF = _PATH_CONSOLE;
E 19
D 29
	if ((SD = pgetstr("sd", &bp)) == NULL)
E 29
I 29
	if (cgetstr(bp, "sd", &SD) == -1)
E 29
D 19
		SD = DEFSPOOL;
E 19
I 19
		SD = _PATH_DEFSPOOL;
E 19
I 4
D 29
	if ((LO = pgetstr("lo", &bp)) == NULL)
E 29
I 29
	if (cgetstr(bp, "lo", &LO) == -1)
E 29
		LO = DEFLOCK;
E 4

I 13
	(void) close(2);			/* set up log file */
	if (open(LF, O_WRONLY|O_APPEND, 0664) < 0) {
		syslog(LOG_ERR, "%s: %m", LF);
D 19
		(void) open("/dev/null", O_WRONLY);
E 19
I 19
		(void) open(_PATH_DEVNULL, O_WRONLY);
E 19
	}

E 13
D 9
	(void) close(2);
D 6
	(void) open(LF, FWRONLY|FAPPEND, 0);
E 6
I 6
	(void) open(LF, O_WRONLY|O_APPEND);
E 9
E 6
	if (chdir(SD) < 0)
D 9
		fatal("cannot chdir to %s", SD);
I 4
	if (stat(LO, &stb) == 0 && (stb.st_mode & 010)) {
		/* queue is disabled */
		putchar('\1');		/* return error code */
		exit(1);
	}
E 9
I 9
		frecverr("%s: %s: %m", printer, SD);
	if (stat(LO, &stb) == 0) {
		if (stb.st_mode & 010) {
			/* queue is disabled */
			putchar('\1');		/* return error code */
			exit(1);
		}
	} else if (stat(SD, &stb) < 0)
		frecverr("%s: %s: %m", printer, SD);
D 25
	minfree = read_number("minfree");
	ddev = find_dev(stb.st_dev, S_IFBLK);
	if ((dfd = open(ddev, O_RDONLY)) < 0)
		syslog(LOG_WARNING, "%s: %s: %m", printer, ddev);
E 25
I 25
	minfree = 2 * read_number("minfree");	/* scale KB to 512 blocks */
E 25
	signal(SIGTERM, rcleanup);
	signal(SIGPIPE, rcleanup);
E 9
E 4

	if (readjob())
		printjob();
}

D 9
char	*sp = "";
#define ack()	(void) write(1, sp, 1);
E 9
I 9
D 25
char *
find_dev(dev, type)
	register dev_t dev;
	register int type;
{
D 19
	register DIR *dfd = opendir("/dev");
E 19
I 19
	register DIR *dfd = opendir(_PATH_DEV);
E 19
	struct direct *dir;
	struct stat stb;
	char devname[MAXNAMLEN+6];
	char *dp;
E 9

I 9
D 19
	strcpy(devname, "/dev/");
E 19
I 19
	strcpy(devname, _PATH_DEV);
E 19
	while ((dir = readdir(dfd))) {
		strcpy(devname + 5, dir->d_name);
		if (stat(devname, &stb))
			continue;
		if ((stb.st_mode & S_IFMT) != type)
			continue;
		if (dev == stb.st_rdev) {
			closedir(dfd);
			dp = (char *)malloc(strlen(devname)+1);
			strcpy(dp, devname);
			return(dp);
		}
	}
	closedir(dfd);
	frecverr("cannot find device %d, %d", major(dev), minor(dev));
	/*NOTREACHED*/
}

E 25
E 9
/*
 * Read printer jobs sent by lpd and copy them to the spooling directory.
 * Return the number of jobs successfully transfered.
 */
I 28
static int
E 28
I 5
D 9
static
E 5
readjob(printer)
	char *printer;
E 9
I 9
readjob()
E 9
{
	register int size, nfiles;
	register char *cp;

	ack();
	nfiles = 0;
	for (;;) {
		/*
		 * Read a command to tell us what to do
		 */
		cp = line;
		do {
			if ((size = read(1, cp, 1)) != 1) {
				if (size < 0)
D 9
					fatal("Lost connection");
E 9
I 9
					frecverr("%s: Lost connection",printer);
E 9
				return(nfiles);
			}
		} while (*cp++ != '\n');
		*--cp = '\0';
		cp = line;
		switch (*cp++) {
		case '\1':	/* cleanup because data sent was bad */
D 9
			cleanup();
E 9
I 9
D 28
			rcleanup();
E 28
I 28
			rcleanup(0);
E 28
E 9
			continue;

		case '\2':	/* read cf file */
			size = 0;
			while (*cp >= '0' && *cp <= '9')
				size = size * 10 + (*cp++ - '0');
			if (*cp++ != ' ')
				break;
I 14
			/*
			 * host name has been authenticated, we use our
			 * view of the host name since we may be passed
			 * something different than what gethostbyaddr()
			 * returns
			 */
			strcpy(cp + 6, from);
E 14
			strcpy(tfname, cp);
			tfname[0] = 't';
I 9
			if (!chksize(size)) {
				(void) write(1, "\2", 1);
				continue;
			}
E 9
			if (!readfile(tfname, size)) {
D 9
				cleanup();
E 9
I 9
D 28
				rcleanup();
E 28
I 28
				rcleanup(0);
E 28
E 9
				continue;
			}
			if (link(tfname, cp) < 0)
D 9
				fatal("cannot rename %s", tfname);
E 9
I 9
				frecverr("%s: %m", tfname);
E 9
			(void) unlink(tfname);
			tfname[0] = '\0';
			nfiles++;
			continue;

		case '\3':	/* read df file */
			size = 0;
			while (*cp >= '0' && *cp <= '9')
				size = size * 10 + (*cp++ - '0');
			if (*cp++ != ' ')
				break;
I 9
			if (!chksize(size)) {
				(void) write(1, "\2", 1);
				continue;
			}
E 9
D 15
			(void) readfile(dfname = cp, size);
E 15
I 15
D 21
			strcpy(dfname, cp);
E 21
I 21
			(void) strcpy(dfname, cp);
			if (index(dfname, '/'))
D 26
				frecverr("illegal path name");
E 26
I 26
				frecverr("readjob: %s: illegal path name",
					dfname);
E 26
E 21
			(void) readfile(dfname, size);
E 15
			continue;
		}
D 9
		fatal("protocol screwup");
E 9
I 9
D 32
		frecverr("protocol screwup");
E 32
I 32
		frecverr("protocol screwup: %s", line);
E 32
E 9
	}
}

/*
 * Read files send by lpd and copy them to the spooling directory.
 */
I 28
static int
E 28
I 5
D 9
static
E 9
E 5
readfile(file, size)
	char *file;
	int size;
{
	register char *cp;
	char buf[BUFSIZ];
	register int i, j, amt;
	int fd, err;

D 6
	fd = open(file, FWRONLY|FCREATE, FILMOD);
E 6
I 6
D 24
	fd = open(file, O_WRONLY|O_CREAT, FILMOD);
E 24
I 24
D 25
	fd = open(file, O_CREAT|O_EXECL|O_WRONLY, FILMOD);
E 25
I 25
	fd = open(file, O_CREAT|O_EXCL|O_WRONLY, FILMOD);
E 25
D 26
		frecverr("illegal path name");
E 26
E 24
E 6
	if (fd < 0)
D 9
		fatal("cannot create %s", file);
E 9
I 9
D 26
		frecverr("%s: %m", file);
E 26
I 26
		frecverr("readfile: %s: illegal path name: %m", file);
E 26
E 9
	ack();
	err = 0;
	for (i = 0; i < size; i += BUFSIZ) {
		amt = BUFSIZ;
		cp = buf;
		if (i + amt > size)
			amt = size - i;
		do {
			j = read(1, cp, amt);
			if (j <= 0)
D 9
				fatal("Lost connection");
E 9
I 9
				frecverr("Lost connection");
E 9
			amt -= j;
			cp += j;
		} while (amt > 0);
		amt = BUFSIZ;
		if (i + amt > size)
			amt = size - i;
D 7
		if (err == 0 && write(fd, buf, amt) != amt)
E 7
I 7
		if (write(fd, buf, amt) != amt) {
E 7
			err++;
I 7
			break;
		}
E 7
	}
	(void) close(fd);
	if (err)
D 9
		fatal("%s: write error", file);
E 9
I 9
		frecverr("%s: write error", file);
E 9
	if (noresponse()) {		/* file sent had bad data in it */
		(void) unlink(file);
		return(0);
	}
	ack();
	return(1);
}

I 28
static int
E 28
D 9
static
E 9
noresponse()
{
	char resp;

	if (read(1, &resp, 1) != 1)
D 9
		fatal("Lost connection");
E 9
I 9
		frecverr("Lost connection");
E 9
	if (resp == '\0')
		return(0);
	return(1);
}

/*
I 9
 * Check to see if there is enough space on the disk for size bytes.
 * 1 == OK, 0 == Not OK.
 */
I 28
static int
E 28
chksize(size)
	int size;
{
D 21
	struct stat stb;
	register char *ddev;
E 21
	int spacefree;
D 25
	struct fs fs;
E 25
I 25
	struct statfs sfb;
E 25

D 16
	if (dfd < 0 || lseek(dfd, (long)(SBLOCK * DEV_BSIZE), 0) < 0)
E 16
I 16
D 25
	if (dfd < 0 || lseek(dfd, (long)(SBOFF), 0) < 0)
E 16
		return(1);
	if (read(dfd, (char *)&fs, sizeof fs) != sizeof fs)
		return(1);
D 16
	spacefree = (fs.fs_cstotal.cs_nbfree * fs.fs_frag +
		fs.fs_cstotal.cs_nffree - fs.fs_dsize * fs.fs_minfree / 100) *
			fs.fs_fsize / 1024;
E 16
I 16
	spacefree = freespace(&fs, fs.fs_minfree) * fs.fs_fsize / 1024;
E 16
	size = (size + 1023) / 1024;
E 25
I 25
	if (statfs(".", &sfb) < 0) {
		syslog(LOG_ERR, "%s: %m", "statfs(\".\")");
		return (1);
	}
D 27
	spacefree = sfb.f_bavail * (sfb.f_fsize / 512);
E 27
I 27
	spacefree = sfb.f_bavail * (sfb.f_bsize / 512);
E 27
	size = (size + 511) / 512;
E 25
	if (minfree + size > spacefree)
		return(0);
	return(1);
}

I 28
static int
E 28
read_number(fn)
	char *fn;
{
	char lin[80];
	register FILE *fp;

	if ((fp = fopen(fn, "r")) == NULL)
		return (0);
	if (fgets(lin, 80, fp) == NULL) {
		fclose(fp);
		return (0);
	}
	fclose(fp);
	return (atoi(lin));
}

/*
E 9
 * Remove all the files associated with the current job being transfered.
 */
I 23
D 28
void
E 23
D 9
static
cleanup()
E 9
I 9
rcleanup()
E 28
I 28
static void
rcleanup(signo)
	int signo;
E 28
E 9
{
D 11
	register int i;
E 11
D 28

E 28
	if (tfname[0])
		(void) unlink(tfname);
D 15
	if (dfname)
E 15
I 15
	if (dfname[0])
E 15
		do {
			do
				(void) unlink(dfname);
D 11
			while (dfname[i]-- != 'A');
			dfname[i] = 'z';
		} while (dfname[i-2]-- != 'd');
E 11
I 11
			while (dfname[2]-- != 'A');
			dfname[2] = 'z';
		} while (dfname[0]-- != 'd');
I 15
	dfname[0] = '\0';
E 15
E 11
}

D 9
static
fatal(msg, a1)
E 9
I 9
D 28
frecverr(msg, a1, a2)
E 28
I 28
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

static void
#if __STDC__
frecverr(const char *msg, ...)
#else
frecverr(msg, va_alist)
E 28
E 9
	char *msg;
I 28
        va_dcl
#endif
E 28
{
I 32
D 34
	extern char *fromb;
E 34
I 34
	extern char fromb[];
E 34
E 32
D 9
	cleanup();
	log(msg, a1);
E 9
I 9
D 28
	rcleanup();
	syslog(LOG_ERR, msg, a1, a2);
E 28
I 28
	va_list ap;
#if __STDC__
	va_start(ap, msg);
#else
	va_start(ap);
#endif
	rcleanup(0);
I 32
	syslog(LOG_ERR, "%s", fromb);
E 32
	vsyslog(LOG_ERR, msg, ap);
	va_end(ap);
E 28
E 9
	putchar('\1');		/* return error code */
	exit(1);
}
E 1
