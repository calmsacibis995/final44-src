h09548
s 00006/00003/00077
d D 1.6 95/04/29 10:09:41 bostic 6 5
c It failed to compile on the sparc because `swapresponse' was
c ifdef'ed on vax, sun, i386 (but not sparc).  I made it pass gcc2 -Wall.
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00004/00075
d D 1.5 94/04/02 15:19:03 bostic 5 4
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00004/00004/00075
d D 1.4 92/10/17 13:36:36 bostic 4 3
c lint to make gcc shut up
e
s 00001/00001/00078
d D 1.3 92/07/19 16:30:33 marc 3 2
c bind only takes three arguments
e
s 00000/00000/00079
d D 1.2 89/05/08 21:38:28 kfall 2 1
c no change
e
s 00079/00000/00000
d D 1.1 89/05/08 12:20:13 kfall 1 0
c date and time created 89/05/08 12:20:13 by kfall
e
u
U
t
T
I 1
D 5
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
 * Copyright (c) 1983, 1985
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
E 5
 */

#ifndef lint
static char sccsid[] = "@(#)ctl.c	5.1 (Berkeley) 6/6/85";
#endif not lint

/*
 * This file handles haggling with the various talk daemons to
 * get a socket to talk to. sockt is opened and connected in
 * the progress
 */

#include "talk_ctl.h"

struct	sockaddr_in daemon_addr = { AF_INET };
struct	sockaddr_in ctl_addr = { AF_INET };
struct	sockaddr_in my_addr = { AF_INET };

    /* inet addresses of the two machines */
struct	in_addr my_machine_addr;
struct	in_addr his_machine_addr;

u_short daemon_port;	/* port number of the talk daemon */

int	ctl_sockt;
int	sockt;
int	invitation_waiting = 0;

CTL_MSG msg;

I 6
void
E 6
open_sockt()
{
    int length;

    my_addr.sin_addr = my_machine_addr;
    my_addr.sin_port = 0;
    sockt = socket(AF_INET, SOCK_STREAM, 0);
    if (sockt <= 0)
	p_error("Bad socket");
D 4
    if (bind(sockt, &my_addr, sizeof(my_addr)) != 0)
E 4
I 4
    if (bind(sockt, (struct sockaddr *)&my_addr, sizeof(my_addr)) != 0)
E 4
	p_error("Binding local socket");
    length = sizeof(my_addr);
D 4
    if (getsockname(sockt, &my_addr, &length) == -1)
E 4
I 4
    if (getsockname(sockt, (struct sockaddr *)&my_addr, &length) == -1)
E 4
	p_error("Bad address for socket");
}

/* open the ctl socket */
I 6
void
E 6
open_ctl() 
{
    int length;

    ctl_addr.sin_port = 0;
    ctl_addr.sin_addr = my_machine_addr;
    ctl_sockt = socket(AF_INET, SOCK_DGRAM, 0);
    if (ctl_sockt <= 0)
	p_error("Bad socket");
D 3
    if (bind(ctl_sockt, &ctl_addr, sizeof(ctl_addr), 0) != 0)
E 3
I 3
D 4
    if (bind(ctl_sockt, &ctl_addr, sizeof(ctl_addr)) != 0)
E 4
I 4
    if (bind(ctl_sockt, (struct sockaddr *)&ctl_addr, sizeof(ctl_addr)) != 0)
E 4
E 3
	p_error("Couldn't bind to control socket");
    length = sizeof(ctl_addr);
D 4
    if (getsockname(ctl_sockt, &ctl_addr, &length) == -1)
E 4
I 4
    if (getsockname(ctl_sockt, (struct sockaddr *)&ctl_addr, &length) == -1)
E 4
	p_error("Bad address for ctl socket");
}

/* print_addr is a debug print routine */
I 6
void
E 6
print_addr(addr)
D 6
struct sockaddr_in addr;
E 6
I 6
    struct sockaddr_in addr;
E 6
{
    int i;

D 6
    printf("addr = %x, port = %o, family = %o zero = ",
	    addr.sin_addr, addr.sin_port, addr.sin_family);
E 6
I 6
    printf("addr = %lx, port = %o, family = %o zero = ",
	    (long)addr.sin_addr.s_addr, addr.sin_port, addr.sin_family);
E 6
    for (i = 0; i<8;i++)
	printf("%o ", (int)addr.sin_zero[i]);
    putchar('\n');
}
E 1
