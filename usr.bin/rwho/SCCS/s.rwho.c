h40183
s 00005/00005/00153
d D 8.1 93/06/06 16:12:03 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00157
d D 5.5 90/06/01 17:41:27 bostic 17 16
c new copyright notice
e
s 00002/00003/00166
d D 5.4 89/05/11 09:48:55 bostic 16 15
c file reorg, pathnames.h, paths.h
e
s 00039/00027/00130
d D 5.3 88/08/25 12:29:43 bostic 15 14
c add Berkeley specific header, getopt, minor cleanups, lint
e
s 00001/00001/00156
d D 5.2 85/06/18 19:27:53 mckusick 14 13
c rwhod.h moves to /usr/include/protocols
e
s 00014/00002/00143
d D 5.1 85/05/31 09:28:54 dist 13 12
c Add copyright
e
s 00001/00001/00144
d D 4.10 85/05/28 15:01:25 serge 12 11
c allow for hosts with long (> 16 characters) names
e
s 00006/00002/00139
d D 4.9 85/05/07 13:32:01 kupfer 11 8
c Wait 11 minutes before deciding a machine is down (same as ruptime).
c Define a macro for deciding if a machine is down.
e
s 00006/00002/00139
d R 4.9 85/05/07 13:25:13 kupfer 10 8
c Wait 11 minutes to decide a machine is down (same as ruptime).
c Use a macro, instead of hiding the test in the middle of the code.
e
s 00001/00001/00140
d R 4.9 84/12/05 17:49:55 edward 9 8
c efficiency
e
s 00005/00005/00136
d D 4.8 84/03/19 20:20:09 leres 8 7
c A perror() message and some pointers were left over from when the rwho
c directory was in /etc.
e
s 00003/00003/00138
d D 4.7 83/07/01 04:17:24 sam 7 6
c can't stand have rwhod.h in /usr/include
e
s 00007/00008/00134
d D 4.6 83/05/25 15:52:01 sam 6 5
c kludges to avoid new utmp format
e
s 00001/00000/00141
d D 4.5 83/05/05 11:45:01 sam 5 4
c directory not part of protocol, so moved out of rwhod.h
e
s 00001/00001/00140
d D 4.4 83/05/03 19:57:16 sam 4 3
c move from netser forces rwhod.h into /usr/include
e
s 00002/00002/00139
d D 4.3 82/12/24 21:04:59 sam 3 2
c port not byte swapped; no more asm.sed; 
c move spool area to /usr/spool/rwho so /etc is always changing
e
s 00002/00002/00139
d D 4.2 82/05/09 23:59:08 mckusick 2 1
c update to new fs
e
s 00141/00000/00000
d D 4.1 82/04/02 10:29:10 wnj 1 0
c date and time created 82/04/02 10:29:10 by wnj
e
u
U
t
T
I 13
/*
D 15
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
D 18
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
D 17
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 17
I 17
 * %sccs.include.redist.c%
E 17
E 15
 */

E 13
I 1
#ifndef lint
D 7
static char sccsid[] = "%W% %E%";
E 7
I 7
D 13
static char sccsid[] = "%W% (Berkeley) %E%";
E 7
#endif
E 13
I 13
D 18
char copyright[] =
D 15
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 15
I 15
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 15
 All rights reserved.\n";
E 18
I 18
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 18
D 15
#endif not lint
E 15
I 15
#endif /* not lint */
E 15

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 15
#endif not lint
E 15
I 15
#endif /* not lint */
E 15
E 13

D 2
#include <sys/types.h>		/* botch in ndir.h */
E 2
I 2
#include <sys/param.h>
E 2
D 15
#include <stdio.h>
E 15
D 2
#include <ndir.h>
E 2
I 2
D 7
#include <dir.h>
E 2
D 6
#include <utmp.h>
E 6
D 4
#include "rwhod.h"
E 4
I 4
#include <rwhod.h>
E 7
I 7
#include <sys/dir.h>
I 15
#include <sys/file.h>
E 15
D 14
#include "../etc/rwhod/rwhod.h"
E 14
I 14
#include <protocols/rwhod.h>
I 15
#include <stdio.h>
E 15
E 14
E 7
E 4

D 8
DIR	*etc;
E 8
I 8
DIR	*dirp;
E 8

struct	whod wd;
int	utmpcmp();
#define	NUSERS	1000
struct	myutmp {
D 15
	char	myhost[32];
E 15
I 15
	char	myhost[MAXHOSTNAMELEN];
E 15
	int	myidle;
D 6
	struct	utmp myutmp;
E 6
I 6
	struct	outmp myutmp;
E 6
} myutmp[NUSERS];
int	nusers;

#define	WHDRSIZE	(sizeof (wd) - sizeof (wd.wd_we))
I 5
D 16
#define	RWHODIR		"/usr/spool/rwho"
E 16
I 11
/* 
 * this macro should be shared with ruptime.
 */
#define	down(w,now)	((now) - (w)->wd_recvtime > 11 * 60)
E 11
E 5

char	*ctime(), *strcpy();
D 15
int	now;
E 15
I 15
time_t	now;
E 15
int	aflg;

main(argc, argv)
	int argc;
	char **argv;
{
I 15
	extern char *optarg;
	extern int optind;
	int ch;
E 15
	struct direct *dp;
	int cc, width;
	register struct whod *w = &wd;
	register struct whoent *we;
	register struct myutmp *mp;
	int f, n, i;
I 15
	time_t time();
E 15

D 15
	argc--, argv++;
again:
	if (argc > 0 && !strcmp(argv[0], "-a")) {
		argc--, argv++;
		aflg++;
		goto again;
	}
	(void) time(&now);
D 3
	if (chdir("/etc") < 0) {
		perror("/etc");
E 3
I 3
	if (chdir(RWHODIR) < 0) {
E 15
I 15
	while ((ch = getopt(argc, argv, "a")) != EOF)
		switch((char)ch) {
		case 'a':
			aflg = 1;
			break;
		case '?':
		default:
			fprintf(stderr, "usage: rwho [-a]\n");
			exit(1);
		}
D 16
	if (chdir(RWHODIR) || (dirp = opendir(".")) == NULL) {
E 15
		perror(RWHODIR);
E 16
I 16
	if (chdir(_PATH_RWHODIR) || (dirp = opendir(".")) == NULL) {
		perror(_PATH_RWHODIR);
E 16
E 3
		exit(1);
	}
D 8
	etc = opendir(".");
	if (etc == NULL) {
		perror("/etc");
E 8
I 8
D 15
	dirp = opendir(".");
	if (dirp == NULL) {
		perror(RWHODIR);
E 8
		exit(1);
	}
E 15
	mp = myutmp;
I 15
	(void)time(&now);
E 15
D 8
	while (dp = readdir(etc)) {
E 8
I 8
	while (dp = readdir(dirp)) {
E 8
D 15
		if (dp->d_ino == 0)
E 15
I 15
		if (dp->d_ino == 0 || strncmp(dp->d_name, "whod.", 5))
E 15
			continue;
D 15
		if (strncmp(dp->d_name, "whod.", 5))
			continue;
		f = open(dp->d_name, 0);
E 15
I 15
		f = open(dp->d_name, O_RDONLY);
E 15
		if (f < 0)
			continue;
		cc = read(f, (char *)&wd, sizeof (struct whod));
		if (cc < WHDRSIZE) {
			(void) close(f);
			continue;
		}
D 11
		if (now - w->wd_recvtime > 5 * 60) {
E 11
I 11
		if (down(w,now)) {
E 11
			(void) close(f);
			continue;
		}
		cc -= WHDRSIZE;
		we = w->wd_we;
		for (n = cc / sizeof (struct whoent); n > 0; n--) {
			if (aflg == 0 && we->we_idle >= 60*60) {
				we++;
				continue;
			}
			if (nusers >= NUSERS) {
				printf("too many users\n");
				exit(1);
			}
			mp->myutmp = we->we_utmp; mp->myidle = we->we_idle;
			(void) strcpy(mp->myhost, w->wd_hostname);
			nusers++; we++; mp++;
		}
		(void) close(f);
	}
	qsort((char *)myutmp, nusers, sizeof (struct myutmp), utmpcmp);
	mp = myutmp;
	width = 0;
	for (i = 0; i < nusers; i++) {
D 6
		int j = strlen(mp->myhost) + 1 + strlen(mp->myutmp.ut_line);
E 6
I 6
		int j = strlen(mp->myhost) + 1 + strlen(mp->myutmp.out_line);
E 6
		if (j > width)
			width = j;
		mp++;
	}
	mp = myutmp;
	for (i = 0; i < nusers; i++) {
D 12
		char buf[22];
E 12
I 12
		char buf[BUFSIZ];
E 12
D 6
		sprintf(buf, "%s:%s", mp->myhost, mp->myutmp.ut_line);
E 6
I 6
D 11
		sprintf(buf, "%s:%s", mp->myhost, mp->myutmp.out_line);
E 11
I 11
		(void)sprintf(buf, "%s:%s", mp->myhost, mp->myutmp.out_line);
E 11
E 6
		printf("%-8.8s %-*s %.12s",
D 6
		   mp->myutmp.ut_name,
E 6
I 6
		   mp->myutmp.out_name,
E 6
		   width,
		   buf,
D 6
		   ctime((time_t *)&mp->myutmp.ut_time)+4);
E 6
I 6
		   ctime((time_t *)&mp->myutmp.out_time)+4);
E 6
		mp->myidle /= 60;
		if (mp->myidle) {
			if (aflg) {
				if (mp->myidle >= 100*60)
					mp->myidle = 100*60 - 1;
				if (mp->myidle >= 60)
					printf(" %2d", mp->myidle / 60);
				else
					printf("   ");
			} else
				printf(" ");
			printf(":%02d", mp->myidle % 60);
		}
		printf("\n");
		mp++;
	}
	exit(0);
}

utmpcmp(u1, u2)
	struct myutmp *u1, *u2;
{
	int rc;

D 6
	rc = strncmp(u1->myutmp.ut_name, u2->myutmp.ut_name, 8);
E 6
I 6
	rc = strncmp(u1->myutmp.out_name, u2->myutmp.out_name, 8);
E 6
	if (rc)
		return (rc);
	rc = strncmp(u1->myhost, u2->myhost, 8);
	if (rc)
		return (rc);
D 6
	return (strncmp(u1->myutmp.ut_line, u2->myutmp.ut_line, 8));
E 6
I 6
	return (strncmp(u1->myutmp.out_line, u2->myutmp.out_line, 8));
E 6
}
E 1
