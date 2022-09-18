h16978
s 00005/00005/00224
d D 8.1 93/06/05 10:47:43 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00001/00218
d D 5.12 92/02/20 11:59:56 sklower 12 11
c use new kerninfo instead of SIOCGCONF, routing socket instead of
c SIOC{ADD,DEL}RT; edit only, can't test for a while.
e
s 00010/00010/00209
d D 5.11 91/02/26 15:31:29 bostic 11 10
c ANSI fixes (one real bug!)
e
s 00002/00016/00217
d D 5.10 90/06/29 19:50:43 karels 10 9
c use daemon() call
e
s 00001/00011/00232
d D 5.9 90/06/01 16:14:39 bostic 9 8
c new copyright notice
e
s 00001/00000/00242
d D 5.8 89/08/21 14:07:36 sklower 8 7
c mbuf and big sockaddr changes
e
s 00002/00001/00240
d D 5.7 89/05/11 14:03:44 bostic 7 6
c file reorg, pathnames.h, paths.h
e
s 00019/00008/00222
d D 5.6 88/09/19 21:00:46 bostic 6 5
c add Berkeley specific copyright notice
e
s 00010/00005/00220
d D 5.5 86/02/14 18:28:01 sklower 5 4
c 1.) Fixes from Nesheim viz pt to pt timeouts;
c 2.) Getting rid of ns_netof, to make common for Gould, CCI
e
s 00022/00031/00203
d D 5.4 85/09/17 21:42:08 sklower 4 3
c latest changes from nesheim@cornell:
c use syslog instead of perror, ignore remote requests unless specifically asked,
c handle requests from net 0.
e
s 00035/00017/00199
d D 5.3 85/08/16 21:48:58 sklower 3 2
c This version Aug 16th -- source directory moved to /usr/src/etc/XNSrouted;
c includes fix to response to request for specific net, and adds copyright notices
e
s 00043/00038/00173
d D 5.2 85/08/16 20:43:49 sklower 2 1
c status as of 4.3 alpha tape
e
s 00211/00000/00000
d D 5.1 85/08/16 20:22:41 sklower 1 0
c date and time created 85/08/16 20:22:41 by sklower
e
u
U
t
T
I 3
/*
D 6
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
D 13
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
E 6
 *
D 6
 * Includes material written at Cornell University by Bill Nesheim
 * with permission of the author.
E 6
I 6
 * This file includes significant work done at Cornell University by
 * Bill Nesheim.  That work included by permission.
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
E 6
 */

E 3
I 1
#ifndef lint
D 3
static char rcsid[] = "$Header$";
#endif
E 3
I 3
D 13
char copyright[] =
D 5
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 5
I 5
D 6
"@(#) Copyright (c) 1983 Regents of the University of California.\n\
E 6
I 6
"%Z% Copyright (c) 1985 The Regents of the University of California.\n\
E 6
E 5
 All rights reserved.\n";
E 13
I 13
static char copyright[] =
"%Z% Copyright (c) 1985, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 13
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6
E 3

I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6

E 3
/*
 * XNS Routing Information Protocol Daemon
 */
#include "defs.h"
D 11
#include <sys/ioctl.h>
E 11
#include <sys/time.h>

#include <net/if.h>

#include <errno.h>
#include <nlist.h>
#include <signal.h>
I 7
#include <paths.h>
E 7
I 2
D 4
#include <syslog.h>
E 4
E 2

int	supplier = -1;		/* process should supply updates */
extern int gateway;

struct	rip *msg = (struct rip *) &packet[sizeof (struct idp)]; 
D 11
int	hup(), fkexit();
E 11
I 11
void	hup(), fkexit(), timer();
E 11

main(argc, argv)
	int argc;
	char *argv[];
{
I 2
	int cc;
E 2
	struct sockaddr from;
	u_char retry;
D 2
	int selectbits;
	struct interface *ifp;
	extern struct interface *ifnet;
E 2
	
	argv0 = argv;
I 2
D 3
	addr.sns_family = AF_NS;
	addr.sns_port = htons(IDPPORT_RIF);
	s = getsocket(SOCK_DGRAM, 0, &addr);
	if (s < 0)
		exit(1);
E 3
E 2
	argv++, argc--;
	while (argc > 0 && **argv == '-') {
		if (strcmp(*argv, "-s") == 0) {
			supplier = 1;
			argv++, argc--;
			continue;
		}
		if (strcmp(*argv, "-q") == 0) {
			supplier = 0;
			argv++, argc--;
			continue;
		}
I 4
		if (strcmp(*argv, "-R") == 0) {
			noteremoterequests++;
			argv++, argc--;
			continue;
		}
E 4
		if (strcmp(*argv, "-t") == 0) {
			tracepackets++;
			argv++, argc--;
			ftrace = stderr;
			tracing = 1; 
			continue;
		}
		if (strcmp(*argv, "-g") == 0) {
			gateway = 1;
			argv++, argc--;
			continue;
		}
		if (strcmp(*argv, "-l") == 0) {
			gateway = -1;
			argv++, argc--;
			continue;
		}
		fprintf(stderr,
			"usage: xnsrouted [ -s ] [ -q ] [ -t ] [ -g ] [ -l ]\n");
		exit(1);
	}
	
I 4
	
E 4
#ifndef DEBUG
D 10
	if (!tracepackets) {
		int t;

		if (fork())
			exit(0);
		for (t = 0; t < 20; t++)
			(void) close(t);
		(void) open("/", 0);
		(void) dup2(0, 1);
		(void) dup2(0, 2);
D 7
		t = open("/dev/tty", 2);
E 7
I 7
		t = open(_PATH_TTY, 2);
E 7
		if (t >= 0) {
			ioctl(t, TIOCNOTTY, (char *)0);
			(void) close(t);
		}
	}
E 10
I 10
	if (!tracepackets)
		daemon(0, 0);
E 10
#endif
I 4
	openlog("XNSrouted", LOG_PID, LOG_DAEMON);

I 5
D 12
	ns_anynet.s_net[0] = -1; ns_anynet.s_net[1] = -1;
E 12
E 5
E 4
I 3
	addr.sns_family = AF_NS;
I 8
	addr.sns_len = sizeof(addr);
E 8
	addr.sns_port = htons(IDPPORT_RIF);
I 12
	ns_anynet.s_net[0] = ns_anynet.s_net[1] = -1;
	ns_netmask.sns_addr.x_net = ns_anynet;
	ns_netmask.sns_len = 6;
	r = socket(AF_ROUTE, SOCK_RAW, 0);
	/* later, get smart about lookingforinterfaces */
	if (r)
		shutdown(r, 0); /* for now, don't want reponses */
	else {
		fprintf(stderr, "routed: no routing socket\n");
		exit(1);
	}
E 12
	s = getsocket(SOCK_DGRAM, 0, &addr);
	if (s < 0)
		exit(1);
E 3
	/*
	 * Any extra argument is considered
	 * a tracing log file.
	 */
	if (argc > 0)
		traceon(*argv);
	/*
	 * Collect an initial view of the world by
	 * snooping in the kernel.  Then, send a request packet on all
	 * directly connected networks to find out what
	 * everyone else thinks.
	 */
	rtinit();
	ifinit();
	if (supplier < 0)
		supplier = 0;
	/* request the state of the world */
	msg->rip_cmd = htons(RIPCMD_REQUEST);
D 2
	xnnet(msg->rip_nets[0].rip_dst) = htonl(DSTNETS_ALL);
E 2
I 2
D 5
	xnnet(msg->rip_nets[0].rip_dst[0]) = htonl(DSTNETS_ALL);
E 5
I 5
	msg->rip_nets[0].rip_dst = ns_anynet;
E 5
E 2
	msg->rip_nets[0].rip_metric =  htons(HOPCNT_INFINITY);
D 11
	toall(sendmsg);
E 11
I 11
	toall(sndmsg);
E 11
	signal(SIGALRM, timer);
	signal(SIGHUP, hup);
	signal(SIGINT, hup);
	signal(SIGEMT, fkexit);
	timer();
	
D 2
	/*
	 * Listen for RIF packets on all interfaces
	 */
	selectbits = 0;
	for( ifp = ifnet; ifp!=0; ifp = ifp->int_next) {
		selectbits |= 1 << ifp->int_ripsock[0];
		selectbits |= 1 << ifp->int_ripsock[1];
	}
E 2

D 4
	for (;;) {
		int ibits;
		register int n;

D 2
		ibits = selectbits;
E 2
I 2
		/*ibits = 1 << s;
E 2
		n = select(20, &ibits, 0, 0, 0);
D 2
		if (n < 0) {
			if(errno != EINTR) {
				perror("main:select");
				exit(1);
			}
E 2
I 2
		if (n < 0)
E 2
			continue;
D 2
		}
		for( ifp = ifnet; ifp!=0; ifp = ifp->int_next) {
		    /* take RIF packet off interface */
		    for(n = 0; n < 2; n++)
			if(ibits & (1 << ifp->int_ripsock[n]))
				process(ifp->int_ripsock[n]);
		}
E 2
I 2
		if (ibits & (1 << s)) */
			process(s);
		/* handle ICMP redirects */
E 2
	}
E 4
I 4
	for (;;) 
		process(s);
	
E 4
}

process(fd)
	int fd;
{
	struct sockaddr from;
	int fromlen = sizeof (from), cc, omask;
	struct idp *idp = (struct idp *)packet;

	cc = recvfrom(fd, packet, sizeof (packet), 0, &from, &fromlen);
	if (cc <= 0) {
		if (cc < 0 && errno != EINTR)
D 4
			perror("recvfrom");
E 4
I 4
D 11
			syslog("recvfrom: %m");
E 11
I 11
			syslog(LOG_ERR, "recvfrom: %m");
E 11
E 4
		return;
	}
D 3
	/* We get the IDP header in front of the RIF packet*/
E 3
D 4
	if (tracepackets > 1) {
E 4
I 4
	if (tracepackets > 1 && ftrace) {
E 4
D 3
	    fprintf(ftrace,"rcv %d bytes on %s ",
D 2
		cc, xns_ntoa(&idp->idp_dst));
	    fprintf(ftrace," from %s\n", xns_ntoa(&idp->idp_src));
E 2
I 2
		cc, xns_ntoa(&idp->idp_dna));
E 3
I 3
	    fprintf(ftrace,"rcv %d bytes on %s ", cc, xns_ntoa(&idp->idp_dna));
E 3
	    fprintf(ftrace," from %s\n", xns_ntoa(&idp->idp_sna));
E 2
	}
D 3
	
D 2
	if (xnnet(idp->idp_src.xn_net) != xnnet(idp->idp_dst.xn_net)) {
E 2
I 2
	if (ns_netof(idp->idp_sna) != ns_netof(idp->idp_dna)) {
E 2
		fprintf(ftrace, "XNSrouted: net of interface (%d) != net on ether (%d)!\n",
D 2
			ntohl(xnnet(idp->idp_dst.xn_net)),
			ntohs(xnnet(idp->idp_src.xn_net)));
E 2
I 2
			ns_netof(idp->idp_dna), ns_netof(idp->idp_sna));
E 3
I 3
D 4
	if (tracepackets > 0) {
	    if (ns_netof(idp->idp_sna) != ns_netof(idp->idp_dna)) {
		    fprintf(ftrace,
			    "XNSrouted: net of interface (%d) ",
			    ns_netof(idp->idp_dna));
		    fprintf(ftrace,
			    "!= net on ether (%d)!\n", ns_netof(idp->idp_sna));
	    }
	    if (fromlen != sizeof (struct sockaddr_ns))
		    fprintf(ftrace, "fromlen is %d instead of %d\n",
		    fromlen, sizeof (struct sockaddr_ns));
E 4
I 4
	
D 5
	if (noteremoterequests && ns_netof(idp->idp_sna) && 
	    ns_netof(idp->idp_sna) != ns_netof(idp->idp_dna)) {
		syslog(LOG_ERR, "net of interface (%d) != net on ether (%d)!\n",  ns_netof(idp->idp_dna), ns_netof(idp->idp_sna));
E 5
I 5
	if (noteremoterequests && !ns_neteqnn(idp->idp_sna.x_net, ns_zeronet)
		&& !ns_neteq(idp->idp_sna, idp->idp_dna))
	{
		syslog(LOG_ERR,
		       "net of interface (%s) != net on ether (%s)!\n",
		       xns_nettoa(idp->idp_dna.x_net),
		       xns_nettoa(idp->idp_sna.x_net));
E 5
E 4
E 3
E 2
	}
			
I 3
	/* We get the IDP header in front of the RIF packet*/
E 3
	cc -= sizeof (struct idp);
D 2
	if (fromlen != sizeof (struct sockaddr_xn))
		return;
E 2
I 2
D 3
	if (fromlen != sizeof (struct sockaddr_ns))
		fprintf(ftrace, "fromlen is %d instead of %d\n",
		fromlen, sizeof (struct sockaddr_ns));
E 3
E 2
#define	mask(s)	(1<<((s)-1))
	omask = sigblock(mask(SIGALRM));
	rip_input(&from, cc);
	sigsetmask(omask);
}

D 2
getsocket(domain, type, proto, sxn)
	int domain, type, proto;
	struct sockaddr_xn *sxn;
E 2
I 2
getsocket(type, proto, sns)
	int type, proto; 
	struct sockaddr_ns *sns;
E 2
{
D 2
	int retry, s;
E 2
I 2
	int domain = sns->sns_family;
	int retry, s, on = 1;
E 2

	retry = 1;
D 2
	while ((s = socket(domain, type, proto, 0)) < 0 && retry) {
E 2
I 2
	while ((s = socket(domain, type, proto)) < 0 && retry) {
E 2
D 4
		perror("socket");
E 4
I 4
D 11
		syslog("socket: %m");
E 11
I 11
		syslog(LOG_ERR, "socket: %m");
E 11
E 4
		sleep(5 * retry);
		retry <<= 1;
	}
	if (retry == 0)
		return (-1);
D 2
	while (bind(s, sxn, sizeof (*sxn), 0) < 0 && retry) {
E 2
I 2
D 11
	while (bind(s, sns, sizeof (*sns), 0) < 0 && retry) {
E 2
D 4
		perror("bind");
E 4
I 4
		syslog("bind: %m");
E 11
I 11
	while (bind(s, (struct sockaddr *)sns, sizeof (*sns)) < 0 && retry) {
		syslog(LOG_ERR, "bind: %m");
E 11
E 4
		sleep(5 * retry);
		retry <<= 1;
	}
	if (retry == 0)
		return (-1);
I 2
	if (domain==AF_NS) {
		struct idp idp;
		if (setsockopt(s, 0, SO_HEADERS_ON_INPUT, &on, sizeof(on))) {
D 4
			perror("setsockopt SEE HEADERS");
E 4
I 4
D 11
			syslog("setsockopt SEE HEADERS: %m");
E 11
I 11
			syslog(LOG_ERR, "setsockopt SEE HEADERS: %m");
E 11
E 4
			exit(1);
		}
		idp.idp_pt = NSPROTO_RI;
		if (setsockopt(s, 0, SO_DEFAULT_HEADERS, &idp, sizeof(idp))) {
D 4
			perror("setsockopt SET HEADERS");
E 4
I 4
D 11
			syslog("setsockopt SET HEADER: %m");
E 11
I 11
			syslog(LOG_ERR, "setsockopt SET HEADER: %m");
E 11
E 4
			exit(1);
		}
	}
	if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &on, sizeof (on)) < 0) {
D 4
		perror("setsockopt SO_BROADCAST");
E 4
I 4
D 11
		syslog("setsockopt SO_BROADCAST: %m");
E 11
I 11
		syslog(LOG_ERR, "setsockopt SO_BROADCAST: %m");
E 11
E 4
		exit(1);
	}
E 2
	return (s);
}

/*
 * Fork and exit on EMT-- for profiling.
 */
I 11
void
E 11
fkexit()
{
	if (fork() == 0)
		exit(0);
}
E 1
