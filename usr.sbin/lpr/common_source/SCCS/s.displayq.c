h20386
s 00001/00000/00423
d D 8.4 95/04/28 15:38:29 tef 33 32
c Better portability to other systems.
e
s 00007/00007/00416
d D 8.3 95/04/28 12:16:49 tef 32 31
c Support for printers connected via ethernet/TCP and terminal servers.
e
s 00005/00005/00418
d D 8.2 95/04/27 21:37:57 tef 31 30
c Bug fixes.
e
s 00002/00002/00421
d D 8.1 93/06/06 13:58:48 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00028/00421
d D 5.16 92/09/14 16:30:19 elan 29 28
c Added SCCS keywords.
e
s 00051/00024/00398
d D 5.15 92/09/01 11:08:01 elan 28 27
c Rewrote to use new getcap(3) library.  Major prototyping and cleanup.
e
s 00035/00012/00387
d D 5.14 92/07/21 10:28:18 bostic 27 26
c prototype lpr to fix quad's
e
s 00001/00011/00398
d D 5.13 90/06/01 18:43:57 bostic 26 25
c new copyright notice
e
s 00000/00002/00409
d D 5.12 90/03/20 13:22:08 tef 25 24
c remove needless declaration
e
s 00002/00036/00409
d D 5.11 89/08/22 21:02:28 tef 24 23
c common code for checking if rm==localhost
e
s 00001/00001/00444
d D 5.10 89/07/27 10:20:48 bostic 23 22
c handle large queues; bug report 4.3BSD-tahoe/usr.bin/24
e
s 00003/00002/00442
d D 5.9 89/05/11 14:09:30 bostic 22 21
c file reorg, pathnames.h, paths.h
e
s 00010/00005/00434
d D 5.8 88/06/30 17:59:42 bostic 21 20
c install approved copyright notice
e
s 00002/00002/00437
d D 5.7 88/06/01 16:49:53 bostic 20 19
c don't support %D anymore
e
s 00009/00003/00430
d D 5.6 88/05/05 18:07:43 bostic 19 18
c written by Ralph Campbell; add Berkeley specific header
e
s 00001/00001/00432
d D 5.5 87/06/23 12:08:02 karels 18 17
c restore keywords
e
s 00003/00002/00430
d D 5.4 87/06/23 12:06:55 karels 17 16
c don't check remote on local printer
e
s 00086/00084/00346
d D 5.3 87/04/30 18:00:20 bostic 16 15
c display local queue first, then foreign queue
e
s 00033/00001/00397
d D 5.2 85/11/11 15:33:55 tef 15 14
c Can now specify both lp= and rm=/rp= in same printcap entry; lpd
c will figure out if printer is on local machine or not and do the right thing.
e
s 00007/00001/00391
d D 5.1 85/06/06 09:59:05 dist 14 13
c Add copyright
e
s 00011/00019/00381
d D 4.12 84/07/24 16:57:21 ralph 13 12
c don't make vars static - rename
e
s 00022/00019/00378
d D 4.11 84/03/19 15:30:02 ralph 12 11
c print down status even if queue is empty.
e
s 00013/00004/00384
d D 4.10 84/01/30 16:16:05 ralph 11 10
c added lpc down printer "status message".
e
s 00004/00001/00384
d D 4.9 83/07/17 00:10:58 sam 10 9
c put sccs id's to some use
e
s 00046/00029/00339
d D 4.8 83/06/29 17:08:51 ralph 9 8
c changed to use unix domain ipc.
e
s 00005/00005/00363
d D 4.7 83/06/17 15:09:29 ralph 8 7
c fixed `fc' and `fs' when 0177777 is needed.
e
s 00004/00002/00364
d D 4.6 83/06/15 14:56:58 sam 7 6
c open and flock defines changed
e
s 00022/00014/00344
d D 4.5 83/06/02 12:24:24 ralph 6 5
c made local variables static to improve separation between functions.
e
s 00008/00002/00350
d D 4.4 83/05/27 10:14:17 ralph 5 3
c improved queue status messages
e
s 00008/00003/00349
d R 4.4 83/05/27 09:47:10 ralph 4 3
c improved queue status reporting
e
s 00001/00001/00351
d D 4.3 83/05/18 16:46:08 ralph 3 2
c fixed lprm segmentation fault when remote is down.
e
s 00015/00013/00337
d D 4.2 83/05/13 11:55:11 ralph 2 1
c bugfixes and changes for lpc command.
e
s 00350/00000/00000
d D 4.1 83/04/29 11:30:19 ralph 1 0
c date and time created 83/04/29 11:30:19 by ralph
e
u
U
t
T
I 14
/*
D 30
 * Copyright (c) 1983 Regents of the University of California.
D 19
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 19
I 19
 * All rights reserved.
E 30
I 30
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 30
 *
D 26
 * Redistribution and use in source and binary forms are permitted
D 21
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 21
I 21
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
E 26
I 26
D 28
 * %sccs.include.redist.c%
E 28
I 28
D 29
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
E 29
I 29
 * %sccs.include.redist.c%
E 29
E 28
E 26
E 21
E 19
 */

E 14
I 1
D 10
/*	%M%	%I%	%E%	*/
E 10
I 10
#ifndef lint
D 15
static char sccsid[] = "%W% (Berkeley) %G%";
E 15
I 15
D 18
static char sccsid[] = "@(#)displayq.c	5.1 (Berkeley) 6/6/85";
E 18
I 18
D 28
static char sccsid[] = "%W% (Berkeley) %G%";
E 28
I 28
D 29
static char sccsid[] = "@(#)displayq.c	5.16 (Berkeley) 8/31/92";
E 29
I 29
static char sccsid[] = "%W% (Berkeley) %G%";
E 29
E 28
E 18
E 15
D 14
#endif
E 14
I 14
D 19
#endif not lint
E 19
I 19
#endif /* not lint */
E 19
E 14

E 10
D 27
/*
 * Routines to display the state of the queue.
 */
E 27
I 27
#include <sys/param.h>
#include <sys/stat.h>
I 33
#include <sys/file.h>
E 33
E 27

I 27
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
E 27
#include "lp.h"
I 27
#include "lp.local.h"
E 27
I 22
#include "pathnames.h"
E 22

I 27
/*
 * Routines to display the state of the queue.
 */
E 27
D 6
#define	JOBCOL		40	/* column for job # in -l format */
#define OWNCOL		7	/* start of Owner column in normal */
E 6
I 6
D 8
#define JOBCOL	40	/* column for job # in -l format */
#define OWNCOL	7	/* start of Owner column in normal */
#define SIZCOL	62	/* start of Size column in normal */
E 8
I 8
#define JOBCOL	40		/* column for job # in -l format */
#define OWNCOL	7		/* start of Owner column in normal */
#define SIZCOL	62		/* start of Size column in normal */
E 8
E 6

/*
 * Stuff for handling job specifications
 */
D 28
extern char	*user[];	/* users to process */
extern int	users;		/* # of users in user array */
E 28
extern int	requ[];		/* job number of spool entries */
extern int	requests;	/* # of spool requests */
I 28
extern char    *user[];	        /* users to process */
extern int	users;		/* # of users in user array */
E 28

D 6
int	lflag;			/* long output option */
char	current[40];		/* current file being printed */
int	garbage;		/* # of garbage cf files */
int	rank;			/* order to be printed (-1=none, 0=active) */
long	totsize;		/* total print job size in bytes */
int	first;			/* first file in ``files'' column? */
int	col;			/* column on screen */
int	SIZCOL = 62;		/* start of Size column in normal */
int	sendtorem;		/* are we sending to a remote? */
char	file[132];		/* print file name */
E 6
I 6
D 13
static int	lflag;		/* long output option */
static char	current[40];	/* current file being printed */
static int	garbage;	/* # of garbage cf files */
static int	rank;		/* order to be printed (-1=none, 0=active) */
static long	totsize;	/* total print job size in bytes */
static int	first;		/* first file in ``files'' column? */
static int	col;		/* column on screen */
static int	sendtorem;	/* are we sending to a remote? */
static char	file[132];	/* print file name */
E 13
I 13
D 28
int	lflag;		/* long output option */
char	current[40];	/* current file being printed */
int	garbage;	/* # of garbage cf files */
int	rank;		/* order to be printed (-1=none, 0=active) */
long	totsize;	/* total print job size in bytes */
int	first;		/* first file in ``files'' column? */
int	col;		/* column on screen */
D 24
int	sendtorem;	/* are we sending to a remote? */
E 24
char	file[132];	/* print file name */
E 28
I 28
static int	col;		/* column on screen */
static char	current[40];	/* current file being printed */
static char	file[132];	/* print file name */
static int	first;		/* first file in ``files'' column? */
static int	garbage;	/* # of garbage cf files */
static int	lflag;		/* long output option */
static int	rank;		/* order to be printed (-1=none, 0=active) */
static long	totsize;	/* total print job size in bytes */
E 28
E 13
E 6

D 6
char	*head0 = "Rank   Owner      Job  Files";
char	*head1 = "Total Size\n";
E 6
I 6
D 13
static char	*head0 = "Rank   Owner      Job  Files";
static char	*head1 = "Total Size\n";
E 13
I 13
D 28
char	*head0 = "Rank   Owner      Job  Files";
char	*head1 = "Total Size\n";
E 28
I 28
static char	*head0 = "Rank   Owner      Job  Files";
static char	*head1 = "Total Size\n";
E 28
E 13
E 6

/*
 * Display the current state of the queue. Format = 1 if long format.
 */
I 27
void
E 27
displayq(format)
	int format;
{
	register struct queue *q;
	register int i, nitems, fd;
I 16
	register char	*cp;
E 16
	struct queue **queue;
	struct stat statb;
	FILE *fp;
I 16
D 27
	char c;
E 27
E 16

D 2
	name = "displayq";
E 2
	lflag = format;
	totsize = 0;
	rank = -1;
D 28

	if ((i = pgetent(line, printer)) < 0)
		fatal("cannot open printer description file");
	else if (i == 0)
E 28
I 28
	if ((i = cgetent(&bp, printcapdb, printer)) == -2)
		fatal("can't open printer description file");
	else if (i == -1)
E 28
		fatal("unknown printer");
D 28
	if ((LP = pgetstr("lp", &bp)) == NULL)
E 28
I 28
	else if (i == -3)
		fatal("potential reference loop detected in printcap file");
	if (cgetstr(bp, "lp", &LP) < 0)
E 28
D 22
		LP = DEFDEVLP;
E 22
I 22
		LP = _PATH_DEFDEVLP;
E 22
D 28
	if ((RP = pgetstr("rp", &bp)) == NULL)
E 28
I 28
	if (cgetstr(bp, "rp", &RP) < 0)
E 28
D 2
		RP = printer;
E 2
I 2
		RP = DEFLP;
E 2
D 28
	if ((SD = pgetstr("sd", &bp)) == NULL)
E 28
I 28
	if (cgetstr(bp, "sd", &SD) < 0)
E 28
D 22
		SD = DEFSPOOL;
E 22
I 22
		SD = _PATH_DEFSPOOL;
E 22
D 28
	if ((LO = pgetstr("lo", &bp)) == NULL)
E 28
I 28
	if (cgetstr(bp,"lo", &LO) < 0)
E 28
		LO = DEFLOCK;
D 28
	if ((ST = pgetstr("st", &bp)) == NULL)
E 28
I 28
	if (cgetstr(bp, "st", &ST) < 0)
E 28
		ST = DEFSTAT;
D 28
	RM = pgetstr("rm", &bp);
E 28
I 28
	cgetstr(bp, "rm", &RM);
E 28
I 15
D 24

	/*
	 * Figure out whether the local machine is the same as the remote 
	 * machine entry (if it exists).  If not, then ignore the local
	 * queue information.
	 */
	 if (RM != (char *) NULL) {
		char name[256];
		struct hostent *hp;

		/* get the standard network name of the local host */
		gethostname(name, sizeof(name));
		name[sizeof(name)-1] = '\0';
		hp = gethostbyname(name);
		if (hp == (struct hostent *) NULL) {
		    printf("unable to get network name for local machine %s\n",
			name);
		    goto localcheck_done;
D 16
		} else strcpy(name, hp->h_name);
E 16
I 16
		} else (void) strcpy(name, hp->h_name);
E 16

		/* get the network standard name of RM */
		hp = gethostbyname(RM);
		if (hp == (struct hostent *) NULL) {
		    printf("unable to get hostname for remote machine %s\n",
			RM);
		    goto localcheck_done;
		}

		/* if printer is not on local machine, ignore LP */
D 16
		if (strcmp(name, hp->h_name) != 0) *LP = '\0';
E 16
I 16
		if (strcmp(name, hp->h_name)) {
			*LP = '\0';
			++sendtorem;
		}
E 16
	}
localcheck_done:
E 24
I 24
	if (cp = checkremote())
		printf("Warning: %s\n", cp);
E 24
E 15

	/*
D 16
	 * If there is no local printer, then print the queue on
	 * the remote machine and then what's in the queue here.
	 * Note that a file in transit may not show up in either queue.
	 */
	if (*LP == '\0') {
		register char *cp;
		char c;

		sendtorem++;
		(void) sprintf(line, "%c%s", format + '\3', RP);
		cp = line;
		for (i = 0; i < requests; i++) {
			cp += strlen(cp);
			(void) sprintf(cp, " %d", requ[i]);
		}
		for (i = 0; i < users; i++) {
			cp += strlen(cp);
			*cp++ = ' ';
			strcpy(cp, user[i]);
		}
		strcat(line, "\n");
D 3
		fd = getport();
E 3
I 3
		fd = getport(RM);
E 3
		if (fd < 0) {
			if (from != host)
				printf("%s: ", host);
			printf("connection to %s is down\n", RM);
		} else {
			i = strlen(line);
			if (write(fd, line, i) != i)
				fatal("Lost connection");
			while ((i = read(fd, line, sizeof(line))) > 0)
				(void) fwrite(line, 1, i, stdout);
			(void) close(fd);
		}
	}
	/*
E 16
I 16
	 * Print out local queue
E 16
	 * Find all the control files in the spooling directory
	 */
	if (chdir(SD) < 0)
		fatal("cannot chdir to spooling directory");
	if ((nitems = getq(&queue)) < 0)
		fatal("cannot examine spooling area\n");
D 5
	if (nitems == 0) {
E 5
I 5
D 12
	if (stat(LO, &statb) >= 0 && (statb.st_mode & 010)) {
E 5
		if (sendtorem)
			printf("\n%s: ", host);
D 5
		printf("no entries\n");
E 5
I 5
		printf("Warning: %s queue is turned off\n", printer);
E 12
I 12
	if (stat(LO, &statb) >= 0) {
D 16
		if ((statb.st_mode & 0110) && sendtorem)
			printf("\n");
E 16
		if (statb.st_mode & 0100) {
D 32
			if (sendtorem)
E 32
I 32
			if (remote)
E 32
				printf("%s: ", host);
			printf("Warning: %s is down: ", printer);
			fd = open(ST, O_RDONLY);
			if (fd >= 0) {
				(void) flock(fd, LOCK_SH);
				while ((i = read(fd, line, sizeof(line))) > 0)
					(void) fwrite(line, 1, i, stdout);
				(void) close(fd);	/* unlocks as well */
			} else
				putchar('\n');
		}
		if (statb.st_mode & 010) {
D 32
			if (sendtorem)
E 32
I 32
			if (remote)
E 32
				printf("%s: ", host);
			printf("Warning: %s queue is turned off\n", printer);
		}
E 12
	}
D 16
	if (nitems == 0) {
		if (!sendtorem)
			printf("no entries\n");
E 5
		return(0);
	}
	fp = fopen(LO, "r");
D 7
	if (fp == NULL || flock(fileno(fp), FSHLOCK|FNBLOCK) == 0) {
E 7
I 7
D 9
	if (fp == NULL || flock(fileno(fp), LOCK_SH|LOCK_NB) == 0) {
E 7
		if (fp != NULL)
D 8
			fclose(fp);
E 8
I 8
			fclose(fp);	/* unlocks as well */
E 8
		garbage = nitems;
I 5
		if (sendtorem)
			printf("\n%s: ", host);
E 5
D 2
		if (*LP && stat(LP, &statb) >= 0 && (statb.st_mode & 0777) == 0)
			status("Warning: %s is down", printer);
E 2
I 2
		if (stat(LO, &statb) >= 0 && (statb.st_mode & 0100))
			printf("Warning: %s is down\n", printer);
E 2
		else
D 2
			status("Warning: no daemon present");
E 2
I 2
			printf("Warning: no daemon present\n");
E 2
	} else {
		register char *cp = current;
E 9
I 9
	if (fp == NULL)
		warn();
	else {
		register char *cp;
E 16
E 9

D 9
		/* skip daemon pid */
		while ((*cp = getc(fp)) != EOF && *cp != '\n');
		/* read current file name */
E 9
I 9
D 16
		/* get daemon pid */
		cp = current;
E 9
		while ((*cp = getc(fp)) != EOF && *cp != '\n')
			cp++;
		*cp = '\0';
D 9
		fclose(fp);
I 2
		/*
		 * Print the status file to show what the daemon is doing.
		 */
		if (sendtorem)
			printf("\n%s: ", host);
D 7
		if ((fd = open(ST, FRDONLY|FSHLOCK)) >= 0) {
E 7
I 7
		fd = open(ST, O_RDONLY);
		if (fd >= 0) {
			(void) flock(fd, LOCK_SH);
E 7
			while ((i = read(fd, line, sizeof(line))) > 0)
				(void) fwrite(line, 1, i, stdout);
D 8
			(void) close(fd);
E 8
I 8
			(void) close(fd);	/* unlocks as well */
E 8
		} else
			putchar('\n');
E 9
I 9
		i = atoi(current);
D 11
		if (kill(i, 0) < 0)
E 11
I 11
		if (i <= 0 || kill(i, 0) < 0)
E 16
I 16
	if (nitems) {
		fp = fopen(LO, "r");
		if (fp == NULL)
E 16
E 11
			warn();
		else {
D 16
			/* read current file name */
E 16
I 16
D 25
			register char *cp;

E 25
			/* get daemon pid */
E 16
			cp = current;
D 31
			while ((*cp = getc(fp)) != EOF && *cp != '\n')
				cp++;
E 31
I 31
			while ((i = getc(fp)) != EOF && i != '\n')
				*cp++ = i;
E 31
			*cp = '\0';
D 16
			/*
			 * Print the status file.
			 */
			if (sendtorem)
				printf("\n%s: ", host);
			fd = open(ST, O_RDONLY);
			if (fd >= 0) {
				(void) flock(fd, LOCK_SH);
				while ((i = read(fd, line, sizeof(line))) > 0)
					(void) fwrite(line, 1, i, stdout);
				(void) close(fd);	/* unlocks as well */
			} else
				putchar('\n');
E 16
I 16
			i = atoi(current);
			if (i <= 0 || kill(i, 0) < 0)
				warn();
			else {
				/* read current file name */
				cp = current;
D 31
				while ((*cp = getc(fp)) != EOF && *cp != '\n')
					cp++;
E 31
I 31
				while ((i = getc(fp)) != EOF && i != '\n')
					*cp++ = i;
E 31
				*cp = '\0';
				/*
				 * Print the status file.
				 */
D 32
				if (sendtorem)
E 32
I 32
				if (remote)
E 32
					printf("%s: ", host);
				fd = open(ST, O_RDONLY);
				if (fd >= 0) {
					(void) flock(fd, LOCK_SH);
					while ((i = read(fd, line, sizeof(line))) > 0)
						(void) fwrite(line, 1, i, stdout);
					(void) close(fd);	/* unlocks as well */
				} else
					putchar('\n');
			}
			(void) fclose(fp);
E 16
		}
D 16
		(void) fclose(fp);
E 16
I 16
		/*
		 * Now, examine the control files and print out the jobs to
		 * be done for each user.
		 */
		if (!lflag)
			header();
		for (i = 0; i < nitems; i++) {
			q = queue[i];
			inform(q->q_name);
			free(q);
		}
		free(queue);
E 16
E 9
E 2
	}
I 16
D 17
	else if (!sendtorem) {
		puts("no entries");
E 17
I 17
D 32
	if (!sendtorem) {
E 32
I 32
	if (!remote) {
E 32
		if (nitems == 0)
			puts("no entries");
E 17
		return;
	}

E 16
	/*
D 16
	 * Now, examine the control files and print out the jobs to
	 * be done for each user.
E 16
I 16
	 * Print foreign queue
	 * Note that a file in transit may show up in either queue.
E 16
	 */
D 2
	if (sendtorem)
		printf("\n%s: ", host);
	if ((fd = open(ST, FRDONLY|FSHLOCK)) >= 0) {
		while ((i = read(fd, line, sizeof(line))) > 0)
			(void) fwrite(line, 1, i, stdout);
		(void) close(fd);
	} else
		putchar('\n');
E 2
D 16
	if (!lflag)
		header();
	for (i = 0; i < nitems; i++) {
		q = queue[i];
		inform(q->q_name);
		free(q);
E 16
I 16
	if (nitems)
		putchar('\n');
	(void) sprintf(line, "%c%s", format + '\3', RP);
	cp = line;
	for (i = 0; i < requests; i++) {
		cp += strlen(cp);
		(void) sprintf(cp, " %d", requ[i]);
E 16
	}
D 16
	free(queue);
	return(nitems-garbage);
E 16
I 16
	for (i = 0; i < users; i++) {
		cp += strlen(cp);
		*cp++ = ' ';
		(void) strcpy(cp, user[i]);
	}
	strcat(line, "\n");
D 32
	fd = getport(RM);
E 32
I 32
	fd = getport(RM, 0);
E 32
	if (fd < 0) {
		if (from != host)
			printf("%s: ", host);
		printf("connection to %s is down\n", RM);
	}
	else {
		i = strlen(line);
		if (write(fd, line, i) != i)
			fatal("Lost connection");
		while ((i = read(fd, line, sizeof(line))) > 0)
			(void) fwrite(line, 1, i, stdout);
		(void) close(fd);
	}
E 16
I 9
}

/*
 * Print a warning message if there is no daemon present.
 */
I 27
void
E 27
warn()
{
D 12
	struct stat statb;
I 11
	int i, fd;
E 11

E 12
D 32
	if (sendtorem)
E 32
I 32
	if (remote)
E 32
		printf("\n%s: ", host);
D 11
	if (stat(LO, &statb) >= 0 && (statb.st_mode & 0100))
		printf("Warning: %s is down\n", printer);
	else
E 11
I 11
D 12
	if (stat(LO, &statb) >= 0 && (statb.st_mode & 0100)) {
		printf("Warning: %s is down: ", printer);
		fd = open(ST, O_RDONLY);
		if (fd >= 0) {
			(void) flock(fd, LOCK_SH);
			while ((i = read(fd, line, sizeof(line))) > 0)
				(void) fwrite(line, 1, i, stdout);
			(void) close(fd);	/* unlocks as well */
		} else
			putchar('\n');
	} else
E 11
		printf("Warning: no daemon present\n");
E 12
I 12
D 16
	printf("Warning: no daemon present\n");
E 16
I 16
	puts("Warning: no daemon present");
E 16
E 12
	current[0] = '\0';
E 9
}

/*
 * Print the header for the short listing format
 */
I 27
void
E 27
I 6
D 13
static
E 13
E 6
header()
{
	printf(head0);
	col = strlen(head0)+1;
	blankfill(SIZCOL);
	printf(head1);
}

I 27
void
E 27
I 6
D 13
static
E 13
E 6
inform(cf)
	char *cf;
{
D 27
	register int j, k;
	register char *cp;
E 27
I 27
	register int j;
E 27
	FILE *cfp;

	/*
	 * There's a chance the control file has gone away
	 * in the meantime; if this is the case just keep going
	 */
	if ((cfp = fopen(cf, "r")) == NULL)
		return;

	if (rank < 0)
		rank = 0;
D 32
	if (sendtorem || garbage || strcmp(cf, current))
E 32
I 32
	if (remote || garbage || strcmp(cf, current))
E 32
		rank++;
	j = 0;
	while (getline(cfp)) {
		switch (line[0]) {
		case 'P': /* Was this file specified in the user's list? */
			if (!inlist(line+1, cf)) {
				fclose(cfp);
				return;
			}
			if (lflag) {
				printf("\n%s: ", line+1);
				col = strlen(line+1) + 2;
				prank(rank);
				blankfill(JOBCOL);
				printf(" [job %s]\n", cf+3);
			} else {
				col = 0;
				prank(rank);
				blankfill(OWNCOL);
				printf("%-10s %-3d  ", line+1, atoi(cf+3));
				col += 16;
				first = 1;
			}
			continue;
		default: /* some format specifer and file name? */
			if (line[0] < 'a' || line[0] > 'z')
				continue;
			if (j == 0 || strcmp(file, line+1) != 0)
D 16
				strcpy(file, line+1);
E 16
I 16
				(void) strcpy(file, line+1);
E 16
			j++;
			continue;
		case 'N':
			show(line+1, file, j);
			file[0] = '\0';
			j = 0;
		}
	}
	fclose(cfp);
	if (!lflag) {
		blankfill(SIZCOL);
D 20
		printf("%D bytes\n", totsize);
E 20
I 20
		printf("%ld bytes\n", totsize);
E 20
		totsize = 0;
	}
}

I 27
int
E 27
I 6
D 13
static
E 13
E 6
inlist(name, file)
	char *name, *file;
{
	register int *r, n;
	register char **u, *cp;

	if (users == 0 && requests == 0)
		return(1);
	/*
	 * Check to see if it's in the user list
	 */
	for (u = user; u < &user[users]; u++)
		if (!strcmp(*u, name))
			return(1);
	/*
	 * Check the request list
	 */
	for (n = 0, cp = file+3; isdigit(*cp); )
		n = n * 10 + (*cp++ - '0');
	for (r = requ; r < &requ[requests]; r++)
		if (*r == n && !strcmp(cp, from))
			return(1);
	return(0);
}

I 27
void
E 27
I 6
D 13
static
E 13
E 6
show(nfile, file, copies)
	register char *nfile, *file;
I 27
	int copies;
E 27
{
	if (strcmp(nfile, " ") == 0)
		nfile = "(standard input)";
	if (lflag)
		ldump(nfile, file, copies);
	else
		dump(nfile, file, copies);
}

/*
 * Fill the line with blanks to the specified column
 */
I 27
void
E 27
I 6
D 13
static
E 13
E 6
blankfill(n)
	register int n;
{
	while (col++ < n)
		putchar(' ');
}

/*
 * Give the abbreviated dump of the file names
 */
I 27
void
E 27
I 6
D 13
static
E 13
E 6
dump(nfile, file, copies)
	char *nfile, *file;
I 27
	int copies;
E 27
{
	register short n, fill;
	struct stat lbuf;

	/*
	 * Print as many files as will fit
	 *  (leaving room for the total size)
	 */
	 fill = first ? 0 : 2;	/* fill space for ``, '' */
	 if (((n = strlen(nfile)) + col + fill) >= SIZCOL-4) {
		if (col < SIZCOL) {
			printf(" ..."), col += 4;
			blankfill(SIZCOL);
		}
	} else {
		if (first)
			first = 0;
		else
			printf(", ");
		printf("%s", nfile);
		col += n+fill;
	}
	if (*file && !stat(file, &lbuf))
		totsize += copies * lbuf.st_size;
}

/*
 * Print the long info about the file
 */
I 27
void
E 27
I 6
D 13
static
E 13
E 6
ldump(nfile, file, copies)
	char *nfile, *file;
I 27
	int copies;
E 27
{
	struct stat lbuf;

	putchar('\t');
	if (copies > 1)
		printf("%-2d copies of %-19s", copies, nfile);
	else
		printf("%-32s", nfile);
	if (*file && !stat(file, &lbuf))
D 20
		printf(" %D bytes", lbuf.st_size);
E 20
I 20
D 27
		printf(" %ld bytes", lbuf.st_size);
E 27
I 27
D 31
		printf(" %qd bytes", lbuf.st_size);
E 31
I 31
		printf(" %ld bytes", (long)lbuf.st_size);
E 31
E 27
E 20
	else
		printf(" ??? bytes");
	putchar('\n');
}

/*
 * Print the job's rank in the queue,
 *   update col for screen management
 */
I 27
void
E 27
I 6
D 13
static
E 13
E 6
prank(n)
I 27
	int n;
E 27
{
D 27
	char line[100];
E 27
I 27
	char rline[100];
E 27
	static char *r[] = {
		"th", "st", "nd", "rd", "th", "th", "th", "th", "th", "th"
	};

	if (n == 0) {
		printf("active");
		col += 6;
		return;
	}
D 23
	if ((n/10) == 1)
E 23
I 23
	if ((n/10)%10 == 1)
E 23
D 27
		(void) sprintf(line, "%dth", n);
E 27
I 27
		(void)snprintf(rline, sizeof(rline), "%dth", n);
E 27
	else
D 27
		(void) sprintf(line, "%d%s", n, r[n%10]);
	col += strlen(line);
	printf("%s", line);
E 27
I 27
		(void)snprintf(rline, sizeof(rline), "%d%s", n, r[n%10]);
	col += strlen(rline);
	printf("%s", rline);
E 27
}
E 1
