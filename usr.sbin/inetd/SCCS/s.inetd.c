h60047
s 00004/00003/01225
d D 8.4 94/04/13 13:04:34 karels 42 41
c restore my 1985 change to pass the listening socket to "stream wait" servers;
c document this, and correct the description of wait vs. nowait for datagram,
c plus other man page cleanups
e
s 00002/00002/01226
d D 8.3 94/04/13 11:34:40 pendry 41 40
c add 1994 copyright
e
s 00120/00080/01108
d D 8.2 94/04/03 14:10:00 pendry 40 39
c prettyness police
e
s 00005/00005/01183
d D 8.1 93/06/06 13:57:20 bostic 39 38
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/01187
d D 5.33 93/06/01 17:47:52 mckusick 38 37
c missing initialization (from Karels)
e
s 00003/00001/01184
d D 5.32 93/05/16 22:24:03 torek 37 36
c make gcc shut up
e
s 00316/00069/00869
d D 5.31 93/02/01 22:52:05 andrew 36 35
c incorporate Mark Lottor's TCPMUX code; minor bug fixes & error checks
e
s 00005/00004/00933
d D 5.30 91/06/03 21:25:07 karels 35 34
c EOF means quit (discard server)
e
s 00004/00004/00933
d D 5.29 91/05/18 15:38:14 bostic 34 33
c If a service port shuts down due to too many requests, the request
c that exceeded the threshold doesn't get closed. The client then hangs forever
c (until aborted). Its fairly easy to exceed the threshold on a Cray.
c From: nbrotz@poplar.cray.com (Norb Brotz)
e
s 00001/00001/00936
d D 5.28 91/03/28 15:44:06 karels 33 32
c don't close descriptors that aren't open
e
s 00066/00061/00871
d D 5.27 91/03/04 12:09:50 karels 32 31
c don't do FD_ISSET on fd -1; wait now returns status in int;
c fix some formatting
e
s 00014/00021/00918
d D 5.26 91/03/02 14:47:09 bostic 31 30
c ANSI, replace local copy of strdup
e
s 00004/00029/00935
d D 5.25 90/06/29 21:01:32 karels 30 29
c use daemon() call
e
s 00005/00004/00959
d D 5.24 90/06/22 18:45:33 bostic 29 28
c Inetd believes that datagram servers are either wait/nowait but that
c stream servers are always nowait.  It refuses to believe in a `wait' stream
c server.  Removing these tests allows wait/nowait to work for stream servers
c too.  -- from Chris Torek.
e
s 00001/00001/00962
d D 5.23 90/06/22 18:40:40 bostic 28 27
c getc returns an int; from Chris Torek
e
s 00001/00011/00962
d D 5.22 90/06/01 18:41:20 bostic 27 26
c new copyright notice
e
s 00001/00001/00972
d D 5.21 90/05/15 20:03:52 bostic 26 25
c string.h is ANSI C include file
e
s 00008/00001/00965
d D 5.20 90/04/04 14:22:53 bostic 25 24
c don't lose datagram server on reconfig; bug report 4.3BSD-tahoe/etc/21
e
s 00002/00002/00964
d D 5.19 90/04/04 08:17:58 bostic 24 23
c change maximum arguments to 20; 5's too few, and it's not expensive
c bug report 4.3BSD-tahoe/usr.sbin/9
e
s 00004/00001/00962
d D 5.18 90/01/02 13:33:29 bostic 23 22
c new signals
e
s 00005/00004/00958
d D 5.17 89/08/09 09:12:53 karels 22 21
c discard faster
e
s 00002/00002/00960
d D 5.16 89/05/11 14:08:01 bostic 21 20
c file reorg, pathnames.h, paths.h
e
s 00002/00001/00960
d D 5.15 89/04/02 14:14:33 bostic 20 19
c add pathnames.h
e
s 00054/00047/00907
d D 5.14 89/01/23 16:12:00 bostic 19 18
c add getopt(); lint and general minor cleanups;
c add space for daemons to overwrite environment for ps
e
s 00010/00005/00944
d D 5.13 88/06/18 14:34:31 bostic 18 17
c install approved copyright notice
e
s 00011/00006/00938
d D 5.12 87/12/26 12:32:35 bostic 17 16
c Berkeley header; declare strdup() properly for ANSI C
e
s 00004/00004/00940
d D 5.11 87/10/22 10:35:54 bostic 16 15
c ANSI C; sprintf now returns an int.
e
s 00028/00021/00916
d D 5.10 87/10/16 16:20:22 karels 15 14
c ignore stop signals, in case we aren't called directly from init/rc
e
s 00043/00052/00894
d D 5.9 87/09/22 08:03:00 bostic 14 13
c redo chargen functions; bug report 4.3BSD/etc/32 
c fix rlogin shell bug; bug report 4.3BSD/etc/33 
c fix long/int problems from 2.10BSD
e
s 00009/00005/00937
d D 5.8 87/09/01 09:38:26 karels 13 12
c fix incorrect title; block signals to test if there's nothing to do
e
s 00024/00002/00918
d D 5.7 86/08/19 09:27:21 karels 12 11
c bug fix, internals had to be last
e
s 00142/00061/00778
d D 5.6 86/04/29 12:35:29 karels 11 10
c notice when server failing, drop service fo a while;
c block all the interesting signals while messing with service blocks;
c check all of the descriptors ready after select
e
s 00024/00018/00815
d D 5.5 86/03/21 06:43:57 lepreau 10 9
c the "user" field was forgotten & thus couldn't be changed; lint.
e
s 00350/00021/00483
d D 5.4 86/03/13 21:25:04 karels 9 8
c add internal services
e
s 00028/00022/00476
d D 5.3 85/09/27 10:40:20 karels 8 7
c changes from tef: allow wait on streams, use sigmask, etc.;
c convert to use new select macros (and up to 256 sockets)
e
s 00001/00001/00497
d D 5.2 85/09/17 19:17:29 eric 7 6
c facilities in syslog
e
s 00014/00002/00484
d D 5.1 85/05/28 14:24:12 dist 6 5
c add copyright
e
s 00013/00000/00473
d D 4.4 84/11/10 22:03:54 bloom 5 3
c added user field to config file so that daemons may be run as somebody 
c besides root
e
s 00012/00000/00473
d R 4.4 84/11/08 17:19:28 bloom 4 3
c add user to config file to allow the servers to run as someone besides
c root
e
s 00006/00003/00467
d D 4.3 84/09/04 21:41:22 sam 3 2
c convert setsockopt calls to new interface
e
s 00017/00020/00453
d D 4.2 84/05/18 11:42:05 ralph 2 1
c modified to use syslog
e
s 00473/00000/00000
d D 4.1 84/04/11 16:31:53 karels 1 0
c date and time created 84/04/11 16:31:53 by karels
e
u
U
t
T
I 6
/*
D 35
 * Copyright (c) 1983 Regents of the University of California.
E 35
I 35
D 36
 * Copyright (c) 1983,1991 The Regents of the University of California.
E 36
I 36
D 39
 * Copyright (c) 1983, 1991, 1993 The Regents of the University of California.
E 36
E 35
D 17
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 17
I 17
 * All rights reserved.
E 39
I 39
D 41
 * Copyright (c) 1983, 1991, 1993
E 41
I 41
 * Copyright (c) 1983, 1991, 1993, 1994
E 41
 *	The Regents of the University of California.  All rights reserved.
E 39
 *
D 27
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
E 27
I 27
 * %sccs.include.redist.c%
E 27
E 18
E 17
 */

E 6
I 1
#ifndef lint
D 6
static	char sccsid[] = "%W% (Berkeley) %G%";
#endif
E 6
I 6
D 39
char copyright[] =
D 36
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 36
I 36
"%Z% Copyright (c) 1983, 1991, 1993 Regents of the University of California.\n\
E 36
 All rights reserved.\n";
E 39
I 39
static char copyright[] =
D 41
"%Z% Copyright (c) 1983, 1991, 1993\n\
E 41
I 41
"%Z% Copyright (c) 1983, 1991, 1993, 1994\n\
E 41
	The Regents of the University of California.  All rights reserved.\n";
E 39
D 17
#endif not lint
E 17
I 17
#endif /* not lint */
E 17

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 17
#endif not lint
E 17
I 17
#endif /* not lint */
E 17
E 6

/*
 * Inetd - Internet super-server
 *
D 36
 * This program invokes all internet services as needed.
 * connection-oriented services are invoked each time a
 * connection is made, by creating a process.  This process
 * is passed the connection as file descriptor 0 and is
 * expected to do a getpeername to find out the source host
 * and port.
E 36
I 36
 * This program invokes all internet services as needed.  Connection-oriented
 * services are invoked each time a connection is made, by creating a process.
 * This process is passed the connection as file descriptor 0 and is expected
 * to do a getpeername to find out the source host and port.
E 36
 *
 * Datagram oriented services are invoked when a datagram
 * arrives; a process is created and passed a pending message
 * on file descriptor 0.  Datagram servers may either connect
 * to their peer, freeing up the original socket for inetd
 * to receive further messages on, or ``take over the socket'',
 * processing all arriving datagrams and, eventually, timing
 * out.	 The first type of server is said to be ``multi-threaded'';
 * the second type of server ``single-threaded''. 
 *
 * Inetd uses a configuration file which is read at startup
 * and, possibly, at some later time in response to a hangup signal.
 * The configuration file is ``free format'' with fields given in the
 * order shown below.  Continuation lines for an entry must being with
 * a space or tab.  All fields must be present in each entry.
 *
D 36
 *	service name			must be in /etc/services
E 36
I 36
 *	service name			must be in /etc/services or must
 *					name a tcpmux service
E 36
 *	socket type			stream/dgram/raw/rdm/seqpacket
 *	protocol			must be in /etc/protocols
 *	wait/nowait			single-threaded/multi-threaded
I 5
 *	user				user to run daemon as
E 5
 *	server program			full path name
D 24
 *	server program arguments	maximum of MAXARGS (5)
E 24
I 24
 *	server program arguments	maximum of MAXARGS (20)
E 24
 *
I 36
 * TCP services without official port numbers are handled with the
 * RFC1078-based tcpmux internal service. Tcpmux listens on port 1 for
 * requests. When a connection is made from a foreign host, the service
 * requested is passed to tcpmux, which looks it up in the servtab list
 * and returns the proper entry for the service. Tcpmux returns a
 * negative reply if the service doesn't exist, otherwise the invoked
 * server is expected to return the positive reply if the service type in
 * inetd.conf file has the prefix "tcpmux/". If the service type has the
 * prefix "tcpmux/+", tcpmux will return the positive reply for the
 * process; this is for compatibility with older server code, and also
 * allows you to invoke programs that use stdin/stdout without putting any
 * special server code in them. Services that use tcpmux are "nowait"
 * because they do not have a well-known port and hence cannot listen
 * for new requests.
 *
E 36
 * Comment lines are indicated by a `#' in column 1.
 */
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
D 36
#include <sys/file.h>
E 36
#include <sys/wait.h>
I 10
#include <sys/time.h>
#include <sys/resource.h>
E 10

#include <netinet/in.h>
#include <arpa/inet.h>

#include <errno.h>
D 19
#include <stdio.h>
E 19
D 36
#include <signal.h>
E 36
I 36
#include <fcntl.h>
E 36
#include <netdb.h>
I 2
D 36
#include <syslog.h>
E 36
I 5
#include <pwd.h>
I 36
#include <signal.h>
E 36
I 19
#include <stdio.h>
I 36
#include <stdlib.h>
E 36
D 26
#include <strings.h>
E 26
I 26
#include <string.h>
I 36
#include <syslog.h>
#include <unistd.h>

E 36
E 26
I 20
#include "pathnames.h"
E 20
E 19
E 5
E 2

I 11
#define	TOOMANY		40		/* don't start more than TOOMANY */
#define	CNT_INTVL	60		/* servers in CNT_INTVL sec. */
#define	RETRYTIME	(60*10)		/* retry after bind or server fail */

#define	SIGBLOCK	(sigmask(SIGCHLD)|sigmask(SIGHUP)|sigmask(SIGALRM))

E 11
D 36
extern	int errno;
E 36

D 11
int	reapchild();
E 11
I 11
D 23
int	reapchild(), retry();
E 23
I 23
D 40
void	config(), reapchild(), retry();
E 23
E 11
D 36
char	*index();
char	*malloc();
E 36

E 40
int	debug = 0;
D 8
int	allsock;
E 8
I 8
int	nsock, maxsock;
fd_set	allsock;
E 8
int	options;
I 11
int	timingout;
I 36
int	toomany = TOOMANY;
E 36
E 11
struct	servent *sp;

struct	servtab {
	char	*se_service;		/* name of service */
	int	se_socktype;		/* type of socket to use */
	char	*se_proto;		/* protocol used */
	short	se_wait;		/* single threaded server */
	short	se_checked;		/* looked at during merge */
I 5
	char	*se_user;		/* user name to run as */
I 9
	struct	biltin *se_bi;		/* if built-in, description */
E 9
E 5
	char	*se_server;		/* server program */
D 24
#define MAXARGV 5
E 24
I 24
#define	MAXARGV 20
E 24
	char	*se_argv[MAXARGV+1];	/* program arguments */
	int	se_fd;			/* open descriptor */
I 36
	int	se_type;		/* type */
E 36
	struct	sockaddr_in se_ctrladdr;/* bound address */
I 11
	int	se_count;		/* number started since se_time */
	struct	timeval se_time;	/* start of se_count */
E 11
	struct	servtab *se_next;
} *servtab;

I 36
#define NORM_TYPE	0
#define MUX_TYPE	1
#define MUXPLUS_TYPE	2
#define ISMUX(sep)	(((sep)->se_type == MUX_TYPE) || \
			 ((sep)->se_type == MUXPLUS_TYPE))
#define ISMUXPLUS(sep)	((sep)->se_type == MUXPLUS_TYPE)

E 36
I 9
D 40
int echo_stream(), discard_stream(), machtime_stream();
int daytime_stream(), chargen_stream();
int echo_dg(), discard_dg(), machtime_dg(), daytime_dg(), chargen_dg();
I 36
struct servtab *tcpmux();
E 40
E 36

I 40
void		chargen_dg __P((int, struct servtab *));
void		chargen_stream __P((int, struct servtab *));
void		close_sep __P((struct servtab *));
void		config __P((int));
void		daytime_dg __P((int, struct servtab *));
void		daytime_stream __P((int, struct servtab *));
void		discard_dg __P((int, struct servtab *));
void		discard_stream __P((int, struct servtab *));
void		echo_dg __P((int, struct servtab *));
void		echo_stream __P((int, struct servtab *));
void		endconfig __P((void));
struct servtab *enter __P((struct servtab *));
void		freeconfig __P((struct servtab *));
struct servtab *getconfigent __P((void));
void		machtime_dg __P((int, struct servtab *));
void		machtime_stream __P((int, struct servtab *));
char	       *newstr __P((char *));
char	       *nextline __P((FILE *));
void		print_service __P((char *, struct servtab *));
void		reapchild __P((int));
void		retry __P((int));
int		setconfig __P((void));
void		setup __P((struct servtab *));
char	       *sskip __P((char **));
char	       *skip __P((char **));
struct servtab *tcpmux __P((int));

E 40
struct biltin {
	char	*bi_service;		/* internally provided service name */
	int	bi_socktype;		/* type of socket supported */
	short	bi_fork;		/* 1 if should fork before call */
	short	bi_wait;		/* 1 if should wait for child */
D 40
	int	(*bi_fn)();		/* function which performs it */
E 40
I 40
	void	(*bi_fn)();		/* function which performs it */
E 40
} biltins[] = {
	/* Echo received data */
D 40
	"echo",		SOCK_STREAM,	1, 0,	echo_stream,
	"echo",		SOCK_DGRAM,	0, 0,	echo_dg,
E 40
I 40
	{ "echo",	SOCK_STREAM,	1, 0,	echo_stream },
	{ "echo",	SOCK_DGRAM,	0, 0,	echo_dg },
E 40

	/* Internet /dev/null */
D 40
	"discard",	SOCK_STREAM,	1, 0,	discard_stream,
	"discard",	SOCK_DGRAM,	0, 0,	discard_dg,
E 40
I 40
	{ "discard",	SOCK_STREAM,	1, 0,	discard_stream },
	{ "discard",	SOCK_DGRAM,	0, 0,	discard_dg },
E 40

	/* Return 32 bit time since 1970 */
D 40
	"time",		SOCK_STREAM,	0, 0,	machtime_stream,
	"time",		SOCK_DGRAM,	0, 0,	machtime_dg,
E 40
I 40
	{ "time",	SOCK_STREAM,	0, 0,	machtime_stream },
	{ "time",	SOCK_DGRAM,	0, 0,	machtime_dg },
E 40

	/* Return human-readable time */
D 40
	"daytime",	SOCK_STREAM,	0, 0,	daytime_stream,
	"daytime",	SOCK_DGRAM,	0, 0,	daytime_dg,
E 40
I 40
	{ "daytime",	SOCK_STREAM,	0, 0,	daytime_stream },
	{ "daytime",	SOCK_DGRAM,	0, 0,	daytime_dg },
E 40

	/* Familiar character generator */
D 40
	"chargen",	SOCK_STREAM,	1, 0,	chargen_stream,
	"chargen",	SOCK_DGRAM,	0, 0,	chargen_dg,
E 40
I 40
	{ "chargen",	SOCK_STREAM,	1, 0,	chargen_stream },
	{ "chargen",	SOCK_DGRAM,	0, 0,	chargen_dg },
E 40
D 36
	0
E 36
I 36

D 40
	"tcpmux",	SOCK_STREAM,	1, 0,	(int (*)())tcpmux,
E 40
I 40
	{ "tcpmux",	SOCK_STREAM,	1, 0,	(void (*)())tcpmux },
E 40

D 40
	NULL
E 40
I 40
	{ NULL }
E 40
E 36
};

#define NUMINT	(sizeof(intab) / sizeof(struct inent))
E 9
D 20
char	*CONFIG = "/etc/inetd.conf";
E 20
I 20
char	*CONFIG = _PATH_INETDCONF;
E 20
I 9
char	**Argv;
char 	*LastArg;
E 9

I 40
int
E 40
D 9
main(argc, argv)
E 9
I 9
main(argc, argv, envp)
E 9
	int argc;
D 9
	char *argv[];
E 9
I 9
	char *argv[], *envp[];
E 9
{
I 19
D 36
	extern char *optarg;
	extern int optind;
E 36
E 19
D 8
	int ctrl;
E 8
D 40
	register struct servtab *sep;
I 5
	register struct passwd *pwd;
E 5
D 19
	char *cp, buf[50];
D 11
	int pid, i;
E 11
I 11
	int pid, i, dofork;
E 19
I 19
	register int tmpint;
E 40
I 40
	struct servtab *sep;
	struct passwd *pwd;
E 40
E 19
	struct sigvec sv;
I 19
D 40
	int ch, pid, dofork;
E 40
I 40
	int tmpint, ch, dofork;
	pid_t pid;
E 40
	char buf[50];
E 19
E 11

I 9
	Argv = argv;
	if (envp == 0 || *envp == 0)
		envp = argv;
	while (*envp)
		envp++;
	LastArg = envp[-1] + strlen(envp[-1]);
E 9
D 19
	argc--, argv++;
	while (argc > 0 && *argv[0] == '-') {
		for (cp = &argv[0][1]; *cp; cp++) switch (*cp) {
E 19

I 19
D 36
	while ((ch = getopt(argc, argv, "d")) != EOF)
E 36
I 36
	openlog("inetd", LOG_PID | LOG_NOWAIT, LOG_DAEMON);

	while ((ch = getopt(argc, argv, "dR:")) != EOF)
E 36
		switch(ch) {
E 19
		case 'd':
			debug = 1;
			options |= SO_DEBUG;
			break;
I 36
		case 'R': {	/* invocation rate */
			char *p;

			tmpint = strtol(optarg, &p, 0);
			if (tmpint < 1 || *p)
				syslog(LOG_ERR,
			         "-R %s: bad value for service invocation rate",
					optarg);
			else
				toomany = tmpint;
			break;
		}
E 36
D 19

E 19
I 19
		case '?':
E 19
		default:
D 19
			fprintf(stderr,
			    "inetd: Unknown flag -%c ignored.\n", *cp);
			break;
E 19
I 19
D 36
			fprintf(stderr, "usage: inetd [-d]");
E 36
I 36
			syslog(LOG_ERR,
				"usage: inetd [-d] [-R rate] [conf-file]");
E 36
			exit(1);
E 19
		}
D 19
nextopt:
		argc--, argv++;
	}
E 19
I 19
	argc -= optind;
	argv += optind;

E 19
	if (argc > 0)
		CONFIG = argv[0];
D 15
#ifndef DEBUG
	if (fork())
		exit(0);
	{ int s;
	for (s = 0; s < 10; s++)
		(void) close(s);
E 15
I 15
D 30
	if (debug == 0) {
		if (fork())
			exit(0);
D 19
		{ int s;
		for (s = 0; s < 10; s++)
			(void) close(s);
		}
E 19
I 19
		for (tmpint = 0; tmpint < 10; tmpint++)
			(void) close(tmpint);
E 19
		(void) open("/", O_RDONLY);
		(void) dup2(0, 1);
		(void) dup2(0, 2);
D 19
		{ int tt = open("/dev/tty", O_RDWR);
		  if (tt > 0) {
			ioctl(tt, TIOCNOTTY, (char *)0);
			close(tt);
		  }
E 19
I 19
D 21
		tmpint = open("/dev/tty", O_RDWR);
E 21
I 21
		tmpint = open(_PATH_TTY, O_RDWR);
E 21
		if (tmpint > 0) {
			ioctl(tmpint, TIOCNOTTY, (char *)0);
			close(tmpint);
E 19
		}
		(void) setpgrp(0, 0);
D 19
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
E 19
I 19
		(void) signal(SIGTSTP, SIG_IGN);
		(void) signal(SIGTTIN, SIG_IGN);
		(void) signal(SIGTTOU, SIG_IGN);
E 19
E 15
	}
E 30
I 30
D 36
	if (debug == 0)
E 36
I 36
	if (debug == 0) {
E 36
		daemon(0, 0);
E 30
D 15
	(void) open("/", O_RDONLY);
	(void) dup2(0, 1);
	(void) dup2(0, 2);
	{ int tt = open("/dev/tty", O_RDWR);
	  if (tt > 0) {
D 10
		ioctl(tt, TIOCNOTTY, 0);
E 10
I 10
		ioctl(tt, TIOCNOTTY, (char *)0);
E 10
		close(tt);
	  }
	}
I 14
	(void) setpgrp(0, 0);
E 14
#endif
E 15
I 2
D 7
	openlog("inetd", LOG_PID, 0);
E 7
I 7
D 11
	openlog("inetd", LOG_PID, LOG_DAEMON);
E 11
I 11
D 36
	openlog("inetd", LOG_PID | LOG_NOWAIT, LOG_DAEMON);
	bzero((char *)&sv, sizeof(sv));
E 36
I 36
	}
D 40
	bzero(&sv, sizeof(sv));
E 40
I 40
	memset(&sv, 0, sizeof(sv));
E 40
E 36
	sv.sv_mask = SIGBLOCK;
	sv.sv_handler = retry;
	sigvec(SIGALRM, &sv, (struct sigvec *)0);
E 11
E 7
E 2
D 40
	config();
E 40
I 40
	config(SIGHUP);
E 40
D 11
	signal(SIGHUP, config);
	signal(SIGCHLD, reapchild);
E 11
I 11
	sv.sv_handler = config;
	sigvec(SIGHUP, &sv, (struct sigvec *)0);
	sv.sv_handler = reapchild;
	sigvec(SIGCHLD, &sv, (struct sigvec *)0);

I 19
	{
		/* space for daemons to overwrite environment for ps */
#define	DUMMYSIZE	100
		char dummy[DUMMYSIZE];

		(void)memset(dummy, 'x', sizeof(DUMMYSIZE) - 1);
		dummy[DUMMYSIZE - 1] = '\0';
		(void)setenv("inetd_dummy", dummy, 1);
	}

E 19
E 11
	for (;;) {
D 8
		int readable, s, ctrl;
E 8
I 8
D 11
		int s, ctrl, n;
		fd_set readable;
E 11
I 11
D 19
	    int s, ctrl, n;
E 19
I 19
	    int n, ctrl;
E 19
	    fd_set readable;
E 11
E 8

D 8
		while (allsock == 0)
E 8
I 8
D 11
		while (nsock == 0)
E 8
			sigpause(0);
		readable = allsock;
D 8
		if (select(32, &readable, 0, 0, 0) <= 0)
E 8
I 8
D 10
		if ((n = select(maxsock + 1, &readable, 0, 0, 0)) <= 0)
E 10
I 10
		if ((n = select(maxsock + 1, &readable, (fd_set *)0,
		    (fd_set *)0, (struct timeval *)0)) <= 0)
E 10
E 8
			continue;
D 8
		s = ffs(readable)-1;
		if (s < 0)
			continue;
E 8
I 8
		for (s = 0; s <= maxsock; s++)
			if (FD_ISSET(s, &readable))
				break;
E 8
		for (sep = servtab; sep; sep = sep->se_next)
			if (s == sep->se_fd)
				goto found;
D 10
		abort(1);
E 10
I 10
		abort();
E 10
	found:
E 11
I 11
D 13
	    while (nsock == 0)
E 13
I 13
	    if (nsock == 0) {
		(void) sigblock(SIGBLOCK);
		while (nsock == 0)
E 13
D 14
		    sigpause(0);
I 13
		(void) sigsetmask(0);
E 14
I 14
		    sigpause(0L);
		(void) sigsetmask(0L);
E 14
	    }
E 13
	    readable = allsock;
	    if ((n = select(maxsock + 1, &readable, (fd_set *)0,
		(fd_set *)0, (struct timeval *)0)) <= 0) {
		    if (n < 0 && errno != EINTR)
D 13
				syslog(LOG_WARNING, "select: %m\n");
E 13
I 13
D 36
			syslog(LOG_WARNING, "select: %m\n");
E 36
I 36
			syslog(LOG_WARNING, "select: %m");
E 36
E 13
		    sleep(1);
		    continue;
	    }
	    for (sep = servtab; n && sep; sep = sep->se_next)
D 32
	    if (FD_ISSET(sep->se_fd, &readable)) {
		n--;
E 11
		if (debug)
			fprintf(stderr, "someone wants %s\n", sep->se_service);
D 8
		if (sep->se_socktype == SOCK_STREAM) {
E 8
I 8
D 29
		if (!sep->se_wait && sep->se_socktype == SOCK_STREAM) {
E 29
I 29
		if (sep->se_socktype == SOCK_STREAM) {
E 29
E 8
D 10
			ctrl = accept(s, 0, 0);
E 10
I 10
D 11
			ctrl = accept(s, (struct sockaddr *)0, (int *)0);
E 11
I 11
			ctrl = accept(sep->se_fd, (struct sockaddr *)0,
			    (int *)0);
E 11
E 10
D 2
		if (debug)
			fprintf(stderr, "accept, ctrl %d\n", ctrl);
E 2
I 2
			if (debug)
				fprintf(stderr, "accept, ctrl %d\n", ctrl);
E 2
			if (ctrl < 0) {
				if (errno == EINTR)
					continue;
D 2
				perror("inetd: accept");
E 2
I 2
D 29
				syslog(LOG_WARNING, "accept: %m");
E 29
I 29
				syslog(LOG_WARNING, "accept (for %s): %m",
					sep->se_service);
E 29
E 2
				continue;
			}
		} else
			ctrl = sep->se_fd;
D 8
#define mask(sig)	(1 << (sig - 1))
		sigblock(mask(SIGCHLD)|mask(SIGHUP));
E 8
I 8
D 10
		sigblock(sigmask(SIGCHLD)|sigmask(SIGHUP));
E 10
I 10
D 11
		(void) sigblock(sigmask(SIGCHLD)|sigmask(SIGHUP));
E 11
I 11
		(void) sigblock(SIGBLOCK);
E 11
E 10
E 8
D 9
		pid = fork();
E 9
I 9
		pid = 0;
D 11
		if (sep->se_bi == 0 || sep->se_bi->bi_fork)
E 11
I 11
		dofork = (sep->se_bi == 0 || sep->se_bi->bi_fork);
		if (dofork) {
			if (sep->se_count++ == 0)
			    (void)gettimeofday(&sep->se_time,
			        (struct timezone *)0);
			else if (sep->se_count >= TOOMANY) {
E 32
I 32
	        if (sep->se_fd != -1 && FD_ISSET(sep->se_fd, &readable)) {
		    n--;
		    if (debug)
			    fprintf(stderr, "someone wants %s\n",
				sep->se_service);
D 42
		    if (sep->se_socktype == SOCK_STREAM) {
E 42
I 42
		    if (!sep->se_wait && sep->se_socktype == SOCK_STREAM) {
E 42
			    ctrl = accept(sep->se_fd, (struct sockaddr *)0,
				(int *)0);
			    if (debug)
				    fprintf(stderr, "accept, ctrl %d\n", ctrl);
			    if (ctrl < 0) {
D 36
				    if (errno == EINTR)
					    continue;
				    syslog(LOG_WARNING, "accept (for %s): %m",
					    sep->se_service);
E 36
I 36
				    if (errno != EINTR)
					    syslog(LOG_WARNING,
						"accept (for %s): %m",
						sep->se_service);
E 36
				    continue;
			    }
I 36
			    /*
			     * Call tcpmux to find the real service to exec.
			     */
			    if (sep->se_bi &&
D 40
				sep->se_bi->bi_fn == (int (*)()) tcpmux) {
E 40
I 40
				sep->se_bi->bi_fn == (void (*)()) tcpmux) {
E 40
				    sep = tcpmux(ctrl);
				    if (sep == NULL) {
					    close(ctrl);
					    continue;
				    }
			    }
E 36
		    } else
			    ctrl = sep->se_fd;
		    (void) sigblock(SIGBLOCK);
		    pid = 0;
		    dofork = (sep->se_bi == 0 || sep->se_bi->bi_fork);
		    if (dofork) {
			    if (sep->se_count++ == 0)
				(void)gettimeofday(&sep->se_time,
				    (struct timezone *)0);
D 36
			    else if (sep->se_count >= TOOMANY) {
E 36
I 36
			    else if (sep->se_count >= toomany) {
E 36
E 32
				struct timeval now;

				(void)gettimeofday(&now, (struct timezone *)0);
				if (now.tv_sec - sep->se_time.tv_sec >
				    CNT_INTVL) {
					sep->se_time = now;
					sep->se_count = 1;
				} else {
					syslog(LOG_ERR,
D 36
			"%s/%s server failing (looping), service terminated\n",
E 36
I 36
			"%s/%s server failing (looping), service terminated",
E 36
					    sep->se_service, sep->se_proto);
D 36
					FD_CLR(sep->se_fd, &allsock);
					(void) close(sep->se_fd);
					sep->se_fd = -1;
					sep->se_count = 0;
					nsock--;
E 36
I 36
					close_sep(sep);
					sigsetmask(0L);
E 36
D 14
					sigsetmask(0);
E 14
I 14
D 34
					sigsetmask(0L);
E 34
E 14
					if (!timingout) {
						timingout = 1;
						alarm(RETRYTIME);
					}
I 36
					continue;
E 36
D 34
					continue;
E 34
				}
D 32
			}
E 11
			pid = fork();
I 11
		}
E 11
E 9
		if (pid < 0) {
D 8
			if (sep->se_socktype == SOCK_STREAM)
E 8
I 8
D 29
			if (!sep->se_wait && sep->se_socktype == SOCK_STREAM)
E 29
I 29
			if (sep->se_socktype == SOCK_STREAM)
E 29
E 8
				close(ctrl);
I 11
D 14
			sigsetmask(0);
E 14
I 14
			sigsetmask(0L);
E 14
E 11
			sleep(1);
			continue;
		}
D 11
		if (sep->se_wait) {
E 11
I 11
		if (pid && sep->se_wait) {
E 11
			sep->se_wait = pid;
D 8
			allsock &= ~(1 << s);
E 8
I 8
D 11
			FD_CLR(s, &allsock);
E 11
I 11
			FD_CLR(sep->se_fd, &allsock);
E 11
			nsock--;
E 8
		}
D 14
		sigsetmask(0);
E 14
I 14
		sigsetmask(0L);
E 14
		if (pid == 0) {
D 15
#ifdef	DEBUG
D 11
			int tt = open("/dev/tty", O_RDWR);
			if (tt > 0) {
E 11
I 11
			int tt;
E 15
I 15
D 30
			if (debug) {
D 19
			    int tt;
E 15

D 15
			if (dofork && (tt = open("/dev/tty", O_RDWR)) > 0) {
E 15
I 15
			    if (dofork && (tt = open("/dev/tty", O_RDWR)) > 0) {
E 15
E 11
				ioctl(tt, TIOCNOTTY, 0);
				close(tt);
I 15
			    }
			    (void) setpgrp(0, 0);
			    signal(SIGTSTP, SIG_IGN);
			    signal(SIGTTIN, SIG_IGN);
			    signal(SIGTTOU, SIG_IGN);
E 19
I 19
				if (dofork &&
D 21
				    (tmpint = open("/dev/tty", O_RDWR)) > 0) {
E 21
I 21
				    (tmpint = open(_PATH_TTY, O_RDWR)) > 0) {
E 21
					ioctl(tmpint, TIOCNOTTY, 0);
					close(tmpint);
				}
				(void) setpgrp(0, 0);
				(void) signal(SIGTSTP, SIG_IGN);
				(void) signal(SIGTTIN, SIG_IGN);
				(void) signal(SIGTTOU, SIG_IGN);
E 19
E 15
			}
E 30
I 30
			if (debug && dofork)
E 32
I 32
			    }
			    pid = fork();
		    }
		    if (pid < 0) {
			    syslog(LOG_ERR, "fork: %m");
D 42
			    if (sep->se_socktype == SOCK_STREAM)
E 42
I 42
			    if (!sep->se_wait &&
				sep->se_socktype == SOCK_STREAM)
E 42
				    close(ctrl);
			    sigsetmask(0L);
			    sleep(1);
			    continue;
		    }
		    if (pid && sep->se_wait) {
			    sep->se_wait = pid;
D 34
			    FD_CLR(sep->se_fd, &allsock);
			    nsock--;
E 34
I 34
			    if (sep->se_fd >= 0) {
				FD_CLR(sep->se_fd, &allsock);
			        nsock--;
			    }
E 34
		    }
		    sigsetmask(0L);
		    if (pid == 0) {
			    if (debug && dofork)
E 32
				setsid();
E 30
D 15
#endif
E 15
D 8
			dup2(ctrl, 0), close(ctrl), dup2(0, 1);
E 8
I 8
D 9
			dup2(ctrl, 0); close(ctrl); dup2(0, 1); dup2(0, 2);
E 8
			for (i = getdtablesize(); --i > 2; )
				close(i);
I 5
			if ((pwd = getpwnam(sep->se_user)) == NULL) {
				syslog(LOG_ERR, "getpwnam: %s: No such user"
					,sep->se_user);
				exit(1);
E 9
I 9
D 11
			if (sep->se_bi == 0 || sep->se_bi->bi_fork)
E 11
I 11
D 32
			if (dofork)
E 32
I 32
D 36
			    if (dofork)
E 32
E 11
D 19
				for (i = getdtablesize(); --i > 2; )
					if (i != ctrl)
						close(i);
E 19
I 19
D 33
				for (tmpint = getdtablesize(); --tmpint > 2; )
E 33
I 33
				for (tmpint = maxsock; --tmpint > 2; )
E 36
I 36
			    if (dofork) {
				if (debug)
					fprintf(stderr, "+ Closing from %d\n",
						maxsock);
				for (tmpint = maxsock; tmpint > 2; tmpint--)
E 36
E 33
					if (tmpint != ctrl)
						close(tmpint);
I 36
			    }
E 36
E 19
D 32
			if (sep->se_bi)
E 32
I 32
			    if (sep->se_bi)
E 32
				(*sep->se_bi->bi_fn)(ctrl, sep);
D 32
			else {
E 32
I 32
			    else {
				if (debug)
					fprintf(stderr, "%d execl %s\n",
					    getpid(), sep->se_server);
E 32
				dup2(ctrl, 0);
				close(ctrl);
				dup2(0, 1);
				dup2(0, 2);
				if ((pwd = getpwnam(sep->se_user)) == NULL) {
					syslog(LOG_ERR,
D 32
						"getpwnam: %s: No such user",
						sep->se_user);
E 32
I 32
D 36
					    "getpwnam: %s: No such user",
					    sep->se_user);
E 36
I 36
					    "%s/%s: %s: No such user",
						sep->se_service, sep->se_proto,
						sep->se_user);
E 36
E 32
I 11
					if (sep->se_socktype != SOCK_STREAM)
						recv(0, buf, sizeof (buf), 0);
E 11
					_exit(1);
				}
				if (pwd->pw_uid) {
D 10
					(void) setgid(pwd->pw_gid);
E 10
I 10
D 36
					(void) setgid((gid_t)pwd->pw_gid);
E 10
					initgroups(pwd->pw_name, pwd->pw_gid);
D 10
					(void) setuid(pwd->pw_uid);
E 10
I 10
					(void) setuid((uid_t)pwd->pw_uid);
E 36
I 36
					if (setgid(pwd->pw_gid) < 0) {
						syslog(LOG_ERR,
						  "%s: can't set gid %d: %m", 
						  sep->se_service, pwd->pw_gid);
						_exit(1);
					}
					(void) initgroups(pwd->pw_name,
							pwd->pw_gid);
					if (setuid(pwd->pw_uid) < 0) {
						syslog(LOG_ERR,
						  "%s: can't set uid %d: %m", 
						  sep->se_service, pwd->pw_uid);
						_exit(1);
					}
E 36
E 10
				}
D 32
				if (debug)
					fprintf(stderr, "%d execl %s\n",
					    getpid(), sep->se_server);
E 32
				execv(sep->se_server, sep->se_argv);
				if (sep->se_socktype != SOCK_STREAM)
					recv(0, buf, sizeof (buf), 0);
D 36
				syslog(LOG_ERR, "execv %s: %m", sep->se_server);
E 36
I 36
				syslog(LOG_ERR,
				    "cannot execute %s: %m", sep->se_server);
E 36
				_exit(1);
E 9
D 32
			}
E 32
I 32
			    }
		    }
D 42
		    if (sep->se_socktype == SOCK_STREAM)
E 42
I 42
		    if (!sep->se_wait && sep->se_socktype == SOCK_STREAM)
E 42
			    close(ctrl);
E 32
D 9
			(void) setgid(pwd->pw_gid);
			initgroups(pwd->pw_name, pwd->pw_gid);
			(void) setuid(pwd->pw_uid);
E 5
			if (debug)
				fprintf(stderr, "%d execl %s\n",
				    getpid(), sep->se_server);
			execv(sep->se_server, sep->se_argv);
			if (sep->se_socktype != SOCK_STREAM)
D 2
				recv(0, buf, sizeof (buf));
			if (debug)
				fprintf(stderr, "execl failed\n");
E 2
I 2
				recv(0, buf, sizeof (buf), 0);
			syslog(LOG_ERR, "execv %s: %m", sep->se_server);
E 2
			_exit(1);
E 9
		}
D 8
		if (sep->se_socktype == SOCK_STREAM)
E 8
I 8
D 29
		if (!sep->se_wait && sep->se_socktype == SOCK_STREAM)
E 29
I 29
D 32
		if (sep->se_socktype == SOCK_STREAM)
E 29
E 8
			close(ctrl);
I 11
	    }
E 32
E 11
	}
}

I 23
void
E 23
D 40
reapchild()
E 40
I 40
reapchild(signo)
	int signo;
E 40
{
D 32
	union wait status;
E 32
I 32
	int status;
E 32
D 40
	int pid;
	register struct servtab *sep;
E 40
I 40
	pid_t pid;
	struct servtab *sep;
E 40

	for (;;) {
D 10
		pid = wait3(&status, WNOHANG, 0);
E 10
I 10
D 31
		pid = wait3(&status, WNOHANG, (struct rusage *)0);
E 31
I 31
D 32
		pid = wait3((int *)&status, WNOHANG, (struct rusage *)0);
E 32
I 32
		pid = wait3(&status, WNOHANG, (struct rusage *)0);
E 32
E 31
E 10
		if (pid <= 0)
			break;
		if (debug)
D 36
			fprintf(stderr, "%d reaped\n", pid);
E 36
I 36
			fprintf(stderr, "%d reaped, status %#x\n", 
				pid, status);
E 36
		for (sep = servtab; sep; sep = sep->se_next)
			if (sep->se_wait == pid) {
D 32
				if (status.w_status)
E 32
I 32
				if (status)
E 32
D 2
					fprintf(stderr,
					    "inetd: %s: exit status %d\n",
E 2
I 2
					syslog(LOG_WARNING,
					    "%s: exit status 0x%x",
E 2
					    sep->se_server, status);
				if (debug)
					fprintf(stderr, "restored %s, fd %d\n",
					    sep->se_service, sep->se_fd);
D 8
				allsock |= 1 << sep->se_fd;
E 8
I 8
				FD_SET(sep->se_fd, &allsock);
				nsock++;
E 8
				sep->se_wait = 1;
			}
	}
}

I 23
void
E 23
D 40
config()
E 40
I 40
config(signo)
	int signo;
E 40
{
D 40
	register struct servtab *sep, *cp, **sepp;
	struct servtab *getconfigent(), *enter();
E 40
I 40
	struct servtab *sep, *cp, **sepp;
E 40
I 36
	struct passwd *pwd;
E 36
D 3
	int omask;
E 3
I 3
D 11
	int omask, on = 1;
E 11
I 11
D 14
	int omask;
E 14
I 14
	long omask;
E 14
E 11
E 3

	if (!setconfig()) {
D 2
		fprintf(stderr, "inetd: ");
		perror(CONFIG);
E 2
I 2
		syslog(LOG_ERR, "%s: %m", CONFIG);
E 2
		return;
	}
	for (sep = servtab; sep; sep = sep->se_next)
		sep->se_checked = 0;
	while (cp = getconfigent()) {
I 36
		if ((pwd = getpwnam(cp->se_user)) == NULL) {
			syslog(LOG_ERR,
				"%s/%s: No such user '%s', service ignored",
				cp->se_service, cp->se_proto, cp->se_user);
			continue;
		}
E 36
		for (sep = servtab; sep; sep = sep->se_next)
			if (strcmp(sep->se_service, cp->se_service) == 0 &&
			    strcmp(sep->se_proto, cp->se_proto) == 0)
				break;
		if (sep != 0) {
			int i;

D 8
			omask = sigblock(mask(SIGCHLD));
E 8
I 8
D 11
			omask = sigblock(sigmask(SIGCHLD));
E 8
			sep->se_wait = cp->se_wait;
E 11
I 11
			omask = sigblock(SIGBLOCK);
D 25
			if (cp->se_bi == 0)
E 25
I 25
			/*
			 * sep->se_wait may be holding the pid of a daemon
			 * that we're waiting for.  If so, don't overwrite
			 * it unless the config file explicitly says don't 
			 * wait.
			 */
			if (cp->se_bi == 0 && 
			    (sep->se_wait == 1 || cp->se_wait == 0))
E 25
				sep->se_wait = cp->se_wait;
E 11
#define SWAP(a, b) { char *c = a; a = b; b = c; }
I 10
			if (cp->se_user)
				SWAP(sep->se_user, cp->se_user);
E 10
			if (cp->se_server)
				SWAP(sep->se_server, cp->se_server);
			for (i = 0; i < MAXARGV; i++)
				SWAP(sep->se_argv[i], cp->se_argv[i]);
			sigsetmask(omask);
			freeconfig(cp);
D 12
		} else
E 12
I 12
			if (debug)
				print_service("REDO", sep);
		} else {
E 12
			sep = enter(cp);
I 12
			if (debug)
				print_service("ADD ", sep);
		}
E 12
		sep->se_checked = 1;
I 36
		if (ISMUX(sep)) {
			sep->se_fd = -1;
			continue;
		}
E 36
D 11
		if (sep->se_fd != -1)
			continue;
E 11
		sp = getservbyname(sep->se_service, sep->se_proto);
		if (sp == 0) {
D 2
			fprintf(stderr,
			    "inetd: %s/%s: unknown service\n",
E 2
I 2
			syslog(LOG_ERR, "%s/%s: unknown service",
E 2
			    sep->se_service, sep->se_proto);
I 32
D 36
			if (sep->se_fd != -1)
				(void) close(sep->se_fd);
			sep->se_fd = -1;
E 36
I 36
			sep->se_checked = 0;
E 36
E 32
			continue;
		}
D 11
		sep->se_ctrladdr.sin_port = sp->s_port;
		if ((sep->se_fd = socket(AF_INET, sep->se_socktype, 0)) < 0) {
D 2
			fprintf(stderr, "inetd: %s/%s: ",
E 2
I 2
			syslog(LOG_ERR, "%s/%s: socket: %m",
E 2
			    sep->se_service, sep->se_proto);
D 2
			perror("socket");
E 2
			continue;
E 11
I 11
		if (sp->s_port != sep->se_ctrladdr.sin_port) {
I 38
			sep->se_ctrladdr.sin_family = AF_INET;
E 38
			sep->se_ctrladdr.sin_port = sp->s_port;
D 36
			if (sep->se_fd != -1)
				(void) close(sep->se_fd);
			sep->se_fd = -1;
E 36
I 36
			if (sep->se_fd >= 0)
				close_sep(sep);
E 36
E 11
		}
I 3
D 11
#define	turnon(fd, opt) \
D 10
	setsockopt(fd, SOL_SOCKET, opt, &on, sizeof (on))
E 10
I 10
	setsockopt(fd, SOL_SOCKET, opt, (char *)&on, sizeof (on))
E 10
E 3
		if (strcmp(sep->se_proto, "tcp") == 0 && (options & SO_DEBUG) &&
D 3
		    setsockopt(sep->se_fd, SOL_SOCKET, SO_DEBUG, 0, 0) < 0)
E 3
I 3
		    turnon(sep->se_fd, SO_DEBUG) < 0)
E 3
D 2
			perror("inetd: setsockopt (SO_DEBUG)");
E 2
I 2
			syslog(LOG_ERR, "setsockopt (SO_DEBUG): %m");
E 2
D 3
		if (setsockopt(sep->se_fd, SOL_SOCKET, SO_REUSEADDR, 0, 0) < 0)
E 3
I 3
		if (turnon(sep->se_fd, SO_REUSEADDR) < 0)
E 3
D 2
			perror("inetd: setsockopt (SO_REUSEADDR)");
E 2
I 2
			syslog(LOG_ERR, "setsockopt (SO_REUSEADDR): %m");
I 3
#undef turnon
E 3
E 2
		if (bind(sep->se_fd, &sep->se_ctrladdr,
D 10
		    sizeof (sep->se_ctrladdr), 0) < 0) {
E 10
I 10
		    sizeof (sep->se_ctrladdr)) < 0) {
E 10
D 2
			fprintf(stderr, "inetd: %s/%s: ",
E 2
I 2
			syslog(LOG_ERR, "%s/%s: bind: %m",
E 2
			    sep->se_service, sep->se_proto);
D 2
			perror("bind");
E 2
			continue;
		}
		if (sep->se_socktype == SOCK_STREAM)
			listen(sep->se_fd, 10);
D 8
		allsock |= 1 << sep->se_fd;
E 8
I 8
		FD_SET(sep->se_fd, &allsock);
		nsock++;
		if (sep->se_fd > maxsock)
			maxsock = sep->se_fd;
E 11
I 11
		if (sep->se_fd == -1)
			setup(sep);
E 11
E 8
	}
	endconfig();
	/*
	 * Purge anything not looked at above.
	 */
D 8
	omask = sigblock(mask(SIGCHLD));
E 8
I 8
D 11
	omask = sigblock(sigmask(SIGCHLD));
E 11
I 11
	omask = sigblock(SIGBLOCK);
E 11
E 8
	sepp = &servtab;
	while (sep = *sepp) {
		if (sep->se_checked) {
			sepp = &sep->se_next;
			continue;
		}
		*sepp = sep->se_next;
D 36
		if (sep->se_fd != -1) {
D 8
			allsock &= ~(1 << sep->se_fd);
E 8
I 8
			FD_CLR(sep->se_fd, &allsock);
			nsock--;
E 8
			(void) close(sep->se_fd);
		}
E 36
I 36
		if (sep->se_fd >= 0)
			close_sep(sep);
E 36
I 12
		if (debug)
			print_service("FREE", sep);
E 12
		freeconfig(sep);
		free((char *)sep);
	}
	(void) sigsetmask(omask);
}

I 23
void
E 23
I 11
D 40
retry()
E 40
I 40
retry(signo)
	int signo;
E 40
{
D 40
	register struct servtab *sep;
E 40
I 40
	struct servtab *sep;
E 40

	timingout = 0;
	for (sep = servtab; sep; sep = sep->se_next)
		if (sep->se_fd == -1)
			setup(sep);
}

I 40
void
E 40
setup(sep)
D 40
	register struct servtab *sep;
E 40
I 40
	struct servtab *sep;
E 40
{
	int on = 1;

	if ((sep->se_fd = socket(AF_INET, sep->se_socktype, 0)) < 0) {
I 36
		if (debug)
			fprintf(stderr, "socket failed on %s/%s: %s\n", 
				sep->se_service, sep->se_proto,
				strerror(errno));
E 36
		syslog(LOG_ERR, "%s/%s: socket: %m",
		    sep->se_service, sep->se_proto);
		return;
	}
#define	turnon(fd, opt) \
setsockopt(fd, SOL_SOCKET, opt, (char *)&on, sizeof (on))
	if (strcmp(sep->se_proto, "tcp") == 0 && (options & SO_DEBUG) &&
	    turnon(sep->se_fd, SO_DEBUG) < 0)
		syslog(LOG_ERR, "setsockopt (SO_DEBUG): %m");
	if (turnon(sep->se_fd, SO_REUSEADDR) < 0)
		syslog(LOG_ERR, "setsockopt (SO_REUSEADDR): %m");
#undef turnon
D 31
	if (bind(sep->se_fd, &sep->se_ctrladdr,
E 31
I 31
	if (bind(sep->se_fd, (struct sockaddr *)&sep->se_ctrladdr,
E 31
	    sizeof (sep->se_ctrladdr)) < 0) {
I 36
		if (debug)
			fprintf(stderr, "bind failed on %s/%s: %s\n",
				sep->se_service, sep->se_proto,
				strerror(errno));
E 36
		syslog(LOG_ERR, "%s/%s: bind: %m",
		    sep->se_service, sep->se_proto);
		(void) close(sep->se_fd);
		sep->se_fd = -1;
		if (!timingout) {
			timingout = 1;
			alarm(RETRYTIME);
		}
		return;
	}
	if (sep->se_socktype == SOCK_STREAM)
		listen(sep->se_fd, 10);
	FD_SET(sep->se_fd, &allsock);
	nsock++;
	if (sep->se_fd > maxsock)
		maxsock = sep->se_fd;
I 36
	if (debug) {
		fprintf(stderr, "registered %s on %d\n",
			sep->se_server, sep->se_fd);
	}
E 36
}

I 36
/*
 * Finish with a service and its socket.
 */
I 40
void
E 40
close_sep(sep)
D 40
	register struct servtab *sep;
E 40
I 40
	struct servtab *sep;
E 40
{
	if (sep->se_fd >= 0) {
		nsock--;
		FD_CLR(sep->se_fd, &allsock);
		(void) close(sep->se_fd);
		sep->se_fd = -1;
	}
	sep->se_count = 0;
	/*
	 * Don't keep the pid of this running deamon: when reapchild()
	 * reaps this pid, it would erroneously increment nsock.
	 */
	if (sep->se_wait > 1)
		sep->se_wait = 1;
}

E 36
E 11
struct servtab *
enter(cp)
	struct servtab *cp;
{
D 40
	register struct servtab *sep;
E 40
I 40
	struct servtab *sep;
E 40
D 8
	int omask, i;
E 8
I 8
D 14
	int omask;
E 14
I 14
	long omask;
E 14
E 8
D 17
	char *strdup();
E 17

	sep = (struct servtab *)malloc(sizeof (*sep));
	if (sep == (struct servtab *)0) {
D 2
		fprintf(stderr, "Out of memory.\n");
E 2
I 2
		syslog(LOG_ERR, "Out of memory.");
E 2
		exit(-1);
	}
	*sep = *cp;
	sep->se_fd = -1;
D 8
	omask = sigblock(mask(SIGCHLD));
E 8
I 8
D 11
	omask = sigblock(sigmask(SIGCHLD));
E 11
I 11
	omask = sigblock(SIGBLOCK);
E 11
E 8
	sep->se_next = servtab;
	servtab = sep;
	sigsetmask(omask);
	return (sep);
}

FILE	*fconfig = NULL;
struct	servtab serv;
D 40
char	line[256];
D 36
char	*skip(), *nextline();
E 36
I 36
char	*sskip(), *skip(), *nextline();
E 40
I 40
char	line[LINE_MAX];
E 40
E 36

I 40
int
E 40
setconfig()
{

	if (fconfig != NULL) {
D 10
		fseek(fconfig, 0, L_SET);
E 10
I 10
D 36
		fseek(fconfig, 0L, L_SET);
E 36
I 36
		fseek(fconfig, 0L, SEEK_SET);
E 36
E 10
		return (1);
	}
	fconfig = fopen(CONFIG, "r");
	return (fconfig != NULL);
}

I 40
void
E 40
endconfig()
{
D 19

	if (fconfig == NULL)
		return;
	fclose(fconfig);
	fconfig = NULL;
E 19
I 19
	if (fconfig) {
		(void) fclose(fconfig);
		fconfig = NULL;
	}
E 19
}

struct servtab *
getconfigent()
{
D 40
	register struct servtab *sep = &serv;
E 40
I 40
	struct servtab *sep = &serv;
E 40
D 17
	char *cp, *arg;
E 17
	int argc;
I 17
D 31
	char *cp, *arg, *strdup();
E 31
I 31
D 40
	char *cp, *arg, *newstr();
E 40
I 40
	char *cp, *arg;
E 40
I 36
	static char TCPMUX_TOKEN[] = "tcpmux/";
#define MUX_LEN		(sizeof(TCPMUX_TOKEN)-1)
E 36
E 31
E 17

I 9
more:
E 9
D 36
	while ((cp = nextline(fconfig)) && *cp == '#')
E 36
I 36
	while ((cp = nextline(fconfig)) && (*cp == '#' || *cp == '\0'))
E 36
		;
	if (cp == NULL)
		return ((struct servtab *)0);
D 31
	sep->se_service = strdup(skip(&cp));
E 31
I 31
D 36
	sep->se_service = newstr(skip(&cp));
E 36
I 36
	/*
	 * clear the static buffer, since some fields (se_ctrladdr,
	 * for example) don't get initialized here.
	 */
D 40
	bzero((caddr_t)sep, sizeof *sep);
E 40
I 40
	memset((caddr_t)sep, 0, sizeof *sep);
E 40
E 36
E 31
	arg = skip(&cp);
I 36
	if (cp == NULL) {
		/* got an empty line containing just blanks/tabs. */
		goto more;
	}
	if (strncmp(arg, TCPMUX_TOKEN, MUX_LEN) == 0) {
		char *c = arg + MUX_LEN;
		if (*c == '+') {
			sep->se_type = MUXPLUS_TYPE;
			c++;
		} else
			sep->se_type = MUX_TYPE;
		sep->se_service = newstr(c);
	} else {
		sep->se_service = newstr(arg);
		sep->se_type = NORM_TYPE;
	}
	arg = sskip(&cp);
E 36
	if (strcmp(arg, "stream") == 0)
		sep->se_socktype = SOCK_STREAM;
	else if (strcmp(arg, "dgram") == 0)
		sep->se_socktype = SOCK_DGRAM;
	else if (strcmp(arg, "rdm") == 0)
		sep->se_socktype = SOCK_RDM;
	else if (strcmp(arg, "seqpacket") == 0)
		sep->se_socktype = SOCK_SEQPACKET;
	else if (strcmp(arg, "raw") == 0)
		sep->se_socktype = SOCK_RAW;
	else
		sep->se_socktype = -1;
D 31
	sep->se_proto = strdup(skip(&cp));
E 31
I 31
D 36
	sep->se_proto = newstr(skip(&cp));
E 31
	arg = skip(&cp);
E 36
I 36
	sep->se_proto = newstr(sskip(&cp));
	arg = sskip(&cp);
E 36
	sep->se_wait = strcmp(arg, "wait") == 0;
I 5
D 31
	sep->se_user = strdup(skip(&cp));
E 5
	sep->se_server = strdup(skip(&cp));
E 31
I 31
D 36
	sep->se_user = newstr(skip(&cp));
	sep->se_server = newstr(skip(&cp));
E 36
I 36
	if (ISMUX(sep)) {
		/*
		 * Silently enforce "nowait" for TCPMUX services since
		 * they don't have an assigned port to listen on.
		 */
		sep->se_wait = 0;

		if (strcmp(sep->se_proto, "tcp")) {
			syslog(LOG_ERR, 
				"%s: bad protocol for tcpmux service %s",
				CONFIG, sep->se_service);
			goto more;
		}
		if (sep->se_socktype != SOCK_STREAM) {
			syslog(LOG_ERR, 
				"%s: bad socket type for tcpmux service %s",
				CONFIG, sep->se_service);
			goto more;
		}
	}
	sep->se_user = newstr(sskip(&cp));
	sep->se_server = newstr(sskip(&cp));
E 36
E 31
I 9
	if (strcmp(sep->se_server, "internal") == 0) {
D 40
		register struct biltin *bi;
E 40
I 40
		struct biltin *bi;
E 40

		for (bi = biltins; bi->bi_service; bi++)
			if (bi->bi_socktype == sep->se_socktype &&
			    strcmp(bi->bi_service, sep->se_service) == 0)
				break;
		if (bi->bi_service == 0) {
D 36
			syslog(LOG_ERR, "internal service %s unknown\n",
E 36
I 36
			syslog(LOG_ERR, "internal service %s unknown",
E 36
				sep->se_service);
			goto more;
		}
		sep->se_bi = bi;
		sep->se_wait = bi->bi_wait;
D 12
	}
E 12
I 12
	} else
		sep->se_bi = NULL;
E 12
E 9
	argc = 0;
	for (arg = skip(&cp); cp; arg = skip(&cp))
		if (argc < MAXARGV)
D 31
			sep->se_argv[argc++] = strdup(arg);
E 31
I 31
			sep->se_argv[argc++] = newstr(arg);
E 31
	while (argc <= MAXARGV)
		sep->se_argv[argc++] = NULL;
	return (sep);
}

I 40
void
E 40
freeconfig(cp)
D 40
	register struct servtab *cp;
E 40
I 40
	struct servtab *cp;
E 40
{
	int i;

	if (cp->se_service)
		free(cp->se_service);
	if (cp->se_proto)
		free(cp->se_proto);
I 10
	if (cp->se_user)
		free(cp->se_user);
E 10
	if (cp->se_server)
		free(cp->se_server);
	for (i = 0; i < MAXARGV; i++)
		if (cp->se_argv[i])
			free(cp->se_argv[i]);
}

I 36

/*
 * Safe skip - if skip returns null, log a syntax error in the
 * configuration file and exit.
 */
E 36
char *
I 36
sskip(cpp)
	char **cpp;
{
D 40
	register char *cp;
E 40
I 40
	char *cp;
E 40

	cp = skip(cpp);
	if (cp == NULL) {
		syslog(LOG_ERR, "%s: syntax error", CONFIG);
		exit(-1);
	}
	return (cp);
}

char *
E 36
skip(cpp)
	char **cpp;
{
D 40
	register char *cp = *cpp;
E 40
I 40
	char *cp = *cpp;
E 40
	char *start;

again:
	while (*cp == ' ' || *cp == '\t')
		cp++;
	if (*cp == '\0') {
D 28
		char c;
E 28
I 28
		int c;
E 28

		c = getc(fconfig);
D 19
		ungetc(c, fconfig);
E 19
I 19
		(void) ungetc(c, fconfig);
E 19
		if (c == ' ' || c == '\t')
			if (cp = nextline(fconfig))
				goto again;
		*cpp = (char *)0;
		return ((char *)0);
	}
	start = cp;
	while (*cp && *cp != ' ' && *cp != '\t')
		cp++;
	if (*cp != '\0')
		*cp++ = '\0';
	*cpp = cp;
	return (start);
}

char *
nextline(fd)
	FILE *fd;
{
	char *cp;

D 10
	if (fgets(line, sizeof (line), fconfig) == NULL)
E 10
I 10
	if (fgets(line, sizeof (line), fd) == NULL)
E 10
		return ((char *)0);
D 40
	cp = index(line, '\n');
E 40
I 40
	cp = strchr(line, '\n');
E 40
	if (cp)
		*cp = '\0';
	return (line);
}

char *
D 31
strdup(cp)
E 31
I 31
newstr(cp)
E 31
	char *cp;
{
D 31
	char *new;

	if (cp == NULL)
		cp = "";
D 10
	new = malloc(strlen(cp) + 1);
E 10
I 10
	new = malloc((unsigned)(strlen(cp) + 1));
E 10
	if (new == (char *)0) {
D 2
		fprintf(stderr, "Out of memory.\n");
E 2
I 2
		syslog(LOG_ERR, "Out of memory.");
E 2
		exit(-1);
	}
D 19
	strcpy(new, cp);
E 19
I 19
	(void)strcpy(new, cp);
E 19
	return (new);
E 31
I 31
D 32
	if (cp = strdup(cp))
E 32
I 32
	if (cp = strdup(cp ? cp : ""))
E 32
D 40
		return(cp);
E 40
I 40
		return (cp);
E 40
D 32
	syslog(LOG_ERR, "%m");
E 32
I 32
	syslog(LOG_ERR, "strdup: %m");
E 32
	exit(-1);
E 31
I 9
}

I 40
void
E 40
setproctitle(a, s)
	char *a;
	int s;
{
	int size;
D 40
	register char *cp;
E 40
I 40
	char *cp;
E 40
	struct sockaddr_in sin;
	char buf[80];

	cp = Argv[0];
	size = sizeof(sin);
D 31
	if (getpeername(s, &sin, &size) == 0)
E 31
I 31
	if (getpeername(s, (struct sockaddr *)&sin, &size) == 0)
E 31
D 16
		sprintf(buf, "-%s [%s]", a, inet_ntoa(sin.sin_addr)); 
E 16
I 16
		(void) sprintf(buf, "-%s [%s]", a, inet_ntoa(sin.sin_addr)); 
E 16
	else
D 16
		sprintf(buf, "-%s", a); 
E 16
I 16
		(void) sprintf(buf, "-%s", a); 
E 16
	strncpy(cp, buf, LastArg - cp);
	cp += strlen(cp);
	while (cp < LastArg)
		*cp++ = ' ';
}

/*
 * Internet services provided internally by inetd:
 */
I 22
D 35
#define	BUFSIZE	4096
E 35
I 35
#define	BUFSIZE	8192
E 35
E 22

/* ARGSUSED */
I 40
void
E 40
echo_stream(s, sep)		/* Echo service -- echo data back */
	int s;
	struct servtab *sep;
{
D 22
	char buffer[BUFSIZ];
E 22
I 22
	char buffer[BUFSIZE];
E 22
	int i;

D 13
	setproctitle("echo", s);
E 13
I 13
	setproctitle(sep->se_service, s);
E 13
	while ((i = read(s, buffer, sizeof(buffer))) > 0 &&
	    write(s, buffer, i) > 0)
		;
	exit(0);
}

/* ARGSUSED */
I 40
void
E 40
echo_dg(s, sep)			/* Echo service -- echo data back */
	int s;
	struct servtab *sep;
{
D 22
	char buffer[BUFSIZ];
E 22
I 22
	char buffer[BUFSIZE];
E 22
	int i, size;
	struct sockaddr sa;

	size = sizeof(sa);
	if ((i = recvfrom(s, buffer, sizeof(buffer), 0, &sa, &size)) < 0)
		return;
	(void) sendto(s, buffer, i, 0, &sa, sizeof(sa));
}

/* ARGSUSED */
I 40
void
E 40
discard_stream(s, sep)		/* Discard service -- ignore data */
	int s;
	struct servtab *sep;
{
I 35
	int ret;
E 35
D 22
	char buffer[BUFSIZ];
E 22
I 22
	char buffer[BUFSIZE];
E 22

D 13
	setproctitle("discard", s);
E 13
I 13
	setproctitle(sep->se_service, s);
E 13
	while (1) {
D 35
		while (read(s, buffer, sizeof(buffer)) > 0)
E 35
I 35
		while ((ret = read(s, buffer, sizeof(buffer))) > 0)
E 35
			;
D 35
		if (errno != EINTR)
E 35
I 35
		if (ret == 0 || errno != EINTR)
E 35
			break;
	}
	exit(0);
}

/* ARGSUSED */
I 40
void
E 40
discard_dg(s, sep)		/* Discard service -- ignore data */
	int s;
	struct servtab *sep;
{
D 22
	char buffer[BUFSIZ];
E 22
I 22
	char buffer[BUFSIZE];
E 22

	(void) read(s, buffer, sizeof(buffer));
}

#include <ctype.h>
#define LINESIZ 72
char ring[128];
char *endring;

I 40
void
E 40
initring()
{
D 40
	register int i;
E 40
I 40
	int i;
E 40

	endring = ring;

	for (i = 0; i <= 128; ++i)
		if (isprint(i))
			*endring++ = i;
}

/* ARGSUSED */
I 40
void
E 40
chargen_stream(s, sep)		/* Character generator */
	int s;
	struct servtab *sep;
{
I 14
D 40
	register char *rs;
E 40
	int len;
E 14
D 40
	char text[LINESIZ+2];
E 40
I 40
	char *rs, text[LINESIZ+2];
E 40
D 14
	register int i;
	register char *rp, *rs, *dp;
E 14

D 13
	setproctitle("discard", s);
E 13
I 13
	setproctitle(sep->se_service, s);
E 13
D 14
	if (endring == 0)
E 14
I 14

	if (!endring) {
E 14
		initring();
I 14
		rs = ring;
	}
E 14

D 14
	for (rs = ring; ; ++rs) {
		if (rs >= endring)
			rs = ring;
		rp = rs;
		dp = text;
		i = MIN(LINESIZ, endring - rp);
		bcopy(rp, dp, i);
		dp += i;
		if ((rp += i) >= endring)
			rp = ring;
		if (i < LINESIZ) {
			i = LINESIZ - i;
			bcopy(rp, dp, i);
			dp += i;
			if ((rp += i) >= endring)
				rp = ring;
E 14
I 14
	text[LINESIZ] = '\r';
	text[LINESIZ + 1] = '\n';
	for (rs = ring;;) {
		if ((len = endring - rs) >= LINESIZ)
D 40
			bcopy(rs, text, LINESIZ);
E 40
I 40
			memmove(text, rs, LINESIZ);
E 40
		else {
D 40
			bcopy(rs, text, len);
			bcopy(ring, text + len, LINESIZ - len);
E 40
I 40
			memmove(text, rs, len);
			memmove(text + len, ring, LINESIZ - len);
E 40
E 14
		}
D 14
		*dp++ = '\r';
		*dp++ = '\n';

		if (write(s, text, dp - text) != dp - text)
E 14
I 14
		if (++rs == endring)
			rs = ring;
		if (write(s, text, sizeof(text)) != sizeof(text))
E 14
			break;
	}
	exit(0);
}

/* ARGSUSED */
I 40
void
E 40
chargen_dg(s, sep)		/* Character generator */
	int s;
	struct servtab *sep;
{
D 14
	char text[LINESIZ+2];
	register int i;
	register char *rp;
	static char *rs = ring;
E 14
	struct sockaddr sa;
D 14
	int size;
E 14
I 14
	static char *rs;
	int len, size;
	char text[LINESIZ+2];
E 14

D 14
	if (endring == 0)
E 14
I 14
	if (endring == 0) {
E 14
		initring();
I 14
		rs = ring;
	}
E 14

	size = sizeof(sa);
	if (recvfrom(s, text, sizeof(text), 0, &sa, &size) < 0)
		return;
D 14
	rp = rs;
	if (rs++ >= endring)
		rs = ring;
	i = MIN(LINESIZ - 2, endring - rp);
	bcopy(rp, text, i);
	if ((rp += i) >= endring)
		rp = ring;
	if (i < LINESIZ - 2) {
		bcopy(rp, text, i);
		if ((rp += i) >= endring)
			rp = ring;
	}
	text[LINESIZ - 2] = '\r';
	text[LINESIZ - 1] = '\n';
E 14

I 14
	if ((len = endring - rs) >= LINESIZ)
D 40
		bcopy(rs, text, LINESIZ);
E 40
I 40
		memmove(text, rs, LINESIZ);
E 40
	else {
D 40
		bcopy(rs, text, len);
		bcopy(ring, text + len, LINESIZ - len);
E 40
I 40
		memmove(text, rs, len);
		memmove(text + len, ring, LINESIZ - len);
E 40
	}
	if (++rs == endring)
		rs = ring;
	text[LINESIZ] = '\r';
	text[LINESIZ + 1] = '\n';
E 14
	(void) sendto(s, text, sizeof(text), 0, &sa, sizeof(sa));
}

/*
 * Return a machine readable date and time, in the form of the
 * number of seconds since midnight, Jan 1, 1900.  Since gettimeofday
 * returns the number of seconds since midnight, Jan 1, 1970,
 * we must add 2208988800 seconds to this figure to make up for
 * some seventy years Bell Labs was asleep.
 */
D 10
#include <sys/time.h>
E 10

long
machtime()
{
	struct timeval tv;

D 10
	if (gettimeofday(&tv, 0) < 0) {
E 10
I 10
	if (gettimeofday(&tv, (struct timezone *)0) < 0) {
E 10
D 36
		fprintf(stderr, "Unable to get time of day\n");
E 36
I 36
		if (debug)
			fprintf(stderr, "Unable to get time of day\n");
E 36
D 10
		return;
E 10
I 10
		return (0L);
E 10
	}
D 37
	return (htonl((long)tv.tv_sec + 2208988800));
E 37
I 37
#define	OFFSET ((u_long)25567 * 24*60*60)
	return (htonl((long)(tv.tv_sec + OFFSET)));
#undef OFFSET
E 37
}

/* ARGSUSED */
I 40
void
E 40
machtime_stream(s, sep)
	int s;
	struct servtab *sep;
{
	long result;

	result = machtime();
	(void) write(s, (char *) &result, sizeof(result));
}

/* ARGSUSED */
I 40
void
E 40
machtime_dg(s, sep)
	int s;
	struct servtab *sep;
{
	long result;
	struct sockaddr sa;
	int size;

	size = sizeof(sa);
D 10
	if (recvfrom(s, &result, sizeof(result), 0, &sa, &size) < 0)
E 10
I 10
	if (recvfrom(s, (char *)&result, sizeof(result), 0, &sa, &size) < 0)
E 10
		return;
	result = machtime();
	(void) sendto(s, (char *) &result, sizeof(result), 0, &sa, sizeof(sa));
}

/* ARGSUSED */
I 40
void
E 40
daytime_stream(s, sep)		/* Return human-readable time of day */
	int s;
	struct servtab *sep;
{
	char buffer[256];
D 36
	time_t time(), clock;
	char *ctime();
E 36
I 36
	time_t clock;
E 36

	clock = time((time_t *) 0);

D 14
	sprintf(buffer, "%s\r", ctime(&clock));
E 14
I 14
D 16
	sprintf(buffer, "%.24s\r\n", ctime(&clock));
E 16
I 16
	(void) sprintf(buffer, "%.24s\r\n", ctime(&clock));
E 16
E 14
D 10
	write(s, buffer, strlen(buffer));
E 10
I 10
	(void) write(s, buffer, strlen(buffer));
E 10
}

/* ARGSUSED */
I 40
void
E 40
daytime_dg(s, sep)		/* Return human-readable time of day */
	int s;
	struct servtab *sep;
{
	char buffer[256];
D 36
	time_t time(), clock;
E 36
I 36
	time_t clock;
E 36
	struct sockaddr sa;
	int size;
D 36
	char *ctime();
E 36

	clock = time((time_t *) 0);

	size = sizeof(sa);
	if (recvfrom(s, buffer, sizeof(buffer), 0, &sa, &size) < 0)
		return;
D 14
	sprintf(buffer, "%s\r", ctime(&clock));
E 14
I 14
D 16
	sprintf(buffer, "%.24s\r\n", ctime(&clock));
E 16
I 16
	(void) sprintf(buffer, "%.24s\r\n", ctime(&clock));
E 16
E 14
	(void) sendto(s, buffer, strlen(buffer), 0, &sa, sizeof(sa));
I 12
}

/*
 * print_service:
 *	Dump relevant information to stderr
 */
I 40
void
E 40
print_service(action, sep)
	char *action;
	struct servtab *sep;
{
	fprintf(stderr,
	    "%s: %s proto=%s, wait=%d, user=%s builtin=%x server=%s\n",
	    action, sep->se_service, sep->se_proto,
D 19
	    sep->se_wait, sep->se_user, sep->se_bi, sep->se_server);
E 19
I 19
	    sep->se_wait, sep->se_user, (int)sep->se_bi, sep->se_server);
I 36
}

/*
 *  Based on TCPMUX.C by Mark K. Lottor November 1988
 *  sri-nic::ps:<mkl>tcpmux.c
 */


static int		/* # of characters upto \r,\n or \0 */
getline(fd, buf, len)
	int fd;
	char *buf;
	int len;
{
	int count = 0, n;

	do {
		n = read(fd, buf, len-count);
		if (n == 0)
D 40
			return count;
E 40
I 40
			return (count);
E 40
		if (n < 0)
			return (-1);
		while (--n >= 0) {
			if (*buf == '\r' || *buf == '\n' || *buf == '\0')
D 40
				return count;
E 40
I 40
				return (count);
E 40
			count++;
			buf++;
		}
	} while (count < len);
	return (count);
}

#define MAX_SERV_LEN	(256+2)		/* 2 bytes for \r\n */

#define strwrite(fd, buf)	(void) write(fd, buf, sizeof(buf)-1)

struct servtab *
tcpmux(s)
	int s;
{
D 40
	register struct servtab *sep;
E 40
I 40
	struct servtab *sep;
E 40
	char service[MAX_SERV_LEN+1];
	int len;

	/* Get requested service name */
	if ((len = getline(s, service, MAX_SERV_LEN)) < 0) {
D 40
	    strwrite(s, "-Error reading service name\r\n");
	    return(NULL);
E 40
I 40
		strwrite(s, "-Error reading service name\r\n");
		return (NULL);
E 40
	}
	service[len] = '\0';

	if (debug)
D 40
	    fprintf(stderr, "tcpmux: someone wants %s\n", service);
E 40
I 40
		fprintf(stderr, "tcpmux: someone wants %s\n", service);
E 40

	/*
	 * Help is a required command, and lists available services,
	 * one per line.
	 */
D 40
	if (!strcasecmp(service,"help")) {
	    for (sep = servtab; sep; sep = sep->se_next) {
		if (!ISMUX(sep))
		    continue;
		(void) write(s, sep->se_service, strlen(sep->se_service));
		strwrite(s, "\r\n");
	    }
	    return(NULL);
E 40
I 40
	if (!strcasecmp(service, "help")) {
		for (sep = servtab; sep; sep = sep->se_next) {
			if (!ISMUX(sep))
				continue;
			(void)write(s,sep->se_service,strlen(sep->se_service));
			strwrite(s, "\r\n");
		}
		return (NULL);
E 40
	}

	/* Try matching a service in inetd.conf with the request */
	for (sep = servtab; sep; sep = sep->se_next) {
D 40
	    if (!ISMUX(sep))
		continue;
	    if (!strcasecmp(service,sep->se_service)) {
		if (ISMUXPLUS(sep)) {
		    strwrite(s, "+Go\r\n");
E 40
I 40
		if (!ISMUX(sep))
			continue;
		if (!strcasecmp(service, sep->se_service)) {
			if (ISMUXPLUS(sep)) {
				strwrite(s, "+Go\r\n");
			}
			return (sep);
E 40
		}
D 40
		return(sep);
	    }
E 40
	}
	strwrite(s, "-Service not available\r\n");
D 40
	return(NULL);
E 40
I 40
	return (NULL);
E 40
E 36
E 19
E 12
E 9
}
E 1
