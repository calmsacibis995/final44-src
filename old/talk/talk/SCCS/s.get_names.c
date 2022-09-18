h19843
s 00005/00004/00082
d D 8.3 95/04/29 10:09:45 bostic 3 2
c It failed to compile on the sparc because `swapresponse' was
c ifdef'ed on vax, sun, i386 (but not sparc).  I made it pass gcc2 -Wall.
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00004/00081
d D 8.2 94/04/02 15:19:05 bostic 2 1
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00085/00000/00000
d D 8.1 94/04/02 15:14:58 bostic 1 0
c date and time created 94/04/02 15:14:58 by bostic
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
static char sccsid[] = "@(#)get_names.c	5.1 (Berkeley) 6/6/85";
#endif not lint

#include "talk.h"
#include "ctl.h"
I 3
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
E 3

D 3
char *getlogin(), *ttyname(), *rindex();

E 3
extern CTL_MSG msg;

D 3
struct hostent *gethostbyname();

E 3
/*
 * Determine the local and remote user, tty, and machines
 */
I 3
void
E 3
get_names(argc, argv)
	int argc;
	char *argv[];
{
	char hostname[HOST_NAME_LENGTH];
	char *his_name;
	char *my_name;
	char *my_machine_name;
	char *his_machine_name;
	char *my_tty;
	char *his_tty;
	char *ptr;

	if (argc < 2 ) {
		printf("Usage:	talk user [ttyname]\n");
		exit(-1);
	}
	if (!isatty(0)) {
		printf("Standard input must be a tty, not a pipe or a file\n");
		exit(-1);
	}
	my_name = getlogin();
	if (my_name == NULL) {
		printf("You don't exist. Go away.\n");
		exit(-1);
	}
	gethostname(hostname, sizeof (hostname));
	my_machine_name = hostname;
	my_tty = rindex(ttyname(0), '/') + 1;
	/* check for, and strip out, the machine name of the target */
	for (ptr = argv[1]; *ptr != '\0' && *ptr != '@' && *ptr != ':' &&
	    *ptr != '!' && *ptr != '.'; ptr++)
		;
	if (*ptr == '\0') {
		/* this is a local to local talk */
		his_name = argv[1];
		his_machine_name = my_machine_name;
	} else {
		if (*ptr == '@') {
			/* user@host */
			his_name = argv[1];
			his_machine_name = ptr + 1;
		} else {
			/* host.user or host!user or host:user */
			his_name = ptr + 1;
			his_machine_name = argv[1];
		}
		*ptr = '\0';
	}
	if (argc > 2)
		his_tty = argv[2];	/* tty name is arg 2 */
	else
		his_tty = "";
	get_addrs(my_machine_name, his_machine_name);
	/* Load these useful values into the standard message header */
	msg.id_num = 0;
	strncpy(msg.l_name, my_name, NAME_SIZE);
	msg.l_name[NAME_SIZE - 1] = '\0';
	strncpy(msg.r_name, his_name, NAME_SIZE);
	msg.r_name[NAME_SIZE - 1] = '\0';
	strncpy(msg.r_tty, his_tty, TTY_SIZE);
	msg.r_tty[TTY_SIZE - 1] = '\0';
}
E 1
