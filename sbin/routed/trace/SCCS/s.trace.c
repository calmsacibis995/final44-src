h15407
s 00002/00002/00097
d D 8.2 95/04/28 11:17:35 bostic 14 13
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00005/00005/00094
d D 8.1 93/06/05 11:17:09 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00014/00095
d D 5.9 91/04/16 17:33:52 bostic 12 11
c new copyright; att/bsd/shared
e
s 00011/00008/00098
d D 5.8 91/02/28 18:13:19 bostic 11 10
c ANSI
e
s 00006/00007/00100
d D 5.7 89/02/18 11:41:36 karels 10 9
c new sockaddrs, other touchups
e
s 00003/00002/00104
d D 5.6 88/10/10 21:59:25 bostic 9 8
c use herror
e
s 00010/00005/00096
d D 5.5 88/06/18 13:49:20 bostic 8 7
c install approved copyright notice
e
s 00010/00004/00091
d D 5.4 88/02/16 18:39:43 bostic 7 6
c add Berkeley specific headers
e
s 00009/00005/00086
d D 5.3 86/02/12 16:43:12 karels 6 5
c accept dot-notation host addresses, -n for query
e
s 00001/00001/00090
d D 5.2 85/11/04 13:19:29 karels 5 4
c update
e
s 00014/00002/00077
d D 5.1 85/06/04 16:41:44 dist 4 3
c Add copyright
e
s 00014/00008/00065
d D 4.3 83/12/21 14:23:42 karels 3 2
c upgrade to 4.2; headers in ..; query looks for multiple responses
c from a host.
e
s 00012/00003/00061
d D 4.2 82/10/06 14:34:32 sam 2 1
c convert to new library
e
s 00064/00000/00000
d D 4.1 82/06/17 11:05:44 sam 1 0
c date and time created 82/06/17 11:05:44 by sam
e
u
U
t
T
I 4
D 12
/*
D 10
 * Copyright (c) 1983 Regents of the University of California.
E 10
I 10
D 11
 * Copyright (c) 1983,1988 Regents of the University of California.
E 11
I 11
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 12
I 12
/*-
D 13
 * Copyright (c) 1983, 1988 The Regents of the University of California.
E 12
E 11
E 10
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 12
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 8
E 7
 */

E 4
I 1
#ifndef lint
D 4
static char sccsid[] = "%W% %G%";
#endif
E 4
I 4
D 13
char copyright[] =
D 10
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 10
I 10
D 11
"%Z% Copyright (c) 1983,1988 Regents of the University of California.\n\
E 11
I 11
D 12
"%Z% Copyright (c) 1983, 1988 Regents of the University of California.\n\
E 12
I 12
"%Z% Copyright (c) 1983, 1988 The Regents of the University of California.\n\
E 12
E 11
E 10
 All rights reserved.\n";
E 13
I 13
static char copyright[] =
"%Z% Copyright (c) 1983, 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 13
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 4

#include <sys/param.h>
#include <sys/protosw.h>
#include <sys/socket.h>
D 3
#include <net/in.h>
E 3
I 3
#include <netinet/in.h>
E 3
D 11
#include <errno.h>
#include <stdio.h>
I 2
#include <netdb.h>
E 11
E 2
D 3
#include "rip.h"
E 3
I 3
D 5
#include "../protocol.h"
E 5
I 5
#include <protocols/routed.h>
I 11
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 11
E 5
E 3

D 10
struct	sockaddr_in myaddr = { AF_INET, IPPORT_RESERVED-1 };
E 10
I 10
struct	sockaddr_in myaddr;
E 10
I 3
char	packet[MAXPACKETSIZE];
E 3

main(argc, argv)
	int argc;
D 11
	char *argv[];
E 11
I 11
	char **argv;
E 11
{
	int size, s;
	struct sockaddr from;
	struct sockaddr_in router;
D 3
	char packet[MAXPACKETSIZE];
E 3
	register struct rip *msg = (struct rip *)packet;
I 2
	struct hostent *hp;
	struct servent *sp;
E 2
	
	if (argc < 3) {
usage:
		printf("usage: trace cmd machines,\n");
		printf("cmd either \"on filename\", or \"off\"\n");
		exit(1);
	}
I 3
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		perror("socket");
		exit(2);
	}
E 3
D 10
#ifdef vax || pdp11
	myaddr.sin_port = htons(myaddr.sin_port);
#endif
E 10
I 10
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(IPPORT_RESERVED-1);
E 10
D 3
	s = socket(SOCK_DGRAM, 0, &myaddr, 0);
	if (s < 0) {
		perror("socket");
E 3
I 3
D 11
	if (bind(s, &myaddr, sizeof(myaddr)) < 0) {
E 11
I 11
	if (bind(s, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
E 11
		perror("bind");
E 3
		exit(2);
	}
I 3

E 3
	argv++, argc--;
	msg->rip_cmd = strcmp(*argv, "on") == 0 ?
		RIPCMD_TRACEON : RIPCMD_TRACEOFF;
I 3
	msg->rip_vers = RIPVERSION;
E 3
	argv++, argc--;
	size = sizeof (int);
	if (msg->rip_cmd == RIPCMD_TRACEON) {
		strcpy(msg->rip_tracefile, *argv);
		size += strlen(*argv);
		argv++, argc--;
	}
	if (argc == 0)
		goto usage;
D 14
	bzero((char *)&router, sizeof (router));
E 14
I 14
	memset(&router, 0, sizeof (router));
E 14
	router.sin_family = AF_INET;
D 2
	router.sin_port = htons(IPPORT_ROUTESERVER);
E 2
I 2
	sp = getservbyname("router", "udp");
	if (sp == 0) {
		printf("udp/router: service unknown\n");
		exit(1);
	}
D 3
	router.sin_port = htons(sp->s_port);
E 3
I 3
	router.sin_port = sp->s_port;
E 3
E 2
	while (argc > 0) {
D 2
		router.sin_addr.s_addr = rhost(argv);
		if (router.sin_addr.s_addr == -1) {
E 2
I 2
D 6
		hp = gethostbyname(*argv);
		if (hp == 0) {
E 2
			printf("%s: unknown\n", *argv);
			continue;
E 6
I 6
		router.sin_family = AF_INET;
		router.sin_addr.s_addr = inet_addr(*argv);
		if (router.sin_addr.s_addr == -1) {
			hp = gethostbyname(*argv);
D 9
			if (hp == 0) {
				printf("%s: unknown\n", *argv);
E 9
I 9
			if (hp == NULL) {
				fprintf(stderr, "trace: %s: ", *argv);
				herror((char *)NULL);
E 9
D 10
				exit(1);
E 10
I 10
				continue;
E 10
			}
D 14
			bcopy(hp->h_addr, &router.sin_addr, hp->h_length);
E 14
I 14
			memmove(&router.sin_addr, hp->h_addr, hp->h_length);
E 14
E 6
		}
I 2
D 6
		bcopy(hp->h_addr, &router.sin_addr, hp->h_length);
E 6
E 2
D 3
		if (send(s, &router, packet, size) < 0)
E 3
I 3
D 11
		if (sendto(s, packet, size, 0, &router, sizeof(router)) < 0)
E 11
I 11
		if (sendto(s, packet, size, 0,
		    (struct sockaddr *)&router, sizeof(router)) < 0)
E 11
E 3
			perror(*argv);
		argv++, argc--;
	}
}
E 1
