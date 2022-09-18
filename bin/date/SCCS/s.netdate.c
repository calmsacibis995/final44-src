h36902
s 00001/00000/00156
d D 8.2 95/04/28 09:45:40 bostic 5 4
c The sin_zero field of one of the sockaddr's wasn't being zeroed.
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/00154
d D 8.1 93/05/31 14:20:48 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00020/00132
d D 5.3 93/04/28 16:24:59 bostic 3 2
c lint, bzero -> memset, prototypes, use library err/warn routines
e
s 00005/00003/00147
d D 5.2 91/02/25 07:27:29 bostic 2 1
c ANSI fixes
e
s 00150/00000/00000
d D 5.1 90/12/04 20:23:33 bostic 1 0
c split out from date.c; some reworking for cleanliness.
c date and time created 90/12/04 20:23:33 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/time.h>
#include <sys/socket.h>
D 3
#include <sys/errno.h>
E 3
I 3

E 3
#include <netinet/in.h>
#include <netdb.h>
#define TSPTYPES
#include <protocols/timed.h>
I 2
D 3
#include <unistd.h>
E 3
I 3

#include <err.h>
#include <errno.h>
E 3
E 2
#include <stdio.h>
I 2
#include <string.h>
I 3
#include <unistd.h>
E 3
E 2

I 3
#include "extern.h"

E 3
#define	WAITACK		2	/* seconds */
#define	WAITDATEACK	5	/* seconds */

extern int retval;

/*
 * Set the date in the machines controlled by timedaemons by communicating the
 * new date to the local timedaemon.  If the timedaemon is in the master state,
 * it performs the correction on all slaves.  If it is in the slave state, it
 * notifies the master that a correction is needed.
 * Returns 0 on success.  Returns > 0 on failure, setting retval to 2;
 */
I 3
int
E 3
netsettime(tval)
	time_t tval;
{
	struct timeval tout;
	struct servent *sp;
	struct tsp msg;
	struct sockaddr_in sin, dest, from;
	fd_set ready;
	long waittime;
	int s, length, port, timed_ack, found, err;
	char hostname[MAXHOSTNAMELEN];

	if ((sp = getservbyname("timed", "udp")) == NULL) {
D 3
		(void)fprintf(stderr, "date: udp/timed: unknown service.n");
E 3
I 3
		warnx("udp/timed: unknown service");
E 3
		return (retval = 2);
	}

I 5
	memset(&dest, 0, sizeof(dest));
E 5
	dest.sin_port = sp->s_port;
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = htonl((u_long)INADDR_ANY);
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		if (errno != EPROTONOSUPPORT)
D 3
			perror("date: timed");
		return(retval = 2);
E 3
I 3
			warn("timed");
		return (retval = 2);
E 3
	}

D 3
	bzero((char *)&sin, sizeof(sin));
E 3
I 3
	memset(&sin, 0, sizeof(sin));
E 3
	sin.sin_family = AF_INET;
	for (port = IPPORT_RESERVED - 1; port > IPPORT_RESERVED / 2; port--) {
		sin.sin_port = htons((u_short)port);
		if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) >= 0)
			break;
		if (errno == EADDRINUSE)
			continue;
		if (errno != EADDRNOTAVAIL)
D 3
			perror("date: bind");
E 3
I 3
			warn("bind");
E 3
		goto bad;
	}
	if (port == IPPORT_RESERVED / 2) {
D 3
		(void)fprintf(stderr, "date: all ports in use.\n");
E 3
I 3
		warnx("all ports in use");
E 3
		goto bad;
	}
	msg.tsp_type = TSP_SETDATE;
	msg.tsp_vers = TSPVERSION;
	if (gethostname(hostname, sizeof(hostname))) {
D 3
		perror("date: gethostname");
E 3
I 3
		warn("gethostname");
E 3
		goto bad;
	}
	(void)strncpy(msg.tsp_name, hostname, sizeof(hostname));
	msg.tsp_seq = htons((u_short)0);
	msg.tsp_time.tv_sec = htonl((u_long)tval);
	msg.tsp_time.tv_usec = htonl((u_long)0);
	length = sizeof(struct sockaddr_in);
D 2
	if (connect(s, &dest, length) < 0) {
E 2
I 2
	if (connect(s, (struct sockaddr *)&dest, length) < 0) {
E 2
D 3
		perror("date: connect");
E 3
I 3
		warn("connect");
E 3
		goto bad;
	}
	if (send(s, (char *)&msg, sizeof(struct tsp), 0) < 0) {
		if (errno != ECONNREFUSED)
D 3
			perror("date: send");
E 3
I 3
			warn("send");
E 3
		goto bad;
	}

	timed_ack = -1;
	waittime = WAITACK;
loop:
	tout.tv_sec = waittime;
	tout.tv_usec = 0;

	FD_ZERO(&ready);
	FD_SET(s, &ready);
	found = select(FD_SETSIZE, &ready, (fd_set *)0, (fd_set *)0, &tout);

	length = sizeof(err);
D 3
	if (!getsockopt(s, SOL_SOCKET, SO_ERROR, (char *)&err, &length)
	    && err) {
E 3
I 3
	if (!getsockopt(s,
	    SOL_SOCKET, SO_ERROR, (char *)&err, &length) && err) {
E 3
		if (err != ECONNREFUSED)
D 3
			perror("date: send (delayed error)");
E 3
I 3
			warn("send (delayed error)");
E 3
		goto bad;
	}

	if (found > 0 && FD_ISSET(s, &ready)) {
		length = sizeof(struct sockaddr_in);
D 2
		if (recvfrom(s, (char *)&msg, sizeof(struct tsp), 0, &from,
		    &length) < 0) {
E 2
I 2
		if (recvfrom(s, &msg, sizeof(struct tsp), 0,
		    (struct sockaddr *)&from, &length) < 0) {
E 2
			if (errno != ECONNREFUSED)
D 3
				perror("date: recvfrom");
E 3
I 3
				warn("recvfrom");
E 3
			goto bad;
		}
		msg.tsp_seq = ntohs(msg.tsp_seq);
		msg.tsp_time.tv_sec = ntohl(msg.tsp_time.tv_sec);
		msg.tsp_time.tv_usec = ntohl(msg.tsp_time.tv_usec);
		switch (msg.tsp_type) {
		case TSP_ACK:
			timed_ack = TSP_ACK;
			waittime = WAITDATEACK;
			goto loop;
		case TSP_DATEACK:
			(void)close(s);
			return (0);
		default:
D 3
			(void)fprintf(stderr,
			    "date: wrong ack received from timed: %s.\n", 
E 3
I 3
			warnx("wrong ack received from timed: %s", 
E 3
			    tsptype[msg.tsp_type]);
			timed_ack = -1;
			break;
		}
	}
	if (timed_ack == -1)
D 3
		(void)fprintf(stderr,
		    "date: can't reach time daemon, time set locally.\n");
E 3
I 3
		warnx("can't reach time daemon, time set locally");
E 3

bad:
	(void)close(s);
D 3
	return(retval = 2);
E 3
I 3
	return (retval = 2);
E 3
}
E 1
