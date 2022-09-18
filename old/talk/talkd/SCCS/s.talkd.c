h56435
s 00007/00006/00104
d D 5.3 94/04/02 15:23:58 bostic 3 2
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00005/00004/00105
d D 5.2 92/10/17 13:26:54 bostic 2 1
c TWO BUGS (printf doesn't take a FILE *, plus wrong arg to gettimeofday)
c lint to make cc shut up
e
s 00109/00000/00000
d D 5.1 92/10/17 13:20:14 bostic 1 0
c date and time created 92/10/17 13:20:14 by bostic
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1983, 1985
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
char copyright[] =
D 3
"@(#) Copyright (c) 1983 Regents of the University of California.\n\
 All rights reserved.\n";
E 3
I 3
"@(#) Copyright (c) 1983, 1985\n\
	Regents of the University of California.  All rights reserved.\n";
E 3
#endif not lint

#ifndef lint
static char sccsid[] = "@(#)talkd.c	5.1 (Berkeley) 6/6/85";
#endif not lint

/*
 * The top level of the daemon, the format is heavily borrowed
 * from rwhod.c. Basically: find out who and where you are; 
 * disconnect all descriptors and ttys, and then endless
 * loop on waiting for and processing requests
 */
#include <stdio.h>
#include <errno.h>
#include <signal.h>

#include "ctl.h"

struct	sockaddr_in sin = { AF_INET };

CTL_MSG		request;
CTL_RESPONSE	response;

int	sockt;
int	debug = 0;
FILE	*debugout;
D 2
int	timeout();
E 2
I 2
void	timeout();
E 2
long	lastmsgtime;

char	hostname[32];

#define TIMEOUT 30
#define MAXIDLE 120

main(argc, argv)
	int argc;
	char *argv[];
{
	struct sockaddr_in from;
	int fromlen, cc;
	
	if (debug)
		debugout = (FILE *)fopen ("/usr/tmp/talkd.msgs", "w");

	if (getuid()) {
		fprintf(stderr, "Talkd : not super user\n");
		exit(1);
	}
	gethostname(hostname, sizeof (hostname));
	(void) chdir("/dev");
	signal(SIGALRM, timeout);
	alarm(TIMEOUT);
	for (;;) {
		extern int errno;

		fromlen = sizeof(from);
D 2
		cc = recvfrom(0, (char *)&request, sizeof (request), 0,
		    &from, &fromlen);
E 2
I 2
		cc = recvfrom(0, (char *) &request, sizeof (request), 0,
		    (struct sockaddr *)&from, &fromlen);
E 2
		if (cc != sizeof(request)) {
			if (cc < 0 && errno != EINTR)
			perror("recvfrom");
			continue;
		}
		lastmsgtime = time(0);
		swapmsg(&request);
		if (debug) print_request(&request);
		process_request(&request, &response);
		/* can block here, is this what I want? */
		cc = sendto(sockt, (char *) &response,
D 2
		    sizeof (response), 0, &request.ctl_addr,
E 2
I 2
		    sizeof (response), 0, (struct sockaddr *)&request.ctl_addr,
E 2
		    sizeof (request.ctl_addr));
		if (cc != sizeof(response))
			perror("sendto");
	}
}

I 2
void
E 2
timeout()
{

	if (time(0) - lastmsgtime >= MAXIDLE)
		exit(0);
	alarm(TIMEOUT);
}

/*  
 * heuristic to detect if need to swap bytes
 */

swapmsg(req)
	CTL_MSG *req;
{
	if (req->ctl_addr.sin_family == ntohs(AF_INET)) {
		req->id_num = ntohl(req->id_num);
		req->pid = ntohl(req->pid);
		req->addr.sin_family = ntohs(req->addr.sin_family);
		req->ctl_addr.sin_family =
			ntohs(req->ctl_addr.sin_family);
	}
}
E 1
