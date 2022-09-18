h28160
s 00002/00002/00099
d D 8.3 94/04/02 10:05:18 pendry 26 25
c add 1994 copyright
e
s 00039/00006/00062
d D 8.2 94/04/01 06:49:58 pendry 25 24
c prettyness police
e
s 00005/00005/00063
d D 8.1 93/06/06 14:12:18 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00004/00067
d D 5.16 91/03/03 16:14:45 bostic 23 22
c pw_edit fails permanently now
e
s 00034/00238/00037
d D 5.15 91/02/12 21:35:34 bostic 22 21
c rework the password subsystem
e
s 00001/00011/00274
d D 5.14 90/06/01 16:33:00 bostic 21 20
c new copyright notice
e
s 00001/00001/00284
d D 5.13 90/05/15 19:52:30 bostic 20 19
c string.h is ANSI C include file
e
s 00013/00012/00272
d D 5.12 90/05/10 17:57:43 marc 19 18
c strsep has new calling convention
e
s 00014/00012/00270
d D 5.11 90/01/05 10:48:11 bostic 18 17
c new strsep broke it; was stupidly coded anyway
e
s 00014/00008/00268
d D 5.10 89/09/12 08:14:46 bostic 17 16
c fix for editors that create new files; bug report 4.3BSD-tahoe/sbin/4
e
s 00002/00002/00274
d D 5.9 89/04/22 11:26:08 bostic 16 15
c file modes have to agree
e
s 00021/00021/00255
d D 5.8 89/03/16 22:29:12 bostic 15 14
c rearrange re-edit code; use passwd.{pag,dir}
e
s 00082/00050/00194
d D 5.7 89/03/11 16:32:56 bostic 14 13
c reenter editor if corrupted password file
e
s 00144/00142/00100
d D 5.6 89/02/22 11:14:44 bostic 13 12
c shadow passwords
e
s 00010/00005/00232
d D 5.5 88/06/18 14:34:58 bostic 12 11
c install approved copyright notice
e
s 00011/00005/00226
d D 5.4 88/02/19 11:12:55 bostic 11 10
c added Berkeley specific header
e
s 00097/00043/00134
d D 5.3 87/11/23 21:21:35 bostic 10 9
c fix uid/gid rollover; check all password entries for correctness; 
c bug reports 4.3BSD/etc/100, 4.3BSD/sys/176
e
s 00124/00126/00053
d D 5.2 87/07/01 16:49:22 bostic 9 8
c well, it started 'cause vipw should realize that you haven't 
c modified the file and kind of got out of control.  
e
s 00013/00001/00166
d D 5.1 85/05/28 15:43:49 dist 8 7
c Add copyright
e
s 00001/00001/00166
d D 4.7 85/02/24 12:25:18 bloom 7 6
c strncmp requires 3 arguments
e
s 00000/00001/00167
d D 4.6 84/02/27 16:13:42 ralph 6 5
c don't trap SIGTSTP.
e
s 00010/00007/00158
d D 4.5 83/12/02 17:53:11 ralph 5 4
c unlink .pag and .dir; trap SIGTSTP.
e
s 00027/00001/00138
d D 4.4 83/12/01 16:57:17 ralph 4 3
c changed to build passwd.pag and passwd.dir
e
s 00003/00000/00136
d D 4.3 83/10/04 15:10:00 ralph 3 2
c fixed exit codes
e
s 00001/00000/00135
d D 4.2 83/09/07 09:19:05 ralph 2 1
c added umask(0) so mode of /etc/passwd will be correct
e
s 00135/00000/00000
d D 4.1 83/07/03 01:53:35 sam 1 0
c date and time created 83/07/03 01:53:35 by sam
e
u
U
t
T
I 8
/*
D 9
 * Copyright (c) 1980 Regents of the University of California.
E 9
I 9
D 24
 * Copyright (c) 1987 Regents of the University of California.
E 9
D 11
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
 * All rights reserved.
E 24
I 24
D 26
 * Copyright (c) 1987, 1993
E 26
I 26
 * Copyright (c) 1987, 1993, 1994
E 26
 *	The Regents of the University of California.  All rights reserved.
E 24
 *
D 21
 * Redistribution and use in source and binary forms are permitted
D 12
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 12
I 12
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
E 21
I 21
 * %sccs.include.redist.c%
E 21
E 12
E 11
 */

E 8
I 1
#ifndef lint
I 8
D 24
char copyright[] =
D 9
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 9
I 9
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 9
 All rights reserved.\n";
E 24
I 24
static char copyright[] =
D 26
"%Z% Copyright (c) 1987, 1993\n\
E 26
I 26
"%Z% Copyright (c) 1987, 1993, 1994\n\
E 26
	The Regents of the University of California.  All rights reserved.\n";
E 24
D 10
#endif not lint
E 10
I 10
D 11
#endif /* !lint */
E 11
I 11
#endif /* not lint */
E 11
E 10

#ifndef lint
E 8
static char sccsid[] = "%W% (Berkeley) %G%";
D 8
#endif
E 8
I 8
D 10
#endif not lint
E 10
I 10
D 11
#endif /* !lint */
E 11
I 11
#endif /* not lint */
E 11
E 10
E 8

I 10
D 13
#include <machine/machparam.h>
E 10
#include <sys/types.h>
E 13
I 13
D 22
#include <sys/param.h>
E 22
I 22
#include <sys/types.h>
E 22
E 13
#include <sys/stat.h>
I 25

#include <err.h>
E 25
I 10
D 22
#include <sys/signal.h>
E 10
#include <sys/file.h>
D 9

E 9
D 13
#include <stdio.h>
E 13
I 13
#include <sys/time.h>
#include <sys/resource.h>
E 13
#include <errno.h>
E 22
I 13
#include <pwd.h>
#include <stdio.h>
I 22
#include <stdlib.h>
E 22
I 14
D 20
#include <strings.h>
E 20
I 20
#include <string.h>
I 25
#include <unistd.h>
E 25
E 20
E 14
E 13
D 10
#include <signal.h>
E 10

I 14
D 22
char *passwd, *temp;
E 22
I 22
D 25
char *progname = "vipw";
E 25
I 25
#include "pw_util.h"

E 25
char *tempname;
E 22

E 14
D 13
/*
 * Password file editor with locking.
 */
D 5
char	*temp = "/etc/ptmp";
I 4
char	*temp_pag = "/etc/ptmp.pag";
char	*temp_dir = "/etc/ptmp.dir";
E 4
char	*passwd = "/etc/passwd";
I 4
char	*passwd_pag = "/etc/passwd.pag";
char	*passwd_dir = "/etc/passwd.dir";
E 5
I 5
D 9
char	temp[] = "/etc/ptmp";
char	temp_pag[] = "/etc/ptmp.pag";
char	temp_dir[] = "/etc/ptmp.dir";
char	passwd[] = "/etc/passwd";
char	passwd_pag[] = "/etc/passwd.pag";
char	passwd_dir[] = "/etc/passwd.dir";
E 5
E 4
char	buf[BUFSIZ];
char	*getenv();
char	*index();
extern	int errno;
E 9
I 9
D 10
static char	*passwd = "/etc/passwd",
		buf[BUFSIZ];
E 10
I 10
static char	*passwd = "/etc/passwd", buf[BUFSIZ];
E 10
E 9

E 13
D 9
main(argc, argv)
	char *argv[];
E 9
I 9
D 25
main()
E 25
I 25
void	copyfile __P((int, int));
void	usage __P((void));

int
main(argc, argv)
	int argc;
	char *argv[];
E 25
E 9
{
D 9
	int fd;
	FILE *ft, *fp;
	char *editor;
E 9
I 9
D 10
	register int	n, fd_passwd, fd_temp;
	static char	*temp = "/etc/ptmp";
	struct stat	s1, s2;
	char	*editor,
		*getenv();
E 10
I 10
D 13
	register int n, fd_passwd, fd_temp;
	static char *temp = "/etc/ptmp";
E 13
I 13
D 22
	extern int errno;
	register int n, fd_passwd, fd;
	struct rlimit rlim;
E 13
D 14
	struct stat s1, s2;
D 11
	char	*editor, *getenv();
E 11
I 11
D 13
	char *editor, *getenv();
E 13
I 13
	char *fend, *passwd, *temp, *tend;
E 14
I 14
D 15
	struct stat s1;
E 15
I 15
	struct stat s1, s2;
	FILE *tfp;
E 15
	char *fend, *tend;
E 14
	char buf[8*1024], from[MAXPATHLEN], to[MAXPATHLEN];
E 22
I 22
D 25
	register int pfd, tfd;
E 25
I 25
	int pfd, tfd;
E 25
	struct stat begin, end;
I 25
	int ch;
E 25
E 22
D 14
	char *strerror(), *strcpy();
E 14
E 13
E 11
E 10
E 9

I 25
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch (ch) {
		case '?':
		default:
			usage();
		}
	
	argc -= optind;
	argv += optind;

	if (argc != 0)
		usage();

E 25
I 5
D 9
	signal(SIGHUP, SIG_IGN);
E 5
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
D 5
	signal(SIGHUP, SIG_IGN);
E 5
I 5
D 6
	signal(SIGTSTP, SIG_IGN);
E 6
E 5
	setbuf(stderr, NULL);
E 9
I 9
D 22
	(void)signal(SIGHUP, SIG_IGN);
	(void)signal(SIGINT, SIG_IGN);
	(void)signal(SIGQUIT, SIG_IGN);
I 13
	(void)signal(SIGTSTP, SIG_IGN);
E 22
I 22
	pw_init();
	pfd = pw_lock();
	tfd = pw_tmp();
	copyfile(pfd, tfd);
	(void)close(tfd);
E 22
E 13

D 13
	setbuf(stderr, (char *)NULL);
E 13
I 13
D 22
	rlim.rlim_cur = rlim.rlim_max = RLIM_INFINITY;
	(void)setrlimit(RLIMIT_CPU, &rlim);
	(void)setrlimit(RLIMIT_FSIZE, &rlim);

E 13
E 9
I 2
D 10
	umask(0);
E 10
I 10
	(void)umask(0);
E 10
E 2
D 9
	fd = open(temp, O_WRONLY|O_CREAT|O_EXCL, 0644);
	if (fd < 0) {
E 9
I 9

D 13
	if ((fd_passwd = open(passwd, O_RDONLY, 0)) < 0) {
D 10
		fprintf(stderr, "vipw: ");
E 10
I 10
		fputs("vipw: ", stderr);
E 10
		perror(passwd);
E 13
I 13
	temp = _PATH_PTMP;
D 16
	if ((fd = open(temp, O_WRONLY|O_CREAT|O_EXCL, 0600)) < 0) {
E 16
I 16
	if ((fd = open(temp, O_RDWR|O_CREAT|O_EXCL, 0600)) < 0) {
E 16
		if (errno == EEXIST)
D 14
			fprintf(stderr, "vipw: password file busy.\n");
E 14
I 14
			(void)fprintf(stderr, "vipw: password file busy.\n");
E 14
		else
D 14
			fprintf(stderr,
E 14
I 14
			(void)fprintf(stderr,
E 14
			    "vipw: %s: %s\n", temp, strerror(errno));
E 13
		exit(1);
	}
D 13
	if ((fd_temp = open(temp, O_WRONLY|O_CREAT|O_EXCL, 0644)) < 0) {
		extern int errno;

E 9
		if (errno == EEXIST) {
D 9
			fprintf(stderr, "vipw: password file busy\n");
E 9
I 9
D 10
			fputs("vipw: password file busy\n", stderr);
E 10
I 10
			fputs("vipw: password file busy.\n", stderr);
E 10
E 9
			exit(1);
		}
D 9
		fprintf(stderr, "vipw: "); perror(temp);
E 9
I 9
D 10
		fprintf(stderr, "vipw: ");
E 10
I 10
		fputs("vipw: ", stderr);
E 10
		perror(temp);
E 13
I 13
	passwd = _PATH_MASTERPASSWD;
	if ((fd_passwd = open(passwd, O_RDONLY, 0)) < 0) {
D 14
		fprintf(stderr, "vipw: %s: %s\n", passwd, strerror(errno));
E 14
I 14
		(void)fprintf(stderr, "vipw: %s: %s\n", passwd,
		    strerror(errno));
E 14
E 13
E 9
		exit(1);
	}
D 9
	ft = fdopen(fd, "w");
	if (ft == NULL) {
		fprintf(stderr, "vipw: "); perror(temp);
E 9
I 9
	while ((n = read(fd_passwd, buf, sizeof(buf))) > 0)
D 13
		if (write(fd_temp, buf, n) != n) {
			perror("vipw: write");
			goto bad;
		}
	if (n == -1) {
		perror("vipw: read");
E 13
I 13
		if (write(fd, buf, n) != n)
			goto syserr;

D 15
	if (n == -1 || close(fd_passwd) || fsync(fd) ||
	    fstat(fd, &s1) || close(fd)) {
D 14
syserr:		fprintf(stderr, "vipw: %s", strerror(errno));
E 13
E 9
		goto bad;
E 14
I 14
syserr:		(void)fprintf(stderr, "vipw: %s; ", strerror(errno));
E 15
I 15
	if (n == -1 || close(fd_passwd)) {
syserr:		(void)fprintf(stderr, "vipw: %s: %s; ",
		    passwd, strerror(errno));
E 15
		stop(1);
E 14
	}
I 15
D 16
	if (fsync(fd) || !(tfp = fdopen(fd, "r"))) {
E 16
I 16
D 17
	if (!(tfp = fdopen(fd, "r"))) {
E 16
		(void)fprintf(stderr, "vipw: %s: %s; ",
		    temp, strerror(errno));
		stop(1);
	}
E 17
E 15
D 9
	fp = fopen(passwd, "r");
	if (fp == NULL) {
		fprintf(stderr, "vipw: "); perror(passwd);
E 9
I 9
D 13
	(void)close(fd_passwd);
	if (fsync(fd_temp)) {
		perror("vipw: fsync");
E 9
		goto bad;
	}
D 9
	while (fgets(buf, sizeof (buf) - 1, fp) != NULL)
		fputs(buf, ft);
	fclose(ft); fclose(fp);
	editor = getenv("EDITOR");
	if (editor == 0)
E 9
I 9
	if (fstat(fd_temp, &s1)) {
		perror("vipw: fstat");
		goto bad;
	}
	(void)close(fd_temp);
E 13

I 17
	(void)fstat(fd, &s1);
	(void)close(fd);
E 22
E 17
D 13
	if (!(editor = getenv("EDITOR")))
E 9
		editor = "vi";
D 9
	sprintf(buf, "%s %s", editor, temp);
	if (system(buf) == 0) {
		struct stat sbuf;
		int ok;
E 9
I 9
	(void)sprintf(buf, "%s %s", editor, temp);
	if (system(buf)) {
		perror("vipw: system");
E 13
I 13
D 14
	if (edit(temp)) {
		fprintf(stderr, "vipw: edit failed");
E 13
		goto bad;
E 14
I 14
	for (;;) {
I 15
D 17
		(void)fstat(fd, &s1);
E 17
E 15
D 22
		if (edit()) {
			(void)fprintf(stderr, "vipw: edit failed; ");
			stop(1);
E 22
I 22
		if (stat(tempname, &begin))
			pw_error(tempname, 1, 1);
D 23
		if (pw_edit(0)) {
			(void)fprintf(stderr, "vipw: edit failed\n");
			pw_error((char *)NULL, 0, 1);
E 22
		}
E 23
I 23
		pw_edit(0);
E 23
D 15
		if (!check(&s1))
E 15
I 15
D 17
		(void)fstat(fd, &s2);
E 17
I 17
D 22
		/*
		 * close and re-open the file each time we edit it; some
		 * editors create a new physical file on each edit session.
		 */
		if (!(tfp = fopen(temp, "r"))) {
			(void)fprintf(stderr, "vipw: %s: %s; ",
			    temp, strerror(errno));
			stop(1);
E 22
I 22
		if (stat(tempname, &end))
			pw_error(tempname, 1, 1);
		if (begin.st_mtime == end.st_mtime) {
D 25
			(void)fprintf(stderr, "vipw: no changes made\n");
E 25
I 25
			warnx("no changes made");
E 25
			pw_error((char *)NULL, 0, 0);
E 22
		}
D 22
		(void)fstat(fileno(tfp), &s2);
E 17
		if (s1.st_mtime == s2.st_mtime) {
			(void)fprintf(stderr, "vipw: no changes made; ");
			stop(0);
		}
D 17
		rewind(tfp);
E 17
		if (!check(tfp))
E 22
I 22
		if (pw_mkdb())
E 22
E 15
			break;
D 22
		if (prompt())
			stop(0);
I 17
		(void)fstat(fileno(tfp), &s1);
		(void)fclose(tfp);
E 22
I 22
		pw_prompt();
E 22
E 17
E 14
	}
E 9
D 22

D 9
		/* sanity checks */
		if (stat(temp, &sbuf) < 0) {
			fprintf(stderr,
			    "vipw: can't stat temp file, %s unchanged\n",
			    passwd);
			goto bad;
E 9
I 9
D 13
	if (!freopen(temp, "r", stdin)) {
D 10
		fprintf(stderr, "vipw: can't reopen temp file, %s unchanged\n", passwd);
E 10
I 10
		fprintf(stderr, "vipw: can't reopen temp file; %s unchanged.\n", passwd);
E 13
I 13
D 14
	if (!freopen(temp, "r", stdin) || fstat(fileno(stdin), &s2) ||
	    !s2.st_size) {
		fprintf(stderr, "vipw: can't read temp file");
E 13
E 10
		goto bad;
	}
D 13
	if (fstat(fileno(stdin), &s2)) {
D 10
		fprintf(stderr, "vipw: can't stat temp file, %s unchanged\n", passwd);
E 10
I 10
		fprintf(stderr, "vipw: can't stat temp file; %s unchanged.\n", passwd);
E 10
		goto bad;
	}
E 13
I 13

E 13
	if (s1.st_mtime == s2.st_mtime) {
D 10
		fprintf(stderr, "vipw: %s unchanged\n", passwd);
E 10
I 10
		fprintf(stderr, "vipw: %s unchanged.\n", passwd);
E 10
D 13
		goto bad;
E 13
I 13
		(void)unlink(temp);
		exit(0);
E 13
	}
D 13
	if (!s2.st_size) {
D 10
		fprintf(stderr, "vipw: bad temp file, %s unchanged\n", passwd);
E 10
I 10
		fprintf(stderr, "vipw: bad temp file; %s unchanged.\n", passwd);
E 13
I 13

	if (!check())
E 13
E 10
		goto bad;
I 13

E 14
	switch(fork()) {
	case 0:
		break;
	case -1:
D 14
		fprintf(stderr, "vipw: can't fork");
		goto bad;
E 14
I 14
		(void)fprintf(stderr, "vipw: can't fork; ");
		stop(1);
E 14
		/* NOTREACHED */
	default:
		exit(0);
		/* NOTREACHED */
E 13
	}
D 10
	if (checkroot()) {
E 10
I 10
D 13
	if (check()) {
E 10
		static char	*temp_pag = "/etc/ptmp.pag",
				*temp_dir = "/etc/ptmp.dir",
				*passwd_pag = "/etc/passwd.pag",
				*passwd_dir = "/etc/passwd.dir";
E 13

D 13
		if (makedb(temp) < 0)
			fputs("vipw: mkpasswd failed.\n", stderr);
		else if (rename(temp_pag, passwd_pag) < 0) {
			fprintf(stderr, "vipw: ");
			perror(temp_pag);
E 9
		}
D 9
		if (sbuf.st_size == 0) {
			fprintf(stderr, "vipw: bad temp file, %s unchanged\n",
			    passwd);
			goto bad;
E 9
I 9
		else if (rename(temp_dir, passwd_dir) < 0) {
			fprintf(stderr, "vipw: ");
			perror(temp_dir);
E 9
		}
D 9
		ft = fopen(temp, "r");
		if (ft == NULL) {
			fprintf(stderr,
			    "vipw: can't reopen temp file, %s unchanged\n",
			    passwd);
			goto bad;
E 9
I 9
		else if (rename(temp, passwd) < 0) {
			fprintf(stderr, "vipw: ");
			perror("rename");
E 9
		}
D 9
		ok = 0;
		while (fgets(buf, sizeof (buf) - 1, ft) != NULL) {
			register char *cp;

			cp = index(buf, '\n');
			if (cp == 0)
				continue;
			*cp = '\0';
			cp = index(buf, ':');
			if (cp == 0)
				continue;
			*cp = '\0';
			if (strcmp(buf, "root"))
				continue;
			/* password */
			cp = index(cp + 1, ':');
			if (cp == 0)
				break;
			/* uid */
			if (atoi(cp + 1) != 0)
				break;
			cp = index(cp + 1, ':');
			if (cp == 0)
				break;
			/* gid */
			cp = index(cp + 1, ':');
			if (cp == 0)
				break;
			/* gecos */
			cp = index(cp + 1, ':');
			if (cp == 0)
				break;
			/* login directory */
D 7
			if (strncmp(++cp, "/:"))
E 7
I 7
			if (strncmp(++cp, "/:", 2))
E 7
				break;
			cp += 2;
			if (*cp && strcmp(cp, "/bin/sh") &&
			    strcmp(cp, "/bin/csh"))
				break;
			ok++;
		}
		fclose(ft);
		if (ok) {
D 4
			if (rename(temp, passwd) < 0)
E 4
I 4
			if (makedb(temp) < 0)
				fprintf(stderr, "vipw: mkpasswd failed\n");
			else if (rename(temp_pag, passwd_pag) < 0)
				fprintf(stderr, "vipw: "), perror(temp_pag);
			else if (rename(temp_dir, passwd_dir) < 0)
				fprintf(stderr, "vipw: "), perror(temp_dir);
			else if (rename(temp, passwd) < 0)
E 4
				fprintf(stderr, "vipw: "), perror("rename");
I 3
			else
				exit(0);
E 3
		} else
			fprintf(stderr,
			    "vipw: you mangled the temp file, %s unchanged\n",
			    passwd);
E 9
I 9
		else
			exit(0);
		(void)unlink(temp_pag);
		(void)unlink(temp_dir);
E 13
I 13
	if (makedb(temp)) {
D 14
		fprintf(stderr, "vipw: mkpasswd failed");
bad:		fprintf(stderr, "; %s unchanged.\n", passwd);
		(void)unlink(temp);
		exit(1);
E 14
I 14
		(void)fprintf(stderr, "vipw: mkpasswd failed; ");
		stop(1);
E 14
E 13
E 9
	}
D 9
bad:
I 5
	unlink(temp_pag);
	unlink(temp_dir);
E 5
	unlink(temp);
E 9
I 9
D 13
bad:	(void)unlink(temp);
E 9
I 3
	exit(1);
E 13
I 13

	/*
	 * possible race; have to rename four files, and someone could slip
	 * in between them.  LOCK_EX and rename the ``passwd.dir'' file first
	 * so that getpwent(3) can't slip in; the lock should never fail and
	 * it's unclear what to do if it does.  Rename ``ptmp'' last so that
	 * passwd/vipw/chpass can't slip in.
	 */
	(void)setpriority(PRIO_PROCESS, 0, -20);
	fend = strcpy(from, temp) + strlen(temp);
D 15
	tend = strcpy(to, passwd) + strlen(passwd);
E 15
I 15
	tend = strcpy(to, _PATH_PASSWD) + strlen(_PATH_PASSWD);
E 15
	bcopy(".dir", fend, 5);
	bcopy(".dir", tend, 5);
	if ((fd = open(from, O_RDONLY, 0)) >= 0)
		(void)flock(fd, LOCK_EX);
	/* here we go... */
	(void)rename(from, to);
	bcopy(".pag", fend, 5);
	bcopy(".pag", tend, 5);
	(void)rename(from, to);
	bcopy(".orig", fend, 6);
	(void)rename(from, _PATH_PASSWD);
	(void)rename(temp, passwd);
	/* done! */
E 22
	exit(0);
E 13
I 4
}

I 25
void
E 25
I 10
D 13
#define	CHN	((char *)NULL)
E 10
I 9
static
E 13
D 10
checkroot()
E 10
I 10
D 14
check()
E 14
I 14
D 15
check(s1)
	struct stat *s1;
E 15
I 15
D 22
check(tfp)
	FILE *tfp;
E 22
I 22
copyfile(from, to)
D 25
	register int from, to;
E 25
I 25
	int from, to;
E 25
E 22
E 15
E 14
E 10
{
D 10
	register int	cnt;
	register char	*cp, *sh;
	char	*getusershell();
E 10
I 10
D 13
	register char *cp, *sh;
E 13
D 22
	register long id;
D 13
	register int root;
E 13
I 13
	register int lcnt, root;
	register char *p, *sh;
I 14
D 15
	struct stat s2;
	FILE *tfp;
E 15
E 14
E 13
	long atol();
D 13
	char *token(), *getusershell();
E 13
I 13
D 14
	char buf[1024], *getusershell(), *strsep();
E 14
I 14
D 19
	char buf[1024], *getusershell();
E 19
I 19
	char buf[1024], *bp, *getusershell();
E 19
E 14
E 13
E 10
D 15

D 10
	while (gets(buf)) {
		if (strncmp(buf, "root:", sizeof("root:") - 1))
E 10
I 10
D 13
	for (root = 0; gets(buf); root = 0) {
		if (!*buf) {
			fputs("vipw: empty line.\n", stderr);
E 10
			continue;
D 10
						/* skip password */
		for (cp = buf + sizeof("root:") - 1; *cp && *cp != ':'; ++cp);
		if (!*cp || atoi(++cp))		/* uid exists && uid == 0 */
			break;			/* skip uid, gid, gcos, dir */
		for (cnt = 0; *cp && cnt < 4; ++cp)
			if (*cp == ':')
				++cnt;
		if (!*cp)
			break;
		while (sh = getusershell())
			if (!strcmp(cp, sh))
				return(1);
		fprintf(stderr, "vipw: illegal shell (%s) for root login, %s unchanged.\n", cp, passwd);
		return(0);
E 10
I 10
		}
		if (!(cp = token(buf)) || !*cp)		/* login */
E 13
I 13
D 14
	for (lcnt = 1; fgets(buf, sizeof(buf), stdin); ++lcnt) {
E 14
I 14
	if (!(tfp = fopen(temp, "r")) || fstat(fileno(tfp), &s2) ||
	    !s2.st_size) {
		(void)fprintf(stderr, "vipw: can't read temp file; ");
		stop(1);
	}

	if (s1->st_mtime == s2.st_mtime) {
		(void)fprintf(stderr, "vipw: ");
		stop(0);
	}
E 15

	for (lcnt = 1; fgets(buf, sizeof(buf), tfp); ++lcnt) {
E 14
		/* skip lines that are too big */
D 18
		if (!index(buf, '\n')) {
E 18
I 18
		if (!(p = index(buf, '\n'))) {
E 18
D 14
			fprintf(stderr, "vipw: line too long");
E 14
I 14
			(void)fprintf(stderr, "vipw: line too long");
E 14
E 13
			goto bad;
D 13
		if (!strcmp(cp, "root"))
			root = 1;
		(void)token(CHN);			/* passwd */
		if (!(cp = token(CHN)) || !*cp)		/* uid */
			goto bad;
		id = atol(cp);
E 13
I 13
		}
D 18
		if (!(p = strsep(buf, ":\n")))		/* login */
E 18
I 18
		*p = '\0';
D 19
		if (!(p = strsep(buf, ":")))		/* login */
E 19
I 19
		bp = buf;
		if (!(p = strsep(&bp, ":")))		/* login */
E 19
E 18
			goto general;
		root = !strcmp(p, "root");
D 18
		(void)strsep((char *)NULL, ":\n");	/* passwd */
		if (!(p = strsep((char *)NULL, ":\n")))	/* uid */
E 18
I 18
D 19
		(void)strsep((char *)NULL, ":");	/* passwd */
		if (!(p = strsep((char *)NULL, ":")))	/* uid */
E 19
I 19
		(void)strsep(&bp, ":");	/* passwd */
		if (!(p = strsep(&bp, ":")))	/* uid */
E 19
E 18
			goto general;
		id = atol(p);
E 13
		if (root && id) {
D 13
			fprintf(stderr, "vipw: root uid should be 0; %s unchanged.\n", passwd);
			return(0);
E 13
I 13
D 14
			fprintf(stderr, "vipw: root uid should be 0");
E 14
I 14
			(void)fprintf(stderr, "vipw: root uid should be 0");
E 14
			goto bad;
E 13
		}
		if (id > USHRT_MAX) {
D 13
			fprintf(stderr, "vipw: %s > max uid value (%u); %s unchanged.\n", cp, USHRT_MAX, passwd);
			return(0);
		}
		if (!(cp = token(CHN)) || !*cp)		/* gid */
E 13
I 13
D 14
			fprintf(stderr, "vipw: %s > max uid value (%d)",
E 14
I 14
			(void)fprintf(stderr, "vipw: %s > max uid value (%d)",
E 14
			    p, USHRT_MAX);
E 13
			goto bad;
D 13
		id = atol(cp);
		if (id > USHRT_MAX) {
			fprintf(stderr, "vipw: %s > max gid value (%u); %s unchanged.\n", cp, USHRT_MAX, passwd);
			return(0);
E 13
		}
D 13
		(void)token(CHN);			/* gcos */
		if (!token(CHN))			/* home directory */
E 13
I 13
D 18
		if (!(p = strsep((char *)NULL, ":\n")))	/* gid */
E 18
I 18
D 19
		if (!(p = strsep((char *)NULL, ":")))	/* gid */
E 19
I 19
		if (!(p = strsep(&bp, ":")))	/* gid */
E 19
E 18
			goto general;
		id = atol(p);
		if (id > USHRT_MAX) {
D 14
			fprintf(stderr, "vipw: %s > max gid value (%d)",
E 14
I 14
			(void)fprintf(stderr, "vipw: %s > max gid value (%d)",
E 14
			    p, USHRT_MAX);
E 13
			goto bad;
D 13
		if (!(cp = token(CHN)))			/* shell */
			goto bad;
		if (root && *cp)			/* empty == /bin/sh */
E 13
I 13
		}
D 18
		(void)strsep((char *)NULL, ":\n");	/* class */
		(void)strsep((char *)NULL, ":\n");	/* change */
		(void)strsep((char *)NULL, ":\n");	/* expire */
		(void)strsep((char *)NULL, ":\n");	/* gecos */
		(void)strsep((char *)NULL, ":\n");	/* directory */
		if (!(p = strsep((char *)NULL, ":\n")))	/* shell */
E 18
I 18
D 19
		(void)strsep((char *)NULL, ":");	/* class */
		(void)strsep((char *)NULL, ":");	/* change */
		(void)strsep((char *)NULL, ":");	/* expire */
		(void)strsep((char *)NULL, ":");	/* gecos */
		(void)strsep((char *)NULL, ":");	/* directory */
		if (!(p = strsep((char *)NULL, ":")))	/* shell */
E 19
I 19
		(void)strsep(&bp, ":");	/* class */
		(void)strsep(&bp, ":");	/* change */
		(void)strsep(&bp, ":");	/* expire */
		(void)strsep(&bp, ":");	/* gecos */
		(void)strsep(&bp, ":");	/* directory */
		if (!(p = strsep(&bp, ":")))	/* shell */
E 19
E 18
			goto general;
		if (root && *p)				/* empty == /bin/sh */
E 13
D 14
			for (;;)
E 14
I 14
			for (setusershell();;)
E 14
				if (!(sh = getusershell())) {
D 13
					fprintf(stderr, "vipw: illegal shell (%s) for root; %s unchanged.\n", cp, passwd);
					return(0);
E 13
I 13
D 14
					fprintf(stderr,
					    "vipw: warning, unknown root shell.");
E 14
I 14
					(void)fprintf(stderr,
					    "vipw: warning, unknown root shell.\n");
E 14
					break;
E 13
				}
D 13
				else if (!strcmp(cp, sh))
E 13
I 13
				else if (!strcmp(p, sh))
E 13
					break;
D 13
		if (token(CHN)) {			/* too many fields */
bad:			fprintf(stderr, "vipw: corrupted entry; %s unchanged.\n", passwd);
E 13
I 13
D 18
		if (strsep((char *)NULL, ":\n")) {	/* too many */
E 18
I 18
D 19
		if (p = strsep((char *)NULL, ":")) {	/* too many */
E 19
I 19
		if (p = strsep(&bp, ":")) {	/* too many */
E 19
(void)fprintf(stderr, "got {%s}\n", p);
E 18
D 14
general:		fprintf(stderr, "vipw: corrupted entry");
bad:			fprintf(stderr, "; line #%d", lcnt);
E 13
			return(0);
E 14
I 14
general:		(void)fprintf(stderr, "vipw: corrupted entry");
bad:			(void)fprintf(stderr, "; line #%d.\n", lcnt);
			(void)fflush(stderr);
			return(1);
E 14
		}
E 10
	}
D 10
	fprintf(stderr, "vipw: root login corrupted, %s unchanged.\n", passwd);
	return(0);
E 10
I 10
D 14
	return(1);
E 14
I 14
	return(0);
E 14
E 10
}

D 13
static
E 13
E 9
makedb(file)
D 9
	char *file;
E 9
I 9
D 10
	char	*file;
E 10
I 10
	char *file;
E 10
E 9
{
D 9
	int status, pid, w;
E 9
I 9
D 10
	int	status, pid, w;
E 10
I 10
	int status, pid, w;
E 10
E 9

D 9
	if ((pid = vfork()) == 0) {
E 9
I 9
	if (!(pid = vfork())) {
E 9
D 13
		execl("/etc/mkpasswd", "mkpasswd", file, 0);
E 13
I 13
		execl(_PATH_MKPASSWD, "mkpasswd", "-p", file, NULL);
E 13
		_exit(127);
	}
D 9
	while ((w = wait(&status)) != pid && w != -1)
		;
	if (w == -1 || status != 0)
		status = -1;
	return(status);
E 9
I 9
	while ((w = wait(&status)) != pid && w != -1);
D 13
	if (w == -1 || status)
		return(-1);
	return(0);
E 13
I 13
	return(w == -1 || status);
E 13
I 10
}

D 13
static char *
token(bfr)
	char *bfr;
E 13
I 13
D 14
edit(file)
	char *file;
E 14
I 14
edit()
E 14
E 13
{
I 14
	extern int errno;
E 14
D 13
	static char *cp;
	char *start;
E 13
I 13
	int status, pid, w;
D 14
	char *p, *editor, *getenv(), *rindex();
E 14
I 14
	char *p, *editor, *getenv(), *strerror();
E 14
E 13

D 13
	if (bfr)			/* re-init string */
		cp = bfr;
	else if (!cp)			/* check if hit EOS last time */
		return(CHN);
	else if (!bfr)			/* start at next char after ':' */
		++cp;
	for (start = cp;; ++cp)
		if (!*cp) {		/* found EOS; mark it for next time */
			cp = CHN;
			break;
		}
		else if (*cp == ':') {	/* found ':'; end token */
			*cp = '\0';
			break;
		}
	return(start);			/* return token */
E 13
I 13
	if (editor = getenv("EDITOR")) {
		if (p = rindex(editor, '/'))
			++p;
		else
			p = editor;
	}
	else
		p = editor = "vi";
	if (!(pid = vfork())) {
D 14
		execlp(editor, p, file, NULL);
E 14
I 14
		execlp(editor, p, temp, NULL);
		(void)fprintf(stderr, "vipw: %s: %s\n", editor,
		    strerror(errno));
E 14
		_exit(127);
	}
	while ((w = wait(&status)) != pid && w != -1);
	return(w == -1 || status);
I 14
}

prompt()
{
	register int c;

	for (;;) {
		(void)printf("re-edit the password file? [y]: ");
		(void)fflush(stdout);
		c = getchar();
		if (c != EOF && c != (int)'\n')
			while (getchar() != (int)'\n');
		return(c == (int)'n');
	}
	/* NOTREACHED */
}

stop(val)
	int val;
{
	(void)fprintf(stderr, "%s unchanged.\n", passwd);
	(void)unlink(temp);
	exit(val);
E 22
I 22
D 25
	register int nr, nw, off;
E 25
I 25
	int nr, nw, off;
E 25
	char buf[8*1024];
	
	while ((nr = read(from, buf, sizeof(buf))) > 0)
		for (off = 0; off < nr; nr -= nw, off += nw)
			if ((nw = write(to, buf + off, nr)) < 0)
				pw_error(tempname, 1, 1);
	if (nr < 0)
		pw_error(_PATH_MASTERPASSWD, 1, 1);
I 25
}

void
usage()
{

	(void)fprintf(stderr, "usage: vipw\n");
	exit(1);
E 25
E 22
E 14
E 13
E 10
E 9
E 4
E 3
}
E 1
