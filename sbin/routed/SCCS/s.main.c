h59454
s 00005/00005/00320
d D 8.1 93/06/05 11:14:02 bostic 40 39
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00324
d D 5.25 92/10/09 16:41:49 sklower 39 38
c fix from forys@utah.edu
e
s 00008/00000/00317
d D 5.24 92/02/19 17:03:06 sklower 38 37
c use kinfo to survey interface list, and use routing socket instead of
c old ioctls
e
s 00002/00002/00315
d D 5.23 91/07/01 00:20:04 bostic 37 36
c FNDELAY -> O_NONBLOCK
e
s 00003/00003/00314
d D 5.22 91/02/28 18:08:01 bostic 36 35
c ANSI
e
s 00002/00017/00315
d D 5.21 90/06/29 20:05:20 karels 35 34
c use daemon() call
e
s 00001/00011/00331
d D 5.20 90/06/01 16:29:29 bostic 34 33
c new copyright notice
e
s 00007/00006/00335
d D 5.19 90/04/12 18:09:43 karels 33 32
c work around vax optimizer bug producing version 0 queries
e
s 00002/00001/00339
d D 5.18 89/05/11 14:11:43 bostic 32 31
c file reorg, pathnames.h, paths.h
e
s 00009/00005/00331
d D 5.17 89/02/20 17:21:22 karels 31 30
c don't use same buffer for input and output, as that leads to race
e
s 00150/00047/00186
d D 5.16 89/02/18 11:28:30 karels 30 29
c working with dynamic updates, auto-loading timer; tracing additions and fixes
e
s 00010/00000/00223
d D 5.15 88/06/27 20:31:36 karels 29 28
c #ifdef's for sun and other out-of-date systems
e
s 00010/00005/00213
d D 5.14 88/06/18 13:56:33 bostic 28 27
c install approved copyright notice
e
s 00019/00007/00199
d D 5.13 88/05/31 11:52:55 karels 27 26
c new tracing
e
s 00011/00005/00195
d D 5.12 88/02/16 18:50:53 bostic 26 25
c add Berkeley specific headers
e
s 00005/00004/00195
d D 5.11 87/05/28 11:26:09 karels 25 24
c rework interface metrics to invert perspective; other misc. fixes
e
s 00000/00000/00199
d D 5.10 87/04/20 12:21:16 karels 24 23
x 22
c put back LOG_UPTO; it's not obsolete, there's no replacement!
c (and logmask takes a MASK!)
e
s 00004/00001/00195
d D 5.9 87/04/20 11:55:14 karels 23 22
c reorder startup so static routes to subnets work right;
c 
e
s 00003/00003/00193
d D 5.8 86/11/24 18:36:19 eric 22 21
c drop LOG_UPTO -- obsolete interface
e
s 00000/00001/00196
d D 5.7 86/04/20 23:34:16 karels 21 20
c changes to allow subnets to remain local, propogate net route
c where subnets don't go, and allow external routes from /etc/gateways
c to block routed from installing routes from elsewhere
e
s 00008/00001/00189
d D 5.6 86/02/23 19:34:13 karels 20 19
c don't rely on AF_MAX (comes from kernel include): check for nil explicitly,
c use our own idea of table size.  Use syslog to (optionally) log bad packets.
c Don't respond to routing inquiries from a router unless we are suppliers
c (really want to respondto everything but broadcasts, but haven't got
c the "to" address.)
e
s 00001/00001/00189
d D 5.5 86/01/06 14:12:04 mckusick 19 18
c check for error on socket()
e
s 00006/00013/00184
d D 5.4 85/11/21 19:55:42 karels 18 17
c don't bother waiting if socket, bind fail
e
s 00001/00001/00196
d D 5.3 85/09/17 18:49:30 eric 17 16
c facilities in syslog
e
s 00004/00005/00193
d D 5.2 85/09/16 17:31:30 sklower 16 15
c call to socket had one too many args, other small fixups.
e
s 00013/00001/00185
d D 5.1 85/06/04 16:36:13 dist 15 14
c Add copyright
e
s 00005/00008/00181
d D 4.13 85/06/03 09:50:36 karels 14 13
c new subnets
e
s 00000/00021/00189
d D 4.12 85/02/25 13:46:47 karels 13 12
c remove 4.1a compat
e
s 00014/00003/00196
d D 4.11 84/12/20 18:04:04 karels 12 10
c syslog for interface transitions; broadcast all unreachable before exit
e
s 00004/00000/00199
d R 4.11 84/08/29 15:06:34 karels 11 10
c add SO_BROADCAST option on socket
e
s 00013/00001/00186
d D 4.10 84/04/10 21:40:08 karels 10 9
c subnet routing
e
s 00002/00000/00185
d D 4.9 84/04/09 15:05:18 karels 9 8
c many cleanups; avoid interface timing out; put it back asap
e
s 00003/00001/00182
d D 4.8 83/07/01 23:59:45 sam 8 7
c include fix
e
s 00005/00004/00178
d D 4.7 83/06/12 02:46:21 sam 7 6
c new signals
e
s 00000/00002/00182
d D 4.6 83/06/01 16:26:49 sam 6 5
c notyet has come
e
s 00007/00002/00177
d D 4.5 83/05/25 17:50:50 sam 5 4
c protocol change; byte swap those fields which need it;  also add 
c a version stamp to allow future changes
e
s 00006/00002/00173
d D 4.4 83/01/31 14:49:19 sam 4 3
c don't close sockets when divorcing tty
e
s 00026/00018/00149
d D 4.3 83/01/31 14:18:35 sam 3 2
c add stdout tracing of all packets
e
s 00063/00045/00104
d D 4.2 83/01/11 14:38:19 sam 2 1
c 4.1c conversion contortions
e
s 00149/00000/00000
d D 4.1 82/11/02 22:28:04 sam 1 0
c date and time created 82/11/02 22:28:04 by sam
e
u
U
t
T
I 15
/*
D 27
 * Copyright (c) 1983 Regents of the University of California.
E 27
I 27
D 40
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 27
D 26
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 26
I 26
 * All rights reserved.
E 40
I 40
 * Copyright (c) 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 40
 *
D 34
 * Redistribution and use in source and binary forms are permitted
D 28
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 28
I 28
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
E 34
I 34
 * %sccs.include.redist.c%
E 34
E 28
E 26
 */

E 15
I 1
#ifndef lint
I 15
D 40
char copyright[] =
D 20
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 20
I 20
D 26
"@(#) Copyright (c) 1983 Regents of the University of California.\n\
E 26
I 26
D 27
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 27
I 27
"%Z% Copyright (c) 1983, 1988 Regents of the University of California.\n\
E 27
E 26
E 20
 All rights reserved.\n";
E 40
I 40
static char copyright[] =
"%Z% Copyright (c) 1983, 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 40
D 26
#endif not lint
E 26
I 26
#endif /* not lint */
E 26

#ifndef lint
E 15
D 5
static char sccsid[] = "%W% %G%";
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
D 15
#endif
E 15
I 15
D 26
#endif not lint
E 26
I 26
#endif /* not lint */
E 26
E 15

/*
 * Routing Table Management Daemon
 */
D 2
#include "router.h"
E 2
I 2
#include "defs.h"
E 2
#include <sys/ioctl.h>
I 8
D 30
#include <sys/time.h>
E 30
I 30
#include <sys/file.h>
E 30

E 8
#include <net/if.h>
I 8

E 8
D 27
#include <errno.h>
D 21
#include <nlist.h>
E 21
#include <signal.h>
I 12
#include <syslog.h>
E 27
I 27
#include <sys/errno.h>
#include <sys/signal.h>
#include <sys/syslog.h>
I 32
#include "pathnames.h"
E 32
E 27
E 12
D 8
#include <time.h>
E 8

int	supplier = -1;		/* process should supply updates */
I 10
D 14
extern int gateway;
E 14
I 14
int	gateway = 0;		/* 1 if we are a gateway to parts beyond */
I 25
int	debug = 0;
I 30
int	bufspace = 127*1024;	/* max. input buffer size to request */
E 30
E 25
E 14
E 10

struct	rip *msg = (struct rip *)packet;
I 9
D 25
int	hup();
E 25
I 25
D 27
int	hup(), rtdeleteall();
E 27
I 27
D 36
int	hup(), rtdeleteall(), sigtrace();
E 36
I 36
void	hup(), rtdeleteall(), sigtrace(), timer();
E 36
E 27
E 25
E 9

main(argc, argv)
	int argc;
	char *argv[];
{
D 30
	int cc;
E 30
I 30
	int n, cc, nfd, omask, tflags = 0;
E 30
	struct sockaddr from;
I 30
	struct timeval *tvp, waittime;
	struct itimerval itval;
I 33
	register struct rip *query = msg;
E 33
	fd_set ibits;
E 30
I 2
	u_char retry;
D 13
#ifdef COMPAT
	int snoroute;
#endif
E 13
E 2
	
	argv0 = argv;
I 29
#if BSD >= 43
E 29
I 12
D 16
	openlog("routed", LOG_PID, 0);
E 16
I 16
D 17
	openlog("routed", LOG_PID | LOG_ODELAY, 0);
E 17
I 17
	openlog("routed", LOG_PID | LOG_ODELAY, LOG_DAEMON);
I 20
D 22
	setlogmask(LOG_UPTO(LOG_WARNING));
I 29
#else
	openlog("routed", LOG_PID);
#define LOG_UPTO(x) (x)
#define setlogmask(x) (x)
#endif
E 29
E 22
I 22
	setlogmask(LOG_WARNING);
E 22
E 20
E 17
E 16
E 12
D 3
#ifndef DEBUG
	if (fork())
		exit(0);
	for (cc = 0; cc < 10; cc++)
		(void) close(cc);
	(void) open("/", 0);
	(void) dup2(0, 1);
	(void) dup2(0, 2);
	{ int t = open("/dev/tty", 2);
	  if (t >= 0) {
		ioctl(t, TIOCNOTTY, (char *)0);
		(void) close(t);
	  }
	}
#endif
E 3
D 2
	if (tracing)
		traceon("/etc/routerlog");

	/*
	 * We use two sockets.  One for which outgoing
	 * packets are routed and for which they're not.
	 * The latter allows us to delete routing table
	 * entries in the kernel for network interfaces
	 * attached to our host which we believe are down
	 * while still polling it to see when/if it comes
	 * back up.  With the new ipc interface we'll be
	 * able to specify ``don't route'' as an option
	 * to send, but until then we utilize a second port.
	 */
E 2
	sp = getservbyname("router", "udp");
D 2
	if (sp == 0) {
		fprintf(stderr, "routed: udp/router: unknown service\n");
E 2
I 2
	if (sp == NULL) {
		fprintf(stderr, "routed: router/udp: unknown service\n");
E 2
		exit(1);
	}
D 2
	routingaddr.sin_family = AF_INET;
	routingaddr.sin_port = htons(sp->s_port);
	noroutingaddr.sin_family = AF_INET;
	noroutingaddr.sin_port = htons(sp->s_port + 1);
again:
	s = socket(SOCK_DGRAM, 0, &routingaddr, 0);
	if (s < 0) {
		perror("socket");
		sleep(30);
		goto again;
	}
again2:
	snoroute = socket(SOCK_DGRAM, 0, &noroutingaddr, SO_DONTROUTE);
	if (snoroute < 0) {
		perror("socket");
		sleep(30);
		goto again2;
	}
E 2
I 2
	addr.sin_family = AF_INET;
	addr.sin_port = sp->s_port;
I 38
	r = socket(AF_ROUTE, SOCK_RAW, 0);
	/* later, get smart about lookingforinterfaces */
	if (r)
		shutdown(r, 0); /* for now, don't want reponses */
	else {
		fprintf(stderr, "routed: no routing socket\n");
		exit(1);
	}
E 38
	s = getsocket(AF_INET, SOCK_DGRAM, &addr);
	if (s < 0)
		exit(1);
D 13
#ifdef COMPAT
	bzero(&addr, sizeof (addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(ntohs(sp->s_port) + 1);
	snoroute = getsocket(AF_INET, SOCK_DGRAM, &addr);
	if (snoroute < 0)
		exit(1);
#endif
E 13
E 2
	argv++, argc--;
	while (argc > 0 && **argv == '-') {
D 3
		if (!strcmp(*argv, "-s") == 0) {
E 3
I 3
		if (strcmp(*argv, "-s") == 0) {
E 3
			supplier = 1;
			argv++, argc--;
			continue;
		}
D 3
		if (!strcmp(*argv, "-q") == 0) {
E 3
I 3
		if (strcmp(*argv, "-q") == 0) {
E 3
			supplier = 0;
			argv++, argc--;
			continue;
		}
D 2
		goto usage;
	}
	if (argc > 0) {
usage:
E 2
D 3
		fprintf(stderr, "usage: routed [ -s ] [ -q ]\n");
E 3
I 3
		if (strcmp(*argv, "-t") == 0) {
D 27
			tracepackets++;
E 27
I 27
D 30
			if (tracehistory == 0)
				tracehistory++;
			else {
				tracehistory = 0;
				tracepackets++;
			}
E 30
I 30
			tflags++;
E 30
E 27
I 20
D 22
			setlogmask(LOG_UPTO(LOG_DEBUG));
E 22
I 22
			setlogmask(LOG_DEBUG);
E 22
			argv++, argc--;
			continue;
		}
		if (strcmp(*argv, "-d") == 0) {
I 25
			debug++;
E 25
D 22
			setlogmask(LOG_UPTO(LOG_DEBUG));
E 22
I 22
			setlogmask(LOG_DEBUG);
E 22
E 20
			argv++, argc--;
			continue;
		}
D 10
		fprintf(stderr, "usage: routed [ -s ] [ -q ] [ -t ]\n");
E 10
I 10
		if (strcmp(*argv, "-g") == 0) {
			gateway = 1;
			argv++, argc--;
			continue;
		}
D 14
		if (strcmp(*argv, "-l") == 0) {
			gateway = -1;
			argv++, argc--;
			continue;
		}
E 14
		fprintf(stderr,
D 14
			"usage: routed [ -s ] [ -q ] [ -t ] [ -g ] [ -l ]\n");
E 14
I 14
			"usage: routed [ -s ] [ -q ] [ -t ] [ -g ]\n");
E 14
E 10
E 3
		exit(1);
	}
I 3
D 25
#ifndef DEBUG
	if (!tracepackets) {
E 25
I 25
D 30
	if (tracepackets == 0 && debug == 0) {
E 30
I 30

D 35
	if (debug == 0) {
E 30
E 25
		int t;

		if (fork())
			exit(0);
D 4
		for (cc = 0; cc < 10; cc++)
			(void) close(cc);
E 4
I 4
		for (t = 0; t < 20; t++)
			if (t != s)
D 13
#ifdef COMPAT
D 5
			    if (t != snoroute)
E 5
I 5
				if (t != snoroute)
E 5
#endif
E 13
D 16
				(void) close(cc);
E 16
I 16
				(void) close(t);
E 16
E 4
		(void) open("/", 0);
		(void) dup2(0, 1);
		(void) dup2(0, 2);
D 32
		t = open("/dev/tty", 2);
E 32
I 32
		t = open(_PATH_TTY, 2);
E 32
		if (t >= 0) {
			ioctl(t, TIOCNOTTY, (char *)0);
			(void) close(t);
		}
	}
E 35
I 35
D 39
	if (debug == 0)
E 39
I 39
	if (debug == 0 && tflags == 0)
E 39
		daemon(0, 0);
E 35
D 25
#endif
E 25
E 3
	/*
I 2
	 * Any extra argument is considered
	 * a tracing log file.
	 */
	if (argc > 0)
		traceon(*argv);
I 30
	while (tflags-- > 0)
		bumploglevel();

	(void) gettimeofday(&now, (struct timezone *)NULL);
E 30
	/*
E 2
	 * Collect an initial view of the world by
D 14
	 * snooping in the kernel and the gateway kludge
E 14
I 14
	 * checking the interface configuration and the gateway kludge
E 14
	 * file.  Then, send a request packet on all
	 * directly connected networks to find out what
	 * everyone else thinks.
	 */
	rtinit();
D 23
	gwkludge();
E 23
	ifinit();
I 23
	gwkludge();
E 23
I 14
	if (gateway > 0)
		rtdefault();
E 14
	if (supplier < 0)
		supplier = 0;
D 33
	msg->rip_cmd = RIPCMD_REQUEST;
I 5
	msg->rip_vers = RIPVERSION;
E 5
D 30
	msg->rip_nets[0].rip_dst.sa_family = AF_UNSPEC;
	msg->rip_nets[0].rip_metric = HOPCNT_INFINITY;
I 5
D 6
#ifdef notyet
E 6
	msg->rip_nets[0].rip_dst.sa_family = htons(AF_UNSPEC);
	msg->rip_nets[0].rip_metric = htonl(HOPCNT_INFINITY);
E 30
I 30
	if (sizeof(msg->rip_nets[0].rip_dst.sa_family) > 1)	/* XXX */
		msg->rip_nets[0].rip_dst.sa_family = htons((u_short)AF_UNSPEC);
E 33
I 33
	query->rip_cmd = RIPCMD_REQUEST;
	query->rip_vers = RIPVERSION;
	if (sizeof(query->rip_nets[0].rip_dst.sa_family) > 1)	/* XXX */
		query->rip_nets[0].rip_dst.sa_family = htons((u_short)AF_UNSPEC);
E 33
	else
D 33
		msg->rip_nets[0].rip_dst.sa_family = AF_UNSPEC;
	msg->rip_nets[0].rip_metric = htonl((u_long)HOPCNT_INFINITY);
E 33
I 33
		query->rip_nets[0].rip_dst.sa_family = AF_UNSPEC;
	query->rip_nets[0].rip_metric = htonl((u_long)HOPCNT_INFINITY);
E 33
E 30
D 6
#endif
E 6
E 5
D 36
	toall(sendmsg);
E 36
I 36
	toall(sndmsg);
E 36
D 7
	sigset(SIGALRM, timer);
E 7
I 7
	signal(SIGALRM, timer);
I 9
	signal(SIGHUP, hup);
I 12
	signal(SIGTERM, hup);
I 25
	signal(SIGINT, rtdeleteall);
I 27
	signal(SIGUSR1, sigtrace);
	signal(SIGUSR2, sigtrace);
E 27
E 25
E 12
E 9
E 7
D 30
	timer();
E 30
I 30
	itval.it_interval.tv_sec = TIMER_RATE;
	itval.it_value.tv_sec = TIMER_RATE;
	itval.it_interval.tv_usec = 0;
	itval.it_value.tv_usec = 0;
	srandom(getpid());
	if (setitimer(ITIMER_REAL, &itval, (struct itimerval *)NULL) < 0)
		syslog(LOG_ERR, "setitimer: %m\n");
E 30

I 30
	FD_ZERO(&ibits);
	nfd = s + 1;			/* 1 + max(fd's) */
E 30
D 2
#define	INFINITY	1000000
E 2
	for (;;) {
D 30
		int ibits;
		register int n;

D 2
		ibits = (1 << s) | (1 << snoroute);
		n = select(32, &ibits, 0, INFINITY);
E 2
I 2
		ibits = 1 << s;
D 13
#ifdef COMPAT
		ibits |= 1 << snoroute;
#endif
E 13
		n = select(20, &ibits, 0, 0, 0);
E 2
		if (n < 0)
E 30
I 30
		FD_SET(s, &ibits);
		/*
		 * If we need a dynamic update that was held off,
		 * needupdate will be set, and nextbcast is the time
		 * by which we want select to return.  Compute time
		 * until dynamic update should be sent, and select only
		 * until then.  If we have already passed nextbcast,
		 * just poll.
		 */
		if (needupdate) {
			waittime = nextbcast;
			timevalsub(&waittime, &now);
			if (waittime.tv_sec < 0) {
				waittime.tv_sec = 0;
				waittime.tv_usec = 0;
			}
			if (traceactions)
				fprintf(ftrace,
				 "select until dynamic update %d/%d sec/usec\n",
				    waittime.tv_sec, waittime.tv_usec);
			tvp = &waittime;
		} else
			tvp = (struct timeval *)NULL;
		n = select(nfd, &ibits, 0, 0, tvp);
		if (n <= 0) {
			/*
			 * Need delayed dynamic update if select returned
			 * nothing and we timed out.  Otherwise, ignore
			 * errors (e.g. EINTR).
			 */
			if (n < 0) {
				if (errno == EINTR)
					continue;
				syslog(LOG_ERR, "select: %m");
			}
			omask = sigblock(sigmask(SIGALRM));
			if (n == 0 && needupdate) {
				if (traceactions)
					fprintf(ftrace,
					    "send delayed dynamic update\n");
				(void) gettimeofday(&now,
					    (struct timezone *)NULL);
				toall(supply, RTS_CHANGED,
				    (struct interface *)NULL);
				lastbcast = now;
				needupdate = 0;
				nextbcast.tv_sec = 0;
			}
			sigsetmask(omask);
E 30
			continue;
D 30
		if (ibits & (1 << s))
E 30
I 30
		}
		(void) gettimeofday(&now, (struct timezone *)NULL);
I 31
		omask = sigblock(sigmask(SIGALRM));
E 31
#ifdef doesntwork
/*
printf("s %d, ibits %x index %d, mod %d, sh %x, or %x &ibits %x\n",
	s,
	ibits.fds_bits[0],
	(s)/(sizeof(fd_mask) * 8),
	((s) % (sizeof(fd_mask) * 8)),
	(1 << ((s) % (sizeof(fd_mask) * 8))),
	ibits.fds_bits[(s)/(sizeof(fd_mask) * 8)] & (1 << ((s) % (sizeof(fd_mask) * 8))),
	&ibits
	);
*/
		if (FD_ISSET(s, &ibits))
#else
		if (ibits.fds_bits[s/32] & (1 << s))
#endif
E 30
			process(s);
I 2
D 13
#ifdef COMPAT
E 2
		if (ibits & (1 << snoroute))
			process(snoroute);
I 2
#endif
E 13
		/* handle ICMP redirects */
I 31
		sigsetmask(omask);
E 31
E 2
	}
}

I 30
timevaladd(t1, t2)
	struct timeval *t1, *t2;
{

	t1->tv_sec += t2->tv_sec;
	if ((t1->tv_usec += t2->tv_usec) > 1000000) {
		t1->tv_sec++;
		t1->tv_usec -= 1000000;
	}
}

timevalsub(t1, t2)
	struct timeval *t1, *t2;
{

	t1->tv_sec -= t2->tv_sec;
	if ((t1->tv_usec -= t2->tv_usec) < 0) {
		t1->tv_sec--;
		t1->tv_usec += 1000000;
	}
}

E 30
process(fd)
	int fd;
{
D 2
	register int cc;
E 2
	struct sockaddr from;
I 2
D 7
	int fromlen = sizeof (from), cc;
E 7
I 7
D 30
	int fromlen = sizeof (from), cc, omask;
I 27
	time_t now;
E 30
I 30
D 31
	int fromlen, cc, omask;
E 31
I 31
	int fromlen, cc;
	union {
		char	buf[MAXPACKETSIZE+1];
		struct	rip rip;
	} inbuf;
E 31
E 30
E 27
E 7
E 2

D 2
	cc = receive(fd, &from, packet, sizeof (packet));
E 2
I 2
D 30
	cc = recvfrom(fd, packet, sizeof (packet), 0, &from, &fromlen);
E 2
	if (cc <= 0) {
		if (cc < 0 && errno != EINTR)
D 2
			perror("receive");
E 2
I 2
			perror("recvfrom");
E 2
		return;
E 30
I 30
	for (;;) {
		fromlen = sizeof (from);
D 31
		cc = recvfrom(fd, packet, sizeof (packet), 0, &from, &fromlen);
E 31
I 31
		cc = recvfrom(fd, &inbuf, sizeof (inbuf), 0, &from, &fromlen);
E 31
		if (cc <= 0) {
			if (cc < 0 && errno != EWOULDBLOCK)
				perror("recvfrom");
			break;
		}
		if (fromlen != sizeof (struct sockaddr_in))
			break;
D 31
		omask = sigblock(sigmask(SIGALRM));
		rip_input(&from, cc);
		sigsetmask(omask);
E 31
I 31
		rip_input(&from, &inbuf.rip, cc);
E 31
E 30
	}
I 2
D 30
	if (fromlen != sizeof (struct sockaddr_in))
		return;
I 27
	if (traceactions && !tracepackets) {
		(void) time(&now);
		curtime = ctime(&now);
	}
E 27
E 2
D 7
	sighold(SIGALRM);
E 7
I 7
D 16
#define	mask(s)	(1<<((s)-1))
	omask = sigblock(mask(SIGALRM));
E 16
I 16
	omask = sigblock(sigmask(SIGALRM));
E 16
E 7
	rip_input(&from, cc);
D 7
	sigrelse(SIGALRM);
E 7
I 7
	sigsetmask(omask);
E 30
E 7
I 2
}

getsocket(domain, type, sin)
	int domain, type;
	struct sockaddr_in *sin;
{
D 12
	int retry, s;
E 12
I 12
D 18
	int retry, s, on = 1;
E 18
I 18
D 30
	int s, on = 1;
E 30
I 30
	int sock, on = 1;
E 30
E 18
E 12

D 18
	retry = 1;
D 16
	while ((s = socket(domain, type, 0, 0)) < 0 && retry) {
E 16
I 16
	while ((s = socket(domain, type, 0)) < 0 && retry) {
E 18
I 18
D 19
	if (s = socket(domain, type, 0)) {
E 19
I 19
D 30
	if ((s = socket(domain, type, 0)) < 0) {
E 30
I 30
	if ((sock = socket(domain, type, 0)) < 0) {
E 30
E 19
E 18
E 16
		perror("socket");
D 18
		sleep(5 * retry);
		retry <<= 1;
	}
D 12
	if (retry == 0)
E 12
I 12
	if (retry == 0) {
E 18
		syslog(LOG_ERR, "socket: %m");
E 12
		return (-1);
I 12
	}
I 29
#ifdef SO_BROADCAST
E 29
D 30
	if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &on, sizeof (on)) < 0) {
E 30
I 30
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &on, sizeof (on)) < 0) {
E 30
		syslog(LOG_ERR, "setsockopt SO_BROADCAST: %m");
D 18
		exit(1);
E 18
I 18
D 30
		close(s);
E 30
I 30
		close(sock);
E 30
		return (-1);
E 18
	}
I 29
#endif
#ifdef SO_RCVBUF
E 29
I 23
D 30
	on = 48*1024;
	if (setsockopt(s, SOL_SOCKET, SO_RCVBUF, &on, sizeof (on)) < 0)
		syslog(LOG_ERR, "setsockopt SO_RCVBUF: %m");
E 30
I 30
	for (on = bufspace; ; on -= 1024) {
		if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF,
		    &on, sizeof (on)) == 0)
			break;
		if (on <= 8*1024) {
			syslog(LOG_ERR, "setsockopt SO_RCVBUF: %m");
			break;
		}
	}
	if (traceactions)
		fprintf(ftrace, "recv buf %d\n", on);
E 30
I 29
#endif
E 29
E 23
E 12
D 18
	while (bind(s, sin, sizeof (*sin), 0) < 0 && retry) {
E 18
I 18
D 30
	if (bind(s, sin, sizeof (*sin), 0) < 0) {
E 30
I 30
D 36
	if (bind(sock, sin, sizeof (*sin), 0) < 0) {
E 36
I 36
	if (bind(sock, (struct sockaddr *)sin, sizeof (*sin)) < 0) {
E 36
E 30
E 18
		perror("bind");
D 18
		sleep(5 * retry);
		retry <<= 1;
	}
D 12
	if (retry == 0)
E 12
I 12
	if (retry == 0) {
E 18
		syslog(LOG_ERR, "bind: %m");
I 18
D 30
		close(s);
E 30
I 30
		close(sock);
E 30
E 18
E 12
		return (-1);
I 12
	}
E 12
D 30
	return (s);
E 30
I 30
D 37
	if (fcntl(sock, F_SETFL, FNDELAY) == -1)
		syslog(LOG_ERR, "fcntl FNDELAY: %m\n");
E 37
I 37
	if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1)
		syslog(LOG_ERR, "fcntl O_NONBLOCK: %m\n");
E 37
	return (sock);
E 30
E 2
}
E 1
