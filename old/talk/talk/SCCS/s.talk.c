h21461
s 00003/00001/00048
d D 8.3 95/04/29 10:09:50 bostic 3 2
c It failed to compile on the sparc because `swapresponse' was
c ifdef'ed on vax, sun, i386 (but not sparc).  I made it pass gcc2 -Wall.
c From: Chris Torek <torek@BSDI.COM>
e
s 00007/00006/00042
d D 8.2 94/04/02 15:19:09 bostic 2 1
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00048/00000/00000
d D 8.1 94/04/02 15:15:34 bostic 1 0
c date and time created 94/04/02 15:15:34 by bostic
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
char copyright[] =
D 2
"@(#) Copyright (c) 1983 Regents of the University of California.\n\
 All rights reserved.\n";
E 2
I 2
"@(#) Copyright (c) 1983, 1985\n\
	 Regents of the University of California.  All rights reserved.\n";
E 2
#endif not lint

#ifndef lint
static char sccsid[] = "@(#)talk.c	5.1 (Berkeley) 6/6/85";
#endif not lint

#include "talk.h"

/*
 * talk:	A visual form of write. Using sockets, a two way 
 *		connection is set up between the two people talking. 
 *		With the aid of curses, the screen is split into two 
 *		windows, and each users text is added to the window,
 *		one character at a time...
 *
 *		Written by Kipp Hickman
 *		
 *		Modified to run under 4.1a by Clem Cole and Peter Moore
 *		Modified to run between hosts by Peter Moore, 8/19/82
 *		Modified to run under 4.1c by Peter Moore 3/17/83
 */

I 3
int
E 3
main(argc, argv)
	int argc;
	char *argv[];
{

	get_names(argc, argv);
	init_display();
	open_ctl();
	open_sockt();
	start_msgs();
D 3
	if (!check_local() )
E 3
I 3
	if (!check_local())
E 3
		invite_remote();
	end_msgs();
	set_edit_chars();
	talk();
I 3
	return (0);
E 3
}
E 1
