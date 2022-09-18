h36983
s 00002/00000/00023
d D 8.3 95/04/29 10:09:51 bostic 3 2
c It failed to compile on the sparc because `swapresponse' was
c ifdef'ed on vax, sun, i386 (but not sparc).  I made it pass gcc2 -Wall.
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00004/00018
d D 8.2 94/04/02 15:19:10 bostic 2 1
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00022/00000/00000
d D 8.1 94/04/02 15:15:41 bostic 1 0
c date and time created 94/04/02 15:15:41 by bostic
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
 *
 *	@(#)talk_ctl.h	5.1 (Berkeley) 6/6/85
 */

#include "ctl.h"
#include "talk.h"
#include <errno.h>

extern	int errno;

extern	struct sockaddr_in daemon_addr;
extern	struct sockaddr_in ctl_addr;
extern	struct sockaddr_in my_addr;
extern	struct in_addr my_machine_addr;
extern	struct in_addr his_machine_addr;
extern	u_short daemon_port;
extern	int ctl_sockt;
extern	CTL_MSG msg;
I 3

void	ctl_transact __P((struct in_addr, CTL_MSG, int, CTL_RESPONSE *));
E 3
E 1
