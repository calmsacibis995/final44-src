h30378
s 00001/00001/00132
d D 8.5 95/04/28 10:43:07 bostic 9 8
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00009/00008/00124
d D 8.4 94/05/21 08:01:47 pendry 8 7
c fix port number parsing
e
s 00001/00000/00131
d D 8.3 94/03/27 13:45:42 pendry 7 6
c missing #includes
e
s 00020/00005/00111
d D 8.2 94/01/14 00:22:07 pendry 6 5
c fix bogus code
e
s 00002/00002/00114
d D 8.1 93/06/05 11:04:09 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00058/00003/00058
d D 5.2 93/05/28 01:30:16 pendry 4 3
c add portal_tcp implementation
e
s 00000/00000/00061
d D 5.1 92/07/13 15:47:32 pendry 3 2
c move to rev 5
e
s 00028/00000/00033
d D 1.2 92/07/12 09:03:55 pendry 2 1
c checkpoint
e
s 00033/00000/00000
d D 1.1 92/07/09 14:47:42 pendry 1 0
c date and time created 92/07/09 14:47:42 by pendry
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 5
I 5
D 8
 * Copyright (c) 1992, 1993
E 8
I 8
 * Copyright (c) 1992, 1993, 1994
E 8
 *	The Regents of the University of California.  All rights reserved.
E 5
 * All rights reserved.
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * $Id: pt_tcp.c,v 1.1 1992/05/25 21:43:09 jsp Exp jsp $
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
I 2
#include <strings.h>
E 2
#include <sys/types.h>
I 2
#include <sys/param.h>
E 2
#include <sys/syslog.h>
I 4
#include <sys/socket.h>
#include <netinet/in.h>
I 7
#include <arpa/inet.h>
E 7
#include <netdb.h>
E 4

#include "portald.h"

I 2
/*
 * Key will be tcp/host/port[/"priv"]
 * Create a TCP socket connected to the
 * requested host and port.
 * Some trailing suffix values have special meanings.
 * An unrecognised suffix is an error.
 */
E 2
D 4
int portal_tcp(pcr, key, v, so, fdp)
E 4
I 4
int portal_tcp(pcr, key, v, kso, fdp)
E 4
D 8
struct portal_cred *pcr;
char *key;
char **v;
D 4
int so;
E 4
I 4
int kso;
E 4
int *fdp;
E 8
I 8
	struct portal_cred *pcr;
	char *key;
	char **v;
	int kso;
	int *fdp;
E 8
{
I 2
	char host[MAXHOSTNAMELEN];
	char port[MAXHOSTNAMELEN];
	char *p = key + (v[1] ? strlen(v[1]) : 0);
	char *q;
I 4
	struct hostent *hp;
	struct servent *sp;
	struct in_addr **ipp;
	struct in_addr *ip[2];
	struct in_addr ina;
	int s_port;
I 6
	int priv = 0;
E 6
	struct sockaddr_in sain;
E 4

	q = strchr(p, '/');
	if (q == 0 || q - p >= sizeof(host))
		return (EINVAL);
	*q = '\0';
	strcpy(host, p);
D 6
	p = q++;
E 6
I 6
	p = q + 1;
E 6

	q = strchr(p, '/');
D 6
	if (q == 0 || q - p >= sizeof(port))
E 6
I 6
	if (q)
		*q = '\0';
	if (strlen(p) >= sizeof(port))
E 6
		return (EINVAL);
D 6
	*q = '\0';
E 6
	strcpy(port, p);
D 6
	p = q++;
E 6
I 6
	if (q) {
		p = q + 1;
		if (strcmp(p, "priv") == 0) {
			if (pcr->pcr_uid == 0)
				priv = 1;
			else
				return (EPERM);
		} else {
			return (EINVAL);
		}
	}
E 6

E 2
D 4
	return (EHOSTUNREACH);
E 4
I 4
	hp = gethostbyname(host);
	if (hp != 0) {
		ipp = (struct in_addr **) hp->h_addr_list;
	} else {
		ina.s_addr = inet_addr(host);
		if (ina.s_addr == INADDR_NONE)
			return (EINVAL);
		ip[0] = &ina;
		ip[1] = 0;
		ipp = ip;
	}

	sp = getservbyname(port, "tcp");
	if (sp != 0)
		s_port = sp->s_port;
	else {
D 8
		s_port = atoi(port);
		if (s_port == 0)
E 8
I 8
		s_port = strtoul(port, &p, 0);
		if (s_port == 0 || *p != '\0')
E 8
			return (EINVAL);
I 8
		s_port = htons(s_port);
E 8
	}

D 9
	bzero(&sain, sizeof(sain));
E 9
I 9
	memset(&sain, 0, sizeof(sain));
E 9
	sain.sin_len = sizeof(sain);
	sain.sin_family = AF_INET;
	sain.sin_port = s_port;

	while (ipp[0]) {
		int so;

D 6
		so = socket(AF_INET, SOCK_STREAM, 0);
E 6
I 6
		if (priv)
			so = rresvport((int *) 0);
		else
			so = socket(AF_INET, SOCK_STREAM, 0);
E 6
		if (so < 0) {
			syslog(LOG_ERR, "socket: %m");
			return (errno);
		}

		sain.sin_addr = *ipp[0];
		if (connect(so, (struct sockaddr *) &sain, sizeof(sain)) == 0) {
			*fdp = so;
			return (0);
		}
		(void) close(so);

		ipp++;
	}

	return (errno);
E 4
}
E 1
