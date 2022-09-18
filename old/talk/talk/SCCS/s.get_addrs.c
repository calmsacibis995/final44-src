h47333
s 00005/00003/00050
d D 8.3 95/04/29 10:09:44 bostic 3 2
c It failed to compile on the sparc because `swapresponse' was
c ifdef'ed on vax, sun, i386 (but not sparc).  I made it pass gcc2 -Wall.
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00004/00048
d D 8.2 94/04/02 15:19:05 bostic 2 1
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00052/00000/00000
d D 8.1 94/04/02 15:14:39 bostic 1 0
c date and time created 94/04/02 15:14:39 by bostic
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
/*-
 * Copyright (c) 1983, 1985
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
static char sccsid[] = "@(#)get_addrs.c	5.1 (Berkeley) 6/6/85";
#endif not lint

#include "talk_ctl.h"
I 3
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
E 3

D 3
struct	hostent *gethostbyname();
struct	servent *getservbyname();

E 3
I 3
void
E 3
get_addrs(my_machine_name, his_machine_name)
	char *my_machine_name;
	char *his_machine_name;
{
	struct hostent *hp;
	struct servent *sp;

	msg.pid = getpid();
	/* look up the address of the local host */
	hp = gethostbyname(my_machine_name);
	if (hp == (struct hostent *) 0) {
		printf("This machine doesn't exist. Boy, am I confused!\n");
		exit(-1);
	}
	bcopy(hp->h_addr, (char *)&my_machine_addr, hp->h_length);
	/* if he is on the same machine, then simply copy */
	if (bcmp((char *)&his_machine_name, (char *)&my_machine_name,
	    sizeof(his_machine_name)) == 0)
		bcopy((char *)&my_machine_addr, (char *)&his_machine_addr,
		    sizeof(his_machine_name));
	else {
		/* look up the address of the recipient's machine */
		hp = gethostbyname(his_machine_name);
		if (hp == (struct hostent *) 0 ) {
			printf("%s is an unknown host\n", his_machine_name);
			exit(-1);
		}
		bcopy(hp->h_addr, (char *) &his_machine_addr, hp->h_length);
	}
	/* find the daemon portal */
	sp = getservbyname("talk", "udp");
	if (sp == 0) {
		p_error("This machine doesn't support talk");
		exit(-1);
	}
	daemon_port = sp->s_port;
}
E 1
