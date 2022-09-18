h24464
s 00003/00003/00052
d D 5.4 95/04/29 10:09:49 bostic 4 3
c It failed to compile on the sparc because `swapresponse' was
c ifdef'ed on vax, sun, i386 (but not sparc).  I made it pass gcc2 -Wall.
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00004/00050
d D 5.3 94/04/02 15:19:08 bostic 3 2
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00003/00002/00051
d D 5.2 92/10/17 13:36:41 bostic 2 1
c lint to make gcc shut up
e
s 00053/00000/00000
d D 5.1 92/10/17 13:33:47 bostic 1 0
c date and time created 92/10/17 13:33:47 by bostic
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
static char sccsid[] = "@(#)msgs.c	5.1 (Berkeley) 6/6/85";
#endif not lint

/* 
 * A package to display what is happening every MSG_INTERVAL seconds
 * if we are slow connecting.
 */

#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include "talk.h"

#define MSG_INTERVAL 4
D 4
#define LONG_TIME 100000
E 4

char	*current_state;
int	current_line = 0;

static	struct itimerval itimer;
static	struct timeval wait = { MSG_INTERVAL , 0};
D 4
static	struct timeval undo = { LONG_TIME, 0};
	
E 4
I 4

E 4
I 2
void
E 2
disp_msg()
{

	message(current_state);
}

I 4
void
E 4
start_msgs()
{

	message(current_state);
	signal(SIGALRM, disp_msg);
	itimer.it_value = itimer.it_interval = wait;
D 2
	setitimer(ITIMER_REAL, &itimer, (struct timerval *)0);
E 2
I 2
	setitimer(ITIMER_REAL, &itimer, (struct itimerval *)0);
E 2
}

I 4
void
E 4
end_msgs()
{

	signal(SIGALRM, SIG_IGN);
	timerclear(&itimer.it_value);
	timerclear(&itimer.it_interval);
D 2
	setitimer(ITIMER_REAL, &itimer, (struct timerval *)0);
E 2
I 2
	setitimer(ITIMER_REAL, &itimer, (struct itimerval *)0);
E 2
}
E 1
