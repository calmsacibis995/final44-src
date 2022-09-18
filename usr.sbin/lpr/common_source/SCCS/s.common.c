h35750
s 00001/00000/00350
d D 8.5 95/04/28 15:38:27 tef 24 23
c Better portability to other systems.
e
s 00038/00015/00312
d D 8.4 95/04/28 12:16:48 tef 23 22
c Support for printers connected via ethernet/TCP and terminal servers.
e
s 00004/00003/00323
d D 8.3 95/04/27 21:37:56 tef 22 21
c Bug fixes.
e
s 00005/00000/00321
d D 8.2 94/01/21 17:37:37 bostic 21 20
c add USL's copyright notice
e
s 00002/00002/00319
d D 8.1 93/06/06 13:58:44 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00028/00319
d D 5.10 92/09/15 10:39:07 elan 19 18
c Added SCCS keywords.
e
s 00065/00037/00282
d D 5.9 92/09/01 11:08:00 elan 18 17
c Rewrote to use new getcap(3) library.  Major prototyping and cleanup.
e
s 00054/00018/00265
d D 5.8 92/07/21 10:28:14 bostic 17 16
c prototype lpr to fix quad's
e
s 00003/00002/00280
d D 5.7 91/03/02 14:50:51 bostic 16 15
c ANSI
e
s 00001/00011/00281
d D 5.6 90/06/01 18:43:52 bostic 15 14
c new copyright notice
e
s 00045/00001/00247
d D 5.5 89/08/22 21:02:22 tef 14 13
c common code for checking if rm==localhost
e
s 00010/00005/00238
d D 5.4 88/06/30 17:59:40 bostic 13 12
c install approved copyright notice
e
s 00009/00003/00234
d D 5.3 88/05/05 18:07:40 bostic 12 11
c written by Ralph Campbell; add Berkeley specific header
e
s 00000/00022/00237
d D 5.2 86/05/06 18:36:47 bloom 11 10
c remove local copy of rresvport
e
s 00007/00001/00252
d D 5.1 85/06/06 09:58:39 dist 10 9
c Add copyright
e
s 00001/00000/00252
d D 4.9 85/02/27 16:20:03 ralph 9 8
c added 'hl' flag to printcap to print the banner last.
e
s 00004/00001/00248
d D 4.8 83/07/17 00:10:51 sam 8 7
c put sccs id's to some use
e
s 00001/00000/00248
d D 4.7 83/06/22 09:33:53 ralph 7 6
c added -n option to print ditroff files.
e
s 00007/00005/00241
d D 4.6 83/06/17 15:09:22 ralph 6 5
c fixed `fc' and `fs' when 0177777 is needed.
e
s 00016/00011/00230
d D 4.5 83/06/02 12:21:23 ralph 5 4
c fixed getport() so sockets are not left open after errors.
e
s 00000/00014/00241
d D 4.4 83/05/27 11:36:02 ralph 4 3
c improved error messages
e
s 00006/00007/00249
d D 4.3 83/05/18 16:45:43 ralph 3 2
c fixed lprm segmentation fault when remote is down.
e
s 00004/00016/00252
d D 4.2 83/05/13 11:54:04 ralph 2 1
c bug fixes and changes for lpc command.
e
s 00268/00000/00000
d D 4.1 83/04/29 11:38:57 ralph 1 0
c date and time created 83/04/29 11:38:57 by ralph
e
u
U
t
T
I 10
/*
D 20
 * Copyright (c) 1983 Regents of the University of California.
D 12
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 12
I 12
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
I 21
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 21
E 20
 *
D 15
 * Redistribution and use in source and binary forms are permitted
D 13
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 13
I 13
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
E 15
I 15
D 18
 * %sccs.include.redist.c%
E 18
I 18
D 19
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
 *
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
E 19
I 19
 * %sccs.include.redist.c%
E 19
E 18
E 15
E 13
E 12
 */

E 10
I 1
D 8
/*	%M%	%I%	%E%	*/
E 8
I 8
#ifndef lint
D 18
static char sccsid[] = "%W% (Berkeley) %G%";
E 18
I 18
D 19
static char sccsid[] = "@(#)common.c	5.9 (Berkeley) 8/6/92";
E 19
I 19
static char sccsid[] = "%W% (Berkeley) %G%";
E 19
E 18
D 10
#endif
E 10
I 10
D 12
#endif not lint
E 12
I 12
#endif /* not lint */
E 12
E 10

I 17
#include <sys/param.h>
#include <sys/stat.h>
I 24
#include <sys/time.h>
E 24

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lp.h"
I 18
#include "pathnames.h"
E 18

E 17
E 8
/*
 * Routines and data common to all the line printer functions.
 */

D 17
#include "lp.h"

E 17
D 18
int	DU;		/* daeomon user-id */
int	MX;		/* maximum number of blocks to copy */
I 6
int	MC;		/* maximum number of copies allowed */
E 6
char	*LP;		/* line printer device name */
char	*RM;		/* remote machine name */
char	*RP;		/* remote printer name */
char	*LO;		/* lock file name */
char	*ST;		/* status file name */
char	*SD;		/* spool directory */
E 18
char	*AF;		/* accounting file */
I 18
long	 BR;		/* baud rate if lp is a tty */
char	*CF;		/* name of cifplot filter (per job) */
char	*DF;		/* name of tex filter (per job) */
long	 DU;		/* daeomon user-id */
long	 FC;		/* flags to clear if lp is a tty */
char	*FF;		/* form feed string */
long	 FS;		/* flags to set if lp is a tty */
char	*GF;		/* name of graph(1G) filter (per job) */
long	 HL;		/* print header last */
char	*IF;		/* name of input filter (created per job) */
E 18
char	*LF;		/* log file for error messages */
I 18
char	*LO;		/* lock file name */
char	*LP;		/* line printer device name */
long	 MC;		/* maximum number of copies allowed */
long	 MX;		/* maximum number of blocks to copy */
char	*NF;		/* name of ditroff filter (per job) */
E 18
char	*OF;		/* name of output filter (created once) */
D 18
char	*IF;		/* name of input filter (created per job) */
E 18
I 18
char	*PF;		/* name of vrast filter (per job) */
long	 PL;		/* page length */
long	 PW;		/* page width */
long	 PX;		/* page width in pixels */
long	 PY;		/* page length in pixels */
E 18
I 2
char	*RF;		/* name of fortran text filter (per job) */
I 18
char    *RG;		/* resricted group */
char	*RM;		/* remote machine name */
char	*RP;		/* remote printer name */
long	 RS;		/* restricted to those with local accounts */
long	 RW;		/* open LP for reading and writing */
long	 SB;		/* short banner instead of normal header */
long	 SC;		/* suppress multiple copies */
char	*SD;		/* spool directory */
long	 SF;		/* suppress FF on each print job */
long	 SH;		/* suppress header page */
char	*ST;		/* status file name */
E 18
E 2
char	*TF;		/* name of troff filter (per job) */
I 7
D 18
char	*NF;		/* name of ditroff filter (per job) */
E 7
char	*DF;		/* name of tex filter (per job) */
char	*GF;		/* name of graph(1G) filter (per job) */
char	*VF;		/* name of vplot filter (per job) */
char	*CF;		/* name of cifplot filter (per job) */
char	*PF;		/* name of vrast filter (per job) */
char	*FF;		/* form feed string */
E 18
char	*TR;		/* trailer string to be output when Q empties */
I 6
D 18
short	SC;		/* suppress multiple copies */
E 6
short	SF;		/* suppress FF on each print job */
short	SH;		/* suppress header page */
short	SB;		/* short banner instead of normal header */
I 9
short	HL;		/* print header last */
E 9
short	RW;		/* open LP for reading and writing */
short	PW;		/* page width */
short	PL;		/* page length */
I 2
short	PX;		/* page width in pixels */
short	PY;		/* page length in pixels */
E 2
short	BR;		/* baud rate if lp is a tty */
D 6
short	FC;		/* flags to clear if lp is a tty */
short	FS;		/* flags to set if lp is a tty */
short	XC;		/* flags to clear for local mode */
short	XS;		/* flags to set for local mode */
E 6
I 6
int	FC;		/* flags to clear if lp is a tty */
int	FS;		/* flags to set if lp is a tty */
int	XC;		/* flags to clear for local mode */
int	XS;		/* flags to set for local mode */
E 6
I 2
short	RS;		/* restricted to those with local accounts */
E 18
I 18
char	*VF;		/* name of vplot filter (per job) */
long	 XC;		/* flags to clear for local mode */
long	 XS;		/* flags to set for local mode */
E 18
E 2

char	line[BUFSIZ];
D 18
char	pbuf[BUFSIZ/2];	/* buffer for printcap strings */
char	*bp = pbuf;	/* pointer into pbuf for pgetent() */
E 18
I 18
char	*bp;		/* pointer into printcap buffer. */
E 18
char	*name;		/* program name */
char	*printer;	/* printer name */
D 17
char	host[32];	/* host machine name */
E 17
I 17
			/* host machine name */
char	host[MAXHOSTNAMELEN];
E 17
char	*from = host;	/* client's machine name */
I 14
D 23
int	sendtorem;	/* are we sending to a remote? */
E 23
I 23
int	remote;		/* true if sending files to a remote host */
E 23
I 18
char	*printcapdb[2] = { _PATH_PRINTCAP, 0 };
E 18
E 14

I 17
static int compar __P((const void *, const void *));

E 17
/*
D 23
 * Create a connection to the remote printer server.
E 23
I 23
 * Create a TCP connection to host "rhost" at port "rport".
 * If rport == 0, then use the printer service port.
E 23
 * Most of this code comes from rcmd.c.
 */
I 17
int
E 17
D 3
getport()
E 3
I 3
D 23
getport(rhost)
E 23
I 23
getport(rhost, rport)
E 23
	char *rhost;
I 23
	int rport;
E 23
E 3
{
	struct hostent *hp;
	struct servent *sp;
	struct sockaddr_in sin;
	int s, timo = 1, lport = IPPORT_RESERVED - 1;
I 5
	int err;
E 5

	/*
	 * Get the host address and port number to connect to.
	 */
D 3
	if (RM == NULL)
E 3
I 3
	if (rhost == NULL)
E 3
		fatal("no remote host to connect to");
D 3
	hp = gethostbyname(RM);
E 3
I 3
D 23
	hp = gethostbyname(rhost);
E 3
	if (hp == NULL)
D 3
		fatal("unknown host %s", RM);
E 3
I 3
		fatal("unknown host %s", rhost);
E 3
	sp = getservbyname("printer", "tcp");
	if (sp == NULL)
		fatal("printer/tcp: unknown service");
E 23
	bzero((char *)&sin, sizeof(sin));
D 23
	bcopy(hp->h_addr, (caddr_t)&sin.sin_addr, hp->h_length);
	sin.sin_family = hp->h_addrtype;
	sin.sin_port = sp->s_port;
E 23
I 23
	sin.sin_addr.s_addr = inet_addr(rhost);
	if (sin.sin_addr.s_addr != INADDR_NONE)
		sin.sin_family = AF_INET;
	else {
		hp = gethostbyname(rhost);
		if (hp == NULL)
			fatal("unknown host %s", rhost);
		bcopy(hp->h_addr, (caddr_t)&sin.sin_addr, hp->h_length);
		sin.sin_family = hp->h_addrtype;
	}
	if (rport == 0) {
		sp = getservbyname("printer", "tcp");
		if (sp == NULL)
			fatal("printer/tcp: unknown service");
		sin.sin_port = sp->s_port;
	} else
		sin.sin_port = htons(rport);
E 23

	/*
	 * Try connecting to the server.
	 */
retry:
	s = rresvport(&lport);
	if (s < 0)
		return(-1);
D 14
	if (connect(s, (caddr_t)&sin, sizeof(sin), 0) < 0) {
E 14
I 14
D 16
	if (connect(s, (caddr_t)&sin, sizeof(sin)) < 0) {
E 16
I 16
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
E 16
E 14
I 5
		err = errno;
		(void) close(s);
		errno = err;
E 5
		if (errno == EADDRINUSE) {
D 5
			close(s);
E 5
			lport--;
			goto retry;
		}
		if (errno == ECONNREFUSED && timo <= 16) {
D 5
			(void) close(s);
E 5
			sleep(timo);
			timo *= 2;
			goto retry;
		}
		return(-1);
	}
	return(s);
}

D 11
rresvport(alport)
	int *alport;
{
	struct sockaddr_in sin;
	int s;

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
		return(-1);
D 5
	for (;;) {
E 5
I 5
	for (; *alport > IPPORT_RESERVED/2; (*alport)--) {
E 5
		sin.sin_port = htons((u_short) *alport);
		if (bind(s, (caddr_t)&sin, sizeof(sin), 0) >= 0)
			return(s);
		if (errno != EADDRINUSE && errno != EADDRNOTAVAIL)
D 5
			return(-1);
		(*alport)--;
D 3
		if (*alport == IPPORT_RESERVED/2) {
			printf("%s: All ports in use\n", name);
E 3
I 3
		if (*alport == IPPORT_RESERVED/2)
E 3
			return(-1);
E 5
I 5
			break;
E 5
D 3
		}
E 3
	}
I 5
	(void) close(s);
	return(-1);
E 5
}

E 11
/*
 * Getline reads a line from the control file cfp, removes tabs, converts
 *  new-line to null and leaves it in line.
 * Returns 0 at EOF or the number of characters read.
 */
I 17
int
E 17
getline(cfp)
	FILE *cfp;
{
	register int linel = 0;
	register char *lp = line;
	register c;

	while ((c = getc(cfp)) != '\n') {
		if (c == EOF)
			return(0);
		if (c == '\t') {
			do {
				*lp++ = ' ';
				linel++;
			} while ((linel & 07) != 0);
			continue;
		}
		*lp++ = c;
		linel++;
	}
	*lp++ = '\0';
	return(linel);
}

/*
 * Scan the current directory and make a list of daemon files sorted by
 * creation time.
 * Return the number of entries and a pointer to the list.
 */
I 17
int
E 17
getq(namelist)
	struct queue *(*namelist[]);
{
D 17
	register struct direct *d;
E 17
I 17
	register struct dirent *d;
E 17
	register struct queue *q, **queue;
	register int nitems;
	struct stat stbuf;
D 16
	int arraysz, compar();
E 16
	DIR *dirp;
I 16
	int arraysz;
D 17
	static int compar();
E 17
E 16

D 6
	if ((dirp = opendir(".")) == NULL)
E 6
I 6
	if ((dirp = opendir(SD)) == NULL)
E 6
		return(-1);
	if (fstat(dirp->dd_fd, &stbuf) < 0)
D 5
		return(-1);
E 5
I 5
		goto errdone;
E 5

	/*
	 * Estimate the array size by taking the size of the directory file
	 * and dividing it by a multiple of the minimum size entry. 
	 */
	arraysz = (stbuf.st_size / 24);
	queue = (struct queue **)malloc(arraysz * sizeof(struct queue *));
	if (queue == NULL)
D 5
		return(-1);
E 5
I 5
		goto errdone;
E 5

	nitems = 0;
	while ((d = readdir(dirp)) != NULL) {
		if (d->d_name[0] != 'c' || d->d_name[1] != 'f')
			continue;	/* daemon control files only */
		if (stat(d->d_name, &stbuf) < 0)
			continue;	/* Doesn't exist */
		q = (struct queue *)malloc(sizeof(time_t)+strlen(d->d_name)+1);
		if (q == NULL)
D 5
			return(-1);
E 5
I 5
			goto errdone;
E 5
		q->q_time = stbuf.st_mtime;
		strcpy(q->q_name, d->d_name);
		/*
		 * Check to make sure the array has space left and
		 * realloc the maximum size.
		 */
		if (++nitems > arraysz) {
I 22
			arraysz *= 2;
E 22
			queue = (struct queue **)realloc((char *)queue,
D 22
				(stbuf.st_size/12) * sizeof(struct queue *));
E 22
I 22
				arraysz * sizeof(struct queue *));
E 22
			if (queue == NULL)
D 5
				return(-1);
E 5
I 5
				goto errdone;
E 5
		}
		queue[nitems-1] = q;
	}
	closedir(dirp);
	if (nitems)
		qsort(queue, nitems, sizeof(struct queue *), compar);
	*namelist = queue;
	return(nitems);
I 5

errdone:
	closedir(dirp);
	return(-1);
E 5
}

/*
 * Compare modification times.
 */
D 17
static
E 17
I 17
static int
E 17
compar(p1, p2)
D 17
	register struct queue **p1, **p2;
E 17
I 17
	const void *p1, *p2;
E 17
{
D 17
	if ((*p1)->q_time < (*p2)->q_time)
E 17
I 17
	if ((*(struct queue **)p1)->q_time < (*(struct queue **)p2)->q_time)
E 17
		return(-1);
D 17
	if ((*p1)->q_time > (*p2)->q_time)
E 17
I 17
	if ((*(struct queue **)p1)->q_time > (*(struct queue **)p2)->q_time)
E 17
		return(1);
	return(0);
I 14
}

/*
 * Figure out whether the local machine is the same
 * as the remote machine (RM) entry (if it exists).
 */
char *
checkremote()
{
	char name[MAXHOSTNAMELEN];
	register struct hostent *hp;
	static char errbuf[128];

D 23
	sendtorem = 0;	/* assume printer is local */
	if (RM != (char *)NULL) {
E 23
I 23
	remote = 0;	/* assume printer is local */
	if (RM != NULL) {
E 23
		/* get the official name of the local host */
		gethostname(name, sizeof(name));
		name[sizeof(name)-1] = '\0';
		hp = gethostbyname(name);
		if (hp == (struct hostent *) NULL) {
D 17
		    (void) sprintf(errbuf,
E 17
I 17
		    (void) snprintf(errbuf, sizeof(errbuf),
E 17
			"unable to get official name for local machine %s",
			name);
		    return errbuf;
		} else (void) strcpy(name, hp->h_name);

		/* get the official name of RM */
		hp = gethostbyname(RM);
		if (hp == (struct hostent *) NULL) {
D 17
		    (void) sprintf(errbuf,
E 17
I 17
		    (void) snprintf(errbuf, sizeof(errbuf),
E 17
			"unable to get official name for remote machine %s",
			RM);
		    return errbuf;
		}

		/*
		 * if the two hosts are not the same,
		 * then the printer must be remote.
		 */
D 22
		if (strcmp(name, hp->h_name) != 0)
E 22
I 22
		if (strcasecmp(name, hp->h_name) != 0)
E 22
D 23
			sendtorem = 1;
E 23
I 23
			remote = 1;
E 23
	}
D 22
	return (char *)0;
E 22
I 22
	return NULL;
I 23
}

/* sleep n milliseconds */
void
delay(n)
{
	struct timeval tdelay;

	if (n <= 0 || n > 10000)
		fatal("unreasonable delay period (%d)", n);
	tdelay.tv_sec = n / 1000;
	tdelay.tv_usec = n * 1000 % 1000000;
	(void) select(0, (fd_set *)0, (fd_set *)0, (fd_set *)0, &tdelay);
E 23
E 22
E 14
D 2
}

/*VARARGS1*/
status(msg, a1, a2, a3)
	char *msg;
{
	register int fd;
	char buf[BUFSIZ];

	umask(0);
	if ((fd = open(ST, FWRONLY|FCREATE|FTRUNCATE|FEXLOCK, 0664)) < 0)
		fatal("cannot create status file");
	sprintf(buf, msg, a1, a2, a3);
	strcat(buf, "\n");
	(void) write(fd, buf, strlen(buf));
	(void) close(fd);
E 2
}

D 17
/*VARARGS1*/
fatal(msg, a1, a2, a3)
E 17
I 17
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
fatal(const char *msg, ...)
#else
fatal(msg, va_alist)
E 17
	char *msg;
I 17
        va_dcl
#endif
E 17
{
I 17
	va_list ap;
#if __STDC__
	va_start(ap, msg);
#else
	va_start(ap);
#endif
E 17
	if (from != host)
D 17
		printf("%s: ", host);
	printf("%s: ", name);
E 17
I 17
		(void)printf("%s: ", host);
	(void)printf("%s: ", name);
E 17
	if (printer)
D 17
		printf("%s: ", printer);
	printf(msg, a1, a2, a3);
	putchar('\n');
E 17
I 17
		(void)printf("%s: ", printer);
	(void)vprintf(msg, ap);
	va_end(ap);
	(void)putchar('\n');
E 17
	exit(1);
}
D 4

fatalerror(msg)
	char *msg;
{
	extern int sys_nerr;
	extern char *sys_errlist[];

	printf("%s: ", name);
	if (*msg)
		printf("%s: ", msg);
	fputs(errno < sys_nerr ? sys_errlist[errno] : "Unknown error" , stdout);
	putchar('\n');
	exit(1);
}
E 4
E 1
