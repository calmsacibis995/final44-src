h41290
s 00002/00002/00040
d D 8.1 93/06/08 18:36:23 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00027/00035
d D 6.4 91/04/17 10:18:58 bostic 4 3
c new copyright; att/bsd/shared
e
s 00027/00006/00035
d D 6.3 89/03/07 11:04:18 bostic 3 2
c add Berkeley specific copyright, networking release
e
s 00004/00004/00037
d D 6.2 86/05/08 14:38:13 karels 2 1
c corrections and additions
e
s 00041/00000/00000
d D 6.1 86/05/04 16:34:26 mckusick 1 0
c document distributed with 4.3BSD
e
u
U
t
T
I 1
D 3
.\" Copyright (c) 1986 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
.\"
.\"	%W% (Berkeley) %G%
.\"
E 3
I 3
D 4
/*
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1986 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 4
I 4
D 5
.\" Copyright (c) 1986 The Regents of the University of California.
.\" All rights reserved.
E 5
I 5
.\" Copyright (c) 1986, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 5
.\"
.\" %sccs.include.redist.roff%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 4
E 3
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

#define DATA "The sea is calm tonight, the tide is full . . ."

/*
 * Here I send a datagram to a receiver whose name I get from the command
 * line arguments.  The form of the command line is udgramsend pathname 
 */

main(argc, argv)
D 2
	int             argc;
	char           *argv[];
E 2
I 2
	int argc;
	char *argv[];
E 2
{
D 2
	int             sock;
E 2
I 2
	int sock;
E 2
	struct sockaddr_un name;

	/* Create socket on which to send. */
	sock = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sock < 0) {
		perror("opening datagram socket");
D 2
		exit(-1);
E 2
I 2
		exit(1);
E 2
	}
	/* Construct name of socket to send to. */
	name.sun_family = AF_UNIX;
	strcpy(name.sun_path, argv[1]);
	/* Send message. */
	if (sendto(sock, DATA, sizeof(DATA), 0,
	    &name, sizeof(struct sockaddr_un)) < 0) {
		perror("sending datagram message");
	}
	close(sock);
}
E 1
