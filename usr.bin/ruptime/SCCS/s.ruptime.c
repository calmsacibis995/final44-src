h56794
s 00119/00105/00136
d D 8.2 94/04/05 13:51:45 bostic 29 28
c hosts which are down were sorted incorrectly
c From: "Chris G. Demetriou" <cgd@postgres.Berkeley.EDU>
c prettiness police
e
s 00005/00005/00236
d D 8.1 93/06/06 16:11:43 bostic 28 27
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00089/00068/00152
d D 5.8 90/07/21 09:23:56 bostic 27 26
c allocate space for hosts, rather than fixed table size
c lots of lint, general cleanliness, redo the man page
c bug report 4.3BSD-reno/usr.bin/2
e
s 00001/00011/00219
d D 5.7 90/06/01 17:40:37 bostic 26 25
c new copyright notice
e
s 00002/00003/00228
d D 5.6 89/05/11 09:48:37 bostic 25 24
c file reorg, pathnames.h, paths.h
e
s 00086/00091/00145
d D 5.5 88/08/25 12:19:57 bostic 24 22
c add Berkeley header, general cleanup, lint
e
s 00084/00095/00141
d R 5.5 88/08/25 12:16:36 bostic 23 22
c add Berkeley specific header; general cleanup, lint
e
s 00001/00001/00235
d D 5.4 87/10/22 18:12:28 bostic 22 21
c ANSI C; sprintf now returns an int.
e
s 00001/00001/00235
d D 5.3 86/01/07 15:18:42 mckusick 21 20
c make ruptime less technophobic (from whm%arizona.csnet@CSNET-RELAY.ARPA)
e
s 00001/00001/00235
d D 5.2 85/06/18 19:28:22 mckusick 20 19
c rwhod.h moves to /usr/include/protocols
e
s 00014/00002/00222
d D 5.1 85/05/31 09:28:29 dist 19 18
c Add copyright
e
s 00002/00002/00222
d D 4.17 85/02/27 08:23:28 karels 18 17
c read in the whole file (struct whod), not just 1K
e
s 00038/00031/00186
d D 4.16 83/11/17 14:20:16 ralph 17 16
c added -r option to reverse sort order
e
s 00006/00006/00211
d D 4.15 83/11/14 15:44:26 ralph 16 15
c print correct error message and down if time > 11 min.
e
s 00002/00002/00215
d D 4.14 83/07/01 04:17:29 sam 15 14
c can't stand have rwhod.h in /usr/include
e
s 00004/00004/00213
d D 4.13 83/07/01 02:47:27 sam 14 13
c from sun
e
s 00002/00002/00215
d D 4.12 83/05/25 16:49:39 sam 13 11
c up host name length
e
s 00002/00002/00215
d R 4.12 83/05/25 16:40:33 sam 12 11
c up host name length printed
e
s 00001/00002/00216
d D 4.11 83/05/25 15:52:07 sam 11 10
c kludges to avoid new utmp format
e
s 00001/00000/00217
d D 4.10 83/05/05 11:44:54 sam 10 9
c directory not part of protocol, so moved out of rwhod.h
e
s 00001/00001/00216
d D 4.9 83/05/03 19:57:10 sam 9 8
c move from netser forces rwhod.h into /usr/include
e
s 00001/00001/00216
d D 4.8 83/04/21 12:38:45 ralph 8 7
c changed it so 'up' and 'down' line up in columns.
e
s 00002/00002/00215
d D 4.7 82/12/24 21:04:27 sam 7 6
c port not byte swapped; no more asm.sed; 
c move spool area to /usr/spool/rwho so /etc is always changing
e
s 00003/00003/00214
d D 4.6 82/11/14 15:17:28 sam 6 5
c convert to 4.1c sys calls and directory layout
e
s 00074/00003/00143
d D 4.5 82/10/07 15:30:17 ecc 5 4
c added additional sorting options
e
s 00002/00002/00144
d D 4.4 82/05/09 23:59:02 mckusick 4 3
c update to new fs
e
s 00011/00004/00135
d D 4.3 82/04/03 19:45:44 wnj 3 2
c variable width for load averages
e
s 00001/00001/00138
d D 4.2 82/04/03 19:33:05 wnj 2 1
c %5.2f
e
s 00139/00000/00000
d D 4.1 82/04/02 10:29:08 wnj 1 0
c date and time created 82/04/02 10:29:08 by wnj
e
u
U
t
T
I 19
/*
D 24
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 24
I 24
D 28
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 28
I 28
D 29
 * Copyright (c) 1983, 1993
E 29
I 29
 * Copyright (c) 1983, 1993, 1994
E 29
 *	The Regents of the University of California.  All rights reserved.
E 28
 *
D 26
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
E 26
I 26
 * %sccs.include.redist.c%
E 26
E 24
 */

E 19
I 1
#ifndef lint
D 11
static char sccsid[] = "%W% %E%";
E 11
I 11
D 19
static char sccsid[] = "%W% (Berkeley) %E%";
E 11
#endif
E 19
I 19
D 28
char copyright[] =
D 24
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 24
I 24
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 24
 All rights reserved.\n";
E 28
I 28
static char copyright[] =
D 29
"%Z% Copyright (c) 1983, 1993\n\
E 29
I 29
"%Z% Copyright (c) 1983, 1993, 1994\n\
E 29
	The Regents of the University of California.  All rights reserved.\n";
E 28
D 24
#endif not lint
E 24
I 24
#endif /* not lint */
E 24

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 24
#endif not lint
E 24
I 24
#endif /* not lint */
E 24
E 19

D 4
#include <sys/types.h>		/* botch in ndir.h */
E 4
I 4
#include <sys/param.h>
E 4
D 24
#include <stdio.h>
E 24
D 4
#include <ndir.h>
E 4
I 4
D 15
#include <dir.h>
E 4
D 11
#include <utmp.h>
E 11
D 9
#include "rwhod.h"
E 9
I 9
#include <rwhod.h>
E 15
I 15
D 29
#include <sys/dir.h>
I 24
#include <sys/file.h>
I 27
#include <sys/errno.h>
E 29
I 29

E 29
E 27
E 24
D 20
#include "../etc/rwhod/rwhod.h"
E 20
I 20
#include <protocols/rwhod.h>
I 29

#include <dirent.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
E 29
I 24
#include <stdio.h>
I 27
#include <stdlib.h>
#include <string.h>
I 29
#include <time.h>
#include <tzfile.h>
#include <unistd.h>
E 29
E 27
E 24
E 20
E 15
E 9

D 16
DIR	*etc;
E 16
I 16
D 24
DIR	*dirp;
E 16

E 24
D 27
#define	NHOSTS	100
int	nhosts;
E 27
I 27
D 29
size_t	nhosts, hspace = 20;
E 29
E 27
D 24
struct	hs {
E 24
I 24
struct hs {
E 24
	struct	whod *hs_wd;
	int	hs_nusers;
D 27
} hs[NHOSTS];
E 27
I 27
} *hs;
E 27
struct	whod awhod;
D 5
int	hscmp();
E 5
I 5
D 24
int	hscmp(), ucmp(), lcmp(), tcmp();
E 24
E 5

I 27
#define	ISDOWN(h)		(now - (h)->hs_wd->wd_recvtime > 11 * 60)
E 27
#define	WHDRSIZE	(sizeof (awhod) - sizeof (awhod.wd_we))
I 10
D 25
#define	RWHODIR		"/usr/spool/rwho"
E 25
I 24
D 27
#define	down(h)		(now - (h)->hs_wd->wd_recvtime > 11 * 60)
E 27
E 24
E 10

I 29
size_t nhosts;
E 29
D 24
char	*interval();
int	now;
D 22
char	*malloc(), *sprintf();
E 22
I 22
char	*malloc();
E 22
int	aflg;
I 17
int 	rflg = 1;
E 24
I 24
D 27
time_t	now;
int	rflg = 1;
int	hscmp(), ucmp(), lcmp(), tcmp();
E 27
I 27
time_t now;
int rflg = 1;
D 29
int hscmp(), ucmp(), lcmp(), tcmp();
E 29
E 27
E 24
E 17

I 29
int	 hscmp __P((const void *, const void *));
char	*interval __P((time_t, char *));
int	 lcmp __P((const void *, const void *));
void	 morehosts __P((void));
int	 tcmp __P((const void *, const void *));
int	 ucmp __P((const void *, const void *));
void	 usage __P((void));

int
E 29
I 5
D 16
#define down(h)		(now - (h)->hs_wd->wd_recvtime > 5 * 60)
E 16
I 16
D 24
#define down(h)		(now - (h)->hs_wd->wd_recvtime > 11 * 60)
E 16

E 24
E 5
main(argc, argv)
	int argc;
	char **argv;
{
D 24
	struct direct *dp;
	int f, i, t;
D 18
	char buf[BUFSIZ]; int cc;
E 18
I 18
	char buf[sizeof(struct whod)]; int cc;
E 18
I 17
	char *name;
E 24
I 24
D 29
	extern char *optarg;
E 29
	extern int optind;
E 24
E 17
D 27
	register struct hs *hsp = hs;
E 27
I 27
D 29
	register struct hs *hsp;
E 27
	register struct whod *wd;
	register struct whoent *we;
I 3
D 24
	int maxloadav = 0;
E 24
I 24
	register DIR *dirp;
	struct direct *dp;
	int aflg, cc, ch, f, i, maxloadav;
E 29
I 29
	struct dirent *dp;
	struct hs *hsp;
	struct whod *wd;
	struct whoent *we;
	DIR *dirp;
	size_t hspace;
	int aflg, cc, ch, fd, i, maxloadav;
E 29
	char buf[sizeof(struct whod)];
E 24
I 5
D 29
	int (*cmp)() = hscmp;
I 24
	time_t time();
D 27
	char *interval(), *malloc();
E 27
I 27
	char *interval();
E 29
I 29
	int (*cmp) __P((const void *, const void *));
E 29
E 27
E 24
E 5
E 3

I 17
D 24
	name = *argv;
	while (*++argv) 
		while (**argv)
			switch (*(*argv)++) {
			case 'a':
				aflg++;
				break;
			case 'l':
				cmp = lcmp;
				break;
			case 'u':
				cmp = ucmp;
				break;
			case 't':
				cmp = tcmp;
				break;
			case 'r':
				rflg = -rflg;
				break;
			case '-':
				break;
			default: 
				fprintf(stderr, "Usage: %s [ -ar [ lut ] ]\n",
					name);
				exit (1);
			}
E 17
	time(&t);
D 17
	argc--, argv++;
again:
D 14
	if (!strcmp(*argv, "-a")) {
E 14
I 14
	if (argc && !strcmp(*argv, "-a")) {
E 14
		aflg++;
		argc--, argv++;
		goto again;
	}
I 5
D 14
	if (!strcmp(*argv, "-l")) {
E 14
I 14
	if (argc && !strcmp(*argv, "-l")) {
E 14
		cmp = lcmp;
		argc--, argv++;
		goto again;
	}
D 14
	if (!strcmp(*argv, "-u")) {
E 14
I 14
	if (argc && !strcmp(*argv, "-u")) {
E 14
		cmp = ucmp;
		argc--, argv++;
		goto again;
	}
D 14
	if (!strcmp(*argv, "-t")) {
E 14
I 14
	if (argc && !strcmp(*argv, "-t")) {
E 14
		cmp = tcmp;
		argc--, argv++;
		goto again;
	}
E 17
E 5
D 7
	if (chdir("/etc") < 0) {
		perror("/etc");
E 7
I 7
	if (chdir(RWHODIR) < 0) {
E 24
I 24
	aflg = 0;
I 29
	cmp = hscmp;
E 29
D 27
	maxloadav = -1;
E 27
	while ((ch = getopt(argc, argv, "alrut")) != EOF)
D 29
		switch((char)ch) {
E 29
I 29
		switch (ch) {
E 29
		case 'a':
			aflg = 1;
			break;
		case 'l':
			cmp = lcmp;
			break;
		case 'r':
			rflg = -1;
			break;
		case 't':
			cmp = tcmp;
			break;
		case 'u':
			cmp = ucmp;
			break;
		default: 
D 27
			fprintf(stderr, "usage: ruptime [-alrut]\n");
E 27
I 27
D 29
			(void)fprintf(stderr, "usage: ruptime [-alrut]\n");
E 27
			exit(1);
E 29
I 29
			usage();
E 29
		}
I 29
	argc -= optind;
	argv += optind;
E 29

D 25
	if (chdir(RWHODIR) || (dirp = opendir(".")) == NULL) {
E 24
		perror(RWHODIR);
E 25
I 25
D 29
	if (chdir(_PATH_RWHODIR) || (dirp = opendir(".")) == NULL) {
D 27
		perror(_PATH_RWHODIR);
E 27
I 27
		(void)fprintf(stderr, "ruptime: %s: %s.\n",
		    _PATH_RWHODIR, strerror(errno));
E 27
E 25
E 7
		exit(1);
	}
I 27
	morehosts();
	hsp = hs;
E 29
I 29
	if (argc != 0)
		usage();

	if (chdir(_PATH_RWHODIR) || (dirp = opendir(".")) == NULL)
		err(1, "%s", _PATH_RWHODIR);

E 29
	maxloadav = -1;
E 27
D 16
	etc = opendir(".");
	if (etc == NULL) {
		perror("/etc");
E 16
I 16
D 24
	dirp = opendir(".");
	if (dirp == NULL) {
		perror(RWHODIR);
E 16
		exit(1);
	}
E 24
D 16
	while (dp = readdir(etc)) {
E 16
I 16
D 29
	while (dp = readdir(dirp)) {
E 29
I 29
	for (nhosts = hspace = 0; (dp = readdir(dirp)) != NULL;) {
E 29
E 16
D 24
		if (dp->d_ino == 0)
E 24
I 24
		if (dp->d_ino == 0 || strncmp(dp->d_name, "whod.", 5))
E 24
			continue;
D 24
		if (strncmp(dp->d_name, "whod.", 5))
			continue;
E 24
D 27
		if (nhosts == NHOSTS) {
D 24
			fprintf(stderr, "too many hosts\n");
E 24
I 24
			fprintf(stderr, "ruptime: too many hosts\n");
E 24
			exit(1);
E 27
I 27
D 29
		if ((f = open(dp->d_name, O_RDONLY, 0)) < 0) {
			(void)fprintf(stderr, "ruptime: %s: %s\n",
			    dp->d_name, strerror(errno));
E 29
I 29
		if ((fd = open(dp->d_name, O_RDONLY, 0)) < 0) {
			warn("%s", dp->d_name);
E 29
			continue;
E 27
		}
D 24
		f = open(dp->d_name, 0);
E 24
I 24
D 27
		f = open(dp->d_name, O_RDONLY, 0);
E 24
		if (f > 0) {
D 18
			cc = read(f, buf, BUFSIZ);
E 18
I 18
			cc = read(f, buf, sizeof(struct whod));
E 18
			if (cc >= WHDRSIZE) {
I 24
				/* NOSTRICT */
E 24
				hsp->hs_wd = (struct whod *)malloc(WHDRSIZE);
				wd = (struct whod *)buf;
D 24
				bcopy(buf, hsp->hs_wd, WHDRSIZE);
E 24
I 24
				bcopy(wd, hsp->hs_wd, WHDRSIZE);
E 24
				hsp->hs_nusers = 0;
I 3
				for (i = 0; i < 2; i++)
					if (wd->wd_loadav[i] > maxloadav)
						maxloadav = wd->wd_loadav[i];
E 3
				we = (struct whoent *)(buf+cc);
				while (--we >= wd->wd_we)
					if (aflg || we->we_idle < 3600)
						hsp->hs_nusers++;
				nhosts++; hsp++;
			}
I 24
			(void)close(f);
E 27
I 27
D 29
		cc = read(f, buf, sizeof(struct whod));
		(void)close(f);
E 29
I 29
		cc = read(fd, buf, sizeof(struct whod));
		(void)close(fd);

E 29
		if (cc < WHDRSIZE)
			continue;
		if (nhosts == hspace) {
D 29
			morehosts();
E 29
I 29
			if ((hs =
			    realloc(hs, (hspace += 40) * sizeof(*hs))) == NULL)
				err(1, NULL);
E 29
			hsp = hs + nhosts;
E 27
E 24
		}
I 27
D 29
		/* NOSTRICT */
		hsp->hs_wd = malloc((size_t)WHDRSIZE);
		wd = (struct whod *)buf;
		bcopy((char *)wd, (char *)hsp->hs_wd, (size_t)WHDRSIZE);
		hsp->hs_nusers = 0;
		for (i = 0; i < 2; i++)
E 29
I 29

		if ((hsp->hs_wd = malloc((size_t)WHDRSIZE)) == NULL)
			err(1, NULL);
		memmove(hsp->hs_wd, buf, (size_t)WHDRSIZE);

		for (wd = (struct whod *)buf, i = 0; i < 2; ++i)
E 29
			if (wd->wd_loadav[i] > maxloadav)
				maxloadav = wd->wd_loadav[i];
D 29
		we = (struct whoent *)(buf+cc);
		while (--we >= wd->wd_we)
E 29
I 29

		for (hsp->hs_nusers = 0,
		    we = (struct whoent *)(buf + cc); --we >= wd->wd_we;)
E 29
			if (aflg || we->we_idle < 3600)
D 29
				hsp->hs_nusers++;
		nhosts++;
		hsp++;
E 29
I 29
				++hsp->hs_nusers;
		++hsp;
		++nhosts;
E 29
E 27
D 24
		(void) close(f);
E 24
	}
D 5
	qsort((char *)hs, nhosts, sizeof (hs[0]), hscmp);
E 5
D 24
	(void) time(&now);
I 5
	qsort((char *)hs, nhosts, sizeof (hs[0]), cmp);
E 5
	if (nhosts == 0) {
		printf("no hosts!?!\n");
E 24
I 24
D 29
	if (!nhosts) {
D 27
		printf("ruptime: no hosts!?!\n");
E 27
I 27
		(void)printf("ruptime: no hosts in %s.\n", _PATH_RWHODIR);
E 27
E 24
		exit(1);
	}
I 24
	qsort((char *)hs, nhosts, sizeof (hs[0]), cmp);
E 29
I 29
	if (nhosts == 0)
		errx(0, "no hosts in %s.", _PATH_RWHODIR);

E 29
	(void)time(&now);
I 29
	qsort(hs, nhosts, sizeof(hs[0]), cmp);
E 29
E 24
	for (i = 0; i < nhosts; i++) {
		hsp = &hs[i];
D 5
		if (now - hsp->hs_wd->wd_recvtime > 5 * 60) {
E 5
I 5
D 27
		if (down(hsp)) {
E 5
D 13
			printf("%-8.8s%s\n", hsp->hs_wd->wd_hostname,
E 13
I 13
			printf("%-12.12s%s\n", hsp->hs_wd->wd_hostname,
E 27
I 27
		if (ISDOWN(hsp)) {
			(void)printf("%-12.12s%s\n", hsp->hs_wd->wd_hostname,
E 27
E 13
			    interval(now - hsp->hs_wd->wd_recvtime, "down"));
			continue;
		}
D 2
		printf("%-8.8s%s,  %4d user%s  load %4.2f, %4.2f, %4.2f\n",
E 2
I 2
D 3
		printf("%-8.8s%s,  %4d user%s  load %5.2f, %5.2f, %5.2f\n",
E 3
I 3
D 13
		printf("%-8.8s%s,  %4d user%s  load %*.2f, %*.2f, %*.2f\n",
E 13
I 13
D 27
		printf("%-12.12s%s,  %4d user%s  load %*.2f, %*.2f, %*.2f\n",
E 27
I 27
		(void)printf(
		    "%-12.12s%s,  %4d user%s  load %*.2f, %*.2f, %*.2f\n",
E 27
E 13
E 3
E 2
		    hsp->hs_wd->wd_hostname,
D 27
		    interval(hsp->hs_wd->wd_sendtime -
D 6
			hsp->hs_wd->wd_bootime, "  up"),
E 6
I 6
			hsp->hs_wd->wd_boottime, "  up"),
E 27
I 27
		    interval((time_t)hsp->hs_wd->wd_sendtime -
			(time_t)hsp->hs_wd->wd_boottime, "  up"),
E 27
E 6
		    hsp->hs_nusers,
		    hsp->hs_nusers == 1 ? ", " : "s,",
D 3
		    hsp->hs_wd->wd_loadav[0] / 100.0,
		    hsp->hs_wd->wd_loadav[1] / 100.0,
		    hsp->hs_wd->wd_loadav[2] / 100.0);
E 3
I 3
		    maxloadav >= 1000 ? 5 : 4,
			hsp->hs_wd->wd_loadav[0] / 100.0,
		    maxloadav >= 1000 ? 5 : 4,
		        hsp->hs_wd->wd_loadav[1] / 100.0,
		    maxloadav >= 1000 ? 5 : 4,
		        hsp->hs_wd->wd_loadav[2] / 100.0);
E 3
D 27
		cfree(hsp->hs_wd);
E 27
I 27
D 29
		free((void *)hsp->hs_wd);
E 29
E 27
	}
	exit(0);
}

char *
D 24
interval(time, updown)
	int time;
E 24
I 24
interval(tval, updown)
	time_t tval;
E 24
	char *updown;
{
	static char resbuf[32];
	int days, hours, minutes;

D 21
	if (time < 0 || time > 3*30*24*60*60) {
E 21
I 21
D 24
	if (time < 0 || time > 365*24*60*60) {
E 21
		(void) sprintf(resbuf, "   %s ??:??", updown);
		return (resbuf);
E 24
I 24
D 29
	if (tval < 0 || tval > 365*24*60*60) {
		(void)sprintf(resbuf, "   %s ??:??", updown);
		return(resbuf);
E 29
I 29
	if (tval < 0 || tval > DAYSPERNYEAR * SECSPERDAY) {
		(void)snprintf(resbuf, sizeof(resbuf), "   %s ??:??", updown);
		return (resbuf);
E 29
E 24
	}
D 24
	minutes = (time + 59) / 60;		/* round to minutes */
E 24
I 24
D 29
	minutes = (tval + 59) / 60;		/* round to minutes */
E 24
	hours = minutes / 60; minutes %= 60;
	days = hours / 24; hours %= 24;
E 29
I 29
						/* round to minutes. */
	minutes = (tval + (SECSPERMIN - 1)) / SECSPERMIN;
	hours = minutes / MINSPERHOUR;
	minutes %= MINSPERHOUR;
	days = hours / HOURSPERDAY;
	hours %= HOURSPERDAY;
E 29
	if (days)
D 24
		(void) sprintf(resbuf, "%s %2d+%02d:%02d",
E 24
I 24
D 29
		(void)sprintf(resbuf, "%s %2d+%02d:%02d",
E 24
		    updown, days, hours, minutes);
E 29
I 29
		(void)snprintf(resbuf, sizeof(resbuf),
		    "%s %2d+%02d:%02d", updown, days, hours, minutes);
E 29
	else
D 8
		(void) sprintf(resbuf, "   %s %2d:%02d",
E 8
I 8
D 24
		(void) sprintf(resbuf, "%s    %2d:%02d",
E 24
I 24
D 29
		(void)sprintf(resbuf, "%s    %2d:%02d",
E 24
E 8
		    updown, hours, minutes);
D 24
	return (resbuf);
E 24
I 24
	return(resbuf);
E 29
I 29
		(void)snprintf(resbuf, sizeof(resbuf),
		    "%s    %2d:%02d", updown, hours, minutes);
	return (resbuf);
E 29
E 24
}

D 27
hscmp(h1, h2)
	struct hs *h1, *h2;
E 27
I 27
D 29
/* alphabetical comparison */
E 29
I 29
#define	HS(a)	((struct hs *)(a))

/* Alphabetical comparison. */
int
E 29
hscmp(a1, a2)
D 29
	void *a1, *a2;
E 29
I 29
	const void *a1, *a2;
E 29
E 27
{
I 27
D 29
	struct hs *h1 = a1, *h2 = a2;

E 27
D 24

D 17
	return (strcmp(h1->hs_wd->wd_hostname, h2->hs_wd->wd_hostname));
E 17
I 17
	return (rflg * strcmp(h1->hs_wd->wd_hostname, h2->hs_wd->wd_hostname));
E 24
I 24
	return(rflg * strcmp(h1->hs_wd->wd_hostname, h2->hs_wd->wd_hostname));
E 29
I 29
	return (rflg *
	    strcmp(HS(a1)->hs_wd->wd_hostname, HS(a2)->hs_wd->wd_hostname));
E 29
E 24
E 17
I 5
}

D 27
/*
 * Compare according to load average.
 */
lcmp(h1, h2)
	struct hs *h1, *h2;
E 27
I 27
D 29
/* load average comparison */
E 29
I 29
/* Load average comparison. */
int
E 29
lcmp(a1, a2)
D 29
	void *a1, *a2;
E 29
I 29
	const void *a1, *a2;
E 29
E 27
{
D 24

E 24
D 27
	if (down(h1))
		if (down(h2))
D 24
			return (tcmp(h1, h2));
E 24
I 24
			return(tcmp(h1, h2));
E 27
I 27
D 29
	register struct hs *h1 = a1, *h2 = a2;

	if (ISDOWN(h1))
		if (ISDOWN(h2))
			return(tcmp(a1, a2));
E 29
I 29
	if (ISDOWN(HS(a1)))
		if (ISDOWN(HS(a2)))
			return (tcmp(a1, a2));
E 29
E 27
E 24
		else
D 17
			return (1);
E 17
I 17
D 24
			return (rflg);
E 24
I 24
D 29
			return(rflg);
E 24
E 17
D 27
	else if (down(h2))
E 27
I 27
	else if (ISDOWN(h2))
E 27
D 17
		return (-1);
E 17
I 17
D 24
		return (-rflg);
E 24
I 24
		return(-rflg);
E 29
I 29
			return (rflg);
	else if (ISDOWN(HS(a2)))
		return (-rflg);
E 29
E 24
E 17
	else
D 17
		return (h2->hs_wd->wd_loadav[0] - h1->hs_wd->wd_loadav[0]);
E 17
I 17
D 24
		return (rflg * 
E 24
I 24
D 29
		return(rflg *
E 24
			(h2->hs_wd->wd_loadav[0] - h1->hs_wd->wd_loadav[0]));
E 29
I 29
		return (rflg *
		   (HS(a2)->hs_wd->wd_loadav[0] - HS(a1)->hs_wd->wd_loadav[0]));
E 29
E 17
}

D 27
/*
 * Compare according to number of users.
 */
ucmp(h1, h2)
	struct hs *h1, *h2;
E 27
I 27
D 29
/* number of users comparison */
E 29
I 29
/* Number of users comparison. */
int
E 29
ucmp(a1, a2)
D 29
	void *a1, *a2;
E 29
I 29
	const void *a1, *a2;
E 29
E 27
{
D 24

E 24
D 27
	if (down(h1))
		if (down(h2))
D 24
			return (tcmp(h1, h2));
E 24
I 24
			return(tcmp(h1, h2));
E 27
I 27
D 29
	register struct hs *h1 = a1, *h2 = a2;

	if (ISDOWN(h1))
		if (ISDOWN(h2))
			return(tcmp(a1, a2));
E 29
I 29
	if (ISDOWN(HS(a1)))
		if (ISDOWN(HS(a2)))
			return (tcmp(a1, a2));
E 29
E 27
E 24
		else
D 17
			return (1);
E 17
I 17
D 24
			return (rflg);
E 24
I 24
D 29
			return(rflg);
E 24
E 17
D 27
	else if (down(h2))
E 27
I 27
	else if (ISDOWN(h2))
E 27
D 17
		return (-1);
E 17
I 17
D 24
		return (-rflg);
E 24
I 24
		return(-rflg);
E 29
I 29
			return (rflg);
	else if (ISDOWN(HS(a2)))
		return (-rflg);
E 29
E 24
E 17
	else
D 17
		return (h2->hs_nusers - h1->hs_nusers);
E 17
I 17
D 24
		return (rflg * (h2->hs_nusers - h1->hs_nusers));
E 24
I 24
D 29
		return(rflg * (h2->hs_nusers - h1->hs_nusers));
E 29
I 29
		return (rflg * (HS(a2)->hs_nusers - HS(a1)->hs_nusers));
E 29
E 24
E 17
}

D 27
/*
 * Compare according to uptime.
 */
tcmp(h1, h2)
	struct hs *h1, *h2;
E 27
I 27
D 29
/* uptime comparison */
E 29
I 29
/* Uptime comparison. */
int
E 29
tcmp(a1, a2)
D 29
	void *a1, *a2;
E 29
I 29
	const void *a1, *a2;
E 29
E 27
{
I 27
D 29
	register struct hs *h1 = a1, *h2 = a2;

E 27
D 24
	long t1, t2;

D 17
	return (
E 17
I 17
	return (rflg * (
E 24
I 24
	return(rflg * (
E 24
E 17
D 27
		(down(h2) ? h2->hs_wd->wd_recvtime - now
E 27
I 27
		(ISDOWN(h2) ? h2->hs_wd->wd_recvtime - now
E 27
D 6
			  : h2->hs_wd->wd_sendtime - h2->hs_wd->wd_bootime)
E 6
I 6
			  : h2->hs_wd->wd_sendtime - h2->hs_wd->wd_boottime)
E 29
I 29
	return (rflg * (
		(ISDOWN(HS(a2)) ? HS(a2)->hs_wd->wd_recvtime - now
		    : HS(a2)->hs_wd->wd_sendtime - HS(a2)->hs_wd->wd_boottime)
E 29
E 6
		-
D 27
		(down(h1) ? h1->hs_wd->wd_recvtime - now
E 27
I 27
D 29
		(ISDOWN(h1) ? h1->hs_wd->wd_recvtime - now
E 27
D 6
			  : h1->hs_wd->wd_sendtime - h1->hs_wd->wd_bootime)
E 6
I 6
			  : h1->hs_wd->wd_sendtime - h1->hs_wd->wd_boottime)
E 29
I 29
		(ISDOWN(HS(a1)) ? HS(a1)->hs_wd->wd_recvtime - now
		    : HS(a1)->hs_wd->wd_sendtime - HS(a1)->hs_wd->wd_boottime)
E 29
E 6
D 17
	);
E 17
I 17
	));
I 27
}

D 29
morehosts()
E 29
I 29
void
usage()
E 29
{
D 29
	hs = realloc((char *)hs, (hspace *= 2) * sizeof(*hs));
	if (hs == NULL) {
		(void)fprintf(stderr, "ruptime: %s.\n", strerror(ENOMEM));
		exit(1);
	}
E 29
I 29
	(void)fprintf(stderr, "usage: ruptime [-alrut]\n");
	exit(1);
E 29
E 27
E 17
E 5
}
E 1
