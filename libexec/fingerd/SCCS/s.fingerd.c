h20656
s 00005/00005/00159
d D 8.1 93/06/04 18:47:56 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00022/00139
d D 5.10 92/07/15 09:44:07 bostic 13 12
c KNF, no ANSI C declarations; turn off getopt logging
e
s 00057/00016/00104
d D 5.9 92/07/12 22:57:56 tef 12 11
c add -s, -l and -p options for better conformance with RFC1196
e
s 00004/00002/00116
d D 5.8 92/02/06 18:57:05 bostic 11 10
c don't break if multiple /w's
e
s 00048/00020/00070
d D 5.7 92/02/06 17:19:52 bostic 10 9
c Eric points out that the -l should be before the user names.
e
s 00001/00011/00089
d D 5.6 90/06/01 15:50:52 bostic 9 8
c new copyright notice
e
s 00002/00001/00098
d D 5.5 89/04/02 12:33:23 bostic 8 7
c add pathnames.h
e
s 00050/00055/00049
d D 5.4 88/11/23 17:04:05 bostic 7 6
c cleanup rewrite; do arguments, errors correctly, don't bother waiting
e
s 00003/00006/00101
d D 5.3 88/11/03 18:16:38 bostic 6 5
c fix security problem; overflow the buffer and change the pc ret
e
s 00018/00006/00089
d D 5.2 88/09/19 21:16:50 bostic 5 4
c Berkeley copyright
e
s 00013/00001/00082
d D 5.1 85/06/06 11:04:30 dist 4 3
c Add copyright
e
s 00033/00016/00050
d D 1.3 84/07/26 11:03:42 ralph 3 2
c fix popen security hole.
e
s 00026/00018/00040
d D 1.2 84/06/18 15:21:40 ralph 2 1
c translate \n to \r\n.
e
s 00058/00000/00000
d D 1.1 84/05/11 22:24:57 sam 1 0
c date and time created 84/05/11 22:24:57 by sam
e
u
U
t
T
I 4
/*
D 5
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 14
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 9
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 5
 */

E 4
I 1
#ifndef lint
I 4
D 14
char copyright[] =
D 5
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 5
I 5
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 5
 All rights reserved.\n";
E 14
I 14
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 14
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

#ifndef lint
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5
E 4

I 13
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
E 13
I 10
#include <errno.h>
I 13

E 13
#include <unistd.h>
I 13
#include <syslog.h>
#include <netdb.h>
E 13
E 10
D 7
/*
 * Finger server.
 */
#include <sys/types.h>
#include <netinet/in.h>
E 7
D 6

E 6
#include <stdio.h>
I 10
#include <stdlib.h>
#include <strings.h>
I 12
D 13
#include <syslog.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
E 13
E 12
E 10
I 8
#include "pathnames.h"
E 8
D 7
#include <ctype.h>
E 7

I 10
void err __P((const char *, ...));

int
E 10
I 2
D 3
FILE	*popen();

E 3
E 2
D 7
main(argc, argv)
I 5
	int argc;
E 5
	char *argv[];
E 7
I 7
D 12
main()
E 12
I 12
D 13
main(int argc, char **argv)
E 13
I 13
main(argc, argv)
	int argc;
	char *argv[];
E 13
E 12
E 7
{
D 2
	register char **fargp;
	register char *cp;
	char *fargv[80], line[512];
E 2
I 2
D 3
	register char *cp, *sp;
	char cmdbuf[512], line[512];
E 3
I 3
D 7
	register char *sp;
	char line[512];
E 7
I 7
	register FILE *fp;
	register int ch;
	register char *lp;
D 13
	int p[2];
#define	ENTRIES	50
D 10
	char **ap, *av[ENTRIES + 1], line[1024], *strtok();
E 10
I 10
	char **ap, *av[ENTRIES + 1], **comp, line[1024];
E 10
D 12

D 10
#ifdef LOGGING					/* unused for now */
E 10
I 10
#ifdef LOGGING					/* Unused for now. */
E 10
#include <netinet/in.h>
E 12
I 12
	char *prog = _PATH_FINGER;
E 13
	struct hostent *hp;
E 12
E 7
E 3
E 2
	struct sockaddr_in sin;
D 3
	int i;
E 3
I 3
D 7
	int i, p[2], pid, status;
E 3
I 2
	FILE *fp;
I 3
	char *av[4];
E 7
I 7
D 12
	int sval;
E 12
I 12
D 13
	int sval = sizeof(sin);
	int secure=0, logging=0;
	extern char *optarg;
E 13
I 13
	int p[2], logging, secure, sval;
#define	ENTRIES	50
	char **ap, *av[ENTRIES + 1], **comp, line[1024], *prog;
E 13
E 12
E 7
E 3
E 2

D 7
	i = sizeof (sin);
	if (getpeername(0, &sin, &i) < 0)
		fatal(argv[0], "getpeername");
D 6
	line[0] = '\0';
	gets(line);
E 6
I 6
	if (fgets(line, sizeof(line), stdin) == NULL)
E 7
I 7
D 12
	sval = sizeof(sin);
	if (getpeername(0, &sin, &sval) < 0)
D 10
		fatal("getpeername");
E 10
I 10
		err("getpeername: %s", strerror(errno));
E 10
#endif
E 12
I 12
D 13
	openlog("fingerd", LOG_PID|LOG_CONS, LOG_DAEMON);
	while ((ch=getopt(argc, argv, "slp:")) != EOF)
E 13
I 13
	prog = _PATH_FINGER;
	logging = secure = 0;
	openlog("fingerd", LOG_PID | LOG_CONS, LOG_DAEMON);
	opterr = 0;
	while ((ch = getopt(argc, argv, "slp:")) != EOF)
E 13
		switch (ch) {
D 13
		case 's':
			secure++;
			break;
E 13
		case 'l':
D 13
			logging++;
E 13
I 13
			logging = 1;
E 13
			break;
		case 'p':
			prog = optarg;
			break;
I 13
		case 's':
			secure = 1;
			break;
E 13
		case '?':
		default:
D 13
			syslog(LOG_ERR, "unknown option: %c", ch);
E 13
I 13
			err("illegal option -- %c", ch);
E 13
		}
E 12

I 12
	if (logging) {
I 13
		sval = sizeof(sin);
E 13
		if (getpeername(0, (struct sockaddr *)&sin, &sval) < 0)
			err("getpeername: %s", strerror(errno));
		if (hp = gethostbyaddr((char *)&sin.sin_addr.s_addr,
D 13
				sizeof(sin.sin_addr.s_addr), AF_INET))
E 13
I 13
		    sizeof(sin.sin_addr.s_addr), AF_INET))
E 13
			lp = hp->h_name;
		else
			lp = inet_ntoa(sin.sin_addr);
		syslog(LOG_NOTICE, "query from %s", lp);
	}

E 12
	if (!fgets(line, sizeof(line), stdin))
E 7
		exit(1);
E 6
D 2
	fargp = fargv;
	*fargp++ = "finger";
	cp = line;
E 2
I 2
D 7
	sp = line;
E 7
I 7
D 10

E 7
D 3
	strcpy(cmdbuf, "/usr/ucb/finger");
	cp = cmdbuf + strlen(cmdbuf);
E 3
I 3
	av[0] = "finger";
D 6
	i = 1;
E 3
E 2
	while (1) {
E 6
I 6
D 7
	for (i = 1;;) {
E 6
D 2
		while (isspace(*cp))
			cp++;
		if (!*cp)
E 2
I 2
		while (isspace(*sp))
			sp++;
		if (!*sp)
E 7
I 7
	for (lp = line, ap = &av[1];;) {
E 10
I 10
	
	comp = &av[1];
	for (lp = line, ap = &av[2];;) {
E 10
		*ap = strtok(lp, " \t\r\n");
D 10
		if (!*ap)
E 10
I 10
D 12
		if (*ap == NULL)
E 12
I 12
		if (!*ap) {
			if (secure && ap == &av[2]) {
				puts("must provide username\r\n");
				exit(1);
			}
E 12
E 10
E 7
E 2
			break;
I 12
		}
		if (secure && strchr(*ap, '@')) {
			puts("fowarding service denied\r\n");
			exit(1);
		}

E 12
D 2
		*fargp++ = cp;
		if (*cp == '/' && (cp[1] == 'W' || cp[1] == 'w')) {
E 2
I 2
D 3
		*cp++ = ' ';
E 3
D 7
		if (*sp == '/' && (sp[1] == 'W' || sp[1] == 'w')) {
			sp += 2;
E 2
D 3
			*cp++ = '-';
			*cp++ = 'l';
E 3
I 3
			av[i++] = "-l";
E 3
		}
D 2
		while (!isspace(*cp))
			cp++;
		*cp++ = '\0';
E 2
I 2
D 3
		while (!isspace(*sp))
			*cp++ = *sp++;
E 3
I 3
		if (*sp && !isspace(*sp)) {
			av[i++] = sp;
			while (*sp && !isspace(*sp))
				sp++;
			*sp = '\0';
		}
E 7
I 7
		/* RFC742: "/[Ww]" == "-l" */
D 11
		if ((*ap)[0] == '/' && ((*ap)[1] == 'W' || (*ap)[1] == 'w'))
D 10
			*ap = "-l";
		if (++ap == av + ENTRIES)
E 10
I 10
			*comp-- = "-l";
E 11
I 11
		if ((*ap)[0] == '/' && ((*ap)[1] == 'W' || (*ap)[1] == 'w')) {
			av[1] = "-l";
			comp = &av[0];
		}
E 11
		else if (++ap == av + ENTRIES)
E 10
			break;
		lp = NULL;
E 7
E 3
E 2
	}
I 10
D 12
	*comp = "finger";
E 12
E 10
D 2
	*fargp = NULL;
	execv("/usr/ucb/finger", fargv);
	execvp("finger", fargv);
	fatal(argv[0], "/usr/ucb/finger");
E 2
I 2
D 3
	*cp++ = '\0';
	if ((fp = popen(cmdbuf, "r")) == NULL)
		fatal(argv[0], "/usr/ucb/finger");
E 3
I 3
D 7
	av[i] = 0;
E 7
I 7

I 12
	if (lp = strrchr(prog, '/'))
		*comp = ++lp;
	else
		*comp = prog;
E 12
E 7
	if (pipe(p) < 0)
D 7
		fatal(argv[0], "pipe");
	if ((pid = fork()) == 0) {
		close(p[0]);
E 7
I 7
D 10
		fatal("pipe");
E 10
I 10
		err("pipe: %s", strerror(errno));
E 10

D 10
	switch(fork()) {
E 10
I 10
	switch(vfork()) {
E 10
	case 0:
		(void)close(p[0]);
E 7
		if (p[1] != 1) {
D 7
			dup2(p[1], 1);
			close(p[1]);
E 7
I 7
			(void)dup2(p[1], 1);
			(void)close(p[1]);
E 7
		}
D 8
		execv("/usr/ucb/finger", av);
E 8
I 8
D 10
		execv(_PATH_FINGER, av);
E 10
I 10
D 12
		execv(_PATH_FINGER, comp);
		err("execv: %s: %s", _PATH_FINGER, strerror(errno));
E 12
I 12
		execv(prog, comp);
		err("execv: %s: %s", prog, strerror(errno));
E 12
E 10
E 8
		_exit(1);
I 7
	case -1:
D 10
		fatal("fork");
E 10
I 10
		err("fork: %s", strerror(errno));
E 10
E 7
	}
D 7
	if (pid == -1)
		fatal(argv[0], "fork");
	close(p[1]);
	if ((fp = fdopen(p[0], "r")) == NULL)
		fatal(argv[0], "fdopen");
E 3
	while ((i = getc(fp)) != EOF) {
		if (i == '\n')
E 7
I 7
	(void)close(p[1]);
	if (!(fp = fdopen(p[0], "r")))
D 10
		fatal("fdopen");
E 10
I 10
		err("fdopen: %s", strerror(errno));
E 10
	while ((ch = getc(fp)) != EOF) {
		if (ch == '\n')
E 7
			putchar('\r');
D 7
		putchar(i);
E 7
I 7
		putchar(ch);
E 7
	}
D 3
	pclose(fp);
E 3
I 3
D 7
	fclose(fp);
	while ((i = wait(&status)) != pid && i != -1)
		;
E 3
	return(0);
E 7
I 7
	exit(0);
E 7
E 2
}

D 7
fatal(prog, s)
	char *prog, *s;
E 7
I 7
D 10
fatal(msg)
	char *msg;
E 7
{
D 6

E 6
D 7
	fprintf(stderr, "%s: ", prog);
	perror(s);
E 7
I 7
	extern int errno;
	char *strerror();
E 10
I 10
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
E 10

D 10
	fprintf(stderr, "fingerd: %s: %s\r\n", msg, strerror(errno));
E 10
I 10
void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
D 12
	(void)fprintf(stderr, "fingerd: ");
	(void)vfprintf(stderr, fmt, ap);
E 12
I 12
	(void)vsyslog(LOG_ERR, fmt, ap);
E 12
	va_end(ap);
D 12
	(void)fprintf(stderr, "\r\n");
E 12
E 10
E 7
	exit(1);
I 10
	/* NOTREACHED */
E 10
}
E 1
