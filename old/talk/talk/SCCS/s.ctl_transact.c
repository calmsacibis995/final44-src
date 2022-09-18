h48756
s 00004/00002/00083
d D 1.5 95/04/29 10:09:42 bostic 5 4
c It failed to compile on the sparc because `swapresponse' was
c ifdef'ed on vax, sun, i386 (but not sparc).  I made it pass gcc2 -Wall.
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00004/00080
d D 1.4 94/04/02 15:19:03 bostic 4 3
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00002/00001/00082
d D 1.3 92/10/17 13:36:37 bostic 3 2
c lint to make gcc shut up
e
s 00000/00000/00083
d D 1.2 89/05/08 21:39:01 kfall 2 1
c no change
e
s 00083/00000/00000
d D 1.1 89/05/08 12:07:51 kfall 1 0
c date and time created 89/05/08 12:07:51 by kfall
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
 * Copyright (c) 1983, 1985
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
static char sccsid[] = "@(#)ctl_transact.c	5.1 (Berkeley) 6/6/85";
#endif not lint

#include "talk_ctl.h"
#include <sys/time.h>
I 5
#include <unistd.h>
E 5

#define CTL_WAIT 2	/* time to wait for a response, in seconds */

/*
 * SOCKDGRAM is unreliable, so we must repeat messages if we have
 * not recieved an acknowledgement within a reasonable amount
 * of time
 */
I 5
void
E 5
ctl_transact(target, msg, type, response)
	struct in_addr target;
	CTL_MSG msg;
	int type;
	CTL_RESPONSE *response;
{
	struct sockaddr junk;
	int read_mask;
	int ctl_mask;
	int nready;
	int cc;
	int junk_size;
	struct timeval wait;

	msg.type = type;
	daemon_addr.sin_addr = target;
	daemon_addr.sin_port = daemon_port;
	ctl_mask = 1 << ctl_sockt;

	/*
	 * keep sending the message until a response of the right
	 * type is obtained
	 */
	do {
		wait.tv_sec = CTL_WAIT;
		wait.tv_usec = 0;

		/* keep sending the message until a response is obtained */
		do {
			cc = sendto(ctl_sockt, (char *)&msg, sizeof(CTL_MSG), 0,
D 3
				&daemon_addr, sizeof(daemon_addr));
E 3
I 3
			    (struct sockaddr *)&daemon_addr,
			    sizeof(daemon_addr));
E 3
			if (cc != sizeof(CTL_MSG)) {
				if (errno == EINTR)
					continue;
				p_error("Error on write to talk daemon");
			}
			read_mask = ctl_mask;
D 5
			if ((nready = select(32, &read_mask, 0, 0, &wait)) < 0) {
E 5
I 5
			if ((nready = select(32, (fd_set *)&read_mask, 0, 0, &wait)) < 0) {
E 5
				if (errno == EINTR)
					continue;
				p_error("Error waiting for daemon response");
			}
		} while (nready == 0);
		/* keep reading while there are queued messages 
		   (this is not necessary, it just saves extra
		   request/acknowledgements being sent)
		 */
		do {
			junk_size = sizeof(junk);
			cc = recvfrom(ctl_sockt, (char *)response,
			    sizeof (CTL_RESPONSE), 0, &junk, &junk_size);
			if (cc < 0) {
				if (errno == EINTR)
					continue;
				p_error("Error on read from talk daemon");
			}
			read_mask = ctl_mask;
			/* an immediate poll */
			timerclear(&wait);
D 5
			nready = select(32, &read_mask, 0, 0, &wait);
E 5
I 5
			nready = select(32, (fd_set *)&read_mask, 0, 0, &wait);
E 5
		} while (nready > 0 && response->type != type);
	} while (response->type != type);
}
E 1
