h30810
s 00004/00001/00140
d D 8.4 95/05/03 12:18:14 mckusick 9 8
c fix include files
e
s 00001/00001/00140
d D 8.3 94/02/22 16:04:59 bostic 8 7
c set the default to 1
e
s 00090/00025/00051
d D 8.2 94/02/22 16:02:37 bostic 7 6
c use -n, not a trailing argument; use getopt even if no arguments;
c don't drop core if NFS not compiled into the kernel; KNF
e
s 00005/00005/00071
d D 8.1 93/06/05 11:08:16 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00006/00054
d D 5.5 92/02/15 17:12:32 mckusick 5 4
c update from Rick Maclem for leases
e
s 00001/00019/00059
d D 5.4 90/06/29 20:10:21 karels 4 3
c use daemon() call
e
s 00001/00011/00077
d D 5.3 90/06/01 16:19:13 bostic 3 2
c new copyright notice
e
s 00005/00007/00083
d D 5.2 90/01/04 14:40:53 mckusick 2 1
c update from Rick Macklem
e
s 00090/00000/00000
d D 5.1 89/08/30 15:38:33 mckusick 1 0
c from Rick Macklem
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
D 6
char copyright[] =
"%Z% Copyright (c) 1989 Regents of the University of California.\n\
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif not lint

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

D 7
#include <stdio.h>
D 2
#include <syslog.h>
E 2
#include <signal.h>
#include <fcntl.h>
D 5
#include <sys/types.h>
E 5
I 5
#include <sys/syslog.h>
E 7
#include <sys/param.h>
E 5
#include <sys/ioctl.h>
I 5
D 7
#include <sys/wait.h>
E 7
I 7
#include <sys/syslog.h>
E 7
#include <sys/ucred.h>
I 7
#include <sys/wait.h>

E 7
D 9
#include <nfs/nfsv2.h>
E 9
I 9
#include <sys/mount.h>
#include <sys/time.h>
#include <nfs/rpcv2.h>
#include <nfs/nfsproto.h>
E 9
#include <nfs/nfs.h>
E 5

I 7
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

E 7
/* Global defs */
#ifdef DEBUG
D 2
#define	syslog(e, s)	fprintf(stderr,(s))
E 2
int debug = 1;
#else
int debug = 0;
#endif
I 5
D 7
extern int errno;
void reapchild();
E 7
E 5

I 7
void nonfs __P((int));
void reapchild __P((int));
void usage __P((void));

E 7
/*
D 2
 * Nfs asynchronous i/o daemon. Just helps out client i/o with read aheads
E 2
I 2
 * Nfsiod does asynchronous buffered I/O on behalf of the NFS client.
D 7
 * It does not have to be running for correct operation, but will improve
 * throughput. The one optional argument is the number of children to fork.
E 7
I 7
 * It does not have to be running for correct operation, but will
 * improve throughput.
E 7
E 2
 */
I 7
int
E 7
main(argc, argv)
	int argc;
	char *argv[];
{
D 7
	register int i;
	int cnt;
E 7
I 7
	int ch, num_servers;
E 7

I 5
D 7
	if (argc != 2 || (cnt = atoi(argv[1])) <= 0 || cnt > 20)
		cnt = 1;
E 7
I 7
#define	MAXNFSDCNT      20
D 8
#define	DEFNFSDCNT       4
E 8
I 8
#define	DEFNFSDCNT       1
E 8
	num_servers = DEFNFSDCNT;
	while ((ch = getopt(argc, argv, "n:")) != EOF)
		switch (ch) {
		case 'n':
			num_servers = atoi(optarg);
			if (num_servers < 1 || num_servers > MAXNFSDCNT) {
				warnx("nfsiod count %d; reset to %d",
				    DEFNFSDCNT);
				num_servers = DEFNFSDCNT;
			}
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	/*
	 * XXX
	 * Backward compatibility, trailing number is the count of daemons.
	 */
	if (argc > 1)
		usage();
	if (argc == 1) {
		num_servers = atoi(argv[0]);
		if (num_servers < 1 || num_servers > MAXNFSDCNT) {
			warnx("nfsiod count %d; reset to %d", DEFNFSDCNT);
			num_servers = DEFNFSDCNT;
		}
	}

E 7
E 5
	if (debug == 0) {
D 4
		if (fork())
			exit(0);
		{ int s;
		for (s = 0; s < 10; s++)
			(void) close(s);
		}
		(void) open("/", O_RDONLY);
		(void) dup2(0, 1);
		(void) dup2(0, 2);
		{ int tt = open("/dev/tty", O_RDWR);
		  if (tt > 0) {
			ioctl(tt, TIOCNOTTY, (char *)0);
			close(tt);
		  }
		}
		(void) setpgrp(0, 0);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
E 4
I 4
		daemon(0, 0);
E 4
D 7
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
D 5
		signal(SIGTERM, SIG_IGN);
E 5
		signal(SIGHUP, SIG_IGN);
E 7
I 7
		(void)signal(SIGHUP, SIG_IGN);
		(void)signal(SIGINT, SIG_IGN);
		(void)signal(SIGQUIT, SIG_IGN);
		(void)signal(SIGSYS, nonfs);
E 7
	}
D 2
	openlog("nfsiod:", LOG_PID, LOG_DAEMON);
E 2
D 5
	if (argc != 2 || (cnt = atoi(argv[1])) <= 0 || cnt > 20)
		cnt = 1;
E 5
I 5
D 7
	signal(SIGCHLD, reapchild);
E 7
I 7
	(void)signal(SIGCHLD, reapchild);

E 7
	openlog("nfsiod:", LOG_PID, LOG_DAEMON);
E 5
D 7
	for (i = 1; i < cnt; i++)
		if (fork() == 0)
			break;
D 2
	if (async_daemon() < 0)		/* Only returns on error */
		syslog(LOG_ERR, "nfsiod() failed %m");
	exit();
E 2
I 2
D 5
	async_daemon();		/* Never returns */
	exit(1);
E 5
I 5
	if (nfssvc(NFSSVC_BIOD, (char *)0) < 0)
		syslog(LOG_ERR, "nfssvc failed %m");
E 7
I 7

	while (num_servers--)
		switch (fork()) {
		case -1:
			syslog(LOG_ERR, "fork: %m");
			exit (1);
		case 0:
			if (nfssvc(NFSSVC_BIOD, NULL) < 0) {
				syslog(LOG_ERR, "nfssvc: %m");
				exit (1);
			}
			exit(0);
		}
	exit (0);
E 7
}

void
D 7
reapchild()
E 7
I 7
nonfs(signo)
	int signo;
E 7
{
I 7
	syslog(LOG_ERR, "missing system call: NFS not available.");
}
E 7

D 7
	while (wait3((int *) NULL, WNOHANG, (struct rusage *) NULL))
		;
E 7
I 7
void
reapchild(signo)
	int signo;
{

	while (wait3(NULL, WNOHANG, NULL));
}

void
usage()
{
	(void)fprintf(stderr, "usage: nfsiod [-n num_servers]\n");
	exit(1);
E 7
E 5
E 2
}
E 1
